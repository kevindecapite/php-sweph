<?php

declare(strict_types=1);

namespace Sweph\DTO;

use Sweph\Enums\HouseSystem;

final readonly class HouseCalculation
{
    /**
     * @param list<float> $cusps
     * @param list<float> $angles
     * @param list<float>|null $cuspSpeeds
     * @param list<float>|null $angleSpeeds
     */
    public function __construct(
        public HouseSystem $system,
        public array $cusps,
        public array $angles,
        public ?array $cuspSpeeds = null,
        public ?array $angleSpeeds = null,
        public int $returnCode = 0,
    ) {
    }
}
