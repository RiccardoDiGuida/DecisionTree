#ifndef CATEGORICALDESCRIPTOR_H
#define CATEGORICALDESCRIPTOR_H

#include <iostream>
#include <string>
#include <vector>

#include "abstractdescriptor.h"

class CategoricalDescriptor : public AbstractDescriptor
{
public:
    CategoricalDescriptor();
    virtual ~CategoricalDescriptor();
    CategoricalDescriptor(const std::vector<std::string>& vec);
    CategoricalDescriptor(const std::vector<std::string>&& vec);
    CategoricalDescriptor(const CategoricalDescriptor &other);
    CategoricalDescriptor& operator=(const CategoricalDescriptor& other);
    CategoricalDescriptor(CategoricalDescriptor&& other) noexcept;
    CategoricalDescriptor& operator=(CategoricalDescriptor&& other) noexcept;

    virtual Ptr create() const;
    virtual Ptr clone() const;
    virtual bool isConvertible() const;

    void toggleUsed();
    bool isUsed();

    const std::string& getLevel(int n) const;
    std::vector<std::string> getLabels() const;

    std::vector<int> idxs(int facNumb) const;

    int dataSize() const;
    int levelSize() const;

    friend std::ostream& operator<<(std::ostream& ostr,const CategoricalDescriptor& descr);

private:
    std::vector<std::string> data;
    std::vector<std::string> levels;
    bool used;
};

#endif // CATEGORICALDESCRIPTOR_H
