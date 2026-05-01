#ifndef MAPA_H
#define MAPA_H

typedef struct Sala {
  char nome[50];
  struct Sala *esquerda;
  struct Sala *direita;
} Sala;

Sala *criarSala(char *nome);
void explorarSalas(Sala *raiz);

#endif