#include "estruturas.h"

int main() {
    //Cria as filas de tarefas por prioridade
    Fila * filas[3];
    for (int i = 0; i < 3; i++) {
        filas[i] = criaFila(); 
    }

    //Cria lista de pendentes
    Lista * pendentes = criaLista();

    return 0;
}