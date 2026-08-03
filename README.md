# PHP Swiss Ephemeris SDK (Modern OOP)

[![Run Tests](https://github.com/drt04-dev/PHP-Swiss-Ephemeris/actions/workflows/tests.yml/badge.svg)](https://github.com/drt04-dev/PHP-Swiss-Ephemeris/actions)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![PHP Version](https://img.shields.io/badge/PHP-%3E%3D%208.4-8892BF.svg)](https://php.net)

Ein moderner, objektorientierter PHP 8.4+ Wrapper für die Hochpräzisions-Berechnungen der **Swiss Ephemeris** (astronomische und astrologische Berechnungen). 

Dieses Paket wirft alten Ballast über Bord und nutzt konsequent Features wie **Backed Enums**, **Asymmetric Visibility** (`public private(set)`), **Property Hooks** und strikte Typisierung.

---

## 📋 Voraussetzungen

* **PHP 8.4** oder neuer
* Die C-Erweiterung **`swephp`** (im PHP-Core geladen als `ext-swephp`)
* Das Hilfsprogramm `curl` (zum Herunterladen der Ephemeriden-Dateien)

---

## 📦 Installation

Installiere das Paket direkt über Composer:

```bash
composer require drt04-dev/php-swiss-ephemeris
```

# 🚀 Quick Start (Verwendung)
```php
<?php

declare(strict_types=1);

use Sweph\Ephemeris;
use Sweph\Enums\Planet;
use Sweph\Enums\HouseSystem;
use Sweph\Enums\CalculationFlag;

// 1. Planetenposition berechnen (liefert ein unveränderliches DTO)
$date = new DateTimeImmutable('2026-07-15 12:00:00', new DateTimeZone('UTC'));
$position = Ephemeris::getPlanetPosition(Planet::Sun, $date, [CalculationFlag::Speed]);

echo "Sonnenposition: {$position->longitude}°\n";
echo "Tägliche Geschwindigkeit: {$position->longitudeSpeed}°/Tag\n";

if ($position->isRetrograde()) {
    echo "Die Sonne ist rückläufig.\n";
}

// 2. Häuser und Achsen berechnen (z.B. für Berlin)
$julianDay = Ephemeris::getJulianDay(2026, 7, 15, 12.0);
$houses = Ephemeris::calculateHouses($julianDay, 52.5200, 13.4050, HouseSystem::PLACIDUS);

echo "Aszendent: {$houses->ascendant}°\n";
echo "Medium Coeli (MC): {$houses->mc}°\n";
echo "Spitze Haus 1: {$houses->getCusp(1)}°\n";
```

# 🐳 C-Erweiterung & Lokale Entwicklung im Docker
Um die C-Erweiterung nicht manuell auf deinem lokalen System kompilieren zu müssen, steht eine fertige Docker-Umgebung zur Verfügung. Sie bringt PHP 8.4, die fertig einkompilierte Extension swephp und alle Werkzeuge mit.

1. Docker-Container starten
Öffne dein Terminal im Hauptverzeichnis des Projekts und führe aus:

```bash
docker compose up -d --build
```

2. Composer-Abhängigkeiten installieren
Da das Repository-Verzeichnis als Volume gespiegelt wird, installierst du PHPUnit und PHPStan direkt im Container:

```bash
docker compose exec app composer install
```

3. Ephemeriden-Dateien (.se1) herunterladen
Für hochpräzise Berechnungen müssen die Ephemeriden-Dateien im Ordner ephe/ liegen:

```bash
# Skript einmalig ausführbar machen
chmod +x bin/download-ephe.sh
# Download im Container anstoßen
docker compose exec app ./bin/download-ephe.sh
```

4. Tests & Static Analysis ausführen

```bash
# Automated Test Suite (PHPUnit 11)
docker compose exec app ./vendor/bin/phpunit
# Statische Code-Analyse (PHPStan)
docker compose exec app ./vendor/bin/phpstan analyse src
```

5. Beispiele im Terminal testen
Im Ordner examples/ findest du sofort ausführbare Demonstrationsskripte:

```bash
docker compose exec app php examples/01-planet-positions.php
docker compose exec app php examples/02-birth-chart.php
docker compose exec app php examples/03-retrogrades.php
```

# 📂 Repository-Struktur
Das Repository ist in die native C-Erweiterung (ext/) und den modernen PHP 8.4 OOP-Wrapper (src/) unterteilt:

```text
drt04-dev/php-swiss-ephemeris/
├── .github/
│   └── workflows/
│       └── tests.yml          # GitHub Action für automatisierte CI/CD-Tests
├── bin/
│   └── download-ephe.sh       # Hilfsskript zum automatischen Laden der .se1-Ephemeridendateien
├── docker/
│   └── Dockerfile             # Alpine PHP 8.4 Image inkl. swephp Extension
├── ext/                       # C-Quellcode der swephp-Erweiterung
│   ├── config.m4
│   ├── php_swephp.h
│   └── swephp.c
├── src/                       # Der moderne PHP 8.4+ OOP-Wrapper (Namespace: Sweph)
│   ├── DTO/                   # Unveränderliche Datenobjekte (public private(set))
│   │   ├── CelestialPosition.php
│   │   └── HouseCalculation.php
│   ├── Enums/                 # Typensichere Backed Enums
│   │   ├── Aspect.php
│   │   ├── Calendar.php
│   │   ├── CalculationFlag.php
│   │   ├── HouseSystem.php
│   │   ├── Planet.php
│   │   └── SiderealMode.php
│   ├── Service/               # Domänen-Services & Hilfsklassen
│   │   └── AspectCalculator.php
│   ├── Ephemeris.php          # Haupt-Service (Statische Kapselung der C-Extension)
│   └── EphemerisException.php # Exception für Ephemeriden- und Berechnungsfehler
├── tests/                     # Qualitätssicherung mit PHPUnit 11
│   └── EphemerisTest.php
├── examples/                  # Direkt lauffähige Praxisbeispiele
│   ├── 01-planet-positions.php
│   ├── 02-birth-chart.php
│   └── 03-retrogrades.php
├── composer.json              # Autoloading & Paketdefinition
├── docker-compose.yml         # Lokale Entwicklungsumgebung
├── LICENSE                    # MIT Lizenz
└── README.md                  # Dokumentation
```

# 🛠️ Integration in Symfony (8.1+)
Da Ephemeris als statischer Service konzipiert ist, lässt er sich nahtlos in moderne Symfony-Anwendungen einbinden.

1. Ephemeriden-Pfad beim Anwendungsstart setzen
Setze den Pfad zu deinen Ephemeriden-Dateien am besten im Bootstrap-Prozess (z. B. in der src/Kernel.php oder einem Listener):

```php
// src/Kernel.php
public function boot(): void
{
    parent::boot();
    
    // Pfad zum Ephemeriden-Verzeichnis setzen (z. B. %kernel.project_dir%/var/ephe)
    \Sweph\Ephemeris::setEphePath($this->getProjectDir() . '/var/ephe');
}
```

2. Nutzung im Controller
```php
<?php

declare(strict_types=1);

namespace App\Controller;

use DateTimeImmutable;
use Sweph\Enums\Planet;
use Sweph\Ephemeris;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\JsonResponse;
use Symfony\Component\Routing\Attribute\Route;

class AstrologyController extends AbstractController
{
    #[Route('/api/planet/{name}', name: 'app_planet_position', methods: ['GET'])]
    public function getPosition(string $name): JsonResponse
    {
        $planet = match (strtolower($name)) {
            'sun' => Planet::Sun,
            'moon' => Planet::Moon,
            'mars' => Planet::Mars,
            default => null,
        };

        if ($planet === null) {
            return $this->json(['error' => 'Planet nicht unterstützt'], 400);
        }

        $position = Ephemeris::getPlanetPosition($planet, new DateTimeImmutable('now'));

        return $this->json([
            'planet' => $planet->name,
            'longitude' => $position->longitude,
            'latitude' => $position->latitude,
            'is_retrograde' => $position->isRetrograde(),
        ]);
    }
}
```

3. CLI Command erstellen (Symfony Console)

```php
<?php

declare(strict_types=1);

namespace App\Command;

use DateTimeImmutable;
use Sweph\Enums\Planet;
use Sweph\Ephemeris;
use Symfony\Component\Console\Attribute\AsCommand;
use Symfony\Component\Console\Command\Command;
use Symfony\Component\Console\Input\InputInterface;
use Symfony\Component\Console\Output\OutputInterface;
use Symfony\Component\Console\Style\SymfonyStyle;

#[AsCommand(
    name: 'app:calculate-sun',
    description: 'Berechnet die aktuelle Position der Sonne.',
)]
class CalculateSunCommand extends Command
{
    protected function execute(InputInterface $input, OutputInterface$output): int
    {
        $io = new SymfonyStyle($input, $output);$position = Ephemeris::getPlanetPosition(Planet::Sun, new DateTimeImmutable('now'));
        
        $io->success(sprintf('Die Sonne steht aktuell auf \%.2f° im Tierkreis.',$position->longitude));
        
        return Command::SUCCESS;
    }
}
```

# 📄 Lizenz
Dieses Projekt ist unter der MIT-Lizenz lizenziert. Siehe LICENSE für Details.