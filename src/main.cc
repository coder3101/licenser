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

#define VERSION_MAJOR 0
#define VERSION_MINOR 0
#define VERSION_PATCH 2

#include <CommandLineArgs.hpp>
#include <iostream>
#include <lyra/lyra.hpp>
#include "ArchInfo.hpp"
#include "ConfigReader.hpp"
#include "ConfigWriter.hpp"
#include "LicenseWriter.hpp"
#include "all_license.hpp"

unsigned int this_year() {
  auto cur_time = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(cur_time);
  auto tm_ptr = std::localtime(&time);
  return tm_ptr->tm_year + 1900;
}

int main(int argc, const char** argv) {
  licenser::ApplicationArgs args;

  auto cli =
      lyra::help(args.commandLineArgs.showHelp) |

      lyra::opt(args.commandLineArgs.initiate)["-i"]["--init"](
          "Initiates a Simple License Configuration") |

      lyra::opt(args.commandLineArgs.update)["-u"]["--update"](
          "Updates Source files with configuration changes") |

      lyra::opt(args.license, "license_shortname")["-l"]["--license"](
          "The short name for license separated by underscore in case "
          "of multiwords")
          .optional()
          .choices([](std::string input) {
            return licenser::licenses::License::enum_from_name(input) !=
                   licenser::licenses::LicenseType::UNKNOWN;
          }) |

      lyra::opt(args.email, "email@domail.com")["-e"]["--email"](
          "The email that should appear on source headers. For multiple "
          "users you can separate them by \" , \" ")
          .optional()
          .choices([](std::string s) {
            auto at_idx = s.find('@');
            auto last_dot = s.find_last_of('.');
            return at_idx != std::string::npos &&
                   last_dot != std::string::npos && last_dot > at_idx;
          }) |

      lyra::opt(args.project, "project_name")["-p"]["--project"](
          "The name of the project that will appear in license headers")
          .optional() |

      lyra::opt(args.year, "year")["-y"]["--year"](
          "The starting year of the project that will appear in the license "
          "header")
          .optional()
          .choices([](std::string s) {
            try {
              auto res = std::atoi(s.c_str());
              return res > 1900;
            } catch (...) {
              return false;
            }
          }) |

      lyra::opt(args.author, "author_name")["-a"]["--author"](
          "The author names or organization name that will be displayed in the "
          "header. You can separate multiple by \" , \"")
          .optional() |

      lyra::opt(args.ongoing_project)["-o"]["--ongoing"](
          "If this project is currently ongoing? This flag is used to "
          "update the year in the Source headers.")
          .optional() |

      lyra::opt(args.commandLineArgs.showVersion)["-v"]["--version"](
          "Shows the version of the application")
          .optional();

  auto result = cli.parse({argc, argv});

  if (!result) {
    std::cerr << "Error in command line: " << result.errorMessage()
              << std::endl;
    exit(1);
  }

  else if (args.commandLineArgs.showVersion) {
    std::cout << "Licenser version " << VERSION_MAJOR << "." << VERSION_MINOR
              << VERSION_PATCH << "\n";
    std::cout << "Licensed under GNU General Public License Version 3\n";
    std::cout << "Target Architecture : " << licenser::get_arch() << "\n";
  }

  else if (args.commandLineArgs.showHelp) {
    std::cout << cli;
  }

  else if (args.commandLineArgs.initiate) {
    auto res = licenser::configmgr::ConfigReader::has_config_file(".");
    if (res) {
      std::cout << "A Configuration file named " << LICENSER_CONFIG_NAME
                << " already exists\n";
      return 0;
    } else {
      std::cout << "Creating a Configuration File in Current Working Directory";

      if (args.author.empty()) {
        while (args.author.empty()) {
          std::cout << std::endl;
          std::cout << "Who is the author (required) : ";
          std::getline(std::cin, args.author);
        }
      }

      if (args.email.empty()) {
        std::cout << std::endl;
        std::cout << "An email of the author (optional) : ";
        std::getline(std::cin, args.author);
      }

      if (args.project.empty()) {
        while (args.project.empty()) {
          std::cout << std::endl;
          std::cout << "Name of the project (required) : ";
          std::getline(std::cin, args.author);
        }
      }

      if (args.year == 0) {
        while (args.year > 1900) {
          std::cout << std::endl;
          std::cout << "When did project started : ";
          std::string num;
          std::getline(std::cin, num);
          try {
            args.year = std::atoi(num.c_str());
          } catch (...) {  // ignore
          };
          if (args.year <= this_year()) {
            std::cout << "Start year cannot Exceed Current year\n";
            args.year = 0;
          }
        }
      }

      if (!args.ongoing_project && args.year < this_year()) {
        std::string res;
        while (res.empty()) {
          std::cout << "Project started in past. Is it still being maintained "
                       "(Y/N)? : ";
          std::getline(std::cin, res);
        }
        args.ongoing_project = res[0] == 'Y' || res[0] == 'y';
      }

      if (args.license.empty()) {
        bool f = true;
        while (f) {
          std::cout << "Short name of license for the project : ";
          std::string ans;
          std::getline(std::cin, ans);
          args.license = ans;
          f = licenser::licenses::License::enum_from_name(ans) ==
              licenser::licenses::LicenseType::UNKNOWN;
        }
      }

      licenser::configmgr::ConfigWriter::write(args);
      using namespace licenser::licenses;

      auto license_enum = License::enum_from_name(args.license);
      auto license_ptr = License::make_license(license_enum);

      licenser::writer::LicenseWriter writer(std::move(license_ptr));
      writer.write(args);
      std::cout << "Initiated LICENSE file in directory " << writer.cwd()
                << std::endl;
    }
  }

  else if (args.commandLineArgs.update) {
    std::cout << "Reading from config\n";
    licenser::configmgr::ConfigReader::read(".");
  } else
    std::cout << cli;
  return 0;
}