#include <iostream>
#include <fstream>
 
int *A;
int *arr;
bool *usado;
int m, k;


// Gerador de arranjos
void generation(int pos) {
    if(pos == m) {
        for(int i = 0; i < m; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
        return;
    }

    for(int i = 0; i < k; i++) {
        if (!usado[i]) {
            usado[i] = true;
            arr[pos] = A[i];
            generation(pos + 1);
            usado[i] = false;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Uso: ./prog <arquivo.txt> <m>\n";
        return 0;
    }

    std::ifstream entry(argv[1]);

    if(!entry.is_open()) {
        std::cerr << "Erro ao abrir arquivos.\n";
        return 1;
    }

    int temp[1000];
    k = 0;
    int num = 0;    
    int sinal = 1;     
    char c;
    m = std::stoi(argv[2]);

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
    
    if(m > k || m <= 0) {
        std::cout << "Valor de m invalidos." << std::endl;
        return 1;
    }

    A = new int[k];
    arr = new int[k];
    usado = new bool[k];

    for(int i = 0; i < k; i++) {
        A[i] = temp[i];
        usado[i] = false;
    }


    generation(0);

    delete[] A;
    delete[] arr;
    delete[] usado;

    return 0; 
}