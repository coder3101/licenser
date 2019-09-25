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

/*
"AGPLv3": GNU Affero General Public License version 3
"AL2": Apache License version 2
"BSD2": BSD 2-clause License
"BSD3": BSD 3-clause License (New BSD License)
"BSL1": Boost Software License - Version 1.0
"GPLv2": GNU General Public License version 2
"GPLv3": GNU General Public License version 3
"LGPLv3": GNU Lesser General Public License version 3
"MIT": MIT License
"MPLv2": Mozilla Public License version 2
"CC-BY-3": Creative Commons Attribution 3.0
"CC-BY-SA-3": Creative Commons Attribution-ShareAlike 3.0
"CC-BY-NC-3": Creative Commons Attribution-NonCommercial 3.0
"CC-BY-ND-3": Creative Commons Attribution-NoDerivs 3.0
"CC-BY-NC-SA-3": Creative Commons Attribution-NonCommercial-ShareAlike 3.0
"CC-BY-NC-ND-3": Creative Commons Attribution-NonCommercial-NoDerivs 3.0
"CC-BY-4": Creative Commons Attribution 4.0
"CC-BY-SA-4": Creative Commons Attribution-ShareAlike 4.0
"CC-BY-NC-4": Creative Commons Attribution-NonCommercial 4.0
"CC-BY-ND-4": Creative Commons Attribution-NoDerivs 4.0
"CC-BY-NC-SA-4": Creative Commons Attribution-NonCommercial-ShareAlike 4.0
"CC-BY-NC-ND-4": Creative Commons Attribution-NonCommercial-NoDerivs 4.0
"CC0-1": CC0 1.0
"WTFPL": Do What The Fuck You Want To Public License
"zlib": zlib License
*/

#pragma once

namespace licenser::licenses {
enum LicenseType {
  AGPLv3,
  AL2,
  BSD2,
  BSD3,
  BSL1,
  GPLv2,
  GPLv3,
  LGPLv3,
  MIT,
  MPLv2,
  CC_BY_3,
  CC_BY_SA_3,
  CC_BY_NC_3,
  CC_BY_ND_3,
  CC_BY_NC_SA_3,
  CC_BY_NC_ND_3,
  CC_BY_4,
  CC_BY_SA_4,
  CC_BY_NC_4,
  CC_BY_ND_4,
  CC_BY_NC_SA_4,
  CC_BY_NC_ND_4,
  CCO1,
  WTFPL,
  ZLIB,
  CUSTOM,
  UNKNOWN
};
}