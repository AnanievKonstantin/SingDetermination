#include "Storrage.h"

Storrage::Storrage(vector<vector<cv::Point>> * contours, vector<cv::Vec4i> * hierarhy)
{
    if(contours == nullptr || hierarhy == nullptr)
    {
        throw std::invalid_argument("contours == nullptr || hierarhy == nullptr is true");
    }

    this->contours = contours;
    this->hierarchyOfContours = hierarhy;
}

Storrage::~Storrage()
{
    delete contours;
    delete hierarchyOfContours;
}

const vector<vector<cv::Point> > *Storrage::getContours() const
{
    return contours;
}

const vector<cv::Vec4i> *Storrage::getHierarhy() const
{
    return hierarchyOfContours;
}
