# videotools

## New Features
  - A progress bar has been added to the interface to update the conversion progress in real time.
  - Added pause feature
  - Add more handling of exceptions

## Introduce
This tool can complete the conversion between video and frame images according to the parameters of the command line.<br>
Completed on July 20, 2018, last modified on October 6, 2018.

## Environment
  - Windows 10<br>
  - Visual Studio 2017<br>
  - OpenCV 3.4.1<br>
  - gflags 2.2.1

## Function
  - Video to frame picture
  - Camera video streaming to frame by frame picture
  - Use image compose video
  
## Command line argument
  | argument | Explanation |
  | ------ | ------ |
  | -video | Specify the name of the converted video |
  | -device | Specify the video to be converted |
  | -folder | Specify where to store the frame-by-frame images |
  | -image | Specify frame-by-frame images to be converted | 
  
## Command line format
Make sure you have entered the videotools main program running directory<br>
1. Video to frame picture
``` sh
$ videotools -device <Your video path> -folder <Your picture folder path>
``` 
2. Camera video streaming to frame by frame picture
``` sh
$ videotools -device <Your camera device number> -folder <Your picture folder path>
```
0 indicates the device number of the system default camera.<br>
3. Use image compose video
``` sh
$ videotools -image <Your image folder path> -video <Video name>
```

## Instructions for use
1. installation by Setup.exe<br>
  - Run Setup.exe in the \Output folder
  - Open the command line and go to the program installation directory.
  - Enter the command to run the program on the command line.
2. Compile source code<br>
  - Open videotools.sln in Visual Studio
  - Configuring OpenCV and gflags
  - Configuring command line parameters
  - Running in Release x64 environment

## Result
![Image](https://github.com/Liut2016/videotools/blob/master/result.png)


# videotools

## 新特性
  - 界面上增加了进度条，实时更新转换进度
  - 增加了暂停功能
  - 增加更多对异常情况的处理

## 简介
视频格式转换工具，可以根据命令行的参数完成视频与帧图片之间的转换。<br>
完成于2018年7月20日，最后修改于2018年10月6日。

## 开发环境
  - Windows 10<br>
  - Visual Studio 2017<br>
  - OpenCV 3.4.1<br>
  - gflags 2.2.1

## 功能
  - 视频转逐帧图片
  - 摄像头视频流转逐帧图片
  - 使用图片合成视频
  
## 命令行参数
  | 参数 | 解释 |
  | ------ | ------ |
  | -video | 指定转换得到的视频名称 |
  | -device | 指定待转换的视频 |
  | -folder | 指定转换得到的逐帧图片的存放位置 |
  | -image | 指定待转换的逐帧图片 | 
  
## 命令行格式
确保你已经进入到videotools主程序运行目录下<br>
1. 视频转换为逐帧图片
``` sh
$ videotools -device <Your video path> -folder <Your picture folder path>
``` 
2. 视频流转换为逐帧图片 
``` sh
$ videotools -device <Your camera device number> -folder <Your picture folder path>
```
0表示系统默认摄像头的设备号<br>
3. 图片合成视频
``` sh
$ videotools -image <Your image folder path> -video <Video name>
```

## 使用说明
1. 直接安装<br>
  - \Output文件夹中运行Setup.exe
  - 打开命令行，进入到程序安装目录下
  - 在命令行中输入命令行指令运行程序
2. 编译源码<br>
  - 在Visual Studio中打开videotools.sln
  - 配置OpenCV和gflags
  - 配置命令行参数
  - 在Release x64环境下运行

## 结果示例
![Image](https://github.com/Liut2016/videotools/blob/master/result.png)
