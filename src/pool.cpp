#include "pool.h"
#include <set>
#include <iterator>
#include <algorithm>
#include <utility>
#include <assert.h>

Pool::Pool()
    :samples(),levels(),next(),factor(),idx_splitter()
{

}

Pool::Pool(const MyMap &mapInit, const std::string &fac, int split)
    :samples(mapInit),next(),factor(fac),idx_splitter(split)
{
    std::set<std::string> uniq;

    std::transform(samples.begin(), samples.end(),
        std::inserter(uniq, uniq.end()),
        [](std::pair<int,std::string> pair){ return pair.second; });

    levels.assign(uniq.begin(),uniq.end());
}

Pool::Pool(const std::vector<int>& idxs,const std::vector<std::string>& labs, const std::string& fac,int split)
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
}

Pool::Pool(const Pool &other)
    :samples(other.samples),levels(other.levels),
     next(other.next),factor(other.factor),idx_splitter(other.idx_splitter)
{

}

Pool& Pool::operator=(const Pool& other)
{
    if(this != &other)
    {
        samples = other.samples;
        levels = other.levels;
        factor = other.factor;
        idx_splitter = other.idx_splitter;
        next = next;
    }
    return *this;
}

Pool::Pool(Pool&& other) noexcept
    :samples(std::move(other.samples)),levels(std::move(levels)),
             next(std::move(other.next)),factor(std::move(factor)),idx_splitter(other.idx_splitter)
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
