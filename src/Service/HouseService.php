<?php

declare(strict_types=1);

namespace Sweph\Service;

use Sweph\Contracts\HouseCalculatorInterface;
use Sweph\Contracts\NativeSwephInterface;
use Sweph\DTO\HouseCalculation;
use Sweph\Enums\HouseSystem;
use Sweph\Mapper\HouseCalculationMapper;
use Sweph\ValueObject\GeographicPosition;

final readonly class HouseService implements HouseCalculatorInterface
{
    public function __construct(
        private NativeSwephInterface $native,
        private HouseCalculationMapper $mapper,
    ) {
    }

    public function calculate(
        float $julianDayUt,
        GeographicPosition $position,
        HouseSystem $system,
        int $flags = 0,
    ): HouseCalculation {
        return $this->mapper->map(
            $system,
            $this->native->housesEx(
                $julianDayUt,
                $flags,
                $position->latitude,
                $position->longitude,
                $system->nativeCode(),
            ),
        );
    }
}
