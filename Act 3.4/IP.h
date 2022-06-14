#ifndef __IP_H_
#define __IP_H_

#include <iostream>
#include <string>

using namespace std;

class IP{
  private:
    string ip;
    int occurrences;
  public:
    IP();
    IP(string, int);
    string getAll();
    int getOcc();
    bool operator ==(const IP&);
    bool operator !=(const IP&);
    bool operator >(const IP&);
    bool operator <(const IP&);
};

IP::IP(){
  this->ip = "desconocido";
  this->occurrences = 0;
}

IP::IP(string _ip, int _occurrences){
  this->ip = _ip;
  this->occurrences = _occurrences;
}

string IP::getAll(){
  string line;
  line += "IP: ";
  line += this -> ip;
  line += " Occurrences: ";
  line += to_string(this->occurrences);
  return line;
}

int IP::getOcc(){
  return this-> occurrences;
}

bool IP::operator==(const IP&other) {
    return this->occurrences == other.occurrences;
}

bool IP::operator!=(const IP&other) {
    return this->occurrences != other.occurrences;
}

bool IP::operator>(const IP&other) {
    return this->occurrences > other.occurrences;
}

bool IP::operator<(const IP&other) {
    return this->occurrences < other.occurrences;
}
#endif