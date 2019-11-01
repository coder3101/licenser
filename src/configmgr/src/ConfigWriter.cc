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


#include "ConfigWriter.hpp"

#include <filesystem>
#include <fstream>

#define LICENSER_RC_DECORATOR \
  "# ========================================================\n"
namespace licenser::configmgr {
bool ConfigWriter::write(ApplicationArgs app, std::string path) {
  std::filesystem::path p(path);
  p.append(LICENSER_CONFIG_NAME);
  path = p.string();
  std::ofstream stream(path);
  if (!stream.is_open() || !stream.good()) return false;
  stream.seekp(0, std::ios_base::beg);

  // Todo(coder3101) : Maybe remove these \n with something platform independent
  stream << "# NOTES FOR END-USER\n";

  stream << "# You can manually edit this file to apply changes using "
            "licenser update\n";
  stream << "# To put a comment use a # before the begining of a line.\n";
  stream << "# If any value contains space like author name, project name\n";
  stream << "# Please do not put \" around the those values\n\n";

  stream << "# This is the name of the project author\n";
  stream << "# You can separate the authors by putting \",\" between names.\n";
  stream << "# Like author=Naruto, Sasuke, Sakura\n";
  stream << "# You can also write an Organization name here like Tensorflow "
            "Team or Similar\n";
  stream << LICENSER_RC_DECORATOR;
  stream << "author=" << app.author << '\n';
  stream << LICENSER_RC_DECORATOR;

  stream << "\n# This is the email of the author (optional)\n";
  stream << "# It is used in License headers. It can be comma separated for "
            "multiple values\n";
  stream << "# You can leave it empty by writing email= \n";
  stream << LICENSER_RC_DECORATOR;
  stream << "email=" << app.email << '\n';
  stream << LICENSER_RC_DECORATOR;

  stream << "\n# This is the short name for the license.\n";
  stream << "# We follow standard shortnames for the Licenses.\n";
  stream << "# This is case-insensitive and shortname spaces are replaced with "
            "\"_\"\n";
  stream << "# Like Creative Commons Version 3 shortname is CC By 3, Here it "
            "will be CC_BY_3\n";
  stream << "# Before changing this value please ensure that updated value is "
            "indeed a license shortname\n";
  stream << "# A list of all the shortnames can be retrieved by running "
            "licenser list-license\n";
  stream << LICENSER_RC_DECORATOR;  
  stream << "license=" << app.license << '\n';
  stream << LICENSER_RC_DECORATOR;

  stream << "\n# This value tells that the project is still under active and \n";
  stream << "# this is used to set the period of the project in the license "
            "header\n";
  stream << "# If a project was started in 2018 and is still going in 2019, "
            "setting this\n";
  stream << "# value to true makes sure that in license header we write "
            "2018-2019\n";
  stream << LICENSER_RC_DECORATOR;
  stream << "ongoing_project=" << (app.ongoing_project ? "true" : "false")
         << '\n';
  stream << LICENSER_RC_DECORATOR;

  stream << "\n# This is the name of the project, It is required and should be "
            "non-empty\n";
  stream << "# This value is also used to write about project in the license "
            "header.\n";
  stream << LICENSER_RC_DECORATOR;
  stream << "project=" << app.project << '\n';
  stream << LICENSER_RC_DECORATOR;

  stream << "\n# This is the starting year of your project\n";
  stream << "# It must be after 1900 and cannot exceed your current year\n";
  
  stream << LICENSER_RC_DECORATOR;
  stream << "year=" << app.year << '\n';
  stream << LICENSER_RC_DECORATOR;
  stream.close();
  return true;
}
}  // namespace licenser::configmgr
