#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <json.hpp>
#include <Customer.h>

/*
load customers into vector of customers
*/
std::vector<Customer> loadCustomers(std::string fname="customers.json");

/*
input a string
return a copy that is converted to lowercase
*/
std::string toLower(std::string const & data);

/*
apply relevant discount
- Call a function that accepts two paramers - a customer object and a string.  Then apply a 50% reduction in "spent" if customer first name contains a specific NON case sensitive string match that is supplied as function's second parameter (use "jack" for your test)
*/
Customer const applyDiscount(Customer const & cust, std::string comp);

std::vector<Customer> const applyDiscount(std::vector<Customer> vec, std::string comp);

/*
sort operator to descend
*/
bool compareByIdDescend(const Customer &a, const Customer &b) {return a.id > b.id;}

/*
do customer printing
*/
void customerPrinter(std::vector<Customer> const& vec);


int main(){

    std::cout<<"starting"<<std::endl;

    // load customers
    auto customers = loadCustomers("customers.json");

    // apply discounts
    auto discountCustomers = applyDiscount(customers, "jack");
    //
    // - sort the vector of customers by customer ID in descending order (using std::sort)
    
    auto csort = discountCustomers;
    std::sort(csort.begin(), csort.end(), compareByIdDescend);
   
    // - print customer id, email and spent (iterate the vector using "auto" types)

    customerPrinter(csort);


    // - calculate and print average customer "spent" using a Generic Lambda

    auto avg = [](auto x) {
        float retval = 0;
        for ( auto &i : x ) retval += i.spent;
        return retval / x.size();
    }; 

    std::cout<<avg(csort)<<std::endl;

    std::cout<<"ending"<<std::endl;
    return 0;
}

std::vector<Customer> loadCustomers(std::string fname) {

    std::ifstream f(fname);
    nlohmann::json j;

    if (f) {
        j << f;
    }
    std::vector<Customer> customers = j["customers"];
    return customers;
}
std::string toLower(std::string const & data) {
    
    auto ret = data;
    // convert string to back to lower case
    std::for_each(ret.begin(), ret.end(), [](char & c){
        c = ::tolower(c);
    });
    return ret;
}

Customer const applyDiscount(Customer const & cust, std::string comp) {
 
   auto ret = cust;

   auto lfname = toLower(cust.fname);
   if (lfname.compare(toLower(comp)) == 0){
       std::cout<<"apply discount!"<<std::endl;
       ret.spent = cust.spent*0.5;
        
   } else std::cout<<"no discount!"<<std::endl;
   std::cout<<lfname<<"\t"<<comp<<std::endl;
   
   return ret;
    
}

void customerPrinter(std::vector<Customer> const& vec) {

   for (auto &it : vec )
    {
        std::cout<<it.id
                 <<"\t"<<it.email
                 <<"\t"<<it.spent
                 <<std::endl;
    }

}

std::vector<Customer> const applyDiscount(std::vector<Customer> vec, std::string comp){
    auto ret = vec;
    for (auto &it : vec ) {
        ret.push_back(applyDiscount(it, comp));
    }
    return ret;
}

