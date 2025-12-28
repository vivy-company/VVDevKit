#include <tree_sitter/parser.h>
#include <wctype.h>
#include <stdio.h>
#include <string.h>

enum TokenType {
  BLOCK_COMMENT,
  STRING,
  CHARACTER,
  LPAREN,
  LPAREN_NEW,
  LSQUARE,
  LSQUARE_NEW
};

typedef struct {
  bool newline;
} scanner_t;

bool tree_sitter_ponylang_external_scanner_scan(
  void *payload,
  TSLexer *lexer,
  const bool *valid_symbols
) {
  // no null-check here
  scanner_t* s = (scanner_t*)payload;

  // skip whitespace, but mark if we found newlines
  while (iswspace(lexer->lookahead))
  {
    if(lexer->lookahead == '\n')
    {
      s->newline = true;
    }
    lexer->advance(lexer, true);
  }

  // handle left parentheses
  if((valid_symbols[LPAREN] || valid_symbols[LPAREN_NEW]) && lexer->lookahead == '(')
  {
    lexer->advance(lexer, false);
    if(s->newline)
    {
      lexer->result_symbol = LPAREN_NEW;
    }
    else
    {
      lexer->result_symbol = LPAREN;
    }
    s->newline = false;
    return true;
  }

  // handle left squares
  if((valid_symbols[LSQUARE] || valid_symbols[LSQUARE_NEW]) && lexer->lookahead == '[')
  {
    lexer->advance(lexer, false);
    if(s->newline)
    {
      lexer->result_symbol = LSQUARE_NEW;
    }
    else
    {
      lexer->result_symbol = LSQUARE;
    }
    s->newline = false;
    return true;
  }
  // we found some other character for which a previous newline doesn't really
  // matter
  s->newline = false;

  // handle block comments
  if (valid_symbols[BLOCK_COMMENT] && lexer->lookahead == '/')
  {
    lexer->advance(lexer, false);
    if (lexer->lookahead != '*')
    {
      return false;
    }
    lexer->advance(lexer, false);

    // we are inside a block comment
    bool after_asterisk = false;
    unsigned nesting_depth = 1;
    for (;;)
    {
      switch (lexer->lookahead)
      {
        case '\0':
          return false;
        case '*':
          lexer->advance(lexer, false);
          after_asterisk = true;
          break;
        case '/':
          if (after_asterisk)
          {
            lexer->advance(lexer, false);
            after_asterisk = false;
            nesting_depth--;
            if (nesting_depth == 0)
            {
              lexer->result_symbol = BLOCK_COMMENT;
              return true;
            }
          }
          else
          {
            lexer->advance(lexer, false);
            after_asterisk = false;
            if (lexer->lookahead == '*')
            {
              nesting_depth++;
              lexer->advance(lexer, false);
            }
          }
        default:
          lexer->advance(lexer, false);
          after_asterisk = false;
          break;
      }
    }
  }

  if (valid_symbols[CHARACTER] && lexer->lookahead == '\'')
  {
    // CHARACTER LITERAL 'A'
    lexer->advance(lexer, false);
    bool inside_escape = false;
    for (;;)
    {
      switch(lexer->lookahead)
      {
        case '\0':
          return false;
        case '\\':
          // escape
          lexer->advance(lexer, false);
          // toggle, as we are getting out of a quote when we have double
          // backslashes
          inside_escape = !inside_escape;
          break;
        case '\'':
          lexer->advance(lexer, false);
          // terminating single-quote
          if(!inside_escape)
          {
            lexer->result_symbol = CHARACTER;
            return true;
          }
          else
          {
            // leaving the escaped quote
            inside_escape = false;
          }
          break;
        default:
          lexer->advance(lexer, false);
          inside_escape = false;
          break;
      }
    }
  }
  else if (valid_symbols[STRING])
  {
    // handle strings, docstrings and quoting
    uint32_t quote_count = 0;
    while (lexer->lookahead == '"' && quote_count < 3) {
      quote_count++;
      lexer->advance(lexer, false);
    }

    switch (quote_count)
    {
      case 2:
        // empty string
        lexer->result_symbol = STRING;
        return true;
      case 1:
        // single quote string - handle quoting
        {
          bool escaped_quote = false;
          for (;;)
          {
            switch(lexer->lookahead)
            {
              case '\0':
                return false;
              case '\\':
                lexer->advance(lexer, false);
                // toggle, as we are getting out of a quote when we have double
                // backslashes
                escaped_quote = !escaped_quote;
                break;
              case '"':
                lexer->advance(lexer, false);
                if (!escaped_quote)
                {
                  // terminating quote
                  lexer->result_symbol = STRING;
                  return true;
                }
                else
                {
                  // we now leave the escaped quote
                  escaped_quote = false;
                }
                break;
              default:
                lexer->advance(lexer, false);
                escaped_quote = false;
                break;
            }
          }

          break;
        }
      case 3:
        // within docstring - no quoting
        {
          quote_count = 0;
          while (quote_count < 3) {
            if (lexer->lookahead == '"') {
              quote_count++;
              lexer->advance(lexer, false);
            } else {
              quote_count = 0;
              if (lexer->lookahead == 0) return false;
              lexer->advance(lexer, false);
            }
          }
          // consume additional quotes
          while (lexer->lookahead == '"')
            lexer->advance(lexer, false);

          lexer->result_symbol = STRING;
          return true;
        }
      default:
        // no quote
        return false;
    }
  }
  return false;
}


void *tree_sitter_ponylang_external_scanner_create() {
  scanner_t* s = malloc(sizeof(scanner_t));
  if(s != NULL)
  {
    s->newline = false;
  }
  return s;
}

void tree_sitter_ponylang_external_scanner_destroy(void *payload) {
  if(payload != NULL)
  {
    free(payload);
  }
}

unsigned tree_sitter_ponylang_external_scanner_serialize(
  void *payload,
  char *buffer
) {
  if(payload != NULL)
  {
    scanner_t* s = (scanner_t*)payload;
    memcpy(&buffer[0], &s->newline, sizeof(bool));
    return sizeof(bool);
  }
  return 0;
}

void tree_sitter_ponylang_external_scanner_deserialize(
  void *payload,
  const char *buffer,
  unsigned length
) {
  if(payload != NULL)
  {
    scanner_t* s = (scanner_t*)payload;
    memcpy(&s->newline, &buffer[0], length);
  }
}
