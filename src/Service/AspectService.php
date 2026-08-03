<?php

declare(strict_types=1);

namespace Sweph\Service;

use Sweph\DTO\AspectResult;
use Sweph\Enums\Aspect;

final class AspectService
{
    public function calculate(
        float $longitude1,
        float $longitude2,
        Aspect $aspect,
        ?float $orb = null,
        ?float $relativeSpeed = null,
    ): ?AspectResult {
        $difference = \fmod(\abs($longitude1 - $longitude2), 360.0);
        if ($difference > 180.0) {
            $difference = 360.0 - $difference;
        }

        $deviation = \abs($difference - $aspect->angle());

        if (!$aspect->isWithinOrb($longitude1, $longitude2, $orb)) {
            return null;
        }

        return new AspectResult(
            aspect: $aspect,
            actualAngle: $difference,
            deviation: $deviation,
            applying: $relativeSpeed !== null && $relativeSpeed < 0.0,
        );
    }
}
