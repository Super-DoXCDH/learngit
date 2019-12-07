#load protoc compile tool & c++ compile

load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_proto_library")

load("@rules_proto//proto:defs.bzl", "proto_library")

#
#Compile .proto with inline protoc compile tool to generate .pb.h & .pb.cpp
#for cc_binary
# Remote repository "com_google_protobuf" must be defined to use this rule.
proto_library(
    name = "addressbook_proto",
    srcs = ["addressbook.proto"],
    deps = ["@com_google_protobuf//:timestamp_proto"],
)


# Remote repository "com_google_protobuf_cc" must be defined to use this rule.
cc_proto_library(
    name = "addressbook_cc_proto",
    deps = [":addressbook_proto"],
)


#
#
# cc_library/cc_binary targets can depend on cc_proto_library targets.
cc_binary(
    name = "add_person_cpp",
    srcs = ["add_person.cc"],
    deps = [":addressbook_cc_proto"],
)

cc_binary(
    name = "list_people_cpp",
    srcs = ["list_people.cc"],
    deps = [":addressbook_cc_proto"],
)


