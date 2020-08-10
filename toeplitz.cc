#include <stdint.h>
#include <rte_thash.h>
#include <map>
#include <fstream>

using namespace std;

static uint8_t const rssKey[40] = {
		0x40, 0x78, 0x93, 0x45, 0x11, 0x09, 0x87, 0x37, 0x40, 0x88,
		0x40, 0x78, 0x93, 0x45, 0x11, 0x09, 0x87, 0x37, 0x40, 0x88,
		0x40, 0x78, 0x93, 0x45, 0x11, 0x09, 0x87, 0x37, 0x40, 0x88,
		0x40, 0x78, 0x93, 0x45, 0x11, 0x09, 0x87, 0x37, 0x40, 0x88
	};

static map<unsigned, unsigned> hashMap;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
	if (size != 4)
		return 0;

	unsigned input = data[3] << 24 |
		data[2] << 16 |
		data[1] << 8 |
		data[0];
	unsigned hash = rte_softrss(&input, 1, rssKey);
	if (hashMap.count(hash))
	{
		if (hashMap[hash] != input)
		{
			ofstream of("toeplitz-collisions.txt");
			of << "Hash: " << hash << endl;
			of << "Input 1: " << hashMap[hash] << endl;
			of << "Input 2: " << input << endl;
		}
	}
	else
		hashMap.emplace(hash, input);
	return 0;
}
