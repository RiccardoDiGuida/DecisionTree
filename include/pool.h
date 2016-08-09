#ifndef POOL_H
#define POOL_H

#include <string>
#include <vector>
#include <map>
#include <memory>

class Pool
{
public:
    typedef std::map<int,std::string> MyMap;
    typedef std::vector<std::shared_ptr<Pool>> NodeContainerType;

    Pool();
    Pool(const MyMap& mapInit,const std::string& fac="",int split=0,int gain=0);
    Pool(const std::vector<int>& idxs, const std::vector<std::string>& labs, const std::string& fac="",int split=0,int gain=0);
    Pool(const Pool &other);       //deep copy of ptrs in next
    Pool& operator=(const Pool& other); //deep copy of ptrs in next
    Pool(Pool&& other) noexcept;
    Pool& operator=(Pool&& other) noexcept;

    void add_sample(std::pair<int,std::string>);
    void remove_sample(int idx);

    void add_node(const Pool& newPool);
    void add_node(Pool&& newPool);

    void setFactor(const std::string& fac);
    void setVarIdx(int var);
    void setInfoGain(double gain);

    Pool& getNext(int i);

    int sampleSize() const;
    int levelSize() const;
    const std::string& getLevel(int n) const;
    std::vector<int> allIdxs() const;
    std::vector<int> idxs(int facNumb) const;
    std::vector<std::string> labsFromIdx(const std::vector<int>& indexes) const;

    friend std::ostream& operator<<(std::ostream& ostr,const Pool& pool);

private:
    std::string factor;   // It is the factor that splitted it. Does not apply for first pool.
    int idx_splitter;    // index of the variable that splits the current pool
    double info_gain;       // information gain obtained on the split
    MyMap samples;
    std::vector<std::string> levels;
    std::vector<std::shared_ptr<Pool>> next;

    void copyNodes(NodeContainerType& to,const NodeContainerType& from);
};

#endif // POOL_H
