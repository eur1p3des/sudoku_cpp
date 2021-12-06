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

//DESC: Funció que retorna si s'ha trobat o no un valor específic
//PRE:
//POST:
bool includes(const vector<int>& valors, int valor){
  bool trobat = false;
  int iterador = 0;
  while (!trobat and iterador < int(valors.size())){
    if (valors[iterador] == valor){ trobat = true; }
    ++iterador;
  }
  return trobat;
}


//DESC:
//PRE:
//POST
vector <int> getPossibleValues(Matriu& sudoku, int fila, int columna){
  vector <int> posible_q;
  vector <int> posible_fc;
  vector <int> posible;
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
  return posible;
 
}


//DESC:
//PRE:
//POST:
bool unicValor(Matriu& sudoku, int fila, int columna, int valor){
  bool mandatory = true;
  int iterator = 0;

  while (mandatory and iterator < 9){
    //INV:
    
    if (columna != iterator and includes(getPossibleValues(sudoku, fila, iterator), valor)){
        mandatory = false;
    }
    if (fila != iterator and includes(getPossibleValues(sudoku, iterator, columna), valor)){
        mandatory = false;
    }
    ++iterator;
  }

  vector <int> submatriu = {
    fila/3,
    columna/3
  };
  
  for (int i = 0; i < 3 and mandatory; ++i){
    for (int j = 0; j < 3 and mandatory; ++j){
      if ( i != fila and j != columna and includes(getPossibleValues(sudoku,i,j), valor)){
        mandatory = false;
      }
    }
  }

  return mandatory;
}


//DESC: funció que quan main rep el parametre A retorna els posibles valors per  a una casella determinada.
//PRE:
//POST:
void function_a( Matriu& sudoku ){
  int fila, columna;
  char cl;
  vector <int> posibles;
  cin >> fila >> cl;
   
  cout << fila << cl << ": ";
  
  // Asignem els valors correctes per a la fila i la columna.
  fila -= 1;
  columna = cl - 'A';

  if (sudoku[fila][columna] == 0){
    posibles = getPossibleValues(sudoku, fila, columna);
   }else if (sudoku[fila][columna] != 0){
      cout << "[]" << endl;
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
 columna = col - 'A';

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
      cout << fila+1 << col << ": " << valor << " es un valor no possible" << endl;
    }
 }
 
 else {
   cout << fila+1 << char('A'+columna) << ": Casella no modificable " << endl;
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
  cout << "   A B C   D E F   G H I" << endl;
  int cont_f = 0, cont_c = 0;

  for (int i = 0; i < 9; ++i){
    //INV:
    cout << i+1 << " ";
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
      cout << "  -------+-------+-------" << endl;
    }
  }
}

//DESC: Funció que quan la funció main rep el paràmetre 'R', resol de forma automàtica el sudoku, indicant quin valor ha d'anar a cada casella.
//PRE: Rep la matriu sudoku
//POST: Retorna quin valor ha d'anar a cada casella així com el sudoku resolt.
void function_r( Matriu& sudoku){
 bool solved = false;

 while (!solved){
   //INV:
   bool changed = false;
   cout << endl;
   for (int fila = 0; fila < 9; ++fila){
     //INV:
     for (int columna = 0; columna < 9; ++columna){
       //INV:
       if (sudoku[fila][columna] == 0){
         vector <int> posibles_valors = getPossibleValues(sudoku, fila, columna);
         if (posibles_valors.size() == 1){
           sudoku[fila][columna] = posibles_valors[0];
           cout << "A la casella (" << fila+1 << "," << char('A'+columna) << ") hi ha d'anar un " << posibles_valors[0] << endl;
           changed = true;
         }
         else if(posibles_valors.size() > 1){
           for (int k = 0; k < int(posibles_valors.size()); ++k){
              //INV:
             if (unicValor(sudoku, fila,columna, posibles_valors[k])){
               sudoku[fila][columna] = posibles_valors[k];
               cout << "A la casella (" << fila+1 << "," << char('A'+columna) << ") hi ha d'anar un " << posibles_valors[k] << endl;
               changed = true;
               break;
             }
           }
         }
       }
     }
   }
   cout << endl;
   function_c(sudoku);
   if (!changed) { solved = true; }
 }
  
}

//DESC: Funció que permet omplir el sudoku.
//PRE: Rep la matriu sudoku buida.
//POST: Emmagatzema els valors entrats a la matriu sudoku.
void omple_sudoku(Matriu& sudoku){

  for (int i = 0; i < 9; ++i) {
    //INV: i recorre cada fila de la 0 a la 8 i no canvia de valor fins que s'han recorregut totes les columnes.
    for (int j = 0; j < 9; ++j) {
       //INV: j recorre cada columna de la 0 a la 8 per a cada fila del sudoku.
       cin >> sudoku[i][j];
    }
  }
}

//DESC: Funció que rep un caracter: {A,B,C,R} i executa la funció corresponent
//PRE: Rep un caràcter i executa la funció corresponent.
//POST: No retorna res.
void option(char opcio, Matriu& sudoku){
    if ( opcio == 'A' ){
      function_a(sudoku);
    }else if (opcio == 'B'){
      function_b(sudoku);
    }else if ( opcio == 'C' ){
      function_c(sudoku);
    }else if ( opcio == 'R' ){
      function_r(sudoku);
    }

}

//---------------------------------
// MAIN
//---------------------------------
int main(){
  Matriu sudoku(9, vector <int>(9));
  
  //OMPLIM LA MATRIU DEL SUDOKU
  omple_sudoku(sudoku); 
  //ESCOLLIM L'OPCIÓ DE JOC DESITJADA
  char c;
  cin >> c;

  while (c != 'Z'){
    //INV: Mentre el valor del caràcter c sigui diferent de Z es seguirà executant el programa.
    option(c, sudoku);
    cin >> c;
  }
}