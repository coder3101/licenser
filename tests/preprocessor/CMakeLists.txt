add_executable(parse_cc tests/preprocessor/parse.cc)

add_test(parser parse_cc)
set_target_properties(parse_cc PROPERTIES 
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF) 