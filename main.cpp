/**
  *@mainpage
  *
  * @author
  * Ананьек Константин
  *
  *@date
  * 04.01.16
  *
  *@brief
  * Программа по определению типа дорожного знака на изображении.
  * Принимает на вход путь к директории, в которой располагаются изображения типы PPM see also Controller.h читает
  * имя изображения из директории. Затем создаёт cv::Mat из изображения по считанному пути. Затем производит
  * коррекции над полученной матрицей see also Correction.h.
  * Скорректированные изображения поступают в see also SearchOutlines.h и там производится поиск контуров по
  * скорректированным изображениям и их HSV значениям. Выделенные контуры поступают в see also ContourAnalis.h,
  * Где выволняет контурный анализ и выявляются круги-овалы(O), ромбы-квадраты(R), триугольники(D).
  * После производится расчет вероятности распознания знака. После выводится результат в вседующем виде:
  * <image number>  ")Processing for:" <image name> ":" <sign type> <probabilityDetection>
  * примеры:<BR>
  * 35) Processing for: O_02780.ppm:  O 0.388889 <BR>
  * 36) Processing for: O_02797.ppm:  O 0.111111  <BR>
  * 37) Processing for: O_03120.ppm:  O 0.0833333 <BR>
  * 38) Processing for: O_03682.ppm:  O 0.0277778 <BR>
  * 39) Processing for: O_04254.ppm:  O 0.222222  <BR>
  * 40) Processing for: O_04556.ppm:  O 0.444444  <BR>
  * 41) Processing for: O_05305.ppm:  O 0.0555556 <BR>
  * 42) Processing for: O_05995.ppm:  O 0.194444  <BR>
  * 43) Processing for: O_06256.ppm:  O 0.527778  <BR>
  * <BR>
  * sign type: определяют слудующие знаки<BR>
  * D - "Уступи дорогу"<BR>
  * R - "Главная дорога"<BR>
  * O - "Движение запрещено"<BR>
  * N - знак не найден или вероятность найти несколько знаков одинакова
  * <BR>
  */

#include <Controller.h>
/**
 * @brief main
 *  точка входа в программу
 * @param argc
 * @param argv
 *  Путь к директории с изображениями
 * @return
 */
int main(int argc, char *argv[])
{
    Controller controller(argc, argv);
    return 0;
}

