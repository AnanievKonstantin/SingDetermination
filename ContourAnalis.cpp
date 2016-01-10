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
    /**
     * В функции используется HoughCircles и отнашение площади круга к его окружности
     */

    vector<cv::Vec3f> circles;
    cv::cvtColor(imageWithContour, imageWithContour, CV_BGR2GRAY);

    cv::HoughCircles(imageWithContour, circles, cv::HOUGH_GRADIENT, 1, 1,
                 100, 30, 10, 300 // change the last two parameters
                                // (min_radius & max_radius) to detect larger circles
                 );

    if(circles.size() != 0) return true;


    double area = cv::contourArea(contour);
    double len = cv::arcLength(contour,false);

//    cout << "\t\tArea: "<<area <<endl;
//    cout << "\t\tLen: " <<len<< endl;
//    cout << "\t\tarea/len: " << area/(len*len) <<endl;

    if(area/(len*len) >= 0.07 && area/(len*len) <= 0.08) return true;
    return false;
}

bool ContourAnalis::rombDetection(cv::Mat &imageWithContour, vector<cv::Point> &contour)
{
    /**
     *              A
     *               o*
     *              ****
     *             ******
     *            ********
     *           **********
     *        B o**********o D
     *           **********
     *            ********
     *             ******
     *              ****
     *               *o
     *                  C
     *
     * Определяются точки A,B,C,D
     * Расчитываются отрезки AB, AD, BC,CD
     *
     * Вычисляется площадь ABCD cv::contourArea(contour)
     * Вычисляется площадь по S = 1/2 * (AC*BD)
     * Вычисляется delta = cv::contourArea(contour)/ S
     * Если delta не ревышает заданного значения то распознаётся как ромб
     *
     */

    cv::Point D(0,0);
    cv::Point C(0,0);
    cv::Point B(imageWithContour.cols,imageWithContour.rows);
    cv::Point A(imageWithContour.cols,imageWithContour.rows);

    for(cv::Point & point: contour)
    {
        if(point.x > D.x)
        {
            D.x = point.x; D.y = point.y;
        }

        if(point.x < B.x)
        {
            B.x = point.x; B.y = point.y;
        }

        if(point.y > C.y)
        {
            C.x = point.x; C.y = point.y;
        }

        if(point.y < A.y)
        {
            A.x = point.x; A.y = point.y;
        }
    }
//    cout << "\t\tD element : " << D<< "\n";
//    cout << "\t\tA element : " << A<< "\n";
//    cout << "\t\tB element : " << B<< "\n";
//    cout << "\t\tC element : " << C<< "\n";

    double areaOfContour = cv::contourArea(contour);
//    cout<<"\t\tareaOfContour" << areaOfContour <<endl;

    double AB = distance(A, B);
    double BC = distance(C, B);
    double AD = distance(D, A);
    double CD = distance(D, C);

//    cout << "\t\tAB " << AB <<endl;
//    cout << "\t\tBC " << BC <<endl;
//    cout << "\t\tAD " << AD <<endl;
//    cout << "\t\tCD " << CD<<endl;

    if(AB <= 1 || BC <= 1 || CD <= 1 || AD <= 1)
    {
        return false;
    }

    double AC = distance(C, A);
    double BD = distance(B, D);

//    cout <<"AC " << AC <<endl;
//    cout <<"BD " << BD <<endl;

    if(A.y >= (B.y - AC/8) || A.y >= (C.y - AC/8))
    {
        return false;
    }

    double areaOfPoints = (0.5) * (AC*BD);

//    cout << "areaOfContour "<< areaOfContour <<endl;
//    cout << "areaOfPoints " << areaOfPoints<<endl;

    double delta = std::fabs(areaOfContour/areaOfPoints);
//    cout << "delta " << delta <<endl;

    if(delta < 1.0 || delta > 1.2)
    {
        return false;
    }


    return true;
}

bool ContourAnalis::triagleDetection(cv::Mat &imageWithContour, vector<cv::Point> &contour)
{
    /**
     *
     *         A      H       B
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

    if(relAB_AC < 0.95 || relAB_AC >1.05)
    {
        return false;
    }

    if(relAB_BC < 0.95 || relAB_BC >1.05)
    {
        return false;
    }

    if(relAC_BC < 0.95 ||  relAC_BC >1.05)
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

void ContourAnalis::CalcProbabilityDetection(double toRect, double toCircle, double toTriagle)
{
    double all = (toRect + toCircle + toTriagle);
    if(all == 0)
    {
        cout << " N " <<endl;
        return;
    }

    double isRect = toRect/all;
    double isCircle = toCircle/all;
    double isTriagle = toTriagle/all;

    if(isCircle > isRect && isCircle > isTriagle)
    {
        cout << " O " << isCircle <<endl;
        return;
    }

    if(isRect > isTriagle && isRect > isCircle)
    {
        cout << " R " << isRect <<endl;
        return;
    }

    if(isTriagle > isRect && isTriagle > isCircle)
    {
        cout << " D " << isTriagle<<endl;
        return;
    }

    cout << " N " <<endl;
    return;


}

ContourAnalis::ContourAnalis()
{
}

void ContourAnalis::makeAnalis(list<Storrage *> *contours)
{
    //cout << "In ANALIS" <<endl;
    int i = 0;
    int imageNumber = 0;

    double isRomb = 0;
    double isCircle = 0;
    double isTriagle = 0;

    for(Storrage * stor: *contours)
    {
//        cout<< "\t " << imageNumber <<") Изображение: " << endl;
        imageNumber++;
        for(vector<cv::Point> & vec: *stor->getContours())
        {
//            cout<<"\t\t "<< i <<") Информация о контуре: " << endl;
            cv::Mat contourImage = drawContour(vec);
            if(circleDetected(contourImage, vec))
            {
//                cout << "\t\tКруг" << endl;
                isCircle ++;
            }else
//                cout << "\t\tНЕ Круг" << endl;

            if(rombDetection(contourImage, vec))
            {
//                cout << "\t\tРомб" << endl;
                isRomb ++;
            }else
//                cout << "\t\tНЕ Ромб" << endl;

            if(triagleDetection(contourImage, vec))
            {
//                cout << "\t\tТриугольник" << endl;
                isTriagle ++;
            }else
//                cout << "\t\tНE триугольник" << endl;

            i++;
        }
        i = 0;
    }

//    cout << "Это круг на: "<<isCircle<<endl;
//    cout << "Это ромб на: "<<isRomb<<endl;
//    cout << "Это триугольник на: "<<isTriagle<<endl;

    CalcProbabilityDetection(isRomb, isCircle, isTriagle);
    //cv::waitKey();
    //cv::destroyAllWindows();
}
