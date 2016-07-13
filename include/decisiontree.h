#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include "continuousdescriptor.h"
#include "pool.h"

class DecisionTree
{
public:
    typedef std::vector<std::shared_ptr<AbstractDescriptor>> AbstractMatType;

    DecisionTree() = delete;
    DecisionTree(const AbstractMatType& mat,const CategoricalDescriptor& resp);
    DecisionTree(const DecisionTree& other);
    DecisionTree& operator=(const DecisionTree& other);
    DecisionTree(DecisionTree&& other) noexcept;
    DecisionTree& operator=(DecisionTree&& other) noexcept;

    AbstractMatType getOriginalMatrix();
    std::vector<CategoricalDescriptor> getComputationMatrix();
    CategoricalDescriptor getResponse();

private:
    void computeTree(Pool& pool);
    double entropy(const std::vector<int>& partitions, int total);
    double infoGain(const CategoricalDescriptor& desc,const Pool& currPool);


    AbstractMatType matOri;
    std::vector<CategoricalDescriptor> matComp;
    std::map<int,int> idxsRelations;
    CategoricalDescriptor response;
    Pool firstPool;
};

#endif // DECISIONTREE_H
