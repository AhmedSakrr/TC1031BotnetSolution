#include <iostream>
#include <vector>
#include "metodos.h"
using namespace std;


Bitacora::Bitacora(){

};


void Bitacora::setFecha(string _fecha){
  fecha = _fecha;
};

void Bitacora::setMensaje(string _mensaje){
  mensaje = _mensaje;
};

string Bitacora::getFecha(){
  return fecha;
};

string Bitacora::getMensaje(){
  return mensaje;
};

int Bitacora::getFechacon(){
  return fechaconvertida;
}

void Bitacora::setFechaCon(int _fechaCon){
  fechaconvertida = _fechaCon;
}