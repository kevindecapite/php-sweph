<?php


declare(strict_types=1);

namespace Sweph\DTO;

use DateTimeImmutable;

readonly class HeliacalEvent
{
    public function __construct(
        public DateTimeImmutable  $startVisibility,
        public ?DateTimeImmutable $optimumVisibility,
        public ?DateTimeImmutable $endVisibility,
        public array              $phenomenonData = []
    )
    {
    }
}