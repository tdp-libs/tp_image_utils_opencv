#include "tp_image_utils_opencv/ImageConversion.h"

#include "tp_image_utils/ColorMap.h"
#include "tp_image_utils/ByteMap.h"

#include <opencv2/core.hpp>

namespace tp_image_utils_opencv
{

//##################################################################################################
cv::Mat colorMapToMatRGBA(const tp_image_utils::ColorMap& in)
{
  int rows = int(in.height());
  int cols = int(in.width());

  cv::Mat mat(rows, cols, CV_8UC4);

  {
    const TPPixel* i = in.constData();
    const TPPixel* iMax = i+(rows*cols);
    uint8_t* o = mat.data;
    for(; i<iMax; i++, o+=4)
    {
      o[0] = i->r;
      o[1] = i->g;
      o[2] = i->b;
      o[3] = i->a;
    }
  }

  return mat;
}

//##################################################################################################
cv::Mat colorMapToMatRGB(const tp_image_utils::ColorMap& in)
{
  cv::Mat mat(int(in.height()), int(in.width()), CV_8UC3, cv::Scalar(0, 0, 0));

  auto data = in.constData();

  for(size_t y=0; y<in.height(); y++)
  {
    for(size_t x=0; x<in.width(); x++, data++)
    {
      mat.at<cv::Vec3b>(cv::Point(x,y)) = cv::Vec3b(data->b, data->g, data->r);
    }
  }

  return mat;
}

//##################################################################################################
cv::Mat byteMapToMat(const tp_image_utils::ByteMap& in)
{
  int rows = int(in.height());
  int cols = int(in.width());

  cv::Mat mat(rows, cols, CV_8UC1);

  {
    const uint8_t* i = in.constData();
    const uint8_t* iMax = i+in.size();
    uint8_t* o = mat.data;
    for(; i<iMax; i++, o++)
    {
      (*o) = (*i);
    }
  }

  return mat;
}

//##################################################################################################
tp_image_utils::ColorMap colorMapFromMat(const cv::Mat& in)
{
  auto rows = size_t(in.rows);
  auto cols = size_t(in.cols);

  tp_image_utils::ColorMap out(cols, rows);
  auto data = out.data();

  if(in.type() == CV_8UC4)
  {
    for(size_t y=0; y<out.height(); y++)
    {
      for(size_t x=0; x<out.width(); x++, data++)
      {
        const auto vec = in.at<cv::Vec4b>(cv::Point(x,y));
        data->r = vec.val[2];
        data->g = vec.val[1];
        data->b = vec.val[0];
        data->a = vec.val[3];
      }
    }
  }

  else if(in.type() == CV_8UC3)
  {
    for(size_t y=0; y<out.height(); y++)
    {
      for(size_t x=0; x<out.width(); x++, data++)
      {
        const auto vec = in.at<cv::Vec3b>(cv::Point(x,y));
        data->r = vec.val[2];
        data->g = vec.val[1];
        data->b = vec.val[0];
      }
    }
  }

  else if(in.type() == CV_8UC1)
  {
    for(size_t y=0; y<out.height(); y++)
    {
      for(size_t x=0; x<out.width(); x++, data++)
      {
        const auto val = in.at<uchar>(cv::Point(x,y));
        data->r = val;
        data->g = val;
        data->b = val;
      }
    }
  }
  else
  {
    return tp_image_utils::ColorMap();
  }

  return out;
}

//##################################################################################################
tp_image_utils::ByteMap byteMapFromMat(const cv::Mat& in)
{
  auto rows = size_t(in.rows);
  auto cols = size_t(in.cols);

  if(in.type() != CV_8UC1)
    return tp_image_utils::ByteMap();

  tp_image_utils::ByteMap out(cols, rows);

  {
    uint8_t* o = out.data();
    uint8_t* oMax = o+(rows*cols);
    uint8_t* i = in.data;
    for(; o<oMax; i++, o+=4)
      (*o) = (*i);
  }

  return out;
}

}
