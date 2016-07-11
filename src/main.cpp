#include <iostream>
#include <vector>

#include "continuousdescriptor.h"
#include "categoricaldescriptor.h"
#include "pool.h"

int main()
{
    CategoricalDescriptor catA = std::vector<std::string>({"cose","da","fare"});
    ContinuousDescriptor conA = std::vector<double>({1,4,2.3,6.3,2});

    const auto& vec = conA.toCategorical(3);

    for(const auto& i : vec)
        std::cout<< i.getLevel(1);

  /*  Pool p(std::vector<int>{3,2,5,4},std::vector<std::string>{"a","b","c","e"});

    Pool p2(std::vector<int>{2,3,8},std::vector<std::string>{"b","b","e"});

    Pool p3(std::vector<int>{1,2,5},std::vector<std::string>{"a","c","b"});

    p2.add_node(p3);

    p.add_node(p2);
    p.add_node(p3);

    std::cout << p;*/

    return 0;
}

