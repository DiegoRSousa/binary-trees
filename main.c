#include <stdio.h>
#include <stdlib.h>

struct arv
{
   int info;
   struct arv* esq;
   struct arv* dir;
};

typedef struct arv Arv;

Arv* init(void)
{
    return NULL;
}

void imprime(Arv* a)
{
    if(a != NULL)
    {
        imprime(a->esq);
        printf("%d \n", a->info);
        imprime(a->dir);
    }
}

Arv* busca(Arv* r, int v)
{
    if(r == NULL)
        return NULL;
    else if(r->info > v)
        return busca(r->esq, v);
    else if(r->info < v)
        return busca(r->dir, v);
    else
        return r;
}

Arv* insere(Arv* a, int v)
{
    if(a == NULL)
    {
        a = (Arv*)malloc((sizeof(Arv)));
        a->info = v;
        a->esq = a->dir = NULL;
    }
    else if(v < a->info)
        a->esq = insere(a->esq, v);
    else
        a->dir = insere(a->dir, v);
    return a;
}

Arv* retira(Arv* r, int v)
{
    if(r == NULL)
        return NULL;
    else if(r->info > v)
        r->esq = retira(r->esq, v);
    else if(r->info < v)
        r->dir = retira(r->dir, v);
    else //encontrou o elemento
    {
        if(r->esq == NULL && r->dir == NULL)
        {
            free(r);
            r = NULL;
        }
        else if(r->esq == NULL)
        {
            Arv* t = r;
            r = r->dir;
            free(t);
        }
        else if(r->dir == NULL)
        {
            Arv* t = r;
            r = r->esq;
            free(t);
        }
        else
        {
          Arv* pai = r;
          Arv* f = r->esq;
          while(f->dir != NULL)
          {
              pai = f;
              f = f->dir;
          }
          r->info = f->info;
          f->info = v;
          r->esq = retira(r->esq, v);
        }
    }
    return r;
}

int main()
{
    int resp = 0;
    Arv* arvore = init();
    int valor;
    do
    {
        printf("1-Adicionar 2-Buscar 3-Remover 4-Imprimir 0-Sair\n");
        scanf("%d", &resp);
        switch(resp)
        {
        case 1:
            printf("1-Adicionar\n");
            printf("Insira o valor: ");
            scanf("%d", &valor);
            arvore = insere(arvore, valor);
            printf("Valor %d inserido com sucesso!\n", valor);
            break;
        case 2:
            printf("2-Buscar\n");
            printf("Insira o valor: ");
            scanf("%d", &valor);
            arvore = busca(arvore, valor);
            if(arvore != NULL)
            {
                printf("%d Valor encontrado!\n", valor);
            }
            else
                printf("%d Valor NAO encontrado!\n", valor);
            break;
        case 3:
            printf("3-Remover\n");
            printf("Insira o valor: ");
            scanf("%d", &valor);

            if(busca(arvore, valor))
            {
                arvore = retira(arvore, valor);
                printf("%d Removido com sucesso!\n", valor);
            }
            else
                printf("%d Nao encontrado!\n", valor);
            break;
        case 4:
            imprime(arvore);
            break;
        }

    } while(resp != 0);

    printf("FIM!!!");
    return 0;
}
