// imgDisplay.cpp

#include <iostream>
#include <opencv2/opencv.hpp>

#include "filters.hpp"

using namespace cv;
using namespace filters;

enum mode {
    ORIGINAL = 1,
    GREY = 2,
    CUSTOM_GREY = 3,
    GAUSSIAN = 4,
    SOBEL_X = 5,
    SOBEL_Y = 6,
    MAGNITUDE = 7,
    QUANTIZE = 8,
    CARTOON = 9,
    INVERT = 10,
    PENCIL = 11,
    CONTOUR = 12,
    EDGE = 13,
    GABOR = 14,
} MODE;

int main(int argc, char const *argv[]) {
    std::cout << "OpenCV Hello the world..." << std::endl;

    Mat img = imread("../data/dog.jpg", IMREAD_COLOR);
    namedWindow("image", WINDOW_AUTOSIZE);

    filters::printOptions();

    cv::Mat dst(img.rows, img.cols, CV_8UC3);  // CV_8UC3: 3 unsigned chars for properly displaying a Mat
    cv::Mat temp1(img.rows, img.cols, CV_8UC3);
    cv::Mat temp2(img.rows, img.cols, CV_8UC3);
    cv::Mat sol16_x(img.rows, img.cols, CV_16SC3);  // CV_16SC3: signed short, for [-255, 255]
    cv::Mat sol16_y(img.rows, img.cols, CV_16SC3);

    int quantizeLevel = 15;
    int magThreshold = 18;

    dst = img.clone();

    for (;;) {
        // see if there is a waiting keystroke
        char key = cv::waitKey(10);

        // break the loop
        if (key == 'q') {
            break;
        }

        // assign color mode
        switch (key) {
        case 'o':
            MODE = ORIGINAL;
            break;
        case 'g':
            MODE = GREY;
            break;
        case 'h':
            MODE = CUSTOM_GREY;
            break;
        case 'b':
            MODE = GAUSSIAN;
            break;
        case 'x':
            MODE = SOBEL_X;
            break;
        case 'y':
            MODE = SOBEL_Y;
            break;
        case 'm':
            MODE = MAGNITUDE;
            break;
        case 'l':
            MODE = QUANTIZE;
            quantizeLevel = 15;
            break;
        case 'c':
            MODE = CARTOON;
            quantizeLevel = 15;
            magThreshold = 18;
            break;
        case '=':
            quantizeLevel++;
            break;
        case '-':
            quantizeLevel--;
            break;
        case ']':
            magThreshold++;
            break;
        case '[':
            magThreshold--;
            break;
        case 'n':
            MODE = INVERT;
            break;
        case '1':
            MODE = PENCIL;
            break;
        case '2':
            MODE = CONTOUR;
            break;
        case '3':
            MODE = EDGE;
            break;
        case '4':
            MODE = GABOR;
            break;
        case 's':
            cv::imwrite("/Users/jiapei/Desktop/image.jpg", dst);
            break;
        }

        // render image based on color mode
        switch (MODE) {
        case ORIGINAL:
            cv::imshow("image", img);
            break;
        case GREY:
            cv::cvtColor(img, dst, COLOR_RGBA2GRAY, 0);
            cv::imshow("image", dst);
            break;
        case CUSTOM_GREY:
            filters::greyscale(img, dst);
            cv::imshow("image", dst);
            break;
        case GAUSSIAN:
            filters::blur5x5(img, dst);
            cv::imshow("image", dst);
            break;
        case SOBEL_X:
            filters::sobelX3x3(img, sol16_x);
            cv::convertScaleAbs(sol16_x, dst, 1, 0);  // convert from CV_16S3C to CV_8UC3 for Mat
            cv::imshow("image", dst);
            break;
        case SOBEL_Y:
            filters::sobelY3x3(img, sol16_y);
            cv::convertScaleAbs(sol16_y, dst, 1, 0);  // convert from CV_16S3C to CV_8UC3 for Mat
            cv::imshow("image", dst);
            break;
        case MAGNITUDE:
            filters::sobelX3x3(img, sol16_x);
            filters::sobelY3x3(img, sol16_y);
            filters::magnitude(sol16_x, sol16_y, dst);  // convert from signed short Vec3s to unsigned char Vec3b within the function
            cv::imshow("image", dst);
            break;
        case QUANTIZE:
            filters::blurQuantize(img, dst, quantizeLevel);
            cv::imshow("image", dst);
            break;
        case CARTOON:
            filters::cartoon(img, dst, quantizeLevel, magThreshold);
            cv::imshow("image", dst);
            break;
        case INVERT:
            filters::invert(img, dst);
            cv::imshow("image", dst);
            break;
        case PENCIL:
            cv::pencilSketch(img, temp1, temp2, 10, 0.07f, 0.03f);
            cv::detailEnhance(temp2, dst);
            cv::imshow("image", dst);
            break;
        case CONTOUR:
            filters::contour(img, dst);
            cv::imshow("image", dst);
            break;
        case EDGE:
            filters::cannyEdgeImg(img, dst);
            cv::imshow("image", dst);
            break;
        case GABOR:
            filters::gabor(img, dst);
            cv::imshow("image", dst);
            break;
        default:
            cv::imshow("image", img);
            break;
        }
    }

    return 0;
}