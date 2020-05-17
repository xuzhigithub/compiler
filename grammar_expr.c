#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "define.h"

void condition_if(){
    cal cal_tmp1;
    cal cal_tmp2;
    char label[Max_ident+1];
    strcpy(label,label_name);
    cal_tmp1 = expr();
    if(sym == EQL || sym == NEQ || sym == LSS || sym == LEQ || sym == GTR || sym == GEQ){
        int tmp = sym;
        sym = word();
        cal_tmp2 = expr();
        strcpy(four_code_para[0],cal_tmp1.name);
        strcpy(four_code_para[1],cal_tmp2.name);
        strcpy(four_code_para[2],label);
        if(tmp==EQL){
            insert_four_code(CNEQ);
        }
        else if(tmp==NEQ){
            insert_four_code(CEQL);
        }
        else if(tmp==LSS){
            insert_four_code(CGEQ);
        }
        else if(tmp==LEQ){
            insert_four_code(CGTR);
        }
        else if(tmp==GTR){
            insert_four_code(CLEQ);
        }
        else if(tmp==GEQ){
            insert_four_code(CLSS);
        }
    }
    else{
        pro_name();
        strcpy(four_code_para[0],val_name);
        four_code_para[1][0]='0';
        four_code_para[1][1]='\0';
        insert_four_code(CASSIGN);
        strcpy(four_code_para[0],cal_tmp1.name);
        strcpy(four_code_para[1],val_name);
        strcpy(four_code_para[2],label);
        insert_four_code(CEQL);
    }
    debug_fprintf(fp_grammar,"there is a condition\n");
    return;
}

void condition_while(){
    cal cal_tmp1;
    cal cal_tmp2;
    char label[Max_ident+1];
    strcpy(label,label_name);
    cal_tmp1 = expr();
    if(sym == EQL || sym == NEQ || sym == LSS || sym == LEQ || sym == GTR || sym == GEQ){
        int tmp = sym;
        sym = word();
        cal_tmp2 = expr();
        strcpy(four_code_para[0],cal_tmp1.name);
        strcpy(four_code_para[1],cal_tmp2.name);
        strcpy(four_code_para[2],label);
        if(tmp==EQL){
            insert_four_code(CEQL);
        }
        else if(tmp==NEQ){
            insert_four_code(CNEQ);
        }
        else if(tmp==LSS){
            insert_four_code(CLSS);
        }
        else if(tmp==LEQ){
            insert_four_code(CLEQ);
        }
        else if(tmp==GTR){
            insert_four_code(CGTR);
        }
        else if(tmp==GEQ){
            insert_four_code(CGEQ);
        }
    }
    else{
        strcpy(four_code_para[0],cal_tmp1.name);
        four_code_para[1][0]='0';
        four_code_para[1][1]='\0';
        strcpy(four_code_para[2],label);
        insert_four_code(CNEQ);
    }
    debug_fprintf(fp_grammar,"there is a condition\n");
    return;
}

cal expr(){
    cal return_val={0,0,0,{'\0'}};
    cal tmp_val;
    int sign=0;
    int flag=0;
    if(sym == PLUS || sym == MINUS){
        sign=(sym==PLUS)?1:-1;
        flag=1;
        sym = word();
    }
    return_val = term();
    if(sign==-1){
        pro_name();
        four_code_para[1][0]='0';
        four_code_para[1][1]='\0';
        strcpy(four_code_para[0],val_name);
        insert_four_code(CASSIGN);
        strcpy(four_code_para[1],val_name);
        strcpy(four_code_para[2],return_val.name);
        pro_name();
        strcpy(four_code_para[0],val_name);
        insert_four_code(CMINUS);
        strcpy(return_val.name,val_name);
    }
    if(flag){
        return_val.type=0;
        if(return_val.con==0){
            return_val.value = return_val.value*sign;
        }
    }
    while(sym == PLUS || sym == MINUS){
        int sign;
        sign=(sym==PLUS)?1:-1;
        return_val.type=0;
        sym = word();
        tmp_val = term();
        if(tmp_val.con==0 && return_val.con==0){
            return_val.value =(sign==1)? return_val.value+tmp_val.value:return_val.value-tmp_val.value;
        }
        else{
            return_val.con=1;
        }
        if(sign==1){
            pro_name();
            strcpy(four_code_para[0],val_name);
            strcpy(four_code_para[1],return_val.name);
            strcpy(four_code_para[2],tmp_val.name);
            insert_four_code(CADD);
            strcpy(return_val.name,val_name);
        }
        else{
            pro_name();
            strcpy(four_code_para[0],val_name);
            strcpy(four_code_para[1],return_val.name);
            strcpy(four_code_para[2],tmp_val.name);
            insert_four_code(CMINUS);
            strcpy(return_val.name,val_name);
        }
    }
    debug_fprintf(fp_grammar,"there is a expr\n");
    debug_fprintf(fp_expr,"expr: line:%d column:%d %d %d %d\n",line,column,return_val.type,return_val.con,return_val.value);
    return return_val;
}

cal term(){
    cal return_val={0,0,0,{'\0'}};
    cal tmp_val;
    return_val = factor();
    while(sym == TIME || sym == DIV){
        int sign=(sym==TIME)?0:1;
        return_val.type=0;
        sym = word();
        tmp_val = factor();
        if(return_val.con==0 && tmp_val.con==0){
            if(sym == TIME){
                return_val.value = return_val.value*tmp_val.value;
            }
            else{
                if(tmp_val.value==0){
                    error(45);
                    return_val.con=0;
                    return_val.type=0;
                    return_val.value=0;
                    return return_val;
                }
                return_val.value = return_val.value/tmp_val.value;
            }
        }
        else{
            return_val.con=1;
        }
        if(sign==0){
            pro_name();
            strcpy(four_code_para[0],val_name);
            strcpy(four_code_para[1],return_val.name);
            strcpy(four_code_para[2],tmp_val.name);
            insert_four_code(CTIME);
            strcpy(return_val.name,val_name);
        }
        else{
            pro_name();
            strcpy(four_code_para[0],val_name);
            strcpy(four_code_para[1],return_val.name);
            strcpy(four_code_para[2],tmp_val.name);
            insert_four_code(CDIV);
            strcpy(return_val.name,val_name);
        }
    }
    debug_fprintf(fp_grammar,"there is a term\n");
    debug_fprintf(fp_expr,"term: line:%d column:%d %d %d %d\n",line,column,return_val.type,return_val.con,return_val.value);
    return return_val;
}

cal factor(){
    int tmp_loc;
    cal tmp_cal;
    cal return_val={0,0,0,{'\0'}};
    if(sym == IDENT){
        tmp_loc=table_search(token);
        if(tmp_loc==-1){
            error(21);
        }
        return_val.con=1;
        sym = word();
        if(sym == LSBRACK){
            if(symlist[tmp_loc].type_data==2){
                return_val.type=0;
            }
            else if(symlist[tmp_loc].type_data==3){
                return_val.type=1;
                cflag = 1;
            }
            else{
                error(43);
            }
            sym = word();
            tmp_cal = expr();
            strcpy(four_code_para[1],symlist[tmp_loc].name);
            strcpy(four_code_para[2],tmp_cal.name);
            pro_name();
            cflag = 0;
            strcpy(four_code_para[0],val_name);
            strcpy(return_val.name,four_code_para[0]);
            insert_four_code(CARRVAL);
            if(tmp_cal.type!=0){
                error(24);
            }
            if(tmp_cal.con==0){
                if(tmp_cal.value>=symlist[tmp_loc].aindex || tmp_cal.value<0){
                    error(44);
                }
            }
            if(sym != RSBRACK){
                error(8);
                return return_val;
            }
            sym = word();
        }
        else if(sym == LBRACK){
            int i=0;
            char push_tmp[Max_para][Max_ident+1];
            int push_index=0;
            cal tmp_cal;
            if(symlist[tmp_loc].type!=2){
                error(32);
            }
            if(symlist[tmp_loc].type_data==4){
                error(29);
            }
            sym = word();
            if(sym != RBRACK){
                tmp_cal = expr();
                if(tmp_cal.type!=symlist[tmp_loc].para_table[i]){
                    error(36);
                }
                strcpy(push_tmp[push_index],tmp_cal.name);
                push_index++;
                i++;
                while(sym == COMMA){
                    sym = word();
                    tmp_cal = expr();
                    if(tmp_cal.type!=symlist[tmp_loc].para_table[i]){
                        error(36);
                    }
                    strcpy(push_tmp[push_index],tmp_cal.name);
                    push_index++;
                    i++;
                }
                if(sym != RBRACK){
                    error(6);
                    return return_val;
                }
                if(i!=symlist[tmp_loc].para){
                    error(35);
                }
            }
            else{
                if(symlist[tmp_loc].para!=0){
                    error(35);
                }
            }
            return_val.type = symlist[tmp_loc].type_data;
            for(i=0;i<push_index;i++){
                strcpy(four_code_para[0],push_tmp[i]);
                strcpy(four_code_para[1],symlist[tmp_loc].name);
                itoa(i,four_code_para[2],10);
                insert_four_code(CPUSH);
            }
            insert_four_code(CSAVE_ENV);
            strcpy(four_code_para[0],symlist[tmp_loc].name);
            insert_four_code(CPUSH_STACK);
            strcpy(four_code_para[0],symlist[tmp_loc].name);
            insert_four_code(CCALL);
            strcpy(four_code_para[0],symlist[tmp_loc].name);
            insert_four_code(CPULL_STACK);
            insert_four_code(CREV_ENV);
            if(symlist[tmp_loc].type_data==1){
                cflag=1;
            }
            pro_name();
            cflag=0;
            strcpy(four_code_para[0],val_name);
            strcpy(return_val.name,val_name);
            strcpy(four_code_para[1],symlist[tmp_loc].name);
            insert_four_code(CRETVAL);
            sym = word();
        }
        else{
            if(symlist[tmp_loc].type==0){
                return_val.con=0;
                return_val.type=symlist[tmp_loc].type_data;
                return_val.value=symlist[tmp_loc].addr;
                strcpy(return_val.name,symlist[tmp_loc].name);
                /*strcpy(four_code_para[0],val_name);
                strcpy(four_code_para[1],symlist[tmp_loc].name);
                insert_four_code(CASSIGN);*/
            }
            else if(symlist[tmp_loc].type==1){
                if(symlist[tmp_loc].type_data!=0 && symlist[tmp_loc].type_data!=1){
                    error(28);
                }
                return_val.con=1;
                return_val.type=symlist[tmp_loc].type_data;
                strcpy(return_val.name,symlist[tmp_loc].name);
                /*strcpy(four_code_para[0],val_name);
                strcpy(four_code_para[1],symlist[tmp_loc].name);
                insert_four_code(CASSIGN);*/
            }
            else{
                error(28);
            }
        }
    }
    else if(sym == INTEGER || sym == CHARACTER){
        return_val.con=0;
        if(sym==INTEGER){
            return_val.type=0;
            return_val.value=token_int;
            pro_name();
            strcpy(return_val.name,val_name);
            strcpy(four_code_para[0],val_name);
            itoa(token_int,four_code_para[1],10);
            insert_four_code(CASSIGN);
        }
        else{
            return_val.type=1;
            return_val.value=(int)token_char;
            cflag = 1;
            pro_name();
            cflag = 0;
            strcpy(return_val.name,val_name);
            strcpy(four_code_para[0],val_name);
            four_code_para[1][0]='\'';
            four_code_para[1][1]=token_char;
            four_code_para[1][2]='\'';
            four_code_para[1][3]='\0';
            insert_four_code(CASSIGN);
        }
        sym = word();
    }
    else if(sym == LBRACK){
        sym = word();
        return_val = expr();
        pro_name();
        strcpy(four_code_para[0],val_name);
        strcpy(four_code_para[1],return_val.name);
        strcpy(return_val.name,val_name);
        insert_four_code(CASSIGN);
        if(sym != RBRACK){
            error(6);
            return return_val;
        }
        sym = word();
    }
    else if(sym == PLUS || sym == MINUS){
        int sign = (sym==PLUS)?1:-1;
        sym=word();
        if(sym!=INTEGER){
            error(42);
        }
        if(token_int==0){
            error(40);
        }
        return_val.con=0;
        return_val.type=0;
        return_val.con=token_int*sign;
        pro_name();
        strcpy(four_code_para[0],val_name);
        strcpy(return_val.name,val_name);
        itoa(token_int*sign,four_code_para[1],10);
        insert_four_code(CASSIGN);
        sym = word();
    }
    else{
        return return_val;
    }
    debug_fprintf(fp_grammar,"there is a factor\n");
    debug_fprintf(fp_expr,"factor: line:%d column:%d %d %d %d\n",line,column,return_val.type,return_val.con,return_val.value);
    return return_val;
}
