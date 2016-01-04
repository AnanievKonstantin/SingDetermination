#include "Correction.h"

Correction::Correction()
{

}

Correction::~Correction()
{

}


void Correction::createImage(std::string path)
{
    this->sourceImage = cv::imread(path);
    cv::imshow("Source", this->sourceImage);

    cv::waitKey(0);

    cv::destroyWindow("Source");
}
