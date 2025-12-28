#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 13
#define STATE_COUNT 82
#define LARGE_STATE_COUNT 51
#define SYMBOL_COUNT 39
#define ALIAS_COUNT 0
#define TOKEN_COUNT 23
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 9
#define MAX_ALIAS_SEQUENCE_LENGTH 5
#define PRODUCTION_ID_COUNT 15

enum {
  sym__ws = 1,
  sym_comment = 2,
  sym_int = 3,
  sym_keyword = 4,
  sym_string_escape = 5,
  anon_sym_DQUOTE = 6,
  aux_sym_string_token1 = 7,
  sym_ignore = 8,
  sym_null = 9,
  sym_bool = 10,
  sym_symbol = 11,
  sym_command = 12,
  sym_slash = 13,
  sym_dot = 14,
  sym_dotdot = 15,
  anon_sym_CARET = 16,
  anon_sym_LPAREN = 17,
  anon_sym_RPAREN = 18,
  anon_sym_LBRACE = 19,
  anon_sym_RBRACE = 20,
  anon_sym_LBRACK = 21,
  anon_sym_RBRACK = 22,
  sym_source = 23,
  sym__gap = 24,
  sym__form = 25,
  sym_string = 26,
  sym_subpath = 27,
  sym_path = 28,
  sym_symbind = 29,
  sym_meta = 30,
  sym_list = 31,
  sym_scope = 32,
  sym_cons = 33,
  aux_sym_source_repeat1 = 34,
  aux_sym_string_repeat1 = 35,
  aux_sym_subpath_repeat1 = 36,
  aux_sym_meta_repeat1 = 37,
  aux_sym_list_repeat1 = 38,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym__ws] = "_ws",
  [sym_comment] = "comment",
  [sym_int] = "int",
  [sym_keyword] = "keyword",
  [sym_string_escape] = "string_escape",
  [anon_sym_DQUOTE] = "\"",
  [aux_sym_string_token1] = "string_token1",
  [sym_ignore] = "ignore",
  [sym_null] = "null",
  [sym_bool] = "bool",
  [sym_symbol] = "symbol",
  [sym_command] = "command",
  [sym_slash] = "slash",
  [sym_dot] = "dot",
  [sym_dotdot] = "dotdot",
  [anon_sym_CARET] = "^",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [sym_source] = "source",
  [sym__gap] = "_gap",
  [sym__form] = "_form",
  [sym_string] = "string",
  [sym_subpath] = "subpath",
  [sym_path] = "path",
  [sym_symbind] = "symbind",
  [sym_meta] = "meta",
  [sym_list] = "list",
  [sym_scope] = "scope",
  [sym_cons] = "cons",
  [aux_sym_source_repeat1] = "source_repeat1",
  [aux_sym_string_repeat1] = "string_repeat1",
  [aux_sym_subpath_repeat1] = "subpath_repeat1",
  [aux_sym_meta_repeat1] = "meta_repeat1",
  [aux_sym_list_repeat1] = "list_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym__ws] = sym__ws,
  [sym_comment] = sym_comment,
  [sym_int] = sym_int,
  [sym_keyword] = sym_keyword,
  [sym_string_escape] = sym_string_escape,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [aux_sym_string_token1] = aux_sym_string_token1,
  [sym_ignore] = sym_ignore,
  [sym_null] = sym_null,
  [sym_bool] = sym_bool,
  [sym_symbol] = sym_symbol,
  [sym_command] = sym_command,
  [sym_slash] = sym_slash,
  [sym_dot] = sym_dot,
  [sym_dotdot] = sym_dotdot,
  [anon_sym_CARET] = anon_sym_CARET,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [sym_source] = sym_source,
  [sym__gap] = sym__gap,
  [sym__form] = sym__form,
  [sym_string] = sym_string,
  [sym_subpath] = sym_subpath,
  [sym_path] = sym_path,
  [sym_symbind] = sym_symbind,
  [sym_meta] = sym_meta,
  [sym_list] = sym_list,
  [sym_scope] = sym_scope,
  [sym_cons] = sym_cons,
  [aux_sym_source_repeat1] = aux_sym_source_repeat1,
  [aux_sym_string_repeat1] = aux_sym_string_repeat1,
  [aux_sym_subpath_repeat1] = aux_sym_subpath_repeat1,
  [aux_sym_meta_repeat1] = aux_sym_meta_repeat1,
  [aux_sym_list_repeat1] = aux_sym_list_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym__ws] = {
    .visible = false,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_int] = {
    .visible = true,
    .named = true,
  },
  [sym_keyword] = {
    .visible = true,
    .named = true,
  },
  [sym_string_escape] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_string_token1] = {
    .visible = false,
    .named = false,
  },
  [sym_ignore] = {
    .visible = true,
    .named = true,
  },
  [sym_null] = {
    .visible = true,
    .named = true,
  },
  [sym_bool] = {
    .visible = true,
    .named = true,
  },
  [sym_symbol] = {
    .visible = true,
    .named = true,
  },
  [sym_command] = {
    .visible = true,
    .named = true,
  },
  [sym_slash] = {
    .visible = true,
    .named = true,
  },
  [sym_dot] = {
    .visible = true,
    .named = true,
  },
  [sym_dotdot] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_CARET] = {
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
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACE] = {
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
  [sym_source] = {
    .visible = true,
    .named = true,
  },
  [sym__gap] = {
    .visible = false,
    .named = true,
  },
  [sym__form] = {
    .visible = false,
    .named = true,
  },
  [sym_string] = {
    .visible = true,
    .named = true,
  },
  [sym_subpath] = {
    .visible = true,
    .named = true,
  },
  [sym_path] = {
    .visible = true,
    .named = true,
  },
  [sym_symbind] = {
    .visible = true,
    .named = true,
  },
  [sym_meta] = {
    .visible = true,
    .named = true,
  },
  [sym_list] = {
    .visible = true,
    .named = true,
  },
  [sym_scope] = {
    .visible = true,
    .named = true,
  },
  [sym_cons] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_string_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_subpath_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_meta_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_list_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum {
  field_close = 1,
  field_escape = 2,
  field_form = 3,
  field_keyword = 4,
  field_marker = 5,
  field_meta = 6,
  field_open = 7,
  field_path = 8,
  field_value = 9,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_close] = "close",
  [field_escape] = "escape",
  [field_form] = "form",
  [field_keyword] = "keyword",
  [field_marker] = "marker",
  [field_meta] = "meta",
  [field_open] = "open",
  [field_path] = "path",
  [field_value] = "value",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 1},
  [3] = {.index = 2, .length = 2},
  [4] = {.index = 4, .length = 2},
  [5] = {.index = 6, .length = 2},
  [6] = {.index = 8, .length = 1},
  [7] = {.index = 9, .length = 1},
  [8] = {.index = 10, .length = 2},
  [9] = {.index = 12, .length = 3},
  [10] = {.index = 15, .length = 3},
  [11] = {.index = 18, .length = 2},
  [12] = {.index = 20, .length = 3},
  [13] = {.index = 23, .length = 3},
  [14] = {.index = 26, .length = 3},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_path, 0},
  [1] =
    {field_escape, 0},
  [2] =
    {field_form, 0},
    {field_keyword, 1},
  [4] =
    {field_form, 0},
    {field_path, 1},
  [6] =
    {field_close, 1},
    {field_open, 0},
  [8] =
    {field_value, 0},
  [9] =
    {field_escape, 1, .inherited = true},
  [10] =
    {field_escape, 0, .inherited = true},
    {field_escape, 1, .inherited = true},
  [12] =
    {field_form, 2},
    {field_marker, 0},
    {field_meta, 1},
  [15] =
    {field_close, 2},
    {field_open, 0},
    {field_value, 1, .inherited = true},
  [18] =
    {field_value, 0, .inherited = true},
    {field_value, 1, .inherited = true},
  [20] =
    {field_form, 3},
    {field_marker, 0},
    {field_meta, 1},
  [23] =
    {field_form, 3},
    {field_marker, 0},
    {field_meta, 2},
  [26] =
    {field_form, 4},
    {field_marker, 0},
    {field_meta, 2},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static inline bool sym_comment_character_set_1(int32_t c) {
  return (c < ':'
    ? (c < '"'
      ? (c < '\t'
        ? c == 0
        : (c <= '\r' || c == ' '))
      : (c <= '"' || (c < ','
        ? (c >= '(' && c <= ')')
        : (c <= ',' || c == '/'))))
    : (c <= ';' || (c < '}'
      ? (c < ']'
        ? c == '['
        : (c <= '^' || c == '{'))
      : (c <= '}' || (c < 160
        ? c == 133
        : c <= 160)))));
}

static inline bool sym_comment_character_set_2(int32_t c) {
  return (c < ':'
    ? (c < '('
      ? (c < ' '
        ? (c >= '\t' && c <= '\r')
        : (c <= ' ' || c == '"'))
      : (c <= ')' || (c < '/'
        ? c == ','
        : c <= '/')))
    : (c <= ';' || (c < '}'
      ? (c < ']'
        ? c == '['
        : (c <= '^' || c == '{'))
      : (c <= '}' || (c < 160
        ? c == 133
        : c <= 160)))));
}

static inline bool sym_keyword_character_set_1(int32_t c) {
  return (c < '.'
    ? (c < '"'
      ? (c < '\t'
        ? c == 0
        : (c <= '\r' || c == ' '))
      : (c <= '"' || (c < ','
        ? (c >= '(' && c <= ')')
        : c <= ',')))
    : (c <= ';' || (c < '}'
      ? (c < ']'
        ? c == '['
        : (c <= '^' || c == '{'))
      : (c <= '}' || (c < 160
        ? c == 133
        : c <= 160)))));
}

static inline bool sym_symbol_character_set_1(int32_t c) {
  return (c < '['
    ? (c < '('
      ? (c < 11
        ? c == 0
        : (c <= '\f' || c == '"'))
      : (c <= ')' || (c < '.'
        ? c == ','
        : c <= ';')))
    : (c <= '[' || (c < '}'
      ? (c < '{'
        ? (c >= ']' && c <= '^')
        : c <= '{')
      : (c <= '}' || (c < 160
        ? c == 133
        : c <= 160)))));
}

static inline bool sym_symbol_character_set_2(int32_t c) {
  return (c < ':'
    ? (c < '('
      ? (c < '\t'
        ? c == 0
        : (c <= '\r' || (c >= ' ' && c <= '"')))
      : (c <= ')' || (c < '/'
        ? c == ','
        : c <= '/')))
    : (c <= ';' || (c < '}'
      ? (c < ']'
        ? c == '['
        : (c <= '^' || c == '{'))
      : (c <= '}' || (c < 160
        ? c == 133
        : c <= 160)))));
}

static inline bool sym_symbol_character_set_3(int32_t c) {
  return (c < ':'
    ? (c < '('
      ? (c < '\t'
        ? c == 0
        : (c <= '\r' || c == ' '))
      : (c <= ')' || (c < '/'
        ? c == ','
        : c <= '/')))
    : (c <= ';' || (c < '}'
      ? (c < '{'
        ? (c >= '[' && c <= '^')
        : c <= '{')
      : (c <= '}' || (c < 160
        ? c == 133
        : c <= 160)))));
}

static inline bool sym_symbol_character_set_4(int32_t c) {
  return (c < '/'
    ? (c < '"'
      ? (c < '\t'
        ? c == 0
        : (c <= '\r' || c == ' '))
      : (c <= '"' || (c < ','
        ? (c >= '(' && c <= ')')
        : c <= ',')))
    : (c <= ';' || (c < '}'
      ? (c < ']'
        ? c == '['
        : (c <= '^' || c == '{'))
      : (c <= '}' || (c < 160
        ? c == 133
        : c <= 160)))));
}

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(6);
      if (lookahead == '"') ADVANCE(16);
      if (lookahead == '#') ADVANCE(22);
      if (lookahead == '(') ADVANCE(40);
      if (lookahead == ')') ADVANCE(41);
      if (lookahead == '.') ADVANCE(37);
      if (lookahead == '/') ADVANCE(36);
      if (lookahead == ':') ADVANCE(4);
      if (lookahead == ';') ADVANCE(11);
      if (lookahead == '[') ADVANCE(44);
      if (lookahead == '\\') ADVANCE(23);
      if (lookahead == ']') ADVANCE(45);
      if (lookahead == '^') ADVANCE(39);
      if (lookahead == '_') ADVANCE(19);
      if (lookahead == 'f') ADVANCE(24);
      if (lookahead == 'n') ADVANCE(32);
      if (lookahead == 't') ADVANCE(29);
      if (lookahead == '{') ADVANCE(42);
      if (lookahead == '}') ADVANCE(43);
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(33);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(7);
      if (lookahead == 11 ||
          lookahead == '\f' ||
          lookahead == ',' ||
          lookahead == 133 ||
          lookahead == 160) ADVANCE(8);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(12);
      if (lookahead != 0) ADVANCE(34);
      END_STATE();
    case 1:
      if (lookahead == '"') ADVANCE(16);
      if (lookahead == '\\') ADVANCE(3);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(17);
      if (lookahead != 0) ADVANCE(18);
      END_STATE();
    case 2:
      if (lookahead == '/') ADVANCE(36);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(2)
      if (!sym_symbol_character_set_1(lookahead)) ADVANCE(34);
      END_STATE();
    case 3:
      if (lookahead == '"' ||
          lookahead == '\\' ||
          lookahead == 'a' ||
          lookahead == 'b' ||
          lookahead == 'f' ||
          lookahead == 'n' ||
          lookahead == 'r' ||
          lookahead == 't' ||
          lookahead == 'v') ADVANCE(14);
      END_STATE();
    case 4:
      if (!sym_keyword_character_set_1(lookahead)) ADVANCE(13);
      END_STATE();
    case 5:
      if (eof) ADVANCE(6);
      if (lookahead == '"') ADVANCE(16);
      if (lookahead == '#') ADVANCE(22);
      if (lookahead == '(') ADVANCE(40);
      if (lookahead == ')') ADVANCE(41);
      if (lookahead == '.') ADVANCE(37);
      if (lookahead == '/') ADVANCE(36);
      if (lookahead == ':') ADVANCE(4);
      if (lookahead == ';') ADVANCE(11);
      if (lookahead == '[') ADVANCE(44);
      if (lookahead == ']') ADVANCE(45);
      if (lookahead == '^') ADVANCE(39);
      if (lookahead == '_') ADVANCE(19);
      if (lookahead == 'f') ADVANCE(24);
      if (lookahead == 'n') ADVANCE(32);
      if (lookahead == 't') ADVANCE(29);
      if (lookahead == '{') ADVANCE(42);
      if (lookahead == '}') ADVANCE(43);
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(33);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(7);
      if (lookahead == 11 ||
          lookahead == '\f' ||
          lookahead == ',' ||
          lookahead == 133 ||
          lookahead == 160) ADVANCE(8);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(12);
      if (lookahead != 0) ADVANCE(34);
      END_STATE();
    case 6:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 7:
      ACCEPT_TOKEN(sym__ws);
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(33);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(7);
      if (lookahead == 11 ||
          lookahead == '\f' ||
          lookahead == ',' ||
          lookahead == 133 ||
          lookahead == 160) ADVANCE(8);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(12);
      END_STATE();
    case 8:
      ACCEPT_TOKEN(sym__ws);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ' ||
          lookahead == ',' ||
          lookahead == 133 ||
          lookahead == 160) ADVANCE(8);
      END_STATE();
    case 9:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 10:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\n') ADVANCE(9);
      if (!sym_comment_character_set_1(lookahead)) ADVANCE(10);
      if (sym_comment_character_set_2(lookahead)) ADVANCE(11);
      END_STATE();
    case 11:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\n') ADVANCE(9);
      if (lookahead != 0) ADVANCE(11);
      END_STATE();
    case 12:
      ACCEPT_TOKEN(sym_int);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(12);
      END_STATE();
    case 13:
      ACCEPT_TOKEN(sym_keyword);
      if (!sym_comment_character_set_1(lookahead)) ADVANCE(13);
      END_STATE();
    case 14:
      ACCEPT_TOKEN(sym_string_escape);
      END_STATE();
    case 15:
      ACCEPT_TOKEN(sym_string_escape);
      if (!sym_comment_character_set_1(lookahead)) ADVANCE(34);
      END_STATE();
    case 16:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 17:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(17);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(18);
      END_STATE();
    case 18:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(18);
      END_STATE();
    case 19:
      ACCEPT_TOKEN(sym_ignore);
      if (!sym_comment_character_set_1(lookahead)) ADVANCE(34);
      END_STATE();
    case 20:
      ACCEPT_TOKEN(sym_null);
      if (!sym_comment_character_set_1(lookahead)) ADVANCE(34);
      END_STATE();
    case 21:
      ACCEPT_TOKEN(sym_bool);
      if (!sym_comment_character_set_1(lookahead)) ADVANCE(34);
      END_STATE();
    case 22:
      ACCEPT_TOKEN(sym_symbol);
      if (lookahead == '!') ADVANCE(10);
      if (!sym_symbol_character_set_2(lookahead)) ADVANCE(34);
      END_STATE();
    case 23:
      ACCEPT_TOKEN(sym_symbol);
      if (lookahead == '"') ADVANCE(14);
      if (lookahead == '\\' ||
          lookahead == 'a' ||
          lookahead == 'b' ||
          lookahead == 'f' ||
          lookahead == 'n' ||
          lookahead == 'r' ||
          lookahead == 't' ||
          lookahead == 'v') ADVANCE(15);
      if (!sym_symbol_character_set_3(lookahead)) ADVANCE(34);
      END_STATE();
    case 24:
      ACCEPT_TOKEN(sym_symbol);
      if (lookahead == 'a') ADVANCE(26);
      if (!sym_comment_character_set_1(lookahead)) ADVANCE(34);
      END_STATE();
    case 25:
      ACCEPT_TOKEN(sym_symbol);
      if (lookahead == 'e') ADVANCE(21);
      if (!sym_comment_character_set_1(lookahead)) ADVANCE(34);
      END_STATE();
    case 26:
      ACCEPT_TOKEN(sym_symbol);
      if (lookahead == 'l') ADVANCE(30);
      if (!sym_comment_character_set_1(lookahead)) ADVANCE(34);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(sym_symbol);
      if (lookahead == 'l') ADVANCE(20);
      if (!sym_comment_character_set_1(lookahead)) ADVANCE(34);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(sym_symbol);
      if (lookahead == 'l') ADVANCE(27);
      if (!sym_comment_character_set_1(lookahead)) ADVANCE(34);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(sym_symbol);
      if (lookahead == 'r') ADVANCE(31);
      if (!sym_comment_character_set_1(lookahead)) ADVANCE(34);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(sym_symbol);
      if (lookahead == 's') ADVANCE(25);
      if (!sym_comment_character_set_1(lookahead)) ADVANCE(34);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(sym_symbol);
      if (lookahead == 'u') ADVANCE(25);
      if (!sym_comment_character_set_1(lookahead)) ADVANCE(34);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(sym_symbol);
      if (lookahead == 'u') ADVANCE(28);
      if (!sym_comment_character_set_1(lookahead)) ADVANCE(34);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(sym_symbol);
      if (!sym_symbol_character_set_4(lookahead)) ADVANCE(34);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(12);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(sym_symbol);
      if (!sym_comment_character_set_1(lookahead)) ADVANCE(34);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(sym_command);
      if (!sym_comment_character_set_1(lookahead)) ADVANCE(35);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(sym_slash);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(sym_dot);
      if (lookahead == '.') ADVANCE(38);
      if (!sym_symbol_character_set_4(lookahead)) ADVANCE(35);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(sym_dotdot);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(anon_sym_CARET);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 5},
  [2] = {.lex_state = 5},
  [3] = {.lex_state = 5},
  [4] = {.lex_state = 5},
  [5] = {.lex_state = 5},
  [6] = {.lex_state = 5},
  [7] = {.lex_state = 5},
  [8] = {.lex_state = 5},
  [9] = {.lex_state = 5},
  [10] = {.lex_state = 5},
  [11] = {.lex_state = 5},
  [12] = {.lex_state = 5},
  [13] = {.lex_state = 5},
  [14] = {.lex_state = 5},
  [15] = {.lex_state = 5},
  [16] = {.lex_state = 5},
  [17] = {.lex_state = 5},
  [18] = {.lex_state = 5},
  [19] = {.lex_state = 5},
  [20] = {.lex_state = 5},
  [21] = {.lex_state = 5},
  [22] = {.lex_state = 5},
  [23] = {.lex_state = 5},
  [24] = {.lex_state = 5},
  [25] = {.lex_state = 5},
  [26] = {.lex_state = 5},
  [27] = {.lex_state = 5},
  [28] = {.lex_state = 5},
  [29] = {.lex_state = 5},
  [30] = {.lex_state = 5},
  [31] = {.lex_state = 5},
  [32] = {.lex_state = 5},
  [33] = {.lex_state = 5},
  [34] = {.lex_state = 5},
  [35] = {.lex_state = 5},
  [36] = {.lex_state = 5},
  [37] = {.lex_state = 5},
  [38] = {.lex_state = 5},
  [39] = {.lex_state = 5},
  [40] = {.lex_state = 5},
  [41] = {.lex_state = 5},
  [42] = {.lex_state = 5},
  [43] = {.lex_state = 5},
  [44] = {.lex_state = 5},
  [45] = {.lex_state = 5},
  [46] = {.lex_state = 5},
  [47] = {.lex_state = 5},
  [48] = {.lex_state = 5},
  [49] = {.lex_state = 5},
  [50] = {.lex_state = 5},
  [51] = {.lex_state = 5},
  [52] = {.lex_state = 5},
  [53] = {.lex_state = 5},
  [54] = {.lex_state = 5},
  [55] = {.lex_state = 5},
  [56] = {.lex_state = 5},
  [57] = {.lex_state = 5},
  [58] = {.lex_state = 5},
  [59] = {.lex_state = 5},
  [60] = {.lex_state = 5},
  [61] = {.lex_state = 5},
  [62] = {.lex_state = 5},
  [63] = {.lex_state = 5},
  [64] = {.lex_state = 5},
  [65] = {.lex_state = 5},
  [66] = {.lex_state = 5},
  [67] = {.lex_state = 5},
  [68] = {.lex_state = 5},
  [69] = {.lex_state = 5},
  [70] = {.lex_state = 5},
  [71] = {.lex_state = 1},
  [72] = {.lex_state = 1},
  [73] = {.lex_state = 1},
  [74] = {.lex_state = 1},
  [75] = {.lex_state = 1},
  [76] = {.lex_state = 2},
  [77] = {.lex_state = 1},
  [78] = {.lex_state = 2},
  [79] = {.lex_state = 2},
  [80] = {.lex_state = 0},
  [81] = {.lex_state = 2},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym__ws] = ACTIONS(1),
    [sym_comment] = ACTIONS(1),
    [sym_int] = ACTIONS(1),
    [sym_keyword] = ACTIONS(1),
    [sym_string_escape] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [sym_ignore] = ACTIONS(1),
    [sym_null] = ACTIONS(1),
    [sym_bool] = ACTIONS(1),
    [sym_symbol] = ACTIONS(1),
    [sym_command] = ACTIONS(1),
    [sym_slash] = ACTIONS(1),
    [sym_dot] = ACTIONS(1),
    [sym_dotdot] = ACTIONS(1),
    [anon_sym_CARET] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
  },
  [1] = {
    [sym_source] = STATE(80),
    [sym__gap] = STATE(12),
    [sym__form] = STATE(12),
    [sym_string] = STATE(12),
    [sym_subpath] = STATE(67),
    [sym_path] = STATE(12),
    [sym_symbind] = STATE(34),
    [sym_meta] = STATE(12),
    [sym_list] = STATE(12),
    [sym_scope] = STATE(12),
    [sym_cons] = STATE(12),
    [aux_sym_source_repeat1] = STATE(12),
    [aux_sym_subpath_repeat1] = STATE(53),
    [ts_builtin_sym_end] = ACTIONS(3),
    [sym__ws] = ACTIONS(5),
    [sym_comment] = ACTIONS(5),
    [sym_int] = ACTIONS(5),
    [sym_keyword] = ACTIONS(5),
    [anon_sym_DQUOTE] = ACTIONS(7),
    [sym_ignore] = ACTIONS(5),
    [sym_null] = ACTIONS(5),
    [sym_bool] = ACTIONS(5),
    [sym_symbol] = ACTIONS(9),
    [sym_command] = ACTIONS(5),
    [sym_slash] = ACTIONS(11),
    [sym_dot] = ACTIONS(13),
    [sym_dotdot] = ACTIONS(13),
    [anon_sym_CARET] = ACTIONS(15),
    [anon_sym_LPAREN] = ACTIONS(17),
    [anon_sym_LBRACE] = ACTIONS(19),
    [anon_sym_LBRACK] = ACTIONS(21),
  },
  [2] = {
    [sym__gap] = STATE(2),
    [sym__form] = STATE(45),
    [sym_string] = STATE(45),
    [sym_subpath] = STATE(47),
    [sym_path] = STATE(45),
    [sym_symbind] = STATE(29),
    [sym_meta] = STATE(45),
    [sym_list] = STATE(45),
    [sym_scope] = STATE(45),
    [sym_cons] = STATE(45),
    [aux_sym_subpath_repeat1] = STATE(31),
    [aux_sym_list_repeat1] = STATE(2),
    [sym__ws] = ACTIONS(23),
    [sym_comment] = ACTIONS(23),
    [sym_int] = ACTIONS(26),
    [sym_keyword] = ACTIONS(26),
    [anon_sym_DQUOTE] = ACTIONS(29),
    [sym_ignore] = ACTIONS(26),
    [sym_null] = ACTIONS(26),
    [sym_bool] = ACTIONS(26),
    [sym_symbol] = ACTIONS(32),
    [sym_command] = ACTIONS(26),
    [sym_slash] = ACTIONS(35),
    [sym_dot] = ACTIONS(38),
    [sym_dotdot] = ACTIONS(38),
    [anon_sym_CARET] = ACTIONS(41),
    [anon_sym_LPAREN] = ACTIONS(44),
    [anon_sym_RPAREN] = ACTIONS(47),
    [anon_sym_LBRACE] = ACTIONS(49),
    [anon_sym_RBRACE] = ACTIONS(47),
    [anon_sym_LBRACK] = ACTIONS(52),
    [anon_sym_RBRACK] = ACTIONS(47),
  },
  [3] = {
    [sym__gap] = STATE(2),
    [sym__form] = STATE(45),
    [sym_string] = STATE(45),
    [sym_subpath] = STATE(47),
    [sym_path] = STATE(45),
    [sym_symbind] = STATE(29),
    [sym_meta] = STATE(45),
    [sym_list] = STATE(45),
    [sym_scope] = STATE(45),
    [sym_cons] = STATE(45),
    [aux_sym_subpath_repeat1] = STATE(31),
    [aux_sym_list_repeat1] = STATE(2),
    [sym__ws] = ACTIONS(55),
    [sym_comment] = ACTIONS(55),
    [sym_int] = ACTIONS(57),
    [sym_keyword] = ACTIONS(57),
    [anon_sym_DQUOTE] = ACTIONS(59),
    [sym_ignore] = ACTIONS(57),
    [sym_null] = ACTIONS(57),
    [sym_bool] = ACTIONS(57),
    [sym_symbol] = ACTIONS(61),
    [sym_command] = ACTIONS(57),
    [sym_slash] = ACTIONS(63),
    [sym_dot] = ACTIONS(65),
    [sym_dotdot] = ACTIONS(65),
    [anon_sym_CARET] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(69),
    [anon_sym_RPAREN] = ACTIONS(71),
    [anon_sym_LBRACE] = ACTIONS(73),
    [anon_sym_LBRACK] = ACTIONS(75),
  },
  [4] = {
    [sym__gap] = STATE(3),
    [sym__form] = STATE(45),
    [sym_string] = STATE(45),
    [sym_subpath] = STATE(47),
    [sym_path] = STATE(45),
    [sym_symbind] = STATE(29),
    [sym_meta] = STATE(45),
    [sym_list] = STATE(45),
    [sym_scope] = STATE(45),
    [sym_cons] = STATE(45),
    [aux_sym_subpath_repeat1] = STATE(31),
    [aux_sym_list_repeat1] = STATE(3),
    [sym__ws] = ACTIONS(77),
    [sym_comment] = ACTIONS(77),
    [sym_int] = ACTIONS(57),
    [sym_keyword] = ACTIONS(57),
    [anon_sym_DQUOTE] = ACTIONS(59),
    [sym_ignore] = ACTIONS(57),
    [sym_null] = ACTIONS(57),
    [sym_bool] = ACTIONS(57),
    [sym_symbol] = ACTIONS(61),
    [sym_command] = ACTIONS(57),
    [sym_slash] = ACTIONS(63),
    [sym_dot] = ACTIONS(65),
    [sym_dotdot] = ACTIONS(65),
    [anon_sym_CARET] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(69),
    [anon_sym_RPAREN] = ACTIONS(79),
    [anon_sym_LBRACE] = ACTIONS(73),
    [anon_sym_LBRACK] = ACTIONS(75),
  },
  [5] = {
    [sym__gap] = STATE(2),
    [sym__form] = STATE(45),
    [sym_string] = STATE(45),
    [sym_subpath] = STATE(47),
    [sym_path] = STATE(45),
    [sym_symbind] = STATE(29),
    [sym_meta] = STATE(45),
    [sym_list] = STATE(45),
    [sym_scope] = STATE(45),
    [sym_cons] = STATE(45),
    [aux_sym_subpath_repeat1] = STATE(31),
    [aux_sym_list_repeat1] = STATE(2),
    [sym__ws] = ACTIONS(55),
    [sym_comment] = ACTIONS(55),
    [sym_int] = ACTIONS(57),
    [sym_keyword] = ACTIONS(57),
    [anon_sym_DQUOTE] = ACTIONS(59),
    [sym_ignore] = ACTIONS(57),
    [sym_null] = ACTIONS(57),
    [sym_bool] = ACTIONS(57),
    [sym_symbol] = ACTIONS(61),
    [sym_command] = ACTIONS(57),
    [sym_slash] = ACTIONS(63),
    [sym_dot] = ACTIONS(65),
    [sym_dotdot] = ACTIONS(65),
    [anon_sym_CARET] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(69),
    [anon_sym_LBRACE] = ACTIONS(73),
    [anon_sym_RBRACE] = ACTIONS(81),
    [anon_sym_LBRACK] = ACTIONS(75),
  },
  [6] = {
    [sym__gap] = STATE(6),
    [sym__form] = STATE(6),
    [sym_string] = STATE(6),
    [sym_subpath] = STATE(67),
    [sym_path] = STATE(6),
    [sym_symbind] = STATE(34),
    [sym_meta] = STATE(6),
    [sym_list] = STATE(6),
    [sym_scope] = STATE(6),
    [sym_cons] = STATE(6),
    [aux_sym_source_repeat1] = STATE(6),
    [aux_sym_subpath_repeat1] = STATE(53),
    [ts_builtin_sym_end] = ACTIONS(83),
    [sym__ws] = ACTIONS(85),
    [sym_comment] = ACTIONS(85),
    [sym_int] = ACTIONS(85),
    [sym_keyword] = ACTIONS(85),
    [anon_sym_DQUOTE] = ACTIONS(88),
    [sym_ignore] = ACTIONS(85),
    [sym_null] = ACTIONS(85),
    [sym_bool] = ACTIONS(85),
    [sym_symbol] = ACTIONS(91),
    [sym_command] = ACTIONS(85),
    [sym_slash] = ACTIONS(94),
    [sym_dot] = ACTIONS(97),
    [sym_dotdot] = ACTIONS(97),
    [anon_sym_CARET] = ACTIONS(100),
    [anon_sym_LPAREN] = ACTIONS(103),
    [anon_sym_LBRACE] = ACTIONS(106),
    [anon_sym_LBRACK] = ACTIONS(109),
  },
  [7] = {
    [sym__gap] = STATE(2),
    [sym__form] = STATE(45),
    [sym_string] = STATE(45),
    [sym_subpath] = STATE(47),
    [sym_path] = STATE(45),
    [sym_symbind] = STATE(29),
    [sym_meta] = STATE(45),
    [sym_list] = STATE(45),
    [sym_scope] = STATE(45),
    [sym_cons] = STATE(45),
    [aux_sym_subpath_repeat1] = STATE(31),
    [aux_sym_list_repeat1] = STATE(2),
    [sym__ws] = ACTIONS(55),
    [sym_comment] = ACTIONS(55),
    [sym_int] = ACTIONS(57),
    [sym_keyword] = ACTIONS(57),
    [anon_sym_DQUOTE] = ACTIONS(59),
    [sym_ignore] = ACTIONS(57),
    [sym_null] = ACTIONS(57),
    [sym_bool] = ACTIONS(57),
    [sym_symbol] = ACTIONS(61),
    [sym_command] = ACTIONS(57),
    [sym_slash] = ACTIONS(63),
    [sym_dot] = ACTIONS(65),
    [sym_dotdot] = ACTIONS(65),
    [anon_sym_CARET] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(69),
    [anon_sym_LBRACE] = ACTIONS(73),
    [anon_sym_LBRACK] = ACTIONS(75),
    [anon_sym_RBRACK] = ACTIONS(112),
  },
  [8] = {
    [sym__gap] = STATE(14),
    [sym__form] = STATE(45),
    [sym_string] = STATE(45),
    [sym_subpath] = STATE(47),
    [sym_path] = STATE(45),
    [sym_symbind] = STATE(29),
    [sym_meta] = STATE(45),
    [sym_list] = STATE(45),
    [sym_scope] = STATE(45),
    [sym_cons] = STATE(45),
    [aux_sym_subpath_repeat1] = STATE(31),
    [aux_sym_list_repeat1] = STATE(14),
    [sym__ws] = ACTIONS(114),
    [sym_comment] = ACTIONS(114),
    [sym_int] = ACTIONS(57),
    [sym_keyword] = ACTIONS(57),
    [anon_sym_DQUOTE] = ACTIONS(59),
    [sym_ignore] = ACTIONS(57),
    [sym_null] = ACTIONS(57),
    [sym_bool] = ACTIONS(57),
    [sym_symbol] = ACTIONS(61),
    [sym_command] = ACTIONS(57),
    [sym_slash] = ACTIONS(63),
    [sym_dot] = ACTIONS(65),
    [sym_dotdot] = ACTIONS(65),
    [anon_sym_CARET] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(69),
    [anon_sym_LBRACE] = ACTIONS(73),
    [anon_sym_RBRACE] = ACTIONS(116),
    [anon_sym_LBRACK] = ACTIONS(75),
  },
  [9] = {
    [sym__gap] = STATE(7),
    [sym__form] = STATE(45),
    [sym_string] = STATE(45),
    [sym_subpath] = STATE(47),
    [sym_path] = STATE(45),
    [sym_symbind] = STATE(29),
    [sym_meta] = STATE(45),
    [sym_list] = STATE(45),
    [sym_scope] = STATE(45),
    [sym_cons] = STATE(45),
    [aux_sym_subpath_repeat1] = STATE(31),
    [aux_sym_list_repeat1] = STATE(7),
    [sym__ws] = ACTIONS(118),
    [sym_comment] = ACTIONS(118),
    [sym_int] = ACTIONS(57),
    [sym_keyword] = ACTIONS(57),
    [anon_sym_DQUOTE] = ACTIONS(59),
    [sym_ignore] = ACTIONS(57),
    [sym_null] = ACTIONS(57),
    [sym_bool] = ACTIONS(57),
    [sym_symbol] = ACTIONS(61),
    [sym_command] = ACTIONS(57),
    [sym_slash] = ACTIONS(63),
    [sym_dot] = ACTIONS(65),
    [sym_dotdot] = ACTIONS(65),
    [anon_sym_CARET] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(69),
    [anon_sym_LBRACE] = ACTIONS(73),
    [anon_sym_LBRACK] = ACTIONS(75),
    [anon_sym_RBRACK] = ACTIONS(120),
  },
  [10] = {
    [sym__gap] = STATE(16),
    [sym__form] = STATE(45),
    [sym_string] = STATE(45),
    [sym_subpath] = STATE(47),
    [sym_path] = STATE(45),
    [sym_symbind] = STATE(29),
    [sym_meta] = STATE(45),
    [sym_list] = STATE(45),
    [sym_scope] = STATE(45),
    [sym_cons] = STATE(45),
    [aux_sym_subpath_repeat1] = STATE(31),
    [aux_sym_list_repeat1] = STATE(16),
    [sym__ws] = ACTIONS(122),
    [sym_comment] = ACTIONS(122),
    [sym_int] = ACTIONS(57),
    [sym_keyword] = ACTIONS(57),
    [anon_sym_DQUOTE] = ACTIONS(59),
    [sym_ignore] = ACTIONS(57),
    [sym_null] = ACTIONS(57),
    [sym_bool] = ACTIONS(57),
    [sym_symbol] = ACTIONS(61),
    [sym_command] = ACTIONS(57),
    [sym_slash] = ACTIONS(63),
    [sym_dot] = ACTIONS(65),
    [sym_dotdot] = ACTIONS(65),
    [anon_sym_CARET] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(69),
    [anon_sym_LBRACE] = ACTIONS(73),
    [anon_sym_LBRACK] = ACTIONS(75),
    [anon_sym_RBRACK] = ACTIONS(124),
  },
  [11] = {
    [sym__gap] = STATE(5),
    [sym__form] = STATE(45),
    [sym_string] = STATE(45),
    [sym_subpath] = STATE(47),
    [sym_path] = STATE(45),
    [sym_symbind] = STATE(29),
    [sym_meta] = STATE(45),
    [sym_list] = STATE(45),
    [sym_scope] = STATE(45),
    [sym_cons] = STATE(45),
    [aux_sym_subpath_repeat1] = STATE(31),
    [aux_sym_list_repeat1] = STATE(5),
    [sym__ws] = ACTIONS(126),
    [sym_comment] = ACTIONS(126),
    [sym_int] = ACTIONS(57),
    [sym_keyword] = ACTIONS(57),
    [anon_sym_DQUOTE] = ACTIONS(59),
    [sym_ignore] = ACTIONS(57),
    [sym_null] = ACTIONS(57),
    [sym_bool] = ACTIONS(57),
    [sym_symbol] = ACTIONS(61),
    [sym_command] = ACTIONS(57),
    [sym_slash] = ACTIONS(63),
    [sym_dot] = ACTIONS(65),
    [sym_dotdot] = ACTIONS(65),
    [anon_sym_CARET] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(69),
    [anon_sym_LBRACE] = ACTIONS(73),
    [anon_sym_RBRACE] = ACTIONS(128),
    [anon_sym_LBRACK] = ACTIONS(75),
  },
  [12] = {
    [sym__gap] = STATE(6),
    [sym__form] = STATE(6),
    [sym_string] = STATE(6),
    [sym_subpath] = STATE(67),
    [sym_path] = STATE(6),
    [sym_symbind] = STATE(34),
    [sym_meta] = STATE(6),
    [sym_list] = STATE(6),
    [sym_scope] = STATE(6),
    [sym_cons] = STATE(6),
    [aux_sym_source_repeat1] = STATE(6),
    [aux_sym_subpath_repeat1] = STATE(53),
    [ts_builtin_sym_end] = ACTIONS(130),
    [sym__ws] = ACTIONS(132),
    [sym_comment] = ACTIONS(132),
    [sym_int] = ACTIONS(132),
    [sym_keyword] = ACTIONS(132),
    [anon_sym_DQUOTE] = ACTIONS(7),
    [sym_ignore] = ACTIONS(132),
    [sym_null] = ACTIONS(132),
    [sym_bool] = ACTIONS(132),
    [sym_symbol] = ACTIONS(9),
    [sym_command] = ACTIONS(132),
    [sym_slash] = ACTIONS(11),
    [sym_dot] = ACTIONS(13),
    [sym_dotdot] = ACTIONS(13),
    [anon_sym_CARET] = ACTIONS(15),
    [anon_sym_LPAREN] = ACTIONS(17),
    [anon_sym_LBRACE] = ACTIONS(19),
    [anon_sym_LBRACK] = ACTIONS(21),
  },
  [13] = {
    [sym__gap] = STATE(15),
    [sym__form] = STATE(45),
    [sym_string] = STATE(45),
    [sym_subpath] = STATE(47),
    [sym_path] = STATE(45),
    [sym_symbind] = STATE(29),
    [sym_meta] = STATE(45),
    [sym_list] = STATE(45),
    [sym_scope] = STATE(45),
    [sym_cons] = STATE(45),
    [aux_sym_subpath_repeat1] = STATE(31),
    [aux_sym_list_repeat1] = STATE(15),
    [sym__ws] = ACTIONS(134),
    [sym_comment] = ACTIONS(134),
    [sym_int] = ACTIONS(57),
    [sym_keyword] = ACTIONS(57),
    [anon_sym_DQUOTE] = ACTIONS(59),
    [sym_ignore] = ACTIONS(57),
    [sym_null] = ACTIONS(57),
    [sym_bool] = ACTIONS(57),
    [sym_symbol] = ACTIONS(61),
    [sym_command] = ACTIONS(57),
    [sym_slash] = ACTIONS(63),
    [sym_dot] = ACTIONS(65),
    [sym_dotdot] = ACTIONS(65),
    [anon_sym_CARET] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(69),
    [anon_sym_RPAREN] = ACTIONS(136),
    [anon_sym_LBRACE] = ACTIONS(73),
    [anon_sym_LBRACK] = ACTIONS(75),
  },
  [14] = {
    [sym__gap] = STATE(2),
    [sym__form] = STATE(45),
    [sym_string] = STATE(45),
    [sym_subpath] = STATE(47),
    [sym_path] = STATE(45),
    [sym_symbind] = STATE(29),
    [sym_meta] = STATE(45),
    [sym_list] = STATE(45),
    [sym_scope] = STATE(45),
    [sym_cons] = STATE(45),
    [aux_sym_subpath_repeat1] = STATE(31),
    [aux_sym_list_repeat1] = STATE(2),
    [sym__ws] = ACTIONS(55),
    [sym_comment] = ACTIONS(55),
    [sym_int] = ACTIONS(57),
    [sym_keyword] = ACTIONS(57),
    [anon_sym_DQUOTE] = ACTIONS(59),
    [sym_ignore] = ACTIONS(57),
    [sym_null] = ACTIONS(57),
    [sym_bool] = ACTIONS(57),
    [sym_symbol] = ACTIONS(61),
    [sym_command] = ACTIONS(57),
    [sym_slash] = ACTIONS(63),
    [sym_dot] = ACTIONS(65),
    [sym_dotdot] = ACTIONS(65),
    [anon_sym_CARET] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(69),
    [anon_sym_LBRACE] = ACTIONS(73),
    [anon_sym_RBRACE] = ACTIONS(138),
    [anon_sym_LBRACK] = ACTIONS(75),
  },
  [15] = {
    [sym__gap] = STATE(2),
    [sym__form] = STATE(45),
    [sym_string] = STATE(45),
    [sym_subpath] = STATE(47),
    [sym_path] = STATE(45),
    [sym_symbind] = STATE(29),
    [sym_meta] = STATE(45),
    [sym_list] = STATE(45),
    [sym_scope] = STATE(45),
    [sym_cons] = STATE(45),
    [aux_sym_subpath_repeat1] = STATE(31),
    [aux_sym_list_repeat1] = STATE(2),
    [sym__ws] = ACTIONS(55),
    [sym_comment] = ACTIONS(55),
    [sym_int] = ACTIONS(57),
    [sym_keyword] = ACTIONS(57),
    [anon_sym_DQUOTE] = ACTIONS(59),
    [sym_ignore] = ACTIONS(57),
    [sym_null] = ACTIONS(57),
    [sym_bool] = ACTIONS(57),
    [sym_symbol] = ACTIONS(61),
    [sym_command] = ACTIONS(57),
    [sym_slash] = ACTIONS(63),
    [sym_dot] = ACTIONS(65),
    [sym_dotdot] = ACTIONS(65),
    [anon_sym_CARET] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(69),
    [anon_sym_RPAREN] = ACTIONS(140),
    [anon_sym_LBRACE] = ACTIONS(73),
    [anon_sym_LBRACK] = ACTIONS(75),
  },
  [16] = {
    [sym__gap] = STATE(2),
    [sym__form] = STATE(45),
    [sym_string] = STATE(45),
    [sym_subpath] = STATE(47),
    [sym_path] = STATE(45),
    [sym_symbind] = STATE(29),
    [sym_meta] = STATE(45),
    [sym_list] = STATE(45),
    [sym_scope] = STATE(45),
    [sym_cons] = STATE(45),
    [aux_sym_subpath_repeat1] = STATE(31),
    [aux_sym_list_repeat1] = STATE(2),
    [sym__ws] = ACTIONS(55),
    [sym_comment] = ACTIONS(55),
    [sym_int] = ACTIONS(57),
    [sym_keyword] = ACTIONS(57),
    [anon_sym_DQUOTE] = ACTIONS(59),
    [sym_ignore] = ACTIONS(57),
    [sym_null] = ACTIONS(57),
    [sym_bool] = ACTIONS(57),
    [sym_symbol] = ACTIONS(61),
    [sym_command] = ACTIONS(57),
    [sym_slash] = ACTIONS(63),
    [sym_dot] = ACTIONS(65),
    [sym_dotdot] = ACTIONS(65),
    [anon_sym_CARET] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(69),
    [anon_sym_LBRACE] = ACTIONS(73),
    [anon_sym_LBRACK] = ACTIONS(75),
    [anon_sym_RBRACK] = ACTIONS(142),
  },
  [17] = {
    [sym__gap] = STATE(23),
    [sym__form] = STATE(35),
    [sym_string] = STATE(35),
    [sym_subpath] = STATE(47),
    [sym_path] = STATE(35),
    [sym_symbind] = STATE(29),
    [sym_meta] = STATE(35),
    [sym_list] = STATE(35),
    [sym_scope] = STATE(35),
    [sym_cons] = STATE(35),
    [aux_sym_subpath_repeat1] = STATE(31),
    [aux_sym_meta_repeat1] = STATE(23),
    [sym__ws] = ACTIONS(144),
    [sym_comment] = ACTIONS(144),
    [sym_int] = ACTIONS(146),
    [sym_keyword] = ACTIONS(146),
    [anon_sym_DQUOTE] = ACTIONS(59),
    [sym_ignore] = ACTIONS(146),
    [sym_null] = ACTIONS(146),
    [sym_bool] = ACTIONS(146),
    [sym_symbol] = ACTIONS(61),
    [sym_command] = ACTIONS(146),
    [sym_slash] = ACTIONS(63),
    [sym_dot] = ACTIONS(65),
    [sym_dotdot] = ACTIONS(65),
    [anon_sym_CARET] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(69),
    [anon_sym_LBRACE] = ACTIONS(73),
    [anon_sym_LBRACK] = ACTIONS(75),
  },
  [18] = {
    [sym__gap] = STATE(51),
    [sym__form] = STATE(17),
    [sym_string] = STATE(17),
    [sym_subpath] = STATE(47),
    [sym_path] = STATE(17),
    [sym_symbind] = STATE(29),
    [sym_meta] = STATE(17),
    [sym_list] = STATE(17),
    [sym_scope] = STATE(17),
    [sym_cons] = STATE(17),
    [aux_sym_subpath_repeat1] = STATE(31),
    [aux_sym_meta_repeat1] = STATE(51),
    [sym__ws] = ACTIONS(148),
    [sym_comment] = ACTIONS(148),
    [sym_int] = ACTIONS(150),
    [sym_keyword] = ACTIONS(150),
    [anon_sym_DQUOTE] = ACTIONS(59),
    [sym_ignore] = ACTIONS(150),
    [sym_null] = ACTIONS(150),
    [sym_bool] = ACTIONS(150),
    [sym_symbol] = ACTIONS(61),
    [sym_command] = ACTIONS(150),
    [sym_slash] = ACTIONS(63),
    [sym_dot] = ACTIONS(65),
    [sym_dotdot] = ACTIONS(65),
    [anon_sym_CARET] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(69),
    [anon_sym_LBRACE] = ACTIONS(73),
    [anon_sym_LBRACK] = ACTIONS(75),
  },
  [19] = {
    [sym__gap] = STATE(22),
    [sym__form] = STATE(54),
    [sym_string] = STATE(54),
    [sym_subpath] = STATE(67),
    [sym_path] = STATE(54),
    [sym_symbind] = STATE(34),
    [sym_meta] = STATE(54),
    [sym_list] = STATE(54),
    [sym_scope] = STATE(54),
    [sym_cons] = STATE(54),
    [aux_sym_subpath_repeat1] = STATE(53),
    [aux_sym_meta_repeat1] = STATE(22),
    [sym__ws] = ACTIONS(152),
    [sym_comment] = ACTIONS(152),
    [sym_int] = ACTIONS(154),
    [sym_keyword] = ACTIONS(154),
    [anon_sym_DQUOTE] = ACTIONS(7),
    [sym_ignore] = ACTIONS(154),
    [sym_null] = ACTIONS(154),
    [sym_bool] = ACTIONS(154),
    [sym_symbol] = ACTIONS(9),
    [sym_command] = ACTIONS(154),
    [sym_slash] = ACTIONS(11),
    [sym_dot] = ACTIONS(13),
    [sym_dotdot] = ACTIONS(13),
    [anon_sym_CARET] = ACTIONS(15),
    [anon_sym_LPAREN] = ACTIONS(17),
    [anon_sym_LBRACE] = ACTIONS(19),
    [anon_sym_LBRACK] = ACTIONS(21),
  },
  [20] = {
    [sym__gap] = STATE(51),
    [sym__form] = STATE(27),
    [sym_string] = STATE(27),
    [sym_subpath] = STATE(47),
    [sym_path] = STATE(27),
    [sym_symbind] = STATE(29),
    [sym_meta] = STATE(27),
    [sym_list] = STATE(27),
    [sym_scope] = STATE(27),
    [sym_cons] = STATE(27),
    [aux_sym_subpath_repeat1] = STATE(31),
    [aux_sym_meta_repeat1] = STATE(51),
    [sym__ws] = ACTIONS(148),
    [sym_comment] = ACTIONS(148),
    [sym_int] = ACTIONS(156),
    [sym_keyword] = ACTIONS(156),
    [anon_sym_DQUOTE] = ACTIONS(59),
    [sym_ignore] = ACTIONS(156),
    [sym_null] = ACTIONS(156),
    [sym_bool] = ACTIONS(156),
    [sym_symbol] = ACTIONS(61),
    [sym_command] = ACTIONS(156),
    [sym_slash] = ACTIONS(63),
    [sym_dot] = ACTIONS(65),
    [sym_dotdot] = ACTIONS(65),
    [anon_sym_CARET] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(69),
    [anon_sym_LBRACE] = ACTIONS(73),
    [anon_sym_LBRACK] = ACTIONS(75),
  },
  [21] = {
    [sym__gap] = STATE(26),
    [sym__form] = STATE(40),
    [sym_string] = STATE(40),
    [sym_subpath] = STATE(47),
    [sym_path] = STATE(40),
    [sym_symbind] = STATE(29),
    [sym_meta] = STATE(40),
    [sym_list] = STATE(40),
    [sym_scope] = STATE(40),
    [sym_cons] = STATE(40),
    [aux_sym_subpath_repeat1] = STATE(31),
    [aux_sym_meta_repeat1] = STATE(26),
    [sym__ws] = ACTIONS(158),
    [sym_comment] = ACTIONS(158),
    [sym_int] = ACTIONS(160),
    [sym_keyword] = ACTIONS(160),
    [anon_sym_DQUOTE] = ACTIONS(59),
    [sym_ignore] = ACTIONS(160),
    [sym_null] = ACTIONS(160),
    [sym_bool] = ACTIONS(160),
    [sym_symbol] = ACTIONS(61),
    [sym_command] = ACTIONS(160),
    [sym_slash] = ACTIONS(63),
    [sym_dot] = ACTIONS(65),
    [sym_dotdot] = ACTIONS(65),
    [anon_sym_CARET] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(69),
    [anon_sym_LBRACE] = ACTIONS(73),
    [anon_sym_LBRACK] = ACTIONS(75),
  },
  [22] = {
    [sym__gap] = STATE(51),
    [sym__form] = STATE(57),
    [sym_string] = STATE(57),
    [sym_subpath] = STATE(67),
    [sym_path] = STATE(57),
    [sym_symbind] = STATE(34),
    [sym_meta] = STATE(57),
    [sym_list] = STATE(57),
    [sym_scope] = STATE(57),
    [sym_cons] = STATE(57),
    [aux_sym_subpath_repeat1] = STATE(53),
    [aux_sym_meta_repeat1] = STATE(51),
    [sym__ws] = ACTIONS(148),
    [sym_comment] = ACTIONS(148),
    [sym_int] = ACTIONS(162),
    [sym_keyword] = ACTIONS(162),
    [anon_sym_DQUOTE] = ACTIONS(7),
    [sym_ignore] = ACTIONS(162),
    [sym_null] = ACTIONS(162),
    [sym_bool] = ACTIONS(162),
    [sym_symbol] = ACTIONS(9),
    [sym_command] = ACTIONS(162),
    [sym_slash] = ACTIONS(11),
    [sym_dot] = ACTIONS(13),
    [sym_dotdot] = ACTIONS(13),
    [anon_sym_CARET] = ACTIONS(15),
    [anon_sym_LPAREN] = ACTIONS(17),
    [anon_sym_LBRACE] = ACTIONS(19),
    [anon_sym_LBRACK] = ACTIONS(21),
  },
  [23] = {
    [sym__gap] = STATE(51),
    [sym__form] = STATE(33),
    [sym_string] = STATE(33),
    [sym_subpath] = STATE(47),
    [sym_path] = STATE(33),
    [sym_symbind] = STATE(29),
    [sym_meta] = STATE(33),
    [sym_list] = STATE(33),
    [sym_scope] = STATE(33),
    [sym_cons] = STATE(33),
    [aux_sym_subpath_repeat1] = STATE(31),
    [aux_sym_meta_repeat1] = STATE(51),
    [sym__ws] = ACTIONS(148),
    [sym_comment] = ACTIONS(148),
    [sym_int] = ACTIONS(164),
    [sym_keyword] = ACTIONS(164),
    [anon_sym_DQUOTE] = ACTIONS(59),
    [sym_ignore] = ACTIONS(164),
    [sym_null] = ACTIONS(164),
    [sym_bool] = ACTIONS(164),
    [sym_symbol] = ACTIONS(61),
    [sym_command] = ACTIONS(164),
    [sym_slash] = ACTIONS(63),
    [sym_dot] = ACTIONS(65),
    [sym_dotdot] = ACTIONS(65),
    [anon_sym_CARET] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(69),
    [anon_sym_LBRACE] = ACTIONS(73),
    [anon_sym_LBRACK] = ACTIONS(75),
  },
  [24] = {
    [sym__gap] = STATE(51),
    [sym__form] = STATE(66),
    [sym_string] = STATE(66),
    [sym_subpath] = STATE(67),
    [sym_path] = STATE(66),
    [sym_symbind] = STATE(34),
    [sym_meta] = STATE(66),
    [sym_list] = STATE(66),
    [sym_scope] = STATE(66),
    [sym_cons] = STATE(66),
    [aux_sym_subpath_repeat1] = STATE(53),
    [aux_sym_meta_repeat1] = STATE(51),
    [sym__ws] = ACTIONS(148),
    [sym_comment] = ACTIONS(148),
    [sym_int] = ACTIONS(166),
    [sym_keyword] = ACTIONS(166),
    [anon_sym_DQUOTE] = ACTIONS(7),
    [sym_ignore] = ACTIONS(166),
    [sym_null] = ACTIONS(166),
    [sym_bool] = ACTIONS(166),
    [sym_symbol] = ACTIONS(9),
    [sym_command] = ACTIONS(166),
    [sym_slash] = ACTIONS(11),
    [sym_dot] = ACTIONS(13),
    [sym_dotdot] = ACTIONS(13),
    [anon_sym_CARET] = ACTIONS(15),
    [anon_sym_LPAREN] = ACTIONS(17),
    [anon_sym_LBRACE] = ACTIONS(19),
    [anon_sym_LBRACK] = ACTIONS(21),
  },
  [25] = {
    [sym__gap] = STATE(18),
    [sym__form] = STATE(21),
    [sym_string] = STATE(21),
    [sym_subpath] = STATE(47),
    [sym_path] = STATE(21),
    [sym_symbind] = STATE(29),
    [sym_meta] = STATE(21),
    [sym_list] = STATE(21),
    [sym_scope] = STATE(21),
    [sym_cons] = STATE(21),
    [aux_sym_subpath_repeat1] = STATE(31),
    [aux_sym_meta_repeat1] = STATE(18),
    [sym__ws] = ACTIONS(168),
    [sym_comment] = ACTIONS(168),
    [sym_int] = ACTIONS(170),
    [sym_keyword] = ACTIONS(170),
    [anon_sym_DQUOTE] = ACTIONS(59),
    [sym_ignore] = ACTIONS(170),
    [sym_null] = ACTIONS(170),
    [sym_bool] = ACTIONS(170),
    [sym_symbol] = ACTIONS(61),
    [sym_command] = ACTIONS(170),
    [sym_slash] = ACTIONS(63),
    [sym_dot] = ACTIONS(65),
    [sym_dotdot] = ACTIONS(65),
    [anon_sym_CARET] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(69),
    [anon_sym_LBRACE] = ACTIONS(73),
    [anon_sym_LBRACK] = ACTIONS(75),
  },
  [26] = {
    [sym__gap] = STATE(51),
    [sym__form] = STATE(36),
    [sym_string] = STATE(36),
    [sym_subpath] = STATE(47),
    [sym_path] = STATE(36),
    [sym_symbind] = STATE(29),
    [sym_meta] = STATE(36),
    [sym_list] = STATE(36),
    [sym_scope] = STATE(36),
    [sym_cons] = STATE(36),
    [aux_sym_subpath_repeat1] = STATE(31),
    [aux_sym_meta_repeat1] = STATE(51),
    [sym__ws] = ACTIONS(148),
    [sym_comment] = ACTIONS(148),
    [sym_int] = ACTIONS(172),
    [sym_keyword] = ACTIONS(172),
    [anon_sym_DQUOTE] = ACTIONS(59),
    [sym_ignore] = ACTIONS(172),
    [sym_null] = ACTIONS(172),
    [sym_bool] = ACTIONS(172),
    [sym_symbol] = ACTIONS(61),
    [sym_command] = ACTIONS(172),
    [sym_slash] = ACTIONS(63),
    [sym_dot] = ACTIONS(65),
    [sym_dotdot] = ACTIONS(65),
    [anon_sym_CARET] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(69),
    [anon_sym_LBRACE] = ACTIONS(73),
    [anon_sym_LBRACK] = ACTIONS(75),
  },
  [27] = {
    [sym__gap] = STATE(24),
    [sym__form] = STATE(56),
    [sym_string] = STATE(56),
    [sym_subpath] = STATE(67),
    [sym_path] = STATE(56),
    [sym_symbind] = STATE(34),
    [sym_meta] = STATE(56),
    [sym_list] = STATE(56),
    [sym_scope] = STATE(56),
    [sym_cons] = STATE(56),
    [aux_sym_subpath_repeat1] = STATE(53),
    [aux_sym_meta_repeat1] = STATE(24),
    [sym__ws] = ACTIONS(174),
    [sym_comment] = ACTIONS(174),
    [sym_int] = ACTIONS(176),
    [sym_keyword] = ACTIONS(176),
    [anon_sym_DQUOTE] = ACTIONS(7),
    [sym_ignore] = ACTIONS(176),
    [sym_null] = ACTIONS(176),
    [sym_bool] = ACTIONS(176),
    [sym_symbol] = ACTIONS(9),
    [sym_command] = ACTIONS(176),
    [sym_slash] = ACTIONS(11),
    [sym_dot] = ACTIONS(13),
    [sym_dotdot] = ACTIONS(13),
    [anon_sym_CARET] = ACTIONS(15),
    [anon_sym_LPAREN] = ACTIONS(17),
    [anon_sym_LBRACE] = ACTIONS(19),
    [anon_sym_LBRACK] = ACTIONS(21),
  },
  [28] = {
    [sym__gap] = STATE(20),
    [sym__form] = STATE(19),
    [sym_string] = STATE(19),
    [sym_subpath] = STATE(47),
    [sym_path] = STATE(19),
    [sym_symbind] = STATE(29),
    [sym_meta] = STATE(19),
    [sym_list] = STATE(19),
    [sym_scope] = STATE(19),
    [sym_cons] = STATE(19),
    [aux_sym_subpath_repeat1] = STATE(31),
    [aux_sym_meta_repeat1] = STATE(20),
    [sym__ws] = ACTIONS(178),
    [sym_comment] = ACTIONS(178),
    [sym_int] = ACTIONS(180),
    [sym_keyword] = ACTIONS(180),
    [anon_sym_DQUOTE] = ACTIONS(59),
    [sym_ignore] = ACTIONS(180),
    [sym_null] = ACTIONS(180),
    [sym_bool] = ACTIONS(180),
    [sym_symbol] = ACTIONS(61),
    [sym_command] = ACTIONS(180),
    [sym_slash] = ACTIONS(63),
    [sym_dot] = ACTIONS(65),
    [sym_dotdot] = ACTIONS(65),
    [anon_sym_CARET] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(69),
    [anon_sym_LBRACE] = ACTIONS(73),
    [anon_sym_LBRACK] = ACTIONS(75),
  },
  [29] = {
    [sym_subpath] = STATE(48),
    [aux_sym_subpath_repeat1] = STATE(31),
    [sym__ws] = ACTIONS(182),
    [sym_comment] = ACTIONS(182),
    [sym_int] = ACTIONS(182),
    [sym_keyword] = ACTIONS(184),
    [anon_sym_DQUOTE] = ACTIONS(182),
    [sym_ignore] = ACTIONS(182),
    [sym_null] = ACTIONS(182),
    [sym_bool] = ACTIONS(182),
    [sym_symbol] = ACTIONS(182),
    [sym_command] = ACTIONS(182),
    [sym_slash] = ACTIONS(63),
    [sym_dot] = ACTIONS(182),
    [sym_dotdot] = ACTIONS(182),
    [anon_sym_CARET] = ACTIONS(182),
    [anon_sym_LPAREN] = ACTIONS(182),
    [anon_sym_RPAREN] = ACTIONS(182),
    [anon_sym_LBRACE] = ACTIONS(182),
    [anon_sym_RBRACE] = ACTIONS(182),
    [anon_sym_LBRACK] = ACTIONS(182),
    [anon_sym_RBRACK] = ACTIONS(182),
  },
  [30] = {
    [aux_sym_subpath_repeat1] = STATE(30),
    [sym__ws] = ACTIONS(186),
    [sym_comment] = ACTIONS(186),
    [sym_int] = ACTIONS(186),
    [sym_keyword] = ACTIONS(186),
    [anon_sym_DQUOTE] = ACTIONS(186),
    [sym_ignore] = ACTIONS(186),
    [sym_null] = ACTIONS(186),
    [sym_bool] = ACTIONS(186),
    [sym_symbol] = ACTIONS(186),
    [sym_command] = ACTIONS(186),
    [sym_slash] = ACTIONS(188),
    [sym_dot] = ACTIONS(186),
    [sym_dotdot] = ACTIONS(186),
    [anon_sym_CARET] = ACTIONS(186),
    [anon_sym_LPAREN] = ACTIONS(186),
    [anon_sym_RPAREN] = ACTIONS(186),
    [anon_sym_LBRACE] = ACTIONS(186),
    [anon_sym_RBRACE] = ACTIONS(186),
    [anon_sym_LBRACK] = ACTIONS(186),
    [anon_sym_RBRACK] = ACTIONS(186),
  },
  [31] = {
    [aux_sym_subpath_repeat1] = STATE(30),
    [sym__ws] = ACTIONS(191),
    [sym_comment] = ACTIONS(191),
    [sym_int] = ACTIONS(191),
    [sym_keyword] = ACTIONS(191),
    [anon_sym_DQUOTE] = ACTIONS(191),
    [sym_ignore] = ACTIONS(191),
    [sym_null] = ACTIONS(191),
    [sym_bool] = ACTIONS(191),
    [sym_symbol] = ACTIONS(191),
    [sym_command] = ACTIONS(191),
    [sym_slash] = ACTIONS(193),
    [sym_dot] = ACTIONS(191),
    [sym_dotdot] = ACTIONS(191),
    [anon_sym_CARET] = ACTIONS(191),
    [anon_sym_LPAREN] = ACTIONS(191),
    [anon_sym_RPAREN] = ACTIONS(191),
    [anon_sym_LBRACE] = ACTIONS(191),
    [anon_sym_RBRACE] = ACTIONS(191),
    [anon_sym_LBRACK] = ACTIONS(191),
    [anon_sym_RBRACK] = ACTIONS(191),
  },
  [32] = {
    [sym__ws] = ACTIONS(195),
    [sym_comment] = ACTIONS(195),
    [sym_int] = ACTIONS(195),
    [sym_keyword] = ACTIONS(195),
    [anon_sym_DQUOTE] = ACTIONS(195),
    [sym_ignore] = ACTIONS(195),
    [sym_null] = ACTIONS(195),
    [sym_bool] = ACTIONS(195),
    [sym_symbol] = ACTIONS(195),
    [sym_command] = ACTIONS(195),
    [sym_slash] = ACTIONS(195),
    [sym_dot] = ACTIONS(195),
    [sym_dotdot] = ACTIONS(195),
    [anon_sym_CARET] = ACTIONS(195),
    [anon_sym_LPAREN] = ACTIONS(195),
    [anon_sym_RPAREN] = ACTIONS(195),
    [anon_sym_LBRACE] = ACTIONS(195),
    [anon_sym_RBRACE] = ACTIONS(195),
    [anon_sym_LBRACK] = ACTIONS(195),
    [anon_sym_RBRACK] = ACTIONS(195),
  },
  [33] = {
    [sym__ws] = ACTIONS(197),
    [sym_comment] = ACTIONS(197),
    [sym_int] = ACTIONS(197),
    [sym_keyword] = ACTIONS(197),
    [anon_sym_DQUOTE] = ACTIONS(197),
    [sym_ignore] = ACTIONS(197),
    [sym_null] = ACTIONS(197),
    [sym_bool] = ACTIONS(197),
    [sym_symbol] = ACTIONS(197),
    [sym_command] = ACTIONS(197),
    [sym_slash] = ACTIONS(197),
    [sym_dot] = ACTIONS(197),
    [sym_dotdot] = ACTIONS(197),
    [anon_sym_CARET] = ACTIONS(197),
    [anon_sym_LPAREN] = ACTIONS(197),
    [anon_sym_RPAREN] = ACTIONS(197),
    [anon_sym_LBRACE] = ACTIONS(197),
    [anon_sym_RBRACE] = ACTIONS(197),
    [anon_sym_LBRACK] = ACTIONS(197),
    [anon_sym_RBRACK] = ACTIONS(197),
  },
  [34] = {
    [sym_subpath] = STATE(62),
    [aux_sym_subpath_repeat1] = STATE(53),
    [ts_builtin_sym_end] = ACTIONS(199),
    [sym__ws] = ACTIONS(182),
    [sym_comment] = ACTIONS(182),
    [sym_int] = ACTIONS(182),
    [sym_keyword] = ACTIONS(201),
    [anon_sym_DQUOTE] = ACTIONS(182),
    [sym_ignore] = ACTIONS(182),
    [sym_null] = ACTIONS(182),
    [sym_bool] = ACTIONS(182),
    [sym_symbol] = ACTIONS(182),
    [sym_command] = ACTIONS(182),
    [sym_slash] = ACTIONS(11),
    [sym_dot] = ACTIONS(182),
    [sym_dotdot] = ACTIONS(182),
    [anon_sym_CARET] = ACTIONS(182),
    [anon_sym_LPAREN] = ACTIONS(182),
    [anon_sym_LBRACE] = ACTIONS(182),
    [anon_sym_LBRACK] = ACTIONS(182),
  },
  [35] = {
    [sym__ws] = ACTIONS(203),
    [sym_comment] = ACTIONS(203),
    [sym_int] = ACTIONS(203),
    [sym_keyword] = ACTIONS(203),
    [anon_sym_DQUOTE] = ACTIONS(203),
    [sym_ignore] = ACTIONS(203),
    [sym_null] = ACTIONS(203),
    [sym_bool] = ACTIONS(203),
    [sym_symbol] = ACTIONS(203),
    [sym_command] = ACTIONS(203),
    [sym_slash] = ACTIONS(203),
    [sym_dot] = ACTIONS(203),
    [sym_dotdot] = ACTIONS(203),
    [anon_sym_CARET] = ACTIONS(203),
    [anon_sym_LPAREN] = ACTIONS(203),
    [anon_sym_RPAREN] = ACTIONS(203),
    [anon_sym_LBRACE] = ACTIONS(203),
    [anon_sym_RBRACE] = ACTIONS(203),
    [anon_sym_LBRACK] = ACTIONS(203),
    [anon_sym_RBRACK] = ACTIONS(203),
  },
  [36] = {
    [sym__ws] = ACTIONS(205),
    [sym_comment] = ACTIONS(205),
    [sym_int] = ACTIONS(205),
    [sym_keyword] = ACTIONS(205),
    [anon_sym_DQUOTE] = ACTIONS(205),
    [sym_ignore] = ACTIONS(205),
    [sym_null] = ACTIONS(205),
    [sym_bool] = ACTIONS(205),
    [sym_symbol] = ACTIONS(205),
    [sym_command] = ACTIONS(205),
    [sym_slash] = ACTIONS(205),
    [sym_dot] = ACTIONS(205),
    [sym_dotdot] = ACTIONS(205),
    [anon_sym_CARET] = ACTIONS(205),
    [anon_sym_LPAREN] = ACTIONS(205),
    [anon_sym_RPAREN] = ACTIONS(205),
    [anon_sym_LBRACE] = ACTIONS(205),
    [anon_sym_RBRACE] = ACTIONS(205),
    [anon_sym_LBRACK] = ACTIONS(205),
    [anon_sym_RBRACK] = ACTIONS(205),
  },
  [37] = {
    [sym__ws] = ACTIONS(207),
    [sym_comment] = ACTIONS(207),
    [sym_int] = ACTIONS(207),
    [sym_keyword] = ACTIONS(207),
    [anon_sym_DQUOTE] = ACTIONS(207),
    [sym_ignore] = ACTIONS(207),
    [sym_null] = ACTIONS(207),
    [sym_bool] = ACTIONS(207),
    [sym_symbol] = ACTIONS(207),
    [sym_command] = ACTIONS(207),
    [sym_slash] = ACTIONS(207),
    [sym_dot] = ACTIONS(207),
    [sym_dotdot] = ACTIONS(207),
    [anon_sym_CARET] = ACTIONS(207),
    [anon_sym_LPAREN] = ACTIONS(207),
    [anon_sym_RPAREN] = ACTIONS(207),
    [anon_sym_LBRACE] = ACTIONS(207),
    [anon_sym_RBRACE] = ACTIONS(207),
    [anon_sym_LBRACK] = ACTIONS(207),
    [anon_sym_RBRACK] = ACTIONS(207),
  },
  [38] = {
    [sym__ws] = ACTIONS(209),
    [sym_comment] = ACTIONS(209),
    [sym_int] = ACTIONS(209),
    [sym_keyword] = ACTIONS(209),
    [anon_sym_DQUOTE] = ACTIONS(209),
    [sym_ignore] = ACTIONS(209),
    [sym_null] = ACTIONS(209),
    [sym_bool] = ACTIONS(209),
    [sym_symbol] = ACTIONS(209),
    [sym_command] = ACTIONS(209),
    [sym_slash] = ACTIONS(209),
    [sym_dot] = ACTIONS(209),
    [sym_dotdot] = ACTIONS(209),
    [anon_sym_CARET] = ACTIONS(209),
    [anon_sym_LPAREN] = ACTIONS(209),
    [anon_sym_RPAREN] = ACTIONS(209),
    [anon_sym_LBRACE] = ACTIONS(209),
    [anon_sym_RBRACE] = ACTIONS(209),
    [anon_sym_LBRACK] = ACTIONS(209),
    [anon_sym_RBRACK] = ACTIONS(209),
  },
  [39] = {
    [sym__ws] = ACTIONS(211),
    [sym_comment] = ACTIONS(211),
    [sym_int] = ACTIONS(211),
    [sym_keyword] = ACTIONS(211),
    [anon_sym_DQUOTE] = ACTIONS(211),
    [sym_ignore] = ACTIONS(211),
    [sym_null] = ACTIONS(211),
    [sym_bool] = ACTIONS(211),
    [sym_symbol] = ACTIONS(211),
    [sym_command] = ACTIONS(211),
    [sym_slash] = ACTIONS(211),
    [sym_dot] = ACTIONS(211),
    [sym_dotdot] = ACTIONS(211),
    [anon_sym_CARET] = ACTIONS(211),
    [anon_sym_LPAREN] = ACTIONS(211),
    [anon_sym_RPAREN] = ACTIONS(211),
    [anon_sym_LBRACE] = ACTIONS(211),
    [anon_sym_RBRACE] = ACTIONS(211),
    [anon_sym_LBRACK] = ACTIONS(211),
    [anon_sym_RBRACK] = ACTIONS(211),
  },
  [40] = {
    [sym__ws] = ACTIONS(213),
    [sym_comment] = ACTIONS(213),
    [sym_int] = ACTIONS(213),
    [sym_keyword] = ACTIONS(213),
    [anon_sym_DQUOTE] = ACTIONS(213),
    [sym_ignore] = ACTIONS(213),
    [sym_null] = ACTIONS(213),
    [sym_bool] = ACTIONS(213),
    [sym_symbol] = ACTIONS(213),
    [sym_command] = ACTIONS(213),
    [sym_slash] = ACTIONS(213),
    [sym_dot] = ACTIONS(213),
    [sym_dotdot] = ACTIONS(213),
    [anon_sym_CARET] = ACTIONS(213),
    [anon_sym_LPAREN] = ACTIONS(213),
    [anon_sym_RPAREN] = ACTIONS(213),
    [anon_sym_LBRACE] = ACTIONS(213),
    [anon_sym_RBRACE] = ACTIONS(213),
    [anon_sym_LBRACK] = ACTIONS(213),
    [anon_sym_RBRACK] = ACTIONS(213),
  },
  [41] = {
    [sym__ws] = ACTIONS(215),
    [sym_comment] = ACTIONS(215),
    [sym_int] = ACTIONS(215),
    [sym_keyword] = ACTIONS(215),
    [anon_sym_DQUOTE] = ACTIONS(215),
    [sym_ignore] = ACTIONS(215),
    [sym_null] = ACTIONS(215),
    [sym_bool] = ACTIONS(215),
    [sym_symbol] = ACTIONS(217),
    [sym_command] = ACTIONS(215),
    [sym_slash] = ACTIONS(215),
    [sym_dot] = ACTIONS(215),
    [sym_dotdot] = ACTIONS(215),
    [anon_sym_CARET] = ACTIONS(215),
    [anon_sym_LPAREN] = ACTIONS(215),
    [anon_sym_RPAREN] = ACTIONS(215),
    [anon_sym_LBRACE] = ACTIONS(215),
    [anon_sym_RBRACE] = ACTIONS(215),
    [anon_sym_LBRACK] = ACTIONS(215),
    [anon_sym_RBRACK] = ACTIONS(215),
  },
  [42] = {
    [sym__ws] = ACTIONS(219),
    [sym_comment] = ACTIONS(219),
    [sym_int] = ACTIONS(219),
    [sym_keyword] = ACTIONS(219),
    [anon_sym_DQUOTE] = ACTIONS(219),
    [sym_ignore] = ACTIONS(219),
    [sym_null] = ACTIONS(219),
    [sym_bool] = ACTIONS(219),
    [sym_symbol] = ACTIONS(219),
    [sym_command] = ACTIONS(219),
    [sym_slash] = ACTIONS(219),
    [sym_dot] = ACTIONS(219),
    [sym_dotdot] = ACTIONS(219),
    [anon_sym_CARET] = ACTIONS(219),
    [anon_sym_LPAREN] = ACTIONS(219),
    [anon_sym_RPAREN] = ACTIONS(219),
    [anon_sym_LBRACE] = ACTIONS(219),
    [anon_sym_RBRACE] = ACTIONS(219),
    [anon_sym_LBRACK] = ACTIONS(219),
    [anon_sym_RBRACK] = ACTIONS(219),
  },
  [43] = {
    [sym__ws] = ACTIONS(221),
    [sym_comment] = ACTIONS(221),
    [sym_int] = ACTIONS(221),
    [sym_keyword] = ACTIONS(221),
    [anon_sym_DQUOTE] = ACTIONS(221),
    [sym_ignore] = ACTIONS(221),
    [sym_null] = ACTIONS(221),
    [sym_bool] = ACTIONS(221),
    [sym_symbol] = ACTIONS(221),
    [sym_command] = ACTIONS(221),
    [sym_slash] = ACTIONS(221),
    [sym_dot] = ACTIONS(221),
    [sym_dotdot] = ACTIONS(221),
    [anon_sym_CARET] = ACTIONS(221),
    [anon_sym_LPAREN] = ACTIONS(221),
    [anon_sym_RPAREN] = ACTIONS(221),
    [anon_sym_LBRACE] = ACTIONS(221),
    [anon_sym_RBRACE] = ACTIONS(221),
    [anon_sym_LBRACK] = ACTIONS(221),
    [anon_sym_RBRACK] = ACTIONS(221),
  },
  [44] = {
    [sym__ws] = ACTIONS(223),
    [sym_comment] = ACTIONS(223),
    [sym_int] = ACTIONS(223),
    [sym_keyword] = ACTIONS(223),
    [anon_sym_DQUOTE] = ACTIONS(223),
    [sym_ignore] = ACTIONS(223),
    [sym_null] = ACTIONS(223),
    [sym_bool] = ACTIONS(223),
    [sym_symbol] = ACTIONS(223),
    [sym_command] = ACTIONS(223),
    [sym_slash] = ACTIONS(223),
    [sym_dot] = ACTIONS(223),
    [sym_dotdot] = ACTIONS(223),
    [anon_sym_CARET] = ACTIONS(223),
    [anon_sym_LPAREN] = ACTIONS(223),
    [anon_sym_RPAREN] = ACTIONS(223),
    [anon_sym_LBRACE] = ACTIONS(223),
    [anon_sym_RBRACE] = ACTIONS(223),
    [anon_sym_LBRACK] = ACTIONS(223),
    [anon_sym_RBRACK] = ACTIONS(223),
  },
  [45] = {
    [sym__ws] = ACTIONS(225),
    [sym_comment] = ACTIONS(225),
    [sym_int] = ACTIONS(225),
    [sym_keyword] = ACTIONS(225),
    [anon_sym_DQUOTE] = ACTIONS(225),
    [sym_ignore] = ACTIONS(225),
    [sym_null] = ACTIONS(225),
    [sym_bool] = ACTIONS(225),
    [sym_symbol] = ACTIONS(225),
    [sym_command] = ACTIONS(225),
    [sym_slash] = ACTIONS(225),
    [sym_dot] = ACTIONS(225),
    [sym_dotdot] = ACTIONS(225),
    [anon_sym_CARET] = ACTIONS(225),
    [anon_sym_LPAREN] = ACTIONS(225),
    [anon_sym_RPAREN] = ACTIONS(225),
    [anon_sym_LBRACE] = ACTIONS(225),
    [anon_sym_RBRACE] = ACTIONS(225),
    [anon_sym_LBRACK] = ACTIONS(225),
    [anon_sym_RBRACK] = ACTIONS(225),
  },
  [46] = {
    [sym__ws] = ACTIONS(186),
    [sym_comment] = ACTIONS(186),
    [sym_int] = ACTIONS(186),
    [sym_keyword] = ACTIONS(186),
    [anon_sym_DQUOTE] = ACTIONS(186),
    [sym_ignore] = ACTIONS(186),
    [sym_null] = ACTIONS(186),
    [sym_bool] = ACTIONS(186),
    [sym_symbol] = ACTIONS(186),
    [sym_command] = ACTIONS(186),
    [sym_slash] = ACTIONS(186),
    [sym_dot] = ACTIONS(186),
    [sym_dotdot] = ACTIONS(186),
    [anon_sym_CARET] = ACTIONS(186),
    [anon_sym_LPAREN] = ACTIONS(186),
    [anon_sym_RPAREN] = ACTIONS(186),
    [anon_sym_LBRACE] = ACTIONS(186),
    [anon_sym_RBRACE] = ACTIONS(186),
    [anon_sym_LBRACK] = ACTIONS(186),
    [anon_sym_RBRACK] = ACTIONS(186),
  },
  [47] = {
    [sym__ws] = ACTIONS(227),
    [sym_comment] = ACTIONS(227),
    [sym_int] = ACTIONS(227),
    [sym_keyword] = ACTIONS(227),
    [anon_sym_DQUOTE] = ACTIONS(227),
    [sym_ignore] = ACTIONS(227),
    [sym_null] = ACTIONS(227),
    [sym_bool] = ACTIONS(227),
    [sym_symbol] = ACTIONS(227),
    [sym_command] = ACTIONS(227),
    [sym_slash] = ACTIONS(227),
    [sym_dot] = ACTIONS(227),
    [sym_dotdot] = ACTIONS(227),
    [anon_sym_CARET] = ACTIONS(227),
    [anon_sym_LPAREN] = ACTIONS(227),
    [anon_sym_RPAREN] = ACTIONS(227),
    [anon_sym_LBRACE] = ACTIONS(227),
    [anon_sym_RBRACE] = ACTIONS(227),
    [anon_sym_LBRACK] = ACTIONS(227),
    [anon_sym_RBRACK] = ACTIONS(227),
  },
  [48] = {
    [sym__ws] = ACTIONS(229),
    [sym_comment] = ACTIONS(229),
    [sym_int] = ACTIONS(229),
    [sym_keyword] = ACTIONS(229),
    [anon_sym_DQUOTE] = ACTIONS(229),
    [sym_ignore] = ACTIONS(229),
    [sym_null] = ACTIONS(229),
    [sym_bool] = ACTIONS(229),
    [sym_symbol] = ACTIONS(229),
    [sym_command] = ACTIONS(229),
    [sym_slash] = ACTIONS(229),
    [sym_dot] = ACTIONS(229),
    [sym_dotdot] = ACTIONS(229),
    [anon_sym_CARET] = ACTIONS(229),
    [anon_sym_LPAREN] = ACTIONS(229),
    [anon_sym_RPAREN] = ACTIONS(229),
    [anon_sym_LBRACE] = ACTIONS(229),
    [anon_sym_RBRACE] = ACTIONS(229),
    [anon_sym_LBRACK] = ACTIONS(229),
    [anon_sym_RBRACK] = ACTIONS(229),
  },
  [49] = {
    [sym__ws] = ACTIONS(231),
    [sym_comment] = ACTIONS(231),
    [sym_int] = ACTIONS(231),
    [sym_keyword] = ACTIONS(231),
    [anon_sym_DQUOTE] = ACTIONS(231),
    [sym_ignore] = ACTIONS(231),
    [sym_null] = ACTIONS(231),
    [sym_bool] = ACTIONS(231),
    [sym_symbol] = ACTIONS(231),
    [sym_command] = ACTIONS(231),
    [sym_slash] = ACTIONS(231),
    [sym_dot] = ACTIONS(231),
    [sym_dotdot] = ACTIONS(231),
    [anon_sym_CARET] = ACTIONS(231),
    [anon_sym_LPAREN] = ACTIONS(231),
    [anon_sym_RPAREN] = ACTIONS(231),
    [anon_sym_LBRACE] = ACTIONS(231),
    [anon_sym_RBRACE] = ACTIONS(231),
    [anon_sym_LBRACK] = ACTIONS(231),
    [anon_sym_RBRACK] = ACTIONS(231),
  },
  [50] = {
    [sym__ws] = ACTIONS(233),
    [sym_comment] = ACTIONS(233),
    [sym_int] = ACTIONS(233),
    [sym_keyword] = ACTIONS(233),
    [anon_sym_DQUOTE] = ACTIONS(233),
    [sym_ignore] = ACTIONS(233),
    [sym_null] = ACTIONS(233),
    [sym_bool] = ACTIONS(233),
    [sym_symbol] = ACTIONS(233),
    [sym_command] = ACTIONS(233),
    [sym_slash] = ACTIONS(233),
    [sym_dot] = ACTIONS(233),
    [sym_dotdot] = ACTIONS(233),
    [anon_sym_CARET] = ACTIONS(233),
    [anon_sym_LPAREN] = ACTIONS(233),
    [anon_sym_RPAREN] = ACTIONS(233),
    [anon_sym_LBRACE] = ACTIONS(233),
    [anon_sym_RBRACE] = ACTIONS(233),
    [anon_sym_LBRACK] = ACTIONS(233),
    [anon_sym_RBRACK] = ACTIONS(233),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 3,
    ACTIONS(235), 2,
      sym__ws,
      sym_comment,
    STATE(51), 2,
      sym__gap,
      aux_sym_meta_repeat1,
    ACTIONS(238), 15,
      sym_int,
      sym_keyword,
      anon_sym_DQUOTE,
      sym_ignore,
      sym_null,
      sym_bool,
      sym_symbol,
      sym_command,
      sym_slash,
      sym_dot,
      sym_dotdot,
      anon_sym_CARET,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
  [26] = 4,
    ACTIONS(240), 1,
      ts_builtin_sym_end,
    ACTIONS(242), 1,
      sym_slash,
    STATE(52), 1,
      aux_sym_subpath_repeat1,
    ACTIONS(186), 16,
      sym__ws,
      sym_comment,
      sym_int,
      sym_keyword,
      anon_sym_DQUOTE,
      sym_ignore,
      sym_null,
      sym_bool,
      sym_symbol,
      sym_command,
      sym_dot,
      sym_dotdot,
      anon_sym_CARET,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
  [54] = 4,
    ACTIONS(245), 1,
      ts_builtin_sym_end,
    ACTIONS(247), 1,
      sym_slash,
    STATE(52), 1,
      aux_sym_subpath_repeat1,
    ACTIONS(191), 16,
      sym__ws,
      sym_comment,
      sym_int,
      sym_keyword,
      anon_sym_DQUOTE,
      sym_ignore,
      sym_null,
      sym_bool,
      sym_symbol,
      sym_command,
      sym_dot,
      sym_dotdot,
      anon_sym_CARET,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
  [82] = 2,
    ACTIONS(249), 1,
      ts_builtin_sym_end,
    ACTIONS(213), 17,
      sym__ws,
      sym_comment,
      sym_int,
      sym_keyword,
      anon_sym_DQUOTE,
      sym_ignore,
      sym_null,
      sym_bool,
      sym_symbol,
      sym_command,
      sym_slash,
      sym_dot,
      sym_dotdot,
      anon_sym_CARET,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
  [105] = 2,
    ACTIONS(251), 1,
      ts_builtin_sym_end,
    ACTIONS(195), 17,
      sym__ws,
      sym_comment,
      sym_int,
      sym_keyword,
      anon_sym_DQUOTE,
      sym_ignore,
      sym_null,
      sym_bool,
      sym_symbol,
      sym_command,
      sym_slash,
      sym_dot,
      sym_dotdot,
      anon_sym_CARET,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
  [128] = 2,
    ACTIONS(253), 1,
      ts_builtin_sym_end,
    ACTIONS(203), 17,
      sym__ws,
      sym_comment,
      sym_int,
      sym_keyword,
      anon_sym_DQUOTE,
      sym_ignore,
      sym_null,
      sym_bool,
      sym_symbol,
      sym_command,
      sym_slash,
      sym_dot,
      sym_dotdot,
      anon_sym_CARET,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
  [151] = 2,
    ACTIONS(255), 1,
      ts_builtin_sym_end,
    ACTIONS(205), 17,
      sym__ws,
      sym_comment,
      sym_int,
      sym_keyword,
      anon_sym_DQUOTE,
      sym_ignore,
      sym_null,
      sym_bool,
      sym_symbol,
      sym_command,
      sym_slash,
      sym_dot,
      sym_dotdot,
      anon_sym_CARET,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
  [174] = 2,
    ACTIONS(257), 1,
      ts_builtin_sym_end,
    ACTIONS(207), 17,
      sym__ws,
      sym_comment,
      sym_int,
      sym_keyword,
      anon_sym_DQUOTE,
      sym_ignore,
      sym_null,
      sym_bool,
      sym_symbol,
      sym_command,
      sym_slash,
      sym_dot,
      sym_dotdot,
      anon_sym_CARET,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
  [197] = 2,
    ACTIONS(259), 1,
      ts_builtin_sym_end,
    ACTIONS(223), 17,
      sym__ws,
      sym_comment,
      sym_int,
      sym_keyword,
      anon_sym_DQUOTE,
      sym_ignore,
      sym_null,
      sym_bool,
      sym_symbol,
      sym_command,
      sym_slash,
      sym_dot,
      sym_dotdot,
      anon_sym_CARET,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
  [220] = 2,
    ACTIONS(240), 1,
      ts_builtin_sym_end,
    ACTIONS(186), 17,
      sym__ws,
      sym_comment,
      sym_int,
      sym_keyword,
      anon_sym_DQUOTE,
      sym_ignore,
      sym_null,
      sym_bool,
      sym_symbol,
      sym_command,
      sym_slash,
      sym_dot,
      sym_dotdot,
      anon_sym_CARET,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
  [243] = 2,
    ACTIONS(261), 1,
      ts_builtin_sym_end,
    ACTIONS(209), 17,
      sym__ws,
      sym_comment,
      sym_int,
      sym_keyword,
      anon_sym_DQUOTE,
      sym_ignore,
      sym_null,
      sym_bool,
      sym_symbol,
      sym_command,
      sym_slash,
      sym_dot,
      sym_dotdot,
      anon_sym_CARET,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
  [266] = 2,
    ACTIONS(263), 1,
      ts_builtin_sym_end,
    ACTIONS(229), 17,
      sym__ws,
      sym_comment,
      sym_int,
      sym_keyword,
      anon_sym_DQUOTE,
      sym_ignore,
      sym_null,
      sym_bool,
      sym_symbol,
      sym_command,
      sym_slash,
      sym_dot,
      sym_dotdot,
      anon_sym_CARET,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
  [289] = 2,
    ACTIONS(265), 1,
      ts_builtin_sym_end,
    ACTIONS(233), 17,
      sym__ws,
      sym_comment,
      sym_int,
      sym_keyword,
      anon_sym_DQUOTE,
      sym_ignore,
      sym_null,
      sym_bool,
      sym_symbol,
      sym_command,
      sym_slash,
      sym_dot,
      sym_dotdot,
      anon_sym_CARET,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
  [312] = 2,
    ACTIONS(267), 1,
      ts_builtin_sym_end,
    ACTIONS(211), 17,
      sym__ws,
      sym_comment,
      sym_int,
      sym_keyword,
      anon_sym_DQUOTE,
      sym_ignore,
      sym_null,
      sym_bool,
      sym_symbol,
      sym_command,
      sym_slash,
      sym_dot,
      sym_dotdot,
      anon_sym_CARET,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
  [335] = 2,
    ACTIONS(269), 1,
      ts_builtin_sym_end,
    ACTIONS(221), 17,
      sym__ws,
      sym_comment,
      sym_int,
      sym_keyword,
      anon_sym_DQUOTE,
      sym_ignore,
      sym_null,
      sym_bool,
      sym_symbol,
      sym_command,
      sym_slash,
      sym_dot,
      sym_dotdot,
      anon_sym_CARET,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
  [358] = 2,
    ACTIONS(271), 1,
      ts_builtin_sym_end,
    ACTIONS(197), 17,
      sym__ws,
      sym_comment,
      sym_int,
      sym_keyword,
      anon_sym_DQUOTE,
      sym_ignore,
      sym_null,
      sym_bool,
      sym_symbol,
      sym_command,
      sym_slash,
      sym_dot,
      sym_dotdot,
      anon_sym_CARET,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
  [381] = 2,
    ACTIONS(273), 1,
      ts_builtin_sym_end,
    ACTIONS(227), 17,
      sym__ws,
      sym_comment,
      sym_int,
      sym_keyword,
      anon_sym_DQUOTE,
      sym_ignore,
      sym_null,
      sym_bool,
      sym_symbol,
      sym_command,
      sym_slash,
      sym_dot,
      sym_dotdot,
      anon_sym_CARET,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
  [404] = 2,
    ACTIONS(275), 1,
      ts_builtin_sym_end,
    ACTIONS(219), 17,
      sym__ws,
      sym_comment,
      sym_int,
      sym_keyword,
      anon_sym_DQUOTE,
      sym_ignore,
      sym_null,
      sym_bool,
      sym_symbol,
      sym_command,
      sym_slash,
      sym_dot,
      sym_dotdot,
      anon_sym_CARET,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
  [427] = 3,
    ACTIONS(277), 1,
      ts_builtin_sym_end,
    ACTIONS(279), 1,
      sym_symbol,
    ACTIONS(215), 16,
      sym__ws,
      sym_comment,
      sym_int,
      sym_keyword,
      anon_sym_DQUOTE,
      sym_ignore,
      sym_null,
      sym_bool,
      sym_command,
      sym_slash,
      sym_dot,
      sym_dotdot,
      anon_sym_CARET,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
  [452] = 2,
    ACTIONS(281), 1,
      ts_builtin_sym_end,
    ACTIONS(231), 17,
      sym__ws,
      sym_comment,
      sym_int,
      sym_keyword,
      anon_sym_DQUOTE,
      sym_ignore,
      sym_null,
      sym_bool,
      sym_symbol,
      sym_command,
      sym_slash,
      sym_dot,
      sym_dotdot,
      anon_sym_CARET,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
  [475] = 4,
    ACTIONS(283), 1,
      sym_string_escape,
    ACTIONS(285), 1,
      anon_sym_DQUOTE,
    ACTIONS(287), 1,
      aux_sym_string_token1,
    STATE(74), 1,
      aux_sym_string_repeat1,
  [488] = 4,
    ACTIONS(283), 1,
      sym_string_escape,
    ACTIONS(289), 1,
      anon_sym_DQUOTE,
    ACTIONS(291), 1,
      aux_sym_string_token1,
    STATE(75), 1,
      aux_sym_string_repeat1,
  [501] = 4,
    ACTIONS(283), 1,
      sym_string_escape,
    ACTIONS(293), 1,
      anon_sym_DQUOTE,
    ACTIONS(295), 1,
      aux_sym_string_token1,
    STATE(72), 1,
      aux_sym_string_repeat1,
  [514] = 4,
    ACTIONS(283), 1,
      sym_string_escape,
    ACTIONS(291), 1,
      aux_sym_string_token1,
    ACTIONS(297), 1,
      anon_sym_DQUOTE,
    STATE(75), 1,
      aux_sym_string_repeat1,
  [527] = 4,
    ACTIONS(299), 1,
      sym_string_escape,
    ACTIONS(302), 1,
      anon_sym_DQUOTE,
    ACTIONS(304), 1,
      aux_sym_string_token1,
    STATE(75), 1,
      aux_sym_string_repeat1,
  [540] = 3,
    ACTIONS(307), 1,
      sym_slash,
    STATE(31), 1,
      aux_sym_subpath_repeat1,
    STATE(48), 1,
      sym_subpath,
  [550] = 2,
    ACTIONS(311), 1,
      aux_sym_string_token1,
    ACTIONS(309), 2,
      sym_string_escape,
      anon_sym_DQUOTE,
  [558] = 3,
    ACTIONS(313), 1,
      sym_slash,
    STATE(53), 1,
      aux_sym_subpath_repeat1,
    STATE(62), 1,
      sym_subpath,
  [568] = 1,
    ACTIONS(315), 1,
      sym_symbol,
  [572] = 1,
    ACTIONS(317), 1,
      ts_builtin_sym_end,
  [576] = 1,
    ACTIONS(319), 1,
      sym_symbol,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(51)] = 0,
  [SMALL_STATE(52)] = 26,
  [SMALL_STATE(53)] = 54,
  [SMALL_STATE(54)] = 82,
  [SMALL_STATE(55)] = 105,
  [SMALL_STATE(56)] = 128,
  [SMALL_STATE(57)] = 151,
  [SMALL_STATE(58)] = 174,
  [SMALL_STATE(59)] = 197,
  [SMALL_STATE(60)] = 220,
  [SMALL_STATE(61)] = 243,
  [SMALL_STATE(62)] = 266,
  [SMALL_STATE(63)] = 289,
  [SMALL_STATE(64)] = 312,
  [SMALL_STATE(65)] = 335,
  [SMALL_STATE(66)] = 358,
  [SMALL_STATE(67)] = 381,
  [SMALL_STATE(68)] = 404,
  [SMALL_STATE(69)] = 427,
  [SMALL_STATE(70)] = 452,
  [SMALL_STATE(71)] = 475,
  [SMALL_STATE(72)] = 488,
  [SMALL_STATE(73)] = 501,
  [SMALL_STATE(74)] = 514,
  [SMALL_STATE(75)] = 527,
  [SMALL_STATE(76)] = 540,
  [SMALL_STATE(77)] = 550,
  [SMALL_STATE(78)] = 558,
  [SMALL_STATE(79)] = 568,
  [SMALL_STATE(80)] = 572,
  [SMALL_STATE(81)] = 576,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source, 0),
  [5] = {.entry = {.count = 1, .reusable = false}}, SHIFT(12),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(73),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(34),
  [11] = {.entry = {.count = 1, .reusable = false}}, SHIFT(81),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(78),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(28),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(4),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(8),
  [21] = {.entry = {.count = 1, .reusable = false}}, SHIFT(9),
  [23] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_list_repeat1, 2, .production_id = 11), SHIFT_REPEAT(2),
  [26] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_list_repeat1, 2, .production_id = 11), SHIFT_REPEAT(45),
  [29] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_list_repeat1, 2, .production_id = 11), SHIFT_REPEAT(71),
  [32] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_list_repeat1, 2, .production_id = 11), SHIFT_REPEAT(29),
  [35] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_list_repeat1, 2, .production_id = 11), SHIFT_REPEAT(79),
  [38] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_list_repeat1, 2, .production_id = 11), SHIFT_REPEAT(76),
  [41] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_list_repeat1, 2, .production_id = 11), SHIFT_REPEAT(25),
  [44] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_list_repeat1, 2, .production_id = 11), SHIFT_REPEAT(13),
  [47] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_list_repeat1, 2, .production_id = 11),
  [49] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_list_repeat1, 2, .production_id = 11), SHIFT_REPEAT(11),
  [52] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_list_repeat1, 2, .production_id = 11), SHIFT_REPEAT(10),
  [55] = {.entry = {.count = 1, .reusable = false}}, SHIFT(2),
  [57] = {.entry = {.count = 1, .reusable = false}}, SHIFT(45),
  [59] = {.entry = {.count = 1, .reusable = false}}, SHIFT(71),
  [61] = {.entry = {.count = 1, .reusable = false}}, SHIFT(29),
  [63] = {.entry = {.count = 1, .reusable = false}}, SHIFT(79),
  [65] = {.entry = {.count = 1, .reusable = false}}, SHIFT(76),
  [67] = {.entry = {.count = 1, .reusable = false}}, SHIFT(25),
  [69] = {.entry = {.count = 1, .reusable = false}}, SHIFT(13),
  [71] = {.entry = {.count = 1, .reusable = false}}, SHIFT(64),
  [73] = {.entry = {.count = 1, .reusable = false}}, SHIFT(11),
  [75] = {.entry = {.count = 1, .reusable = false}}, SHIFT(10),
  [77] = {.entry = {.count = 1, .reusable = false}}, SHIFT(3),
  [79] = {.entry = {.count = 1, .reusable = false}}, SHIFT(59),
  [81] = {.entry = {.count = 1, .reusable = false}}, SHIFT(38),
  [83] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_repeat1, 2),
  [85] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat1, 2), SHIFT_REPEAT(6),
  [88] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat1, 2), SHIFT_REPEAT(73),
  [91] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat1, 2), SHIFT_REPEAT(34),
  [94] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat1, 2), SHIFT_REPEAT(81),
  [97] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat1, 2), SHIFT_REPEAT(78),
  [100] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat1, 2), SHIFT_REPEAT(28),
  [103] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat1, 2), SHIFT_REPEAT(4),
  [106] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat1, 2), SHIFT_REPEAT(8),
  [109] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat1, 2), SHIFT_REPEAT(9),
  [112] = {.entry = {.count = 1, .reusable = false}}, SHIFT(58),
  [114] = {.entry = {.count = 1, .reusable = false}}, SHIFT(14),
  [116] = {.entry = {.count = 1, .reusable = false}}, SHIFT(65),
  [118] = {.entry = {.count = 1, .reusable = false}}, SHIFT(7),
  [120] = {.entry = {.count = 1, .reusable = false}}, SHIFT(68),
  [122] = {.entry = {.count = 1, .reusable = false}}, SHIFT(16),
  [124] = {.entry = {.count = 1, .reusable = false}}, SHIFT(42),
  [126] = {.entry = {.count = 1, .reusable = false}}, SHIFT(5),
  [128] = {.entry = {.count = 1, .reusable = false}}, SHIFT(43),
  [130] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source, 1),
  [132] = {.entry = {.count = 1, .reusable = false}}, SHIFT(6),
  [134] = {.entry = {.count = 1, .reusable = false}}, SHIFT(15),
  [136] = {.entry = {.count = 1, .reusable = false}}, SHIFT(44),
  [138] = {.entry = {.count = 1, .reusable = false}}, SHIFT(61),
  [140] = {.entry = {.count = 1, .reusable = false}}, SHIFT(39),
  [142] = {.entry = {.count = 1, .reusable = false}}, SHIFT(37),
  [144] = {.entry = {.count = 1, .reusable = false}}, SHIFT(23),
  [146] = {.entry = {.count = 1, .reusable = false}}, SHIFT(35),
  [148] = {.entry = {.count = 1, .reusable = false}}, SHIFT(51),
  [150] = {.entry = {.count = 1, .reusable = false}}, SHIFT(17),
  [152] = {.entry = {.count = 1, .reusable = false}}, SHIFT(22),
  [154] = {.entry = {.count = 1, .reusable = false}}, SHIFT(54),
  [156] = {.entry = {.count = 1, .reusable = false}}, SHIFT(27),
  [158] = {.entry = {.count = 1, .reusable = false}}, SHIFT(26),
  [160] = {.entry = {.count = 1, .reusable = false}}, SHIFT(40),
  [162] = {.entry = {.count = 1, .reusable = false}}, SHIFT(57),
  [164] = {.entry = {.count = 1, .reusable = false}}, SHIFT(33),
  [166] = {.entry = {.count = 1, .reusable = false}}, SHIFT(66),
  [168] = {.entry = {.count = 1, .reusable = false}}, SHIFT(18),
  [170] = {.entry = {.count = 1, .reusable = false}}, SHIFT(21),
  [172] = {.entry = {.count = 1, .reusable = false}}, SHIFT(36),
  [174] = {.entry = {.count = 1, .reusable = false}}, SHIFT(24),
  [176] = {.entry = {.count = 1, .reusable = false}}, SHIFT(56),
  [178] = {.entry = {.count = 1, .reusable = false}}, SHIFT(20),
  [180] = {.entry = {.count = 1, .reusable = false}}, SHIFT(19),
  [182] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__form, 1),
  [184] = {.entry = {.count = 1, .reusable = false}}, SHIFT(50),
  [186] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_subpath_repeat1, 2),
  [188] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_subpath_repeat1, 2), SHIFT_REPEAT(79),
  [191] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_subpath, 1),
  [193] = {.entry = {.count = 1, .reusable = false}}, SHIFT(41),
  [195] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string, 3, .production_id = 7),
  [197] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_meta, 5, .production_id = 14),
  [199] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__form, 1),
  [201] = {.entry = {.count = 1, .reusable = false}}, SHIFT(63),
  [203] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_meta, 4, .production_id = 13),
  [205] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_meta, 4, .production_id = 12),
  [207] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cons, 3, .production_id = 10),
  [209] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_scope, 3, .production_id = 10),
  [211] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_list, 3, .production_id = 10),
  [213] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_meta, 3, .production_id = 9),
  [215] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_subpath, 2),
  [217] = {.entry = {.count = 1, .reusable = false}}, SHIFT(46),
  [219] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cons, 2, .production_id = 5),
  [221] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_scope, 2, .production_id = 5),
  [223] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_list, 2, .production_id = 5),
  [225] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_list_repeat1, 1, .production_id = 6),
  [227] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_path, 1, .production_id = 1),
  [229] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_path, 2, .production_id = 4),
  [231] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string, 2),
  [233] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_symbind, 2, .production_id = 3),
  [235] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_meta_repeat1, 2), SHIFT_REPEAT(51),
  [238] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_meta_repeat1, 2),
  [240] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_subpath_repeat1, 2),
  [242] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_subpath_repeat1, 2), SHIFT_REPEAT(81),
  [245] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_subpath, 1),
  [247] = {.entry = {.count = 1, .reusable = false}}, SHIFT(69),
  [249] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_meta, 3, .production_id = 9),
  [251] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 3, .production_id = 7),
  [253] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_meta, 4, .production_id = 13),
  [255] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_meta, 4, .production_id = 12),
  [257] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cons, 3, .production_id = 10),
  [259] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list, 2, .production_id = 5),
  [261] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_scope, 3, .production_id = 10),
  [263] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_path, 2, .production_id = 4),
  [265] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_symbind, 2, .production_id = 3),
  [267] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list, 3, .production_id = 10),
  [269] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_scope, 2, .production_id = 5),
  [271] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_meta, 5, .production_id = 14),
  [273] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_path, 1, .production_id = 1),
  [275] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cons, 2, .production_id = 5),
  [277] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_subpath, 2),
  [279] = {.entry = {.count = 1, .reusable = false}}, SHIFT(60),
  [281] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 2),
  [283] = {.entry = {.count = 1, .reusable = false}}, SHIFT(77),
  [285] = {.entry = {.count = 1, .reusable = false}}, SHIFT(49),
  [287] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [289] = {.entry = {.count = 1, .reusable = false}}, SHIFT(55),
  [291] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [293] = {.entry = {.count = 1, .reusable = false}}, SHIFT(70),
  [295] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [297] = {.entry = {.count = 1, .reusable = false}}, SHIFT(32),
  [299] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_repeat1, 2, .production_id = 8), SHIFT_REPEAT(77),
  [302] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_repeat1, 2, .production_id = 8),
  [304] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_string_repeat1, 2, .production_id = 8), SHIFT_REPEAT(75),
  [307] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [309] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_repeat1, 1, .production_id = 2),
  [311] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_string_repeat1, 1, .production_id = 2),
  [313] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [315] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [317] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [319] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_bass(void) {
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
