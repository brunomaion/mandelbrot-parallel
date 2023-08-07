#include <complex>
#include <iostream>
#include <fstream>
#include <omp.h>
#include <chrono> 

using namespace std;

int main(){

 	auto start = chrono::steady_clock::now();

	int max_row, max_column, max_n;
	cin >> max_row;         // Lê o número máximo de linhas da matriz
	cin >> max_column;      // Lê o número máximo de colunas da matriz
	cin >> max_n;           // Lê o valor máximo de iterações (número máximo de iterações para cada ponto)

	char **mat = (char**)malloc(sizeof(char*)*max_row);   // Aloca dinamicamente um vetor de ponteiros para armazenar as linhas da matriz

	for (int i=0; i<max_row;i++)
		mat[i]=(char*)malloc(sizeof(char)*max_column);   // Aloca dinamicamente cada linha da matriz

	#pragma omp parallel for
	for(int r = 0; r < max_row; ++r){
		
		//#pragma omp parallel for
		for(int c = 0; c < max_column; ++c){
			complex<float> z;    // Cria um número complexo inicializado em (0,0)
			int n = 0;           // Inicializa o contador de iterações

			// Realiza o loop enquanto a magnitude do número complexo z for menor que 2
			// e o número de iterações for menor que o valor máximo permitido (max_n)
			while(abs(z) < 2 && ++n < max_n)
				z = pow(z, 2) + decltype(z)(
					(float)c * 2 / max_column - 1.5,   // Parte real do ponto mapeado para o intervalo [-1.5, 0.5]
					(float)r * 2 / max_row - 1        // Parte imaginária do ponto mapeado para o intervalo [-1, 1]
				);

			// Atribui ao elemento da matriz (r, c) o caractere '#' se o loop completou todas as iterações, caso contrário, '.'
			mat[r][c] = (n == max_n ? '#' : '.');
		}
	}

    ofstream output_file("openmp.txt"); // Cria um arquivo de saída chamado "original.txt"


		for (int r = 0; r < max_row; ++r) {
        for (int c = 0; c < max_column; ++c)
            output_file << mat[r][c]; // Escreve o elemento da matriz (r, c) no arquivo de saída
        
				
			output_file << '\n'; // Escreve uma quebra de linha para separar as linhas da matriz no arquivo de saída
    }

    output_file.close();


    auto end = chrono::steady_clock::now();
    cout<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
        << "\n";

}