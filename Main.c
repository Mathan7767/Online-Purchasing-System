#include"mod1.h" // User define header file to get login module
#include<stdlib.h>
#include<time.h>	//To input the System time and sate
#include<stdio.h>	//Input and output stream header fille

void billing(struct user *u,struct product *p)
{
	int a,continue1;	
	int hours,min,sec,day,month,year;

	// time_t is arithmetic time type
	time_t now;

	//time() returns the current time of the sysetm
	time(&now);

	
	//localtime converts a time_t value to calander time and
	//return a ponter to tm structure with its members
	struct tm *local=localtime(&now);

	hours=local->tm_hour;
	min=local->tm_min;
	sec=local->tm_sec;
	
	day=local->tm_mday; 	//get day of month(1 to 31)
	month=local->tm_mon+1;	//get month of year(0 to 11)
	year=local->tm_year+1900; //get year since 1990
	

	printf("\n\n\tPit Bull Electronics\t\t\t\tINVOICE\n\n");
	printf("\t[Address]\t\t\t\t\tINVOICE NO:%d\n",a%100);
	printf("\t[Address]\t\t\t\t\tTime:");

	if(hours<12)
		printf("%.2d:%.2d:%.2d am\n",hours,min,sec);
	else
		printf("%.2d:%.2d:%.2d pm\n",hours-12,min,sec);

	printf("\t[phone]\t\t\t\t\t\tDate:%.2d/%.2d/%.2d\n\n",day,month,year);
	printf("\tDelivery Address:\n\n");
	printf("\t%s,\n",u->name);
	printf("\t%s,\n",u->addr);
	printf("\t%s,\n",u->mobile);
	printf("\t%s.\n\n",u->mail);
	printf("\t=======================================================================================================\n");
	printf("\tQuantity\tDescription\t\t\t\t\t\t\t\tAmount\n");
	printf("\t=======================================================================================================\n");
	printf("\n\t1\t\t%s\t%s\n",p->title,p->price);
	printf("\t=======================================================================================================");
	printf("\n\n\t\t\t\t\t\t\t\t\t\t           Total:%s\n\n\n",p->price);
	Label4:printf("\n1.Do u want to Continue Shopping 2.Logout");
	scanf("%d",&continue1);
	if(continue1==1)
		display(u);
	else if(continue1==2)
		exit(0);
	else
	{
		printf("Enter the valid Choice!!!!!\n");
		goto Label4;
	}
	
}

void productcat(struct user *u)
{
	system("cls");
	int c1,choice,choice1,choice2,count;
	struct product p;
	char i[5];
	FILE *fp;
	Label1:printf("\nShop by category\n1.Laptops\n2.Televisions\n3.Refrigerator\n4.Washing Machines\n5.Back to previous screen\n\nProceed with product ");
	scanf("%d",&choice);
	printf("\t\t===================================================================================================================");
	printf("\n\t\tS.NO\t\t\tPRODUCT NAME\t\t\t\t\t\t\t\t\tPRICE\n");
	printf("\t\t===================================================================================================================\n\n");
	count=0;
	switch(choice)
	{
		case 1:
			strcpy(i,"PL");
			fp=fopen("laptop.dat","r+");
			break;
		case 2:
			strcpy(i,"PT");
			fp=fopen("tv.dat","r+");
			break;
		case 3:
			strcpy(i,"PF");
			fp=fopen("fridge.dat","r+");
			break;
		case 4:
			strcpy(i,"PW");
			fp=fopen("washingMachine.dat","r+");
			break;
		case 5:
			printf("Getting Back....");
			display(u);
			return;
			break;
		default:
			printf("Choose a valid choice");
			goto Label1;
	}
	fseek(fp,0,SEEK_SET);
	while(fread(&p,sizeof(struct product),1,fp))
	{
		printf("\t\t%d\t\t%-75s\t\t%s\t%d\n",++count,p.title,p.price,p.quantity);
	}
	Label2:printf("\n\t1.Select a Product\n\t0.Back to previous Screen\n\n\tEnter Choice ");
	scanf("%d",&c1);
	if(c1==0)
		goto Label1;
	else if(c1!=1)
	{
		printf("Invalid Choice!!!!!");
		goto Label2;
	}
	printf("Proceed with your Product Number ");
	scanf("%d",&choice1);
	if(choice1<1 ||  choice1>count)
	{
		printf("\n\tInvalid choice of product!!!!!\n");
		goto Label2;
	}
	fseek(fp,(choice1-1)*sizeof(struct product),SEEK_SET);
	fread(&p,sizeof(struct product),1,fp);
	if(p.quantity<=0)
	{
		printf("\tOops, Product looking is Out of Stock......\n");
		printf("\tTry with another product\n");
		goto Label2;
	}
	Label3:printf("\nYour Cart\n\t\t%s%.2d\t%s\t%s\n\n",i,choice1,p.title,p.price);
	printf("\t1.Proceed to Check out\n\t2.Back to Shopping\nProceed with your Choice");
	scanf("%d",&choice2);
	if(choice2==1)
	{
		--p.quantity;			
		fseek(fp,-sizeof(struct product),SEEK_CUR);
		fwrite(&p,sizeof(struct product),1,fp);
	}
	else if(choice2==2)
	{
		printf("\n");	
		goto Label1;
	}
	else
	{
		printf("Invalid choice!!!!!\n");
		goto Label3;
	}
	billing(u,&p);
	fclose(fp);
	
}

int main(){
	system("cls");
    int choice;
    printf("1.Sign in\n2.Sign Up\nEnter your choice\t");
    scanf("%d",&choice);
    switch(choice){
        case 1:signin();break;
        case 2:signup();break;
        default:system("cls");
				writeWithDelay("Please select valid choice\n");
				main();
				break;
    }
}

