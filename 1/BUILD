load("@rules_cc//cc:cc_binary.bzl", "cc_binary")
load("@rules_rust//rust:defs.bzl", "rust_binary")

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

rust_binary(
    name = "1_rust",
    srcs = ["1.rs"],
    data = ["test_data.txt", "data.txt"],
    edition = "2021",
    deps = [
        "@crates//:clap",
        "//table:table_rust",
    ],
)