#include "ContourAnalis.h"

cv::Mat ContourAnalis::drawContour(const vector<cv::Point> &contour)
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
    count++;

    return drawing;
}

bool ContourAnalis::circleDetected(cv::Mat &imageWithContour, vector<cv::Point> &contour)
{
    vector<cv::Vec3f> circles;
    cv::cvtColor(imageWithContour, imageWithContour, CV_BGR2GRAY);

    cv::HoughCircles(imageWithContour, circles, cv::HOUGH_GRADIENT, 1, 1,
                 100, 30, 10, 300 // change the last two parameters
                                // (min_radius & max_radius) to detect larger circles
                 );

    if(circles.size() != 0) return true;


    double area = cv::contourArea(contour);
    double len = cv::arcLength(contour,false);

    cout << "\t\tArea: "<<area <<endl;
    cout << "\t\tLen: " <<len<< endl;
    cout << "\t\tarea/len: " << area/(len*len) <<endl;

    if(area/(len*len) >= 0.06 && area/(len*len) <= 0.08) return true;
    return false;
}

ContourAnalis::ContourAnalis()
{
}

int ContourAnalis::makeAnalis(list<Storrage *> *contours)
{
    //cout << "In ANALIS" <<endl;
    int i = 0;
    int imageNumber = 0;
    for(Storrage * stor: *contours)
    {
        cout<< "\t " << imageNumber <<") Изображение: " << endl;
        imageNumber++;
        for(vector<cv::Point> & vec: *stor->getContours())
        {
            cout<<"\t\t "<< i <<") Информация о контуре: " << endl;
            cv::Mat contourImage = drawContour(vec);
            if(circleDetected(contourImage, vec))
            {
                cout << "\t\tКруг" << endl;
            }
            i++;
            cv::waitKey();
        }
        i = 0;
    }
}
