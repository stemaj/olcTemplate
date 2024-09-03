#include <olcTemplate/game/videoFrame.hpp>
#include <opencv2/opencv.hpp>

using namespace stemaj;

VideoFrame::VideoFrame(const std::string& filePath)
{
  _videoCapture = std::make_unique<cv::VideoCapture>(filePath);
  if (!_videoCapture->isOpened())
  {
    std::cout << "Error: Could not open video file." << std::endl;
  }

  _fps = _videoCapture->get(cv::CAP_PROP_FPS);
  _videoSize = { _videoCapture->get(cv::CAP_PROP_FRAME_WIDTH),
    _videoCapture->get(cv::CAP_PROP_FRAME_HEIGHT) };
  _frameCount = static_cast<int>(_videoCapture->get(cv::CAP_PROP_FRAME_COUNT));

  _pixelData.reserve(_videoSize.x*_videoSize.y);
  _pixelData.resize(_videoSize.x*_videoSize.y);
}

std::vector<VideoFrame::RGB> VideoFrame::Frame(float timestamp)
{
  _currentTimestamp += timestamp;
  int frameNumber = static_cast<int>(_currentTimestamp * _fps);

  if (frameNumber >= _frameCount)
  {
    return _pixelData; // Timestamp exceeds video duration
  }

  if (!_videoCapture->set(cv::CAP_PROP_POS_FRAMES, frameNumber))
  {
    return _pixelData;
  }

  cv::Mat frame;
  *_videoCapture.get() >> frame;
  if (frame.empty())
  {
    return _pixelData;
  }

  for (int y = 0; y < frame.rows; ++y)
  {
    for (int x = 0; x < frame.cols; ++x)
    {
      cv::Vec3b pixel = frame.at<cv::Vec3b>(y, x);
      _pixelData.at(y*_videoSize.x+x) = { static_cast<int>(pixel[2]),
        static_cast<int>(pixel[1]),
        static_cast<int>(pixel[0])};
    }
  }
  return _pixelData;
}