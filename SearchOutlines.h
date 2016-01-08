#ifndef SEARCHOUTLINES_H
#define SEARCHOUTLINES_H


#include <Tools.h>
#include <Storrage.h>

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
        void showPictures(string name,const vector<cv::Mat> * const pictures);

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

        /**
         * @brief createHSVChannelsFrom
         *  Создаёт каналы H S V из поступившено изображения
         * @param image
         *  3 канальное избражение BGR
         * @return
         *  массив каналов
         *  vector[0] H
         *  vector[1] S
         *  vector[2] V
         */
        vector<cv::Mat> * createBinaryHSVChannelsFrom(const cv::Mat & image);

        /**
         * @brief findContours
         *  Нахлжит контуры и их иерархию в:
         *  @see grayScaleImages
         *  @see binaryImages
         *  @see hsvChannelsFromSource
         *  @see hsvChannelsFromBright
         *  @see hsvChannelsFromContrast
         */
        void findContours();

        vector<cv::Mat> * grayScaleImages = nullptr;
        vector<cv::Mat> * binaryImages = nullptr;
        vector<cv::Mat> * hsvChannelsFromSource = nullptr;
        vector<cv::Mat> * hsvChannelsFromBright = nullptr;
        vector<cv::Mat> * hsvChannelsFromContrast = nullptr;

        list<Storrage> * imagesContours = nullptr;
};

#endif // SEARCHOUTLINES_H
