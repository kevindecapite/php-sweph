<?php

declare(strict_types=1);

namespace Sweph\ValueObject;

use Sweph\Exception\InvalidCoordinateException;

final readonly class GeographicPosition
{
    public function __construct(
        public float $longitude,
        public float $latitude,
        public float $altitudeMeters = 0.0,
    ) {
        if (!\is_finite($longitude) || $longitude < -180.0 || $longitude > 180.0) {
            throw new InvalidCoordinateException('Longitude must be between -180 and 180 degrees.');
        }

        if (!\is_finite($latitude) || $latitude < -90.0 || $latitude > 90.0) {
            throw new InvalidCoordinateException('Latitude must be between -90 and 90 degrees.');
        }

        if (!\is_finite($altitudeMeters)) {
            throw new InvalidCoordinateException('Altitude must be finite.');
        }
    }

    /** @return array{0: float, 1: float, 2: float} */
    public function toNativeArray(): array
    {
        return [$this->longitude, $this->latitude, $this->altitudeMeters];
    }
}
