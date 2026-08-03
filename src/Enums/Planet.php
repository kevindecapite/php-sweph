<?php

declare(strict_types=1);

namespace Sweph\Enums;

enum Planet: int
{
    case EclipticAndNutation = -1;
    case FixedStar = -10;

    case Sun = 0;
    case Moon = 1;
    case Mercury = 2;
    case Venus = 3;
    case Mars = 4;
    case Jupiter = 5;
    case Saturn = 6;
    case Uranus = 7;
    case Neptune = 8;
    case Pluto = 9;
    case MeanNode = 10;
    case TrueNode = 11;
    case MeanApogee = 12;
    case OsculatingApogee = 13;
    case Earth = 14;
    case Chiron = 15;
    case Pholus = 16;
    case Ceres = 17;
    case Pallas = 18;
    case Juno = 19;
    case Vesta = 20;
    case InterpolatedApogee = 21;
    case InterpolatedPerigee = 22;

    case Cupido = 40;
    case Hades = 41;
    case Zeus = 42;
    case Kronos = 43;
    case Apollon = 44;
    case Admetos = 45;
    case Vulkanus = 46;
    case Poseidon = 47;
    case Isis = 48;
    case Nibiru = 49;
    case Harrington = 50;
    case NeptuneLeverrier = 51;
    case NeptuneAdams = 52;
    case PlutoLowell = 53;
    case PlutoPickering = 54;
    case Vulcan = 55;
    case WhiteMoon = 56;
    case Proserpina = 57;
    case Waldemath = 58;
}
