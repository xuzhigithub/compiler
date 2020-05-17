#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "define.h"
#include "debug.h"

void mips(){
    int loc_1;
    int loc_2;
    int loc_3;
    char tmp_name1[Max_ident+1];
    char tmp_name2[Max_ident+1];
    char tmp_name3[Max_ident+1];
    strcpy(tmp_name1,four_code_list[mips_4code_loc].para_1);
    strcpy(tmp_name2,four_code_list[mips_4code_loc].para_2);
    strcpy(tmp_name3,four_code_list[mips_4code_loc].para_3);
    switch (four_code_list[mips_4code_loc].code){
        case CPASS:{
            fprintf(fp_mips,"nop\n");
            break;
        }
        case CADD:{
            loc_1 = table_search(tmp_name1);
            loc_2 = table_search(tmp_name2);
            loc_3 = table_search(tmp_name3);
            if(symlist[loc_2].type==0){
                fprintf(fp_mips,"li $t0 %d\n",symlist[loc_2].addr);
            }
            else{
                if(symlist[loc_2].global==0){
                    fprintf(fp_mips,"lw $t0 %d($gp)\n",symlist[loc_2].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t0 %d($sp)\n",symlist[loc_2].addr);
                }
            }
            if(symlist[loc_3].type==0){
                fprintf(fp_mips,"li $t1 %d\n",symlist[loc_3].addr);
            }
            else{
                if(symlist[loc_3].global==0){
                    fprintf(fp_mips,"lw $t1 %d($gp)\n",symlist[loc_3].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t1 %d($sp)\n",symlist[loc_3].addr);
                }
            }
            fprintf(fp_mips,"add $t2 $t0 $t1\n");
            if(symlist[loc_1].global==0){
                fprintf(fp_mips,"sw $t2 %d($gp)\n",symlist[loc_1].addr);
            }
            else{
                fprintf(fp_mips,"sw $t2 %d($sp)\n",symlist[loc_1].addr);
            }
            break;
        }
        case CMINUS:{
            loc_1 = table_search(tmp_name1);
            loc_2 = table_search(tmp_name2);
            loc_3 = table_search(tmp_name3);
            if(symlist[loc_2].type==0){
                fprintf(fp_mips,"li $t0 %d\n",symlist[loc_2].addr);
            }
            else{
                if(symlist[loc_2].global==0){
                    fprintf(fp_mips,"lw $t0 %d($gp)\n",symlist[loc_2].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t0 %d($sp)\n",symlist[loc_2].addr);
                }
            }
            if(symlist[loc_3].type==0){
                fprintf(fp_mips,"li $t1 %d\n",symlist[loc_3].addr);
            }
            else{
                if(symlist[loc_3].global==0){
                    fprintf(fp_mips,"lw $t1 %d($gp)\n",symlist[loc_3].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t1 %d($sp)\n",symlist[loc_3].addr);
                }
            }
            fprintf(fp_mips,"sub $t2 $t0 $t1\n");
            if(symlist[loc_1].global==0){
                fprintf(fp_mips,"sw $t2 %d($gp)\n",symlist[loc_1].addr);
            }
            else{
                fprintf(fp_mips,"sw $t2 %d($sp)\n",symlist[loc_1].addr);
            }
            break;
        }
        case CTIME:{
            loc_1 = table_search(tmp_name1);
            loc_2 = table_search(tmp_name2);
            loc_3 = table_search(tmp_name3);
            if(symlist[loc_2].type==0){
                fprintf(fp_mips,"li $t0 %d\n",symlist[loc_2].addr);
            }
            else{
                if(symlist[loc_2].global==0){
                    fprintf(fp_mips,"lw $t0 %d($gp)\n",symlist[loc_2].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t0 %d($sp)\n",symlist[loc_2].addr);
                }
            }
            if(symlist[loc_3].type==0){
                fprintf(fp_mips,"li $t1 %d\n",symlist[loc_3].addr);
            }
            else{
                if(symlist[loc_3].global==0){
                    fprintf(fp_mips,"lw $t1 %d($gp)\n",symlist[loc_3].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t1 %d($sp)\n",symlist[loc_3].addr);
                }
            }
            fprintf(fp_mips,"mul $t2 $t0 $t1\n");
            if(symlist[loc_1].global==0){
                fprintf(fp_mips,"sw $t2 %d($gp)\n",symlist[loc_1].addr);
            }
            else{
                fprintf(fp_mips,"sw $t2 %d($sp)\n",symlist[loc_1].addr);
            }
            break;
        }
        case CDIV:{
            loc_1 = table_search(tmp_name1);
            loc_2 = table_search(tmp_name2);
            loc_3 = table_search(tmp_name3);
            if(symlist[loc_2].type==0){
                fprintf(fp_mips,"li $t0 %d\n",symlist[loc_2].addr);
            }
            else{
                if(symlist[loc_2].global==0){
                    fprintf(fp_mips,"lw $t0 %d($gp)\n",symlist[loc_2].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t0 %d($sp)\n",symlist[loc_2].addr);
                }
            }
            if(symlist[loc_3].type==0){
                fprintf(fp_mips,"li $t1 %d\n",symlist[loc_3].addr);
            }
            else{
                if(symlist[loc_3].global==0){
                    fprintf(fp_mips,"lw $t1 %d($gp)\n",symlist[loc_3].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t1 %d($sp)\n",symlist[loc_3].addr);
                }
            }
            fprintf(fp_mips,"div $t2 $t0 $t1\n");
            if(symlist[loc_1].global==0){
                fprintf(fp_mips,"sw $t2 %d($gp)\n",symlist[loc_1].addr);
            }
            else{
                fprintf(fp_mips,"sw $t2 %d($sp)\n",symlist[loc_1].addr);
            }
            break;
        }
        case CARRVAL:{
            loc_1 = table_search(tmp_name1);
            loc_2 = table_search(tmp_name2);
            loc_3 = table_search(tmp_name3);
            fprintf(fp_mips,"li $t0 %d\n",symlist[loc_2].addr);
            if(symlist[loc_3].type==0){
                fprintf(fp_mips,"li $t1 %d\n",symlist[loc_3].addr);
            }
            else{
                if(symlist[loc_3].global==0){
                    fprintf(fp_mips,"lw $t1 %d($gp)\n",symlist[loc_3].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t1 %d($sp)\n",symlist[loc_3].addr);
                }
            }
            fprintf(fp_mips,"sll $t1 $t1 2\n");
            if(symlist[loc_2].global==0){
                fprintf(fp_mips,"sub $t2 $t0 $t1\n");
                fprintf(fp_mips,"add $t2 $t2 $gp\n");
                fprintf(fp_mips,"lw $t3 ($t2)\n");
            }
            else{
                fprintf(fp_mips,"add $t2 $t0 $t1\n");
                fprintf(fp_mips,"add $t2 $t2 $sp\n");
                fprintf(fp_mips,"lw $t3 ($t2)\n");
            }
            if(symlist[loc_1].global==0){
                fprintf(fp_mips,"sw $t3 %d($gp)\n",symlist[loc_1].addr);
            }
            else{
                fprintf(fp_mips,"sw $t3 %d($sp)\n",symlist[loc_1].addr);
            }
            break;
        }
        case CARRASN:{
            loc_1 = table_search(tmp_name1);
            loc_2 = table_search(tmp_name2);
            loc_3 = table_search(tmp_name3);
            if(symlist[loc_3].type==0){
                fprintf(fp_mips,"li $t0 %d\n",symlist[loc_3].addr);
            }
            else{
                if(symlist[loc_3].global==0){
                    fprintf(fp_mips,"lw $t0 %d($gp)\n",symlist[loc_3].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t0 %d($sp)\n",symlist[loc_3].addr);
                }
            }
            fprintf(fp_mips,"li $t1 %d\n",symlist[loc_1].addr);
            if(symlist[loc_2].type==0){
                fprintf(fp_mips,"li $t2 %d\n",symlist[loc_2].addr);
            }
            else{
                if(symlist[loc_2].global==0){
                    fprintf(fp_mips,"lw $t2 %d($gp)\n",symlist[loc_2].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t2 %d($sp)\n",symlist[loc_2].addr);
                }
            }
            fprintf(fp_mips,"sll $t2 $t2 2\n");
            if(symlist[loc_1].global==0){
                fprintf(fp_mips,"sub $t3 $t1 $t2\n");
                fprintf(fp_mips,"add $t3 $t3 $gp\n");
                fprintf(fp_mips,"sw $t0 ($t3)\n");
            }
            else{
                fprintf(fp_mips,"add $t3 $t1 $t2\n");
                fprintf(fp_mips,"add $t3 $t3 $sp\n");
                fprintf(fp_mips,"sw $t0 ($t3)\n");
            }
            break;
        }
        case CEQL:{
            loc_1 = table_search(tmp_name1);
            loc_2 = table_search(tmp_name2);
            if(symlist[loc_1].type==0){
                fprintf(fp_mips,"li $t0 %d\n",symlist[loc_1].addr);
            }
            else{
                if(symlist[loc_1].global==0){
                    fprintf(fp_mips,"lw $t0 %d($gp)\n",symlist[loc_1].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t0 %d($sp)\n",symlist[loc_1].addr);
                }
            }
            if(symlist[loc_2].type==0){
                fprintf(fp_mips,"li $t1 %d\n",symlist[loc_2].addr);
            }
            else{
                if(symlist[loc_2].global==0){
                    fprintf(fp_mips,"lw $t1 %d($gp)\n",symlist[loc_2].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t1 %d($sp)\n",symlist[loc_2].addr);
                }
            }
            fprintf(fp_mips,"beq $t0 $t1 %s\n",tmp_name3);
            break;
        }
        case CGEQ:{
            loc_1 = table_search(tmp_name1);
            loc_2 = table_search(tmp_name2);
            if(symlist[loc_1].type==0){
                fprintf(fp_mips,"li $t0 %d\n",symlist[loc_1].addr);
            }
            else{
                if(symlist[loc_1].global==0){
                    fprintf(fp_mips,"lw $t0 %d($gp)\n",symlist[loc_1].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t0 %d($sp)\n",symlist[loc_1].addr);
                }
            }
            if(symlist[loc_2].type==0){
                fprintf(fp_mips,"li $t1 %d\n",symlist[loc_2].addr);
            }
            else{
                if(symlist[loc_2].global==0){
                    fprintf(fp_mips,"lw $t1 %d($gp)\n",symlist[loc_2].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t1 %d($sp)\n",symlist[loc_2].addr);
                }
            }
            fprintf(fp_mips,"sge $t2 $t0 $t1\n");
            fprintf(fp_mips,"bgtz $t2 %s\n",tmp_name3);
            break;
        }
        case CGTR:{
            loc_1 = table_search(tmp_name1);
            loc_2 = table_search(tmp_name2);
            if(symlist[loc_1].type==0){
                fprintf(fp_mips,"li $t0 %d\n",symlist[loc_1].addr);
            }
            else{
                if(symlist[loc_1].global==0){
                    fprintf(fp_mips,"lw $t0 %d($gp)\n",symlist[loc_1].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t0 %d($sp)\n",symlist[loc_1].addr);
                }
            }
            if(symlist[loc_2].type==0){
                fprintf(fp_mips,"li $t1 %d\n",symlist[loc_2].addr);
            }
            else{
                if(symlist[loc_2].global==0){
                    fprintf(fp_mips,"lw $t1 %d($gp)\n",symlist[loc_2].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t1 %d($sp)\n",symlist[loc_2].addr);
                }
            }
            fprintf(fp_mips,"sgt $t2 $t0 $t1\n");
            fprintf(fp_mips,"bgtz $t2 %s\n",tmp_name3);
            break;
        }
        case CLEQ:{
            loc_1 = table_search(tmp_name1);
            loc_2 = table_search(tmp_name2);
            if(symlist[loc_1].type==0){
                fprintf(fp_mips,"li $t0 %d\n",symlist[loc_1].addr);
            }
            else{
                if(symlist[loc_1].global==0){
                    fprintf(fp_mips,"lw $t0 %d($gp)\n",symlist[loc_1].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t0 %d($sp)\n",symlist[loc_1].addr);
                }
            }
            if(symlist[loc_2].type==0){
                fprintf(fp_mips,"li $t1 %d\n",symlist[loc_2].addr);
            }
            else{
                if(symlist[loc_2].global==0){
                    fprintf(fp_mips,"lw $t1 %d($gp)\n",symlist[loc_2].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t1 %d($sp)\n",symlist[loc_2].addr);
                }
            }
            fprintf(fp_mips,"sle $t2 $t0 $t1\n");
            fprintf(fp_mips,"bgtz $t2 %s\n",tmp_name3);
            break;
        }
        case CLSS:{
            loc_1 = table_search(tmp_name1);
            loc_2 = table_search(tmp_name2);
            if(symlist[loc_1].type==0){
                fprintf(fp_mips,"li $t0 %d\n",symlist[loc_1].addr);
            }
            else{
                if(symlist[loc_1].global==0){
                    fprintf(fp_mips,"lw $t0 %d($gp)\n",symlist[loc_1].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t0 %d($sp)\n",symlist[loc_1].addr);
                }
            }
            if(symlist[loc_2].type==0){
                fprintf(fp_mips,"li $t1 %d\n",symlist[loc_2].addr);
            }
            else{
                if(symlist[loc_2].global==0){
                    fprintf(fp_mips,"lw $t1 %d($gp)\n",symlist[loc_2].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t1 %d($sp)\n",symlist[loc_2].addr);
                }
            }
            fprintf(fp_mips,"slt $t2 $t0 $t1\n");
            fprintf(fp_mips,"bgtz $t2 %s\n",tmp_name3);
            break;
        }
        case CNEQ:{
            loc_1 = table_search(tmp_name1);
            loc_2 = table_search(tmp_name2);
            if(loc_1==-1){
                if(tmp_name1[0]=='\''){
                    fprintf(fp_mips,"li $t1 %d\n",(int)tmp_name1[1]);
                }
                else{
                    fprintf(fp_mips,"li $t1 %d\n",atoi(tmp_name1));
                }
            }
            else{
                if(symlist[loc_1].type==0){
                    fprintf(fp_mips,"li $t0 %d\n",symlist[loc_1].addr);
                }
                else{
                    if(symlist[loc_1].global==0){
                        fprintf(fp_mips,"lw $t0 %d($gp)\n",symlist[loc_1].addr);
                    }
                    else{
                        fprintf(fp_mips,"lw $t0 %d($sp)\n",symlist[loc_1].addr);
                    }
                }
            }
            if(loc_2==-1){
                if(tmp_name2[0]=='\''){
                    fprintf(fp_mips,"li $t1 %d\n",(int)tmp_name2[1]);
                }
                else{
                    fprintf(fp_mips,"li $t1 %d\n",atoi(tmp_name2));
                }
            }
            else{
                if(symlist[loc_2].type==0){
                    fprintf(fp_mips,"li $t1 %d\n",symlist[loc_2].addr);
                }
                else{
                    if(symlist[loc_2].global==0){
                        fprintf(fp_mips,"lw $t1 %d($gp)\n",symlist[loc_2].addr);
                    }
                    else{
                        fprintf(fp_mips,"lw $t1 %d($sp)\n",symlist[loc_2].addr);
                    }
                }
            }
            fprintf(fp_mips,"bne $t0 $t1 %s\n",tmp_name3);
            break;
        }
        case CJUMP:{
            fprintf(fp_mips,"j %s\n",tmp_name1);
            break;
        }
        case CASSIGN:{
            loc_1 = table_search(tmp_name1);
            loc_2 = table_search(tmp_name2);
            if(loc_2==-1){
                if(tmp_name2[0]=='\''){
                    fprintf(fp_mips,"li $t0 %d\n",(int)tmp_name2[1]);
                }
                else{
                    fprintf(fp_mips,"li $t0 %d\n",atoi(tmp_name2));
                }
            }
            else{
                if(symlist[loc_2].type==0){
                    fprintf(fp_mips,"li $t0 %d\n",symlist[loc_2].addr);
                }
                else{
                    if(symlist[loc_2].global==0){
                        fprintf(fp_mips,"lw $t0 %d($gp)\n",symlist[loc_2].addr);
                    }
                    else{
                        fprintf(fp_mips,"lw $t0 %d($sp)\n",symlist[loc_2].addr);
                    }
                }
            }
            if(symlist[loc_1].global==0){
                fprintf(fp_mips,"sw $t0 %d($gp)\n",symlist[loc_1].addr);
            }
            else{
                fprintf(fp_mips,"sw $t0 %d($sp)\n",symlist[loc_1].addr);
            }
            break;
        }
        case CPUSH:{
            loc_1 = table_search(tmp_name1);
            loc_2 = table_search(tmp_name2);
            int i = atoi(tmp_name3);
            fprintf(fp_mips,"subi $t0 $sp 4\n");
            fprintf(fp_mips,"subi $t0 $t0 %d\n",symlist[loc_2].addr);
            fprintf(fp_mips,"li $t1 %d\n",i);
            fprintf(fp_mips,"sll $t1 $t1 2\n");
            fprintf(fp_mips,"add $t0 $t0 $t1\n");
            if(symlist[loc_1].type==0){
                fprintf(fp_mips,"li $t2 %d\n",symlist[loc_1].addr);
            }
            else{
                if(symlist[loc_1].global==0){
                    fprintf(fp_mips,"lw $t2 %d($gp)\n",symlist[loc_1].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t2 %d($sp)\n",symlist[loc_1].addr);
                }
            }
            fprintf(fp_mips,"sw $t2 ($t0)\n");
            break;
        }
        case CCALL:{
            char fun_name[Max_ident+1]={"_F\0"};
            strcat(tmp_name1,fun_name);
            fprintf(fp_mips,"jal %s\n",tmp_name1);
            break;
        }
        case CRET:{
            loc_1 = table_search(tmp_name1);
            if(symlist[loc_1].type==0){
                fprintf(fp_mips,"li $t0 %d\n",symlist[loc_1].addr);
            }
            else{
                if(symlist[loc_1].global==0){
                    fprintf(fp_mips,"lw $t0 %d($gp)\n",symlist[loc_1].addr);
                }
                else{
                    fprintf(fp_mips,"lw $t0 %d($sp)\n",symlist[loc_1].addr);
                }
            }
            fprintf(fp_mips,"move $v0 $t0\n");
            fprintf(fp_mips,"jr $ra\n");
            break;
        }
        case CNRET:{
            if(inmflag==0){
                fprintf(fp_mips,"jr $ra\n");
            }
            else{
                fprintf(fp_mips,"j END\n");
            }
            break;
        }
        case CRETVAL:{
            loc_1 = table_search(tmp_name1);
            if(symlist[loc_1].global==0){
                fprintf(fp_mips,"sw $v0 %d($gp)\n",symlist[loc_1].addr);
            }
            else{
                fprintf(fp_mips,"sw $v0 %d($sp)\n",symlist[loc_1].addr);
            }
            break;
        }
        case CLABEL:{
            fprintf(fp_mips,"%s:\n",tmp_name1);
            break;
        }
        case CSCANF:{
            loc_1 = table_search(tmp_name1);
            if(symlist[loc_1].type_data==0){
                fprintf(fp_mips,"li $v0 5\n");
                fprintf(fp_mips,"syscall\n");
                if(symlist[loc_1].global==0){
                    fprintf(fp_mips,"sw $v0 %d($gp)\n",symlist[loc_1].addr);
                }
                else{
                    fprintf(fp_mips,"sw $v0 %d($sp)\n",symlist[loc_1].addr);
                }
            }
            else{
                fprintf(fp_mips,"li $v0 12\n");
                fprintf(fp_mips,"syscall\n");
                if(symlist[loc_1].global==0){
                    fprintf(fp_mips,"sw $v0 %d($gp)\n",symlist[loc_1].addr);
                }
                else{
                    fprintf(fp_mips,"sw $v0 %d($sp)\n",symlist[loc_1].addr);
                }
            }
            break;
        }
        case CPRINTF:{
            loc_1 = table_search(tmp_name1);
            if(symlist[loc_1].type_data==0){
                if(symlist[loc_1].type==0){
                    fprintf(fp_mips,"li $a0 %d\n",symlist[loc_1].addr);
                }
                else if(symlist[loc_1].global==0){
                    fprintf(fp_mips,"lw $a0 %d($gp)\n",symlist[loc_1].addr);
                }
                else{
                    fprintf(fp_mips,"lw $a0 %d($sp)\n",symlist[loc_1].addr);
                }
                fprintf(fp_mips,"li $v0 1\n");
                fprintf(fp_mips,"syscall\n");
            }
            else{
                if(symlist[loc_1].type==0){
                    fprintf(fp_mips,"li $a0 %d\n",symlist[loc_1].addr);
                }
                else if(symlist[loc_1].global==0){
                    fprintf(fp_mips,"lw $a0 %d($gp)\n",symlist[loc_1].addr);
                }
                else{
                    fprintf(fp_mips,"lw $a0 %d($sp)\n",symlist[loc_1].addr);
                }
                fprintf(fp_mips,"li $v0 11\n");
                fprintf(fp_mips,"syscall\n");
            }
            fprintf(fp_mips,"li $v0 11\n");
            fprintf(fp_mips,"li $a0 10\n");
            fprintf(fp_mips,"syscall\n");
            break;
        }
        case CPRINTF_ST:{
            fprintf(fp_mips,".data\nstring_%d:  .asciiz\"%s\"\n",string_num,four_code_list[mips_4code_loc].index_string);
            fprintf(fp_mips,".text\n");
            fprintf(fp_mips,"la $a0 string_%d\n",string_num);
            fprintf(fp_mips,"li $v0 4\n");
            fprintf(fp_mips,"syscall\n");
            string_num++;
            fprintf(fp_mips,"li $v0 11\n");
            fprintf(fp_mips,"li $a0 10\n");
            fprintf(fp_mips,"syscall\n");
            break;
        }
        case CPUSH_STACK:{
            loc_1 = table_search(tmp_name1);
            fprintf(fp_mips,"subi $sp $sp %d\n",symlist[loc_1].addr);
            break;
        }
        case CPULL_STACK:{
            loc_1 = table_search(tmp_name1);
            fprintf(fp_mips,"addi $sp $sp %d\n",symlist[loc_1].addr);
            break;
        }
        case CSAVE_ENV:{
            fprintf(fp_mips,"subi $sp $sp 4\n");
            fprintf(fp_mips,"sw $ra ($sp)\n");
            break;
        }
        case CREV_ENV:{
            fprintf(fp_mips,"lw $ra ($sp)\n");
            fprintf(fp_mips,"addi $sp $sp 4\n");
            break;
        }
        default:{
            fprintf(fp_mips,"wrong\n");
        }
    }
}
