#ifndef LEXER_HEADER_HXX
#define LEXER_HEADER_HXX

#include "../tokens.hpp"
#include <memory>
#include <string>

namespace frontend::lexer {
class Lexer {
public:
  static Lexer &Get(std::unique_ptr<std::string>);
  tokens::token_array_t tokenize();

private:
  std::string m_Source;
  std::vector<std::string> seperate_source_string;
  Lexer() {}
  Lexer(const Lexer &);
  void operator=(const Lexer &);
  Lexer(std::string src) : m_Source(std::move(src)) {}
};
} // namespace frontend::lexer

#endif
