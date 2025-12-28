#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 269
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 90
#define ALIAS_COUNT 5
#define TOKEN_COUNT 49
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 1
#define MAX_ALIAS_SEQUENCE_LENGTH 6
#define PRODUCTION_ID_COUNT 8

enum {
  anon_sym_EQ_EQ_EQ_EQ_EQ = 1,
  aux_sym__separator_token1 = 2,
  anon_sym_ATauthor = 3,
  anon_sym_ATsee = 4,
  anon_sym_ATparam = 5,
  anon_sym_EQ_EQ = 6,
  anon_sym_EQ_EQ_EQ = 7,
  anon_sym_EQ_EQ_EQ_EQ = 8,
  anon_sym_LBRACE = 9,
  aux_sym_macro_token1 = 10,
  anon_sym_RBRACE = 11,
  anon_sym_TODO_COLON = 12,
  aux_sym_tag_token1 = 13,
  aux_sym_argument_token1 = 14,
  anon_sym_ATlink = 15,
  anon_sym_DOT = 16,
  anon_sym_SLASH = 17,
  anon_sym_COLON = 18,
  anon_sym_LPAREN = 19,
  anon_sym_RPAREN = 20,
  sym_arity = 21,
  anon_sym_LTem_GT = 22,
  anon_sym_LT_SLASHem_GT = 23,
  anon_sym_LTstrong_GT = 24,
  anon_sym_LT_SLASHstrong_GT = 25,
  anon_sym_LT = 26,
  aux_sym_xhtml_tag_token1 = 27,
  anon_sym_GT = 28,
  anon_sym_AT_LBRACE = 29,
  anon_sym_AT_RBRACE = 30,
  anon_sym_AT_AT = 31,
  sym_quote_escape = 32,
  anon_sym_BQUOTE = 33,
  aux_sym__inline_quote_token1 = 34,
  anon_sym_SQUOTE = 35,
  anon_sym_BQUOTE_BQUOTE = 36,
  aux_sym__double_inline_quote_token1 = 37,
  anon_sym_SQUOTE_SQUOTE = 38,
  anon_sym_BQUOTE_BQUOTE_BQUOTE = 39,
  aux_sym__triple_inline_quote_token1 = 40,
  anon_sym_SQUOTE_SQUOTE_SQUOTE = 41,
  sym_language_identifier = 42,
  aux_sym_quote_content_token1 = 43,
  sym__terminator = 44,
  sym__word = 45,
  sym__unquoted_atom = 46,
  sym__escape_sequence = 47,
  sym__quoted_content = 48,
  sym_source = 49,
  sym__line = 50,
  sym__separator = 51,
  sym__tag_line = 52,
  sym__author_line = 53,
  sym__see_line = 54,
  sym__param_line = 55,
  aux_sym__text_line = 56,
  sym_section = 57,
  sym_macro = 58,
  sym_tag = 59,
  sym_argument = 60,
  sym__link_macro = 61,
  sym_expression = 62,
  sym_module = 63,
  sym_function = 64,
  sym_type = 65,
  sym__xhtml_tag = 66,
  sym_em_xhtml_tag = 67,
  sym_strong_xhtml_tag = 68,
  sym_xhtml_tag = 69,
  sym_xhtml_tag_content = 70,
  sym_macro_escape = 71,
  sym_inline_quote = 72,
  sym__inline_quote = 73,
  sym__double_inline_quote = 74,
  sym__triple_inline_quote = 75,
  sym_block_quote = 76,
  sym_quote_content = 77,
  sym__atom = 78,
  sym__quoted_atom = 79,
  aux_sym_source_repeat1 = 80,
  aux_sym_source_repeat2 = 81,
  aux_sym__author_line_repeat1 = 82,
  aux_sym_argument_repeat1 = 83,
  aux_sym_xhtml_tag_repeat1 = 84,
  aux_sym_xhtml_tag_content_repeat1 = 85,
  aux_sym__double_inline_quote_repeat1 = 86,
  aux_sym__triple_inline_quote_repeat1 = 87,
  aux_sym_quote_content_repeat1 = 88,
  aux_sym__quoted_atom_repeat1 = 89,
  alias_sym_description = 90,
  alias_sym_email_address = 91,
  alias_sym_parameter = 92,
  alias_sym_quote_marker = 93,
  alias_sym_section_content = 94,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_EQ_EQ_EQ_EQ_EQ] = "=====",
  [aux_sym__separator_token1] = "_separator_token1",
  [anon_sym_ATauthor] = "tag",
  [anon_sym_ATsee] = "tag",
  [anon_sym_ATparam] = "tag",
  [anon_sym_EQ_EQ] = "section_marker",
  [anon_sym_EQ_EQ_EQ] = "section_marker",
  [anon_sym_EQ_EQ_EQ_EQ] = "section_marker",
  [anon_sym_LBRACE] = "{",
  [aux_sym_macro_token1] = "macro_token1",
  [anon_sym_RBRACE] = "}",
  [anon_sym_TODO_COLON] = "TODO:",
  [aux_sym_tag_token1] = "tag_token1",
  [aux_sym_argument_token1] = "argument_token1",
  [anon_sym_ATlink] = "tag",
  [anon_sym_DOT] = ".",
  [anon_sym_SLASH] = "/",
  [anon_sym_COLON] = ":",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [sym_arity] = "arity",
  [anon_sym_LTem_GT] = "open_xhtml_tag",
  [anon_sym_LT_SLASHem_GT] = "close_xhtml_tag",
  [anon_sym_LTstrong_GT] = "open_xhtml_tag",
  [anon_sym_LT_SLASHstrong_GT] = "close_xhtml_tag",
  [anon_sym_LT] = "<",
  [aux_sym_xhtml_tag_token1] = "xhtml_tag_token1",
  [anon_sym_GT] = ">",
  [anon_sym_AT_LBRACE] = "@{",
  [anon_sym_AT_RBRACE] = "@}",
  [anon_sym_AT_AT] = "@@",
  [sym_quote_escape] = "quote_escape",
  [anon_sym_BQUOTE] = "`",
  [aux_sym__inline_quote_token1] = "_inline_quote_token1",
  [anon_sym_SQUOTE] = "'",
  [anon_sym_BQUOTE_BQUOTE] = "``",
  [aux_sym__double_inline_quote_token1] = "_double_inline_quote_token1",
  [anon_sym_SQUOTE_SQUOTE] = "''",
  [anon_sym_BQUOTE_BQUOTE_BQUOTE] = "```",
  [aux_sym__triple_inline_quote_token1] = "_triple_inline_quote_token1",
  [anon_sym_SQUOTE_SQUOTE_SQUOTE] = "'''",
  [sym_language_identifier] = "language_identifier",
  [aux_sym_quote_content_token1] = "quote_content_token1",
  [sym__terminator] = "_terminator",
  [sym__word] = "_word",
  [sym__unquoted_atom] = "_unquoted_atom",
  [sym__escape_sequence] = "_escape_sequence",
  [sym__quoted_content] = "_quoted_content",
  [sym_source] = "source",
  [sym__line] = "_line",
  [sym__separator] = "_separator",
  [sym__tag_line] = "_tag_line",
  [sym__author_line] = "_author_line",
  [sym__see_line] = "_see_line",
  [sym__param_line] = "_param_line",
  [aux_sym__text_line] = "_text_line",
  [sym_section] = "section",
  [sym_macro] = "macro",
  [sym_tag] = "tag",
  [sym_argument] = "argument",
  [sym__link_macro] = "_link_macro",
  [sym_expression] = "expression",
  [sym_module] = "module",
  [sym_function] = "function",
  [sym_type] = "type",
  [sym__xhtml_tag] = "_xhtml_tag",
  [sym_em_xhtml_tag] = "em_xhtml_tag",
  [sym_strong_xhtml_tag] = "strong_xhtml_tag",
  [sym_xhtml_tag] = "xhtml_tag",
  [sym_xhtml_tag_content] = "xhtml_tag_content",
  [sym_macro_escape] = "macro_escape",
  [sym_inline_quote] = "inline_quote",
  [sym__inline_quote] = "_inline_quote",
  [sym__double_inline_quote] = "_double_inline_quote",
  [sym__triple_inline_quote] = "_triple_inline_quote",
  [sym_block_quote] = "block_quote",
  [sym_quote_content] = "quote_content",
  [sym__atom] = "_atom",
  [sym__quoted_atom] = "_quoted_atom",
  [aux_sym_source_repeat1] = "source_repeat1",
  [aux_sym_source_repeat2] = "source_repeat2",
  [aux_sym__author_line_repeat1] = "_author_line_repeat1",
  [aux_sym_argument_repeat1] = "argument_repeat1",
  [aux_sym_xhtml_tag_repeat1] = "xhtml_tag_repeat1",
  [aux_sym_xhtml_tag_content_repeat1] = "xhtml_tag_content_repeat1",
  [aux_sym__double_inline_quote_repeat1] = "_double_inline_quote_repeat1",
  [aux_sym__triple_inline_quote_repeat1] = "_triple_inline_quote_repeat1",
  [aux_sym_quote_content_repeat1] = "quote_content_repeat1",
  [aux_sym__quoted_atom_repeat1] = "_quoted_atom_repeat1",
  [alias_sym_description] = "description",
  [alias_sym_email_address] = "email_address",
  [alias_sym_parameter] = "parameter",
  [alias_sym_quote_marker] = "quote_marker",
  [alias_sym_section_content] = "section_content",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_EQ_EQ_EQ_EQ_EQ] = anon_sym_EQ_EQ_EQ_EQ_EQ,
  [aux_sym__separator_token1] = aux_sym__separator_token1,
  [anon_sym_ATauthor] = sym_tag,
  [anon_sym_ATsee] = sym_tag,
  [anon_sym_ATparam] = sym_tag,
  [anon_sym_EQ_EQ] = anon_sym_EQ_EQ,
  [anon_sym_EQ_EQ_EQ] = anon_sym_EQ_EQ,
  [anon_sym_EQ_EQ_EQ_EQ] = anon_sym_EQ_EQ,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [aux_sym_macro_token1] = aux_sym_macro_token1,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_TODO_COLON] = anon_sym_TODO_COLON,
  [aux_sym_tag_token1] = aux_sym_tag_token1,
  [aux_sym_argument_token1] = aux_sym_argument_token1,
  [anon_sym_ATlink] = sym_tag,
  [anon_sym_DOT] = anon_sym_DOT,
  [anon_sym_SLASH] = anon_sym_SLASH,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [sym_arity] = sym_arity,
  [anon_sym_LTem_GT] = anon_sym_LTem_GT,
  [anon_sym_LT_SLASHem_GT] = anon_sym_LT_SLASHem_GT,
  [anon_sym_LTstrong_GT] = anon_sym_LTem_GT,
  [anon_sym_LT_SLASHstrong_GT] = anon_sym_LT_SLASHem_GT,
  [anon_sym_LT] = anon_sym_LT,
  [aux_sym_xhtml_tag_token1] = aux_sym_xhtml_tag_token1,
  [anon_sym_GT] = anon_sym_GT,
  [anon_sym_AT_LBRACE] = anon_sym_AT_LBRACE,
  [anon_sym_AT_RBRACE] = anon_sym_AT_RBRACE,
  [anon_sym_AT_AT] = anon_sym_AT_AT,
  [sym_quote_escape] = sym_quote_escape,
  [anon_sym_BQUOTE] = anon_sym_BQUOTE,
  [aux_sym__inline_quote_token1] = aux_sym__inline_quote_token1,
  [anon_sym_SQUOTE] = anon_sym_SQUOTE,
  [anon_sym_BQUOTE_BQUOTE] = anon_sym_BQUOTE_BQUOTE,
  [aux_sym__double_inline_quote_token1] = aux_sym__double_inline_quote_token1,
  [anon_sym_SQUOTE_SQUOTE] = anon_sym_SQUOTE_SQUOTE,
  [anon_sym_BQUOTE_BQUOTE_BQUOTE] = anon_sym_BQUOTE_BQUOTE_BQUOTE,
  [aux_sym__triple_inline_quote_token1] = aux_sym__triple_inline_quote_token1,
  [anon_sym_SQUOTE_SQUOTE_SQUOTE] = anon_sym_SQUOTE_SQUOTE_SQUOTE,
  [sym_language_identifier] = sym_language_identifier,
  [aux_sym_quote_content_token1] = aux_sym_quote_content_token1,
  [sym__terminator] = sym__terminator,
  [sym__word] = sym__word,
  [sym__unquoted_atom] = sym__unquoted_atom,
  [sym__escape_sequence] = sym__escape_sequence,
  [sym__quoted_content] = sym__quoted_content,
  [sym_source] = sym_source,
  [sym__line] = sym__line,
  [sym__separator] = sym__separator,
  [sym__tag_line] = sym__tag_line,
  [sym__author_line] = sym__author_line,
  [sym__see_line] = sym__see_line,
  [sym__param_line] = sym__param_line,
  [aux_sym__text_line] = aux_sym__text_line,
  [sym_section] = sym_section,
  [sym_macro] = sym_macro,
  [sym_tag] = sym_tag,
  [sym_argument] = sym_argument,
  [sym__link_macro] = sym__link_macro,
  [sym_expression] = sym_expression,
  [sym_module] = sym_module,
  [sym_function] = sym_function,
  [sym_type] = sym_type,
  [sym__xhtml_tag] = sym__xhtml_tag,
  [sym_em_xhtml_tag] = sym_em_xhtml_tag,
  [sym_strong_xhtml_tag] = sym_strong_xhtml_tag,
  [sym_xhtml_tag] = sym_xhtml_tag,
  [sym_xhtml_tag_content] = sym_xhtml_tag_content,
  [sym_macro_escape] = sym_macro_escape,
  [sym_inline_quote] = sym_inline_quote,
  [sym__inline_quote] = sym__inline_quote,
  [sym__double_inline_quote] = sym__double_inline_quote,
  [sym__triple_inline_quote] = sym__triple_inline_quote,
  [sym_block_quote] = sym_block_quote,
  [sym_quote_content] = sym_quote_content,
  [sym__atom] = sym__atom,
  [sym__quoted_atom] = sym__quoted_atom,
  [aux_sym_source_repeat1] = aux_sym_source_repeat1,
  [aux_sym_source_repeat2] = aux_sym_source_repeat2,
  [aux_sym__author_line_repeat1] = aux_sym__author_line_repeat1,
  [aux_sym_argument_repeat1] = aux_sym_argument_repeat1,
  [aux_sym_xhtml_tag_repeat1] = aux_sym_xhtml_tag_repeat1,
  [aux_sym_xhtml_tag_content_repeat1] = aux_sym_xhtml_tag_content_repeat1,
  [aux_sym__double_inline_quote_repeat1] = aux_sym__double_inline_quote_repeat1,
  [aux_sym__triple_inline_quote_repeat1] = aux_sym__triple_inline_quote_repeat1,
  [aux_sym_quote_content_repeat1] = aux_sym_quote_content_repeat1,
  [aux_sym__quoted_atom_repeat1] = aux_sym__quoted_atom_repeat1,
  [alias_sym_description] = alias_sym_description,
  [alias_sym_email_address] = alias_sym_email_address,
  [alias_sym_parameter] = alias_sym_parameter,
  [alias_sym_quote_marker] = alias_sym_quote_marker,
  [alias_sym_section_content] = alias_sym_section_content,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_EQ_EQ_EQ_EQ_EQ] = {
    .visible = true,
    .named = false,
  },
  [aux_sym__separator_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_ATauthor] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_ATsee] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_ATparam] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_EQ_EQ] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_EQ_EQ_EQ] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_EQ_EQ_EQ_EQ] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_macro_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_TODO_COLON] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_tag_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_argument_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_ATlink] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_DOT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SLASH] = {
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
  [sym_arity] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LTem_GT] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LT_SLASHem_GT] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LTstrong_GT] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LT_SLASHstrong_GT] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LT] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_xhtml_tag_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_AT_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_AT_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_AT_AT] = {
    .visible = true,
    .named = false,
  },
  [sym_quote_escape] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_BQUOTE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym__inline_quote_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_SQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BQUOTE_BQUOTE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym__double_inline_quote_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_SQUOTE_SQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BQUOTE_BQUOTE_BQUOTE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym__triple_inline_quote_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_SQUOTE_SQUOTE_SQUOTE] = {
    .visible = true,
    .named = false,
  },
  [sym_language_identifier] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_quote_content_token1] = {
    .visible = false,
    .named = false,
  },
  [sym__terminator] = {
    .visible = false,
    .named = true,
  },
  [sym__word] = {
    .visible = false,
    .named = true,
  },
  [sym__unquoted_atom] = {
    .visible = false,
    .named = true,
  },
  [sym__escape_sequence] = {
    .visible = false,
    .named = true,
  },
  [sym__quoted_content] = {
    .visible = false,
    .named = true,
  },
  [sym_source] = {
    .visible = true,
    .named = true,
  },
  [sym__line] = {
    .visible = false,
    .named = true,
  },
  [sym__separator] = {
    .visible = false,
    .named = true,
  },
  [sym__tag_line] = {
    .visible = false,
    .named = true,
  },
  [sym__author_line] = {
    .visible = false,
    .named = true,
  },
  [sym__see_line] = {
    .visible = false,
    .named = true,
  },
  [sym__param_line] = {
    .visible = false,
    .named = true,
  },
  [aux_sym__text_line] = {
    .visible = false,
    .named = false,
  },
  [sym_section] = {
    .visible = true,
    .named = true,
  },
  [sym_macro] = {
    .visible = true,
    .named = true,
  },
  [sym_tag] = {
    .visible = true,
    .named = true,
  },
  [sym_argument] = {
    .visible = true,
    .named = true,
  },
  [sym__link_macro] = {
    .visible = false,
    .named = true,
  },
  [sym_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_module] = {
    .visible = true,
    .named = true,
  },
  [sym_function] = {
    .visible = true,
    .named = true,
  },
  [sym_type] = {
    .visible = true,
    .named = true,
  },
  [sym__xhtml_tag] = {
    .visible = false,
    .named = true,
  },
  [sym_em_xhtml_tag] = {
    .visible = true,
    .named = true,
  },
  [sym_strong_xhtml_tag] = {
    .visible = true,
    .named = true,
  },
  [sym_xhtml_tag] = {
    .visible = true,
    .named = true,
  },
  [sym_xhtml_tag_content] = {
    .visible = true,
    .named = true,
  },
  [sym_macro_escape] = {
    .visible = true,
    .named = true,
  },
  [sym_inline_quote] = {
    .visible = true,
    .named = true,
  },
  [sym__inline_quote] = {
    .visible = false,
    .named = true,
  },
  [sym__double_inline_quote] = {
    .visible = false,
    .named = true,
  },
  [sym__triple_inline_quote] = {
    .visible = false,
    .named = true,
  },
  [sym_block_quote] = {
    .visible = true,
    .named = true,
  },
  [sym_quote_content] = {
    .visible = true,
    .named = true,
  },
  [sym__atom] = {
    .visible = false,
    .named = true,
  },
  [sym__quoted_atom] = {
    .visible = false,
    .named = true,
  },
  [aux_sym_source_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_source_repeat2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__author_line_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_argument_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_xhtml_tag_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_xhtml_tag_content_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__double_inline_quote_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__triple_inline_quote_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_quote_content_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__quoted_atom_repeat1] = {
    .visible = false,
    .named = false,
  },
  [alias_sym_description] = {
    .visible = true,
    .named = true,
  },
  [alias_sym_email_address] = {
    .visible = true,
    .named = true,
  },
  [alias_sym_parameter] = {
    .visible = true,
    .named = true,
  },
  [alias_sym_quote_marker] = {
    .visible = true,
    .named = true,
  },
  [alias_sym_section_content] = {
    .visible = true,
    .named = true,
  },
};

enum {
  field_language = 1,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_language] = "language",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [6] = {.index = 0, .length = 1},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_language, 1},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
  [1] = {
    [1] = alias_sym_email_address,
  },
  [2] = {
    [1] = alias_sym_parameter,
  },
  [3] = {
    [2] = alias_sym_email_address,
  },
  [4] = {
    [1] = alias_sym_section_content,
  },
  [5] = {
    [0] = alias_sym_quote_marker,
    [2] = alias_sym_quote_marker,
  },
  [6] = {
    [0] = alias_sym_quote_marker,
    [3] = alias_sym_quote_marker,
  },
  [7] = {
    [4] = alias_sym_description,
  },
};

static const uint16_t ts_non_terminal_alias_map[] = {
  aux_sym__text_line, 2,
    aux_sym__text_line,
    alias_sym_section_content,
  sym_argument, 2,
    sym_argument,
    alias_sym_description,
  sym_xhtml_tag, 2,
    sym_xhtml_tag,
    alias_sym_email_address,
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
  [7] = 6,
  [8] = 6,
  [9] = 9,
  [10] = 6,
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
  [24] = 23,
  [25] = 25,
  [26] = 26,
  [27] = 27,
  [28] = 26,
  [29] = 25,
  [30] = 26,
  [31] = 25,
  [32] = 27,
  [33] = 26,
  [34] = 25,
  [35] = 35,
  [36] = 36,
  [37] = 37,
  [38] = 36,
  [39] = 39,
  [40] = 40,
  [41] = 35,
  [42] = 42,
  [43] = 43,
  [44] = 44,
  [45] = 45,
  [46] = 46,
  [47] = 47,
  [48] = 48,
  [49] = 43,
  [50] = 42,
  [51] = 36,
  [52] = 52,
  [53] = 53,
  [54] = 54,
  [55] = 48,
  [56] = 56,
  [57] = 47,
  [58] = 58,
  [59] = 46,
  [60] = 60,
  [61] = 37,
  [62] = 39,
  [63] = 40,
  [64] = 35,
  [65] = 44,
  [66] = 45,
  [67] = 46,
  [68] = 47,
  [69] = 48,
  [70] = 43,
  [71] = 42,
  [72] = 47,
  [73] = 45,
  [74] = 44,
  [75] = 35,
  [76] = 40,
  [77] = 52,
  [78] = 39,
  [79] = 37,
  [80] = 53,
  [81] = 54,
  [82] = 60,
  [83] = 58,
  [84] = 56,
  [85] = 58,
  [86] = 60,
  [87] = 37,
  [88] = 39,
  [89] = 58,
  [90] = 40,
  [91] = 60,
  [92] = 56,
  [93] = 44,
  [94] = 45,
  [95] = 95,
  [96] = 46,
  [97] = 54,
  [98] = 48,
  [99] = 52,
  [100] = 53,
  [101] = 53,
  [102] = 52,
  [103] = 54,
  [104] = 36,
  [105] = 42,
  [106] = 43,
  [107] = 56,
  [108] = 47,
  [109] = 40,
  [110] = 43,
  [111] = 111,
  [112] = 111,
  [113] = 111,
  [114] = 111,
  [115] = 40,
  [116] = 48,
  [117] = 117,
  [118] = 46,
  [119] = 39,
  [120] = 37,
  [121] = 39,
  [122] = 37,
  [123] = 58,
  [124] = 43,
  [125] = 48,
  [126] = 47,
  [127] = 46,
  [128] = 58,
  [129] = 129,
  [130] = 129,
  [131] = 131,
  [132] = 132,
  [133] = 133,
  [134] = 133,
  [135] = 129,
  [136] = 132,
  [137] = 132,
  [138] = 132,
  [139] = 129,
  [140] = 133,
  [141] = 133,
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
  [154] = 152,
  [155] = 155,
  [156] = 152,
  [157] = 152,
  [158] = 158,
  [159] = 159,
  [160] = 160,
  [161] = 160,
  [162] = 162,
  [163] = 159,
  [164] = 164,
  [165] = 162,
  [166] = 166,
  [167] = 162,
  [168] = 168,
  [169] = 169,
  [170] = 170,
  [171] = 168,
  [172] = 172,
  [173] = 173,
  [174] = 174,
  [175] = 170,
  [176] = 176,
  [177] = 177,
  [178] = 168,
  [179] = 159,
  [180] = 160,
  [181] = 172,
  [182] = 170,
  [183] = 160,
  [184] = 159,
  [185] = 185,
  [186] = 168,
  [187] = 166,
  [188] = 159,
  [189] = 160,
  [190] = 168,
  [191] = 172,
  [192] = 170,
  [193] = 170,
  [194] = 172,
  [195] = 168,
  [196] = 162,
  [197] = 159,
  [198] = 160,
  [199] = 160,
  [200] = 172,
  [201] = 172,
  [202] = 170,
  [203] = 168,
  [204] = 204,
  [205] = 95,
  [206] = 206,
  [207] = 204,
  [208] = 204,
  [209] = 209,
  [210] = 210,
  [211] = 210,
  [212] = 210,
  [213] = 204,
  [214] = 210,
  [215] = 215,
  [216] = 216,
  [217] = 217,
  [218] = 217,
  [219] = 219,
  [220] = 220,
  [221] = 221,
  [222] = 222,
  [223] = 223,
  [224] = 224,
  [225] = 224,
  [226] = 223,
  [227] = 220,
  [228] = 219,
  [229] = 217,
  [230] = 222,
  [231] = 221,
  [232] = 223,
  [233] = 233,
  [234] = 234,
  [235] = 222,
  [236] = 236,
  [237] = 221,
  [238] = 223,
  [239] = 220,
  [240] = 240,
  [241] = 241,
  [242] = 219,
  [243] = 220,
  [244] = 223,
  [245] = 219,
  [246] = 246,
  [247] = 222,
  [248] = 248,
  [249] = 221,
  [250] = 250,
  [251] = 224,
  [252] = 252,
  [253] = 253,
  [254] = 246,
  [255] = 255,
  [256] = 217,
  [257] = 257,
  [258] = 258,
  [259] = 224,
  [260] = 260,
  [261] = 223,
  [262] = 246,
  [263] = 246,
  [264] = 48,
  [265] = 40,
  [266] = 266,
  [267] = 246,
  [268] = 246,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(63);
      if (lookahead == '\n') ADVANCE(142);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == '\'') ADVANCE(124);
      if (lookahead == '(') ADVANCE(102);
      if (lookahead == ')') ADVANCE(103);
      if (lookahead == '.') ADVANCE(99);
      if (lookahead == '/') ADVANCE(100);
      if (lookahead == ':') ADVANCE(101);
      if (lookahead == '<') ADVANCE(110);
      if (lookahead == '=') ADVANCE(25);
      if (lookahead == '>') ADVANCE(116);
      if (lookahead == '@') ADVANCE(31);
      if (lookahead == 'T') ADVANCE(34);
      if (lookahead == '\\') ADVANCE(36);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '{') ADVANCE(75);
      if (lookahead == '}') ADVANCE(78);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(104);
      if (('a' <= lookahead && lookahead <= 'z') ||
          (224 <= lookahead && lookahead <= 246) ||
          (248 <= lookahead && lookahead <= 255)) ADVANCE(168);
      if ((1 <= lookahead && lookahead <= '\t') ||
          (17 <= lookahead && lookahead <= ' ') ||
          (128 <= lookahead && lookahead <= 160)) SKIP(0)
      END_STATE();
    case 1:
      if (lookahead == '\n') ADVANCE(142);
      END_STATE();
    case 2:
      if (lookahead == '\n') ADVANCE(142);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == '<') ADVANCE(113);
      if (lookahead == '=') ADVANCE(155);
      if (lookahead == '@') ADVANCE(165);
      if (lookahead == 'T') ADVANCE(163);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '{') ADVANCE(75);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(2)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(143);
      if (lookahead != 0) ADVANCE(167);
      END_STATE();
    case 3:
      if (lookahead == '\n') ADVANCE(142);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == '<') ADVANCE(113);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '{') ADVANCE(75);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(3)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(144);
      if (lookahead != 0) ADVANCE(167);
      END_STATE();
    case 4:
      if (lookahead == '\n') ADVANCE(142);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == '<') ADVANCE(111);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(4)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(145);
      if (lookahead != 0 &&
          lookahead != '{') ADVANCE(167);
      END_STATE();
    case 5:
      if (lookahead == '\n') ADVANCE(142);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == '<') ADVANCE(109);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(5)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(146);
      if (lookahead != 0 &&
          lookahead != '{') ADVANCE(167);
      END_STATE();
    case 6:
      if (lookahead == '\n') ADVANCE(142);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == '<') ADVANCE(109);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(6)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(147);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{') ADVANCE(167);
      END_STATE();
    case 7:
      if (lookahead == '\n') ADVANCE(142);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == '<') ADVANCE(112);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(7)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(148);
      if (lookahead != 0 &&
          lookahead != '{') ADVANCE(167);
      END_STATE();
    case 8:
      if (lookahead == '\n') ADVANCE(137);
      END_STATE();
    case 9:
      if (lookahead == '\n') ADVANCE(137);
      if (lookahead == '\r') ADVANCE(8);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(9);
      END_STATE();
    case 10:
      if (lookahead == '"') ADVANCE(174);
      if (lookahead == '\'') ADVANCE(124);
      if (lookahead == '\\') ADVANCE(176);
      if ((1 <= lookahead && lookahead <= '\t') ||
          (17 <= lookahead && lookahead <= ' ') ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(175);
      if (lookahead != 0) ADVANCE(177);
      END_STATE();
    case 11:
      if (lookahead == '\'') ADVANCE(135);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(138);
      if ((1 <= lookahead && lookahead <= '\t') ||
          (17 <= lookahead && lookahead <= ' ') ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(133);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(132);
      if (lookahead != 0) ADVANCE(131);
      END_STATE();
    case 12:
      if (lookahead == '\'') ADVANCE(135);
      if ((1 <= lookahead && lookahead <= '\t') ||
          (17 <= lookahead && lookahead <= ' ') ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(134);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(131);
      END_STATE();
    case 13:
      if (lookahead == '\'') ADVANCE(14);
      END_STATE();
    case 14:
      if (lookahead == '\'') ADVANCE(136);
      END_STATE();
    case 15:
      if (lookahead == '\'') ADVANCE(128);
      if ((1 <= lookahead && lookahead <= '\t') ||
          (17 <= lookahead && lookahead <= ' ') ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(127);
      if (lookahead != 0 &&
          lookahead != '`') ADVANCE(126);
      END_STATE();
    case 16:
      if (lookahead == '\'') ADVANCE(139);
      if ((1 <= lookahead && lookahead <= '\t') ||
          (17 <= lookahead && lookahead <= ' ') ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(140);
      if (lookahead != 0) ADVANCE(138);
      END_STATE();
    case 17:
      if (lookahead == '\'') ADVANCE(13);
      if (lookahead == '@') ADVANCE(42);
      if (lookahead == 'T') ADVANCE(34);
      if ((1 <= lookahead && lookahead <= '\t') ||
          (17 <= lookahead && lookahead <= ' ') ||
          (128 <= lookahead && lookahead <= 160)) SKIP(17)
      END_STATE();
    case 18:
      if (lookahead == ':') ADVANCE(79);
      END_STATE();
    case 19:
      if (lookahead == '<') ADVANCE(113);
      if (lookahead == '=') ADVANCE(155);
      if (lookahead == '@') ADVANCE(165);
      if (lookahead == 'T') ADVANCE(163);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '{') ADVANCE(75);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(19)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(150);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(167);
      END_STATE();
    case 20:
      if (lookahead == '<') ADVANCE(113);
      if (lookahead == '=') ADVANCE(161);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '{') ADVANCE(75);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(20)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(151);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(167);
      END_STATE();
    case 21:
      if (lookahead == '<') ADVANCE(113);
      if (lookahead == '=') ADVANCE(158);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '{') ADVANCE(75);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(21)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(152);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(167);
      END_STATE();
    case 22:
      if (lookahead == '<') ADVANCE(113);
      if (lookahead == '=') ADVANCE(160);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '{') ADVANCE(75);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(22)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(153);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(167);
      END_STATE();
    case 23:
      if (lookahead == '<') ADVANCE(113);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '{') ADVANCE(75);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(23)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(154);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(167);
      END_STATE();
    case 24:
      if (lookahead == '<') ADVANCE(54);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(24)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(166);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '`' &&
          lookahead != '{') ADVANCE(167);
      END_STATE();
    case 25:
      if (lookahead == '=') ADVANCE(70);
      END_STATE();
    case 26:
      if (lookahead == '>') ADVANCE(116);
      if ((1 <= lookahead && lookahead <= '\t') ||
          (17 <= lookahead && lookahead <= ' ') ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(115);
      if (lookahead != 0) ADVANCE(114);
      END_STATE();
    case 27:
      if (lookahead == '>') ADVANCE(105);
      END_STATE();
    case 28:
      if (lookahead == '>') ADVANCE(106);
      END_STATE();
    case 29:
      if (lookahead == '>') ADVANCE(107);
      END_STATE();
    case 30:
      if (lookahead == '>') ADVANCE(108);
      END_STATE();
    case 31:
      if (lookahead == '@') ADVANCE(119);
      if (lookahead == 'a') ADVANCE(93);
      if (lookahead == 'l') ADVANCE(85);
      if (lookahead == 'p') ADVANCE(80);
      if (lookahead == 's') ADVANCE(83);
      if (lookahead == '{') ADVANCE(117);
      if (lookahead == '}') ADVANCE(118);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 32:
      if (lookahead == '@') ADVANCE(96);
      if (lookahead == '}') ADVANCE(78);
      if ((1 <= lookahead && lookahead <= '\t') ||
          (17 <= lookahead && lookahead <= ' ') ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(97);
      if (lookahead != 0) ADVANCE(95);
      END_STATE();
    case 33:
      if (lookahead == 'D') ADVANCE(35);
      END_STATE();
    case 34:
      if (lookahead == 'O') ADVANCE(33);
      END_STATE();
    case 35:
      if (lookahead == 'O') ADVANCE(18);
      END_STATE();
    case 36:
      if (lookahead == '^') ADVANCE(173);
      if (lookahead == 'x') ADVANCE(170);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(172);
      if ((' ' <= lookahead && lookahead <= 127)) ADVANCE(169);
      END_STATE();
    case 37:
      if (lookahead == '`') ADVANCE(167);
      END_STATE();
    case 38:
      if (lookahead == 'e') ADVANCE(44);
      END_STATE();
    case 39:
      if (lookahead == 'e') ADVANCE(44);
      if (lookahead == 's') ADVANCE(53);
      END_STATE();
    case 40:
      if (lookahead == 'g') ADVANCE(29);
      END_STATE();
    case 41:
      if (lookahead == 'g') ADVANCE(30);
      END_STATE();
    case 42:
      if (lookahead == 'l') ADVANCE(85);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 43:
      if (lookahead == 'm') ADVANCE(27);
      END_STATE();
    case 44:
      if (lookahead == 'm') ADVANCE(28);
      END_STATE();
    case 45:
      if (lookahead == 'n') ADVANCE(40);
      END_STATE();
    case 46:
      if (lookahead == 'n') ADVANCE(41);
      END_STATE();
    case 47:
      if (lookahead == 'o') ADVANCE(45);
      END_STATE();
    case 48:
      if (lookahead == 'o') ADVANCE(46);
      END_STATE();
    case 49:
      if (lookahead == 'r') ADVANCE(47);
      END_STATE();
    case 50:
      if (lookahead == 'r') ADVANCE(48);
      END_STATE();
    case 51:
      if (lookahead == 's') ADVANCE(53);
      END_STATE();
    case 52:
      if (lookahead == 't') ADVANCE(49);
      END_STATE();
    case 53:
      if (lookahead == 't') ADVANCE(50);
      END_STATE();
    case 54:
      if (lookahead == '{') ADVANCE(37);
      END_STATE();
    case 55:
      if (lookahead == '}') ADVANCE(78);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(76);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(77);
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) SKIP(55)
      END_STATE();
    case 56:
      if (lookahead == '}') ADVANCE(169);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(56);
      END_STATE();
    case 57:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(169);
      END_STATE();
    case 58:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(56);
      END_STATE();
    case 59:
      if ((1 <= lookahead && lookahead <= '\t') ||
          (17 <= lookahead && lookahead <= ' ') ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(122);
      if (lookahead != 0 &&
          lookahead != '\'') ADVANCE(123);
      END_STATE();
    case 60:
      if (lookahead != 0 &&
          (lookahead < 1 || '\t' < lookahead) &&
          (lookahead < 17 || ' ' < lookahead) &&
          (lookahead < 128 || 160 < lookahead)) ADVANCE(138);
      if ((1 <= lookahead && lookahead <= '\t') ||
          (17 <= lookahead && lookahead <= ' ') ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(141);
      END_STATE();
    case 61:
      if (eof) ADVANCE(63);
      if (lookahead == '\n') ADVANCE(142);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == '<') ADVANCE(113);
      if (lookahead == '=') ADVANCE(155);
      if (lookahead == '@') ADVANCE(165);
      if (lookahead == 'T') ADVANCE(163);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '{') ADVANCE(75);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(61)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(143);
      if (lookahead != 0) ADVANCE(167);
      END_STATE();
    case 62:
      if (eof) ADVANCE(63);
      if (lookahead == '<') ADVANCE(113);
      if (lookahead == '=') ADVANCE(155);
      if (lookahead == '@') ADVANCE(165);
      if (lookahead == 'T') ADVANCE(163);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '{') ADVANCE(75);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(62)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(150);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(167);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(anon_sym_EQ_EQ_EQ_EQ_EQ);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(aux_sym__separator_token1);
      if (lookahead == '=') ADVANCE(65);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(anon_sym_ATauthor);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(anon_sym_ATsee);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(anon_sym_ATparam);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(anon_sym_EQ_EQ);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(anon_sym_EQ_EQ);
      if (lookahead == '=') ADVANCE(72);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(anon_sym_EQ_EQ_EQ);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(anon_sym_EQ_EQ_EQ);
      if (lookahead == '=') ADVANCE(74);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(anon_sym_EQ_EQ_EQ_EQ);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(anon_sym_EQ_EQ_EQ_EQ);
      if (lookahead == '=') ADVANCE(64);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(aux_sym_macro_token1);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(76);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(77);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(aux_sym_macro_token1);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(77);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(anon_sym_TODO_COLON);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(aux_sym_tag_token1);
      if (lookahead == 'a') ADVANCE(91);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(aux_sym_tag_token1);
      if (lookahead == 'a') ADVANCE(87);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(aux_sym_tag_token1);
      if (lookahead == 'e') ADVANCE(67);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(aux_sym_tag_token1);
      if (lookahead == 'e') ADVANCE(82);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(aux_sym_tag_token1);
      if (lookahead == 'h') ADVANCE(89);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(aux_sym_tag_token1);
      if (lookahead == 'i') ADVANCE(88);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(aux_sym_tag_token1);
      if (lookahead == 'k') ADVANCE(98);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(aux_sym_tag_token1);
      if (lookahead == 'm') ADVANCE(68);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(aux_sym_tag_token1);
      if (lookahead == 'n') ADVANCE(86);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(aux_sym_tag_token1);
      if (lookahead == 'o') ADVANCE(90);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(aux_sym_tag_token1);
      if (lookahead == 'r') ADVANCE(66);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(aux_sym_tag_token1);
      if (lookahead == 'r') ADVANCE(81);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(aux_sym_tag_token1);
      if (lookahead == 't') ADVANCE(84);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(aux_sym_tag_token1);
      if (lookahead == 'u') ADVANCE(92);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(aux_sym_tag_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(aux_sym_argument_token1);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(aux_sym_argument_token1);
      if (lookahead == '@') ADVANCE(119);
      if (lookahead == '{') ADVANCE(117);
      if (lookahead == '}') ADVANCE(118);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(aux_sym_argument_token1);
      if (lookahead == '@') ADVANCE(96);
      if ((1 <= lookahead && lookahead <= '\t') ||
          (17 <= lookahead && lookahead <= ' ') ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(97);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(95);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(anon_sym_ATlink);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(anon_sym_DOT);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(anon_sym_SLASH);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(sym_arity);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(104);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(anon_sym_LTem_GT);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(anon_sym_LT_SLASHem_GT);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(anon_sym_LTstrong_GT);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(anon_sym_LT_SLASHstrong_GT);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(anon_sym_LT);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '/') ADVANCE(39);
      if (lookahead == 'e') ADVANCE(43);
      if (lookahead == 's') ADVANCE(52);
      END_STATE();
    case 111:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '/') ADVANCE(38);
      END_STATE();
    case 112:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '/') ADVANCE(51);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == 'e') ADVANCE(43);
      if (lookahead == 's') ADVANCE(52);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(aux_sym_xhtml_tag_token1);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(aux_sym_xhtml_tag_token1);
      if ((1 <= lookahead && lookahead <= '\t') ||
          (17 <= lookahead && lookahead <= ' ') ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(115);
      if (lookahead != 0 &&
          lookahead != '>') ADVANCE(114);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(anon_sym_GT);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(anon_sym_AT_LBRACE);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(anon_sym_AT_RBRACE);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(anon_sym_AT_AT);
      END_STATE();
    case 120:
      ACCEPT_TOKEN(sym_quote_escape);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(anon_sym_BQUOTE);
      if (lookahead == '\'') ADVANCE(120);
      if (lookahead == '`') ADVANCE(125);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(aux_sym__inline_quote_token1);
      if ((1 <= lookahead && lookahead <= '\t') ||
          (17 <= lookahead && lookahead <= ' ') ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(122);
      if (lookahead != 0 &&
          lookahead != '\'') ADVANCE(123);
      END_STATE();
    case 123:
      ACCEPT_TOKEN(aux_sym__inline_quote_token1);
      if (lookahead != 0 &&
          lookahead != '\'') ADVANCE(123);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(anon_sym_BQUOTE_BQUOTE);
      if (lookahead == '`') ADVANCE(130);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(aux_sym__double_inline_quote_token1);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(aux_sym__double_inline_quote_token1);
      if (lookahead == '\'') ADVANCE(128);
      if ((1 <= lookahead && lookahead <= '\t') ||
          (17 <= lookahead && lookahead <= ' ') ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(127);
      if (lookahead != 0 &&
          lookahead != '`') ADVANCE(126);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(aux_sym__double_inline_quote_token1);
      if (lookahead == '\'') ADVANCE(129);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(anon_sym_SQUOTE_SQUOTE);
      END_STATE();
    case 130:
      ACCEPT_TOKEN(anon_sym_BQUOTE_BQUOTE_BQUOTE);
      END_STATE();
    case 131:
      ACCEPT_TOKEN(aux_sym__triple_inline_quote_token1);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(aux_sym__triple_inline_quote_token1);
      if (lookahead == '\n') ADVANCE(137);
      if (lookahead == '\r') ADVANCE(8);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(9);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(aux_sym__triple_inline_quote_token1);
      if (lookahead == '\'') ADVANCE(135);
      if ((1 <= lookahead && lookahead <= '\t') ||
          (17 <= lookahead && lookahead <= ' ') ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(133);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(132);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(131);
      END_STATE();
    case 134:
      ACCEPT_TOKEN(aux_sym__triple_inline_quote_token1);
      if (lookahead == '\'') ADVANCE(135);
      if ((1 <= lookahead && lookahead <= '\t') ||
          (17 <= lookahead && lookahead <= ' ') ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(134);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(131);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(aux_sym__triple_inline_quote_token1);
      if (lookahead == '\'') ADVANCE(14);
      END_STATE();
    case 136:
      ACCEPT_TOKEN(anon_sym_SQUOTE_SQUOTE_SQUOTE);
      END_STATE();
    case 137:
      ACCEPT_TOKEN(sym_language_identifier);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(aux_sym_quote_content_token1);
      END_STATE();
    case 139:
      ACCEPT_TOKEN(aux_sym_quote_content_token1);
      if (lookahead == '\'') ADVANCE(14);
      END_STATE();
    case 140:
      ACCEPT_TOKEN(aux_sym_quote_content_token1);
      if (lookahead == '\'') ADVANCE(139);
      if ((1 <= lookahead && lookahead <= '\t') ||
          (17 <= lookahead && lookahead <= ' ') ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(140);
      if (lookahead != 0) ADVANCE(138);
      END_STATE();
    case 141:
      ACCEPT_TOKEN(aux_sym_quote_content_token1);
      if (lookahead != 0 &&
          (lookahead < 1 || '\t' < lookahead) &&
          (lookahead < 17 || ' ' < lookahead) &&
          (lookahead < 128 || 160 < lookahead)) ADVANCE(138);
      if ((1 <= lookahead && lookahead <= '\t') ||
          (17 <= lookahead && lookahead <= ' ') ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(141);
      END_STATE();
    case 142:
      ACCEPT_TOKEN(sym__terminator);
      END_STATE();
    case 143:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '\n') ADVANCE(142);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == '<') ADVANCE(113);
      if (lookahead == '=') ADVANCE(155);
      if (lookahead == '@') ADVANCE(165);
      if (lookahead == 'T') ADVANCE(163);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '{') ADVANCE(75);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(2)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(143);
      if (lookahead != 0) ADVANCE(167);
      END_STATE();
    case 144:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '\n') ADVANCE(142);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == '<') ADVANCE(113);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '{') ADVANCE(75);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(3)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(144);
      if (lookahead != 0) ADVANCE(167);
      END_STATE();
    case 145:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '\n') ADVANCE(142);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == '<') ADVANCE(111);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(4)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(145);
      if (lookahead != 0 &&
          lookahead != '{') ADVANCE(167);
      END_STATE();
    case 146:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '\n') ADVANCE(142);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == '<') ADVANCE(109);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(5)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(146);
      if (lookahead != 0 &&
          lookahead != '{') ADVANCE(167);
      END_STATE();
    case 147:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '\n') ADVANCE(142);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == '<') ADVANCE(109);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(6)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(147);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{') ADVANCE(167);
      END_STATE();
    case 148:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '\n') ADVANCE(142);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == '<') ADVANCE(112);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(7)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(148);
      if (lookahead != 0 &&
          lookahead != '{') ADVANCE(167);
      END_STATE();
    case 149:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == ':') ADVANCE(79);
      if (lookahead == '<') ADVANCE(54);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '`' &&
          lookahead != '{') ADVANCE(167);
      END_STATE();
    case 150:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '<') ADVANCE(113);
      if (lookahead == '=') ADVANCE(155);
      if (lookahead == '@') ADVANCE(165);
      if (lookahead == 'T') ADVANCE(163);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '{') ADVANCE(75);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(19)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(150);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(167);
      END_STATE();
    case 151:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '<') ADVANCE(113);
      if (lookahead == '=') ADVANCE(161);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '{') ADVANCE(75);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(20)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(151);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(167);
      END_STATE();
    case 152:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '<') ADVANCE(113);
      if (lookahead == '=') ADVANCE(158);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '{') ADVANCE(75);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(21)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(152);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(167);
      END_STATE();
    case 153:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '<') ADVANCE(113);
      if (lookahead == '=') ADVANCE(160);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '{') ADVANCE(75);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(22)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(153);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(167);
      END_STATE();
    case 154:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '<') ADVANCE(113);
      if (lookahead == '`') ADVANCE(121);
      if (lookahead == '{') ADVANCE(75);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(23)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(154);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(167);
      END_STATE();
    case 155:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '<') ADVANCE(54);
      if (lookahead == '=') ADVANCE(70);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '`' &&
          lookahead != '{') ADVANCE(167);
      END_STATE();
    case 156:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '<') ADVANCE(54);
      if (lookahead == '=') ADVANCE(73);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '`' &&
          lookahead != '{') ADVANCE(167);
      END_STATE();
    case 157:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '<') ADVANCE(54);
      if (lookahead == '=') ADVANCE(71);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '`' &&
          lookahead != '{') ADVANCE(167);
      END_STATE();
    case 158:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '<') ADVANCE(54);
      if (lookahead == '=') ADVANCE(69);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '`' &&
          lookahead != '{') ADVANCE(167);
      END_STATE();
    case 159:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '<') ADVANCE(54);
      if (lookahead == '=') ADVANCE(156);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '`' &&
          lookahead != '{') ADVANCE(167);
      END_STATE();
    case 160:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '<') ADVANCE(54);
      if (lookahead == '=') ADVANCE(157);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '`' &&
          lookahead != '{') ADVANCE(167);
      END_STATE();
    case 161:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '<') ADVANCE(54);
      if (lookahead == '=') ADVANCE(159);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '`' &&
          lookahead != '{') ADVANCE(167);
      END_STATE();
    case 162:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '<') ADVANCE(54);
      if (lookahead == 'D') ADVANCE(164);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '`' &&
          lookahead != '{') ADVANCE(167);
      END_STATE();
    case 163:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '<') ADVANCE(54);
      if (lookahead == 'O') ADVANCE(162);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '`' &&
          lookahead != '{') ADVANCE(167);
      END_STATE();
    case 164:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '<') ADVANCE(54);
      if (lookahead == 'O') ADVANCE(149);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '`' &&
          lookahead != '{') ADVANCE(167);
      END_STATE();
    case 165:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '<') ADVANCE(54);
      if (lookahead == 'a') ADVANCE(93);
      if (lookahead == 'p') ADVANCE(80);
      if (lookahead == 's') ADVANCE(83);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          (lookahead < '`' || '{' < lookahead)) ADVANCE(167);
      END_STATE();
    case 166:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '<') ADVANCE(54);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(24)
      if ((1 <= lookahead && lookahead <= 8) ||
          (17 <= lookahead && lookahead <= 31) ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(166);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '`' &&
          lookahead != '{') ADVANCE(167);
      END_STATE();
    case 167:
      ACCEPT_TOKEN(sym__word);
      if (lookahead == '<') ADVANCE(54);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '`' &&
          lookahead != '{') ADVANCE(167);
      END_STATE();
    case 168:
      ACCEPT_TOKEN(sym__unquoted_atom);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('@' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          (192 <= lookahead && lookahead <= 255)) ADVANCE(168);
      END_STATE();
    case 169:
      ACCEPT_TOKEN(sym__escape_sequence);
      END_STATE();
    case 170:
      ACCEPT_TOKEN(sym__escape_sequence);
      if (lookahead == '{') ADVANCE(58);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(57);
      END_STATE();
    case 171:
      ACCEPT_TOKEN(sym__escape_sequence);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(169);
      END_STATE();
    case 172:
      ACCEPT_TOKEN(sym__escape_sequence);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(171);
      END_STATE();
    case 173:
      ACCEPT_TOKEN(sym__escape_sequence);
      if (('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 174:
      ACCEPT_TOKEN(sym__quoted_content);
      END_STATE();
    case 175:
      ACCEPT_TOKEN(sym__quoted_content);
      if (lookahead == '"') ADVANCE(174);
      if (lookahead == '\'') ADVANCE(124);
      if (lookahead == '\\') ADVANCE(176);
      if ((1 <= lookahead && lookahead <= '\t') ||
          (17 <= lookahead && lookahead <= ' ') ||
          (128 <= lookahead && lookahead <= 160)) ADVANCE(175);
      if (lookahead != 0) ADVANCE(177);
      END_STATE();
    case 176:
      ACCEPT_TOKEN(sym__quoted_content);
      if (lookahead == '^') ADVANCE(173);
      if (lookahead == 'x') ADVANCE(170);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(172);
      if ((' ' <= lookahead && lookahead <= 127)) ADVANCE(169);
      END_STATE();
    case 177:
      ACCEPT_TOKEN(sym__quoted_content);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(177);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 61},
  [2] = {.lex_state = 61},
  [3] = {.lex_state = 62},
  [4] = {.lex_state = 62},
  [5] = {.lex_state = 62},
  [6] = {.lex_state = 20},
  [7] = {.lex_state = 22},
  [8] = {.lex_state = 21},
  [9] = {.lex_state = 3},
  [10] = {.lex_state = 3},
  [11] = {.lex_state = 3},
  [12] = {.lex_state = 21},
  [13] = {.lex_state = 3},
  [14] = {.lex_state = 22},
  [15] = {.lex_state = 20},
  [16] = {.lex_state = 3},
  [17] = {.lex_state = 3},
  [18] = {.lex_state = 23},
  [19] = {.lex_state = 61},
  [20] = {.lex_state = 23},
  [21] = {.lex_state = 61},
  [22] = {.lex_state = 23},
  [23] = {.lex_state = 4},
  [24] = {.lex_state = 7},
  [25] = {.lex_state = 5},
  [26] = {.lex_state = 5},
  [27] = {.lex_state = 4},
  [28] = {.lex_state = 5},
  [29] = {.lex_state = 5},
  [30] = {.lex_state = 5},
  [31] = {.lex_state = 5},
  [32] = {.lex_state = 7},
  [33] = {.lex_state = 5},
  [34] = {.lex_state = 5},
  [35] = {.lex_state = 21},
  [36] = {.lex_state = 22},
  [37] = {.lex_state = 20},
  [38] = {.lex_state = 3},
  [39] = {.lex_state = 20},
  [40] = {.lex_state = 22},
  [41] = {.lex_state = 20},
  [42] = {.lex_state = 3},
  [43] = {.lex_state = 3},
  [44] = {.lex_state = 20},
  [45] = {.lex_state = 20},
  [46] = {.lex_state = 20},
  [47] = {.lex_state = 20},
  [48] = {.lex_state = 22},
  [49] = {.lex_state = 20},
  [50] = {.lex_state = 20},
  [51] = {.lex_state = 20},
  [52] = {.lex_state = 22},
  [53] = {.lex_state = 22},
  [54] = {.lex_state = 22},
  [55] = {.lex_state = 3},
  [56] = {.lex_state = 22},
  [57] = {.lex_state = 3},
  [58] = {.lex_state = 22},
  [59] = {.lex_state = 3},
  [60] = {.lex_state = 22},
  [61] = {.lex_state = 22},
  [62] = {.lex_state = 22},
  [63] = {.lex_state = 21},
  [64] = {.lex_state = 22},
  [65] = {.lex_state = 22},
  [66] = {.lex_state = 22},
  [67] = {.lex_state = 22},
  [68] = {.lex_state = 22},
  [69] = {.lex_state = 21},
  [70] = {.lex_state = 22},
  [71] = {.lex_state = 22},
  [72] = {.lex_state = 21},
  [73] = {.lex_state = 3},
  [74] = {.lex_state = 3},
  [75] = {.lex_state = 3},
  [76] = {.lex_state = 3},
  [77] = {.lex_state = 21},
  [78] = {.lex_state = 3},
  [79] = {.lex_state = 3},
  [80] = {.lex_state = 21},
  [81] = {.lex_state = 21},
  [82] = {.lex_state = 3},
  [83] = {.lex_state = 3},
  [84] = {.lex_state = 21},
  [85] = {.lex_state = 21},
  [86] = {.lex_state = 21},
  [87] = {.lex_state = 21},
  [88] = {.lex_state = 21},
  [89] = {.lex_state = 20},
  [90] = {.lex_state = 20},
  [91] = {.lex_state = 20},
  [92] = {.lex_state = 3},
  [93] = {.lex_state = 21},
  [94] = {.lex_state = 21},
  [95] = {.lex_state = 3},
  [96] = {.lex_state = 21},
  [97] = {.lex_state = 3},
  [98] = {.lex_state = 20},
  [99] = {.lex_state = 20},
  [100] = {.lex_state = 3},
  [101] = {.lex_state = 20},
  [102] = {.lex_state = 3},
  [103] = {.lex_state = 20},
  [104] = {.lex_state = 21},
  [105] = {.lex_state = 21},
  [106] = {.lex_state = 21},
  [107] = {.lex_state = 20},
  [108] = {.lex_state = 4},
  [109] = {.lex_state = 4},
  [110] = {.lex_state = 4},
  [111] = {.lex_state = 0},
  [112] = {.lex_state = 0},
  [113] = {.lex_state = 0},
  [114] = {.lex_state = 0},
  [115] = {.lex_state = 7},
  [116] = {.lex_state = 7},
  [117] = {.lex_state = 0},
  [118] = {.lex_state = 4},
  [119] = {.lex_state = 4},
  [120] = {.lex_state = 4},
  [121] = {.lex_state = 7},
  [122] = {.lex_state = 7},
  [123] = {.lex_state = 4},
  [124] = {.lex_state = 7},
  [125] = {.lex_state = 4},
  [126] = {.lex_state = 7},
  [127] = {.lex_state = 7},
  [128] = {.lex_state = 7},
  [129] = {.lex_state = 32},
  [130] = {.lex_state = 32},
  [131] = {.lex_state = 32},
  [132] = {.lex_state = 11},
  [133] = {.lex_state = 32},
  [134] = {.lex_state = 32},
  [135] = {.lex_state = 32},
  [136] = {.lex_state = 11},
  [137] = {.lex_state = 11},
  [138] = {.lex_state = 11},
  [139] = {.lex_state = 32},
  [140] = {.lex_state = 32},
  [141] = {.lex_state = 32},
  [142] = {.lex_state = 32},
  [143] = {.lex_state = 0},
  [144] = {.lex_state = 0},
  [145] = {.lex_state = 0},
  [146] = {.lex_state = 0},
  [147] = {.lex_state = 6},
  [148] = {.lex_state = 32},
  [149] = {.lex_state = 6},
  [150] = {.lex_state = 6},
  [151] = {.lex_state = 10},
  [152] = {.lex_state = 17},
  [153] = {.lex_state = 0},
  [154] = {.lex_state = 17},
  [155] = {.lex_state = 10},
  [156] = {.lex_state = 17},
  [157] = {.lex_state = 17},
  [158] = {.lex_state = 10},
  [159] = {.lex_state = 15},
  [160] = {.lex_state = 26},
  [161] = {.lex_state = 26},
  [162] = {.lex_state = 60},
  [163] = {.lex_state = 15},
  [164] = {.lex_state = 0},
  [165] = {.lex_state = 60},
  [166] = {.lex_state = 12},
  [167] = {.lex_state = 60},
  [168] = {.lex_state = 26},
  [169] = {.lex_state = 0},
  [170] = {.lex_state = 15},
  [171] = {.lex_state = 26},
  [172] = {.lex_state = 12},
  [173] = {.lex_state = 16},
  [174] = {.lex_state = 12},
  [175] = {.lex_state = 15},
  [176] = {.lex_state = 15},
  [177] = {.lex_state = 26},
  [178] = {.lex_state = 26},
  [179] = {.lex_state = 15},
  [180] = {.lex_state = 26},
  [181] = {.lex_state = 12},
  [182] = {.lex_state = 15},
  [183] = {.lex_state = 26},
  [184] = {.lex_state = 15},
  [185] = {.lex_state = 16},
  [186] = {.lex_state = 26},
  [187] = {.lex_state = 12},
  [188] = {.lex_state = 15},
  [189] = {.lex_state = 26},
  [190] = {.lex_state = 26},
  [191] = {.lex_state = 12},
  [192] = {.lex_state = 15},
  [193] = {.lex_state = 15},
  [194] = {.lex_state = 12},
  [195] = {.lex_state = 26},
  [196] = {.lex_state = 60},
  [197] = {.lex_state = 15},
  [198] = {.lex_state = 26},
  [199] = {.lex_state = 26},
  [200] = {.lex_state = 12},
  [201] = {.lex_state = 12},
  [202] = {.lex_state = 15},
  [203] = {.lex_state = 26},
  [204] = {.lex_state = 55},
  [205] = {.lex_state = 55},
  [206] = {.lex_state = 0},
  [207] = {.lex_state = 55},
  [208] = {.lex_state = 55},
  [209] = {.lex_state = 0},
  [210] = {.lex_state = 0},
  [211] = {.lex_state = 0},
  [212] = {.lex_state = 0},
  [213] = {.lex_state = 55},
  [214] = {.lex_state = 0},
  [215] = {.lex_state = 0},
  [216] = {.lex_state = 0},
  [217] = {.lex_state = 0},
  [218] = {.lex_state = 0},
  [219] = {.lex_state = 0},
  [220] = {.lex_state = 17},
  [221] = {.lex_state = 0},
  [222] = {.lex_state = 0},
  [223] = {.lex_state = 0},
  [224] = {.lex_state = 17},
  [225] = {.lex_state = 17},
  [226] = {.lex_state = 0},
  [227] = {.lex_state = 17},
  [228] = {.lex_state = 0},
  [229] = {.lex_state = 0},
  [230] = {.lex_state = 0},
  [231] = {.lex_state = 0},
  [232] = {.lex_state = 0},
  [233] = {.lex_state = 0},
  [234] = {.lex_state = 0},
  [235] = {.lex_state = 0},
  [236] = {.lex_state = 0},
  [237] = {.lex_state = 0},
  [238] = {.lex_state = 0},
  [239] = {.lex_state = 17},
  [240] = {.lex_state = 0},
  [241] = {.lex_state = 65},
  [242] = {.lex_state = 0},
  [243] = {.lex_state = 17},
  [244] = {.lex_state = 0},
  [245] = {.lex_state = 0},
  [246] = {.lex_state = 59},
  [247] = {.lex_state = 0},
  [248] = {.lex_state = 0},
  [249] = {.lex_state = 0},
  [250] = {.lex_state = 0},
  [251] = {.lex_state = 17},
  [252] = {.lex_state = 0},
  [253] = {.lex_state = 0},
  [254] = {.lex_state = 59},
  [255] = {.lex_state = 0},
  [256] = {.lex_state = 0},
  [257] = {.lex_state = 0},
  [258] = {.lex_state = 0},
  [259] = {.lex_state = 17},
  [260] = {.lex_state = 0},
  [261] = {.lex_state = 0},
  [262] = {.lex_state = 59},
  [263] = {.lex_state = 59},
  [264] = {.lex_state = 0},
  [265] = {.lex_state = 0},
  [266] = {.lex_state = 24},
  [267] = {.lex_state = 59},
  [268] = {.lex_state = 59},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_EQ_EQ_EQ_EQ_EQ] = ACTIONS(1),
    [anon_sym_ATauthor] = ACTIONS(1),
    [anon_sym_ATsee] = ACTIONS(1),
    [anon_sym_ATparam] = ACTIONS(1),
    [anon_sym_EQ_EQ] = ACTIONS(1),
    [anon_sym_EQ_EQ_EQ] = ACTIONS(1),
    [anon_sym_EQ_EQ_EQ_EQ] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_TODO_COLON] = ACTIONS(1),
    [aux_sym_tag_token1] = ACTIONS(1),
    [anon_sym_ATlink] = ACTIONS(1),
    [anon_sym_DOT] = ACTIONS(1),
    [anon_sym_SLASH] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [sym_arity] = ACTIONS(1),
    [anon_sym_LTem_GT] = ACTIONS(1),
    [anon_sym_LT_SLASHem_GT] = ACTIONS(1),
    [anon_sym_LTstrong_GT] = ACTIONS(1),
    [anon_sym_LT_SLASHstrong_GT] = ACTIONS(1),
    [anon_sym_LT] = ACTIONS(1),
    [anon_sym_GT] = ACTIONS(1),
    [anon_sym_AT_LBRACE] = ACTIONS(1),
    [anon_sym_AT_RBRACE] = ACTIONS(1),
    [anon_sym_AT_AT] = ACTIONS(1),
    [sym_quote_escape] = ACTIONS(1),
    [anon_sym_BQUOTE] = ACTIONS(1),
    [anon_sym_SQUOTE] = ACTIONS(1),
    [anon_sym_BQUOTE_BQUOTE] = ACTIONS(1),
    [anon_sym_BQUOTE_BQUOTE_BQUOTE] = ACTIONS(1),
    [sym__terminator] = ACTIONS(1),
    [sym__unquoted_atom] = ACTIONS(1),
    [sym__escape_sequence] = ACTIONS(1),
  },
  [1] = {
    [sym_source] = STATE(260),
    [sym__line] = STATE(206),
    [sym__separator] = STATE(206),
    [sym__tag_line] = STATE(206),
    [sym__author_line] = STATE(206),
    [sym__see_line] = STATE(206),
    [sym__param_line] = STATE(206),
    [aux_sym__text_line] = STATE(17),
    [sym_section] = STATE(206),
    [sym_macro] = STATE(38),
    [sym_tag] = STATE(16),
    [sym__link_macro] = STATE(42),
    [sym__xhtml_tag] = STATE(38),
    [sym_em_xhtml_tag] = STATE(38),
    [sym_strong_xhtml_tag] = STATE(38),
    [sym_xhtml_tag] = STATE(38),
    [sym_inline_quote] = STATE(38),
    [sym__inline_quote] = STATE(43),
    [sym__double_inline_quote] = STATE(43),
    [sym__triple_inline_quote] = STATE(43),
    [sym_block_quote] = STATE(38),
    [aux_sym_source_repeat1] = STATE(2),
    [aux_sym_source_repeat2] = STATE(4),
    [ts_builtin_sym_end] = ACTIONS(3),
    [anon_sym_EQ_EQ_EQ_EQ_EQ] = ACTIONS(5),
    [anon_sym_ATauthor] = ACTIONS(7),
    [anon_sym_ATsee] = ACTIONS(9),
    [anon_sym_ATparam] = ACTIONS(11),
    [anon_sym_EQ_EQ] = ACTIONS(13),
    [anon_sym_EQ_EQ_EQ] = ACTIONS(15),
    [anon_sym_EQ_EQ_EQ_EQ] = ACTIONS(17),
    [anon_sym_LBRACE] = ACTIONS(19),
    [anon_sym_TODO_COLON] = ACTIONS(21),
    [aux_sym_tag_token1] = ACTIONS(21),
    [anon_sym_LTem_GT] = ACTIONS(23),
    [anon_sym_LTstrong_GT] = ACTIONS(25),
    [anon_sym_LT] = ACTIONS(27),
    [sym_quote_escape] = ACTIONS(29),
    [anon_sym_BQUOTE] = ACTIONS(31),
    [anon_sym_BQUOTE_BQUOTE] = ACTIONS(33),
    [anon_sym_BQUOTE_BQUOTE_BQUOTE] = ACTIONS(35),
    [sym__terminator] = ACTIONS(37),
    [sym__word] = ACTIONS(29),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 26,
    ACTIONS(5), 1,
      anon_sym_EQ_EQ_EQ_EQ_EQ,
    ACTIONS(7), 1,
      anon_sym_ATauthor,
    ACTIONS(9), 1,
      anon_sym_ATsee,
    ACTIONS(11), 1,
      anon_sym_ATparam,
    ACTIONS(13), 1,
      anon_sym_EQ_EQ,
    ACTIONS(15), 1,
      anon_sym_EQ_EQ_EQ,
    ACTIONS(17), 1,
      anon_sym_EQ_EQ_EQ_EQ,
    ACTIONS(19), 1,
      anon_sym_LBRACE,
    ACTIONS(23), 1,
      anon_sym_LTem_GT,
    ACTIONS(25), 1,
      anon_sym_LTstrong_GT,
    ACTIONS(27), 1,
      anon_sym_LT,
    ACTIONS(31), 1,
      anon_sym_BQUOTE,
    ACTIONS(33), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(35), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    ACTIONS(39), 1,
      ts_builtin_sym_end,
    ACTIONS(41), 1,
      sym__terminator,
    STATE(3), 1,
      aux_sym_source_repeat2,
    STATE(16), 1,
      sym_tag,
    STATE(17), 1,
      aux_sym__text_line,
    STATE(21), 1,
      aux_sym_source_repeat1,
    STATE(42), 1,
      sym__link_macro,
    ACTIONS(21), 2,
      anon_sym_TODO_COLON,
      aux_sym_tag_token1,
    ACTIONS(29), 2,
      sym_quote_escape,
      sym__word,
    STATE(43), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
    STATE(38), 7,
      sym_macro,
      sym__xhtml_tag,
      sym_em_xhtml_tag,
      sym_strong_xhtml_tag,
      sym_xhtml_tag,
      sym_inline_quote,
      sym_block_quote,
    STATE(206), 7,
      sym__line,
      sym__separator,
      sym__tag_line,
      sym__author_line,
      sym__see_line,
      sym__param_line,
      sym_section,
  [95] = 24,
    ACTIONS(5), 1,
      anon_sym_EQ_EQ_EQ_EQ_EQ,
    ACTIONS(7), 1,
      anon_sym_ATauthor,
    ACTIONS(9), 1,
      anon_sym_ATsee,
    ACTIONS(11), 1,
      anon_sym_ATparam,
    ACTIONS(13), 1,
      anon_sym_EQ_EQ,
    ACTIONS(15), 1,
      anon_sym_EQ_EQ_EQ,
    ACTIONS(17), 1,
      anon_sym_EQ_EQ_EQ_EQ,
    ACTIONS(19), 1,
      anon_sym_LBRACE,
    ACTIONS(23), 1,
      anon_sym_LTem_GT,
    ACTIONS(25), 1,
      anon_sym_LTstrong_GT,
    ACTIONS(27), 1,
      anon_sym_LT,
    ACTIONS(31), 1,
      anon_sym_BQUOTE,
    ACTIONS(33), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(35), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    ACTIONS(43), 1,
      ts_builtin_sym_end,
    STATE(5), 1,
      aux_sym_source_repeat2,
    STATE(16), 1,
      sym_tag,
    STATE(17), 1,
      aux_sym__text_line,
    STATE(42), 1,
      sym__link_macro,
    ACTIONS(21), 2,
      anon_sym_TODO_COLON,
      aux_sym_tag_token1,
    ACTIONS(29), 2,
      sym_quote_escape,
      sym__word,
    STATE(43), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
    STATE(38), 7,
      sym_macro,
      sym__xhtml_tag,
      sym_em_xhtml_tag,
      sym_strong_xhtml_tag,
      sym_xhtml_tag,
      sym_inline_quote,
      sym_block_quote,
    STATE(206), 7,
      sym__line,
      sym__separator,
      sym__tag_line,
      sym__author_line,
      sym__see_line,
      sym__param_line,
      sym_section,
  [184] = 24,
    ACTIONS(5), 1,
      anon_sym_EQ_EQ_EQ_EQ_EQ,
    ACTIONS(7), 1,
      anon_sym_ATauthor,
    ACTIONS(9), 1,
      anon_sym_ATsee,
    ACTIONS(11), 1,
      anon_sym_ATparam,
    ACTIONS(13), 1,
      anon_sym_EQ_EQ,
    ACTIONS(15), 1,
      anon_sym_EQ_EQ_EQ,
    ACTIONS(17), 1,
      anon_sym_EQ_EQ_EQ_EQ,
    ACTIONS(19), 1,
      anon_sym_LBRACE,
    ACTIONS(23), 1,
      anon_sym_LTem_GT,
    ACTIONS(25), 1,
      anon_sym_LTstrong_GT,
    ACTIONS(27), 1,
      anon_sym_LT,
    ACTIONS(31), 1,
      anon_sym_BQUOTE,
    ACTIONS(33), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(35), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    ACTIONS(39), 1,
      ts_builtin_sym_end,
    STATE(5), 1,
      aux_sym_source_repeat2,
    STATE(16), 1,
      sym_tag,
    STATE(17), 1,
      aux_sym__text_line,
    STATE(42), 1,
      sym__link_macro,
    ACTIONS(21), 2,
      anon_sym_TODO_COLON,
      aux_sym_tag_token1,
    ACTIONS(29), 2,
      sym_quote_escape,
      sym__word,
    STATE(43), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
    STATE(38), 7,
      sym_macro,
      sym__xhtml_tag,
      sym_em_xhtml_tag,
      sym_strong_xhtml_tag,
      sym_xhtml_tag,
      sym_inline_quote,
      sym_block_quote,
    STATE(206), 7,
      sym__line,
      sym__separator,
      sym__tag_line,
      sym__author_line,
      sym__see_line,
      sym__param_line,
      sym_section,
  [273] = 24,
    ACTIONS(45), 1,
      ts_builtin_sym_end,
    ACTIONS(47), 1,
      anon_sym_EQ_EQ_EQ_EQ_EQ,
    ACTIONS(50), 1,
      anon_sym_ATauthor,
    ACTIONS(53), 1,
      anon_sym_ATsee,
    ACTIONS(56), 1,
      anon_sym_ATparam,
    ACTIONS(59), 1,
      anon_sym_EQ_EQ,
    ACTIONS(62), 1,
      anon_sym_EQ_EQ_EQ,
    ACTIONS(65), 1,
      anon_sym_EQ_EQ_EQ_EQ,
    ACTIONS(68), 1,
      anon_sym_LBRACE,
    ACTIONS(74), 1,
      anon_sym_LTem_GT,
    ACTIONS(77), 1,
      anon_sym_LTstrong_GT,
    ACTIONS(80), 1,
      anon_sym_LT,
    ACTIONS(86), 1,
      anon_sym_BQUOTE,
    ACTIONS(89), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(92), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    STATE(5), 1,
      aux_sym_source_repeat2,
    STATE(16), 1,
      sym_tag,
    STATE(17), 1,
      aux_sym__text_line,
    STATE(42), 1,
      sym__link_macro,
    ACTIONS(71), 2,
      anon_sym_TODO_COLON,
      aux_sym_tag_token1,
    ACTIONS(83), 2,
      sym_quote_escape,
      sym__word,
    STATE(43), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
    STATE(38), 7,
      sym_macro,
      sym__xhtml_tag,
      sym_em_xhtml_tag,
      sym_strong_xhtml_tag,
      sym_xhtml_tag,
      sym_inline_quote,
      sym_block_quote,
    STATE(206), 7,
      sym__line,
      sym__separator,
      sym__tag_line,
      sym__author_line,
      sym__see_line,
      sym__param_line,
      sym_section,
  [362] = 13,
    ACTIONS(95), 1,
      anon_sym_EQ_EQ_EQ_EQ,
    ACTIONS(97), 1,
      anon_sym_LBRACE,
    ACTIONS(100), 1,
      anon_sym_LTem_GT,
    ACTIONS(103), 1,
      anon_sym_LTstrong_GT,
    ACTIONS(106), 1,
      anon_sym_LT,
    ACTIONS(112), 1,
      anon_sym_BQUOTE,
    ACTIONS(115), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(118), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    STATE(6), 1,
      aux_sym__text_line,
    STATE(50), 1,
      sym__link_macro,
    ACTIONS(109), 2,
      sym_quote_escape,
      sym__word,
    STATE(49), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
    STATE(51), 7,
      sym_macro,
      sym__xhtml_tag,
      sym_em_xhtml_tag,
      sym_strong_xhtml_tag,
      sym_xhtml_tag,
      sym_inline_quote,
      sym_block_quote,
  [411] = 13,
    ACTIONS(95), 1,
      anon_sym_EQ_EQ_EQ,
    ACTIONS(121), 1,
      anon_sym_LBRACE,
    ACTIONS(124), 1,
      anon_sym_LTem_GT,
    ACTIONS(127), 1,
      anon_sym_LTstrong_GT,
    ACTIONS(130), 1,
      anon_sym_LT,
    ACTIONS(136), 1,
      anon_sym_BQUOTE,
    ACTIONS(139), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(142), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    STATE(7), 1,
      aux_sym__text_line,
    STATE(71), 1,
      sym__link_macro,
    ACTIONS(133), 2,
      sym_quote_escape,
      sym__word,
    STATE(70), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
    STATE(36), 7,
      sym_macro,
      sym__xhtml_tag,
      sym_em_xhtml_tag,
      sym_strong_xhtml_tag,
      sym_xhtml_tag,
      sym_inline_quote,
      sym_block_quote,
  [460] = 13,
    ACTIONS(95), 1,
      anon_sym_EQ_EQ,
    ACTIONS(145), 1,
      anon_sym_LBRACE,
    ACTIONS(148), 1,
      anon_sym_LTem_GT,
    ACTIONS(151), 1,
      anon_sym_LTstrong_GT,
    ACTIONS(154), 1,
      anon_sym_LT,
    ACTIONS(160), 1,
      anon_sym_BQUOTE,
    ACTIONS(163), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(166), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    STATE(8), 1,
      aux_sym__text_line,
    STATE(105), 1,
      sym__link_macro,
    ACTIONS(157), 2,
      sym_quote_escape,
      sym__word,
    STATE(106), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
    STATE(104), 7,
      sym_macro,
      sym__xhtml_tag,
      sym_em_xhtml_tag,
      sym_strong_xhtml_tag,
      sym_xhtml_tag,
      sym_inline_quote,
      sym_block_quote,
  [509] = 13,
    ACTIONS(19), 1,
      anon_sym_LBRACE,
    ACTIONS(23), 1,
      anon_sym_LTem_GT,
    ACTIONS(25), 1,
      anon_sym_LTstrong_GT,
    ACTIONS(27), 1,
      anon_sym_LT,
    ACTIONS(31), 1,
      anon_sym_BQUOTE,
    ACTIONS(33), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(35), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    ACTIONS(169), 1,
      sym__terminator,
    STATE(10), 1,
      aux_sym__text_line,
    STATE(42), 1,
      sym__link_macro,
    ACTIONS(29), 2,
      sym_quote_escape,
      sym__word,
    STATE(43), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
    STATE(38), 7,
      sym_macro,
      sym__xhtml_tag,
      sym_em_xhtml_tag,
      sym_strong_xhtml_tag,
      sym_xhtml_tag,
      sym_inline_quote,
      sym_block_quote,
  [558] = 13,
    ACTIONS(95), 1,
      sym__terminator,
    ACTIONS(171), 1,
      anon_sym_LBRACE,
    ACTIONS(174), 1,
      anon_sym_LTem_GT,
    ACTIONS(177), 1,
      anon_sym_LTstrong_GT,
    ACTIONS(180), 1,
      anon_sym_LT,
    ACTIONS(186), 1,
      anon_sym_BQUOTE,
    ACTIONS(189), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(192), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    STATE(10), 1,
      aux_sym__text_line,
    STATE(42), 1,
      sym__link_macro,
    ACTIONS(183), 2,
      sym_quote_escape,
      sym__word,
    STATE(43), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
    STATE(38), 7,
      sym_macro,
      sym__xhtml_tag,
      sym_em_xhtml_tag,
      sym_strong_xhtml_tag,
      sym_xhtml_tag,
      sym_inline_quote,
      sym_block_quote,
  [607] = 13,
    ACTIONS(19), 1,
      anon_sym_LBRACE,
    ACTIONS(23), 1,
      anon_sym_LTem_GT,
    ACTIONS(25), 1,
      anon_sym_LTstrong_GT,
    ACTIONS(27), 1,
      anon_sym_LT,
    ACTIONS(31), 1,
      anon_sym_BQUOTE,
    ACTIONS(33), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(35), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    ACTIONS(195), 1,
      sym__terminator,
    STATE(13), 1,
      aux_sym__text_line,
    STATE(42), 1,
      sym__link_macro,
    ACTIONS(29), 2,
      sym_quote_escape,
      sym__word,
    STATE(43), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
    STATE(38), 7,
      sym_macro,
      sym__xhtml_tag,
      sym_em_xhtml_tag,
      sym_strong_xhtml_tag,
      sym_xhtml_tag,
      sym_inline_quote,
      sym_block_quote,
  [656] = 13,
    ACTIONS(197), 1,
      anon_sym_EQ_EQ,
    ACTIONS(199), 1,
      anon_sym_LBRACE,
    ACTIONS(201), 1,
      anon_sym_LTem_GT,
    ACTIONS(203), 1,
      anon_sym_LTstrong_GT,
    ACTIONS(205), 1,
      anon_sym_LT,
    ACTIONS(209), 1,
      anon_sym_BQUOTE,
    ACTIONS(211), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(213), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    STATE(8), 1,
      aux_sym__text_line,
    STATE(105), 1,
      sym__link_macro,
    ACTIONS(207), 2,
      sym_quote_escape,
      sym__word,
    STATE(106), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
    STATE(104), 7,
      sym_macro,
      sym__xhtml_tag,
      sym_em_xhtml_tag,
      sym_strong_xhtml_tag,
      sym_xhtml_tag,
      sym_inline_quote,
      sym_block_quote,
  [705] = 13,
    ACTIONS(19), 1,
      anon_sym_LBRACE,
    ACTIONS(23), 1,
      anon_sym_LTem_GT,
    ACTIONS(25), 1,
      anon_sym_LTstrong_GT,
    ACTIONS(27), 1,
      anon_sym_LT,
    ACTIONS(31), 1,
      anon_sym_BQUOTE,
    ACTIONS(33), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(35), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    ACTIONS(215), 1,
      sym__terminator,
    STATE(10), 1,
      aux_sym__text_line,
    STATE(42), 1,
      sym__link_macro,
    ACTIONS(29), 2,
      sym_quote_escape,
      sym__word,
    STATE(43), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
    STATE(38), 7,
      sym_macro,
      sym__xhtml_tag,
      sym_em_xhtml_tag,
      sym_strong_xhtml_tag,
      sym_xhtml_tag,
      sym_inline_quote,
      sym_block_quote,
  [754] = 13,
    ACTIONS(197), 1,
      anon_sym_EQ_EQ_EQ,
    ACTIONS(217), 1,
      anon_sym_LBRACE,
    ACTIONS(219), 1,
      anon_sym_LTem_GT,
    ACTIONS(221), 1,
      anon_sym_LTstrong_GT,
    ACTIONS(223), 1,
      anon_sym_LT,
    ACTIONS(227), 1,
      anon_sym_BQUOTE,
    ACTIONS(229), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(231), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    STATE(7), 1,
      aux_sym__text_line,
    STATE(71), 1,
      sym__link_macro,
    ACTIONS(225), 2,
      sym_quote_escape,
      sym__word,
    STATE(70), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
    STATE(36), 7,
      sym_macro,
      sym__xhtml_tag,
      sym_em_xhtml_tag,
      sym_strong_xhtml_tag,
      sym_xhtml_tag,
      sym_inline_quote,
      sym_block_quote,
  [803] = 13,
    ACTIONS(197), 1,
      anon_sym_EQ_EQ_EQ_EQ,
    ACTIONS(233), 1,
      anon_sym_LBRACE,
    ACTIONS(235), 1,
      anon_sym_LTem_GT,
    ACTIONS(237), 1,
      anon_sym_LTstrong_GT,
    ACTIONS(239), 1,
      anon_sym_LT,
    ACTIONS(243), 1,
      anon_sym_BQUOTE,
    ACTIONS(245), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(247), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    STATE(6), 1,
      aux_sym__text_line,
    STATE(50), 1,
      sym__link_macro,
    ACTIONS(241), 2,
      sym_quote_escape,
      sym__word,
    STATE(49), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
    STATE(51), 7,
      sym_macro,
      sym__xhtml_tag,
      sym_em_xhtml_tag,
      sym_strong_xhtml_tag,
      sym_xhtml_tag,
      sym_inline_quote,
      sym_block_quote,
  [852] = 13,
    ACTIONS(19), 1,
      anon_sym_LBRACE,
    ACTIONS(23), 1,
      anon_sym_LTem_GT,
    ACTIONS(25), 1,
      anon_sym_LTstrong_GT,
    ACTIONS(27), 1,
      anon_sym_LT,
    ACTIONS(31), 1,
      anon_sym_BQUOTE,
    ACTIONS(33), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(35), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    ACTIONS(249), 1,
      sym__terminator,
    STATE(9), 1,
      aux_sym__text_line,
    STATE(42), 1,
      sym__link_macro,
    ACTIONS(29), 2,
      sym_quote_escape,
      sym__word,
    STATE(43), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
    STATE(38), 7,
      sym_macro,
      sym__xhtml_tag,
      sym_em_xhtml_tag,
      sym_strong_xhtml_tag,
      sym_xhtml_tag,
      sym_inline_quote,
      sym_block_quote,
  [901] = 13,
    ACTIONS(19), 1,
      anon_sym_LBRACE,
    ACTIONS(23), 1,
      anon_sym_LTem_GT,
    ACTIONS(25), 1,
      anon_sym_LTstrong_GT,
    ACTIONS(27), 1,
      anon_sym_LT,
    ACTIONS(31), 1,
      anon_sym_BQUOTE,
    ACTIONS(33), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(35), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    ACTIONS(251), 1,
      sym__terminator,
    STATE(10), 1,
      aux_sym__text_line,
    STATE(42), 1,
      sym__link_macro,
    ACTIONS(29), 2,
      sym_quote_escape,
      sym__word,
    STATE(43), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
    STATE(38), 7,
      sym_macro,
      sym__xhtml_tag,
      sym_em_xhtml_tag,
      sym_strong_xhtml_tag,
      sym_xhtml_tag,
      sym_inline_quote,
      sym_block_quote,
  [950] = 12,
    ACTIONS(233), 1,
      anon_sym_LBRACE,
    ACTIONS(235), 1,
      anon_sym_LTem_GT,
    ACTIONS(237), 1,
      anon_sym_LTstrong_GT,
    ACTIONS(239), 1,
      anon_sym_LT,
    ACTIONS(243), 1,
      anon_sym_BQUOTE,
    ACTIONS(245), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(247), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    STATE(15), 1,
      aux_sym__text_line,
    STATE(50), 1,
      sym__link_macro,
    ACTIONS(241), 2,
      sym_quote_escape,
      sym__word,
    STATE(49), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
    STATE(51), 7,
      sym_macro,
      sym__xhtml_tag,
      sym_em_xhtml_tag,
      sym_strong_xhtml_tag,
      sym_xhtml_tag,
      sym_inline_quote,
      sym_block_quote,
  [996] = 4,
    ACTIONS(41), 1,
      sym__terminator,
    ACTIONS(45), 1,
      ts_builtin_sym_end,
    STATE(21), 1,
      aux_sym_source_repeat1,
    ACTIONS(253), 18,
      anon_sym_EQ_EQ_EQ_EQ_EQ,
      anon_sym_ATauthor,
      anon_sym_ATsee,
      anon_sym_ATparam,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_EQ_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_TODO_COLON,
      aux_sym_tag_token1,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1026] = 12,
    ACTIONS(217), 1,
      anon_sym_LBRACE,
    ACTIONS(219), 1,
      anon_sym_LTem_GT,
    ACTIONS(221), 1,
      anon_sym_LTstrong_GT,
    ACTIONS(223), 1,
      anon_sym_LT,
    ACTIONS(227), 1,
      anon_sym_BQUOTE,
    ACTIONS(229), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(231), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    STATE(14), 1,
      aux_sym__text_line,
    STATE(71), 1,
      sym__link_macro,
    ACTIONS(225), 2,
      sym_quote_escape,
      sym__word,
    STATE(70), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
    STATE(36), 7,
      sym_macro,
      sym__xhtml_tag,
      sym_em_xhtml_tag,
      sym_strong_xhtml_tag,
      sym_xhtml_tag,
      sym_inline_quote,
      sym_block_quote,
  [1072] = 4,
    ACTIONS(255), 1,
      ts_builtin_sym_end,
    ACTIONS(259), 1,
      sym__terminator,
    STATE(21), 1,
      aux_sym_source_repeat1,
    ACTIONS(257), 18,
      anon_sym_EQ_EQ_EQ_EQ_EQ,
      anon_sym_ATauthor,
      anon_sym_ATsee,
      anon_sym_ATparam,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_EQ_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_TODO_COLON,
      aux_sym_tag_token1,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1102] = 12,
    ACTIONS(199), 1,
      anon_sym_LBRACE,
    ACTIONS(201), 1,
      anon_sym_LTem_GT,
    ACTIONS(203), 1,
      anon_sym_LTstrong_GT,
    ACTIONS(205), 1,
      anon_sym_LT,
    ACTIONS(209), 1,
      anon_sym_BQUOTE,
    ACTIONS(211), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(213), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    STATE(12), 1,
      aux_sym__text_line,
    STATE(105), 1,
      sym__link_macro,
    ACTIONS(207), 2,
      sym_quote_escape,
      sym__word,
    STATE(106), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
    STATE(104), 7,
      sym_macro,
      sym__xhtml_tag,
      sym_em_xhtml_tag,
      sym_strong_xhtml_tag,
      sym_xhtml_tag,
      sym_inline_quote,
      sym_block_quote,
  [1148] = 8,
    ACTIONS(262), 1,
      anon_sym_LT_SLASHem_GT,
    ACTIONS(264), 1,
      anon_sym_LT,
    ACTIONS(270), 1,
      anon_sym_BQUOTE,
    ACTIONS(273), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(276), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    ACTIONS(267), 3,
      sym_quote_escape,
      sym__terminator,
      sym__word,
    STATE(23), 3,
      sym_xhtml_tag,
      sym_inline_quote,
      aux_sym_xhtml_tag_content_repeat1,
    STATE(110), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
  [1179] = 8,
    ACTIONS(262), 1,
      anon_sym_LT_SLASHstrong_GT,
    ACTIONS(279), 1,
      anon_sym_LT,
    ACTIONS(285), 1,
      anon_sym_BQUOTE,
    ACTIONS(288), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(291), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    ACTIONS(282), 3,
      sym_quote_escape,
      sym__terminator,
      sym__word,
    STATE(24), 3,
      sym_xhtml_tag,
      sym_inline_quote,
      aux_sym_xhtml_tag_content_repeat1,
    STATE(124), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
  [1210] = 8,
    ACTIONS(294), 1,
      anon_sym_LT,
    ACTIONS(298), 1,
      anon_sym_BQUOTE,
    ACTIONS(300), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(302), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    STATE(221), 1,
      sym_xhtml_tag_content,
    ACTIONS(296), 3,
      sym_quote_escape,
      sym__terminator,
      sym__word,
    STATE(27), 3,
      sym_xhtml_tag,
      sym_inline_quote,
      aux_sym_xhtml_tag_content_repeat1,
    STATE(110), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
  [1241] = 8,
    ACTIONS(304), 1,
      anon_sym_LT,
    ACTIONS(308), 1,
      anon_sym_BQUOTE,
    ACTIONS(310), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(312), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    STATE(222), 1,
      sym_xhtml_tag_content,
    ACTIONS(306), 3,
      sym_quote_escape,
      sym__terminator,
      sym__word,
    STATE(32), 3,
      sym_xhtml_tag,
      sym_inline_quote,
      aux_sym_xhtml_tag_content_repeat1,
    STATE(124), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
  [1272] = 8,
    ACTIONS(294), 1,
      anon_sym_LT,
    ACTIONS(298), 1,
      anon_sym_BQUOTE,
    ACTIONS(300), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(302), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    ACTIONS(314), 1,
      anon_sym_LT_SLASHem_GT,
    ACTIONS(316), 3,
      sym_quote_escape,
      sym__terminator,
      sym__word,
    STATE(23), 3,
      sym_xhtml_tag,
      sym_inline_quote,
      aux_sym_xhtml_tag_content_repeat1,
    STATE(110), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
  [1303] = 8,
    ACTIONS(304), 1,
      anon_sym_LT,
    ACTIONS(308), 1,
      anon_sym_BQUOTE,
    ACTIONS(310), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(312), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    STATE(247), 1,
      sym_xhtml_tag_content,
    ACTIONS(306), 3,
      sym_quote_escape,
      sym__terminator,
      sym__word,
    STATE(32), 3,
      sym_xhtml_tag,
      sym_inline_quote,
      aux_sym_xhtml_tag_content_repeat1,
    STATE(124), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
  [1334] = 8,
    ACTIONS(294), 1,
      anon_sym_LT,
    ACTIONS(298), 1,
      anon_sym_BQUOTE,
    ACTIONS(300), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(302), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    STATE(249), 1,
      sym_xhtml_tag_content,
    ACTIONS(296), 3,
      sym_quote_escape,
      sym__terminator,
      sym__word,
    STATE(27), 3,
      sym_xhtml_tag,
      sym_inline_quote,
      aux_sym_xhtml_tag_content_repeat1,
    STATE(110), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
  [1365] = 8,
    ACTIONS(304), 1,
      anon_sym_LT,
    ACTIONS(308), 1,
      anon_sym_BQUOTE,
    ACTIONS(310), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(312), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    STATE(230), 1,
      sym_xhtml_tag_content,
    ACTIONS(306), 3,
      sym_quote_escape,
      sym__terminator,
      sym__word,
    STATE(32), 3,
      sym_xhtml_tag,
      sym_inline_quote,
      aux_sym_xhtml_tag_content_repeat1,
    STATE(124), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
  [1396] = 8,
    ACTIONS(294), 1,
      anon_sym_LT,
    ACTIONS(298), 1,
      anon_sym_BQUOTE,
    ACTIONS(300), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(302), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    STATE(231), 1,
      sym_xhtml_tag_content,
    ACTIONS(296), 3,
      sym_quote_escape,
      sym__terminator,
      sym__word,
    STATE(27), 3,
      sym_xhtml_tag,
      sym_inline_quote,
      aux_sym_xhtml_tag_content_repeat1,
    STATE(110), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
  [1427] = 8,
    ACTIONS(304), 1,
      anon_sym_LT,
    ACTIONS(308), 1,
      anon_sym_BQUOTE,
    ACTIONS(310), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(312), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    ACTIONS(314), 1,
      anon_sym_LT_SLASHstrong_GT,
    ACTIONS(318), 3,
      sym_quote_escape,
      sym__terminator,
      sym__word,
    STATE(24), 3,
      sym_xhtml_tag,
      sym_inline_quote,
      aux_sym_xhtml_tag_content_repeat1,
    STATE(124), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
  [1458] = 8,
    ACTIONS(304), 1,
      anon_sym_LT,
    ACTIONS(308), 1,
      anon_sym_BQUOTE,
    ACTIONS(310), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(312), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    STATE(235), 1,
      sym_xhtml_tag_content,
    ACTIONS(306), 3,
      sym_quote_escape,
      sym__terminator,
      sym__word,
    STATE(32), 3,
      sym_xhtml_tag,
      sym_inline_quote,
      aux_sym_xhtml_tag_content_repeat1,
    STATE(124), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
  [1489] = 8,
    ACTIONS(294), 1,
      anon_sym_LT,
    ACTIONS(298), 1,
      anon_sym_BQUOTE,
    ACTIONS(300), 1,
      anon_sym_BQUOTE_BQUOTE,
    ACTIONS(302), 1,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
    STATE(237), 1,
      sym_xhtml_tag_content,
    ACTIONS(296), 3,
      sym_quote_escape,
      sym__terminator,
      sym__word,
    STATE(27), 3,
      sym_xhtml_tag,
      sym_inline_quote,
      aux_sym_xhtml_tag_content_repeat1,
    STATE(110), 3,
      sym__inline_quote,
      sym__double_inline_quote,
      sym__triple_inline_quote,
  [1520] = 1,
    ACTIONS(320), 10,
      anon_sym_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1533] = 1,
    ACTIONS(322), 10,
      anon_sym_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1546] = 1,
    ACTIONS(324), 10,
      anon_sym_EQ_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1559] = 1,
    ACTIONS(322), 10,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [1572] = 1,
    ACTIONS(326), 10,
      anon_sym_EQ_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1585] = 1,
    ACTIONS(328), 10,
      anon_sym_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1598] = 1,
    ACTIONS(320), 10,
      anon_sym_EQ_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1611] = 1,
    ACTIONS(330), 10,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [1624] = 1,
    ACTIONS(332), 10,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [1637] = 1,
    ACTIONS(334), 10,
      anon_sym_EQ_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1650] = 1,
    ACTIONS(336), 10,
      anon_sym_EQ_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1663] = 1,
    ACTIONS(338), 10,
      anon_sym_EQ_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1676] = 1,
    ACTIONS(340), 10,
      anon_sym_EQ_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1689] = 1,
    ACTIONS(342), 10,
      anon_sym_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1702] = 1,
    ACTIONS(332), 10,
      anon_sym_EQ_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1715] = 1,
    ACTIONS(330), 10,
      anon_sym_EQ_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1728] = 1,
    ACTIONS(322), 10,
      anon_sym_EQ_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1741] = 1,
    ACTIONS(344), 10,
      anon_sym_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1754] = 1,
    ACTIONS(346), 10,
      anon_sym_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1767] = 1,
    ACTIONS(348), 10,
      anon_sym_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1780] = 1,
    ACTIONS(342), 10,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [1793] = 1,
    ACTIONS(350), 10,
      anon_sym_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1806] = 1,
    ACTIONS(340), 10,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [1819] = 1,
    ACTIONS(352), 10,
      anon_sym_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1832] = 1,
    ACTIONS(338), 10,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [1845] = 1,
    ACTIONS(354), 10,
      anon_sym_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1858] = 1,
    ACTIONS(324), 10,
      anon_sym_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1871] = 1,
    ACTIONS(326), 10,
      anon_sym_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1884] = 1,
    ACTIONS(328), 10,
      anon_sym_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1897] = 1,
    ACTIONS(320), 10,
      anon_sym_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1910] = 1,
    ACTIONS(334), 10,
      anon_sym_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1923] = 1,
    ACTIONS(336), 10,
      anon_sym_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1936] = 1,
    ACTIONS(338), 10,
      anon_sym_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1949] = 1,
    ACTIONS(340), 10,
      anon_sym_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1962] = 1,
    ACTIONS(342), 10,
      anon_sym_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1975] = 1,
    ACTIONS(332), 10,
      anon_sym_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [1988] = 1,
    ACTIONS(330), 10,
      anon_sym_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2001] = 1,
    ACTIONS(340), 10,
      anon_sym_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2014] = 1,
    ACTIONS(336), 10,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2027] = 1,
    ACTIONS(334), 10,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2040] = 1,
    ACTIONS(320), 10,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2053] = 1,
    ACTIONS(328), 10,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2066] = 1,
    ACTIONS(344), 10,
      anon_sym_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2079] = 1,
    ACTIONS(326), 10,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2092] = 1,
    ACTIONS(324), 10,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2105] = 1,
    ACTIONS(346), 10,
      anon_sym_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2118] = 1,
    ACTIONS(348), 10,
      anon_sym_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2131] = 1,
    ACTIONS(354), 10,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2144] = 1,
    ACTIONS(352), 10,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2157] = 1,
    ACTIONS(350), 10,
      anon_sym_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2170] = 1,
    ACTIONS(352), 10,
      anon_sym_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2183] = 1,
    ACTIONS(354), 10,
      anon_sym_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2196] = 1,
    ACTIONS(324), 10,
      anon_sym_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2209] = 1,
    ACTIONS(326), 10,
      anon_sym_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2222] = 1,
    ACTIONS(352), 10,
      anon_sym_EQ_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2235] = 1,
    ACTIONS(328), 10,
      anon_sym_EQ_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2248] = 1,
    ACTIONS(354), 10,
      anon_sym_EQ_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2261] = 1,
    ACTIONS(350), 10,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2274] = 1,
    ACTIONS(334), 10,
      anon_sym_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2287] = 1,
    ACTIONS(336), 10,
      anon_sym_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2300] = 1,
    ACTIONS(356), 10,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2313] = 1,
    ACTIONS(338), 10,
      anon_sym_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2326] = 1,
    ACTIONS(348), 10,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2339] = 1,
    ACTIONS(342), 10,
      anon_sym_EQ_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2352] = 1,
    ACTIONS(344), 10,
      anon_sym_EQ_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2365] = 1,
    ACTIONS(346), 10,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2378] = 1,
    ACTIONS(346), 10,
      anon_sym_EQ_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2391] = 1,
    ACTIONS(344), 10,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2404] = 1,
    ACTIONS(348), 10,
      anon_sym_EQ_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2417] = 1,
    ACTIONS(322), 10,
      anon_sym_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2430] = 1,
    ACTIONS(330), 10,
      anon_sym_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2443] = 1,
    ACTIONS(332), 10,
      anon_sym_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2456] = 1,
    ACTIONS(350), 10,
      anon_sym_EQ_EQ_EQ_EQ,
      anon_sym_LBRACE,
      anon_sym_LTem_GT,
      anon_sym_LTstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__word,
  [2469] = 1,
    ACTIONS(340), 8,
      anon_sym_LT_SLASHem_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2480] = 1,
    ACTIONS(328), 8,
      anon_sym_LT_SLASHem_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2491] = 1,
    ACTIONS(332), 8,
      anon_sym_LT_SLASHem_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2502] = 7,
    ACTIONS(358), 1,
      anon_sym_SQUOTE,
    ACTIONS(360), 1,
      sym__unquoted_atom,
    STATE(153), 1,
      sym_module,
    STATE(210), 1,
      sym_expression,
    STATE(252), 1,
      sym_type,
    STATE(253), 1,
      sym_function,
    STATE(146), 2,
      sym__atom,
      sym__quoted_atom,
  [2525] = 7,
    ACTIONS(358), 1,
      anon_sym_SQUOTE,
    ACTIONS(360), 1,
      sym__unquoted_atom,
    STATE(153), 1,
      sym_module,
    STATE(214), 1,
      sym_expression,
    STATE(252), 1,
      sym_type,
    STATE(253), 1,
      sym_function,
    STATE(146), 2,
      sym__atom,
      sym__quoted_atom,
  [2548] = 7,
    ACTIONS(358), 1,
      anon_sym_SQUOTE,
    ACTIONS(360), 1,
      sym__unquoted_atom,
    STATE(153), 1,
      sym_module,
    STATE(211), 1,
      sym_expression,
    STATE(252), 1,
      sym_type,
    STATE(253), 1,
      sym_function,
    STATE(146), 2,
      sym__atom,
      sym__quoted_atom,
  [2571] = 7,
    ACTIONS(358), 1,
      anon_sym_SQUOTE,
    ACTIONS(360), 1,
      sym__unquoted_atom,
    STATE(153), 1,
      sym_module,
    STATE(212), 1,
      sym_expression,
    STATE(252), 1,
      sym_type,
    STATE(253), 1,
      sym_function,
    STATE(146), 2,
      sym__atom,
      sym__quoted_atom,
  [2594] = 1,
    ACTIONS(328), 8,
      anon_sym_LT_SLASHstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2605] = 1,
    ACTIONS(342), 8,
      anon_sym_LT_SLASHstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2616] = 7,
    ACTIONS(358), 1,
      anon_sym_SQUOTE,
    ACTIONS(360), 1,
      sym__unquoted_atom,
    STATE(153), 1,
      sym_module,
    STATE(252), 1,
      sym_type,
    STATE(253), 1,
      sym_function,
    STATE(255), 1,
      sym_expression,
    STATE(146), 2,
      sym__atom,
      sym__quoted_atom,
  [2639] = 1,
    ACTIONS(338), 8,
      anon_sym_LT_SLASHem_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2650] = 1,
    ACTIONS(326), 8,
      anon_sym_LT_SLASHem_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2661] = 1,
    ACTIONS(324), 8,
      anon_sym_LT_SLASHem_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2672] = 1,
    ACTIONS(326), 8,
      anon_sym_LT_SLASHstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2683] = 1,
    ACTIONS(324), 8,
      anon_sym_LT_SLASHstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2694] = 1,
    ACTIONS(352), 8,
      anon_sym_LT_SLASHem_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2705] = 1,
    ACTIONS(332), 8,
      anon_sym_LT_SLASHstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2716] = 1,
    ACTIONS(342), 8,
      anon_sym_LT_SLASHem_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2727] = 1,
    ACTIONS(340), 8,
      anon_sym_LT_SLASHstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2738] = 1,
    ACTIONS(338), 8,
      anon_sym_LT_SLASHstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2749] = 1,
    ACTIONS(352), 8,
      anon_sym_LT_SLASHstrong_GT,
      anon_sym_LT,
      sym_quote_escape,
      anon_sym_BQUOTE,
      anon_sym_BQUOTE_BQUOTE,
      anon_sym_BQUOTE_BQUOTE_BQUOTE,
      sym__terminator,
      sym__word,
  [2760] = 4,
    ACTIONS(362), 1,
      aux_sym_argument_token1,
    STATE(219), 1,
      sym_argument,
    STATE(142), 2,
      sym_macro_escape,
      aux_sym_argument_repeat1,
    ACTIONS(364), 3,
      anon_sym_AT_LBRACE,
      anon_sym_AT_RBRACE,
      anon_sym_AT_AT,
  [2776] = 4,
    ACTIONS(362), 1,
      aux_sym_argument_token1,
    STATE(245), 1,
      sym_argument,
    STATE(142), 2,
      sym_macro_escape,
      aux_sym_argument_repeat1,
    ACTIONS(364), 3,
      anon_sym_AT_LBRACE,
      anon_sym_AT_RBRACE,
      anon_sym_AT_AT,
  [2792] = 4,
    ACTIONS(366), 1,
      anon_sym_RBRACE,
    ACTIONS(368), 1,
      aux_sym_argument_token1,
    STATE(131), 2,
      sym_macro_escape,
      aux_sym_argument_repeat1,
    ACTIONS(371), 3,
      anon_sym_AT_LBRACE,
      anon_sym_AT_RBRACE,
      anon_sym_AT_AT,
  [2808] = 7,
    ACTIONS(374), 1,
      aux_sym__triple_inline_quote_token1,
    ACTIONS(376), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
    ACTIONS(378), 1,
      sym_language_identifier,
    ACTIONS(380), 1,
      aux_sym_quote_content_token1,
    STATE(185), 1,
      aux_sym_quote_content_repeat1,
    STATE(200), 1,
      aux_sym__triple_inline_quote_repeat1,
    STATE(251), 1,
      sym_quote_content,
  [2830] = 4,
    ACTIONS(362), 1,
      aux_sym_argument_token1,
    STATE(217), 1,
      sym_argument,
    STATE(142), 2,
      sym_macro_escape,
      aux_sym_argument_repeat1,
    ACTIONS(364), 3,
      anon_sym_AT_LBRACE,
      anon_sym_AT_RBRACE,
      anon_sym_AT_AT,
  [2846] = 4,
    ACTIONS(362), 1,
      aux_sym_argument_token1,
    STATE(256), 1,
      sym_argument,
    STATE(142), 2,
      sym_macro_escape,
      aux_sym_argument_repeat1,
    ACTIONS(364), 3,
      anon_sym_AT_LBRACE,
      anon_sym_AT_RBRACE,
      anon_sym_AT_AT,
  [2862] = 4,
    ACTIONS(362), 1,
      aux_sym_argument_token1,
    STATE(228), 1,
      sym_argument,
    STATE(142), 2,
      sym_macro_escape,
      aux_sym_argument_repeat1,
    ACTIONS(364), 3,
      anon_sym_AT_LBRACE,
      anon_sym_AT_RBRACE,
      anon_sym_AT_AT,
  [2878] = 7,
    ACTIONS(380), 1,
      aux_sym_quote_content_token1,
    ACTIONS(382), 1,
      aux_sym__triple_inline_quote_token1,
    ACTIONS(384), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
    ACTIONS(386), 1,
      sym_language_identifier,
    STATE(185), 1,
      aux_sym_quote_content_repeat1,
    STATE(194), 1,
      aux_sym__triple_inline_quote_repeat1,
    STATE(224), 1,
      sym_quote_content,
  [2900] = 7,
    ACTIONS(380), 1,
      aux_sym_quote_content_token1,
    ACTIONS(388), 1,
      aux_sym__triple_inline_quote_token1,
    ACTIONS(390), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
    ACTIONS(392), 1,
      sym_language_identifier,
    STATE(185), 1,
      aux_sym_quote_content_repeat1,
    STATE(201), 1,
      aux_sym__triple_inline_quote_repeat1,
    STATE(259), 1,
      sym_quote_content,
  [2922] = 7,
    ACTIONS(380), 1,
      aux_sym_quote_content_token1,
    ACTIONS(394), 1,
      aux_sym__triple_inline_quote_token1,
    ACTIONS(396), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
    ACTIONS(398), 1,
      sym_language_identifier,
    STATE(185), 1,
      aux_sym_quote_content_repeat1,
    STATE(191), 1,
      aux_sym__triple_inline_quote_repeat1,
    STATE(225), 1,
      sym_quote_content,
  [2944] = 4,
    ACTIONS(362), 1,
      aux_sym_argument_token1,
    STATE(242), 1,
      sym_argument,
    STATE(142), 2,
      sym_macro_escape,
      aux_sym_argument_repeat1,
    ACTIONS(364), 3,
      anon_sym_AT_LBRACE,
      anon_sym_AT_RBRACE,
      anon_sym_AT_AT,
  [2960] = 4,
    ACTIONS(362), 1,
      aux_sym_argument_token1,
    STATE(229), 1,
      sym_argument,
    STATE(142), 2,
      sym_macro_escape,
      aux_sym_argument_repeat1,
    ACTIONS(364), 3,
      anon_sym_AT_LBRACE,
      anon_sym_AT_RBRACE,
      anon_sym_AT_AT,
  [2976] = 4,
    ACTIONS(362), 1,
      aux_sym_argument_token1,
    STATE(218), 1,
      sym_argument,
    STATE(142), 2,
      sym_macro_escape,
      aux_sym_argument_repeat1,
    ACTIONS(364), 3,
      anon_sym_AT_LBRACE,
      anon_sym_AT_RBRACE,
      anon_sym_AT_AT,
  [2992] = 4,
    ACTIONS(400), 1,
      anon_sym_RBRACE,
    ACTIONS(402), 1,
      aux_sym_argument_token1,
    STATE(131), 2,
      sym_macro_escape,
      aux_sym_argument_repeat1,
    ACTIONS(364), 3,
      anon_sym_AT_LBRACE,
      anon_sym_AT_RBRACE,
      anon_sym_AT_AT,
  [3008] = 1,
    ACTIONS(404), 6,
      anon_sym_RBRACE,
      anon_sym_DOT,
      anon_sym_SLASH,
      anon_sym_COLON,
      anon_sym_LPAREN,
      sym__terminator,
  [3017] = 5,
    ACTIONS(358), 1,
      anon_sym_SQUOTE,
    ACTIONS(406), 1,
      sym__unquoted_atom,
    STATE(216), 1,
      sym_type,
    STATE(240), 1,
      sym_function,
    STATE(209), 2,
      sym__atom,
      sym__quoted_atom,
  [3034] = 1,
    ACTIONS(408), 6,
      anon_sym_RBRACE,
      anon_sym_DOT,
      anon_sym_SLASH,
      anon_sym_COLON,
      anon_sym_LPAREN,
      sym__terminator,
  [3043] = 3,
    ACTIONS(412), 1,
      anon_sym_SLASH,
    ACTIONS(414), 1,
      anon_sym_LPAREN,
    ACTIONS(410), 4,
      anon_sym_RBRACE,
      anon_sym_DOT,
      anon_sym_COLON,
      sym__terminator,
  [3056] = 5,
    ACTIONS(416), 1,
      anon_sym_LT,
    ACTIONS(418), 1,
      sym__terminator,
    ACTIONS(420), 1,
      sym__word,
    STATE(150), 1,
      aux_sym__author_line_repeat1,
    STATE(233), 1,
      sym_xhtml_tag,
  [3072] = 1,
    ACTIONS(422), 5,
      anon_sym_RBRACE,
      aux_sym_argument_token1,
      anon_sym_AT_LBRACE,
      anon_sym_AT_RBRACE,
      anon_sym_AT_AT,
  [3080] = 5,
    ACTIONS(416), 1,
      anon_sym_LT,
    ACTIONS(424), 1,
      sym__terminator,
    ACTIONS(426), 1,
      sym__word,
    STATE(147), 1,
      aux_sym__author_line_repeat1,
    STATE(257), 1,
      sym_xhtml_tag,
  [3096] = 3,
    ACTIONS(430), 1,
      sym__word,
    STATE(150), 1,
      aux_sym__author_line_repeat1,
    ACTIONS(428), 2,
      anon_sym_LT,
      sym__terminator,
  [3107] = 3,
    ACTIONS(433), 1,
      anon_sym_SQUOTE,
    STATE(155), 1,
      aux_sym__quoted_atom_repeat1,
    ACTIONS(435), 2,
      sym__escape_sequence,
      sym__quoted_content,
  [3118] = 4,
    ACTIONS(437), 1,
      anon_sym_TODO_COLON,
    ACTIONS(439), 1,
      aux_sym_tag_token1,
    ACTIONS(441), 1,
      anon_sym_ATlink,
    STATE(207), 1,
      sym_tag,
  [3131] = 2,
    ACTIONS(445), 1,
      anon_sym_COLON,
    ACTIONS(443), 3,
      anon_sym_RBRACE,
      anon_sym_DOT,
      sym__terminator,
  [3140] = 4,
    ACTIONS(437), 1,
      anon_sym_TODO_COLON,
    ACTIONS(439), 1,
      aux_sym_tag_token1,
    ACTIONS(447), 1,
      anon_sym_ATlink,
    STATE(208), 1,
      sym_tag,
  [3153] = 3,
    ACTIONS(449), 1,
      anon_sym_SQUOTE,
    STATE(158), 1,
      aux_sym__quoted_atom_repeat1,
    ACTIONS(451), 2,
      sym__escape_sequence,
      sym__quoted_content,
  [3164] = 4,
    ACTIONS(437), 1,
      anon_sym_TODO_COLON,
    ACTIONS(439), 1,
      aux_sym_tag_token1,
    ACTIONS(453), 1,
      anon_sym_ATlink,
    STATE(204), 1,
      sym_tag,
  [3177] = 4,
    ACTIONS(437), 1,
      anon_sym_TODO_COLON,
    ACTIONS(439), 1,
      aux_sym_tag_token1,
    ACTIONS(455), 1,
      anon_sym_ATlink,
    STATE(213), 1,
      sym_tag,
  [3190] = 3,
    ACTIONS(457), 1,
      anon_sym_SQUOTE,
    STATE(158), 1,
      aux_sym__quoted_atom_repeat1,
    ACTIONS(459), 2,
      sym__escape_sequence,
      sym__quoted_content,
  [3201] = 3,
    ACTIONS(462), 1,
      aux_sym__double_inline_quote_token1,
    ACTIONS(464), 1,
      anon_sym_SQUOTE_SQUOTE,
    STATE(202), 1,
      aux_sym__double_inline_quote_repeat1,
  [3211] = 3,
    ACTIONS(466), 1,
      aux_sym_xhtml_tag_token1,
    ACTIONS(468), 1,
      anon_sym_GT,
    STATE(171), 1,
      aux_sym_xhtml_tag_repeat1,
  [3221] = 3,
    ACTIONS(470), 1,
      aux_sym_xhtml_tag_token1,
    ACTIONS(472), 1,
      anon_sym_GT,
    STATE(168), 1,
      aux_sym_xhtml_tag_repeat1,
  [3231] = 3,
    ACTIONS(474), 1,
      aux_sym_quote_content_token1,
    STATE(185), 1,
      aux_sym_quote_content_repeat1,
    STATE(227), 1,
      sym_quote_content,
  [3241] = 3,
    ACTIONS(476), 1,
      aux_sym__double_inline_quote_token1,
    ACTIONS(478), 1,
      anon_sym_SQUOTE_SQUOTE,
    STATE(170), 1,
      aux_sym__double_inline_quote_repeat1,
  [3251] = 1,
    ACTIONS(480), 3,
      anon_sym_RBRACE,
      anon_sym_DOT,
      sym__terminator,
  [3257] = 3,
    ACTIONS(474), 1,
      aux_sym_quote_content_token1,
    STATE(185), 1,
      aux_sym_quote_content_repeat1,
    STATE(243), 1,
      sym_quote_content,
  [3267] = 3,
    ACTIONS(482), 1,
      aux_sym__triple_inline_quote_token1,
    ACTIONS(484), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
    STATE(181), 1,
      aux_sym__triple_inline_quote_repeat1,
  [3277] = 3,
    ACTIONS(474), 1,
      aux_sym_quote_content_token1,
    STATE(185), 1,
      aux_sym_quote_content_repeat1,
    STATE(220), 1,
      sym_quote_content,
  [3287] = 3,
    ACTIONS(486), 1,
      aux_sym_xhtml_tag_token1,
    ACTIONS(488), 1,
      anon_sym_GT,
    STATE(177), 1,
      aux_sym_xhtml_tag_repeat1,
  [3297] = 1,
    ACTIONS(490), 3,
      anon_sym_RBRACE,
      anon_sym_DOT,
      sym__terminator,
  [3303] = 3,
    ACTIONS(492), 1,
      aux_sym__double_inline_quote_token1,
    ACTIONS(494), 1,
      anon_sym_SQUOTE_SQUOTE,
    STATE(176), 1,
      aux_sym__double_inline_quote_repeat1,
  [3313] = 3,
    ACTIONS(486), 1,
      aux_sym_xhtml_tag_token1,
    ACTIONS(496), 1,
      anon_sym_GT,
    STATE(177), 1,
      aux_sym_xhtml_tag_repeat1,
  [3323] = 3,
    ACTIONS(498), 1,
      aux_sym__triple_inline_quote_token1,
    ACTIONS(500), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
    STATE(174), 1,
      aux_sym__triple_inline_quote_repeat1,
  [3333] = 3,
    ACTIONS(502), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
    ACTIONS(504), 1,
      aux_sym_quote_content_token1,
    STATE(173), 1,
      aux_sym_quote_content_repeat1,
  [3343] = 3,
    ACTIONS(507), 1,
      aux_sym__triple_inline_quote_token1,
    ACTIONS(510), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
    STATE(174), 1,
      aux_sym__triple_inline_quote_repeat1,
  [3353] = 3,
    ACTIONS(492), 1,
      aux_sym__double_inline_quote_token1,
    ACTIONS(512), 1,
      anon_sym_SQUOTE_SQUOTE,
    STATE(176), 1,
      aux_sym__double_inline_quote_repeat1,
  [3363] = 3,
    ACTIONS(514), 1,
      aux_sym__double_inline_quote_token1,
    ACTIONS(517), 1,
      anon_sym_SQUOTE_SQUOTE,
    STATE(176), 1,
      aux_sym__double_inline_quote_repeat1,
  [3373] = 3,
    ACTIONS(519), 1,
      aux_sym_xhtml_tag_token1,
    ACTIONS(522), 1,
      anon_sym_GT,
    STATE(177), 1,
      aux_sym_xhtml_tag_repeat1,
  [3383] = 3,
    ACTIONS(486), 1,
      aux_sym_xhtml_tag_token1,
    ACTIONS(524), 1,
      anon_sym_GT,
    STATE(177), 1,
      aux_sym_xhtml_tag_repeat1,
  [3393] = 3,
    ACTIONS(526), 1,
      aux_sym__double_inline_quote_token1,
    ACTIONS(528), 1,
      anon_sym_SQUOTE_SQUOTE,
    STATE(175), 1,
      aux_sym__double_inline_quote_repeat1,
  [3403] = 3,
    ACTIONS(530), 1,
      aux_sym_xhtml_tag_token1,
    ACTIONS(532), 1,
      anon_sym_GT,
    STATE(178), 1,
      aux_sym_xhtml_tag_repeat1,
  [3413] = 3,
    ACTIONS(498), 1,
      aux_sym__triple_inline_quote_token1,
    ACTIONS(534), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
    STATE(174), 1,
      aux_sym__triple_inline_quote_repeat1,
  [3423] = 3,
    ACTIONS(492), 1,
      aux_sym__double_inline_quote_token1,
    ACTIONS(536), 1,
      anon_sym_SQUOTE_SQUOTE,
    STATE(176), 1,
      aux_sym__double_inline_quote_repeat1,
  [3433] = 3,
    ACTIONS(538), 1,
      aux_sym_xhtml_tag_token1,
    ACTIONS(540), 1,
      anon_sym_GT,
    STATE(190), 1,
      aux_sym_xhtml_tag_repeat1,
  [3443] = 3,
    ACTIONS(542), 1,
      aux_sym__double_inline_quote_token1,
    ACTIONS(544), 1,
      anon_sym_SQUOTE_SQUOTE,
    STATE(192), 1,
      aux_sym__double_inline_quote_repeat1,
  [3453] = 3,
    ACTIONS(546), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
    ACTIONS(548), 1,
      aux_sym_quote_content_token1,
    STATE(173), 1,
      aux_sym_quote_content_repeat1,
  [3463] = 3,
    ACTIONS(486), 1,
      aux_sym_xhtml_tag_token1,
    ACTIONS(550), 1,
      anon_sym_GT,
    STATE(177), 1,
      aux_sym_xhtml_tag_repeat1,
  [3473] = 3,
    ACTIONS(552), 1,
      aux_sym__triple_inline_quote_token1,
    ACTIONS(554), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
    STATE(172), 1,
      aux_sym__triple_inline_quote_repeat1,
  [3483] = 3,
    ACTIONS(556), 1,
      aux_sym__double_inline_quote_token1,
    ACTIONS(558), 1,
      anon_sym_SQUOTE_SQUOTE,
    STATE(182), 1,
      aux_sym__double_inline_quote_repeat1,
  [3493] = 3,
    ACTIONS(560), 1,
      aux_sym_xhtml_tag_token1,
    ACTIONS(562), 1,
      anon_sym_GT,
    STATE(186), 1,
      aux_sym_xhtml_tag_repeat1,
  [3503] = 3,
    ACTIONS(486), 1,
      aux_sym_xhtml_tag_token1,
    ACTIONS(564), 1,
      anon_sym_GT,
    STATE(177), 1,
      aux_sym_xhtml_tag_repeat1,
  [3513] = 3,
    ACTIONS(498), 1,
      aux_sym__triple_inline_quote_token1,
    ACTIONS(566), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
    STATE(174), 1,
      aux_sym__triple_inline_quote_repeat1,
  [3523] = 3,
    ACTIONS(492), 1,
      aux_sym__double_inline_quote_token1,
    ACTIONS(568), 1,
      anon_sym_SQUOTE_SQUOTE,
    STATE(176), 1,
      aux_sym__double_inline_quote_repeat1,
  [3533] = 3,
    ACTIONS(492), 1,
      aux_sym__double_inline_quote_token1,
    ACTIONS(570), 1,
      anon_sym_SQUOTE_SQUOTE,
    STATE(176), 1,
      aux_sym__double_inline_quote_repeat1,
  [3543] = 3,
    ACTIONS(498), 1,
      aux_sym__triple_inline_quote_token1,
    ACTIONS(572), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
    STATE(174), 1,
      aux_sym__triple_inline_quote_repeat1,
  [3553] = 3,
    ACTIONS(486), 1,
      aux_sym_xhtml_tag_token1,
    ACTIONS(574), 1,
      anon_sym_GT,
    STATE(177), 1,
      aux_sym_xhtml_tag_repeat1,
  [3563] = 3,
    ACTIONS(474), 1,
      aux_sym_quote_content_token1,
    STATE(185), 1,
      aux_sym_quote_content_repeat1,
    STATE(239), 1,
      sym_quote_content,
  [3573] = 3,
    ACTIONS(576), 1,
      aux_sym__double_inline_quote_token1,
    ACTIONS(578), 1,
      anon_sym_SQUOTE_SQUOTE,
    STATE(193), 1,
      aux_sym__double_inline_quote_repeat1,
  [3583] = 3,
    ACTIONS(580), 1,
      aux_sym_xhtml_tag_token1,
    ACTIONS(582), 1,
      anon_sym_GT,
    STATE(195), 1,
      aux_sym_xhtml_tag_repeat1,
  [3593] = 3,
    ACTIONS(584), 1,
      aux_sym_xhtml_tag_token1,
    ACTIONS(586), 1,
      anon_sym_GT,
    STATE(203), 1,
      aux_sym_xhtml_tag_repeat1,
  [3603] = 3,
    ACTIONS(498), 1,
      aux_sym__triple_inline_quote_token1,
    ACTIONS(588), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
    STATE(174), 1,
      aux_sym__triple_inline_quote_repeat1,
  [3613] = 3,
    ACTIONS(498), 1,
      aux_sym__triple_inline_quote_token1,
    ACTIONS(590), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
    STATE(174), 1,
      aux_sym__triple_inline_quote_repeat1,
  [3623] = 3,
    ACTIONS(492), 1,
      aux_sym__double_inline_quote_token1,
    ACTIONS(592), 1,
      anon_sym_SQUOTE_SQUOTE,
    STATE(176), 1,
      aux_sym__double_inline_quote_repeat1,
  [3633] = 3,
    ACTIONS(486), 1,
      aux_sym_xhtml_tag_token1,
    ACTIONS(594), 1,
      anon_sym_GT,
    STATE(177), 1,
      aux_sym_xhtml_tag_repeat1,
  [3643] = 2,
    ACTIONS(596), 1,
      aux_sym_macro_token1,
    ACTIONS(598), 1,
      anon_sym_RBRACE,
  [3650] = 2,
    ACTIONS(356), 1,
      anon_sym_RBRACE,
    ACTIONS(600), 1,
      aux_sym_macro_token1,
  [3657] = 2,
    ACTIONS(602), 1,
      sym__terminator,
    STATE(19), 1,
      aux_sym_source_repeat1,
  [3664] = 2,
    ACTIONS(604), 1,
      aux_sym_macro_token1,
    ACTIONS(606), 1,
      anon_sym_RBRACE,
  [3671] = 2,
    ACTIONS(608), 1,
      aux_sym_macro_token1,
    ACTIONS(610), 1,
      anon_sym_RBRACE,
  [3678] = 2,
    ACTIONS(412), 1,
      anon_sym_SLASH,
    ACTIONS(414), 1,
      anon_sym_LPAREN,
  [3685] = 2,
    ACTIONS(612), 1,
      anon_sym_RBRACE,
    ACTIONS(614), 1,
      anon_sym_DOT,
  [3692] = 2,
    ACTIONS(616), 1,
      anon_sym_RBRACE,
    ACTIONS(618), 1,
      anon_sym_DOT,
  [3699] = 2,
    ACTIONS(620), 1,
      anon_sym_RBRACE,
    ACTIONS(622), 1,
      anon_sym_DOT,
  [3706] = 2,
    ACTIONS(624), 1,
      aux_sym_macro_token1,
    ACTIONS(626), 1,
      anon_sym_RBRACE,
  [3713] = 2,
    ACTIONS(628), 1,
      anon_sym_RBRACE,
    ACTIONS(630), 1,
      anon_sym_DOT,
  [3720] = 1,
    ACTIONS(632), 1,
      anon_sym_RPAREN,
  [3724] = 1,
    ACTIONS(634), 1,
      anon_sym_LPAREN,
  [3728] = 1,
    ACTIONS(636), 1,
      anon_sym_RBRACE,
  [3732] = 1,
    ACTIONS(638), 1,
      anon_sym_RBRACE,
  [3736] = 1,
    ACTIONS(640), 1,
      anon_sym_RBRACE,
  [3740] = 1,
    ACTIONS(642), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
  [3744] = 1,
    ACTIONS(644), 1,
      anon_sym_LT_SLASHem_GT,
  [3748] = 1,
    ACTIONS(646), 1,
      anon_sym_LT_SLASHstrong_GT,
  [3752] = 1,
    ACTIONS(648), 1,
      anon_sym_SQUOTE,
  [3756] = 1,
    ACTIONS(650), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
  [3760] = 1,
    ACTIONS(652), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
  [3764] = 1,
    ACTIONS(654), 1,
      anon_sym_SQUOTE,
  [3768] = 1,
    ACTIONS(656), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
  [3772] = 1,
    ACTIONS(658), 1,
      anon_sym_RBRACE,
  [3776] = 1,
    ACTIONS(660), 1,
      anon_sym_RBRACE,
  [3780] = 1,
    ACTIONS(662), 1,
      anon_sym_LT_SLASHstrong_GT,
  [3784] = 1,
    ACTIONS(664), 1,
      anon_sym_LT_SLASHem_GT,
  [3788] = 1,
    ACTIONS(666), 1,
      anon_sym_SQUOTE,
  [3792] = 1,
    ACTIONS(668), 1,
      sym__terminator,
  [3796] = 1,
    ACTIONS(632), 1,
      sym_arity,
  [3800] = 1,
    ACTIONS(670), 1,
      anon_sym_LT_SLASHstrong_GT,
  [3804] = 1,
    ACTIONS(672), 1,
      sym__terminator,
  [3808] = 1,
    ACTIONS(674), 1,
      anon_sym_LT_SLASHem_GT,
  [3812] = 1,
    ACTIONS(676), 1,
      anon_sym_SQUOTE,
  [3816] = 1,
    ACTIONS(678), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
  [3820] = 1,
    ACTIONS(680), 1,
      anon_sym_SLASH,
  [3824] = 1,
    ACTIONS(682), 1,
      aux_sym__separator_token1,
  [3828] = 1,
    ACTIONS(684), 1,
      anon_sym_RBRACE,
  [3832] = 1,
    ACTIONS(686), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
  [3836] = 1,
    ACTIONS(688), 1,
      anon_sym_SQUOTE,
  [3840] = 1,
    ACTIONS(690), 1,
      anon_sym_RBRACE,
  [3844] = 1,
    ACTIONS(692), 1,
      aux_sym__inline_quote_token1,
  [3848] = 1,
    ACTIONS(694), 1,
      anon_sym_LT_SLASHstrong_GT,
  [3852] = 1,
    ACTIONS(696), 1,
      sym_arity,
  [3856] = 1,
    ACTIONS(698), 1,
      anon_sym_LT_SLASHem_GT,
  [3860] = 1,
    ACTIONS(696), 1,
      anon_sym_RPAREN,
  [3864] = 1,
    ACTIONS(700), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
  [3868] = 1,
    ACTIONS(702), 1,
      anon_sym_LPAREN,
  [3872] = 1,
    ACTIONS(704), 1,
      anon_sym_SLASH,
  [3876] = 1,
    ACTIONS(706), 1,
      aux_sym__inline_quote_token1,
  [3880] = 1,
    ACTIONS(708), 1,
      sym__terminator,
  [3884] = 1,
    ACTIONS(710), 1,
      anon_sym_RBRACE,
  [3888] = 1,
    ACTIONS(712), 1,
      sym__terminator,
  [3892] = 1,
    ACTIONS(714), 1,
      sym__terminator,
  [3896] = 1,
    ACTIONS(716), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
  [3900] = 1,
    ACTIONS(718), 1,
      ts_builtin_sym_end,
  [3904] = 1,
    ACTIONS(720), 1,
      anon_sym_SQUOTE,
  [3908] = 1,
    ACTIONS(722), 1,
      aux_sym__inline_quote_token1,
  [3912] = 1,
    ACTIONS(724), 1,
      aux_sym__inline_quote_token1,
  [3916] = 1,
    ACTIONS(726), 1,
      sym__terminator,
  [3920] = 1,
    ACTIONS(728), 1,
      sym__terminator,
  [3924] = 1,
    ACTIONS(730), 1,
      sym__word,
  [3928] = 1,
    ACTIONS(732), 1,
      aux_sym__inline_quote_token1,
  [3932] = 1,
    ACTIONS(734), 1,
      aux_sym__inline_quote_token1,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 95,
  [SMALL_STATE(4)] = 184,
  [SMALL_STATE(5)] = 273,
  [SMALL_STATE(6)] = 362,
  [SMALL_STATE(7)] = 411,
  [SMALL_STATE(8)] = 460,
  [SMALL_STATE(9)] = 509,
  [SMALL_STATE(10)] = 558,
  [SMALL_STATE(11)] = 607,
  [SMALL_STATE(12)] = 656,
  [SMALL_STATE(13)] = 705,
  [SMALL_STATE(14)] = 754,
  [SMALL_STATE(15)] = 803,
  [SMALL_STATE(16)] = 852,
  [SMALL_STATE(17)] = 901,
  [SMALL_STATE(18)] = 950,
  [SMALL_STATE(19)] = 996,
  [SMALL_STATE(20)] = 1026,
  [SMALL_STATE(21)] = 1072,
  [SMALL_STATE(22)] = 1102,
  [SMALL_STATE(23)] = 1148,
  [SMALL_STATE(24)] = 1179,
  [SMALL_STATE(25)] = 1210,
  [SMALL_STATE(26)] = 1241,
  [SMALL_STATE(27)] = 1272,
  [SMALL_STATE(28)] = 1303,
  [SMALL_STATE(29)] = 1334,
  [SMALL_STATE(30)] = 1365,
  [SMALL_STATE(31)] = 1396,
  [SMALL_STATE(32)] = 1427,
  [SMALL_STATE(33)] = 1458,
  [SMALL_STATE(34)] = 1489,
  [SMALL_STATE(35)] = 1520,
  [SMALL_STATE(36)] = 1533,
  [SMALL_STATE(37)] = 1546,
  [SMALL_STATE(38)] = 1559,
  [SMALL_STATE(39)] = 1572,
  [SMALL_STATE(40)] = 1585,
  [SMALL_STATE(41)] = 1598,
  [SMALL_STATE(42)] = 1611,
  [SMALL_STATE(43)] = 1624,
  [SMALL_STATE(44)] = 1637,
  [SMALL_STATE(45)] = 1650,
  [SMALL_STATE(46)] = 1663,
  [SMALL_STATE(47)] = 1676,
  [SMALL_STATE(48)] = 1689,
  [SMALL_STATE(49)] = 1702,
  [SMALL_STATE(50)] = 1715,
  [SMALL_STATE(51)] = 1728,
  [SMALL_STATE(52)] = 1741,
  [SMALL_STATE(53)] = 1754,
  [SMALL_STATE(54)] = 1767,
  [SMALL_STATE(55)] = 1780,
  [SMALL_STATE(56)] = 1793,
  [SMALL_STATE(57)] = 1806,
  [SMALL_STATE(58)] = 1819,
  [SMALL_STATE(59)] = 1832,
  [SMALL_STATE(60)] = 1845,
  [SMALL_STATE(61)] = 1858,
  [SMALL_STATE(62)] = 1871,
  [SMALL_STATE(63)] = 1884,
  [SMALL_STATE(64)] = 1897,
  [SMALL_STATE(65)] = 1910,
  [SMALL_STATE(66)] = 1923,
  [SMALL_STATE(67)] = 1936,
  [SMALL_STATE(68)] = 1949,
  [SMALL_STATE(69)] = 1962,
  [SMALL_STATE(70)] = 1975,
  [SMALL_STATE(71)] = 1988,
  [SMALL_STATE(72)] = 2001,
  [SMALL_STATE(73)] = 2014,
  [SMALL_STATE(74)] = 2027,
  [SMALL_STATE(75)] = 2040,
  [SMALL_STATE(76)] = 2053,
  [SMALL_STATE(77)] = 2066,
  [SMALL_STATE(78)] = 2079,
  [SMALL_STATE(79)] = 2092,
  [SMALL_STATE(80)] = 2105,
  [SMALL_STATE(81)] = 2118,
  [SMALL_STATE(82)] = 2131,
  [SMALL_STATE(83)] = 2144,
  [SMALL_STATE(84)] = 2157,
  [SMALL_STATE(85)] = 2170,
  [SMALL_STATE(86)] = 2183,
  [SMALL_STATE(87)] = 2196,
  [SMALL_STATE(88)] = 2209,
  [SMALL_STATE(89)] = 2222,
  [SMALL_STATE(90)] = 2235,
  [SMALL_STATE(91)] = 2248,
  [SMALL_STATE(92)] = 2261,
  [SMALL_STATE(93)] = 2274,
  [SMALL_STATE(94)] = 2287,
  [SMALL_STATE(95)] = 2300,
  [SMALL_STATE(96)] = 2313,
  [SMALL_STATE(97)] = 2326,
  [SMALL_STATE(98)] = 2339,
  [SMALL_STATE(99)] = 2352,
  [SMALL_STATE(100)] = 2365,
  [SMALL_STATE(101)] = 2378,
  [SMALL_STATE(102)] = 2391,
  [SMALL_STATE(103)] = 2404,
  [SMALL_STATE(104)] = 2417,
  [SMALL_STATE(105)] = 2430,
  [SMALL_STATE(106)] = 2443,
  [SMALL_STATE(107)] = 2456,
  [SMALL_STATE(108)] = 2469,
  [SMALL_STATE(109)] = 2480,
  [SMALL_STATE(110)] = 2491,
  [SMALL_STATE(111)] = 2502,
  [SMALL_STATE(112)] = 2525,
  [SMALL_STATE(113)] = 2548,
  [SMALL_STATE(114)] = 2571,
  [SMALL_STATE(115)] = 2594,
  [SMALL_STATE(116)] = 2605,
  [SMALL_STATE(117)] = 2616,
  [SMALL_STATE(118)] = 2639,
  [SMALL_STATE(119)] = 2650,
  [SMALL_STATE(120)] = 2661,
  [SMALL_STATE(121)] = 2672,
  [SMALL_STATE(122)] = 2683,
  [SMALL_STATE(123)] = 2694,
  [SMALL_STATE(124)] = 2705,
  [SMALL_STATE(125)] = 2716,
  [SMALL_STATE(126)] = 2727,
  [SMALL_STATE(127)] = 2738,
  [SMALL_STATE(128)] = 2749,
  [SMALL_STATE(129)] = 2760,
  [SMALL_STATE(130)] = 2776,
  [SMALL_STATE(131)] = 2792,
  [SMALL_STATE(132)] = 2808,
  [SMALL_STATE(133)] = 2830,
  [SMALL_STATE(134)] = 2846,
  [SMALL_STATE(135)] = 2862,
  [SMALL_STATE(136)] = 2878,
  [SMALL_STATE(137)] = 2900,
  [SMALL_STATE(138)] = 2922,
  [SMALL_STATE(139)] = 2944,
  [SMALL_STATE(140)] = 2960,
  [SMALL_STATE(141)] = 2976,
  [SMALL_STATE(142)] = 2992,
  [SMALL_STATE(143)] = 3008,
  [SMALL_STATE(144)] = 3017,
  [SMALL_STATE(145)] = 3034,
  [SMALL_STATE(146)] = 3043,
  [SMALL_STATE(147)] = 3056,
  [SMALL_STATE(148)] = 3072,
  [SMALL_STATE(149)] = 3080,
  [SMALL_STATE(150)] = 3096,
  [SMALL_STATE(151)] = 3107,
  [SMALL_STATE(152)] = 3118,
  [SMALL_STATE(153)] = 3131,
  [SMALL_STATE(154)] = 3140,
  [SMALL_STATE(155)] = 3153,
  [SMALL_STATE(156)] = 3164,
  [SMALL_STATE(157)] = 3177,
  [SMALL_STATE(158)] = 3190,
  [SMALL_STATE(159)] = 3201,
  [SMALL_STATE(160)] = 3211,
  [SMALL_STATE(161)] = 3221,
  [SMALL_STATE(162)] = 3231,
  [SMALL_STATE(163)] = 3241,
  [SMALL_STATE(164)] = 3251,
  [SMALL_STATE(165)] = 3257,
  [SMALL_STATE(166)] = 3267,
  [SMALL_STATE(167)] = 3277,
  [SMALL_STATE(168)] = 3287,
  [SMALL_STATE(169)] = 3297,
  [SMALL_STATE(170)] = 3303,
  [SMALL_STATE(171)] = 3313,
  [SMALL_STATE(172)] = 3323,
  [SMALL_STATE(173)] = 3333,
  [SMALL_STATE(174)] = 3343,
  [SMALL_STATE(175)] = 3353,
  [SMALL_STATE(176)] = 3363,
  [SMALL_STATE(177)] = 3373,
  [SMALL_STATE(178)] = 3383,
  [SMALL_STATE(179)] = 3393,
  [SMALL_STATE(180)] = 3403,
  [SMALL_STATE(181)] = 3413,
  [SMALL_STATE(182)] = 3423,
  [SMALL_STATE(183)] = 3433,
  [SMALL_STATE(184)] = 3443,
  [SMALL_STATE(185)] = 3453,
  [SMALL_STATE(186)] = 3463,
  [SMALL_STATE(187)] = 3473,
  [SMALL_STATE(188)] = 3483,
  [SMALL_STATE(189)] = 3493,
  [SMALL_STATE(190)] = 3503,
  [SMALL_STATE(191)] = 3513,
  [SMALL_STATE(192)] = 3523,
  [SMALL_STATE(193)] = 3533,
  [SMALL_STATE(194)] = 3543,
  [SMALL_STATE(195)] = 3553,
  [SMALL_STATE(196)] = 3563,
  [SMALL_STATE(197)] = 3573,
  [SMALL_STATE(198)] = 3583,
  [SMALL_STATE(199)] = 3593,
  [SMALL_STATE(200)] = 3603,
  [SMALL_STATE(201)] = 3613,
  [SMALL_STATE(202)] = 3623,
  [SMALL_STATE(203)] = 3633,
  [SMALL_STATE(204)] = 3643,
  [SMALL_STATE(205)] = 3650,
  [SMALL_STATE(206)] = 3657,
  [SMALL_STATE(207)] = 3664,
  [SMALL_STATE(208)] = 3671,
  [SMALL_STATE(209)] = 3678,
  [SMALL_STATE(210)] = 3685,
  [SMALL_STATE(211)] = 3692,
  [SMALL_STATE(212)] = 3699,
  [SMALL_STATE(213)] = 3706,
  [SMALL_STATE(214)] = 3713,
  [SMALL_STATE(215)] = 3720,
  [SMALL_STATE(216)] = 3724,
  [SMALL_STATE(217)] = 3728,
  [SMALL_STATE(218)] = 3732,
  [SMALL_STATE(219)] = 3736,
  [SMALL_STATE(220)] = 3740,
  [SMALL_STATE(221)] = 3744,
  [SMALL_STATE(222)] = 3748,
  [SMALL_STATE(223)] = 3752,
  [SMALL_STATE(224)] = 3756,
  [SMALL_STATE(225)] = 3760,
  [SMALL_STATE(226)] = 3764,
  [SMALL_STATE(227)] = 3768,
  [SMALL_STATE(228)] = 3772,
  [SMALL_STATE(229)] = 3776,
  [SMALL_STATE(230)] = 3780,
  [SMALL_STATE(231)] = 3784,
  [SMALL_STATE(232)] = 3788,
  [SMALL_STATE(233)] = 3792,
  [SMALL_STATE(234)] = 3796,
  [SMALL_STATE(235)] = 3800,
  [SMALL_STATE(236)] = 3804,
  [SMALL_STATE(237)] = 3808,
  [SMALL_STATE(238)] = 3812,
  [SMALL_STATE(239)] = 3816,
  [SMALL_STATE(240)] = 3820,
  [SMALL_STATE(241)] = 3824,
  [SMALL_STATE(242)] = 3828,
  [SMALL_STATE(243)] = 3832,
  [SMALL_STATE(244)] = 3836,
  [SMALL_STATE(245)] = 3840,
  [SMALL_STATE(246)] = 3844,
  [SMALL_STATE(247)] = 3848,
  [SMALL_STATE(248)] = 3852,
  [SMALL_STATE(249)] = 3856,
  [SMALL_STATE(250)] = 3860,
  [SMALL_STATE(251)] = 3864,
  [SMALL_STATE(252)] = 3868,
  [SMALL_STATE(253)] = 3872,
  [SMALL_STATE(254)] = 3876,
  [SMALL_STATE(255)] = 3880,
  [SMALL_STATE(256)] = 3884,
  [SMALL_STATE(257)] = 3888,
  [SMALL_STATE(258)] = 3892,
  [SMALL_STATE(259)] = 3896,
  [SMALL_STATE(260)] = 3900,
  [SMALL_STATE(261)] = 3904,
  [SMALL_STATE(262)] = 3908,
  [SMALL_STATE(263)] = 3912,
  [SMALL_STATE(264)] = 3916,
  [SMALL_STATE(265)] = 3920,
  [SMALL_STATE(266)] = 3924,
  [SMALL_STATE(267)] = 3928,
  [SMALL_STATE(268)] = 3932,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source, 0),
  [5] = {.entry = {.count = 1, .reusable = false}}, SHIFT(241),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(149),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(117),
  [11] = {.entry = {.count = 1, .reusable = false}}, SHIFT(266),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(22),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(20),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(18),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(154),
  [21] = {.entry = {.count = 1, .reusable = false}}, SHIFT(95),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(29),
  [25] = {.entry = {.count = 1, .reusable = false}}, SHIFT(28),
  [27] = {.entry = {.count = 1, .reusable = false}}, SHIFT(161),
  [29] = {.entry = {.count = 1, .reusable = false}}, SHIFT(38),
  [31] = {.entry = {.count = 1, .reusable = false}}, SHIFT(263),
  [33] = {.entry = {.count = 1, .reusable = false}}, SHIFT(163),
  [35] = {.entry = {.count = 1, .reusable = false}}, SHIFT(132),
  [37] = {.entry = {.count = 1, .reusable = false}}, SHIFT(2),
  [39] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source, 1),
  [41] = {.entry = {.count = 1, .reusable = false}}, SHIFT(21),
  [43] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source, 2),
  [45] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_repeat2, 2),
  [47] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat2, 2), SHIFT_REPEAT(241),
  [50] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat2, 2), SHIFT_REPEAT(149),
  [53] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat2, 2), SHIFT_REPEAT(117),
  [56] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat2, 2), SHIFT_REPEAT(266),
  [59] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat2, 2), SHIFT_REPEAT(22),
  [62] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat2, 2), SHIFT_REPEAT(20),
  [65] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat2, 2), SHIFT_REPEAT(18),
  [68] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat2, 2), SHIFT_REPEAT(154),
  [71] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat2, 2), SHIFT_REPEAT(95),
  [74] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat2, 2), SHIFT_REPEAT(29),
  [77] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat2, 2), SHIFT_REPEAT(28),
  [80] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat2, 2), SHIFT_REPEAT(161),
  [83] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat2, 2), SHIFT_REPEAT(38),
  [86] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat2, 2), SHIFT_REPEAT(263),
  [89] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat2, 2), SHIFT_REPEAT(163),
  [92] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat2, 2), SHIFT_REPEAT(132),
  [95] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym__text_line, 2),
  [97] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(157),
  [100] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(25),
  [103] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(26),
  [106] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(189),
  [109] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(51),
  [112] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(262),
  [115] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(197),
  [118] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(138),
  [121] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(152),
  [124] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(34),
  [127] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(33),
  [130] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(198),
  [133] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(36),
  [136] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(254),
  [139] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(159),
  [142] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(137),
  [145] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(156),
  [148] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(31),
  [151] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(30),
  [154] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(199),
  [157] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(104),
  [160] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(246),
  [163] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(184),
  [166] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(136),
  [169] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__tag_line, 2),
  [171] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(154),
  [174] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(29),
  [177] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(28),
  [180] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(161),
  [183] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(38),
  [186] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(263),
  [189] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(163),
  [192] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__text_line, 2), SHIFT_REPEAT(132),
  [195] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__param_line, 2, .production_id = 2),
  [197] = {.entry = {.count = 1, .reusable = false}}, SHIFT(236),
  [199] = {.entry = {.count = 1, .reusable = false}}, SHIFT(156),
  [201] = {.entry = {.count = 1, .reusable = false}}, SHIFT(31),
  [203] = {.entry = {.count = 1, .reusable = false}}, SHIFT(30),
  [205] = {.entry = {.count = 1, .reusable = false}}, SHIFT(199),
  [207] = {.entry = {.count = 1, .reusable = false}}, SHIFT(104),
  [209] = {.entry = {.count = 1, .reusable = false}}, SHIFT(246),
  [211] = {.entry = {.count = 1, .reusable = false}}, SHIFT(184),
  [213] = {.entry = {.count = 1, .reusable = false}}, SHIFT(136),
  [215] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__param_line, 3, .production_id = 2),
  [217] = {.entry = {.count = 1, .reusable = false}}, SHIFT(152),
  [219] = {.entry = {.count = 1, .reusable = false}}, SHIFT(34),
  [221] = {.entry = {.count = 1, .reusable = false}}, SHIFT(33),
  [223] = {.entry = {.count = 1, .reusable = false}}, SHIFT(198),
  [225] = {.entry = {.count = 1, .reusable = false}}, SHIFT(36),
  [227] = {.entry = {.count = 1, .reusable = false}}, SHIFT(254),
  [229] = {.entry = {.count = 1, .reusable = false}}, SHIFT(159),
  [231] = {.entry = {.count = 1, .reusable = false}}, SHIFT(137),
  [233] = {.entry = {.count = 1, .reusable = false}}, SHIFT(157),
  [235] = {.entry = {.count = 1, .reusable = false}}, SHIFT(25),
  [237] = {.entry = {.count = 1, .reusable = false}}, SHIFT(26),
  [239] = {.entry = {.count = 1, .reusable = false}}, SHIFT(189),
  [241] = {.entry = {.count = 1, .reusable = false}}, SHIFT(51),
  [243] = {.entry = {.count = 1, .reusable = false}}, SHIFT(262),
  [245] = {.entry = {.count = 1, .reusable = false}}, SHIFT(197),
  [247] = {.entry = {.count = 1, .reusable = false}}, SHIFT(138),
  [249] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__tag_line, 1),
  [251] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__line, 1),
  [253] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_source_repeat2, 2),
  [255] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_repeat1, 2),
  [257] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_source_repeat1, 2),
  [259] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_repeat1, 2), SHIFT_REPEAT(21),
  [262] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_xhtml_tag_content_repeat1, 2),
  [264] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_xhtml_tag_content_repeat1, 2), SHIFT_REPEAT(180),
  [267] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_xhtml_tag_content_repeat1, 2), SHIFT_REPEAT(23),
  [270] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_xhtml_tag_content_repeat1, 2), SHIFT_REPEAT(267),
  [273] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_xhtml_tag_content_repeat1, 2), SHIFT_REPEAT(188),
  [276] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_xhtml_tag_content_repeat1, 2), SHIFT_REPEAT(166),
  [279] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_xhtml_tag_content_repeat1, 2), SHIFT_REPEAT(160),
  [282] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_xhtml_tag_content_repeat1, 2), SHIFT_REPEAT(24),
  [285] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_xhtml_tag_content_repeat1, 2), SHIFT_REPEAT(268),
  [288] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_xhtml_tag_content_repeat1, 2), SHIFT_REPEAT(179),
  [291] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_xhtml_tag_content_repeat1, 2), SHIFT_REPEAT(187),
  [294] = {.entry = {.count = 1, .reusable = false}}, SHIFT(180),
  [296] = {.entry = {.count = 1, .reusable = false}}, SHIFT(27),
  [298] = {.entry = {.count = 1, .reusable = false}}, SHIFT(267),
  [300] = {.entry = {.count = 1, .reusable = false}}, SHIFT(188),
  [302] = {.entry = {.count = 1, .reusable = false}}, SHIFT(166),
  [304] = {.entry = {.count = 1, .reusable = false}}, SHIFT(160),
  [306] = {.entry = {.count = 1, .reusable = false}}, SHIFT(32),
  [308] = {.entry = {.count = 1, .reusable = false}}, SHIFT(268),
  [310] = {.entry = {.count = 1, .reusable = false}}, SHIFT(179),
  [312] = {.entry = {.count = 1, .reusable = false}}, SHIFT(187),
  [314] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_xhtml_tag_content, 1),
  [316] = {.entry = {.count = 1, .reusable = false}}, SHIFT(23),
  [318] = {.entry = {.count = 1, .reusable = false}}, SHIFT(24),
  [320] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_strong_xhtml_tag, 3),
  [322] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym__text_line, 1),
  [324] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__double_inline_quote, 3),
  [326] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__inline_quote, 3),
  [328] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_xhtml_tag, 3),
  [330] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_macro, 1),
  [332] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_inline_quote, 1),
  [334] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_em_xhtml_tag, 3),
  [336] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_macro, 3),
  [338] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__triple_inline_quote, 2),
  [340] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__double_inline_quote, 2),
  [342] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_xhtml_tag, 2),
  [344] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__link_macro, 6, .production_id = 7),
  [346] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_macro, 5),
  [348] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block_quote, 4, .production_id = 6),
  [350] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__link_macro, 4),
  [352] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__triple_inline_quote, 3),
  [354] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block_quote, 3, .production_id = 5),
  [356] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_tag, 1),
  [358] = {.entry = {.count = 1, .reusable = true}}, SHIFT(151),
  [360] = {.entry = {.count = 1, .reusable = true}}, SHIFT(146),
  [362] = {.entry = {.count = 1, .reusable = false}}, SHIFT(142),
  [364] = {.entry = {.count = 1, .reusable = false}}, SHIFT(148),
  [366] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_argument_repeat1, 2),
  [368] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_argument_repeat1, 2), SHIFT_REPEAT(131),
  [371] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_argument_repeat1, 2), SHIFT_REPEAT(148),
  [374] = {.entry = {.count = 1, .reusable = false}}, SHIFT(200),
  [376] = {.entry = {.count = 1, .reusable = false}}, SHIFT(59),
  [378] = {.entry = {.count = 1, .reusable = false}}, SHIFT(196),
  [380] = {.entry = {.count = 1, .reusable = false}}, SHIFT(185),
  [382] = {.entry = {.count = 1, .reusable = false}}, SHIFT(194),
  [384] = {.entry = {.count = 1, .reusable = false}}, SHIFT(96),
  [386] = {.entry = {.count = 1, .reusable = false}}, SHIFT(167),
  [388] = {.entry = {.count = 1, .reusable = false}}, SHIFT(201),
  [390] = {.entry = {.count = 1, .reusable = false}}, SHIFT(67),
  [392] = {.entry = {.count = 1, .reusable = false}}, SHIFT(165),
  [394] = {.entry = {.count = 1, .reusable = false}}, SHIFT(191),
  [396] = {.entry = {.count = 1, .reusable = false}}, SHIFT(46),
  [398] = {.entry = {.count = 1, .reusable = false}}, SHIFT(162),
  [400] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_argument, 1),
  [402] = {.entry = {.count = 1, .reusable = false}}, SHIFT(131),
  [404] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__quoted_atom, 3),
  [406] = {.entry = {.count = 1, .reusable = true}}, SHIFT(209),
  [408] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__quoted_atom, 2),
  [410] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_module, 1),
  [412] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function, 1),
  [414] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type, 1),
  [416] = {.entry = {.count = 1, .reusable = false}}, SHIFT(183),
  [418] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__author_line, 2),
  [420] = {.entry = {.count = 1, .reusable = false}}, SHIFT(150),
  [422] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_macro_escape, 1),
  [424] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__author_line, 1),
  [426] = {.entry = {.count = 1, .reusable = false}}, SHIFT(147),
  [428] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym__author_line_repeat1, 2),
  [430] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__author_line_repeat1, 2), SHIFT_REPEAT(150),
  [433] = {.entry = {.count = 1, .reusable = false}}, SHIFT(145),
  [435] = {.entry = {.count = 1, .reusable = false}}, SHIFT(155),
  [437] = {.entry = {.count = 1, .reusable = true}}, SHIFT(205),
  [439] = {.entry = {.count = 1, .reusable = false}}, SHIFT(205),
  [441] = {.entry = {.count = 1, .reusable = false}}, SHIFT(111),
  [443] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression, 1),
  [445] = {.entry = {.count = 1, .reusable = true}}, SHIFT(144),
  [447] = {.entry = {.count = 1, .reusable = false}}, SHIFT(113),
  [449] = {.entry = {.count = 1, .reusable = false}}, SHIFT(143),
  [451] = {.entry = {.count = 1, .reusable = false}}, SHIFT(158),
  [453] = {.entry = {.count = 1, .reusable = false}}, SHIFT(114),
  [455] = {.entry = {.count = 1, .reusable = false}}, SHIFT(112),
  [457] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym__quoted_atom_repeat1, 2),
  [459] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__quoted_atom_repeat1, 2), SHIFT_REPEAT(158),
  [462] = {.entry = {.count = 1, .reusable = false}}, SHIFT(202),
  [464] = {.entry = {.count = 1, .reusable = false}}, SHIFT(68),
  [466] = {.entry = {.count = 1, .reusable = true}}, SHIFT(171),
  [468] = {.entry = {.count = 1, .reusable = false}}, SHIFT(116),
  [470] = {.entry = {.count = 1, .reusable = true}}, SHIFT(168),
  [472] = {.entry = {.count = 1, .reusable = false}}, SHIFT(55),
  [474] = {.entry = {.count = 1, .reusable = true}}, SHIFT(185),
  [476] = {.entry = {.count = 1, .reusable = false}}, SHIFT(170),
  [478] = {.entry = {.count = 1, .reusable = false}}, SHIFT(57),
  [480] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression, 5),
  [482] = {.entry = {.count = 1, .reusable = false}}, SHIFT(181),
  [484] = {.entry = {.count = 1, .reusable = false}}, SHIFT(118),
  [486] = {.entry = {.count = 1, .reusable = true}}, SHIFT(177),
  [488] = {.entry = {.count = 1, .reusable = false}}, SHIFT(76),
  [490] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression, 3),
  [492] = {.entry = {.count = 1, .reusable = false}}, SHIFT(176),
  [494] = {.entry = {.count = 1, .reusable = false}}, SHIFT(79),
  [496] = {.entry = {.count = 1, .reusable = false}}, SHIFT(115),
  [498] = {.entry = {.count = 1, .reusable = false}}, SHIFT(174),
  [500] = {.entry = {.count = 1, .reusable = false}}, SHIFT(128),
  [502] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_quote_content_repeat1, 2),
  [504] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_quote_content_repeat1, 2), SHIFT_REPEAT(173),
  [507] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__triple_inline_quote_repeat1, 2), SHIFT_REPEAT(174),
  [510] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym__triple_inline_quote_repeat1, 2),
  [512] = {.entry = {.count = 1, .reusable = false}}, SHIFT(122),
  [514] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__double_inline_quote_repeat1, 2), SHIFT_REPEAT(176),
  [517] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym__double_inline_quote_repeat1, 2),
  [519] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_xhtml_tag_repeat1, 2), SHIFT_REPEAT(177),
  [522] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_xhtml_tag_repeat1, 2),
  [524] = {.entry = {.count = 1, .reusable = false}}, SHIFT(109),
  [526] = {.entry = {.count = 1, .reusable = false}}, SHIFT(175),
  [528] = {.entry = {.count = 1, .reusable = false}}, SHIFT(126),
  [530] = {.entry = {.count = 1, .reusable = true}}, SHIFT(178),
  [532] = {.entry = {.count = 1, .reusable = false}}, SHIFT(125),
  [534] = {.entry = {.count = 1, .reusable = false}}, SHIFT(123),
  [536] = {.entry = {.count = 1, .reusable = false}}, SHIFT(120),
  [538] = {.entry = {.count = 1, .reusable = true}}, SHIFT(190),
  [540] = {.entry = {.count = 1, .reusable = false}}, SHIFT(264),
  [542] = {.entry = {.count = 1, .reusable = false}}, SHIFT(192),
  [544] = {.entry = {.count = 1, .reusable = false}}, SHIFT(72),
  [546] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_quote_content, 1),
  [548] = {.entry = {.count = 1, .reusable = false}}, SHIFT(173),
  [550] = {.entry = {.count = 1, .reusable = false}}, SHIFT(90),
  [552] = {.entry = {.count = 1, .reusable = false}}, SHIFT(172),
  [554] = {.entry = {.count = 1, .reusable = false}}, SHIFT(127),
  [556] = {.entry = {.count = 1, .reusable = false}}, SHIFT(182),
  [558] = {.entry = {.count = 1, .reusable = false}}, SHIFT(108),
  [560] = {.entry = {.count = 1, .reusable = true}}, SHIFT(186),
  [562] = {.entry = {.count = 1, .reusable = false}}, SHIFT(98),
  [564] = {.entry = {.count = 1, .reusable = false}}, SHIFT(265),
  [566] = {.entry = {.count = 1, .reusable = false}}, SHIFT(89),
  [568] = {.entry = {.count = 1, .reusable = false}}, SHIFT(87),
  [570] = {.entry = {.count = 1, .reusable = false}}, SHIFT(37),
  [572] = {.entry = {.count = 1, .reusable = false}}, SHIFT(85),
  [574] = {.entry = {.count = 1, .reusable = false}}, SHIFT(40),
  [576] = {.entry = {.count = 1, .reusable = false}}, SHIFT(193),
  [578] = {.entry = {.count = 1, .reusable = false}}, SHIFT(47),
  [580] = {.entry = {.count = 1, .reusable = true}}, SHIFT(195),
  [582] = {.entry = {.count = 1, .reusable = false}}, SHIFT(48),
  [584] = {.entry = {.count = 1, .reusable = true}}, SHIFT(203),
  [586] = {.entry = {.count = 1, .reusable = false}}, SHIFT(69),
  [588] = {.entry = {.count = 1, .reusable = false}}, SHIFT(83),
  [590] = {.entry = {.count = 1, .reusable = false}}, SHIFT(58),
  [592] = {.entry = {.count = 1, .reusable = false}}, SHIFT(61),
  [594] = {.entry = {.count = 1, .reusable = false}}, SHIFT(63),
  [596] = {.entry = {.count = 1, .reusable = true}}, SHIFT(129),
  [598] = {.entry = {.count = 1, .reusable = false}}, SHIFT(94),
  [600] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_tag, 1),
  [602] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [604] = {.entry = {.count = 1, .reusable = true}}, SHIFT(139),
  [606] = {.entry = {.count = 1, .reusable = false}}, SHIFT(66),
  [608] = {.entry = {.count = 1, .reusable = true}}, SHIFT(130),
  [610] = {.entry = {.count = 1, .reusable = false}}, SHIFT(73),
  [612] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [614] = {.entry = {.count = 1, .reusable = true}}, SHIFT(133),
  [616] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [618] = {.entry = {.count = 1, .reusable = true}}, SHIFT(134),
  [620] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [622] = {.entry = {.count = 1, .reusable = true}}, SHIFT(141),
  [624] = {.entry = {.count = 1, .reusable = true}}, SHIFT(135),
  [626] = {.entry = {.count = 1, .reusable = false}}, SHIFT(45),
  [628] = {.entry = {.count = 1, .reusable = true}}, SHIFT(107),
  [630] = {.entry = {.count = 1, .reusable = true}}, SHIFT(140),
  [632] = {.entry = {.count = 1, .reusable = true}}, SHIFT(169),
  [634] = {.entry = {.count = 1, .reusable = true}}, SHIFT(250),
  [636] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [638] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [640] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [642] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [644] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [646] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [648] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [650] = {.entry = {.count = 1, .reusable = true}}, SHIFT(86),
  [652] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [654] = {.entry = {.count = 1, .reusable = true}}, SHIFT(88),
  [656] = {.entry = {.count = 1, .reusable = true}}, SHIFT(103),
  [658] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [660] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [662] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [664] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [666] = {.entry = {.count = 1, .reusable = true}}, SHIFT(119),
  [668] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__author_line, 3, .production_id = 3),
  [670] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [672] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section, 3, .production_id = 4),
  [674] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [676] = {.entry = {.count = 1, .reusable = true}}, SHIFT(121),
  [678] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [680] = {.entry = {.count = 1, .reusable = true}}, SHIFT(248),
  [682] = {.entry = {.count = 1, .reusable = true}}, SHIFT(258),
  [684] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [686] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [688] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [690] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [692] = {.entry = {.count = 1, .reusable = true}}, SHIFT(226),
  [694] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [696] = {.entry = {.count = 1, .reusable = true}}, SHIFT(164),
  [698] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [700] = {.entry = {.count = 1, .reusable = true}}, SHIFT(82),
  [702] = {.entry = {.count = 1, .reusable = true}}, SHIFT(215),
  [704] = {.entry = {.count = 1, .reusable = true}}, SHIFT(234),
  [706] = {.entry = {.count = 1, .reusable = true}}, SHIFT(261),
  [708] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__see_line, 2),
  [710] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [712] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__author_line, 2, .production_id = 1),
  [714] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__separator, 2),
  [716] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [718] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [720] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [722] = {.entry = {.count = 1, .reusable = true}}, SHIFT(223),
  [724] = {.entry = {.count = 1, .reusable = true}}, SHIFT(244),
  [726] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_xhtml_tag, 2),
  [728] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_xhtml_tag, 3),
  [730] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [732] = {.entry = {.count = 1, .reusable = true}}, SHIFT(232),
  [734] = {.entry = {.count = 1, .reusable = true}}, SHIFT(238),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_edoc(void) {
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
