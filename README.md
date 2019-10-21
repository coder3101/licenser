# Licenser : A License Manager CLI

![](https://img.shields.io/badge/C%2B%2B-17-yellowgreen) ![](https://img.shields.io/badge/version-0.10-red)![](https://img.shields.io/badge/license-GPLv3-blue) ![](https://img.shields.io/badge/application-cli-brightgreen) ![](https://img.shields.io/badge/platform-linux%20%7C%20macOs%20%7C%20windows-green)

Licenser is a free, Simple, Cross-Platform license manager CLI tool. It can quickly add, update and validate the license headers in your source files and LICENSE file.


## Build 

[![Build Status](https://dev.azure.com/ashar786khan/licenser/_apis/build/status/coder3101.licenser?branchName=master)](https://dev.azure.com/ashar786khan/licenser/_build/latest?definitionId=1&branchName=master)

##### `master`

| Build   | Linux GCC-8                                                  | Linux Clang-6                                                | VS 17 32 bit                                                 | VS 17 64 bit                                                 | XCode 11                                                     |
| ------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| Release | [![Build Status](https://dev.azure.com/ashar786khan/licenser/_apis/build/status/coder3101.licenser?branchName=master&jobName=Linux&configuration=Linux%20GCC-8%20Release)](https://dev.azure.com/ashar786khan/licenser/_build/latest?definitionId=1&branchName=master) | [![Build Status](https://dev.azure.com/ashar786khan/licenser/_apis/build/status/coder3101.licenser?branchName=master&jobName=Linux&configuration=Linux%20Clang-6%20Release)](https://dev.azure.com/ashar786khan/licenser/_build/latest?definitionId=1&branchName=master) | [![Build Status](https://dev.azure.com/ashar786khan/licenser/_apis/build/status/coder3101.licenser?branchName=master&jobName=Windows&configuration=Windows%2032-bit%20Release)](https://dev.azure.com/ashar786khan/licenser/_build/latest?definitionId=1&branchName=master) | [![Build Status](https://dev.azure.com/ashar786khan/licenser/_apis/build/status/coder3101.licenser?branchName=master&jobName=Windows&configuration=Windows%2064-bit%20Release)](https://dev.azure.com/ashar786khan/licenser/_build/latest?definitionId=1&branchName=master) | [![Build Status](https://dev.azure.com/ashar786khan/licenser/_apis/build/status/coder3101.licenser?branchName=master&jobName=macOS&configuration=macOS%20Release)](https://dev.azure.com/ashar786khan/licenser/_build/latest?definitionId=1&branchName=master) |
| Debug   | [![Build Status](https://dev.azure.com/ashar786khan/licenser/_apis/build/status/coder3101.licenser?branchName=master&jobName=Linux&configuration=Linux%20GCC-8%20Debug)](https://dev.azure.com/ashar786khan/licenser/_build/latest?definitionId=1&branchName=master) | [![Build Status](https://dev.azure.com/ashar786khan/licenser/_apis/build/status/coder3101.licenser?branchName=master&jobName=Linux&configuration=Linux%20Clang-6%20Debug)](https://dev.azure.com/ashar786khan/licenser/_build/latest?definitionId=1&branchName=master) | [![Build Status](https://dev.azure.com/ashar786khan/licenser/_apis/build/status/coder3101.licenser?branchName=master&jobName=Windows&configuration=Windows%2032-bit%20Debug)](https://dev.azure.com/ashar786khan/licenser/_build/latest?definitionId=1&branchName=master) | [![Build Status](https://dev.azure.com/ashar786khan/licenser/_apis/build/status/coder3101.licenser?branchName=master&jobName=Windows&configuration=Windows%2064-bit%20Debug)](https://dev.azure.com/ashar786khan/licenser/_build/latest?definitionId=1&branchName=master) | [![Build Status](https://dev.azure.com/ashar786khan/licenser/_apis/build/status/coder3101.licenser?branchName=master&jobName=macOS&configuration=macOS%20Debug)](https://dev.azure.com/ashar786khan/licenser/_build/latest?definitionId=1&branchName=master) |



## Usage
> Coming Soon

## Pre-built Binaries
> Coming Soon


## Building from Source

- **Linux**
  Here is the recipe for compiling the project
  
  ````bash
  git clone https://github.com/coder3101/licenser &&
  git submodule update --init --recursive &&
  mkdir build && cd build &&
  cmake -DENABLE_TESTS=Off .. &&
  ninja -j4
  ````
  

  Enjoy the food ! located at `${PROJECT_ROOT}/build/licenser`

- **macOS**

  > Note : At least macOS 10.15 or higher is required with X Code 11 or above

  - Make sure that CMake picks Apple Clang 11.0 as the compiler.
  - Set the compiler by exporting `CC` and `CXX`environment variables before generating build file
  - Now Go ahead and follow the same steps as mentioned in the Linux Section

- **Windows**

  >  Visual Studio 2017 or higher is required with CMake at least 3.12

  - Clone the Project and Its submodules as mentioned in the above steps of Linux
  - `cmake -G "Visual Studio 17" -DENABLE_TESTS=Off .`
  - `cmake --build . --config Release` or `msbuild licenser.sln`

## License

Distributed under [GNU General Public License Version 3.0](https://github.com/coder3101/licenser/blob/master/LICENSE)