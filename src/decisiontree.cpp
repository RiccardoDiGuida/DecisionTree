#include "decisiontree.h"
#include "assert.h"

DecisionTree::DecisionTree(const AbstractMatType& mat,const CategoricalDescriptor& resp)
{

}

DecisionTree::DecisionTree(const DecisionTree& other)
    :matComp(other.matComp),response(other.response),
      firstPool(other.firstPool),idxsRelations(other.idxsRelations)
{
    matOri.resize(other.matOri.size());

    for(int i=0;i<matOri.size();i++)
        matOri[i] = other.matOri[i]->clone();
}

DecisionTree& DecisionTree::operator=(const DecisionTree& other)
{
    if(&other != this)
    {
        matComp = other.matComp;
        response = other.response;
        firstPool = other.firstPool;
        idxsRelations = other.idxsRelations;

        matOri.resize(other.matOri.size());

        for(int i=0;i<matOri.size();i++)
            matOri[i] = other.matOri[i]->clone();
    }

    return *this;
}

DecisionTree::DecisionTree(DecisionTree&& other) noexcept
    :matComp(std::move(other.matComp)),response(std::move(other.response)),
      firstPool(std::move(other.firstPool)),idxsRelations(std::move(other.idxsRelations)),
      matOri(std::move(other.matOri))
{

}

DecisionTree& DecisionTree::operator=(DecisionTree&& other) noexcept
{
    assert(this != &other);

    matComp = std::move(other.matComp);
    response = std::move(other.response);
    firstPool = std::move(other.firstPool);
    idxsRelations = std::move(other.idxsRelations);
    matOri = std::move(other.matOri);

    return *this;
}

DecisionTree::AbstractMatType DecisionTree::getOriginalMatrix()
{
    AbstractMatType mat(matOri.size());

    for(int i=0;i<matOri.size();i++)
        mat[i] = matOri[i]->clone();

    return mat;
}

std::vector<CategoricalDescriptor> DecisionTree::getComputationMatrix()
{
    return std::vector<CategoricalDescriptor>(matComp);
}

CategoricalDescriptor DecisionTree::getResponse()
{
    return CategoricalDescriptor(response);
}

void DecisionTree::computeTree()
{

}
