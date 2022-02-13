#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct qwe
{
    char a[100];
} arr[100];
struct wer
{
    int len;
    int ind;
} leng[100];
void main()
{
    FILE *fint, *ftab, *flen, *fsym, *fout;
    int op1[10], txtlen, txtlen1, i, j = 0, len;
    char abc[10] = {'0', '0', '0', '0'}, add[5], symadd[5], op[5], start[10], temp[30], line[20], label[20], mne[10], operand[10], symtab[10], opmne[10];
    fint = fopen("input.txt", "r");
    flen = fopen("length.txt", "r");
    ftab = fopen("optab.txt", "r");
    fsym = fopen("symbol.txt", "r");
    fout = fopen("output.txt", "w");
    leng[0].ind = 0;
    leng[0].len = 0;
    fscanf(fint, "%s%s%s%s", add, label, mne, operand);
    if (strcmp(mne, "START") == 0)
    {
        strcpy(start, operand);
        fscanf(flen, "%d", &len);
    }
    fprintf(fout, "H^%s^%06d^%X", label, atoi(start), len);
    fscanf(fint, "%s%s%s%s", add, label, mne, operand);
    int co = 0, co_len = 1, c = 0;
    while (strcmp(mne, "END") != 0)
    {
        fscanf(ftab, "%s%s", opmne, op);
        while (!feof(ftab))
        {
            if (strcmp(mne, opmne) == 0)
            {
                while (!feof(fsym))
                {
                    fscanf(fsym, "%s%s", symadd, symtab);
                    if (strcmp(operand, symtab) == 0)
                    {
                        strcpy(arr[c].a, op);
                        strcat(arr[c++].a, symadd);
                        co += strlen(op);
                        co += strlen(symadd);
                        if (co >= 60)
                        {
                            leng[co_len].ind = c - 1;
                            leng[co_len++].len = co - strlen(op) - strlen(symadd);
                            co = 0;
                            co += strlen(op) + strlen(symadd);
                        }
                        break;
                    }
                }
                fseek(fsym, SEEK_SET, 0);
                break;
            }
            else
                fscanf(ftab, "%s%s", opmne, op);
        }
        fseek(ftab, SEEK_SET, 0);
        if ((strcmp(mne, "BYTE") == 0) || (strcmp(mne, "WORD") == 0))
        {
            if (strcmp(mne, "WORD") == 0)
            {
                strcpy(abc, "00000");
                strcpy(arr[c++].a, strcat(abc, operand));
                co += strlen(operand);
                co += 5;
                if (co >= 60)
                {
                    leng[co_len].ind = c - 1;
                    leng[co_len++].len = co - strlen(operand) - 5;
                    co = 0;
                    co += strlen(operand) + 5;
                }
            }
            else
            {
                len = strlen(operand);
                int aqw[100], asd = 0;
                char str[100];
                for (i = 2; i < len - 1; i++)
                {
                    aqw[asd++] = (int)operand[i];
                }
                int index = 0;
                for (i = 0; i < asd; i++)
                    index += sprintf(&str[index], "%d", aqw[i]);
                strcpy(arr[c++].a, str);
                co += strlen(str);
                if (co >= 60)
                {
                    leng[co_len].ind = c - 1;
                    leng[co_len++].len = co - strlen(str);
                    co = 0;
                    co += strlen(str);
                }
            }
        }
        fscanf(fint, "%s%s%s%s", add, label, mne, operand);
    }
    if (co < 60)
    {
        leng[co_len].ind = c;
        leng[co_len++].len = co;
    }
    fprintf(fout, "\n");
    int a = atoi(start);
    for (int i = 0; i < co_len - 1; i++)
    {
        a = a + leng[i].len / 2;
        fprintf(fout, "T^00%X", a + 3096);
        fprintf(fout, "^%X", leng[i + 1].len / 2);
        for (int j = leng[i].ind; j < leng[i + 1].ind; j++)
        {
            fprintf(fout, "^%s", arr[j].a);
        }
        fprintf(fout, "\n");
    }
    fprintf(fout, "E^00%s", start);
    fclose(fint);
    fclose(ftab);
    fclose(fsym);
    fclose(flen);
    fclose(fout);
}
