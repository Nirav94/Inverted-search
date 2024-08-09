#include "header.h"

status check(invert *head,char *str)            // functon for check files arleady stored or not
{
    if(head == NULL)
    {
	return success;
    }
    else
    {
	invert *temp = head;
	while(temp != NULL)
	{
	    if(strcmp(temp -> arr,str) == 0)
	    {
		return failure;
	    }
	    temp = temp -> link;
	}
	return success;
    }
}

status insert_list(invert **head, char *str)  // function for inserting files in to slist
{
    invert *new = malloc(sizeof(invert));
    if(new == NULL)
    {
	return failure;
    }
    strcpy(new -> arr ,str);
    new -> link = NULL;
    if(*head == NULL)
    {
	*head = new;
	return success;
    }
    invert *temp = *head;
    while(temp->link !=NULL)
    {
	temp = temp->link;
    }
    temp->link =new;

    return success;
}

status create(hash *arr, invert *head)     // function for creating hash table
{
    char str[50];
    int index;
    invert *temp = head;

    while(temp != NULL)
    {
	FILE *fptr = fopen(temp -> arr,"r"); 
	while((fscanf(fptr,"%s",str)) != EOF)
	{
	    if(str[0] >='0' && str[0] <='9')
	    {
		index = 26;
	    }
	    else if((str[0] >= 'A' && str[0] <= 'Z') ||(str[0] >= 'a' && str[0] <= 'z'))
	    {
		char ch = tolower(str[0]);
		index = ch-97;
	    }
	    else
	    {
		index = 27;
	    }

	    if(arr[index].link == NULL)
	    {
		main_node *mnew = malloc(sizeof(main_node));
		sub_node *snew= malloc(sizeof(sub_node));
		strcpy(mnew -> word , str);
		mnew -> f_count = 1;
		mnew -> slink = snew;
		mnew -> mlink = NULL;
		snew -> w_count =1; 
		strcpy(snew -> f_name,temp ->arr);
		snew -> slink = NULL;
		arr[index].link = mnew;
	    }
	    else
	    {
		main_node * mtemp = arr[index].link;
		main_node *mprev = NULL;
		int w_flag=0,f_flag = 0;
		while(mtemp != NULL)
		{
		    mprev = mtemp;
		    if(strcmp(str,mtemp -> word) == 0)
		    {
			f_flag =0;
			w_flag =1;
			sub_node *stemp = mtemp -> slink;
			sub_node *sprev = NULL;
			while(stemp != NULL)
			{
			    sprev = stemp;
			    if(strcmp(stemp -> f_name,temp -> arr) == 0)
			    {
				stemp -> w_count++;
				f_flag = 1;
				break;
			    }
			    else
			    {
				stemp = stemp -> slink;
			    }
			}
			if(f_flag == 0)
			{
			    sub_node *snew= malloc(sizeof(sub_node));
			    strcpy(snew -> f_name , temp -> arr);
			    snew -> w_count =1; 
			    sprev -> slink = snew;
			    snew -> slink = NULL;
			}
		    }
		    if(w_flag == 1)
		    {
			mtemp -> f_count++;
			break;
		    }
		    mtemp = mtemp -> mlink;
		}
		if(w_flag ==0)
		{
		    main_node *mnew = malloc(sizeof(main_node));
		    sub_node *snew = malloc(sizeof(sub_node));
		    strcpy(mnew ->word,str);
		    mnew -> f_count =1;
		    mnew -> slink =snew;
		    mnew -> mlink = NULL;
		    mprev -> mlink = mnew;
		    strcpy(snew ->f_name,temp -> arr);
		    snew -> w_count = 1;
		    snew -> slink = NULL;
		}

	    }
	}
	temp = temp->link;
    }
    return success;
}

status display(hash *arr)                           // function to display output
{
    printf("--------------------------------------------------------------------------------------------\n");
    printf("[Index]\t[Word]\t[File_count]\t[Word_count]\t[filename]\n");
    printf("--------------------------------------------------------------------------------------------\n");
    for(int i =0; i< 28; i++)
    {
	if(arr[i].link != NULL)
	{
	    main_node * prtemp = arr[i].link;
	    while(prtemp != NULL)
	    {
		printf("[%2d]\t",i);
		printf("%-12s\t",prtemp -> word);
		printf("%-10d\t",prtemp -> f_count);
		sub_node *sub_temp = prtemp -> slink;
		while(sub_temp != NULL)
		{
		    printf("%-10d",sub_temp -> w_count);
		    printf("%-15s\t",sub_temp -> f_name);
		    sub_temp = sub_temp->slink;
		}
		prtemp = prtemp -> mlink;
		printf("\n");
	    }
    printf("--------------------------------------------------------------------------------------------\n");
	}
    }
    return success;
}

status search(hash *arr, char *user)           // function to search user given word
{
    int index;
    if(user[0] >='0' && user[0] <='9')
    {
	index = 26;
    }
    else if((user[0] >= 'A' && user[0] <= 'Z') ||(user[0] >= 'a' && user[0] <= 'z'))
    {
	char ch = tolower(user[0]);
	index = ch-97;
    }
    else
    {
	index = 27;
    }
    if(arr[index].link != NULL)
    {
	main_node * mtemp = arr[index].link;
	while(mtemp != NULL)
	{
	    if( strcmp(mtemp -> word,user) == 0)
	    {
		printf("\nWord Matched\n");
		printf("========================\n");
		printf("\nIndex is   : %d\n",index);
		printf("\nfile count : %d\n",mtemp -> f_count);
		sub_node * stemp = mtemp -> slink;
		for(int j =1; j<= mtemp -> f_count; j++)
		{
		    printf("\nword count : %d\n",stemp -> w_count);
		    printf("\nfile name  : %s\n",stemp -> f_name);
		    printf("=====================\n");
		    stemp = stemp -> slink;
		}
		return success;
	    }
	    mtemp = mtemp -> mlink;
	}
    }
    printf("====================================================\n");
    printf("Word is Not Found\n");
    printf("====================================================\n");
    return failure;
}

status save(hash *arr, FILE *fptr)                       // function to save data in to user given file
{
    for(int i=0; i<28; i++)
    {
	main_node *mtemp = arr[i].link;
	if(arr[i].link != NULL)
	{
	    while(mtemp != NULL)
	    {
		fprintf(fptr,"#%d;",i);
		fprintf(fptr,"%s;",mtemp -> word);
		fprintf(fptr,"%d;",mtemp -> f_count);
		sub_node *stemp = mtemp -> slink;
		for(int j=1; j<=mtemp -> f_count; j++)
		{
		    fprintf(fptr,"%d;",stemp -> w_count);
		    fprintf(fptr,"%s;",stemp -> f_name);
		    stemp = stemp -> slink;
		}
		mtemp = mtemp -> mlink;
		fprintf(fptr,"#%s","\n");
	    }
	}
    }
    return success;
}

status update(FILE *fptr1,hash *arr,invert **head)           // function to update a new file
{
    char word[50],f_name[50],temp[150];
    int i,index=0,f_count=0,w_count=0;
    while(fscanf(fptr1,"%s",temp) != EOF)
    {
	if(temp[0] == '#')
	{
	    index = atoi(strtok(temp+1,";"));
	    strcpy(word,(strtok(NULL,";")));
	    f_count = atoi(strtok(NULL,";"));
	    if(arr[index].link == NULL)               // if index of hash table  empty
	    {
		main_node *mnew= malloc(sizeof(main_node));
		if(mnew == NULL)
		{
		    return failure;
		}
		else
		{
		    mnew -> f_count = f_count;
		    strcpy(mnew -> word, word);
		    mnew -> mlink = NULL;
		    mnew -> slink = NULL;
		    for(int i=0; i<f_count; i++)
		    {
			sub_node *snew = malloc(sizeof(sub_node));
			if(snew == NULL)
			{
			    return failure;
			}
			else
			{
			    snew->w_count = atoi(strtok(NULL,";"));
			    strcpy(snew->f_name,(strtok(NULL,";")));
			    free_head(head, snew -> f_name);
			    snew -> slink = NULL;
			    if( mnew->slink == NULL)
			    {
				mnew->slink = snew;
			    }
			    else
			    {
				sub_node* stemp = mnew->slink;
				while(stemp->slink != NULL)
				{
				    stemp = stemp->slink;
				}
				stemp->slink = snew;
			    }
			}
		    }
		}
		arr[index].link = mnew;
	    }
	    else                          // if index of hash table not empty
	    {
		main_node *mtemp = arr[index].link,*mprev = NULL;
		main_node *mnew = malloc(sizeof(main_node));
		if(mnew == NULL)
		{
		    return failure;
		}
		else
		{
		    mnew -> f_count = f_count;
		    strcpy(mnew -> word , word);
		    mnew -> mlink = NULL;
		    mnew -> slink = NULL;
		    for(int i=0; i< f_count; i++)
		    {
			sub_node *snew = malloc(sizeof(sub_node));
			if(snew == NULL)
			{
			    return failure;
			}
			else
			{
			    snew->w_count = atoi(strtok(NULL,";"));
			    strcpy(snew->f_name,(strtok(NULL,";")));
			    free_head(head, snew -> f_name);
			    snew -> slink = NULL;
			    if(mnew->slink == NULL)
			    {
				mnew->slink = snew;
			    }
			    else
			    {
				sub_node* stemp = mnew->slink;
				while(stemp->slink != NULL)
				{
				    stemp = stemp->slink;
				}
				stemp = snew;
			    }

			}
		    }
		}
		while(mtemp->mlink != NULL)
		{
		    mtemp = mtemp -> mlink;
		}
		mtemp->mlink = mnew;
	    }
	}
    }
    return success;
}

status free_head(invert ** head, char *str)       // function to free the saved files
{
    invert * temp = *head;
    invert *prev = NULL;
    while(temp != NULL)
    {
	if(strcmp(temp -> arr, str) == 0) 
	{
	    invert *back = temp -> link;
	    free(temp);
	    if(prev == NULL)
	    {
		*head = back;
	    }
	    else
	    {
		prev -> link = back;
	    }
	    return success;
	}
	prev = temp;
	temp = temp -> link;
    }
    return success;
}

