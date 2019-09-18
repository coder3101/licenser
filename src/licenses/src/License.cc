/**
 * Copyright (C) 2019 Ashar ashar786khan@gmail.com
 *
 * This file is part of licenser.
 *
 * licenser is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * licenser is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with licenser.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "License.hpp"

namespace licenser::licenses {
License::License(LicenseType t) : typeLicense(t){};

inline LicenseType License::enum_type() const noexcept { return typeLicense; }

inline std::string License::license_name() const noexcept {
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
  }
}
}  // namespace licenser::licenses