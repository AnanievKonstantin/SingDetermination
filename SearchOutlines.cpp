#include "SearchOutlines.h"

SearchOutlines::SearchOutlines()
{

}

SearchOutlines::~SearchOutlines()
{
}

list<Storrage * > *  SearchOutlines::search(const vector<cv::Mat> * correctedPictures)
{

    //showPictures("Origin", correctedPictures);
    grayScaleImages = createGrayScale(correctedPictures);

    binaryImages = createBin();
//    showPictures("Bin", binaryImages);
//    showPictures("Bin ", binaryImages);

    hsvBinChannelsFromSource = createBinaryHSVChannelsFrom(correctedPictures->at(0));
    hsvBinChannelsFromBright = createBinaryHSVChannelsFrom(correctedPictures->at(1));
    hsvBinChannelsFromContrast = createBinaryHSVChannelsFrom(correctedPictures->at(2));

    infoContours = new list<Storrage*>();
    findContours(grayScaleImages, 0,0);
    findContours(binaryImages, 0,0);
    findContours(hsvBinChannelsFromSource,0,0);
    findContours(hsvBinChannelsFromBright,0,0);
    findContours(hsvBinChannelsFromContrast,0,0);

//    showPictures("Bright ", hsvBinChannelsFromBright);
//    showPictures("Contrast ", hsvBinChannelsFromContrast);
//    showPictures("Source ",hsvBinChannelsFromSource);

    //drawContours();

//    cv::waitKey(0);
//    cv::destroyAllWindows();

    makeNormalisation();

    delete this->grayScaleImages;
    delete this->binaryImages;
    delete this->hsvBinChannelsFromBright;
    delete this->hsvBinChannelsFromContrast;
    delete this->hsvBinChannelsFromSource;

    return infoContours;
}

void SearchOutlines::showPictures(string name,const vector<cv::Mat> * const pictures)
{
    static int i = 0;
    for(const cv::Mat & image: *pictures)
    {
        cv::imshow(name+":"+std::to_string(i), image);
        i++;
    }
}

vector<cv::Mat> *SearchOutlines::createGrayScale(const vector<cv::Mat> *correctedPictures)
{
    vector<cv::Mat> * grayImages = new vector<cv::Mat>;
    grayImages->reserve(correctedPictures->size());
    for(const cv::Mat & image: *correctedPictures)
    {
        cv::Mat * gray = new cv::Mat();
        cv::cvtColor(image, *gray, CV_BGR2GRAY);
        grayImages->push_back(*gray);
    }

    return grayImages;
}

vector<cv::Mat> *SearchOutlines::createBin()
{
    vector<cv::Mat> * binImages = new vector<cv::Mat>;
    binImages->reserve(grayScaleImages->size());

    binImages->push_back(cv::Mat());
    binImages->push_back(cv::Mat());
    binImages->push_back(cv::Mat());
    binImages->push_back(cv::Mat());
    binImages->push_back(cv::Mat());
    binImages->push_back(cv::Mat());

    cv::threshold(grayScaleImages->at(0), binImages->at(0), 127, 255, CV_THRESH_BINARY);
    cv::threshold(grayScaleImages->at(1), binImages->at(1), 127, 255, CV_THRESH_BINARY);
    cv::threshold(grayScaleImages->at(2), binImages->at(2), 127, 255, CV_THRESH_BINARY);
    cv::threshold(grayScaleImages->at(3), binImages->at(3), 1, 255, CV_THRESH_BINARY);
    cv::threshold(grayScaleImages->at(4), binImages->at(4), 1, 255, CV_THRESH_BINARY);
    cv::threshold(grayScaleImages->at(5), binImages->at(5), 1, 255, CV_THRESH_BINARY);


    return binImages;
}

vector<cv::Mat> *SearchOutlines::createBinaryHSVChannelsFrom(const cv::Mat &image)
{
    cv::Mat imageHSV = image.clone();
    vector<cv::Mat> * chanels = new vector<cv::Mat>;
    cv::cvtColor(image, imageHSV, CV_BGR2HSV);
    cv::split(imageHSV, *chanels);

    for(cv::Mat & image: *chanels)
    {
        cv::threshold(image, image, 127, 255, CV_THRESH_BINARY);
    }

    return chanels;
}

void SearchOutlines::findContours(vector<cv::Mat> *images, int cannyLower, int cannyUpper)
{
    vector<vector<cv::Point>> * contours = nullptr;
    vector<cv::Vec4i> * hierarhy = nullptr;
    cv::Mat cannyOut;

    for(cv::Mat & image: *images)
    {
        cv::Canny(image, cannyOut, cannyLower, cannyUpper,5);
        contours = new vector<vector<cv::Point>>();
        hierarhy = new vector<cv::Vec4i>();
        cv::findContours(cannyOut, *contours, *hierarhy,
                         CV_RETR_TREE, CV_CHAIN_APPROX_NONE, cv::Point(0, 0));

        Storrage * outline = new Storrage(contours, hierarhy);
        infoContours->push_back(outline);
        outline = nullptr;
    }
}

void SearchOutlines::drawContours()
{
    cv::Mat toSize = grayScaleImages->at(0);
    cv::RNG r;

    int count = 0;

    for(Storrage * data: *infoContours)
    {
        cv::Mat drawing = cv::Mat::zeros(toSize.size(),CV_8UC3);

        for( int i = 0; i < data->getContours()->size(); i++ )
        {
            cv::Scalar color = cv::Scalar( r.uniform(0, 255),
                                           r.uniform(0, 255),
                                           r.uniform(0, 255));

            cv::drawContours(drawing, *data->getContours(), i, color, 1, 8, *data->getHierarhy(), 0, cv::Point());
        }

        cv::imshow("Contours: " + std::to_string(count), drawing);
        //cv::waitKey(0);
        count++;
    }
}

void SearchOutlines::makeNormalisation()
{
    removeShortContours();
}

void SearchOutlines::removeShortContours()
{

    for(Storrage * stor: *infoContours)
    {
        vector<int> indexes;
        int i = 0;
        for(const vector<cv::Point> & vec: *stor->getContours())
        {
            if(vec.size() < 200)
            {
                indexes.push_back(i);
            }
            i++;
        }

        stor->getContours()->erase(
                    std::remove_if(
                        stor->getContours()->begin(), stor->getContours()->end(),
                        [](const vector<cv::Point> &vec){ return vec.size() < 200;}),
                    stor->getContours()->end());

//        vector<int>::iterator iter;
//        for(iter = indexes.end(); iter != indexes.begin(); iter--)
//        {
//            (stor->getHierarhy())->erase(stor->getHierarhy()->begin() + *iter);
//        }
    }
}













