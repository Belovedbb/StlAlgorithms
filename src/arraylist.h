#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <memory>
#include <initializer_list>
#include "arraylist_impl.h"
#include "arraylist_iterator.h"

using std::allocator;
using std::allocator_traits;

namespace a_list{

template<typename T, typename alloc = allocator<T>>
class arraylist{
    public:
        using value_type = T;
        using allocator_type = alloc;
        using reference = value_type&;
        using const_reference =const value_type&;
        using pointer = typename allocator_traits<allocator_type>::pointer;
        using const_pointer = typename allocator_traits<allocator_type>::const_pointer;
        using iterator = arraylist_iterator<T>;
        using const_iterator = arraylist_const_iterator<T>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
    private: 
        using self = arraylist<T, alloc>;
    public:
        //copy and move constructor
        arraylist(const arraylist&) = default;
        arraylist(arraylist&&) = default;
        //constructor
        explicit arraylist(const allocator_type& alloc_ = allocator_type());
        arraylist(std::initializer_list<value_type> init_list, const allocator_type& alloc_ = allocator_type());
        template<typename FwdIter>
        arraylist(FwdIter first, FwdIter last, const allocator_type& = allocator_type());
        //
        arraylist& operator=(const arraylist&) = default;
        arraylist& operator=(arraylist&&) = default;

        ~arraylist() = default;

        /*Selectors */
        size_type size() const noexcept;
        size_type max_size() const noexcept;
        size_type capacity() const noexcept;
        bool empty() const noexcept;
        reference at(size_type n);
        const_reference at(size_type n) const;
        reference operator[](size_type n);

        /*Mutators */
        iterator insert(const_iterator position, const value_type& val);
        template<typename InputIterator>
        iterator insert(const const_iterator position, InputIterator first, InputIterator second);
        void clear() noexcept;
        iterator erase(const_iterator first, const_iterator last);
        iterator erase(iterator first, iterator last);
        void push_back(value_type value);

        /*Iterators */
        iterator begin() noexcept;
        iterator end() noexcept;
        const_iterator cbegin() const;
        const_iterator cend() const;
        reverse_iterator rbegin();
        reverse_iterator rend();
        const_reverse_iterator crbegin() const;
        const_reverse_iterator crend() const;

        /*Allocator */
        allocator_type get_allocator() const noexcept;

        /*Non member functions */
        template<typename TT, typename allocator>
        friend bool operator==(const arraylist<TT, allocator>& lhs, const arraylist<TT, allocator>& rhs);
        
        template<typename TT, typename allocator>
        friend bool operator!=(const arraylist<TT, allocator>& lhs, const arraylist<TT, allocator>& rhs);
        
        template<typename TT, typename allocator>
        friend bool operator<(const arraylist<TT, allocator>& lhs, const arraylist<TT, allocator>& rhs);
        
        template<typename TT, typename allocator>
        friend bool operator<=(const arraylist<TT, allocator>& lhs, const arraylist<TT, allocator>& rhs);
        
        template<typename TT, typename allocator>
        friend bool operator>(const arraylist<TT, allocator>& lhs, const arraylist<TT, allocator>& rhs);
        
        template<typename TT, typename allocator>
        friend bool operator>=(const arraylist<TT, allocator>& lhs, const arraylist<TT, allocator>& rhs);
        
    private:
        using impl_type =  arraylist_impl<T, allocator_type>;
    private:
        impl_type impl;

};

};

#include "arraylist.hpp"

#endif