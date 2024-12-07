#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>
#include <cstdio>

using namespace std;

const int LIN = 5;
const int COL = 5;


struct Cartela{
	int number[LIN][COL];
	bool marked;
};

//Gera cartela
Cartela gerarCart(){
	Cartela cart = {};
	//Usado para mostrar o menor e o maior valor dentro de cada letra no bingo.
	int limite[COL][2] = {{1, 15}, {16, 30}, {31, 45}, {46, 60}, {61, 75}};
	
	for(int col = 0; col < COL; ++col){
		bool usados[76] = {};//Array usado para rastrear números ja usados nesta coluna
		for(int lin = 0; lin < LIN; ++lin){
			if(col == 2 && lin == 2){//FREE
				cart.number[lin][col] = -1;//Marcação unica
				cart.marked = true;// Espaço marcado automaticamente
			}else{
				int num;
				do{
					num = rand() % (limite[col][1] - limite[col][0] + 1) + limite[col][0];//Criação do numero randomico
				}while (usados[num]);//Gera ate achar numeros unicos
				usados[num] = true;// Marca o numero como esta na coluna
				cart.number[lin][col] = num;//Atribui o numero no devido espaço
			}
		}
	}
	
	return cart;//Retorna a cartela criada
}

void mostrarCart(Cartela &cart){
	cout << "B  I  N  G  O" << endl;
	for(int lin = 0; lin < LIN; ++lin){
		for(int col = 0; col < COL; ++col){
			if(cart.number[lin][col] == -1){
				cout << " * ";
			}else {
				cout << cart.number[lin][col] << " ";
			}
		}
		cout << endl;
	}
}

// Salva a cartela em um arquivo
void salvarCart(Cartela &cart, char *nomeArq){
	FILE *arquivo = fopen(nomeArq, "w");
	
    if (arquivo) {
        for (int lin = 0; lin < LIN; ++lin) {
            for (int col = 0; col < COL; ++col) {
                fprintf(arquivo, "%d ", cart.number[lin][col]);
            }
            fprintf(arquivo, "\n");
        }
        fclose(arquivo);
    } else {
        cout << "Erro ao salvar a cartela no arquivo " << nomeArq << endl;
    }
}


Cartela carregarCart(char *nomeArq) {
    Cartela cart = {};
    FILE *arquivo = fopen(nomeArq, "r");
    if (arquivo) {
        for (int lin = 0; lin < LIN; ++lin) {
            for (int col = 0; col < COL; ++col) {
                fscanf(arquivo, "%d", &cart.number[lin][col]);  // Lê os números da cartela
                cart.marked = (cart.number[lin][col] == -1);  // Marca a posição "FREE"
            }
        }
        fclose(arquivo);
    } else {
        cout << "Erro ao carregar a cartela do arquivo " << nomeArq << endl;
    }
    
    return cart;
}

//Marca numero na cartela
bool marcarNum(Cartela &cart, int numero){
	bool encontrado = false;
	for (int lin = 0; lin < LIN ; ++lin){
		for (int col = 0; col < COL ; ++col){
			if(cart.number[lin][col] == numero){
				cart.marked = true;//marca o booleano na cartela
				encontrado = true; //Numero encontrado e marcado
			}else {
				cout << "numero nao encontrado!" << endl;
			}
		}
	}
	
	return encontrado;
}



int main(int argc, char** argv) {
	srand(time(0));
	int op, numCart, escolha;
	char nomeArq[50];
	
	cout << "Ola, Bem vindo ao Sistema de Bingo! Escolha uma opcao" << endl << endl;
	
	do{
		cout << "|----------------------------|" << endl;
		cout << "| 1 - Cadastrar Cartela      |" << endl;
		cout << "| 2 - Cadastrar numeros      |" << endl;
		cout << "| 3 - Ver Cartelas           |" << endl;
		cout << "| 4 - Sair                   |" << endl;
		cout << "|----------------------------|" << endl;
		cin >> op;
		
		switch(op){
			case 1:
				cout << "Quantas Cartelas voce deseja registrar" << endl;
				cin >> numCart;
				
				for (int i = 0; i < numCart; i++) {
        			Cartela cart = gerarCart();
        			sprintf(nomeArq, "cartela_%d.txt", i + 1);
        			salvarCart(cart, nomeArq);
        			cout << "Cartela " << i + 1 << " salva em " << nomeArq << endl;
					}
				break;
				
			case 2:
				cout << "Quais numeros voce deseja colocar?" << endl;
				cin >> escolha;
				
				for (int i = 0; i < numCart; i++) {
                    sprintf(nomeArq, "cartela_%d.txt", i + 1);
                    Cartela cart = carregarCart(nomeArq);
                    if (marcarNum(cart, escolha)) {
                        cout << "Numero " << escolha << " encontrado e marcado na Cartela " << i + 1 << "!\n";
                        salvarCart(cart, nomeArq);
                    }
                }
				break;
			
			case 3:
				for (int i = 0; i < numCart; ++i) {
                    sprintf(nomeArq, "cartela_%d.txt", i + 1);
                    Cartela cart = carregarCart(nomeArq);
                    cout << "\nCartela " << i + 1 << ":\n";
                    mostrarCart(cart);
                }
				break;
				
			case 4:
				cout  << "Obrigado por usar o sistema!!" << endl;
				cout  << "Ate a proxima!";
				break;
			
			default:
				cout  << "Escolha uma opcao valida!!!" << endl;
		}
		
		
	}while(op != 4);
	
	
	return 0;
}
