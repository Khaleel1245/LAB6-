#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

typedef void MYFUNC(char *bpath,char indent[10000]);
int checkDir(const char* fpath)
{
    struct stat path;

    stat(fpath, &path);

    return S_ISREG(path.st_mode);
}

void  opfunc(char *bpath,char indent[1000],MYFUNC *c){

            c(bpath,indent);

}


int main(int argc, char const *argv[])
{
    // it display the data in location
    void displayList(char *loc,char *s);
    void displayListWithSize(char *loc,char *s);
    void displayListWithExt(char *loc,char ext[100],int level,char*s);
    void  displayListWithExtFilter(char *loc,char ext[100],int level,int bytes,char *s);
    char fun1[100];

    int S=0;
    int s=0;
    int bytes=0;
    int f=0;
    char ext[100];
    char path[100]=".";
    int level;
    // Here is the path

    for(int i=1; i<argc; i++)
    {
        if(strcmp(argv[i],"-S") ==0)
        {
            S=1;
        }
        else if(strcmp(argv[i],"-s") == 0)
        {
             s = 1;
             bytes = atoi(argv[++i]);
        }
        else if(strcmp(argv[i],"-f") == 0)
        {
           f=1;
           strcpy(ext,argv[++i]);
           level = atoi(argv[++i]);
           
        }
        else {
            strcpy(path,argv[i]);
        }

    }
   // printf("\nThe path is %s \n",path);
    if(S==0)
    {
          if(s!=0 && f!=0)
          {
              displayListWithExtFilter(path,ext,level,bytes,"");
          }
          else if(s!=0)
          {
             displayListWithFilter(path,bytes,"");
          }
          else if(f!=0)
          {
              printf("\nDisplay list with ext\n");
             displayListWithExt(path,ext,level,"");
          }
          else 
          {
            opfunc(path,"",displayList);
          }
    }
    else 
    {
 if(s!=0 && f!=0)
          {
              
          }
          else if(s!=0)
          {

          }
          else if(f!=0)
          {

          }
          else 
          {
            opfunc(path,"",displayListWithSize);
          }
    }
    

    return 0;
}

void displayList(char *bpath,char indent[1000])
{

      char path[1000];

      struct dirent *d;

      DIR *dir = opendir(bpath);
      if(!dir)
      {
          return;
      }

      char ind[1000];
      strcpy(ind,indent);

      while((d = readdir(dir)) != NULL)
      {
          if(strcmp(d->d_name,".") != 0 && strcmp(d->d_name,"..") != 0)
          {

              printf("%s%s\n",indent,d->d_name);
             
              strcpy(path,bpath);
              strcat(path,"/");
              strcat(path,d->d_name);
              
              if(checkDir(path)==0)
              {
              strcat(ind,"   ");
              displayList(path,ind);
              }

              
          }
      }

      closedir(dir);

}
 void  displayListWithExtFilter(char *bpath,char ext[100],int level,int bytes,char indent[1000])
 {

     char path[1000];

      struct dirent *d;

      DIR *dir = opendir(bpath);
      if(!dir)
      {
          return;
      }

      char ind[1000];
      strcpy(ind,indent);

        struct stat st;
    
       

      while((d = readdir(dir)) != NULL)
      {
          if(strcmp(d->d_name,".") != 0 && strcmp(d->d_name,"..") != 0)
          {

              stat(d->d_name, &st);
              off_t size = st.st_size;
             if(size>= bytes)
             {
                  char *ex = strrchr(d->d_name, '.');
               
              if(ex!=NULL) 
              {
                   if(strcmp(ex+1,ext) == 0)
                   printf("%s\n",d->d_name);
             
              }
             }
              strcpy(path,bpath);
              strcat(path,"/");
              strcat(path,d->d_name);
              
              if(checkDir(path)==0)
              {
              strcat(ind,"   ");
            
               displayListWithExtFilter(path,ext,level,bytes,ind);
              }

              
          }
      }

      closedir(dir);

}

void displayListWithFilter(char *bpath,int bytes ,char indent[1000])
{

      char path[1000];

      struct dirent *d;

      DIR *dir = opendir(bpath);
      if(!dir)
      {
          return;
      }

      char ind[1000];
      strcpy(ind,indent);

        struct stat st;
    
       

      while((d = readdir(dir)) != NULL)
      {
          if(strcmp(d->d_name,".") != 0 && strcmp(d->d_name,"..") != 0)
          {

              stat(d->d_name, &st);
              off_t size = st.st_size;
             if(size>= bytes)
              printf("%s%s\n",indent,d->d_name);
             
              strcpy(path,bpath);
              strcat(path,"/");
              strcat(path,d->d_name);
              
              if(checkDir(path)==0)
              {
              strcat(ind,"   ");
            
               displayListWithFilter(path,bytes,ind);
              }

              
          }
      }

      closedir(dir);

}

void displayListWithExt(char *bpath,char ext[100],int level ,char indent[1000])
{

      char path[1000];

      struct dirent *d;

      DIR *dir = opendir(bpath);
      if(!dir)
      {
          return;
      }

      char ind[1000];
      strcpy(ind,indent);

       struct stat st;
    
       

      while((d = readdir(dir)) != NULL)
      {
          if(strcmp(d->d_name,".") != 0 && strcmp(d->d_name,"..") != 0)
          {

            char *ex = strrchr(d->d_name, '.');
               
              if(ex!=NULL) 
              {
                if(strcmp(ex+1,ext) == 0)
                   printf("%s\n",d->d_name);
              }
              strcpy(path,bpath);
              strcat(path,"/");
              strcat(path,d->d_name);
              
              if(checkDir(path)==0)
              {
              strcat(ind,"   ");
            
               displayListWithExt(path,ext,level,ind);
              }

              
          }
      }

      closedir(dir);

}


void displayListWithSize(char *bpath,char indent[1000])
{

      char path[1000];

      struct dirent *d;

      DIR *dir = opendir(bpath);
      if(!dir)
      {
          return;
      }

      char ind[1000];
      strcpy(ind,indent);

      struct stat st;
    
   
      while((d = readdir(dir)) != NULL)
      {
          if(strcmp(d->d_name,".") != 0 && strcmp(d->d_name,"..") != 0)
          {
              stat(d->d_name, &st);
              off_t size = st.st_size;
              printf("%s%s(%d,%X,%d)\n",indent,d->d_name,size,st.st_mode,(st.st_mtime));
                           
              strcpy(path,bpath);
              strcat(path,"/");
              strcat(path,d->d_name);
              
              if(checkDir(path)==0)
              {
              strcat(ind,"   ");
              displayListWithSize(path,ind);
              }

              
          }
      }

      closedir(dir);

}







