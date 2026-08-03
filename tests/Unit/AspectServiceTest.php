<?php

declare(strict_types=1);

namespace Sweph\Tests\Unit;

use PHPUnit\Framework\TestCase;
use Sweph\Enums\Aspect;
use Sweph\Service\AspectService;

final class AspectServiceTest extends TestCase
{
    private AspectService $service;

    protected function setUp(): void
    {
        $this->service = new AspectService();
    }

    public function testDetectsExactConjunction(): void
    {
        $result = $this->service->calculate(
            longitude1: 10.0,
            longitude2: 10.0,
            aspect: Aspect::Conjunction,
            orb: 5.0,
        );

        self::assertNotNull($result);
        self::assertSame(Aspect::Conjunction, $result->aspect);
        self::assertSame(0.0, $result->actualAngle);
        self::assertSame(0.0, $result->deviation);
        self::assertFalse($result->applying);
    }

    public function testDetectsConjunctionWithinOrb(): void
    {
        $result = $this->service->calculate(
            longitude1: 10.0,
            longitude2: 12.0,
            aspect: Aspect::Conjunction,
            orb: 5.0,
            relativeSpeed: -0.5,
        );

        self::assertNotNull($result);
        self::assertSame(Aspect::Conjunction, $result->aspect);
        self::assertEqualsWithDelta(2.0, $result->actualAngle, 0.000001);
        self::assertEqualsWithDelta(2.0, $result->deviation, 0.000001);
        self::assertTrue($result->applying);
    }

    public function testReturnsNullOutsideOrb(): void
    {
        $result = $this->service->calculate(
            longitude1: 10.0,
            longitude2: 17.0,
            aspect: Aspect::Conjunction,
            orb: 5.0,
        );

        self::assertNull($result);
    }

    public function testDetectsSquareAcrossZeroDegrees(): void
    {
        $result = $this->service->calculate(
            longitude1: 350.0,
            longitude2: 80.0,
            aspect: Aspect::Square,
            orb: 1.0,
        );

        self::assertNotNull($result);
        self::assertSame(Aspect::Square, $result->aspect);
        self::assertEqualsWithDelta(90.0, $result->actualAngle, 0.000001);
        self::assertEqualsWithDelta(0.0, $result->deviation, 0.000001);
    }

    public function testDetectsOpposition(): void
    {
        $result = $this->service->calculate(
            longitude1: 15.0,
            longitude2: 195.0,
            aspect: Aspect::Opposition,
            orb: 1.0,
        );

        self::assertNotNull($result);
        self::assertSame(Aspect::Opposition, $result->aspect);
        self::assertEqualsWithDelta(180.0, $result->actualAngle, 0.000001);
        self::assertEqualsWithDelta(0.0, $result->deviation, 0.000001);
    }

    public function testUsesDefaultOrbWhenNoneIsProvided(): void
    {
        $result = $this->service->calculate(
            longitude1: 0.0,
            longitude2: 64.5,
            aspect: Aspect::Sextile,
        );

        self::assertNotNull($result);
        self::assertSame(Aspect::Sextile, $result->aspect);
        self::assertEqualsWithDelta(64.5, $result->actualAngle, 0.000001);
        self::assertEqualsWithDelta(4.5, $result->deviation, 0.000001);
    }

    public function testRelativeSpeedGreaterThanZeroIsSeparating(): void
    {
        $result = $this->service->calculate(
            longitude1: 10.0,
            longitude2: 12.0,
            aspect: Aspect::Conjunction,
            orb: 5.0,
            relativeSpeed: 0.5,
        );

        self::assertNotNull($result);
        self::assertFalse($result->applying);
    }

    public function testRelativeSpeedBelowZeroIsApplying(): void
    {
        $result = $this->service->calculate(
            longitude1: 10.0,
            longitude2: 12.0,
            aspect: Aspect::Conjunction,
            orb: 5.0,
            relativeSpeed: -0.5,
        );

        self::assertNotNull($result);
        self::assertTrue($result->applying);
    }
}