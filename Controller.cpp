#include "Controller.h"

Controller::Controller(int argc, char *argv[])
{
    string path = "/home/takava/Documents/Study/Works/individual/R/";
    DIR * folder = opendir(path.c_str());

    if(folder != NULL)
    {
        struct dirent * entry;
        string checkType;

        Correction corrector;
        SearchOutlines searcher;
        ContourAnalis analisator;

        int countFiles = 0;
        while((entry = readdir(folder)) != NULL)
        {
            try
            {
                checkType = entry->d_name;
                if(checkType.substr(checkType.find_last_of(".") + 1) == "ppm")
                {

                    cout << countFiles <<") Processing for: ";
                    countFiles ++;
                    cout << path << entry->d_name <<endl;
                    const vector<cv::Mat> * correctedImage = corrector.makeCorrection(path + entry->d_name);
                    list<Storrage*> * contours = searcher.search(correctedImage);

                    analisator.makeAnalis(contours);

                    delete correctedImage;
                    correctedImage = nullptr;
                    for(Storrage * s: *contours)
                    {
                        delete s;
                    }
                    delete contours;
                }
             }
             catch(const std::exception &e)
             {
                cout << "Expextion" <<endl;
             }

        }

        closedir(folder);
    }
    else
    {
        cout << "Can't to open directory" <<endl;
    }


}

Controller::~Controller()
{

}
