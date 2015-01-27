#include "systems/input/InputSystem.hpp"

#include "systems/GameContext.hpp"

#include <cstring>

using fri::system::GameContext;
using fri::system::input::InputResponse;
using fri::system::input::InputSystem;

InputSystem::InputSystem() :
  _action_tree(InputAction::INPUT_END, nullptr) {
}

InputSystem::~InputSystem() {
}

void InputSystem::Tick(GameContext & Context, double Step) {
  InputAction queue[1024]; // If there are more that 1024 input actions we've got a big problem
  int i = 0;

  while(_input_queue.front().input_frame < Context.GetCurrentTime() - 5/60.f) {
    _input_queue.pop_front();
  }

  for (InputEvent ev : _input_queue) {
    auto a = _input_mappings.find(ev.key);
    if (a != _input_mappings.end()) {
      queue[i] = a->second;
      ++i;
    }
  }

  auto a = _action_tree.FirstMatch(queue, i);
  if (a.first) {
    queue[a.second] = INPUT_END;
    a.first->GetValue()(Context, queue);
  }
}

void InputSystem::EnqueueInputEvent(GameContext & Context, SDL_Keycode K) {
  _input_queue.push_back(InputEvent(K, Context.GetCurrentTime()));
}

void InputSystem::RegisterInputAction(const InputAction * Descriptor, InputResponse Response) {
  int len = strlen((const char *)Descriptor);
  _action_tree.Insert(Descriptor, len, Response);
}

void InputSystem::SetInputMapping(SDL_Keycode K, InputAction Action) {
  _input_mappings.insert(std::make_pair(K, Action));
}
