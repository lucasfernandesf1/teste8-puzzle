#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//ASSINATURAS DAS FUNÇÕES
static inline int rand_int(int a, int b)
{
 return a + rand() % (b - a + 1);
}

//Imprime a variavel estado, que é uma matriz
void printEstado(int estado[3][3])
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            printf("%d\t",estado[i][j]);
        }
        printf("\n");
    }
    return;
}

void deepcopy(int estado[3][3], int copiaEstado[3][3]){
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            copiaEstado[i][j] = estado[i][j];
        }
    }
    return;
}



//Copia a matriz m1 e faz uma alteracao simples (duplica os valores) alterando a variavel novaMatriz
//TODO2: usar essa funcao como base para criar a funcao sucessora, sera necessario adicionar novos parametros
void cria_random(/*int m1[3][3], */int novaMatriz[3][3])
{
    /*for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                novaMatriz[i][j] = m1[i][j];
            }
        }*/

    int guarda_rand[9];
    int z = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            int aleatorio;
            int repetido;


            do {
                aleatorio = rand_int(1, 9);
                repetido = 0;

                for (int h = 0; h < z; h++) {
                    if (aleatorio == guarda_rand[h]) {
                        repetido = 1;
                        break;
                    }
                }
            } while (repetido);
            guarda_rand[z] = aleatorio;
            novaMatriz[i][j] = aleatorio;
            z++;
        }
    }
}
//Soma os valores da matriz e verifica se a soma eh um numero par

//Soma os valores da matriz e verifica se a soma eh um numero par
//TODO: usar essa funcao como base para a funcao de avaliacao
int somaehpar(int wololo[3][3])
{
    int sum = 0;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            sum += wololo[i][j];
        }
    }
    if ((sum % 2) == 0)
    {
        return 1;
    }
    else
    {
        return -1; //poderia ser 0, mas usei -1 para reforçar que C entende 0 como FALSE e qualquer outra coisa como verdadeiro
    }
}

//MAIN
int main()
{
    //Usando printEstado
    printf("Imprimindo Matriz:\n");
    int m[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    printEstado(m); //Notem que passo m diretamente, sem usar o &

    //Usando deepcopy
    printf("\nCopiando e imprimindo versão nova\n"); //-------------------
    int moriginal[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int mnovo[3][3]; //Notem que nao inicializei mnovo
    deepcopy(moriginal, mnovo); //A ordem dos parametros eh essencial; quem inicializa os valores de mnovo eh a propria funcao
    printEstado(mnovo); //imprimindo para ver se está tudo certo

    //Alterando a matriz e gerando novo estado
    printf("\nAlterando e imprimindo versão alterada\n");
    int moriginal2[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int malterada[3][3]; //Notem que nao inicializei malterada
    cria_random(/*moriginal2, */malterada); //A ordem dos parametros eh essencial; quem inicializa os valores de mnovo eh a propria funcao
    printEstado(malterada); //imprimindo para ver se está tudo certo

    //Alterando a matriz diversas vezes seguidas
    printf("\nAlterando a matriz 3 vezes seguidas e imprimindo\n");
    printf("Matriz original:");
    printEstado(m);
    printf("\nAlteradas RANDOM:\n");
    for(int i=0; i<3;i++)
    {
        cria_random(/*m,*/ m);
        //printf("\t\t");
        printEstado(m);
        printf("\n");
    }

    //verificando se a soma dos valores da matriz eh um numero par
    //Utilizarei as matrizes m (cuja soma eh impar) e malterada (cuja soma eh par)
    printf("\nVerificando se a soma é par\n");
    printf("m: %d\n",somaehpar(m));
    printf("malterada: %d\n",somaehpar(malterada));
    printf("\nVerificando se a soma é par. Usando condições dentro do printf\n");
    printf("m: %d\n",somaehpar(m)==1);
    printf("malterada: %d\n",somaehpar(malterada)==1);
    printf("\nVerificando se a soma é par. Usando a saída da função para processar o if\n");
    if (somaehpar(m))
    {
        printf("a soma de m é par!\n");
    }
    else
    {
        printf("a soma de m é impar!\n");
    }

    if (somaehpar(malterada)) //TODO: algo está errado que faz com que esse eja impresso errado, mas funcionou certo nos outros...
    {
        printf("a soma de malterada é par!\n");
    }
    else
    {
        printf("a soma de malterada é impar!\n");
    }




    return 0;
}

