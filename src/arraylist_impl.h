#ifndef ARRAYLIST_IMPL_H
#define ARRAYLIST_IMPL_H

#include <memory>
#include <cstring>
#include <utility>
#include <cassert>

namespace a_list{
    template<typename T, typename alloc>
    class arraylist_impl : public alloc{
        private:
            using value_type  = T;
            using alloc_traits = std::allocator_traits<alloc>;
            using storage_type = value_type*;

        public:
            explicit arraylist_impl(const alloc& a = alloc()):
                alloc{a}, c_size{0}, c_capacity(0), storage(nullptr)
                {}
            arraylist_impl(const arraylist_impl& other) :
                alloc(other), c_size(other.c_size){

                }
            arraylist_impl(arraylist_impl&& other):
            alloc(other), c_size(other.c_size){

            }
            arraylist_impl& operator=(const arraylist_impl& other){
                return *this;
            }

            arraylist_impl& operator=(arraylist_impl&& other){
                return *this;
            }

            ~arraylist_impl(){
                erase(0, c_size );
                this->deallocate(storage, c_capacity);
            }

            size_t erase(size_t first, size_t last){
                for(size_t i = first; i < last; i++){
                    alloc_traits::destroy(*this, storage + i);
                }
                size_t cleared_range = last - first;
                c_size -= cleared_range;
                return cleared_range;
            }

            size_t insert(size_t pos, value_type ele){
                if(c_size  >= c_capacity){
                    realloc_util(c_capacity >= 8 ? c_capacity * 2 : 8); 
                }
                if(pos < c_size){
                    shift_ele_right(pos);
                }
                alloc_traits::construct(*this, storage + pos, std::forward<value_type>(ele));
                c_size++;
                return pos;
            }

            size_t find(value_type value){
                for(int i = 0; i < c_size; i++){
                    if(value == storage[i]){
                        return i;
                    }
                }
                return -1;
            }

            value_type& at(size_t pos){
                assert(pos < c_size);
                return storage[pos];
            }

            storage_type get_storage() const{
                return storage;
            }

            size_t size() const{
                return c_size;
            }

            size_t capacity() const{
                return c_capacity;
            }


        private:
            size_t c_size, c_capacity;
            storage_type storage;
        private:

            void realloc_util(size_t allocated_num){
                storage_type new_storage = this->allocate(allocated_num);
                if(storage != nullptr){
                    size_t cur_size = c_size;
                    std::memcpy(new_storage, storage, c_size * sizeof(value_type));
                    erase(0, c_size );
                    this->deallocate(storage, c_capacity);
                    c_size = cur_size;
                }
                storage = new_storage;
                c_capacity = allocated_num;
            }
            void shift_ele_right(size_t pos){
                T cur_ele = storage[pos];
                T next_ele;
                for(size_t i = pos; i < c_size; i++){
                    next_ele = storage[i + 1];
                    alloc_traits::construct(*this, storage + i + 1, std::forward<value_type>(cur_ele));
                    cur_ele = next_ele;
                }
            }

            void insert_realloc_util(size_t allocated_num, size_t pos, value_type ele){
                storage_type new_storage_first = this->allocate(allocated_num/2);
                storage_type new_storage_second = this->allocate(allocated_num - allocated_num/2);
                std::memcpy(new_storage_first, storage, pos * sizeof(value_type));
                std::memcpy(new_storage_second, storage + (c_size - pos) * sizeof(value_type), (c_size - pos) * sizeof(value_type));
                storage_type new_storage = this->allocate(allocated_num);
                erase(0, c_size + 1);
                std::memcpy(new_storage, new_storage_first, pos * sizeof(value_type));
                std::memcpy(new_storage + (c_size - pos), new_storage_second, (c_size - pos) * sizeof(value_type));
                this->deallocate(storage, c_capacity);
                storage = new_storage;
                c_capacity += allocated_num;
            }

            

    };
};

#endif