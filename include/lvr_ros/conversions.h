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
 * conversions.h
 *
 * created on: 30.04.2014
 *
 * Author: Henning Deeken <hdeeken@uos.de>,
 *         Sebastian Pütz <spuetz@uos.de>,
 *         Marcel Mrozinski <mmrozins@uos.de>,
 *         Tristan Igelbrink <tigelbri@uos.de>
 *
 */

#ifndef LVR_ROS_CONVERSIONS_H_
#define LVR_ROS_CONVERSIONS_H_

#include <map>

#include <ros/ros.h>
#include <ros/console.h>

#include <lvr2/geometry/BaseVector.hpp>
#include <lvr2/io/PointBuffer.hpp>
#include <lvr2/io/MeshBuffer.hpp>
#include <lvr2/geometry/BaseMesh.hpp>
#include <lvr2/attrmaps/AttrMaps.hpp>

#include <lvr/io/Model.hpp>
#include <lvr/io/MeshBuffer.hpp>
#include <lvr/io/PLYIO.hpp>
#include <lvr/io/DataStruct.hpp>
#include <lvr/io/ModelFactory.hpp>

#include <lvr/texture/Texture.hpp>
#include <lvr/geometry/Vertex.hpp>
#include <lvr/geometry/HalfEdgeMesh.hpp>

#include <std_msgs/String.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/fill_image.h>

#include <mesh_msgs/Cluster.h>
#include <mesh_msgs/Material.h>
#include <mesh_msgs/PolygonIndices.h>
#include <mesh_msgs/PolygonMesh.h>
#include <mesh_msgs/PolygonMeshStamped.h>
#include <mesh_msgs/TriangleIndices.h>
#include <mesh_msgs/TriangleMesh.h>
#include <mesh_msgs/TriangleMeshStamped.h>
#include <mesh_msgs/MeshGeometry.h>
#include <mesh_msgs/MeshGeometry.h>
#include <mesh_msgs/MeshMaterialsStamped.h>
#include <mesh_msgs/MeshMaterialsStamped.h>
#include <mesh_msgs/MeshVertexColors.h>
#include <mesh_msgs/MeshVertexColorsStamped.h>
#include <mesh_msgs/VertexTexCoords.h>
#include <mesh_msgs/Material.h>

#include <sensor_msgs/point_cloud2_iterator.h>


namespace lvr_ros
{

using Vec = lvr2::BaseVector<float>;
using PointBuffer = lvr2::PointBuffer<Vec>;
using PointBufferPtr = lvr2::PointBufferPtr<Vec>;

struct MaterialGroup
{
    int texture_index;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    std::vector<unsigned int> faceBuffer;
};

typedef std::vector <boost::shared_ptr<MaterialGroup>> GroupVector;
typedef boost::shared_ptr <MaterialGroup> MaterialGroupPtr;



/// Convert lvr2::MeshBuffer to various messages for services
bool fromMeshBufferToMeshMessages(
    const lvr2::MeshBufferPtr<Vec>& buffer,
    mesh_msgs::MeshGeometry& mesh_geometry,
    mesh_msgs::MeshMaterials& mesh_materials,
    mesh_msgs::MeshVertexColors& mesh_vertex_colors,
    boost::optional<std::vector<sensor_msgs::Image>&> texture_cache
);

/**
 * @brief Convert lvr::MeshBuffer to mesh_msgs::TriangleMesh
 * @param buffer to be read
 * @param message to be returned
 * @return bool success status
 */
bool fromMeshBufferToTriangleMesh(
    const lvr::MeshBufferPtr& buffer,
    mesh_msgs::TriangleMesh& message
);

bool fromMeshBufferToTriangleMesh(
    lvr::MeshBuffer& buffer,
    mesh_msgs::TriangleMesh& message
);

/**
 * @brief Convert mesh_msgs::TriangleMesh to lvr::MeshBuffer
 * @param message to be read
 * @param buffer to be returned
 * @return bool success status
 */
bool fromTriangleMeshToMeshBuffer(
    const mesh_msgs::TriangleMesh& mesh,
    lvr::MeshBuffer& buffer
);

bool fromPolygonMeshToTriangleMesh(
    const mesh_msgs::PolygonMesh& polygon_mesh,
    mesh_msgs::TriangleMesh& triangle_mesh
);

void removeDuplicates(lvr::MeshBuffer& buffer);

void removeDuplicates(mesh_msgs::TriangleMesh& mesh);

/**
 * @brief Creates a LVR-MeshBufferPointer from a file
 *
 * @param path    Path to a MeshFile
 *
 * @return LVR-MeshBufferPointer
 */
bool readMeshBuffer(lvr::MeshBufferPtr& buffer, string path);

/**
 * @brief Writes a LVR-MeshBufferPointer to a file
 *
 * @param mesh   LVR-MeshBufferPointer
 * @param path   Path to a MeshFile
 */
bool writeMeshBuffer(lvr::MeshBufferPtr& mesh, string path);

/**
 * @brief Reads a file and returns a lvr_ros/TriangleMesh
 *
 * @param path to file
 * @param mesh to be filled
 *
 * @return bool indicating sucess/failure
 */
bool readTriangleMesh(mesh_msgs::TriangleMesh& mesh, string path);

/**
 * @brief Writes a ROS-TriangleMeshGeometryMessage to a file
 *
 * @param mesh   ROS-TriangleMeshGeometryMessage
 * @param path   Path to a MeshFile
 */
bool writeTriangleMesh(mesh_msgs::TriangleMesh& mesh, string path);

/**
 * @brief Writes intensity values as rainbow colors for the triangle colors
 *
 * @param intensity Intensity values as std::vector<float>
 * @param mesh      ROS-TriangleMeshGeometryMessage
 */
void intensityToTriangleRainbowColors(const std::vector<float>& intensity, mesh_msgs::TriangleMesh& mesh);

/**
 * @brief Writes intensity values as rainbow colors for the triangle colors
 *
 * @param intensity Intensity values
 * @param mesh      ROS-TriangleMeshGeometryMessage
 * @param min       The minimal value
 * @param max       The maximal value
 */
void intensityToTriangleRainbowColors(
    const std::vector<float>& intensity,
    mesh_msgs::TriangleMesh& mesh,
    float min,
    float max
);

/**
 * @brief Writes intensity values as rainbow colors for the vertex colors
 *
 * @param intensity Intensity values as std::vector<float>
 * @param mesh      ROS-TriangleMeshGeometryMessage
 * @param min       The minimal value
 * @param max       The maximal value
 */
void intensityToVertexRainbowColors(
    const std::vector<float>& intensity,
    mesh_msgs::TriangleMesh& mesh,
    float min,
    float max
);

/**
 * @brief Writes intensity values as rainbow colors for the vertex colors
 *
 * @param intensity Intensity values as DenseVertexMap<float>
 * @param mesh      ROS-TriangleMeshGeometryMessage
 * @param min       The minimal value
 * @param max       The maximal value
 */
void intensityToVertexRainbowColors(
    const lvr2::DenseVertexMap<float>& intensity,
    mesh_msgs::TriangleMesh& mesh,
    float min,
    float max
);

/**
 * @brief Writes intensity values as rainbow colors for the vertex colors
 *
 * @param intensity Intensity values
 * @param mesh      ROS-TriangleMeshGeometryMessage
 */
void intensityToVertexRainbowColors(const std::vector<float>& intensity, mesh_msgs::TriangleMesh& mesh);

bool fromPointCloud2ToPointBuffer(const sensor_msgs::PointCloud2& cloud, PointBuffer& buffer);

} // end namespace

#endif /* LVR_ROS_CONVERSIONS_H_ */
