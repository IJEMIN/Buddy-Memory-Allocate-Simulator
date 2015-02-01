#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

/*
피지컬 메모리량을 전달받아, 피지컬 메모리 내에 적절하게 메모리를 할당하는 클래스
상한과 하한을 2^n 꼴로 정한 뒤, 그 이하와 그 이상은 할당되지 않는다.
할당 요청시, 요청된 크기보다 큰 2^n 값 중, 가장 작은 크기 만큼 메모리 공간을 제공한다.

|!| 할당 단위는 KB이다. |!|

*/


/*
메모리를 가정하고 실행하는 시뮬레이션으로서 동작한다.

실제 메모리를 할당하고자 할때는 포인터 변수를 생성한후 KB와 변수의 크기 사이의 단위 변환을 고려하여 배수를 취하여 Allocater가 리턴하는 값만큼
malloc(할당시), free(릴리즈시) 등의 메모리 함수를 통해 할당, 해제를 시행해주는 스크립트를 RelaseMemory, Allocater에 추가하면된다.

/!/이 경우 실제 운영체제의 메모리에 간섭하므로 반드시 초기 설정때 가용메모리 보다 피지컬 메모리를 높게 설정해서는 안된다/!/


*/

//해당 클래스의 인터페이스는 제공하지 않는 방향으로 작성한다. 호출하는 쪽 스크립트에서 각 매소드를 호출하는 인터페이스를 작성.
//현재는 매소드 내부에서 콘솔 출력을 통해 결과값과 정보를 출력하도록 되어있다. 이후 콘솔 입출력을 인터페이스를 통해서 하도록만 수정해야 한다.

class BuddyAllocater
{

private:

	//가용 메모리
    double pMemory;

	//전체 메모리
    double totalMemory;

public:
	//생성자
	BuddyAllocater(double tMemory_);

	double GetMemoryLeft();


	//메모리 할당을 요청한다. 가용 메모리가 적을 경우 거부한다. 실제 할당을 위해 내부에서 Allocater를 호출한다.
	int AskAllocation();

    //GUI를 사용할 경우, 콘솔로 입력 받지 않고, GUI클래스로 부터 값을 전달받는다. 오버로드.
    //이경우 할당된 값을 리턴한다. 0의 경우 실패.
    double AskAllocation(double other);


	//AskAllocation에서 호출된다. 상한선과 하한선 사이에 요구되는 메모리 보다 큰, 최소 2^n값을 찾아 리턴한다.
	//요구되는 2^n값은 재귀로 찾는다.
	double Allocater(double askedMemory, int times);

	//메모리를 릴리즈 한다.
	int ReleaseMemory();

    //GUI를 사용하는 경우
    double ReleaseMemory(double other);



	//실제로 메모리 주소를 검사하여 물리적인 할당을 실행한다.
	//int RunSimulation();

};
