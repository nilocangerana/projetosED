//Nome: Nilo Conrado Messias Alves Cangerana
//N USP: 9805362

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

//Definiçao dos elementos da lista
struct elemento{
    struct elemento *ant;
    double latitude;
    double longitude;
    int tempo;
    double velocidade;
    double distanciaPercorrida;
    struct elemento *prox;
};

typedef struct elemento Elem;

typedef struct elemento* Lista;


//Funcoes fornecidas do trabalho
double grauParaRadiano(double angulo)
    {
        return (angulo * M_PI) / 180.0;
    }

double distancia(
    double latitude1,
    double longitude1,
    double latitude2,
    double longitude2)
    {
        double diferencaLatitude = grauParaRadiano(latitude1 - latitude2);
        double diferencaLongitude = grauParaRadiano(longitude1 - longitude2);
        double a =
        pow(sin(diferencaLatitude / 2.0), 2.0) +
        cos(grauParaRadiano(latitude2)) *
        cos(grauParaRadiano(latitude1)) *
        pow(sin(diferencaLongitude / 2.0), 2.0);
        return 6378137.0 * (2.0 * atan2(sqrt(a), sqrt(1.0 - a)));
}


//Funçoes da LDED
Lista* cria_lista()
{
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL)
        *li = NULL;
    return li;
}


void libera_lista(Lista* li)
{
    if (li != NULL)
	{
        Elem* no;
        while ((*li) != NULL)
		{
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

void imprime_lista(Lista* li)
{
    Elem* no = *li;

    if (li == NULL)
        return;
    while (no != NULL)
    {
        printf("%lf %lf %d %lf %lf\n",no->latitude,no->longitude,no->tempo,no->velocidade,no->distanciaPercorrida);
        no = no->prox;
    }
}

int insere_lista_final(Lista* li, double lat,double longi)
{
    Elem *no;

    if (li == NULL) return 0;
    no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)  return 0;

    no->latitude = lat;
    no->longitude = longi;
    no->prox = NULL;

	if ((*li) == NULL)
	{   //lista vazia: insere início com tempo 0, distancia percorrida 0 e velocidade 0
        no->ant = NULL;
        no->tempo=0;
        no->distanciaPercorrida=0;
        no->velocidade=0;
        *li = no;
    }else
	{
        Elem *aux;
        aux = *li;
        while (aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;

        no->tempo=(no->ant->tempo)+1;
        no->distanciaPercorrida=(distancia(no->latitude,no->longitude,no->ant->latitude,no->ant->longitude))+(no->ant->distanciaPercorrida);
        no->velocidade=((no->distanciaPercorrida)-(no->ant->distanciaPercorrida))/((no->tempo)-(no->ant->tempo));
    }
    return 1;
}

Elem *removeLista(Lista *li, Elem *del)
{
    if (*li == NULL || del == NULL)
        return 0;

    if (*li == del)
        *li = del->prox;

    if (del->prox != NULL)
        del->prox->ant = del->ant;

    if (del->ant != NULL)
        del->ant->prox = del->prox;

    Elem *retorno = del->prox;
    free(del);
    return retorno;
}

void radar(Lista *li,int posicaoRadar,double coberturaRadar,double velMaxPermitida)
{
    Elem *no;
    Elem *noVrI;
    Elem *aux;

    Elem *noVrF;

    int flagSituacao=0;
    double velMax=0;

    if (li == NULL) return;

    no = *li;

    for(int i=0;i<posicaoRadar;i++) //procura o no da posicao informada
    {
        no=no->prox;
    }

    noVrI=no;
    noVrF=no;
    while(noVrI!=NULL && no->distanciaPercorrida - noVrI->distanciaPercorrida <= coberturaRadar && noVrI!=NULL)    //no variante volta ate a distancia minima possivel
    {
        aux=noVrI;
        noVrI=noVrI->ant;
    }
    noVrI=aux; //noVrI recebe a distancia minima possivel de cobertura do radar

    while(noVrF!=NULL && noVrF->distanciaPercorrida - no->distanciaPercorrida <= coberturaRadar) //no variante vai ate a distancia maxima possivel
    {
        aux=noVrF;
        noVrF=noVrF->prox;
    }
    noVrF=aux;  //noVrF recebe a distancia maxima possivel de cobertura do radar

    //checagem de velocidade para ver se esta autuado ou liberado
    aux=noVrI;
    while(aux!=noVrF->prox)
    {
        if(aux->velocidade>velMaxPermitida)
        {
            flagSituacao=1; //esta autuado
            break;
        }
        aux=aux->prox;
    }

    if(flagSituacao==1) //autuado, checagem da velocidade maxima
    {
        aux=noVrI;
        while(aux!=noVrF->prox)
        {
            if(aux->velocidade>=velMax)
            {
                velMax=aux->velocidade;
            }
            aux=aux->prox;
        }
        printf("autuado\n");
        printf("%lf",velMax);
    }
    else
    {
        printf("liberado");
    }
}

void simplificacao(Lista *li,double distanciaMax)
{
    Elem *liFim; //variavel que aponta pro fim da lista(varia conforme o programa é executado)
    Elem *liInicio;//variavel que aponta pro inicio da lista(varia conforme o programa é executado)
    Elem *aux1;
    aux1=*li;
    liInicio=*li;
    Elem *noInicioV; //no que comeca no inicio e varia
    Elem *noFimV; //no que comeca no fim e varia
    int flag1=1;
    int flag2=1;
    int flagEncontro=1;

    Elem *auxI;
    Elem *auxF;

    while(aux1->prox!=NULL) //acha o fim da lista
    {
        aux1=aux1->prox;
    }
    liFim=aux1;
    noFimV=liFim;
    noInicioV=*li;
    while(liFim->distanciaPercorrida - liInicio->distanciaPercorrida > distanciaMax) //loop que é executado enquanto o inicio e fim da lista sao maiores que a distancia maxima pedida
    {
        while(flag1==1) //loop que compara o lado direito com esquerdo ate que é quebrado quando os lados ultrapassam a distancia maxima
        {
            if(noInicioV->distanciaPercorrida - liInicio->distanciaPercorrida<=distanciaMax) //compara o inicio para ver se é menor que a distancia maxima
            {
                if(liFim->distanciaPercorrida - noFimV->distanciaPercorrida<=distanciaMax)  //compara o fim para ver se é menor que a distancia maxima
                {
                    if(noInicioV->distanciaPercorrida - liInicio->distanciaPercorrida <= liFim->distanciaPercorrida - noFimV->distanciaPercorrida)     //avanca o inicio se for menor que o fim
                    {
                        noInicioV=noInicioV->prox;
                    }
                    else    //avanca o fim se for menor que o inicio e etc
                    {
                        noFimV=noFimV->ant;
                    }
                }
                else
                {
                    noInicioV=noInicioV->prox;
                }
            }
            else
            {
                if(liFim->distanciaPercorrida - noFimV->distanciaPercorrida<=distanciaMax)
                {
                    noFimV=noFimV->ant;
                }
                else        //se os dois lados sao maiores que a distancia maxima, o noInicioV volta um no e o noFimV avanca um no(para se ter o limite superior e inferior)
                {
                    if(noFimV->prox!=NULL)
                    {
                        noFimV=noFimV->prox;
                    }
                    if(noInicioV->ant!=NULL)
                    {
                        noInicioV=noInicioV->ant;
                    }
                    flag1=0;
                    flag2=0;
                }
            }

            if(flag2==1) //checar se o noInicioV e noFimV se cruzaram. Caso sim, houve o encontrao, entao ele será tratado ja que a flagEncontro recebe 1
            {            //caso nao houve o cruzamento, nada acontece e o algoritmo segue o curso normal
                if((noFimV->distanciaPercorrida - noInicioV->distanciaPercorrida<0))
                {
                    flag1=0;
                    flagEncontro=0;
                }
            }
        } // fim do while do flag
        auxI=liInicio;
        auxF=noFimV;

        if(flagEncontro==0) //realiza a operacao caso houve encontrao, remove os elementos do meio e deixa o elemento do encontro
        {
            aux1=liInicio->prox;
            if(noInicioV->distanciaPercorrida - liInicio->distanciaPercorrida > liFim->distanciaPercorrida - noFimV->distanciaPercorrida) //checa qual o no de encontro
            {
                noInicioV=noInicioV->ant;
            }
            else
            {
                noFimV=noFimV->prox;
            }
            while(aux1!=noFimV) //remove a primeira metade
            {
                aux1=removeLista(li,aux1);
            }
            aux1=aux1->prox;

            while(aux1!=liFim)  //remove a segunda metade
            {
                aux1=removeLista(li,aux1);
            }
            break; //sai do loop principal
        } else {

        while(auxI!=noInicioV)  //remove os elementos caso o inicio e o noInicioV estejam separados
        {
            if(auxI==liInicio)
            {
                auxI=auxI->prox;
            }
            else
            {
                auxI=removeLista(li,auxI);
            }
        }

        while(auxF!=liFim) //remove os elementos caso o fim e o noFimV estejam separados
        {
            if(auxF==noFimV)
            {
                auxF=auxF->prox;
            }
            else
            {
                auxF=removeLista(li,auxF);
            }
        }

        if(liFim==noFimV) //atualiza o fim e inicio da lista com os novos valores
        {
            liFim=liFim->ant;
            noFimV=liFim;
        }
        else
        {
            liFim=noFimV;
        }

        if(liInicio==noInicioV)
        {
            liInicio=liInicio->prox;
            noInicioV=liInicio;
        }
        else
        {
            liInicio=noInicioV;
        }
        flag1=1;    //reinicia os flags do loop
        flag2=1;
        flagEncontro=1;
        }
    } //while final

    aux1=liInicio;
    while(aux1!=liFim&&flagEncontro==1)  //remove os nos do meio caso tenha algum
    {
        if(aux1!=liInicio)
        {
            aux1=removeLista(li,aux1);
        }
        else
        {
            aux1=aux1->prox;
        }
    }

}

int main()
{
    int qtdEntradas;        //variaveis de entrada
    int opcaoEntrada;
    double *entradaLatLong;
    int posicaoRadar;
    double coberturaRadar;
    double velMaxPermitida;
    double distanciaMaxima;

    Lista *li=cria_lista();

    scanf("%d",&qtdEntradas);   //vetor de double do tamanho de 2 vezes a quantidade de dados, para armazenar latitude e longitude
    entradaLatLong=calloc(2*qtdEntradas,sizeof(double));

    for(int i=0;i<2*qtdEntradas;i=i+2)  //input e insercao dos dados na lista dupla
    {
        scanf("%lf %lf",&entradaLatLong[i],&entradaLatLong[i+1]);
        insere_lista_final(li,entradaLatLong[i],entradaLatLong[i+1]);
    }
    free(entradaLatLong);

    scanf("%d",&opcaoEntrada);
    switch(opcaoEntrada)
    {
    case 0:
        imprime_lista(li);
        break;
    case 1:
        scanf("%d",&posicaoRadar);
        scanf("%lf",&coberturaRadar);
        scanf("%lf",&velMaxPermitida);
        radar(li,posicaoRadar,coberturaRadar,velMaxPermitida);
        break;
    case 2:
        scanf("%lf",&distanciaMaxima);
        simplificacao(li,distanciaMaxima);
        imprime_lista(li);
        break;
    }

    libera_lista(li);
    return 0;
}

