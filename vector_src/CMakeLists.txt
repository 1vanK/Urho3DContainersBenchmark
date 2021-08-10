cmake_minimum_required(VERSION 3.19)

project(vector)

# Название таргета
set(target_name vector_benchmark)

# Создаём список файлов
file(GLOB_RECURSE source_files *.cpp *.h)

# Создаём конольное приложение
add_executable(${target_name} ${source_files})

# Заставляем VS отображать дерево каталогов
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${source_files})
