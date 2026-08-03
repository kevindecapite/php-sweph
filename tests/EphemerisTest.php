<?php

declare(strict_types=1);

namespace Sweph\Tests;

use DateTimeImmutable;
use DateTimeZone;
use PHPUnit\Framework\TestCase;
use Sweph\DTO\CelestialPosition;
use Sweph\Enums\HouseSystem;
use Sweph\Enums\Planet;
use Sweph\Ephemeris;
use Sweph\Service\AspectCalculator;

final class EphemerisTest extends TestCase
{
    protected function tearDown(): void
    {
        // Sicherstellen, dass C-Resourcen nach dem Test aufgeräumt werden
        Ephemeris::close();
    }

    public function testGetPlanetPositionReturnsValidData(): void
    {
        $date = new DateTimeImmutable('2026-07-15 12:00:00', new DateTimeZone('UTC'));

        // Statischer Aufruf anstelle von Instanziierung
        $position = Ephemeris::getPlanetPosition(Planet::Sun, $date);

        // Validierung des DTO-Typs und der Wertebereiche
        $this->assertInstanceOf(CelestialPosition::class, $position);

        // Die Ekliptik-Länge eines Himmelskörpers liegt immer zwischen 0° und 360°
        $this->assertGreaterThanOrEqual(0.0, $position->longitude);
        $this->assertLessThan(360.0, $position->longitude);

        // Geschwindigkeit der Sonne liegt bei ca. ~1° pro Tag (0.95 bis 1.02)
        $this->assertEqualsWithDelta(1.0, $position->longitudeSpeed, 0.1);

        // Entfernung zur Sonne liegt im Juli (Aphel) bei ca. 1.016 AE
        $this->assertEqualsWithDelta(1.0, $position->distance, 0.1);
    }

    public function testJulianDayCalculation(): void
    {
        // 1. Januar 2000, 12:00 UTC entspricht J2000.0 (2451545.0)
        $jd = Ephemeris::getJulianDay(2000, 1, 1, 12.0);

        $this->assertEqualsWithDelta(2451545.0, $jd, 0.0001);
    }

    public function testCalculateHousesReturnsValidData(): void
    {
        $jd = Ephemeris::getJulianDay(2026, 7, 15, 12.0);
        $berlinLat = 52.5200;
        $berlinLon = 13.4050;

        $houses = Ephemeris::calculateHouses($jd, $berlinLat, $berlinLon, HouseSystem::PLACIDUS);

        $this->assertCount(12, $houses->cusps);
        $this->assertGreaterThanOrEqual(0.0, $houses->ascendant);
        $this->assertLessThan(360.0, $houses->ascendant);
        $this->assertGreaterThanOrEqual(0.0, $houses->mc);
        $this->assertLessThan(360.0, $houses->mc);
    }

    public function testAspectCalculatorDetectsConjunction(): void
    {
        // Erzeuge zwei Test-Positionen mit exakt 0° Abstand
        $pos1 = new CelestialPosition(longitude: 10.0, latitude: 0.0, distance: 1.0, longitudeSpeed: 1.0);
        $pos2 = new CelestialPosition(longitude: 12.0, latitude: 0.0, distance: 1.0, longitudeSpeed: 0.5);

        $aspectResult = AspectCalculator::calculate($pos1, $pos2, maxOrb: 5.0);

        $this->assertNotNull($aspectResult);
        $this->assertEquals(\Sweph\Enums\Aspect::Conjunction, $aspectResult->aspect);
        $this->assertEquals(2.0, $aspectResult->orb);
        $this->assertTrue($aspectResult->isApplying);
    }
}