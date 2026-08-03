FROM php:8.4-cli

# --------------------------------------------------------------------
# Systemabhängigkeiten
# --------------------------------------------------------------------

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        autoconf \
        build-essential \
        pkg-config \
        git \
        unzip \
        curl \
    && rm -rf /var/lib/apt/lists/*

# Composer aus dem offiziellen Composer-Image übernehmen
COPY --from=composer:2 \
    /usr/bin/composer \
    /usr/local/bin/composer

# --------------------------------------------------------------------
# Native Swiss-Ephemeris-Bibliothek bauen
# --------------------------------------------------------------------

WORKDIR /opt/swephp

COPY native/swisseph/ /opt/swephp/native/swisseph/

# Alte Build-Artefakte entfernen, ohne das fehlerhafte clean-Target
# des Swiss-Ephemeris-Makefiles aufzurufen.
RUN find /opt/swephp/native/swisseph \
        -maxdepth 1 \
        -type f \
        \( \
            -name '*.o' \
            -o -name 'libswe.a' \
            -o -name 'libswe.so' \
            -o -name 'swetest' \
        \) \
        -delete

# Statische Swiss-Ephemeris-Bibliothek mit -fPIC bauen,
# damit sie in das Shared Object swephp.so eingebunden werden kann.
RUN make \
        -C /opt/swephp/native/swisseph \
        CFLAGS="-O2 -fPIC" \
        libswe.a

# Sicherstellen, dass die Bibliothek tatsächlich erzeugt wurde.
RUN test -s /opt/swephp/native/swisseph/libswe.a \
    && ls -lh /opt/swephp/native/swisseph/libswe.a

# --------------------------------------------------------------------
# PHP-Extension bauen
# --------------------------------------------------------------------

COPY ext/ /opt/swephp/ext/

WORKDIR /opt/swephp/ext

RUN phpize --clean || true \
    && rm -rf \
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

RUN phpize

RUN ./configure \
    --enable-swephp=shared \
    --with-swisseph-src=/opt/swephp/native/swisseph

RUN make -j"$(nproc)" V=1

# Build-Artefakt finden — unabhängig davon, ob es unter modules/ oder .libs/ liegt
RUN echo "=== Erzeugte swephp-Artefakte ===" \
    && find /opt/swephp/ext \
        -type f \
        \( \
            -name 'swephp.so' \
            -o -name 'swephp.la' \
            -o -name 'swephp.lo' \
        \) \
        -print

# Shared Object direkt in das PHP-Extension-Verzeichnis installieren
RUN SWEPHP_SO="$(find /opt/swephp/ext \
        -type f \
        -name 'swephp.so' \
        -print \
        -quit)" \
    && EXTENSION_DIR="$(php-config --extension-dir)" \
    && test -n "${SWEPHP_SO}" \
    && echo "Installiere ${SWEPHP_SO}" \
    && echo "nach ${EXTENSION_DIR}/swephp.so" \
    && mkdir -p "${EXTENSION_DIR}" \
    && install -m 755 "${SWEPHP_SO}" "${EXTENSION_DIR}/swephp.so"

RUN docker-php-ext-enable swephp

RUN php --ri swephp \
    && php -r "echo swe_version(), PHP_EOL;"

# Installierte Extension als Release-Artefakt kopieren
RUN EXTENSION_DIR="$(php-config --extension-dir)" \
    && mkdir -p /dist/linux/php84 \
    && cp "${EXTENSION_DIR}/swephp.so" /dist/linux/php84/swephp.so \
    && ls -lh /dist/linux/php84/swephp.so

# Optional: Prüfsumme für Release-Downloads erzeugen
RUN cd /dist/linux/php84 \
    && sha256sum swephp.so > swephp.so.sha256 \
    && cat swephp.so.sha256

# --------------------------------------------------------------------
# PHP-Projekt
# --------------------------------------------------------------------

WORKDIR /app

# Composer-Dateien zuerst kopieren, damit Docker diesen Layer cachen kann.
COPY composer.json composer.lock* /app/

# Quellcode und Konfigurationsdateien kopieren
COPY src/ /app/src/
COPY tests/ /app/tests/
COPY examples/ /app/examples/

# Diese Dateien nur kopieren, wenn sie im Repository vorhanden sind.
# COPY phpunit.xml /app/phpunit.xml
# COPY phpstan.neon /app/phpstan.neon
# COPY README.md /app/README.md

# Composer kann ext-swephp jetzt erkennen, da die Extension bereits
# installiert und aktiviert wurde.
RUN composer install \
        --no-interaction \
        --prefer-dist \
        --optimize-autoloader

# Abschließende Prüfungen
RUN composer check-platform-reqs \
    && php --ri swephp \
    && php -r "echo 'Swiss Ephemeris: ', swe_version(), PHP_EOL;"

CMD ["tail", "-f", "/dev/null"]