#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 54
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 31
#define ALIAS_COUNT 0
#define TOKEN_COUNT 19
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 6
#define PRODUCTION_ID_COUNT 1

enum {
  aux_sym__line_token1 = 1,
  sym_change_port = 2,
  sym_parameter = 3,
  anon_sym_LBRACK = 4,
  anon_sym_COMMA = 5,
  anon_sym_RBRACK = 6,
  sym_index = 7,
  anon_sym_0x = 8,
  aux_sym_hex_argument_token1 = 9,
  sym_template = 10,
  sym_numeric_argument = 11,
  sym_string_literal_argument = 12,
  sym_string_argument = 13,
  sym_ipv4_argument = 14,
  anon_sym_SEMI = 15,
  aux_sym_comment_token1 = 16,
  sym_port_comment = 17,
  sym__line_ending = 18,
  sym_program = 19,
  aux_sym__lines = 20,
  sym__line = 21,
  sym_command = 22,
  sym_indexes = 23,
  sym__argument = 24,
  sym_hex_argument = 25,
  sym_comment = 26,
  aux_sym_command_repeat1 = 27,
  aux_sym_indexes_repeat1 = 28,
  aux_sym_hex_argument_repeat1 = 29,
  aux_sym_comment_repeat1 = 30,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [aux_sym__line_token1] = "_line_token1",
  [sym_change_port] = "change_port",
  [sym_parameter] = "parameter",
  [anon_sym_LBRACK] = "[",
  [anon_sym_COMMA] = ",",
  [anon_sym_RBRACK] = "]",
  [sym_index] = "index",
  [anon_sym_0x] = "0x",
  [aux_sym_hex_argument_token1] = "hex_argument_token1",
  [sym_template] = "template",
  [sym_numeric_argument] = "numeric_argument",
  [sym_string_literal_argument] = "string_literal_argument",
  [sym_string_argument] = "string_argument",
  [sym_ipv4_argument] = "ipv4_argument",
  [anon_sym_SEMI] = ";",
  [aux_sym_comment_token1] = "comment_token1",
  [sym_port_comment] = "port_comment",
  [sym__line_ending] = "_line_ending",
  [sym_program] = "program",
  [aux_sym__lines] = "_lines",
  [sym__line] = "_line",
  [sym_command] = "command",
  [sym_indexes] = "indexes",
  [sym__argument] = "_argument",
  [sym_hex_argument] = "hex_argument",
  [sym_comment] = "comment",
  [aux_sym_command_repeat1] = "command_repeat1",
  [aux_sym_indexes_repeat1] = "indexes_repeat1",
  [aux_sym_hex_argument_repeat1] = "hex_argument_repeat1",
  [aux_sym_comment_repeat1] = "comment_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [aux_sym__line_token1] = aux_sym__line_token1,
  [sym_change_port] = sym_change_port,
  [sym_parameter] = sym_parameter,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [sym_index] = sym_index,
  [anon_sym_0x] = anon_sym_0x,
  [aux_sym_hex_argument_token1] = aux_sym_hex_argument_token1,
  [sym_template] = sym_template,
  [sym_numeric_argument] = sym_numeric_argument,
  [sym_string_literal_argument] = sym_string_literal_argument,
  [sym_string_argument] = sym_string_argument,
  [sym_ipv4_argument] = sym_ipv4_argument,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [aux_sym_comment_token1] = aux_sym_comment_token1,
  [sym_port_comment] = sym_port_comment,
  [sym__line_ending] = sym__line_ending,
  [sym_program] = sym_program,
  [aux_sym__lines] = aux_sym__lines,
  [sym__line] = sym__line,
  [sym_command] = sym_command,
  [sym_indexes] = sym_indexes,
  [sym__argument] = sym__argument,
  [sym_hex_argument] = sym_hex_argument,
  [sym_comment] = sym_comment,
  [aux_sym_command_repeat1] = aux_sym_command_repeat1,
  [aux_sym_indexes_repeat1] = aux_sym_indexes_repeat1,
  [aux_sym_hex_argument_repeat1] = aux_sym_hex_argument_repeat1,
  [aux_sym_comment_repeat1] = aux_sym_comment_repeat1,
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
  [sym_change_port] = {
    .visible = true,
    .named = true,
  },
  [sym_parameter] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [sym_index] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_0x] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_hex_argument_token1] = {
    .visible = false,
    .named = false,
  },
  [sym_template] = {
    .visible = true,
    .named = true,
  },
  [sym_numeric_argument] = {
    .visible = true,
    .named = true,
  },
  [sym_string_literal_argument] = {
    .visible = true,
    .named = true,
  },
  [sym_string_argument] = {
    .visible = true,
    .named = true,
  },
  [sym_ipv4_argument] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_SEMI] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_comment_token1] = {
    .visible = false,
    .named = false,
  },
  [sym_port_comment] = {
    .visible = true,
    .named = true,
  },
  [sym__line_ending] = {
    .visible = false,
    .named = true,
  },
  [sym_program] = {
    .visible = true,
    .named = true,
  },
  [aux_sym__lines] = {
    .visible = false,
    .named = false,
  },
  [sym__line] = {
    .visible = false,
    .named = true,
  },
  [sym_command] = {
    .visible = true,
    .named = true,
  },
  [sym_indexes] = {
    .visible = true,
    .named = true,
  },
  [sym__argument] = {
    .visible = false,
    .named = true,
  },
  [sym_hex_argument] = {
    .visible = true,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_command_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_indexes_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_hex_argument_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_comment_repeat1] = {
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
  [23] = 23,
  [24] = 24,
  [25] = 25,
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
  [49] = 49,
  [50] = 50,
  [51] = 51,
  [52] = 52,
  [53] = 53,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(38);
      if (lookahead == ',') ADVANCE(44);
      if (lookahead == ';') ADVANCE(64);
      if (lookahead == '[') ADVANCE(43);
      if (lookahead == ']') ADVANCE(45);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(39);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(69);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(46);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(48);
      if (lookahead != 0) ADVANCE(65);
      END_STATE();
    case 1:
      if (lookahead == '"') ADVANCE(2);
      if (lookahead == ',') ADVANCE(44);
      if (lookahead == '-') ADVANCE(33);
      if (lookahead == '0') ADVANCE(51);
      if (lookahead == '1') ADVANCE(55);
      if (lookahead == '2') ADVANCE(50);
      if (lookahead == '<') ADVANCE(36);
      if (lookahead == '[') ADVANCE(43);
      if (lookahead == ']') ADVANCE(45);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(40);
      if (('3' <= lookahead && lookahead <= '9')) ADVANCE(54);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(34);
      END_STATE();
    case 2:
      if (lookahead == '"') ADVANCE(57);
      if (lookahead != 0) ADVANCE(2);
      END_STATE();
    case 3:
      if (lookahead == '.') ADVANCE(17);
      END_STATE();
    case 4:
      if (lookahead == '.') ADVANCE(17);
      if (lookahead == '5') ADVANCE(5);
      if (('6' <= lookahead && lookahead <= '9')) ADVANCE(3);
      if (('0' <= lookahead && lookahead <= '4')) ADVANCE(6);
      END_STATE();
    case 5:
      if (lookahead == '.') ADVANCE(17);
      if (('0' <= lookahead && lookahead <= '5')) ADVANCE(3);
      END_STATE();
    case 6:
      if (lookahead == '.') ADVANCE(17);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(3);
      END_STATE();
    case 7:
      if (lookahead == '.') ADVANCE(17);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(6);
      END_STATE();
    case 8:
      if (lookahead == '.') ADVANCE(18);
      END_STATE();
    case 9:
      if (lookahead == '.') ADVANCE(18);
      if (lookahead == '5') ADVANCE(10);
      if (('6' <= lookahead && lookahead <= '9')) ADVANCE(8);
      if (('0' <= lookahead && lookahead <= '4')) ADVANCE(11);
      END_STATE();
    case 10:
      if (lookahead == '.') ADVANCE(18);
      if (('0' <= lookahead && lookahead <= '5')) ADVANCE(8);
      END_STATE();
    case 11:
      if (lookahead == '.') ADVANCE(18);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(8);
      END_STATE();
    case 12:
      if (lookahead == '.') ADVANCE(18);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(11);
      END_STATE();
    case 13:
      if (lookahead == '/') ADVANCE(32);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(13);
      END_STATE();
    case 14:
      if (lookahead == '/') ADVANCE(31);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(14);
      END_STATE();
    case 15:
      if (lookahead == '/') ADVANCE(31);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(14);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(15);
      END_STATE();
    case 16:
      if (lookahead == '0') ADVANCE(8);
      if (lookahead == '1') ADVANCE(12);
      if (lookahead == '2') ADVANCE(9);
      if (('3' <= lookahead && lookahead <= '9')) ADVANCE(11);
      END_STATE();
    case 17:
      if (lookahead == '0') ADVANCE(59);
      if (lookahead == '1') ADVANCE(63);
      if (lookahead == '2') ADVANCE(60);
      if (('3' <= lookahead && lookahead <= '9')) ADVANCE(62);
      END_STATE();
    case 18:
      if (lookahead == '0') ADVANCE(3);
      if (lookahead == '1') ADVANCE(7);
      if (lookahead == '2') ADVANCE(4);
      if (('3' <= lookahead && lookahead <= '9')) ADVANCE(6);
      END_STATE();
    case 19:
      if (lookahead == ':') ADVANCE(30);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(19);
      END_STATE();
    case 20:
      if (lookahead == '<') ADVANCE(36);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(39);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(69);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(48);
      END_STATE();
    case 21:
      if (lookahead == '>') ADVANCE(49);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(21);
      END_STATE();
    case 22:
      if (lookahead == 'P') ADVANCE(66);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(67);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(69);
      if (lookahead != 0) ADVANCE(65);
      END_STATE();
    case 23:
      if (lookahead == '_') ADVANCE(35);
      END_STATE();
    case 24:
      if (lookahead == '_') ADVANCE(35);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(25);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(23);
      END_STATE();
    case 25:
      if (lookahead == '_') ADVANCE(35);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(23);
      END_STATE();
    case 26:
      if (lookahead == 'r') ADVANCE(27);
      END_STATE();
    case 27:
      if (lookahead == 't') ADVANCE(19);
      END_STATE();
    case 28:
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(40);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(46);
      END_STATE();
    case 29:
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(29);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(69);
      END_STATE();
    case 30:
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(30);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(15);
      END_STATE();
    case 31:
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(31);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(68);
      END_STATE();
    case 32:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(41);
      END_STATE();
    case 33:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(56);
      END_STATE();
    case 34:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(58);
      END_STATE();
    case 35:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(42);
      END_STATE();
    case 36:
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(21);
      END_STATE();
    case 37:
      if (eof) ADVANCE(38);
      if (lookahead == ',') ADVANCE(44);
      if (lookahead == ';') ADVANCE(64);
      if (lookahead == ']') ADVANCE(45);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(39);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(69);
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(24);
      if (lookahead == 'C' ||
          lookahead == 'M' ||
          lookahead == 'c' ||
          lookahead == 'm') ADVANCE(25);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(13);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(aux_sym__line_token1);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(39);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(69);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(aux_sym__line_token1);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(40);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(sym_change_port);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(41);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(sym_parameter);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(42);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(sym_index);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(46);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(anon_sym_0x);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(aux_sym_hex_argument_token1);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(sym_template);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(sym_numeric_argument);
      if (lookahead == '.') ADVANCE(16);
      if (lookahead == '5') ADVANCE(52);
      if (('6' <= lookahead && lookahead <= '9')) ADVANCE(53);
      if (('0' <= lookahead && lookahead <= '4')) ADVANCE(54);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(sym_numeric_argument);
      if (lookahead == '.') ADVANCE(16);
      if (lookahead == 'x') ADVANCE(47);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(56);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(sym_numeric_argument);
      if (lookahead == '.') ADVANCE(16);
      if (('6' <= lookahead && lookahead <= '9')) ADVANCE(56);
      if (('0' <= lookahead && lookahead <= '5')) ADVANCE(53);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(sym_numeric_argument);
      if (lookahead == '.') ADVANCE(16);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(56);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(sym_numeric_argument);
      if (lookahead == '.') ADVANCE(16);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(53);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(sym_numeric_argument);
      if (lookahead == '.') ADVANCE(16);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(54);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(sym_numeric_argument);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(56);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(sym_string_literal_argument);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(sym_string_argument);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(58);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(sym_ipv4_argument);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(sym_ipv4_argument);
      if (lookahead == '5') ADVANCE(61);
      if (('6' <= lookahead && lookahead <= '9')) ADVANCE(59);
      if (('0' <= lookahead && lookahead <= '4')) ADVANCE(62);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(sym_ipv4_argument);
      if (('0' <= lookahead && lookahead <= '5')) ADVANCE(59);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(sym_ipv4_argument);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(59);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(sym_ipv4_argument);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(62);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(aux_sym_comment_token1);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(aux_sym_comment_token1);
      if (lookahead == 'o') ADVANCE(26);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(aux_sym_comment_token1);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(29);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(69);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(sym_port_comment);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(68);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(sym__line_ending);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(69);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 37},
  [2] = {.lex_state = 37},
  [3] = {.lex_state = 1},
  [4] = {.lex_state = 37},
  [5] = {.lex_state = 1},
  [6] = {.lex_state = 37},
  [7] = {.lex_state = 37},
  [8] = {.lex_state = 37},
  [9] = {.lex_state = 37},
  [10] = {.lex_state = 37},
  [11] = {.lex_state = 37},
  [12] = {.lex_state = 37},
  [13] = {.lex_state = 37},
  [14] = {.lex_state = 20},
  [15] = {.lex_state = 20},
  [16] = {.lex_state = 37},
  [17] = {.lex_state = 22},
  [18] = {.lex_state = 1},
  [19] = {.lex_state = 1},
  [20] = {.lex_state = 1},
  [21] = {.lex_state = 22},
  [22] = {.lex_state = 1},
  [23] = {.lex_state = 1},
  [24] = {.lex_state = 22},
  [25] = {.lex_state = 1},
  [26] = {.lex_state = 1},
  [27] = {.lex_state = 20},
  [28] = {.lex_state = 37},
  [29] = {.lex_state = 37},
  [30] = {.lex_state = 37},
  [31] = {.lex_state = 37},
  [32] = {.lex_state = 1},
  [33] = {.lex_state = 37},
  [34] = {.lex_state = 28},
  [35] = {.lex_state = 37},
  [36] = {.lex_state = 37},
  [37] = {.lex_state = 37},
  [38] = {.lex_state = 37},
  [39] = {.lex_state = 28},
  [40] = {.lex_state = 37},
  [41] = {.lex_state = 37},
  [42] = {.lex_state = 37},
  [43] = {.lex_state = 37},
  [44] = {.lex_state = 28},
  [45] = {.lex_state = 0},
  [46] = {.lex_state = 0},
  [47] = {.lex_state = 0},
  [48] = {.lex_state = 28},
  [49] = {.lex_state = 28},
  [50] = {.lex_state = 0},
  [51] = {.lex_state = 0},
  [52] = {.lex_state = 28},
  [53] = {.lex_state = 37},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [aux_sym__line_token1] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [sym_index] = ACTIONS(1),
    [aux_sym_hex_argument_token1] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [aux_sym_comment_token1] = ACTIONS(1),
    [sym__line_ending] = ACTIONS(1),
  },
  [1] = {
    [sym_program] = STATE(46),
    [aux_sym__lines] = STATE(2),
    [sym__line] = STATE(2),
    [sym_command] = STATE(47),
    [sym_comment] = STATE(47),
    [aux_sym__line_token1] = ACTIONS(3),
    [sym_change_port] = ACTIONS(5),
    [sym_parameter] = ACTIONS(7),
    [anon_sym_SEMI] = ACTIONS(9),
    [sym__line_ending] = ACTIONS(11),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 8,
    ACTIONS(3), 1,
      aux_sym__line_token1,
    ACTIONS(5), 1,
      sym_change_port,
    ACTIONS(7), 1,
      sym_parameter,
    ACTIONS(9), 1,
      anon_sym_SEMI,
    ACTIONS(13), 1,
      ts_builtin_sym_end,
    ACTIONS(15), 1,
      sym__line_ending,
    STATE(4), 2,
      aux_sym__lines,
      sym__line,
    STATE(47), 2,
      sym_command,
      sym_comment,
  [27] = 6,
    ACTIONS(17), 1,
      anon_sym_LBRACK,
    ACTIONS(19), 1,
      anon_sym_0x,
    ACTIONS(23), 1,
      sym_numeric_argument,
    STATE(28), 1,
      sym_indexes,
    STATE(42), 2,
      sym__argument,
      sym_hex_argument,
    ACTIONS(21), 4,
      sym_template,
      sym_string_literal_argument,
      sym_string_argument,
      sym_ipv4_argument,
  [50] = 8,
    ACTIONS(25), 1,
      ts_builtin_sym_end,
    ACTIONS(27), 1,
      aux_sym__line_token1,
    ACTIONS(30), 1,
      sym_change_port,
    ACTIONS(33), 1,
      sym_parameter,
    ACTIONS(36), 1,
      anon_sym_SEMI,
    ACTIONS(39), 1,
      sym__line_ending,
    STATE(4), 2,
      aux_sym__lines,
      sym__line,
    STATE(47), 2,
      sym_command,
      sym_comment,
  [77] = 4,
    ACTIONS(19), 1,
      anon_sym_0x,
    ACTIONS(23), 1,
      sym_numeric_argument,
    STATE(42), 2,
      sym__argument,
      sym_hex_argument,
    ACTIONS(21), 4,
      sym_template,
      sym_string_literal_argument,
      sym_string_argument,
      sym_ipv4_argument,
  [94] = 5,
    ACTIONS(7), 1,
      sym_parameter,
    ACTIONS(9), 1,
      anon_sym_SEMI,
    ACTIONS(42), 1,
      sym_change_port,
    ACTIONS(44), 1,
      sym__line_ending,
    STATE(51), 2,
      sym_command,
      sym_comment,
  [111] = 5,
    ACTIONS(7), 1,
      sym_parameter,
    ACTIONS(9), 1,
      anon_sym_SEMI,
    ACTIONS(44), 1,
      sym__line_ending,
    ACTIONS(46), 1,
      aux_sym__line_token1,
    STATE(51), 2,
      sym_command,
      sym_comment,
  [128] = 2,
    ACTIONS(50), 1,
      aux_sym__line_token1,
    ACTIONS(48), 5,
      ts_builtin_sym_end,
      sym_change_port,
      sym_parameter,
      anon_sym_SEMI,
      sym__line_ending,
  [139] = 2,
    ACTIONS(54), 1,
      aux_sym__line_token1,
    ACTIONS(52), 5,
      ts_builtin_sym_end,
      sym_change_port,
      sym_parameter,
      anon_sym_SEMI,
      sym__line_ending,
  [150] = 5,
    ACTIONS(7), 1,
      sym_parameter,
    ACTIONS(9), 1,
      anon_sym_SEMI,
    ACTIONS(56), 1,
      aux_sym__line_token1,
    ACTIONS(58), 1,
      sym__line_ending,
    STATE(45), 2,
      sym_command,
      sym_comment,
  [167] = 2,
    ACTIONS(62), 1,
      aux_sym__line_token1,
    ACTIONS(60), 5,
      ts_builtin_sym_end,
      sym_change_port,
      sym_parameter,
      anon_sym_SEMI,
      sym__line_ending,
  [178] = 2,
    ACTIONS(66), 1,
      aux_sym__line_token1,
    ACTIONS(64), 5,
      ts_builtin_sym_end,
      sym_change_port,
      sym_parameter,
      anon_sym_SEMI,
      sym__line_ending,
  [189] = 4,
    ACTIONS(7), 1,
      sym_parameter,
    ACTIONS(9), 1,
      anon_sym_SEMI,
    ACTIONS(68), 1,
      sym__line_ending,
    STATE(50), 2,
      sym_command,
      sym_comment,
  [203] = 4,
    ACTIONS(70), 1,
      aux_sym__line_token1,
    ACTIONS(75), 1,
      sym__line_ending,
    STATE(14), 1,
      aux_sym_hex_argument_repeat1,
    ACTIONS(72), 2,
      aux_sym_hex_argument_token1,
      sym_template,
  [217] = 4,
    ACTIONS(77), 1,
      aux_sym__line_token1,
    ACTIONS(81), 1,
      sym__line_ending,
    STATE(14), 1,
      aux_sym_hex_argument_repeat1,
    ACTIONS(79), 2,
      aux_sym_hex_argument_token1,
      sym_template,
  [231] = 4,
    ACTIONS(7), 1,
      sym_parameter,
    ACTIONS(9), 1,
      anon_sym_SEMI,
    ACTIONS(58), 1,
      sym__line_ending,
    STATE(45), 2,
      sym_command,
      sym_comment,
  [245] = 4,
    ACTIONS(83), 1,
      aux_sym_comment_token1,
    ACTIONS(86), 1,
      sym_port_comment,
    ACTIONS(89), 1,
      sym__line_ending,
    STATE(17), 1,
      aux_sym_comment_repeat1,
  [258] = 4,
    ACTIONS(91), 1,
      aux_sym__line_token1,
    ACTIONS(93), 1,
      anon_sym_COMMA,
    ACTIONS(95), 1,
      anon_sym_RBRACK,
    STATE(20), 1,
      aux_sym_indexes_repeat1,
  [271] = 4,
    ACTIONS(97), 1,
      aux_sym__line_token1,
    ACTIONS(100), 1,
      anon_sym_COMMA,
    ACTIONS(103), 1,
      anon_sym_RBRACK,
    STATE(19), 1,
      aux_sym_indexes_repeat1,
  [284] = 4,
    ACTIONS(93), 1,
      anon_sym_COMMA,
    ACTIONS(105), 1,
      aux_sym__line_token1,
    ACTIONS(107), 1,
      anon_sym_RBRACK,
    STATE(19), 1,
      aux_sym_indexes_repeat1,
  [297] = 4,
    ACTIONS(109), 1,
      aux_sym_comment_token1,
    ACTIONS(111), 1,
      sym_port_comment,
    ACTIONS(113), 1,
      sym__line_ending,
    STATE(24), 1,
      aux_sym_comment_repeat1,
  [310] = 4,
    ACTIONS(93), 1,
      anon_sym_COMMA,
    ACTIONS(115), 1,
      aux_sym__line_token1,
    ACTIONS(117), 1,
      anon_sym_RBRACK,
    STATE(23), 1,
      aux_sym_indexes_repeat1,
  [323] = 4,
    ACTIONS(91), 1,
      aux_sym__line_token1,
    ACTIONS(93), 1,
      anon_sym_COMMA,
    ACTIONS(95), 1,
      anon_sym_RBRACK,
    STATE(19), 1,
      aux_sym_indexes_repeat1,
  [336] = 4,
    ACTIONS(119), 1,
      aux_sym_comment_token1,
    ACTIONS(121), 1,
      sym_port_comment,
    ACTIONS(123), 1,
      sym__line_ending,
    STATE(17), 1,
      aux_sym_comment_repeat1,
  [349] = 1,
    ACTIONS(125), 3,
      aux_sym__line_token1,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [355] = 1,
    ACTIONS(127), 3,
      aux_sym__line_token1,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [361] = 2,
    STATE(15), 1,
      aux_sym_hex_argument_repeat1,
    ACTIONS(129), 2,
      aux_sym_hex_argument_token1,
      sym_template,
  [369] = 3,
    ACTIONS(131), 1,
      aux_sym__line_token1,
    ACTIONS(133), 1,
      sym__line_ending,
    STATE(33), 1,
      aux_sym_command_repeat1,
  [379] = 3,
    ACTIONS(135), 1,
      aux_sym__line_token1,
    ACTIONS(137), 1,
      sym__line_ending,
    STATE(31), 1,
      aux_sym_command_repeat1,
  [389] = 3,
    ACTIONS(139), 1,
      aux_sym__line_token1,
    ACTIONS(142), 1,
      sym__line_ending,
    STATE(30), 1,
      aux_sym_command_repeat1,
  [399] = 3,
    ACTIONS(131), 1,
      aux_sym__line_token1,
    ACTIONS(144), 1,
      sym__line_ending,
    STATE(30), 1,
      aux_sym_command_repeat1,
  [409] = 1,
    ACTIONS(103), 3,
      aux_sym__line_token1,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [415] = 3,
    ACTIONS(131), 1,
      aux_sym__line_token1,
    ACTIONS(146), 1,
      sym__line_ending,
    STATE(30), 1,
      aux_sym_command_repeat1,
  [425] = 2,
    ACTIONS(148), 1,
      aux_sym__line_token1,
    ACTIONS(150), 1,
      sym_index,
  [432] = 2,
    ACTIONS(95), 1,
      anon_sym_RBRACK,
    ACTIONS(152), 1,
      anon_sym_COMMA,
  [439] = 2,
    ACTIONS(154), 1,
      aux_sym__line_token1,
    ACTIONS(156), 1,
      sym__line_ending,
  [446] = 2,
    ACTIONS(107), 1,
      anon_sym_RBRACK,
    ACTIONS(152), 1,
      anon_sym_COMMA,
  [453] = 2,
    ACTIONS(158), 1,
      aux_sym__line_token1,
    ACTIONS(160), 1,
      sym__line_ending,
  [460] = 2,
    ACTIONS(162), 1,
      aux_sym__line_token1,
    ACTIONS(164), 1,
      sym_index,
  [467] = 2,
    ACTIONS(166), 1,
      aux_sym__line_token1,
    ACTIONS(168), 1,
      sym__line_ending,
  [474] = 2,
    ACTIONS(152), 1,
      anon_sym_COMMA,
    ACTIONS(170), 1,
      anon_sym_RBRACK,
  [481] = 2,
    ACTIONS(142), 1,
      sym__line_ending,
    ACTIONS(172), 1,
      aux_sym__line_token1,
  [488] = 2,
    ACTIONS(174), 1,
      aux_sym__line_token1,
    ACTIONS(176), 1,
      sym__line_ending,
  [495] = 2,
    ACTIONS(178), 1,
      aux_sym__line_token1,
    ACTIONS(180), 1,
      sym_index,
  [502] = 1,
    ACTIONS(68), 1,
      sym__line_ending,
  [506] = 1,
    ACTIONS(182), 1,
      ts_builtin_sym_end,
  [510] = 1,
    ACTIONS(44), 1,
      sym__line_ending,
  [514] = 1,
    ACTIONS(184), 1,
      sym_index,
  [518] = 1,
    ACTIONS(164), 1,
      sym_index,
  [522] = 1,
    ACTIONS(186), 1,
      sym__line_ending,
  [526] = 1,
    ACTIONS(58), 1,
      sym__line_ending,
  [530] = 1,
    ACTIONS(188), 1,
      sym_index,
  [534] = 1,
    ACTIONS(152), 1,
      anon_sym_COMMA,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 27,
  [SMALL_STATE(4)] = 50,
  [SMALL_STATE(5)] = 77,
  [SMALL_STATE(6)] = 94,
  [SMALL_STATE(7)] = 111,
  [SMALL_STATE(8)] = 128,
  [SMALL_STATE(9)] = 139,
  [SMALL_STATE(10)] = 150,
  [SMALL_STATE(11)] = 167,
  [SMALL_STATE(12)] = 178,
  [SMALL_STATE(13)] = 189,
  [SMALL_STATE(14)] = 203,
  [SMALL_STATE(15)] = 217,
  [SMALL_STATE(16)] = 231,
  [SMALL_STATE(17)] = 245,
  [SMALL_STATE(18)] = 258,
  [SMALL_STATE(19)] = 271,
  [SMALL_STATE(20)] = 284,
  [SMALL_STATE(21)] = 297,
  [SMALL_STATE(22)] = 310,
  [SMALL_STATE(23)] = 323,
  [SMALL_STATE(24)] = 336,
  [SMALL_STATE(25)] = 349,
  [SMALL_STATE(26)] = 355,
  [SMALL_STATE(27)] = 361,
  [SMALL_STATE(28)] = 369,
  [SMALL_STATE(29)] = 379,
  [SMALL_STATE(30)] = 389,
  [SMALL_STATE(31)] = 399,
  [SMALL_STATE(32)] = 409,
  [SMALL_STATE(33)] = 415,
  [SMALL_STATE(34)] = 425,
  [SMALL_STATE(35)] = 432,
  [SMALL_STATE(36)] = 439,
  [SMALL_STATE(37)] = 446,
  [SMALL_STATE(38)] = 453,
  [SMALL_STATE(39)] = 460,
  [SMALL_STATE(40)] = 467,
  [SMALL_STATE(41)] = 474,
  [SMALL_STATE(42)] = 481,
  [SMALL_STATE(43)] = 488,
  [SMALL_STATE(44)] = 495,
  [SMALL_STATE(45)] = 502,
  [SMALL_STATE(46)] = 506,
  [SMALL_STATE(47)] = 510,
  [SMALL_STATE(48)] = 514,
  [SMALL_STATE(49)] = 518,
  [SMALL_STATE(50)] = 522,
  [SMALL_STATE(51)] = 526,
  [SMALL_STATE(52)] = 530,
  [SMALL_STATE(53)] = 534,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = false}}, SHIFT(6),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [13] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_program, 1),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(42),
  [25] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__lines, 2),
  [27] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__lines, 2), SHIFT_REPEAT(6),
  [30] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__lines, 2), SHIFT_REPEAT(7),
  [33] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__lines, 2), SHIFT_REPEAT(29),
  [36] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__lines, 2), SHIFT_REPEAT(21),
  [39] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__lines, 2), SHIFT_REPEAT(4),
  [42] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [44] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [46] = {.entry = {.count = 1, .reusable = false}}, SHIFT(16),
  [48] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__line, 5),
  [50] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__line, 5),
  [52] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__line, 4),
  [54] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__line, 4),
  [56] = {.entry = {.count = 1, .reusable = false}}, SHIFT(13),
  [58] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [60] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__line, 2),
  [62] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__line, 2),
  [64] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__line, 3),
  [66] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__line, 3),
  [68] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [70] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_hex_argument_repeat1, 2),
  [72] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_hex_argument_repeat1, 2), SHIFT_REPEAT(14),
  [75] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_hex_argument_repeat1, 2),
  [77] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_hex_argument, 2),
  [79] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [81] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_hex_argument, 2),
  [83] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_comment_repeat1, 2), SHIFT_REPEAT(17),
  [86] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_comment_repeat1, 2), SHIFT_REPEAT(17),
  [89] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_comment_repeat1, 2),
  [91] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [93] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [95] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [97] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_indexes_repeat1, 2), SHIFT_REPEAT(53),
  [100] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_indexes_repeat1, 2), SHIFT_REPEAT(34),
  [103] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_indexes_repeat1, 2),
  [105] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [107] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [109] = {.entry = {.count = 1, .reusable = false}}, SHIFT(24),
  [111] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [113] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comment, 1),
  [115] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [117] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [119] = {.entry = {.count = 1, .reusable = false}}, SHIFT(17),
  [121] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [123] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comment, 2),
  [125] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_indexes_repeat1, 4),
  [127] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_indexes_repeat1, 3),
  [129] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [131] = {.entry = {.count = 1, .reusable = false}}, SHIFT(5),
  [133] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 3),
  [135] = {.entry = {.count = 1, .reusable = false}}, SHIFT(3),
  [137] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 1),
  [139] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_command_repeat1, 2), SHIFT_REPEAT(5),
  [142] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_command_repeat1, 2),
  [144] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 2),
  [146] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 4),
  [148] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [150] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [152] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [154] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_indexes, 3),
  [156] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_indexes, 3),
  [158] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_indexes, 4),
  [160] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_indexes, 4),
  [162] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [164] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [166] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_indexes, 5),
  [168] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_indexes, 5),
  [170] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [172] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_command_repeat1, 2),
  [174] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_indexes, 6),
  [176] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_indexes, 6),
  [178] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [180] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [182] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [184] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [186] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [188] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_xtc(void) {
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
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
