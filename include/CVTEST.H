#ifndef __CVTEST_H__
#define __CVTEST_H__

#include <iostream>
#include <string>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui_c.h>
//#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

namespace
{
    Mat src, src_gray, dst,dst1,dst2, map_x, map_y;
    const char* OUTPUT_WIN = "output image";
    int element_size = 3;
    int max_size = 21;
    int threadhold_value = 127;
    int threadhold_max = 255;
    int t1 = 25 ;
    int max_val = 255;
    int index = 0;


    void CallBack_Demo(int, void*)
    {
        int s = element_size *2 +1;
        Mat structureElement = getStructuringElement(MORPH_RECT,Size(s,s),Point(-1,-1));
        // dilate(src,dst,structureElement,Point(-1,-1),1);
        erode(src,dst,structureElement,Point(-1,-1),1);
        imshow(OUTPUT_WIN,dst);
    }

    void Thread_Demo(int, void*)
    {
        cvtColor(src,src_gray,CV_BGR2GRAY);
        threshold(src_gray,dst,threadhold_value,threadhold_max,THRESH_OTSU);
        imshow(OUTPUT_WIN,dst);
    }

    void Canny_demo(int,void*)
    {
        Canny(src_gray,dst,t1,t1 *2,3,false);
        // dst1.create(src.size(),src.type());
        // src.copyTo(dst1,dst);
        imshow(OUTPUT_WIN,~dst);

    }

    void Update_Map()
    {
        for(int row = 0; row < src.rows; ++row)
        {
            for(int col = 0; col < src.cols; ++col)
            {
                switch (index)
                {
                case 0:
                    if(col > (src.cols * 0.25) && col < (src.cols * 0.75) && row >(src.rows * 0.25) && row < (src.rows * 0.75))
                    {
                        map_x.at<float>(row,col) = 2 * (col - (src.cols * 0.25));
                        map_y.at<float>(row,col) = 2 * (row - (src.rows * 0.25));
                    }
                    else
                    {
                        map_x.at<float>(row,col) = 0;
                        map_y.at<float>(row,col) = 0;
                    }

                    break;
                case 1:
                    {
                        map_x.at<float>(row,col) = (src.cols - col - 1);
                        map_y.at<float>(row,col) = row;
                    }
                    break;
                case 2:
                    {
                        map_x.at<float>(row,col) = col;
                        map_y.at<float>(row,col) = src.rows - row - 1;
                    }
                    break;
                case 3:
                    {
                        map_x.at<float>(row,col) = (src.cols - col - 1);
                        map_y.at<float>(row,col) = (src.rows - row - 1);
                    }
                    break;
                default:
                    break;
                }
            }

        }
    }
}





#endif