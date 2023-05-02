#include <stdlib.h> 
#include <time.h> 
using namespace std;
int getRandomNumber(int min, int max)
{
	srand(time(NULL));
	int num = min + rand() % (max - min + 1);

	return num;
}
