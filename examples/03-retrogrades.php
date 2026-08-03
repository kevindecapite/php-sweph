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
        'now',
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
        "Rückläufigkeiten am %s UTC\n",
        $date->format('Y-m-d H:i:s'),
    );

    echo "============================================================\n\n";

    $retrogradeCount = 0;

    foreach ($planets as $planet) {
        $position = $sweph->planets()->calculateUt(
            julianDayUt: $julianDay->value,
            planet: $planet,
            flags: $flags,
        );

        $isRetrograde = $position->longitudeSpeed < 0.0;

        if ($isRetrograde) {
            $retrogradeCount++;
        }

        printf(
            "%-10s %-11s Länge: %10.6f°  Geschwindigkeit: %+10.6f°/Tag\n",
            $planet->name,
            $isRetrograde ? 'rückläufig' : 'direkt',
            $position->longitude,
            $position->longitudeSpeed,
        );
    }

    printf(
        "\n%d von %d untersuchten Planeten sind rückläufig.\n",
        $retrogradeCount,
        count($planets),
    );
} finally {
    $sweph->close();
}