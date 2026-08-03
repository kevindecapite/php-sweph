<?php

declare(strict_types=1);

namespace Sweph\Traits;

/**
 * Gemeinsame Hilfsmethoden für Integer-Bitmask-Enums.
 *
 * @phpstan-require-implements \BackedEnum
 */
trait BitmaskTrait
{
    public static function combine(self ...$flags): int
    {
        $mask = 0;

        foreach ($flags as $flag) {
            $mask |= $flag->value;
        }

        return $mask;
    }

    /**
     * @return list<self>
     */
    public static function fromMask(int $mask): array
    {
        return \array_values(\array_filter(
            self::cases(),
            static fn (self $flag): bool => $flag->isSetIn($mask),
        ));
    }

    public function isSetIn(int $mask): bool
    {
        return ($mask & $this->value) === $this->value;
    }
}
