/* -*- mode: C++ -*- */
/*  Copyright (C) 2010 UT-Austin & Austin Robot Technology,
 *  David Claridge, Michael Quinlan
 * 
 *  License: Modified BSD Software License 
 */


#ifndef _HEIGHT_MAP_H_
#define _HEIGHT_MAP_H_

#include <ros/ros.h>
#include <pcl_ros/point_cloud.h>
#include <std_msgs/Bool.h>
#include <iostream>

namespace polar_height_map {

// shorter names for point cloud types in this namespace
typedef pcl::PointXYZI VPoint;
typedef pcl::PointCloud<VPoint> VPointCloud;

class HeightMap
{
public:

  /** Constructor
   *
   *  @param node NodeHandle of this instance
   *  @param private_nh private NodeHandle of this instance
   */
  HeightMap(ros::NodeHandle node, ros::NodeHandle private_nh);
  ~HeightMap();

  /** callback to process data input
   *
   *  @param scan vector of input 3D data points
   *  @param stamp time stamp of data
   *  @param frame_id data frame of reference
   */
  void processData(const VPointCloud::ConstPtr &scan);

  void shutdown_cb(const std_msgs::Bool::ConstPtr &msg); 

private:
  void constructFullClouds(const VPointCloud::ConstPtr &scan, unsigned npoints,
                           size_t &obs_count, size_t &empty_count);
  void constructGridClouds(const VPointCloud::ConstPtr &scan, unsigned npoints,
                           size_t &obs_count, size_t &empty_count);



  // Parameters that define the grids and the height threshold
  // Can be set via the parameter server
  double g_per_cell_phi;
  double m_per_cell_polar;
  //int grid_dim_;
  int grid_dim_z_polar;
  int grid_dim_phi;
  //double m_per_cell_;
  double height_diff_threshold_;
  bool full_clouds_;
  
  

 
  
  

  // Point clouds generated in processData
  VPointCloud obstacle_cloud_;            
  VPointCloud clear_cloud_;            

  // ROS topics
  ros::Subscriber polar_scan_;
  ros::Subscriber shutdown_sub;
  ros::Publisher obstacle_publisher_;
  ros::Publisher clear_publisher_;
};

} // namespace polar_height_map

#endif
