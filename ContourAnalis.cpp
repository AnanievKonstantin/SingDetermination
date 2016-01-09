#include "ContourAnalis.h"

void ContourAnalis::drawContour(const vector<cv::Point> &contour)
{
    //cout<<"In contour" <<endl;
    cv::RNG r;

    int count = 0;

    cv::Scalar color = cv::Scalar( r.uniform(0, 255),
                                   r.uniform(0, 255),
                                   r.uniform(0, 255));

    cv::Mat drawing = cv::Mat::zeros(700,700,CV_8UC3);
    for( int i = 0; i < contour.size(); i++ )
    {
        cv::line(drawing, contour.at(i),contour.at(i),color);
    }

    cv::imshow("Contours: " + std::to_string(count), drawing);
    //cv::waitKey(0);
    count++;
}

ContourAnalis::ContourAnalis()
{
}

int ContourAnalis::makeAnalis(list<Storrage *> *contours)
{
    //cout << "In ANALIS" <<endl;
    int i = 0;

    for(Storrage * stor: *contours)
    {
        for(const vector<cv::Point> & vec: *stor->getContours())
        {
            drawContour(vec);
        }
        cv::waitKey();
    }
}
