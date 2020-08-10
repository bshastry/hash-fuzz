#include <boost/crc.hpp>
#include <map>
#include <fstream>

using namespace std;
using namespace boost;

/// Maps hash to IPv4 address
static map<unsigned, unsigned> hashMap;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	if (size != 4)
		return 0;

	crc_32_type hash;
	// IPv4 address data[3].data[2].data[1].data[0]
	unsigned i = (data[0] << 24 |
			data[1] << 16 |
			data[2] << 8 |
			data[3]);

	hash.process_bytes(data, size);
	unsigned cs = hash.checksum();
	if (hashMap.count(cs))
	{
		if (hashMap[cs] != i)
		{
			ofstream of("collision.txt", ios::app);
			of << "Hash: " << cs << endl;
			of << "i1: " << i << endl;
			of << "i2: " << hashMap[cs] << endl;
		}
	}
	else
		hashMap.emplace(cs, i);
	return 0;
}
