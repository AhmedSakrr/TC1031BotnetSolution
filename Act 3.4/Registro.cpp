#include "Registro.h"
#include <math.h>


Registro::Registro() {
  mes = "";
  dia = "";
  hora = "";
  minutos = "";
  segundos = "";
  ip = "";
  puerto = "";
  RazonDeFalla = "";
}

Registro::Registro(std::string MES, std::string DIA, std::string HORA, std::string MINUTOS, std::string SEGUNDOS, std::string IP, std::string PUERTO, std::string RAZON_DE_FALLA) {
  mes = MES;
  dia = DIA;
  hora = HORA;
  minutos = MINUTOS;
  segundos = SEGUNDOS;
  ip = IP;
  puerto = PUERTO;
  RazonDeFalla = RAZON_DE_FALLA;

  // Almacenar los campos de la fecha-hora en el struct tm
  dateStruct.tm_sec = std::stoi(segundos);
  dateStruct.tm_min = std::stoi(minutos);
  dateStruct.tm_hour = std::stoi(hora);
  dateStruct.tm_mday = std::stoi(dia);
  // Agregado para resolver problema de compatibilidad en Windows
  dateStruct.tm_isdst = 0;
  for (int i=0; i < meses.size(); i++) {
    if (meses[i]==mes)
      dateStruct.tm_mon = i;
  }
  dateStruct.tm_year = 2022 - 1900;  // Asumimos el año 2022
  // Obtener el Unix timestamp a partir del struct tm anterior 
  // Numero de segundos desde el 1 de enero de 1970
  dateTime = mktime(&dateStruct);
  this -> ipInt = this -> ipToInt();
}

time_t Registro::getDate() {
  //std::cout<<date;   //lo imprime 2 veces si se descomenta
  return dateTime;
}

std::string Registro::getAll() {
  return mes +" " + dia + " " + hora + ":" + minutos + ":" + segundos + " " + ip + ":" + puerto + " " + RazonDeFalla;
}

std::string Registro::getIp(){
  return ip;
}

//Complejidad O(n)
long Registro::ipToInt(){
  std::string ads;
  ads = ip.substr(0, ip.find(":"));
  long ip1 = stoi(ads.substr(0, ads.find(".")));
  ads = ads.erase(0, ads.find(".")+1);
  long ip2 = stoi(ads.substr(0, ads.find(".")));
  ads = ads.erase(0, ads.find(".")+1);
  long ip3 = stoi(ads.substr(0, ads.find(".")));
  ads = ads.erase(0, ads.find(".")+1);
  long ip4 = stoi(ads.substr(0, ads.find(":")));
  return ((ip1*pow(256,3))+(ip2*pow(256,2))+(ip3*pow(256,1))+(ip4*pow(256,0)));
}

//Complejidad O(1)
long Registro::getipInt(){
  return this -> ipInt;
}


bool Registro::operator==(const Registro &other) {
  return this->dateTime == other.dateTime;
}

bool Registro::operator!=(const Registro &other) {
  return this->dateTime != other.dateTime;
}

bool Registro::operator>(const Registro &other) {
  return this->dateTime > other.dateTime;
}

bool Registro::operator<(const Registro &other) {
  return this->dateTime < other.dateTime;
}

bool Registro::operator<=(const Registro &other) {
  return this->dateTime <= other.dateTime;
}

bool Registro::operator>=(const Registro &other) {
  return this->dateTime >= other.dateTime;
}




