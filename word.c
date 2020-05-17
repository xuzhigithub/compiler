#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "define.h"
#include "debug.h"

int word(){//返回值为-1说明文件已经读完了
    int i;
    int iskey;
    int issingle;
    /*if(line==36){
        printf("there");
    }*/
    if(input[loc]!='\0'){
        while(input[loc]==' '||input[loc]=='\t'||input[loc]=='\n'){
            if(input[loc]=='\n'){
                line++;
                column = 0;
            }
            else{
                column++;
            }
            loc++;
        }
        if((input[loc]>='a'&&input[loc]<='z')||(input[loc]>='A'&&input[loc]<='Z')||input[loc]=='_'){
            i=0;
            if(input[loc]<='Z'&&input[loc]>='A'){
                token[i]=input[loc]-'A'+'a';
            }
            else{
                token[i]=input[loc];
            }
            column++;
            loc++;
            while((input[loc]>='a'&&input[loc]<='z')||(input[loc]>='A'&&input[loc]<='Z')||(input[loc]<='9'&&input[loc]>='0')||input[loc]=='_'){
                if(input[loc]<='Z'&&input[loc]>='A'){
                    token[++i]=input[loc]-'A'+'a';
                }
                else{
                    token[++i]=input[loc];
                }
                if(i==(Max_ident+1)){
                    error(1);
                    debug_wprintf("%s %s\n",token,symbol[IDENT]);
                    debug_fprintf(fp_word,"%s %s\n",token,symbol[IDENT]);
                    return IDENT;
                }
                column++;
                loc++;
            }
            token[++i]='\0';
            //loc--;//回退一个字符
            iskey = searchkey(token);
            if(iskey==0){
                debug_wprintf("%s %s\n",token,symbol[IDENT]);
                debug_fprintf(fp_word,"%s %s\n",token,symbol[IDENT]);
            }//说明不是保留字
            else{
                return iskey;
            }
            return IDENT;
        }
        else if(input[loc]<='9'&&input[loc]>='0'){
            i=0;
            token_int=input[loc]-'0';
            column++;
            loc++;
            while(input[loc]<='9'&&input[loc]>='0'){
                if(token_int==0){
                    error(37);
                    return INTEGER;
                }
                if(token_int>=214748364||(token_int==214748364&&input[loc]-'0'>=6)){
                    error(2);
                    return INTEGER;
                }
                token_int = token_int*10+input[loc]-'0';
                column++;
                loc++;
            }
            if((input[loc]>='a'&&input[loc]<='z')||(input[loc]>='A'&&input[loc]<='Z')||(input[loc]<='9'&&input[loc]>='0')||input[loc]=='_'){
                error(28);
                return INTEGER;
            }
            //loc--;
            token[++i]='\0';
            debug_wprintf("%d %s\n",token_int,symbol[INTEGER]);
            debug_fprintf(fp_word,"%d %s\n",token_int,symbol[INTEGER]);
            return INTEGER;
        }
        else if((issingle=searchsingle(input[loc]))!=0){
            column++;
            loc++;
            return issingle;
        }
        else if(input[loc]=='<'){
            column++;
            loc++;
            if(input[loc]=='='){
                column++;
                loc++;
                debug_wprintf("<= %s\n",symbol[LEQ]);
                debug_fprintf(fp_word,"<= %s\n",symbol[LEQ]);
                return LEQ;
            }
            else{
                debug_wprintf("< %s\n",symbol[LSS]);
                debug_fprintf(fp_word,"< %s\n",symbol[LSS]);
                return LSS;
            }
        }
        else if(input[loc]=='>'){
            column++;
            loc++;
            if(input[loc]=='='){
                column++;
                loc++;
                debug_wprintf(">= %s\n",symbol[GEQ]);
                debug_fprintf(fp_word,">= %s\n",symbol[GEQ]);
                return GEQ;
            }
            else{
                debug_wprintf("> %s\n",symbol[GTR]);
                debug_fprintf(fp_word,"> %s\n",symbol[GTR]);
                return GTR;
            }
        }
        else if(input[loc]=='!'){
            column++;
            loc++;
            if(input[loc]=='='){
                column++;
                loc++;
                debug_wprintf("!= %s\n",symbol[NEQ]);
                debug_fprintf(fp_word,"!= %s\n",symbol[NEQ]);
                return NEQ;
            }
            else{
                debug_wprintf("!must have = after it");//there is an error
                debug_fprintf(fp_word,"!must have = after it");
            }
        }
        else if(input[loc]=='='){
            column++;
            loc++;
            if(input[loc]=='='){
                column++;
                loc++;
                debug_wprintf("== %s\n",symbol[EQL]);
                debug_fprintf(fp_word,"== %s\n",symbol[EQL]);
                return EQL;
            }
            else{
                debug_wprintf("= %s\n",symbol[ASSIGN]);
                debug_fprintf(fp_word,"= %s\n",symbol[ASSIGN]);
                return ASSIGN;
            }
        }
        else if(input[loc]=='\''){
            column++;
            loc++;
            if(!((input[loc]>='a'&&input[loc]<='z')||(input[loc]>='A'&&input[loc]<='Z')||
                (input[loc]<='9'&&input[loc]>='0')||
                input[loc]=='_'||input[loc]=='+'||input[loc]=='-'||input[loc]=='*'||input[loc]=='/'))
            {
                error(46);
            }
            token_char=input[loc];
            column++;
            loc++;
            if(input[loc]!='\''){
                debug_wprintf("'must have a ' after it");//there is an error
                debug_fprintf(fp_word,"'must have a ' after it");
            }
            else{
                loc++;
                debug_wprintf("'%c' %s\n",token_char,symbol[CHARACTER]);
                debug_fprintf(fp_word,"'%c' %s\n",token_char,symbol[CHARACTER]);
                return CHARACTER;
            }
        }
        else if(input[loc]=='"'){
            int temp = loc+1;
            int count=0;
            int i=0;
            while(input[temp]!='"'){
                if(input[temp]=='\0'){
                    debug_wprintf("there is end of file and can not find a \" after \"");//there is an error
                    debug_fprintf(fp_word,"there is end of file and can not find a \" after \"");
                    loc++;
                    break;;
                }
                if(input[temp]=='\\'){
                    count++;
                }
                temp++;
                count++;
            }
            token_string = (char*)malloc(sizeof(char)*(count+1));//这里一定要记得free
            if(count==0){
                column+=2;
                loc+=2;
                token_string[0]='\0';
                debug_wprintf("\"\" %s\n",symbol[STRING]);
                debug_fprintf(fp_word,"\"\" %s\n",symbol[STRING]);
                return STRING;
            }
            else{
                column++;
                loc++;
                for(i=0;i<count;i++){
                    token_string[i] = input[loc];
                    if(input[loc]=='\\'){
                        i++;
                        token_string[i] = '\\';
                    }
                    loc++;
                }
                column++;
                loc++;
                token_string[i]='\0';
                debug_wprintf("\"%s\" %s\n",token_string,symbol[STRING]);
                debug_fprintf(fp_word,"\"%s\" %s\n",token_string,symbol[STRING]);
                return  STRING;
            }
        }
        else if(input[loc]=='\0'){
            return -1;
        }
        else{
            column++;
            loc++;
            debug_wprintf("no such word\n");//there is an error
            debug_fprintf(fp_word,"no such word\n");
            return 0;
        }
    }
    else{
        return -1;
    }
    return 0;
}

void open_file(char **input){
    char *filename = (char*)malloc(100*sizeof(char));
    FILE *fp;
    int flen;
    int i=0;
    printf("please input your filename:");
    scanf("%s",filename);
    if((fp = fopen(filename,"r"))==NULL){
        printf("can not open target file!");
        exit(0);
    }
    fseek(fp,0,SEEK_END);
    flen = ftell(fp);//返回文件长度
    *input = (char*)malloc(sizeof(char)*(flen+1));
    fseek(fp,0,SEEK_SET);
    while(!feof(fp)){
        (*input)[i++]=fgetc(fp);
    }
    (*input)[i-1]='\0';
    fclose(fp);
    return;
}

int searchkey(char* token){
    int i;
    for(i=0;i<13;i++){
        if(strcmp(token,key[i])==0){
            debug_wprintf("%s %s\n",key[i],ksy[i]);
            debug_fprintf(fp_word,"%s %s\n",key[i],ksy[i]);
            return (i+1);//返回对应的类型码
        }
    }
    return 0;
}

int searchsingle(char c){
    int i;
    for(i=0;i<13;i++){
        if (c==single[i]){
            debug_wprintf("%c %s\n",c,singlesy[i]);
            debug_fprintf(fp_word,"%c %s\n",c,singlesy[i]);
            return (i+14);//返回对应的类型码
        }
    }
    return 0;
}
