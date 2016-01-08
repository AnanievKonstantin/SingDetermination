#include "Controller.h"

Controller::Controller(int argc, char *argv[])
{
    string path = "/home/takava/Documents/Study/Works/individual/D/";
    DIR * folder = opendir(path.c_str());
    struct dirent * entry;
    string checkType;

    Correction corrector;
    SearchOutlines searcher;

    while((entry = readdir(folder)) != NULL)
    {
        checkType = entry->d_name;
        if(checkType.substr(checkType.find_last_of(".") + 1) == "ppm")
        {
            cout << "Processing for: " << endl;
            cout << path << entry->d_name <<endl;
            const vector<cv::Mat> * corrected = corrector.makeCorrection(path + entry->d_name);
            searcher.search(corrected);


            delete corrected;
            corrected = nullptr;
        }

    }

    closedir(folder);
}

Controller::~Controller()
{

}
