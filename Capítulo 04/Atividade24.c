


#include <stdio.h>
#include <stdio.h>

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

// Função para SALVAR em binário
void salvarPartidaBinario(const char *nomeArquivo, const Partida *p) {
    // REQUISITO: Usar o modo "wb" (escrita binária)
    FILE *arquivo = fopen(nomeArquivo, "wb");

    if (arquivo == NULL) {
        printf("[ERRO] Não foi possível criar o arquivo binário para escrita.\n");
        return;
    }

    // REQUISITO: Usar fwrite, sizeof e conferir a quantidade escrita
    // Escrevemos 1 bloco do tamanho da struct Partida
    size_t gravados = fwrite(p, sizeof(Partida), 1, arquivo);

    if (gravados == 1) {
        printf("Partida gravada em binário com sucesso! (%zu bytes escritos)\n", sizeof(Partida));
    } else {
        printf("[ERRO] Falha ao gravar a estrutura no arquivo.\n");
    }

    fclose(arquivo);
}

// Função para LER e RESTAURAR do binário
void carregarPartidaBinario(const char *nomeArquivo, Partida *pDestino) {
    // REQUISITO: Usar o modo "rb" (leitura binária)
    FILE *arquivo = fopen(nomeArquivo, "rb");

    // REQUISITO: Detectar arquivo inexistente
    if (arquivo == NULL) {
        printf("[ERRO] Arquivo binário não encontrado.\n");
        return;
    }

    // REQUISITO: Usar fread, sizeof e conferir a quantidade lida
    size_t lidos = fread(pDestino, sizeof(Partida), 1, arquivo);

    // REQUISITO: Detectar arquivo vazio ou registro incompleto
    if (lidos < 1) {
        if (feof(arquivo)) {
            printf("[AVISO] O arquivo binário está vazio ou incompleto!\n");
        } else {
            printf("[ERRO] Falha de leitura durante a restauração do registro.\n");
        }
    } else {
        printf("Registro lido e reconstruído com sucesso a partir do binário!\n");
    }

    fclose(arquivo);
}

// Função para comparar a estrutura original com a restaurada
void compararPartidas(const Partida *original, const Partida *restaurada) {
    printf("\n=== COMPARAÇÃO DE DADOS (ORIGINAL vs RESTAURADO) ===\n");
    
    int idIgual = (original->id == restaurada->id);
    int nomeIgual = (strcmp(original->jogador, restaurada->jogador) == 0);
    int pontosIgual = (original->pontuacao == restaurada->pontuacao);

    // REQUISITO: Exibir o objeto reconstruído
    printf("Original   -> ID: %d | Jogador: %-10s | Pontos: %d\n", 
           original->id, original->jogador, original->pontuacao);
    printf("Restaurado -> ID: %d | Jogador: %-10s | Pontos: %d\n", 
           restaurada->id, restaurada->jogador, restaurada->pontuacao);

    if (idIgual && nomeIgual && pontosIgual) {
        printf("RESULTADO: [SUCESSO] Todos os campos correspondem perfeitamente!\n");
    } else {
        printf("RESULTADO: [ERRO] Houve divergência nos dados restaurados.\n");
    }
    printf("===================================================\n\n");
}




int main (){
    const char *caminhoHistorico = "historico_partidas.txt";
    const char *origem = "historico_partidas.txt";
    const char *destino = "relatorio_temporada_final.txt";
    const char *caminhoBinario = "savegame.bin";

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

    // Partida original na memória
    Partida partidaOriginal = {501, "MestreGame", 9850};
    
    // Partida vazia que receberá os dados lidos do arquivo binário
    Partida partidaRestaurada = {0, "", 0};

    // 1. Grava no disco em formato binário
    salvarPartidaBinario(caminhoBinario, &partidaOriginal);

    // 2. Lê do disco e reconstrói na estrutura de destino
    carregarPartidaBinario(caminhoBinario, &partidaRestaurada);

    // 3. Compara o objeto reconstruído com o original
    compararPartidas(&partidaOriginal, &partidaRestaurada);

    recuperacaoDados ();

    return 0;

}