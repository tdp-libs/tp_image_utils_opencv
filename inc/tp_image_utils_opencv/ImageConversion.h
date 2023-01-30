#ifndef tp_image_utils_opencv_ImageConversion_h
#define tp_image_utils_opencv_ImageConversion_h

#include "tp_image_utils_opencv/Globals.h" // IWYU pragma: keep

namespace tp_image_utils
{
class ColorMap;
class ByteMap;
}

namespace cv
{
class Mat;
}

namespace tp_image_utils_opencv
{

//##################################################################################################
cv::Mat colorMapToMatRGBA(const tp_image_utils::ColorMap& in);

//##################################################################################################
cv::Mat colorMapToMatRGB(const tp_image_utils::ColorMap& in);

//##################################################################################################
cv::Mat byteMapToMat(const tp_image_utils::ByteMap& in);

//##################################################################################################
tp_image_utils::ColorMap colorMapFromMat(const cv::Mat& in);

//##################################################################################################
tp_image_utils::ByteMap byteMapFromMat(const cv::Mat& in);

}

#endif
