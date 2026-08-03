<?php

declare(strict_types=1);

namespace Sweph\DTO;

readonly class FixstarPosition
{
    public function __construct(
        public string $name,
        public float $longitude,
        public float $latitude,
        public float $distanceAu,
        public float $longitudeSpeed,
        public float $latitudeSpeed,
        public float $distanceSpeed,
        public float $magnitude
    ) {}
}