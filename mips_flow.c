#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "debug.h"

void mips_flow(){
    int i,j,k;
    int loc;
    int loc_1=-1;
    int loc_2=-1;
    int loc_3=-1;
    int var_1;
    int var_2;
    int var_3;
    char tmp_name1[Max_ident+1];
    char tmp_name2[Max_ident+1];
    char tmp_name3[Max_ident+1];
    strcpy(tmp_name1,four_code_list_improve[mips_4code_flow_loc].para_1);
    strcpy(tmp_name2,four_code_list_improve[mips_4code_flow_loc].para_2);
    strcpy(tmp_name3,four_code_list_improve[mips_4code_flow_loc].para_3);
    for(i=0;i<block_index;i++){
        if(mips_4code_flow_loc == block_list[i].end_block){
            switch(four_code_list_improve[mips_4code_flow_loc].code){
                case CEQL:{}
                case CGEQ:{}
                case CGTR:{}
                case CLEQ:{}
                case CLSS:{}
                case CNEQ:{}
                case CJUMP:{}
                case CRET:{}
                case CNRET:{}
                case CSAVE_ENV:{
                    for(j=0;j<block_list[i].out_index;j++){
                        for(k=0;k<10;k++){
                            if(strcmp(block_list[i].out[j],tregister[k])==0){
                                loc = table_search(tregister[k]);
                                if(loc==-1 || symlist[loc].global==0){
                                    printf("there may be something wrong in write back\n");
                                }
                                fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",k,symlist[loc].addr);
                            }
                        }
                    }
                    for(k=0;k<10;k++){
                        loc = table_search(tregister[k]);
                        if(symlist[loc].global==0 && loc!=-1 && symlist[loc].type!=0){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",k,symlist[loc].addr);
                        }
                    }
                    break;
                }
            }
        }
    }
    switch(four_code_list_improve[mips_4code_flow_loc].code){
        case CPASS:{
            fprintf(fp_mips_flow,"nop\n");
            break;
        }
        case CADD:{}
        case CMINUS:{}
        case CTIME:{}
        case CDIV:{
            loc_1 = table_search(tmp_name1);
            loc_2 = table_search(tmp_name2);
            loc_3 = table_search(tmp_name3);
            var_2=-1;
            var_3=-1;
            for(i=0;i<8;i++){
                if(strcmp(sregister[i],tmp_name2)==0){
                    var_2=i;
                }
                if(strcmp(sregister[i],tmp_name3)==0){
                    var_3=i;
                }
            }
            for(i=0;i<10;i++){
                if(strcmp(tregister[i],tmp_name2)==0){
                    var_2=-i-1;
                }
                if(strcmp(tregister[i],tmp_name3)==0){
                    var_3=-i-1;
                }
            }
            if(var_2==-1){
                if(loc_2==-1){
                    for(i=0;i<10;i++){
                        if(strcmp(tmp_name2,tregister[i])==0){
                            break;
                        }
                    }
                    if(i==10){
                        loc = table_search(tregister[tregister_index]);
                        if(loc != -1 && symlist[loc].type!=0){
                            if(symlist[loc].global==0){
                                fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                            }
                            else{
                                fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                            }
                        }
                        fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,atoi(tmp_name2));
                        strcpy(tregister[tregister_index],tmp_name2);
                        tregister_index = (tregister_index+1)%10;
                    }
                }
                else if(symlist[loc_2].haves==1){
                    strcpy(sregister[symlist[loc_2].snum],tmp_name2);
                }
                else{
                    for(i=0;i<10;i++){
                        if(strcmp(tmp_name2,tregister[i])==0){
                            break;
                        }
                    }
                    if(i==10){
                        loc = table_search(tregister[tregister_index]);
                        if(loc != -1 && symlist[loc].type!=0){
                            if(symlist[loc].global==0){
                                fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                            }
                            else{
                                fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                            }
                        }
                        if(symlist[loc_2].type==0){
                            fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,symlist[loc_2].addr);
                            strcpy(tregister[tregister_index],tmp_name2);
                            tregister_index = (tregister_index+1)%10;
                        }
                        else{
                            if(symlist[loc_2].global==0){
                                fprintf(fp_mips_flow,"lw $t%d %d($gp)\n",tregister_index,symlist[loc_2].addr);
                                strcpy(tregister[tregister_index],tmp_name2);
                                tregister_index = (tregister_index+1)%10;
                            }
                            else{
                                fprintf(fp_mips_flow,"lw $t%d %d($sp)\n",tregister_index,symlist[loc_2].addr);
                                strcpy(tregister[tregister_index],tmp_name2);
                                tregister_index = (tregister_index+1)%10;
                            }
                        }
                    }
                }
            }
            if(var_3==-1){
                if(loc_3==-1){}
                else if(symlist[loc_3].haves==1){
                    strcpy(sregister[symlist[loc_3].snum],tmp_name3);
                }
                else{
                    for(i=0;i<10;i++){
                        if(strcmp(tmp_name3,tregister[i])==0){
                            break;
                        }
                    }
                    if(i==10){
                        loc = table_search(tregister[tregister_index]);
                        if(loc != -1 && symlist[loc].type!=0){
                            if(symlist[loc].global==0){
                                fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                            }
                            else{
                                fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                            }
                        }
                        if(symlist[loc_3].type==0){
                            fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,symlist[loc_3].addr);
                            strcpy(tregister[tregister_index],tmp_name3);
                            tregister_index = (tregister_index+1)%10;
                        }
                        else{
                            if(symlist[loc_3].global==0){
                                fprintf(fp_mips_flow,"lw $t%d %d($gp)\n",tregister_index,symlist[loc_3].addr);
                                strcpy(tregister[tregister_index],tmp_name3);
                                tregister_index = (tregister_index+1)%10;
                            }
                            else{
                                fprintf(fp_mips_flow,"lw $t%d %d($sp)\n",tregister_index,symlist[loc_3].addr);
                                strcpy(tregister[tregister_index],tmp_name3);
                                tregister_index = (tregister_index+1)%10;
                            }
                        }
                    }
                }
            }
            for(i=0;i<8;i++){
                if(strcmp(sregister[i],tmp_name2)==0){
                    var_2=i;
                }
                if(strcmp(sregister[i],tmp_name3)==0){
                    var_3=i;
                }
            }
            for(i=0;i<10;i++){
                if(strcmp(tregister[i],tmp_name2)==0){
                    var_2=-i-1;
                }
                if(strcmp(tregister[i],tmp_name3)==0){
                    var_3=-i-1;
                }
            }
            if(symlist[loc_1].haves==1){
                strcpy(sregister[symlist[loc_1].snum],tmp_name1);
                if(var_2>=0 && var_3>=0){
                    switch(four_code_list_improve[mips_4code_flow_loc].code){
                        case CADD:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"addi $s%d $s%d %d\n",symlist[loc_1].snum,var_2,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"add $s%d $s%d $s%d\n",symlist[loc_1].snum,var_2,var_3);
                            }
                            break;
                        }
                        case CMINUS:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"subi $s%d $s%d %d\n",symlist[loc_1].snum,var_2,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"sub $s%d $s%d $s%d\n",symlist[loc_1].snum,var_2,var_3);
                            }
                            break;
                        }
                        case CTIME:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"mul $s%d $s%d %d\n",symlist[loc_1].snum,var_2,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"mul $s%d $s%d $s%d\n",symlist[loc_1].snum,var_2,var_3);
                            }
                            break;
                        }
                        case CDIV:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"div $s%d $s%d %d\n",symlist[loc_1].snum,var_2,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"div $s%d $s%d $s%d\n",symlist[loc_1].snum,var_2,var_3);
                            }
                            break;
                        }
                    }
                }
                else if(var_2>=0 && var_3<0){
                    switch(four_code_list_improve[mips_4code_flow_loc].code){
                        case CADD:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"addi $s%d $s%d %d\n",symlist[loc_1].snum,var_2,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"add $s%d $s%d $t%d\n",symlist[loc_1].snum,var_2,-var_3-1);
                            }
                            break;
                        }
                        case CMINUS:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"subi $s%d $s%d %d\n",symlist[loc_1].snum,var_2,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"sub $s%d $s%d $t%d\n",symlist[loc_1].snum,var_2,-var_3-1);
                            }
                            break;
                        }
                        case CTIME:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"mul $s%d $s%d %d\n",symlist[loc_1].snum,var_2,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"mul $s%d $s%d $t%d\n",symlist[loc_1].snum,var_2,-var_3-1);
                            }
                            break;
                        }
                        case CDIV:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"div $s%d $s%d %d\n",symlist[loc_1].snum,var_2,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"div $s%d $s%d $t%d\n",symlist[loc_1].snum,var_2,-var_3-1);
                            }
                            break;
                        }
                    }
                }
                else if(var_2<0 && var_3>=0){
                    switch(four_code_list_improve[mips_4code_flow_loc].code){
                        case CADD:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"addi $s%d $t%d %d\n",symlist[loc_1].snum,-var_2-1,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"add $s%d $t%d $s%d\n",symlist[loc_1].snum,-var_2-1,var_3);
                            }
                            break;
                        }
                        case CMINUS:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"subi $s%d $t%d %d\n",symlist[loc_1].snum,-var_2-1,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"sub $s%d $t%d $s%d\n",symlist[loc_1].snum,-var_2-1,var_3);
                            }
                            break;
                        }
                        case CTIME:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"mul $s%d $t%d %d\n",symlist[loc_1].snum,-var_2-1,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"mul $s%d $t%d $s%d\n",symlist[loc_1].snum,-var_2-1,var_3);
                            }
                            break;
                        }
                        case CDIV:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"div $s%d $t%d %d\n",symlist[loc_1].snum,-var_2-1,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"div $s%d $t%d $s%d\n",symlist[loc_1].snum,-var_2-1,var_3);
                            }
                            break;
                        }
                    }
                }
                else if(var_2<0 && var_3<0){
                    switch(four_code_list_improve[mips_4code_flow_loc].code){
                        case CADD:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"addi $s%d $t%d %d\n",symlist[loc_1].snum,-var_2-1,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"add $s%d $t%d $t%d\n",symlist[loc_1].snum,-var_2-1,-var_3-1);
                            }
                            break;
                        }
                        case CMINUS:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"subi $s%d $t%d %d\n",symlist[loc_1].snum,-var_2-1,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"sub $s%d $t%d $t%d\n",symlist[loc_1].snum,-var_2-1,-var_3-1);
                            }
                            break;
                        }
                        case CTIME:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"mul $s%d $t%d %d\n",symlist[loc_1].snum,-var_2-1,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"mul $s%d $t%d $t%d\n",symlist[loc_1].snum,-var_2-1,-var_3-1);
                            }
                            break;
                        }
                        case CDIV:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"div $s%d $t%d %d\n",symlist[loc_1].snum,-var_2-1,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"div $s%d $t%d $t%d\n",symlist[loc_1].snum,-var_2-1,-var_3-1);
                            }
                            break;
                        }
                    }
                }
            }
            else{
                for(i=0;i<10;i++){
                    if(strcmp(tregister[i],tmp_name1)==0){
                        break;
                    }
                }
                if(i==10){
                    loc = table_search(tregister[tregister_index]);
                    if(loc != -1 && symlist[loc].type!=0){
                        if(symlist[loc].global==0){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                        }
                        else{
                            fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                        }
                    }
                    strcpy(tregister[tregister_index],tmp_name1);
                    tregister_index = (tregister_index+1)%10;
                }
                for(i=0;i<10;i++){
                    if(strcmp(tregister[i],tmp_name1)==0){
                        var_1 = i;
                    }
                }
                if(var_2>=0 && var_3>=0){
                    switch(four_code_list_improve[mips_4code_flow_loc].code){
                        case CADD:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"addi $t%d $s%d %d\n",var_1,var_2,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"add $t%d $s%d $s%d\n",var_1,var_2,var_3);
                            }
                            break;
                        }
                        case CMINUS:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"subi $t%d $s%d %d\n",var_1,var_2,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"sub $t%d $s%d $s%d\n",var_1,var_2,var_3);
                            }
                            break;
                        }
                        case CTIME:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"mul $t%d $s%d %d\n",var_1,var_2,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"mul $t%d $s%d $s%d\n",var_1,var_2,var_3);
                            }
                            break;
                        }
                        case CDIV:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"div $t%d $s%d %d\n",var_1,var_2,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"div $t%d $s%d $s%d\n",var_1,var_2,var_3);
                            }
                            break;
                        }
                    }
                }
                else if(var_2>=0 && var_3<0){
                    switch(four_code_list_improve[mips_4code_flow_loc].code){
                        case CADD:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"addi $t%d $s%d %d\n",var_1,var_2,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"add $t%d $s%d $t%d\n",var_1,var_2,-var_3-1);
                            }
                            break;
                        }
                        case CMINUS:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"subi $t%d $s%d %d\n",var_1,var_2,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"sub $t%d $s%d $t%d\n",var_1,var_2,-var_3-1);
                            }
                            break;
                        }
                        case CTIME:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"mul $t%d $s%d %d\n",var_1,var_2,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"mul $t%d $s%d $t%d\n",var_1,var_2,-var_3-1);
                            }
                            break;
                        }
                        case CDIV:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"div $t%d $s%d %d\n",var_1,var_2,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"div $t%d $s%d $t%d\n",var_1,var_2,-var_3-1);
                            }
                            break;
                        }
                    }
                }
                else if(var_2<0 && var_3>=0){
                    switch(four_code_list_improve[mips_4code_flow_loc].code){
                        case CADD:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"addi $t%d $t%d %d\n",var_1,-var_2-1,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"add $t%d $t%d $s%d\n",var_1,-var_2-1,var_3);
                            }
                            break;
                        }
                        case CMINUS:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"subi $t%d $t%d %d\n",var_1,-var_2-1,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"sub $t%d $t%d $s%d\n",var_1,-var_2-1,var_3);
                            }
                            break;
                        }
                        case CTIME:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"mul $t%d $t%d %d\n",var_1,-var_2-1,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"mul $t%d $t%d $s%d\n",var_1,-var_2-1,var_3);
                            }
                            break;
                        }
                        case CDIV:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"div $t%d $t%d %d\n",var_1,-var_2-1,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"div $t%d $t%d $s%d\n",var_1,-var_2-1,var_3);
                            }
                            break;
                        }
                    }
                }
                else if(var_2<0 && var_3<0){
                    switch(four_code_list_improve[mips_4code_flow_loc].code){
                        case CADD:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"addi $t%d $t%d %d\n",var_1,-var_2-1,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"add $t%d $t%d $t%d\n",var_1,-var_2-1,-var_3-1);
                            }
                            break;
                        }
                        case CMINUS:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"subi $t%d $t%d %d\n",var_1,-var_2-1,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"sub $t%d $t%d $t%d\n",var_1,-var_2-1,-var_3-1);
                            }
                            break;
                        }
                        case CTIME:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"mul $t%d $t%d %d\n",var_1,-var_2-1,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"mul $t%d $t%d $t%d\n",var_1,-var_2-1,-var_3-1);
                            }
                            break;
                        }
                        case CDIV:{
                            if(loc_3==-1){
                                fprintf(fp_mips_flow,"div $t%d $t%d %d\n",var_1,-var_2-1,atoi(tmp_name3));
                            }
                            else{
                                fprintf(fp_mips_flow,"div $t%d $t%d $t%d\n",var_1,-var_2-1,-var_3-1);
                            }
                            break;
                        }
                    }
                }
            }
            break;
        }
        case CARRVAL:{
            loc_1 = table_search(tmp_name1);
            loc_2 = table_search(tmp_name2);
            loc_3 = table_search(tmp_name3);
            fprintf(fp_mips_flow,"li $a3 %d\n",symlist[loc_2].addr);
            if(loc_3==-1){
                for(i=0;i<10;i++){
                    if(strcmp(tmp_name3,tregister[i])==0){
                        break;
                    }
                }
                if(i==10){
                    loc = table_search(tregister[tregister_index]);
                    if(loc != -1 && symlist[loc].type!=0){
                        if(symlist[loc].global==0){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                        }
                        else{
                            fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                        }
                    }
                    fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,atoi(tmp_name3));
                    strcpy(tregister[tregister_index],tmp_name3);
                    tregister_index = (tregister_index+1)%10;
                }
            }
            else if(symlist[loc_3].haves==1){
                strcpy(sregister[symlist[loc_3].snum],tmp_name3);
            }
            else{
                for(i=0;i<10;i++){
                    if(strcmp(tmp_name3,tregister[i])==0){
                        break;
                    }
                }
                if(i==10){
                    loc = table_search(tregister[tregister_index]);
                    if(loc != -1 && symlist[loc].type!=0){
                        if(symlist[loc].global==0){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                        }
                        else{
                            fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                        }
                    }
                    if(symlist[loc_3].type==0){
                        fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,symlist[loc_3].addr);
                        strcpy(tregister[tregister_index],tmp_name3);
                        tregister_index = (tregister_index+1)%10;
                    }
                    else{
                        if(symlist[loc_3].global==0){
                            fprintf(fp_mips_flow,"lw $t%d %d($gp)\n",tregister_index,symlist[loc_3].addr);
                            strcpy(tregister[tregister_index],tmp_name3);
                            tregister_index = (tregister_index+1)%10;
                        }
                        else{
                            fprintf(fp_mips_flow,"lw $t%d %d($sp)\n",tregister_index,symlist[loc_3].addr);
                            strcpy(tregister[tregister_index],tmp_name3);
                            tregister_index = (tregister_index+1)%10;
                        }
                    }
                }
            }
            if(symlist[loc_1].haves==1){
                strcpy(sregister[symlist[loc_1].snum],tmp_name1);
                for(i=0;i<8;i++){
                    if(strcmp(sregister[i],tmp_name3)==0){
                        var_3 = i;
                    }
                }
                for(i=0;i<10;i++){
                    if(strcmp(tregister[i],tmp_name3)==0){
                        var_3 = -i-1;
                    }
                }
                if(var_3>=0){
                    fprintf(fp_mips_flow,"sll $a2 $s%d 2\n",var_3);
                    if(symlist[loc_2].global==0){
                        fprintf(fp_mips_flow,"sub $a2 $a3 $a2\n");
                        fprintf(fp_mips_flow,"add $a2 $a2 $gp\n");
                        fprintf(fp_mips_flow,"lw $s%d ($a2)\n",symlist[loc_1].snum);
                    }
                    else{
                        fprintf(fp_mips_flow,"add $a2 $a3 $a2\n");
                        fprintf(fp_mips_flow,"add $a2 $a2 $sp\n");
                        fprintf(fp_mips_flow,"lw $s%d ($a2)\n",symlist[loc_1].snum);
                    }
                }
                else{
                    fprintf(fp_mips_flow,"sll $a2 $t%d 2\n",-var_3-1);
                    if(symlist[loc_2].global==0){
                        fprintf(fp_mips_flow,"sub $a2 $a3 $a2\n");
                        fprintf(fp_mips_flow,"add $a2 $a2 $gp\n");
                        fprintf(fp_mips_flow,"lw $s%d ($a2)\n",symlist[loc_1].snum);
                    }
                    else{
                        fprintf(fp_mips_flow,"add $a2 $a3 $a2\n");
                        fprintf(fp_mips_flow,"add $a2 $a2 $sp\n");
                        fprintf(fp_mips_flow,"lw $s%d ($a2)\n",symlist[loc_1].snum);
                    }
                }
            }
            else{
                for(i=0;i<10;i++){
                    if(strcmp(tregister[i],tmp_name1)==0){
                        break;
                    }
                }
                if(i==10){
                    loc = table_search(tregister[tregister_index]);
                    if(loc != -1 && symlist[loc].type!=0){
                        if(symlist[loc].global==0){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                        }
                        else{
                            fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                        }
                    }
                    strcpy(tregister[tregister_index],tmp_name1);
                    tregister_index = (tregister_index+1)%10;
                }
                for(i=0;i<8;i++){
                    if(strcmp(sregister[i],tmp_name3)==0){
                        var_3 = i;
                    }
                }
                for(i=0;i<10;i++){
                    if(strcmp(tregister[i],tmp_name3)==0){
                        var_3 = -i-1;
                    }
                    if(strcmp(tregister[i],tmp_name1)==0){
                        var_1 = i;
                    }
                }
                if(var_3>=0){
                    fprintf(fp_mips_flow,"sll $a2 $s%d 2\n",var_3);
                    if(symlist[loc_2].global==0){
                        fprintf(fp_mips_flow,"sub $a2 $a3 $a2\n");
                        fprintf(fp_mips_flow,"add $a2 $a2 $gp\n");
                        fprintf(fp_mips_flow,"lw $t%d ($a2)\n",var_1);
                    }
                    else{
                        fprintf(fp_mips_flow,"add $a2 $a3 $a2\n");
                        fprintf(fp_mips_flow,"add $a2 $a2 $sp\n");
                        fprintf(fp_mips_flow,"lw $t%d ($a2)\n",var_1);
                    }
                }
                else{
                    fprintf(fp_mips_flow,"sll $a2 $t%d 2\n",-var_3-1);
                    if(symlist[loc_2].global==0){
                        fprintf(fp_mips_flow,"sub $a2 $a3 $a2\n");
                        fprintf(fp_mips_flow,"add $a2 $a2 $gp\n");
                        fprintf(fp_mips_flow,"lw $t%d ($a2)\n",var_1);
                    }
                    else{
                        fprintf(fp_mips_flow,"add $a2 $a3 $a2\n");
                        fprintf(fp_mips_flow,"add $a2 $a2 $sp\n");
                        fprintf(fp_mips_flow,"lw $t%d ($a2)\n",var_1);
                    }
                }
            }
            break;
        }
        case CARRASN:{
            loc_1 = table_search(tmp_name1);
            loc_2 = table_search(tmp_name2);
            loc_3 = table_search(tmp_name3);
            if(loc_2==-1){
                for(i=0;i<10;i++){
                    if(strcmp(tmp_name2,tregister[i])==0){
                        break;
                    }
                }
                if(i==10){
                    loc = table_search(tregister[tregister_index]);
                    if(loc != -1 && symlist[loc].type!=0){
                        if(symlist[loc].global==0){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                        }
                        else{
                            fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                        }
                    }
                    fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,atoi(tmp_name2));
                    strcpy(tregister[tregister_index],tmp_name2);
                    tregister_index = (tregister_index+1)%10;
                }
            }
            else if(symlist[loc_2].haves==1){
                strcpy(sregister[symlist[loc_2].snum],tmp_name2);
            }
            else{
                for(i=0;i<10;i++){
                    if(strcmp(tmp_name2,tregister[i])==0){
                        break;
                    }
                }
                if(i==10){
                    loc = table_search(tregister[tregister_index]);
                    if(loc != -1 && symlist[loc].type!=0){
                        if(symlist[loc].global==0){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                        }
                        else{
                            fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                        }
                    }
                    if(symlist[loc_2].type==0){
                        fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,symlist[loc_2].addr);
                        strcpy(tregister[tregister_index],tmp_name2);
                        tregister_index = (tregister_index+1)%10;
                    }
                    else{
                        if(symlist[loc_2].global==0){
                            fprintf(fp_mips_flow,"lw $t%d %d($gp)\n",tregister_index,symlist[loc_2].addr);
                            strcpy(tregister[tregister_index],tmp_name2);
                            tregister_index = (tregister_index+1)%10;
                        }
                        else{
                            fprintf(fp_mips_flow,"lw $t%d %d($sp)\n",tregister_index,symlist[loc_2].addr);
                            strcpy(tregister[tregister_index],tmp_name2);
                            tregister_index = (tregister_index+1)%10;
                        }
                    }
                }
            }
            if(loc_3==-1){
                for(i=0;i<10;i++){
                    if(strcmp(tmp_name3,tregister[i])==0){
                        break;
                    }
                }
                if(i==10){
                    loc = table_search(tregister[tregister_index]);
                    if(loc != -1 && symlist[loc].type!=0){
                        if(symlist[loc].global==0){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                        }
                        else{
                            fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                        }
                    }
                    fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,atoi(tmp_name3));
                    strcpy(tregister[tregister_index],tmp_name3);
                    tregister_index = (tregister_index+1)%10;
                }
            }
            else if(symlist[loc_3].haves==1){
                strcpy(sregister[symlist[loc_3].snum],tmp_name3);
            }
            else{
                for(i=0;i<10;i++){
                    if(strcmp(tmp_name3,tregister[i])==0){
                        break;
                    }
                }
                if(i==10){
                    loc = table_search(tregister[tregister_index]);
                    if(loc != -1 && symlist[loc].type!=0){
                        if(symlist[loc].global==0){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                        }
                        else{
                            fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                        }
                    }
                    if(symlist[loc_3].type==0){
                        fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,symlist[loc_3].addr);
                        strcpy(tregister[tregister_index],tmp_name3);
                        tregister_index = (tregister_index+1)%10;
                    }
                    else{
                        if(symlist[loc_3].global==0){
                            fprintf(fp_mips_flow,"lw $t%d %d($gp)\n",tregister_index,symlist[loc_3].addr);
                            strcpy(tregister[tregister_index],tmp_name3);
                            tregister_index = (tregister_index+1)%10;
                        }
                        else{
                            fprintf(fp_mips_flow,"lw $t%d %d($sp)\n",tregister_index,symlist[loc_3].addr);
                            strcpy(tregister[tregister_index],tmp_name3);
                            tregister_index = (tregister_index+1)%10;
                        }
                    }
                }
            }
            for(i=0;i<8;i++){
                if(strcmp(sregister[i],tmp_name2)==0){
                    var_2=i;
                }
                if(strcmp(sregister[i],tmp_name3)==0){
                    var_3=i;
                }
            }
            for(i=0;i<10;i++){
                if(strcmp(tregister[i],tmp_name2)==0){
                    var_2=-i-1;
                }
                if(strcmp(tregister[i],tmp_name3)==0){
                    var_3=-i-1;
                }
            }
            if(var_2>=0){
                fprintf(fp_mips_flow,"sll $a2 $s%d 2\n",var_2);
            }
            else{
                fprintf(fp_mips_flow,"sll $a2 $t%d 2\n",-var_2-1);
            }
            fprintf(fp_mips_flow,"li $a3 %d\n",symlist[loc_1].addr);
            if(symlist[loc_1].global==0){
                if(var_3>=0){
                    fprintf(fp_mips_flow,"sub $a2 $a3 $a2\n");
                    fprintf(fp_mips_flow,"add $a2 $a2 $gp\n");
                    fprintf(fp_mips_flow,"sw $s%d ($a2)\n",var_3);
                }
                else{
                    fprintf(fp_mips_flow,"sub $a2 $a3 $a2\n");
                    fprintf(fp_mips_flow,"add $a2 $a2 $gp\n");
                    fprintf(fp_mips_flow,"sw $t%d ($a2)\n",-var_3-1);
                }
            }
            else{
                if(var_3>=0){
                    fprintf(fp_mips_flow,"add $a2 $a3 $a2\n");
                    fprintf(fp_mips_flow,"add $a2 $a2 $sp\n");
                    fprintf(fp_mips_flow,"sw $s%d ($a2)\n",var_3);
                }
                else{
                    fprintf(fp_mips_flow,"add $a2 $a3 $a2\n");
                    fprintf(fp_mips_flow,"add $a2 $a2 $sp\n");
                    fprintf(fp_mips_flow,"sw $t%d ($a2)\n",-var_3-1);
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
            loc_1 = table_search(tmp_name1);
            loc_2 = table_search(tmp_name2);
            loc_3 = table_search(tmp_name3);
            if(loc_2==-1){
                for(i=0;i<10;i++){
                    if(strcmp(tmp_name2,tregister[i])==0){
                        break;
                    }
                }
                if(i==10){
                    loc = table_search(tregister[tregister_index]);
                    if(loc != -1 && symlist[loc].type!=0){
                        if(symlist[loc].global==0){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                        }
                        else{
                            fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                        }
                    }
                    if(tmp_name2[0]=='\''){
                        fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,(int)tmp_name2[1]);
                    }
                    else{
                        fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,atoi(tmp_name2));
                    }
                    strcpy(tregister[tregister_index],tmp_name2);
                    tregister_index = (tregister_index+1)%10;
                }
            }
            else if(symlist[loc_2].haves==1){
                strcpy(sregister[symlist[loc_2].snum],tmp_name2);
            }
            else{
                for(i=0;i<10;i++){
                    if(strcmp(tmp_name2,tregister[i])==0){
                        break;
                    }
                }
                if(i==10){
                    loc = table_search(tregister[tregister_index]);
                    if(loc != -1 && symlist[loc].type!=0){
                        if(symlist[loc].global==0){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                        }
                        else{
                            fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                        }
                    }
                    if(symlist[loc_2].type==0){
                        fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,symlist[loc_2].addr);
                        strcpy(tregister[tregister_index],tmp_name2);
                        tregister_index = (tregister_index+1)%10;
                    }
                    else{
                        if(symlist[loc_2].global==0){
                            fprintf(fp_mips_flow,"lw $t%d %d($gp)\n",tregister_index,symlist[loc_2].addr);
                            strcpy(tregister[tregister_index],tmp_name2);
                            tregister_index = (tregister_index+1)%10;
                        }
                        else{
                            fprintf(fp_mips_flow,"lw $t%d %d($sp)\n",tregister_index,symlist[loc_2].addr);
                            strcpy(tregister[tregister_index],tmp_name2);
                            tregister_index = (tregister_index+1)%10;
                        }
                    }
                }
            }
            if(loc_1==-1){
                for(i=0;i<10;i++){
                    if(strcmp(tmp_name1,tregister[i])==0){
                        break;
                    }
                }
                if(i==10){
                    loc = table_search(tregister[tregister_index]);
                    if(loc != -1 && symlist[loc].type!=0){
                        if(symlist[loc].global==0){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                        }
                        else{
                            fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                        }
                    }
                    if(tmp_name1[0]=='\''){
                        fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,(int)tmp_name1[1]);
                    }
                    else{
                        fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,atoi(tmp_name1));
                    }
                    strcpy(tregister[tregister_index],tmp_name1);
                    tregister_index = (tregister_index+1)%10;
                }
            }
            else if(symlist[loc_1].haves==1){
                strcpy(sregister[symlist[loc_1].snum],tmp_name1);
            }
            else{
                for(i=0;i<10;i++){
                    if(strcmp(tmp_name1,tregister[i])==0){
                        break;
                    }
                }
                if(i==10){
                    loc = table_search(tregister[tregister_index]);
                    if(loc != -1 && symlist[loc].type!=0){
                        if(symlist[loc].global==0){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                        }
                        else{
                            fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                        }
                    }
                    if(symlist[loc_1].type==0){
                        fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,symlist[loc_1].addr);
                        strcpy(tregister[tregister_index],tmp_name1);
                        tregister_index = (tregister_index+1)%10;
                    }
                    else{
                        if(symlist[loc_1].global==0){
                            fprintf(fp_mips_flow,"lw $t%d %d($gp)\n",tregister_index,symlist[loc_1].addr);
                            strcpy(tregister[tregister_index],tmp_name1);
                            tregister_index = (tregister_index+1)%10;
                        }
                        else{
                            fprintf(fp_mips_flow,"lw $t%d %d($sp)\n",tregister_index,symlist[loc_1].addr);
                            strcpy(tregister[tregister_index],tmp_name1);
                            tregister_index = (tregister_index+1)%10;
                        }
                    }
                }
            }
            for(i=0;i<8;i++){
                if(strcmp(sregister[i],tmp_name2)==0){
                    var_2=i;
                }
                if(strcmp(sregister[i],tmp_name1)==0){
                    var_1=i;
                }
            }
            for(i=0;i<10;i++){
                if(strcmp(tregister[i],tmp_name2)==0){
                    var_2=-i-1;
                }
                if(strcmp(tregister[i],tmp_name1)==0){
                    var_1=-i-1;
                }
            }
            if(var_1>=0 && var_2>=0){
                switch(four_code_list_improve[mips_4code_flow_loc].code){
                    case CEQL:{
                        fprintf(fp_mips_flow,"beq $s%d $s%d %s\n",var_1,var_2,tmp_name3);
                        break;
                    }
                    case CGEQ:{
                        fprintf(fp_mips_flow,"sge $a2 $s%d $s%d\n",var_1,var_2);
                        fprintf(fp_mips_flow,"bgtz $a2 %s\n",tmp_name3);
                        break;
                    }
                    case CGTR:{
                        fprintf(fp_mips_flow,"sgt $a2 $s%d $s%d\n",var_1,var_2);
                        fprintf(fp_mips_flow,"bgtz $a2 %s\n",tmp_name3);
                        break;
                    }
                    case CLEQ:{
                        fprintf(fp_mips_flow,"sle $a2 $s%d $s%d\n",var_1,var_2);
                        fprintf(fp_mips_flow,"bgtz $a2 %s\n",tmp_name3);
                        break;
                    }
                    case CLSS:{
                        fprintf(fp_mips_flow,"slt $a2 $s%d $s%d\n",var_1,var_2);
                        fprintf(fp_mips_flow,"bgtz $a2 %s\n",tmp_name3);
                        break;
                    }
                    case CNEQ:{
                        fprintf(fp_mips_flow,"bne $s%d $s%d %s\n",var_1,var_2,tmp_name3);
                        break;
                    }
                }
            }
            else if(var_1>=0 && var_2<0){
                switch(four_code_list_improve[mips_4code_flow_loc].code){
                    case CEQL:{
                        fprintf(fp_mips_flow,"beq $s%d $t%d %s\n",var_1,-var_2-1,tmp_name3);
                        break;
                    }
                    case CGEQ:{
                        fprintf(fp_mips_flow,"sge $a2 $s%d $t%d\n",var_1,-var_2-1);
                        fprintf(fp_mips_flow,"bgtz $a2 %s\n",tmp_name3);
                        break;
                    }
                    case CGTR:{
                        fprintf(fp_mips_flow,"sgt $a2 $s%d $t%d\n",var_1,-var_2-1);
                        fprintf(fp_mips_flow,"bgtz $a2 %s\n",tmp_name3);
                        break;
                    }
                    case CLEQ:{
                        fprintf(fp_mips_flow,"sle $a2 $s%d $t%d\n",var_1,-var_2-1);
                        fprintf(fp_mips_flow,"bgtz $a2 %s\n",tmp_name3);
                        break;
                    }
                    case CLSS:{
                        fprintf(fp_mips_flow,"slt $a2 $s%d $t%d\n",var_1,-var_2-1);
                        fprintf(fp_mips_flow,"bgtz $a2 %s\n",tmp_name3);
                        break;
                    }
                    case CNEQ:{
                        fprintf(fp_mips_flow,"bne $s%d $t%d %s\n",var_1,-var_2-1,tmp_name3);
                        break;
                    }
                }
            }
            else if(var_1<0 && var_2>=0){
                switch(four_code_list_improve[mips_4code_flow_loc].code){
                    case CEQL:{
                        fprintf(fp_mips_flow,"beq $t%d $s%d %s\n",-var_1-1,var_2,tmp_name3);
                        break;
                    }
                    case CGEQ:{
                        fprintf(fp_mips_flow,"sge $a2 $t%d $s%d\n",-var_1-1,var_2);
                        fprintf(fp_mips_flow,"bgtz $a2 %s\n",tmp_name3);
                        break;
                    }
                    case CGTR:{
                        fprintf(fp_mips_flow,"sgt $a2 $t%d $s%d\n",-var_1-1,var_2);
                        fprintf(fp_mips_flow,"bgtz $a2 %s\n",tmp_name3);
                        break;
                    }
                    case CLEQ:{
                        fprintf(fp_mips_flow,"sle $a2 $t%d $s%d\n",-var_1-1,var_2);
                        fprintf(fp_mips_flow,"bgtz $a2 %s\n",tmp_name3);
                        break;
                    }
                    case CLSS:{
                        fprintf(fp_mips_flow,"slt $a2 $t%d $s%d\n",-var_1-1,var_2);
                        fprintf(fp_mips_flow,"bgtz $a2 %s\n",tmp_name3);
                        break;
                    }
                    case CNEQ:{
                        fprintf(fp_mips_flow,"bne $t%d $s%d %s\n",-var_1-1,var_2,tmp_name3);
                        break;
                    }
                }
            }
            else if(var_1<0 && var_2<0){
                switch(four_code_list_improve[mips_4code_flow_loc].code){
                    case CEQL:{
                        fprintf(fp_mips_flow,"beq $t%d $t%d %s\n",-var_1-1,-var_2-1,tmp_name3);
                        break;
                    }
                    case CGEQ:{
                        fprintf(fp_mips_flow,"sge $a2 $t%d $t%d\n",-var_1-1,-var_2-1);
                        fprintf(fp_mips_flow,"bgtz $a2 %s\n",tmp_name3);
                        break;
                    }
                    case CGTR:{
                        fprintf(fp_mips_flow,"sgt $a2 $t%d $t%d\n",-var_1-1,-var_2-1);
                        fprintf(fp_mips_flow,"bgtz $a2 %s\n",tmp_name3);
                        break;
                    }
                    case CLEQ:{
                        fprintf(fp_mips_flow,"sle $a2 $t%d $t%d\n",-var_1-1,-var_2-1);
                        fprintf(fp_mips_flow,"bgtz $a2 %s\n",tmp_name3);
                        break;
                    }
                    case CLSS:{
                        fprintf(fp_mips_flow,"slt $a2 $t%d $t%d\n",-var_1-1,-var_2-1);
                        fprintf(fp_mips_flow,"bgtz $a2 %s\n",tmp_name3);
                        break;
                    }
                    case CNEQ:{
                        fprintf(fp_mips_flow,"bne $t%d $t%d %s\n",-var_1-1,-var_2-1,tmp_name3);
                        break;
                    }
                }
            }
            break;
        }
        case CJUMP:{
            fprintf(fp_mips_flow,"j %s\n",tmp_name1);
            break;
        }
        case CASSIGN:{
            loc_1 = table_search(tmp_name1);
            loc_2 = table_search(tmp_name2);
            loc_3 = table_search(tmp_name3);
            if(loc_2==-1){}
            else if(symlist[loc_2].haves==1){
                strcpy(sregister[symlist[loc_2].snum],tmp_name2);
            }
            else{
                for(i=0;i<10;i++){
                    if(strcmp(tmp_name2,tregister[i])==0){
                        break;
                    }
                }
                if(i==10){
                    loc = table_search(tregister[tregister_index]);
                    if(loc != -1 && symlist[loc].type!=0){
                        if(symlist[loc].global==0){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                        }
                        else{
                            fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                        }
                    }
                    if(symlist[loc_2].type==0){
                        fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,symlist[loc_2].addr);
                        strcpy(tregister[tregister_index],tmp_name2);
                        tregister_index = (tregister_index+1)%10;
                    }
                    else{
                        if(symlist[loc_2].global==0){
                            fprintf(fp_mips_flow,"lw $t%d %d($gp)\n",tregister_index,symlist[loc_2].addr);
                            strcpy(tregister[tregister_index],tmp_name2);
                            tregister_index = (tregister_index+1)%10;
                        }
                        else{
                            fprintf(fp_mips_flow,"lw $t%d %d($sp)\n",tregister_index,symlist[loc_2].addr);
                            strcpy(tregister[tregister_index],tmp_name2);
                            tregister_index = (tregister_index+1)%10;
                        }
                    }
                }
            }
            for(i=0;i<8;i++){
                if(strcmp(sregister[i],tmp_name2)==0){
                    var_2 = i;
                }
            }
            for(i=0;i<10;i++){
                if(strcmp(tregister[i],tmp_name2)==0){
                    var_2 = -i-1;
                }
            }
            if(symlist[loc_1].haves==1){
                if(loc_2==-1){
                    if(tmp_name2[0]=='\''){
                        fprintf(fp_mips_flow,"li $s%d %d\n",symlist[loc_1].snum,(int)tmp_name2[1]);
                    }
                    else{
                        fprintf(fp_mips_flow,"li $s%d %d\n",symlist[loc_1].snum,atoi(tmp_name2));
                    }
                }
                else if(var_2>=0){
                    fprintf(fp_mips_flow,"add $s%d $0 $s%d\n",symlist[loc_1].snum,var_2);
                }
                else{
                    fprintf(fp_mips_flow,"add $s%d $0 $t%d\n",symlist[loc_1].snum,-var_2-1);
                }
            }
            else{
                 for(i=0;i<10;i++){
                    if(strcmp(tregister[i],tmp_name1)==0){
                        break;
                    }
                }
                if(i==10){
                    loc = table_search(tregister[tregister_index]);
                    if(loc != -1 && symlist[loc].type!=0){
                        if(symlist[loc].global==0){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                        }
                        else{
                            fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                        }
                    }
                    strcpy(tregister[tregister_index],tmp_name1);
                    tregister_index = (tregister_index+1)%10;
                }
                for(i=0;i<8;i++){
                    if(strcmp(sregister[i],tmp_name2)==0){
                        var_2=i;
                    }
                }
                for(i=0;i<10;i++){
                    if(strcmp(tregister[i],tmp_name1)==0){
                        var_1 = i;
                    }
                    if(strcmp(tregister[i],tmp_name2)==0){
                        var_2=-i-1;
                    }
                }
                if(loc_2==-1){
                    if(tmp_name2[0]=='\''){
                        fprintf(fp_mips_flow,"li $t%d %d\n",var_1,(int)tmp_name2[1]);
                    }
                    else{
                        fprintf(fp_mips_flow,"li $t%d %d\n",var_1,atoi(tmp_name2));
                    }
                }
                else if(var_2>=0){
                    fprintf(fp_mips_flow,"add $t%d $0 $s%d\n",var_1,var_2);
                }
                else{
                    fprintf(fp_mips_flow,"add $t%d $0 $t%d\n",var_1,-var_2-1);
                }
            }
            break;
        }
        case CPUSH:{
            loc_1 = table_search(tmp_name1);
            loc_2 = table_search(tmp_name2);
            int i = atoi(tmp_name3);
            fprintf(fp_mips_flow,"subi $a2 $sp 32\n");
            fprintf(fp_mips_flow,"subi $a2 $a2 %d\n",symlist[loc_2].after_dag);
            fprintf(fp_mips_flow,"li $a3 %d\n",i);
            fprintf(fp_mips_flow,"sll $a3 $a3 2\n");
            fprintf(fp_mips_flow,"add $a2 $a2 $a3\n");
            if(loc_1==-1){
                for(i=0;i<10;i++){
                    if(strcmp(tmp_name1,tregister[i])==0){
                        break;
                    }
                }
                if(i==10){
                    loc = table_search(tregister[tregister_index]);
                    if(loc != -1 && symlist[loc].type!=0){
                        if(symlist[loc].global==0){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                        }
                        else{
                            fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                        }
                    }
                    if(tmp_name1[0]=='\''){
                        fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,(int)tmp_name1[1]);
                    }
                    else{
                        fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,atoi(tmp_name1));
                    }
                    strcpy(tregister[tregister_index],tmp_name1);
                    tregister_index = (tregister_index+1)%10;
                }
            }
            else if(symlist[loc_1].haves==1){
                strcpy(sregister[symlist[loc_1].snum],tmp_name1);
            }
            else{
                for(i=0;i<10;i++){
                    if(strcmp(tmp_name1,tregister[i])==0){
                        break;
                    }
                }
                if(i==10){
                    loc = table_search(tregister[tregister_index]);
                    if(loc != -1 && symlist[loc].type!=0){
                        if(symlist[loc].global==0){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                        }
                        else{
                            fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                        }
                    }
                    if(symlist[loc_1].type==0){
                        fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,symlist[loc_1].addr);
                        strcpy(tregister[tregister_index],tmp_name1);
                        tregister_index = (tregister_index+1)%10;
                    }
                    else{
                        if(symlist[loc_1].global==0){
                            fprintf(fp_mips_flow,"lw $t%d %d($gp)\n",tregister_index,symlist[loc_1].addr);
                            strcpy(tregister[tregister_index],tmp_name1);
                            tregister_index = (tregister_index+1)%10;
                        }
                        else{
                            fprintf(fp_mips_flow,"lw $t%d %d($sp)\n",tregister_index,symlist[loc_1].addr);
                            strcpy(tregister[tregister_index],tmp_name1);
                            tregister_index = (tregister_index+1)%10;
                        }
                    }
                }
            }
            for(i=0;i<8;i++){
                if(strcmp(sregister[i],tmp_name1)==0){
                    var_1=i;
                }
            }
            for(i=0;i<10;i++){
                if(strcmp(tregister[i],tmp_name1)==0){
                    var_1=-i-1;
                }
            }
            if(var_1>=0){
                fprintf(fp_mips_flow,"sw $s%d ($a2)\n",var_1);
            }
            else{
                fprintf(fp_mips_flow,"sw $t%d ($a2)\n",-var_1-1);
            }
            break;
        }
        case CCALL:{
            char fun_name[Max_ident+1]={"_F\0"};
            strcat(tmp_name1,fun_name);
            fprintf(fp_mips_flow,"jal %s\n",tmp_name1);
            break;
        }
        case CRET:{
            loc_1 = table_search(tmp_name1);
            if(loc_1==-1){
                for(i=0;i<10;i++){
                    if(strcmp(tmp_name1,tregister[i])==0){
                        break;
                    }
                }
                if(i==10){
                    loc = table_search(tregister[tregister_index]);
                    if(loc != -1 && symlist[loc].type!=0){
                        if(symlist[loc].global==0){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                        }
                        else{
                            fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                        }
                    }
                    if(tmp_name1[0]=='\''){
                        fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,(int)tmp_name1[1]);
                    }
                    else{
                        fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,atoi(tmp_name1));
                    }
                    strcpy(tregister[tregister_index],tmp_name1);
                    tregister_index = (tregister_index+1)%10;
                }
            }
            else if(symlist[loc_1].haves==1){
                strcpy(sregister[symlist[loc_1].snum],tmp_name1);
            }
            else{
                for(i=0;i<10;i++){
                    if(strcmp(tmp_name1,tregister[i])==0){
                        break;
                    }
                }
                if(i==10){
                    loc = table_search(tregister[tregister_index]);
                    if(loc != -1 && symlist[loc].type!=0){
                        if(symlist[loc].global==0){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                        }
                        else{
                            fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                        }
                    }
                    if(symlist[loc_1].type==0){
                        fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,symlist[loc_1].addr);
                        strcpy(tregister[tregister_index],tmp_name1);
                        tregister_index = (tregister_index+1)%10;
                    }
                    else{
                        if(symlist[loc_1].global==0){
                            fprintf(fp_mips_flow,"lw $t%d %d($gp)\n",tregister_index,symlist[loc_1].addr);
                            strcpy(tregister[tregister_index],tmp_name1);
                            tregister_index = (tregister_index+1)%10;
                        }
                        else{
                            fprintf(fp_mips_flow,"lw $t%d %d($sp)\n",tregister_index,symlist[loc_1].addr);
                            strcpy(tregister[tregister_index],tmp_name1);
                            tregister_index = (tregister_index+1)%10;
                        }
                    }
                }
            }
            for(i=0;i<8;i++){
                if(strcmp(sregister[i],tmp_name1)==0){
                    var_1=i;
                }
            }
            for(i=0;i<10;i++){
                if(strcmp(tregister[i],tmp_name1)==0){
                    var_1=-i-1;
                }
            }
            if(var_1>=0){
                fprintf(fp_mips_flow,"move $v0 $s%d\n",var_1);
            }
            else{
                fprintf(fp_mips_flow,"move $v0 $t%d\n",-var_1-1);
            }
            fprintf(fp_mips_flow,"jr $ra\n");
            break;
        }
        case CNRET:{
            if(inmflag==0){
                fprintf(fp_mips_flow,"jr $ra\n");
            }
            else{
                fprintf(fp_mips_flow,"j END\n");
            }
            break;
        }
        case CRETVAL:{
            loc_1 = table_search(tmp_name1);
            if(loc_1==-1){
                for(i=0;i<10;i++){
                    if(strcmp(tmp_name1,tregister[i])==0){
                        break;
                    }
                }
                if(i==10){
                    loc = table_search(tregister[tregister_index]);
                    if(loc != -1 && symlist[loc].type!=0){
                        if(symlist[loc].global==0){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                        }
                        else{
                            fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                        }
                    }
                    if(tmp_name1[0]=='\''){
                        fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,(int)tmp_name1[1]);
                    }
                    else{
                        fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,atoi(tmp_name1));
                    }
                    strcpy(tregister[tregister_index],tmp_name1);
                    tregister_index = (tregister_index+1)%10;
                }
            }
            else if(symlist[loc_1].haves==1){
                strcpy(sregister[symlist[loc_1].snum],tmp_name1);
            }
            else{
                for(i=0;i<10;i++){
                    if(strcmp(tmp_name1,tregister[i])==0){
                        break;
                    }
                }
                if(i==10){
                    loc = table_search(tregister[tregister_index]);
                    if(loc != -1 && symlist[loc].type!=0){
                        if(symlist[loc].global==0){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                        }
                        else{
                            fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                        }
                    }
                    if(symlist[loc_1].type==0){
                        fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,symlist[loc_1].addr);
                        strcpy(tregister[tregister_index],tmp_name1);
                        tregister_index = (tregister_index+1)%10;
                    }
                    else{
                        if(symlist[loc_1].global==0){
                            fprintf(fp_mips_flow,"lw $t%d %d($gp)\n",tregister_index,symlist[loc_1].addr);
                            strcpy(tregister[tregister_index],tmp_name1);
                            tregister_index = (tregister_index+1)%10;
                        }
                        else{
                            fprintf(fp_mips_flow,"lw $t%d %d($sp)\n",tregister_index,symlist[loc_1].addr);
                            strcpy(tregister[tregister_index],tmp_name1);
                            tregister_index = (tregister_index+1)%10;
                        }
                    }
                }
            }
            for(i=0;i<8;i++){
                if(strcmp(sregister[i],tmp_name1)==0){
                    var_1=i;
                }
            }
            for(i=0;i<10;i++){
                if(strcmp(tregister[i],tmp_name1)==0){
                    var_1=-i-1;
                }
            }
            if(var_1>=0){
                fprintf(fp_mips_flow,"move $s%d $v0\n",var_1);
            }
            else{
                fprintf(fp_mips_flow,"move $t%d $v0\n",-var_1-1);
            }
            break;
        }
        case CLABEL:{
            fprintf(fp_mips_flow,"%s:\n",tmp_name1);
            break;
        }
        case CSCANF:{
            loc_1 = table_search(tmp_name1);
            if(symlist[loc_1].haves==1){
                if(symlist[loc_1].type_data==0){
                    fprintf(fp_mips_flow,"li $v0 5\n");
                    fprintf(fp_mips_flow,"syscall\n");
                    fprintf(fp_mips_flow,"add $s%d $0 $v0\n",symlist[loc_1].snum);
                }
                else{
                    fprintf(fp_mips_flow,"li $v0 12\n");
                    fprintf(fp_mips_flow,"syscall\n");
                    fprintf(fp_mips_flow,"add $s%d $0 $v0\n",symlist[loc_1].snum);
                }
            }
            else{
                 for(i=0;i<10;i++){
                    if(strcmp(tregister[i],tmp_name1)==0){
                        break;
                    }
                }
                if(i==10){
                    loc = table_search(tregister[tregister_index]);
                    if(loc != -1 && symlist[loc].type!=0){
                        if(symlist[loc].global==0){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                        }
                        else{
                            fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                        }
                    }
                    strcpy(tregister[tregister_index],tmp_name1);
                    tregister_index = (tregister_index+1)%10;
                }
                for(i=0;i<10;i++){
                    if(strcmp(tregister[i],tmp_name1)==0){
                        var_1 = i;
                    }
                }
                if(symlist[loc_1].type_data==0){
                    fprintf(fp_mips_flow,"li $v0 5\n");
                    fprintf(fp_mips_flow,"syscall\n");
                    fprintf(fp_mips_flow,"add $t%d $0 $v0\n",var_1);
                }
                else{
                    fprintf(fp_mips_flow,"li $v0 12\n");
                    fprintf(fp_mips_flow,"syscall\n");
                    fprintf(fp_mips_flow,"add $t%d $0 $v0\n",var_1);
                }
            }
            break;
        }
        case CPRINTF:{
            loc_1 = table_search(tmp_name1);
            if(loc_1==-1){
                if(tmp_name1[0]=='\''){
                    fprintf(fp_mips_flow,"li $a0 %d\n",(int)tmp_name1[1]);
                    fprintf(fp_mips_flow,"li $v0 11\n");
                    fprintf(fp_mips_flow,"syscall\n");
                }
                else{
                    fprintf(fp_mips_flow,"li $a0 %d\n",atoi(tmp_name1));
                    fprintf(fp_mips_flow,"li $v0 1\n");
                    fprintf(fp_mips_flow,"syscall\n");
                }
            }
            else{
                if(symlist[loc_1].haves==1){
                    if(symlist[loc_1].type_data==0){
                        fprintf(fp_mips_flow,"add $a0 $0 $s%d\n",symlist[loc_1].snum);
                        fprintf(fp_mips_flow,"li $v0 1\n");
                        fprintf(fp_mips_flow,"syscall\n");
                    }
                    else{
                        fprintf(fp_mips_flow,"add $a0 $0 $s%d\n",symlist[loc_1].snum);
                        fprintf(fp_mips_flow,"li $v0 11\n");
                        fprintf(fp_mips_flow,"syscall\n");
                    }
                }
                else{
                    for(i=0;i<10;i++){
                        if(strcmp(tregister[i],tmp_name1)==0){
                            break;
                        }
                    }
                    if(i==10){
                        loc = table_search(tregister[tregister_index]);
                        if(loc != -1 && symlist[loc].type!=0){
                            if(symlist[loc].global==0){
                                fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",tregister_index,symlist[loc].addr);
                            }
                            else{
                                fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",tregister_index,symlist[loc].addr);
                            }
                        }
                        if(symlist[loc_1].type==0){
                        fprintf(fp_mips_flow,"li $t%d %d\n",tregister_index,symlist[loc_1].addr);
                        }
                        else if(symlist[loc_1].global==0){
                            fprintf(fp_mips_flow,"lw $t%d %d($gp)\n",tregister_index,symlist[loc_1].addr);
                        }
                        else{
                            fprintf(fp_mips_flow,"lw $t%d %d($sp)\n",tregister_index,symlist[loc_1].addr);
                        }
                        strcpy(tregister[tregister_index],tmp_name1);
                        tregister_index = (tregister_index+1)%10;
                    }
                    for(i=0;i<10;i++){
                        if(strcmp(tregister[i],tmp_name1)==0){
                            var_1=i;
                        }
                    }
                    if(symlist[loc_1].type_data==0){
                        fprintf(fp_mips_flow,"add $a0 $0 $t%d\n",var_1);
                        fprintf(fp_mips_flow,"li $v0 1\n");
                        fprintf(fp_mips_flow,"syscall\n");
                    }
                    else{
                        fprintf(fp_mips_flow,"add $a0 $0 $t%d\n",var_1);
                        fprintf(fp_mips_flow,"li $v0 11\n");
                        fprintf(fp_mips_flow,"syscall\n");
                    }
                }
            }
            fprintf(fp_mips_flow,"li $v0 11\n");
            fprintf(fp_mips_flow,"li $a0 10\n");
            fprintf(fp_mips_flow,"syscall\n");
            break;
        }
        case CPRINTF_ST:{
            fprintf(fp_mips_flow,".data\nstring_%d:  .asciiz\"%s\"\n",string_num,four_code_list_improve[mips_4code_flow_loc].index_string);
            fprintf(fp_mips_flow,".text\n");
            fprintf(fp_mips_flow,"la $a0 string_%d\n",string_num);
            fprintf(fp_mips_flow,"li $v0 4\n");
            fprintf(fp_mips_flow,"syscall\n");
            string_num++;
            fprintf(fp_mips_flow,"li $v0 11\n");
            fprintf(fp_mips_flow,"li $a0 10\n");
            fprintf(fp_mips_flow,"syscall\n");
            break;
        }
        case CPUSH_STACK:{
            loc_1 = table_search(tmp_name1);
            fprintf(fp_mips_flow,"subi $sp $sp %d\n",symlist[loc_1].after_dag);
            break;
        }
        case CPULL_STACK:{
            loc_1 = table_search(tmp_name1);
            fprintf(fp_mips_flow,"addi $sp $sp %d\n",symlist[loc_1].after_dag);
            break;
        }
        case CSAVE_ENV:{
            fprintf(fp_mips_flow,"subi $sp $sp 32\n");
            fprintf(fp_mips_flow,"sw $s0 0($sp)\n");
            fprintf(fp_mips_flow,"sw $s1 4($sp)\n");
            fprintf(fp_mips_flow,"sw $s2 8($sp)\n");
            fprintf(fp_mips_flow,"sw $s3 12($sp)\n");
            fprintf(fp_mips_flow,"sw $s4 16($sp)\n");
            fprintf(fp_mips_flow,"sw $s5 20($sp)\n");
            fprintf(fp_mips_flow,"sw $s6 24($sp)\n");
            fprintf(fp_mips_flow,"sw $s7 28($sp)\n");
            fprintf(fp_mips_flow,"sw $ra 32($sp)\n");
            break;
        }
        case CREV_ENV:{
            fprintf(fp_mips_flow,"lw $ra 32($sp)\n");
            fprintf(fp_mips_flow,"lw $s7 28($sp)\n");
            fprintf(fp_mips_flow,"lw $s6 24($sp)\n");
            fprintf(fp_mips_flow,"lw $s5 20($sp)\n");
            fprintf(fp_mips_flow,"lw $s4 16($sp)\n");
            fprintf(fp_mips_flow,"lw $s3 12($sp)\n");
            fprintf(fp_mips_flow,"lw $s2 8($sp)\n");
            fprintf(fp_mips_flow,"lw $s1 4($sp)\n");
            fprintf(fp_mips_flow,"lw $s0 0($sp)\n");
            fprintf(fp_mips_flow,"addi $sp $sp 32\n");
            break;
        }
        default:{
            fprintf(fp_mips_flow,"wrong\n");
        }
    }
    for(i=0;i<block_index;i++){
        if(mips_4code_flow_loc == block_list[i].end_block){
            switch(four_code_list_improve[mips_4code_flow_loc].code){
                case CEQL:{}
                case CGEQ:{}
                case CGTR:{}
                case CLEQ:{}
                case CLSS:{}
                case CNEQ:{}
                case CJUMP:{}
                case CRET:{}
                case CNRET:{}
                case CSAVE_ENV:{
                    break;
                }
                case CPASS:{}
                case CADD:{}
                case CMINUS:{}
                case CTIME:{}
                case CDIV:{}
                case CARRVAL:{}
                case CARRASN:{}
                case CASSIGN:{}
                case CPUSH:{}
                case CPUSH_STACK:{}
                case CRETVAL:{}
                case CLABEL:{}
                case CSCANF:{}
                case CPRINTF:{}
                case CPRINTF_ST:{}
                case CREV_ENV:{
                    for(j=0;j<block_list[i].out_index;j++){
                        for(k=0;k<10;k++){
                            if(strcmp(block_list[i].out[j],tregister[k])==0){
                                loc = table_search(tregister[k]);
                                if(loc==-1 || symlist[loc].global==0){
                                    printf("there may be something wrong in write back\n");
                                }
                                fprintf(fp_mips_flow,"sw $t%d %d($sp)\n",k,symlist[loc].addr);
                            }
                        }
                    }
                    for(k=0;k<10;k++){
                        loc = table_search(tregister[k]);
                        if(symlist[loc].global==0 && loc!=-1){
                            fprintf(fp_mips_flow,"sw $t%d %d($gp)\n",k,symlist[loc].addr);
                        }
                    }
                    break;
                }
                default:{
                    printf("%d %d",four_code_list_improve[mips_4code_flow_loc].code,mips_4code_flow_loc);
                    printf("there may be something wrong in write back2\n");
                }
            }
            for(j=0;j<10;j++){
                tregister[j][0]='\0';
            }
            tregister_index=0;
        }
    }
    return;
}
