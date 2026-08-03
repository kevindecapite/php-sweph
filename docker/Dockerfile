FROM php:8.4-cli

# --------------------------------------------------------------------
# Systempakete
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

# Composer übernehmen
COPY --from=composer:2 /usr/bin/composer /usr/local/bin/composer

# --------------------------------------------------------------------
# Swiss Ephemeris Quellen
# --------------------------------------------------------------------

WORKDIR /opt/swephp

COPY native/swisseph/ /opt/swephp/native/swisseph/

# Alte Artefakte entfernen
RUN find /opt/swephp/native/swisseph \
        -maxdepth 1 \
        -type f \
        \( \
            -name "*.o" \
            -o -name "libswe.a" \
            -o -name "libswe.so" \
            -o -name "swetest" \
        \) \
        -delete

# libswe.a bauen
RUN make -C /opt/swephp/native/swisseph \
        CFLAGS="-O2 -fPIC" \
        libswe.a

RUN test -s /opt/swephp/native/swisseph/libswe.a

# --------------------------------------------------------------------
# PHP Extension
# --------------------------------------------------------------------

COPY ext/ /opt/swephp/ext/

WORKDIR /opt/swephp/ext

RUN phpize --clean || true

RUN phpize

RUN ./configure \
        --enable-swephp=shared \
        --with-swisseph-src=/opt/swephp/native/swisseph

# Kompilieren
RUN make -j"$(nproc)" V=1

# --------------------------------------------------------------------
# Diagnose
# --------------------------------------------------------------------

RUN echo "==============================" \
 && echo "Extension Build Output" \
 && echo "==============================" \
 && pwd \
 && find . -maxdepth 3 -type f | sort

RUN echo "==============================" \
 && echo "Shared Objects" \
 && echo "==============================" \
 && find . -name "*.so" -o -name "*.la" -o -name "*.lo"

# Prüfen ob die Extension erzeugt wurde
RUN test -f modules/swephp.so

# --------------------------------------------------------------------
# Installation
# --------------------------------------------------------------------

RUN make install

RUN docker-php-ext-enable swephp

RUN php --ri swephp

RUN php -r "echo swe_version(), PHP_EOL;"

# --------------------------------------------------------------------
# Release-Artefakte
# --------------------------------------------------------------------

RUN mkdir -p /dist/linux/php84

RUN cp modules/swephp.so /dist/linux/php84/swephp.so

RUN ls -lh /dist/linux/php84

# --------------------------------------------------------------------
# Anwendung
# --------------------------------------------------------------------

WORKDIR /app

COPY composer.json composer.lock* ./

RUN composer install \
    --no-interaction \
    --prefer-dist \
    --optimize-autoloader

COPY src/ ./src/
COPY tests/ ./tests/
COPY examples/ ./examples/
COPY README.md ./

CMD ["tail", "-f", "/dev/null"]