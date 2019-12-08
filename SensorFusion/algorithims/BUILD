load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "klm",
    srcs = ["kalman.cpp"],
    hdrs = ["kalman.h"],
    visibility = ["//main:__pkg__"],
)

cc_library(
    name = "sf",
    srcs = ["sensorfusion.cpp"],
    hdrs = ["sensorfusion.h"],
    deps = [
	":klm",
	"//interface:gm"
	],
    visibility = ["//main:__pkg__"],
)
