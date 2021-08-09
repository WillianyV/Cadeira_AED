/*AULA 04 - LISTA DINAMICA ENCADEADA*/
#include <stdio.h>
#include <stdlib.h>

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};

struct elemento{
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;
typedef struct elemento* Lista;

//FUNÇÕES
Lista* cria_lista();
void libera_lista(Lista* li);
int insere_lista_final(Lista* li, struct aluno al);
int insere_lista_inicio(Lista* li, struct aluno al);
int insere_lista_ordenada(Lista* li, struct aluno al);
int remove_lista(Lista* li, int mat);
int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int tamanho_lista(Lista* li);
int lista_vazia(Lista* li);
int lista_cheia(Lista* li);
void imprime_lista(Lista* li);
int consulta_lista_mat(Lista* li, int mat, struct aluno *al);
int consulta_lista_pos(Lista* li, int pos, struct aluno *al);

int main(){
    struct aluno a[4] = {{2,"Andre",9.5,7.8,8.5},
                         {4,"Ricardo",7.5,8.7,6.8},
                         {1,"Bianca",9.7,6.7,8.4},
                         {3,"Ana",5.7,6.1,7.4}};
    Lista* li = cria_lista();//PONTEIRO PARA PONTEIRO, ESTRUCT ELEMENTO LISTA
    printf("\nTAMANHO DA LISTA:  %d\n\n",tamanho_lista(li));

    int i;
    printf("\nINSERE:\n\n");
    for(i=0; i < 4; i++){
    	insere_lista_ordenada(li,a[i]);
        //insere_lista_inicio(li,a[i]);
        //insere_lista_final(li,a[i]);
	}
    imprime_lista(li);
    printf("\nTAMANHO DA LISTA:  %d\n\n",tamanho_lista(li));

	printf("\nREMOVE:\n\n");
    for(i=0; i < 4; i++){
        remove_lista_final(li);
		//remove_lista_inicio(li);
        imprime_lista(li);
        printf("\nTAMANHO DA LISTA:  %d\n\n",tamanho_lista(li));
    }
	/*
	remove_lista(li, 3);
	imprime_lista(li);
    printf("\nTAMANHO DA LISTA:  %d\n\n",tamanho_lista(li));

    for(i=0; i < 4; i++)
        insere_lista_ordenada(li,a[i]);
    imprime_lista(li);
	*/
    libera_lista(li);
    system("pause");
    return 0;
}

//FUNÇÕES:
Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;// O INCIO APONTA PARA O NULL, LISTA VAZIA
    return li;
}

void libera_lista(Lista* li){
    if(li != NULL){
        Elem* no;
        while((*li) != NULL){// ENQUANTO O CONTEUDO DA LISTA NAO ESTA VAZIA
            no = *li;// 'NO' RECEBE O INÍCIO DA LISTA
            *li = (*li)->prox;// O INÍCIO DA LISTA APONTA PARA O PRXIMO ELEMENTO DA LISTA
            free(no);//LIBERA O ANTIGO INICIO
        }// FAZER ATÉ A  LISTA FICAR VAZIA
        free(li);// LIBERA A LISTA
    }
}

int consulta_lista_pos(Lista* li, int pos, struct aluno *al){
    if(li == NULL || pos <= 0)//SE A LISTA EH VALIDA E SE A POSICAO EH MAIOR QUE 0
        return 0;
    Elem *no = *li;//PNTEIRO AUXILIAR APONTANDO PARA O INICIO DA LISTA
    int i = 1;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;
    }
    if(no == NULL)//O 'NO' EH IGUAL A NULL? CHEGOU AO FINAL DA LISTA E NAO ENCONTROU
        return 0;
    else{
        *al = no->dados;// O CONTEUDO DO PONTEITO IRA RECEBER OS DADOS DO NO
        return 1;
    }
}

int consulta_lista_mat(Lista* li, int mat, struct aluno *al){
    if(li == NULL)
        return 0;
    Elem *no = *li;
    while(no != NULL && no->dados.matricula != mat){
        no = no->prox;
    }
    if(no == NULL)
        return 0;
    else{
        *al = no->dados;
        return 1;
    }
}

int insere_lista_final(Lista* li, struct aluno al){
    if(li == NULL)// VERIFICA SE A LISTA EXISTE
        return 0;
    Elem *no;
    no = (Elem*) malloc(sizeof(Elem));//ALOCA MEMORIA PARA ELE
    if(no == NULL)//SE NÃO CONSEGUIR ALOCAR MEMORIA PARA O 'NO' RETORNE 0
        return 0;
    no->dados = al;//O 'NO' IRA RECEBER A ESTRUTURA
    no->prox = NULL;// COMO VAI INSERIR NO FINAL, O PROXIMO ELEMENTO EH O NULL
    if((*li) == NULL){//lista vazia: insere início
        *li = no;
    }else{//SE NAO FOR UMA LISTA VAZIA VAI PECORRER TODOS OS ELEMENTOS ATÉ ACHAR O ULTIMO ELEMENTO
        Elem *aux;// CRIAR UM PONTEIRO AUXILIAR, PARA PECORRER A LISTA
        aux = *li;// ENQUANTO O ELEMNTO PROXIMO  FOR DIFERENTE DE NULL
        while(aux->prox != NULL){
            aux = aux->prox;//O ELEMENTO AUXILIAR, VAI RECEBER O PROXIMO
        }
        aux->prox = no;
    }
    return 1;
}

int insere_lista_inicio(Lista* li, struct aluno al){
    if(li == NULL)// VERIFICA SE A LISTA EXISTE
        return 0;
    Elem* no;//CRIAR UM NOVO ELEMENTO 'NO'
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)//SE NÃO CONSEGUIR ALOCAR MEMORIA PARA O 'NO' RETORNE 0
        return 0;
    no->dados = al;
    no->prox = (*li);
    *li = no;
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al){
    if(li == NULL)//VERIFICA SE A LISTA E VALIDA
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));//ALOCA MEMORIA
    if(no == NULL)//VERIFICA SE CONSEGUIU AOCAR MEMORIA DO ELEMENTO
        return 0;
    no->dados = al;
    if((*li) == NULL){//lista vazia: insere início
        no->prox = NULL;
        *li = no;
        return 1;
    }
    else{//PROCURA ONDE INSERIR
        Elem *ant, *atual = *li;//CRIAR ELEMENTOS APARA PECORRER A LSTA
        while(atual != NULL && atual->dados.matricula < al.matricula){
            ant = atual; //O ANTERIOR PASSA A SER O ATUAL
            atual = atual->prox;//E O ATUAL PASSA A SER O PROX ELEMENTO
        }
        if(atual == *li){//insere início
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

int remove_lista(Lista* li, int mat){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;
    Elem *ant, *no = *li;
    while(no != NULL && no->dados.matricula != mat){
        ant = no;
        no = no->prox;
    }
    if(no == NULL)//não encontrado
        return 0;

    if(no == *li)//remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;//O ELEMENTO ANTERIOR AO PROXIMO,VAI APONTAR PARA O PROXIMO DO NO
    free(no);
    return 1;
}

int remove_lista_inicio(Lista* li){
    if(li == NULL)
        return 0;//VERIFICO SE A LISTA EXISTE
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *no = *li;//CRIA UM NOVO ELEMENTO 'NO' QUE IRA RECEBER O VALOR DO INICIO DA LISTA
    *li = no->prox;//O INICIO APONTA PARA O SEGUNTE AO 'NO'
    free(no);
    return 1;
}

int remove_lista_final(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *ant, *no = *li;
    while(no->prox != NULL){
        ant = no;
        no = no->prox;//O 'NO' RECEBE O ELEMENTO SEGUINTE A ELE
    }

    if(no == (*li))//O 'NO' EH IGUAL AO INCIO DA LISTA?
        *li = no->prox;//REMOVE O PRIMEIRO
    else
        ant->prox = no->prox;//O ANTERIO VAI APONTAR, PARA A ONDEO 'NO' APONTA
    free(no);
    return 1;
}

int tamanho_lista(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li; // CRIA UM 'NO' QUE IRÁ RECEBER O PRIMEIRO ELEM DA LISTA
    while(no != NULL){// PECORRE A LISTA ATÉ O 'NO' SER DIFERENTE DE NULL
        cont++;
        no = no->prox;// IR PROXÍMO
    }
    return cont;
}

int lista_cheia(Lista* li){//NA LISTA DINÂMICA NÃO EXISTE CONCEITO DE CHEIA
    return 0;// SÓ QUANDO ACABAR A MEMORIA DINAMICA DO PC
}// VAI RETORNA 0(FALSO) - A LITSA ESTA CHEIA? FALSO.

int lista_vazia(Lista* li){
    if(li == NULL)// SE A LISTA ESTIVER VAZIA RETORNA 1
        return 1;
    if(*li == NULL)// SE O 'CONTEUDO' DA LISTA ESTIVER VAZIO RETORNA 1
        return 1;
    return 0;// A LISTA NÃO ESTA VAZIA;
}

void imprime_lista(Lista* li){
    if(li == NULL)
        return;
    Elem* no = *li;
    while(no != NULL){
        printf("Matricula: %d\n",no->dados.matricula);
        printf("Nome: %s\n",no->dados.nome);
        printf("Notas: %f %f %f\n",no->dados.n1,
                                   no->dados.n2,
                                   no->dados.n3);
        printf("-------------------------------\n");

        no = no->prox;
    }
}
