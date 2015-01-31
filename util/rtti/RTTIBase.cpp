#include "util/rtti/RTTIBase.hpp"

namespace {
  int current_typeid = 0;
}

int fri::util::rtti::NextTypeID() {
  current_typeid += 1;
  return current_typeid;
}
