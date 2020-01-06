//
// Created by avichai on 27/12/2019.
//

#ifndef EX3A_OPENSERVERCOMMAND_H
#define EX3A_OPENSERVERCOMMAND_H

#include <vector>
#include <string>
#include "Command.h"
#include <mutex>

using namespace std;
//mutex mutex_lock;

class OpenServerCommand : public Command {
public:
    static vector<string> createLoc() {
//        mutex_lock.lock();
        string loc[36];
        loc[0] = "/instrumentation/airspeed-indicator/indicated-speed-kt";
        loc[1] = "/sim/time/warp";
        loc[2] = "/controls/switches/magnetos";
        loc[3] = "/instrumentation/heading-indicator/offset-deg";
        loc[4] = "/instrumentation/altimeter/indicated-altitude-ft";
        loc[5] = "/instrumentation/altimeter/pressure-alt-ft";
        loc[6] = "/instrumentation/attitude-indicator/indicated-pitch-deg";
        loc[7] = "/instrumentation/attitude-indicator/indicated-roll-deg";
        loc[8] = "/instrumentation/attitude-indicator/internal-pitch-deg";
        loc[9] = "/instrumentation/attitude-indicator/internal-roll-deg";
        loc[10] = "/instrumentation/encoder/indicated-altitude-ft";
        loc[11] = "/instrumentation/encoder/pressure-alt-ft";
        loc[12] = "/instrumentation/gps/indicated-altitude-ft";
        loc[13] = "/instrumentation/gps/indicated-ground-speed-kt";
        loc[14] = "/instrumentation/gps/indicated-vertical-speed";
        loc[15] = "/instrumentation/heading-indicator/indicated-heading-deg";
        loc[16] = "/instrumentation/magnetic-compass/indicated-heading-deg";
        loc[17] = "/instrumentation/slip-skid-ball/indicated-slip-skid";
        loc[18] = "/instrumentation/turn-indicator/indicated-turn-rate";
        loc[19] = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
        loc[20] = "/controls/flight/aileron";
        loc[21] = "/controls/flight/elevator";
        loc[22] = "/controls/flight/rudder";
        loc[23] = "/controls/flight/flaps";
        loc[24] = "/controls/engines/engine/throttle";
        loc[25] = "/controls/engines/current-engine/throttle";
        loc[26] = "/controls/switches/master-avionics";
        loc[27] = "/controls/switches/starter";
        loc[28] = "/engines/active-engine/auto-start";
        loc[29] = "/controls/flight/speedbrake";
        loc[30] = "/sim/model/c172p/brake-parking";
        loc[31] = "/controls/engines/engine/primer";
        loc[32] = "/controls/engines/current-engine/mixture";
        loc[33] = "/controls/switches/master-bat";
        loc[34] = "/controls/switches/master-alt";
        loc[35] = "/engines/engine/rpm";

        vector<string> location;
        location.reserve(36);
        for (const auto & i : loc){
            location.push_back(i);
        }
//        mutex_lock.unlock();
        return location;
    }

    OpenServerCommand();
    int execute(vector<string> lexer, int ind) override;
};


#endif //EX3A_OPENSERVERCOMMAND_H
