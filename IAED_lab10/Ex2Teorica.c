#include <stdio.h>
#include <stdlib.h>

#define less(a,b) ((10000*a.year+100*a.month+a.day)<(10000*b.year+100*b.month+b.day))

typedef struct {
    int day;
    int month;
    int year;
} date;

int main()
{
    int i,j,n;
    date d;
    date *dates;
    scanf("%d",&n);
    dates=(date*) malloc(sizeof(date)*n);
    for (i=0;i<n;i++){
        scanf("%d-%d-%d",&d.day,&d.month,&d.year);
        for(j=i-1;j>=0 && less(d,dates[j]);j--){
            dates[j+1]=dates[j];
        }
        dates[j+1]=d;
    }
    for (i=0;i<n;i++)
        printf("%02d-%02d-%04d\n",dates[i].day,dates[i].month,dates[i].year);

    free (dates);
    return 0;
}