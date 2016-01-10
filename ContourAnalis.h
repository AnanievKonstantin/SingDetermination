#ifndef CONTOURANALIS_H
#define CONTOURANALIS_H

#include <Tools.h>
#include <Storrage.h>

/**
 * @brief The ContourAnalis class
 *  Производит анализ контуров
 */
class ContourAnalis
{
private:
    /**
     * @brief drawContour
     *  Рисует контуры
     * @param contour
     *  контуры для отрисовки
     * @debug
     */
    cv::Mat drawContour(const vector<cv::Point> &contour);

    /**
     * @brief circleDetected
     *  Проверяет является ли контур кругом - овалом
     * @param imageWithContour
     *  Изображение с нарисованным контуром
     * @param contour
     *  Точки контура
     * @return
     *  true если распознан как круг иначе false
     */
    bool circleDetected(cv::Mat & imageWithContour, vector<cv::Point> &contour);

    /**
     * @brief rombDetection
     *  определяет является ли контур или ромбом или квадратом или прямоугольником
     * @param imageWithContour
     *  Изображение с нарисованным контуром
     * @param contour
     *  Точки контура
     * @return true если контур распознан как ромб
     */
    bool rombDetection(cv::Mat & imageWithContour, vector<cv::Point> &contour);

    /**
     * @brief triagleDetection
     *  Определяет является ли полученный контур триугольником
     * @param imageWithContour
     *  Изображение с нарисованным контуром
     * @param contour
     *  Точки контура
     * @return
     *  true если контур распознан как триугольник
     */
    bool triagleDetection(cv::Mat & imageWithContour, vector<cv::Point> &contour);

    /**
     * @brief distance
     *  Определяет расстояние между двумя точками
     * @param a
     * @param b
     * @return
     *  расстояние d= sqrt((x2−x1)^2+(y2−y1)^2)
     */
    double distance(cv::Point a, cv::Point b);

    /**
     * @brief CalcProbabilityDetection
     *  Производит расчет верояности определения знаков
     *  исходя из количества найденных контуров для которых функции
     *  triagleDetection, rombDetection, circleDetected вернули true;
     *
     *  Следовательно, вероятность равная 1 означает,
     *  что были обнаружены контуры только одного типа, равная 0 означает,что не было
     *  распознано контуров или есть одинаковое количество распознанных контуров разных типов
     * @param toRect
     *  Число обнаружений контура ромб
     * @param toCircle
     *  Число обнаружений контура круг
     * @param toTriagle
     *  Число обнаружений контура триугольник
     */
    void CalcProbabilityDetection(double toRect, double toCircle, double toTriagle);

public:
    ContourAnalis();
    /**
     * @brief makeAnalis
     *  Производит анализ контуров и выводит результат распознования в консоль
     * @param contours
     *  Контуры для распознования
     */
    void makeAnalis(list<Storrage*> * contours);
};

#endif // CONTOURANALIS_H
