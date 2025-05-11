load("@rules_cc//cc:cc_binary.bzl", "cc_binary")

cc_binary(
    name = "1",
    srcs = ["1.cc"],
    deps = [
        "//flags:flags",  # Reference the flags target
        "//table_read:table_read",  # Reference the table_read library
    ],
    data = ["test_data.txt", "data.txt"],
    copts = ["-DTARGET_DIR=\\\"1\\\""],
)