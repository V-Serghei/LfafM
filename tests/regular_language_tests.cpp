#include "lfaf/RegularLanguage.h"

#include <string>
#include <utility>
#include <vector>

namespace {
int expect(bool condition) {
    return condition ? 0 : 1;
}
}

int main() {
    RegularLanguage language;
    int failures = 0;

    failures += expect(language.isTerminalSymbol('a'));
    failures += expect(language.isTerminalSymbol('0'));
    failures += expect(!language.isTerminalSymbol('A'));

    failures += expect(RegularLanguage::hasLowerCase("ABc"));
    failures += expect(!RegularLanguage::hasLowerCase("ABC"));
    failures += expect(RegularLanguage::isLowerCase('x'));
    failures += expect(!RegularLanguage::isLowerCase('X'));

    const std::vector<std::pair<std::string, std::string>> replacements = {
            {"A", "a"},
            {"B", "BC"},
    };

    failures += expect(RegularLanguage::findFirstWithSecondValue(replacements, "BC") == "B");
    failures += expect(RegularLanguage::findFirstWithSecondValue(replacements, "missing").empty());

    return failures;
}
