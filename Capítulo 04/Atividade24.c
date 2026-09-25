//Contexto: Além do relatório legível, o jogo precisa de um formato direto para restaurar registros sem interpretar linhas de texto. Um quivo binário pode armazenar a estrutura persistente de cada partida.
//Descrição detalhada: Acrescente rotinas que gravem e leiam uma estrutura de partida com fwrite e fread. Compare o registro restaurado com o original e trate leituras incompletas. Caso a estrutura venha a conter ponteiros, eles não deverão ser persistidos como endereços.
//Requisitos:
//- usar os modos wb e rb;
//- calcular tamanhos com sizeof;
//- conferir a quantidade escrita e lida;
//- gravar somente campos que façam sentido após reiniciar o programa;
//- detectar arquivo vazio ou registro incompleto;
//- exibir o objeto reconstruído.


#include <stdio.h>
#include <stdio.h>

int main (){
    FILE * file= fopen ("Números.b", "rb");
    int a;
    while (fread (&a, sizeof (int), 2, file));
      printf ("%d\n", a);
 fclose (file);
 return 0;
}