#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void preencheVetor(int vetorDeDados[], int dadosTotal);
void printVetor(int vetorDeDados[], int dadosTotal);
int menu(void);
void algoritmos(int escolha, int vetorDeDados[], int dadosTotal);
void insertionSort(int vetorDeDados[], int dadosTotal);
void selectionSort(int vetorDeDados[], int dadosTotal);
void quickSort(int vetorDeDados[], int esquerda, int direita);
void mergeSort(int vetorDeDados[], int tamanho, int esquerda, int direita);
void merge(int vetorDeDados[], int tamanho, int esquerda, int meio, int direita);

int main()
{
    int dadosTotal, escolhaDoAlgoritmo;

    srand(time(NULL));

    printf("\nInforme a quantidade de elementos do vetor: ");
    scanf("%d", &dadosTotal);

    int vetorDeDados[dadosTotal];

    preencheVetor(vetorDeDados, dadosTotal);
    printVetor(vetorDeDados, dadosTotal);

    printf("Escolha um algoritmo: \n\n");
    escolhaDoAlgoritmo = menu();

    algoritmos(escolhaDoAlgoritmo, vetorDeDados, dadosTotal);

    return 0;
}

void preencheVetor(int vetorDeDados[], int dadosTotal)
{
    for (int i = 0; i < dadosTotal; i++)
    {
        vetorDeDados[i] = rand() % dadosTotal; 
    }
    printf("\n");
}

void printVetor(int vetorDeDados[], int dadosTotal)
{
    for (int i = 0; i < dadosTotal; i++)
    {   
        if (i < (dadosTotal - 1))
            printf("[%d] - ", vetorDeDados[i]);
        else
            printf("[%d]\n\n", vetorDeDados[i]);
    }
}

int menu(void)
{
    int escolha = 0;

    do {
        printf("1 - Insertion Sort\n");
        printf("2 - Selection Sort\n");
        printf("3 - Quick Sort\n");
        printf("4 - Merge Sort\n");
        printf("\nInforme a sua escolha: ");
        scanf("%d", &escolha);

        if (escolha < 1 || escolha > 4)
            printf("\nEscolha inválida. Escolha um algoritmo: \n\n");

    } while (escolha < 1 || escolha > 4);

    return escolha;
}

void algoritmos(int escolha, int vetorDeDados[], int dadosTotal)
{
    switch (escolha)
    {
        case 1:
            printf("\nEscolha: Insertion Sort\n");
            insertionSort(vetorDeDados, dadosTotal);
        break;
        case 2:
            printf("\nEscolha: Selection Sort\n");
            selectionSort(vetorDeDados, dadosTotal);
        break;
        case 3:
            printf("\nEscolha: Quick Sort\n");
            quickSort(vetorDeDados, NULL, dadosTotal - 1);
        break;
        case 4:
            printf("\nEscolha: Merge Sort\n");
        break;
    }
}

void insertionSort(int vetorDeDados[], int dadosTotal)
{
    int j, aux;

    for (int i = 1; i < dadosTotal; i++)
    {
        printf("\n[%d] ", i);

        aux = vetorDeDados[i];
        j = i - 1;

        while (j >= 0 && aux < vetorDeDados[j])
        {
            printf("%d, ", j);

            vetorDeDados[j + 1] = vetorDeDados[j];
            j--;
        }

        vetorDeDados[j + 1] = aux;
    }
}

void selectionSort(int vetorDeDados[], int dadosTotal)
{
    int menorValor, aux, menorValorAux;

    for (int i = 0; i <= dadosTotal; i++)
    {
        menorValorAux = i;
        menorValor = vetorDeDados[i];

        for (int j = i + 1; j < dadosTotal; j++)
        {
            if (vetorDeDados[j] < menorValor)
            {
                menorValor = vetorDeDados[j];
                menorValorAux = j;
            }
        }

        aux = vetorDeDados[i];
        vetorDeDados[i] = vetorDeDados[menorValorAux];
        vetorDeDados[menorValorAux] = aux;
    } 
}

void quickSort(int vetorDeDados[], int esquerda, int direita)
{
    int pivo, aux, e = esquerda, d = direita;

    pivo = vetorDeDados[(esquerda + direita) / 2];

    do {

        while (vetorDeDados[e] < pivo) //Busca o maior valor do vetor.
        {
            e++;
        }
        while (vetorDeDados[d] > pivo) //Busca o menor valor do vetor.
        {
            d--;
        }

        if (e <= d)
        {
            aux = vetorDeDados[e];
            vetorDeDados[e] = vetorDeDados[d];
            vetorDeDados[d] = aux;
            e++;
            d--;
        }
    } while (e <= d);

    if (esquerda < d)
        quickSort(vetorDeDados, esquerda, d);

    if (direita > e)
        quickSort(vetorDeDados, e, direita);
}

void mergeSort(int vetorDeDados[], int tamanho, int esquerda, int direita)
{
    if (esquerda >= direita)
    {
        return;
    }    

    int meio;

    meio = (esquerda + direita) / 2;

    mergeSort(vetorDeDados, tamanho, esquerda, meio);
    mergeSort(vetorDeDados, tamanho, meio + 1, direita);

    if (vetorDeDados[meio] <=  vetorDeDados[meio + 1])
    {
        return;
    }

    merge(vetorDeDados, tamanho, esquerda, meio, direita);
}

void merge(int vetorDeDados[], int tamanho, int esquerda, int meio, int direita)
{
    int inicioAux = esquerda, inicioVetorDeDados = esquerda, meioAux = meio + 1, vetorAux[tamanho];
    
    for (int i = esquerda; i <= direita; i++)
    {
        vetorAux[i] = vetorDeDados[i];
    }

    while (inicioVetorDeDados <= meio &&meioAux <= direita)
    {
        if (vetorAux[inicioVetorDeDados] <= vetorAux[meioAux])
        {
            vetorDeDados[inicioAux] <= vetorAux[inicioVetorDeDados];
            inicioVetorDeDados++;
        }
        else
        {
            vetorDeDados[inicioAux] = vetorAux[meioAux];
            meioAux++;
        }

        inicioAux++;
    }

    while (inicioVetorDeDados <= meio)
    {
        vetorDeDados[inicioAux] = vetorAux[inicioVetorDeDados];
        inicioAux++;
        inicioVetorDeDados++;
    }

    while (meioAux <= direita)
    {
        vetorDeDados[inicioAux] = vetorAux[meioAux];
        inicioAux++;
        meioAux++;
    }
}