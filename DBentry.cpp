#include "DBentry.h"
#include <string>

DBentry::DBentry(){
    
}

DBentry::DBentry(string _name, unsigned int _IPaddress, bool _active){
    
}

DBentry::~DBentry(){
    
}

bool DBentry::getActive() const{
    return true;
}

unsigned int DBentry::getIPaddress() const{
    return 0;
}

string DBentry::getName() const{
    return "hi";
}

void DBentry::setActive(bool _active){
    
}

void DBentry::setIPaddress(unsigned int _IPaddress){
    
}

void DBentry::setName(string _name){
    
}