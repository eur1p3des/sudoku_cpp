// INCLUDING LIBRARIES
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// NAMESPACE
using namespace std;

// TYPEDEF
typedef vector< vector<int> > Matriu;

//------------------------------------------
// FUNCTIONS
//------------------------------------------

// DESC: funció que retorna els valors "correctes" per a una determinada casella, si aquests no apareixen a la mateixa fila ni a la mateixa columna.
// PRE: Rep la matriu sudoku, el valor de la fila, el valor de la columna, i el valor de la casella sudoku[fila][columna]
// POST: Retorna si el valor de la casella es posible o no per a aquella casella.
bool correcte_fila_columna(Matriu &sudoku, int fila, int columna, int valor)
{
  Matriu back = sudoku;
  back[fila][columna] = valor;

  for (int col = 0; col < 9; ++col)
  {
    // INV: col conté la posició de la columna per a cada fila.
    if (col != columna)
    {
      if (back[fila][col] == back[fila][columna])
      {
        return false;
      }
    }
  }

  // Miramos en la fila
  for (int fil = 0; fil < 9; ++fil)
  {
    // INV: fil augmenta en 1 a cada iteració i conté la fila actual dins d'una columna.
    if (fil != fila)
    {
      if (back[fil][columna] == back[fila][columna])
      {
        return false;
      }
    }
  }

  return true;
}

// DESC: funció que retorna els valors "correctes" per a una determinada casella, si aquests no apareixen al mateix quadrant.
// PRE: Rep la matriu sudoku, el valor de la fila, el valor de la columna, i el valor de la casella sudoku[fila][columna]
// POST: Retorna si el valor de la casella es posible o no per a aquella casella.
bool correcte_quadrant(Matriu &sudoku, int fila, int columna, int valor)
{
  Matriu back = sudoku;
  back[fila][columna] = valor;

  int f = fila / 3;
  int c = columna / 3;
  for (int i = 0; i < 3; ++i)
  {
    // INV: i conté la fila dins d'un quadrant.
    for (int j = 0; j < 3; ++j)
    {
      // INV: j conté la columna dins d'un quadrant.
      if ((f * 3 + i != fila) and (c * 3 + j != columna))
      {
        if (back[fila][columna] == back[f * 3 + i][c * 3 + j])
        {
          return false;
        }
      }
    }
  }
  return true;
}

bool findEmptyPlace(Matriu &grid, int &row, int &col)
{ // get empty location and update row and column
  for (row = 0; row < (int)grid.size(); row++)
    for (col = 0; col < (int)grid[0].size(); col++)
      if (grid[row][col] == 0) // marked with 0 is empty
        return true;
  return false;
}

//DESC:
//PRE:
//POST:
bool esCorrectePos(Matriu &grid, int row, int col, int num)
{
  return correcte_fila_columna(grid, row, col, num) && correcte_quadrant(grid, row, col, num);
}

// DESC: Funció que busca els possibles valors per a una cassella.
// PRE: Rep la matriu sudoku, la fila i la columna.
// POST: Retorna un vector amb els posibles valors dins de la casella sudoku[fila][columna]
vector<int> trobaValors(Matriu &sudoku, int fila, int columna)
{
  vector<int> posible_q;
  vector<int> posible_fc;
  vector<int> posible;
  for (int i = 1; i <= 9; ++i)
  {
    // INV: i conté un valor a comprobar si és correcte per la casella.
    if (correcte_quadrant(sudoku, fila, columna, i))
    {
      posible_q.push_back(i);
    }
    if (correcte_fila_columna(sudoku, fila, columna, i))
    {
      posible_fc.push_back(i);
    }
  }
  int val;
  for (int i = 0; i < int(posible_fc.size()); ++i)
  {
    // INV: i és menor al tamany de posible_fc, i aquest valor 'i' conté la posició dins el vector posible_fc.
    for (int j = 0; j < int(posible_q.size()); ++j)
    {
      // INV:j és menor al tamany de posible_q, i aquest valor 'j' conté la posició dins el vector posible_q.
      if (posible_fc[i] == posible_q[j])
      {
        val = posible_q[j];
        posible.push_back(val);
      }
    }
  }
  return posible;
}

// DESC: funció que quan main rep el parametre A retorna els posibles valors per  a una casella determinada.
// PRE: Rep la matriu sudoku.
// POST: Retorna els valors posibles per a una casella i una columna determinada
void function_a(Matriu &sudoku)
{
  int fila, columna;
  char cl;
  vector<int> posibles;
  cin >> fila >> cl;

  cout << fila << cl << ": ";

  fila -= 1;
  columna = cl - 'A';

  if (sudoku[fila][columna] == 0)
  {
    posibles = trobaValors(sudoku, fila, columna);
  }
  if (sudoku[fila][columna] != 0)
  {
    cout << "[]" << endl;
  }

  int tamany = posibles.size();
  if (tamany == 1)
  {
    cout << "[" << posibles[0] << "]" << endl;
  }
  if (tamany > 1)
  {
    cout << "[";
    for (int i = 0; i < tamany - 1; ++i)
    {
      // INV: i conté la posició dins del vector, sent i estrictament menor al tamany del vector - 1, per a poder aplicar el format i que en l'últim valor no hi hagi una coma. És a dir: El tamany és 3, i els valors del vector són 1,2,3. Al printar-ho, si no apliquéssim aquest filtre ens queda de la següent forma: [1,2,3,]. Al aplicar aquest filtre, el resultat del bucle serà 1,2,   . I així, després podem printar l'últim valor sense necessitat de la coma.
      cout << posibles[i] << ", ";
    }
    cout << posibles[tamany - 1] << "]" << endl;
  }
}

// DESC: Funció que quan es rep el parametre B en la funció main, omple la casella seleccionada (si està buida) i si el valor pot ser insertat.
// PRE: Rep la matriu sudoku
// POST: Retorna:
//  - Casella no modificable: si aquella casella ja està omplerta, és a dir sudoku[fila][columna] != 0
//  - Valor no posible: si el valor que volem insertar ja es troba al quadrant, a la fila o a la columna.push_back(i);
//  - No retorna res si s'ha pogut insertar el valor.
void function_b(Matriu &sudoku, Matriu &back)
{
  int fila, columna, valor;
  char col;
  cin >> fila >> col >> valor;

  vector<int> posible;
  fila = fila - 1;
  columna = col - 'A';

  if (back[fila][columna] == 0)
  {
    posible = trobaValors(sudoku, fila, columna);
    int cont = 0;

    for (int i = 0; i < int(posible.size()); ++i)
    {
      // INV: i val la posició en el vector posible, i ha de tenir un valor estrictament inferior al del tamany del vector.
      if (posible[i] == valor)
      {
        cont++;
      }
    }
    if (cont != 0)
    {
      sudoku[fila][columna] = 0;
      sudoku[fila][columna] = valor;
    }
    if (cont == 0)
    {
      cout << fila + 1 << col << ": " << valor << " es un valor no possible" << endl;
    }
  }

  if (back[fila][columna] != 0)
  {
    cout << fila + 1 << char('A' + columna) << ": Casella no modificable " << endl;
  }
}

// DESC: Funcio que quan rep el par�metre "c" a la funció main, retorna l'estat actual del sudoku
// PRE: matriu sudoku
// POST: retorna l'estat actual del sudoku en el següent format:
//     A B C   D E F   G H I
// 1   . 2 6 | . . . | 3 7 8
// 2   . 5 8 | 6 3 7 | 4 . .
// 3   . 4 7 | . . . | 5 6 1
//  -------+-------+-------
// 4   . . . | 7 2 . | 9 . .
// 5   . . . | 3 . 8 | 2 5 .
// 6   8 . 2 | . . . | . 1 .
//  -------+-------+-------
// 7   4 6 9 | 5 . 1 | . . .
// 8   . . 1 | 9 . . | 7 4 .
// 9   . 3 . | . 4 . | . 9 5
//  on els '.' corresponen a les caselles buides.
void function_c(Matriu &sudoku)
{
  char l_columna[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
  cout << "  ";

  for (int i = 0; i < int(sizeof(l_columna)); ++i)
  {
    // INV: Per a cada valor de i, sent i estrictament menor al tamany de l'array de caracters, es printa el valor que hi ha ha a aquesta posició en l'array
    // l_columna.
    if ((i + 1 / 3 == 3) or (i + 1 / 3 == 6))
    {
      cout << "  ";
    }
    cout << " " << l_columna[i];
  }
  cout << endl;
  int cont_f = 0, cont_c = 0;

  for (int i = 0; i < 9; ++i)
  {
    // INV: Per a cada valor de i (fila), mostrarem la fila en la que ens trobem: i+1, i recorrerem cada columna d'aquesta fila.
    cout << i + 1 << " ";
    cont_f++;
    for (int j = 0; j < 9; ++j)
    {
      // INV: Per a cada valor de j (columna), printarem el valor que hi ha en la posició sudoku[i][j]
      if (cont_c == 3 or cont_c == 6)
      {
        cout << " |";
      }
      if (sudoku[i][j] == 0)
      {
        cout << " .";
      }
      if (sudoku[i][j] != 0)
      {
        cout << " " << sudoku[i][j];
      }
      cont_c++;
    }
    cont_c = 0;
    cout << endl;

    if (cont_f == 3 or cont_f == 6)
    {
      cout << "   -------+-------+-----" << endl;
    }
  }
}

// DESC: Funció que quan la funció main rep el paràmetre 'R', resol de forma automàtica el sudoku, indicant quin valor ha d'anar a cada casella.
// PRE: Rep la matriu sudoku
// POST: Retorna quin valor ha d'anar a cada casella així com el sudoku resolt.
/*bool function_r(Matriu &sudoku, Matriu& back)
{
  int row, col;
  int i = 0;
  if (!findEmptyPlace(sudoku, row, col))
  {    
    return true;
  } // when all places are filled
  for (int num = 1; num <= 9; num++)
  {
    //INV: num conté el posible valor per a una casella en concret
    if (esCorrectePos(sudoku, row, col, num))
    {
      sudoku[row][col] = num;
      if (function_r(sudoku, back)){ 
        return true;
      }
      sudoku[row][col] = 0;
    }
    cout << "A la casella (" << row + 1 << "," << char(col + 'A') << ") hi ha d'anar:" << num << endl;
  }
  return false;
}*/

bool function_r(Matriu &sudoku, Matriu &back)
{
  int fila, columna;
  if (!findEmptyPlace(sudoku, fila, columna))
  {
    function_c(sudoku);
    return true;
  }
  for (int fil = 0; fil < 9; fil++)
  {
    for (int col = 0; col < 9; col++)
    {
      if (sudoku[fil][col] == 0)
      {
        vector<int> posibles = trobaValors(sudoku, fil, col);

        if ((int)posibles.size() == 1)
        {
          sudoku[fil][col] = posibles[0];
          cout << "A la casella (" << fil + 1 << ", " << char(col + 'A') << " ) hi ha d'anar un: " << posibles[0] << endl;
        }
        if ((int)posibles.size() > 1)
        {
          for (int i = 0; i < posibles.size(); ++i){
            if (esCorrectePos(sudoku, fila, columna, posibles[i]))
            {
              sudoku[fila][columna] = posibles[i];
              cout << "A la casella (" << fil + 1 << ", " << char(col + 'A') << " ) hi ha d'anar un: " << posibles[0] << endl;
              if (function_r(sudoku, back))
              {
                return true;
              }
              sudoku[fil][col] = 0;
            }
          }
        }
      }
    }
  }
  return false;
}

// DESC: Funció que permet omplir el sudoku.
// PRE: Rep la matriu sudoku buida.
// POST: Emmagatzema els valors entrats a la matriu sudoku.
void omple_sudoku(Matriu &sudoku)
{
  for (int i = 0; i < 9; ++i)
  {
    // INV: i recorre cada fila de la 0 a la 8 i no canvia de valor fins que s'han recorregut totes les columnes.
    for (int j = 0; j < 9; ++j)
    {
      // INV: j recorre cada columna de la 0 a la 8 per a cada fila del sudoku.
      cin >> sudoku[i][j];
    }
  }
}

// DESC: Funció que rep un caracter: {A,B,C,R} i executa la funció corresponent
// PRE: Rep un caràcter i executa la funció corresponent.
// POST: No retorna res.
void option(char opcio, Matriu &sudoku, Matriu &back)
{
  if (opcio == 'A')
  {
    function_a(sudoku);
  }
  else if (opcio == 'B')
  {
    function_b(sudoku, back);
  }
  else if (opcio == 'C')
  {
    function_c(sudoku);
  }
  else if (opcio == 'R')
  {
    function_r(sudoku, back);
    if (function_r(sudoku, back) == true){
      function_c(sudoku);
    }
    function_c(sudoku);
  }
}

//---------------------------------
// MAIN
//---------------------------------
int main()
{
  Matriu sudoku(9, vector<int>(9));

  omple_sudoku(sudoku);
  Matriu back = sudoku;

  char c;
  cin >> c;

  while (c != 'Z')
  {
    // INV: Mentre el valor del caràcter c sigui diferent de Z es seguirà executant el programa.
    option(c, sudoku, back);
    cin >> c;
  }
}
