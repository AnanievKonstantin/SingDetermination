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
         */
        void createImage(string path);
    private:
        cv::Mat sourceImage;
};

#endif // CORRECTION_H
