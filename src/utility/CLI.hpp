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
#include "CommandLineArgs.hpp"
#include "Util.hpp"
#include "lyra/lyra.hpp"
namespace licenser {
auto get_lyra_cli(licenser::ApplicationArgs &args) {
  return lyra::help(args.commandLineArgs.showHelp) |

         lyra::opt(args.commandLineArgs.initiate)["-i"]["--init"](
             "Initiates a Simple License Configuration") |

         lyra::opt(args.commandLineArgs.update)["-u"]["--update"](
             "Updates Source files with configuration changes") |

         lyra::opt(args.commandLineArgs.show_licenses)["--show_licenses"](
             "Shows all the predefined licenses and their shortnames") |

         lyra::opt(args.license, "license_shortname")["-l"]["--license"](
             "The short name for license separated by underscore in case "
             "of multiwords")
             .optional()
             .choices(licenser::lambdas::is_valid_license) |

         lyra::opt(args.email, "email@domail.com")["-e"]["--email"](
             "The email that should appear on source headers. For multiple "
             "users you can separate them by \" , \" ")
             .optional()
             .choices(licenser::lambdas::is_valid_email) |

         lyra::opt(args.project, "project_name")["-p"]["--project"](
             "The name of the project that will appear in license headers")
             .optional()
             .choices(licenser::lambdas::is_non_empty) |

         lyra::opt(args.year, "year")["-y"]["--year"](
             "The starting year of the project that will appear in the license "
             "header")
             .optional()
             .choices(licenser::lambdas::is_valid_year) |

         lyra::opt(args.author, "author_name")["-a"]["--author"](
             "The author names or organization name that will be displayed in "
             "the "
             "header. You can separate multiple by \" , \"")
             .optional() |

         lyra::opt(args.ongoing_project)["-o"]["--ongoing"](
             "If this project is currently ongoing? This flag is used to "
             "update the year in the Source headers.")
             .optional()
             .choices(licenser::lambdas::is_non_empty) |

         lyra::opt(args.commandLineArgs
                       .prefer_multiline)["-ml"]["--prefer-multiline"](
             "If this flag is set when calling --update the license headers "
             "are writer with multi-line comment if langauag allows it.")
             .optional() |

         lyra::opt(args.commandLineArgs.showVersion)["-v"]["--version"](
             "Shows the version of the application")
             .optional();
}
}  // namespace licenser
