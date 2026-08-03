<?php

declare(strict_types=1);

namespace Sweph\Enums;

enum RefractionMode: int
{
    case TrueToApparent = 0;
    case ApparentToTrue = 1;
}
