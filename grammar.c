#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "define.h"

void program(){
    debug_fprintf(fp_grammar,"there is a program\n");
    //constant();//常量说明
    //variable();//变量说明
    while(1){
        if(sym == VOIDSY){
            sym = word();
            if(sym == MAINSY){
                sym = word();
                //mainfun();//主函数分析
                break;
            }
            else{
                //noretfun();//无返回值函数定义
            }
        }
        else if(sym == INTSY || sym == CHARSY){
            sym = word();
            //retfun();//有返回值函数定义
        }
    }
}

