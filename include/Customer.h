#pragma once

#include <json.hpp>

/*
define customer type
*/
typedef struct Customer {

    std::string lname;
    std::string fname;
    std::string email;
    int id;
    float spent;

} Customer;

/*
defined to convert to a struct from json
*/
void from_json(const nlohmann::json & j, Customer & t) {
    j.at("lname").get_to(t.lname);
    j.at("fname").get_to(t.fname);
    j.at("email").get_to(t.email); 
    j.at("id").get_to(t.id); 
    j.at("spent").get_to(t.spent); 
}


