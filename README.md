# BadAppleCheatEngine

Plays **Bad Apple!!** inside of **Cheat Engine** memory viewer

# video.bin

The `video.bin` file was generated using the following ffmpeg command
```bash
ffmpeg -i input.mp4 -pix_fmt monob -map 0:v -vf scale=72:76 -f rawvideo -y video.bin
```
and is embedded as a resource inside of the executable at compile time.

# Video resolution

Current video resolution is set to 72x76 which is perfect for maximized memory viewer at a monitor resolution of 1440p and 100% scaling in windows

If you want to run this on a different resolution you will need to regenerate the `video.bin` file and update the defines at the top of [BadAppleCheatEngine.cpp](./BadAppleCheatEngine.cpp)

# Demo

Demo on [YouTube](https://youtu.be/B1NtVP7PIIk)
