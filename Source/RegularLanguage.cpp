//
// Created by Sitovlas on 10.04.2024.
//
#include <set>
#include "../LfafH/RegularLanguage.h"
///
///Introduction is accompanied by compliance with specific rules
///


bool RegularLanguage::isTerminalSymbol(char symbol) {
    return !isupper(symbol) || !isalpha(symbol) || isdigit(symbol);
}

void RegularLanguage::LanguageRulesInput() {
    string input;
    cout << "Enter a language rule |___|=>|___| (or 'end' to complete): ";
    cout <<"Epsilon should be specified as 0(zero)\n";
    while (true) {
        getline(cin, input);

        if (input == "end") {
            break;
        }
        if( std::find(Vn.begin(), Vn.end(), input[0]) == Vn.end()){
                Vn.push_back(input[0]);
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

void RegularLanguage::RemovalOfUnproductiveCharacters() {
    set<char> prodS;

    for (const auto& rule : P)
    {
        const vector<string>& rRul = rule.second;

        for (const string& prod : rRul)
        {
            for (char symbol : prod)
            {

                if (isTerminalSymbol(symbol))
                {
                    prodS.insert(symbol);
                }
            }
        }
    }
    bool flag = true;
    while (flag)
    {
        flag = false;

        for (const auto& rule : P)
        {
            const vector<string>& rRul = rule.second;

            for (const string& prod : rRul)
            {
                bool isProductive = true;

                for (char symbol : prod)
                {
                    if (!isTerminalSymbol(symbol) && prodS.find(symbol) == prodS.end())
                    {
                        isProductive = false;
                        break;
                    }
                }
                if (isProductive)
                {
                    if (prodS.insert(rule.first[0]).second)
                    {
                        flag = true;
                    }
                }
            }
        }
    }

    std::vector<std::string> unProdS;
    for (const auto& rule : P)
    {
        if (prodS.find(rule.first[0]) == prodS.end())
        {
            unProdS.push_back(rule.first);
        }
    }
    for (const auto& symbol : unProdS)
    {
        P.erase(symbol);
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




///"Normal form of Greibach"
///
///


void RegularLanguage::RemovingLeftRecursion() {


    bool flag = true;
    bool flagReset = false;
    while (flag) {
        flag = false;
        for (const auto &rule: P) {
            const vector<string> &rRul = rule.second;

            for (const string &prod: rRul) {


                    if (!isTerminalSymbol(prod[0])) {
                        if (prod[0] == rule.first[0]) {
                            flag = true;
                            delLeftRecFromSym(rule.first);
                            flagReset = true;
                        }

                    }
                    if(flagReset){
                        break;
                    }

            }
            if(flagReset){
                flagReset = false;
                break;
            }

        }
        DelMeaninglessTransition();

        for (const auto &rule: P) {
            const vector<string> &rRul = rule.second;

            for (const string &prod: rRul) {

                    if (!isTerminalSymbol(prod[0])) {
                        if (comIndexWildcard(rule.first[0], prod[0])) {
                            flag = true;
                            Wildcard(rule.first,prod);
                            flagReset = true;
                        }
                    }
                if(flagReset){
                    break;
                }
            }
            if(flagReset){
                flagReset = false;
                break;
            }
        }
        DelMeaninglessTransition();



    }


}

std::string strCreateAlfa(const std::string& str) {
    if (str.empty() || str.length() == 1) {
        return "";
    }

    return str.substr(1);
}

void RegularLanguage::delLeftRecFromSym(string A) {
    vector<pair<string,string>> correct;
    vector<string> alfa;
    vector<string> betta;
    string Y = ABC.front();

    ABC.pop();
    Vn.push_back(Y[0]);


    vector<string> arrP = P[A];
   // for (const auto &rule: P) {
       // const vector<string> &rRul = rule.second;

        for (const string &prod: arrP) {

                if (!isTerminalSymbol(prod[0])) {
                    if (prod[0] == A[0]) {
                        alfa.push_back(strCreateAlfa(prod));
                        continue;
                    }
                }
                else
                {
                    betta.push_back(prod);
                }
        }
        const auto& a1 = A;
        P.erase(a1);
        for( const auto& currBetta : betta){
            P[A].push_back(currBetta + Y);
            P[A].push_back(currBetta);
        }
        for(const auto& currAlfa : alfa){
            P[Y].push_back(currAlfa);
            P[Y].push_back(currAlfa+Y);
        }

   // }

}

bool RegularLanguage::comIndexWildcard(const char &AL, const char &AR) {
    auto it1 = std::find(Vn.begin(), Vn.end(), AL);
    auto it2 = std::find(Vn.begin(), Vn.end(), AR);

    if (it1 == Vn.end() || it2 == Vn.end()) {
        return false;
    }

    return std::distance(Vn.begin(), it1) > std::distance(Vn.begin(), it2);
}

void RegularLanguage::Wildcard(const string& AL, const string &AR) {

    vector<string> substitution = P[AR.substr(0, 1)];
    string stored = strCreateAlfa(AR);

    auto it = P.find(AL);
    if (it != P.end()) {
        auto vec = it->second;
        auto arIt = std::find(vec.begin(), vec.end(), AR);

        if (arIt != vec.end()) {
            vec.erase(arIt);
            it->second = vec;
        }
    }

    for( const auto& pr : substitution){
        P[AL].push_back(pr+stored);
    }


}

void RegularLanguage::DelMeaninglessTransition() {
    for (auto& entry : P) {
        const std::string& key = entry.first;
        std::vector<std::string>& vec = entry.second;

        vec.erase(std::remove_if(vec.begin(), vec.end(), [&](const std::string& str) {
            return str == key;
        }), vec.end());
    }
}


void RegularLanguage::NormalFormOfGreibach() {

    vector<pair<string,string>> newAddReg;
    bool flagReset = false;
    bool flag = true;
    while (flag) {
        flag = false;
        for (const auto &rule: P) {
            const vector<string> &rRul = rule.second;

            for (const string &prod: rRul) {


                if (!isTerminalSymbol(prod[0])) {
                    //if (prod[0] == rule.first[0]) {
                    substitutionForNormalShape(rule.first,prod);
                    flag = true;
                    flagReset = true;

                   // }
                }
                if(flagReset){
                    break;
                }
            }
            if(flagReset){
                flagReset = false;
                break;
            }

        }
    }
    for (auto& rule : P)
    {
        vector<string>& rRul = rule.second;

        for (string& prod : rRul)
        {
            string sym = strCreateAlfa(prod);
            for (std::size_t i = 0; i < sym.size(); ++i) {
                if (isTerminalSymbol(sym[i])) {
                    auto it = std::find_if(newAddReg.begin(), newAddReg.end(), [&](const auto& pair) {
                        return pair.second == std::string(1, sym[i]);
                    });

                    if (it != newAddReg.end()) {
                        prod[i+1] = it->first[0];
                    } else {
                        newAddReg.emplace_back(ABC.front(), std::string(1, sym[i]));
                        Vn.push_back(ABC.front()[0]);
                        ABC.pop();
                    }
                }
            }

        }
    }

    for(const auto& Add : newAddReg){
        P[Add.first].push_back(Add.second);
    }





}

void RegularLanguage::substitutionForNormalShape(const string& A, const string &modif) {
    vector<string> substitution = P[modif.substr(0, 1)];
    string stored = strCreateAlfa(modif);

    auto it = P.find(A);
    if (it != P.end()) {
        auto vec = it->second;
        auto arIt = std::find(vec.begin(), vec.end(), modif);

        if (arIt != vec.end()) {
            vec.erase(arIt);
            it->second = vec;
        }
    }
    for( const auto& pr : substitution){
        P[A].push_back(pr+stored);
    }




}

bool RegularLanguage::containsSymbol(vector<pair<string, string>> newAddReg, char symbol) {
    return std::find_if(newAddReg.begin(), newAddReg.end(), [&](const auto& pair) {
        return pair.second == std::string(1, symbol);
    }) != newAddReg.end();
}

void RegularLanguage::printMapWithRule() {
    int i = 1;
    for(auto key : Vn){

        vector<string> reg = P[std::string(1, key)];
        for(auto rul:reg){
            cout << i++ << ") A";
            auto it = std::find(Vn.begin(), Vn.end(), key);
            int index = std::distance(Vn.begin(), it);
            cout << index << "=> ";
            for(auto ch:rul){
                if(isTerminalSymbol(ch)){
                    cout<<ch;
                }else{
                    auto it1 = std::find(Vn.begin(), Vn.end(), ch);
                    int index1 = std::distance(Vn.begin(), it1);
                    cout<<"A"<<index1;
                }
            }
            cout<<endl;
        }



    }




}


