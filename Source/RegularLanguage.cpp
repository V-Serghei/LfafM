//
// Created by Sitovlas on 10.04.2024.
//
#include "../LfafH/RegularLanguage.h"
///
///Introduction is accompanied by compliance with specific rules
///
void RegularLanguage::LanguageRulesInput() {
    string input;
    cout << "Enter a language rule |___|=>|___| (or 'end' to complete): ";
    cout <<"Epsilon should be specified as 0(zero)\n";
    while (true) {
        getline(cin, input);

        if (input == "end") {
            break;
        }

        if (!isupper(input[0])) {
            cout << "The first character should be uppercase. Repeat the input." << endl;
            continue;
        }

        size_t spacePos = input.find(' ');
        if (spacePos == string::npos) {
            cout << "Incorrect input. Expected space between key and value." << endl;
            continue;
        }

        string key = input.substr(0, spacePos);
        string value = input.substr(spacePos + 1);

        P[key].push_back(value);

    }



    for (int i = 0; i < letters.length(); ++i) {
        auto it = P.find(letters.substr(i, 1));
        if (it == P.end()) {
            std::string str = letters.substr(i, 1);
            ABC.push(str);
        }
    }
}
///
///Step 1: Deletion Of Epsilon Productions
///
void RegularLanguage::DeletionOfEpsilonProductions() {
    bool findEps = true;
    string epsCh;
    vector<pair<string,string>> stAdd;
    while (findEps) {
        findEps = false;

        for (auto& rule : P) {
            vector<string>& rightRul = rule.second;

            for (size_t i = 0; i < rightRul.size(); ++i) {
                if (rightRul[i] == "0") {
                    epsCh = rule.first;
                    findEps = true;
                    rightRul.erase(rightRul.begin() + (int)i);
                    i--;
                    for (auto& otherRule : P) {
                        size_t countEl = otherRule.second.size();
                        for (auto& otherTransition : otherRule.second) {
                            size_t pos = otherTransition.find(epsCh);
                            if(countEl-- == 0)break;
                            while (pos != string::npos) {
                                stAdd.emplace_back(otherRule.first,otherTransition);
                                otherTransition.erase(pos, 1);
                                pos = otherTransition.find(rule.first, pos);
                            }
                        }
                    }
                }
            }

        }
    }
    for (const auto& p : stAdd) {
        P[p.first].push_back(p.second);
    }

}
///
///Step 2:Delete a character that cannot be reached.
///Unreachable rule
///
void RegularLanguage::RemovalOfDeadCharacters() {

    vector<char> stLeftL;
    vector<char> stRightL;
    std::vector<char> uniqueSymbols;

    for (const auto& rule : P) {

        stLeftL.push_back(rule.first[0]);
        for (const auto& value : rule.second) {
            for (char ch : value) {
                if (std::isupper(ch)) {
                    if (std::find(stRightL.begin(), stRightL.end(), ch) == stRightL.end()) {
                        stRightL.push_back(ch);
                    }
                }
            }
        }
    }
    for (char ch : stLeftL) {
        if (std::find(stRightL.begin(), stRightL.end(), ch) == stRightL.end()) {
            uniqueSymbols.push_back(ch);
        }
    }
    for (char ch : stRightL) {
        if (std::find(stLeftL.begin(), stLeftL.end(), ch) == stLeftL.end()) {
            uniqueSymbols.push_back(ch);
        }
    }


    for(auto del:uniqueSymbols){
        std::string str(1, del);
        if(str != current)P.erase(str);
    }
    for (auto& pair : P) {
        auto& values = pair.second;

        for (auto it = values.begin(); it != values.end(); ) {
            bool containsSymbol = false;

            for (char symbol : *it) {
                if (std::find(uniqueSymbols.begin(), uniqueSymbols.end(), symbol) != uniqueSymbols.end()) {
                    containsSymbol = true;
                    break;
                }
            }

            if (containsSymbol) {
                if(it[0] != current)it = values.erase(it);
            } else {
                ++it;
            }
        }
    }


}
///
///Step 3: Deletion Of Replacements
///
void RegularLanguage::DeletionOfReplacements() {


    std::vector<char> uniqueSymbols;
    vector<pair<string,string>> stAdd;
    bool adding = true;
    while (adding){
        adding = false;
        for (auto& rule : P) {
            vector<string> &rightRul = rule.second;

            for (size_t i = 0; i < rightRul.size(); ++i) {
                if (rightRul[i].size() == 1) {

                    for (auto &otherRule: P) {
                        if (rightRul[i] == otherRule.first) {
                            for (const auto &add: otherRule.second) {
                                stAdd.emplace_back(rule.first, add);
                                adding = true;
                            }
                            rightRul.erase(rightRul.begin() + (int)i);
                            i--;
                        }
                    }
                }
            }

        }
    }
    for (const auto& p : stAdd) {
        P[p.first].push_back(p.second);
    }
}
///
///Step 4: Removal Of Unproductive Characters
///

//TODO: Исправить, должна быть проверка на возможность выхода через другой символ
//TODO: Fix, there should be a check to be able to exit through another character
void RegularLanguage::RemovalOfUnproductiveCharacters() {
    std::vector<char> uniqueSymbols;
    map<string , vector<string>> tmp;

    vector<string> stDel;
    bool delUnprodCh;
    for (auto& rule : P) {
        vector<string> &rightRul = rule.second;
        delUnprodCh = false;
        for (size_t i = 0; i < rightRul.size(); ++i) {

            if (rightRul[i].size() == 1) {

                delUnprodCh = true;
                break;
            }
        }
        if(!delUnprodCh)stDel.push_back(rule.first);


    }
    for (const auto& p : stDel) {
        P.erase(p);
    }
}
///
///Step 5: Chomsky Normal Form
///
void RegularLanguage::NormalFormOfKhom() {


    std::vector<char> elAdd;
    vector<pair<string,string>> stAdd;
    vector<pair<string,string>> newStep;

    bool adding = true;
    while (adding){
        adding = false;
        for (auto& rule : P) {
            vector<string> &rightRul = rule.second;

            for (size_t i = 0; i < rightRul.size(); ++i) {
                if (hasLowerCase(rightRul[i]) &&rightRul[i].size()>1 ) {
                    for (auto &chT: rightRul[i]) {
                        if(isLowerCase(chT)){
                            adding = true;
                            std::string str(1, chT);
                            if(findFirstWithSecondValue(stAdd,str).empty()){
                                stAdd.emplace_back(ABC.front(), str);
                                char ch = ABC.front()[0];
                                chT = ch;
                                ABC.pop();
                            }else{
                                string string1 = findFirstWithSecondValue(stAdd,str);
                                char ch = string1[0];
                                chT = ch;

                            }

                        }
                    }
                }
                else if(rightRul[i].size()>=3){
                    for(size_t i1 = 0; i1 < rightRul[i].size()-1; i1++){
                        std::string str1(1, rightRul[i][i1]);
                        std::string str2(1, rightRul[i][i1+1]);
                        str1+=str2;
                        if(!findFirstWithSecondValue(stAdd,str1).empty()){
                            string stringAdd =  findFirstWithSecondValue(stAdd,str1);
                            char ch1 = stringAdd[0];
                            rightRul[i][i1] = ch1;
                            rightRul[i].erase(i1+1, 1);
                            adding = true;
                        }
                    }
                    if(!adding){
                        std::string str1(1, rightRul[i][0]);
                        std::string str2(1, rightRul[i][1]);
                        str1+=str2;
                        stAdd.emplace_back(ABC.front(), str1);
                        char ch3 = ABC.front()[0];
                        rightRul[i][0] = ch3;
                        rightRul[i].erase(1, 1);
                        ABC.pop();
                        adding = true;
                    }



                }
            }

        }
    }
    for (const auto& p : stAdd) {
        P[p.first].push_back(p.second);
    }



}
///
///When necessary : Print Language Rules
///
void RegularLanguage::PrintLanguageRules()
{
    cout << "Language Rules:" << endl;
    int i=1;
    for (const auto& rule : P) {

        for (const auto& transition : rule.second) {
            cout <<i++<<". "<< rule.first<<" => "<< transition << " \n";
        }
    }
}

/// Additional tools.
///
/// Searches and returns the key, by value.
/// \param stAdd // is used as a temporary data store for map
/// \param targetValue // expected map value
/// \return Key //expected map key
string RegularLanguage::findFirstWithSecondValue(const vector<pair<string, string>> &stAdd, const string &targetValue) {
    for (const auto& pair : stAdd) {
        if (pair.second == targetValue) {
            return pair.first;
        }
    }

    return "";
}
///verification
/// \param str // the word in which you want to find a lowercase
/// \return //lowercase confirmation
bool RegularLanguage::hasLowerCase(const string &str) {
    for (char ch : str) {
        if (std::islower(ch)) {
            return true;
        }
    }
    return false;
}
///Lower case detection of the spell
/// \param ch // verifiable character
/// \return bool
bool RegularLanguage::isLowerCase(char ch) {
    return std::islower(ch) != false;
}


