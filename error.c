#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "debug.h"

void error(int error_type){
    fprintf(fp_error,"line:%d column:%d %s\n",line,column,error_msg[error_type]);
    debug_printf("line:%d column:%d %s\n",line,column,error_msg[error_type]);
    switch(error_type){
        case 1:{
            while((input[loc]>='a'&&input[loc]<='z')||(input[loc]>='A'&&input[loc]<='Z')||(input[loc]<='9'&&input[loc]>='0')||input[loc]=='_'){
                column++;
                loc++;
            }
            break;
        }
        case 37:{}
        case 2:{
            while(input[loc]<='9'&&input[loc]>='0'){
                column++;
                loc++;
            }
            token_int = 0;
            break;
        }
        case 3:{}
        case 4:{}
        case 5:{}
        case 6:{}
        case 7:{}
        case 8:{}
        case 9:{}
        case 10:{}
        case 11:{}
        case 12:{}
        case 15:{}
        case 23:{
            while(1){
                if(sym == IFSY || sym == DOSY || sym == SWITCHSY || sym == LBRACE || sym == SCANFSY || sym == PRINTFSY || sym == RETURNSY || sym == SEMICOLON||sym==-1){
                    break;
                }
                sym = word();
            }
            break;
        }
        case 16:{
            int count = 1;
            while(1){
                if(sym == RBRACE){
                    count--;
                    if(count == 0){
                       sym = word();
                        break;
                    }
                }
                else if(sym == LBRACE){
                    count++;
                }
                else if(sym==-1){
                    break;
                }
                sym = word();
            }
            break;
        }//跳出switch的循环体
        case 13:{}
        case 14:{}
        case 18:{}
        case 19:{}
        case 22:{}
        case 25:{
            while(1){
                if(sym == CONSTSY || sym == INTSY || sym == CHARSY || sym == VOIDSY ||sym==-1){
                    break;
                }
                sym = word();
            }
            break;
        }//跳过当前常量定义
        case 27:{
            while(1){
                if(sym != -1){
                    sym = word();
                }
            }
        }
        case 28:{
            while((input[loc]>='a'&&input[loc]<='z')||(input[loc]>='A'&&input[loc]<='Z')||(input[loc]<='9'&&input[loc]>='0')||input[loc]=='_'){
                loc++;
                column++;
            }
            break;
        }
        case 38:{
            sym = word();
            break;
        }
        case 30:{}
        case 31:{}
        case 32:{}
        case 33:{}
        case 34:{}
        case 35:{}
        case 36:{}
        case 39:{}
        case 40:{}
        case 41:{}
        case 21:{}
        case 24:{
            break;
        }
        case 17:{}//缺少main函数，输出即可，不作处理
    }
}
