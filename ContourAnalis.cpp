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

    //cv::imshow("Contours: " + std::to_string(count), drawing);
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

    if(area/(len*len) >= 0.07 && area/(len*len) <= 0.08) return true;
    return false;
}

bool ContourAnalis::rombDetection(cv::Mat &imageWithContour, vector<cv::Point> &contour)
{
    cv::Point maxX(0,0);
    cv::Point maxY(0,0);
    cv::Point minX(imageWithContour.cols,imageWithContour.rows);
    cv::Point minY(imageWithContour.cols,imageWithContour.rows);

    for(cv::Point & point: contour)
    {
        if(point.x > maxX.x)
        {
            maxX.x = point.x; maxX.y = point.y;
        }

        if(point.x < minX.x)
        {
            minX.x = point.x; minX.y = point.y;
        }

        if(point.y > maxY.y)
        {
            maxY.x = point.x; maxY.y = point.y;
        }

        if(point.y < minY.y)
        {
            minY.x = point.x; minY.y = point.y;
        }
    }
    cout << "\t\tmaxX element : " << maxX<< "\n";
    cout << "\t\tminY element : " << minY<< "\n";
    cout << "\t\tminX element : " << minX<< "\n";
    cout << "\t\tmaxY element : " << maxY<< "\n";

    double areaOfContour = cv::contourArea(contour);
    cout<<"\t\tareaOfContour" << areaOfContour <<endl;

    double lenLeftTop = distance(minY, minX);
    double lenLeftDown = distance(maxY, minX);
    double lenRightTop = distance(maxX, minY);
    double lenRightDown = distance(maxX,maxY);

    cout << "\t\tlenLeftTop " << lenLeftTop <<endl;
    cout << "\t\tlenLeftDown " <<lenLeftDown <<endl;
    cout << "\t\tlenRightTop " <<lenRightTop <<endl;
    cout << "\t\tlenRightDown" <<lenRightDown<<endl;

    if(lenLeftTop <= 1 || lenLeftDown <= 1 || lenRightDown <= 1 || lenRightTop <= 1)
    {
        return false;
    }

    double areaOfLeftTop    = lenLeftTop*lenLeftTop;
    double areaOfLeftDown   = lenLeftDown*lenLeftDown;
    double areaOfRightTop   = lenRightTop*lenRightTop;
    double areaOfRightDown  = lenRightDown*lenRightDown;

    cout << "\t\tareaOfLeftTop   " << areaOfLeftTop  <<endl;
    cout << "\t\tareaOfLeftDown  " << areaOfLeftDown <<endl;
    cout << "\t\tareaOfRightTop  " << areaOfRightTop <<endl;
    cout << "\t\tareaOfRightDown " << areaOfRightDown<<endl;

    double deltaArea0 = areaOfContour - areaOfLeftTop;
    double deltaArea1 = areaOfContour - areaOfLeftDown;
    double deltaArea2 = areaOfContour - areaOfRightTop;
    double deltaArea3 = areaOfContour - areaOfRightDown;

    cout<<"\t\tdeltaArea0 "<<deltaArea0<<endl;
    cout<<"\t\tdeltaArea1 "<<deltaArea1<<endl;
    cout<<"\t\tdeltaArea2 "<<deltaArea2<<endl;
    cout<<"\t\tdeltaArea3 "<<deltaArea3<<endl;

    if(deltaArea0 <500 && deltaArea1 <500  && deltaArea2 <500  && deltaArea3 <500 )
    {
        return false;
    }


    double averageAreaOfPoints = (areaOfLeftTop + areaOfLeftDown + areaOfRightTop + areaOfRightDown)/4;
    cout << "\t\taverageAreaOfPoints/areaOfContour " << averageAreaOfPoints/areaOfContour<<endl;
    if(averageAreaOfPoints/areaOfContour < 0.7 || averageAreaOfPoints/areaOfContour > 0.9)
    {
        return false;
    }




    return true;
}

bool ContourAnalis::triagleDetection(cv::Mat &imageWithContour, vector<cv::Point> &contour)
{
    /**        A      H       B
     *          o*****o******o
     *           ************
     *            **********
     *             ********
     *              ******
     *               ****
     *                **
     *                 o
     *                C
     *
     * триугольник ABC с высотой СH
     *
     * При распознании сравнивается параметр площади найденный по формуле 1/2 * AB * CH
     * и площадь найденная по функции cv::contourArea()
     *
     * Если расстояние между всеми сторонами одинаковое и если H.y не выше (A.x + B.x)/2
     *  белее чем на AB/4 то распознаётся как триугольник
     */


    cv::Point A(imageWithContour.cols,imageWithContour.rows);
    cv::Point B(0,0);
    cv::Point H(0,0);
    cv::Point C(0,0);

    for(cv::Point & point: contour)
    {
        if(point.x > B.x)
        {
            B.x = point.x; B.y = point.y;
        }

        if(point.y > C.y)
        {
            C.x = point.x; C.y = point.y;
        }

        if(point.x < A.x)
        {
            A.x = point.x; A.y = point.y;
        }

    }

    int AB = (int)distance(B, A);

    for(cv::Point & point: contour)
    {
        if(point.x >= (A.x + AB/2) - 5 && point.x <= (B.x - AB/2) + 5)
        {
            double dyAB = (A.y + B.y)/2;
            if(point.y <= (A.y + dyAB) && point.y >= (A.y - dyAB))
            {
                if(point.y <= (B.y + dyAB) && point.y >= (B.y - dyAB))
                {
                   H.x = point.x; H.y = point.y;
                }
            }

        }
    }
//    cout << "\t\tA: " << A<< "\n";
//    cout << "\t\tB: " << B<< "\n";
//    cout << "\t\tC : " << C<< "\n";
//    cout << "\t\tH: " << H<< "\n";

    if(H.x == 0 && H.y == 0)
    {
        return 0;
    }

    AB = distance(B,A);
    double AC = distance(A, C);
    double BC = distance(B, C);

//    cout << "\t\tAB: " << AB<< "\n";
//    cout << "\t\tAC: " << AC<< "\n";
//    cout << "\t\tBC : " <<BC<< "\n";

    if(AB+AC <= BC || AB+BC <= AC || AC+BC <= AB)
    {
        return false;
    }

    double relAB_AC = AB/AC;
    double relAB_BC = AB/BC;
    double relAC_BC = AC/BC;

    double dRelation = (relAB_AC + relAB_BC + relAC_BC)/3;

    if(dRelation < 0.95 || dRelation >1.05)
    {
        return false;
    }

//    cout << "AB/AC" << AB/AC <<endl;
//    cout << "AB/BC" << AB/BC <<endl;
//    cout << "AC/BC" << AC/BC <<endl;

    return true;

}

double ContourAnalis::distance(cv::Point a, cv::Point b)
{
    double d = 0;
    double arg1 = std::pow((b.x - a.x), 2);
    double arg2 = std::pow((b.y - a.y), 2);
    d = std::sqrt(std::fabs(arg1)+std::fabs(arg2));
    return d;
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
//            if(circleDetected(contourImage, vec))
//            {
//                cout << "\t\tКруг" << endl;
//            }else
//                cout << "\t\tНЕ Круг" << endl;

//            if(rombDetection(contourImage, vec))
//            {
//                cout << "\t\tРомб" << endl;
//            }else
//                cout << "\t\tНЕ Ромб" << endl;

            if(triagleDetection(contourImage, vec))
            {
                cout << "\t\tТриугольник" << endl;
            }else
                cout << "\t\tНE триугольник" << endl;

            i++;
            cv::waitKey();
        }
        i = 0;
    }
    cv::destroyAllWindows();
}
