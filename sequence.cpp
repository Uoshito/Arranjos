#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: ./prog <arquivo.txt>\n";
        return 1;
    }

    std::ifstream entry(argv[1]);

    if (!entry.is_open()) {
        std::cerr << "Erro ao abrir arquivo.\n";
        return 1;
    }

    int temp[1000];
    int k = 0;
    int num = 0;
    int sinal = 1;
    char c;

    // Leitura da entrada e conversão para int
    while(entry.get(c)) {
        if(c == '-') {
            sinal = -1;
        } else if(c >= '0' && c <= '9') {
            num = num * 10 + (c - '0');
        } else if(c == ',') {
            temp[k++] = sinal * num;
            num = 0;
            sinal = 1;
        }
    }

    temp[k++] = sinal * num;
    entry.close();

    if (k == 0) return 0;

    int first = 0;
    int tam = 1;
    int bestFirst = 0;
    int newTam = 1;

    for(int i = 1; i < k; i++) {
        if(temp[i] >= temp[i - 1]) {
            tam++;
        } else {
            first = i;
            tam = 1;
        }
        if (tam > newTam) {
            newTam = tam;
            bestFirst = first;
        }
    }

    std::cout << "Maior subarranjo crescente:\n";
    for(int i = bestFirst; i < bestFirst + newTam; i++) {
        std::cout << temp[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
