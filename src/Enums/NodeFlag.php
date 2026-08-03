<?php

declare(strict_types=1);

namespace Sweph\Enums;

use Sweph\Traits\BitmaskTrait;

enum NodeFlag: int
{
    use BitmaskTrait;

    case Mean = 1;
    case Osculating = 2;
    case OsculatingBarycentric = 4;
    case FocalPoint = 256;
}
