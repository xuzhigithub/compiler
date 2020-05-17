#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "debug.h"

void constant_define(){
    while(1){
        if (sym == CONSTSY){
            debug_fprintf(fp_grammar,"there is a constant define\n");
            sym = word();
            if (sym == INTSY){
                sym = word();
                if(constant_int_define()!=0){
                    return;//there is an error
                }
                while(1){
                    if(sym != COMMA){
                        break;
                    }
                    else{
                        sym = word();
                        constant_int_define();
                    }
                }
            }
            else if(sym == CHARSY){
                sym = word();
                if(constant_char_define()!=0){
                    return;//there is an error
                }
                while(1){
                    if(sym != COMMA){
                        break;
                    }
                    else{
                        sym = word();
                        constant_char_define();
                    }
                }
            }
            else{
                error(13);
                return;
            }
            if(sym != SEMICOLON){
                fprintf(fp_error,"line:%d column:%d there should have a ; after define\n",line,column);//there is an error
                return;
            }
            sym = word();
        }
        else{
            return;
        }
    }
}

void variable_define(){
    debug_fprintf(fp_grammar,"there is a variable_define\n");
    if((fflag ==1 || mflag == 1)&&infflag != 1){
        error(25);
        return;
    }
    if(sym == LSBRACK){
        sym = word();
        if(sym != INTEGER){
            error(24);
        }
        tmp_type_data = (tmp_type_data%2)+2;
        tmp_aindex = token_int;
        sym = word();
        if(sym != RSBRACK){
            error(8);
            return;//there is an error
        }
        table_insert();
        sym = word();
        while(1){
            if(sym == COMMA){
                sym = word();
                if(sym != IDENT){
                    error(23);
                    return;//there is an error
                }
                strcpy(tmp_name,token);
                sym = word();
                if(sym == LSBRACK){
                    tmp_type_data = (tmp_type_data%2)+2;
                    sym = word();
                    if(sym != INTEGER){
                        error(24);
                    }
                    tmp_aindex = token_int;
                    sym = word();
                    if(sym != RSBRACK){
                        error(8);
                        return;//there is an error
                    }
                    sym = word();
                }
                else{
                    tmp_type_data = (tmp_type_data%2);
                }
                table_insert();
            }
            else if(sym == SEMICOLON){
                sym = word();
                if(sym == INTSY || sym == CHARSY){
                    if(sym==INTSY){
                        tmp_type_data = 0;
                    }
                    else{
                        tmp_type_data = 1;
                    }
                    sym = word();
                    if(sym != IDENT){
                        error(23);
                        return;//there is an error
                    }
                    strcpy(tmp_name,token);
                    sym = word();
                    if(sym != LBRACK){
                        tmp_type=1;
                        variable_define();//变量声明
                        return;
                    }
                    else{
                        if(infflag == 1){
                            debug_fprintf(fp_grammar,"you can not define function in function\n");
                            return;
                        }
                        tmp_type=2;
                        sym = word();
                        fflag = 1;
                        haveret=0;
                        funflag=(tmp_type_data==0)?2:3;
                        function_define();//有返回值函数定义
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
                        return ;
                    }
                }
                else{
                    return;
                }
            }
            else if(sym == ASSIGN){
                error(19);
                return;
            }
            else{
                error(3);
                return;
            }
        }
    }
    else{
        table_insert();
        while(1){
            if(sym == COMMA){
                sym = word();
                if(sym != IDENT){
                    error(23);
                    return;//there is an error
                }
                strcpy(tmp_name,token);
                sym = word();
                if(sym == LSBRACK){
                    tmp_type_data = (tmp_type_data%2)+2;
                    sym = word();
                    if(sym != INTEGER){
                        error(24);
                    }
                    tmp_aindex=token_int;
                    sym = word();
                    if(sym != RSBRACK){
                        error(8);
                        return;//there is an error
                    }
                    sym = word();
                }
                else{
                    tmp_type_data = (tmp_type_data%2);
                }
                table_insert();
            }
            else if(sym == SEMICOLON){
                sym = word();
                if(sym == INTSY || sym == CHARSY){
                    if(sym==INTSY){
                        tmp_type_data=0;
                    }
                    else{
                        tmp_type_data=1;
                    }
                    sym = word();
                    if(sym != IDENT){
                        error(23);
                        return;//there is an error
                    }
                    strcpy(tmp_name,token);
                    sym = word();
                    if(sym != LBRACK){
                        tmp_type=1;
                        variable_define();//变量声明
                        return;
                    }
                    else{
                        if(infflag == 1){
                            debug_fprintf(fp_grammar,"you can not define function in function");
                            return;
                        }
                        tmp_type=2;
                        sym = word();
                        fflag = 1;
                        haveret=0;
                        funflag=(tmp_type_data==0)?2:3;
                        function_define();//有返回值函数定义
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
                        return ;
                    }
                }
                else{
                    return;
                }
            }
            else{
                error(3);
                return;
            }
        }
    }
}

void function_define(){
    debug_fprintf(fp_grammar,"there is a function_define\n");
    tmp_para = 0;
    int tmp_loc=loc_table;
    strcpy(four_code_para[0],tmp_name);
    four_code_para[1][0]='_';
    four_code_para[1][1]='F';
    four_code_para[1][2]='\0';
    strcat(four_code_para[0],four_code_para[1]);
    insert_four_code(CLABEL);
    tmp_global = 0;
    table_insert();
    tmp_global = 1;
    table_index=loc_table;
    int i=0;
    if(mflag == 1){
        debug_fprintf(fp_grammar,"there have defined main function,you can not define function\n");
        return;//there is an error
    }
    if(sym != RBRACK){
        if(sym != INTSY && sym != CHARSY){
            error(13);
            return;//there is an error
        }
        if(sym == INTSY){
            tmp_type=1;
            tmp_type_data=0;
            symlist[tmp_loc].para_table[i++]=0;
        }
        else{
            tmp_type=1;
            tmp_type_data=1;
            symlist[tmp_loc].para_table[i++]=1;
        }
        sym = word();
        if(sym != IDENT){
            error(23);
            return;//there is an error
        }
        strcpy(tmp_name,token);
        symlist[tmp_loc].para++;
        table_insert();
        sym = word();
        while(1){
            if(sym != COMMA){
                break;
            }
            sym = word();
            if(sym != INTSY && sym != CHARSY){
                error(13);
                return;//there is an error
            }
            if(sym == INTSY){
                tmp_type=1;
                tmp_type_data=0;
                symlist[tmp_loc].para_table[i++]=0;
            }
            else{
                tmp_type=1;
                tmp_type_data=1;
                symlist[tmp_loc].para_table[i++]=1;
            }
            sym = word();
            if(sym != IDENT){
                error(23);
                return;//there is an error
            }
            strcpy(tmp_name,token);
            symlist[tmp_loc].para++;
            table_insert();
            sym = word();
        }
        if(sym != RBRACK){
            error(6);
            return;//there is an error
        }
    }
    sym = word();
    if(sym != LBRACE){
        error(9);
        return;//there is an error
    }
    sym = word();
    com_statement();
    insert_four_code(CNRET);
    if(sym != RBRACE){
        error(10);
        return;//there is an error
    }
    symlist[tmp_loc].addr = local_loc;
    sym = word();
    return;
}

void main_define(){
    int tmp_loc = loc_table;
    debug_fprintf(fp_grammar,"there is a main_define\n");
    if(mflag == 1){
        debug_fprintf(fp_grammar,"there have defined main function, you can not define the second one\n");
        return;//there is an error
    }
    tmp_para=0;
    tmp_global = 0;
    table_insert();
    tmp_global = 1;
    four_code_para[0][0]='m';
    four_code_para[0][1]='a';
    four_code_para[0][2]='i';
    four_code_para[0][3]='n';
    four_code_para[0][4]='\0';
    table_index = loc_table;
    insert_four_code(CLABEL);
    strcpy(four_code_para[0],symlist[tmp_loc].name);
    insert_four_code(CPUSH_STACK);
    if(sym != LBRACK){
        error(5);
        return;//there is an error
    }
    sym = word();
    if(sym != RBRACK){
        error(6);
        return;//there is an error
    }
    sym = word();
    if(sym != LBRACE){
        error(9);
        return;//there is an error
    }
    sym = word();
    com_statement();
    if(sym != RBRACE){
        error(10);
        return;//there is an error
    }
    sym = word();
    symlist[tmp_loc].addr = local_loc;
    strcpy(four_code_para[0],symlist[tmp_loc].name);
    return;
}

int constant_int_define(){
    int sign=1;
    if(sym != IDENT){
        error(23);
        return -1;
    }
    strcpy(tmp_name,token);
    tmp_type = 0;
    tmp_type_data = 0;
    sym = word();
    if(sym != ASSIGN){
        error(18);
        return -1;
    }
    sym = word();
    if(sym == PLUS || sym == MINUS){
        if(sym == MINUS){
            sign = -1;
        }
        sym = word();
        if(sym == INTEGER && token_int == 0){
            error(40);
        }
    }
    if(sym != INTEGER){
        error(22);
        return -1;
    }
    tmp_addr = sign*token_int;
    tmp_aindex = -1;
    tmp_para = -1;
    table_insert();
    sym = word();
    return 0;
}

int constant_char_define(){
    if(sym != IDENT){
        error(23);
        return -1;
    }
    strcpy(tmp_name,token);
    tmp_type = 0;
    tmp_type_data = 1;
    sym = word();
    if(sym != ASSIGN){
        error(18);
        return -1;
    }
    sym = word();
    if(sym != CHARACTER){
        error(22);
        return -1;
    }
    tmp_addr = (int)token_char;
    tmp_aindex = -1;
    tmp_para = -1;
    table_insert();
    sym = word();
    return 0;
}
