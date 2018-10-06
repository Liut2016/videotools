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
	cout << "֡��Ϊ �� " << rate << endl;

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


//��λ���λ��
void gotoxy(long x, long y) {
	COORD pos = { x,y };
//	cout << x << '\t' << y << endl;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
	SetConsoleCursorPosition(hOut, pos);//���������ֱ���ָ���ĸ����壬����λ��
}

int show(int num,int frameNum, string s)
{
	system("cls");
	int i;
	double ratio = (num*1.0) / (frameNum*1.0);
//	cout << "num : " << num << '\t' << "frameNum : " << frameNum << endl;
//	cout << (int)(ratio *10)<< endl;
	
	gotoxy(0, 0);
	cout << "��ǰ���� �� " << s << endl;
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

//��ƵתͼƬ
int videoToImage(bool mode,string device,string address)
{
	
	VideoCapture capture;
	Mat frame;
	int num = 0;//ÿһ֡����������ͳ�ƺ�����
	int delay;//֮֡����ӳ٣������ӳٺ���
	bool pause = false;//��ͣ״̬��Ϊtrue������״̬��Ϊfalse

	//����Ƶ��������ͷ
	if (!mode)
	{
		if (_access(device.c_str(), 0) == -1)
		{
			cout << "��Ƶ�ļ�������" << endl;
			return -1;
		}
		capture.open(device);
	}
	else capture.open(atoi(device.c_str()));
	//�ж���Ƶ�Ƿ��
	if (!capture.isOpened())
	{
		cout << "Video not open." << endl;
		return -1;
	}

	//�жϱ���·���Ƿ���ڣ���������ڣ��򴴽�
	if (_access(address.c_str(), 0) == -1)
	{
		int i = _mkdir(address.c_str());
		if (i == -1)
		{
			cout << address << "·������ʧ��" << endl;
			return -1;
		}
		else if (i == 0) cout << address << "·�������ɹ�" << endl;
	}


	//������ʱ
	if (!mode)
	{
		double rate = capture.get(CV_CAP_PROP_FPS);
		delay = 1000 / rate;
		cout << "֡��Ϊ �� " << rate << endl;
	}
	else delay = 23.976;

	int frameNum = capture.get(CV_CAP_PROP_FRAME_COUNT);

	/*
	//ptΪ��ȡ��ǰλ��
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
			cout << "֡��Ϊ �� " << t << endl;
			delay = t;
		}
		*/
		cv::imshow("video", frame);
		num++;

		//���ô洢·��������
		char a[10];
		sprintf_s(a, 10, "%06d", num);
	//	sprintf(a, "%06d", num);
	//	string s = string(address) + "/" + string(a) + ".jpg";
	//	string s = "D:\\work\\videotools\\image\\" + string(a) + ".jpg";
		char path[MAX_PATH + 1] = { 0 };
		GetCurrentDirectoryA(MAX_PATH, path);
		
	//	string s = string(path) + "/image/" + string(a) + ".jpg";
		string s = address + "\\" + string(a) + ".jpg";
		
		//���ո�ʽ���������
		if(!mode) show(num, frameNum, s);
		else show(-1, -1, s);
		
		
		
		//����ͼƬ
		bool ret=imwrite(s, frame);

		int status = waitKey(delay);
		
		//��ESCʱ�˳�
		if (status == 27)
		{
//			cout << "ESC" << endl;
			stop = true;
			cv::destroyAllWindows();
			capture.release();
			cout << "ת��������ֹ" << endl;
		}
		//���ո�ʱ��ͣ
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
				cout << "ת��������ֹ" << endl;
			}
		}
	}
	if (num >= frameNum) cout << "ת�����" << endl;
	cv::destroyAllWindows();
	capture.release();
	return 0;
}

int findFile(string address, vector<string> &fileset)
{
	WIN32_FIND_DATAA stFD;							//����ļ���Ϣ�Ľṹ��
	HANDLE h;
	string temp;

	//�ж�·���Ƿ����
	if (_access(address.c_str(), 0) == -1)
	{
		cout << "·��������" << endl;
		return -1;
	}

	temp = address + "\\*.jpg";
	h = FindFirstFileA(temp.c_str(), &stFD);			//����Ŀ¼���

	do
	{
		temp = address + "\\" + stFD.cFileName;

		if (temp == address + "\\..")										//��һ��·��
		{
			continue;
		}
		else if (PathIsDirectoryA(temp.c_str()))		//������Ŀ¼
		{
			findFile(temp, fileset);									//�ݹ����
		}
		else
		{

			//	cout<<stFD.cFileName<<endl;				//��ӡ�ļ���
			//	fileset.push_back(stFD.cFileName);

			string s = address + "\\" + stFD.cFileName;
	//		cout << s << endl;
			fileset.push_back(s);
		}
	} while (FindNextFileA(h, &stFD));

	/*
	while (FindNextFileA(h, &stFD))						//��ȡĿ¼�����ӦĿ¼���������ļ�
	{
		temp = address + "\\" + stFD.cFileName;

		if (temp == address + "\\..")										//��һ��·��
		{
			continue;
		}
		else if (PathIsDirectoryA(temp.c_str()))		//������Ŀ¼
		{
			findFile(temp, fileset);									//�ݹ����
		}
		else
		{
			
		//	cout<<stFD.cFileName<<endl;				//��ӡ�ļ���
		//	fileset.push_back(stFD.cFileName);

			string s = address + "\\" + stFD.cFileName;
			cout << s << endl;
			fileset.push_back(s);
		}
	}
	*/
	return 0;

}

//ͼƬת��Ƶ
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
		//��ͼƬд��
		writer.write(frame);

		cv::imshow("video", frame);
		num++;
		show(num, imageNum, *it);
		it++;
		

		int status = waitKey(delay);
		//��ESCʱ�˳�
		if (status == 27)
		{
//			cout << "ESC" << endl;
			cv::destroyAllWindows();
			writer.release();
			cout << "ת��������ֹ" << endl;
			break;
		}
		//���ո�ʱ��ͣ
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
				cout << "ת��������ֹ" << endl;
				break;
			}
		}
	}
	if (num >= imageNum) cout << "ת�����" << endl;
	cv::destroyAllWindows();
	writer.release();
	return 0;
}


int main(int argc,char** argv)
{
//	Mat image = imread(argv[1]);  //����Լ�ͼ���·�� 
//	imshow("��ʾͼ��", image);
	
	
	bool mode = false;            //�ж���Ƶ��Դ��false��ʾ��Ƶ��Դ��������Ƶ�ļ���true��ʾ��Ƶ����������ͷ
	bool isImageToVideo = true;   //
	int function = 0;
	
	if (!strcmp(argv[1], "-device") || !strcmp(argv[1], "--device")) isImageToVideo = true;
	else if (!strcmp(argv[1], "-image") || !strcmp(argv[1], "--image")) isImageToVideo = false;
	else
	{
		cout << "������ʽ����" << endl;
		return -1;
	}


	//������������
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
