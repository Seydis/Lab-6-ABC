#include <stdio.h>
#include <stdlib.h>

typedef struct arbore
{
    int info;
    struct arbore *stg, *dr;
}arbore;

//arbore *rad;

void insert(arbore **rad, int x)
{
    if (*rad == NULL)
    {
        *rad=(arbore*)malloc(sizeof(arbore));
        (*rad)->info=x;
        (*rad)->dr=NULL;
        (*rad)->stg=NULL;
    }
    else
    {
        if (x<(*rad)->info)
            insert(&(*rad)->stg,x);
        if (x>(*rad)->info)
             insert(&(*rad)->dr,x);
    }
}

void rsd (arbore *rad)
{
    if (rad)
    {
        printf("%d ", rad->info);
        rsd(rad->stg);
        rsd(rad->dr);
    }
}

//int search (arbore *rad, int x)
//{
//    while (rad!=NULL)
//    {
//        if (rad->info == x)
//            return 1;
//        if (rad->info < x)
//            rad=rad->dr;
//        if (rad->info > x)
//            rad=rad->stg;
//    }
//
//    return 0;
//}

int search(arbore *rad, int x)
{
    if (rad == NULL)
        return 0;

    if (rad->info == x)
        return 1;

    if (rad->info > x)
        return search(rad->stg, x);

    return search(rad->dr, x);

}
arbore* findMax(arbore *t)
{
    if (!t)
    {
        printf("Arborele nu exista \n");
        exit(1);
    }

    if (t->dr != NULL)
        return findMax(t->dr);

    return t;
}

arbore* findMin(arbore *t)
{
    if (!t)
    {
        printf("Arborele nu exista \n");
        exit(1);
    }

    if (t->stg != NULL)
        return findMin(t->stg);

    return t;
}

//arbore* del (arbore **t, int val)
//{
//    arbore* aux;
//
//    if (*t==NULL)
//        printf("Elementul nu exista");
//    else
//        if (val < (*t)->info)
//            (*t)->stg = del(&(*t)->stg, val);
//        if (val > (*t)->info)
//            (*t)->dr = del(&(*t)->dr, val);
//
//        if (val == (*t)->info)
//        {
//            if ((*t)->dr != NULL && (*t)->stg !=NULL)  // are 2 fii
//                {
//                    aux=findMin((*t)->dr);
//                    (*t)->info = aux->info;
//                }
//            else
//            {
//
//                if ((*t)->dr == NULL && (*t)->stg == NULL) // e frunza
//                    free(t); // imi trebuie predecesor
//                else
//                {
//                    aux = *t;
//
//                    if ((*t)->stg == NULL)
//                    {
//                        *t=(*t)->dr;
//                        free(aux);
//                    }
//                    else
//                        if ((*t)->dr == NULL)
//                    {
//                        *t=(*t)->stg;
//                        free(aux);
//                    }
//                }
//            }
//        }
//
//    return t;
//}

void delete0 (arbore**t, int info, char i);

void delete1 (arbore **t, int info, arbore **rad)
{
   if ((*t)->dr != NULL && (*t)->stg !=NULL)  // are 2 fii
    {
        arbore *pred;
        int a;
        rad=*t;
        pred=findMax((*t)->stg);
        //pred=findMin((*t)->dr);
        a=(*t)->info;
        (*t)->info = pred->info;
        pred->info=a;

        delete0(&rad, pred->info, 1);

    }
}

void delete0 (arbore**rad, int info, char i)
{
    arbore *p;
    arbore *t;

    t=*rad;

    if (i==1)
        t=t->stg;

    if (t==NULL)
        printf("Arborele nu exista");

    while ((t)->info!=info)
    {
        if ((t)->info < info)
      //  if ((t)->info > info)
        {
            p=t;
            t=(t)->dr;
        }
        else
        {
            p=t;
            t=(t)->stg;
        }
    }

    if (!(t)->stg || !(t)->dr)
        //e frunza sau nod cu un descendent
    {
        if (t==p->stg)
        {
            if ((t)->stg != NULL)
            {
                p->stg=(t)->stg;
                free(t);
            }

            else
            {
                if ((t)->dr != NULL)
                {
                p->stg=t->dr;
                }
                else
                {
                    p->stg=NULL;
                    free(t);
                }
            }

        }

        if (t == p->dr)
        {

            if ((t)->dr != NULL)
            {
                p->dr=(t)->dr;
                free(t);
            }

            else
            {
                if ((t)->stg != NULL)
                {
                p->dr=(t)->stg;
                }
                else
                {
                    p->dr=NULL;
                    free(t);
                }
            }
        }
    }
    else delete1(&(t), info, &(*rad));
}

int main()
{
    int x,n;
    arbore *rad = NULL;

    insert(&rad, 50);
    insert(&rad, 30);
    insert(&rad, 80);
    insert(&rad, 60);
    insert(&rad, 90);
    insert(&rad, 70);
    insert(&rad, 20);
    insert(&rad, 40);
    insert(&rad, 35);




    printf("Ce nr cautam ?");
    scanf ("%d", &x);

    if (search(rad, x)== 1)
        printf("Nr. cautat exista \n");
    else printf("Nr. cautat nu exista \n");

    printf("Maxim: %d \n", findMax(rad)->info);

    delete0 (&rad, 35, 0);

    printf("\n");
    rsd(rad);

    printf("\n");


    printf("Hello world!\n");

    return 0;
}
