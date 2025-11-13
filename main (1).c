#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
            if (estado[i][j] == 9)
            {
                printf("|   |");
            }
            else{
                printf("| %d |",estado[i][j]);
            }

        }
        //printf("\n===========\n");
        printf("\n");
    }
    return;
}

void deepcopy(int estado[3][3], int copiaEstado[3][3]){
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            copiaEstado[i][j] = estado[i][j];   //serve p nada por enqt----------
        }
    }
    return;
}

//Copia a matriz m1 e faz uma alteracao simples (duplica os valores) alterando a variavel novaMatriz
//TODO2: usar essa funcao como base para criar a funcao sucessora, sera necessario adicionar novos parametros
void cria_random(/*int m1[3][3], */int novaMatriz[3][3], int *linhaVazio, int *colVazio)
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
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            int repetido;
            do {
                aleatorio = rand_int(1, 9);
                repetido = 0;
                /*if (aleatorio == 9)
                {
                    aleatorio = 96;
                }*/

                for (int h = 0; h < z; h++)
                {


                    if (aleatorio == guarda_rand[h])
                    {
                        repetido = 1;
                        break;
                    }
                }guarda_rand[z] = aleatorio;
            } while (repetido);
            novaMatriz[i][j] = (int)aleatorio;
            //guarda_rand[z] = aleatorio;
            z++;
            if (novaMatriz[i][j] == '`')
            {
                *linhaVazio = i;
                *colVazio = j;

            }
        }
    }
}
void jogador_mov (int *mover)
{
    char mov;
    printf("escolha qual peça vc quer mover: \nw - peça de cima\ns - peça de baixo\nd - peça da direita\na - peça da esquerda");
    scanf("%c", &mov);

    switch (mov)
    {
    case 'w':
        // cima
        mover = 1;
        break;
    case 'd':
        // direita
        mover = 2;
        //break;
    case 's':
        //baixo
        mover = 3;
        break;
    case 'a':
        //esq
        mover = 4;

        break;
        // Códig
    }

}

void movimentos (int m[3][3],  int mover, int *linha, int *col)
{
    int auxLinha, auxCol;


    switch (mover)
    {
    case 1:
        // cima
        // printf("cima");
        auxLinha = linha;
        linha -= 1;
        break;
    case 2:
        // direita
        //printf("direita");
        auxCol = col;
        col += 1;
        //break;
    case 3:
        //baixo
        //printf("baixo");
        auxLinha = linha;
        linha +=1;
        break;
    case 4:
        //esq
        //printf("esq");
        auxCol = col;
        col -= 1;
        break;
        // Códig
    }
     m[*linha][*col] = 9; // nao ta atualizando ----!!!!!!
     printEstado(m);

}



//Soma os valores da matriz e verifica se a soma eh um numero par

//Soma os valores da matriz e verifica se a soma eh um numero par
//TODO: usar essa funcao como base para a funcao de avaliacao

/*int somaehpar(int wololo[3][3])
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
}*/

int main()
{
    srand(time(NULL));
    int linhavazia, colvazia, movimento;
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
    cria_random(/*moriginal2, */malterada, &linhavazia, &colvazia); //A ordem dos parametros eh essencial; quem inicializa os valores de mnovo eh a propria funcao
    printEstado(malterada); //imprimindo para ver se está tudo certo

    //Alterando a matriz diversas vezes seguidas
    printf("\nAlterando a matriz 3 vezes seguidas e imprimindo\n");
    printf("Matriz original:\n");
    printEstado(m);
    printf("\nAlteradas RANDOM:\n");
    for(int i=0; i<3;i++)
    {
        cria_random(/*m,*/ m, &linhavazia, &colvazia);
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
    jogador_mov(movimento);
    movimentos(m, movimento, &linhavazia, &colvazia);

    printEstado(m); //ta td errado não ta atualizando posição, não ta criando matrizes diferentes a cada compilação. Está salvando linha e coluna de vazio corretamente;;;

    return 0;
}

