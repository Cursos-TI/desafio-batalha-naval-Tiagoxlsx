#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; // 0 = água
        }
    }
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) {
                printf(" ~ "); // Água
            } else if (tabuleiro[i][j] == 3) {
                printf(" N "); // Navio
            } else if (tabuleiro[i][j] == 5) {
                printf(" * "); // Área de efeito da habilidade
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Função para criar a matriz da habilidade em forma de cone
void criarCone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (j >= (TAM_HABILIDADE/2 - i) && j <= (TAM_HABILIDADE/2 + i)) {
                matriz[i][j] = 1; // Dentro do cone
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz da habilidade em forma de cruz
void criarCruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == centro || j == centro) {
                matriz[i][j] = 1; // Linha e coluna central
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz da habilidade em forma de octaedro (losango)
void criarOctaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro) {
                matriz[i][j] = 1; // Dentro do losango
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Função para sobrepor uma matriz de habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                       int habilidade[TAM_HABILIDADE][TAM_HABILIDADE],
                       int origemX, int origemY) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int x = origemX + (i - centro);
                int y = origemY + (j - centro);

                // Garante que está dentro do tabuleiro
                if (x >= 0 && x < TAM_TABULEIRO && y >= 0 && y < TAM_TABULEIRO) {
                    if (tabuleiro[x][y] != 3) { 
                        // Não sobrescreve navio
                        tabuleiro[x][y] = 5;
                    }
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Posiciona manualmente alguns navios
    tabuleiro[2][2] = 3;
    tabuleiro[5][5] = 3;
    tabuleiro[7][3] = 3;

    // Cria as matrizes de habilidade
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplica as habilidades em pontos específicos
    aplicarHabilidade(tabuleiro, cone, 2, 5);
    aplicarHabilidade(tabuleiro, cruz, 6, 6);
    aplicarHabilidade(tabuleiro, octaedro, 4, 2);

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
