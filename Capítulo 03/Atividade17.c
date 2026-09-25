#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id; // identificar o jogador
    int nivel;
    char nome[10];
    int vida;
    int pontuacao;
    int pos;
} Personagem;


Personagem criar_personagem(int id, int nivel, const char *nome, int vida, int pontuacao, int pos) {
    Personagem p; // Struct simples

    // Atribuição direta dos valores recebidos pelos parâmetros
    p.id = id; 
    p.nivel = nivel;
    p.vida = vida;
    p.pontuacao = pontuacao;
    p.pos = pos;

    strncpy(p.nome, nome, sizeof(p.nome) - 1);
    p.nome[sizeof(p.nome) - 1] = '\0'; // Garante o caractere nulo de término de string
    
    return p;
}
void exibir_ficha_personagem(Personagem p) {
    printf("--- [CONSULTA] FICHA DO PERSONAGEM ---\n");
    printf("ID: %d | Nome: %s | Nivel: %d | Vida: %d | Pontos: %d | Posicao: %d\n",
           p.id, p.nome, p.nivel, p.vida, p.pontuacao, p.pos); // o que estava no main vem para essa função
    printf("-------------------------------------\n\n");
}

//  Segunda função de consulta por valor (apenas calcula dados)
int calcular_poder_total(Personagem p) {
    // Exemplo de cálculo baseado nos atributos sem alterar o original
    return (p.nivel * 10) + (p.vida * 2) + p.pontuacao;
}

// Função de demonstração que altera a cópia local
void tentar_alterar_copia(Personagem p) {
    printf("\n>>> Entrando na funcao tentar_alterar_copia... <<<\n");
    
    // Alteração intencional na cópia local
    p.vida = 0;
    p.pontuacao = 9999;
    strcpy(p.nome, "MODIFICADO");

    printf("[DENTRO DA FUNCAO] Estado da Copia Local:\n");
    printf("Nome: %s | Vida: %d | Pontos: %d\n", p.nome, p.vida, p.pontuacao);
    printf(">>> Saindo da funcao tentar_alterar_copia... <<<\n\n");
}


int main() {

    
    Personagem p_teste = {.id = 99, .nivel = 5, .nome = "Herói", .vida = 80, .pontuacao = 300, .pos = 1}; // inicialização da struct

    printf("\n === INICIALIZACAO DESIGNADA SOMENTE PELA STRUCT ===\n");
    exibir_ficha_personagem (p_teste);
   
    
    int capacidade_atual = 3; // quantidade de jogadores
    int nova_capacidade;
    char buffer [20]; // Meu Vscode estava dando problema e decidi colocar o buffer para uma leitura segura

    Personagem *catalogo = (Personagem*) calloc(capacidade_atual, sizeof(Personagem));
    if (catalogo == NULL) {
        printf("Erro no sistema\n");
        return 1; // encerra o programa em caso de falha
    }
     //Recebendo a função no cátalogo para criar o personagem
    catalogo[0] = criar_personagem(1, 1, "Herói", 100, 0, 10); 
    
    printf("=== ESTADO INICIAL DO PRIMEIRO PERSONAGEM ===\n");
    exibir_ficha_personagem (catalogo [0]); // Foi substituído pela função
    
    printf("== ALTERACAO SEGURA DE NOME ==\n");
    printf("Digite o novo nome para o personagem [0] (max 9 letras): ");
  
    // leitura segura no teclado
    fgets(catalogo[0].nome, sizeof(catalogo[0].nome), stdin);
    // Remove a quebra de linha (\n) que o fgets insere no final do texto:
    catalogo[0].nome[strcspn(catalogo[0].nome, "\n")] = '\0';

    printf("\n === REGISTRO APOS A TROCA DE NOME ===\n");
    exibir_ficha_personagem (catalogo [0]);

    printf("== PERSONAGEM SOFRENDO DANOS, ALTERANDO VIDA E POSICAO ===\n");
    catalogo[0].vida -= 30;
    catalogo[0].pontuacao += 150;
    catalogo[0].pos += 5;

    if (catalogo[0].vida < 0) {
        catalogo[0].vida = 0; // validação do limite
    }

    printf("\n=== ESTADO DO PERSONAGEM APOS A ALTERACAO ===\n");
    exibir_ficha_personagem (catalogo [0]);

    printf("=== TESTE DE PASSAGEM POR VALOR ===\n"); // passagem por valor
    int poder = calcular_poder_total(catalogo[0]);
    printf("Poder Total Calculado (Consulta): %d\n", poder);

    // Alteracao intencional na copia
    tentar_alterar_copia(catalogo[0]); 
     
    do {
        printf("Digite a nova capacidade: ");
        fgets(buffer, sizeof(buffer), stdin); // Lê a linha inteira de forma segura
        nova_capacidade = atoi(buffer);        // Converte o texto lido para número inteiro

        if (nova_capacidade <= 0) {
            printf("Capacidade invalida!\n");
        }
    } while (nova_capacidade <= 0);
    
    // Utilizar um ponteiro temporário para evitar problemas maiores
    Personagem *temp = (Personagem*) realloc(catalogo, nova_capacidade * sizeof(Personagem));
    
    if (temp == NULL) {
        printf("Erro de alocacao\n");
        free(catalogo);
        return 1;
    } else {
        catalogo = temp; // atualiza o ponteiro principal com o novo endereço
        printf("\nCapacidade alterada com sucesso!\n");
        printf("Capacidade anterior: %d | Nova capacidade: %d\n", capacidade_atual, nova_capacidade); 
    }

    // Inicializar posições acrescentadas usando a função construtora
    if (nova_capacidade > capacidade_atual) {
        for (int i = capacidade_atual; i < nova_capacidade; i++) {
            catalogo[i] = criar_personagem(i + 1, 1, "Novo", 100, 0, 0);
        }
    }
    
    // Atualização da capacidade atual do vetor
    capacidade_atual = nova_capacidade;

    printf("\n === ESTADO FINAL DO CATALOGO ===\n");
    for (int i = 0; i < capacidade_atual; i++) {
        exibir_ficha_personagem (catalogo[i]); // Utilização da função
    }

    free(catalogo);

    catalogo = NULL; 
    // evita o Dangling Pointer (ponteiro solto) e 
    // evita modificar a memória de forma silenciosa e 
    // imprevisível (o que seria uma corrupção de dados difícil de encontrar).
    
    return 0;
}