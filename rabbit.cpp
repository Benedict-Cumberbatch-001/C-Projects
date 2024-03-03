#include <pcl/visualization/cloud_viewer.h>
#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkInteractionStyle);//初始化了 VTK 中的交互样式模块
VTK_MODULE_INIT(vtkRenderingFreeType);//初始化了 VTK 中的 FreeType 渲染模块
VTK_MODULE_INIT(vtkRenderingOpenGL2);//初始化了 VTK 中的 OpenGL2 渲染模块
using namespace std;
using namespace pcl;
int user_data;

void viewerOneOff(pcl::visualization::PCLVisualizer& viewer)//viewer是创建的可视化器
{
    viewer.setBackgroundColor(1.0, 0.5, 1.0);//设置背景颜色
    PointXYZ o;//创建一个PointXYZ类型的点，并给该点初始化
    o.x = 0;
    o.y = 0;
    o.z = 1.0;
    //viewer.addSphere(o, 0.25, "sphere", 0);//球心，半径，id，球体的可视化属性0可能是默认值
    cout << "i only run once" << endl;

}

void viewerPsycho(pcl::visualization::PCLVisualizer& viewer)
{
    static unsigned count = 0;//静态数据变量，全局变量
    stringstream ss;//提供了一个方便的接口，用于在字符串和其他数据类型之间进行转换，特别是在需要在字符串中构建或解析复杂数据时非常有用。
    ss << "Once per viewer loop: " << count++;
    viewer.removeShape("text", 0);//用于清除之前的内容
    viewer.addText(ss.str(), 100, 100, "text", 0);//生成新的显示文本，200 和 300: 这是文本在窗口中的位置，分别表示 x 和 y 坐标。

    //FIXME: possible race condition here:
    user_data++;
}

int main()
{
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGBA>);//前半句表示XYZRGB，使用Ptr而不是*表示建立的是智能指针类型
    pcl::io::loadPCDFile("rabbit.pcd", *cloud);
    pcl::visualization::CloudViewer viewer("Cloud Viewer");



    //blocks until the cloud is actually rendered
    viewer.showCloud(cloud);

    //use the following functions to get access to the underlying more advanced/powerful
    //PCLVisualizer

    //This will only get called once
    viewer.runOnVisualizationThreadOnce(viewerOneOff);

    //This will get called once per visualization iteration
    viewer.runOnVisualizationThread(viewerPsycho);
    while (!viewer.wasStopped())
    {
        //you can also do cool processing here
        //FIXME: Note that this is running in a separate thread from viewerPsycho
        //and you should guard against race conditions yourself...
        user_data++;
    }
    return 0;
}