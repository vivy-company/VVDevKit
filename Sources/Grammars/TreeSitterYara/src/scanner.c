#include <tree_sitter/parser.h>
#include <wctype.h>

enum TokenType {
  STRING_CONTENT,
  PATTERN_CONTENT,
};

void *tree_sitter_yara_external_scanner_create() { return NULL; }
void tree_sitter_yara_external_scanner_destroy(void *p) {}
void tree_sitter_yara_external_scanner_reset(void *p) {}
unsigned tree_sitter_yara_external_scanner_serialize(void *p, char *buffer) { return 0; }
void tree_sitter_yara_external_scanner_deserialize(void *p, const char *b, unsigned n) {}

static void advance(TSLexer *lexer) { lexer->advance(lexer, false); }

bool tree_sitter_yara_external_scanner_scan(void *payload, TSLexer *lexer, const bool *valid_symbols) {
  if (valid_symbols[STRING_CONTENT]) {
    for (;;) {
      if (lexer->lookahead == '"' || lexer->lookahead == '\'') {
        break;
      } else if (lexer->lookahead == '\\') {
        advance(lexer);
        if (lexer->lookahead != 0) advance(lexer);
      } else if (lexer->lookahead == 0) {
        return false;
      } else {
        advance(lexer);
      }
    }
    lexer->result_symbol = STRING_CONTENT;
    return true;
  }

  if (valid_symbols[PATTERN_CONTENT]) {
    for (;;) {
      if (lexer->lookahead == '/') {
        break;
      } else if (lexer->lookahead == '\\') {
        advance(lexer);
        if (lexer->lookahead != 0) advance(lexer);
      } else if (lexer->lookahead == 0) {
        return false;
      } else {
        advance(lexer);
      }
    }
    lexer->result_symbol = PATTERN_CONTENT;
    return true;
  }

  return false;
}
