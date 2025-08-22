#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isLeap(int y) {
    if (y % 400 == 0) return true;
    if (y % 100 == 0) return false;
    return (y % 4 == 0);
}

int daysInMonth(int m, int y) {
    static int mdays[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2) return 28 + (isLeap(y) ? 1 : 0);
    if (m >= 1 && m <= 12) return mdays[m];
    return 0;
}

void parseDate(const char *s, int *d, int *m, int *y) {
    if (sscanf(s, "%d-%d-%d", d, m, y) != 3) {
        *d = *m = *y = 0;
    }
}

int cmpDate(int d1, int m1, int y1, int d2, int m2, int y2) {
    if (y1 != y2) return (y1 < y2) ? -1 : 1;
    if (m1 != m2) return (m1 < m2) ? -1 : 1;
    if (d1 != d2) return (d1 < d2) ? -1 : 1;
    return 0;
}

void nextDate(int *d, int *m, int *y) {
    (*d)++;
    int dim = daysInMonth(*m, *y);
    if (dim == 0) { // invalid month, advance safely
        *d = 1;
        (*m)++;
        if (*m > 12) { *m = 1; (*y)++; }
        return;
    }
    if (*d > dim) {
        *d = 1;
        (*m)++;
        if (*m > 12) { *m = 1; (*y)++; }
    }
}

int main() {
    char u[64], v[64];
    if (scanf("%63s %63s", u, v) != 2) return 0;

    int d1=0, m1=0, y1=0, d2=0, m2=0, y2=0;
    parseDate(u, &d1, &m1, &y1);
    parseDate(v, &d2, &m2, &y2);

    if (cmpDate(d1,m1,y1, d2,m2,y2) > 0) {
        int td=d1, tm=m1, ty=y1;
        d1 = d2; m1 = m2; y1 = y2;
        d2 = td; m2 = tm; y2 = ty;
    }

    int count = 0;
    int cd = d1, cm = m1, cy = y1;
    char buf[32];

    long long safety = 0;
    const long long SAFETY_LIMIT = 20000000LL;

    while (1) {
        if (++safety > SAFETY_LIMIT) break;

        if (snprintf(buf, sizeof(buf), "%d%d%d", cd, cm, cy) < 0) break;
        long long x = atoll(buf);
        if (x % 4 == 0 || x % 7 == 0) count++;

        if (cmpDate(cd,cm,cy, d2,m2,y2) == 0) break;
        nextDate(&cd, &cm, &cy);
    }

    printf("%d\n", count);
    return 0;
}
