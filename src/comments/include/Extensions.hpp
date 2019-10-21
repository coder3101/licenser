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


#pragma once
#include <memory>

#include "Base.hpp"
#include "all_lang.hpp"

namespace licenser::comments {
struct Extensions {
  static std::unique_ptr<CommentBase> to_lang(std::string extension) {
    if (extension == ".ads" || extension == ".adb")
      return std::make_unique<Ada>();

    else if (extension == ".applescript" || extension == ".scpt")
      return std::make_unique<AppleScript>();

    else if (extension == ".S" || extension == ".s" || extension == ".asm")
      return std::make_unique<Asm>();

    else if (extension == ".c" || extension == ".h")
      return std::make_unique<C>();

    else if (extension == ".cpp" || extension == ".cc" || extension == ".cxx" ||
             extension == ".CPP" || extension == ".C" || extension == ".c++" ||
             extension == ".hpp" || extension == ".hxx" || extension == ".hh")
      return std::make_unique<Cxx>();

    else if (extension == ".go")
      return std::make_unique<Go>();

    else if (extension == ".lhs" || extension == ".hs")
      return std::make_unique<Haskell>();

    else if (extension == ".html" || extension == ".htm" ||
             extension == ".xhtml")
      return std::make_unique<Html>();

    else if (extension == ".java")
      return std::make_unique<Java>();

    else if (extension == ".JS" || extension == ".js")
      return std::make_unique<JavaScript>();

    else if (extension == ".kt" || extension == ".kts" || extension == ".ktm")
      return std::make_unique<Kotlin>();

    else if (extension == ".lua")
      return std::make_unique<Lua>();

    else if (extension == ".m")
      return std::make_unique<Matlab>();

    else if (extension == ".ml" || extension == ".mli")
      return std::make_unique<OCaml>();

    else if (extension == ".pl")
      return std::make_unique<Perl>();

    else if (extension == ".php")
      return std::make_unique<Php>();

    else if (extension == ".ps1")
      return std::make_unique<PowerShell>();

    else if (extension == ".py" || extension == ".py2" || extension == ".py3")
      return std::make_unique<Python>();

    else if (extension == ".rb" || extension == ".ruby")
      return std::make_unique<Ruby>();

    else if (extension == ".rs" || extension == ".rlib")
      return std::make_unique<Rust>();

    else if (extension == ".sh" || extension == ".zsh")
      return std::make_unique<Shell>();

    else if (extension == ".sql")
      return std::make_unique<Sql>();

    else if (extension == ".swift")
      return std::make_unique<Swift>();

    else if (extension == ".xml")
      return std::make_unique<Xml>();

    else if (extension == ".yaml" || extension == ".yml")
      return std::make_unique<Yaml>();

    else
      return nullptr;
  }
};
}  // namespace licenser::comments
