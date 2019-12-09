#include <stdio.h>
#include <stdlib.h>

#define MAX 100


int matrix_chain(int *p, int n, int **m, int **s)
{
    int i, j, r, k;

    for (i = 0; i < n; i++)  
    {
        m[i][i] = 0;
    }

    for (r = 2; r <= n; r++) 
    {
        for (i = 0; i <= n - r; i++)  
        {
            j = i + r - 1;         
            m[i][j] = 99999;
            for (k = i; k <= j - 1; k++)  
            {
                int tmp = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (tmp < m[i][j])
                {
                    m[i][j] = tmp;
                    s[i][j] = k;
                }
            }
        }
    }
    return m[0][n - 1];
}

void print_chain(int i, int j, char **a, int **s)
{   

    if (i == j)
    {
        printf("%s", a[i]);
    }
    else
    {
        printf("(");
        print_chain(i, s[i][j], a, s);
        print_chain(s[i][j] + 1, j, a, s);
        printf(")");
    }
}

int main()
{

    int *p, **min_part, **min_point;
    char **a;
    int n = 6, i;
    int ret;

    p = (int *)malloc((n + 1)*sizeof(int));
    a = (char **)malloc(n*sizeof(char*));
    min_part = (int **)malloc(n*sizeof(int *));
    min_point = (int **)malloc(n*sizeof(int *));

    for (i = 0; i < n; i++)
    {
        min_part[i] = (int *)malloc(n*sizeof(int));
        min_point[i] = (int *)malloc(n*sizeof(int));
        a[i] = (char *)malloc(n*sizeof(char));
    }

    p[0] = 30;   
    p[1] = 35;     
    p[2] = 15;     
    p[3] = 5;      
    p[4] = 10;   
    p[5] = 20;     
    p[6] = 25;     

    a[0] = "A1";
    a[1] = "A2";
    a[2] = "A3";
    a[3] = "A4";
    a[4] = "A5";
    a[5] = "A6";

    ret = matrix_chain(p, n, min_part, min_point);
    printf("最小次数:%d.\n", ret);
    print_chain(0, n - 1, a, min_point);

    free(p);
    free(min_part);
    free(min_point);
    free(a);

    return 0;
}
