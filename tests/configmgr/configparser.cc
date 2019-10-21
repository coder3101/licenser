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


#define CATCH_CONFIG_MAIN
#include "ConfigParser.hpp"
#include <string>
#include <vector>
#include "catch.hpp"

TEST_CASE("trim_start", "[Config Parser]") {
  std::string Q1 = "    Hello";
  std::string Q2 = "No spaced";
  std::string Q3 = "  -Something";
  std::string Q4 = " 5 %%K55";
  std::string Q5 = " ,,Neptune  \n";
  std::string Q6 = "";

  std::string A1 = "Hello";
  std::string A2 = "No spaced";
  std::string A3 = "-Something";
  std::string A4 = "5 %%K55";
  std::string A5 = ",,Neptune  \n";
  std::string A6 = "";
  using namespace licenser::configmgr;

  CHECK(ConfigParser::trim_start(Q1) == A1);
  CHECK(ConfigParser::trim_start(Q2) == A2);
  CHECK(ConfigParser::trim_start(Q3) == A3);
  CHECK(ConfigParser::trim_start(Q4) == A4);
  CHECK(ConfigParser::trim_start(Q5) == A5);
  CHECK(ConfigParser::trim_start(Q6) == A6);
}

TEST_CASE("trim_end", "[ConfigParser]") {
  using namespace licenser::configmgr;
  std::string Q1 = "    Hello   \n";
  std::string Q2 = "No spaced  \n";
  std::string Q3 = "  -Something   \n";
  std::string Q4 = " 5 %%K55  \n";
  std::string Q5 = " ,,Neptune\n";
  std::string Q6 = "No newline  ";
  std::string Q7 = "";

  std::string A1 = "    Hello\n";
  std::string A2 = "No spaced\n";
  std::string A3 = "  -Something\n";
  std::string A4 = " 5 %%K55\n";
  std::string A5 = " ,,Neptune\n";
  std::string A6 = "No newline";
  std::string A7 = "";

  CHECK(ConfigParser::trim_end(Q1) == A1);
  CHECK(ConfigParser::trim_end(Q2) == A2);
  CHECK(ConfigParser::trim_end(Q3) == A3);
  CHECK(ConfigParser::trim_end(Q4) == A4);
  CHECK(ConfigParser::trim_end(Q5) == A5);
  CHECK(ConfigParser::trim_end(Q6) == A6);
  CHECK(ConfigParser::trim_end(Q7) == A7);
}

TEST_CASE("starts_with", "[ConfigParser]"){
  std::string Q1 = "  # This should be a comment";
  std::string Q2 = " ! Funny text";
  std::string Q3 = "Nothing is amaing";
  std::string Q4 = "  \nNothing ";

  using namespace licenser::configmgr;
  CHECK(ConfigParser::starts_with(Q1, '#'));
  CHECK(!ConfigParser::starts_with(Q1, '!'));

  CHECK(ConfigParser::starts_with(Q2, '!'));
  CHECK(!ConfigParser::starts_with(Q2, ' '));
  
  CHECK(ConfigParser::starts_with(Q3, 'N'));
  CHECK(!ConfigParser::starts_with(Q3, 'n'));

  CHECK(ConfigParser::starts_with(Q4, '\n'));
  CHECK(!ConfigParser::starts_with(Q4, 'N'));
}

TEST_CASE("split", "[ConfigParser]"){
  std::string Q1 = "author=Ashar";
  std::string Q2 = "year=2015";
  std::string Q3 = "Month=January";
  std::string Q4 = "";
  std::string Q5 = "nothing=";
  std::string Q6 = "somthing = good is the result";
  std::string Q7 = "name = Ashar Khan";
  std::string Q8 = "Some two line = meet in the middle";
  std::string Q9 = "=Min";
  
  using out_t = std::pair<std::string, std::string>;
  out_t A1 = {"author", "Ashar"};
  out_t A2 = {"year", "2015"};
  out_t A3 = {"Month", "January"};
  out_t A4 = {"",""};
  out_t A5 = {"nothing", ""};
  out_t A6 = {"somthing", "good is the result"};
  out_t A7 = {"name", "Ashar Khan"};
  out_t A8 = {"Some two line", "meet in the middle"};
  out_t A9 = {"","Min"};

  using namespace licenser::configmgr;

  CHECK(ConfigParser::split(Q1) == A1);
  CHECK(ConfigParser::split(Q2) == A2);
  CHECK(ConfigParser::split(Q3) == A3);
  CHECK(ConfigParser::split(Q4) == A4);
  CHECK(ConfigParser::split(Q5) == A5);
  CHECK(ConfigParser::split(Q6) == A6);
  CHECK(ConfigParser::split(Q7) == A7);
  CHECK(ConfigParser::split(Q8) == A8);
  CHECK(ConfigParser::split(Q9) == A9);
}

TEST_CASE("append_to_args", "[ConfigParser]"){

}
