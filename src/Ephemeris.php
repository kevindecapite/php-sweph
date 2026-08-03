<?php

declare(strict_types=1);

namespace Sweph;

use DateTimeInterface;
use DateTimeZone;
use Sweph\DTO\CelestialPosition;
use Sweph\DTO\HouseCalculation;
use Sweph\Enums\CalculationFlag;
use Sweph\Enums\Calendar;
use Sweph\Enums\HouseSystem;
use Sweph\Enums\Planet;

/**
 * Die Hauptklasse des SDKs.
 * Kapselt die C-Extension "swephp" in ein modernes, objektorientiertes PHP-Interface.
 */
class Ephemeris
{
    private static bool $initialized = false;

    /**
     * Setzt den Pfad zu den Ephemeriden-Dateien (.se1)
     *
     * @param string|null $path Standardmäßig das vom Downloader genutzte Verzeichnis
     */
    public static function setEphePath(?string $path = null): void
    {
        if (!extension_loaded('swephp')) {
            throw new EphemerisException("Die C-Erweiterung 'swephp' ist nicht geladen.");
        }

        if ($path === null) {
            $path = dirname(__DIR__) . '/ephe';
        }

        \swe_set_ephe_path($path);
        self::$initialized = true;
    }

    /**
     * Berechnet die astronomische Position eines Himmelskörpers.
     *
     * @param float $julianDay Der Julianische Tag (Zeitpunkt der Berechnung)
     * @param Planet $planet Der zu berechnende Himmelskörper (Enum)
     * @param array<CalculationFlag> $flags Berechnungsoptionen (z.B. Geozentrisch, Tropisch)
     * @return CelestialPosition Das strukturierte Datenobjekt mit den Ergebnissen
     */
    public static function calculatePlanetPosition(
        float $julianDay,
        Planet $planet,
        array $flags = []
    ): CelestialPosition {
        if (!self::$initialized) {
            self::setEphePath();
        }

        if (empty($flags)) {
            $flags = [CalculationFlag::Speed];
        }

        $bitmask = 0;
        foreach ($flags as $flag) {
            $bitmask |= $flag->value;
        }

        $result = \swe_calc($julianDay, $planet->value, $bitmask);

        if (!is_array($result)) {
            throw new EphemerisException("Fehler beim Aufruf von swe_calc: Ungültiger Rückgabetyp.");
        }

        $rc = $result['rc'] ?? 0;
        $serr = $result['serr'] ?? '';

        if ($rc < 0 || !empty($serr)) {
            throw new EphemerisException(
                sprintf("Fehler bei der Berechnung für %s am Tag %f: %s", $planet->name, $julianDay, $serr)
            );
        }

        // Falls C-Extension ein Unter-Array 'calc' zurückgibt, sonst $result direkt nehmen
        $calcData = $result['calc'] ?? $result;

        return CelestialPosition::fromCArray($calcData);
    }

    /**
     * Alias für calculatePlanetPosition, der ein DateTimeInterface entgegennimmt
     * und es automatisch in UTC umwandelt und den Julianischen Tag berechnet.
     */
    public static function getPlanetPosition(
        Planet $planet,
        DateTimeInterface $dateTime,
        array $flags = []
    ): CelestialPosition {
        // Garantieren, dass wir in UTC rechnen!
        $utcDateTime = \DateTimeImmutable::createFromInterface($dateTime)
            ->setTimezone(new DateTimeZone('UTC'));

        $hour = (int)$utcDateTime->format('H');
        $minute = (int)$utcDateTime->format('i');
        $second = (int)$utcDateTime->format('s');
        $decimalHourUtc = $hour + ($minute / 60.0) + ($second / 3600.0);

        $julianDay = self::getJulianDay(
            (int)$utcDateTime->format('Y'),
            (int)$utcDateTime->format('m'),
            (int)$utcDateTime->format('d'),
            $decimalHourUtc
        );

        return self::calculatePlanetPosition($julianDay, $planet, $flags);
    }

    /**
     * Hilfsmethode zur Umrechnung eines Datums in einen Julianischen Tag.
     */
    public static function getJulianDay(
        int $year,
        int $month,
        int $day,
        float $hourUtc,
        Calendar $calendar = Calendar::GREGORIAN
    ): float {
        return \swe_julday($year, $month, $day, $hourUtc, $calendar->value);
    }

    /**
     * Berechnet die Häuserspitzen und astrologischen Achsen.
     */
    public static function calculateHouses(
        float $julianDay,
        float $latitude,
        float $longitude,
        HouseSystem $system = HouseSystem::PLACIDUS
    ): HouseCalculation {
        if (!self::$initialized) {
            self::setEphePath();
        }

        $hsysChar = ord($system->value);

        // Aufruf der C-Extension (Rückgabe als assoziatives Array)
        $result = \swe_houses($julianDay, $latitude, $longitude, $hsysChar);

        if (!is_array($result) || (isset($result['rc']) && $result['rc'] < 0)) {
            throw new EphemerisException("Fehler bei der Berechnung der Häuserspitzen.");
        }

        return HouseCalculation::fromCArrays(
            $result['cusps'] ?? [],
            $result['ascmc'] ?? []
        );
    }

    public static function setSiderealMode(int $sidMode = 0): void
    {
        if (!self::$initialized) {
            self::setEphePath();
        }

        \swe_set_sid_mode($sidMode, 0.0, 0.0);
    }

    public static function getAyanamsa(float $julianDay): float
    {
        if (!self::$initialized) {
            self::setEphePath();
        }

        return \swe_get_ayanamsa($julianDay);
    }

    public static function close(): void
    {
        if (function_exists('swe_close')) {
            \swe_close();
        }
        self::$initialized = false;
    }
}