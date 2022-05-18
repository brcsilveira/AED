#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
    int dadosTotal, escolhaDoAlgoritmo;

    srand(time(NULL));

    printf("Informe a quantidade de elementos do vetor: ");
    scanf("%d", &dadosTotal);

    int vetorDeDados[dadosTotal];

    //Preenchendo o vetor.
    for (int i = 0; i < dadosTotal; i++)
    {
        vetorDeDados[i] = rand() % dadosTotal; 
    }

    //Printando o vetor.
    printf("\n\nVetor, não ordenado, de tamanho %d: ", dadosTotal);
    for (int i = 0; i < dadosTotal; i++)
    {   
        if (i < (dadosTotal - 1))
            printf("[%d] - ", vetorDeDados[i]);
        else
            printf("[%d]\n\n", vetorDeDados[i]);
    }

    return 0;
}