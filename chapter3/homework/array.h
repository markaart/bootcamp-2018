#ifndef CHAPTER3_ARRAY_H
#define CHAPTER3_ARRAY_H

#include <memory>
#include <initializer_list>

namespace chapter3
{
  template <typename T, size_t N>
  class array
  {
   public:
    array(): my_size(N), data(new T[my_size]) {}

    array(std::initializer_list<T> values) : my_size(values.size()), data(new T[my_size])
    {
      std::copy(std::begin(values), std::end(values), &data[0]);
    }
    
    array(const array& that) : my_size(that.my_size), data(new T[my_size])
    {
      std::copy(&that.data[0], &that.data[that.my_size], &data[0]);
    }

    //int size() const { return my_size; }
    
    const T& operator[](int i) const 
    {
      //check_index(i);
	return data[i];
    }
		     
    T& operator[](int i) 
    {
      //check_index(i);
	return data[i];
    }

    void fill(const T& val)
    {
      for (int i=0; i<my_size; ++i)
      {
	data[i] = val;
      }
    }
    
    using iterator = T*;
    using const_iterator = const T*; // where does it actually state these in the book??

    iterator begin() {return &data[0];}
    const_iterator begin() const {return &data[0];}
    iterator end() {return &data[my_size];}
    const_iterator end() const {return &data[my_size];}

   private:
    size_t my_size;
    std::unique_ptr<T[]> data;
  };
}

#endif //CHAPTER3_ARRAY_H
