#include <iostream>
#include <fstream>

int *A, *B;
int *atual, *best;
int tamA, tamB;
int m, n, p;

int tam = 0;
int newTam = 0;

// Gerador de arranjos
void generation(int soma, int cx, int cy) {
    if(soma == p) {
        if (tam > newTam) {
            newTam = tam;
            for(int i = 0; i < tam; i++) {
                best[i] = atual[i];
            }
        }
        return;
    }

    if(soma > p) return;

    // Tenta adicionar elementos de X
    for(int i = 0; i < tamA; i++) {
        if(cx < m) {
            atual[tam++] = A[i];
            generation(soma + A[i], cx + 1, cy);
            tam--;
        }
    }

    // Tenta adicionar elementos de Y
    for(int i = 0; i < tamB; i++) {
        if(cy < n) {
            atual[tam++] = B[i];
            generation(soma + B[i], cx, cy + 1);
            tam--;
        }
    }
}

int main(int argc, char *argv[]) {
    if(argc < 6) {
        std::cerr << "Uso: ./prog <A.txt> <B.txt> <m> <n> <p>\n";
        return 0;
    }

    std::ifstream X(argv[1]);
    std::ifstream Y(argv[2]);
    m = std::stoi(argv[3]);
    n = std::stoi(argv[4]);
    p = std::stoi(argv[5]);

    if(!X.is_open() || !Y.is_open()) {
        std::cerr << "Erro ao abrir arquivos.\n";
        return 1;
    }

    int tempA[1000], tempB[1000];
    tamA = 0;
    tamB = 0;

    int num, sinal;
    char c;

    // Leitura da entrada de X
    num = 0; sinal = 1;
    while (X.get(c)) {
        if(c == '-') {
            sinal = -1;
        } else if(c >= '0' && c <= '9') {
            num = num * 10 + (c - '0');
        } else if(c == ',') {
            tempA[tamA++] = sinal * num;
            num = 0; sinal = 1;
        }
    }
    tempA[tamA++] = sinal * num;
    X.close();

    // Leitura da entrada de Y
    num = 0; sinal = 1;
    while(Y.get(c)) {
        if(c == '-') {
            sinal = -1;
        } else if(c >= '0' && c <= '9') {
            num = num * 10 + (c - '0');
        } else if(c == ',') {
            tempB[tamB++] = sinal * num;
            num = 0; sinal = 1;
        }
    }
    tempB[tamB++] = sinal * num;
    Y.close();


    atual = new int[100];
    best = new int[100];
    A = new int[tamA];
    B = new int[tamB];

    for(int i = 0; i < tamA; i++) A[i] = tempA[i];
    for(int i = 0; i < tamB; i++) B[i] = tempB[i];

    generation(0, 0, 0);

    // Saída
    std::cout << "Maior arranjo encontrado:\n";
    for(int i = 0; i < newTam; i++) {
        std::cout << best[i] << " ";
    }
    std::cout << std::endl;

    delete[] A;
    delete[] B;
    delete[] atual;
    delete[] best;

    return 0;
}
