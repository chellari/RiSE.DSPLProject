/*
 *  Created on: Oct 21, 2017
 *      Author: Michelle Larissa
 * 				Tiago Januario
 */

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <dirent.h>

using namespace std;

 #ifndef VRP_INPUT_H
 #define VRP_INPUT_H

class input {

//	// Sobrecarga de operador
	friend ostream& operator<<(ostream&, const input &in);

public:

	// Constructor padrao
	input();

	// Constructor com instância como parâmetro
	input(ifstream& file_name){
		load(file_name);
	}
	
	// Leitura e armazenamento dos dados de entrada
	void load(ifstream& file_name);


	//nome do modelo
	string name_;
	
	//comentário do modelo
	string comment_;
	
	// Type of SPL model 
	string type_;
	
	// Number of features
	int dimention_;
	
	// Hierarchical relations
	vector< vector<int> > H;
	
	// # of hierarchical relations
	int H_size;
	
	// Mandadoty relation
	vector< vector<int> > M;
	int M_size;

	int convert(string s);

};

#endif  // VRP
