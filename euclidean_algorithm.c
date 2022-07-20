#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int get_gcd(int a, int b) {
    // when a = bq + r => r = a % b, gcd(a, b) = gcd(b, r) = gcb(b, a%b) while (r != 0)
    // when a >= b then b >= a % b,
    // when a < b then a % b = a, so call function get_gcd(b,a) recursively.
    if (b == 0) return a;
    else return get_gcd(b, a % b);
}

int get_lcm(int x, int y) {
    return x * y / get_gcd(x, y);
}

// solve Ax + By = gcd(A, B)
int extgcd(int a, int b, int *x, int *y) {
    int g = a;
    if (b != 0) {
        g = extgcd(b, a%b, y, x);
        *y -= (a / b) * *x;
    } else {
        *x = 1; *y = 0;
    }
    return g;
}

int main(void){
    char buf[1024];
    char str[1024];
    char *p;
    int a, b;
    
    fgets(buf, sizeof(buf), stdin);
    sscanf(buf, "%[^\n]", str);
    p = strtok(str, " "); a = atoi(p);
    p = strtok(NULL, " "); b = atoi(p);
    
    printf("%d\n", get_gcd(a, b));

    return 0;
}
