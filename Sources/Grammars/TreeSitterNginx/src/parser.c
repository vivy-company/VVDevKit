#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 83
#define LARGE_STATE_COUNT 11
#define SYMBOL_COUNT 72
#define ALIAS_COUNT 0
#define TOKEN_COUNT 47
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 3
#define MAX_ALIAS_SEQUENCE_LENGTH 10
#define PRODUCTION_ID_COUNT 4

enum ts_symbol_identifiers {
  sym_comment = 1,
  sym_directive = 2,
  anon_sym_SEMI = 3,
  anon_sym_LBRACE = 4,
  anon_sym_RBRACE = 5,
  anon_sym_LPAREN = 6,
  anon_sym_RPAREN = 7,
  anon_sym_LBRACK = 8,
  anon_sym_RBRACK = 9,
  sym_generic = 10,
  sym_metric = 11,
  aux_sym_variable_token1 = 12,
  aux_sym_variable_token2 = 13,
  sym_number = 14,
  sym_sq_string_content = 15,
  sym_dq_string_content = 16,
  anon_sym_SQUOTE = 17,
  anon_sym_DQUOTE = 18,
  anon_sym_SLASH = 19,
  anon_sym_DOT = 20,
  sym_regex_pattern = 21,
  sym__colon = 22,
  sym__or = 23,
  sym__option = 24,
  sym__carrot = 25,
  sym__star = 26,
  sym_escaped_dot = 27,
  sym__eol = 28,
  sym__plus = 29,
  sym__eq = 30,
  sym__tild = 31,
  sym__not = 32,
  sym__ts_modifier = 33,
  sym__st_modifier = 34,
  sym_scheme = 35,
  sym_ipv4 = 36,
  anon_sym_access_by_lua_block = 37,
  anon_sym_header_filter_by_lua_block = 38,
  anon_sym_body_filter_by_lua_block = 39,
  anon_sym_log_by_lua_block = 40,
  anon_sym_balancer_by_lua_block = 41,
  anon_sym_content_by_lua_block = 42,
  anon_sym_rewrite_by_lua_block = 43,
  aux_sym__lua_code_token1 = 44,
  aux_sym__lua_code_token2 = 45,
  aux_sym__lua_code_token3 = 46,
  sym_conf = 47,
  sym__directives = 48,
  sym_simple_directive = 49,
  sym_block_directive = 50,
  sym_block = 51,
  sym_parenthese = 52,
  sym_bracket = 53,
  sym_param = 54,
  sym_variable = 55,
  sym_string = 56,
  sym_regex = 57,
  sym__regex_tokens = 58,
  sym_modifier = 59,
  sym_uri = 60,
  sym__lua_block_directives = 61,
  sym_lua_block_directive = 62,
  sym_lua_block = 63,
  sym_lua_code = 64,
  sym__lua_code = 65,
  aux_sym_conf_repeat1 = 66,
  aux_sym_simple_directive_repeat1 = 67,
  aux_sym_string_repeat1 = 68,
  aux_sym_string_repeat2 = 69,
  aux_sym_lua_block_repeat1 = 70,
  aux_sym__lua_code_repeat1 = 71,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_comment] = "comment",
  [sym_directive] = "directive",
  [anon_sym_SEMI] = ";",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [sym_generic] = "generic",
  [sym_metric] = "metric",
  [aux_sym_variable_token1] = "variable_token1",
  [aux_sym_variable_token2] = "variable_token2",
  [sym_number] = "number",
  [sym_sq_string_content] = "sq_string_content",
  [sym_dq_string_content] = "dq_string_content",
  [anon_sym_SQUOTE] = "'",
  [anon_sym_DQUOTE] = "\"",
  [anon_sym_SLASH] = "/",
  [anon_sym_DOT] = ".",
  [sym_regex_pattern] = "regex_pattern",
  [sym__colon] = "_colon",
  [sym__or] = "_or",
  [sym__option] = "_option",
  [sym__carrot] = "_carrot",
  [sym__star] = "_star",
  [sym_escaped_dot] = "escaped_dot",
  [sym__eol] = "_eol",
  [sym__plus] = "_plus",
  [sym__eq] = "_eq",
  [sym__tild] = "_tild",
  [sym__not] = "_not",
  [sym__ts_modifier] = "_ts_modifier",
  [sym__st_modifier] = "_st_modifier",
  [sym_scheme] = "scheme",
  [sym_ipv4] = "ipv4",
  [anon_sym_access_by_lua_block] = "access_by_lua_block",
  [anon_sym_header_filter_by_lua_block] = "header_filter_by_lua_block",
  [anon_sym_body_filter_by_lua_block] = "body_filter_by_lua_block",
  [anon_sym_log_by_lua_block] = "log_by_lua_block",
  [anon_sym_balancer_by_lua_block] = "balancer_by_lua_block",
  [anon_sym_content_by_lua_block] = "content_by_lua_block",
  [anon_sym_rewrite_by_lua_block] = "rewrite_by_lua_block",
  [aux_sym__lua_code_token1] = "_lua_code_token1",
  [aux_sym__lua_code_token2] = "_lua_code_token2",
  [aux_sym__lua_code_token3] = "_lua_code_token3",
  [sym_conf] = "conf",
  [sym__directives] = "_directives",
  [sym_simple_directive] = "simple_directive",
  [sym_block_directive] = "block_directive",
  [sym_block] = "block",
  [sym_parenthese] = "parenthese",
  [sym_bracket] = "bracket",
  [sym_param] = "param",
  [sym_variable] = "variable",
  [sym_string] = "string",
  [sym_regex] = "regex",
  [sym__regex_tokens] = "_regex_tokens",
  [sym_modifier] = "modifier",
  [sym_uri] = "uri",
  [sym__lua_block_directives] = "_lua_block_directives",
  [sym_lua_block_directive] = "lua_block_directive",
  [sym_lua_block] = "lua_block",
  [sym_lua_code] = "lua_code",
  [sym__lua_code] = "_lua_code",
  [aux_sym_conf_repeat1] = "conf_repeat1",
  [aux_sym_simple_directive_repeat1] = "simple_directive_repeat1",
  [aux_sym_string_repeat1] = "string_repeat1",
  [aux_sym_string_repeat2] = "string_repeat2",
  [aux_sym_lua_block_repeat1] = "lua_block_repeat1",
  [aux_sym__lua_code_repeat1] = "_lua_code_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_comment] = sym_comment,
  [sym_directive] = sym_directive,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [sym_generic] = sym_generic,
  [sym_metric] = sym_metric,
  [aux_sym_variable_token1] = aux_sym_variable_token1,
  [aux_sym_variable_token2] = aux_sym_variable_token2,
  [sym_number] = sym_number,
  [sym_sq_string_content] = sym_sq_string_content,
  [sym_dq_string_content] = sym_dq_string_content,
  [anon_sym_SQUOTE] = anon_sym_SQUOTE,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [anon_sym_SLASH] = anon_sym_SLASH,
  [anon_sym_DOT] = anon_sym_DOT,
  [sym_regex_pattern] = sym_regex_pattern,
  [sym__colon] = sym__colon,
  [sym__or] = sym__or,
  [sym__option] = sym__option,
  [sym__carrot] = sym__carrot,
  [sym__star] = sym__star,
  [sym_escaped_dot] = sym_escaped_dot,
  [sym__eol] = sym__eol,
  [sym__plus] = sym__plus,
  [sym__eq] = sym__eq,
  [sym__tild] = sym__tild,
  [sym__not] = sym__not,
  [sym__ts_modifier] = sym__ts_modifier,
  [sym__st_modifier] = sym__st_modifier,
  [sym_scheme] = sym_scheme,
  [sym_ipv4] = sym_ipv4,
  [anon_sym_access_by_lua_block] = anon_sym_access_by_lua_block,
  [anon_sym_header_filter_by_lua_block] = anon_sym_header_filter_by_lua_block,
  [anon_sym_body_filter_by_lua_block] = anon_sym_body_filter_by_lua_block,
  [anon_sym_log_by_lua_block] = anon_sym_log_by_lua_block,
  [anon_sym_balancer_by_lua_block] = anon_sym_balancer_by_lua_block,
  [anon_sym_content_by_lua_block] = anon_sym_content_by_lua_block,
  [anon_sym_rewrite_by_lua_block] = anon_sym_rewrite_by_lua_block,
  [aux_sym__lua_code_token1] = aux_sym__lua_code_token1,
  [aux_sym__lua_code_token2] = aux_sym__lua_code_token2,
  [aux_sym__lua_code_token3] = aux_sym__lua_code_token3,
  [sym_conf] = sym_conf,
  [sym__directives] = sym__directives,
  [sym_simple_directive] = sym_simple_directive,
  [sym_block_directive] = sym_block_directive,
  [sym_block] = sym_block,
  [sym_parenthese] = sym_parenthese,
  [sym_bracket] = sym_bracket,
  [sym_param] = sym_param,
  [sym_variable] = sym_variable,
  [sym_string] = sym_string,
  [sym_regex] = sym_regex,
  [sym__regex_tokens] = sym__regex_tokens,
  [sym_modifier] = sym_modifier,
  [sym_uri] = sym_uri,
  [sym__lua_block_directives] = sym__lua_block_directives,
  [sym_lua_block_directive] = sym_lua_block_directive,
  [sym_lua_block] = sym_lua_block,
  [sym_lua_code] = sym_lua_code,
  [sym__lua_code] = sym__lua_code,
  [aux_sym_conf_repeat1] = aux_sym_conf_repeat1,
  [aux_sym_simple_directive_repeat1] = aux_sym_simple_directive_repeat1,
  [aux_sym_string_repeat1] = aux_sym_string_repeat1,
  [aux_sym_string_repeat2] = aux_sym_string_repeat2,
  [aux_sym_lua_block_repeat1] = aux_sym_lua_block_repeat1,
  [aux_sym__lua_code_repeat1] = aux_sym__lua_code_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_directive] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_SEMI] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [sym_generic] = {
    .visible = true,
    .named = true,
  },
  [sym_metric] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_variable_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_variable_token2] = {
    .visible = false,
    .named = false,
  },
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [sym_sq_string_content] = {
    .visible = true,
    .named = true,
  },
  [sym_dq_string_content] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_SQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SLASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOT] = {
    .visible = true,
    .named = false,
  },
  [sym_regex_pattern] = {
    .visible = true,
    .named = true,
  },
  [sym__colon] = {
    .visible = false,
    .named = true,
  },
  [sym__or] = {
    .visible = false,
    .named = true,
  },
  [sym__option] = {
    .visible = false,
    .named = true,
  },
  [sym__carrot] = {
    .visible = false,
    .named = true,
  },
  [sym__star] = {
    .visible = false,
    .named = true,
  },
  [sym_escaped_dot] = {
    .visible = true,
    .named = true,
  },
  [sym__eol] = {
    .visible = false,
    .named = true,
  },
  [sym__plus] = {
    .visible = false,
    .named = true,
  },
  [sym__eq] = {
    .visible = false,
    .named = true,
  },
  [sym__tild] = {
    .visible = false,
    .named = true,
  },
  [sym__not] = {
    .visible = false,
    .named = true,
  },
  [sym__ts_modifier] = {
    .visible = false,
    .named = true,
  },
  [sym__st_modifier] = {
    .visible = false,
    .named = true,
  },
  [sym_scheme] = {
    .visible = true,
    .named = true,
  },
  [sym_ipv4] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_access_by_lua_block] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_header_filter_by_lua_block] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_body_filter_by_lua_block] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_log_by_lua_block] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_balancer_by_lua_block] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_content_by_lua_block] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_rewrite_by_lua_block] = {
    .visible = true,
    .named = false,
  },
  [aux_sym__lua_code_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__lua_code_token2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__lua_code_token3] = {
    .visible = false,
    .named = false,
  },
  [sym_conf] = {
    .visible = true,
    .named = true,
  },
  [sym__directives] = {
    .visible = false,
    .named = true,
  },
  [sym_simple_directive] = {
    .visible = true,
    .named = true,
  },
  [sym_block_directive] = {
    .visible = true,
    .named = true,
  },
  [sym_block] = {
    .visible = true,
    .named = true,
  },
  [sym_parenthese] = {
    .visible = true,
    .named = true,
  },
  [sym_bracket] = {
    .visible = true,
    .named = true,
  },
  [sym_param] = {
    .visible = true,
    .named = true,
  },
  [sym_variable] = {
    .visible = true,
    .named = true,
  },
  [sym_string] = {
    .visible = true,
    .named = true,
  },
  [sym_regex] = {
    .visible = true,
    .named = true,
  },
  [sym__regex_tokens] = {
    .visible = false,
    .named = true,
  },
  [sym_modifier] = {
    .visible = true,
    .named = true,
  },
  [sym_uri] = {
    .visible = true,
    .named = true,
  },
  [sym__lua_block_directives] = {
    .visible = false,
    .named = true,
  },
  [sym_lua_block_directive] = {
    .visible = true,
    .named = true,
  },
  [sym_lua_block] = {
    .visible = true,
    .named = true,
  },
  [sym_lua_code] = {
    .visible = true,
    .named = true,
  },
  [sym__lua_code] = {
    .visible = false,
    .named = true,
  },
  [aux_sym_conf_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_simple_directive_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_string_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_string_repeat2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_lua_block_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__lua_code_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum ts_field_identifiers {
  field_name = 1,
  field_pattern = 2,
  field_scheme = 3,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_name] = "name",
  [field_pattern] = "pattern",
  [field_scheme] = "scheme",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 1},
  [3] = {.index = 2, .length = 1},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_name, 0},
  [1] =
    {field_pattern, 1},
  [2] =
    {field_scheme, 0},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 4,
  [7] = 7,
  [8] = 4,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 23,
  [25] = 23,
  [26] = 26,
  [27] = 27,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 35,
  [36] = 36,
  [37] = 37,
  [38] = 38,
  [39] = 39,
  [40] = 40,
  [41] = 41,
  [42] = 42,
  [43] = 43,
  [44] = 44,
  [45] = 45,
  [46] = 46,
  [47] = 47,
  [48] = 48,
  [49] = 14,
  [50] = 50,
  [51] = 51,
  [52] = 52,
  [53] = 14,
  [54] = 54,
  [55] = 55,
  [56] = 56,
  [57] = 57,
  [58] = 58,
  [59] = 59,
  [60] = 60,
  [61] = 61,
  [62] = 62,
  [63] = 63,
  [64] = 64,
  [65] = 65,
  [66] = 66,
  [67] = 67,
  [68] = 68,
  [69] = 69,
  [70] = 70,
  [71] = 71,
  [72] = 72,
  [73] = 73,
  [74] = 74,
  [75] = 75,
  [76] = 76,
  [77] = 77,
  [78] = 78,
  [79] = 79,
  [80] = 80,
  [81] = 81,
  [82] = 82,
};

static inline bool sym__not_character_set_1(int32_t c) {
  return (c < 8192
    ? (c < 160
      ? (c < ' '
        ? (c >= '\t' && c <= '\r')
        : c <= ' ')
      : (c <= 160 || c == 5760))
    : (c <= 8203 || (c < 12288
      ? (c < 8287
        ? c == 8239
        : c <= 8288)
      : (c <= 12288 || c == 65279))));
}

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(43);
      if (lookahead == '!') ADVANCE(256);
      if (lookahead == '"') ADVANCE(218);
      if (lookahead == '#') ADVANCE(1);
      if (lookahead == '$') ADVANCE(251);
      if (lookahead == '\'') ADVANCE(217);
      if (lookahead == '(') ADVANCE(189);
      if (lookahead == ')') ADVANCE(190);
      if (lookahead == '*') ADVANCE(249);
      if (lookahead == '+') ADVANCE(253);
      if (lookahead == '.') ADVANCE(221);
      if (lookahead == '/') ADVANCE(219);
      if (lookahead == ':') ADVANCE(245);
      if (lookahead == ';') ADVANCE(186);
      if (lookahead == '=') ADVANCE(254);
      if (lookahead == '?') ADVANCE(247);
      if (lookahead == '[') ADVANCE(191);
      if (lookahead == '\\') ADVANCE(17);
      if (lookahead == ']') ADVANCE(192);
      if (lookahead == '^') ADVANCE(248);
      if (lookahead == 'a') ADVANCE(94);
      if (lookahead == 'b') ADVANCE(69);
      if (lookahead == 'c') ADVANCE(147);
      if (lookahead == 'h') ADVANCE(105);
      if (lookahead == 'l') ADVANCE(148);
      if (lookahead == 'r') ADVANCE(106);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '|') ADVANCE(246);
      if (lookahead == '}') ADVANCE(188);
      if (lookahead == '~') ADVANCE(255);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(45);
      if (sym__not_character_set_1(lookahead)) SKIP(41)
      if (('A' <= lookahead && lookahead <= '_') ||
          ('d' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 1:
      if (lookahead == '\n') ADVANCE(44);
      if (lookahead != 0) ADVANCE(1);
      END_STATE();
    case 2:
      if (lookahead == '\n') ADVANCE(44);
      if (lookahead != 0) ADVANCE(224);
      END_STATE();
    case 3:
      if (lookahead == '!') ADVANCE(256);
      if (lookahead == '"') ADVANCE(218);
      if (lookahead == '#') ADVANCE(1);
      if (lookahead == '$') ADVANCE(251);
      if (lookahead == '\'') ADVANCE(217);
      if (lookahead == '(') ADVANCE(189);
      if (lookahead == ')') ADVANCE(190);
      if (lookahead == '*') ADVANCE(249);
      if (lookahead == '+') ADVANCE(253);
      if (lookahead == '-') ADVANCE(38);
      if (lookahead == '.') ADVANCE(223);
      if (lookahead == '/') ADVANCE(220);
      if (lookahead == ':') ADVANCE(245);
      if (lookahead == ';') ADVANCE(186);
      if (lookahead == '=') ADVANCE(254);
      if (lookahead == '?') ADVANCE(247);
      if (lookahead == '[') ADVANCE(191);
      if (lookahead == '\\') ADVANCE(17);
      if (lookahead == ']') ADVANCE(192);
      if (lookahead == '^') ADVANCE(248);
      if (lookahead == '_') ADVANCE(32);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '|') ADVANCE(246);
      if (lookahead == '~') ADVANCE(255);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(208);
      if (sym__not_character_set_1(lookahead)) SKIP(4)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(19);
      END_STATE();
    case 4:
      if (lookahead == '!') ADVANCE(256);
      if (lookahead == '"') ADVANCE(218);
      if (lookahead == '#') ADVANCE(1);
      if (lookahead == '$') ADVANCE(251);
      if (lookahead == '\'') ADVANCE(217);
      if (lookahead == '(') ADVANCE(189);
      if (lookahead == ')') ADVANCE(190);
      if (lookahead == '*') ADVANCE(249);
      if (lookahead == '+') ADVANCE(253);
      if (lookahead == '-') ADVANCE(38);
      if (lookahead == '.') ADVANCE(223);
      if (lookahead == '/') ADVANCE(220);
      if (lookahead == ';') ADVANCE(186);
      if (lookahead == '=') ADVANCE(254);
      if (lookahead == '[') ADVANCE(191);
      if (lookahead == '\\') ADVANCE(17);
      if (lookahead == ']') ADVANCE(192);
      if (lookahead == '^') ADVANCE(248);
      if (lookahead == '_') ADVANCE(32);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '~') ADVANCE(255);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(208);
      if (sym__not_character_set_1(lookahead)) SKIP(4)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(19);
      END_STATE();
    case 5:
      if (lookahead == '!') ADVANCE(256);
      if (lookahead == '"') ADVANCE(218);
      if (lookahead == '#') ADVANCE(1);
      if (lookahead == '$') ADVANCE(251);
      if (lookahead == '\'') ADVANCE(217);
      if (lookahead == '(') ADVANCE(189);
      if (lookahead == ')') ADVANCE(190);
      if (lookahead == '*') ADVANCE(249);
      if (lookahead == '+') ADVANCE(253);
      if (lookahead == '-') ADVANCE(38);
      if (lookahead == '.') ADVANCE(223);
      if (lookahead == '/') ADVANCE(220);
      if (lookahead == '=') ADVANCE(254);
      if (lookahead == '[') ADVANCE(191);
      if (lookahead == '\\') ADVANCE(17);
      if (lookahead == '^') ADVANCE(248);
      if (lookahead == '_') ADVANCE(32);
      if (lookahead == '~') ADVANCE(255);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(208);
      if (sym__not_character_set_1(lookahead)) SKIP(5)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(19);
      END_STATE();
    case 6:
      if (lookahead == '!') ADVANCE(256);
      if (lookahead == '"') ADVANCE(218);
      if (lookahead == '#') ADVANCE(1);
      if (lookahead == '$') ADVANCE(251);
      if (lookahead == '\'') ADVANCE(217);
      if (lookahead == '(') ADVANCE(189);
      if (lookahead == '*') ADVANCE(249);
      if (lookahead == '+') ADVANCE(253);
      if (lookahead == '-') ADVANCE(38);
      if (lookahead == '.') ADVANCE(223);
      if (lookahead == '/') ADVANCE(220);
      if (lookahead == ';') ADVANCE(186);
      if (lookahead == '=') ADVANCE(254);
      if (lookahead == '[') ADVANCE(191);
      if (lookahead == '\\') ADVANCE(17);
      if (lookahead == '^') ADVANCE(248);
      if (lookahead == '_') ADVANCE(32);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '~') ADVANCE(255);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(208);
      if (sym__not_character_set_1(lookahead)) SKIP(6)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(19);
      END_STATE();
    case 7:
      if (lookahead == '!') ADVANCE(256);
      if (lookahead == '"') ADVANCE(218);
      if (lookahead == '#') ADVANCE(1);
      if (lookahead == '$') ADVANCE(251);
      if (lookahead == '\'') ADVANCE(217);
      if (lookahead == '(') ADVANCE(189);
      if (lookahead == '*') ADVANCE(249);
      if (lookahead == '+') ADVANCE(253);
      if (lookahead == '-') ADVANCE(38);
      if (lookahead == '.') ADVANCE(223);
      if (lookahead == '/') ADVANCE(220);
      if (lookahead == '=') ADVANCE(254);
      if (lookahead == '[') ADVANCE(191);
      if (lookahead == '\\') ADVANCE(17);
      if (lookahead == ']') ADVANCE(192);
      if (lookahead == '^') ADVANCE(248);
      if (lookahead == '_') ADVANCE(32);
      if (lookahead == '~') ADVANCE(255);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(208);
      if (sym__not_character_set_1(lookahead)) SKIP(7)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(19);
      END_STATE();
    case 8:
      if (lookahead == '!') ADVANCE(256);
      if (lookahead == '"') ADVANCE(218);
      if (lookahead == '#') ADVANCE(224);
      if (lookahead == '$') ADVANCE(252);
      if (lookahead == '\'') ADVANCE(217);
      if (lookahead == '(') ADVANCE(189);
      if (lookahead == ')') ADVANCE(190);
      if (lookahead == '*') ADVANCE(249);
      if (lookahead == '+') ADVANCE(253);
      if (lookahead == '-') ADVANCE(240);
      if (lookahead == '.') ADVANCE(222);
      if (lookahead == '/') ADVANCE(220);
      if (lookahead == ':') ADVANCE(245);
      if (lookahead == '=') ADVANCE(254);
      if (lookahead == '?') ADVANCE(247);
      if (lookahead == '[') ADVANCE(191);
      if (lookahead == '\\') ADVANCE(18);
      if (lookahead == '^') ADVANCE(248);
      if (lookahead == '_') ADVANCE(236);
      if (lookahead == '|') ADVANCE(246);
      if (lookahead == '~') ADVANCE(255);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(5)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(205);
      if (lookahead == 160 ||
          lookahead == 5760 ||
          (8192 <= lookahead && lookahead <= 8203) ||
          lookahead == 8239 ||
          lookahead == 8287 ||
          lookahead == 8288 ||
          lookahead == 12288 ||
          lookahead == 65279) ADVANCE(225);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(228);
      if (lookahead != 0) ADVANCE(244);
      END_STATE();
    case 9:
      if (lookahead == '!') ADVANCE(256);
      if (lookahead == '"') ADVANCE(218);
      if (lookahead == '#') ADVANCE(224);
      if (lookahead == '$') ADVANCE(252);
      if (lookahead == '\'') ADVANCE(217);
      if (lookahead == '(') ADVANCE(189);
      if (lookahead == '*') ADVANCE(249);
      if (lookahead == '+') ADVANCE(253);
      if (lookahead == '-') ADVANCE(240);
      if (lookahead == '.') ADVANCE(222);
      if (lookahead == '/') ADVANCE(220);
      if (lookahead == ':') ADVANCE(245);
      if (lookahead == ';') ADVANCE(186);
      if (lookahead == '=') ADVANCE(254);
      if (lookahead == '?') ADVANCE(247);
      if (lookahead == '[') ADVANCE(191);
      if (lookahead == '\\') ADVANCE(18);
      if (lookahead == '^') ADVANCE(248);
      if (lookahead == '_') ADVANCE(236);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '|') ADVANCE(246);
      if (lookahead == '~') ADVANCE(255);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(6)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(205);
      if (lookahead == 160 ||
          lookahead == 5760 ||
          (8192 <= lookahead && lookahead <= 8203) ||
          lookahead == 8239 ||
          lookahead == 8287 ||
          lookahead == 8288 ||
          lookahead == 12288 ||
          lookahead == 65279) ADVANCE(226);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(228);
      if (lookahead != 0) ADVANCE(244);
      END_STATE();
    case 10:
      if (lookahead == '!') ADVANCE(256);
      if (lookahead == '"') ADVANCE(218);
      if (lookahead == '#') ADVANCE(224);
      if (lookahead == '$') ADVANCE(252);
      if (lookahead == '\'') ADVANCE(217);
      if (lookahead == '(') ADVANCE(189);
      if (lookahead == '*') ADVANCE(249);
      if (lookahead == '+') ADVANCE(253);
      if (lookahead == '-') ADVANCE(240);
      if (lookahead == '.') ADVANCE(222);
      if (lookahead == '/') ADVANCE(220);
      if (lookahead == ':') ADVANCE(245);
      if (lookahead == '=') ADVANCE(254);
      if (lookahead == '?') ADVANCE(247);
      if (lookahead == '[') ADVANCE(191);
      if (lookahead == '\\') ADVANCE(18);
      if (lookahead == ']') ADVANCE(192);
      if (lookahead == '^') ADVANCE(248);
      if (lookahead == '_') ADVANCE(236);
      if (lookahead == '|') ADVANCE(246);
      if (lookahead == '~') ADVANCE(255);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(7)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(205);
      if (lookahead == 160 ||
          lookahead == 5760 ||
          (8192 <= lookahead && lookahead <= 8203) ||
          lookahead == 8239 ||
          lookahead == 8287 ||
          lookahead == 8288 ||
          lookahead == 12288 ||
          lookahead == 65279) ADVANCE(227);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(228);
      if (lookahead != 0) ADVANCE(244);
      END_STATE();
    case 11:
      if (lookahead == '"') ADVANCE(218);
      if (lookahead == '#') ADVANCE(214);
      if (lookahead == '$') ADVANCE(216);
      if (sym__not_character_set_1(lookahead)) ADVANCE(215);
      if (lookahead != 0) ADVANCE(214);
      END_STATE();
    case 12:
      if (lookahead == '"') ADVANCE(218);
      if (lookahead == '#') ADVANCE(273);
      if (lookahead == '\'') ADVANCE(217);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '}') ADVANCE(188);
      if (sym__not_character_set_1(lookahead)) ADVANCE(274);
      if (lookahead != 0) ADVANCE(275);
      END_STATE();
    case 13:
      if (lookahead == '#') ADVANCE(1);
      if (lookahead == '$') ADVANCE(33);
      if (('-' <= lookahead && lookahead <= '/') ||
          lookahead == '_') ADVANCE(38);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(22);
      if (sym__not_character_set_1(lookahead)) SKIP(13)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(20);
      END_STATE();
    case 14:
      if (lookahead == '#') ADVANCE(211);
      if (lookahead == '$') ADVANCE(213);
      if (lookahead == '\'') ADVANCE(217);
      if (sym__not_character_set_1(lookahead)) ADVANCE(212);
      if (lookahead != 0) ADVANCE(211);
      END_STATE();
    case 15:
      if (lookahead == '#') ADVANCE(279);
      if (sym__not_character_set_1(lookahead)) ADVANCE(280);
      if (lookahead != 0 &&
          lookahead != '\'') ADVANCE(281);
      END_STATE();
    case 16:
      if (lookahead == '#') ADVANCE(276);
      if (sym__not_character_set_1(lookahead)) ADVANCE(277);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(278);
      END_STATE();
    case 17:
      if (lookahead == '.') ADVANCE(250);
      END_STATE();
    case 18:
      if (lookahead == '.') ADVANCE(250);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(244);
      END_STATE();
    case 19:
      if (lookahead == '.') ADVANCE(38);
      if (lookahead == ':') ADVANCE(31);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(195);
      if (lookahead == ',' ||
          lookahead == '=' ||
          lookahead == '?') ADVANCE(198);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(194);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(194);
      END_STATE();
    case 20:
      if (lookahead == '.') ADVANCE(38);
      if (lookahead == ',' ||
          lookahead == '=' ||
          lookahead == '?') ADVANCE(198);
      if (('-' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(195);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(195);
      END_STATE();
    case 21:
      if (lookahead == '.') ADVANCE(35);
      if (('-' <= lookahead && lookahead <= '/') ||
          lookahead == '_') ADVANCE(38);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(23);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(20);
      END_STATE();
    case 22:
      if (lookahead == '.') ADVANCE(35);
      if (('-' <= lookahead && lookahead <= '/') ||
          lookahead == '_') ADVANCE(38);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(21);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(20);
      END_STATE();
    case 23:
      if (lookahead == '.') ADVANCE(35);
      if (('-' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(38);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(20);
      END_STATE();
    case 24:
      if (lookahead == '.') ADVANCE(36);
      if (('-' <= lookahead && lookahead <= '/') ||
          lookahead == '_') ADVANCE(38);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(26);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(20);
      END_STATE();
    case 25:
      if (lookahead == '.') ADVANCE(36);
      if (('-' <= lookahead && lookahead <= '/') ||
          lookahead == '_') ADVANCE(38);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(24);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(20);
      END_STATE();
    case 26:
      if (lookahead == '.') ADVANCE(36);
      if (('-' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(38);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(20);
      END_STATE();
    case 27:
      if (lookahead == '.') ADVANCE(37);
      if (('-' <= lookahead && lookahead <= '/') ||
          lookahead == '_') ADVANCE(38);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(29);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(20);
      END_STATE();
    case 28:
      if (lookahead == '.') ADVANCE(37);
      if (('-' <= lookahead && lookahead <= '/') ||
          lookahead == '_') ADVANCE(38);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(27);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(20);
      END_STATE();
    case 29:
      if (lookahead == '.') ADVANCE(37);
      if (('-' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(38);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(20);
      END_STATE();
    case 30:
      if (lookahead == '/') ADVANCE(259);
      END_STATE();
    case 31:
      if (lookahead == '/') ADVANCE(30);
      END_STATE();
    case 32:
      if (lookahead == ':') ADVANCE(31);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(38);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(32);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(19);
      END_STATE();
    case 33:
      if (lookahead == '{') ADVANCE(39);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(201);
      END_STATE();
    case 34:
      if (lookahead == '}') ADVANCE(202);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(34);
      END_STATE();
    case 35:
      if (('-' <= lookahead && lookahead <= '/') ||
          lookahead == '_') ADVANCE(38);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(28);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(20);
      END_STATE();
    case 36:
      if (('-' <= lookahead && lookahead <= '/') ||
          lookahead == '_') ADVANCE(38);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(264);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(20);
      END_STATE();
    case 37:
      if (('-' <= lookahead && lookahead <= '/') ||
          lookahead == '_') ADVANCE(38);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(25);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(20);
      END_STATE();
    case 38:
      if (('-' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(38);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(20);
      END_STATE();
    case 39:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(34);
      END_STATE();
    case 40:
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(244);
      END_STATE();
    case 41:
      if (eof) ADVANCE(43);
      if (lookahead == '!') ADVANCE(256);
      if (lookahead == '"') ADVANCE(218);
      if (lookahead == '#') ADVANCE(1);
      if (lookahead == '$') ADVANCE(251);
      if (lookahead == '\'') ADVANCE(217);
      if (lookahead == '(') ADVANCE(189);
      if (lookahead == ')') ADVANCE(190);
      if (lookahead == '*') ADVANCE(249);
      if (lookahead == '+') ADVANCE(253);
      if (lookahead == '.') ADVANCE(221);
      if (lookahead == '/') ADVANCE(219);
      if (lookahead == ';') ADVANCE(186);
      if (lookahead == '=') ADVANCE(254);
      if (lookahead == '[') ADVANCE(191);
      if (lookahead == '\\') ADVANCE(17);
      if (lookahead == ']') ADVANCE(192);
      if (lookahead == '^') ADVANCE(248);
      if (lookahead == 'a') ADVANCE(94);
      if (lookahead == 'b') ADVANCE(69);
      if (lookahead == 'c') ADVANCE(147);
      if (lookahead == 'h') ADVANCE(105);
      if (lookahead == 'l') ADVANCE(148);
      if (lookahead == 'r') ADVANCE(106);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '}') ADVANCE(188);
      if (lookahead == '~') ADVANCE(255);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(45);
      if (sym__not_character_set_1(lookahead)) SKIP(41)
      if (('A' <= lookahead && lookahead <= '_') ||
          ('d' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 42:
      if (eof) ADVANCE(43);
      if (lookahead == '#') ADVANCE(1);
      if (lookahead == 'a') ADVANCE(94);
      if (lookahead == 'b') ADVANCE(69);
      if (lookahead == 'c') ADVANCE(147);
      if (lookahead == 'h') ADVANCE(105);
      if (lookahead == 'l') ADVANCE(148);
      if (lookahead == 'r') ADVANCE(106);
      if (lookahead == '}') ADVANCE(188);
      if (sym__not_character_set_1(lookahead)) SKIP(42)
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('d' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(185);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(45);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(184);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(86);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(114);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(79);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(127);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(80);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(81);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(82);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(83);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(84);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(85);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(137);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(138);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(139);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(140);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(141);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(142);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(87);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(88);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(89);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(90);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(91);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(92);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == '_') ADVANCE(115);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'a') ADVANCE(128);
      if (lookahead == 'o') ADVANCE(103);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'a') ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'a') ADVANCE(146);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'a') ADVANCE(48);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'a') ADVANCE(50);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'a') ADVANCE(51);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'a') ADVANCE(52);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'a') ADVANCE(53);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'a') ADVANCE(54);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'a') ADVANCE(55);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'b') ADVANCE(129);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'b') ADVANCE(130);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'b') ADVANCE(131);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'b') ADVANCE(132);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'b') ADVANCE(133);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'b') ADVANCE(134);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'b') ADVANCE(135);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'b') ADVANCE(177);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'b') ADVANCE(178);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'b') ADVANCE(179);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'b') ADVANCE(180);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'b') ADVANCE(181);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'b') ADVANCE(182);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'b') ADVANCE(183);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'c') ADVANCE(120);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'c') ADVANCE(96);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'c') ADVANCE(121);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'c') ADVANCE(107);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'c') ADVANCE(122);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'c') ADVANCE(123);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'c') ADVANCE(124);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'c') ADVANCE(109);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'c') ADVANCE(125);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'c') ADVANCE(126);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'd') ADVANCE(176);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'd') ADVANCE(108);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'e') ADVANCE(70);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'e') ADVANCE(175);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'e') ADVANCE(161);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'e') ADVANCE(160);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'e') ADVANCE(157);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'e') ADVANCE(145);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 111:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'e') ADVANCE(64);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 112:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'e') ADVANCE(158);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'e') ADVANCE(159);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'f') ADVANCE(117);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'f') ADVANCE(119);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'g') ADVANCE(46);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'i') ADVANCE(136);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'i') ADVANCE(164);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'i') ADVANCE(143);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 120:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'k') ADVANCE(269);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'k') ADVANCE(266);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'k') ADVANCE(271);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 123:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'k') ADVANCE(272);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'k') ADVANCE(270);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'k') ADVANCE(268);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'k') ADVANCE(267);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'l') ADVANCE(168);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'l') ADVANCE(71);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'l') ADVANCE(149);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 130:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'l') ADVANCE(150);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 131:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'l') ADVANCE(151);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'l') ADVANCE(152);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'l') ADVANCE(153);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 134:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'l') ADVANCE(154);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'l') ADVANCE(155);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 136:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'l') ADVANCE(166);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 137:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'l') ADVANCE(169);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'l') ADVANCE(170);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 139:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'l') ADVANCE(171);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 140:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'l') ADVANCE(172);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 141:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'l') ADVANCE(173);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 142:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'l') ADVANCE(174);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 143:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'l') ADVANCE(167);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 144:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'n') ADVANCE(163);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 145:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'n') ADVANCE(165);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 146:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'n') ADVANCE(100);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 147:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'o') ADVANCE(144);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 148:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'o') ADVANCE(116);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 149:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'o') ADVANCE(93);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 150:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'o') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 151:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'o') ADVANCE(97);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 152:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'o') ADVANCE(98);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 153:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'o') ADVANCE(99);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 154:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'o') ADVANCE(101);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 155:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'o') ADVANCE(102);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 156:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'r') ADVANCE(118);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 157:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'r') ADVANCE(65);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 158:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'r') ADVANCE(66);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 159:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'r') ADVANCE(67);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 160:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'r') ADVANCE(68);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 161:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 's') ADVANCE(162);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 162:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 's') ADVANCE(62);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 163:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 't') ADVANCE(110);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 164:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 't') ADVANCE(111);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 165:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 't') ADVANCE(63);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 166:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 't') ADVANCE(112);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 167:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 't') ADVANCE(113);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 168:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'u') ADVANCE(72);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 169:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'u') ADVANCE(73);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 170:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'u') ADVANCE(74);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 171:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'u') ADVANCE(75);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 172:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'u') ADVANCE(76);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 173:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'u') ADVANCE(77);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 174:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'u') ADVANCE(78);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 175:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'w') ADVANCE(156);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 176:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'y') ADVANCE(47);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 177:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'y') ADVANCE(49);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 178:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'y') ADVANCE(56);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 179:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'y') ADVANCE(57);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 180:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'y') ADVANCE(58);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 181:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'y') ADVANCE(59);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 182:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'y') ADVANCE(60);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 183:
      ACCEPT_TOKEN(sym_directive);
      if (lookahead == 'y') ADVANCE(61);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 184:
      ACCEPT_TOKEN(sym_directive);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(185);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(184);
      END_STATE();
    case 185:
      ACCEPT_TOKEN(sym_directive);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 186:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 187:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 188:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 189:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 190:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 191:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 192:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 193:
      ACCEPT_TOKEN(sym_generic);
      if (lookahead == '-') ADVANCE(196);
      if (lookahead == '.') ADVANCE(240);
      if (lookahead == '/') ADVANCE(195);
      if (lookahead == ':') ADVANCE(241);
      if (lookahead == ',' ||
          lookahead == '=' ||
          lookahead == '?') ADVANCE(197);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(193);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 194:
      ACCEPT_TOKEN(sym_generic);
      if (lookahead == '.') ADVANCE(38);
      if (lookahead == ':') ADVANCE(31);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(195);
      if (lookahead == ',' ||
          lookahead == '=' ||
          lookahead == '?') ADVANCE(198);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(194);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(194);
      END_STATE();
    case 195:
      ACCEPT_TOKEN(sym_generic);
      if (lookahead == '.') ADVANCE(38);
      if (lookahead == ',' ||
          lookahead == '=' ||
          lookahead == '?') ADVANCE(198);
      if (('-' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(195);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(195);
      END_STATE();
    case 196:
      ACCEPT_TOKEN(sym_generic);
      if (lookahead == '.') ADVANCE(240);
      if (lookahead == '/') ADVANCE(195);
      if (lookahead == ',' ||
          lookahead == '=' ||
          lookahead == '?') ADVANCE(197);
      if (('-' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(196);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(196);
      END_STATE();
    case 197:
      ACCEPT_TOKEN(sym_generic);
      if (lookahead == '/') ADVANCE(198);
      if (lookahead == ',' ||
          lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(197);
      END_STATE();
    case 198:
      ACCEPT_TOKEN(sym_generic);
      if (lookahead == ',' ||
          lookahead == '-' ||
          ('/' <= lookahead && lookahead <= '9') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(198);
      END_STATE();
    case 199:
      ACCEPT_TOKEN(sym_metric);
      if (lookahead == '-') ADVANCE(196);
      if (lookahead == '.') ADVANCE(240);
      if (lookahead == '/') ADVANCE(195);
      if (lookahead == ':') ADVANCE(241);
      if (lookahead == ',' ||
          lookahead == '=' ||
          lookahead == '?') ADVANCE(197);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(193);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 200:
      ACCEPT_TOKEN(sym_metric);
      if (lookahead == '.') ADVANCE(38);
      if (lookahead == ':') ADVANCE(31);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(195);
      if (lookahead == ',' ||
          lookahead == '=' ||
          lookahead == '?') ADVANCE(198);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(194);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(194);
      END_STATE();
    case 201:
      ACCEPT_TOKEN(aux_sym_variable_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(201);
      END_STATE();
    case 202:
      ACCEPT_TOKEN(aux_sym_variable_token2);
      END_STATE();
    case 203:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '-') ADVANCE(240);
      if (lookahead == '.') ADVANCE(237);
      if (lookahead == '/') ADVANCE(38);
      if (lookahead == ':') ADVANCE(241);
      if (lookahead == '_') ADVANCE(236);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(209);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(199);
      END_STATE();
    case 204:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '-') ADVANCE(240);
      if (lookahead == '.') ADVANCE(237);
      if (lookahead == '/') ADVANCE(38);
      if (lookahead == ':') ADVANCE(241);
      if (lookahead == '_') ADVANCE(236);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(203);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(199);
      END_STATE();
    case 205:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '-') ADVANCE(240);
      if (lookahead == '.') ADVANCE(237);
      if (lookahead == '/') ADVANCE(38);
      if (lookahead == ':') ADVANCE(241);
      if (lookahead == '_') ADVANCE(236);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(204);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(199);
      END_STATE();
    case 206:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(35);
      if (lookahead == ':') ADVANCE(31);
      if (lookahead == '_') ADVANCE(32);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(38);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(210);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(200);
      END_STATE();
    case 207:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(35);
      if (lookahead == ':') ADVANCE(31);
      if (lookahead == '_') ADVANCE(32);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(38);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(206);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(200);
      END_STATE();
    case 208:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(35);
      if (lookahead == ':') ADVANCE(31);
      if (lookahead == '_') ADVANCE(32);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(38);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(207);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(200);
      END_STATE();
    case 209:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '/') ADVANCE(38);
      if (lookahead == ':') ADVANCE(241);
      if (lookahead == '_') ADVANCE(236);
      if (lookahead == '-' ||
          lookahead == '.') ADVANCE(240);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(209);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(199);
      END_STATE();
    case 210:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == ':') ADVANCE(31);
      if (lookahead == '_') ADVANCE(32);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(38);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(210);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(200);
      END_STATE();
    case 211:
      ACCEPT_TOKEN(sym_sq_string_content);
      END_STATE();
    case 212:
      ACCEPT_TOKEN(sym_sq_string_content);
      if (lookahead == '#') ADVANCE(211);
      if (lookahead == '$') ADVANCE(213);
      if (sym__not_character_set_1(lookahead)) ADVANCE(212);
      if (lookahead != 0 &&
          lookahead != '\'') ADVANCE(211);
      END_STATE();
    case 213:
      ACCEPT_TOKEN(sym_sq_string_content);
      if (lookahead == '{') ADVANCE(39);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(201);
      END_STATE();
    case 214:
      ACCEPT_TOKEN(sym_dq_string_content);
      END_STATE();
    case 215:
      ACCEPT_TOKEN(sym_dq_string_content);
      if (lookahead == '#') ADVANCE(214);
      if (lookahead == '$') ADVANCE(216);
      if (sym__not_character_set_1(lookahead)) ADVANCE(215);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(214);
      END_STATE();
    case 216:
      ACCEPT_TOKEN(sym_dq_string_content);
      if (lookahead == '{') ADVANCE(39);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(201);
      END_STATE();
    case 217:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 218:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 219:
      ACCEPT_TOKEN(anon_sym_SLASH);
      END_STATE();
    case 220:
      ACCEPT_TOKEN(anon_sym_SLASH);
      if (('-' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(38);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(20);
      END_STATE();
    case 221:
      ACCEPT_TOKEN(anon_sym_DOT);
      END_STATE();
    case 222:
      ACCEPT_TOKEN(anon_sym_DOT);
      if (lookahead == '/') ADVANCE(38);
      if (('-' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(240);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(229);
      END_STATE();
    case 223:
      ACCEPT_TOKEN(anon_sym_DOT);
      if (('-' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(38);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(20);
      END_STATE();
    case 224:
      ACCEPT_TOKEN(sym_regex_pattern);
      if (lookahead == '\n') ADVANCE(44);
      if (lookahead == '\\') ADVANCE(2);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ' ||
          lookahead == '/' ||
          lookahead == '[') ADVANCE(1);
      if (lookahead != 0) ADVANCE(224);
      END_STATE();
    case 225:
      ACCEPT_TOKEN(sym_regex_pattern);
      if (lookahead == '!') ADVANCE(256);
      if (lookahead == '"') ADVANCE(218);
      if (lookahead == '#') ADVANCE(224);
      if (lookahead == '$') ADVANCE(252);
      if (lookahead == '\'') ADVANCE(217);
      if (lookahead == '(') ADVANCE(189);
      if (lookahead == ')') ADVANCE(190);
      if (lookahead == '*') ADVANCE(249);
      if (lookahead == '+') ADVANCE(253);
      if (lookahead == '-') ADVANCE(240);
      if (lookahead == '.') ADVANCE(222);
      if (lookahead == '/') ADVANCE(220);
      if (lookahead == '=') ADVANCE(254);
      if (lookahead == '[') ADVANCE(191);
      if (lookahead == '\\') ADVANCE(18);
      if (lookahead == '^') ADVANCE(248);
      if (lookahead == '_') ADVANCE(236);
      if (lookahead == '~') ADVANCE(255);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(5)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(205);
      if (lookahead == 160 ||
          lookahead == 5760 ||
          (8192 <= lookahead && lookahead <= 8203) ||
          lookahead == 8239 ||
          lookahead == 8287 ||
          lookahead == 8288 ||
          lookahead == 12288 ||
          lookahead == 65279) ADVANCE(225);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(228);
      if (lookahead != 0) ADVANCE(244);
      END_STATE();
    case 226:
      ACCEPT_TOKEN(sym_regex_pattern);
      if (lookahead == '!') ADVANCE(256);
      if (lookahead == '"') ADVANCE(218);
      if (lookahead == '#') ADVANCE(224);
      if (lookahead == '$') ADVANCE(252);
      if (lookahead == '\'') ADVANCE(217);
      if (lookahead == '(') ADVANCE(189);
      if (lookahead == '*') ADVANCE(249);
      if (lookahead == '+') ADVANCE(253);
      if (lookahead == '-') ADVANCE(240);
      if (lookahead == '.') ADVANCE(222);
      if (lookahead == '/') ADVANCE(220);
      if (lookahead == ';') ADVANCE(186);
      if (lookahead == '=') ADVANCE(254);
      if (lookahead == '[') ADVANCE(191);
      if (lookahead == '\\') ADVANCE(18);
      if (lookahead == '^') ADVANCE(248);
      if (lookahead == '_') ADVANCE(236);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '~') ADVANCE(255);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(6)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(205);
      if (lookahead == 160 ||
          lookahead == 5760 ||
          (8192 <= lookahead && lookahead <= 8203) ||
          lookahead == 8239 ||
          lookahead == 8287 ||
          lookahead == 8288 ||
          lookahead == 12288 ||
          lookahead == 65279) ADVANCE(226);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(228);
      if (lookahead != 0) ADVANCE(244);
      END_STATE();
    case 227:
      ACCEPT_TOKEN(sym_regex_pattern);
      if (lookahead == '!') ADVANCE(256);
      if (lookahead == '"') ADVANCE(218);
      if (lookahead == '#') ADVANCE(224);
      if (lookahead == '$') ADVANCE(252);
      if (lookahead == '\'') ADVANCE(217);
      if (lookahead == '(') ADVANCE(189);
      if (lookahead == '*') ADVANCE(249);
      if (lookahead == '+') ADVANCE(253);
      if (lookahead == '-') ADVANCE(240);
      if (lookahead == '.') ADVANCE(222);
      if (lookahead == '/') ADVANCE(220);
      if (lookahead == '=') ADVANCE(254);
      if (lookahead == '[') ADVANCE(191);
      if (lookahead == '\\') ADVANCE(18);
      if (lookahead == ']') ADVANCE(192);
      if (lookahead == '^') ADVANCE(248);
      if (lookahead == '_') ADVANCE(236);
      if (lookahead == '~') ADVANCE(255);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(7)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(205);
      if (lookahead == 160 ||
          lookahead == 5760 ||
          (8192 <= lookahead && lookahead <= 8203) ||
          lookahead == 8239 ||
          lookahead == 8287 ||
          lookahead == 8288 ||
          lookahead == 12288 ||
          lookahead == 65279) ADVANCE(227);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(228);
      if (lookahead != 0) ADVANCE(244);
      END_STATE();
    case 228:
      ACCEPT_TOKEN(sym_regex_pattern);
      if (lookahead == '-') ADVANCE(196);
      if (lookahead == '.') ADVANCE(240);
      if (lookahead == '/') ADVANCE(195);
      if (lookahead == ':') ADVANCE(241);
      if (lookahead == '\\') ADVANCE(40);
      if (lookahead == ',' ||
          lookahead == '=' ||
          lookahead == '?') ADVANCE(197);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(193);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ' &&
          lookahead != '[') ADVANCE(244);
      END_STATE();
    case 229:
      ACCEPT_TOKEN(sym_regex_pattern);
      if (lookahead == '.') ADVANCE(240);
      if (lookahead == '/') ADVANCE(195);
      if (lookahead == '\\') ADVANCE(40);
      if (lookahead == ',' ||
          lookahead == '=' ||
          lookahead == '?') ADVANCE(197);
      if (('-' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(196);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(196);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ' &&
          lookahead != '[') ADVANCE(244);
      END_STATE();
    case 230:
      ACCEPT_TOKEN(sym_regex_pattern);
      if (lookahead == '.') ADVANCE(238);
      if (lookahead == '/') ADVANCE(38);
      if (lookahead == '\\') ADVANCE(40);
      if (lookahead == '-' ||
          lookahead == '_') ADVANCE(240);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(232);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(229);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ' &&
          lookahead != '[') ADVANCE(244);
      END_STATE();
    case 231:
      ACCEPT_TOKEN(sym_regex_pattern);
      if (lookahead == '.') ADVANCE(238);
      if (lookahead == '/') ADVANCE(38);
      if (lookahead == '\\') ADVANCE(40);
      if (lookahead == '-' ||
          lookahead == '_') ADVANCE(240);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(230);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(229);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ' &&
          lookahead != '[') ADVANCE(244);
      END_STATE();
    case 232:
      ACCEPT_TOKEN(sym_regex_pattern);
      if (lookahead == '.') ADVANCE(238);
      if (lookahead == '/') ADVANCE(38);
      if (lookahead == '\\') ADVANCE(40);
      if (('-' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(240);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(229);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ' &&
          lookahead != '[') ADVANCE(244);
      END_STATE();
    case 233:
      ACCEPT_TOKEN(sym_regex_pattern);
      if (lookahead == '.') ADVANCE(239);
      if (lookahead == '/') ADVANCE(38);
      if (lookahead == '\\') ADVANCE(40);
      if (lookahead == '-' ||
          lookahead == '_') ADVANCE(240);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(235);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(229);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ' &&
          lookahead != '[') ADVANCE(244);
      END_STATE();
    case 234:
      ACCEPT_TOKEN(sym_regex_pattern);
      if (lookahead == '.') ADVANCE(239);
      if (lookahead == '/') ADVANCE(38);
      if (lookahead == '\\') ADVANCE(40);
      if (lookahead == '-' ||
          lookahead == '_') ADVANCE(240);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(233);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(229);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ' &&
          lookahead != '[') ADVANCE(244);
      END_STATE();
    case 235:
      ACCEPT_TOKEN(sym_regex_pattern);
      if (lookahead == '.') ADVANCE(239);
      if (lookahead == '/') ADVANCE(38);
      if (lookahead == '\\') ADVANCE(40);
      if (('-' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(240);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(229);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ' &&
          lookahead != '[') ADVANCE(244);
      END_STATE();
    case 236:
      ACCEPT_TOKEN(sym_regex_pattern);
      if (lookahead == '/') ADVANCE(38);
      if (lookahead == ':') ADVANCE(241);
      if (lookahead == '\\') ADVANCE(40);
      if (lookahead == '-' ||
          lookahead == '.') ADVANCE(240);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(236);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(228);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ' &&
          lookahead != '[') ADVANCE(244);
      END_STATE();
    case 237:
      ACCEPT_TOKEN(sym_regex_pattern);
      if (lookahead == '/') ADVANCE(38);
      if (lookahead == '\\') ADVANCE(40);
      if (lookahead == '-' ||
          lookahead == '.' ||
          lookahead == '_') ADVANCE(240);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(234);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(229);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ' &&
          lookahead != '[') ADVANCE(244);
      END_STATE();
    case 238:
      ACCEPT_TOKEN(sym_regex_pattern);
      if (lookahead == '/') ADVANCE(38);
      if (lookahead == '\\') ADVANCE(40);
      if (lookahead == '-' ||
          lookahead == '.' ||
          lookahead == '_') ADVANCE(240);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(261);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(229);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ' &&
          lookahead != '[') ADVANCE(244);
      END_STATE();
    case 239:
      ACCEPT_TOKEN(sym_regex_pattern);
      if (lookahead == '/') ADVANCE(38);
      if (lookahead == '\\') ADVANCE(40);
      if (lookahead == '-' ||
          lookahead == '.' ||
          lookahead == '_') ADVANCE(240);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(231);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(229);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ' &&
          lookahead != '[') ADVANCE(244);
      END_STATE();
    case 240:
      ACCEPT_TOKEN(sym_regex_pattern);
      if (lookahead == '/') ADVANCE(38);
      if (lookahead == '\\') ADVANCE(40);
      if (('-' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(240);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(229);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ' &&
          lookahead != '[') ADVANCE(244);
      END_STATE();
    case 241:
      ACCEPT_TOKEN(sym_regex_pattern);
      if (lookahead == '/') ADVANCE(30);
      if (lookahead == '\\') ADVANCE(40);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ' &&
          lookahead != '[') ADVANCE(244);
      END_STATE();
    case 242:
      ACCEPT_TOKEN(sym_regex_pattern);
      if (lookahead == '\\') ADVANCE(40);
      if (lookahead == '}') ADVANCE(202);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(242);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ' &&
          lookahead != '/' &&
          lookahead != '[') ADVANCE(244);
      END_STATE();
    case 243:
      ACCEPT_TOKEN(sym_regex_pattern);
      if (lookahead == '\\') ADVANCE(40);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(242);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ' &&
          lookahead != '/' &&
          lookahead != '[') ADVANCE(244);
      END_STATE();
    case 244:
      ACCEPT_TOKEN(sym_regex_pattern);
      if (lookahead == '\\') ADVANCE(40);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ' &&
          lookahead != '/' &&
          lookahead != '[') ADVANCE(244);
      END_STATE();
    case 245:
      ACCEPT_TOKEN(sym__colon);
      END_STATE();
    case 246:
      ACCEPT_TOKEN(sym__or);
      END_STATE();
    case 247:
      ACCEPT_TOKEN(sym__option);
      END_STATE();
    case 248:
      ACCEPT_TOKEN(sym__carrot);
      END_STATE();
    case 249:
      ACCEPT_TOKEN(sym__star);
      if (lookahead == '~') ADVANCE(258);
      END_STATE();
    case 250:
      ACCEPT_TOKEN(sym_escaped_dot);
      END_STATE();
    case 251:
      ACCEPT_TOKEN(sym__eol);
      if (lookahead == '{') ADVANCE(39);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(201);
      END_STATE();
    case 252:
      ACCEPT_TOKEN(sym__eol);
      if (lookahead == '{') ADVANCE(243);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(201);
      END_STATE();
    case 253:
      ACCEPT_TOKEN(sym__plus);
      END_STATE();
    case 254:
      ACCEPT_TOKEN(sym__eq);
      END_STATE();
    case 255:
      ACCEPT_TOKEN(sym__tild);
      if (lookahead == '*') ADVANCE(257);
      END_STATE();
    case 256:
      ACCEPT_TOKEN(sym__not);
      END_STATE();
    case 257:
      ACCEPT_TOKEN(sym__ts_modifier);
      END_STATE();
    case 258:
      ACCEPT_TOKEN(sym__st_modifier);
      END_STATE();
    case 259:
      ACCEPT_TOKEN(sym_scheme);
      END_STATE();
    case 260:
      ACCEPT_TOKEN(sym_ipv4);
      if (lookahead == '/') ADVANCE(38);
      if (lookahead == '-' ||
          lookahead == '.' ||
          lookahead == '_') ADVANCE(240);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(262);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(229);
      END_STATE();
    case 261:
      ACCEPT_TOKEN(sym_ipv4);
      if (lookahead == '/') ADVANCE(38);
      if (lookahead == '-' ||
          lookahead == '.' ||
          lookahead == '_') ADVANCE(240);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(260);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(229);
      END_STATE();
    case 262:
      ACCEPT_TOKEN(sym_ipv4);
      if (lookahead == '/') ADVANCE(38);
      if (('-' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(240);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(229);
      END_STATE();
    case 263:
      ACCEPT_TOKEN(sym_ipv4);
      if (('-' <= lookahead && lookahead <= '/') ||
          lookahead == '_') ADVANCE(38);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(265);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(20);
      END_STATE();
    case 264:
      ACCEPT_TOKEN(sym_ipv4);
      if (('-' <= lookahead && lookahead <= '/') ||
          lookahead == '_') ADVANCE(38);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(263);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(20);
      END_STATE();
    case 265:
      ACCEPT_TOKEN(sym_ipv4);
      if (('-' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(38);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(20);
      END_STATE();
    case 266:
      ACCEPT_TOKEN(anon_sym_access_by_lua_block);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 267:
      ACCEPT_TOKEN(anon_sym_header_filter_by_lua_block);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 268:
      ACCEPT_TOKEN(anon_sym_body_filter_by_lua_block);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 269:
      ACCEPT_TOKEN(anon_sym_log_by_lua_block);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 270:
      ACCEPT_TOKEN(anon_sym_balancer_by_lua_block);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 271:
      ACCEPT_TOKEN(anon_sym_content_by_lua_block);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 272:
      ACCEPT_TOKEN(anon_sym_rewrite_by_lua_block);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(185);
      END_STATE();
    case 273:
      ACCEPT_TOKEN(aux_sym__lua_code_token1);
      if (lookahead == '\n') ADVANCE(275);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\'' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(273);
      END_STATE();
    case 274:
      ACCEPT_TOKEN(aux_sym__lua_code_token1);
      if (lookahead == '#') ADVANCE(273);
      if (sym__not_character_set_1(lookahead)) ADVANCE(274);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\'' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(275);
      END_STATE();
    case 275:
      ACCEPT_TOKEN(aux_sym__lua_code_token1);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\'' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(275);
      END_STATE();
    case 276:
      ACCEPT_TOKEN(aux_sym__lua_code_token2);
      if (lookahead == '\n') ADVANCE(278);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(276);
      END_STATE();
    case 277:
      ACCEPT_TOKEN(aux_sym__lua_code_token2);
      if (lookahead == '#') ADVANCE(276);
      if (sym__not_character_set_1(lookahead)) ADVANCE(277);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(278);
      END_STATE();
    case 278:
      ACCEPT_TOKEN(aux_sym__lua_code_token2);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(278);
      END_STATE();
    case 279:
      ACCEPT_TOKEN(aux_sym__lua_code_token3);
      if (lookahead == '\n') ADVANCE(281);
      if (lookahead != 0 &&
          lookahead != '\'') ADVANCE(279);
      END_STATE();
    case 280:
      ACCEPT_TOKEN(aux_sym__lua_code_token3);
      if (lookahead == '#') ADVANCE(279);
      if (sym__not_character_set_1(lookahead)) ADVANCE(280);
      if (lookahead != 0 &&
          lookahead != '\'') ADVANCE(281);
      END_STATE();
    case 281:
      ACCEPT_TOKEN(aux_sym__lua_code_token3);
      if (lookahead != 0 &&
          lookahead != '\'') ADVANCE(281);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 42},
  [2] = {.lex_state = 3},
  [3] = {.lex_state = 3},
  [4] = {.lex_state = 3},
  [5] = {.lex_state = 3},
  [6] = {.lex_state = 3},
  [7] = {.lex_state = 3},
  [8] = {.lex_state = 3},
  [9] = {.lex_state = 3},
  [10] = {.lex_state = 3},
  [11] = {.lex_state = 3},
  [12] = {.lex_state = 3},
  [13] = {.lex_state = 3},
  [14] = {.lex_state = 3},
  [15] = {.lex_state = 3},
  [16] = {.lex_state = 3},
  [17] = {.lex_state = 3},
  [18] = {.lex_state = 3},
  [19] = {.lex_state = 3},
  [20] = {.lex_state = 3},
  [21] = {.lex_state = 3},
  [22] = {.lex_state = 3},
  [23] = {.lex_state = 9},
  [24] = {.lex_state = 10},
  [25] = {.lex_state = 8},
  [26] = {.lex_state = 42},
  [27] = {.lex_state = 42},
  [28] = {.lex_state = 42},
  [29] = {.lex_state = 42},
  [30] = {.lex_state = 42},
  [31] = {.lex_state = 42},
  [32] = {.lex_state = 42},
  [33] = {.lex_state = 42},
  [34] = {.lex_state = 42},
  [35] = {.lex_state = 42},
  [36] = {.lex_state = 42},
  [37] = {.lex_state = 42},
  [38] = {.lex_state = 14},
  [39] = {.lex_state = 11},
  [40] = {.lex_state = 14},
  [41] = {.lex_state = 11},
  [42] = {.lex_state = 14},
  [43] = {.lex_state = 11},
  [44] = {.lex_state = 12},
  [45] = {.lex_state = 12},
  [46] = {.lex_state = 12},
  [47] = {.lex_state = 13},
  [48] = {.lex_state = 12},
  [49] = {.lex_state = 11},
  [50] = {.lex_state = 12},
  [51] = {.lex_state = 12},
  [52] = {.lex_state = 12},
  [53] = {.lex_state = 14},
  [54] = {.lex_state = 12},
  [55] = {.lex_state = 12},
  [56] = {.lex_state = 12},
  [57] = {.lex_state = 12},
  [58] = {.lex_state = 12},
  [59] = {.lex_state = 12},
  [60] = {.lex_state = 12},
  [61] = {.lex_state = 0},
  [62] = {.lex_state = 12},
  [63] = {.lex_state = 12},
  [64] = {.lex_state = 12},
  [65] = {.lex_state = 12},
  [66] = {.lex_state = 15},
  [67] = {.lex_state = 16},
  [68] = {.lex_state = 0},
  [69] = {.lex_state = 0},
  [70] = {.lex_state = 15},
  [71] = {.lex_state = 16},
  [72] = {.lex_state = 0},
  [73] = {.lex_state = 15},
  [74] = {.lex_state = 0},
  [75] = {.lex_state = 0},
  [76] = {.lex_state = 16},
  [77] = {.lex_state = 15},
  [78] = {.lex_state = 0},
  [79] = {.lex_state = 0},
  [80] = {.lex_state = 0},
  [81] = {.lex_state = 15},
  [82] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
    [sym_directive] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [sym_metric] = ACTIONS(1),
    [aux_sym_variable_token1] = ACTIONS(1),
    [aux_sym_variable_token2] = ACTIONS(1),
    [sym_number] = ACTIONS(1),
    [anon_sym_SQUOTE] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [anon_sym_SLASH] = ACTIONS(1),
    [anon_sym_DOT] = ACTIONS(1),
    [sym__colon] = ACTIONS(1),
    [sym__or] = ACTIONS(1),
    [sym__option] = ACTIONS(1),
    [sym__carrot] = ACTIONS(1),
    [sym__star] = ACTIONS(1),
    [sym_escaped_dot] = ACTIONS(1),
    [sym__eol] = ACTIONS(1),
    [sym__plus] = ACTIONS(1),
    [sym__eq] = ACTIONS(1),
    [sym__tild] = ACTIONS(1),
    [sym__not] = ACTIONS(1),
    [sym__ts_modifier] = ACTIONS(1),
    [sym__st_modifier] = ACTIONS(1),
    [anon_sym_access_by_lua_block] = ACTIONS(1),
    [anon_sym_header_filter_by_lua_block] = ACTIONS(1),
    [anon_sym_body_filter_by_lua_block] = ACTIONS(1),
    [anon_sym_log_by_lua_block] = ACTIONS(1),
    [anon_sym_balancer_by_lua_block] = ACTIONS(1),
    [anon_sym_content_by_lua_block] = ACTIONS(1),
    [anon_sym_rewrite_by_lua_block] = ACTIONS(1),
  },
  [1] = {
    [sym_conf] = STATE(79),
    [sym__directives] = STATE(29),
    [sym_simple_directive] = STATE(29),
    [sym_block_directive] = STATE(29),
    [sym__lua_block_directives] = STATE(61),
    [sym_lua_block_directive] = STATE(29),
    [aux_sym_conf_repeat1] = STATE(29),
    [ts_builtin_sym_end] = ACTIONS(5),
    [sym_comment] = ACTIONS(3),
    [sym_directive] = ACTIONS(7),
    [anon_sym_access_by_lua_block] = ACTIONS(9),
    [anon_sym_header_filter_by_lua_block] = ACTIONS(9),
    [anon_sym_body_filter_by_lua_block] = ACTIONS(9),
    [anon_sym_log_by_lua_block] = ACTIONS(9),
    [anon_sym_balancer_by_lua_block] = ACTIONS(9),
    [anon_sym_content_by_lua_block] = ACTIONS(9),
    [anon_sym_rewrite_by_lua_block] = ACTIONS(9),
  },
  [2] = {
    [sym_block] = STATE(31),
    [sym_parenthese] = STATE(11),
    [sym_bracket] = STATE(11),
    [sym_param] = STATE(3),
    [sym_variable] = STATE(11),
    [sym_string] = STATE(11),
    [sym_regex] = STATE(11),
    [sym__regex_tokens] = STATE(18),
    [sym_modifier] = STATE(11),
    [sym_uri] = STATE(11),
    [aux_sym_simple_directive_repeat1] = STATE(3),
    [sym_comment] = ACTIONS(3),
    [anon_sym_SEMI] = ACTIONS(11),
    [anon_sym_LBRACE] = ACTIONS(13),
    [anon_sym_LPAREN] = ACTIONS(15),
    [anon_sym_LBRACK] = ACTIONS(17),
    [sym_generic] = ACTIONS(19),
    [sym_metric] = ACTIONS(19),
    [aux_sym_variable_token1] = ACTIONS(21),
    [aux_sym_variable_token2] = ACTIONS(21),
    [sym_number] = ACTIONS(19),
    [anon_sym_SQUOTE] = ACTIONS(23),
    [anon_sym_DQUOTE] = ACTIONS(25),
    [anon_sym_SLASH] = ACTIONS(27),
    [anon_sym_DOT] = ACTIONS(27),
    [sym__colon] = ACTIONS(29),
    [sym__or] = ACTIONS(29),
    [sym__option] = ACTIONS(29),
    [sym__carrot] = ACTIONS(29),
    [sym__star] = ACTIONS(31),
    [sym_escaped_dot] = ACTIONS(33),
    [sym__eol] = ACTIONS(31),
    [sym__plus] = ACTIONS(29),
    [sym__eq] = ACTIONS(35),
    [sym__tild] = ACTIONS(37),
    [sym__not] = ACTIONS(35),
    [sym__ts_modifier] = ACTIONS(35),
    [sym__st_modifier] = ACTIONS(35),
    [sym_scheme] = ACTIONS(39),
    [sym_ipv4] = ACTIONS(19),
  },
  [3] = {
    [sym_block] = STATE(36),
    [sym_parenthese] = STATE(11),
    [sym_bracket] = STATE(11),
    [sym_param] = STATE(4),
    [sym_variable] = STATE(11),
    [sym_string] = STATE(11),
    [sym_regex] = STATE(11),
    [sym__regex_tokens] = STATE(18),
    [sym_modifier] = STATE(11),
    [sym_uri] = STATE(11),
    [aux_sym_simple_directive_repeat1] = STATE(4),
    [sym_comment] = ACTIONS(3),
    [anon_sym_SEMI] = ACTIONS(41),
    [anon_sym_LBRACE] = ACTIONS(13),
    [anon_sym_LPAREN] = ACTIONS(15),
    [anon_sym_LBRACK] = ACTIONS(17),
    [sym_generic] = ACTIONS(19),
    [sym_metric] = ACTIONS(19),
    [aux_sym_variable_token1] = ACTIONS(21),
    [aux_sym_variable_token2] = ACTIONS(21),
    [sym_number] = ACTIONS(19),
    [anon_sym_SQUOTE] = ACTIONS(23),
    [anon_sym_DQUOTE] = ACTIONS(25),
    [anon_sym_SLASH] = ACTIONS(27),
    [anon_sym_DOT] = ACTIONS(27),
    [sym__colon] = ACTIONS(29),
    [sym__or] = ACTIONS(29),
    [sym__option] = ACTIONS(29),
    [sym__carrot] = ACTIONS(29),
    [sym__star] = ACTIONS(31),
    [sym_escaped_dot] = ACTIONS(33),
    [sym__eol] = ACTIONS(31),
    [sym__plus] = ACTIONS(29),
    [sym__eq] = ACTIONS(35),
    [sym__tild] = ACTIONS(37),
    [sym__not] = ACTIONS(35),
    [sym__ts_modifier] = ACTIONS(35),
    [sym__st_modifier] = ACTIONS(35),
    [sym_scheme] = ACTIONS(39),
    [sym_ipv4] = ACTIONS(19),
  },
  [4] = {
    [sym_parenthese] = STATE(11),
    [sym_bracket] = STATE(11),
    [sym_param] = STATE(4),
    [sym_variable] = STATE(11),
    [sym_string] = STATE(11),
    [sym_regex] = STATE(11),
    [sym__regex_tokens] = STATE(18),
    [sym_modifier] = STATE(11),
    [sym_uri] = STATE(11),
    [aux_sym_simple_directive_repeat1] = STATE(4),
    [sym_comment] = ACTIONS(3),
    [anon_sym_SEMI] = ACTIONS(43),
    [anon_sym_LBRACE] = ACTIONS(43),
    [anon_sym_LPAREN] = ACTIONS(45),
    [anon_sym_LBRACK] = ACTIONS(48),
    [sym_generic] = ACTIONS(51),
    [sym_metric] = ACTIONS(51),
    [aux_sym_variable_token1] = ACTIONS(54),
    [aux_sym_variable_token2] = ACTIONS(54),
    [sym_number] = ACTIONS(51),
    [anon_sym_SQUOTE] = ACTIONS(57),
    [anon_sym_DQUOTE] = ACTIONS(60),
    [anon_sym_SLASH] = ACTIONS(63),
    [anon_sym_DOT] = ACTIONS(63),
    [sym__colon] = ACTIONS(66),
    [sym__or] = ACTIONS(66),
    [sym__option] = ACTIONS(66),
    [sym__carrot] = ACTIONS(66),
    [sym__star] = ACTIONS(69),
    [sym_escaped_dot] = ACTIONS(72),
    [sym__eol] = ACTIONS(69),
    [sym__plus] = ACTIONS(66),
    [sym__eq] = ACTIONS(75),
    [sym__tild] = ACTIONS(78),
    [sym__not] = ACTIONS(75),
    [sym__ts_modifier] = ACTIONS(75),
    [sym__st_modifier] = ACTIONS(75),
    [sym_scheme] = ACTIONS(81),
    [sym_ipv4] = ACTIONS(51),
  },
  [5] = {
    [sym_parenthese] = STATE(11),
    [sym_bracket] = STATE(11),
    [sym_param] = STATE(8),
    [sym_variable] = STATE(11),
    [sym_string] = STATE(11),
    [sym_regex] = STATE(11),
    [sym__regex_tokens] = STATE(18),
    [sym_modifier] = STATE(11),
    [sym_uri] = STATE(11),
    [aux_sym_simple_directive_repeat1] = STATE(8),
    [sym_comment] = ACTIONS(3),
    [anon_sym_LPAREN] = ACTIONS(15),
    [anon_sym_RPAREN] = ACTIONS(84),
    [anon_sym_LBRACK] = ACTIONS(17),
    [sym_generic] = ACTIONS(19),
    [sym_metric] = ACTIONS(19),
    [aux_sym_variable_token1] = ACTIONS(21),
    [aux_sym_variable_token2] = ACTIONS(21),
    [sym_number] = ACTIONS(19),
    [anon_sym_SQUOTE] = ACTIONS(23),
    [anon_sym_DQUOTE] = ACTIONS(25),
    [anon_sym_SLASH] = ACTIONS(86),
    [anon_sym_DOT] = ACTIONS(86),
    [sym__colon] = ACTIONS(29),
    [sym__or] = ACTIONS(29),
    [sym__option] = ACTIONS(29),
    [sym__carrot] = ACTIONS(29),
    [sym__star] = ACTIONS(31),
    [sym_escaped_dot] = ACTIONS(88),
    [sym__eol] = ACTIONS(31),
    [sym__plus] = ACTIONS(29),
    [sym__eq] = ACTIONS(35),
    [sym__tild] = ACTIONS(37),
    [sym__not] = ACTIONS(35),
    [sym__ts_modifier] = ACTIONS(35),
    [sym__st_modifier] = ACTIONS(35),
    [sym_scheme] = ACTIONS(39),
    [sym_ipv4] = ACTIONS(19),
  },
  [6] = {
    [sym_parenthese] = STATE(11),
    [sym_bracket] = STATE(11),
    [sym_param] = STATE(6),
    [sym_variable] = STATE(11),
    [sym_string] = STATE(11),
    [sym_regex] = STATE(11),
    [sym__regex_tokens] = STATE(18),
    [sym_modifier] = STATE(11),
    [sym_uri] = STATE(11),
    [aux_sym_simple_directive_repeat1] = STATE(6),
    [sym_comment] = ACTIONS(3),
    [anon_sym_LPAREN] = ACTIONS(45),
    [anon_sym_LBRACK] = ACTIONS(48),
    [anon_sym_RBRACK] = ACTIONS(43),
    [sym_generic] = ACTIONS(51),
    [sym_metric] = ACTIONS(51),
    [aux_sym_variable_token1] = ACTIONS(54),
    [aux_sym_variable_token2] = ACTIONS(54),
    [sym_number] = ACTIONS(51),
    [anon_sym_SQUOTE] = ACTIONS(57),
    [anon_sym_DQUOTE] = ACTIONS(60),
    [anon_sym_SLASH] = ACTIONS(90),
    [anon_sym_DOT] = ACTIONS(90),
    [sym__colon] = ACTIONS(66),
    [sym__or] = ACTIONS(66),
    [sym__option] = ACTIONS(66),
    [sym__carrot] = ACTIONS(66),
    [sym__star] = ACTIONS(69),
    [sym_escaped_dot] = ACTIONS(93),
    [sym__eol] = ACTIONS(69),
    [sym__plus] = ACTIONS(66),
    [sym__eq] = ACTIONS(75),
    [sym__tild] = ACTIONS(78),
    [sym__not] = ACTIONS(75),
    [sym__ts_modifier] = ACTIONS(75),
    [sym__st_modifier] = ACTIONS(75),
    [sym_scheme] = ACTIONS(81),
    [sym_ipv4] = ACTIONS(51),
  },
  [7] = {
    [sym_parenthese] = STATE(11),
    [sym_bracket] = STATE(11),
    [sym_param] = STATE(6),
    [sym_variable] = STATE(11),
    [sym_string] = STATE(11),
    [sym_regex] = STATE(11),
    [sym__regex_tokens] = STATE(18),
    [sym_modifier] = STATE(11),
    [sym_uri] = STATE(11),
    [aux_sym_simple_directive_repeat1] = STATE(6),
    [sym_comment] = ACTIONS(3),
    [anon_sym_LPAREN] = ACTIONS(15),
    [anon_sym_LBRACK] = ACTIONS(17),
    [anon_sym_RBRACK] = ACTIONS(96),
    [sym_generic] = ACTIONS(19),
    [sym_metric] = ACTIONS(19),
    [aux_sym_variable_token1] = ACTIONS(21),
    [aux_sym_variable_token2] = ACTIONS(21),
    [sym_number] = ACTIONS(19),
    [anon_sym_SQUOTE] = ACTIONS(23),
    [anon_sym_DQUOTE] = ACTIONS(25),
    [anon_sym_SLASH] = ACTIONS(98),
    [anon_sym_DOT] = ACTIONS(98),
    [sym__colon] = ACTIONS(29),
    [sym__or] = ACTIONS(29),
    [sym__option] = ACTIONS(29),
    [sym__carrot] = ACTIONS(29),
    [sym__star] = ACTIONS(31),
    [sym_escaped_dot] = ACTIONS(100),
    [sym__eol] = ACTIONS(31),
    [sym__plus] = ACTIONS(29),
    [sym__eq] = ACTIONS(35),
    [sym__tild] = ACTIONS(37),
    [sym__not] = ACTIONS(35),
    [sym__ts_modifier] = ACTIONS(35),
    [sym__st_modifier] = ACTIONS(35),
    [sym_scheme] = ACTIONS(39),
    [sym_ipv4] = ACTIONS(19),
  },
  [8] = {
    [sym_parenthese] = STATE(11),
    [sym_bracket] = STATE(11),
    [sym_param] = STATE(8),
    [sym_variable] = STATE(11),
    [sym_string] = STATE(11),
    [sym_regex] = STATE(11),
    [sym__regex_tokens] = STATE(18),
    [sym_modifier] = STATE(11),
    [sym_uri] = STATE(11),
    [aux_sym_simple_directive_repeat1] = STATE(8),
    [sym_comment] = ACTIONS(3),
    [anon_sym_LPAREN] = ACTIONS(45),
    [anon_sym_RPAREN] = ACTIONS(43),
    [anon_sym_LBRACK] = ACTIONS(48),
    [sym_generic] = ACTIONS(51),
    [sym_metric] = ACTIONS(51),
    [aux_sym_variable_token1] = ACTIONS(54),
    [aux_sym_variable_token2] = ACTIONS(54),
    [sym_number] = ACTIONS(51),
    [anon_sym_SQUOTE] = ACTIONS(57),
    [anon_sym_DQUOTE] = ACTIONS(60),
    [anon_sym_SLASH] = ACTIONS(102),
    [anon_sym_DOT] = ACTIONS(102),
    [sym__colon] = ACTIONS(66),
    [sym__or] = ACTIONS(66),
    [sym__option] = ACTIONS(66),
    [sym__carrot] = ACTIONS(66),
    [sym__star] = ACTIONS(69),
    [sym_escaped_dot] = ACTIONS(105),
    [sym__eol] = ACTIONS(69),
    [sym__plus] = ACTIONS(66),
    [sym__eq] = ACTIONS(75),
    [sym__tild] = ACTIONS(78),
    [sym__not] = ACTIONS(75),
    [sym__ts_modifier] = ACTIONS(75),
    [sym__st_modifier] = ACTIONS(75),
    [sym_scheme] = ACTIONS(81),
    [sym_ipv4] = ACTIONS(51),
  },
  [9] = {
    [sym_parenthese] = STATE(11),
    [sym_bracket] = STATE(11),
    [sym_param] = STATE(5),
    [sym_variable] = STATE(11),
    [sym_string] = STATE(11),
    [sym_regex] = STATE(11),
    [sym__regex_tokens] = STATE(18),
    [sym_modifier] = STATE(11),
    [sym_uri] = STATE(11),
    [aux_sym_simple_directive_repeat1] = STATE(5),
    [sym_comment] = ACTIONS(3),
    [anon_sym_LPAREN] = ACTIONS(15),
    [anon_sym_RPAREN] = ACTIONS(108),
    [anon_sym_LBRACK] = ACTIONS(17),
    [sym_generic] = ACTIONS(19),
    [sym_metric] = ACTIONS(19),
    [aux_sym_variable_token1] = ACTIONS(21),
    [aux_sym_variable_token2] = ACTIONS(21),
    [sym_number] = ACTIONS(19),
    [anon_sym_SQUOTE] = ACTIONS(23),
    [anon_sym_DQUOTE] = ACTIONS(25),
    [anon_sym_SLASH] = ACTIONS(86),
    [anon_sym_DOT] = ACTIONS(86),
    [sym__colon] = ACTIONS(29),
    [sym__or] = ACTIONS(29),
    [sym__option] = ACTIONS(29),
    [sym__carrot] = ACTIONS(29),
    [sym__star] = ACTIONS(31),
    [sym_escaped_dot] = ACTIONS(88),
    [sym__eol] = ACTIONS(31),
    [sym__plus] = ACTIONS(29),
    [sym__eq] = ACTIONS(35),
    [sym__tild] = ACTIONS(37),
    [sym__not] = ACTIONS(35),
    [sym__ts_modifier] = ACTIONS(35),
    [sym__st_modifier] = ACTIONS(35),
    [sym_scheme] = ACTIONS(39),
    [sym_ipv4] = ACTIONS(19),
  },
  [10] = {
    [sym_parenthese] = STATE(11),
    [sym_bracket] = STATE(11),
    [sym_param] = STATE(7),
    [sym_variable] = STATE(11),
    [sym_string] = STATE(11),
    [sym_regex] = STATE(11),
    [sym__regex_tokens] = STATE(18),
    [sym_modifier] = STATE(11),
    [sym_uri] = STATE(11),
    [aux_sym_simple_directive_repeat1] = STATE(7),
    [sym_comment] = ACTIONS(3),
    [anon_sym_LPAREN] = ACTIONS(15),
    [anon_sym_LBRACK] = ACTIONS(17),
    [anon_sym_RBRACK] = ACTIONS(110),
    [sym_generic] = ACTIONS(19),
    [sym_metric] = ACTIONS(19),
    [aux_sym_variable_token1] = ACTIONS(21),
    [aux_sym_variable_token2] = ACTIONS(21),
    [sym_number] = ACTIONS(19),
    [anon_sym_SQUOTE] = ACTIONS(23),
    [anon_sym_DQUOTE] = ACTIONS(25),
    [anon_sym_SLASH] = ACTIONS(98),
    [anon_sym_DOT] = ACTIONS(98),
    [sym__colon] = ACTIONS(29),
    [sym__or] = ACTIONS(29),
    [sym__option] = ACTIONS(29),
    [sym__carrot] = ACTIONS(29),
    [sym__star] = ACTIONS(31),
    [sym_escaped_dot] = ACTIONS(100),
    [sym__eol] = ACTIONS(31),
    [sym__plus] = ACTIONS(29),
    [sym__eq] = ACTIONS(35),
    [sym__tild] = ACTIONS(37),
    [sym__not] = ACTIONS(35),
    [sym__ts_modifier] = ACTIONS(35),
    [sym__st_modifier] = ACTIONS(35),
    [sym_scheme] = ACTIONS(39),
    [sym_ipv4] = ACTIONS(19),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(114), 9,
      sym_generic,
      sym_metric,
      sym_number,
      anon_sym_SLASH,
      anon_sym_DOT,
      sym__star,
      sym__eol,
      sym__tild,
      sym_ipv4,
    ACTIONS(112), 21,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      sym__colon,
      sym__or,
      sym__option,
      sym__carrot,
      sym_escaped_dot,
      sym__plus,
      sym__eq,
      sym__not,
      sym__ts_modifier,
      sym__st_modifier,
      sym_scheme,
  [38] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(118), 9,
      sym_generic,
      sym_metric,
      sym_number,
      anon_sym_SLASH,
      anon_sym_DOT,
      sym__star,
      sym__eol,
      sym__tild,
      sym_ipv4,
    ACTIONS(116), 21,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      sym__colon,
      sym__or,
      sym__option,
      sym__carrot,
      sym_escaped_dot,
      sym__plus,
      sym__eq,
      sym__not,
      sym__ts_modifier,
      sym__st_modifier,
      sym_scheme,
  [76] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(122), 9,
      sym_generic,
      sym_metric,
      sym_number,
      anon_sym_SLASH,
      anon_sym_DOT,
      sym__star,
      sym__eol,
      sym__tild,
      sym_ipv4,
    ACTIONS(120), 21,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      sym__colon,
      sym__or,
      sym__option,
      sym__carrot,
      sym_escaped_dot,
      sym__plus,
      sym__eq,
      sym__not,
      sym__ts_modifier,
      sym__st_modifier,
      sym_scheme,
  [114] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(126), 9,
      sym_generic,
      sym_metric,
      sym_number,
      anon_sym_SLASH,
      anon_sym_DOT,
      sym__star,
      sym__eol,
      sym__tild,
      sym_ipv4,
    ACTIONS(124), 21,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      sym__colon,
      sym__or,
      sym__option,
      sym__carrot,
      sym_escaped_dot,
      sym__plus,
      sym__eq,
      sym__not,
      sym__ts_modifier,
      sym__st_modifier,
      sym_scheme,
  [152] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(130), 9,
      sym_generic,
      sym_metric,
      sym_number,
      anon_sym_SLASH,
      anon_sym_DOT,
      sym__star,
      sym__eol,
      sym__tild,
      sym_ipv4,
    ACTIONS(128), 21,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      sym__colon,
      sym__or,
      sym__option,
      sym__carrot,
      sym_escaped_dot,
      sym__plus,
      sym__eq,
      sym__not,
      sym__ts_modifier,
      sym__st_modifier,
      sym_scheme,
  [190] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(134), 9,
      sym_generic,
      sym_metric,
      sym_number,
      anon_sym_SLASH,
      anon_sym_DOT,
      sym__star,
      sym__eol,
      sym__tild,
      sym_ipv4,
    ACTIONS(132), 21,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      sym__colon,
      sym__or,
      sym__option,
      sym__carrot,
      sym_escaped_dot,
      sym__plus,
      sym__eq,
      sym__not,
      sym__ts_modifier,
      sym__st_modifier,
      sym_scheme,
  [228] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(138), 9,
      sym_generic,
      sym_metric,
      sym_number,
      anon_sym_SLASH,
      anon_sym_DOT,
      sym__star,
      sym__eol,
      sym__tild,
      sym_ipv4,
    ACTIONS(136), 21,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      sym__colon,
      sym__or,
      sym__option,
      sym__carrot,
      sym_escaped_dot,
      sym__plus,
      sym__eq,
      sym__not,
      sym__ts_modifier,
      sym__st_modifier,
      sym_scheme,
  [266] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(142), 9,
      sym_generic,
      sym_metric,
      sym_number,
      anon_sym_SLASH,
      anon_sym_DOT,
      sym__star,
      sym__eol,
      sym__tild,
      sym_ipv4,
    ACTIONS(140), 21,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      sym__colon,
      sym__or,
      sym__option,
      sym__carrot,
      sym_escaped_dot,
      sym__plus,
      sym__eq,
      sym__not,
      sym__ts_modifier,
      sym__st_modifier,
      sym_scheme,
  [304] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(146), 9,
      sym_generic,
      sym_metric,
      sym_number,
      anon_sym_SLASH,
      anon_sym_DOT,
      sym__star,
      sym__eol,
      sym__tild,
      sym_ipv4,
    ACTIONS(144), 21,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      sym__colon,
      sym__or,
      sym__option,
      sym__carrot,
      sym_escaped_dot,
      sym__plus,
      sym__eq,
      sym__not,
      sym__ts_modifier,
      sym__st_modifier,
      sym_scheme,
  [342] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(150), 9,
      sym_generic,
      sym_metric,
      sym_number,
      anon_sym_SLASH,
      anon_sym_DOT,
      sym__star,
      sym__eol,
      sym__tild,
      sym_ipv4,
    ACTIONS(148), 21,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      sym__colon,
      sym__or,
      sym__option,
      sym__carrot,
      sym_escaped_dot,
      sym__plus,
      sym__eq,
      sym__not,
      sym__ts_modifier,
      sym__st_modifier,
      sym_scheme,
  [380] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(154), 9,
      sym_generic,
      sym_metric,
      sym_number,
      anon_sym_SLASH,
      anon_sym_DOT,
      sym__star,
      sym__eol,
      sym__tild,
      sym_ipv4,
    ACTIONS(152), 21,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      sym__colon,
      sym__or,
      sym__option,
      sym__carrot,
      sym_escaped_dot,
      sym__plus,
      sym__eq,
      sym__not,
      sym__ts_modifier,
      sym__st_modifier,
      sym_scheme,
  [418] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(158), 9,
      sym_generic,
      sym_metric,
      sym_number,
      anon_sym_SLASH,
      anon_sym_DOT,
      sym__star,
      sym__eol,
      sym__tild,
      sym_ipv4,
    ACTIONS(156), 21,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      sym__colon,
      sym__or,
      sym__option,
      sym__carrot,
      sym_escaped_dot,
      sym__plus,
      sym__eq,
      sym__not,
      sym__ts_modifier,
      sym__st_modifier,
      sym_scheme,
  [456] = 4,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(162), 1,
      sym_regex_pattern,
    ACTIONS(140), 3,
      sym__colon,
      sym__or,
      sym__option,
    ACTIONS(142), 25,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_LBRACK,
      sym_generic,
      sym_metric,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
      sym_number,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      anon_sym_SLASH,
      anon_sym_DOT,
      sym__carrot,
      sym__star,
      sym_escaped_dot,
      sym__eol,
      sym__plus,
      sym__eq,
      sym__tild,
      sym__not,
      sym__ts_modifier,
      sym__st_modifier,
      sym_scheme,
      sym_ipv4,
  [495] = 4,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(162), 1,
      sym_regex_pattern,
    ACTIONS(140), 3,
      sym__colon,
      sym__or,
      sym__option,
    ACTIONS(142), 24,
      anon_sym_LPAREN,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      sym_generic,
      sym_metric,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
      sym_number,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      anon_sym_SLASH,
      anon_sym_DOT,
      sym__carrot,
      sym__star,
      sym_escaped_dot,
      sym__eol,
      sym__plus,
      sym__eq,
      sym__tild,
      sym__not,
      sym__ts_modifier,
      sym__st_modifier,
      sym_scheme,
      sym_ipv4,
  [533] = 4,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(162), 1,
      sym_regex_pattern,
    ACTIONS(140), 3,
      sym__colon,
      sym__or,
      sym__option,
    ACTIONS(142), 24,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      sym_generic,
      sym_metric,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
      sym_number,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      anon_sym_SLASH,
      anon_sym_DOT,
      sym__carrot,
      sym__star,
      sym_escaped_dot,
      sym__eol,
      sym__plus,
      sym__eq,
      sym__tild,
      sym__not,
      sym__ts_modifier,
      sym__st_modifier,
      sym_scheme,
      sym_ipv4,
  [571] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(166), 1,
      sym_directive,
    STATE(61), 1,
      sym__lua_block_directives,
    ACTIONS(164), 2,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
    STATE(26), 5,
      sym__directives,
      sym_simple_directive,
      sym_block_directive,
      sym_lua_block_directive,
      aux_sym_conf_repeat1,
    ACTIONS(169), 7,
      anon_sym_access_by_lua_block,
      anon_sym_header_filter_by_lua_block,
      anon_sym_body_filter_by_lua_block,
      anon_sym_log_by_lua_block,
      anon_sym_balancer_by_lua_block,
      anon_sym_content_by_lua_block,
      anon_sym_rewrite_by_lua_block,
  [601] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      sym_directive,
    ACTIONS(172), 1,
      anon_sym_RBRACE,
    STATE(61), 1,
      sym__lua_block_directives,
    STATE(26), 5,
      sym__directives,
      sym_simple_directive,
      sym_block_directive,
      sym_lua_block_directive,
      aux_sym_conf_repeat1,
    ACTIONS(9), 7,
      anon_sym_access_by_lua_block,
      anon_sym_header_filter_by_lua_block,
      anon_sym_body_filter_by_lua_block,
      anon_sym_log_by_lua_block,
      anon_sym_balancer_by_lua_block,
      anon_sym_content_by_lua_block,
      anon_sym_rewrite_by_lua_block,
  [630] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      sym_directive,
    ACTIONS(174), 1,
      anon_sym_RBRACE,
    STATE(61), 1,
      sym__lua_block_directives,
    STATE(27), 5,
      sym__directives,
      sym_simple_directive,
      sym_block_directive,
      sym_lua_block_directive,
      aux_sym_conf_repeat1,
    ACTIONS(9), 7,
      anon_sym_access_by_lua_block,
      anon_sym_header_filter_by_lua_block,
      anon_sym_body_filter_by_lua_block,
      anon_sym_log_by_lua_block,
      anon_sym_balancer_by_lua_block,
      anon_sym_content_by_lua_block,
      anon_sym_rewrite_by_lua_block,
  [659] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      sym_directive,
    ACTIONS(176), 1,
      ts_builtin_sym_end,
    STATE(61), 1,
      sym__lua_block_directives,
    STATE(26), 5,
      sym__directives,
      sym_simple_directive,
      sym_block_directive,
      sym_lua_block_directive,
      aux_sym_conf_repeat1,
    ACTIONS(9), 7,
      anon_sym_access_by_lua_block,
      anon_sym_header_filter_by_lua_block,
      anon_sym_body_filter_by_lua_block,
      anon_sym_log_by_lua_block,
      anon_sym_balancer_by_lua_block,
      anon_sym_content_by_lua_block,
      anon_sym_rewrite_by_lua_block,
  [688] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(178), 2,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
    ACTIONS(180), 8,
      sym_directive,
      anon_sym_access_by_lua_block,
      anon_sym_header_filter_by_lua_block,
      anon_sym_body_filter_by_lua_block,
      anon_sym_log_by_lua_block,
      anon_sym_balancer_by_lua_block,
      anon_sym_content_by_lua_block,
      anon_sym_rewrite_by_lua_block,
  [706] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(182), 2,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
    ACTIONS(184), 8,
      sym_directive,
      anon_sym_access_by_lua_block,
      anon_sym_header_filter_by_lua_block,
      anon_sym_body_filter_by_lua_block,
      anon_sym_log_by_lua_block,
      anon_sym_balancer_by_lua_block,
      anon_sym_content_by_lua_block,
      anon_sym_rewrite_by_lua_block,
  [724] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(186), 2,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
    ACTIONS(188), 8,
      sym_directive,
      anon_sym_access_by_lua_block,
      anon_sym_header_filter_by_lua_block,
      anon_sym_body_filter_by_lua_block,
      anon_sym_log_by_lua_block,
      anon_sym_balancer_by_lua_block,
      anon_sym_content_by_lua_block,
      anon_sym_rewrite_by_lua_block,
  [742] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(190), 2,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
    ACTIONS(192), 8,
      sym_directive,
      anon_sym_access_by_lua_block,
      anon_sym_header_filter_by_lua_block,
      anon_sym_body_filter_by_lua_block,
      anon_sym_log_by_lua_block,
      anon_sym_balancer_by_lua_block,
      anon_sym_content_by_lua_block,
      anon_sym_rewrite_by_lua_block,
  [760] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(194), 2,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
    ACTIONS(196), 8,
      sym_directive,
      anon_sym_access_by_lua_block,
      anon_sym_header_filter_by_lua_block,
      anon_sym_body_filter_by_lua_block,
      anon_sym_log_by_lua_block,
      anon_sym_balancer_by_lua_block,
      anon_sym_content_by_lua_block,
      anon_sym_rewrite_by_lua_block,
  [778] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(198), 2,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
    ACTIONS(200), 8,
      sym_directive,
      anon_sym_access_by_lua_block,
      anon_sym_header_filter_by_lua_block,
      anon_sym_body_filter_by_lua_block,
      anon_sym_log_by_lua_block,
      anon_sym_balancer_by_lua_block,
      anon_sym_content_by_lua_block,
      anon_sym_rewrite_by_lua_block,
  [796] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(202), 2,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
    ACTIONS(204), 8,
      sym_directive,
      anon_sym_access_by_lua_block,
      anon_sym_header_filter_by_lua_block,
      anon_sym_body_filter_by_lua_block,
      anon_sym_log_by_lua_block,
      anon_sym_balancer_by_lua_block,
      anon_sym_content_by_lua_block,
      anon_sym_rewrite_by_lua_block,
  [814] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(206), 2,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
    ACTIONS(208), 8,
      sym_directive,
      anon_sym_access_by_lua_block,
      anon_sym_header_filter_by_lua_block,
      anon_sym_body_filter_by_lua_block,
      anon_sym_log_by_lua_block,
      anon_sym_balancer_by_lua_block,
      anon_sym_content_by_lua_block,
      anon_sym_rewrite_by_lua_block,
  [832] = 5,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(212), 1,
      sym_sq_string_content,
    ACTIONS(214), 1,
      anon_sym_SQUOTE,
    ACTIONS(210), 2,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
    STATE(42), 2,
      sym_variable,
      aux_sym_string_repeat1,
  [850] = 5,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(214), 1,
      anon_sym_DQUOTE,
    ACTIONS(218), 1,
      sym_dq_string_content,
    ACTIONS(216), 2,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
    STATE(43), 2,
      sym_variable,
      aux_sym_string_repeat2,
  [868] = 5,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(220), 1,
      sym_sq_string_content,
    ACTIONS(222), 1,
      anon_sym_SQUOTE,
    ACTIONS(210), 2,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
    STATE(38), 2,
      sym_variable,
      aux_sym_string_repeat1,
  [886] = 5,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(222), 1,
      anon_sym_DQUOTE,
    ACTIONS(224), 1,
      sym_dq_string_content,
    ACTIONS(216), 2,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
    STATE(39), 2,
      sym_variable,
      aux_sym_string_repeat2,
  [904] = 5,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(229), 1,
      sym_sq_string_content,
    ACTIONS(232), 1,
      anon_sym_SQUOTE,
    ACTIONS(226), 2,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
    STATE(42), 2,
      sym_variable,
      aux_sym_string_repeat1,
  [922] = 5,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(237), 1,
      sym_dq_string_content,
    ACTIONS(240), 1,
      anon_sym_DQUOTE,
    ACTIONS(234), 2,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
    STATE(43), 2,
      sym_variable,
      aux_sym_string_repeat2,
  [940] = 5,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(242), 1,
      anon_sym_RBRACE,
    ACTIONS(244), 1,
      aux_sym__lua_code_token1,
    STATE(62), 1,
      sym__lua_code,
    STATE(44), 2,
      sym_lua_code,
      aux_sym_lua_block_repeat1,
  [957] = 6,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(247), 1,
      anon_sym_LBRACE,
    ACTIONS(249), 1,
      anon_sym_RBRACE,
    ACTIONS(251), 1,
      anon_sym_SQUOTE,
    ACTIONS(253), 1,
      anon_sym_DQUOTE,
    ACTIONS(255), 1,
      aux_sym__lua_code_token1,
  [976] = 5,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(257), 1,
      anon_sym_RBRACE,
    ACTIONS(259), 1,
      aux_sym__lua_code_token1,
    STATE(62), 1,
      sym__lua_code,
    STATE(44), 2,
      sym_lua_code,
      aux_sym_lua_block_repeat1,
  [993] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(261), 1,
      sym_generic,
    ACTIONS(263), 1,
      sym_ipv4,
    STATE(20), 1,
      sym_variable,
    ACTIONS(21), 2,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
  [1010] = 4,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(265), 1,
      anon_sym_RBRACE,
    ACTIONS(267), 1,
      aux_sym__lua_code_token1,
    STATE(48), 2,
      sym__lua_code,
      aux_sym__lua_code_repeat1,
  [1024] = 2,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(126), 4,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
      sym_dq_string_content,
      anon_sym_DQUOTE,
  [1034] = 5,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(270), 1,
      anon_sym_RBRACE,
    ACTIONS(272), 1,
      anon_sym_SQUOTE,
    ACTIONS(274), 1,
      anon_sym_DQUOTE,
    ACTIONS(276), 1,
      aux_sym__lua_code_token1,
  [1050] = 4,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(259), 1,
      aux_sym__lua_code_token1,
    ACTIONS(278), 1,
      anon_sym_RBRACE,
    STATE(48), 2,
      sym__lua_code,
      aux_sym__lua_code_repeat1,
  [1064] = 4,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(259), 1,
      aux_sym__lua_code_token1,
    ACTIONS(280), 1,
      anon_sym_RBRACE,
    STATE(51), 2,
      sym__lua_code,
      aux_sym__lua_code_repeat1,
  [1078] = 2,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(126), 4,
      aux_sym_variable_token1,
      aux_sym_variable_token2,
      sym_sq_string_content,
      anon_sym_SQUOTE,
  [1088] = 5,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(282), 1,
      anon_sym_RBRACE,
    ACTIONS(284), 1,
      anon_sym_SQUOTE,
    ACTIONS(286), 1,
      anon_sym_DQUOTE,
    ACTIONS(288), 1,
      aux_sym__lua_code_token1,
  [1104] = 4,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(259), 1,
      aux_sym__lua_code_token1,
    STATE(62), 1,
      sym__lua_code,
    STATE(46), 2,
      sym_lua_code,
      aux_sym_lua_block_repeat1,
  [1118] = 4,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(282), 1,
      anon_sym_RBRACE,
    ACTIONS(284), 1,
      anon_sym_SQUOTE,
    ACTIONS(288), 1,
      aux_sym__lua_code_token1,
  [1131] = 4,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(290), 1,
      anon_sym_RBRACE,
    ACTIONS(292), 1,
      anon_sym_SQUOTE,
    ACTIONS(294), 1,
      aux_sym__lua_code_token1,
  [1144] = 4,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(296), 1,
      anon_sym_RBRACE,
    ACTIONS(298), 1,
      anon_sym_SQUOTE,
    ACTIONS(300), 1,
      aux_sym__lua_code_token1,
  [1157] = 3,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(296), 1,
      anon_sym_RBRACE,
    ACTIONS(300), 1,
      aux_sym__lua_code_token1,
  [1167] = 3,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(290), 1,
      anon_sym_RBRACE,
    ACTIONS(294), 1,
      aux_sym__lua_code_token1,
  [1177] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(302), 1,
      anon_sym_LBRACE,
    STATE(33), 1,
      sym_lua_block,
  [1187] = 3,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(304), 1,
      anon_sym_RBRACE,
    ACTIONS(306), 1,
      aux_sym__lua_code_token1,
  [1197] = 3,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(308), 1,
      anon_sym_RBRACE,
    ACTIONS(310), 1,
      aux_sym__lua_code_token1,
  [1207] = 3,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(312), 1,
      anon_sym_RBRACE,
    ACTIONS(314), 1,
      aux_sym__lua_code_token1,
  [1217] = 3,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(282), 1,
      anon_sym_RBRACE,
    ACTIONS(288), 1,
      aux_sym__lua_code_token1,
  [1227] = 2,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(316), 1,
      aux_sym__lua_code_token3,
  [1234] = 2,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(318), 1,
      aux_sym__lua_code_token2,
  [1241] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(320), 1,
      anon_sym_SQUOTE,
  [1248] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(322), 1,
      anon_sym_DQUOTE,
  [1255] = 2,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(324), 1,
      aux_sym__lua_code_token3,
  [1262] = 2,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(326), 1,
      aux_sym__lua_code_token2,
  [1269] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(328), 1,
      anon_sym_SQUOTE,
  [1276] = 2,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(330), 1,
      aux_sym__lua_code_token3,
  [1283] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(332), 1,
      anon_sym_SQUOTE,
  [1290] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(334), 1,
      anon_sym_SQUOTE,
  [1297] = 2,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(336), 1,
      aux_sym__lua_code_token2,
  [1304] = 2,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(338), 1,
      aux_sym__lua_code_token3,
  [1311] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(340), 1,
      anon_sym_DQUOTE,
  [1318] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(342), 1,
      ts_builtin_sym_end,
  [1325] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(344), 1,
      anon_sym_SQUOTE,
  [1332] = 2,
    ACTIONS(160), 1,
      sym_comment,
    ACTIONS(346), 1,
      aux_sym__lua_code_token3,
  [1339] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(348), 1,
      anon_sym_DQUOTE,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(11)] = 0,
  [SMALL_STATE(12)] = 38,
  [SMALL_STATE(13)] = 76,
  [SMALL_STATE(14)] = 114,
  [SMALL_STATE(15)] = 152,
  [SMALL_STATE(16)] = 190,
  [SMALL_STATE(17)] = 228,
  [SMALL_STATE(18)] = 266,
  [SMALL_STATE(19)] = 304,
  [SMALL_STATE(20)] = 342,
  [SMALL_STATE(21)] = 380,
  [SMALL_STATE(22)] = 418,
  [SMALL_STATE(23)] = 456,
  [SMALL_STATE(24)] = 495,
  [SMALL_STATE(25)] = 533,
  [SMALL_STATE(26)] = 571,
  [SMALL_STATE(27)] = 601,
  [SMALL_STATE(28)] = 630,
  [SMALL_STATE(29)] = 659,
  [SMALL_STATE(30)] = 688,
  [SMALL_STATE(31)] = 706,
  [SMALL_STATE(32)] = 724,
  [SMALL_STATE(33)] = 742,
  [SMALL_STATE(34)] = 760,
  [SMALL_STATE(35)] = 778,
  [SMALL_STATE(36)] = 796,
  [SMALL_STATE(37)] = 814,
  [SMALL_STATE(38)] = 832,
  [SMALL_STATE(39)] = 850,
  [SMALL_STATE(40)] = 868,
  [SMALL_STATE(41)] = 886,
  [SMALL_STATE(42)] = 904,
  [SMALL_STATE(43)] = 922,
  [SMALL_STATE(44)] = 940,
  [SMALL_STATE(45)] = 957,
  [SMALL_STATE(46)] = 976,
  [SMALL_STATE(47)] = 993,
  [SMALL_STATE(48)] = 1010,
  [SMALL_STATE(49)] = 1024,
  [SMALL_STATE(50)] = 1034,
  [SMALL_STATE(51)] = 1050,
  [SMALL_STATE(52)] = 1064,
  [SMALL_STATE(53)] = 1078,
  [SMALL_STATE(54)] = 1088,
  [SMALL_STATE(55)] = 1104,
  [SMALL_STATE(56)] = 1118,
  [SMALL_STATE(57)] = 1131,
  [SMALL_STATE(58)] = 1144,
  [SMALL_STATE(59)] = 1157,
  [SMALL_STATE(60)] = 1167,
  [SMALL_STATE(61)] = 1177,
  [SMALL_STATE(62)] = 1187,
  [SMALL_STATE(63)] = 1197,
  [SMALL_STATE(64)] = 1207,
  [SMALL_STATE(65)] = 1217,
  [SMALL_STATE(66)] = 1227,
  [SMALL_STATE(67)] = 1234,
  [SMALL_STATE(68)] = 1241,
  [SMALL_STATE(69)] = 1248,
  [SMALL_STATE(70)] = 1255,
  [SMALL_STATE(71)] = 1262,
  [SMALL_STATE(72)] = 1269,
  [SMALL_STATE(73)] = 1276,
  [SMALL_STATE(74)] = 1283,
  [SMALL_STATE(75)] = 1290,
  [SMALL_STATE(76)] = 1297,
  [SMALL_STATE(77)] = 1304,
  [SMALL_STATE(78)] = 1311,
  [SMALL_STATE(79)] = 1318,
  [SMALL_STATE(80)] = 1325,
  [SMALL_STATE(81)] = 1332,
  [SMALL_STATE(82)] = 1339,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_conf, 0),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(2),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(61),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(11),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [27] = {.entry = {.count = 1, .reusable = false}}, SHIFT(23),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [31] = {.entry = {.count = 1, .reusable = false}}, SHIFT(18),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [35] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [37] = {.entry = {.count = 1, .reusable = false}}, SHIFT(15),
  [39] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [41] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [43] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_simple_directive_repeat1, 2),
  [45] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_simple_directive_repeat1, 2), SHIFT_REPEAT(9),
  [48] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_simple_directive_repeat1, 2), SHIFT_REPEAT(10),
  [51] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_simple_directive_repeat1, 2), SHIFT_REPEAT(11),
  [54] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_simple_directive_repeat1, 2), SHIFT_REPEAT(14),
  [57] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_simple_directive_repeat1, 2), SHIFT_REPEAT(40),
  [60] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_simple_directive_repeat1, 2), SHIFT_REPEAT(41),
  [63] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_simple_directive_repeat1, 2), SHIFT_REPEAT(23),
  [66] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_simple_directive_repeat1, 2), SHIFT_REPEAT(18),
  [69] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_simple_directive_repeat1, 2), SHIFT_REPEAT(18),
  [72] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_simple_directive_repeat1, 2), SHIFT_REPEAT(23),
  [75] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_simple_directive_repeat1, 2), SHIFT_REPEAT(15),
  [78] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_simple_directive_repeat1, 2), SHIFT_REPEAT(15),
  [81] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_simple_directive_repeat1, 2), SHIFT_REPEAT(47),
  [84] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [86] = {.entry = {.count = 1, .reusable = false}}, SHIFT(25),
  [88] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [90] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_simple_directive_repeat1, 2), SHIFT_REPEAT(24),
  [93] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_simple_directive_repeat1, 2), SHIFT_REPEAT(24),
  [96] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [98] = {.entry = {.count = 1, .reusable = false}}, SHIFT(24),
  [100] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [102] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_simple_directive_repeat1, 2), SHIFT_REPEAT(25),
  [105] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_simple_directive_repeat1, 2), SHIFT_REPEAT(25),
  [108] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [110] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [112] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_param, 1),
  [114] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_param, 1),
  [116] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 2),
  [118] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string, 2),
  [120] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 3),
  [122] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string, 3),
  [124] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_variable, 1),
  [126] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_variable, 1),
  [128] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_modifier, 1),
  [130] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_modifier, 1),
  [132] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parenthese, 2),
  [134] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_parenthese, 2),
  [136] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_regex, 2, .production_id = 2),
  [138] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_regex, 2, .production_id = 2),
  [140] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_regex, 1),
  [142] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_regex, 1),
  [144] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bracket, 2),
  [146] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_bracket, 2),
  [148] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_uri, 2, .production_id = 3),
  [150] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_uri, 2, .production_id = 3),
  [152] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parenthese, 3),
  [154] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_parenthese, 3),
  [156] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bracket, 3),
  [158] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_bracket, 3),
  [160] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [162] = {.entry = {.count = 1, .reusable = false}}, SHIFT(17),
  [164] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_conf_repeat1, 2),
  [166] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_conf_repeat1, 2), SHIFT_REPEAT(2),
  [169] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_conf_repeat1, 2), SHIFT_REPEAT(61),
  [172] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [174] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [176] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_conf, 1),
  [178] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block, 3),
  [180] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block, 3),
  [182] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_directive, 2, .production_id = 1),
  [184] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block_directive, 2, .production_id = 1),
  [186] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_simple_directive, 2, .production_id = 1),
  [188] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_simple_directive, 2, .production_id = 1),
  [190] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_lua_block_directive, 2),
  [192] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_lua_block_directive, 2),
  [194] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block, 2),
  [196] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block, 2),
  [198] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_simple_directive, 3, .production_id = 1),
  [200] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_simple_directive, 3, .production_id = 1),
  [202] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_directive, 3, .production_id = 1),
  [204] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block_directive, 3, .production_id = 1),
  [206] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_lua_block, 3),
  [208] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_lua_block, 3),
  [210] = {.entry = {.count = 1, .reusable = false}}, SHIFT(53),
  [212] = {.entry = {.count = 1, .reusable = false}}, SHIFT(42),
  [214] = {.entry = {.count = 1, .reusable = false}}, SHIFT(13),
  [216] = {.entry = {.count = 1, .reusable = false}}, SHIFT(49),
  [218] = {.entry = {.count = 1, .reusable = false}}, SHIFT(43),
  [220] = {.entry = {.count = 1, .reusable = false}}, SHIFT(38),
  [222] = {.entry = {.count = 1, .reusable = false}}, SHIFT(12),
  [224] = {.entry = {.count = 1, .reusable = false}}, SHIFT(39),
  [226] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_repeat1, 2), SHIFT_REPEAT(53),
  [229] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_repeat1, 2), SHIFT_REPEAT(42),
  [232] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_repeat1, 2),
  [234] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_repeat2, 2), SHIFT_REPEAT(49),
  [237] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_repeat2, 2), SHIFT_REPEAT(43),
  [240] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_repeat2, 2),
  [242] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_lua_block_repeat1, 2),
  [244] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_lua_block_repeat1, 2), SHIFT_REPEAT(45),
  [247] = {.entry = {.count = 1, .reusable = false}}, SHIFT(52),
  [249] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__lua_code, 1),
  [251] = {.entry = {.count = 1, .reusable = false}}, SHIFT(66),
  [253] = {.entry = {.count = 1, .reusable = false}}, SHIFT(67),
  [255] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__lua_code, 1),
  [257] = {.entry = {.count = 1, .reusable = false}}, SHIFT(37),
  [259] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [261] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [263] = {.entry = {.count = 1, .reusable = false}}, SHIFT(20),
  [265] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym__lua_code_repeat1, 2),
  [267] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__lua_code_repeat1, 2), SHIFT_REPEAT(45),
  [270] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__lua_code, 3),
  [272] = {.entry = {.count = 1, .reusable = false}}, SHIFT(77),
  [274] = {.entry = {.count = 1, .reusable = false}}, SHIFT(71),
  [276] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__lua_code, 3),
  [278] = {.entry = {.count = 1, .reusable = false}}, SHIFT(54),
  [280] = {.entry = {.count = 1, .reusable = false}}, SHIFT(50),
  [282] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__lua_code, 4),
  [284] = {.entry = {.count = 1, .reusable = false}}, SHIFT(81),
  [286] = {.entry = {.count = 1, .reusable = false}}, SHIFT(76),
  [288] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__lua_code, 4),
  [290] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__lua_code, 7),
  [292] = {.entry = {.count = 1, .reusable = false}}, SHIFT(73),
  [294] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__lua_code, 7),
  [296] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__lua_code, 6),
  [298] = {.entry = {.count = 1, .reusable = false}}, SHIFT(70),
  [300] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__lua_code, 6),
  [302] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [304] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_lua_code, 1),
  [306] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_lua_code, 1),
  [308] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__lua_code, 10),
  [310] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__lua_code, 10),
  [312] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__lua_code, 9),
  [314] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__lua_code, 9),
  [316] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [318] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [320] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [322] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [324] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [326] = {.entry = {.count = 1, .reusable = true}}, SHIFT(82),
  [328] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [330] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [332] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [334] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [336] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [338] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [340] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [342] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [344] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [346] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [348] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_nginx(void) {
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
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
