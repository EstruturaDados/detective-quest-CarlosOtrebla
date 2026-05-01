#ifndef HASH_H
#define HASH_H

#define TAMANHO_HASH 11

/* Nó da lista encadeada — trata colisões por encadeamento.
 *
 * NOTA DE DESIGN (Nível Mestre): 
 * O roteiro original sugeria "struct Suspeito contendo nome e lista de pistas associadas".
 * Optei por inverter a lógica (Pista → Suspeito) visando O(1) na busca real do jogo.
 * Em um cenário onde a chave fosse o "Suspeito", toda vez que o detetive encontrasse
 * uma pista na mansão, o algoritmo teria que varrer todas as listas de todos os suspeitos
 * na tabela Hash para descobrir a quem a pista pertencia (complexidade O(n)).
 * Mapeando Pista como chave, temos acesso direto (O(1)) ao suspeito dono daquela evidência.
 */
typedef struct NoHash {
  char pista[100];
  char suspeito[50];
  struct NoHash *proximo;
} NoHash;

/* Tabela hash: array de ponteiros para listas encadeadas */
typedef struct {
  NoHash *tabela[TAMANHO_HASH];
} TabelaHash;

/* Inicializa todos os buckets como NULL */
void inicializarHash(TabelaHash *th);

/* Insere ou atualiza a relação pista → suspeito */
void inserirNaHash(TabelaHash *th, const char *pista, const char *suspeito);

/* Retorna o nome do suspeito associado à pista, ou NULL se não existir */
const char *buscarSuspeito(const TabelaHash *th, const char *pista);

/* Exibe todas as relações pista → suspeito cadastradas */
void listarAssociacoes(const TabelaHash *th);

/* Retorna o suspeito mais citado entre as pistas passadas */
const char *suspeitorMaisCitado(const TabelaHash *th,
                                const char pistas[][100], int nPistas);

/* Libera toda a memória da tabela */
void liberarHash(TabelaHash *th);

#endif
