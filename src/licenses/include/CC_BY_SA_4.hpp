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


#pragma once
#include "License.hpp"
namespace licenser::licenses {
class CC_BY_SA_4_ final : public License {
 public:
  CC_BY_SA_4_();
  std::string body_to_string() const override;
  std::string header_to_string() const override;
  std::string name() const override;
};
}  // namespace licenser::licenses
