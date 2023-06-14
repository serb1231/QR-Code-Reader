#include <ZXEncoder.hpp>
#include <stdio.h>

int main()
{

	auto enc = ZX_Encoder();

	std::string err = enc.encode_text_QRcode("test text for encoding", "HAJAJAJ", "/home/maxi/Hallo/", 100, 0);
	std::cout << err << std::endl;

	return 0;
}
