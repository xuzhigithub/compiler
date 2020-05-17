#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "define.h"

void pro_dag_name(){
    dag_val_name[0]='D';
    dag_val_name[1]='\0';
    itoa(dag_val_index,dag_val_num,10);
    dag_val_index++;
    strcat(dag_val_name,dag_val_num);
}

void dag_improve(){
    last_index=-1;
    for(;dag_4code<four_code_index;dag_4code++){
        //debug_printf("%d ",dag_4code);
        int loc_1=-1;
        int loc_2=-1;
        int loc_3=-1;
        char tmp_name1[Max_ident+1];
        char tmp_name2[Max_ident+1];
        char tmp_name3[Max_ident+1];
        strcpy(tmp_name1,four_code_list[dag_4code].para_1);
        strcpy(tmp_name2,four_code_list[dag_4code].para_2);
        strcpy(tmp_name3,four_code_list[dag_4code].para_3);
        int loc_sym2 = table_search(tmp_name2);
        int loc_sym3 = table_search(tmp_name3);
        int location=-1;
        int i,j;
        switch(four_code_list[dag_4code].code){
            case CPASS:{
                break;
            }
            case CADD:{}
            case CMINUS:{}
            case CTIME:{}
            case CDIV:{}
            case CARRVAL:{}
            case CARRASN:{
                for(i=0;i<dag_index;i++){
                    if(strcmp(tmp_name1,daggraph[i].name)==0){
                        loc_1 = i;
                    }
                    if(strcmp(tmp_name2,daggraph[i].name)==0){
                        loc_2 = i;
                    }
                    if(strcmp(tmp_name3,daggraph[i].name)==0){
                        loc_3 = i;
                    }
                }
                if(loc_2==-1){
                    strcpy(dag_name,tmp_name2);
                    dag_left=-1;
                    dag_right=-1;
                    dag_loc=-1;
                    dag_operate=-1;
                    if(symlist[loc_sym2].type==0){
                        dag_con=0;
                        dag_value=symlist[loc_sym2].addr;
                    }
                    else{
                        dag_con=1;
                        dag_value=0;
                    }
                    dag_type = symlist[loc_sym2].type_data;
                    loc_2 = dag_insert();
                    if(four_code_list[dag_4code].code==CARRVAL){
                        last_array = daggraph[loc_2].loc;
                    }
                }
                if(loc_3==-1){
                    strcpy(dag_name,tmp_name3);
                    dag_left=-1;
                    dag_right=-1;
                    dag_loc=-1;
                    dag_operate=-1;
                    if(symlist[loc_sym3].type==0 && loc_sym3!=-1){
                        dag_con=0;
                        dag_value=symlist[loc_sym3].addr;
                    }
                    else{
                        dag_con=1;
                        dag_value=0;
                    }
                    dag_type = symlist[loc_sym3].type_data;
                    loc_3 = dag_insert();
                }
                switch(four_code_list[dag_4code].code){
                    case CADD:{
                        for(i=0;i<dag_index;i++){
                            if(((daggraph[i].left==daggraph[loc_2].loc&&daggraph[i].right==daggraph[loc_3].loc)
                                ||(daggraph[i].left==daggraph[loc_3].loc&&daggraph[i].right==daggraph[loc_2].loc))
                               &&daggraph[i].operate==0){
                                location = i;
                                break;
                            }
                        }
                        break;
                    }
                    case CMINUS:{
                        for(i=0;i<dag_index;i++){
                            if(((daggraph[i].left==daggraph[loc_2].loc&&daggraph[i].right==daggraph[loc_3].loc))
                               &&daggraph[i].operate==1){
                                location = i;
                                break;
                            }
                        }
                        break;
                    }
                    case CTIME:{
                        for(i=0;i<dag_index;i++){
                            if(((daggraph[i].left==daggraph[loc_2].loc&&daggraph[i].right==daggraph[loc_3].loc)
                                ||(daggraph[i].left==daggraph[loc_3].loc&&daggraph[i].right==daggraph[loc_2].loc))
                               &&daggraph[i].operate==2){
                                location = i;
                                break;
                            }
                        }
                        break;
                    }
                    case CDIV:{
                        for(i=0;i<dag_index;i++){
                            if(((daggraph[i].left==daggraph[loc_2].loc&&daggraph[i].right==daggraph[loc_3].loc))
                               &&daggraph[i].operate==3){
                                location = i;
                                break;
                            }
                        }
                        break;
                    }
                    case CARRVAL:{
                        for(i=0;i<dag_index;i++){
                            if(((daggraph[i].left==daggraph[loc_2].loc&&daggraph[i].right==daggraph[loc_3].loc))
                               &&daggraph[i].operate==4){
                                location = i;
                                break;
                            }
                        }
                        break;
                    }
                    case CARRASN:{
                        /*for(i=0;i<dag_index;i++){
                            if(((daggraph[i].left==daggraph[loc_2].loc&&daggraph[i].right==daggraph[loc_3].loc))
                               &&daggraph[i].operate==5){
                                location = i;
                                break;
                            }
                        }*/
                        break;
                    }
                }
                if(loc_1!=-1 && daggraph[loc_1].operate!=-1){
                    int j;
                    for(j=0;j<dag_index;j++){
                        if(daggraph[j].loc==daggraph[loc_1].loc && daggraph[j].operate!=-1 && j!=loc_1){
                            break;
                        }
                    }
                    if(j==dag_index){
                        pro_dag_name();
                        strcpy(dag_name,dag_val_name);
                        if(daggraph[loc_1].operate==5){
                            strcat(dag_name,daggraph[loc_1].name);
                        }
                        dag_loc = daggraph[loc_1].loc;
                        dag_type=0;
                        dag_left = daggraph[loc_1].left;
                        dag_right = daggraph[loc_1].right;
                        dag_operate = daggraph[loc_1].operate;
                        dag_con = daggraph[loc_1].con;
                        dag_value = daggraph[loc_1].value;
                        dag_insert();
                    }
                    if(location!=-1){
                        daggraph[loc_1].left = daggraph[location].left;
                        daggraph[loc_1].right = daggraph[location].right;
                        daggraph[loc_1].loc = daggraph[location].loc;
                        daggraph[loc_1].con = daggraph[location].con;
                        daggraph[loc_1].value = daggraph[location].value;
                        daggraph[loc_1].operate = daggraph[location].operate;
                    }
                    else{
                        daggraph[loc_1].left = daggraph[loc_2].loc;
                        daggraph[loc_1].right = daggraph[loc_3].loc;
                        daggraph[loc_1].loc = dag_count;
                        dag_count++;
                        switch(four_code_list[dag_4code].code){
                            case CADD:{
                                daggraph[loc_1].operate=0;
                                daggraph[loc_1].con=(daggraph[loc_2].con||daggraph[loc_3].con);
                                dag_value=(dag_con==0)? daggraph[loc_2].value+daggraph[loc_3].value:0;
                                break;
                            }
                            case CMINUS:{
                                daggraph[loc_1].operate=1;
                                daggraph[loc_1].con=(daggraph[loc_2].con||daggraph[loc_3].con);
                                dag_value=(dag_con==0)? daggraph[loc_2].value-daggraph[loc_3].value:0;
                                break;
                            }
                            case CTIME:{
                                daggraph[loc_1].operate=2;
                                daggraph[loc_1].con=(daggraph[loc_2].con||daggraph[loc_3].con);
                                dag_value=(dag_con==0)? daggraph[loc_2].value*daggraph[loc_3].value:0;
                                break;
                            }
                            case CDIV:{
                                daggraph[loc_1].operate=3;
                                daggraph[loc_1].con=(daggraph[loc_2].con||daggraph[loc_3].con);
                                dag_value=(dag_con==0)? daggraph[loc_2].value/daggraph[loc_3].value:0;
                                break;
                            }
                            case CARRVAL:{
                                daggraph[loc_1].operate=4;
                                daggraph[loc_1].con=1;
                                daggraph[loc_1].value=0;
                                break;
                            }
                            case CARRASN:{
                                daggraph[loc_1].operate=5;
                                daggraph[loc_1].con=1;
                                daggraph[loc_1].value=0;
                                array_order[dag_count-1] = last_array;
                                last_array = dag_count-1;
                                break;
                            }
                        }
                    }
                }
                else{
                    if(location!=-1){
                        strcpy(dag_name,tmp_name1);
                        dag_type = daggraph[location].type;
                        dag_left = daggraph[location].left;
                        dag_right = daggraph[location].right;
                        dag_loc = daggraph[location].loc;
                        dag_con = daggraph[location].con;
                        dag_value = daggraph[location].value;
                        dag_operate = daggraph[location].operate;
                        dag_insert();
                    }
                    else{
                        strcpy(dag_name,tmp_name1);
                        dag_type=0;
                        dag_left = daggraph[loc_2].loc;
                        dag_right = daggraph[loc_3].loc;
                        dag_loc=-1;
                        switch(four_code_list[dag_4code].code){
                            case CADD:{
                                dag_operate=0;
                                dag_con=(daggraph[loc_2].con||daggraph[loc_3].con);
                                dag_value=(dag_con==0)? daggraph[loc_2].value+daggraph[loc_3].value:0;
                                break;
                            }
                            case CMINUS:{
                                dag_operate=1;
                                dag_con=(daggraph[loc_2].con||daggraph[loc_3].con);
                                dag_value=(dag_con==0)? daggraph[loc_2].value-daggraph[loc_3].value:0;
                                break;
                            }
                            case CTIME:{
                                dag_operate=2;
                                dag_con=(daggraph[loc_2].con||daggraph[loc_3].con);
                                dag_value=(dag_con==0)? daggraph[loc_2].value*daggraph[loc_3].value:0;
                                break;
                            }
                            case CDIV:{
                                dag_operate=3;
                                dag_con=(daggraph[loc_2].con||daggraph[loc_3].con);
                                dag_value=(dag_con==0)? daggraph[loc_2].value/daggraph[loc_3].value:0;
                                break;
                            }
                            case CARRVAL:{
                                dag_operate=4;
                                dag_con=1;
                                dag_value=0;
                                break;
                            }
                            case CARRASN:{
                                dag_con=1;
                                dag_value=0;
                                dag_operate=5;
                                break;
                            }
                        }
                        int tmp = dag_insert();
                        if(four_code_list[dag_4code].code==CARRASN){
                            array_order[daggraph[tmp].loc] = last_array;
                            last_array = daggraph[tmp].loc;
                        }
                    }
                }
                break;
            }
            case CEQL:{}
            case CGEQ:{}
            case CGTR:{}
            case CLEQ:{}
            case CLSS:{}
            case CNEQ:{
                int m,n;
                m=-1;
                n=-1;
                dag_export();
                for(i=0;i<dag_index;i++){
                    if(strcmp(daggraph[i].name,tmp_name1)==0){
                        m=daggraph[i].loc;
                    }
                    if(strcmp(daggraph[i].name,tmp_name2)==0){
                        n=daggraph[i].loc;
                    }
                }
                if(m==-1){
                    strcpy(four_code_para_improve[0],four_code_list[dag_4code].para_1);
                }
                else{
                    for(i=0;i<dag_index;i++){
                        if(daggraph[i].loc==m && daggraph[i].operate==-1){
                            if(daggraph[i].con==0){
                                itoa(daggraph[i].value,four_code_para_improve[0],10);
                            }
                            else{
                                strcpy(four_code_para_improve[0],daggraph[i].name);
                            }
                            break;
                        }
                    }
                    if(i==dag_index){
                        strcpy(four_code_para_improve[0],dag_pointname[m]);
                    }
                }
                if(n==-1){
                    strcpy(four_code_para_improve[1],four_code_list[dag_4code].para_2);
                }
                else{
                    for(i=0;i<dag_index;i++){
                        if(daggraph[i].loc==n && daggraph[i].con==0){
                            itoa(daggraph[i].value,four_code_para_improve[1],10);
                            break;
                        }
                    }
                    if(i==dag_index){
                        for(i=0;i<dag_index;i++){
                            if(daggraph[i].loc==n && daggraph[i].operate==-1){
                                strcpy(four_code_para_improve[1],daggraph[i].name);
                                break;
                            }
                        }
                        if(i==dag_index){
                            if(loc_sym2==-1){
                                strcpy(four_code_para_improve[1],tmp_name2);
                            }
                            else{
                                strcpy(four_code_para_improve[1],dag_pointname[daggraph[n].loc]);
                            }
                        }
                    }
                }

                strcpy(four_code_para_improve[2],tmp_name3);
                insert_four_code_dag(four_code_list[dag_4code].code);
                dag_delete();
                break;
            }
            case CJUMP:{
                dag_export();
                dag_delete();
                strcpy(four_code_para_improve[0],four_code_list[dag_4code].para_1);
                insert_four_code_dag(CJUMP);
                break;
            }
            case CASSIGN:{
                for(i=0;i<dag_index;i++){
                    if(strcmp(tmp_name1,daggraph[i].name)==0){
                        loc_1 = i;
                    }
                    if(strcmp(tmp_name2,daggraph[i].name)==0){
                        loc_2 = i;
                    }
                }
                if(tmp_name2[0]=='\''||(tmp_name2[0]<='9'&&tmp_name2[0]>='0')||tmp_name2[0]=='-'){
                    strcpy(dag_name,tmp_name1);
                    dag_left=-1;
                    dag_right=-1;
                    dag_operate=-1;
                    dag_con=0;
                    if(tmp_name2[0]=='\''){
                        dag_type=1;
                        dag_value = (int)tmp_name2[1];
                    }
                    else if(tmp_name[2]=='-'){
                        dag_type=0;
                        dag_value = atoi(tmp_name2);
                    }
                    else{
                        dag_type=0;
                       dag_value=atoi(tmp_name2);
                    }
                    for(i=0;i<dag_index;i++){
                        if(daggraph[i].value==dag_value && daggraph[i].con==0){
                            dag_loc=daggraph[i].loc;
                            break;
                        }
                    }
                    if(i==dag_index){
                        dag_loc=-1;
                    }
                    dag_insert();
                    break;
                }
                if(loc_2==-1){
                    strcpy(dag_name,tmp_name2);
                    dag_type = symlist[loc_sym2].type_data;
                    dag_left=-1;
                    dag_right=-1;
                    dag_loc=-1;
                    dag_operate=-1;
                    if(symlist[loc_sym2].type==0){
                        dag_con=0;
                        dag_value=symlist[loc_sym2].addr;
                    }
                    else{
                        dag_con=1;
                        dag_value=0;
                    }
                    loc_2 = dag_insert();
                }
                if(loc_1!=-1 && daggraph[loc_1].operate!=-1){
                    int j;
                    for(j=0;j<dag_index;j++){
                        if(daggraph[j].loc==daggraph[loc_1].loc){
                            break;
                        }
                    }
                    if(j==dag_index){
                        pro_dag_name();
                        strcpy(dag_name,dag_val_name);
                        dag_type = daggraph[loc_1].type;
                        dag_left = daggraph[loc_1].left;
                        dag_right = daggraph[loc_1].right;
                        dag_loc = daggraph[loc_1].loc;
                        dag_operate = daggraph[loc_1].operate;
                        dag_con = daggraph[loc_1].con;
                        dag_value = daggraph[loc_1].value;
                        dag_insert();
                    }
                    daggraph[loc_1].left = daggraph[loc_2].left;
                    daggraph[loc_1].right = daggraph[loc_2].right;
                    daggraph[loc_1].loc = daggraph[loc_2].loc;
                    daggraph[loc_1].operate = daggraph[loc_2].operate;
                    daggraph[loc_1].con = daggraph[loc_2].con;
                    daggraph[loc_1].value = daggraph[loc_2].value;
                }
                else{
                    strcpy(dag_name,tmp_name1);
                    dag_type = daggraph[loc_2].type;
                    dag_left = daggraph[loc_2].left;
                    dag_right = daggraph[loc_2].right;
                    dag_loc = daggraph[loc_2].loc;
                    dag_operate = daggraph[loc_2].loc;
                    dag_operate = 6;
                    dag_con = daggraph[loc_2].con;
                    dag_value = daggraph[loc_2].value;
                    dag_insert();
                }
                break;
            }
            case CPUSH:{
                int j=-1;
                for(i=0;i<dag_index;i++){
                    if(strcmp(daggraph[i].name,tmp_name1)==0){
                        j=i;
                    }
                }
                if(j==-1){
                    strcpy(dag_name,tmp_name1);
                    dag_left=-1;
                    dag_right=-1;
                    dag_loc=-1;
                    dag_operate=-1;
                    dag_value=0;
                    dag_con=-1;
                    dag_type=0;
                    int tmp = dag_insert();
                    push_list[push_index]=daggraph[tmp].loc;
                }
                else{
                    push_list[push_index]=daggraph[j].loc;
                }
                push_index++;
                strcpy(push_function,tmp_name2);
                break;
            }
            case CCALL:{
                strcpy(four_code_para_improve[0],four_code_list[dag_4code].para_1);
                insert_four_code_dag(CCALL);
                break;
            }
            case CRET:{
                dag_export();
                j=-1;
                for(i=0;i<dag_index;i++){
                    if(strcmp(daggraph[i].name,four_code_list[dag_4code].para_1)==0){
                        j=daggraph[i].loc;
                    }
                }
                if(j==-1){
                    strcpy(four_code_para_improve[0],four_code_list[dag_4code].para_1);
                }
                else{
                    for(i=0;i<dag_index;i++){
                        if(daggraph[i].loc==j && daggraph[i].con==0){
                            itoa(daggraph[i].value,four_code_para_improve[0],10);
                            break;
                        }
                    }
                    if(i==dag_index){
                        for(i=0;i<dag_index;i++){
                            if(daggraph[i].operate==-1&&daggraph[i].loc==j){
                                strcpy(four_code_para_improve[0],daggraph[i].name);
                                break;
                            }
                        }
                        if(i==dag_index){
                            strcpy(four_code_para_improve[0],dag_pointname[j]);
                        }
                    }
                }
                insert_four_code_dag(CRET);
                dag_delete();
                break;
            }
            case CNRET:{
                dag_export();
                dag_delete();
                insert_four_code_dag(CNRET);
                break;
            }
            case CRETVAL:{
                strcpy(dag_name,four_code_list[dag_4code].para_1);
                dag_left=-1;
                dag_right=-1;
                dag_loc=-1;
                dag_operate=10;
                dag_con=1;
                dag_value=0;
                int tmp = table_search(four_code_list[dag_4code].para_2);
                dag_type = symlist[tmp].type_data;
                /*dag_string = (char*)malloc(sizeof(char)*strlen(four_code_list[dag_4code].para_2));
                strcpy(dag_string,four_code_list[dag_4code].para_2);*/
                dag_insert();
                break;
            }
            case CLABEL:{
                dag_export();
                dag_delete();
                strcpy(four_code_para_improve[0],four_code_list[dag_4code].para_1);
                insert_four_code_dag(CLABEL);
                break;
            }
            case CSCANF:{
                for(i=0;i<dag_index;i++){
                    if(strcmp(tmp_name1,daggraph[i].name)==0){
                        loc_1 = i;
                    }
                }
                if(loc_1!=-1 && daggraph[loc_1].operate!=-1){
                    int j;
                    for(j=0;j<dag_index;j++){
                        if(daggraph[j].loc==daggraph[loc_1].loc){
                            break;
                        }
                    }
                    if(j==dag_index){
                        pro_dag_name();
                        strcpy(dag_name,dag_val_name);
                        dag_type = daggraph[loc_1].type;
                        dag_left = daggraph[loc_1].left;
                        dag_right = daggraph[loc_1].right;
                        dag_loc = daggraph[loc_1].loc;
                        dag_operate = daggraph[loc_1].operate;
                        dag_con = daggraph[loc_1].con;
                        dag_value = daggraph[loc_1].value;
                        dag_insert();
                    }
                    strcpy(dag_name,tmp_name1);
                    dag_left=last_index;
                    dag_right=-1;
                    dag_loc=-1;
                    dag_con=1;
                    dag_value=0;
                    dag_operate=7;
                    int tmp = table_search(tmp_name1);
                    dag_type = symlist[tmp].type_data;
                    tmp = dag_insert();
                    last_index = daggraph[tmp].loc;
                }
                else{
                    strcpy(dag_name,tmp_name1);
                    dag_left=last_index;
                    dag_right=-1;
                    dag_loc=-1;
                    dag_con=1;
                    dag_value=0;
                    dag_operate=7;
                    int tmp = table_search(tmp_name1);
                    dag_type = symlist[tmp].type_data;
                    tmp = dag_insert();
                    last_index = daggraph[tmp].loc;
                }
                break;
            }
            case CPRINTF:{
                int i,j;
                j=-1;
                for(i=0;i<dag_index;i++){
                    if(strcmp(daggraph[i].name,tmp_name1)==0){
                        j=i;
                    }
                }
                if(j==-1){
                    strcpy(dag_name,tmp_name1);
                    int tmp = table_search(tmp_name1);
                    dag_type = symlist[tmp].type_data;
                    dag_left=-1;
                    dag_right=-1;
                    dag_loc=-1;
                    dag_con=1;
                    dag_value=0;
                    dag_operate=-1;
                    j = dag_insert();
                }
                pro_dag_name();
                strcpy(dag_name,dag_val_name);
                dag_left = daggraph[j].loc;
                dag_right = last_index;
                dag_loc=-1;
                dag_con=-1;
                dag_value=-1;
                dag_operate=8;
                dag_type=1;
                int tmp = dag_insert();
                last_index = daggraph[tmp].loc;
                break;
            }
            case CPRINTF_ST:{
                pro_dag_name();
                strcpy(dag_name,dag_val_name);
                dag_left = -1;
                dag_right = last_index;
                dag_loc=-1;
                dag_con=-1;
                dag_value=0;
                dag_type=1;
                dag_operate=9;
                dag_string = (char*)malloc(sizeof(char)*strlen(four_code_list[dag_4code].index_string)+1);
                strcpy(dag_string,four_code_list[dag_4code].index_string);
                int tmp = dag_insert();
                last_index = daggraph[tmp].loc;
                break;
            }
            case CPUSH_STACK:{
                strcpy(four_code_para_improve[0],four_code_list[dag_4code].para_1);
                insert_four_code_dag(CPUSH_STACK);
                break;
            }
            case CPULL_STACK:{
                strcpy(four_code_para_improve[0],four_code_list[dag_4code].para_1);
                insert_four_code_dag(CPULL_STACK);
                break;
            }
            case CSAVE_ENV:{
                dag_export();
                push_print();
                dag_delete();
                insert_four_code_dag(CSAVE_ENV);
                break;
            }
            case CREV_ENV:{
                insert_four_code_dag(CREV_ENV);
                break;
            }
        }
    }
}

int dag_insert(){
    strcpy(daggraph[dag_index].name,dag_name);
    daggraph[dag_index].left=dag_left;
    daggraph[dag_index].right=dag_right;
    daggraph[dag_index].operate=dag_operate;
    daggraph[dag_index].type = dag_type;
    if(dag_loc==-1){
        daggraph[dag_index].loc = dag_count;
        dag_count++;
    }
    else{
        daggraph[dag_index].loc=dag_loc;
    }
    daggraph[dag_index].con=dag_con;
    daggraph[dag_index].value=dag_value;
    if(dag_operate==9){
        daggraph[dag_index].token_string = (char*)malloc(sizeof(char)*(strlen(dag_string)+1));
        strcpy(daggraph[dag_index].token_string,dag_string);
        free(dag_string);
    }
    else if(dag_operate==10){
        daggraph[dag_index].token_string = (char*)malloc(sizeof(char)*(strlen(four_code_list[dag_4code].para_2)+1));
        strcpy(daggraph[dag_index].token_string,four_code_list[dag_4code].para_2);
    }
    else{
        daggraph[dag_index].token_string=NULL;
    }
    //debug_fprintf(fp_dag,"insert name:%s left:%d right:%d loc:%d operate:%d con:%d value:%d string:%s\n"
    //              ,daggraph[dag_index].name,daggraph[dag_index].left,daggraph[dag_index].right,daggraph[dag_index].loc,daggraph[dag_index].operate,daggraph[dag_index].con,daggraph[dag_index].value,daggraph[dag_index].token_string);
    //debug_printf("insert name:%s left:%d right:%d loc:%d operate:%d con:%d value:%d string:%s\n"
    //             ,daggraph[dag_index].name,daggraph[dag_index].left,daggraph[dag_index].right,daggraph[dag_index].loc,daggraph[dag_index].operate,daggraph[dag_index].con,daggraph[dag_index].value,daggraph[dag_index].token_string);
    dag_index++;
    return (dag_index-1);
}

void dag_export(){
    //debug_printf("enter\n");
    int i,j,k;
    int cur_point=-1;
    int cur_index;
    char cur_name[Max_ident+1]={'\0'};
    int max_point=-1;
    for(i=0;i<dag_index;i++){
        debug_fprintf(fp_dag,"name:%s left:%d right:%d loc:%d operate:%d con:%d value:%d type:%d string:%s\n",
                      daggraph[i].name,daggraph[i].left,daggraph[i].right,daggraph[i].loc,daggraph[i].operate,daggraph[i].con,daggraph[i].value,daggraph[i].type,daggraph[i].token_string);
        //debug_printf("name:%s left:%d right:%d loc:%d operate:%d con:%d value:%d string:%s\n",
        //              daggraph[i].name,daggraph[i].left,daggraph[i].right,daggraph[i].loc,daggraph[i].operate,daggraph[i].con,daggraph[i].value,daggraph[i].token_string);
    }
    debug_fprintf(fp_dag,"\n");
    for(i=0;i<dag_index;i++){
        if(daggraph[i].loc>max_point){
            max_point = daggraph[i].loc;
        }
    }
    max_point=max_point+1;
    int* dag_father = (int*)malloc(sizeof(int)*(max_point+1));
    int* dag_use = (int*)malloc(sizeof(int)*(max_point+1));
    for(i=0;i<max_point;i++){
        dag_father[i]=0;
        dag_use[i]=0;
    }
    for(i=0;i<dag_index;i++){
        if(dag_use[daggraph[i].loc]==1){
            continue;
        }
        if(daggraph[i].left!=-1){
            dag_father[daggraph[i].left]++;
        }
        if(daggraph[i].right!=-1){
            dag_father[daggraph[i].right]++;
        }
        if(daggraph[i].operate==5){
            if(array_order[daggraph[i].loc]!=-1){
                for(j=0;j<dag_index;j++){
                    if(daggraph[j].left==array_order[daggraph[i].loc] && daggraph[j].operate==4){
                        dag_father[daggraph[j].loc]++;
                    }
                }
            }
        }
        dag_use[daggraph[i].loc]=1;
    }
    for(i=0;i<max_point;i++){
        dag_use[i]=0;
    }
    //debug_printf("1\n");
    while(1){
        cur_name[0]='\0';
        if(cur_point==-1){
            for(i=0;i<dag_index;i++){
                if(dag_father[daggraph[i].loc]==0 && dag_use[daggraph[i].loc]==0 && daggraph[i].operate!=-1 && daggraph[i].operate!=10 && daggraph[i].con!=0){
                    int m;
                    for(m=0;m<dag_index;m++){
                        if(daggraph[m].loc==daggraph[i].loc&&daggraph[m].operate==10){
                            break;
                        }
                    }
                    if(m==dag_index){
                        dag_use[daggraph[i].loc]=1;
                        cur_point = daggraph[i].loc;
                        dag_printorder[dag_printorder_index]=daggraph[i].loc;
                        dag_printorder_index++;
                        break;
                    }
                }
            }
        }
        if(cur_point==-1){
            for(i=0;i<dag_index;i++){
                if(dag_father[daggraph[i].loc]==0 && dag_use[daggraph[i].loc]==0 && daggraph[i].operate!=-1 && daggraph[i].con!=0){
                    dag_use[daggraph[i].loc]=1;
                    cur_point = daggraph[i].loc;
                    dag_printorder[dag_printorder_index]=daggraph[i].loc;
                    dag_printorder_index++;
                    break;
                }
            }
        }
        if(cur_point==-1){
            break;
        }
        for(i=0;i<dag_index;i++){
            if(daggraph[i].loc==cur_point){ //&& daggraph[i].operate!=-1){
                if(cur_name[0]=='\0'){
                    cur_index=i;
                    /*if(daggraph[i].con==0){
                        itoa(daggraph[i].value,cur_name,10);
                        itoa(daggraph[i].value,dag_pointname[daggraph[i].loc],10);
                    }
                    else{
                        strcpy(cur_name,daggraph[i].name);
                        int tmp;
                        for(tmp=table_index;tmp<loc_table;tmp++){
                            if(strcmp(symlist[tmp].name,daggraph[i].name)==0){
                                break;
                            }
                        }
                        if(tmp==loc_table){
                            strcpy(cur_name,daggraph[i].name);
                            strcpy(dag_pointname[daggraph[i].loc],daggraph[i].name);
                            strcpy(tmp_name,daggraph[i].name);
                            tmp_type=1;
                            tmp_type_data=0;
                            tmp_global=1;
                            tmp_aindex=-1;
                            tmp_para=-1;
                            table_insert();
                        }
                    }*/
                }
                else{
                    if((daggraph[i].name[0]<='z'&&daggraph[i].name[0]>='a')||daggraph[i].name[0]=='_'){
                        cur_index=i;
                        /*strcpy(cur_name,daggraph[i].name);
                        strcpy(dag_pointname[daggraph[i].loc],daggraph[i].name);*/
                        break;
                    }
                }
            }
        }
        /*for(i=0;i<max_point;i++){
            if(dag_pointname[i][0]=='T'||dag_pointname[i][0]=='D'){
                for(j=table_index;j<loc_table;j++){
                    if(strcmp(dag_pointname[i],symlist[j].name)==0){
                        break;
                    }
                }
                if(j==loc_table){
                    strcpy(tmp_name,dag_pointname[i]);
                    tmp_type=1;
                    tmp_type_data=0;
                    tmp_aindex=-1;
                    tmp_para=-1;
                    tmp_global=1;
                    table_insert();
                }
            }
        }*/
        /*if(cur_name[0]=='\0'){
            for(i=0;i<dag_index;i++){
                if(daggraph[i].loc==cur_point){
                    strcpy(dag_pointname[daggraph[i].loc],daggraph[i].name);
                    break;
                }
            }
            dag_printorder_index--;
        }*/
        if(daggraph[cur_index].left!=-1){
            dag_father[daggraph[cur_index].left]--;
        }
        if(daggraph[cur_index].right!=-1){
            dag_father[daggraph[cur_index].right]--;
        }
        if(daggraph[cur_index].operate==5){
            if(array_order[daggraph[cur_index].loc]!=-1){
                for(j=0;j<dag_index;j++){
                    if(daggraph[j].left==array_order[daggraph[cur_index].loc]&&daggraph[j].operate==4){
                        dag_father[daggraph[j].loc]--;
                    }
                }
            }
        }
        if(dag_father[daggraph[cur_index].left]==0){
            for(i=0;i<dag_index;i++){
                if(daggraph[i].loc==daggraph[cur_index].left && daggraph[i].operate!=-1 && daggraph[i].con!=0){
                    int m;
                    for(m=0;m<dag_index;m++){
                        if(daggraph[m].operate==10 && daggraph[m].loc==daggraph[i].loc){
                            break;
                        }
                    }
                    if(m==dag_index){
                        cur_point=daggraph[cur_index].left;
                        dag_use[cur_point]=1;
                        dag_printorder[dag_printorder_index]=cur_point;
                        dag_printorder_index++;
                        break;
                    }
                }
            }
            if(i==dag_index){
                cur_point=-1;
            }
        }
        else{
            cur_point=-1;
        }
    }
    //debug_printf("2\n");
    for(j=0;j<max_point;j++){
        cur_name[0]='\0';
        for(i=0;i<dag_index;i++){
            if(daggraph[i].loc==j){
                if(cur_name[0]=='\0'){
                    if(daggraph[i].con==0){
                        itoa(daggraph[i].value,cur_name,10);
                        itoa(daggraph[i].value,dag_pointname[daggraph[i].loc],10);
                    }
                    else{
                        strcpy(cur_name,daggraph[i].name);
                        strcpy(dag_pointname[daggraph[i].loc],daggraph[i].name);
                        int tmp;
                        for(tmp=0;tmp<loc_table;tmp++){
                            if(strcmp(symlist[tmp].name,daggraph[i].name)==0){
                                break;
                            }
                        }
                        if(tmp==loc_table && daggraph[i].operate!=9){
                            strcpy(tmp_name,daggraph[i].name);
                            tmp_type=1;
                            tmp_type_data=0;
                            tmp_global=1;
                            tmp_aindex=-1;
                            tmp_para=-1;
                            table_insert();
                        }
                    }
                }
                else{
                    if(((daggraph[i].name[0]<='z'&&daggraph[i].name[0]>='a')||daggraph[i].name[0]=='_')&&daggraph[i].operate!=6){
                        strcpy(cur_name,daggraph[i].name);
                        strcpy(dag_pointname[daggraph[i].loc],daggraph[i].name);
                        break;
                    }
                }
            }
        }
    }
    //debug_printf("3\n");
    for(i=0;i<dag_index;i++){
        if(daggraph[i].operate==-1){
            for(j=0;j<dag_index;j++){
                if((strcmp(daggraph[i].name,daggraph[j].name)==0)&&i!=j && daggraph[j].operate!=5){
                    for(k=0;k<max_point;k++){
                        if((strcmp(dag_pointname[k],daggraph[i].name)==0)&&k==daggraph[i].loc){
                            pro_dag_name();
                            strcpy(four_code_para_improve[0],dag_val_name);
                            strcpy(four_code_para_improve[1],daggraph[i].name);
                            insert_four_code_dag(CASSIGN);
                            strcpy(dag_pointname[k],dag_val_name);
                            strcpy(tmp_name,dag_val_name);
                            tmp_type=1;
                            tmp_type_data=0;
                            tmp_global=1;
                            tmp_aindex=-1;
                            tmp_para=-1;
                            table_insert();
                        }
                    }
                }
            }
        }
    }
    //debug_printf("4\n");
    for(i=dag_printorder_index-1;i>=0;i--){
        for(j=0;j<dag_index;j++){
            if((daggraph[j].loc==dag_printorder[i]) && (daggraph[j].operate!=-1)){ //&& strcmp(dag_pointname[daggraph[j].loc],daggraph[j].name)==0){
                switch(daggraph[j].operate){
                    case 0:{}
                    case 1:{}
                    case 2:{}
                    case 3:{}
                    case 4:{}
                    case 5:{
                        strcpy(four_code_para_improve[0],dag_pointname[daggraph[j].loc]);
                        for(k=0;k<dag_index;k++){
                            if(daggraph[k].loc==daggraph[j].left && daggraph[k].con==0){
                                itoa(daggraph[k].value,four_code_para_improve[1],10);
                                break;
                            }
                        }
                        if(k==dag_index){
                            /*for(k=0;k<dag_index;k++){
                                if(daggraph[k].loc==daggraph[j].left && daggraph[k].operate==-1){
                                    strcpy(four_code_para_improve[1],daggraph[k].name);
                                    break;
                                }
                            }
                            if(k==dag_index){
                                 strcpy(four_code_para_improve[1],dag_pointname[daggraph[j].left]);
                            }*/
                            strcpy(four_code_para_improve[1],dag_pointname[daggraph[j].left]);
                        }
                        for(k=0;k<dag_index;k++){
                            if(daggraph[k].loc==daggraph[j].right && daggraph[k].con==0){
                                itoa(daggraph[k].value,four_code_para_improve[2],10);
                                break;
                            }
                        }
                        if(k==dag_index){
                            /*for(k=0;k<dag_index;k++){
                                if(daggraph[k].loc==daggraph[j].right && daggraph[k].operate==-1){
                                    strcpy(four_code_para_improve[2],daggraph[k].name);
                                    break;
                                }
                            }
                            if(k==dag_index){
                                 strcpy(four_code_para_improve[2],dag_pointname[daggraph[j].right]);
                            }*/
                            strcpy(four_code_para_improve[2],dag_pointname[daggraph[j].right]);
                        }
                        if(daggraph[j].operate==4&&four_code_para_improve[1][0]=='D'){
                            int m;
                            for(m=1;m<Max_ident;m++){
                                if(four_code_para_improve[1][m]>'9'||four_code_para_improve[1][m]<'0')
                                    break;
                            }
                            for(k=0;k<Max_ident-1;k++){
                                four_code_para_improve[1][k]=four_code_para_improve[1][k+m];
                            }
                        }
                        if(daggraph[j].operate==5&&four_code_para_improve[0][0]=='D'){
                            int m;
                            for(m=1;m<Max_ident;m++){
                                if(four_code_para_improve[0][m]>'9'||four_code_para_improve[0][m]<'0')
                                    break;
                            }
                            for(k=0;k<Max_ident-1;k++){
                                four_code_para_improve[0][k]=four_code_para_improve[0][k+m];
                            }
                        }
                        insert_four_code_dag((daggraph[j].operate)+1);
                        break;
                    }
                    case 6:{
                        break;
                    }
                    case 7:{
                        strcpy(four_code_para_improve[0],dag_pointname[daggraph[j].loc]);
                        insert_four_code_dag(CSCANF);
                        break;
                    }
                    case 8:{
                        for(k=0;k<dag_index;k++){
                            if(daggraph[k].loc==daggraph[j].left && daggraph[k].con==0){
                                if(daggraph[k].type==0){
                                    itoa(daggraph[k].value,four_code_para_improve[0],10);
                                    break;
                                }
                                else{
                                    four_code_para_improve[0][0]='\'';
                                    four_code_para_improve[0][1]=(char)daggraph[k].value;
                                    four_code_para_improve[0][2]='\'';
                                    four_code_para_improve[0][3]='\0';
                                    break;
                                }
                            }
                        }
                        if(k==dag_index){
                            strcpy(four_code_para_improve[0],dag_pointname[daggraph[j].left]);
                        }
                        insert_four_code_dag(CPRINTF);
                        break;
                    }
                    case 9:{
                        token_string = (char*)malloc(sizeof(char)*strlen(daggraph[j].token_string)+1);
                        strcpy(token_string,daggraph[j].token_string);
                        insert_four_code_dag(CPRINTF_ST);
                        free(token_string);
                        break;
                    }
                    case 10:{
                        strcpy(four_code_para_improve[0],dag_pointname[daggraph[j].loc]);
                        strcpy(four_code_para_improve[1],daggraph[j].token_string);
                        insert_four_code_dag(CRETVAL);
                        break;
                    }
                }
                break;
            }
        }
    }
    //debug_printf("5\n");
    for(i=0,j=0;i<dag_index;i++){
        int flag=0;
        int m;
        if((((daggraph[i].name[0]<='z'&&daggraph[i].name[0]>='a')||(daggraph[i].name[0]=='_'))&&(daggraph[i].operate!=-1))){
            for(j=0;j<max_point;j++){
                if(strcmp(daggraph[i].name,dag_pointname[j])==0){
                    int k;
                    for(k=0;k<dag_index;k++){
                        if(daggraph[k].loc==j && ((daggraph[k].operate==-1)||((daggraph[k].operate==1)&&daggraph[k].con==0)||(daggraph[k].operate==6 && daggraph[k].con==0))){
                            flag=1;
                            m=k;
                            break;
                        }
                    }
                    if(k==dag_index){
                        break;
                    }
                }
            }
        }
        if(j==max_point){
            strcpy(four_code_para_improve[0],daggraph[i].name);
            if(daggraph[i].con==0){
                itoa(daggraph[i].value,four_code_para_improve[1],10);
            }
            else{
                if(flag==1){
                    strcpy(four_code_para_improve[1],daggraph[m].name);
                }
                else{
                    strcpy(four_code_para_improve[1],dag_pointname[daggraph[i].loc]);
                }
            }
            insert_four_code_dag(CASSIGN);
            j=0;
        }
    }
    for(i=0;i<dag_index;i++){
        if(daggraph[i].name[0]=='T'){
            for(j=0;j<temp_store_index;j++){
                if(strcmp(daggraph[i].name,temp_store[j])==0){
                    strcpy(four_code_para_improve[0],daggraph[i].name);
                    if(daggraph[i].con==0){
                        itoa(daggraph[i].value,four_code_para_improve[1],10);
                    }
                    else{
                        strcpy(four_code_para_improve[1],dag_pointname[daggraph[i].loc]);
                    }
                    insert_four_code_dag(CASSIGN);
                    break;
                }
            }
        }
    }
    free(dag_father);
    free(dag_use);
    return;
}
void push_print(){
    int i,j;
    for(i=0;i<push_index;i++){
        for(j=0;j<dag_index;j++){
            if(daggraph[j].loc==push_list[i]&&daggraph[j].con==0){
                itoa(daggraph[j].value,four_code_para_improve[0],10);
                break;
            }
        }
        if(j==dag_index){
            for(j=0;j<dag_index;j++){
                if(daggraph[j].loc==push_list[i]&&daggraph[j].operate==-1){
                    strcpy(four_code_para_improve[0],daggraph[j].name);
                    break;
                }
            }
            if(j==dag_index){
                strcpy(four_code_para_improve[0],dag_pointname[push_list[i]]);
            }
        }
        strcpy(four_code_para_improve[1],push_function);
        itoa(i,four_code_para_improve[2],10);
        insert_four_code_dag(CPUSH);
    }
}
void dag_delete(){
    dag_index=0;
    dag_count=0;
    last_index=-1;
    last_array=-1;
    push_index=0;
    dag_printorder_index=0;
    point_index=0;
    return;
}

void find_tmp_store(){
    int i,j;
    int para1,para2,para3;
    temp_store_index=0;
    for(i=dag_4code;i<four_code_index;i++){
        if(four_code_list[i].para_1[0]=='T'){
            j=1;
            para1=0;
            while(four_code_list[i].para_1[j]>='0'&&four_code_list[i].para_1[j]<='9'){
                para1 = para1*10+four_code_list[i].para_1[j]-'0';
                //printf("there1 %d\n" ,para1);
                j++;
            }
            if(para1>temp_max){
                temp_max=para1;
            }
            if(para1<temp_last){
                strcpy(temp_store[temp_store_index],four_code_list[i].para_1);
                temp_store_index++;
                for(j=table_index;j<loc_table;j++){
                    if(strcmp(symlist[j].name,four_code_list[i].para_1)==0){
                        break;
                    }
                }
                if(j==loc_table){
                    tmp_type=1;
                    tmp_type_data=0;
                    tmp_global=1;
                    tmp_aindex=-1;
                    tmp_para=-1;
                    strcpy(tmp_name,four_code_list[i].para_1);
                    table_insert();
                }
                //printf("%d %d %s\n",para1,temp_last,four_code_list[i].para_1);
            }
        }
        if(four_code_list[i].para_2[0]=='T'){
            j=1;
            para2=0;
            while(four_code_list[i].para_2[j]>='0'&&four_code_list[i].para_2[j]<='9'){
                para2 = para2*10+four_code_list[i].para_2[j]-'0';
                //printf("there2 %d\n" ,para2);
                j++;
            }
            if(para2>temp_max){
                temp_max=para2;
            }
            if(para2<temp_last){
                strcpy(temp_store[temp_store_index],four_code_list[i].para_2);
                temp_store_index++;
                for(j=table_index;j<loc_table;j++){
                    if(strcmp(symlist[j].name,four_code_list[i].para_2)==0){
                        break;
                    }
                }
                if(j==loc_table){
                    tmp_type=1;
                    tmp_type_data=0;
                    tmp_global=1;
                    tmp_aindex=-1;
                    tmp_para=-1;
                    strcpy(tmp_name,four_code_list[i].para_2);
                    table_insert();
                }
                //printf("%d %d %s\n",para2,temp_last,four_code_list[i].para_2);
            }
        }
        if(four_code_list[i].para_3[0]=='T'){
            j=1;
            para3=0;
            while(four_code_list[i].para_3[j]>='0'&&four_code_list[i].para_3[j]<='9'){
                para3 = para3*10+four_code_list[i].para_3[j]-'0';
                //printf("there3 %d\n" ,para3);
                j++;
            }
            if(para3>temp_max){
                temp_max=para3;
            }
            if(para3<temp_last){
                strcpy(temp_store[temp_store_index],four_code_list[i].para_3);
                temp_store_index++;
                for(j=table_index;j<loc_table;j++){
                    if(strcmp(symlist[j].name,four_code_list[i].para_3)==0){
                        break;
                    }
                }
                if(j==loc_table){
                    tmp_type=1;
                    tmp_type_data=0;
                    tmp_global=1;
                    tmp_aindex=-1;
                    tmp_para=-1;
                    strcpy(tmp_name,four_code_list[i].para_3);
                    table_insert();
                }
                //printf("%d %d %s\n",para1,temp_last,four_code_list[i].para_3);
            }
        }
        if(four_code_list[i].code==CEQL||four_code_list[i].code==CNEQ||four_code_list[i].code==CGTR||four_code_list[i].code==GEQ
           ||four_code_list[i].code==CLSS||four_code_list[i].code==CLEQ||four_code_list[i].code==CJUMP||four_code_list[i].code==CRET
           ||four_code_list[i].code==CNRET||four_code_list[i].code==CSAVE_ENV){
            temp_last=temp_max;
            //printf("change %d\n",temp_last);
           }
    }
    return;
}
