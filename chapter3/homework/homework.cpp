
/**
 * A histogram
 *
 * A histogram is the partitioning of a given space into cells, 
 * where each cell has a value associated with it which represents 
 * the number of objects in that cell.
 * 
 * Only the number of objects in a cell are represented in a histogram.  
 * A histogram in an imprecise representation of the original space.
 * It's a lossy compression algorithm.
 *
 * Assumptions:
 *  - Assume cells are contiguous sub-spaces.
 *  - Each object has a position.
 */

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cmath>

#include "pair.h"
#include "array_sizet.h"

// Homework - Comment out the next three lines and
//            implement array and pair.  You only need
//            to implement enough so that this compiles
//            and you get the same result.
//#include <array> 
//using std::array;
//using std::pair;
using chapter3::pair;
using chapter3::array;

template <typename X, size_t N, typename W = unsigned>
class histogram{
public:
  using axis_t = array<X,N+1>;
  using bin_t = array<W,N>;

  histogram(const axis_t& axis) : axis(axis){
    bins.fill(0);
  }
  
  size_t get_n() const { return n; }
  const axis_t& get_axis() const { return axis; }
  const bin_t& get_bins() const { return bins; }
  void fill(const X& value, const W& weight){
    size_t bin_index{0};
    for(auto leading_edge : axis){
      if(value < leading_edge){
	bins[bin_index-1] += weight;
	break;
      }
      bin_index++;
    }
  }
  
private:
  size_t n = N;
  axis_t axis;
  bin_t bins;
};

template <typename T, size_t N>
void print(const array<T,N>& a){
  for(auto v : a){ //array needs an iterator, each element needs an operator<<
    std::cout<<v<<" ";
  }
  std::cout<<std::endl;
}

template<typename T>
T random_uniform(const pair<T,T>& range){
  T f{static_cast<T>(std::rand())/RAND_MAX};
  return (1-f)*range.first + f*range.second;
}

template <typename F, typename T>
T accept_reject(F f, const pair<T,T>& range){
  const pair<T,T> y_range(0,1);
  T x0{random_uniform(range)};
  T y0{random_uniform(y_range)};
  while(y0 > f(x0)){
    x0 = random_uniform(range);
    y0 = random_uniform(y_range);
  }
  return x0;
}

struct dom{
  unsigned string;
  unsigned om;
};

bool operator<(const dom& lhs, const dom& rhs){
  return (lhs.string < rhs.string || lhs.om < rhs.om);
}

int main(int argc, char** argv){

  array<double, 100> data;
  pair<double, double> minmax{0,10};
  const double pi{3.141592653589793};
  double mean{5};
  double width{2};
  double amp{1/(width*std::sqrt(2*pi))};
  for(auto& d: data){
    d = accept_reject([amp, mean, width](double x){
	return amp * std::exp(-(x-mean)*(x-mean)/width);
      }, minmax);
  }
  
  using double_histogram_t = histogram<double, 10>;  
  double_histogram_t::axis_t dh_axis{1,2,3,4,5,6,7,8,9,10};    
  double_histogram_t dh(dh_axis);
  for(auto d : data){
    dh.fill(d,1);
  }
  std::cout<<"Gaussian Distribution"<<std::endl;
  print(dh.get_bins());
  std::cout<<std::endl;

  
  using dom_histogram_t = histogram<dom, 4>;  
  dom_histogram_t::axis_t dom_h_axis{dom{1,1}, dom{1,2}, dom{2,1}, dom{2,2}, dom{3,3}};    
  dom_histogram_t dom_h(dom_h_axis);
  array<dom, 5> hits{dom{1,1}, dom{1,2}, dom{1,1}, dom{1,2}, dom{2,2}};
  for(auto hit : hits){
    dom_h.fill(hit,1);
  }
  std::cout<<"DOM Hit Distribution"<<std::endl;
  print(dom_h.get_bins());
}
