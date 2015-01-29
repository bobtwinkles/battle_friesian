#ifndef _UTIL_TREE_H_
#define _UTIL_TREE_H_

#include <array>
#include <cassert>
#include <functional>
#include <map>
#include <vector>

namespace fri {
  namespace util {
    template<typename KeyType, typename ValueType>
    class ChainTreeNode {
      private:
        std::map<KeyType, ChainTreeNode<KeyType, ValueType>* > _children;
        ChainTreeNode<KeyType, ValueType> * _parent;
        const KeyType _key;
        ValueType _value;
      public:
        ChainTreeNode(const KeyType & Key, ValueType Value) :
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

    template<typename KeyType, typename ValueType, KeyType LeafKey, ValueType DefaultValue>
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

        // Returns the matched node and the length of the key sequence leading up to the matched node
        std::pair<ChainTreeNode<KeyType, ValueType> *, int> FirstMatch(const KeyType * KeyChain, int KeyChainLength) {
          ChainTreeNode<KeyType, ValueType> * current = &_root;
          ChainTreeNode<KeyType, ValueType> * next;
          int depth = 0;
          bool found = false;
          while (!found && depth < KeyChainLength &&
                (next = current->GetChild(KeyChain[depth]))) {
            current = next;
            if (current->GetKey() == LeafKey || current->GetValue() != DefaultValue) {
              found = true;
            }
            ++depth;
          }
          if (!found) {
            return std::make_pair(nullptr, 0);
          } else {
            return std::make_pair(current, depth);
          }
        }

        ChainTreeNode<KeyType, ValueType> * Get(const KeyType * KeyChain, int KeyChainLength) {
          ChainTreeNode<KeyType, ValueType> * current = &_root;
          ChainTreeNode<KeyType, ValueType> * next;
          int depth = 0;
          bool found = false;
          while (!found && depth < KeyChainLength &&
                (next = current->GetChild(KeyChain[depth]))) {
            current = next;
            if (current->GetKey() == LeafKey) {
              found = true;
            }
            ++depth;
          }
          if (!found) {
            return nullptr;
          } else {
            return current;
          }
        }

        enum InsertFailure {
          E_SUCCESS = 0,
          E_AMBIGUOUS_KEY,
        };

        std::pair<ChainTreeNode<KeyType, ValueType> *, InsertFailure> Insert(const KeyType * KeyChain, int KeyChainLength, const ValueType & Value) {
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

          while (depth < KeyChainLength) {
            next = new ChainTreeNode<KeyType, ValueType>(KeyChain[depth], DefaultValue);
            _nodes.push_back(next);
            current->AddChild(next);
            current = next;
            ++depth;
          }
          next = new ChainTreeNode<KeyType, ValueType>(LeafKey, Value);
          _nodes.push_back(next);
          current->AddChild(next);
          return std::make_pair(next, E_SUCCESS);
        }
    };
  }
}

#endif
