include_directories(src/licenses/include)

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
            
set_target_properties(licenses PROPERTIES 
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED ON
                      CXX_EXTENSIONS OFF)