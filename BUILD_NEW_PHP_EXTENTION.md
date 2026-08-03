# Aktualisierung der C-Erweiterung für eine neue PHP-Version

Wenn die C-Erweiterung auf eine neue PHP-Version (z. B. PHP 8.4 oder neuer) portiert wird, müssen zunächst die Build-Dateien sowie der eigentliche Extension-Code aktualisiert werden.

Dazu gehören insbesondere:

- `php_swephp.h`
- `swephp.c`
- `swephp_arginfo.h`
- `config.m4`
- `config.w32`

Nach erfolgreicher Anpassung kann die Erweiterung vollständig innerhalb der Docker-Entwicklungsumgebung gebaut und getestet werden.

> **Hinweis:** Der Build wird ausschließlich innerhalb von Docker durchgeführt. Auf dem Host-System werden weder `phpize` noch Compiler oder PHP-Entwicklungspakete benötigt.

---

# Projektstruktur

Die Build-Konfiguration geht von folgender Verzeichnisstruktur aus:

```text
project/
├── docker/
├── ext/
│   ├── config.m4
│   ├── config.w32
│   ├── php_swephp.h
│   ├── swephp.c
│   └── swephp_arginfo.h
├── native/
│   └── swisseph/
│       ├── swephexp.h
│       ├── libswe.a
│       ├── sweph.c
│       ├── swephlib.c
│       ├── swedate.c
│       ├── swehouse.c
│       └── ...
└── src/
```

Die nativen Swiss-Ephemeris-Quellen befinden sich im Verzeichnis:

```text
/app/native/swisseph
```

---

# Docker-Image neu bauen

Nach Änderungen an der C-Erweiterung sollte zunächst das Docker-Image neu erstellt werden.

```bash
docker compose down --remove-orphans

docker compose build --no-cache app

docker compose up -d
```

---

# Erweiterung im Container kompilieren

Verbinde dich anschließend mit dem Container:

```bash
docker compose exec app sh
```

---

## 1. Swiss Ephemeris Bibliothek neu bauen

Wechsle zunächst in das Verzeichnis der nativen Swiss-Ephemeris-Quellen.

```bash
cd /app/native/swisseph
```

Vorhandene Build-Artefakte entfernen:

```bash
make clean || true
```

Nun wird die statische Bibliothek mit Position Independent Code erstellt.

```bash
make CFLAGS="-O2 -fPIC" libswe.a
```

Prüfen, ob die Bibliothek erfolgreich erstellt wurde:

```bash
test -s libswe.a

ls -lh libswe.a
```

---

## 2. PHP-Erweiterung vorbereiten

Nun in das Extension-Verzeichnis wechseln:

```bash
cd /app/ext
```

Alte Build-Dateien entfernen:

```bash
phpize --clean || true
```

Neue Build-Dateien erzeugen:

```bash
phpize
```

---

## 3. Extension konfigurieren

Die Extension muss mit dem Pfad zu den Swiss-Ephemeris-Quellen konfiguriert werden.

```bash
./configure \
    --enable-swephp=shared \
    --with-swisseph-src=/app/native/swisseph
```

Wenn die Konfiguration erfolgreich war, sollte unter anderem folgende Ausgabe erscheinen:

```text
checking whether to enable the swephp extension... yes, shared
checking path to the Swiss Ephemeris source directory... /app/native/swisseph
```

---

## 4. Erweiterung kompilieren

```bash
make -j"$(nproc)" V=1
```

Vor der Installation sollte überprüft werden, ob das PHP-Modul tatsächlich erzeugt wurde.

```bash
test -f modules/swephp.so

ls -lh modules/swephp.so
```

Die Datei

```text
modules/swephp.so
```

muss vorhanden sein.

Falls sie **nicht** existiert, ist der Build fehlgeschlagen und `make install` darf **nicht** ausgeführt werden.

---

## 5. Erweiterung installieren

```bash
make install
```

Danach wird die Extension dauerhaft aktiviert.

```bash
docker-php-ext-enable swephp
```

Container verlassen:

```bash
exit
```

Container neu starten:

```bash
docker compose restart app
```

---

# Installation überprüfen

Prüfen, ob die Extension geladen wurde:

```bash
docker compose exec app php --ri swephp
```

Die Swiss-Ephemeris-Version prüfen:

```bash
docker compose exec app php -r "echo swe_version(), PHP_EOL;"
```

Wenn beide Befehle erfolgreich sind, wurde die Extension korrekt installiert.

---

# Composer verwenden

Da das Projekt die PHP-Erweiterung voraussetzt,

```json
  "ext-swephp": "*"
```

muss Composer innerhalb des Containers ausgeführt werden.

```bash
docker compose exec app composer install
```

Die Plattformanforderungen überprüfen:

```bash
docker compose exec app composer check-platform-reqs
```

Prüfen, ob Composer die Extension erkannt hat:

```bash
docker compose exec app composer show --platform
```

Die Ausgabe sollte unter anderem enthalten:

```text
ext-swephp
```

---

# Tests ausführen

PHPUnit:

```bash
docker compose exec app composer test
```

PHPStan:

```bash
docker compose exec app composer phpstan
```

---

# Nach Änderungen an der Extension neu bauen

Immer wenn Änderungen an einer der folgenden Dateien vorgenommen werden,

- `php_swephp.h`
- `swephp.c`
- `swephp_arginfo.h`
- `config.m4`
- `config.w32`

oder an den nativen Swiss-Ephemeris-Quellen, muss die Erweiterung vollständig neu gebaut werden.

Empfohlener Ablauf:

```bash
docker compose down --remove-orphans

docker compose build --no-cache app

docker compose up -d
```

Anschließend:

```bash
docker compose exec app php --ri swephp

docker compose exec app composer check-platform-reqs

docker compose exec app composer test

docker compose exec app composer phpstan
```

---

# Build überprüfen

PHP-Version:

```bash
docker compose exec app php -v
```

Extension:

```bash
docker compose exec app php --ri swephp
```

Swiss-Ephemeris-Version:

```bash
docker compose exec app php -r "echo swe_version(), PHP_EOL;"
```

Composer:

```bash
docker compose exec app composer check-platform-reqs
```

Tests:

```bash
docker compose exec app composer test
```

PHPStan:

```bash
docker compose exec app composer phpstan
```

---

# Fehlerbehebung

## `Swiss Ephemeris source directory missing`

Die Extension wurde ohne den Parameter

```bash
--with-swisseph-src=/app/native/swisseph
```

konfiguriert.

Den tatsächlichen Pfad der Quellen kann man prüfen:

```bash
find /app -name swephexp.h
```

Die Ausgabe sollte sein:

```text
/app/native/swisseph/swephexp.h
```

---

## `libswe.a not found`

Die native Bibliothek wurde noch nicht erstellt.

```bash
cd /app/native/swisseph

make clean || true

make CFLAGS="-O2 -fPIC" libswe.a
```

---

## `modules/swephp.so` fehlt

Wenn

```bash
make install
```

folgende Fehlermeldung erzeugt:

```text
cp: cannot stat 'modules/*'
```

wurde das Modul nicht erfolgreich gebaut.

Vor `make install` deshalb immer prüfen:

```bash
test -f modules/swephp.so
```

Existiert die Datei nicht, muss zuerst der Fehler beim `configure`- oder `make`-Schritt behoben werden.

---

# Vollständiger Build-Ablauf

```bash
docker compose down --remove-orphans

docker compose build --no-cache app

docker compose up -d

docker compose exec app sh

cd /app/native/swisseph

make clean || true

make CFLAGS="-O2 -fPIC" libswe.a

cd /app/ext

phpize --clean || true

phpize

./configure \
    --enable-swephp=shared \
    --with-swisseph-src=/app/native/swisseph

make -j"$(nproc)" V=1

test -f modules/swephp.so

make install

docker-php-ext-enable swephp

exit

docker compose restart app

docker compose exec app php --ri swephp

docker compose exec app php -r "echo swe_version(), PHP_EOL;"

docker compose exec app composer install

docker compose exec app composer test

docker compose exec app composer phpstan
```

Wenn `php --ri swephp` Informationen zur Erweiterung ausgibt und `swe_version()` erfolgreich die Version der Swiss Ephemeris zurückliefert, wurde die Erweiterung erfolgreich gebaut, installiert und steht sowohl PHP als auch Composer vollständig zur Verfügung.