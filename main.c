#include "mapa.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/*
 * Monta a árvore binária que representa o mapa da mansão:
 *
 *                   Hall de Entrada
 *                  /               \
 *           Biblioteca           Sala de Jantar
 *           /        \             /           \
 *       Porão       Escritório  Cozinha       Jardim
 *                               /
 *                         Despensa
 */
static Sala *montarMansao(void) {
  /* Raiz */
  Sala *hall = criarSala("Hall de Entrada");

  /* Nível 1 */
  Sala *biblioteca = criarSala("Biblioteca");
  Sala *salaJantar = criarSala("Sala de Jantar");

  /* Nível 2 — filhos da Biblioteca */
  Sala *porao = criarSala("Porão");
  Sala *escritorio = criarSala("Escritório");

  /* Nível 2 — filhos da Sala de Jantar */
  Sala *cozinha = criarSala("Cozinha");
  Sala *jardim = criarSala("Jardim");

  /* Nível 3 — filho da Cozinha */
  Sala *despensa = criarSala("Despensa");

  /* Ligações */
  hall->esquerda = biblioteca;
  hall->direita = salaJantar;

  biblioteca->esquerda = porao;
  biblioteca->direita = escritorio;

  salaJantar->esquerda = cozinha;
  salaJantar->direita = jardim;

  cozinha->esquerda = despensa;

  return hall;
}

/* Libera toda a memória alocada para a árvore (pós-ordem) */
static void liberarMansao(Sala *sala) {
  if (sala == NULL)
    return;
  liberarMansao(sala->esquerda);
  liberarMansao(sala->direita);
  free(sala);
}

int main(void) {
  /* Mantém a acentuação correta no terminal */
  SetConsoleOutputCP(65001);
  SetConsoleCP(65001);

  printf("============================================\n");
  printf("       DETECTIVE QUEST - Nivel Novato       \n");
  printf("============================================\n");
  printf("Bem-vindo, detetive! Explore a mansão e\n");
  printf("descubra todos os seus segredos...\n");

  Sala *mansao = montarMansao();

  explorarSalas(mansao);

  liberarMansao(mansao);

  printf("\nPrograma encerrado. Até a próxima investigação!\n");
  return 0;
}
