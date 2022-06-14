#ifndef metodos_h
#define metodos_h
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;


class Bitacora {
  private: 
    int hora;
    int minuto;
    int segundo;
    int dia;
    string mes;

  public:
    string fecha;
    string mensaje;
    int fechaconvertida;
    Bitacora();
    void setFechaCon(int _fechaCon);
    int getFechacon();
    string getFecha();
    string getMensaje();
    void setFecha(string _fecha);
    void setMensaje(string _mensaje);
};

#endif