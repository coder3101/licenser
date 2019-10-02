include_directories(src/licensewriter/include)

add_library(licensewriter
            src/licensewriter/src/LicenseWriter.cc
            )

set_target_properties(licensewriter PROPERTIES 
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF)   