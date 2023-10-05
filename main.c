#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

struct Data {
    int dia;
    int mes;
    int ano;
};

struct Task {
    int codigo;
    char nome[30];
    char projeto[30];
    struct Data DataInicio;
    struct Data DataFinal;
    struct Data DataTerminoInicial;
    int prioridade;
    int status;
};

struct CompletedTask {
    int codigo;
    char nome[30];
    char projeto[30];
    struct Data DataInicio;
    struct Data DataFinal;
    struct Data DataTerminoInicial;
    int prioridade;
    int status;
};

struct Data Time() {
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    struct Data currentDate;
    currentDate.dia = tm.tm_mday;
    currentDate.mes = tm.tm_mon + 1;
    currentDate.ano = tm.tm_year + 1900;

    return currentDate;
}

int ComparaCodigoTarefa(struct Task tasks[], int taskCount, int code) {
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].codigo == code) {
            return 1; // Código de tarefa duplicado encontrado
        }
    }
    return 0; // Código de tarefa único
}

int verificaData(struct Task newTask) {
    if(newTask.DataInicio.mes == 1 || newTask.DataInicio.mes == 3 || newTask.DataInicio.mes == 5 || newTask.DataInicio.mes == 7 || newTask.DataInicio.mes == 8 || newTask.DataInicio.mes == 10 || newTask.DataInicio.mes == 12){
        if(newTask.DataInicio.dia > 31){
            return 1;
        }else{
            return 0;
        }
    }
    else if(newTask.DataInicio.mes == 4 || newTask.DataInicio.mes == 6 || newTask.DataInicio.mes == 9 || newTask.DataInicio.mes == 11){
        if(newTask.DataInicio.dia > 30){
            return 1;
        }else{
            return 0;
        }
    }
    else if(newTask.DataInicio.mes == 2){
        if(newTask.DataInicio.dia > 29){
            return 1;
        }else {
            return 0;
        }
    }else {
        return 0;
    }

    if(newTask.DataFinal.mes == 1 || newTask.DataFinal.mes == 3 || newTask.DataFinal.mes == 5 || newTask.DataFinal.mes == 7 || newTask.DataFinal.mes == 8 || newTask.DataFinal.mes == 10 || newTask.DataFinal.mes == 12){
        if(newTask.DataFinal.dia > 31){
            return 1;
        }else{
            return 0;
        }
    }
    else if(newTask.DataFinal.mes == 4 || newTask.DataFinal.mes == 6 || newTask.DataFinal.mes == 9 || newTask.DataFinal.mes == 11){
        if(newTask.DataFinal.dia > 30){
            return 1;
        }else {
            return 0;
        }
    }
    else if(newTask.DataFinal.mes == 2){
        if(newTask.DataFinal.dia > 29){
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}

int isNumeroValido() {
    int num;
    char newline;
    while (1) {
        if (scanf("%d%c", &num, &newline) == 2 && newline == '\n') {
            return num;
        } else {
            printf("ERRO: Digite um numero valido: ");
            while (getchar() != '\n');  // Limpa o buffer de entrada
        }
    }
}


void addTask(struct Task tasks[], int *taskCount, struct CompletedTask completedTasks[], int *completedTaskCount) {
    struct Task newTask;
    if (*taskCount < 100) {
        printf("Digite o codigo da tarefa: ");
        newTask.codigo = isNumeroValido();

        if (ComparaCodigoTarefa(tasks, *taskCount, newTask.codigo)) {
            printf("ERRO: codigo da tarefa ja atribuido.\n");
            return;
        }

        printf("Digite o nome da tarefa (ate 30 caracteres): ");
        scanf(" %[^\n]", newTask.nome);
        printf("Digite o nome do projeto (ate 30 caracteres): ");
        scanf(" %[^\n]", newTask.projeto);
        printf("Digite a data de inicio (dia mes ano (Exemplo: 12 12 2023)): ");
        scanf("%d %d %d", &newTask.DataInicio.dia, &newTask.DataInicio.mes, &newTask.DataInicio.ano);

        if(verificaData(newTask)) {
            printf("\nData de inicio invalida.\n");
            while (getchar() != '\n');  // Limpa o buffer de entrada
            return;
        }

        printf("Digite a data de termino (dia mes ano (Exemplo: 12 12 2023)): ");
        scanf("%d %d %d", &newTask.DataFinal.dia, &newTask.DataFinal.mes, &newTask.DataFinal.ano);

        newTask.DataTerminoInicial.dia = newTask.DataFinal.dia;
        newTask.DataTerminoInicial.mes = newTask.DataFinal.mes;
        newTask.DataTerminoInicial.ano = newTask.DataFinal.ano;

        if(newTask.DataFinal.ano >= newTask.DataInicio.ano){
            if(newTask.DataFinal.mes >= newTask.DataInicio.mes){
                if(newTask.DataFinal.dia < newTask.DataInicio.dia){
                    printf("\nERRO: data de termino anterior a data de inicio.\n");
                    return;
                }
            }else{
                printf("\nERRO: data de termino anterior a data de inicio.\n");
                return;
            }
        }else{
            printf("\nERRO: data de termino anterior a data de inicio.\n");
            return;
        }


        if(verificaData(newTask)) {
            printf("\nData de termino invalida.\n");
            while (getchar() != '\n');  // Limpa o buffer de entrada
            return;
        }

        printf("Digite o nivel de prioridade (de 1 a 3): ");
        scanf("%d", &newTask.prioridade);

        if(newTask.prioridade < 1 || newTask.prioridade > 3){
            printf("Erro: digite uma prioridade valida");
            return;
        }

        newTask.status = -1;
        tasks[*taskCount] = newTask;
        (*taskCount)++;
        printf("\nTarefa adicionada com sucesso!\n\n");
        saveTasksToFile(tasks, *taskCount, completedTasks, *completedTaskCount);
    } else {
        printf("A fila de tarefas esta cheia. Nao e possivel adicionar mais tarefas.\n");
    }
}


int compareDates(struct Data date1, struct Data date2) { //date1 = pc, date2 = lida
    // Comparar anos
    if (date1.ano < date2.ano) {
        return -1;
    } else if (date1.ano > date2.ano) {
        return 1;
    } else {
        // Se os anos são iguais, comparar meses
        if (date1.mes < date2.mes) {
            return -1;
        } else if (date1.mes > date2.mes) {
            return 1;
        } else {
            // Se os meses são iguais, comparar dias
            if (date1.dia < date2.dia) {
                return -1;
            } else if (date1.dia > date2.dia) {
                return 1;
            } else {
                // As datas são iguais
                return 0;
            }
        }
    }
}


void listPendingTasks(struct Task tasks[], int taskCount, int desiredPriority) {
    // Determinar o tamanho máximo para cada coluna
    int maxCodeLength = 0;
    int maxNameLength = 0;
    int maxProjectLength = 0;
    int maxPriorityLength = 0;
    struct Data currentDate = Time();
    int i;

    // Ordenar as tarefas pendentes com base na data de término (atrasadas primeiro)
    for (int i = 0; i < taskCount - 1; i++) {
        for (int j = 0; j < taskCount - i - 1; j++) {
            if (tasks[j].status == -1 && tasks[j + 1].status == -1) {
                if (compareDates(tasks[j].DataFinal, tasks[j + 1].DataFinal) == 1) {
                    // Trocar as posições das tarefas
                    struct Task temp = tasks[j];
                    tasks[j] = tasks[j + 1];
                    tasks[j + 1] = temp;
                }
            }
        }
    }

    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].status == -1 && tasks[i].prioridade == desiredPriority) {
            int codeLength = snprintf(NULL, 0, "%d", tasks[i].codigo);
            if (codeLength > maxCodeLength) {
                maxCodeLength = codeLength;
            }

            int nameLength = strlen(tasks[i].nome);
            if (nameLength > maxNameLength) {
                maxNameLength = nameLength;
            }

            int projectLength = strlen(tasks[i].projeto);
            if (projectLength > maxProjectLength) {
                maxProjectLength = projectLength;
            }

            int priorityLength = snprintf(NULL, 0, "%d", tasks[i].prioridade);
            if (priorityLength > maxPriorityLength) {
                maxPriorityLength = priorityLength;
            }
        }
    }

    for(int i =0; i < taskCount; i++){
        if(tasks[i].prioridade == desiredPriority && taskCount > 0){
            // Imprimir a tabela com base nos tamanhos máximos calculados
            printf("\n\n --------------------------------------------------------------\n");
            printf("| Tarefas Pendentes (Prioridade %d):                            |\n", desiredPriority);
            printf("|                                                               |\n");
        } else if(tasks[i].prioridade == desiredPriority && taskCount == 0){
            printf("\n\nNenhuma tarefa pendente referente a essa prioridade.\n");
        } else{
            printf("\n\nNenhuma tarefa pendente referente a essa prioridade.\n");
        }
    }

    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].status == -1 && tasks[i].prioridade == desiredPriority) {
            printf("| Codigo: %-*d                                                  |\n", maxCodeLength, tasks[i].codigo);
            printf("| Nome: %-*s                                                      |\n", maxNameLength, tasks[i].nome);
            printf("| Projeto: %-*s                                                   |\n", maxProjectLength, tasks[i].projeto);
            printf("| Data de Inicio: %02d/%02d/%04d                                    |\n", tasks[i].DataInicio.dia, tasks[i].DataInicio.mes, tasks[i].DataInicio.ano);
            printf("| Data de Termino: %02d/%02d/%04d                                   |\n", tasks[i].DataTerminoInicial.dia, tasks[i].DataTerminoInicial.mes, tasks[i].DataTerminoInicial.ano);
            printf("| Nivel de prioridade: %-*d                                           |\n", maxPriorityLength, tasks[i].prioridade);

            // Verificar se a tarefa está atrasada com base na data atual
            if (compareDates(currentDate, tasks[i].DataTerminoInicial) == 1) {
                printf("| Status: Atrasada                                              |\n");
            } else {
                printf("| Status: Pendente                                              |\n");
            }

            printf(" --------------------------------------------------------------\n");
        }
    }
}


void completeTaskWithStatus(struct Task tasks[], int *taskCount, struct CompletedTask completedTasks[], int *completedTaskCount, int taskCode) {
    int found = 0;
    struct Data currentDate = Time();

    for (int i = 0; i < *taskCount; i++) {
        if (tasks[i].codigo == taskCode) {
            struct CompletedTask completedTask;
            struct Task pendingTask;
            completedTask.codigo = tasks[i].codigo;
            strcpy(completedTask.nome, tasks[i].nome);
            strcpy(completedTask.projeto, tasks[i].projeto);
            completedTask.DataInicio = tasks[i].DataInicio;
            completedTask.DataFinal = currentDate;
            completedTask.prioridade = tasks[i].prioridade;
            completedTask.DataTerminoInicial = tasks[i].DataFinal;
            pendingTask.DataFinal = completedTasks[i].DataTerminoInicial;

            // Verificar se a tarefa está atrasada ou não
            if (compareDates(currentDate, tasks[i].DataFinal) == 1) {
                completedTask.status = 1; // Concluída com atraso
            } else {
                completedTask.status = 0; // Concluída sem atraso
            }

            // Adicionar a tarefa concluída à lista de tarefas concluídas
            completedTasks[*completedTaskCount] = completedTask;
            (*completedTaskCount)++;

            // Remover a tarefa da lista de tarefas pendentes
            for (int j = i; j < *taskCount - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            (*taskCount)--;
            found = 1;
            printf("\nTarefa com codigo %d foi marcada como concluida.\n", taskCode);
            break;
        }
    }

    if (!found) {
        printf("\nTarefa com codigo %d nao encontrada.\n", taskCode);
    } else {
        // Após marcar como concluída, atualizar os arquivos tasks.txt e completed_tasks.txt
        saveTasksToFile(tasks, *taskCount, completedTasks, *completedTaskCount);
    }
}

int compareCompletedTasks(const void *a, const void *b) {
    struct CompletedTask *taskA = (struct CompletedTask *)a;
    struct CompletedTask *taskB = (struct CompletedTask *)b;

    // Compare as datas de término (do mais antigo para o mais recente)
    return compareDates(taskA->DataFinal, taskB->DataFinal);
}


void listCompletedTasks(struct CompletedTask completedTasks[], int completedTaskCount) {
    // Determinar o tamanho máximo para cada coluna (semelhante à função listPendingTasks)
    int maxCodeLength = 0;
    int maxNameLength = 0;
    int maxProjectLength = 0;
    int maxPriorityLength = 0;

    qsort(completedTasks, completedTaskCount, sizeof(struct CompletedTask), compareCompletedTasks);

    // Imprimir a tabela com base nos tamanhos máximos calculados
    printf("\n\n --------------------------------------------------------------\n");
    printf("| Tarefas Concluidas:                                           |\n");
    printf("|                                                               |\n");

    for (int i = 0; i < completedTaskCount; i++) {
        printf("| Codigo: %-*d                                                  |\n", maxCodeLength, completedTasks[i].codigo);
        printf("| Nome: %-*s                                                      |\n", maxNameLength, completedTasks[i].nome);
        printf("| Projeto: %-*s                                                   |\n", maxProjectLength, completedTasks[i].projeto);
        printf("| Data de Inicio: %02d/%02d/%04d                                    |\n", completedTasks[i].DataInicio.dia, completedTasks[i].DataInicio.mes, completedTasks[i].DataInicio.ano);
        printf("| Data de Termino: %02d/%02d/%04d                                   |\n", completedTasks[i].DataTerminoInicial.dia, completedTasks[i].DataTerminoInicial.mes, completedTasks[i].DataTerminoInicial.ano);
        printf("| Data de Conclusao: %02d/%02d/%04d                                   |\n", completedTasks[i].DataFinal.dia, completedTasks[i].DataFinal.mes, completedTasks[i].DataFinal.ano);
        printf("| Prioridade: %-*d                                                |\n", maxPriorityLength, completedTasks[i].prioridade);

        if (completedTasks[i].status == 0) {
            printf("| Status: Concluida (Sem atraso)                                |\n");
        } else {
            printf("| Status: Concluida (Com atraso)                                |\n");
        }

        printf(" --------------------------------------------------------------\n");
    }
}

// Função para verificar se o arquivo existe
int fileExists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

// Função para salvar as tarefas em um arquivo TXT
void saveTasksToFile(struct Task tasks[], int taskCount, struct CompletedTask completedTasks[], int completedTaskCount) {
    FILE *file = fopen("tasks.txt", "w"); // Abre o arquivo para escrita

    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "%d;%s;%s;%d/%d/%d;%d/%d/%d;%d/%d/%d;%d;%d\n",
                tasks[i].codigo, tasks[i].nome, tasks[i].projeto,
                tasks[i].DataInicio.dia, tasks[i].DataInicio.mes, tasks[i].DataInicio.ano,
                tasks[i].DataFinal.dia, tasks[i].DataFinal.mes, tasks[i].DataFinal.ano,
                tasks[i].DataTerminoInicial.dia, tasks[i].DataTerminoInicial.mes, tasks[i].DataTerminoInicial.ano,
                tasks[i].status, tasks[i].prioridade);
    }

    fclose(file);
    printf("Tarefas pendentes salvas com sucesso no arquivo tasks.txt.\n");

    // Salvar as tarefas concluídas em um arquivo separado
    file = fopen("completed_tasks.txt", "w");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo de tarefas concluidas para escrita.\n");
        return;
    }

    for (int i = 0; i < completedTaskCount; i++) {
        fprintf(file, "%d;%s;%s;%d/%d/%d;%d/%d/%d;%d/%d/%d;%d;%d\n",
                completedTasks[i].codigo, completedTasks[i].nome, completedTasks[i].projeto,
                completedTasks[i].DataInicio.dia, completedTasks[i].DataInicio.mes, completedTasks[i].DataInicio.ano,
                completedTasks[i].DataFinal.dia, completedTasks[i].DataFinal.mes, completedTasks[i].DataFinal.ano,
                completedTasks[i].DataTerminoInicial.dia, completedTasks[i].DataTerminoInicial.mes, completedTasks[i].DataTerminoInicial.ano,
                completedTasks[i].status, completedTasks[i].prioridade);
    }

    fclose(file);
    printf("Tarefas concluidas salvas com sucesso no arquivo completed_tasks.txt.\n");
}


// Função para carregar as tarefas pendentes de um arquivo TXT
int loadTasksFromFile(struct Task tasks[], int *taskCount) {
    FILE *file = fopen("tasks.txt", "r"); // Abre o arquivo de tarefas pendentes para leitura

    if (file == NULL) {
        printf("Arquivo tasks.txt nao encontrado. Criando um novo arquivo...\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%d;%[^;];%[^;];%d/%d/%d;%d/%d/%d;%d/%d/%d;%d;%d\n",
                  &tasks[count].codigo, tasks[count].nome, tasks[count].projeto,
                  &tasks[count].DataInicio.dia, &tasks[count].DataInicio.mes, &tasks[count].DataInicio.ano,
                  &tasks[count].DataFinal.dia, &tasks[count].DataFinal.mes, &tasks[count].DataFinal.ano,
                  &tasks[count].DataTerminoInicial.dia, &tasks[count].DataTerminoInicial.mes, &tasks[count].DataTerminoInicial.ano,
                  &tasks[count].status, &tasks[count].prioridade) == 14) {
        count++;
    }

    fclose(file);
    *taskCount = count;
    printf("Tarefas pendentes carregadas com sucesso do arquivo tasks.txt.\n");
    return 1;
}


// Função para carregar as tarefas concluídas de um arquivo TXT
int loadCompletedTasksFromFile(struct CompletedTask completedTasks[], int *completedTaskCount) {
    FILE *file = fopen("completed_tasks.txt", "r"); // Abre o arquivo de tarefas concluídas para leitura

    if (file == NULL) {
        printf("Arquivo completed_tasks.txt nao encontrado. Criando um novo arquivo...\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%d;%[^;];%[^;];%d/%d/%d;%d/%d/%d;%d/%d/%d;%d;%d\n",
                  &completedTasks[count].codigo, completedTasks[count].nome, completedTasks[count].projeto,
                  &completedTasks[count].DataInicio.dia, &completedTasks[count].DataInicio.mes, &completedTasks[count].DataInicio.ano,
                  &completedTasks[count].DataFinal.dia, &completedTasks[count].DataFinal.mes, &completedTasks[count].DataFinal.ano,
                  &completedTasks[count].DataTerminoInicial.dia, &completedTasks[count].DataTerminoInicial.mes, &completedTasks[count].DataTerminoInicial.ano,
                  &completedTasks[count].status, &completedTasks[count].prioridade) == 14) {
        count++;
    }

    fclose(file);
    *completedTaskCount = count;
    printf("Tarefas concluidas carregadas com sucesso do arquivo completed_tasks.txt.\n");
    return 1;
}

// Função para excluir uma tarefa do arquivo com base no código
void deleteTaskFromFile(const char *filename, int taskCode) {
    FILE *file = fopen(filename, "r"); // Abre o arquivo para leitura
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    // Crie um arquivo temporário para armazenar as tarefas que não devem ser excluídas
    FILE *tempFile = fopen("temp.txt", "w");

    if (tempFile == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(file);
        return;
    }

    int found = 0; // Variável para verificar se a tarefa foi encontrada

    while (!feof(file)) {
        struct Task task;
        if (fscanf(file, "%d;%[^;];%[^;];%d/%d/%d;%d/%d/%d;%d/%d/%d;%d;%d\n",
                   &task.codigo, task.nome, task.projeto,
                   &task.DataInicio.dia, &task.DataInicio.mes, &task.DataInicio.ano,
                   &task.DataFinal.dia, &task.DataFinal.mes, &task.DataFinal.ano,
                   &task.DataTerminoInicial.dia, &task.DataTerminoInicial.mes, &task.DataTerminoInicial.ano,
                   &task.status, &task.prioridade) == 14) {
            if (task.codigo != taskCode) {
                // Se o código da tarefa for diferente do código a ser excluído, escreva no arquivo temporário
                fprintf(tempFile, "%d;%s;%s;%d/%d/%d;%d/%d/%d;%d/%d/%d;%d;%d\n",
                        task.codigo, task.nome, task.projeto,
                        task.DataInicio.dia, task.DataInicio.mes, task.DataInicio.ano,
                        task.DataFinal.dia, task.DataFinal.mes, task.DataFinal.ano,
                        task.DataTerminoInicial.dia, task.DataTerminoInicial.mes, task.DataTerminoInicial.ano,
                        task.status, task.prioridade);
            } else {
                found = 1; // Tarefa encontrada e excluída
            }
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("Tarefa com codigo %d nao encontrada.\n", taskCode);
        remove("temp.txt"); // Se não encontrou, exclua o arquivo temporário
    } else {
        // Substitua o arquivo original pelo arquivo temporário (a tarefa foi excluída)
        if (remove(filename) == 0 && rename("temp.txt", filename) == 0) {
            printf("Tarefa com codigo %d excluida permanentemente.\n", taskCode);
        } else {
            printf("Erro ao excluir a tarefa.\n");
        }
    }
}

// Função para excluir permanentemente uma tarefa pendente
void deletePendingTask(struct Task tasks[], int *taskCount, int taskCode) {
    int found = 0; // Variável para verificar se a tarefa foi encontrada

    for (int i = 0; i < *taskCount; i++) {
        if (tasks[i].codigo == taskCode) {
            found = 1;
            // Remove a tarefa da lista de tarefas concluídas (memória)
            for (int j = i; j < *taskCount - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            (*taskCount)--;
            break; // Não é necessário continuar procurando
        }
    }

    if (found) {
        // Após excluir da memória, exclua permanentemente do arquivo completed_tasks.txt
        deleteTaskFromFile("tasks.txt", taskCode);
    } else {
        printf("\nTarefa com codigo %d nao encontrada.\n", taskCode);
    }
}

// Função para excluir permanentemente uma tarefa concluída
void deleteCompletedTask(struct CompletedTask completedTasks[], int *completedTaskCount, int taskCode) {
    int found = 0; // Variável para verificar se a tarefa foi encontrada

    for (int i = 0; i < *completedTaskCount; i++) {
        if (completedTasks[i].codigo == taskCode) {
            found = 1;
            // Remove a tarefa da lista de tarefas concluídas (memória)
            for (int j = i; j < *completedTaskCount - 1; j++) {
                completedTasks[j] = completedTasks[j + 1];
            }
            (*completedTaskCount)--;
            break; // Não é necessário continuar procurando
        }
    }

    if (found) {
        // Após excluir da memória, exclua permanentemente do arquivo completed_tasks.txt
        deleteTaskFromFile("completed_tasks.txt", taskCode);
    } else {
        printf("\nTarefa com codigo %d nao encontrada.\n", taskCode);
    }
}

// Função para marcar uma tarefa como concluída
void completeTask(struct Task tasks[], int *taskCount, struct CompletedTask completedTasks[], int *completedTaskCount, int taskCode) {
    int found = 0;

    for (int i = 0; i < *taskCount; i++) {
        if (tasks[i].codigo == taskCode) {
            struct CompletedTask completedTask;
            completedTask.codigo = tasks[i].codigo;
            strcpy(completedTask.nome, tasks[i].nome);
            strcpy(completedTask.projeto, tasks[i].projeto);
            completedTask.DataInicio = tasks[i].DataInicio;
            completedTask.DataFinal = tasks[i].DataFinal;
            completedTask.status = tasks[i].status;

            // Adicionar a tarefa concluída à lista de tarefas concluídas
            completedTasks[*completedTaskCount] = completedTask;
            (*completedTaskCount)++;

            // Remover a tarefa da lista de tarefas pendentes
            for (int j = i; j < *taskCount - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            (*taskCount)--;
            found = 1;
            printf("\nTarefa com codigo %d foi marcada como concluida.\n", taskCode);
            break;
        }
    }

    if (!found) {
        printf("\nTarefa com codigo %d nao encontrada.\n", taskCode);
    } else {
        // Após marcar como concluída, atualize os arquivos tasks.txt e completed_tasks.txt
        saveTasksToFile(tasks, *taskCount, completedTasks, *completedTaskCount);
    }
}

// Função para modificar informações de uma tarefa com base no código
void modificaTask(struct Task tasks[], int *taskCount, int taskCode) {
    int found = 0;
    int choicemod;

    for (int i = 0; i < *taskCount; i++) {
        if (tasks[i].codigo == taskCode) {
            printf(" --------------------------------------\n");
            printf("| Qual informacao gostaria de alterar? |\n");
            printf("| 1. Codigo da tarefa                  |\n");
            printf("| 2. Nome da tarefa                    |\n");
            printf("| 3. Nome do projeto                   |\n");
            printf("| 4. Data de inicio                    |\n");
            printf("| 5. Data de termino                   |\n");
            printf("| 6. Prioridade                        |\n");
            printf(" --------------------------------------\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &choicemod);

            switch (choicemod) {
                case 1:
                    printf("Novo codigo da tarefa: ");
                    scanf("%d", &tasks[i].codigo);
                    break;
                case 2:
                    printf("Novo nome da tarefa (ate 30 caracteres): ");
                    scanf(" %[^\n]", tasks[i].nome);
                    break;
                case 3:
                    printf("Novo nome do projeto (ate 30 caracteres): ");
                    scanf(" %[^\n]", tasks[i].projeto);
                    break;
                case 4:
                    printf("Nova data de inicio (dia mes ano): ");
                    scanf("%d %d %d", &tasks[i].DataInicio.dia, &tasks[i].DataInicio.mes, &tasks[i].DataInicio.ano);
                    break;
                case 5:
                    printf("Nova data de termino (dia mes ano): ");
                    scanf("%d %d %d", &tasks[i].DataTerminoInicial.dia, &tasks[i].DataTerminoInicial.mes, &tasks[i].DataTerminoInicial.ano);
                    break;
                case 6:
                    printf("Nova prioridade: ");
                    scanf("%d", &tasks[i].prioridade);
                    break;
                default:
                    printf("Opcao invalida. Nenhuma alteracao foi feita.\n");
            }

            found = 1;
            printf("Informacao alterada com sucesso.\n");
            break; // Não é necessário continuar procurando
        }
    }

    if (!found) {
        printf("Tarefa com codigo %d nao encontrada.\n", taskCode);
    } else {
        // Após a modificação, atualize o arquivo tasks.txt
        saveTasksToFile(tasks, *taskCount, NULL, 0);
    }
}

void revertTaskToPending(struct Task tasks[], int *taskCount, struct CompletedTask completedTasks[], int *completedTaskCount, int taskCode) {
    int found = 0;

    for (int i = 0; i < *completedTaskCount; i++) {
        if (completedTasks[i].codigo == taskCode) {
            struct Task pendingTask;
            pendingTask.codigo = completedTasks[i].codigo;
            strcpy(pendingTask.nome, completedTasks[i].nome);
            strcpy(pendingTask.projeto, completedTasks[i].projeto);
            pendingTask.DataInicio = completedTasks[i].DataInicio;
            pendingTask.DataFinal = completedTasks[i].DataTerminoInicial;
            pendingTask.status = -1; // Definir como pendente
            pendingTask.prioridade = completedTasks[i].prioridade;

            // Adicionar a tarefa pendente à lista de tarefas pendentes
            tasks[*taskCount] = pendingTask;
            (*taskCount)++;

            tasks[i].DataTerminoInicial.dia = tasks[i].DataFinal.dia;
            tasks[i].DataTerminoInicial.mes = tasks[i].DataFinal.mes;
            tasks[i].DataTerminoInicial.ano = tasks[i].DataFinal.ano;

            // Remover a tarefa da lista de tarefas concluídas
            for (int j = i; j < *completedTaskCount - 1; j++) {
                completedTasks[j] = completedTasks[j + 1];
            }
            (*completedTaskCount)--;
            found = 1;
            printf("\nTarefa com codigo %d foi revertida para o estado pendente.\n", taskCode);
            break;
        }
    }

    if (!found) {
        printf("\nTarefa com codigo %d nao encontrada nas tarefas concluidas.\n", taskCode);
    } else {
        // Após reverter, atualize os arquivos tasks.txt e completed_tasks.txt
        saveTasksToFile(tasks, *taskCount, completedTasks, *completedTaskCount);
    }
}


int main() {
    struct Task tasks[100];
    int taskCount = 0;
    struct CompletedTask completedTasks[100];
    int completedTaskCount = 0;
    int choice;
    int taskCode;
    struct Data currentDate;
    int desiredPriority;

    // Verificar se o arquivo existe, e criar se não existir
    if (!fileExists("tasks.txt")) {
        printf("Arquivo tasks.txt nao encontrado. Criando um novo arquivo...\n");
        FILE *file = fopen("tasks.txt", "w");
        if (file) {
            fclose(file);
        } else {
            printf("Erro ao criar o arquivo tasks.txt.\n");
            return 1;
        }
    }

    if (!fileExists("completed_tasks.txt")) {
        printf("Arquivo completed_tasks.txt nao encontrado. Criando um novo arquivo...\n");
        FILE *file = fopen("completed_tasks.txt", "w");
        if (file) {
            fclose(file);
        } else {
            printf("Erro ao criar o arquivo completed_tasks.txt.\n");
            return 1;
        }
    }

    // Carregar tarefas do arquivo ao iniciar o programa
    if (loadTasksFromFile(tasks, &taskCount)) {
        printf("%d tarefas pendentes carregadas do arquivo.\n", taskCount);
    }

    // Carregar tarefas concluídas do arquivo ao iniciar o programa
    if (loadCompletedTasksFromFile(completedTasks, &completedTaskCount)) {
        printf("%d tarefas concluidas carregadas do arquivo.\n", completedTaskCount);
    }

    while (1) {
        Time();
        printf(" -------------------------------------\n");
        printf("| Sistema de Gerenciamento de Tarefas |\n");
        printf("| 1. Adicionar uma nova Tarefa        |\n");
        printf("| 2. Listar Tarefas Pendentes         |\n");
        printf("| 3. Concluir uma tarefa              |\n");
        printf("| 4. Reverter uma tarefa concluida    |\n");
        printf("| 5. Modificar uma tarefa             |\n");
        printf("| 6. Listar tarefas concluidas        |\n");
        printf("| 7. Excluir uma tarefa pendente      |\n");
        printf("| 8. Excluir uma tarefa concluida     |\n");
        printf("| 9. Sair                             |\n");
        printf(" -------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask(tasks, &taskCount, completedTasks, &completedTaskCount);
                break;
            case 2:
                if (taskCount > 0){
                    printf(" ----------------------------------------------\n");
                    printf("| Qual a prioridade das tarefas que deseja ver |\n");
                    printf("| 1. Prioridade mais alta                      |\n");
                    printf("| 2. Prioridade mediana                        |\n");
                    printf("| 3. Prioridade mais baixa                     |\n");
                    printf(" ----------------------------------------------\n");
                    scanf("%d", &desiredPriority);
                    if(desiredPriority < 1 || desiredPriority > 3){
                        printf("ERRO: digite um numero valido.");
                    }
                    listPendingTasks(tasks, taskCount, desiredPriority);
                }
                else {
                    printf("Nenhuma tarefa pendente encontrada!\n\n");
                }
                break;
            case 3:
                printf("Digite o codigo da tarefa que deseja concluir: ");
                scanf("%d", &taskCode);
                completeTaskWithStatus(tasks, &taskCount, completedTasks, &completedTaskCount, taskCode);
                break;
            case 4:
                printf("Digite o codigo da tarefa que deseja reverter para pendente: ");
                scanf("%d", &taskCode);
                revertTaskToPending(tasks, &taskCount, completedTasks, &completedTaskCount, taskCode);
                break;
            case 5:
                printf("Digite o codigo da tarefa que deseja modificar: ");
                scanf("%d", &taskCode);
                modificaTask(tasks, &taskCount, taskCode);
                break;
            case 6:
                if (completedTaskCount > 0)
                    listCompletedTasks(completedTasks, completedTaskCount);
                else {
                    printf("Nenhuma tarefa concluida encontrada!\n\n");
                }
                break;
            case 7:
                printf("Digite o codigo da tarefa pendente que deseja excluir: ");
                scanf("%d", &taskCode);
                deletePendingTask(tasks, &taskCount, taskCode); // Para excluir uma tarefa pendente
                break;
            case 8:
                printf("Digite o codigo da tarefa concluida que deseja excluir: ");
                scanf("%d", &taskCode);
                deleteCompletedTask(completedTasks, &completedTaskCount, taskCode); // Para excluir uma tarefa concluída
                break;
            case 9:
                saveTasksToFile(tasks, taskCount, completedTasks, completedTaskCount);
                printf("Saindo do programa. Tarefas salvas.\n");
                exit(0);
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}
