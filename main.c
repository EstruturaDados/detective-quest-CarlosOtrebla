#include "mapa.h"
#include "pistas.h"
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
 * Salas com pista: Biblioteca, Escritorio, Cozinha, Despensa
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
  printf("  DETECTIVE QUEST - Nível Aventureiro\n");
  printf("============================================\n");
  printf("%s Bem-vindo, detetive! Explore a mansão,\n", EMOJI_DETETIVE);
  printf("colete pistas e resolva o mistério...\n");

  Sala *mansao = montarMansao();
  NoPista *bstPistas = NULL;

  /* Exploração: coleta pistas somente das salas visitadas */
  bstPistas = explorarSalas(mansao, bstPistas);

  /* Exibe o resumo das pistas em ordem alfabetica */
  printf("\n============================================\n");
  printf("   %s EVIDÊNCIAS COLETADAS                  \n", EMOJI_PERGAMINHO);
  printf("============================================\n");
  printf("%s Pistas registradas em ordem alfabética:\n", EMOJI_LUPA);
  listarPistas(bstPistas);

  /* Menu de busca de pista */
  char busca[100];
  char resposta;
  printf("\nDeseja buscar uma pista específica? (s/n): ");
  do { resposta = (char)getchar(); } while (resposta == '\n' || resposta == '\r');

  while (resposta == 's' || resposta == 'S') {
    /* Limpa buffer antes de ler a pista */
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("Digite a pista que deseja buscar: ");
    fgets(busca, sizeof(busca), stdin);
    /* Remove o '\n' do fgets */
    busca[strcspn(busca, "\n")] = '\0';

    NoPista *resultado = buscarPista(bstPistas, busca);
    if (resultado != NULL)
      printf("%s Pista encontrada: \"%s\"\n", EMOJI_CHAVE, resultado->texto);
    else
      printf("%s Pista \"%s\" não foi coletada nesta exploração.\n", EMOJI_AVISO, busca);

    printf("\nBuscar outra pista? (s/n): ");
    do { resposta = (char)getchar(); } while (resposta == '\n' || resposta == '\r');
  }

  liberarMansao(mansao);
  liberarPistas(bstPistas);

  printf("\n%s Investigação encerrada. Até a próxima!\n", EMOJI_ALVO);

  /* Esvazia qualquer caractere residual no buffer antes de pausar */
  int c;
  while ((c = getchar()) != '\n' && c != EOF);

  printf("\nPressione ENTER para fechar...\n");
  getchar();
  return 0;
}

