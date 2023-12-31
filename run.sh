#!/bin/bash

# Função para executar um programa e registrar a saída no arquivo results.csv
execute_program() {
    local program_name=$1
    local input_file=$2
    local output_file=$3

    echo "=== Executando $program_name ==="
    output=$(./$program_name < $input_file)
    echo "$program_name;$output" >> $output_file
}

execute_mpi_program() {
    local program_name=$1  # Adicione essa linha para receber o nome do programa MPI
    local input_file=$2
    local output_file=$3

    echo "=== Executando MPI ==="
    output=$(mpiexec -n 2 ./$program_name < $input_file) 
    echo "$program_name;$output" >> $output_file
}

# Cria o arquivo results.csv e escreve o cabeçalho
echo "Arquivo;Tempo(ms)" > results.csv

# Loop para diferentes valores de X
for ((X = 1; X <= 3; X += 1)); do
    echo "===== Execuções para X=$X ====="
    # Execução dos códigos com a entrada.in
    execute_program "orig" "entrada.in" "results.csv"
    execute_program "openmp" "entrada.in" "results.csv"
    execute_mpi_program "mpi" "entrada.in" "results.csv"
    echo "=============================="
done

python grafico.py


