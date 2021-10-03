cc_library(
    name = "string_view",
    hdrs = ["jerryct/string_view.h"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "test",
    srcs = ["jerryct/string_view_tests.cpp"],
    deps = [
        ":string_view",
        "@com_google_googletest//:gtest_main",
    ],
)
