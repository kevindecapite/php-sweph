<?php

declare(strict_types=1);

require_once __DIR__ . '/../vendor/autoload.php';

use Sweph\Ephemeris;
use Sweph\Enums\Planet;
use Sweph\EphemerisException;

$now = new DateTimeImmutable('now', new DateTimeZone('UTC'));

echo "=== Rückläufigkeits-Check ({$now->format('Y-m-d H:i:s')} UTC) ===\n\n";

try {
    $planets = [
        Planet::Mercury,
        Planet::Venus,
        Planet::Mars,
        Planet::Jupiter,
        Planet::Saturn,
        Planet::Uranus,
        Planet::Neptune,
        Planet::Pluto,
    ];

    foreach ($planets as $planet) {
        $pos = Ephemeris::getPlanetPosition($planet, $now);
        $isRetrograde = $pos->longitudeSpeed < 0.0;

        printf(
            "%-10s | Speed: %6.3f°/Tag | Status: %s\n",
            $planet->name,
            $pos->longitudeSpeed,
            $isRetrograde ? "🔴 RÜCKLÄUFIG (Retrograde)" : "🟢 DIREKT"
        );
    }
} catch (EphemerisException $e) {
    echo "Fehler: " . $e->getMessage() . "\n";
} finally {
    Ephemeris::close();
}