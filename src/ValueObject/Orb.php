<?php

declare(strict_types=1);

namespace Sweph\ValueObject;

use InvalidArgumentException;

final readonly class Orb
{
    public function __construct(public float $degrees)
    {
        if (!\is_finite($degrees) || $degrees < 0.0 || $degrees > 180.0) {
            throw new InvalidArgumentException('Orb must be between 0 and 180 degrees.');
        }
    }
}
