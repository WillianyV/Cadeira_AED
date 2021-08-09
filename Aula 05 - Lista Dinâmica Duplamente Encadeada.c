/*AULA 05 - LISTA DINÂMICA DUPLAMENTE ENCADEADA*/
#include <stdio.h>
#include <stdlib.h>

struct aluno{//INFORMAÇÃO QUE IRÁ SER GUARDADA NA LISTA
    int matricula;
    char nome[30];
    float n1,n2,n3;
};

struct elemento{//ESTRUTURA QUE CONTROLA A LISTA
    struct elemento *ant;
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;//FACILITAR AS OPERAÇÕES DENTRO DAS FUNÇÕES
typedef struct elemento* Lista;//DEFENIDO O PONTEIRO TIPO LISTA, SERA USADO NO PROG PRINCIPAL

//FUNÇÕES
Lista* cria_lista();
void libera_lista(Lista* li);
int consulta_lista_pos(Lista* li, int pos, struct aluno *al);
int consulta_lista_mat(Lista* li, int mat, struct aluno *al);
int insere_lista_final(Lista* li, struct aluno al);
int insere_lista_inicio(Lista* li, struct aluno al);
int insere_lista_ordenada(Lista* li, struct aluno al);
int remove_lista_meio(Lista* li, int mat);
int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int tamanho_lista(Lista* li);
int lista_vazia(Lista* li);
void imprime_lista(Lista* li);

int main(int argc, char *argv[]) {
	struct aluno a[4] = {{2,"Andre",9.5,7.8,8.5},
                         {4,"Ricardo",7.5,8.7,6.8},
                         {1,"Bianca",9.7,6.7,8.4},
                         {3,"Ana",5.7,6.1,7.4}};
    Lista* li = cria_lista();
    printf("TAMANH0: %d\n\n\n\n",tamanho_lista(li));

    int i;
    for(i=0; i < 4; i++){
        insere_lista_ordenada(li,a[i]);
        //insere_lista_final(li,a[i]);
        //insere_lista_inicio(li, a[i]);
    }
    imprime_lista(li);
    printf("\n\nTAMANH0: %d\n\n\n",tamanho_lista(li));

    //remove_lista_meio(li,3);

    for(i=0; i < 4; i++){
        remove_lista_final(li);
        imprime_lista(li);
        printf("\nTamanho: %d\n\n\n\n",tamanho_lista(li));
    }

    //imprime_lista(li);
    //printf("\n\nTAMANH0: %d\n\n\n",tamanho_lista(li));
    libera_lista(li);
    system("pause");
    return 0;
}


Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li){
    if(li != NULL){
        Elem* no;//'NO' AUXILIAR
        while((*li) != NULL){// ENQUANTO CONTEUDO DIFERENTE DE 'NULL'
            no = *li;//O 'NO' RECEBE CONTEUDO
            *li = (*li)->prox;//*LI RECEBE O PROXIMO ELEMENTO
            free(no);//LIBERA O 'NO', O 'NO' FICA PARA TRÁS
        }
        free(li);
    }
}

int consulta_lista_pos(Lista* li, int pos, struct aluno *al){
    if(li == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;
    }
    if(no == NULL)//NAO ENCONTRADO
        return 0;
    else{
        *al = no->dados;//DEVOLVER OS DADOS
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
    if(li == NULL)
        return 0;
    Elem *no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if((*li) == NULL){//lista vazia: insere início
        no->ant = NULL;
        *li = no;//O PRIMEIRO ELEMENTO DA LISTA PASSA A SER O 'NO'
    }else{
        Elem *aux;//PONTEIRO AXU QUE IRA RECEBER O INICIO DA LISTA
        aux = *li;
        while(aux->prox != NULL){//ENQUANTO O PROX FOR DIFERENTE DE NULL, IRA ANDAR A LISTA
            aux = aux->prox;// AUXILIAR SEMPRE VAI RECEBER O PROXIMO
        }
        aux->prox = no;//AUXILIAR VAI APONTAR PARA O ELEM 'NO'
        no->ant = aux;//E O 'NO' IRA APONTA, PARA QUEM ERA O ULTIMO ELEMENTO
    }
    return 1;
}

int insere_lista_inicio(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = (*li);//O PRX 'NO' IRA APONTAT PARA O CONTEUDO DE LI
    no->ant = NULL;
    if(*li != NULL)//lista não vazia: apontar para o anterior!
        (*li)->ant = no;//O ANT APONTA PARA O NOVO NO QUE INSERIU
    *li = no;// E O 'NO' PASSA A SER O PRIMEIRO ELEM DA LISTA
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    if((*li) == NULL){//lista vazia: insere início
        no->prox = NULL;
        no->ant = NULL;
        *li = no;
        return 1;
    }
    else{//PROCURAR ONDE INSERIR
        Elem *ante, *atual = *li;
        while(atual != NULL && atual->dados.matricula < al.matricula){
            ante = atual;
            atual = atual->prox;
        }
        if(atual == *li){//insere início
            no->ant = NULL;
            (*li)->ant = no;
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = ante->prox;//O 'NO' IRA RECEBO O PROXIMO DO ANTERIOR
            no->ant = ante;//O 'NO' PASSA APONTAR PARA O ANTERIOR
            ante->prox = no;//O PROXIMO ELEMNTE DO ANTERIOR, RECEBE O 'NO'
            if(atual != NULL)//VERIFICA SE NAO EH IGUA A NULL, OU SEJA SE ESTA NO MEIO DA LISTA
                atual->ant = no;
        }
        return 1;
    }
}

int remove_lista_meio(Lista* li, int mat){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;
    Elem *no = *li;
    while(no != NULL && no->dados.matricula != mat){
        no = no->prox;
    }
    if(no == NULL)//não encontrado
        return 0;

    if(no->ant == NULL)//remover o primeiro?
        *li = no->prox;//SE O 'NO' ANTERIOR EH IGUAL A NULL,REMOVE O PRIMEIRO ELM DA LISTA
    else//REMOVENDO NO MEIO
        no->ant->prox = no->prox;//O 'NO' PROXIMO DO ANTERIO, IRA RECEBER O PRIXIMO ELEM

    if(no->prox != NULL)//VERIFICA SE ERA O ULTIMO
        no->prox->ant = no->ant;//O PROXIMO ELEMNTO , IRA APONTAR PARA O ANTERIOR

    free(no);
    return 1;
}

int remove_lista_inicio(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *no = *li;
    *li = no->prox;
    if(no->prox != NULL)
        no->prox->ant = NULL;// O PROXIMO DE 'NO', IRA APONTAR NULL PARA O SEU ANTERIOR

    free(no);
    return 1;
}

int remove_lista_final(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *no = *li;//CRIA UM 'NO' AUXILIAR QUE REEBE O INCIO DA LISTA
    while(no->prox != NULL)//PECORRE A LISTA
        no = no->prox;

    if(no->ant == NULL)
        *li = no->prox;//REMOVE O PRIMEIRO E UNICO
    else
        no->ant->prox = NULL;//MEU 'NO' VAI APONTAR PARA ANTERIOR, E O PROX DO ANTERIOR VAI APONTAR PARA NULL

    free(no);
    return 1;
}

int tamanho_lista(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;//CRIAR 'NO' AUXILIAR PARA RECEBER PRIMEIRO 'NO' DA LISTA
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li){
    return 0;
}

int lista_vazia(Lista* li){
    if(li == NULL)//NAO TENHO LISTA
        return 1;
    if(*li == NULL)//SE OCONTEUDO FOR IGUAL A NULL
        return 1;
    return 0;//A LISTA EH VALIDA
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
