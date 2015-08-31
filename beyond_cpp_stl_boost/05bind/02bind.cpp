#include <boost/bind.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // provides std::for_each

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
  std::vector<Status> statuses;
  statuses.push_back(Status("status 1"));
  statuses.push_back(Status("status 2"));
  statuses.push_back(Status("status 3"));
  statuses.push_back(Status("status 4"));

  statuses[1].break_it();
  statuses[2].break_it();

  // the old way
  for (std::vector<Status>::iterator it = statuses.begin(); it != statuses.end(); ++it)
    it->report();

  // using std::for_each without boost::bind -- std::mem_fun_ref converts class member function to function object reference
  std::for_each(statuses.begin(), statuses.end(), std::mem_fun_ref(&Status::report));
  // this is also more efficient than the old way, because we don't have to call statuses.end() each time

  // using std::for_each with boost::bind
  std::for_each(statuses.begin(), statuses.end(), boost::bind(&Status::report,_1));
  // "tells the compiler that _1 is to be substituted for an actual argument by the function invoking the binder"
}
