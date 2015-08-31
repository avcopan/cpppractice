#include <boost/bind.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // provides std::for_each
#include <boost/shared_ptr.hpp>

class Status {
  private:
    std::string name_;
    bool        ok_;
  public:
    Status(const std::string& name) : name_(name), ok_(true) {}

    void break_it() { ok_ = false; }
    bool is_broken() const { return ok_; }
    void report() const { std::cout << name_ << " is " << (ok_ ? "okay" : "broken") << std::endl; }
};


int main()
{
  std::vector<boost::shared_ptr<Status> > statptrs;
  statptrs.push_back(boost::shared_ptr<Status>(new Status("status 1")));
  statptrs.push_back(boost::shared_ptr<Status>(new Status("status 2")));
  statptrs.push_back(boost::shared_ptr<Status>(new Status("status 3")));
  statptrs.push_back(boost::shared_ptr<Status>(new Status("status 4")));

  statptrs[1]->break_it();
  statptrs[2]->break_it();

  // this no longer works for boost::shared_ptrs
//std::for_each(statptrs.begin(), statptrs.end(), std::mem_fun(&Status::report));

  // boost::bind works the same way
  std::for_each(statptrs.begin(), statptrs.end(), boost::bind(&Status::report,_1));

  // now, we no longer to deallocate
}
