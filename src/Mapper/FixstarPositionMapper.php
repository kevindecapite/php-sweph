<?php

declare(strict_types=1);

namespace Sweph\Mapper;

use Sweph\DTO\FixstarPosition;
use Sweph\Exception\FixstarNotFoundException;
use Sweph\Exception\InvalidResponseException;

final class FixstarPositionMapper
{
    /** @param array<int|string, mixed> $native */
    public function map(array $native): FixstarPosition
    {
        $rc = (int) ($native['rc'] ?? -1);

        if ($rc < 0) {
            throw new FixstarNotFoundException((string) ($native['serr'] ?? 'Fixed star not found.'));
        }

        for ($i = 0; $i < 6; $i++) {
            if (!isset($native[$i]) || !\is_numeric($native[$i])) {
                throw new InvalidResponseException("Missing numeric fixed-star index {$i}.");
            }
        }

        return new FixstarPosition(
            name: (string) ($native['star'] ?? ''),
            longitude: (float) $native[0],
            latitude: (float) $native[1],
            distance: (float) $native[2],
            longitudeSpeed: (float) $native[3],
            latitudeSpeed: (float) $native[4],
            distanceSpeed: (float) $native[5],
            returnFlags: $rc,
        );
    }
}
