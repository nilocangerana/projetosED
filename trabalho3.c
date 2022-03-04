//Nome: Nilo Conrado Messias Alves Cangerana
//N USP: 9805362

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct NO{
    char t;
    int x;
    char semantica[60];
    double valorTeste; //somente para nos numericos NXXX
    char tPai;
    int xPai;
    char ladoConexao; //nao existe este valor no nodo raiz RXXX
    double nivelCerteza; //somente para nos do tipo CXXX

    struct NO *esq;
    struct NO *dir;
};

typedef struct NO NodoArvBin;
typedef struct NO *ArvBin;


ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}


void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada nу
    free(raiz);//libera a raiz
}

/*int insere_ArvBinaria(ArvBin* raiz,char *s,int qtdNos)
{
    if(raiz == NULL)
    return 0;
    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL)
        return 0;

    //Adicionar os valores no novo no que serб inserido
    novo->t=s[0];
    novo->x=((s[1]-'0')*100) + ((s[2]-'0')*10) + (s[3]-'0'); //Conversao do Nу para inteiro
    novo->semantica[0]=s[5]; // adiciona " no primeiro valor do vetor semantica
    int i1=6; //indice do vetor da instrucao apos a primeira aspas "
    int iSemantica=1;   //indice do vetor apos a primeira aspas "
    while(s[i1]!='"')
    {
        novo->semantica[iSemantica]=s[i1]; //adiciona a string de semantica
        iSemantica++;
        i1++;
    }
    novo->semantica[iSemantica]=s[i1]; //recebe a ultima aspas "
    novo->semantica[iSemantica+1]='\0';
    i1=i1+2; // avanca para a proxima instrucao(no pai) do vetor de instrucoes ou primeirp valor numerico em Nos do tipo N
    novo->dir=NULL;
    novo->esq=NULL;

    if(novo->t!='N')
    {
        novo->tPai=s[i1];
        novo->xPai=((s[i1+1]-'0')*100) + ((s[i1+2]-'0')*10) + (s[i1+3]-'0');
    }
    else
    {
        char valorTeste[15];
        int iValorTeste=0;
        char *ptrDouble;
        while(s[i1]!='.')
        {
            valorTeste[iValorTeste]=s[i1];
            iValorTeste++;
            i1++;
        }
        valorTeste[iValorTeste]=s[i1];
        i1++;
        iValorTeste++;
        valorTeste[iValorTeste]=s[i1]; //recebe o digito depois da virgula
        iValorTeste++; //avanca 1 posicao
        valorTeste[iValorTeste]='\0'; //recebe o \0
        i1=i1+2; //avanca a string de comandos e adiciona o no pai
        novo->tPai=s[i1];
        novo->xPai=((s[i1+1]-'0')*100) + ((s[i1+2]-'0')*10) + (s[i1+3]-'0');
        novo->valorTeste=strtod(valorTeste,&ptrDouble);//converte valor teste de string para double
    }
    i1=i1+5; //avanca para a instrucao de ladoConexao

    if(novo->tPai!='R') //se o no pai nao for a raiz(no 0), adiciona o lado da conexao
    {
        novo->ladoConexao=s[i1];
    }
    i1=i1+2; //avanca para a instrucao de nivel de certeza.

    if(novo->t=='C') //adiciona o nivel de certeza de o no for do tipo C
    {
        char nivelCerteza[15];
        int iNivelCerteza=0;
        char *ptrDoubleNC;
        while(s[i1]!='\0')
        {
            nivelCerteza[iNivelCerteza]=s[i1];
            iNivelCerteza++;
            i1++;
        }
        nivelCerteza[iNivelCerteza]=s[i1]; // recebe o \0
        novo->nivelCerteza=strtod(nivelCerteza,&ptrDoubleNC); //converte nivel de certeza de string para double
    }

    //Adiciona o no na arvore
    if(*raiz == NULL) // o nу adicionado й o raiz
    {
        *raiz = novo;
        return 1;
    }
    else{   //o no adicionado nao й a raiz
        struct NO* atual = *raiz;
        struct NO* ant = NULL;


        while(atual != NULL){
            ant = atual;
            if(atual->t==novo->tPai && atual->x==novo->xPai)    //achou o no pai do novo
            {
                if(novo->ladoConexao=='E') //adiciona a esquerda
                {
                    atual->esq=novo;
                    atual=*raiz; //atual volta para o inicio
                }
                else                //adiciona a direita
                {
                    atual->dir=novo;
                    atual=*raiz; //atual volta para o inicio
                }
            }
            else        //nao achou o pai do nу novo
            {

            }



        }
          /*  if(valor == atual->info){
                free(novo);
                return 0;//elemento jб existe
            }

            if(valor > atual->info)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        if(valor > ant->info)
            ant->dir = novo;
        else
            ant->esq = novo;*/
//    }


/*    //print teste--------------------------------------------------------------------
    if(novo->tPai=='R')
    {
        printf("%c %d %s %c %d\n",novo->t,novo->x,novo->semantica,novo->tPai,novo->xPai);
    }
    else
    {
        if(novo->t=='C')
        {
            printf("%c %d %s %c %d %c %.2lf\n",novo->t,novo->x,novo->semantica,novo->tPai,novo->xPai,novo->ladoConexao,novo->nivelCerteza);
        }
        else
        {
            if(novo->t=='B')
            {
                printf("%c %d %s %c %d %c\n",novo->t,novo->x,novo->semantica,novo->tPai,novo->xPai,novo->ladoConexao);
            }
            else
            {
                printf("%c %d %s %.1lf %c %d %c\n",novo->t,novo->x,novo->semantica,novo->valorTeste,novo->tPai,novo->xPai,novo->ladoConexao);
            }
        }
    }
    free(novo);
    //-------------------------------------------------------------------------

    return 0;
}  */

NodoArvBin* criaNo(ArvBin* raiz,char *s) //Cria o nу a partir da descriзгo em string e retorna o nу criado
{
    if(raiz == NULL)
    return 0;

    struct NO* novo;

    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL)
    return 0;

    //Adicionar os valores no novo nу que serб inserido
    novo->t=s[0];
    novo->x=((s[1]-'0')*100) + ((s[2]-'0')*10) + (s[3]-'0'); //Conversao do Nу para inteiro
    novo->semantica[0]=s[5]; // adiciona " no primeiro valor do vetor semantica
    int i1=6; //indice do vetor da instrucao apos a primeira aspas "
    int iSemantica=1;   //indice do vetor apos a primeira aspas "
    while(s[i1]!='"')
    {
        novo->semantica[iSemantica]=s[i1]; //adiciona a string de semantica
        iSemantica++;
        i1++;
    }
    novo->semantica[iSemantica]=s[i1]; //recebe a ultima aspas "
    novo->semantica[iSemantica+1]='\0';
    i1=i1+2; // avanca para a proxima instrucao(no pai) do vetor de instrucoes ou primeirp valor numerico em Nos do tipo N
    novo->dir=NULL;
    novo->esq=NULL;

    if(novo->t!='N')
    {
        novo->tPai=s[i1];
        novo->xPai=((s[i1+1]-'0')*100) + ((s[i1+2]-'0')*10) + (s[i1+3]-'0');
    }
    else
    {
        char valorTeste[15];
        int iValorTeste=0;
        char *ptrDouble;
        while(s[i1]!='.')
        {
            valorTeste[iValorTeste]=s[i1];
            iValorTeste++;
            i1++;
        }
        valorTeste[iValorTeste]=s[i1];
        i1++;
        iValorTeste++;
        valorTeste[iValorTeste]=s[i1]; //recebe o digito depois da virgula
        iValorTeste++; //avanca 1 posicao
        valorTeste[iValorTeste]='\0'; //recebe o \0
        i1=i1+2; //avanca a string de comandos e adiciona o no pai
        novo->tPai=s[i1];
        novo->xPai=((s[i1+1]-'0')*100) + ((s[i1+2]-'0')*10) + (s[i1+3]-'0');
        novo->valorTeste=strtod(valorTeste,&ptrDouble);//converte valor teste de string para double
    }
    i1=i1+5; //avanca para a instrucao de ladoConexao

    if(novo->tPai!='R') //se o no pai nao for a raiz(no 0), adiciona o lado da conexao
    {
        novo->ladoConexao=s[i1];
    }
    i1=i1+2; //avanca para a instrucao de nivel de certeza.

    if(novo->t=='C') //adiciona o nivel de certeza de o no for do tipo C
    {
        char nivelCerteza[15];
        int iNivelCerteza=0;
        char *ptrDoubleNC;
        while(s[i1]!='\0')
        {
            nivelCerteza[iNivelCerteza]=s[i1];
            iNivelCerteza++;
            i1++;
        }
        nivelCerteza[iNivelCerteza]=s[i1]; // recebe o \0
        novo->nivelCerteza=strtod(nivelCerteza,&ptrDoubleNC); //converte nivel de certeza de string para double
    }
    return novo;
}


int inserirNo(ArvBin* raiz, NodoArvBin *novo,NodoArvBin **vetorDeNos,int posVetor)
{
    if(raiz == NULL)
    return 0;

    if(novo == NULL)
    return 0;

    if(*raiz == NULL) //arvore vazia
    {
        *raiz = novo; //insere na raiz
        vetorDeNos[posVetor]=novo;
        printf("%c %d %s %c %d\n",vetorDeNos[posVetor]->t,vetorDeNos[posVetor]->x,vetorDeNos[posVetor]->semantica,vetorDeNos[posVetor]->tPai,vetorDeNos[posVetor]->xPai);
        if(vetorDeNos[posVetor]->esq==NULL)
        {
            printf("esq e null\n");
        }
        posVetor++;
        return posVetor;
    }
    else        //novo nó não é raiz
    {
        for(int i=0;i<posVetor;i++)
        {
            if(vetorDeNos[posVetor]->t==novo->tPai && vetorDeNos[posVetor]->x==novo->xPai)  //se o novo nó tPai e xPai for igual ao valor do nó já inserido(o nó já inserido é o pai) -> inserir
            {
                printf("2");
                //vetorDeNos[posVetor]
                if(novo->ladoConexao=='E')
                {
                    vetorDeNos[posVetor]->esq=novo;
                    if(vetorDeNos[posVetor]->esq==NULL)
                    {
                        printf("esq e null aind\n");
                    }
                    else
                    {
                        printf("esq nao e mais null\n");
                    }
                }
                else
                {
                    vetorDeNos[posVetor]->dir=novo;
                }
                i=posVetor+1;
            }
        }

        if(novo->t=='C') //se o nó é folha
        {
            return posVetor;
        }
        else            // nó não é folha
        {
            vetorDeNos[posVetor]=novo;
            posVetor++;
            return posVetor;
        }
    }
}

void emOrdem_ArvBin(ArvBin *raiz)
{
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvBin(&((*raiz)->esq));
        if((*raiz)->tPai=='R')
        {
            printf("%c %d %s %c %d\n",(*raiz)->t,(*raiz)->x,(*raiz)->semantica,(*raiz)->tPai,(*raiz)->xPai);
        }
        else
        {
        if((*raiz)->t=='C')
        {
            printf("%c %d %s %c %d %c %.2lf\n",(*raiz)->t,(*raiz)->x,(*raiz)->semantica,(*raiz)->tPai,(*raiz)->xPai,(*raiz)->ladoConexao,(*raiz)->nivelCerteza);
        }
        else
        {
            if((*raiz)->t=='B')
            {
                printf("%c %d %s %c %d %c\n",(*raiz)->t,(*raiz)->x,(*raiz)->semantica,(*raiz)->tPai,(*raiz)->xPai,(*raiz)->ladoConexao);
            }
            else
            {
                printf("%c %d %s %.1lf %c %d %c\n",(*raiz)->t,(*raiz)->x,(*raiz)->semantica,(*raiz)->valorTeste,(*raiz)->tPai,(*raiz)->xPai,(*raiz)->ladoConexao);
            }
        }
    }
        emOrdem_ArvBin(&((*raiz)->dir));
    }
}


int main ()
{
    int qtdLinhas; //Quantidade de nos que serao descritos
    int qtdEntradaTeste; //quantidade de entradas testes
    char descricaoNoEntrada[100];   //string que representa a descricao do no

    ArvBin* raiz = cria_ArvBin();

    scanf("%d",&qtdLinhas);
    struct NO* *vetorDeNos = malloc(qtdLinhas * sizeof(struct NO*));
    int posVetorNos=0; //começa em 0 (ponteiro para raiz fica alocada em 0)
    fflush(stdin);
    for(int i=0;i<qtdLinhas;i++)
    {
        fgets(descricaoNoEntrada,100,stdin);
        //printf("%s \n",descricaoNoEntrada);
        fflush(stdin);
        NodoArvBin *novo = criaNo(raiz,descricaoNoEntrada); //cria o no a partir da linha de descricao
        posVetorNos=inserirNo(raiz,novo,vetorDeNos,posVetorNos); //insere novo no na arvore
    }
    //emOrdem_ArvBin(raiz);
    /*scanf("%d",&qtdEntradaTeste);
    for(int i=0;i<qtdEntradaTeste;i++)
    {
        //inserir entrada testes.
    }
    //liberarnos.valorTeste=2;*/

    free(vetorDeNos);
    libera_ArvBin(raiz);
    return 0;
}
