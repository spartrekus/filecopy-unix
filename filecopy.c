#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h> 
#include <time.h>


/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
int fexist(char *a_option)
{
  char dir1[PATH_MAX]; 
  char *dir2;
  DIR *dip;
  strncpy( dir1 , "",  PATH_MAX  );
  strncpy( dir1 , a_option,  PATH_MAX  );

  struct stat st_buf; 
  int status; 
  int fileordir = 0 ; 

  status = stat ( dir1 , &st_buf);
  if (status != 0) {
    fileordir = 0;
  }

  // this is compatible to check if a file exists
  FILE *fp2check = fopen( dir1  ,"r");
  if( fp2check ) {
  // exists
  fileordir = 1; 
  fclose(fp2check);
  } 

  if (S_ISDIR (st_buf.st_mode)) {
    fileordir = 2; 
  }
return fileordir;
/////////////////////////////
}









long totalfilesize = 0;

void fseek_filesize(const char *filename)
{
    FILE *fp = NULL;
    long off;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("failed to fopen %s\n", filename);
        exit(EXIT_FAILURE);
    }

    if (fseek(fp, 0, SEEK_END) == -1)
    {
        printf("failed to fseek %s\n", filename);
        exit(EXIT_FAILURE);
    }

    off = ftell(fp);
    if (off == (long)-1)
    {
        printf("failed to ftell %s\n", filename);
        exit(EXIT_FAILURE);
    }

    //printf("[*] fseek_filesize - file: %s, size: %ld\n", filename, off);
    printf("%ld\n", off);
    totalfilesize = off; 

    if (fclose(fp) != 0)
    {
        printf("failed to fclose %s\n", filename);
        exit(EXIT_FAILURE);
    }
}



//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
void fstat_filesize(const char *filename)
{
    int fd;
    struct stat statbuf;

    fd = open(filename, O_RDONLY, S_IRUSR | S_IRGRP);
    if (fd == -1)
    {
        printf("failed to open %s\n", filename);
        exit(EXIT_FAILURE);
    }

    if (fstat(fd, &statbuf) == -1)
    {
        printf("failed to fstat %s\n", filename);
        exit(EXIT_FAILURE);
    }

    //printf("[*] fstat_filesize - file: %s, size: %lld\n", filename, statbuf.st_size);
    printf("%lld\n", statbuf.st_size);

    if (close(fd) == -1)
    {
        printf("failed to fclose %s\n", filename);
        exit(EXIT_FAILURE);
    }
}

void
stat_filesize(const char *filename)
{
    struct stat statbuf;

    if (stat(filename, &statbuf) == -1)
    {
        printf("failed to stat %s\n", filename);
        exit(EXIT_FAILURE);
    }

    //printf("[*] stat_filesize - file: %s, size: %lld\n", filename, statbuf.st_size);
    printf("%lld\n", statbuf.st_size);
}




void
seek_filesize(const char *filename)
{
    int fd;
    off_t off;

    if (filename == NULL)
    {
        printf("invalid filename\n");
        exit(EXIT_FAILURE);
    }

    fd = open(filename, O_RDONLY, S_IRUSR | S_IRGRP);
    if (fd == -1)
    {
        printf("failed to open %s\n", filename);
        exit(EXIT_FAILURE);
    }

    off = lseek(fd, 0, SEEK_END);
    if (off == (off_t)-1)
    {
        printf("failed to lseek %s\n", filename);
        exit(EXIT_FAILURE);
    }

    printf("[*] seek_filesize - file: %s, size: %lld\n", filename, off);

    if (close(fd) == -1)
    {
        printf("failed to close %s\n", filename);
        exit(EXIT_FAILURE);
    }
}








//////////////////
void ncpdisplay( char *filetarget,  char *filesource )
{
  /// new
  long copypos = -1;
  // fread
  char            buffer[1];
  size_t          n;
  size_t          m;
  FILE *fp;
  FILE *fp1; 
  FILE *fp2;
  int counter = 0 ; 
  int freader = 1 ; 
  int i , j ,posy, posx ; 
  if ( fexist( filesource ) == 1 )
  {
        fp = fopen( filesource, "rb");
        fp2 = fopen( filetarget, "wb");
        counter = 0; 
        while(  !feof(fp) && ( freader == 1)   ) {
           if (  feof(fp)   ) 
           {
                freader = 0 ; 
           }
           n = fread(  buffer, sizeof(char), 1 , fp);
           m = fwrite( buffer, sizeof(char), 1,  fp2);
           copypos++;
           printf("Copying byte: [%ld/%ld]", copypos, totalfilesize );
           printf("\r");
        }
        fclose(fp2);
        fclose(fp);
      }
      printf("\n");
}








///jint main(int argc, const char *argv[])
int main(int argc, char *argv[])
{
    char cwd[PATH_MAX]; int i ; 

    ////////////////////////////////////////////////////////
    if ( argc >= 2)
    if ( strcmp(argv[1], "--arg" ) == 0)
    {
          for( i = 1 ; i < argc ; i++) 
	     printf( "%d/%d: %s\n", i, argc-1 ,  argv[ i] );
          return 0;
    }

    if (argc < 2)
    {
        printf("%s <file1> <file2>...\n", argv[0]);
        exit(0);
    }

    for(i = 1; i < argc; i++)
    {
        //seek_filesize(argv[i]);
        //stat_filesize(argv[i]);
        //fstat_filesize(argv[i]);
        //fseek_filesize(argv[i]);
    }

    if (argc >= 2)
    if ( fexist( argv[1] ) == 1 )
    {
         printf( "Filesize: %s => ", argv[1]);
         fseek_filesize(argv[1]);
    }

    if (argc >= 2)
    if (argc == 3)
    {
       printf( "Source: %s\n", argv[1]);
       printf( "Target: %s\n", argv[2]);
       ncpdisplay( argv[2], argv[1] );
    }

    return 0;
}



