/*
* Copyright (C) 2019- Mohammad Ashar Khan ashar786khan@gmail.com
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


#define CATCH_CONFIG_MAIN
#include "CommandLineArgs.hpp"
#include "PreProcessor.hpp"
#include "catch.hpp"

std::string this_year() {
  auto cur_time = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(cur_time);
  auto tm_ptr = std::localtime(&time);
  return std::to_string(tm_ptr->tm_year + 1900);
}
TEST_CASE("Tests Preprocessor Base", "[preprocessor]") {
  using namespace licenser;

  ApplicationArgs args;
  args.author = "Ashar";
  args.email = "ashar786khan@archlinux.email";
  args.project = "Licenser";
  args.year = 2018;
  args.ongoing_project = true;  // Required if %YEAR_TO% should be replaced

  std::string format =
      R"(My name is %AUTHOR% I started %PROJECT% in %YEAR_FROM%.
      You can reach me on %EMAIL%. This year is %YEAR_TO%)";

  std::string ans = Preprocessor::parse(format, args);
  std::string expected = R"(My name is Ashar I started Licenser in 2018.
      You can reach me on ashar786khan@archlinux.email. This year is )";
  CHECK(ans == (expected + this_year()));
}

TEST_CASE("Test Preprocessor Corner", "[preprocessor]") {
  using namespace licenser;

  ApplicationArgs args;
  args.author = "Ashar Khan";
  args.email = "ashar786khan@archlinux.email";
  args.project = "Licenser";
  args.year = 2018;
  args.ongoing_project = true;  // Required if %YEAR_TO% should be replaced

  std::string Q1 = R"(%YEAR_FROM%-%YEAR_TO%)";
  std::string Q2 = R"(%YEAR_FROM%%YEAR_TO%)";
  std::string Q3 = R"(%AUTHOR% has 75% of %something%)";
  std::string Q4 = R"(No placeholders here)";
  std::string Q5 = R"KK(I have %%%%% (5 times) in the middle of %PROJECT%)KK";
  std::string Q6 = R"(%AUTHOr% mis-spelled something)";
  std::string Q7 = R"(This is good %CASE)";
  std::string Q8 = R"(How about %this)";

  std::string A1 = R"(2018-)" + this_year();
  std::string A2 = R"(2018)" + this_year();
  std::string A3 = R"(Ashar Khan has 75% of %something%)";
  std::string A4 = R"(No placeholders here)";
  std::string A5 = R"KK(I have %%%%% (5 times) in the middle of Licenser)KK";
  std::string A6 = R"(%AUTHOr% mis-spelled something)";
  std::string A7 = R"(This is good %CASE)";
  std::string A8 = R"(How about %this)";

  CHECK(Preprocessor::parse(Q1, args) == A1);
  CHECK(Preprocessor::parse(Q2, args) == A2);
  CHECK(Preprocessor::parse(Q3, args) == A3);
  CHECK(Preprocessor::parse(Q4, args) == A4);
  CHECK(Preprocessor::parse(Q5, args) == A5);
  CHECK(Preprocessor::parse(Q6, args) == A6);
  CHECK(Preprocessor::parse(Q7, args) == A7);
  CHECK(Preprocessor::parse(Q8, args) == A8);

}
