//#include "Drawing.h"
#include "Rest\Restaurant.h"

int main()
{

	Restaurant* pRest = new Restaurant;
    pRest->Read();
	pRest->RunSimulation();
	cout << "function is ............read";
	delete pRest;

	system("pause");
	return 0;
}
