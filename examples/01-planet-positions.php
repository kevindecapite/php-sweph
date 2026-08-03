<?php

declare(strict_types=1);

require_once __DIR__ . '/../vendor/autoload.php';

use Sweph\Ephemeris;
use Sweph\Enums\Planet;
use Sweph\EphemerisException;

// Ephemeriden-Pfad optional explizit setzen (greift sonst auf das Standard-Verzeichnis zurück)
Ephemeris::setEphePath('/opt/sweph/ephe');

// Aktueller Zeitpunkt (UTC)
$now = new DateTimeImmutable('now', new DateTimeZone('UTC'));

echo "=== Aktuelle Planetenpositionen ({$now->format('Y-m-d H:i:s')} UTC) ===\n\n";

try {
    $planets = [
        Planet::Sun,
        Planet::Moon,
        Planet::Mercury,
        Planet::Venus,
        Planet::Mars,
        Planet::Jupiter,
        Planet::Saturn,
    ];

    foreach ($planets as $planet) {
        $position = Ephemeris::getPlanetPosition($planet, $now);

        printf(
            "%-10s | Länge: %6.2f° | Breite: %5.2f° | Distanz: %6.4f AE | Speed: %5.2f°/Tag\n",
            $planet->name,
            $position->longitude,
            $position->latitude,
            $position->distance,
            $position->longitudeSpeed
        );
    }
} catch (EphemerisException $e) {
    echo "Fehler bei der Berechnung: " . $e->getMessage() . "\n";
} finally {
    Ephemeris::close();
}