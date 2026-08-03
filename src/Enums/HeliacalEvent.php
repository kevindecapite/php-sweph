<?php

declare(strict_types=1);

namespace Sweph\Enums;

/**
 * Ereignistypen für heliakalische Berechnungen.
 */
enum HeliacalEvent: int
{
    case HeliacalRising = 1;
    case HeliacalSetting = 2;
    case EveningFirst = 3;
    case MorningLast = 4;

    /** Laut Header noch nicht implementiert. */
    case AcronychalRising = 5;

    /** Laut Header noch nicht implementiert. */
    case AcronychalSetting = 6;

    public const self MorningFirst = self::HeliacalRising;
    public const self EveningLast = self::HeliacalSetting;
    public const self CosmicalSetting = self::AcronychalSetting;
}
