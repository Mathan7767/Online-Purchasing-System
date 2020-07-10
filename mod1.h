#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifdef _WIN32
    #include<windows.h>
    void sleep(unsigned milliseconds){Sleep(milliseconds);}
#else
    #include<unistd.h>
    void sleep(unsigned milliseconds){usleep(milliseconds);}
#endif
void writeWithDelay(char *s){
    int i=0;
    while(s[i]!='\0'){
        printf("%c",s[i++]);
        sleep(70);
    }
}
int signup();
int signin();

struct user
{
	char mail[30];
	char name[20],pass[20];
	char mobile[10];
	char addr[100];
}profile;

struct product{
	char title[150];
	char price[13];
	int quantity;
	int id;
};

int display(struct user *p)
{
	int n,i;
	char temp[150];
	l1:
	system("cls");
	strcpy(temp,"");
	strcat(temp,"Welcome ");
	strcat(temp,p->name);
	strcat(temp,"\n");
	writeWithDelay(temp);
	printf("1.profile\n");
	printf("2.Product categories\n");
	printf("3.Logout\n");
	scanf("%d",&n);
	switch(n){
		case 1:	
		system("cls");
		writeWithDelay(strcat(p->name,",Your Details\n"));
		printf("%-15s : %s\n","Email",p->mail);
		printf("%-15s : %s\n","Mobile Number",p->mobile);
		printf("%-15s : %s\n","Address",p->addr);
//		getch();
		display(p);
		return 0;
case 2:
		productcat(p);
		return 0;
case 3:
		main();
		break;
case -1:
		goto l1;
		break;
default:
		writeWithDelay("Invalid user option");
		goto l1;		
		return 0;	
}
}


int signup()
{
	FILE *data;
	int a,i;
 	fflush(stdin);
	system("cls");
	data=fopen("userprofile.dat","ab+");
	printf("Enter mail id:\n");
      gets(profile.mail);
	printf("Enter Name:\n");
	gets(profile.name);
	printf("Enter password:\n");
	gets(profile.pass);
	printf("Enter Address:\n");
	gets(profile.addr);
	printf("Enter mobile number\n");
      gets(profile.mobile);
	fwrite(&profile,sizeof(struct user),1,data);
	system("cls");
	writeWithDelay("User created successfully");
	fclose(data);	
	main();
}
	
	
int signin(){
	system("cls");
	writeWithDelay("Enter login credentials\n");
	FILE *data;
	int i,j=0,count=0;
	char c;
	fflush(stdin);
	char s1[100];
	char s2[100];
	puts("Enter mail id:\n");
	gets(s1);
	puts("Enter password:\n");
	do{
		c=getch();
		if(c=='\b'){
			printf("\b \b");
			j--;
			continue;
		}
		else if(c!='\r' && c!='\n')
		s2[j++]=c;
		else break;
		printf("*");
	}while(1);
	s2[j]='\0';
	data=fopen("userprofile.dat","rb+");
	while(fread(&profile,sizeof(profile),1,data))
		if(strcmp(s1,profile.mail)==0 && strcmp(s2,profile.pass)==0 )
		{
			system("cls");
			fclose(data);
			writeWithDelay("Successfully Logged in\n");
			display(&profile);
			count=1;
			return 0;
		}
	if(count==0){
		system("cls");
		writeWithDelay("Invalid credentials");
		main();
	}else{
		
	}
}





