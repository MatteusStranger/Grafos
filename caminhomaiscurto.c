#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Implementacao TAD Grafo com listas/apontadores */

#define MaxNumvertices  100
#define MaxNumArestas   100
#define Infinito        INT_MAX
#define TRUE            1
#define FALSE           0

/*--Entram aqui os tipos do Programa 6.1 --*/

typedef int  TipoValorVertice;
typedef int  TipoPeso;
typedef struct TipoItem {
  TipoValorVertice Vertice;
  TipoPeso Peso;
} TipoItem;
typedef struct Celula* Apontador;
typedef struct Celula {
  TipoItem Item;
  struct Celula *Prox;
} Celula;
typedef struct TipoLista {
  Celula *Primeiro, *Ultimo;
} TipoLista;

/* -- Entra aqui tipo Fila do Programa 2.18 --*/
typedef struct TipoFila {
  Celula *Frente, *Tras;
} TipoFila;
typedef struct TipoGrafo {
  TipoLista Adj[MaxNumvertices + 1];
  TipoValorVertice NumVertices;
  int NumArestas;
} TipoGrafo;
typedef int TipoValorTempo;
typedef enum {
  branco, cinza, preto
} TipoCor;

int  i;
TipoValorVertice V1, V2, Adj;
TipoPeso Peso;
TipoGrafo Grafo;
TipoValorVertice NVertices;
int NArestas;
TipoItem x;
short FimListaAdj;

/*--Entram aqui os operadores do Programa 2.4--*/
void FLVazia(TipoLista *Lista)
{ Lista->Primeiro = malloc(sizeof(Celula));
  Lista->Ultimo = Lista->Primeiro;
  Lista->Primeiro->Prox = NULL;
} 


short ListaVazia(TipoLista Lista)
{  return (Lista.Primeiro == Lista.Ultimo);
} 

void Insere(TipoItem *x, TipoLista *Lista)
{ /*-- Insere depois do ultimo item da lista --*/
  Lista->Ultimo->Prox = malloc(sizeof(Celula));
  Lista->Ultimo = Lista->Ultimo->Prox;
  Lista->Ultimo->Item = *x;
  Lista->Ultimo->Prox = NULL;
} 

/* -- Entram aqui os operadores do Programa 2.19 --*/
void FFVazia(TipoFila *Fila)
{ Fila->Frente = malloc(sizeof(Celula));
  Fila->Tras = Fila->Frente;
  Fila->Frente->Prox = NULL;
}

short FilaVazia(TipoFila Fila)
{ return (Fila.Frente == Fila.Tras);
}

void Enfileira(TipoItem x, TipoFila *Fila)
{ Fila->Tras->Prox = malloc(sizeof(Celula));
  Fila->Tras = Fila->Tras->Prox;
  Fila->Tras->Item = x;
  Fila->Tras->Prox = NULL;
}

void Desenfileira(TipoFila *Fila, TipoItem *Item)
{ Celula *q;
  if (FilaVazia(*Fila)) 
  { printf(" Erro   fila est  a  vazia\n");
    return;
  }
  q = Fila->Frente;
  Fila->Frente = Fila->Frente->Prox;
  *Item = Fila->Frente->Item;
  free(q);
} 

void ImprimeFila(TipoFila Fila)
{ Celula *Aux;
  Aux = Fila.Frente->Prox;
  while (Aux != NULL) 
    { printf(" %d (%d) ", Aux->Item.Vertice, Aux->Item.Peso);
      Aux = Aux->Prox;
    }
} 

/*-- Entram aqui os operadores do Programa 6.2 --*/
void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2,
			 TipoPeso *Peso, TipoGrafo *Grafo)
{ TipoItem x;
  x.Vertice = *V2;
  x.Peso = *Peso;
  Insere(&x, &Grafo->Adj[*V1]);
}

void FGVazio(TipoGrafo *Grafo)
{ short i;
  for (i = 0; i <= Grafo->NumVertices - 1; i++)
    FLVazia(&Grafo->Adj[i]);
} 

short ExisteAresta(TipoValorVertice Vertice1,
		   TipoValorVertice Vertice2, TipoGrafo *Grafo)
{ Apontador Aux;
  short EncontrouAresta = FALSE;
  Aux = Grafo->Adj[Vertice1].Primeiro->Prox;
  while (Aux != NULL && EncontrouAresta == FALSE) 
    { if (Vertice2 == Aux->Item.Vertice)
      EncontrouAresta = TRUE;
      Aux = Aux->Prox;
    }
  return EncontrouAresta;
} 

short ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo)
{ return (Grafo->Adj[*Vertice].Primeiro == Grafo->Adj[*Vertice].Ultimo);
} 

Apontador PrimeiroListaAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo)
{ return (Grafo->Adj[*Vertice].Primeiro->Prox);
} 

void ProxAdj(TipoValorVertice *Vertice, TipoValorVertice *Adj,
		    TipoPeso *Peso, Celula **Prox, short *FimListaAdj)
{ /* --Retorna Adj apontado por Prox--*/
  *Adj = (*Prox)->Item.Vertice;
  *Peso = (*Prox)->Item.Peso;
  *Prox = (*Prox)->Prox;
  if (*Prox == NULL)  *FimListaAdj = TRUE;
} 

void ImprimeLista(TipoLista Lista)
{ Celula *Aux;
  Aux = Lista.Primeiro->Prox;
  while (Aux != NULL) 
    { printf("%d (%d)  ", Aux->Item.Vertice, Aux->Item.Peso);
      Aux = Aux->Prox;
  }
}  

void ImprimeGrafo(TipoGrafo *Grafo)
{ short i;
  for (i = 0; i <= Grafo->NumVertices - 1; i++) 
    { printf("Vertice %d:  ", i);
      if (!ListaVazia(Grafo->Adj[i]))
	ImprimeLista(Grafo->Adj[i]);
      putchar('\n');
    }
} 

void VisitaBfs(TipoValorVertice u, TipoGrafo *Grafo, int *Dist, TipoCor *Cor, int *Antecessor)
{ TipoValorVertice v;
  Apontador Aux;
  short FimListaAdj;
  TipoPeso Peso;
  TipoItem Item;
  TipoFila Fila;
  Cor[u] = cinza;
  Dist[u] = 0;
  FFVazia(&Fila);
  Item.Vertice = u;
  Item.Peso = 0;
  Enfileira(Item, &Fila);
  printf("Visita origem%2d cor: cinza F:", u);
  ImprimeFila(Fila);
  getchar();
  while (!FilaVazia(Fila)) 
    { Desenfileira(&Fila, &Item);
      u = Item.Vertice;
      if (!ListaAdjVazia(&u, Grafo)) 
      { Aux = PrimeiroListaAdj(&u, Grafo);
        FimListaAdj = FALSE;
        while (FimListaAdj == FALSE) 
	  { ProxAdj(&u, &v, &Peso, &Aux, &FimListaAdj);
	    if (Cor[v] != branco)
	    continue;
	    Cor[v] = cinza;
 	    Dist[v] = Dist[u] + 1;
	    Antecessor[v] = u;
	    Item.Vertice = v;
	    Item.Peso = Peso;
	    Enfileira(Item, &Fila);
	  }
      }
      Cor[u] = preto;
      printf("Visita%2d Dist%2d cor: preto F:", u, Dist[u]);
      ImprimeFila(Fila);
      getchar();
  }
}  /* VisitaBfs */


void ImprimeCaminho(TipoValorVertice Origem, TipoValorVertice v, 
		    TipoGrafo *Grafo, int * Dist, TipoCor *Cor,  
		    int *Antecessor)
{ if (Origem == v) { printf("%d ", Origem); return; }
  if (Antecessor[v] == -1)
  printf("Nao existe caminho de %d ate %d", Origem, v);
  else { ImprimeCaminho(Origem,Antecessor[v], 
                        Grafo, Dist, Cor, Antecessor);
         printf("%d ", v);
       }
} 

void BuscaEmLargura(TipoGrafo *Grafo)
{ int Dist[MaxNumvertices + 1];
  TipoCor Cor[MaxNumvertices + 1];
  int  Antecessor[MaxNumvertices + 1];
  TipoValorVertice x;
  for (x = 0; x <= Grafo->NumVertices - 1; x++) 
    { Cor[x] = branco;
      Dist[x] = Infinito;
      Antecessor[x] = -1;
    }
  for (x = 0; x <= Grafo->NumVertices - 1; x++) 
    { if (Cor[x] == branco) 
      { VisitaBfs(x,Grafo, Dist, Cor, Antecessor  );
        printf("Caminho de %d ate %d\n", x, Grafo->NumVertices - 1);
        ImprimeCaminho(x, Grafo->NumVertices - 1, Grafo,  Dist, Cor, Antecessor);
	putchar('\n');
      }
    }
}

/* ============================================================= */

int main(int argc, char *argv[])
{  /*-- Programa principal --*/
  /* -- NumVertices: definido antes da leitura das arestas --*/
  /* -- NumArestas: inicializado com zero e incrementado a --*/
  /* -- cada chamada de InsereAresta                       --*/
  printf("No. vertices:");
  scanf("%d%*[^\n]", &NVertices);
  printf("No. arestas:");
  scanf("%d%*[^\n]", &NArestas);
  Grafo.NumVertices = NVertices;
  Grafo.NumArestas = 0;
  FGVazio(&Grafo);
  for (i = 0; i <= NArestas - 1; i++) 
    { printf("Insere V1 -- V2 -- Peso:");
      scanf("%d*[^\n]", &V1);
      scanf("%d*[^\n]", &V2);
      scanf("%d*[^\n]", &Peso);
      getchar();
      Grafo.NumArestas++;
      InsereAresta(&V1, &V2, &Peso, &Grafo);   /*1 chamada : G direcionado*/
      InsereAresta(&V2, &V1, &Peso, &Grafo);   /*2 chamadas: G nao-direcionado*/
    }
  ImprimeGrafo(&Grafo);
  getchar();
  BuscaEmLargura(&Grafo);
  getchar();
 return 0; 
}

