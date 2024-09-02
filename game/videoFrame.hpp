#ifndef __VIDEOFRAME_HPP
#define __VIDEOFRAME_HPP

#include <memory>
#include <string>
#include <vector>

namespace cv {
  class VideoCapture;
}

namespace stemaj
{
  class VideoFrame
  {
  public:
    explicit VideoFrame(const std::string& filePath);
    struct RGB
    {
      int r;
      int g;
      int b;
    };
    std::vector<RGB> Frame(float time);

  private:
    int _frameCount;
    float _fps;
    std::unique_ptr<cv::VideoCapture> _videoCapture;
  };
}

#endif // __VIDEOFRAME_HPP