#ifndef _UTIL_RTTI_H_
#define _UTIL_RTTI_H_

#include <iostream>

namespace fri {
  namespace util {
    namespace rtti {
      typedef int TypeID;

      /**
       * Structure encapsulating all information RTTI needs about the base
       * information.
       */
      struct BaseInfo {
        void * base_pointer;
        TypeID type;
      };

      /**
       * The stub which should be passed around instead of an RTTI object
       * which allows retrieval of the correct base pointer.
       */
      class RTTIStub {
        private:
          BaseInfo _base_info;

          friend class RTTIBase;
          RTTIStub(const BaseInfo & Info) {
            _base_info = Info;
          }
        public:
          ~RTTIStub() {
          }

          inline void * GetBase() const { return _base_info.base_pointer; }

          inline TypeID GetType() const { return _base_info.type; }
      };

      class RTTIBase {
        private:
          RTTIStub _stub;
        public:
          /**
           * The BasePointer should be the `this` pointer of the lowest element
           * in the inheritance hierarchy.
           */
          RTTIBase(const BaseInfo & Info) : _stub(Info) {
          }

          virtual ~RTTIBase() {}

          inline const RTTIStub * GetStub() const { return &_stub; }
          inline RTTIStub * GetStub() { return &_stub; }
      };

      TypeID NextTypeID(const char * ClassName);
      const char * ClassnameForTypeID(TypeID ID);
    }
  }
}

#endif
