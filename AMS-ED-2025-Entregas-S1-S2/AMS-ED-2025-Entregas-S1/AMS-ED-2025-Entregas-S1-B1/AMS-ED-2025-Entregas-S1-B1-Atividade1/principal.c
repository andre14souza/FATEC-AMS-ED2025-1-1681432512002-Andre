/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

// Função para aplicar o desconto
void aplicarDesconto(float *preco, float desconto) {
    *preco -= (*preco * (desconto / 100));
}

int main() {
    float preco, desconto;
    
    // Solicita o preço do produto
    printf("Digite o preco do produto: ");
    scanf("%f", &preco);
    
    
    // Solicita o valor do desconto
    printf("Digite o percentual de desconto: ");
    scanf("%f", &desconto);
    
    // Exibe o preço original
    printf("Preco original: %.2f\n", preco);
    
    // Aplica o desconto
    aplicarDesconto(&preco, desconto);
    
    // Exibe o desconto e o preço final
    printf("Desconto aplicado: %.2f%%\n", desconto);
    printf("Preco final apos desconto: %.2f\n", preco);
    
    return 0;
}
