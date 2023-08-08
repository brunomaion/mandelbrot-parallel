#include <complex>
#include <iostream>
#include <fstream>
#include <chrono> 
#include <stdio.h>
#include <mpi.h>
#include <omp.h>

using namespace std;

int main (int argc, char * argv [])
{ 

 	auto start = chrono::steady_clock::now();

  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

	int max_row, max_column, max_n;
	cin >> max_row;         // Lê o número máximo de linhas da matriz
	cin >> max_column;      // Lê o número máximo de colunas da matriz
	cin >> max_n;           // Lê o valor máximo de iterações (número máximo de iterações para cada ponto)

	char **mat = (char**)malloc(sizeof(char*)*max_row);  
	for (int i=0; i<max_row;i++)
		mat[i]=(char*)malloc(sizeof(char)*max_column);   


	/* Cada processo rank pega as linhas onde o índice é igual a rank, 
	e então salta size linhas a cada iteração subsequente
	*/

	for (int r = rank; r < max_row; r += size) {
			for (int c = 0; c < max_column; ++c) {
					complex<float> z;
					int n = 0;

					while (abs(z) < 2 && ++n < max_n)
							z = pow(z, 2) + decltype(z)(
									(float)c * 2 / max_column - 1.5,
									(float)r * 2 / max_row - 1
							);

					mat[r][c] = (n == max_n ? '#' : '.');
			}
	}
    
		MPI_Finalize();

    ofstream output_file("mpi.txt"); 
		for (int r = 0; r < max_row; ++r) {
        for (int c = 0; c < max_column; ++c)
            output_file << mat[r][c]; 
				
			output_file << '\n';  }

    output_file.close();

    auto end = chrono::steady_clock::now();
    cout<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
        << "\n";


}


