#include <Decoder.hpp>
#include <stdio.h>
#include <QualityImprove.hpp>
int main(){

    cv::Mat image = cv::imread("../../test_images/QR_another_real_test_foto_2.jpg");

    // This gave a sharper image as a result
    cv::Mat result_detailEnhance;
    detailEnhance(image,result_detailEnhance, 10,0.15f);
    cv::imshow("Detail Enhances Image", result_detailEnhance);

    cv::Mat result1 = DenoiseTakeFromFolder("../../test_images/SameImageBlurry/", true);
    cv::imshow("plm1", result1);
    
    cv::Mat result2 = TestNoiseSameImageAndDenoise("../../test_images/SameImageBlurry/WhatsApp Image 2023-06-11 at 7.10.18 PM.jpeg");
    cv::imshow("plm2", result2);
    cv::imshow("plm2", image);
    cv::waitKey();

    return 0;

}

