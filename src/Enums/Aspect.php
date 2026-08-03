<?php

declare(strict_types=1);

namespace Sweph\Enums;

enum Aspect: int
{
    case Conjunction = 0;   // 0°
    case Sextile = 60;      // 60°
    case Square = 90;       // 90°
    case Trine = 120;       // 120°
    case Opposition = 180;  // 180°

    /**
     * Gibt den Winkel in Grad zurück.
     */
    public function angle(): float
    {
        return (float) $this->value;
    }

    /**
     * Gibt den Standard-Orbis (Toleranz) in Grad für den Aspekt zurück.
     */
    public function getDefaultOrbis(): float
    {
        return match ($this) {
            self::Conjunction, self::Opposition => 8.0,
            self::Square, self::Trine => 7.0,
            self::Sextile => 5.0,
        };
    }

    /**
     * Prüft, ob der Winkel zwischen zwei Positionen innerhalb des angegebenen Orbis für diesen Aspekt liegt.
     */
    public function isWithinOrb(float $longitude1, float $longitude2, ?float $customOrb = null): bool
    {
        $orb = $customOrb ?? $this->getDefaultOrbis();

        // Kürzesten Winkel auf dem 360°-Kreis berechnen
        $diff = \abs($longitude1 - $longitude2) % 360.0;
        if ($diff > 180.0) {
            $diff = 360.0 - $diff;
        }

        return \abs($diff - $this->value) <= $orb;
    }
}