#include <stdio.h>
#include <stdlib.h>

struct NO{
    int info;
    struct NO *esq;
    struct NO *dir;
};
typedef struct NO* ArvBin;//STRUC PONTEIRO ArvBin

ArvBin* cria_ArvBin();
void libera_ArvBin(ArvBin *raiz);
int insere_ArvBin(ArvBin* raiz, int valor);
int remove_ArvBin(ArvBin *raiz, int valor);
int estaVazia_ArvBin(ArvBin *raiz);
int altura_ArvBin(ArvBin *raiz);
int totalNO_ArvBin(ArvBin *raiz);
int consulta_ArvBin(ArvBin *raiz, int valor);
void preOrdem_ArvBin(ArvBin *raiz);
void emOrdem_ArvBin(ArvBin *raiz);
void posOrdem_ArvBin(ArvBin *raiz);


int main(){
    int N = 8, dados[8] = {50,100,30,20,40,45,35,37};

    ArvBin* raiz = cria_ArvBin();//ArvBin* ASSIM FICA PONTEIRO PARA PONTEIRO

    int i;
    for(i=0; i < N; i++)
        insere_ArvBin(raiz,dados[i]);

    preOrdem_ArvBin(raiz);//RED
    //emOrdem_ArvBin(raiz);//ERD
    //posOrdem_ArvBin(raiz);EDR

    if(remove_ArvBin(raiz,50)){
        printf("removido\n");
        preOrdem_ArvBin(raiz);
    }else
        printf("NAO removido\n");


//    printf("altura: %d\n",altura_ArvBin(raiz));
//    printf("total NOs: %d\n",totalNO_ArvBin(raiz));
//
//    if (consulta_ArvBin(raiz, 4, &al))
//        printf("\n%d %s\n",al.mat,al.nome);

    libera_ArvBin(raiz);
    printf("\nFim!\n");
    return 0;
}
//FUNÇÕES:
ArvBin* cria_ArvBin(){// TIPO CRIAR NO
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)//SE DEU CERTO A ALOCAÇÃO
        *raiz = NULL;//VOU INSERIR NO 'CONTEUDO' O NULL
    return raiz;
}
/*professor berg:
no* criar_no(int elemento) {
	no* novo = (no*) malloc(sizeof(no));
	if (novo == NULL) {
		printf("\n-------erro de memoria------\n");
		return NULL;
	} else {
		novo->valor = elemento;
		novo->esquerda = NULL;
		novo->direita = NULL;
	}
	return novo;
}*/
void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);//PECORRER RECUSSIVAMENTE O NO DA ESQUERDA
    libera_NO(no->dir);//PECORRER RECUSSIVAMENTE O NO DA DIREITA
    free(no);//E LIBERAR O NO, SEMPRE ELMINANDO OS ULTIMOS, 1a ESQ 2a DIR
    no = NULL;
}

void libera_ArvBin(ArvBin* raiz){
    if(raiz == NULL)// VERIFICA SE EXISTE RAIZ
        return;
    libera_NO(*raiz);//LIVERA CADA NO DA ARVORE
    free(raiz);//LIBERA RAIZ
}

int insere_ArvBin(ArvBin* raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* novo;//CRIA UM NOVO NO
    novo = (struct NO*) malloc(sizeof(struct NO));//ALOCA
    if(novo == NULL)//ERRO DE MEMORIA
        return 0;
    novo->info = valor;
    novo->dir = NULL;
    novo->esq = NULL;
    //PROCURAR O LUGAR DA INSERÇÃO:
    if(*raiz == NULL)//ARVORE VAZIA?
        *raiz = novo;//INSERIR NA RAIZ
    else{
        struct NO* atual = *raiz;//PARA PEOCRRER A RAIZ
        struct NO* ant = NULL;
        while(atual != NULL){
            ant = atual;
            if(valor == atual->info){
                free(novo);
                return 0;//elemento já existe
            }

            if(valor > atual->info)//PECORRENDO A LISTA A DIR
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        if(valor > ant->info)//QUANDO CHEGAR NO FOLHA
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}
/*
void inserir(no **raiz, int elemento) {
	if (*raiz == NULL) { //não existe raiz
		*raiz = criar_no(elemento); //(novo)
	} else if (elemento < (*raiz)->valor) {
		//inserir a esquerda
		inserir(&((*raiz)->esquerda), elemento); //&((*raiz)->esquerda) = posição d esquerdo
	} else if (elemento > (*raiz)->valor) {
		//inserir a direita
		inserir(&((*raiz)->direita), elemento); //&((*raiz)->direita) = posição d direito
	} else {
		printf("numero jah existe na arvore. impossivel inserir");
	}
}
*/

struct NO* remove_atual(struct NO* atual) {
    struct NO *no1, *no2;
    if(atual->esq == NULL){//SEM FILHO A ESQUERDA
        no2 = atual->dir;//APONTA PAAR O ATUAL A DIREITA
        free(atual);
        return no2;
    }

    no1 = atual;
    no2 = atual->esq;
    while(no2->dir != NULL){//procurar filho mai dir na subarv a esquerda
        no1 = no2;
        no2 = no2->dir;//DESCER A DIREITA
    }

    if(no1 != atual){//COPIA O FILO MAIS A DIRETIA NA SUB-ARV DA ESQUERDA PARA O
        no1->dir = no2->esq;//LUGAR DO NO REMOVIDO
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

int remove_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* ant = NULL;
    struct NO* atual = *raiz;
    while(atual != NULL){//ACHOU O NO, VAMOS VER O LADO A SER REMOVIDO
        if(valor == atual->info){
            if(atual == *raiz)
                *raiz = remove_atual(atual);
            else{
                if(ant->dir == atual)
                    ant->dir = remove_atual(atual);//ANT VAI APONTAR PARA O NOVO ATUAL
                else
                    ant->esq = remove_atual(atual);
            }
            return 1;
        }
        ant = atual;//ANDANDO NA ARVORE A PROCUARA DO NO A SER REMOVIDO
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

int estaVazia_ArvBin(ArvBin *raiz){
    if(raiz == NULL)//SE A RAIZ FOR IGUAL A NULL, NAO TEM RAIZ
        return 1;
    if(*raiz == NULL)//SE O CONTEUDO DA RAIZ IGUAL A NULL, NAO TEM ELEMENTOS
        return 1;
    return 0;
}

int totalNO_ArvBin(ArvBin *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvBin(&((*raiz)->esq));//CHAMA RECUSSIVAMENTE
    int alt_dir = totalNO_ArvBin(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);//SOMA OS NOS E 1(RAIZ)
}

int altura_ArvBin(ArvBin *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvBin(&((*raiz)->esq));//RECUSSIVAMENTE, PASSAR O ENDEREÇO
    int alt_dir = altura_ArvBin(&((*raiz)->dir));
    if (alt_esq > alt_dir)//ALTURA DO MAIOR  FILHO(TBM SUB-ARVORE) FAZ A COMPARAÇÃO, QUE QUEM EH MAIOR
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

int consulta_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            return 1;//ACHOU
        }
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;//CHEGOU EM UMA NO FOLHA E NAO ACHOU
}
/*

int busca_arvore(no *raiz, int elemento){//BUSCA BINARIA
    if (raiz == NULL){
        return FALSE;
    }else{
        if (elemento == raiz->valor){
            return TRUE;
        }else if (elemento < raiz->valor){
            return busca_arvore(raiz->esquerda,elemento);
        }else{
            return busca_arvore(raiz->direita,elemento);
        }
    }
}
*/

//PECORRER A LISTA:
void preOrdem_ArvBin(ArvBin *raiz){//RAIZ,ESQUERDA,DIREITA
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("%d\n",(*raiz)->info);
        preOrdem_ArvBin(&((*raiz)->esq));
        preOrdem_ArvBin(&((*raiz)->dir));
    }
}

void emOrdem_ArvBin(ArvBin *raiz){//ESQUERDA, RAIZ, DIREITA
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvBin(&((*raiz)->esq));//ESQ, IMPRIME O NO, DIREITA
        printf("%d\n",(*raiz)->info);
        emOrdem_ArvBin(&((*raiz)->dir));
    }
}

void posOrdem_ArvBin(ArvBin *raiz){//ESQUERDA, DIREITA, RAIZ
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdem_ArvBin(&((*raiz)->esq));
        posOrdem_ArvBin(&((*raiz)->dir));
        printf("%d\n",(*raiz)->info);
    }
}
/*
void imprimir(no *raiz, int metodo) {
	if(metodo==PRE_ORDEM){//imprimir em pré-ordem
		if (raiz != NULL) {
				printf("%d ", raiz->valor);  //R
				imprimir(raiz->esquerda,-1);//E
				imprimir(raiz->direita,-1);//D
			}
	}else if(metodo==ORDEM){ //imprimir em ordem
		if (raiz != NULL) {
				imprimir(raiz->esquerda, 0); //E
				printf("%d ", raiz->valor); //R
				imprimir(raiz->direita, 0);//D
			}
	}else if(metodo==POS_ORDEM){//imprimir em pos-ordem
		if (raiz != NULL) {
				imprimir(raiz->esquerda,1);  //E
				imprimir(raiz->direita,1);  //D
				printf("%d ", raiz->valor);//R
			}
	}else{
		printf("vou fazer o exercicio de casa para imprimir em largura!!");
	}
}*/
