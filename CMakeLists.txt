cmake_minimum_required(3.15)

project(licenser 
        VERSION 0.1
        LANGUAGE CXX)

add_executable(licenser "")

set(DEFAULT_CMAKE_BUILD_TYPE Release)


if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Build type set to '${DEFAULT_CMAKE_BUILD_TYPE}' as none specified.")
  set(CMAKE_BUILD_TYPE ${DEFAULT_CMAKE_BUILD_TYPE}
      CACHE STRING "Choose the type of build." FORCE)

  set_property(CACHE CMAKE_BUILD_TYPE
               PROPERTY STRINGS Debug Release MinSizeRel RelWithDebInfo)
endif()

set_property(TARGET licenser PROPERTY CXX_STANDARD 17)
set_property(TARGET licenser PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET licenser PROPERTY CXX_EXTENSIONS OFF)

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

# Libraries
