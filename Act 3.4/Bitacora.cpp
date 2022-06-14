#include "Bitacora.h"


Bitacora::Bitacora() {
  listaHeap.setCapacity(18000);
}

Bitacora::Bitacora(std::string fileName) {
  listaHeap.setCapacity(18000);
  std::string month, day, hours, minutes, seconds, ipAdd, port, error;
  std::ifstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  }
  else {
    while (!file.eof()) {
        std::getline(file, month, ' ');
        std::getline(file, day, ' ');
        std::getline(file, hours, ':');
        std::getline(file, minutes, ':');
        std::getline(file, seconds, ' ');
        std::getline(file, ipAdd, ':');
        std::getline(file, port, ' ');
        std::getline(file, error);
        // Crear un objeto de la clase Registro
        Registro tmpRegistro(month, day, hours, minutes, seconds, ipAdd, port, error);
        // Agregar al vector de registro
        listaHeap.push(tmpRegistro);
      }
  }
}

  // Complejidad: O(n)

void Bitacora::print() {

}

// Complejidad: O(n log n) worst case: O(n^2)

void Bitacora::sort() {  
  this->listaHeap.heapSort(this->listaHeap.getSize());
}

// Busqueda binaria, complejidad: O(log n)

int Bitacora::search(int k){

}

// Complejidad: O(n)

void Bitacora::BuscarDatos(){

}

  // Complejidad: O(n)

void Bitacora::crearBitacoraOrd(){
    std::ofstream readbitacora("bitacora_ordenada.txt");    
    std::string linea;
    if(readbitacora.is_open()){
      for(int i = 0; i<listaHeap.getSize(); i++){
          linea = listaHeap.top().getAll();
          readbitacora << linea << std::endl;
      }
      std::cout << "Archivo con bitacora ordenada creado correctamente. " << std::endl;
    }else{
      std::cout << "Fallo en creacion de archivo." << std::endl;  
    } // Uso de excepciones.
    readbitacora.close();
    if(!readbitacora.is_open()){
      std::cout << "Archivo cerrado correctamente." <<       std::endl;
    }else{
      std::cout<<"El archivo no se ha cerrado correctamente. " << std::endl;
    }
}



