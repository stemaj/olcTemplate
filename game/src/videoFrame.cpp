#include <olcTemplate/game/videoFrame.hpp>
#include <iostream>

extern "C" {
    #include <olcTemplate/sdk/ffmpeg-7.0.2/include/libavformat/avformat.h>
    #include <olcTemplate/sdk/ffmpeg-7.0.2/include/libavcodec/avcodec.h>
    #include <olcTemplate/sdk/ffmpeg-7.0.2/include/libswscale/swscale.h>
}

using namespace stemaj;

VideoFrame::VideoFrame(const std::string& filePath)
{
  AVFormatContext* fmt_ctx = nullptr;
    AVCodecContext* codec_ctx = nullptr;
    AVFrame* frame = nullptr;
    AVFrame* rgb_frame = nullptr;
    AVPacket* packet = nullptr;
    SwsContext* sws_ctx = nullptr;
    int video_stream_index = -1;

const char* filename;
    // FFmpeg initialisieren
        //av_register_all();

        // Video öffnen
        if (avformat_open_input(&fmt_ctx, filename, nullptr, nullptr) != 0) {
            std::cerr << "Konnte Video nicht öffnen\n";
            return;
        }

        // Streams suchen
        if (avformat_find_stream_info(fmt_ctx, nullptr) < 0) {
            std::cerr << "Konnte Stream-Infos nicht finden\n";
            return;
        }

        // Videostream finden
        video_stream_index = -1;
        for (unsigned int i = 0; i < fmt_ctx->nb_streams; i++) {
            if (fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
                video_stream_index = i;
                break;
            }
        }

        if (video_stream_index == -1) {
            std::cerr << "Kein Videostream gefunden\n";
            return;
        }

        // Codec für den Videostream öffnen
        AVCodec* codec = (AVCodec*)avcodec_find_decoder(fmt_ctx->streams[video_stream_index]->codecpar->codec_id);
        if (!codec) {
            std::cerr << "Codec nicht gefunden\n";
            return;
        }

        codec_ctx = avcodec_alloc_context3(codec);
        if (avcodec_parameters_to_context(codec_ctx, fmt_ctx->streams[video_stream_index]->codecpar) < 0) {
            std::cerr << "Konnte Codec-Kontext nicht initialisieren\n";
            return;
        }

        if (avcodec_open2(codec_ctx, codec, nullptr) < 0) {
            std::cerr << "Konnte Codec nicht öffnen\n";
            return;
        }

        // Frames und Pakete vorbereiten
        frame = av_frame_alloc();
        rgb_frame = av_frame_alloc();
        packet = av_packet_alloc();

        // SwsContext für die Konvertierung zu RGB erstellen
        sws_ctx = sws_getContext(codec_ctx->width, codec_ctx->height, codec_ctx->pix_fmt,
                                 codec_ctx->width, codec_ctx->height, AV_PIX_FMT_RGB24,
                                 SWS_BILINEAR, nullptr, nullptr, nullptr);

        // Platz für RGB-Frame-Daten reservieren
        //int num_bytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24, codec_ctx->width, codec_ctx->height, 1);
        //std::vector<uint8_t> buffer(num_bytes);
        //av_image_fill_arrays(rgb_frame->data, rgb_frame->linesize, buffer.data(), AV_PIX_FMT_RGB24, codec_ctx->width, codec_ctx->height, 1);



// Speicher freigeben
        av_packet_free(&packet);
        av_frame_free(&frame);
        av_frame_free(&rgb_frame);
        avcodec_free_context(&codec_ctx);
        avformat_close_input(&fmt_ctx);
        sws_freeContext(sws_ctx);


  // _videoCapture = std::make_unique<cv::VideoCapture>(filePath);
  // if (!_videoCapture->isOpened())
  // {
  //   std::cout << "Error: Could not open video file." << std::endl;
  // }

  // _fps = _videoCapture->get(cv::CAP_PROP_FPS);
  // _videoSize = { _videoCapture->get(cv::CAP_PROP_FRAME_WIDTH),
  //   _videoCapture->get(cv::CAP_PROP_FRAME_HEIGHT) };
  // _frameCount = static_cast<int>(_videoCapture->get(cv::CAP_PROP_FRAME_COUNT));

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

  // if (!_videoCapture->set(cv::CAP_PROP_POS_FRAMES, frameNumber))
  // {
  //   return _pixelData;
  // }

  // cv::Mat frame;
  // *_videoCapture.get() >> frame;
  // if (frame.empty())
  // {
  //   return _pixelData;
  // }

  // for (int y = 0; y < frame.rows; ++y)
  // {
  //   for (int x = 0; x < frame.cols; ++x)
  //   {
  //     cv::Vec3b pixel = frame.at<cv::Vec3b>(y, x);
  //     _pixelData.at(y*_videoSize.x+x) = { static_cast<int>(pixel[2]),
  //       static_cast<int>(pixel[1]),
  //       static_cast<int>(pixel[0])};
  //   }
  // }
  return _pixelData;
}