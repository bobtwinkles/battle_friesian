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

      /**
       * Replace `dynamic_cast`.
       *
       * @todo support casting up a type hierarchy
       */
      template<typename T>
      T * GetBaseAs(RTTIStub * Stub) {
        if (Stub->GetType() == T::_type) {
          return (T*) Stub->GetBase();
        } else {
          return nullptr;
        }
      }

      /**
       * Passes through a nullptr if `Stub` is null.
       *
       * @see GetBaseAs()
       */
      template<typename T>
      T * GetBaseAsNull(RTTIStub * Stub) {
        if (!Stub) {
          return nullptr;
        } else {
          return GetBaseAs<T>(Stub);
        }
      }

      /**
       * Base class of all things which intend to provide RTTI data.
       * Every subclass _must_ export a member of the form
       * `public static TypeID _type` in order to allow the casting functions
       *  to work properly.
       */
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
