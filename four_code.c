#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "define.h"
#include "debug.h"

void pro_name(){
    val_name[0]='T';
    val_name[1]='\0';
    itoa(val_index,val_num,10);
    val_index++;
    strcat(val_name,val_num);
    strcpy(tmp_name,val_name);
    tmp_type=1;
    if(cflag==1){
        tmp_type_data=1;
    }
    else{
        tmp_type_data=0;
    }
    table_insert();
}

void pro_label(){
    label_name[0]='L';
    label_name[1]='A';
    label_name[2]='B';
    label_name[3]='E';
    label_name[4]='L';
    label_name[5]='_';
    label_name[6]='\0';
    itoa(label_index,label_num,10);
    strcat(label_name,label_num);
    label_index++;
}

void insert_four_code(int code){
    four_code_list[four_code_index].code=code;
    strcpy(four_code_list[four_code_index].para_1,four_code_para[0]);
    strcpy(four_code_list[four_code_index].para_2,four_code_para[1]);
    strcpy(four_code_list[four_code_index].para_3,four_code_para[2]);
    if(code==CPRINTF_ST){
        four_code_list[four_code_index].index_string = (char*)malloc(sizeof(char)*(strlen(token_string)+1));
        strcpy(four_code_list[four_code_index].index_string,token_string);
    }
    four_code_index++;
    if(four_code_index>=Max_fourcode){
        debug_printf("out of index\n");
        exit(0);
    }
    /*if(four_code_index==110){
        printf("there");
    }*/
}

void print_four_code(){
    int i;
    for(i=0;i<four_code_index;i++){
        switch (four_code_list[i].code){
            case CPASS:{
                fprintf(fp_four_code,"pass\n");
                break;
            }
            case CADD:{
                fprintf(fp_four_code,"%s = %s + %s\n",four_code_list[i].para_1,four_code_list[i].para_2,four_code_list[i].para_3);
                break;
            }
            case CMINUS:{
                fprintf(fp_four_code,"%s = %s - %s\n",four_code_list[i].para_1,four_code_list[i].para_2,four_code_list[i].para_3);
                break;
            }
            case CTIME:{
                fprintf(fp_four_code,"%s = %s * %s\n",four_code_list[i].para_1,four_code_list[i].para_2,four_code_list[i].para_3);
                break;
            }
            case CDIV:{
                fprintf(fp_four_code,"%s = %s / %s\n",four_code_list[i].para_1,four_code_list[i].para_2,four_code_list[i].para_3);
                break;
            }
            case CARRVAL:{
                fprintf(fp_four_code,"%s =  %s[%s]\n",four_code_list[i].para_1,four_code_list[i].para_2,four_code_list[i].para_3);
                break;
            }
            case CARRASN:{
                fprintf(fp_four_code,"%s[%s] = %s\n",four_code_list[i].para_1,four_code_list[i].para_2,four_code_list[i].para_3);
                break;
            }
            case CEQL:{
                fprintf(fp_four_code,"EQL %s %s %s\n",four_code_list[i].para_1,four_code_list[i].para_2,four_code_list[i].para_3);
                break;
            }
            case CGEQ:{
                fprintf(fp_four_code,"GEQ %s %s %s\n",four_code_list[i].para_1,four_code_list[i].para_2,four_code_list[i].para_3);
                break;
            }
            case CGTR:{
                fprintf(fp_four_code,"GTR %s %s %s\n",four_code_list[i].para_1,four_code_list[i].para_2,four_code_list[i].para_3);
                break;
            }
            case CLEQ:{
                fprintf(fp_four_code,"LEQ %s %s %s\n",four_code_list[i].para_1,four_code_list[i].para_2,four_code_list[i].para_3);
                break;
            }
            case CLSS:{
                fprintf(fp_four_code,"LSS %s %s %s\n",four_code_list[i].para_1,four_code_list[i].para_2,four_code_list[i].para_3);
                break;
            }
            case CNEQ:{
                fprintf(fp_four_code,"NEQ %s %s %s\n",four_code_list[i].para_1,four_code_list[i].para_2,four_code_list[i].para_3);
                break;
            }
            case CJUMP:{
                fprintf(fp_four_code,"JUMP %s\n",four_code_list[i].para_1);
                break;
            }
            case CASSIGN:{
                fprintf(fp_four_code,"%s = %s\n",four_code_list[i].para_1,four_code_list[i].para_2);
                break;
            }
            case CPUSH:{
                fprintf(fp_four_code,"PUSH %s %s %s\n",four_code_list[i].para_1,four_code_list[i].para_2,four_code_list[i].para_3);
                break;
            }
            case CCALL:{
                fprintf(fp_four_code,"CALL %s\n",four_code_list[i].para_1);
                break;
            }
            case CRET:{
                fprintf(fp_four_code,"return %s\n",four_code_list[i].para_1);
                break;
            }
            case CNRET:{
                fprintf(fp_four_code,"return\n");
                break;
            }
            case CRETVAL:{
                fprintf(fp_four_code,"%s = %s()\n",four_code_list[i].para_1,four_code_list[i].para_2);
                break;
            }
            case CLABEL:{
                fprintf(fp_four_code,"%s:\n",four_code_list[i].para_1);
                break;
            }
            case CSCANF:{
                fprintf(fp_four_code,"scanf %s\n",four_code_list[i].para_1);
                break;
            }
            case CPRINTF:{
                fprintf(fp_four_code,"printf %s\n",four_code_list[i].para_1);
                break;
            }
            case CPRINTF_ST:{
                fprintf(fp_four_code,"printf %s\n",four_code_list[i].index_string);
                break;
            }
            case CPUSH_STACK:{
                fprintf(fp_four_code,"push stack %s\n",four_code_list[i].para_1);
                break;
            }
            case CPULL_STACK:{
                fprintf(fp_four_code,"pull stack %s\n",four_code_list[i].para_1);
                break;
            }
            case CSAVE_ENV:{
                fprintf(fp_four_code,"save environment\n");
                break;
            }
            case CREV_ENV:{
                fprintf(fp_four_code,"recover environment\n");
                break;
            }
            default:{
                fprintf(fp_four_code,"unknown four code type : %d\n",four_code_list[i].code);
            }
        }
    }
}

