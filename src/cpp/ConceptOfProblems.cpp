#include <set>
#include <memory>
#include <string>

template<typename T>
concept bool
LessComparable()
{
  return requires (T a, T b)
  {
    { a < b } -> bool;
  };
}


template<LessComparable Key>
class set: public std::set<Key> {
public:
    using std::set<Key>::set;
};

class Problem {
public:
    // ...
};

int main() {
    set<Problem> to_do;

    to_do.insert(Problem());

    return 0;
}
