#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int day;
    int month;
    int year;
} date;

int main()
{
    int i,n;
    date *dates;
    scanf("%d",&n);
    dates=(date*) malloc(sizeof(date)*n);
    for (i=0;i<n;i++)
        scanf("%d-%d-%d",&dates[i].day,&dates[i].month,&dates[i].year);
    for (i=n-1;i>=0;i--)
        printf("%02d-%02d-%04d\n",dates[i].day,dates[i].month,dates[i].year);

    free (dates);
    return 0;
}