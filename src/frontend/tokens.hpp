#ifndef TOKEN_HEADER_HXX
#define TOKEN_HEADER_HXX

#include <optional>
#include <variant>
#include <vector>

namespace frontend::tokens {
using literal_value_variant_t = std::variant<int>;

/* any value between 1 - 255 will be treated as error */
enum class TokenType {
  print = -1,
  exit = -2,
  int_lit = -3,
  lparen = -4,
  rparen = -5,
  semi = -6,
};

struct Token {
  TokenType type;
  std::optional<literal_value_variant_t> value;
};

using token_array_t = std::vector<Token>;
} // namespace frontend::tokens

#endif
