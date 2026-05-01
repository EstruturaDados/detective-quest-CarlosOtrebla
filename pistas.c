#define _CRT_SECURE_NO_WARNINGS
#include "emojis.h"
#include "pistas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

NoPista *inserirPista(NoPista *raiz, const char *texto) {
  /* Aloca novo nó */
  if (raiz == NULL) {
    NoPista *novo = (NoPista *)malloc(sizeof(NoPista));
    if (novo == NULL) {
      printf("Erro ao alocar memoria para pista.\n");
      exit(1);
    }
    strcpy(novo->texto, texto);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
  }

  int cmp = strcmp(texto, raiz->texto);

  if (cmp < 0)
    raiz->esquerda = inserirPista(raiz->esquerda, texto);
  else if (cmp > 0)
    raiz->direita = inserirPista(raiz->direita, texto);
  /* Se igual, pista duplicada — ignora */

  return raiz;
}

NoPista *buscarPista(NoPista *raiz, const char *texto) {
  if (raiz == NULL)
    return NULL; /* pista não encontrada */

  int cmp = strcmp(texto, raiz->texto);

  if (cmp == 0)
    return raiz;           /* encontrou */
  else if (cmp < 0)
    return buscarPista(raiz->esquerda, texto); /* busca à esquerda */
  else
    return buscarPista(raiz->direita, texto);  /* busca à direita */
}

void listarPistas(NoPista *raiz) {
  if (raiz == NULL)
    return;
  listarPistas(raiz->esquerda);
  printf("%s %s\n", EMOJI_LUPA, raiz->texto);
  listarPistas(raiz->direita);
}

void liberarPistas(NoPista *raiz) {
  if (raiz == NULL)
    return;
  liberarPistas(raiz->esquerda);
  liberarPistas(raiz->direita);
  free(raiz);
}
