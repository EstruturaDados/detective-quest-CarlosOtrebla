#ifndef MAPA_H
#define MAPA_H

#include "pistas.h"

typedef struct Sala {
  char nome[50];
  char pista[100]; /* pista encontrada nesta sala; "" se nao houver */
  struct Sala *esquerda;
  struct Sala *direita;
} Sala;

Sala *criarSala(const char *nome, const char *pista);
NoPista *explorarSalas(Sala *raiz, NoPista *bst);

#endif