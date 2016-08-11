#include <iostream>
#include <string>

// Concept
template<class T> concept bool Stringable = 
    requires(const T& a) {
        {to_string(a)} -> std::string;
    };
// Modelling
class Person {
public:
    template<class T, class U>
    Person(T&& firstname, U&& lastname)
        : firstname_{std::forward<T>(firstname)}
        , lastname_{std::forward<U>(lastname)}
    {}
    //...
    friend std::string to_string(const Person& p) {
        return p.firstname_.substr(0, 1) + ". " + p.lastname_;
    } 

private:
    std::string firstname_;
    std::string lastname_;
};
// Algorithm
std::string bold(Stringable s) {
    return "<b>" + to_string(s) + "</b>";
}

int main()
{
    // Instantiation
    std::cout << bold(Person{"John", "Smith"}) << "\n";
    return 0;
}