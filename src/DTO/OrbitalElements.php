<?php

declare(strict_types=1);

namespace Sweph\DTO;

final readonly class OrbitalElements
{
    /**
     * @param list<float> $values Native Swiss-Ephemeris orbital-element array.
     */
    public function __construct(public array $values)
    {
    }
}
