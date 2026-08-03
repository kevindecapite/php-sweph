# Developer information
# Aktualisierung der C-Erweiterung für eine neue PHP-Version

Wenn die C-Erweiterung auf eine neue PHP-Version, beispielsweise PHP 8.4 oder neuer, portiert wird, müssen zunächst die Build-Dateien sowie der eigentliche Extension-Code aktualisiert werden.

Dazu gehören insbesondere:

- `php_swephp.h`
- `swephp.c`
- `swephp_arginfo.h`
- `config.m4`
- `config.w32`

Nach erfolgreicher Anpassung kann die Erweiterung vollständig innerhalb der Docker-Entwicklungsumgebung gebaut und getestet werden.

> **Hinweis:** Der Build erfolgt ausschließlich innerhalb von Docker. Auf dem Host-System werden weder `phpize` noch Compiler oder PHP-Entwicklungspakete benötigt.

---

# Projektstruktur

Die Build-Konfiguration geht von folgender Verzeichnisstruktur aus:

```text
project/
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
│       ├── swephexp.h
│       ├── sweodef.h
│       ├── sweph.c
│       ├── swephlib.c
│       ├── swedate.c
│       ├── swehouse.c
│       ├── Makefile
│       └── ...
├── src/
├── tests/
├── examples/
├── composer.json
└── docker-compose.yml
```

Während des Docker-Image-Builds werden die Dateien unter folgenden Pfaden verwendet:

```text
/opt/swephp/native/swisseph
/opt/swephp/ext
```

Im laufenden Entwicklungscontainer wird das Repository über Docker Compose nach `/app` eingebunden:

```text
/app/native/swisseph
/app/ext
```

Diese beiden Pfadgruppen dürfen nicht miteinander verwechselt werden:

- Dockerfile-Build: `/opt/swephp/...`
- laufender Container mit Volume: `/app/...`

---

# Docker-Image neu bauen

Nach Änderungen an der C-Erweiterung sollte das Docker-Image ohne Cache neu erstellt werden:

```bash
docker compose down --remove-orphans

docker compose build --no-cache --progress=plain app

docker compose up -d
```

Mit `--progress=plain` wird das vollständige Build-Log angezeigt. Das ist besonders wichtig, wenn `configure`, `make` oder das Linken der Extension fehlschlägt.

---

# Erweiterung im laufenden Container manuell kompilieren

Für Tests oder eine manuelle Fehleranalyse kann die Erweiterung im laufenden Container neu gebaut werden.

Container-Shell öffnen:

```bash
docker compose exec app sh
```

---

## 1. Swiss-Ephemeris-Bibliothek bauen

In das Verzeichnis der nativen Swiss-Ephemeris-Quellen wechseln:

```bash
cd /app/native/swisseph
```

Das originale `make clean` kann fehlschlagen, wenn beispielsweise das Verzeichnis `setest/` nicht mitkopiert wurde:

```text
cd: can't cd to setest
make: *** [Makefile:64: clean] Error 2
```

Deshalb sollten die relevanten Build-Artefakte direkt entfernt werden:

```bash
find . \
    -maxdepth 1 \
    -type f \
    \( \
        -name '*.o' \
        -o -name 'libswe.a' \
        -o -name 'libswe.so' \
        -o -name 'swetest' \
    \) \
    -delete
```

Nun wird die statische Swiss-Ephemeris-Bibliothek mit Position Independent Code gebaut:

```bash
make CFLAGS="-O2 -fPIC" libswe.a
```

Die Option `-fPIC` ist erforderlich, weil die statische Bibliothek später in das dynamische PHP-Modul `swephp.so` eingebunden wird.

Prüfen, ob die Bibliothek erfolgreich erstellt wurde:

```bash
test -s libswe.a

ls -lh libswe.a
```

Erwartet wird eine vorhandene, nicht leere Datei:

```text
libswe.a
```

---

## 2. PHP-Erweiterung vorbereiten

In das Extension-Verzeichnis wechseln:

```bash
cd /app/ext
```

Alte PHP-Build- und Autoconf-Artefakte entfernen:

```bash
phpize --clean || true

rm -rf \
    autom4te.cache \
    build \
    modules \
    .libs \
    Makefile \
    Makefile.fragments \
    Makefile.objects \
    config.h \
    config.h.in \
    config.log \
    config.nice \
    config.status \
    configure \
    libtool
```

Neue Build-Dateien erzeugen:

```bash
phpize
```

---

## 3. Extension konfigurieren

Die Extension muss mit dem Pfad zu den Swiss-Ephemeris-Quellen konfiguriert werden:

```bash
./configure \
    --enable-swephp=shared \
    --with-swisseph-src=/app/native/swisseph
```

Eine erfolgreiche Konfiguration sollte unter anderem Folgendes ausgeben:

```text
checking whether to enable the swephp extension... yes, shared
checking path to the Swiss Ephemeris source directory... /app/native/swisseph
```

Wird stattdessen Folgendes ausgegeben:

```text
Swiss Ephemeris source directory missing
```

wurde `./configure` ohne den erforderlichen Parameter aufgerufen.

Der korrekte Aufruf lautet:

```bash
./configure \
    --enable-swephp=shared \
    --with-swisseph-src=/app/native/swisseph
```

Nach erfolgreichem `configure` muss ein Makefile vorhanden sein:

```bash
test -f Makefile

grep -n '^PHP_MODULES' Makefile
```

---

## 4. Erweiterung kompilieren

```bash
make -j"$(nproc)" V=1
```

Anschließend alle erzeugten Extension-Artefakte suchen:

```bash
find /app/ext \
    -type f \
    \( \
        -name 'swephp.so' \
        -o -name 'swephp.la' \
        -o -name 'swephp.lo' \
        -o -name 'swephp.o' \
    \) \
    -print
```

Je nach Build-Konfiguration kann sich die fertige Datei beispielsweise hier befinden:

```text
/app/ext/modules/swephp.so
```

oder:

```text
/app/ext/.libs/swephp.so
```

Deshalb sollte nicht ausschließlich davon ausgegangen werden, dass die Datei unter `modules/swephp.so` liegt.

Die tatsächlich erzeugte Datei kann so ermittelt werden:

```bash
SWEPHP_SO="$(find /app/ext \
    -type f \
    -name 'swephp.so' \
    -print \
    -quit)"

test -n "${SWEPHP_SO}"

echo "Gefundene Extension: ${SWEPHP_SO}"

ls -lh "${SWEPHP_SO}"
```

---

# Extension installieren

In der aktuellen Build-Konfiguration kann `make install` mit folgendem Fehler abbrechen:

```text
Installing shared extensions:
/usr/local/lib/php/extensions/no-debug-non-zts-20240924/

cp: cannot stat 'modules/*': No such file or directory
make: *** [Makefile:87: install-modules] Error 1
```

Dieser Fehler bedeutet nicht zwingend, dass keine Extension gebaut wurde. Häufig liegt die fertige `swephp.so` lediglich an einem anderen Build-Pfad, beispielsweise unter `.libs/`.

Deshalb wird die Extension direkt in das von PHP gemeldete Extension-Verzeichnis installiert.

Zielverzeichnis ermitteln:

```bash
php-config --extension-dir
```

Extension direkt installieren:

```bash
SWEPHP_SO="$(find /app/ext \
    -type f \
    -name 'swephp.so' \
    -print \
    -quit)"

EXTENSION_DIR="$(php-config --extension-dir)"

test -n "${SWEPHP_SO}"

mkdir -p "${EXTENSION_DIR}"

install -m 755 \
    "${SWEPHP_SO}" \
    "${EXTENSION_DIR}/swephp.so"
```

Installation prüfen:

```bash
ls -lh "$(php-config --extension-dir)/swephp.so"
```

Danach die Extension dauerhaft aktivieren:

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

Eine erfolgreiche Ausgabe sieht beispielsweise so aus:

```text
swephp

swephp support => enabled
extension version => 2.0.0-php84
library (libswe.a) version => 2.10.03
default ephemeris file path => .:/users/ephe2/:/users/ephe/
```

Swiss-Ephemeris-Version direkt prüfen:

```bash
docker compose exec app php -r "echo swe_version(), PHP_EOL;"
```

PHP-Extension-Verzeichnis anzeigen:

```bash
docker compose exec app php-config --extension-dir
```

Installierte Datei prüfen:

```bash
docker compose exec app sh -lc \
    'ls -lh "$(php-config --extension-dir)/swephp.so"'
```

---

# Release-Artefakt erzeugen

Die installierte Extension wird zusätzlich nach `/dist` kopiert. Dieser Ordner dient als Quelle für spätere GitHub-Releases oder manuelle Installationspakete.

Im Container:

```bash
EXTENSION_DIR="$(php-config --extension-dir)"

mkdir -p /dist/linux/php84

cp \
    "${EXTENSION_DIR}/swephp.so" \
    /dist/linux/php84/swephp.so
```

Prüfen:

```bash
ls -lh /dist/linux/php84/swephp.so
```

Beispiel:

```text
-rwxr-xr-x 1 root root 831K Aug 3 14:21 swephp.so
```

Prüfsumme erzeugen:

```bash
cd /dist/linux/php84

sha256sum swephp.so > swephp.so.sha256

cat swephp.so.sha256
```

---

# Release-Artefakt auf den Host kopieren

Unter Linux, macOS oder PowerShell:

```bash
docker compose cp app:/dist ./dist
```

Unter Git Bash auf Windows kann die automatische Pfadumwandlung Probleme verursachen. Ein Containerpfad wie `/dist` kann dabei fälschlich in einen Windows-Pfad umgewandelt werden.

Deshalb unter Git Bash:

```bash
MSYS_NO_PATHCONV=1 docker compose cp \
    app:/dist \
    ./dist
```

Nur die Extension kopieren:

```bash
mkdir -p dist/linux/php84

MSYS_NO_PATHCONV=1 docker compose cp \
    app:/dist/linux/php84/swephp.so \
    ./dist/linux/php84/swephp.so
```

Lokale Datei prüfen:

```bash
ls -lh dist/linux/php84/swephp.so
```

---

# `/dist` unter Git Bash prüfen

Dieser Befehl kann unter Git Bash fehlschlagen:

```bash
docker compose exec app ls -lh /dist/linux/php84/
```

Git Bash wandelt `/dist/...` möglicherweise in einen Windows-Pfad wie diesen um:

```text
C:/Program Files/Git/dist/linux/php84/
```

Verwende deshalb:

```bash
docker compose exec app sh -lc \
    'ls -lh /dist/linux/php84/'
```

Alternativ:

```bash
MSYS_NO_PATHCONV=1 docker compose exec app \
    ls -lh /dist/linux/php84/
```

---

# Composer verwenden

Da das Projekt die PHP-Erweiterung voraussetzt:

```json
{
    "require": {
        "ext-swephp": "*"
    }
}
```

muss Composer in einer PHP-Umgebung ausgeführt werden, in der `swephp` geladen ist.

Innerhalb des Containers:

```bash
docker compose exec app composer install
```

Plattformanforderungen prüfen:

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

Alle Tests:

```bash
docker compose exec app composer test
```

Unit-Tests:

```bash
docker compose exec app composer test:unit
```

Integrationstests:

```bash
docker compose exec app composer test:integration
```

PHPStan:

```bash
docker compose exec app composer phpstan
```

Alternativ direkt:

```bash
docker compose exec app ./vendor/bin/phpstan analyse src tests
```

---

# Nach Änderungen an der Extension neu bauen

Nach Änderungen an einer der folgenden Dateien muss die Extension neu gebaut werden:

- `php_swephp.h`
- `swephp.c`
- `swephp_arginfo.h`
- `config.m4`
- `config.w32`

Das gilt ebenfalls bei Änderungen an den nativen Swiss-Ephemeris-Quellen.

Empfohlener Ablauf:

```bash
docker compose down --remove-orphans

docker compose build --no-cache --progress=plain app

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
docker compose exec app php -r \
    "echo swe_version(), PHP_EOL;"
```

Installierte Extension:

```bash
docker compose exec app sh -lc \
    'ls -lh "$(php-config --extension-dir)/swephp.so"'
```

Release-Artefakt:

```bash
docker compose exec app sh -lc \
    'ls -lh /dist/linux/php84/'
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

## `phpize: command not found`

`phpize` soll nicht auf dem Host ausgeführt werden.

Stattdessen:

```bash
docker compose exec app sh
```

Dann im Container:

```bash
cd /app/ext

phpize
```

---

## `Swiss Ephemeris source directory missing`

Die Extension wurde ohne den Parameter `--with-swisseph-src` konfiguriert.

Den tatsächlichen Pfad prüfen:

```bash
find /app /opt \
    -name swephexp.h \
    -type f \
    2>/dev/null
```

Im laufenden Container wird typischerweise ausgegeben:

```text
/app/native/swisseph/swephexp.h
```

Der korrekte Configure-Aufruf lautet dann:

```bash
./configure \
    --enable-swephp=shared \
    --with-swisseph-src=/app/native/swisseph
```

---

## `libswe.a not found`

Die statische Bibliothek wurde noch nicht gebaut.

```bash
cd /app/native/swisseph

find . \
    -maxdepth 1 \
    -type f \
    \( \
        -name '*.o' \
        -o -name 'libswe.a' \
        -o -name 'libswe.so' \
        -o -name 'swetest' \
    \) \
    -delete

make CFLAGS="-O2 -fPIC" libswe.a
```

---

## `make clean` scheitert wegen `setest`

Beispiel:

```text
cd setest && make clean
cd: can't cd to setest
```

Das `clean`-Target des originalen Makefiles erwartet ein Verzeichnis, das im Docker-Kontext nicht vorhanden ist.

Verwende deshalb kein `make clean`, sondern lösche die Artefakte direkt:

```bash
find . \
    -maxdepth 1 \
    -type f \
    \( \
        -name '*.o' \
        -o -name 'libswe.a' \
        -o -name 'libswe.so' \
        -o -name 'swetest' \
    \) \
    -delete
```

---

## Kein Makefile vorhanden

Beispiel:

```text
make: No targets specified and no makefile found
```

Dann ist `./configure` vorher fehlgeschlagen.

Zuerst erneut konfigurieren:

```bash
cd /app/ext

phpize --clean || true

phpize

./configure \
    --enable-swephp=shared \
    --with-swisseph-src=/app/native/swisseph
```

Erst wenn dieser Befehl erfolgreich war:

```bash
make -j"$(nproc)" V=1
```

---

## `modules/swephp.so` fehlt

Die fertige Extension kann sich auch unter einem anderen Build-Pfad befinden.

Nicht nur dies prüfen:

```bash
test -f modules/swephp.so
```

Sondern stattdessen suchen:

```bash
find /app/ext \
    -type f \
    -name 'swephp.so' \
    -print
```

---

## `make install` meldet `modules/*` fehlt

Beispiel:

```text
cp: cannot stat 'modules/*'
make: *** [Makefile:87: install-modules] Error 1
```

Dann die erzeugte Extension direkt installieren:

```bash
SWEPHP_SO="$(find /app/ext \
    -type f \
    -name 'swephp.so' \
    -print \
    -quit)"

EXTENSION_DIR="$(php-config --extension-dir)"

test -n "${SWEPHP_SO}"

install -m 755 \
    "${SWEPHP_SO}" \
    "${EXTENSION_DIR}/swephp.so"

docker-php-ext-enable swephp
```

---

# Vollständiger manueller Build-Ablauf

```bash
docker compose up -d --build

docker compose exec app sh
```

Im Container:

```bash
cd /app/native/swisseph

find . \
    -maxdepth 1 \
    -type f \
    \( \
        -name '*.o' \
        -o -name 'libswe.a' \
        -o -name 'libswe.so' \
        -o -name 'swetest' \
    \) \
    -delete

make CFLAGS="-O2 -fPIC" libswe.a

test -s libswe.a

cd /app/ext

phpize --clean || true

rm -rf \
    autom4te.cache \
    build \
    modules \
    .libs \
    Makefile \
    Makefile.fragments \
    Makefile.objects \
    config.h \
    config.h.in \
    config.log \
    config.nice \
    config.status \
    configure \
    libtool

phpize

./configure \
    --enable-swephp=shared \
    --with-swisseph-src=/app/native/swisseph

make -j"$(nproc)" V=1

SWEPHP_SO="$(find /app/ext \
    -type f \
    -name 'swephp.so' \
    -print \
    -quit)"

test -n "${SWEPHP_SO}"

EXTENSION_DIR="$(php-config --extension-dir)"

install -m 755 \
    "${SWEPHP_SO}" \
    "${EXTENSION_DIR}/swephp.so"

docker-php-ext-enable swephp

mkdir -p /dist/linux/php84

cp \
    "${EXTENSION_DIR}/swephp.so" \
    /dist/linux/php84/swephp.so

cd /dist/linux/php84

sha256sum swephp.so > swephp.so.sha256

exit
```

Container neu starten und prüfen:

```bash
docker compose restart app

docker compose exec app php --ri swephp

docker compose exec app php -r \
    "echo swe_version(), PHP_EOL;"

docker compose exec app composer install

docker compose exec app composer check-platform-reqs

docker compose exec app composer test

docker compose exec app composer phpstan
```

Wenn `php --ri swephp` die Extension als aktiviert meldet, `swe_version()` die Swiss-Ephemeris-Version zurückgibt und unter `/dist/linux/php84/swephp.so` ein Release-Artefakt vorhanden ist, wurde die Erweiterung erfolgreich gebaut, installiert und für die spätere Verteilung vorbereitet.