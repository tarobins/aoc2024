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

# DEPRECATED: Use flags_int or flags_char instead
# cc_library(
#     name = "flags",
#     hdrs = ["flags_table.h"],
#     deps = [
#         ":file_setup",
#         "//table:table",  # Reference the table library
#     ],
#     visibility = ["//visibility:public"],  # Allow other targets to use this library
# )

cc_library(
    name = "flags_int",
    hdrs = ["flags_table_int.h"],
    deps = [
        ":file_setup",
        "//table:table",  # Reference the table library
    ],
    visibility = ["//visibility:public"],  # Allow other targets to use this library
)

cc_library(
    name = "flags_char",
    hdrs = ["flags_table_char.h"],
    deps = [
        ":file_setup",
        "//table:table",  # Reference the table library
    ],
    visibility = ["//visibility:public"],  # Allow other targets to use this library
)

cc_library(
    name = "flags_string",
    hdrs = ["flags_string.h"],
    deps = [
        ":file_setup",
    ],
    visibility = ["//visibility:public"],  # Allow other targets to use this library
)