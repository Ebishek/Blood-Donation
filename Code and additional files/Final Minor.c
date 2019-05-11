	#include<windows.h>	
	#include<stdio.h>
	#include<conio.h>
	#include <stdlib.h>
	#include<string.h>                  //contains strcmp(),strcpy(),strlen(),etc
	#include<ctype.h>                   //contains toupper(), tolower(),etc
	#include<dos.h>                     //contains _dos_getdate
	#include<time.h>
	
	#define RETURNTIME 15
	#include <stdio.h>
	#include <stdlib.h> 
	#include<string.h>
	#define inf 	99
	#define V_SIZE	20
	#define MAX 20
	
	char catagories[][15]={"New Donor","Existing Donor"};
	void returnfunc(void);
	void returnfuncadmin(void);
	void array_fill(int * array, int len, int val);
	void dijkstra(int graph[][V_SIZE],int n,int start,int dist[],int dest,const char* c[]);
	void usermenu(void);	
	void adminmenu(void);
	void mainmenu(void);
	void login(void);
	void findpath(void);
	void pathmenu(void);
	void adddonors(void);
	void editdonors(void);
	void searchdonors(void);
	void viewowndetails(void);
	void viewdonors(void);
	void viewrequest(void);
	int  getdata();
	int  checkid(int);
	int checkidpass(char[], char[]);
	int  t(void);
	void AdminPassword();
	void UserPassword();
	char shownotification();
	char requesttoadmin();
	
	
	FILE *fp,*ft,*fs;
	
	
	COORD coord = {0, 0};
	//list of global variable
	int s;
	char finddonor;
	char adminpassword[10]="userpass";
	char userpassword[10] = "bloodbank";
	struct donors
	{
	int donor_id;
	char name[20];
	char Address[20];
	int age;
	char sex[6];
	char userid[10];
	char contact[10];
	int count;
	char *cat;
	};
	
	struct donors a;
/////////////////////////////////////////////////////////////////////////////
	void gotoxy (int x, int y)
	{
	coord.X= x; coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}
/////////////////////////////////////////////////////////////////////////////////
	char cha;
	void array_fill(int * array, int len, int val) 
	{
		int i;
		for (i = 0; i < len; i++) 
		{
			array[i] = val;
		}
	}
	/////////////////////////////////////////////////////////////////////////////////
	
	void dijkstra(int graph[][V_SIZE],int n,int start,int dist[],int dest,const char* c[])
	{	
		int visited1[n],path1[n],shortest1[n],min,v,i,j;
		int *visited=visited1;
		int *path=path1;
		int *shortest=shortest1;
		array_fill(visited,n, 0);
		array_fill(dist,n, inf);
		FILE *f;
	            char ch;																										
	            f=fopen("output_set.txt","a+");
		for(i=0;i<n;i++) 
		{
			dist[i]=graph[start][i];
			if(i!=start&&dist[i]<inf)
			path[i]=start;
			else path[i]=-1;
		}
		visited[start]=1;
		while(1) 
		{
			min=inf;
			v=-1;
			for(i=0;i<n;i++) 
			{
				if(!visited[i]) 
				{
					if(dist[i]<min) {min=dist[i];v=i;}
				}
			}
			if(v==-1)break; 
			visited[v]=1;
			for(i=0;i<n;i++) {
				if(!visited[i]&&graph[v][i]!=inf &&	dist[v]+graph[v][i]<dist[i]) 
				{
					dist[i]=dist[v]+graph[v][i];
					path[i]=v;
				}
			}
		}
		printf("\n");
		for(i=0;i<n;i++) 
		{
			if(i==start) 
			continue;
			array_fill(shortest,n, 0);
			if(i==dest)
			{
			printf(" Start = %d\t",start);
			fprintf(f,"Start = %d\t",start);
			printf(" End = %d\t\t",i);
			fprintf(f,"End = %d\t",i);
			printf(" Cost = %dkm",dist[i]);
			fprintf(f,"Cost = %d\t",dist[i]);
			printf(" Path = ");
			fprintf(f,"Path = ");
			int k=0,s=0;
			shortest[k]=i;
			while(path[shortest[k]]!=start)
			 {
				k++;
				shortest[k]=path[shortest[k-1]];
			 }
			k++;
			shortest[k]=start;
			for(j=k;j>0;j--) {
				 s=shortest[j];
				 printf(" -> %s  ",c[s]);
				 fprintf(f,"-> %s ",c[s]);
			}
			s=shortest[0];
			printf("-> %s \n",c[s]);
			fprintf(f,"-> %s \n",c[s]);
			printf("\n");
			fprintf(f,"\n");
			}
		}
		
	   	return;
	}
	///////////////////////////////////////////////////////////////////////////	
	void mainmenu()
{
system("cls");
int i;
gotoxy(20,3);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,5);
printf("\xDB\xDB\xDB\xDB\xB2 1. Login   ");
gotoxy(20,7);
printf("\xDB\xDB\xDB\xDB\xB2 2. Register");
gotoxy(20,9);
printf("\xDB\xDB\xDB\xDB\xB2 3. Admin Login");
gotoxy(20,11);
printf("\xDB\xDB\xDB\xDB\xB2 4. Close Application");
gotoxy(20,13);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,20);
	
	char c[1000];
    FILE *fptr;
    if ((fptr = fopen("adminmessage.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);         
    }
    fscanf(fptr,"%[^\n]", c);
    gotoxy(20,19);
    printf("Alert:-%s\n", c);
    fclose(fptr);
    gotoxy(20,20);
t();
gotoxy(20,22);
printf("Enter your choice:");
switch(getch())
{
case '1':
login();
break;
case '2':
adddonors();
break;
case '3':
AdminPassword();
break;
case '4':
{
system("cls");
gotoxy(16,3);
printf("\tBlood Donation and Management System");
gotoxy(16,4);
printf("\tMini Project in C");
gotoxy(16,5);
printf("******************************************");
gotoxy(16,6);
printf("*******************************************");
gotoxy(16,9);
printf("*******************************************");
gotoxy(16,12);
printf("********************************************");
gotoxy(10,17);
printf("Exiting in 3 second...........>");
Sleep(3000);
exit(0);
}
default:
{
gotoxy(10,23);
printf("\aWrong Entry!!Please re-entered correct option");
if(getch())
mainmenu();
}

}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
int getdata()
{
int t;
gotoxy(20,3);printf("Enter the Information Below,(Warning :- Extra word more then basic standard would be skipped)");
gotoxy(20,4);printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,5);
printf("\xB2");gotoxy(46,5);printf("\xB2");
gotoxy(20,6);
printf("\xB2");gotoxy(46,6);printf("\xB2");
gotoxy(20,7);
printf("\xB2");gotoxy(46,7);printf("\xB2");
gotoxy(20,8);
printf("\xB2");gotoxy(46,8);printf("\xB2");
gotoxy(20,9);
printf("\xB2");gotoxy(46,9);printf("\xB2");
gotoxy(20,10);
printf("\xB2");gotoxy(46,10);printf("\xB2");
gotoxy(20,11);
printf("\xB2");gotoxy(46,11);printf("\xB2");
gotoxy(20,12);
printf("\xB2");gotoxy(46,12);printf("\xB2");
gotoxy(20,13);
printf("\xB2");gotoxy(46,13);printf("\xB2");
gotoxy(20,14);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(21,5);
printf("Category:");
gotoxy(31,5);
printf("%s",catagories[s-1]);
gotoxy(21,6);
printf("Donor Name:");gotoxy(33,6);
scanf("%s",&a.name);
gotoxy(21,7);
printf("Address:");gotoxy(33,7);
scanf("%s",&a.Address);
gotoxy(21,8);
printf("Age:");gotoxy(33,8);
scanf("%2d",&a.age);
gotoxy(21,9);
printf("Sex:");gotoxy(33,9);
scanf("%s",&a.sex);
gotoxy(21,10);
printf("Contact No:");gotoxy(33,10);
scanf("%10s",&a.contact);
gotoxy(21,11);
printf("User Id:");gotoxy(33,11);
scanf("%s",&a.userid);
gotoxy(21,12);
printf("Password is:-%s",&userpassword);gotoxy(33,11);
gotoxy(21,13);
return 1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void login(void)
{

UserPassword();

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void usermenu()
{
system("cls");
int i;
gotoxy(20,3);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 USER MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,5);
printf("\xDB\xDB\xDB\xDB\xB2 1. View Own Details   ");
gotoxy(20,7);
printf("\xDB\xDB\xDB\xDB\xB2 2. Request to Admin");
gotoxy(20,9);
printf("\xDB\xDB\xDB\xDB\xB2 3. Find Shortest Path");
gotoxy(20,11);
printf("\xDB\xDB\xDB\xDB\xB2 4. Logout");
gotoxy(20,13);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,20);
t();
gotoxy(20,21);
////////////////////////////////////////////////
printf("Enter your choice:");
switch(getch())
{
case '1':
viewowndetails();
break;
case '2':
requesttoadmin();
break;
case '3':
findpath();
break;
case '4':
{
system("cls");
gotoxy(16,3);
printf("\tThanks for Being a part of Donation Campain");
gotoxy(16,4);
}
default:
{
gotoxy(10,23);
printf("\aWrong Entry!!Please re-entered correct option");
if(getch())
mainmenu();
}

}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void viewowndetails()
{
system("cls");
char d[10];
printf("*****************************Search Donors*********************************");
gotoxy(20,10);
printf("\xDB\xDB\xDB\xB2 1.View Details By Donor_id");
gotoxy(20,14);
printf("\xDB\xDB\xDB\xB2 2.View Details By Doonor Name");
gotoxy(20,18);
printf("\xDB\xDB\xDB\xB2 3.Go Back To Menu");
gotoxy(20,25);
printf("Enter Your Choice");
fp=fopen("Bibek.txt","rt+"); //open file for reading propose
rewind(fp);   //move pointer at the begining of file
switch(getch())
{
case '1':
{
system("cls");
gotoxy(25,4);
printf("****View By User_Id****");
gotoxy(20,5);
printf("Enter the User_Id:");
scanf("%s",&d);
gotoxy(20,7);
printf("Searching........");
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.userid==d)
{
Sleep(2);
gotoxy(20,7);
printf("Donor is available");
gotoxy(20,8);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,9);
printf("\xB2 Donor_Id:%d",a.donor_id);gotoxy(47,9);printf("\xB2");
gotoxy(20,10);
printf("\xB2 Name:%s",a.name);gotoxy(47,10);printf("\xB2");
gotoxy(20,11);
printf("\xB2 Address:%s ",a.Address);gotoxy(47,11);printf("\xB2");
gotoxy(20,12);
printf("\xB2 Age:%d ",a.age);gotoxy(47,12);printf("\xB2"); gotoxy(47,11);printf("\xB2");
gotoxy(20,13);
printf("\xB2 Sex:Rs.%s",a.sex);gotoxy(47,13);printf("\xB2");
gotoxy(20,14);
printf("\xB2 Contact No:%d ",a.contact);gotoxy(47,14);printf("\xB2");
gotoxy(20,15);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
finddonor='t';
}

}
if(finddonor!='t')  //checks whether conditiion enters inside loop or not
{
gotoxy(20,8);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,9);printf("\xB2");  gotoxy(38,9);printf("\xB2");
gotoxy(20,10);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(22,9);printf("\aNo Record Found");
}
gotoxy(20,17);
printf("Try another search?(Y/N)");
if(getch()=='y')
searchdonors();
else
mainmenu();
break;
}
case '2':
{
char s[15];
system("cls");
gotoxy(25,4);
printf("****View Donors By Name****");
gotoxy(20,5);
printf("Enter Donor Name:");
scanf("%s",s);
int d=0;
while(fread(&a,sizeof(a),1,fp)==1)
{
if(strcmp(a.name,(s))==0) //checks whether a.name is equal to s or not
{
gotoxy(20,7);
printf("The Donor is available");
gotoxy(20,8);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,9);
printf("\xB2 Donor_Id:%d",a.donor_id);gotoxy(47,9);printf("\xB2");
gotoxy(20,10);
printf("\xB2 Name:%s",a.name);gotoxy(47,10);printf("\xB2");
gotoxy(20,11);
printf("\xB2 Address:%s",a.Address);gotoxy(47,11);printf("\xB2");
gotoxy(20,12);
printf("\xB2 Age:%d",a.age);gotoxy(47,12);printf("\xB2");
gotoxy(20,13);
printf("\xB2 Sex:Rs.%s",a.sex);gotoxy(47,13);printf("\xB2");
gotoxy(20,14);
printf("\xB2 Contact No:%d ",a.contact);gotoxy(47,14);printf("\xB2");
gotoxy(20,15);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
d++;
}

}
if(d==0)
{
gotoxy(20,8);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,9);printf("\xB2");  gotoxy(38,9);printf("\xB2");
gotoxy(20,10);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(22,9);printf("\aNo Record Found");
}
gotoxy(20,17);
printf("Try another search?(Y/N)");
if(getch()=='y')
searchdonors();
else
mainmenu();
break;
}
case '3':
{
system("cls");
gotoxy(16,3);
adminmenu();
gotoxy(16,4);
break;
}
default :
getch();
searchdonors();
}
fclose(fp);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void searchdonors()
{
system("cls");
int d;
printf("*****************************Search Donors*********************************");
gotoxy(20,10);
printf("\xDB\xDB\xDB\xB2 1. Search By Donor_id");
gotoxy(20,14);
printf("\xDB\xDB\xDB\xB2 2. Search By Name");
gotoxy( 15,20);
printf("Enter Your Choice");
fp=fopen("Bibek.txt","rt+"); //open file for reading propose
rewind(fp);   //move pointer at the begining of file
switch(getch())
{
case '1':
{
system("cls");
gotoxy(25,4);
printf("****Search By Donor_Id****");
gotoxy(20,5);
printf("Enter the Donor_Id:");
scanf("%d",&d);
gotoxy(20,7);
printf("Searching........");
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.donor_id==d)
{
Sleep(2);
gotoxy(20,7);
printf("Donor is available");
gotoxy(20,8);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,9);
printf("\xB2 Donor_Id:%d",a.donor_id);gotoxy(47,9);printf("\xB2");
gotoxy(20,10);
printf("\xB2 Name:%s",a.name);gotoxy(47,10);printf("\xB2");
gotoxy(20,11);
printf("\xB2 Address:%s ",a.Address);gotoxy(47,11);printf("\xB2");
gotoxy(20,12);
printf("\xB2 Age:%d ",a.age);gotoxy(47,12);printf("\xB2"); gotoxy(47,11);printf("\xB2");
gotoxy(20,13);
printf("\xB2 Sex:Rs.%s",a.sex);gotoxy(47,13);printf("\xB2");
gotoxy(20,14);
printf("\xB2 Contact No:%d ",a.contact);gotoxy(47,14);printf("\xB2");
gotoxy(20,15);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
finddonor='t';
}

}
if(finddonor!='t')  //checks whether conditiion enters inside loop or not
{
gotoxy(20,8);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,9);printf("\xB2");  gotoxy(38,9);printf("\xB2");
gotoxy(20,10);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(22,9);printf("\aNo Record Found");
}
gotoxy(20,17);
printf("Try another search?(Y/N)");
if(getch()=='y')
searchdonors();
else
mainmenu();
break;
}
case '2':
{
char s[15];
system("cls");
gotoxy(25,4);
printf("****Search Donors By Name****");
gotoxy(20,5);
printf("Enter Donor Name:");
scanf("%s",s);
int d=0;
while(fread(&a,sizeof(a),1,fp)==1)
{
if(strcmp(a.name,(s))==0) //checks whether a.name is equal to s or not
{
gotoxy(20,7);
printf("The Donor is available");
gotoxy(20,8);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,9);
printf("\xB2 Donor_Id:%d",a.donor_id);gotoxy(47,9);printf("\xB2");
gotoxy(20,10);
printf("\xB2 Name:%s",a.name);gotoxy(47,10);printf("\xB2");
gotoxy(20,11);
printf("\xB2 Address:%s",a.Address);gotoxy(47,11);printf("\xB2");
gotoxy(20,12);
printf("\xB2 Age:%d",a.age);gotoxy(47,12);printf("\xB2");
gotoxy(20,13);
printf("\xB2 Sex:Rs.%s",a.sex);gotoxy(47,13);printf("\xB2");
gotoxy(20,14);
printf("\xB2 Contact No:%d ",a.contact);gotoxy(47,14);printf("\xB2");
gotoxy(20,15);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
d++;
}

}
if(d==0)
{
gotoxy(20,8);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,9);printf("\xB2");  gotoxy(38,9);printf("\xB2");
gotoxy(20,10);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(22,9);printf("\aNo Record Found");
}
gotoxy(20,17);
printf("Try another search?(Y/N)");
if(getch()=='y')
searchdonors();
else
mainmenu();
break;
}
default :
getch();
searchdonors();
}
fclose(fp);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void adddonors(void)    //funtion that New Donor
{
system("cls");
int i;
gotoxy(20,5);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2SELECT CATEGOIES\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,7);
printf("\xDB\xDB\xDB\xDB\xB2 1. New Donor");
gotoxy(20,9);
printf("\xDB\xDB\xDB\xDB\xB2 2. Back to Main Menu");
gotoxy(20,11);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,14);
printf("Enter your choice:");
scanf("%d",&s);
if(s==2)
mainmenu() ;
system("cls");
fp=fopen("Bibek.txt","at");
if(getdata()==1)
{
int prevdid;
int prevcnt;
prevdid = a.donor_id;
prevcnt = a.count;
a.cat=catagories[s-1];
a.donor_id = prevdid;
a.count = prevcnt;
a.donor_id = a.donor_id + 1;
a.count = a.count + 1;
fseek(fp,0,SEEK_END);
fwrite(&a,sizeof(a),1,fp);
fclose(fp);
gotoxy(21,15);
printf("The record is sucessfully saved");
gotoxy(21,16);
printf("Save any more?(Y / N):");
if(getch()=='n')
login();
else
system("cls");
login();
}
}

void AdminPassword(void) //for password option
	{
	
		system("cls");
		char d[25]="Enter The Password";
		char ch,pass[10];
		int i=0,j;
		//textbackground(WHITE);
		//textcolor(RED);
		gotoxy(10,4);
		for(j=0;j<20;j++)
		{
		Sleep(50);
		printf(":");
		}
		for(j=0;j<20;j++)
		{
		Sleep(50);
		printf("%c",d[j]);
		}
		for(j=0;j<20;j++)
		{
		Sleep(50);
		printf(":");
		}
		gotoxy(10,10);
		gotoxy(15,7);
		printf("Enter Password:");
		
		while(ch!=13)
		{
		ch=getch();
		
		if(ch!=13 && ch!=8){
		putch('*');
		pass[i] = ch;
		i++;
		}
		}
		pass[i] = '\0';
		if(strcmp(pass,adminpassword)==0)
		{
		
		gotoxy(15,9);
		//textcolor(BLINK);
		printf("Now You Are Logged In!");
		gotoxy(17,10);
		printf("\n\xB2\xB2\xB2\xB2Press any key to countinue...");
		getch();
		adminmenu();
		}
		else
		{
		gotoxy(15,16);
		printf("\aWarning!! Incorrect Password");
		getch();
		AdminPassword();
		}
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////

void UserPassword(void) //for password option
	{
	
		system("cls");
		char d[25]="Enter The Password";
		char ch,pass[10];
		int i=0,j;
		//textbackground(WHITE);
		//textcolor(RED);
		gotoxy(10,4);
		for(j=0;j<20;j++)
		{
		Sleep(50);
		printf(":");
		}
		for(j=0;j<20;j++)
		{
		Sleep(50);
		printf("%c",d[j]);
		}
		for(j=0;j<20;j++)
		{
		Sleep(50);
		printf(":");
		}
		gotoxy(10,10);
		gotoxy(15,7);
		printf("Enter Password:");
		
		while(ch!=13)
		{
		ch=getch();
		
		if(ch!=13 && ch!=8){
		putch('*');
		pass[i] = ch;
		i++;
		}
		}
		pass[i] = '\0';
		if(strcmp(pass,userpassword)==0)
		{
		
		gotoxy(15,9);
		//textcolor(BLINK);
		printf("Now You Are Logged In!");
		gotoxy(17,10);
		printf("\n\xB2\xB2\xB2\xB2Press any key to countinue...");
		getch();
		usermenu();
		}
		else
		{
		gotoxy(15,16);
		printf("\aWarning!! Incorrect Password");
		getch();
		UserPassword();
		}
	}	
	
/////////////////////////////////////////////////////////////////////////////////////////////////////
void findpath()
{
	system("cls");
	int dist[V_SIZE],start,end;
	const char* c[] = {"Selaqui","Bidholi","Nand","Premnager","IMA","Ballupur","Synergy","Balliwala","Garhi C.","IMA Blood B","Bindalpul","ISBT","Clock T.","Railway S.","Survey C.","Max H.","CMI Hosp.","Rispana B.","Kailash","Prince C."};
	int W[V_SIZE][V_SIZE] = {
				{inf , 15 , 13 ,inf ,inf ,inf ,inf ,inf ,inf ,inf ,inf ,inf ,inf ,inf ,inf ,inf ,inf ,inf ,inf ,inf },
				{15 , inf , 9 , inf , inf , inf , inf , inf , inf , inf , inf , inf , inf , inf , inf , inf , inf , inf , inf ,inf },
				{13 , 9 , inf , 2 , inf , inf , inf , inf , 8 , inf , inf , inf , inf , inf , inf , inf , inf , inf , inf,inf },
				{inf , inf , 2 , inf , 3 , inf , inf , inf , inf , inf , inf , 9 , inf , inf , inf , inf , inf , inf , inf , inf },
				{inf, inf ,inf , 3 , inf , 3 , inf , 2 , inf , inf , inf , inf , inf , inf , inf , inf , inf , inf , inf , inf },
				{inf, inf ,inf , inf , 3 , inf , 2 , 3 , inf , 1 , inf , inf , inf , inf , inf , inf , inf , inf , inf , inf },
				{inf, inf ,inf , inf , inf , 2 , inf , inf , 4 , inf , inf , inf , inf , inf , inf , inf , inf , inf , inf , inf },
				{inf, inf ,inf , inf , 2 , 3 , inf , inf , inf , 3 , inf , 6 , inf , inf , inf , inf , inf , inf , inf , inf },
				{inf, inf ,8 , inf , inf,inf,4,inf,inf,inf,4,inf,inf,inf,inf,6,inf,inf,inf,inf},
				{inf, inf ,inf , inf ,inf,1,inf,3,inf,inf,2,inf,inf,inf,inf,inf,inf,inf,inf,inf},
				{inf, inf ,inf , inf ,inf,inf,inf,inf,4,2,inf,inf,1,inf,inf,inf,inf,inf,inf,inf},
				{inf, inf ,inf , 9 ,inf,inf,inf,6,inf,inf,inf,inf,7,6,inf,inf,inf,7,inf,inf},
				{inf, inf ,inf , inf ,inf,inf,inf,inf,inf,inf,1,7,inf,inf,1,8,inf,inf,inf,1},
				{inf, inf ,inf , inf ,inf,inf,inf,inf,inf,inf,inf,6,inf,inf,inf,inf,inf,inf,inf,6},
				{inf, inf ,inf , inf ,inf,inf,inf,inf,inf,inf,inf,inf,1,inf,inf,7,2,inf,inf,inf},
				{inf, inf ,inf , inf , inf,inf,inf,inf,6,inf,inf,inf,8,inf,7,inf,inf,8,inf,inf},
				{inf, inf ,inf , inf ,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,2,inf,inf,3,inf,inf},
				{inf, inf ,inf , inf ,inf,inf,inf,inf,inf,inf,inf,7,inf,inf,inf,8,3,inf,2,inf},
				{inf, inf ,inf , inf ,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,2,inf,inf},
				{inf, inf ,inf , inf ,inf,inf,inf,inf,inf,inf,inf,inf,1,6,inf,inf,inf,inf,inf,inf}
				};
			FILE *f;
            char ch;
            f=fopen("data_set.txt","rt");
			while((ch=fgetc(f))!=EOF){
            printf("%c",ch);
            }
            fclose(f);
			do
	{
gotoxy(20,1);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 PATH MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,3);printf("\xDB\xDB\xDB\xDB\xB2 0. SELAQUI");
gotoxy(20,5);printf("\xDB\xDB\xDB\xDB\xB2 1. BIDHOLI");
gotoxy(20,7);printf("\xDB\xDB\xDB\xDB\xB2 2. NANDA KI CHOWKI");
gotoxy(20,9);printf("\xDB\xDB\xDB\xDB\xB2 3. PREMNAGAR");
gotoxy(20,11);printf("\xDB\xDB\xDB\xDB\xB2 4. IMA");
gotoxy(20,13);printf("\xDB\xDB\xDB\xDB\xB2 5. BALLUPUR");
gotoxy(20,15);printf("\xDB\xDB\xDB\xDB\xB2 6. SYNERGY");
gotoxy(20,17);printf("\xDB\xDB\xDB\xDB\xB2 7. BALLIWLA CHOWK");
gotoxy(20,19);printf("\xDB\xDB\xDB\xDB\xB2 8. GARHI CANT");
gotoxy(20,21);printf("\xDB\xDB\xDB\xDB\xB2 9. IMA BLOOD BANK");
gotoxy(20,23);printf("\xDB\xDB\xDB\xDB\xB2 10. BINDALPUL");
gotoxy(20,25);printf("\xDB\xDB\xDB\xDB\xB2 11. ISBT");
gotoxy(20,27);printf("\xDB\xDB\xDB\xDB\xB2 12. CLOCK TOWER");
gotoxy(20,29);printf("\xDB\xDB\xDB\xDB\xB2 13. RAILWAY STATION");
gotoxy(20,31);printf("\xDB\xDB\xDB\xDB\xB2 14. SURVEY CHOWK");
gotoxy(20,33);printf("\xDB\xDB\xDB\xDB\xB2 15. MAX HOSPITAL");
gotoxy(20,35);printf("\xDB\xDB\xDB\xDB\xB2 16. CMI HOSPITAL");
gotoxy(20,37);printf("\xDB\xDB\xDB\xDB\xB2 17. RISPANA BRIDGE");
gotoxy(20,39);printf("\xDB\xDB\xDB\xDB\xB2 18. KAILASH HOSPITAL");
gotoxy(20,41);printf("\xDB\xDB\xDB\xDB\xB2 19. PRINCE CHOWK");
	printf("\n\n Enter Starting Vertex : ");
	scanf("%d",&start);
	printf(" Enter Ending Vertex : ");
	scanf("%d",&end);
	if(start == end)
	{
		printf(" \n  Hey you have enter same initial and ending point please change it");
	}
	dijkstra(W,V_SIZE,start,dist,end,c);
	printf ("Do you want to continue: y/n :-");
    scanf (" %c", &cha);
	}
	while(cha == 'y' || cha == 'Y');
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

void adminmenu()
{
system("cls");
int i;
gotoxy(20,3);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 ADMIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,5);
printf("\xDB\xDB\xDB\xDB\xB2 1. Edit Profile   ");
gotoxy(20,7);
printf("\xDB\xDB\xDB\xDB\xB2 2. Show Notification to all");
gotoxy(20,9);
printf("\xDB\xDB\xDB\xDB\xB2 3. Show Donors");
gotoxy(20,11);
printf("\xDB\xDB\xDB\xDB\xB2 4. Show Users Requests");
gotoxy(20,13);
printf("\xDB\xDB\xDB\xDB\xB2 5. Exit");
gotoxy(20,15);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,19);
t();
gotoxy(20,21);
printf("Enter your choice:");
switch(getch())
{
case '1':
editdonors();
break;
case '2':
shownotification();
break;
case '3':
viewdonors();
case '4':
	system("cls");
	char c[1000];
    FILE *fptr;
    if ((fptr = fopen("userrequest.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);         
    }
    fscanf(fptr,"%[^\n]", c);
    printf("Request:-%s\n", c);
    fclose(fptr);
    if(getch())
    adminmenu();
break;
case '5':
{
system("cls");
gotoxy(16,3);
mainmenu();
gotoxy(16,4);
}
default:
{
gotoxy(10,23);
printf("\aWrong Entry!!Please re-entered correct option");
if(getch())
mainmenu();
}
}
}

void editdonors(void)  //edit information about donor
{
system("cls");
int c=0;
int d,e;
gotoxy(20,4);
printf("****Edit Donor Section****");
char another='y';
while(another=='y')
{
system("cls");
gotoxy(15,6);
printf("Enter Donor Id to be edited:");
scanf("%d",&d);
fp=fopen("Bibek.txt","rt+");
while(fread(&a,sizeof(a),1,fp)==1)
{
if(checkid(d)==0)
{
gotoxy(15,7);
printf("The Donor is availble");
gotoxy(15,8);
printf("The Donor Id:%d",a.donor_id);
gotoxy(15,9);
printf("Enter New Name:");scanf("%s",a.name);
gotoxy(15,10);
printf("Enter New Address:");scanf("%s",a.Address);
gotoxy(15,11);
printf("Enter New Age:");scanf("%d",&a.age);
gotoxy(15,12);
printf("Enter Sex:");scanf("%s",&a.sex);
gotoxy(15,13);
printf("Enter Contact:");scanf("%s",&a.contact);
gotoxy(15,14);
printf("The record is modified");
fseek(fp,ftell(fp)-sizeof(a),0);
fwrite(&a,sizeof(a),1,fp);
fclose(fp);
c=1;
}
if(c==0)
{
gotoxy(15,9);
printf("No record found");
}
}
gotoxy(15,16);
printf("Modify another Record?(Y/N)");
fflush(stdin);
another=getch() ;
}
adminmenu();
}
/////////////////////////////////////////////////////////////////////////
char shownotification()
{
	system("cls");
	char sentence[1000];
	printf("Enter Some Important Information That You Want To Display In User Menu\n");
   	FILE *fptr;

   	fptr = fopen("adminmessage.txt", "w");
   	if(fptr == NULL)
   	{
      printf("Error!");
      exit(1);
   	}
   
   printf("Enter Message:\n");
   gets(sentence);

   fprintf(fptr,"%s", sentence);
   fclose(fptr);
   if(getch())
   printf("Enter any key to exit1\n");
   mainmenu();
}

char requesttoadmin()
{
	system("cls");
	char sentence[1000];
	printf("Enter Some Important Information That You Want To Display In Admin Menu\n");
   	FILE *fptr;

   	fptr = fopen("userrequest.txt", "w");
   	if(fptr == NULL)
   	{
      printf("Error!");
      exit(1);
   	}
   
   printf("Enter Message:\n");
   scanf("%s",&sentence);

   fprintf(fptr,"%s", sentence);
   fclose(fptr);
   if(getch())
   printf("Enter any key to exit1\n");
   mainmenu();
}
//////////////////////////////////////////////////////////////////////////////
void viewdonors(void)  //show the list of donor persists
{
int i=0,j;
system("cls");
gotoxy(1,1);
printf("*********************************Donor List*****************************");
gotoxy(2,2);
printf(" CATEGORY  DONOR_ID DONON NAME    ADDRESS	 AGE  	 SEX  	   CONTACT ");
j=4;
fp=fopen("Bibek.txt","rt");
while(fread(&a,sizeof(a),1,fp)==1)
{
gotoxy(3,j);
printf("%s",a.cat);
gotoxy(16,j);
printf("%d",a.donor_id);
gotoxy(22,j);
printf("%s",a.name);
gotoxy(36,j);
printf("%s",a.Address);
gotoxy(50,j);
printf("%d",a.age);
gotoxy(57,j);
printf("%s",a.sex);
gotoxy(69,j);
printf("%s",a.contact);
printf("\n\n");
j++;
}
gotoxy(3,25);
printf("Total Donors =%d",a.count);
fclose(fp);
gotoxy(35,25);
returnfuncadmin();
}
/////////////////////////////////////////////////////////////////////////////////

void viewrequest()
{
	system("cls");
	char c[1000];
    FILE *fptr;
    if ((fptr = fopen("userrequest.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);         
    }
    fscanf(fptr,"%[^\n]", c);
    gotoxy(20,19);
    printf("Request:-%s\n", c);
    fclose(fptr);
    gotoxy(20,20);
}

///////////////////////////////////////////////////////////////////////////////////////////////
int checkid(int t)  //check whether the donor is exist in library or not
{
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
if(a.donor_id==t)
return 0;  //returns 0 if donor exits
return 1; //return 1 if it not
}
///////////////////////////////////////////////////////////////////////////////////////
void returnfuncadmin(void)
{
{
printf(" Press ENTER to return to Admin Menu");
}
a:if(getch()==13) //allow only use of enter
adminmenu();
else
goto a;
}
///////////////////////////////////////////////////////////////////////////////////
int t(void) //for time
{
time_t t;
time(&t);
printf("Date and time:%s\n",ctime(&t));

return 0 ;
}

///////////////////////////////////////////////////////////////////////////////////
int main()
{
mainmenu();
getch();
return 0;

}
///////////////////////////////////////////////////////////////////////////////
