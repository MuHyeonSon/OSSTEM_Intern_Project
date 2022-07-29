#include <iostream>

using namespace std;

int main()
{	
	int user_input = 11;
	while (user_input != 10)
	{
		cout << "************메뉴를 선택하세요***********" << endl;
		cout << endl;
		cout << "(1) 환자조회" << endl;
		cout << endl;
		cout << "(2) 환자추가" << endl;
		cout << endl;
		cout << "(3) 환자삭제" << endl;
		cout << endl;
		cout << "(4) 환자수정" << endl;
		cout << endl;
		cout << "(5) 환자저장" << endl;
		cout << endl;
		cout << "(6) 환자불러오기(Data Base or File)" << endl;
		cout << endl;
		cout << "(7) 환자복사" << endl;
		cout << endl;
		cout << "(8) export(csv file)" << endl;
		cout << endl;
		cout << "(9) import(csv file)" << endl;
		cout << endl;
		cout << "(10) 프로그램 종료" << endl;
		cout << endl;
		cout << "****************************************" << endl;
		cout << "번호 : ";
		cin >> user_input;
		cout << endl;

		if ((user_input > 11) || (user_input < 1)) //메뉴 번호 밖에 범위의 숫자가 입력으로 들어왔을 때경고메세지 출력!
		{
			cout << "잘못된 입력입니다. 다시 입력하세요!"<< endl;
			cout << endl;
		}
		else if (user_input == 10)
		{
			cout << "프로그램을 종료합니다!" << endl;
			exit(0);
		}
	}
	
	return 0;

}
