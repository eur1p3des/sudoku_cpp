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
  //Creem un arrai de caràcters, per als noms de les columnes
  char l_columna[] = {'A','B','C','D','E','F','G','H','I'};
  //Printem l'espai doble per a que quedi ben quadrat amb el sudoku.
  cout << "  ";
  
  for (int i = 0; i < int(sizeof(l_columna)); ++i){
    //INV: Per a cada valor de i, sent i estrictament menor al tamany de l'array de caracters, es printa el valor que hi ha ha a aquesta posició en l'array
    //l_columna.
    if ((i+1 / 3 == 3) or (i+1 / 3 == 6)){
      //Si al sumar-li 1 a la posició, per a obtindre la columna real, ens dona 3 o 6, printarem un doble espaiat, per a que cuadri amb el sudoku.
      cout << "  ";
    }
    //Printem, mantinguent un espaiat davant, el caràcter que hi ha a la posició i de l'array l_columna.
    cout << " " << l_columna[i];
  }
  //Printem un salt de línia.
  cout << endl;
  //Cont_f = contador de files ; cont_c = contador de columnes
  int cont_f = 0, cont_c = 0;

  for (int i = 0; i < 9; ++i){
    //INV: Per a cada valor de i (fila), mostrarem la fila en la que ens trobem: i+1, i recorrerem cada columna d'aquesta fila.
    cout << i+1 << " ";
    //El contador de files es incrementat en 1 per a cada fila recorreguda.
    cont_f++;
    for (int j = 0; j < 9; ++j){
      //INV: Per a cada valor de j (columna), printarem el valor que hi ha en la posició sudoku[i][j]
      if ( cont_c == 3 or cont_c == 6 ){
        //Si la variable cont_c (contador de columnes) val 3 o val 6 es printarà el caràcter | acompanyat de 2 espais, per a mostrar que s'ha acabat les columnes del quadrant.
        cout << " |";
      }
      if ( sudoku[i][j] == 0 ){
        //Quan sudoku[i][j] val 0, es mostrarà un . simbolitzant que aquella casella està buida.
        cout << " .";
      }
      if (sudoku[i][j] != 0){
        //Si la casella no val 0 (no està buida), es mostrarà el valor que té la casella.
        cout << " " << sudoku[i][j];
      }
      //Augmentem en 1 el valor actual del contador de columnes.
      cont_c++;
    }
    //Un cop recorregudes totes les columnes de la fila, reinizalitzem el contador de columnes a 0.
    cont_c = 0;
    //Printem un salt de línia.
    cout << endl;

    if (cont_f == 3 or cont_f == 6){
      //Si el contador de files val 3 o 6, es printarà una línia simbolitzant que s'ha arribat a la última fila del qadrant.
      cout << "-------+-------+-------" << endl;
    }
  }
}

//DESC: Funció que quan la funció main rep el paràmetre 'R', resol de forma automàtica el sudoku, indicant quin valor ha d'anar a cada casella.
//PRE: Rep la matriu sudoku
//POST: Retorna quin valor ha d'anar a cada casella així com el sudoku resolt.
void function_r( Matriu& sudoku){
 bool solved = false;

 while (!solved){
   //INV: Mentre el boleà solved no sigui true es seguirà executant el bucle.
   bool changed = false;
   cout << endl;
   for (int fila = 0; fila < 9; ++fila){
     //INV: Per a cada fila, recorrem totes les columnes.
     for (int columna = 0; columna < 9; ++columna){
       //INV:sudoku[fila][columna] conté el valor de actual de la posició fila-columna en la que es troba el bucle. Exemple: fila 1 columna B -> 1B = 0
       if (sudoku[fila][columna] == 0){
         //Si el valor del sudoku a la fila i columna indicats és igual a 0 s'entra al condicional, si no no s'hi entra.
         //Declarem un vector anomentat posibles_valors, que contingui els valors posibles per a la fila i la columna indicats.
         vector <int> posibles_valors = getPossibleValues(sudoku, fila, columna);
         if (posibles_valors.size() == 1){
           //Si el tamany del vector posibles_valors és igual a 1, s'asigna a la posició en la que estem el valor que hi ha a posibles_valors.
           sudoku[fila][columna] = posibles_valors[0];
           // Es mostra el missatge indicant que a la fila i la columna actuals hi ha d'anar el valor contingut a posibles_valors.
           cout << "A la casella (" << fila+1 << "," << char('A'+columna) << ") hi ha d'anar un " << posibles_valors[0] << endl;
           //Es canvia el boleà changed a true, indicant que hi ha hagut un canvi en el nostre sudoku.
           changed = true;
         }
         if(posibles_valors.size() > 1){
           //Si el tamany del vector posibles_valors és major que 1, s'entra al condicional.
           for (int k = 0; k < int(posibles_valors.size()); ++k){
              //INV: k és la posició actual dins del vector posibles_valors, aquesta k < el tamamny de posibles_valors.
             if (unicValor(sudoku, fila,columna, posibles_valors[k])){
               //Si la funció unicValor ( que mira que aquest valor només pugui ser assignat en aquesta posició) retorna true, s'asigna el valor a la fila i la columna.
               sudoku[fila][columna] = posibles_valors[k];
               // Es mostra el missatge indicant que a la fila i la columna actuals hi ha d'anar el valor que es troba en la posició k del vector posibles_valors.
               cout << "A la casella (" << fila+1 << "," << char('A'+columna) << ") hi ha d'anar un " << posibles_valors[k] << endl;
               // Es canvia el boleà changed a true, indicant que hi ha hagut un canvi en el nostre sudoku.
               changed = true;
               // Es surt del bucle, que mira per a cada posició del vector posibles_valors, ja que ja s'ha trobat el valor per a aquella casella.
               break;
             }
           }
         }
       }
     }
   }
   //Printem un salt de línia
   cout << endl;
   //Cridem a la funció function_c per a que printi el sudoku.
   function_c(sudoku);
   //Si no hi ha hagut canvis (changed == false) el boleà solved pasa a valdre true, ja que si no s'ha modificat res, vol dir que el sudoku ja estava resolt.
   if (!changed) { solved = true;}
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