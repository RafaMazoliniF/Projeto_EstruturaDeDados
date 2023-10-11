#include "estruturas.h"
#include <time.h>

void limpaTela() {
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #else
    #endif
}

void escolha1(Fila ** filas, Lista * pendentes, Lista * concluidas) {
    limpaTela();
    printf("Mostrar quais tarefas?\n[1] Todas;\n[2] Somente as ativas;\n[3] Somente as pendentes\n[4] Somente as concluidas;\n[5] Voltar;\n> ");
    
    int escolha; 
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            limpaTela();

            printf("TAREFAS ATIVAS\n");
            for (int i = 0; i < 3; i++) {
                printf("\nPriotidade %d:", i + 1);
                printaFila(filas[i]);
            }

            printf("\n\nTAREFAS PENDENTES");
            printaLista(pendentes, false);
            printf("\n\nTAREFAS CONCLUIDAS");
            printaLista(concluidas, true);
            break;
        case 2:
            limpaTela();

            printf("TAREFAS ATIVAS\n");
            for (int i = 0; i < 3; i++) {
                printf("\nPriotidade %d:", i + 1);
                printaFila(filas[i]);
            }
            break;
        case 3:
            limpaTela();

            printf("\n\nTAREFAS PENDENTES");
            printaLista(pendentes, false);
            break;
        case 4:
            limpaTela();

            printf("\n\nTAREFAS CONCLUIDAS");
            printaLista(concluidas, true);
            break;
        case 5:
        default: 
        limpaTela();
        break;
    }
}

void escolha2(Fila ** filas, int * codigo_atual, int hoje[]) {
    limpaTela();
    cadastraNovaTarefa(filas, criaTarefa(codigo_atual, hoje));
}

void escolha3(Lista ** pendentes, Lista * filas[], Lista ** concluidas, int hoje[]){
    limpaTela();

    printf("Digite o codigo da tarefa a ser aberta: ");
    limpaBuffer();
    int codigo;
    scanf("%d", &codigo);

    Tarefa * tarefa = getTarefa(codigo, *pendentes, filas);

    limpaTela();
    printaTarefa(*tarefa);

    printf("Digite um numero para escolher uma acao:\n[1] Editar;\n[2] Excluir;\n[3] Marcar como concluida;\n[4] Sair;\n> ");
    int escolha;
    limpaBuffer();
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            editaTarefa(codigo, filas, pendentes);
            limpaTela();
            printf("TAREFA ATUALIZADA");
            printaTarefa(*tarefa);
            break;
        case 2:
            deletaTarefa(codigo, pendentes, filas);
            break;
        case 3:
            free(retiraTarefa(codigo, pendentes, filas));
            insereLista(concluidas, tarefa);

            tarefa->termino.dia = hoje[0];
            tarefa->termino.mes = hoje[1];
            tarefa->termino.ano = hoje[2];
        case 4:
        default:
            break;
    }

    limpaTela();
}

int main() {
    limpaTela();

    int codigo_atual = 0;
    bool terminou = false;

    //DEFINE A DATA ATUAL
    time_t tempo_atual;
    struct tm *info_tempo;
    time(&tempo_atual);
    info_tempo = localtime(&tempo_atual);
    int hoje[3] = { info_tempo->tm_mday, info_tempo->tm_mon + 1, info_tempo->tm_year + 1900 };

    //TAREFAS PRE-EXISTENTES ----- YAMA ----- cria algumas dessas (o quanto e como voce achar necessario) nesse modelo
    Tarefa tarefa1 = {
        .codigo = codigo_atual++, //AS OUTRAS TAREFAS DEVEM TER <codigo_atual++>
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
    Fila ** filas = (Fila **) malloc(3 * sizeof(Fila));
    for (int i = 0; i < 3; i++) {
        filas[i] = criaFila(); 
    }

    //Cria lista de pendentes e concluídas
    Lista * pendentes = criaLista();
    Lista * concluidas = criaLista();  

    cadastraNovaTarefa(filas, &tarefa1);

    //INICIO DO PROGRAMA
    printf("===== GERENCIADOR DE TAREFAS =====\n");
    while (!terminou) {
        printf("\nDigite um numero para escolher uma acao:\n[1] Mostrar as tarefas existentes; \n[2] Adicionar uma nova tarefa;\n[3] Abrir uma tarefa; \n[4] Fechar;\n> ");
        
        int escolha; 
        
        scanf("%d", &escolha);
        
        switch (escolha){
            case 1:
                escolha1(filas, pendentes, concluidas);
                break;
            case 2:
                escolha2(filas, &codigo_atual, hoje);
                break;
            case 3:
                escolha3(&pendentes, filas, &concluidas, hoje);
                break;
            case 4: 
                terminou = true;
                break;
            default: 
                limpaTela();
                printf("Escolha invalida.\n");
                break;
        }
    }


    printf("\n");
    return 0;
}




