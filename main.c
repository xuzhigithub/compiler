#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "debug.h"

int main()
{
    fp_grammar = fopen("grammar.txt","w");
    fp_word = fopen("word.txt","w");
    fp_error = fopen("error.txt","w");
    fp_table = fopen("table.txt","w");
    fp_expr = fopen("expr.txt","w");
    fp_four_code = fopen("four_code.txt","w");
    fp_dag_four_code = fopen("dag_four_code.txt","w");
    fp_mips = fopen("mips.txt","w");
    fp_dag = fopen("dag.txt","w");
    fp_mips_dag = fopen("mips_dag.txt","w");
    fp_block = fopen("block.txt","w");
    fp_mips_flow = fopen("mips_flow.txt","w");
    fprintf(fp_mips,".text\nj main\n");
    fprintf(fp_mips_dag,".text\nj main\n");
    fprintf(fp_mips_flow,".text\nj main\n");
    open_file(&input);
    //debug_printf("%s",input);
    //while((sym=word())!=-1);
    sym = word();
    program();
    fprintf(fp_mips,"END:\n");
    fprintf(fp_mips_dag,"END:\n");
    fprintf(fp_mips_flow,"END:\n");
    print_four_code();
    print_four_code_dag();
    fclose(fp_word);
    fclose(fp_grammar);
    fclose(fp_error);
    fclose(fp_table);
    fclose(fp_expr);
    fclose(fp_four_code);
    fclose(fp_dag_four_code);
    fclose(fp_mips);
    fclose(fp_mips_dag);
    fclose(fp_dag);
    fclose(fp_block);
    fclose(fp_mips_flow);
    return 0;
}
