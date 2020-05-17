#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "define.h"

void program(){
    tmp_global = 0;
    constant_define();//常量声明
    while(1){
        if(sym == VOIDSY){
            sym = word();
            if(sym == MAINSY){
                strcpy(tmp_name,token);
                tmp_type_data=4;
                tmp_type=2;
                sym = word();
                vflag = 1;
                fflag = 1;
                infflag = 1;
                inmflag=1;
                main_define();//主函数分析
                infflag = 0;
                mflag = 1;
                if(haveret!=1){
                    four_code_para[0][0]='m';
                    four_code_para[0][1]='a';
                    four_code_para[0][2]='i';
                    four_code_para[0][3]='n';
                    four_code_para[0][4]='\0';
                    insert_four_code(CPULL_STACK);
                    insert_four_code(CNRET);
                }
                for(;mips_4code_loc<four_code_index;mips_4code_loc++){
                    mips();
                }
                int i,j;
                for(i=table_index;i<loc_table;i++){
                    if(symlist[i].name[0]=='T'){
                        loc_table = i;
                        break;
                    }
                }
                for(j=i;j>table_index;j--){
                    if(symlist[j].type==1){
                        local_loc = symlist[j].addr;
                        break;
                    }
                }
                if(j==table_index){
                    local_loc=0;
                }
                find_tmp_store();
                dag_improve();
                symlist[table_index-1].after_dag=local_loc;
                for(;mips_4code_dag_loc<four_code_index_improve;mips_4code_dag_loc++){
                    mips_dag();
                }
                flow();
                table_delete();
                inmflag=0;
            }
            else if(sym == IDENT){
                strcpy(tmp_name,token);
                tmp_type_data = 4;
                tmp_type = 2;
                sym = word();
                if(sym != LBRACK){
                    fprintf(fp_error,"line:%d column:%d there should have a (\n",line,column);
                    debug_printf("line:%d column:%d there should have a (\n",line,column);
                }
                else{
                    sym = word();
                }
                vflag = 1;
                fflag = 1;
                funflag=1;
                function_define();//函数定义
                funflag=0;
                if(haveret!=1){
                    insert_four_code(CNRET);
                }
                for(;mips_4code_loc<four_code_index;mips_4code_loc++){
                    mips();
                }
                int i,j;
                for(i=table_index;i<loc_table;i++){
                    if(symlist[i].name[0]=='T'){
                        loc_table = i;
                        break;
                    }
                }
                for(j=i;j>table_index;j--){
                    if(symlist[j].type==1){
                        local_loc = symlist[j].addr;
                        break;
                    }
                }
                if(j==table_index){
                    local_loc=0;
                }
                find_tmp_store();
                dag_improve();
                symlist[table_index-1].after_dag=local_loc;
                for(;mips_4code_dag_loc<four_code_index_improve;mips_4code_dag_loc++){
                    mips_dag();
                }
                flow();
                table_delete();
                continue;
            }
        }
        else if(sym == INTSY || sym == CHARSY){
            if(sym==INTSY){
                tmp_type_data=0;
            }
            else{
                tmp_type_data=1;
            }
            sym = word();
            if(sym != IDENT){
                error(23);
            }
            strcpy(tmp_name,token);
            sym = word();
            if(sym != LBRACK){
                tmp_type=1;
                vflag = 1;
                variable_define();//变量声明
                continue;
            }
            else{
                tmp_type=2;
                vflag = 1;
                fflag = 1;
                sym = word();
                haveret=0;
                funflag=(tmp_type_data==0)?2:3;
                function_define();//函数定义
                funflag=0;
                if(haveret!=1){
                    error(31);
                }
                haveret=0;
                for(;mips_4code_loc<four_code_index;mips_4code_loc++){
                    mips();
                }
                int i,j;
                for(i=table_index;i<loc_table;i++){
                    if(symlist[i].name[0]=='T'){
                        loc_table = i;
                        break;
                    }
                }
                for(j=i;j>table_index;j--){
                    if(symlist[j].type==1){
                        local_loc = symlist[j].addr;
                        break;
                    }
                }
                if(j==table_index){
                    local_loc=0;
                }
                find_tmp_store();
                dag_improve();
                symlist[table_index-1].after_dag=local_loc;
                for(;mips_4code_dag_loc<four_code_index_improve;mips_4code_dag_loc++){
                    mips_dag();
                }
                flow();
                table_delete();
                continue;
            }
        }
        else if(sym == -1){
            break;
        }
        else{
            sym = word();
            //error(38);
        }
    }
    if(mflag == 0){
        error(17);
    }
    debug_fprintf(fp_grammar,"there is a program\n");
    return;
}
