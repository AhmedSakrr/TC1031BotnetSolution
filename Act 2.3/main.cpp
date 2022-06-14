#include <iostream>
#include "Bitacora.h"
#include "DLinkedList.h"
#include "StackedLinkedList.h"
#include "Registro.h"

using std::cout;
using std::endl;


//Main
int main () {
  
  Bitacora miBitacora("bitacora.txt");
  miBitacora.sort();
  miBitacora.crearBitacoraOrd();;
  miBitacora.BuscarDatos();

  
  
  return 0;
}
