#include <iostream>

#include "lfaf/RegularLanguage.h"

int main() {
    while (true) {
        RegularLanguage regLeng;
        std::cout << "/\nChoose: \n"
                     "1)Normal Form Of Khom\n"
                     "2)Normal form of Greibach\n"
                     "3)End\n";
        int tmp;
        std::cin >> tmp;

        switch (tmp) {
            case 1: {
                regLeng.LanguageRulesInput();
                regLeng.PrintLanguageRules();
                std::cout << std::endl;

                std::cout << "Deletion Of Epsilon Productions\n";
                regLeng.DeletionOfEpsilonProductions();
                regLeng.PrintLanguageRules();
                std::cout << std::endl;

                std::cout << "Removal Of Dead Characters\n";
                regLeng.RemovalOfDeadCharacters();
                regLeng.PrintLanguageRules();
                std::cout << std::endl;

                std::cout << "Removal Of Unproductive Characters\n";
                regLeng.RemovalOfUnproductiveCharacters();
                regLeng.RemovalOfDeadCharacters();
                regLeng.PrintLanguageRules();
                std::cout << std::endl;

                std::cout << "Deletion Of Replacements\n";
                regLeng.DeletionOfReplacements();
                regLeng.PrintLanguageRules();
                std::cout << std::endl;

                std::cout << "Normal Form Of Khom\n";
                regLeng.NormalFormOfKhom();
                regLeng.PrintLanguageRules();
                break;
            }
            case 2: {
                regLeng.LanguageRulesInput();
                regLeng.PrintLanguageRules();
                std::cout << std::endl;

                std::cout << "Deletion Of Epsilon Productions\n";
                regLeng.DeletionOfEpsilonProductions();
                regLeng.DelMeaninglessTransition();
                regLeng.PrintLanguageRules();
                std::cout << std::endl;

                std::cout << "Removal Of Dead Characters\n";
                regLeng.RemovalOfDeadCharacters();
                regLeng.PrintLanguageRules();
                std::cout << std::endl;
                regLeng.DelMeaninglessTransition();

                std::cout << "Removal Of Unproductive Characters\n";
                regLeng.RemovalOfUnproductiveCharacters();
                regLeng.RemovalOfDeadCharacters();
                regLeng.PrintLanguageRules();
                std::cout << std::endl;
                regLeng.DelMeaninglessTransition();

                std::cout << "Removing Left Recursion\n";
                regLeng.RemovingLeftRecursion();
                regLeng.PrintLanguageRules();
                std::cout << std::endl;

                std::cout << "Normal Form Of Greibach\n";
                regLeng.NormalFormOfGreibach();
                regLeng.PrintLanguageRules();
                std::cout << std::endl;
                regLeng.printMapWithRule();
                std::cout << std::endl;

                break;
            }
            case 3: {
                return 0;
            }
            default: {
                std::cout << "Choose one of the suggested options!\n";
                break;
            }
        }
    }
}
