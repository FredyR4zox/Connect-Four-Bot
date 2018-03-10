#include <limits>
using namespace std;

void Minimax_Decision(Board *current) {


}

int MM_Max(Board *current) {
/*PSEUDO-CÓDIGO*/
	if (victory(current)) //se o tabuleiro atual conter a vitória
		return utilty(current); //retornar vitória
int v = numeric_limits::min(); //inicializa v ao minimo possivel (- inf.)
lista = current->makeDescendents();	 //cria uma lista onde vai por os possiveis movimentos a partir do atual
	while (!lista.empty()) { // enquanto a lista nao estiver vazia
		avalia = lista.peek(); //remove o da frente
		lista.pop();
		v = max(v, MM_Min(avalia)); //o valor a retornar sera o máximo entre o v e o min do avalia
	}
	return v;
}

int MM_Min(Board *current) {

}