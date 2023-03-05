#include "tests.h"
#include "IsPalindrom.h"

#include <stdexcept>

using namespace std;

int main() {
    TestRunner runner;
    runner.RunTest(TestPalindrom, "TestPalindrom");
    return 0;
}

/*
void TestIsPalindrom() {
    Assert(IsPalindrom(""), "empty string is a palindrome");
    Assert(IsPalindrom("a"), "one letter string is a palindrome");
    Assert(IsPalindrom("abba"), "abba is a palindrome");
    Assert(IsPalindrom("abXba"), "abXba is a palindrome");
    Assert(IsPalindrom("a b X b a"), "`a b X b a` is a palindrome");
    Assert(IsPalindrom("  ABBA  "), "`  ABBA  ` is a palindrome");

    Assert(!IsPalindrom("XabbaY"), "XabbaY is not a palindrome");
    Assert(!IsPalindrom("abXYba"), "abXYba is not a palindrome");
    Assert(!IsPalindrom("Xabba"), "Xabba is not a palindrome");
    Assert(!IsPalindrom("abbaX"), "abbaX is not a palindrome");
    Assert(
        !IsPalindrom("was it a car or a cat i saw"),
        "`was it a car or a cat i saw` is not a palindrome because spaces do not match"
    );
    Assert(!IsPalindrom("ABBA   "), "`ABBA   ` is not a palindrome");
    Assert(!IsPalindrom("  ABBA"), "`  ABBA` is not a palindrome");
} */
