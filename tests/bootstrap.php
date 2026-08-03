<?php

declare(strict_types=1);

// 1. Composer Autoloader einbinden
$autoloader = __DIR__ . '/../vendor/autoload.php';

if (!file_exists($autoloader)) {
    echo "Composer Autoloader nicht gefunden! Bitte führe zuerst 'composer install' aus.\n";
    exit(1);
}

require_once $autoloader;

// 2. Standard-Zeitzone für konsistente Testergebnisse festlegen (UTC)
date_default_timezone_set('UTC');

// 3. Strikte Fehlerbehandlung aktivieren (PHP-Warnungen in Exceptions umwandeln)
error_reporting(E_ALL);
set_error_handler(function (int $severity, string $message, string $file, int $line): bool {
    if (!(error_reporting() & $severity)) {
        // Dieser Fehlercode ist nicht im aktuellen error_reporting enthalten
        return false;
    }
    throw new \ErrorException($message, 0, $severity, $file, $line);
});