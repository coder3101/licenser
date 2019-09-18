/**
 * Copyright (C) 2019
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

#include <CommandLineArgs.hpp>
#include <GPLv3.hpp>
#include <iostream>
#include <lyra/lyra.hpp>

int main(int argc, const char** argv) {
  licenser::ApplicationArgs args;

  auto cli = lyra::help(args.showHelp) |
             lyra::opt(args.initiate)["-i"]["--init"](
                 "Initiates a Simple License Configuration") |
             lyra::opt(args.update)["-u"]["--update"](
                 "Updates Source files with configuration changes");

  auto result = cli.parse({argc, argv});

  if (!result) {
    std::cerr << "Error in command line: " << result.errorMessage()
              << std::endl;
    exit(1);
  } else if (args.showHelp) {
    std::cout << cli;
  } else if (args.initiate) {
    // licenser init
  } else if (args.update) {
    // licenser update
  } else {
    std::cout << cli;
  }
  return 0;
}