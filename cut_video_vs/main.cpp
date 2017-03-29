#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace std; 
using namespace cv;

//����Ƶ�ļ����Ƶ���ǰ������
int main()
{
	//��������
	Mat frame;//����֡
	Mat outFrame;
	float startTime = 40;//����ʼʱ��
	float outputTime = 10;//����ʱ�䳤��

	//����Ƶ
	VideoCapture cap("1��-��� [DIVX 720p].avi");	  
	if(!cap.isOpened()){cout<<"��Ƶ��ȡ����"<<endl;system("puase");return -1;}

	//������Ƶ
	double rate=cap.get(CV_CAP_PROP_FPS);//��ȡ֡��
	int delay=1000/rate;//ÿ֮֡����ӳ�����Ƶ��֡�����Ӧ
	VideoWriter outputVideo("1��-���.avi", CV_FOURCC('M', 'J', 'P', 'G'), rate, Size(360, 240));//д��Ƶ��
	Rect place(500,250,360,240);//�����Ƶ������


	//���ô���ʼʱ��
	for (int i=0;i<startTime*rate;i++)
	{
		cap>>frame;
	}
	
	//��ʼ��Ƶ����
	bool stop = false;
	for (int i=0;!stop&&i<outputTime*rate;i++)
	{
		if(!cap.read(frame))//��ȡ��Ƶ��һ֡
		{
			cout<<"��Ƶ����"<<endl;
			waitKey(0);
			break;
		}
		outFrame = frame(place);

		outputVideo<<outFrame;
		imshow("video",outFrame);

		if(waitKey(delay)>=0)//�����ӳ٣�ͨ������ֹͣ��Ƶ
			stop = true;
	}
	
	return 0;
}