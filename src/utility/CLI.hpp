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
#include <iostream>

#include "ArchInfo.hpp"
#include "CommandLineArgs.hpp"
#include "SubcommandMode.hpp"
#include "Util.hpp"
#include "clipp.h"
namespace licenser {
auto get_cli(licenser::ApplicationArgs &args, SubCommandMode &selected,
             std::vector<std::string> &wrong) {
  auto initMode = (
      clipp::command("init").set(selected, SubCommandMode::init)
      ,
      clipp::opt_value(/* lambdas::is_exist, */ "path", args.commandLineArgs.path)
        //    .if_blocked([] { std::cout << "Make sure path exists and is a directory\n"; exit(-1); })
           .if_repeated([] { std::cout<<"Only one path allowed at one time\n"; exit(-1);})
      ,
      (clipp::option("-a", "--author") & clipp::opt_value(lambdas::is_non_empty, "author", args.author)
            .if_blocked([]{ std::cout<<"Author cannot be empty\n"; exit(-1); })
            .if_repeated([]{ std::cout<<"Author cannot be repeated. Multiple author should be separated with comma"; exit(-1); }))
           % "sets the name of the author"
      ,
      (clipp::option("-e", "--email") & clipp::opt_value(lambdas::is_valid_email, "email", args.email)
            .if_repeated([]{ std::cout<<"Email cannot be repeated. Multiple email can should be separated with comma"; exit(-1);})
            .if_blocked([]{ std::cout<<"Not valid email address."; exit(-1);})) 
           % "sets the email of the author"
      ,
      (clipp::option("-y", "--year") &
        clipp::opt_value(lambdas::is_valid_year, "year", args.year)
             .if_blocked([]{std::cout<<"Year must not exceed current year or preceed 1900"; exit(-1);})
             .if_repeated([]{std::cout<<"Year should not be repeated\n"; exit(-1);})) 
             % "starting year of project"
       ,
       (clipp::option("-l", "--license") &
        clipp::opt_value(lambdas::is_valid_license, "license", args.license)
               .if_blocked([]{std::cout<<"license must be valid short name of license. Run licenser list-license for shortnames\n";exit(-1);})
               .if_repeated([]{std::cout<<"license must not be repeated\n";exit(-1);})) 
             % "sets the license for the project"
       ,
       (clipp::option("-p", "--project") &
        clipp::opt_value(lambdas::is_non_empty, "project", args.project)
                .if_blocked([]{std::cout<<"Project name must be non-empty string\n";exit(-1);})
                .if_repeated([]{std::cout<<"Project must not be repeated\n"; exit(-1);}))
              % "sets the name of the project"
        ,
       clipp::option("-o", "--ongoing")
           .set(args.ongoing_project, true)
           .doc("specifies if project is ongoing")
    );

  auto updateMode = (
      
      clipp::command("update").set(selected, SubCommandMode::update),
      clipp::opt_value(/* lambdas::is_exist,  */"path", args.commandLineArgs.path)
            .if_repeated([]{std::cout<<"Only one update path at a time.\n";exit(-1);})
            // .if_blocked([]{std::cout<<"update path must be a valid directory\n";exit(-1);})
       ,
      clipp::option("-m", "--prefer-multiline")
           .set(args.commandLineArgs.prefer_multiline, true)
           .doc("use multiline comment header if language allows")
    );
  
  auto checkMode =(
      clipp::command("check").set(selected, SubCommandMode::check),
      clipp::opt_value(/* lambdas::is_exist, */ "path", args.commandLineArgs.path)
            .if_repeated([]{std::cout<<"Only one update path at a time.\n";exit(-1);})
            // .if_blocked([]{std::cout<<"update path must be a valid directory\n";exit(-1);})
    );


  return ((initMode | updateMode | checkMode |
           clipp::command("help").set(selected, SubCommandMode::help) |
           clipp::command("list-license")
               .set(selected, SubCommandMode::listLicense)),

          clipp::option("-v", "--version")
              .call([]() {
    std::cout << "Licenser version " << VERSION_MAJOR << "." << VERSION_MINOR
              << VERSION_PATCH << "\n";
    std::cout << "Licensed under GNU General Public License 3\n";
    std::cout << "Target Architecture : " << licenser::get_arch() << "\n";
    exit(0);
              })
              .doc("shows version and extra information"),
          clipp::any_other(wrong));
}
}  // namespace licenser
