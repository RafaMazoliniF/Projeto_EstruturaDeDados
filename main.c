#include "estruturas.h"
#include <time.h>

Tarefa * criaTarefa(int * codigo_atual, int hoje[]);
void cadastraNovaTarefa(Fila * filas[], Lista ** pendentes, Tarefa * tarefa);
Tarefa * getTarefa(int codigo, Lista * pendentes, Fila * filas[]);
void editaTarefa(int codigo, Fila * filas[], Lista * pendentes);

int main() {
    int codigo_atual = 0;

    //DEFINE A DATA ATUAL
    time_t tempo_atual;
    struct tm *info_tempo;
    time(&tempo_atual);
    info_tempo = localtime(&tempo_atual);
    int hoje[3] = { info_tempo->tm_mday, info_tempo->tm_mon + 1, info_tempo->tm_year + 1900 };

    //TAREFAS PRE-EXISTENTES ----- YAMA ----- cria algumas dessas (o quanto e como voce achar necessario) nesse modelo
    Tarefa tarefa1 = {
        .codigo = codigo_atual, //AS OUTRAS TAREFAS DEVEM TER <codigo_atual++>
        .nome = "Terminar o projeto",
        .projeto = "Gerenciamento",
        .inicio.dia = 20,
        .inicio.mes = 9,
        .inicio.ano = 2023,
        .termino.dia = 10,
        .termino.mes = 10,
        .termino.ano = 2023,
        .status = 0,
        .prioridade = 1
    };

    //Cria as filas de tarefas por prioridade
    Fila * filas[3];
    for (int i = 0; i < 3; i++) {
        filas[i] = criaFila(); 
    }

    //Cria lista de pendentes e concluídas
    Lista * pendentes = criaLista();
    Lista * concluidas = criaLista();  

    cadastraNovaTarefa(filas, &pendentes, criaTarefa(&codigo_atual, hoje));
    cadastraNovaTarefa(filas, &pendentes, criaTarefa(&codigo_atual, hoje));
    cadastraNovaTarefa(filas, &pendentes, criaTarefa(&codigo_atual, hoje));


    return 0;
}


Tarefa * criaTarefa(int * codigo_atual, int hoje[]) {
    
    Tarefa * nova_tarefa = (Tarefa *) malloc(sizeof(Tarefa));

    printaDiv();
    printf("AREA DE CRIACAO DE TAREFA\n\n");

    //NOME
    printf("Digite o nome da tarefa: ");
    fflush(stdin);
    fgets(nova_tarefa->nome, 30, stdin);
    int nome_i = 0;
    while (nova_tarefa->nome[nome_i] != '\n') nome_i++;
    nova_tarefa->nome[nome_i] = '\0';

    //PROJETO
    printf("\nDigite o nome do projeto: ");
    fflush(stdin);
    fgets(nova_tarefa->projeto, 30, stdin);
    int projeto_i = 0;
    while (nova_tarefa->projeto[projeto_i] != '\n') projeto_i++;
    nova_tarefa->projeto[projeto_i] = '\0';

    //DATA INICIO
    printf("\nData de início: %d/%d/%d", hoje[0], hoje[1], hoje[2]);
    nova_tarefa->inicio.dia = hoje[0];
    nova_tarefa->inicio.mes = hoje[1];
    nova_tarefa->inicio.ano = hoje[2];

    //DATA TERMINO
    printf("\nDigite a data de termino:");
    printf("\nDia: "); fflush(stdin); scanf("%d", &nova_tarefa->termino.dia);
    printf("Mes: "); fflush(stdin); scanf("%d", &nova_tarefa->termino.mes);
    printf("Ano: "); fflush(stdin); scanf("%d", &nova_tarefa->termino.ano);

    //STATUS
    printf("\nDigite o status da tarefa ([1] => atrasada; [0] => em dia; [-1] => pendente)\n> "); 
    fflush(stdin); 
    scanf("%d", &nova_tarefa->status);

    //PRIORIDADE
    printf("\nDigite a prioridade da tarefa ([1] => Alta; [2] => Media; [3] => Baixa)\n> ");
    fflush(stdin);
    scanf("%d", &nova_tarefa->prioridade);
    getchar();

    //CODIGO
    nova_tarefa->codigo = *codigo_atual;
    printf("\nO codigo da tarefa eh: %d", *codigo_atual);
    printaDiv();

    (*codigo_atual)++;

    return nova_tarefa;
}

//Recebe uma tarefa e insere em uma das filas ou na lista de pendentes
void cadastraNovaTarefa(Fila * filas[], Lista ** pendentes, Tarefa * tarefa) {
    if (tarefa->status == -1) {
        insereLista(pendentes, tarefa);
    }

    else {
        insereFila(filas[tarefa->prioridade - 1], tarefa);
    }
}

//retorna a tarefa com o código passado
Tarefa * getTarefa(int codigo, Lista * pendentes, Fila * filas[]) {
    while (pendentes != NULL) {
        if (pendentes->tarefa->codigo == codigo) return pendentes->tarefa;
        pendentes = pendentes->proximo_no;
    }

    for (int i = 0; i < 3; i++) {
        No * no_atual = filas[i]->inicio;
        while (no_atual != NULL) {
            if (no_atual->tarefa->codigo == codigo) return no_atual->tarefa;
            no_atual = no_atual->proximo_no;
        }
    }

    return NULL; // Default
}

//Recebe o codigo de uma tarefa e altera as suas informacoes
void editaTarefa(int codigo, Fila * filas[], Lista * pendentes) {
    Tarefa * tarefa = getTarefa(codigo, pendentes, filas);
    
    printaDiv();
    printf("AREA DE EDICAO DE TAREFA\n\n");

    printf("Para editar, digite:\n[0] Nome\n[1] Projeto;\n[2] Data de inicio;\n[3] Data de termino;\n[4] Status;\n[5] Prioridade;\n> ");
    int escolha;
    fflush(stdin);
    scanf("%d", &escolha);

    switch (escolha) {
        case 0:
            printf("\n Novo nome: ");
            fflush(stdin);
            fgets(tarefa->nome, 30, stdin);
            break;
        case 1:
            printf("\n Novo projeto: ");
            fflush(stdin);
            fgets(tarefa->nome, 30, stdin);
            break;
        case 2:
            printf("Nova data de inicio:");
            printf("\nDia: "); fflush(stdin); scanf("%d", &tarefa->inicio.dia);
            printf("Mes: "); fflush(stdin); scanf("%d", &tarefa->inicio.mes);
            printf("Ano: "); fflush(stdin); scanf("%d", &tarefa->inicio.ano);
            break;
        case 3:
            printf("Nova data de termino:");
            printf("\nDia: "); fflush(stdin); scanf("%d", &tarefa->inicio.dia);
            printf("Mes: "); fflush(stdin); scanf("%d", &tarefa->inicio.mes);
            printf("Ano: "); fflush(stdin); scanf("%d", &tarefa->inicio.ano);
            break;
        case 4:
            printf("Novo status: ");
            fflush(stdin);
            scanf("%d", &tarefa->status);
            break;
        case 5:
            printf("Nova prioridade: ");
            fflush(stdin);
            scanf("%d", &tarefa->prioridade);
            break;
        default: 
            printf("Escolha invalida");
    }

    printaDiv();
}
