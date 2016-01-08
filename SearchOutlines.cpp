#include "SearchOutlines.h"

SearchOutlines::SearchOutlines()
{

}

SearchOutlines::~SearchOutlines()
{
}

void SearchOutlines::search(const vector<cv::Mat> * correctedPictures)
{
    grayScaleImages = createGrayScale(correctedPictures);

    binaryImages = createBin();

    //showPictures("Bin ", binaryImages);

    hsvBinChannelsFromSource = createBinaryHSVChannelsFrom(correctedPictures->at(0));
    hsvBinChannelsFromBright = createBinaryHSVChannelsFrom(correctedPictures->at(1));
    hsvBinChannelsFromContrast = createBinaryHSVChannelsFrom(correctedPictures->at(2));

    findContours();

    //showPictures("Bright ", hsvBinChannelsFromBright);
    //showPictures("Contrast ", hsvBinChannelsFromContrast);
    //showPictures("Source ",hsvBinChannelsFromSource);

    drawContours();

    cv::waitKey(0);

    cv::destroyAllWindows();

    delete this->grayScaleImages;
    delete this->binaryImages;
    delete this->hsvBinChannelsFromBright;
    delete this->hsvBinChannelsFromContrast;
    delete this->hsvBinChannelsFromSource;

    for(Storrage * iteam: *infoContours)
    {
        delete iteam;
        iteam = nullptr;
    }

    delete infoContours;
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

void SearchOutlines::findContours()
{
    vector<vector<cv::Point>> * contours = nullptr;
    vector<cv::Vec4i> * hierarhy = nullptr;
    infoContours = new list<Storrage*>();
    cv::Mat cannyOut;

    for(cv::Mat & image: *binaryImages)
    {
        //ERROR --> нужно настроить поиск контуров
        cv::Canny(image, cannyOut, 200, 255);
        contours = new vector<vector<cv::Point>>();
        hierarhy = new vector<cv::Vec4i>();
        cv::findContours(cannyOut, *contours, *hierarhy,
                         CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

        Storrage * outline = new Storrage(contours, hierarhy);
        infoContours->push_back(outline);
    }

    for(cv::Mat & image: *hsvBinChannelsFromSource)
    {
        cv::Canny(image, cannyOut, 0, 254);
        contours = new vector<vector<cv::Point>>();
        hierarhy = new vector<cv::Vec4i>();
        cv::findContours(cannyOut, *contours, *hierarhy,
                         CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

        Storrage * outline = new Storrage(contours, hierarhy);
        infoContours->push_back(outline);
    }

    for(cv::Mat & image: *hsvBinChannelsFromContrast)
    {
        cv::Canny(image, cannyOut, 0, 254);
        contours = new vector<vector<cv::Point>>();
        hierarhy = new vector<cv::Vec4i>();
        cv::findContours(cannyOut, *contours, *hierarhy,
                         CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

        Storrage * outline = new Storrage(contours, hierarhy);
        infoContours->push_back(outline);
    }

    for(cv::Mat & image: *hsvBinChannelsFromBright)
    {
        cv::Canny(image, cannyOut, 0, 254);
        contours = new vector<vector<cv::Point>>();
        hierarhy = new vector<cv::Vec4i>();
        cv::findContours(cannyOut, *contours, *hierarhy,
                         CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

        Storrage * outline = new Storrage(contours, hierarhy);
        infoContours->push_back(outline);
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
        cv::waitKey(0);
        count++;
    }
}













