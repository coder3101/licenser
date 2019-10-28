/*
* Copyright (c) 2019 Mohammad Ashar Khan <ashar786khan@gmail.com>
* 
* Licenser is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* Enjoy the software but don't blame me if you blow up things !!
* 
*/


#include "License.hpp"
#include "all_license.hpp"

namespace licenser::licenses {
License::License(LicenseType t) : typeLicense(t){};

inline LicenseType License::enum_type() const noexcept { return typeLicense; }

std::string License::name_from_enum(LicenseType typeLicense) noexcept {
  switch (typeLicense) {
    case AGPLv3:
      return "GNU Affero General Public License version 3";
    case AL2:
      return "Apache License version 2";
    case BSD2:
      return "BSD 2-clause License";
    case BSD3:
      return "BSD 3-clause License (New BSD License)";
    case BSL1:
      return "Boost Software License - Version 1.0";
    case CC_BY_3:
      return "Creative Commons Attribution 3.0";
    case CC_BY_4:
      return "Creative Commons Attribution 4.0";
    case CC_BY_NC_3:
      return "Creative Commons Attribution-NonCommercial 3.0";
    case CC_BY_NC_4:
      return "Creative Commons Attribution-NonCommercial 4.0";
    case CC_BY_NC_ND_3:
      return "Creative Commons Attribution-NonCommercial-NoDerivs 3.0";
    case CC_BY_NC_ND_4:
      return "Creative Commons Attribution-NonCommercial-NoDerivs 4.0";
    case CC_BY_NC_SA_3:
      return "Creative Commons Attribution-NonCommercial-ShareAlike 3.0";
    case CC_BY_NC_SA_4:
      return "Creative Commons Attribution-NonCommercial-ShareAlike 4.0";
    case CC_BY_ND_3:
      return "Creative Commons Attribution-NoDerivs 3.0";
    case CC_BY_ND_4:
      return "Creative Commons Attribution-NoDerivs 4.0";
    case CC_BY_SA_3:
      return "Creative Commons Attribution-ShareAlike 3.0";
    case CC_BY_SA_4:
      return "Creative Commons Attribution-ShareAlike 4.0";
    case CCO1:
      return "CC0 1.0";
    case GPLv2:
      return "GNU General Public License version 2";
    case GPLv3:
      return "GNU General Public License version 3";
    case LGPLv3:
      return "GNU Lesser General Public License version 3";
    case MIT:
      return "MIT License";
    case MPLv2:
      return "Mozilla Public License version 2";
    case WTFPL:
      return "Do What The Fuck You Want To Public License";
    case ZLIB:
      return "zlib License";
    case CUSTOM:
      return "Custom";
    default:  // Unknown
      return "Unknown";
  }
}

std::string License::short_name_from_enum(LicenseType typeLicense) noexcept {
  switch (typeLicense) {
    case AGPLv3:
      return "AGPLv3";
    case AL2:
      return "AL2";
    case BSD2:
      return "BSD2";
    case BSD3:
      return "BSD3";
    case BSL1:
      return "BSL1";
    case CC_BY_3:
      return "CC_BY_3";
    case CC_BY_4:
      return "CCC_BY_4";
    case CC_BY_NC_3:
      return "CC_BY_NC_3";
    case CC_BY_NC_4:
      return "CC_BY_NC_4";
    case CC_BY_NC_ND_3:
      return "CC_BY_NC_ND_3";
    case CC_BY_NC_ND_4:
      return "CC_BY_NC_ND_4";
    case CC_BY_NC_SA_3:
      return "CC_BY_NC_SA_3";
    case CC_BY_NC_SA_4:
      return "CC_BY_NC_SA_4";
    case CC_BY_ND_3:
      return "CC_BY_ND_3";
    case CC_BY_ND_4:
      return "CC_BY_ND_4";
    case CC_BY_SA_3:
      return "CC_BY_SA_3";
    case CC_BY_SA_4:
      return "CC_BY_SA_4";
    case CCO1:
      return "CC01";
    case GPLv2:
      return "GPLv2";
    case GPLv3:
      return "GPLv3";
    case LGPLv3:
      return "LGPLv3";
    case MIT:
      return "MIT";
    case MPLv2:
      return "MPLv2";
    case WTFPL:
      return "WTFPL";
    case ZLIB:
      return "ZLIB";
    case CUSTOM:
      return "CUSTOM";
    default:  // Unknown
      return "UNKNOWN";
  }
}

std::unique_ptr<License> License::make_license(
    LicenseType type, std::unique_ptr<License> custom) {
  switch (type) {
    case AGPLv3:
      return std::make_unique<AGPLv3_>();
    case AL2:
      return std::make_unique<AL2_>();
    case BSD2:
      return std::make_unique<BSD2_>();
    case BSD3:
      return std::make_unique<BSD3_>();
    case BSL1:
      return std::make_unique<BSL1_>();
    case CC_BY_3:
      return std::make_unique<CC_BY_3_>();
    case CC_BY_4:
      return std::make_unique<CC_BY_4_>();
    case CC_BY_NC_3:
      return std::make_unique<CC_BY_NC_3_>();
    case CC_BY_NC_4:
      return std::make_unique<CC_BY_NC_4_>();
    case CC_BY_NC_ND_3:
      return std::make_unique<CC_BY_NC_ND_3_>();
    case CC_BY_NC_ND_4:
      return std::make_unique<CC_BY_NC_ND_4_>();
    case CC_BY_NC_SA_3:
      return std::make_unique<CC_BY_NC_SA_3_>();
    case CC_BY_NC_SA_4:
      return std::make_unique<CC_BY_NC_SA_4_>();
    case CC_BY_ND_3:
      return std::make_unique<CC_BY_ND_3_>();
    case CC_BY_ND_4:
      return std::make_unique<CC_BY_ND_4_>();
    case CC_BY_SA_3:
      return std::make_unique<CC_BY_SA_3_>();
    case CC_BY_SA_4:
      return std::make_unique<CC_BY_SA_4_>();
    case CCO1:
      return std::make_unique<CC0_1_>();
    case GPLv2:
      return std::make_unique<GPLv2_>();
    case GPLv3:
      return std::make_unique<GPLv3_>();
    case LGPLv3:
      return std::make_unique<LGPLv3_>();
    case MIT:
      return std::make_unique<MIT_>();
    case MPLv2:
      return std::make_unique<MPLv2_>();
    case WTFPL:
      return std::make_unique<WTFPL_>();
    case ZLIB:
      return std::make_unique<ZLIB_>();
    case CUSTOM:
      return custom;
    default:  // Unknown
      return nullptr;
  }
}

LicenseType License::enum_from_name(std::string shortName) noexcept {
  for (auto &e : shortName)
    if (e >= 'a' && e <= 'z') e = e - 32;
  if (shortName == "AGPLV3")
    return AGPLv3;
  else if (shortName == "AL2")
    return AL2;
  else if (shortName == "BSD2")
    return BSD2;
  else if (shortName == "BSD3")
    return BSD3;
  else if (shortName == "BSL1")
    return BSL1;
  else if (shortName == "CC_BY_3")
    return CC_BY_3;
  else if (shortName == "CC_BY_4")
    return CC_BY_4;
  else if (shortName == "CC_BY_NC_3")
    return CC_BY_NC_3;
  else if (shortName == "CC_BY_NC_4")
    return CC_BY_NC_4;
  else if (shortName == "CC_BY_NC_ND_3")
    return CC_BY_NC_ND_3;
  else if (shortName == "CC_BY_NC_ND_4")
    return CC_BY_NC_ND_4;
  else if (shortName == "CC_BY_NC_SA_3")
    return CC_BY_NC_SA_3;
  else if (shortName == "CC_BY_NC_SA_4")
    return CC_BY_NC_SA_4;
  else if (shortName == "CC_BY_ND_3")
    return CC_BY_ND_3;
  else if (shortName == "CC_BY_ND_4")
    return CC_BY_ND_4;
  else if (shortName == "CC_BY_SA_3")
    return CC_BY_SA_3;
  else if (shortName == "CC_BY_SA_4")
    return CC_BY_SA_4;
  else if (shortName == "CC01")
    return CCO1;
  else if (shortName == "GPLV2")
    return GPLv2;
  else if (shortName == "GPLV3")
    return GPLv3;
  else if (shortName == "LGPLV3")
    return LGPLv3;
  else if (shortName == "MIT")
    return MIT;
  else if (shortName == "MPLV2")
    return MPLv2;
  else if (shortName == "WTFPL")
    return WTFPL;
  else if (shortName == "ZLIB")
    return ZLIB;
  else if (shortName == "CUSTOM")
    return CUSTOM;
  else
    return UNKNOWN;
}

}  // namespace licenser::licenses
