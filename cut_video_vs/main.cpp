#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace std; 
using namespace cv;

//将视频文件复制到当前工程下
int main()
{
	//变量定义
	Mat frame;//定义帧
	Mat outFrame;
	float startTime = 40;//处理开始时间
	float outputTime = 10;//处理时间长度

	//打开视频
	VideoCapture cap("1轮-浙大 [DIVX 720p].avi");	  
	if(!cap.isOpened()){cout<<"视频读取错误"<<endl;system("puase");return -1;}

	//设置视频
	double rate=cap.get(CV_CAP_PROP_FPS);//获取帧率
	int delay=1000/rate;//每帧之间的延迟与视频的帧率相对应
	VideoWriter outputVideo("1轮-浙大.avi", CV_FOURCC('M', 'J', 'P', 'G'), rate, Size(360, 240));//写视频类
	Rect place(500,250,360,240);//输出视频的区域


	//设置处理开始时间
	for (int i=0;i<startTime*rate;i++)
	{
		cap>>frame;
	}
	
	//开始视频处理
	bool stop = false;
	for (int i=0;!stop&&i<outputTime*rate;i++)
	{
		if(!cap.read(frame))//获取视频下一帧
		{
			cout<<"视频结束"<<endl;
			waitKey(0);
			break;
		}
		outFrame = frame(place);

		outputVideo<<outFrame;
		imshow("video",outFrame);

		if(waitKey(delay)>=0)//引入延迟，通过按键停止视频
			stop = true;
	}
	
	return 0;
}