include_directories(src/configmgr/include)
add_library(configmgr
            src/configmgr/src/ConfigReader.cc
            src/configmgr/src/ConfigWriter.cc
            src/configmgr/src/ConfigParser.cc)

set_target_properties(configmgr PROPERTIES 
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF)