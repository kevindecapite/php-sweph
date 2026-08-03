<?php

declare(strict_types=1);

namespace Sweph;

use Sweph\Contracts\NativeSwephInterface;
use Sweph\Service\AspectService;
use Sweph\Service\FixstarService;
use Sweph\Service\HouseService;
use Sweph\Service\PlanetService;
use Sweph\Service\TimeService;

final readonly class Sweph
{
    public function __construct(
        private NativeSwephInterface $native,
        private PlanetService $planetService,
        private FixstarService $fixstarService,
        private HouseService $houseService,
        private TimeService $timeService,
        private AspectService $aspectService,
    ) {
    }

    public function planets(): PlanetService
    {
        return $this->planetService;
    }

    public function fixedStars(): FixstarService
    {
        return $this->fixstarService;
    }

    public function houses(): HouseService
    {
        return $this->houseService;
    }

    public function time(): TimeService
    {
        return $this->timeService;
    }

    public function aspects(): AspectService
    {
        return $this->aspectService;
    }

    public function close(): void
    {
        $this->native->close();
    }
}
