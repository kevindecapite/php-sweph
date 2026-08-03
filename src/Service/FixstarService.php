<?php

declare(strict_types=1);

namespace Sweph\Service;

use Sweph\Contracts\NativeSwephInterface;
use Sweph\DTO\FixstarPosition;
use Sweph\Mapper\FixstarPositionMapper;
use Sweph\ValueObject\FixstarQuery;

final readonly class FixstarService
{
    public function __construct(
        private NativeSwephInterface $native,
        private FixstarPositionMapper $mapper,
    ) {
    }

    public function calculateUt(FixstarQuery $query, float $julianDayUt, int $flags = 0): FixstarPosition
    {
        return $this->mapper->map(
            $this->native->fixstarUt($query->toNativeString(), $julianDayUt, $flags),
        );
    }
}
