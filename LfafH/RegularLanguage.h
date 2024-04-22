//
// Created by Sitovlas on 10.04.2024.
//
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

#ifndef LFAF_REGULARLANGUAGE_H
#define LFAF_REGULARLANGUAGE_H
class RegularLanguage{
private:
    map<string , vector<string>> P;
    bool found = false;
    string current = "S";
    string currentKey;
    std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::queue<std::string> ABC;
    vector<char> Vn;
public:
    bool isTerminalSymbol(char symbol);

    void LanguageRulesInput();

    void DeletionOfEpsilonProductions();

    void RemovalOfDeadCharacters();

    void DeletionOfReplacements();

    static string findFirstWithSecondValue(const vector<pair<string, string>>& stAdd,
                                           const string& targetValue);
    void RemovalOfUnproductiveCharacters();


    static bool hasLowerCase(const string& str);
    static bool isLowerCase(char ch);

    void NormalFormOfKhom();

    void PrintLanguageRules();

public:

    void DelMeaninglessTransition();
    void RemovingLeftRecursion();

    void delLeftRecFromSym(string A);

    bool comIndexWildcard(const char &AL, const char &AR);

    void Wildcard(const string& AL, const string &AR);

    void NormalFormOfGreibach();

    void substitutionForNormalShape(const string& A, const string &modif);

    static bool containsSymbol(vector<pair<string, string>> newAddReg, char symbol);

    void printMapWithRule();
};
#endif //LFAF_REGULARLANGUAGE_H
