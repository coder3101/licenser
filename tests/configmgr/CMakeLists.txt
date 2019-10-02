add_library(configmgr_test src/configmgr/src/ConfigParser.cc)
add_executable(config_parse_cc tests/configmgr/configparser.cc)
target_link_libraries(config_parse_cc PRIVATE configmgr_test )
add_test(config_parser config_parse_cc)
set_target_properties(config_parse_cc PROPERTIES 
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF) 