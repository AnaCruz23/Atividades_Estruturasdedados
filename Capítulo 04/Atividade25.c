#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BONUS_TEMPORADA 500

typedef struct {
    int id;
    char jogador[50];
    int pontuacao;
} Partida;

typedef struct {
    Partida *partidas; // Vetor dinâmico
    int quantidade;    // Quantidade atual de partidas salvas na memória RAM
} Temporada;

// Registra uma nova partida em modo 'append' (anexar ao final)
void adicionarPartidaAoHistorico(const char *nomeArquivo, Partida p) {
    FILE *arquivo = fopen(nomeArquivo, "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para registrar a partida!\n");
        return;
    }

    fprintf(arquivo, "%d %s %d\n", p.id, p.jogador, p.pontuacao);
    fclose(arquivo);
    printf("Partida do jogador '%s' anexada ao histórico com sucesso!\n", p.jogador);
}

// Exibe o histórico de texto com validações de leitura
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

    while ((resultadoLeitura = fscanf(arquivo, "%d %s %d", &p.id, p.jogador, &p.pontuacao)) == 3) {
        totalRegistros++;
        printf("[%d] ID: %d | Jogador: %-10s | Pontuação: %d\n", totalRegistros, p.id, p.jogador, p.pontuacao);
    }

    if (resultadoLeitura != EOF) {
        printf("\n[ALERTA] Foi encontrado um dado malformado ou corrompido no arquivo!\n");
    }

    if (totalRegistros == 0) {
        printf("O histórico de partidas está vazio.\n");
    } else {
        printf("------------------------------------------------------\n");
        printf("Total de partidas registradas no histórico: %d\n", totalRegistros);
    }

    printf("======================================================\n\n");
    fclose(arquivo);
}

// Faz a leitura simples de teste do arquivo de histórico
void recuperacaoDados() {
    FILE *arquivo = fopen("historico_partidas.txt", "r");
    Partida p;

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura!\n");
        return;
    }

    printf("\n== Dados recuperados do arquivo ==\n");
    while (fscanf(arquivo, "%d %s %d", &p.id, p.jogador, &p.pontuacao) == 3) {
        printf("ID: %d | Jogador: %s | Pontos: %d\n", p.id, p.jogador, p.pontuacao);
    }
    fclose(arquivo);
}

// Processa o relatório applying o bônus de temporada
void processarRelatorioTemporada(const char *caminhoOrigem, const char *caminhoDestino) {
    FILE *arquivoOrigem = fopen(caminhoOrigem, "r");

    if (arquivoOrigem == NULL) {
        printf("[ERRO CRÍTICO] Não foi possível abrir o arquivo de origem '%s'.\n", caminhoOrigem);
        return;
    }

    FILE *arquivoDestino = fopen(caminhoDestino, "w");

    if (arquivoDestino == NULL) {
        printf("[ERRO CRÍTICO] Não foi possível criar o arquivo de destino '%s'.\n", caminhoDestino);
        fclose(arquivoOrigem);
        return;
    }

    Partida p;
    int registrosProcessados = 0;

    printf("\n--- INICIANDO PROCESSAMENTO DE FIM DE TEMPORADA ---\n");

    while (fscanf(arquivoOrigem, "%d %s %d", &p.id, p.jogador, &p.pontuacao) == 3) {
        int pontuacaoAntiga = p.pontuacao;
        p.pontuacao += BONUS_TEMPORADA;

        fprintf(arquivoDestino, "%d %s %d\n", p.id, p.jogador, p.pontuacao);
        registrosProcessados++;

        printf("Processado: %s | Pontos Antigos: %d -> Com Bônus: %d\n", 
               p.jogador, pontuacaoAntiga, p.pontuacao);
    }

    fclose(arquivoOrigem);
    fclose(arquivoDestino);

    printf("---------------------------------------------------\n");
    printf("Processamento concluído! Total de registros atualizados: %d\n", registrosProcessados);
    printf("Relatório final gerado com sucesso em '%s'.\n\n", caminhoDestino);
}

// Grava apenas UMA estrutura Partida individual em modo binário
void salvarPartidaBinario(const char *nomeArquivo, const Partida *p) {
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        printf("[ERRO] Falha ao criar arquivo binário individual.\n");
        return;
    }
    fwrite(p, sizeof(Partida), 1, arquivo);
    fclose(arquivo);
}

// Lê apenas UMA estrutura Partida individual de um arquivo binário
void carregarPartidaBinario(const char *nomeArquivo, Partida *p) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        printf("[ERRO] Falha ao abrir arquivo binário para leitura.\n");
        return;
    }
    fread(p, sizeof(Partida), 1, arquivo);
    fclose(arquivo);
}

// Compara o objeto original com o restaurado via binário
void compararPartidas(const Partida *original, const Partida *restaurada) {
    printf("\n=== COMPARAÇÃO DE DADOS (ORIGINAL vs RESTAURADO) ===\n");
    
    int idIgual = (original->id == restaurada->id);
    int nomeIgual = (strcmp(original->jogador, restaurada->jogador) == 0);
    int pontosIgual = (original->pontuacao == restaurada->pontuacao);

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

// Cadastra uma nova partida no vetor dinâmico da memória RAM
void cadastrarPartida(Temporada *temp) {
    int novaQtd = temp->quantidade + 1;
    
    Partida *novoVetor = realloc(temp->partidas, novaQtd * sizeof(Partida));
    if (novoVetor == NULL) {
        printf("[ERRO] Falha ao alocar memória para a nova partida!\n");
        return;
    }

    temp->partidas = novoVetor;
    Partida *nova = &temp->partidas[temp->quantidade];

    nova->id = temp->quantidade + 101; // Gera ID dinâmico

    printf("\n--- CADASTRAR NOVA PARTIDA ---\n");
    printf("Nome do Jogador (sem espaços): ");
    scanf("%49s", nova->jogador);

    printf("Pontuação obtida: ");
    scanf("%d", &nova->pontuacao);

    temp->quantidade = novaQtd;
    printf("[SUCESSO] Partida registrada na memória RAM!\n");
}

// Listar todas as partidas carregadas na memória RAM
void listarPartidas(const Temporada *temp) {
    printf("\n=================== TEMPORADA ATUAL ===================\n");
    if (temp->quantidade == 0 || temp->partidas == NULL) {
        printf("Nenhuma partida registrada na memória RAM no momento.\n");
        printf("=======================================================\n\n");
        return;
    }

    for (int i = 0; i < temp->quantidade; i++) {
        printf("[%d] ID: %d | Jogador: %-12s | Pontos: %d\n", 
               i + 1, temp->partidas[i].id, temp->partidas[i].jogador, temp->partidas[i].pontuacao);
    }
    printf("-------------------------------------------------------\n");
    printf("Total de partidas na memória: %d\n", temp->quantidade);
    printf("=======================================================\n\n");
}

// Salva o vetor inteiro da temporada no arquivo binário
void salvarTemporadaBinario(const char *nomeArquivo, const Temporada *temp) {
    if (temp->quantidade == 0 || temp->partidas == NULL) {
        printf("[AVISO] Nenhuma partida para salvar.\n");
        return;
    }

    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        printf("[ERRO] Não foi possível abrir o arquivo para escrita.\n");
        return;
    }

    size_t qtdEscrita = fwrite(&temp->quantidade, sizeof(int), 1, arquivo);
    if (qtdEscrita != 1) {
        printf("[ERRO] Falha ao gravar a quantidade de registros.\n");
        fclose(arquivo);
        return;
    }

    size_t itensEscritos = fwrite(temp->partidas, sizeof(Partida), temp->quantidade, arquivo);

    if (itensEscritos == (size_t)temp->quantidade) {
        printf("[SUCESSO] Temporada salva! (%d partidas gravadas no arquivo '%s')\n", 
               temp->quantidade, nomeArquivo);
    } else {
        printf("[ERRO] Falha ao gravar as partidas no arquivo.\n");
    }

    fclose(arquivo);
}

// Carrega o vetor de temporada a partir do arquivo binário
void carregarTemporadaBinario(const char *nomeArquivo, Temporada *temp) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        printf("[ERRO] Arquivo de save '%s' não encontrado.\n", nomeArquivo);
        return;
    }

    int qtdNoArquivo = 0;
    size_t lidosQtd = fread(&qtdNoArquivo, sizeof(int), 1, arquivo);

    if (lidosQtd != 1 || qtdNoArquivo <= 0) {
        printf("[ERRO] Arquivo de save vazio, inválido ou corrompido!\n");
        fclose(arquivo);
        return;
    }

    Partida *vetorTemporario = (Partida *)malloc(qtdNoArquivo * sizeof(Partida));
    if (vetorTemporario == NULL) {
        printf("[ERRO] Memória insuficiente para carregar as partidas!\n");
        fclose(arquivo);
        return;
    }

    size_t partidasLidas = fread(vetorTemporario, sizeof(Partida), qtdNoArquivo, arquivo);

    if (partidasLidas != (size_t)qtdNoArquivo) {
        printf("[ERRO] Leitura incompleta! Esperava %d registros, mas leu %zu.\n", 
               qtdNoArquivo, partidasLidas);
        free(vetorTemporario);
        fclose(arquivo);
        return;
    }

    if (temp->partidas != NULL) {
        free(temp->partidas);
    }

    temp->partidas = vetorTemporario;
    temp->quantidade = qtdNoArquivo;

    fclose(arquivo);
    printf("[SUCESSO] %d partidas restauradas com sucesso do arquivo!\n", temp->quantidade);
}

// Libera memória alocada dinamicamente
void liberarTemporada(Temporada *temp) {
    if (temp->partidas != NULL) {
        free(temp->partidas);
        temp->partidas = NULL;
    }
    temp->quantidade = 0;
}

int main() {
    const char *caminhoHistorico = "historico_partidas.txt";
    const char *origem = "historico_partidas.txt";
    const char *destino = "relatorio_temporada_final.txt";
    const char *caminhoBinario = "savegame.bin";
    const char *arquivoSave = "temporada_save.bin";
    
    Temporada temporadaAtual = {NULL, 0};
    int opcao = 0;

    do {
        printf("\n======= GERENCIADOR DE TEMPORADA =======\n");
        printf("1. Cadastrar nova partida\n");
        printf("2. Listar partidas na memória\n");
        printf("3. Salvar temporada em arquivo (.bin)\n");
        printf("4. Carregar temporada do arquivo (.bin)\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarPartida(&temporadaAtual);
                break;
            case 2:
                listarPartidas(&temporadaAtual);
                break;
            case 3:
                salvarTemporadaBinario(arquivoSave, &temporadaAtual);
                break;
            case 4:
                carregarTemporadaBinario(arquivoSave, &temporadaAtual);
                break;
            case 5:
                printf("Saindo do menu...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);

    // Executa testes adicionais de gravação e leitura
    exibirHistoricoCompleto(caminhoHistorico);
    processarRelatorioTemporada(origem, destino);

    Partida partidaOriginal = {501, "MestreGame", 9850};
    Partida partidaRestaurada = {0, "", 0};

    salvarPartidaBinario(caminhoBinario, &partidaOriginal);
    carregarPartidaBinario(caminhoBinario, &partidaRestaurada);
    compararPartidas(&partidaOriginal, &partidaRestaurada);
    
    recuperacaoDados();


    liberarTemporada(&temporadaAtual);

    return 0;
}