<?php

declare(strict_types=1);

namespace Sweph\Enums;

enum HeliacalEventType: int
{
    case MorningFirst = 1;  // Morning first appearance (all visible planets/stars)
    case EveningLast = 2;   // Evening last appearance (all visible planets/stars)
    case EveningFirst = 3;  // Evening first appearance (Mercury, Venus, Moon)
    case MorningLast = 4;   // Morning last appearance (Mercury, Venus, Moon)
}