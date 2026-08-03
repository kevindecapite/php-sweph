<?php

declare(strict_types=1);

namespace Sweph\Enums;

enum Calendar: int
{
    case Julian = 0;
    case Gregorian = 1;

    public function isGregorian(): bool
    {
        return $this === self::Gregorian;
    }

    public function isJulian(): bool
    {
        return $this === self::Julian;
    }
}
