#include "continuousdescriptor.h"
#include <stdexcept>
#include <string>
#include <algorithm>
#include <sstream>
#include <assert.h>

ContinuousDescriptor::ContinuousDescriptor()
    : data()
{

}

ContinuousDescriptor::~ContinuousDescriptor()
{

}

ContinuousDescriptor::ContinuousDescriptor(const std::vector<double>& vec)
    : data(vec)
{

}

ContinuousDescriptor::ContinuousDescriptor(const ContinuousDescriptor& other)
    : data(other.data)
{

}

ContinuousDescriptor& ContinuousDescriptor::operator=(const ContinuousDescriptor& other)
{
    if(this != &other)
        data = other.data;

    return *this;
}

ContinuousDescriptor::ContinuousDescriptor(ContinuousDescriptor&& other) noexcept
    : data(std::move(other.data))
{

}

ContinuousDescriptor& ContinuousDescriptor::operator=(ContinuousDescriptor&& other) noexcept
{
    assert(this != &other);

    data = std::move(other.data);

    return *this;
}

ContinuousDescriptor::Ptr ContinuousDescriptor::create() const
{
    return Ptr(new ContinuousDescriptor());
}

ContinuousDescriptor::Ptr ContinuousDescriptor::clone() const
{
    return Ptr(new ContinuousDescriptor(*this));
}

std::vector<CategoricalDescriptor>  ContinuousDescriptor::toCategorical(int groups)
{
    // Divides the range into equal parts and treats each segment as a separate categorical variable
    // May not work well when the variable does not have a normal distribution
    if(groups<2)
        throw std::invalid_argument("groups must be at least 2");

    double min = *(std::min_element(data.cbegin(),data.cend()));
    double max = *(std::max_element(data.cbegin(),data.cend()));

    double segment = (max-min)/groups;

    std::vector<CategoricalDescriptor> result(groups-1);

    for(int i=0;i<groups-1;i++)
    {
        double threshold = min+segment*(i+1);
        std::vector<std::string> newVar;   // vector to allocate every categoricalVariable
        //Margin of optimization: instead of checking on the whole vector every iteration
        // we may copy the vector and subtract the cells as soon as they get chosen
        for(int j=0;j<data.size();j++)
        {
            newVar.resize(data.size());

            std::ostringstream ss;
            ss << threshold;

            /*std::string minorstr = "<" + std::to_string(threshold);
            std::string majorstr = ">" + std::to_string(threshold);  GIVES PROBLEMS WITH MINGW */

            std::string minorstr = "<=" + ss.str();
            std::string majorstr = ">" + ss.str();

            if(data[j]<=threshold)
                newVar[j] = minorstr;
            else
                newVar[j] = majorstr;
        }

        result[i] = std::move(newVar);    //here we use CategoricalVar ctor with vector<>&&
    }
    return result;
}

std::ostream& operator<<(std::ostream& ostr,const ContinuousDescriptor& descr)
{
    for(const auto& i: descr.data)
        ostr << i << " ";
    return ostr;
}
