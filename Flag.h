//
// Created by avichai on 31/12/2019.
//

#ifndef EX3_FLAG_H
#define EX3_FLAG_H


class Flag {
private:
    static Flag* instance;
    bool threadFlag = true;
public:
    static Flag* getInstance() {
        if (instance == nullptr) {
            instance = new Flag();
        }
        return instance;
    }

    bool isThreadFlag() const {
        return threadFlag;
    }
};


#endif //EX3_FLAG_H
