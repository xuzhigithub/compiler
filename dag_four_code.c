#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "debug.h"

void insert_four_code_dag(int code){
    four_code_list_improve[four_code_index_improve].code=code;
    strcpy(four_code_list_improve[four_code_index_improve].para_1,four_code_para_improve[0]);
    strcpy(four_code_list_improve[four_code_index_improve].para_2,four_code_para_improve[1]);
    strcpy(four_code_list_improve[four_code_index_improve].para_3,four_code_para_improve[2]);
    if(code==CPRINTF_ST){
        four_code_list_improve[four_code_index_improve].index_string = (char*)malloc(sizeof(char)*(strlen(token_string)+1));
        strcpy(four_code_list_improve[four_code_index_improve].index_string,token_string);
    }
    four_code_index_improve++;
    if(four_code_index>=Max_fourcode){
        debug_printf("out of index\n");
        exit(0);
    }
    /*if(four_code_index==110){
        printf("there");
    }*/
}

void print_four_code_dag(){
    int i;
    for(i=0;i<four_code_index_improve;i++){
        switch (four_code_list_improve[i].code){
            case CPASS:{
                fprintf(fp_dag_four_code,"pass\n");
                break;
            }
            case CADD:{
                fprintf(fp_dag_four_code,"%s = %s + %s\n",four_code_list_improve[i].para_1,four_code_list_improve[i].para_2,four_code_list_improve[i].para_3);
                break;
            }
            case CMINUS:{
                fprintf(fp_dag_four_code,"%s = %s - %s\n",four_code_list_improve[i].para_1,four_code_list_improve[i].para_2,four_code_list_improve[i].para_3);
                break;
            }
            case CTIME:{
                fprintf(fp_dag_four_code,"%s = %s * %s\n",four_code_list_improve[i].para_1,four_code_list_improve[i].para_2,four_code_list_improve[i].para_3);
                break;
            }
            case CDIV:{
                fprintf(fp_dag_four_code,"%s = %s / %s\n",four_code_list_improve[i].para_1,four_code_list_improve[i].para_2,four_code_list_improve[i].para_3);
                break;
            }
            case CARRVAL:{
                fprintf(fp_dag_four_code,"%s =  %s[%s]\n",four_code_list_improve[i].para_1,four_code_list_improve[i].para_2,four_code_list_improve[i].para_3);
                break;
            }
            case CARRASN:{
                fprintf(fp_dag_four_code,"%s[%s] = %s\n",four_code_list_improve[i].para_1,four_code_list_improve[i].para_2,four_code_list_improve[i].para_3);
                break;
            }
            case CEQL:{
                fprintf(fp_dag_four_code,"EQL %s %s %s\n",four_code_list_improve[i].para_1,four_code_list_improve[i].para_2,four_code_list_improve[i].para_3);
                break;
            }
            case CGEQ:{
                fprintf(fp_dag_four_code,"GEQ %s %s %s\n",four_code_list_improve[i].para_1,four_code_list_improve[i].para_2,four_code_list_improve[i].para_3);
                break;
            }
            case CGTR:{
                fprintf(fp_dag_four_code,"GTR %s %s %s\n",four_code_list_improve[i].para_1,four_code_list_improve[i].para_2,four_code_list_improve[i].para_3);
                break;
            }
            case CLEQ:{
                fprintf(fp_dag_four_code,"LEQ %s %s %s\n",four_code_list_improve[i].para_1,four_code_list_improve[i].para_2,four_code_list_improve[i].para_3);
                break;
            }
            case CLSS:{
                fprintf(fp_dag_four_code,"LSS %s %s %s\n",four_code_list_improve[i].para_1,four_code_list_improve[i].para_2,four_code_list_improve[i].para_3);
                break;
            }
            case CNEQ:{
                fprintf(fp_dag_four_code,"NEQ %s %s %s\n",four_code_list_improve[i].para_1,four_code_list_improve[i].para_2,four_code_list_improve[i].para_3);
                break;
            }
            case CJUMP:{
                fprintf(fp_dag_four_code,"JUMP %s\n",four_code_list_improve[i].para_1);
                break;
            }
            case CASSIGN:{
                fprintf(fp_dag_four_code,"%s = %s\n",four_code_list_improve[i].para_1,four_code_list_improve[i].para_2);
                break;
            }
            case CPUSH:{
                fprintf(fp_dag_four_code,"PUSH %s %s %s\n",four_code_list_improve[i].para_1,four_code_list_improve[i].para_2,four_code_list_improve[i].para_3);
                break;
            }
            case CCALL:{
                fprintf(fp_dag_four_code,"CALL %s\n",four_code_list_improve[i].para_1);
                break;
            }
            case CRET:{
                fprintf(fp_dag_four_code,"return %s\n",four_code_list_improve[i].para_1);
                break;
            }
            case CNRET:{
                fprintf(fp_dag_four_code,"return\n");
                break;
            }
            case CRETVAL:{
                fprintf(fp_dag_four_code,"%s = %s()\n",four_code_list_improve[i].para_1,four_code_list_improve[i].para_2);
                break;
            }
            case CLABEL:{
                fprintf(fp_dag_four_code,"%s:\n",four_code_list_improve[i].para_1);
                break;
            }
            case CSCANF:{
                fprintf(fp_dag_four_code,"scanf %s\n",four_code_list_improve[i].para_1);
                break;
            }
            case CPRINTF:{
                fprintf(fp_dag_four_code,"printf %s\n",four_code_list_improve[i].para_1);
                break;
            }
            case CPRINTF_ST:{
                fprintf(fp_dag_four_code,"printf_st %s\n",four_code_list_improve[i].index_string);
                break;
            }
            case CPUSH_STACK:{
                fprintf(fp_dag_four_code,"push stack %s\n",four_code_list_improve[i].para_1);
                break;
            }
            case CPULL_STACK:{
                fprintf(fp_dag_four_code,"pull stack %s\n",four_code_list_improve[i].para_1);
                break;
            }
            case CSAVE_ENV:{
                fprintf(fp_dag_four_code,"save environment\n");
                break;
            }
            case CREV_ENV:{
                fprintf(fp_dag_four_code,"recover environment\n");
                break;
            }
            default:{
                fprintf(fp_dag_four_code,"unknown four code type : %d\n",four_code_list_improve[i].code);
            }
        }
    }
}

