# Guide zum Compilen für Windows

## Boost für Windows installieren

Da wir Boost nutzen, um den Netzwerkverkehr zu leiten, muss dieses erst runtergeladen werden.

1.⁠ ⁠Download Boost:

⁠ bash
wget https://boostorg.jfrog.io/artifactory/main/release/1.84.0/source/boost_1_84_0.tar.gz
 ⁠

2.⁠ ⁠Entpacken und für Windows mit MinGW bauen:

⁠ bash
./bootstrap.sh
./b2 \
  toolset=gcc \
  address-model=64 \
  architecture=x86 \
  target-os=windows \
  link=static \
  threading=multi \
  variant=release \
  --prefix=$HOME/ProjektKI/boost-windows-install \
  --with-system install
 ⁠

Wir bauen nur ⁠ --with-system ⁠, da Boost.Asio von ⁠ boost_system ⁠ abhängt.

## CMake Setup

### Toolchain File: ⁠ toolchain-windows.cmake ⁠

⁠ cmake
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
 ⁠

### Main CMakeLists.txt:

⁠ cmake
set(Boost_NO_BOOST_CMAKE ON)
set(BOOST_ROOT "$ENV{HOME}/ProjektKI/boost-windows-install")
find_package(Boost REQUIRED COMPONENTS system)

add_library(pki_netlib ...)
target_include_directories(pki_netlib PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(pki_netlib PUBLIC ${Boost_LIBRARIES} ws2_32)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
 ⁠
## Building

1.⁠ ⁠Erzeuge die Build-Dateien:

⁠ bash
cmake -S . -B build-windows \
  -DCMAKE_TOOLCHAIN_FILE=toolchain-windows.cmake \
  -DCMAKE_BUILD_TYPE=Release
 ⁠

2.⁠ ⁠Baue das Projekt mit cmake:

⁠ bash
cmake --build build-windows
 ⁠

3.⁠ ⁠Statische Verlinkung überprüfen:

⁠ bash
x86_64-w64-mingw32-objdump -p build-windows/PKI_CppClientMain.exe | grep DLL
 ⁠
Es sollten nur Windows-System-DLLs wie ⁠ KERNEL32.dll ⁠ angezeigt werden, keine ⁠ libstdc++-6.dll ⁠.
