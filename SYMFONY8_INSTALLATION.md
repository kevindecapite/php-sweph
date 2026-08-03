# Symfony-8-Integration mit eigener `swephp.so`

Diese Anleitung richtet sich an Anwender, die das Repository `drt04-dev/php-swiss-ephemeris` in ein Symfony-8-Projekt integrieren möchten.

Sie beschreibt den vollständigen Ablauf:

1. Repository herunterladen
2. native Swiss-Ephemeris-Bibliothek bauen
3. eigene PHP-Erweiterung `swephp.so` erzeugen
4. Erweiterung auf einem Linux-Server installieren
5. PHP-SDK per Composer laden
6. SDK als Symfony-Service konfigurieren
7. erste Berechnung in einem Controller ausführen

---

## Systemübersicht

Das Projekt besteht aus zwei voneinander abhängigen Schichten:

```text
Symfony-8-Anwendung
        │
        ▼
PHP Swiss Ephemeris SDK
        │
        ▼
PHP-Erweiterung ext-swephp
        │
        ▼
Swiss Ephemeris C Library
```

Composer installiert ausschließlich den objektorientierten PHP-Code. Die native Erweiterung `swephp.so` muss vorher gebaut, installiert und in PHP aktiviert werden.

---

## Voraussetzungen

Für den empfohlenen Docker-Build werden benötigt:

- Git
- Docker
- Docker Compose
- eine 64-Bit-Linux-Umgebung für den späteren Einsatz
- PHP 8.4 im Symfony-Projekt
- Composer 2
- Symfony 8

Auf dem Entwicklungsrechner müssen bei Verwendung von Docker weder `phpize` noch Compiler oder PHP-Header installiert sein.

Auf dem Zielserver müssen die erzeugte Erweiterung und die dort verwendete PHP-Version binär kompatibel sein.

---

# 1. Symfony-8-Projekt vorbereiten

Bei einem bestehenden Symfony-8-Projekt kann dieser Schritt übersprungen werden.

```bash
composer create-project symfony/skeleton:"8.0.*" my-symfony-app
cd my-symfony-app
composer require webapp
```

---

# 2. Repository herunterladen

```bash
git clone https://github.com/drt04-dev/PHP-Swiss-Ephemeris.git
cd PHP-Swiss-Ephemeris
```

Relevante Struktur:

```text
PHP-Swiss-Ephemeris/
├── docker/
│   └── Dockerfile
├── ext/
│   ├── config.m4
│   ├── config.w32
│   ├── php_swephp.h
│   ├── swephp.c
│   └── swephp_arginfo.h
├── native/
│   └── swisseph/
├── src/
├── tests/
├── examples/
├── composer.json
├── docker-compose.yml
└── README.md
```

---

# 3. Eigene `swephp.so` mit Docker bauen

```bash
docker compose down --remove-orphans

docker compose build \
    --no-cache \
    --progress=plain \
    app

docker compose up -d
```

Build prüfen:

```bash
docker compose exec app php --ri swephp
```

Erwartete Kerndaten:

```text
swephp support => enabled
extension version => 2.0.0-php84
library (libswe.a) version => 2.10.03
```

Swiss-Ephemeris-Version prüfen:

```bash
docker compose exec app php -r "echo swe_version(), PHP_EOL;"
```

Release-Artefakt prüfen:

```bash
docker compose exec app sh -lc 'ls -lh /dist/linux/php84/'
```

Prüfsumme erzeugen:

```bash
docker compose exec app sh -lc '
    cd /dist/linux/php84
    sha256sum swephp.so > swephp.so.sha256
    cat swephp.so.sha256
'
```

---

# 4. `swephp.so` auf den Host kopieren

```bash
mkdir -p dist/linux/php84

docker compose cp \
    app:/dist/linux/php84/. \
    ./dist/linux/php84/
```

Unter Git Bash auf Windows:

```bash
MSYS_NO_PATHCONV=1 docker compose cp \
    app:/dist/linux/php84/. \
    ./dist/linux/php84/
```

---

# 5. Binärkompatibilität prüfen

Die erzeugte `swephp.so` muss zur Zielumgebung passen:

- PHP 8.4
- PHP API `20240924`
- NTS oder ZTS
- CPU-Architektur
- libc
- Linux-Distribution beziehungsweise kompatible Laufzeitumgebung

Build-Umgebung prüfen:

```bash
docker compose exec app sh -lc '
    php -v
    php -i | grep -E "PHP API|Zend Extension Build|Thread Safety|Architecture"
    file /dist/linux/php84/swephp.so
    ldd /dist/linux/php84/swephp.so
'
```

Zielserver prüfen:

```bash
php -v
php -i | grep -E "PHP API|Zend Extension Build|Thread Safety|Architecture"
```

Für produktive Systeme sollte die Extension möglichst auf dem Zielserver oder in einer identischen Build-Umgebung erzeugt werden.

---

# 6. Erweiterung auf dem Linux-Server installieren

Dateien übertragen:

```bash
scp dist/linux/php84/swephp.so user@example-server:/tmp/swephp.so
scp dist/linux/php84/swephp.so.sha256 user@example-server:/tmp/swephp.so.sha256
```

Prüfsumme kontrollieren:

```bash
cd /tmp
sha256sum -c swephp.so.sha256
```

PHP-Extension-Verzeichnis ermitteln:

```bash
EXTENSION_DIR="$(php -r 'echo ini_get("extension_dir");')"
```

Erweiterung installieren:

```bash
sudo install -m 755 /tmp/swephp.so "${EXTENSION_DIR}/swephp.so"
ls -lh "${EXTENSION_DIR}/swephp.so"
```

---

# 7. PHP-Erweiterung aktivieren

PHP-Konfigurationspfade anzeigen:

```bash
php --ini
```

## Debian und Ubuntu

```bash
echo 'extension=swephp.so' \
    | sudo tee /etc/php/8.4/mods-available/swephp.ini

sudo phpenmod -v 8.4 swephp
sudo systemctl restart php8.4-fpm
```

Bei Apache:

```bash
sudo systemctl restart apache2
```

## Offizielles PHP-Docker-Image

```bash
cp swephp.so "$(php-config --extension-dir)/swephp.so"
docker-php-ext-enable swephp
```

## Andere Linux-Systeme

```ini
extension=swephp.so
```

Die INI-Datei muss in den von `php --ini` angezeigten Scan-Verzeichnissen liegen. Für PHP-FPM muss die Extension ebenfalls aktiviert und der FPM-Dienst neu gestartet werden.

---

# 8. Installation testen

```bash
php --ri swephp
php -r "echo swe_version(), PHP_EOL;"
php -m | grep swephp
composer show --platform | grep ext-swephp
```

---

# 9. SDK in das Symfony-Projekt laden

```bash
cd /path/to/my-symfony-app
composer require drt04-dev/php-swiss-ephemeris
```

Ist das Paket noch nicht über Packagist verfügbar:

```bash
composer repo add \
    sweph \
    vcs \
    https://github.com/drt04-dev/PHP-Swiss-Ephemeris.git

composer require drt04-dev/php-swiss-ephemeris:dev-main
```

Lokales Path-Repository:

```bash
mkdir -p packages

git clone \
    https://github.com/drt04-dev/PHP-Swiss-Ephemeris.git \
    packages/php-swiss-ephemeris
```

Symfony-`composer.json`:

```json
{
    "repositories": [
        {
            "type": "path",
            "url": "packages/php-swiss-ephemeris",
            "options": {
                "symlink": true
            }
        }
    ],
    "require": {
        "drt04-dev/php-swiss-ephemeris": "@dev"
    }
}
```

Anschließend:

```bash
composer update drt04-dev/php-swiss-ephemeris
```

---

# 10. Ephemeriden-Dateien einrichten

```bash
mkdir -p var/ephe
```

Beispielstruktur:

```text
my-symfony-app/
└── var/
    └── ephe/
        ├── sepl_18.se1
        ├── semo_18.se1
        └── ...
```

Berechtigungen:

```bash
sudo chown -R www-data:www-data var/ephe
sudo find var/ephe -type d -exec chmod 755 {} \;
sudo find var/ephe -type f -exec chmod 644 {} \;
```

---

# 11. SDK als Symfony-Service registrieren

`config/services.yaml`:

```yaml
parameters:
    sweph.ephemeris_path: '%kernel.project_dir%/var/ephe'

services:
    _defaults:
        autowire: true
        autoconfigure: true

    App\:
        resource: '../src/'

    Sweph\SwephConfig:
        arguments:
            $ephemerisPath: '%sweph.ephemeris_path%'

    Sweph\Sweph:
        factory:
            - 'Sweph\SwephFactory'
            - 'create'
        arguments:
            $config: '@Sweph\SwephConfig'
```

Prüfen:

```bash
php bin/console lint:container
php bin/console debug:container 'Sweph\Sweph'
php bin/console debug:autowiring Sweph
```

---

# 12. Erste Berechnung in einem Symfony-Controller

`src/Controller/EphemerisController.php`:

```php
<?php

declare(strict_types=1);

namespace App\Controller;

use DateTimeImmutable;
use DateTimeZone;
use Sweph\Enums\CalculationFlag;
use Sweph\Enums\Calendar;
use Sweph\Enums\Planet;
use Sweph\Sweph;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\JsonResponse;
use Symfony\Component\Routing\Attribute\Route;

final class EphemerisController extends AbstractController
{
    #[Route(
        '/api/ephemeris/sun',
        name: 'api_ephemeris_sun',
        methods: ['GET'],
    )]
    public function sun(Sweph $sweph): JsonResponse
    {
        $date = new DateTimeImmutable(
            'now',
            new DateTimeZone('UTC'),
        );

        $decimalHour = (int) $date->format('G')
            + ((int) $date->format('i') / 60)
            + ((int) $date->format('s') / 3600);

        $julianDay = $sweph->time()->julianDay(
            year: (int) $date->format('Y'),
            month: (int) $date->format('n'),
            day: (int) $date->format('j'),
            decimalHour: $decimalHour,
            calendar: Calendar::Gregorian,
        );

        $position = $sweph->planets()->calculateUt(
            julianDayUt: $julianDay->value,
            planet: Planet::Sun,
            flags: CalculationFlag::combine(
                CalculationFlag::SwissEphemeris,
                CalculationFlag::Speed,
            ),
        );

        return $this->json([
            'dateUtc' => $date->format(DATE_ATOM),
            'julianDayUt' => $julianDay->value,
            'body' => $position->body->name,
            'longitude' => $position->longitude,
            'latitude' => $position->latitude,
            'distanceAu' => $position->distance,
            'longitudeSpeed' => $position->longitudeSpeed,
            'retrograde' => $position->isRetrograde(),
            'returnFlags' => $position->returnFlags,
        ]);
    }
}
```

---

# 13. Route testen

```bash
symfony server:start
```

Aufrufen:

```text
/api/ephemeris/sun
```

---

# 14. Topozentrische Berechnungen konfigurieren

`config/services.yaml`:

```yaml
services:
    Sweph\ValueObject\GeographicPosition:
        arguments:
            $longitude: 13.4050
            $latitude: 52.5200
            $altitudeMeters: 34.0

    Sweph\SwephConfig:
        arguments:
            $ephemerisPath: '%sweph.ephemeris_path%'
            $observer: '@Sweph\ValueObject\GeographicPosition'

    Sweph\Sweph:
        factory:
            - 'Sweph\SwephFactory'
            - 'create'
        arguments:
            $config: '@Sweph\SwephConfig'
```

Berechnung:

```php
$position = $sweph->planets()->calculateUt(
    julianDayUt: $julianDay->value,
    planet: Planet::Moon,
    flags: CalculationFlag::combine(
        CalculationFlag::SwissEphemeris,
        CalculationFlag::Speed,
        CalculationFlag::Topocentric,
    ),
);
```

---

# 15. Produktionsdeployment

Prüfungen:

```bash
php --ri swephp
php -r "echo swe_version(), PHP_EOL;"
composer check-platform-reqs
php bin/console lint:container --env=prod
APP_ENV=prod APP_DEBUG=0 php bin/console cache:clear
APP_ENV=prod APP_DEBUG=0 php bin/console cache:warmup
sudo systemctl restart php8.4-fpm
```

---

# 16. Fehlerbehebung

## Composer findet `ext-swephp` nicht

```bash
php --ri swephp
which php
composer check-platform-reqs
```

## CLI funktioniert, Symfony aber nicht

Die Erweiterung ist wahrscheinlich nur für CLI, nicht für PHP-FPM aktiviert.

```bash
php --ini
php-fpm8.4 -i | grep swephp
sudo systemctl restart php8.4-fpm
```

## `undefined symbol`

Die Extension ist nicht zur Zielumgebung kompatibel. Neu bauen:

- auf dem Zielserver,
- im produktiven PHP-Image oder
- in einer identischen Build-Umgebung.

## `wrong ELF class`

```bash
uname -m
file swephp.so
```

## `Module compiled with module API=...`

```bash
php -i | grep 'PHP API'
```

## Ephemeriden-Dateien werden nicht gefunden

```yaml
parameters:
    sweph.ephemeris_path: '%kernel.project_dir%/var/ephe'
```

```bash
find var/ephe -maxdepth 1 -type f -name '*.se1' -ls
```

---

# 17. Aktualisierung

```bash
composer update drt04-dev/php-swiss-ephemeris
```

Wenn eine neue native Extension erforderlich ist, muss `swephp.so` ebenfalls neu gebaut und installiert werden.

---

# 18. Sicherheit und Lizenz

Die PHP-Erweiterung enthält beziehungsweise verlinkt Swiss-Ephemeris-Code. Die Swiss Ephemeris verwendet ein duales Lizenzmodell.

Vor der Verteilung einer Anwendung, eines gehosteten Dienstes oder einer kompilierten `swephp.so` muss geprüft werden, ob die AGPL-Bedingungen erfüllt werden oder eine kommerzielle Swiss-Ephemeris-Lizenz erforderlich ist.

Die Lizenz des PHP-SDKs ersetzt nicht die Lizenzbedingungen der Swiss Ephemeris.

---

# Kurzfassung

```bash
# Repository laden
git clone https://github.com/drt04-dev/PHP-Swiss-Ephemeris.git
cd PHP-Swiss-Ephemeris

# Extension bauen
docker compose build --no-cache --progress=plain app
docker compose up -d

# Build kontrollieren
docker compose exec app php --ri swephp

# Binary exportieren
mkdir -p dist/linux/php84
docker compose cp \
    app:/dist/linux/php84/swephp.so \
    ./dist/linux/php84/swephp.so

# Auf Zielserver installieren
EXTENSION_DIR="$(php -r 'echo ini_get("extension_dir");')"
sudo install -m 755 swephp.so "${EXTENSION_DIR}/swephp.so"

echo 'extension=swephp.so' \
    | sudo tee /etc/php/8.4/mods-available/swephp.ini

sudo phpenmod -v 8.4 swephp
sudo systemctl restart php8.4-fpm

# Extension prüfen
php --ri swephp

# Symfony SDK installieren
composer require drt04-dev/php-swiss-ephemeris

# Symfony prüfen
php bin/console lint:container
composer check-platform-reqs
```

Nach diesen Schritten steht die Swiss Ephemeris als native PHP-Erweiterung und als objektorientierter Symfony-Service zur Verfügung.
