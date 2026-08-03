<?php

declare(strict_types=1);

require_once __DIR__ . '/../vendor/autoload.php';

use Sweph\Ephemeris;
use Sweph\Enums\Planet;
use Sweph\Enums\HouseSystem;
use Sweph\Service\AspectCalculator;
use Sweph\EphemerisException;

// Beispiel: Geburtsdatum 15. Mai 1990, 14:30 Uhr in Berlin (UTC+2 in Sommerszeit -> 12:30 UTC)
$birthDate = new DateTimeImmutable('1990-05-15 12:30:00', new DateTimeZone('UTC'));
$berlinLat = 52.5200;
$berlinLon = 13.4050;

echo "=== Geburtshoroskop (Berlin, {$birthDate->format('Y-m-d H:i:s')} UTC) ===\n\n";

try {
    // 1. Julianischen Tag berechnen
    $julianDay = Ephemeris::getJulianDay(
        (int)$birthDate->format('Y'),
        (int)$birthDate->format('m'),
        (int)$birthDate->format('d'),
        12.5 // 12:30 UTC
    );

    // 2. Häuser berechnen
    $houses = Ephemeris::calculateHouses($julianDay, $berlinLat, $berlinLon, HouseSystem::PLACIDUS);

    echo "--- ACHSEN & HÄUSER ---\n";
    printf("Aszendent (AC): %6.2f°\n", $houses->ascendant);
    printf("Medium Coeli (MC): %6.2f°\n\n", $houses->mc);

    echo "Häuserspitzen:\n";
    foreach ($houses->cusps as $houseNumber => $cuspDegree) {
        printf("Haus %2d: %6.2f°\n", $houseNumber, $cuspDegree);
    }

    // 3. Planetenpositionen berechnen
    echo "\n--- PLANETEN ---\n";
    $planets = [Planet::Sun, Planet::Moon, Planet::Mercury, Planet::Venus, Planet::Mars, Planet::Jupiter];
    $positions = [];

    foreach ($planets as $planet) {
        $positions[$planet->value] = Ephemeris::calculatePlanetPosition($julianDay, $planet);
        printf("%-10s: %6.2f°\n", $planet->name, $positions[$planet->value]->longitude);
    }

    // 4. Aspekte berechnen
    echo "\n--- ASPEKTE ---\n";
    for ($i = 0; $i < count($planets); $i++) {
        for ($j = $i + 1; $j < count($planets); $j++) {
            $p1 = $planets[$i];
            $p2 = $planets[$j];

            $aspect = AspectCalculator::calculate($positions[$p1->value], $positions[$p2->value]);

            if ($aspect !== null) {
                printf(
                    "%-8s %-12s %-8s (Abweichung: %4.2f°, %s)\n",
                    $p1->name,
                    $aspect->aspect->name,
                    $p2->name,
                    $aspect->orb,
                    $aspect->isApplying ? 'zulaufend' : 'ablaufend'
                );
            }
        }
    }

} catch (EphemerisException $e) {
    echo "Fehler: " . $e->getMessage() . "\n";
} finally {
    Ephemeris::close();
}