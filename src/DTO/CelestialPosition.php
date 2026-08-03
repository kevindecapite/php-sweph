<?php

declare(strict_types=1);

namespace Sweph\DTO;

/**
 * Repräsentiert die berechnete Position und Geschwindigkeit eines Himmelskörpers.
 */
class CelestialPosition
{
    /**
     * @param float $longitude Ekliptikale Länge (0° bis 360°, z.B. 0° Widder bis 359.9° Fische)
     * @param float $latitude Ekliptikale Breite (Abweichung von der Ekliptik nach Norden(+) oder Süden(-))
     * @param float $distance Entfernung zur Erde (oder zur Sonne bei heliozentrischer Berechnung) in Astronomischen Einheiten (AE)
     * @param float $longitudeSpeed Tägliche Bewegung in der Länge (Grad pro Tag). Negativ bedeutet Rückläufigkeit!
     * @param float $latitudeSpeed Tägliche Bewegung in der Breite (Grad pro Tag)
     * @param float $distanceSpeed Tägliche Änderung der Entfernung (AE pro Tag)
     */
    public function __construct(
        private(set) float $longitude,
        private(set) float $latitude,
        private(set) float $distance,
        private(set) float $longitudeSpeed,
        private(set) float $latitudeSpeed,
        private(set) float $distanceSpeed,
    ) {}

    /**
     * Hilfsmethode, um schnell zu prüfen, ob der Planet gerade rückläufig ist.
     */
    public function isRetrograde(): bool
    {
        return $this->longitudeSpeed < 0.0;
    }

    /**
     * Erstellt eine Instanz direkt aus dem rohen 6-Elemente-Array der C-Extension (swe_calc / swe_calc_ut).
     *
     * @param array<int, float> $data
     */
    public static function fromCArray(array $data): self
    {
        return new self(
            longitude: $data[0] ?? 0.0,
            latitude: $data[1] ?? 0.0,
            distance: $data[2] ?? 0.0,
            longitudeSpeed: $data[3] ?? 0.0,
            latitudeSpeed: $data[4] ?? 0.0,
            distanceSpeed: $data[5] ?? 0.0,
        );
    }
}