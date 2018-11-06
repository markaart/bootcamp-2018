#ifndef CHAPTER3_PAIR_H
#define CHAPTER3_PAIR_H

/*
  Pair class implementation. Only needs the "<" operator property, but should also follow the rule of six, and needs to be default constructable to go into a container. Investigate further needs in homework.cpp
*/

namespace chapter3
{

  template <typename T, typename U>
  class pair
  {
   public:
    pair(const T& first_, const U& second_) : first(first_), second(second_) {}    
    T first;
    U second;
  };
}

#endif //CHAPTER3_PAIR_H
