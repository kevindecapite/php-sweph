<?php

declare(strict_types=1);

namespace Sweph\Enums;

enum ZodiacSign: int
{
    case Aries = 0;
    case Taurus = 1;
    case Gemini = 2;
    case Cancer = 3;
    case Leo = 4;
    case Virgo = 5;
    case Libra = 6;
    case Scorpio = 7;
    case Sagittarius = 8;
    case Capricorn = 9;
    case Aquarius = 10;
    case Pisces = 11;

    public static function fromLongitude(float $longitude): self
    {
        $normalized = \fmod($longitude, 360.0);
        if ($normalized < 0.0) {
            $normalized += 360.0;
        }

        return self::from((int) \floor($normalized / 30.0));
    }
}
