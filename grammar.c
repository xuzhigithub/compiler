#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "define.h"

void program(){
    debug_fprintf(fp_grammar,"there is a program\n");
    //constant();//����˵��
    //variable();//����˵��
    while(1){
        if(sym == VOIDSY){
            sym = word();
            if(sym == MAINSY){
                sym = word();
                //mainfun();//����������
                break;
            }
            else{
                //noretfun();//�޷���ֵ��������
            }
        }
        else if(sym == INTSY || sym == CHARSY){
            sym = word();
            //retfun();//�з���ֵ��������
        }
    }
}

