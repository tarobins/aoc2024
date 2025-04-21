load("@rules_cc//cc:cc_library.bzl", "cc_library")

cc_library(
    name = "table_read",
    srcs = ["table_read.cc"],
    hdrs = ["table_read.h"],
    deps = [
        "//flags:flags",  # Reference the flags target
        # "@abseil-cpp//absl/strings:str_format",
        # "@abseil-cpp//absl/strings:string_view",
    ],
    visibility = ["//visibility:public"],  # Allow other targets to use this library
)


cc_test(
    name = "table_read_test",
    srcs = ["table_read_test.cc"],
    deps = [
        ":table_read",  # Reference the table_read library
        "//flags:flags",  # Reference the flags target
        "@googletest//:gtest",  # GoogleTest dependency
        "@googletest//:gtest_main",  # GoogleTest main function
    ],
)