#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // Adicionado para suportar bool, true e false

// Estrutura para armazenar as métricas de execução
typedef struct {
    long long acessos;
    long long comparacoes;
    long long chamadas_recursivas;
} Contadores;

void zerar_contadores(Contadores *c) {
    c->acessos = 0;
    c->comparacoes = 0;
    c->chamadas_recursivas = 0;
}

bool acesso_direto(int vetor[], int tamanho, int indice, int *valor_saida, Contadores *c) {
    c->comparacoes++;
    if (indice < 0) return false;

    c->comparacoes++;
    if (indice >= tamanho) return false;

    *valor_saida = vetor[indice];
    c->acessos++;

    return true;
}

int buscar_maior(int vetor[], int tamanho, Contadores *c) {
    if (tamanho <= 0) return -1;

    int maior = vetor[0];
    c->acessos++;

    for (int i = 0; i < tamanho; i++) {
        c->acessos++;
        int elemento_atual = vetor[i];

        c->comparacoes++;
        if (elemento_atual > maior) {
            maior = elemento_atual;
        }
    }

    return maior;
}

int buscar_pares_soma(int vetor[], int tamanho, int alvo, Contadores *c) {
    int total_pares = 0;

    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            c->acessos += 2;
            int soma = vetor[i] + vetor[j];

            c->comparacoes++;
            if (soma == alvo) {
                total_pares++;
            }
        }
    }

    return total_pares;
}

bool esta_ordenado(int vetor[], int tamanho, Contadores *c) {
    for (int i = 0; i < tamanho - 1; i++) {
        c->acessos += 2;
        c->comparacoes++;
        if (vetor[i] > vetor[i + 1]) {
            return false;
        }
    }
    return true;
}

int busca_linear(int vetor[], int tamanho, int alvo, Contadores *c) {
    for (int i = 0; i < tamanho; i++) {
        c->acessos++;
        c->comparacoes++;
        if (vetor[i] == alvo) return i;
    }
    return -1;
}

int busca_binaria(int vetor[], int tamanho, int alvo, Contadores *c) {
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;

        c->acessos++;
        int valor_meio = vetor[meio];

        c->comparacoes++;
        if (valor_meio == alvo) {
            return meio;
        }

        c->comparacoes++;
        if (valor_meio < alvo) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return -1;
}

void testar_e_comparar(const char *label, int vetor[], int n, int alvo) {
    Contadores c_lin, c_bin;
    zerar_contadores(&c_lin);
    zerar_contadores(&c_bin);

    int pos_lin = busca_linear(vetor, n, alvo, &c_lin);
    int pos_bin = busca_binaria(vetor, n, alvo, &c_bin);

    printf("Testando [%s] (Alvo: %d)\n", label, alvo);
    printf("  -> Linear : Pos = %2d | Comp = %2lld | Acessos = %2lld\n", 
           pos_lin, c_lin.comparacoes, c_lin.acessos);
    printf("  -> Binaria: Pos = %2d | Comp = %2lld | Acessos = %2lld\n\n", 
           pos_bin, c_bin.comparacoes, c_bin.acessos);
}

long long fatorial_iterativo(int n, Contadores *c) {
    long long resultado = 1;
    for (int i = 1; i <= n; i++) {
        c->comparacoes++;
        resultado *= i;
    }
    c->comparacoes++;
    return resultado;
}

long long fatorial_recursivo(int n, Contadores *c) {
    c->chamadas_recursivas++;
    c->comparacoes++;
    if (n <= 1) return 1;
    return n * fatorial_recursivo(n - 1, c);
}

int soma_vetor_iterativa(int vetor[], int tamanho, Contadores *c) {
    int soma = 0;
    for (int i = 0; i < tamanho; i++) {
        c->comparacoes++;
        c->acessos++;
        soma += vetor[i];
    }
    c->comparacoes++;
    return soma;
}

int soma_vetor_recursiva(int vetor[], int tamanho, int indice, Contadores *c) {
    c->chamadas_recursivas++;
    c->comparacoes++;
    if (indice >= tamanho || indice < 0) return 0;
    c->acessos++;
    return vetor[indice] + soma_vetor_recursiva(vetor, tamanho, indice + 1, c);
}

long long fibonacci_ramificado(int n, Contadores *c) {
    c->chamadas_recursivas++;
    c->comparacoes++;
    if (n <= 0) return 0;
    c->comparacoes++;
    if (n == 1) return 1;

    return fibonacci_ramificado(n - 1, c) + fibonacci_ramificado(n - 2, c);
}

int busca_binaria_recursiva(int vetor[], int inicio, int fim, int alvo, Contadores *c) {
    c->chamadas_recursivas++;
    c->comparacoes++;
    if (inicio > fim) return -1;

    int meio = inicio + (fim - inicio) / 2;
    c->acessos++;
    int valor_meio = vetor[meio];

    c->comparacoes++;
    if (valor_meio == alvo) return meio;

    c->comparacoes++;
    if (valor_meio < alvo) {
        return busca_binaria_recursiva(vetor, meio + 1, fim, alvo, c);
    } else {
        return busca_binaria_recursiva(vetor, inicio, meio - 1, alvo, c);
    }
}

// Procedimentos dos menus e testes
void executar_exp1() {
    int v[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int n = 10, alvo = 70;
    Contadores c_lin, c_bin;
    zerar_contadores(&c_lin); zerar_contadores(&c_bin);

    busca_linear(v, n, alvo, &c_lin);
    busca_binaria(v, n, alvo, &c_bin);

    printf("\n=== EXPERIMENTO 1: BUSCA LINEAR vs BINÁRIA ITERATIVA ===\n");
    printf("Procurando alvo %d em vetor ordenado de tamanho %d:\n", alvo, n);
    printf("Busca Linear  -> Comparaçoes: %lld | Acessos: %lld\n", c_lin.comparacoes, c_lin.acessos);
    printf("Busca Binária -> Comparaçoes: %lld | Acessos: %lld\n", c_bin.comparacoes, c_bin.acessos);
}

void executar_exp2() {
    int v[] = {5, 10, 15, 20, 25};
    Contadores c_fat, c_soma;
    zerar_contadores(&c_fat); zerar_contadores(&c_soma);

    long long res_fat = fatorial_recursivo(5, &c_fat);
    int res_soma = soma_vetor_recursiva(v, 5, 0, &c_soma);

    printf("\n=== EXPERIMENTO 2: RECURSÃO SIMPLES ===\n");
    printf("Fatorial de 5 = %lld (Chamadas Recursivas: %lld)\n", res_fat, c_fat.chamadas_recursivas);
    printf("Soma do vetor = %d   (Chamadas Recursivas: %lld)\n", res_soma, c_soma.chamadas_recursivas);
}

void executar_exp3() {
    printf("\n=== EXPERIMENTO 3: RECURSÃO RAMIFICADA vs LOGARÍTMICA ===\n");
    int n_fib;
    printf("Digite um valor para o Fibonacci (Recomendado entre 5 e 30): ");
    if (scanf("%d", &n_fib) != 1) return;

    if (n_fib > 35) {
        printf("[ALERTA] Valor limitado a 35 para evitar estouro de tempo/memória devido ao O(2^n)!\n");
        n_fib = 35;
    }

    Contadores c_fib;
    zerar_contadores(&c_fib);
    long long res_fib = fibonacci_ramificado(n_fib, &c_fib);

    printf("\n[Fibonacci Ramificado - O(2^n)]\n");
    printf("  Resultado Fib(%d)     : %lld\n", n_fib, res_fib);
    printf("  Chamadas Recursivas  : %lld  <-- CRESCIMENTO EXPONENCIAL!\n", c_fib.chamadas_recursivas);

    int v_grande[1024];
    for (int i = 0; i < 1024; i++) v_grande[i] = i * 2;

    Contadores c_bin_rec;
    zerar_contadores(&c_bin_rec);
    int alvo = 1500;
    int pos = busca_binaria_recursiva(v_grande, 0, 1023, alvo, &c_bin_rec);

    printf("\n[Busca Binária Recursiva - O(log n)]\n");
    printf("  Tamanho do Vetor (N) : 1024 elementos\n");
    printf("  Alvo Procurado       : %d\n", alvo);
    printf("  Posicao Retornada    : %d\n", pos);
    printf("  Chamadas Recursivas  : %lld  <-- APENAS log2(1024) + 1!\n", c_bin_rec.chamadas_recursivas);
}

int main() {
    int opcao;

    do {
        printf("\n======================================================================\n");
        printf("       PAINEL DO LABORATÓRIO DE ALGORITMOS E ESTRUTURA DE DADOS       \n");
        printf("======================================================================\n");
        printf("1. Experimento 1: Busca Linear vs. Busca Binaria (Iterativa)\n");
        printf("2. Experimento 2: Recursão Simples (Fatorial e Soma)\n");
        printf("3. Experimento 3: Recursão Ramificada (Fibonacci) vs Logarítmica (Busca Binária)\n");
        printf("0. Sair do Laboratório\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) break;

        switch (opcao) {
            case 1:
                executar_exp1();
                break;
            case 2:
                executar_exp2();
                break;
            case 3:
                executar_exp3();
                break;
            case 0:
                printf("\nEncerrando o laboratório...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}