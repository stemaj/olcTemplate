#ifndef __VIDEOFRAME_HPP
#define __VIDEOFRAME_HPP

#include <olcTemplate/game/coordinates.hpp>
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
    PT<int> _videoSize = {};

  private:
    float _currentTimestamp = 0.0f;
    std::vector<RGB> _pixelData;

    int _frameCount;
    float _fps;
    //std::unique_ptr<cv::VideoCapture> _videoCapture;
  };
}

#endif // __VIDEOFRAME_HPP