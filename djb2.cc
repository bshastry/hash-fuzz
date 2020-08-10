#include <stdint.h>
#include <string>
#include <map>
#include <fstream>

using namespace std;

namespace {
unsigned djb2Hash(string const& input)
{
    unsigned hash = 5381;
    for (auto c: input) {
        hash = (hash << 5) + hash + c; /* hash * 33 + c */
    }
    return hash;
}
}

/// Maps DJB2 hash to IPv4 address
static map<unsigned, unsigned> s_HashMap;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t len)
{
	if (len != 4)
		return 0;

	// Convert data[3].data[2].data[1].data[0] to an integer
	unsigned ipaddress = (data[0] << 24 |
			data[1] << 16 |
			data[2] << 8 |
			data[3]);

	string input{data, data + len};
	unsigned h = djb2Hash(input);
	if (s_HashMap.count(h))
	{
		if (s_HashMap[h] != ipaddress)
		{
			ofstream f("collisions.txt", ios::app);
			f << "Hash: " << h << endl;
			f << "Input 1: " << s_HashMap[h] << endl;
			f << "Input 2: " << ipaddress << endl;
		}
	}
	else
		s_HashMap.emplace(h, ipaddress);
	return 0;
}
