#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;

typedef struct g
{
    int v;
    int *vis;
    struct Node **alst;
} GPH;

typedef struct s
{
    int t;
    int scap;
    int *arr;
} STK;

NODE *create_node(int v)
{
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH *g, int src, int dest)
{
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

GPH *create_g(int v)
{
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(v * sizeof(NODE *));
    g->vis = malloc(v * sizeof(int));

    for (int i = 0; i < v; i++)
    {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }

    return g;
}

STK *create_s(int scap)
{
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;

    return s;
}

void push(int pshd, STK *s)
{
    s->t++;
    s->arr[s->t] = pshd;
}

void DFS(GPH *g, STK *s, int v_nr)
{
    NODE *adj_list = g->alst[v_nr];
    NODE *aux = adj_list;

    g->vis[v_nr] = 1;
    printf("%d ", v_nr);
    push(v_nr, s);

    while (aux != NULL)
    {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0)
        {
            DFS(g, s, con_ver);
        }

        aux = aux->next;
    }
}

void insert_edges(GPH *g, int edg_nr, int nrv)
{
    int src, dest;
    printf("Adauga %d muchii (de la 0 la %d):\n", edg_nr, nrv - 1);

    for (int i = 0; i < edg_nr; i++)
    {
        scanf("%d%d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void wipe(GPH *g, int nrv)
{
    for (int i = 0; i < nrv; i++)
    {
        g->vis[i] = 0;
    }
}

int can_be_reached(GPH *g, int nrv, int a, int b)
{
    STK *s = create_s(2 * nrv);
    DFS(g, s, a);

    for (int i = 0; i <= s->t; i++)
    {
        if (s->arr[i] == b)
        {
            free(s->arr);
            free(s);
            return 1;
        }
    }

    free(s->arr);
    free(s);
    return 0;
}

int main()
{
    int nrv;
    int edg_nr;
    int a, b;

    printf("Cate noduri are graful? ");
    scanf("%d", &nrv);

    printf("Cate muchii are graful? ");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);
    insert_edges(g, edg_nr, nrv);

    printf("Verificam daca exista drum direct intre doua restaurante.\n");
    printf("Introdu cele doua noduri (ex: 0 1): ");
    scanf("%d%d", &a, &b);

    if (can_be_reached(g, nrv, a, b))
    {
        printf("Exista un drum intre %d si %d.\n", a, b);
    }
    else
    {
        printf("NU exista drum intre %d si %d.\n", a, b);
    }

    return 0;
}
