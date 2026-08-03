<?php

declare(strict_types=1);

use Sweph\Enums\CalculationFlag;
use Sweph\Enums\Calendar;
use Sweph\Enums\Planet;
use Sweph\SwephConfig;
use Sweph\SwephFactory;

require dirname(__DIR__) . '/vendor/autoload.php';

$sweph = SwephFactory::create(
    new SwephConfig(
        ephemerisPath: dirname(__DIR__) . '/ephe',
    ),
);

try {
    $date = new DateTimeImmutable(
        '2026-07-15 12:00:00',
        new DateTimeZone('UTC'),
    );

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

    $flags = CalculationFlag::combine(
        CalculationFlag::SwissEphemeris,
        CalculationFlag::Speed,
    );

    $planets = [
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
    ];

    printf(
        "Planetenpositionen für %s UTC\n",
        $date->format('Y-m-d H:i:s'),
    );

    printf(
        "Julianischer Tag: %.8f\n\n",
        $julianDay->value,
    );

    foreach ($planets as $planet) {
        $position = $sweph->planets()->calculateUt(
            julianDayUt: $julianDay->value,
            planet: $planet,
            flags: $flags,
        );

        printf(
            "%-10s Länge: %10.6f°  Breite: %9.6f°  Distanz: %12.8f AU  Geschwindigkeit: %+10.6f°/Tag\n",
            $planet->name,
            $position->longitude,
            $position->latitude,
            $position->distance,
            $position->longitudeSpeed,
        );
    }
} finally {
    $sweph->close();
}