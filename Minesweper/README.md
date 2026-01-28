# Minesweper Build Guide

Dieses Projekt unterstützt zwei Build-Umgebungen: **Lokal (macOS)** und **Docker (Linux)**. Beide können parallel verwendet werden.

## Build-Verzeichnisse

- `build-local/` - Für lokale macOS Builds
- `build-docker/` - Für Docker/Linux Builds

## Voraussetzungen

### Lokal (macOS)
- CMake 3.22 oder höher
- C++ Compiler (clang/clang++ - normalerweise mit Xcode Command Line Tools)
- ncurses Library (normalerweise bereits installiert)

**CMake installieren:**
```bash
brew install cmake
```

### Docker Container
- Docker Desktop
- VS Code/Cursor mit Dev Containers Extension

## Build-Anleitung

### Lokal auf macOS bauen

**Option 1: Mit CMake Preset (empfohlen)**
```bash
cd /Users/aarondroge/Desktop/Minesweper/Minesweper

# Konfigurieren
cmake --preset local

# Kompilieren
cmake --build build-local

# Ausführen
./build-local/Minesweper
```

**Option 2: Direkt mit CMake**
```bash
cd /Users/aarondroge/Desktop/Minesweper/Minesweper

# Konfigurieren und kompilieren
cmake -S . -B build-local
cmake --build build-local

# Ausführen
./build-local/Minesweper
```

**Option 3: Mit Make (nach CMake Konfiguration)**
```bash
cd /Users/aarondroge/Desktop/Minesweper/Minesweper/build-local
make
./Minesweper
```

### Im Docker Container bauen

**Voraussetzung:** Docker Container muss laufen (siehe unten)

**Option 1: Mit CMake Preset (empfohlen)**
```bash
# Im Container-Terminal (Cursor/VS Code)
cd /workspace/Minesweper

# Konfigurieren
cmake --preset docker

# Kompilieren
cmake --build build-docker

# Ausführen
./build-docker/Minesweper
```

**Option 2: Direkt mit CMake**
```bash
cd /workspace/Minesweper

# Konfigurieren und kompilieren
cmake -S . -B build-docker
cmake --build build-docker

# Ausführen
./build-docker/Minesweper
```

**Option 3: Mit Make (nach CMake Konfiguration)**
```bash
cd /workspace/Minesweper/build-docker
make
./Minesweper
```

## Docker Container starten

### In Cursor/VS Code:
1. Öffne das Projekt in Cursor/VS Code
2. Drücke `F1` (oder `Cmd+Shift+P`)
3. Wähle "Dev Containers: Reopen in Container"
4. Warte, bis der Container gebaut und gestartet ist
5. Öffne ein Terminal im Container (`Ctrl+`` oder `View` → `Terminal`)

### Manuell mit Docker:
```bash
cd /Users/aarondroge/Desktop/Minesweper
docker-compose -f .devcontainer/docker-compose.yml up -d minesweper-dev
docker-compose -f .devcontainer/docker-compose.yml exec minesweper-dev bash
```

## Build-Optionen

### Debug Build (Standard)
```bash
cmake --preset local -DCMAKE_BUILD_TYPE=Debug
cmake --build build-local
```

### Release Build
```bash
cmake --preset local -DCMAKE_BUILD_TYPE=Release
cmake --build build-local
```

### Clean Build (alles neu kompilieren)
```bash
# Lokal
rm -rf build-local/*
cmake --preset local
cmake --build build-local

# Docker
rm -rf build-docker/*
cmake --preset docker
cmake --build build-docker
```

## Verfügbare CMake Presets

- `local` - Lokaler macOS Build (build-local/)
- `docker` - Docker/Linux Build (build-docker/)
- `default` - Standard Build (build/)
- `arm64` - Apple Silicon spezifisch (nur macOS)
- `x86_64` - Intel Mac spezifisch (nur macOS)
- `universal` - Universal Binary (nur macOS)

## Troubleshooting

### CMake nicht gefunden
```bash
# macOS
brew install cmake

# Prüfen
cmake --version
```

### ncurses nicht gefunden
```bash
# macOS
brew install ncurses

# Prüfen
pkg-config --modversion ncurses
```

### Build-Verzeichnis Berechtigungen
```bash
# Verzeichnisse neu erstellen
rm -rf build-local build-docker
mkdir -p build-local build-docker
chmod 755 build-local build-docker
```

### Docker Container startet nicht
1. Prüfe, ob Docker Desktop läuft
2. Prüfe Docker Status: `docker ps`
3. Starte Docker Desktop manuell aus Applications

## Projektstruktur

```
Minesweper/
├── src/
│   ├── Game/          # Spiel-Logik
│   └── terminal/      # Terminal-UI
├── build/             # Altes Build-Verzeichnis
├── build-local/       # Lokale macOS Builds
├── build-docker/      # Docker/Linux Builds
├── CMakeLists.txt     # CMake Konfiguration
└── CMakePresets.json  # CMake Presets
```

## Weitere Informationen

- CMake Dokumentation: https://cmake.org/documentation/
- Docker Dokumentation: https://docs.docker.com/
- Dev Containers: https://containers.dev/
