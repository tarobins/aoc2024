load("@rules_cc//cc:cc_binary.bzl", "cc_binary")

cc_binary(
    name = "3",
    srcs = ["3.cc"],
    deps = [
        "//flags:flags",  # Reference the flags target
    ],
    data = ["test_data.txt", "data.txt"],
    copts = ["-DTARGET_DIR=\\\"3\\\""],
)
