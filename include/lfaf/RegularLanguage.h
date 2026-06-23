#ifndef LFAF_REGULARLANGUAGE_H
#define LFAF_REGULARLANGUAGE_H

#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

class RegularLanguage {
private:
    std::map<std::string, std::vector<std::string>> P;
    bool found = false;
    std::string current = "S";
    std::string currentKey;
    std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::queue<std::string> ABC;
    std::vector<char> Vn;

public:
    bool isTerminalSymbol(char symbol);

    void LanguageRulesInput();

    void DeletionOfEpsilonProductions();

    void RemovalOfDeadCharacters();

    void DeletionOfReplacements();

    static std::string findFirstWithSecondValue(
            const std::vector<std::pair<std::string, std::string>>& stAdd,
            const std::string& targetValue);

    void RemovalOfUnproductiveCharacters();

    static bool hasLowerCase(const std::string& str);

    static bool isLowerCase(char ch);

    void NormalFormOfKhom();

    void PrintLanguageRules();

    void DelMeaninglessTransition();

    void RemovingLeftRecursion();

    void delLeftRecFromSym(std::string A);

    bool comIndexWildcard(const char& AL, const char& AR);

    void Wildcard(const std::string& AL, const std::string& AR);

    void NormalFormOfGreibach();

    void substitutionForNormalShape(const std::string& A, const std::string& modif);

    static bool containsSymbol(std::vector<std::pair<std::string, std::string>> newAddReg,
                               char symbol);

    void printMapWithRule();
};

#endif // LFAF_REGULARLANGUAGE_H
