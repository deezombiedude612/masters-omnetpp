/*
 * txc5.cc
 *
 *  Created on: May 13, 2021
 *      Author: deezombiedude612
 */

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Txc5 : public cSimpleModule {
private:
    int counter;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Txc5);

void Txc5::initialize() {
    counter = par("limit");

    if(par("sendMsgOnInit").boolValue() == true) {
        EV << "Sending initial message\n";
        cMessage *msg = new cMessage("tictocMsg");
        send(msg, "out");
    }
}

void Txc5::handleMessage(cMessage *msg) {
    counter--;
    if(counter == 0) {
        EV << getName() << "' counter reached zero, deleting message\n";
        delete msg;
    } else {
        EV << getName() << "'s counter is " << counter << ", sending back message\n";
        send(msg, "out");
    }
}
