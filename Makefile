CXX=g++
MXX=mpicxx
FLAGS=-O3 -std=c++11

RM=rm -f

ORIG=orig
OMP=openmp
MPI=mpi

all: $(ORIG) $(OMP) $(MPI)

$(ORIG): $(ORIG).cpp
	$(CXX) $(FLAGS) $(ORIG).cpp -c -o $(ORIG).o
	$(CXX) $(FLAGS) $(ORIG).o -o $(ORIG)

$(OMP): $(OMP).cpp
	$(CXX) -fopenmp $(FLAGS) $(OMP).cpp -c -o $(OMP).o
	$(CXX) -fopenmp $(FLAGS) $(OMP).o -o $(OMP)

$(MPI): $(MPI).cpp 
	$(MXX) -o $(MPI) $(MPI).cpp 


clean:
	$(RM) $(ORIG).o $(ORIG)
	$(RM) $(OMP).o $(OMP)
	$(RM) $(MPI).o $(MPI)
	$(RM) Grafico.png
