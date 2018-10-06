#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <shlwapi.h>
#include <io.h>
#include <direct.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <Windows.h>
#include <gflags/gflags.h>
#include <string>
using namespace std;
using namespace cv;

//#define MAX_PATH       256
DEFINE_string(var, "", "input var");
DEFINE_string(device, "0", "video from camera");
DEFINE_string(folder, "./image", "address that save image");
DEFINE_string(image, "./image", "address that video image from");
DEFINE_string(video, "test.avi", "video name");

/*
int videoToImage2(bool mode, string device, string address)
{
	VideoCapture capture;
//	Mat frame;
	int num = 0;

	if (!mode) capture.open(device);
	else capture.open(atoi(device.c_str()));

	if (!capture.isOpened())
	{
		cout << "Video not open." << endl;
		return 1;
	}

	double rate = capture.get(CV_CAP_PROP_FPS);
	int delay = 1000 / rate;
	cout << "帧率为 ： " << rate << endl;

	while (true)
	{
		Mat frame;
		capture >> frame;

		char a[7];
		sprintf_s(a, 10, "%06d", num);
		//	sprintf(a, "%06d", num);
		//	string s = string(address) + "/" + string(a) + ".jpg";
		//	string s = "D:\\work\\videotools\\image\\" + string(a) + ".jpg";
		char path[MAX_PATH + 1] = { 0 };
		GetCurrentDirectoryA(MAX_PATH, path);
		//	cout << path << endl;
		//	string s = "../image/" + string(a) + ".jpg";
		string s = string(path) + "/image/" + string(a) + ".jpg";
		cout << s << endl;

		if (!frame.empty())
			bool ret = imwrite(s, frame);
		else break;

		if (waitKey(0) == 27) break;
	}
	return 0;
}
*/


//定位光标位置
void gotoxy(long x, long y) {
	COORD pos = { x,y };
//	cout << x << '\t' << y << endl;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
	SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}

int show(int num,int frameNum, string s)
{
	system("cls");
	int i;
	double ratio = (num*1.0) / (frameNum*1.0);
//	cout << "num : " << num << '\t' << "frameNum : " << frameNum << endl;
//	cout << (int)(ratio *10)<< endl;
	
	gotoxy(0, 0);
	cout << "当前处理 ： " << s << endl;
	gotoxy(0, 2);
	for (i = 0; i < 10; i++) cout << '-';
	gotoxy(0, 4);
	for (i = 0; i < 10; i++) cout << '-';
	gotoxy(0, 3);
	for (int i = 0; i<int(ratio * 10); i++) cout << "#";
	gotoxy(12, 3);
//	for (i = 0; i < 10; i++) cout << ' ';
	printf("%.2f", ratio * 100);
	cout << "% ( " << num << " / " << frameNum << " )";
//	cout << ratio * 100 << "% ( " << num << " / " << frameNum << " )" ;
	gotoxy(0, 6);
	return 0;
}

//视频转图片
int videoToImage(bool mode,string device,string address)
{
	
	VideoCapture capture;
	Mat frame;
	int num = 0;//每一帧计数，用于统计和命名
	int delay;//帧之间的延迟，用于延迟函数
	bool pause = false;//暂停状态下为true，运行状态下为false

	//打开视频或者摄像头
	if (!mode)
	{
		if (_access(device.c_str(), 0) == -1)
		{
			cout << "视频文件不存在" << endl;
			return -1;
		}
		capture.open(device);
	}
	else capture.open(atoi(device.c_str()));
	//判断视频是否打开
	if (!capture.isOpened())
	{
		cout << "Video not open." << endl;
		return -1;
	}

	//判断保存路径是否存在，如果不存在，则创建
	if (_access(address.c_str(), 0) == -1)
	{
		int i = _mkdir(address.c_str());
		if (i == -1)
		{
			cout << address << "路径创建失败" << endl;
			return -1;
		}
		else if (i == 0) cout << address << "路径创建成功" << endl;
	}


	//设置延时
	if (!mode)
	{
		double rate = capture.get(CV_CAP_PROP_FPS);
		delay = 1000 / rate;
		cout << "帧率为 ： " << rate << endl;
	}
	else delay = 23.976;

	int frameNum = capture.get(CV_CAP_PROP_FRAME_COUNT);

	/*
	//pt为获取当前位置
	POINT pt;
	GetCursorPos(&pt);
//	printf("%ld %ld\n", pt.x, pt.y);

	long x = pt.x;
	long y = pt.y;
	*/

	bool stop(false);
	while (!stop)
	{
		if (!capture.read(frame))
		{
			cout << "No video frame" << endl;
			break;
		}
		/*
		if (mode)
		{
			t = ((double)getTickCount() - t) / getTickFrequency();
			double fps = 1.0 / t;
			cout << "帧率为 ： " << t << endl;
			delay = t;
		}
		*/
		cv::imshow("video", frame);
		num++;

		//设置存储路径和名称
		char a[10];
		sprintf_s(a, 10, "%06d", num);
	//	sprintf(a, "%06d", num);
	//	string s = string(address) + "/" + string(a) + ".jpg";
	//	string s = "D:\\work\\videotools\\image\\" + string(a) + ".jpg";
		char path[MAX_PATH + 1] = { 0 };
		GetCurrentDirectoryA(MAX_PATH, path);
		
	//	string s = string(path) + "/image/" + string(a) + ".jpg";
		string s = address + "\\" + string(a) + ".jpg";
		
		//按照格式输出进度条
		if(!mode) show(num, frameNum, s);
		else show(-1, -1, s);
		
		
		
		//保存图片
		bool ret=imwrite(s, frame);

		int status = waitKey(delay);
		
		//按ESC时退出
		if (status == 27)
		{
//			cout << "ESC" << endl;
			stop = true;
			cv::destroyAllWindows();
			capture.release();
			cout << "转换意外终止" << endl;
		}
		//按空格时暂停
		if (status == 32)
		{
//			cout << "SPACE" << endl;
			status = waitKey(0);
			if (status == 32)
			{
//				cout << "SPACE" << endl;
				continue;
				
			}
			if (status == 27)
			{
//				cout << "ESC" << endl;
				stop = true;
				cv::destroyAllWindows();
				capture.release();
				cout << "转换意外终止" << endl;
			}
		}
	}
	if (num >= frameNum) cout << "转换完成" << endl;
	cv::destroyAllWindows();
	capture.release();
	return 0;
}

int findFile(string address, vector<string> &fileset)
{
	WIN32_FIND_DATAA stFD;							//存放文件信息的结构体
	HANDLE h;
	string temp;

	//判断路径是否存在
	if (_access(address.c_str(), 0) == -1)
	{
		cout << "路径不存在" << endl;
		return -1;
	}

	temp = address + "\\*.jpg";
	h = FindFirstFileA(temp.c_str(), &stFD);			//构建目录句柄

	do
	{
		temp = address + "\\" + stFD.cFileName;

		if (temp == address + "\\..")										//上一级路径
		{
			continue;
		}
		else if (PathIsDirectoryA(temp.c_str()))		//包含子目录
		{
			findFile(temp, fileset);									//递归调用
		}
		else
		{

			//	cout<<stFD.cFileName<<endl;				//打印文件名
			//	fileset.push_back(stFD.cFileName);

			string s = address + "\\" + stFD.cFileName;
	//		cout << s << endl;
			fileset.push_back(s);
		}
	} while (FindNextFileA(h, &stFD));

	/*
	while (FindNextFileA(h, &stFD))						//提取目录句柄对应目录所包含的文件
	{
		temp = address + "\\" + stFD.cFileName;

		if (temp == address + "\\..")										//上一级路径
		{
			continue;
		}
		else if (PathIsDirectoryA(temp.c_str()))		//包含子目录
		{
			findFile(temp, fileset);									//递归调用
		}
		else
		{
			
		//	cout<<stFD.cFileName<<endl;				//打印文件名
		//	fileset.push_back(stFD.cFileName);

			string s = address + "\\" + stFD.cFileName;
			cout << s << endl;
			fileset.push_back(s);
		}
	}
	*/
	return 0;

}

//图片转视频
int imageToVideo(string address, string name,int delay)
{
	VideoWriter writer;
	vector<string> fileset;
	Size frameSize;
	int num = 0;

	if (findFile(address, fileset) == -1) return -1;
	
	
	vector<string>::iterator it = fileset.begin();
	int imageNum = fileset.size();

	while (it != fileset.end())
	{
		Mat frame;
//		cout << *it << endl;
		frame = imread(*it);
		if (!writer.isOpened())
		{
			frameSize.width = frame.cols;
			frameSize.height = frame.rows;
			if (!writer.open(name, CV_FOURCC('D', 'I', 'V', 'X'), delay, frameSize, true))
			{
				cout << "open writer error..." << endl;
				return -1;
			}
		}
		//将图片写入
		writer.write(frame);

		cv::imshow("video", frame);
		num++;
		show(num, imageNum, *it);
		it++;
		

		int status = waitKey(delay);
		//按ESC时退出
		if (status == 27)
		{
//			cout << "ESC" << endl;
			cv::destroyAllWindows();
			writer.release();
			cout << "转换意外中止" << endl;
			break;
		}
		//按空格时暂停
		if (status == 32)
		{
//			cout << "SPACE" << endl;
			status = waitKey(0);
			if (status == 32)
			{
//				cout << "SPACE" << endl;
				continue;

			}
			if (status == 27)
			{
//				cout << "ESC" << endl;
				cv::destroyAllWindows();
				writer.release();
				cout << "转换意外终止" << endl;
				break;
			}
		}
	}
	if (num >= imageNum) cout << "转换完成" << endl;
	cv::destroyAllWindows();
	writer.release();
	return 0;
}


int main(int argc,char** argv)
{
//	Mat image = imread(argv[1]);  //存放自己图像的路径 
//	imshow("显示图像", image);
	
	
	bool mode = false;            //判断视频来源，false表示视频来源于已有视频文件，true表示视频来自于摄像头
	bool isImageToVideo = true;   //
	int function = 0;
	
	if (!strcmp(argv[1], "-device") || !strcmp(argv[1], "--device")) isImageToVideo = true;
	else if (!strcmp(argv[1], "-image") || !strcmp(argv[1], "--image")) isImageToVideo = false;
	else
	{
		cout << "参数格式有误" << endl;
		return -1;
	}


	//解析参数变量
	google::ParseCommandLineFlags(&argc, &argv, true);
//	cout << "device : " << FLAGS_device << endl;
//	cout << "folder : " << FLAGS_folder << endl;
//	cout << "image : " << FLAGS_image << endl;
//	cout << "video : " << FLAGS_video << endl;
//	cout << argv[1] << endl;



	if (isImageToVideo)
	{
		if (FLAGS_device[0] <= '9'&&FLAGS_device[0] >= '0'&&FLAGS_device.length()<=4)
		{
			cout << "video to image : camera mode" << endl;
			mode = true;
		}
		else
			cout << "video to image : video mode" << endl;
		videoToImage(mode, FLAGS_device, FLAGS_folder);
	}
	else
	{
		double frameRate = 23.976;
		int delay = 1000 / frameRate;

		imageToVideo(FLAGS_image, FLAGS_video, delay);
	}
	

//	if (!strcmp(argv[1], "-device")) cout << "device mode" << endl;
//	videoToPicture(argv[2], argv[2]);
	system("pause");
	return 0;
}
