#ifndef ABSTRACTDESCRIPTOR_H
#define ABSTRACTDESCRIPTOR_H

#include <memory>

class AbstractDescriptor
{
public:
    typedef std::shared_ptr<AbstractDescriptor> Ptr;

    virtual ~AbstractDescriptor() {}
    virtual Ptr create() const = 0;
    virtual Ptr clone() const = 0;
    virtual void Dummy() const = 0;
};

#endif // ABSTRACTDESCRIPTOR_H
