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


#include "HeaderWriter.hpp"

#include "CommentBuilder.hpp"
#include "ConfigReader.hpp"
#include "Extensions.hpp"
#include "HeaderRemover.hpp"
#include "License.hpp"
#include "PreProcessor.hpp"
#define TEMP_FILE_PREFIX "temp_"

namespace licenser::writer {
HeaderWriter::HeaderWriter(std::string path) {
  std::filesystem::path p(path);
  this->old_path = p.string();
  std::string fname = p.filename().string();
  this->new_temp_path = p.replace_filename(TEMP_FILE_PREFIX + fname).string();
}
bool HeaderWriter::write(licenser::ApplicationArgs const& arg, bool multiline) {
  std::filesystem::path xp(this->old_path);

  if (xp.filename() == LICENSER_CONFIG_NAME || xp.filename() == "LICENSE")
    return true;

  if (xp.has_extension()) {
    std::string extension = xp.extension().string();
    auto commenter = licenser::comments::Extensions::to_lang(extension);
    if (commenter == nullptr) {
      this->error_cause = "the file extension was not identified";
      return false;
    }

    auto ename = licenser::licenses::License::enum_from_name(arg.license);
    if (ename == licenser::licenses::UNKNOWN) {
      this->error_cause = "the license specified in configuration is not valid";
      return false;
    }

    auto license = licenser::licenses::License::make_license(ename);
    if (license == nullptr) {
      this->error_cause =
          "make_license returned nullptr? Cannot allocate memory on heap?";
      return false;
    }

    std::string raw =
        licenser::Preprocessor::parse(license->header_to_string(), arg);

    std::string header_ = licenser::comments::CommentBuilder::from_header(
        std::move(commenter), raw, multiline);

    old_reader.open(this->old_path);
    new_writer.open(this->new_temp_path);

    if (!new_writer.good()) {
      this->error_cause =
          "licenser cannot create a new file. Do you have write permission here?";
      return false;
    }

    std::string full_file;
    std::string line;

    if (!old_reader.good()) {
      this->error_cause =
          "licenser cannot read source file. Do you have read permission here?";
      std::filesystem::remove(std::filesystem::path(this->new_temp_path));
      return false;
    }
    while (std::getline(old_reader, line)) {
      full_file += line;
      full_file += '\n';
    }

    std::string pure_code = HeaderRemover::from_str(full_file, extension);
    std::string final_code = header_ + pure_code;
    new_writer.write(final_code.c_str(), final_code.size());

    std::filesystem::remove(std::filesystem::path(this->old_path));
    std::filesystem::rename(std::filesystem::path(this->new_temp_path),
                            std::filesystem::path(this->old_path));
    old_reader.close();
    new_writer.close();
    return true;
  }
  this->error_cause =
      "it has no file extension. Add it to .licenserignore to supress this "
      "warning";
  return false;
}

std::string HeaderWriter::get_error_cause() const noexcept {
  return this->error_cause;
}
HeaderWriter::~HeaderWriter() {
  if (old_reader.is_open()) old_reader.close();
  if (new_writer.is_open()) new_writer.close();
}
}  // namespace licenser::writer
