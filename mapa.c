#include "emojis.h"
#define _CRT_SECURE_NO_WARNINGS
#include "mapa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Sala *criarSala(const char *nome, const char *pista) {
  Sala *nova = (Sala *)malloc(sizeof(Sala));
  if (nova == NULL) {
    printf("Erro ao alocar memória.\n");
    exit(1);
  }
  strcpy(nova->nome, nome);
  strcpy(nova->pista, pista != NULL ? pista : "");
  nova->esquerda = NULL;
  nova->direita = NULL;
  return nova;
}

NoPista *explorarSalas(Sala *raiz, NoPista *bst) {
  if (raiz == NULL) {
    printf("\nMansão vazia — nenhuma sala para explorar.\n");
    return bst;
  }

  Sala *salaAtual = raiz;
  char opcao;

  while (salaAtual != NULL) {
    printf("\n========================================\n");
    printf("  %s Você está em: %s\n", EMOJI_MANSAO, salaAtual->nome);
    printf("========================================\n");

    /* Coleta pista da sala atual na BST (somente salas visitadas) */
    if (salaAtual->pista[0] != '\0') {
      bst = inserirPista(bst, salaAtual->pista);
      printf("  %s [Pista encontrada!]: \"%s\"\n", EMOJI_CHAVE, salaAtual->pista);
    }

    int temEsquerda = (salaAtual->esquerda != NULL);
    int temDireita = (salaAtual->direita != NULL);

    if (!temEsquerda && !temDireita) {
      printf("  %s [Fim do caminho — não há mais salas nesta direção.]\n", EMOJI_BLOQUEADO);
      break;
    }

    printf("Para onde deseja ir?\n");
    if (temEsquerda)
      printf("  e → %s Esquerda (%s)\n", EMOJI_ESQUERDA, salaAtual->esquerda->nome);
    if (temDireita)
      printf("  d → %s Direita  (%s)\n", EMOJI_DIREITA, salaAtual->direita->nome);
    printf("  s → %sSair da exploração\n", EMOJI_PORTA);
    printf("Opção: ");

    /* Descarta espaços/quebras de linha residuais antes de ler */
    do {
      opcao = (char)getchar();
    } while (opcao == '\n' || opcao == '\r' || opcao == ' ');

    if (opcao == 's' || opcao == 'S') {
      printf("\n%s Você decidiu encerrar a exploração. Até a próxima!\n", EMOJI_TCHAU);
      break;
    } else if ((opcao == 'e' || opcao == 'E') && temEsquerda) {
      salaAtual = salaAtual->esquerda;
    } else if ((opcao == 'd' || opcao == 'D') && temDireita) {
      salaAtual = salaAtual->direita;
    } else {
      printf("  %s Opção inválida ou caminho inexistente. Tente novamente.\n", EMOJI_AVISO);
    }
  }

  return bst;
}