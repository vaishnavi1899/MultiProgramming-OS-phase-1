#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
char M[100][4],IR[4],R[4],t[41];
bool c;
int IC,SI,B,B2;
FILE *fr,*fw;
int main()
{
    int i,j;
  fr=fopen("input_Phase1.txt","r");
  fw=fopen("output_Phase1.txt","w");
  if(fr==NULL)
     printf("File not found");
  else
  {
  load();
  }
  printf("Operation completed");

  return 0;
}
void init()
{
    for(int i=0;i<100;i++)
    {
        for(int j=0;j<4;j++)
        {
            M[i][j]=' ';
        }
    }
    IR[0]=' ';
    R[0]=' ';
    c=false;
    B=0;
    B2=B+10;
}
void mos()
{
  switch(SI)
  {
  case 1:
      read();
      SI=0;
      break;
  case 2:
      write();
      SI=0;
      break;
  case 3:
      terminate();
      SI=0;
      break;
  }
}
void read()
{
    for(int i=0;i<41;i++)
        t[i]='\0';
     fgets(t,41,fr);
    int k=0;
    int i=IR[2]-'0';
    i=i*10;
    for(int l=0;l<10;l++)
    {
        for(int j=0;j<4;j++)
        {
            M[i][j]=t[k];
            k++;
        }
        if(k==41)
        {
            break;
        }
        i++;

    }


}
void write()
{
    for(int i=0;i<41;i++)
     t[i]='\0';
     int k=0;
     int i=IR[2]-'0';
     i=i*10;
      for(int l=0;l<10;l++)
      {
          for(int j=0;j<4;j++)
          {
              t[k]=M[i][j];
              fputc(t[k],fw);
              k++;
          }
          if(k==41)
          {
              break;
          }
          i++;
      }

      fputc('\n',fw);
}
void terminate()
{
    fputc('\n',fw);
    fputc('\n',fw);
    load();
}
void load()
{

    printf("Reading contents.........\n");
    int x=0,k;
    char ch,temp[4];
    ch=fgetc(fr);
    init();
    do
    {

       for( k=0;k<4 && ch!='\n';k++){
            temp[k]=ch;
            ch=fgetc(fr);
       }
        temp[k]='\0';
        if(temp[0]=='$' && temp[1]=='A' && temp[2]=='M' && temp[3]=='J')
        {
           while(ch!='\n')
            ch=fgetc(fr);
        }
        else if(temp[0]=='$' && temp[1]=='D' && temp[2]=='T' && temp[3]=='A')
        {
            startExecution();
        }
        else if(temp[0]=='$' && temp[1]=='E' && temp[2]=='N' && temp[3]=='D')
        {
            continue;
        }
        else
        {
             k=0;
            if(B==B2)
            {
                B2=B2+10;
            }
            for(int j=0;j<4;j++)
            {
                M[B][j]=temp[k];
                k++;
                printf("M[%d][%d]=%c",B,j,M[B][j]);
                printf("\n");
            }
            B++;
        }
        if(ch=='\n')
            ch=fgetc(fr);

    }while(ch!=EOF);
}
void startExecution()
{
    IC=00;
    executeProgram();
}
void executeProgram()
{
    while(true)
    {
        for(int i=0;i<4;i++)
        {
            IR[i]=M[IC][i];
        }
        IC++;
        if(IR[0]=='G' && IR[1]=='D')
        {
            SI=1;
            mos();
        }
        else if(IR[0]=='P' && IR[1]=='D')
        {
            SI=2;
            mos();
        }
        else if(IR[0]=='H')
        {
            SI=3;
            mos();
            break;
        }
        else if(IR[0]=='L' && IR[1]=='R')
        {
            int i=IR[2]-'0';
            i=i*10+(IR[3]-'0');
            for(int j=0;j<4;j++)
                R[j]=M[i][j];

        }
        else if(IR[0]=='S' && IR[1]=='R')
        {
            int i=IR[2]-'0';
            i=i*10+(IR[3]-'0');
            for(int j=0;j<4;j++)
                M[i][j]=R[j];

        }
        else if(IR[0]=='C' && IR[1]=='R')
        {
            int i=IR[2]-'0';
            i=i*10+(IR[3]-'0');
            int count=0;
            for(int j=0;j<4;j++)
              if(R[j]==M[i][j])
                count++;
              if(count==4)
                c=true;
              else
                c=false;
        }
        else if(IR[0]=='B' && IR[1]=='T')
        {
            if(c==true)
            {
                int i=IR[2]-'0';
                i=i*10+(IR[3]-'0');
                IC=i;
            }
        }

    }

}
