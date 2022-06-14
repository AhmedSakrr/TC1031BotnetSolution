#include "Bitacora.h"


Bitacora::Bitacora() {
  
}

Bitacora::Bitacora(std::string fileName) {
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
        listaRegistros.addLast(tmpRegistro);
      }
  }
}

  // Complejidad: O(n)

void Bitacora::print() {
  for (int i=0; i < listaRegistros.getNumElements(); i++){
    Registro temp = listaRegistros[i];
    std::cout << temp.getAll() << std::endl;
  }
}


// Complejidad: O(n log n) worst case: O(n^2)

void Bitacora::sort() {  
  this->listaRegistros.quickSort();
}

// Busqueda binaria, complejidad: O(log n)

int Bitacora::search(int k){
    int low = 0;
    int high = listaRegistros.getNumElements() - 1;
    while (low <= high) {
        int m = low + (high - low) / 2;
        if (k == listaRegistros[m].getDate()) {
            return m;
        } else if (k < listaRegistros[m].getDate()) {
            high = m - 1;
        } else {
            low = m + 1;
        }
    }
    return -1;  
}

// Complejidad: O(n)

void Bitacora::BuscarDatos(){
    std::cout << "----------------------------------" << std::endl;
    std::cout << "| Bienvenido a mi base de datos. | " << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << "| Elige lo que quieres hacer.    |" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << "1. Buscar registro por fecha. " << std::endl;
    std::cout << "2. Salir. " << std::endl;
  
    std::string eleccion;
    
    std::cin >> eleccion;
  
    if (eleccion == "1"){

      std::cout << "Elige tu fecha de inicio: " << std::endl;  

  
    // Declaracion de variables importantes, la hora se divide por substrings.
  
      std::string mes;
      std::string dia;
      std::string hora;
      std::string minuto;
      std::string segundo;

      std::cout << "Ingresa el mes, formato: (Aug, Jun, Jan) " << std::endl;
      std::cin >> mes;
      std::cout << "Ingresa el día, formato: (00) " << std::endl;
      std::cin >> dia;
      std::cout << "Ingresa la hora, formato: (hh:mm:ss): " << std::endl;
      std::cin >> hora;
      std::string hh = hora.substr(0, 2);
      std::string mm = hora.substr(3, 2);
      std::string ss = hora.substr(6, 2);

  
      Registro f2(mes, dia, hh, mm, ss, " ", " ", " ");
      int inicio = f2.getDate();
  

      

      std::cout << "Elige tu fecha de fin: " << std::endl;

      // Esta parte transforma la fecha pedida de nuevo a substrings para despues convertirse en int referente a segundos.
  
      std::cout << "Ingresa el mes, formato: (Aug, Jun, Jan) " << std::endl;
      std::cin >> mes;
      std::cout << "Ingresa el día, formato: (00)" << std::endl;
      std::cin >> dia;
      std::cout << "Ingresa la hora, formato: (hh:mm:ss)" << std::endl;
      std::cin >> hora;
      hh = hora.substr(0, 2);
      mm = hora.substr(3, 2);
      ss = hora.substr(6, 2);
  
      Registro f3(mes, dia, hh, mm, ss, " ", " ", " ");
      int fin = f3.getDate();
  
  
      // Ahora esa fecha convertida a un entero puede servir facilmente como una key de busqueda.
  
      int indice1 = search(inicio);
      int indice2 = search(fin);
  
      // Aviso si no se encontro la fecha deseada utilizando el menos 1 que returnea la funcion. O(n)
  
      if (indice1 == -1 || indice2 == -1){
        std::cout << "No se pudo encontrar uno o todos los indices." << std::endl;
      }else{
        std::cout << "Resultados: " << (indice2 - indice1 + 1) << std::endl;
        for (int i = indice1; i < indice2 + 1; i++){
          std::cout << listaRegistros[i].getAll() << std::endl;
        }

        // Esto crea el archivo con los resultados O(n)
        
        std::ofstream crearResultados("resultado_busqueda.txt");
        std::string linea;
        if(crearResultados.is_open()){
          for (int j = indice1; j < indice2 + 1; j++){
            linea = listaRegistros[j].getAll();
            crearResultados << linea << std::endl;
          }
          std::cout << "Archivo de resultados creado correctamente. " << std::endl;
        }else{ // Uso de excepciones
          std::cout << "Fallo en creacion de archivo. " << std::endl;
        }
        crearResultados.close();
        if(!crearResultados.is_open()){
          std::cout << "El archivo se ha cerrado correctamente. " << std::endl;
        }else{
          std::cout << "El archivo no se ha cerrado correctamente. " << std::endl;
        }
}
    
    }else if(eleccion == "2"){
      std::cout << "Nos vemos!" << std::endl;
    }else{
      std::cout << "Opcion no valida!" << std::endl;
    }
  
}

  // Complejidad: O(n)

void Bitacora::crearBitacoraOrd(){
    std::ofstream readbitacora("bitacora_ordenada.txt");    
    std::string linea;
    if(readbitacora.is_open()){
      for(int i = 0; i<listaRegistros.getNumElements(); i++){
          linea = listaRegistros[i].getAll();
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



