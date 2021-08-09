/*AULA 06 - LISTAS CIRCULARES*/
#include <stdio.h>
#include <stdlib.h>

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};
struct elemento{
    struct aluno dados;
    struct elemento *prox;// PARA O PROXIMO ELEM DA LITSA
};
typedef struct elemento Elem;
typedef struct elemento* Lista; //PONTEIRO TIPO LISTA

Lista* cria_lista();
void libera_lista(Lista* li);
int consulta_lista_pos(Lista* li, int pos, struct aluno *al);
int consulta_lista_mat(Lista* li, int mat, struct aluno *al);
int insere_lista_final(Lista* li, struct aluno al);
int insere_lista_inicio(Lista* li, struct aluno al);
int insere_lista_ordenada(Lista* li, struct aluno al);
int remove_lista(Lista* li, int mat);
int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int tamanho_lista(Lista* li);
int lista_vazia(Lista* li);
void imprime_lista(Lista* li);

int main(){
    struct aluno a[4] = {{2,"Andre",9.5,7.8,8.5},
                         {4,"Ricardo",7.5,8.7,6.8},
                         {1,"Bianca",9.7,6.7,8.4},
                         {3,"Ana",5.7,6.1,7.4}};
    Lista* li = cria_lista(); //LISTA* LI EH UM PONTEIRO PARA PONTEIRO
    printf("Tamanho: %d\n\n\n\n",tamanho_lista(li));

    int i;
    for(i=0; i < 4; i++)
        //insere_lista_inicio(li,a[i]);
        //insere_lista_final(li,a[i]);
        insere_lista_ordenada(li,a[i]);


    imprime_lista(li);
    printf("\n\n Tamanho: %d\n\n\n",tamanho_lista(li));

    //remove_lista(li,4);
    for(i=0; i < 4; i++){
        //remove_lista_final(li);
        remove_lista_inicio(li);
        imprime_lista(li);
        printf("\n\n======================\n\n");
    }

    imprime_lista(li);
    printf("\n\n Tamanho: %d\n\n\n",tamanho_lista(li));
    libera_lista(li);
    system("pause");
    return 0;
}


Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)//SE ALOCAÇÃO DEU CERTO
        *li = NULL;//ENTAO O CONTEUDO DA RIMEIRO ELM RECEBE/ ESTA VAZIO
    return li;
}

void libera_lista(Lista* li){
    if(li != NULL && (*li) != NULL){// VERIFICA SE A SLITA EH VALIDA E SE O CONTEUDO EH DIFERENTE DE NULL (NAO EH VAZIA)
        Elem *aux, *no = *li; //CRIA ELM PARA PECORRER A LITSA
        while((*li) != no->prox){//ENQUANTO O PROXIMO ELEM FOR DIFERENTE DO PRIMEIRO ELM DA LISTA
            aux = no;
            no = no->prox;// O NO APONTA PARA O PROXM ELM
            free(aux);
        }
        free(no);
        free(li);
    }
}

int consulta_lista_pos(Lista* li, int pos, struct aluno *al){
    if(li == NULL || (*li) == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while(no->prox != (*li) && i < pos){//ENQUANDO NAO DER UMA VOLTA NA LISTA E O CONT FOR MENOR QUE A POS
        no = no->prox;// NO IRA AVANCAR
        i++;
    }
    if(i != pos)//POS NAO EXISTE
        return 0;
    else{
        *al = no->dados;//COIA OS DADOS DA POS 'NO' PARA O CONTEUDO (*AL)
        return 1;
    }
}

int consulta_lista_mat(Lista* li, int mat, struct aluno *al){
    if(li == NULL || (*li) == NULL)
        return 0;
    Elem *no = *li;
    while(no->prox != (*li) && no->dados.matricula != mat)//ANDAR NA LISTA
        no = no->prox;
    if(no->dados.matricula != mat)//NAO LOCALIZOU
        return 0;
    else{
        *al = no->dados;//COIA OS DADOS
        return 1;
    }
}

int insere_lista_final(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    if((*li) == NULL){//lista vazia: insere início
        *li = no;
        no->prox = no;
    }else{
        Elem *aux = *li;
        while(aux->prox != (*li)){//ANDAR NA LISTA, ATÉ O INICIO
            aux = aux->prox;//AUX REBECE SEU PROCXIMO ELM
        }
        aux->prox = no;//VAI APONTAR PARA O NO, O NO VAI SER O PROX
        no->prox = *li;//E O NO IRA APONTAR PARA O INCIO DA LISTA
    }
    return 1;
}

int insere_lista_inicio(Lista* li, struct aluno al){
    if(li == NULL)//VERIFICA SE A LISTA EXISTE
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));//ALOCAR NOVO ELEM
    if(no == NULL)//VERIFICA SE FOI ALOCADO
        return 0;
    no->dados = al;//COPIA OS DADOS DO ALUNO APAR O NOVO NO
    if((*li) == NULL){//lista vazia: insere início
        *li = no;//INSERE NO INICIO
        no->prox = no;//ELE VAI APONTAR PARA ELE MESMO
    }else{
        Elem *aux = *li;//ELEMENTO AUX QUE RECEBE O INICIO DA LISTA
        while(aux->prox != (*li)){//VAI ANDAR NA LISTA ATÉ SER DIFERE DO PRIMEIRO ELEM DA LISTA
            aux = aux->prox;//AUX, RECEBE O PROXIMO ELEM
        }
        aux->prox = no;//APONTA PARA O NO QUE VAI INCERIR
        no->prox = *li;//E O NO QUE FOI INSERIDO VAI APONTAT PARA O INICIO DA LISTA
        *li = no;// O INCIO DA LISTA  RECEBE NO
    }
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al){//TERMINAR
    if(li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    if((*li) == NULL){//LISTA VAZIA: insere início
        *li = no;
        no->prox = no;
        return 1;
    }
    else{
        if((*li)->dados.matricula > al.matricula){//insere início
            Elem *atual = *li;
            while(atual->prox != (*li))//procura o último
                atual = atual->prox;
            no->prox = *li;
            atual->prox = no;
            *li = no;
            return 1;
        }
        Elem *ant = *li, *atual = (*li)->prox;//FOI CRIADO DOIS NOS
        while(atual != (*li) && atual->dados.matricula < al.matricula){//ENQUANTO O ATUAL FOR DIFERENTE DO PRIMEIRO ELEM E OS DANDOS SAO MENORES
            ant = atual;//O ATUAL PASSA A SER O ANTERIOR
            atual = atual->prox;//O ATUAL RECEBE O PROXIMO ELEM
        }
        //INSERIR
        ant->prox = no;//O PROXIMO DO ANT IRA RECEBER O O
        no->prox = atual;//E O PROX ELEM AO NO RECEBE ATUAL
        return 1;
    }
}

int remove_lista_inicio(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    if((*li) == (*li)->prox){//VERIFICA SE A LISTA TEM 'UM UNICO' ELEMENTO
        free(*li);
        *li = NULL;
        return 1;
    }
    Elem *atual = *li;
    while(atual->prox != (*li))//procura o último
        atual = atual->prox;

    Elem *no = *li;
    atual->prox = no->prox;//ATUAL APONTA, PARA ONDE O 'NO' APONTAVA
    *li = no->prox;//O INICIO DA LISTA APONTA (O PROXIMO ELEM AO 'NO')
    free(no);
    return 1;
}

int remove_lista_final(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    if((*li) == (*li)->prox){//VERIFICA SE A LISTA TEM 'UM UNICO' ELEMENTO
        free(*li);
        *li = NULL;
        return 1;
    }
    Elem *ant, *no = *li;
    while(no->prox != (*li)){//procura o último
        ant = no;//O ANTERIOR PASSAR A SER O NO
        no = no->prox;//E O NO RECEBE O DA FRENTE
    }
    ant->prox = no->prox;//O ANTERIOR VAI APONTAR PARA ONDE O 'NO' APONTAVA
    free(no);
    return 1;
}

int remove_lista(Lista* li, int mat){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;
    Elem *no = *li;//NO AUX COMPRIMEIRO ELEM DA LISTA
    if(no->dados.matricula == mat){//remover do início
        if(no == no->prox){//VERIFICA SE A LISTA TEM 'UM UNICO' ELEMENTO
            free(no);
            *li = NULL;
            return 1;
        }else{
            Elem *ult = *li;
            while(ult->prox != (*li))//procura o último
                ult = ult->prox;
            ult->prox = (*li)->prox;
            *li = (*li)->prox;
            free(no);
            return 1;
        }
    }
    Elem *ant = no;// O ANTERIOR RECEBE O VALOR DO NO
    no = no->prox;// O NO VAI PARA O PROX ELEM
    while(no != (*li) && no->dados.matricula != mat){
        ant = no;
        no = no->prox;
    }
    if(no == *li)//não encontrado
        return 0;

    ant->prox = no->prox;//O ANTERIOR VAI APONTAR PARA ONDE O 'NO' APONTAVA
    free(no);
    return 1;
}

int tamanho_lista(Lista* li){
    if(li == NULL || (*li) == NULL)//VERIFICAMOS SE A LISTA EH VALIDA E SE A LISTA ESTA VAZIA
        return 0;
    int cont = 0;
    Elem* no = *li;// VARIAVÉL AUX, RECEBE O CONTEUDO DO PRIMEIOR ELEM
    do{
        cont++;
        no = no->prox;//ANDA PARA O PROXIMO
    }while(no != (*li));//FAZ ISSO ATÉ O NO SER TIFERENTE DO PRIMEIRO CONTEU DA LISTA
    return cont;
}

int lista_cheia(Lista* li){
    return 0;
}

int lista_vazia(Lista* li){
    if(li == NULL)//SE ALISTA EH VALIDA
        return 1;
    if(*li == NULL)//SE A LISTA ESTA VAZIA
        return 1;
    return 0;
}

void imprime_lista(Lista* li){
    if(li == NULL || (*li) == NULL)
        return;
    Elem* no = *li;
    do{
        printf("Matricula: %d\n",no->dados.matricula);
        printf("Nome: %s\n",no->dados.nome);
        printf("Notas: %f %f %f\n",no->dados.n1,
                                   no->dados.n2,
                                   no->dados.n3);
        printf("-------------------------------\n");
        no = no->prox;
    }while(no != (*li));
}
