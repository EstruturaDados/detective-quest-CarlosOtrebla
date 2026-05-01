#define _CRT_SECURE_NO_WARNINGS
#include "mapa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Sala *criarSala(char *nome) {
  Sala *nova = (Sala *)malloc(sizeof(Sala));
  if (nova == NULL) {
    printf("Erro ao alocar memória\n");
    exit(1);
  }
  strcpy(nova->nome, nome);
  nova->esquerda = NULL;
  nova->direita = NULL;
  return nova;
}

void explorarSalas(Sala *raiz) {
  if (raiz == NULL) {
    printf("\nMansão vazia — nenhuma sala para explorar.\n");
    return;
  }

  Sala *salaAtual = raiz;
  char opcao;

  while (salaAtual != NULL) {
    printf("\n========================================\n");
    printf("  🔍  Você está em: %s\n", salaAtual->nome);
    printf("========================================\n");

    /* Verifica se é nó-folha (fim do caminho) */
    int temEsquerda = (salaAtual->esquerda != NULL);
    int temDireita = (salaAtual->direita != NULL);

    if (!temEsquerda && !temDireita) {
      printf("  [Fim do caminho — não há mais salas nesta direção.]\n");
      break;
    }

    printf("Para onde deseja ir?\n");
    if (temEsquerda)
      printf("  e → Esquerda (%s)\n", salaAtual->esquerda->nome);
    if (temDireita)
      printf("  d → Direita  (%s)\n", salaAtual->direita->nome);
    printf("  s → Sair da exploração\n");
    printf("Opção: ");

    /* Descarta espaços/quebras de linha residuais antes de ler */
    do {
      opcao = (char)getchar();
    } while (opcao == '\n' || opcao == '\r' || opcao == ' ');

    if (opcao == 's' || opcao == 'S') {
      printf("\nVocê decidiu encerrar a exploração. Até a próxima!\n");
      break;
    } else if ((opcao == 'e' || opcao == 'E') && temEsquerda) {
      salaAtual = salaAtual->esquerda;
    } else if ((opcao == 'd' || opcao == 'D') && temDireita) {
      salaAtual = salaAtual->direita;
    } else {
      printf("  ⚠️  Opção inválida ou caminho inexistente. Tente novamente.\n");
    }
  }
}