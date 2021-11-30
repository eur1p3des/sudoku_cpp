//INCLUDING LIBRARIES
#include <iostream>
#include <vector>
#include <string>

//NAMESPACE
using namespace std;

//TYPEDEF
typedef vector<vector<int>> Matriu;

//------------------------------------------
//FUNCTIONS
//------------------------------------------

//DESC: funció que retorna els valors "correctes" per a una determinada casella, si aquests no apareixen a la mateixa fila ni a la mateixa columna.
//PRE: Rep la matriu sudoku, el valor de la fila, el valor de la columna, i el valor de la casella sudoku[fila][columna]
//POST: Retorna si el valor de la casella es posible o no per a aquella casella.
bool correcte_fila_columna( Matriu& sudoku, int fila, int columna, int valor ){
  Matriu back = sudoku;
  back[fila][columna] = valor;


  //Miramos en la columna
  for (int col = 0; col < 9; ++col){
    //INV:
    if (col != columna){
      if (back[fila][col] == back[fila][columna]){
        return false;
      }
    }
   }
  
  //Miramos en la fila
  for (int fil = 0; fil < 9; ++fil){
    //INV:
    if (fil != fila){
      if (back[fil][columna] == back[fila][columna]){
        return false;
      }
    }
  }

  return true;
}


//DESC: funció que retorna els valors "correctes" per a una determinada casella, si aquests no apareixen al mateix quadrant.
//PRE: Rep la matriu sudoku, el valor de la fila, el valor de la columna, i el valor de la casella sudoku[fila][columna]
//POST: Retorna si el valor de la casella es posible o no per a aquella casella.
bool correcte_quadrant( Matriu& sudoku, int fila, int columna, int valor ){
  Matriu back = sudoku;
  back[fila][columna] = valor;
  
  //Miramos el quadrante:
  int f = fila/3;
  int c = columna/3;
  for (int i = 0; i < 3; ++i){
    //INV:
    for (int j = 0; j < 3; ++j){
      //INV:
     if ((f*3+i != fila) and (c*3+j != columna)){
      if (back[fila][columna] == back[f*3+i][c*3+j]){
        return false;
      }
     }
    }
  }
  return true;
  
}


//DESC: funció que quan main rep el parametre A retorna els posibles valors per  a una casella determinada.
//PRE:
//POST:
void function_a( Matriu& sudoku ){
  int fila, columna;
  char cl;
  vector <int> posibles_fc; vector <int> posibles_q; vector <int>  posibles;

  cin >> fila >> cl;
  
  if ( cl == 'A' ){
    columna = 0;
    fila -= 1;

    if (sudoku[fila][columna] == 0){
      for (int i = 1; i <= 9; ++i){
        //INV:
        if (correcte_quadrant(sudoku,fila,columna,i)){
          posibles_q.push_back(i);
        }
        if (correcte_fila_columna(sudoku,fila,columna,i)){
          posibles_fc.push_back(i);
        }
      }

    }else if (sudoku[fila][columna] != 0){
      cout << "[]" << endl;
    }
  }else if ( cl == 'B' ){
    columna = 1;
    fila -= 1;
    
    if (sudoku[fila][columna] == 0){
      for (int i = 1; i <= 9; ++i){
        //INV:
        if (correcte_quadrant(sudoku,fila,columna,i)){
          posibles_q.push_back(i);
        }
        if (correcte_fila_columna(sudoku,fila,columna,i)){
          posibles_fc.push_back(i);
        }
      }
    }else if (sudoku[fila][columna] != 0){
      cout << "[]" << endl;
    }

  }else if ( cl == 'C' ){
    columna = 2;
    fila -= 1;
    
    if (sudoku[fila][columna] == 0){
      for (int i = 1; i <= 9; ++i){
        //INV:
        if (correcte_quadrant(sudoku,fila,columna,i)){
          posibles_q.push_back(i);
        }
        if (correcte_fila_columna(sudoku,fila,columna,i)){
          posibles_fc.push_back(i);
        }
      }
    }else if (sudoku[fila][columna] != 0){
      cout << "[]" << endl;
    }

  }else if ( cl == 'D' ){
    columna = 3;
    fila -= 1;
    
    if (sudoku[fila][columna] == 0){
      for (int i = 1; i <= 9; ++i){
        //INV:
        if (correcte_quadrant(sudoku,fila,columna,i)){
          posibles_q.push_back(i);
        }
        if (correcte_fila_columna(sudoku,fila,columna,i)){
          posibles_fc.push_back(i);
        }
      }
    }else if (sudoku[fila][columna] != 0){
      cout << "[]" << endl;
    }

  }else if ( cl == 'E' ){
    columna = 4;
    fila -= 1;
    
    if (sudoku[fila][columna] == 0){
      for (int i = 1; i <= 9; ++i){
        //INV:
        if (correcte_quadrant(sudoku,fila,columna,i)){
          posibles_q.push_back(i);
        }
        if (correcte_fila_columna(sudoku,fila,columna,i)){
          posibles_fc.push_back(i);
        }
      }
    }else if (sudoku[fila][columna] != 0){
      cout << "[]" << endl;
    }

  }else if ( cl == 'F' ){
    columna = 5;
    fila -= 1;
    
    if (sudoku[fila][columna] == 0){
      for (int i = 1; i <= 9; ++i){
        //INV:
        if (correcte_quadrant(sudoku,fila,columna,i)){
          posibles_q.push_back(i);
        }
        if (correcte_fila_columna(sudoku,fila,columna,i)){
          posibles_fc.push_back(i);
        }
      }
    }else if (sudoku[fila][columna] != 0){
      cout << "[]" << endl;
    }

  }else if ( cl == 'G' ){
    columna = 6;
    fila -= 1;  
    
    if (sudoku[fila][columna] == 0){
      for (int i = 1; i <= 9; ++i){
        //INV:
        if (correcte_quadrant(sudoku,fila,columna,i)){
          posibles_q.push_back(i);
        }
        if (correcte_fila_columna(sudoku,fila,columna,i)){
          posibles_fc.push_back(i);
        }
      }
    }else if (sudoku[fila][columna] != 0){
      cout << "[]" << endl;
    }

  }else if ( cl == 'H' ){
    columna = 7;
    fila -= 1;
    
    if (sudoku[fila][columna] == 0){
      for (int i = 1; i <= 9; ++i){
        //INV:
        if (correcte_quadrant(sudoku,fila,columna,i)){
          posibles_q.push_back(i);
        }
        if (correcte_fila_columna(sudoku,fila,columna,i)){
          posibles_fc.push_back(i);
        }
      }
    }else if (sudoku[fila][columna] != 0){
      cout << "[]" << endl;
    }

  }else if ( cl == 'I' ){
    columna = 8;
    fila -= 1;
    
    if (sudoku[fila][columna] == 0){
      for (int i = 1; i <= 9; ++i){
        //INV:
        if (correcte_quadrant(sudoku,fila,columna,i)){
          //if (correcte_fila_columna(sudoku,fila,columna,i)){
          posibles_q.push_back(i);
          //}
        }
        if (correcte_fila_columna(sudoku,fila,columna,i)){
          posibles_fc.push_back(i);
        }
      }
    }else if (sudoku[fila][columna] != 0){
      cout << "[]" << endl;
    }

  }
  int val;
  for (int i = 0; i < int(posibles_fc.size()); ++i){
    //INV:
      for (int j = 0; j < int(posibles_q.size()); ++j){
        //INV:
        if (posibles_fc[i] == posibles_q[j]){ 
          val = posibles_q[j];
          posibles.push_back(val);
        }
      }
  }
  
  int tamany = posibles.size();

  if (tamany == 1){
    cout << "[" << posibles[0] << "]"<< endl;
  }else if ( tamany > 1 ){
    cout << "[";
    for (int i = 0; i < tamany-1; ++i){
      //INV:
      cout << posibles[i] << ", ";
    }
    cout << posibles[tamany-1] << "]"<< endl;
  }
  

}

//DESC: Funció que quan es rep el parametre B en la funció main, omple la casella seleccionada (si està buida) i si el valor pot ser insertat.
//PRE: Rep la matriu sudoku
//POST: Retorna:
// - Casella no modificable: si aquella casella ja està omplerta, és a dir sudoku[fila][columna] != 0
// - Valor no posible: si el valor que volem insertar ja es troba al quadrant, a la fila o a la columna.push_back(i);
// - No retorna res si s'ha pogut insertar el valor.
void function_b( Matriu& sudoku ){
 int fila, columna, valor;
 char col; 
 cin >> fila >> col >> valor;
 vector <int> posible_q; vector <int> posible_fc; vector <int> posible;
 
 fila = fila - 1;

 if (col == 'A'){
  columna = 0;

 }else if (col == 'B'){
  columna = 1;

 }else if (col == 'C'){
  columna = 2;

 }else if (col == 'D'){
  columna = 3;

 }else if (col == 'E'){
  columna = 4;

 }else if (col == 'F'){
  columna = 5;

 }else if (col == 'G'){
  columna = 6;

 }else if (col == 'H'){
  columna = 7;

 }else if (col == 'I'){
  columna = 8;

 }else {
    cout << " Columna no correcte, torneu a introduir els valors per a aquesta casella " << endl;
    function_b(sudoku);
 }


  for (int i = 1; i <= 9; ++i){
    //INV:
        if (correcte_quadrant(sudoku,fila,columna,i)){
          posible_q.push_back(i);
        }
        if (correcte_fila_columna(sudoku,fila,columna,i)){
          posible_fc.push_back(i);
        }
  }
  int val;
  for (int i = 0; i < int(posible_fc.size()); ++i){
      //INV:
      for (int j = 0; j < int(posible_q.size()); ++j){
        //INV:
        if (posible_fc[i] == posible_q[j]){ 
          val = posible_q[j];
          posible.push_back(val);
        }
      }
  }
  
  if ( sudoku[fila][columna]  == 0){
   int cont = 0;
  
   for (int i = 0; i < int(posible.size()); ++i){
    //INV:
    if (posible[i] == valor){
      cont++;
    }
   }
   if(cont != 0){
      sudoku[fila][columna] = 0;
      sudoku[fila][columna] = valor;
    }else{
     cout << "Valor no posible: " << valor << endl;
    }
 }
 
 else {
   cout << "Casella no modificable " << fila << " " << columna << " " << sudoku[fila][columna] << endl;
 }


}

//DESC: Funció que quan rep el paràmetre "c" a la funció main, retorna l'estat actual del sudoku
//PRE: matriu sudoku
//POST: retorna l'estat actual del sudoku en el següent format:
//    A B C   D E F   G H I
//1   . 2 6 | . . . | 3 7 8
//2   . 5 8 | 6 3 7 | 4 . .
//3   . 4 7 | . . . | 5 6 1
// -------+-------+-------
//4   . . . | 7 2 . | 9 . .
//5   . . . | 3 . 8 | 2 5 .
//6   8 . 2 | . . . | . 1 .
// -------+-------+-------
//7   4 6 9 | 5 . 1 | . . .
//8   . . 1 | 9 . . | 7 4 .
//9   . 3 . | . 4 . | . 9 5
// on els '.' corresponen a les caselles buides.
void function_c( Matriu& sudoku ){
  cout << "    A B C   D E F   G H I" << endl;
  int cont_f = 0, cont_c = 0;

  for (int i = 0; i < 9; ++i){
    //INV:
    cout << i+1 << "  ";
    cont_f++;
    for (int j = 0; j < 9; ++j){
      //INV:
      if ( cont_c == 3 or cont_c == 6 ){
        cout << " |";
      }
      if ( sudoku[i][j] == 0 ){
        cout << " .";
      }else{
        cout << " " << sudoku[i][j];
      }
      cont_c++;
    }
    cont_c = 0;
    cout << endl;

    if (cont_f == 3 or cont_f == 6){
      cout << " -------+-------+-------" << endl;
    }
  }
}


//DESC: Funció que quan la funció main rep el paràmetre 'R', resol de forma automàtica el sudoku, indicant quin valor ha d'anar a cada casella.
//PRE: Rep la matriu sudoku
//POST: Retorna quin valor ha d'anar a cada casella així com el sudoku resolt.
void function_r( Matriu& sudoku){
 Matriu back = sudoku;
 
}
//MAIN
int main(){
  Matriu sudoku(9, vector <int>(9));
  
  //OMPLIM LA MATRIU
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      cin >> sudoku[i][j];
    }
  }
  
  //ESCOLLIM L'OPCIÓ DE JOC DESITJADA
  char c;
  cin >> c;

  while (c != 'Z'){
    //INV: Mentre el valor del caràcter c sigui diferent de Z es seguirà executant el programa.
    if ( c == 'A' ){
      function_a(sudoku);
    }else if (c == 'B'){
      function_b(sudoku);
    }else if ( c == 'C' ){
      function_c(sudoku);
    }else if ( c == 'R' ){
      function_r(sudoku);
    }

    cin >> c;
  }
}
