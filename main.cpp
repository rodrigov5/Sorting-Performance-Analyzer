#include <iostream>
#include <vector>
#include <algorithm>  // Para std::random_shuffle
#include <ctime>      // Para medição de tempo
#include <cstdlib>    // Para srand e rand

using namespace std;

// Estruturas para armazenar o número de comparações e trocas
struct Metrics {
    long long comparisons = 0;
    long long swaps = 0;
};

// Função para trocar elementos
void swap(int &a, int &b, Metrics &metrics) {
    int temp = a;
    a = b;
    b = temp;
    metrics.swaps++;
}

// Algoritmos de Ordenação
void bubbleSort(vector<int> &arr, Metrics &metrics) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            metrics.comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1], metrics);
            }
        }
    }
}

void selectionSort(vector<int> &arr, Metrics &metrics) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            metrics.comparisons++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[min_idx], arr[i], metrics);
    }
}

void insertionSort(vector<int> &arr, Metrics &metrics) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            metrics.comparisons++;
            arr[j + 1] = arr[j];
            metrics.swaps++;
            j--;
        }
        arr[j + 1] = key;
    }
}

// Função para gerar vetor aleatório ou decrescente
vector<int> generateArray(int size, bool isDescending) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000; // Gera números aleatórios
    }
    if (isDescending) {
        sort(arr.begin(), arr.end(), greater<int>()); // Ordena em ordem decrescente
    } else {
        random_shuffle(arr.begin(), arr.end()); // Embaralha aleatoriamente
    }
    return arr;
}

// Função para exibir o vetor
void printArray(const vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0)); // Inicializa semente de aleatoriedade

    // Escolhas do usuário
    int n, algorithmChoice;
    bool isDescending, printBefore;
    
    cout << "Escolha a quantidade de elementos (10, 100, 1000, 10000): ";
    cin >> n;
    
    cout << "Deseja que os elementos estejam em ordem decrescente? (1 para sim, 0 para nao): ";
    cin >> isDescending;
    
    cout << "Deseja exibir o vetor antes da ordenacao? (1 para sim, 0 para nao): ";
    cin >> printBefore;
    
    cout << "Escolha o algoritmo de ordenacao:\n";
    cout << "1. Bubble Sort, Selection Sort, Insertion Sort\n";
    cout << "2. Merge Sort, Quick Sort, Heap Sort (não implementado aqui)\n";
    cout << "3. Radix Sort, Bucket Sort, Counting Sort (não implementado aqui)\n";
    cin >> algorithmChoice;

    // Gera o vetor
    vector<int> arr = generateArray(n, isDescending);

    if (printBefore) {
        cout << "Vetor antes da ordenacao:\n";
        printArray(arr);
    }

    // Medir tempo e contadores de comparações/trocas
    Metrics metrics;
    clock_t start, end;

    // Escolhe o algoritmo com base na escolha do usuário
    start = clock();
    switch (algorithmChoice) {
        case 1:
            bubbleSort(arr, metrics);
            break;
        case 2:
            selectionSort(arr, metrics);
            break;
        case 3:
            insertionSort(arr, metrics);
            break;
        default:
            cout << "Escolha inválida!" << endl;
            return 1;
    }
    end = clock();

    // Exibir vetor ordenado
    cout << "Vetor apos a ordenacao:\n";
    printArray(arr);

    // Resultados
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    cout << "Tempo de execucao: " << time_taken << " segundos" << endl;
    cout << "Comparacoes: " << metrics.comparisons << endl;
    cout << "Trocas: " << metrics.swaps << endl;

    return 0;
}
