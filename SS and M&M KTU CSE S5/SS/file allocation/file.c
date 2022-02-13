#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
struct file
{
    int si;
    int len;
    int b[100];
    struct node *k;
} f[100];
int mem[100], n;
struct node
{
    int n;
    struct node *next;
};
void seq()
{
    for (int i = 0; i < 100; i++)
    {
        mem[i] = 0;
    }

    printf("\nEnter the no: of Files : ");
    scanf("%i", &n);
    for (int i = 0; i < n;)
    {
        printf("\nfile%i", i + 1);
        printf("\nEnter the Starting block : ");
        scanf("%i", &f[i].si);
        if (mem[f[i].si] == 0)
        {
            printf("\nEnter the length : ");
            scanf("%i", &f[i].len);
            int check = 0;
            for (int j = f[i].si; j < f[i].si + f[i].len; j++)
            {
                if (mem[j] == 1)
                {
                    check = 1;
                    break;
                }
            }
            if (check == 0)
            {
                for (int j = f[i].si; j < f[i].si + f[i].len; j++)
                {
                    mem[j] = 1;
                }
            }
            else
            {
                printf("\nFile%i Cannot be Allocated\n", i + 1);
                continue;
            }
        }
        else
        {
            printf("\nFile%i Cannot be Allocated\n", i + 1);
            continue;
        }
        i++;
    }
    for (int i = 0; i < n; i++)
    {
        printf("\nfile%i ALOCATED -> ", i + 1);
        for (int j = f[i].si; j < f[i].si + f[i].len; j++)
            printf("\t%i\t", j);
    }
}
void ind()
{
    for (int i = 0; i < 100; i++)
    {
        mem[i] = 0;
    }

    printf("\nEnter the no: of Files : ");
    scanf("%i", &n);
    for (int i = 0; i < n;)
    {
        printf("\nfile%i", i + 1);
        printf("\nEnter the Starting Index : ");
        scanf("%i", &f[i].si);
        if (mem[f[i].si] == 1)
        {
            printf("\nFile%i Cannot be Allocated\n", i + 1);
            continue;
        }
        else
        {
            printf("\nEnter the no: BLOCKS : ");
            scanf("%i", &f[i].len);
            int check = 0;
            mem[f[i].si] = 1;
            for (int j = 0; j < f[i].len; j++)
            {
                for (int kk = 1; kk < 100; kk++)
                {
                    if (mem[kk] == 0)
                    {
                        f[i].b[j] = kk;
                        mem[kk] = 1;
                        break;
                    }
                }
            }
        }
        i++;
    }
    for (int i = 0; i < n; i++)
    {
        printf("\nfile%i ALLOCATED ->\t%i : ", i + 1, f[i].si);
        for (int ii = 0; ii < f[i].len; ii++)
            printf("\t%i", f[i].b[ii]);
    }
}

void lin()
{
    for (int i = 0; i < 100; i++)
    {
        mem[i] = 0;
    }

    printf("\nEnter the no: of Files : ");
    scanf("%i", &n);
    for (int i = 0; i < n;)
    {
        printf("\nfile%i", i + 1);
        printf("\nEnter the Starting block : ");
        scanf("%i", &f[i].si);
        if (mem[f[i].si] == 1)
        {
            printf("\nFile%i Cannot be Allocated\n", i + 1);
            continue;
        }
        else
        {
            printf("\nEnter the no: BLOCKS : ");
            scanf("%i", &f[i].len);
            int check = 0;
            mem[f[i].si] = 1;
            for (int j = 0; j < f[i].len; j++)
            {
                for (int kk = 1; kk < 100; kk++)
                {
                    if (mem[kk] == 0)
                    {
                        struct node *ll = (struct node *)malloc(sizeof(struct node));
                        ll->n = kk;
                        ll->next = NULL;
                        if (f[i].k == NULL)
                            f[i].k = ll;
                        else
                        {
                            struct node *temp = f[i].k;
                            while (temp->next != NULL)
                            {
                                temp = temp->next;
                            }
                            temp->next = ll;
                        }
                        mem[kk] = 1;
                        break;
                    }
                }
            }
        }
        i++;
    }
    for (int i = 0; i < n; i++)
    {
        printf("\nfile%i ALLOCATED :\t%i\t->", i + 1, f[i].si);
        struct node *temp = f[i].k;
        while (temp != NULL)
        {
            printf("\t%i\t->", temp->n);
            temp = temp->next;
        }
    }
}
int main(int argc, char const *argv[])
{
    while (1)
    {
        printf("\n");
        printf("1.Sequential\n");
        printf("2.Indexed\n");
        printf("3.Linked\n");
        printf("4.Exit\n");
        int ch;
        printf("\nInput your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            seq();
            break;
        case 2:
            ind();
            break;
        case 3:
            lin();
            break;
        case 4:
            exit(0);
            break;
        default:
            printf("Please input a valid choice.\n");
        }
    }
    // seq();
    // ind();
    // lin();
    return 0;
}