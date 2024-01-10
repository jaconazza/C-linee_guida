#include <iostream>
#include <cmath>
using namespace std;

struct Matrix{
    int rows;
    int columns;
    int* mat;
};

//sintassi: Matrix matrix = {.rows = N, .columns = M, .mat = new int[N*M]};
//accedere ad un elemento:  matrix.mat[ matrix.columns * indice_riga + indice_colonna];

//inizializza una matrice di n righe e m colonne
Matrix init(int rows, int columns){
    return {.rows = rows, .columns = columns, .mat = new int[rows*columns]};
}

//inizializza una matrice di n righe, m colonne, passando un puntatore ad un array di int
Matrix complete_init(int rows, int columns, int* record){
    Matrix new_matrix = {.rows = rows, .columns = columns, .mat = new int[rows*columns]};
    for(int i=0; i<new_matrix.rows; i++){ //in alternativa:    for(int i=0; i<rows*columns; i++) new_matrix.mat[i] = record[i];
        for(int j=0; j<new_matrix.columns; j++){
            new_matrix.mat[ new_matrix.columns * i + j] = record[ columns * i +j];
        }
    }
    return new_matrix;
}

//inizializza a zero una matrice
Matrix zero_init(int rows, int columns){
    Matrix new_matrix = {.rows = rows, .columns = columns, .mat = new int[rows*columns]};
    for(int i=0; i<new_matrix.rows; i++){
        for(int j=0; j<new_matrix.columns; j++){
            new_matrix.mat[ new_matrix.columns * i + j] = 0;
        }
    }
    return new_matrix;
}


//drop della matrice
void drop(Matrix& matrix){
    delete[] matrix.mat;
    matrix.rows = 0;
    matrix.columns = 0;
}


//Visualizzazione di una matrice
void print_matrix(const Matrix& matrix){
    for(int i=0; i<matrix.rows; i++){
        for(int j=0; j<matrix.columns; j++){
            cout << matrix.mat[ matrix.columns * i + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


//funzione che ritorna il valore di un elemento data riga e colonna (-1 se gli indici sono sbagliati)
int get_value( const Matrix& matrix, const int row, const int column){
    if( (row>=0 && row<matrix.rows) && (column>=0 && column<matrix.columns)) return matrix.mat[ matrix.columns * row + column];
    return -1;
}

//funzione che cambia il valore in un punto della matrice
void set_value( const Matrix& matrix, const int row, const int column, const int value){
    if( (row>=0 && row<matrix.rows) && (column>=0 && column<matrix.columns)){
        matrix.mat[ matrix.columns * row + column] = value;
    }
}

// somma della diagonale di una matrice (SOLO PER MATRICI QUADRATE)
int get_diag_sum(const Matrix& matrix){
    if( matrix.columns == matrix.rows){
        int sum = 0;
        for(int i=0; i<matrix.rows; i++){
            sum += matrix.mat[ matrix.columns * i + i];
        }
        return sum;
    }
    return -1; //-1 potrebbe comunque essere un valore della somma della diagonale, ma fa lo stesso
}

//funzione che ritorna una matrice trasposta
Matrix get_transpose(const Matrix& matrix){
    Matrix tr_matrix = {.rows = matrix.columns, .columns = matrix.rows, .mat = new int[ matrix.rows * matrix.columns]};
    for(int i=0; i<matrix.rows; i++){
        for(int j=0; j<matrix.columns; j++){
            tr_matrix.mat[ tr_matrix.columns * j + i ] = matrix.mat[ matrix.columns * i +j];
        }
    }
    return tr_matrix;
}

//funzione che copia il contenuto della matrice source nella matrice destination (DIMENSIONI DET > DIMENSIONI SOURCE)
//se dest è piuù grande, copia i valori di soure negli indici corrispondenti in dest e lascia invariati gli elementi in più
void copy( const Matrix& source, Matrix& destination){
    if( (destination.rows >= source.rows) && (destination.columns >= source.columns)){
        for(int i=0; i<source.rows; i++){
            for(int j=0; j<source.columns; j++){
                destination.mat[ destination.columns * i + j] = source.mat[ source.columns * i + j];
            }
        }
    }
    return;
}


//funzione che ritorna una sottomatrice ELIMINANDO la riga e la colonna passati come argomento (utile per determinante)
Matrix get_sub_matrix(const Matrix& matrix, const int del_row, const int del_col){
    if( (del_row>=0 && del_row<matrix.rows) && (del_col>=0 && del_col<matrix.columns)){
        Matrix sub_matrix = {.rows = matrix.rows-1, .columns = matrix.columns-1, .mat = new int[ (matrix.rows-1)*(matrix.columns-1) ]};
        int k=0;
        for(int i=0; i<matrix.rows; i++){
            for(int j=0; j<matrix.columns; j++){
                if( i!=del_row && j!=del_col){
                    sub_matrix.mat[k] = matrix.mat[ matrix.columns * i +j ];
                    k++;
                }
            }
        }
        return sub_matrix;
    }
    return {.rows = 0, .columns = 0, .mat = nullptr};
}

//funzione che ritorna la matrice risultante dalla somma di due matrici (DEVONO AVERE LE STESSE DIMENSIONI) [in caso di dim diverse, ritorna matrice a nullptr]
Matrix get_sum_matrix(const Matrix& first, const Matrix& second){
    if( (first.rows == second.rows) && (first.columns == second.columns)){
        Matrix sum = {.rows = first.rows, .columns = first.columns, .mat = new int[first.rows*first.columns]};
        for(int i=0; i<first.rows; i++){
            for(int j=0; j<first.columns; j++){
                sum.mat[ sum.columns * i + j ] = first.mat[first.columns * i + j ] + second.mat[ second.columns * i + j];
            }
            //in alternativa:    for(int i=0; i<first.columns*first.rows; i++) sum.mat[ sum.columns * i + j ] = first.mat[first.columns * i + j ] + second.mat[ second.columns * i + j];
        }
        return sum;
    }
    return {.rows = 0, .columns = 0, .mat = nullptr};
}

//funzione che ritorn il prodotto fra matrici (NUMERO DI COLONNE DELLA PRIMA == NUMERO DI RIGHE DELLA SECONDA) [in alternativa ritorna una struct a nullptr]
Matrix get_product_matrix(const Matrix& first, const Matrix& second){
    if( first.columns == second.rows){
        Matrix product = {.rows = first.rows, .columns = second.columns, .mat = new int[ first.rows * second.columns] };
        int k = 0;
        int sum = 0;

        for(int i=0; i<first.rows; i++){
            for(int h=0; h<second.columns; h++){
                sum = 0;
                for(int j=0; j<first.columns; j++){
                    sum += first.mat[first.columns * i + j ] * second.mat[ second.columns * j + h];
                }
                product.mat[k] = sum;
                k++;
            }
        }

        return product;
    }
    return {.rows = 0, .columns = 0, .mat = nullptr};
}

//funzione per calcolare il determinante di una matrice (SOLO DI MATRICI QUADRATE)
//UTILIZZO LA REGOLA DI LAPLACE SULLA PRIMA RIGA DELLA MATRICE

int get_determinant(const Matrix& matrix){
    if( matrix.columns == matrix.rows ){
        if(matrix.columns == 1) return matrix.mat[0];

        int determinant = 0;
        for(int i=0; i<matrix.columns; i++){
            Matrix sub_matrix = get_sub_matrix(matrix, 0, i);
            determinant += matrix.mat[i] * pow(-1, i) * get_determinant( sub_matrix );
            drop(sub_matrix);
        }
        return determinant;
    }
    return -1; //accrocchio pure qua, ma chissene frega
}


// INVERSIONE DI RIGHE E COLONNE 

//funzione che ritorna una matriche con righe invertite
Matrix get_reverse_rows(const Matrix& matrix){
    Matrix reverse = {.rows = matrix.rows, .columns = matrix.columns, .mat = new int[matrix.columns*matrix.rows]};
    for(int i=0; i<matrix.rows; i++){
        for(int j=0; j<matrix.columns; j++){
            reverse.mat[ reverse.columns * (reverse.rows-1-i) + j] = matrix.mat[ matrix.columns * i + j];
        }
    }
    return reverse;
}

//funzione che passa una matrice e ne inverte righe  ( no return  )
void reverse_rows(Matrix& matrix){
    Matrix old = {.rows = matrix.rows, .columns = matrix.columns, .mat = new int[ matrix.columns*matrix.rows]};
    copy( matrix, old );
    for(int i=0; i<old.rows; i++){
        for(int j=0; j<old.rows; j++){
            matrix.mat[ matrix.columns * (matrix.rows-1-i) + j] = old.mat[ old.columns * i +j];
        }
    }
    drop(old);
}

//funzione che ritorna una matrice con colonne invertite
Matrix get_reverse_columns(const Matrix& matrix){
    Matrix reverse = {.rows = matrix.rows, .columns = matrix.columns, .mat = new int[matrix.columns*matrix.rows]};
    for(int i=0; i<matrix.rows; i++){
        for(int j=0; j<matrix.columns; j++){
            reverse.mat[ reverse.columns * i + (reverse.columns-1-j)] = matrix.mat[ matrix.columns * i + j];
        }
    }
    return reverse;
}

//funzione che passa una matrice e ne inverte le colonne ( no return )
void reverse_columns(Matrix& matrix){
    Matrix old = {.rows = matrix.rows, .columns = matrix.columns, .mat = new int[ matrix.rows * matrix.columns]};
    copy( matrix, old);
    for(int i=0; i<old.rows; i++){
        for(int j=0; j<old.columns; j++){
            matrix.mat[ matrix.columns * i + (matrix.columns-1-j)] = old.mat[ old.columns * i +j];
        }
    }
    drop(old);
}

//funzione che somma i valori adiacenti ad uno specifico elemento della matrice (elemento escluso)
int near_sum( const Matrix& matrix, const int sel_row, const int sel_col){
    if( (sel_row>=0 && sel_row<matrix.rows) && (sel_col>=0 && sel_col<matrix.columns)){
        int sum = 0;
        for(int i=0; i<3; i++){
            if( (sel_col-1+i)>=0 && (sel_col-1+i)<matrix.columns){
                if( sel_row-1 >= 0 ) sum += matrix.mat[ matrix.columns * (sel_row-1) + (sel_col-1+i)];
                if( (sel_col-1+i) != sel_col) sum+= matrix.mat[ matrix.columns * sel_row + (sel_col-1+i)];
                if( sel_row+1 < matrix.rows ) sum += matrix.mat[ matrix.columns * (sel_row+1) + (sel_col-1+i)];
            }
        }
        return sum;
    }
    return -1;
}

//funzione che aggiunge una riga alla matrice passata
void expand_row(Matrix& matrix){
    Matrix old = {.rows = matrix.rows, .columns = matrix.columns, .mat = new int[ matrix.rows * matrix.columns]};
    copy(matrix, old);
    drop(matrix);
    matrix = zero_init( old.rows+1, old.columns);
    copy(old, matrix);
    drop(old);
}

//funzione che aggiunge una colonna alla matrice passata
void expand_column(Matrix& matrix){
    Matrix old = {.rows = matrix.rows, .columns = matrix.columns, .mat = new int[ matrix.rows * matrix.columns]};
    copy(matrix, old);
    drop(matrix);
    matrix = zero_init( old.rows, old.columns+1);
    copy(old, matrix);
    drop(old);
}


int main(){

    int first[] = { 1,2,3,4,5,6,7,8,9};
    int second[] = {4,5,7,22,11,16,9,55,30};
    int no_sqr[] = {1,2,3,4,5,6};

    Matrix mat1 = complete_init(3,3, first);
    Matrix mat2 = complete_init(3,3,second);
    Matrix no_sq = complete_init(2,3, no_sqr);

    cout<<" Matrice 1: "<<endl;
    print_matrix(mat1);
    cout<<" Matrice 2:"<<endl;
    print_matrix(mat2);
    cout<<"Matrice non quadrata"<<endl;
    print_matrix(no_sq);

    cout<<"valore di mat1 in 0,0: "<< get_value( mat1, 0, 0) << endl;
    cout<<"valore inesistente di mat1 in -100, -100: "<< get_value( mat1, -100, -100)<<endl;

    cout<<"setto il valore di mat1 in 0,0 a 30: "<<endl;
    set_value( mat1, 0, 0, 30);
    print_matrix(mat1);
    cout<<"setto il valore di mat1 in 0,0 a 1"<<endl;
    set_value( mat1, 0, 0, 1);
    print_matrix(mat1);

    cout<<"Calcolo la somma della diagonale della matrice mat1: "<< get_diag_sum(mat1)<<endl;
    cout<<"Calcolo la somma della diagonale della matrice non quadrata: "<<get_diag_sum(no_sq)<<endl;
    cout<<endl;

    cout<<"Trasposta della matrice non quadrata: "<< endl;
    print_matrix(get_transpose(no_sq));

    cout<<"Matrice1 senza la riga 0 e colonna 0: "<< endl;
    print_matrix( get_sub_matrix( mat1, 0, 0));
    cout<<"Matrice1 senza riga 100 e colonna 0 (ritorno nullptr)"<<endl;
    print_matrix( get_sub_matrix(mat1, 100, 0));

    cout<<"Somma delle matrici 1 e 2: "<<endl;
    print_matrix( get_sum_matrix( mat1, mat2));
    cout<<"Errore sulla somma tra mat1 e non quadrata: (nullptr) "<<endl;
    print_matrix( get_sum_matrix( mat1, no_sq));

    cout<<"Prodotto fra matrice 1 e 2: "<<endl;
    print_matrix(get_product_matrix(mat1, mat2));
    cout<<"Errore sul prodotto fra mat1 e non quadrata (nullptr)"<<endl;
    print_matrix(get_product_matrix(mat1, no_sq));

    cout<<"Determinante della matrice1: "<< get_determinant(mat1)<<endl;
    cout<<"Determinante della matrice2: "<<get_determinant(mat2)<<endl;
    cout<<"Errore sul determinante di non quadrata (-1)"<< get_determinant(no_sq)<<endl;

    cout<<"Matrice1 a righe invertite: "<<endl;
    print_matrix(get_reverse_rows(mat1));
    cout<<"mAtrice2 a colonne invertite"<<endl;
    print_matrix(get_reverse_columns(mat2));

    cout<<"Somma adiacenti dell'elemento in posizione 0,0 in mat1: "<< near_sum(mat1, 0,0)<<endl;
    cout<<"Somma adiacenti dell'elemento in posizione 1,1 in mat1: "<< near_sum(mat1,1,1)<<endl;
    cout<<"Somma adiacenti dell'elemento in posizione 2,2, in mat1: "<< near_sum(mat1,2,2)<<endl;
    cout<<"Indice riga sballato (ritorno -1): "<< near_sum(mat1, 100,0)<< endl;
    cout<<"Indice colonna sballato (ritorno -1): "<< near_sum(mat1, 0, 100)<<endl;

    Matrix mat3 = zero_init(4,4);
    cout<<"Matrice di zeri 4x4: "<<endl;
    print_matrix(mat3);
    cout<<"copia della sezione di no sq in mat3: "<<endl;
    copy(no_sq, mat3);
    print_matrix(mat3);

    cout<<"Matrice1 con un l'espansione di una riga: "<<endl;
    expand_row(mat1);
    print_matrix(mat1);

    cout<<"Matrice1 con l'espansione di una colonna: "<<endl;
    expand_column(mat1);
    print_matrix(mat1);

    drop(mat1);
    drop(mat2);
    drop(mat3);
    drop(no_sq);

    return 0;
}