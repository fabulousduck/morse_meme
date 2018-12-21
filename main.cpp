#include <stdlib.h>	
#include <stdio.h>
#include <iostream>
#include <string>
#include <wiringPi.h>

std::string morseString;
bool exec = false;


void wait() {
    printf("wait\n");
    digitalWrite(0, LOW);
    delay(300);
}
void dash() {
    printf("dash\n");
    digitalWrite(0,HIGH);
    delay(450);
    digitalWrite(0, LOW);
    delay(450);
}
void dot() {
    printf("dot\n");
    digitalWrite(0, HIGH);
    delay(150);
    digitalWrite(0, LOW);
    delay(150);
}


void execMorse(int morseBuffer[]) {
    for(int i = 0; i < 4; i++) {
        switch(morseBuffer[i]) {
            case 0:
                wait();
                break;
            case 1:
                dot();
                break;
            case 2:
                dash();
        }
    }

}



void execThing() {
    int dict[26][4] = {
        {1,2,0,0}, //a
        {2,1,1,1}, //b
        {2,1,2,1}, //c
        {2,1,1,0}, //d
        {1,0,0,0}, //e
        {1,1,2,1}, //f
        {2,2,1,0}, //g
        {1,1,1,1}, //h
        {1,1,0,0}, //i
        {1,2,2,2}, //j
        {2,1,2,0}, //k
        {1,2,1,1}, //l
        {2,2,0,0}, //m
        {2,1,0,0}, //n
        {2,2,2,0}, //o
        {1,2,2,1}, //p
        {2,2,1,2}, //q
        {1,2,1,0}, //r
        {1,1,1,0}, //s
        {2,0,0,0}, //t
        {1,1,2,0}, //u
        {1,1,1,2}, //v
        {2,1,1,2}, //x
        {2,1,2,2}, //y
        {2,2,1,1} //z
    };
    const char *cstr = morseString.c_str();
    int i = 0;

    while(cstr[i] != '\0') {
        if(cstr == " ") {
            i++;
            continue;
        }
       execMorse(dict[cstr[i]-97]);
        i++;
    }
	exec = true;
}

int main(int argc, char * argv[]) {
    wiringPiSetup();
    pinMode(0, OUTPUT);
    pinMode(2, INPUT);
    pullUpDnControl(2, PUD_UP);

    char tmp[101];
    
    if(argc > 1) {
        morseString = argv[1];
    } else {
        printf("enter some sentence>");
        scanf("%[^\n]", tmp);
        morseString = tmp;
    }
   
    wiringPiISR(2, INT_EDGE_FALLING, &execThing);
	while(!exec) {
		continue;
	}
}
