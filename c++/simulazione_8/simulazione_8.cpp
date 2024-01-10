#include <iostream>
using namespace std;

struct Matrix{
    int row;
    int columns;
    int* mat;
};


Matrix init(int rows, int columns, int* matrix){
    Matrix new_matrix =  {.row = rows, .columns = columns, .mat = new int [rows*columns]};
    for(int i=0; i<rows*columns; i++){
        new_matrix.mat[i] = matrix[i];
    }
    return new_matrix;
}

Matrix trasponi(const Matrix& matrix){
    Matrix trasposta = {.row = matrix.columns, .columns = matrix.row, .mat = new int [ matrix.row * matrix.columns ]};
    for(int i=0; i<matrix.row; i++){
        for(int j=0; j<matrix.columns; j++){
            trasposta.mat[ matrix.row * j +i ] = matrix.mat[ matrix.columns * i +j];
        }
    }
    return trasposta;
}

Matrix somma(const Matrix& first, const Matrix& second){
    if( (first.row == second.row ) && (first.columns == second.columns)){
        Matrix sum = {.row = first.row, .columns = first.columns, .mat = new int[first.row*first.columns]};
        for(int i=0; i<first.row; i++){
            for(int j=0; j<first.columns; j++){
                sum.mat[ sum.columns * i + j] = first.mat[ first.columns * i +j] + second.mat[ second.columns * i +j];
            }
        }
        return sum;
    }
    else return {.row = 0, .columns = 0, .mat = nullptr};
}

Matrix submatrix( Matrix& matrix, int del_row, int del_col){
    Matrix submat = {.row = matrix.row-1, .columns = matrix.columns-1, .mat = new int[ (matrix.row-1)*(matrix.columns-1)]};
    int k = 0;
    for(int i=0; i<matrix.row; i++){
        for(int j=0; j<matrix.columns; j++){
            if(i != del_row && j!=del_col){
                submat.mat[ k ] = matrix.mat[ matrix.columns * i +j];
                k++;
            }
        }
    }
    return submat;
}


void print( const Matrix& matrix){
    for(int i=0; i<matrix.row; i++){
        for(int j=0; j<matrix.columns; j++){
            cout<< matrix.mat[ matrix.columns * i +j] << " ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int determinante( Matrix& matrix){
    if( matrix.columns == matrix.row){
        if( matrix.columns == 1) return matrix.mat[0];
        int det = 0;
        for(int i=0; i<matrix.columns; i++){
            Matrix sub = submatrix( matrix, 0, i);
            det += matrix.mat[i] * pow( -1, i ) * determinante(sub);
            delete[] sub.mat;
        }
        return det;
    }
    return 0;
}

Matrix matrix_product(const Matrix& first, const Matrix& second){
    if( first.columns == second.row ){
        Matrix product = {.row = first.row, .columns = second.columns, .mat = new int[ first.row*second.columns]};
        int k = 0;
        int sum = 0;
        
        for(int i=0; i<first.row; i++){
            for(int h=0; h<second.columns; h++){
                sum = 0;
                for(int j=0; j<first.columns; j++){
                    cout<<"Prodotto fra: ["<<i<<"-"<<j<<"] e ["<<j<<"-"<<h<<"]:     "<< first.mat[ first.columns * i + j] << "  e " << second.mat[ second.columns * j + h] << endl;
                    sum += first.mat[ first.columns * i + j] * second.mat[ second.columns * j + h];
                }
                cout<<endl;
                product.mat[k] = sum;
                k++;
            }
        }
        return product;

    }
    return {.row = 0, .columns = 0, .mat = nullptr};
}

int somma_adiacenti(const Matrix& matrix, int row, int col){
    int sum = 0;
    for(int i=0; i<3; i++){
        if( (col-1+i)>=0 && (col-1+i<matrix.columns)){
            if( row-1 >= 0 ) sum+= matrix.mat[ matrix.columns * (row-1) + (col-1+i)];
            if( (col-1+i) != col ) sum+= matrix.mat[ matrix.columns * row + (col-1+i)];
            if( row+1<matrix.row) sum+= matrix.mat[ matrix.columns * (row+1) + (col-1+i)];
        }
    }
    return sum;
}

Matrix filtro_smoothing( const Matrix& matrix){ //somma adiacenti, senza elemento
    Matrix smooth_matrix = {.row = matrix.row, .columns = matrix.columns, .mat = new int[matrix.row*matrix.columns]};
    for(int i=0; i<matrix.row; i++){
        for(int j=0; j<matrix.columns; j++){
            smooth_matrix.mat[ smooth_matrix.columns * i +j] = somma_adiacenti( matrix, i, j);
        }
    }
    return smooth_matrix;
}

Matrix inverti_righe(const Matrix& matrix){
    Matrix inv_rows = {.row = matrix.row, .columns= matrix.columns, .mat = new int[matrix.row*matrix.columns]};
    for(int i=0; i<matrix.row; i++){
        for(int j=0; j<matrix.columns; j++){
            inv_rows.mat[ inv_rows.columns * (matrix.row-1-i) + j] = matrix.mat[ matrix.columns * i +j];
        }
    }
    return inv_rows;
}

Matrix inverti_colonne(const Matrix& matrix){
    Matrix inv_cols = {.row = matrix.row, .columns= matrix.columns, .mat = new int[matrix.row*matrix.columns]};
    for(int i=0; i<matrix.row; i++){
        for(int j=0; j<matrix.columns; j++){
            inv_cols.mat[ inv_cols.columns * i + (matrix.columns-1-j)] = matrix.mat[ matrix.columns * i +j];
        }
    }
    return inv_cols;
}

int somma_diagonale(const Matrix& matrix){
    if( matrix.columns == matrix.row ){
        int sum = 0;
        for(int i=0; i<matrix.row; i++){
            sum+= matrix.mat[ matrix.columns * i + i ];
        }
        return sum;
    }
    return -1; 
}

int index_max(const Matrix& matrix){ //in notazione array
    int max = matrix.mat[0];
    int index = 0;

    for(int i=0; i<matrix.columns*matrix.row; i++){
        if( max < matrix.mat[i]){
            max = matrix.mat[i];
            index = i;
        }
    }
    return index;
}

int main(){
    const int N = 9;
    int* first = new int[N];
    for(int i=0; i<N; i++){
        first[i] = i+1;
    }

    int second[9] = { 7,5,4,33,11,22,1,1,16};

    
    Matrix mat1 = init( N/3, N/3, first);
    Matrix mat2 = init( N/3, N/3, second);

    print(mat1);
    cout<<endl;
    print(mat2);
    cout<<endl;

    cout<<"Trasposte:"<<endl;
    print( trasponi(mat1));
    cout<<endl;
    print(trasponi(mat2));
    cout<<endl;

    cout<<"Somma"<<endl;
    print( somma( mat1, mat2));
    cout<<endl;

    cout<<"Determinante: "<<endl;
    cout<<"Det 1: " << determinante(mat2)<<endl;


    cout<<"Prodotto: "<<endl;
    print(mat1);
    print(mat2);
    print( matrix_product( mat1, mat2) );

    cout<<"Smooth matrix: "<<endl;
    print(filtro_smoothing(mat1));

    cout<<"Indice del max value"<<endl;
    cout<<index_max(mat1)<<endl;

    cout<<"Inverti righe: "<<endl;
    print(inverti_righe(mat1));

    cout<<"Inverti colonne: "<<endl;
    print(inverti_colonne(mat1));

    cout<<"Somma diagonale"<<endl;
    cout<< somma_diagonale(mat1) << endl;

    return 0;
}