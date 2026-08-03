<?php

declare(strict_types=1);

namespace Sweph\Enums;

/**
 * Unterstützte Häusersysteme der Swiss Ephemeris.
 */
enum HouseSystem: string
{
    case Placidus = 'P';
    case Koch = 'K';
    case Porphyrius = 'O';
    case Regiomontanus = 'R';
    case Campanus = 'C';
    case Equal = 'E';         // Equal (Aszendent ist Spitze Haus 1)
    case Vehlow = 'V';        // Vehlow Equal (Aszendent in Mitte Haus 1)
    case WholeSign = 'W';     // Ganzzeichenhäuser (Whole Sign)
    case Meridian = 'X';      // Meridian-System (Axial)
    case Morinus = 'M';
    case Topocentric = 'T';   // Polich/Page

    /**
     * Gibt an, ob das Häusersystem geografische Breite benötigt
     * oder auch in polaren Breiten ohne Quadranten-Probleme funktioniert.
     */
    public function isPolarCapable(): bool
    {
        return match ($this) {
            self::Equal, self::Vehlow, self::WholeSign, self::Meridian, self::Morinus => true,
            default => false,
        };
    }
}