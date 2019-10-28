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
#include <string>
namespace licenser {
struct ApplicationArgs {
  ApplicationArgs() : ongoing_project(false) {}

  struct CommandLineArgs {
    CommandLineArgs()
        : showHelp(false),
          initiate(false),
          update(false),
          showVersion(false),
          show_licenses(false),
          prefer_multiline(false) {}
    bool showHelp;
    bool initiate;
    bool update;
    bool showVersion;
    bool show_licenses;
    bool prefer_multiline;
  };
  bool ongoing_project;
  std::string author;
  std::string email;
  unsigned int year = 0;
  std::string license;
  std::string project;

  CommandLineArgs commandLineArgs;
};
}  // namespace licenser
