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
#define VERSION_MINOR 2
#define VERSION_PATCH 0

#include <iomanip>
#include <iostream>

#include "ArchInfo.hpp"
#include "CLI.hpp"
#include "CommandLineArgs.hpp"
#include "CommentBuilder.hpp"
#include "ConfigReader.hpp"
#include "ConfigWriter.hpp"
#include "Extensions.hpp"
#include "HeaderWriter.hpp"
#include "LicenseWriter.hpp"
#include "RecursiveFileIterator.hpp"
#include "SigHandlers.hpp"
#include "Util.hpp"

int main(int argc, const char** argv) {
  licenser::RegisterInterruptSignalHandler();
  licenser::ApplicationArgs args;
  auto cli = licenser::get_lyra_cli(args);
  auto result = cli.parse({argc, argv});

  // *************************** ON ERROR ***********************************
  if (!result) {
    std::cerr << "Error in command line: " << result.errorMessage()
              << std::endl;
    exit(1);
  }
  // **************************** ON VERSION ********************************
  else if (args.commandLineArgs.showVersion) {
    std::cout << "Licenser version " << VERSION_MAJOR << "." << VERSION_MINOR
              << VERSION_PATCH << "\n";
    std::cout << "Licensed under GNU General Public License 3\n";
    std::cout << "Target Architecture : " << licenser::get_arch() << "\n";
  }
  // *************************** ON HELP ************************************
  else if (args.commandLineArgs.showHelp) {
    std::cout << cli;
  }
  //**************************** ON INIT ************************************
  else if (args.commandLineArgs.initiate) {
    auto res = licenser::configmgr::ConfigReader::exists(".");
    if (res) {
      std::cout << "A Configuration file named " << LICENSER_CONFIG_NAME
                << " already exists\n";
      exit(1);
    } else {
      std::cout
          << "Creating a Configuration File in Current Working Directory\n";

      if (args.author.empty()) {
        while (args.author.empty()) {
          std::cout << "Who is the author (required) : ";
          std::getline(std::cin, args.author);
          if (args.author.empty())
            std::cout << "Author name cannot be empty. Try again\n";
        }
      }

      if (args.email.empty()) {
        do {
          std::cout << "An email of the author (optional) : ";
          std::getline(std::cin, args.email);
          if (!licenser::lambdas::is_valid_email(args.email)) {
            std::cout
                << "Not a valid email address. Try again or leave empty\n";
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
          std::cout
              << "Project was started in past. Is it still being maintained "
                 "(Y/N)? : ";
          std::getline(std::cin, res);
          if (args.author.empty()) std::cout << "Response cannot be empty\n";
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
            std::cout << "That didn't matched with any License. Try again\n";
        }
      }

      if (args.year == licenser::this_year()) args.ongoing_project = true;

      licenser::configmgr::ConfigWriter::write(args);
      licenser::writer::LicenseWriter writer{};
      writer.write(args);
      std::cout << "Initiated LICENSE file in directory " << writer.cwd()
                << std::endl;
    }
  }

  // **************************** ON SHOW_LICENSE ****************************

  else if (args.commandLineArgs.show_licenses) {
    std::cout << std::setw(30) << std::left;
    std::cout << "Short Name ";
    std::cout << std::setw(60) << std::left;
    std::cout << "   License Name";
    std::cout << '\n' << std::endl;
    for (int start = licenser::licenses::LicenseType::AGPLv3;
         start != licenser::licenses::LicenseType::UNKNOWN; start++) {
      auto enum_type = static_cast<licenser::licenses::LicenseType>(start);
      std::cout << std::setw(30) << std::left;
      std::cout << "   " + licenser::licenses::License::short_name_from_enum(
                               enum_type);
      std::cout << std::setw(60) << std::left;
      std::cout << licenser::licenses::License::name_from_enum(enum_type);
      std::cout << std::endl;
    }
    return 0;
  }

  // ***************************** ON UPDATE **********************************
  else if (args.commandLineArgs.update) {
    if (!licenser::configmgr::ConfigReader::exists()) {
      std::cout << "Error, this directory does not have .licenserrc file\n";
      exit(1);
    }
    licenser::configmgr::ConfigReader reader;
    licenser::configmgr::RecursiveFileIterator iter(reader);

    int count = 0;
    auto total_touch =
        iter.iterate([args, &count](auto pth, auto config, auto cust_hdr) {
          licenser::writer::HeaderWriter h(pth);
          if (!h.write(config, cust_hdr, args.commandLineArgs.prefer_multiline))
            count++, std::cout << "[WARNING] Skipped " << pth << " because "
                               << h.get_error_cause() << std::endl;
        });

    std::cout << "Update Affected " << total_touch - count << " Files\n";
  }
  // ***************************** ON UNKNOWN *********************************
  else {
    std::cout << "Nothing to do. For all commands please run with --help\n";
  }
  return 0;
}
