#ifndef SEARCHOUTLINES_H
#define SEARCHOUTLINES_H


#include <Tools.h>

/**
 * @brief The SearchOutlines class
 *  Производит поиск и нормализацию контуров
 */
class SearchOutlines
{
    public:
        SearchOutlines();
        ~SearchOutlines();
        void search(const vector<cv::Mat> * correctedPictures);

    private:

        /**
         * @brief showPictures
         * Выводит на экран массив изображений
         * @debug
         */
        void showPictures(const vector<cv::Mat> * const pictures);

        /**
         * @brief createGrayScale
         *  создаёт gray версию изображений
         * @return
         */
        vector<cv::Mat> * createGrayScale(const vector<cv::Mat> * correctedPictures);

        /**
         * @brief createBin
         *  создаёт бинарную версию изобажений
         * @return
         *  массив бинарных изображений
         */
        vector<cv::Mat> * createBin();

        vector<cv::Mat> * grayScaleImages = nullptr;
        vector<cv::Mat> * binaryImages = nullptr;
};

#endif // SEARCHOUTLINES_H
