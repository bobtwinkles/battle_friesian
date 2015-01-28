#include "systems/input/InputSystem.hpp"

#include "systems/GameContext.hpp"

#include <cstring>

using fri::util::ChainTreeNode;
using fri::system::GameContext;
using fri::system::input::InputAction;
using fri::system::input::InputEvent;
using fri::system::input::InputResponse;
using fri::system::input::InputSystem;

namespace {
  void PrintInputQueue(std::list<InputEvent> & Queue, std::unordered_map<SDL_Keycode, InputAction> & Mapping) {
    for (auto i : Queue) {
      auto m = Mapping.find(i.key);
      if (m == Mapping.end()) {
        std::cout << i.key << " ";
      } else {
        switch(m->second) {
          case InputAction::INPUT_END   : std::cout << "INPUT_END   "; break;
          case InputAction::INPUT_UP    : std::cout << "INPUT_UP    "; break;
          case InputAction::INPUT_DOWN  : std::cout << "INPUT_DOWN  "; break;
          case InputAction::INPUT_LEFT  : std::cout << "INPUT_LEFT  "; break;
          case InputAction::INPUT_RIGHT : std::cout << "INPUT_RIGHT "; break;
          case InputAction::INPUT_JUMP  : std::cout << "INPUT_JUMP  "; break;
          default: std::cout << "UNKNOWN " << m->second; break;
        }
      }
    }
    if (Queue.size() > 0) {
      std::cout << std::endl;
    }
  }
}

InputSystem::InputSystem() :
  _action_tree(InputAction::INPUT_END, nullptr) {
}

InputSystem::~InputSystem() {
}

void InputSystem::Tick(GameContext & Context, double Step) {
  InputAction queue[1024]; // If there are more that 1024 input actions we've got a big problem
  int queue_length= 0;

  PrintInputQueue(_input_queue, _input_mappings);

  // Drop stale input events
  while(_input_queue.size() > 0 && _input_queue.front().input_frame < Context.GetCurrentTime() - 5/60.f) {
    _input_queue.pop_front();
  }
  if (_input_queue.size() > 0) {
    // Transcribe input queue to InputActions for pattern matching
    for (InputEvent ev : _input_queue) {
      auto a = _input_mappings.find(ev.key);
      if (a != _input_mappings.end()) {
        queue[queue_length] = a->second;
        ++queue_length;
      }
    }

    // Pattern match input
    std::pair<ChainTreeNode<InputAction, InputResponse> *, int> action = std::make_pair(nullptr, 0);
    int num_drop = 0;
    do {
      action = _action_tree.FirstMatch(queue + num_drop, queue_length - num_drop);
      if (action.first) {
        action.first->GetValue()(Context, queue + num_drop);
        num_drop += action.second;
      }
    } while (action.first);

    // and drop all the consumed input
    while ( num_drop > 0 ) { _input_queue.pop_front(); }
  }

  // Handle any continuous actions
  for (auto k : _active_inputs) {
    auto mapped = _input_mappings.find(k);
    if (mapped != _input_mappings.end()) {
      auto response = _continuous_actions.find(mapped->second);
      if (response != _continuous_actions.end()) {
        response->second(Context, &response->first);
      }
    }
  }
}

void InputSystem::InputActivate(GameContext & Context, SDL_Keycode K) {
  _input_queue.push_back(InputEvent(Context.GetCurrentTime(), K));
  _active_inputs.insert(K);
}

void InputSystem::InputDeactivate(GameContext & Context, SDL_Keycode K) {
  _active_inputs.erase(K);
}

void InputSystem::RegisterInputEdgeTrigger(const InputAction * Descriptor, InputResponse Response) {
  int len = strlen((const char *)Descriptor);
  _action_tree.Insert(Descriptor, len, Response);
}

void InputSystem::RegisterInputContinuousTrigger(const InputAction Action, InputResponse Response) {
  _continuous_actions.insert(std::make_pair(Action, Response));
}

void InputSystem::SetInputMapping(SDL_Keycode K, InputAction Action) {
  _input_mappings.insert(std::make_pair(K, Action));
}
