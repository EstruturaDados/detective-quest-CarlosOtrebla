#include "mapa.h"
#include "pistas.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "emojis.h"

/*
 * Monta a arvore binaria que representa o mapa da mansao:
 *
 *                   Hall de Entrada
 *                  /               \
 *           Biblioteca           Sala de Jantar
 *           /        \             /           \
 *       Porao       Escritorio  Cozinha       Jardim
 *                               /
 *                         Despensa
 *
 * Salas com pista: Biblioteca, Escritório, Cozinha, Despensa
 */
Sala *montarMansao() {
  Sala *hall = criarSala("Hall de Entrada", "");

  Sala *biblioteca = criarSala("Biblioteca", "Livro com páginas arrancadas");
  Sala *salaJantar = criarSala("Sala de Jantar", "");

  Sala *porao = criarSala("Porão", "");
  Sala *escritorio = criarSala("Escritório", "Carta anônima na gaveta");

  Sala *cozinha = criarSala("Cozinha", "Veneno no armário");
  Sala *jardim = criarSala("Jardim", "");

  Sala *despensa = criarSala("Despensa", "Pegadas de barro no chão");

  hall->esquerda = biblioteca;
  hall->direita = salaJantar;

  biblioteca->esquerda = porao;
  biblioteca->direita = escritorio;

  salaJantar->esquerda = cozinha;
  salaJantar->direita = jardim;

  cozinha->esquerda = despensa;

  return hall;
}

/* Popula a tabela hash com todas as relações pista → suspeito */
void popularHash(TabelaHash *th) {
  inserirNaHash(th, "Livro com páginas arrancadas", "Coronel Mustard");
  inserirNaHash(th, "Carta anônima na gaveta",      "Srta. Scarlett");
  inserirNaHash(th, "Veneno no armário",             "Srta. Scarlett"); /* Duas pistas apontam para ela! */
  inserirNaHash(th, "Pegadas de barro no chão",      "Sra. White");
}

/* Coleta pistas da BST em array (percurso in-order) */
static void coletarEmArray(NoPista *raiz, char arr[][100], int *idx) {
  if (raiz == NULL)
    return;
  coletarEmArray(raiz->esquerda, arr, idx);
  strcpy(arr[(*idx)++], raiz->texto);
  coletarEmArray(raiz->direita, arr, idx);
}

/* Conta nós na BST */
static int contarNos(NoPista *raiz) {
  if (raiz == NULL)
    return 0;
  return 1 + contarNos(raiz->esquerda) + contarNos(raiz->direita);
}

void liberarMansao(Sala *sala) {
  if (sala == NULL)
    return;
  liberarMansao(sala->esquerda);
  liberarMansao(sala->direita);
  free(sala);
}

int main() {
  SetConsoleOutputCP(65001);
  SetConsoleCP(65001);

  printf("============================================\n");
  printf("    DETECTIVE QUEST - Nível Mestre\n");
  printf("============================================\n");
  printf("%s Bem-vindo, detetive! Explore a mansão,\n", EMOJI_DETETIVE);
  printf("colete pistas e descubra o culpado!\n");

  /* ── Nível Aventureiro: mapa + BST de pistas ── */
  Sala *mansao = montarMansao();
  NoPista *bstPistas = NULL;

  char continuarExplorando;
  do {
    bstPistas = explorarSalas(mansao, bstPistas);
    
    printf("\n%s Deseja explorar a mansão novamente a partir do Hall de Entrada? (s/n): ", EMOJI_PENSANDO);
    do { continuarExplorando = (char)getchar(); } while (continuarExplorando == '\n' || continuarExplorando == '\r' || continuarExplorando == ' ');
  } while (continuarExplorando == 's' || continuarExplorando == 'S');

  printf("\n============================================\n");
  printf("   %s EVIDÊNCIAS COLETADAS\n", EMOJI_PERGAMINHO);
  printf("============================================\n");
  printf("%s Pistas em ordem alfabética:\n", EMOJI_LUPA);
  listarPistas(bstPistas);

  /* Busca na BST (Nível Aventureiro) */
  char busca[100];
  char resposta;
  printf("\nDeseja buscar uma pista específica? (s/n): ");
  do { resposta = (char)getchar(); } while (resposta == '\n' || resposta == '\r');

  while (resposta == 's' || resposta == 'S') {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("Digite a pista que deseja buscar: ");
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = '\0';

    NoPista *resultado = buscarPista(bstPistas, busca);
    if (resultado != NULL)
      printf("%s Pista encontrada: \"%s\"\n", EMOJI_CHAVE, resultado->texto);
    else
      printf("%s Pista \"%s\" não foi coletada nesta exploração.\n", EMOJI_AVISO, busca);

    printf("\nBuscar outra pista? (s/n): ");
    do { resposta = (char)getchar(); } while (resposta == '\n' || resposta == '\r');
  }

  /* ── Nível Mestre: tabela hash de suspeitos ── */
  TabelaHash hash;
  inicializarHash(&hash);
  popularHash(&hash);

  /* Coleta pistas do BST em array para análise */
  int nPistas = contarNos(bstPistas);
  char pistasArr[20][100];
  int idx = 0;
  coletarEmArray(bstPistas, pistasArr, &idx);

  printf("\n============================================\n");
  printf("   %s ANÁLISE DE SUSPEITOS\n", EMOJI_DETETIVE);
  printf("============================================\n");

  if (nPistas == 0) {
    printf("%s Nenhuma pista foi coletada. Sem suspeitos!\n", EMOJI_AVISO);
  } else {
    /* Mostra pista → suspeito para cada pista coletada */
    printf("Pistas coletadas e seus suspeitos:\n");
    for (int i = 0; i < nPistas; i++) {
      const char *suspeito = buscarSuspeito(&hash, pistasArr[i]);
      if (suspeito)
        printf("  %s \"%s\"  %s  %s\n",
               EMOJI_CHAVE, pistasArr[i], "→", suspeito);
    }

    /* Suspeito mais citado */
    const char *culpado = suspeitorMaisCitado(&hash, pistasArr, nPistas);
    if (culpado) {
      printf("\n============================================\n");
      printf("   %s VEREDITO FINAL\n", EMOJI_ALVO);
      printf("============================================\n");
      printf("Com base nas evidências, o culpado é:\n\n");
      printf("  >>> %s <<<\n\n", culpado);
    }
  }

  /* Exibe todas as associações cadastradas na hash */
  printf("============================================\n");
  printf("   %s TODAS AS ASSOCIAÇÕES (hash)\n", EMOJI_PERGAMINHO);
  printf("============================================\n");
  listarAssociacoes(&hash);

  liberarHash(&hash);
  liberarMansao(mansao);
  liberarPistas(bstPistas);

  printf("\n%s Investigação encerrada. Até a próxima!\n", EMOJI_ALVO);

  int c;
  while ((c = getchar()) != '\n' && c != EOF);

  printf("\nPressione ENTER para fechar...\n");
  getchar();
  return 0;
}
