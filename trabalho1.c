//Nome: Nilo Conrado Messias Alves Cangerana
//NUSP: 9805362

#include <stdio.h>
#include <stdlib.h>

//Definiçao da estrutura da lista
struct elemento{
    char letra;
    struct elemento *prox;
};
typedef struct elemento Elem;
typedef struct elemento *Lista;

int contaTamanhoStr(char *str) //Funcao que conta a quantidade de elementos que contem uma string, o ponteiro varia ate encontrar o \0 e para,
{                              //retornado a quantidade de caracteres que a string contem
    int contador=0;
    str=&str[0];
    while(*str!='\0')
    {
        contador++;
        str++;
    }
    return contador;
}

int contaTamanhoLista(Lista *li) //Funcao que conta a quantidade de elementos que a lista possui, percorre a lista até encontrar o ponteiro que
{                                //aponta para NULL e retorna a quantidade de elementos na lista
    int qtdElementos=0;
    if(li == NULL)
        return 0;
    Elem *no = *li;
    while(no != NULL){
        qtdElementos++;
        no = no->prox;
    }
    return qtdElementos;
}

//Funcoes da LDES
Lista *cria_lista() //Cria a lista
{
Lista* li = (Lista*) malloc(sizeof(Lista));
if (li != NULL)
*li = NULL;
return li;
}

void libera_lista(Lista* li)    //Libera as listas da memoria
{
    if(li != NULL){
        Elem* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int insere_lista_final(Lista *li, char dt)  //Insere elementos no final da lista
{
    if(li == NULL)
        return 0;
    Elem *no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->letra = dt;
    no->prox = NULL;
    if((*li) == NULL){ //lista vazia: insere início
        *li = no;
    }else{
        Elem *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return 1;
}

void insereLista (char caracter, Elem *p)   //Funcao que insere um elemento na lista em posiçao especifica.
{                                           //O elemento é inserido após o elemento passado por parametro (p)
   Elem *nova;
   nova = malloc (sizeof (Elem));
   nova->letra = caracter;
   nova->prox = p->prox;
   p->prox = nova;
}

Elem *removeLista(Lista* li, Elem *dt)  //Funcao que remove um nó da lista e retorna o próximo nó(posterior ao removido)
{
    if(li == NULL)
        return 0; //lista vazia
    if((*li) == NULL)
        return 0;

    Elem *ant;
    Elem *no = *li;
    Elem *p;

    while(no!=NULL)
    {
        if(no==dt)      //Checa se o elemento atual e igual ao elemento passado por parametro
        {
            if(no==*li)         //se for igual, remove a cabeca da lista, caso o elemento esteja na posicao 1, ou remove um elemento qualquer
            {
                *li=no->prox; //remove a cabeca da lista
            }
            else
            {
                ant->prox=no->prox;
            }
            p=no->prox;
            free(no);
            break;
        }
        else
        {
            ant=no;
            no=no->prox;
        }
    }
    return p;
}

//Funcoes do Apendice A
int calculoDeslocamento(Lista *li)  //Realiza o calculo do deslocamento, passando a lista da chave como parametro
{
    int deslocamento=0;

    if(li == NULL)
        return 0;
    Elem *no = *li;
    while(no != NULL){
        deslocamento = (deslocamento ^ (no->letra));
        no = no->prox;
    }
    deslocamento = deslocamento%26;

    return deslocamento;
}

int calculoIntervalos(Lista *li, int deslocamento, int *vetorInt)   //Realiza o calculo dos intervalos, tem como parametros:
{                                                                   //A lista da chave, o deslocamento calculado e um vetor de inteiros que armazena os valores.
    int i=0;
    if(li == NULL)
        return 0;
    Elem *no = *li;
    while(no != NULL)
    {
        vetorInt[i]=((no->letra) - 97)^deslocamento;
        no=no->prox;
        i++;
    }
    return i;
}

int insercaoDaChave(Lista *liMsg, Lista *liChave,int *vetorInt,int tamInt)  //Funcao que insere as chaves na lista da mensagem Recebe como parametro:
{                                                                           //As listas de mensagem e de chave, o vetor de intervalos e o tamanho do vetor dos intervalos
    int contadorIntervalo=0;
    int seletorIntervalo=0;
    if(liMsg == NULL)
        return 0;
    if(liChave == NULL)
        return 0;

    Elem *noChave = *liChave;
    Elem *noMsg = *liMsg;

    while(noMsg!=NULL)
    {
        if(contadorIntervalo>=vetorInt[seletorIntervalo%tamInt])
        {
            for(int j=0;j<contadorIntervalo-1;j++)      //Este loop move a posicao atual na lista da mensagem para que os elementos sejam inseridos corretamente.
            {
                if(noMsg != NULL)
                {
                    noMsg=noMsg->prox;                  //Quando atinje o fim da lista (NULL) ele termina o loop
                }
                else
                {
                    j=contadorIntervalo;
                }
            }
            if(noMsg!=NULL)                             //Quando o loop é terminado, se a mensagem estiver em NULL ele quebra o loop do while principal e termina a execucao.
            {
                insereLista(noChave->letra,noMsg);
                contadorIntervalo=0;
                seletorIntervalo++;
                noChave=noChave->prox;
                noMsg=noMsg->prox;
                noMsg=noMsg->prox;
                if(noChave==NULL)
                {
                    noChave=*liChave;
                }
            }
        }
        contadorIntervalo++;
    }

    return 1;
}

int cifraCesar(Lista *li,int deslocamento)      //Funcao que realiza deslocamento da cifra de césar
{
    if(li == NULL)
        return 0;
    Elem *noMsg = *li;
    while(noMsg != NULL)
    {
        noMsg->letra = (((noMsg->letra -97)+deslocamento)%26) +97;
        noMsg=noMsg->prox;
        deslocamento++;
    }
    return 1;
}

void imprime_lista(Lista* li)           //Funcao que imprime a lista
{
    if(li == NULL)
        return;
    Elem* no = *li;
    while(no != NULL){
        printf("%c",no->letra);
        no = no->prox;
    }
}
//Funcoes do Apendice B
int cifraCesarB(Lista *li, int deslocamento) //Funcao que realiza deslocamento da cifra de césar reversa
{
    int auxDeslocamento = deslocamento;
    char auxCaracter;

    if(li == NULL)
        return 0;
    Elem* noMsg = *li;

    while(noMsg!=NULL)
    {
        auxCaracter = (noMsg->letra - 97) - (auxDeslocamento%26);

        if(auxCaracter<0)
        {
            noMsg->letra = auxCaracter + 26 +97;
        }
        else
        {
            noMsg->letra =auxCaracter +97;
        }
        noMsg=noMsg->prox;
        auxDeslocamento++;
    }
    return 1;
}

int remocaoDaChave(Lista *liMsg,int *vetorInt,int tamInt)   //Funcao de remocao de nós da lista
{
    int contadorIntervalo=0;
    int seletorIntervalo=0;
    if(liMsg == NULL)
        return 0;

    Elem* noMsg = *liMsg;

    while(noMsg!=NULL)
    {
        if(contadorIntervalo>=vetorInt[seletorIntervalo%tamInt])
        {
            for(int j=0;j<contadorIntervalo;j++)        //move o ponteiro de noMsg para o elemento que sera removido
            {
                if(noMsg != NULL)                   //Se o ponteiro for NULL ele sai do loop
                {
                    noMsg=noMsg->prox;
                }
                else
                {
                    j=contadorIntervalo;
                }
            }
            if(noMsg!=NULL)
            {
                noMsg = removeLista(liMsg,noMsg);   //Remove o elemento e aponta para o proximo do removido
                contadorIntervalo=0;
                seletorIntervalo++;
            }
        }
        contadorIntervalo++;
    }
    return 1;
}

int main() {
    int tipoEntrada; //valores:  0 para encriptar e 1 para decriptar
    char *msgEntrada; //armazena mensagem
    char *chaveEntrada; //armazena chave
    msgEntrada=calloc(5000,sizeof(char)); //Aloca espaço para guardar 5000 dados do tipo char para mensagem e para chave
    chaveEntrada=calloc(5000,sizeof(char));
    int iMsg=0;
    int iChave=0;

    int *intervalos;    //vetor dos intervalos

    Lista *liMsg = cria_lista();
    Lista *liChave = cria_lista();

    scanf("%d",&tipoEntrada);

    switch(tipoEntrada)
    {
    case 0: //Encriptaçao
        scanf("%s",msgEntrada); //Le a mensagem de entrada e a chave
        scanf("%s",chaveEntrada);
        printf("%d\n",contaTamanhoStr(msgEntrada)); //Conta o tamanho da chave de entrada
        while(*msgEntrada!='\0')        //Cria as listas de mensagem e de chave
        {
            insere_lista_final(liMsg,*msgEntrada);
            msgEntrada++;
            iMsg++;
        }
        while(*chaveEntrada!='\0')
        {
            insere_lista_final(liChave,*chaveEntrada);
            chaveEntrada++;
            iChave++;
        }
        intervalos=calloc(contaTamanhoLista(liChave),sizeof(int));      //aloca espaco para o vetor de intervalos
        calculoIntervalos(liChave,calculoDeslocamento(liChave),intervalos); //calcula os intervalos
        insercaoDaChave(liMsg,liChave,intervalos,contaTamanhoLista(liChave));   //insere a chave na lista de mensagem
        cifraCesar(liMsg,calculoDeslocamento(liChave));     //realiza a cifra de cesar
        printf("%d\n",contaTamanhoLista(liMsg));            //conta o tamanho da lista de mensagem nova
        imprime_lista(liMsg);                               //exibe a lista encripitada
        break;
    case 1: //Decriptaçao
        scanf("%s",msgEntrada);     //Le a mensagem de entrada e a chave
        scanf("%s",chaveEntrada);
        printf("%d\n",contaTamanhoStr(msgEntrada)); //Conta o tamanho da chave de entrada
        while(*msgEntrada!='\0')    //Cria as listas de mensagem e de chave
        {
            insere_lista_final(liMsg,*msgEntrada);
            msgEntrada++;
            iMsg++;
        }
        while(*chaveEntrada!='\0')
        {
            insere_lista_final(liChave,*chaveEntrada);
            chaveEntrada++;
            iChave++;
        }
        intervalos=calloc(contaTamanhoLista(liChave),sizeof(int));  //aloca espaco para o vetor de intervalos
        calculoIntervalos(liChave,calculoDeslocamento(liChave),intervalos); //calcula os intervalos
        cifraCesarB(liMsg,calculoDeslocamento(liChave));                //realiza a cifra de cesar inversa
        remocaoDaChave(liMsg,intervalos,contaTamanhoLista(liChave));    //remove a chave na lista de mensagem
        printf("%d\n",contaTamanhoLista(liMsg));    //conta o tamanho da lista de mensagem nova
        imprime_lista(liMsg);                       //exibe a lista decriptada
        break;
    }
    //Libera a memoria alocada durante o programa
    libera_lista(liMsg);
    libera_lista(liChave);
    free(intervalos);
    free(msgEntrada-iMsg);
    free(chaveEntrada-iChave);
    return 0;
}

