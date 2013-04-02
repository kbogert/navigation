#ifndef FOOTPRINT_COSTMAP_PLUGIN_H_
#define FOOTPRINT_COSTMAP_PLUGIN_H_
#include <ros/ros.h>
#include <costmap_2d/plugin_ros.h>
#include <costmap_2d/layered_costmap.h>
#include <costmap_2d/costmap_math.h>
#include <costmap_2d/GenericPluginConfig.h>
#include <dynamic_reconfigure/server.h>
#include <nav_msgs/OccupancyGrid.h>
#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/PolygonStamped.h>

namespace common_costmap_plugins
{
  class FootprintCostmapPlugin : public costmap_2d::CostmapPluginROS
  {
    public:
      FootprintCostmapPlugin() { layered_costmap_ = NULL; }

      void initialize(costmap_2d::LayeredCostmap* costmap, std::string name);
      void update_bounds(double origin_x, double origin_y, double origin_yaw, double* min_x, double* min_y, double* max_x, double* max_y);
      void update_costs(costmap_2d::Costmap2D& master_grid, int min_i, int min_j, int max_i, int max_j);

      void activate() {}
      void deactivate() {}

    private:
      void footprint_cb(const geometry_msgs::Polygon& footprint);
      ros::Subscriber footprint_sub_;
      bool got_footprint_;
      geometry_msgs::Polygon footprint_spec_;
      geometry_msgs::PolygonStamped footprint_;
      void publishFootprint();
      void reconfigureCB(costmap_2d::GenericPluginConfig &config, uint32_t level);
      ros::Publisher footprint_pub_;
      dynamic_reconfigure::Server<costmap_2d::GenericPluginConfig> *dsrv_;
  };
};
#endif
