#ifndef __VIDEOFRAME_HPP
#define __VIDEOFRAME_HPP

#include "b2_types.h"
#include "olcTemplate/game/src/tools/videoLoader.hpp"
#include <olcTemplate/game/coordinates.hpp>
#include <memory>
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

    std::unique_ptr<VideoProcessor> l;


    class FFmpegImpl;
    FFmpegImpl* ffmpeg;
  };
}

#endif // __VIDEOFRAME_HPP