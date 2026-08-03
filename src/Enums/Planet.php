<?php

declare(strict_types=1);

namespace Sweph\Enums;

/**
 * Repräsentiert die Himmelskörper und sensitiven Punkte der Swiss Ephemeris.
 */
enum Planet: int
{
    // Hauptplaneten & Lichter
    case Sun = 0;             // SE_SUN
    case Moon = 1;            // SE_MOON
    case Mercury = 2;         // SE_MERCURY
    case Venus = 3;           // SE_VENUS
    case Mars = 4;            // SE_MARS
    case Jupiter = 5;         // SE_JUPITER
    case Saturn = 6;          // SE_SATURN
    case Uranus = 7;          // SE_URANUS
    case Neptune = 8;         // SE_NEPTUNE
    case Pluto = 9;           // SE_PLUTO

    // Mondknoten & Apogäum / Lilith
    case MeanNode = 10;       // Mittlerer Mondknoten (SE_MEAN_NODE)
    case TrueNode = 11;       // Wahrer Mondknoten (SE_TRUE_NODE)
    case MeanApog = 12;       // Lilith / Mittleres Apogäum (SE_MEAN_APOG)
    case OscuApog = 13;       // Oszillierende Lilith (SE_OSCU_APOG)

    // Himmelskörper & Asteroiden
    case Earth = 14;          // Erde (SE_EARTH)
    case Chiron = 15;         // Chiron (SE_CHIRON)
    case Pholus = 16;         // Pholus (SE_PHOLUS)
    case Ceres = 17;          // Ceres (SE_CERES)
    case Pallas = 18;         // Pallas (SE_PALLAS)
    case Juno = 19;           // Juno (SE_JUNO)
    case Vesta = 20;          // Vesta (SE_VESTA)

    // Interpolierte Apsiden-Punkte (Natürliche Lilith & Priapus)
    case IntpApog = 21;       // Interpoliertes Apogäum / Natürliche Lilith (SE_INTP_APOG)
    case IntpPerg = 22;       // Interpoliertes Perigäum / Priapus (SE_INTP_PERG)

    /**
     * Prüft, ob der Körper ein Hauptplanet oder Licht (Sonne/Mond) ist.
     */
    public function isMainPlanet(): bool
    {
        return $this->value >= self::Sun->value && $this->value <= self::Pluto->value;
    }

    /**
     * Prüft, ob es sich um einen mathematisch berechneten Punkt/Apside handelt.
     */
    public function isCalculatedPoint(): bool
    {
        return match ($this) {
            self::MeanNode, self::TrueNode, self::MeanApog,
            self::OscuApog, self::IntpApog, self::IntpPerg => true,
            default => false,
        };
    }

    /**
     * Prüft, ob es sich um einen Kleinplaneten / Asteroiden handelt.
     */
    public function isAsteroid(): bool
    {
        return match ($this) {
            self::Chiron, self::Pholus, self::Ceres,
            self::Pallas, self::Juno, self::Vesta => true,
            default => false,
        };
    }
}