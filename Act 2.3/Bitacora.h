#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <vector>
#include <fstream>
#include <stdexcept>
#include <string>
#include "Registro.h"
#include "DLinkedList.h"

class Bitacora {

  private:
    DLinkedList<Registro> listaRegistros;

  public:
    Bitacora();
    Bitacora(std::string fileName);
    // Print
    void print();
    // Ordenamiento
    void sort();
    // Busqueda
    int search(int k);
    // Func base datos
    void BuscarDatos();
    // Crear archivo 
    void crearBitacoraOrd();


};



#endif  // _BITACORA_H_