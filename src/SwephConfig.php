<?php

declare(strict_types=1);

namespace Sweph;

use Sweph\ValueObject\GeographicPosition;

final readonly class SwephConfig
{
    public function __construct(
        public ?string $ephemerisPath = null,
        public ?GeographicPosition $observer = null,
    ) {
    }
}
