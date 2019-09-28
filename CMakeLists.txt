cmake_minimum_required(VERSION 3.12)

project(licenser VERSION 0.01)
add_executable(licenser src/main.cc)

set(DEFAULT_CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(CODE_COVERAGE "Enable code coverage on tests" OFF)
option(ENABLE_TESTS "Enable building of tests" ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Build type set to '${DEFAULT_CMAKE_BUILD_TYPE}' as none specified.")
  set(CMAKE_BUILD_TYPE ${DEFAULT_CMAKE_BUILD_TYPE}
      CACHE STRING "Choose the type of build." FORCE)

  set_property(CACHE CMAKE_BUILD_TYPE
               PROPERTY STRINGS Debug Release MinSizeRel RelWithDebInfo)
endif()

# Set C++17 as build standard

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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
include_directories(src)
include_directories(src/licenses/include)

# Building Static Libs
add_library(licenses 
            src/licenses/src/AGPLv3.cc
            src/licenses/src/AL2.cc
            src/licenses/src/BSD2.cc
            src/licenses/src/BSD3.cc
            src/licenses/src/BSL1.cc
            src/licenses/src/CC_BY_3.cc
            src/licenses/src/CC_BY_4.cc
            src/licenses/src/CC_BY_NC_3.cc
            src/licenses/src/CC_BY_NC_4.cc
            src/licenses/src/CC_BY_NC_ND_3.cc
            src/licenses/src/CC_BY_NC_ND_4.cc
            src/licenses/src/CC_BY_NC_SA_3.cc
            src/licenses/src/CC_BY_NC_SA_4.cc
            src/licenses/src/CC_BY_ND_3.cc
            src/licenses/src/CC_BY_ND_4.cc
            src/licenses/src/CC_BY_SA_3.cc
            src/licenses/src/CC_BY_SA_4.cc
            src/licenses/src/CC0_1.cc
            src/licenses/src/GPLv2.cc
            src/licenses/src/GPLv3.cc 
            src/licenses/src/LGPLv3.cc
            src/licenses/src/License.cc
            src/licenses/src/MIT.cc
            src/licenses/src/MPLv2.cc
            src/licenses/src/WTFPL.cc
            src/licenses/src/ZLIB.cc
            )

add_library(utility
            src/LicenseWriter.cc)

# Static Modules of licenser
target_link_libraries(licenser PRIVATE licenses)
target_link_libraries(licenser PRIVATE utility)

# Testing
if(ENABLE_TESTS)
  enable_testing()

  if (CODE_COVERAGE AND (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU))
    set(CMAKE_CXX_FLAGS "-O0 -g --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "--coverage")
    message(STATUS "Coverage report will be generated")
  endif()

  add_executable(parse_cc tests/preprocessor/parse.cc)
  add_executable(remove_placeholder_cc tests/preprocessor/remove_placeholder.cc)

  add_test(parser parse_cc)
  add_test(placeholder remove_placeholder_cc)

endif()
