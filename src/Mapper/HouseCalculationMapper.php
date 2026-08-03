<?php

declare(strict_types=1);

namespace Sweph\Mapper;

use Sweph\DTO\HouseCalculation;
use Sweph\Enums\HouseSystem;
use Sweph\Exception\CalculationException;
use Sweph\Exception\InvalidResponseException;

final class HouseCalculationMapper
{
    /** @param array<string, mixed> $native */
    public function map(HouseSystem $system, array $native): HouseCalculation
    {
        $rc = (int) ($native['rc'] ?? 0);

        if ($rc < 0) {
            throw new CalculationException((string) ($native['serr'] ?? 'House calculation failed.'));
        }

        $cusps = $native['cusps'] ?? null;
        $angles = $native['ascmc'] ?? null;

        if (!\is_array($cusps) || !\is_array($angles)) {
            throw new InvalidResponseException('House response does not contain cusps and ascmc arrays.');
        }

        return new HouseCalculation(
            system: $system,
            cusps: \array_values(\array_map('floatval', $cusps)),
            angles: \array_values(\array_map('floatval', $angles)),
            cuspSpeeds: isset($native['cusp_speed']) && \is_array($native['cusp_speed'])
                ? \array_values(\array_map('floatval', $native['cusp_speed']))
                : null,
            angleSpeeds: isset($native['ascmc_speed']) && \is_array($native['ascmc_speed'])
                ? \array_values(\array_map('floatval', $native['ascmc_speed']))
                : null,
            returnCode: $rc,
        );
    }
}
