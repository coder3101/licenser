cmake_minimum_required(VERSION 3.12)

include_directories(src/writer/include)

add_library(writer
            src/writer/src/LicenseWriter.cc
            )
set_target_properties(writer PROPERTIES 
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF)   