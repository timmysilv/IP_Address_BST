#include "DBentry.h"

DBentry::DBentry(){
    name = "";
    IPaddress = 0;
    active = false;
}

DBentry::DBentry(string _name, unsigned int _IPaddress, bool _active){
    name = _name;
    IPaddress = _IPaddress;
    active = _active;
}

DBentry::~DBentry(){}

bool DBentry::getActive() const{
    return active;
}

unsigned int DBentry::getIPaddress() const{
    return IPaddress;
}

string DBentry::getName() const{
    return name;
}

void DBentry::setActive(bool _active){
    active = _active;
}

void DBentry::setIPaddress(unsigned int _IPaddress){
    IPaddress = _IPaddress;
}

void DBentry::setName(string _name){
    name = _name;
}

void DBentry::print(){
    string status;
    if(active) status = "active";
    else status = "inactive";
    cout << name << " : " << IPaddress << " : " << status << endl;
}