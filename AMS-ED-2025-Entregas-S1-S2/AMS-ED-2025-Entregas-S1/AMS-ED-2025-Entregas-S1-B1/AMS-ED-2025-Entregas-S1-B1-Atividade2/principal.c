/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: xxxxxxxxxxx                             */
/*             Objetivo: Implementação de um sistema para seleção de residência    */
/*                        médica, utilizando vetores e ponteiros.                  */
/*                                                                                  */
/*                                  Autor: xxxxxxxxxxxxxxxxxxxxxxxxxxx              */
/*                                                                    Data:xx/xx/xxx*/
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATOS 50

typedef struct {
    char nome[100];
    float notasPE[4];
    float notasAC[5];
    float notasPP[10];
    float notasEB[3];
    float notaFinal;
} Candidato;

void receberNotas(float *notas, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("Digite a nota %d: ", i + 1);
        scanf("%f", &notas[i]);
    }
}

float calcularNotaFinal(float *notas, int tamanho) {
    float maior = notas[0], menor = notas[0], soma = 0;
    for (int i = 0; i < tamanho; i++) {
        if (notas[i] > maior) maior = notas[i];
        if (notas[i] < menor) menor = notas[i];
        soma += notas[i];
    }
    return (soma - maior - menor) / (tamanho - 2);
}

void ordenarCandidatos(Candidato *candidatos, int total) {
    for (int i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {
            if (candidatos[i].notaFinal < candidatos[j].notaFinal) {
                Candidato temp = candidatos[i];
                candidatos[i] = candidatos[j];
                candidatos[j] = temp;
            }
        }
    }
}

int main() {
    Candidato candidatos[MAX_CANDIDATOS];
    int totalCandidatos = 0;
    char continuar;
    
    do {
        if (totalCandidatos >= MAX_CANDIDATOS) {
            printf("Número máximo de candidatos atingido!\n");
            break;
        }

        printf("Digite o nome do candidato: ");
        scanf(" %99[^\n]", candidatos[totalCandidatos].nome);

        printf("Notas da Prova Escrita:\n");
        receberNotas(candidatos[totalCandidatos].notasPE, 4);
        printf("Notas da Análise Curricular:\n");
        receberNotas(candidatos[totalCandidatos].notasAC, 5);
        printf("Notas da Prova Prática:\n");
        receberNotas(candidatos[totalCandidatos].notasPP, 10);
        printf("Notas da Entrevista:\n");
        receberNotas(candidatos[totalCandidatos].notasEB, 3);

        float PE = calcularNotaFinal(candidatos[totalCandidatos].notasPE, 4);
        float AC = calcularNotaFinal(candidatos[totalCandidatos].notasAC, 5);
        float PP = calcularNotaFinal(candidatos[totalCandidatos].notasPP, 10);
        float EB = calcularNotaFinal(candidatos[totalCandidatos].notasEB, 3);
        
        candidatos[totalCandidatos].notaFinal = (PE * 0.3) + (AC * 0.1) + (PP * 0.4) + (EB * 0.2);

        totalCandidatos++;

        printf("Deseja cadastrar outro candidato? (S/N): ");
        scanf(" %c", &continuar);
    } while (continuar == 'S' || continuar == 's');

    ordenarCandidatos(candidatos, totalCandidatos);

    printf("\nTop 5 candidatos:\n");
    for (int i = 0; i < (totalCandidatos < 5 ? totalCandidatos : 5); i++) {
        printf("%d. %s - Nota Final: %.2f\n", i + 1, candidatos[i].nome, candidatos[i].notaFinal);
    }

    return 0;
}
