#ifndef TAMANHO_FIXO.H
#define TAMANHO_FIXO.H

#define TAM_KEY 11
#define TAM_LAST 11    //tamanho do campo last name
#define TAM_FIRST 11   //tamanho do campo first name
#define TAM_ADDRESS 16 //tamanho do campo address
#define TAM_CITY 16    //tamanho do campo city
#define TAM_STATE 3    //tamanho do campo state
#define TAM_ZIP 10     //tamanho do campo zip
#define TAM_PHONE 15
#define TAM_REG TAM_KEY+TAM_LAST+TAM_FIRST+TAM_ADDRESS+TAM_CITY+TAM_STATE+TAM_ZIP+TAM_PHONE

void lerNumeroRegistro(void);

void ler(void);

typedef struct
{
   char key[TAM_KEY]; //verifica se existe um valor dentro do arquivo (usado para garantir que as chaves sejam únicas)
   char last[TAM_LAST];
   char first[TAM_FIRST];
   char address[TAM_ADDRESS];
   char city[TAM_CITY];
   char state[TAM_STATE];
   char zip[TAM_ZIP];
   char phone[TAM_PHONE];
} pessoa;

int existeValor(char *); //verifica se existe um valor dentro do arquivo (usado para garantir que as chaves sejam únicas)
void lerRegistro(pessoa *, char *);  /* Procedimento que transfere para a
estrutura pessoa um registro armazenado no buffer. */

void lerNumeroRegistro(void);

void ler(void);  /*Procedimento que le registros de tamanho fixo com campos de
                   tamanho fixo em um arquivo. */

void lerRegistro(pessoa *, char *);  /* Procedimento que transfere para a
estrutura pessoa um registro armazenado no buffer. */

void lerRegistroAux(char *, char *, int *, int);   //pega um campo do buffer e coloca na estrutura pessoa

void mostrarRegistro(pessoa);   // Mostra o registro na tela.

FILE *obterArquivo(char *);  /*Funcao que abre o arquivo aonde sera feita a
leitura de registros. */

void escrever(void); /*Procedimento que escreve registros de tamanho fixo com
                       campos de tamanho fixo em um arquivo. */
void removerCampo(void);

int recuperarRegistro(char *, FILE *); //recupera um registro do arquivo

int obterRegistro(char *); //obtem dados do teclado e os armazena no buffer de escrita

int obterCampo(char *, int, int);  //obtem um campo da estrutura pessoa e o coloca no buffer

void escreverRegistro(char *, FILE *, FILE *);  //escreve o buffer no arquivo especificado

void pesquisar(void);    //procura por campo no arquivo

int posicaoCampo(int, int[]); //calcula a posicao aonde um determinado campo comeca dentro do registro

int atoi(const char* str); //conversão de string para inteiro, retorna o inteiro



#endif

