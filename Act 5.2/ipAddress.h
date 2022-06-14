#ifndef _IPADDRESS_H_
#define _IPADDRESS_H_

#include <cmath>
#include <iostream>
#include <vector>

class ipAddress {
    private:
      std::string ipString;
      std::string ipPort;
      int ipIndex;
      long int ipValue;
      int degree;

    public:
      ipAddress();
      ipAddress(std::string _ip, std::string _port, int idx);
      // Complejidad O(1)
      std::string getIp();
      // Complejidad O(1)
      std::string getIpPort();
      // Complejidad O(1)
      unsigned int getIpValue();
      // Complejidad O(1)
      int getIpIndex();
      // Complejidad O(1)
      void setDegree(int g);
      // Complejidad O(1)
      void addToDegree();
      // Complejidad O(1)
      int getDegree();

      // Complejidad O(1) en sobrecarga de operadores.  

      bool operator ==(const ipAddress&);
      bool operator !=(const ipAddress&);
      bool operator >(const ipAddress&);
      bool operator >=(const ipAddress&);
      bool operator <(const ipAddress&);
      bool operator <=(const ipAddress&);
      /* incorrecto 
      bool operator ==(ipAddress);
      bool operator !=(ipAddress);
      bool operator >(ipAddress);
      bool operator <(ipAddress);
      bool operator >=(ipAddress);
      bool operator <=(ipAddress);
      */
};


#endif
