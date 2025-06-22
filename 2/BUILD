load("@rules_cc//cc:cc_binary.bzl", "cc_binary")

cc_binary(
    name = "2",
    srcs = ["2.cc"],
    deps = [
        "//flags:flags_int",  # Reference the flags_int target
    ],
    data = ["test_data.txt", "data.txt"],
    copts = ["-DTARGET_DIR=\\\"2\\\""],
    linkopts = ["-pthread"],
)