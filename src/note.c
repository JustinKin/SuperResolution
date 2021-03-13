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
#include <opencv2/opencv.hpp>
//#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui_c.h>

using namespace std;
using namespace cv;



int note()
{
//begin
    Mat src = imread("/home/justinkin/C/cvTest/img/EastProject.jpg");//1=RGB,0=gray
    if(src.empty())//!src.data
    {
        cout<<"image is ont exit...\n";
        return -1;
    }

    namedWindow("test opencv setup", CV_WINDOW_AUTOSIZE);
    imshow("test opencv setup",src);

    Mat tpic;
    namedWindow("tpic win",1);//1=CV_WINDOW_AUTOSIZE
    cvtColor(src,tpic, CV_BGR2GRAY);
    imshow("tpic win",tpic);
    imwrite("/home/justinkin/C/cvTest/img/EastProject_Gray.jpg",tpic);


//掩膜，锐化？
    Mat pic_read = imread("/home/justinkin/C/cvTest/img/EastProject.jpg");//1=RGB,0=gray
    Mat pic_write;

    int cols = (pic_read.cols - 1) * pic_read.channels(),
        offsetx = pic_read.channels(),
        rows = pic_read.rows;
    pic_write = Mat::zeros(pic_read.size(), pic_read.type());
    for(int row = 1; row < (rows -1); ++row)
    {
        const uchar *previous = pic_read.ptr<uchar>(row - 1),
                    *current = pic_read.ptr<uchar>(row),
                    *next = pic_read.ptr<uchar>(row + 1);
        uchar *output = pic_write.ptr<uchar>(row);
        for(int col = offsetx; col < cols; ++col)
        {//掩膜，锐化？
        output[col] = saturate_cast<uchar>(5 * current[col] -  (current[col - offsetx] + current[col+offsetx] +previous[col] + next[col]));
        }

    }

//file up edge
    const uchar *current_up = pic_read.ptr<uchar>(0), *current_down = pic_read.ptr<uchar>(pic_read.rows-1);
    uchar *output_up = pic_write.ptr<uchar>(0), *output_down = pic_write.ptr<uchar>(pic_read.rows-1);
    for(int i =0; i < (pic_read.cols * pic_read.channels()); ++i)
    {
        output_up[i] = current_up[i];
        output_down[i] = current_down[i];
    }
    for(int i=1; i<pic_read.rows; ++i)
    {
        const uchar *current_left = pic_read.ptr<uchar>(i);
        uchar *output_left = pic_write.ptr<uchar>(i);
        output_left[0] = current_left[0];
        output_left[1] = current_left[1];
        output_left[2] = current_left[2];
        output_left[(pic_read.cols-1)* pic_read.channels()] = current_left[(pic_read.cols-1)* pic_read.channels()];
        output_left[(pic_read.cols-1)* pic_read.channels()+1] = current_left[(pic_read.cols-1)* pic_read.channels()+1];
        output_left[(pic_read.cols-1)* pic_read.channels()+2] = current_left[(pic_read.cols-1)* pic_read.channels()+2];
    }
//using fileter2D
    Mat kernel = (Mat_<char>(3,3)<<0,-1,0,-1,5,-1,0,-1,0);
    filter2D(pic_read, pic_write, -1, kernel);

//constract enhancement
    string  file_1 = "D:/123.jpg",
            file_2 = "D:/123_t.jpg";
    Mat img_in = imread(file_1, 1), img_out;

    if(!img_in.data)
    {
        cout << "file read erro !\n";
        return -1;
    }
    namedWindow(file_1, 1);
    imshow(file_1,img_in);

    size_t  height = img_in.rows,
            width = img_in.cols;
    img_out = Mat::zeros(img_in.size(), img_in.type());
    float alpha = 1.1, beta = 0.618;
    for(int row = 0; row < height; ++row)
    {
        for(int col = 0; col < width; ++col)
        {
            if(img_in.channels() ==3)
            {
                for(size_t i = 0; i<3; ++i)
                    img_out.at<Vec3b>(row,col).val[i] = saturate_cast<uchar>((img_in.at<Vec3b>(row,col).val[i]) * alpha + beta);
            }
            else
            {
                img_out.at<uchar>(row,col) = saturate_cast<uchar>(img_in.at<uchar>(row,col) * alpha + beta);

            }
        }
    }
    namedWindow(file_2,1);
    imshow(file_2,img_out);

//draw geometry
    string  file_1("D:/123.jpg"),
            file_2("D:/123_t.jpg");
    Mat img_1(800, 800, CV_8UC3, Scalar(255,255,255));
    Point p1 = Point(20,30), p2;
    p2.x = 300;
    p2.y = 300;
    Scalar red(0,0,255), blue(255,0,0), green(0,255,0), color(0,255,255), last(255,0,255);
    Point pts[1][5];
    pts[0][0] = Point(100,100);
    pts[0][1] = Point(100,200);
    pts[0][2] = Point(200,200);
    pts[0][3] = Point(200,100);
    pts[0][4] = Point(100,100);
    const Point *ppts[] = { pts[0]};
    int npt[] = {5};
    line(img_1, p1, p2, red, 1, LINE_AA);
    Rect rect(200,100,300,300);//起点，宽，高
    rectangle(img_1,rect,blue,2,8);
    ellipse(img_1,Point(img_1.cols/2,img_1.rows/2),Size(img_1.cols/4,img_1.rows/8),45,0,360,green,2,LINE_AA);
    circle(img_1,Point(img_1.cols/2,img_1.rows/2),150,color,2, LINE_AA);
    fillPoly(img_1,ppts,npt,1,last,LINE_AA);
    putText(img_1,"Hello OpenCV",Point(50,50),CV_FONT_NORMAL,1,red,1,LINE_AA);
    //TODO RNG

//Blur
    Mat img_1=imread(file_1,1), img_2, img_3, img_4, img_5;

    if(img_1.empty())
        {
            cerr<<"read file error"<<endl;
            return -1;
        }

    namedWindow("img_1",1);
    namedWindow("Blur",1);
    namedWindow("GaussBlur",1);
    namedWindow("medianBlur",1);
    namedWindow("bilateralFilter",1);
    imshow("img_1",img_1);

    blur(img_1,img_2,Size(5,5), Point(-1,-1));
    GaussianBlur(img_1,img_3,Size(5,5),3,3);
    medianBlur(img_1, img_4, 5);
    bilateralFilter(img_1, img_5, 5, 100, 3);
    imshow("Blur",img_2);
    imshow("GaussBlur",img_3);
    imshow("medianBlur",img_4);
    imshow("bilateralFilter",img_5);

//dilate & erode
namespace
{
    Mat src, dst;
    char OUTPUT_WIN[] = "output image";
    int element_size = 3;
    int max_size = 21;

    void CallBack_Demo(int, void*)
    {
        int s = element_size *2 +1;
        Mat structureElement = getStructuringElement(MORPH_RECT,Size(s,s),Point(-1,-1));
        // dilate(src,dst,structureElement,Point(-1,-1),1);
        erode(src,dst,structureElement,Point(-1,-1),1);
        imshow(OUTPUT_WIN,dst);
    }
}
    src = imread(file_1);
    if(!src.data)
    {
        cerr<<"read file error !\n";
        return -1;
    }
    namedWindow(file_1,1);
    imshow(file_1,src);

    namedWindow(OUTPUT_WIN,1);
    createTrackbar("Element Size: ",OUTPUT_WIN,&element_size,max_size,CallBack_Demo);
    CallBack_Demo(0,0);

    waitKey(0);
    return 1;

// Morphological
    Mat kernel = getStructuringElement(MORPH_RECT,Size(11,11),Point(-1,-1));
    morphologyEx(src,dst,CV_MOP_OPEN,kernel);

//Extract line
    Mat gray_src(src);
    cvtColor(src,gray_src,CV_BGR2GRAY);
    imshow("result",gray_src);

    Mat binary(src);
    adaptiveThreshold(~gray_src,binary,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,15,-2);
    imshow("binary",binary);

    Mat hline = getStructuringElement(MORPH_RECT,Size(src.cols / 16, 1), Point(-1,-1));
    Mat vline = getStructuringElement(MORPH_RECT,Size(1, src.rows / 16), Point(-1,-1));
    // morphologyEx(binary,dst,CV_MOP_OPEN,hline,Point(-1,-1));//erode -> dilate
    morphologyEx(binary,dst,CV_MOP_OPEN,vline,Point(-1,-1));
    bitwise_not(dst,dst);
    GaussianBlur(dst,dst,Size(3,3),1,1);
    imshow("final",dst);

// pyramid, DOG
    pyrUp(img_1, dst, Size(img_1.cols*2, img_1.rows*2));
    pyrDown(img_1, img_2, Size(img_2.cols/2, img_2.rows/2));

    cvtColor(img_1,img_3, CV_BGR2GRAY);
    Mat g1, g2, dog;
    GaussianBlur(img_3,g1,Size(5,5),0,0);
    GaussianBlur(g1,g2,Size(5,5),0,0);
    subtract(g1,g2,dog,Mat());//2-1
    normalize(dog,dog,255,0,NORM_MINMAX);
    imshow("dog",dog);

// threshold
    Mat src, src_gray, dst;
    const char* OUTPUT_WIN = "output image";
    int threadhold_value = 127;
    int threadhold_max = 255;
    void Thread_Demo(int, void*)
    {
        cvtColor(src,src_gray,CV_BGR2GRAY);
        threshold(src_gray,dst,threadhold_value,threadhold_max,THRESH_OTSU);
        imshow(OUTPUT_WIN,dst);
    }
    imshow("input",img_1);
    namedWindow(OUTPUT_WIN,1);
    cvtColor(img_1,img_2,CV_BGR2GRAY);
    createTrackbar("Threadhold Value",OUTPUT_WIN,&threadhold_value,threadhold_max,Thread_Demo);
    Thread_Demo(0,0);

    //拉普拉斯
    Mat kernel_x = (Mat_<int>(3,3)<<0,-1,0,-1,4,-1,0,-1,0);
    filter2D(src,dst1,-1,kernel_x,Point(-1,-1),0.0);
    imshow(OUTPUT_WIN,dst1);

    //Sobel Y
    Mat kernel_y = (Mat_<int>(3,3)<<-1,-2,-1,0,0,0,1,2,1);
    filter2D(src,dst2,-1,kernel_y,Point(-1,-1),0.0);
    imshow("2",dst2);

    //deal with edge
    int top = 0.05*src.rows;
    int bottom = 0.05*src.rows;
    int left = 0.05*src.cols;
    int right = 0.05*src.cols;
    copyMakeBorder(src, dst,top,bottom,left,right,BORDER_REFLECT_101);

    //Sobel, Scharr
    GaussianBlur(img_1,img_2,Size(3,3),0,0);
    cvtColor(img_2,img_3, CV_BGR2GRAY);
    imshow(OUTPUT_WIN, img_3);
    Mat img_x, img_y;
    Sobel(img_3,img_x,CV_16S,1,0,3);
    Sobel(img_3,img_y,CV_16S,0,1,3);
    // Scharr(img_3,img_x,CV_16S,1,0,3);
    // Scharr(img_3,img_y,CV_16S,0,1,3);
    convertScaleAbs(img_x,img_x);
    convertScaleAbs(img_y,img_y);
    imshow("Sobelx", img_x);
    imshow("Sobely", img_y);
    dst = Mat(img_x.size(),img_y.type());
    for(int row = 0; row < img_x.rows; ++row)
    {
        for(int col = 0; col < img_x.cols; ++col)
        {
            int xg = img_x.at<uchar>(row,col);
            int yg = img_y.at<uchar>(row,col);
            // dst.at<uchar>(row,col) = saturate_cast<uchar>(xg + yg);
            dst.at<uchar>(row,col) = saturate_cast<uchar>(sqrt(xg * xg + yg * yg));
        }
    }
    // addWeighted(img_x,0.5,img_y,0.5,0,dst);
    imshow("add",dst);

    // Laplacian
    GaussianBlur(img_1,img_2,Size(3,3),0,0);
    cvtColor(img_2,src_gray,CV_BGR2GRAY);
    imshow("Gray", src_gray);
    Laplacian(src_gray,dst,CV_16S,3);
    convertScaleAbs(dst,dst);
    // threshold(dst,dst,0,255,THRESH_OTSU | THRESH_BINARY);
    imshow("Laplacian",dst);

    //Canny
    namedWindow(OUTPUT_WIN, 1);
    GaussianBlur(img_1,img_2,Size(3,3),0,0);
    cvtColor(img_2,src_gray,CV_BGR2GRAY);
    createTrackbar("threshold value : ", OUTPUT_WIN,&t1,max_val,Canny_demo);
    Canny_demo(0,0);

    // HoughLine
    Canny(img_1,img_2,100,200);
    imshow("output", img_2);
    cvtColor(img_2,dst,CV_GRAY2BGR);
    vector<Vec4f> plines;
    HoughLinesP(img_2,plines,1,CV_PI/180.0,50,30,2);
    Scalar color = Scalar(0, 0, 255);
    for(size_t i = 0; i <plines.size(); ++i)
    {
        Vec4f hline = plines[i];
        line(dst,Point(hline[0],hline[1]),Point(hline[2],hline[3]),color,1,LINE_AA);
    }
    imshow("hough line ",dst);

    // HoughCircles
    medianBlur(img_1,img_2,3);
    // imshow("mout", img_2);
    cvtColor(img_2,img_3,CV_BGR2GRAY);
    vector<Vec3f> pcircles;
    HoughCircles(img_3,pcircles,HOUGH_GRADIENT,1,10,100,50,5,50);
    img_1.copyTo(img_3);
    for(size_t i = 0 ; i<pcircles.size(); ++i)
    {
        Vec3f cc = pcircles[i];
        circle(img_3,Point(cc[0],cc[1]),cc[2],Scalar(0,0,255),1,LINE_AA);
        circle(img_3,Point(cc[0],cc[1]),2,Scalar(0,0,255),2,LINE_AA);
    }
    imshow("mout", img_3);

    // remap
    map_x.create(src.size(), CV_32FC1);
    map_y.create(src.size(), CV_32FC1);

    int c = 0;
    while(true)
    {
        c = waitKey(500);
        if((char)c == 27)
        {
            break;
        }
        index = c%4;
        Update_Map();
        remap(src,dst,map_x,map_y,INTER_LINEAR,BORDER_CONSTANT,Scalar(0,255,255));
        imshow("dst",dst);
    }

    // equalizeHist
    cvtColor(img_1,img_2,CV_BGR2GRAY);
    equalizeHist(img_2,img_3);


    // compareHist
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




}