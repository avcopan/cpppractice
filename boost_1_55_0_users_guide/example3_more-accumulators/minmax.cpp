#include <stdio.h>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/lambda/lambda.hpp>
namespace ba = boost::accumulators;
namespace bl = boost::lambda;

int main()
{
    std::vector<int> numbers;
    numbers.push_back( -1);
    numbers.push_back(  3);
    numbers.push_back(  4);
    numbers.push_back(  9);
    numbers.push_back( 15);
    numbers.push_back(267);
    std::for_each(numbers.begin(), numbers.end(), std::cout << bl::_1);

/*
    ba::accumulator_set<double, ba::stats<ba::tag::mean, ba::tag::moment<2> > > acc;

    // push in some data ...
    acc(1.2);
    acc(2.3);
    acc(3.4);
    acc(4.5);

    // Display the results ...
    std::cout << "Mean:   " << ba::mean(acc) << std::endl;
    std::cout << "Moment: " << ba::moment<2>(acc) << std::endl;
*/
}
