#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 44
#define LARGE_STATE_COUNT 4
#define SYMBOL_COUNT 26
#define ALIAS_COUNT 1
#define TOKEN_COUNT 12
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 3
#define MAX_ALIAS_SEQUENCE_LENGTH 4
#define PRODUCTION_ID_COUNT 6

enum {
  anon_sym_LF = 1,
  anon_sym_ = 2,
  sym__word = 3,
  anon_sym_EQ_GT = 4,
  anon_sym_BQUOTE_BQUOTE_BQUOTE = 5,
  sym_end_pre = 6,
  anon_sym_POUND = 7,
  anon_sym_POUND_POUND = 8,
  anon_sym_POUND_POUND_POUND = 9,
  anon_sym_STAR = 10,
  anon_sym_GT = 11,
  sym_source_file = 12,
  aux_sym__space = 13,
  sym_text = 14,
  sym_link = 15,
  sym_start_pre = 16,
  sym_pre = 17,
  sym_heading1 = 18,
  sym_heading2 = 19,
  sym_heading3 = 20,
  sym_ulist = 21,
  sym_quote = 22,
  aux_sym_source_file_repeat1 = 23,
  aux_sym_source_file_repeat2 = 24,
  aux_sym_text_repeat1 = 25,
  alias_sym_uri = 26,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_LF] = "\n",
  [anon_sym_] = " ",
  [sym__word] = "_word",
  [anon_sym_EQ_GT] = "=>",
  [anon_sym_BQUOTE_BQUOTE_BQUOTE] = "```",
  [sym_end_pre] = "end_pre",
  [anon_sym_POUND] = "#",
  [anon_sym_POUND_POUND] = "##",
  [anon_sym_POUND_POUND_POUND] = "###",
  [anon_sym_STAR] = "indicator",
  [anon_sym_GT] = "indicator",
  [sym_source_file] = "source_file",
  [aux_sym__space] = "_space",
  [sym_text] = "text",
  [sym_link] = "link",
  [sym_start_pre] = "start_pre",
  [sym_pre] = "pre",
  [sym_heading1] = "heading1",
  [sym_heading2] = "heading2",
  [sym_heading3] = "heading3",
  [sym_ulist] = "ulist",
  [sym_quote] = "quote",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_source_file_repeat2] = "source_file_repeat2",
  [aux_sym_text_repeat1] = "text_repeat1",
  [alias_sym_uri] = "uri",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_LF] = anon_sym_LF,
  [anon_sym_] = anon_sym_,
  [sym__word] = sym__word,
  [anon_sym_EQ_GT] = anon_sym_EQ_GT,
  [anon_sym_BQUOTE_BQUOTE_BQUOTE] = anon_sym_BQUOTE_BQUOTE_BQUOTE,
  [sym_end_pre] = sym_end_pre,
  [anon_sym_POUND] = anon_sym_POUND,
  [anon_sym_POUND_POUND] = anon_sym_POUND_POUND,
  [anon_sym_POUND_POUND_POUND] = anon_sym_POUND_POUND_POUND,
  [anon_sym_STAR] = anon_sym_STAR,
  [anon_sym_GT] = anon_sym_STAR,
  [sym_source_file] = sym_source_file,
  [aux_sym__space] = aux_sym__space,
  [sym_text] = sym_text,
  [sym_link] = sym_link,
  [sym_start_pre] = sym_start_pre,
  [sym_pre] = sym_pre,
  [sym_heading1] = sym_heading1,
  [sym_heading2] = sym_heading2,
  [sym_heading3] = sym_heading3,
  [sym_ulist] = sym_ulist,
  [sym_quote] = sym_quote,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_source_file_repeat2] = aux_sym_source_file_repeat2,
  [aux_sym_text_repeat1] = aux_sym_text_repeat1,
  [alias_sym_uri] = alias_sym_uri,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_LF] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_] = {
    .visible = true,
    .named = false,
  },
  [sym__word] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_EQ_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BQUOTE_BQUOTE_BQUOTE] = {
    .visible = true,
    .named = false,
  },
  [sym_end_pre] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_POUND] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_POUND_POUND] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_POUND_POUND_POUND] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_STAR] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_GT] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [aux_sym__space] = {
    .visible = false,
    .named = false,
  },
  [sym_text] = {
    .visible = true,
    .named = true,
  },
  [sym_link] = {
    .visible = true,
    .named = true,
  },
  [sym_start_pre] = {
    .visible = true,
    .named = true,
  },
  [sym_pre] = {
    .visible = true,
    .named = true,
  },
  [sym_heading1] = {
    .visible = true,
    .named = true,
  },
  [sym_heading2] = {
    .visible = true,
    .named = true,
  },
  [sym_heading3] = {
    .visible = true,
    .named = true,
  },
  [sym_ulist] = {
    .visible = true,
    .named = true,
  },
  [sym_quote] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_source_file_repeat2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_text_repeat1] = {
    .visible = false,
    .named = false,
  },
  [alias_sym_uri] = {
    .visible = true,
    .named = true,
  },
};

enum {
  field_alt = 1,
  field_label = 2,
  field_uri = 3,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_alt] = "alt",
  [field_label] = "label",
  [field_uri] = "uri",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 2},
  [3] = {.index = 3, .length = 1},
  [4] = {.index = 4, .length = 1},
  [5] = {.index = 5, .length = 2},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_uri, 1},
  [1] =
    {field_label, 2},
    {field_uri, 1},
  [3] =
    {field_uri, 2},
  [4] =
    {field_alt, 1},
  [5] =
    {field_label, 3},
    {field_uri, 2},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
  [1] = {
    [1] = alias_sym_uri,
  },
  [2] = {
    [1] = alias_sym_uri,
  },
  [3] = {
    [2] = alias_sym_uri,
  },
  [5] = {
    [2] = alias_sym_uri,
  },
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
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(4);
      if (lookahead == '\n') ADVANCE(5);
      if (lookahead == ' ') ADVANCE(6);
      if (lookahead == '#') ADVANCE(17);
      if (lookahead == '*') ADVANCE(7);
      if (lookahead == '=') ADVANCE(8);
      if (lookahead == '>') ADVANCE(21);
      if (lookahead == '`') ADVANCE(11);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\r') ADVANCE(13);
      END_STATE();
    case 1:
      if (lookahead == '\n') ADVANCE(5);
      if (lookahead == ' ') ADVANCE(6);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\r') ADVANCE(13);
      END_STATE();
    case 2:
      if (lookahead == ' ') ADVANCE(6);
      if (lookahead == '`') ADVANCE(12);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(13);
      END_STATE();
    case 3:
      if (eof) ADVANCE(4);
      if (lookahead == ' ') ADVANCE(6);
      if (lookahead == '#') ADVANCE(17);
      if (lookahead == '*') ADVANCE(7);
      if (lookahead == '=') ADVANCE(8);
      if (lookahead == '>') ADVANCE(21);
      if (lookahead == '`') ADVANCE(11);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(13);
      END_STATE();
    case 4:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 5:
      ACCEPT_TOKEN(anon_sym_LF);
      END_STATE();
    case 6:
      ACCEPT_TOKEN(anon_sym_);
      END_STATE();
    case 7:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == ' ') ADVANCE(20);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(13);
      END_STATE();
    case 8:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '>') ADVANCE(14);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(13);
      END_STATE();
    case 9:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '`') ADVANCE(15);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(13);
      END_STATE();
    case 10:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '`') ADVANCE(16);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(13);
      END_STATE();
    case 11:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '`') ADVANCE(9);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(13);
      END_STATE();
    case 12:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '`') ADVANCE(10);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(13);
      END_STATE();
    case 13:
      ACCEPT_TOKEN(sym__word);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(13);
      END_STATE();
    case 14:
      ACCEPT_TOKEN(anon_sym_EQ_GT);
      END_STATE();
    case 15:
      ACCEPT_TOKEN(anon_sym_BQUOTE_BQUOTE_BQUOTE);
      END_STATE();
    case 16:
      ACCEPT_TOKEN(sym_end_pre);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(13);
      END_STATE();
    case 17:
      ACCEPT_TOKEN(anon_sym_POUND);
      if (lookahead == '#') ADVANCE(18);
      END_STATE();
    case 18:
      ACCEPT_TOKEN(anon_sym_POUND_POUND);
      if (lookahead == '#') ADVANCE(19);
      END_STATE();
    case 19:
      ACCEPT_TOKEN(anon_sym_POUND_POUND_POUND);
      END_STATE();
    case 20:
      ACCEPT_TOKEN(anon_sym_STAR);
      END_STATE();
    case 21:
      ACCEPT_TOKEN(anon_sym_GT);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 3},
  [2] = {.lex_state = 3},
  [3] = {.lex_state = 3},
  [4] = {.lex_state = 3},
  [5] = {.lex_state = 3},
  [6] = {.lex_state = 3},
  [7] = {.lex_state = 2},
  [8] = {.lex_state = 2},
  [9] = {.lex_state = 2},
  [10] = {.lex_state = 1},
  [11] = {.lex_state = 1},
  [12] = {.lex_state = 1},
  [13] = {.lex_state = 1},
  [14] = {.lex_state = 1},
  [15] = {.lex_state = 1},
  [16] = {.lex_state = 1},
  [17] = {.lex_state = 1},
  [18] = {.lex_state = 1},
  [19] = {.lex_state = 1},
  [20] = {.lex_state = 1},
  [21] = {.lex_state = 1},
  [22] = {.lex_state = 1},
  [23] = {.lex_state = 1},
  [24] = {.lex_state = 1},
  [25] = {.lex_state = 1},
  [26] = {.lex_state = 2},
  [27] = {.lex_state = 1},
  [28] = {.lex_state = 2},
  [29] = {.lex_state = 1},
  [30] = {.lex_state = 0},
  [31] = {.lex_state = 0},
  [32] = {.lex_state = 0},
  [33] = {.lex_state = 0},
  [34] = {.lex_state = 0},
  [35] = {.lex_state = 0},
  [36] = {.lex_state = 0},
  [37] = {.lex_state = 0},
  [38] = {.lex_state = 0},
  [39] = {.lex_state = 0},
  [40] = {.lex_state = 0},
  [41] = {.lex_state = 0},
  [42] = {.lex_state = 0},
  [43] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_LF] = ACTIONS(1),
    [anon_sym_] = ACTIONS(1),
    [sym__word] = ACTIONS(1),
    [anon_sym_EQ_GT] = ACTIONS(1),
    [anon_sym_BQUOTE_BQUOTE_BQUOTE] = ACTIONS(1),
    [sym_end_pre] = ACTIONS(1),
    [anon_sym_POUND] = ACTIONS(1),
    [anon_sym_POUND_POUND] = ACTIONS(1),
    [anon_sym_POUND_POUND_POUND] = ACTIONS(1),
    [anon_sym_STAR] = ACTIONS(1),
    [anon_sym_GT] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(37),
    [aux_sym__space] = STATE(12),
    [sym_text] = STATE(42),
    [sym_link] = STATE(42),
    [sym_start_pre] = STATE(9),
    [sym_heading1] = STATE(42),
    [sym_heading2] = STATE(42),
    [sym_heading3] = STATE(42),
    [sym_ulist] = STATE(42),
    [sym_quote] = STATE(42),
    [aux_sym_source_file_repeat2] = STATE(3),
    [aux_sym_text_repeat1] = STATE(27),
    [ts_builtin_sym_end] = ACTIONS(3),
    [anon_sym_] = ACTIONS(5),
    [sym__word] = ACTIONS(7),
    [anon_sym_EQ_GT] = ACTIONS(9),
    [anon_sym_BQUOTE_BQUOTE_BQUOTE] = ACTIONS(11),
    [anon_sym_POUND] = ACTIONS(13),
    [anon_sym_POUND_POUND] = ACTIONS(15),
    [anon_sym_POUND_POUND_POUND] = ACTIONS(17),
    [anon_sym_STAR] = ACTIONS(19),
    [anon_sym_GT] = ACTIONS(21),
  },
  [2] = {
    [aux_sym__space] = STATE(12),
    [sym_text] = STATE(42),
    [sym_link] = STATE(42),
    [sym_start_pre] = STATE(9),
    [sym_heading1] = STATE(42),
    [sym_heading2] = STATE(42),
    [sym_heading3] = STATE(42),
    [sym_ulist] = STATE(42),
    [sym_quote] = STATE(42),
    [aux_sym_source_file_repeat2] = STATE(2),
    [aux_sym_text_repeat1] = STATE(27),
    [ts_builtin_sym_end] = ACTIONS(23),
    [anon_sym_] = ACTIONS(25),
    [sym__word] = ACTIONS(28),
    [anon_sym_EQ_GT] = ACTIONS(31),
    [anon_sym_BQUOTE_BQUOTE_BQUOTE] = ACTIONS(34),
    [anon_sym_POUND] = ACTIONS(37),
    [anon_sym_POUND_POUND] = ACTIONS(40),
    [anon_sym_POUND_POUND_POUND] = ACTIONS(43),
    [anon_sym_STAR] = ACTIONS(46),
    [anon_sym_GT] = ACTIONS(49),
  },
  [3] = {
    [aux_sym__space] = STATE(12),
    [sym_text] = STATE(42),
    [sym_link] = STATE(42),
    [sym_start_pre] = STATE(9),
    [sym_heading1] = STATE(42),
    [sym_heading2] = STATE(42),
    [sym_heading3] = STATE(42),
    [sym_ulist] = STATE(42),
    [sym_quote] = STATE(42),
    [aux_sym_source_file_repeat2] = STATE(2),
    [aux_sym_text_repeat1] = STATE(27),
    [ts_builtin_sym_end] = ACTIONS(52),
    [anon_sym_] = ACTIONS(5),
    [sym__word] = ACTIONS(7),
    [anon_sym_EQ_GT] = ACTIONS(9),
    [anon_sym_BQUOTE_BQUOTE_BQUOTE] = ACTIONS(11),
    [anon_sym_POUND] = ACTIONS(13),
    [anon_sym_POUND_POUND] = ACTIONS(15),
    [anon_sym_POUND_POUND_POUND] = ACTIONS(17),
    [anon_sym_STAR] = ACTIONS(19),
    [anon_sym_GT] = ACTIONS(21),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 2,
    ACTIONS(56), 3,
      sym__word,
      anon_sym_POUND,
      anon_sym_POUND_POUND,
    ACTIONS(54), 7,
      ts_builtin_sym_end,
      anon_sym_,
      anon_sym_EQ_GT,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      anon_sym_POUND_POUND_POUND,
      anon_sym_STAR,
      anon_sym_GT,
  [15] = 2,
    ACTIONS(60), 3,
      sym__word,
      anon_sym_POUND,
      anon_sym_POUND_POUND,
    ACTIONS(58), 7,
      ts_builtin_sym_end,
      anon_sym_,
      anon_sym_EQ_GT,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      anon_sym_POUND_POUND_POUND,
      anon_sym_STAR,
      anon_sym_GT,
  [30] = 2,
    ACTIONS(62), 3,
      sym__word,
      anon_sym_POUND,
      anon_sym_POUND_POUND,
    ACTIONS(23), 7,
      ts_builtin_sym_end,
      anon_sym_,
      anon_sym_EQ_GT,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      anon_sym_POUND_POUND_POUND,
      anon_sym_STAR,
      anon_sym_GT,
  [45] = 8,
    ACTIONS(64), 1,
      anon_sym_,
    ACTIONS(67), 1,
      sym__word,
    ACTIONS(70), 1,
      sym_end_pre,
    STATE(7), 1,
      aux_sym_source_file_repeat1,
    STATE(21), 1,
      aux_sym__space,
    STATE(27), 1,
      aux_sym_text_repeat1,
    STATE(35), 1,
      sym_text,
    STATE(36), 1,
      sym_pre,
  [70] = 8,
    ACTIONS(7), 1,
      sym__word,
    ACTIONS(72), 1,
      anon_sym_,
    ACTIONS(74), 1,
      sym_end_pre,
    STATE(7), 1,
      aux_sym_source_file_repeat1,
    STATE(21), 1,
      aux_sym__space,
    STATE(27), 1,
      aux_sym_text_repeat1,
    STATE(35), 1,
      sym_text,
    STATE(36), 1,
      sym_pre,
  [95] = 8,
    ACTIONS(7), 1,
      sym__word,
    ACTIONS(72), 1,
      anon_sym_,
    ACTIONS(76), 1,
      sym_end_pre,
    STATE(8), 1,
      aux_sym_source_file_repeat1,
    STATE(21), 1,
      aux_sym__space,
    STATE(27), 1,
      aux_sym_text_repeat1,
    STATE(35), 1,
      sym_text,
    STATE(36), 1,
      sym_pre,
  [120] = 6,
    ACTIONS(72), 1,
      anon_sym_,
    ACTIONS(78), 1,
      anon_sym_LF,
    ACTIONS(80), 1,
      sym__word,
    STATE(21), 1,
      aux_sym__space,
    STATE(27), 1,
      aux_sym_text_repeat1,
    STATE(40), 1,
      sym_text,
  [139] = 6,
    ACTIONS(72), 1,
      anon_sym_,
    ACTIONS(80), 1,
      sym__word,
    ACTIONS(82), 1,
      anon_sym_LF,
    STATE(21), 1,
      aux_sym__space,
    STATE(27), 1,
      aux_sym_text_repeat1,
    STATE(43), 1,
      sym_text,
  [158] = 5,
    ACTIONS(80), 1,
      sym__word,
    ACTIONS(84), 1,
      anon_sym_LF,
    ACTIONS(86), 1,
      anon_sym_,
    STATE(19), 1,
      aux_sym__space,
    STATE(24), 1,
      aux_sym_text_repeat1,
  [174] = 5,
    ACTIONS(72), 1,
      anon_sym_,
    ACTIONS(80), 1,
      sym__word,
    STATE(21), 1,
      aux_sym__space,
    STATE(27), 1,
      aux_sym_text_repeat1,
    STATE(39), 1,
      sym_text,
  [190] = 5,
    ACTIONS(72), 1,
      anon_sym_,
    ACTIONS(80), 1,
      sym__word,
    STATE(21), 1,
      aux_sym__space,
    STATE(27), 1,
      aux_sym_text_repeat1,
    STATE(38), 1,
      sym_text,
  [206] = 5,
    ACTIONS(72), 1,
      anon_sym_,
    ACTIONS(80), 1,
      sym__word,
    STATE(21), 1,
      aux_sym__space,
    STATE(27), 1,
      aux_sym_text_repeat1,
    STATE(30), 1,
      sym_text,
  [222] = 5,
    ACTIONS(72), 1,
      anon_sym_,
    ACTIONS(80), 1,
      sym__word,
    STATE(21), 1,
      aux_sym__space,
    STATE(27), 1,
      aux_sym_text_repeat1,
    STATE(33), 1,
      sym_text,
  [238] = 5,
    ACTIONS(72), 1,
      anon_sym_,
    ACTIONS(80), 1,
      sym__word,
    STATE(21), 1,
      aux_sym__space,
    STATE(27), 1,
      aux_sym_text_repeat1,
    STATE(31), 1,
      sym_text,
  [254] = 5,
    ACTIONS(72), 1,
      anon_sym_,
    ACTIONS(80), 1,
      sym__word,
    STATE(21), 1,
      aux_sym__space,
    STATE(27), 1,
      aux_sym_text_repeat1,
    STATE(32), 1,
      sym_text,
  [270] = 3,
    ACTIONS(90), 1,
      anon_sym_,
    STATE(19), 1,
      aux_sym__space,
    ACTIONS(88), 2,
      anon_sym_LF,
      sym__word,
  [281] = 3,
    ACTIONS(86), 1,
      anon_sym_,
    STATE(19), 1,
      aux_sym__space,
    ACTIONS(93), 2,
      anon_sym_LF,
      sym__word,
  [292] = 4,
    ACTIONS(80), 1,
      sym__word,
    ACTIONS(86), 1,
      anon_sym_,
    STATE(19), 1,
      aux_sym__space,
    STATE(24), 1,
      aux_sym_text_repeat1,
  [305] = 3,
    ACTIONS(97), 1,
      anon_sym_,
    STATE(20), 1,
      aux_sym__space,
    ACTIONS(95), 2,
      anon_sym_LF,
      sym__word,
  [316] = 3,
    ACTIONS(93), 1,
      anon_sym_LF,
    ACTIONS(99), 1,
      sym__word,
    STATE(23), 1,
      aux_sym_text_repeat1,
  [326] = 3,
    ACTIONS(80), 1,
      sym__word,
    ACTIONS(102), 1,
      anon_sym_LF,
    STATE(23), 1,
      aux_sym_text_repeat1,
  [336] = 3,
    ACTIONS(86), 1,
      anon_sym_,
    ACTIONS(104), 1,
      sym__word,
    STATE(19), 1,
      aux_sym__space,
  [346] = 2,
    ACTIONS(106), 1,
      anon_sym_,
    ACTIONS(108), 2,
      sym__word,
      sym_end_pre,
  [354] = 3,
    ACTIONS(80), 1,
      sym__word,
    ACTIONS(110), 1,
      anon_sym_LF,
    STATE(23), 1,
      aux_sym_text_repeat1,
  [364] = 2,
    ACTIONS(112), 1,
      anon_sym_,
    ACTIONS(70), 2,
      sym__word,
      sym_end_pre,
  [372] = 3,
    ACTIONS(114), 1,
      anon_sym_,
    ACTIONS(116), 1,
      sym__word,
    STATE(25), 1,
      aux_sym__space,
  [382] = 1,
    ACTIONS(118), 1,
      anon_sym_LF,
  [386] = 1,
    ACTIONS(120), 1,
      anon_sym_LF,
  [390] = 1,
    ACTIONS(122), 1,
      anon_sym_LF,
  [394] = 1,
    ACTIONS(124), 1,
      anon_sym_LF,
  [398] = 1,
    ACTIONS(126), 1,
      anon_sym_LF,
  [402] = 1,
    ACTIONS(128), 1,
      anon_sym_LF,
  [406] = 1,
    ACTIONS(130), 1,
      anon_sym_LF,
  [410] = 1,
    ACTIONS(132), 1,
      ts_builtin_sym_end,
  [414] = 1,
    ACTIONS(134), 1,
      anon_sym_LF,
  [418] = 1,
    ACTIONS(136), 1,
      anon_sym_LF,
  [422] = 1,
    ACTIONS(138), 1,
      anon_sym_LF,
  [426] = 1,
    ACTIONS(140), 1,
      anon_sym_LF,
  [430] = 1,
    ACTIONS(84), 1,
      anon_sym_LF,
  [434] = 1,
    ACTIONS(142), 1,
      anon_sym_LF,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(4)] = 0,
  [SMALL_STATE(5)] = 15,
  [SMALL_STATE(6)] = 30,
  [SMALL_STATE(7)] = 45,
  [SMALL_STATE(8)] = 70,
  [SMALL_STATE(9)] = 95,
  [SMALL_STATE(10)] = 120,
  [SMALL_STATE(11)] = 139,
  [SMALL_STATE(12)] = 158,
  [SMALL_STATE(13)] = 174,
  [SMALL_STATE(14)] = 190,
  [SMALL_STATE(15)] = 206,
  [SMALL_STATE(16)] = 222,
  [SMALL_STATE(17)] = 238,
  [SMALL_STATE(18)] = 254,
  [SMALL_STATE(19)] = 270,
  [SMALL_STATE(20)] = 281,
  [SMALL_STATE(21)] = 292,
  [SMALL_STATE(22)] = 305,
  [SMALL_STATE(23)] = 316,
  [SMALL_STATE(24)] = 326,
  [SMALL_STATE(25)] = 336,
  [SMALL_STATE(26)] = 346,
  [SMALL_STATE(27)] = 354,
  [SMALL_STATE(28)] = 364,
  [SMALL_STATE(29)] = 372,
  [SMALL_STATE(30)] = 382,
  [SMALL_STATE(31)] = 386,
  [SMALL_STATE(32)] = 390,
  [SMALL_STATE(33)] = 394,
  [SMALL_STATE(34)] = 398,
  [SMALL_STATE(35)] = 402,
  [SMALL_STATE(36)] = 406,
  [SMALL_STATE(37)] = 410,
  [SMALL_STATE(38)] = 414,
  [SMALL_STATE(39)] = 418,
  [SMALL_STATE(40)] = 422,
  [SMALL_STATE(41)] = 426,
  [SMALL_STATE(42)] = 430,
  [SMALL_STATE(43)] = 434,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(22),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(14),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(15),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [23] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2),
  [25] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2), SHIFT_REPEAT(12),
  [28] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat2, 2), SHIFT_REPEAT(22),
  [31] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2), SHIFT_REPEAT(29),
  [34] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2), SHIFT_REPEAT(13),
  [37] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat2, 2), SHIFT_REPEAT(14),
  [40] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat2, 2), SHIFT_REPEAT(15),
  [43] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2), SHIFT_REPEAT(17),
  [46] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2), SHIFT_REPEAT(18),
  [49] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2), SHIFT_REPEAT(16),
  [52] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [54] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 4),
  [56] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_source_file_repeat2, 4),
  [58] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 3),
  [60] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_source_file_repeat2, 3),
  [62] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_source_file_repeat2, 2),
  [64] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(21),
  [67] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(22),
  [70] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [72] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [74] = {.entry = {.count = 1, .reusable = false}}, SHIFT(41),
  [76] = {.entry = {.count = 1, .reusable = false}}, SHIFT(34),
  [78] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_link, 2, .production_id = 1),
  [80] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [82] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_link, 3, .production_id = 3),
  [84] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [86] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [88] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__space, 2),
  [90] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__space, 2), SHIFT_REPEAT(19),
  [93] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_text_repeat1, 2),
  [95] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_text_repeat1, 1),
  [97] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [99] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_text_repeat1, 2), SHIFT_REPEAT(22),
  [102] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_text, 2),
  [104] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [106] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_start_pre, 3, .production_id = 4),
  [108] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_start_pre, 3, .production_id = 4),
  [110] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_text, 1),
  [112] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [114] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [116] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [118] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_heading2, 2),
  [120] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_heading3, 2),
  [122] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ulist, 2),
  [124] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_quote, 2),
  [126] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [128] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pre, 1),
  [130] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [132] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [134] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_heading1, 2),
  [136] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [138] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_link, 3, .production_id = 2),
  [140] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [142] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_link, 4, .production_id = 5),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_gemini(void) {
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
