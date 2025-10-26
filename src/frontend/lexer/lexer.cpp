#include "lexer.hpp"
#include <cctype>

bool is_string_digit(std::string str) {
  for (const char &ch : str)
    if (!std::isdigit(ch))
      return false;
  return true;
}

frontend::lexer::Lexer &
frontend::lexer::Lexer::Get(std::unique_ptr<std::string> source) {
  static Lexer instance;
  return instance;
}

frontend::tokens::token_array_t frontend::lexer::Lexer::tokenize() {
  tokens::token_array_t m_tokens;
  std::string buffer;
  for (const char &ch : m_Source) {
    if (!(ch == ' ' || ch == '\t' || ch == '\n')) {
      buffer.clear();
      continue;
    } else if (ch == ';' || ch == '(' || ch == ')') {
      buffer.push_back(ch);
      seperate_source_string.push_back(buffer);
      buffer.clear();
      continue;
    }
    buffer.push_back(ch);
  }

  for (const std::string &str : seperate_source_string) {
    using namespace tokens;
    if (str == "exit") {
      m_tokens.emplace_back(Token{
          .type = TokenType::exit,
          .value = std::nullopt,
      });
    } else if (str == "print") {
      m_tokens.emplace_back(Token{
          .type = TokenType::print,
          .value = std::nullopt,
      });
    } else if (str == ";") {
      m_tokens.emplace_back(Token{
          .type = TokenType::semi,
          .value = std::nullopt,
      });
    } else if (str == "(") {
      m_tokens.emplace_back(Token{
          .type = TokenType::lparen,
          .value = std::nullopt,
      });
    } else if (str == ")") {
      m_tokens.emplace_back(Token{
          .type = TokenType::rparen,
          .value = std::nullopt,
      });
    } else if (is_string_digit(std::move(str))) {
      m_tokens.emplace_back(Token{
          .type = TokenType::rparen,
          .value = std::nullopt,
      });
    }
  }
  return m_tokens;
}
