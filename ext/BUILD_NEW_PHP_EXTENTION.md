# Als Erstes updaten

Wenn die C Erweiterung fertig vorbereitet ist für eine neue PHP version also:

[php_swephp.h](php_swephp.h)
[swephp.c](swephp.c)
[swephp_arginfo.h](swephp_arginfo.h)
[config.m4](config.m4)
[config.w32](config.w32)

wurden angepasst dann sollten die nächsten schritte befolgt werden.

---


# 🚀 Letzter Schritt: Build & Test
Wenn der Header sowie die swephp.c auf dem neuesten Stand sind für PHP 8.4, kannst du das Modul direkt übersetzen:

```bash
# 1. Build-Artefakte aufräumen
phpize --clean


# 2. Umgebung für PHP 8.4 vorbereiten
phpize

# 3. Konfigurieren und Bauen
./configure
make
```

# 🧪 Schnelltest in PHP
Wenn make ohne Warnungen/Fehler durchläuft, kannst du das Modul direkt testen, ohne es zu installieren:

```bash
php -d extension=modules/swephp.so -r "var_dump(swe_version());"
# Wenn dir das die Version der Swiss Ephemeris ausgibt, ist deine PHP 8.4 Extension 100% einsatzbereit! Probiere den Build-Schritt gerne aus.
```