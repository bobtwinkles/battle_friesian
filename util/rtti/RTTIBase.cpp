#include "util/rtti/RTTIBase.hpp"

#include <unordered_map>
#include <iostream>
#include "util/Hash.hpp"

using fri::util::rtti::TypeID;

namespace {
  TypeID current_typeid = 0;

  typedef std::unordered_map<TypeID, const char *> ClassnameMap;

   inline ClassnameMap & GetClassnameMap() {
     /// TODO: this should probably find a way to dealloc the map, but for now it should be OK
    static ClassnameMap * class_names = new ClassnameMap();
    return *class_names;
  }

}

TypeID fri::util::rtti::NextTypeID(const char * Name) {
  current_typeid += 1;
  std::cout << current_typeid << " " << Name << std::endl;
  GetClassnameMap().insert(std::make_pair(current_typeid, Name));
  return current_typeid;
}

const char * fri::util::rtti::ClassnameForTypeID(TypeID ID) {
  auto it = GetClassnameMap().find(ID);

  if (it != GetClassnameMap().end()) {
    return it->second;
  } else {
    return "BAD_TYPE_ID";
  }
}
