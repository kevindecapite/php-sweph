<?php

declare(strict_types=1);

namespace Sweph\Contracts;

use Sweph\DTO\HouseCalculation;
use Sweph\Enums\HouseSystem;
use Sweph\ValueObject\GeographicPosition;

interface HouseCalculatorInterface
{
    public function calculate(
        float $julianDayUt,
        GeographicPosition $position,
        HouseSystem $system,
        int $flags = 0,
    ): HouseCalculation;
}
