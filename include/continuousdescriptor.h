#ifndef CONTINUOUSDESCRIPTOR_H
#define CONTINUOUSDESCRIPTOR_H

#include <iostream>
#include <vector>

#include "abstractdescriptor.h"
#include "categoricaldescriptor.h"

class ContinuousDescriptor : public AbstractDescriptor
{
public:
    ContinuousDescriptor();
    virtual ~ContinuousDescriptor();
    ContinuousDescriptor(const std::vector<double>& vec);
    ContinuousDescriptor(const ContinuousDescriptor &other);
    ContinuousDescriptor& operator=(const ContinuousDescriptor& other);
    ContinuousDescriptor(ContinuousDescriptor&& other) noexcept;
    ContinuousDescriptor& operator=(ContinuousDescriptor&& other) noexcept;

    virtual Ptr create() const;
    virtual Ptr clone() const;
    virtual bool isConvertible()const;

    std::vector<CategoricalDescriptor> toCategorical(int groups=10);

    friend std::ostream& operator<<(std::ostream& ostr,const ContinuousDescriptor& descr);

private:
    std::vector<double> data;
};


#endif // CONTINUOUSDESCRIPTOR_H
