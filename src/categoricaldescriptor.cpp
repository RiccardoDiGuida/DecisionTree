#include "categoricaldescriptor.h"
#include <set>
#include <stdexcept>
#include <assert.h>

CategoricalDescriptor::CategoricalDescriptor()
    : data(), levels(), used(false)
{

}

CategoricalDescriptor::~CategoricalDescriptor()
{

}

CategoricalDescriptor::CategoricalDescriptor(const std::vector<std::string>& vec)
    : data(vec)
{
    std::set<std::string> uniq(vec.begin(),vec.end());
    levels.assign(uniq.begin(),uniq.end());

    used=false;
}

CategoricalDescriptor::CategoricalDescriptor(const std::vector<std::string>&& vec)
    : data(std::move(vec))
{
    std::set<std::string> uniq(data.begin(),data.end());
    levels.assign(uniq.begin(),uniq.end());

    used=false;
}

CategoricalDescriptor::CategoricalDescriptor(const CategoricalDescriptor& other)
    : data(other.data),levels(other.levels),used(other.used)
{

}

CategoricalDescriptor& CategoricalDescriptor::operator=(const CategoricalDescriptor& other)
{
    if(this != &other)
    {
        data = other.data;
        levels = other.levels;
        used = other.used;
    }
    return *this;
}

CategoricalDescriptor::CategoricalDescriptor(CategoricalDescriptor&& other) noexcept
    : data(std::move(other.data)), levels(std::move(other.levels)), used(other.used)
{
    std::cout<<"Move";
}

CategoricalDescriptor& CategoricalDescriptor::operator=(CategoricalDescriptor&& other) noexcept
{
    assert(this != &other);

    data = std::move(other.data);
    levels = std::move(other.levels);
    used = other.used;

    return *this;
}

CategoricalDescriptor::Ptr CategoricalDescriptor::create() const
{
    return Ptr(new CategoricalDescriptor());
}

CategoricalDescriptor::Ptr CategoricalDescriptor::clone() const
{
    return Ptr(new CategoricalDescriptor(*this));
}

bool CategoricalDescriptor::isConvertible() const
{
    return false;
}

const std::string& CategoricalDescriptor::getLevel(int n) const
{
    if(n<levels.size())
        return levels[n];
    else
        throw std::out_of_range("n must be less than the number of levels!");
}

std::vector<int> CategoricalDescriptor::idxs(int facNumb) const
{
    std::vector<int> indexes;

    if(facNumb<levels.size())
    {
        indexes.reserve(data.size());
        const std::string& sample = levels[facNumb];
        for(int i=0;i<data.size();i++)
            if(sample==data[i])
                indexes.push_back(i);
    }
    else
        throw std::out_of_range("n must be less than the number of levels!");

    return indexes;
}

void CategoricalDescriptor::toggleUsed()
{
    used = !used;
}

bool CategoricalDescriptor::isUsed()
{
    return used;
}

int CategoricalDescriptor::dataSize() const
{
    return data.size();
}

int CategoricalDescriptor::levelSize() const
{
    return levels.size();
}

std::ostream& operator<<(std::ostream& ostr,const CategoricalDescriptor& descr)
{
    for(const auto& i: descr.data)
        ostr << i << " ";
    return ostr;
}
