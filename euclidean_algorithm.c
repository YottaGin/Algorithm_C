#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int get_gcd(int x, int y) {
    // when a = bq + r, gcd(a, b) = gcd(b, r) while (r != 0)
    int a, b, r;
    if (x >= y) {
        a = x; b = y;
    } else {
        a = y; b = x;
    }
    
    r = a % b;
    while (r != 0) {
        a = b;
        b = r;
        r = a % b;
    }
    
    return b;
}

int get_lcb(int x, int y) {
    return x * y / get_gcd(x, y);
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
