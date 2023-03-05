#include "tests.h"

void TestPalindrom() {
	Assert(IsPalindrom(""), "void");

	Assert(IsPalindrom("a"), "a");
	Assert(IsPalindrom("0"), "0");
	Assert(IsPalindrom("z"), "0");

	Assert(IsPalindrom("madam"), "0");
	Assert(IsPalindrom("level"), "0");
	Assert(IsPalindrom("wasitacaroracatisaw"), "0");
	Assert(IsPalindrom("aba"), "0");
	Assert(IsPalindrom("abccba"), "0");

	Assert(IsPalindrom("aba aba"), "0");
	Assert(IsPalindrom("ma d am"), "0");
	Assert(IsPalindrom("z z z z z z"), "0");



	Assert(!IsPalindrom(" aba"), "0");
	Assert(!IsPalindrom("aba "), "0");

	Assert(!IsPalindrom("aadam"), "0");
	Assert(!IsPalindrom("madama"), "0");

	Assert(!IsPalindrom("z0abc0z"), "0");
	Assert(!IsPalindrom("z0cbc1z"), "0");

	Assert(!IsPalindrom("ab ccba"), "0");
}





