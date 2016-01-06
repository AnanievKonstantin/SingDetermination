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
         * @brief makeCorrection
         *  Корректирует изображение
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

        /**
         * @brief correctColorRange
         *  Ищит желтые, красные элементы и делает их максимально насыщенными
         */
        void correctColorRange();

        /**
         * @brief showImage
         *  Выводит изображение на экран и ожидает нажатия любой клавиши для закрытия
         * @param image
         *  картинка для вывода
         * @param name
         *  заголовок окна
         * @debug
         */
        void showImage(std::string name, cv::Mat & image);


        /**
         * @brief increaseSizeIn
         *  Увеличивает изображение в multiplier раз, сохраняя пропорции
         * @param image
         *  Картинка для увеличения
         * @param multiplier
         *  множитель: new size = image.size() * multiplier;
         * @debug
         */
        void increaseSizeIn(cv::Mat & image, int multiplier);
        string path;
        cv::Mat sourceImage;
        cv::Mat imageHSV;



        cv::Mat resultImage;
};

#endif // CORRECTION_H
