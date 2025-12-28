#include "tree_sitter/array.h"
#include "tree_sitter/parser.h"

#include <assert.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <wctype.h>

// Required by tree-sitter, the order and variant count here must match that of
// `../grammar.js:externals`, see there for docs on the variants.
enum TokenType {
    MUST_BE_FILLED_WITH_ACTUAL_VARIANTS,
};

// ================================================================================================
// DEBUG HELPER
// ================================================================================================

// Debug macro that either forwards to printf or does nothing depending on
// `DEBUG_PRINT`
static inline int debug(TSLexer *lexer, const char *format, ...) {
#define DEBUG_PRINT 1

#if DEBUG_PRINT == 1
    printf("col %3d: ", lexer->get_column(lexer));

    va_list args;
    va_start(args, format);
    int result = vprintf(format, args);
    va_end(args);

    printf("\n");

    return result;
#else
    return 0;
#endif

#undef DEBUG_PRINT
}

// ================================================================================================
// HELPER FUNCTIONS
// ================================================================================================

// Advance the lexer.
//
// Includes the current character in the text range associated with tokens
// emitted by the external scanner.
static inline void advance(TSLexer *lexer) { lexer->advance(lexer, false); }

// Advance the lexer, skipping the current character.
//
// The current character will be treated as whitespace; whitespace won’t be
// included in the text range associated with tokens emitted by the external
// scanner.
static inline void skip(TSLexer *lexer) { lexer->advance(lexer, true); }

// `true` if the lexer reached the end of the file.
//
// Prefer this to using `while (lexer->lookahead)`, to avoid failing on NUL
// bytes in files.
static inline bool eof(TSLexer *lexer) { return lexer->eof(lexer); }

// A function for marking the end of the recognized token. This allows matching
// tokens that require multiple characters of lookahead.
static inline void mark_end(TSLexer *lexer) { lexer->mark_end(lexer); }

// ================================================================================================
// FUNCTIONS REQUIRED BY TREE SITTER
// ================================================================================================

// Allocate the state for our custom scanner, if any.
//
// This is only called once per language initialization so the scanner must be
// able to handle nested state if it can happen.
void *tree_sitter_just_external_scanner_create() { return NULL; }

// Free the custom scanner.
void tree_sitter_just_external_scanner_destroy(void *payload) {}

unsigned tree_sitter_just_external_scanner_serialize(void *payload,
                                                     char *buffer) {
    return 0;
}

void tree_sitter_just_external_scanner_deserialize(void *payload,
                                                   const char *buffer,
                                                   unsigned length) {}

// ================================================================================================
// SCANNING FUNCTION
//
// The most important function, responsible for actually producing tokens.
// ================================================================================================

// Docs:
// <https://tree-sitter.github.io/tree-sitter/creating-parsers#external-scanners>
bool tree_sitter_just_external_scanner_scan(void *payload, TSLexer *lexer,
                                            const bool *valid_symbols) {
    return false;
}
