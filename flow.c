#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "define.h"

int not_in_set(char* name,char set_list[][Max_ident+1],int set_index){
    int i;
    for(i=0;i<set_index;i++){
        if(strcmp(name,set_list[i])==0){
            return 0;
        }
    }
    return 1;
}

int cal_out(char set1[][Max_ident+1],char set2[][Max_ident+1],
            char (*tarset)[Max_ident+1],int set1_index,int set2_index){
    int i,j;
    int tar_index=0;
    for(i=0;i<set1_index;i++){
        strcpy(tarset[i],set1[i]);
        tar_index++;
    }
    for(i=0;i<set2_index;i++){
        for(j=0;j<tar_index;j++){
            if(strcmp(tarset[j],set2[i])==0){
                break;
            }
        }
        if(j==tar_index){
            strcpy(tarset[tar_index],set2[i]);
            tar_index++;
        }
    }
    return tar_index;
}

int cal_in(char set1[][Max_ident+1],char set2[][Max_ident+1],char set3[][Max_ident+1],
            char (*tarset)[Max_ident+1],int set1_index,int set2_index,int set3_index){
    int i,j,k;
    int tar_index=0;
    for(i=0;i<set1_index;i++){
        strcpy(tarset[i],set1[i]);
        tar_index++;
    }
    for(i=0;i<set2_index;i++){
        for(j=0;j<tar_index;j++){
            if(strcmp(tarset[j],set2[i])==0){
                break;
            }
        }
        for(k=0;k<set3_index;k++){
            if(strcmp(set3[k],set2[i])==0){
                break;
            }
        }
        if(j==tar_index && k==set3_index){
            strcpy(tarset[tar_index],set2[i]);
            tar_index++;
        }
    }
    //printf("%d\n",tar_index);
    return tar_index;
}

void flow_init(){
    int j,m,n;
    for(j=0;j<block_index;j++){
        block_list[j].begin_block=flow_dag;
        block_list[j].end_block=flow_dag;
        block_list[j].use_index=0;
        block_list[j].def_index=0;
        block_list[j].in_index=0;
        block_list[j].out_index=0;
        block_list[j].next_block[0]=0;
        block_list[j].next_block[1]=0;
    }
    for(m=0;m<var_count;m++){
        for(n=0;n<var_count;n++){
            var_graph[m][n]=0;
        }
    }
    var_count=0;
    block_index = 0;
    block_list[block_index].begin_block=flow_dag;
    block_list[block_index].end_block=flow_dag;
    block_list[block_index].use_index=0;
    block_list[block_index].def_index=0;
    block_index++;
    tregister_index=0;
}

void find_block(){
    int i = flow_dag;
    int j;
    int m,n;
    int not_in_use,not_in_def;
    for(;i<four_code_index_improve;i++){
        not_in_use=1;
        not_in_def=1;
        switch(four_code_list_improve[i].code){
            case CPASS:{
                break;
            }
            case CADD:{}
            case CMINUS:{}
            case CTIME:{}
            case CDIV:{
                if((four_code_list_improve[i].para_2[0]<='9'&&four_code_list_improve[i].para_2[0]>='0')||four_code_list_improve[i].para_2[0]=='-'){}
                else{
                    for(j=0;j<block_list[block_index].use_index;j++){
                        if(not_in_set(four_code_list_improve[i].para_2,block_list[block_index].use,block_list[block_index].use_index)){
                            not_in_use=1;
                        }
                        else{
                            not_in_use=0;
                        }
                    }
                    for(j=0;j<block_list[block_index].def_index;j++){
                        if(not_in_set(four_code_list_improve[i].para_2,block_list[block_index].def,block_list[block_index].def_index)){
                            not_in_def=1;
                        }
                        else{
                            not_in_def=0;
                        }
                    }
                     if(not_in_use && not_in_def){
                        for(j=table_index;j<loc_table;j++){
                            if(strcmp(symlist[j].name,four_code_list_improve[i].para_2)==0){
                                break;
                            }
                        }
                        if(j!=loc_table){
                            strcpy(block_list[block_index].use[block_list[block_index].use_index],four_code_list_improve[i].para_2);
                            block_list[block_index].use_index++;
                        }
                    }
                }
                if((four_code_list_improve[i].para_3[0]<='9'&&four_code_list_improve[i].para_3[0]>='0')||four_code_list_improve[i].para_3[0]=='-'){}
                else{
                    for(j=0;j<block_list[block_index].use_index;j++){
                        if(not_in_set(four_code_list_improve[i].para_3,block_list[block_index].use,block_list[block_index].use_index)){
                            not_in_use=1;
                        }
                        else{
                            not_in_use=0;
                        }
                    }
                    for(j=0;j<block_list[block_index].def_index;j++){
                        if(not_in_set(four_code_list_improve[i].para_3,block_list[block_index].def,block_list[block_index].def_index)){
                            not_in_def=1;
                        }
                        else{
                            not_in_def=0;
                        }
                    }
                     if(not_in_use && not_in_def){
                        for(j=table_index;j<loc_table;j++){
                            if(strcmp(symlist[j].name,four_code_list_improve[i].para_3)==0){
                                break;
                            }
                        }
                        if(j!=loc_table){
                            strcpy(block_list[block_index].use[block_list[block_index].use_index],four_code_list_improve[i].para_3);
                            block_list[block_index].use_index++;
                        }
                    }
                }
                for(j=0;j<block_list[block_index].use_index;j++){
                    if(not_in_set(four_code_list_improve[i].para_1,block_list[block_index].use,block_list[block_index].use_index)){
                        not_in_use=1;
                    }
                    else{
                        not_in_use=0;
                    }
                }
                for(j=0;j<block_list[block_index].def_index;j++){
                    if(not_in_set(four_code_list_improve[i].para_1,block_list[block_index].def,block_list[block_index].def_index)){
                        not_in_def=1;
                    }
                    else{
                        not_in_def=0;
                    }
                }
                if(not_in_use && not_in_def){
                        for(j=table_index;j<loc_table;j++){
                            if(strcmp(symlist[j].name,four_code_list_improve[i].para_1)==0){
                                break;
                            }
                        }
                        if(j!=loc_table){
                            strcpy(block_list[block_index].def[block_list[block_index].def_index],four_code_list_improve[i].para_1);
                            block_list[block_index].def_index++;
                        }
                    }
                break;
            }
            case CARRVAL:{
                if((four_code_list_improve[i].para_3[0]<='9'&&four_code_list_improve[i].para_3[0]>='0')||four_code_list_improve[i].para_3[0]=='-'){}
                else{
                    for(j=0;j<block_list[block_index].use_index;j++){
                        if(not_in_set(four_code_list_improve[i].para_3,block_list[block_index].use,block_list[block_index].use_index)){
                            not_in_use=1;
                        }
                        else{
                            not_in_use=0;
                        }
                    }
                    for(j=0;j<block_list[block_index].def_index;j++){
                        if(not_in_set(four_code_list_improve[i].para_3,block_list[block_index].def,block_list[block_index].def_index)){
                            not_in_def=1;
                        }
                        else{
                            not_in_def=0;
                        }
                    }
                     if(not_in_use && not_in_def){
                        for(j=table_index;j<loc_table;j++){
                            if(strcmp(symlist[j].name,four_code_list_improve[i].para_3)==0){
                                break;
                            }
                        }
                        if(j!=loc_table){
                            strcpy(block_list[block_index].use[block_list[block_index].use_index],four_code_list_improve[i].para_3);
                            block_list[block_index].use_index++;
                        }
                    }
                }
                for(j=0;j<block_list[block_index].use_index;j++){
                    if(not_in_set(four_code_list_improve[i].para_1,block_list[block_index].use,block_list[block_index].use_index)){
                        not_in_use=1;
                    }
                    else{
                        not_in_use=0;
                    }
                }
                for(j=0;j<block_list[block_index].def_index;j++){
                    if(not_in_set(four_code_list_improve[i].para_1,block_list[block_index].def,block_list[block_index].def_index)){
                        not_in_def=1;
                    }
                    else{
                        not_in_def=0;
                    }
                }
                if(not_in_use && not_in_def){
                        for(j=table_index;j<loc_table;j++){
                            if(strcmp(symlist[j].name,four_code_list_improve[i].para_1)==0){
                                break;
                            }
                        }
                        if(j!=loc_table){
                            strcpy(block_list[block_index].def[block_list[block_index].def_index],four_code_list_improve[i].para_1);
                            block_list[block_index].def_index++;
                        }
                    }
                break;
            }
            case CARRASN:{
                if((four_code_list_improve[i].para_2[0]<='9'&&four_code_list_improve[i].para_2[0]>='0')||four_code_list_improve[i].para_2[0]=='-'){}
                else{
                    for(j=0;j<block_list[block_index].use_index;j++){
                        if(not_in_set(four_code_list_improve[i].para_2,block_list[block_index].use,block_list[block_index].use_index)){
                            not_in_use=1;
                        }
                        else{
                            not_in_use=0;
                        }
                    }
                    for(j=0;j<block_list[block_index].def_index;j++){
                        if(not_in_set(four_code_list_improve[i].para_2,block_list[block_index].def,block_list[block_index].def_index)){
                            not_in_def=1;
                        }
                        else{
                            not_in_def=0;
                        }
                    }
                     if(not_in_use && not_in_def){
                        for(j=table_index;j<loc_table;j++){
                            if(strcmp(symlist[j].name,four_code_list_improve[i].para_2)==0){
                                break;
                            }
                        }
                        if(j!=loc_table){
                            strcpy(block_list[block_index].use[block_list[block_index].use_index],four_code_list_improve[i].para_2);
                            block_list[block_index].use_index++;
                        }
                    }
                }
                if((four_code_list_improve[i].para_3[0]<='9'&&four_code_list_improve[i].para_3[0]>='0')||four_code_list_improve[i].para_3[0]=='-'){}
                else{
                    for(j=0;j<block_list[block_index].use_index;j++){
                        if(not_in_set(four_code_list_improve[i].para_3,block_list[block_index].use,block_list[block_index].use_index)){
                            not_in_use=1;
                        }
                        else{
                            not_in_use=0;
                        }
                    }
                    for(j=0;j<block_list[block_index].def_index;j++){
                        if(not_in_set(four_code_list_improve[i].para_3,block_list[block_index].def,block_list[block_index].def_index)){
                            not_in_def=1;
                        }
                        else{
                            not_in_def=0;
                        }
                    }
                     if(not_in_use && not_in_def){
                        for(j=table_index;j<loc_table;j++){
                            if(strcmp(symlist[j].name,four_code_list_improve[i].para_3)==0){
                                break;
                            }
                        }
                        if(j!=loc_table){
                            strcpy(block_list[block_index].use[block_list[block_index].use_index],four_code_list_improve[i].para_3);
                            block_list[block_index].use_index++;
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
                if((four_code_list_improve[i].para_2[0]<='9'&&four_code_list_improve[i].para_2[0]>='0')||four_code_list_improve[i].para_2[0]=='-'){}
                else{
                    for(j=0;j<block_list[block_index].use_index;j++){
                        if(not_in_set(four_code_list_improve[i].para_2,block_list[block_index].use,block_list[block_index].use_index)){
                            not_in_use=1;
                        }
                        else{
                            not_in_use=0;
                        }
                    }
                    for(j=0;j<block_list[block_index].def_index;j++){
                        if(not_in_set(four_code_list_improve[i].para_2,block_list[block_index].def,block_list[block_index].def_index)){
                            not_in_def=1;
                        }
                        else{
                            not_in_def=0;
                        }
                    }
                     if(not_in_use && not_in_def){
                        for(j=table_index;j<loc_table;j++){
                            if(strcmp(symlist[j].name,four_code_list_improve[i].para_2)==0){
                                break;
                            }
                        }
                        if(j!=loc_table){
                            strcpy(block_list[block_index].use[block_list[block_index].use_index],four_code_list_improve[i].para_2);
                            block_list[block_index].use_index++;
                        }
                    }
                }
                if((four_code_list_improve[i].para_1[0]<='9'&&four_code_list_improve[i].para_1[0]>='0')||four_code_list_improve[i].para_1[0]=='-'){}
                else{
                    for(j=0;j<block_list[block_index].use_index;j++){
                        if(not_in_set(four_code_list_improve[i].para_1,block_list[block_index].use,block_list[block_index].use_index)){
                            not_in_use=1;
                        }
                        else{
                            not_in_use=0;
                        }
                    }
                    for(j=0;j<block_list[block_index].def_index;j++){
                        if(not_in_set(four_code_list_improve[i].para_1,block_list[block_index].def,block_list[block_index].def_index)){
                            not_in_def=1;
                        }
                        else{
                            not_in_def=0;
                        }
                    }
                     if(not_in_use && not_in_def){
                        for(j=table_index;j<loc_table;j++){
                            if(strcmp(symlist[j].name,four_code_list_improve[i].para_1)==0){
                                break;
                            }
                        }
                        if(j!=loc_table){
                            strcpy(block_list[block_index].use[block_list[block_index].use_index],four_code_list_improve[i].para_1);
                            block_list[block_index].use_index++;
                        }
                    }
                }
                block_list[block_index].end_block = i;
                block_index++;
                block_list[block_index].begin_block = i+1;
                break;
            }
            case CJUMP:{
                block_list[block_index].end_block = i;
                block_index++;
                block_list[block_index].begin_block = i+1;
                break;
            }
            case CASSIGN:{
                if((four_code_list_improve[i].para_2[0]<='9'&&four_code_list_improve[i].para_2[0]>='0')||four_code_list_improve[i].para_2[0]=='-'){}
                else{
                    for(j=0;j<block_list[block_index].use_index;j++){
                        if(not_in_set(four_code_list_improve[i].para_2,block_list[block_index].use,block_list[block_index].use_index)){
                            not_in_use=1;
                        }
                        else{
                            not_in_use=0;
                        }
                    }
                    for(j=0;j<block_list[block_index].def_index;j++){
                        if(not_in_set(four_code_list_improve[i].para_2,block_list[block_index].def,block_list[block_index].def_index)){
                            not_in_def=1;
                        }
                        else{
                            not_in_def=0;
                        }
                    }
                     if(not_in_use && not_in_def){
                        for(j=table_index;j<loc_table;j++){
                            if(strcmp(symlist[j].name,four_code_list_improve[i].para_2)==0){
                                break;
                            }
                        }
                        if(j!=loc_table){
                            strcpy(block_list[block_index].use[block_list[block_index].use_index],four_code_list_improve[i].para_2);
                            block_list[block_index].use_index++;
                        }
                    }
                }
                for(j=0;j<block_list[block_index].use_index;j++){
                    if(not_in_set(four_code_list_improve[i].para_1,block_list[block_index].use,block_list[block_index].use_index)){
                        not_in_use=1;
                    }
                    else{
                        not_in_use=0;
                    }
                }
                for(j=0;j<block_list[block_index].def_index;j++){
                    if(not_in_set(four_code_list_improve[i].para_1,block_list[block_index].def,block_list[block_index].def_index)){
                        not_in_def=1;
                    }
                    else{
                        not_in_def=0;
                    }
                }
                if(not_in_use && not_in_def){
                        for(j=table_index;j<loc_table;j++){
                            if(strcmp(symlist[j].name,four_code_list_improve[i].para_1)==0){
                                break;
                            }
                        }
                        if(j!=loc_table){
                            strcpy(block_list[block_index].def[block_list[block_index].def_index],four_code_list_improve[i].para_1);
                            block_list[block_index].def_index++;
                        }
                    }
                break;
            }
            case CPUSH:{
                if((four_code_list_improve[i].para_1[0]<='9'&&four_code_list_improve[i].para_1[0]>='0')||four_code_list_improve[i].para_1[0]=='-'){}
                else{
                    for(j=0;j<block_list[block_index].use_index;j++){
                        if(not_in_set(four_code_list_improve[i].para_1,block_list[block_index].use,block_list[block_index].use_index)){
                            not_in_use=1;
                        }
                        else{
                            not_in_use=0;
                        }
                    }
                    for(j=0;j<block_list[block_index].def_index;j++){
                        if(not_in_set(four_code_list_improve[i].para_1,block_list[block_index].def,block_list[block_index].def_index)){
                            not_in_def=1;
                        }
                        else{
                            not_in_def=0;
                        }
                    }
                     if(not_in_use && not_in_def){
                        for(j=table_index;j<loc_table;j++){
                            if(strcmp(symlist[j].name,four_code_list_improve[i].para_1)==0){
                                break;
                            }
                        }
                        if(j!=loc_table){
                            strcpy(block_list[block_index].use[block_list[block_index].use_index],four_code_list_improve[i].para_1);
                            block_list[block_index].use_index++;
                        }
                    }
                }
                break;
            }
            case CCALL:{
                break;
            }
            case CRET:{
                if((four_code_list_improve[i].para_1[0]<='9'&&four_code_list_improve[i].para_1[0]>='0')||four_code_list_improve[i].para_1[0]=='-'){}
                else{
                    for(j=0;j<block_list[block_index].use_index;j++){
                        if(not_in_set(four_code_list_improve[i].para_1,block_list[block_index].use,block_list[block_index].use_index)){
                            not_in_use=1;
                        }
                        else{
                            not_in_use=0;
                        }
                    }
                    for(j=0;j<block_list[block_index].def_index;j++){
                        if(not_in_set(four_code_list_improve[i].para_1,block_list[block_index].def,block_list[block_index].def_index)){
                            not_in_def=1;
                        }
                        else{
                            not_in_def=0;
                        }
                    }
                     if(not_in_use && not_in_def){
                        for(j=table_index;j<loc_table;j++){
                            if(strcmp(symlist[j].name,four_code_list_improve[i].para_1)==0){
                                break;
                            }
                        }
                        if(j!=loc_table){
                            strcpy(block_list[block_index].use[block_list[block_index].use_index],four_code_list_improve[i].para_1);
                            block_list[block_index].use_index++;
                        }
                    }
                }
                block_list[block_index].end_block = i;
                block_index++;
                block_list[block_index].begin_block = i+1;
                break;
            }
            case CNRET:{
                block_list[block_index].end_block = i;
                block_index++;
                block_list[block_index].begin_block = i+1;
                break;
            }
            case CRETVAL:{
                 for(j=0;j<block_list[block_index].use_index;j++){
                    if(not_in_set(four_code_list_improve[i].para_1,block_list[block_index].use,block_list[block_index].use_index)){
                        not_in_use=1;
                    }
                    else{
                        not_in_use=0;
                    }
                }
                for(j=0;j<block_list[block_index].def_index;j++){
                    if(not_in_set(four_code_list_improve[i].para_1,block_list[block_index].def,block_list[block_index].def_index)){
                        not_in_def=1;
                    }
                    else{
                        not_in_def=0;
                    }
                }
                if(not_in_use && not_in_def){
                        for(j=table_index;j<loc_table;j++){
                            if(strcmp(symlist[j].name,four_code_list_improve[i].para_1)==0){
                                break;
                            }
                        }
                        if(j!=loc_table){
                            strcpy(block_list[block_index].def[block_list[block_index].def_index],four_code_list_improve[i].para_1);
                            block_list[block_index].def_index++;
                        }
                    }
                break;
            }
            case CLABEL:{
                if(block_list[block_index].begin_block == i){
                    break;
                }
                block_list[block_index].end_block = i-1;
                block_index++;
                block_list[block_index].begin_block = i;
                break;
            }
            case CSCANF:{
                 for(j=0;j<block_list[block_index].use_index;j++){
                    if(not_in_set(four_code_list_improve[i].para_1,block_list[block_index].use,block_list[block_index].use_index)){
                        not_in_use=1;
                    }
                    else{
                        not_in_use=0;
                    }
                }
                for(j=0;j<block_list[block_index].def_index;j++){
                    if(not_in_set(four_code_list_improve[i].para_1,block_list[block_index].def,block_list[block_index].def_index)){
                        not_in_def=1;
                    }
                    else{
                        not_in_def=0;
                    }
                }
                if(not_in_use && not_in_def){
                        for(j=table_index;j<loc_table;j++){
                            if(strcmp(symlist[j].name,four_code_list_improve[i].para_1)==0){
                                break;
                            }
                        }
                        if(j!=loc_table){
                            strcpy(block_list[block_index].def[block_list[block_index].def_index],four_code_list_improve[i].para_1);
                            block_list[block_index].def_index++;
                        }
                    }
                break;
            }
            case CPRINTF:{
                if((four_code_list_improve[i].para_1[0]<='9'&&four_code_list_improve[i].para_1[0]>='0')||four_code_list_improve[i].para_1[0]=='-'){}
                else{
                    for(j=0;j<block_list[block_index].use_index;j++){
                        if(not_in_set(four_code_list_improve[i].para_1,block_list[block_index].use,block_list[block_index].use_index)){
                            not_in_use=1;
                        }
                        else{
                            not_in_use=0;
                        }
                    }
                    for(j=0;j<block_list[block_index].def_index;j++){
                        if(not_in_set(four_code_list_improve[i].para_1,block_list[block_index].def,block_list[block_index].def_index)){
                            not_in_def=1;
                        }
                        else{
                            not_in_def=0;
                        }
                    }
                     if(not_in_use && not_in_def){
                        for(j=table_index;j<loc_table;j++){
                            if(strcmp(symlist[j].name,four_code_list_improve[i].para_1)==0){
                                break;
                            }
                        }
                        if(j!=loc_table){
                            strcpy(block_list[block_index].use[block_list[block_index].use_index],four_code_list_improve[i].para_1);
                            block_list[block_index].use_index++;
                        }
                    }
                }
                break;
            }
            case CPRINTF_ST:{
                break;
            }
            case CPUSH_STACK:{
                break;
            }
            case CPULL_STACK:{
                break;
            }
            case CSAVE_ENV:{
                if(block_list[block_index].begin_block == i){
                    break;
                }
                block_list[block_index].end_block = i-1;
                block_index++;
                block_list[block_index].begin_block = i;
                break;
            }
            case CREV_ENV:{
                block_list[block_index].end_block = i;
                block_index++;
                block_list[block_index].begin_block = i+1;
                break;
            }
        }
    }
    block_list[block_index].begin_block=i;
    block_list[block_index].end_block=i;
    block_list[block_index].use_index=0;
    block_list[block_index].def_index=0;
    block_index++;
    flow_dag = i;
    findblocknext();
    findinout();
    findvarblock();
    findconflict();
    for(j=0;j<block_index;j++){
        debug_fprintf(fp_block,"blocknum:%d begin:%d end:%d use_index:%d def_index:%d\n",j,block_list[j].begin_block,block_list[j].end_block,block_list[j].use_index,block_list[j].def_index);
        int k;
        debug_fprintf(fp_block,"nextblock:%d %d\n",block_list[j].next_block[0],block_list[j].next_block[1]);
        debug_fprintf(fp_block,"use:\n");
        for(k=0;k<block_list[j].use_index;k++){
            debug_fprintf(fp_block,"%s ",block_list[j].use[k]);
        }
        debug_fprintf(fp_block,"\n");
        debug_fprintf(fp_block,"def:\n");
        for(k=0;k<block_list[j].def_index;k++){
            debug_fprintf(fp_block,"%s ",block_list[j].def[k]);
        }
        debug_fprintf(fp_block,"\n");
        debug_fprintf(fp_block,"in:\n");
        for(k=0;k<block_list[j].in_index;k++){
            debug_fprintf(fp_block,"%s ",block_list[j].in[k]);
        }
        debug_fprintf(fp_block,"\n");
        debug_fprintf(fp_block,"out:\n");
        for(k=0;k<block_list[j].out_index;k++){
            debug_fprintf(fp_block,"%s ",block_list[j].out[k]);
        }
        debug_fprintf(fp_block,"\n");
    }
    debug_fprintf(fp_block,"variable:\n");
    for(j=0;j<var_count;j++){
        debug_fprintf(fp_block,"%s ",var_block[j]);
    }
    debug_fprintf(fp_block,"\n");
    debug_fprintf(fp_block,"conflict graph:\n");
    for(m=0;m<var_count;m++){
        for(n=0;n<var_count;n++){
            debug_fprintf(fp_block,"%d ",var_graph[m][n]);
        }
        debug_fprintf(fp_block,"\n");
    }
    debug_fprintf(fp_block,"\n");
    return;
}

void findblocknext(){
    int i,j;
    for(i=0;i<block_index;i++){
        switch(four_code_list_improve[block_list[i].end_block].code){
            case CEQL:{}
            case CGEQ:{}
            case CGTR:{}
            case CLEQ:{}
            case CLSS:{}
            case CNEQ:{
                block_list[i].next_block[0] = i+1;
                for(j=0;j<block_index;j++){
                    if(strcmp(four_code_list_improve[block_list[i].end_block].para_3,four_code_list_improve[block_list[j].begin_block].para_1)==0){
                        block_list[i].next_block[1] = j;
                        break;
                    }
                }
                if(j==block_index){
                    printf("there may be something wrong in flow\n");
                }
                break;
            }
            case CJUMP:{
                for(j=0;j<block_index;j++){
                    if(strcmp(four_code_list_improve[block_list[i].end_block].para_1,four_code_list_improve[block_list[j].begin_block].para_1)==0){
                        block_list[i].next_block[0] = j;
                        break;
                    }
                }
                if(j==block_index){
                    printf("there may be something wrong in flow\n");
                }
                break;
            }
            case CREV_ENV:{
                block_list[i].next_block[0] = i+1;
                break;
            }
            case CRET:{}
            case CNRET:{
                block_list[i].next_block[0] = block_index-1;
                break;
            }
            default:{
                block_list[i].next_block[0] = i+1;
            }
        }
    }
    return;
}

void findinout(){
    int i,j,m;
    int change;
    while(1){
        change = 0;
        for(i=block_index-2;i>=0;i--){
            if(block_list[i].next_block[1]==0){
                for(j=0;j<block_list[block_list[i].next_block[0]].in_index;j++){
                    strcpy(block_list[i].out[j],block_list[block_list[i].next_block[0]].in[j]);
                }
                if(block_list[block_list[i].next_block[0]].in_index>block_list[i].out_index){
                    block_list[i].out_index = block_list[block_list[i].next_block[0]].in_index;
                    change = 1;
                }
            }
            else{
                //printf("%d %d\n",block_list[i].next_block[0],block_list[i].next_block[1]);
                //printf("%d %d\n",block_list[block_list[i].next_block[0]].in_index,block_list[block_list[i].next_block[1]].in_index);
                m = cal_out(block_list[block_list[i].next_block[0]].in,block_list[block_list[i].next_block[1]].in,
                           block_list[i].out,
                           block_list[block_list[i].next_block[0]].in_index,block_list[block_list[i].next_block[1]].in_index);
                if(m>block_list[i].out_index){
                    block_list[i].out_index=m;
                    change = 1;
                }
            }
            m = cal_in(block_list[i].use,block_list[i].out,block_list[i].def,block_list[i].in,
                       block_list[i].use_index,block_list[i].out_index,block_list[i].def_index);
            if(m>block_list[i].in_index){
                block_list[i].in_index = m;
                change = 1;
            }
        }
        if(change==0){
            break;
        }
    }
    return;
}

void findvarblock(){
    int i,j,k;
    for(i=0;i<block_index;i++){
        for(j=0;j<block_list[i].in_index;j++){
            for(k=0;k<var_count;k++){
                if(strcmp(block_list[i].in[j],var_block[k])==0){
                    break;
                }
            }
            if(k==var_count){
                strcpy(var_block[var_count],block_list[i].in[j]);
                var_count++;
            }
        }
    }
    return;
}

void findconflict(){
    int i,j,k;
    for(i=0;i<block_index;i++){
        char temp_var[Max_var][Max_ident+1];
        int temp_var_index=0;
        for(j=0;j<block_list[i].in_index;j++){
            for(k=0;k<temp_var_index;k++){
                if(strcmp(block_list[i].in[j],temp_var[k])==0){
                    break;
                }
            }
            if(k==temp_var_index){
                for(k=0;k<var_count;k++){
                    if(strcmp(var_block[k],block_list[i].in[j])==0){
                        break;
                    }
                }
                if(k!=var_count){
                    strcpy(temp_var[temp_var_index],block_list[i].in[j]);
                    temp_var_index++;
                }
            }
        }
        for(j=0;j<block_list[i].out_index;j++){
            for(k=0;k<temp_var_index;k++){
                if(strcmp(block_list[i].out[j],temp_var[k])==0){
                    break;
                }
            }
            if(k==temp_var_index){
                for(k=0;k<var_count;k++){
                    if(strcmp(var_block[k],block_list[i].out[j])==0){
                        break;
                    }
                }
                if(k!=var_count){
                    strcpy(temp_var[temp_var_index],block_list[i].out[j]);
                    temp_var_index++;
                }
            }
        }
        for(j=0;j<block_list[i].def_index;j++){
            for(k=0;k<temp_var_index;k++){
                if(strcmp(block_list[i].def[j],temp_var[k])==0){
                    break;
                }
            }
            if(k==temp_var_index){
                for(k=0;k<var_count;k++){
                    if(strcmp(var_block[k],block_list[i].def[j])==0){
                        break;
                    }
                }
                if(k!=var_count){
                    strcpy(temp_var[temp_var_index],block_list[i].def[j]);
                    temp_var_index++;
                }
            }
        }
        for(j=0;j<block_list[i].use_index;j++){
            for(k=0;k<temp_var_index;k++){
                if(strcmp(block_list[i].use[j],temp_var[k])==0){
                    break;
                }
            }
            if(k==temp_var_index){
                for(k=0;k<var_count;k++){
                    if(strcmp(var_block[k],block_list[i].use[j])==0){
                        break;
                    }
                }
                if(k!=var_count){
                    strcpy(temp_var[temp_var_index],block_list[i].use[j]);
                    temp_var_index++;
                }
            }
        }
        for(j=0;j<temp_var_index;j++){
            for(k=j+1;k<temp_var_index;k++){
                int m,n;
                for(m=0;m<var_count;m++){
                    if(strcmp(var_block[m],temp_var[j])==0){
                        break;
                    }
                }
                if(m==var_count){
                    printf("there may be something wrong in conflict graph\n");
                }
                for(n=0;n<var_count;n++){
                    if(strcmp(var_block[n],temp_var[k])==0){
                        break;
                    }
                }
                if(n==var_count){
                    printf("there may be something wrong in conflict graph\n");
                }
                var_graph[m][n]=1;
                var_graph[n][m]=1;
            }
        }
    }
    return;
}

void allotregister(){
    int i,j,m;
    int haveuse[Max_var]={0};
    int temp_allot[Max_var]={0};
    int change;
    int conflict_count;
    int add_order[Max_var]={0};
    int add_index=0;
    int temp_var_graph[Max_var][Max_var];
    int delete_node,delete_count;
    for(i=0;i<var_count;i++){
        for(j=0;j<var_count;j++){
            temp_var_graph[i][j]=var_graph[i][j];
        }
    }
    while(1){
        change=0;
        for(i=0;i<var_count;i++){
            if(haveuse[i]==1){
                continue;
            }
            conflict_count = 0;
            for(j=0;j<var_count;j++){
                if(temp_var_graph[i][j]==1){
                    conflict_count++;
                }
            }
            if(conflict_count<8){
                haveuse[i]=1;
                add_order[add_index]=i;
                add_index++;
                change=1;
                for(j=0;j<var_count;j++){
                    temp_var_graph[i][j]=0;
                    temp_var_graph[j][i]=0;
                }
            }
        }
        for(i=0;i<var_count;i++){
            if(haveuse[i]!=1){
                break;
            }
        }
        if(i==var_count){
            break;
        }
        if(change==0){
            delete_node=0;
            delete_count=0;
            int k;
            for(i=0;i<var_count;i++){
                if(haveuse[i]==1){
                    continue;
                }
                for(j=0;j<var_count;j++){
                    if(temp_var_graph[i][j]==1){
                        k++;
                    }
                }
                if(k>delete_count){
                    delete_count=k;
                    delete_node=i;
                }
            }
            haveuse[delete_node]=1;
            for(i=0;i<var_count;i++){
                temp_var_graph[i][delete_node]=0;
                temp_var_graph[delete_node][i]=0;
            }
        }
    }
    for(i=add_index-1;i>=0;i--){
        for(j=0;j<8;j++){
            for(m=add_index-1;m>i;m--){
                if(temp_allot[m]==j && var_graph[i][m]==1){
                    break;
                }
            }
            if(m==i){
                break;
            }
        }
        temp_allot[i] = j;
    }
    debug_fprintf(fp_block,"allotregisert:\n");
    for(i=0;i<add_index;i++){
        debug_fprintf(fp_block,"%s:%d\n",var_block[add_order[i]],temp_allot[i]);
    }
    debug_fprintf(fp_block,"\n");
    for(i=0;i<add_index;i++){
        for(j=table_index;j<loc_table;j++){
            if(strcmp(symlist[j].name,var_block[add_order[i]])==0){
                symlist[j].haves=1;
                symlist[j].snum = temp_allot[i];
            }
        }
    }
    return;
}

void flow(){
    int i;
    int loc;
    flow_init();
    find_block();
    allotregister();
    fprintf(fp_mips_flow,"%s:\n",four_code_list_improve[mips_4code_flow_loc].para_1);
    mips_4code_flow_loc++;
    for(i=0;i<block_list[0].in_index;i++){
        loc = table_search(block_list[0].in[i]);
        if(symlist[loc].haves==1 && symlist[loc].type!=0){
            fprintf(fp_mips_flow,"lw $s%d %d($sp)\n",symlist[loc].snum,symlist[loc].addr);
            strcpy(sregister[symlist[loc].snum],symlist[loc].name);
        }
    }
    for(;mips_4code_flow_loc<four_code_index_improve;mips_4code_flow_loc++){
        mips_flow();
    }
    for(i=0;i<8;i++){
        sregister[i][0]='\0';
    }
}
