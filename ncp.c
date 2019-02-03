



#include <stdio.h>
#include <stdlib.h>



int main( int argc, char *argv[])
{

   FILE *source, *target; int ch ; 
   source = fopen( argv[ 1 ], "r");
   if( source == NULL )
   {
      printf("Press any key to exit...\n");
      exit(EXIT_FAILURE);
   }
 
   target = fopen( argv[ 2 ] , "w");
   if( target == NULL )
   {
      fclose(source);
      printf("Press any key to exit...\n");
      exit(EXIT_FAILURE);
   }
 
   printf("Source: %s\n",  argv[ 1 ] );
   printf("Target: %s\n",  argv[ 2 ] );
   printf("Copying...\n");

   while( ( ch = fgetc(source) ) != EOF )
      fputc(ch, target);
 
   printf("File copied successfully.\n");
   fclose(source);
   fclose(target);
   return 0;
}





