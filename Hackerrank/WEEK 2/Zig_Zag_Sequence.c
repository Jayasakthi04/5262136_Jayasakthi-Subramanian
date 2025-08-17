#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


int cmp(const void *p, const void *q)
{
    int a = *(const int*)p;
    int b = *(const int*)q;
    return (a > b) - (a < b);
}

void findZigZagSequence(int *a, int n)
{
    if (n <= 1) return;
    qsort(a, n, sizeof(int), cmp);
    
    int k = (n + 1) / 2;
    int tmp = a[k-1];
    a[k-1] = a[n-1];
    a[n-1] = tmp;
    
    int i = k, j = n - 2;
    while (i < j)
    {
        int t = a[i];
        a[i] = a[j];
        a[j] = t;
        i++; j--;
    }
}
int main(void) {

int t;
if (scanf("%d", &t) !=1)return 0;
while (t--)
{
    int n;
    if (scanf("%d", &n)!=1)return 0;
    int *a = malloc(n * sizeof(int));
    if(!a) return 0;
    for (int i=0; i<n; ++i)
    {
        if (scanf("%d", &a[i])!=1)
        {
            free(a);
            return 0;
        }
    }

    
    findZigZagSequence(a,n);
    
    for(int i = 0; i<n; ++i)
    {
        
        printf("%d", a[i]);
        if (i + 1 < n)printf("");
    }
    printf("\n");
    free(a);
}

    

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    
    return 0;
}
