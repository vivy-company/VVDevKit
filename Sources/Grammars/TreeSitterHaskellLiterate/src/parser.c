#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 44
#define LARGE_STATE_COUNT 4
#define SYMBOL_COUNT 29
#define ALIAS_COUNT 0
#define TOKEN_COUNT 12
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 4
#define PRODUCTION_ID_COUNT 1

enum ts_symbol_identifiers {
  anon_sym_GT = 1,
  anon_sym_LT = 2,
  anon_sym_SPACE = 3,
  anon_sym_BSLASHbegin_LBRACEcode_RBRACE = 4,
  anon_sym_PERCENT = 5,
  aux_sym_latex_comment_token1 = 6,
  anon_sym_BSLASHend_LBRACEcode_RBRACE = 7,
  anon_sym_BQUOTE_BQUOTE_BQUOTEhaskell = 8,
  anon_sym_BQUOTE_BQUOTE_BQUOTE = 9,
  aux_sym_prose_line_token1 = 10,
  sym__newline = 11,
  sym_source_file = 12,
  sym_bird_line = 13,
  sym_latex_code_block = 14,
  sym_latex_begin = 15,
  sym_latex_comment = 16,
  sym_latex_end = 17,
  sym_latex_code_line = 18,
  sym_markdown_code_block = 19,
  sym_markdown_begin = 20,
  sym_markdown_end = 21,
  sym_markdown_code_line = 22,
  sym_haskell_code = 23,
  sym_prose_line = 24,
  sym_blank_line = 25,
  aux_sym_source_file_repeat1 = 26,
  aux_sym_latex_code_block_repeat1 = 27,
  aux_sym_markdown_code_block_repeat1 = 28,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_GT] = ">",
  [anon_sym_LT] = "<",
  [anon_sym_SPACE] = " ",
  [anon_sym_BSLASHbegin_LBRACEcode_RBRACE] = "\\begin{code}",
  [anon_sym_PERCENT] = "%",
  [aux_sym_latex_comment_token1] = "latex_comment_token1",
  [anon_sym_BSLASHend_LBRACEcode_RBRACE] = "\\end{code}",
  [anon_sym_BQUOTE_BQUOTE_BQUOTEhaskell] = "```haskell",
  [anon_sym_BQUOTE_BQUOTE_BQUOTE] = "```",
  [aux_sym_prose_line_token1] = "prose_line_token1",
  [sym__newline] = "_newline",
  [sym_source_file] = "source_file",
  [sym_bird_line] = "bird_line",
  [sym_latex_code_block] = "latex_code_block",
  [sym_latex_begin] = "latex_begin",
  [sym_latex_comment] = "latex_comment",
  [sym_latex_end] = "latex_end",
  [sym_latex_code_line] = "latex_code_line",
  [sym_markdown_code_block] = "markdown_code_block",
  [sym_markdown_begin] = "markdown_begin",
  [sym_markdown_end] = "markdown_end",
  [sym_markdown_code_line] = "markdown_code_line",
  [sym_haskell_code] = "haskell_code",
  [sym_prose_line] = "prose_line",
  [sym_blank_line] = "blank_line",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_latex_code_block_repeat1] = "latex_code_block_repeat1",
  [aux_sym_markdown_code_block_repeat1] = "markdown_code_block_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_GT] = anon_sym_GT,
  [anon_sym_LT] = anon_sym_LT,
  [anon_sym_SPACE] = anon_sym_SPACE,
  [anon_sym_BSLASHbegin_LBRACEcode_RBRACE] = anon_sym_BSLASHbegin_LBRACEcode_RBRACE,
  [anon_sym_PERCENT] = anon_sym_PERCENT,
  [aux_sym_latex_comment_token1] = aux_sym_latex_comment_token1,
  [anon_sym_BSLASHend_LBRACEcode_RBRACE] = anon_sym_BSLASHend_LBRACEcode_RBRACE,
  [anon_sym_BQUOTE_BQUOTE_BQUOTEhaskell] = anon_sym_BQUOTE_BQUOTE_BQUOTEhaskell,
  [anon_sym_BQUOTE_BQUOTE_BQUOTE] = anon_sym_BQUOTE_BQUOTE_BQUOTE,
  [aux_sym_prose_line_token1] = aux_sym_prose_line_token1,
  [sym__newline] = sym__newline,
  [sym_source_file] = sym_source_file,
  [sym_bird_line] = sym_bird_line,
  [sym_latex_code_block] = sym_latex_code_block,
  [sym_latex_begin] = sym_latex_begin,
  [sym_latex_comment] = sym_latex_comment,
  [sym_latex_end] = sym_latex_end,
  [sym_latex_code_line] = sym_latex_code_line,
  [sym_markdown_code_block] = sym_markdown_code_block,
  [sym_markdown_begin] = sym_markdown_begin,
  [sym_markdown_end] = sym_markdown_end,
  [sym_markdown_code_line] = sym_markdown_code_line,
  [sym_haskell_code] = sym_haskell_code,
  [sym_prose_line] = sym_prose_line,
  [sym_blank_line] = sym_blank_line,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_latex_code_block_repeat1] = aux_sym_latex_code_block_repeat1,
  [aux_sym_markdown_code_block_repeat1] = aux_sym_markdown_code_block_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SPACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BSLASHbegin_LBRACEcode_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PERCENT] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_latex_comment_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_BSLASHend_LBRACEcode_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BQUOTE_BQUOTE_BQUOTEhaskell] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BQUOTE_BQUOTE_BQUOTE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_prose_line_token1] = {
    .visible = false,
    .named = false,
  },
  [sym__newline] = {
    .visible = false,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym_bird_line] = {
    .visible = true,
    .named = true,
  },
  [sym_latex_code_block] = {
    .visible = true,
    .named = true,
  },
  [sym_latex_begin] = {
    .visible = true,
    .named = true,
  },
  [sym_latex_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_latex_end] = {
    .visible = true,
    .named = true,
  },
  [sym_latex_code_line] = {
    .visible = true,
    .named = true,
  },
  [sym_markdown_code_block] = {
    .visible = true,
    .named = true,
  },
  [sym_markdown_begin] = {
    .visible = true,
    .named = true,
  },
  [sym_markdown_end] = {
    .visible = true,
    .named = true,
  },
  [sym_markdown_code_line] = {
    .visible = true,
    .named = true,
  },
  [sym_haskell_code] = {
    .visible = true,
    .named = true,
  },
  [sym_prose_line] = {
    .visible = true,
    .named = true,
  },
  [sym_blank_line] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_latex_code_block_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_markdown_code_block_repeat1] = {
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
  [29] = 13,
  [30] = 13,
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
      if (eof) ADVANCE(34);
      ADVANCE_MAP(
        '\n', 63,
        '\r', 1,
        ' ', 37,
        '%', 40,
        '<', 36,
        '>', 35,
        '\\', 8,
        '`', 4,
      );
      END_STATE();
    case 1:
      if (lookahead == '\n') ADVANCE(63);
      END_STATE();
    case 2:
      if (lookahead == '`') ADVANCE(60);
      END_STATE();
    case 3:
      if (lookahead == '`') ADVANCE(19);
      if (lookahead != 0) ADVANCE(62);
      END_STATE();
    case 4:
      if (lookahead == '`') ADVANCE(2);
      END_STATE();
    case 5:
      if (lookahead == '`') ADVANCE(3);
      if (lookahead != 0) ADVANCE(62);
      END_STATE();
    case 6:
      if (lookahead == 'a') ADVANCE(28);
      END_STATE();
    case 7:
      if (lookahead == 'b') ADVANCE(14);
      END_STATE();
    case 8:
      if (lookahead == 'b') ADVANCE(14);
      if (lookahead == 'e') ADVANCE(24);
      END_STATE();
    case 9:
      if (lookahead == 'c') ADVANCE(26);
      END_STATE();
    case 10:
      if (lookahead == 'c') ADVANCE(27);
      END_STATE();
    case 11:
      if (lookahead == 'd') ADVANCE(29);
      END_STATE();
    case 12:
      if (lookahead == 'd') ADVANCE(16);
      END_STATE();
    case 13:
      if (lookahead == 'd') ADVANCE(17);
      END_STATE();
    case 14:
      if (lookahead == 'e') ADVANCE(18);
      END_STATE();
    case 15:
      if (lookahead == 'e') ADVANCE(23);
      END_STATE();
    case 16:
      if (lookahead == 'e') ADVANCE(31);
      END_STATE();
    case 17:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 18:
      if (lookahead == 'g') ADVANCE(20);
      END_STATE();
    case 19:
      if (lookahead == 'h') ADVANCE(6);
      END_STATE();
    case 20:
      if (lookahead == 'i') ADVANCE(25);
      END_STATE();
    case 21:
      if (lookahead == 'k') ADVANCE(15);
      END_STATE();
    case 22:
      if (lookahead == 'l') ADVANCE(59);
      END_STATE();
    case 23:
      if (lookahead == 'l') ADVANCE(22);
      END_STATE();
    case 24:
      if (lookahead == 'n') ADVANCE(11);
      END_STATE();
    case 25:
      if (lookahead == 'n') ADVANCE(30);
      END_STATE();
    case 26:
      if (lookahead == 'o') ADVANCE(12);
      END_STATE();
    case 27:
      if (lookahead == 'o') ADVANCE(13);
      END_STATE();
    case 28:
      if (lookahead == 's') ADVANCE(21);
      END_STATE();
    case 29:
      if (lookahead == '{') ADVANCE(9);
      END_STATE();
    case 30:
      if (lookahead == '{') ADVANCE(10);
      END_STATE();
    case 31:
      if (lookahead == '}') ADVANCE(57);
      END_STATE();
    case 32:
      if (lookahead == '}') ADVANCE(39);
      END_STATE();
    case 33:
      if (eof) ADVANCE(34);
      if (lookahead == '\n') ADVANCE(63);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == '<') ADVANCE(36);
      if (lookahead == '>') ADVANCE(35);
      if (lookahead == '\\') ADVANCE(7);
      if (lookahead == '`') ADVANCE(5);
      if (lookahead != 0) ADVANCE(62);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(anon_sym_GT);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(anon_sym_LT);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(anon_sym_SPACE);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(anon_sym_SPACE);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(56);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(anon_sym_BSLASHbegin_LBRACEcode_RBRACE);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(anon_sym_PERCENT);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(aux_sym_latex_comment_token1);
      if (lookahead == '\n') ADVANCE(63);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == ' ') ADVANCE(38);
      if (lookahead != 0) ADVANCE(56);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(aux_sym_latex_comment_token1);
      if (lookahead == '\n') ADVANCE(63);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == '\\') ADVANCE(50);
      if (lookahead != 0) ADVANCE(56);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(aux_sym_latex_comment_token1);
      if (lookahead == '\n') ADVANCE(63);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == '`') ADVANCE(46);
      if (lookahead != 0) ADVANCE(56);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(aux_sym_latex_comment_token1);
      if (lookahead == '\n') ADVANCE(63);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead != 0) ADVANCE(56);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(aux_sym_latex_comment_token1);
      if (lookahead == '`') ADVANCE(61);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(56);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(aux_sym_latex_comment_token1);
      if (lookahead == '`') ADVANCE(45);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(56);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(aux_sym_latex_comment_token1);
      if (lookahead == 'c') ADVANCE(53);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(56);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(aux_sym_latex_comment_token1);
      if (lookahead == 'd') ADVANCE(54);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(56);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(aux_sym_latex_comment_token1);
      if (lookahead == 'd') ADVANCE(51);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(56);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(aux_sym_latex_comment_token1);
      if (lookahead == 'e') ADVANCE(52);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(56);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(aux_sym_latex_comment_token1);
      if (lookahead == 'e') ADVANCE(55);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(56);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(aux_sym_latex_comment_token1);
      if (lookahead == 'n') ADVANCE(48);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(56);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(aux_sym_latex_comment_token1);
      if (lookahead == 'o') ADVANCE(49);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(56);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(aux_sym_latex_comment_token1);
      if (lookahead == '{') ADVANCE(47);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(56);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(aux_sym_latex_comment_token1);
      if (lookahead == '}') ADVANCE(58);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(56);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(aux_sym_latex_comment_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(56);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(anon_sym_BSLASHend_LBRACEcode_RBRACE);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(anon_sym_BSLASHend_LBRACEcode_RBRACE);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(56);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(anon_sym_BQUOTE_BQUOTE_BQUOTEhaskell);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(anon_sym_BQUOTE_BQUOTE_BQUOTE);
      if (lookahead == 'h') ADVANCE(6);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(anon_sym_BQUOTE_BQUOTE_BQUOTE);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(56);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(aux_sym_prose_line_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(62);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(sym__newline);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 33},
  [2] = {.lex_state = 33},
  [3] = {.lex_state = 33},
  [4] = {.lex_state = 42},
  [5] = {.lex_state = 43},
  [6] = {.lex_state = 42},
  [7] = {.lex_state = 43},
  [8] = {.lex_state = 33},
  [9] = {.lex_state = 33},
  [10] = {.lex_state = 33},
  [11] = {.lex_state = 33},
  [12] = {.lex_state = 33},
  [13] = {.lex_state = 33},
  [14] = {.lex_state = 33},
  [15] = {.lex_state = 33},
  [16] = {.lex_state = 42},
  [17] = {.lex_state = 33},
  [18] = {.lex_state = 33},
  [19] = {.lex_state = 43},
  [20] = {.lex_state = 33},
  [21] = {.lex_state = 41},
  [22] = {.lex_state = 0},
  [23] = {.lex_state = 42},
  [24] = {.lex_state = 42},
  [25] = {.lex_state = 42},
  [26] = {.lex_state = 43},
  [27] = {.lex_state = 43},
  [28] = {.lex_state = 44},
  [29] = {.lex_state = 42},
  [30] = {.lex_state = 43},
  [31] = {.lex_state = 0},
  [32] = {.lex_state = 0},
  [33] = {.lex_state = 0},
  [34] = {.lex_state = 0},
  [35] = {.lex_state = 0},
  [36] = {.lex_state = 0},
  [37] = {.lex_state = 0},
  [38] = {.lex_state = 56},
  [39] = {.lex_state = 0},
  [40] = {.lex_state = 0},
  [41] = {.lex_state = 0},
  [42] = {.lex_state = 0},
  [43] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_GT] = ACTIONS(1),
    [anon_sym_LT] = ACTIONS(1),
    [anon_sym_SPACE] = ACTIONS(1),
    [anon_sym_BSLASHbegin_LBRACEcode_RBRACE] = ACTIONS(1),
    [anon_sym_PERCENT] = ACTIONS(1),
    [anon_sym_BSLASHend_LBRACEcode_RBRACE] = ACTIONS(1),
    [anon_sym_BQUOTE_BQUOTE_BQUOTEhaskell] = ACTIONS(1),
    [anon_sym_BQUOTE_BQUOTE_BQUOTE] = ACTIONS(1),
    [sym__newline] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(37),
    [sym_bird_line] = STATE(2),
    [sym_latex_code_block] = STATE(2),
    [sym_latex_begin] = STATE(4),
    [sym_markdown_code_block] = STATE(2),
    [sym_markdown_begin] = STATE(5),
    [sym_prose_line] = STATE(2),
    [sym_blank_line] = STATE(2),
    [aux_sym_source_file_repeat1] = STATE(2),
    [ts_builtin_sym_end] = ACTIONS(3),
    [anon_sym_GT] = ACTIONS(5),
    [anon_sym_LT] = ACTIONS(5),
    [anon_sym_BSLASHbegin_LBRACEcode_RBRACE] = ACTIONS(7),
    [anon_sym_BQUOTE_BQUOTE_BQUOTEhaskell] = ACTIONS(9),
    [aux_sym_prose_line_token1] = ACTIONS(11),
    [sym__newline] = ACTIONS(13),
  },
  [2] = {
    [sym_bird_line] = STATE(3),
    [sym_latex_code_block] = STATE(3),
    [sym_latex_begin] = STATE(4),
    [sym_markdown_code_block] = STATE(3),
    [sym_markdown_begin] = STATE(5),
    [sym_prose_line] = STATE(3),
    [sym_blank_line] = STATE(3),
    [aux_sym_source_file_repeat1] = STATE(3),
    [ts_builtin_sym_end] = ACTIONS(15),
    [anon_sym_GT] = ACTIONS(5),
    [anon_sym_LT] = ACTIONS(5),
    [anon_sym_BSLASHbegin_LBRACEcode_RBRACE] = ACTIONS(7),
    [anon_sym_BQUOTE_BQUOTE_BQUOTEhaskell] = ACTIONS(9),
    [aux_sym_prose_line_token1] = ACTIONS(11),
    [sym__newline] = ACTIONS(13),
  },
  [3] = {
    [sym_bird_line] = STATE(3),
    [sym_latex_code_block] = STATE(3),
    [sym_latex_begin] = STATE(4),
    [sym_markdown_code_block] = STATE(3),
    [sym_markdown_begin] = STATE(5),
    [sym_prose_line] = STATE(3),
    [sym_blank_line] = STATE(3),
    [aux_sym_source_file_repeat1] = STATE(3),
    [ts_builtin_sym_end] = ACTIONS(17),
    [anon_sym_GT] = ACTIONS(19),
    [anon_sym_LT] = ACTIONS(19),
    [anon_sym_BSLASHbegin_LBRACEcode_RBRACE] = ACTIONS(22),
    [anon_sym_BQUOTE_BQUOTE_BQUOTEhaskell] = ACTIONS(25),
    [aux_sym_prose_line_token1] = ACTIONS(28),
    [sym__newline] = ACTIONS(31),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 6,
    ACTIONS(34), 1,
      aux_sym_latex_comment_token1,
    ACTIONS(36), 1,
      anon_sym_BSLASHend_LBRACEcode_RBRACE,
    ACTIONS(38), 1,
      sym__newline,
    STATE(12), 1,
      sym_latex_end,
    STATE(31), 1,
      sym_haskell_code,
    STATE(6), 3,
      sym_latex_code_line,
      sym_blank_line,
      aux_sym_latex_code_block_repeat1,
  [21] = 6,
    ACTIONS(34), 1,
      aux_sym_latex_comment_token1,
    ACTIONS(40), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    ACTIONS(42), 1,
      sym__newline,
    STATE(20), 1,
      sym_markdown_end,
    STATE(35), 1,
      sym_haskell_code,
    STATE(7), 3,
      sym_markdown_code_line,
      sym_blank_line,
      aux_sym_markdown_code_block_repeat1,
  [42] = 6,
    ACTIONS(34), 1,
      aux_sym_latex_comment_token1,
    ACTIONS(36), 1,
      anon_sym_BSLASHend_LBRACEcode_RBRACE,
    ACTIONS(38), 1,
      sym__newline,
    STATE(8), 1,
      sym_latex_end,
    STATE(31), 1,
      sym_haskell_code,
    STATE(16), 3,
      sym_latex_code_line,
      sym_blank_line,
      aux_sym_latex_code_block_repeat1,
  [63] = 6,
    ACTIONS(34), 1,
      aux_sym_latex_comment_token1,
    ACTIONS(40), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    ACTIONS(42), 1,
      sym__newline,
    STATE(18), 1,
      sym_markdown_end,
    STATE(35), 1,
      sym_haskell_code,
    STATE(19), 3,
      sym_markdown_code_line,
      sym_blank_line,
      aux_sym_markdown_code_block_repeat1,
  [84] = 1,
    ACTIONS(44), 7,
      ts_builtin_sym_end,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_BSLASHbegin_LBRACEcode_RBRACE,
      anon_sym_BQUOTE_BQUOTE_BQUOTEhaskell,
      aux_sym_prose_line_token1,
      sym__newline,
  [94] = 1,
    ACTIONS(46), 7,
      ts_builtin_sym_end,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_BSLASHbegin_LBRACEcode_RBRACE,
      anon_sym_BQUOTE_BQUOTE_BQUOTEhaskell,
      aux_sym_prose_line_token1,
      sym__newline,
  [104] = 1,
    ACTIONS(48), 7,
      ts_builtin_sym_end,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_BSLASHbegin_LBRACEcode_RBRACE,
      anon_sym_BQUOTE_BQUOTE_BQUOTEhaskell,
      aux_sym_prose_line_token1,
      sym__newline,
  [114] = 1,
    ACTIONS(50), 7,
      ts_builtin_sym_end,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_BSLASHbegin_LBRACEcode_RBRACE,
      anon_sym_BQUOTE_BQUOTE_BQUOTEhaskell,
      aux_sym_prose_line_token1,
      sym__newline,
  [124] = 1,
    ACTIONS(52), 7,
      ts_builtin_sym_end,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_BSLASHbegin_LBRACEcode_RBRACE,
      anon_sym_BQUOTE_BQUOTE_BQUOTEhaskell,
      aux_sym_prose_line_token1,
      sym__newline,
  [134] = 1,
    ACTIONS(54), 7,
      ts_builtin_sym_end,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_BSLASHbegin_LBRACEcode_RBRACE,
      anon_sym_BQUOTE_BQUOTE_BQUOTEhaskell,
      aux_sym_prose_line_token1,
      sym__newline,
  [144] = 1,
    ACTIONS(56), 7,
      ts_builtin_sym_end,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_BSLASHbegin_LBRACEcode_RBRACE,
      anon_sym_BQUOTE_BQUOTE_BQUOTEhaskell,
      aux_sym_prose_line_token1,
      sym__newline,
  [154] = 1,
    ACTIONS(58), 7,
      ts_builtin_sym_end,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_BSLASHbegin_LBRACEcode_RBRACE,
      anon_sym_BQUOTE_BQUOTE_BQUOTEhaskell,
      aux_sym_prose_line_token1,
      sym__newline,
  [164] = 5,
    ACTIONS(60), 1,
      aux_sym_latex_comment_token1,
    ACTIONS(63), 1,
      anon_sym_BSLASHend_LBRACEcode_RBRACE,
    ACTIONS(65), 1,
      sym__newline,
    STATE(31), 1,
      sym_haskell_code,
    STATE(16), 3,
      sym_latex_code_line,
      sym_blank_line,
      aux_sym_latex_code_block_repeat1,
  [182] = 1,
    ACTIONS(68), 7,
      ts_builtin_sym_end,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_BSLASHbegin_LBRACEcode_RBRACE,
      anon_sym_BQUOTE_BQUOTE_BQUOTEhaskell,
      aux_sym_prose_line_token1,
      sym__newline,
  [192] = 1,
    ACTIONS(70), 7,
      ts_builtin_sym_end,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_BSLASHbegin_LBRACEcode_RBRACE,
      anon_sym_BQUOTE_BQUOTE_BQUOTEhaskell,
      aux_sym_prose_line_token1,
      sym__newline,
  [202] = 5,
    ACTIONS(72), 1,
      aux_sym_latex_comment_token1,
    ACTIONS(75), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    ACTIONS(77), 1,
      sym__newline,
    STATE(35), 1,
      sym_haskell_code,
    STATE(19), 3,
      sym_markdown_code_line,
      sym_blank_line,
      aux_sym_markdown_code_block_repeat1,
  [220] = 1,
    ACTIONS(80), 7,
      ts_builtin_sym_end,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_BSLASHbegin_LBRACEcode_RBRACE,
      anon_sym_BQUOTE_BQUOTE_BQUOTEhaskell,
      aux_sym_prose_line_token1,
      sym__newline,
  [230] = 4,
    ACTIONS(34), 1,
      aux_sym_latex_comment_token1,
    ACTIONS(82), 1,
      anon_sym_SPACE,
    ACTIONS(84), 1,
      sym__newline,
    STATE(36), 1,
      sym_haskell_code,
  [243] = 3,
    ACTIONS(86), 1,
      anon_sym_PERCENT,
    ACTIONS(88), 1,
      sym__newline,
    STATE(41), 1,
      sym_latex_comment,
  [253] = 2,
    ACTIONS(92), 1,
      sym__newline,
    ACTIONS(90), 2,
      aux_sym_latex_comment_token1,
      anon_sym_BSLASHend_LBRACEcode_RBRACE,
  [261] = 2,
    ACTIONS(96), 1,
      sym__newline,
    ACTIONS(94), 2,
      aux_sym_latex_comment_token1,
      anon_sym_BSLASHend_LBRACEcode_RBRACE,
  [269] = 2,
    ACTIONS(100), 1,
      sym__newline,
    ACTIONS(98), 2,
      aux_sym_latex_comment_token1,
      anon_sym_BSLASHend_LBRACEcode_RBRACE,
  [277] = 2,
    ACTIONS(104), 1,
      sym__newline,
    ACTIONS(102), 2,
      aux_sym_latex_comment_token1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
  [285] = 2,
    ACTIONS(108), 1,
      sym__newline,
    ACTIONS(106), 2,
      aux_sym_latex_comment_token1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
  [293] = 3,
    ACTIONS(34), 1,
      aux_sym_latex_comment_token1,
    ACTIONS(110), 1,
      sym__newline,
    STATE(39), 1,
      sym_haskell_code,
  [303] = 2,
    ACTIONS(54), 1,
      sym__newline,
    ACTIONS(112), 2,
      aux_sym_latex_comment_token1,
      anon_sym_BSLASHend_LBRACEcode_RBRACE,
  [311] = 2,
    ACTIONS(54), 1,
      sym__newline,
    ACTIONS(112), 2,
      aux_sym_latex_comment_token1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
  [319] = 1,
    ACTIONS(114), 1,
      sym__newline,
  [323] = 1,
    ACTIONS(116), 1,
      sym__newline,
  [327] = 1,
    ACTIONS(118), 1,
      sym__newline,
  [331] = 1,
    ACTIONS(120), 1,
      sym__newline,
  [335] = 1,
    ACTIONS(122), 1,
      sym__newline,
  [339] = 1,
    ACTIONS(110), 1,
      sym__newline,
  [343] = 1,
    ACTIONS(124), 1,
      ts_builtin_sym_end,
  [347] = 1,
    ACTIONS(126), 1,
      aux_sym_latex_comment_token1,
  [351] = 1,
    ACTIONS(128), 1,
      sym__newline,
  [355] = 1,
    ACTIONS(130), 1,
      sym__newline,
  [359] = 1,
    ACTIONS(132), 1,
      sym__newline,
  [363] = 1,
    ACTIONS(134), 1,
      sym__newline,
  [367] = 1,
    ACTIONS(136), 1,
      sym__newline,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(4)] = 0,
  [SMALL_STATE(5)] = 21,
  [SMALL_STATE(6)] = 42,
  [SMALL_STATE(7)] = 63,
  [SMALL_STATE(8)] = 84,
  [SMALL_STATE(9)] = 94,
  [SMALL_STATE(10)] = 104,
  [SMALL_STATE(11)] = 114,
  [SMALL_STATE(12)] = 124,
  [SMALL_STATE(13)] = 134,
  [SMALL_STATE(14)] = 144,
  [SMALL_STATE(15)] = 154,
  [SMALL_STATE(16)] = 164,
  [SMALL_STATE(17)] = 182,
  [SMALL_STATE(18)] = 192,
  [SMALL_STATE(19)] = 202,
  [SMALL_STATE(20)] = 220,
  [SMALL_STATE(21)] = 230,
  [SMALL_STATE(22)] = 243,
  [SMALL_STATE(23)] = 253,
  [SMALL_STATE(24)] = 261,
  [SMALL_STATE(25)] = 269,
  [SMALL_STATE(26)] = 277,
  [SMALL_STATE(27)] = 285,
  [SMALL_STATE(28)] = 293,
  [SMALL_STATE(29)] = 303,
  [SMALL_STATE(30)] = 311,
  [SMALL_STATE(31)] = 319,
  [SMALL_STATE(32)] = 323,
  [SMALL_STATE(33)] = 327,
  [SMALL_STATE(34)] = 331,
  [SMALL_STATE(35)] = 335,
  [SMALL_STATE(36)] = 339,
  [SMALL_STATE(37)] = 343,
  [SMALL_STATE(38)] = 347,
  [SMALL_STATE(39)] = 351,
  [SMALL_STATE(40)] = 355,
  [SMALL_STATE(41)] = 359,
  [SMALL_STATE(42)] = 363,
  [SMALL_STATE(43)] = 367,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0, 0, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [15] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [17] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [19] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(21),
  [22] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(22),
  [25] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(32),
  [28] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(34),
  [31] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(13),
  [34] = {.entry = {.count = 1, .reusable = false}}, SHIFT(42),
  [36] = {.entry = {.count = 1, .reusable = false}}, SHIFT(43),
  [38] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [40] = {.entry = {.count = 1, .reusable = false}}, SHIFT(33),
  [42] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [44] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_latex_code_block, 3, 0, 0),
  [46] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bird_line, 4, 0, 0),
  [48] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bird_line, 2, 0, 0),
  [50] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_prose_line, 2, 0, 0),
  [52] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_latex_code_block, 2, 0, 0),
  [54] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_blank_line, 1, 0, 0),
  [56] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bird_line, 3, 0, 0),
  [58] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_latex_end, 2, 0, 0),
  [60] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_latex_code_block_repeat1, 2, 0, 0), SHIFT_REPEAT(42),
  [63] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_latex_code_block_repeat1, 2, 0, 0),
  [65] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_latex_code_block_repeat1, 2, 0, 0), SHIFT_REPEAT(29),
  [68] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_markdown_end, 2, 0, 0),
  [70] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_markdown_code_block, 3, 0, 0),
  [72] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_markdown_code_block_repeat1, 2, 0, 0), SHIFT_REPEAT(42),
  [75] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_markdown_code_block_repeat1, 2, 0, 0),
  [77] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_markdown_code_block_repeat1, 2, 0, 0), SHIFT_REPEAT(30),
  [80] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_markdown_code_block, 2, 0, 0),
  [82] = {.entry = {.count = 1, .reusable = false}}, SHIFT(28),
  [84] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [86] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [88] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [90] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_latex_begin, 2, 0, 0),
  [92] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_latex_begin, 2, 0, 0),
  [94] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_latex_code_line, 2, 0, 0),
  [96] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_latex_code_line, 2, 0, 0),
  [98] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_latex_begin, 3, 0, 0),
  [100] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_latex_begin, 3, 0, 0),
  [102] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_markdown_begin, 2, 0, 0),
  [104] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_markdown_begin, 2, 0, 0),
  [106] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_markdown_code_line, 2, 0, 0),
  [108] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_markdown_code_line, 2, 0, 0),
  [110] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [112] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_blank_line, 1, 0, 0),
  [114] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [116] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [118] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [120] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [122] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [124] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [126] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [128] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [130] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_latex_comment, 2, 0, 0),
  [132] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [134] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_haskell_code, 1, 0, 0),
  [136] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef TREE_SITTER_HIDE_SYMBOLS
#define TS_PUBLIC
#elif defined(_WIN32)
#define TS_PUBLIC __declspec(dllexport)
#else
#define TS_PUBLIC __attribute__((visibility("default")))
#endif

TS_PUBLIC const TSLanguage *tree_sitter_haskell_literate(void) {
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
