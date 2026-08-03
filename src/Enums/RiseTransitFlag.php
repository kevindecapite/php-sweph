<?php

declare(strict_types=1);

namespace Sweph\Enums;

use Sweph\Traits\BitmaskTrait;

enum RiseTransitFlag: int
{
    use BitmaskTrait;

    case Rise = 1;
    case Set = 2;
    case MeridianTransit = 4;
    case InferiorTransit = 8;
    case GeocentricNoEclipticLatitude = 128;
    case DiscCenter = 256;
    case NoRefraction = 512;
    case CivilTwilight = 1024;
    case NauticalTwilight = 2048;
    case AstronomicalTwilight = 4096;
    case DiscBottom = 8192;
    case FixedDiscSize = 16384;
    case ForceSlowMethod = 32768;
}
