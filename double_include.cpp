#include "string_view.h"
#include <gtest/gtest.h>

namespace view {
namespace {

TEST(StringViewTest, FindChar) {
  const char *a{"abc"};
  EXPECT_EQ(string_view{a}.find('d'), string_view::npos);
}

} // namespace
} // namespace view
