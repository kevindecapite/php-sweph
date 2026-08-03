<?php

declare(strict_types=1);

namespace Sweph\Native;

use Sweph\Contracts\NativeSwephInterface;
use Sweph\Exception\NativeExtensionException;

final class ExtensionSweph implements NativeSwephInterface
{
    public function __construct()
    {
        if (!\function_exists('swe_calc_ut')) {
            throw new NativeExtensionException(
                'The swephp extension is not loaded or swe_calc_ut() is unavailable.',
            );
        }
    }

    public function calcUt(float $julianDayUt, int $planet, int $flags): array
    {
        return \swe_calc_ut($julianDayUt, $planet, $flags);
    }

    public function fixstarUt(string $star, float $julianDayUt, int $flags): array
    {
        return \swe_fixstar_ut($star, $julianDayUt, $flags);
    }

    public function housesEx(
        float $julianDayUt,
        int $flags,
        float $latitude,
        float $longitude,
        string $system,
    ): array {
        return \swe_houses_ex($julianDayUt, $flags, $latitude, $longitude, $system);
    }

    public function julday(int $year, int $month, int $day, float $hour, int $calendar): float
    {
        return \swe_julday($year, $month, $day, $hour, $calendar);
    }

    public function setTopocentric(float $longitude, float $latitude, float $altitudeMeters): void
    {
        \swe_set_topo($longitude, $latitude, $altitudeMeters);
    }

    public function setEphemerisPath(?string $path): void
    {
        \swe_set_ephe_path($path);
    }

    public function close(): void
    {
        \swe_close();
    }
}
