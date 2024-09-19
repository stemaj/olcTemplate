#include "libavcodec/packet.h"
#include <memory>
#include <olcTemplate/game/videoFrame.hpp>
#include <iostream>
#include <ostream>
#include <string>
#include <olcTemplate/game/src/tools/videoLoader.hpp>

extern "C" {
    #include <olcTemplate/sdk/ffmpeg-7.0.2/include/libavformat/avformat.h>
    #include <olcTemplate/sdk/ffmpeg-7.0.2/include/libavcodec/avcodec.h>
    #include <olcTemplate/sdk/ffmpeg-7.0.2/include/libswscale/swscale.h>
    #include <olcTemplate/sdk/ffmpeg-7.0.2/include/libavutil/imgutils.h>
}

using namespace stemaj;

class VideoFrame::FFmpegImpl
{
public:
  virtual ~FFmpegImpl()
  {
    avcodec_free_context(&codecContext);
    //avformat_close_input(&formatContext);
    sws_freeContext(swsContext);
  }
  //AVFormatContext* formatContext = nullptr;
  AVCodecContext* codecContext = nullptr;
  SwsContext* swsContext = nullptr;
  int videoStreamIndex = -1;
};

VideoFrame::VideoFrame(const std::string& filePath) : ffmpeg(new FFmpegImpl())
{
  // Video öffnen
  // AVFormatContext erstellen und Datei öffnen
  // ffmpeg->formatContext = avformat_alloc_context();
  // if (avformat_open_input(&ffmpeg->formatContext, filePath.c_str(), nullptr, nullptr) != 0)
  // {
  //   std::cout << "Konnte Video nicht öffnen\n";
  //   return;
  // }

  l = std::make_unique<VideoProcessor>();
  l->openVideo(filePath);  // URL des Videos
  //emscripten_exit_with_live_runtime();  // Halte das Programm am Leben, bis alle Downloads abgeschlossen sind

  // Streams suchen
  if (avformat_find_stream_info(l->formatContext, nullptr) < 0)
  {
    std::cout << "Konnte Stream-Infos nicht finden\n";
    return;
  }

  // Finde den Video-Stream
  for (unsigned int i = 0; i < l->formatContext->nb_streams; i++)
  {
    if (l->formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
    {
      ffmpeg->videoStreamIndex = i;
      break;
    }
  }

  if (ffmpeg->videoStreamIndex == -1)
  {
    std::cout << "Kein Videostream gefunden\n";
    return;
  }

  // Codec Kontext erstellen
  AVCodecParameters* codecParams =
    l->formatContext->streams[ffmpeg->videoStreamIndex]->codecpar;

  auto codec = avcodec_find_decoder(codecParams->codec_id);
  if (!codec)
  {
    std::cout << "Codec nicht gefunden\n";
    return;
  }

  ffmpeg->codecContext = avcodec_alloc_context3(codec);
  if (avcodec_parameters_to_context(ffmpeg->codecContext, codecParams) < 0)
  {
    std::cout << "Konnte Codec-Kontext nicht initialisieren\n";
    return;
  }

  if (avcodec_open2(ffmpeg->codecContext, codec, nullptr) < 0)
  {
    std::cout << "Konnte Codec nicht öffnen\n";
    return;
  }

  std::cout << "Width: " << ffmpeg->codecContext->width << " Height: " << ffmpeg->codecContext->height << std::endl;

  // Frame-Größe holen
  _videoSize = { ffmpeg->codecContext->width, ffmpeg->codecContext->height };

  // Kontext für die Format-Konvertierung (YUV zu RGB)
  ffmpeg->swsContext = sws_getContext(
    _videoSize.x, _videoSize.y, ffmpeg->codecContext->pix_fmt,/*Quelle*/
    _videoSize.x, _videoSize.y,AV_PIX_FMT_RGB24,/*Ziel*/
    SWS_BILINEAR, nullptr, nullptr, nullptr);

  _pixelData.reserve(_videoSize.x*_videoSize.y);
  _pixelData.resize(_videoSize.x*_videoSize.y);
}

VideoFrame::~VideoFrame()
{
  delete ffmpeg;
}

std::vector<VideoFrame::RGB> VideoFrame::Frame(float timestamp)
{
  

  _currentTimestamp += timestamp;
  int64_t stamp = static_cast<int64_t>(_currentTimestamp * 90000.0f);

  //std::cout << _currentTimestamp << std::endl;

  // timestampInSeconds ist dein Float-Wert in Sekunden
  //int64_t timestampInSeconds = static_cast<int64_t>((double)_currentTimestamp * AV_TIME_BASE);

  // Hole die Time Base des Video Streams
  //AVRational timeBase = ffmpeg->formatContext->streams[ffmpeg->videoStreamIndex]->time_base;
  //std::cout << "Time base: " << timeBase.num << "/" << timeBase.den << std::endl;

  // Berechne den Timestamp in der Time Base des Streams
  //int64_t stamp = static_cast<int64_t>((double)_currentTimestamp / av_q2d(timeBase) / 1000.0);

  //std::cout << stamp << std::endl;

  if (av_seek_frame(l->formatContext, ffmpeg->videoStreamIndex,
    stamp, AVSEEK_FLAG_BACKWARD) < 0) 
    {
      std::cerr << "Error seeking to timestamp" << std::endl;
      return {};
    }

// Decoder-Buffer leeren nach dem Seek
avcodec_flush_buffers(ffmpeg->codecContext);

  AVFrame* frame = av_frame_alloc();
  AVFrame* rgbFrame = av_frame_alloc();

  // Speicher für RGB Bild vorbereiten
  int numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24,
    _videoSize.x, _videoSize.y, 1);
  std::vector<uint8_t> rgbBuffer(numBytes);

  // Zeiger des rgbFrame auf den RGB-Puffer einstellen
  av_image_fill_arrays(rgbFrame->data, rgbFrame->linesize,
    rgbBuffer.data(), AV_PIX_FMT_RGB24, _videoSize.x, _videoSize.y, 1);

  // Setze die Höhe und Breite für das rgbFrame
  rgbFrame->width = _videoSize.x;
  rgbFrame->height = _videoSize.y;
  rgbFrame->format = AV_PIX_FMT_RGB24;

  bool frameDecoded = false;
  AVPacket packet;
  //av_init_packet(&packet);

  // Schleife durch die Pakete bis ein Frame dekodiert wurde
  while (av_read_frame(l->formatContext, &packet) >= 0)
  {
    if (packet.stream_index == ffmpeg->videoStreamIndex)
    {
      int ret = avcodec_send_packet(ffmpeg->codecContext, &packet);
      if (ret < 0)
      {
        std::cout << "Error: Could not send packet for decoding\n";
        break;
      }

      // Versuche, Frames zu empfangen
        while (ret >= 0) {
            ret = avcodec_receive_frame(ffmpeg->codecContext, frame);

            if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                // Warte auf mehr Pakete oder EOF
                break;
            } else if (ret < 0) {
                std::cerr << "Error during decoding: " << ret << std::endl;
                break;
            }

// Konvertiere das YUV-Frame in RGB
            sws_scale(ffmpeg->swsContext, frame->data, frame->linesize, 0,  _videoSize.y, rgbFrame->data, rgbFrame->linesize);

            // Debug-Ausgabe: Überprüfe die ersten paar Pixel im RGB-Frame
            // std::cout << "First pixel RGB values: "
            //           << (int)rgbFrame->data[0][0] << ", "
            //           << (int)rgbFrame->data[0][1] << ", "
            //           << (int)rgbFrame->data[0][2] << std::endl;

            frameDecoded = true;

            // Hier könntest du überprüfen, ob der Zeitstempel korrekt ist:
            if (frame->pts * av_q2d(l->formatContext->streams[ffmpeg->videoStreamIndex]->time_base) >= stamp) {
                std::cout << "Dies ist der richtige Frame\n";
                break;
            }

            break;  // Dekodiere nur ein Frame



        }

    }
    //av_packet_free(AVPacket **pkt)
    //av_packet_unref(&packet);

    if (frameDecoded) {
        break;
    }
  }

  //std::cout << frame->height << std::endl;
  //std::cout << frameDecoded << std::endl;
  //std::cout << rgbFrame->data[0] << std::endl;
  //std::cout << "Input frame format: " << av_get_pix_fmt_name(static_cast<AVPixelFormat>(frame->format)) << std::endl;


  //std::vector<std::array<uint8_t, 3>> rgbData;
    if (frameDecoded) {
       for (int y = 0; y < rgbFrame->height; y++) {
        // Hole den Zeilenstart basierend auf linesize[0]
        uint8_t* row = rgbFrame->data[0] + y * rgbFrame->linesize[0];

        for (int x = 0; x < rgbFrame->width; x++) {
            // Extrahiere RGB-Werte aus der Zeile
            uint8_t r = row[x * 3];      // R-Wert
            uint8_t g = row[x * 3 + 1];  // G-Wert
            uint8_t b = row[x * 3 + 2];  // B-Wert

            // Speichere den RGB-Wert im _pixelData-Vektor
            _pixelData[y * rgbFrame->width + x] = {r, g, b};
        }
    }
    }

  //sws_freeContext(ffmpeg->swsContext);
  av_frame_free(&frame);
  av_frame_free(&rgbFrame);
 // av_packet_unref(&packet);

  // std::cout << "hier " << _pixelData.size() << std::endl;
    // std::cout << "rgb " << int(_pixelData[30000].r) 
    // << int(_pixelData[30000].g) 
    // << int(_pixelData[30000].b) <<  std::endl;

  // std::cout << "got data\n";
  return _pixelData;
}
