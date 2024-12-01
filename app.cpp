#include<iostream>
#include<fstream>
#include<cstring>
#include<algorithm>
#include<iomanip>
#include<map>
#include<limits>
#include<ctime>
using namespace std;

//This is a basic quiz application that uses concepts like file handling, OOPS, random, map etc.


class problem //Encapsulating details of a problem into a single object
{
	public:
	string cat,ques,c1,c2,c3,c4,ans;
};

problem a[30];
int i,p[30],flag[10],score=0;
map<string,int> total,answered;

char ch,userans[10];
string categories[5]={"General","Science","Inventions","Sports","Personalities"};

void extract() //This function extracts the questions and options from the text file and stores it in the struct variable
{
	ifstream fin;
	fin.open("questions.txt",ios::in);
	for(i=0;i<30;++i)
	{
		getline(fin,a[i].cat);
		getline(fin,a[i].ques);
		getline(fin,a[i].c1);
		getline(fin,a[i].c2);
		getline(fin,a[i].c3);
		getline(fin,a[i].c4);
		getline(fin,a[i].ans);
	}

}


void conduct()//This function conducts the quiz and evaluates marks.
{
	score=0;
	for(i=0;i<10;++i)
	{
		flag[i]=0;     //An array to store marks for each of the question attempted
	}
	for(i=0;i<5;++i)
	{
		total[categories[i]]=0;
		answered[categories[i]]=0;;
	}
	for(i=0;i<30;++i)
	{
		p[i]=i; //An array to store values from 0 to 29 which can be shuffled later
	}
	srand(time(NULL));
	random_shuffle(&p[0],&p[29]); //shuffles the array p and the program will use the first 10 elements to select the question
	system("cls");
	for(i=0;i<10;++i)
	{
		cout<<endl;
		cout<<"Category : "<<a[p[i]].cat<<endl<<endl;
		total[a[p[i]].cat]++;
		cout<<i+1<<")"<<a[p[i]].ques<<endl<<endl;
		cout<<a[p[i]].c1<<endl;
		cout<<a[p[i]].c2<<endl;
		cout<<a[p[i]].c3<<endl;
		cout<<a[p[i]].c4<<endl;
		enter:
		cout<<endl<<"Enter your answer : ";
		cin>>userans[i];
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		userans[i]=tolower(userans[i]);
		if(userans[i]<'a' || userans[i]>'d')
		{
			cout<<"INVALID! Please enter a valid choice.";
			goto enter;
		}
		if(a[p[i]].ans[0]==userans[i])
		{
			score+=5;
			flag[i]=5;
			answered[a[p[i]].cat]++;
		}
		system("cls");
	}
	cout<<endl<<"Congratulations. You have completed the quiz.\nYou answered "<<score/5<<" out of 10 questions correctly. "<<endl<<endl;
	cout<<"Here are your answers !! "<<endl<<endl;
	for(i=0;i<10;++i)
	{
		cout<<"Question Category : "<<a[p[i]].cat<<endl;
		cout<<"Question : "<<a[p[i]].ques<<endl;
		cout<<"Correct Answer : "<<a[p[i]].ans<<endl;
		cout<<"Your answer : "<<userans[i]<<endl;
		cout<<"Marks Awarded : "<<flag[i]<<endl<<endl;

	}
	cout<<"Category Wise Score -> "<<endl<<endl;
	for(i=0;i<5;++i)
	{

		if(total[categories[i]]>0)
		{
			cout<<categories[i]<<" : "<<fixed<<setprecision(2)<<((float)answered[categories[i]]/(float)total[categories[i]])*100<<"%"<<endl;
		}
	}
	cout<<endl<<"Your Total Score is :  "<<score<<" out of 50."<<endl<<endl;
}



void mainmenu() //Function to give general instructions about the quiz
{
	mainmenu:
	system("cls");

	cout<<endl<<"HEY THERE! WELCOME TO THE THE QUIZ APPLICATION!!\n.\n\n";
	cout<<"\nGeneral Instructions :";
	cout<<"\n-> The quiz will contain 10 questions asked one at a time.";
	cout<<"\n-> Each question will have 4 answers. The user has to choose the correct one. ";
	cout<<"\n-> When the user submits his answer, the program will evaluate it against stored answer for the specific question. ";
	cout<<"\n-> All the questions will be evaluated in the similar manner & marks will be assigned to the correctly chosen answers.";
	cout<<"\n-> At the end it will display the marks you've scored. ";
	cout<<"\n\n->IMPORTANT NOTE : \nIf you enter a string as input, program will take the first character of the string as answer and ignore the rest..";

	choice:
	cout<<"\n\na)Start the Quiz\nb)Exit\n";
	cout<<"Enter choice :";
	cin.get(ch);
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
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
		cout<<endl<<"INVALID CHOICE! Press any key. ";
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		goto choice;
	}

	cout<<"Going back to MAINMENU.\n";
	system("pause");
	goto mainmenu;
}



int main()
{
	extract();
	mainmenu();
}
