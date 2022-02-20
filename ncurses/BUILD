load("//:rules.bzl", "rntop_cc_auto_library")

rntop_cc_auto_library(
    name = "ncurses",
    deps = [
        "//ncurses/window",
        "//ncurses/session",
    ],
    linkopts = ["-lncurses"],
)
