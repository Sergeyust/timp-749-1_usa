#include <stdio.h>
int main()
{
    int n, x, i;
    double result;
    double sum = 0;
    (void)scanf("%d", &n);
    for (i = 1; i <= n; ++i)
    {
        (void)scanf("%d", &x);
        sum += x;
    }
    result = sum/n;
    printf("%lf", result);
    return 0;
}
