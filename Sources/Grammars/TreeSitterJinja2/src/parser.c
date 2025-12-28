#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 23
#define LARGE_STATE_COUNT 9
#define SYMBOL_COUNT 65
#define ALIAS_COUNT 0
#define TOKEN_COUNT 53
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 4
#define PRODUCTION_ID_COUNT 1

enum {
  sym_identifier = 1,
  aux_sym__text_token1 = 2,
  aux_sym__not_token1 = 3,
  aux_sym__not_token2 = 4,
  aux_sym__not_token3 = 5,
  aux_sym__not_token4 = 6,
  anon_sym_LBRACE_PERCENT = 7,
  anon_sym_PERCENT_RBRACE = 8,
  anon_sym_LBRACE_LBRACE = 9,
  aux_sym_expression_token1 = 10,
  anon_sym_RBRACE_RBRACE = 11,
  anon_sym_LBRACE_POUND = 12,
  aux_sym_comment_token1 = 13,
  anon_sym_POUND_RBRACE = 14,
  anon_sym_for = 15,
  anon_sym_in = 16,
  anon_sym_endfor = 17,
  anon_sym_if = 18,
  anon_sym_and = 19,
  anon_sym_or = 20,
  anon_sym_endif = 21,
  anon_sym_else = 22,
  anon_sym_elif = 23,
  anon_sym_raw = 24,
  anon_sym_endraw = 25,
  anon_sym_macro = 26,
  anon_sym_endmacro = 27,
  anon_sym_extends = 28,
  anon_sym_block = 29,
  anon_sym_endblock = 30,
  anon_sym_call = 31,
  anon_sym_endcall = 32,
  anon_sym_filter = 33,
  anon_sym_endfilter = 34,
  anon_sym_set = 35,
  anon_sym_endset = 36,
  anon_sym_include = 37,
  anon_sym_import = 38,
  anon_sym_from = 39,
  anon_sym_autoescape = 40,
  anon_sym_endautoescape = 41,
  anon_sym_trans = 42,
  anon_sym_endtrans = 43,
  anon_sym_pluralize = 44,
  anon_sym_with = 45,
  anon_sym_endwith = 46,
  anon_sym_debug = 47,
  anon_sym_do = 48,
  sym_white_space_control = 49,
  sym__white_space = 50,
  sym_operator = 51,
  sym_string = 52,
  sym_source_file = 53,
  sym__text = 54,
  sym__not = 55,
  sym__node = 56,
  sym_statement = 57,
  sym_statement_begin = 58,
  sym_statement_end = 59,
  sym_expression = 60,
  sym_comment = 61,
  sym_keyword = 62,
  aux_sym__inner_text = 63,
  aux_sym_source_file_repeat1 = 64,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_identifier] = "identifier",
  [aux_sym__text_token1] = "_text_token1",
  [aux_sym__not_token1] = "_not_token1",
  [aux_sym__not_token2] = "_not_token2",
  [aux_sym__not_token3] = "_not_token3",
  [aux_sym__not_token4] = "_not_token4",
  [anon_sym_LBRACE_PERCENT] = "{%",
  [anon_sym_PERCENT_RBRACE] = "%}",
  [anon_sym_LBRACE_LBRACE] = "{{",
  [aux_sym_expression_token1] = "expression_token1",
  [anon_sym_RBRACE_RBRACE] = "}}",
  [anon_sym_LBRACE_POUND] = "{#",
  [aux_sym_comment_token1] = "comment_token1",
  [anon_sym_POUND_RBRACE] = "#}",
  [anon_sym_for] = "for",
  [anon_sym_in] = "in",
  [anon_sym_endfor] = "endfor",
  [anon_sym_if] = "if",
  [anon_sym_and] = "and",
  [anon_sym_or] = "or",
  [anon_sym_endif] = "endif",
  [anon_sym_else] = "else",
  [anon_sym_elif] = "elif",
  [anon_sym_raw] = "raw",
  [anon_sym_endraw] = "endraw",
  [anon_sym_macro] = "macro",
  [anon_sym_endmacro] = "endmacro",
  [anon_sym_extends] = "extends",
  [anon_sym_block] = "block",
  [anon_sym_endblock] = "endblock",
  [anon_sym_call] = "call",
  [anon_sym_endcall] = "endcall",
  [anon_sym_filter] = "filter",
  [anon_sym_endfilter] = "endfilter",
  [anon_sym_set] = "set",
  [anon_sym_endset] = "endset",
  [anon_sym_include] = "include",
  [anon_sym_import] = "import",
  [anon_sym_from] = "from",
  [anon_sym_autoescape] = "autoescape",
  [anon_sym_endautoescape] = "endautoescape",
  [anon_sym_trans] = "trans",
  [anon_sym_endtrans] = "endtrans",
  [anon_sym_pluralize] = "pluralize",
  [anon_sym_with] = "with",
  [anon_sym_endwith] = "endwith",
  [anon_sym_debug] = "debug",
  [anon_sym_do] = "do",
  [sym_white_space_control] = "white_space_control",
  [sym__white_space] = "_white_space",
  [sym_operator] = "operator",
  [sym_string] = "string",
  [sym_source_file] = "source_file",
  [sym__text] = "_text",
  [sym__not] = "_not",
  [sym__node] = "_node",
  [sym_statement] = "statement",
  [sym_statement_begin] = "statement_begin",
  [sym_statement_end] = "statement_end",
  [sym_expression] = "expression",
  [sym_comment] = "comment",
  [sym_keyword] = "keyword",
  [aux_sym__inner_text] = "_inner_text",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_identifier] = sym_identifier,
  [aux_sym__text_token1] = aux_sym__text_token1,
  [aux_sym__not_token1] = aux_sym__not_token1,
  [aux_sym__not_token2] = aux_sym__not_token2,
  [aux_sym__not_token3] = aux_sym__not_token3,
  [aux_sym__not_token4] = aux_sym__not_token4,
  [anon_sym_LBRACE_PERCENT] = anon_sym_LBRACE_PERCENT,
  [anon_sym_PERCENT_RBRACE] = anon_sym_PERCENT_RBRACE,
  [anon_sym_LBRACE_LBRACE] = anon_sym_LBRACE_LBRACE,
  [aux_sym_expression_token1] = aux_sym_expression_token1,
  [anon_sym_RBRACE_RBRACE] = anon_sym_RBRACE_RBRACE,
  [anon_sym_LBRACE_POUND] = anon_sym_LBRACE_POUND,
  [aux_sym_comment_token1] = aux_sym_comment_token1,
  [anon_sym_POUND_RBRACE] = anon_sym_POUND_RBRACE,
  [anon_sym_for] = anon_sym_for,
  [anon_sym_in] = anon_sym_in,
  [anon_sym_endfor] = anon_sym_endfor,
  [anon_sym_if] = anon_sym_if,
  [anon_sym_and] = anon_sym_and,
  [anon_sym_or] = anon_sym_or,
  [anon_sym_endif] = anon_sym_endif,
  [anon_sym_else] = anon_sym_else,
  [anon_sym_elif] = anon_sym_elif,
  [anon_sym_raw] = anon_sym_raw,
  [anon_sym_endraw] = anon_sym_endraw,
  [anon_sym_macro] = anon_sym_macro,
  [anon_sym_endmacro] = anon_sym_endmacro,
  [anon_sym_extends] = anon_sym_extends,
  [anon_sym_block] = anon_sym_block,
  [anon_sym_endblock] = anon_sym_endblock,
  [anon_sym_call] = anon_sym_call,
  [anon_sym_endcall] = anon_sym_endcall,
  [anon_sym_filter] = anon_sym_filter,
  [anon_sym_endfilter] = anon_sym_endfilter,
  [anon_sym_set] = anon_sym_set,
  [anon_sym_endset] = anon_sym_endset,
  [anon_sym_include] = anon_sym_include,
  [anon_sym_import] = anon_sym_import,
  [anon_sym_from] = anon_sym_from,
  [anon_sym_autoescape] = anon_sym_autoescape,
  [anon_sym_endautoescape] = anon_sym_endautoescape,
  [anon_sym_trans] = anon_sym_trans,
  [anon_sym_endtrans] = anon_sym_endtrans,
  [anon_sym_pluralize] = anon_sym_pluralize,
  [anon_sym_with] = anon_sym_with,
  [anon_sym_endwith] = anon_sym_endwith,
  [anon_sym_debug] = anon_sym_debug,
  [anon_sym_do] = anon_sym_do,
  [sym_white_space_control] = sym_white_space_control,
  [sym__white_space] = sym__white_space,
  [sym_operator] = sym_operator,
  [sym_string] = sym_string,
  [sym_source_file] = sym_source_file,
  [sym__text] = sym__text,
  [sym__not] = sym__not,
  [sym__node] = sym__node,
  [sym_statement] = sym_statement,
  [sym_statement_begin] = sym_statement_begin,
  [sym_statement_end] = sym_statement_end,
  [sym_expression] = sym_expression,
  [sym_comment] = sym_comment,
  [sym_keyword] = sym_keyword,
  [aux_sym__inner_text] = aux_sym__inner_text,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [aux_sym__text_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__not_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__not_token2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__not_token3] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__not_token4] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_LBRACE_PERCENT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PERCENT_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACE_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_expression_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_RBRACE_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACE_POUND] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_comment_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_POUND_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_for] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_in] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_endfor] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_if] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_and] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_or] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_endif] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_else] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_elif] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_raw] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_endraw] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_macro] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_endmacro] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_extends] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_block] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_endblock] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_call] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_endcall] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_filter] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_endfilter] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_set] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_endset] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_include] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_import] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_from] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_autoescape] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_endautoescape] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_trans] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_endtrans] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_pluralize] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_with] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_endwith] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_debug] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_do] = {
    .visible = true,
    .named = false,
  },
  [sym_white_space_control] = {
    .visible = true,
    .named = true,
  },
  [sym__white_space] = {
    .visible = false,
    .named = true,
  },
  [sym_operator] = {
    .visible = true,
    .named = true,
  },
  [sym_string] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym__text] = {
    .visible = false,
    .named = true,
  },
  [sym__not] = {
    .visible = false,
    .named = true,
  },
  [sym__node] = {
    .visible = false,
    .named = true,
  },
  [sym_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_statement_begin] = {
    .visible = true,
    .named = true,
  },
  [sym_statement_end] = {
    .visible = true,
    .named = true,
  },
  [sym_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_keyword] = {
    .visible = true,
    .named = true,
  },
  [aux_sym__inner_text] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
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
  [6] = 6,
  [7] = 7,
  [8] = 8,
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
};

static inline bool sym_operator_character_set_1(int32_t c) {
  return (c < '0'
    ? (c < '%'
      ? (c < '"'
        ? c == 0
        : c <= '#')
      : (c <= '%' || c == '\''))
    : (c <= '9' || (c < 'a'
      ? (c < '_'
        ? (c >= 'A' && c <= 'Z')
        : c <= '_')
      : (c <= '{' || c == '}'))));
}

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(11);
      if (lookahead == '#') ADVANCE(22);
      if (lookahead == '%') ADVANCE(2);
      if (lookahead == '{') ADVANCE(16);
      if (lookahead == '}') ADVANCE(18);
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(39);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(42);
      if (lookahead != 0) ADVANCE(3);
      END_STATE();
    case 1:
      if (lookahead == '#') ADVANCE(22);
      if (lookahead == '%') ADVANCE(2);
      if (lookahead == '{') ADVANCE(16);
      if (lookahead == '}') ADVANCE(18);
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(39);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(42);
      if (lookahead != 0) ADVANCE(3);
      END_STATE();
    case 2:
      if (lookahead == '#') ADVANCE(23);
      if (lookahead == '}') ADVANCE(29);
      END_STATE();
    case 3:
      if (lookahead == '#') ADVANCE(23);
      if (lookahead == '}') ADVANCE(17);
      END_STATE();
    case 4:
      if (lookahead == '#') ADVANCE(7);
      if (lookahead == '}') ADVANCE(8);
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(38);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(4)
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(43);
      END_STATE();
    case 5:
      if (lookahead == '%') ADVANCE(6);
      if (lookahead == '"' ||
          lookahead == '\'') ADVANCE(9);
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(40);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(41);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(43);
      if (lookahead != 0 &&
          lookahead != '#' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(44);
      END_STATE();
    case 6:
      if (lookahead == '}') ADVANCE(29);
      END_STATE();
    case 7:
      if (lookahead == '}') ADVANCE(37);
      END_STATE();
    case 8:
      if (lookahead == '}') ADVANCE(33);
      END_STATE();
    case 9:
      if (lookahead == '"' ||
          lookahead == '\'') ADVANCE(45);
      if (lookahead != 0) ADVANCE(9);
      END_STATE();
    case 10:
      if (eof) ADVANCE(11);
      if (lookahead == '#') ADVANCE(21);
      if (lookahead == '%') ADVANCE(26);
      if (lookahead == '{') ADVANCE(16);
      if (lookahead == '}') ADVANCE(19);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(13);
      if (lookahead != 0) ADVANCE(12);
      END_STATE();
    case 11:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 12:
      ACCEPT_TOKEN(aux_sym__text_token1);
      if (lookahead == '#') ADVANCE(23);
      if (lookahead == '%') ADVANCE(27);
      if (lookahead == '}') ADVANCE(17);
      if (lookahead != 0 &&
          lookahead != '{') ADVANCE(14);
      END_STATE();
    case 13:
      ACCEPT_TOKEN(aux_sym__text_token1);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(13);
      if (lookahead != 0 &&
          lookahead != '#' &&
          lookahead != '%' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(12);
      END_STATE();
    case 14:
      ACCEPT_TOKEN(aux_sym__text_token1);
      if (lookahead != 0 &&
          lookahead != '#' &&
          lookahead != '%' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(14);
      END_STATE();
    case 15:
      ACCEPT_TOKEN(aux_sym__not_token1);
      END_STATE();
    case 16:
      ACCEPT_TOKEN(aux_sym__not_token1);
      if (lookahead == '#') ADVANCE(34);
      if (lookahead == '%') ADVANCE(28);
      if (lookahead == '{') ADVANCE(30);
      if (lookahead == '}') ADVANCE(15);
      if (lookahead != 0) ADVANCE(15);
      END_STATE();
    case 17:
      ACCEPT_TOKEN(aux_sym__not_token2);
      END_STATE();
    case 18:
      ACCEPT_TOKEN(aux_sym__not_token2);
      if (lookahead == '#') ADVANCE(23);
      END_STATE();
    case 19:
      ACCEPT_TOKEN(aux_sym__not_token2);
      if (lookahead == '#') ADVANCE(23);
      if (lookahead == '%') ADVANCE(27);
      END_STATE();
    case 20:
      ACCEPT_TOKEN(aux_sym__not_token3);
      END_STATE();
    case 21:
      ACCEPT_TOKEN(aux_sym__not_token3);
      if (lookahead == '#') ADVANCE(23);
      if (lookahead == '%') ADVANCE(24);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(20);
      END_STATE();
    case 22:
      ACCEPT_TOKEN(aux_sym__not_token3);
      if (lookahead == '#') ADVANCE(23);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(20);
      END_STATE();
    case 23:
      ACCEPT_TOKEN(aux_sym__not_token3);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(20);
      END_STATE();
    case 24:
      ACCEPT_TOKEN(aux_sym__not_token3);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(25);
      END_STATE();
    case 25:
      ACCEPT_TOKEN(aux_sym__not_token4);
      END_STATE();
    case 26:
      ACCEPT_TOKEN(aux_sym__not_token4);
      if (lookahead == '#') ADVANCE(23);
      if (lookahead == '%') ADVANCE(27);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(25);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(aux_sym__not_token4);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(25);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(anon_sym_LBRACE_PERCENT);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(anon_sym_PERCENT_RBRACE);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(anon_sym_LBRACE_LBRACE);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(aux_sym_expression_token1);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(31);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(32);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(aux_sym_expression_token1);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(32);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(anon_sym_RBRACE_RBRACE);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(anon_sym_LBRACE_POUND);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(aux_sym_comment_token1);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(35);
      if (lookahead != 0 &&
          lookahead != '#') ADVANCE(36);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(aux_sym_comment_token1);
      if (lookahead != 0 &&
          lookahead != '#') ADVANCE(36);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(anon_sym_POUND_RBRACE);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(sym_white_space_control);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(sym_white_space_control);
      if (lookahead == '#') ADVANCE(23);
      if (lookahead == '}') ADVANCE(17);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(sym_white_space_control);
      if (!sym_operator_character_set_1(lookahead)) ADVANCE(44);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(sym__white_space);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(41);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '#') ADVANCE(23);
      if (lookahead == '}') ADVANCE(17);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(43);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(43);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(sym_operator);
      if (!sym_operator_character_set_1(lookahead)) ADVANCE(44);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(sym_string);
      END_STATE();
    default:
      return false;
  }
}

static bool ts_lex_keywords(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (lookahead == 'a') ADVANCE(1);
      if (lookahead == 'b') ADVANCE(2);
      if (lookahead == 'c') ADVANCE(3);
      if (lookahead == 'd') ADVANCE(4);
      if (lookahead == 'e') ADVANCE(5);
      if (lookahead == 'f') ADVANCE(6);
      if (lookahead == 'i') ADVANCE(7);
      if (lookahead == 'm') ADVANCE(8);
      if (lookahead == 'o') ADVANCE(9);
      if (lookahead == 'p') ADVANCE(10);
      if (lookahead == 'r') ADVANCE(11);
      if (lookahead == 's') ADVANCE(12);
      if (lookahead == 't') ADVANCE(13);
      if (lookahead == 'w') ADVANCE(14);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(0)
      END_STATE();
    case 1:
      if (lookahead == 'n') ADVANCE(15);
      if (lookahead == 'u') ADVANCE(16);
      END_STATE();
    case 2:
      if (lookahead == 'l') ADVANCE(17);
      END_STATE();
    case 3:
      if (lookahead == 'a') ADVANCE(18);
      END_STATE();
    case 4:
      if (lookahead == 'e') ADVANCE(19);
      if (lookahead == 'o') ADVANCE(20);
      END_STATE();
    case 5:
      if (lookahead == 'l') ADVANCE(21);
      if (lookahead == 'n') ADVANCE(22);
      if (lookahead == 'x') ADVANCE(23);
      END_STATE();
    case 6:
      if (lookahead == 'i') ADVANCE(24);
      if (lookahead == 'o') ADVANCE(25);
      if (lookahead == 'r') ADVANCE(26);
      END_STATE();
    case 7:
      if (lookahead == 'f') ADVANCE(27);
      if (lookahead == 'm') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(29);
      END_STATE();
    case 8:
      if (lookahead == 'a') ADVANCE(30);
      END_STATE();
    case 9:
      if (lookahead == 'r') ADVANCE(31);
      END_STATE();
    case 10:
      if (lookahead == 'l') ADVANCE(32);
      END_STATE();
    case 11:
      if (lookahead == 'a') ADVANCE(33);
      END_STATE();
    case 12:
      if (lookahead == 'e') ADVANCE(34);
      END_STATE();
    case 13:
      if (lookahead == 'r') ADVANCE(35);
      END_STATE();
    case 14:
      if (lookahead == 'i') ADVANCE(36);
      END_STATE();
    case 15:
      if (lookahead == 'd') ADVANCE(37);
      END_STATE();
    case 16:
      if (lookahead == 't') ADVANCE(38);
      END_STATE();
    case 17:
      if (lookahead == 'o') ADVANCE(39);
      END_STATE();
    case 18:
      if (lookahead == 'l') ADVANCE(40);
      END_STATE();
    case 19:
      if (lookahead == 'b') ADVANCE(41);
      END_STATE();
    case 20:
      ACCEPT_TOKEN(anon_sym_do);
      END_STATE();
    case 21:
      if (lookahead == 'i') ADVANCE(42);
      if (lookahead == 's') ADVANCE(43);
      END_STATE();
    case 22:
      if (lookahead == 'd') ADVANCE(44);
      END_STATE();
    case 23:
      if (lookahead == 't') ADVANCE(45);
      END_STATE();
    case 24:
      if (lookahead == 'l') ADVANCE(46);
      END_STATE();
    case 25:
      if (lookahead == 'r') ADVANCE(47);
      END_STATE();
    case 26:
      if (lookahead == 'o') ADVANCE(48);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(anon_sym_if);
      END_STATE();
    case 28:
      if (lookahead == 'p') ADVANCE(49);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(anon_sym_in);
      if (lookahead == 'c') ADVANCE(50);
      END_STATE();
    case 30:
      if (lookahead == 'c') ADVANCE(51);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(anon_sym_or);
      END_STATE();
    case 32:
      if (lookahead == 'u') ADVANCE(52);
      END_STATE();
    case 33:
      if (lookahead == 'w') ADVANCE(53);
      END_STATE();
    case 34:
      if (lookahead == 't') ADVANCE(54);
      END_STATE();
    case 35:
      if (lookahead == 'a') ADVANCE(55);
      END_STATE();
    case 36:
      if (lookahead == 't') ADVANCE(56);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(anon_sym_and);
      END_STATE();
    case 38:
      if (lookahead == 'o') ADVANCE(57);
      END_STATE();
    case 39:
      if (lookahead == 'c') ADVANCE(58);
      END_STATE();
    case 40:
      if (lookahead == 'l') ADVANCE(59);
      END_STATE();
    case 41:
      if (lookahead == 'u') ADVANCE(60);
      END_STATE();
    case 42:
      if (lookahead == 'f') ADVANCE(61);
      END_STATE();
    case 43:
      if (lookahead == 'e') ADVANCE(62);
      END_STATE();
    case 44:
      if (lookahead == 'a') ADVANCE(63);
      if (lookahead == 'b') ADVANCE(64);
      if (lookahead == 'c') ADVANCE(65);
      if (lookahead == 'f') ADVANCE(66);
      if (lookahead == 'i') ADVANCE(67);
      if (lookahead == 'm') ADVANCE(68);
      if (lookahead == 'r') ADVANCE(69);
      if (lookahead == 's') ADVANCE(70);
      if (lookahead == 't') ADVANCE(71);
      if (lookahead == 'w') ADVANCE(72);
      END_STATE();
    case 45:
      if (lookahead == 'e') ADVANCE(73);
      END_STATE();
    case 46:
      if (lookahead == 't') ADVANCE(74);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(anon_sym_for);
      END_STATE();
    case 48:
      if (lookahead == 'm') ADVANCE(75);
      END_STATE();
    case 49:
      if (lookahead == 'o') ADVANCE(76);
      END_STATE();
    case 50:
      if (lookahead == 'l') ADVANCE(77);
      END_STATE();
    case 51:
      if (lookahead == 'r') ADVANCE(78);
      END_STATE();
    case 52:
      if (lookahead == 'r') ADVANCE(79);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(anon_sym_raw);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(anon_sym_set);
      END_STATE();
    case 55:
      if (lookahead == 'n') ADVANCE(80);
      END_STATE();
    case 56:
      if (lookahead == 'h') ADVANCE(81);
      END_STATE();
    case 57:
      if (lookahead == 'e') ADVANCE(82);
      END_STATE();
    case 58:
      if (lookahead == 'k') ADVANCE(83);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(anon_sym_call);
      END_STATE();
    case 60:
      if (lookahead == 'g') ADVANCE(84);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(anon_sym_elif);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(anon_sym_else);
      END_STATE();
    case 63:
      if (lookahead == 'u') ADVANCE(85);
      END_STATE();
    case 64:
      if (lookahead == 'l') ADVANCE(86);
      END_STATE();
    case 65:
      if (lookahead == 'a') ADVANCE(87);
      END_STATE();
    case 66:
      if (lookahead == 'i') ADVANCE(88);
      if (lookahead == 'o') ADVANCE(89);
      END_STATE();
    case 67:
      if (lookahead == 'f') ADVANCE(90);
      END_STATE();
    case 68:
      if (lookahead == 'a') ADVANCE(91);
      END_STATE();
    case 69:
      if (lookahead == 'a') ADVANCE(92);
      END_STATE();
    case 70:
      if (lookahead == 'e') ADVANCE(93);
      END_STATE();
    case 71:
      if (lookahead == 'r') ADVANCE(94);
      END_STATE();
    case 72:
      if (lookahead == 'i') ADVANCE(95);
      END_STATE();
    case 73:
      if (lookahead == 'n') ADVANCE(96);
      END_STATE();
    case 74:
      if (lookahead == 'e') ADVANCE(97);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(anon_sym_from);
      END_STATE();
    case 76:
      if (lookahead == 'r') ADVANCE(98);
      END_STATE();
    case 77:
      if (lookahead == 'u') ADVANCE(99);
      END_STATE();
    case 78:
      if (lookahead == 'o') ADVANCE(100);
      END_STATE();
    case 79:
      if (lookahead == 'a') ADVANCE(101);
      END_STATE();
    case 80:
      if (lookahead == 's') ADVANCE(102);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(anon_sym_with);
      END_STATE();
    case 82:
      if (lookahead == 's') ADVANCE(103);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(anon_sym_block);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(anon_sym_debug);
      END_STATE();
    case 85:
      if (lookahead == 't') ADVANCE(104);
      END_STATE();
    case 86:
      if (lookahead == 'o') ADVANCE(105);
      END_STATE();
    case 87:
      if (lookahead == 'l') ADVANCE(106);
      END_STATE();
    case 88:
      if (lookahead == 'l') ADVANCE(107);
      END_STATE();
    case 89:
      if (lookahead == 'r') ADVANCE(108);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(anon_sym_endif);
      END_STATE();
    case 91:
      if (lookahead == 'c') ADVANCE(109);
      END_STATE();
    case 92:
      if (lookahead == 'w') ADVANCE(110);
      END_STATE();
    case 93:
      if (lookahead == 't') ADVANCE(111);
      END_STATE();
    case 94:
      if (lookahead == 'a') ADVANCE(112);
      END_STATE();
    case 95:
      if (lookahead == 't') ADVANCE(113);
      END_STATE();
    case 96:
      if (lookahead == 'd') ADVANCE(114);
      END_STATE();
    case 97:
      if (lookahead == 'r') ADVANCE(115);
      END_STATE();
    case 98:
      if (lookahead == 't') ADVANCE(116);
      END_STATE();
    case 99:
      if (lookahead == 'd') ADVANCE(117);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(anon_sym_macro);
      END_STATE();
    case 101:
      if (lookahead == 'l') ADVANCE(118);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(anon_sym_trans);
      END_STATE();
    case 103:
      if (lookahead == 'c') ADVANCE(119);
      END_STATE();
    case 104:
      if (lookahead == 'o') ADVANCE(120);
      END_STATE();
    case 105:
      if (lookahead == 'c') ADVANCE(121);
      END_STATE();
    case 106:
      if (lookahead == 'l') ADVANCE(122);
      END_STATE();
    case 107:
      if (lookahead == 't') ADVANCE(123);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(anon_sym_endfor);
      END_STATE();
    case 109:
      if (lookahead == 'r') ADVANCE(124);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(anon_sym_endraw);
      END_STATE();
    case 111:
      ACCEPT_TOKEN(anon_sym_endset);
      END_STATE();
    case 112:
      if (lookahead == 'n') ADVANCE(125);
      END_STATE();
    case 113:
      if (lookahead == 'h') ADVANCE(126);
      END_STATE();
    case 114:
      if (lookahead == 's') ADVANCE(127);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(anon_sym_filter);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(anon_sym_import);
      END_STATE();
    case 117:
      if (lookahead == 'e') ADVANCE(128);
      END_STATE();
    case 118:
      if (lookahead == 'i') ADVANCE(129);
      END_STATE();
    case 119:
      if (lookahead == 'a') ADVANCE(130);
      END_STATE();
    case 120:
      if (lookahead == 'e') ADVANCE(131);
      END_STATE();
    case 121:
      if (lookahead == 'k') ADVANCE(132);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(anon_sym_endcall);
      END_STATE();
    case 123:
      if (lookahead == 'e') ADVANCE(133);
      END_STATE();
    case 124:
      if (lookahead == 'o') ADVANCE(134);
      END_STATE();
    case 125:
      if (lookahead == 's') ADVANCE(135);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(anon_sym_endwith);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(anon_sym_extends);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(anon_sym_include);
      END_STATE();
    case 129:
      if (lookahead == 'z') ADVANCE(136);
      END_STATE();
    case 130:
      if (lookahead == 'p') ADVANCE(137);
      END_STATE();
    case 131:
      if (lookahead == 's') ADVANCE(138);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(anon_sym_endblock);
      END_STATE();
    case 133:
      if (lookahead == 'r') ADVANCE(139);
      END_STATE();
    case 134:
      ACCEPT_TOKEN(anon_sym_endmacro);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(anon_sym_endtrans);
      END_STATE();
    case 136:
      if (lookahead == 'e') ADVANCE(140);
      END_STATE();
    case 137:
      if (lookahead == 'e') ADVANCE(141);
      END_STATE();
    case 138:
      if (lookahead == 'c') ADVANCE(142);
      END_STATE();
    case 139:
      ACCEPT_TOKEN(anon_sym_endfilter);
      END_STATE();
    case 140:
      ACCEPT_TOKEN(anon_sym_pluralize);
      END_STATE();
    case 141:
      ACCEPT_TOKEN(anon_sym_autoescape);
      END_STATE();
    case 142:
      if (lookahead == 'a') ADVANCE(143);
      END_STATE();
    case 143:
      if (lookahead == 'p') ADVANCE(144);
      END_STATE();
    case 144:
      if (lookahead == 'e') ADVANCE(145);
      END_STATE();
    case 145:
      ACCEPT_TOKEN(anon_sym_endautoescape);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 10},
  [2] = {.lex_state = 5},
  [3] = {.lex_state = 5},
  [4] = {.lex_state = 5},
  [5] = {.lex_state = 5},
  [6] = {.lex_state = 4},
  [7] = {.lex_state = 4},
  [8] = {.lex_state = 4},
  [9] = {.lex_state = 10},
  [10] = {.lex_state = 10},
  [11] = {.lex_state = 10},
  [12] = {.lex_state = 10},
  [13] = {.lex_state = 10},
  [14] = {.lex_state = 10},
  [15] = {.lex_state = 10},
  [16] = {.lex_state = 10},
  [17] = {.lex_state = 0},
  [18] = {.lex_state = 0},
  [19] = {.lex_state = 31},
  [20] = {.lex_state = 4},
  [21] = {.lex_state = 4},
  [22] = {.lex_state = 35},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [aux_sym__not_token1] = ACTIONS(1),
    [aux_sym__not_token2] = ACTIONS(1),
    [aux_sym__not_token3] = ACTIONS(1),
    [anon_sym_LBRACE_PERCENT] = ACTIONS(1),
    [anon_sym_PERCENT_RBRACE] = ACTIONS(1),
    [anon_sym_LBRACE_LBRACE] = ACTIONS(1),
    [anon_sym_LBRACE_POUND] = ACTIONS(1),
    [anon_sym_for] = ACTIONS(1),
    [anon_sym_in] = ACTIONS(1),
    [anon_sym_endfor] = ACTIONS(1),
    [anon_sym_if] = ACTIONS(1),
    [anon_sym_and] = ACTIONS(1),
    [anon_sym_or] = ACTIONS(1),
    [anon_sym_endif] = ACTIONS(1),
    [anon_sym_else] = ACTIONS(1),
    [anon_sym_elif] = ACTIONS(1),
    [anon_sym_raw] = ACTIONS(1),
    [anon_sym_endraw] = ACTIONS(1),
    [anon_sym_macro] = ACTIONS(1),
    [anon_sym_endmacro] = ACTIONS(1),
    [anon_sym_extends] = ACTIONS(1),
    [anon_sym_block] = ACTIONS(1),
    [anon_sym_endblock] = ACTIONS(1),
    [anon_sym_call] = ACTIONS(1),
    [anon_sym_endcall] = ACTIONS(1),
    [anon_sym_filter] = ACTIONS(1),
    [anon_sym_endfilter] = ACTIONS(1),
    [anon_sym_set] = ACTIONS(1),
    [anon_sym_endset] = ACTIONS(1),
    [anon_sym_include] = ACTIONS(1),
    [anon_sym_import] = ACTIONS(1),
    [anon_sym_from] = ACTIONS(1),
    [anon_sym_autoescape] = ACTIONS(1),
    [anon_sym_endautoescape] = ACTIONS(1),
    [anon_sym_trans] = ACTIONS(1),
    [anon_sym_endtrans] = ACTIONS(1),
    [anon_sym_pluralize] = ACTIONS(1),
    [anon_sym_with] = ACTIONS(1),
    [anon_sym_endwith] = ACTIONS(1),
    [anon_sym_debug] = ACTIONS(1),
    [anon_sym_do] = ACTIONS(1),
    [sym_white_space_control] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(17),
    [sym__text] = STATE(9),
    [sym__not] = STATE(9),
    [sym__node] = STATE(9),
    [sym_statement] = STATE(9),
    [sym_statement_begin] = STATE(7),
    [sym_expression] = STATE(9),
    [sym_comment] = STATE(9),
    [aux_sym_source_file_repeat1] = STATE(9),
    [ts_builtin_sym_end] = ACTIONS(3),
    [aux_sym__text_token1] = ACTIONS(5),
    [aux_sym__not_token1] = ACTIONS(5),
    [aux_sym__not_token2] = ACTIONS(5),
    [aux_sym__not_token3] = ACTIONS(5),
    [aux_sym__not_token4] = ACTIONS(5),
    [anon_sym_LBRACE_PERCENT] = ACTIONS(7),
    [anon_sym_LBRACE_LBRACE] = ACTIONS(9),
    [anon_sym_LBRACE_POUND] = ACTIONS(11),
  },
  [2] = {
    [sym_statement_end] = STATE(12),
    [sym_keyword] = STATE(4),
    [aux_sym__inner_text] = STATE(4),
    [sym_identifier] = ACTIONS(13),
    [anon_sym_PERCENT_RBRACE] = ACTIONS(15),
    [anon_sym_for] = ACTIONS(17),
    [anon_sym_in] = ACTIONS(17),
    [anon_sym_endfor] = ACTIONS(17),
    [anon_sym_if] = ACTIONS(17),
    [anon_sym_and] = ACTIONS(17),
    [anon_sym_or] = ACTIONS(17),
    [anon_sym_endif] = ACTIONS(17),
    [anon_sym_else] = ACTIONS(17),
    [anon_sym_elif] = ACTIONS(17),
    [anon_sym_raw] = ACTIONS(17),
    [anon_sym_endraw] = ACTIONS(17),
    [anon_sym_macro] = ACTIONS(17),
    [anon_sym_endmacro] = ACTIONS(17),
    [anon_sym_extends] = ACTIONS(17),
    [anon_sym_block] = ACTIONS(17),
    [anon_sym_endblock] = ACTIONS(17),
    [anon_sym_call] = ACTIONS(17),
    [anon_sym_endcall] = ACTIONS(17),
    [anon_sym_filter] = ACTIONS(17),
    [anon_sym_endfilter] = ACTIONS(17),
    [anon_sym_set] = ACTIONS(17),
    [anon_sym_endset] = ACTIONS(17),
    [anon_sym_include] = ACTIONS(17),
    [anon_sym_import] = ACTIONS(17),
    [anon_sym_from] = ACTIONS(17),
    [anon_sym_autoescape] = ACTIONS(17),
    [anon_sym_endautoescape] = ACTIONS(17),
    [anon_sym_trans] = ACTIONS(17),
    [anon_sym_endtrans] = ACTIONS(17),
    [anon_sym_pluralize] = ACTIONS(17),
    [anon_sym_with] = ACTIONS(17),
    [anon_sym_endwith] = ACTIONS(17),
    [anon_sym_debug] = ACTIONS(17),
    [anon_sym_do] = ACTIONS(17),
    [sym_white_space_control] = ACTIONS(19),
    [sym__white_space] = ACTIONS(13),
    [sym_operator] = ACTIONS(13),
    [sym_string] = ACTIONS(13),
  },
  [3] = {
    [sym_statement_end] = STATE(11),
    [sym_keyword] = STATE(2),
    [aux_sym__inner_text] = STATE(2),
    [sym_identifier] = ACTIONS(21),
    [anon_sym_PERCENT_RBRACE] = ACTIONS(15),
    [anon_sym_for] = ACTIONS(17),
    [anon_sym_in] = ACTIONS(17),
    [anon_sym_endfor] = ACTIONS(17),
    [anon_sym_if] = ACTIONS(17),
    [anon_sym_and] = ACTIONS(17),
    [anon_sym_or] = ACTIONS(17),
    [anon_sym_endif] = ACTIONS(17),
    [anon_sym_else] = ACTIONS(17),
    [anon_sym_elif] = ACTIONS(17),
    [anon_sym_raw] = ACTIONS(17),
    [anon_sym_endraw] = ACTIONS(17),
    [anon_sym_macro] = ACTIONS(17),
    [anon_sym_endmacro] = ACTIONS(17),
    [anon_sym_extends] = ACTIONS(17),
    [anon_sym_block] = ACTIONS(17),
    [anon_sym_endblock] = ACTIONS(17),
    [anon_sym_call] = ACTIONS(17),
    [anon_sym_endcall] = ACTIONS(17),
    [anon_sym_filter] = ACTIONS(17),
    [anon_sym_endfilter] = ACTIONS(17),
    [anon_sym_set] = ACTIONS(17),
    [anon_sym_endset] = ACTIONS(17),
    [anon_sym_include] = ACTIONS(17),
    [anon_sym_import] = ACTIONS(17),
    [anon_sym_from] = ACTIONS(17),
    [anon_sym_autoescape] = ACTIONS(17),
    [anon_sym_endautoescape] = ACTIONS(17),
    [anon_sym_trans] = ACTIONS(17),
    [anon_sym_endtrans] = ACTIONS(17),
    [anon_sym_pluralize] = ACTIONS(17),
    [anon_sym_with] = ACTIONS(17),
    [anon_sym_endwith] = ACTIONS(17),
    [anon_sym_debug] = ACTIONS(17),
    [anon_sym_do] = ACTIONS(17),
    [sym_white_space_control] = ACTIONS(19),
    [sym__white_space] = ACTIONS(21),
    [sym_operator] = ACTIONS(21),
    [sym_string] = ACTIONS(21),
  },
  [4] = {
    [sym_keyword] = STATE(4),
    [aux_sym__inner_text] = STATE(4),
    [sym_identifier] = ACTIONS(23),
    [anon_sym_PERCENT_RBRACE] = ACTIONS(26),
    [anon_sym_for] = ACTIONS(28),
    [anon_sym_in] = ACTIONS(28),
    [anon_sym_endfor] = ACTIONS(28),
    [anon_sym_if] = ACTIONS(28),
    [anon_sym_and] = ACTIONS(28),
    [anon_sym_or] = ACTIONS(28),
    [anon_sym_endif] = ACTIONS(28),
    [anon_sym_else] = ACTIONS(28),
    [anon_sym_elif] = ACTIONS(28),
    [anon_sym_raw] = ACTIONS(28),
    [anon_sym_endraw] = ACTIONS(28),
    [anon_sym_macro] = ACTIONS(28),
    [anon_sym_endmacro] = ACTIONS(28),
    [anon_sym_extends] = ACTIONS(28),
    [anon_sym_block] = ACTIONS(28),
    [anon_sym_endblock] = ACTIONS(28),
    [anon_sym_call] = ACTIONS(28),
    [anon_sym_endcall] = ACTIONS(28),
    [anon_sym_filter] = ACTIONS(28),
    [anon_sym_endfilter] = ACTIONS(28),
    [anon_sym_set] = ACTIONS(28),
    [anon_sym_endset] = ACTIONS(28),
    [anon_sym_include] = ACTIONS(28),
    [anon_sym_import] = ACTIONS(28),
    [anon_sym_from] = ACTIONS(28),
    [anon_sym_autoescape] = ACTIONS(28),
    [anon_sym_endautoescape] = ACTIONS(28),
    [anon_sym_trans] = ACTIONS(28),
    [anon_sym_endtrans] = ACTIONS(28),
    [anon_sym_pluralize] = ACTIONS(28),
    [anon_sym_with] = ACTIONS(28),
    [anon_sym_endwith] = ACTIONS(28),
    [anon_sym_debug] = ACTIONS(28),
    [anon_sym_do] = ACTIONS(28),
    [sym_white_space_control] = ACTIONS(26),
    [sym__white_space] = ACTIONS(23),
    [sym_operator] = ACTIONS(23),
    [sym_string] = ACTIONS(23),
  },
  [5] = {
    [sym_identifier] = ACTIONS(31),
    [anon_sym_PERCENT_RBRACE] = ACTIONS(31),
    [anon_sym_for] = ACTIONS(31),
    [anon_sym_in] = ACTIONS(31),
    [anon_sym_endfor] = ACTIONS(31),
    [anon_sym_if] = ACTIONS(31),
    [anon_sym_and] = ACTIONS(31),
    [anon_sym_or] = ACTIONS(31),
    [anon_sym_endif] = ACTIONS(31),
    [anon_sym_else] = ACTIONS(31),
    [anon_sym_elif] = ACTIONS(31),
    [anon_sym_raw] = ACTIONS(31),
    [anon_sym_endraw] = ACTIONS(31),
    [anon_sym_macro] = ACTIONS(31),
    [anon_sym_endmacro] = ACTIONS(31),
    [anon_sym_extends] = ACTIONS(31),
    [anon_sym_block] = ACTIONS(31),
    [anon_sym_endblock] = ACTIONS(31),
    [anon_sym_call] = ACTIONS(31),
    [anon_sym_endcall] = ACTIONS(31),
    [anon_sym_filter] = ACTIONS(31),
    [anon_sym_endfilter] = ACTIONS(31),
    [anon_sym_set] = ACTIONS(31),
    [anon_sym_endset] = ACTIONS(31),
    [anon_sym_include] = ACTIONS(31),
    [anon_sym_import] = ACTIONS(31),
    [anon_sym_from] = ACTIONS(31),
    [anon_sym_autoescape] = ACTIONS(31),
    [anon_sym_endautoescape] = ACTIONS(31),
    [anon_sym_trans] = ACTIONS(31),
    [anon_sym_endtrans] = ACTIONS(31),
    [anon_sym_pluralize] = ACTIONS(31),
    [anon_sym_with] = ACTIONS(31),
    [anon_sym_endwith] = ACTIONS(31),
    [anon_sym_debug] = ACTIONS(31),
    [anon_sym_do] = ACTIONS(31),
    [sym_white_space_control] = ACTIONS(31),
    [sym__white_space] = ACTIONS(31),
    [sym_operator] = ACTIONS(31),
    [sym_string] = ACTIONS(31),
  },
  [6] = {
    [anon_sym_for] = ACTIONS(33),
    [anon_sym_in] = ACTIONS(35),
    [anon_sym_endfor] = ACTIONS(33),
    [anon_sym_if] = ACTIONS(33),
    [anon_sym_and] = ACTIONS(33),
    [anon_sym_or] = ACTIONS(33),
    [anon_sym_endif] = ACTIONS(33),
    [anon_sym_else] = ACTIONS(33),
    [anon_sym_elif] = ACTIONS(33),
    [anon_sym_raw] = ACTIONS(33),
    [anon_sym_endraw] = ACTIONS(33),
    [anon_sym_macro] = ACTIONS(33),
    [anon_sym_endmacro] = ACTIONS(33),
    [anon_sym_extends] = ACTIONS(33),
    [anon_sym_block] = ACTIONS(33),
    [anon_sym_endblock] = ACTIONS(33),
    [anon_sym_call] = ACTIONS(33),
    [anon_sym_endcall] = ACTIONS(33),
    [anon_sym_filter] = ACTIONS(33),
    [anon_sym_endfilter] = ACTIONS(33),
    [anon_sym_set] = ACTIONS(33),
    [anon_sym_endset] = ACTIONS(33),
    [anon_sym_include] = ACTIONS(33),
    [anon_sym_import] = ACTIONS(33),
    [anon_sym_from] = ACTIONS(33),
    [anon_sym_autoescape] = ACTIONS(33),
    [anon_sym_endautoescape] = ACTIONS(33),
    [anon_sym_trans] = ACTIONS(33),
    [anon_sym_endtrans] = ACTIONS(33),
    [anon_sym_pluralize] = ACTIONS(33),
    [anon_sym_with] = ACTIONS(33),
    [anon_sym_endwith] = ACTIONS(33),
    [anon_sym_debug] = ACTIONS(33),
    [anon_sym_do] = ACTIONS(33),
    [sym_white_space_control] = ACTIONS(37),
  },
  [7] = {
    [sym_keyword] = STATE(3),
    [anon_sym_for] = ACTIONS(39),
    [anon_sym_in] = ACTIONS(17),
    [anon_sym_endfor] = ACTIONS(39),
    [anon_sym_if] = ACTIONS(39),
    [anon_sym_and] = ACTIONS(39),
    [anon_sym_or] = ACTIONS(39),
    [anon_sym_endif] = ACTIONS(39),
    [anon_sym_else] = ACTIONS(39),
    [anon_sym_elif] = ACTIONS(39),
    [anon_sym_raw] = ACTIONS(39),
    [anon_sym_endraw] = ACTIONS(39),
    [anon_sym_macro] = ACTIONS(39),
    [anon_sym_endmacro] = ACTIONS(39),
    [anon_sym_extends] = ACTIONS(39),
    [anon_sym_block] = ACTIONS(39),
    [anon_sym_endblock] = ACTIONS(39),
    [anon_sym_call] = ACTIONS(39),
    [anon_sym_endcall] = ACTIONS(39),
    [anon_sym_filter] = ACTIONS(39),
    [anon_sym_endfilter] = ACTIONS(39),
    [anon_sym_set] = ACTIONS(39),
    [anon_sym_endset] = ACTIONS(39),
    [anon_sym_include] = ACTIONS(39),
    [anon_sym_import] = ACTIONS(39),
    [anon_sym_from] = ACTIONS(39),
    [anon_sym_autoescape] = ACTIONS(39),
    [anon_sym_endautoescape] = ACTIONS(39),
    [anon_sym_trans] = ACTIONS(39),
    [anon_sym_endtrans] = ACTIONS(39),
    [anon_sym_pluralize] = ACTIONS(39),
    [anon_sym_with] = ACTIONS(39),
    [anon_sym_endwith] = ACTIONS(39),
    [anon_sym_debug] = ACTIONS(39),
    [anon_sym_do] = ACTIONS(39),
  },
  [8] = {
    [anon_sym_for] = ACTIONS(41),
    [anon_sym_in] = ACTIONS(43),
    [anon_sym_endfor] = ACTIONS(41),
    [anon_sym_if] = ACTIONS(41),
    [anon_sym_and] = ACTIONS(41),
    [anon_sym_or] = ACTIONS(41),
    [anon_sym_endif] = ACTIONS(41),
    [anon_sym_else] = ACTIONS(41),
    [anon_sym_elif] = ACTIONS(41),
    [anon_sym_raw] = ACTIONS(41),
    [anon_sym_endraw] = ACTIONS(41),
    [anon_sym_macro] = ACTIONS(41),
    [anon_sym_endmacro] = ACTIONS(41),
    [anon_sym_extends] = ACTIONS(41),
    [anon_sym_block] = ACTIONS(41),
    [anon_sym_endblock] = ACTIONS(41),
    [anon_sym_call] = ACTIONS(41),
    [anon_sym_endcall] = ACTIONS(41),
    [anon_sym_filter] = ACTIONS(41),
    [anon_sym_endfilter] = ACTIONS(41),
    [anon_sym_set] = ACTIONS(41),
    [anon_sym_endset] = ACTIONS(41),
    [anon_sym_include] = ACTIONS(41),
    [anon_sym_import] = ACTIONS(41),
    [anon_sym_from] = ACTIONS(41),
    [anon_sym_autoescape] = ACTIONS(41),
    [anon_sym_endautoescape] = ACTIONS(41),
    [anon_sym_trans] = ACTIONS(41),
    [anon_sym_endtrans] = ACTIONS(41),
    [anon_sym_pluralize] = ACTIONS(41),
    [anon_sym_with] = ACTIONS(41),
    [anon_sym_endwith] = ACTIONS(41),
    [anon_sym_debug] = ACTIONS(41),
    [anon_sym_do] = ACTIONS(41),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 7,
    ACTIONS(7), 1,
      anon_sym_LBRACE_PERCENT,
    ACTIONS(9), 1,
      anon_sym_LBRACE_LBRACE,
    ACTIONS(11), 1,
      anon_sym_LBRACE_POUND,
    ACTIONS(45), 1,
      ts_builtin_sym_end,
    STATE(7), 1,
      sym_statement_begin,
    ACTIONS(47), 5,
      aux_sym__text_token1,
      aux_sym__not_token1,
      aux_sym__not_token2,
      aux_sym__not_token3,
      aux_sym__not_token4,
    STATE(10), 7,
      sym__text,
      sym__not,
      sym__node,
      sym_statement,
      sym_expression,
      sym_comment,
      aux_sym_source_file_repeat1,
  [32] = 7,
    ACTIONS(49), 1,
      ts_builtin_sym_end,
    ACTIONS(54), 1,
      anon_sym_LBRACE_PERCENT,
    ACTIONS(57), 1,
      anon_sym_LBRACE_LBRACE,
    ACTIONS(60), 1,
      anon_sym_LBRACE_POUND,
    STATE(7), 1,
      sym_statement_begin,
    ACTIONS(51), 5,
      aux_sym__text_token1,
      aux_sym__not_token1,
      aux_sym__not_token2,
      aux_sym__not_token3,
      aux_sym__not_token4,
    STATE(10), 7,
      sym__text,
      sym__not,
      sym__node,
      sym_statement,
      sym_expression,
      sym_comment,
      aux_sym_source_file_repeat1,
  [64] = 2,
    ACTIONS(63), 1,
      ts_builtin_sym_end,
    ACTIONS(65), 8,
      aux_sym__text_token1,
      aux_sym__not_token1,
      aux_sym__not_token2,
      aux_sym__not_token3,
      aux_sym__not_token4,
      anon_sym_LBRACE_PERCENT,
      anon_sym_LBRACE_LBRACE,
      anon_sym_LBRACE_POUND,
  [78] = 2,
    ACTIONS(67), 1,
      ts_builtin_sym_end,
    ACTIONS(69), 8,
      aux_sym__text_token1,
      aux_sym__not_token1,
      aux_sym__not_token2,
      aux_sym__not_token3,
      aux_sym__not_token4,
      anon_sym_LBRACE_PERCENT,
      anon_sym_LBRACE_LBRACE,
      anon_sym_LBRACE_POUND,
  [92] = 2,
    ACTIONS(71), 1,
      ts_builtin_sym_end,
    ACTIONS(73), 8,
      aux_sym__text_token1,
      aux_sym__not_token1,
      aux_sym__not_token2,
      aux_sym__not_token3,
      aux_sym__not_token4,
      anon_sym_LBRACE_PERCENT,
      anon_sym_LBRACE_LBRACE,
      anon_sym_LBRACE_POUND,
  [106] = 2,
    ACTIONS(75), 1,
      ts_builtin_sym_end,
    ACTIONS(77), 8,
      aux_sym__text_token1,
      aux_sym__not_token1,
      aux_sym__not_token2,
      aux_sym__not_token3,
      aux_sym__not_token4,
      anon_sym_LBRACE_PERCENT,
      anon_sym_LBRACE_LBRACE,
      anon_sym_LBRACE_POUND,
  [120] = 2,
    ACTIONS(79), 1,
      ts_builtin_sym_end,
    ACTIONS(81), 8,
      aux_sym__text_token1,
      aux_sym__not_token1,
      aux_sym__not_token2,
      aux_sym__not_token3,
      aux_sym__not_token4,
      anon_sym_LBRACE_PERCENT,
      anon_sym_LBRACE_LBRACE,
      anon_sym_LBRACE_POUND,
  [134] = 2,
    ACTIONS(83), 1,
      ts_builtin_sym_end,
    ACTIONS(85), 8,
      aux_sym__text_token1,
      aux_sym__not_token1,
      aux_sym__not_token2,
      aux_sym__not_token3,
      aux_sym__not_token4,
      anon_sym_LBRACE_PERCENT,
      anon_sym_LBRACE_LBRACE,
      anon_sym_LBRACE_POUND,
  [148] = 1,
    ACTIONS(87), 1,
      ts_builtin_sym_end,
  [152] = 1,
    ACTIONS(89), 1,
      anon_sym_PERCENT_RBRACE,
  [156] = 1,
    ACTIONS(91), 1,
      aux_sym_expression_token1,
  [160] = 1,
    ACTIONS(93), 1,
      anon_sym_POUND_RBRACE,
  [164] = 1,
    ACTIONS(95), 1,
      anon_sym_RBRACE_RBRACE,
  [168] = 1,
    ACTIONS(97), 1,
      aux_sym_comment_token1,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(9)] = 0,
  [SMALL_STATE(10)] = 32,
  [SMALL_STATE(11)] = 64,
  [SMALL_STATE(12)] = 78,
  [SMALL_STATE(13)] = 92,
  [SMALL_STATE(14)] = 106,
  [SMALL_STATE(15)] = 120,
  [SMALL_STATE(16)] = 134,
  [SMALL_STATE(17)] = 148,
  [SMALL_STATE(18)] = 152,
  [SMALL_STATE(19)] = 156,
  [SMALL_STATE(20)] = 160,
  [SMALL_STATE(21)] = 164,
  [SMALL_STATE(22)] = 168,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [5] = {.entry = {.count = 1, .reusable = false}}, SHIFT(9),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(6),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(19),
  [11] = {.entry = {.count = 1, .reusable = false}}, SHIFT(22),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(4),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(16),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(5),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(18),
  [21] = {.entry = {.count = 1, .reusable = false}}, SHIFT(2),
  [23] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__inner_text, 2), SHIFT_REPEAT(4),
  [26] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym__inner_text, 2),
  [28] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__inner_text, 2), SHIFT_REPEAT(5),
  [31] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_keyword, 1),
  [33] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_statement_begin, 1),
  [35] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_statement_begin, 1),
  [37] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [39] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [41] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_statement_begin, 2),
  [43] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_statement_begin, 2),
  [45] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [47] = {.entry = {.count = 1, .reusable = false}}, SHIFT(10),
  [49] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [51] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(10),
  [54] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(6),
  [57] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(19),
  [60] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(22),
  [63] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_statement, 3),
  [65] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_statement, 3),
  [67] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_statement, 4),
  [69] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_statement, 4),
  [71] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_statement_end, 2),
  [73] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_statement_end, 2),
  [75] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression, 3),
  [77] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_expression, 3),
  [79] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comment, 3),
  [81] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comment, 3),
  [83] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_statement_end, 1),
  [85] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_statement_end, 1),
  [87] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [89] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [91] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [93] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [95] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [97] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_jinja2(void) {
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
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .keyword_lex_fn = ts_lex_keywords,
    .keyword_capture_token = sym_identifier,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
