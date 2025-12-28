#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 74
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 40
#define ALIAS_COUNT 0
#define TOKEN_COUNT 20
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 8
#define MAX_ALIAS_SEQUENCE_LENGTH 6
#define PRODUCTION_ID_COUNT 11

enum {
  anon_sym_CHIP = 1,
  anon_sym_LBRACE = 2,
  anon_sym_RBRACE = 3,
  anon_sym_IN = 4,
  anon_sym_COMMA = 5,
  anon_sym_SEMI = 6,
  anon_sym_OUT = 7,
  anon_sym_LBRACK = 8,
  anon_sym_RBRACK = 9,
  anon_sym_BUILTIN = 10,
  anon_sym_CLOCKED = 11,
  anon_sym_PARTS = 12,
  anon_sym_COLON = 13,
  anon_sym_LPAREN = 14,
  anon_sym_RPAREN = 15,
  anon_sym_EQ = 16,
  sym_identifier = 17,
  sym_number = 18,
  sym_comment = 19,
  sym_source_file = 20,
  sym__definition = 21,
  sym_chip_definition = 22,
  sym_chip_header = 23,
  sym_in_section = 24,
  sym_out_section = 25,
  sym_bus_identifier = 26,
  sym_chip_body = 27,
  sym_builtin_body = 28,
  sym_clocked_body = 29,
  sym_parts_body = 30,
  sym_part = 31,
  sym_connection = 32,
  aux_sym_source_file_repeat1 = 33,
  aux_sym_in_section_repeat1 = 34,
  aux_sym_out_section_repeat1 = 35,
  aux_sym_chip_body_repeat1 = 36,
  aux_sym_clocked_body_repeat1 = 37,
  aux_sym_parts_body_repeat1 = 38,
  aux_sym_part_repeat1 = 39,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_CHIP] = "CHIP",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_IN] = "IN",
  [anon_sym_COMMA] = ",",
  [anon_sym_SEMI] = ";",
  [anon_sym_OUT] = "OUT",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [anon_sym_BUILTIN] = "BUILTIN",
  [anon_sym_CLOCKED] = "CLOCKED",
  [anon_sym_PARTS] = "PARTS",
  [anon_sym_COLON] = ":",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_EQ] = "=",
  [sym_identifier] = "identifier",
  [sym_number] = "number",
  [sym_comment] = "comment",
  [sym_source_file] = "source_file",
  [sym__definition] = "_definition",
  [sym_chip_definition] = "chip_definition",
  [sym_chip_header] = "chip_header",
  [sym_in_section] = "in_section",
  [sym_out_section] = "out_section",
  [sym_bus_identifier] = "bus_identifier",
  [sym_chip_body] = "chip_body",
  [sym_builtin_body] = "builtin_body",
  [sym_clocked_body] = "clocked_body",
  [sym_parts_body] = "parts_body",
  [sym_part] = "part",
  [sym_connection] = "connection",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_in_section_repeat1] = "in_section_repeat1",
  [aux_sym_out_section_repeat1] = "out_section_repeat1",
  [aux_sym_chip_body_repeat1] = "chip_body_repeat1",
  [aux_sym_clocked_body_repeat1] = "clocked_body_repeat1",
  [aux_sym_parts_body_repeat1] = "parts_body_repeat1",
  [aux_sym_part_repeat1] = "part_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_CHIP] = anon_sym_CHIP,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_IN] = anon_sym_IN,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_OUT] = anon_sym_OUT,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [anon_sym_BUILTIN] = anon_sym_BUILTIN,
  [anon_sym_CLOCKED] = anon_sym_CLOCKED,
  [anon_sym_PARTS] = anon_sym_PARTS,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_EQ] = anon_sym_EQ,
  [sym_identifier] = sym_identifier,
  [sym_number] = sym_number,
  [sym_comment] = sym_comment,
  [sym_source_file] = sym_source_file,
  [sym__definition] = sym__definition,
  [sym_chip_definition] = sym_chip_definition,
  [sym_chip_header] = sym_chip_header,
  [sym_in_section] = sym_in_section,
  [sym_out_section] = sym_out_section,
  [sym_bus_identifier] = sym_bus_identifier,
  [sym_chip_body] = sym_chip_body,
  [sym_builtin_body] = sym_builtin_body,
  [sym_clocked_body] = sym_clocked_body,
  [sym_parts_body] = sym_parts_body,
  [sym_part] = sym_part,
  [sym_connection] = sym_connection,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_in_section_repeat1] = aux_sym_in_section_repeat1,
  [aux_sym_out_section_repeat1] = aux_sym_out_section_repeat1,
  [aux_sym_chip_body_repeat1] = aux_sym_chip_body_repeat1,
  [aux_sym_clocked_body_repeat1] = aux_sym_clocked_body_repeat1,
  [aux_sym_parts_body_repeat1] = aux_sym_parts_body_repeat1,
  [aux_sym_part_repeat1] = aux_sym_part_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_CHIP] = {
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
  [anon_sym_IN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SEMI] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_OUT] = {
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
  [anon_sym_BUILTIN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_CLOCKED] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PARTS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
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
  [anon_sym_EQ] = {
    .visible = true,
    .named = false,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym__definition] = {
    .visible = false,
    .named = true,
  },
  [sym_chip_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_chip_header] = {
    .visible = true,
    .named = true,
  },
  [sym_in_section] = {
    .visible = true,
    .named = true,
  },
  [sym_out_section] = {
    .visible = true,
    .named = true,
  },
  [sym_bus_identifier] = {
    .visible = true,
    .named = true,
  },
  [sym_chip_body] = {
    .visible = true,
    .named = true,
  },
  [sym_builtin_body] = {
    .visible = true,
    .named = true,
  },
  [sym_clocked_body] = {
    .visible = true,
    .named = true,
  },
  [sym_parts_body] = {
    .visible = true,
    .named = true,
  },
  [sym_part] = {
    .visible = true,
    .named = true,
  },
  [sym_connection] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_in_section_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_out_section_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_chip_body_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_clocked_body_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_parts_body_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_part_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum {
  field_body = 1,
  field_chip_name = 2,
  field_chip_pin = 3,
  field_header = 4,
  field_input_pin_name = 5,
  field_name = 6,
  field_output_pin_name = 7,
  field_part_pin = 8,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_body] = "body",
  [field_chip_name] = "chip_name",
  [field_chip_pin] = "chip_pin",
  [field_header] = "header",
  [field_input_pin_name] = "input_pin_name",
  [field_name] = "name",
  [field_output_pin_name] = "output_pin_name",
  [field_part_pin] = "part_pin",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 3},
  [3] = {.index = 4, .length = 2},
  [4] = {.index = 6, .length = 2},
  [5] = {.index = 8, .length = 1},
  [6] = {.index = 9, .length = 1},
  [7] = {.index = 10, .length = 2},
  [8] = {.index = 12, .length = 2},
  [9] = {.index = 14, .length = 1},
  [10] = {.index = 15, .length = 2},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_input_pin_name, 1},
  [1] =
    {field_body, 4},
    {field_header, 3},
    {field_name, 1},
  [4] =
    {field_input_pin_name, 1},
    {field_input_pin_name, 2, .inherited = true},
  [6] =
    {field_input_pin_name, 0, .inherited = true},
    {field_input_pin_name, 1, .inherited = true},
  [8] =
    {field_chip_name, 1},
  [9] =
    {field_output_pin_name, 1},
  [10] =
    {field_output_pin_name, 1},
    {field_output_pin_name, 2, .inherited = true},
  [12] =
    {field_output_pin_name, 0, .inherited = true},
    {field_output_pin_name, 1, .inherited = true},
  [14] =
    {field_chip_name, 0},
  [15] =
    {field_chip_pin, 2},
    {field_part_pin, 0},
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
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(28);
      if (lookahead == '(') ADVANCE(45);
      if (lookahead == ')') ADVANCE(46);
      if (lookahead == ',') ADVANCE(33);
      if (lookahead == '/') ADVANCE(2);
      if (lookahead == ':') ADVANCE(44);
      if (lookahead == ';') ADVANCE(34);
      if (lookahead == '=') ADVANCE(47);
      if (lookahead == 'B') ADVANCE(26);
      if (lookahead == 'C') ADVANCE(11);
      if (lookahead == 'I') ADVANCE(17);
      if (lookahead == 'O') ADVANCE(27);
      if (lookahead == 'P') ADVANCE(7);
      if (lookahead == '[') ADVANCE(36);
      if (lookahead == ']') ADVANCE(37);
      if (lookahead == '{') ADVANCE(30);
      if (lookahead == '}') ADVANCE(31);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(0)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(65);
      END_STATE();
    case 1:
      if (lookahead == ')') ADVANCE(46);
      if (lookahead == '/') ADVANCE(2);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(1)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(64);
      END_STATE();
    case 2:
      if (lookahead == '*') ADVANCE(3);
      if (lookahead == '/') ADVANCE(67);
      END_STATE();
    case 3:
      if (lookahead == '*') ADVANCE(4);
      END_STATE();
    case 4:
      if (lookahead == '*') ADVANCE(6);
      if (lookahead != 0) ADVANCE(4);
      END_STATE();
    case 5:
      if (lookahead == '/') ADVANCE(2);
      if (lookahead == 'B') ADVANCE(63);
      if (lookahead == 'C') ADVANCE(55);
      if (lookahead == 'P') ADVANCE(48);
      if (lookahead == '}') ADVANCE(31);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(5)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(64);
      END_STATE();
    case 6:
      if (lookahead == '/') ADVANCE(66);
      if (lookahead != 0) ADVANCE(4);
      END_STATE();
    case 7:
      if (lookahead == 'A') ADVANCE(21);
      END_STATE();
    case 8:
      if (lookahead == 'C') ADVANCE(15);
      END_STATE();
    case 9:
      if (lookahead == 'D') ADVANCE(40);
      END_STATE();
    case 10:
      if (lookahead == 'E') ADVANCE(9);
      END_STATE();
    case 11:
      if (lookahead == 'H') ADVANCE(13);
      if (lookahead == 'L') ADVANCE(19);
      END_STATE();
    case 12:
      if (lookahead == 'I') ADVANCE(16);
      END_STATE();
    case 13:
      if (lookahead == 'I') ADVANCE(20);
      END_STATE();
    case 14:
      if (lookahead == 'I') ADVANCE(18);
      END_STATE();
    case 15:
      if (lookahead == 'K') ADVANCE(10);
      END_STATE();
    case 16:
      if (lookahead == 'L') ADVANCE(25);
      END_STATE();
    case 17:
      if (lookahead == 'N') ADVANCE(32);
      END_STATE();
    case 18:
      if (lookahead == 'N') ADVANCE(38);
      END_STATE();
    case 19:
      if (lookahead == 'O') ADVANCE(8);
      END_STATE();
    case 20:
      if (lookahead == 'P') ADVANCE(29);
      END_STATE();
    case 21:
      if (lookahead == 'R') ADVANCE(24);
      END_STATE();
    case 22:
      if (lookahead == 'S') ADVANCE(42);
      END_STATE();
    case 23:
      if (lookahead == 'T') ADVANCE(35);
      END_STATE();
    case 24:
      if (lookahead == 'T') ADVANCE(22);
      END_STATE();
    case 25:
      if (lookahead == 'T') ADVANCE(14);
      END_STATE();
    case 26:
      if (lookahead == 'U') ADVANCE(12);
      END_STATE();
    case 27:
      if (lookahead == 'U') ADVANCE(23);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(anon_sym_CHIP);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(anon_sym_IN);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(anon_sym_OUT);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(anon_sym_BUILTIN);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(anon_sym_BUILTIN);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(64);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(anon_sym_CLOCKED);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(anon_sym_CLOCKED);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(64);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(anon_sym_PARTS);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(anon_sym_PARTS);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(64);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'A') ADVANCE(59);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(64);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'C') ADVANCE(54);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(64);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'D') ADVANCE(41);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(64);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'E') ADVANCE(50);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(64);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'I') ADVANCE(57);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(64);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'I') ADVANCE(56);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(64);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'K') ADVANCE(51);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(64);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'L') ADVANCE(58);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(64);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'L') ADVANCE(62);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(64);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'N') ADVANCE(39);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(64);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'O') ADVANCE(49);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(64);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'R') ADVANCE(61);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(64);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'S') ADVANCE(43);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(64);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'T') ADVANCE(60);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(64);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'T') ADVANCE(52);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(64);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'U') ADVANCE(53);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(64);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(64);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(65);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(67);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 0},
  [3] = {.lex_state = 0},
  [4] = {.lex_state = 0},
  [5] = {.lex_state = 5},
  [6] = {.lex_state = 5},
  [7] = {.lex_state = 5},
  [8] = {.lex_state = 5},
  [9] = {.lex_state = 5},
  [10] = {.lex_state = 0},
  [11] = {.lex_state = 5},
  [12] = {.lex_state = 0},
  [13] = {.lex_state = 0},
  [14] = {.lex_state = 0},
  [15] = {.lex_state = 0},
  [16] = {.lex_state = 0},
  [17] = {.lex_state = 0},
  [18] = {.lex_state = 0},
  [19] = {.lex_state = 0},
  [20] = {.lex_state = 0},
  [21] = {.lex_state = 0},
  [22] = {.lex_state = 0},
  [23] = {.lex_state = 0},
  [24] = {.lex_state = 0},
  [25] = {.lex_state = 0},
  [26] = {.lex_state = 0},
  [27] = {.lex_state = 0},
  [28] = {.lex_state = 0},
  [29] = {.lex_state = 0},
  [30] = {.lex_state = 0},
  [31] = {.lex_state = 0},
  [32] = {.lex_state = 0},
  [33] = {.lex_state = 0},
  [34] = {.lex_state = 1},
  [35] = {.lex_state = 0},
  [36] = {.lex_state = 0},
  [37] = {.lex_state = 0},
  [38] = {.lex_state = 0},
  [39] = {.lex_state = 0},
  [40] = {.lex_state = 0},
  [41] = {.lex_state = 0},
  [42] = {.lex_state = 0},
  [43] = {.lex_state = 0},
  [44] = {.lex_state = 1},
  [45] = {.lex_state = 0},
  [46] = {.lex_state = 1},
  [47] = {.lex_state = 1},
  [48] = {.lex_state = 1},
  [49] = {.lex_state = 0},
  [50] = {.lex_state = 1},
  [51] = {.lex_state = 0},
  [52] = {.lex_state = 0},
  [53] = {.lex_state = 0},
  [54] = {.lex_state = 1},
  [55] = {.lex_state = 0},
  [56] = {.lex_state = 1},
  [57] = {.lex_state = 0},
  [58] = {.lex_state = 0},
  [59] = {.lex_state = 0},
  [60] = {.lex_state = 0},
  [61] = {.lex_state = 0},
  [62] = {.lex_state = 0},
  [63] = {.lex_state = 0},
  [64] = {.lex_state = 0},
  [65] = {.lex_state = 0},
  [66] = {.lex_state = 1},
  [67] = {.lex_state = 1},
  [68] = {.lex_state = 0},
  [69] = {.lex_state = 1},
  [70] = {.lex_state = 0},
  [71] = {.lex_state = 0},
  [72] = {.lex_state = 0},
  [73] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_CHIP] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_IN] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_OUT] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [anon_sym_BUILTIN] = ACTIONS(1),
    [anon_sym_CLOCKED] = ACTIONS(1),
    [anon_sym_PARTS] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [sym_number] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
  },
  [1] = {
    [sym_source_file] = STATE(73),
    [sym__definition] = STATE(10),
    [sym_chip_definition] = STATE(10),
    [aux_sym_source_file_repeat1] = STATE(10),
    [ts_builtin_sym_end] = ACTIONS(5),
    [anon_sym_CHIP] = ACTIONS(7),
    [sym_comment] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(9), 1,
      anon_sym_BUILTIN,
    ACTIONS(11), 1,
      anon_sym_CLOCKED,
    ACTIONS(13), 1,
      anon_sym_PARTS,
    STATE(72), 1,
      sym_chip_body,
    STATE(4), 4,
      sym_builtin_body,
      sym_clocked_body,
      sym_parts_body,
      aux_sym_chip_body_repeat1,
  [22] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(15), 1,
      anon_sym_RBRACE,
    ACTIONS(17), 1,
      anon_sym_BUILTIN,
    ACTIONS(20), 1,
      anon_sym_CLOCKED,
    ACTIONS(23), 1,
      anon_sym_PARTS,
    STATE(3), 4,
      sym_builtin_body,
      sym_clocked_body,
      sym_parts_body,
      aux_sym_chip_body_repeat1,
  [44] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(9), 1,
      anon_sym_BUILTIN,
    ACTIONS(11), 1,
      anon_sym_CLOCKED,
    ACTIONS(13), 1,
      anon_sym_PARTS,
    ACTIONS(26), 1,
      anon_sym_RBRACE,
    STATE(3), 4,
      sym_builtin_body,
      sym_clocked_body,
      sym_parts_body,
      aux_sym_chip_body_repeat1,
  [66] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(28), 1,
      anon_sym_RBRACE,
    ACTIONS(32), 1,
      sym_identifier,
    STATE(7), 2,
      sym_part,
      aux_sym_parts_body_repeat1,
    ACTIONS(30), 3,
      anon_sym_BUILTIN,
      anon_sym_CLOCKED,
      anon_sym_PARTS,
  [85] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(34), 1,
      anon_sym_RBRACE,
    ACTIONS(38), 1,
      sym_identifier,
    STATE(6), 2,
      sym_part,
      aux_sym_parts_body_repeat1,
    ACTIONS(36), 3,
      anon_sym_BUILTIN,
      anon_sym_CLOCKED,
      anon_sym_PARTS,
  [104] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(32), 1,
      sym_identifier,
    ACTIONS(41), 1,
      anon_sym_RBRACE,
    STATE(6), 2,
      sym_part,
      aux_sym_parts_body_repeat1,
    ACTIONS(43), 3,
      anon_sym_BUILTIN,
      anon_sym_CLOCKED,
      anon_sym_PARTS,
  [123] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(45), 1,
      anon_sym_RBRACE,
    ACTIONS(47), 4,
      anon_sym_BUILTIN,
      anon_sym_CLOCKED,
      anon_sym_PARTS,
      sym_identifier,
  [136] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(49), 1,
      anon_sym_RBRACE,
    ACTIONS(51), 4,
      anon_sym_BUILTIN,
      anon_sym_CLOCKED,
      anon_sym_PARTS,
      sym_identifier,
  [149] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      anon_sym_CHIP,
    ACTIONS(53), 1,
      ts_builtin_sym_end,
    STATE(12), 3,
      sym__definition,
      sym_chip_definition,
      aux_sym_source_file_repeat1,
  [164] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_RBRACE,
    ACTIONS(57), 4,
      anon_sym_BUILTIN,
      anon_sym_CLOCKED,
      anon_sym_PARTS,
      sym_identifier,
  [177] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(59), 1,
      ts_builtin_sym_end,
    ACTIONS(61), 1,
      anon_sym_CHIP,
    STATE(12), 3,
      sym__definition,
      sym_chip_definition,
      aux_sym_source_file_repeat1,
  [192] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(64), 4,
      anon_sym_RBRACE,
      anon_sym_BUILTIN,
      anon_sym_CLOCKED,
      anon_sym_PARTS,
  [202] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(66), 1,
      anon_sym_COMMA,
    ACTIONS(68), 1,
      anon_sym_SEMI,
    ACTIONS(70), 1,
      anon_sym_LBRACK,
    STATE(26), 1,
      aux_sym_in_section_repeat1,
  [218] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(72), 4,
      anon_sym_RBRACE,
      anon_sym_BUILTIN,
      anon_sym_CLOCKED,
      anon_sym_PARTS,
  [228] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(74), 4,
      anon_sym_RBRACE,
      anon_sym_BUILTIN,
      anon_sym_CLOCKED,
      anon_sym_PARTS,
  [238] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(70), 1,
      anon_sym_LBRACK,
    ACTIONS(76), 1,
      anon_sym_COMMA,
    ACTIONS(78), 1,
      anon_sym_SEMI,
    STATE(19), 1,
      aux_sym_out_section_repeat1,
  [254] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(70), 1,
      anon_sym_LBRACK,
    ACTIONS(80), 2,
      anon_sym_COMMA,
      anon_sym_SEMI,
  [265] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(76), 1,
      anon_sym_COMMA,
    ACTIONS(82), 1,
      anon_sym_SEMI,
    STATE(30), 1,
      aux_sym_out_section_repeat1,
  [278] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(84), 1,
      anon_sym_COMMA,
    ACTIONS(87), 1,
      anon_sym_RPAREN,
    STATE(20), 1,
      aux_sym_part_repeat1,
  [291] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(70), 1,
      anon_sym_LBRACK,
    ACTIONS(89), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [302] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(91), 3,
      anon_sym_BUILTIN,
      anon_sym_CLOCKED,
      anon_sym_PARTS,
  [311] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      anon_sym_COMMA,
    ACTIONS(95), 1,
      anon_sym_RPAREN,
    STATE(20), 1,
      aux_sym_part_repeat1,
  [324] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(97), 1,
      anon_sym_IN,
    STATE(2), 1,
      sym_chip_header,
    STATE(53), 1,
      sym_in_section,
  [337] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      anon_sym_COMMA,
    ACTIONS(99), 1,
      anon_sym_RPAREN,
    STATE(23), 1,
      aux_sym_part_repeat1,
  [350] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(66), 1,
      anon_sym_COMMA,
    ACTIONS(101), 1,
      anon_sym_SEMI,
    STATE(36), 1,
      aux_sym_in_section_repeat1,
  [363] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(66), 1,
      anon_sym_COMMA,
    ACTIONS(103), 1,
      anon_sym_SEMI,
    STATE(36), 1,
      aux_sym_in_section_repeat1,
  [376] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(105), 3,
      anon_sym_BUILTIN,
      anon_sym_CLOCKED,
      anon_sym_PARTS,
  [385] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 1,
      anon_sym_COMMA,
    ACTIONS(109), 1,
      anon_sym_SEMI,
    STATE(41), 1,
      aux_sym_clocked_body_repeat1,
  [398] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(111), 1,
      anon_sym_COMMA,
    ACTIONS(114), 1,
      anon_sym_SEMI,
    STATE(30), 1,
      aux_sym_out_section_repeat1,
  [411] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(76), 1,
      anon_sym_COMMA,
    ACTIONS(78), 1,
      anon_sym_SEMI,
    STATE(39), 1,
      aux_sym_out_section_repeat1,
  [424] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(70), 1,
      anon_sym_LBRACK,
    ACTIONS(116), 2,
      anon_sym_COMMA,
      anon_sym_SEMI,
  [435] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(105), 3,
      anon_sym_BUILTIN,
      anon_sym_CLOCKED,
      anon_sym_PARTS,
  [444] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(118), 1,
      anon_sym_RPAREN,
    ACTIONS(120), 1,
      sym_identifier,
    STATE(25), 1,
      sym_connection,
  [457] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(122), 1,
      anon_sym_COMMA,
    ACTIONS(125), 1,
      anon_sym_SEMI,
    STATE(35), 1,
      aux_sym_clocked_body_repeat1,
  [470] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(127), 1,
      anon_sym_COMMA,
    ACTIONS(130), 1,
      anon_sym_SEMI,
    STATE(36), 1,
      aux_sym_in_section_repeat1,
  [483] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(66), 1,
      anon_sym_COMMA,
    ACTIONS(68), 1,
      anon_sym_SEMI,
    STATE(27), 1,
      aux_sym_in_section_repeat1,
  [496] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(132), 3,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
  [505] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(76), 1,
      anon_sym_COMMA,
    ACTIONS(134), 1,
      anon_sym_SEMI,
    STATE(30), 1,
      aux_sym_out_section_repeat1,
  [518] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(136), 3,
      anon_sym_BUILTIN,
      anon_sym_CLOCKED,
      anon_sym_PARTS,
  [527] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 1,
      anon_sym_COMMA,
    ACTIONS(138), 1,
      anon_sym_SEMI,
    STATE(35), 1,
      aux_sym_clocked_body_repeat1,
  [540] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(80), 2,
      anon_sym_COMMA,
      anon_sym_SEMI,
  [548] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(87), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [556] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(140), 1,
      sym_identifier,
    STATE(42), 1,
      sym_bus_identifier,
  [566] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(89), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [574] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(142), 1,
      sym_identifier,
    STATE(31), 1,
      sym_bus_identifier,
  [584] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(144), 1,
      sym_identifier,
    STATE(52), 1,
      sym_bus_identifier,
  [594] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(120), 1,
      sym_identifier,
    STATE(43), 1,
      sym_connection,
  [604] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(125), 2,
      anon_sym_COMMA,
      anon_sym_SEMI,
  [612] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(146), 1,
      sym_identifier,
    STATE(45), 1,
      sym_bus_identifier,
  [622] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(148), 2,
      ts_builtin_sym_end,
      anon_sym_CHIP,
  [630] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(116), 2,
      anon_sym_COMMA,
      anon_sym_SEMI,
  [638] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(150), 1,
      anon_sym_OUT,
    STATE(22), 1,
      sym_out_section,
  [648] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(152), 1,
      sym_identifier,
    STATE(37), 1,
      sym_bus_identifier,
  [658] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(154), 1,
      anon_sym_OUT,
  [665] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(156), 1,
      sym_identifier,
  [672] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(158), 1,
      anon_sym_RBRACK,
  [679] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(160), 1,
      anon_sym_SEMI,
  [686] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(162), 1,
      anon_sym_SEMI,
  [693] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(164), 1,
      anon_sym_EQ,
  [700] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(166), 1,
      sym_number,
  [707] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(168), 1,
      anon_sym_OUT,
  [714] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(154), 1,
      anon_sym_OUT,
  [721] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(170), 1,
      anon_sym_LPAREN,
  [728] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(172), 1,
      anon_sym_SEMI,
  [735] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(174), 1,
      sym_identifier,
  [742] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(176), 1,
      sym_identifier,
  [749] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(178), 1,
      anon_sym_COLON,
  [756] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(180), 1,
      sym_identifier,
  [763] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(182), 1,
      anon_sym_LBRACE,
  [770] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(184), 1,
      anon_sym_SEMI,
  [777] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(186), 1,
      anon_sym_RBRACE,
  [784] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(188), 1,
      ts_builtin_sym_end,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 22,
  [SMALL_STATE(4)] = 44,
  [SMALL_STATE(5)] = 66,
  [SMALL_STATE(6)] = 85,
  [SMALL_STATE(7)] = 104,
  [SMALL_STATE(8)] = 123,
  [SMALL_STATE(9)] = 136,
  [SMALL_STATE(10)] = 149,
  [SMALL_STATE(11)] = 164,
  [SMALL_STATE(12)] = 177,
  [SMALL_STATE(13)] = 192,
  [SMALL_STATE(14)] = 202,
  [SMALL_STATE(15)] = 218,
  [SMALL_STATE(16)] = 228,
  [SMALL_STATE(17)] = 238,
  [SMALL_STATE(18)] = 254,
  [SMALL_STATE(19)] = 265,
  [SMALL_STATE(20)] = 278,
  [SMALL_STATE(21)] = 291,
  [SMALL_STATE(22)] = 302,
  [SMALL_STATE(23)] = 311,
  [SMALL_STATE(24)] = 324,
  [SMALL_STATE(25)] = 337,
  [SMALL_STATE(26)] = 350,
  [SMALL_STATE(27)] = 363,
  [SMALL_STATE(28)] = 376,
  [SMALL_STATE(29)] = 385,
  [SMALL_STATE(30)] = 398,
  [SMALL_STATE(31)] = 411,
  [SMALL_STATE(32)] = 424,
  [SMALL_STATE(33)] = 435,
  [SMALL_STATE(34)] = 444,
  [SMALL_STATE(35)] = 457,
  [SMALL_STATE(36)] = 470,
  [SMALL_STATE(37)] = 483,
  [SMALL_STATE(38)] = 496,
  [SMALL_STATE(39)] = 505,
  [SMALL_STATE(40)] = 518,
  [SMALL_STATE(41)] = 527,
  [SMALL_STATE(42)] = 540,
  [SMALL_STATE(43)] = 548,
  [SMALL_STATE(44)] = 556,
  [SMALL_STATE(45)] = 566,
  [SMALL_STATE(46)] = 574,
  [SMALL_STATE(47)] = 584,
  [SMALL_STATE(48)] = 594,
  [SMALL_STATE(49)] = 604,
  [SMALL_STATE(50)] = 612,
  [SMALL_STATE(51)] = 622,
  [SMALL_STATE(52)] = 630,
  [SMALL_STATE(53)] = 638,
  [SMALL_STATE(54)] = 648,
  [SMALL_STATE(55)] = 658,
  [SMALL_STATE(56)] = 665,
  [SMALL_STATE(57)] = 672,
  [SMALL_STATE(58)] = 679,
  [SMALL_STATE(59)] = 686,
  [SMALL_STATE(60)] = 693,
  [SMALL_STATE(61)] = 700,
  [SMALL_STATE(62)] = 707,
  [SMALL_STATE(63)] = 714,
  [SMALL_STATE(64)] = 721,
  [SMALL_STATE(65)] = 728,
  [SMALL_STATE(66)] = 735,
  [SMALL_STATE(67)] = 742,
  [SMALL_STATE(68)] = 749,
  [SMALL_STATE(69)] = 756,
  [SMALL_STATE(70)] = 763,
  [SMALL_STATE(71)] = 770,
  [SMALL_STATE(72)] = 777,
  [SMALL_STATE(73)] = 784,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [15] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_chip_body_repeat1, 2),
  [17] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_chip_body_repeat1, 2), SHIFT_REPEAT(56),
  [20] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_chip_body_repeat1, 2), SHIFT_REPEAT(69),
  [23] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_chip_body_repeat1, 2), SHIFT_REPEAT(68),
  [26] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_chip_body, 1),
  [28] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parts_body, 2),
  [30] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_parts_body, 2),
  [32] = {.entry = {.count = 1, .reusable = false}}, SHIFT(64),
  [34] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_parts_body_repeat1, 2),
  [36] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_parts_body_repeat1, 2),
  [38] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_parts_body_repeat1, 2), SHIFT_REPEAT(64),
  [41] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parts_body, 3),
  [43] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_parts_body, 3),
  [45] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_part, 6, .production_id = 9),
  [47] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_part, 6, .production_id = 9),
  [49] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_part, 5, .production_id = 9),
  [51] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_part, 5, .production_id = 9),
  [53] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [55] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_part, 4, .production_id = 9),
  [57] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_part, 4, .production_id = 9),
  [59] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [61] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(66),
  [64] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_clocked_body, 4),
  [66] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [68] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [70] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [72] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_clocked_body, 3),
  [74] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_builtin_body, 3, .production_id = 5),
  [76] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [78] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [80] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_out_section_repeat1, 2, .production_id = 6),
  [82] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [84] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_part_repeat1, 2), SHIFT_REPEAT(48),
  [87] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_part_repeat1, 2),
  [89] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_connection, 3, .production_id = 10),
  [91] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_chip_header, 2),
  [93] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [95] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [97] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [99] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [101] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [103] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_out_section, 4, .production_id = 7),
  [107] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [109] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [111] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_out_section_repeat1, 2, .production_id = 8), SHIFT_REPEAT(44),
  [114] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_out_section_repeat1, 2, .production_id = 8),
  [116] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_in_section_repeat1, 2, .production_id = 1),
  [118] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [120] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [122] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_clocked_body_repeat1, 2), SHIFT_REPEAT(67),
  [125] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_clocked_body_repeat1, 2),
  [127] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_in_section_repeat1, 2, .production_id = 4), SHIFT_REPEAT(47),
  [130] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_in_section_repeat1, 2, .production_id = 4),
  [132] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bus_identifier, 4),
  [134] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [136] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_out_section, 3, .production_id = 6),
  [138] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [140] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [142] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [144] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [146] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [148] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_chip_definition, 6, .production_id = 2),
  [150] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [152] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [154] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_in_section, 4, .production_id = 3),
  [156] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [158] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [160] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [162] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [164] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [166] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [168] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_in_section, 3, .production_id = 1),
  [170] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [172] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [174] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [176] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [178] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [180] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [182] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [184] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [186] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [188] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_hdl(void) {
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
