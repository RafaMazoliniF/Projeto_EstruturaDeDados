# Projeto_EstruturaDeDados
## Como o projeto está organizado?
- **estruturas.h**:
  - Arquivo com todas as definições e funções das estruturas de dados utilizadas.

- **main.c**
  - Arquivo com a função principal e as funções adicionais específicas para o uso da main().

## Como foram implementadas as estrutaras para a resolução do problema proposto?
- **struct Tarefa**:
    - A estrutura guardas todas as informações exigidas:
      - Código
      - Nome da tarefa
      - Nome do projeto
      - status
      - prioridas
- **struct No**: Estrutura comum de lista ligada -> giarda um ponteiro para uma tarefa e um ponteiro para o próximo nó.

## Detalhes importantes:
  Na main, as filas de tarefas separadas por prioridade foram armazenadas em um vetor que guarda 3 ponteiros para as respectivas filas:
  - [0] fila de prioridade 1;
  - [1] fila de prioridade 2;
  - [2] fila de prioridade 3;

  A lista de tarefas pendentes é uma lista ligada comum.
