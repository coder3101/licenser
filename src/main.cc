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

#include <CommandLineArgs.hpp>
#include <iostream>
#include <lyra/lyra.hpp>
#include "LicenseWriter.hpp"
#include "all_license.hpp"

int main(int argc, const char** argv) {
  licenser::ApplicationArgs args;

  auto cli =
      lyra::help(args.showHelp) |

      lyra::opt(args.initiate)["-i"]["--init"](
          "Initiates a Simple License Configuration") |

      lyra::opt(args.update)["-u"]["--update"](
          "Updates Source files with configuration changes") |

      lyra::opt(args.license, "license_shortname")["-l"]["--license"](
          "The short name for license separated by underscore in case "
          "of multiwords")
          .optional() |

      lyra::opt(args.email, "email@domail.com")["-e"]["--email"](
          "The email that should appear on source headers. For multiple "
          "users you can separate them by \" , \" ")
          .optional() |

      lyra::opt(args.project, "project_name")["-p"]["--project"](
          "The name of the project that will appear in license headers")
          .optional() |

      lyra::opt(args.year, "year")["-y"]["--year"](
          "The starting year of the project that will appear in the license "
          "header")
          .optional() |

      lyra::opt(args.author, "author_name")["-a"]["--author"](
          "The author names or organization name that will be displayed in the "
          "header. You can separate multiple by \" , \"")
          .optional() |

      lyra::opt(args.ongoing_project)["-o"]["--ongoing"](
          "If this project is currently ongoing? This flag is used to "
          "update the year in the Source headers.")
          .optional();

  auto result = cli.parse({argc, argv});

  if (!result) {
    std::cerr << "Error in command line: " << result.errorMessage()
              << std::endl;
    exit(1);
  } else if (args.showHelp) {
    std::cout << cli;
  } else if (args.initiate) {
    using namespace licenser::licenses;

    auto license_enum = License::enum_from_name(args.license);
    auto license_ptr = License::make_license(license_enum);
    licenser::LicenseWriter writer(std::move(license_ptr));
    writer.write();
    std::cout << "Initiated LICENSE file in directory " << writer.cwd()
              << std::endl;
  } else if (args.update) {
  } else {
    std::cout << cli;
  }
  return 0;
}