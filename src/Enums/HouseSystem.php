<?php

declare(strict_types=1);

namespace Sweph\Enums;

/**
 * Häusersystem-Codes für swe_houses*().
 */
enum HouseSystem: string
{
    case Placidus = 'P';
    case Koch = 'K';
    case Porphyry = 'O';
    case Regiomontanus = 'R';
    case Campanus = 'C';
    case EqualAscendant = 'A';
    case EqualAries = 'E';
    case VehlowEqual = 'V';
    case WholeSign = 'W';
    case AxialRotation = 'X';
    case Horizontal = 'H';
    case PolichPage = 'T';
    case Alcabitius = 'B';
    case GauquelinSectors = 'G';
    case Morinus = 'M';

    public function nativeCode(): string
    {
        return $this->value;
    }
}
