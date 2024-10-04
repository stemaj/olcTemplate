#ifndef __VIDEOFRAME_HPP
#define __VIDEOFRAME_HPP

#include <olcTemplate/game/coordinates.hpp>
#include <string>
#include <vector>
#include <experimental/propagate_const>

namespace stemaj
{
  class VideoProcessor;

  class VideoFrame
  {
  public:
    explicit VideoFrame(const std::string& filePath);
    virtual ~VideoFrame();
    struct RGB
    {
      uint8_t r;
      uint8_t g;
      uint8_t b;
    };
    std::vector<RGB> Frame(float time);
    PT<int> _videoSize = {};

  private:
    float _currentTimestamp = 0.0f;
    std::vector<RGB> _pixelData;

    int _frameCount;
    float _fps;
  };
}

#endif // __VIDEOFRAME_HPP