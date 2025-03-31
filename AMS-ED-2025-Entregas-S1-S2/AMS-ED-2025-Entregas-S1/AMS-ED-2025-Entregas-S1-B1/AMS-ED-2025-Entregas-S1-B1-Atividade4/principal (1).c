#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 4  // Memória da HP12c: X, Y, Z, T

typedef struct {
    double itens[MAX];
    char expressao[100]; // Armazena a expressão algébrica
    int topo;
} Pilha;

// Funções da Pilha
Pilha* criar_pilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->topo = -1;
    p->expressao[0] = '\0'; // Inicializa a expressão vazia
    return p;
}

int vazia(Pilha* p) {
    return p->topo == -1;
}

int cheia(Pilha* p) {
    return p->topo == MAX - 1;
}

void push(Pilha* p, double dado, char* expr) {
    if (cheia(p)) {
        printf("Erro: Pilha cheia!\n");
        return;
    }
    p->itens[++p->topo] = dado;
    if (strlen(p->expressao) == 0)
        strcpy(p->expressao, expr);
    else {
        strcat(p->expressao, " ");
        strcat(p->expressao, expr);
    }
}

double pop(Pilha* p) {
    if (vazia(p)) {
        printf("Erro: Pilha vazia!\n");
        exit(1);
    }
    return p->itens[p->topo--];
}

double top(Pilha* p) {
    if (vazia(p)) {
        printf("Erro: Pilha vazia!\n");
        exit(1);
    }
    return p->itens[p->topo];
}

// Função para calcular expressões RPN e converter para notação algébrica
double calcular_rpn(char* expressao, char* expressao_alg) {
    Pilha* p = criar_pilha();
    char* token = strtok(expressao, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(p, atof(token), token);
        } else {
            double op2 = pop(p);
            double op1 = pop(p);
            char temp[100];
            sprintf(temp, "(%g %c %g)", op1, token[0], op2);
            push(p, (token[0] == '+') ? op1 + op2 :
                     (token[0] == '-') ? op1 - op2 :
                     (token[0] == '*') ? op1 * op2 :
                                         op1 / op2,
                 temp);
        }
        token = strtok(NULL, " ");
    }
    double resultado = pop(p);
    strcpy(expressao_alg, p->expressao);
    free(p);
    return resultado;
}

int main() {
    char expressao[100], expressao_alg[100];
    printf("Digite a expressão RPN: ");
    fgets(expressao, sizeof(expressao), stdin);
    expressao[strcspn(expressao, "\n")] = 0;
    
    double resultado = calcular_rpn(expressao, expressao_alg);
    printf("Expressão Algébrica: %s\n", expressao_alg);
    printf("Resultado: %.2f\n", resultado);
    return 0;
}