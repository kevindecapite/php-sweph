<?php

declare(strict_types=1);

namespace Sweph\DTO;

use InvalidArgumentException;
use OutOfRangeException;

/**
 * Repräsentiert das Ergebnis einer Häuserberechnung.
 */
class HouseCalculation
{
    /**
     * @param array<int, float> $cusps Die Spitzen der 12 Häuser (Keys 1 bis 12).
     * @param float $ascendant Der Aszendent (Schnittpunkt des Horizonts mit der Ekliptik im Osten)
     * @param float $mc Das Medium Coeli (Himmelsmitte)
     * @param float $armc Die Rektaszension des Medium Coeli (in Grad)
     * @param float $vertex Der Vertex (Schnittpunkt des Ersten Vertikals mit der Ekliptik im Westen)
     */
    public function __construct(
        public private(set) array $cusps,
        public private(set) float $ascendant,
        public private(set) float $mc,
        public private(set) float $armc,
        public private(set) float $vertex,
    ) {
        if (count($this->cusps) !== 12) {
            throw new InvalidArgumentException('Das Cusps-Array muss exakt 12 Einträge enthalten.');
        }
    }

    /**
     * Holt die Position einer bestimmten Häuserspitze (1 bis 12).
     */
    public function getCusp(int $houseNumber): float
    {
        if ($houseNumber < 1 || $houseNumber > 12) {
            throw new OutOfRangeException("Häusernummer muss zwischen 1 und 12 liegen, {$houseNumber} gegeben.");
        }

        return $this->cusps[$houseNumber] ?? throw new InvalidArgumentException("Häuserspitze für Haus {$houseNumber} nicht im Array vorhanden (Keys müssen 1..12 sein).");
    }

    /**
     * Erstellt eine Instanz aus den rohen C-Arrays (cusps und ascmc aus swe_houses).
     *
     * @param array<int, float> $rawCusps 1-basiertes oder 0-basiertes Array der Häuserspitzen
     * @param array<int, float> $rawAscmc  Array mit Hauptachsen (0: ASC, 1: MC, 2: ARMC, 3: Vertex)
     */
    public static function fromCArrays(array $rawCusps, array $rawAscmc): self
    {
        if (count($rawAscmc) < 4) {
            throw new InvalidArgumentException('Das ascmc-Array muss mindestens 4 Elemente enthalten.');
        }

        // Falls das C-Array 13 Elemente hat (0 ignoriert, 1..12 genutzt), schneiden wir Element 0 ab
        $cuspsValues = array_values($rawCusps);
        if (count($cuspsValues) === 13) {
            array_shift($cuspsValues);
        }

        if (count($cuspsValues) !== 12) {
            throw new InvalidArgumentException('Konnte keine 12 Häuserspitzen aus den C-Daten extrahieren.');
        }

        // Keys explizit auf 1..12 mappen
        $normalizedCusps = array_combine(range(1, 12), $cuspsValues);

        return new self(
            cusps: $normalizedCusps,
            ascendant: (float) $rawAscmc[0],
            mc: (float) $rawAscmc[1],
            armc: (float) $rawAscmc[2],
            vertex: (float) $rawAscmc[3],
        );
    }
}