#pragma once

template <typename ...Types>
struct type_list
{
    template <template <typename...> typename Holder>
    using apply = Holder<Types...>;
    
    template <typename Type>
    using push_front = type_list<Type, Types...>;
    
    template <typename Type>
    using push_back = type_list<Types..., Type>;
};
