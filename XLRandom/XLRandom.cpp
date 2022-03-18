/*********************
真随机数生成
*********************/

#include "XLRandom.h"
#include <thread>

namespace{
	struct RandomStruct
	{
		bool run;
		uint64_t val;

		void Init()
		{
			val = 0;
			run = true;
		}
	};
	RandomStruct randomStruct;
}


void XLRandom::RandomThread()
{
	while (randomStruct.run)
	{
		randomStruct.val++;
	}
}

XLRandom::XLRandom()
{
	randomStruct.Init();
}

XLRandom::~XLRandom()
{

}


int XLRandom::GetRandom(uint64_t count, unsigned char* random)
{
	uint64_t last = 0, current = 0;

	std::thread thr(RandomThread);

	while ((current = randomStruct.val) == 0) {}
	random[0] = current & 0xFF;
	last = current;

	for (uint64_t i = 1; i < count; i++) {
		while (true) {
			if (last < (current = randomStruct.val) ? current - last > 256 : current + UINT64_MAX - last > 256) {
				random[i] = current & 0xFF;
				last = current;
				break;
			}
		}
	}

	randomStruct.run = false;
	thr.join();

	randomStruct.Init();

	return 0;
}




