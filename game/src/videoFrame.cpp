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
  _frameCount = static_cast<int>(_videoCapture->get(cv::CAP_PROP_FRAME_COUNT));
}

std::vector<VideoFrame::RGB> VideoFrame::Frame(float timestamp)
{
  // Berechnen, welches Frame dem Timestamp entspricht
  int frameNumber = static_cast<int>(timestamp * _fps);

  if (frameNumber >= _frameCount)
  {
    std::cout << "Error: Timestamp exceeds video duration." << std::endl;
    return {};
  }

  _videoCapture->set(cv::CAP_PROP_POS_FRAMES, frameNumber);

  cv::Mat frame;
  *_videoCapture >> frame;
  if (frame.empty())
  {
    std::cout << "Error: Could not read frame." << std::endl;
    return {};
  }

  std::vector<RGB> pixelData;
  for (int y = 0; y < frame.rows; ++y)
  {
    for (int x = 0; x < frame.cols; ++x)
    {
      cv::Vec3b pixel = frame.at<cv::Vec3b>(y, x);
      //BGR
      pixelData.push_back({
        static_cast<int>(pixel[2]),
        static_cast<int>(pixel[1]),
        static_cast<int>(pixel[0])});
    }
  }
  return pixelData;
}