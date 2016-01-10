#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Tools.h>
#include <Correction.h>
#include <SearchOutlines.h>
#include <ContourAnalis.h>

/**
 * @brief The Controller class
 *  Контролиоует процесс выволнения программы. Организует основной цикл программы.
 */
class Controller
{
public:
    Controller(int argc, char *argv[]);
    ~Controller();
private:
};

#endif // CONTROLLER_H
