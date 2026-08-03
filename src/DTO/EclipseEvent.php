<?php


declare(strict_types=1);

namespace Sweph\DTO;

use DateTimeImmutable;

readonly class EclipseEvent
{
    public function __construct(
        public int                $returnCode,
        public DateTimeImmutable  $maximumTime,
        public ?DateTimeImmutable $firstContact,
        public ?DateTimeImmutable $secondContact,
        public ?DateTimeImmutable $thirdContact,
        public ?DateTimeImmutable $fourthContact,
        public array              $attributes = []
    )
    {
    }
}