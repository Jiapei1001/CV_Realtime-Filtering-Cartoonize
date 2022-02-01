// filters.cpp

#include "filters.hpp"

#include <math.h>

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace filters;
using namespace std;

void filters::printOptions() {
    // Menu buttons:
    std::cout << "Press following keys to select the effect:" << std::endl;
    std::cout << "1)Original Image \t\t -key 'o' :" << std::endl;
    std::cout << "2)Greyscale Image \t\t -key 'g' :" << std::endl;
    std::cout << "3)Custom Grey Image \t\t -key 'h' :" << std::endl;
    std::cout << "4)Gaussian Blurred Image \t -key 'b' :" << std::endl;
    std::cout << "5)Sobel in x direction \t\t -key 'x' :" << std::endl;
    std::cout << "6)Sobel in y direction \t\t -key 'y' :" << std::endl;
    std::cout << "7)Sobel Magnitude \t\t -key 'm' :" << std::endl;
    std::cout << "8)Burred and Quantized Image \t -key 'l' :" << std::endl;
    std::cout << "\tUse key '-' to decrease and key '=' to increase quantize level. Default level is set to 15." << std::endl;
    std::cout << "9)Cartoonized Image \t\t -key 'c' :" << std::endl;
    std::cout << "\tUse key '[' to decrease and key ']' to increase cartoonized magnitude threshod. Default level is set to 18." << std::endl;
    std::cout << "10)Invert an Image \t\t -key 'n' :" << std::endl;
    std::cout << "11)Apply Pencil Sketch \t\t -key '1' :" << std::endl;
    std::cout << "12)Apply Green Spot Contour \t -key '2' :" << std::endl;
    std::cout << "13)Apply Canny Edge Detection \t -key '3' :" << std::endl;
    std::cout << "14)Apply Gabor Kernel Texture \t -key '4' :" << std::endl;
    std::cout << "15)Save Image \t\t\t -key 's' :" << std::endl;
}

int processBoundary(int total, int x) {
    if (x < 0) {
        return -x - 1;
    }
    if (x >= total) {
        return 2 * total - x - 1;
    }
    return x;
}

// Customized greyscale function that accesses G, B, R channels
// and applys the value of channel G to B and R
int filters::greyscale(cv::Mat &src, cv::Mat &dst) {
    dst = src.clone();

    for (int y = 0; y < dst.rows; y++) {
        for (int x = 0; x < dst.cols; x++) {
            cv::Vec3b t = dst.at<cv::Vec3b>(y, x);
            t.val[1] = t.val[0];
            t.val[2] = t.val[0];
            dst.at<cv::Vec3b>(y, x) = t;
        }
    }

    return 0;
}

// Apply a 5x5 Gaussian filter
int filters::blur5x5(cv::Mat &src, cv::Mat &dst) {
    Mat temp;
    float r, c;

    float co[] = {1, 2, 4, 2, 1};

    temp = src.clone();
    dst = src.clone();

    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            float sum[] = {0.0, 0.0, 0.0};

            for (int i = -2; i <= 2; i++) {
                r = processBoundary(src.rows, y - i);

                cv::Vec3b p = src.at<cv::Vec3b>(r, x);

                sum[0] += p[0] * co[i + 2];
                sum[1] += p[1] * co[i + 2];
                sum[2] += p[2] * co[i + 2];
            }

            for (int i = 0; i < 3; i++) {
                sum[i] /= 10;
            }

            cv::Vec3b t = temp.at<cv::Vec3b>(y, x);
            t.val[0] = sum[0];
            t.val[1] = sum[1];
            t.val[2] = sum[2];
            temp.at<cv::Vec3b>(y, x) = t;
        }
    }

    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            float sum[] = {0.0, 0.0, 0.0};

            for (int i = -2; i <= 2; i++) {
                c = processBoundary(src.cols, x - i);

                cv::Vec3b p = temp.at<cv::Vec3b>(y, c);

                sum[0] += p[0] * co[i + 2];
                sum[1] += p[1] * co[i + 2];
                sum[2] += p[2] * co[i + 2];
            }

            for (int i = 0; i < 3; i++) {
                sum[i] /= 10;
            }

            cv::Vec3b p = dst.at<cv::Vec3b>(y, x);
            p.val[0] = sum[0];
            p.val[1] = sum[1];
            p.val[2] = sum[2];
            dst.at<cv::Vec3b>(y, x) = p;
        }
    }

    return 0;
}

// Apply sobel filter
int apply_sobel(cv::Mat &src, cv::Mat &dst, double co_r[], double co_c[]) {
    cv::Mat temp(src.rows, src.cols, CV_16SC3);
    int r, c;

    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            float sum[] = {0.0, 0.0, 0.0};

            for (int i = -1; i <= 1; i++) {
                r = processBoundary(src.rows, y - i);

                cv::Vec3b p = src.at<cv::Vec3b>(r, x);

                sum[0] += p.val[0] * co_r[i + 1];
                sum[1] += p.val[1] * co_r[i + 1];
                sum[2] += p.val[2] * co_r[i + 1];
            }

            for (int i = 0; i < 3; i++) {
                sum[i] /= 1;
            }

            // NOTE: here is cv::Vec3s as type CV_16S3C, for range of -255 to 255
            // it is not CV_8UC3, unsigned char
            cv::Vec3s t = temp.at<cv::Vec3s>(y, x);
            t.val[0] = sum[0];
            t.val[1] = sum[1];
            t.val[2] = sum[2];
            temp.at<cv::Vec3s>(y, x) = t;
        }
    }

    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            float sum[] = {0.0, 0.0, 0.0};

            for (int i = -1; i <= 1; i++) {
                c = processBoundary(src.cols, x - i);

                cv::Vec3s p = temp.at<cv::Vec3s>(y, c);  // CV_16S3C

                sum[0] += p.val[0] * co_c[i + 1];
                sum[1] += p.val[1] * co_c[i + 1];
                sum[2] += p.val[2] * co_c[i + 1];
            }

            for (int i = 0; i < 3; i++) {
                sum[i] /= 4;
            }

            cv::Vec3s t = dst.at<cv::Vec3s>(y, x);
            t.val[0] = sum[0];
            t.val[1] = sum[1];
            t.val[2] = sum[2];
            dst.at<cv::Vec3s>(y, x) = t;
        }
    }

    return 0;
}

// A 3x3 Sobel X filter - captures horizontal changes
int filters::sobelX3x3(cv::Mat &src, cv::Mat &dst) {
    // note the r & c sequence
    double co_c[] = {-1.0, 0.0, 1.0};
    double co_r[] = {1.0, 2.0, 1.0};

    apply_sobel(src, dst, co_r, co_c);
    return 0;
}

// A 3x3 Sobel Y filter - captures vertical changes
int filters::sobelY3x3(cv::Mat &src, cv::Mat &dst) {
    // note the r & c sequence
    double co_c[] = {1.0, 2.0, 1.0};
    double co_r[] = {1.0, 0.0, -1.0};

    apply_sobel(src, dst, co_r, co_c);
    return 0;
}

// Generates a gradient magnitude image from the X and Y Sobel images
int filters::magnitude(cv::Mat &sx, cv::Mat &sy, cv::Mat &dst) {
    for (int y = 0; y < sx.rows; y++) {
        for (int x = 0; x < sx.cols; x++) {
            cv::Vec3s h = sx.at<cv::Vec3s>(y, x);
            cv::Vec3s v = sy.at<cv::Vec3s>(y, x);
            cv::Vec3b t = dst.at<cv::Vec3b>(y, x);

            for (int i = 0; i < 3; i++) {
                t.val[i] = (unsigned char)sqrt(h[i] * h[i] + v[i] * v[i]);
            }

            dst.at<cv::Vec3b>(y, x) = t;
        }
    }

    return 0;
}

// Blurs and quantizes a color image
int filters::blurQuantize(cv::Mat &src, cv::Mat &dst, int levels) {
    // Blur
    filters::blur5x5(src, dst);

    int bucket = 255 / levels;

    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            cv::Vec3b p = dst.at<cv::Vec3b>(y, x);
            p[0] = p[0] / bucket * bucket;
            p[1] = p[1] / bucket * bucket;
            p[2] = p[2] / bucket * bucket;
            dst.at<cv::Vec3b>(y, x) = p;
        }
    }

    return 0;
}

// Cartoonizes a color image
int filters::cartoon(cv::Mat &src, cv::Mat &dst, int levels, int magThreshold) {
    // signed short, apply sobel X & Y
    cv::Mat sol16_x(src.rows, src.cols, CV_16SC3);
    cv::Mat sol16_y(src.rows, src.cols, CV_16SC3);

    filters::sobelX3x3(src, sol16_x);
    filters::sobelY3x3(src, sol16_y);

    // unsigned char, apply magnitude
    cv::Mat tempMag(src.rows, src.cols, CV_8UC3);
    filters::magnitude(sol16_x, sol16_y, tempMag);

    // unsigned char, apply quantize
    filters::blurQuantize(src, dst, levels);

    // unsigned char, black
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            cv::Vec3b m = tempMag.at<cv::Vec3b>(y, x);
            cv::Vec3b t = dst.at<cv::Vec3b>(y, x);

            for (int i = 0; i < 3; i++) {
                if (m[i] > magThreshold) {
                    t[i] = 0;
                }
            }

            dst.at<cv::Vec3b>(y, x) = t;
        }
    }

    return 0;
}

// Apply a Filter to invert an image
int filters::invert(cv::Mat &src, cv::Mat &dst) {
    cv::Mat sub_mat(src.rows, src.cols, CV_8UC3);

    // fill solid white color
    sub_mat = cv::Scalar(255, 255, 255);

    cv::subtract(sub_mat, src, dst);

    return 0;
}

// Apply Contour Filter
int filters::contour(cv::Mat &src, cv::Mat &dst) {
    cv::Mat temp1(src.rows, src.cols, CV_8UC3);
    cv::Mat temp2(src.rows, src.cols, CV_8UC3);

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    cv::cvtColor(src, temp1, COLOR_BGR2GRAY);
    cv::threshold(temp1, temp2, 100, 255, THRESH_BINARY);
    cv::findContours(temp2, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

    dst = src.clone();
    cv::drawContours(dst, contours, -1, cv::Scalar(0, 255, 0), 6, LINE_AA, hierarchy, 1000, cv::Point());

    return 0;
}

// Apply Canny Edge for Images
int filters::cannyEdgeImg(cv::Mat &src, cv::Mat &dst) {
    cv::Mat edge(src.rows, src.cols, CV_8UC3);
    cv::Mat grey(src.rows, src.cols, CV_8UC3);

    // reset to avoid infinite loop
    dst = src.clone();

    for (int i = 0; i < 22; i++) {
        cv::cvtColor(dst, grey, COLOR_BGR2GRAY);
        // threshold range [6, 100]
        cv::Canny(grey, edge, 6, 180, 3);

        cv::cvtColor(edge, edge, COLOR_GRAY2BGR);
        edge = edge.mul(cv::Scalar(255, 0, 0), 1);
        dst += edge;
    }

    return 0;
}

// Apply Canny Edge for Videos
int filters::cannyEdgeVid(cv::Mat &src, cv::Mat &dst) {
    cv::Mat edge(src.rows, src.cols, CV_8UC3);
    cv::Mat grey(src.rows, src.cols, CV_8UC3);

    // reset to avoid infinite loop
    dst = src.clone();

    cv::cvtColor(dst, grey, COLOR_BGR2GRAY);
    // threshold range [6, 100]
    cv::Canny(grey, edge, 6, 180, 3);

    cv::cvtColor(edge, edge, COLOR_GRAY2BGR);
    edge = edge.mul(cv::Scalar(255, 0, 0), 1);
    dst += edge;

    return 0;
}

// Builds a Gabor kernel and apply it as a filter
int filters::gabor(cv::Mat &src, cv::Mat &dst) {
    cv::Mat kernel1;
    cv::Mat kernel2;
    cv::Mat kernel3;
    cv::Mat kernel4;

    int kernel_size = 4;
    double sigma = 5.0;
    double theta1 = 0;
    double theta2 = 1 * M_PI / 4;
    double theta3 = 2 * M_PI / 4;
    double theta4 = 3 * M_PI / 4;

    double lamda = 6;
    double gamma = 0.9;
    double phi = 0.4;

    kernel1 = cv::getGaborKernel(cv::Size(kernel_size, kernel_size), sigma, theta1, lamda, gamma, CV_32F);
    kernel2 = cv::getGaborKernel(cv::Size(kernel_size, kernel_size), sigma, theta2, lamda, gamma, CV_32F);
    kernel3 = cv::getGaborKernel(cv::Size(kernel_size, kernel_size), sigma, theta3, lamda, gamma, CV_32F);
    kernel4 = cv::getGaborKernel(cv::Size(kernel_size, kernel_size), sigma, theta4, lamda, gamma, CV_32F);

    cv::Mat temp1(src.rows, src.cols, CV_8UC3);
    cv::filter2D(src, temp1, CV_8UC3, kernel1);

    cv::Mat temp2(src.rows, src.cols, CV_8UC3);
    cv::filter2D(temp1, temp2, CV_8UC3, kernel2);

    cv::Mat temp3(src.rows, src.cols, CV_8UC3);
    cv::filter2D(temp2, temp3, CV_8UC3, kernel3);

    cv::filter2D(temp3, dst, CV_8UC3, kernel4);

    // convert black color
    for (int y = 0; y < dst.rows; y++) {
        for (int x = 0; x < dst.cols; x++) {
            cv::Vec3b p = dst.at<cv::Vec3b>(y, x);
            if (p[0] <= 8 && p[1] <= 8 && p[2] <= 8) {
                p[0] = 255;
                p[1] = 0;
                p[2] = 0;
            }
            dst.at<cv::Vec3b>(y, x) = p;

            cv::Vec3b q = dst.at<cv::Vec3b>(y, x);
            if (p[0] >= 240 && p[1] >= 240 && p[2] >= 240) {
                p[0] = 0;
                p[1] = 255;
                p[2] = 0;
            }
            dst.at<cv::Vec3b>(y, x) = q;
        }
    }

    return 0;
}