#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct{
    int itens[MAX];
    int inicio;
    int fim;
    int quantidade;
}FilaCircular;

//Inicializar a fila 
void Inicializar(FilaCircular *f) {
    f->inicio=0;
    f->fim=0;
    f->quantidade=0;
}

int estaVazia(FilaCircular *f){
    return (f->quantidade==0);
}

int estaCheia(FilaCircular *f) {
    return(f->quantidade==MAX);
}    
    void Inserir(FilaCircular *f, int valor){
        if(estaCheia(f)) {
            printf("\n[ERRO] Overflow: A fila esta cheia! Nao e possivel inserir o valor %d.\n", valor);
            return;
        }
        f->itens[f->fim]= valor;
        f->fim= (f->fim + 1) % MAX;
        f->quantidade++;
        printf("[SUCESSO] Elemento %d inserido com sucesso. \n", valor);
    }
    
    void Remover(FilaCircular *f) {
        if(estaVazia(f)){
            printf("\n[ERRO] Underflow: A fila esta vazia! Nao ha elementos para remover. \n");
            return;
        }
        int valorRemovido=f->itens[f->inicio];
        f->inicio=(f->inicio + 1) % MAX;
        f->quantidade--;
        printf("\n[SUCESSO] Elemento %d removido da fila.\n", valorRemovido);
    }
    
    void Listar(FilaCircular *f){
        if(estaVazia(f)){
            printf("\n A fila esta vazia.\n");
            return;
        }
        printf("\n--- ESTADO ATUAL DA FILA ---\n");
        printf("Inicio: %d | Fim: %d | Quantidade: %d/*myDataMAX\n", f->inicio, f->fim, f->quantidade);
        printf("Elementos: [");
        
        int i, idx;
        for(i=0; i<f->quantidade; i++) {
            idx=(f->inicio + i) % MAX;
            printf("%d", f->itens[idx]);
        }
        printf("]\n-------------------------\n");
    }
    
    int main() {
        FilaCircular fila;
        Inicializar(&fila);
        int opcao, valor;
        
        do{
            printf("\n=== MENU FILA CIRCULAR (Exercicio 1)===\n");
            printf("1. Inserir elemento\n");
            printf("2. Remover elemento\n");
            printf("3. Listar elementos\n");
            printf("4. Sair\n");
            printf("Escolha uma opcao:");
            if(scanf("%d", &opcao) != 1){
                printf("Opcao invalida!\n");
                break;
            }
            
            switch(opcao){
                case 1:
                printf("Digite o valor inteiro a ser inserido: ");
                scanf("%d", &valor);
                Inserir(&fila, valor);
                break;
            case 2:
                Remover(&fila);
                break;
            case 3:
                Listar(&fila);
                break;
            case 4:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}
