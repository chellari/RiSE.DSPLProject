/*
 *  Created on: Oct 21, 2017
 *      Author: Michelle Larissa
 * 				Tiago Januario
 */

#include "input.h"
#include <iomanip>
#include <cmath>

using namespace std;

input::input() {
	
	comment_ = "no comment";
	type_ = "no type";
	dimention_ = 0;
}

//funcao de conversao de string para int
int input::convert(string s){
    //declaracao de um conversor do tipo stringstream
    stringstream conversor_(s);

    //inteiro auxiliar
    int inteiro_;

    //associacao da string dando um parse para int
    conversor_ >> inteiro_;

    return inteiro_;
}

// Faz a leitura do arquivo de entrada e armazena as informacoes necessarias
void input::load(ifstream& inputFile) {

    //string auxiliar para entrada
	string s;

	if (inputFile.is_open()) {
            
            //NAME
            getline(inputFile,s,' ');
            //Se a entrada nao estiver com o ":" junto ao tipo (ex: NAME:, EDGE_WEIGHT_TYPE_:)
            if(s[s.size()-1] != ':')
                getline(inputFile,s,' ');
            //le a informacao sobre os tipos ate o fim de linha
            getline(inputFile,s);

            //Associacao da string auxiliar s ao nome
            name_ = s;
            
            cout<<"NAME : "<<name_<<endl;
            //COMMENT
            getline(inputFile,s,' ');

            if(s[s.size()-1] != ':')
                getline(inputFile,s,' ');

            getline(inputFile,s);

            //Associacao da string auxiliar s ao comentário
            comment_ = s;
            cout<<"COMMENT : "<<s<<endl;

            //TYPE
            getline(inputFile,s,' ');

            if(s[s.size()-1] != ':')
                getline(inputFile,s,' ');

            getline(inputFile,s);

            //Associacao da string auxiliar s ao tipo
            type_ = s;
            cout<<"TYPE : "<<s<<endl;

            //DIMENSION
            getline(inputFile,s,' ');

            if(s[s.size()-1] != ':')
                getline(inputFile,s,' ');

            getline(inputFile,s);
            dimention_ = convert(s);
            cout<<"DIMENSION : "<<s<<endl;


			H.resize(dimention_, vector<int> (dimention_));
			M.resize(dimention_, vector<int> (dimention_));

            //FEATURE_MODEL_SECTION
            getline(inputFile,s,' ');
			if(s[s.size()-1] != ':')
                getline(inputFile,s,' ');
			getline(inputFile,s);
			H_size = convert(s);
			cout<<"FEATURE_MODEL_SECTION : "<<H_size<<endl;
			

			int id,x,y;
			for (int i = 0; i < H_size; i++) {
				inputFile >> id >> x >> y;
				cout << id <<" "<<x<<" "<<y<<endl;
				H[x][y] = 1;
					
			}

			//MANDATORY_SECTION
            getline(inputFile,s,' ');
			if(s[s.size()-1] != ':')
                getline(inputFile,s,' ');
			getline(inputFile,s);
			M_size = convert(s);
			cout<<"MANDATORY_SECTION : "<<M_size<<endl;
			
			for (int i = 0; i < M_size; i++) {
				inputFile >> id >> x >> y;
				cout << id <<" "<<x<<" "<<y<<endl;
				M[x][y] = 1;	
			}


            //EOF
            getline(inputFile,s);

        //fim do arquivo
		inputFile.close();
		}
        //se nao houver sucesso ao abrir o arquivo
        else {
            cout << "Impossivel abrir o arquivo" << endl;
            exit(1);
        }
}
