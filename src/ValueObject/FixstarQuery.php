<?php

declare(strict_types=1);

namespace Sweph\ValueObject;

use InvalidArgumentException;

final readonly class FixstarQuery
{
    public string $value;

    public function __construct(string $value)
    {
        $value = \trim($value);

        if ($value === '') {
            throw new InvalidArgumentException('Fixed-star query must not be empty.');
        }

        $this->value = $value;
    }

    public function toNativeString(): string
    {
        return $this->value;
    }
}
