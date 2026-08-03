<?php

declare(strict_types=1);

namespace Sweph\DTO;

final readonly class EclipseEvent
{
    /**
     * @param list<float> $times
     * @param list<float> $attributes
     */
    public function __construct(
        public int $typeFlags,
        public array $times,
        public array $attributes = [],
    ) {
    }
}
