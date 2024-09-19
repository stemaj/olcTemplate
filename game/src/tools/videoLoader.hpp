#ifndef __VIDEOLOADER_HPP
#define __VIDEOLOADER_HPP

#include <iostream>
#include <string>
extern "C" {
    #include <olcTemplate/sdk/ffmpeg-7.0.2/include/libavformat/avformat.h>
    #include <olcTemplate/sdk/ffmpeg-7.0.2/include/libavcodec/avcodec.h>
}

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/fetch.h>
#endif

namespace stemaj {

class VideoProcessor {
public:
    AVFormatContext* formatContext = nullptr;

    #include <libavcodec/avcodec.h>
#include <iostream>

void printSupportedCodecs() {
    const AVCodec* codec = nullptr;
    void* i = 0;
    
    std::cout << "Unterstützte Codecs:\n";
    while ((codec = av_codec_iterate(&i)) != nullptr) {
        std::cout << "Codec: " << codec->name << " (\n" ;
                  //<< (codec-> ->decode ? "Decoder" : "Encoder") << ")\n";
    }
}


    VideoProcessor() {
        //av_log_set_level(AV_LOG_DEBUG);  // Setze das Log-Level auf DEBUG

        printSupportedCodecs();

        //av_register_all();  // Registriere alle FFmpeg-Formate und Codecs
    }

    ~VideoProcessor() {
        if (formatContext) {
            avformat_close_input(&formatContext);  // Schließe Formatkontext, wenn geöffnet
        }
    }

    // Funktion zum Starten des Videoladevorgangs (je nach Umgebung)
    void openVideo(const std::string& pathOrUrl) {
        //filePath = pathOrUrl;  // Pfad im virtuellen Dateisystem
#ifdef __EMSCRIPTEN__
        // In der WebAssembly-Umgebung wird die Datei heruntergeladen
        downloadFile("assets/mp4/watch.mp4");
        //filePath = "http://localhost:6931/" + filePath;
        //filePath = "assets/mp4/watch.mp4";
#else
        // In einer nativen Umgebung wird direkt vom Dateisystem geladen
        processVideo();
#endif
    }

private:
#ifdef __EMSCRIPTEN__
    // Funktion zum Herunterladen der Datei ins virtuelle Dateisystem (nur für WASM)
    void downloadFile(const std::string& url) {
        emscripten_fetch_attr_t attr;
        emscripten_fetch_attr_init(&attr);
        strcpy(attr.requestMethod, "GET");
        attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;  // Lade die Datei in den Speicher
        attr.onsuccess = onSuccess;  // Statische Callback-Funktion bei Erfolg
        attr.onerror = onError;      // Statische Callback-Funktion bei Fehler
        attr.userData = this;        // Verweise auf das aktuelle Objekt

        emscripten_fetch(&attr, url.c_str());
    }

    // Callback-Funktion bei erfolgreichem Download
    static void onSuccess(emscripten_fetch_t* fetch) {
        // Zugriff auf das `VideoProcessor`-Objekt durch `userData`
        VideoProcessor* processor = static_cast<VideoProcessor*>(fetch->userData);
        processor->processDownload(fetch);
        emscripten_fetch_close(fetch);  // Beende den Fetch
    }

    // Callback-Funktion bei fehlerhaftem Download
    static void onError(emscripten_fetch_t* fetch) {
        std::cout << "Download fehlgeschlagen\n";
        emscripten_fetch_close(fetch);
    }

    // Verarbeite die heruntergeladene Datei im WASM-Dateisystem
    void processDownload(emscripten_fetch_t* fetch) {
        FILE* fp = fopen("/tmp/video.mp4", "wb");  // Virtueller Pfad im EM-Dateisystem
        if (!fp) {
            std::cout << "Fehler beim Öffnen der Datei:\n ";// << filePath << std::endl;
            return;
        }

        fwrite(fetch->data, 1, fetch->numBytes, fp);  // Schreibe die heruntergeladene Datei ins virtuelle Dateisystem
        fclose(fp);
        std::cout << "Video erfolgreich heruntergeladen und gespeichert.\n";

        // Starte den Verarbeitungsprozess nach dem Herunterladen
        processVideo();
    }
#endif

    // Funktion zum Verarbeiten des Videos (für beide Umgebungen)
    void processVideo() {
        // AVFormatContext erstellen und Datei öffnen
        formatContext = avformat_alloc_context();
        const char* filePath = "assets/mp4/watch.mp4";
#ifdef __EMSCRIPTEN__
        filePath = "/tmp/video.mp4";  // Virtueller Pfad
#endif

#ifdef __EMSCRIPTEN__
EM_ASM({
    FS.syncfs(function (err) {
        if (err) {
            console.log("Fehler beim Synchronisieren des Dateisystems");
        } else {
            console.log("Dateisystem synchronisiert");
        }
    });
});


        EM_ASM({
    var stats = FS.stat('/tmp/video.mp4');
    console.log("Dateigröße: " + stats.size + " Bytes");
});
#endif

        if (avformat_open_input(&formatContext, filePath, nullptr, nullptr) != 0) {
            std::cout << "Konnte Video nicht öffnen --> " << filePath << std::endl;
            return;
        }




        std::cout << "Video erfolgreich geöffnet\n";
        // Hier kannst du weitere Videoverarbeitungen hinzufügen
    }
};


} // namespace stemaj

#endif // __VIDEOLOADER_HPP
