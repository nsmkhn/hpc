#include "interval.h"
#include "thread_pool.h"
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include <unordered_set>

#define NUM_ARGS 2

void parse_intervals(const char *filename, std::vector<Interval> *intervals);
void parse_primes(std::vector<Interval> *intervals, ThreadPool *tp, std::unordered_set<uint64_t> *primes, std::mutex *mutex);
void _parse_primes_in_interval(Interval interval, std::unordered_set<uint64_t> *primes, std::mutex *mutex);
bool _isprime(int64_t digit);
 
int main(int argc, char **argv)
{
    if(argc != NUM_ARGS)
    {
        std::cerr << "Usage: " << argv[0] << " <file>\n";
        exit(EXIT_FAILURE);
    }

    std::vector<Interval> intervals;
    parse_intervals(argv[1], &intervals);

    ThreadPool tp;
    std::unordered_set<uint64_t> primes;
    std::mutex mutex;
    parse_primes(&intervals, &tp, &primes, &mutex);
    tp.join_workers();

    std::cout << primes.size() << std::endl;

    return 0;
}

void
parse_intervals(const char *filename, std::vector<Interval> *intervals)
{
    boost::property_tree::ptree pt;
    try {
        boost::property_tree::read_xml(filename, pt);
    } catch(boost::property_tree::xml_parser_error &e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    for(auto &kv : pt.get_child(INTERVALS_TAG))
        intervals->emplace_back(kv.second.get<int64_t>(INTERVALS_LEFT_TAG, 0),
                                kv.second.get<int64_t>(INTERVALS_RIGHT_TAG, 0));
}

void
parse_primes(std::vector<Interval> *intervals,
             ThreadPool *tp,
             std::unordered_set<uint64_t> *primes,
             std::mutex *mutex)
{
    for(auto &interval : *intervals)
        tp->add_task(std::bind(_parse_primes_in_interval, interval, primes, mutex));
}

void
_parse_primes_in_interval(Interval interval,
                          std::unordered_set<uint64_t> *primes,
                          std::mutex *mutex)
{
    for(int64_t digit = interval.left_bound;
        digit < interval.right_bound;
        ++digit)
    {
        if(_isprime(digit))
        {
            std::lock_guard<std::mutex> lock(*mutex);
            primes->insert(digit);
        }
    }
}

bool
_isprime(int64_t digit)
{
    if(digit <= 1)
        return false;
    if(digit <= 3)
        return true;
    for(int64_t j = 2; j*j <= digit; ++j)
        if(digit % j == 0)
            return false;

    return true;
}
