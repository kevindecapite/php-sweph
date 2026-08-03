<?php

declare(strict_types=1);

namespace Sweph\Mapper;

use Sweph\DTO\CelestialPosition;
use Sweph\Enums\Planet;
use Sweph\Exception\CalculationException;
use Sweph\Exception\InvalidResponseException;

final class CelestialPositionMapper
{
    /** @param array<int|string, mixed> $native */
    public function map(Planet $body, array $native): CelestialPosition
    {
        $this->assertSuccess($native);

        for ($i = 0; $i < 6; $i++) {
            if (!isset($native[$i]) || !\is_numeric($native[$i])) {
                throw new InvalidResponseException("Missing numeric position index {$i}.");
            }
        }

        return new CelestialPosition(
            body: $body,
            longitude: (float) $native[0],
            latitude: (float) $native[1],
            distance: (float) $native[2],
            longitudeSpeed: (float) $native[3],
            latitudeSpeed: (float) $native[4],
            distanceSpeed: (float) $native[5],
            returnFlags: (int) ($native['rc'] ?? 0),
        );
    }

    /** @param array<int|string, mixed> $native */
    private function assertSuccess(array $native): void
    {
        $rc = (int) ($native['rc'] ?? 0);
        $error = \trim((string) ($native['serr'] ?? ''));

        if ($rc < 0) {
            throw new CalculationException($error !== '' ? $error : 'Swiss Ephemeris calculation failed.');
        }
    }
}
