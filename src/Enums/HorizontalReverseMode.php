<?php

declare(strict_types=1);

namespace Sweph\Enums;

enum HorizontalReverseMode: int
{
    case HorizontalToEcliptic = 0;
    case HorizontalToEquatorial = 1;
}
