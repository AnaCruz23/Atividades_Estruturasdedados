
//Contexto: O catálogo ainda não possui um tipo completo para os personagens, mas precisa preparar um armazenamento que possa crescer à medida que novos registros forem incluídos.
//Descrição detalhada: Crie a base do programa usando calloc para reservar um vetor inicialmente zerado. Permita aumentar ou reduzir sua capacidade com realloc, sempre preservando o bloco original em caso de erro. Mostre ao usuário a capacidade anterior e a nova.
//Requisitos:
//- reservar a capacidade inicial com calloc;
//- demonstrar que as posições começam zeradas;
//- validar a nova capacidade;
//- usar um ponteiro temporário ao chamar realloc;
//- inicializar as posições acrescentadas;
//- liberar o vetor antes de encerrar.

#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int id;
  int nivel;
} Personagem;

int main (){

    int capacidade_atual=3;
    int nova_capacidade;

    Personagem *catalogo = (Personagem*) calloc (capacidade_atual, sizeof (Personagem));
    if ( catalogo == NULL){
        printf ("Erro no sistema\n");
        return 1; // encerra o programa em caso de falha
    }

    // Demonstrar que as posições começam zeradas
    printf ("\n=== ESTADO INICIAL DO CATÁLOGO===\n");
    for (int i=0; i< capacidade_atual; i++){
        printf ("Personagem [%d] -> id: %d, Nível: %d\n",i, catalogo[i].id, catalogo [i].nivel);
    }
    // Validar a nova capacidade informada
    do{
       printf ("Digite a nova capacidade");
       scanf ("%d", &nova_capacidade);
       if (nova_capacidade <= 0){
         printf ("Capacidade inválida\n");
    }
    }while (nova_capacidade <=0); // rodar esse loop até essa condição ser verdadeira
    
    // Utilizar um ponteiro temporário para evitar problemas maiores
     Personagem *temp= realloc (catalogo, nova_capacidade *sizeof (Personagem));
    
     if (temp == NULL){
        printf ("Erro de alocação\n");
        return 1;
    } else{
        catalogo = temp; // atualiza o ponteiro principal com o novo endereço
        printf ("\n Capacidade alterada com sucesso!\n");
        printf ("\n Capacidade anterior: %d | Nova capacidade: %d", capacidade_atual, nova_capacidade); 
    }

    if ( nova_capacidade > capacidade_atual){
        for (int i= capacidade_atual; i< nova_capacidade; i++){
            catalogo [i].id=0;
            catalogo [i].nivel= 0;
        }

    }

    // Atualização da capacidade atual do vetor
    capacidade_atual= nova_capacidade;

    printf ("\n === ESTADO FINAL DO CATÁLOGO==\n");
    for (int i=0; i< capacidade_atual; i++){
        printf ("Posição [%d]->id: %d | Nível: %d \n", i, catalogo[i].id, catalogo[i].nivel);
    }

    free (catalogo);

    catalogo = NULL;
    
    return 0;
}
