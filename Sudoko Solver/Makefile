CXX = g++
CXX_FLAGS = -std=c++11

sudoko: classical_sudoko_solver.o
	$(CXX) $(CXX_FLAGS) -o sudoko classical_sudoko_solver.o

classical_sudoko_solver.o: classical_sudoko_solver.cpp
	$(CXX) $(CXX_FLAGS) -c classical_sudoko_solver.cpp

clean:
	rm -rf *.o sudoko