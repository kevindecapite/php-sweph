<?php

declare(strict_types=1);

use Sweph\Enums\CalculationFlag;
use Sweph\Enums\Calendar;
use Sweph\Enums\HouseSystem;
use Sweph\Enums\Planet;
use Sweph\SwephConfig;
use Sweph\SwephFactory;
use Sweph\ValueObject\GeographicPosition;

require dirname(__DIR__) . '/vendor/autoload.php';

$date = new DateTimeImmutable(
    '1990-07-15 12:00:00',
    new DateTimeZone('UTC'),
);

$location = new GeographicPosition(
    longitude: 13.4050,
    latitude: 52.5200,
    altitudeMeters: 34.0,
);

$sweph = SwephFactory::create(
    new SwephConfig(
        ephemerisPath: dirname(__DIR__) . '/ephe',
        observer: $location,
    ),
);

try {
    $decimalHour = (int) $date->format('G')
        + ((int) $date->format('i') / 60)
        + ((int) $date->format('s') / 3600);

    $julianDay = $sweph->time()->julianDay(
        year: (int) $date->format('Y'),
        month: (int) $date->format('n'),
        day: (int) $date->format('j'),
        decimalHour: $decimalHour,
        calendar: Calendar::Gregorian,
    );

    $planetFlags = CalculationFlag::combine(
        CalculationFlag::SwissEphemeris,
        CalculationFlag::Speed,
        CalculationFlag::Topocentric,
    );

    $bodies = [
        Planet::Sun,
        Planet::Moon,
        Planet::Mercury,
        Planet::Venus,
        Planet::Mars,
        Planet::Jupiter,
        Planet::Saturn,
        Planet::Uranus,
        Planet::Neptune,
        Planet::Pluto,
        Planet::TrueNode,
    ];

    echo "Geburtshoroskop\n";
    echo "================\n";

    printf(
        "Zeit: %s UTC\n",
        $date->format('Y-m-d H:i:s'),
    );

    printf(
        "Ort: %.4f° N, %.4f° E; Höhe %.0f m\n",
        $location->latitude,
        $location->longitude,
        $location->altitudeMeters,
    );

    printf(
        "Julianischer Tag: %.8f\n\n",
        $julianDay->value,
    );

    echo "Planeten und Punkte\n";
    echo "-------------------\n";

    foreach ($bodies as $body) {
        $position = $sweph->planets()->calculateUt(
            julianDayUt: $julianDay->value,
            planet: $body,
            flags: $planetFlags,
        );

        printf(
            "%-12s Länge: %10.6f°  Breite: %9.6f°  Geschwindigkeit: %+10.6f°/Tag\n",
            $body->name,
            $position->longitude,
            $position->latitude,
            $position->longitudeSpeed,
        );
    }

    $houses = $sweph->houses()->calculate(
        julianDayUt: $julianDay->value,
        position: $location,
        system: HouseSystem::Placidus,
    );

    echo "\nHäuser nach Placidus\n";
    echo "--------------------\n";

    /*
     * Bei normalen Häusersystemen befindet sich an Index 0 üblicherweise
     * ein unbenutzter Eintrag. Die Hausspitzen liegen an Index 1 bis 12.
     */
    for ($house = 1; $house <= 12; $house++) {
        if (!isset($houses->cusps[$house])) {
            continue;
        }

        printf(
            "Haus %2d: %10.6f°\n",
            $house,
            $houses->cusps[$house],
        );
    }

    echo "\nAchsen\n";
    echo "------\n";

    if (isset($houses->angles[0])) {
        printf(
            "Aszendent:     %10.6f°\n",
            $houses->angles[0],
        );
    }

    if (isset($houses->angles[1])) {
        printf(
            "Medium Coeli:  %10.6f°\n",
            $houses->angles[1],
        );
    }

    if (isset($houses->angles[2])) {
        printf(
            "ARMC:          %10.6f°\n",
            $houses->angles[2],
        );
    }

    if (isset($houses->angles[3])) {
        printf(
            "Vertex:        %10.6f°\n",
            $houses->angles[3],
        );
    }
} finally {
    $sweph->close();
}