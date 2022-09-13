//作业2 配置好OpenCV，随便显示一幅图像。附上代码和显示结果截图
//#include <opencv2/core.hpp>
//#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

int main()
{
    Mat img = imread("B21023716席庆澳_作业2.jpg");
    namedWindow("B21023716席庆澳",0);
    resizeWindow("B21023716席庆澳",800,540);
    imshow("B21023716席庆澳", img);
    waitKey(1000);//1s,   waitKey(0);写0的话会窗口不会自己关闭，需要按任意键关闭
    destroyAllWindows();
    return 0;
}
//姓名：席庆澳|学号：B21023716|完成时间：2022年8月31日11:20:07