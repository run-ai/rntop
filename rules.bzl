def rntop_cc_library(visibility=None, **kwargs):
    native.cc_library(
        visibility = visibility if visibility else ["//visibility:public"],
        **kwargs
    )

def rntop_cc_auto_library(hdrs=None, srcs=None, **kwargs):
    rntop_cc_library(
        hdrs = hdrs if hdrs else native.glob(["**/*.h"]),
        srcs = srcs if srcs else native.glob(["**/*.cc"], exclude=["**/*_test*.cc"]),
        **kwargs
    )
