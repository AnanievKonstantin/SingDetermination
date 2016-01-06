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
         * @brief isWhite
         *  Определяет является ли пиксель оттенком белого
         * @param pixel пиксель в BGR
         * @return true если является, else false
         */
        bool isWhite(const cv::Vec3b & pixel);


        /**
         * @brief isRed
         *  Определяет является ли пиксель оттенком красного
         * @param pixel
         *  пиксель в BGR
         * @return true если является, else false
         */
        bool isRed(const cv::Vec3b & pixel);


        /**
         * @brief isYellow
         *  определит является ли пиксель оттенком желтого
         * @param pixel
         *  пиксель в BGR
         * @return
         *  true если является, else false
         */
        bool isYellow(const cv::Vec3b & pixel);

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


        /**
         * @brief increaseContrast
         *  увеличивает контраст изображения
         * @param image
         *  Изображение для контрастирования в BGR
         * @param alpha
         *  коэффициент увеличения alpha in [1.0, 3.0]
         */
        void increaseContrast(cv::Mat & image, double alpha);


        /**
         * @brief findRYW
         *  Сделает красный, желтый и белый цвета абсолютными:
         *  белый (255,255,255)
         *  красный (0,0,255)
         *  желтый (0,255,255)
         * @param image
         *  изображение в BGR
         * @return
         *  vector [red,yellow, white]
         */
        vector<cv::Mat> & findRYW(const cv::Mat & image);

        string path;
        cv::Mat sourceImage;
        cv::Mat imageHSV;



        cv::Mat resultImage;
};

#endif // CORRECTION_H
