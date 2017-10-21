model_c++ : model_c++.cpp input.cpp
	g++ -Wall -o "model_c++" *.cpp -I/Library/gurobi751/mac64/include/ -L/Library/gurobi751/mac64/lib/ -lgurobi_c++ -lgurobi75 -lm
input.o : input.cpp input.h
	g++ -c input.cpp
clean:
	rm model_c++
