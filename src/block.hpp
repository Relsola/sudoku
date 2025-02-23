#pragma once

#include <sstream>

#include "common.hpp"

// 数独行政区域类
class CBlock {
  static const int MAX_COUNT = 9;

 public:
  CBlock();
  bool isValid() const;
  bool isFull() const;
  void print(std::ostringstream& buffer) const;
  void push_back(point_value_t* point);

 private:
  int _count;
  point_value_t* _numbers[MAX_COUNT];
};
