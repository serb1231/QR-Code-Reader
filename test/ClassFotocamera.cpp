#include <fotocamera.hpp>

#include "testasserts.hpp"

int main() {
fotocamera fcam=fotocamera();

fcam.InitWebcam();
if(fcam.checkOpenWebcam()){
    std::cout<<"Succsess"<<std::endl;
    fcam.TakeFoto();
    fcam.OpenFoto();
}else{
    std::cout<<"Fail"<<std::endl;
}
  return 0;
}