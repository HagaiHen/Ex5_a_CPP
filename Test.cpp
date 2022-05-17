#include <string>
#include "doctest.h"
#include "OrgChart.hpp"
using namespace ariel;

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

TEST_CASE("Add root, Add sub") {
    
    OrgChart org;
    
    CHECK_NOTHROW(org.add_root("Hagai"));
    CHECK_NOTHROW(org.add_sub("Hagai", "Lior"));

    CHECK(org.get_root()->get_data() == "Hagai");

    CHECK_NOTHROW(org.add_root("Lior"));

    CHECK(org.get_root()->get_data() == "Lior");

    CHECK_NOTHROW(org.add_root("Hagai"));

    CHECK(org.get_node("Lior")->get_parent()->get_data() == "Hagai");

    CHECK(org.get_sub("Hagai").size() == 1);

    org.add_sub("Hagai", "Yotam");
    org.add_sub("Hagai", "Neta");

    CHECK(org.get_sub("Hagai").size() == 3);

    CHECK(org.get_sub("Hagai").at(0)->get_data() == "Lior");
    CHECK(org.get_sub("Hagai").at(1)->get_data() == "Yotam");
    CHECK(org.get_sub("Hagai").at(2)->get_data() == "Neta");
    
    CHECK_NOTHROW(org.add_sub("Lior", "Amit"));

    CHECK(org.get_node("Amit")->get_parent()->get_data() == "Lior");

    org.add_sub("Amit", "Ron");

    CHECK(org.get_sub("Lior").size() == 1);
    CHECK(org.get_sub("Lior").at(0)->get_data() == "Amit");

    CHECK_THROWS(org.get_sub("Ariel"));
    
    CHECK_NOTHROW(org.get_sub("Hagai"));
    CHECK_NOTHROW(org.get_sub("Lior"));
    CHECK_NOTHROW(org.get_sub("Neta"));
    CHECK_NOTHROW(org.get_sub("Yotam"));

    CHECK(org.get_node("Lior")->get_data() == "Lior");

    CHECK(org.get_node("Lior")->get_parent()->get_data() == "Hagai");
    CHECK(org.get_node("Amit")->get_parent()->get_data() == "Lior");
    
}
TEST_CASE("Level Order") {

    OrgChart org;
    
    org.add_root("Hagai");
       
    org.add_sub("Hagai", "Lior");
    org.add_sub("Hagai", "Yotam");
    org.add_sub("Hagai", "Neta");
    org.add_sub("Lior", "Amit");
    org.add_sub("Amit", "Ron");

    vector<string> vec;

    vec.push_back("Hagai");
    vec.push_back("Lior");
    vec.push_back("Yotam");
    vec.push_back("Neta");
    vec.push_back("Amit");
    vec.push_back("Ron");
    size_t i = 0;
    
    for (auto it = org.begin_level_order(); it != org.end_level_order(); ++it) {
        CHECK((*it) == vec[i]);
        i++;
    }
}

TEST_CASE("Reverse Level Order") {
    OrgChart org;
    
    org.add_root("Hagai");
    org.add_sub("Hagai", "Lior");
    org.add_sub("Hagai", "Yotam");
    org.add_sub("Hagai", "Neta");
    org.add_sub("Lior", "Amit");
    org.add_sub("Amit", "Ron");

    vector<string> vec;

    vec.push_back("Ron");
    vec.push_back("Amit");
    vec.push_back("Lior");
    vec.push_back("Yotam");
    vec.push_back("Neta");
    vec.push_back("Hagai");

    size_t i = 0;
    for (auto it = org.begin_level_order(); it != org.end_level_order(); ++it) {
        CHECK((*it) == vec[i]);
        i++;
    }
}

TEST_CASE("PreOrder") {

    OrgChart org;
    
    org.add_root("Hagai");
    org.add_sub("Hagai", "Lior");
    org.add_sub("Hagai", "Yotam");
    org.add_sub("Hagai", "Neta");
    org.add_sub("Lior", "Amit");
    org.add_sub("Amit", "Ron");

    vector<string> vec;

    vec.push_back("Hagai");
    vec.push_back("Lior");
    vec.push_back("Amit");
    vec.push_back("Ron");      
    vec.push_back("Yotam");
    vec.push_back("Neta");
    
    size_t i = 0;
    
    for (auto it = org.begin_level_order(); it != org.end_level_order(); ++it) {
        CHECK((*it) == vec[i]);
        i++;
    }
}