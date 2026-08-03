<?php

declare(strict_types=1);

namespace Sweph\DTO;

use Sweph\Enums\Aspect;

final readonly class AspectResult
{
    public function __construct(
        public Aspect $aspect,
        public float $actualAngle,
        public float $deviation,
        public bool $applying,
    ) {
    }
}
