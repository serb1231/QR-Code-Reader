#include <ZXEncoder.hpp>
#include <stdio.h>

int main(){

    auto enc = ZX_Encoder();

    int err = enc.encode_text_QRcode("test text for encoding","fromMain.jpg","",100,0);

    return err;

}

