<?php

declare(strict_types=1);

namespace Sweph\Enums;

enum CalculationFlag: int
{
    // --- Ephemeriden-Quellen (Ephemeris Databases) ---
    case JplEphemeris = 1;         // SEFLG_JPLEPH (Nutzt die präziseste NASA-JPL-Datenbank)
    case SwissEphemeris = 2;       // SEFLG_SWIEPH (Nutzt die präzisen .se1-Dateien von Astrodienst)
    case Moshier = 4;              // SEFLG_MOSEPH (Analytische Formeln, ungenaues Fallback ohne Dateien)

    // --- Koordinatensysteme (Coordinate Systems) ---
    case Heliocentric = 8;         // SEFLG_HELIO (Heliozentrisch: Sonne im Zentrum statt Erde)
    case TruePositions = 16;       // SEFLG_TRUEPOS (Wahre statt scheinbare Positionen - d.h. ohne Lichtzeit)
    case Sidereal = 64;            // SEFLG_SIDEREAL (Siderischer Tierkreis statt tropischer - z.B. für indische Astrologie)
    case Equatorial = 2048;        // SEFLG_EQUATORIAL (Rektaszension & Deklination statt ekliptikaler Länge & Breite)
    case Topocentric = 32768;      // SEFLG_TOPO (Topozentrisch: Position bezogen auf Koordinaten des Beobachters auf der Erdoberfläche)

    // --- Geschwindigkeiten (Speeds) ---
    case Speed3 = 128;             // SEFLG_SPEED3 (Geschwindigkeit berechnet aus 3 Positionen - langsamer/ungenauer)
    case Speed = 256;              // SEFLG_SPEED (Präzise, analytische Geschwindigkeitsberechnung - Standard)

    // --- Physikalische / Optische Korrekturen (Physical Corrections) ---
    case NoGravitationalDeflection = 512; // SEFLG_NOGDEFL (Schaltet die gravitative Lichtablenkung durch die Sonne aus)
    case NoAbberation = 1024;      // SEFLG_NOABERR (Schaltet die stellare Aberration des Lichts aus)
    case NoNutation = 4096;        // SEFLG_NONUT (Nutzt die mittlere statt der wahren Ekliptik des Datums - d.h. ohne Nutation)

    // --- Spezial-Koordinaten & Kombinationen ---
    case Barycentric = 16384;      // SEFLG_BARYCENTRIC (Baryzentrische statt geozentrische Berechnungen)
    case CartesianXYZ = 65536;     // SEFLG_XYZ (Gibt kartesische XYZ-Koordinaten statt Kugelkoordinaten zurück)
    case Radians = 131072;         // SEFLG_RADIANS (Rückgabe in Bogenmaß statt in Grad)


    case TruePosition = 16;    // SEFLG_TRUEPOS
    case J2000 = 32;           // SEFLG_J2000
    case XYZ = 4096;           // SEFLG_XYZ

    /**
     * Kombiniert mehrere CalculationFlag-Instanzen zu einer Bitmaske.
     */
    public static function combine(self ...$flags): int
    {
        $mask = 0;
        foreach ($flags as $flag) {
            $mask |= $flag->value;
        }

        return $mask;
    }

    /**
     * Prüft, ob ein bestimmtes Flag in einer Bitmaske enthalten ist.
     */
    public function isSetIn(int $mask): bool
    {
        return ($mask & $this->value) === $this->value;
    }
}