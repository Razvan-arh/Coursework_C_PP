#include <stdio.h>


int main(){
    FILE *fptr;

    fptr = fopen("input.txt", "r");

    int n;
    while (feof(fptr)){
    fscanf(fptr, "(%d)", &n);
    printf("\n number is %d \n", n);
    fscanf(fptr, "%d", &n);
    printf("\n number is %d \n", n);
    }
    
    return 0;
}