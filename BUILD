cc_library(
    name = "lib",
    deps = [
        "//arguments",
        "//cluster",
        "//node",
        "//popen",
        "//ssh",
        "//utils",
    ]
)

cc_binary(
    name = "rntop",
    srcs = ["main.cc"],
    deps = [":lib"],
)
