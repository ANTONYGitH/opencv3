//ʵ��1 ���³�����Լ�ʵ���㷨��Ҳ���Ե���OpenCV�ĺ���
//1.��һ���Ҷ�ͼ��img1�������صĻҶ�ֵ + 50�����ͼ��img2��
//2.��img2����ֱ��ͼ���⻯�����ͼ��img3��
//3.��img3�������͡���ʴ�������img4��
//4.ͨ��C++���Զ������ֻ���ͼ��img4������ֵ�˲��Լ�����Sobel���ӽ���ͼ����
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;

int main()
{
	Mat XQAImage;//ԭͼ
	XQAImage = imread("�����ձ�.jpg");
	if (!XQAImage.data)
	{
		printf("\n����ʾ����ȡͼ�����,��������е�������ͼ���Ƿ�һ�¡�\n");
		std::cin.get();
		std::cin.get();
		return 0;
	}
    namedWindow("��ԭͼ��", 0);
    resizeWindow("��ԭͼ��", 400, 270);
	imshow("��ԭͼ��", XQAImage);

	//�ָ���--------------------------------------------//ʵ������ʼ//---------------------------------------------

	"\t��ʵ������1����һ���Ҷ�ͼ��img1�������صĻҶ�ֵ + 50�����ͼ��img2\n";

	int height = XQAImage.rows;//���ԭͼ�ĸ�
	int width = XQAImage.cols;//���ԭͼ�Ŀ�
	Mat XQAImage_2 = Mat::zeros(XQAImage.size(), XQAImage.type());  //����һ����ԭͼһ����С�Ŀհ�ͼƬ����ͬ      

	float brightValue = 50;//�������ȼ�50
	//ѭ������������ÿһ�У�ÿһ�е�Ԫ��
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (XQAImage.channels() == 3)//�ж��Ƿ�Ϊ3ͨ��ͼƬ
			{
				//�������õ���ԭͼ����ֵ�����ظ�����b,g,r
				float b = XQAImage.at<Vec3b>(row, col)[0];//blue
				float g = XQAImage.at<Vec3b>(row, col)[1];//green
				float r = XQAImage.at<Vec3b>(row, col)[2];//red
				//��ʼ�������أ��Ա���b,g,r���ı���ٷ��ص��µ�ͼƬ��
				XQAImage_2.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b + brightValue);
				XQAImage_2.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g + brightValue);
				XQAImage_2.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r + brightValue);
			}
			else if (XQAImage_2.channels() == 1)//�ж��Ƿ�Ϊ��ͨ����ͼƬ
			{
				float i = XQAImage_2.at<uchar>(row, col);
				XQAImage_2.at<uchar>(row, col) = saturate_cast<uchar>(i + brightValue);
			}
		}
	}
	namedWindow("��Ч��ͼ1���Ҷ�ֵ+50", 0);
	resizeWindow("��Ч��ͼ1���Ҷ�ֵ+50", 400, 270);
	imshow("��Ч��ͼ1���Ҷ�ֵ+50", XQAImage_2);

	"\t��ʵ������2����img2����ֱ��ͼ���⻯�����ͼ��img3\n";

	Mat XQAImage_3 = Mat::zeros(XQAImage.size(), XQAImage.type());
	
	std::vector<Mat> rc;
	split(XQAImage_2, rc);//��һ����ͨ���������ɼ�����ͨ������
	equalizeHist(rc[0], rc[0]);//0��1��2����ͨ��
	equalizeHist(rc[1], rc[1]);
	equalizeHist(rc[2], rc[2]);
	merge(rc, XQAImage_3);//��split()��������������������������Ϻϲ���һ����ͨ��������

	namedWindow("��Ч��ͼ2����ͼ��ֱ��ͼ���⻯", 0);
	resizeWindow("��Ч��ͼ2����ͼ��ֱ��ͼ���⻯", 400, 270);
	imshow("��Ч��ͼ2����ͼ��ֱ��ͼ���⻯", XQAImage_3);

	"\t��ʵ������3����img3�������͡���ʴ�������img4\n";

	Mat XQAImage_4 = Mat::zeros(XQAImage.size(), XQAImage.type());
	int CoreSize = 4;//�ں˾���ĳߴ�
	//���Ͳ���
	dilate(XQAImage_3, XQAImage_4, getStructuringElement
	(MORPH_RECT, Size(2 * CoreSize + 1, 2 * CoreSize + 1), Point(CoreSize, CoreSize)));
	//��ʴ����
	erode(XQAImage_4, XQAImage_4, getStructuringElement
	(MORPH_RECT, Size(2 * CoreSize + 1, 2 * CoreSize + 1), Point(CoreSize, CoreSize)));
	namedWindow("��Ч��ͼ3�����͡���ʴ��", 0);
	resizeWindow("��Ч��ͼ3�����͡���ʴ��", 400, 270);
	imshow("��Ч��ͼ3�����͡���ʴ��", XQAImage_4);

	"\t��ʵ������4��ͨ��C++���Զ������ֻ���ͼ��img4������ֵ�˲��Լ�����Sobel���ӽ���ͼ����\n";

	Mat XQAImage_5 = Mat::zeros(XQAImage.size(), XQAImage.type());//��ֵ�˲����ͼ
	Mat out_xImage, out_yImage;//Sobel��������Ķ�x��y����������ݶȴ����ͼƬ
	Mat abs_x, abs_y;//Sobel���ӵ��ڲ�
	Mat XQAImage_6 = Mat::zeros(XQAImage.size(), XQAImage.type());//Sobel��ȡ���ͼ

	//��ֵ�˲�
	int medianBlurValue = 10;
	//��ֵ�˲�
	medianBlur(XQAImage_4, XQAImage_5, medianBlurValue * 2 + 1);//ע��˴��������������������޸ģ��������medianBlurValue*2+1
	//��sobel������ȡͼ������
	Sobel(XQAImage_5, out_xImage, CV_64F, 1, 0, 1, 1, 1, BORDER_DEFAULT);//��x�����ݶ�,��6������Ϊsoble�ںˣ�����Ҫ
	convertScaleAbs(out_xImage, abs_x);
	Sobel(XQAImage_5, out_yImage, CV_64F, 0, 1, 1, 1, 1, BORDER_DEFAULT);//��y�����ݶ�
	convertScaleAbs(out_yImage, abs_y);
	addWeighted(abs_x, 0.5, abs_y, 0.5, 0, XQAImage_6);//�ϲ��ݶ�
	namedWindow("��Ч��ͼ4����ֵ�˲�&Sobel����ͼ����", 0);
	resizeWindow("��Ч��ͼ4����ֵ�˲�&Sobel����ͼ����", 400, 270);
	imshow("��Ч��ͼ4����ֵ�˲�&Sobel����ͼ����", XQAImage_6);

    waitKey(0);
    destroyAllWindows();
    return 0;
}
//������ϯ���|ѧ�ţ�B21023716|���ʱ�䣺2022��9��27��11:00:41