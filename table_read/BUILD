load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("@rules_cc//cc:cc_test.bzl", "cc_test")

cc_library(
    name = "table",
    srcs = ["table.cc"],
    hdrs = ["table.h"],
    deps = [
        # "//flags:flags",  # Reference the flags target
        # "@abseil-cpp//absl/strings:str_format",
        # "@abseil-cpp//absl/strings:string_view",
    ],
    visibility = ["//visibility:public"],  # Allow other targets to use this library
)


cc_test(
    name = "table_test",
    srcs = ["table_test.cc"],
    deps = [
        ":table",  # Reference the table library
        # "//flags:flags",  # Reference the flags target
        "@googletest//:gtest",  # GoogleTest dependency
        "@googletest//:gtest_main",  # GoogleTest main function
    ],
)