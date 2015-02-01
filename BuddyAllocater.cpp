#include "BuddyAllocater.h"

BuddyAllocater::BuddyAllocater(double tMemory_)
{
    pMemory = 1024*tMemory_;
    totalMemory = 1024*tMemory_;
}

//가용가능한 메모리를 리턴한다.
double BuddyAllocater::GetMemoryLeft()
{
	return pMemory;
}

//메모리 할당을 요청한다. 요청된 메모리가 가용 가능 메모리보다 클 경우 거절당한다.
int BuddyAllocater::AskAllocation()
{

	double askMemory = 0;

	cout << endl << "할당하려는 메모리 크기(KB): ";
	cin >> askMemory;


	cout << askMemory << " KB 메모리가 요청되었다." << endl;


	if (askMemory <= 2)
	{
		cout << "하한선은 2KB이다. 강제종료" << endl;
		return 0;
	}

	//가용 메모리가 요구 메모리보다 큰경우 할당
	if (pMemory > askMemory)
	{
		double MemoAllocated = Allocater(askMemory, 1);


		cout << MemoAllocated << " KB메모리가 할당되었다 " << endl;
		
		
		pMemory -= MemoAllocated;
		
		
		cout << pMemory << " KB가용 가능 " << endl;

		return 1;
	}
	else
	{

		//그렇지 못한 경우
		cout << "충분한 메모리 공간이 없다." << endl;
		return 0;
	}
}

//GUI를 사용하는 경우
double BuddyAllocater::AskAllocation(double other)
{

    double askMemory = other;

    //가용 메모리가 요구 메모리보다 큰경우 할당
    if (pMemory > askMemory)
    {
        double MemoAllocated = Allocater(askMemory, 1);


        cout << MemoAllocated << " KB메모리가 할당되었다 " << endl;


        pMemory -= MemoAllocated;


        cout << pMemory << " KB가용 가능 " << endl;

        return MemoAllocated;
    }
    else
    {

        //그렇지 못한 경우
        cout << "충분한 메모리 공간이 없다." << endl;
        return 0;
    }
}







/*
재귀하면 이전 단계로 부터 time을 전달 받는다.
해당 time변수는 시행 횟수를 표시한다.
이를 바탕으로 상한선과 하한선을 2배씩 계속 증가시키며
할당하려는 메모리가 상한선과 하한선 사이에 존재하는지 검사한다.
하한과 상한 사이에 할당 메모리의 크기가 존재할시 메모리를 할당하고 재귀에서 벗어난다.
*/
 double BuddyAllocater::Allocater(double askMemory, int times)
{
	//상한과 하한은 각각 2의 제곱수이다.
	//검사용 상한선과 하한선은 2배 차이난다.
	//재귀할수록 검사용 상한선과 하한선은 2배가 된다.
	double lowerBlock = pow(2.0, times++);
	double upperBlock = pow(2.0, times);
	
	//상한과 하한 사이에 메모리 크기가 있는지 검사.
	if (askMemory > lowerBlock && askMemory <= upperBlock)
	{
		return upperBlock;
	}
	else
	{
		//상한선과 하한선 사이에 메모리가 존재하지 않을 경우, 상한선과 하한선을 한 배수 높인다.
		return Allocater(askMemory, times);
	}
	
}


//메모리를 릴리즈 한다.
int BuddyAllocater::ReleaseMemory()
{
	cout << endl << "릴리즈할 메모리: ";
	
	double askedMemory;
	cin >> askedMemory;

	cout << askedMemory << " kb 릴리즈 요청되었다." << endl;

	if (askedMemory <= 2)
	{
		cout << "하한선은 2KB이다. 강제종료" << endl;
		return 0;
	}

	//릴리즈를 요구하는 메모리가 전체 메모리보다 큰지 검사한다.
	if ((pMemory + askedMemory) > totalMemory)
	{
		cout << "오버플로우" << endl;

		return 0;
	}
	else
	{
		//Allocater를 통해 리턴할 블록 크기를 계산한다.
		//Allocater는 해당 메모리 크기 보다 큰 최소 2^n값을 리턴해주기 때문.
		double returnMemory = Allocater(askedMemory, 1);
		cout << returnMemory << " 가 릴리즈 되었다. " << endl;

		pMemory += returnMemory;


		cout << "마지막 가용 메모리" << pMemory << endl;

		return 1;
	}
}



//GUI를 사용하는 경우
double BuddyAllocater::ReleaseMemory(double other)
{
    double askedMemory;
askedMemory = other;

    cout << askedMemory << " kb 릴리즈 요청되었다." << endl;

    if (askedMemory <= 2)
    {
        cout << "하한선은 2KB이다. 강제종료" << endl;
        return 0;
    }

    //릴리즈를 요구하는 메모리가 전체 메모리보다 큰지 검사한다.
    if ((pMemory + askedMemory) > totalMemory)
    {
        cout << "오버플로우" << endl;

        return 0;
    }
    else
    {
        //Allocater를 통해 리턴할 블록 크기를 계산한다.
        //Allocater는 해당 메모리 크기 보다 큰 최소 2^n값을 리턴해주기 때문.
        double returnMemory = Allocater(askedMemory, 1);
        cout << returnMemory << " 가 릴리즈 되었다. " << endl;

        pMemory += returnMemory;


        cout << "마지막 가용 메모리" << pMemory << endl;

        return returnMemory;
    }
}
