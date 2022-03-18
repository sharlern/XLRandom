#include "XLRandom.h"
#include <iostream>
using namespace std;

void main()
{
	XLRandom random;
	const int count = 256 * 256;
	uint64_t pre[256]{ 0 };
	unsigned char arr[count]{ 0 };

	int times = 1;
	while (true)
	{
		
		random.GetRandom(count, arr);

		int a = count;
		while (a--) {
			// cout << int(arr[a]) << "\t";
			++pre[arr[a]];
		}
		cout << "\n" << endl;

		int t = 256;
		while (t--)
		{
			cout << pre[t] * 10000 / count / times << (t % 15 == 0 ? "\n" : "\t");

		}
		cout << "\n" << endl;
		++times;
	}
	

}