load("@rules_cc//cc:cc_binary.bzl", "cc_binary")

cc_binary(
    name = "1",
    srcs = ["1.cc"],
    deps = [
        "//flags:flags_int",  # Reference the flags_int target
        "//table:table",  # Reference the table library
    ],
    data = ["test_data.txt", "data.txt"],
    copts = ["-DTARGET_DIR=\\\"1\\\""],
)