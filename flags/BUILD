load("@rules_cc//cc:cc_library.bzl", "cc_library")

cc_library(
    name = "file_setup",
    hdrs = ["file_setup.h"],
    srcs = ["file_setup.cc"],
    deps = [
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/flags:parse",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "flags",
    hdrs = ["flags.h"],
    deps = [
        ":file_setup",
        "//table_read:table_read",  # Reference the table_read library
    ],
    visibility = ["//visibility:public"],  # Allow other targets to use this library
)