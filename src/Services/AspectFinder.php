<?php

declare(strict_types=1);

namespace Sweph\Services;

use Sweph\Enums\Aspect;

class AspectFinder
{
    /**
     * Prüft, ob zwischen zwei Längengraden ein bestimmter Aspekt liegt.
     */
    public static function getAspect(float $lon1, float $lon2): ?Aspect
    {
        // Winkel auf 0..360 Grad normieren
        $l1 = fmod(fmod($lon1, 360.0) + 360.0, 360.0);
        $l2 = fmod(fmod($lon2, 360.0) + 360.0, 360.0);

        // Kürzeste Distanz auf dem 360°-Kreis berechnen
        $diff = abs($l1 - $l2);
        $distance = $diff > 180.0 ? 360.0 - $diff : $diff;

        foreach (Aspect::cases() as $aspect) {
            $orbis = $aspect->getDefaultOrbis();
            if (abs($distance - $aspect->value) <= $orbis) {
                return $aspect;
            }
        }

        return null; // Kein Hauptaspekt gefunden
    }
}