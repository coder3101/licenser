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

#include "CC_BY_NC_3.hpp"

namespace licenser::licenses {
CC_BY_NC_3_::CC_BY_NC_3_() : License(LicenseType::CC_BY_NC_3) {}

std::string CC_BY_NC_3_::body_to_string() const {
  return R"i_like_naruto(

        )i_like_naruto";
}

std::string CC_BY_NC_3_::header_to_string() const {
  return R"i_like_naruto(

        )i_like_naruto";
}
}  // namespace licenser::licenses