<?php

declare(strict_types=1);

namespace Sweph\DTO;

final readonly class UtcDateTime
{
    public function __construct(
        public int $year,
        public int $month,
        public int $day,
        public int $hour,
        public int $minute,
        public float $second,
    ) {
    }
}
