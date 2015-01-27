#ifndef _UTIL_TREE_H_
#define _UTIL_TREE_H_

#include <array>
#include <map>
#include <vector>
#include <cassert>
#include <functional>

namespace fri {
  namespace util {
    template<typename KeyType, typename ValueType>
    class ChainTreeNode {
      private:
        std::map<KeyType, ChainTreeNode<KeyType, ValueType>* > _children;
        ChainTreeNode<KeyType, ValueType> * _parent;
        KeyType _key;
        ValueType _value;
      public:
        ChainTreeNode(KeyType & Key, ValueType Value) :
          _key(Key) {
          _value = Value;
          _parent = nullptr;
        }

        ~ChainTreeNode() {
        }

        void AddChild(ChainTreeNode<KeyType, ValueType> * Child) {
          Child->_parent = this;
          _children.insert(std::make_pair(Child->_key, Child));
        }

        ChainTreeNode<KeyType, ValueType> * GetChild(KeyType K) {
          auto a = _children.find(K);
          if (a == _children.end()) {
            return nullptr;
          }
          return a->second;
        }

        inline const KeyType & GetKey() const { return _key; }
        inline ValueType & GetValue() { return _value; }
        inline void SetValue(const ValueType & Value) { _value = Value; }
    };

    template<typename KeyType, typename ValueType, ValueType DefaultValue>
    class ChainTree {
      private:
        ChainTreeNode<KeyType, ValueType> _root;
        std::vector<ChainTreeNode<KeyType, ValueType> *> _nodes;
      public:
        ChainTree(KeyType RootKey, ValueType RootValue) :
          _root(RootKey, RootValue) {
        }

        ~ChainTree() {
          for (auto i : _nodes) {
            delete i;
          }
        }

        ChainTreeNode<KeyType, ValueType> * Get(const KeyType * KeyChain, int KeyChainLength) {
          ChainTreeNode<KeyType, ValueType> * current = &_root;
          ChainTreeNode<KeyType, ValueType> * next;
          int depth = 0;
          while (depth < KeyChainLength &&
                (next = current->GetChild(KeyChain[depth]))) {
            current = next;
            ++depth;
          }
          if (depth >= KeyChainLength) {
            return nullptr;
          } else {
            return current;
          }
        }

        enum InsertFailure {
          E_SUCCESS = 0,
          E_AMBIGUOUS_KEY,
        };

        std::pair<ChainTreeNode<KeyType, ValueType> *, InsertFailure> Insert(const KeyType * KeyChain, int KeyChainLength, ValueType & Value) {
          ChainTreeNode<KeyType, ValueType> * current = &_root;
          ChainTreeNode<KeyType, ValueType> * next;
          int depth = 0;

          while (depth < KeyChainLength &&
                 (next = current->GetChild(KeyChain[depth]))) {
            current = next;
            ++depth;
          }

          if (depth >= KeyChainLength) {
            return std::make_pair(nullptr, E_AMBIGUOUS_KEY);
          }

          while (depth < KeyChainLength - 1) {
            next = new ChainTreeNode<KeyType, ValueType>(KeyChain[depth], DefaultValue);
            _nodes.push_back(next);
            current->AddChild(next);
            current = next;
          }
          next = new ChainTreeNode<KeyType, ValueType>(KeyChain[depth], DefaultValue);
          _nodes.push_back(next);
          current->AddChild(next);
          return std::make_pair(next, E_SUCCESS);
        }
    };
  }
}

#endif
