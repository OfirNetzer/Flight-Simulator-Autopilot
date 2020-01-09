//
// Created by ofirn93 on 03/01/2020.
//

#ifndef EX3_IFCOMMAND_H
#define EX3_IFCOMMAND_H


#include "ConditionParser.h"

/* we will get here only when executing ifCommand.
 * the only differnce between the execute of condition parser is the inner func
 * that called runCondition. it runs the entire inner commands of the if command
 * once the condition is satisfied.
 * */
class ifCommand: public ConditionParser {
public:
    int runCondition(vector<string> arr, int ind) override;
};


#endif //EX3_IFCOMMAND_H
