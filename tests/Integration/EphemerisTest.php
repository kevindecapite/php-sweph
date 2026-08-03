<?php

declare(strict_types=1);

namespace Integration;

use DateTimeImmutable;
use DateTimeZone;
use PHPUnit\Framework\TestCase;
use Sweph\DTO\CelestialPosition;
use Sweph\Enums\Aspect;
use Sweph\Enums\CalculationFlag;
use Sweph\Enums\Calendar;
use Sweph\Enums\HouseSystem;
use Sweph\Enums\Planet;
use Sweph\Sweph;
use Sweph\SwephConfig;
use Sweph\SwephFactory;
use Sweph\ValueObject\GeographicPosition;

final class EphemerisTest extends TestCase
{
    private Sweph $sweph;

    protected function setUp(): void
    {
        $this->sweph = SwephFactory::create(
            new SwephConfig(
                ephemerisPath: dirname(__DIR__) . '/ephe',
            ),
        );
    }

    protected function tearDown(): void
    {
        $this->sweph->close();
    }

    public function testGetPlanetPositionReturnsValidData(): void
    {
        $date = new DateTimeImmutable(
            '2026-07-15 12:00:00',
            new DateTimeZone('UTC'),
        );

        $decimalHour = (int) $date->format('G')
            + ((int) $date->format('i') / 60)
            + ((int) $date->format('s') / 3600);

        $julianDay = $this->sweph->time()->julianDay(
            year: (int) $date->format('Y'),
            month: (int) $date->format('n'),
            day: (int) $date->format('j'),
            decimalHour: $decimalHour,
            calendar: Calendar::Gregorian,
        );

        $flags = CalculationFlag::combine(
            CalculationFlag::SwissEphemeris,
            CalculationFlag::Speed,
        );

        $position = $this->sweph->planets()->calculateUt(
            julianDayUt: $julianDay->value,
            planet: Planet::Sun,
            flags: $flags,
        );

        self::assertInstanceOf(CelestialPosition::class, $position);
        self::assertSame(Planet::Sun, $position->body);

        self::assertGreaterThanOrEqual(
            0.0,
            $position->longitude,
        );

        self::assertLessThan(
            360.0,
            $position->longitude,
        );

        self::assertEqualsWithDelta(
            1.0,
            $position->longitudeSpeed,
            0.1,
        );

        self::assertEqualsWithDelta(
            1.0,
            $position->distance,
            0.1,
        );
    }

    public function testJulianDayCalculation(): void
    {
        $julianDay = $this->sweph->time()->julianDay(
            year: 2000,
            month: 1,
            day: 1,
            decimalHour: 12.0,
            calendar: Calendar::Gregorian,
        );

        self::assertEqualsWithDelta(
            2451545.0,
            $julianDay->value,
            0.0001,
        );
    }

    public function testCalculateHousesReturnsValidData(): void
    {
        $julianDay = $this->sweph->time()->julianDay(
            year: 2026,
            month: 7,
            day: 15,
            decimalHour: 12.0,
            calendar: Calendar::Gregorian,
        );

        $berlin = new GeographicPosition(
            longitude: 13.4050,
            latitude: 52.5200,
        );

        $houses = $this->sweph->houses()->calculate(
            julianDayUt: $julianDay->value,
            position: $berlin,
            system: HouseSystem::Placidus,
        );

        self::assertGreaterThanOrEqual(
            13,
            count($houses->cusps),
        );

        self::assertArrayHasKey(
            0,
            $houses->angles,
        );

        self::assertArrayHasKey(
            1,
            $houses->angles,
        );

        $ascendant = $houses->angles[0];
        $mediumCoeli = $houses->angles[1];

        self::assertGreaterThanOrEqual(0.0, $ascendant);
        self::assertLessThan(360.0, $ascendant);

        self::assertGreaterThanOrEqual(0.0, $mediumCoeli);
        self::assertLessThan(360.0, $mediumCoeli);
    }

    public function testAspectServiceDetectsConjunction(): void
    {
        $aspectResult = $this->sweph->aspects()->calculate(
            longitude1: 10.0,
            longitude2: 12.0,
            aspect: Aspect::Conjunction,
            orb: 5.0,
            relativeSpeed: -0.5,
        );

        self::assertNotNull($aspectResult);

        self::assertSame(
            Aspect::Conjunction,
            $aspectResult->aspect,
        );

        self::assertEqualsWithDelta(
            2.0,
            $aspectResult->actualAngle,
            0.000001,
        );

        self::assertEqualsWithDelta(
            2.0,
            $aspectResult->deviation,
            0.000001,
        );

        self::assertTrue(
            $aspectResult->applying,
        );
    }
}