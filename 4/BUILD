load("@rules_cc//cc:cc_binary.bzl", "cc_binary")

cc_binary(
    name = "4",
    srcs = ["4.cc"],
    deps = [
        "//flags:flags_char",  # Reference the flags_char target
    ],
    data = ["test_data.txt", "data.txt"],
    copts = ["-DTARGET_DIR=\\\"4\\\""],
)