cc_binary(
    name = "2",
    srcs = ["2.cc"],
    deps = [
        "//flags:flags",  # Reference the flags target
    ],
    data = ["test_data.txt", "data.txt"],
    copts = ["-DTARGET_DIR=\\\"2\\\""],
)