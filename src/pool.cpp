#include "pool.h"
#include <set>
#include <iterator>
#include <algorithm>
#include <utility>
#include <iostream>
#include <assert.h>

Pool::Pool()
    :samples(),levels(),next(),factor(),idx_splitter(),info_gain()
{

}

Pool::Pool(const MyMap &mapInit, const std::string &fac, int split,int gain)
    :samples(mapInit),next(),factor(fac),idx_splitter(split),info_gain(gain)
{
    std::set<std::string> uniq;

    std::transform(samples.begin(), samples.end(),
        std::inserter(uniq, uniq.end()),
        [](std::pair<int,std::string> pair){ return pair.second; });

    levels.assign(uniq.begin(),uniq.end());
}

Pool::Pool(const std::vector<int>& idxs,const std::vector<std::string>& labs, const std::string& fac,int split,int gain)
{
    if(idxs.size()!=labs.size())
        throw std::out_of_range("Indexes and labels must have tha same size");

    std::transform( idxs.begin(), idxs.end(), labs.begin(),
           std::inserter(samples, samples.end() ),[](int a,const std::string& b)
                                                    {return std::make_pair(a,b);} );

    std::set<std::string> uniq(labs.begin(),labs.end());

    levels.assign(uniq.begin(),uniq.end());

    factor = fac;
    idx_splitter=split;
    info_gain = gain;
}

Pool::Pool(const Pool &other)
    :samples(other.samples),levels(other.levels),
     factor(other.factor),idx_splitter(other.idx_splitter),info_gain(other.info_gain)
{
    copyNodes(next,other.next);
}

Pool& Pool::operator=(const Pool& other)
{
    if(this != &other)
    {
        samples = other.samples;
        levels = other.levels;
        factor = other.factor;
        idx_splitter = other.idx_splitter;
        info_gain = other.info_gain;
        copyNodes(next,other.next);
    }
    return *this;
}

Pool::Pool(Pool&& other) noexcept
    :samples(std::move(other.samples)),levels(std::move(levels)),
             next(std::move(other.next)),factor(std::move(factor)),idx_splitter(other.idx_splitter),info_gain(other.info_gain)
{

}

Pool& Pool::operator=(Pool&& other) noexcept
{
    assert(this != &other);

    samples = std::move(other.samples);
    levels = std::move(other.levels);
    next = std::move(other.next);
    factor = std::move(other.factor);
    idx_splitter = other.idx_splitter;
    info_gain = other.info_gain;

    return *this;
}

void Pool::add_sample(std::pair<int,std::string>)
{
    //ignore for the moment
}

void Pool::remove_sample(int idx)
{
    //ignore for the moment
}

void Pool::setFactor(const std::string &fac)
{
    factor = fac;
}

void Pool::setVarIdx(int var)
{
    idx_splitter = var;
}

void Pool::setInfoGain(double gain)
{
    info_gain = gain;
}

void Pool::add_node(const Pool& newPool)
{
    next.push_back(std::make_shared<Pool>(newPool));
}

void Pool::add_node(Pool&& newPool)
{
    next.push_back(std::make_shared<Pool>(std::move(newPool)));
}

Pool& Pool::getNext(int i)
{
    if(i>=next.size())
        throw std::out_of_range("i must be less than the number of pools pointed!");
    return *(next[i]);
}

int Pool::sampleSize() const
{
    return samples.size();
}

int Pool::levelSize() const
{
    return levels.size();
}
const std::string& Pool::getLevel(int n) const
{
    if(n<levels.size())
        return levels[n];
    else
        throw std::out_of_range("n must be less than the number of levels!");
}

std::vector<int> Pool::allIdxs() const
{
    std::vector<int> res(sampleSize());

    transform(samples.begin(),samples.end(),res.begin(),[](std::pair<int,std::string> a){return a.first;});

    return res;
}

std::vector<std::string> Pool::labsFromIdx(const std::vector<int>& indexes) const
{
    std::vector<std::string> res(indexes.size());
    for(int i=0;i<indexes.size();i++)
        res[i] = samples.at(indexes[i]);

    return res;
}

std::vector<int> Pool::idxs(int facNumb) const
{
    std::vector<int> indexes;

    if(facNumb<levels.size())
    {
        indexes.reserve(samples.size());
        const std::string& toFind = levels[facNumb];
        for(auto i=samples.begin();i!=samples.end();i++)
            if(toFind==i->second)
                indexes.push_back(i->first);
    }
    else
        throw std::out_of_range("n must be less than the number of levels!");

    return indexes;
}

std::ostream& operator<<(std::ostream& ostr,const Pool& pool)
{
    for(const auto& i: pool.samples)
    {
        ostr << i.first << " " << i.second << std::endl;

        ostr << std::endl;
    }

    for(int i=0;i<pool.next.size();i++)
    {
        ostr << "Next[" << i << "]: " << std::endl;
        ostr << *pool.next[i];
    }
    return ostr;
}

void Pool::copyNodes(NodeContainerType& to,const NodeContainerType& from)
{
    to.resize(from.size());

    for(int i=0;i<to.size();i++)
        to[i] = std::make_shared<Pool>(*(from[i]));  //here it calls recursevily the copy-ctor(and copyNodes)
}
