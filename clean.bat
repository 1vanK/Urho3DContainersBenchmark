rmdir /S /Q build_vector_vs32\CMakeFiles
rmdir /S /Q build_vector_vs32\EASTL
rmdir /S /Q build_vector_vs32\vector_benchmark.dir
rmdir /S /Q build_vector_vs32\Win32
rmdir /S /Q build_vector_vs32\.vs
del build_vector_vs32\*.* /f /q

rmdir /S /Q build_vector_vs64\CMakeFiles
rmdir /S /Q build_vector_vs64\EASTL
rmdir /S /Q build_vector_vs64\vector_benchmark.dir
rmdir /S /Q build_vector_vs64\x64
rmdir /S /Q build_vector_vs64\.vs
del build_vector_vs64\*.* /f /q

rmdir /S /Q build_vector_mingw32_debug\CMakeFiles
rmdir /S /Q build_vector_mingw32_debug\EASTL
del build_vector_mingw32_debug\Makefile /f /q
del build_vector_mingw32_debug\cmake_install.cmake /f /q
del build_vector_mingw32_debug\CMakeCache.txt /f /q

rmdir /S /Q build_vector_mingw32_release\CMakeFiles
rmdir /S /Q build_vector_mingw32_release\EASTL
del build_vector_mingw32_release\Makefile /f /q
del build_vector_mingw32_release\cmake_install.cmake /f /q
del build_vector_mingw32_release\CMakeCache.txt /f /q

rmdir /S /Q build_vector_mingw64_debug\CMakeFiles
rmdir /S /Q build_vector_mingw64_debug\EASTL
del build_vector_mingw64_debug\Makefile /f /q
del build_vector_mingw64_debug\cmake_install.cmake /f /q
del build_vector_mingw64_debug\CMakeCache.txt /f /q

rmdir /S /Q build_vector_mingw64_release\CMakeFiles
rmdir /S /Q build_vector_mingw64_release\EASTL
del build_vector_mingw64_release\Makefile /f /q
del build_vector_mingw64_release\cmake_install.cmake /f /q
del build_vector_mingw64_release\CMakeCache.txt /f /q

pause
