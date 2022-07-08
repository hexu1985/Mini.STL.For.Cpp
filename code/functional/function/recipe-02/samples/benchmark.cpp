#include <iostream>
#include <string>
#include <functional>

using namespace std::placeholders;

bool some_function(const std::string& s) {
    std::cout << s << " This is really neat\n";
    return true;
}

class some_class {
public:
    bool some_function(const std::string& s) {
        std::cout << s << " This is also quite nice\n";
        return true;
    }

    bool other_function() {
        std::cout << "other" << " This is also quite nice\n";
        return true;
    }
};

class some_function_object {
public:
    bool operator()(const std::string& s) {
        std::cout << s << 
            " This should work, too, in a flexible solution\n";
        return true;
    }
};

// a class with data members:
struct MyValue {
  int value;
  int fifth() {return value/5;}
};

int main() {
    std::function<bool (const std::string&)> f1(&some_function);
    f1(std::string("Hello"));

    some_class s;

    std::function<bool (some_class*)> f2(&some_class::other_function);
    f2(&s);

    std::function<bool (const std::string&)> f3(std::bind(&some_class::some_function,&s,_1));
    f3(std::string("Hello"));

    some_function_object fso;
    std::function<bool (const std::string&)> f4(fso);
    f4(std::string("Hello"));

    std::function<bool (some_class&)> f5(&some_class::other_function);
    f5(s);

    // stuff with members:
    std::function<int(MyValue&)> value(&MyValue::value);  // pointer to data member
    std::function<int(MyValue&)> fifth(&MyValue::fifth);  // pointer to member function

    MyValue sixty {60};

    std::cout << "value(sixty): " << value(sixty) << '\n';
    std::cout << "fifth(sixty): " << fifth(sixty) << '\n';

    return 0;
}

