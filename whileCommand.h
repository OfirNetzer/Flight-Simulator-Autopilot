//
// Created by ofirn93 on 03/01/2020.
//

#ifndef EX3_WHILECOMMAND_H
#define EX3_WHILECOMMAND_H


#include "ConditionParser.h"

class whileCommand: public ConditionParser {
public:
//    int execute(vector<string> arr, int ind);
    int runCondition(vector<string> arr, int ind) override;
};


#endif //EX3_WHILECOMMAND_H
