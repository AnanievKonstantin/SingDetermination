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
    void drawContour(const vector<cv::Point> &contour);

public:
    ContourAnalis();
    int makeAnalis(list<Storrage*> * contours);
};

#endif // CONTOURANALIS_H
