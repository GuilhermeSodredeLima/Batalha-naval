#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAM_TAB 10       // Tamanho do tabuleiro
#define TAM_HAB 5        // Tamanho das matrizes de habilidade (5x5)
#define NAVIO 3          // Valor para representar navio
#define AGUA 0           // Valor para representar água
#define HABILIDADE 5     // Valor para representar área afetada por habilidade

int tabuleiro[TAM_TAB][TAM_TAB];

// Inicializa o tabuleiro com água (0)
void inicializar_tabuleiro() {
    for (int i = 0; i < TAM_TAB; i++)
        for (int j = 0; j < TAM_TAB; j++)
            tabuleiro[i][j] = AGUA;
}

// Posiciona navio horizontal
void posicionar_navio_horizontal(int linha, int coluna) {
    for (int i = 0; i < 3 && coluna + i < TAM_TAB; i++)
        tabuleiro[linha][coluna + i] = NAVIO;
}

// Posiciona navio vertical
void posicionar_navio_vertical(int linha, int coluna) {
    for (int i = 0; i < 3 && linha + i < TAM_TAB; i++)
        tabuleiro[linha + i][coluna] = NAVIO;
}

// Gera a matriz em forma de cone (ponta para cima)
void gerar_cone(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i >= TAM_HAB / 2 && j >= (TAM_HAB / 2 - i + TAM_HAB / 2) && j <= (TAM_HAB / 2 + i - TAM_HAB / 2))
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera a matriz em forma de cruz
void gerar_cruz(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera a matriz em forma de octaedro (losango)
void gerar_octaedro(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - TAM_HAB / 2) + abs(j - TAM_HAB / 2) <= TAM_HAB / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Aplica a matriz de habilidade ao tabuleiro com ponto central
void aplicar_habilidade(int origem_linha, int origem_coluna, int matriz[TAM_HAB][TAM_HAB]) {
    int offset = TAM_HAB / 2;

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int lin = origem_linha - offset + i;
            int col = origem_coluna - offset + j;

            // Verifica se está dentro dos limites
            if (lin >= 0 && lin < TAM_TAB && col >= 0 && col < TAM_TAB) {
                if (matriz[i][j] == 1 && tabuleiro[lin][col] != NAVIO)
                    tabuleiro[lin][col] = HABILIDADE;
            }
        }
    }
}

// Exibe o tabuleiro
void exibir_tabuleiro() {
    printf("\nTabuleiro:\n\n");
    for (int i = 0; i < TAM_TAB; i++) {
        for (int j = 0; j < TAM_TAB; j++) {
            if (tabuleiro[i][j] == AGUA)
                printf("0 ");
            else if (tabuleiro[i][j] == NAVIO)
                printf("3 ");
            else if (tabuleiro[i][j] == HABILIDADE)
                printf("5 ");
        }
        printf("\n");
    }
}

int main() {
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    // Etapa 1: Inicializa tabuleiro
    inicializar_tabuleiro();

    // Etapa 2: Posiciona dois navios (fixos)
    posicionar_navio_horizontal(2, 2);
    posicionar_navio_vertical(6, 5);

    // Etapa 3: Gera matrizes das habilidades
    gerar_cone(cone);
    gerar_cruz(cruz);
    gerar_octaedro(octaedro);

    // Etapa 4: Aplica habilidades em coordenadas fixas
    aplicar_habilidade(1, 4, cone);       // Aplica cone
    aplicar_habilidade(5, 5, cruz);       // Aplica cruz
    aplicar_habilidade(8, 2, octaedro);   // Aplica octaedro

    // Etapa 5: Exibe o resultado
    exibir_tabuleiro();

    return 0;
}