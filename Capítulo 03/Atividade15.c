

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  int id;
  int nivel;
  char nome [10];
  int vida;
  int pontuacao;
  int pos;
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
    catalogo [0].id = 1;
    catalogo [0].nivel = 1;
    catalogo [0].vida = 100;
    catalogo [0].pontuacao = 0;
    catalogo [0].pos = 10;
    strcpy (catalogo[0].nome, "Herói");

    
    printf ("\n== ESTADO INICIAL DO JOGADOR==\n");
    printf ("Nome do jogador: %s| Pontuação: %d | Posição inicial: %d", catalogo[0].nome, catalogo[0].pontuacao, catalogo[0].pos);

    printf ("\n== JOGADOR SOFRENDO DANOS, ALTERANDO VIDA E POSIÇÃO ===\n");
    catalogo [0].vida -=30;
    catalogo [0].pontuacao += 150;
    catalogo [0].pos += 5;

    if (catalogo[0].vida <0){
        catalogo[0].vida =0; // validação do limite
    }

    printf ("\n=== ESTADO DO JOGADOR APÓS A ALTERAÇÃO===\n");
    printf ("Nome: %s | id= %d | Vida: %d | Pontos: %d | posição: %d\n", catalogo[0].nome, catalogo [0].id, catalogo[0].vida, catalogo[0].pontuacao, catalogo[0].pos);

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
    // Inicializar posições acrescentadas
    if ( nova_capacidade > capacidade_atual){
        for (int i= capacidade_atual; i< nova_capacidade; i++){
           
            catalogo [i].id=0;
            catalogo [i].nivel= 0;
            catalogo [i].vida =100;
            catalogo[i].pontuacao =0;
            catalogo [i].pos=0;
            strcpy (catalogo [i].nome, "Herói");
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
    // evita o Dangling Pointer (ponteiro solto) e 
    //evita modificar a memória de forma silenciosa e 
    //imprevisível (o que seria uma corrupção de dados difícil de encontrar).
    
    return 0;
}
