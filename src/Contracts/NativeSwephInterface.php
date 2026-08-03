<?php

declare(strict_types=1);

namespace Sweph\Contracts;

interface NativeSwephInterface
{
    /** @return array<int|string, mixed> */
    public function calcUt(float $julianDayUt, int $planet, int $flags): array;

    /** @return array<int|string, mixed> */
    public function fixstarUt(string $star, float $julianDayUt, int $flags): array;

    /** @return array<int|string, mixed> */
    public function housesEx(float $julianDayUt, int $flags, float $latitude, float $longitude, string $system): array;

    public function julday(int $year, int $month, int $day, float $hour, int $calendar): float;

    public function setTopocentric(float $longitude, float $latitude, float $altitudeMeters): void;

    public function setEphemerisPath(?string $path): void;

    public function close(): void;
}
