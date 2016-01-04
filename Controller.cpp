#include "Controller.h"

Controller::Controller(int argc, char *argv[])
{
    string path = "/home/takava/Documents/Study/Works/individual/";
    DIR * folder = opendir(path.c_str());
    struct dirent * entry;
    string checkType;

    Correction corrector;

    while((entry = readdir(folder)) != nullptr)
    {
        checkType = entry->d_name;
        if(checkType.substr(checkType.find_last_of(".") + 1) == "ppm")
        {
            cout << "Processing for: " << endl;
            cout << path << entry->d_name <<endl;

            corrector.makeCorrection(path + entry->d_name);
        }

    }

    closedir(folder);
}

Controller::~Controller()
{

}
