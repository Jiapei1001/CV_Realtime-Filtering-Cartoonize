// filters.hpp

#ifndef filters_hpp
#define filters_hpp

#include <opencv2/core/mat.hpp>

namespace filters {

int greyscale(cv::Mat &src, cv::Mat &dst);

int blur5x5(cv::Mat &src, cv::Mat &dst);

int sobelX3x3(cv::Mat &src, cv::Mat &dst);
int sobelY3x3(cv::Mat &src, cv::Mat &dst);

int magnitude(cv::Mat &sx, cv::Mat &sy, cv::Mat &dst);

}  // namespace filters

#endif /* filters_hpp */