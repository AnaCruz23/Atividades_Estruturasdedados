#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VIDA_MAXIMA 100
#define EQUIPE 10

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

//Modificar Vida (Valida ponteiro nulo e limites [0, VIDA_MAXIMA])
void aplicar_dano(Personagem *p, int dano) {
    if (p == NULL) {
        printf("Erro: Ponteiro nulo passado para aplicar_dano!\n");
        return;
    }
    
    // Acesso com sintaxe ->
    p->vida -= dano;

    // Regra de Negócio: Impedir vida negativa
    if (p->vida < 0) {
        p->vida = 0;
    }
}
void curar_personagem(Personagem *p, int cura) {
    if (p == NULL) {
        printf("Erro: Ponteiro nulo passado para curar_personagem!\n");
        return;
    }

    // DEMONSTRAÇÃO PEDIDA: Expressão equivalente (*p).membro
    (*p).vida += cura;

    // Regra de Negócio: Impedir vida superior ao máximo
    if ((*p).vida > VIDA_MAXIMA) {
        (*p).vida = VIDA_MAXIMA;
    }
}

//Modificar Posição (Valida ponteiro nulo)
void avancar_posicao(Personagem *p, int passos) {
    if (p == NULL) {
        printf("Erro: Ponteiro nulo passado para avancar_posicao!\n");
        return;
    }
    if (passos < 0) {
        printf("Erro: Numero de passos invalido!\n");
        return;
    }

    p->pos += passos;
}
// Modificar Pontuação (Valida ponteiro nulo)
void adicionar_pontos(Personagem *p, int pontos) {
    if (p == NULL) {
        printf("Erro: Ponteiro nulo passado para adicionar_pontos!\n");
        return;
    }
    if (pontos < 0) {
        printf("Erro: Pontuacao invalida!\n");
        return;
    }

    p->pontuacao += pontos;
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
// Comparação (questão 19)
void ordenar (Personagem x[], int total){
    int comparacao=0;
    
    for(int i=0; i<total -1;i++){
        int menor=i;

        for(int j=i +1; j<total;j++){
            comparacao++;
            if(x[j].id < x[menor].id){
                menor=j;
            }
        }

        if(menor !=i){
            Personagem t=x[i];
            x[i]= x[menor];
            x[menor]=t;
        }
    }
    printf("Total comparções:%d\n",comparacao);
}

int main() {

   // Equipe
    Personagem equipe[EQUIPE] = {
        {"Ana",  100, 0, 0.0f, 0.0f, 42, 15, 10},
        {"João",  80, 0, 0.0f, 0.0f, 10, 20, 12},
        {"Maria",  90, 0, 0.0f, 0.0f,  7, 18, 15},
     };

     int e_total=3;
     int capacidade_atual = 0; // quantidade de jogadores
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
    printf("\n=== APLICANDO OPERACOES VIA PONTEIRO ===\n"); // ( atividade 18) Utilizando ponteiros para aplicação

    // Passamos o ENDEREÇO do elemento usando o operador &
    aplicar_dano(&catalogo[0], 40);     
    avancar_posicao(&catalogo[0], 5);     
    adicionar_pontos(&catalogo[0], 250);  

    printf("\n=== ESTADO DO PERSONAGEM APOS A ALTERACAO ===\n");
    exibir_ficha_personagem (catalogo [0]);
    // testando o limite superior de cura
    curar_personagem (&catalogo[0], 100);

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

    printf ( "\n Antes da Ordenação\n"); // Antes da ordenação
      for (int i = 0; i < e_total; i++) {
        printf("| Id: %2d \n| Nome: %s\n", equipe[i].id, equipe[i].nome);
    }
    ordenar (equipe,e_total); // chamamento da função
    
    printf ("\nApós ordenação:\n"); // depois da ordenação
     for (int i = 0; i < e_total; i++) {
        printf("| Id: %2d \n| Nome: %s\n", equipe[i].id, equipe[i].nome);

    // Testando a validação de Ponteiro Nulo
    printf("\n--- Teste de Seguranca: Enviolando Ponteiro Nulo ---\n");
    Personagem *ptr_nulo = NULL;
    aplicar_dano(ptr_nulo, 50); // Deve exibir mensagem de erro e nao crashar o programa

    free(catalogo);

    catalogo = NULL; 
     return 0;
}