#include <stdio.h>

typedef struct{
    int day;
    int month;
    int year;
} date;

unsigned days_of_month[]={31,28,31,30,31,30,31,31,30,31,30,31};

int main()
{
    date d;
    scanf("%d-%d-%d",&d.day,&d.month,&d.year);
    d.day++;
    if(d.day > days_of_month[d.month-1]){
        d.day=1;
        if(d.month++==12){
            d.month=1;
            d.year++;
        }
    }
    printf("%02d-%02d-%04d",d.day,d.month,d.year);
    return 0;
}