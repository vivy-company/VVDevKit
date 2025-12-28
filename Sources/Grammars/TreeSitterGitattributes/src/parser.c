#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 13
#define STATE_COUNT 112
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 62
#define ALIAS_COUNT 1
#define TOKEN_COUNT 36
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 3
#define MAX_ALIAS_SEQUENCE_LENGTH 5
#define PRODUCTION_ID_COUNT 20

enum {
  aux_sym__line_token1 = 1,
  aux_sym__line_token2 = 2,
  sym_comment = 3,
  anon_sym_DASH = 4,
  anon_sym_BANG = 5,
  anon_sym_EQ = 6,
  anon_sym_DQUOTE = 7,
  sym_attribute = 8,
  sym_value = 9,
  sym_directory_separator = 10,
  sym_directory_separator_escaped = 11,
  sym_pattern_char = 12,
  anon_sym_BSLASH = 13,
  aux_sym_pattern_char_escaped_token1 = 14,
  anon_sym_QMARK = 15,
  anon_sym_STAR = 16,
  anon_sym_STAR_STAR = 17,
  anon_sym_LBRACK = 18,
  anon_sym_CARET = 19,
  anon_sym_RBRACK = 20,
  sym_bracket_char = 21,
  anon_sym_LBRACK_COLON = 22,
  anon_sym_alnum = 23,
  anon_sym_COLON_RBRACK = 24,
  anon_sym_alpha = 25,
  anon_sym_blank = 26,
  anon_sym_cntrl = 27,
  anon_sym_digit = 28,
  anon_sym_graph = 29,
  anon_sym_lower = 30,
  anon_sym_print = 31,
  anon_sym_punct = 32,
  anon_sym_space = 33,
  anon_sym_upper = 34,
  anon_sym_xdigit = 35,
  sym_document = 36,
  sym__line = 37,
  sym_attributes_line = 38,
  sym__attribute_declaration = 39,
  sym_attribute_set = 40,
  sym_attribute_unset = 41,
  sym_attribute_set_to = 42,
  sym_quoted_pattern = 43,
  sym_pattern = 44,
  sym__directory_separator = 45,
  aux_sym__pattern = 46,
  sym_pattern_char_escaped = 47,
  sym__wildcard = 48,
  sym_bracket_expr = 49,
  sym__bracket_pattern = 50,
  sym__bracket_pattern_closing_bracket = 51,
  sym__bracket_char_closing_bracket = 52,
  sym__bracket_range_closing_bracket = 53,
  sym__bracket_char = 54,
  sym_bracket_char_escaped = 55,
  sym_bracket_range = 56,
  sym_bracket_char_class = 57,
  aux_sym_document_repeat1 = 58,
  aux_sym_attributes_line_repeat1 = 59,
  aux_sym_pattern_repeat1 = 60,
  aux_sym_bracket_expr_repeat1 = 61,
  alias_sym_negation = 62,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [aux_sym__line_token1] = "_line_token1",
  [aux_sym__line_token2] = "_line_token2",
  [sym_comment] = "comment",
  [anon_sym_DASH] = "-",
  [anon_sym_BANG] = "!",
  [anon_sym_EQ] = "=",
  [anon_sym_DQUOTE] = "\"",
  [sym_attribute] = "attribute",
  [sym_value] = "value",
  [sym_directory_separator] = "directory_separator",
  [sym_directory_separator_escaped] = "directory_separator_escaped",
  [sym_pattern_char] = "pattern_char",
  [anon_sym_BSLASH] = "\\",
  [aux_sym_pattern_char_escaped_token1] = "pattern_char_escaped_token1",
  [anon_sym_QMARK] = "wildcard_char_single",
  [anon_sym_STAR] = "wildcard_chars",
  [anon_sym_STAR_STAR] = "wildcard_chars_allow_slash",
  [anon_sym_LBRACK] = "[",
  [anon_sym_CARET] = "bracket_negation",
  [anon_sym_RBRACK] = "]",
  [sym_bracket_char] = "bracket_char",
  [anon_sym_LBRACK_COLON] = "[:",
  [anon_sym_alnum] = "alnum",
  [anon_sym_COLON_RBRACK] = ":]",
  [anon_sym_alpha] = "alpha",
  [anon_sym_blank] = "blank",
  [anon_sym_cntrl] = "cntrl",
  [anon_sym_digit] = "digit",
  [anon_sym_graph] = "graph",
  [anon_sym_lower] = "lower",
  [anon_sym_print] = "print",
  [anon_sym_punct] = "punct",
  [anon_sym_space] = "space",
  [anon_sym_upper] = "upper",
  [anon_sym_xdigit] = "xdigit",
  [sym_document] = "document",
  [sym__line] = "_line",
  [sym_attributes_line] = "attributes_line",
  [sym__attribute_declaration] = "_attribute_declaration",
  [sym_attribute_set] = "attribute_set",
  [sym_attribute_unset] = "attribute_unset",
  [sym_attribute_set_to] = "attribute_set_to",
  [sym_quoted_pattern] = "quoted_pattern",
  [sym_pattern] = "pattern",
  [sym__directory_separator] = "_directory_separator",
  [aux_sym__pattern] = "_pattern",
  [sym_pattern_char_escaped] = "pattern_char_escaped",
  [sym__wildcard] = "_wildcard",
  [sym_bracket_expr] = "bracket_expr",
  [sym__bracket_pattern] = "_bracket_pattern",
  [sym__bracket_pattern_closing_bracket] = "_bracket_pattern_closing_bracket",
  [sym__bracket_char_closing_bracket] = "_bracket_char_closing_bracket",
  [sym__bracket_range_closing_bracket] = "bracket_range",
  [sym__bracket_char] = "_bracket_char",
  [sym_bracket_char_escaped] = "bracket_char_escaped",
  [sym_bracket_range] = "bracket_range",
  [sym_bracket_char_class] = "bracket_char_class",
  [aux_sym_document_repeat1] = "document_repeat1",
  [aux_sym_attributes_line_repeat1] = "attributes_line_repeat1",
  [aux_sym_pattern_repeat1] = "pattern_repeat1",
  [aux_sym_bracket_expr_repeat1] = "bracket_expr_repeat1",
  [alias_sym_negation] = "negation",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [aux_sym__line_token1] = aux_sym__line_token1,
  [aux_sym__line_token2] = aux_sym__line_token2,
  [sym_comment] = sym_comment,
  [anon_sym_DASH] = anon_sym_DASH,
  [anon_sym_BANG] = anon_sym_BANG,
  [anon_sym_EQ] = anon_sym_EQ,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [sym_attribute] = sym_attribute,
  [sym_value] = sym_value,
  [sym_directory_separator] = sym_directory_separator,
  [sym_directory_separator_escaped] = sym_directory_separator_escaped,
  [sym_pattern_char] = sym_pattern_char,
  [anon_sym_BSLASH] = anon_sym_BSLASH,
  [aux_sym_pattern_char_escaped_token1] = aux_sym_pattern_char_escaped_token1,
  [anon_sym_QMARK] = anon_sym_QMARK,
  [anon_sym_STAR] = anon_sym_STAR,
  [anon_sym_STAR_STAR] = anon_sym_STAR_STAR,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_CARET] = anon_sym_CARET,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [sym_bracket_char] = sym_bracket_char,
  [anon_sym_LBRACK_COLON] = anon_sym_LBRACK_COLON,
  [anon_sym_alnum] = anon_sym_alnum,
  [anon_sym_COLON_RBRACK] = anon_sym_COLON_RBRACK,
  [anon_sym_alpha] = anon_sym_alpha,
  [anon_sym_blank] = anon_sym_blank,
  [anon_sym_cntrl] = anon_sym_cntrl,
  [anon_sym_digit] = anon_sym_digit,
  [anon_sym_graph] = anon_sym_graph,
  [anon_sym_lower] = anon_sym_lower,
  [anon_sym_print] = anon_sym_print,
  [anon_sym_punct] = anon_sym_punct,
  [anon_sym_space] = anon_sym_space,
  [anon_sym_upper] = anon_sym_upper,
  [anon_sym_xdigit] = anon_sym_xdigit,
  [sym_document] = sym_document,
  [sym__line] = sym__line,
  [sym_attributes_line] = sym_attributes_line,
  [sym__attribute_declaration] = sym__attribute_declaration,
  [sym_attribute_set] = sym_attribute_set,
  [sym_attribute_unset] = sym_attribute_unset,
  [sym_attribute_set_to] = sym_attribute_set_to,
  [sym_quoted_pattern] = sym_quoted_pattern,
  [sym_pattern] = sym_pattern,
  [sym__directory_separator] = sym__directory_separator,
  [aux_sym__pattern] = aux_sym__pattern,
  [sym_pattern_char_escaped] = sym_pattern_char_escaped,
  [sym__wildcard] = sym__wildcard,
  [sym_bracket_expr] = sym_bracket_expr,
  [sym__bracket_pattern] = sym__bracket_pattern,
  [sym__bracket_pattern_closing_bracket] = sym__bracket_pattern_closing_bracket,
  [sym__bracket_char_closing_bracket] = sym__bracket_char_closing_bracket,
  [sym__bracket_range_closing_bracket] = sym_bracket_range,
  [sym__bracket_char] = sym__bracket_char,
  [sym_bracket_char_escaped] = sym_bracket_char_escaped,
  [sym_bracket_range] = sym_bracket_range,
  [sym_bracket_char_class] = sym_bracket_char_class,
  [aux_sym_document_repeat1] = aux_sym_document_repeat1,
  [aux_sym_attributes_line_repeat1] = aux_sym_attributes_line_repeat1,
  [aux_sym_pattern_repeat1] = aux_sym_pattern_repeat1,
  [aux_sym_bracket_expr_repeat1] = aux_sym_bracket_expr_repeat1,
  [alias_sym_negation] = alias_sym_negation,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [aux_sym__line_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__line_token2] = {
    .visible = false,
    .named = false,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_DASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BANG] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [sym_attribute] = {
    .visible = true,
    .named = true,
  },
  [sym_value] = {
    .visible = true,
    .named = true,
  },
  [sym_directory_separator] = {
    .visible = true,
    .named = true,
  },
  [sym_directory_separator_escaped] = {
    .visible = true,
    .named = true,
  },
  [sym_pattern_char] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_BSLASH] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_pattern_char_escaped_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_QMARK] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_STAR] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_STAR_STAR] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_CARET] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [sym_bracket_char] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LBRACK_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_alnum] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_alpha] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_blank] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_cntrl] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_digit] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_graph] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_lower] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_print] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_punct] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_space] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_upper] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_xdigit] = {
    .visible = true,
    .named = false,
  },
  [sym_document] = {
    .visible = true,
    .named = true,
  },
  [sym__line] = {
    .visible = false,
    .named = true,
  },
  [sym_attributes_line] = {
    .visible = true,
    .named = true,
  },
  [sym__attribute_declaration] = {
    .visible = false,
    .named = true,
  },
  [sym_attribute_set] = {
    .visible = true,
    .named = true,
  },
  [sym_attribute_unset] = {
    .visible = true,
    .named = true,
  },
  [sym_attribute_set_to] = {
    .visible = true,
    .named = true,
  },
  [sym_quoted_pattern] = {
    .visible = true,
    .named = true,
  },
  [sym_pattern] = {
    .visible = true,
    .named = true,
  },
  [sym__directory_separator] = {
    .visible = false,
    .named = true,
  },
  [aux_sym__pattern] = {
    .visible = false,
    .named = false,
  },
  [sym_pattern_char_escaped] = {
    .visible = true,
    .named = true,
  },
  [sym__wildcard] = {
    .visible = false,
    .named = true,
  },
  [sym_bracket_expr] = {
    .visible = true,
    .named = true,
  },
  [sym__bracket_pattern] = {
    .visible = false,
    .named = true,
  },
  [sym__bracket_pattern_closing_bracket] = {
    .visible = false,
    .named = true,
  },
  [sym__bracket_char_closing_bracket] = {
    .visible = false,
    .named = true,
  },
  [sym__bracket_range_closing_bracket] = {
    .visible = true,
    .named = true,
  },
  [sym__bracket_char] = {
    .visible = false,
    .named = true,
  },
  [sym_bracket_char_escaped] = {
    .visible = true,
    .named = true,
  },
  [sym_bracket_range] = {
    .visible = true,
    .named = true,
  },
  [sym_bracket_char_class] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_document_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_attributes_line_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_pattern_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_bracket_expr_repeat1] = {
    .visible = false,
    .named = false,
  },
  [alias_sym_negation] = {
    .visible = true,
    .named = true,
  },
};

enum {
  field_directory_flag = 1,
  field_name = 2,
  field_relative_flag = 3,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_directory_flag] = "directory_flag",
  [field_name] = "name",
  [field_relative_flag] = "relative_flag",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [3] = {.index = 0, .length = 1},
  [4] = {.index = 1, .length = 1},
  [5] = {.index = 2, .length = 1},
  [6] = {.index = 3, .length = 1},
  [7] = {.index = 4, .length = 1},
  [8] = {.index = 5, .length = 1},
  [9] = {.index = 6, .length = 2},
  [10] = {.index = 8, .length = 2},
  [11] = {.index = 10, .length = 2},
  [12] = {.index = 12, .length = 2},
  [13] = {.index = 14, .length = 2},
  [14] = {.index = 16, .length = 2},
  [15] = {.index = 18, .length = 2},
  [17] = {.index = 20, .length = 1},
  [18] = {.index = 21, .length = 3},
  [19] = {.index = 24, .length = 3},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_relative_flag, 0},
  [1] =
    {field_directory_flag, 1},
  [2] =
    {field_relative_flag, 1, .inherited = true},
  [3] =
    {field_relative_flag, 1},
  [4] =
    {field_directory_flag, 2},
  [5] =
    {field_relative_flag, 2, .inherited = true},
  [6] =
    {field_directory_flag, 2},
    {field_relative_flag, 0},
  [8] =
    {field_relative_flag, 0},
    {field_relative_flag, 2, .inherited = true},
  [10] =
    {field_directory_flag, 2},
    {field_relative_flag, 1, .inherited = true},
  [12] =
    {field_relative_flag, 0, .inherited = true},
    {field_relative_flag, 1, .inherited = true},
  [14] =
    {field_directory_flag, 3},
    {field_relative_flag, 1},
  [16] =
    {field_relative_flag, 1},
    {field_relative_flag, 3, .inherited = true},
  [18] =
    {field_directory_flag, 3},
    {field_relative_flag, 2, .inherited = true},
  [20] =
    {field_name, 1},
  [21] =
    {field_directory_flag, 3},
    {field_relative_flag, 0},
    {field_relative_flag, 2, .inherited = true},
  [24] =
    {field_directory_flag, 4},
    {field_relative_flag, 1},
    {field_relative_flag, 3, .inherited = true},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
  [1] = {
    [0] = alias_sym_negation,
  },
  [2] = {
    [0] = sym_bracket_char,
  },
  [6] = {
    [0] = alias_sym_negation,
  },
  [7] = {
    [0] = alias_sym_negation,
  },
  [8] = {
    [0] = alias_sym_negation,
  },
  [13] = {
    [0] = alias_sym_negation,
  },
  [14] = {
    [0] = alias_sym_negation,
  },
  [15] = {
    [0] = alias_sym_negation,
  },
  [16] = {
    [1] = anon_sym_CARET,
  },
  [19] = {
    [0] = alias_sym_negation,
  },
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(63);
      if (lookahead == '\n') ADVANCE(65);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == '!') ADVANCE(68);
      if (lookahead == '"') ADVANCE(70);
      if (lookahead == '#') ADVANCE(66);
      if (lookahead == '*') ADVANCE(80);
      if (lookahead == '-') ADVANCE(67);
      if (lookahead == '/') ADVANCE(73);
      if (lookahead == '=') ADVANCE(69);
      if (lookahead == '?') ADVANCE(79);
      if (lookahead == '[') ADVANCE(83);
      if (lookahead == '\\') ADVANCE(76);
      if (lookahead == ']') ADVANCE(85);
      if (lookahead == '^') ADVANCE(84);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(64);
      if (lookahead != 0) ADVANCE(75);
      END_STATE();
    case 1:
      if (lookahead == '\n') ADVANCE(65);
      END_STATE();
    case 2:
      if (lookahead == '\n') ADVANCE(65);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == '*') ADVANCE(81);
      if (lookahead == '/') ADVANCE(73);
      if (lookahead == '?') ADVANCE(79);
      if (lookahead == '[') ADVANCE(83);
      if (lookahead == '\\') ADVANCE(77);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(64);
      if (lookahead != 0) ADVANCE(75);
      END_STATE();
    case 3:
      if (lookahead == '\n') ADVANCE(65);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == '*') ADVANCE(81);
      if (lookahead == '?') ADVANCE(79);
      if (lookahead == '[') ADVANCE(83);
      if (lookahead == '\\') ADVANCE(76);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(64);
      if (lookahead != 0 &&
          lookahead != '/') ADVANCE(75);
      END_STATE();
    case 4:
      if (lookahead == '\n') ADVANCE(65);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == ':') ADVANCE(13);
      if (lookahead == '=') ADVANCE(69);
      if (lookahead == 'a') ADVANCE(34);
      if (lookahead == 'b') ADVANCE(35);
      if (lookahead == 'c') ADVANCE(38);
      if (lookahead == 'd') ADVANCE(28);
      if (lookahead == 'g') ADVANCE(51);
      if (lookahead == 'l') ADVANCE(43);
      if (lookahead == 'p') ADVANCE(50);
      if (lookahead == 's') ADVANCE(46);
      if (lookahead == 'u') ADVANCE(45);
      if (lookahead == 'x') ADVANCE(20);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(64);
      END_STATE();
    case 5:
      if (lookahead == '!') ADVANCE(68);
      if (lookahead == '*') ADVANCE(81);
      if (lookahead == '/') ADVANCE(73);
      if (lookahead == '?') ADVANCE(79);
      if (lookahead == '[') ADVANCE(83);
      if (lookahead == '\\') ADVANCE(77);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(75);
      END_STATE();
    case 6:
      if (lookahead == '!') ADVANCE(68);
      if (lookahead == '-') ADVANCE(67);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '=') ADVANCE(71);
      END_STATE();
    case 7:
      if (lookahead == '!') ADVANCE(68);
      if (lookahead == '[') ADVANCE(87);
      if (lookahead == '\\') ADVANCE(76);
      if (lookahead == ']') ADVANCE(85);
      if (lookahead == '^') ADVANCE(84);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '/') ADVANCE(86);
      END_STATE();
    case 8:
      if (lookahead == '"') ADVANCE(70);
      if (lookahead == '*') ADVANCE(81);
      if (lookahead == '/') ADVANCE(73);
      if (lookahead == '?') ADVANCE(79);
      if (lookahead == '[') ADVANCE(83);
      if (lookahead == '\\') ADVANCE(77);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(75);
      END_STATE();
    case 9:
      if (lookahead == '"') ADVANCE(70);
      if (lookahead == '*') ADVANCE(81);
      if (lookahead == '?') ADVANCE(79);
      if (lookahead == '[') ADVANCE(83);
      if (lookahead == '\\') ADVANCE(76);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '/') ADVANCE(75);
      END_STATE();
    case 10:
      if (lookahead == '-') ADVANCE(67);
      if (lookahead == '[') ADVANCE(87);
      if (lookahead == '\\') ADVANCE(76);
      if (lookahead == ']') ADVANCE(85);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '/') ADVANCE(86);
      END_STATE();
    case 11:
      if (lookahead == '[') ADVANCE(87);
      if (lookahead == '\\') ADVANCE(76);
      if (lookahead == ']') ADVANCE(85);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '/') ADVANCE(86);
      END_STATE();
    case 12:
      if (lookahead == '\\') ADVANCE(76);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '/' &&
          lookahead != ']') ADVANCE(86);
      END_STATE();
    case 13:
      if (lookahead == ']') ADVANCE(90);
      END_STATE();
    case 14:
      if (lookahead == 'a') ADVANCE(91);
      END_STATE();
    case 15:
      if (lookahead == 'a') ADVANCE(18);
      END_STATE();
    case 16:
      if (lookahead == 'a') ADVANCE(41);
      END_STATE();
    case 17:
      if (lookahead == 'a') ADVANCE(44);
      END_STATE();
    case 18:
      if (lookahead == 'c') ADVANCE(21);
      END_STATE();
    case 19:
      if (lookahead == 'c') ADVANCE(55);
      END_STATE();
    case 20:
      if (lookahead == 'd') ADVANCE(32);
      END_STATE();
    case 21:
      if (lookahead == 'e') ADVANCE(99);
      END_STATE();
    case 22:
      if (lookahead == 'e') ADVANCE(48);
      END_STATE();
    case 23:
      if (lookahead == 'e') ADVANCE(49);
      END_STATE();
    case 24:
      if (lookahead == 'g') ADVANCE(29);
      END_STATE();
    case 25:
      if (lookahead == 'g') ADVANCE(30);
      END_STATE();
    case 26:
      if (lookahead == 'h') ADVANCE(95);
      END_STATE();
    case 27:
      if (lookahead == 'h') ADVANCE(14);
      END_STATE();
    case 28:
      if (lookahead == 'i') ADVANCE(24);
      END_STATE();
    case 29:
      if (lookahead == 'i') ADVANCE(53);
      END_STATE();
    case 30:
      if (lookahead == 'i') ADVANCE(56);
      END_STATE();
    case 31:
      if (lookahead == 'i') ADVANCE(42);
      END_STATE();
    case 32:
      if (lookahead == 'i') ADVANCE(25);
      END_STATE();
    case 33:
      if (lookahead == 'k') ADVANCE(92);
      END_STATE();
    case 34:
      if (lookahead == 'l') ADVANCE(39);
      END_STATE();
    case 35:
      if (lookahead == 'l') ADVANCE(16);
      END_STATE();
    case 36:
      if (lookahead == 'l') ADVANCE(93);
      END_STATE();
    case 37:
      if (lookahead == 'm') ADVANCE(89);
      END_STATE();
    case 38:
      if (lookahead == 'n') ADVANCE(57);
      END_STATE();
    case 39:
      if (lookahead == 'n') ADVANCE(58);
      if (lookahead == 'p') ADVANCE(27);
      END_STATE();
    case 40:
      if (lookahead == 'n') ADVANCE(19);
      END_STATE();
    case 41:
      if (lookahead == 'n') ADVANCE(33);
      END_STATE();
    case 42:
      if (lookahead == 'n') ADVANCE(54);
      END_STATE();
    case 43:
      if (lookahead == 'o') ADVANCE(59);
      END_STATE();
    case 44:
      if (lookahead == 'p') ADVANCE(26);
      END_STATE();
    case 45:
      if (lookahead == 'p') ADVANCE(47);
      END_STATE();
    case 46:
      if (lookahead == 'p') ADVANCE(15);
      END_STATE();
    case 47:
      if (lookahead == 'p') ADVANCE(23);
      END_STATE();
    case 48:
      if (lookahead == 'r') ADVANCE(96);
      END_STATE();
    case 49:
      if (lookahead == 'r') ADVANCE(100);
      END_STATE();
    case 50:
      if (lookahead == 'r') ADVANCE(31);
      if (lookahead == 'u') ADVANCE(40);
      END_STATE();
    case 51:
      if (lookahead == 'r') ADVANCE(17);
      END_STATE();
    case 52:
      if (lookahead == 'r') ADVANCE(36);
      END_STATE();
    case 53:
      if (lookahead == 't') ADVANCE(94);
      END_STATE();
    case 54:
      if (lookahead == 't') ADVANCE(97);
      END_STATE();
    case 55:
      if (lookahead == 't') ADVANCE(98);
      END_STATE();
    case 56:
      if (lookahead == 't') ADVANCE(101);
      END_STATE();
    case 57:
      if (lookahead == 't') ADVANCE(52);
      END_STATE();
    case 58:
      if (lookahead == 'u') ADVANCE(37);
      END_STATE();
    case 59:
      if (lookahead == 'w') ADVANCE(22);
      END_STATE();
    case 60:
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '/') ADVANCE(78);
      END_STATE();
    case 61:
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(72);
      END_STATE();
    case 62:
      if (eof) ADVANCE(63);
      if (lookahead == '\n') ADVANCE(65);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == '!') ADVANCE(68);
      if (lookahead == '"') ADVANCE(70);
      if (lookahead == '#') ADVANCE(66);
      if (lookahead == '*') ADVANCE(81);
      if (lookahead == '/') ADVANCE(73);
      if (lookahead == '?') ADVANCE(79);
      if (lookahead == '[') ADVANCE(83);
      if (lookahead == '\\') ADVANCE(77);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(64);
      if (lookahead != 0) ADVANCE(75);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(aux_sym__line_token1);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(64);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(aux_sym__line_token2);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(66);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(anon_sym_BANG);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(sym_attribute);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '=') ADVANCE(71);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(sym_value);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(72);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(sym_directory_separator);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(sym_directory_separator_escaped);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(sym_pattern_char);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(anon_sym_BSLASH);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(anon_sym_BSLASH);
      if (lookahead == '/') ADVANCE(74);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(aux_sym_pattern_char_escaped_token1);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(anon_sym_QMARK);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(anon_sym_STAR);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(anon_sym_STAR);
      if (lookahead == '*') ADVANCE(82);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(anon_sym_STAR_STAR);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(anon_sym_CARET);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(sym_bracket_char);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(sym_bracket_char);
      if (lookahead == ':') ADVANCE(88);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(anon_sym_LBRACK_COLON);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(anon_sym_alnum);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(anon_sym_COLON_RBRACK);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(anon_sym_alpha);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(anon_sym_blank);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(anon_sym_cntrl);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(anon_sym_digit);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(anon_sym_graph);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(anon_sym_lower);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(anon_sym_print);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(anon_sym_punct);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(anon_sym_space);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(anon_sym_upper);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(anon_sym_xdigit);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 62},
  [2] = {.lex_state = 62},
  [3] = {.lex_state = 62},
  [4] = {.lex_state = 2},
  [5] = {.lex_state = 2},
  [6] = {.lex_state = 2},
  [7] = {.lex_state = 2},
  [8] = {.lex_state = 5},
  [9] = {.lex_state = 8},
  [10] = {.lex_state = 7},
  [11] = {.lex_state = 8},
  [12] = {.lex_state = 8},
  [13] = {.lex_state = 8},
  [14] = {.lex_state = 7},
  [15] = {.lex_state = 2},
  [16] = {.lex_state = 62},
  [17] = {.lex_state = 2},
  [18] = {.lex_state = 62},
  [19] = {.lex_state = 8},
  [20] = {.lex_state = 11},
  [21] = {.lex_state = 8},
  [22] = {.lex_state = 11},
  [23] = {.lex_state = 2},
  [24] = {.lex_state = 2},
  [25] = {.lex_state = 3},
  [26] = {.lex_state = 3},
  [27] = {.lex_state = 4},
  [28] = {.lex_state = 3},
  [29] = {.lex_state = 3},
  [30] = {.lex_state = 3},
  [31] = {.lex_state = 3},
  [32] = {.lex_state = 3},
  [33] = {.lex_state = 3},
  [34] = {.lex_state = 9},
  [35] = {.lex_state = 9},
  [36] = {.lex_state = 9},
  [37] = {.lex_state = 9},
  [38] = {.lex_state = 9},
  [39] = {.lex_state = 9},
  [40] = {.lex_state = 9},
  [41] = {.lex_state = 9},
  [42] = {.lex_state = 2},
  [43] = {.lex_state = 3},
  [44] = {.lex_state = 2},
  [45] = {.lex_state = 11},
  [46] = {.lex_state = 11},
  [47] = {.lex_state = 11},
  [48] = {.lex_state = 11},
  [49] = {.lex_state = 11},
  [50] = {.lex_state = 11},
  [51] = {.lex_state = 11},
  [52] = {.lex_state = 3},
  [53] = {.lex_state = 11},
  [54] = {.lex_state = 3},
  [55] = {.lex_state = 3},
  [56] = {.lex_state = 11},
  [57] = {.lex_state = 11},
  [58] = {.lex_state = 11},
  [59] = {.lex_state = 2},
  [60] = {.lex_state = 11},
  [61] = {.lex_state = 2},
  [62] = {.lex_state = 3},
  [63] = {.lex_state = 3},
  [64] = {.lex_state = 11},
  [65] = {.lex_state = 2},
  [66] = {.lex_state = 8},
  [67] = {.lex_state = 8},
  [68] = {.lex_state = 8},
  [69] = {.lex_state = 8},
  [70] = {.lex_state = 8},
  [71] = {.lex_state = 6},
  [72] = {.lex_state = 62},
  [73] = {.lex_state = 62},
  [74] = {.lex_state = 62},
  [75] = {.lex_state = 62},
  [76] = {.lex_state = 62},
  [77] = {.lex_state = 62},
  [78] = {.lex_state = 10},
  [79] = {.lex_state = 62},
  [80] = {.lex_state = 62},
  [81] = {.lex_state = 62},
  [82] = {.lex_state = 62},
  [83] = {.lex_state = 10},
  [84] = {.lex_state = 10},
  [85] = {.lex_state = 10},
  [86] = {.lex_state = 11},
  [87] = {.lex_state = 11},
  [88] = {.lex_state = 11},
  [89] = {.lex_state = 11},
  [90] = {.lex_state = 12},
  [91] = {.lex_state = 12},
  [92] = {.lex_state = 0},
  [93] = {.lex_state = 4},
  [94] = {.lex_state = 0},
  [95] = {.lex_state = 0},
  [96] = {.lex_state = 0},
  [97] = {.lex_state = 0},
  [98] = {.lex_state = 0},
  [99] = {.lex_state = 0},
  [100] = {.lex_state = 0},
  [101] = {.lex_state = 61},
  [102] = {.lex_state = 0},
  [103] = {.lex_state = 60},
  [104] = {.lex_state = 60},
  [105] = {.lex_state = 4},
  [106] = {.lex_state = 60},
  [107] = {.lex_state = 62},
  [108] = {.lex_state = 0},
  [109] = {.lex_state = 6},
  [110] = {.lex_state = 0},
  [111] = {.lex_state = 60},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [aux_sym__line_token1] = ACTIONS(1),
    [aux_sym__line_token2] = ACTIONS(1),
    [sym_comment] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [anon_sym_BANG] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [sym_directory_separator] = ACTIONS(1),
    [sym_pattern_char] = ACTIONS(1),
    [anon_sym_BSLASH] = ACTIONS(1),
    [aux_sym_pattern_char_escaped_token1] = ACTIONS(1),
    [anon_sym_QMARK] = ACTIONS(1),
    [anon_sym_STAR] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_CARET] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [sym_bracket_char] = ACTIONS(1),
  },
  [1] = {
    [sym_document] = STATE(110),
    [sym__line] = STATE(2),
    [sym_attributes_line] = STATE(100),
    [sym_quoted_pattern] = STATE(94),
    [sym_pattern] = STATE(94),
    [sym__directory_separator] = STATE(54),
    [aux_sym__pattern] = STATE(5),
    [sym_pattern_char_escaped] = STATE(5),
    [sym__wildcard] = STATE(5),
    [sym_bracket_expr] = STATE(5),
    [aux_sym_document_repeat1] = STATE(2),
    [ts_builtin_sym_end] = ACTIONS(3),
    [aux_sym__line_token1] = ACTIONS(5),
    [aux_sym__line_token2] = ACTIONS(7),
    [sym_comment] = ACTIONS(9),
    [anon_sym_BANG] = ACTIONS(11),
    [anon_sym_DQUOTE] = ACTIONS(13),
    [sym_directory_separator] = ACTIONS(15),
    [sym_directory_separator_escaped] = ACTIONS(15),
    [sym_pattern_char] = ACTIONS(17),
    [anon_sym_BSLASH] = ACTIONS(19),
    [anon_sym_QMARK] = ACTIONS(21),
    [anon_sym_STAR] = ACTIONS(17),
    [anon_sym_STAR_STAR] = ACTIONS(21),
    [anon_sym_LBRACK] = ACTIONS(23),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 16,
    ACTIONS(5), 1,
      aux_sym__line_token1,
    ACTIONS(9), 1,
      sym_comment,
    ACTIONS(11), 1,
      anon_sym_BANG,
    ACTIONS(13), 1,
      anon_sym_DQUOTE,
    ACTIONS(19), 1,
      anon_sym_BSLASH,
    ACTIONS(23), 1,
      anon_sym_LBRACK,
    ACTIONS(25), 1,
      ts_builtin_sym_end,
    ACTIONS(27), 1,
      aux_sym__line_token2,
    STATE(54), 1,
      sym__directory_separator,
    STATE(100), 1,
      sym_attributes_line,
    ACTIONS(15), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
    ACTIONS(17), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(21), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    STATE(3), 2,
      sym__line,
      aux_sym_document_repeat1,
    STATE(94), 2,
      sym_quoted_pattern,
      sym_pattern,
    STATE(5), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [57] = 16,
    ACTIONS(29), 1,
      ts_builtin_sym_end,
    ACTIONS(31), 1,
      aux_sym__line_token1,
    ACTIONS(34), 1,
      aux_sym__line_token2,
    ACTIONS(37), 1,
      sym_comment,
    ACTIONS(40), 1,
      anon_sym_BANG,
    ACTIONS(43), 1,
      anon_sym_DQUOTE,
    ACTIONS(52), 1,
      anon_sym_BSLASH,
    ACTIONS(58), 1,
      anon_sym_LBRACK,
    STATE(54), 1,
      sym__directory_separator,
    STATE(100), 1,
      sym_attributes_line,
    ACTIONS(46), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
    ACTIONS(49), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(55), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    STATE(3), 2,
      sym__line,
      aux_sym_document_repeat1,
    STATE(94), 2,
      sym_quoted_pattern,
      sym_pattern,
    STATE(5), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [114] = 9,
    ACTIONS(19), 1,
      anon_sym_BSLASH,
    ACTIONS(23), 1,
      anon_sym_LBRACK,
    STATE(30), 1,
      sym__directory_separator,
    STATE(76), 1,
      aux_sym_pattern_repeat1,
    ACTIONS(61), 2,
      aux_sym__line_token1,
      aux_sym__line_token2,
    ACTIONS(63), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
    ACTIONS(65), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(67), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    STATE(17), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [149] = 9,
    ACTIONS(19), 1,
      anon_sym_BSLASH,
    ACTIONS(23), 1,
      anon_sym_LBRACK,
    STATE(31), 1,
      sym__directory_separator,
    STATE(73), 1,
      aux_sym_pattern_repeat1,
    ACTIONS(65), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(67), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    ACTIONS(69), 2,
      aux_sym__line_token1,
      aux_sym__line_token2,
    ACTIONS(71), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
    STATE(17), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [184] = 9,
    ACTIONS(19), 1,
      anon_sym_BSLASH,
    ACTIONS(23), 1,
      anon_sym_LBRACK,
    STATE(32), 1,
      sym__directory_separator,
    STATE(74), 1,
      aux_sym_pattern_repeat1,
    ACTIONS(65), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(67), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    ACTIONS(73), 2,
      aux_sym__line_token1,
      aux_sym__line_token2,
    ACTIONS(75), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
    STATE(17), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [219] = 9,
    ACTIONS(19), 1,
      anon_sym_BSLASH,
    ACTIONS(23), 1,
      anon_sym_LBRACK,
    STATE(25), 1,
      sym__directory_separator,
    STATE(72), 1,
      aux_sym_pattern_repeat1,
    ACTIONS(65), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(67), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    ACTIONS(77), 2,
      aux_sym__line_token1,
      aux_sym__line_token2,
    ACTIONS(79), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
    STATE(17), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [254] = 9,
    ACTIONS(81), 1,
      anon_sym_BANG,
    ACTIONS(87), 1,
      anon_sym_BSLASH,
    ACTIONS(91), 1,
      anon_sym_LBRACK,
    STATE(62), 1,
      sym__directory_separator,
    STATE(107), 1,
      sym_pattern,
    ACTIONS(83), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
    ACTIONS(85), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(89), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    STATE(11), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [288] = 9,
    ACTIONS(73), 1,
      anon_sym_DQUOTE,
    ACTIONS(87), 1,
      anon_sym_BSLASH,
    ACTIONS(91), 1,
      anon_sym_LBRACK,
    STATE(38), 1,
      sym__directory_separator,
    STATE(81), 1,
      aux_sym_pattern_repeat1,
    ACTIONS(93), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
    ACTIONS(95), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(97), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    STATE(19), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [322] = 9,
    ACTIONS(101), 1,
      anon_sym_BSLASH,
    ACTIONS(103), 1,
      anon_sym_RBRACK,
    ACTIONS(105), 1,
      sym_bracket_char,
    ACTIONS(107), 1,
      anon_sym_LBRACK_COLON,
    STATE(84), 1,
      sym__bracket_char_closing_bracket,
    ACTIONS(99), 2,
      anon_sym_BANG,
      anon_sym_CARET,
    STATE(64), 2,
      sym__bracket_pattern_closing_bracket,
      sym__bracket_range_closing_bracket,
    STATE(78), 2,
      sym__bracket_char,
      sym_bracket_char_escaped,
    STATE(58), 4,
      sym__bracket_pattern,
      sym_bracket_range,
      sym_bracket_char_class,
      aux_sym_bracket_expr_repeat1,
  [356] = 9,
    ACTIONS(69), 1,
      anon_sym_DQUOTE,
    ACTIONS(87), 1,
      anon_sym_BSLASH,
    ACTIONS(91), 1,
      anon_sym_LBRACK,
    STATE(36), 1,
      sym__directory_separator,
    STATE(80), 1,
      aux_sym_pattern_repeat1,
    ACTIONS(95), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(97), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    ACTIONS(109), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
    STATE(19), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [390] = 9,
    ACTIONS(77), 1,
      anon_sym_DQUOTE,
    ACTIONS(87), 1,
      anon_sym_BSLASH,
    ACTIONS(91), 1,
      anon_sym_LBRACK,
    STATE(39), 1,
      sym__directory_separator,
    STATE(82), 1,
      aux_sym_pattern_repeat1,
    ACTIONS(95), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(97), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    ACTIONS(111), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
    STATE(19), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [424] = 9,
    ACTIONS(61), 1,
      anon_sym_DQUOTE,
    ACTIONS(87), 1,
      anon_sym_BSLASH,
    ACTIONS(91), 1,
      anon_sym_LBRACK,
    STATE(34), 1,
      sym__directory_separator,
    STATE(77), 1,
      aux_sym_pattern_repeat1,
    ACTIONS(95), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(97), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    ACTIONS(113), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
    STATE(19), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [458] = 9,
    ACTIONS(101), 1,
      anon_sym_BSLASH,
    ACTIONS(103), 1,
      anon_sym_RBRACK,
    ACTIONS(105), 1,
      sym_bracket_char,
    ACTIONS(107), 1,
      anon_sym_LBRACK_COLON,
    STATE(84), 1,
      sym__bracket_char_closing_bracket,
    ACTIONS(115), 2,
      anon_sym_BANG,
      anon_sym_CARET,
    STATE(48), 2,
      sym__bracket_pattern_closing_bracket,
      sym__bracket_range_closing_bracket,
    STATE(78), 2,
      sym__bracket_char,
      sym_bracket_char_escaped,
    STATE(51), 4,
      sym__bracket_pattern,
      sym_bracket_range,
      sym_bracket_char_class,
      aux_sym_bracket_expr_repeat1,
  [492] = 6,
    ACTIONS(19), 1,
      anon_sym_BSLASH,
    ACTIONS(23), 1,
      anon_sym_LBRACK,
    ACTIONS(65), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(67), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    ACTIONS(117), 4,
      aux_sym__line_token1,
      aux_sym__line_token2,
      sym_directory_separator,
      sym_directory_separator_escaped,
    STATE(17), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [519] = 2,
    ACTIONS(121), 3,
      sym_pattern_char,
      anon_sym_BSLASH,
      anon_sym_STAR,
    ACTIONS(119), 11,
      ts_builtin_sym_end,
      aux_sym__line_token1,
      aux_sym__line_token2,
      sym_comment,
      anon_sym_BANG,
      anon_sym_DQUOTE,
      sym_directory_separator,
      sym_directory_separator_escaped,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
      anon_sym_LBRACK,
  [538] = 6,
    ACTIONS(128), 1,
      anon_sym_BSLASH,
    ACTIONS(134), 1,
      anon_sym_LBRACK,
    ACTIONS(125), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(131), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    ACTIONS(123), 4,
      aux_sym__line_token1,
      aux_sym__line_token2,
      sym_directory_separator,
      sym_directory_separator_escaped,
    STATE(17), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [565] = 2,
    ACTIONS(139), 3,
      sym_pattern_char,
      anon_sym_BSLASH,
      anon_sym_STAR,
    ACTIONS(137), 11,
      ts_builtin_sym_end,
      aux_sym__line_token1,
      aux_sym__line_token2,
      sym_comment,
      anon_sym_BANG,
      anon_sym_DQUOTE,
      sym_directory_separator,
      sym_directory_separator_escaped,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
      anon_sym_LBRACK,
  [584] = 6,
    ACTIONS(144), 1,
      anon_sym_BSLASH,
    ACTIONS(150), 1,
      anon_sym_LBRACK,
    ACTIONS(141), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(147), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    ACTIONS(123), 3,
      anon_sym_DQUOTE,
      sym_directory_separator,
      sym_directory_separator_escaped,
    STATE(19), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [610] = 8,
    ACTIONS(101), 1,
      anon_sym_BSLASH,
    ACTIONS(103), 1,
      anon_sym_RBRACK,
    ACTIONS(105), 1,
      sym_bracket_char,
    ACTIONS(107), 1,
      anon_sym_LBRACK_COLON,
    STATE(84), 1,
      sym__bracket_char_closing_bracket,
    STATE(53), 2,
      sym__bracket_pattern_closing_bracket,
      sym__bracket_range_closing_bracket,
    STATE(78), 2,
      sym__bracket_char,
      sym_bracket_char_escaped,
    STATE(56), 4,
      sym__bracket_pattern,
      sym_bracket_range,
      sym_bracket_char_class,
      aux_sym_bracket_expr_repeat1,
  [640] = 6,
    ACTIONS(87), 1,
      anon_sym_BSLASH,
    ACTIONS(91), 1,
      anon_sym_LBRACK,
    ACTIONS(95), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(97), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    ACTIONS(117), 3,
      anon_sym_DQUOTE,
      sym_directory_separator,
      sym_directory_separator_escaped,
    STATE(19), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [666] = 8,
    ACTIONS(101), 1,
      anon_sym_BSLASH,
    ACTIONS(103), 1,
      anon_sym_RBRACK,
    ACTIONS(105), 1,
      sym_bracket_char,
    ACTIONS(107), 1,
      anon_sym_LBRACK_COLON,
    STATE(84), 1,
      sym__bracket_char_closing_bracket,
    STATE(50), 2,
      sym__bracket_pattern_closing_bracket,
      sym__bracket_range_closing_bracket,
    STATE(78), 2,
      sym__bracket_char,
      sym_bracket_char_escaped,
    STATE(57), 4,
      sym__bracket_pattern,
      sym_bracket_range,
      sym_bracket_char_class,
      aux_sym_bracket_expr_repeat1,
  [696] = 7,
    ACTIONS(19), 1,
      anon_sym_BSLASH,
    ACTIONS(23), 1,
      anon_sym_LBRACK,
    STATE(52), 1,
      sym__directory_separator,
    ACTIONS(153), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
    ACTIONS(155), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(157), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    STATE(6), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [724] = 7,
    ACTIONS(87), 1,
      anon_sym_BSLASH,
    ACTIONS(91), 1,
      anon_sym_LBRACK,
    STATE(55), 1,
      sym__directory_separator,
    ACTIONS(159), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
    ACTIONS(161), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(163), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    STATE(9), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [752] = 6,
    ACTIONS(23), 1,
      anon_sym_LBRACK,
    ACTIONS(169), 1,
      anon_sym_BSLASH,
    ACTIONS(165), 2,
      aux_sym__line_token1,
      aux_sym__line_token2,
    ACTIONS(167), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(171), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    STATE(15), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [777] = 6,
    ACTIONS(23), 1,
      anon_sym_LBRACK,
    ACTIONS(169), 1,
      anon_sym_BSLASH,
    ACTIONS(167), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(171), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    ACTIONS(173), 2,
      aux_sym__line_token1,
      aux_sym__line_token2,
    STATE(15), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [802] = 1,
    ACTIONS(175), 12,
      anon_sym_alnum,
      anon_sym_alpha,
      anon_sym_blank,
      anon_sym_cntrl,
      anon_sym_digit,
      anon_sym_graph,
      anon_sym_lower,
      anon_sym_print,
      anon_sym_punct,
      anon_sym_space,
      anon_sym_upper,
      anon_sym_xdigit,
  [817] = 6,
    ACTIONS(23), 1,
      anon_sym_LBRACK,
    ACTIONS(169), 1,
      anon_sym_BSLASH,
    ACTIONS(167), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(171), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    ACTIONS(177), 2,
      aux_sym__line_token1,
      aux_sym__line_token2,
    STATE(15), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [842] = 6,
    ACTIONS(23), 1,
      anon_sym_LBRACK,
    ACTIONS(169), 1,
      anon_sym_BSLASH,
    ACTIONS(167), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(171), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    ACTIONS(179), 2,
      aux_sym__line_token1,
      aux_sym__line_token2,
    STATE(15), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [867] = 6,
    ACTIONS(23), 1,
      anon_sym_LBRACK,
    ACTIONS(169), 1,
      anon_sym_BSLASH,
    ACTIONS(167), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(171), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    ACTIONS(181), 2,
      aux_sym__line_token1,
      aux_sym__line_token2,
    STATE(15), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [892] = 6,
    ACTIONS(23), 1,
      anon_sym_LBRACK,
    ACTIONS(169), 1,
      anon_sym_BSLASH,
    ACTIONS(167), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(171), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    ACTIONS(183), 2,
      aux_sym__line_token1,
      aux_sym__line_token2,
    STATE(15), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [917] = 6,
    ACTIONS(23), 1,
      anon_sym_LBRACK,
    ACTIONS(169), 1,
      anon_sym_BSLASH,
    ACTIONS(167), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(171), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    ACTIONS(185), 2,
      aux_sym__line_token1,
      aux_sym__line_token2,
    STATE(15), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [942] = 6,
    ACTIONS(23), 1,
      anon_sym_LBRACK,
    ACTIONS(169), 1,
      anon_sym_BSLASH,
    ACTIONS(167), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(171), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    ACTIONS(187), 2,
      aux_sym__line_token1,
      aux_sym__line_token2,
    STATE(15), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [967] = 6,
    ACTIONS(91), 1,
      anon_sym_LBRACK,
    ACTIONS(181), 1,
      anon_sym_DQUOTE,
    ACTIONS(191), 1,
      anon_sym_BSLASH,
    ACTIONS(189), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(193), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    STATE(21), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [991] = 6,
    ACTIONS(91), 1,
      anon_sym_LBRACK,
    ACTIONS(173), 1,
      anon_sym_DQUOTE,
    ACTIONS(191), 1,
      anon_sym_BSLASH,
    ACTIONS(189), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(193), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    STATE(21), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [1015] = 6,
    ACTIONS(91), 1,
      anon_sym_LBRACK,
    ACTIONS(183), 1,
      anon_sym_DQUOTE,
    ACTIONS(191), 1,
      anon_sym_BSLASH,
    ACTIONS(189), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(193), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    STATE(21), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [1039] = 6,
    ACTIONS(91), 1,
      anon_sym_LBRACK,
    ACTIONS(177), 1,
      anon_sym_DQUOTE,
    ACTIONS(191), 1,
      anon_sym_BSLASH,
    ACTIONS(189), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(193), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    STATE(21), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [1063] = 6,
    ACTIONS(91), 1,
      anon_sym_LBRACK,
    ACTIONS(185), 1,
      anon_sym_DQUOTE,
    ACTIONS(191), 1,
      anon_sym_BSLASH,
    ACTIONS(189), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(193), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    STATE(21), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [1087] = 6,
    ACTIONS(91), 1,
      anon_sym_LBRACK,
    ACTIONS(165), 1,
      anon_sym_DQUOTE,
    ACTIONS(191), 1,
      anon_sym_BSLASH,
    ACTIONS(189), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(193), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    STATE(21), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [1111] = 6,
    ACTIONS(91), 1,
      anon_sym_LBRACK,
    ACTIONS(187), 1,
      anon_sym_DQUOTE,
    ACTIONS(191), 1,
      anon_sym_BSLASH,
    ACTIONS(189), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(193), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    STATE(21), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [1135] = 6,
    ACTIONS(91), 1,
      anon_sym_LBRACK,
    ACTIONS(179), 1,
      anon_sym_DQUOTE,
    ACTIONS(191), 1,
      anon_sym_BSLASH,
    ACTIONS(189), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(193), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    STATE(21), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [1159] = 2,
    ACTIONS(197), 3,
      sym_pattern_char,
      anon_sym_BSLASH,
      anon_sym_STAR,
    ACTIONS(195), 7,
      aux_sym__line_token1,
      aux_sym__line_token2,
      sym_directory_separator,
      sym_directory_separator_escaped,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
      anon_sym_LBRACK,
  [1174] = 5,
    ACTIONS(91), 1,
      anon_sym_LBRACK,
    ACTIONS(191), 1,
      anon_sym_BSLASH,
    ACTIONS(189), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(193), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    STATE(21), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [1195] = 2,
    ACTIONS(201), 3,
      sym_pattern_char,
      anon_sym_BSLASH,
      anon_sym_STAR,
    ACTIONS(199), 7,
      aux_sym__line_token1,
      aux_sym__line_token2,
      sym_directory_separator,
      sym_directory_separator_escaped,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
      anon_sym_LBRACK,
  [1210] = 6,
    ACTIONS(101), 1,
      anon_sym_BSLASH,
    ACTIONS(105), 1,
      sym_bracket_char,
    ACTIONS(107), 1,
      anon_sym_LBRACK_COLON,
    ACTIONS(203), 1,
      anon_sym_RBRACK,
    STATE(78), 2,
      sym__bracket_char,
      sym_bracket_char_escaped,
    STATE(47), 4,
      sym__bracket_pattern,
      sym_bracket_range,
      sym_bracket_char_class,
      aux_sym_bracket_expr_repeat1,
  [1233] = 6,
    ACTIONS(101), 1,
      anon_sym_BSLASH,
    ACTIONS(105), 1,
      sym_bracket_char,
    ACTIONS(107), 1,
      anon_sym_LBRACK_COLON,
    ACTIONS(205), 1,
      anon_sym_RBRACK,
    STATE(78), 2,
      sym__bracket_char,
      sym_bracket_char_escaped,
    STATE(47), 4,
      sym__bracket_pattern,
      sym_bracket_range,
      sym_bracket_char_class,
      aux_sym_bracket_expr_repeat1,
  [1256] = 6,
    ACTIONS(207), 1,
      anon_sym_BSLASH,
    ACTIONS(210), 1,
      anon_sym_RBRACK,
    ACTIONS(212), 1,
      sym_bracket_char,
    ACTIONS(215), 1,
      anon_sym_LBRACK_COLON,
    STATE(78), 2,
      sym__bracket_char,
      sym_bracket_char_escaped,
    STATE(47), 4,
      sym__bracket_pattern,
      sym_bracket_range,
      sym_bracket_char_class,
      aux_sym_bracket_expr_repeat1,
  [1279] = 6,
    ACTIONS(101), 1,
      anon_sym_BSLASH,
    ACTIONS(105), 1,
      sym_bracket_char,
    ACTIONS(107), 1,
      anon_sym_LBRACK_COLON,
    ACTIONS(218), 1,
      anon_sym_RBRACK,
    STATE(78), 2,
      sym__bracket_char,
      sym_bracket_char_escaped,
    STATE(49), 4,
      sym__bracket_pattern,
      sym_bracket_range,
      sym_bracket_char_class,
      aux_sym_bracket_expr_repeat1,
  [1302] = 6,
    ACTIONS(101), 1,
      anon_sym_BSLASH,
    ACTIONS(105), 1,
      sym_bracket_char,
    ACTIONS(107), 1,
      anon_sym_LBRACK_COLON,
    ACTIONS(220), 1,
      anon_sym_RBRACK,
    STATE(78), 2,
      sym__bracket_char,
      sym_bracket_char_escaped,
    STATE(47), 4,
      sym__bracket_pattern,
      sym_bracket_range,
      sym_bracket_char_class,
      aux_sym_bracket_expr_repeat1,
  [1325] = 6,
    ACTIONS(101), 1,
      anon_sym_BSLASH,
    ACTIONS(105), 1,
      sym_bracket_char,
    ACTIONS(107), 1,
      anon_sym_LBRACK_COLON,
    ACTIONS(222), 1,
      anon_sym_RBRACK,
    STATE(78), 2,
      sym__bracket_char,
      sym_bracket_char_escaped,
    STATE(60), 4,
      sym__bracket_pattern,
      sym_bracket_range,
      sym_bracket_char_class,
      aux_sym_bracket_expr_repeat1,
  [1348] = 6,
    ACTIONS(101), 1,
      anon_sym_BSLASH,
    ACTIONS(105), 1,
      sym_bracket_char,
    ACTIONS(107), 1,
      anon_sym_LBRACK_COLON,
    ACTIONS(218), 1,
      anon_sym_RBRACK,
    STATE(78), 2,
      sym__bracket_char,
      sym_bracket_char_escaped,
    STATE(47), 4,
      sym__bracket_pattern,
      sym_bracket_range,
      sym_bracket_char_class,
      aux_sym_bracket_expr_repeat1,
  [1371] = 5,
    ACTIONS(23), 1,
      anon_sym_LBRACK,
    ACTIONS(169), 1,
      anon_sym_BSLASH,
    ACTIONS(224), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(226), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    STATE(4), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [1392] = 6,
    ACTIONS(101), 1,
      anon_sym_BSLASH,
    ACTIONS(105), 1,
      sym_bracket_char,
    ACTIONS(107), 1,
      anon_sym_LBRACK_COLON,
    ACTIONS(228), 1,
      anon_sym_RBRACK,
    STATE(78), 2,
      sym__bracket_char,
      sym_bracket_char_escaped,
    STATE(46), 4,
      sym__bracket_pattern,
      sym_bracket_range,
      sym_bracket_char_class,
      aux_sym_bracket_expr_repeat1,
  [1415] = 5,
    ACTIONS(23), 1,
      anon_sym_LBRACK,
    ACTIONS(169), 1,
      anon_sym_BSLASH,
    ACTIONS(230), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(232), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    STATE(7), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [1436] = 5,
    ACTIONS(91), 1,
      anon_sym_LBRACK,
    ACTIONS(191), 1,
      anon_sym_BSLASH,
    ACTIONS(234), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(236), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    STATE(13), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [1457] = 6,
    ACTIONS(101), 1,
      anon_sym_BSLASH,
    ACTIONS(105), 1,
      sym_bracket_char,
    ACTIONS(107), 1,
      anon_sym_LBRACK_COLON,
    ACTIONS(228), 1,
      anon_sym_RBRACK,
    STATE(78), 2,
      sym__bracket_char,
      sym_bracket_char_escaped,
    STATE(47), 4,
      sym__bracket_pattern,
      sym_bracket_range,
      sym_bracket_char_class,
      aux_sym_bracket_expr_repeat1,
  [1480] = 6,
    ACTIONS(101), 1,
      anon_sym_BSLASH,
    ACTIONS(105), 1,
      sym_bracket_char,
    ACTIONS(107), 1,
      anon_sym_LBRACK_COLON,
    ACTIONS(222), 1,
      anon_sym_RBRACK,
    STATE(78), 2,
      sym__bracket_char,
      sym_bracket_char_escaped,
    STATE(47), 4,
      sym__bracket_pattern,
      sym_bracket_range,
      sym_bracket_char_class,
      aux_sym_bracket_expr_repeat1,
  [1503] = 6,
    ACTIONS(101), 1,
      anon_sym_BSLASH,
    ACTIONS(105), 1,
      sym_bracket_char,
    ACTIONS(107), 1,
      anon_sym_LBRACK_COLON,
    ACTIONS(238), 1,
      anon_sym_RBRACK,
    STATE(78), 2,
      sym__bracket_char,
      sym_bracket_char_escaped,
    STATE(47), 4,
      sym__bracket_pattern,
      sym_bracket_range,
      sym_bracket_char_class,
      aux_sym_bracket_expr_repeat1,
  [1526] = 2,
    ACTIONS(242), 3,
      sym_pattern_char,
      anon_sym_BSLASH,
      anon_sym_STAR,
    ACTIONS(240), 7,
      aux_sym__line_token1,
      aux_sym__line_token2,
      sym_directory_separator,
      sym_directory_separator_escaped,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
      anon_sym_LBRACK,
  [1541] = 6,
    ACTIONS(101), 1,
      anon_sym_BSLASH,
    ACTIONS(105), 1,
      sym_bracket_char,
    ACTIONS(107), 1,
      anon_sym_LBRACK_COLON,
    ACTIONS(244), 1,
      anon_sym_RBRACK,
    STATE(78), 2,
      sym__bracket_char,
      sym_bracket_char_escaped,
    STATE(47), 4,
      sym__bracket_pattern,
      sym_bracket_range,
      sym_bracket_char_class,
      aux_sym_bracket_expr_repeat1,
  [1564] = 2,
    ACTIONS(248), 3,
      sym_pattern_char,
      anon_sym_BSLASH,
      anon_sym_STAR,
    ACTIONS(246), 7,
      aux_sym__line_token1,
      aux_sym__line_token2,
      sym_directory_separator,
      sym_directory_separator_escaped,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
      anon_sym_LBRACK,
  [1579] = 5,
    ACTIONS(91), 1,
      anon_sym_LBRACK,
    ACTIONS(191), 1,
      anon_sym_BSLASH,
    ACTIONS(250), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(252), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    STATE(12), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [1600] = 5,
    ACTIONS(23), 1,
      anon_sym_LBRACK,
    ACTIONS(169), 1,
      anon_sym_BSLASH,
    ACTIONS(167), 2,
      sym_pattern_char,
      anon_sym_STAR,
    ACTIONS(171), 2,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
    STATE(15), 4,
      aux_sym__pattern,
      sym_pattern_char_escaped,
      sym__wildcard,
      sym_bracket_expr,
  [1621] = 6,
    ACTIONS(101), 1,
      anon_sym_BSLASH,
    ACTIONS(105), 1,
      sym_bracket_char,
    ACTIONS(107), 1,
      anon_sym_LBRACK_COLON,
    ACTIONS(238), 1,
      anon_sym_RBRACK,
    STATE(78), 2,
      sym__bracket_char,
      sym_bracket_char_escaped,
    STATE(45), 4,
      sym__bracket_pattern,
      sym_bracket_range,
      sym_bracket_char_class,
      aux_sym_bracket_expr_repeat1,
  [1644] = 2,
    ACTIONS(256), 3,
      sym_pattern_char,
      anon_sym_BSLASH,
      anon_sym_STAR,
    ACTIONS(254), 7,
      aux_sym__line_token1,
      aux_sym__line_token2,
      sym_directory_separator,
      sym_directory_separator_escaped,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
      anon_sym_LBRACK,
  [1659] = 2,
    ACTIONS(256), 3,
      sym_pattern_char,
      anon_sym_BSLASH,
      anon_sym_STAR,
    ACTIONS(254), 6,
      anon_sym_DQUOTE,
      sym_directory_separator,
      sym_directory_separator_escaped,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
      anon_sym_LBRACK,
  [1673] = 2,
    ACTIONS(248), 3,
      sym_pattern_char,
      anon_sym_BSLASH,
      anon_sym_STAR,
    ACTIONS(246), 6,
      anon_sym_DQUOTE,
      sym_directory_separator,
      sym_directory_separator_escaped,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
      anon_sym_LBRACK,
  [1687] = 2,
    ACTIONS(197), 3,
      sym_pattern_char,
      anon_sym_BSLASH,
      anon_sym_STAR,
    ACTIONS(195), 6,
      anon_sym_DQUOTE,
      sym_directory_separator,
      sym_directory_separator_escaped,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
      anon_sym_LBRACK,
  [1701] = 2,
    ACTIONS(201), 3,
      sym_pattern_char,
      anon_sym_BSLASH,
      anon_sym_STAR,
    ACTIONS(199), 6,
      anon_sym_DQUOTE,
      sym_directory_separator,
      sym_directory_separator_escaped,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
      anon_sym_LBRACK,
  [1715] = 2,
    ACTIONS(242), 3,
      sym_pattern_char,
      anon_sym_BSLASH,
      anon_sym_STAR,
    ACTIONS(240), 6,
      anon_sym_DQUOTE,
      sym_directory_separator,
      sym_directory_separator_escaped,
      anon_sym_QMARK,
      anon_sym_STAR_STAR,
      anon_sym_LBRACK,
  [1729] = 3,
    ACTIONS(260), 1,
      sym_attribute,
    ACTIONS(258), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    STATE(96), 4,
      sym__attribute_declaration,
      sym_attribute_set,
      sym_attribute_unset,
      sym_attribute_set_to,
  [1743] = 4,
    STATE(28), 1,
      sym__directory_separator,
    STATE(75), 1,
      aux_sym_pattern_repeat1,
    ACTIONS(262), 2,
      aux_sym__line_token1,
      aux_sym__line_token2,
    ACTIONS(264), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
  [1758] = 4,
    STATE(33), 1,
      sym__directory_separator,
    STATE(75), 1,
      aux_sym_pattern_repeat1,
    ACTIONS(266), 2,
      aux_sym__line_token1,
      aux_sym__line_token2,
    ACTIONS(268), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
  [1773] = 4,
    STATE(29), 1,
      sym__directory_separator,
    STATE(75), 1,
      aux_sym_pattern_repeat1,
    ACTIONS(270), 2,
      aux_sym__line_token1,
      aux_sym__line_token2,
    ACTIONS(272), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
  [1788] = 4,
    STATE(63), 1,
      sym__directory_separator,
    STATE(75), 1,
      aux_sym_pattern_repeat1,
    ACTIONS(274), 2,
      aux_sym__line_token1,
      aux_sym__line_token2,
    ACTIONS(276), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
  [1803] = 4,
    STATE(26), 1,
      sym__directory_separator,
    STATE(75), 1,
      aux_sym_pattern_repeat1,
    ACTIONS(279), 2,
      aux_sym__line_token1,
      aux_sym__line_token2,
    ACTIONS(281), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
  [1818] = 4,
    ACTIONS(279), 1,
      anon_sym_DQUOTE,
    STATE(35), 1,
      sym__directory_separator,
    STATE(79), 1,
      aux_sym_pattern_repeat1,
    ACTIONS(283), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
  [1832] = 3,
    ACTIONS(285), 1,
      anon_sym_DASH,
    ACTIONS(289), 1,
      sym_bracket_char,
    ACTIONS(287), 3,
      anon_sym_BSLASH,
      anon_sym_RBRACK,
      anon_sym_LBRACK_COLON,
  [1844] = 4,
    ACTIONS(274), 1,
      anon_sym_DQUOTE,
    STATE(43), 1,
      sym__directory_separator,
    STATE(79), 1,
      aux_sym_pattern_repeat1,
    ACTIONS(291), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
  [1858] = 4,
    ACTIONS(266), 1,
      anon_sym_DQUOTE,
    STATE(40), 1,
      sym__directory_separator,
    STATE(79), 1,
      aux_sym_pattern_repeat1,
    ACTIONS(294), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
  [1872] = 4,
    ACTIONS(270), 1,
      anon_sym_DQUOTE,
    STATE(41), 1,
      sym__directory_separator,
    STATE(79), 1,
      aux_sym_pattern_repeat1,
    ACTIONS(296), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
  [1886] = 4,
    ACTIONS(262), 1,
      anon_sym_DQUOTE,
    STATE(37), 1,
      sym__directory_separator,
    STATE(79), 1,
      aux_sym_pattern_repeat1,
    ACTIONS(298), 2,
      sym_directory_separator,
      sym_directory_separator_escaped,
  [1900] = 2,
    ACTIONS(302), 1,
      sym_bracket_char,
    ACTIONS(300), 4,
      anon_sym_DASH,
      anon_sym_BSLASH,
      anon_sym_RBRACK,
      anon_sym_LBRACK_COLON,
  [1910] = 3,
    ACTIONS(304), 1,
      anon_sym_DASH,
    ACTIONS(308), 1,
      sym_bracket_char,
    ACTIONS(306), 3,
      anon_sym_BSLASH,
      anon_sym_RBRACK,
      anon_sym_LBRACK_COLON,
  [1922] = 2,
    ACTIONS(312), 1,
      sym_bracket_char,
    ACTIONS(310), 4,
      anon_sym_DASH,
      anon_sym_BSLASH,
      anon_sym_RBRACK,
      anon_sym_LBRACK_COLON,
  [1932] = 2,
    ACTIONS(316), 1,
      sym_bracket_char,
    ACTIONS(314), 3,
      anon_sym_BSLASH,
      anon_sym_RBRACK,
      anon_sym_LBRACK_COLON,
  [1941] = 2,
    ACTIONS(320), 1,
      sym_bracket_char,
    ACTIONS(318), 3,
      anon_sym_BSLASH,
      anon_sym_RBRACK,
      anon_sym_LBRACK_COLON,
  [1950] = 2,
    ACTIONS(312), 1,
      sym_bracket_char,
    ACTIONS(310), 3,
      anon_sym_BSLASH,
      anon_sym_RBRACK,
      anon_sym_LBRACK_COLON,
  [1959] = 2,
    ACTIONS(324), 1,
      sym_bracket_char,
    ACTIONS(322), 3,
      anon_sym_BSLASH,
      anon_sym_RBRACK,
      anon_sym_LBRACK_COLON,
  [1968] = 3,
    ACTIONS(326), 1,
      anon_sym_BSLASH,
    ACTIONS(328), 1,
      sym_bracket_char,
    STATE(87), 2,
      sym__bracket_char,
      sym_bracket_char_escaped,
  [1979] = 3,
    ACTIONS(326), 1,
      anon_sym_BSLASH,
    ACTIONS(330), 1,
      sym_bracket_char,
    STATE(86), 2,
      sym__bracket_char,
      sym_bracket_char_escaped,
  [1990] = 3,
    ACTIONS(332), 1,
      aux_sym__line_token1,
    ACTIONS(335), 1,
      aux_sym__line_token2,
    STATE(92), 1,
      aux_sym_attributes_line_repeat1,
  [2000] = 2,
    ACTIONS(339), 1,
      anon_sym_EQ,
    ACTIONS(337), 2,
      aux_sym__line_token1,
      aux_sym__line_token2,
  [2008] = 3,
    ACTIONS(341), 1,
      aux_sym__line_token1,
    ACTIONS(343), 1,
      aux_sym__line_token2,
    STATE(95), 1,
      aux_sym_attributes_line_repeat1,
  [2018] = 3,
    ACTIONS(341), 1,
      aux_sym__line_token1,
    ACTIONS(345), 1,
      aux_sym__line_token2,
    STATE(92), 1,
      aux_sym_attributes_line_repeat1,
  [2028] = 1,
    ACTIONS(335), 2,
      aux_sym__line_token1,
      aux_sym__line_token2,
  [2033] = 1,
    ACTIONS(347), 2,
      aux_sym__line_token1,
      aux_sym__line_token2,
  [2038] = 1,
    ACTIONS(349), 2,
      aux_sym__line_token1,
      aux_sym__line_token2,
  [2043] = 1,
    ACTIONS(351), 2,
      aux_sym__line_token1,
      aux_sym__line_token2,
  [2048] = 2,
    ACTIONS(353), 1,
      aux_sym__line_token1,
    ACTIONS(355), 1,
      aux_sym__line_token2,
  [2055] = 1,
    ACTIONS(357), 1,
      sym_value,
  [2059] = 1,
    ACTIONS(355), 1,
      aux_sym__line_token2,
  [2063] = 1,
    ACTIONS(359), 1,
      aux_sym_pattern_char_escaped_token1,
  [2067] = 1,
    ACTIONS(361), 1,
      aux_sym_pattern_char_escaped_token1,
  [2071] = 1,
    ACTIONS(363), 1,
      anon_sym_COLON_RBRACK,
  [2075] = 1,
    ACTIONS(365), 1,
      aux_sym_pattern_char_escaped_token1,
  [2079] = 1,
    ACTIONS(367), 1,
      anon_sym_DQUOTE,
  [2083] = 1,
    ACTIONS(369), 1,
      aux_sym__line_token2,
  [2087] = 1,
    ACTIONS(371), 1,
      sym_attribute,
  [2091] = 1,
    ACTIONS(373), 1,
      ts_builtin_sym_end,
  [2095] = 1,
    ACTIONS(375), 1,
      aux_sym_pattern_char_escaped_token1,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 57,
  [SMALL_STATE(4)] = 114,
  [SMALL_STATE(5)] = 149,
  [SMALL_STATE(6)] = 184,
  [SMALL_STATE(7)] = 219,
  [SMALL_STATE(8)] = 254,
  [SMALL_STATE(9)] = 288,
  [SMALL_STATE(10)] = 322,
  [SMALL_STATE(11)] = 356,
  [SMALL_STATE(12)] = 390,
  [SMALL_STATE(13)] = 424,
  [SMALL_STATE(14)] = 458,
  [SMALL_STATE(15)] = 492,
  [SMALL_STATE(16)] = 519,
  [SMALL_STATE(17)] = 538,
  [SMALL_STATE(18)] = 565,
  [SMALL_STATE(19)] = 584,
  [SMALL_STATE(20)] = 610,
  [SMALL_STATE(21)] = 640,
  [SMALL_STATE(22)] = 666,
  [SMALL_STATE(23)] = 696,
  [SMALL_STATE(24)] = 724,
  [SMALL_STATE(25)] = 752,
  [SMALL_STATE(26)] = 777,
  [SMALL_STATE(27)] = 802,
  [SMALL_STATE(28)] = 817,
  [SMALL_STATE(29)] = 842,
  [SMALL_STATE(30)] = 867,
  [SMALL_STATE(31)] = 892,
  [SMALL_STATE(32)] = 917,
  [SMALL_STATE(33)] = 942,
  [SMALL_STATE(34)] = 967,
  [SMALL_STATE(35)] = 991,
  [SMALL_STATE(36)] = 1015,
  [SMALL_STATE(37)] = 1039,
  [SMALL_STATE(38)] = 1063,
  [SMALL_STATE(39)] = 1087,
  [SMALL_STATE(40)] = 1111,
  [SMALL_STATE(41)] = 1135,
  [SMALL_STATE(42)] = 1159,
  [SMALL_STATE(43)] = 1174,
  [SMALL_STATE(44)] = 1195,
  [SMALL_STATE(45)] = 1210,
  [SMALL_STATE(46)] = 1233,
  [SMALL_STATE(47)] = 1256,
  [SMALL_STATE(48)] = 1279,
  [SMALL_STATE(49)] = 1302,
  [SMALL_STATE(50)] = 1325,
  [SMALL_STATE(51)] = 1348,
  [SMALL_STATE(52)] = 1371,
  [SMALL_STATE(53)] = 1392,
  [SMALL_STATE(54)] = 1415,
  [SMALL_STATE(55)] = 1436,
  [SMALL_STATE(56)] = 1457,
  [SMALL_STATE(57)] = 1480,
  [SMALL_STATE(58)] = 1503,
  [SMALL_STATE(59)] = 1526,
  [SMALL_STATE(60)] = 1541,
  [SMALL_STATE(61)] = 1564,
  [SMALL_STATE(62)] = 1579,
  [SMALL_STATE(63)] = 1600,
  [SMALL_STATE(64)] = 1621,
  [SMALL_STATE(65)] = 1644,
  [SMALL_STATE(66)] = 1659,
  [SMALL_STATE(67)] = 1673,
  [SMALL_STATE(68)] = 1687,
  [SMALL_STATE(69)] = 1701,
  [SMALL_STATE(70)] = 1715,
  [SMALL_STATE(71)] = 1729,
  [SMALL_STATE(72)] = 1743,
  [SMALL_STATE(73)] = 1758,
  [SMALL_STATE(74)] = 1773,
  [SMALL_STATE(75)] = 1788,
  [SMALL_STATE(76)] = 1803,
  [SMALL_STATE(77)] = 1818,
  [SMALL_STATE(78)] = 1832,
  [SMALL_STATE(79)] = 1844,
  [SMALL_STATE(80)] = 1858,
  [SMALL_STATE(81)] = 1872,
  [SMALL_STATE(82)] = 1886,
  [SMALL_STATE(83)] = 1900,
  [SMALL_STATE(84)] = 1910,
  [SMALL_STATE(85)] = 1922,
  [SMALL_STATE(86)] = 1932,
  [SMALL_STATE(87)] = 1941,
  [SMALL_STATE(88)] = 1950,
  [SMALL_STATE(89)] = 1959,
  [SMALL_STATE(90)] = 1968,
  [SMALL_STATE(91)] = 1979,
  [SMALL_STATE(92)] = 1990,
  [SMALL_STATE(93)] = 2000,
  [SMALL_STATE(94)] = 2008,
  [SMALL_STATE(95)] = 2018,
  [SMALL_STATE(96)] = 2028,
  [SMALL_STATE(97)] = 2033,
  [SMALL_STATE(98)] = 2038,
  [SMALL_STATE(99)] = 2043,
  [SMALL_STATE(100)] = 2048,
  [SMALL_STATE(101)] = 2055,
  [SMALL_STATE(102)] = 2059,
  [SMALL_STATE(103)] = 2063,
  [SMALL_STATE(104)] = 2067,
  [SMALL_STATE(105)] = 2071,
  [SMALL_STATE(106)] = 2075,
  [SMALL_STATE(107)] = 2079,
  [SMALL_STATE(108)] = 2083,
  [SMALL_STATE(109)] = 2087,
  [SMALL_STATE(110)] = 2091,
  [SMALL_STATE(111)] = 2095,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_document, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(5),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(111),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [25] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_document, 1),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [29] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2),
  [31] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2), SHIFT_REPEAT(102),
  [34] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2), SHIFT_REPEAT(3),
  [37] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2), SHIFT_REPEAT(100),
  [40] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2), SHIFT_REPEAT(23),
  [43] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2), SHIFT_REPEAT(8),
  [46] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2), SHIFT_REPEAT(54),
  [49] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_document_repeat1, 2), SHIFT_REPEAT(5),
  [52] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_document_repeat1, 2), SHIFT_REPEAT(111),
  [55] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2), SHIFT_REPEAT(5),
  [58] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2), SHIFT_REPEAT(10),
  [61] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pattern, 3, .production_id = 6),
  [63] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [65] = {.entry = {.count = 1, .reusable = false}}, SHIFT(17),
  [67] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [69] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pattern, 1),
  [71] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [73] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pattern, 2, .production_id = 1),
  [75] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [77] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pattern, 2, .production_id = 3),
  [79] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [81] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [83] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [85] = {.entry = {.count = 1, .reusable = false}}, SHIFT(11),
  [87] = {.entry = {.count = 1, .reusable = false}}, SHIFT(103),
  [89] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [91] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [93] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [95] = {.entry = {.count = 1, .reusable = false}}, SHIFT(19),
  [97] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [99] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [101] = {.entry = {.count = 1, .reusable = true}}, SHIFT(106),
  [103] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [105] = {.entry = {.count = 1, .reusable = false}}, SHIFT(78),
  [107] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [109] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [111] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [113] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [115] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [117] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_pattern_repeat1, 2, .production_id = 3),
  [119] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__line, 2),
  [121] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__line, 2),
  [123] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__pattern, 2),
  [125] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__pattern, 2), SHIFT_REPEAT(17),
  [128] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__pattern, 2), SHIFT_REPEAT(111),
  [131] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__pattern, 2), SHIFT_REPEAT(17),
  [134] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__pattern, 2), SHIFT_REPEAT(10),
  [137] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__line, 3),
  [139] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__line, 3),
  [141] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__pattern, 2), SHIFT_REPEAT(19),
  [144] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__pattern, 2), SHIFT_REPEAT(103),
  [147] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__pattern, 2), SHIFT_REPEAT(19),
  [150] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__pattern, 2), SHIFT_REPEAT(14),
  [153] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [155] = {.entry = {.count = 1, .reusable = false}}, SHIFT(6),
  [157] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [159] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [161] = {.entry = {.count = 1, .reusable = false}}, SHIFT(9),
  [163] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [165] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pattern, 3, .production_id = 9),
  [167] = {.entry = {.count = 1, .reusable = false}}, SHIFT(15),
  [169] = {.entry = {.count = 1, .reusable = true}}, SHIFT(111),
  [171] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [173] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pattern, 5, .production_id = 19),
  [175] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [177] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pattern, 4, .production_id = 18),
  [179] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pattern, 4, .production_id = 15),
  [181] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pattern, 4, .production_id = 13),
  [183] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pattern, 2, .production_id = 4),
  [185] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pattern, 3, .production_id = 7),
  [187] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pattern, 3, .production_id = 11),
  [189] = {.entry = {.count = 1, .reusable = false}}, SHIFT(21),
  [191] = {.entry = {.count = 1, .reusable = true}}, SHIFT(103),
  [193] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [195] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bracket_expr, 4, .production_id = 16),
  [197] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_bracket_expr, 4, .production_id = 16),
  [199] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bracket_expr, 3),
  [201] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_bracket_expr, 3),
  [203] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [205] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [207] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_bracket_expr_repeat1, 2), SHIFT_REPEAT(106),
  [210] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_bracket_expr_repeat1, 2),
  [212] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_bracket_expr_repeat1, 2), SHIFT_REPEAT(78),
  [215] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_bracket_expr_repeat1, 2), SHIFT_REPEAT(27),
  [218] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [220] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [222] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [224] = {.entry = {.count = 1, .reusable = false}}, SHIFT(4),
  [226] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [228] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [230] = {.entry = {.count = 1, .reusable = false}}, SHIFT(7),
  [232] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [234] = {.entry = {.count = 1, .reusable = false}}, SHIFT(13),
  [236] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [238] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [240] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pattern_char_escaped, 2),
  [242] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pattern_char_escaped, 2),
  [244] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [246] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bracket_expr, 4),
  [248] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_bracket_expr, 4),
  [250] = {.entry = {.count = 1, .reusable = false}}, SHIFT(12),
  [252] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [254] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bracket_expr, 5, .production_id = 16),
  [256] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_bracket_expr, 5, .production_id = 16),
  [258] = {.entry = {.count = 1, .reusable = true}}, SHIFT(109),
  [260] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [262] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pattern, 3, .production_id = 10),
  [264] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [266] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pattern, 2, .production_id = 5),
  [268] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [270] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pattern, 3, .production_id = 8),
  [272] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [274] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_pattern_repeat1, 2, .production_id = 12),
  [276] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pattern_repeat1, 2, .production_id = 12), SHIFT_REPEAT(63),
  [279] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pattern, 4, .production_id = 14),
  [281] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [283] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [285] = {.entry = {.count = 1, .reusable = true}}, SHIFT(90),
  [287] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__bracket_pattern, 1),
  [289] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__bracket_pattern, 1),
  [291] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pattern_repeat1, 2, .production_id = 12), SHIFT_REPEAT(43),
  [294] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [296] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [298] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [300] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__bracket_char_closing_bracket, 1, .production_id = 2),
  [302] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__bracket_char_closing_bracket, 1, .production_id = 2),
  [304] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [306] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__bracket_pattern_closing_bracket, 1),
  [308] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__bracket_pattern_closing_bracket, 1),
  [310] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bracket_char_escaped, 2),
  [312] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_bracket_char_escaped, 2),
  [314] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__bracket_range_closing_bracket, 3),
  [316] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__bracket_range_closing_bracket, 3),
  [318] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bracket_range, 3),
  [320] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_bracket_range, 3),
  [322] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bracket_char_class, 3, .production_id = 17),
  [324] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_bracket_char_class, 3, .production_id = 17),
  [326] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [328] = {.entry = {.count = 1, .reusable = false}}, SHIFT(87),
  [330] = {.entry = {.count = 1, .reusable = false}}, SHIFT(86),
  [332] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_attributes_line_repeat1, 2), SHIFT_REPEAT(71),
  [335] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_attributes_line_repeat1, 2),
  [337] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attribute_set, 1),
  [339] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [341] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [343] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attributes_line, 1),
  [345] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attributes_line, 2),
  [347] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_quoted_pattern, 3),
  [349] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attribute_unset, 2),
  [351] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attribute_set_to, 3),
  [353] = {.entry = {.count = 1, .reusable = true}}, SHIFT(108),
  [355] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [357] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [359] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [361] = {.entry = {.count = 1, .reusable = true}}, SHIFT(88),
  [363] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [365] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [367] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [369] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [371] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [373] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [375] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_gitattributes(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
