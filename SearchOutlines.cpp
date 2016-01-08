#include "SearchOutlines.h"

SearchOutlines::SearchOutlines()
{

}

SearchOutlines::~SearchOutlines()
{
}

void SearchOutlines::search(const vector<cv::Mat> * correctedPictures)
{

    //showPictures(correctedPictures);

    grayScaleImages = createGrayScale(correctedPictures);

    //showPictures(grayScaleImages);

    binaryImages = createBin();

    //showPictures(binaryImages);


    hsvChannelsFromSource = createBinaryHSVChannelsFrom(correctedPictures->at(0));
    hsvChannelsFromBright = createBinaryHSVChannelsFrom(correctedPictures->at(1));
    hsvChannelsFromContrast = createBinaryHSVChannelsFrom(correctedPictures->at(2));

    showPictures("Bright ", hsvChannelsFromBright);
    showPictures("Contrast ", hsvChannelsFromContrast);
    showPictures("Source ",hsvChannelsFromSource);

    cv::waitKey(0);

    cv::destroyAllWindows();



    delete this->grayScaleImages;
    delete this->binaryImages;
    delete this->hsvChannelsFromBright;
    delete this->hsvChannelsFromContrast;
    delete this->hsvChannelsFromSource;
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

}













