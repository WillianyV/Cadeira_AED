#include <stdio.h>
#include <stdlib.h>

#define MAX 4
struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};
struct fila{
    int inicio, final, qtd;
    struct aluno dados[MAX];
};
typedef struct fila Fila;

Fila* cria_Fila();
void libera_Fila(Fila* fi);
int consulta_Fila(Fila* fi, struct aluno *al);
int insere_Fila(Fila* fi, struct aluno al);
int remove_Fila(Fila* fi);
int tamanho_Fila(Fila* fi);
int Fila_vazia(Fila* fi);
int Fila_cheia(Fila* fi);
void imprime_Fila(Fila* fi);

int main(){
    struct aluno al,a[4] = {{2,"Andre",9.5,7.8,8.5},
                         {4,"Ricardo",7.5,8.7,6.8},
                         {1,"Bianca",9.7,6.7,8.4},
                         {3,"Ana",5.7,6.1,7.4}};
    Fila* fi = cria_Fila();
    printf("Tamanho: %d\n\n\n\n",tamanho_Fila(fi));
    int i;
    for(i=0; i < 4; i++){
        insere_Fila(fi,a[i]);
    }

    imprime_Fila(fi);
    printf("\ntamanho: %d\n\n",tamanho_Fila(fi));

    consulta_Fila(fi,&al);
    printf("\nConsulta: %d \t %s\n\n",al.matricula,al.nome);


    for(i=0; i < 4; i++){
        consulta_Fila(fi,&al);
        printf("Remove primeiro elem: %d \t %s\n\n",al.matricula,al.nome);
        remove_Fila(fi);
        printf("Tamanho: %d\n\n",tamanho_Fila(fi));
        imprime_Fila(fi);
   }

    for(i=0; i < 4; i++)
        insere_Fila(fi,a[i]);

    imprime_Fila(fi);
    printf("Tamanho: %d\n\n\n\n",tamanho_Fila(fi));


    libera_Fila(fi);
    system("pause");
    return 0;
}

Fila* cria_Fila(){
    Fila *fi;
    fi = (Fila*) malloc(sizeof(struct fila));
    if(fi != NULL){
        fi->inicio = 0;
        fi->final = 0;
        fi->qtd = 0;
    }
    return fi;
}

void libera_Fila(Fila* fi){
    free(fi);
}

int consulta_Fila(Fila* fi, struct aluno *al){//SÓ TEM ACESSO AO PRIMEIRO ELEMENTO DA FILA
    if(fi == NULL || Fila_vazia(fi))
        return 0;
    *al = fi->dados[fi->inicio];// O 'CONTEUDO' DA STRUCT IRA RECEBE OS DADOS, QUE ESTAO NO INICIO DA FILA
    return 1;
}

int insere_Fila(Fila* fi, struct aluno al){//SEMPRE NO FINAL
    if(fi == NULL)//VERIFICA SE A FILA  FOI ALOCADA
        return 0;
    if(Fila_cheia(fi))//VERIFICA SE A FILA EXISTE
        return 0;
    fi->dados[fi->final] = al;//NO VETOR DADOS, E NA POSIÇAO FINAL DELA, VAMOS INSERIR OS DADOS
    fi->final = (fi->final+1)%MAX;// O FINAL VAI APONTAR PARA O PROXI, SE A DIVISAO POR MAX = 0, VOLTA PARA O 1ª ELEMEN,(%MAX) = TIPO CICURLAR
    fi->qtd++;//SOMA MAIS UM DADOS
    return 1;
}

int remove_Fila(Fila* fi){//REMOVE DO INCIO
    if(fi == NULL || Fila_vazia(fi))
        return 0;
    fi->inicio = (fi->inicio+1)%MAX;//ANDAR COM O INCIO
    fi->qtd--;//RETIRA O DADO
    return 1;
}

int tamanho_Fila(Fila* fi){
    if(fi == NULL)//VERIFICA SE A FILA FOI ALOCADA
        return -1;
    return fi->qtd;//ACESSAR CAMPO QUANTIDADE
}

int Fila_cheia(Fila* fi){
    if(fi == NULL)//VERIFICA SE A FILA FOI ALOCADA
        return -1;
    if (fi->qtd == MAX)//VERIFICA SE A QUANTIDA ESTA IGUAL A MAX, ENTAO A FILA ESTA CHEIA
        return 1;
    else
        return 0;
}

int Fila_vazia(Fila* fi){
    if(fi == NULL)
        return -1;
    if (fi->qtd == 0)// SE A QUANTIDADE EH IGUAL A 0
        return 1;//ENTAO EH VAZIA
    else
        return 0;
}

void imprime_Fila(Fila* fi){
    if(fi == NULL)
        return;
    int n, i = fi->inicio;
    for(n=0; n < fi->qtd; n++){
        printf("Matricula: %d\n",fi->dados[i].matricula);
        printf("Nome: %s\n",fi->dados[i].nome);
        printf("Notas: %f %f %f\n",fi->dados[i].n1,
                                   fi->dados[i].n2,
                                   fi->dados[i].n3);
        printf("-------------------------------\n");
        i = (i + 1) % MAX;
    }
}
