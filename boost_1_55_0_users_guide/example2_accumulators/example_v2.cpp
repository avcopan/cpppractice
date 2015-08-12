#include <iostream>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>

int main()
{
    // Define an accumulator set for calculating the mean and the
    // 2nd moment ...
    boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::mean, boost::accumulators::tag::moment<2> > > acc;

    // push in some data ...
    acc(1.2);
    acc(2.3);
    acc(3.4);
    acc(4.5);

    // Display the results ...
    std::cout << "Mean:   " << boost::accumulators::mean(acc) << std::endl;
    std::cout << "Moment: " << boost::accumulators::moment<2>(acc) << std::endl;

    return 0;
}
