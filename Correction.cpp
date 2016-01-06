#include "Correction.h"

Correction::Correction()
{

}

Correction::~Correction()
{

}

void Correction::createImage()
{
    this->sourceImage = cv::imread(this->path);
}

void Correction::correctColorRange()
{
    cv::Mat imageInHSV;

    cv::imshow("SOURCE", this->sourceImage);

//    cv::Mat sourceBin = this->sourceImage.clone();
//    cv::cvtColor(sourceBin, sourceBin, CV_RGB2GRAY);
//    cv::threshold(sourceBin, sourceBin, 127, 255, CV_THRESH_BINARY);
//    this->increaseSizeIn(sourceBin, 3);
//    cv::imshow("SOURCE BIN", sourceBin);

    //cv::blur(this->sourceImage, this->sourceImage, cv::Size(3,3));

    cv::xphoto::autowbGrayworld(this->sourceImage, this->sourceImage);

    //Чуткость ++
//        const cv::Mat kernel = (cv::Mat_<double>(3,3) << -0.2,-0.2,-0.2,
//                                                         -0.2,   3,-0.2,
//                                                         -0.2,-0.2,-0.2);
//        //cv::filter2D(sourceImage, sourceImage, sourceImage.depth(), kernel);



    //this->sourceImage *= 2;

//    cv::Mat correctedSource = this->sourceImage.clone();
//    cv::imshow("CSource", correctedSource);
//    cv::cvtColor(correctedSource, correctedSource, CV_BGR2GRAY);
//    cv::threshold(correctedSource, correctedSource, 127, 255, CV_THRESH_BINARY);
//    this->increaseSizeIn(correctedSource, 3);
//    cv::imshow("CSBin", correctedSource);


    cv::cvtColor(this->sourceImage, imageInHSV, CV_BGR2HSV);

    long midleValue = 0;

    cv::MatIterator_<cv::Vec3b> it, end;
    for( it = imageInHSV.begin<cv::Vec3b>(), end = imageInHSV.end<cv::Vec3b>(); it != end; ++it)
    {
        midleValue += (*it)[2];
    }

    midleValue /= (imageInHSV.cols * imageInHSV.rows);
    cout << "MidleVAlue: " << midleValue <<"\n";


    if(midleValue <=15)
    {
        for( it = imageInHSV.begin<cv::Vec3b>(), end = imageInHSV.end<cv::Vec3b>(); it != end; ++it)
        {
            (*it)[1] += (*it)[1]/3;
            (*it)[2] += (*it)[2]/3;
        }
        cout<< "3 inc bright" <<endl;
    }
    else if(midleValue <=70)
    {
        for( it = imageInHSV.begin<cv::Vec3b>(), end = imageInHSV.end<cv::Vec3b>(); it != end; ++it)
        {
            (*it)[1] += (*it)[1]/4;
            (*it)[2] += (*it)[2]/4;
        }
        cout<< "inc bright" <<endl;
    }
    else if(midleValue >=140)
    {
        for( it = imageInHSV.begin<cv::Vec3b>(), end = imageInHSV.end<cv::Vec3b>(); it != end; ++it)
        {
             (*it)[2] -= (*it)[2]/4;
        }
        cout<< "dec bright" <<endl;
    }
    else
    {
        cout<< "normal bright" <<endl;
    }

    for( it = imageInHSV.begin<cv::Vec3b>(), end = imageInHSV.end<cv::Vec3b>(); it != end; ++it)
    {
        //Yellow
        if( ((*it)[1] >= 130) && (*it)[2] >= 100 && (*it)[0] >= 19 && (*it)[0] <= 39)
        {
            (*it)[0] = 30;
            (*it)[1] = 254;
            (*it)[2] = 254;
            continue;
        }

        //Red
        if( ((*it)[1] >= 130) && (*it)[2] >= 100 && (*it)[0] <= 5)
        {
            (*it)[0] = 0;
            (*it)[1] = 254;
            (*it)[2] = 254;
            continue;

        }

        //white
        if(((*it)[2] >= 80 && (*it)[1] <= 100))
        {
            (*it)[0] = 60;
            (*it)[1] = 255;
            (*it)[2] = 255;
            continue;
        }
    }

    cv::imshow("cHSV", imageInHSV);
    cv::imshow("Bright", this->sourceImage);

    cv::cvtColor(imageInHSV, this->sourceImage, CV_HSV2BGR);

    cv::Mat gray;

    cv::cvtColor(this->sourceImage, gray, CV_BGR2GRAY);
    cv::threshold(gray, gray, 127,255,CV_THRESH_BINARY);

    cv::imshow("Bin", gray);






//    cv::Mat colorCorrectBRG;

//    cv::cvtColor(imageInHSV, colorCorrectBRG, CV_HSV2BGR);
//    cv::resize(colorCorrectBRG, colorCorrectBRG, colorCorrectBRG.size() * 3);

//    cv::imshow("new BGR", colorCorrectBRG);



//    vector<cv::Mat> channelsDefault;

//    cv::split(imageInHSV, channelsDefault);
//    for(cv::Mat c: channelsDefault)
//    {
//        cv::threshold(c, c, 127, 255, CV_THRESH_BINARY);
//        this->increaseSizeIn(c, 4);
//    }

//    //cv::Mat SandV;
//    //cv::bitwise_and(channelsDefault[1].clone(), channelsDefault[2].clone(), SandV);

//    //cv::imshow("SandV", SandV);

//    cv::imshow("H default", channelsDefault[0]);
//    cv::imshow("S default", channelsDefault[1]);
//    cv::imshow("V default", channelsDefault[2]);

    cv::waitKey(0);

    cv::destroyAllWindows();

    //cv::cvtColor(imageInHSV, this->resultImage, CV_HSV2BGR);




    //cv::cvtColor(this->resultImage, this->resultImage, CV_BGR2GRAY);

//    cv::adaptiveThreshold(this->resultImage, this->resultImage, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY,15,-5);
//    this->increaseSizeIn(this->resultImage, 3);

    //this->showImage("Bin", this->resultImage);
}

void Correction::showImage(std::string name, cv::Mat &image)
{
    cv::imshow(name, image);
    cv::waitKey(0);

    cv::destroyWindow(name);
}

void Correction::increaseSizeIn(cv::Mat &image, int multiplier)
{
    cv::resize(image, image, image.size() * multiplier);
}

cv::Mat Correction::makeCorrection(std::string path)
{
    this->path = path;
    this->createImage();

    this->correctColorRange();

    return this->resultImage;
}
