set "PATH=c:\Programs\CMake_3_19\bin"

rmdir /S /Q build_vector_vs32
cmake.exe . -B build_vector_vs32 -G "Visual Studio 16" -A Win32
cmake.exe --build build_vector_vs32 --config Debug
cmake.exe --build build_vector_vs32 --config Release

rmdir /S /Q build_vector_vs64
cmake.exe . -B build_vector_vs64 -G "Visual Studio 16" -A x64
cmake.exe --build build_vector_vs64 --config Debug
cmake.exe --build build_vector_vs64 --config Release

set "PATH=c:\Programs\CMake_3_19\bin;c:\msys64\mingw32\bin"

rmdir /S /Q build_vector_mingw32_debug
cmake.exe . -B build_vector_mingw32_debug -G "MinGW Makefiles" -D CMAKE_BUILD_TYPE=Debug
cmake --build build_vector_mingw32_debug
copy c:\msys64\mingw32\bin\libwinpthread-1.dll build_vector_mingw32_debug
copy "c:\msys64\mingw32\bin\libstdc++-6.dll" build_vector_mingw32_debug
copy c:\msys64\mingw32\bin\libgcc_s_dw2-1.dll build_vector_mingw32_debug

rmdir /S /Q build_vector_mingw32_release
cmake.exe . -B build_vector_mingw32_release -G "MinGW Makefiles" -D CMAKE_BUILD_TYPE=Release
cmake --build build_vector_mingw32_release
copy c:\msys64\mingw32\bin\libwinpthread-1.dll build_vector_mingw32_release
copy "c:\msys64\mingw32\bin\libstdc++-6.dll" build_vector_mingw32_release
copy c:\msys64\mingw32\bin\libgcc_s_dw2-1.dll build_vector_mingw32_release

set "PATH=c:\Programs\CMake_3_19\bin;c:\msys64\mingw64\bin"

rmdir /S /Q build_vector_mingw64_debug
cmake.exe . -B build_vector_mingw64_debug -G "MinGW Makefiles" -D CMAKE_BUILD_TYPE=Debug
cmake --build build_vector_mingw64_debug
copy c:\msys64\mingw64\bin\libwinpthread-1.dll build_vector_mingw64_debug
copy "c:\msys64\mingw64\bin\libstdc++-6.dll" build_vector_mingw64_debug
copy c:\msys64\mingw64\bin\libgcc_s_seh-1.dll build_vector_mingw64_debug

rmdir /S /Q build_vector_mingw64_release
cmake.exe . -B build_vector_mingw64_release -G "MinGW Makefiles" -D CMAKE_BUILD_TYPE=Release
cmake --build build_vector_mingw64_release
copy c:\msys64\mingw64\bin\libwinpthread-1.dll build_vector_mingw64_release
copy "c:\msys64\mingw64\bin\libstdc++-6.dll" build_vector_mingw64_release
copy c:\msys64\mingw64\bin\libgcc_s_seh-1.dll build_vector_mingw64_release

pause
