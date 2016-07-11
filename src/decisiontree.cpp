#include "decisiontree.h"

DecisionTree::DecisionTree(const AbstractMatType& mat,const CategoricalDescriptor& resp)
{

}

DecisionTree::DecisionTree(const DecisionTree& other)
    :matComp(other.matComp),response(other.response),
      firstPool(other.firstPool),idxsRelations(other.idxsRelations)
{
    matOri.resize(other.matOri.size());

  /*  for(int i=0;i<matOri.size();i++)
    {
        matOri[i] = std::make_shared<
    }   */
}

DecisionTree& DecisionTree::operator=(const DecisionTree& other)
{

}

DecisionTree::DecisionTree(DecisionTree&& other) noexcept
{

}

DecisionTree& DecisionTree::operator=(DecisionTree&& other) noexcept
{

}

DecisionTree::AbstractMatType DecisionTree::getOriginalMatrix()
{

}

std::vector<CategoricalDescriptor> DecisionTree::getComputationMatrix()
{

}

CategoricalDescriptor DecisionTree::getResponse()
{

}

void DecisionTree::computeTree()
{

}
