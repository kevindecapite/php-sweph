<?php

declare(strict_types=1);

namespace Sweph\Enums;

use InvalidArgumentException;

enum Aspect: int
{
    case Conjunction = 0;
    case Sextile = 60;
    case Square = 90;
    case Trine = 120;
    case Opposition = 180;

    public function angle(): float
    {
        return (float) $this->value;
    }

    public function defaultOrb(): float
    {
        return match ($this) {
            self::Conjunction, self::Opposition => 8.0,
            self::Square, self::Trine => 7.0,
            self::Sextile => 5.0,
        };
    }

    public function isWithinOrb(
        float $longitude1,
        float $longitude2,
        ?float $customOrb = null,
    ): bool {
        $orb = $customOrb ?? $this->defaultOrb();

        if (!\is_finite($longitude1) || !\is_finite($longitude2)) {
            throw new InvalidArgumentException('Longitudes must be finite.');
        }

        if (!\is_finite($orb) || $orb < 0.0) {
            throw new InvalidArgumentException('Orb must be finite and non-negative.');
        }

        $difference = \fmod(\abs($longitude1 - $longitude2), 360.0);

        if ($difference > 180.0) {
            $difference = 360.0 - $difference;
        }

        return \abs($difference - $this->angle()) <= $orb;
    }
}
