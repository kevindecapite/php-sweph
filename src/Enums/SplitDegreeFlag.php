<?php

declare(strict_types=1);

namespace Sweph\Enums;

use Sweph\Traits\BitmaskTrait;

enum SplitDegreeFlag: int
{
    use BitmaskTrait;

    case RoundSeconds = 1;
    case RoundMinutes = 2;
    case RoundDegrees = 4;
    case Zodiacal = 8;
    case KeepSign = 16;
    case KeepDegree = 32;
    case Nakshatra = 1024;
}
