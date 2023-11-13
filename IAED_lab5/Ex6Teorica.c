#include <stdio.h>

#define SWAP(a,b) { date tmp;tmp=a;a=b;b=tmp}

typedef struct{
    int day;
    int month;
    int year;
} date;

int main()
{
    date d1,d2;
    scanf("%d-%d-%d",&d1.day,&d1.month,&d1.year);
    scanf("%d-%d-%d",&d2.day,&d2.month,&d2.year);

    if(d1.year>d2.year)
        SWAP(d1,d2)
    else if (d1.year==d2.year){
            if(d1.month>d2.month)
                SWAP(d1,d2)
            else if (d1.month==d2.month && d1.day>d2.day)
                SWAP(d1,d2)
    }
    printf("%02d-%02d-%04d\n",d1.day,d1.month,d1.year);
    printf("%02d-%02d-%04d\n",d2.day,d2.month,d2.year);
}