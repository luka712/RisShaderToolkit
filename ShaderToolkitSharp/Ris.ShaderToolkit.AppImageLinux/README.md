# Creating an AppImage

To bundle your application as an **AppImage**, follow these steps:

---

## 1. Get AppImageTool

If you don’t already have it, download **AppImageTool** from:
[https://github.com/AppImage/appimagetool/releases](https://github.com/AppImage/appimagetool/releases)

Make it executable:

```bash
chmod +x appimagetool
```

> If your project folder already contains it, you can skip this step.

---

## 2. Create an AppDir

Create a folder ending with `.AppDir` (the name can be anything, e.g., `RisShaderToolkit.AppDir`):

```bash
mkdir RisShaderToolkit
```

Inside the AppDir, create the following structure:

```
RisShaderToolkit.AppDir/
├── usr/
│   └── bin/      # Place all your compiled binaries here
```

---

## 3. Add a `.desktop` File

Create a `.desktop` file (name can be anything, e.g., `RisShaderToolkit.desktop`) inside the AppDir:

```ini
[Desktop Entry]
Name=Ris Shader Toolkit
Exec=ris-shader-toolkit
Icon=icon
Type=Application
Categories=Utility
Terminal=false
StartupNotify=true
PrefersNonDefaultGPU=false
```

* `Exec` should point to your binary.
* `Icon` should match the icon filename you will add.
* Adjust `Categories` if necessary (see [Freedesktop.org categories](https://specifications.freedesktop.org/menu-spec/latest/apa.html#main-categories)).

---

## 4. Add an Icon

Place a 256×256 PNG icon in the AppDir:

```
RisShaderToolkit.AppDir/icon.png
```

> Ensure the icon filename matches the `Icon` field in your `.desktop` file.

---

## 5. Create the AppRun Script

Create an `AppRun` file in the root of the AppDir. This script tells AppImage which binary to execute:

```bash
#!/bin/sh

DIR="$(dirname "$(readlink -f "$0")")"
EXEC="${DIR}/usr/bin/ris-sprite-toolkit"
exec "$EXEC"
```

Make it executable:

```bash
chmod +x RisShaderToolkit.AppDir/AppRun
```

---

## 6. Build the AppImage

Run **AppImageTool** to generate your AppImage:

```bash
./appimagetool RisShaderToolkit.AppDir
```

This will create `RisShaderToolkit.AppDir/AppRun-x86_64.AppImage` (or similar) in your current folder.

---

✅ Your application is now packaged as a portable AppImage that can run on most Linux distributions without installation.

