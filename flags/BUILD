load("@rules_cc//cc:cc_library.bzl", "cc_library")

cc_library(
    name = "flags",
    hdrs = ["flags.h"],
    deps = [
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/flags:parse",
        "//table_read:table_read",  # Reference the table_read library
    ],
    visibility = ["//visibility:public"],  # Allow other targets to use this library
)