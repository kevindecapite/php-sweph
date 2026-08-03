<?php

declare(strict_types=1);

namespace Sweph\DTO;

use Sweph\Enums\Planet;

final readonly class CelestialPosition
{
    public function __construct(
        public Planet $body,
        public float $longitude,
        public float $latitude,
        public float $distance,
        public float $longitudeSpeed,
        public float $latitudeSpeed,
        public float $distanceSpeed,
        public int $returnFlags,
    ) {
    }
}
