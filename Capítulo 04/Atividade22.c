#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int id;
    char jogador [50];
    int pontuacao;
} Partida;

 void adicionarPartidaAoHistorico(const char *nomeArquivo, Partida p) {
    // Modo "a" abre para escrita mantendo o conteúdo existente
    FILE *arquivo = fopen(nomeArquivo, "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para registrar a partida!\n");
        return;
    }

    // Grava a nova partida no final do arquivo
    fprintf(arquivo, "%d %s %d\n", p.id, p.jogador, p.pontuacao);
    
    fclose(arquivo);
    printf("Partida do jogador '%s' anexada ao histórico com sucesso!\n", p.jogador);
}


void exibirHistoricoCompleto(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Nenhum histórico encontrado ainda (arquivo não existe).\n");
        return;
    }

    Partida p;
    int totalRegistros = 0;
    int resultadoLeitura;

    printf("\n================ HISTÓRICO DE PARTIDAS ================\n");

    // REQUISITO: Basear o laço no retorno do fscanf diretamente
    // Lemos até a leitura não retornar mais exatamente 3 campos
    while ((resultadoLeitura = fscanf(arquivo, "%d %s %d", &p.id, p.jogador, &p.pontuacao)) == 3) {
        totalRegistros++; // REQUISITO: Contar registros lidos
        printf("[%d] ID: %d | Jogador: %-10s | Pontuação: %d\n", totalRegistros, p.id, p.jogador, p.pontuacao);
    }

    // REQUISITO: Diferenciar fim normal de dado malformado
    if (resultadoLeitura != EOF) {
        printf("\n[ALERTA] Foi encontrado um dado malformado ou corrompido no arquivo!\n");
    }

    // REQUISITO: Informar quando o histórico estiver vazio
    if (totalRegistros == 0) {
        printf("O histórico de partidas está vazio.\n");
    } else {
        printf("------------------------------------------------------\n");
        printf("Total de partidas registradas no histórico: %d\n", totalRegistros);
    }

    printf("======================================================\n\n");

    fclose(arquivo);
}

void recuperacaoDados (){
    FILE *arquivo;
    Partida p;
    arquivo = fopen ("historico_partidas.txt", "r");

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
    const char *caminhoHistorico = "historico_partidas.txt";

    // Simulando 3 partidas jogadas em momentos diferentes
    Partida p1 = {101, "Alex", 1200};
    Partida p2 = {102, "Beatriz", 2500};
    Partida p3 = {103, "Carlos", 1850};

    // Anexando cada partida (como se o jogo estivesse rodando e salvando ao fim de cada fase)
    adicionarPartidaAoHistorico(caminhoHistorico, p1);
    adicionarPartidaAoHistorico(caminhoHistorico, p2);
    adicionarPartidaAoHistorico(caminhoHistorico, p3);

    // Exibindo o histórico acumulado completo
    exibirHistoricoCompleto(caminhoHistorico);

    recuperacaoDados ();

    return 0;

}