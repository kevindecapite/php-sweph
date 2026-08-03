# PHP Swiss Ephemeris

[![Tests](https://github.com/drt04-dev/PHP-Swiss-Ephemeris/actions/workflows/tests.yml/badge.svg)](https://github.com/drt04-dev/PHP-Swiss-Ephemeris/actions)
[![PHP](https://img.shields.io/badge/PHP-8.4+-8892BF.svg)](https://php.net)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

A modern, strongly typed **PHP 8.4 SDK** for the **Swiss Ephemeris**.

The project combines the performance of the native Swiss Ephemeris C library with a modern, object-oriented PHP API based on immutable DTOs, enums, value objects and services.

---

# Features

- ✅ PHP 8.4+
- ✅ Strict Types
- ✅ Immutable DTOs
- ✅ Native PHP Enums
- ✅ Value Objects
- ✅ Dependency Injection ready
- ✅ Modern Service Layer
- ✅ Type-safe API
- ✅ Swiss Ephemeris compatible
- ✅ PHPUnit & PHPStan ready

---

# Requirements

- PHP 8.4+
- ext-swephp
- Composer
- Swiss Ephemeris data files (.se1) (optional when using Moshier)

---

# Installation

```bash
composer require drt04-dev/php-swiss-ephemeris
```

---

# Quick Start

```php
<?php

declare(strict_types=1);

use Sweph\SwephFactory;
use Sweph\SwephConfig;
use Sweph\Enums\Planet;
use Sweph\Enums\CalculationFlag;

$config = new SwephConfig(
    ephemerisPath: __DIR__.'/ephe',
);

$sweph = SwephFactory::create($config);

$position = $sweph
    ->planets()
    ->calculateUt(
        julianDayUt: 2461256.0,
        planet: Planet::Sun,
        flags: CalculationFlag::combine(
            CalculationFlag::SwissEphemeris,
            CalculationFlag::Speed,
        ),
    );

echo $position->longitude;
```

---

# Architecture

```
Swiss Ephemeris C Library
            │
            ▼
     PHP Extension (ext-swephp)
            │
            ▼
      Native Adapter Layer
            │
            ▼
           Mapper
            │
            ▼
       Immutable DTOs
            │
            ▼
      Service Layer API
```

---

# Project Structure

```
src/

├── Contracts/
├── DTO/
├── Enums/
├── Exception/
├── Mapper/
├── Native/
├── Service/
├── Traits/
├── ValueObject/
│
├── Sweph.php
├── SwephConfig.php
└── SwephFactory.php
```

---

# DTOs

The SDK returns immutable DTOs instead of arrays.

Included DTOs:

- AspectResult
- CelestialPosition
- EclipseEvent
- FixstarPosition
- HeliacalEvent
- HouseCalculation
- JulianDayResult
- OrbitalElements
- SplitDegreeResult
- UtcDateTime

Example:

```php
$position->longitude;
$position->latitude;
$position->distance;
$position->longitudeSpeed;
```

---

# Enums

Every important Swiss Ephemeris constant is represented by a PHP Enum.

Examples:

- Planet
- Calendar
- HouseSystem
- CalculationFlag
- SiderealMode
- SiderealFlag
- NodeFlag
- EclipseFlag
- RiseTransitFlag
- SplitDegreeFlag
- RefractionMode
- HeliacalEventType
- HeliacalFlag

Example:

```php
CalculationFlag::combine(
    CalculationFlag::SwissEphemeris,
    CalculationFlag::Speed,
    CalculationFlag::Equatorial,
);
```

---

# Value Objects

Instead of primitive values, the SDK uses dedicated value objects.

Available:

- GeographicPosition
- JulianDate
- Orb
- FixstarQuery

Example:

```php
$location = new GeographicPosition(
    longitude: 13.405,
    latitude: 52.520,
    altitudeMeters: 34.0,
);
```

---

# Services

The SDK exposes dedicated domain services.

```php
$sweph->planets();

$sweph->houses();

$sweph->fixedStars();

$sweph->time();

$sweph->aspects();
```

---

# Example: Houses

```php
use Sweph\Enums\HouseSystem;
use Sweph\ValueObject\GeographicPosition;

$houses = $sweph
    ->houses()
    ->calculate(
        julianDayUt: 2461256.0,
        position: new GeographicPosition(
            longitude: 13.405,
            latitude: 52.520,
        ),
        system: HouseSystem::Placidus,
    );
```

---

# Example: Aspects

```php
use Sweph\Enums\Aspect;

$result = $sweph
    ->aspects()
    ->calculate(
        10.0,
        129.5,
        Aspect::Trine,
    );

if ($result !== null) {
    echo $result->deviation;
}
```

---

# Error Handling

Dedicated exception hierarchy.

```
SwephException
├── NativeExtensionException
├── CalculationException
├── InvalidCoordinateException
├── InvalidJulianDayException
├── InvalidResponseException
├── FixstarNotFoundException
└── TopocentricConfigurationException
```

---

# Docker Development

Start the development environment.

```bash
docker compose up -d --build
```

Install dependencies.

```bash
docker compose exec app composer install
```

Run tests.

```bash
docker compose exec app composer test
```

Run static analysis.

```bash
docker compose exec app composer phpstan
```

---

# Examples

```
examples/

01-planets.php
02-houses.php
03-fixed-stars.php
04-aspects.php
05-eclipses.php
```

---

# Testing

Run PHPUnit.

```bash
vendor/bin/phpunit
```

Run PHPStan.

```bash
vendor/bin/phpstan analyse
```

---

# Supported Swiss Ephemeris Functions

The SDK currently wraps functions such as:

- swe_calc()
- swe_calc_ut()
- swe_fixstar()
- swe_fixstar_ut()
- swe_houses()
- swe_houses_ex()
- swe_julday()
- swe_revjul()
- swe_set_topo()
- swe_set_ephe_path()

and many more.

---

# Why this SDK?

Instead of returning loosely typed arrays like the native C API, this SDK provides:

- Immutable DTOs
- PHP Enums
- Dependency Injection
- Service Layer
- Value Objects
- Better IDE autocompletion
- Static analysis support
- Cleaner, more maintainable code

---

# Contributing

Pull requests are welcome.

Please ensure that:

- PHPUnit passes
- PHPStan passes
- Coding style is respected
- New features include tests

---

# License

This project is licensed under the terms described in the `LICENSE` file.

Please note that the **Swiss Ephemeris** itself is distributed under its own licensing terms. Ensure that your use of the underlying library complies with those terms.