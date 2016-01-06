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
    cv::resize(sourceImage, sourceImage, sourceImage.size()*5,cv::INTER_NEAREST);

    cv::imshow("Start", this->sourceImage);

    cv::xphoto::autowbGrayworld(this->sourceImage, this->sourceImage);

    //Чуткость ++
        const cv::Mat kernel = (cv::Mat_<double>(3,3) << -0.1,-0.1,-0.1,
                                                         -0.1,   2,-0.1,
                                                         -0.1,-0.1,-0.1);
    cv::filter2D(sourceImage, sourceImage, sourceImage.depth(), kernel);

    //increaseContrast(sourceImage, 2);



    /**
     * @brief colors
     * Пробдлема желтого и красного
     * и 255 для желтого
     *
     *
     *
     *
     *
     *
     * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
     */









    vector<cv::Mat> colors = findRYW(sourceImage);

    cv::imshow("Red", colors[0]);
    cv::imshow("Yellow", colors[1]);
    cv::imshow("White", colors[2]);
    cv::imshow("END", sourceImage);

    cv::waitKey(0);

    cv::destroyAllWindows();
}

void Correction::showImage(std::string name, cv::Mat &image)
{
    cv::imshow(name, image);
    cv::waitKey(0);

    cv::destroyWindow(name);
}

bool Correction::isWhite(const cv::Vec3b &pixel)
{
    int BonG = pixel[0]/pixel[1];
    int GonR = pixel[2]/pixel[1];

    int delta = std::abs(BonG - GonR);
    if(pixel[0] >= 127 && pixel[1] >= 127 && pixel[2] >= 127)
    {
        return true;
    }
    else if(delta >= 0 && delta <=10)
    {
        return true;
    }
    else
        return false;
}

bool Correction::isRed(const cv::Vec3b &pixel)
{
    if(pixel[0] <= 127 && pixel[1] <= 127 && pixel[2] >= 127)
    {
        return true;
    }
    else if(pixel[2] >= pixel[0]*2 && pixel[2] >= pixel[1]*2)
    {
        return true;
    }
    else if(pixel[2] >= pixel[0]/3 + pixel[0] && pixel[2] >= pixel[1]/3 + pixel[1])
    {
        return true;
    }
    else
        return false;
}

bool Correction::isYellow(const cv::Vec3b &pixel)
{
    if(pixel[2] > pixel[1] && pixel[1] > pixel[0])
    {
        return true;
    }
    else if(pixel[0] <= 127 && pixel[1] >= 127 && pixel[2] >= 127)
    {
        return true;
    }

    else
        return false;
}

void Correction::increaseSizeIn(cv::Mat &image, int multiplier)
{
    cv::resize(image, image, image.size() * multiplier);
}

void Correction::increaseContrast(cv::Mat &image, double alpha)
{
    if(alpha < 1 || alpha > 3)
    {
        throw std::invalid_argument("alpha most be in [1.0, 3.0]");
    }

    for( int y = 0; y < image.rows; y++ )
    {
        for( int x = 0; x < image.cols; x++ )
        {
            for( int c = 0; c < 3; c++ )
            {
                image.at<cv::Vec3b>(y,x)[c] = cv::saturate_cast<uchar>( alpha*(image.at<cv::Vec3b>(y,x)[c] ));
            }
        }
    }
}

vector<cv::Mat> &Correction::findRYW(const cv::Mat &image)
{
    cv::MatIterator_<cv::Vec3b> itR,itY,itW;
    cv::MatConstIterator_<cv::Vec3b> it, end;
    vector<cv::Mat> * colors = new vector<cv::Mat>(3);
    colors->at(0) = image.clone();//Red
    colors->at(1) = image.clone();//Yellow
    colors->at(2) = image.clone();//White

    for( it = image.begin<cv::Vec3b>(),
         itR = colors->at(0).begin<cv::Vec3b>(),
         itY = colors->at(1).begin<cv::Vec3b>(),
         itW = colors->at(2).begin<cv::Vec3b>(),
         end = image.end<cv::Vec3b>(); it != end; ++it,++itR,++itY,++itW)
    {
        if(isRed(*it))
        {
            (*itR)[0] = 0;
            (*itR)[1] = 0;
            (*itR)[2] = 255;
        }
        else if(isYellow(*it))
        {
            (*itY)[0] = 0;
            (*itY)[1] = 255;
            (*itY)[2] = 255;
        }
        else if(isWhite(*it))
        {
            (*itW)[0] = 255;
            (*itW)[1] = 255;
            (*itW)[2] = 255;
        }
    }
    return * colors;
}



cv::Mat Correction::makeCorrection(std::string path)
{
    this->path = path;
    this->createImage();

    this->correctColorRange();

    return this->resultImage;
}
