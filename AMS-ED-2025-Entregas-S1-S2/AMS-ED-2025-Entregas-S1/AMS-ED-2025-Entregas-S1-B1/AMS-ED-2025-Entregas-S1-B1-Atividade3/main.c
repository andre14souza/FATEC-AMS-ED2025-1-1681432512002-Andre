#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo estrutura do pedido
typedef struct Pedido {
    int numero;               // Número do pedido (gerado automaticamente)
    char cliente[50];
    char descricao[100];
    int quantidade;
    int contadorStatus;       // Contador de status: 1=pendente, 2=em preparo, 3=pronto, 4=entregue
    struct Pedido *proximo;
} Pedido;

// Função para criar um novo pedido
Pedido* criarPedido(int numero, const char *cliente, const char *descricao, int quantidade) {
    Pedido *novo = (Pedido*)malloc(sizeof(Pedido));
    if (!novo) {
        printf("Erro ao alocar memória para o novo pedido.\n");
        return NULL;
    }
    novo->numero = numero;
    strcpy(novo->cliente, cliente);
    strcpy(novo->descricao, descricao);
    novo->quantidade = quantidade;
    novo->contadorStatus = 1;  // Status inicial é "pendente"
    novo->proximo = NULL;
    return novo;
}

// Função para inserir um pedido na lista
void inserirPedido(Pedido **lista, Pedido *novo) {
    if (*lista == NULL) {
        *lista = novo;
    } else {
        Pedido *temp = *lista;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novo;
    }
}

// Função para buscar um pedido pelo número
Pedido* obterPedido(Pedido *lista, int numero) {
    while (lista != NULL) {
        if (lista->numero == numero) {
            return lista;
        }
        lista = lista->proximo;
    }
    return NULL;
}

// Função para atualizar o status de um pedido
void atualizarStatus(Pedido *pedido) {
    if (pedido->contadorStatus < 4) {
        pedido->contadorStatus++; // Incrementa o contador de status
        switch (pedido->contadorStatus) {
            case 2:
                printf("Status do pedido %d atualizado para: Em Preparo\n", pedido->numero);
                break;
            case 3:
                printf("Status do pedido %d atualizado para: Pronto\n", pedido->numero);
                break;
            case 4:
                printf("Status do pedido %d atualizado para: Entregue\n", pedido->numero);
                break;
        }
    } else {
        printf("O status do pedido %d não pode ser alterado, pois já foi marcado como 'Entregue'.\n", pedido->numero);
    }
}

// Função para deletar um pedido e reajustar os números dos pedidos subsequentes
void deletarPedido(Pedido **lista, int numero) {
    Pedido *atual = *lista;
    Pedido *anterior = NULL;
    Pedido *remover = NULL;

    // Encontra o pedido a ser removido
    while (atual != NULL && atual->numero != numero) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Pedido %d não encontrado.\n", numero);
        return;
    }

    // Ajusta a lista removendo o pedido encontrado
    if (anterior == NULL) {
        *lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    
    // Libera a memória do pedido removido
    remover = atual;
    free(remover);

    printf("Pedido %d removido com sucesso.\n", numero);

    // Agora, reajusta os números dos pedidos subsequentes
    atual = *lista;
    int novoNumero = 1;
    while (atual != NULL) {
        atual->numero = novoNumero++;
        atual = atual->proximo;
    }
}

// Função para liberar toda a lista
void liberarLista(Pedido *lista) {
    Pedido *temp;
    while (lista != NULL) {
        temp = lista;
        lista = lista->proximo;
        free(temp);
    }
}

// Função para exibir um pedido
void exibirPedido(Pedido *pedido) {
    if (pedido != NULL) {
        printf("Pedido Nº: %03d\nCliente: %s\nPrato: %s\nQuantidade: %d\nStatus: ", 
               pedido->numero, pedido->cliente, pedido->descricao, pedido->quantidade);
        switch (pedido->contadorStatus) {
            case 1:
                printf("Pendente\n");
                break;
            case 2:
                printf("Em Preparo\n");
                break;
            case 3:
                printf("Pronto\n");
                break;
            case 4:
                printf("Entregue\n");
                break;
        }
    } else {
        printf("Pedido não encontrado.\n");
    }
}

// Função para exibir todos os pedidos
void exibirTodosPedidos(Pedido *lista) {
    if (lista == NULL) {
        printf("Nenhum pedido registrado.\n");
    } else {
        Pedido *temp = lista;
        while (temp != NULL) {
            exibirPedido(temp);
            temp = temp->proximo;
        }
    }
}

int main() {
    Pedido *listaPedidos = NULL;
    int opcao, quantidade, numero;
    char cliente[50], descricao[100];

    do {
        printf("\nMenu de Opções:\n");
        printf("1. Inserir Pedido\n");
        printf("2. Atualizar Status do Pedido\n");
        printf("3. Deletar Pedido\n");
        printf("4. Exibir Pedido\n");
        printf("5. Exibir Todos os Pedidos\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: // Inserir pedido
                // Gerar número automaticamente com base no número de pedidos na lista
                int numero = 1;
                if (listaPedidos != NULL) {
                    Pedido *temp = listaPedidos;
                    while (temp->proximo != NULL) {
                        temp = temp->proximo;
                        numero++;
                    }
                }
                
                printf("Digite o nome do cliente: ");
                getchar(); // Para limpar o buffer do enter
                fgets(cliente, sizeof(cliente), stdin);
                cliente[strcspn(cliente, "\n")] = '\0';  // Remover o \n do fgets
                
                printf("Digite a descrição do prato: ");
                fgets(descricao, sizeof(descricao), stdin);
                descricao[strcspn(descricao, "\n")] = '\0'; // Remover o \n do fgets
                
                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);

                // Criando e inserindo o pedido
                Pedido *novoPedido = criarPedido(numero, cliente, descricao, quantidade);
                inserirPedido(&listaPedidos, novoPedido);
                break;

            case 2: // Atualizar status
                printf("Digite o número do pedido: ");
                scanf("%d", &numero);
                Pedido *pedido = obterPedido(listaPedidos, numero);
                if (pedido != NULL) {
                    atualizarStatus(pedido);
                } else {
                    printf("Pedido não encontrado.\n");
                }
                break;

            case 3: // Deletar pedido
                printf("Digite o número do pedido: ");
                scanf("%d", &numero);
                deletarPedido(&listaPedidos, numero);
                break;

            case 4: // Exibir pedido
                printf("Digite o número do pedido: ");
                scanf("%d", &numero);
                exibirPedido(obterPedido(listaPedidos, numero));
                break;

            case 5: // Exibir todos os pedidos
                exibirTodosPedidos(listaPedidos);
                break;

            case 6: // Sair
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 6);

    liberarLista(listaPedidos);
    return 0;
}