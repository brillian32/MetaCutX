# 项目简介
对标市面一线剪辑产品付费功能, 实现内嵌式/无感交互的剪辑助手效果，对标剪映(capcut) 、 万兴喵影(filmora)付费功能

# 项目结构
- 3rd 三方库
- App 应用层代码
  * MXTimeline 时间线模块
- Core 底层核心
    * MXVideoDecoder 视频解码模块
    * MXUtils 工具类模块

# 已完成模块
## UI
### 时间线
![img.png](ShowCase%2Fimg.png)
# 底层
## 视频解码
![img_1.png](ShowCase%2Fimg_1.png)
## 视频超清ai

# 依赖库安装
opencv
ffmpeg
qt6.4
doctest
spdlog
glew
# 工程编译
- mkdir build
- cd build
- cmake -DCMAKE_BUILD_TYPE=Debug ..

# 依赖技术
1. FFmpeg：强大的音视频处理工具，用于视频解码、特效处理和编码。
2. OpenCV：一个开源计算机视觉库，可以用于图像和视频处理，包括特效处理和分析。
3. OpenGL：图形渲染API，用于实现实时视频特效、图形渲染和动画效果。
4. CUDA：用于利用NVIDIA GPU进行加速计算的并行计算平台，可以提高视频特效处理的性能。
5. Qt：一个跨平台的C++ GUI开发框架，用于创建用户界面和交互。
6. Boost：一个C++库集合，提供了许多有用的功能和工具，可以用于处理文件操作、日期时间处理等辅助功能。
7. Libavcodec：FFmpeg中的编解码器库，用于处理视频和音频编解码。
8. Libavformat：FFmpeg中的格式管理库，用于处理不同格式的视频和音频。
9. Libavfilter：FFmpeg中的滤镜库，用于应用各种特效和转换。
10. Shader编程语言：用于编写GPU上的渲染效果和特效。
