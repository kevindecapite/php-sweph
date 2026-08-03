<?php

declare(strict_types=1);

namespace Sweph\DTO;

use Sweph\Enums\Aspect;

/**
 * Ergebnis der Aspektberechnung zwischen zwei Punkten.
 */
class AspectResult
{
    /**
     * @param Aspect $aspect Der gefundene Aspekt
     * @param float $exactAngle Der Winkel des Aspekts (0°, 60°, 90°, etc.)
     * @param float $actualDistance Der tatsächliche Winkelabstand zwischen den zwei Punkten (0° - 180°)
     * @param float $orb Die aktuelle Abweichung vom exakten Winkel in Grad
     * @param bool $isApplying True, wenn sich die Körper aufeinander zubewegen (zulaufender Aspekt)
     */
    public function __construct(
        public private(set) Aspect $aspect,
        public private(set) float $exactAngle,
        public private(set) float $actualDistance,
        public private(set) float $orb,
        public private(set) bool $isApplying,
    ) {}
}