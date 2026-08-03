<?php

declare(strict_types=1);

namespace Sweph\Enums;

use Sweph\Traits\BitmaskTrait;

enum HeliacalFlag: int
{
    use BitmaskTrait;

    case LongSearch = 128;
    case HighPrecision = 256;
    case OpticalParameters = 512;
    case NoDetails = 1024;
    case SearchOnePeriod = 2048;
    case VisibilityLimitDark = 4096;
    case VisibilityLimitNoMoon = 8192;
}
