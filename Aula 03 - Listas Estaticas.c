/*Aula 03 - Listas Sequêncial Estaticas*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};
struct lista{
    int qtd;
    struct aluno dados[MAX];
};
typedef struct lista Lista;
//FUNÇÕES:
Lista* cria_lista();
void libera_lista(Lista* li);
int tamanho_lista(Lista* li);
int lista_cheia(Lista* li);
int lista_vazia (Lista* li);
int insere_lista_final(Lista* li, struct aluno al);
int insere_lista_inicio(Lista* li, struct aluno al);
int insere_lista_ordenada(Lista* li, struct aluno al);
int remove_lista_final (Lista* li);
int remove_lista_inicio(Lista* li);
int remove_lista_meio(Lista* li, int mat);
int consulta_lista_posicao(Lista* li, int pos, struct aluno *al);
int consulta_lista_conteudo(Lista* li, int cont, struct aluno *al);
void imprime_lista (Lista* li);

int main(int argc, char *argv[]) {
     struct aluno a[4] = {{2,"Andre",9.5,7.8,8.5},
                         {4,"Ricardo",7.5,8.7,6.8},
                         {1,"Bianca",9.7,6.7,8.4},
                         {3,"Ana",5.7,6.1,7.4}};
    Lista* li = cria_lista();

    int i;
    for(i=0;i<4;i++)
        insere_lista_ordenada(li,a[i]);
        //insere_lista_final(li,a[i]);
        //insere_lista_inicio(li,a[i]);
    imprime_lista(li);
    printf("\n\n\n");

    for(i=0;i < 5; i++){
        //if(!remove_lista_meio(li,i))
        //if(!remove_lista_inicio(li))
        if(!remove_lista_final(li))
            printf("ERRO!\n");
        imprime_lista(li);
        printf("\n\n\n");
    }

    libera_lista(li);
    system("pause");
    return 0;
}
Lista* cria_lista(){
    Lista *li;
    li = (Lista*) malloc(sizeof(struct lista));
    if(li != NULL)
        li->qtd = 0; //APONTAR A PRIMEIRA POSICAO VAJA DA LISTA, E TBM QUANTAS POSIÇÕES TENHO PREENCHIDAS
    return li;
}

void libera_lista(Lista* li){
    free(li);
}

int tamanho_lista(Lista* li){
    if (li == NULL)
        return -1; // RETORNA ERRO
    else
        return li->qtd;
}

int lista_cheia(Lista* li){
    if (li == NULL)
        return -1;
    return (li->qtd == MAX);// SE ESSA EXPRESSÃO FOR VERDADEIRA RETORNA 1 SE FOR FALSA O
}

int lista_vazia (Lista* li){
    if (li == NULL)
        return -1;
    return (li->qtd == 0); // SE ESSA EXPRESSÃO FOR VERDADEIRA RETORNA 1 SE FOR FALSA O
}

int insere_lista_final(Lista* li, struct aluno al){
    if (li == NULL)
        return 0;
    if(lista_cheia(li))
        return 0;
    li->dados[li->qtd] = al;
    li->qtd++;
    return 1;
}

int insere_lista_inicio(Lista* li, struct aluno al){
    if (li == NULL) return 0;
    if (lista_cheia(li)) return 0;
    int i;
    for (i = li->qtd-1;i>=0;i--) //qtd-1= ultimo el da lista;
        li->dados[i+1] = li->dados[i]; // POSICAO DA FRENTE = RECEBE OS DADOS DA ANTERIOR A ELA
    li->dados[0] = al; //ABRIU ESPAO NO INICIO DA LISTA, AI INSERI O EL
    li->qtd++;
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al){
    if(li == NULL) return 0;
    if(li->qtd == MAX) return 0;//lista cheia

    int k,i = 0;
    while(i<li->qtd && li->dados[i].matricula < al.matricula)
        i++;

    for(k=li->qtd-1; k >= i; k--)
        li->dados[k+1] = li->dados[k];

    li->dados[i] = al;
    li->qtd++;
    return 1;
}

int remove_lista_final (Lista* li){
    if (li == NULL) return 0;
    if (li->qtd == 0) return 0; //if (lista_vazia(li))
    li->qtd--;
    return 1;
}

int remove_lista_inicio(Lista* li){
    if (li == NULL) return 0;
    if(lista_vazia(li)) return 0;
    int k = 0;
    for (k=0; k < li->qtd-1;k++)
        li->dados[k] = li->dados[k+1]; // A POSICAO QUE ESTA ATRAS, RECEBE A POSICAO QUE ESTA NA FRENTE
    li->qtd--;
    return 1;
}

int remove_lista_meio(Lista* li, int mat){
    if (li == NULL) return 0;
    if(lista_vazia(li)) return 0;
    int k, i = 0;
    while (i < li->qtd && li->dados[i].matricula != mat) //PROCURAR A MATRICULA  DO ALUNO
        i++;
    if(i == li->qtd) // ELEMENTO NAO ENCONTRADO
        return 0;
    for(k=i;k < li->qtd-1; k++)
        li->dados[k] = li->dados[k+1];
    li->qtd--;
    return 1;
}

int consulta_lista_posicao(Lista* li, int pos, struct aluno *al){
    if (li == NULL || pos<= 0 || pos > li->qtd)
        return 0;
    *al = li->dados[pos-1];// MOTIFICA O CONTEUDO [*] - E POS-1 PQ O USARIO SEMPRE DIGITA A POSI, MAS COMEÇA POR 0
    return 1;
}

int consulta_lista_conteudo(Lista* li, int cont, struct aluno *al){
    if (li == NULL) return 0;
    int i=0;
    while (i < li->qtd && li->dados[i].matricula != cont)
        i++;
    if(i == li->qtd)// ELEMENTO NAO ENCONTRADO
        return 0;
    *al = li->dados[i];
    return 1;
}

void imprime_lista (Lista* li){
    if(li == NULL) return;
    int i;
    for(i=0;i < li->qtd; i++){
        printf("\nMatricula: %d\n",li->dados[i].matricula);
        printf("\nNome: %s\n",li->dados[i].nome);
        printf("\nNotas: %f %f %f\n",li->dados[i].n1, li->dados[i].n2, li->dados[i].n3);
        printf("________________________________\n");
    }

}
