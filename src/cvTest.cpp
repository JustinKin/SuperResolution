/*
                           _ooOoo_
                          o8888888o
                          88" . "88
                          (| -_- |)
                          O\  =  /O
                       ____/`---'\____
                     .'  \\|     |//  `.
                    /  \\|||  :  |||//  \
                   /  _||||| -:- |||||-  \
                   |   | \\\  -  /// |   |
                   | \_|  ''\---/''  |   |
                   \  .-\__  `-`  ___/-. /
                 ___`. .'  /--.--\  `. . __
              ."" '<  `.___\_<|>_/___.'  >'"".
             | | :  `- \`.;`\ _ /`;.`/ - ` : | |
             \  \ `-.   \_ __\ /__ _/   .-` /  /
        ======`-.____`-.___\_____/___.-`____.-'======
                           `=---='
        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
            一心向善	好运相伴	佛祖保佑	永无BUG
*/

#include <iostream>
#include <string>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <cmath>
//#include <opencv2/core/core.hpp>
#include "CVTEST.H"

using namespace std;
using namespace cv;


void Canny_demo(int,void*);
int main(int argc, char **argv)
{
    cout << "\nMission Start:  \n";
    auto start = chrono::high_resolution_clock::now();
    //=================================================================//
    string file_1("D:/123.jpg"),
        file_2("D:/123_addWeighted.jpg"),
        file_3("D:/123_t.jpg");

    Mat img_1 = imread(file_1, 1), img_2 = imread(file_2, 1), img_3 = imread(file_3, 1), img_4, img_5;
    src = imread(file_1);
    if (!src.data)
    {
        cerr << "read file error !\n";
        return -1;
    }

    cvtColor(img_1, img_1, CV_BGR2HSV);
    cvtColor(img_2, img_2, CV_BGR2HSV);
    cvtColor(img_3, img_3, CV_BGR2HSV);

    int h_bins = 50, s_bins = 60;
    int histSize[] = { h_bins, s_bins};
    // jue varies from 0 - 179, saturation from 0 - 255
    float h_ranges[] = { 0, 180 };
    float s_ranges[] = { 0, 256 };
    float const *ranges[] = {h_ranges, s_ranges};
    // use 0, 1 channels
    int channels[] = {0, 1};
    MatND hist_base;
    MatND hist_test1;
    MatND hist_test2;

    calcHist(&img_1, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false);
    normalize(hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat());

    calcHist(&img_2, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false);
    normalize(hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat());

    double img1_2 = compareHist(hist_base, hist_test1, CV_COMP_CORREL);
    putText(img_1, to_string(img1_2), Point(50,50), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,255), 2, LINE_AA);
    imshow("calcHist1", img_1);


    // imshow("img_4", img_4);




















    waitKey(0);
    //=================================================================//
    cout << "\n\n";
    auto end = chrono::high_resolution_clock::now();
    cout << "Elapsed Time:  " << std::chrono::duration<double>(end - start).count() << " s\n\n"
         << "**Mission Completed !**\n\n\n"
         << "\a";
    return 0;
}

