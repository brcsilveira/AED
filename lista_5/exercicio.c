#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void preencheVetor(int vetorDeDados[], int dadosTotal);
void printVetor(int vetorDeDados[], int dadosTotal);
int menu(void);
void algoritmos(int escolha, int vetorDeDados[], int dadosTotal);

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
        break;
        case 2:
            printf("\nEscolha: Selection Sort\n");
        break;
        case 3:
            printf("\nEscolha: Quick Sort\n");
        break;
        case 4:
            printf("\nEscolha: Merge Sort\n");
        break;
    }
}