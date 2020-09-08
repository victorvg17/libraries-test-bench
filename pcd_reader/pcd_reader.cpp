#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

void iterate_over_cloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_ptr) {
	for (int i=0; i<10; i++) {
		const auto& point = cloud_ptr->points[i];
		std::cout << " " << point.x
				  << " " << point.y 
				  << " " << point.z << std::endl;
		// cloud_ptr++;
	}
	
}
int main (int argc, char ** argv) {
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_ptr
	(new pcl::PointCloud<pcl::PointXYZ>);

	int success = pcl::io::loadPCDFile<pcl::PointXYZ>("../GP_gantry.pcd", *cloud_ptr);
	if (success != 0) {
		std::cout << "could not load GP_trolley.pcd file" << std::endl;
		return -1;
	}

	std::cout << "loaded " << cloud_ptr->width * cloud_ptr->height <<
				" data points from GP_trolley.pcd" << std::endl;
	iterate_over_cloud(cloud_ptr);
}
