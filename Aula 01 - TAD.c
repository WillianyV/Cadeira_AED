/*EXEMPLO DE TAD: UM PONTO DEFINIDO POR SUAS COORDENADAS 'X' E 'Y'
  CALCULA A DISTÂNCIA ENTRE DOIS PONTOS
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct ponto{
    float x;
    float y;
};
typedef struct ponto Ponto; // O STRUCT ponto, AGORA PASSA A SER CONHECIDA COMO Ponto;

//CRIA UM NOVO PONTO
Ponto* pto_cria(float x, float y); // EQUIVALENTE AO FOPEN
//LIBERA UM PONTOA
void pto_libera(Ponto* p);// EQUIVALENTE AO FCLOSE
//ACESSA OS VALORES 'X' E 'Y' A UM PONTO
void pto_acessa(Ponto* p, float* x, float* y);
//ATRIBUI OS VALORES 'X' E 'Y' A UM PONTO
void pto_atribui (Ponto* p, float x, float y);
//CALCULA A DISTÂNCIA ENTRE DOIS PONTOS
float pto_distancia(Ponto* p1, Ponto* p2);

int main()
{
    float d;
    Ponto *p, *q;
    p = pto_cria(10,21);// CRIA UM ESTRUTURA, PASSANDO OS VALORES 'X' E 'Y'
    q = pto_cria(7,25);// CRIA UMA 'NOVA' ESTRUTURA, PASSANDO X E Y
    d = pto_distancia(p,q);
    printf("\nDISTANCIA ENTRE DOIS PONTOS: %.2f\n",d);
    pto_libera(q);
    pto_libera(p);
    system("pause");
    return 0;
}

//CRIA UM NOVO PONTO
Ponto* pto_cria(float x, float y){
    Ponto* p = (Ponto*) malloc(sizeof(Ponto)); //ALOCANDO UM ESPAÇO NA MEMORIA PARA GUARDA 'X' E 'Y'
    if (p != NULL){ // SE MINHA ALOCAÇÃO DEU CERTO, ENTÃO:
        p->x = x; // ENTAO ATIBUI OS VALORES X E Y, DOS CAMPOS X E Y DO PONTO, OU SEJA,
        p->y = y; // COPIA OS VALORES PARA DENTRO DA ESTRUTURA;
    }
    return p;
}

//LIBERA UM PONTOA
void pto_libera(Ponto* p){
    free(p);
}

//RECUPERA, POR REFERÊNCIA, O VALOR DE UM PONTO
void pto_acessa(Ponto* p, float* x, float* y){
    *x = p->x; // TENHO UMA ESTRUTURA X E Y, NO MEU PONTEIRO P
    *y = p->y; // COPIA OS VALORES QUE ESTÃO NA ESTRUTURAS PARA REFÊRENCIAS
}

//ATRIBUI A UM PONTO AS COORDENADAS 'X' E 'Y'
void pto_atribui (Ponto* p, float x, float y){
    p->x = x; // COLOCA DENTRO DAS ESTRUTURAS OS VALORES;
    p->y = y;
}

//CALCULA A DISTÂNCIA ENTRE DOIS PONTOS
float pto_distancia(Ponto* p1, Ponto* p2){
    float dx = p1->x - p2->x;
    float dy = p1->y - p2->y;
    return sqrt (dx * dx + dy * dy);
}
