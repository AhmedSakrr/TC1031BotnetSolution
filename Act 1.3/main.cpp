#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include "metodos.h"
#include "dateTime.h"
using namespace std;

// Rogelio Guzman Cruzado
// A01639914
// Jorge Guillén Berrueta
// A01639681

// Funcion trim que quita espacios en mis strings.

string trim(const string& str,
                 const string& whitespace = " \t")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

// Algoritmo de ordenamiento (quicksort).

int partition(std::vector<Bitacora> &A, int low, int high)
{
  int temp;
  string temp1;
  string temp2;
  int pivot = A[high].fechaconvertida;
  int i = low - 1;
  for (int j = low; j < high; j++)
  {
    if (A[j].fechaconvertida < pivot)
    {
      i++;
      temp = A[i].fechaconvertida;
      temp1 = A[i].fecha;
      temp2 = A[i].mensaje;
      A[i].fechaconvertida = A[j].fechaconvertida;
      A[i].fecha = A[j].fecha;
      A[i].mensaje = A[j].mensaje;
      A[j].fechaconvertida = temp;
      A[j].fecha = temp1;
      A[j].mensaje = temp2;
    }
  }
  temp = A[i + 1].fechaconvertida;
  temp1 = A[i + 1].fecha;
  temp2 = A[i + 1].mensaje;
  A[i + 1].fechaconvertida = A[high].fechaconvertida;
  A[i + 1].fecha = A[high].fecha;
  A[i + 1].mensaje = A[high].mensaje;
  A[high].fechaconvertida = temp;
  A[high].fecha = temp1;
  A[high].mensaje = temp2;
  return i + 1;
}

void quickSort(std::vector<Bitacora> &values, int low, int high)
{

  if (low < high)
  {
    int pivot = partition(values, low, high);
    quickSort(values, low, pivot - 1);
    quickSort(values, pivot + 1, high);
  }
}

// Algoritmo de busqueda binaria recursiva.

int binarySearchRecursive(std::vector<Bitacora> &values, int low, int high, int k, int compara)
{
  int m;
  if (low > high)
    return -1;
  compara++;
  m = low + (high - low) / 2;
  if (k == values[m].fechaconvertida)
    return m;
  else if (k < values[m].fechaconvertida)
    return binarySearchRecursive(values, low, m - 1, k, compara);
  else{
    return binarySearchRecursive(values, m + 1, high, k, compara);
  }

}

// Funciones para separar el string en substrings y luego convertirlos a int.

string separarMes(std::vector<Bitacora> &vector, int i)
{
  string mes;
  string linea;
  linea = vector[i].getFecha();
  mes = linea.substr(0, 3);
  return mes;
}

int separarDia(std::vector<Bitacora> &vector, int i)
{
  int dia;
  string linea;
  string temp;
  linea = vector[i].getFecha();
  if (linea.length() == 15){
    temp = linea.substr(4, 2);
  }else{
    temp = linea.substr(4,1);
  }


  dia = stoi(temp);
  return dia;
}

int separarHora(std::vector<Bitacora> &vector, int i)
{
  int hora;
  string linea;
  string temp;
  linea = vector[i].getFecha();
  if (linea.length() == 15){
      temp = linea.substr(7, 2);
  }else{
    temp = linea.substr(6, 2);
  }

  hora = stoi(temp);
  return hora;
}

int separarMinuto(std::vector<Bitacora> &vector, int i)
{
  int minuto;
  string linea;
  string temp;
  linea = vector[i].getFecha();
  if (linea.length() == 15){
      temp = linea.substr(10, 2);
  }else{
    temp = linea.substr(9, 2);
  }

  minuto = stoi(temp);
  return minuto;
}

int separarSegundo(std::vector<Bitacora> &vector, int i)
{
  int segundo;
  string linea;
  string temp;
  linea = vector[i].getFecha();
  if (linea.length() == 15){
      temp = linea.substr(13, 2);
  }else{
    temp = linea.substr(12, 2);
  }
  segundo = stoi(temp);
  return segundo;
}

int main()
{
  // Declaracion del vector.

  std::vector<Bitacora> miVectorFinal;


  // Lectura de archivo bitacora en forma de read.

  fstream file;
  file.open("bitacora.txt", ios::in);
  string line;
  if (file.is_open())
  {
    while (getline(file, line))
    {
      Bitacora temp;
      temp.setFecha(trim(line.substr(0, 15)));
      temp.setMensaje(trim(line.substr(15, string::npos)));
      miVectorFinal.push_back(temp);
    }
    file.close();
  }
  else
  {
    cout << "Archivo no existe" << endl;
  }


  // Converti mi string en ints para usar esta funcion en especifico.

  // Datetime f1 convierte mis fechas en un entero que representa la cantidad de segundos desde el 1 de enero de 1970 hasta esa fecha.

  for (int i = 0; i < miVectorFinal.size(); i++)
  {
    dateTime f1(separarMes(miVectorFinal, i), separarDia(miVectorFinal, i), separarHora(miVectorFinal, i), separarMinuto(miVectorFinal, i), separarSegundo(miVectorFinal, i));
    int temp2 = f1.getDate();
    miVectorFinal[i].setFechaCon(temp2);
  }

  // Sorteo del vector.

  quickSort(miVectorFinal, 0, miVectorFinal.size() - 1);


  // Esto escribe todos los datos de mi vector en un archivo ya completamente ordenados por fecha en orden ascendente.\
  // Gracias al uso de un vector de clase pudo existir facilmente la relacion entre la fecha en segundos y la fecha en strings y sus mensajes.

  ofstream myFile("bitacora_ordenada.txt");
  if (myFile.is_open())
  {
    int i;
    for (i = 0; i < miVectorFinal.size(); i++)
    {
      myFile << miVectorFinal[i].getFechacon() << " " << miVectorFinal[i].getFecha() << " " << miVectorFinal[i].getMensaje() << endl;
    }
    myFile.close();
  }
  else{
    cout << "No se pudo abrir el archivo";
  }


  // Inicializacion de mi menu.

  cout << "----------------------------------" << endl;
  cout << "| Bienvenido a mi base de datos. | " << endl;
  cout << "----------------------------------" << endl;
  cout << "| Elige lo que quieres hacer.    |" << endl;
  cout << "----------------------------------" << endl;
  cout << "1. Buscar registro por fecha. " << endl;
  cout << "2. Salir. " << endl;

  string eleccion;
  
  // Utilice getlines en vez de cins comunes por que no funcionaba con el formato de fecha pedido por el trabajo.

  std::getline(cin, eleccion);

  if (eleccion == "1"){
    cout << "Importante que tu fecha de consulta este formateada de esta manera." << endl;
    cout << "Ejemplos: " << "Jun 01 00:22:36, " << "Aug 10 03:21:41" << " Meses en ING." << endl;

    string rangoinicio;
    cout << "Elige tu fecha de inicio: ";
    std::getline(std::cin, rangoinicio);

    // Esta parte transforma la fecha pedida de nuevo a substrings para despues convertirse en int referente a segundos.

    string mes = rangoinicio.substr(0, 3);
    string dia = rangoinicio.substr(4, 2);
    string hora = rangoinicio.substr(7, 2);
    string minuto = rangoinicio.substr(10, 2);
    string segundo = rangoinicio.substr(13, 2);
    int diaT = stoi(dia);
    int horaT = stoi(hora);
    int minutoT = stoi(minuto);
    int segundoT = stoi(segundo);

    dateTime f2(mes, diaT, horaT, minutoT, segundoT);
    int inicio = f2.getDate();



    string rangofin;
    cout << "Elige tu fecha de fin: ";
    getline(cin, rangofin);
    
    // Esta parte transforma la fecha pedida de nuevo a substrings para despues convertirse en int referente a segundos.

    mes = rangofin.substr(0, 3);
    dia = rangofin.substr(4, 2);
    hora = rangofin.substr(7, 2);
    minuto = rangofin.substr(10, 2);
    segundo = rangofin.substr(13, 2);
    diaT = stoi(dia);
    horaT = stoi(hora);
    minutoT = stoi(minuto);
    segundoT = stoi(segundo);

    dateTime f3(mes, diaT, horaT, minutoT, segundoT);
    int fin = f3.getDate();


    // Ahora esa fecha convertida a un entero puede servir facilmente como una key de busqueda.
    int comparaciones;

    int indice1 = binarySearchRecursive(miVectorFinal, 0, miVectorFinal.size(), inicio, comparaciones);
    int indice2 = binarySearchRecursive(miVectorFinal, 0, miVectorFinal.size(), fin, comparaciones);

    // Aviso si no se encontro la fecha deseada utilizando el menos 1 que returnea la funcion.

    if (indice1 == -1 || indice2 == -1){
      cout << "No se pudo encontrar uno o todos los indices." << endl;
    }else{
      cout << "Resultados: " << (indice2 - indice1 + 1) << endl;
      for (int i = indice1; i < indice2 + 1; i++){
        cout << miVectorFinal[i].getFechacon() << " " << miVectorFinal[i].getFecha() << " " << miVectorFinal[i].getMensaje() << endl;
      }
    }


  }else if(eleccion == "2"){
    cout << "Nos vemos!" << endl;
    return 0;
  }else{
    cout << "Opcion no valida!" << endl;
    return 0;
  }

}
  
// Fin del programa
// Creado por Rogelio Guzman Cruzado.