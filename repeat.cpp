#include <iostream>
#include <fstream>
 
int *A;
int *arr;
int m, n, k;

int countDiff() {
    bool *visto = new bool[k];
    for(int i = 0; i < k; i++) {
        visto[i] = false;
    }

    int cont = 0;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < k; j++) {
            if(arr[i] == A[j] && !visto[j]) {
                visto[j] = true;
                cont++;
            }
        }
    }
    delete[] visto;

    return cont;
}

// Gerador de arranjos
void generation(int pos) {
    if(pos == m) {
        if(countDiff() >= n){
            for(int i = 0; i < m; i++) {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }
        return;
    }

    for(int i = 0; i < k; i++) {
        arr[pos] = A[i];
        generation(pos + 1);
    }
}

int main(int argc, char *argv[]) {
    if(argc < 4) {
        std::cerr << "Uso: ./prog <arquivo.txt> <m> <n> \n";
        return 1;
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
    int n = std::stoi(argv[3]);

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
    
    if(m <= 0 || n <= 0 || n > k || n > m) {
        std::cout << "Valores de m ou n invalidos." << std::endl;
        return 1;
    }

    A = new int[k];
    arr = new int[m];

    for(int i = 0; i < k; i++) {
        A[i] = temp[i];
    }


    generation(0);

    delete[] A;
    delete[] arr;

    return 0; 
}