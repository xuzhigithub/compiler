#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

//全局静态变量声明
#define Max_ident 30 //标识符最大长度
#define Max_table 300//符号表最大长度
#define Max_para  30//函数传参最大个数
#define Max_switch 100//case最大个数
#define Max_fourcode 1000//四元式最大长度
#define Max_block 100//最多能够有多少个基本块
#define Max_use 100//use集最大多大
#define Max_def 100//def集最大多大
#define Max_in 200//in集最大多大
#define Max_out 200//out集最大多大
#define Max_var 100//冲突图最多多少个变量

//全局变量声明
extern int line;//行号
extern int column;//列号
extern int loc;//当前读取到的位置
extern const char *key[13];//保留字表
extern const char *ksy[13];//保留字对应的助记符
extern const char *symbol[38];//助记符表
extern const char single[13];//单分界符表
extern const char* singlesy[13];//单分界符对应的助记符表
extern char* input;//文件读取存储的指针
extern int sym;//当前读入符号的类型码
extern char token[Max_ident+1];//词法分析传出的字符
extern char token_char;
extern int token_int;
extern char* token_string;//词法分析传出的字符串
extern FILE* fp_word;
extern FILE* fp_grammar;
extern FILE* fp_error;
extern FILE* fp_table;
extern FILE* fp_expr;
extern FILE* fp_four_code;
extern FILE* fp_dag_four_code;
extern FILE* fp_mips;
extern FILE* fp_dag;
extern FILE* fp_mips_dag;
extern FILE* fp_block;
extern FILE* fp_mips_flow;
extern int vflag;//判断是否出现了变量定义
extern int fflag;//判断是否出现了函数定义
extern int mflag;//判断是否出现了main函数定义
extern int infflag;//判断是不是在函数内部定义变量定义
extern int inmflag;//判断在不在main函数内部
extern int cflag;
extern const char *error_msg[49];//错误报错信息

/*单词符号表
单词符号    种别码     助记符
do          1           dosy
while       2           whilesy
switch      3           switchsy
case        4           casesy
if          5           ifsy
scanf       6           scanfsy
printf      7           printfsy
return      8           returnsy
const       9           constsy
char        10          charsy
int         11          intsy
main        12          mainsy
void        13          voidsy
*           14          time
/           15          div
+           16          plus
-           17          minus
,           18          comma
(           19          lbrack
)           20          rbrack
[           21          lsbrack
]           22          rsbrack
{           23          lbrace
}           24          rbrace
;           25          semicolon
:           26          colon
=           27          assign
<           28          lss
<=          29          leq
>           30          gtr
>=          31          geq
==          32          eql
!=          33          neq
标识符      34          ident
整数        35          integer
字符串      36          string
字符常量    37          character
*/

#define DOSY 1
#define WHILESY 2
#define SWITCHSY 3
#define CASESY 4
#define IFSY 5
#define SCANFSY 6
#define PRINTFSY 7
#define RETURNSY 8
#define CONSTSY 9
#define CHARSY 10
#define INTSY 11
#define MAINSY 12
#define VOIDSY 13
#define TIME 14
#define DIV 15
#define PLUS 16
#define MINUS 17
#define COMMA 18
#define LBRACK 19
#define RBRACK 20
#define LSBRACK 21
#define RSBRACK 22
#define LBRACE 23
#define RBRACE 24
#define SEMICOLON 25
#define COLON 26
#define ASSIGN 27
#define LSS 28
#define LEQ 29
#define GTR 30
#define GEQ 31
#define EQL 32
#define NEQ 33
#define IDENT 34
#define INTEGER 35
#define STRING 36
#define CHARACTER 37

//函数声明
void open_file(char **input);//打开并读取源文件
int searchkey(char* token);//判断是不是保留字
int searchsingle(char c);//判断是不是单分界符
int word();//词法分析程序

//语法分析程序
typedef struct cal{
    int type;//zero is int,one is char
    int con;//zero is constant,one is not constant
    int value;//if is constant,it store the constant value
    char name[Max_ident+1];//
}cal;
void program();
void constant_define();
void variable_define();
void function_define();
void main_define();
void com_statement();//复合语句
void statements();//语句列
void statement();//语句
void condition_if();
void condition_while();
cal expr();
cal term();
cal factor();
int constant_int_define();
int constant_char_define();

//错误处理程序
/*
错误输出                        种别码         说明
 ident is too long               1              标识符过长
 digit is too long               2              数字过长
 without semicolon               3              缺少分号
 without colon                   4              缺少冒号
 without lbrack                  5              缺少左小括号
 without rbrack                  6              缺少右小括号
 without lsbrack                 7              缺少左中括号
 without rsbrack                 8              缺少右中括号
 without lbrace                  9              缺少左大括号
 without rbrace                  10             缺少右大括号
 without compare                 11             缺少关系运算符
 without assign                  12             缺少等号
 without int                     13             缺少int
 without char                    14             缺少char
 without while                   15             缺少while
 without case                    16             缺少case
 without main                    17             缺少main函数
 constant have no value          18             未对常量赋初值
 variable have init value        19             定义变量的时候赋了初值
 repeat ident                    20             标识符定义重复
 undefined ident                 21             引用了未定义的标识符
 constant type wrong             22             常量定义左右类型不一致
 without ident                   23             此处应为标识符
 array index not int             24             数组下标不为整型
 variable define after function  25             变量定义出现在函数定义之后
 constant define after function  26             常量定义出现在函数定义之后
 define after main               27             main函数后还有内容
 wrong ident                     28             非法标识符
 no ret function be factor       29             无返回值函数作为因子
 no ret function return value    30             无返回值函数返回了一个值
 ret function no ret             31             有返回值函数无返回值
 ident is not function           32             该标识符不为函数标识符
 left is char and right is int   33             不能对char型变量赋int型值
 not variable can not change     34             非变量标识符无法进行赋值操作
 para num not fit                35             参数个数不匹配
 para type not fit               36             参数类型不匹配
 use zero as head                37             整型非零值第一位为0
 illegal character               38             非法字符
 ret type is wrong               39             函数返回值不对应
 there should not have plus or minus before zero 40 零前面不应该有正负号
 switch and case is not fit      41             switch 和 case 类型不对应
 there should have an integer    42             此处应为整型
 this is not an array            43             当前标识符不为数组
 not enough length               44             数组显式越界
 zero can not be dived           45             显式除零操作
 illegal character in ''         46             非法字符
 repeat case                     47             case后面的常量重复
 too much ident                  48             符号表越界
*/

void error(int error_type);

//符号表
typedef struct table{
    char name[Max_ident+1];
    int type;//
    int type_data;
    int global;
    int aindex;
    int addr;
    int after_dag;//存储dag过后的函数大小
    int para;
    int para_table[Max_para];
    int haves;//是否分配到了全局寄存器
    int snum;//分配到的全局寄存器编号
}table;

extern table symlist[Max_table];//符号表
extern int table_index;//分程序索引，因为我们只有一层嵌套，因此不需要开辟一个数组
extern int loc_table;//当前符号表最后一个符号的位置
void table_insert();
int table_search(char *dest);
void table_delete();
extern char tmp_name[Max_ident+1];
extern int tmp_type;
extern int tmp_type_data;
extern int tmp_global;
extern int tmp_aindex;
extern int tmp_addr;
extern int tmp_para;
extern int tmp_para_table[Max_para];

//语义分析
extern int funflag;//zero is not in function,void is one,int is two,char is three
extern int haveret;
/*
type
zero is constant,one is variable, two is function

type_data
zero is int, one is char,two is int array,three is char array,four is void

global
zero is global,else is not global

aindex
store size of the array

addr
if is constant int,it store the value of the int,if it is a constant char,it store the ascii of the constant char,if it is a valuable,
it store the relative location in function,if it is a string, it store the begin location of the string,if it is a global variable,it store
the location in $gp

para
it store the number of the parameter of the function,if it is not a function,it store -1
*/

//中间代码格式及含义
/*
中间代码编号             参数个数             含义              助记符
0                        0                    nop               CPASS
1                        3                    a=b+c             CADD
2                        3                    a=b-c             CMINUS
3                        3                    a=b*c             CTIME
4                        3                    a=b/c             CDIV
5                        3                    a=b[c]            CARRVAL
6                        3                    a[b]=c            CARRASN
7                        3                    a==b?->c          CEQL
8                        3                    a>=b?->c          CGEQ
9                        3                    a>b?->c           CGTR
10                       3                    a<=b?->c          CLEQ
11                       3                    a<b?->c           CLSS
12                       3                    a!=b?->c          CNEQ
13                       1                    ->a               CJUMP
14                       2                    a=b               CASSIGN
15                       1                    a->stack          CPUSH
16                       1                    a(...)            CCALL
17                       1                    return(a)         CRET
18                       0                    return            CNRET
19                       2                    a=b()             CRETVAL
20                       1                    a:                CLABEL
21                       1                    scanf(a)          CSCANF
22                       1                    printf(a)         CPRINTF
23                       0                    printf(string)    CPRINTF_ST
24                       1                    sp+=sizeof(a)     CPUSH_STACK
25                       1                    sp-=sizeof(a)     CPULL_STACK
26                       0                    save environment  CSAVE_ENV
27                       0                    recover environment CREV_ENV
*/
#define CPASS 0
#define CADD 1
#define CMINUS 2
#define CTIME 3
#define CDIV 4
#define CARRVAL 5
#define CARRASN 6
#define CEQL 7
#define CGEQ 8
#define CGTR 9
#define CLEQ 10
#define CLSS 11
#define CNEQ 12
#define CJUMP 13
#define CASSIGN 14
#define CPUSH 15
#define CCALL 16
#define CRET 17
#define CNRET 18
#define CRETVAL 19
#define CLABEL 20
#define CSCANF 21
#define CPRINTF 22
#define CPRINTF_ST 23
#define CPUSH_STACK 24
#define CPULL_STACK 25
#define CSAVE_ENV 26
#define CREV_ENV 27
typedef struct four_code{
    int code;
    char para_1[Max_ident+1];
    char para_2[Max_ident+2];
    char para_3[Max_ident+3];
    char *index_string;
}four_code;

extern four_code four_code_list[Max_fourcode];
extern int four_code_index;
extern int label_index;
extern char four_code_para[3][Max_ident+1];
extern int val_index;//中间变量
extern char val_name[Max_ident+1];
extern char val_num[15];
extern char label_name[Max_ident+1];
extern char label_num[15];
extern int string_num;

void pro_name();
void pro_label();
void insert_four_code(int code);
void print_four_code();

//目标代码生成
extern int global_loc;
extern int local_loc;
extern int mips_4code_loc;
void mips();

//优化
typedef struct dag{
    char name[Max_ident+1];
    int type;//zero is int , one is char
    int left;//left son in daglist
    int right;//right son in daglist
    int loc;//self in daglist
    int operate;
    //minus one is leaf,zero is add,one is minus,two is time,three is div,four is arrval,five is arrasn,six is assign,seven is scanf,eight is printf,nine is printf_st,ten is retval
    int con;//if is zero,it is constant
    int value;//if con==0,it store the value
    char *token_string;
}dag;
extern int dag_4code;//上一次局部优化在原四元式中结束的位置
extern int four_code_index_improve;
extern four_code four_code_list_improve[Max_fourcode];//优化后的四元式
extern char four_code_para_improve[3][Max_ident+1];
extern int val_index_improve;//中间变量
extern char val_name_improve[Max_ident+1];
extern char val_num_improve[15];
extern dag daggraph[Max_table];
extern int dag_index;
extern char dag_name[Max_ident+1];
extern int dag_type;
extern int dag_left;
extern int dag_right;
extern int dag_loc;
extern int dag_operate;
extern int dag_con;
extern int dag_value;
extern int dag_count;//用于dag图分配新节点给出节点编号
extern int dag_val_index;
extern char dag_val_name[Max_ident+1];
extern char dag_val_num[15];
extern char dag_pointname[Max_table][Max_ident+1];
extern char* dag_string;
extern int point_index;
extern int dag_printorder[Max_table];
extern int dag_printorder_index;
extern int last_index;
extern int push_list[Max_para];
extern int push_index;
extern char push_function[Max_ident+1];
extern int last_array;
int array_order[Max_table];
void dag_improve();
int dag_insert();
void dag_delete();
void dag_export();
void push_print();
void insert_four_code_dag(int code);
void print_four_code_dag();
//dag图生成mips
extern int mips_4code_dag_loc;
extern char temp_store[Max_table][Max_ident+1];
extern int temp_store_index;
extern int temp_max;
extern int temp_last;
void mips_dag();
void find_tmp_store();

typedef struct block{
    int begin_block;
    int end_block;
    int next_block[2];
    char use[Max_use+1][Max_ident+1];
    char def[Max_def+1][Max_ident+1];
    int use_index;
    int def_index;
    char in[Max_in+1][Max_ident+1];
    char out[Max_out+1][Max_ident+1];
    int in_index;
    int out_index;
}block;
extern int four_code_index_flow;
extern int flow_dag;
extern int mips_4code_flow_loc;
extern block block_list[Max_block+1];
extern int block_index;
extern char var_block[Max_var][Max_ident+1];
extern int var_graph[Max_var][Max_var];
extern int var_count;
void flow();
void flow_init();
void find_block();
void findblocknext();
void findinout();
void findvarblock();
void findconflict();
void allotregister();
char sregister[8][Max_ident+1];
char tregister[10][Max_ident+1];
int tregister_index;
int mips_4code_flow_loc;
int not_in_set(char* name,char set_list[][Max_ident+1],int set_index);
int cal_out(char set1[][Max_ident+1],char set2[][Max_ident+1],
            char (*tarset)[Max_ident+1],int set1_index,int set2_index);
int cal_in(char set1[][Max_ident+1],char set2[][Max_ident+1],char set3[][Max_ident+1],
            char (*tarset)[Max_ident+1],int set1_index,int set2_index,int set3_index);
void mips_flow();

#endif // DEFINE_H_INCLUDED
