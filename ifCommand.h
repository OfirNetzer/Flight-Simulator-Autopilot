//
// Created by ofirn93 on 03/01/2020.
//

#ifndef EX3_IFCOMMAND_H
#define EX3_IFCOMMAND_H


#include "ConditionParser.h"


class ifCommand: public ConditionParser {
public:
    int runCondition(vector<string> arr, int ind) override;
};


#endif //EX3_IFCOMMAND_H
