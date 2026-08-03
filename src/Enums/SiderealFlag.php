<?php

declare(strict_types=1);

namespace Sweph\Enums;

use Sweph\Traits\BitmaskTrait;

enum SiderealFlag: int
{
    use BitmaskTrait;

    case EclipticOfT0 = 256;
    case SolarSystemPlane = 512;
    case UserDefinedT0IsUt = 1024;
    case EclipticOfDate = 2048;
    case NoPrecessionOffset = 4096;
    case OriginalPrecessionModel = 8192;
}
