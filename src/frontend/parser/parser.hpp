#ifndef PARSER_HEADER_HXX
#define PARSER_HEADER_HXX

#include "../tokens.hpp"

namespace frontend::parser {
/// Parser Class
class Parser {
  Parser() = default;
  ~Parser() = delete;
  Parser(const Parser &) = delete;
  Parser &operator=(const Parser &) = delete;

public:
  static Parser &Get(frontend::tokens::token_array_t);
};
} // namespace frontend::parser

#endif
