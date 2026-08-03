<?php

declare(strict_types=1);

namespace Sweph\Enums;

enum HorizontalCoordinateMode: int
{
    case EclipticToHorizontal = 0;
    case EquatorialToHorizontal = 1;
}
