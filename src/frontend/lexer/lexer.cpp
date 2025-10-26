#include "lexer.hpp"
#include <cctype>
#include <optional>
#include <unordered_map>
#include <variant>

namespace frontend::lexer {

// Helper struct to detect numeric strings
struct digit_struct {
  bool isdigit = true; // true if the string is a valid number
  tokens::flag_t flag; // INT or DOUBLE
  std::variant<int, double, std::string> value; // parsed numeric value
};

// Checks whether a string represents a valid integer or floating-point number
digit_struct is_string_digit(const std::string &str) {
  digit_struct digit;
  bool seen_dot = false;

  for (const char &ch : str) {
    if (ch == '.') {
      if (seen_dot) { // more than one dot -> invalid
        digit.isdigit = false;
        return digit;
      }
      seen_dot = true;
      digit.flag = tokens::flag_t::DOUBLE;
    } else if (!std::isdigit(ch)) {
      digit.isdigit = false;
      return digit;
    }
  }

  if (digit.isdigit) {
    if (seen_dot) {
      digit.value = std::stod(str);
      digit.flag = tokens::flag_t::DOUBLE;
    } else {
      digit.value = std::stoi(str);
      digit.flag = tokens::flag_t::INT;
    }
  }

  return digit;
}

// Singleton getter for Lexer
Lexer &Lexer::Get(std::unique_ptr<std::string> source) {
  static Lexer instance;
  if (source) {
    instance.m_Source = *source; // assign source string
  }
  return instance;
}

// Tokenizes the source string into a vector of Tokens
tokens::token_array_t Lexer::tokenize() {
  tokens::token_array_t m_tokens;
  std::vector<std::string> separate_source_string;
  std::string buffer;

  // Step 1: Split source into tokens based on whitespace and delimiters
  for (const char &ch : m_Source) {
    if (ch == ' ' || ch == '\t' || ch == '\n') {
      if (!buffer.empty()) {
        separate_source_string.push_back(buffer);
        buffer.clear();
      }
    } else if (ch == ';' || ch == '(' || ch == ')' || ch == '{' || ch == '}') {
      if (!buffer.empty()) {
        separate_source_string.push_back(buffer);
        buffer.clear();
      }
      buffer.push_back(ch);
      separate_source_string.push_back(buffer);
      buffer.clear();
    } else {
      buffer.push_back(ch);
    }
  }
  if (!buffer.empty()) {
    separate_source_string.push_back(buffer);
  }

  // Step 2: Map strings to TokenType for operators and keywords
  static const std::unordered_map<std::string, tokens::TokenType> token_map = {
      {"exit", tokens::TokenType::exit},
      {"print", tokens::TokenType::print},
      {"let", tokens::TokenType::let},
      {";", tokens::TokenType::semi},
      {"(", tokens::TokenType::lparen},
      {")", tokens::TokenType::rparen},
      {"{", tokens::TokenType::lbrace},
      {"}", tokens::TokenType::rbrace},
      {"^", tokens::TokenType::exponentiation},
      {"^=", tokens::TokenType::exponentiation_equ},
      {"+", tokens::TokenType::plus},
      {"-", tokens::TokenType::minus},
      {"*", tokens::TokenType::multiply},
      {"/", tokens::TokenType::divide},
      {"=", tokens::TokenType::equ},
      {"+=", tokens::TokenType::plus_equ},
      {"-=", tokens::TokenType::minus_equ},
      {"*=", tokens::TokenType::multiply_equ},
      {"/=", tokens::TokenType::divide_equ},
      {"\"", tokens::TokenType::double_quotes},
      {"'", tokens::TokenType::single_quotes}};

  // Step 3: Convert string tokens into Token objects
  for (const std::string &str : separate_source_string) {
    using namespace tokens;

    // Check if token is a known operator or keyword
    auto it = token_map.find(str);
    if (it != token_map.end()) {
      m_tokens.emplace_back(Token{.type = it->second, .value = std::nullopt});
      continue;
    }

    // Check if token is a number
    digit_struct digit = is_string_digit(str);
    if (digit.isdigit) {
      m_tokens.emplace_back(Token{
          .type = (digit.flag == flag_t::INT) ? TokenType::int_lit
                                              : TokenType::double_lit,
          .value = std::make_optional(
              static_cast<tokens::literal_value_variant_t>(digit.value))});
      continue;
    }
    m_tokens.emplace_back(Token{.type = TokenType::let, .value = str});
  }

  return m_tokens;
}

} // namespace frontend::lexer
