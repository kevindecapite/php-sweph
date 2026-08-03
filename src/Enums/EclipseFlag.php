<?php

declare(strict_types=1);

namespace Sweph\Enums;

use Sweph\Traits\BitmaskTrait;

enum EclipseFlag: int
{
    use BitmaskTrait;

    case Central = 1;
    case NonCentral = 2;
    case Total = 4;
    case Annular = 8;
    case Partial = 16;
    case AnnularTotal = 32;
    case Penumbral = 64;
    case Visible = 128;
    case MaximumVisible = 256;
    case FirstContactVisible = 512;
    case SecondContactVisible = 1024;
    case ThirdContactVisible = 2048;
    case FourthContactVisible = 4096;
    case PenumbralBeginVisible = 8192;
    case PenumbralEndVisible = 16384;
    case OneTry = 32768;

    public const self Hybrid = self::AnnularTotal;
}
