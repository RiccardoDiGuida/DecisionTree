#include <iostream>
#include <vector>

#include "continuousdescriptor.h"
#include "categoricaldescriptor.h"

int main()
{
  //  CategoricalDescriptor catA = std::vector<std::string>({"cose","da","fare"});
    ContinuousDescriptor conA = std::vector<double>({1,4,2.3,6.3,2});

    const auto& vec = conA.toCategorical(3);

    for(const auto& i : vec)
        std::cout<< i.getLevel(0);

    return 0;
}

