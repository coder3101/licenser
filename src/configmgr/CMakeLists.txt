include_directories(src/configmgr/include)
add_library(configmgr
            src/configmgr/src/ConfigReader.cc
            src/configmgr/src/ConfigWriter.cc
            src/configmgr/src/ConfigParser.cc
            src/configmgr/src/ConfigIgnore.cc
            src/configmgr/src/ConfigManager.cc
            src/configmgr/src/ConfigOnly.cc
            src/configmgr/src/ConfigCustomHeader.cc
            src/configmgr/src/ConfigCommand.cc
            src/configmgr/src/RecursiveFileIterator.cc)

set_target_properties(configmgr PROPERTIES 
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF)