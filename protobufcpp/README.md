Protocol Buffers - Google's data interchange format
===================================================

Copyright 2008 Google Inc.

https://developers.google.com/protocol-buffers/

Overview
--------

Protocol Buffers (a.k.a., protobuf) are Google's language-neutral,
platform-neutral, extensible mechanism for serializing structured data. You
can find [protobuf's documentation on the Google Developers site](https://developers.google.com/protocol-buffers/).

This README file contains protobuf installation instructions. To install
For this protobuf, you just need to install bazel & only supports c++!!!
 
------------------------------

The protocol compiler is written in C++. If you are using C++, please follow
the [C++ Installation Instructions](src/README.md) to install protoc along
with the C++ runtime.

For non-C++ users, the simplest way to install the protocol compiler is to
download a pre-built binary from our release page:

  [https://github.com/protocolbuffers/protobuf/releases](https://github.com/protocolbuffers/protobuf/releases)

In the downloads section of each release, you can find pre-built binaries in
zip packages: protoc-$VERSION-$PLATFORM.zip. It contains the protoc binary
as well as a set of standard .proto files distributed along with protobuf.

If you are looking for an old version that is not available in the release
page, check out the maven repo here:

  [https://repo1.maven.org/maven2/com/google/protobuf/protoc/](https://repo1.maven.org/maven2/com/google/protobuf/protoc/)

These pre-built binaries are only provided for released versions. If you want
to use the github master version at HEAD, or you need to modify protobuf code,
or you are using C++, it's recommended to build your own protoc binary from
source.

If you would like to build protoc binary from source, see the [C++ Installation
Instructions](src/README.md).

Protobuf Runtime Installation
-----------------------------

Protobuf supports several different programming languages. For each programming
language, you can find instructions in the corresponding source directory about
how to install protobuf runtime for that specific language:

| Language                             | Source                                                      | Ubuntu | MacOS | Windows |
|--------------------------------------|-------------------------------------------------------------|--------|-------|---------|
| C++ (include C++ runtime and protoc) | [src](src)                                                  | [![Build status](https://storage.googleapis.com/protobuf-kokoro-results/status-badge/linux-cpp_distcheck.png)](https://fusion.corp.google.com/projectanalysis/current/KOKORO/prod:protobuf%2Fgithub%2Fmaster%2Fubuntu%2Fcpp_distcheck%2Fcontinuous)<br/>[![Build status](https://storage.googleapis.com/protobuf-kokoro-results/status-badge/linux-bazel.png)](https://fusion.corp.google.com/projectanalysis/current/KOKORO/prod:protobuf%2Fgithub%2Fmaster%2Fubuntu%2Fbazel%2Fcontinuous)<br/>[![Build status](https://storage.googleapis.com/protobuf-kokoro-results/status-badge/linux-dist_install.png)](https://fusion.corp.google.com/projectanalysis/current/KOKORO/prod:protobuf%2Fgithub%2Fmaster%2Fubuntu%2Fdist_install%2Fcontinuous) | [![Build status](https://storage.googleapis.com/protobuf-kokoro-results/status-badge/macos-cpp.png)](https://fusion.corp.google.com/projectanalysis/current/KOKORO/prod:protobuf%2Fgithub%2Fmaster%2Fmacos%2Fcpp%2Fcontinuous)<br/>[![Build status](https://storage.googleapis.com/protobuf-kokoro-results/status-badge/macos-cpp_distcheck.png)](https://fusion.corp.google.com/projectanalysis/current/KOKORO/prod:protobuf%2Fgithub%2Fmaster%2Fmacos%2Fcpp_distcheck%2Fcontinuous) | [![Build status](https://ci.appveyor.com/api/projects/status/73ctee6ua4w2ruin?svg=true)](https://ci.appveyor.com/project/protobuf/protobuf) |

Quick Start
-----------

The best way to learn how to use protobuf is to follow the tutorials in our
developer guide:

https://developers.google.com/protocol-buffers/docs/tutorials


Documentation
-------------

The complete documentation for Protocol Buffers is available via the
web at:

https://developers.google.com/protocol-buffers/
