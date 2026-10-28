#include<iostream>
#include<string.h> 

void xoropr(char *a , const char *b , int start , int len) {
    for(int i = 0 ; i < len ; i++) {
        a[start + i] = (a[start + i] == b[i]) ? '0' : '1';
    }
}

void divCrc(char *data , const char *generator) {
    int datalen = strlen(data) ; 
    int genlen = strlen(generator) ;
    for(int i = 0 ; i <= datalen - genlen ; ) {
        if(data[i] == '1') {
            xoropr(data , generator , i , genlen) ;
        }
    }
}

int main(){
    char data[] = "1101001110110000" ;
    char generator[] = "1001" ;
    divCrc(data , generator) ;
    printf("Remainder: %s\n" , data) ;
    return 0 ;
}