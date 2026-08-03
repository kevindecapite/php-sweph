<?php

declare(strict_types=1);

namespace Sweph\Enums;

/**
 * Repräsentiert die Suchmodi für Fixstern-Abfragen in der Swiss Ephemeris.
 */
enum FixstarSearchMode: string
{
    /** Suche nach dem gebräuchlichen Namen oder Katalognamen (Standard) */
    case Name = 'name';

    /** Exakte Namenssuche ohne Case-Insensitivity-Fallback */
    case ExactName = 'exact_name';

    /** Suche über die Katalognummer (z. B. Nomina, Harvard, BSC, etc.) */
    case CatalogNumber = 'catalog_number';

    /**
     * Gibt an, ob der Suchmodus als C-String-Präfix/Flag für die C-Extension aufbereitet werden muss.
     */
    public function requiresCatalogPrefix(): bool
    {
        return $this === self::CatalogNumber;
    }
}