#include <sstream>
#include <string>
#include <set>
#include <exception>
#include <iostream>

// Boost property tree
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

// Boost program options
#include "boost/program_options.hpp"

// Boost.Geometry
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/algorithms/intersection.hpp>
#include <boost/geometry/geometries/register/segment.hpp>

using namespace boost::geometry;
namespace pt = boost::property_tree;

typedef model::d2::point_xy<double> Point;
typedef model::polygon<Point, false, false> Polygon;
typedef model::segment<Point> Segment;

Polygon operator+(
  const Polygon& poly,
  const Point& offset)
{
  Polygon result;
  result.outer().reserve(poly.outer().size());
  for (auto&& p : poly.outer()) {
    append(result, Point(p.x() + offset.x(), p.y() + offset.y()));
  }
  return result;
}

double run(
  const std::string& sceneFile,
  const std::string& outputFile)
{
  // Declare a stream and an SVG mapper
  std::ofstream svg(outputFile);
  boost::geometry::svg_mapper<Point> mapper(svg, 400, 400, "width=\"400\" height=\"400\"");

  // Create empty property tree object
  pt::ptree tree;

  // Parse the JSON into the property tree.
  pt::read_json(sceneFile, tree);

  // read boundary
  Polygon poly;
  boost::geometry::read_wkt(tree.get<std::string>("boundary"), poly);
  mapper.add(poly);
  mapper.map(poly, "fill-opacity:1.0;fill:none;stroke:rgb(0,0,0);stroke-width:5");

  // read targets
  std::vector<Polygon> objectPaths;
  std::vector<double> objectVelocities;

  for (auto& item : tree.get_child("targets")) {
    Polygon shape;
    boost::geometry::read_wkt(item.second.get<std::string>("shape"), shape);
    Polygon path;
    boost::geometry::read_wkt(item.second.get<std::string>("path"), path);
    double vel = item.second.get<double>("velocity", 1.0);

    mapper.map(shape + path.outer().front(), "fill-opacity:1.0;fill:rgb(153,153,153)");
    mapper.map(path, "fill-opacity:0.8;fill:none;stroke:rgb(0,0,255);stroke-width:2");

    if (path.outer().size() > 1) {
      std::stringstream sstr;
      sstr << vel << " m/s";
      mapper.text(path.outer().front(), sstr.str(), "fill:rgb(0,0,0);font-family:Arial;font-size:15px");
    }
  }

  // read obstacles
  for (auto& item : tree.get_child("obstacles")) {
    Polygon shape;
    boost::geometry::read_wkt(item.second.get<std::string>("shape"), shape);
    Polygon path;
    boost::geometry::read_wkt(item.second.get<std::string>("path"), path);
    double vel = item.second.get<double>("velocity", 1.0);

    mapper.map(shape + path.outer().front(), "fill-opacity:1.0;fill:rgb(80,80,80)");
    mapper.map(path, "fill-opacity:0.8;fill:none;stroke:rgb(0,0,255);stroke-width:2");

    if (path.outer().size() > 1) {
      std::stringstream sstr;
      sstr << vel << " m/s";
      mapper.text(path.outer().front(), sstr.str(), "fill:rgb(0,0,0);font-family:Arial;font-size:15px");
    }
  }

  // read cameras
  double cameraFoV = tree.get<double>("cameraFoV") / 180 * M_PI;
  for (auto& item : tree.get_child("cameras")) {
    Point pos;
    boost::geometry::read_wkt(item.second.get<std::string>("pos"), pos);
    double angle = item.second.get<double>("angle") / 180 * M_PI;
    double maxVelocity = item.second.get<double>("maxVelocity");
    double maxAngularVelocity = item.second.get<double>("maxAngularVelocity");

    boost::geometry::model::linestring<Point> polyline;
    const double length = 2;
    append(polyline, Point(length * cos(angle - cameraFoV) + pos.x(), length * sin(angle - cameraFoV) + pos.y()));
    append(polyline, pos);
    append(polyline, Point(length * cos(angle + cameraFoV) + pos.x(), length * sin(angle + cameraFoV) + pos.y()));
    mapper.map(pos, "fill-opacity:0.5;fill:rgb(153,204,0);stroke:rgb(153,204,0);stroke-width:2", 5);
    mapper.map(polyline, "fill-opacity:0.8;fill:none;stroke:rgb(153,204,0);stroke-width:2");

    std::stringstream sstr;
    sstr << maxVelocity << " m/s\n" << maxAngularVelocity << " rad/s";
    mapper.text(pos, sstr.str(), "fill:rgb(0,0,0);font-family:Arial;font-size:15px");
  }
}

int main(int argc, char** argv)
{
  namespace po = boost::program_options;
  // Declare the supported options.
  po::options_description desc("Allowed options");
  desc.add_options()
      ("help", "produce help message")
      ("scene,s", po::value<std::string>()->required(), "input file for scene")
      ("output,o", po::value<std::string>()->required(), "output file")
  ;

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);

  if (vm.count("help")) {
      std::cout << desc << std::endl;
      return 1;
  }

  po::notify(vm);

  run(
    vm["scene"].as<std::string>(),
    vm["output"].as<std::string>());

  return 0;
}
