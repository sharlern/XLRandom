/*****************************************************************************
MIT License

Copyright (c) 2022 sharlern/wood

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*****************************************************************************/

/*********************
Generate an real random.
*********************/

#include "XLRandom.h"
#include <thread>

namespace{
	struct RandomStruct
	{
		bool run;
		volatile uint64_t val;

		void Init()
		{
			val = 0;
			run = true;
		}
	};
	RandomStruct f_randomStruct;
}


void XLRandom::RandomThread()
{
	while (f_randomStruct.run)
	{
		f_randomStruct.val++;
	}
}

XLRandom::XLRandom()
{
	f_randomStruct.Init();
}

XLRandom::~XLRandom()
{

}


int XLRandom::GetRandom(uint64_t count, unsigned char* random)
{
	if (count < 1 || random == nullptr) {
		return -1;
	}

	uint64_t last = 0, current = 0;

	std::thread thr(RandomThread);

	while ((current = f_randomStruct.val) == 0) {}
	random[0] = current & 0xFF;
	last = current;

	for (uint64_t i = 1; i < count; i++) {
		while (true) {
			if (last < (current = f_randomStruct.val) ? current - last > 256 : current + UINT64_MAX - last > 256) {
				random[i] = current & 0xFF;
				last = current;
				break;
			}
		}
	}

	f_randomStruct.run = false;
	thr.join();

	f_randomStruct.Init();

	return count;
}




