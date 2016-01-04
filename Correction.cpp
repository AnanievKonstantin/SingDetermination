#include "Correction.h"

Correction::Correction()
{

}

Correction::~Correction()
{

}

void Correction::createImage()
{
    this->sourceImage = cv::imread(this->path);
}


cv::Mat Correction::makeCorrection(std::string path)
{
    this->path = path;
    this->createImage();

    cv::imshow("Source", this->sourceImage);

    cv::waitKey(0);

    cv::destroyWindow("Source");

    return this->resultImage;
}
