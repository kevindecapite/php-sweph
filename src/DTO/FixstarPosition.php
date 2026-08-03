<?php

declare(strict_types=1);

namespace Sweph\DTO;

final readonly class FixstarPosition
{
    public function __construct(
        public string $name,
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
