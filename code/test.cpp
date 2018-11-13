#include "PCN.h"

int main()
{
 const int i=8;
 cv::Mat img =
            cv::imread("../imgs/" + std::to_string(i) + ".jpg");
 test(img);

}

