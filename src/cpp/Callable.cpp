#include <iostream>
#include <typeinfo>

struct string_view
{
    char const* data;
    std::size_t size;
};

inline std::ostream& operator<<(std::ostream& o, string_view const& s)
{
    return o.write(s.data, s.size);
}

template<class T>
constexpr string_view get_name()
{
    char const* p = __PRETTY_FUNCTION__;
    while (*p++ != '=');
    for (; *p == ' '; ++p);
    char const* p2 = p;
    int count = 1;
    for (;;++p2)
    {
        switch (*p2)
        {
        case '[':
            ++count;
            break;
        case ']':
            --count;
            if (!count)
                return {p, std::size_t(p2 - p)};
        }
    }
    return {};
}

template<class Func, class... Args>
concept bool Callable = 
    requires(Func&& f, Args... args) {
        {f(args...)};
    };


template<class Func, class... Args>
    requires Callable<Func, Args...>
decltype(auto) log_and_invoke(Func&& f, Args... args) {
    // log function call
    return f(std::forward<Args>(args)...);
}


class Gizmo {
public:
    void operator()() { }
    void operator()(int) { }
};

int foo(int a) { return a + 1; }

void bar(int, int) {}


int main() {
    std::cout << log_and_invoke(foo, 1) << "\n";
    log_and_invoke(Gizmo{}, 1, 2);
    // call(foo);
    // call(bar);
    // Gizmo g;
    // call(g);
    return 0;
}