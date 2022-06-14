/** 
* Ejemplo que implementa dos representaciones de Grafos
* (Matriz de adyacencia y Lista de adyacencia) y el 
* algoritmos BFS 
*
* Compilacion para debug:  
*    g++ -std=c++17 -g -o main *.cpp 
* Ejecucion con valgrind:
*    nix-env -iA nixpkgs.valgrind
*    valgrind --leak-check=full ./main 
*
* Compilacion para ejecucion:  
*    g++ -std=c++17 -O3 -o main *.cpp 
* Ejecucion:
*    ./main 
**/

// Actividad integral 4.3, grafos
// Rogelio Guzman Cruzado - a01639914
// Jorge Guillen Berrueta - A01639681
// Alan Ricardo Vilchis Arceo - A01640260

// Complejidades en .h

#include <iostream>
#include "Bitacora.h"

int main() {
  Bitacora myBitacora("bitacoraGrafos.txt");
  return 0;
}