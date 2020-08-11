#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <vector>
using namespace std;
using namespace cv;
int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("/cv_camera/image_raw", 1);
  vector<cv::String> fn;
  string path = argv[1];
  glob(path+"*.jpg", fn, false);
  
  ros::Rate loop_rate(5);
  while(nh.ok() && ros::ok()) {
	  for (size_t i=0; i<fn.size() && ros::ok();i++) {
	    Mat image = imread(fn[i]);
	    sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
	    pub.publish(msg);
	    ros::spinOnce();
	    loop_rate.sleep();
	  }
  }
  //cv::Mat image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
  //cv::waitKey(30);
  //sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();

  /*ros::Rate loop_rate(5);
  while (nh.ok()) {
    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }*/
}
