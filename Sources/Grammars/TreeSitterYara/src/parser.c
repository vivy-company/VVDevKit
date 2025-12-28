#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 174
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 146
#define ALIAS_COUNT 1
#define TOKEN_COUNT 79
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 8
#define MAX_ALIAS_SEQUENCE_LENGTH 10
#define PRODUCTION_ID_COUNT 12

enum ts_symbol_identifiers {
  sym_identifier = 1,
  anon_sym_EQ = 2,
  anon_sym_COLON = 3,
  anon_sym_LBRACE = 4,
  anon_sym_RBRACE = 5,
  anon_sym_LBRACK = 6,
  anon_sym_RBRACK = 7,
  anon_sym_LPAREN = 8,
  anon_sym_RPAREN = 9,
  anon_sym_DOLLAR = 10,
  anon_sym_POUND = 11,
  anon_sym_AT = 12,
  anon_sym_DOT_DOT = 13,
  anon_sym_PIPE = 14,
  anon_sym_COMMA = 15,
  anon_sym_BANG = 16,
  anon_sym_SLASH = 17,
  anon_sym_DQUOTE = 18,
  anon_sym_SQUOTE = 19,
  anon_sym_import = 20,
  anon_sym_include = 21,
  anon_sym_private = 22,
  anon_sym_global = 23,
  anon_sym_rule = 24,
  anon_sym_meta = 25,
  anon_sym_strings = 26,
  aux_sym_double_quoted_string_token1 = 27,
  aux_sym_single_quoted_string_token1 = 28,
  sym_escape_sequence = 29,
  sym_hex_byte = 30,
  sym_hex_wildcard = 31,
  aux_sym_regex_string_content_token1 = 32,
  anon_sym_nocase = 33,
  anon_sym_ascii = 34,
  anon_sym_wide = 35,
  anon_sym_fullword = 36,
  anon_sym_base64 = 37,
  anon_sym_base64wide = 38,
  anon_sym_xor = 39,
  anon_sym_condition = 40,
  sym_filesize_keyword = 41,
  sym_entrypoint_keyword = 42,
  anon_sym_KB = 43,
  anon_sym_MB = 44,
  anon_sym_GB = 45,
  aux_sym_integer_literal_token1 = 46,
  anon_sym_for = 47,
  anon_sym_of = 48,
  anon_sym_in = 49,
  anon_sym_all = 50,
  anon_sym_any = 51,
  anon_sym_none = 52,
  anon_sym_them = 53,
  anon_sym_not = 54,
  anon_sym_DASH = 55,
  anon_sym_STAR = 56,
  anon_sym_BSLASH = 57,
  anon_sym_PERCENT = 58,
  anon_sym_PLUS = 59,
  anon_sym_EQ_EQ = 60,
  anon_sym_BANG_EQ = 61,
  anon_sym_LT = 62,
  anon_sym_LT_EQ = 63,
  anon_sym_GT = 64,
  anon_sym_GT_EQ = 65,
  anon_sym_contains = 66,
  anon_sym_matches = 67,
  anon_sym_icontains = 68,
  anon_sym_imatches = 69,
  anon_sym_startswith = 70,
  anon_sym_istartswith = 71,
  anon_sym_endswith = 72,
  anon_sym_iendswith = 73,
  anon_sym_and = 74,
  anon_sym_or = 75,
  anon_sym_true = 76,
  anon_sym_false = 77,
  sym_comment = 78,
  sym_source_file = 79,
  sym__equal = 80,
  sym__colon = 81,
  sym__lbrace = 82,
  sym__rbrace = 83,
  sym__lbrack = 84,
  sym__rbrack = 85,
  sym__lparen = 86,
  sym__rparen = 87,
  sym__dollar = 88,
  sym__hash = 89,
  sym__at = 90,
  sym__range = 91,
  sym__pipe = 92,
  sym__comma = 93,
  sym__bang = 94,
  sym__slash = 95,
  sym__quote = 96,
  sym__squote = 97,
  sym_import_statement = 98,
  sym_include_statement = 99,
  sym_rule_definition = 100,
  sym_tag_list = 101,
  sym_rule_body = 102,
  sym_meta_section = 103,
  sym_meta_definition = 104,
  sym_strings_section = 105,
  sym_string_definition = 106,
  sym_string_identifier = 107,
  sym_text_string = 108,
  sym_double_quoted_string = 109,
  sym_single_quoted_string = 110,
  sym_hex_string = 111,
  sym_hex_jump = 112,
  sym_hex_alternative = 113,
  sym_regex_string = 114,
  sym_regex_string_content = 115,
  sym_string_modifiers = 116,
  sym_condition_section = 117,
  sym__expression = 118,
  sym_size_unit = 119,
  sym_integer_literal = 120,
  sym_string_count = 121,
  sym_string_offset = 122,
  sym_string_length = 123,
  sym_for_expression = 124,
  sym_for_of_expression = 125,
  sym_of_expression = 126,
  sym_quantifier = 127,
  sym_string_set = 128,
  sym_range = 129,
  sym_unary_expression = 130,
  sym_binary_expression = 131,
  sym_parenthesized_expression = 132,
  sym_boolean_literal = 133,
  sym_string_literal = 134,
  aux_sym_source_file_repeat1 = 135,
  aux_sym_tag_list_repeat1 = 136,
  aux_sym_meta_section_repeat1 = 137,
  aux_sym_strings_section_repeat1 = 138,
  aux_sym_double_quoted_string_repeat1 = 139,
  aux_sym_single_quoted_string_repeat1 = 140,
  aux_sym_hex_string_repeat1 = 141,
  aux_sym_hex_alternative_repeat1 = 142,
  aux_sym_regex_string_content_repeat1 = 143,
  aux_sym_string_modifiers_repeat1 = 144,
  aux_sym_string_set_repeat1 = 145,
  alias_sym_tag = 146,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_identifier] = "identifier",
  [anon_sym_EQ] = "=",
  [anon_sym_COLON] = ":",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_DOLLAR] = "$",
  [anon_sym_POUND] = "#",
  [anon_sym_AT] = "@",
  [anon_sym_DOT_DOT] = "..",
  [anon_sym_PIPE] = "|",
  [anon_sym_COMMA] = ",",
  [anon_sym_BANG] = "!",
  [anon_sym_SLASH] = "/",
  [anon_sym_DQUOTE] = "\"",
  [anon_sym_SQUOTE] = "'",
  [anon_sym_import] = "import",
  [anon_sym_include] = "include",
  [anon_sym_private] = "private",
  [anon_sym_global] = "global",
  [anon_sym_rule] = "rule",
  [anon_sym_meta] = "meta",
  [anon_sym_strings] = "strings",
  [aux_sym_double_quoted_string_token1] = "double_quoted_string_token1",
  [aux_sym_single_quoted_string_token1] = "single_quoted_string_token1",
  [sym_escape_sequence] = "escape_sequence",
  [sym_hex_byte] = "hex_byte",
  [sym_hex_wildcard] = "hex_wildcard",
  [aux_sym_regex_string_content_token1] = "regex_string_content_token1",
  [anon_sym_nocase] = "nocase",
  [anon_sym_ascii] = "ascii",
  [anon_sym_wide] = "wide",
  [anon_sym_fullword] = "fullword",
  [anon_sym_base64] = "base64",
  [anon_sym_base64wide] = "base64wide",
  [anon_sym_xor] = "xor",
  [anon_sym_condition] = "condition",
  [sym_filesize_keyword] = "filesize_keyword",
  [sym_entrypoint_keyword] = "entrypoint_keyword",
  [anon_sym_KB] = "KB",
  [anon_sym_MB] = "MB",
  [anon_sym_GB] = "GB",
  [aux_sym_integer_literal_token1] = "integer_literal_token1",
  [anon_sym_for] = "for",
  [anon_sym_of] = "of",
  [anon_sym_in] = "in",
  [anon_sym_all] = "all",
  [anon_sym_any] = "any",
  [anon_sym_none] = "none",
  [anon_sym_them] = "them",
  [anon_sym_not] = "not",
  [anon_sym_DASH] = "-",
  [anon_sym_STAR] = "*",
  [anon_sym_BSLASH] = "\\",
  [anon_sym_PERCENT] = "%",
  [anon_sym_PLUS] = "+",
  [anon_sym_EQ_EQ] = "==",
  [anon_sym_BANG_EQ] = "!=",
  [anon_sym_LT] = "<",
  [anon_sym_LT_EQ] = "<=",
  [anon_sym_GT] = ">",
  [anon_sym_GT_EQ] = ">=",
  [anon_sym_contains] = "contains",
  [anon_sym_matches] = "matches",
  [anon_sym_icontains] = "icontains",
  [anon_sym_imatches] = "imatches",
  [anon_sym_startswith] = "startswith",
  [anon_sym_istartswith] = "istartswith",
  [anon_sym_endswith] = "endswith",
  [anon_sym_iendswith] = "iendswith",
  [anon_sym_and] = "and",
  [anon_sym_or] = "or",
  [anon_sym_true] = "true",
  [anon_sym_false] = "false",
  [sym_comment] = "comment",
  [sym_source_file] = "source_file",
  [sym__equal] = "_equal",
  [sym__colon] = "_colon",
  [sym__lbrace] = "_lbrace",
  [sym__rbrace] = "_rbrace",
  [sym__lbrack] = "_lbrack",
  [sym__rbrack] = "_rbrack",
  [sym__lparen] = "_lparen",
  [sym__rparen] = "_rparen",
  [sym__dollar] = "_dollar",
  [sym__hash] = "_hash",
  [sym__at] = "_at",
  [sym__range] = "_range",
  [sym__pipe] = "_pipe",
  [sym__comma] = "_comma",
  [sym__bang] = "_bang",
  [sym__slash] = "_slash",
  [sym__quote] = "_quote",
  [sym__squote] = "_squote",
  [sym_import_statement] = "import_statement",
  [sym_include_statement] = "include_statement",
  [sym_rule_definition] = "rule_definition",
  [sym_tag_list] = "tag_list",
  [sym_rule_body] = "rule_body",
  [sym_meta_section] = "meta_section",
  [sym_meta_definition] = "meta_definition",
  [sym_strings_section] = "strings_section",
  [sym_string_definition] = "string_definition",
  [sym_string_identifier] = "string_identifier",
  [sym_text_string] = "text_string",
  [sym_double_quoted_string] = "double_quoted_string",
  [sym_single_quoted_string] = "single_quoted_string",
  [sym_hex_string] = "hex_string",
  [sym_hex_jump] = "hex_jump",
  [sym_hex_alternative] = "hex_alternative",
  [sym_regex_string] = "regex_string",
  [sym_regex_string_content] = "pattern",
  [sym_string_modifiers] = "string_modifiers",
  [sym_condition_section] = "condition_section",
  [sym__expression] = "_expression",
  [sym_size_unit] = "size_unit",
  [sym_integer_literal] = "integer_literal",
  [sym_string_count] = "string_count",
  [sym_string_offset] = "string_offset",
  [sym_string_length] = "string_length",
  [sym_for_expression] = "for_expression",
  [sym_for_of_expression] = "for_of_expression",
  [sym_of_expression] = "of_expression",
  [sym_quantifier] = "quantifier",
  [sym_string_set] = "string_set",
  [sym_range] = "range",
  [sym_unary_expression] = "unary_expression",
  [sym_binary_expression] = "binary_expression",
  [sym_parenthesized_expression] = "parenthesized_expression",
  [sym_boolean_literal] = "boolean_literal",
  [sym_string_literal] = "string_literal",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_tag_list_repeat1] = "tag_list_repeat1",
  [aux_sym_meta_section_repeat1] = "meta_section_repeat1",
  [aux_sym_strings_section_repeat1] = "strings_section_repeat1",
  [aux_sym_double_quoted_string_repeat1] = "double_quoted_string_repeat1",
  [aux_sym_single_quoted_string_repeat1] = "single_quoted_string_repeat1",
  [aux_sym_hex_string_repeat1] = "hex_string_repeat1",
  [aux_sym_hex_alternative_repeat1] = "hex_alternative_repeat1",
  [aux_sym_regex_string_content_repeat1] = "regex_string_content_repeat1",
  [aux_sym_string_modifiers_repeat1] = "string_modifiers_repeat1",
  [aux_sym_string_set_repeat1] = "string_set_repeat1",
  [alias_sym_tag] = "tag",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_identifier] = sym_identifier,
  [anon_sym_EQ] = anon_sym_EQ,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_DOLLAR] = anon_sym_DOLLAR,
  [anon_sym_POUND] = anon_sym_POUND,
  [anon_sym_AT] = anon_sym_AT,
  [anon_sym_DOT_DOT] = anon_sym_DOT_DOT,
  [anon_sym_PIPE] = anon_sym_PIPE,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_BANG] = anon_sym_BANG,
  [anon_sym_SLASH] = anon_sym_SLASH,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [anon_sym_SQUOTE] = anon_sym_SQUOTE,
  [anon_sym_import] = anon_sym_import,
  [anon_sym_include] = anon_sym_include,
  [anon_sym_private] = anon_sym_private,
  [anon_sym_global] = anon_sym_global,
  [anon_sym_rule] = anon_sym_rule,
  [anon_sym_meta] = anon_sym_meta,
  [anon_sym_strings] = anon_sym_strings,
  [aux_sym_double_quoted_string_token1] = aux_sym_double_quoted_string_token1,
  [aux_sym_single_quoted_string_token1] = aux_sym_single_quoted_string_token1,
  [sym_escape_sequence] = sym_escape_sequence,
  [sym_hex_byte] = sym_hex_byte,
  [sym_hex_wildcard] = sym_hex_wildcard,
  [aux_sym_regex_string_content_token1] = aux_sym_regex_string_content_token1,
  [anon_sym_nocase] = anon_sym_nocase,
  [anon_sym_ascii] = anon_sym_ascii,
  [anon_sym_wide] = anon_sym_wide,
  [anon_sym_fullword] = anon_sym_fullword,
  [anon_sym_base64] = anon_sym_base64,
  [anon_sym_base64wide] = anon_sym_base64wide,
  [anon_sym_xor] = anon_sym_xor,
  [anon_sym_condition] = anon_sym_condition,
  [sym_filesize_keyword] = sym_filesize_keyword,
  [sym_entrypoint_keyword] = sym_entrypoint_keyword,
  [anon_sym_KB] = anon_sym_KB,
  [anon_sym_MB] = anon_sym_MB,
  [anon_sym_GB] = anon_sym_GB,
  [aux_sym_integer_literal_token1] = aux_sym_integer_literal_token1,
  [anon_sym_for] = anon_sym_for,
  [anon_sym_of] = anon_sym_of,
  [anon_sym_in] = anon_sym_in,
  [anon_sym_all] = anon_sym_all,
  [anon_sym_any] = anon_sym_any,
  [anon_sym_none] = anon_sym_none,
  [anon_sym_them] = anon_sym_them,
  [anon_sym_not] = anon_sym_not,
  [anon_sym_DASH] = anon_sym_DASH,
  [anon_sym_STAR] = anon_sym_STAR,
  [anon_sym_BSLASH] = anon_sym_BSLASH,
  [anon_sym_PERCENT] = anon_sym_PERCENT,
  [anon_sym_PLUS] = anon_sym_PLUS,
  [anon_sym_EQ_EQ] = anon_sym_EQ_EQ,
  [anon_sym_BANG_EQ] = anon_sym_BANG_EQ,
  [anon_sym_LT] = anon_sym_LT,
  [anon_sym_LT_EQ] = anon_sym_LT_EQ,
  [anon_sym_GT] = anon_sym_GT,
  [anon_sym_GT_EQ] = anon_sym_GT_EQ,
  [anon_sym_contains] = anon_sym_contains,
  [anon_sym_matches] = anon_sym_matches,
  [anon_sym_icontains] = anon_sym_icontains,
  [anon_sym_imatches] = anon_sym_imatches,
  [anon_sym_startswith] = anon_sym_startswith,
  [anon_sym_istartswith] = anon_sym_istartswith,
  [anon_sym_endswith] = anon_sym_endswith,
  [anon_sym_iendswith] = anon_sym_iendswith,
  [anon_sym_and] = anon_sym_and,
  [anon_sym_or] = anon_sym_or,
  [anon_sym_true] = anon_sym_true,
  [anon_sym_false] = anon_sym_false,
  [sym_comment] = sym_comment,
  [sym_source_file] = sym_source_file,
  [sym__equal] = sym__equal,
  [sym__colon] = sym__colon,
  [sym__lbrace] = sym__lbrace,
  [sym__rbrace] = sym__rbrace,
  [sym__lbrack] = sym__lbrack,
  [sym__rbrack] = sym__rbrack,
  [sym__lparen] = sym__lparen,
  [sym__rparen] = sym__rparen,
  [sym__dollar] = sym__dollar,
  [sym__hash] = sym__hash,
  [sym__at] = sym__at,
  [sym__range] = sym__range,
  [sym__pipe] = sym__pipe,
  [sym__comma] = sym__comma,
  [sym__bang] = sym__bang,
  [sym__slash] = sym__slash,
  [sym__quote] = sym__quote,
  [sym__squote] = sym__squote,
  [sym_import_statement] = sym_import_statement,
  [sym_include_statement] = sym_include_statement,
  [sym_rule_definition] = sym_rule_definition,
  [sym_tag_list] = sym_tag_list,
  [sym_rule_body] = sym_rule_body,
  [sym_meta_section] = sym_meta_section,
  [sym_meta_definition] = sym_meta_definition,
  [sym_strings_section] = sym_strings_section,
  [sym_string_definition] = sym_string_definition,
  [sym_string_identifier] = sym_string_identifier,
  [sym_text_string] = sym_text_string,
  [sym_double_quoted_string] = sym_double_quoted_string,
  [sym_single_quoted_string] = sym_single_quoted_string,
  [sym_hex_string] = sym_hex_string,
  [sym_hex_jump] = sym_hex_jump,
  [sym_hex_alternative] = sym_hex_alternative,
  [sym_regex_string] = sym_regex_string,
  [sym_regex_string_content] = sym_regex_string_content,
  [sym_string_modifiers] = sym_string_modifiers,
  [sym_condition_section] = sym_condition_section,
  [sym__expression] = sym__expression,
  [sym_size_unit] = sym_size_unit,
  [sym_integer_literal] = sym_integer_literal,
  [sym_string_count] = sym_string_count,
  [sym_string_offset] = sym_string_offset,
  [sym_string_length] = sym_string_length,
  [sym_for_expression] = sym_for_expression,
  [sym_for_of_expression] = sym_for_of_expression,
  [sym_of_expression] = sym_of_expression,
  [sym_quantifier] = sym_quantifier,
  [sym_string_set] = sym_string_set,
  [sym_range] = sym_range,
  [sym_unary_expression] = sym_unary_expression,
  [sym_binary_expression] = sym_binary_expression,
  [sym_parenthesized_expression] = sym_parenthesized_expression,
  [sym_boolean_literal] = sym_boolean_literal,
  [sym_string_literal] = sym_string_literal,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_tag_list_repeat1] = aux_sym_tag_list_repeat1,
  [aux_sym_meta_section_repeat1] = aux_sym_meta_section_repeat1,
  [aux_sym_strings_section_repeat1] = aux_sym_strings_section_repeat1,
  [aux_sym_double_quoted_string_repeat1] = aux_sym_double_quoted_string_repeat1,
  [aux_sym_single_quoted_string_repeat1] = aux_sym_single_quoted_string_repeat1,
  [aux_sym_hex_string_repeat1] = aux_sym_hex_string_repeat1,
  [aux_sym_hex_alternative_repeat1] = aux_sym_hex_alternative_repeat1,
  [aux_sym_regex_string_content_repeat1] = aux_sym_regex_string_content_repeat1,
  [aux_sym_string_modifiers_repeat1] = aux_sym_string_modifiers_repeat1,
  [aux_sym_string_set_repeat1] = aux_sym_string_set_repeat1,
  [alias_sym_tag] = alias_sym_tag,
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
  [anon_sym_EQ] = {
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
  [anon_sym_LBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACK] = {
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
  [anon_sym_DOLLAR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_POUND] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_AT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOT_DOT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PIPE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BANG] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SLASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_import] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_include] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_private] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_global] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_rule] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_meta] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_strings] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_double_quoted_string_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_single_quoted_string_token1] = {
    .visible = false,
    .named = false,
  },
  [sym_escape_sequence] = {
    .visible = true,
    .named = true,
  },
  [sym_hex_byte] = {
    .visible = true,
    .named = true,
  },
  [sym_hex_wildcard] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_regex_string_content_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_nocase] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ascii] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_wide] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_fullword] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_base64] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_base64wide] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_xor] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_condition] = {
    .visible = true,
    .named = false,
  },
  [sym_filesize_keyword] = {
    .visible = true,
    .named = true,
  },
  [sym_entrypoint_keyword] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_KB] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_MB] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GB] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_integer_literal_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_for] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_of] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_in] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_all] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_any] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_none] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_them] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_not] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_STAR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BSLASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PERCENT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PLUS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BANG_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_contains] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_matches] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_icontains] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_imatches] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_startswith] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_istartswith] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_endswith] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_iendswith] = {
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
  [anon_sym_true] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_false] = {
    .visible = true,
    .named = false,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym__equal] = {
    .visible = false,
    .named = true,
  },
  [sym__colon] = {
    .visible = false,
    .named = true,
  },
  [sym__lbrace] = {
    .visible = false,
    .named = true,
  },
  [sym__rbrace] = {
    .visible = false,
    .named = true,
  },
  [sym__lbrack] = {
    .visible = false,
    .named = true,
  },
  [sym__rbrack] = {
    .visible = false,
    .named = true,
  },
  [sym__lparen] = {
    .visible = false,
    .named = true,
  },
  [sym__rparen] = {
    .visible = false,
    .named = true,
  },
  [sym__dollar] = {
    .visible = false,
    .named = true,
  },
  [sym__hash] = {
    .visible = false,
    .named = true,
  },
  [sym__at] = {
    .visible = false,
    .named = true,
  },
  [sym__range] = {
    .visible = false,
    .named = true,
  },
  [sym__pipe] = {
    .visible = false,
    .named = true,
  },
  [sym__comma] = {
    .visible = false,
    .named = true,
  },
  [sym__bang] = {
    .visible = false,
    .named = true,
  },
  [sym__slash] = {
    .visible = false,
    .named = true,
  },
  [sym__quote] = {
    .visible = false,
    .named = true,
  },
  [sym__squote] = {
    .visible = false,
    .named = true,
  },
  [sym_import_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_include_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_rule_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_tag_list] = {
    .visible = true,
    .named = true,
  },
  [sym_rule_body] = {
    .visible = true,
    .named = true,
  },
  [sym_meta_section] = {
    .visible = true,
    .named = true,
  },
  [sym_meta_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_strings_section] = {
    .visible = true,
    .named = true,
  },
  [sym_string_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_string_identifier] = {
    .visible = true,
    .named = true,
  },
  [sym_text_string] = {
    .visible = true,
    .named = true,
  },
  [sym_double_quoted_string] = {
    .visible = true,
    .named = true,
  },
  [sym_single_quoted_string] = {
    .visible = true,
    .named = true,
  },
  [sym_hex_string] = {
    .visible = true,
    .named = true,
  },
  [sym_hex_jump] = {
    .visible = true,
    .named = true,
  },
  [sym_hex_alternative] = {
    .visible = true,
    .named = true,
  },
  [sym_regex_string] = {
    .visible = true,
    .named = true,
  },
  [sym_regex_string_content] = {
    .visible = true,
    .named = true,
  },
  [sym_string_modifiers] = {
    .visible = true,
    .named = true,
  },
  [sym_condition_section] = {
    .visible = true,
    .named = true,
  },
  [sym__expression] = {
    .visible = false,
    .named = true,
  },
  [sym_size_unit] = {
    .visible = true,
    .named = true,
  },
  [sym_integer_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_string_count] = {
    .visible = true,
    .named = true,
  },
  [sym_string_offset] = {
    .visible = true,
    .named = true,
  },
  [sym_string_length] = {
    .visible = true,
    .named = true,
  },
  [sym_for_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_for_of_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_of_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_quantifier] = {
    .visible = true,
    .named = true,
  },
  [sym_string_set] = {
    .visible = true,
    .named = true,
  },
  [sym_range] = {
    .visible = true,
    .named = true,
  },
  [sym_unary_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_binary_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_parenthesized_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_boolean_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_string_literal] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_tag_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_meta_section_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_strings_section_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_double_quoted_string_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_single_quoted_string_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_hex_string_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_hex_alternative_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_regex_string_content_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_string_modifiers_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_string_set_repeat1] = {
    .visible = false,
    .named = false,
  },
  [alias_sym_tag] = {
    .visible = true,
    .named = true,
  },
};

enum ts_field_identifiers {
  field_body = 1,
  field_key = 2,
  field_left = 3,
  field_name = 4,
  field_operand = 5,
  field_operator = 6,
  field_right = 7,
  field_value = 8,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_body] = "body",
  [field_key] = "key",
  [field_left] = "left",
  [field_name] = "name",
  [field_operand] = "operand",
  [field_operator] = "operator",
  [field_right] = "right",
  [field_value] = "value",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 2},
  [2] = {.index = 2, .length = 2},
  [3] = {.index = 4, .length = 2},
  [4] = {.index = 6, .length = 2},
  [5] = {.index = 8, .length = 2},
  [7] = {.index = 10, .length = 2},
  [8] = {.index = 12, .length = 2},
  [9] = {.index = 14, .length = 2},
  [10] = {.index = 16, .length = 2},
  [11] = {.index = 18, .length = 3},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_body, 2},
    {field_name, 1},
  [2] =
    {field_body, 3},
    {field_name, 2},
  [4] =
    {field_body, 3},
    {field_name, 1},
  [6] =
    {field_body, 4},
    {field_name, 3},
  [8] =
    {field_body, 4},
    {field_name, 2},
  [10] =
    {field_body, 5},
    {field_name, 3},
  [12] =
    {field_operand, 1},
    {field_operator, 0},
  [14] =
    {field_key, 0},
    {field_value, 2},
  [16] =
    {field_name, 0},
    {field_value, 2},
  [18] =
    {field_left, 0},
    {field_operator, 1},
    {field_right, 2},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
  [6] = {
    [0] = alias_sym_tag,
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
  [56] = 55,
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
  [112] = 112,
  [113] = 113,
  [114] = 114,
  [115] = 115,
  [116] = 116,
  [117] = 117,
  [118] = 118,
  [119] = 119,
  [120] = 120,
  [121] = 121,
  [122] = 122,
  [123] = 123,
  [124] = 124,
  [125] = 125,
  [126] = 126,
  [127] = 127,
  [128] = 128,
  [129] = 129,
  [130] = 130,
  [131] = 131,
  [132] = 132,
  [133] = 133,
  [134] = 134,
  [135] = 135,
  [136] = 136,
  [137] = 137,
  [138] = 138,
  [139] = 139,
  [140] = 140,
  [141] = 141,
  [142] = 142,
  [143] = 143,
  [144] = 144,
  [145] = 145,
  [146] = 146,
  [147] = 147,
  [148] = 148,
  [149] = 149,
  [150] = 150,
  [151] = 151,
  [152] = 152,
  [153] = 153,
  [154] = 154,
  [155] = 155,
  [156] = 156,
  [157] = 157,
  [158] = 158,
  [159] = 159,
  [160] = 160,
  [161] = 161,
  [162] = 162,
  [163] = 163,
  [164] = 164,
  [165] = 165,
  [166] = 166,
  [167] = 167,
  [168] = 168,
  [169] = 169,
  [170] = 170,
  [171] = 171,
  [172] = 172,
  [173] = 173,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(24);
      if (lookahead == '\r') SKIP(0);
      if (lookahead == '!') ADVANCE(41);
      if (lookahead == '"') ADVANCE(43);
      if (lookahead == '#') ADVANCE(35);
      if (lookahead == '$') ADVANCE(34);
      if (lookahead == '%') ADVANCE(71);
      if (lookahead == '\'') ADVANCE(44);
      if (lookahead == '(') ADVANCE(32);
      if (lookahead == ')') ADVANCE(33);
      if (lookahead == '*') ADVANCE(69);
      if (lookahead == '+') ADVANCE(72);
      if (lookahead == ',') ADVANCE(39);
      if (lookahead == '-') ADVANCE(68);
      if (lookahead == '.') ADVANCE(9);
      if (lookahead == '/') ADVANCE(42);
      if (lookahead == ':') ADVANCE(27);
      if (lookahead == '<') ADVANCE(75);
      if (lookahead == '=') ADVANCE(26);
      if (lookahead == '>') ADVANCE(77);
      if (lookahead == '?') ADVANCE(63);
      if (lookahead == '@') ADVANCE(36);
      if (lookahead == '[') ADVANCE(30);
      if (lookahead == '\\') ADVANCE(70);
      if (lookahead == ']') ADVANCE(31);
      if (lookahead == '{') ADVANCE(28);
      if (lookahead == '|') ADVANCE(38);
      if (lookahead == '}') ADVANCE(29);
      if (('\t' <= lookahead && lookahead <= '\f') ||
          lookahead == ' ' ||
          lookahead == 0x200b ||
          lookahead == 0x2060 ||
          lookahead == 0xfeff) SKIP(0);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(66);
      if (('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(79);
      if (('G' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(80);
      END_STATE();
    case 1:
      if (lookahead == '\r') SKIP(1);
      if (lookahead == '!') ADVANCE(10);
      if (lookahead == '%') ADVANCE(71);
      if (lookahead == ')') ADVANCE(33);
      if (lookahead == '*') ADVANCE(69);
      if (lookahead == '+') ADVANCE(72);
      if (lookahead == ',') ADVANCE(39);
      if (lookahead == '-') ADVANCE(68);
      if (lookahead == '/') ADVANCE(6);
      if (lookahead == '<') ADVANCE(75);
      if (lookahead == '=') ADVANCE(26);
      if (lookahead == '>') ADVANCE(77);
      if (lookahead == '[') ADVANCE(30);
      if (lookahead == '\\') ADVANCE(70);
      if (lookahead == '}') ADVANCE(29);
      if (('\t' <= lookahead && lookahead <= '\f') ||
          lookahead == ' ' ||
          lookahead == 0x200b ||
          lookahead == 0x2060 ||
          lookahead == 0xfeff) SKIP(1);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(80);
      END_STATE();
    case 2:
      if (lookahead == '\r') SKIP(2);
      if (lookahead == '(') ADVANCE(32);
      if (lookahead == '/') ADVANCE(6);
      if (lookahead == '?') ADVANCE(63);
      if (lookahead == '[') ADVANCE(30);
      if (lookahead == '}') ADVANCE(29);
      if (('\t' <= lookahead && lookahead <= '\f') ||
          lookahead == ' ' ||
          lookahead == 0x200b ||
          lookahead == 0x2060 ||
          lookahead == 0xfeff) SKIP(2);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(13);
      END_STATE();
    case 3:
      if (lookahead == '\r') ADVANCE(52);
      if (lookahead == '\'') ADVANCE(44);
      if (lookahead == '/') ADVANCE(53);
      if (lookahead == '\\') ADVANCE(12);
      if (('\t' <= lookahead && lookahead <= '\f') ||
          lookahead == ' ' ||
          lookahead == 0x200b ||
          lookahead == 0x2060 ||
          lookahead == 0xfeff) ADVANCE(52);
      if (lookahead != 0) ADVANCE(56);
      END_STATE();
    case 4:
      if (lookahead == '\r') ADVANCE(46);
      if (lookahead == '"') ADVANCE(43);
      if (lookahead == '/') ADVANCE(47);
      if (lookahead == '\\') ADVANCE(12);
      if (('\t' <= lookahead && lookahead <= '\f') ||
          lookahead == ' ' ||
          lookahead == 0x200b ||
          lookahead == 0x2060 ||
          lookahead == 0xfeff) ADVANCE(46);
      if (lookahead != 0) ADVANCE(50);
      END_STATE();
    case 5:
      if (lookahead == '\r') ADVANCE(64);
      if (lookahead == '/') ADVANCE(42);
      if (lookahead == '\\') ADVANCE(12);
      if (('\t' <= lookahead && lookahead <= '\f') ||
          lookahead == ' ' ||
          lookahead == 0x200b ||
          lookahead == 0x2060 ||
          lookahead == 0xfeff) ADVANCE(64);
      if (lookahead != 0) ADVANCE(65);
      END_STATE();
    case 6:
      if (lookahead == '*') ADVANCE(8);
      if (lookahead == '/') ADVANCE(82);
      END_STATE();
    case 7:
      if (lookahead == '*') ADVANCE(7);
      if (lookahead == '/') ADVANCE(81);
      if (lookahead != 0) ADVANCE(8);
      END_STATE();
    case 8:
      if (lookahead == '*') ADVANCE(7);
      if (lookahead != 0) ADVANCE(8);
      END_STATE();
    case 9:
      if (lookahead == '.') ADVANCE(37);
      END_STATE();
    case 10:
      if (lookahead == '=') ADVANCE(74);
      END_STATE();
    case 11:
      if (lookahead == '=') ADVANCE(73);
      END_STATE();
    case 12:
      if (lookahead == 'U') ADVANCE(21);
      if (lookahead == 'u') ADVANCE(17);
      if (lookahead == 'x') ADVANCE(15);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(59);
      if (lookahead != 0) ADVANCE(57);
      END_STATE();
    case 13:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(60);
      END_STATE();
    case 14:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(57);
      END_STATE();
    case 15:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(14);
      END_STATE();
    case 16:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(15);
      END_STATE();
    case 17:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(16);
      END_STATE();
    case 18:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(17);
      END_STATE();
    case 19:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(18);
      END_STATE();
    case 20:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(19);
      END_STATE();
    case 21:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(20);
      END_STATE();
    case 22:
      if (eof) ADVANCE(24);
      if (lookahead == '\r') SKIP(22);
      if (lookahead == '!') ADVANCE(40);
      if (lookahead == '"') ADVANCE(43);
      if (lookahead == '#') ADVANCE(35);
      if (lookahead == '$') ADVANCE(34);
      if (lookahead == '\'') ADVANCE(44);
      if (lookahead == '(') ADVANCE(32);
      if (lookahead == '-') ADVANCE(68);
      if (lookahead == '.') ADVANCE(9);
      if (lookahead == '/') ADVANCE(6);
      if (lookahead == ':') ADVANCE(27);
      if (lookahead == '=') ADVANCE(25);
      if (lookahead == '@') ADVANCE(36);
      if (lookahead == ']') ADVANCE(31);
      if (lookahead == '{') ADVANCE(28);
      if (('\t' <= lookahead && lookahead <= '\f') ||
          lookahead == ' ' ||
          lookahead == 0x200b ||
          lookahead == 0x2060 ||
          lookahead == 0xfeff) SKIP(22);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(67);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(80);
      END_STATE();
    case 23:
      if (eof) ADVANCE(24);
      if (lookahead == '\r') SKIP(23);
      if (lookahead == '!') ADVANCE(10);
      if (lookahead == '$') ADVANCE(34);
      if (lookahead == '%') ADVANCE(71);
      if (lookahead == ')') ADVANCE(33);
      if (lookahead == '*') ADVANCE(69);
      if (lookahead == '+') ADVANCE(72);
      if (lookahead == '-') ADVANCE(68);
      if (lookahead == '.') ADVANCE(9);
      if (lookahead == '/') ADVANCE(6);
      if (lookahead == ':') ADVANCE(27);
      if (lookahead == '<') ADVANCE(75);
      if (lookahead == '=') ADVANCE(11);
      if (lookahead == '>') ADVANCE(77);
      if (lookahead == '[') ADVANCE(30);
      if (lookahead == '\\') ADVANCE(70);
      if (lookahead == ']') ADVANCE(31);
      if (lookahead == '}') ADVANCE(29);
      if (('\t' <= lookahead && lookahead <= '\f') ||
          lookahead == ' ' ||
          lookahead == 0x200b ||
          lookahead == 0x2060 ||
          lookahead == 0xfeff) SKIP(23);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(80);
      END_STATE();
    case 24:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 25:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 26:
      ACCEPT_TOKEN(anon_sym_EQ);
      if (lookahead == '=') ADVANCE(73);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(anon_sym_DOLLAR);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(anon_sym_POUND);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(anon_sym_AT);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(anon_sym_DOT_DOT);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(anon_sym_PIPE);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(anon_sym_BANG);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(anon_sym_BANG);
      if (lookahead == '=') ADVANCE(74);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(anon_sym_SLASH);
      if (lookahead == '*') ADVANCE(8);
      if (lookahead == '/') ADVANCE(82);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(aux_sym_double_quoted_string_token1);
      if (lookahead == '\n') ADVANCE(50);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(45);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(aux_sym_double_quoted_string_token1);
      if (lookahead == '\r') ADVANCE(46);
      if (lookahead == '/') ADVANCE(47);
      if (('\t' <= lookahead && lookahead <= '\f') ||
          lookahead == ' ' ||
          lookahead == 0x200b ||
          lookahead == 0x2060 ||
          lookahead == 0xfeff) ADVANCE(46);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(50);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(aux_sym_double_quoted_string_token1);
      if (lookahead == '*') ADVANCE(49);
      if (lookahead == '/') ADVANCE(45);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(50);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(aux_sym_double_quoted_string_token1);
      if (lookahead == '*') ADVANCE(48);
      if (lookahead == '/') ADVANCE(50);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(49);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(aux_sym_double_quoted_string_token1);
      if (lookahead == '*') ADVANCE(48);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(49);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(aux_sym_double_quoted_string_token1);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(50);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(aux_sym_single_quoted_string_token1);
      if (lookahead == '\n') ADVANCE(56);
      if (lookahead != 0 &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(51);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(aux_sym_single_quoted_string_token1);
      if (lookahead == '\r') ADVANCE(52);
      if (lookahead == '/') ADVANCE(53);
      if (('\t' <= lookahead && lookahead <= '\f') ||
          lookahead == ' ' ||
          lookahead == 0x200b ||
          lookahead == 0x2060 ||
          lookahead == 0xfeff) ADVANCE(52);
      if (lookahead != 0 &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(56);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(aux_sym_single_quoted_string_token1);
      if (lookahead == '*') ADVANCE(55);
      if (lookahead == '/') ADVANCE(51);
      if (lookahead != 0 &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(56);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(aux_sym_single_quoted_string_token1);
      if (lookahead == '*') ADVANCE(54);
      if (lookahead == '/') ADVANCE(56);
      if (lookahead != 0 &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(55);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(aux_sym_single_quoted_string_token1);
      if (lookahead == '*') ADVANCE(54);
      if (lookahead != 0 &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(55);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(aux_sym_single_quoted_string_token1);
      if (lookahead != 0 &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(56);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(sym_escape_sequence);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(57);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(58);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(sym_hex_byte);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(sym_hex_byte);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(67);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(sym_hex_byte);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(80);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(sym_hex_wildcard);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(aux_sym_regex_string_content_token1);
      if (lookahead == '\r') ADVANCE(64);
      if (('\t' <= lookahead && lookahead <= '\f') ||
          lookahead == ' ' ||
          lookahead == 0x200b ||
          lookahead == 0x2060 ||
          lookahead == 0xfeff) ADVANCE(64);
      if (lookahead != 0 &&
          lookahead != '/' &&
          lookahead != '\\') ADVANCE(65);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(aux_sym_regex_string_content_token1);
      if (lookahead != 0 &&
          lookahead != '/' &&
          lookahead != '\\') ADVANCE(65);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(aux_sym_integer_literal_token1);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(61);
      if (('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(60);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(aux_sym_integer_literal_token1);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(67);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(anon_sym_STAR);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(anon_sym_BSLASH);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(anon_sym_PERCENT);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(anon_sym_PLUS);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(anon_sym_EQ_EQ);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(anon_sym_BANG_EQ);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '=') ADVANCE(76);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(anon_sym_LT_EQ);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(anon_sym_GT);
      if (lookahead == '=') ADVANCE(78);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(anon_sym_GT_EQ);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(62);
      if (('G' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(80);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(80);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(82);
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
      if (lookahead == '\r') SKIP(0);
      if (lookahead == 'G') ADVANCE(1);
      if (lookahead == 'K') ADVANCE(2);
      if (lookahead == 'M') ADVANCE(3);
      if (lookahead == 'a') ADVANCE(4);
      if (lookahead == 'b') ADVANCE(5);
      if (lookahead == 'c') ADVANCE(6);
      if (lookahead == 'e') ADVANCE(7);
      if (lookahead == 'f') ADVANCE(8);
      if (lookahead == 'g') ADVANCE(9);
      if (lookahead == 'i') ADVANCE(10);
      if (lookahead == 'm') ADVANCE(11);
      if (lookahead == 'n') ADVANCE(12);
      if (lookahead == 'o') ADVANCE(13);
      if (lookahead == 'p') ADVANCE(14);
      if (lookahead == 'r') ADVANCE(15);
      if (lookahead == 's') ADVANCE(16);
      if (lookahead == 't') ADVANCE(17);
      if (lookahead == 'w') ADVANCE(18);
      if (lookahead == 'x') ADVANCE(19);
      if (('\t' <= lookahead && lookahead <= '\f') ||
          lookahead == ' ' ||
          lookahead == 0x200b ||
          lookahead == 0x2060 ||
          lookahead == 0xfeff) SKIP(0);
      END_STATE();
    case 1:
      if (lookahead == 'B') ADVANCE(20);
      END_STATE();
    case 2:
      if (lookahead == 'B') ADVANCE(21);
      END_STATE();
    case 3:
      if (lookahead == 'B') ADVANCE(22);
      END_STATE();
    case 4:
      if (lookahead == 'l') ADVANCE(23);
      if (lookahead == 'n') ADVANCE(24);
      if (lookahead == 's') ADVANCE(25);
      END_STATE();
    case 5:
      if (lookahead == 'a') ADVANCE(26);
      END_STATE();
    case 6:
      if (lookahead == 'o') ADVANCE(27);
      END_STATE();
    case 7:
      if (lookahead == 'n') ADVANCE(28);
      END_STATE();
    case 8:
      if (lookahead == 'a') ADVANCE(29);
      if (lookahead == 'i') ADVANCE(30);
      if (lookahead == 'o') ADVANCE(31);
      if (lookahead == 'u') ADVANCE(32);
      END_STATE();
    case 9:
      if (lookahead == 'l') ADVANCE(33);
      END_STATE();
    case 10:
      if (lookahead == 'c') ADVANCE(34);
      if (lookahead == 'e') ADVANCE(35);
      if (lookahead == 'm') ADVANCE(36);
      if (lookahead == 'n') ADVANCE(37);
      if (lookahead == 's') ADVANCE(38);
      END_STATE();
    case 11:
      if (lookahead == 'a') ADVANCE(39);
      if (lookahead == 'e') ADVANCE(40);
      END_STATE();
    case 12:
      if (lookahead == 'o') ADVANCE(41);
      END_STATE();
    case 13:
      if (lookahead == 'f') ADVANCE(42);
      if (lookahead == 'r') ADVANCE(43);
      END_STATE();
    case 14:
      if (lookahead == 'r') ADVANCE(44);
      END_STATE();
    case 15:
      if (lookahead == 'u') ADVANCE(45);
      END_STATE();
    case 16:
      if (lookahead == 't') ADVANCE(46);
      END_STATE();
    case 17:
      if (lookahead == 'h') ADVANCE(47);
      if (lookahead == 'r') ADVANCE(48);
      END_STATE();
    case 18:
      if (lookahead == 'i') ADVANCE(49);
      END_STATE();
    case 19:
      if (lookahead == 'o') ADVANCE(50);
      END_STATE();
    case 20:
      ACCEPT_TOKEN(anon_sym_GB);
      END_STATE();
    case 21:
      ACCEPT_TOKEN(anon_sym_KB);
      END_STATE();
    case 22:
      ACCEPT_TOKEN(anon_sym_MB);
      END_STATE();
    case 23:
      if (lookahead == 'l') ADVANCE(51);
      END_STATE();
    case 24:
      if (lookahead == 'd') ADVANCE(52);
      if (lookahead == 'y') ADVANCE(53);
      END_STATE();
    case 25:
      if (lookahead == 'c') ADVANCE(54);
      END_STATE();
    case 26:
      if (lookahead == 's') ADVANCE(55);
      END_STATE();
    case 27:
      if (lookahead == 'n') ADVANCE(56);
      END_STATE();
    case 28:
      if (lookahead == 'd') ADVANCE(57);
      if (lookahead == 't') ADVANCE(58);
      END_STATE();
    case 29:
      if (lookahead == 'l') ADVANCE(59);
      END_STATE();
    case 30:
      if (lookahead == 'l') ADVANCE(60);
      END_STATE();
    case 31:
      if (lookahead == 'r') ADVANCE(61);
      END_STATE();
    case 32:
      if (lookahead == 'l') ADVANCE(62);
      END_STATE();
    case 33:
      if (lookahead == 'o') ADVANCE(63);
      END_STATE();
    case 34:
      if (lookahead == 'o') ADVANCE(64);
      END_STATE();
    case 35:
      if (lookahead == 'n') ADVANCE(65);
      END_STATE();
    case 36:
      if (lookahead == 'a') ADVANCE(66);
      if (lookahead == 'p') ADVANCE(67);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(anon_sym_in);
      if (lookahead == 'c') ADVANCE(68);
      END_STATE();
    case 38:
      if (lookahead == 't') ADVANCE(69);
      END_STATE();
    case 39:
      if (lookahead == 't') ADVANCE(70);
      END_STATE();
    case 40:
      if (lookahead == 't') ADVANCE(71);
      END_STATE();
    case 41:
      if (lookahead == 'c') ADVANCE(72);
      if (lookahead == 'n') ADVANCE(73);
      if (lookahead == 't') ADVANCE(74);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(anon_sym_of);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(anon_sym_or);
      END_STATE();
    case 44:
      if (lookahead == 'i') ADVANCE(75);
      END_STATE();
    case 45:
      if (lookahead == 'l') ADVANCE(76);
      END_STATE();
    case 46:
      if (lookahead == 'a') ADVANCE(77);
      if (lookahead == 'r') ADVANCE(78);
      END_STATE();
    case 47:
      if (lookahead == 'e') ADVANCE(79);
      END_STATE();
    case 48:
      if (lookahead == 'u') ADVANCE(80);
      END_STATE();
    case 49:
      if (lookahead == 'd') ADVANCE(81);
      END_STATE();
    case 50:
      if (lookahead == 'r') ADVANCE(82);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(anon_sym_all);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(anon_sym_and);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(anon_sym_any);
      END_STATE();
    case 54:
      if (lookahead == 'i') ADVANCE(83);
      END_STATE();
    case 55:
      if (lookahead == 'e') ADVANCE(84);
      END_STATE();
    case 56:
      if (lookahead == 'd') ADVANCE(85);
      if (lookahead == 't') ADVANCE(86);
      END_STATE();
    case 57:
      if (lookahead == 's') ADVANCE(87);
      END_STATE();
    case 58:
      if (lookahead == 'r') ADVANCE(88);
      END_STATE();
    case 59:
      if (lookahead == 's') ADVANCE(89);
      END_STATE();
    case 60:
      if (lookahead == 'e') ADVANCE(90);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(anon_sym_for);
      END_STATE();
    case 62:
      if (lookahead == 'l') ADVANCE(91);
      END_STATE();
    case 63:
      if (lookahead == 'b') ADVANCE(92);
      END_STATE();
    case 64:
      if (lookahead == 'n') ADVANCE(93);
      END_STATE();
    case 65:
      if (lookahead == 'd') ADVANCE(94);
      END_STATE();
    case 66:
      if (lookahead == 't') ADVANCE(95);
      END_STATE();
    case 67:
      if (lookahead == 'o') ADVANCE(96);
      END_STATE();
    case 68:
      if (lookahead == 'l') ADVANCE(97);
      END_STATE();
    case 69:
      if (lookahead == 'a') ADVANCE(98);
      END_STATE();
    case 70:
      if (lookahead == 'c') ADVANCE(99);
      END_STATE();
    case 71:
      if (lookahead == 'a') ADVANCE(100);
      END_STATE();
    case 72:
      if (lookahead == 'a') ADVANCE(101);
      END_STATE();
    case 73:
      if (lookahead == 'e') ADVANCE(102);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(anon_sym_not);
      END_STATE();
    case 75:
      if (lookahead == 'v') ADVANCE(103);
      END_STATE();
    case 76:
      if (lookahead == 'e') ADVANCE(104);
      END_STATE();
    case 77:
      if (lookahead == 'r') ADVANCE(105);
      END_STATE();
    case 78:
      if (lookahead == 'i') ADVANCE(106);
      END_STATE();
    case 79:
      if (lookahead == 'm') ADVANCE(107);
      END_STATE();
    case 80:
      if (lookahead == 'e') ADVANCE(108);
      END_STATE();
    case 81:
      if (lookahead == 'e') ADVANCE(109);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(anon_sym_xor);
      END_STATE();
    case 83:
      if (lookahead == 'i') ADVANCE(110);
      END_STATE();
    case 84:
      if (lookahead == '6') ADVANCE(111);
      END_STATE();
    case 85:
      if (lookahead == 'i') ADVANCE(112);
      END_STATE();
    case 86:
      if (lookahead == 'a') ADVANCE(113);
      END_STATE();
    case 87:
      if (lookahead == 'w') ADVANCE(114);
      END_STATE();
    case 88:
      if (lookahead == 'y') ADVANCE(115);
      END_STATE();
    case 89:
      if (lookahead == 'e') ADVANCE(116);
      END_STATE();
    case 90:
      if (lookahead == 's') ADVANCE(117);
      END_STATE();
    case 91:
      if (lookahead == 'w') ADVANCE(118);
      END_STATE();
    case 92:
      if (lookahead == 'a') ADVANCE(119);
      END_STATE();
    case 93:
      if (lookahead == 't') ADVANCE(120);
      END_STATE();
    case 94:
      if (lookahead == 's') ADVANCE(121);
      END_STATE();
    case 95:
      if (lookahead == 'c') ADVANCE(122);
      END_STATE();
    case 96:
      if (lookahead == 'r') ADVANCE(123);
      END_STATE();
    case 97:
      if (lookahead == 'u') ADVANCE(124);
      END_STATE();
    case 98:
      if (lookahead == 'r') ADVANCE(125);
      END_STATE();
    case 99:
      if (lookahead == 'h') ADVANCE(126);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(anon_sym_meta);
      END_STATE();
    case 101:
      if (lookahead == 's') ADVANCE(127);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(anon_sym_none);
      END_STATE();
    case 103:
      if (lookahead == 'a') ADVANCE(128);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(anon_sym_rule);
      END_STATE();
    case 105:
      if (lookahead == 't') ADVANCE(129);
      END_STATE();
    case 106:
      if (lookahead == 'n') ADVANCE(130);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(anon_sym_them);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(anon_sym_true);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(anon_sym_wide);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(anon_sym_ascii);
      END_STATE();
    case 111:
      if (lookahead == '4') ADVANCE(131);
      END_STATE();
    case 112:
      if (lookahead == 't') ADVANCE(132);
      END_STATE();
    case 113:
      if (lookahead == 'i') ADVANCE(133);
      END_STATE();
    case 114:
      if (lookahead == 'i') ADVANCE(134);
      END_STATE();
    case 115:
      if (lookahead == 'p') ADVANCE(135);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(anon_sym_false);
      END_STATE();
    case 117:
      if (lookahead == 'i') ADVANCE(136);
      END_STATE();
    case 118:
      if (lookahead == 'o') ADVANCE(137);
      END_STATE();
    case 119:
      if (lookahead == 'l') ADVANCE(138);
      END_STATE();
    case 120:
      if (lookahead == 'a') ADVANCE(139);
      END_STATE();
    case 121:
      if (lookahead == 'w') ADVANCE(140);
      END_STATE();
    case 122:
      if (lookahead == 'h') ADVANCE(141);
      END_STATE();
    case 123:
      if (lookahead == 't') ADVANCE(142);
      END_STATE();
    case 124:
      if (lookahead == 'd') ADVANCE(143);
      END_STATE();
    case 125:
      if (lookahead == 't') ADVANCE(144);
      END_STATE();
    case 126:
      if (lookahead == 'e') ADVANCE(145);
      END_STATE();
    case 127:
      if (lookahead == 'e') ADVANCE(146);
      END_STATE();
    case 128:
      if (lookahead == 't') ADVANCE(147);
      END_STATE();
    case 129:
      if (lookahead == 's') ADVANCE(148);
      END_STATE();
    case 130:
      if (lookahead == 'g') ADVANCE(149);
      END_STATE();
    case 131:
      ACCEPT_TOKEN(anon_sym_base64);
      if (lookahead == 'w') ADVANCE(150);
      END_STATE();
    case 132:
      if (lookahead == 'i') ADVANCE(151);
      END_STATE();
    case 133:
      if (lookahead == 'n') ADVANCE(152);
      END_STATE();
    case 134:
      if (lookahead == 't') ADVANCE(153);
      END_STATE();
    case 135:
      if (lookahead == 'o') ADVANCE(154);
      END_STATE();
    case 136:
      if (lookahead == 'z') ADVANCE(155);
      END_STATE();
    case 137:
      if (lookahead == 'r') ADVANCE(156);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(anon_sym_global);
      END_STATE();
    case 139:
      if (lookahead == 'i') ADVANCE(157);
      END_STATE();
    case 140:
      if (lookahead == 'i') ADVANCE(158);
      END_STATE();
    case 141:
      if (lookahead == 'e') ADVANCE(159);
      END_STATE();
    case 142:
      ACCEPT_TOKEN(anon_sym_import);
      END_STATE();
    case 143:
      if (lookahead == 'e') ADVANCE(160);
      END_STATE();
    case 144:
      if (lookahead == 's') ADVANCE(161);
      END_STATE();
    case 145:
      if (lookahead == 's') ADVANCE(162);
      END_STATE();
    case 146:
      ACCEPT_TOKEN(anon_sym_nocase);
      END_STATE();
    case 147:
      if (lookahead == 'e') ADVANCE(163);
      END_STATE();
    case 148:
      if (lookahead == 'w') ADVANCE(164);
      END_STATE();
    case 149:
      if (lookahead == 's') ADVANCE(165);
      END_STATE();
    case 150:
      if (lookahead == 'i') ADVANCE(166);
      END_STATE();
    case 151:
      if (lookahead == 'o') ADVANCE(167);
      END_STATE();
    case 152:
      if (lookahead == 's') ADVANCE(168);
      END_STATE();
    case 153:
      if (lookahead == 'h') ADVANCE(169);
      END_STATE();
    case 154:
      if (lookahead == 'i') ADVANCE(170);
      END_STATE();
    case 155:
      if (lookahead == 'e') ADVANCE(171);
      END_STATE();
    case 156:
      if (lookahead == 'd') ADVANCE(172);
      END_STATE();
    case 157:
      if (lookahead == 'n') ADVANCE(173);
      END_STATE();
    case 158:
      if (lookahead == 't') ADVANCE(174);
      END_STATE();
    case 159:
      if (lookahead == 's') ADVANCE(175);
      END_STATE();
    case 160:
      ACCEPT_TOKEN(anon_sym_include);
      END_STATE();
    case 161:
      if (lookahead == 'w') ADVANCE(176);
      END_STATE();
    case 162:
      ACCEPT_TOKEN(anon_sym_matches);
      END_STATE();
    case 163:
      ACCEPT_TOKEN(anon_sym_private);
      END_STATE();
    case 164:
      if (lookahead == 'i') ADVANCE(177);
      END_STATE();
    case 165:
      ACCEPT_TOKEN(anon_sym_strings);
      END_STATE();
    case 166:
      if (lookahead == 'd') ADVANCE(178);
      END_STATE();
    case 167:
      if (lookahead == 'n') ADVANCE(179);
      END_STATE();
    case 168:
      ACCEPT_TOKEN(anon_sym_contains);
      END_STATE();
    case 169:
      ACCEPT_TOKEN(anon_sym_endswith);
      END_STATE();
    case 170:
      if (lookahead == 'n') ADVANCE(180);
      END_STATE();
    case 171:
      ACCEPT_TOKEN(sym_filesize_keyword);
      END_STATE();
    case 172:
      ACCEPT_TOKEN(anon_sym_fullword);
      END_STATE();
    case 173:
      if (lookahead == 's') ADVANCE(181);
      END_STATE();
    case 174:
      if (lookahead == 'h') ADVANCE(182);
      END_STATE();
    case 175:
      ACCEPT_TOKEN(anon_sym_imatches);
      END_STATE();
    case 176:
      if (lookahead == 'i') ADVANCE(183);
      END_STATE();
    case 177:
      if (lookahead == 't') ADVANCE(184);
      END_STATE();
    case 178:
      if (lookahead == 'e') ADVANCE(185);
      END_STATE();
    case 179:
      ACCEPT_TOKEN(anon_sym_condition);
      END_STATE();
    case 180:
      if (lookahead == 't') ADVANCE(186);
      END_STATE();
    case 181:
      ACCEPT_TOKEN(anon_sym_icontains);
      END_STATE();
    case 182:
      ACCEPT_TOKEN(anon_sym_iendswith);
      END_STATE();
    case 183:
      if (lookahead == 't') ADVANCE(187);
      END_STATE();
    case 184:
      if (lookahead == 'h') ADVANCE(188);
      END_STATE();
    case 185:
      ACCEPT_TOKEN(anon_sym_base64wide);
      END_STATE();
    case 186:
      ACCEPT_TOKEN(sym_entrypoint_keyword);
      END_STATE();
    case 187:
      if (lookahead == 'h') ADVANCE(189);
      END_STATE();
    case 188:
      ACCEPT_TOKEN(anon_sym_startswith);
      END_STATE();
    case 189:
      ACCEPT_TOKEN(anon_sym_istartswith);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 22},
  [2] = {.lex_state = 22},
  [3] = {.lex_state = 22},
  [4] = {.lex_state = 22},
  [5] = {.lex_state = 22},
  [6] = {.lex_state = 22},
  [7] = {.lex_state = 22},
  [8] = {.lex_state = 22},
  [9] = {.lex_state = 22},
  [10] = {.lex_state = 22},
  [11] = {.lex_state = 22},
  [12] = {.lex_state = 23},
  [13] = {.lex_state = 23},
  [14] = {.lex_state = 23},
  [15] = {.lex_state = 23},
  [16] = {.lex_state = 23},
  [17] = {.lex_state = 23},
  [18] = {.lex_state = 23},
  [19] = {.lex_state = 23},
  [20] = {.lex_state = 1},
  [21] = {.lex_state = 23},
  [22] = {.lex_state = 1},
  [23] = {.lex_state = 23},
  [24] = {.lex_state = 23},
  [25] = {.lex_state = 23},
  [26] = {.lex_state = 23},
  [27] = {.lex_state = 23},
  [28] = {.lex_state = 23},
  [29] = {.lex_state = 23},
  [30] = {.lex_state = 23},
  [31] = {.lex_state = 23},
  [32] = {.lex_state = 23},
  [33] = {.lex_state = 23},
  [34] = {.lex_state = 23},
  [35] = {.lex_state = 23},
  [36] = {.lex_state = 23},
  [37] = {.lex_state = 23},
  [38] = {.lex_state = 23},
  [39] = {.lex_state = 23},
  [40] = {.lex_state = 23},
  [41] = {.lex_state = 23},
  [42] = {.lex_state = 23},
  [43] = {.lex_state = 23},
  [44] = {.lex_state = 23},
  [45] = {.lex_state = 23},
  [46] = {.lex_state = 0},
  [47] = {.lex_state = 22},
  [48] = {.lex_state = 22},
  [49] = {.lex_state = 22},
  [50] = {.lex_state = 22},
  [51] = {.lex_state = 2},
  [52] = {.lex_state = 22},
  [53] = {.lex_state = 22},
  [54] = {.lex_state = 22},
  [55] = {.lex_state = 22},
  [56] = {.lex_state = 22},
  [57] = {.lex_state = 2},
  [58] = {.lex_state = 2},
  [59] = {.lex_state = 22},
  [60] = {.lex_state = 22},
  [61] = {.lex_state = 22},
  [62] = {.lex_state = 22},
  [63] = {.lex_state = 0},
  [64] = {.lex_state = 0},
  [65] = {.lex_state = 0},
  [66] = {.lex_state = 22},
  [67] = {.lex_state = 22},
  [68] = {.lex_state = 22},
  [69] = {.lex_state = 0},
  [70] = {.lex_state = 22},
  [71] = {.lex_state = 0},
  [72] = {.lex_state = 22},
  [73] = {.lex_state = 22},
  [74] = {.lex_state = 22},
  [75] = {.lex_state = 22},
  [76] = {.lex_state = 0},
  [77] = {.lex_state = 22},
  [78] = {.lex_state = 22},
  [79] = {.lex_state = 22},
  [80] = {.lex_state = 22},
  [81] = {.lex_state = 22},
  [82] = {.lex_state = 22},
  [83] = {.lex_state = 22},
  [84] = {.lex_state = 0},
  [85] = {.lex_state = 3},
  [86] = {.lex_state = 22},
  [87] = {.lex_state = 0},
  [88] = {.lex_state = 0},
  [89] = {.lex_state = 2},
  [90] = {.lex_state = 2},
  [91] = {.lex_state = 0},
  [92] = {.lex_state = 22},
  [93] = {.lex_state = 2},
  [94] = {.lex_state = 2},
  [95] = {.lex_state = 4},
  [96] = {.lex_state = 3},
  [97] = {.lex_state = 2},
  [98] = {.lex_state = 0},
  [99] = {.lex_state = 4},
  [100] = {.lex_state = 5},
  [101] = {.lex_state = 22},
  [102] = {.lex_state = 5},
  [103] = {.lex_state = 22},
  [104] = {.lex_state = 4},
  [105] = {.lex_state = 22},
  [106] = {.lex_state = 22},
  [107] = {.lex_state = 22},
  [108] = {.lex_state = 0},
  [109] = {.lex_state = 0},
  [110] = {.lex_state = 22},
  [111] = {.lex_state = 5},
  [112] = {.lex_state = 3},
  [113] = {.lex_state = 0},
  [114] = {.lex_state = 0},
  [115] = {.lex_state = 0},
  [116] = {.lex_state = 0},
  [117] = {.lex_state = 22},
  [118] = {.lex_state = 0},
  [119] = {.lex_state = 0},
  [120] = {.lex_state = 22},
  [121] = {.lex_state = 22},
  [122] = {.lex_state = 0},
  [123] = {.lex_state = 22},
  [124] = {.lex_state = 0},
  [125] = {.lex_state = 22},
  [126] = {.lex_state = 22},
  [127] = {.lex_state = 0},
  [128] = {.lex_state = 0},
  [129] = {.lex_state = 0},
  [130] = {.lex_state = 22},
  [131] = {.lex_state = 22},
  [132] = {.lex_state = 22},
  [133] = {.lex_state = 22},
  [134] = {.lex_state = 0},
  [135] = {.lex_state = 0},
  [136] = {.lex_state = 0},
  [137] = {.lex_state = 0},
  [138] = {.lex_state = 0},
  [139] = {.lex_state = 22},
  [140] = {.lex_state = 22},
  [141] = {.lex_state = 0},
  [142] = {.lex_state = 22},
  [143] = {.lex_state = 0},
  [144] = {.lex_state = 22},
  [145] = {.lex_state = 0},
  [146] = {.lex_state = 0},
  [147] = {.lex_state = 0},
  [148] = {.lex_state = 0},
  [149] = {.lex_state = 0},
  [150] = {.lex_state = 22},
  [151] = {.lex_state = 0},
  [152] = {.lex_state = 0},
  [153] = {.lex_state = 0},
  [154] = {.lex_state = 22},
  [155] = {.lex_state = 0},
  [156] = {.lex_state = 0},
  [157] = {.lex_state = 22},
  [158] = {.lex_state = 0},
  [159] = {.lex_state = 22},
  [160] = {.lex_state = 22},
  [161] = {.lex_state = 22},
  [162] = {.lex_state = 0},
  [163] = {.lex_state = 2},
  [164] = {.lex_state = 2},
  [165] = {.lex_state = 22},
  [166] = {.lex_state = 22},
  [167] = {.lex_state = 22},
  [168] = {.lex_state = 22},
  [169] = {.lex_state = 22},
  [170] = {.lex_state = 22},
  [171] = {.lex_state = 0},
  [172] = {.lex_state = 22},
  [173] = {.lex_state = 22},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_DOLLAR] = ACTIONS(1),
    [anon_sym_POUND] = ACTIONS(1),
    [anon_sym_AT] = ACTIONS(1),
    [anon_sym_DOT_DOT] = ACTIONS(1),
    [anon_sym_PIPE] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_BANG] = ACTIONS(1),
    [anon_sym_SLASH] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [anon_sym_SQUOTE] = ACTIONS(1),
    [anon_sym_import] = ACTIONS(1),
    [anon_sym_include] = ACTIONS(1),
    [anon_sym_private] = ACTIONS(1),
    [anon_sym_global] = ACTIONS(1),
    [anon_sym_rule] = ACTIONS(1),
    [anon_sym_meta] = ACTIONS(1),
    [anon_sym_strings] = ACTIONS(1),
    [sym_hex_byte] = ACTIONS(1),
    [sym_hex_wildcard] = ACTIONS(1),
    [anon_sym_nocase] = ACTIONS(1),
    [anon_sym_ascii] = ACTIONS(1),
    [anon_sym_wide] = ACTIONS(1),
    [anon_sym_fullword] = ACTIONS(1),
    [anon_sym_base64] = ACTIONS(1),
    [anon_sym_base64wide] = ACTIONS(1),
    [anon_sym_xor] = ACTIONS(1),
    [anon_sym_condition] = ACTIONS(1),
    [sym_filesize_keyword] = ACTIONS(1),
    [sym_entrypoint_keyword] = ACTIONS(1),
    [anon_sym_KB] = ACTIONS(1),
    [anon_sym_MB] = ACTIONS(1),
    [anon_sym_GB] = ACTIONS(1),
    [aux_sym_integer_literal_token1] = ACTIONS(1),
    [anon_sym_for] = ACTIONS(1),
    [anon_sym_of] = ACTIONS(1),
    [anon_sym_in] = ACTIONS(1),
    [anon_sym_all] = ACTIONS(1),
    [anon_sym_any] = ACTIONS(1),
    [anon_sym_none] = ACTIONS(1),
    [anon_sym_them] = ACTIONS(1),
    [anon_sym_not] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [anon_sym_STAR] = ACTIONS(1),
    [anon_sym_BSLASH] = ACTIONS(1),
    [anon_sym_PERCENT] = ACTIONS(1),
    [anon_sym_PLUS] = ACTIONS(1),
    [anon_sym_EQ_EQ] = ACTIONS(1),
    [anon_sym_BANG_EQ] = ACTIONS(1),
    [anon_sym_LT] = ACTIONS(1),
    [anon_sym_LT_EQ] = ACTIONS(1),
    [anon_sym_GT] = ACTIONS(1),
    [anon_sym_GT_EQ] = ACTIONS(1),
    [anon_sym_contains] = ACTIONS(1),
    [anon_sym_matches] = ACTIONS(1),
    [anon_sym_icontains] = ACTIONS(1),
    [anon_sym_imatches] = ACTIONS(1),
    [anon_sym_startswith] = ACTIONS(1),
    [anon_sym_istartswith] = ACTIONS(1),
    [anon_sym_endswith] = ACTIONS(1),
    [anon_sym_iendswith] = ACTIONS(1),
    [anon_sym_and] = ACTIONS(1),
    [anon_sym_or] = ACTIONS(1),
    [anon_sym_true] = ACTIONS(1),
    [anon_sym_false] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
  },
  [1] = {
    [sym_source_file] = STATE(162),
    [sym_import_statement] = STATE(52),
    [sym_include_statement] = STATE(52),
    [sym_rule_definition] = STATE(52),
    [aux_sym_source_file_repeat1] = STATE(52),
    [ts_builtin_sym_end] = ACTIONS(5),
    [anon_sym_import] = ACTIONS(7),
    [anon_sym_include] = ACTIONS(9),
    [anon_sym_private] = ACTIONS(11),
    [anon_sym_global] = ACTIONS(13),
    [anon_sym_rule] = ACTIONS(15),
    [sym_comment] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 26,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(19), 1,
      anon_sym_LPAREN,
    ACTIONS(21), 1,
      anon_sym_DOLLAR,
    ACTIONS(23), 1,
      anon_sym_POUND,
    ACTIONS(25), 1,
      anon_sym_AT,
    ACTIONS(27), 1,
      anon_sym_BANG,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    ACTIONS(33), 1,
      aux_sym_integer_literal_token1,
    ACTIONS(35), 1,
      anon_sym_for,
    ACTIONS(39), 1,
      anon_sym_not,
    ACTIONS(41), 1,
      anon_sym_DASH,
    STATE(5), 1,
      sym__lparen,
    STATE(20), 1,
      sym__dollar,
    STATE(28), 1,
      sym_integer_literal,
    STATE(85), 1,
      sym__squote,
    STATE(99), 1,
      sym__quote,
    STATE(115), 1,
      sym__hash,
    STATE(122), 1,
      sym__at,
    STATE(124), 1,
      sym__bang,
    STATE(161), 1,
      sym_quantifier,
    ACTIONS(43), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(17), 2,
      sym_double_quoted_string,
      sym_single_quoted_string,
    ACTIONS(17), 3,
      sym_filesize_keyword,
      sym_entrypoint_keyword,
      sym_identifier,
    ACTIONS(37), 3,
      anon_sym_all,
      anon_sym_any,
      anon_sym_none,
    STATE(45), 13,
      sym_string_identifier,
      sym__expression,
      sym_string_count,
      sym_string_offset,
      sym_string_length,
      sym_for_expression,
      sym_for_of_expression,
      sym_of_expression,
      sym_unary_expression,
      sym_binary_expression,
      sym_parenthesized_expression,
      sym_boolean_literal,
      sym_string_literal,
  [97] = 26,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(19), 1,
      anon_sym_LPAREN,
    ACTIONS(21), 1,
      anon_sym_DOLLAR,
    ACTIONS(23), 1,
      anon_sym_POUND,
    ACTIONS(25), 1,
      anon_sym_AT,
    ACTIONS(27), 1,
      anon_sym_BANG,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    ACTIONS(33), 1,
      aux_sym_integer_literal_token1,
    ACTIONS(35), 1,
      anon_sym_for,
    ACTIONS(39), 1,
      anon_sym_not,
    ACTIONS(41), 1,
      anon_sym_DASH,
    STATE(5), 1,
      sym__lparen,
    STATE(20), 1,
      sym__dollar,
    STATE(28), 1,
      sym_integer_literal,
    STATE(85), 1,
      sym__squote,
    STATE(99), 1,
      sym__quote,
    STATE(115), 1,
      sym__hash,
    STATE(122), 1,
      sym__at,
    STATE(124), 1,
      sym__bang,
    STATE(161), 1,
      sym_quantifier,
    ACTIONS(43), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(17), 2,
      sym_double_quoted_string,
      sym_single_quoted_string,
    ACTIONS(37), 3,
      anon_sym_all,
      anon_sym_any,
      anon_sym_none,
    ACTIONS(45), 3,
      sym_filesize_keyword,
      sym_entrypoint_keyword,
      sym_identifier,
    STATE(32), 13,
      sym_string_identifier,
      sym__expression,
      sym_string_count,
      sym_string_offset,
      sym_string_length,
      sym_for_expression,
      sym_for_of_expression,
      sym_of_expression,
      sym_unary_expression,
      sym_binary_expression,
      sym_parenthesized_expression,
      sym_boolean_literal,
      sym_string_literal,
  [194] = 26,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(19), 1,
      anon_sym_LPAREN,
    ACTIONS(21), 1,
      anon_sym_DOLLAR,
    ACTIONS(23), 1,
      anon_sym_POUND,
    ACTIONS(25), 1,
      anon_sym_AT,
    ACTIONS(27), 1,
      anon_sym_BANG,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    ACTIONS(33), 1,
      aux_sym_integer_literal_token1,
    ACTIONS(35), 1,
      anon_sym_for,
    ACTIONS(39), 1,
      anon_sym_not,
    ACTIONS(41), 1,
      anon_sym_DASH,
    STATE(5), 1,
      sym__lparen,
    STATE(20), 1,
      sym__dollar,
    STATE(28), 1,
      sym_integer_literal,
    STATE(85), 1,
      sym__squote,
    STATE(99), 1,
      sym__quote,
    STATE(115), 1,
      sym__hash,
    STATE(122), 1,
      sym__at,
    STATE(124), 1,
      sym__bang,
    STATE(161), 1,
      sym_quantifier,
    ACTIONS(43), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(17), 2,
      sym_double_quoted_string,
      sym_single_quoted_string,
    ACTIONS(37), 3,
      anon_sym_all,
      anon_sym_any,
      anon_sym_none,
    ACTIONS(47), 3,
      sym_filesize_keyword,
      sym_entrypoint_keyword,
      sym_identifier,
    STATE(30), 13,
      sym_string_identifier,
      sym__expression,
      sym_string_count,
      sym_string_offset,
      sym_string_length,
      sym_for_expression,
      sym_for_of_expression,
      sym_of_expression,
      sym_unary_expression,
      sym_binary_expression,
      sym_parenthesized_expression,
      sym_boolean_literal,
      sym_string_literal,
  [291] = 26,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(19), 1,
      anon_sym_LPAREN,
    ACTIONS(21), 1,
      anon_sym_DOLLAR,
    ACTIONS(23), 1,
      anon_sym_POUND,
    ACTIONS(25), 1,
      anon_sym_AT,
    ACTIONS(27), 1,
      anon_sym_BANG,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    ACTIONS(33), 1,
      aux_sym_integer_literal_token1,
    ACTIONS(35), 1,
      anon_sym_for,
    ACTIONS(39), 1,
      anon_sym_not,
    ACTIONS(41), 1,
      anon_sym_DASH,
    STATE(5), 1,
      sym__lparen,
    STATE(20), 1,
      sym__dollar,
    STATE(28), 1,
      sym_integer_literal,
    STATE(85), 1,
      sym__squote,
    STATE(99), 1,
      sym__quote,
    STATE(115), 1,
      sym__hash,
    STATE(122), 1,
      sym__at,
    STATE(124), 1,
      sym__bang,
    STATE(161), 1,
      sym_quantifier,
    ACTIONS(43), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(17), 2,
      sym_double_quoted_string,
      sym_single_quoted_string,
    ACTIONS(37), 3,
      anon_sym_all,
      anon_sym_any,
      anon_sym_none,
    ACTIONS(49), 3,
      sym_filesize_keyword,
      sym_entrypoint_keyword,
      sym_identifier,
    STATE(33), 13,
      sym_string_identifier,
      sym__expression,
      sym_string_count,
      sym_string_offset,
      sym_string_length,
      sym_for_expression,
      sym_for_of_expression,
      sym_of_expression,
      sym_unary_expression,
      sym_binary_expression,
      sym_parenthesized_expression,
      sym_boolean_literal,
      sym_string_literal,
  [388] = 26,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(19), 1,
      anon_sym_LPAREN,
    ACTIONS(21), 1,
      anon_sym_DOLLAR,
    ACTIONS(23), 1,
      anon_sym_POUND,
    ACTIONS(25), 1,
      anon_sym_AT,
    ACTIONS(27), 1,
      anon_sym_BANG,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    ACTIONS(33), 1,
      aux_sym_integer_literal_token1,
    ACTIONS(35), 1,
      anon_sym_for,
    ACTIONS(39), 1,
      anon_sym_not,
    ACTIONS(41), 1,
      anon_sym_DASH,
    STATE(5), 1,
      sym__lparen,
    STATE(20), 1,
      sym__dollar,
    STATE(28), 1,
      sym_integer_literal,
    STATE(85), 1,
      sym__squote,
    STATE(99), 1,
      sym__quote,
    STATE(115), 1,
      sym__hash,
    STATE(122), 1,
      sym__at,
    STATE(124), 1,
      sym__bang,
    STATE(161), 1,
      sym_quantifier,
    ACTIONS(43), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(17), 2,
      sym_double_quoted_string,
      sym_single_quoted_string,
    ACTIONS(37), 3,
      anon_sym_all,
      anon_sym_any,
      anon_sym_none,
    ACTIONS(51), 3,
      sym_filesize_keyword,
      sym_entrypoint_keyword,
      sym_identifier,
    STATE(36), 13,
      sym_string_identifier,
      sym__expression,
      sym_string_count,
      sym_string_offset,
      sym_string_length,
      sym_for_expression,
      sym_for_of_expression,
      sym_of_expression,
      sym_unary_expression,
      sym_binary_expression,
      sym_parenthesized_expression,
      sym_boolean_literal,
      sym_string_literal,
  [485] = 26,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(19), 1,
      anon_sym_LPAREN,
    ACTIONS(21), 1,
      anon_sym_DOLLAR,
    ACTIONS(23), 1,
      anon_sym_POUND,
    ACTIONS(25), 1,
      anon_sym_AT,
    ACTIONS(27), 1,
      anon_sym_BANG,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    ACTIONS(33), 1,
      aux_sym_integer_literal_token1,
    ACTIONS(35), 1,
      anon_sym_for,
    ACTIONS(39), 1,
      anon_sym_not,
    ACTIONS(41), 1,
      anon_sym_DASH,
    STATE(5), 1,
      sym__lparen,
    STATE(20), 1,
      sym__dollar,
    STATE(28), 1,
      sym_integer_literal,
    STATE(85), 1,
      sym__squote,
    STATE(99), 1,
      sym__quote,
    STATE(115), 1,
      sym__hash,
    STATE(122), 1,
      sym__at,
    STATE(124), 1,
      sym__bang,
    STATE(161), 1,
      sym_quantifier,
    ACTIONS(43), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(17), 2,
      sym_double_quoted_string,
      sym_single_quoted_string,
    ACTIONS(37), 3,
      anon_sym_all,
      anon_sym_any,
      anon_sym_none,
    ACTIONS(53), 3,
      sym_filesize_keyword,
      sym_entrypoint_keyword,
      sym_identifier,
    STATE(34), 13,
      sym_string_identifier,
      sym__expression,
      sym_string_count,
      sym_string_offset,
      sym_string_length,
      sym_for_expression,
      sym_for_of_expression,
      sym_of_expression,
      sym_unary_expression,
      sym_binary_expression,
      sym_parenthesized_expression,
      sym_boolean_literal,
      sym_string_literal,
  [582] = 26,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(19), 1,
      anon_sym_LPAREN,
    ACTIONS(21), 1,
      anon_sym_DOLLAR,
    ACTIONS(23), 1,
      anon_sym_POUND,
    ACTIONS(25), 1,
      anon_sym_AT,
    ACTIONS(27), 1,
      anon_sym_BANG,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    ACTIONS(33), 1,
      aux_sym_integer_literal_token1,
    ACTIONS(35), 1,
      anon_sym_for,
    ACTIONS(39), 1,
      anon_sym_not,
    ACTIONS(41), 1,
      anon_sym_DASH,
    STATE(5), 1,
      sym__lparen,
    STATE(20), 1,
      sym__dollar,
    STATE(28), 1,
      sym_integer_literal,
    STATE(85), 1,
      sym__squote,
    STATE(99), 1,
      sym__quote,
    STATE(115), 1,
      sym__hash,
    STATE(122), 1,
      sym__at,
    STATE(124), 1,
      sym__bang,
    STATE(161), 1,
      sym_quantifier,
    ACTIONS(43), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(17), 2,
      sym_double_quoted_string,
      sym_single_quoted_string,
    ACTIONS(37), 3,
      anon_sym_all,
      anon_sym_any,
      anon_sym_none,
    ACTIONS(55), 3,
      sym_filesize_keyword,
      sym_entrypoint_keyword,
      sym_identifier,
    STATE(35), 13,
      sym_string_identifier,
      sym__expression,
      sym_string_count,
      sym_string_offset,
      sym_string_length,
      sym_for_expression,
      sym_for_of_expression,
      sym_of_expression,
      sym_unary_expression,
      sym_binary_expression,
      sym_parenthesized_expression,
      sym_boolean_literal,
      sym_string_literal,
  [679] = 26,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(19), 1,
      anon_sym_LPAREN,
    ACTIONS(21), 1,
      anon_sym_DOLLAR,
    ACTIONS(23), 1,
      anon_sym_POUND,
    ACTIONS(25), 1,
      anon_sym_AT,
    ACTIONS(27), 1,
      anon_sym_BANG,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    ACTIONS(33), 1,
      aux_sym_integer_literal_token1,
    ACTIONS(35), 1,
      anon_sym_for,
    ACTIONS(39), 1,
      anon_sym_not,
    ACTIONS(41), 1,
      anon_sym_DASH,
    STATE(5), 1,
      sym__lparen,
    STATE(20), 1,
      sym__dollar,
    STATE(28), 1,
      sym_integer_literal,
    STATE(85), 1,
      sym__squote,
    STATE(99), 1,
      sym__quote,
    STATE(115), 1,
      sym__hash,
    STATE(122), 1,
      sym__at,
    STATE(124), 1,
      sym__bang,
    STATE(161), 1,
      sym_quantifier,
    ACTIONS(43), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(17), 2,
      sym_double_quoted_string,
      sym_single_quoted_string,
    ACTIONS(37), 3,
      anon_sym_all,
      anon_sym_any,
      anon_sym_none,
    ACTIONS(57), 3,
      sym_filesize_keyword,
      sym_entrypoint_keyword,
      sym_identifier,
    STATE(29), 13,
      sym_string_identifier,
      sym__expression,
      sym_string_count,
      sym_string_offset,
      sym_string_length,
      sym_for_expression,
      sym_for_of_expression,
      sym_of_expression,
      sym_unary_expression,
      sym_binary_expression,
      sym_parenthesized_expression,
      sym_boolean_literal,
      sym_string_literal,
  [776] = 26,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(19), 1,
      anon_sym_LPAREN,
    ACTIONS(21), 1,
      anon_sym_DOLLAR,
    ACTIONS(23), 1,
      anon_sym_POUND,
    ACTIONS(25), 1,
      anon_sym_AT,
    ACTIONS(27), 1,
      anon_sym_BANG,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    ACTIONS(33), 1,
      aux_sym_integer_literal_token1,
    ACTIONS(35), 1,
      anon_sym_for,
    ACTIONS(39), 1,
      anon_sym_not,
    ACTIONS(41), 1,
      anon_sym_DASH,
    STATE(5), 1,
      sym__lparen,
    STATE(20), 1,
      sym__dollar,
    STATE(28), 1,
      sym_integer_literal,
    STATE(85), 1,
      sym__squote,
    STATE(99), 1,
      sym__quote,
    STATE(115), 1,
      sym__hash,
    STATE(122), 1,
      sym__at,
    STATE(124), 1,
      sym__bang,
    STATE(161), 1,
      sym_quantifier,
    ACTIONS(43), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(17), 2,
      sym_double_quoted_string,
      sym_single_quoted_string,
    ACTIONS(37), 3,
      anon_sym_all,
      anon_sym_any,
      anon_sym_none,
    ACTIONS(59), 3,
      sym_filesize_keyword,
      sym_entrypoint_keyword,
      sym_identifier,
    STATE(38), 13,
      sym_string_identifier,
      sym__expression,
      sym_string_count,
      sym_string_offset,
      sym_string_length,
      sym_for_expression,
      sym_for_of_expression,
      sym_of_expression,
      sym_unary_expression,
      sym_binary_expression,
      sym_parenthesized_expression,
      sym_boolean_literal,
      sym_string_literal,
  [873] = 26,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(19), 1,
      anon_sym_LPAREN,
    ACTIONS(21), 1,
      anon_sym_DOLLAR,
    ACTIONS(23), 1,
      anon_sym_POUND,
    ACTIONS(25), 1,
      anon_sym_AT,
    ACTIONS(27), 1,
      anon_sym_BANG,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    ACTIONS(33), 1,
      aux_sym_integer_literal_token1,
    ACTIONS(35), 1,
      anon_sym_for,
    ACTIONS(39), 1,
      anon_sym_not,
    ACTIONS(41), 1,
      anon_sym_DASH,
    STATE(5), 1,
      sym__lparen,
    STATE(20), 1,
      sym__dollar,
    STATE(28), 1,
      sym_integer_literal,
    STATE(85), 1,
      sym__squote,
    STATE(99), 1,
      sym__quote,
    STATE(115), 1,
      sym__hash,
    STATE(122), 1,
      sym__at,
    STATE(124), 1,
      sym__bang,
    STATE(161), 1,
      sym_quantifier,
    ACTIONS(43), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(17), 2,
      sym_double_quoted_string,
      sym_single_quoted_string,
    ACTIONS(37), 3,
      anon_sym_all,
      anon_sym_any,
      anon_sym_none,
    ACTIONS(61), 3,
      sym_filesize_keyword,
      sym_entrypoint_keyword,
      sym_identifier,
    STATE(43), 13,
      sym_string_identifier,
      sym__expression,
      sym_string_count,
      sym_string_offset,
      sym_string_length,
      sym_for_expression,
      sym_for_of_expression,
      sym_of_expression,
      sym_unary_expression,
      sym_binary_expression,
      sym_parenthesized_expression,
      sym_boolean_literal,
      sym_string_literal,
  [970] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(63), 13,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_DOLLAR,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
    ACTIONS(65), 27,
      anon_sym_import,
      anon_sym_include,
      anon_sym_private,
      anon_sym_global,
      anon_sym_rule,
      anon_sym_strings,
      anon_sym_nocase,
      anon_sym_ascii,
      anon_sym_wide,
      anon_sym_fullword,
      anon_sym_base64,
      anon_sym_base64wide,
      anon_sym_xor,
      anon_sym_condition,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
      sym_identifier,
  [1018] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(67), 13,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_DOLLAR,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
    ACTIONS(69), 27,
      anon_sym_import,
      anon_sym_include,
      anon_sym_private,
      anon_sym_global,
      anon_sym_rule,
      anon_sym_strings,
      anon_sym_nocase,
      anon_sym_ascii,
      anon_sym_wide,
      anon_sym_fullword,
      anon_sym_base64,
      anon_sym_base64wide,
      anon_sym_xor,
      anon_sym_condition,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
      sym_identifier,
  [1066] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(71), 13,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_DOLLAR,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
    ACTIONS(73), 27,
      anon_sym_import,
      anon_sym_include,
      anon_sym_private,
      anon_sym_global,
      anon_sym_rule,
      anon_sym_strings,
      anon_sym_nocase,
      anon_sym_ascii,
      anon_sym_wide,
      anon_sym_fullword,
      anon_sym_base64,
      anon_sym_base64wide,
      anon_sym_xor,
      anon_sym_condition,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
      sym_identifier,
  [1114] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(75), 13,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_DOLLAR,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
    ACTIONS(77), 27,
      anon_sym_import,
      anon_sym_include,
      anon_sym_private,
      anon_sym_global,
      anon_sym_rule,
      anon_sym_strings,
      anon_sym_nocase,
      anon_sym_ascii,
      anon_sym_wide,
      anon_sym_fullword,
      anon_sym_base64,
      anon_sym_base64wide,
      anon_sym_xor,
      anon_sym_condition,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
      sym_identifier,
  [1162] = 5,
    ACTIONS(3), 1,
      sym_comment,
    STATE(19), 1,
      sym_size_unit,
    ACTIONS(83), 3,
      anon_sym_KB,
      anon_sym_MB,
      anon_sym_GB,
    ACTIONS(81), 13,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_DOT_DOT,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
    ACTIONS(79), 16,
      anon_sym_strings,
      anon_sym_condition,
      anon_sym_of,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
      sym_identifier,
  [1207] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(85), 12,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
    ACTIONS(87), 20,
      anon_sym_import,
      anon_sym_include,
      anon_sym_private,
      anon_sym_global,
      anon_sym_rule,
      anon_sym_strings,
      anon_sym_condition,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
      sym_identifier,
  [1247] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(91), 13,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_DOT_DOT,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
    ACTIONS(89), 16,
      anon_sym_strings,
      anon_sym_condition,
      anon_sym_of,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
      sym_identifier,
  [1284] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(95), 13,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_DOT_DOT,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
    ACTIONS(93), 16,
      anon_sym_strings,
      anon_sym_condition,
      anon_sym_of,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
      sym_identifier,
  [1321] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(97), 1,
      sym_identifier,
    ACTIONS(99), 13,
      anon_sym_EQ,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
    ACTIONS(101), 13,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
  [1358] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(105), 11,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
    ACTIONS(103), 15,
      anon_sym_strings,
      anon_sym_condition,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
      sym_identifier,
  [1392] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 3,
      anon_sym_EQ,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(109), 23,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
  [1426] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(113), 1,
      anon_sym_LBRACK,
    STATE(132), 1,
      sym__lbrack,
    ACTIONS(115), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(111), 21,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
  [1463] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(119), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(117), 23,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_in,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
  [1496] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(123), 1,
      anon_sym_LBRACK,
    STATE(131), 1,
      sym__lbrack,
    ACTIONS(125), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(121), 21,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
  [1533] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(129), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(127), 23,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_in,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
  [1566] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(133), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(131), 23,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_in,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
  [1599] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(137), 1,
      anon_sym_of,
    ACTIONS(139), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(135), 21,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
  [1633] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(151), 1,
      anon_sym_and,
    ACTIONS(143), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(149), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(141), 3,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_or,
    ACTIONS(145), 3,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
    ACTIONS(147), 12,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
  [1672] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(143), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(153), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(145), 3,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
    ACTIONS(141), 16,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
  [1707] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(157), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(155), 21,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
  [1738] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(161), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(159), 21,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
  [1769] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(151), 1,
      anon_sym_and,
    ACTIONS(163), 1,
      anon_sym_RPAREN,
    ACTIONS(165), 1,
      anon_sym_or,
    STATE(31), 1,
      sym__rparen,
    ACTIONS(143), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(149), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(145), 3,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
    ACTIONS(147), 12,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
  [1812] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(153), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(145), 3,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
    ACTIONS(141), 18,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
  [1845] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(153), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(141), 21,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
  [1876] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(143), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(149), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(145), 3,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
    ACTIONS(141), 4,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_and,
      anon_sym_or,
    ACTIONS(147), 12,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
  [1913] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(169), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(167), 21,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
  [1944] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(151), 1,
      anon_sym_and,
    ACTIONS(165), 1,
      anon_sym_or,
    ACTIONS(171), 1,
      anon_sym_RPAREN,
    STATE(42), 1,
      sym__rparen,
    ACTIONS(143), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(149), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(145), 3,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
    ACTIONS(147), 12,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
  [1987] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(175), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(173), 21,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
  [2018] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(179), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(177), 21,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
  [2049] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(183), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(181), 21,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
  [2080] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(187), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(185), 21,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
  [2111] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(151), 1,
      anon_sym_and,
    ACTIONS(165), 1,
      anon_sym_or,
    ACTIONS(189), 1,
      anon_sym_RPAREN,
    STATE(44), 1,
      sym__rparen,
    ACTIONS(143), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(149), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(145), 3,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
    ACTIONS(147), 12,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
  [2154] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(193), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(191), 21,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
      anon_sym_and,
      anon_sym_or,
  [2185] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(151), 1,
      anon_sym_and,
    ACTIONS(165), 1,
      anon_sym_or,
    ACTIONS(195), 1,
      anon_sym_RBRACE,
    ACTIONS(143), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(149), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(145), 3,
      anon_sym_STAR,
      anon_sym_BSLASH,
      anon_sym_PERCENT,
    ACTIONS(147), 12,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_contains,
      anon_sym_matches,
      anon_sym_icontains,
      anon_sym_imatches,
      anon_sym_startswith,
      anon_sym_istartswith,
      anon_sym_endswith,
      anon_sym_iendswith,
  [2225] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    ACTIONS(197), 1,
      anon_sym_LBRACE,
    ACTIONS(199), 1,
      anon_sym_SLASH,
    STATE(58), 1,
      sym__lbrace,
    STATE(85), 1,
      sym__squote,
    STATE(99), 1,
      sym__quote,
    STATE(111), 1,
      sym__slash,
    STATE(59), 2,
      sym_double_quoted_string,
      sym_single_quoted_string,
    STATE(48), 3,
      sym_text_string,
      sym_hex_string,
      sym_regex_string,
  [2262] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    ACTIONS(33), 1,
      aux_sym_integer_literal_token1,
    STATE(85), 1,
      sym__squote,
    STATE(99), 1,
      sym__quote,
    ACTIONS(201), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(17), 2,
      sym_double_quoted_string,
      sym_single_quoted_string,
    STATE(125), 3,
      sym_integer_literal,
      sym_boolean_literal,
      sym_string_literal,
  [2294] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(207), 1,
      anon_sym_base64,
    ACTIONS(209), 1,
      anon_sym_base64wide,
    STATE(56), 1,
      aux_sym_string_modifiers_repeat1,
    STATE(150), 1,
      sym_string_modifiers,
    ACTIONS(203), 2,
      anon_sym_DOLLAR,
      anon_sym_condition,
    ACTIONS(205), 5,
      anon_sym_nocase,
      anon_sym_ascii,
      anon_sym_wide,
      anon_sym_fullword,
      anon_sym_xor,
  [2321] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(211), 1,
      anon_sym_LPAREN,
    ACTIONS(215), 1,
      anon_sym_base64,
    STATE(65), 1,
      sym__lparen,
    ACTIONS(213), 8,
      anon_sym_DOLLAR,
      anon_sym_nocase,
      anon_sym_ascii,
      anon_sym_wide,
      anon_sym_fullword,
      anon_sym_base64wide,
      anon_sym_xor,
      anon_sym_condition,
  [2344] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(207), 1,
      anon_sym_base64,
    ACTIONS(209), 1,
      anon_sym_base64wide,
    STATE(55), 1,
      aux_sym_string_modifiers_repeat1,
    STATE(62), 1,
      sym_string_modifiers,
    ACTIONS(217), 2,
      anon_sym_DOLLAR,
      anon_sym_condition,
    ACTIONS(219), 5,
      anon_sym_nocase,
      anon_sym_ascii,
      anon_sym_wide,
      anon_sym_fullword,
      anon_sym_xor,
  [2371] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(221), 1,
      anon_sym_RBRACE,
    ACTIONS(223), 1,
      anon_sym_LBRACK,
    ACTIONS(225), 1,
      anon_sym_LPAREN,
    STATE(61), 1,
      sym__rbrace,
    STATE(106), 1,
      sym__lbrack,
    STATE(164), 1,
      sym__lparen,
    ACTIONS(227), 2,
      sym_hex_byte,
      sym_hex_wildcard,
    STATE(57), 3,
      sym_hex_jump,
      sym_hex_alternative,
      aux_sym_hex_string_repeat1,
  [2402] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      anon_sym_import,
    ACTIONS(9), 1,
      anon_sym_include,
    ACTIONS(11), 1,
      anon_sym_private,
    ACTIONS(13), 1,
      anon_sym_global,
    ACTIONS(15), 1,
      anon_sym_rule,
    ACTIONS(229), 1,
      ts_builtin_sym_end,
    STATE(54), 4,
      sym_import_statement,
      sym_include_statement,
      sym_rule_definition,
      aux_sym_source_file_repeat1,
  [2430] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(236), 1,
      anon_sym_base64,
    ACTIONS(239), 1,
      anon_sym_base64wide,
    STATE(53), 1,
      aux_sym_string_modifiers_repeat1,
    ACTIONS(231), 2,
      anon_sym_DOLLAR,
      anon_sym_condition,
    ACTIONS(233), 5,
      anon_sym_nocase,
      anon_sym_ascii,
      anon_sym_wide,
      anon_sym_fullword,
      anon_sym_xor,
  [2454] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(242), 1,
      ts_builtin_sym_end,
    ACTIONS(244), 1,
      anon_sym_import,
    ACTIONS(247), 1,
      anon_sym_include,
    ACTIONS(250), 1,
      anon_sym_private,
    ACTIONS(253), 1,
      anon_sym_global,
    ACTIONS(256), 1,
      anon_sym_rule,
    STATE(54), 4,
      sym_import_statement,
      sym_include_statement,
      sym_rule_definition,
      aux_sym_source_file_repeat1,
  [2482] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(261), 1,
      anon_sym_base64,
    STATE(53), 1,
      aux_sym_string_modifiers_repeat1,
    ACTIONS(259), 8,
      anon_sym_DOLLAR,
      anon_sym_nocase,
      anon_sym_ascii,
      anon_sym_wide,
      anon_sym_fullword,
      anon_sym_base64wide,
      anon_sym_xor,
      anon_sym_condition,
  [2502] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(207), 1,
      anon_sym_base64,
    ACTIONS(209), 1,
      anon_sym_base64wide,
    STATE(53), 1,
      aux_sym_string_modifiers_repeat1,
    ACTIONS(259), 2,
      anon_sym_DOLLAR,
      anon_sym_condition,
    ACTIONS(263), 5,
      anon_sym_nocase,
      anon_sym_ascii,
      anon_sym_wide,
      anon_sym_fullword,
      anon_sym_xor,
  [2526] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(265), 1,
      anon_sym_RBRACE,
    ACTIONS(267), 1,
      anon_sym_LBRACK,
    ACTIONS(270), 1,
      anon_sym_LPAREN,
    STATE(106), 1,
      sym__lbrack,
    STATE(164), 1,
      sym__lparen,
    ACTIONS(273), 2,
      sym_hex_byte,
      sym_hex_wildcard,
    STATE(57), 3,
      sym_hex_jump,
      sym_hex_alternative,
      aux_sym_hex_string_repeat1,
  [2554] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(223), 1,
      anon_sym_LBRACK,
    ACTIONS(225), 1,
      anon_sym_LPAREN,
    STATE(106), 1,
      sym__lbrack,
    STATE(164), 1,
      sym__lparen,
    ACTIONS(276), 2,
      sym_hex_byte,
      sym_hex_wildcard,
    STATE(51), 3,
      sym_hex_jump,
      sym_hex_alternative,
      aux_sym_hex_string_repeat1,
  [2579] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(280), 1,
      anon_sym_base64,
    ACTIONS(278), 8,
      anon_sym_DOLLAR,
      anon_sym_nocase,
      anon_sym_ascii,
      anon_sym_wide,
      anon_sym_fullword,
      anon_sym_base64wide,
      anon_sym_xor,
      anon_sym_condition,
  [2596] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(284), 1,
      anon_sym_base64,
    ACTIONS(282), 8,
      anon_sym_DOLLAR,
      anon_sym_nocase,
      anon_sym_ascii,
      anon_sym_wide,
      anon_sym_fullword,
      anon_sym_base64wide,
      anon_sym_xor,
      anon_sym_condition,
  [2613] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(288), 1,
      anon_sym_base64,
    ACTIONS(286), 8,
      anon_sym_DOLLAR,
      anon_sym_nocase,
      anon_sym_ascii,
      anon_sym_wide,
      anon_sym_fullword,
      anon_sym_base64wide,
      anon_sym_xor,
      anon_sym_condition,
  [2630] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(292), 1,
      anon_sym_base64,
    ACTIONS(290), 8,
      anon_sym_DOLLAR,
      anon_sym_nocase,
      anon_sym_ascii,
      anon_sym_wide,
      anon_sym_fullword,
      anon_sym_base64wide,
      anon_sym_xor,
      anon_sym_condition,
  [2647] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    STATE(66), 1,
      sym_string_literal,
    STATE(85), 1,
      sym__squote,
    STATE(99), 1,
      sym__quote,
    STATE(17), 2,
      sym_double_quoted_string,
      sym_single_quoted_string,
  [2670] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    STATE(67), 1,
      sym_string_literal,
    STATE(85), 1,
      sym__squote,
    STATE(99), 1,
      sym__quote,
    STATE(17), 2,
      sym_double_quoted_string,
      sym_single_quoted_string,
  [2693] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    STATE(85), 1,
      sym__squote,
    STATE(99), 1,
      sym__quote,
    STATE(158), 1,
      sym_string_literal,
    STATE(17), 2,
      sym_double_quoted_string,
      sym_single_quoted_string,
  [2716] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(294), 6,
      ts_builtin_sym_end,
      anon_sym_import,
      anon_sym_include,
      anon_sym_private,
      anon_sym_global,
      anon_sym_rule,
  [2728] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(296), 6,
      ts_builtin_sym_end,
      anon_sym_import,
      anon_sym_include,
      anon_sym_private,
      anon_sym_global,
      anon_sym_rule,
  [2740] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(298), 6,
      ts_builtin_sym_end,
      anon_sym_import,
      anon_sym_include,
      anon_sym_private,
      anon_sym_global,
      anon_sym_rule,
  [2752] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(300), 1,
      anon_sym_COLON,
    ACTIONS(302), 1,
      anon_sym_LBRACE,
    STATE(72), 1,
      sym__lbrace,
    STATE(73), 1,
      sym_rule_body,
    STATE(127), 1,
      sym_tag_list,
    STATE(170), 1,
      sym__colon,
  [2774] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(304), 1,
      anon_sym_DOLLAR,
    ACTIONS(307), 1,
      anon_sym_condition,
    STATE(20), 1,
      sym__dollar,
    STATE(130), 1,
      sym_string_identifier,
    STATE(70), 2,
      sym_string_definition,
      aux_sym_strings_section_repeat1,
  [2794] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(300), 1,
      anon_sym_COLON,
    ACTIONS(302), 1,
      anon_sym_LBRACE,
    STATE(72), 1,
      sym__lbrace,
    STATE(83), 1,
      sym_rule_body,
    STATE(114), 1,
      sym_tag_list,
    STATE(170), 1,
      sym__colon,
  [2816] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(309), 1,
      anon_sym_meta,
    ACTIONS(311), 1,
      anon_sym_strings,
    ACTIONS(313), 1,
      anon_sym_condition,
    STATE(101), 1,
      sym_meta_section,
    STATE(140), 1,
      sym_strings_section,
    STATE(147), 1,
      sym_condition_section,
  [2838] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(315), 6,
      ts_builtin_sym_end,
      anon_sym_import,
      anon_sym_include,
      anon_sym_private,
      anon_sym_global,
      anon_sym_rule,
  [2850] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(317), 6,
      ts_builtin_sym_end,
      anon_sym_import,
      anon_sym_include,
      anon_sym_private,
      anon_sym_global,
      anon_sym_rule,
  [2862] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(21), 1,
      anon_sym_DOLLAR,
    ACTIONS(319), 1,
      anon_sym_condition,
    STATE(20), 1,
      sym__dollar,
    STATE(130), 1,
      sym_string_identifier,
    STATE(70), 2,
      sym_string_definition,
      aux_sym_strings_section_repeat1,
  [2882] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(300), 1,
      anon_sym_COLON,
    ACTIONS(302), 1,
      anon_sym_LBRACE,
    STATE(72), 1,
      sym__lbrace,
    STATE(80), 1,
      sym_rule_body,
    STATE(119), 1,
      sym_tag_list,
    STATE(170), 1,
      sym__colon,
  [2904] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(33), 1,
      aux_sym_integer_literal_token1,
    STATE(167), 1,
      sym_integer_literal,
    STATE(173), 1,
      sym_quantifier,
    ACTIONS(321), 3,
      anon_sym_all,
      anon_sym_any,
      anon_sym_none,
  [2922] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(323), 6,
      ts_builtin_sym_end,
      anon_sym_import,
      anon_sym_include,
      anon_sym_private,
      anon_sym_global,
      anon_sym_rule,
  [2934] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(325), 6,
      ts_builtin_sym_end,
      anon_sym_import,
      anon_sym_include,
      anon_sym_private,
      anon_sym_global,
      anon_sym_rule,
  [2946] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(327), 6,
      ts_builtin_sym_end,
      anon_sym_import,
      anon_sym_include,
      anon_sym_private,
      anon_sym_global,
      anon_sym_rule,
  [2958] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(329), 6,
      ts_builtin_sym_end,
      anon_sym_import,
      anon_sym_include,
      anon_sym_private,
      anon_sym_global,
      anon_sym_rule,
  [2970] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(331), 6,
      ts_builtin_sym_end,
      anon_sym_import,
      anon_sym_include,
      anon_sym_private,
      anon_sym_global,
      anon_sym_rule,
  [2982] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(333), 6,
      ts_builtin_sym_end,
      anon_sym_import,
      anon_sym_include,
      anon_sym_private,
      anon_sym_global,
      anon_sym_rule,
  [2994] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(335), 1,
      anon_sym_RPAREN,
    ACTIONS(337), 1,
      anon_sym_COMMA,
    STATE(26), 1,
      sym__rparen,
    STATE(88), 1,
      aux_sym_string_set_repeat1,
    STATE(116), 1,
      sym__comma,
  [3013] = 5,
    ACTIONS(339), 1,
      anon_sym_SQUOTE,
    ACTIONS(343), 1,
      sym_comment,
    STATE(14), 1,
      sym__squote,
    STATE(96), 1,
      aux_sym_single_quoted_string_repeat1,
    ACTIONS(341), 2,
      aux_sym_single_quoted_string_token1,
      sym_escape_sequence,
  [3030] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(345), 1,
      sym_identifier,
    ACTIONS(347), 2,
      anon_sym_strings,
      anon_sym_condition,
    STATE(92), 2,
      sym_meta_definition,
      aux_sym_meta_section_repeat1,
  [3045] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(349), 1,
      anon_sym_RPAREN,
    ACTIONS(351), 1,
      anon_sym_PIPE,
    STATE(90), 1,
      sym__rparen,
    STATE(91), 1,
      aux_sym_hex_alternative_repeat1,
    STATE(163), 1,
      sym__pipe,
  [3064] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(337), 1,
      anon_sym_COMMA,
    ACTIONS(353), 1,
      anon_sym_RPAREN,
    STATE(27), 1,
      sym__rparen,
    STATE(108), 1,
      aux_sym_string_set_repeat1,
    STATE(116), 1,
      sym__comma,
  [3083] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(355), 5,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_LPAREN,
      sym_hex_byte,
      sym_hex_wildcard,
  [3094] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(357), 5,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_LPAREN,
      sym_hex_byte,
      sym_hex_wildcard,
  [3105] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(351), 1,
      anon_sym_PIPE,
    ACTIONS(359), 1,
      anon_sym_RPAREN,
    STATE(94), 1,
      sym__rparen,
    STATE(109), 1,
      aux_sym_hex_alternative_repeat1,
    STATE(163), 1,
      sym__pipe,
  [3124] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(361), 1,
      sym_identifier,
    ACTIONS(364), 2,
      anon_sym_strings,
      anon_sym_condition,
    STATE(92), 2,
      sym_meta_definition,
      aux_sym_meta_section_repeat1,
  [3139] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(366), 5,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_LPAREN,
      sym_hex_byte,
      sym_hex_wildcard,
  [3150] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(368), 5,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_LPAREN,
      sym_hex_byte,
      sym_hex_wildcard,
  [3161] = 5,
    ACTIONS(343), 1,
      sym_comment,
    ACTIONS(370), 1,
      anon_sym_DQUOTE,
    STATE(15), 1,
      sym__quote,
    STATE(104), 1,
      aux_sym_double_quoted_string_repeat1,
    ACTIONS(372), 2,
      aux_sym_double_quoted_string_token1,
      sym_escape_sequence,
  [3178] = 5,
    ACTIONS(343), 1,
      sym_comment,
    ACTIONS(374), 1,
      anon_sym_SQUOTE,
    STATE(13), 1,
      sym__squote,
    STATE(112), 1,
      aux_sym_single_quoted_string_repeat1,
    ACTIONS(376), 2,
      aux_sym_single_quoted_string_token1,
      sym_escape_sequence,
  [3195] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(378), 5,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_LPAREN,
      sym_hex_byte,
      sym_hex_wildcard,
  [3206] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(21), 1,
      anon_sym_DOLLAR,
    STATE(20), 1,
      sym__dollar,
    STATE(130), 1,
      sym_string_identifier,
    STATE(75), 2,
      sym_string_definition,
      aux_sym_strings_section_repeat1,
  [3223] = 5,
    ACTIONS(343), 1,
      sym_comment,
    ACTIONS(380), 1,
      anon_sym_DQUOTE,
    STATE(12), 1,
      sym__quote,
    STATE(95), 1,
      aux_sym_double_quoted_string_repeat1,
    ACTIONS(382), 2,
      aux_sym_double_quoted_string_token1,
      sym_escape_sequence,
  [3240] = 4,
    ACTIONS(343), 1,
      sym_comment,
    ACTIONS(384), 1,
      anon_sym_SLASH,
    STATE(102), 1,
      aux_sym_regex_string_content_repeat1,
    ACTIONS(386), 2,
      sym_escape_sequence,
      aux_sym_regex_string_content_token1,
  [3254] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(311), 1,
      anon_sym_strings,
    ACTIONS(313), 1,
      anon_sym_condition,
    STATE(129), 1,
      sym_condition_section,
    STATE(157), 1,
      sym_strings_section,
  [3270] = 4,
    ACTIONS(343), 1,
      sym_comment,
    ACTIONS(388), 1,
      anon_sym_SLASH,
    STATE(102), 1,
      aux_sym_regex_string_content_repeat1,
    ACTIONS(390), 2,
      sym_escape_sequence,
      aux_sym_regex_string_content_token1,
  [3284] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(393), 1,
      anon_sym_LPAREN,
    ACTIONS(395), 1,
      anon_sym_them,
    STATE(118), 1,
      sym__lparen,
    STATE(126), 1,
      sym_string_set,
  [3300] = 4,
    ACTIONS(343), 1,
      sym_comment,
    ACTIONS(397), 1,
      anon_sym_DQUOTE,
    STATE(104), 1,
      aux_sym_double_quoted_string_repeat1,
    ACTIONS(399), 2,
      aux_sym_double_quoted_string_token1,
      sym_escape_sequence,
  [3314] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(33), 1,
      aux_sym_integer_literal_token1,
    ACTIONS(402), 1,
      anon_sym_RBRACK,
    STATE(93), 1,
      sym__rbrack,
    STATE(148), 1,
      sym_integer_literal,
  [3330] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(33), 1,
      aux_sym_integer_literal_token1,
    ACTIONS(404), 1,
      anon_sym_DOT_DOT,
    STATE(110), 1,
      sym__range,
    STATE(155), 1,
      sym_integer_literal,
  [3346] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(393), 1,
      anon_sym_LPAREN,
    ACTIONS(395), 1,
      anon_sym_them,
    STATE(37), 1,
      sym_string_set,
    STATE(118), 1,
      sym__lparen,
  [3362] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(406), 1,
      anon_sym_RPAREN,
    ACTIONS(408), 1,
      anon_sym_COMMA,
    STATE(108), 1,
      aux_sym_string_set_repeat1,
    STATE(116), 1,
      sym__comma,
  [3378] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(411), 1,
      anon_sym_RPAREN,
    ACTIONS(413), 1,
      anon_sym_PIPE,
    STATE(109), 1,
      aux_sym_hex_alternative_repeat1,
    STATE(163), 1,
      sym__pipe,
  [3394] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(33), 1,
      aux_sym_integer_literal_token1,
    ACTIONS(416), 1,
      anon_sym_RBRACK,
    STATE(89), 1,
      sym__rbrack,
    STATE(138), 1,
      sym_integer_literal,
  [3410] = 4,
    ACTIONS(343), 1,
      sym_comment,
    STATE(100), 1,
      aux_sym_regex_string_content_repeat1,
    STATE(146), 1,
      sym_regex_string_content,
    ACTIONS(418), 2,
      sym_escape_sequence,
      aux_sym_regex_string_content_token1,
  [3424] = 4,
    ACTIONS(343), 1,
      sym_comment,
    ACTIONS(420), 1,
      anon_sym_SQUOTE,
    STATE(112), 1,
      aux_sym_single_quoted_string_repeat1,
    ACTIONS(422), 2,
      aux_sym_single_quoted_string_token1,
      sym_escape_sequence,
  [3438] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(425), 1,
      anon_sym_LPAREN,
    STATE(142), 1,
      sym__lparen,
    STATE(143), 1,
      sym_range,
  [3451] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(302), 1,
      anon_sym_LBRACE,
    STATE(72), 1,
      sym__lbrace,
    STATE(79), 1,
      sym_rule_body,
  [3464] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(21), 1,
      anon_sym_DOLLAR,
    STATE(20), 1,
      sym__dollar,
    STATE(40), 1,
      sym_string_identifier,
  [3477] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(21), 1,
      anon_sym_DOLLAR,
    STATE(20), 1,
      sym__dollar,
    STATE(145), 1,
      sym_string_identifier,
  [3490] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(427), 1,
      sym_identifier,
    ACTIONS(429), 1,
      anon_sym_LBRACE,
    STATE(121), 1,
      aux_sym_tag_list_repeat1,
  [3503] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(21), 1,
      anon_sym_DOLLAR,
    STATE(20), 1,
      sym__dollar,
    STATE(84), 1,
      sym_string_identifier,
  [3516] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(302), 1,
      anon_sym_LBRACE,
    STATE(72), 1,
      sym__lbrace,
    STATE(81), 1,
      sym_rule_body,
  [3529] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(431), 1,
      sym_identifier,
    ACTIONS(434), 1,
      anon_sym_LBRACE,
    STATE(120), 1,
      aux_sym_tag_list_repeat1,
  [3542] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(427), 1,
      sym_identifier,
    ACTIONS(436), 1,
      anon_sym_LBRACE,
    STATE(120), 1,
      aux_sym_tag_list_repeat1,
  [3555] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(21), 1,
      anon_sym_DOLLAR,
    STATE(20), 1,
      sym__dollar,
    STATE(25), 1,
      sym_string_identifier,
  [3568] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(438), 1,
      sym_identifier,
    STATE(86), 2,
      sym_meta_definition,
      aux_sym_meta_section_repeat1,
  [3579] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(21), 1,
      anon_sym_DOLLAR,
    STATE(20), 1,
      sym__dollar,
    STATE(23), 1,
      sym_string_identifier,
  [3592] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(440), 3,
      anon_sym_strings,
      anon_sym_condition,
      sym_identifier,
  [3601] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(442), 1,
      anon_sym_COLON,
    ACTIONS(444), 1,
      anon_sym_in,
    STATE(134), 1,
      sym__colon,
  [3614] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(302), 1,
      anon_sym_LBRACE,
    STATE(72), 1,
      sym__lbrace,
    STATE(78), 1,
      sym_rule_body,
  [3627] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(446), 1,
      anon_sym_DOT_DOT,
    STATE(154), 1,
      sym__range,
  [3637] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(448), 1,
      anon_sym_RBRACE,
    STATE(68), 1,
      sym__rbrace,
  [3647] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(450), 1,
      anon_sym_EQ,
    STATE(46), 1,
      sym__equal,
  [3657] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(33), 1,
      aux_sym_integer_literal_token1,
    STATE(151), 1,
      sym_integer_literal,
  [3667] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(33), 1,
      aux_sym_integer_literal_token1,
    STATE(153), 1,
      sym_integer_literal,
  [3677] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(452), 1,
      anon_sym_EQ,
    STATE(47), 1,
      sym__equal,
  [3687] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(454), 1,
      anon_sym_LPAREN,
    STATE(10), 1,
      sym__lparen,
  [3697] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(456), 1,
      anon_sym_COLON,
    STATE(123), 1,
      sym__colon,
  [3707] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(458), 1,
      anon_sym_COLON,
    STATE(98), 1,
      sym__colon,
  [3717] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(460), 1,
      anon_sym_COLON,
    STATE(2), 1,
      sym__colon,
  [3727] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(402), 1,
      anon_sym_RBRACK,
    STATE(93), 1,
      sym__rbrack,
  [3737] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(462), 1,
      anon_sym_global,
    ACTIONS(464), 1,
      anon_sym_rule,
  [3747] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(313), 1,
      anon_sym_condition,
    STATE(129), 1,
      sym_condition_section,
  [3757] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(466), 1,
      anon_sym_RBRACE,
    STATE(74), 1,
      sym__rbrace,
  [3767] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(33), 1,
      aux_sym_integer_literal_token1,
    STATE(128), 1,
      sym_integer_literal,
  [3777] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(468), 1,
      anon_sym_COLON,
    STATE(152), 1,
      sym__colon,
  [3787] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(470), 2,
      anon_sym_LBRACE,
      sym_identifier,
  [3795] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(406), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [3803] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(472), 1,
      anon_sym_SLASH,
    STATE(50), 1,
      sym__slash,
  [3813] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(474), 1,
      anon_sym_RBRACE,
    STATE(82), 1,
      sym__rbrace,
  [3823] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(476), 1,
      anon_sym_RBRACK,
    STATE(97), 1,
      sym__rbrack,
  [3833] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(411), 2,
      anon_sym_RPAREN,
      anon_sym_PIPE,
  [3841] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(478), 2,
      anon_sym_DOLLAR,
      anon_sym_condition,
  [3849] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(480), 1,
      anon_sym_RBRACK,
    STATE(41), 1,
      sym__rbrack,
  [3859] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(482), 1,
      anon_sym_LPAREN,
    STATE(11), 1,
      sym__lparen,
  [3869] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(484), 1,
      anon_sym_RBRACK,
    STATE(39), 1,
      sym__rbrack,
  [3879] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(33), 1,
      aux_sym_integer_literal_token1,
    STATE(156), 1,
      sym_integer_literal,
  [3889] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(486), 1,
      anon_sym_DOT_DOT,
    STATE(105), 1,
      sym__range,
  [3899] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(488), 1,
      anon_sym_RPAREN,
    STATE(171), 1,
      sym__rparen,
  [3909] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(313), 1,
      anon_sym_condition,
    STATE(141), 1,
      sym_condition_section,
  [3919] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(490), 1,
      anon_sym_RPAREN,
    STATE(60), 1,
      sym__rparen,
  [3929] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(492), 1,
      sym_identifier,
  [3936] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(494), 1,
      sym_identifier,
  [3943] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(496), 1,
      anon_sym_of,
  [3950] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(498), 1,
      ts_builtin_sym_end,
  [3957] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(500), 1,
      sym_hex_byte,
  [3964] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(502), 1,
      sym_hex_byte,
  [3971] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(464), 1,
      anon_sym_rule,
  [3978] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(504), 1,
      anon_sym_of,
  [3985] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(137), 1,
      anon_sym_of,
  [3992] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(506), 1,
      anon_sym_rule,
  [3999] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(508), 1,
      sym_identifier,
  [4006] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(510), 1,
      sym_identifier,
  [4013] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(512), 1,
      anon_sym_COLON,
  [4020] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(514), 1,
      anon_sym_of,
  [4027] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(516), 1,
      anon_sym_of,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 97,
  [SMALL_STATE(4)] = 194,
  [SMALL_STATE(5)] = 291,
  [SMALL_STATE(6)] = 388,
  [SMALL_STATE(7)] = 485,
  [SMALL_STATE(8)] = 582,
  [SMALL_STATE(9)] = 679,
  [SMALL_STATE(10)] = 776,
  [SMALL_STATE(11)] = 873,
  [SMALL_STATE(12)] = 970,
  [SMALL_STATE(13)] = 1018,
  [SMALL_STATE(14)] = 1066,
  [SMALL_STATE(15)] = 1114,
  [SMALL_STATE(16)] = 1162,
  [SMALL_STATE(17)] = 1207,
  [SMALL_STATE(18)] = 1247,
  [SMALL_STATE(19)] = 1284,
  [SMALL_STATE(20)] = 1321,
  [SMALL_STATE(21)] = 1358,
  [SMALL_STATE(22)] = 1392,
  [SMALL_STATE(23)] = 1426,
  [SMALL_STATE(24)] = 1463,
  [SMALL_STATE(25)] = 1496,
  [SMALL_STATE(26)] = 1533,
  [SMALL_STATE(27)] = 1566,
  [SMALL_STATE(28)] = 1599,
  [SMALL_STATE(29)] = 1633,
  [SMALL_STATE(30)] = 1672,
  [SMALL_STATE(31)] = 1707,
  [SMALL_STATE(32)] = 1738,
  [SMALL_STATE(33)] = 1769,
  [SMALL_STATE(34)] = 1812,
  [SMALL_STATE(35)] = 1845,
  [SMALL_STATE(36)] = 1876,
  [SMALL_STATE(37)] = 1913,
  [SMALL_STATE(38)] = 1944,
  [SMALL_STATE(39)] = 1987,
  [SMALL_STATE(40)] = 2018,
  [SMALL_STATE(41)] = 2049,
  [SMALL_STATE(42)] = 2080,
  [SMALL_STATE(43)] = 2111,
  [SMALL_STATE(44)] = 2154,
  [SMALL_STATE(45)] = 2185,
  [SMALL_STATE(46)] = 2225,
  [SMALL_STATE(47)] = 2262,
  [SMALL_STATE(48)] = 2294,
  [SMALL_STATE(49)] = 2321,
  [SMALL_STATE(50)] = 2344,
  [SMALL_STATE(51)] = 2371,
  [SMALL_STATE(52)] = 2402,
  [SMALL_STATE(53)] = 2430,
  [SMALL_STATE(54)] = 2454,
  [SMALL_STATE(55)] = 2482,
  [SMALL_STATE(56)] = 2502,
  [SMALL_STATE(57)] = 2526,
  [SMALL_STATE(58)] = 2554,
  [SMALL_STATE(59)] = 2579,
  [SMALL_STATE(60)] = 2596,
  [SMALL_STATE(61)] = 2613,
  [SMALL_STATE(62)] = 2630,
  [SMALL_STATE(63)] = 2647,
  [SMALL_STATE(64)] = 2670,
  [SMALL_STATE(65)] = 2693,
  [SMALL_STATE(66)] = 2716,
  [SMALL_STATE(67)] = 2728,
  [SMALL_STATE(68)] = 2740,
  [SMALL_STATE(69)] = 2752,
  [SMALL_STATE(70)] = 2774,
  [SMALL_STATE(71)] = 2794,
  [SMALL_STATE(72)] = 2816,
  [SMALL_STATE(73)] = 2838,
  [SMALL_STATE(74)] = 2850,
  [SMALL_STATE(75)] = 2862,
  [SMALL_STATE(76)] = 2882,
  [SMALL_STATE(77)] = 2904,
  [SMALL_STATE(78)] = 2922,
  [SMALL_STATE(79)] = 2934,
  [SMALL_STATE(80)] = 2946,
  [SMALL_STATE(81)] = 2958,
  [SMALL_STATE(82)] = 2970,
  [SMALL_STATE(83)] = 2982,
  [SMALL_STATE(84)] = 2994,
  [SMALL_STATE(85)] = 3013,
  [SMALL_STATE(86)] = 3030,
  [SMALL_STATE(87)] = 3045,
  [SMALL_STATE(88)] = 3064,
  [SMALL_STATE(89)] = 3083,
  [SMALL_STATE(90)] = 3094,
  [SMALL_STATE(91)] = 3105,
  [SMALL_STATE(92)] = 3124,
  [SMALL_STATE(93)] = 3139,
  [SMALL_STATE(94)] = 3150,
  [SMALL_STATE(95)] = 3161,
  [SMALL_STATE(96)] = 3178,
  [SMALL_STATE(97)] = 3195,
  [SMALL_STATE(98)] = 3206,
  [SMALL_STATE(99)] = 3223,
  [SMALL_STATE(100)] = 3240,
  [SMALL_STATE(101)] = 3254,
  [SMALL_STATE(102)] = 3270,
  [SMALL_STATE(103)] = 3284,
  [SMALL_STATE(104)] = 3300,
  [SMALL_STATE(105)] = 3314,
  [SMALL_STATE(106)] = 3330,
  [SMALL_STATE(107)] = 3346,
  [SMALL_STATE(108)] = 3362,
  [SMALL_STATE(109)] = 3378,
  [SMALL_STATE(110)] = 3394,
  [SMALL_STATE(111)] = 3410,
  [SMALL_STATE(112)] = 3424,
  [SMALL_STATE(113)] = 3438,
  [SMALL_STATE(114)] = 3451,
  [SMALL_STATE(115)] = 3464,
  [SMALL_STATE(116)] = 3477,
  [SMALL_STATE(117)] = 3490,
  [SMALL_STATE(118)] = 3503,
  [SMALL_STATE(119)] = 3516,
  [SMALL_STATE(120)] = 3529,
  [SMALL_STATE(121)] = 3542,
  [SMALL_STATE(122)] = 3555,
  [SMALL_STATE(123)] = 3568,
  [SMALL_STATE(124)] = 3579,
  [SMALL_STATE(125)] = 3592,
  [SMALL_STATE(126)] = 3601,
  [SMALL_STATE(127)] = 3614,
  [SMALL_STATE(128)] = 3627,
  [SMALL_STATE(129)] = 3637,
  [SMALL_STATE(130)] = 3647,
  [SMALL_STATE(131)] = 3657,
  [SMALL_STATE(132)] = 3667,
  [SMALL_STATE(133)] = 3677,
  [SMALL_STATE(134)] = 3687,
  [SMALL_STATE(135)] = 3697,
  [SMALL_STATE(136)] = 3707,
  [SMALL_STATE(137)] = 3717,
  [SMALL_STATE(138)] = 3727,
  [SMALL_STATE(139)] = 3737,
  [SMALL_STATE(140)] = 3747,
  [SMALL_STATE(141)] = 3757,
  [SMALL_STATE(142)] = 3767,
  [SMALL_STATE(143)] = 3777,
  [SMALL_STATE(144)] = 3787,
  [SMALL_STATE(145)] = 3795,
  [SMALL_STATE(146)] = 3803,
  [SMALL_STATE(147)] = 3813,
  [SMALL_STATE(148)] = 3823,
  [SMALL_STATE(149)] = 3833,
  [SMALL_STATE(150)] = 3841,
  [SMALL_STATE(151)] = 3849,
  [SMALL_STATE(152)] = 3859,
  [SMALL_STATE(153)] = 3869,
  [SMALL_STATE(154)] = 3879,
  [SMALL_STATE(155)] = 3889,
  [SMALL_STATE(156)] = 3899,
  [SMALL_STATE(157)] = 3909,
  [SMALL_STATE(158)] = 3919,
  [SMALL_STATE(159)] = 3929,
  [SMALL_STATE(160)] = 3936,
  [SMALL_STATE(161)] = 3943,
  [SMALL_STATE(162)] = 3950,
  [SMALL_STATE(163)] = 3957,
  [SMALL_STATE(164)] = 3964,
  [SMALL_STATE(165)] = 3971,
  [SMALL_STATE(166)] = 3978,
  [SMALL_STATE(167)] = 3985,
  [SMALL_STATE(168)] = 3992,
  [SMALL_STATE(169)] = 3999,
  [SMALL_STATE(170)] = 4006,
  [SMALL_STATE(171)] = 4013,
  [SMALL_STATE(172)] = 4020,
  [SMALL_STATE(173)] = 4027,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0, 0, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(139),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(165),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(169),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(45),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(122),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(124),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [35] = {.entry = {.count = 1, .reusable = false}}, SHIFT(77),
  [37] = {.entry = {.count = 1, .reusable = false}}, SHIFT(172),
  [39] = {.entry = {.count = 1, .reusable = false}}, SHIFT(3),
  [41] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [43] = {.entry = {.count = 1, .reusable = false}}, SHIFT(21),
  [45] = {.entry = {.count = 1, .reusable = false}}, SHIFT(32),
  [47] = {.entry = {.count = 1, .reusable = false}}, SHIFT(30),
  [49] = {.entry = {.count = 1, .reusable = false}}, SHIFT(33),
  [51] = {.entry = {.count = 1, .reusable = false}}, SHIFT(36),
  [53] = {.entry = {.count = 1, .reusable = false}}, SHIFT(34),
  [55] = {.entry = {.count = 1, .reusable = false}}, SHIFT(35),
  [57] = {.entry = {.count = 1, .reusable = false}}, SHIFT(29),
  [59] = {.entry = {.count = 1, .reusable = false}}, SHIFT(38),
  [61] = {.entry = {.count = 1, .reusable = false}}, SHIFT(43),
  [63] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_double_quoted_string, 2, 0, 0),
  [65] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_double_quoted_string, 2, 0, 0),
  [67] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_single_quoted_string, 3, 0, 0),
  [69] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_single_quoted_string, 3, 0, 0),
  [71] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_single_quoted_string, 2, 0, 0),
  [73] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_single_quoted_string, 2, 0, 0),
  [75] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_double_quoted_string, 3, 0, 0),
  [77] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_double_quoted_string, 3, 0, 0),
  [79] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_integer_literal, 1, 0, 0),
  [81] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_integer_literal, 1, 0, 0),
  [83] = {.entry = {.count = 1, .reusable = false}}, SHIFT(18),
  [85] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_literal, 1, 0, 0),
  [87] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string_literal, 1, 0, 0),
  [89] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_size_unit, 1, 0, 0),
  [91] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_size_unit, 1, 0, 0),
  [93] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_integer_literal, 2, 0, 0),
  [95] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_integer_literal, 2, 0, 0),
  [97] = {.entry = {.count = 1, .reusable = false}}, SHIFT(22),
  [99] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string_identifier, 1, 0, 0),
  [101] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_identifier, 1, 0, 0),
  [103] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_boolean_literal, 1, 0, 0),
  [105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_boolean_literal, 1, 0, 0),
  [107] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string_identifier, 2, 0, 0),
  [109] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_identifier, 2, 0, 0),
  [111] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_length, 2, 0, 0),
  [113] = {.entry = {.count = 1, .reusable = true}}, SHIFT(132),
  [115] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string_length, 2, 0, 0),
  [117] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_set, 1, 0, 0),
  [119] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string_set, 1, 0, 0),
  [121] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_offset, 2, 0, 0),
  [123] = {.entry = {.count = 1, .reusable = true}}, SHIFT(131),
  [125] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string_offset, 2, 0, 0),
  [127] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_set, 3, 0, 0),
  [129] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string_set, 3, 0, 0),
  [131] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_set, 4, 0, 0),
  [133] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string_set, 4, 0, 0),
  [135] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__expression, 1, 0, 0),
  [137] = {.entry = {.count = 1, .reusable = true}}, SHIFT(166),
  [139] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__expression, 1, 0, 0),
  [141] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binary_expression, 3, 0, 11),
  [143] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [145] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [147] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [149] = {.entry = {.count = 1, .reusable = false}}, SHIFT(4),
  [151] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [153] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_binary_expression, 3, 0, 11),
  [155] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parenthesized_expression, 3, 0, 0),
  [157] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_parenthesized_expression, 3, 0, 0),
  [159] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unary_expression, 2, 0, 8),
  [161] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_unary_expression, 2, 0, 8),
  [163] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [165] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [167] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_of_expression, 3, 0, 0),
  [169] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_of_expression, 3, 0, 0),
  [171] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [173] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_length, 5, 0, 0),
  [175] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string_length, 5, 0, 0),
  [177] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_count, 2, 0, 0),
  [179] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string_count, 2, 0, 0),
  [181] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_offset, 5, 0, 0),
  [183] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string_offset, 5, 0, 0),
  [185] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_for_expression, 8, 0, 0),
  [187] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_for_expression, 8, 0, 0),
  [189] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [191] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_for_of_expression, 10, 0, 0),
  [193] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_for_of_expression, 10, 0, 0),
  [195] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_condition_section, 3, 0, 0),
  [197] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [199] = {.entry = {.count = 1, .reusable = false}}, SHIFT(111),
  [201] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [203] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_definition, 3, 0, 10),
  [205] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [207] = {.entry = {.count = 1, .reusable = false}}, SHIFT(49),
  [209] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [211] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [213] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_string_modifiers_repeat1, 1, 0, 0),
  [215] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_modifiers_repeat1, 1, 0, 0),
  [217] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_regex_string, 3, 0, 0),
  [219] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [221] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [223] = {.entry = {.count = 1, .reusable = true}}, SHIFT(106),
  [225] = {.entry = {.count = 1, .reusable = true}}, SHIFT(164),
  [227] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [229] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [231] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_string_modifiers_repeat1, 2, 0, 0),
  [233] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_string_modifiers_repeat1, 2, 0, 0), SHIFT_REPEAT(53),
  [236] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_modifiers_repeat1, 2, 0, 0), SHIFT_REPEAT(49),
  [239] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_string_modifiers_repeat1, 2, 0, 0), SHIFT_REPEAT(49),
  [242] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [244] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(63),
  [247] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(64),
  [250] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(139),
  [253] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(165),
  [256] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(169),
  [259] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_modifiers, 1, 0, 0),
  [261] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string_modifiers, 1, 0, 0),
  [263] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [265] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_hex_string_repeat1, 2, 0, 0),
  [267] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_hex_string_repeat1, 2, 0, 0), SHIFT_REPEAT(106),
  [270] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_hex_string_repeat1, 2, 0, 0), SHIFT_REPEAT(164),
  [273] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_hex_string_repeat1, 2, 0, 0), SHIFT_REPEAT(57),
  [276] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [278] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_text_string, 1, 0, 0),
  [280] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_text_string, 1, 0, 0),
  [282] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_string_modifiers_repeat1, 4, 0, 0),
  [284] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_modifiers_repeat1, 4, 0, 0),
  [286] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_hex_string, 3, 0, 0),
  [288] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_hex_string, 3, 0, 0),
  [290] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_regex_string, 4, 0, 0),
  [292] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_regex_string, 4, 0, 0),
  [294] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 2, 0, 0),
  [296] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_include_statement, 2, 0, 0),
  [298] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule_body, 4, 0, 0),
  [300] = {.entry = {.count = 1, .reusable = true}}, SHIFT(170),
  [302] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [304] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_strings_section_repeat1, 2, 0, 0), SHIFT_REPEAT(20),
  [307] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_strings_section_repeat1, 2, 0, 0),
  [309] = {.entry = {.count = 1, .reusable = true}}, SHIFT(135),
  [311] = {.entry = {.count = 1, .reusable = true}}, SHIFT(136),
  [313] = {.entry = {.count = 1, .reusable = true}}, SHIFT(137),
  [315] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule_definition, 3, 0, 1),
  [317] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule_body, 5, 0, 0),
  [319] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_strings_section, 3, 0, 0),
  [321] = {.entry = {.count = 1, .reusable = true}}, SHIFT(172),
  [323] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule_definition, 4, 0, 3),
  [325] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule_definition, 5, 0, 5),
  [327] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule_definition, 5, 0, 4),
  [329] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule_definition, 6, 0, 7),
  [331] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule_body, 3, 0, 0),
  [333] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule_definition, 4, 0, 2),
  [335] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [337] = {.entry = {.count = 1, .reusable = true}}, SHIFT(116),
  [339] = {.entry = {.count = 1, .reusable = false}}, SHIFT(14),
  [341] = {.entry = {.count = 1, .reusable = true}}, SHIFT(96),
  [343] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [345] = {.entry = {.count = 1, .reusable = false}}, SHIFT(133),
  [347] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_meta_section, 3, 0, 0),
  [349] = {.entry = {.count = 1, .reusable = true}}, SHIFT(90),
  [351] = {.entry = {.count = 1, .reusable = true}}, SHIFT(163),
  [353] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [355] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_hex_jump, 3, 0, 0),
  [357] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_hex_alternative, 3, 0, 0),
  [359] = {.entry = {.count = 1, .reusable = true}}, SHIFT(94),
  [361] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_meta_section_repeat1, 2, 0, 0), SHIFT_REPEAT(133),
  [364] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_meta_section_repeat1, 2, 0, 0),
  [366] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_hex_jump, 4, 0, 0),
  [368] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_hex_alternative, 4, 0, 0),
  [370] = {.entry = {.count = 1, .reusable = false}}, SHIFT(15),
  [372] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [374] = {.entry = {.count = 1, .reusable = false}}, SHIFT(13),
  [376] = {.entry = {.count = 1, .reusable = true}}, SHIFT(112),
  [378] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_hex_jump, 5, 0, 0),
  [380] = {.entry = {.count = 1, .reusable = false}}, SHIFT(12),
  [382] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [384] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_regex_string_content, 1, 0, 0),
  [386] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [388] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_regex_string_content_repeat1, 2, 0, 0),
  [390] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_regex_string_content_repeat1, 2, 0, 0), SHIFT_REPEAT(102),
  [393] = {.entry = {.count = 1, .reusable = true}}, SHIFT(118),
  [395] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [397] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_double_quoted_string_repeat1, 2, 0, 0),
  [399] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_double_quoted_string_repeat1, 2, 0, 0), SHIFT_REPEAT(104),
  [402] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [404] = {.entry = {.count = 1, .reusable = true}}, SHIFT(110),
  [406] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_string_set_repeat1, 2, 0, 0),
  [408] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_string_set_repeat1, 2, 0, 0), SHIFT_REPEAT(116),
  [411] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_hex_alternative_repeat1, 2, 0, 0),
  [413] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_hex_alternative_repeat1, 2, 0, 0), SHIFT_REPEAT(163),
  [416] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [418] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [420] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_single_quoted_string_repeat1, 2, 0, 0),
  [422] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_single_quoted_string_repeat1, 2, 0, 0), SHIFT_REPEAT(112),
  [425] = {.entry = {.count = 1, .reusable = true}}, SHIFT(142),
  [427] = {.entry = {.count = 1, .reusable = true}}, SHIFT(144),
  [429] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_tag_list, 2, 0, 0),
  [431] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_tag_list_repeat1, 2, 0, 0), SHIFT_REPEAT(144),
  [434] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_tag_list_repeat1, 2, 0, 0),
  [436] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_tag_list, 3, 0, 0),
  [438] = {.entry = {.count = 1, .reusable = true}}, SHIFT(133),
  [440] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_meta_definition, 3, 0, 9),
  [442] = {.entry = {.count = 1, .reusable = true}}, SHIFT(134),
  [444] = {.entry = {.count = 1, .reusable = true}}, SHIFT(113),
  [446] = {.entry = {.count = 1, .reusable = true}}, SHIFT(154),
  [448] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [450] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [452] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [454] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [456] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [458] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [460] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [462] = {.entry = {.count = 1, .reusable = true}}, SHIFT(168),
  [464] = {.entry = {.count = 1, .reusable = true}}, SHIFT(160),
  [466] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [468] = {.entry = {.count = 1, .reusable = true}}, SHIFT(152),
  [470] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_tag_list_repeat1, 1, 0, 6),
  [472] = {.entry = {.count = 1, .reusable = false}}, SHIFT(50),
  [474] = {.entry = {.count = 1, .reusable = true}}, SHIFT(82),
  [476] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [478] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_definition, 4, 0, 10),
  [480] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [482] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [484] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [486] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [488] = {.entry = {.count = 1, .reusable = true}}, SHIFT(171),
  [490] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [492] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [494] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [496] = {.entry = {.count = 1, .reusable = true}}, SHIFT(107),
  [498] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [500] = {.entry = {.count = 1, .reusable = true}}, SHIFT(149),
  [502] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [504] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_quantifier, 2, 0, 0),
  [506] = {.entry = {.count = 1, .reusable = true}}, SHIFT(159),
  [508] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [510] = {.entry = {.count = 1, .reusable = true}}, SHIFT(117),
  [512] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_range, 5, 0, 0),
  [514] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_quantifier, 1, 0, 0),
  [516] = {.entry = {.count = 1, .reusable = true}}, SHIFT(103),
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

TS_PUBLIC const TSLanguage *tree_sitter_yara(void) {
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
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
