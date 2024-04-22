#include <iostream>
#include <algorithm>
#include "LfafH/RegularLanguage.h"


int main() {
    while(true){
        RegularLanguage regLeng = *new RegularLanguage();
        std::cout << "/\nChoose: \n"
                     "1)Normal Form Of Khom\n"
                     "2)Normal form of Greibach\n"
                     "3)End\n";
        int tmp;
        cin >> tmp;

        switch (tmp) {
            case 1: {
                {
                    regLeng.LanguageRulesInput();
                    regLeng.PrintLanguageRules();
                    cout << endl;

                    cout << "Deletion Of Epsilon Productions\n";
                    regLeng.DeletionOfEpsilonProductions();
                    regLeng.PrintLanguageRules();
                    cout << endl;
                    cout << "Removal Of Dead Characters\n";
                    regLeng.RemovalOfDeadCharacters();
                    regLeng.PrintLanguageRules();
                    cout << endl;
                    cout << "Removal Of Unproductive Characters\n";
                    regLeng.RemovalOfUnproductiveCharacters();
                    regLeng.RemovalOfDeadCharacters();
                    regLeng.PrintLanguageRules();
                    cout << endl;

                    cout << "Deletion Of Replacements\n";
                    regLeng.DeletionOfReplacements();
                    regLeng.PrintLanguageRules();
                    cout << endl;


                    cout << "Normal Form Of Khom\n";
                    regLeng.NormalFormOfKhom();
                    regLeng.PrintLanguageRules();
                }
                break;
            }
            case 2: {
                regLeng.LanguageRulesInput();
                regLeng.PrintLanguageRules();
                cout << endl;

                cout << "Deletion Of Epsilon Productions\n";
                regLeng.DeletionOfEpsilonProductions();
                regLeng.DelMeaninglessTransition();
                regLeng.PrintLanguageRules();
                cout << endl;

                cout << "Removal Of Dead Characters\n";
                regLeng.RemovalOfDeadCharacters();
                regLeng.PrintLanguageRules();
                cout << endl;
                regLeng.DelMeaninglessTransition();

                cout << "Removal Of Unproductive Characters\n";
                regLeng.RemovalOfUnproductiveCharacters();
                regLeng.RemovalOfDeadCharacters();
                regLeng.PrintLanguageRules();
                cout << endl;
                regLeng.DelMeaninglessTransition();

                cout << "Removal Of Unproductive Characters\n";
                regLeng.RemovingLeftRecursion();
                regLeng.PrintLanguageRules();
                cout << endl;

                cout << "Normal Form Of Greibach\n";
                regLeng.NormalFormOfGreibach();
                regLeng.PrintLanguageRules();
                cout << endl;
                regLeng.printMapWithRule();
                cout << endl;


                break;
            }
            case 3:{
                return 0;
            }
            default: {
                cout<<"Choose one of the suggested options!\n";
                break;
            }
        }
    }


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


S AC
A d
A dS
A BdB
B a
B aA
B BC
C bC
C 0
end
 */