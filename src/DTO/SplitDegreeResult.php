<?php

declare(strict_types=1);

namespace Sweph\DTO;

final readonly class SplitDegreeResult
{
    public function __construct(
        public int $degree,
        public int $minute,
        public int $second,
        public float $secondFraction,
        public int $sign,
    ) {
    }
}
