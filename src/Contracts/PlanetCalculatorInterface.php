<?php

declare(strict_types=1);

namespace Sweph\Contracts;

use Sweph\DTO\CelestialPosition;
use Sweph\Enums\Planet;

interface PlanetCalculatorInterface
{
    public function calculateUt(float $julianDayUt, Planet $planet, int $flags = 0): CelestialPosition;
}
