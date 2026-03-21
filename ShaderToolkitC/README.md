# ShaderToolkitC

C/C++ shader tooling library built with **CMake** and **vcpkg**.

## Prerequisites

- **CMake**
- A C/C++ compiler toolchain
- **vcpkg**
- (Linux) **Ninja** (the Linux script uses `-G Ninja`)

> Note: The build scripts currently set `VCPKG_ROOT` to a machine-specific path.
> You will likely need to edit `VCPKG_ROOT` inside the script for your setup.

---

## Build

All commands below assume you run them from the repository root.

### Linux

The Linux script configures CMake with Ninja and uses the vcpkg toolchain.

#### Debug (default)

```
./scripts/build_linux.sh
```

Build output: `cmake-build-debug/`

#### Release

```
./scripts/build_linux.sh release`
```
Build output: `cmake-build-release/`

**What it does (high level):**
- Configures CMake in `cmake-build-<type>/`
- Sets `CMAKE_BUILD_TYPE`
- Enables `compile_commands.json`
- Uses vcpkg toolchain file: `$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake`
- Builds the configured directory
---

### macOS

The macOS script installs dependencies with vcpkg and generates an Xcode project.

```
./scripts/build_macos.sh
```


Build output: `cmake-build-debug-macos-xcode/`

Notes:
- Uses generator: **Xcode**
- Uses `-DVCPKG_TARGET_TRIPLET=arm64-osx`
- Uses vcpkg manifest mode (`-DVCPKG_MANIFEST_MODE=ON`)

---

### Windows (PowerShell)

The Windows script installs dependencies with vcpkg and configures CMake.

```powershell
.\scripts\build_windows.ps1
```

Build output: `cmake-build-debugvisualstudio/`

Notes:
- Sets `VCPKG_ROOT` and prepends it to `PATH`
- Runs `vcpkg install`
- Configures CMake with the vcpkg toolchain file

---
