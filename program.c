#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main (int argc, char *argv[])
{
  int fd;
  char ptr;
  char nazwa[20];
  int plik ;
  void* wsk ;
  struct stat sfile;
  size_t rozmiar;
  int pid;
  fd = open("Plik_map.mm",O_RDWR | O_CREAT);

  if(pid = fork() != 0)
    {

      while(nazwa!="q")
	{
	  printf("Podaj nazwe pliku\n");
	  scanf("%s",&nazwa);
	  if(nazwa == "q")
	    {
	      exit(1);
	      return 0;
	    } 
	  stat(nazwa, &sfile);
	  rozmiar = sfile.st_size;
	  ftruncate(fd,rozmiar);
	       
	  wsk = mmap(NULL,rozmiar,PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);
	  plik = open(nazwa,O_RDONLY);

	  if(plik > 0)
	    {
	      read(plik,wsk,rozmiar);	     
	      close(plik);
	      
	      write(fd,wsk,rozmiar);
	      msync(wsk,rozmiar,MS_SYNC);
	    }
	  else
	    printf("Nie ma pliku %s!!!\n",nazwa);
	}  
    }
  if(pid == 0) {
 
    execlp("display","display","-update", "1","Plik_map.mm",(char *)NULL);

  }
  close(fd);
  return 0;
}




