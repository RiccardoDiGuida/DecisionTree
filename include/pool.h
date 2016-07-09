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

    Pool();
    Pool(const MyMap& mapInit,const std::string& fac="",int split=0);
    Pool(const std::vector<int>& idxs, const std::vector<std::string>& labs, const std::string& fac="",int split=0);
    Pool(const Pool &other);       //shallow copy of ptrs in next
    Pool& operator=(const Pool& other); //shallow copy of ptrs in next
    Pool(Pool&& other) noexcept;
    Pool& operator=(Pool&& other) noexcept;

    void add_sample(std::pair<int,std::string>);
    void remove_sample(int idx);
    int sampleSize() const;
    int levelSize() const;
    const std::string& getLevel(int n) const;
    std::vector<int> idxs(int facNumb) const;


private:
    std::string factor;   // It is the factor that splitted it. Does not apply for first pool.
    int idx_splitter;    // index of the variable that splits the current pool
    MyMap samples;
    std::vector<std::string> levels;
    std::vector<std::shared_ptr<Pool>> next;
};

#endif // POOL_H