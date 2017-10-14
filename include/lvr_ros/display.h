/*
 * UOS-ROS packages - Robot Operating System code by the University of Osnabrück
 * Copyright (C) 2013 University of Osnabrück
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * display.h
 *
 * Author: Jan Philipp Vogtherr <jvogtherr@uni-osnabrueck.de>
 *
 */

#ifndef LVR_ROS_RECONSTRUCTION_H_
#define LVR_ROS_RECONSTRUCTION_H_

#include <ros/ros.h>

#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/Image.h>
#include <mesh_msgs/Cluster.h>
#include <mesh_msgs/Material.h>
#include <mesh_msgs/MeshGeometry.h>
#include <mesh_msgs/MeshGeometryStamped.h>
#include <mesh_msgs/MeshMaterials.h>
#include <mesh_msgs/MeshMaterialsStamped.h>
#include <mesh_msgs/MeshVertexColors.h>
#include <mesh_msgs/MeshVertexColorsStamped.h>
#include <mesh_msgs/VertexTexCoords.h>
#include <mesh_msgs/Texture.h>

#include "lvr_ros/GetGeometry.h"
#include "lvr_ros/GetMaterials.h"
#include "lvr_ros/GetTexture.h"
#include "lvr_ros/GetUUID.h"
#include "lvr_ros/GetVertexColors.h"

namespace lvr_ros
{

class Display
{
public:
    Display();
    ~Display();

private:
    void pointCloudCallback(const sensor_msgs::PointCloud2::ConstPtr cloud);
    void meshGeometryCallback(const mesh_msgs::MeshGeometryStamped::ConstPtr mesh_geometry);
    void processNewUUID(std::string uuid);
    void processNewGeometry(const mesh_msgs::MeshGeometryStamped mesh_geometry_stamped);

    ros::NodeHandle node_handle;

    ros::Subscriber cloud_subscriber;
    ros::Subscriber mesh_geometry_subscriber;

    ros::Publisher mesh_geometry_publisher;
    ros::Publisher mesh_materials_publisher;
    ros::Publisher mesh_vertex_colors_publisher;
    ros::Publisher mesh_texture_publisher;

    ros::ServiceClient mesh_geometry_service_client;
    ros::ServiceClient mesh_uuid_service_client;
    ros::ServiceClient mesh_materials_service_client;
    ros::ServiceClient mesh_vertex_colors_service_client;
    ros::ServiceClient mesh_textures_service_client;
};

} /* namespace lvr_ros */

#endif /* LVR_ROS_RECONSTRUCTION_H_ */
