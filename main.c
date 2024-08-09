#include "header.h"

int main(int argc, char * argv[])       // main function with commmand line arguments
{
    invert *head = NULL;
    hash arr[28];
    for(int i =0; i<28; i++)
    {
	arr[i].index = i;
	arr[i].link = NULL;
    }
    if(argc == 1)
    {
	printf("\n============================================\n");
	fprintf(stdout,"\nERROR : please pass proper commands\n");
	fprintf(stdout,"\n example: ./result.exe file1.txt file2.txt\n");
	printf("\n============================================\n");
	return 0;
    }
    else
    {
	if(argc > 1)
	{
	    int i = 1,choice; 
	    while(argv[i] != NULL)
	    {
		char* cmp;
		cmp = strstr(argv[i],".");
		if(strcmp(cmp,".txt") !=0)
		{
		    printf("\n====================\n");
		    printf("\nError : %s is not a .txt file\n",argv[i]);
		    printf("\n====================\n");
		}
		else
		{
		    FILE * fptr = fopen(argv[i],"r");
		    if(fptr == NULL)
		    {
			printf("\n==================================\n");
			fprintf(stdout,"\nERROR :%s File is not present\n",argv[i]);
			printf("\n===================================\n");
		    }
		    else
		    {
			fseek(fptr,0,SEEK_END);
			int size = ftell(fptr);
			if(size == 0)
			{
			    printf("\n==============================\n");
			    printf("\nError : %s File is Empty \n",argv[i]);
			    printf("\n===============================\n");
			}
			else
			{
			    if(check(head,argv[i]) == success)
			    {
				if(insert_list(&head,argv[i]) == success)
				{
				    printf("\nFile is Inserted %s\n",argv[i]);
				}
				else
				{
				    printf("\nFile is not Inserted\n");
				}
			    }
			    else
			    {
	                        printf("\n============================================\n");
				printf("\nError :%s is Duplicate File\n",argv[i]);
	                        printf("\n============================================\n");
			    }
			}
		    }
		}
		i++;
	    } 
	    int flag1 =0,flag2=0;
	    while(1)
	    {
		printf("\n1.Create Database\n2.Display Database\n3.Search Database\n4.Save Database\n5.Update Database\n6.Exit\nEnter your Choice :");
		scanf("%d",&choice);
		switch(choice)
		{
		    case 1 :
			if(flag1 == 0)
			{
			printf("\nYou entered create database\n");
			if(create(arr,head) == success)
			{
			    flag1 =1;
			    printf("\nSuccessfully created\n");
			}
			else
			{
			    printf("\nCreation failed\n");
			}
			}
			else
			{
			    printf("\nSuccessfully created\n");
			}
			break;
		    case 2:
			printf("\nYou entered Display database\n");
			if(display(arr) == success)
			{
			    printf("\nDisplay is successfull\n");
			}
			else
			{
			    printf("\nDisplay is failed\n");
			}
			break;
		    case 3:
			printf("\nyou entered Search database\n");
			char user[20];
			printf("\nEnter the word to search : ");
			scanf("%s",user);
			if(search(arr,user) == success)
			{
			    printf("\nSearching is done\n");
			}
			else
			{
			    printf("\nSearching failed\n");
			}
			break;
		    case 4:
			printf("\nYou entered Save database\n");
			char file[20],*cmp;
			printf("\nEnter the filename to save : ");
			scanf("%s",file);
			cmp = strstr(file,".");
			if(strcmp(cmp,".txt") == 0)
			{
			    FILE *fptr = fopen(file,"w");
			    if(save(arr,fptr) == success)
			    {
				printf("\nSaving of file is done\n");
			    }
			    else
			    {
				printf("\nSaving of file is failure\n");
			    }
			}
			else
			{
			    printf("\nEnter file in a .txt format\n");
			}
			break;
		    case 5:
			if(flag2 == 0)
			{
			printf("\nyou Entered Update database\n");
			printf("\nEnter the file name : ");
			scanf("%s",file);
			cmp = strstr(file,".");
			if(strcmp(cmp,".txt") == 0)
			{
			    FILE *fptr = fopen(file,"r");
			    printf("File is %s\n",file);
			    if(update(fptr,arr,&head) == success)
			    {
				flag2 =1;
				printf("\nUpdating of file is Done\n");
			    }
			    else
			    {
				printf("\nUpdating of file is Failure\n");
			    }
			}
			else
			{
			    printf("\nPlease pass .txt file\n");
			}
			}
			else
			{
				printf("\nUpdating of file is Done\n");
			}
			break;
		    case 6:
			return 0;
		    default :
			printf("\nEnter the correct Choice\n");
		}
	    }
	}
    }
    return 0;
}

