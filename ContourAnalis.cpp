#include "ContourAnalis.h"

void ContourAnalis::drawContour(const vector<cv::Point> &contour)
{
    cout<<"In contour" <<endl;
    cv::RNG r;

    int count = 0;

    cv::Scalar color = cv::Scalar( r.uniform(0, 255),
                                   r.uniform(0, 255),
                                   r.uniform(0, 255));

    cv::Mat drawing = cv::Mat::zeros(500,500,CV_8UC3);
    for( int i = 0; i < contour.size(); i++ )
    {
//        cv::drawContours(drawing, *contour->getContours(),
//                         i, color, 1, 8, *contour->getHierarhy(), 0, cv::Point());
        cv::line(drawing, contour.at(i),contour.at(i),color);
    }

    cv::imshow("Contours: " + std::to_string(count), drawing);
    cv::waitKey(0);
    count++;
}

ContourAnalis::ContourAnalis()
{
}

int ContourAnalis::makeAnalis(list<Storrage *> *contours)
{
    cout << "In ANALIS" <<endl;
//    for(Storrage * contour: *contours)
//    {
//        double area = cv::contourArea(*contour->getContours());
//        //double len = cv::arcLength(*contour->getContours(),true);

//        //double relation = area/len;

//        //cout<<"Relation: " << relation <<endl;

//    }


    int i = 0;

    for(Storrage * stor: *contours)
    {
        for(const vector<cv::Point> & vec: *stor->getContours())
        {
            drawContour(vec);
            i = (*stor->getHierarhy())[i][0];
            if((*stor->getHierarhy())[i][0] < 0)
            {
                cout << "Open" <<endl;
            }
            else
            {
                cout <<"Close" <<endl;
            }
        }
    }

//    for( int i = 0; i < contours[]; i=hierarchy[i][0] ) // iterate through each contour.
//        {
//            Rect r= boundingRect(contours[i]);
//            if(hierarchy[i][2]<0) //Check if there is a child contour
//              cv::rectangle(src,Point(r.x-10,r.y-10),
//                            Point(r.x+r.width+10,r.y+r.height+10), Scalar(0,0,255),2,8,0); //Opened contour
//            else
//              cv::rectangle(src,cv::Point(r.x-10,r.y-10),
//                            Point(r.x+r.width+10,r.y+r.height+10), Scalar(0,255,0),2,8,0); //closed contour
//        }


}
