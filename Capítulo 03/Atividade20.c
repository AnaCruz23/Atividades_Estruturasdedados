#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VIDA_MAXIMA 100

// Enum para representar a classe
typedef enum {
    GUERREIRO = 1,
    MAGO,
    ARQUEIRO,
    CLERIGO
} ClassePersonagem;

// Struct Posicao para aninhar em Personagem
typedef struct {
    int x;
    int y;
} Posicao;

// Struct Personagem com Posicao aninhada
typedef struct {
    int id;
    int nivel;
    char nome[20];
    ClassePersonagem classe;
    int vida;
    int pontuacao;
    Posicao pos;
} Personagem;

// Struct Equipe para gerenciar o catálogo dinâmico
typedef struct {
    char nome_equipe[30];
    Personagem *membros;
    int quantidade;
    int capacidade;
} Equipe;

// Função para limpar o buffer de entrada do teclado
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Converter Enum para Texto Legível
const char* obter_nome_classe(ClassePersonagem classe) {
    switch (classe) {
        case GUERREIRO: return "Guerreiro";
        case MAGO:      return "Mago";
        case ARQUEIRO:  return "Arqueiro";
        case CLERIGO:   return "Clerigo";
        default:        return "Desconhecido";
    }
}

// Função para exibir único personagem
void exibir_personagem(Personagem p) {
    printf("ID: %-3d | Nome: %-12s | Classe: %-10s | Nivel: %-2d | Vida: %-3d | Pontos: %-5d | Pos: (%d, %d)\n",
           p.id, p.nome, obter_nome_classe(p.classe), p.nivel, p.vida, p.pontuacao, p.pos.x, p.pos.y);
}

// Construtor
Personagem criar_personagem(int id, int nivel, const char *nome, ClassePersonagem classe, int vida, int pontuacao, int x, int y) {
    Personagem p;
    p.id = id;
    p.nivel = nivel;
    p.classe = classe;
    p.vida = vida;
    p.pontuacao = pontuacao;
    p.pos.x = x;
    p.pos.y = y;

    strncpy(p.nome, nome, sizeof(p.nome) - 1);
    p.nome[sizeof(p.nome) - 1] = '\0';
    
    return p;
}

// Buscar índice por ID na Equipe
int buscar_indice_por_id(const Equipe *eq, int id) {
    for (int i = 0; i < eq->quantidade; i++) {
        if (eq->membros[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Cadastrar novo integrante na Equipe
void cadastrar_personagem(Equipe *eq) {
    if (eq->quantidade == eq->capacidade) {
        int nova_cap = eq->capacidade == 0 ? 2 : eq->capacidade * 2;
        Personagem *temp = (Personagem*) realloc(eq->membros, nova_cap * sizeof(Personagem));
        if (temp == NULL) {
            printf("Erro de alocacao de memoria ao expandir equipe!\n");
            return;
        }
        eq->membros = temp;
        eq->capacidade = nova_cap;
        printf("[SISTEMA] Capacidade da equipe expandida para %d membros.\n", eq->capacidade);
    }

    Personagem novo;
    novo.id = eq->quantidade + 1;

    printf("\n--- CADASTRO DE NOVO INTEGRANTE ---\n");
    printf("Nome do Personagem: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    int opcao_classe;
    do {
        printf("Escolha a Classe (1-Guerreiro, 2-Mago, 3-Arqueiro, 4-Clerigo): ");
        if (scanf("%d", &opcao_classe) != 1 || opcao_classe < 1 || opcao_classe > 4) {
            printf("Opcao invalida!\n");
            limpar_buffer();
            opcao_classe = 0;
        }
    } while (opcao_classe == 0);
    novo.classe = (ClassePersonagem)opcao_classe;

    novo.nivel = 1;
    novo.vida = VIDA_MAXIMA;
    novo.pontuacao = 0;
    
    printf("Posicao Inicial X: ");
    scanf("%d", &novo.pos.x);
    printf("Posicao Inicial Y: ");
    scanf("%d", &novo.pos.y);
    limpar_buffer();

    eq->membros[eq->quantidade] = novo;
    eq->quantidade++;

    printf(">>> Personagem '%s' cadastrado com sucesso! <<<\n\n", novo.nome);
}

// Listar membros da Equipe
void listar_equipe(const Equipe *eq) {
    printf("\n=========================================================================================\n");
    printf(" EQUIPE: %s | TOTAL: %d/%d membros\n", eq->nome_equipe, eq->quantidade, eq->capacidade);
    printf("=========================================================================================\n");

    if (eq->quantidade == 0) {
        printf("Nenhum integrante cadastrado na equipe.\n");
    } else {
        for (int i = 0; i < eq->quantidade; i++) {
            exibir_personagem(eq->membros[i]);
        }
    }

}

// Alterar estado de um membro
void alterar_estado_personagem(Equipe *eq) {
    if (eq->quantidade == 0) {
        printf("A equipe nao possui membros para alterar.\n");
        return;
    }

    int id;
    printf("Digite o ID do personagem que deseja alterar: ");
    scanf("%d", &id);
    limpar_buffer();

    int idx = buscar_indice_por_id(eq, id);
    if (idx == -1) {
        printf("Personagem com ID %d nao encontrado!\n", id);
        return;
    }

    Personagem *p = &eq->membros[idx];

    printf("\n--- ALTERANDO ESTADO DE: %s ---\n", p->nome);
    printf("1. Receber Dano / Curar\n");
    printf("2. Mover (Alterar Posicao X, Y)\n");
    printf("3. Adicionar Pontos\n");
    printf("Opcao: ");

    int op;
    scanf("%d", &op);
    limpar_buffer();

    if (op == 1) {
        int valor;
        printf("Digite o valor de Dano (negativo) ou Cura (positivo): ");
        scanf("%d", &valor);
        limpar_buffer();

        p->vida += valor;
        if (p->vida > VIDA_MAXIMA) p->vida = VIDA_MAXIMA;
        if (p->vida < 0) p->vida = 0;

        printf("Vida atualizada para: %d\n", p->vida);
    } else if (op == 2) {
        printf("Nova Posicao X: ");
        scanf("%d", &p->pos.x);
        printf("Nova Posicao Y: ");
        scanf("%d", &p->pos.y);
        limpar_buffer();
        printf("Nova posicao: (%d, %d)\n", p->pos.x, p->pos.y);
    } else if (op == 3) {
        int pts;
        printf("Pontos a adicionar: ");
        scanf("%d", &pts);
        limpar_buffer();
        p->pontuacao += pts;
        printf("Pontuacao atualizada para: %d\n", p->pontuacao);
    } else {
        printf("Opcao invalida!\n");
    }
}

int main() {
    // Inicialização da Equipe
    Equipe minha_equipe;
    strcpy(minha_equipe.nome_equipe, "Guardioes");
    minha_equipe.quantidade = 0;
    minha_equipe.capacidade = 2;
    minha_equipe.membros = (Personagem*) malloc(minha_equipe.capacidade * sizeof(Personagem));

    if (minha_equipe.membros == NULL) {
        printf("Erro ao alocar memoria inicial!\n");
        return 1;
    }

    // Pré-cadastrando alguns integrantes para teste
    minha_equipe.membros[0] = criar_personagem(1, 15, "Ana", GUERREIRO, 100, 10, 0, 0);
    minha_equipe.membros[1] = criar_personagem(2, 20, "Joao", MAGO, 80, 12, 5, 2);
    minha_equipe.quantidade = 2;

    int opcao;

    do {
        printf("=== MENU GERENCIADOR DE EQUIPE ===\n");
        printf("1. Cadastrar Integrante\n");
        printf("2. Listar Integrantes da Equipe\n");
        printf("3. Buscar Integrante por ID\n");
        printf("4. Alterar Estado de Integrante (Dano, Posicao, Pontos)\n");
        printf("0. Sair do Programa\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        limpar_buffer();

        switch (opcao) {
            case 1:
                cadastrar_personagem(&minha_equipe);
                break;
            case 2:
                listar_equipe(&minha_equipe);
                break;
            case 3: {
                int id;
                printf("Digite o ID para busca: ");
                scanf("%d", &id);
                limpar_buffer();
                int idx = buscar_indice_por_id(&minha_equipe, id);
                if (idx != -1) {
                    printf("\n--- PERSONAGEM ENCONTRADO ---\n");
                    exibir_personagem(minha_equipe.membros[idx]);
                    printf("\n");
                } else {
                    printf("Personagem nao encontrado.\n\n");
                }
                break;
            }
            case 4:
                alterar_estado_personagem(&minha_equipe);
                break;
            case 0:
                printf("\nEncerrando o sistema e liberando memoria...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n\n");
        }
    } while (opcao != 0);

    // Liberação de Memória
    free(minha_equipe.membros);
    minha_equipe.membros = NULL;

    return 0;
}