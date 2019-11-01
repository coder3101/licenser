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


#define VERSION_MAJOR 0
#define VERSION_MINOR 5
#define VERSION_PATCH 0

#include <iomanip>
#include <iostream>

#include "CLI.hpp"
#include "CommandLineArgs.hpp"
#include "CommentBuilder.hpp"
#include "ConfigCommand.hpp"
#include "ConfigReader.hpp"
#include "ConfigWriter.hpp"
#include "Extensions.hpp"
#include "HeaderWriter.hpp"
#include "LicenseWriter.hpp"
#include "RecursiveFileIterator.hpp"
#include "SigHandlers.hpp"
#include "SubcommandMode.hpp"
#include "Util.hpp"
#include "clipp.h"

int main(int argc, char* argv[]) {
  licenser::RegisterInterruptSignalHandler();
  licenser::ApplicationArgs args;
  std::vector<std::string> wrong;
  auto selected = licenser::SubCommandMode::help;
  auto cli = licenser::get_cli(args, selected, wrong);
  auto res = clipp::parse(argc, argv, cli);
  if (res) {
    switch (selected) {
      case licenser::SubCommandMode::init: {
        std::string maybe_path = args.commandLineArgs.path;
        if (maybe_path.empty())
          maybe_path = ".";
        else if (!licenser::lambdas::is_exist(maybe_path)) {
          std::cout << "Directory is not reachable or exists.\n";
          exit(-1);
        }
        auto res = licenser::configmgr::ConfigReader::exists(maybe_path);
        if (res) {
          std::cout << "A Configuration file named " << LICENSER_CONFIG_NAME
                    << " already exists\n";
          exit(1);
        } else {
          std::string email_git = licenser::configmgr::CommandRunner::exec(
              "git config --get user.email");
          std::string name_git = licenser::configmgr::CommandRunner::exec(
              "git config --get user.name");

          std::cout << "Creating a Configuration File in " << maybe_path
                    << " Directory\n";

          if (args.author.empty() && name_git.empty()) {
            while (args.author.empty()) {
              std::cout << "Who is the author (required) : ";
              std::getline(std::cin, args.author);
              if (args.author.empty())
                std::cout << "Author name cannot be empty. Try again\n";
            }
          } else if(args.author.empty()){
            std::cout << "Who is the author (required) [Default: " << name_git
                      << " ] : ";
            std::getline(std::cin, args.author);
            if (args.author.empty()) {
              args.author = name_git;
              std::cout << "Author set to : " << args.author << "\n";
            }
          }

          if (args.email.empty()) {
            do {
              std::cout << "An email of the author (optional) [Default: "
                        << email_git << " ] [s to skip] : ";
              std::getline(std::cin, args.email);
              if (args.email == "s" || args.email == "S") {
                args.email.clear();
                break;
              } else if (args.email.empty()) {
                args.email = email_git;
                std::cout << "Email set to : " << args.email << "\n";
                break;
              }
              if (!licenser::lambdas::is_valid_email(args.email)) {
                std::cout
                    << "Not a valid email address. Try again or s to skip\n";
              }
            } while (!licenser::lambdas::is_valid_email(args.email));
          }

          if (args.project.empty()) {
            while (args.project.empty()) {
              std::cout << "Name of the project (required) : ";
              std::getline(std::cin, args.project);
              if (args.project.empty())
                std::cout << "Project name cannot be empty. Try again\n";
            }
          }

          if (args.year == 0) {
            while (args.year < 1900) {
              std::cout << "When did project started : ";
              std::string num;
              std::getline(std::cin, num);
              if (!licenser::lambdas::is_valid_year(num)) {
                std::cout << "Not a valid year. Try again\n";
                continue;
              } else
                args.year = std::stoi(num);  // Guaranteed to be safe.
              if (args.year > licenser::this_year()) {
                std::cout << "Start year cannot be more than present year\n";
                args.year = 0;
              }
            }
          }

          if (!args.ongoing_project && args.year < licenser::this_year()) {
            std::string res;
            while (res.empty()) {
              std::cout << "Project was started in past. Is it still being "
                           "maintained "
                           "(Y/N)? : ";
              std::getline(std::cin, res);
              if (args.author.empty())
                std::cout << "Response cannot be empty\n";
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
              if (f)
                std::cout
                    << "That didn't matched with any License. Try again\n";
            }
          }

          if (args.year == licenser::this_year()) args.ongoing_project = true;

          licenser::configmgr::ConfigWriter::write(args);
          licenser::writer::LicenseWriter writer{};
          writer.write(args);
          std::cout << "Initiated LICENSE file in directory " << maybe_path
                    << std::endl;
        }
        return 0;
      }
      case licenser::SubCommandMode::update: {
        using namespace licenser::configmgr;
        std::string maybe_path = args.commandLineArgs.path;
        if (maybe_path.empty()) maybe_path = ".";
        if (!ConfigReader::exists(maybe_path)) {
          std::cout << "Error directory does not have .licenserrc file\n";
          exit(1);
        }
        ConfigReader reader(maybe_path);
        RecursiveFileIterator iter(reader);

        int count = 0;
        auto total_touch = iter.iterate([args, &count](auto pth, auto config,
                                                       auto cust_hdr) {
          licenser::writer::HeaderWriter h(pth);
          if (!h.write(config, cust_hdr, args.commandLineArgs.prefer_multiline))
            count++, std::cout << "[WARNING] Skipped " << pth << " because "
                               << h.get_error_cause() << std::endl;
          // TODO(coder3101): Maybe add a progress bar here
        });
        std::cout << "Update Affected " << total_touch - count << " Files\n";
        return 0;
      }
      case licenser::SubCommandMode::check:
        break;
      case licenser::SubCommandMode::listLicense: {
        using namespace licenser::licenses;
        std::cout << std::setw(30) << std::left;
        std::cout << "Short Name ";
        std::cout << std::setw(60) << std::left;
        std::cout << "   License Name";
        std::cout << '\n' << std::endl;
        for (int start = LicenseType::AGPLv3; start != LicenseType::UNKNOWN;
             start++) {
          auto enum_type = static_cast<LicenseType>(start);
          std::cout << std::setw(30) << std::left;
          std::cout << "   " + License::short_name_from_enum(enum_type);
          std::cout << std::setw(60) << std::left;
          std::cout << License::name_from_enum(enum_type);
          std::cout << std::endl;
        }
        return 0;
      }
      case licenser::SubCommandMode::help: {
        std::cout << clipp::make_man_page(cli, "licenser");
        return 0;
      }
    }
  } else if (!wrong.empty()) {
    for (auto e : wrong) std::cerr << "Unexpected argument : " << e << '\n';
    exit(-1);
  }
  return 0;
}
