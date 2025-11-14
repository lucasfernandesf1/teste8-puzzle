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
        printf("\n");
    }
    return;
}

void deepcopy(int estado[3][3], int copiaEstado[3][3]){
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            copiaEstado[i][j] = estado[i][j];   //serve p nada por enqt------------------
        }
    }
    return;
}

void cria_random(int novaMatriz[3][3], int *linhaVazio, int *colVazio)
{
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

                for (int h = 0; h < z; h++)
                {


                    if (aleatorio == guarda_rand[h])
                    {
                        repetido = 1;
                        break;
                    }
                }guarda_rand[z] = aleatorio;
            } while (repetido);
            novaMatriz[i][j] = aleatorio;
            //guarda_rand[z] = aleatorio;
            z++;
            if (novaMatriz[i][j] == 9)
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
    printf("escolha qual peça vc quer mover: \nw - peça de cima\ns - peça de baixo\nd - peça da direita\na - peça da esquerda\n");
    scanf(" %c", &mov);
    printf("\n");
    switch (mov)
    {
    case 'w':
        // cima
        *mover = 1;
        break;
    case 'd':
        // direita
        *mover = 2;
        break;
    case 's':
        //baixo
        *mover = 3;
        break;
    case 'a':
        //esq
        *mover = 4;
        break;
    }
}

void movimentos (int m[3][3],  int mover, int *linha, int *col)
{
    int auxLinha, auxCol;
    auxLinha = *linha;
    auxCol = *col;

    switch (mover)
    {
    case 1:
        // printf("cima");
        *linha -= 1;
        m[auxLinha][*col] = m[*linha][*col];
        break;
    case 2:
        //printf("direita");
        *col += 1;
        m[*linha][auxCol] = m[*linha][*col];
        break;
    case 3:
        //printf("baixo");
        *linha +=1;
        m[auxLinha][*col] = m[*linha][*col];
        break;
    case 4:
        //printf("esq");
        *col -= 1;
        m[*linha][auxCol] = m[*linha][*col];
        break;
    }
     m[*linha][*col] = 9;

}

int verifica_matriz(int m[3][3])
{
    int verificacao=1;
    int true_false;
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            if(m[i][j] != verificacao)
            {
                return 0;
            }
        }
    }
    return 1;
}

int main()
{
    srand(time(NULL));
    int linhavazia, colvazia, movimento;
    //Usando printEstado
    printf("Imprimindo Matriz:\n");
    int m[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    printEstado(m);

    /*//Usando deepcopy
    printf("\nCopiando e imprimindo versão nova\n");
    int moriginal[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int mnovo[3][3]; //Notem que nao inicializei mnovo
    deepcopy(moriginal, mnovo); //A ordem dos parametros eh essencial; quem inicializa os valores de mnovo eh a propria funcao
    printEstado(mnovo); //imprimindo para ver se está tudo certo*/
//-------------------------------------------------------------------------------------------
    //Alterando a matriz e gerando novo estado
    printf("\nAlterando e imprimindo versão alterada\n");
    int moriginal2[3][3] = {{1,2,3},{4,5,6},{7,8,9}};          //usar algo daqui para verificar se verificação a funcionando
    int malterada[3][3]; //Notem que nao inicializei malterada
    cria_random(/*moriginal2, */malterada, &linhavazia, &colvazia); //A ordem dos parametros eh essencial; quem inicializa os valores de mnovo eh a propria funcao
    printEstado(malterada); //imprimindo para ver se está tudo certo
//-------------------------------------------------------------------------------------------
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
    while (verifica_matriz(m) != 1)
    {
        jogador_mov(&movimento);
        movimentos(m, movimento, &linhavazia, &colvazia);
        printEstado(m);

    }

    //precisa testar com matriz correta (trazer de volta original) para ver se verificação esta funcionando,
    //testar se movimentação ta funcionando mesmo dentro do laço (eu acho q n ta), ta movendo 2 posições seguidas,
    //criar restrições para não poder sair para fora do tabuleiro ;
    //queria dar a opção de limpar a tela antiga ao jogador;

    return 0;
}

