# QRX
[VCV Rack](https://vcvrack.com) plugin.

*Under development!*

---
![Version](https://img.shields.io/badge/Version-1.dev.0-blue)
[![conan vcvrack-sdk](https://img.shields.io/badge/conan-vcvrack--sdk%2F1.1.6%40vcvrack%2Fstable-blue)](https://bintray.com/qno/conan-public/vcvrack-sdk%3Avcvrack/1.1.6%3Astable)
[![GitHub release (latest by date including pre-releases)](https://img.shields.io/github/v/release/qno/QRX?include_prereleases)](https://github.com/qno/QRX/releases)
[![GitHub All Releases](https://img.shields.io/github/downloads/qno/QRX/total)](https://github.com/qno/QRX/releases)

[![Build Status](https://dev.azure.com/qnohot/qnohot/_apis/build/status/qno.QRX?branchName=feature%2Fcreate_cvwizard)](https://dev.azure.com/qnohot/qnohot/_build/latest?definitionId=28&branchName=feature%2Fcreate_cvwizard)
[![Azure DevOps tests](https://img.shields.io/azure-devops/tests/qnohot/qnohot/28)](https://dev.azure.com/qnohot/qnohot/_test/analytics?definitionId=28&contextType=build)
[![Azure DevOps coverage](https://img.shields.io/azure-devops/coverage/qnohot/qnohot/28)](https://dev.azure.com/qnohot/qnohot/_build/results?buildId=937&view=codecoverage-tab)

[![GitHub issues](https://img.shields.io/github/issues/qno/QRX)](https://github.com/qno/QRX/issues)
![GitHub last commit (branch)](https://img.shields.io/github/last-commit/qno/QRX/feature/create_cvwizard)
[![GitHub commit activity](https://img.shields.io/github/commit-activity/m/qno/QRX)](https://github.com/qno/QRX/graphs/commit-activity)
---

## Building the plugin

* Install and setup the [Conan C++ package manager](https://docs.conan.io/en/latest/installation.html) for your build platform
* ***Note:*** On the Windows platform there is no need to have the MinGW toolchain installed. It will be completely handled by Conan!
* On Windows create a [Conan profile](https://docs.conan.io/en/latest/reference/profiles.html) for MinGW under `<USER HOME>/.conan/profiles`, called e.g. `mingw`
    ```
    [settings]
    os=Windows
    os_build=Windows
    arch=x86_64
    arch_build=x86_64
    compiler=gcc
    compiler.version=8
    compiler.exception=seh
    compiler.libcxx=libstdc++11
    compiler.threads=posix
    build_type=Release
    [options]
    [build_requires]
    mingw_installer/1.0@conan/stable
    msys2_installer/latest@bincrafters/stable
    [env]
    ```
* Add the following conan remotes:
  * `conan remote add qno https://api.bintray.com/conan/qno/conan-public` 
  * `conan remote add conan-transit https://api.bintray.com/conan/conan/conan-transit`
* Clone the repository
  * `git clone https://github.com/qno/QRX.git` 
* Create a build directory and change into this directory
* Setup the project with Conan
  * On Linux and MacOS
    * `conan install <PATH-TO-QRX> --build missing`
  * On Windows
    * `conan install <PATH-TO-QRX> --profile mingw --build missing`
* Build the plugin with CMake (adapt CMake generator and install prefix according to your needs) e.g.
  * On Windows you have to additionally load the [generated build environment by Conan](https://docs.conan.io/en/latest/mastering/virtualenv.html?#virtualenv-generator) with `activate.bat`
    * `cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=dist -G Ninja <PATH-TO-QRX>`
    * `cmake --build . --target install`
  * Execute the unit tests
    * run `ctest` command
