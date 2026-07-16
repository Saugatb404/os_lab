#include<stdio.h>
#include<sys/stat.h>
#include<string.h>
int main(){
FILE *fp,*f1,*f2;
int opt;
char line[100];
printf("enter ur choice\n");
scanf("%d",&opt);
switch(opt){
case 1:
if((fp=popen("/bin/ls","r"))==NULL){
printf("pipeline error");
}
printf("list command\n");
printf("*************\n");
while(fgets(line,80,fp)){
printf("%s",line);
}
break;
case 2:
printf("PWD comman\n");
printf("**********\n");
if((f1=popen("/bin/pwd","r"))==NULL){
printf("PWD function error\n");
}
while(fgets(line,80,f1)){
printf("%s",line);
}
break;
case 3:
printf("cat commond\n");
printf("***********\n");
if((f2=fopen("ch.c","w"))==NULL){
printf("Cat function error\n");
}
while(fgets(line,80,f2)){
printf("%s",line);
}
break;
case 4:
printf("exit\n");
printf("****\n");
exit(0);
break;
}
}