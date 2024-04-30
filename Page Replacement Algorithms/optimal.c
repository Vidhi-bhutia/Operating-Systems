#include <stdio.h>
#include <stdbool.h>

bool search(int key, int fr[], int fn)
{
    for (int i = 0; i < fn; i++)
        if (fr[i] == key)
            return true;
    return false;
}

int predict(int pg[], int fr[], int pn, int fn, int index)
{
    int res = -1, farthest = index;
    for (int i = 0; i < fn; i++) {
        int j;
        for (j = index; j < pn; j++) {
            if (fr[i] == pg[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == pn)
            return i;
    }
    return (res == -1) ? 0 : res;
}

void optimalPage(int pg[], int pn, int fn)
{
    int fr[fn];
    for (int i = 0; i < fn; i++)
        fr[i] = -1;

    int hit = 0;
    for (int i = 0; i < pn; i++) {
        if (search(pg[i], fr, fn)) {
            hit++;
            continue;
        }

        int j;
        for (j = 0; j < fn; j++) {
            if (fr[j] == -1) {
                fr[j] = pg[i];
                break;
            }
        }
        if (j == fn) {
            int k = predict(pg, fr, pn, fn, i + 1);
            fr[k] = pg[i];
        }
    }
    printf("No. of hits = %d\n", hit);
    printf("No. of misses = %d\n", pn - hit);
}

int main()
{
    int pn;
    printf("Enter the number of pages: ");
    scanf("%d", &pn);

    int pg[pn];
    printf("Enter the page sequence:\n");
    for (int i = 0; i < pn; i++) {
        printf("Page %d: ", i + 1);
        scanf("%d", &pg[i]);
    }

    int fn;
    printf("Enter the number of frames: ");
    scanf("%d", &fn);

    optimalPage(pg, pn, fn);
    return 0;
}
