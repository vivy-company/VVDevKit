#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 112
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 60
#define ALIAS_COUNT 1
#define TOKEN_COUNT 31
#define EXTERNAL_TOKEN_COUNT 2
#define FIELD_COUNT 11
#define MAX_ALIAS_SEQUENCE_LENGTH 5
#define PRODUCTION_ID_COUNT 24

enum {
  sym_identifier = 1,
  anon_sym_LT_COLON = 2,
  anon_sym_LBRACE = 3,
  anon_sym_RBRACE = 4,
  anon_sym_EQ = 5,
  anon_sym_COLON_EQ = 6,
  anon_sym_PLUS_EQ = 7,
  anon_sym_LT = 8,
  anon_sym_COMMA = 9,
  anon_sym_GT = 10,
  anon_sym_LPAREN = 11,
  aux_sym_rule_descr_token1 = 12,
  anon_sym_RPAREN = 13,
  anon_sym_PIPE = 14,
  anon_sym_DOT_DOT_DOT = 15,
  anon_sym_DASH_DASH = 16,
  aux_sym_case_name_token1 = 17,
  anon_sym_AMP = 18,
  anon_sym_TILDE = 19,
  anon_sym_POUND = 20,
  anon_sym_STAR = 21,
  anon_sym_PLUS = 22,
  anon_sym_QMARK = 23,
  anon_sym_DOT_DOT = 24,
  anon_sym_DQUOTE = 25,
  anon_sym_DQUOTE2 = 26,
  sym_escape_char = 27,
  sym_singleline_comment = 28,
  sym__unicode_char = 29,
  sym_multiline_comment = 30,
  sym_source_file = 31,
  sym_grammar = 32,
  sym_super_grammar = 33,
  sym_grammar_body = 34,
  sym_rule = 35,
  sym_formals = 36,
  sym_rule_descr = 37,
  sym_rule_body = 38,
  sym_top_level_term = 39,
  sym_override_rule_body = 40,
  sym_override_top_level_term = 41,
  sym_case_name = 42,
  sym_seq = 43,
  sym_term = 44,
  sym__base = 45,
  sym_params = 46,
  sym_alt = 47,
  sym_terminal_string = 48,
  sym_one_char_terminal = 49,
  sym__terminal_char = 50,
  aux_sym_source_file_repeat1 = 51,
  aux_sym_grammar_body_repeat1 = 52,
  aux_sym_formals_repeat1 = 53,
  aux_sym_rule_body_repeat1 = 54,
  aux_sym_override_rule_body_repeat1 = 55,
  aux_sym_seq_repeat1 = 56,
  aux_sym_params_repeat1 = 57,
  aux_sym_alt_repeat1 = 58,
  aux_sym_terminal_string_repeat1 = 59,
  alias_sym_param = 60,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_identifier] = "identifier",
  [anon_sym_LT_COLON] = "<:",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_EQ] = "define",
  [anon_sym_COLON_EQ] = "override",
  [anon_sym_PLUS_EQ] = "extend",
  [anon_sym_LT] = "<",
  [anon_sym_COMMA] = ",",
  [anon_sym_GT] = ">",
  [anon_sym_LPAREN] = "(",
  [aux_sym_rule_descr_token1] = "rule_descr_token1",
  [anon_sym_RPAREN] = ")",
  [anon_sym_PIPE] = "|",
  [anon_sym_DOT_DOT_DOT] = "super_splice",
  [anon_sym_DASH_DASH] = "--",
  [aux_sym_case_name_token1] = "case_name_token1",
  [anon_sym_AMP] = "lookahead",
  [anon_sym_TILDE] = "negative_lookahead",
  [anon_sym_POUND] = "lexification",
  [anon_sym_STAR] = "zero_or_more",
  [anon_sym_PLUS] = "one_or_more",
  [anon_sym_QMARK] = "zero_or_one",
  [anon_sym_DOT_DOT] = "..",
  [anon_sym_DQUOTE] = "\"",
  [anon_sym_DQUOTE2] = "\"",
  [sym_escape_char] = "escape_char",
  [sym_singleline_comment] = "singleline_comment",
  [sym__unicode_char] = "_unicode_char",
  [sym_multiline_comment] = "multiline_comment",
  [sym_source_file] = "source_file",
  [sym_grammar] = "grammar",
  [sym_super_grammar] = "super_grammar",
  [sym_grammar_body] = "grammar_body",
  [sym_rule] = "rule",
  [sym_formals] = "formals",
  [sym_rule_descr] = "rule_descr",
  [sym_rule_body] = "rule_body",
  [sym_top_level_term] = "top_level_term",
  [sym_override_rule_body] = "override_rule_body",
  [sym_override_top_level_term] = "override_top_level_term",
  [sym_case_name] = "case_name",
  [sym_seq] = "seq",
  [sym_term] = "term",
  [sym__base] = "_base",
  [sym_params] = "params",
  [sym_alt] = "alt",
  [sym_terminal_string] = "terminal_string",
  [sym_one_char_terminal] = "one_char_terminal",
  [sym__terminal_char] = "_terminal_char",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_grammar_body_repeat1] = "grammar_body_repeat1",
  [aux_sym_formals_repeat1] = "formals_repeat1",
  [aux_sym_rule_body_repeat1] = "rule_body_repeat1",
  [aux_sym_override_rule_body_repeat1] = "override_rule_body_repeat1",
  [aux_sym_seq_repeat1] = "seq_repeat1",
  [aux_sym_params_repeat1] = "params_repeat1",
  [aux_sym_alt_repeat1] = "alt_repeat1",
  [aux_sym_terminal_string_repeat1] = "terminal_string_repeat1",
  [alias_sym_param] = "param",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_identifier] = sym_identifier,
  [anon_sym_LT_COLON] = anon_sym_LT_COLON,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_EQ] = anon_sym_EQ,
  [anon_sym_COLON_EQ] = anon_sym_COLON_EQ,
  [anon_sym_PLUS_EQ] = anon_sym_PLUS_EQ,
  [anon_sym_LT] = anon_sym_LT,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_GT] = anon_sym_GT,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [aux_sym_rule_descr_token1] = aux_sym_rule_descr_token1,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_PIPE] = anon_sym_PIPE,
  [anon_sym_DOT_DOT_DOT] = anon_sym_DOT_DOT_DOT,
  [anon_sym_DASH_DASH] = anon_sym_DASH_DASH,
  [aux_sym_case_name_token1] = aux_sym_case_name_token1,
  [anon_sym_AMP] = anon_sym_AMP,
  [anon_sym_TILDE] = anon_sym_TILDE,
  [anon_sym_POUND] = anon_sym_POUND,
  [anon_sym_STAR] = anon_sym_STAR,
  [anon_sym_PLUS] = anon_sym_PLUS,
  [anon_sym_QMARK] = anon_sym_QMARK,
  [anon_sym_DOT_DOT] = anon_sym_DOT_DOT,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [anon_sym_DQUOTE2] = anon_sym_DQUOTE,
  [sym_escape_char] = sym_escape_char,
  [sym_singleline_comment] = sym_singleline_comment,
  [sym__unicode_char] = sym__unicode_char,
  [sym_multiline_comment] = sym_multiline_comment,
  [sym_source_file] = sym_source_file,
  [sym_grammar] = sym_grammar,
  [sym_super_grammar] = sym_super_grammar,
  [sym_grammar_body] = sym_grammar_body,
  [sym_rule] = sym_rule,
  [sym_formals] = sym_formals,
  [sym_rule_descr] = sym_rule_descr,
  [sym_rule_body] = sym_rule_body,
  [sym_top_level_term] = sym_top_level_term,
  [sym_override_rule_body] = sym_override_rule_body,
  [sym_override_top_level_term] = sym_override_top_level_term,
  [sym_case_name] = sym_case_name,
  [sym_seq] = sym_seq,
  [sym_term] = sym_term,
  [sym__base] = sym__base,
  [sym_params] = sym_params,
  [sym_alt] = sym_alt,
  [sym_terminal_string] = sym_terminal_string,
  [sym_one_char_terminal] = sym_one_char_terminal,
  [sym__terminal_char] = sym__terminal_char,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_grammar_body_repeat1] = aux_sym_grammar_body_repeat1,
  [aux_sym_formals_repeat1] = aux_sym_formals_repeat1,
  [aux_sym_rule_body_repeat1] = aux_sym_rule_body_repeat1,
  [aux_sym_override_rule_body_repeat1] = aux_sym_override_rule_body_repeat1,
  [aux_sym_seq_repeat1] = aux_sym_seq_repeat1,
  [aux_sym_params_repeat1] = aux_sym_params_repeat1,
  [aux_sym_alt_repeat1] = aux_sym_alt_repeat1,
  [aux_sym_terminal_string_repeat1] = aux_sym_terminal_string_repeat1,
  [alias_sym_param] = alias_sym_param,
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
  [anon_sym_LT_COLON] = {
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
  [anon_sym_EQ] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_COLON_EQ] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_PLUS_EQ] = {
    .visible = true,
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
  [anon_sym_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_rule_descr_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PIPE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOT_DOT_DOT] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_DASH_DASH] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_case_name_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_AMP] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_TILDE] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_POUND] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_STAR] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_PLUS] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_QMARK] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_DOT_DOT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DQUOTE2] = {
    .visible = true,
    .named = false,
  },
  [sym_escape_char] = {
    .visible = true,
    .named = true,
  },
  [sym_singleline_comment] = {
    .visible = true,
    .named = true,
  },
  [sym__unicode_char] = {
    .visible = false,
    .named = true,
  },
  [sym_multiline_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym_grammar] = {
    .visible = true,
    .named = true,
  },
  [sym_super_grammar] = {
    .visible = true,
    .named = true,
  },
  [sym_grammar_body] = {
    .visible = true,
    .named = true,
  },
  [sym_rule] = {
    .visible = true,
    .named = true,
  },
  [sym_formals] = {
    .visible = true,
    .named = true,
  },
  [sym_rule_descr] = {
    .visible = true,
    .named = true,
  },
  [sym_rule_body] = {
    .visible = true,
    .named = true,
  },
  [sym_top_level_term] = {
    .visible = true,
    .named = true,
  },
  [sym_override_rule_body] = {
    .visible = true,
    .named = true,
  },
  [sym_override_top_level_term] = {
    .visible = true,
    .named = true,
  },
  [sym_case_name] = {
    .visible = true,
    .named = true,
  },
  [sym_seq] = {
    .visible = true,
    .named = true,
  },
  [sym_term] = {
    .visible = true,
    .named = true,
  },
  [sym__base] = {
    .visible = false,
    .named = true,
  },
  [sym_params] = {
    .visible = true,
    .named = true,
  },
  [sym_alt] = {
    .visible = true,
    .named = true,
  },
  [sym_terminal_string] = {
    .visible = true,
    .named = true,
  },
  [sym_one_char_terminal] = {
    .visible = true,
    .named = true,
  },
  [sym__terminal_char] = {
    .visible = false,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_grammar_body_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_formals_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_rule_body_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_override_rule_body_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_seq_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_params_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_alt_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_terminal_string_repeat1] = {
    .visible = false,
    .named = false,
  },
  [alias_sym_param] = {
    .visible = true,
    .named = true,
  },
};

enum {
  field_base = 1,
  field_body = 2,
  field_case = 3,
  field_description = 4,
  field_formals = 5,
  field_inherits = 6,
  field_lexification = 7,
  field_name = 8,
  field_predicate = 9,
  field_quantification = 10,
  field_sequence = 11,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_base] = "base",
  [field_body] = "body",
  [field_case] = "case",
  [field_description] = "description",
  [field_formals] = "formals",
  [field_inherits] = "inherits",
  [field_lexification] = "lexification",
  [field_name] = "name",
  [field_predicate] = "predicate",
  [field_quantification] = "quantification",
  [field_sequence] = "sequence",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 2},
  [2] = {.index = 2, .length = 1},
  [3] = {.index = 3, .length = 3},
  [4] = {.index = 6, .length = 2},
  [5] = {.index = 8, .length = 3},
  [6] = {.index = 11, .length = 1},
  [7] = {.index = 12, .length = 1},
  [8] = {.index = 13, .length = 1},
  [9] = {.index = 14, .length = 3},
  [10] = {.index = 17, .length = 3},
  [11] = {.index = 20, .length = 2},
  [12] = {.index = 22, .length = 2},
  [13] = {.index = 24, .length = 2},
  [14] = {.index = 26, .length = 2},
  [15] = {.index = 28, .length = 4},
  [16] = {.index = 32, .length = 4},
  [17] = {.index = 36, .length = 4},
  [18] = {.index = 40, .length = 3},
  [19] = {.index = 43, .length = 3},
  [20] = {.index = 46, .length = 3},
  [21] = {.index = 49, .length = 5},
  [22] = {.index = 54, .length = 4},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_body, 1},
    {field_name, 0},
  [2] =
    {field_name, 1},
  [3] =
    {field_body, 2},
    {field_inherits, 1},
    {field_name, 0},
  [6] =
    {field_case, 1},
    {field_name, 0},
  [8] =
    {field_body, 2},
    {field_case, 1},
    {field_name, 0},
  [11] =
    {field_name, 0},
  [12] =
    {field_sequence, 0},
  [13] =
    {field_base, 0},
  [14] =
    {field_case, 2},
    {field_formals, 1},
    {field_name, 0},
  [17] =
    {field_case, 2},
    {field_description, 1},
    {field_name, 0},
  [20] =
    {field_base, 1},
    {field_predicate, 0},
  [22] =
    {field_base, 1},
    {field_lexification, 0},
  [24] =
    {field_name, 1},
    {field_sequence, 0},
  [26] =
    {field_base, 0},
    {field_quantification, 1},
  [28] =
    {field_body, 3},
    {field_case, 2},
    {field_formals, 1},
    {field_name, 0},
  [32] =
    {field_case, 3},
    {field_description, 2},
    {field_formals, 1},
    {field_name, 0},
  [36] =
    {field_body, 3},
    {field_case, 2},
    {field_description, 1},
    {field_name, 0},
  [40] =
    {field_base, 2},
    {field_lexification, 1},
    {field_predicate, 0},
  [43] =
    {field_base, 1},
    {field_predicate, 0},
    {field_quantification, 2},
  [46] =
    {field_base, 1},
    {field_lexification, 0},
    {field_quantification, 2},
  [49] =
    {field_body, 4},
    {field_case, 3},
    {field_description, 2},
    {field_formals, 1},
    {field_name, 0},
  [54] =
    {field_base, 2},
    {field_lexification, 1},
    {field_predicate, 0},
    {field_quantification, 3},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
  [23] = {
    [1] = alias_sym_param,
  },
};

static const uint16_t ts_non_terminal_alias_map[] = {
  sym_seq, 2,
    sym_seq,
    alias_sym_param,
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
  [23] = 12,
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
  [74] = 74,
  [75] = 75,
  [76] = 76,
  [77] = 77,
  [78] = 78,
  [79] = 79,
  [80] = 80,
  [81] = 81,
  [82] = 82,
  [83] = 83,
  [84] = 84,
  [85] = 85,
  [86] = 86,
  [87] = 87,
  [88] = 88,
  [89] = 89,
  [90] = 90,
  [91] = 91,
  [92] = 92,
  [93] = 93,
  [94] = 94,
  [95] = 95,
  [96] = 96,
  [97] = 97,
  [98] = 98,
  [99] = 99,
  [100] = 100,
  [101] = 101,
  [102] = 102,
  [103] = 103,
  [104] = 104,
  [105] = 105,
  [106] = 106,
  [107] = 107,
  [108] = 108,
  [109] = 109,
  [110] = 110,
  [111] = 111,
};

static inline bool sym_identifier_character_set_1(int32_t c) {
  return (c < 43514
    ? (c < 4193
      ? (c < 2707
        ? (c < 1994
          ? (c < 910
            ? (c < 736
              ? (c < 186
                ? (c < 'a'
                  ? (c < '_'
                    ? (c >= 'A' && c <= 'Z')
                    : c <= '_')
                  : (c <= 'z' || (c < 181
                    ? c == 170
                    : c <= 181)))
                : (c <= 186 || (c < 248
                  ? (c < 216
                    ? (c >= 192 && c <= 214)
                    : c <= 246)
                  : (c <= 705 || (c >= 710 && c <= 721)))))
              : (c <= 740 || (c < 891
                ? (c < 880
                  ? (c < 750
                    ? c == 748
                    : c <= 750)
                  : (c <= 884 || (c >= 886 && c <= 887)))
                : (c <= 893 || (c < 904
                  ? (c < 902
                    ? c == 895
                    : c <= 902)
                  : (c <= 906 || c == 908))))))
            : (c <= 929 || (c < 1649
              ? (c < 1376
                ? (c < 1162
                  ? (c < 1015
                    ? (c >= 931 && c <= 1013)
                    : c <= 1153)
                  : (c <= 1327 || (c < 1369
                    ? (c >= 1329 && c <= 1366)
                    : c <= 1369)))
                : (c <= 1416 || (c < 1568
                  ? (c < 1519
                    ? (c >= 1488 && c <= 1514)
                    : c <= 1522)
                  : (c <= 1610 || (c >= 1646 && c <= 1647)))))
              : (c <= 1747 || (c < 1791
                ? (c < 1774
                  ? (c < 1765
                    ? c == 1749
                    : c <= 1766)
                  : (c <= 1775 || (c >= 1786 && c <= 1788)))
                : (c <= 1791 || (c < 1869
                  ? (c < 1810
                    ? c == 1808
                    : c <= 1839)
                  : (c <= 1957 || c == 1969))))))))
          : (c <= 2026 || (c < 2482
            ? (c < 2208
              ? (c < 2088
                ? (c < 2048
                  ? (c < 2042
                    ? (c >= 2036 && c <= 2037)
                    : c <= 2042)
                  : (c <= 2069 || (c < 2084
                    ? c == 2074
                    : c <= 2084)))
                : (c <= 2088 || (c < 2160
                  ? (c < 2144
                    ? (c >= 2112 && c <= 2136)
                    : c <= 2154)
                  : (c <= 2183 || (c >= 2185 && c <= 2190)))))
              : (c <= 2249 || (c < 2417
                ? (c < 2384
                  ? (c < 2365
                    ? (c >= 2308 && c <= 2361)
                    : c <= 2365)
                  : (c <= 2384 || (c >= 2392 && c <= 2401)))
                : (c <= 2432 || (c < 2451
                  ? (c < 2447
                    ? (c >= 2437 && c <= 2444)
                    : c <= 2448)
                  : (c <= 2472 || (c >= 2474 && c <= 2480)))))))
            : (c <= 2482 || (c < 2579
              ? (c < 2527
                ? (c < 2510
                  ? (c < 2493
                    ? (c >= 2486 && c <= 2489)
                    : c <= 2493)
                  : (c <= 2510 || (c >= 2524 && c <= 2525)))
                : (c <= 2529 || (c < 2565
                  ? (c < 2556
                    ? (c >= 2544 && c <= 2545)
                    : c <= 2556)
                  : (c <= 2570 || (c >= 2575 && c <= 2576)))))
              : (c <= 2600 || (c < 2649
                ? (c < 2613
                  ? (c < 2610
                    ? (c >= 2602 && c <= 2608)
                    : c <= 2611)
                  : (c <= 2614 || (c >= 2616 && c <= 2617)))
                : (c <= 2652 || (c < 2693
                  ? (c < 2674
                    ? c == 2654
                    : c <= 2676)
                  : (c <= 2701 || (c >= 2703 && c <= 2705)))))))))))
        : (c <= 2728 || (c < 3242
          ? (c < 2962
            ? (c < 2858
              ? (c < 2784
                ? (c < 2741
                  ? (c < 2738
                    ? (c >= 2730 && c <= 2736)
                    : c <= 2739)
                  : (c <= 2745 || (c < 2768
                    ? c == 2749
                    : c <= 2768)))
                : (c <= 2785 || (c < 2831
                  ? (c < 2821
                    ? c == 2809
                    : c <= 2828)
                  : (c <= 2832 || (c >= 2835 && c <= 2856)))))
              : (c <= 2864 || (c < 2911
                ? (c < 2877
                  ? (c < 2869
                    ? (c >= 2866 && c <= 2867)
                    : c <= 2873)
                  : (c <= 2877 || (c >= 2908 && c <= 2909)))
                : (c <= 2913 || (c < 2949
                  ? (c < 2947
                    ? c == 2929
                    : c <= 2947)
                  : (c <= 2954 || (c >= 2958 && c <= 2960)))))))
            : (c <= 2965 || (c < 3090
              ? (c < 2984
                ? (c < 2974
                  ? (c < 2972
                    ? (c >= 2969 && c <= 2970)
                    : c <= 2972)
                  : (c <= 2975 || (c >= 2979 && c <= 2980)))
                : (c <= 2986 || (c < 3077
                  ? (c < 3024
                    ? (c >= 2990 && c <= 3001)
                    : c <= 3024)
                  : (c <= 3084 || (c >= 3086 && c <= 3088)))))
              : (c <= 3112 || (c < 3168
                ? (c < 3160
                  ? (c < 3133
                    ? (c >= 3114 && c <= 3129)
                    : c <= 3133)
                  : (c <= 3162 || c == 3165))
                : (c <= 3169 || (c < 3214
                  ? (c < 3205
                    ? c == 3200
                    : c <= 3212)
                  : (c <= 3216 || (c >= 3218 && c <= 3240)))))))))
          : (c <= 3251 || (c < 3648
            ? (c < 3412
              ? (c < 3332
                ? (c < 3293
                  ? (c < 3261
                    ? (c >= 3253 && c <= 3257)
                    : c <= 3261)
                  : (c <= 3294 || (c < 3313
                    ? (c >= 3296 && c <= 3297)
                    : c <= 3314)))
                : (c <= 3340 || (c < 3389
                  ? (c < 3346
                    ? (c >= 3342 && c <= 3344)
                    : c <= 3386)
                  : (c <= 3389 || c == 3406))))
              : (c <= 3414 || (c < 3507
                ? (c < 3461
                  ? (c < 3450
                    ? (c >= 3423 && c <= 3425)
                    : c <= 3455)
                  : (c <= 3478 || (c >= 3482 && c <= 3505)))
                : (c <= 3515 || (c < 3585
                  ? (c < 3520
                    ? c == 3517
                    : c <= 3526)
                  : (c <= 3632 || c == 3634))))))
            : (c <= 3654 || (c < 3782
              ? (c < 3749
                ? (c < 3718
                  ? (c < 3716
                    ? (c >= 3713 && c <= 3714)
                    : c <= 3716)
                  : (c <= 3722 || (c >= 3724 && c <= 3747)))
                : (c <= 3749 || (c < 3773
                  ? (c < 3762
                    ? (c >= 3751 && c <= 3760)
                    : c <= 3762)
                  : (c <= 3773 || (c >= 3776 && c <= 3780)))))
              : (c <= 3782 || (c < 3976
                ? (c < 3904
                  ? (c < 3840
                    ? (c >= 3804 && c <= 3807)
                    : c <= 3840)
                  : (c <= 3911 || (c >= 3913 && c <= 3948)))
                : (c <= 3980 || (c < 4176
                  ? (c < 4159
                    ? (c >= 4096 && c <= 4138)
                    : c <= 4159)
                  : (c <= 4181 || (c >= 4186 && c <= 4189)))))))))))))
      : (c <= 4193 || (c < 8134
        ? (c < 6176
          ? (c < 4808
            ? (c < 4688
              ? (c < 4295
                ? (c < 4213
                  ? (c < 4206
                    ? (c >= 4197 && c <= 4198)
                    : c <= 4208)
                  : (c <= 4225 || (c < 4256
                    ? c == 4238
                    : c <= 4293)))
                : (c <= 4295 || (c < 4348
                  ? (c < 4304
                    ? c == 4301
                    : c <= 4346)
                  : (c <= 4680 || (c >= 4682 && c <= 4685)))))
              : (c <= 4694 || (c < 4752
                ? (c < 4704
                  ? (c < 4698
                    ? c == 4696
                    : c <= 4701)
                  : (c <= 4744 || (c >= 4746 && c <= 4749)))
                : (c <= 4784 || (c < 4800
                  ? (c < 4792
                    ? (c >= 4786 && c <= 4789)
                    : c <= 4798)
                  : (c <= 4800 || (c >= 4802 && c <= 4805)))))))
            : (c <= 4822 || (c < 5792
              ? (c < 5024
                ? (c < 4888
                  ? (c < 4882
                    ? (c >= 4824 && c <= 4880)
                    : c <= 4885)
                  : (c <= 4954 || (c >= 4992 && c <= 5007)))
                : (c <= 5109 || (c < 5743
                  ? (c < 5121
                    ? (c >= 5112 && c <= 5117)
                    : c <= 5740)
                  : (c <= 5759 || (c >= 5761 && c <= 5786)))))
              : (c <= 5866 || (c < 5984
                ? (c < 5919
                  ? (c < 5888
                    ? (c >= 5870 && c <= 5880)
                    : c <= 5905)
                  : (c <= 5937 || (c >= 5952 && c <= 5969)))
                : (c <= 5996 || (c < 6103
                  ? (c < 6016
                    ? (c >= 5998 && c <= 6000)
                    : c <= 6067)
                  : (c <= 6103 || c == 6108))))))))
          : (c <= 6264 || (c < 7312
            ? (c < 6823
              ? (c < 6512
                ? (c < 6320
                  ? (c < 6314
                    ? (c >= 6272 && c <= 6312)
                    : c <= 6314)
                  : (c <= 6389 || (c < 6480
                    ? (c >= 6400 && c <= 6430)
                    : c <= 6509)))
                : (c <= 6516 || (c < 6656
                  ? (c < 6576
                    ? (c >= 6528 && c <= 6571)
                    : c <= 6601)
                  : (c <= 6678 || (c >= 6688 && c <= 6740)))))
              : (c <= 6823 || (c < 7098
                ? (c < 7043
                  ? (c < 6981
                    ? (c >= 6917 && c <= 6963)
                    : c <= 6988)
                  : (c <= 7072 || (c >= 7086 && c <= 7087)))
                : (c <= 7141 || (c < 7258
                  ? (c < 7245
                    ? (c >= 7168 && c <= 7203)
                    : c <= 7247)
                  : (c <= 7293 || (c >= 7296 && c <= 7304)))))))
            : (c <= 7354 || (c < 8008
              ? (c < 7418
                ? (c < 7406
                  ? (c < 7401
                    ? (c >= 7357 && c <= 7359)
                    : c <= 7404)
                  : (c <= 7411 || (c >= 7413 && c <= 7414)))
                : (c <= 7418 || (c < 7960
                  ? (c < 7680
                    ? (c >= 7424 && c <= 7615)
                    : c <= 7957)
                  : (c <= 7965 || (c >= 7968 && c <= 8005)))))
              : (c <= 8013 || (c < 8031
                ? (c < 8027
                  ? (c < 8025
                    ? (c >= 8016 && c <= 8023)
                    : c <= 8025)
                  : (c <= 8027 || c == 8029))
                : (c <= 8061 || (c < 8126
                  ? (c < 8118
                    ? (c >= 8064 && c <= 8116)
                    : c <= 8124)
                  : (c <= 8126 || (c >= 8130 && c <= 8132)))))))))))
        : (c <= 8140 || (c < 12337
          ? (c < 8544
            ? (c < 8458
              ? (c < 8305
                ? (c < 8160
                  ? (c < 8150
                    ? (c >= 8144 && c <= 8147)
                    : c <= 8155)
                  : (c <= 8172 || (c < 8182
                    ? (c >= 8178 && c <= 8180)
                    : c <= 8188)))
                : (c <= 8305 || (c < 8450
                  ? (c < 8336
                    ? c == 8319
                    : c <= 8348)
                  : (c <= 8450 || c == 8455))))
              : (c <= 8467 || (c < 8488
                ? (c < 8484
                  ? (c < 8472
                    ? c == 8469
                    : c <= 8477)
                  : (c <= 8484 || c == 8486))
                : (c <= 8488 || (c < 8517
                  ? (c < 8508
                    ? (c >= 8490 && c <= 8505)
                    : c <= 8511)
                  : (c <= 8521 || c == 8526))))))
            : (c <= 8584 || (c < 11680
              ? (c < 11559
                ? (c < 11506
                  ? (c < 11499
                    ? (c >= 11264 && c <= 11492)
                    : c <= 11502)
                  : (c <= 11507 || (c >= 11520 && c <= 11557)))
                : (c <= 11559 || (c < 11631
                  ? (c < 11568
                    ? c == 11565
                    : c <= 11623)
                  : (c <= 11631 || (c >= 11648 && c <= 11670)))))
              : (c <= 11686 || (c < 11720
                ? (c < 11704
                  ? (c < 11696
                    ? (c >= 11688 && c <= 11694)
                    : c <= 11702)
                  : (c <= 11710 || (c >= 11712 && c <= 11718)))
                : (c <= 11726 || (c < 12293
                  ? (c < 11736
                    ? (c >= 11728 && c <= 11734)
                    : c <= 11742)
                  : (c <= 12295 || (c >= 12321 && c <= 12329)))))))))
          : (c <= 12341 || (c < 42891
            ? (c < 19968
              ? (c < 12549
                ? (c < 12445
                  ? (c < 12353
                    ? (c >= 12344 && c <= 12348)
                    : c <= 12438)
                  : (c <= 12447 || (c < 12540
                    ? (c >= 12449 && c <= 12538)
                    : c <= 12543)))
                : (c <= 12591 || (c < 12784
                  ? (c < 12704
                    ? (c >= 12593 && c <= 12686)
                    : c <= 12735)
                  : (c <= 12799 || (c >= 13312 && c <= 19903)))))
              : (c <= 42124 || (c < 42560
                ? (c < 42512
                  ? (c < 42240
                    ? (c >= 42192 && c <= 42237)
                    : c <= 42508)
                  : (c <= 42527 || (c >= 42538 && c <= 42539)))
                : (c <= 42606 || (c < 42775
                  ? (c < 42656
                    ? (c >= 42623 && c <= 42653)
                    : c <= 42735)
                  : (c <= 42783 || (c >= 42786 && c <= 42888)))))))
            : (c <= 42954 || (c < 43250
              ? (c < 43011
                ? (c < 42965
                  ? (c < 42963
                    ? (c >= 42960 && c <= 42961)
                    : c <= 42963)
                  : (c <= 42969 || (c >= 42994 && c <= 43009)))
                : (c <= 43013 || (c < 43072
                  ? (c < 43020
                    ? (c >= 43015 && c <= 43018)
                    : c <= 43042)
                  : (c <= 43123 || (c >= 43138 && c <= 43187)))))
              : (c <= 43255 || (c < 43360
                ? (c < 43274
                  ? (c < 43261
                    ? c == 43259
                    : c <= 43262)
                  : (c <= 43301 || (c >= 43312 && c <= 43334)))
                : (c <= 43388 || (c < 43488
                  ? (c < 43471
                    ? (c >= 43396 && c <= 43442)
                    : c <= 43471)
                  : (c <= 43492 || (c >= 43494 && c <= 43503)))))))))))))))
    : (c <= 43518 || (c < 70727
      ? (c < 66956
        ? (c < 64914
          ? (c < 43868
            ? (c < 43714
              ? (c < 43646
                ? (c < 43588
                  ? (c < 43584
                    ? (c >= 43520 && c <= 43560)
                    : c <= 43586)
                  : (c <= 43595 || (c < 43642
                    ? (c >= 43616 && c <= 43638)
                    : c <= 43642)))
                : (c <= 43695 || (c < 43705
                  ? (c < 43701
                    ? c == 43697
                    : c <= 43702)
                  : (c <= 43709 || c == 43712))))
              : (c <= 43714 || (c < 43785
                ? (c < 43762
                  ? (c < 43744
                    ? (c >= 43739 && c <= 43741)
                    : c <= 43754)
                  : (c <= 43764 || (c >= 43777 && c <= 43782)))
                : (c <= 43790 || (c < 43816
                  ? (c < 43808
                    ? (c >= 43793 && c <= 43798)
                    : c <= 43814)
                  : (c <= 43822 || (c >= 43824 && c <= 43866)))))))
            : (c <= 43881 || (c < 64287
              ? (c < 63744
                ? (c < 55216
                  ? (c < 44032
                    ? (c >= 43888 && c <= 44002)
                    : c <= 55203)
                  : (c <= 55238 || (c >= 55243 && c <= 55291)))
                : (c <= 64109 || (c < 64275
                  ? (c < 64256
                    ? (c >= 64112 && c <= 64217)
                    : c <= 64262)
                  : (c <= 64279 || c == 64285))))
              : (c <= 64296 || (c < 64323
                ? (c < 64318
                  ? (c < 64312
                    ? (c >= 64298 && c <= 64310)
                    : c <= 64316)
                  : (c <= 64318 || (c >= 64320 && c <= 64321)))
                : (c <= 64324 || (c < 64612
                  ? (c < 64467
                    ? (c >= 64326 && c <= 64433)
                    : c <= 64605)
                  : (c <= 64829 || (c >= 64848 && c <= 64911)))))))))
          : (c <= 64967 || (c < 65599
            ? (c < 65382
              ? (c < 65147
                ? (c < 65139
                  ? (c < 65137
                    ? (c >= 65008 && c <= 65017)
                    : c <= 65137)
                  : (c <= 65139 || (c < 65145
                    ? c == 65143
                    : c <= 65145)))
                : (c <= 65147 || (c < 65313
                  ? (c < 65151
                    ? c == 65149
                    : c <= 65276)
                  : (c <= 65338 || (c >= 65345 && c <= 65370)))))
              : (c <= 65437 || (c < 65498
                ? (c < 65482
                  ? (c < 65474
                    ? (c >= 65440 && c <= 65470)
                    : c <= 65479)
                  : (c <= 65487 || (c >= 65490 && c <= 65495)))
                : (c <= 65500 || (c < 65576
                  ? (c < 65549
                    ? (c >= 65536 && c <= 65547)
                    : c <= 65574)
                  : (c <= 65594 || (c >= 65596 && c <= 65597)))))))
            : (c <= 65613 || (c < 66464
              ? (c < 66208
                ? (c < 65856
                  ? (c < 65664
                    ? (c >= 65616 && c <= 65629)
                    : c <= 65786)
                  : (c <= 65908 || (c >= 66176 && c <= 66204)))
                : (c <= 66256 || (c < 66384
                  ? (c < 66349
                    ? (c >= 66304 && c <= 66335)
                    : c <= 66378)
                  : (c <= 66421 || (c >= 66432 && c <= 66461)))))
              : (c <= 66499 || (c < 66776
                ? (c < 66560
                  ? (c < 66513
                    ? (c >= 66504 && c <= 66511)
                    : c <= 66517)
                  : (c <= 66717 || (c >= 66736 && c <= 66771)))
                : (c <= 66811 || (c < 66928
                  ? (c < 66864
                    ? (c >= 66816 && c <= 66855)
                    : c <= 66915)
                  : (c <= 66938 || (c >= 66940 && c <= 66954)))))))))))
        : (c <= 66962 || (c < 68864
          ? (c < 67828
            ? (c < 67506
              ? (c < 67072
                ? (c < 66979
                  ? (c < 66967
                    ? (c >= 66964 && c <= 66965)
                    : c <= 66977)
                  : (c <= 66993 || (c < 67003
                    ? (c >= 66995 && c <= 67001)
                    : c <= 67004)))
                : (c <= 67382 || (c < 67456
                  ? (c < 67424
                    ? (c >= 67392 && c <= 67413)
                    : c <= 67431)
                  : (c <= 67461 || (c >= 67463 && c <= 67504)))))
              : (c <= 67514 || (c < 67644
                ? (c < 67594
                  ? (c < 67592
                    ? (c >= 67584 && c <= 67589)
                    : c <= 67592)
                  : (c <= 67637 || (c >= 67639 && c <= 67640)))
                : (c <= 67644 || (c < 67712
                  ? (c < 67680
                    ? (c >= 67647 && c <= 67669)
                    : c <= 67702)
                  : (c <= 67742 || (c >= 67808 && c <= 67826)))))))
            : (c <= 67829 || (c < 68224
              ? (c < 68096
                ? (c < 67968
                  ? (c < 67872
                    ? (c >= 67840 && c <= 67861)
                    : c <= 67897)
                  : (c <= 68023 || (c >= 68030 && c <= 68031)))
                : (c <= 68096 || (c < 68121
                  ? (c < 68117
                    ? (c >= 68112 && c <= 68115)
                    : c <= 68119)
                  : (c <= 68149 || (c >= 68192 && c <= 68220)))))
              : (c <= 68252 || (c < 68448
                ? (c < 68352
                  ? (c < 68297
                    ? (c >= 68288 && c <= 68295)
                    : c <= 68324)
                  : (c <= 68405 || (c >= 68416 && c <= 68437)))
                : (c <= 68466 || (c < 68736
                  ? (c < 68608
                    ? (c >= 68480 && c <= 68497)
                    : c <= 68680)
                  : (c <= 68786 || (c >= 68800 && c <= 68850)))))))))
          : (c <= 68899 || (c < 70106
            ? (c < 69749
              ? (c < 69488
                ? (c < 69376
                  ? (c < 69296
                    ? (c >= 69248 && c <= 69289)
                    : c <= 69297)
                  : (c <= 69404 || (c < 69424
                    ? c == 69415
                    : c <= 69445)))
                : (c <= 69505 || (c < 69635
                  ? (c < 69600
                    ? (c >= 69552 && c <= 69572)
                    : c <= 69622)
                  : (c <= 69687 || (c >= 69745 && c <= 69746)))))
              : (c <= 69749 || (c < 69959
                ? (c < 69891
                  ? (c < 69840
                    ? (c >= 69763 && c <= 69807)
                    : c <= 69864)
                  : (c <= 69926 || c == 69956))
                : (c <= 69959 || (c < 70019
                  ? (c < 70006
                    ? (c >= 69968 && c <= 70002)
                    : c <= 70006)
                  : (c <= 70066 || (c >= 70081 && c <= 70084)))))))
            : (c <= 70106 || (c < 70405
              ? (c < 70280
                ? (c < 70163
                  ? (c < 70144
                    ? c == 70108
                    : c <= 70161)
                  : (c <= 70187 || (c >= 70272 && c <= 70278)))
                : (c <= 70280 || (c < 70303
                  ? (c < 70287
                    ? (c >= 70282 && c <= 70285)
                    : c <= 70301)
                  : (c <= 70312 || (c >= 70320 && c <= 70366)))))
              : (c <= 70412 || (c < 70453
                ? (c < 70442
                  ? (c < 70419
                    ? (c >= 70415 && c <= 70416)
                    : c <= 70440)
                  : (c <= 70448 || (c >= 70450 && c <= 70451)))
                : (c <= 70457 || (c < 70493
                  ? (c < 70480
                    ? c == 70461
                    : c <= 70480)
                  : (c <= 70497 || (c >= 70656 && c <= 70708)))))))))))))
      : (c <= 70730 || (c < 119894
        ? (c < 73056
          ? (c < 72001
            ? (c < 71424
              ? (c < 71128
                ? (c < 70852
                  ? (c < 70784
                    ? (c >= 70751 && c <= 70753)
                    : c <= 70831)
                  : (c <= 70853 || (c < 71040
                    ? c == 70855
                    : c <= 71086)))
                : (c <= 71131 || (c < 71296
                  ? (c < 71236
                    ? (c >= 71168 && c <= 71215)
                    : c <= 71236)
                  : (c <= 71338 || c == 71352))))
              : (c <= 71450 || (c < 71945
                ? (c < 71840
                  ? (c < 71680
                    ? (c >= 71488 && c <= 71494)
                    : c <= 71723)
                  : (c <= 71903 || (c >= 71935 && c <= 71942)))
                : (c <= 71945 || (c < 71960
                  ? (c < 71957
                    ? (c >= 71948 && c <= 71955)
                    : c <= 71958)
                  : (c <= 71983 || c == 71999))))))
            : (c <= 72001 || (c < 72349
              ? (c < 72192
                ? (c < 72161
                  ? (c < 72106
                    ? (c >= 72096 && c <= 72103)
                    : c <= 72144)
                  : (c <= 72161 || c == 72163))
                : (c <= 72192 || (c < 72272
                  ? (c < 72250
                    ? (c >= 72203 && c <= 72242)
                    : c <= 72250)
                  : (c <= 72272 || (c >= 72284 && c <= 72329)))))
              : (c <= 72349 || (c < 72818
                ? (c < 72714
                  ? (c < 72704
                    ? (c >= 72368 && c <= 72440)
                    : c <= 72712)
                  : (c <= 72750 || c == 72768))
                : (c <= 72847 || (c < 72971
                  ? (c < 72968
                    ? (c >= 72960 && c <= 72966)
                    : c <= 72969)
                  : (c <= 73008 || c == 73030))))))))
          : (c <= 73061 || (c < 93952
            ? (c < 82944
              ? (c < 73728
                ? (c < 73112
                  ? (c < 73066
                    ? (c >= 73063 && c <= 73064)
                    : c <= 73097)
                  : (c <= 73112 || (c < 73648
                    ? (c >= 73440 && c <= 73458)
                    : c <= 73648)))
                : (c <= 74649 || (c < 77712
                  ? (c < 74880
                    ? (c >= 74752 && c <= 74862)
                    : c <= 75075)
                  : (c <= 77808 || (c >= 77824 && c <= 78894)))))
              : (c <= 83526 || (c < 92928
                ? (c < 92784
                  ? (c < 92736
                    ? (c >= 92160 && c <= 92728)
                    : c <= 92766)
                  : (c <= 92862 || (c >= 92880 && c <= 92909)))
                : (c <= 92975 || (c < 93053
                  ? (c < 93027
                    ? (c >= 92992 && c <= 92995)
                    : c <= 93047)
                  : (c <= 93071 || (c >= 93760 && c <= 93823)))))))
            : (c <= 94026 || (c < 110589
              ? (c < 94208
                ? (c < 94176
                  ? (c < 94099
                    ? c == 94032
                    : c <= 94111)
                  : (c <= 94177 || c == 94179))
                : (c <= 100343 || (c < 110576
                  ? (c < 101632
                    ? (c >= 100352 && c <= 101589)
                    : c <= 101640)
                  : (c <= 110579 || (c >= 110581 && c <= 110587)))))
              : (c <= 110590 || (c < 113664
                ? (c < 110948
                  ? (c < 110928
                    ? (c >= 110592 && c <= 110882)
                    : c <= 110930)
                  : (c <= 110951 || (c >= 110960 && c <= 111355)))
                : (c <= 113770 || (c < 113808
                  ? (c < 113792
                    ? (c >= 113776 && c <= 113788)
                    : c <= 113800)
                  : (c <= 113817 || (c >= 119808 && c <= 119892)))))))))))
        : (c <= 119964 || (c < 125259
          ? (c < 120572
            ? (c < 120086
              ? (c < 119995
                ? (c < 119973
                  ? (c < 119970
                    ? (c >= 119966 && c <= 119967)
                    : c <= 119970)
                  : (c <= 119974 || (c < 119982
                    ? (c >= 119977 && c <= 119980)
                    : c <= 119993)))
                : (c <= 119995 || (c < 120071
                  ? (c < 120005
                    ? (c >= 119997 && c <= 120003)
                    : c <= 120069)
                  : (c <= 120074 || (c >= 120077 && c <= 120084)))))
              : (c <= 120092 || (c < 120138
                ? (c < 120128
                  ? (c < 120123
                    ? (c >= 120094 && c <= 120121)
                    : c <= 120126)
                  : (c <= 120132 || c == 120134))
                : (c <= 120144 || (c < 120514
                  ? (c < 120488
                    ? (c >= 120146 && c <= 120485)
                    : c <= 120512)
                  : (c <= 120538 || (c >= 120540 && c <= 120570)))))))
            : (c <= 120596 || (c < 123191
              ? (c < 120714
                ? (c < 120656
                  ? (c < 120630
                    ? (c >= 120598 && c <= 120628)
                    : c <= 120654)
                  : (c <= 120686 || (c >= 120688 && c <= 120712)))
                : (c <= 120744 || (c < 122624
                  ? (c < 120772
                    ? (c >= 120746 && c <= 120770)
                    : c <= 120779)
                  : (c <= 122654 || (c >= 123136 && c <= 123180)))))
              : (c <= 123197 || (c < 124904
                ? (c < 123584
                  ? (c < 123536
                    ? c == 123214
                    : c <= 123565)
                  : (c <= 123627 || (c >= 124896 && c <= 124902)))
                : (c <= 124907 || (c < 124928
                  ? (c < 124912
                    ? (c >= 124909 && c <= 124910)
                    : c <= 124926)
                  : (c <= 125124 || (c >= 125184 && c <= 125251)))))))))
          : (c <= 125259 || (c < 126559
            ? (c < 126535
              ? (c < 126505
                ? (c < 126497
                  ? (c < 126469
                    ? (c >= 126464 && c <= 126467)
                    : c <= 126495)
                  : (c <= 126498 || (c < 126503
                    ? c == 126500
                    : c <= 126503)))
                : (c <= 126514 || (c < 126523
                  ? (c < 126521
                    ? (c >= 126516 && c <= 126519)
                    : c <= 126521)
                  : (c <= 126523 || c == 126530))))
              : (c <= 126535 || (c < 126548
                ? (c < 126541
                  ? (c < 126539
                    ? c == 126537
                    : c <= 126539)
                  : (c <= 126543 || (c >= 126545 && c <= 126546)))
                : (c <= 126548 || (c < 126555
                  ? (c < 126553
                    ? c == 126551
                    : c <= 126553)
                  : (c <= 126555 || c == 126557))))))
            : (c <= 126559 || (c < 126625
              ? (c < 126580
                ? (c < 126567
                  ? (c < 126564
                    ? (c >= 126561 && c <= 126562)
                    : c <= 126564)
                  : (c <= 126570 || (c >= 126572 && c <= 126578)))
                : (c <= 126583 || (c < 126592
                  ? (c < 126590
                    ? (c >= 126585 && c <= 126588)
                    : c <= 126590)
                  : (c <= 126601 || (c >= 126603 && c <= 126619)))))
              : (c <= 126627 || (c < 177984
                ? (c < 131072
                  ? (c < 126635
                    ? (c >= 126629 && c <= 126633)
                    : c <= 126651)
                  : (c <= 173791 || (c >= 173824 && c <= 177976)))
                : (c <= 178205 || (c < 194560
                  ? (c < 183984
                    ? (c >= 178208 && c <= 183969)
                    : c <= 191456)
                  : (c <= 195101 || (c >= 196608 && c <= 201546)))))))))))))))));
}

static inline bool sym_identifier_character_set_2(int32_t c) {
  return (c < 43494
    ? (c < 4186
      ? (c < 2703
        ? (c < 1969
          ? (c < 908
            ? (c < 710
              ? (c < 181
                ? (c < '_'
                  ? (c < 'A'
                    ? (c >= '0' && c <= '9')
                    : c <= 'Z')
                  : (c <= '_' || (c < 170
                    ? (c >= 'a' && c <= 'z')
                    : c <= 170)))
                : (c <= 181 || (c < 216
                  ? (c < 192
                    ? c == 186
                    : c <= 214)
                  : (c <= 246 || (c >= 248 && c <= 705)))))
              : (c <= 721 || (c < 886
                ? (c < 750
                  ? (c < 748
                    ? (c >= 736 && c <= 740)
                    : c <= 748)
                  : (c <= 750 || (c >= 880 && c <= 884)))
                : (c <= 887 || (c < 902
                  ? (c < 895
                    ? (c >= 891 && c <= 893)
                    : c <= 895)
                  : (c <= 902 || (c >= 904 && c <= 906)))))))
            : (c <= 908 || (c < 1646
              ? (c < 1369
                ? (c < 1015
                  ? (c < 931
                    ? (c >= 910 && c <= 929)
                    : c <= 1013)
                  : (c <= 1153 || (c < 1329
                    ? (c >= 1162 && c <= 1327)
                    : c <= 1366)))
                : (c <= 1369 || (c < 1519
                  ? (c < 1488
                    ? (c >= 1376 && c <= 1416)
                    : c <= 1514)
                  : (c <= 1522 || (c >= 1568 && c <= 1610)))))
              : (c <= 1647 || (c < 1786
                ? (c < 1765
                  ? (c < 1749
                    ? (c >= 1649 && c <= 1747)
                    : c <= 1749)
                  : (c <= 1766 || (c >= 1774 && c <= 1775)))
                : (c <= 1788 || (c < 1810
                  ? (c < 1808
                    ? c == 1791
                    : c <= 1808)
                  : (c <= 1839 || (c >= 1869 && c <= 1957)))))))))
          : (c <= 1969 || (c < 2474
            ? (c < 2185
              ? (c < 2084
                ? (c < 2042
                  ? (c < 2036
                    ? (c >= 1994 && c <= 2026)
                    : c <= 2037)
                  : (c <= 2042 || (c < 2074
                    ? (c >= 2048 && c <= 2069)
                    : c <= 2074)))
                : (c <= 2084 || (c < 2144
                  ? (c < 2112
                    ? c == 2088
                    : c <= 2136)
                  : (c <= 2154 || (c >= 2160 && c <= 2183)))))
              : (c <= 2190 || (c < 2392
                ? (c < 2365
                  ? (c < 2308
                    ? (c >= 2208 && c <= 2249)
                    : c <= 2361)
                  : (c <= 2365 || c == 2384))
                : (c <= 2401 || (c < 2447
                  ? (c < 2437
                    ? (c >= 2417 && c <= 2432)
                    : c <= 2444)
                  : (c <= 2448 || (c >= 2451 && c <= 2472)))))))
            : (c <= 2480 || (c < 2575
              ? (c < 2524
                ? (c < 2493
                  ? (c < 2486
                    ? c == 2482
                    : c <= 2489)
                  : (c <= 2493 || c == 2510))
                : (c <= 2525 || (c < 2556
                  ? (c < 2544
                    ? (c >= 2527 && c <= 2529)
                    : c <= 2545)
                  : (c <= 2556 || (c >= 2565 && c <= 2570)))))
              : (c <= 2576 || (c < 2616
                ? (c < 2610
                  ? (c < 2602
                    ? (c >= 2579 && c <= 2600)
                    : c <= 2608)
                  : (c <= 2611 || (c >= 2613 && c <= 2614)))
                : (c <= 2617 || (c < 2674
                  ? (c < 2654
                    ? (c >= 2649 && c <= 2652)
                    : c <= 2654)
                  : (c <= 2676 || (c >= 2693 && c <= 2701)))))))))))
        : (c <= 2705 || (c < 3218
          ? (c < 2958
            ? (c < 2835
              ? (c < 2768
                ? (c < 2738
                  ? (c < 2730
                    ? (c >= 2707 && c <= 2728)
                    : c <= 2736)
                  : (c <= 2739 || (c < 2749
                    ? (c >= 2741 && c <= 2745)
                    : c <= 2749)))
                : (c <= 2768 || (c < 2821
                  ? (c < 2809
                    ? (c >= 2784 && c <= 2785)
                    : c <= 2809)
                  : (c <= 2828 || (c >= 2831 && c <= 2832)))))
              : (c <= 2856 || (c < 2908
                ? (c < 2869
                  ? (c < 2866
                    ? (c >= 2858 && c <= 2864)
                    : c <= 2867)
                  : (c <= 2873 || c == 2877))
                : (c <= 2909 || (c < 2947
                  ? (c < 2929
                    ? (c >= 2911 && c <= 2913)
                    : c <= 2929)
                  : (c <= 2947 || (c >= 2949 && c <= 2954)))))))
            : (c <= 2960 || (c < 3086
              ? (c < 2979
                ? (c < 2972
                  ? (c < 2969
                    ? (c >= 2962 && c <= 2965)
                    : c <= 2970)
                  : (c <= 2972 || (c >= 2974 && c <= 2975)))
                : (c <= 2980 || (c < 3024
                  ? (c < 2990
                    ? (c >= 2984 && c <= 2986)
                    : c <= 3001)
                  : (c <= 3024 || (c >= 3077 && c <= 3084)))))
              : (c <= 3088 || (c < 3165
                ? (c < 3133
                  ? (c < 3114
                    ? (c >= 3090 && c <= 3112)
                    : c <= 3129)
                  : (c <= 3133 || (c >= 3160 && c <= 3162)))
                : (c <= 3165 || (c < 3205
                  ? (c < 3200
                    ? (c >= 3168 && c <= 3169)
                    : c <= 3200)
                  : (c <= 3212 || (c >= 3214 && c <= 3216)))))))))
          : (c <= 3240 || (c < 3634
            ? (c < 3406
              ? (c < 3313
                ? (c < 3261
                  ? (c < 3253
                    ? (c >= 3242 && c <= 3251)
                    : c <= 3257)
                  : (c <= 3261 || (c < 3296
                    ? (c >= 3293 && c <= 3294)
                    : c <= 3297)))
                : (c <= 3314 || (c < 3346
                  ? (c < 3342
                    ? (c >= 3332 && c <= 3340)
                    : c <= 3344)
                  : (c <= 3386 || c == 3389))))
              : (c <= 3406 || (c < 3482
                ? (c < 3450
                  ? (c < 3423
                    ? (c >= 3412 && c <= 3414)
                    : c <= 3425)
                  : (c <= 3455 || (c >= 3461 && c <= 3478)))
                : (c <= 3505 || (c < 3520
                  ? (c < 3517
                    ? (c >= 3507 && c <= 3515)
                    : c <= 3517)
                  : (c <= 3526 || (c >= 3585 && c <= 3632)))))))
            : (c <= 3634 || (c < 3776
              ? (c < 3724
                ? (c < 3716
                  ? (c < 3713
                    ? (c >= 3648 && c <= 3654)
                    : c <= 3714)
                  : (c <= 3716 || (c >= 3718 && c <= 3722)))
                : (c <= 3747 || (c < 3762
                  ? (c < 3751
                    ? c == 3749
                    : c <= 3760)
                  : (c <= 3762 || c == 3773))))
              : (c <= 3780 || (c < 3913
                ? (c < 3840
                  ? (c < 3804
                    ? c == 3782
                    : c <= 3807)
                  : (c <= 3840 || (c >= 3904 && c <= 3911)))
                : (c <= 3948 || (c < 4159
                  ? (c < 4096
                    ? (c >= 3976 && c <= 3980)
                    : c <= 4138)
                  : (c <= 4159 || (c >= 4176 && c <= 4181)))))))))))))
      : (c <= 4189 || (c < 8130
        ? (c < 6108
          ? (c < 4802
            ? (c < 4682
              ? (c < 4256
                ? (c < 4206
                  ? (c < 4197
                    ? c == 4193
                    : c <= 4198)
                  : (c <= 4208 || (c < 4238
                    ? (c >= 4213 && c <= 4225)
                    : c <= 4238)))
                : (c <= 4293 || (c < 4304
                  ? (c < 4301
                    ? c == 4295
                    : c <= 4301)
                  : (c <= 4346 || (c >= 4348 && c <= 4680)))))
              : (c <= 4685 || (c < 4746
                ? (c < 4698
                  ? (c < 4696
                    ? (c >= 4688 && c <= 4694)
                    : c <= 4696)
                  : (c <= 4701 || (c >= 4704 && c <= 4744)))
                : (c <= 4749 || (c < 4792
                  ? (c < 4786
                    ? (c >= 4752 && c <= 4784)
                    : c <= 4789)
                  : (c <= 4798 || c == 4800))))))
            : (c <= 4805 || (c < 5761
              ? (c < 4992
                ? (c < 4882
                  ? (c < 4824
                    ? (c >= 4808 && c <= 4822)
                    : c <= 4880)
                  : (c <= 4885 || (c >= 4888 && c <= 4954)))
                : (c <= 5007 || (c < 5121
                  ? (c < 5112
                    ? (c >= 5024 && c <= 5109)
                    : c <= 5117)
                  : (c <= 5740 || (c >= 5743 && c <= 5759)))))
              : (c <= 5786 || (c < 5952
                ? (c < 5888
                  ? (c < 5870
                    ? (c >= 5792 && c <= 5866)
                    : c <= 5880)
                  : (c <= 5905 || (c >= 5919 && c <= 5937)))
                : (c <= 5969 || (c < 6016
                  ? (c < 5998
                    ? (c >= 5984 && c <= 5996)
                    : c <= 6000)
                  : (c <= 6067 || c == 6103))))))))
          : (c <= 6108 || (c < 7296
            ? (c < 6688
              ? (c < 6480
                ? (c < 6314
                  ? (c < 6272
                    ? (c >= 6176 && c <= 6264)
                    : c <= 6312)
                  : (c <= 6314 || (c < 6400
                    ? (c >= 6320 && c <= 6389)
                    : c <= 6430)))
                : (c <= 6509 || (c < 6576
                  ? (c < 6528
                    ? (c >= 6512 && c <= 6516)
                    : c <= 6571)
                  : (c <= 6601 || (c >= 6656 && c <= 6678)))))
              : (c <= 6740 || (c < 7086
                ? (c < 6981
                  ? (c < 6917
                    ? c == 6823
                    : c <= 6963)
                  : (c <= 6988 || (c >= 7043 && c <= 7072)))
                : (c <= 7087 || (c < 7245
                  ? (c < 7168
                    ? (c >= 7098 && c <= 7141)
                    : c <= 7203)
                  : (c <= 7247 || (c >= 7258 && c <= 7293)))))))
            : (c <= 7304 || (c < 7968
              ? (c < 7413
                ? (c < 7401
                  ? (c < 7357
                    ? (c >= 7312 && c <= 7354)
                    : c <= 7359)
                  : (c <= 7404 || (c >= 7406 && c <= 7411)))
                : (c <= 7414 || (c < 7680
                  ? (c < 7424
                    ? c == 7418
                    : c <= 7615)
                  : (c <= 7957 || (c >= 7960 && c <= 7965)))))
              : (c <= 8005 || (c < 8029
                ? (c < 8025
                  ? (c < 8016
                    ? (c >= 8008 && c <= 8013)
                    : c <= 8023)
                  : (c <= 8025 || c == 8027))
                : (c <= 8029 || (c < 8118
                  ? (c < 8064
                    ? (c >= 8031 && c <= 8061)
                    : c <= 8116)
                  : (c <= 8124 || c == 8126))))))))))
        : (c <= 8132 || (c < 12321
          ? (c < 8526
            ? (c < 8455
              ? (c < 8182
                ? (c < 8150
                  ? (c < 8144
                    ? (c >= 8134 && c <= 8140)
                    : c <= 8147)
                  : (c <= 8155 || (c < 8178
                    ? (c >= 8160 && c <= 8172)
                    : c <= 8180)))
                : (c <= 8188 || (c < 8336
                  ? (c < 8319
                    ? c == 8305
                    : c <= 8319)
                  : (c <= 8348 || c == 8450))))
              : (c <= 8455 || (c < 8486
                ? (c < 8472
                  ? (c < 8469
                    ? (c >= 8458 && c <= 8467)
                    : c <= 8469)
                  : (c <= 8477 || c == 8484))
                : (c <= 8486 || (c < 8508
                  ? (c < 8490
                    ? c == 8488
                    : c <= 8505)
                  : (c <= 8511 || (c >= 8517 && c <= 8521)))))))
            : (c <= 8526 || (c < 11648
              ? (c < 11520
                ? (c < 11499
                  ? (c < 11264
                    ? (c >= 8544 && c <= 8584)
                    : c <= 11492)
                  : (c <= 11502 || (c >= 11506 && c <= 11507)))
                : (c <= 11557 || (c < 11568
                  ? (c < 11565
                    ? c == 11559
                    : c <= 11565)
                  : (c <= 11623 || c == 11631))))
              : (c <= 11670 || (c < 11712
                ? (c < 11696
                  ? (c < 11688
                    ? (c >= 11680 && c <= 11686)
                    : c <= 11694)
                  : (c <= 11702 || (c >= 11704 && c <= 11710)))
                : (c <= 11718 || (c < 11736
                  ? (c < 11728
                    ? (c >= 11720 && c <= 11726)
                    : c <= 11734)
                  : (c <= 11742 || (c >= 12293 && c <= 12295)))))))))
          : (c <= 12329 || (c < 42786
            ? (c < 13312
              ? (c < 12540
                ? (c < 12353
                  ? (c < 12344
                    ? (c >= 12337 && c <= 12341)
                    : c <= 12348)
                  : (c <= 12438 || (c < 12449
                    ? (c >= 12445 && c <= 12447)
                    : c <= 12538)))
                : (c <= 12543 || (c < 12704
                  ? (c < 12593
                    ? (c >= 12549 && c <= 12591)
                    : c <= 12686)
                  : (c <= 12735 || (c >= 12784 && c <= 12799)))))
              : (c <= 19903 || (c < 42538
                ? (c < 42240
                  ? (c < 42192
                    ? (c >= 19968 && c <= 42124)
                    : c <= 42237)
                  : (c <= 42508 || (c >= 42512 && c <= 42527)))
                : (c <= 42539 || (c < 42656
                  ? (c < 42623
                    ? (c >= 42560 && c <= 42606)
                    : c <= 42653)
                  : (c <= 42735 || (c >= 42775 && c <= 42783)))))))
            : (c <= 42888 || (c < 43138
              ? (c < 42994
                ? (c < 42963
                  ? (c < 42960
                    ? (c >= 42891 && c <= 42954)
                    : c <= 42961)
                  : (c <= 42963 || (c >= 42965 && c <= 42969)))
                : (c <= 43009 || (c < 43020
                  ? (c < 43015
                    ? (c >= 43011 && c <= 43013)
                    : c <= 43018)
                  : (c <= 43042 || (c >= 43072 && c <= 43123)))))
              : (c <= 43187 || (c < 43312
                ? (c < 43261
                  ? (c < 43259
                    ? (c >= 43250 && c <= 43255)
                    : c <= 43259)
                  : (c <= 43262 || (c >= 43274 && c <= 43301)))
                : (c <= 43334 || (c < 43471
                  ? (c < 43396
                    ? (c >= 43360 && c <= 43388)
                    : c <= 43442)
                  : (c <= 43471 || (c >= 43488 && c <= 43492)))))))))))))))
    : (c <= 43503 || (c < 70727
      ? (c < 66956
        ? (c < 64914
          ? (c < 43824
            ? (c < 43712
              ? (c < 43642
                ? (c < 43584
                  ? (c < 43520
                    ? (c >= 43514 && c <= 43518)
                    : c <= 43560)
                  : (c <= 43586 || (c < 43616
                    ? (c >= 43588 && c <= 43595)
                    : c <= 43638)))
                : (c <= 43642 || (c < 43701
                  ? (c < 43697
                    ? (c >= 43646 && c <= 43695)
                    : c <= 43697)
                  : (c <= 43702 || (c >= 43705 && c <= 43709)))))
              : (c <= 43712 || (c < 43777
                ? (c < 43744
                  ? (c < 43739
                    ? c == 43714
                    : c <= 43741)
                  : (c <= 43754 || (c >= 43762 && c <= 43764)))
                : (c <= 43782 || (c < 43808
                  ? (c < 43793
                    ? (c >= 43785 && c <= 43790)
                    : c <= 43798)
                  : (c <= 43814 || (c >= 43816 && c <= 43822)))))))
            : (c <= 43866 || (c < 64287
              ? (c < 63744
                ? (c < 44032
                  ? (c < 43888
                    ? (c >= 43868 && c <= 43881)
                    : c <= 44002)
                  : (c <= 55203 || (c < 55243
                    ? (c >= 55216 && c <= 55238)
                    : c <= 55291)))
                : (c <= 64109 || (c < 64275
                  ? (c < 64256
                    ? (c >= 64112 && c <= 64217)
                    : c <= 64262)
                  : (c <= 64279 || c == 64285))))
              : (c <= 64296 || (c < 64323
                ? (c < 64318
                  ? (c < 64312
                    ? (c >= 64298 && c <= 64310)
                    : c <= 64316)
                  : (c <= 64318 || (c >= 64320 && c <= 64321)))
                : (c <= 64324 || (c < 64612
                  ? (c < 64467
                    ? (c >= 64326 && c <= 64433)
                    : c <= 64605)
                  : (c <= 64829 || (c >= 64848 && c <= 64911)))))))))
          : (c <= 64967 || (c < 65599
            ? (c < 65382
              ? (c < 65147
                ? (c < 65139
                  ? (c < 65137
                    ? (c >= 65008 && c <= 65017)
                    : c <= 65137)
                  : (c <= 65139 || (c < 65145
                    ? c == 65143
                    : c <= 65145)))
                : (c <= 65147 || (c < 65313
                  ? (c < 65151
                    ? c == 65149
                    : c <= 65276)
                  : (c <= 65338 || (c >= 65345 && c <= 65370)))))
              : (c <= 65437 || (c < 65498
                ? (c < 65482
                  ? (c < 65474
                    ? (c >= 65440 && c <= 65470)
                    : c <= 65479)
                  : (c <= 65487 || (c >= 65490 && c <= 65495)))
                : (c <= 65500 || (c < 65576
                  ? (c < 65549
                    ? (c >= 65536 && c <= 65547)
                    : c <= 65574)
                  : (c <= 65594 || (c >= 65596 && c <= 65597)))))))
            : (c <= 65613 || (c < 66464
              ? (c < 66208
                ? (c < 65856
                  ? (c < 65664
                    ? (c >= 65616 && c <= 65629)
                    : c <= 65786)
                  : (c <= 65908 || (c >= 66176 && c <= 66204)))
                : (c <= 66256 || (c < 66384
                  ? (c < 66349
                    ? (c >= 66304 && c <= 66335)
                    : c <= 66378)
                  : (c <= 66421 || (c >= 66432 && c <= 66461)))))
              : (c <= 66499 || (c < 66776
                ? (c < 66560
                  ? (c < 66513
                    ? (c >= 66504 && c <= 66511)
                    : c <= 66517)
                  : (c <= 66717 || (c >= 66736 && c <= 66771)))
                : (c <= 66811 || (c < 66928
                  ? (c < 66864
                    ? (c >= 66816 && c <= 66855)
                    : c <= 66915)
                  : (c <= 66938 || (c >= 66940 && c <= 66954)))))))))))
        : (c <= 66962 || (c < 68864
          ? (c < 67828
            ? (c < 67506
              ? (c < 67072
                ? (c < 66979
                  ? (c < 66967
                    ? (c >= 66964 && c <= 66965)
                    : c <= 66977)
                  : (c <= 66993 || (c < 67003
                    ? (c >= 66995 && c <= 67001)
                    : c <= 67004)))
                : (c <= 67382 || (c < 67456
                  ? (c < 67424
                    ? (c >= 67392 && c <= 67413)
                    : c <= 67431)
                  : (c <= 67461 || (c >= 67463 && c <= 67504)))))
              : (c <= 67514 || (c < 67644
                ? (c < 67594
                  ? (c < 67592
                    ? (c >= 67584 && c <= 67589)
                    : c <= 67592)
                  : (c <= 67637 || (c >= 67639 && c <= 67640)))
                : (c <= 67644 || (c < 67712
                  ? (c < 67680
                    ? (c >= 67647 && c <= 67669)
                    : c <= 67702)
                  : (c <= 67742 || (c >= 67808 && c <= 67826)))))))
            : (c <= 67829 || (c < 68224
              ? (c < 68096
                ? (c < 67968
                  ? (c < 67872
                    ? (c >= 67840 && c <= 67861)
                    : c <= 67897)
                  : (c <= 68023 || (c >= 68030 && c <= 68031)))
                : (c <= 68096 || (c < 68121
                  ? (c < 68117
                    ? (c >= 68112 && c <= 68115)
                    : c <= 68119)
                  : (c <= 68149 || (c >= 68192 && c <= 68220)))))
              : (c <= 68252 || (c < 68448
                ? (c < 68352
                  ? (c < 68297
                    ? (c >= 68288 && c <= 68295)
                    : c <= 68324)
                  : (c <= 68405 || (c >= 68416 && c <= 68437)))
                : (c <= 68466 || (c < 68736
                  ? (c < 68608
                    ? (c >= 68480 && c <= 68497)
                    : c <= 68680)
                  : (c <= 68786 || (c >= 68800 && c <= 68850)))))))))
          : (c <= 68899 || (c < 70106
            ? (c < 69749
              ? (c < 69488
                ? (c < 69376
                  ? (c < 69296
                    ? (c >= 69248 && c <= 69289)
                    : c <= 69297)
                  : (c <= 69404 || (c < 69424
                    ? c == 69415
                    : c <= 69445)))
                : (c <= 69505 || (c < 69635
                  ? (c < 69600
                    ? (c >= 69552 && c <= 69572)
                    : c <= 69622)
                  : (c <= 69687 || (c >= 69745 && c <= 69746)))))
              : (c <= 69749 || (c < 69959
                ? (c < 69891
                  ? (c < 69840
                    ? (c >= 69763 && c <= 69807)
                    : c <= 69864)
                  : (c <= 69926 || c == 69956))
                : (c <= 69959 || (c < 70019
                  ? (c < 70006
                    ? (c >= 69968 && c <= 70002)
                    : c <= 70006)
                  : (c <= 70066 || (c >= 70081 && c <= 70084)))))))
            : (c <= 70106 || (c < 70405
              ? (c < 70280
                ? (c < 70163
                  ? (c < 70144
                    ? c == 70108
                    : c <= 70161)
                  : (c <= 70187 || (c >= 70272 && c <= 70278)))
                : (c <= 70280 || (c < 70303
                  ? (c < 70287
                    ? (c >= 70282 && c <= 70285)
                    : c <= 70301)
                  : (c <= 70312 || (c >= 70320 && c <= 70366)))))
              : (c <= 70412 || (c < 70453
                ? (c < 70442
                  ? (c < 70419
                    ? (c >= 70415 && c <= 70416)
                    : c <= 70440)
                  : (c <= 70448 || (c >= 70450 && c <= 70451)))
                : (c <= 70457 || (c < 70493
                  ? (c < 70480
                    ? c == 70461
                    : c <= 70480)
                  : (c <= 70497 || (c >= 70656 && c <= 70708)))))))))))))
      : (c <= 70730 || (c < 119894
        ? (c < 73056
          ? (c < 72001
            ? (c < 71424
              ? (c < 71128
                ? (c < 70852
                  ? (c < 70784
                    ? (c >= 70751 && c <= 70753)
                    : c <= 70831)
                  : (c <= 70853 || (c < 71040
                    ? c == 70855
                    : c <= 71086)))
                : (c <= 71131 || (c < 71296
                  ? (c < 71236
                    ? (c >= 71168 && c <= 71215)
                    : c <= 71236)
                  : (c <= 71338 || c == 71352))))
              : (c <= 71450 || (c < 71945
                ? (c < 71840
                  ? (c < 71680
                    ? (c >= 71488 && c <= 71494)
                    : c <= 71723)
                  : (c <= 71903 || (c >= 71935 && c <= 71942)))
                : (c <= 71945 || (c < 71960
                  ? (c < 71957
                    ? (c >= 71948 && c <= 71955)
                    : c <= 71958)
                  : (c <= 71983 || c == 71999))))))
            : (c <= 72001 || (c < 72349
              ? (c < 72192
                ? (c < 72161
                  ? (c < 72106
                    ? (c >= 72096 && c <= 72103)
                    : c <= 72144)
                  : (c <= 72161 || c == 72163))
                : (c <= 72192 || (c < 72272
                  ? (c < 72250
                    ? (c >= 72203 && c <= 72242)
                    : c <= 72250)
                  : (c <= 72272 || (c >= 72284 && c <= 72329)))))
              : (c <= 72349 || (c < 72818
                ? (c < 72714
                  ? (c < 72704
                    ? (c >= 72368 && c <= 72440)
                    : c <= 72712)
                  : (c <= 72750 || c == 72768))
                : (c <= 72847 || (c < 72971
                  ? (c < 72968
                    ? (c >= 72960 && c <= 72966)
                    : c <= 72969)
                  : (c <= 73008 || c == 73030))))))))
          : (c <= 73061 || (c < 93952
            ? (c < 82944
              ? (c < 73728
                ? (c < 73112
                  ? (c < 73066
                    ? (c >= 73063 && c <= 73064)
                    : c <= 73097)
                  : (c <= 73112 || (c < 73648
                    ? (c >= 73440 && c <= 73458)
                    : c <= 73648)))
                : (c <= 74649 || (c < 77712
                  ? (c < 74880
                    ? (c >= 74752 && c <= 74862)
                    : c <= 75075)
                  : (c <= 77808 || (c >= 77824 && c <= 78894)))))
              : (c <= 83526 || (c < 92928
                ? (c < 92784
                  ? (c < 92736
                    ? (c >= 92160 && c <= 92728)
                    : c <= 92766)
                  : (c <= 92862 || (c >= 92880 && c <= 92909)))
                : (c <= 92975 || (c < 93053
                  ? (c < 93027
                    ? (c >= 92992 && c <= 92995)
                    : c <= 93047)
                  : (c <= 93071 || (c >= 93760 && c <= 93823)))))))
            : (c <= 94026 || (c < 110589
              ? (c < 94208
                ? (c < 94176
                  ? (c < 94099
                    ? c == 94032
                    : c <= 94111)
                  : (c <= 94177 || c == 94179))
                : (c <= 100343 || (c < 110576
                  ? (c < 101632
                    ? (c >= 100352 && c <= 101589)
                    : c <= 101640)
                  : (c <= 110579 || (c >= 110581 && c <= 110587)))))
              : (c <= 110590 || (c < 113664
                ? (c < 110948
                  ? (c < 110928
                    ? (c >= 110592 && c <= 110882)
                    : c <= 110930)
                  : (c <= 110951 || (c >= 110960 && c <= 111355)))
                : (c <= 113770 || (c < 113808
                  ? (c < 113792
                    ? (c >= 113776 && c <= 113788)
                    : c <= 113800)
                  : (c <= 113817 || (c >= 119808 && c <= 119892)))))))))))
        : (c <= 119964 || (c < 125259
          ? (c < 120572
            ? (c < 120086
              ? (c < 119995
                ? (c < 119973
                  ? (c < 119970
                    ? (c >= 119966 && c <= 119967)
                    : c <= 119970)
                  : (c <= 119974 || (c < 119982
                    ? (c >= 119977 && c <= 119980)
                    : c <= 119993)))
                : (c <= 119995 || (c < 120071
                  ? (c < 120005
                    ? (c >= 119997 && c <= 120003)
                    : c <= 120069)
                  : (c <= 120074 || (c >= 120077 && c <= 120084)))))
              : (c <= 120092 || (c < 120138
                ? (c < 120128
                  ? (c < 120123
                    ? (c >= 120094 && c <= 120121)
                    : c <= 120126)
                  : (c <= 120132 || c == 120134))
                : (c <= 120144 || (c < 120514
                  ? (c < 120488
                    ? (c >= 120146 && c <= 120485)
                    : c <= 120512)
                  : (c <= 120538 || (c >= 120540 && c <= 120570)))))))
            : (c <= 120596 || (c < 123191
              ? (c < 120714
                ? (c < 120656
                  ? (c < 120630
                    ? (c >= 120598 && c <= 120628)
                    : c <= 120654)
                  : (c <= 120686 || (c >= 120688 && c <= 120712)))
                : (c <= 120744 || (c < 122624
                  ? (c < 120772
                    ? (c >= 120746 && c <= 120770)
                    : c <= 120779)
                  : (c <= 122654 || (c >= 123136 && c <= 123180)))))
              : (c <= 123197 || (c < 124904
                ? (c < 123584
                  ? (c < 123536
                    ? c == 123214
                    : c <= 123565)
                  : (c <= 123627 || (c >= 124896 && c <= 124902)))
                : (c <= 124907 || (c < 124928
                  ? (c < 124912
                    ? (c >= 124909 && c <= 124910)
                    : c <= 124926)
                  : (c <= 125124 || (c >= 125184 && c <= 125251)))))))))
          : (c <= 125259 || (c < 126559
            ? (c < 126535
              ? (c < 126505
                ? (c < 126497
                  ? (c < 126469
                    ? (c >= 126464 && c <= 126467)
                    : c <= 126495)
                  : (c <= 126498 || (c < 126503
                    ? c == 126500
                    : c <= 126503)))
                : (c <= 126514 || (c < 126523
                  ? (c < 126521
                    ? (c >= 126516 && c <= 126519)
                    : c <= 126521)
                  : (c <= 126523 || c == 126530))))
              : (c <= 126535 || (c < 126548
                ? (c < 126541
                  ? (c < 126539
                    ? c == 126537
                    : c <= 126539)
                  : (c <= 126543 || (c >= 126545 && c <= 126546)))
                : (c <= 126548 || (c < 126555
                  ? (c < 126553
                    ? c == 126551
                    : c <= 126553)
                  : (c <= 126555 || c == 126557))))))
            : (c <= 126559 || (c < 126625
              ? (c < 126580
                ? (c < 126567
                  ? (c < 126564
                    ? (c >= 126561 && c <= 126562)
                    : c <= 126564)
                  : (c <= 126570 || (c >= 126572 && c <= 126578)))
                : (c <= 126583 || (c < 126592
                  ? (c < 126590
                    ? (c >= 126585 && c <= 126588)
                    : c <= 126590)
                  : (c <= 126601 || (c >= 126603 && c <= 126619)))))
              : (c <= 126627 || (c < 177984
                ? (c < 131072
                  ? (c < 126635
                    ? (c >= 126629 && c <= 126633)
                    : c <= 126651)
                  : (c <= 173791 || (c >= 173824 && c <= 177976)))
                : (c <= 178205 || (c < 194560
                  ? (c < 183984
                    ? (c >= 178208 && c <= 183969)
                    : c <= 191456)
                  : (c <= 195101 || (c >= 196608 && c <= 201546)))))))))))))))));
}

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(28);
      if (lookahead == '"') ADVANCE(61);
      if (lookahead == '#') ADVANCE(53);
      if (lookahead == '&') ADVANCE(51);
      if (lookahead == '(') ADVANCE(39);
      if (lookahead == ')') ADVANCE(44);
      if (lookahead == '*') ADVANCE(54);
      if (lookahead == '+') ADVANCE(56);
      if (lookahead == ',') ADVANCE(37);
      if (lookahead == '-') ADVANCE(5);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == '/') ADVANCE(10);
      if (lookahead == ':') ADVANCE(13);
      if (lookahead == '<') ADVANCE(36);
      if (lookahead == '=') ADVANCE(32);
      if (lookahead == '>') ADVANCE(38);
      if (lookahead == '?') ADVANCE(57);
      if (lookahead == '\\') ADVANCE(21);
      if (lookahead == 'r') ADVANCE(63);
      if (lookahead == '{') ADVANCE(30);
      if (lookahead == '|') ADVANCE(45);
      if (lookahead == '}') ADVANCE(31);
      if (lookahead == '~') ADVANCE(52);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(27)
      if (sym_identifier_character_set_1(lookahead)) ADVANCE(64);
      END_STATE();
    case 1:
      if (lookahead == '"') ADVANCE(61);
      if (lookahead == '(') ADVANCE(39);
      if (lookahead == '+') ADVANCE(12);
      if (lookahead == '/') ADVANCE(10);
      if (lookahead == ':') ADVANCE(13);
      if (lookahead == '<') ADVANCE(35);
      if (lookahead == '=') ADVANCE(32);
      if (lookahead == '\\') ADVANCE(21);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(4)
      END_STATE();
    case 2:
      if (lookahead == '"') ADVANCE(60);
      if (lookahead == '#') ADVANCE(53);
      if (lookahead == '&') ADVANCE(51);
      if (lookahead == '(') ADVANCE(39);
      if (lookahead == ')') ADVANCE(44);
      if (lookahead == '*') ADVANCE(54);
      if (lookahead == '+') ADVANCE(55);
      if (lookahead == ',') ADVANCE(37);
      if (lookahead == '-') ADVANCE(5);
      if (lookahead == '.') ADVANCE(9);
      if (lookahead == '/') ADVANCE(10);
      if (lookahead == '<') ADVANCE(35);
      if (lookahead == '>') ADVANCE(38);
      if (lookahead == '?') ADVANCE(57);
      if (lookahead == 'r') ADVANCE(63);
      if (lookahead == '|') ADVANCE(45);
      if (lookahead == '}') ADVANCE(31);
      if (lookahead == '~') ADVANCE(52);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(2)
      if (sym_identifier_character_set_1(lookahead)) ADVANCE(64);
      END_STATE();
    case 3:
      if (lookahead == '"') ADVANCE(60);
      if (lookahead == '#') ADVANCE(53);
      if (lookahead == '&') ADVANCE(51);
      if (lookahead == '(') ADVANCE(39);
      if (lookahead == ')') ADVANCE(44);
      if (lookahead == '*') ADVANCE(54);
      if (lookahead == '+') ADVANCE(55);
      if (lookahead == ',') ADVANCE(37);
      if (lookahead == '-') ADVANCE(5);
      if (lookahead == '.') ADVANCE(8);
      if (lookahead == '/') ADVANCE(10);
      if (lookahead == '<') ADVANCE(11);
      if (lookahead == '>') ADVANCE(38);
      if (lookahead == '?') ADVANCE(57);
      if (lookahead == 'r') ADVANCE(63);
      if (lookahead == '{') ADVANCE(30);
      if (lookahead == '|') ADVANCE(45);
      if (lookahead == '}') ADVANCE(31);
      if (lookahead == '~') ADVANCE(52);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(3)
      if (sym_identifier_character_set_1(lookahead)) ADVANCE(64);
      END_STATE();
    case 4:
      if (lookahead == '(') ADVANCE(39);
      if (lookahead == '+') ADVANCE(12);
      if (lookahead == '/') ADVANCE(10);
      if (lookahead == ':') ADVANCE(13);
      if (lookahead == '<') ADVANCE(35);
      if (lookahead == '=') ADVANCE(32);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(4)
      END_STATE();
    case 5:
      if (lookahead == '-') ADVANCE(47);
      END_STATE();
    case 6:
      if (lookahead == '.') ADVANCE(59);
      END_STATE();
    case 7:
      if (lookahead == '.') ADVANCE(46);
      END_STATE();
    case 8:
      if (lookahead == '.') ADVANCE(58);
      END_STATE();
    case 9:
      if (lookahead == '.') ADVANCE(7);
      END_STATE();
    case 10:
      if (lookahead == '/') ADVANCE(65);
      END_STATE();
    case 11:
      if (lookahead == ':') ADVANCE(29);
      END_STATE();
    case 12:
      if (lookahead == '=') ADVANCE(34);
      END_STATE();
    case 13:
      if (lookahead == '=') ADVANCE(33);
      END_STATE();
    case 14:
      if (lookahead == '{') ADVANCE(24);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(23);
      END_STATE();
    case 15:
      if (lookahead == '}') ADVANCE(62);
      END_STATE();
    case 16:
      if (lookahead == '}') ADVANCE(62);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(15);
      END_STATE();
    case 17:
      if (lookahead == '}') ADVANCE(62);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(16);
      END_STATE();
    case 18:
      if (lookahead == '}') ADVANCE(62);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(17);
      END_STATE();
    case 19:
      if (lookahead == '}') ADVANCE(62);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(18);
      END_STATE();
    case 20:
      if (lookahead == '}') ADVANCE(62);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(19);
      END_STATE();
    case 21:
      if (lookahead == '"' ||
          lookahead == '\'' ||
          lookahead == '\\' ||
          lookahead == 'b' ||
          lookahead == 'n' ||
          lookahead == 'r' ||
          lookahead == 't') ADVANCE(62);
      if (lookahead == 'u') ADVANCE(14);
      if (lookahead == 'x') ADVANCE(25);
      END_STATE();
    case 22:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(62);
      END_STATE();
    case 23:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(25);
      END_STATE();
    case 24:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(20);
      END_STATE();
    case 25:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(22);
      END_STATE();
    case 26:
      if (sym_identifier_character_set_1(lookahead)) ADVANCE(64);
      END_STATE();
    case 27:
      if (eof) ADVANCE(28);
      if (lookahead == '"') ADVANCE(60);
      if (lookahead == '#') ADVANCE(53);
      if (lookahead == '&') ADVANCE(51);
      if (lookahead == '(') ADVANCE(39);
      if (lookahead == ')') ADVANCE(44);
      if (lookahead == '*') ADVANCE(54);
      if (lookahead == '+') ADVANCE(56);
      if (lookahead == ',') ADVANCE(37);
      if (lookahead == '-') ADVANCE(5);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == '/') ADVANCE(10);
      if (lookahead == ':') ADVANCE(13);
      if (lookahead == '<') ADVANCE(36);
      if (lookahead == '=') ADVANCE(32);
      if (lookahead == '>') ADVANCE(38);
      if (lookahead == '?') ADVANCE(57);
      if (lookahead == 'r') ADVANCE(63);
      if (lookahead == '{') ADVANCE(30);
      if (lookahead == '|') ADVANCE(45);
      if (lookahead == '}') ADVANCE(31);
      if (lookahead == '~') ADVANCE(52);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(27)
      if (sym_identifier_character_set_1(lookahead)) ADVANCE(64);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(anon_sym_LT_COLON);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(anon_sym_COLON_EQ);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(anon_sym_PLUS_EQ);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(anon_sym_LT);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == ':') ADVANCE(29);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(anon_sym_GT);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(aux_sym_rule_descr_token1);
      if (lookahead == ')') ADVANCE(65);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(40);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(aux_sym_rule_descr_token1);
      if (lookahead == '/') ADVANCE(42);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(41);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != ')') ADVANCE(43);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(aux_sym_rule_descr_token1);
      if (lookahead == '/') ADVANCE(40);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != ')') ADVANCE(43);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(aux_sym_rule_descr_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != ')') ADVANCE(43);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(anon_sym_PIPE);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(anon_sym_DOT_DOT_DOT);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(anon_sym_DASH_DASH);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(aux_sym_case_name_token1);
      if (lookahead == '/') ADVANCE(49);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(48);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(50);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(aux_sym_case_name_token1);
      if (lookahead == '/') ADVANCE(50);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(50);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(aux_sym_case_name_token1);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(50);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(anon_sym_AMP);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(anon_sym_TILDE);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(anon_sym_POUND);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(anon_sym_STAR);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(anon_sym_PLUS);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(anon_sym_PLUS);
      if (lookahead == '=') ADVANCE(34);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(anon_sym_QMARK);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(anon_sym_DOT_DOT);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(anon_sym_DOT_DOT);
      if (lookahead == '.') ADVANCE(46);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(anon_sym_DQUOTE2);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(sym_escape_char);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '#') ADVANCE(26);
      if (sym_identifier_character_set_2(lookahead)) ADVANCE(64);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(sym_identifier);
      if (sym_identifier_character_set_2(lookahead)) ADVANCE(64);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(sym_singleline_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(65);
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
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0, .external_lex_state = 1},
  [1] = {.lex_state = 0, .external_lex_state = 2},
  [2] = {.lex_state = 2, .external_lex_state = 2},
  [3] = {.lex_state = 2, .external_lex_state = 2},
  [4] = {.lex_state = 2, .external_lex_state = 2},
  [5] = {.lex_state = 2, .external_lex_state = 2},
  [6] = {.lex_state = 2, .external_lex_state = 2},
  [7] = {.lex_state = 2, .external_lex_state = 2},
  [8] = {.lex_state = 2, .external_lex_state = 2},
  [9] = {.lex_state = 2, .external_lex_state = 2},
  [10] = {.lex_state = 2, .external_lex_state = 2},
  [11] = {.lex_state = 2, .external_lex_state = 2},
  [12] = {.lex_state = 2, .external_lex_state = 2},
  [13] = {.lex_state = 2, .external_lex_state = 2},
  [14] = {.lex_state = 2, .external_lex_state = 2},
  [15] = {.lex_state = 3, .external_lex_state = 2},
  [16] = {.lex_state = 2, .external_lex_state = 2},
  [17] = {.lex_state = 2, .external_lex_state = 2},
  [18] = {.lex_state = 2, .external_lex_state = 2},
  [19] = {.lex_state = 2, .external_lex_state = 2},
  [20] = {.lex_state = 2, .external_lex_state = 2},
  [21] = {.lex_state = 2, .external_lex_state = 2},
  [22] = {.lex_state = 2, .external_lex_state = 2},
  [23] = {.lex_state = 2, .external_lex_state = 2},
  [24] = {.lex_state = 2, .external_lex_state = 2},
  [25] = {.lex_state = 2, .external_lex_state = 2},
  [26] = {.lex_state = 2, .external_lex_state = 2},
  [27] = {.lex_state = 2, .external_lex_state = 2},
  [28] = {.lex_state = 2, .external_lex_state = 2},
  [29] = {.lex_state = 2, .external_lex_state = 2},
  [30] = {.lex_state = 2, .external_lex_state = 2},
  [31] = {.lex_state = 2, .external_lex_state = 2},
  [32] = {.lex_state = 2, .external_lex_state = 2},
  [33] = {.lex_state = 2, .external_lex_state = 2},
  [34] = {.lex_state = 2, .external_lex_state = 2},
  [35] = {.lex_state = 2, .external_lex_state = 2},
  [36] = {.lex_state = 2, .external_lex_state = 2},
  [37] = {.lex_state = 2, .external_lex_state = 2},
  [38] = {.lex_state = 2, .external_lex_state = 2},
  [39] = {.lex_state = 2, .external_lex_state = 2},
  [40] = {.lex_state = 2, .external_lex_state = 2},
  [41] = {.lex_state = 1, .external_lex_state = 2},
  [42] = {.lex_state = 1, .external_lex_state = 1},
  [43] = {.lex_state = 0, .external_lex_state = 2},
  [44] = {.lex_state = 0, .external_lex_state = 2},
  [45] = {.lex_state = 1, .external_lex_state = 2},
  [46] = {.lex_state = 1, .external_lex_state = 1},
  [47] = {.lex_state = 1, .external_lex_state = 1},
  [48] = {.lex_state = 0, .external_lex_state = 2},
  [49] = {.lex_state = 0, .external_lex_state = 2},
  [50] = {.lex_state = 1, .external_lex_state = 2},
  [51] = {.lex_state = 0, .external_lex_state = 2},
  [52] = {.lex_state = 0, .external_lex_state = 2},
  [53] = {.lex_state = 1, .external_lex_state = 2},
  [54] = {.lex_state = 0, .external_lex_state = 2},
  [55] = {.lex_state = 0, .external_lex_state = 2},
  [56] = {.lex_state = 0, .external_lex_state = 2},
  [57] = {.lex_state = 0, .external_lex_state = 2},
  [58] = {.lex_state = 3, .external_lex_state = 2},
  [59] = {.lex_state = 0, .external_lex_state = 2},
  [60] = {.lex_state = 0, .external_lex_state = 2},
  [61] = {.lex_state = 0, .external_lex_state = 2},
  [62] = {.lex_state = 0, .external_lex_state = 2},
  [63] = {.lex_state = 1, .external_lex_state = 2},
  [64] = {.lex_state = 0, .external_lex_state = 2},
  [65] = {.lex_state = 0, .external_lex_state = 2},
  [66] = {.lex_state = 0, .external_lex_state = 2},
  [67] = {.lex_state = 0, .external_lex_state = 1},
  [68] = {.lex_state = 0, .external_lex_state = 2},
  [69] = {.lex_state = 0, .external_lex_state = 2},
  [70] = {.lex_state = 0, .external_lex_state = 2},
  [71] = {.lex_state = 0, .external_lex_state = 2},
  [72] = {.lex_state = 0, .external_lex_state = 2},
  [73] = {.lex_state = 1, .external_lex_state = 1},
  [74] = {.lex_state = 0, .external_lex_state = 2},
  [75] = {.lex_state = 0, .external_lex_state = 2},
  [76] = {.lex_state = 0, .external_lex_state = 2},
  [77] = {.lex_state = 0, .external_lex_state = 2},
  [78] = {.lex_state = 0, .external_lex_state = 2},
  [79] = {.lex_state = 0, .external_lex_state = 2},
  [80] = {.lex_state = 0, .external_lex_state = 2},
  [81] = {.lex_state = 0, .external_lex_state = 2},
  [82] = {.lex_state = 0, .external_lex_state = 2},
  [83] = {.lex_state = 0, .external_lex_state = 2},
  [84] = {.lex_state = 0, .external_lex_state = 2},
  [85] = {.lex_state = 0, .external_lex_state = 2},
  [86] = {.lex_state = 0, .external_lex_state = 2},
  [87] = {.lex_state = 2, .external_lex_state = 2},
  [88] = {.lex_state = 0, .external_lex_state = 2},
  [89] = {.lex_state = 0, .external_lex_state = 2},
  [90] = {.lex_state = 0, .external_lex_state = 2},
  [91] = {.lex_state = 0, .external_lex_state = 2},
  [92] = {.lex_state = 0, .external_lex_state = 2},
  [93] = {.lex_state = 0, .external_lex_state = 2},
  [94] = {.lex_state = 0, .external_lex_state = 2},
  [95] = {.lex_state = 0, .external_lex_state = 2},
  [96] = {.lex_state = 0, .external_lex_state = 2},
  [97] = {.lex_state = 0, .external_lex_state = 2},
  [98] = {.lex_state = 0, .external_lex_state = 2},
  [99] = {.lex_state = 48, .external_lex_state = 2},
  [100] = {.lex_state = 41, .external_lex_state = 2},
  [101] = {.lex_state = 0, .external_lex_state = 2},
  [102] = {.lex_state = 0, .external_lex_state = 2},
  [103] = {.lex_state = 3, .external_lex_state = 2},
  [104] = {.lex_state = 0, .external_lex_state = 2},
  [105] = {.lex_state = 0, .external_lex_state = 2},
  [106] = {.lex_state = 0, .external_lex_state = 2},
  [107] = {.lex_state = 1, .external_lex_state = 2},
  [108] = {.lex_state = 0, .external_lex_state = 2},
  [109] = {.lex_state = 0, .external_lex_state = 2},
  [110] = {.lex_state = 0, .external_lex_state = 2},
  [111] = {.lex_state = 0, .external_lex_state = 2},
};

enum {
  ts_external_token__unicode_char = 0,
  ts_external_token_multiline_comment = 1,
};

static const TSSymbol ts_external_scanner_symbol_map[EXTERNAL_TOKEN_COUNT] = {
  [ts_external_token__unicode_char] = sym__unicode_char,
  [ts_external_token_multiline_comment] = sym_multiline_comment,
};

static const bool ts_external_scanner_states[3][EXTERNAL_TOKEN_COUNT] = {
  [1] = {
    [ts_external_token__unicode_char] = true,
    [ts_external_token_multiline_comment] = true,
  },
  [2] = {
    [ts_external_token_multiline_comment] = true,
  },
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [anon_sym_LT_COLON] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_COLON_EQ] = ACTIONS(1),
    [anon_sym_PLUS_EQ] = ACTIONS(1),
    [anon_sym_LT] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_GT] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_PIPE] = ACTIONS(1),
    [anon_sym_DOT_DOT_DOT] = ACTIONS(1),
    [anon_sym_DASH_DASH] = ACTIONS(1),
    [anon_sym_AMP] = ACTIONS(1),
    [anon_sym_TILDE] = ACTIONS(1),
    [anon_sym_POUND] = ACTIONS(1),
    [anon_sym_STAR] = ACTIONS(1),
    [anon_sym_PLUS] = ACTIONS(1),
    [anon_sym_QMARK] = ACTIONS(1),
    [anon_sym_DOT_DOT] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [anon_sym_DQUOTE2] = ACTIONS(1),
    [sym_escape_char] = ACTIONS(1),
    [sym_singleline_comment] = ACTIONS(3),
    [sym__unicode_char] = ACTIONS(1),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [1] = {
    [sym_source_file] = STATE(111),
    [sym_grammar] = STATE(51),
    [aux_sym_source_file_repeat1] = STATE(51),
    [ts_builtin_sym_end] = ACTIONS(5),
    [sym_identifier] = ACTIONS(7),
    [sym_singleline_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 17,
    ACTIONS(9), 1,
      sym_identifier,
    ACTIONS(12), 1,
      anon_sym_RBRACE,
    ACTIONS(14), 1,
      anon_sym_LPAREN,
    ACTIONS(16), 1,
      anon_sym_PIPE,
    ACTIONS(18), 1,
      anon_sym_DOT_DOT_DOT,
    ACTIONS(20), 1,
      anon_sym_DASH_DASH,
    ACTIONS(24), 1,
      anon_sym_POUND,
    ACTIONS(26), 1,
      anon_sym_DQUOTE,
    STATE(44), 1,
      sym_seq,
    STATE(59), 1,
      sym_override_top_level_term,
    STATE(78), 1,
      sym_case_name,
    STATE(94), 1,
      sym_override_rule_body,
    STATE(103), 1,
      sym_one_char_terminal,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(22), 2,
      anon_sym_AMP,
      anon_sym_TILDE,
    STATE(23), 2,
      sym_term,
      aux_sym_seq_repeat1,
    STATE(29), 3,
      sym__base,
      sym_alt,
      sym_terminal_string,
  [57] = 17,
    ACTIONS(14), 1,
      anon_sym_LPAREN,
    ACTIONS(16), 1,
      anon_sym_PIPE,
    ACTIONS(18), 1,
      anon_sym_DOT_DOT_DOT,
    ACTIONS(20), 1,
      anon_sym_DASH_DASH,
    ACTIONS(24), 1,
      anon_sym_POUND,
    ACTIONS(26), 1,
      anon_sym_DQUOTE,
    ACTIONS(28), 1,
      sym_identifier,
    ACTIONS(31), 1,
      anon_sym_RBRACE,
    STATE(44), 1,
      sym_seq,
    STATE(59), 1,
      sym_override_top_level_term,
    STATE(78), 1,
      sym_case_name,
    STATE(90), 1,
      sym_override_rule_body,
    STATE(103), 1,
      sym_one_char_terminal,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(22), 2,
      anon_sym_AMP,
      anon_sym_TILDE,
    STATE(23), 2,
      sym_term,
      aux_sym_seq_repeat1,
    STATE(29), 3,
      sym__base,
      sym_alt,
      sym_terminal_string,
  [114] = 16,
    ACTIONS(14), 1,
      anon_sym_LPAREN,
    ACTIONS(20), 1,
      anon_sym_DASH_DASH,
    ACTIONS(24), 1,
      anon_sym_POUND,
    ACTIONS(26), 1,
      anon_sym_DQUOTE,
    ACTIONS(28), 1,
      sym_identifier,
    ACTIONS(31), 1,
      anon_sym_RBRACE,
    ACTIONS(33), 1,
      anon_sym_PIPE,
    STATE(43), 1,
      sym_seq,
    STATE(49), 1,
      sym_top_level_term,
    STATE(76), 1,
      sym_case_name,
    STATE(90), 1,
      sym_rule_body,
    STATE(103), 1,
      sym_one_char_terminal,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(22), 2,
      anon_sym_AMP,
      anon_sym_TILDE,
    STATE(23), 2,
      sym_term,
      aux_sym_seq_repeat1,
    STATE(29), 3,
      sym__base,
      sym_alt,
      sym_terminal_string,
  [168] = 16,
    ACTIONS(14), 1,
      anon_sym_LPAREN,
    ACTIONS(20), 1,
      anon_sym_DASH_DASH,
    ACTIONS(24), 1,
      anon_sym_POUND,
    ACTIONS(26), 1,
      anon_sym_DQUOTE,
    ACTIONS(33), 1,
      anon_sym_PIPE,
    ACTIONS(35), 1,
      sym_identifier,
    ACTIONS(38), 1,
      anon_sym_RBRACE,
    STATE(43), 1,
      sym_seq,
    STATE(49), 1,
      sym_top_level_term,
    STATE(76), 1,
      sym_case_name,
    STATE(92), 1,
      sym_rule_body,
    STATE(103), 1,
      sym_one_char_terminal,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(22), 2,
      anon_sym_AMP,
      anon_sym_TILDE,
    STATE(23), 2,
      sym_term,
      aux_sym_seq_repeat1,
    STATE(29), 3,
      sym__base,
      sym_alt,
      sym_terminal_string,
  [222] = 16,
    ACTIONS(14), 1,
      anon_sym_LPAREN,
    ACTIONS(20), 1,
      anon_sym_DASH_DASH,
    ACTIONS(24), 1,
      anon_sym_POUND,
    ACTIONS(26), 1,
      anon_sym_DQUOTE,
    ACTIONS(33), 1,
      anon_sym_PIPE,
    ACTIONS(40), 1,
      sym_identifier,
    ACTIONS(43), 1,
      anon_sym_RBRACE,
    STATE(43), 1,
      sym_seq,
    STATE(49), 1,
      sym_top_level_term,
    STATE(76), 1,
      sym_case_name,
    STATE(86), 1,
      sym_rule_body,
    STATE(103), 1,
      sym_one_char_terminal,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(22), 2,
      anon_sym_AMP,
      anon_sym_TILDE,
    STATE(23), 2,
      sym_term,
      aux_sym_seq_repeat1,
    STATE(29), 3,
      sym__base,
      sym_alt,
      sym_terminal_string,
  [276] = 16,
    ACTIONS(9), 1,
      sym_identifier,
    ACTIONS(12), 1,
      anon_sym_RBRACE,
    ACTIONS(14), 1,
      anon_sym_LPAREN,
    ACTIONS(20), 1,
      anon_sym_DASH_DASH,
    ACTIONS(24), 1,
      anon_sym_POUND,
    ACTIONS(26), 1,
      anon_sym_DQUOTE,
    ACTIONS(33), 1,
      anon_sym_PIPE,
    STATE(43), 1,
      sym_seq,
    STATE(49), 1,
      sym_top_level_term,
    STATE(76), 1,
      sym_case_name,
    STATE(94), 1,
      sym_rule_body,
    STATE(103), 1,
      sym_one_char_terminal,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(22), 2,
      anon_sym_AMP,
      anon_sym_TILDE,
    STATE(23), 2,
      sym_term,
      aux_sym_seq_repeat1,
    STATE(29), 3,
      sym__base,
      sym_alt,
      sym_terminal_string,
  [330] = 10,
    ACTIONS(45), 1,
      sym_identifier,
    ACTIONS(50), 1,
      anon_sym_LPAREN,
    ACTIONS(56), 1,
      anon_sym_POUND,
    ACTIONS(59), 1,
      anon_sym_DQUOTE,
    STATE(103), 1,
      sym_one_char_terminal,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(53), 2,
      anon_sym_AMP,
      anon_sym_TILDE,
    STATE(8), 2,
      sym_term,
      aux_sym_seq_repeat1,
    STATE(29), 3,
      sym__base,
      sym_alt,
      sym_terminal_string,
    ACTIONS(48), 6,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_GT,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_DASH_DASH,
  [371] = 14,
    ACTIONS(14), 1,
      anon_sym_LPAREN,
    ACTIONS(18), 1,
      anon_sym_DOT_DOT_DOT,
    ACTIONS(20), 1,
      anon_sym_DASH_DASH,
    ACTIONS(24), 1,
      anon_sym_POUND,
    ACTIONS(26), 1,
      anon_sym_DQUOTE,
    ACTIONS(62), 1,
      sym_identifier,
    STATE(44), 1,
      sym_seq,
    STATE(65), 1,
      sym_override_top_level_term,
    STATE(78), 1,
      sym_case_name,
    STATE(103), 1,
      sym_one_char_terminal,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(22), 2,
      anon_sym_AMP,
      anon_sym_TILDE,
    STATE(23), 2,
      sym_term,
      aux_sym_seq_repeat1,
    STATE(29), 3,
      sym__base,
      sym_alt,
      sym_terminal_string,
  [419] = 4,
    ACTIONS(66), 1,
      anon_sym_LT,
    STATE(25), 1,
      sym_params,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(64), 15,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_GT,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_DASH_DASH,
      anon_sym_AMP,
      anon_sym_TILDE,
      anon_sym_POUND,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_QMARK,
      anon_sym_DQUOTE,
      sym_identifier,
  [447] = 14,
    ACTIONS(14), 1,
      anon_sym_LPAREN,
    ACTIONS(18), 1,
      anon_sym_DOT_DOT_DOT,
    ACTIONS(20), 1,
      anon_sym_DASH_DASH,
    ACTIONS(24), 1,
      anon_sym_POUND,
    ACTIONS(26), 1,
      anon_sym_DQUOTE,
    ACTIONS(62), 1,
      sym_identifier,
    STATE(44), 1,
      sym_seq,
    STATE(78), 1,
      sym_case_name,
    STATE(82), 1,
      sym_override_top_level_term,
    STATE(103), 1,
      sym_one_char_terminal,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(22), 2,
      anon_sym_AMP,
      anon_sym_TILDE,
    STATE(23), 2,
      sym_term,
      aux_sym_seq_repeat1,
    STATE(29), 3,
      sym__base,
      sym_alt,
      sym_terminal_string,
  [495] = 10,
    ACTIONS(14), 1,
      anon_sym_LPAREN,
    ACTIONS(24), 1,
      anon_sym_POUND,
    ACTIONS(26), 1,
      anon_sym_DQUOTE,
    ACTIONS(62), 1,
      sym_identifier,
    STATE(103), 1,
      sym_one_char_terminal,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(22), 2,
      anon_sym_AMP,
      anon_sym_TILDE,
    STATE(8), 2,
      sym_term,
      aux_sym_seq_repeat1,
    STATE(29), 3,
      sym__base,
      sym_alt,
      sym_terminal_string,
    ACTIONS(68), 4,
      anon_sym_COMMA,
      anon_sym_GT,
      anon_sym_RPAREN,
      anon_sym_PIPE,
  [534] = 13,
    ACTIONS(14), 1,
      anon_sym_LPAREN,
    ACTIONS(20), 1,
      anon_sym_DASH_DASH,
    ACTIONS(24), 1,
      anon_sym_POUND,
    ACTIONS(26), 1,
      anon_sym_DQUOTE,
    ACTIONS(62), 1,
      sym_identifier,
    STATE(43), 1,
      sym_seq,
    STATE(76), 1,
      sym_case_name,
    STATE(81), 1,
      sym_top_level_term,
    STATE(103), 1,
      sym_one_char_terminal,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(22), 2,
      anon_sym_AMP,
      anon_sym_TILDE,
    STATE(23), 2,
      sym_term,
      aux_sym_seq_repeat1,
    STATE(29), 3,
      sym__base,
      sym_alt,
      sym_terminal_string,
  [579] = 13,
    ACTIONS(14), 1,
      anon_sym_LPAREN,
    ACTIONS(20), 1,
      anon_sym_DASH_DASH,
    ACTIONS(24), 1,
      anon_sym_POUND,
    ACTIONS(26), 1,
      anon_sym_DQUOTE,
    ACTIONS(62), 1,
      sym_identifier,
    STATE(43), 1,
      sym_seq,
    STATE(55), 1,
      sym_top_level_term,
    STATE(76), 1,
      sym_case_name,
    STATE(103), 1,
      sym_one_char_terminal,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(22), 2,
      anon_sym_AMP,
      anon_sym_TILDE,
    STATE(23), 2,
      sym_term,
      aux_sym_seq_repeat1,
    STATE(29), 3,
      sym__base,
      sym_alt,
      sym_terminal_string,
  [624] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(70), 16,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_GT,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_DASH_DASH,
      anon_sym_AMP,
      anon_sym_TILDE,
      anon_sym_POUND,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_QMARK,
      anon_sym_DOT_DOT,
      anon_sym_DQUOTE,
      sym_identifier,
  [647] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(72), 15,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_GT,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_DASH_DASH,
      anon_sym_AMP,
      anon_sym_TILDE,
      anon_sym_POUND,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_QMARK,
      anon_sym_DQUOTE,
      sym_identifier,
  [669] = 3,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(76), 3,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_QMARK,
    ACTIONS(74), 12,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_GT,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_DASH_DASH,
      anon_sym_AMP,
      anon_sym_TILDE,
      anon_sym_POUND,
      anon_sym_DQUOTE,
      sym_identifier,
  [693] = 3,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(80), 3,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_QMARK,
    ACTIONS(78), 12,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_GT,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_DASH_DASH,
      anon_sym_AMP,
      anon_sym_TILDE,
      anon_sym_POUND,
      anon_sym_DQUOTE,
      sym_identifier,
  [717] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(82), 15,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_GT,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_DASH_DASH,
      anon_sym_AMP,
      anon_sym_TILDE,
      anon_sym_POUND,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_QMARK,
      anon_sym_DQUOTE,
      sym_identifier,
  [739] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(84), 15,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_GT,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_DASH_DASH,
      anon_sym_AMP,
      anon_sym_TILDE,
      anon_sym_POUND,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_QMARK,
      anon_sym_DQUOTE,
      sym_identifier,
  [761] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(86), 15,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_GT,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_DASH_DASH,
      anon_sym_AMP,
      anon_sym_TILDE,
      anon_sym_POUND,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_QMARK,
      anon_sym_DQUOTE,
      sym_identifier,
  [783] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(88), 15,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_GT,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_DASH_DASH,
      anon_sym_AMP,
      anon_sym_TILDE,
      anon_sym_POUND,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_QMARK,
      anon_sym_DQUOTE,
      sym_identifier,
  [805] = 10,
    ACTIONS(14), 1,
      anon_sym_LPAREN,
    ACTIONS(24), 1,
      anon_sym_POUND,
    ACTIONS(26), 1,
      anon_sym_DQUOTE,
    ACTIONS(90), 1,
      sym_identifier,
    STATE(103), 1,
      sym_one_char_terminal,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(22), 2,
      anon_sym_AMP,
      anon_sym_TILDE,
    STATE(8), 2,
      sym_term,
      aux_sym_seq_repeat1,
    ACTIONS(68), 3,
      anon_sym_RBRACE,
      anon_sym_PIPE,
      anon_sym_DASH_DASH,
    STATE(29), 3,
      sym__base,
      sym_alt,
      sym_terminal_string,
  [843] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(93), 15,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_GT,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_DASH_DASH,
      anon_sym_AMP,
      anon_sym_TILDE,
      anon_sym_POUND,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_QMARK,
      anon_sym_DQUOTE,
      sym_identifier,
  [865] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(95), 15,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_GT,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_DASH_DASH,
      anon_sym_AMP,
      anon_sym_TILDE,
      anon_sym_POUND,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_QMARK,
      anon_sym_DQUOTE,
      sym_identifier,
  [887] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(97), 15,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_GT,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_DASH_DASH,
      anon_sym_AMP,
      anon_sym_TILDE,
      anon_sym_POUND,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_QMARK,
      anon_sym_DQUOTE,
      sym_identifier,
  [909] = 3,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(101), 3,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_QMARK,
    ACTIONS(99), 12,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_GT,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_DASH_DASH,
      anon_sym_AMP,
      anon_sym_TILDE,
      anon_sym_POUND,
      anon_sym_DQUOTE,
      sym_identifier,
  [933] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(103), 15,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_GT,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_DASH_DASH,
      anon_sym_AMP,
      anon_sym_TILDE,
      anon_sym_POUND,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_QMARK,
      anon_sym_DQUOTE,
      sym_identifier,
  [955] = 3,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(107), 3,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_QMARK,
    ACTIONS(105), 12,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_GT,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_DASH_DASH,
      anon_sym_AMP,
      anon_sym_TILDE,
      anon_sym_POUND,
      anon_sym_DQUOTE,
      sym_identifier,
  [979] = 11,
    ACTIONS(14), 1,
      anon_sym_LPAREN,
    ACTIONS(24), 1,
      anon_sym_POUND,
    ACTIONS(26), 1,
      anon_sym_DQUOTE,
    ACTIONS(62), 1,
      sym_identifier,
    ACTIONS(109), 1,
      anon_sym_GT,
    STATE(80), 1,
      sym_seq,
    STATE(103), 1,
      sym_one_char_terminal,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(22), 2,
      anon_sym_AMP,
      anon_sym_TILDE,
    STATE(12), 2,
      sym_term,
      aux_sym_seq_repeat1,
    STATE(29), 3,
      sym__base,
      sym_alt,
      sym_terminal_string,
  [1018] = 10,
    ACTIONS(14), 1,
      anon_sym_LPAREN,
    ACTIONS(24), 1,
      anon_sym_POUND,
    ACTIONS(26), 1,
      anon_sym_DQUOTE,
    ACTIONS(62), 1,
      sym_identifier,
    STATE(85), 1,
      sym_seq,
    STATE(103), 1,
      sym_one_char_terminal,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(22), 2,
      anon_sym_AMP,
      anon_sym_TILDE,
    STATE(12), 2,
      sym_term,
      aux_sym_seq_repeat1,
    STATE(29), 3,
      sym__base,
      sym_alt,
      sym_terminal_string,
  [1054] = 10,
    ACTIONS(14), 1,
      anon_sym_LPAREN,
    ACTIONS(24), 1,
      anon_sym_POUND,
    ACTIONS(26), 1,
      anon_sym_DQUOTE,
    ACTIONS(62), 1,
      sym_identifier,
    STATE(84), 1,
      sym_seq,
    STATE(103), 1,
      sym_one_char_terminal,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(22), 2,
      anon_sym_AMP,
      anon_sym_TILDE,
    STATE(12), 2,
      sym_term,
      aux_sym_seq_repeat1,
    STATE(29), 3,
      sym__base,
      sym_alt,
      sym_terminal_string,
  [1090] = 10,
    ACTIONS(14), 1,
      anon_sym_LPAREN,
    ACTIONS(24), 1,
      anon_sym_POUND,
    ACTIONS(26), 1,
      anon_sym_DQUOTE,
    ACTIONS(62), 1,
      sym_identifier,
    STATE(89), 1,
      sym_seq,
    STATE(103), 1,
      sym_one_char_terminal,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(22), 2,
      anon_sym_AMP,
      anon_sym_TILDE,
    STATE(12), 2,
      sym_term,
      aux_sym_seq_repeat1,
    STATE(29), 3,
      sym__base,
      sym_alt,
      sym_terminal_string,
  [1126] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(111), 12,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_GT,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_DASH_DASH,
      anon_sym_AMP,
      anon_sym_TILDE,
      anon_sym_POUND,
      anon_sym_DQUOTE,
      sym_identifier,
  [1145] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(113), 12,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_GT,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_DASH_DASH,
      anon_sym_AMP,
      anon_sym_TILDE,
      anon_sym_POUND,
      anon_sym_DQUOTE,
      sym_identifier,
  [1164] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(115), 12,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_GT,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_DASH_DASH,
      anon_sym_AMP,
      anon_sym_TILDE,
      anon_sym_POUND,
      anon_sym_DQUOTE,
      sym_identifier,
  [1183] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(117), 12,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_GT,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_DASH_DASH,
      anon_sym_AMP,
      anon_sym_TILDE,
      anon_sym_POUND,
      anon_sym_DQUOTE,
      sym_identifier,
  [1202] = 7,
    ACTIONS(14), 1,
      anon_sym_LPAREN,
    ACTIONS(26), 1,
      anon_sym_DQUOTE,
    ACTIONS(62), 1,
      sym_identifier,
    ACTIONS(119), 1,
      anon_sym_POUND,
    STATE(103), 1,
      sym_one_char_terminal,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    STATE(17), 3,
      sym__base,
      sym_alt,
      sym_terminal_string,
  [1227] = 6,
    ACTIONS(14), 1,
      anon_sym_LPAREN,
    ACTIONS(26), 1,
      anon_sym_DQUOTE,
    ACTIONS(62), 1,
      sym_identifier,
    STATE(103), 1,
      sym_one_char_terminal,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    STATE(27), 3,
      sym__base,
      sym_alt,
      sym_terminal_string,
  [1249] = 6,
    ACTIONS(14), 1,
      anon_sym_LPAREN,
    ACTIONS(26), 1,
      anon_sym_DQUOTE,
    ACTIONS(62), 1,
      sym_identifier,
    STATE(103), 1,
      sym_one_char_terminal,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    STATE(18), 3,
      sym__base,
      sym_alt,
      sym_terminal_string,
  [1271] = 7,
    ACTIONS(123), 1,
      anon_sym_COLON_EQ,
    ACTIONS(125), 1,
      anon_sym_LT,
    ACTIONS(127), 1,
      anon_sym_LPAREN,
    STATE(45), 1,
      sym_formals,
    STATE(104), 1,
      sym_rule_descr,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(121), 2,
      anon_sym_EQ,
      anon_sym_PLUS_EQ,
  [1295] = 4,
    ACTIONS(129), 1,
      anon_sym_DQUOTE2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(131), 2,
      sym__unicode_char,
      sym_escape_char,
    STATE(42), 2,
      sym__terminal_char,
      aux_sym_terminal_string_repeat1,
  [1311] = 4,
    ACTIONS(20), 1,
      anon_sym_DASH_DASH,
    STATE(83), 1,
      sym_case_name,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(134), 3,
      anon_sym_RBRACE,
      anon_sym_PIPE,
      sym_identifier,
  [1327] = 4,
    ACTIONS(20), 1,
      anon_sym_DASH_DASH,
    STATE(68), 1,
      sym_case_name,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(136), 3,
      anon_sym_RBRACE,
      anon_sym_PIPE,
      sym_identifier,
  [1343] = 5,
    ACTIONS(127), 1,
      anon_sym_LPAREN,
    ACTIONS(140), 1,
      anon_sym_COLON_EQ,
    STATE(102), 1,
      sym_rule_descr,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(138), 2,
      anon_sym_EQ,
      anon_sym_PLUS_EQ,
  [1361] = 5,
    ACTIONS(142), 1,
      anon_sym_DQUOTE2,
    STATE(47), 1,
      aux_sym_terminal_string_repeat1,
    STATE(73), 1,
      sym__terminal_char,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(144), 2,
      sym__unicode_char,
      sym_escape_char,
  [1379] = 4,
    ACTIONS(146), 1,
      anon_sym_DQUOTE2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(148), 2,
      sym__unicode_char,
      sym_escape_char,
    STATE(42), 2,
      sym__terminal_char,
      aux_sym_terminal_string_repeat1,
  [1395] = 4,
    ACTIONS(152), 1,
      anon_sym_PIPE,
    STATE(48), 1,
      aux_sym_override_rule_body_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(150), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [1410] = 4,
    ACTIONS(157), 1,
      anon_sym_PIPE,
    STATE(60), 1,
      aux_sym_rule_body_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(155), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [1425] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(159), 4,
      anon_sym_EQ,
      anon_sym_COLON_EQ,
      anon_sym_PLUS_EQ,
      anon_sym_LPAREN,
  [1436] = 4,
    ACTIONS(7), 1,
      sym_identifier,
    ACTIONS(161), 1,
      ts_builtin_sym_end,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    STATE(56), 2,
      sym_grammar,
      aux_sym_source_file_repeat1,
  [1451] = 4,
    ACTIONS(163), 1,
      sym_identifier,
    ACTIONS(165), 1,
      anon_sym_RBRACE,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    STATE(61), 2,
      sym_rule,
      aux_sym_grammar_body_repeat1,
  [1466] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(167), 4,
      anon_sym_EQ,
      anon_sym_COLON_EQ,
      anon_sym_PLUS_EQ,
      anon_sym_LPAREN,
  [1477] = 4,
    ACTIONS(171), 1,
      anon_sym_PIPE,
    STATE(48), 1,
      aux_sym_override_rule_body_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(169), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [1492] = 4,
    ACTIONS(157), 1,
      anon_sym_PIPE,
    STATE(62), 1,
      aux_sym_rule_body_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(173), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [1507] = 4,
    ACTIONS(175), 1,
      ts_builtin_sym_end,
    ACTIONS(177), 1,
      sym_identifier,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    STATE(56), 2,
      sym_grammar,
      aux_sym_source_file_repeat1,
  [1522] = 4,
    ACTIONS(182), 1,
      anon_sym_PIPE,
    STATE(57), 1,
      aux_sym_rule_body_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(180), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [1537] = 5,
    ACTIONS(185), 1,
      anon_sym_LT_COLON,
    ACTIONS(187), 1,
      anon_sym_LBRACE,
    STATE(91), 1,
      sym_super_grammar,
    STATE(97), 1,
      sym_grammar_body,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [1554] = 4,
    ACTIONS(171), 1,
      anon_sym_PIPE,
    STATE(66), 1,
      aux_sym_override_rule_body_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(189), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [1569] = 4,
    ACTIONS(157), 1,
      anon_sym_PIPE,
    STATE(57), 1,
      aux_sym_rule_body_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(173), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [1584] = 4,
    ACTIONS(163), 1,
      sym_identifier,
    ACTIONS(191), 1,
      anon_sym_RBRACE,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    STATE(64), 2,
      sym_rule,
      aux_sym_grammar_body_repeat1,
  [1599] = 4,
    ACTIONS(157), 1,
      anon_sym_PIPE,
    STATE(57), 1,
      aux_sym_rule_body_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(193), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [1614] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(195), 4,
      anon_sym_EQ,
      anon_sym_COLON_EQ,
      anon_sym_PLUS_EQ,
      anon_sym_LPAREN,
  [1625] = 4,
    ACTIONS(197), 1,
      sym_identifier,
    ACTIONS(200), 1,
      anon_sym_RBRACE,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    STATE(64), 2,
      sym_rule,
      aux_sym_grammar_body_repeat1,
  [1640] = 4,
    ACTIONS(171), 1,
      anon_sym_PIPE,
    STATE(54), 1,
      aux_sym_override_rule_body_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(202), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [1655] = 4,
    ACTIONS(171), 1,
      anon_sym_PIPE,
    STATE(48), 1,
      aux_sym_override_rule_body_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(202), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [1670] = 3,
    STATE(107), 1,
      sym__terminal_char,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(204), 2,
      sym__unicode_char,
      sym_escape_char,
  [1682] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(206), 3,
      anon_sym_RBRACE,
      anon_sym_PIPE,
      sym_identifier,
  [1692] = 4,
    ACTIONS(208), 1,
      anon_sym_COMMA,
    ACTIONS(211), 1,
      anon_sym_GT,
    STATE(69), 1,
      aux_sym_params_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [1706] = 4,
    ACTIONS(213), 1,
      anon_sym_COMMA,
    ACTIONS(215), 1,
      anon_sym_GT,
    STATE(71), 1,
      aux_sym_formals_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [1720] = 4,
    ACTIONS(213), 1,
      anon_sym_COMMA,
    ACTIONS(217), 1,
      anon_sym_GT,
    STATE(77), 1,
      aux_sym_formals_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [1734] = 4,
    ACTIONS(219), 1,
      anon_sym_COMMA,
    ACTIONS(221), 1,
      anon_sym_GT,
    STATE(69), 1,
      aux_sym_params_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [1748] = 3,
    ACTIONS(223), 1,
      anon_sym_DQUOTE2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(226), 2,
      sym__unicode_char,
      sym_escape_char,
  [1760] = 4,
    ACTIONS(228), 1,
      anon_sym_RPAREN,
    ACTIONS(230), 1,
      anon_sym_PIPE,
    STATE(74), 1,
      aux_sym_alt_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [1774] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(233), 3,
      anon_sym_RBRACE,
      anon_sym_PIPE,
      sym_identifier,
  [1784] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(235), 3,
      anon_sym_RBRACE,
      anon_sym_PIPE,
      sym_identifier,
  [1794] = 4,
    ACTIONS(237), 1,
      anon_sym_COMMA,
    ACTIONS(240), 1,
      anon_sym_GT,
    STATE(77), 1,
      aux_sym_formals_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [1808] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(242), 3,
      anon_sym_RBRACE,
      anon_sym_PIPE,
      sym_identifier,
  [1818] = 4,
    ACTIONS(244), 1,
      anon_sym_RPAREN,
    ACTIONS(246), 1,
      anon_sym_PIPE,
    STATE(74), 1,
      aux_sym_alt_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [1832] = 4,
    ACTIONS(219), 1,
      anon_sym_COMMA,
    ACTIONS(248), 1,
      anon_sym_GT,
    STATE(72), 1,
      aux_sym_params_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [1846] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(180), 3,
      anon_sym_RBRACE,
      anon_sym_PIPE,
      sym_identifier,
  [1856] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(150), 3,
      anon_sym_RBRACE,
      anon_sym_PIPE,
      sym_identifier,
  [1866] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(250), 3,
      anon_sym_RBRACE,
      anon_sym_PIPE,
      sym_identifier,
  [1876] = 4,
    ACTIONS(246), 1,
      anon_sym_PIPE,
    ACTIONS(252), 1,
      anon_sym_RPAREN,
    STATE(79), 1,
      aux_sym_alt_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [1890] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(228), 2,
      anon_sym_RPAREN,
      anon_sym_PIPE,
  [1899] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(254), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [1908] = 3,
    ACTIONS(256), 1,
      anon_sym_DQUOTE,
    STATE(24), 1,
      sym_one_char_terminal,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [1919] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(258), 2,
      ts_builtin_sym_end,
      sym_identifier,
  [1928] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(260), 2,
      anon_sym_COMMA,
      anon_sym_GT,
  [1937] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(262), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [1946] = 3,
    ACTIONS(187), 1,
      anon_sym_LBRACE,
    STATE(95), 1,
      sym_grammar_body,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [1957] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(264), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [1966] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(266), 2,
      ts_builtin_sym_end,
      sym_identifier,
  [1975] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(268), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [1984] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(270), 2,
      ts_builtin_sym_end,
      sym_identifier,
  [1993] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(240), 2,
      anon_sym_COMMA,
      anon_sym_GT,
  [2002] = 2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
    ACTIONS(272), 2,
      ts_builtin_sym_end,
      sym_identifier,
  [2011] = 3,
    ACTIONS(274), 1,
      sym_identifier,
    ACTIONS(276), 1,
      anon_sym_GT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [2022] = 3,
    ACTIONS(3), 1,
      sym_multiline_comment,
    ACTIONS(278), 1,
      aux_sym_case_name_token1,
    ACTIONS(280), 1,
      sym_singleline_comment,
  [2032] = 3,
    ACTIONS(3), 1,
      sym_multiline_comment,
    ACTIONS(280), 1,
      sym_singleline_comment,
    ACTIONS(282), 1,
      aux_sym_rule_descr_token1,
  [2042] = 2,
    ACTIONS(284), 1,
      anon_sym_LBRACE,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [2050] = 2,
    ACTIONS(286), 1,
      anon_sym_EQ,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [2058] = 2,
    ACTIONS(288), 1,
      anon_sym_DOT_DOT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [2066] = 2,
    ACTIONS(290), 1,
      anon_sym_EQ,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [2074] = 2,
    ACTIONS(292), 1,
      sym_identifier,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [2082] = 2,
    ACTIONS(294), 1,
      sym_identifier,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [2090] = 2,
    ACTIONS(296), 1,
      anon_sym_DQUOTE2,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [2098] = 2,
    ACTIONS(298), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [2106] = 2,
    ACTIONS(300), 1,
      anon_sym_EQ,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [2114] = 2,
    ACTIONS(302), 1,
      sym_identifier,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
  [2122] = 2,
    ACTIONS(304), 1,
      ts_builtin_sym_end,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_singleline_comment,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 57,
  [SMALL_STATE(4)] = 114,
  [SMALL_STATE(5)] = 168,
  [SMALL_STATE(6)] = 222,
  [SMALL_STATE(7)] = 276,
  [SMALL_STATE(8)] = 330,
  [SMALL_STATE(9)] = 371,
  [SMALL_STATE(10)] = 419,
  [SMALL_STATE(11)] = 447,
  [SMALL_STATE(12)] = 495,
  [SMALL_STATE(13)] = 534,
  [SMALL_STATE(14)] = 579,
  [SMALL_STATE(15)] = 624,
  [SMALL_STATE(16)] = 647,
  [SMALL_STATE(17)] = 669,
  [SMALL_STATE(18)] = 693,
  [SMALL_STATE(19)] = 717,
  [SMALL_STATE(20)] = 739,
  [SMALL_STATE(21)] = 761,
  [SMALL_STATE(22)] = 783,
  [SMALL_STATE(23)] = 805,
  [SMALL_STATE(24)] = 843,
  [SMALL_STATE(25)] = 865,
  [SMALL_STATE(26)] = 887,
  [SMALL_STATE(27)] = 909,
  [SMALL_STATE(28)] = 933,
  [SMALL_STATE(29)] = 955,
  [SMALL_STATE(30)] = 979,
  [SMALL_STATE(31)] = 1018,
  [SMALL_STATE(32)] = 1054,
  [SMALL_STATE(33)] = 1090,
  [SMALL_STATE(34)] = 1126,
  [SMALL_STATE(35)] = 1145,
  [SMALL_STATE(36)] = 1164,
  [SMALL_STATE(37)] = 1183,
  [SMALL_STATE(38)] = 1202,
  [SMALL_STATE(39)] = 1227,
  [SMALL_STATE(40)] = 1249,
  [SMALL_STATE(41)] = 1271,
  [SMALL_STATE(42)] = 1295,
  [SMALL_STATE(43)] = 1311,
  [SMALL_STATE(44)] = 1327,
  [SMALL_STATE(45)] = 1343,
  [SMALL_STATE(46)] = 1361,
  [SMALL_STATE(47)] = 1379,
  [SMALL_STATE(48)] = 1395,
  [SMALL_STATE(49)] = 1410,
  [SMALL_STATE(50)] = 1425,
  [SMALL_STATE(51)] = 1436,
  [SMALL_STATE(52)] = 1451,
  [SMALL_STATE(53)] = 1466,
  [SMALL_STATE(54)] = 1477,
  [SMALL_STATE(55)] = 1492,
  [SMALL_STATE(56)] = 1507,
  [SMALL_STATE(57)] = 1522,
  [SMALL_STATE(58)] = 1537,
  [SMALL_STATE(59)] = 1554,
  [SMALL_STATE(60)] = 1569,
  [SMALL_STATE(61)] = 1584,
  [SMALL_STATE(62)] = 1599,
  [SMALL_STATE(63)] = 1614,
  [SMALL_STATE(64)] = 1625,
  [SMALL_STATE(65)] = 1640,
  [SMALL_STATE(66)] = 1655,
  [SMALL_STATE(67)] = 1670,
  [SMALL_STATE(68)] = 1682,
  [SMALL_STATE(69)] = 1692,
  [SMALL_STATE(70)] = 1706,
  [SMALL_STATE(71)] = 1720,
  [SMALL_STATE(72)] = 1734,
  [SMALL_STATE(73)] = 1748,
  [SMALL_STATE(74)] = 1760,
  [SMALL_STATE(75)] = 1774,
  [SMALL_STATE(76)] = 1784,
  [SMALL_STATE(77)] = 1794,
  [SMALL_STATE(78)] = 1808,
  [SMALL_STATE(79)] = 1818,
  [SMALL_STATE(80)] = 1832,
  [SMALL_STATE(81)] = 1846,
  [SMALL_STATE(82)] = 1856,
  [SMALL_STATE(83)] = 1866,
  [SMALL_STATE(84)] = 1876,
  [SMALL_STATE(85)] = 1890,
  [SMALL_STATE(86)] = 1899,
  [SMALL_STATE(87)] = 1908,
  [SMALL_STATE(88)] = 1919,
  [SMALL_STATE(89)] = 1928,
  [SMALL_STATE(90)] = 1937,
  [SMALL_STATE(91)] = 1946,
  [SMALL_STATE(92)] = 1957,
  [SMALL_STATE(93)] = 1966,
  [SMALL_STATE(94)] = 1975,
  [SMALL_STATE(95)] = 1984,
  [SMALL_STATE(96)] = 1993,
  [SMALL_STATE(97)] = 2002,
  [SMALL_STATE(98)] = 2011,
  [SMALL_STATE(99)] = 2022,
  [SMALL_STATE(100)] = 2032,
  [SMALL_STATE(101)] = 2042,
  [SMALL_STATE(102)] = 2050,
  [SMALL_STATE(103)] = 2058,
  [SMALL_STATE(104)] = 2066,
  [SMALL_STATE(105)] = 2074,
  [SMALL_STATE(106)] = 2082,
  [SMALL_STATE(107)] = 2090,
  [SMALL_STATE(108)] = 2098,
  [SMALL_STATE(109)] = 2106,
  [SMALL_STATE(110)] = 2114,
  [SMALL_STATE(111)] = 2122,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [9] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_rule, 2, .production_id = 4), SHIFT(10),
  [12] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule, 2, .production_id = 4),
  [14] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [16] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [18] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [20] = {.entry = {.count = 1, .reusable = true}}, SHIFT(110),
  [22] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [24] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [26] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [28] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_rule, 3, .production_id = 9), SHIFT(10),
  [31] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule, 3, .production_id = 9),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [35] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_rule, 3, .production_id = 10), SHIFT(10),
  [38] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule, 3, .production_id = 10),
  [40] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_rule, 4, .production_id = 16), SHIFT(10),
  [43] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule, 4, .production_id = 16),
  [45] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_seq_repeat1, 2), SHIFT_REPEAT(10),
  [48] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_seq_repeat1, 2),
  [50] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_seq_repeat1, 2), SHIFT_REPEAT(32),
  [53] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_seq_repeat1, 2), SHIFT_REPEAT(38),
  [56] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_seq_repeat1, 2), SHIFT_REPEAT(39),
  [59] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_seq_repeat1, 2), SHIFT_REPEAT(46),
  [62] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [64] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__base, 1),
  [66] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [68] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_seq, 1),
  [70] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_one_char_terminal, 3),
  [72] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_params, 2),
  [74] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_term, 2, .production_id = 11),
  [76] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [78] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_term, 3, .production_id = 18),
  [80] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [82] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alt, 3),
  [84] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_params, 4, .production_id = 23),
  [86] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_params, 3, .production_id = 23),
  [88] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_terminal_string, 3),
  [90] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_seq, 1), SHIFT(10),
  [93] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__base, 3),
  [95] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__base, 2),
  [97] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alt, 4),
  [99] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_term, 2, .production_id = 12),
  [101] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [103] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_terminal_string, 2),
  [105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_term, 1, .production_id = 8),
  [107] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [109] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [111] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_term, 2, .production_id = 14),
  [113] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_term, 4, .production_id = 22),
  [115] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_term, 3, .production_id = 19),
  [117] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_term, 3, .production_id = 20),
  [119] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [121] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [123] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [125] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [127] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [129] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_terminal_string_repeat1, 2),
  [131] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_terminal_string_repeat1, 2), SHIFT_REPEAT(42),
  [134] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_top_level_term, 1, .production_id = 7),
  [136] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_override_top_level_term, 1, .production_id = 7),
  [138] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [140] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [142] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [144] = {.entry = {.count = 1, .reusable = true}}, SHIFT(73),
  [146] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [148] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [150] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_override_rule_body_repeat1, 2),
  [152] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_override_rule_body_repeat1, 2), SHIFT_REPEAT(11),
  [155] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule_body, 1),
  [157] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [159] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_formals, 2),
  [161] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [163] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [165] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [167] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_formals, 4),
  [169] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_override_rule_body, 3),
  [171] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [173] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule_body, 2),
  [175] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [177] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(58),
  [180] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_rule_body_repeat1, 2),
  [182] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_rule_body_repeat1, 2), SHIFT_REPEAT(13),
  [185] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [187] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [189] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_override_rule_body, 1),
  [191] = {.entry = {.count = 1, .reusable = true}}, SHIFT(88),
  [193] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule_body, 3),
  [195] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_formals, 3),
  [197] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_grammar_body_repeat1, 2), SHIFT_REPEAT(41),
  [200] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_grammar_body_repeat1, 2),
  [202] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_override_rule_body, 2),
  [204] = {.entry = {.count = 1, .reusable = true}}, SHIFT(107),
  [206] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_override_top_level_term, 2, .production_id = 13),
  [208] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_params_repeat1, 2), SHIFT_REPEAT(33),
  [211] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_params_repeat1, 2),
  [213] = {.entry = {.count = 1, .reusable = true}}, SHIFT(106),
  [215] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [217] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [219] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [221] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [223] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_terminal_string_repeat1, 1), SHIFT(15),
  [226] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_terminal_string_repeat1, 1),
  [228] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_alt_repeat1, 2),
  [230] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_alt_repeat1, 2), SHIFT_REPEAT(31),
  [233] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_case_name, 3),
  [235] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_top_level_term, 1, .production_id = 6),
  [237] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_formals_repeat1, 2), SHIFT_REPEAT(106),
  [240] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_formals_repeat1, 2),
  [242] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_override_top_level_term, 1, .production_id = 6),
  [244] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [246] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [248] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [250] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_top_level_term, 2, .production_id = 13),
  [252] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [254] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule, 5, .production_id = 21),
  [256] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [258] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_grammar_body, 3),
  [260] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_params_repeat1, 2, .production_id = 23),
  [262] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule, 4, .production_id = 15),
  [264] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule, 4, .production_id = 17),
  [266] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_grammar_body, 2),
  [268] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule, 3, .production_id = 5),
  [270] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_grammar, 3, .production_id = 3),
  [272] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_grammar, 2, .production_id = 1),
  [274] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [276] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [278] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [280] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [282] = {.entry = {.count = 1, .reusable = false}}, SHIFT(108),
  [284] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_super_grammar, 2, .production_id = 2),
  [286] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [288] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [290] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [292] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [294] = {.entry = {.count = 1, .reusable = true}}, SHIFT(96),
  [296] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [298] = {.entry = {.count = 1, .reusable = true}}, SHIFT(109),
  [300] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule_descr, 3),
  [302] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [304] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
};

#ifdef __cplusplus
extern "C" {
#endif
void *tree_sitter_ohm_external_scanner_create(void);
void tree_sitter_ohm_external_scanner_destroy(void *);
bool tree_sitter_ohm_external_scanner_scan(void *, TSLexer *, const bool *);
unsigned tree_sitter_ohm_external_scanner_serialize(void *, char *);
void tree_sitter_ohm_external_scanner_deserialize(void *, const char *, unsigned);

#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_ohm(void) {
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
    .keyword_lex_fn = ts_lex_keywords,
    .keyword_capture_token = sym_identifier,
    .external_scanner = {
      &ts_external_scanner_states[0][0],
      ts_external_scanner_symbol_map,
      tree_sitter_ohm_external_scanner_create,
      tree_sitter_ohm_external_scanner_destroy,
      tree_sitter_ohm_external_scanner_scan,
      tree_sitter_ohm_external_scanner_serialize,
      tree_sitter_ohm_external_scanner_deserialize,
    },
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
