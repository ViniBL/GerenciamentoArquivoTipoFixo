#include "fixo.h"

int existeValor(char *Chave) //comando respons�vel para verificar se existe uma chave com o valor Chave no arquivo.
{
    //adicionando espa�os adicionais
    char *espacoAdic;
    int i;
    int tamanho = strlen(Chave);
    espacoAdic = (char *) malloc(11 - strlen(Chave) + 1);
    for( i = 0; i < 11 - strlen(Chave); i++)
    {
       espacoAdic[i] = '*';
    }
    espacoAdic[11] = '\0';

    strcat(Chave, espacoAdic);

    FILE *arquivo;
    char buffer[TAM_REG];
    int posicao;
    // abrindo arquivo no modo read write com bin�rio
    arquivo = obterArquivo("rb+");
    //enquanto ele continuar lendo caracteres no arquivo, � para continuar
    while(fread(buffer,TAM_REG,1,arquivo))
    {
        char bufferChave[12];
        for(int i =0;i<TAM_KEY;i++)
        {
            //atribuindo o valor da chave do buffer para o buffer tempor�rio "bufferChave"
            bufferChave[i] = buffer[i];
        }
            //se o bufferChave for igual ao valor procurado, deve-se encerrar a fun��o com return 1
        if(strcmp(bufferChave,Chave)==0)
        {
            Chave[tamanho] = '\0'; //indica onde o buffer deve terminar (por causa dos espa�os adicionais que foram inseridos)
            fseek(arquivo, -(TAM_REG), SEEK_CUR);
            posicao = ftell(arquivo);
            return posicao;// Retorna a posicao da chave
        }

    }

    Chave[tamanho] = '\0';

    return -1;
}

void lerNumeroRegistro(void){
   pessoa umaPessoa; //cria��o do struct "umaPessoa"

   FILE *arquivo;
   char buffer[TAM_REG];


   arquivo = obterArquivo("rb"); //abre o arquivo no modo read binario

   int posicao;
   printf("Qual registro deseja ler?\n");
   scanf("%d", &posicao);


   if(recuperarRegistroPosicao(buffer, arquivo, posicao)){
       fflush(stdin);
       lerRegistro(&umaPessoa, buffer); //os dados s�o transferidos para o struct umaPessoa
       mostrarRegistro(umaPessoa); //mostra na tela o registro
       getchar(); //exige um caractere para ir para o pr�ximo registro
   }
   else printf("Registro com essa posicao nao existe.\n");

   putchar('\n');
   fclose(arquivo);
}

void ler(void)
{
   pessoa umaPessoa;  //cria��o do struct
   FILE *arquivo;
   char buffer[TAM_REG];

   arquivo = obterArquivo("rb");

   //enquanto houver caracteres para serem lidos no arquivo
   while(recuperarRegistro(buffer, arquivo))  //leitura de um registro (do tamanho TAMREG)
   {
   	  fflush(stdin); //
      lerRegistro(&umaPessoa, buffer);    //transfere os dados do buffer para a estrutura pessoa
      mostrarRegistro(umaPessoa);          //mostrar Registro na Tela
      getchar();
   }//while

   putchar('\n');
   fclose(arquivo);
}

int recuperarRegistroPosicao(char *buffer, FILE *arquivo, int pos)
{
   int tamReg = TAM_REG;
   int resultado = fseek(arquivo, tamReg*pos, SEEK_SET);
   return fread(buffer, TAM_REG, 1, arquivo);  //retorna a posi��o do registro procurado
}
int recuperarRegistro(char *buffer, FILE *arquivo)
{
   return fread(buffer, TAM_REG, 1, arquivo);  //lendo registro do arquivo para buffer
}

void lerRegistro(pessoa *umaPessoa, char *buffer)
{
   int inicioCampo = 0;  //o in�cio do campo sempre ser� na posi��o 0

   //em cada uma das entradas no lerRegistroAux, ser� atribuido o valor do respectivo campo procurado para o campo do struct pessoa
   lerRegistroAux(umaPessoa->key, buffer, &inicioCampo, TAM_KEY);

   lerRegistroAux(umaPessoa->last, buffer, &inicioCampo, TAM_LAST);

   lerRegistroAux(umaPessoa->first, buffer, &inicioCampo, TAM_FIRST);

   lerRegistroAux(umaPessoa->address, buffer, &inicioCampo, TAM_ADDRESS);

   lerRegistroAux(umaPessoa->city, buffer, &inicioCampo, TAM_CITY);

   lerRegistroAux(umaPessoa->state, buffer, &inicioCampo, TAM_STATE);

   lerRegistroAux(umaPessoa->zip, buffer, &inicioCampo, TAM_ZIP);

   lerRegistroAux(umaPessoa->phone, buffer, &inicioCampo, TAM_PHONE);
}

void lerRegistroAux(char *campo, char *buffer, int *inicioCampo, int tamanho)
{
   strncpy(campo, &buffer[*inicioCampo], tamanho);  //o campo � lido
   campo[tamanho - 1] = '\0';  //o caractere "\0" � colocado para indicar o fim da string
   *inicioCampo += tamanho; //o inicio campo � atualizado, para que na pr�xima chamada do lerRegistroAux o m�todo comece no inicioCampo correto.
}

void mostrarCampo(char *campo, char nomeCampo[20])
{
    //m�todo que imprime o valor do campo at� achar o caractere "*", caractere esse que representa um espa�o vazio. Essa fun��o existe para que n�o seja imprimido v�rios "*" no final de cada print
    printf("\n Campo %s: ",nomeCampo);
    for (int i=0;i<strlen(campo);i++)
    {
        if(campo[i] != '*')
        {
            printf("%c",campo[i]);
        }
        else
        {
            break; //caso o caractere seja igual a "*", a fun��o ir� acabar
        }
    }
}


void mostrarRegistro(pessoa umaPessoa)
{
   //essa fun��o ir� imprimir todos os campos do struct pessoa, ir� chamar a fun��o "mostrarCampo" para os "*" n�o serem printados
   printf("Registro:\n");
   mostrarCampo(umaPessoa.key,"Chave");
   mostrarCampo(umaPessoa.last,"Ultimo Nome");
   mostrarCampo(umaPessoa.first,"Primeiro nome");
   mostrarCampo(umaPessoa.address,"Endere�o");
   mostrarCampo(umaPessoa.city,"Cidade");
   mostrarCampo(umaPessoa.state,"Estado");
   mostrarCampo(umaPessoa.zip,"CEP");
   mostrarCampo(umaPessoa.phone,"Telefone");
   printf("\n");
}

FILE *obterArquivo(char *modoAbertura)
{
   //fun��o respons�vel por abrir o arquivo no modo passado no par�metro "modo Abertura", o arquivo aberto ser� o arquivo "arquivo"
   FILE * arquivo;

   arquivo = fopen("Arquivo", modoAbertura);  //abre o arquivo "Arquivo" com o modo de aberta especificado

   return arquivo;    //retornando o arquivo aberto
}

FILE *obterArquivoAux(char *modoAbertura)
{
   FILE * arquivoAux;

   arquivoAux = fopen("ArquivoAux", modoAbertura);  //abrindo arquivo especificado por pathname

   return arquivoAux;    //retornando o arquivo aberto
}

void escrever(void)
{
   FILE * arquivo;    //arquivo onde serao escritos os registros
   FILE * arquivoAux;
   int continua;     // indica se continua ou nao a escrever registros
   char buffer[TAM_REG] = "\0";  //buffer utilizado para escrevermos registros no arquivo

   int i;


   arquivo = obterArquivo("ab");   //abrindo arquivo para escrita no fim do arquivo (append)
   arquivoAux = obterArquivoAux("ab");

   if(NULL == arquivo)   //usuario deseja sair
   {
      return;
   }//if

   printf("1 - Escrever Registro\tOutra - Sair\n");
   scanf("%d",&continua);    //obter resposta do teclado
   putchar('\n');         //pula uma linha


    fclose(arquivo);
    fclose(arquivoAux);

   while (1 == continua)  //enquanto tiver registro a escrever...
   {
      arquivo = obterArquivo("ab");   //abrindo arquivo para escrita no fim do arquivo (append)
      arquivoAux = obterArquivoAux("ab");

      if(obterRegistro(buffer) == -1)
      {
        fclose(arquivo);
        fclose(arquivoAux);
          return;
      }   //obter registro para escrever no arquivo
      escreverRegistro(buffer, arquivo, arquivoAux);  //escrever registro no arquivo
      printf("1 - Escrever Registro\tOutra - Sair\n");
      scanf("%d",&continua);    //obter resposta do teclado
      putchar('\n');         //pula uma linha

     fclose(arquivo);
     fclose(arquivoAux);
   }//while




}//escrever

int obterRegistro(char *buffer)
{
    //as chamadas do m�todo "obterCampo", o obterCampo � respons�vel por receber a entrada do usu�rio, e retornar no buffer

   printf("Digite a Chave/CPF: ");
   if(obterCampo(buffer, TAM_KEY, 1) == -1) //essa condi��o s� ser� true caso a chave n�o ser  �nica
   {
       return -1;
   }

   printf("Digite o �ltimo Nome: ");
   obterCampo(buffer, TAM_LAST, 0);

   printf("Digite o Primeiro Nome: ");
   obterCampo(buffer, TAM_FIRST, 0);

   printf("Digite o Endere�o: ");
   obterCampo(buffer, TAM_ADDRESS, 0);

   printf("Digite a Cidade: ");
   obterCampo(buffer, TAM_CITY, 0);

   printf("Digite o Estado: ");
   obterCampo(buffer, TAM_STATE, 0);

   printf("Digite o CEP: ");
   obterCampo(buffer, TAM_ZIP, 0);

   printf("Digite o telefone: ");
   obterCampo(buffer, TAM_PHONE, 0);

   putchar('\n');    //pula uma linha
}//obterRegistro


void removerCampo(void)
{
        //c�digo respons�vel pela remo��o de um registro

    char Chave[TAM_KEY+1];
    printf("Escolha a chave do registro que voc� deseja remover: ");
    scanf("%s",Chave);
    char *espacoAdic;
    int i;

    espacoAdic = (char *) malloc(11 - strlen(Chave) + 1);
     /*ser�o adicionados caracteres ("*") adicionais no input do usu�rio, pois como o registro � de tamanho fixo, caso a chave n�o ocupe todo o tamanho dispon�vel,
    diversos "*" s�o adicionados para representar que o resto do campo est� vazio.*/

    for( i = 0; i < 11 - strlen(Chave); i++)
    {
       espacoAdic[i] = '*';
    }
    espacoAdic[11] = '\0';
  //concatena o input do usu�rio com os espa�os adicionais
    strcat(Chave, espacoAdic);


    FILE *arquivoAux;
    FILE *arquivo;
    char buffer[TAM_REG];
    arquivo = obterArquivo("rb+");
    arquivoAux = obterArquivoAux("rb+");
    char posicao[10];
    char registro[20];
    int posicaoRemovida;
    int converterAux;

    while(fread(buffer,TAM_REG,1,arquivo)) //enquanto houver registros para serem lidos
    {
        char bufferChave[12];
        for(int i =0;i<11;i++)
        {
            bufferChave[i] = buffer[i];  //o bufferChave receber� os 12 primeiros caracteres do buffer, sendo esses os caracteres reservados para a Chave
        }

        if(strcmp(bufferChave,Chave)==0) //se o BufferChave for igual ao input do usu�rio (Chave), o registro inteiro ser� substituido pelo caractere "#"
        {
            fseek(arquivo, -(TAM_REG), SEEK_CUR);  //esse fseek ir� colocar o ponteiro do arquivo para o seu in�cio, para ent�o poder modifica-lo.
            posicaoRemovida = ftell(arquivo); //armazena a posi��o do arquivo

              //o caractere ser� inserido TAM_REG vezes, representando um espa�o vazio no registro
            for (int i=0;i<TAM_REG;i++)
            {
                fputc('#', arquivo);
                fseek(arquivo, 0, SEEK_CUR);
            }
             //o registro tamb�m ser� removido no auxiliar

            converterAux = posicaoRemovida / (TAM_REG);
            fseek(arquivoAux, converterAux * 20, SEEK_CUR);

            for (int i=0;i<20;i++)
            {
                fputc('#', arquivoAux);
                fseek(arquivoAux, 0, SEEK_CUR);
            }

         }

    }


    fclose(arquivoAux);
    fclose(arquivo);


}
int obterCampo(char *buffer, int tamanho,int flag)
{
    //m�todo respons�vel por obter os campos do usu�rio, e retornar seu valor para o buffer

   char bufferAux[TAM_REG];
   char *espacoAdic;
   int i;

   fflush(stdin);
   scanf("%s",bufferAux);   //entrada de dados
   strcat(buffer, bufferAux);  //os dados ser�o adicionados no fim do buffer
   if(flag == 1)
   {
       if(existeValor(buffer)>=0)  /*caso a flag passada seja igual a 1, o m�todo ir� invocar o m�todo existeValor, que ir� certificar se o valor passado � �nico,
       caso n�o for, ele ir� retornar -1, para o programa ser impedido de continuar*/
       {
           printf("\nChave j� cadastrada! Tente novamente.\n");
           return -1;
       }
   }
   //caractere adicionais s�o inseridos no fim do buffer se necess�rio

   espacoAdic = (char *) malloc(tamanho - strlen(bufferAux) + 1);

   for(i = 0; i < tamanho - strlen(bufferAux); i++)
   {
      espacoAdic[i] = '*';
   }//for
   espacoAdic[i] = '\0';

   strcat(buffer, espacoAdic);
}//obterCampo

void escreverRegistro(char *buffer, FILE *arquivo, FILE *arquivoAux)
{
    fseek(arquivo, 0, SEEK_END); // Size ser� usado na hora de se inserir no arquivo auxiliar de busca
    int size = ftell(arquivo); // A posi��o do arquivo antes da adi��o da pessoa ao arquivo
    fseek(arquivo, 0, SEEK_SET);
    char size_c[9];



    // Inser��o no arquivo de dados
    fclose(arquivo);
    arquivo = obterArquivo("rb");
    int flag;//Caso a flag for 0 quer dizer que ser� reaproveitado a memoria do arquivo e o arquivo auxiliar ir� adicionar a posicao que est� no arquivo de dados correta.

    char bufferAux[TAM_REG];

    int posicaoInserirAux;
    fseek(arquivo, 0, SEEK_END);
    int posicaoInserir = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    while(fread(bufferAux, TAM_REG, 1, arquivo)){
        if(bufferAux[0] == '#'){
            fseek(arquivo, -(TAM_REG), SEEK_CUR);
            posicaoInserir = ftell(arquivo);
            posicaoInserirAux = posicaoInserir;
            flag = 0;
            break;
        }
    }
    fclose(arquivo);
    arquivo = obterArquivo("r+b");

    fseek(arquivo, posicaoInserir, 0);
    fwrite(buffer, TAM_REG, 1, arquivo);

    //Escrever no arquivo auxiliar de busca
    int i;
    char *espacoAdic;
    char bufferArquivoAux[20];
    char firstName[TAM_FIRST];
    fclose(arquivoAux);
    arquivoAux = obterArquivoAux("rb");

    fseek(arquivoAux, 0, SEEK_END);
    posicaoInserir = ftell(arquivoAux);
    fseek(arquivoAux, 0, SEEK_SET);


    while(fread(bufferArquivoAux, 20, 1, arquivoAux)){
        if(bufferArquivoAux[0] == '#'){
            fseek(arquivoAux, -(20), SEEK_CUR);
            posicaoInserir = ftell(arquivoAux);
            break;
        }
    }

    for(i=0; i<TAM_FIRST && buffer[i+22]!= '*';i++){
        firstName[i] = buffer[i+22];
    }

    espacoAdic = (char *) malloc(TAM_FIRST - strlen(firstName) + 1);

    for(i = 0; i < TAM_FIRST - strlen(firstName); i++)
    {
        espacoAdic[i] = '*';
    }//for
    espacoAdic[i] = '\0';

    strcat(firstName, espacoAdic);

    fclose(arquivoAux);
    arquivoAux = obterArquivoAux("r+b");

    if(flag == 0){
        size = posicaoInserirAux;
    }
    itoa(size, size_c, 10);
    fseek(arquivoAux, posicaoInserir, 0);

    fwrite(firstName, TAM_FIRST, 1, arquivoAux);

    //Espa�o adicional para a posi��o
    espacoAdic = (char *) realloc(espacoAdic, 9 - strlen(size_c) + 1 );

    for(i = 0; i < 9 - strlen(size_c); i++)
    {
        espacoAdic[i] = '*';
    }//for

    espacoAdic[i] = '\0';

    strcat(size_c, espacoAdic);

    //escrevendo o buffer no arquivo
    fwrite(size_c, 9 , 1, arquivoAux);


    buffer[0] = '\0';  //preparando buffer para armazenar o proximo registro

}//escreverRegistro

void pesquisarChave(void)
{
   pessoa umaPessoa;

   FILE * arquivo;      //arquivo onde deseja-se fazer a pesquisa
   int posicao = 0;         //armazena a posicao do campo dentro do registro
   int inicioCampo;

   char *espacoAdic;
   int i;
   char buffer[TAM_REG];
   char chave[TAM_KEY+1];
   char chaveAux[TAM_KEY];
   arquivo = obterArquivo("rb");   //obtendo arquivo para pesquisa

   //obtendo a opcao desejada
   printf("Digite a chave desejada:");
   scanf("%s", chave);

   espacoAdic = (char *) malloc(12 - strlen(chave) + 1);

   for( i = 0; i < 11 - strlen(chave); i++)
   {
     espacoAdic[i] = '*';
   }//for
   espacoAdic[i] = '\0';

   strcat(chave, espacoAdic);

   if(existeValor(chave)==-1){
        printf("Essa Chave nao existe.");
   }else{
        fseek(arquivo, existeValor(chave) , SEEK_SET);
        recuperarRegistro(buffer, arquivo);
        lerRegistro(&umaPessoa, buffer);    //transfere os dados do buffer para a estrutura pessoa
        mostrarRegistro(umaPessoa);
   }




   fclose(arquivo);   //fechando arquivo depois da pesquisa
}//pesquisar

void pesquisarNome(void){
    FILE * arquivo;
    FILE * arquivoAux;

    arquivo = obterArquivo("rb");
    arquivoAux = obterArquivoAux("rb");

    //cria��o das vari�veis necess�rias
    int i;
    char *espacoAdic;
    char registro[20];
    char NameAux[12];
    char firstName[12];
    char posicao[10];
    int continua;
    for(int i=0;i<11;i++){
        NameAux[i] = '*';
    }
    firstName[11] = '\0';

    printf("Escreva o nome que deseja procurar: ");
    scanf("%s", NameAux);
    //caracteres adicionais s�o inseridos
    espacoAdic = (char *) malloc(11 - strlen(NameAux) + 1);

    for( i = 0; i < 11 - strlen(NameAux); i++)
    {
       espacoAdic[i] = '*';
    }//for
    espacoAdic[11] = '\0';

    strcat(NameAux, espacoAdic);
        //concatena��o dos caracteres adicioanis ao nome informado do usu�rio

    char buffer[TAM_REG];
    pessoa umaPessoa;
    int numeroPosicao;
    //a procura s� ir� parar qunado chegar ao final do arquivo

    while(fread(registro, 20, 1, arquivoAux)){
        for(int i=0;i<11;i++){
            firstName[i] = registro[i]; //o valor do firstname ser� atribuido ao "firstName"
        }
        for(int i=0; i<9;i++){
            posicao[i] = registro[i+11]; //o valor da posi��o ser� atribuido a "posicao"
        }
        if(!strcmp(NameAux, firstName)){
            numeroPosicao = atoi(posicao); //n�mero posi��o ser� convertido para int
            fseek(arquivo, numeroPosicao, 0); //o ponteiro ser� colocado na posi��o dada no arquivo auxilair
            fread(buffer, TAM_REG, 1, arquivo); //o registro ser� lido, e adicionado ao buffer
            lerRegistro(&umaPessoa, buffer);
            mostrarRegistro(umaPessoa); //o registro � imprimido
            break;
        }
    }


    fclose(arquivo);
    fclose(arquivoAux);

}

//fun��o respons�vel por converter uma string para um tipo inteiro
int atoi(const char* str){
    int num = 0;
    int i = 0;
    int isNegetive = 0;
    if(str[i] == '-'){
        isNegetive = 1;
        i++;
    }
    while (str[i] && (str[i] >= '0' && str[i] <= '9')){
        num = num * 10 + (str[i] - '0');
        i++;
    }
    if(isNegetive) num = -1 * num;
    return num; //a fun��o retorna um int
}

