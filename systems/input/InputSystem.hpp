#ifndef _SYSTEMS_INPUT_INPUTSYSTEM_H_
#define _SYSTEMS_INPUT_INPUTSYSTEM_H_

#include <unordered_map>
#include <list>

#include <SDL2/SDL_keyboard.h>

#include "systems/System.hpp"
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

      typedef void (*InputResponse) (fri::system::GameContext & Context, const InputAction * Action);

      struct InputEvent {
        double input_frame;
        SDL_Keycode key;

        InputEvent(double Frame, SDL_Keycode Key) : input_frame(Frame), key(Key) {}
      };

      class InputSystem : public fri::system::ISystem {
        public:
        private:
          std::unordered_map<SDL_Keycode, InputAction> _input_mappings;
          std::list<InputEvent> _input_queue;
          // Todo: replace with std::function
          fri::util::ChainTree<InputAction, InputResponse, INPUT_END, nullptr> _action_tree;

          void MapInput(char * Out) const;
        public:
          InputSystem();
          ~InputSystem();

          virtual void Tick(fri::system::GameContext & Context, double Step);

          void EnqueueInputEvent(fri::system::GameContext & Context, SDL_Keycode K);

          void SetInputMapping(SDL_Keycode K, InputAction Action);

          void RegisterInputAction(const InputAction * Descriptor, InputResponse Response);
      };
    }
  }
}

#endif
