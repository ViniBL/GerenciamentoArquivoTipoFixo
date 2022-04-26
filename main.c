#include <locale.h>
#include <stdio.h>

#include <string.h>
#include <stdlib.h>

#include "fixo.c"

/*
Aquila Oliveira
Victor Andrade Louren�o Marques
Vin�cius Borges de Lima
*/

int main(void)
{
   setlocale(LC_ALL, "Portuguese");
   int opcao;

   printf("IMPLEMENTA��O USANDO REGISTROS DE TAMANHO FIXO COM CAMPOS DE"
          " TAMANHO FIXO:\n\n");

    /*op��o 1: Todos os registros s�o mostrados
     op��o 2: O registro na posi��o informada � msotrado
     op��o 3: Inserir no arquivo
     op��o 4: Pesquisar um registro pela chave
     op��o 5: Pesquisar um registro pelo firstName
     op��o 6: Remover um registro
     op��o 7: sair
     */

   printf("\t1 - Ler todos os registros\n\t2 - Ler o registro da posic�o desejada\n\t3 - Escrever\n\t4 - Pesquisar por chave\n\t5 - Pesquisar por nome\n\t6 - Remover registro KEY\n\n");
   printf("Digite a Op��o (7 para terminar): ");
   scanf("%d",&opcao);
   putchar('\n');
   while(opcao != 7)
   {
      switch(opcao)
      {
         case 1:  ler();
                    break;
         case 2:  lerNumeroRegistro();
                    break;
         case 3:  escrever();
                    break;
         case 4:  pesquisarChave();
                    break;
         case 5:  pesquisarNome();
                    break;
         case 6:  removerCampo();
                    break;
         default:   printf("Op��o Inv�lida! Digite Novamente.\n");
                    break;
      }

      printf("\t1 - Ler todos os registros\n\t2 - Ler o registro da posic�o desejada\n\t3 - Escrever\n\t4 - Pesquisar por chave\n\t5 - Pesquisar por nome\n\t6 - Remover registro KEY\n\n");
      printf("Digite a Op��o (7 para terminar): ");
      fflush(stdin);
      scanf("%d",&opcao);
      putchar('\n');
   }

   return 0;
}



