<?php

declare(strict_types=1);

namespace Sweph;

use Sweph\Contracts\NativeSwephInterface;
use Sweph\Mapper\CelestialPositionMapper;
use Sweph\Mapper\FixstarPositionMapper;
use Sweph\Mapper\HouseCalculationMapper;
use Sweph\Native\ExtensionSweph;
use Sweph\Service\AspectService;
use Sweph\Service\FixstarService;
use Sweph\Service\HouseService;
use Sweph\Service\PlanetService;
use Sweph\Service\TimeService;

final class SwephFactory
{
    public static function create(
        ?SwephConfig $config = null,
        ?NativeSwephInterface $native = null,
    ): Sweph {
        $config ??= new SwephConfig();
        $native ??= new ExtensionSweph();

        if ($config->ephemerisPath !== null) {
            $native->setEphemerisPath($config->ephemerisPath);
        }

        if ($config->observer !== null) {
            $native->setTopocentric(
                $config->observer->longitude,
                $config->observer->latitude,
                $config->observer->altitudeMeters,
            );
        }

        return new Sweph(
            native: $native,
            planetService: new PlanetService($native, new CelestialPositionMapper()),
            fixstarService: new FixstarService($native, new FixstarPositionMapper()),
            houseService: new HouseService($native, new HouseCalculationMapper()),
            timeService: new TimeService($native),
            aspectService: new AspectService(),
        );
    }
}
