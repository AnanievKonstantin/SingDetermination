#ifndef STORRAGE_H
#define STORRAGE_H

#include <Tools.h>

/**
 * @brief The Storrage class
 *  Хранит значения контуров и их иерархии
 */
class Storrage
{
public:
    Storrage(vector<vector<cv::Point>> * contours, vector<cv::Vec4i> * hierarhy);
    ~Storrage();

    const vector<vector<cv::Point>> * getContours() const;
    const vector<cv::Vec4i> * getHierarhy() const;

private:
    vector<vector<cv::Point>> * contours = nullptr;
    vector<cv::Vec4i> * hierarchyOfContours = nullptr;
};

#endif // STORRAGE_H
