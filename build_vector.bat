set "PATH=c:\Programs\CMake_3_19\bin"

cmake.exe vector_src -B build_vector_vs32 -G "Visual Studio 16" -A Win32
cmake.exe --build build_vector_vs32 --config Debug
cmake.exe --build build_vector_vs32 --config Release

cmake.exe vector_src -B build_vector_vs64 -G "Visual Studio 16" -A x64
cmake.exe --build build_vector_vs64 --config Debug
cmake.exe --build build_vector_vs64 --config Release

set "PATH=c:\Programs\CMake_3_19\bin;c:\msys64\mingw32\bin"

cmake.exe vector_src -B build_vector_mingw32_debug -G "MinGW Makefiles" -D CMAKE_BUILD_TYPE=Debug
cmake --build build_vector_mingw32_debug

cmake.exe vector_src -B build_vector_mingw32_release -G "MinGW Makefiles" -D CMAKE_BUILD_TYPE=Release
cmake --build build_vector_mingw32_release

set "PATH=c:\Programs\CMake_3_19\bin;c:\msys64\mingw64\bin"

cmake.exe vector_src -B build_vector_mingw64_debug -G "MinGW Makefiles" -D CMAKE_BUILD_TYPE=Debug
cmake --build build_vector_mingw64_debug

cmake.exe vector_src -B build_vector_mingw64_release -G "MinGW Makefiles" -D CMAKE_BUILD_TYPE=Release
cmake --build build_vector_mingw64_release

pause
