#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

typedef struct node
{
    int Linha;
    int Coluna;
    int PixelValue;
    struct node *next;
    struct node *prev;
} Tnode;

char identificador[5]="";

int MaxLin=0, MaxCol=0, MaxPixel=0;

Tnode *Final;

int zero, TipoDaLista = 0, repeticao = 0 ;


Tnode *InsereFimDaListaLigada0(Tnode *Imagem, int Linha, int Coluna, int PixelVl )
{
    if (Imagem == NULL )
    {
        Imagem = calloc(1,sizeof(Tnode));

        Imagem -> Linha = Linha;
        Imagem -> Coluna = Coluna;
        Imagem -> PixelValue = PixelVl;
        Imagem -> next = NULL;
    }
    else
    {
        Tnode *NewNode, *tmp;

        NewNode = calloc(1,sizeof(Tnode));

        NewNode -> Linha = Linha;
        NewNode -> Coluna = Coluna;
        NewNode -> PixelValue = PixelVl;
        NewNode -> next = NULL;
        tmp = Imagem;

        while ( tmp -> next != NULL  )
        {
            tmp = tmp -> next;
        }

        tmp -> next = NewNode;
    }
    return Imagem;
}

Tnode *InsereNaListaLigada1(Tnode *Imagem, int Linha, int Coluna, int PixelVl )
{
    Tnode *tmp;

    if(Imagem == NULL)
    {
        Imagem = calloc(1, sizeof(Tnode));
        Final = Imagem;
        Imagem->Linha = Linha;
        Imagem->Coluna = Coluna;
        Imagem->PixelValue = PixelVl;
        Imagem->next = NULL;
        Imagem->prev = NULL;
    }
    else
    {
        Final -> next = calloc(1, sizeof(Tnode));
        Final -> prev = NULL;
        Final = Final -> next;

        Final -> Linha = Linha;
        Final -> Coluna = Coluna;
        Final -> PixelValue = PixelVl;
        Final -> next = NULL;
        Final -> prev = NULL;

    }
    return Imagem;
}

Tnode *InsereFimDaListaLigada2(Tnode *Imagem, int Linha, int Coluna, int PixelVl)
{
    if(Imagem == NULL)
    {
        Imagem = calloc(1, sizeof(Tnode));
        Imagem->Linha = Linha;
        Imagem->Coluna = Coluna;
        Imagem->PixelValue = PixelVl;
        Imagem->next = NULL;
        Imagem->prev = NULL;
    }
    else
    {
        Tnode *NewNode;
        NewNode = calloc(1,sizeof(Tnode));
        NewNode->Linha = Linha;
        NewNode->Coluna = Coluna;
        NewNode->PixelValue = PixelVl;
        NewNode ->prev = NULL;
        Imagem ->prev = NewNode;
        NewNode -> next = Imagem;
        Imagem = NewNode;
    }
    return Imagem;
}

Tnode *LiberaMemoria(Tnode *Imagem)
{

    Tnode *ptr = Imagem, *tmp;
    while(ptr!=NULL)
    {
        tmp = ptr;
        ptr = ptr->next;
        free(tmp);
        if (ptr == Imagem)
            break;
    }
    return NULL;
}

Tnode *CarregaImagem(Tnode *Imagem, char File[])
{
    int valorpixel=0;

    FILE *txt = fopen(File, "r+");

    fscanf(txt, "%s \n", identificador);
    fscanf(txt, "%d %d \n", &MaxCol, &MaxLin );
    fscanf(txt, "%d \n", &MaxPixel);

    for (int i = 0 ; i < MaxLin && !feof(txt) ; i++)
    {
        for (int j = 0 ; j < MaxCol && !feof(txt) ; j++)
        {
            fscanf(txt, "%d \n",&valorpixel);
            if (valorpixel != 0)
            {
                if (TipoDaLista == 1)
                {
                    Imagem = InsereNaListaLigada1(Imagem, i, j, valorpixel);
                }
                else if (TipoDaLista == 0)
                {
                    Imagem = InsereFimDaListaLigada0(Imagem, i, j, valorpixel);
                }
                else if (TipoDaLista == 2)
                {
                    Imagem = InsereFimDaListaLigada2(Imagem, i, j, valorpixel);
                }
            }
        }
    }
    fclose(txt);
    return Imagem;
}

void ProcessaPixel(Tnode *Imagem, int OldPixel, int NewPixel)
{
    if (zero!=0)
    {
        Tnode *tmp;

        tmp = Imagem;

        while( tmp != NULL )
        {
            if( tmp -> PixelValue == OldPixel )
            {
                tmp -> PixelValue = NewPixel;

            }
            tmp = tmp -> next;
        }
    }
}

void DescarregaNovaImagem(Tnode *Imagem, char File[],int NewPixel)
{
    Tnode *percorre;

    percorre = Imagem;

    FILE *novotxt = fopen( File, "w+" );

    fprintf (novotxt,"%s \n",identificador);
    fprintf (novotxt,"%d %d \n", MaxCol, MaxLin );
    fprintf (novotxt,"%d \n",MaxPixel);

    if( TipoDaLista == 2 )
    {
        while (percorre -> next != NULL )
        {
            percorre = percorre -> next;
        }

        for (int i = 0 ; i < MaxLin ; i++)
        {
            for (int j = 0 ; j < MaxCol ; j++)
            {
                if ( (percorre -> Linha == i ) && (percorre -> Coluna == j) && percorre != NULL )
                {
                    fprintf(novotxt,"%d\n", percorre -> PixelValue );

                    if ( percorre -> prev != NULL )
                    {
                        percorre = percorre -> prev;
                    }
                    else {}

                }
                else
                {
                    if (zero != 0)
                    {
                        fprintf(novotxt,"0 \n");
                    }
                    else
                    {
                        fprintf(novotxt,"%d\n",NewPixel);
                    }
                }
            }
        }
    }
    else
    {
        for (int i = 0 ; i < MaxLin ; i++)
        {
            for (int j = 0 ; j < MaxCol ; j++)
            {
                if ( (percorre -> Linha == i) && (percorre -> Coluna == j) && percorre!= NULL)
                {
                    fprintf(novotxt,"%d\n", percorre -> PixelValue );
                    if ( percorre -> next != NULL )
                    {
                        percorre = percorre -> next;
                    }
                    else {}
                }
                else
                {
                    if (zero != 0)
                    {
                        fprintf(novotxt,"0 \n");
                    }
                    else
                    {
                        fprintf(novotxt,"%d\n",NewPixel);
                    }
                }
            }
        }
        fclose(novotxt);
    }
}

void main()
{
    setlocale(LC_ALL,"Portuguese");

    Tnode *Imagem = NULL;

    char ReadFile[30]="", SaveFile[30]="", Formato[5]=".pgm";

    int OldPixel=0, NewPixel=0;

    double tempomedio;

    printf("Qual programa vc quer usar ( 0 - Ruim || 1 - Bom || 2 - Menos Bom ): ");

    scanf("%d",&TipoDaLista);

    printf("\nQuantas vezes voce quer repetir o processamento: ");

    scanf("%d",&repeticao);

    printf("\nInforme o nome do arquivo de imagem para ler (Não precisa colocar a extensão): ");

    scanf("%s",ReadFile);
    strcat(ReadFile,Formato);

    printf("\nNo processamento, vc quer substituir qual pixel: ");

    scanf("%d",&OldPixel);

    printf("\nSubstituir por qual valor: ");

    scanf("%d",&NewPixel);

    printf("\nInforme o nome do arquivo NOVO arquivo (Não precisa colocar a extensão): ");

    scanf("%s",SaveFile);
    strcat(SaveFile,Formato);

    zero = OldPixel;

    int i;
    for( i = 0 ; i < repeticao ; i++)
    {
        clock_t begin = clock();

        Imagem = CarregaImagem(Imagem,ReadFile);

        ProcessaPixel(Imagem, OldPixel, NewPixel);

        DescarregaNovaImagem(Imagem,SaveFile,NewPixel);

        Imagem = LiberaMemoria(Imagem);

        clock_t end = clock();

        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

        printf("\nTEMPO DE PROCESSAMENTO : %lf\n",time_spent);

        tempomedio = tempomedio + time_spent;
    }
   // printf("\nTEMPO MÉDIO DE PROCESSAMENTO : %lf\n",(tempomedio/repeticao));
}
