#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "debug.h"

void com_statement(){
    constant_define();
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
        if(sym == LSBRACK || sym == COMMA || sym == SEMICOLON){
            infflag = 1;
            tmp_type=1;
            variable_define();
            infflag = 0;
        }
    }
    statements();
    debug_fprintf(fp_grammar,"there is a com_statement\n");
    return;
}

void statements(){
    while(sym == IFSY || sym == DOSY || sym == SWITCHSY || sym == LBRACE || sym == IDENT || sym == SCANFSY || sym == PRINTFSY || sym == RETURNSY || sym == SEMICOLON){
        statement();
    }
}

void statement(){
    char label[Max_ident+1];
    if(sym == IFSY){
        sym = word();
        if(sym != LBRACK){
            error(5);
            return;
        }
        sym = word();
        pro_label();
        strcpy(label,label_name);
        condition_if();
        if(sym != RBRACK){
            error(6);
            return;
        }
        sym = word();
        statement();
        strcpy(four_code_para[0],label);
        insert_four_code(CLABEL);
    }
    else if(sym == DOSY){
        char label[Max_ident+1];
        pro_label();
        strcpy(four_code_para[0],label_name);
        strcpy(label,label_name);
        insert_four_code(CLABEL);
        sym = word();
        statement();
        if(sym != WHILESY){
            error(15);
            return;
        }
        sym  = word();
        if(sym != LBRACK){
            error(5);
            return;
        }
        sym = word();
        strcpy(label_name,label);
        condition_while();
        if(sym != RBRACK){
            error(6);
            return;
        }
        sym = word();
    }
    else if(sym == SWITCHSY){
        cal tmp_cal;
        char labels[Max_ident+1];
        int con[Max_switch+1]={0};
        int index=0;
        int i;
        pro_label();
        strcpy(labels,label_name);
        sym = word();
        if(sym != LBRACK){
            error(5);
            return;
        }
        sym = word();
        tmp_cal = expr();
        if(sym != RBRACK){
            error(6);
            return;
        }
        sym = word();
        if(sym != LBRACE){
            error(8);
            return;
        }
        sym = word();
        do{
           if(sym != CASESY){
                error(16);
                return;
            }
            sym = word();
            char label[Max_ident+1];
            int sign=(sym==MINUS)?-1:1;
            pro_label();
            strcpy(label,label_name);
            if(sym == PLUS || sym == MINUS){
                sym = word();
                if(sym != INTEGER){
                    debug_fprintf(fp_error,"there should be a integer/n");
                }
                if(token_int==0){
                    error(40);
                }
            }
            if(sym != INTEGER && sym != CHARACTER){
                debug_fprintf(fp_grammar,"there should have a constant after case\n");
                return;
            }
            if(sym==INTEGER && tmp_cal.type!=0){
                error(41);
            }
            if(sym==CHARACTER && tmp_cal.type!=1){
                error(41);
            }
            if(sym==INTEGER){
                if(sign==-1){
                    four_code_para[1][0]='-';
                    four_code_para[1][1]='\0';
                    for(i=0;i<index;i++){
                        if(-token_int==con[i]){
                            error(47);
                        }
                    }
                    con[index]=-token_int;
                    index++;
                }
                else{
                    four_code_para[1][0]='\0';
                    for(i=0;i<index;i++){
                        if(token_int==con[i]){
                            error(47);
                        }
                    }
                    con[index]=token_int;
                    index++;
                }
                itoa(token_int,val_num,10);
                strcat(four_code_para[1],val_num);
                strcpy(four_code_para[0],tmp_cal.name);
                strcpy(four_code_para[2],label_name);
                insert_four_code(CNEQ);
            }
            else{
                for(i=0;i<index;i++){
                    if(con[i]==(int)token_char){
                        error(47);
                    }
                }
                con[index]=(int)token_char;
                index++;
                four_code_para[1][0]='\'';
                four_code_para[1][1]=token_char;
                four_code_para[1][2]='\'';
                four_code_para[1][3]='\0';
                strcpy(four_code_para[0],tmp_cal.name);
                strcpy(four_code_para[2],label_name);
                insert_four_code(CNEQ);
            }
            sym = word();
            if(sym != COLON){
                error(4);
                return;
            }
            sym = word();
            statement();
            strcpy(four_code_para[0],labels);
            insert_four_code(CJUMP);
            strcpy(four_code_para[0],label);
            insert_four_code(CLABEL);
        }
        while(sym == CASESY);
        if(sym != RBRACE){
            error(10);
            return;
        }
        strcpy(four_code_para[0],labels);
        insert_four_code(CLABEL);
        sym = word();
    }
    else if(sym == LBRACE){
        sym = word();
        statements();
        if(sym != RBRACE){
            error(10);
            return;
        }
        sym = word();
    }
    else if(sym == IDENT){
        int tmp_loc = table_search(token);
        cal tmp_cal;
        if(tmp_loc==-1){
            error(21);
        }
        sym = word();
        if(sym == LBRACK){
            int i=0;
            char push_tmp[Max_para][Max_ident+1];
            int push_index=0;
            if(symlist[tmp_loc].type!=2){
                error(32);
            }
            sym = word();
            if(sym != RBRACK){
                tmp_cal = expr();
                if(tmp_cal.type != symlist[tmp_loc].para_table[i]){
                    error(36);
                }
                strcpy(push_tmp[push_index],tmp_cal.name);
                push_index++;
                i++;
                while(sym == COMMA){
                    sym = word();
                    tmp_cal = expr();
                    if(tmp_cal.type != symlist[tmp_loc].para_table[i]){
                        error(36);
                    }
                    strcpy(push_tmp[push_index],tmp_cal.name);
                    push_index++;
                    i++;
                }
                if(i!=symlist[tmp_loc].para){
                    error(35);
                }
                if(sym != RBRACK){
                    error(6);
                    return;
                }
            }
            else{
                if(symlist[tmp_loc].para!=0){
                    error(35);
                }
            }
            sym = word();
            if(sym != SEMICOLON){
                error(3);
                return;
            }
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
            sym = word();
        }
        else if(sym == ASSIGN){
            if(symlist[tmp_loc].type!=1){
                error(34);
            }
            if(symlist[tmp_loc].type_data!=0 && symlist[tmp_loc].type_data!=1){
                error(34);
            }
            sym = word();
            tmp_cal = expr();
            if(tmp_cal.type==0 && symlist[tmp_loc].type_data==1){
                error(33);
            }
            if(sym != SEMICOLON){
                error(3);
                return;
            }
            strcpy(four_code_para[0],symlist[tmp_loc].name);
            strcpy(four_code_para[1],tmp_cal.name);
            insert_four_code(CASSIGN);
            sym = word();
        }
        else if(sym == LSBRACK){
            if((symlist[tmp_loc].type_data!=2 && symlist[tmp_loc].type_data!=3) || symlist[tmp_loc].type!=1){
                error(43);
            }
            sym = word();
            tmp_cal = expr();
            char tmp[Max_ident+1];
            strcpy(tmp,tmp_cal.name);
            if(tmp_cal.type!=0){
                error(24);
            }
            if(tmp_cal.con==0 && (tmp_cal.value>=symlist[tmp_loc].aindex || tmp_cal.value<0)){
                error(44);
            }
            if(sym != RSBRACK){
                error(8);
                return;
            }
            sym = word();
            if(sym != ASSIGN){
                error(12);
                return;
            }
            sym = word();
            tmp_cal = expr();
            strcpy(four_code_para[2],tmp_cal.name);
            strcpy(four_code_para[1],tmp);
            strcpy(four_code_para[0],symlist[tmp_loc].name);
            insert_four_code(CARRASN);
            if(tmp_cal.type==0 && symlist[tmp_loc].type_data==3){
                error(33);
            }
            if(sym != SEMICOLON){
                error(3);
                return;
            }
            sym = word();
        }
        else{
            error(5);
            return;
        }
    }
    else if(sym == SCANFSY){
        sym = word();
        if(sym != LBRACK){
            error(5);
            return;
        }
        do{
            sym = word();
            if(sym != IDENT){
                error(23);
                return;
            }
            int tmp_loc = table_search(token);
            if(tmp_loc==-1){
                error(35);
            }
            if(symlist[tmp_loc].type!=1 || (symlist[tmp_loc].type_data!=0&&symlist[tmp_loc].type_data!=1)){
                error(34);
            }
            strcpy(four_code_para[0],symlist[tmp_loc].name);
            insert_four_code(CSCANF);
            sym = word();
        }
        while(sym == COMMA);
        if(sym != RBRACK){
            error(6);
            return;
        }
        sym = word();
        if(sym != SEMICOLON){
            error(3);
            return;
        }
        sym = word();
    }
    else if(sym == PRINTFSY){
        cal tmp_cal;
        sym = word();
        if(sym != LBRACK){
            error(5);
            return;
        }
        sym = word();
        if(sym == STRING){
            insert_four_code(CPRINTF_ST);
            free(token_string);
            sym = word();
            if(sym == COMMA){
                sym = word();
                tmp_cal = expr();
                strcpy(four_code_para[0],tmp_cal.name);
                insert_four_code(CPRINTF);
            }
        }
        else {
            tmp_cal = expr();
            strcpy(four_code_para[0],tmp_cal.name);
            insert_four_code(CPRINTF);
        }
        if(sym != RBRACK){
            error(6);
            return;
        }
        sym = word();
        if(sym != SEMICOLON){
            error(3);
            return;
        }
        sym = word();
    }
    else if(sym == SEMICOLON){
        sym = word();
    }
    else if(sym == RETURNSY){
        haveret=1;
        cal tmp_cal;
        sym = word();
        if(sym == LBRACK){
            if(funflag==1){
                error(30);
            }
            sym = word();
            tmp_cal=expr();
            if(tmp_cal.type!=funflag-2){
                error(39);
            }
            if(sym != RBRACK){
                error(6);
                return;
            }
            strcpy(four_code_para[0],tmp_cal.name);
            insert_four_code(CRET);
            sym = word();
        }
        else{
            if(funflag==2 || funflag==3){
                error(31);
            }
            if(inmflag==1){
                four_code_para[0][0]='m';
                four_code_para[0][1]='a';
                four_code_para[0][2]='i';
                four_code_para[0][3]='n';
                four_code_para[0][4]='\0';
                insert_four_code(CPULL_STACK);
            }
            insert_four_code(CNRET);
        }
        if(sym != SEMICOLON){
            error(3);
            return;
        }
        sym = word();
    }
    else{
        return;
    }
    debug_fprintf(fp_grammar,"there is a statement\n");
    return;
}
