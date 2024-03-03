#include <pcl/visualization/cloud_viewer.h>
#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkInteractionStyle);//��ʼ���� VTK �еĽ�����ʽģ��
VTK_MODULE_INIT(vtkRenderingFreeType);//��ʼ���� VTK �е� FreeType ��Ⱦģ��
VTK_MODULE_INIT(vtkRenderingOpenGL2);//��ʼ���� VTK �е� OpenGL2 ��Ⱦģ��
using namespace std;
using namespace pcl;
int user_data;

void viewerOneOff(pcl::visualization::PCLVisualizer& viewer)//viewer�Ǵ����Ŀ��ӻ���
{
    viewer.setBackgroundColor(1.0, 0.5, 1.0);//���ñ�����ɫ
    PointXYZ o;//����һ��PointXYZ���͵ĵ㣬�����õ��ʼ��
    o.x = 0;
    o.y = 0;
    o.z = 1.0;
    //viewer.addSphere(o, 0.25, "sphere", 0);//���ģ��뾶��id������Ŀ��ӻ�����0������Ĭ��ֵ
    cout << "i only run once" << endl;

}

void viewerPsycho(pcl::visualization::PCLVisualizer& viewer)
{
    static unsigned count = 0;//��̬���ݱ�����ȫ�ֱ���
    stringstream ss;//�ṩ��һ������Ľӿڣ��������ַ�����������������֮�����ת�����ر�������Ҫ���ַ����й����������������ʱ�ǳ����á�
    ss << "Once per viewer loop: " << count++;
    viewer.removeShape("text", 0);//�������֮ǰ������
    viewer.addText(ss.str(), 100, 100, "text", 0);//�����µ���ʾ�ı���200 �� 300: �����ı��ڴ����е�λ�ã��ֱ��ʾ x �� y ���ꡣ

    //FIXME: possible race condition here:
    user_data++;
}

int main()
{
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGBA>);//ǰ����ʾXYZRGB��ʹ��Ptr������*��ʾ������������ָ������
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