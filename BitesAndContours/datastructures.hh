// Datastructures.hh
// Created by Jade Pitkänen
// Information for estimates of performance found on cplusplus.com
// AI tool used and the version: Chat GPT-4o
// The purpose of the use: Debugging and general advice. No code
// was directly copied and use was minimal.
// The part(s) where it was utilized: Mainly helped with
// sort_distance_map_IDs sorting algorithim. Small bug fixing with other
// parts of code.

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include "customtypes.hh"
#include <utility>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <set>

template <typename Type>
Type random_in_range(Type start, Type end);

class Datastructures
{
public:
  Datastructures();
  ~Datastructures();

  // Estimate of performance: O(1)
  // Short rationale for estimate: complexity of .size() is constant
  unsigned int get_bite_count();

  // Estimate of performance: O(n)
  // Short rationale for estimate: .clear is linear
  void clear_all();

  // Estimate of performance: O(n)
  // Short rationale for estimate: for-loop goes through all bites in linear time
  std::vector<BiteID> all_bites();

  // Estimate of performance: O(1)
  // Short rationale for estimate: find and insert are constant on average
  bool add_bite(BiteID id, const Name &name, Coord xy);

  // Estimate of performance: O(1)
  // Short rationale for estimate: find is constant on avarage
  Name get_bite_name(BiteID id);

  // Estimate of performance: O(1)
  // Short rationale for estimate: find is constant on avarage
  Coord get_bite_coord(BiteID id);

  // Estimate of performance: O(n * log(n))
  // Short rationale for estimate: complexity of sort-function
  // is n * log(n)
  std::vector<BiteID> get_bites_alphabetically();

  // Estimate of performance: O(n)
  // Short rationale for estimate: for-loop goes through all bites
  std::vector<BiteID> get_bites_distance_increasing();

  // Estimate of performance: O(1)
  // Short rationale for estimate: find is constant on avarage
  BiteID find_bite_with_coord(Coord xy);

  // Estimate of performance: O(1)
  // Short rationale for estimate: find is constant on avarage
  bool change_bite_coord(BiteID id, Coord newcoord);

  // Estimate of performance: O(1)
  // Short rationale for estimate: find is constant on avarage
  bool add_contour(ContourID id, const Name & name, ContourHeight height,
                   std::vector<Coord> coords);

  // Estimate of performance: O(n)
  // Short rationale for estimate: for-loop goes through all contours
  std::vector<ContourID> all_contours();

  // Estimate of performance: O(1)
  // Short rationale for estimate: find is constant on avarage
  Name get_contour_name(ContourID id);

  // Estimate of performance: O(n)
  // Short rationale for estimate: find is logarithmic for maps
  //
  std::vector<Coord> get_contour_coords(ContourID id);

  // Estimate of performance: O(1)
  // Short rationale for estimate: find is constant on avarage
  ContourHeight get_contour_height(ContourID id);

  // Estimate of performance: O(1)
  // Short rationale for estimate: find is constant on avarage
  bool add_subcontour_to_contour(ContourID id, ContourID parentid);

  // Estimate of performance: O(1)
  // Short rationale for estimate: find is constant on avarage
  bool add_bite_to_contour(BiteID biteid, ContourID parentid);

  // Estimate of performance: O(n)
  // Short rationale for estimate: while-loop goes through parents linearly
  std::vector<ContourID> get_bite_in_contours(BiteID id);

  // Non-compulsory operations

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<ContourID> all_subcontours_of_contour(ContourID /*id*/);

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<BiteID> get_bites_closest_to(Coord /*xy*/);

  // Estimate of performance:
  // Short rationale for estimate:
  bool remove_bite(BiteID /*id*/);

  // Estimate of performance:
  // Short rationale for estimate:
  ContourID get_closest_common_ancestor_of_contours(ContourID /*id1*/,
                                                    ContourID /*id2*/);

private:
  struct get_distance_difference{
      // Compares Manhattan distance and y-values of 2 coords

      bool operator()(Coord xy1, Coord xy2) const {
          int d1 = abs(xy1.x)+abs(xy1.y);
          int d2 = abs(xy2.x)+abs(xy2.y);
          if (d1 != d2) {
              return (d1 < d2);
          }
          if (xy1.y != xy2.y) {
              return xy1.y < xy2.y;
          }
          return xy1.x < xy2.x;
      }
  };

  struct Contour;

  struct Bite {
      Name name;
      Coord xy;
      ContourID contour = NO_CONTOUR;
  };

  std::unordered_map<BiteID, Bite> bites;
  std::multimap<Name, BiteID> names;
  std::map<Coord, BiteID, get_distance_difference> coords;

  struct Contour {
      Name name;
      ContourHeight height;
      std::vector<Coord> coords;
      ContourID parent = NO_CONTOUR;
      std::vector<ContourID> subcontours = {};
      std::vector<BiteID> bites = {};
  };

  std::unordered_map<ContourID, Contour> contours;
  void add_subcontours(std::vector<ContourID>& vect, ContourID parent);

  void sort_distance_map_IDs(std::multimap<unsigned int, BiteID>& d_map,
                             unsigned int d);
  unsigned int calculate_distance(Coord xy1, Coord xy2);
};

#endif // DATASTRUCTURES_HH
