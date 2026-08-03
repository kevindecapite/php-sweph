<?php

declare(strict_types=1);

namespace Sweph\Enums;

enum EclipticCrossingType: string
{
    case Ascending = 'ascending';
    case Descending = 'descending';

    public function invert(): self
    {
        return match ($this) {
            self::Ascending => self::Descending,
            self::Descending => self::Ascending,
        };
    }
}
