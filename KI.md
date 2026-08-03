# 🤖 KI-Briefing & Kontext-Leitfaden (`KI.md`)

Diese Datei dient als primärer Kontext-Einstieg für KI-Assistenten (LLMs wie ChatGPT, Claude, Gemini), um bei der Weiterentwicklung, dem Refactoring oder Bugfixing dieses Repositories sofort ohne Informationsverlust arbeiten zu können.

---

## 🎯 Projekt-Übersicht

* **Name**: `drt04-dev/php-swiss-ephemeris` (`Sweph`)
* **Zweck**: Ein moderner, objektorientierter, typsicherer und performanter PHP 8.4+ SDK-Wrapper für die C-Extension **Swiss Ephemeris** (`swephp`).
* **Zielgruppe**: Entwickler, die hochpräzise astronomische und astrologische Berechnungen in PHP 8.4+ / Symfony / Laravel ohne C-Extension-Boilerplate ausführen möchten.
* **Architektur-Motto**: Striktes OOP, Immutability, Type-Safety und Zero-Legacy-Code.

---

## 🛠️ Tech Stack & Konventionen

* **PHP-Version**: `>= 8.4` (strikte Nutzung von PHP 8.4 Features!)
* **Testing**: PHPUnit 11 (`tests/`)
* **Static Analysis**: PHPStan Level 8 (`src/`)
* **Namespace**: `Sweph\` (PSR-4)
* **C-Extension**: `ext-swephp` (geladen via `php_swephp.h` / `swephp.c`)

### Strikte PHP 8.4 Design-Regeln:
1. **Naming Conventions**: 
   * Enums nutzen **PascalCase** für Cases (z. B. `Planet::Sun`, `HouseSystem::Placidus`, `CalculationFlag::Speed`).
   * Backed Enums nutzen wo nötig native `int` oder `string` Values.
2. **Immutability & Visibility**:
   * DTOs sind `readonly` oder nutzen **Asymmetric Visibility** (`public private(set)`).
   * Keine Getter/Setter-Orgien für reine Daten-Eigenschaften.
3. **Property Hooks**:
   * Wo nützlich, Property Hooks für abgeleitete oder berechnete Properties verwenden.
4. **Service Architecture**:
   * `Sweph\Ephemeris` ist die zentrale Fassade (static methods), welche die Low-Level-Funktionen der C-Extension kapselt, UTC-Zeiten konvertiert und Exceptions wirft.
   * `EphemerisException` ist die Basis-Exception für alle C-Level-Fehler.

---

## 🐳 Docker Infrastructure (`docker-compose.yml`)

Für die lokale Entwicklung wird folgende Container-Konfiguration verwendet:

```yaml
services:
  app:
    build:
      context: .
      dockerfile: docker/Dockerfile
    volumes:
      - .:/app
    working_dir: /app
    tty: true                  # Hält die Standard-Eingabe offen
    stdin_open: true           # Erlaubt interaktive Shells
    command: tail -f /dev/null # Hält den Container unendlich im Hintergrund aktiv
📂 Ordnerstruktur & Verantwortung
Plaintext
├── bin/
│   └── download-ephe.sh       # Lädt .se1 Ephemeriden-Dateien nach /ephe
├── docker/
│   └── Dockerfile             # Alpine PHP 8.4 Dev-Environment inkl. swephp C-Build
├── ext/                       # C-Quellcode der C-Erweiterung (swephp)
├── src/                       # SDK Quellcode
│   ├── DTO/                   # CelestialPosition, HouseCalculation (unveränderlich)
│   ├── Enums/                 # Planet, HouseSystem, CalculationFlag, Aspect, Calendar, SiderealMode
│   ├── Service/               # AspectCalculator & Business-Logik
│   ├── Ephemeris.php          # Statischer Core-Service (C-Extension Wrapper)
│   └── EphemerisException.php # Domain-Exception
├── tests/                     # PHPUnit Tests
├── examples/                  # Lauffähige Beispiele
├── .github/workflows/tests.yml# CI/CD (Baut C-Extension & führt PHPUnit + PHPStan aus)
├── docker-compose.yml         # Lokale Docker-Entwicklungsumgebung
└── README.md                  # Öffentliche Dokumentation
💡 Schnell-Einstieg für die KI (Workflow Commands)
Sollte der User Fragen stellen oder Code-Änderungen anfordern, können folgende Befehle im Docker-Container ausgeführt / vorausgesetzt werden:

Bash
# Container bauen/starten
docker compose up -d --build

# Abhängigkeiten installieren
docker compose exec app composer install

# Tests ausführen
docker compose exec app ./vendor/bin/phpunit

# Statische Analyse ausführen
docker compose exec app ./vendor/bin/phpstan analyse src

# Ephemeriden laden
docker compose exec app ./bin/download-ephe.sh
📌 Aktueller Projektstatus
✅ C-Extension & Docker Setup: Vollständig. libswe.a kompiliert sauber gegen PHP 8.4.

✅ Core SDK: Ephemeris, CelestialPosition, HouseCalculation & Enums sind vollständig implementiert.

✅ Business Logic: AspectCalculator zur Aspekterkennung vorhanden.

✅ Qualitätssicherung: CI/CD (GitHub Actions), PHPUnit 11 Tests und PHPStan Level 8 eingerichtet.

✅ Dokumentation: README.md und KI.md inkl. Symfony 8.1 Integration und Docker-Guide fertiggestellt.

📋 Anweisung an die KI bei zukünftigen Prompts:
Behalte den PHP 8.4 Standard bei: Schreibe niemals PHP 7.x/8.0 Syntax. Nutze Match-Expressions, Named Arguments, Backed Enums und Property Hooks.

Prüfe Enum-Values: Achte darauf, dass Enum-Cases wie Planet::Sun (PascalCase) und nicht Planet::SUN verwendet werden.

C-Extension Kapselung: Gehe nie davon aus, dass der Endnutzer C-Funktionen direkt aufruft. Alles muss über Sweph\Ephemeris oder dedizierte Services laufen.