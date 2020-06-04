#ifndef ARRAYLIST_ITERATOR_H
#define ARRAYLIST_ITERATOR_H

#include <iterator>
#include <memory>

namespace a_list{

    template<typename T, typename alloc>
    class arraylist;

    template<typename T, typename alloc>
    class arraylist_impl;

    template<typename T>
    class arraylist_const_iterator;

    template<typename T>
    class arraylist_iterator;

    template<typename T>
    class arraylist_iterator{
        private:
        using self = arraylist_iterator<T>;
        using alloc = std::allocator<T>;
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using reference = T&;
            using pointer = T*;
        public:
            explicit arraylist_iterator(pointer impl_p):
                storage(impl_p) {};
            arraylist_iterator(const arraylist_iterator& other) :
                storage(other.storage)
                {}

            arraylist_iterator(const arraylist_const_iterator<T>& const_iter): 
                storage(const_iter.storage){}
            
        
            arraylist_iterator& operator=(const arraylist_iterator& other){
                if(other == *this){
                    return *this;
                }
                storage = other.storage;
                return *this;
            }

            reference operator*() const{
                return *storage;
            }

            pointer operator->() const{
                return storage;
            }

            self& operator++(){
                storage++;
                return *this;
            }

            self& operator++(int){
                ++(*this);
                return *this;
            }

            self& operator--(){
                storage--;
                return *this;
            }

            self& operator--(int){
                --(*this);
                return *this;
            }

            bool operator==(const self& other) const {
                return this->storage == other.storage;
            }

            bool operator!=(const self& other) const {
                return this->storage != other.storage;
            }


        private:
            pointer storage;

            template<typename U, typename alloc_>
            friend class arraylist;

            template<typename UU>
            friend class arraylist_const_iterator;
    };

    template<typename T>
    class arraylist_const_iterator{
        private:
        using self = arraylist_const_iterator<T>;
        using alloc = std::allocator<T>;
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using reference = T&;
            using pointer = T*;
        public:
            explicit arraylist_const_iterator(const pointer impl_p):
                storage(impl_p) {};
            
            explicit arraylist_const_iterator(const arraylist_iterator<value_type> iterator_c):
                storage(iterator_c.storage) {};

            arraylist_const_iterator(const arraylist_const_iterator& other_const):
                storage(other_const.storage){
                    
                }
                
            arraylist_const_iterator& operator=(const arraylist_const_iterator& other){
               if(other == *this){
                    return *this;
                }
                other.storage = storage;
                return *this;
            }

            reference operator*() const{
                return *storage;
            }

            pointer operator->() const{
                return storage;
            }

            self& operator++(){
                storage++;
                return *this;
            }

            self& operator++(int){
                ++(*this);
                return *this;
            }

            self& operator--(){
                storage--;
                return *this;
            }

            self& operator--(int){
                --(*this);
                return *this;
            }

            bool operator==(const self& other) const {
                return this->storage == other.storage;
            }

            bool operator!=(const self& other) const {
                return this->storage != other.storage;
            }


        private:
            pointer storage;

            template<typename U, typename alloc_>
            friend class arraylist;

            template<typename UU>
            friend class arraylist_iterator;
    };

};

#endif