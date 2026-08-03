<?php

declare(strict_types=1);

namespace Sweph\DTO;

final readonly class JulianDayResult
{
    public function __construct(
        public float $julianDayEt,
        public float $julianDayUt,
    ) {
    }
}
