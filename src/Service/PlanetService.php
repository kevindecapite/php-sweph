<?php

declare(strict_types=1);

namespace Sweph\Service;

use Sweph\Contracts\NativeSwephInterface;
use Sweph\Contracts\PlanetCalculatorInterface;
use Sweph\DTO\CelestialPosition;
use Sweph\Enums\Planet;
use Sweph\Mapper\CelestialPositionMapper;

final readonly class PlanetService implements PlanetCalculatorInterface
{
    public function __construct(
        private NativeSwephInterface $native,
        private CelestialPositionMapper $mapper,
    ) {
    }

    public function calculateUt(float $julianDayUt, Planet $planet, int $flags = 0): CelestialPosition
    {
        return $this->mapper->map(
            $planet,
            $this->native->calcUt($julianDayUt, $planet->value, $flags),
        );
    }
}
