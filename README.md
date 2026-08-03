# PHP Swiss Ephemeris

[![Tests](https://github.com/drt04-dev/PHP-Swiss-Ephemeris/actions/workflows/tests.yml/badge.svg)](https://github.com/drt04-dev/PHP-Swiss-Ephemeris/actions)
[![PHP](https://img.shields.io/badge/PHP-8.4%2B-8892BF.svg)](https://www.php.net/)
[![Swiss Ephemeris](https://img.shields.io/badge/Swiss%20Ephemeris-2.10.03-blue.svg)](https://www.astro.com/swisseph/)
[![License](https://img.shields.io/badge/SDK%20License-MIT-yellow.svg)](LICENSE)

A modern, strongly typed **PHP 8.4+ SDK** for the **Swiss Ephemeris**.

The project combines the performance of the native Swiss Ephemeris C library with a modern object-oriented PHP API based on services, immutable DTOs, backed enums, value objects, mappers and dedicated exceptions.

---

## Features

- PHP 8.4 or newer
- Native PHP extension `ext-swephp`
- Swiss Ephemeris 2.10.03
- Strict typing with `declare(strict_types=1)`
- Immutable `readonly` DTOs
- Native PHP backed enums
- Validated value objects
- Service-oriented architecture
- Dependency-injection friendly
- Composer and PSR-4 autoloading
- PHPUnit 11 test suites
- PHPStan static analysis
- Docker-based extension build
- Exportable Linux extension binary

---

## Architecture

```text
Application
    │
    ▼
SwephFactory
    │
    ▼
Sweph SDK façade
    │
    ├── PlanetService
    ├── HouseService
    ├── FixstarService
    ├── TimeService
    └── AspectService
    │
    ▼
Native adapter
    │
    ▼
PHP extension ext-swephp
    │
    ▼
Swiss Ephemeris C library
```

End users work with the object-oriented SDK. Direct calls to native `swe_*()` functions are normally not required.

---

## Requirements

- PHP 8.4+
- Composer 2
- `ext-swephp`
- A supported 64-bit Linux environment when using the provided Linux binary
- Swiss Ephemeris data files for high-precision Swiss Ephemeris calculations

The Moshier ephemeris does not require external ephemeris files, but it is less precise and considered deprecated by Swiss Ephemeris.

---

# Installation

## 1. Install `ext-swephp`

Composer requires the native extension:

```json
{
    "require": {
        "ext-swephp": "*"
    }
}
```

The extension must therefore be installed and enabled before running `composer install`.

### Install a prebuilt Linux binary

Download the binary matching your PHP environment from the project releases.

A binary must match at least:

- PHP major and minor version
- PHP API version
- Thread safety mode: NTS or ZTS
- CPU architecture
- Linux libc and distribution compatibility

Check your PHP environment:

```bash
php -v
php -i | grep -E "PHP API|Thread Safety|Architecture"
php-config --extension-dir
```

Copy the extension into the PHP extension directory:

```bash
sudo cp swephp.so "$(php-config --extension-dir)/swephp.so"
```

Create an INI file:

```bash
echo "extension=swephp.so" \
    | sudo tee /usr/local/etc/php/conf.d/99-swephp.ini
```

The exact INI directory depends on the PHP installation. Display all loaded configuration paths with:

```bash
php --ini
```

Verify the installation:

```bash
php --ri swephp
```

Expected output includes:

```text
swephp support => enabled
extension version => 2.0.0-php84
library (libswe.a) version => 2.10.03
```

You can also test the linked Swiss Ephemeris library directly:

```bash
php -r "echo swe_version(), PHP_EOL;"
```

---

## 2. Install the SDK with Composer

After `ext-swephp` is available:

```bash
composer require drt04-dev/php-swiss-ephemeris
```

Verify all platform requirements:

```bash
composer check-platform-reqs
```

---

# Quick Start

```php
<?php

declare(strict_types=1);

use Sweph\Enums\CalculationFlag;
use Sweph\Enums\Planet;
use Sweph\SwephConfig;
use Sweph\SwephFactory;

$config = new SwephConfig(
    ephemerisPath: __DIR__ . '/ephe',
);

$sweph = SwephFactory::create($config);

try {
    $position = $sweph->planets()->calculateUt(
        julianDayUt: 2461256.0,
        planet: Planet::Sun,
        flags: CalculationFlag::combine(
            CalculationFlag::SwissEphemeris,
            CalculationFlag::Speed,
        ),
    );

    printf(
        "Sun: %.6f°, speed: %+.6f°/day\n",
        $position->longitude,
        $position->longitudeSpeed,
    );
} finally {
    $sweph->close();
}
```

---

# Date and Julian Day Calculation

```php
<?php

declare(strict_types=1);

use Sweph\Enums\Calendar;
use Sweph\SwephFactory;

$sweph = SwephFactory::create();

try {
    $julianDay = $sweph->time()->julianDay(
        year: 2000,
        month: 1,
        day: 1,
        decimalHour: 12.0,
        calendar: Calendar::Gregorian,
    );

    echo $julianDay->value; // 2451545.0
} finally {
    $sweph->close();
}
```

---

# Planet Positions

```php
<?php

declare(strict_types=1);

use Sweph\Enums\CalculationFlag;
use Sweph\Enums\Planet;

$flags = CalculationFlag::combine(
    CalculationFlag::SwissEphemeris,
    CalculationFlag::Speed,
);

$position = $sweph->planets()->calculateUt(
    julianDayUt: 2461256.0,
    planet: Planet::Mars,
    flags: $flags,
);

echo $position->longitude;
echo $position->latitude;
echo $position->distance;
echo $position->longitudeSpeed;

if ($position->isRetrograde()) {
    echo 'Mars is retrograde.';
}
```

A planet is considered retrograde when its ecliptic longitude speed is negative.

---

# Topocentric Calculations

Topocentric calculations require observer coordinates and the `Topocentric` calculation flag.

```php
<?php

declare(strict_types=1);

use Sweph\Enums\CalculationFlag;
use Sweph\Enums\Planet;
use Sweph\SwephConfig;
use Sweph\SwephFactory;
use Sweph\ValueObject\GeographicPosition;

$observer = new GeographicPosition(
    longitude: 13.4050,
    latitude: 52.5200,
    altitudeMeters: 34.0,
);

$sweph = SwephFactory::create(
    new SwephConfig(
        ephemerisPath: __DIR__ . '/ephe',
        observer: $observer,
    ),
);

try {
    $position = $sweph->planets()->calculateUt(
        julianDayUt: 2461256.0,
        planet: Planet::Moon,
        flags: CalculationFlag::combine(
            CalculationFlag::SwissEphemeris,
            CalculationFlag::Speed,
            CalculationFlag::Topocentric,
        ),
    );
} finally {
    $sweph->close();
}
```

---

# House Calculation

```php
<?php

declare(strict_types=1);

use Sweph\Enums\HouseSystem;
use Sweph\ValueObject\GeographicPosition;

$location = new GeographicPosition(
    longitude: 13.4050,
    latitude: 52.5200,
    altitudeMeters: 34.0,
);

$houses = $sweph->houses()->calculate(
    julianDayUt: 2461256.0,
    position: $location,
    system: HouseSystem::Placidus,
);

for ($house = 1; $house <= 12; $house++) {
    if (!isset($houses->cusps[$house])) {
        continue;
    }

    printf(
        "House %d: %.6f°\n",
        $house,
        $houses->cusps[$house],
    );
}

$ascendant = $houses->angles[0] ?? null;
$mediumCoeli = $houses->angles[1] ?? null;
$armc = $houses->angles[2] ?? null;
$vertex = $houses->angles[3] ?? null;
```

The native Swiss Ephemeris house result usually contains an unused cusp entry at index `0`. House cusps are normally stored at indexes `1` through `12`.

---

# Fixed Stars

Fixed-star lookup is represented by a validated query value object rather than an artificial search-mode enum.

```php
<?php

declare(strict_types=1);

use Sweph\Enums\CalculationFlag;
use Sweph\ValueObject\FixstarQuery;

$star = $sweph->fixedStars()->calculateUt(
    query: new FixstarQuery('Spica'),
    julianDayUt: 2461256.0,
    flags: CalculationFlag::combine(
        CalculationFlag::SwissEphemeris,
        CalculationFlag::Speed,
    ),
);

echo $star->name;
echo $star->longitude;
echo $star->latitude;
```

---

# Aspect Calculation

Aspect calculations are implemented in the PHP domain layer and do not require a native Swiss Ephemeris call.

```php
<?php

declare(strict_types=1);

use Sweph\Enums\Aspect;

$result = $sweph->aspects()->calculate(
    longitude1: 10.0,
    longitude2: 129.5,
    aspect: Aspect::Trine,
    orb: 2.0,
);

if ($result !== null) {
    printf(
        "%s with %.6f° deviation\n",
        $result->aspect->name,
        $result->deviation,
    );
}
```

The aspect service returns `null` when the requested aspect is outside the allowed orb.

---

# Calculation Flags

Calculation flags are represented as integer-backed enums and combined into native bitmasks.

```php
use Sweph\Enums\CalculationFlag;

$flags = CalculationFlag::combine(
    CalculationFlag::SwissEphemeris,
    CalculationFlag::Speed,
    CalculationFlag::Equatorial,
);
```

Check whether a flag is present:

```php
$isSpeedEnabled = CalculationFlag::Speed->isSetIn($flags);
```

Resolve a mask back into enum cases:

```php
$enabledFlags = CalculationFlag::fromMask($flags);
```

Some combinations are technically representable as bitmasks but are not meaningful. For example, multiple ephemeris sources or conflicting calculation centres should not normally be combined.

---

# DTOs

Native arrays are converted into immutable DTOs.

Current DTOs include:

- `AspectResult`
- `CelestialPosition`
- `EclipseEvent`
- `FixstarPosition`
- `HeliacalEvent`
- `HouseCalculation`
- `JulianDayResult`
- `OrbitalElements`
- `SplitDegreeResult`
- `UtcDateTime`

DTO properties are accessed directly:

```php
$position->longitude;
$position->latitude;
$position->distance;
$position->longitudeSpeed;
```

---

# Enums

The SDK maps important Swiss Ephemeris constants to native PHP enums.

Current enums include:

- `Aspect`
- `Calendar`
- `CalculationFlag`
- `EclipseFlag`
- `EclipticCrossingType`
- `HeliacalEventType`
- `HeliacalFlag`
- `HorizontalCoordinateMode`
- `HorizontalReverseMode`
- `HouseSystem`
- `NodeFlag`
- `Planet`
- `RefractionMode`
- `RiseTransitFlag`
- `SiderealFlag`
- `SiderealMode`
- `SplitDegreeFlag`
- `ZodiacSign`

Enum cases use PascalCase:

```php
Planet::Sun;
HouseSystem::Placidus;
Calendar::Gregorian;
CalculationFlag::Speed;
```

---

# Value Objects

Validated input values are represented by dedicated value objects.

Current value objects include:

- `FixstarQuery`
- `GeographicPosition`
- `JulianDate`
- `Orb`

Example:

```php
$location = new GeographicPosition(
    longitude: 13.4050,
    latitude: 52.5200,
    altitudeMeters: 34.0,
);
```

Invalid coordinates throw an exception before a native calculation is attempted.

---

# Services

The public SDK façade provides access to specialized services:

```php
$sweph->planets();
$sweph->houses();
$sweph->fixedStars();
$sweph->time();
$sweph->aspects();
```

The services convert type-safe PHP arguments into native extension calls and map native responses back into immutable DTOs.

---

# Error Handling

The SDK uses a dedicated exception hierarchy:

```text
SwephException
├── CalculationException
├── FixstarNotFoundException
├── InvalidCoordinateException
├── InvalidJulianDayException
├── InvalidResponseException
├── NativeExtensionException
└── TopocentricConfigurationException
```

Example:

```php
<?php

declare(strict_types=1);

use Sweph\Exception\CalculationException;

try {
    $position = $sweph->planets()->calculateUt(
        julianDayUt: 2461256.0,
        planet: Planet::Mars,
        flags: $flags,
    );
} catch (CalculationException $exception) {
    echo $exception->getMessage();
}
```

---

# Ephemeris Data Files

High-precision Swiss Ephemeris calculations use external ephemeris files, commonly stored in an `ephe/` directory.

Configure the path when creating the SDK:

```php
$sweph = SwephFactory::create(
    new SwephConfig(
        ephemerisPath: __DIR__ . '/ephe',
    ),
);
```

Without an explicit path, the native library reports its compiled default search path, for example:

```text
.:/users/ephe2/:/users/ephe/
```

Applications should normally configure their own absolute ephemeris path.

---

# Docker Development

The repository contains a complete Docker environment that builds:

1. `libswe.a`
2. the PHP extension `swephp.so`
3. the PHP SDK dependencies

Build and start the environment:

```bash
docker compose up -d --build
```

Install Composer dependencies:

```bash
docker compose exec app composer install
```

Check the extension:

```bash
docker compose exec app php --ri swephp
```

Check Composer platform requirements:

```bash
docker compose exec app composer check-platform-reqs
```

Run all tests:

```bash
docker compose exec app composer test
```

Run Unit tests:

```bash
docker compose exec app composer test:unit
```

Run Integration tests:

```bash
docker compose exec app composer test:integration
```

Run PHPStan:

```bash
docker compose exec app composer phpstan
```

---

# Extension Build Artifact

The Docker build exports the installed Linux extension to:

```text
/dist/linux/php84/swephp.so
```

Check the artifact:

```bash
docker compose exec app sh -lc \
    'ls -lh /dist/linux/php84/'
```

Copy it to the host:

```bash
docker compose cp app:/dist ./dist
```

Under Git Bash on Windows, disable automatic path conversion:

```bash
MSYS_NO_PATHCONV=1 docker compose cp \
    app:/dist \
    ./dist
```

The exported `.so` is platform-specific. It should not be presented as a universal Linux binary.

---

# Repository Structure

```text
.
├── bin/
│   └── download-ephe.sh
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
│   ├── Contracts/
│   ├── DTO/
│   ├── Enums/
│   ├── Exception/
│   ├── Mapper/
│   ├── Native/
│   ├── Service/
│   ├── Traits/
│   ├── ValueObject/
│   ├── Sweph.php
│   ├── SwephConfig.php
│   └── SwephFactory.php
├── tests/
│   ├── Integration/
│   ├── Unit/
│   └── bootstrap.php
├── examples/
│   ├── 01-planet-positions.php
│   ├── 02-birth-chart.php
│   └── 03-retrogrades.php
├── composer.json
├── docker-compose.yml
├── phpunit.xml
├── README.md
└── KI.md
```

---

# Examples

The repository currently includes:

```text
examples/
├── 01-planet-positions.php
├── 02-birth-chart.php
└── 03-retrogrades.php
```

Run an example inside Docker:

```bash
docker compose exec app \
    php examples/01-planet-positions.php
```

```bash
docker compose exec app \
    php examples/02-birth-chart.php
```

```bash
docker compose exec app \
    php examples/03-retrogrades.php
```

---

# Testing

Run PHPUnit directly:

```bash
./vendor/bin/phpunit
```

Run a specific test suite:

```bash
./vendor/bin/phpunit --testsuite unit
```

```bash
./vendor/bin/phpunit --testsuite integration
```

Run PHPStan directly:

```bash
./vendor/bin/phpstan analyse src tests
```

---

# Native Extension Functions

The native extension currently exposes functions including:

- `swe_calc()`
- `swe_calc_ut()`
- `swe_calc_pctr()`
- `swe_solcross()`
- `swe_solcross_ut()`
- `swe_mooncross()`
- `swe_mooncross_ut()`
- `swe_fixstar()`
- `swe_fixstar2()`
- `swe_fixstar_ut()`
- `swe_fixstar2_ut()`
- `swe_fixstar_mag()`
- `swe_fixstar2_mag()`
- `swe_julday()`
- `swe_revjul()`
- `swe_utc_to_jd()`
- `swe_houses()`
- `swe_houses_ex()`
- `swe_houses_ex2()`
- `swe_set_topo()`
- `swe_set_ephe_path()`
- `swe_set_jpl_file()`
- `swe_get_planet_name()`
- `swe_degnorm()`
- `swe_radnorm()`
- `swe_split_deg()`
- `swe_day_of_week()`
- `swe_close()`
- `swe_version()`

Not every native function is necessarily exposed through a high-level SDK service yet. The object-oriented service layer is expanded incrementally while the native extension remains available as the lower-level integration layer.

---

# Why This SDK?

The native Swiss Ephemeris API returns procedural arrays and integer flags. This SDK adds:

- Type-safe method signatures
- PHP enums instead of magic integers
- Immutable DTOs instead of anonymous arrays
- Validated value objects
- Dedicated domain services
- Consistent exceptions
- Better IDE completion
- PHPStan support
- PHPUnit coverage
- Dependency-injection friendly architecture

---

# Contributing

Pull requests are welcome.

Before submitting a change, run:

```bash
composer check-platform-reqs
composer test
composer phpstan
```

New functionality should include:

- strict PHP 8.4 typing
- PHPUnit tests
- PHPStan-compatible code
- appropriate DTOs, enums or value objects
- documentation updates where required

Native Swiss Ephemeris source files under `native/swisseph/` should not be modified unless the bundled Swiss Ephemeris version is intentionally being updated.

---

# Security and Accuracy

Swiss Ephemeris is a specialist astronomical calculation library. Applications should:

- validate dates and geographic coordinates
- distinguish UT and ET/TT correctly
- use the correct calculation flags
- configure topocentric observer coordinates before topocentric calculations
- configure the siderial mode before siderial calculations
- use appropriate ephemeris files for the required date range and precision

The SDK improves type safety but does not replace an understanding of the underlying astronomical model.

---

# License

The PHP SDK code in this repository is distributed under the license stated in [`LICENSE`](LICENSE).

The bundled or linked **Swiss Ephemeris** library uses a separate dual-license model:

- GNU Affero General Public License
- Swiss Ephemeris Professional License

Before distributing software, a hosted service or binaries containing Swiss Ephemeris code, ensure that the chosen license model permits the intended use.

The MIT license of the PHP SDK does not replace or override the licensing requirements of Swiss Ephemeris.