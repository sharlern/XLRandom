#pragma once
typedef unsigned long long uint64_t;
#define UINT64_MAX       0xffffffffffffffffui64

class XLRandom
{
public:
	XLRandom();
	~XLRandom();

	static void RandomThread();
	int GetRandom(uint64_t count, unsigned char* random);
};

