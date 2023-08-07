#include <complex>
#include <iostream>
#include <fstream>
#include <mpi.h>
#include <chrono> 

using namespace std;

int main(int argc, char** argv){

    MPI_Init(&argc, &argv);

    auto start = chrono::steady_clock::now();

    int max_row, max_column, max_n;
    cin >> max_row;
    cin >> max_column;
    cin >> max_n;

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rows_per_process = max_row / size;
    int remaining_rows = max_row % size;

    int start_row = rank * rows_per_process;
    int end_row = start_row + rows_per_process;
    if (rank == size - 1) {
        end_row += remaining_rows;
    }

    char **mat = (char**)malloc(sizeof(char*) * (end_row - start_row));

    for (int i = 0; i < end_row - start_row; i++)
        mat[i] = (char*)malloc(sizeof(char) * max_column);

    for (int r = start_row; r < end_row; ++r) {
        for (int c = 0; c < max_column; ++c) {
            complex<float> z;
            int n = 0;
            while (abs(z) < 2 && ++n < max_n)
                z = pow(z, 2) + decltype(z)(
                    (float)c * 2 / max_column - 1.5,
                    (float)r * 2 / max_row - 1
                );
            mat[r - start_row][c] = (n == max_n ? '#' : '.');
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0) {
        ofstream output_file("mpi.txt");
        for (int i = 0; i < end_row - start_row; ++i) {
            for (int c = 0; c < max_column; ++c)
                output_file << mat[i][c];
            output_file << '\n';
        }
        output_file.close();

        auto end = chrono::steady_clock::now();
        cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "\n";
    }

    MPI_Finalize();
}
