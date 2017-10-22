/* Copyright 2017, Gurobi Optimization, Inc. */

/* This example formulates and solves the following simple MIP model:

     maximize    x +   y + 2 z
     subject to  x + 2 y + 3 z <= 4
                 x +   y       >= 1
     x, y, z binary
*/

#include "gurobi_c++.h"
#include "input.h"
#include <iostream>
using namespace std;

int
main(int   argc,
     char *argv[])
{
	// Arquivo para armazenar dados de entrada
	input entrada;
	
	// Manipulador do arquivo de entrada
    ifstream file_(argv[1],ios::in);

	// Leitura dos dados de entrada
    entrada.load(file_);
	
  try {
    GRBEnv env = GRBEnv();

    GRBModel model = GRBModel(env);

	// Decision variables
	GRBVar *x = new GRBVar[entrada.dimention_];
	cout<<entrada.dimention_<<endl;
    for (int i = 0; i < entrada.dimention_; i++){
		string varName = "xf" + std::to_string (i);
		x[i] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, varName);
	}
	
	// Hierarchical constraints
	for (int i = 0; i < entrada.dimention_; i++){
		for (int j = i+1; j < entrada.dimention_; j++){
			if(entrada.H[i][j] == 1){
				string constraintName = "x[" + to_string (j)+"]<=x["+ to_string (j)+"]";
				model.addConstr(x[j] <= x[i], constraintName);
			}
		}
	}
	
	// Mandadoty constraints
	for (int i = 0; i < entrada.dimention_; i++){
		for (int j = i+1; j < entrada.dimention_; j++){
			if(entrada.M[i][j] == 1){
				string constraintName = "x[" + to_string (j)+"]==x["+ to_string (j)+"]";
				model.addConstr(x[j] == x[i], constraintName);
			}
		}
	}
	
    model.setObjective(1.3*x[2] - 0.42*x[4] + 0*x[8]+ 1.53*x[9] + 0.93*x[10] 
    + 0*x[11] + 1.34*x[13] + 0.01*x[14] -0.16*x[15]+1.93*x[16]+0.6*x[17], GRB_MAXIMIZE);

	
	// OR constraints
	// At least one feature must be activated, if the father is activated
	model.addConstr(x[16] + x[17] >= x[15], "c23");
	model.addConstr( x[9] + x[10] >= x[8], "c24");
	
	// Alternative constraints 
	model.addConstr(x[13] + x[14] == x[12], "c25");

    // Require constraints
    model.addConstr( x[2] <= x[4], "c26");

    // Optimize model

    model.optimize();

	for (int i = 0; i < entrada.dimention_; i++){
		cout << x[i].get(GRB_StringAttr_VarName) << " "
         << x[i].get(GRB_DoubleAttr_X) << endl;
	}

    cout << "Obj: " << model.get(GRB_DoubleAttr_ObjVal) << endl;
    

  } catch(GRBException e) {
    cout << "Error code = " << e.getErrorCode() << endl;
    cout << e.getMessage() << endl;
  } catch(...) {
    cout << "Exception during optimization" << endl;
  }
  return 0;
}
