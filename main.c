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
void printEstado(char estado[3][3])
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            printf("%c\t",estado[i][j]);
        }
        printf("\n");
    }
    return;
}

void deepcopy(char estado[3][3], char copiaEstado[3][3]){
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
void cria_random(/*int m1[3][3], */char novaMatriz[3][3])
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
    int aleatorio=0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {


            int repetido;


            do {
                aleatorio = rand_int(49, 57);
                repetido = 0;
                if (aleatorio == 57)
                {
                    aleatorio = 96;
                }

                for (int h = 0; h < z; h++)
                {


                    if (aleatorio == guarda_rand[h])
                    {
                        repetido = 1;
                        break;
                    }
                }guarda_rand[z] = aleatorio;
            } while (repetido);
            novaMatriz[i][j] = (char)aleatorio;
            //printf("@@@@@%c\n", (char)aleatorio);
           // char  = (char)integer_value;
            //guarda_rand[z] = aleatorio;
            z++;
        }
    }
}

void movimentos (char m[3][3],char novam[3][3])
{
    char mover;
    printf("Digite w - cima\nd - direita\ns - baixo\na - esquerda para movimentar:\n\t");
    scanf("%c", &mover);

    switch (mover)
    {
    case 'w':
        // cima
        printf("cima");
        break;
    case 'd':
        // direita
        printf("direita");
        //break;
    case 's':
        //baixo
        printf("baixo");
        break;
    case 'a':
        //esq
        printf("esq");
        break;
        // Códig
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
    char m[3][3] = {{49,50,51},{52,53,54},{55,56,57}};
    printEstado(m); //Notem que passo m diretamente, sem usar o &

    //Usando deepcopy
    printf("\nCopiando e imprimindo versão nova\n"); //-------------------
    char moriginal[3][3] = {{49,50,51},{52,53,54},{55,56,57}};
    char mnovo[3][3]; //Notem que nao inicializei mnovo
    deepcopy(moriginal, mnovo); //A ordem dos parametros eh essencial; quem inicializa os valores de mnovo eh a propria funcao
    printEstado(mnovo); //imprimindo para ver se está tudo certo

    //Alterando a matriz e gerando novo estado
    printf("\nAlterando e imprimindo versão alterada\n");
    char moriginal2[3][3] = {{49,50,51},{52,53,54},{55,56,57}};
    char malterada[3][3]; //Notem que nao inicializei malterada
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
    /*printf("\nVerificando se a soma é par\n");
    printf("m: %d\n",somaehpar(m));
    printf("malterada: %c\n",somaehpar(malterada));
    printf("\nVerificando se a soma é par. Usando condições dentro do printf\n");
    printf("m: %d\n",somaehpar(m)==1);
    printf("malterada: %c\n",somaehpar(malterada)==1);
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

*/
    movimentos(m, m); //saber se ta entrando comando. falta fazer movimento i+1 ou i-1// j+1 ou j-1

    return 0;
}

