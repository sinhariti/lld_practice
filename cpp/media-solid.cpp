#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class Player {
public:
    virtual ~Player() = default;
    virtual void play(const string& source) = 0;
    virtual void pause() = 0;
};
class LivePlayer{
  public:
    virtual ~LivePlayer()=default;
    virtual void streamLive(const string& url) = 0;
};
class DownloadablePlayer{
  public:
    virtual ~DownloadablePlayer()=default;
    virtual void download(const string& sourceUrl) = 0;
};
class AudioPlayer : public Player, public DownloadablePlayer {
  private:
    bool playing{false};
public:
    void play(const string& source) override { (void)source; playing = true; }
    void pause() override { playing = false; }
    void download(const string& url) { (void)url; /* pretend */ }
    bool isPlaying() const { return playing; }
};

class CameraStreamPlayer : public LivePlayer, public Player {
    bool liveStarted{false};
    bool playing{false};
public:
    void play(const string& src) override {
        (void)src;
        playing = true;
    }
    void pause() override { playing = false; }
    void record(const string& dest) { (void)dest; /* pretend */ }
    void streamLive(const string& url) { (void)url; liveStarted = true; }
    bool isPlaying() const { return playing; }
    bool isLive() const { return liveStarted; }
};

int main() {
    AudioPlayer ap;
    ap.play("song.mp3");
    cout << "Audio playing: " << boolalpha << ap.isPlaying() << "\n";
    ap.pause();
    ap.download("song.mp3");

    CameraStreamPlayer cam;
    cam.play("rtsp://camera");      
    cam.streamLive("rtsp://camera"); 
    cam.play("rtsp://camera");

    return 0;
}