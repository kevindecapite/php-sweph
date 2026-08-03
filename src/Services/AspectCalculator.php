<?php

declare(strict_types=1);

namespace Sweph\Services;

use Sweph\DTO\AspectResult;
use Sweph\DTO\CelestialPosition;
use Sweph\Enums\Aspect;

class AspectCalculator
{
    /**
     * Berechnet den Aspekt zwischen zwei CelestialPosition-DTOs.
     *
     * @param CelestialPosition $pos1 Position des ersten Planeten (z.B. schnellerer Planet)
     * @param CelestialPosition $pos2 Position des zweiten Planeten (z.B. langsamerer Planet)
     * @param float $maxOrb Maximal erlaubter Orbis (Abweichung) in Grad (Standard: 8.0°)
     * @return AspectResult|null Gibt das Ergebnis zurück oder null, falls kein Aspekt im Orbis liegt.
     */
    public static function calculate(
        CelestialPosition $pos1,
        CelestialPosition $pos2,
        float $maxOrb = 8.0
    ): ?AspectResult {
        $distance = self::calculateShortestDistance($pos1->longitude, $pos2->longitude);

        foreach (Aspect::cases() as $aspect) {
            $exactAngle = $aspect->angle();
            $orb = abs($distance - $exactAngle);

            if ($orb <= $maxOrb) {
                // Relativgeschwindigkeit ermitteln zur Bestimmung von exakt/zulaufend/ablaufend
                $relativeSpeed = $pos1->longitudeSpeed - $pos2->longitudeSpeed;
                $isApplying = self::checkIsApplying($pos1->longitude, $pos2->longitude, $exactAngle, $relativeSpeed);

                return new AspectResult(
                    aspect: $aspect,
                    exactAngle: $exactAngle,
                    actualDistance: $distance,
                    orb: round($orb, 4),
                    isApplying: $isApplying
                );
            }
        }

        return null; // Kein Aspekt innerhalb des Orbis gefunden
    }

    /**
     * Berechnet den kürzesten Winkelabstand auf dem 360-Grad-Kreis (Ergebnis immer zwischen 0° und 180°).
     */
    public static function calculateShortestDistance(float $long1, float $long2): float
    {
        $diff = abs($long1 - $long2) % 360.0;
        return $diff > 180.0 ? 360.0 - $diff : $diff;
    }

    /**
     * Prüft, ob der Aspekt zulaufend (applying) ist.
     */
    private static function checkIsApplying(
        float $long1,
        float $long2,
        float $targetAngle,
        float $relativeSpeed
    ): bool {
        if (abs($relativeSpeed) < 0.00001) {
            return false; // Keine signifikante Eigenbewegung
        }

        $currentDistance = self::calculateShortestDistance($long1, $long2);

        // Simuliere die Position in einer kleinen Zeiteinheit (z.B. 0.01 Tage)
        $futureLong1 = fmod($long1 + ($relativeSpeed * 0.01) + 360.0, 360.0);
        $futureDistance = self::calculateShortestDistance($futureLong1, $long2);

        $currentOrb = abs($currentDistance - $targetAngle);
        $futureOrb = abs($futureDistance - $targetAngle);

        // Wenn die Abweichung in der Zukunft kleiner wird, läuft der Aspekt zu!
        return $futureOrb < $currentOrb;
    }
}