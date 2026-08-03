<?php

declare(strict_types=1);

namespace Sweph\Enums;

enum SiderealMode: int
{
    case FaganBradley = 0;
    case Lahiri = 1;
    case DeLuce = 2;
    case Raman = 3;
    case Ushashashi = 4;
    case Krishnamurti = 5;
    case DjwhalKhul = 6;
    case Yukteshwar = 7;
    case JnBhasin = 8;
    case BabylonianKugler1 = 9;
    case BabylonianKugler2 = 10;
    case BabylonianKugler3 = 11;
    case BabylonianHuber = 12;
    case BabylonianEtpsc = 13;
    case Aldebaran15Taurus = 14;
    case Hipparchos = 15;
    case Sassanian = 16;
    case GalacticCenter0Sagittarius = 17;
    case J2000 = 18;
    case J1900 = 19;
    case B1950 = 20;
    case SuryaSiddhanta = 21;
    case SuryaSiddhantaMeanSun = 22;
    case Aryabhata = 23;
    case AryabhataMeanSun = 24;
    case SsRevati = 25;
    case SsCitra = 26;
    case TrueCitra = 27;
    case TrueRevati = 28;
    case TruePushya = 29;
    case GalacticCenterRgilbrand = 30;
    case GalacticEquatorIau1958 = 31;
    case GalacticEquatorTrue = 32;
    case GalacticEquatorMula = 33;
    case GalacticAlignmentMardyks = 34;
    case TrueMula = 35;
    case GalacticCenterMulaWilhelm = 36;
    case Aryabhata522 = 37;
    case BabylonianBritton = 38;
    case TrueSheoran = 39;
    case GalacticCenterCochrane = 40;
    case GalacticEquatorFiorenza = 41;
    case ValensMoon = 42;
    case Lahiri1940 = 43;
    case LahiriVp285 = 44;
    case KrishnamurtiVp291 = 45;
    case LahiriIcrc = 46;
    case UserDefined = 255;
}
