#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "../src/arraylist.h"
#include <limits>
#include <algorithm>

TEST_CASE("Test Selectors", "[stl-algorithm-arraylist]"){
    using list  = a_list::arraylist<int>;
    SECTION("Test Size"){
        list instance = {1, 2, 3, 4, 5};
        REQUIRE(instance.size() == 5);
        instance.erase(std::remove_if(instance.begin(), instance.end(), [](int ele){
            return ele == 2;
        }), instance.end());
        REQUIRE(instance.size() == 4);
        instance.clear();
        REQUIRE(instance.size() == 0);
    }
    SECTION("Test Max_Size && Test Empty"){
        list instance;
        REQUIRE(instance.max_size() == std::numeric_limits<size_t>::max());
        for(size_t i = 0; i < 10000; i++){
            instance.push_back(i);
        }
        REQUIRE(instance.size() == 10000);
        instance.clear();
        REQUIRE(instance.empty() == 1);
    }
    SECTION("Test Capacity"){
        list instance;
        REQUIRE(instance.capacity() == 0);
        instance.push_back(0);
        REQUIRE(instance.capacity() == 8);
        for(size_t i = 0; i < 10000 << 1; i++){
            if(i % 8 == 0){
                REQUIRE(instance.capacity() % 8 == 0);
            }
        }
    }
    SECTION("Test At && operator []"){
        list instance;
        for(size_t i = 0; i < 1000; i++){
            instance.push_back(i);
            REQUIRE(instance.at(i) == i);
            REQUIRE(instance[i] == i);
        }
    }
    
}

TEST_CASE("Test Mutators", "[stl-algorithm-arraylist]"){
     using list  = a_list::arraylist<int>;
    SECTION("Test insert"){
        list instance = {1, 2, 3, 4, 5};
        auto const_iter = instance.cbegin();
        const_iter++; const_iter++;
        instance.insert(const_iter, 9);
        REQUIRE(instance.at(2) == 9);
        REQUIRE(instance.size() == 6);
        list instance_2 = {10, 11, 12, 13, 14, 15};
        auto const_iter_2 = instance.cbegin();
        for(size_t i = 0; i < 5; i++){
            instance.insert(const_iter_2,instance.at(i));
        }
        REQUIRE(!instance.empty());
        REQUIRE(instance.size() == 11);
    }

    SECTION("Test clear"){
        list instance;
        instance.clear();
        REQUIRE(instance.size() == 0);
        REQUIRE(instance.capacity() == 0);
        for(size_t i = 0; i < 1000; i++){
            instance.push_back(i);
        }
        REQUIRE(instance.size() == 1000);
        instance.clear();
        REQUIRE(instance.size() == 0);
    }

    SECTION("Test erase"){
        list instance;
        for(size_t i = 0; i < 10; i++){
            instance.push_back(i);
        }
        REQUIRE(instance.size() == 10);
        list::iterator iter_beg = instance.begin();
        iter_beg++;
        instance.erase(instance.begin(), iter_beg);
        REQUIRE(instance.size() == 9);
        for(size_t i = 0; i < instance.size(); i++){
            REQUIRE(instance.at(i) == i );
        }
    }
}

TEST_CASE("Test Iterators", "[stl-algorithm-arraylist]"){
    using list  = a_list::arraylist<int>;
    list instance = {1, 2, 3, 4, 5, 6};
    REQUIRE(*instance.begin() == 1);
    REQUIRE(*instance.cbegin() == 1);
    REQUIRE(*instance.rbegin() == 6);
    REQUIRE(*(instance.crbegin()) == 6);
    REQUIRE(*(--instance.end()) == 6);
    REQUIRE(*(--instance.cend()) == 6);
    REQUIRE(*(--instance.rend()) == 1);
    REQUIRE(*(--instance.crend()) == 1);
}
