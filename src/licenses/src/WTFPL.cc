/*
* Copyright (C) 2019- Mohammad Ashar Khan ashar786khan@gmail.com
*  
* This file is part of Licenser.
*  
* Licenser is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*  
* Licenser is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*  
* You should have received a copy of the GNU General Public License
* along with Licenser.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "WTFPL.hpp"

namespace licenser::licenses {
WTFPL_::WTFPL_() : License(LicenseType::WTFPL) {}

std::string WTFPL_::body_to_string() const {
  return R"i_like_naruto(
DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
Version 2, December 2004

Copyright (C) %YEAR_FROM%-%YEAR_TO% %AUTHOR%

Everyone is permitted to copy and distribute verbatim or modified
copies of this license document, and changing it is allowed as long
as the name is changed.

DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

0. You just DO WHAT THE FUCK YOU WANT TO.

)i_like_naruto";
}

std::string WTFPL_::header_to_string() const {
  return R"i_like_naruto(Copyright %YEAR_FROM%-%YEAR_TO% %AUTHOR%.
Use of this source code is governed by the WTFPL
license that can be found in the LICENSE file.)i_like_naruto";
}

std::string WTFPL_::name() const {
  return "Do What The Fuck You Want To Public License";
}
}  // namespace licenser::licenses
