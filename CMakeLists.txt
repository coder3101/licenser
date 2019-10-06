cmake_minimum_required(VERSION 3.12)

project(licenser VERSION 0.01)
add_executable(licenser src/main.cc)

set(DEFAULT_CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(CODE_COVERAGE "Enable code coverage on tests" OFF)
option(ENABLE_TESTS "Enable building of tests" ON)
option(STATIC_EXECUTABLE "Should be make Static Executable (only GCC)" OFF)

set_target_properties(licenser PROPERTIES 
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF) 

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Build type set to '${DEFAULT_CMAKE_BUILD_TYPE}' as none specified.")
  set(CMAKE_BUILD_TYPE ${DEFAULT_CMAKE_BUILD_TYPE}
      CACHE STRING "Choose the type of build." FORCE)

  set_property(CACHE CMAKE_BUILD_TYPE
               PROPERTY STRINGS Debug Release MinSizeRel RelWithDebInfo)
endif()

# CMake sets MSVC for both MSVC and Clang(Windows)
if(MSVC)
  # Common MSVC/Clang(Windows) options
  target_compile_options(licenser PRIVATE
    /nologo
    /EHsc
    /D_CRT_SECURE_NO_WARNINGS # don't try to use MSVC std replacements
    /W3 # roughly -Wall
    /wd4996 # ignore deprecated declaration
    /wd4267 # ignores warning C4267
    /wd4800
    /wd4068 # Disable unknown pragma warning
    /std:c++17
    $<$<CONFIG:Debug>:/FS>
  )
  # relink system libs
  target_link_libraries(licenser PRIVATE Mincore.lib)
else()
  # Common GCC/Clang(Linux) options
  target_compile_options(licenser PRIVATE
                         -Wall
                         -Wno-sign-compare
                         )

  if(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    target_compile_options(licenser PRIVATE -Wno-return-type -Wno-unused-result)
  endif()

  if(${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    target_compile_options(licenser PRIVATE
                           $<$<CONFIG:Debug>:-fno-limit-debug-info>)
  endif()
endif()

# Header only Libraries
# Lyra used by licenser
include_directories(third_party/Lyra/include)
# Catch2 Used only upon Testing
if (ENABLE_TESTS)
  include_directories(third_party/Catch2/include)
endif()

# Licenser Headers
include_directories(src/utility)

# Building Static Libs
include(src/licenses/CMakeLists.txt)
include(src/configmgr/CMakeLists.txt)
include(src/writer/CMakeLists.txt)

# Static Modules of licenser
target_link_libraries(licenser PRIVATE licenses)
target_link_libraries(licenser PRIVATE writer)
target_link_libraries(licenser PRIVATE configmgr)

# Static linkage for libstdc++
if(STATIC_EXECUTABLE AND (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU))
  set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")
endif()

# Testing
if(ENABLE_TESTS)
  enable_testing()

  if (CODE_COVERAGE AND (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU))
    set(CMAKE_CXX_FLAGS "-O0 -g --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "--coverage")
    message(STATUS "Coverage report will be generated")
  endif()

  include(tests/preprocessor/CMakeLists.txt)
  include(tests/configmgr/CMakeLists.txt)

endif()
