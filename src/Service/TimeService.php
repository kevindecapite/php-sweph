<?php

declare(strict_types=1);

namespace Sweph\Service;

use Sweph\Contracts\NativeSwephInterface;
use Sweph\Enums\Calendar;
use Sweph\ValueObject\JulianDate;

final readonly class TimeService
{
    public function __construct(private NativeSwephInterface $native)
    {
    }

    public function julianDay(
        int $year,
        int $month,
        int $day,
        float $decimalHour,
        Calendar $calendar = Calendar::Gregorian,
    ): JulianDate {
        return new JulianDate(
            $this->native->julday(
                $year,
                $month,
                $day,
                $decimalHour,
                $calendar->value,
            ),
        );
    }
}
