#define _CRT_SECURE_NO_WARNINGS
#include "emojis.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Função de espalhamento: soma dos valores ASCII mod TAMANHO_HASH */
static int funcaoHash(const char *chave) {
  unsigned int soma = 0;
  for (int i = 0; chave[i] != '\0'; i++)
    soma += (unsigned char)chave[i];
  return (int)(soma % TAMANHO_HASH);
}

void inicializarHash(TabelaHash *th) {
  for (int i = 0; i < TAMANHO_HASH; i++)
    th->tabela[i] = NULL;
}

void inserirNaHash(TabelaHash *th, const char *pista, const char *suspeito) {
  int indice = funcaoHash(pista);

  /* Se a pista já existe, apenas atualiza o suspeito */
  NoHash *atual = th->tabela[indice];
  while (atual != NULL) {
    if (strcmp(atual->pista, pista) == 0) {
      strcpy(atual->suspeito, suspeito);
      return;
    }
    atual = atual->proximo;
  }

  /* Cria novo nó e insere no início da lista (encadeamento) */
  NoHash *novo = (NoHash *)malloc(sizeof(NoHash));
  if (novo == NULL) {
    printf("Erro ao alocar memória para tabela hash.\n");
    exit(1);
  }
  strcpy(novo->pista, pista);
  strcpy(novo->suspeito, suspeito);
  novo->proximo = th->tabela[indice];
  th->tabela[indice] = novo;
}

const char *buscarSuspeito(const TabelaHash *th, const char *pista) {
  int indice = funcaoHash(pista);
  NoHash *atual = th->tabela[indice];
  while (atual != NULL) {
    if (strcmp(atual->pista, pista) == 0)
      return atual->suspeito;
    atual = atual->proximo;
  }
  return NULL;
}

void listarAssociacoes(const TabelaHash *th) {
  printf("  %-34s %s\n", "PISTA", "SUSPEITO");
  printf("  %-34s %s\n", "------------------------------", "----------");
  for (int i = 0; i < TAMANHO_HASH; i++) {
    NoHash *atual = th->tabela[i];
    while (atual != NULL) {
      printf("  %-34s %s %s\n", atual->pista, "→", atual->suspeito);
      atual = atual->proximo;
    }
  }
}

const char *suspeitorMaisCitado(const TabelaHash *th,
                                const char pistas[][100], int nPistas) {
  char nomes[20][50];
  int contagens[20] = {0};
  int nSuspeitos = 0;

  for (int i = 0; i < nPistas; i++) {
    const char *suspeito = buscarSuspeito(th, pistas[i]);
    if (suspeito == NULL)
      continue;

    /* Verifica se suspeito já está na lista de contagem */
    int encontrado = 0;
    for (int j = 0; j < nSuspeitos; j++) {
      if (strcmp(nomes[j], suspeito) == 0) {
        contagens[j]++;
        encontrado = 1;
        break;
      }
    }
    if (!encontrado && nSuspeitos < 20) {
      strcpy(nomes[nSuspeitos], suspeito);
      contagens[nSuspeitos] = 1;
      nSuspeitos++;
    }
  }

  if (nSuspeitos == 0)
    return NULL;

  /* Encontra o maior */
  int maxIdx = 0;
  for (int i = 1; i < nSuspeitos; i++)
    if (contagens[i] > contagens[maxIdx])
      maxIdx = i;

  /* Buffer estático para retornar o nome */
  static char resultado[50];
  strcpy(resultado, nomes[maxIdx]);
  return resultado;
}

void liberarHash(TabelaHash *th) {
  for (int i = 0; i < TAMANHO_HASH; i++) {
    NoHash *atual = th->tabela[i];
    while (atual != NULL) {
      NoHash *prox = atual->proximo;
      free(atual);
      atual = prox;
    }
    th->tabela[i] = NULL;
  }
}
