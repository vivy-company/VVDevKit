#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 13
#define STATE_COUNT 103
#define LARGE_STATE_COUNT 8
#define SYMBOL_COUNT 41
#define ALIAS_COUNT 0
#define TOKEN_COUNT 24
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 2
#define MAX_ALIAS_SEQUENCE_LENGTH 5
#define PRODUCTION_ID_COUNT 2

enum {
  anon_sym_LT = 1,
  anon_sym_COMMA = 2,
  anon_sym_LF = 3,
  anon_sym_ = 4,
  anon_sym_TAB = 5,
  anon_sym_GT = 6,
  anon_sym_COLON = 7,
  anon_sym_LBRACE = 8,
  anon_sym_RBRACE = 9,
  anon_sym_i_LBRACE = 10,
  anon_sym_LBRACK = 11,
  anon_sym_RBRACK = 12,
  anon_sym_DQUOTE = 13,
  aux_sym_string_content_token1 = 14,
  sym_escape_sequence = 15,
  sym_number = 16,
  sym_datetime = 17,
  sym_true = 18,
  sym_hexblob = 19,
  sym_escblob = 20,
  sym_false = 21,
  sym_null = 22,
  sym_comment = 23,
  sym_document = 24,
  sym__value = 25,
  sym_meta = 26,
  sym_mpair = 27,
  sym_map = 28,
  sym_pair = 29,
  sym_imap = 30,
  sym_ipair = 31,
  sym_array = 32,
  sym_string = 33,
  sym_string_content = 34,
  aux_sym_meta_repeat1 = 35,
  aux_sym_meta_repeat2 = 36,
  aux_sym_map_repeat1 = 37,
  aux_sym_imap_repeat1 = 38,
  aux_sym_array_repeat1 = 39,
  aux_sym_string_content_repeat1 = 40,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_LT] = "<",
  [anon_sym_COMMA] = ",",
  [anon_sym_LF] = "\n",
  [anon_sym_] = " ",
  [anon_sym_TAB] = "\t",
  [anon_sym_GT] = ">",
  [anon_sym_COLON] = ":",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_i_LBRACE] = "i{",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [anon_sym_DQUOTE] = "\"",
  [aux_sym_string_content_token1] = "string_content_token1",
  [sym_escape_sequence] = "escape_sequence",
  [sym_number] = "number",
  [sym_datetime] = "datetime",
  [sym_true] = "true",
  [sym_hexblob] = "hexblob",
  [sym_escblob] = "escblob",
  [sym_false] = "false",
  [sym_null] = "null",
  [sym_comment] = "comment",
  [sym_document] = "document",
  [sym__value] = "_value",
  [sym_meta] = "meta",
  [sym_mpair] = "mpair",
  [sym_map] = "map",
  [sym_pair] = "pair",
  [sym_imap] = "imap",
  [sym_ipair] = "ipair",
  [sym_array] = "array",
  [sym_string] = "string",
  [sym_string_content] = "string_content",
  [aux_sym_meta_repeat1] = "meta_repeat1",
  [aux_sym_meta_repeat2] = "meta_repeat2",
  [aux_sym_map_repeat1] = "map_repeat1",
  [aux_sym_imap_repeat1] = "imap_repeat1",
  [aux_sym_array_repeat1] = "array_repeat1",
  [aux_sym_string_content_repeat1] = "string_content_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_LT] = anon_sym_LT,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_LF] = anon_sym_LF,
  [anon_sym_] = anon_sym_,
  [anon_sym_TAB] = anon_sym_TAB,
  [anon_sym_GT] = anon_sym_GT,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_i_LBRACE] = anon_sym_i_LBRACE,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [aux_sym_string_content_token1] = aux_sym_string_content_token1,
  [sym_escape_sequence] = sym_escape_sequence,
  [sym_number] = sym_number,
  [sym_datetime] = sym_datetime,
  [sym_true] = sym_true,
  [sym_hexblob] = sym_hexblob,
  [sym_escblob] = sym_escblob,
  [sym_false] = sym_false,
  [sym_null] = sym_null,
  [sym_comment] = sym_comment,
  [sym_document] = sym_document,
  [sym__value] = sym__value,
  [sym_meta] = sym_meta,
  [sym_mpair] = sym_mpair,
  [sym_map] = sym_map,
  [sym_pair] = sym_pair,
  [sym_imap] = sym_imap,
  [sym_ipair] = sym_ipair,
  [sym_array] = sym_array,
  [sym_string] = sym_string,
  [sym_string_content] = sym_string_content,
  [aux_sym_meta_repeat1] = aux_sym_meta_repeat1,
  [aux_sym_meta_repeat2] = aux_sym_meta_repeat2,
  [aux_sym_map_repeat1] = aux_sym_map_repeat1,
  [aux_sym_imap_repeat1] = aux_sym_imap_repeat1,
  [aux_sym_array_repeat1] = aux_sym_array_repeat1,
  [aux_sym_string_content_repeat1] = aux_sym_string_content_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_LT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LF] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_TAB] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
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
  [anon_sym_i_LBRACE] = {
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
  [anon_sym_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_string_content_token1] = {
    .visible = false,
    .named = false,
  },
  [sym_escape_sequence] = {
    .visible = true,
    .named = true,
  },
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [sym_datetime] = {
    .visible = true,
    .named = true,
  },
  [sym_true] = {
    .visible = true,
    .named = true,
  },
  [sym_hexblob] = {
    .visible = true,
    .named = true,
  },
  [sym_escblob] = {
    .visible = true,
    .named = true,
  },
  [sym_false] = {
    .visible = true,
    .named = true,
  },
  [sym_null] = {
    .visible = true,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_document] = {
    .visible = true,
    .named = true,
  },
  [sym__value] = {
    .visible = false,
    .named = true,
  },
  [sym_meta] = {
    .visible = true,
    .named = true,
  },
  [sym_mpair] = {
    .visible = true,
    .named = true,
  },
  [sym_map] = {
    .visible = true,
    .named = true,
  },
  [sym_pair] = {
    .visible = true,
    .named = true,
  },
  [sym_imap] = {
    .visible = true,
    .named = true,
  },
  [sym_ipair] = {
    .visible = true,
    .named = true,
  },
  [sym_array] = {
    .visible = true,
    .named = true,
  },
  [sym_string] = {
    .visible = true,
    .named = true,
  },
  [sym_string_content] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_meta_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_meta_repeat2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_map_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_imap_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_array_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_string_content_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum {
  field_key = 1,
  field_value = 2,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_key] = "key",
  [field_value] = "value",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 2},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_key, 0},
    {field_value, 2},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(66);
      if (lookahead == '"') ADVANCE(79);
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(19);
      if (lookahead == ',') ADVANCE(68);
      if (lookahead == '.') ADVANCE(49);
      if (lookahead == '/') ADVANCE(14);
      if (lookahead == '0') ADVANCE(90);
      if (lookahead == ':') ADVANCE(73);
      if (lookahead == '<') ADVANCE(67);
      if (lookahead == '>') ADVANCE(72);
      if (lookahead == '[') ADVANCE(77);
      if (lookahead == '\\') ADVANCE(45);
      if (lookahead == ']') ADVANCE(78);
      if (lookahead == 'b') ADVANCE(4);
      if (lookahead == 'd') ADVANCE(13);
      if (lookahead == 'f') ADVANCE(27);
      if (lookahead == 'i') ADVANCE(37);
      if (lookahead == 'n') ADVANCE(36);
      if (lookahead == 't') ADVANCE(33);
      if (lookahead == 'x') ADVANCE(5);
      if (lookahead == '{') ADVANCE(74);
      if (lookahead == '}') ADVANCE(75);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(65)
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(89);
      END_STATE();
    case 1:
      if (lookahead == '\t') ADVANCE(71);
      if (lookahead == '\n') ADVANCE(69);
      if (lookahead == '\r') SKIP(1)
      if (lookahead == ' ') ADVANCE(70);
      if (lookahead == '"') ADVANCE(79);
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(19);
      if (lookahead == ',') ADVANCE(68);
      if (lookahead == '.') ADVANCE(49);
      if (lookahead == '/') ADVANCE(14);
      if (lookahead == '0') ADVANCE(90);
      if (lookahead == '<') ADVANCE(67);
      if (lookahead == '>') ADVANCE(72);
      if (lookahead == '[') ADVANCE(77);
      if (lookahead == ']') ADVANCE(78);
      if (lookahead == 'b') ADVANCE(4);
      if (lookahead == 'd') ADVANCE(13);
      if (lookahead == 'f') ADVANCE(27);
      if (lookahead == 'i') ADVANCE(37);
      if (lookahead == 'n') ADVANCE(36);
      if (lookahead == 't') ADVANCE(33);
      if (lookahead == 'x') ADVANCE(5);
      if (lookahead == '{') ADVANCE(74);
      if (lookahead == '}') ADVANCE(75);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(89);
      END_STATE();
    case 2:
      if (lookahead == '\n') SKIP(3)
      if (lookahead == '"') ADVANCE(79);
      if (lookahead == '/') ADVANCE(80);
      if (lookahead == '\\') ADVANCE(45);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(83);
      if (lookahead != 0) ADVANCE(85);
      END_STATE();
    case 3:
      if (lookahead == '"') ADVANCE(79);
      if (lookahead == '/') ADVANCE(14);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(3)
      END_STATE();
    case 4:
      if (lookahead == '"') ADVANCE(7);
      END_STATE();
    case 5:
      if (lookahead == '"') ADVANCE(8);
      END_STATE();
    case 6:
      if (lookahead == '"') ADVANCE(99);
      if (lookahead == '\\') ADVANCE(6);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(7);
      if ((' ' <= lookahead && lookahead <= '~')) ADVANCE(7);
      END_STATE();
    case 7:
      if (lookahead == '"') ADVANCE(99);
      if (lookahead == '\\') ADVANCE(6);
      if ((' ' <= lookahead && lookahead <= '~')) ADVANCE(7);
      END_STATE();
    case 8:
      if (lookahead == '"') ADVANCE(98);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(63);
      END_STATE();
    case 9:
      if (lookahead == '"') ADVANCE(96);
      END_STATE();
    case 10:
      if (lookahead == '"') ADVANCE(96);
      if (lookahead == '.') ADVANCE(60);
      if (lookahead == 'Z') ADVANCE(9);
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(22);
      END_STATE();
    case 11:
      if (lookahead == '"') ADVANCE(96);
      if (lookahead == 'Z') ADVANCE(9);
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(22);
      END_STATE();
    case 12:
      if (lookahead == '"') ADVANCE(96);
      if (('0' <= lookahead && lookahead <= '5')) ADVANCE(57);
      END_STATE();
    case 13:
      if (lookahead == '"') ADVANCE(62);
      END_STATE();
    case 14:
      if (lookahead == '*') ADVANCE(16);
      if (lookahead == '/') ADVANCE(103);
      END_STATE();
    case 15:
      if (lookahead == '*') ADVANCE(15);
      if (lookahead == '/') ADVANCE(102);
      if (lookahead != 0) ADVANCE(16);
      END_STATE();
    case 16:
      if (lookahead == '*') ADVANCE(15);
      if (lookahead != 0) ADVANCE(16);
      END_STATE();
    case 17:
      if (lookahead == '-') ADVANCE(20);
      END_STATE();
    case 18:
      if (lookahead == '-') ADVANCE(21);
      END_STATE();
    case 19:
      if (lookahead == '0') ADVANCE(88);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(91);
      END_STATE();
    case 20:
      if (lookahead == '0') ADVANCE(48);
      if (lookahead == '1') ADVANCE(41);
      END_STATE();
    case 21:
      if (lookahead == '0') ADVANCE(46);
      if (lookahead == '3') ADVANCE(39);
      if (lookahead == '1' ||
          lookahead == '2') ADVANCE(52);
      END_STATE();
    case 22:
      if (lookahead == '0') ADVANCE(47);
      if (lookahead == '1') ADVANCE(40);
      END_STATE();
    case 23:
      if (lookahead == '0') ADVANCE(53);
      if (lookahead == '1') ADVANCE(53);
      if (lookahead == '2') ADVANCE(42);
      END_STATE();
    case 24:
      if (lookahead == ':') ADVANCE(44);
      END_STATE();
    case 25:
      if (lookahead == ':') ADVANCE(43);
      END_STATE();
    case 26:
      if (lookahead == 'T') ADVANCE(23);
      END_STATE();
    case 27:
      if (lookahead == 'a') ADVANCE(30);
      END_STATE();
    case 28:
      if (lookahead == 'e') ADVANCE(97);
      END_STATE();
    case 29:
      if (lookahead == 'e') ADVANCE(100);
      END_STATE();
    case 30:
      if (lookahead == 'l') ADVANCE(34);
      END_STATE();
    case 31:
      if (lookahead == 'l') ADVANCE(101);
      END_STATE();
    case 32:
      if (lookahead == 'l') ADVANCE(31);
      END_STATE();
    case 33:
      if (lookahead == 'r') ADVANCE(35);
      END_STATE();
    case 34:
      if (lookahead == 's') ADVANCE(29);
      END_STATE();
    case 35:
      if (lookahead == 'u') ADVANCE(28);
      END_STATE();
    case 36:
      if (lookahead == 'u') ADVANCE(32);
      END_STATE();
    case 37:
      if (lookahead == '{') ADVANCE(76);
      END_STATE();
    case 38:
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(50);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(95);
      END_STATE();
    case 39:
      if (lookahead == '0' ||
          lookahead == '1') ADVANCE(26);
      END_STATE();
    case 40:
      if (('0' <= lookahead && lookahead <= '2')) ADVANCE(12);
      END_STATE();
    case 41:
      if (('0' <= lookahead && lookahead <= '2')) ADVANCE(18);
      END_STATE();
    case 42:
      if (('0' <= lookahead && lookahead <= '3')) ADVANCE(24);
      END_STATE();
    case 43:
      if (('0' <= lookahead && lookahead <= '5')) ADVANCE(54);
      END_STATE();
    case 44:
      if (('0' <= lookahead && lookahead <= '5')) ADVANCE(61);
      END_STATE();
    case 45:
      if (lookahead == '"' ||
          lookahead == '/' ||
          lookahead == '\\' ||
          lookahead == 'b' ||
          lookahead == 'f' ||
          lookahead == 'n' ||
          lookahead == 'r' ||
          lookahead == 't') ADVANCE(86);
      END_STATE();
    case 46:
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(26);
      END_STATE();
    case 47:
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(12);
      END_STATE();
    case 48:
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(18);
      END_STATE();
    case 49:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(94);
      END_STATE();
    case 50:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(95);
      END_STATE();
    case 51:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(17);
      END_STATE();
    case 52:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(26);
      END_STATE();
    case 53:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(24);
      END_STATE();
    case 54:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(10);
      END_STATE();
    case 55:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(11);
      END_STATE();
    case 56:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(51);
      END_STATE();
    case 57:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(9);
      END_STATE();
    case 58:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(55);
      END_STATE();
    case 59:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(56);
      END_STATE();
    case 60:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(58);
      END_STATE();
    case 61:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(25);
      END_STATE();
    case 62:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(59);
      END_STATE();
    case 63:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(8);
      END_STATE();
    case 64:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(93);
      END_STATE();
    case 65:
      if (eof) ADVANCE(66);
      if (lookahead == '"') ADVANCE(79);
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(19);
      if (lookahead == ',') ADVANCE(68);
      if (lookahead == '.') ADVANCE(49);
      if (lookahead == '/') ADVANCE(14);
      if (lookahead == '0') ADVANCE(90);
      if (lookahead == ':') ADVANCE(73);
      if (lookahead == '<') ADVANCE(67);
      if (lookahead == '>') ADVANCE(72);
      if (lookahead == '[') ADVANCE(77);
      if (lookahead == ']') ADVANCE(78);
      if (lookahead == 'b') ADVANCE(4);
      if (lookahead == 'd') ADVANCE(13);
      if (lookahead == 'f') ADVANCE(27);
      if (lookahead == 'i') ADVANCE(37);
      if (lookahead == 'n') ADVANCE(36);
      if (lookahead == 't') ADVANCE(33);
      if (lookahead == 'x') ADVANCE(5);
      if (lookahead == '{') ADVANCE(74);
      if (lookahead == '}') ADVANCE(75);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(65)
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(89);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(anon_sym_LT);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(anon_sym_LF);
      if (lookahead == '\t') ADVANCE(71);
      if (lookahead == '\n') ADVANCE(69);
      if (lookahead == ' ') ADVANCE(70);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(anon_sym_);
      if (lookahead == '\t') ADVANCE(71);
      if (lookahead == '\n') ADVANCE(69);
      if (lookahead == ' ') ADVANCE(70);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(anon_sym_TAB);
      if (lookahead == '\t') ADVANCE(71);
      if (lookahead == '\n') ADVANCE(69);
      if (lookahead == ' ') ADVANCE(70);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(anon_sym_GT);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(anon_sym_i_LBRACE);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(aux_sym_string_content_token1);
      if (lookahead == '*') ADVANCE(82);
      if (lookahead == '/') ADVANCE(84);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(85);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(aux_sym_string_content_token1);
      if (lookahead == '*') ADVANCE(81);
      if (lookahead == '/') ADVANCE(85);
      if (lookahead == '\n' ||
          lookahead == '"' ||
          lookahead == '\\') ADVANCE(16);
      if (lookahead != 0) ADVANCE(82);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(aux_sym_string_content_token1);
      if (lookahead == '*') ADVANCE(81);
      if (lookahead == '\n' ||
          lookahead == '"' ||
          lookahead == '\\') ADVANCE(16);
      if (lookahead != 0) ADVANCE(82);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(aux_sym_string_content_token1);
      if (lookahead == '/') ADVANCE(80);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(83);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(85);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(aux_sym_string_content_token1);
      if (lookahead == '"' ||
          lookahead == '\\') ADVANCE(103);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(84);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(aux_sym_string_content_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(85);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(sym_escape_sequence);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(sym_number);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(94);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(38);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(94);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(38);
      if (lookahead == 'u') ADVANCE(87);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(89);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(94);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(38);
      if (lookahead == 'X' ||
          lookahead == 'x') ADVANCE(64);
      if (lookahead == 'u') ADVANCE(87);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(92);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(94);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(38);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(91);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == 'u') ADVANCE(87);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(92);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == 'u') ADVANCE(87);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(93);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(38);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(94);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(95);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(sym_datetime);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(sym_true);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(sym_hexblob);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(sym_escblob);
      if (lookahead == '"') ADVANCE(99);
      if (lookahead == '\\') ADVANCE(6);
      if ((' ' <= lookahead && lookahead <= '~')) ADVANCE(7);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(sym_false);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(sym_null);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(103);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 1},
  [3] = {.lex_state = 1},
  [4] = {.lex_state = 1},
  [5] = {.lex_state = 1},
  [6] = {.lex_state = 1},
  [7] = {.lex_state = 1},
  [8] = {.lex_state = 0},
  [9] = {.lex_state = 0},
  [10] = {.lex_state = 0},
  [11] = {.lex_state = 0},
  [12] = {.lex_state = 0},
  [13] = {.lex_state = 0},
  [14] = {.lex_state = 0},
  [15] = {.lex_state = 0},
  [16] = {.lex_state = 0},
  [17] = {.lex_state = 0},
  [18] = {.lex_state = 0},
  [19] = {.lex_state = 1},
  [20] = {.lex_state = 1},
  [21] = {.lex_state = 1},
  [22] = {.lex_state = 1},
  [23] = {.lex_state = 1},
  [24] = {.lex_state = 1},
  [25] = {.lex_state = 1},
  [26] = {.lex_state = 1},
  [27] = {.lex_state = 1},
  [28] = {.lex_state = 1},
  [29] = {.lex_state = 1},
  [30] = {.lex_state = 1},
  [31] = {.lex_state = 1},
  [32] = {.lex_state = 1},
  [33] = {.lex_state = 1},
  [34] = {.lex_state = 1},
  [35] = {.lex_state = 1},
  [36] = {.lex_state = 1},
  [37] = {.lex_state = 1},
  [38] = {.lex_state = 1},
  [39] = {.lex_state = 1},
  [40] = {.lex_state = 1},
  [41] = {.lex_state = 1},
  [42] = {.lex_state = 1},
  [43] = {.lex_state = 1},
  [44] = {.lex_state = 1},
  [45] = {.lex_state = 1},
  [46] = {.lex_state = 1},
  [47] = {.lex_state = 1},
  [48] = {.lex_state = 1},
  [49] = {.lex_state = 1},
  [50] = {.lex_state = 1},
  [51] = {.lex_state = 1},
  [52] = {.lex_state = 1},
  [53] = {.lex_state = 1},
  [54] = {.lex_state = 1},
  [55] = {.lex_state = 1},
  [56] = {.lex_state = 1},
  [57] = {.lex_state = 1},
  [58] = {.lex_state = 1},
  [59] = {.lex_state = 1},
  [60] = {.lex_state = 1},
  [61] = {.lex_state = 1},
  [62] = {.lex_state = 1},
  [63] = {.lex_state = 1},
  [64] = {.lex_state = 1},
  [65] = {.lex_state = 1},
  [66] = {.lex_state = 0},
  [67] = {.lex_state = 2},
  [68] = {.lex_state = 2},
  [69] = {.lex_state = 1},
  [70] = {.lex_state = 1},
  [71] = {.lex_state = 1},
  [72] = {.lex_state = 1},
  [73] = {.lex_state = 1},
  [74] = {.lex_state = 1},
  [75] = {.lex_state = 2},
  [76] = {.lex_state = 0},
  [77] = {.lex_state = 2},
  [78] = {.lex_state = 0},
  [79] = {.lex_state = 0},
  [80] = {.lex_state = 0},
  [81] = {.lex_state = 0},
  [82] = {.lex_state = 0},
  [83] = {.lex_state = 0},
  [84] = {.lex_state = 0},
  [85] = {.lex_state = 0},
  [86] = {.lex_state = 0},
  [87] = {.lex_state = 0},
  [88] = {.lex_state = 0},
  [89] = {.lex_state = 0},
  [90] = {.lex_state = 0},
  [91] = {.lex_state = 0},
  [92] = {.lex_state = 0},
  [93] = {.lex_state = 0},
  [94] = {.lex_state = 0},
  [95] = {.lex_state = 0},
  [96] = {.lex_state = 0},
  [97] = {.lex_state = 0},
  [98] = {.lex_state = 0},
  [99] = {.lex_state = 0},
  [100] = {.lex_state = 0},
  [101] = {.lex_state = 0},
  [102] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_LT] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_GT] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_i_LBRACE] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [sym_escape_sequence] = ACTIONS(1),
    [sym_number] = ACTIONS(1),
    [sym_datetime] = ACTIONS(1),
    [sym_true] = ACTIONS(1),
    [sym_hexblob] = ACTIONS(1),
    [sym_escblob] = ACTIONS(1),
    [sym_false] = ACTIONS(1),
    [sym_null] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
  },
  [1] = {
    [sym_document] = STATE(98),
    [sym__value] = STATE(96),
    [sym_meta] = STATE(13),
    [sym_map] = STATE(96),
    [sym_imap] = STATE(96),
    [sym_array] = STATE(96),
    [sym_string] = STATE(96),
    [anon_sym_LT] = ACTIONS(5),
    [anon_sym_LBRACE] = ACTIONS(7),
    [anon_sym_i_LBRACE] = ACTIONS(9),
    [anon_sym_LBRACK] = ACTIONS(11),
    [anon_sym_DQUOTE] = ACTIONS(13),
    [sym_number] = ACTIONS(15),
    [sym_datetime] = ACTIONS(15),
    [sym_true] = ACTIONS(15),
    [sym_hexblob] = ACTIONS(15),
    [sym_escblob] = ACTIONS(15),
    [sym_false] = ACTIONS(15),
    [sym_null] = ACTIONS(15),
    [sym_comment] = ACTIONS(3),
  },
  [2] = {
    [sym__value] = STATE(73),
    [sym_meta] = STATE(14),
    [sym_map] = STATE(73),
    [sym_imap] = STATE(73),
    [sym_array] = STATE(73),
    [sym_string] = STATE(73),
    [aux_sym_meta_repeat1] = STATE(7),
    [anon_sym_LT] = ACTIONS(17),
    [anon_sym_COMMA] = ACTIONS(19),
    [anon_sym_LF] = ACTIONS(19),
    [anon_sym_] = ACTIONS(19),
    [anon_sym_TAB] = ACTIONS(19),
    [anon_sym_LBRACE] = ACTIONS(21),
    [anon_sym_i_LBRACE] = ACTIONS(23),
    [anon_sym_LBRACK] = ACTIONS(25),
    [anon_sym_RBRACK] = ACTIONS(27),
    [anon_sym_DQUOTE] = ACTIONS(29),
    [sym_number] = ACTIONS(31),
    [sym_datetime] = ACTIONS(31),
    [sym_true] = ACTIONS(31),
    [sym_hexblob] = ACTIONS(31),
    [sym_escblob] = ACTIONS(31),
    [sym_false] = ACTIONS(31),
    [sym_null] = ACTIONS(31),
    [sym_comment] = ACTIONS(33),
  },
  [3] = {
    [sym__value] = STATE(73),
    [sym_meta] = STATE(14),
    [sym_map] = STATE(73),
    [sym_imap] = STATE(73),
    [sym_array] = STATE(73),
    [sym_string] = STATE(73),
    [aux_sym_meta_repeat1] = STATE(7),
    [anon_sym_LT] = ACTIONS(17),
    [anon_sym_COMMA] = ACTIONS(19),
    [anon_sym_LF] = ACTIONS(19),
    [anon_sym_] = ACTIONS(19),
    [anon_sym_TAB] = ACTIONS(19),
    [anon_sym_LBRACE] = ACTIONS(21),
    [anon_sym_i_LBRACE] = ACTIONS(23),
    [anon_sym_LBRACK] = ACTIONS(25),
    [anon_sym_RBRACK] = ACTIONS(35),
    [anon_sym_DQUOTE] = ACTIONS(29),
    [sym_number] = ACTIONS(31),
    [sym_datetime] = ACTIONS(31),
    [sym_true] = ACTIONS(31),
    [sym_hexblob] = ACTIONS(31),
    [sym_escblob] = ACTIONS(31),
    [sym_false] = ACTIONS(31),
    [sym_null] = ACTIONS(31),
    [sym_comment] = ACTIONS(33),
  },
  [4] = {
    [sym__value] = STATE(73),
    [sym_meta] = STATE(14),
    [sym_map] = STATE(73),
    [sym_imap] = STATE(73),
    [sym_array] = STATE(73),
    [sym_string] = STATE(73),
    [aux_sym_meta_repeat1] = STATE(7),
    [anon_sym_LT] = ACTIONS(17),
    [anon_sym_COMMA] = ACTIONS(19),
    [anon_sym_LF] = ACTIONS(19),
    [anon_sym_] = ACTIONS(19),
    [anon_sym_TAB] = ACTIONS(19),
    [anon_sym_LBRACE] = ACTIONS(21),
    [anon_sym_i_LBRACE] = ACTIONS(23),
    [anon_sym_LBRACK] = ACTIONS(25),
    [anon_sym_RBRACK] = ACTIONS(37),
    [anon_sym_DQUOTE] = ACTIONS(29),
    [sym_number] = ACTIONS(31),
    [sym_datetime] = ACTIONS(31),
    [sym_true] = ACTIONS(31),
    [sym_hexblob] = ACTIONS(31),
    [sym_escblob] = ACTIONS(31),
    [sym_false] = ACTIONS(31),
    [sym_null] = ACTIONS(31),
    [sym_comment] = ACTIONS(33),
  },
  [5] = {
    [sym__value] = STATE(73),
    [sym_meta] = STATE(14),
    [sym_map] = STATE(73),
    [sym_imap] = STATE(73),
    [sym_array] = STATE(73),
    [sym_string] = STATE(73),
    [aux_sym_meta_repeat1] = STATE(7),
    [anon_sym_LT] = ACTIONS(17),
    [anon_sym_COMMA] = ACTIONS(19),
    [anon_sym_LF] = ACTIONS(19),
    [anon_sym_] = ACTIONS(19),
    [anon_sym_TAB] = ACTIONS(19),
    [anon_sym_LBRACE] = ACTIONS(21),
    [anon_sym_i_LBRACE] = ACTIONS(23),
    [anon_sym_LBRACK] = ACTIONS(25),
    [anon_sym_RBRACK] = ACTIONS(39),
    [anon_sym_DQUOTE] = ACTIONS(29),
    [sym_number] = ACTIONS(31),
    [sym_datetime] = ACTIONS(31),
    [sym_true] = ACTIONS(31),
    [sym_hexblob] = ACTIONS(31),
    [sym_escblob] = ACTIONS(31),
    [sym_false] = ACTIONS(31),
    [sym_null] = ACTIONS(31),
    [sym_comment] = ACTIONS(33),
  },
  [6] = {
    [sym__value] = STATE(73),
    [sym_meta] = STATE(14),
    [sym_map] = STATE(73),
    [sym_imap] = STATE(73),
    [sym_array] = STATE(73),
    [sym_string] = STATE(73),
    [aux_sym_meta_repeat1] = STATE(7),
    [anon_sym_LT] = ACTIONS(17),
    [anon_sym_COMMA] = ACTIONS(19),
    [anon_sym_LF] = ACTIONS(19),
    [anon_sym_] = ACTIONS(19),
    [anon_sym_TAB] = ACTIONS(19),
    [anon_sym_LBRACE] = ACTIONS(21),
    [anon_sym_i_LBRACE] = ACTIONS(23),
    [anon_sym_LBRACK] = ACTIONS(25),
    [anon_sym_DQUOTE] = ACTIONS(29),
    [sym_number] = ACTIONS(31),
    [sym_datetime] = ACTIONS(31),
    [sym_true] = ACTIONS(31),
    [sym_hexblob] = ACTIONS(31),
    [sym_escblob] = ACTIONS(31),
    [sym_false] = ACTIONS(31),
    [sym_null] = ACTIONS(31),
    [sym_comment] = ACTIONS(33),
  },
  [7] = {
    [aux_sym_meta_repeat1] = STATE(7),
    [anon_sym_LT] = ACTIONS(41),
    [anon_sym_COMMA] = ACTIONS(43),
    [anon_sym_LF] = ACTIONS(43),
    [anon_sym_] = ACTIONS(43),
    [anon_sym_TAB] = ACTIONS(43),
    [anon_sym_GT] = ACTIONS(41),
    [anon_sym_LBRACE] = ACTIONS(41),
    [anon_sym_RBRACE] = ACTIONS(41),
    [anon_sym_i_LBRACE] = ACTIONS(41),
    [anon_sym_LBRACK] = ACTIONS(41),
    [anon_sym_RBRACK] = ACTIONS(41),
    [anon_sym_DQUOTE] = ACTIONS(41),
    [sym_number] = ACTIONS(41),
    [sym_datetime] = ACTIONS(41),
    [sym_true] = ACTIONS(41),
    [sym_hexblob] = ACTIONS(41),
    [sym_escblob] = ACTIONS(41),
    [sym_false] = ACTIONS(41),
    [sym_null] = ACTIONS(41),
    [sym_comment] = ACTIONS(33),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(5), 1,
      anon_sym_LT,
    ACTIONS(46), 1,
      anon_sym_LBRACE,
    ACTIONS(48), 1,
      anon_sym_i_LBRACE,
    ACTIONS(50), 1,
      anon_sym_LBRACK,
    ACTIONS(52), 1,
      anon_sym_RBRACK,
    ACTIONS(54), 1,
      anon_sym_DQUOTE,
    STATE(14), 1,
      sym_meta,
    STATE(37), 5,
      sym__value,
      sym_map,
      sym_imap,
      sym_array,
      sym_string,
    ACTIONS(56), 7,
      sym_number,
      sym_datetime,
      sym_true,
      sym_hexblob,
      sym_escblob,
      sym_false,
      sym_null,
  [41] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(5), 1,
      anon_sym_LT,
    ACTIONS(46), 1,
      anon_sym_LBRACE,
    ACTIONS(48), 1,
      anon_sym_i_LBRACE,
    ACTIONS(50), 1,
      anon_sym_LBRACK,
    ACTIONS(54), 1,
      anon_sym_DQUOTE,
    ACTIONS(58), 1,
      anon_sym_RBRACK,
    STATE(14), 1,
      sym_meta,
    STATE(33), 5,
      sym__value,
      sym_map,
      sym_imap,
      sym_array,
      sym_string,
    ACTIONS(60), 7,
      sym_number,
      sym_datetime,
      sym_true,
      sym_hexblob,
      sym_escblob,
      sym_false,
      sym_null,
  [82] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(5), 1,
      anon_sym_LT,
    ACTIONS(46), 1,
      anon_sym_LBRACE,
    ACTIONS(48), 1,
      anon_sym_i_LBRACE,
    ACTIONS(50), 1,
      anon_sym_LBRACK,
    ACTIONS(54), 1,
      anon_sym_DQUOTE,
    STATE(14), 1,
      sym_meta,
    STATE(72), 5,
      sym__value,
      sym_map,
      sym_imap,
      sym_array,
      sym_string,
    ACTIONS(62), 7,
      sym_number,
      sym_datetime,
      sym_true,
      sym_hexblob,
      sym_escblob,
      sym_false,
      sym_null,
  [120] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(5), 1,
      anon_sym_LT,
    ACTIONS(46), 1,
      anon_sym_LBRACE,
    ACTIONS(48), 1,
      anon_sym_i_LBRACE,
    ACTIONS(50), 1,
      anon_sym_LBRACK,
    ACTIONS(54), 1,
      anon_sym_DQUOTE,
    STATE(14), 1,
      sym_meta,
    STATE(71), 5,
      sym__value,
      sym_map,
      sym_imap,
      sym_array,
      sym_string,
    ACTIONS(64), 7,
      sym_number,
      sym_datetime,
      sym_true,
      sym_hexblob,
      sym_escblob,
      sym_false,
      sym_null,
  [158] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(5), 1,
      anon_sym_LT,
    ACTIONS(46), 1,
      anon_sym_LBRACE,
    ACTIONS(48), 1,
      anon_sym_i_LBRACE,
    ACTIONS(50), 1,
      anon_sym_LBRACK,
    ACTIONS(54), 1,
      anon_sym_DQUOTE,
    STATE(14), 1,
      sym_meta,
    STATE(70), 5,
      sym__value,
      sym_map,
      sym_imap,
      sym_array,
      sym_string,
    ACTIONS(66), 7,
      sym_number,
      sym_datetime,
      sym_true,
      sym_hexblob,
      sym_escblob,
      sym_false,
      sym_null,
  [196] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      anon_sym_LBRACE,
    ACTIONS(9), 1,
      anon_sym_i_LBRACE,
    ACTIONS(11), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_DQUOTE,
    STATE(95), 4,
      sym_map,
      sym_imap,
      sym_array,
      sym_string,
    ACTIONS(68), 7,
      sym_number,
      sym_datetime,
      sym_true,
      sym_hexblob,
      sym_escblob,
      sym_false,
      sym_null,
  [227] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(46), 1,
      anon_sym_LBRACE,
    ACTIONS(48), 1,
      anon_sym_i_LBRACE,
    ACTIONS(50), 1,
      anon_sym_LBRACK,
    ACTIONS(54), 1,
      anon_sym_DQUOTE,
    STATE(56), 4,
      sym_map,
      sym_imap,
      sym_array,
      sym_string,
    ACTIONS(70), 7,
      sym_number,
      sym_datetime,
      sym_true,
      sym_hexblob,
      sym_escblob,
      sym_false,
      sym_null,
  [258] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(72), 11,
      anon_sym_LBRACE,
      anon_sym_i_LBRACE,
      anon_sym_LBRACK,
      anon_sym_DQUOTE,
      sym_number,
      sym_datetime,
      sym_true,
      sym_hexblob,
      sym_escblob,
      sym_false,
      sym_null,
  [275] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(74), 11,
      anon_sym_LBRACE,
      anon_sym_i_LBRACE,
      anon_sym_LBRACK,
      anon_sym_DQUOTE,
      sym_number,
      sym_datetime,
      sym_true,
      sym_hexblob,
      sym_escblob,
      sym_false,
      sym_null,
  [292] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(76), 11,
      anon_sym_LBRACE,
      anon_sym_i_LBRACE,
      anon_sym_LBRACK,
      anon_sym_DQUOTE,
      sym_number,
      sym_datetime,
      sym_true,
      sym_hexblob,
      sym_escblob,
      sym_false,
      sym_null,
  [309] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(78), 11,
      anon_sym_LBRACE,
      anon_sym_i_LBRACE,
      anon_sym_LBRACK,
      anon_sym_DQUOTE,
      sym_number,
      sym_datetime,
      sym_true,
      sym_hexblob,
      sym_escblob,
      sym_false,
      sym_null,
  [326] = 8,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(80), 1,
      anon_sym_GT,
    ACTIONS(82), 1,
      anon_sym_DQUOTE,
    ACTIONS(84), 1,
      sym_number,
    STATE(7), 1,
      aux_sym_meta_repeat1,
    STATE(65), 1,
      sym_mpair,
    STATE(94), 1,
      sym_string,
    ACTIONS(19), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [354] = 8,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(82), 1,
      anon_sym_DQUOTE,
    ACTIONS(84), 1,
      sym_number,
    ACTIONS(86), 1,
      anon_sym_GT,
    STATE(7), 1,
      aux_sym_meta_repeat1,
    STATE(65), 1,
      sym_mpair,
    STATE(94), 1,
      sym_string,
    ACTIONS(19), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [382] = 7,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(82), 1,
      anon_sym_DQUOTE,
    ACTIONS(88), 1,
      anon_sym_RBRACE,
    STATE(7), 1,
      aux_sym_meta_repeat1,
    STATE(74), 1,
      sym_pair,
    STATE(86), 1,
      sym_string,
    ACTIONS(19), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [407] = 7,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(82), 1,
      anon_sym_DQUOTE,
    ACTIONS(90), 1,
      anon_sym_RBRACE,
    STATE(7), 1,
      aux_sym_meta_repeat1,
    STATE(74), 1,
      sym_pair,
    STATE(86), 1,
      sym_string,
    ACTIONS(19), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [432] = 7,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(82), 1,
      anon_sym_DQUOTE,
    ACTIONS(92), 1,
      anon_sym_RBRACE,
    STATE(7), 1,
      aux_sym_meta_repeat1,
    STATE(74), 1,
      sym_pair,
    STATE(86), 1,
      sym_string,
    ACTIONS(19), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [457] = 7,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(82), 1,
      anon_sym_DQUOTE,
    ACTIONS(84), 1,
      sym_number,
    STATE(7), 1,
      aux_sym_meta_repeat1,
    STATE(65), 1,
      sym_mpair,
    STATE(94), 1,
      sym_string,
    ACTIONS(19), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [482] = 7,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(82), 1,
      anon_sym_DQUOTE,
    ACTIONS(94), 1,
      anon_sym_RBRACE,
    STATE(7), 1,
      aux_sym_meta_repeat1,
    STATE(74), 1,
      sym_pair,
    STATE(86), 1,
      sym_string,
    ACTIONS(19), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [507] = 6,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(96), 1,
      anon_sym_RBRACE,
    ACTIONS(98), 1,
      sym_number,
    STATE(7), 1,
      aux_sym_meta_repeat1,
    STATE(69), 1,
      sym_ipair,
    ACTIONS(19), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [529] = 6,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(98), 1,
      sym_number,
    ACTIONS(100), 1,
      anon_sym_RBRACE,
    STATE(7), 1,
      aux_sym_meta_repeat1,
    STATE(69), 1,
      sym_ipair,
    ACTIONS(19), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [551] = 6,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(98), 1,
      sym_number,
    ACTIONS(102), 1,
      anon_sym_RBRACE,
    STATE(7), 1,
      aux_sym_meta_repeat1,
    STATE(69), 1,
      sym_ipair,
    ACTIONS(19), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [573] = 6,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(98), 1,
      sym_number,
    ACTIONS(104), 1,
      anon_sym_RBRACE,
    STATE(7), 1,
      aux_sym_meta_repeat1,
    STATE(69), 1,
      sym_ipair,
    ACTIONS(19), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [595] = 6,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(82), 1,
      anon_sym_DQUOTE,
    STATE(7), 1,
      aux_sym_meta_repeat1,
    STATE(74), 1,
      sym_pair,
    STATE(86), 1,
      sym_string,
    ACTIONS(19), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [617] = 5,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(109), 1,
      anon_sym_RBRACE,
    STATE(30), 1,
      aux_sym_meta_repeat1,
    STATE(31), 1,
      aux_sym_map_repeat1,
    ACTIONS(106), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [636] = 5,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(98), 1,
      sym_number,
    STATE(7), 1,
      aux_sym_meta_repeat1,
    STATE(69), 1,
      sym_ipair,
    ACTIONS(19), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [655] = 5,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(113), 1,
      anon_sym_RBRACK,
    STATE(2), 1,
      aux_sym_meta_repeat1,
    STATE(44), 1,
      aux_sym_array_repeat1,
    ACTIONS(111), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [674] = 5,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(39), 1,
      anon_sym_RBRACK,
    STATE(3), 1,
      aux_sym_meta_repeat1,
    STATE(61), 1,
      aux_sym_array_repeat1,
    ACTIONS(115), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [693] = 5,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(96), 1,
      anon_sym_RBRACE,
    STATE(29), 1,
      aux_sym_meta_repeat1,
    STATE(57), 1,
      aux_sym_imap_repeat1,
    ACTIONS(117), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [712] = 5,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(90), 1,
      anon_sym_RBRACE,
    STATE(25), 1,
      aux_sym_meta_repeat1,
    STATE(31), 1,
      aux_sym_map_repeat1,
    ACTIONS(119), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [731] = 5,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(123), 1,
      anon_sym_RBRACK,
    STATE(5), 1,
      aux_sym_meta_repeat1,
    STATE(34), 1,
      aux_sym_array_repeat1,
    ACTIONS(121), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [750] = 5,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(86), 1,
      anon_sym_GT,
    STATE(19), 1,
      aux_sym_meta_repeat1,
    STATE(49), 1,
      aux_sym_meta_repeat2,
    ACTIONS(125), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [769] = 5,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(129), 1,
      anon_sym_RBRACE,
    STATE(26), 1,
      aux_sym_meta_repeat1,
    STATE(35), 1,
      aux_sym_imap_repeat1,
    ACTIONS(127), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [788] = 5,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(88), 1,
      anon_sym_RBRACE,
    STATE(23), 1,
      aux_sym_meta_repeat1,
    STATE(31), 1,
      aux_sym_map_repeat1,
    ACTIONS(131), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [807] = 5,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(135), 1,
      anon_sym_RBRACE,
    STATE(22), 1,
      aux_sym_meta_repeat1,
    STATE(36), 1,
      aux_sym_map_repeat1,
    ACTIONS(133), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [826] = 5,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(102), 1,
      anon_sym_RBRACE,
    STATE(27), 1,
      aux_sym_meta_repeat1,
    STATE(57), 1,
      aux_sym_imap_repeat1,
    ACTIONS(137), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [845] = 5,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(141), 1,
      anon_sym_GT,
    STATE(20), 1,
      aux_sym_meta_repeat1,
    STATE(38), 1,
      aux_sym_meta_repeat2,
    ACTIONS(139), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [864] = 5,
    ACTIONS(27), 1,
      anon_sym_RBRACK,
    ACTIONS(33), 1,
      sym_comment,
    STATE(4), 1,
      aux_sym_meta_repeat1,
    STATE(61), 1,
      aux_sym_array_repeat1,
    ACTIONS(143), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [883] = 2,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(145), 7,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
      anon_sym_GT,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
  [896] = 2,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(147), 7,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
      anon_sym_GT,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
  [909] = 2,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(149), 7,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
      anon_sym_GT,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
  [922] = 2,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(151), 7,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
      anon_sym_GT,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
  [935] = 5,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(156), 1,
      anon_sym_GT,
    STATE(24), 1,
      aux_sym_meta_repeat1,
    STATE(49), 1,
      aux_sym_meta_repeat2,
    ACTIONS(153), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [954] = 2,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(158), 7,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
      anon_sym_GT,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
  [967] = 2,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(160), 7,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
      anon_sym_GT,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
  [980] = 2,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(162), 7,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
      anon_sym_GT,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
  [993] = 2,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(164), 7,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
      anon_sym_GT,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
  [1006] = 2,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(166), 7,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
      anon_sym_GT,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
  [1019] = 2,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(168), 7,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
      anon_sym_GT,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
  [1032] = 2,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(170), 7,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
      anon_sym_GT,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
  [1045] = 5,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(175), 1,
      anon_sym_RBRACE,
    STATE(32), 1,
      aux_sym_meta_repeat1,
    STATE(57), 1,
      aux_sym_imap_repeat1,
    ACTIONS(172), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [1064] = 2,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(177), 7,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
      anon_sym_GT,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
  [1077] = 2,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(179), 7,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
      anon_sym_GT,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
  [1090] = 5,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(183), 1,
      anon_sym_RBRACE,
    STATE(28), 1,
      aux_sym_meta_repeat1,
    STATE(42), 1,
      aux_sym_imap_repeat1,
    ACTIONS(181), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [1109] = 5,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(188), 1,
      anon_sym_RBRACK,
    STATE(6), 1,
      aux_sym_meta_repeat1,
    STATE(61), 1,
      aux_sym_array_repeat1,
    ACTIONS(185), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [1128] = 2,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(190), 7,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
      anon_sym_GT,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
  [1141] = 2,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(192), 7,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
      anon_sym_GT,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
  [1154] = 5,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(196), 1,
      anon_sym_RBRACE,
    STATE(21), 1,
      aux_sym_meta_repeat1,
    STATE(40), 1,
      aux_sym_map_repeat1,
    ACTIONS(194), 4,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
  [1173] = 2,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(156), 5,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
      anon_sym_GT,
  [1184] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(13), 1,
      anon_sym_DQUOTE,
    ACTIONS(198), 1,
      anon_sym_GT,
    ACTIONS(200), 1,
      sym_number,
    STATE(43), 1,
      sym_mpair,
    STATE(94), 1,
      sym_string,
  [1203] = 6,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(202), 1,
      anon_sym_DQUOTE,
    ACTIONS(204), 1,
      aux_sym_string_content_token1,
    ACTIONS(206), 1,
      sym_escape_sequence,
    STATE(77), 1,
      aux_sym_string_content_repeat1,
    STATE(99), 1,
      sym_string_content,
  [1222] = 6,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(204), 1,
      aux_sym_string_content_token1,
    ACTIONS(206), 1,
      sym_escape_sequence,
    ACTIONS(208), 1,
      anon_sym_DQUOTE,
    STATE(77), 1,
      aux_sym_string_content_repeat1,
    STATE(93), 1,
      sym_string_content,
  [1241] = 2,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(175), 5,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
      anon_sym_RBRACE,
  [1252] = 2,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(210), 5,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
      anon_sym_GT,
  [1263] = 2,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(212), 5,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
      anon_sym_RBRACE,
  [1274] = 2,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(214), 5,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
      anon_sym_RBRACE,
  [1285] = 2,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(188), 5,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
      anon_sym_RBRACK,
  [1296] = 2,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(109), 5,
      anon_sym_COMMA,
      anon_sym_LF,
      anon_sym_,
      anon_sym_TAB,
      anon_sym_RBRACE,
  [1307] = 5,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(216), 1,
      anon_sym_DQUOTE,
    ACTIONS(218), 1,
      aux_sym_string_content_token1,
    ACTIONS(221), 1,
      sym_escape_sequence,
    STATE(75), 1,
      aux_sym_string_content_repeat1,
  [1323] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(13), 1,
      anon_sym_DQUOTE,
    ACTIONS(224), 1,
      anon_sym_RBRACE,
    STATE(64), 1,
      sym_pair,
    STATE(86), 1,
      sym_string,
  [1339] = 5,
    ACTIONS(33), 1,
      sym_comment,
    ACTIONS(226), 1,
      anon_sym_DQUOTE,
    ACTIONS(228), 1,
      aux_sym_string_content_token1,
    ACTIONS(230), 1,
      sym_escape_sequence,
    STATE(75), 1,
      aux_sym_string_content_repeat1,
  [1355] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(13), 1,
      anon_sym_DQUOTE,
    ACTIONS(232), 1,
      anon_sym_RBRACE,
    STATE(41), 1,
      sym_pair,
    STATE(86), 1,
      sym_string,
  [1371] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(234), 1,
      anon_sym_RBRACE,
    ACTIONS(236), 1,
      sym_number,
    STATE(60), 1,
      sym_ipair,
  [1384] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(236), 1,
      sym_number,
    ACTIONS(238), 1,
      anon_sym_RBRACE,
    STATE(39), 1,
      sym_ipair,
  [1397] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(240), 2,
      ts_builtin_sym_end,
      anon_sym_COLON,
  [1405] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(242), 2,
      ts_builtin_sym_end,
      anon_sym_COLON,
  [1413] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(244), 1,
      ts_builtin_sym_end,
  [1420] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(246), 1,
      ts_builtin_sym_end,
  [1427] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(248), 1,
      ts_builtin_sym_end,
  [1434] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(250), 1,
      anon_sym_COLON,
  [1441] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(252), 1,
      ts_builtin_sym_end,
  [1448] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(254), 1,
      ts_builtin_sym_end,
  [1455] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(256), 1,
      ts_builtin_sym_end,
  [1462] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(258), 1,
      ts_builtin_sym_end,
  [1469] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(260), 1,
      ts_builtin_sym_end,
  [1476] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(262), 1,
      ts_builtin_sym_end,
  [1483] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(264), 1,
      anon_sym_DQUOTE,
  [1490] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(266), 1,
      anon_sym_COLON,
  [1497] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(268), 1,
      ts_builtin_sym_end,
  [1504] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(270), 1,
      ts_builtin_sym_end,
  [1511] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(272), 1,
      ts_builtin_sym_end,
  [1518] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(274), 1,
      ts_builtin_sym_end,
  [1525] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(276), 1,
      anon_sym_DQUOTE,
  [1532] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(278), 1,
      ts_builtin_sym_end,
  [1539] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(280), 1,
      anon_sym_COLON,
  [1546] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(282), 1,
      ts_builtin_sym_end,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(8)] = 0,
  [SMALL_STATE(9)] = 41,
  [SMALL_STATE(10)] = 82,
  [SMALL_STATE(11)] = 120,
  [SMALL_STATE(12)] = 158,
  [SMALL_STATE(13)] = 196,
  [SMALL_STATE(14)] = 227,
  [SMALL_STATE(15)] = 258,
  [SMALL_STATE(16)] = 275,
  [SMALL_STATE(17)] = 292,
  [SMALL_STATE(18)] = 309,
  [SMALL_STATE(19)] = 326,
  [SMALL_STATE(20)] = 354,
  [SMALL_STATE(21)] = 382,
  [SMALL_STATE(22)] = 407,
  [SMALL_STATE(23)] = 432,
  [SMALL_STATE(24)] = 457,
  [SMALL_STATE(25)] = 482,
  [SMALL_STATE(26)] = 507,
  [SMALL_STATE(27)] = 529,
  [SMALL_STATE(28)] = 551,
  [SMALL_STATE(29)] = 573,
  [SMALL_STATE(30)] = 595,
  [SMALL_STATE(31)] = 617,
  [SMALL_STATE(32)] = 636,
  [SMALL_STATE(33)] = 655,
  [SMALL_STATE(34)] = 674,
  [SMALL_STATE(35)] = 693,
  [SMALL_STATE(36)] = 712,
  [SMALL_STATE(37)] = 731,
  [SMALL_STATE(38)] = 750,
  [SMALL_STATE(39)] = 769,
  [SMALL_STATE(40)] = 788,
  [SMALL_STATE(41)] = 807,
  [SMALL_STATE(42)] = 826,
  [SMALL_STATE(43)] = 845,
  [SMALL_STATE(44)] = 864,
  [SMALL_STATE(45)] = 883,
  [SMALL_STATE(46)] = 896,
  [SMALL_STATE(47)] = 909,
  [SMALL_STATE(48)] = 922,
  [SMALL_STATE(49)] = 935,
  [SMALL_STATE(50)] = 954,
  [SMALL_STATE(51)] = 967,
  [SMALL_STATE(52)] = 980,
  [SMALL_STATE(53)] = 993,
  [SMALL_STATE(54)] = 1006,
  [SMALL_STATE(55)] = 1019,
  [SMALL_STATE(56)] = 1032,
  [SMALL_STATE(57)] = 1045,
  [SMALL_STATE(58)] = 1064,
  [SMALL_STATE(59)] = 1077,
  [SMALL_STATE(60)] = 1090,
  [SMALL_STATE(61)] = 1109,
  [SMALL_STATE(62)] = 1128,
  [SMALL_STATE(63)] = 1141,
  [SMALL_STATE(64)] = 1154,
  [SMALL_STATE(65)] = 1173,
  [SMALL_STATE(66)] = 1184,
  [SMALL_STATE(67)] = 1203,
  [SMALL_STATE(68)] = 1222,
  [SMALL_STATE(69)] = 1241,
  [SMALL_STATE(70)] = 1252,
  [SMALL_STATE(71)] = 1263,
  [SMALL_STATE(72)] = 1274,
  [SMALL_STATE(73)] = 1285,
  [SMALL_STATE(74)] = 1296,
  [SMALL_STATE(75)] = 1307,
  [SMALL_STATE(76)] = 1323,
  [SMALL_STATE(77)] = 1339,
  [SMALL_STATE(78)] = 1355,
  [SMALL_STATE(79)] = 1371,
  [SMALL_STATE(80)] = 1384,
  [SMALL_STATE(81)] = 1397,
  [SMALL_STATE(82)] = 1405,
  [SMALL_STATE(83)] = 1413,
  [SMALL_STATE(84)] = 1420,
  [SMALL_STATE(85)] = 1427,
  [SMALL_STATE(86)] = 1434,
  [SMALL_STATE(87)] = 1441,
  [SMALL_STATE(88)] = 1448,
  [SMALL_STATE(89)] = 1455,
  [SMALL_STATE(90)] = 1462,
  [SMALL_STATE(91)] = 1469,
  [SMALL_STATE(92)] = 1476,
  [SMALL_STATE(93)] = 1483,
  [SMALL_STATE(94)] = 1490,
  [SMALL_STATE(95)] = 1497,
  [SMALL_STATE(96)] = 1504,
  [SMALL_STATE(97)] = 1511,
  [SMALL_STATE(98)] = 1518,
  [SMALL_STATE(99)] = 1525,
  [SMALL_STATE(100)] = 1532,
  [SMALL_STATE(101)] = 1539,
  [SMALL_STATE(102)] = 1546,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(96),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(66),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(7),
  [21] = {.entry = {.count = 1, .reusable = false}}, SHIFT(78),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(80),
  [25] = {.entry = {.count = 1, .reusable = false}}, SHIFT(8),
  [27] = {.entry = {.count = 1, .reusable = false}}, SHIFT(84),
  [29] = {.entry = {.count = 1, .reusable = false}}, SHIFT(68),
  [31] = {.entry = {.count = 1, .reusable = false}}, SHIFT(73),
  [33] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [35] = {.entry = {.count = 1, .reusable = false}}, SHIFT(45),
  [37] = {.entry = {.count = 1, .reusable = false}}, SHIFT(100),
  [39] = {.entry = {.count = 1, .reusable = false}}, SHIFT(48),
  [41] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_meta_repeat1, 2),
  [43] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_meta_repeat1, 2), SHIFT_REPEAT(7),
  [46] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [48] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [50] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [52] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [54] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [56] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [58] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [60] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [62] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [64] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [66] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [68] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [70] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [72] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_meta, 2),
  [74] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_meta, 5),
  [76] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_meta, 4),
  [78] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_meta, 3),
  [80] = {.entry = {.count = 1, .reusable = false}}, SHIFT(16),
  [82] = {.entry = {.count = 1, .reusable = false}}, SHIFT(67),
  [84] = {.entry = {.count = 1, .reusable = false}}, SHIFT(94),
  [86] = {.entry = {.count = 1, .reusable = false}}, SHIFT(17),
  [88] = {.entry = {.count = 1, .reusable = false}}, SHIFT(83),
  [90] = {.entry = {.count = 1, .reusable = false}}, SHIFT(51),
  [92] = {.entry = {.count = 1, .reusable = false}}, SHIFT(97),
  [94] = {.entry = {.count = 1, .reusable = false}}, SHIFT(47),
  [96] = {.entry = {.count = 1, .reusable = false}}, SHIFT(50),
  [98] = {.entry = {.count = 1, .reusable = false}}, SHIFT(101),
  [100] = {.entry = {.count = 1, .reusable = false}}, SHIFT(88),
  [102] = {.entry = {.count = 1, .reusable = false}}, SHIFT(85),
  [104] = {.entry = {.count = 1, .reusable = false}}, SHIFT(46),
  [106] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_map_repeat1, 2), SHIFT_REPEAT(30),
  [109] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_map_repeat1, 2),
  [111] = {.entry = {.count = 1, .reusable = false}}, SHIFT(2),
  [113] = {.entry = {.count = 1, .reusable = false}}, SHIFT(90),
  [115] = {.entry = {.count = 1, .reusable = false}}, SHIFT(3),
  [117] = {.entry = {.count = 1, .reusable = false}}, SHIFT(29),
  [119] = {.entry = {.count = 1, .reusable = false}}, SHIFT(25),
  [121] = {.entry = {.count = 1, .reusable = false}}, SHIFT(5),
  [123] = {.entry = {.count = 1, .reusable = false}}, SHIFT(53),
  [125] = {.entry = {.count = 1, .reusable = false}}, SHIFT(19),
  [127] = {.entry = {.count = 1, .reusable = false}}, SHIFT(26),
  [129] = {.entry = {.count = 1, .reusable = false}}, SHIFT(54),
  [131] = {.entry = {.count = 1, .reusable = false}}, SHIFT(23),
  [133] = {.entry = {.count = 1, .reusable = false}}, SHIFT(22),
  [135] = {.entry = {.count = 1, .reusable = false}}, SHIFT(55),
  [137] = {.entry = {.count = 1, .reusable = false}}, SHIFT(27),
  [139] = {.entry = {.count = 1, .reusable = false}}, SHIFT(20),
  [141] = {.entry = {.count = 1, .reusable = false}}, SHIFT(18),
  [143] = {.entry = {.count = 1, .reusable = false}}, SHIFT(4),
  [145] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_array, 5),
  [147] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_imap, 5),
  [149] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_map, 5),
  [151] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_array, 4),
  [153] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_meta_repeat2, 2), SHIFT_REPEAT(24),
  [156] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_meta_repeat2, 2),
  [158] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_imap, 4),
  [160] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_map, 4),
  [162] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string, 3),
  [164] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_array, 3),
  [166] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_imap, 3),
  [168] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_map, 3),
  [170] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__value, 2),
  [172] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_imap_repeat1, 2), SHIFT_REPEAT(32),
  [175] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_imap_repeat1, 2),
  [177] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string, 2),
  [179] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_array, 2),
  [181] = {.entry = {.count = 1, .reusable = false}}, SHIFT(28),
  [183] = {.entry = {.count = 1, .reusable = false}}, SHIFT(91),
  [185] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_array_repeat1, 2), SHIFT_REPEAT(6),
  [188] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_array_repeat1, 2),
  [190] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_imap, 2),
  [192] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_map, 2),
  [194] = {.entry = {.count = 1, .reusable = false}}, SHIFT(21),
  [196] = {.entry = {.count = 1, .reusable = false}}, SHIFT(92),
  [198] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [200] = {.entry = {.count = 1, .reusable = true}}, SHIFT(94),
  [202] = {.entry = {.count = 1, .reusable = false}}, SHIFT(82),
  [204] = {.entry = {.count = 1, .reusable = false}}, SHIFT(77),
  [206] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [208] = {.entry = {.count = 1, .reusable = false}}, SHIFT(58),
  [210] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_mpair, 3, .production_id = 1),
  [212] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_ipair, 3, .production_id = 1),
  [214] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pair, 3, .production_id = 1),
  [216] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_content_repeat1, 2),
  [218] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_content_repeat1, 2), SHIFT_REPEAT(75),
  [221] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_string_content_repeat1, 2), SHIFT_REPEAT(75),
  [224] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [226] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string_content, 1),
  [228] = {.entry = {.count = 1, .reusable = false}}, SHIFT(75),
  [230] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [232] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [234] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [236] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [238] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [240] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 3),
  [242] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 2),
  [244] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map, 4),
  [246] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_array, 4),
  [248] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_imap, 4),
  [250] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [252] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_array, 2),
  [254] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_imap, 5),
  [256] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map, 2),
  [258] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_array, 3),
  [260] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_imap, 3),
  [262] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map, 3),
  [264] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [266] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [268] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__value, 2),
  [270] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_document, 1),
  [272] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map, 5),
  [274] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [276] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [278] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_array, 5),
  [280] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [282] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_imap, 2),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_cpon(void) {
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
