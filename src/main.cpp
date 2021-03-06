#include <iostream>
#include <vector>
#include <typeinfo>

#include "continuousdescriptor.h"
#include "categoricaldescriptor.h"
#include "pool.h"
#include "decisiontree.h"

int main()
{
 /*   CategoricalDescriptor catA = std::vector<std::string>({"cose","da","fare"});
    ContinuousDescriptor conA = std::vector<double>({1,4,2.3,6.3,2});

    std::shared_ptr<AbstractDescriptor> n = conA.clone();

    std::cout << conA << std::endl;

   const auto& vec = conA.toCategorical(3);

    for(const auto& i : vec)
        std::cout<< i.getLevel(1);

    Pool p(std::vector<int>{3,2,5,4},std::vector<std::string>{"a","b","c","e"});

    Pool p2(std::vector<int>{2,3,8},std::vector<std::string>{"b","b","e"});

    Pool p3(std::vector<int>{1,2,5},std::vector<std::string>{"a","c","b"});

    p2.add_node(p3);

    p.add_node(p2);
    p.add_node(p3);

    std::cout << p;*/

    CategoricalDescriptor pat({"Some","Full","Some","Full","Full","Some","None","Some","Full","Full","None","Full"});
    CategoricalDescriptor type({"French","Thai","Burger","Thai","French","Italian","Burger","Thai","Burger","Italian","Thai","Burger"});
    CategoricalDescriptor labs({"T","F","T","T","F","T","F","T","F","F","F","T"});

    DecisionTree::AbstractMatType mat;

    mat.push_back(std::make_shared<CategoricalDescriptor>(pat));
    mat.push_back(std::make_shared<CategoricalDescriptor>(type));

    DecisionTree tree(mat,labs);

    auto compMat = tree.getComputationMatrix();
    auto oriMat = tree.getOriginalMatrix();
    for(const auto& i : oriMat)
        std::cout << i << std::endl;

    return 0;
}

