<?php

declare(strict_types=1);

namespace Sweph\Enums;

use Sweph\Traits\BitmaskTrait;

enum CalculationFlag: int
{
    use BitmaskTrait;

    case JplEphemeris = 1;
    case SwissEphemeris = 2;
    case MoshierEphemeris = 4;
    case Heliocentric = 8;
    case TruePosition = 16;
    case J2000 = 32;
    case NoNutation = 64;
    case Speed3 = 128;
    case Speed = 256;
    case NoGravitationalDeflection = 512;
    case NoAberration = 1024;
    case Equatorial = 2048;
    case CartesianXYZ = 4096;
    case Radians = 8192;
    case Barycentric = 16384;
    case Topocentric = 32768;
    case Sidereal = 65536;
    case Icrs = 131072;
    case JplHorizons = 262144;
    case JplHorizonsApprox = 524288;
    case CenterBody = 1048576;

    public const self DefaultEphemeris = self::SwissEphemeris;
    public const self DpsiDeps1980 = self::JplHorizons;
}
