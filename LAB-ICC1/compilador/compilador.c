/*---------------------------------------------------------------------- 
                       Universidade de São Paulo
       Instituto de Ciências Matemáticas e de Computação - ICMC
                Departamento de Ciências de Computação - SCC
                SCC0221 - Introdução a Ciência de Computação 1
                   Nome: Vitor da Silveira Paula - 10689651           
---------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>


void fazerArquivo();


int main() {
   
   fazerArquivo();

   system("gcc jitGerado.c -o jit-exe");
   system("./jit-exe");

   return 0;
}

void fazerArquivo() {
   char caractere = '\0';
   FILE *arquivo = NULL;
   arquivo = fopen("jitGerado.c", "w");

   fprintf(arquivo, "#include <stdio.h>\n");
   fprintf(arquivo, "#include <stdlib.h>\n");
   fprintf(arquivo, "int main() {\n");
   fprintf(arquivo, "\tchar mensagem[30000];\n");
   fprintf(arquivo, "\tfor (int i = 0; i < 30000; i++)\n");
   fprintf(arquivo, "\t\tmensagem[i] = 0;\n");
   fprintf(arquivo, "\tint i = 0;\n");


   do {
      caractere = getchar();
      switch (caractere) {
         case '+':
            fprintf(arquivo, "\tmensagem[i]++;\n");
            break;
         case '-':
            fprintf(arquivo, "\tmensagem[i]--;\n");
            break;
         case '>':
            fprintf(arquivo, "\ti++;\n");
            break;
         case '<':
            fprintf(arquivo, "\ti--;\n");
            break;
         case '.':
            fprintf(arquivo, "\tprintf(\"%%c\", mensagem[i]);\n");
            break;
         case '[':
            fprintf(arquivo, "\twhile (mensagem[i]) {\n");
            break;
         case ']':
            fprintf(arquivo, "\t}\n");
            break;
      }

   } while(caractere != EOF);

   fprintf(arquivo, "\tprintf(\"\\n\");\n");
   fprintf(arquivo, "\tfor (int i = 0; i < 30000; i++) {\n");
   fprintf(arquivo,"\tif (mensagem[i] != 0)\n");
   fprintf(arquivo, "\t\tprintf(\"%%d \", mensagem[i]);\n");
   fprintf(arquivo, "\t}\n");
   fprintf(arquivo, "\tprintf(\"\\n\");\n");
   fprintf(arquivo, "\n\treturn 0;\n");
   fprintf(arquivo, "}\n");

   fclose(arquivo);

}
