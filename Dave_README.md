# Questo readme è per Dave per non perdersi nella scrittura e build del codice 


# Building IanniX

IanniX uses CMake (≥ 3.17) and Qt 5. Qt 6 support is in progress but not yet complete.
Release builds are 64-bit only; 32-bit releases have been discontinued.

# Linux


### openSUSE Tumbleweed

**Install dependencies**

```bash
sudo zypper install \
    cmake \
    gcc-c++ \
    libqt5-qtbase-devel \
    libqt5-qtdeclarative-devel \
    libqt5-qtserialport-devel \
    libqt5-qtwebsockets-devel \
    libqt5-qtx11extras-devel \
    muparser-devel \
    rtmidi-devel
```

**Configure and build**

```bash
cmake -B build -S .
cmake --build build -j$(nproc)
```

The binary is written to `build/iannix`.

**Install system-wide (optional)**

```bash
sudo cmake --install build
```

This installs the binary to `/usr/local/bin/iannix`, the `.desktop` file to
`/usr/local/share/applications/`, the icon to `/usr/local/share/pixmaps/`, and
the runtime asset directories to `/usr/local/share/iannix/`.

---

### Ubuntu 22.04 / 24.04

**Install dependencies**

```bash
sudo apt install \
    cmake \
    g++ \
    qtbase5-dev \
    libqt5opengl5-dev \
    qtdeclarative5-dev \
    libqt5serialport5-dev \
    libqt5websockets5-dev \
    libmuparser-dev \
    librtmidi-dev
```

**Configure and build**

```bash
::Original
cmake -B build -S . 

::Edited
cmake -B build -S . -DCMAKE_CXX_FLAGS="-I/usr/include/KF5/KSyntaxHighlighting"

cmake --build build -j$(nproc)
```

The binary is written to `build/iannix`.

**Install system-wide (optional)**

```bash
sudo cmake --install build
```
##### Build con log deprecated - UBUNTU
cmake -B build-qt5.15.2 -S . -DQT_VERSION=5 -DCMAKE_PREFIX_PATH=/opt/Qt/Qt5.15.12/5.15.2/gcc_64 -DCMAKE_CXX_FLAGS="-Wdeprecated-declarations" -DCMAKE_CXX_FLAGS="-Wdeprecated-declarations -Wno-error=deprecated-declarations"

- Log completo 
cmake --build build-qt5.15.2 -j$(nproc) 2>&1 | tee deprecated_qt6.log

- Log solo warning
cmake --build build-qt5.15.2 -j"$(nproc)" 2>&1 | tee build-qt6/full_build.log | rg "deprecated|deprecated-declarations" > build-qt6/deprecated_qt5.15.2.log




---

# Win

### Installa dipendenze

#### con vcpkg
1 - installa gestore pacchetti vcpkg https://learn.microsoft.com/it-it/vcpkg/get_started/get-started?pivots=shell-cmd
2 - Install the required and optional packages:

```bat
:: Required
%USERPROFILE%\vcpkg\vcpkg install muparser rtmidi --triplet x64-windows

:: Core Qt dependencies (alternative to the Qt installer)
%USERPROFILE%\vcpkg\vcpkg install qt5-base qt5-declarative qt5-serialport qt5-websockets --triplet x64-windows

:: Optional: FFmpeg (enables USE_FFMPEG=ON)
%USERPROFILE%\vcpkg\vcpkg install ffmpeg --triplet x64-windows

::Mandatory  kf5syntaxhighlighting
vcpkg install kf5syntaxhighlighting --triplet x64-windows

::Mandatory qt5 serial port
vcpkg install qt5-serialport --triplet x64-windows
```

Pass the vcpkg toolchain file to CMake:

```bat
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows

cmake --build build --config Release

::build con log
cmake --build build --config Release --verbose 2>&1 | Tee-Object -FilePath build.log
```

#### oppure manualmente
**installazione muparser**
```bat
:: Clona la repo 
git clone https://github.com/beltoforion/muparser third_party\muparser

:: Compila ed installa la libreria
cmake -S C:\third_party\muparser -B C:\third_party\build-muparser -DCMAKE_INSTALL_PREFIX=C:\third_party\install
cmake --build C:\third_party\build-muparser --config Release
cmake --install C:\third_party\build-muparser --config Release
```

**installazione rtmidi**
```bat
:: Clona Repo
git clone https://github.com/thestk/rtmidi third_party\rtmidi

:: Compila ed installa la libreria
cmake -S C:\third_party\rtmidi -B C:\third_party\build-rtmidi -DCMAKE_INSTALL_PREFIX=C:\third_party\install
cmake --build C:\third_party\build-rtmidi --config Release
cmake --install C:\third_party\build-rtmidi --config Release
```


### BUILD
#### Build qt5.15.2 - UBUNTU
cmake -B build-qt5.15.2 -S . -DQT_VERSION=5 -DCMAKE_PREFIX_PATH=/home/dave/Qt/5.15.2/gcc_64
cmake --build build-qt5.15.2 -j$(nproc)

#### Build qt5.15.2 - WIN
```bat
::Compilazione MinGW
cmake -B build-qt5.15.2 -S . -G "MinGW Makefiles" "-DCMAKE_PREFIX_PATH=C:\Qt\Qt 5.15.2\Tools\mingw810_64"

::Compilazione MSVC
cmake -B build-qt5.5.2 -S . "-DCMAKE_PREFIX_PATH=C:\Qt\Qt 5.15.2\Tools\msvc2019_64"

cmake --build build -j$env:NUMBER_OF_PROCESSORS
```

##### Build con log deprecated - UBUNTU
cmake -B build-qt6 -S . -DQT_VERSION=6 -DCMAKE_PREFIX_PATH=/opt/Qt/6.11.0/gcc_64 -DCMAKE_CXX_FLAGS="-Wdeprecated-declarations" -DCMAKE_CXX_FLAGS="-Wdeprecated-declarations -Wno-error=deprecated-declarations"

- Log completo 
cmake --build build-qt6 -j$(nproc) 2>&1 | tee deprecated_qt6.log

- Log solo warning
cmake --build build-qt6 -j"$(nproc)" 2>&1 | tee build-qt6/full_build.log | rg "deprecated|deprecated-declarations" > build-qt6/deprecated_qt6.log