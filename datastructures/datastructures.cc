/**
 * @brief The Datastructures class
 * Made for a school project
 * Created by Jade Pitkänen
 */

#include "datastructures.hh"
#include "customtypes.hh"

Datastructures::Datastructures()
{
}

Datastructures::~Datastructures()
{
}

unsigned int Datastructures::get_bite_count()
{
    // Returns the number of bites in the database

    return bites.size();
}

void Datastructures::clear_all()
{
    // Clears all bites and contours in the database

    bites.clear();
    coords.clear();
    names.clear();
    contours.clear();
}

std::vector<BiteID> Datastructures::all_bites()
{
    // Returns vector of all BiteIDs

    auto it = bites.begin();
    std::vector<BiteID> new_vector;
    new_vector.reserve(bites.size());

    for (it = bites.begin(); it != bites.end(); ++it) {
        new_vector.push_back(it->first);
    }
    return new_vector;
}

bool Datastructures::add_bite(BiteID id, const Name & name, Coord xy)
{
    // If valid, adds a new bite to the database

    auto it = bites.find(id);

    if (it != bites.end() || find_bite_with_coord(xy) != NO_BITE) {
        return false;
    }

    Bite new_bite = {name, xy};

    bites.insert({id, new_bite});
    coords.insert({xy,id});
    names.insert({name, id});

    return true;
}

Name Datastructures::get_bite_name(BiteID id)
{
    // If found, returns the name of bite

    auto it = bites.find(id);

    if (it != bites.end()) {
        return it->second.name;
    }
    return NO_NAME;
}

Coord Datastructures::get_bite_coord(BiteID id)
{
    // If found, returns the Coord of bite

    auto it = bites.find(id);

    if (it != bites.end()) {
        return it->second.xy;
    }
    return NO_COORD;
}

std::vector<BiteID> Datastructures::get_bites_alphabetically()
{
    // Returns a vector of BiteIDs sorted alphabetically based on names

    auto it = names.begin();

    std::vector<BiteID> id_vect;
    id_vect.reserve(names.size());

    for (it = names.begin(); it != names.end(); ++it) {
        id_vect.push_back(it->second);
    }
    return id_vect;
}

std::vector<BiteID> Datastructures::get_bites_distance_increasing()
{
    // Creates BiteID vector sorted based on Manhattan-distance of coords

    auto it = coords.begin();

    std::vector<BiteID> id_vect;
    id_vect.reserve(coords.size());

    for (it = coords.begin(); it != coords.end(); ++it) {
        id_vect.push_back(it->second);
    }
    return id_vect;
}

BiteID Datastructures::find_bite_with_coord(Coord xy)
{
    // Finds BiteID based on Coord

    auto it = coords.find(xy);

    if (it != coords.end()) {
        return it->second;
    }
    return NO_BITE;
}

bool Datastructures::change_bite_coord(BiteID id, Coord newcoord)
{
    // If bite is found, changes bite Coord to given new Coord

    auto it = bites.find(id);

    if (it == bites.end()) {
        return false;
    }

    if (find_bite_with_coord(newcoord) != NO_BITE) {
        return false;
    }

    coords.erase(it->second.xy);
    coords.insert({newcoord, id});
    it->second.xy = newcoord;

    return true;
}

bool Datastructures::add_contour(ContourID id, const Name & name, ContourHeight height,
                                 std::vector<Coord> coords)
{
    // If valid, adds a new contour to database

    if (coords.empty() || height > MAX_CONTOUR_HEIGHT || height <- MAX_CONTOUR_HEIGHT) {
        return false;
    }

    auto it = contours.find(id);

    if (it != contours.end()) {
        return false;
    }

    Contour new_contour = {name, height, coords};
    contours.insert({id, new_contour});

    return true;
}

std::vector<ContourID> Datastructures::all_contours()
{
    // Returns vector of all ContourIDs in database

    std::vector<ContourID> id_vect;
    id_vect.reserve(contours.size());

    auto it = contours.begin();

    for (it = contours.begin(); it != contours.end(); ++it) {
        id_vect.push_back(it->first);
    }
    return id_vect;
}

Name Datastructures::get_contour_name(ContourID id)
{
    // Returns contour name, if id is found

    auto it = contours.find(id);

    if (it != contours.end()) {
        return it->second.name;
    }
    return NO_NAME;
}

std::vector<Coord> Datastructures::get_contour_coords(ContourID id)
{
    // Returns vector of contour coords, if id is found

    auto it = contours.find(id);

    if (it != contours.end()) {
        return it->second.coords;
    }
    std::vector<Coord> no_coords;
    no_coords.push_back(NO_COORD);
    return no_coords;
}

ContourHeight Datastructures::get_contour_height(ContourID id)
{
    // Returns contour height, if id is found

    auto it = contours.find(id);

    if (it != contours.end()) {
        return it->second.height;
    }
    return NO_CONTOUR_HEIGHT;
}

bool Datastructures::add_subcontour_to_contour(ContourID id,
                                               ContourID parentid)
{
    // If found, adds given contour as subcontour of given parent

    auto c_it = contours.find(id);
    auto p_it = contours.find(parentid);

    if (c_it == contours.end() || p_it == contours.end()) {
        return false;
    }

    if (abs(c_it->second.height) < abs(p_it->second.height)
        || abs(c_it->second.height - p_it->second.height) != 1
        || c_it->second.parent != NO_CONTOUR) {
        return false;
    }
    c_it->second.parent = parentid;
    p_it->second.subcontours.push_back(id);

    return true;
}

bool Datastructures::add_bite_to_contour(BiteID biteid, ContourID contourid)
{
    // If found, adds given bite to given contour

    auto c_it = contours.find(contourid);

    if (c_it == contours.end()) {
        return false;
    }

    auto b_it = bites.find(biteid);

    if (b_it == bites.end()) {
        return false;
    }
    Coord xy1 = b_it->second.xy;

    auto coord_it = find(c_it->second.coords.begin(),
                         c_it->second.coords.end(), xy1);

    if (coord_it == c_it->second.coords.end() ||
        b_it->second.contour != NO_CONTOUR) {
        return false;
    }
    c_it->second.bites.push_back(biteid);
    b_it->second.contour = contourid;

    return true;
}

std::vector<ContourID> Datastructures::get_bite_in_contours(BiteID id)
{
    // If found, returns all contours the given bite is part of

    auto b_it = bites.find(id);
    std::vector<ContourID> id_vect = {};

    if (b_it == bites.end()) {
        id_vect.push_back(NO_CONTOUR);
        return id_vect;
    }

    auto c_it = contours.find(b_it->second.contour);

    if (c_it == contours.end()) {
        return id_vect;
    }

    while (c_it->second.parent != NO_CONTOUR) {
        id_vect.push_back(c_it->first);
        c_it = contours.find(c_it->second.parent);
    }
    id_vect.push_back(c_it->first);
    return id_vect;
}

void Datastructures::add_subcontours(std::vector<ContourID>& vect, ContourID parent) {
    auto p_it = contours.find(parent);

    for (auto c_it : p_it->second.subcontours) {
        vect.push_back(c_it);
        add_subcontours(vect, c_it);
    }
}

std::vector<ContourID>
Datastructures::all_subcontours_of_contour(ContourID id)
{
    auto p_it = contours.find(id);
    std::vector<ContourID> id_vect = {};

    if (p_it == contours.end()) {
        id_vect.push_back(NO_CONTOUR);
        return id_vect;
    }
    if (p_it->second.subcontours.empty()) {
        return id_vect;
    }
    add_subcontours(id_vect, id);

    return id_vect;
}

ContourID
Datastructures::get_closest_common_ancestor_of_contours(ContourID id1,
                                                        ContourID id2)
{
    // Goes through given contour parents and finds if they have
    // a common ancestor

    auto it1 = contours.find(id1);
    auto it2 = contours.find(id2);

    if (it1 == contours.end() || it2 == contours.end()) {
        return NO_CONTOUR;
    }

    std::vector<ContourID> ids1 = {};

    while (it1->second.parent != NO_CONTOUR) {
        ids1.push_back(it1->first);
        it1 = contours.find(it1->second.parent);
    }
    ids1.push_back(it1->first);

    while (it2->second.parent != NO_CONTOUR) {
        if (std::find(ids1.begin(), ids1.end(), it2->first) != ids1.end()) {
            return it2->second.parent;
        }
        it2 = contours.find(it2->second.parent);
    }
    if (std::find(ids1.begin(), ids1.end(), it2->first) != ids1.end()) {
        return it2->second.parent;
    }
    return NO_CONTOUR;
}

bool Datastructures::remove_bite(BiteID id)
{
    //If found, removes bite with the given id

    auto it = bites.find(id);

    if (it == bites.end()) {
        return false;
    }

    Coord xy = get_bite_coord(id);
    coords.erase(xy);

    // Names can be multiples so let's make sure to remove
    // the right one
    auto range = names.equal_range(get_bite_name(id));

    for (auto it = range.first; it != range.second; ++it) {
        if (it->second == id) {
            names.erase(it);
            break;
        }
    }
    bites.erase(id);

    return true;
}

unsigned int Datastructures::calculate_distance(Coord xy1, Coord xy2) {
    // Calculates the Manhattan distance between 2 points

    unsigned int d = abs(xy1.x - xy2.x) + abs(xy1.y - xy2.y);

    return d;
}

void Datastructures::sort_distance_map_IDs(std::multimap<unsigned int, BiteID>& d_map,
                                           unsigned int d) {
    // Sorts given map of distances and BiteIDs based on y-coord and id

    auto range = d_map.equal_range(d);

    std::vector<std::pair<Coord, BiteID>> sorted;

    for (auto it = range.first; it != range.second; ++it) {
        Coord xy = get_bite_coord(it->second);
        sorted.emplace_back(xy, it->second);
    }

    std::sort(sorted.begin(), sorted.end(), [](const std::pair<Coord, BiteID>& a,
                                            const std::pair<Coord, BiteID>& b) {
        if (a.first.y != b.first.y) {
            return a.first.y < b.first.y;
        }
        return a.second < b.second;
    });

    d_map.erase(range.first, range.second);

    for (const auto& pair : sorted) {
        d_map.emplace(d, pair.second);
    }
}

std::vector<BiteID> Datastructures::get_bites_closest_to(Coord xy)
{
    // Returns vector of up to 3 closest bites to coordinate

    auto it = coords.begin();

    std::vector<BiteID> closest;
    closest.reserve(3);

    std::multimap<unsigned int, BiteID> d_map;

    for (it = coords.begin(); it != coords.end(); ++it) {
        unsigned int d = calculate_distance(xy, it->first);
        d_map.insert({d, it->second});
    }

    for (const auto& pair : d_map) {
        sort_distance_map_IDs(d_map, pair.first);
    }

    unsigned int i = 0;

    for (auto it = d_map.begin(); i < 3 && it != d_map.end(); ++it) {
        closest.push_back(it->second);
        ++i;
    }
    return closest;
}
