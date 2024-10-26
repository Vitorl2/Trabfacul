#include <stdio.h>
#include <stdlib.h>

// Estrutura para um nó da lista
typedef struct Node {
    int valor;
    struct Node* proximo;
} Node;

// Estrutura para a lista
typedef struct {
    Node* cabeca;
} Lista;

// Função para criar uma nova lista
Lista* criarLista() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    lista->cabeca = NULL;
    return lista;
}

// Função para inserir um valor na lista (no início)
void inserirLista(Lista* lista, int valor) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->valor = valor;
    novo->proximo = lista->cabeca;
    lista->cabeca = novo;
}

// Função para exibir os elementos da lista
void exibirLista(Lista* lista) {
    Node* atual = lista->cabeca;
    if (atual == NULL) {
        printf("A lista está vazia.\n");
        return;
    }
    printf("Elementos da lista: ");
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

// Função para verificar se a lista está vazia
int verificarVazia(Lista* lista) {
    return lista->cabeca == NULL;
}

// Função para buscar um valor na lista
Node* buscarLista(Lista* lista, int valor) {
    Node* atual = lista->cabeca;
    while (atual != NULL) {
        if (atual->valor == valor) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

// Função para excluir um valor da lista
void excluirLista(Lista* lista, int valor) {
    Node* atual = lista->cabeca;
    Node* anterior = NULL;

    // Percorre a lista para encontrar o valor a ser excluído
    while (atual != NULL && atual->valor != valor) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Se o valor não foi encontrado
    if (atual == NULL) {
        printf("Valor %d não encontrado na lista.\n", valor);
        return;
    }

    // Se o nó a ser excluído é o primeiro
    if (anterior == NULL) {
        lista->cabeca = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual); // Libera a memória do nó excluído
    printf("Valor %d excluído com sucesso.\n", valor);
}

// Função para liberar a memória da lista
void liberarLista(Lista* lista) {
    Node* atual = lista->cabeca;
    while (atual != NULL) {
        Node* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    free(lista); // Libera a memória da lista
}

// Função para inserir um valor em ordem crescente
void inserirOrdenado(Lista* lista, int valor) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->valor = valor;

    // Caso a lista esteja vazia ou o novo valor é menor que o primeiro
    if (lista->cabeca == NULL || lista->cabeca->valor >= valor) {
        novo->proximo = lista->cabeca;
        lista->cabeca = novo;
        return;
    }

    // Percorre a lista até encontrar a posição correta
    Node* atual = lista->cabeca;
    while (atual->proximo != NULL && atual->proximo->valor < valor) {
        atual = atual->proximo;
    }

    novo->proximo = atual->proximo;
    atual->proximo = novo;
}

// Função principal para testar a lista
int main() {
    Lista* lista = criarLista();
    
    // Teste de inserções
    inserirLista(lista, 10);
    inserirLista(lista, 20);
    inserirLista(lista, 30);
    
    exibirLista(lista);
    
    printf("Verificar se a lista está vazia: %s\n", verificarVazia(lista) ? "Sim" : "Não");
    
    // Busca um valor na lista
    Node* encontrado = buscarLista(lista, 20);
    if (encontrado != NULL) {
        printf("Valor %d encontrado na lista.\n", encontrado->valor);
    } else {
        printf("Valor não encontrado.\n");
    }
    
    // Excluir um valor da lista
    excluirLista(lista, 20);
    exibirLista(lista);
    
    // Inserir valores em ordem crescente
    inserirOrdenado(lista, 15);
    inserirOrdenado(lista, 5);
    inserirOrdenado(lista, 25);
    
    exibirLista(lista);
    
    // Liberar a memória antes de sair
    liberarLista(lista);
    return 0;
}
