<?php

declare(strict_types=1);

namespace Sweph\Enums;

/**
 * Kalendersysteme für die julianische Tagesberechnung.
 */
enum Calendar: int
{
    case Julian = 0;    // SE_JUL_CAL
    case Gregorian = 1; // SE_GREG_CAL

    /**
     * Gibt an, ob es sich um den gregorianischen Kalender handelt.
     */
    public function isGregorian(): bool
    {
        return $this === self::Gregorian;
    }

    /**
     * Gibt an, ob es sich um den julianischen Kalender handelt.
     */
    public function isJulian(): bool
    {
        return $this === self::Julian;
    }
}