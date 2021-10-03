#include "jerryct/string_view.h"
#include <gtest/gtest.h>

namespace jerryct {
namespace {

TEST(StringViewTest, WhenDefaultConstructed) {
  const string_view v{};
  EXPECT_EQ(nullptr, v.data());
  EXPECT_EQ(0, v.size());
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.begin(), v.end());
}

TEST(StringViewTest, WhenConstructedFromCStringWithoutLength) {
  const char *s{"foo"};
  const string_view v{s};
  EXPECT_EQ(s, v.data());
  EXPECT_EQ(3, v.size());
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(3, std::distance(v.begin(), v.end()));
}

TEST(StringViewTest, WhenConstructedFromCStringWithLength) {
  const char *s{"foobar"};
  const string_view v{s, 3};
  EXPECT_EQ(s, v.data());
  EXPECT_EQ(3, v.size());
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(3, std::distance(v.begin(), v.end()));
}

TEST(StringViewTest, WhenConstructedFromString) {
  const std::string s{"foo"};
  const string_view v{s};
  EXPECT_EQ(s.data(), v.data());
  EXPECT_EQ(s.size(), v.size());
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(3, std::distance(v.begin(), v.end()));
}

TEST(StringViewTest, WhenAccess) {
  const char *s{"abc"};
  const string_view v{s};
  EXPECT_EQ('a', v[0]);
  EXPECT_EQ('b', v[1]);
  EXPECT_EQ('c', v[2]);
}

TEST(StringViewTest, WhenAccessWithIterator) {
  const char *s{"abc"};
  const string_view v{s};

  auto it = v.begin();
  EXPECT_EQ('a', *it++);
  EXPECT_EQ('b', *it++);
  EXPECT_EQ('c', *it++);
  EXPECT_EQ(it, v.end());
}

TEST(StringViewTest, WhenAccessWithOutOfBounds_ThenContractViolation) {
  const char *s{"abc"};
  const string_view v{s};
  EXPECT_NO_THROW(v[2]);
  EXPECT_THROW(v[3], ContractViolation);
}

TEST(StringViewTest, WhenEqual) {
  {
    const char *a{"a"};
    const char *b{"a"};
    EXPECT_EQ(0, string_view{a}.compare(string_view{b}));
    EXPECT_TRUE(string_view{a} == string_view{b});
    EXPECT_TRUE(string_view{a} <= string_view{b});
    EXPECT_TRUE(string_view{a} >= string_view{b});
  }
  {
    const char *a{""};
    const char *b{""};
    EXPECT_EQ(0, string_view{a}.compare(string_view{b}));
    EXPECT_TRUE(string_view{a} == string_view{b});
    EXPECT_TRUE(string_view{a} <= string_view{b});
    EXPECT_TRUE(string_view{a} >= string_view{b});
  }
}

TEST(StringViewTest, WhenNotEqual) {
  const char *a{"a"};
  const char *b{"b"};
  EXPECT_NE(0, string_view{a}.compare(string_view{b}));
  EXPECT_TRUE(string_view{a} != string_view{b});
}

TEST(StringViewTest, WhenLessThanBecauseOfSize) {
  const char *a{"ab"};
  const char *b{"abc"};
  EXPECT_LE(string_view{a}.compare(string_view{b}), 0);
  EXPECT_TRUE(string_view{a} < string_view{b});
  EXPECT_TRUE(string_view{a} <= string_view{b});
}

TEST(StringViewTest, WhenLessThanBecauseOfLexicographicalComparision) {
  const char *a{"abc"};
  const char *b{"abd"};
  EXPECT_LE(string_view{a}.compare(string_view{b}), 0);
  EXPECT_TRUE(string_view{a} < string_view{b});
  EXPECT_TRUE(string_view{a} <= string_view{b});
}

TEST(StringViewTest, WhenGreaterThanBecauseOfSize) {
  const char *a{"abcd"};
  const char *b{"abc"};
  EXPECT_GE(string_view{a}.compare(string_view{b}), 0);
  EXPECT_TRUE(string_view{a} > string_view{b});
  EXPECT_TRUE(string_view{a} >= string_view{b});
}

TEST(StringViewTest, WhenGreaterThanBecauseOfLexicographicalComparision) {
  const char *a{"abcf"};
  const char *b{"abcd"};
  EXPECT_GE(string_view{a}.compare(string_view{b}), 0);
  EXPECT_TRUE(string_view{a} > string_view{b});
  EXPECT_TRUE(string_view{a} >= string_view{b});
}

TEST(StringViewTest, FindChar) {
  const char *a{"abc"};
  EXPECT_EQ(string_view{a}.find('a'), 0);
  EXPECT_EQ(string_view{a}.find('b'), 1);
  EXPECT_EQ(string_view{a}.find('c'), 2);
  EXPECT_EQ(string_view{a}.find('d'), string_view::npos);
}

TEST(StringViewTest, FindStr) {
  const char *a{"abc"};
  EXPECT_EQ(string_view{a}.find(string_view{""}), 0);
  EXPECT_EQ(string_view{a}.find(string_view{"a"}), 0);
  EXPECT_EQ(string_view{a}.find(string_view{"ab"}), 0);
  EXPECT_EQ(string_view{a}.find(string_view{"abc"}), 0);
  EXPECT_EQ(string_view{a}.find(string_view{"bc"}), 1);
  EXPECT_EQ(string_view{a}.find(string_view{"c"}), 2);
  EXPECT_EQ(string_view{a}.find(string_view{"d"}), string_view::npos);
  EXPECT_EQ(string_view{a}.find(string_view{"abcde"}), string_view::npos);
}

TEST(StringViewTest, StartsWith) {
  const char *a{"abc"};
  EXPECT_TRUE(string_view{a}.starts_with(string_view{""}));
  EXPECT_TRUE(string_view{a}.starts_with(string_view{"a"}));
  EXPECT_TRUE(string_view{a}.starts_with(string_view{"ab"}));
  EXPECT_TRUE(string_view{a}.starts_with(string_view{"abc"}));
  EXPECT_FALSE(string_view{a}.starts_with(string_view{"bc"}));
  EXPECT_FALSE(string_view{a}.starts_with(string_view{"c"}));
  EXPECT_FALSE(string_view{a}.starts_with(string_view{"d"}));
  EXPECT_FALSE(string_view{a}.starts_with(string_view{"abcd"}));
}

TEST(StringViewTest, StartsWithChar) {
  const char *a{"ab"};
  EXPECT_TRUE(string_view{a}.starts_with('a'));
  EXPECT_FALSE(string_view{a}.starts_with('b'));
  EXPECT_FALSE(string_view{a}.starts_with('c'));
}

TEST(StringViewTest, EndsWith) {
  const char *a{"abc"};
  EXPECT_TRUE(string_view{a}.ends_with(string_view{""}));
  EXPECT_FALSE(string_view{a}.ends_with(string_view{"a"}));
  EXPECT_FALSE(string_view{a}.ends_with(string_view{"ab"}));
  EXPECT_TRUE(string_view{a}.ends_with(string_view{"abc"}));
  EXPECT_TRUE(string_view{a}.ends_with(string_view{"bc"}));
  EXPECT_TRUE(string_view{a}.ends_with(string_view{"c"}));
  EXPECT_FALSE(string_view{a}.ends_with(string_view{"d"}));
  EXPECT_FALSE(string_view{a}.ends_with(string_view{"abcd"}));
}

TEST(StringViewTest, EndsWithChar) {
  const char *a{"bc"};
  EXPECT_FALSE(string_view{a}.ends_with('a'));
  EXPECT_FALSE(string_view{a}.ends_with('b'));
  EXPECT_TRUE(string_view{a}.ends_with('c'));
}

TEST(StringViewTest, RemovePrefix) {
  const char *a{"abc"};
  {
    string_view b{a};
    EXPECT_NO_THROW(b.remove_prefix(0U));
    EXPECT_EQ(string_view{"abc"}, b);
  }
  {
    string_view b{a};
    EXPECT_NO_THROW(b.remove_prefix(1U));
    EXPECT_EQ(string_view{"bc"}, b);
  }
  {
    string_view b{a};
    EXPECT_NO_THROW(b.remove_prefix(2U));
    EXPECT_EQ(string_view{"c"}, b);
  }
  {
    string_view b{a};
    EXPECT_NO_THROW(b.remove_prefix(3U));
    EXPECT_EQ(string_view{""}, b);
  }
  {
    string_view b{a};
    EXPECT_THROW(b.remove_prefix(4U), ContractViolation);
  }
}

TEST(StringViewTest, RemoveSuffix) {
  const char *a{"abc"};
  {
    string_view b{a};
    EXPECT_NO_THROW(b.remove_suffix(0U));
    EXPECT_EQ(string_view{"abc"}, b);
  }
  {
    string_view b{a};
    EXPECT_NO_THROW(b.remove_suffix(1U));
    EXPECT_EQ(string_view{"ab"}, b);
  }
  {
    string_view b{a};
    EXPECT_NO_THROW(b.remove_suffix(2U));
    EXPECT_EQ(string_view{"a"}, b);
  }
  {
    string_view b{a};
    EXPECT_NO_THROW(b.remove_suffix(3U));
    EXPECT_EQ(string_view{""}, b);
  }
  {
    string_view b{a};
    EXPECT_THROW(b.remove_suffix(4U), ContractViolation);
  }
}

TEST(StringViewTest, Front) {
  const char *a{"abc"};
  EXPECT_NO_THROW(string_view{a}.front());
  EXPECT_EQ('a', string_view{a}.front());
}

TEST(StringViewTest, Front_WhenEmpty) { //
  EXPECT_THROW(string_view{""}.front(), ContractViolation);
}

TEST(StringViewTest, Back) {
  const char *a{"abc"};
  EXPECT_NO_THROW(string_view{a}.back());
  EXPECT_EQ('c', string_view{a}.back());
}

TEST(StringViewTest, Back_WhenEmpty) { //
  EXPECT_THROW(string_view{""}.back(), ContractViolation);
}

} // namespace
} // namespace jerryct
