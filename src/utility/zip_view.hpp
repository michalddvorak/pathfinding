#pragma once

#include <ranges>
#include <utility>

template <std::ranges::input_range Range1, std::ranges::input_range Range2>
class zip_view
{
  
  public:
    
    class iterator
    {
      private:
        using iterator1_t = std::ranges::iterator_t<Range1>;
        using iterator2_t = std::ranges::iterator_t<Range2>;
        using value1_t = std::ranges::range_value_t<Range1>;
        using value2_t = std::ranges::range_value_t<Range2>;
        iterator1_t it1;
        iterator2_t it2;
      
      public:
        iterator(iterator1_t it1, iterator2_t it2) : it1(it1), it2(it2) { }
        
        auto operator*() const
        {
            return std::tie(*it1, *it2);
        }
        
        auto operator*()
        {
            return std::tie(*it1, *it2);
        }
        
        iterator& operator++()
        {
            ++it1;
            ++it2;
            return *this;
        }
        bool operator!=(const iterator& other) const
        {
            //note that this assures that the zip iterates ove min(size(range1), size(range2)) elements
            return it1 != other.it1 && it2 != other.it2;
        }
    };
    
    zip_view(Range1& range1, Range2& range2) : range1_(range1), range2_(range2) { }
    
    iterator begin()
    {
        return iterator(std::ranges::begin(range1_), std::ranges::begin(range2_));
    }
    
    iterator end()
    {
        return iterator(std::ranges::end(range1_), std::ranges::end(range2_));
    }
  
  private:
    Range1& range1_;
    Range2& range2_;
};