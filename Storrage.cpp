#include "Storrage.h"

Storrage::Storrage(vector<vector<cv::Point>> * contours, vector<cv::Vec4i> * hierarhy)
{
    //cout << "In constract" << endl;
    if(contours == nullptr || hierarhy == nullptr)
    {
        //cout << "Null" << endl;
        throw std::invalid_argument("contours == nullptr || hierarhy == nullptr is true");
    }

    this->contours = contours;
    this->hierarchyOfContours = hierarhy;
}

Storrage::~Storrage()
{
    //cout << "In de constract" << endl;
    delete contours;
    delete hierarchyOfContours;
}

vector<vector<cv::Point> > *Storrage::getContours() const
{
    return contours;
}

vector<cv::Vec4i> *Storrage::getHierarhy() const
{
    return hierarchyOfContours;
}
