#include <iostream>
#include <type_traits>
#include <cstring>
#include <string>

template<typename T>
concept bool POD()
{
    return std::is_pod<std::remove_reference_t<T>>::value;  
}

template<typename T>
concept bool nonPOD()
{
    return !std::is_pod<std::remove_reference_t<T>>::value;
}

template<class InputIt, class OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt d_first) requires POD<decltype(*first)>() {
    std::cout << "POD copy\n";
    auto n_bytes = sizeof(decltype(*first)) * std::distance(first, last);
    return reinterpret_cast<OutputIt>(std::memmove(reinterpret_cast<void*>(d_first),
                        reinterpret_cast<void*>(first),
                        n_bytes));
}

template<class InputIt, class OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt d_first) requires nonPOD<decltype(*first)>() {
    std::cout << "nonPOD copy\n";
    while (first != last) {
        *d_first++ = *first++;
    }
    return d_first;
}


int main()
{
    int src[] = {1, 2, 3, 4};
    constexpr auto n = sizeof(src)/sizeof(src[0]);
    int dst[n];

    std::cout << POD<int>() << '\n';

    copy(src, src + n, dst);
    for (unsigned i = 0; i < n; ++i) {
        std::cout << dst[i] << " ";
    }
    std::cout << "\n";

    std::string src_s[] = {"one", "two", "three"};
    constexpr auto n_s = sizeof(src_s)/sizeof(src_s[0]);
    std::string dst_s[n_s];
    
    std::cout << POD<std::string>() << '\n';
    std::cout << std::is_pod<std::string>::value << '\n';

    copy(src_s, src_s + n_s, dst_s);
    for (unsigned i = 0; i < n_s; ++i) {
        std::cout << dst_s[i] << " ";
    }
    std::cout << "\n";    
    /* code */
    return 0;
}