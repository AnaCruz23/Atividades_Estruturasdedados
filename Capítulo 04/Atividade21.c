#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int id;
    char jogador [50];
    int pontuacao;
} Partida;

 void gravacaoArquivo ( Partida p){
    FILE *arquivo;

    arquivo = fopen ("partida.txt", "w");

     if (arquivo ==NULL){
        printf ("Não há arquivo\n");
        return;
    }

    fprintf (arquivo, "%d %s %d\n", p.id, p.jogador, p.pontuacao);
    fclose (arquivo);
    printf ("Dados salvos com sucesso!\n");
}

void recuperacaoDados (){
    FILE *arquivo;
    Partida p;
    arquivo = fopen ("partida.txt", "r");

if (arquivo == NULL){
        printf ("Erro ao abrir o arquivo para leitura!\n");
        return;
    }

    printf ("\n== Dados recuperados do arquivo==\n");

    while (fscanf (arquivo, "%d %s %d", &p.id, p.jogador, &p.pontuacao)==3){
        printf ("ID: %d | Jogador: %s | Pontos: %d\n", p.id, p.jogador, p.pontuacao);
    }
    fclose (arquivo);
}

int main (){
    Partida minhaPartida= {1, "Jogador_1", 2500};

    gravacaoArquivo (minhaPartida);
    recuperacaoDados ();

    return 0;

}