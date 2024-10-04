#include <olcTemplate/game/videoFrame.hpp>
#include <string>

using namespace stemaj;

VideoFrame::VideoFrame(const std::string& filePath)
{
  _pixelData.reserve(_videoSize.x*_videoSize.y);
  _pixelData.resize(_videoSize.x*_videoSize.y);
}

VideoFrame::~VideoFrame()
{
}

std::vector<VideoFrame::RGB> VideoFrame::Frame(float timestamp)
{
  _currentTimestamp += timestamp;

  return _pixelData;
}
