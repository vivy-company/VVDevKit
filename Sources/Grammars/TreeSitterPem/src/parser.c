#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 40
#define LARGE_STATE_COUNT 6
#define SYMBOL_COUNT 32
#define ALIAS_COUNT 0
#define TOKEN_COUNT 17
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 5
#define PRODUCTION_ID_COUNT 1

enum {
  anon_sym_ = 1,
  anon_sym_2 = 2,
  anon_sym_DASH_DASH_DASH_DASH_DASHBEGIN = 3,
  anon_sym_DASH_DASH_DASH_DASH_DASH = 4,
  anon_sym_DASH_DASH_DASH_DASH_DASHEND = 5,
  anon_sym_PLUS = 6,
  anon_sym_SLASH = 7,
  sym_base64pad = 8,
  sym__labelchar = 9,
  anon_sym_DASH = 10,
  sym__ALPHA = 11,
  sym__DIGIT = 12,
  sym__SP = 13,
  sym__HTAB = 14,
  sym__CR = 15,
  sym__LF = 16,
  sym_pem_file = 17,
  sym_laxtextualmsg = 18,
  sym__W = 19,
  sym___laxbase64text_char = 20,
  sym__laxbase64text_padding = 21,
  sym_laxbase64text = 22,
  sym_preeb = 23,
  sym_posteb = 24,
  sym__base64char = 25,
  sym_label = 26,
  sym__WSP = 27,
  aux_sym_pem_file_repeat1 = 28,
  aux_sym_laxtextualmsg_repeat1 = 29,
  aux_sym_laxbase64text_repeat1 = 30,
  aux_sym_label_repeat1 = 31,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_] = "",
  [anon_sym_2] = "\f",
  [anon_sym_DASH_DASH_DASH_DASH_DASHBEGIN] = "-----BEGIN ",
  [anon_sym_DASH_DASH_DASH_DASH_DASH] = "-----",
  [anon_sym_DASH_DASH_DASH_DASH_DASHEND] = "-----END ",
  [anon_sym_PLUS] = "+",
  [anon_sym_SLASH] = "/",
  [sym_base64pad] = "base64pad",
  [sym__labelchar] = "_labelchar",
  [anon_sym_DASH] = "-",
  [sym__ALPHA] = "_ALPHA",
  [sym__DIGIT] = "_DIGIT",
  [sym__SP] = "_SP",
  [sym__HTAB] = "_HTAB",
  [sym__CR] = "_CR",
  [sym__LF] = "_LF",
  [sym_pem_file] = "pem_file",
  [sym_laxtextualmsg] = "laxtextualmsg",
  [sym__W] = "_W",
  [sym___laxbase64text_char] = "__laxbase64text_char",
  [sym__laxbase64text_padding] = "_laxbase64text_padding",
  [sym_laxbase64text] = "laxbase64text",
  [sym_preeb] = "preeb",
  [sym_posteb] = "posteb",
  [sym__base64char] = "_base64char",
  [sym_label] = "label",
  [sym__WSP] = "_WSP",
  [aux_sym_pem_file_repeat1] = "pem_file_repeat1",
  [aux_sym_laxtextualmsg_repeat1] = "laxtextualmsg_repeat1",
  [aux_sym_laxbase64text_repeat1] = "laxbase64text_repeat1",
  [aux_sym_label_repeat1] = "label_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_] = anon_sym_,
  [anon_sym_2] = anon_sym_2,
  [anon_sym_DASH_DASH_DASH_DASH_DASHBEGIN] = anon_sym_DASH_DASH_DASH_DASH_DASHBEGIN,
  [anon_sym_DASH_DASH_DASH_DASH_DASH] = anon_sym_DASH_DASH_DASH_DASH_DASH,
  [anon_sym_DASH_DASH_DASH_DASH_DASHEND] = anon_sym_DASH_DASH_DASH_DASH_DASHEND,
  [anon_sym_PLUS] = anon_sym_PLUS,
  [anon_sym_SLASH] = anon_sym_SLASH,
  [sym_base64pad] = sym_base64pad,
  [sym__labelchar] = sym__labelchar,
  [anon_sym_DASH] = anon_sym_DASH,
  [sym__ALPHA] = sym__ALPHA,
  [sym__DIGIT] = sym__DIGIT,
  [sym__SP] = sym__SP,
  [sym__HTAB] = sym__HTAB,
  [sym__CR] = sym__CR,
  [sym__LF] = sym__LF,
  [sym_pem_file] = sym_pem_file,
  [sym_laxtextualmsg] = sym_laxtextualmsg,
  [sym__W] = sym__W,
  [sym___laxbase64text_char] = sym___laxbase64text_char,
  [sym__laxbase64text_padding] = sym__laxbase64text_padding,
  [sym_laxbase64text] = sym_laxbase64text,
  [sym_preeb] = sym_preeb,
  [sym_posteb] = sym_posteb,
  [sym__base64char] = sym__base64char,
  [sym_label] = sym_label,
  [sym__WSP] = sym__WSP,
  [aux_sym_pem_file_repeat1] = aux_sym_pem_file_repeat1,
  [aux_sym_laxtextualmsg_repeat1] = aux_sym_laxtextualmsg_repeat1,
  [aux_sym_laxbase64text_repeat1] = aux_sym_laxbase64text_repeat1,
  [aux_sym_label_repeat1] = aux_sym_label_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_2] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH_DASH_DASH_DASH_DASHBEGIN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH_DASH_DASH_DASH_DASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH_DASH_DASH_DASH_DASHEND] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PLUS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SLASH] = {
    .visible = true,
    .named = false,
  },
  [sym_base64pad] = {
    .visible = true,
    .named = true,
  },
  [sym__labelchar] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_DASH] = {
    .visible = true,
    .named = false,
  },
  [sym__ALPHA] = {
    .visible = false,
    .named = true,
  },
  [sym__DIGIT] = {
    .visible = false,
    .named = true,
  },
  [sym__SP] = {
    .visible = false,
    .named = true,
  },
  [sym__HTAB] = {
    .visible = false,
    .named = true,
  },
  [sym__CR] = {
    .visible = false,
    .named = true,
  },
  [sym__LF] = {
    .visible = false,
    .named = true,
  },
  [sym_pem_file] = {
    .visible = true,
    .named = true,
  },
  [sym_laxtextualmsg] = {
    .visible = true,
    .named = true,
  },
  [sym__W] = {
    .visible = false,
    .named = true,
  },
  [sym___laxbase64text_char] = {
    .visible = false,
    .named = true,
  },
  [sym__laxbase64text_padding] = {
    .visible = false,
    .named = true,
  },
  [sym_laxbase64text] = {
    .visible = true,
    .named = true,
  },
  [sym_preeb] = {
    .visible = true,
    .named = true,
  },
  [sym_posteb] = {
    .visible = true,
    .named = true,
  },
  [sym__base64char] = {
    .visible = false,
    .named = true,
  },
  [sym_label] = {
    .visible = true,
    .named = true,
  },
  [sym__WSP] = {
    .visible = false,
    .named = true,
  },
  [aux_sym_pem_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_laxtextualmsg_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_laxbase64text_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_label_repeat1] = {
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
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(19);
      if (lookahead == '\t') ADVANCE(33);
      if (lookahead == '\n') ADVANCE(35);
      if (lookahead == 11) ADVANCE(20);
      if (lookahead == '\f') ADVANCE(21);
      if (lookahead == '\r') ADVANCE(34);
      if (lookahead == ' ') ADVANCE(32);
      if (lookahead == '+') ADVANCE(25);
      if (lookahead == '-') ADVANCE(29);
      if (lookahead == '/') ADVANCE(26);
      if (lookahead == '=') ADVANCE(27);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(28);
      if (('!' <= lookahead && lookahead <= '@') ||
          ('[' <= lookahead && lookahead <= '`') ||
          ('{' <= lookahead && lookahead <= '~')) ADVANCE(28);
      if (('A' <= lookahead && lookahead <= 'z')) ADVANCE(28);
      END_STATE();
    case 1:
      if (lookahead == ' ') ADVANCE(32);
      if (lookahead == '-') ADVANCE(29);
      if (('!' <= lookahead && lookahead <= '~')) ADVANCE(28);
      END_STATE();
    case 2:
      if (lookahead == ' ') ADVANCE(24);
      END_STATE();
    case 3:
      if (lookahead == ' ') ADVANCE(22);
      END_STATE();
    case 4:
      if (lookahead == '-') ADVANCE(23);
      END_STATE();
    case 5:
      if (lookahead == '-') ADVANCE(11);
      END_STATE();
    case 6:
      if (lookahead == '-') ADVANCE(4);
      END_STATE();
    case 7:
      if (lookahead == '-') ADVANCE(5);
      END_STATE();
    case 8:
      if (lookahead == '-') ADVANCE(6);
      END_STATE();
    case 9:
      if (lookahead == '-') ADVANCE(7);
      END_STATE();
    case 10:
      if (lookahead == '-') ADVANCE(9);
      END_STATE();
    case 11:
      if (lookahead == 'B') ADVANCE(13);
      if (lookahead == 'E') ADVANCE(16);
      END_STATE();
    case 12:
      if (lookahead == 'D') ADVANCE(2);
      END_STATE();
    case 13:
      if (lookahead == 'E') ADVANCE(14);
      END_STATE();
    case 14:
      if (lookahead == 'G') ADVANCE(15);
      END_STATE();
    case 15:
      if (lookahead == 'I') ADVANCE(17);
      END_STATE();
    case 16:
      if (lookahead == 'N') ADVANCE(12);
      END_STATE();
    case 17:
      if (lookahead == 'N') ADVANCE(3);
      END_STATE();
    case 18:
      if (eof) ADVANCE(19);
      if (lookahead == '\t') ADVANCE(33);
      if (lookahead == '\n') ADVANCE(35);
      if (lookahead == 11) ADVANCE(20);
      if (lookahead == '\f') ADVANCE(21);
      if (lookahead == '\r') ADVANCE(34);
      if (lookahead == ' ') ADVANCE(32);
      if (lookahead == '+') ADVANCE(25);
      if (lookahead == '-') ADVANCE(10);
      if (lookahead == '/') ADVANCE(26);
      if (lookahead == '=') ADVANCE(27);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(31);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(30);
      END_STATE();
    case 19:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 20:
      ACCEPT_TOKEN(anon_sym_);
      END_STATE();
    case 21:
      ACCEPT_TOKEN(anon_sym_2);
      END_STATE();
    case 22:
      ACCEPT_TOKEN(anon_sym_DASH_DASH_DASH_DASH_DASHBEGIN);
      END_STATE();
    case 23:
      ACCEPT_TOKEN(anon_sym_DASH_DASH_DASH_DASH_DASH);
      END_STATE();
    case 24:
      ACCEPT_TOKEN(anon_sym_DASH_DASH_DASH_DASH_DASHEND);
      END_STATE();
    case 25:
      ACCEPT_TOKEN(anon_sym_PLUS);
      END_STATE();
    case 26:
      ACCEPT_TOKEN(anon_sym_SLASH);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(sym_base64pad);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(sym__labelchar);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(anon_sym_DASH);
      if (lookahead == '-') ADVANCE(8);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(sym__ALPHA);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(sym__DIGIT);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(sym__SP);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(sym__HTAB);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(sym__CR);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(sym__LF);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 18},
  [2] = {.lex_state = 18},
  [3] = {.lex_state = 18},
  [4] = {.lex_state = 18},
  [5] = {.lex_state = 18},
  [6] = {.lex_state = 18},
  [7] = {.lex_state = 18},
  [8] = {.lex_state = 18},
  [9] = {.lex_state = 18},
  [10] = {.lex_state = 18},
  [11] = {.lex_state = 18},
  [12] = {.lex_state = 18},
  [13] = {.lex_state = 18},
  [14] = {.lex_state = 18},
  [15] = {.lex_state = 18},
  [16] = {.lex_state = 18},
  [17] = {.lex_state = 18},
  [18] = {.lex_state = 18},
  [19] = {.lex_state = 18},
  [20] = {.lex_state = 18},
  [21] = {.lex_state = 18},
  [22] = {.lex_state = 18},
  [23] = {.lex_state = 18},
  [24] = {.lex_state = 18},
  [25] = {.lex_state = 18},
  [26] = {.lex_state = 1},
  [27] = {.lex_state = 1},
  [28] = {.lex_state = 1},
  [29] = {.lex_state = 1},
  [30] = {.lex_state = 1},
  [31] = {.lex_state = 1},
  [32] = {.lex_state = 18},
  [33] = {.lex_state = 18},
  [34] = {.lex_state = 18},
  [35] = {.lex_state = 0},
  [36] = {.lex_state = 1},
  [37] = {.lex_state = 18},
  [38] = {.lex_state = 0},
  [39] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_] = ACTIONS(1),
    [anon_sym_2] = ACTIONS(1),
    [anon_sym_DASH_DASH_DASH_DASH_DASH] = ACTIONS(1),
    [anon_sym_PLUS] = ACTIONS(1),
    [anon_sym_SLASH] = ACTIONS(1),
    [sym_base64pad] = ACTIONS(1),
    [sym__labelchar] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [sym__ALPHA] = ACTIONS(1),
    [sym__DIGIT] = ACTIONS(1),
    [sym__SP] = ACTIONS(1),
    [sym__HTAB] = ACTIONS(1),
    [sym__CR] = ACTIONS(1),
    [sym__LF] = ACTIONS(1),
  },
  [1] = {
    [sym_pem_file] = STATE(39),
    [sym_laxtextualmsg] = STATE(6),
    [sym__W] = STATE(16),
    [sym_preeb] = STATE(2),
    [sym__WSP] = STATE(16),
    [aux_sym_pem_file_repeat1] = STATE(6),
    [aux_sym_laxtextualmsg_repeat1] = STATE(16),
    [ts_builtin_sym_end] = ACTIONS(3),
    [anon_sym_] = ACTIONS(5),
    [anon_sym_2] = ACTIONS(5),
    [anon_sym_DASH_DASH_DASH_DASH_DASHBEGIN] = ACTIONS(7),
    [sym__SP] = ACTIONS(5),
    [sym__HTAB] = ACTIONS(5),
    [sym__CR] = ACTIONS(5),
    [sym__LF] = ACTIONS(5),
  },
  [2] = {
    [sym__W] = STATE(4),
    [sym___laxbase64text_char] = STATE(4),
    [sym__laxbase64text_padding] = STATE(37),
    [sym_laxbase64text] = STATE(33),
    [sym_posteb] = STATE(14),
    [sym__base64char] = STATE(4),
    [sym__WSP] = STATE(4),
    [aux_sym_laxbase64text_repeat1] = STATE(4),
    [anon_sym_] = ACTIONS(9),
    [anon_sym_2] = ACTIONS(9),
    [anon_sym_DASH_DASH_DASH_DASH_DASHEND] = ACTIONS(11),
    [anon_sym_PLUS] = ACTIONS(9),
    [anon_sym_SLASH] = ACTIONS(9),
    [sym_base64pad] = ACTIONS(13),
    [sym__ALPHA] = ACTIONS(9),
    [sym__DIGIT] = ACTIONS(9),
    [sym__SP] = ACTIONS(9),
    [sym__HTAB] = ACTIONS(9),
    [sym__CR] = ACTIONS(9),
    [sym__LF] = ACTIONS(9),
  },
  [3] = {
    [sym__W] = STATE(4),
    [sym___laxbase64text_char] = STATE(4),
    [sym__laxbase64text_padding] = STATE(37),
    [sym_laxbase64text] = STATE(32),
    [sym_posteb] = STATE(18),
    [sym__base64char] = STATE(4),
    [sym__WSP] = STATE(4),
    [aux_sym_laxbase64text_repeat1] = STATE(4),
    [anon_sym_] = ACTIONS(9),
    [anon_sym_2] = ACTIONS(9),
    [anon_sym_DASH_DASH_DASH_DASH_DASHEND] = ACTIONS(11),
    [anon_sym_PLUS] = ACTIONS(9),
    [anon_sym_SLASH] = ACTIONS(9),
    [sym_base64pad] = ACTIONS(13),
    [sym__ALPHA] = ACTIONS(9),
    [sym__DIGIT] = ACTIONS(9),
    [sym__SP] = ACTIONS(9),
    [sym__HTAB] = ACTIONS(9),
    [sym__CR] = ACTIONS(9),
    [sym__LF] = ACTIONS(9),
  },
  [4] = {
    [sym__W] = STATE(5),
    [sym___laxbase64text_char] = STATE(5),
    [sym__laxbase64text_padding] = STATE(34),
    [sym__base64char] = STATE(5),
    [sym__WSP] = STATE(5),
    [aux_sym_laxbase64text_repeat1] = STATE(5),
    [anon_sym_] = ACTIONS(15),
    [anon_sym_2] = ACTIONS(15),
    [anon_sym_DASH_DASH_DASH_DASH_DASHEND] = ACTIONS(17),
    [anon_sym_PLUS] = ACTIONS(15),
    [anon_sym_SLASH] = ACTIONS(15),
    [sym_base64pad] = ACTIONS(13),
    [sym__ALPHA] = ACTIONS(15),
    [sym__DIGIT] = ACTIONS(15),
    [sym__SP] = ACTIONS(15),
    [sym__HTAB] = ACTIONS(15),
    [sym__CR] = ACTIONS(15),
    [sym__LF] = ACTIONS(15),
  },
  [5] = {
    [sym__W] = STATE(5),
    [sym___laxbase64text_char] = STATE(5),
    [sym__base64char] = STATE(5),
    [sym__WSP] = STATE(5),
    [aux_sym_laxbase64text_repeat1] = STATE(5),
    [anon_sym_] = ACTIONS(19),
    [anon_sym_2] = ACTIONS(19),
    [anon_sym_DASH_DASH_DASH_DASH_DASHEND] = ACTIONS(22),
    [anon_sym_PLUS] = ACTIONS(19),
    [anon_sym_SLASH] = ACTIONS(19),
    [sym_base64pad] = ACTIONS(22),
    [sym__ALPHA] = ACTIONS(19),
    [sym__DIGIT] = ACTIONS(19),
    [sym__SP] = ACTIONS(19),
    [sym__HTAB] = ACTIONS(19),
    [sym__CR] = ACTIONS(19),
    [sym__LF] = ACTIONS(19),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 6,
    ACTIONS(7), 1,
      anon_sym_DASH_DASH_DASH_DASH_DASHBEGIN,
    ACTIONS(24), 1,
      ts_builtin_sym_end,
    STATE(2), 1,
      sym_preeb,
    STATE(7), 2,
      sym_laxtextualmsg,
      aux_sym_pem_file_repeat1,
    STATE(16), 3,
      sym__W,
      sym__WSP,
      aux_sym_laxtextualmsg_repeat1,
    ACTIONS(5), 6,
      anon_sym_,
      anon_sym_2,
      sym__SP,
      sym__HTAB,
      sym__CR,
      sym__LF,
  [27] = 6,
    ACTIONS(26), 1,
      ts_builtin_sym_end,
    ACTIONS(31), 1,
      anon_sym_DASH_DASH_DASH_DASH_DASHBEGIN,
    STATE(2), 1,
      sym_preeb,
    STATE(7), 2,
      sym_laxtextualmsg,
      aux_sym_pem_file_repeat1,
    STATE(16), 3,
      sym__W,
      sym__WSP,
      aux_sym_laxtextualmsg_repeat1,
    ACTIONS(28), 6,
      anon_sym_,
      anon_sym_2,
      sym__SP,
      sym__HTAB,
      sym__CR,
      sym__LF,
  [54] = 3,
    STATE(8), 3,
      sym__W,
      sym__WSP,
      aux_sym_laxtextualmsg_repeat1,
    ACTIONS(34), 4,
      ts_builtin_sym_end,
      anon_sym_DASH_DASH_DASH_DASH_DASHBEGIN,
      anon_sym_DASH_DASH_DASH_DASH_DASHEND,
      sym_base64pad,
    ACTIONS(36), 6,
      anon_sym_,
      anon_sym_2,
      sym__SP,
      sym__HTAB,
      sym__CR,
      sym__LF,
  [74] = 1,
    ACTIONS(39), 12,
      anon_sym_,
      anon_sym_2,
      anon_sym_DASH_DASH_DASH_DASH_DASHEND,
      anon_sym_PLUS,
      anon_sym_SLASH,
      sym_base64pad,
      sym__ALPHA,
      sym__DIGIT,
      sym__SP,
      sym__HTAB,
      sym__CR,
      sym__LF,
  [89] = 1,
    ACTIONS(41), 12,
      anon_sym_,
      anon_sym_2,
      anon_sym_DASH_DASH_DASH_DASH_DASHEND,
      anon_sym_PLUS,
      anon_sym_SLASH,
      sym_base64pad,
      sym__ALPHA,
      sym__DIGIT,
      sym__SP,
      sym__HTAB,
      sym__CR,
      sym__LF,
  [104] = 3,
    ACTIONS(43), 2,
      ts_builtin_sym_end,
      anon_sym_DASH_DASH_DASH_DASH_DASHBEGIN,
    STATE(15), 3,
      sym__W,
      sym__WSP,
      aux_sym_laxtextualmsg_repeat1,
    ACTIONS(45), 6,
      anon_sym_,
      anon_sym_2,
      sym__SP,
      sym__HTAB,
      sym__CR,
      sym__LF,
  [122] = 4,
    ACTIONS(50), 1,
      anon_sym_DASH_DASH_DASH_DASH_DASHEND,
    ACTIONS(52), 1,
      sym_base64pad,
    STATE(17), 3,
      sym__W,
      sym__WSP,
      aux_sym_laxtextualmsg_repeat1,
    ACTIONS(48), 6,
      anon_sym_,
      anon_sym_2,
      sym__SP,
      sym__HTAB,
      sym__CR,
      sym__LF,
  [142] = 3,
    ACTIONS(43), 2,
      ts_builtin_sym_end,
      anon_sym_DASH_DASH_DASH_DASH_DASHBEGIN,
    STATE(8), 3,
      sym__W,
      sym__WSP,
      aux_sym_laxtextualmsg_repeat1,
    ACTIONS(54), 6,
      anon_sym_,
      anon_sym_2,
      sym__SP,
      sym__HTAB,
      sym__CR,
      sym__LF,
  [160] = 3,
    ACTIONS(57), 2,
      ts_builtin_sym_end,
      anon_sym_DASH_DASH_DASH_DASH_DASHBEGIN,
    STATE(19), 3,
      sym__W,
      sym__WSP,
      aux_sym_laxtextualmsg_repeat1,
    ACTIONS(59), 6,
      anon_sym_,
      anon_sym_2,
      sym__SP,
      sym__HTAB,
      sym__CR,
      sym__LF,
  [178] = 3,
    ACTIONS(62), 2,
      ts_builtin_sym_end,
      anon_sym_DASH_DASH_DASH_DASH_DASHBEGIN,
    STATE(8), 3,
      sym__W,
      sym__WSP,
      aux_sym_laxtextualmsg_repeat1,
    ACTIONS(64), 6,
      anon_sym_,
      anon_sym_2,
      sym__SP,
      sym__HTAB,
      sym__CR,
      sym__LF,
  [196] = 4,
    ACTIONS(7), 1,
      anon_sym_DASH_DASH_DASH_DASH_DASHBEGIN,
    STATE(3), 1,
      sym_preeb,
    STATE(8), 3,
      sym__W,
      sym__WSP,
      aux_sym_laxtextualmsg_repeat1,
    ACTIONS(67), 6,
      anon_sym_,
      anon_sym_2,
      sym__SP,
      sym__HTAB,
      sym__CR,
      sym__LF,
  [216] = 4,
    ACTIONS(69), 1,
      anon_sym_DASH_DASH_DASH_DASH_DASHEND,
    ACTIONS(71), 1,
      sym_base64pad,
    STATE(8), 3,
      sym__W,
      sym__WSP,
      aux_sym_laxtextualmsg_repeat1,
    ACTIONS(67), 6,
      anon_sym_,
      anon_sym_2,
      sym__SP,
      sym__HTAB,
      sym__CR,
      sym__LF,
  [236] = 3,
    ACTIONS(73), 2,
      ts_builtin_sym_end,
      anon_sym_DASH_DASH_DASH_DASH_DASHBEGIN,
    STATE(13), 3,
      sym__W,
      sym__WSP,
      aux_sym_laxtextualmsg_repeat1,
    ACTIONS(75), 6,
      anon_sym_,
      anon_sym_2,
      sym__SP,
      sym__HTAB,
      sym__CR,
      sym__LF,
  [254] = 3,
    ACTIONS(73), 2,
      ts_builtin_sym_end,
      anon_sym_DASH_DASH_DASH_DASH_DASHBEGIN,
    STATE(8), 3,
      sym__W,
      sym__WSP,
      aux_sym_laxtextualmsg_repeat1,
    ACTIONS(78), 6,
      anon_sym_,
      anon_sym_2,
      sym__SP,
      sym__HTAB,
      sym__CR,
      sym__LF,
  [272] = 3,
    ACTIONS(83), 1,
      anon_sym_DASH_DASH_DASH_DASH_DASHEND,
    STATE(23), 3,
      sym__W,
      sym__WSP,
      aux_sym_laxtextualmsg_repeat1,
    ACTIONS(81), 6,
      anon_sym_,
      anon_sym_2,
      sym__SP,
      sym__HTAB,
      sym__CR,
      sym__LF,
  [289] = 3,
    ACTIONS(83), 1,
      anon_sym_DASH_DASH_DASH_DASH_DASHEND,
    STATE(8), 3,
      sym__W,
      sym__WSP,
      aux_sym_laxtextualmsg_repeat1,
    ACTIONS(67), 6,
      anon_sym_,
      anon_sym_2,
      sym__SP,
      sym__HTAB,
      sym__CR,
      sym__LF,
  [306] = 3,
    ACTIONS(69), 1,
      anon_sym_DASH_DASH_DASH_DASH_DASHEND,
    STATE(21), 3,
      sym__W,
      sym__WSP,
      aux_sym_laxtextualmsg_repeat1,
    ACTIONS(85), 6,
      anon_sym_,
      anon_sym_2,
      sym__SP,
      sym__HTAB,
      sym__CR,
      sym__LF,
  [323] = 3,
    ACTIONS(87), 1,
      anon_sym_DASH_DASH_DASH_DASH_DASHEND,
    STATE(8), 3,
      sym__W,
      sym__WSP,
      aux_sym_laxtextualmsg_repeat1,
    ACTIONS(67), 6,
      anon_sym_,
      anon_sym_2,
      sym__SP,
      sym__HTAB,
      sym__CR,
      sym__LF,
  [340] = 1,
    ACTIONS(89), 8,
      ts_builtin_sym_end,
      anon_sym_,
      anon_sym_2,
      anon_sym_DASH_DASH_DASH_DASH_DASHBEGIN,
      sym__SP,
      sym__HTAB,
      sym__CR,
      sym__LF,
  [351] = 1,
    ACTIONS(91), 8,
      ts_builtin_sym_end,
      anon_sym_,
      anon_sym_2,
      anon_sym_DASH_DASH_DASH_DASH_DASHBEGIN,
      sym__SP,
      sym__HTAB,
      sym__CR,
      sym__LF,
  [362] = 5,
    ACTIONS(93), 1,
      anon_sym_DASH_DASH_DASH_DASH_DASH,
    ACTIONS(95), 1,
      sym__labelchar,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(99), 1,
      sym__SP,
    STATE(27), 1,
      aux_sym_label_repeat1,
  [378] = 5,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(99), 1,
      sym__SP,
    ACTIONS(101), 1,
      anon_sym_DASH_DASH_DASH_DASH_DASH,
    ACTIONS(103), 1,
      sym__labelchar,
    STATE(28), 1,
      aux_sym_label_repeat1,
  [394] = 5,
    ACTIONS(105), 1,
      anon_sym_DASH_DASH_DASH_DASH_DASH,
    ACTIONS(107), 1,
      sym__labelchar,
    ACTIONS(110), 1,
      anon_sym_DASH,
    ACTIONS(113), 1,
      sym__SP,
    STATE(28), 1,
      aux_sym_label_repeat1,
  [410] = 2,
    ACTIONS(116), 1,
      anon_sym_DASH,
    ACTIONS(105), 3,
      anon_sym_DASH_DASH_DASH_DASH_DASH,
      sym__labelchar,
      sym__SP,
  [419] = 3,
    ACTIONS(118), 1,
      anon_sym_DASH_DASH_DASH_DASH_DASH,
    ACTIONS(120), 1,
      sym__labelchar,
    STATE(35), 1,
      sym_label,
  [429] = 3,
    ACTIONS(120), 1,
      sym__labelchar,
    ACTIONS(122), 1,
      anon_sym_DASH_DASH_DASH_DASH_DASH,
    STATE(38), 1,
      sym_label,
  [439] = 2,
    ACTIONS(11), 1,
      anon_sym_DASH_DASH_DASH_DASH_DASHEND,
    STATE(11), 1,
      sym_posteb,
  [446] = 2,
    ACTIONS(11), 1,
      anon_sym_DASH_DASH_DASH_DASH_DASHEND,
    STATE(18), 1,
      sym_posteb,
  [453] = 1,
    ACTIONS(124), 1,
      anon_sym_DASH_DASH_DASH_DASH_DASHEND,
  [457] = 1,
    ACTIONS(126), 1,
      anon_sym_DASH_DASH_DASH_DASH_DASH,
  [461] = 1,
    ACTIONS(128), 1,
      sym__labelchar,
  [465] = 1,
    ACTIONS(17), 1,
      anon_sym_DASH_DASH_DASH_DASH_DASHEND,
  [469] = 1,
    ACTIONS(130), 1,
      anon_sym_DASH_DASH_DASH_DASH_DASH,
  [473] = 1,
    ACTIONS(132), 1,
      ts_builtin_sym_end,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(6)] = 0,
  [SMALL_STATE(7)] = 27,
  [SMALL_STATE(8)] = 54,
  [SMALL_STATE(9)] = 74,
  [SMALL_STATE(10)] = 89,
  [SMALL_STATE(11)] = 104,
  [SMALL_STATE(12)] = 122,
  [SMALL_STATE(13)] = 142,
  [SMALL_STATE(14)] = 160,
  [SMALL_STATE(15)] = 178,
  [SMALL_STATE(16)] = 196,
  [SMALL_STATE(17)] = 216,
  [SMALL_STATE(18)] = 236,
  [SMALL_STATE(19)] = 254,
  [SMALL_STATE(20)] = 272,
  [SMALL_STATE(21)] = 289,
  [SMALL_STATE(22)] = 306,
  [SMALL_STATE(23)] = 323,
  [SMALL_STATE(24)] = 340,
  [SMALL_STATE(25)] = 351,
  [SMALL_STATE(26)] = 362,
  [SMALL_STATE(27)] = 378,
  [SMALL_STATE(28)] = 394,
  [SMALL_STATE(29)] = 410,
  [SMALL_STATE(30)] = 419,
  [SMALL_STATE(31)] = 429,
  [SMALL_STATE(32)] = 439,
  [SMALL_STATE(33)] = 446,
  [SMALL_STATE(34)] = 453,
  [SMALL_STATE(35)] = 457,
  [SMALL_STATE(36)] = 461,
  [SMALL_STATE(37)] = 465,
  [SMALL_STATE(38)] = 469,
  [SMALL_STATE(39)] = 473,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pem_file, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [17] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_laxbase64text, 1),
  [19] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_laxbase64text_repeat1, 2), SHIFT_REPEAT(5),
  [22] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_laxbase64text_repeat1, 2),
  [24] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pem_file, 1),
  [26] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_pem_file_repeat1, 2),
  [28] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pem_file_repeat1, 2), SHIFT_REPEAT(16),
  [31] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pem_file_repeat1, 2), SHIFT_REPEAT(31),
  [34] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_laxtextualmsg_repeat1, 2),
  [36] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_laxtextualmsg_repeat1, 2), SHIFT_REPEAT(8),
  [39] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_preeb, 3),
  [41] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_preeb, 2),
  [43] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_laxtextualmsg, 4),
  [45] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_laxtextualmsg, 4), SHIFT(15),
  [48] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [50] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__laxbase64text_padding, 1),
  [52] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [54] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_laxtextualmsg, 4), SHIFT(8),
  [57] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_laxtextualmsg, 2),
  [59] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_laxtextualmsg, 2), SHIFT(19),
  [62] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_laxtextualmsg, 5),
  [64] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_laxtextualmsg, 5), SHIFT(8),
  [67] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [69] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__laxbase64text_padding, 2),
  [71] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [73] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_laxtextualmsg, 3),
  [75] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_laxtextualmsg, 3), SHIFT(13),
  [78] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_laxtextualmsg, 3), SHIFT(8),
  [81] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [83] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__laxbase64text_padding, 3),
  [85] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [87] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__laxbase64text_padding, 4),
  [89] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_posteb, 3),
  [91] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_posteb, 2),
  [93] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_label, 1),
  [95] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [97] = {.entry = {.count = 1, .reusable = false}}, SHIFT(36),
  [99] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [101] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_label, 2),
  [103] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_label_repeat1, 2),
  [107] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_label_repeat1, 2), SHIFT_REPEAT(28),
  [110] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_label_repeat1, 2), SHIFT_REPEAT(36),
  [113] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_label_repeat1, 2), SHIFT_REPEAT(36),
  [116] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_label_repeat1, 2),
  [118] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [120] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [122] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [124] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_laxbase64text, 2),
  [126] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [128] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [130] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [132] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_pem(void) {
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
