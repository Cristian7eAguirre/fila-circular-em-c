#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ATENDIMENTO 4

typedef struct {
    int senha;
    char nome[50];
} Pessoa;

typedef struct {
    Pessoa pessoas[MAX_ATENDIMENTO];
    int inicio;
    int fim;
    int quantidade;
    int proximaSenha;
} FilaAtendimento;

void inicializarFila(FilaAtendimento *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
    f->proximaSenha = 1;
}

int estaVazia(FilaAtendimento *f) {
    return (f->quantidade == 0);
}

int estaCheia(FilaAtendimento *f) {
    return (f->quantidade == MAX_ATENDIMENTO);
}

void exibirStatus(FilaAtendimento *f) {
    printf("[STATUS] inicio = %d | fim = %d | quantidade = %d (Capacidade: %d)\n", 
           f->inicio, f->fim, f->quantidade, MAX_ATENDIMENTO);
}

void inserirPessoa(FilaAtendimento *f, char *nome) {
    if (estaCheia(f)) {
        printf("\n[OVERFLOW] A fila de atendimento esta cheia! Nao e possivel adicionar '%s'.\n", nome);
        exibirStatus(f);
        return;
    }

    f->pessoas[f->fim].senha = f->proximaSenha++;
    strcpy(f->pessoas[f->fim].nome, nome);
    
    printf("\n[INSERCAO] Senha %d (%s) adicionada com sucesso.\n", f->pessoas[f->fim].senha, nome);
    
    f->fim = (f->fim + 1) % MAX_ATENDIMENTO;
    f->quantidade++;
    
    exibirStatus(f);
}

void chamarProximaPessoa(FilaAtendimento *f) {
    if (estaVazia(f)) {
        printf("\n[UNDERFLOW] A fila esta vazia! Nao ha clientes para atender.\n");
        exibirStatus(f);
        return;
    }

    Pessoa atendida = f->pessoas[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_ATENDIMENTO;
    f->quantidade--;

    printf("\n[ATENDIMENTO] Chamando a senha %d - %s para o guiche!\n", atendida.senha, atendida.nome);
    exibirStatus(f);
}

void visualizarFila(FilaAtendimento *f) {
    if (estaVazia(f)) {
        printf("\n--- FILA DE ATENDIMENTO VAZIA ---\n");
        exibirStatus(f);
        return;
    }

    printf("\n--- FILA DE ESPERA ATUAL ---\n");
    exibirStatus(f);
    printf("Pessoas na espera:\n");
    
    int i, idx;
    for (i = 0; i < f->quantidade; i++) {
        idx = (f->inicio + i) % MAX_ATENDIMENTO;
        printf("  -> [%d] Senha: %d | Nome: %s\n", i + 1, f->pessoas[idx].senha, f->pessoas[idx].nome);
    }
    printf("-------------------------------\n");
}

int main() {
    FilaAtendimento fila;
    inicializarFila(&fila);
    int opcao;
    char nome[50];

    do {
        printf("\n=== SISTEMA DE ATENDIMENTO (Exercicio 2) ===\n");
        printf("1. Inserir pessoa na fila (Gerar Senha)\n");
        printf("2. Chamar proxima pessoa (Atender)\n");
        printf("3. Visualizar fila de espera\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida!\n");
            while(getchar() != '\n');
            continue;
        }
        getchar();

        switch (opcao) {
            case 1:
                printf("Digite o nome da pessoa: ");
                if (fgets(nome, sizeof(nome), stdin) != NULL) {
                    nome[strcspn(nome, "\n")] = 0;
                    inserirPessoa(&fila, nome);
                }
                break;
            case 2:
                chamarProximaPessoa(&fila);
                break;
            case 3:
                visualizarFila(&fila);
                break;
            case 4:
                printf("\nEncerrando sistema de atendimento...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while (opcao != 4);

    return 0;
}
