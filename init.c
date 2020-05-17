#include<stdio.h>
#include<stdlib.h>
#include"define.h"
/*
该文件用于给全局静态变量赋初值
*/
int loc = 0;
int line=1;
int column=0;
const char *key[13]={"do","while","switch","case","if","scanf","printf","return","const","char","int","main","void"};
const char *symbol[38]={"","dosy","whilesy","switchsy","casesy","ifsy","scanfsy","printfsy","returnsy","constsy","charsy","intsy","mainsy","voidsy",
                        "time","div","plus","minus","comma","lbrack","rbrack","lsbrack","rsbrack","lbrace","rbrace","semicolon","colon",
                        "assign","lss","leq","gtr","geq","eql","neq","ident","integer","string","character"};
const char *ksy[13] = {"dosy","whilesy","switchsy","casesy","ifsy","scanfsy","printfsy","returnsy","constsy","charsy","intsy","mainsy","voidsy"};
const char single[13]={'*','/','+','-',',','(',')','[',']','{','}',';',':'};
const char *singlesy[13]={"time","div","plus","minus","comma","lbrack","rbrack","lsbrack","rsbrack","lbrace","rbrace","semicolon","colon"};
char* input=NULL;
char token[Max_ident+1]={'\0'};
char token_char = '\0';
int token_int = 0;
char *token_string = NULL;
FILE* fp_grammar=NULL;
FILE* fp_word=NULL;
FILE* fp_error=NULL;
FILE* fp_table = NULL;
FILE* fp_expr = NULL;
FILE* fp_four_code = NULL;
FILE* fp_mips = NULL;
FILE* fp_dag_four_code=NULL;
FILE* fp_dag = NULL;
FILE* fp_mips_dag = NULL;
FILE* fp_block = NULL;
FILE* fp_mips_flow = NULL;
int sym=0;
int vflag = 0;
int fflag = 0;
int mflag = 0;
int infflag = 0;
int inmflag = 0;
int cflag = 0 ;
const char *error_msg[49]={"","ident is too long","digit is too long","without semicolon","without colon","without lbrack","without rbrack",
                           "without lsbrack","without rsbrack","without lbrace","without rbrace","without compare","without assign",
                           "without int","without char","without while","without case","without main","constant have no value","variable have init value",
                           "repeat ident","undefined ident","constant type wrong","without ident","array index not int","variable define after function",
                           "constant define after function","main must be the last","wrong ident","no ret function be factor","no ret function return value",
                           "ret function no ret","ident is not function","left is char and right is int","not variable can not change","para num not fit","para type not fit","use zero as head",
                           "illegal character","ret type is wrong","there should not have plus or minus before zero","switch and case is not fit","there should have an integer","this is not an array",
                           "not enough length","zero can not be dived","illegal character in ''","repeat case","too much ident"};
table symlist[Max_table] ;
int loc_table = 0;
int table_index=0;
char tmp_name[Max_ident+1]={'\0'};
int tmp_type=0;
int tmp_type_data=0;
int tmp_global = 0;
int tmp_aindex=0;
int tmp_addr=0;
int tmp_para=0;
int tmp_para_table[Max_para]={0};
int funflag=0;
int haveret=0;

four_code four_code_list[Max_fourcode];
char four_code_para[3][Max_ident+1];
int four_code_index=0;
int label_index=0;
int val_index = 0;
char val_name[Max_ident+1]={'\0'};
char val_num[15]={'\0'};
char label_name[Max_ident+1]={'\0'};
char label_num[15]={'\0'};
int string_num=0;
int global_loc = 0;
int local_loc = 0;
int mips_4code_loc=0;

int dag_4code=0;
int four_code_index_improve=0;
four_code four_code_list_improve[Max_fourcode];
char four_code_para_improve[3][Max_ident+1];
int val_index_improve=0;
char val_name_improve[Max_ident+1]={'\0'};
char val_num_improve[15]={'\0'};
dag daggraph[Max_table];
int dag_index=0;
char dag_name[Max_ident+1]={'\0'};
int dag_type=0;
int dag_left=0;
int dag_right=0;
int dag_loc=0;
int dag_operate=0;
int dag_con=0;
int dag_value=0;
char* dag_string=NULL;
int dag_count=0;
int dag_val_index=0;
char dag_val_name[Max_ident+1]={'\0'};
char dag_val_num[15]={'\0'};
char dag_pointname[Max_table][Max_ident+1]={{'\0'}};
int point_index=0;
int dag_printorder[Max_table]={0};
int dag_printorder_index=0;
int last_index=0;
int push_list[Max_para]={0};
int push_index=0;
char push_function[Max_ident+1]={'\0'};
int mips_4code_dag_loc=0;
int last_array=0;
int array_order[Max_table] = {0};
char temp_store[Max_table][Max_ident+1];
int temp_store_index;
int temp_max;
int temp_last;

int four_code_index_flow=0;
int flow_dag=0;
int mips_4code_flow_loc=0;
block block_list[Max_block+1];
int block_index=0;
char var_block[Max_var][Max_ident+1];
int var_graph[Max_var][Max_var];
int var_count=0;
char sregister[8][Max_ident+1];
char tregister[10][Max_ident+1];
int tregister_index;
