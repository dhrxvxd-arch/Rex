#ifndef TOKEN_HEADER_HXX
#define TOKEN_HEADER_HXX

#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace frontend::tokens {
using literal_value_variant_t = std::variant<int, double, std::string>;

/* any value between 1 - 255 will be treated as error */
enum class TokenType {
  print = -1,
  exit = -2,
  let = -3,
  int_lit = -4,
  double_lit = -5,
  lparen = -6,
  rparen = -7,
  lbrace = -8,
  rbrace = -9,
  semi = -10,
  plus = -11,
  minus = -12,
  multiply = -13,
  divide = -14,
  equ = -15,
  plus_equ = -16,
  minus_equ = -17,
  multiply_equ = -18,
  divide_equ = -19,
  double_quotes = -20,
  single_quotes = -21,
  exponentiation = -22,
  exponentiation_equ = -23,
};

struct Token {
  TokenType type;
  std::optional<literal_value_variant_t> value;
};

enum class flag_t {
  INT,
  DOUBLE,
};

using token_array_t = std::vector<Token>;
} // namespace frontend::tokens

#endif
