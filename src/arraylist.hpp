#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include <limits>
#include <algorithm>
#include <utility>

namespace a_list{
        //constructor
        template<typename T, typename alloc>
        arraylist<T, alloc>::arraylist(const allocator_type&  alloc_): impl(alloc_){

        }
        template<typename T, typename alloc>
        arraylist<T, alloc>::arraylist(std::initializer_list<value_type> init_list, const allocator_type& alloc_):
            impl(alloc_){
                int i = size();
                for (const auto& ele : init_list) {
                    impl.insert(i, ele);
                    i++;
                }
            }

        /*Selectors */
        template<typename T, typename alloc>
        auto arraylist<T, alloc>::size() const noexcept -> size_type{
            return impl.size();
        }
        template<typename T, typename alloc>
        auto arraylist<T, alloc>::max_size() const noexcept -> size_type {
            return std::numeric_limits<size_t>::max();
        }
        template<typename T, typename alloc>
        auto arraylist<T, alloc>::capacity() const noexcept->size_type{
            return impl.capacity();
        }
        template<typename T, typename alloc>
        auto arraylist<T, alloc>::empty() const noexcept -> bool{
            return impl.size() == 0;
        }
        template<typename T, typename alloc>
        auto arraylist<T, alloc>::at(size_type n) -> reference{
            return impl.at(n);
        }
        template<typename T, typename alloc>
        auto arraylist<T, alloc>::at(size_type n) const -> const_reference{
            return impl.at(n);
        }

        /*Mutators */
        template<typename T, typename alloc>
        auto arraylist<T, alloc>::insert(const_iterator position, const value_type& val) -> iterator{
            size_t dis = std::distance(cbegin(), position);
            impl.insert(dis, val);
            return position;
        }

        template<typename T, typename alloc>
        template<typename InputIterator>
        auto arraylist<T, alloc>::insert(const const_iterator position, InputIterator first, InputIterator second) -> iterator{

        }

        template<typename T, typename alloc>
        auto arraylist<T, alloc>::operator[](size_type n) -> reference{
            return impl.at(n);
        }

        template<typename T, typename alloc>
        void arraylist<T, alloc>::clear() noexcept{
            impl.erase(0, size() );
        }
        template<typename T, typename alloc>
        auto arraylist<T, alloc>::erase(const_iterator first, const_iterator last) -> iterator{
            size_t initial_ = std::distance(begin(), first);
            size_t end_ = std::distance(begin(), last);
            impl.erase(initial_, end_);
            return last;
        }
        template<typename T, typename alloc>
        void arraylist<T, alloc>::push_back(value_type value){
            impl.insert(size(), value);
        }

        /*Iterators */
        template<typename T, typename alloc>
        auto arraylist<T, alloc>::begin() noexcept -> iterator{
            T* beg_pointer = impl.get_storage();
            return iterator(beg_pointer);
        }
        template<typename T, typename alloc>
        auto arraylist<T, alloc>::end() noexcept -> iterator{
            T* beg_pointer = impl.get_storage();
            T* end_pointer = beg_pointer + size();
            return iterator(end_pointer);
        }
        template<typename T, typename alloc>
        auto arraylist<T, alloc>::cbegin() const -> const_iterator{
            T* beg_pointer = impl.get_storage();
            auto begin_iterator = iterator(beg_pointer);
            return const_iterator(begin_iterator);
        }
        template<typename T, typename alloc>
        auto arraylist<T, alloc>::cend() const -> const_iterator{
            T* beg_pointer = impl.get_storage();
            T* end_pointer = beg_pointer + size();
            auto end_iterator = iterator(end_pointer);
            return const_iterator(end_iterator);
        }
        template<typename T, typename alloc>
        auto arraylist<T, alloc>::rbegin() -> reverse_iterator{
            return std::make_reverse_iterator(end());
        }
        template<typename T, typename alloc>
        auto arraylist<T, alloc>::rend() -> reverse_iterator{
            return std::make_reverse_iterator(begin());
        }
        template<typename T, typename alloc>
        auto arraylist<T, alloc>::crbegin() const -> const_reverse_iterator{
            return rbegin();
        }
        template<typename T, typename alloc>
        auto arraylist<T, alloc>::crend() const -> const_reverse_iterator{
            return rend();
        }

        /*Allocator */
        template<typename T, typename alloc>
        auto arraylist<T, alloc>::get_allocator() const noexcept -> allocator_type{
            return static_cast<allocator_type>(impl);
        }

        /*Non member functions */
        template<typename T, typename alloc>
        bool operator==(const arraylist<T, alloc>& lhs, const arraylist<T, alloc>& rhs){
            auto mismatch_comp = std::mismatch(lhs.cbegin(), lhs.cend(), rhs.cbegin(), 
                [](const typename arraylist<T, alloc>::value_type lhs,  const typename arraylist<T, alloc>::value_type rhs){
                    return lhs == rhs;
                });
            return mismatch_comp.first == lhs.cend() && mismatch_comp.second == rhs.cend();
        }
        
        template<typename T, typename alloc>
        bool operator!=(const arraylist<T, alloc>& lhs, const arraylist<T, alloc>& rhs){
           return !(lhs == rhs);
        }
        
        template<typename T, typename alloc>
        bool operator<(const arraylist<T, alloc>& lhs, const arraylist<T, alloc>& rhs){
            auto mismatch_comp = std::mismatch(lhs.cbegin(), lhs.cend(), rhs.cbegin(), 
                [](const typename arraylist<T, alloc>::value_type lhs,  const typename arraylist<T, alloc>::value_type rhs){
                    return lhs < rhs;
                });
            return mismatch_comp.first == lhs.cend() && mismatch_comp.second == rhs.cend();
        }
        
        template<typename T, typename alloc>
        bool operator<=(const arraylist<T, alloc>& lhs, const arraylist<T, alloc>& rhs){
            return !(lhs > rhs);
        }
        
        template<typename T, typename alloc>
        bool operator>(const arraylist<T, alloc>& lhs, const arraylist<T, alloc>& rhs){
            auto mismatch_comp = std::mismatch(lhs.cbegin(), lhs.cend(), rhs.cbegin(), 
                [](const typename arraylist<T, alloc>::value_type lhs,  const typename arraylist<T, alloc>::value_type rhs){
                    return lhs > rhs;
                });
            return mismatch_comp.first == lhs.cend() && mismatch_comp.second == rhs.cend();
        }
        
        template<typename T, typename alloc>
        bool operator>=(const arraylist<T, alloc>& lhs, const arraylist<T, alloc>& rhs){
            return !(lhs < rhs);
        }
};

#endif