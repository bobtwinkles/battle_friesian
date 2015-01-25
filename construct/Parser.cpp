#include "construct/Parser.hpp"
// None of the actual parsers are implemented here
// They are implemented as follows:
//
// ParseLevel()    -- LevelParser.cpp

using fri::construct::ParseError;

////////////////////////////////////////////////////////////////////////////////
//////////////////////////  ParseError Members /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

ParseError::ParseError() {
  _did_error = false;
}

ParseError::ParseError(int Line, int Char, std::string Error) {
  _line = Line;
  _char = Char;
  _error = Error;
  _did_error = true;
}

ParseError::ParseError(const ParseError & Other) {
  _line = Other._line;
  _char = Other._char;
  _error = Other._error;
  _did_error = Other._did_error;
}

ParseError::ParseError(const ParseError && Other) {
  _line = Other._line;
  _char = Other._char;
  _error = std::move(Other._error);
  _did_error = Other._did_error;
}

ParseError & ParseError::operator=(const ParseError & Other) {
  ParseError temp(Other);
  temp.Swap(*this);
  return *this;
}

ParseError & ParseError::operator=(const ParseError && Other) {
  _line = Other._line;
  _char = Other._char;
  _error = std::move(Other._error);
  _did_error = Other._did_error;
  return *this;
}

void ParseError::Swap(ParseError & Other) {
  std::swap<int>(_line, Other._line);
  std::swap<int>(_char, Other._char);
  std::swap<std::string>(_error, Other._error);
  std::swap<bool>(_did_error, Other._did_error);
}
