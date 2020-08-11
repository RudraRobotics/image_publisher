#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh("~");
  std::string img;

//  nh.getParam("img", img);
//  if(img.empty()) {
//      ROS_WARN("No image passed, abort!");
//      return 0;
//  }
//  ROS_INFO("Got parameter : %s", img.c_str());
  if(argc<2) {
      ROS_ERROR("Enter image as an argument!");
      return 0;
  }
  ROS_INFO("Got parameter : %s", argv[1]);
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("/cv_camera/image_raw", 1);
  cv::Mat image = cv::imread(argv[1], cv::IMREAD_COLOR);
  cv::waitKey(30);
  sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();

  ros::Rate loop_rate(5);
  while (nh.ok()) {
    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
  nh.deleteParam("img");
}
