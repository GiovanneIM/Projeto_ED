
cmake_minimum_required(VERSION 3.15)

project(projeto_ED VERSION 1.0 LANGUAGES CXX)

# Padrão da linguagem
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Arquivos fonte
file(GLOB SRC_FILES
    src/*.cpp
)

# Executável
add_executable(projeto
    main.cpp
    ${SRC_FILES}
)

# Diretório de includes
target_include_directories(projeto PRIVATE include)

# Warnings
target_compile_options(projeto PRIVATE -Wall -Wextra)