#include <iostream>
#include <algorithm>
#include "LfafH/RegularLanguage.h"


int main() {
    RegularLanguage regLeng = *new RegularLanguage();
    regLeng.LanguageRulesInput();
    regLeng.PrintLanguageRules();
    cout<<endl;

    cout<<"Deletion Of Epsilon Productions\n";
    regLeng.DeletionOfEpsilonProductions();
    regLeng.PrintLanguageRules();
    cout<<endl;
    cout<<"Removal Of Dead Characters\n";
    regLeng.RemovalOfDeadCharacters();
    regLeng.PrintLanguageRules();
    cout<<endl;
    cout<<"Removal Of Unproductive Characters\n";
    regLeng.RemovalOfUnproductiveCharacters();
    regLeng.RemovalOfDeadCharacters();
    regLeng.PrintLanguageRules();
    cout<<endl;

    cout<<"Deletion Of Replacements\n";
    regLeng.DeletionOfReplacements();
    regLeng.PrintLanguageRules();
    cout<<endl;


    cout<<"Normal Form Of Khom\n";
    regLeng.NormalFormOfKhom();
    regLeng.PrintLanguageRules();

    return 0;
}
/*
S dB
S AC
A d
A dS
A aBdB
B a
B aA
B AC
D ab
C bC
C 0
end

S aA
S AC
A a
A ASC
A BC
A aD
B b
B bA
C 0
C BA
E aB
D abC
end
 */