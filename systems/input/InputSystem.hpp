#ifndef _SYSTEMS_INPUT_INPUTSYSTEM_H_
#define _SYSTEMS_INPUT_INPUTSYSTEM_H_

#include <unordered_map>
#include <list>
#include <set>

#include <SDL2/SDL_keyboard.h>

#include "systems/System.hpp"
#include "util/Hash.hpp"
#include "util/Tree.hpp"

namespace fri {
  namespace system {
    class GameContext;

    namespace input {
      enum InputAction : char { // Must be a char so strlen hack won't break.
        INPUT_END = 0, // used to indicate the end of a list of inputs
                       // Using 0 for this means we can use strlen to get the length of the input strings
                       // NullTerminatedHash also depeneds on this behavior
        INPUT_UP,
        INPUT_DOWN,
        INPUT_LEFT,
        INPUT_RIGHT,
        INPUT_JUMP,
      };

      //typedef void (*InputResponse) (fri::system::GameContext & Context, const InputAction * Action);
      typedef std::function<void(fri::system::GameContext & Context, const InputAction * Action)> InputResponse;

      struct InputEvent {
        double input_frame;
        SDL_Keycode key;

        InputEvent(double Frame, SDL_Keycode Key) : input_frame(Frame), key(Key) {}
      };

      class InputSystem : public fri::system::ISystem {
        public:
        private:
          std::unordered_map<SDL_Keycode, InputAction> _input_mappings;
          std::unordered_map<InputAction, InputResponse, fri::util::FNVHash<InputAction>> _continuous_actions;
          std::list<InputEvent> _input_queue;
          std::set<SDL_Keycode> _active_inputs;
          typedef fri::util::ChainTree<InputAction, const InputResponse *, INPUT_END, nullptr> ActionTree;
          ActionTree _action_tree;
        public:
          InputSystem();
          ~InputSystem();

          virtual void Tick(fri::system::GameContext & Context, double Step);

          void InputActivate(fri::system::GameContext & Context, SDL_Keycode K);
          void InputDeactivate(fri::system::GameContext & Context, SDL_Keycode K);

          void SetInputMapping(SDL_Keycode K, InputAction Action);

          void RegisterInputEdgeTrigger(const InputAction * Descriptor, InputResponse Response);
          void RegisterInputContinuousTrigger(const InputAction Action, InputResponse Response);
      };
    }
  }
}

#endif
