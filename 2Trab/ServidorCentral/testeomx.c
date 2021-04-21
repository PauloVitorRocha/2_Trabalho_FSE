#include<stdio.h>
#include<stdlib.h>

int main(){
    system("omxplayer --no-keys beep.mp3 > /dev/null 2>&1 &");
return 0;
}