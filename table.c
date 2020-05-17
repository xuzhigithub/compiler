#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "define.h"

void table_insert(){
    int i;
    for(i=loc_table-1;i>=table_index;i--){
        if(strcmp(tmp_name,symlist[i].name)==0){
            error(20);
            return;
        }
    }
    if(loc_table>=Max_table){
        error(48);
        return;
    }
    strcpy(symlist[loc_table].name,tmp_name);
    symlist[loc_table].type = tmp_type;
    symlist[loc_table].type_data = tmp_type_data;
    symlist[loc_table].global = tmp_global;
    symlist[loc_table].addr = tmp_addr;
    symlist[loc_table].after_dag=0;
    symlist[loc_table].aindex  = tmp_aindex;
    symlist[loc_table].para = tmp_para;
    symlist[loc_table].haves=0;
    symlist[loc_table].snum=0;
    for(i=0;i<tmp_para;i++){
        symlist[loc_table].para_table[i]=tmp_para_table[i];
    }
    if(tmp_global==0){
        if(tmp_type==1){
            symlist[loc_table].addr = global_loc;
            if(tmp_type_data==2 || tmp_type_data==3){
                global_loc-=4*tmp_aindex;
            }
            else{
                global_loc-=4;
            }
        }
        else if(tmp_type==2){
            local_loc=0;
        }
    }
    else{
        if(tmp_type==0){}
        else{
            symlist[loc_table].addr= local_loc;
            if(tmp_type_data==2 ||tmp_type_data==3){
                local_loc+=4*tmp_aindex;
            }
            else{
                local_loc+=4;
            }
        }
    }
    tmp_addr=0;
    tmp_aindex=0;
    tmp_para=0;
    loc_table++;
    /*for(j=0;j<loc_table;j++){
        debug_fprintf(fp_table,"name:%s type:%d type_data:%d global:%d aindex:%d addr:%d para:%d\n",symlist[j].name,symlist[j].type,symlist[j].type_data,symlist[j].global,symlist[j].aindex,symlist[j].addr,symlist[j].para);
        for(i=0;i<symlist[j].para;i++){
            debug_fprintf(fp_table,"%d ",symlist[j].para_table[i]);
        }
        if(i!=0){
            debug_fprintf(fp_table,"\n");
        }
    }*/
}

void table_delete(){
    int i,j;
    for(j=0;j<loc_table;j++){
        debug_fprintf(fp_table,"name:%s type:%d type_data:%d global:%d aindex:%d addr:%d after_dag:%d para:%d haves:%d snum:%d\n",
                      symlist[j].name,symlist[j].type,symlist[j].type_data,symlist[j].global,symlist[j].aindex,
                      symlist[j].addr,symlist[j].after_dag,symlist[j].para,symlist[j].haves,symlist[j].snum);
        for(i=0;i<symlist[j].para;i++){
            debug_fprintf(fp_table,"%d ",symlist[j].para_table[i]);
        }
        if(i!=0){
            debug_fprintf(fp_table,"\n");
        }
    }
    loc_table = table_index;
    table_index = 0;
    debug_fprintf(fp_table,"\n");
}

int table_search(char *dest){
    int i;
    for(i=loc_table-1;i>=0;i--){
        if(strcmp(symlist[i].name,dest)==0){
            return i;
        }
    }
    return -1;
}
