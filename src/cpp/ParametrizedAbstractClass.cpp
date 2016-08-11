#include <string>
#include <iostream>

using namespace std;

template<typename T>
struct Stringable {
    virtual string to_string(const T&) const = 0;
};

class Person {
public:
    Person(const string& firstname, const string& lastname)
        : firstname_{firstname}
        , lastname_{lastname}
    {}

    string firstname() const { return firstname_; }

    string lastname() const {return lastname_; }

private:
    string firstname_;
    string lastname_;
};

template<typename T> struct StringablePerson;

template<>
struct StringablePerson<Person>: Stringable<Person> {
    string to_string(const Person& p) const override {
        return p.firstname().substr(0, 1) + ". " + p.lastname();
    }
};

StringablePerson<Person> dStringable;

template<typename T>
string bold(const Stringable<T>& dStringable, const T& a) {
    return "<b>" + dStringable.to_string(a) + "</b>";
}

int main() {
    cout << bold(dStringable, Person{"John", "Smith"}) << endl;
    return 0;
}
