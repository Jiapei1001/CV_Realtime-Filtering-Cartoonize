// filters.cpp

#include "filters.hpp"

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace filters;

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
