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
public:
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

};
#endif //LFAF_REGULARLANGUAGE_H
