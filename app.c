#include<stdio.h>
#include<string.h>
#include<time.h>
#include<process.h>
#include<conio.h>
#include<time.h>
#include<ctype.h>
#include<stdlib.h>
#define MAXCHAR 1000


struct problem
{
	char cat[20],ques[150],c1[50],c2[50],c3[50],c4[50],ans[10];
};


struct problem a[30];
int i,j,k,p[30],flag[10],total[5],answered[5],score=0;
char ch,userans[10];
char categories[5][25];

// A utility function to swap two integers
void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void countCategories(char *dupe) //For counting the questions attempted in a particular category
{
	int b,sign=0;
	for(b=0;b<5;++b)
	{
		if(strcmp(categories[b],dupe)==0)
		{
			total[b]++;
			sign=1;
			break;
		}
	}
	if(!sign)
	{
		strcpy(categories[k],dupe);
		total[k]++;
		k++;
	}
}


void extract() //This function extracts the questions and choices from the text file and stores it in the struct variable
{
	FILE *fin;
	fin=fopen("questions.txt","r");
	for(i=0;i<30;++i)
	{
		fgets(a[i].cat,MAXCHAR,fin);
		fgets(a[i].ques,MAXCHAR,fin);
		fgets(a[i].c1,MAXCHAR,fin);
		fgets(a[i].c2,MAXCHAR,fin);
		fgets(a[i].c3,MAXCHAR,fin);
		fgets(a[i].c4,MAXCHAR,fin);
		fgets(a[i].ans,MAXCHAR,fin);
	}

}


void conduct()//This function conducts the quiz and evaluates marks.
{
	score=0,k=0;
	for(i=0;i<10;++i)
	{
		flag[i]=0;     //An array to store marks for each of the question attempted
	}
	for(i=0;i<5;++i)
	{
		total[i]=0;
		answered[i]=0;
	}
	for(i=0;i<30;++i)
	{
		p[i]=i; //An array to store values from 0 to 29 which can be shuffled later
	}
	srand(time(NULL));
	int add;
    for (add = 29; add >0; add--) //shuffles the array p and the program will use the first 10 elements to select the question
    {
          // Pick a random index from 0 to add
        int j = rand() % (add+1);

        // Swap p[add] with the element at random index
        swap(&p[add], &p[j]);
    }
	system("cls");
	for(i=0;i<10;++i)
	{
		fputs("\nCategory : ",stdout);
		puts(a[p[i]].cat);
		countCategories(a[p[i]].cat);
		printf("%d) ",i+1);
		puts(a[p[i]].ques);
		puts(a[p[i]].c1);
		puts(a[p[i]].c2);
		puts(a[p[i]].c3);
		puts(a[p[i]].c4);
		enter:
		puts("\nEnter your answer : ");
		scanf(" %c",&userans[i]);
		while ((getchar()) != '\n'); 		//To clean input buffer
		userans[i]=tolower(userans[i]);
		if(userans[i]<'a' || userans[i]>'d')
		{
			puts("\nINVALID! Please enter a valid choice.");
			goto enter;
		}
		if(a[p[i]].ans[0]==userans[i])
		{
			score+=5;
			flag[i]=5;
			for(j=0;j<5;++j)
			{
				if(strcmp(categories[j],a[p[i]].cat)==0)
				{
					answered[j]++;
				}
			}
		}
		system("cls");
	}

	printf("\nCongratulations. You have completed the quiz.\nYou answered %d out of 10 questions correctly. \n\n",score/5);
	puts("Here are your answers !! \n");
	for(i=0;i<10;++i)
	{
		printf("Question Category : %s",a[p[i]].cat);
		printf("Question : %s",a[p[i]].ques);
		printf("Correct Answer : %c\n",a[p[i]].ans[0]);
		printf("Your answer : %c\n",userans[i]);
		printf("Marks Awarded : %d\n\n",flag[i]);

	}
	printf("******************** CATEGORY WISE SCORE ********************\n\n");
	for(i=0;i<5;++i)
	{
		if(total[i]>0)
		{
			printf("%s-> %0.2f %% \n",categories[i],((float)answered[i]/(float)total[i])*100);
		}
	}
	printf("\nYour Total Score is : %d out of 50.\n\n",score);
}



void mainmenu() //Function to give general instructions about the quiz
{
	mainmenu:
	system("cls");

	puts("\nHEY THERE! WELCOME TO THE THE QUIZ APPLICATION!!\n .\n");
	puts("\nGeneral Instructions :");
	puts("-> The quiz will contain 10 questions asked one at a time.");
	puts("-> Each question will have 4 answers. The user has to choose the correct one. ");
	puts("-> When the user submits his answer, the program will evaluate it against stored answer for the specific question. ");
	puts("-> All the questions will be evaluated in the similar manner & marks will be assigned to the correctly chosen answers.");
	puts("-> At the end it will display the marks you've scored. ");
	puts("\n->IMPORTANT NOTE : \nIf you enter a string as input, program will take the first character of the string as answer and ignore the rest.");

	choice:
	printf("\n\na)Start the Quiz\nb)Exit\n");
	printf("Enter choice :");
	scanf(" %c",&ch);
	while ((getchar()) != '\n');		//To clean input buffer
	ch=tolower(ch);
	if(ch=='b')
	{
		exit(0); //exits the program
	}
	else if(ch=='a')
	{
			conduct();      //calls conduct function when the user presses 1
	}
	else
	{
		printf("\nINVALID CHOICE! ");
		goto choice;
	}

	printf("Going back to MAINMENU.\n");
	system("pause");
	goto mainmenu;
}



int main()
{
	extract();
	mainmenu();
	return 0;
}
