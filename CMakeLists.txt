cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(vector)

# Название таргета
set(target_name vector_benchmark)

# Создаём список файлов
file(GLOB_RECURSE source_files vector_src/*.cpp vector_src/*.h)

# Создаём конольное приложение
add_executable(${target_name} ${source_files})

# Заставляем VS отображать дерево каталогов
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${source_files})

# Создаём таргет EASTL
add_subdirectory(EASTL)

# Делаем EASTL доступным нашему проекту
target_link_libraries(${target_name} PUBLIC EASTL)
