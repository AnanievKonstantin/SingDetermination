#include "Controller.h"

Controller::Controller(int argc, char *argv[])
{
    string path = "/home/takava/Documents/Study/Works/individual/Ones/";
    DIR * folder = opendir(path.c_str());
    struct dirent * entry;
    string checkType;

    Correction corrector;
    SearchOutlines searcher;
    ContourAnalis analisator;

    while((entry = readdir(folder)) != NULL)
    {
        checkType = entry->d_name;
        if(checkType.substr(checkType.find_last_of(".") + 1) == "ppm")
        {
            cout << "Processing for: " << endl;
            cout << path << entry->d_name <<endl;
            const vector<cv::Mat> * correctedImage = corrector.makeCorrection(path + entry->d_name);
            list<Storrage*> * contours = searcher.search(correctedImage);

            analisator.makeAnalis(contours);

            delete correctedImage;
            correctedImage = nullptr;

            for(Storrage * iteam: *contours)
            {
                delete iteam;
                iteam = nullptr;
            }

            delete contours;
        }

    }

    closedir(folder);
}

Controller::~Controller()
{

}
