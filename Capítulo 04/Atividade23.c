#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int id;
    char jogador [50];
    int pontuacao;
} Partida;

#define BONUS_TEMPORADA 500

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

void processarRelatorioTemporada(const char *caminhoOrigem, const char *caminhoDestino) {
    // 1. REQUISITO: Tentar abrir o arquivo de origem
    FILE *arquivoOrigem = fopen(caminhoOrigem, "r");

    // REQUISITO: Verificar retorno e emitir mensagem específica para falha de origem
    if (arquivoOrigem == NULL) {
        printf("[ERRO CRÍTICO] Não foi possível abrir o arquivo de origem '%s'.\n", caminhoOrigem);
        printf("Verifique se o arquivo realmente existe no pasta do projeto.\n");
        return; // Nenhum arquivo precisa ser fechado aqui, pois a origem falhou
    }

    // 2. REQUISITO: Tentar abrir o arquivo de destino
    FILE *arquivoDestino = fopen(caminhoDestino, "w");

    // REQUISITO: Verificar retorno e emitir mensagem específica para falha de destino
    if (arquivoDestino == NULL) {
        printf("[ERRO CRÍTICO] Não foi possível criar o arquivo de destino '%s'.\n", caminhoDestino);
        printf("Verifique permissões de escrita na pasta.\n");
        
        // REQUISITO: Fechar o arquivo que já havia sido aberto com sucesso
        fclose(arquivoOrigem);
        return;
    }

    Partida p;
    int registrosProcessados = 0;

    printf("\n--- INICIANDO PROCESSAMENTO DE FIM DE TEMPORADA ---\n");

    // REQUISITO: Processar cada registro apenas quando a leitura for completa (retorno == 3)
    while (fscanf(arquivoOrigem, "%d %s %d", &p.id, p.jogador, &p.pontuacao) == 3) {
        
        // Aplica a regra de bonificação
        int pontuacaoAntiga = p.pontuacao;
        p.pontuacao += BONUS_TEMPORADA;

        // REQUISITO: Escrever os dados transformados no arquivo de destino
        fprintf(arquivoDestino, "%d %s %d\n", p.id, p.jogador, p.pontuacao);

        registrosProcessados++;

        printf("Processado: %s | Pontos Antigos: %d -> Com Bônus: %d\n", 
               p.jogador, pontuacaoAntiga, p.pontuacao);
    }

    // REQUISITO: Fechar os dois arquivos no caminho de sucesso
    fclose(arquivoOrigem);
    fclose(arquivoDestino);

    // REQUISITO: Apresentar a quantidade de registros processados
    printf("---------------------------------------------------\n");
    printf("Processamento concluído! Total de registros atualizados: %d\n", registrosProcessados);
    printf("Relatório final gerado com sucesso em '%s'.\n\n", caminhoDestino);
}

int main (){
    const char *caminhoHistorico = "historico_partidas.txt";
    const char *origem = "historico_partidas.txt";
    const char *destino = "relatorio_temporada_final.txt";

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
    // Executa a transformação
    processarRelatorioTemporada(origem, destino);

    recuperacaoDados ();

    return 0;

}