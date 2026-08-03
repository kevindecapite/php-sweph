<?php

declare(strict_types=1);

namespace Sweph\DTO;

use Sweph\Enums\HeliacalEventType;

final readonly class HeliacalEvent
{
    /**
     * @param list<float> $values
     */
    public function __construct(
        public string $objectName,
        public HeliacalEventType $type,
        public array $values,
    ) {
    }
}
