#include <iostream>
#include <string>
using namespace std;

enum enQuestionLevel { EasyLevel = 1, MediumLevel = 2, HardLevel = 3, MixLevel = 4 };

enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enQuestionLevel QuestionLevel;
	enOperationType OperptionType;
	int PlayerAnswer = 0;
	int CorrectAnswer = 0;
	bool AnswerResult = false;

};

struct stQuizz
{
	stQuestion QuestionList[1000];
	short NumberOfQuesstions = 0;
	enQuestionLevel QuestionLevel;
	enOperationType OpType;
	short NumberOfRightAnswer = 0;
	short NumberOfWrongAnswer = 0;
	bool IsPass = false;
};

int RandomNumber(int From, int To)
{
	//Function generater a random number

	int RandomNum = rand() % (To - From + 1) + From;

	return RandomNum;
}

short ReadHowManyQuestion()
{
	short NumberOfQuestion = 0;

	do
	{
		cout << "How Many Question do you want to Answer ??";
		cin >> NumberOfQuestion;

	} while (NumberOfQuestion <1 || NumberOfQuestion > 1000);

	return NumberOfQuestion;

}

enQuestionLevel ReadLevelOfQuestion()
{
	short LevelOfQuestion = 0;

	do
	{
		cout << "Enter Questions Level. [1]Easy, [2]Medium, [3]Hard, [4]Mix ? ";
		cin >> LevelOfQuestion;

	} while (LevelOfQuestion < 1 || LevelOfQuestion >4);

	return (enQuestionLevel)LevelOfQuestion;
}

enOperationType ReadOperationType()
{
	short OperationType = 0;

	do
	{
		cout << "Enter Opertion Type. [1]Add, [2]Sub, [3]Mul, [4]Div, [5]Mix ?? ";
		cin >> OperationType;

	} while (OperationType <1 || OperationType >5);

	return (enOperationType)OperationType;
}

int SimpleCalculeter(int Number1, int Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mul:
		return Number1 * Number2;
	case enOperationType::Div:
		return Number1 / Number2;
	}

}

void SetScreenColor(bool Right)
{
	if (Right)
	{
		system("color 2F");// turn screen to Green	
	}
	else
	{
		system("color 4F");// turn screen to Red and start small sound 
		cout << "\a";
	}
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OperationType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionLevel::MixLevel)
	{
		QuestionLevel = (enQuestionLevel) RandomNumber(1, 3);
	}

	if (OperationType == enOperationType::MixOp)
	{
		OperationType = (enOperationType)RandomNumber(1, 4);
	}

	Question.OperptionType = OperationType;

	switch (QuestionLevel)
	{
	case enQuestionLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		Question.CorrectAnswer = SimpleCalculeter(Question.Number1, Question.Number2,Question.OperptionType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	case enQuestionLevel::MediumLevel:

		Question.Number1 = RandomNumber(10, 100);
		Question.Number2 = RandomNumber(10, 100);
		Question.CorrectAnswer = SimpleCalculeter(Question.Number1, Question.Number2, Question.OperptionType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	case enQuestionLevel::HardLevel:
		Question.Number1 = RandomNumber(100, 1000);
		Question.Number2 = RandomNumber(100, 1000);
		Question.CorrectAnswer = SimpleCalculeter(Question.Number1, Question.Number2, Question.OperptionType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	}


	return Question;

}

void GenerateQuizzQuestions(stQuizz &Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuesstions; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);
	}

}

string GetOpTypeSymbo(enOperationType Op)
{
	switch (Op)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mul:
		return "*";
	case enOperationType::Div:
		return "/";
	case enOperationType::MixOp:
		return "Mix";
	}
}

string GetQuestionLevelText(enQuestionLevel Level)
{
	string QuestionLevel[4] = { "Easy","Meduim","Hard","Mix" };
	return QuestionLevel[Level - 1];
}

void PrintTheQuestion(stQuizz Quizz,short NumberQuestion)
{
	cout << "\n\n";
	cout << "Question [" << NumberQuestion + 1 << "/" << Quizz.NumberOfQuesstions << "]" << endl;
	cout << Quizz.QuestionList[NumberQuestion].Number1 << endl;
	cout << Quizz.QuestionList[NumberQuestion].Number2 << " ";
	cout << GetOpTypeSymbo(Quizz.QuestionList[NumberQuestion].OperptionType) << endl;
	cout << "------------ \n";

}

int ReadPlayerAnswer()
{
	int PlayerAnswer = 0;
	cin >> PlayerAnswer;
	return PlayerAnswer;
}

void CorrectTheQuestionAnswer(stQuizz &Quizz, short NumberQuestion)
{
	if (Quizz.QuestionList[NumberQuestion].PlayerAnswer != Quizz.QuestionList[NumberQuestion].CorrectAnswer)
	{
		Quizz.QuestionList[NumberQuestion].AnswerResult = false;
		Quizz.NumberOfWrongAnswer++;

		cout << "Wrong Answer :-( \n";
		cout << "The right answer is : " << Quizz.QuestionList[NumberQuestion].CorrectAnswer;
		cout << "\n";
	}
	else
	{
		Quizz.QuestionList[NumberQuestion].AnswerResult = true;
		Quizz.NumberOfRightAnswer++;
	     
		cout << "Right Answer :-) \n";
	
	}

	SetScreenColor(Quizz.QuestionList[NumberQuestion].AnswerResult);
}

void AskAndCorrectQuestionListAnswer(stQuizz& Quizz)
{
	for (short NumberQuestion = 0; NumberQuestion < Quizz.NumberOfQuesstions; NumberQuestion++)
	{
		PrintTheQuestion(Quizz,NumberQuestion);
		Quizz.QuestionList[NumberQuestion].PlayerAnswer = ReadPlayerAnswer();
		CorrectTheQuestionAnswer(Quizz, NumberQuestion);

	}

	Quizz.IsPass = (Quizz.NumberOfRightAnswer > Quizz.NumberOfWrongAnswer);

	//The Nurmal line is :

	/* 
	if(Quizz.NumberOfRightAnswer > Quizz.NumberOfWrongAnswer)
	{
	Quizz.NumberOfWrongAnswer++;
	}
	else
	{
	Quizz.NumberOfRightAnswer++;
	}

	*/
}

string GetFinalResultsText(bool Pass)
{
	if (Pass)
		return "Win :-)";
	else
		return "Fail :-(";
}

void PrintQuizzResults(stQuizz Quizz)
{
	cout << endl << endl;
	cout << "--------------------------------------------------\n";
	cout << "     Final Results is  " << GetFinalResultsText(Quizz.IsPass) << endl;
	cout << "--------------------------------------------------\n";

	cout << "Number of Questions : " << Quizz.NumberOfQuesstions << endl;
	cout << "Question Level : " <<  GetQuestionLevelText(Quizz.QuestionLevel) << endl;
	cout << "Operation      : " << GetOpTypeSymbo(Quizz.OpType) << endl;
	cout << "Number of Right Answers : " << Quizz.NumberOfRightAnswer << endl;
	cout << "Number of Wrong Answers : " << Quizz.NumberOfWrongAnswer << endl;
	cout << "--------------------------------------------------\n";

	SetScreenColor(Quizz.IsPass);

}

void PlayMathGame()
{
	stQuizz Quizz;
	
	Quizz.NumberOfQuesstions = ReadHowManyQuestion();
	Quizz.QuestionLevel = ReadLevelOfQuestion();
	Quizz.OpType = ReadOperationType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswer(Quizz);
	PrintQuizzResults(Quizz);

}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{

	char PlayGame = 'Y';

	do
	{

		ResetScreen();
		PlayMathGame();
		cout << endl << "Do you to play agian?? Y/N??";
		cin >> PlayGame;

	} while (PlayGame == 'Y' || PlayGame == 'y');

}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}