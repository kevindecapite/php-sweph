<?php

declare(strict_types=1);

namespace Sweph\ValueObject;

use Sweph\Exception\InvalidJulianDayException;

final readonly class JulianDate
{
    public function __construct(public float $value)
    {
        if (!\is_finite($value)) {
            throw new InvalidJulianDayException('Julian day must be finite.');
        }
    }
}
