#ifndef _UTIL_TREE_H_
#define _UTIL_TREE_H_

#include <map>

namespace fri {
  namespace util {
    template<typename KeyType, typename ValueType>
    class Tree {
      private:
        std::map<KeyType, Tree<KeyType, ValueType>* > _children;
        Tree<KeyType, ValueType> * _parent;
        ValueType _value;
        KeyType _key;

      public:
        Tree(KeyType Key, ValueType Value) {
          _key = Key;
          _value = Value;
          _parent = nullptr;
        }

        ~Tree() {
        }

        void AddChild(Tree<KeyType, ValueType> * Child) {
          Child->_parent = this;
          _children.insert(std::make_pair(Child->_key, Child));
        }

        Tree<KeyType, ValueType> * GetChild(KeyType K) {
          auto a = _children.find(K);
          if (a == _children.end()) {
            return nullptr;
          }
          return a->second;
        }

        inline ValueType & GetValue() { return _value; }
        inline void SetValue(const ValueType & Value) { _value = Value; }
    };
  }
}

#endif
