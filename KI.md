# 🤖 KI-Briefing & Projektkontext (`KI.md`)

Diese Datei dient als primärer Einstiegspunkt für KI-Assistenten (ChatGPT, Claude, Gemini usw.), damit Änderungen am Repository konsistent mit der bestehenden Architektur umgesetzt werden können.

---

# Projekt

**Name**

`drt04-dev/php-swiss-ephemeris`

**Namespace**

```php
Sweph\
```

Dieses Repository besteht aus zwei Schichten:

1. **Native PHP-Erweiterung (`ext-swephp`)**
   - geschrieben in C
   - kapselt die Swiss Ephemeris (`libswe`)
   - stellt typsichere PHP-Funktionen bereit

2. **Modernes PHP SDK**
   - objektorientiert
   - vollständig typisiert
   - nutzt ausschließlich PHP 8.4+
   - kapselt die C-Erweiterung vollständig

Der Endanwender arbeitet ausschließlich mit dem SDK.

---

# Architektur

Die Architektur ist strikt serviceorientiert.

```
User
    │
    ▼
SwephFactory
    │
    ▼
Sweph
 ├── planets()
 ├── houses()
 ├── time()
 ├── fixstars()
 ├── aspects()
 └── system()
    │
    ▼
Native C Extension (ext-swephp)
    │
    ▼
Swiss Ephemeris (libswe)
```

Die C-Funktionen werden niemals direkt vom Anwender aufgerufen.

---

# Designprinzipien

Das Projekt verfolgt konsequent folgende Prinzipien.

## PHP

- PHP ≥ 8.4
- `declare(strict_types=1);`
- keine Legacy-Syntax
- keine Kompatibilität zu PHP 8.3 oder älter

## Typisierung

- Backed Enums
- readonly DTOs
- Value Objects
- Named Arguments
- Match Expressions

## Architektur

- kleine Services
- keine God-Class
- keine statischen Utility-Klassen
- Dependency Injection über `SwephFactory`

---

# Coding Style

## Klassen

PascalCase

```
Planet
HouseSystem
SwephFactory
PlanetService
```

---

## Methoden

camelCase

```
calculate()
calculateUt()
julianDay()
planetName()
```

---

## Enum Cases

Immer PascalCase.

Richtig

```php
Planet::Sun
Planet::Moon
HouseSystem::Placidus
CalculationFlag::Speed
Calendar::Gregorian
```

Falsch

```php
Planet::SUN
Planet::MOON
HouseSystem::PLACIDUS
```

---

# DTOs

DTOs sind immutable.

Getter werden nicht geschrieben.

Statt

```php
$position->getLongitude();
```

immer

```php
$position->longitude;
```

---

# Services

Jeder fachliche Bereich besitzt seinen eigenen Service.

Beispiele

```
PlanetService
HouseService
TimeService
AspectService
FixstarService
SystemService
```

Neue Funktionalität gehört grundsätzlich in den passenden Service.

---

# Factory

SDK-Instanzen werden ausschließlich über die Factory erzeugt.

```php
$config = new SwephConfig(
    ephemerisPath: __DIR__.'/ephe',
);

$sweph = SwephFactory::create($config);
```

Keine direkte Instanziierung interner Services.

---

# Docker

Die gesamte Entwicklungsumgebung basiert auf Docker.

Es wird niemals vorausgesetzt, dass lokal

- phpize
- autoconf
- gcc
- make

installiert sind.

Alles wird im Container gebaut.

Container starten

```bash
docker compose up -d --build
```

Shell öffnen

```bash
docker compose exec app sh
```

---

# Native Extension

Die Extension wird im Docker-Image kompiliert.

Build:

```
native/swisseph
        │
        ▼
libswe.a
        │
        ▼
ext/swephp
        │
        ▼
swephp.so
```

Nach erfolgreichem Build befindet sich die Extension unter

```
/dist/linux/php84/swephp.so
```

Sie dient als Release-Artefakt.

---

# Tests

Es existieren zwei Testarten.

```
tests/

    Unit/

    Integration/
```

## Unit

keine native Extension erforderlich

## Integration

benötigt

- ext-swephp
- libswe
- Ephemeriden

---

Tests

```bash
composer test
```

Unit

```bash
composer test:unit
```

Integration

```bash
composer test:integration
```

---

# Static Analysis

PHPStan

```bash
composer phpstan
```

---

# Composer

Installation

```bash
composer install
```

Plattform prüfen

```bash
composer check-platform-reqs
```

---

# Repository

```
bin/
docker/
ext/
native/
src/
tests/
examples/
ephe/
.github/
```

---

# src

```
Contracts/
DTO/
Enums/
Exceptions/
Factories/
Service/
ValueObject/

Sweph.php
SwephConfig.php
SwephFactory.php
```

---

# C-Extension

```
ext/

config.m4
config.w32

php_swephp.h
swephp.c
swephp_arginfo.h
```

---

# Native Swiss Ephemeris

```
native/
    swisseph/
```

Die Originalquellen dürfen nicht verändert werden, außer beim Update auf eine neue Swiss-Ephemeris-Version.

---

# Release

Nach jedem erfolgreichen Build wird automatisch erzeugt:

```
dist/

linux/

php84/

swephp.so
```

Diese Datei ist das veröffentlichte Linux-Binary.

---

# CI

GitHub Actions

führt aus:

- Docker Build
- Build der C-Extension
- PHPUnit
- PHPStan
- Composer Platform Checks

---

# Wichtige Regeln

Die KI soll niemals

- Legacy-PHP schreiben
- Getter für DTOs erzeugen
- statische Utility-Klassen einführen
- Enum Cases in Großbuchstaben verwenden
- C-Funktionen direkt im SDK aufrufen

Die KI soll bevorzugen

- Services
- Value Objects
- readonly DTOs
- Backed Enums
- Named Arguments
- kleine klar abgegrenzte Klassen

---

# Ziel des Projekts

Das Repository soll die modernste PHP-Implementierung der Swiss Ephemeris werden.

Die öffentliche API soll vollständig objektorientiert, typsicher und stabil sein, während die C-Extension vollständig im Hintergrund gekapselt bleibt.