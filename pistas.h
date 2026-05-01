#ifndef PISTAS_H
#define PISTAS_H

/* Nó da árvore de busca (BST) de pistas */
typedef struct NoPista {
  char texto[100];
  struct NoPista *esquerda;
  struct NoPista *direita;
} NoPista;

/* Insere uma pista na BST (em ordem alfabética) */
NoPista *inserirPista(NoPista *raiz, const char *texto);

/* Busca uma pista na BST; retorna o nó se encontrado, NULL se não */
NoPista *buscarPista(NoPista *raiz, const char *texto);

/* Exibe todas as pistas em ordem alfabética (in-order) */
void listarPistas(NoPista *raiz);

/* Libera toda a memória da BST */
void liberarPistas(NoPista *raiz);

#endif
