#include <iostream>
#include "Bitacora.h"
#include "Registro.h"

using std::cout;
using std::endl;


//Main
int main () {
  
  Bitacora miBitacora("bitacoraHeap.txt");
  miBitacora.sort();
  miBitacora.crearBitacoraOrd();;
 

  
  
  return 0;
}
