#ifndef CORRECTION_H
#define CORRECTION_H

#include <Tools.h>

/**
 * @brief The Correction class
 * Анализирует поступившее изображение и корректирует его для дальнейшего распохнования
 * Увеличивает размер, нормализует цвета, увеличивает яркость.
 */
class Correction
{
    public:
        Correction();
        ~Correction();

        /**
         * @brief createImage
         *  создает cv::Mat
         * @param path
         *  Путь к избражению
         * @return
         * скорректированное изображение
         */
        cv::Mat makeCorrection(string path);

    private:

        /**
         * @brief createImage
         *  создает cv::Mat из this->path для обработки
         */
        void createImage();
        string path;
        cv::Mat sourceImage;
        cv::Mat resultImage;
};

#endif // CORRECTION_H
