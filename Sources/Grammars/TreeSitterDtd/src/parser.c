#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 255
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 129
#define ALIAS_COUNT 6
#define TOKEN_COUNT 76
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 10
#define PRODUCTION_ID_COUNT 10

enum {
  aux_sym_document_token1 = 1,
  aux_sym__name_char_token1 = 2,
  anon_sym_DOT = 3,
  anon_sym_DASH = 4,
  anon_sym_COLON = 5,
  aux_sym__name_char_token2 = 6,
  aux_sym__name_char_token3 = 7,
  aux_sym__name_char_token4 = 8,
  aux_sym__name_char_token5 = 9,
  aux_sym__name_char_token6 = 10,
  aux_sym__name_char_token7 = 11,
  aux_sym__name_char_token8 = 12,
  aux_sym__name_char_token9 = 13,
  aux_sym__name_char_token10 = 14,
  aux_sym__name_char_token11 = 15,
  aux_sym__name_char_token12 = 16,
  aux_sym__name_char_token13 = 17,
  aux_sym__name_char_token14 = 18,
  aux_sym__name_char_token15 = 19,
  anon_sym__ = 20,
  aux_sym_names_token1 = 21,
  anon_sym_DQUOTE = 22,
  anon_sym_SQUOTE = 23,
  aux_sym_attribute_value_token1 = 24,
  aux_sym_attribute_value_token2 = 25,
  aux_sym_system_literal_token1 = 26,
  aux_sym_system_literal_token2 = 27,
  sym_pubid_char = 28,
  anon_sym_LT_BANG_DASH_DASH = 29,
  aux_sym_comment_token1 = 30,
  anon_sym_DASH_DASH_GT = 31,
  anon_sym_LT_QMARK = 32,
  aux_sym_processing_instructions_token1 = 33,
  anon_sym_QMARK_GT = 34,
  anon_sym_EQ = 35,
  anon_sym_LT_SLASH = 36,
  anon_sym_GT = 37,
  anon_sym_LT_BANG = 38,
  anon_sym_ELEMENT = 39,
  anon_sym_EMPTY = 40,
  anon_sym_ANY = 41,
  anon_sym_QMARK = 42,
  anon_sym_STAR = 43,
  anon_sym_PLUS = 44,
  anon_sym_LPAREN = 45,
  anon_sym_PIPE = 46,
  anon_sym_RPAREN = 47,
  anon_sym_COMMA = 48,
  anon_sym_POUNDPCDATA = 49,
  anon_sym_RPAREN_STAR = 50,
  anon_sym_ATTLIST = 51,
  sym__string_type = 52,
  anon_sym_ID = 53,
  anon_sym_IDREF = 54,
  anon_sym_IDREFS = 55,
  anon_sym_ENTITY = 56,
  anon_sym_ENTITIES = 57,
  anon_sym_NMTOKEN = 58,
  anon_sym_NMTOKENS = 59,
  anon_sym_NOTATION = 60,
  anon_sym_POUNDREQUIRED = 61,
  anon_sym_POUNDIMPLIED = 62,
  anon_sym_POUNDFIXED = 63,
  anon_sym_AMP_POUND = 64,
  aux_sym_char_ref_token1 = 65,
  anon_sym_SEMI = 66,
  anon_sym_AMP_POUNDx = 67,
  aux_sym_char_ref_token2 = 68,
  anon_sym_AMP = 69,
  anon_sym_PERCENT = 70,
  anon_sym_SYSTEM = 71,
  anon_sym_PUBLIC = 72,
  anon_sym_NDATA = 73,
  aux_sym__enc_name_token1 = 74,
  aux_sym__enc_name_token2 = 75,
  sym_document = 76,
  sym__name_char = 77,
  sym__name = 78,
  sym_nm_token = 79,
  sym_entity_value = 80,
  sym_attribute_value = 81,
  sym_system_literal = 82,
  sym_pubid_literal = 83,
  sym_comment = 84,
  sym_processing_instructions = 85,
  sym_pi_target = 86,
  sym__markup_decl = 87,
  sym_element_decl = 88,
  sym_content_spec = 89,
  sym_children = 90,
  sym_cp = 91,
  sym_element_choice = 92,
  sym_element_seq = 93,
  sym_mixed = 94,
  sym_attlist_decl = 95,
  sym_attribute_def = 96,
  sym_attribute_type = 97,
  sym__tokenized_type = 98,
  sym__enumerated_type = 99,
  sym_notation_type = 100,
  sym_enumeration = 101,
  sym_default_decl = 102,
  sym_char_ref = 103,
  sym_reference = 104,
  sym_entity_ref = 105,
  sym_pe_reference = 106,
  sym_entity_decl = 107,
  sym_ge_decl = 108,
  sym_pe_decl = 109,
  sym_entity_def = 110,
  sym_pe_def = 111,
  sym_external_id = 112,
  sym_ndata_decl = 113,
  sym_notation_decl = 114,
  sym_public_id = 115,
  aux_sym_document_repeat1 = 116,
  aux_sym__name_repeat1 = 117,
  aux_sym_attribute_value_repeat1 = 118,
  aux_sym_attribute_value_repeat2 = 119,
  aux_sym_pubid_literal_repeat1 = 120,
  aux_sym_pubid_literal_repeat2 = 121,
  aux_sym_comment_repeat1 = 122,
  aux_sym_element_choice_repeat1 = 123,
  aux_sym_element_seq_repeat1 = 124,
  aux_sym_mixed_repeat1 = 125,
  aux_sym_attlist_decl_repeat1 = 126,
  aux_sym_notation_type_repeat1 = 127,
  aux_sym_enumeration_repeat1 = 128,
  alias_sym_attlist_name = 129,
  alias_sym_attribute_name = 130,
  alias_sym_element_name = 131,
  alias_sym_ndata_name = 132,
  alias_sym_notation_name = 133,
  alias_sym_notation_type_name = 134,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [aux_sym_document_token1] = "document_token1",
  [aux_sym__name_char_token1] = "_name_char_token1",
  [anon_sym_DOT] = ".",
  [anon_sym_DASH] = "-",
  [anon_sym_COLON] = ":",
  [aux_sym__name_char_token2] = "_name_char_token2",
  [aux_sym__name_char_token3] = "_name_char_token3",
  [aux_sym__name_char_token4] = "_name_char_token4",
  [aux_sym__name_char_token5] = "_name_char_token5",
  [aux_sym__name_char_token6] = "_name_char_token6",
  [aux_sym__name_char_token7] = "_name_char_token7",
  [aux_sym__name_char_token8] = "_name_char_token8",
  [aux_sym__name_char_token9] = "_name_char_token9",
  [aux_sym__name_char_token10] = "_name_char_token10",
  [aux_sym__name_char_token11] = "_name_char_token11",
  [aux_sym__name_char_token12] = "_name_char_token12",
  [aux_sym__name_char_token13] = "_name_char_token13",
  [aux_sym__name_char_token14] = "_name_char_token14",
  [aux_sym__name_char_token15] = "_name_char_token15",
  [anon_sym__] = "_",
  [aux_sym_names_token1] = "names_token1",
  [anon_sym_DQUOTE] = "\"",
  [anon_sym_SQUOTE] = "'",
  [aux_sym_attribute_value_token1] = "attribute_value_token1",
  [aux_sym_attribute_value_token2] = "attribute_value_token2",
  [aux_sym_system_literal_token1] = "system_literal_token1",
  [aux_sym_system_literal_token2] = "system_literal_token2",
  [sym_pubid_char] = "pubid_char",
  [anon_sym_LT_BANG_DASH_DASH] = "<!--",
  [aux_sym_comment_token1] = "comment_token1",
  [anon_sym_DASH_DASH_GT] = "-->",
  [anon_sym_LT_QMARK] = "<\?",
  [aux_sym_processing_instructions_token1] = "processing_instructions_token1",
  [anon_sym_QMARK_GT] = "\?>",
  [anon_sym_EQ] = "=",
  [anon_sym_LT_SLASH] = "</",
  [anon_sym_GT] = ">",
  [anon_sym_LT_BANG] = "<!",
  [anon_sym_ELEMENT] = "ELEMENT",
  [anon_sym_EMPTY] = "EMPTY",
  [anon_sym_ANY] = "ANY",
  [anon_sym_QMARK] = "\?",
  [anon_sym_STAR] = "*",
  [anon_sym_PLUS] = "+",
  [anon_sym_LPAREN] = "(",
  [anon_sym_PIPE] = "|",
  [anon_sym_RPAREN] = ")",
  [anon_sym_COMMA] = ",",
  [anon_sym_POUNDPCDATA] = "#PCDATA",
  [anon_sym_RPAREN_STAR] = ")*",
  [anon_sym_ATTLIST] = "ATTLIST",
  [sym__string_type] = "_string_type",
  [anon_sym_ID] = "ID",
  [anon_sym_IDREF] = "IDREF",
  [anon_sym_IDREFS] = "IDREFS",
  [anon_sym_ENTITY] = "ENTITY",
  [anon_sym_ENTITIES] = "ENTITIES",
  [anon_sym_NMTOKEN] = "NMTOKEN",
  [anon_sym_NMTOKENS] = "NMTOKENS",
  [anon_sym_NOTATION] = "NOTATION",
  [anon_sym_POUNDREQUIRED] = "#REQUIRED",
  [anon_sym_POUNDIMPLIED] = "#IMPLIED",
  [anon_sym_POUNDFIXED] = "#FIXED",
  [anon_sym_AMP_POUND] = "&#",
  [aux_sym_char_ref_token1] = "char_ref_token1",
  [anon_sym_SEMI] = ";",
  [anon_sym_AMP_POUNDx] = "&#x",
  [aux_sym_char_ref_token2] = "char_ref_token2",
  [anon_sym_AMP] = "&",
  [anon_sym_PERCENT] = "%",
  [anon_sym_SYSTEM] = "SYSTEM",
  [anon_sym_PUBLIC] = "PUBLIC",
  [anon_sym_NDATA] = "NDATA",
  [aux_sym__enc_name_token1] = "_enc_name_token1",
  [aux_sym__enc_name_token2] = "_enc_name_token2",
  [sym_document] = "document",
  [sym__name_char] = "_name_char",
  [sym__name] = "_name",
  [sym_nm_token] = "nm_token",
  [sym_entity_value] = "entity_value",
  [sym_attribute_value] = "attribute_value",
  [sym_system_literal] = "system_literal",
  [sym_pubid_literal] = "pubid_literal",
  [sym_comment] = "comment",
  [sym_processing_instructions] = "processing_instructions",
  [sym_pi_target] = "pi_target",
  [sym__markup_decl] = "_markup_decl",
  [sym_element_decl] = "element_decl",
  [sym_content_spec] = "content_spec",
  [sym_children] = "children",
  [sym_cp] = "cp",
  [sym_element_choice] = "element_choice",
  [sym_element_seq] = "element_seq",
  [sym_mixed] = "mixed",
  [sym_attlist_decl] = "attlist_decl",
  [sym_attribute_def] = "attribute_def",
  [sym_attribute_type] = "attribute_type",
  [sym__tokenized_type] = "_tokenized_type",
  [sym__enumerated_type] = "_enumerated_type",
  [sym_notation_type] = "notation_type",
  [sym_enumeration] = "enumeration",
  [sym_default_decl] = "default_decl",
  [sym_char_ref] = "char_ref",
  [sym_reference] = "reference",
  [sym_entity_ref] = "entity_ref",
  [sym_pe_reference] = "pe_reference",
  [sym_entity_decl] = "entity_decl",
  [sym_ge_decl] = "ge_decl",
  [sym_pe_decl] = "pe_decl",
  [sym_entity_def] = "entity_def",
  [sym_pe_def] = "pe_def",
  [sym_external_id] = "external_id",
  [sym_ndata_decl] = "ndata_decl",
  [sym_notation_decl] = "notation_decl",
  [sym_public_id] = "public_id",
  [aux_sym_document_repeat1] = "document_repeat1",
  [aux_sym__name_repeat1] = "_name_repeat1",
  [aux_sym_attribute_value_repeat1] = "attribute_value_repeat1",
  [aux_sym_attribute_value_repeat2] = "attribute_value_repeat2",
  [aux_sym_pubid_literal_repeat1] = "pubid_literal_repeat1",
  [aux_sym_pubid_literal_repeat2] = "pubid_literal_repeat2",
  [aux_sym_comment_repeat1] = "comment_repeat1",
  [aux_sym_element_choice_repeat1] = "element_choice_repeat1",
  [aux_sym_element_seq_repeat1] = "element_seq_repeat1",
  [aux_sym_mixed_repeat1] = "mixed_repeat1",
  [aux_sym_attlist_decl_repeat1] = "attlist_decl_repeat1",
  [aux_sym_notation_type_repeat1] = "notation_type_repeat1",
  [aux_sym_enumeration_repeat1] = "enumeration_repeat1",
  [alias_sym_attlist_name] = "attlist_name",
  [alias_sym_attribute_name] = "attribute_name",
  [alias_sym_element_name] = "element_name",
  [alias_sym_ndata_name] = "ndata_name",
  [alias_sym_notation_name] = "notation_name",
  [alias_sym_notation_type_name] = "notation_type_name",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [aux_sym_document_token1] = aux_sym_document_token1,
  [aux_sym__name_char_token1] = aux_sym__name_char_token1,
  [anon_sym_DOT] = anon_sym_DOT,
  [anon_sym_DASH] = anon_sym_DASH,
  [anon_sym_COLON] = anon_sym_COLON,
  [aux_sym__name_char_token2] = aux_sym__name_char_token2,
  [aux_sym__name_char_token3] = aux_sym__name_char_token3,
  [aux_sym__name_char_token4] = aux_sym__name_char_token4,
  [aux_sym__name_char_token5] = aux_sym__name_char_token5,
  [aux_sym__name_char_token6] = aux_sym__name_char_token6,
  [aux_sym__name_char_token7] = aux_sym__name_char_token7,
  [aux_sym__name_char_token8] = aux_sym__name_char_token8,
  [aux_sym__name_char_token9] = aux_sym__name_char_token9,
  [aux_sym__name_char_token10] = aux_sym__name_char_token10,
  [aux_sym__name_char_token11] = aux_sym__name_char_token11,
  [aux_sym__name_char_token12] = aux_sym__name_char_token12,
  [aux_sym__name_char_token13] = aux_sym__name_char_token13,
  [aux_sym__name_char_token14] = aux_sym__name_char_token14,
  [aux_sym__name_char_token15] = aux_sym__name_char_token15,
  [anon_sym__] = anon_sym__,
  [aux_sym_names_token1] = aux_sym_names_token1,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [anon_sym_SQUOTE] = anon_sym_SQUOTE,
  [aux_sym_attribute_value_token1] = aux_sym_attribute_value_token1,
  [aux_sym_attribute_value_token2] = aux_sym_attribute_value_token2,
  [aux_sym_system_literal_token1] = aux_sym_system_literal_token1,
  [aux_sym_system_literal_token2] = aux_sym_system_literal_token2,
  [sym_pubid_char] = sym_pubid_char,
  [anon_sym_LT_BANG_DASH_DASH] = anon_sym_LT_BANG_DASH_DASH,
  [aux_sym_comment_token1] = aux_sym_comment_token1,
  [anon_sym_DASH_DASH_GT] = anon_sym_DASH_DASH_GT,
  [anon_sym_LT_QMARK] = anon_sym_LT_QMARK,
  [aux_sym_processing_instructions_token1] = aux_sym_processing_instructions_token1,
  [anon_sym_QMARK_GT] = anon_sym_QMARK_GT,
  [anon_sym_EQ] = anon_sym_EQ,
  [anon_sym_LT_SLASH] = anon_sym_LT_SLASH,
  [anon_sym_GT] = anon_sym_GT,
  [anon_sym_LT_BANG] = anon_sym_LT_BANG,
  [anon_sym_ELEMENT] = anon_sym_ELEMENT,
  [anon_sym_EMPTY] = anon_sym_EMPTY,
  [anon_sym_ANY] = anon_sym_ANY,
  [anon_sym_QMARK] = anon_sym_QMARK,
  [anon_sym_STAR] = anon_sym_STAR,
  [anon_sym_PLUS] = anon_sym_PLUS,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_PIPE] = anon_sym_PIPE,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_POUNDPCDATA] = anon_sym_POUNDPCDATA,
  [anon_sym_RPAREN_STAR] = anon_sym_RPAREN_STAR,
  [anon_sym_ATTLIST] = anon_sym_ATTLIST,
  [sym__string_type] = sym__string_type,
  [anon_sym_ID] = anon_sym_ID,
  [anon_sym_IDREF] = anon_sym_IDREF,
  [anon_sym_IDREFS] = anon_sym_IDREFS,
  [anon_sym_ENTITY] = anon_sym_ENTITY,
  [anon_sym_ENTITIES] = anon_sym_ENTITIES,
  [anon_sym_NMTOKEN] = anon_sym_NMTOKEN,
  [anon_sym_NMTOKENS] = anon_sym_NMTOKENS,
  [anon_sym_NOTATION] = anon_sym_NOTATION,
  [anon_sym_POUNDREQUIRED] = anon_sym_POUNDREQUIRED,
  [anon_sym_POUNDIMPLIED] = anon_sym_POUNDIMPLIED,
  [anon_sym_POUNDFIXED] = anon_sym_POUNDFIXED,
  [anon_sym_AMP_POUND] = anon_sym_AMP_POUND,
  [aux_sym_char_ref_token1] = aux_sym_char_ref_token1,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_AMP_POUNDx] = anon_sym_AMP_POUNDx,
  [aux_sym_char_ref_token2] = aux_sym_char_ref_token2,
  [anon_sym_AMP] = anon_sym_AMP,
  [anon_sym_PERCENT] = anon_sym_PERCENT,
  [anon_sym_SYSTEM] = anon_sym_SYSTEM,
  [anon_sym_PUBLIC] = anon_sym_PUBLIC,
  [anon_sym_NDATA] = anon_sym_NDATA,
  [aux_sym__enc_name_token1] = aux_sym__enc_name_token1,
  [aux_sym__enc_name_token2] = aux_sym__enc_name_token2,
  [sym_document] = sym_document,
  [sym__name_char] = sym__name_char,
  [sym__name] = sym__name,
  [sym_nm_token] = sym_nm_token,
  [sym_entity_value] = sym_entity_value,
  [sym_attribute_value] = sym_attribute_value,
  [sym_system_literal] = sym_system_literal,
  [sym_pubid_literal] = sym_pubid_literal,
  [sym_comment] = sym_comment,
  [sym_processing_instructions] = sym_processing_instructions,
  [sym_pi_target] = sym_pi_target,
  [sym__markup_decl] = sym__markup_decl,
  [sym_element_decl] = sym_element_decl,
  [sym_content_spec] = sym_content_spec,
  [sym_children] = sym_children,
  [sym_cp] = sym_cp,
  [sym_element_choice] = sym_element_choice,
  [sym_element_seq] = sym_element_seq,
  [sym_mixed] = sym_mixed,
  [sym_attlist_decl] = sym_attlist_decl,
  [sym_attribute_def] = sym_attribute_def,
  [sym_attribute_type] = sym_attribute_type,
  [sym__tokenized_type] = sym__tokenized_type,
  [sym__enumerated_type] = sym__enumerated_type,
  [sym_notation_type] = sym_notation_type,
  [sym_enumeration] = sym_enumeration,
  [sym_default_decl] = sym_default_decl,
  [sym_char_ref] = sym_char_ref,
  [sym_reference] = sym_reference,
  [sym_entity_ref] = sym_entity_ref,
  [sym_pe_reference] = sym_pe_reference,
  [sym_entity_decl] = sym_entity_decl,
  [sym_ge_decl] = sym_ge_decl,
  [sym_pe_decl] = sym_pe_decl,
  [sym_entity_def] = sym_entity_def,
  [sym_pe_def] = sym_pe_def,
  [sym_external_id] = sym_external_id,
  [sym_ndata_decl] = sym_ndata_decl,
  [sym_notation_decl] = sym_notation_decl,
  [sym_public_id] = sym_public_id,
  [aux_sym_document_repeat1] = aux_sym_document_repeat1,
  [aux_sym__name_repeat1] = aux_sym__name_repeat1,
  [aux_sym_attribute_value_repeat1] = aux_sym_attribute_value_repeat1,
  [aux_sym_attribute_value_repeat2] = aux_sym_attribute_value_repeat2,
  [aux_sym_pubid_literal_repeat1] = aux_sym_pubid_literal_repeat1,
  [aux_sym_pubid_literal_repeat2] = aux_sym_pubid_literal_repeat2,
  [aux_sym_comment_repeat1] = aux_sym_comment_repeat1,
  [aux_sym_element_choice_repeat1] = aux_sym_element_choice_repeat1,
  [aux_sym_element_seq_repeat1] = aux_sym_element_seq_repeat1,
  [aux_sym_mixed_repeat1] = aux_sym_mixed_repeat1,
  [aux_sym_attlist_decl_repeat1] = aux_sym_attlist_decl_repeat1,
  [aux_sym_notation_type_repeat1] = aux_sym_notation_type_repeat1,
  [aux_sym_enumeration_repeat1] = aux_sym_enumeration_repeat1,
  [alias_sym_attlist_name] = alias_sym_attlist_name,
  [alias_sym_attribute_name] = alias_sym_attribute_name,
  [alias_sym_element_name] = alias_sym_element_name,
  [alias_sym_ndata_name] = alias_sym_ndata_name,
  [alias_sym_notation_name] = alias_sym_notation_name,
  [alias_sym_notation_type_name] = alias_sym_notation_type_name,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [aux_sym_document_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__name_char_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_DOT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [aux_sym__name_char_token2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__name_char_token3] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__name_char_token4] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__name_char_token5] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__name_char_token6] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__name_char_token7] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__name_char_token8] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__name_char_token9] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__name_char_token10] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__name_char_token11] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__name_char_token12] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__name_char_token13] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__name_char_token14] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__name_char_token15] = {
    .visible = false,
    .named = false,
  },
  [anon_sym__] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_names_token1] = {
    .visible = false,
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
  [aux_sym_attribute_value_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_attribute_value_token2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_system_literal_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_system_literal_token2] = {
    .visible = false,
    .named = false,
  },
  [sym_pubid_char] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LT_BANG_DASH_DASH] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_comment_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_DASH_DASH_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT_QMARK] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_processing_instructions_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_QMARK_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT_SLASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT_BANG] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ELEMENT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EMPTY] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ANY] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_QMARK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_STAR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PLUS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PIPE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_POUNDPCDATA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN_STAR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ATTLIST] = {
    .visible = true,
    .named = false,
  },
  [sym__string_type] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_ID] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_IDREF] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_IDREFS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ENTITY] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ENTITIES] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_NMTOKEN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_NMTOKENS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_NOTATION] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_POUNDREQUIRED] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_POUNDIMPLIED] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_POUNDFIXED] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_AMP_POUND] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_char_ref_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_SEMI] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_AMP_POUNDx] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_char_ref_token2] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_AMP] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PERCENT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SYSTEM] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PUBLIC] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_NDATA] = {
    .visible = true,
    .named = false,
  },
  [aux_sym__enc_name_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__enc_name_token2] = {
    .visible = false,
    .named = false,
  },
  [sym_document] = {
    .visible = true,
    .named = true,
  },
  [sym__name_char] = {
    .visible = false,
    .named = true,
  },
  [sym__name] = {
    .visible = false,
    .named = true,
  },
  [sym_nm_token] = {
    .visible = true,
    .named = true,
  },
  [sym_entity_value] = {
    .visible = true,
    .named = true,
  },
  [sym_attribute_value] = {
    .visible = true,
    .named = true,
  },
  [sym_system_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_pubid_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_processing_instructions] = {
    .visible = true,
    .named = true,
  },
  [sym_pi_target] = {
    .visible = true,
    .named = true,
  },
  [sym__markup_decl] = {
    .visible = false,
    .named = true,
  },
  [sym_element_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_content_spec] = {
    .visible = true,
    .named = true,
  },
  [sym_children] = {
    .visible = true,
    .named = true,
  },
  [sym_cp] = {
    .visible = true,
    .named = true,
  },
  [sym_element_choice] = {
    .visible = true,
    .named = true,
  },
  [sym_element_seq] = {
    .visible = true,
    .named = true,
  },
  [sym_mixed] = {
    .visible = true,
    .named = true,
  },
  [sym_attlist_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_attribute_def] = {
    .visible = true,
    .named = true,
  },
  [sym_attribute_type] = {
    .visible = true,
    .named = true,
  },
  [sym__tokenized_type] = {
    .visible = false,
    .named = true,
  },
  [sym__enumerated_type] = {
    .visible = false,
    .named = true,
  },
  [sym_notation_type] = {
    .visible = true,
    .named = true,
  },
  [sym_enumeration] = {
    .visible = true,
    .named = true,
  },
  [sym_default_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_char_ref] = {
    .visible = true,
    .named = true,
  },
  [sym_reference] = {
    .visible = true,
    .named = true,
  },
  [sym_entity_ref] = {
    .visible = true,
    .named = true,
  },
  [sym_pe_reference] = {
    .visible = true,
    .named = true,
  },
  [sym_entity_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_ge_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_pe_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_entity_def] = {
    .visible = true,
    .named = true,
  },
  [sym_pe_def] = {
    .visible = true,
    .named = true,
  },
  [sym_external_id] = {
    .visible = true,
    .named = true,
  },
  [sym_ndata_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_notation_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_public_id] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_document_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__name_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_attribute_value_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_attribute_value_repeat2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_pubid_literal_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_pubid_literal_repeat2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_comment_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_element_choice_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_element_seq_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_mixed_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_attlist_decl_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_notation_type_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_enumeration_repeat1] = {
    .visible = false,
    .named = false,
  },
  [alias_sym_attlist_name] = {
    .visible = true,
    .named = true,
  },
  [alias_sym_attribute_name] = {
    .visible = true,
    .named = true,
  },
  [alias_sym_element_name] = {
    .visible = true,
    .named = true,
  },
  [alias_sym_ndata_name] = {
    .visible = true,
    .named = true,
  },
  [alias_sym_notation_name] = {
    .visible = true,
    .named = true,
  },
  [alias_sym_notation_type_name] = {
    .visible = true,
    .named = true,
  },
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
  [1] = {
    [3] = alias_sym_attlist_name,
  },
  [2] = {
    [3] = alias_sym_element_name,
  },
  [3] = {
    [3] = alias_sym_notation_name,
  },
  [4] = {
    [1] = alias_sym_attribute_name,
  },
  [5] = {
    [3] = alias_sym_ndata_name,
  },
  [6] = {
    [3] = alias_sym_notation_type_name,
  },
  [7] = {
    [4] = alias_sym_notation_type_name,
  },
  [8] = {
    [1] = alias_sym_notation_type_name,
  },
  [9] = {
    [2] = alias_sym_notation_type_name,
  },
};

static const uint16_t ts_non_terminal_alias_map[] = {
  sym__name, 7,
    sym__name,
    alias_sym_attlist_name,
    alias_sym_attribute_name,
    alias_sym_element_name,
    alias_sym_ndata_name,
    alias_sym_notation_name,
    alias_sym_notation_type_name,
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 4,
  [6] = 3,
  [7] = 2,
  [8] = 4,
  [9] = 2,
  [10] = 3,
  [11] = 2,
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
  [73] = 70,
  [74] = 74,
  [75] = 75,
  [76] = 76,
  [77] = 77,
  [78] = 76,
  [79] = 75,
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
  [128] = 119,
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
  [174] = 174,
  [175] = 175,
  [176] = 176,
  [177] = 177,
  [178] = 178,
  [179] = 179,
  [180] = 180,
  [181] = 181,
  [182] = 182,
  [183] = 183,
  [184] = 184,
  [185] = 185,
  [186] = 186,
  [187] = 187,
  [188] = 188,
  [189] = 189,
  [190] = 190,
  [191] = 191,
  [192] = 192,
  [193] = 193,
  [194] = 194,
  [195] = 195,
  [196] = 196,
  [197] = 197,
  [198] = 198,
  [199] = 199,
  [200] = 200,
  [201] = 201,
  [202] = 202,
  [203] = 203,
  [204] = 204,
  [205] = 205,
  [206] = 206,
  [207] = 207,
  [208] = 208,
  [209] = 209,
  [210] = 210,
  [211] = 211,
  [212] = 212,
  [213] = 213,
  [214] = 214,
  [215] = 215,
  [216] = 216,
  [217] = 217,
  [218] = 218,
  [219] = 219,
  [220] = 220,
  [221] = 221,
  [222] = 222,
  [223] = 223,
  [224] = 224,
  [225] = 225,
  [226] = 226,
  [227] = 219,
  [228] = 228,
  [229] = 229,
  [230] = 230,
  [231] = 231,
  [232] = 232,
  [233] = 233,
  [234] = 234,
  [235] = 235,
  [236] = 236,
  [237] = 237,
  [238] = 238,
  [239] = 239,
  [240] = 240,
  [241] = 241,
  [242] = 242,
  [243] = 243,
  [244] = 244,
  [245] = 245,
  [246] = 246,
  [247] = 247,
  [248] = 248,
  [249] = 249,
  [250] = 250,
  [251] = 220,
  [252] = 250,
  [253] = 228,
  [254] = 254,
};

static inline bool aux_sym__name_char_token3_character_set_1(int32_t c) {
  return (c < 2492
    ? (c < 1648
      ? (c < 1476
        ? c == 1471
        : c <= 1476)
      : (c <= 1648 || (c < 2381
        ? c == 2364
        : c <= 2381)))
    : (c <= 2492 || (c < 2562
      ? (c < 2519
        ? (c >= 2494 && c <= 2495)
        : c <= 2519)
      : (c <= 2562 || (c < 2622
        ? c == 2620
        : c <= 2623)))));
}

static inline bool aux_sym__name_char_token8_character_set_1(int32_t c) {
  return (c < 2817
    ? (c < 903
      ? (c < 720
        ? c == 183
        : c <= 721)
      : (c <= 903 || (c < 2763
        ? c == 1600
        : c <= 2765)))
    : (c <= 2819 || (c < 3782
      ? (c < 3654
        ? c == 2876
        : c <= 3654)
      : (c <= 3782 || c == 12442))));
}

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(98);
      if (lookahead == '"') ADVANCE(121);
      if (lookahead == '%') ADVANCE(170);
      if (lookahead == '&') ADVANCE(169);
      if (lookahead == '\'') ADVANCE(122);
      if (lookahead == '(') ADVANCE(144);
      if (lookahead == ')') ADVANCE(146);
      if (lookahead == '*') ADVANCE(142);
      if (lookahead == '+') ADVANCE(143);
      if (lookahead == ',') ADVANCE(148);
      if (lookahead == '-') ADVANCE(102);
      if (lookahead == '.') ADVANCE(101);
      if (lookahead == ':') ADVANCE(104);
      if (lookahead == ';') ADVANCE(166);
      if (lookahead == '<') ADVANCE(3);
      if (lookahead == '=') ADVANCE(134);
      if (lookahead == '>') ADVANCE(136);
      if (lookahead == '?') ADVANCE(141);
      if (lookahead == '_') ADVANCE(119);
      if (lookahead == '|') ADVANCE(145);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(99);
      if (('!' <= lookahead && lookahead <= '/') ||
          lookahead == '@') ADVANCE(123);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(100);
      if (aux_sym__name_char_token3_character_set_1(lookahead)) ADVANCE(106);
      if (aux_sym__name_char_token8_character_set_1(lookahead)) ADVANCE(111);
      if ((3014 <= lookahead && lookahead <= 3016) ||
          (3018 <= lookahead && lookahead <= 3021) ||
          lookahead == 3031 ||
          (3398 <= lookahead && lookahead <= 3400) ||
          (3402 <= lookahead && lookahead <= 3405) ||
          lookahead == 3415 ||
          lookahead == 3633) ADVANCE(113);
      if ((2496 <= lookahead && lookahead <= 2500) ||
          lookahead == 2503 ||
          lookahead == 2504 ||
          (2507 <= lookahead && lookahead <= 2509) ||
          lookahead == 2530 ||
          lookahead == 2531 ||
          (2624 <= lookahead && lookahead <= 2626) ||
          lookahead == 2631 ||
          lookahead == 2632) ADVANCE(109);
      if ((2878 <= lookahead && lookahead <= 2883) ||
          lookahead == 2887 ||
          lookahead == 2888 ||
          (2891 <= lookahead && lookahead <= 2893) ||
          lookahead == 2902 ||
          lookahead == 2903 ||
          lookahead == 2946 ||
          lookahead == 2947 ||
          (3006 <= lookahead && lookahead <= 3010)) ADVANCE(112);
      if ((2635 <= lookahead && lookahead <= 2637) ||
          lookahead == 2672 ||
          lookahead == 2673 ||
          (2689 <= lookahead && lookahead <= 2691) ||
          lookahead == 2748 ||
          (2750 <= lookahead && lookahead <= 2757) ||
          (2759 <= lookahead && lookahead <= 2761) ||
          lookahead == 12293) ADVANCE(110);
      if ((3073 <= lookahead && lookahead <= 3075) ||
          (3134 <= lookahead && lookahead <= 3140) ||
          (3142 <= lookahead && lookahead <= 3144) ||
          (3146 <= lookahead && lookahead <= 3149) ||
          lookahead == 3157 ||
          lookahead == 3158 ||
          lookahead == 3202 ||
          lookahead == 3203) ADVANCE(114);
      if ((3262 <= lookahead && lookahead <= 3268) ||
          (3270 <= lookahead && lookahead <= 3272) ||
          (3274 <= lookahead && lookahead <= 3277) ||
          lookahead == 3285 ||
          lookahead == 3286 ||
          lookahead == 3330 ||
          lookahead == 3331 ||
          (3390 <= lookahead && lookahead <= 3395)) ADVANCE(115);
      if (lookahead == 1473 ||
          lookahead == 1474 ||
          (1611 <= lookahead && lookahead <= 1618) ||
          (1750 <= lookahead && lookahead <= 1764) ||
          lookahead == 1767 ||
          lookahead == 1768) ADVANCE(107);
      if ((1770 <= lookahead && lookahead <= 1773) ||
          (2305 <= lookahead && lookahead <= 2307) ||
          (2366 <= lookahead && lookahead <= 2380) ||
          (2385 <= lookahead && lookahead <= 2388) ||
          lookahead == 2402 ||
          lookahead == 2403 ||
          (2433 <= lookahead && lookahead <= 2435)) ADVANCE(108);
      if ((3636 <= lookahead && lookahead <= 3642) ||
          (3655 <= lookahead && lookahead <= 3662) ||
          lookahead == 3761 ||
          (3764 <= lookahead && lookahead <= 3769) ||
          lookahead == 3771 ||
          lookahead == 3772 ||
          (3784 <= lookahead && lookahead <= 3789) ||
          lookahead == 3864 ||
          lookahead == 3865) ADVANCE(116);
      if (lookahead == 3893 ||
          lookahead == 3895 ||
          lookahead == 3897 ||
          lookahead == 3902 ||
          lookahead == 3903 ||
          (3953 <= lookahead && lookahead <= 3972) ||
          (3974 <= lookahead && lookahead <= 3979) ||
          (3984 <= lookahead && lookahead <= 3989) ||
          lookahead == 3991) ADVANCE(117);
      if ((3993 <= lookahead && lookahead <= 4013) ||
          (4017 <= lookahead && lookahead <= 4023) ||
          lookahead == 4025 ||
          (8400 <= lookahead && lookahead <= 8412) ||
          lookahead == 8417 ||
          (12330 <= lookahead && lookahead <= 12335) ||
          lookahead == 12441) ADVANCE(118);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(100);
      if ((768 <= lookahead && lookahead <= 837) ||
          lookahead == 864 ||
          lookahead == 865 ||
          (1155 <= lookahead && lookahead <= 1158) ||
          (1425 <= lookahead && lookahead <= 1441) ||
          (1443 <= lookahead && lookahead <= 1465) ||
          (1467 <= lookahead && lookahead <= 1469)) ADVANCE(105);
      if (lookahead != 0) ADVANCE(123);
      END_STATE();
    case 1:
      if (lookahead == ' ') ADVANCE(93);
      END_STATE();
    case 2:
      if (lookahead == ' ') ADVANCE(14);
      END_STATE();
    case 3:
      if (lookahead == '!') ADVANCE(137);
      if (lookahead == '/') ADVANCE(135);
      if (lookahead == '?') ADVANCE(131);
      END_STATE();
    case 4:
      if (lookahead == '!') ADVANCE(137);
      if (lookahead == '?') ADVANCE(131);
      END_STATE();
    case 5:
      if (lookahead == '"') ADVANCE(121);
      if (lookahead == '&') ADVANCE(169);
      if (lookahead != 0 &&
          lookahead != '<') ADVANCE(123);
      END_STATE();
    case 6:
      if (lookahead == '"') ADVANCE(121);
      if (lookahead == '\'') ADVANCE(122);
      if (lookahead == '(') ADVANCE(144);
      if (lookahead == 'A') ADVANCE(63);
      if (lookahead == 'C') ADVANCE(31);
      if (lookahead == 'E') ADVANCE(54);
      if (lookahead == 'I') ADVANCE(30);
      if (lookahead == 'N') ADVANCE(59);
      if (lookahead == 'P') ADVANCE(87);
      if (lookahead == 'S') ADVANCE(90);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(165);
      END_STATE();
    case 7:
      if (lookahead == '"') ADVANCE(121);
      if (lookahead == '\'') ADVANCE(122);
      if (lookahead == ')') ADVANCE(146);
      if (lookahead == '-') ADVANCE(102);
      if (lookahead == '.') ADVANCE(101);
      if (lookahead == ':') ADVANCE(104);
      if (lookahead == ';') ADVANCE(166);
      if (lookahead == '>') ADVANCE(136);
      if (lookahead == '?') ADVANCE(16);
      if (lookahead == '|') ADVANCE(145);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(120);
      if (aux_sym__name_char_token3_character_set_1(lookahead)) ADVANCE(106);
      if (aux_sym__name_char_token8_character_set_1(lookahead)) ADVANCE(111);
      if ((3014 <= lookahead && lookahead <= 3016) ||
          (3018 <= lookahead && lookahead <= 3021) ||
          lookahead == 3031 ||
          (3398 <= lookahead && lookahead <= 3400) ||
          (3402 <= lookahead && lookahead <= 3405) ||
          lookahead == 3415 ||
          lookahead == 3633) ADVANCE(113);
      if ((2496 <= lookahead && lookahead <= 2500) ||
          lookahead == 2503 ||
          lookahead == 2504 ||
          (2507 <= lookahead && lookahead <= 2509) ||
          lookahead == 2530 ||
          lookahead == 2531 ||
          (2624 <= lookahead && lookahead <= 2626) ||
          lookahead == 2631 ||
          lookahead == 2632) ADVANCE(109);
      if ((2878 <= lookahead && lookahead <= 2883) ||
          lookahead == 2887 ||
          lookahead == 2888 ||
          (2891 <= lookahead && lookahead <= 2893) ||
          lookahead == 2902 ||
          lookahead == 2903 ||
          lookahead == 2946 ||
          lookahead == 2947 ||
          (3006 <= lookahead && lookahead <= 3010)) ADVANCE(112);
      if ((2635 <= lookahead && lookahead <= 2637) ||
          lookahead == 2672 ||
          lookahead == 2673 ||
          (2689 <= lookahead && lookahead <= 2691) ||
          lookahead == 2748 ||
          (2750 <= lookahead && lookahead <= 2757) ||
          (2759 <= lookahead && lookahead <= 2761) ||
          lookahead == 12293) ADVANCE(110);
      if ((3073 <= lookahead && lookahead <= 3075) ||
          (3134 <= lookahead && lookahead <= 3140) ||
          (3142 <= lookahead && lookahead <= 3144) ||
          (3146 <= lookahead && lookahead <= 3149) ||
          lookahead == 3157 ||
          lookahead == 3158 ||
          lookahead == 3202 ||
          lookahead == 3203) ADVANCE(114);
      if ((3262 <= lookahead && lookahead <= 3268) ||
          (3270 <= lookahead && lookahead <= 3272) ||
          (3274 <= lookahead && lookahead <= 3277) ||
          lookahead == 3285 ||
          lookahead == 3286 ||
          lookahead == 3330 ||
          lookahead == 3331 ||
          (3390 <= lookahead && lookahead <= 3395)) ADVANCE(115);
      if (lookahead == 1473 ||
          lookahead == 1474 ||
          (1611 <= lookahead && lookahead <= 1618) ||
          (1750 <= lookahead && lookahead <= 1764) ||
          lookahead == 1767 ||
          lookahead == 1768) ADVANCE(107);
      if ((1770 <= lookahead && lookahead <= 1773) ||
          (2305 <= lookahead && lookahead <= 2307) ||
          (2366 <= lookahead && lookahead <= 2380) ||
          (2385 <= lookahead && lookahead <= 2388) ||
          lookahead == 2402 ||
          lookahead == 2403 ||
          (2433 <= lookahead && lookahead <= 2435)) ADVANCE(108);
      if ((3636 <= lookahead && lookahead <= 3642) ||
          (3655 <= lookahead && lookahead <= 3662) ||
          lookahead == 3761 ||
          (3764 <= lookahead && lookahead <= 3769) ||
          lookahead == 3771 ||
          lookahead == 3772 ||
          (3784 <= lookahead && lookahead <= 3789) ||
          lookahead == 3864 ||
          lookahead == 3865) ADVANCE(116);
      if (lookahead == 3893 ||
          lookahead == 3895 ||
          lookahead == 3897 ||
          lookahead == 3902 ||
          lookahead == 3903 ||
          (3953 <= lookahead && lookahead <= 3972) ||
          (3974 <= lookahead && lookahead <= 3979) ||
          (3984 <= lookahead && lookahead <= 3989) ||
          lookahead == 3991) ADVANCE(117);
      if ((3993 <= lookahead && lookahead <= 4013) ||
          (4017 <= lookahead && lookahead <= 4023) ||
          lookahead == 4025 ||
          (8400 <= lookahead && lookahead <= 8412) ||
          lookahead == 8417 ||
          (12330 <= lookahead && lookahead <= 12335) ||
          lookahead == 12441) ADVANCE(118);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(100);
      if ((768 <= lookahead && lookahead <= 837) ||
          lookahead == 864 ||
          lookahead == 865 ||
          (1155 <= lookahead && lookahead <= 1158) ||
          (1425 <= lookahead && lookahead <= 1441) ||
          (1443 <= lookahead && lookahead <= 1465) ||
          (1467 <= lookahead && lookahead <= 1469)) ADVANCE(105);
      END_STATE();
    case 8:
      if (lookahead == '"') ADVANCE(121);
      if (lookahead == '\'') ADVANCE(122);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          (' ' <= lookahead && lookahead <= '%') ||
          ('(' <= lookahead && lookahead <= ';') ||
          lookahead == '=' ||
          ('?' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 9:
      if (lookahead == '#') ADVANCE(67);
      if (lookahead == '%') ADVANCE(170);
      if (lookahead == '(') ADVANCE(144);
      if (lookahead == ':') ADVANCE(104);
      if (lookahead == '>') ADVANCE(136);
      if (lookahead == '_') ADVANCE(119);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(99);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(100);
      END_STATE();
    case 10:
      if (lookahead == '&') ADVANCE(169);
      if (lookahead == '\'') ADVANCE(122);
      if (lookahead != 0 &&
          lookahead != '<') ADVANCE(124);
      END_STATE();
    case 11:
      if (lookahead == ')') ADVANCE(147);
      if (lookahead == '-') ADVANCE(102);
      if (lookahead == '.') ADVANCE(101);
      if (lookahead == ':') ADVANCE(104);
      if (lookahead == '|') ADVANCE(145);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(120);
      if (aux_sym__name_char_token3_character_set_1(lookahead)) ADVANCE(106);
      if (aux_sym__name_char_token8_character_set_1(lookahead)) ADVANCE(111);
      if ((3014 <= lookahead && lookahead <= 3016) ||
          (3018 <= lookahead && lookahead <= 3021) ||
          lookahead == 3031 ||
          (3398 <= lookahead && lookahead <= 3400) ||
          (3402 <= lookahead && lookahead <= 3405) ||
          lookahead == 3415 ||
          lookahead == 3633) ADVANCE(113);
      if ((2496 <= lookahead && lookahead <= 2500) ||
          lookahead == 2503 ||
          lookahead == 2504 ||
          (2507 <= lookahead && lookahead <= 2509) ||
          lookahead == 2530 ||
          lookahead == 2531 ||
          (2624 <= lookahead && lookahead <= 2626) ||
          lookahead == 2631 ||
          lookahead == 2632) ADVANCE(109);
      if ((2878 <= lookahead && lookahead <= 2883) ||
          lookahead == 2887 ||
          lookahead == 2888 ||
          (2891 <= lookahead && lookahead <= 2893) ||
          lookahead == 2902 ||
          lookahead == 2903 ||
          lookahead == 2946 ||
          lookahead == 2947 ||
          (3006 <= lookahead && lookahead <= 3010)) ADVANCE(112);
      if ((2635 <= lookahead && lookahead <= 2637) ||
          lookahead == 2672 ||
          lookahead == 2673 ||
          (2689 <= lookahead && lookahead <= 2691) ||
          lookahead == 2748 ||
          (2750 <= lookahead && lookahead <= 2757) ||
          (2759 <= lookahead && lookahead <= 2761) ||
          lookahead == 12293) ADVANCE(110);
      if ((3073 <= lookahead && lookahead <= 3075) ||
          (3134 <= lookahead && lookahead <= 3140) ||
          (3142 <= lookahead && lookahead <= 3144) ||
          (3146 <= lookahead && lookahead <= 3149) ||
          lookahead == 3157 ||
          lookahead == 3158 ||
          lookahead == 3202 ||
          lookahead == 3203) ADVANCE(114);
      if ((3262 <= lookahead && lookahead <= 3268) ||
          (3270 <= lookahead && lookahead <= 3272) ||
          (3274 <= lookahead && lookahead <= 3277) ||
          lookahead == 3285 ||
          lookahead == 3286 ||
          lookahead == 3330 ||
          lookahead == 3331 ||
          (3390 <= lookahead && lookahead <= 3395)) ADVANCE(115);
      if (lookahead == 1473 ||
          lookahead == 1474 ||
          (1611 <= lookahead && lookahead <= 1618) ||
          (1750 <= lookahead && lookahead <= 1764) ||
          lookahead == 1767 ||
          lookahead == 1768) ADVANCE(107);
      if ((1770 <= lookahead && lookahead <= 1773) ||
          (2305 <= lookahead && lookahead <= 2307) ||
          (2366 <= lookahead && lookahead <= 2380) ||
          (2385 <= lookahead && lookahead <= 2388) ||
          lookahead == 2402 ||
          lookahead == 2403 ||
          (2433 <= lookahead && lookahead <= 2435)) ADVANCE(108);
      if ((3636 <= lookahead && lookahead <= 3642) ||
          (3655 <= lookahead && lookahead <= 3662) ||
          lookahead == 3761 ||
          (3764 <= lookahead && lookahead <= 3769) ||
          lookahead == 3771 ||
          lookahead == 3772 ||
          (3784 <= lookahead && lookahead <= 3789) ||
          lookahead == 3864 ||
          lookahead == 3865) ADVANCE(116);
      if (lookahead == 3893 ||
          lookahead == 3895 ||
          lookahead == 3897 ||
          lookahead == 3902 ||
          lookahead == 3903 ||
          (3953 <= lookahead && lookahead <= 3972) ||
          (3974 <= lookahead && lookahead <= 3979) ||
          (3984 <= lookahead && lookahead <= 3989) ||
          lookahead == 3991) ADVANCE(117);
      if ((3993 <= lookahead && lookahead <= 4013) ||
          (4017 <= lookahead && lookahead <= 4023) ||
          lookahead == 4025 ||
          (8400 <= lookahead && lookahead <= 8412) ||
          lookahead == 8417 ||
          (12330 <= lookahead && lookahead <= 12335) ||
          lookahead == 12441) ADVANCE(118);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(100);
      if ((768 <= lookahead && lookahead <= 837) ||
          lookahead == 864 ||
          lookahead == 865 ||
          (1155 <= lookahead && lookahead <= 1158) ||
          (1425 <= lookahead && lookahead <= 1441) ||
          (1443 <= lookahead && lookahead <= 1465) ||
          (1467 <= lookahead && lookahead <= 1469)) ADVANCE(105);
      END_STATE();
    case 12:
      if (lookahead == '-') ADVANCE(128);
      END_STATE();
    case 13:
      if (lookahead == '-') ADVANCE(103);
      if (lookahead != 0) ADVANCE(129);
      END_STATE();
    case 14:
      if (lookahead == '-') ADVANCE(1);
      END_STATE();
    case 15:
      if (lookahead == ':') ADVANCE(104);
      if (lookahead == '_') ADVANCE(119);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(120);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(100);
      END_STATE();
    case 16:
      if (lookahead == '>') ADVANCE(133);
      END_STATE();
    case 17:
      if (lookahead == '>') ADVANCE(130);
      END_STATE();
    case 18:
      if (lookahead == 'A') ADVANCE(79);
      END_STATE();
    case 19:
      if (lookahead == 'A') ADVANCE(149);
      END_STATE();
    case 20:
      if (lookahead == 'A') ADVANCE(152);
      END_STATE();
    case 21:
      if (lookahead == 'A') ADVANCE(80);
      END_STATE();
    case 22:
      if (lookahead == 'A') ADVANCE(84);
      END_STATE();
    case 23:
      if (lookahead == 'B') ADVANCE(56);
      END_STATE();
    case 24:
      if (lookahead == 'C') ADVANCE(26);
      END_STATE();
    case 25:
      if (lookahead == 'C') ADVANCE(172);
      END_STATE();
    case 26:
      if (lookahead == 'D') ADVANCE(18);
      END_STATE();
    case 27:
      if (lookahead == 'D') ADVANCE(163);
      END_STATE();
    case 28:
      if (lookahead == 'D') ADVANCE(162);
      END_STATE();
    case 29:
      if (lookahead == 'D') ADVANCE(161);
      END_STATE();
    case 30:
      if (lookahead == 'D') ADVANCE(153);
      END_STATE();
    case 31:
      if (lookahead == 'D') ADVANCE(21);
      END_STATE();
    case 32:
      if (lookahead == 'E') ADVANCE(70);
      END_STATE();
    case 33:
      if (lookahead == 'E') ADVANCE(43);
      END_STATE();
    case 34:
      if (lookahead == 'E') ADVANCE(64);
      END_STATE();
    case 35:
      if (lookahead == 'E') ADVANCE(60);
      END_STATE();
    case 36:
      if (lookahead == 'E') ADVANCE(27);
      END_STATE();
    case 37:
      if (lookahead == 'E') ADVANCE(72);
      END_STATE();
    case 38:
      if (lookahead == 'E') ADVANCE(61);
      END_STATE();
    case 39:
      if (lookahead == 'E') ADVANCE(58);
      END_STATE();
    case 40:
      if (lookahead == 'E') ADVANCE(28);
      END_STATE();
    case 41:
      if (lookahead == 'E') ADVANCE(29);
      END_STATE();
    case 42:
      if (lookahead == 'F') ADVANCE(44);
      if (lookahead == 'I') ADVANCE(57);
      if (lookahead == 'P') ADVANCE(24);
      if (lookahead == 'R') ADVANCE(32);
      END_STATE();
    case 43:
      if (lookahead == 'F') ADVANCE(154);
      END_STATE();
    case 44:
      if (lookahead == 'I') ADVANCE(89);
      END_STATE();
    case 45:
      if (lookahead == 'I') ADVANCE(71);
      END_STATE();
    case 46:
      if (lookahead == 'I') ADVANCE(25);
      END_STATE();
    case 47:
      if (lookahead == 'I') ADVANCE(66);
      END_STATE();
    case 48:
      if (lookahead == 'I') ADVANCE(37);
      if (lookahead == 'Y') ADVANCE(156);
      END_STATE();
    case 49:
      if (lookahead == 'I') ADVANCE(76);
      END_STATE();
    case 50:
      if (lookahead == 'I') ADVANCE(74);
      END_STATE();
    case 51:
      if (lookahead == 'I') ADVANCE(40);
      END_STATE();
    case 52:
      if (lookahead == 'K') ADVANCE(38);
      END_STATE();
    case 53:
      if (lookahead == 'L') ADVANCE(51);
      END_STATE();
    case 54:
      if (lookahead == 'L') ADVANCE(35);
      if (lookahead == 'M') ADVANCE(69);
      if (lookahead == 'N') ADVANCE(82);
      END_STATE();
    case 55:
      if (lookahead == 'L') ADVANCE(50);
      END_STATE();
    case 56:
      if (lookahead == 'L') ADVANCE(46);
      END_STATE();
    case 57:
      if (lookahead == 'M') ADVANCE(68);
      END_STATE();
    case 58:
      if (lookahead == 'M') ADVANCE(171);
      END_STATE();
    case 59:
      if (lookahead == 'M') ADVANCE(75);
      if (lookahead == 'O') ADVANCE(86);
      END_STATE();
    case 60:
      if (lookahead == 'M') ADVANCE(34);
      END_STATE();
    case 61:
      if (lookahead == 'N') ADVANCE(158);
      END_STATE();
    case 62:
      if (lookahead == 'N') ADVANCE(160);
      END_STATE();
    case 63:
      if (lookahead == 'N') ADVANCE(91);
      if (lookahead == 'T') ADVANCE(85);
      END_STATE();
    case 64:
      if (lookahead == 'N') ADVANCE(78);
      END_STATE();
    case 65:
      if (lookahead == 'O') ADVANCE(52);
      END_STATE();
    case 66:
      if (lookahead == 'O') ADVANCE(62);
      END_STATE();
    case 67:
      if (lookahead == 'P') ADVANCE(24);
      END_STATE();
    case 68:
      if (lookahead == 'P') ADVANCE(53);
      END_STATE();
    case 69:
      if (lookahead == 'P') ADVANCE(81);
      END_STATE();
    case 70:
      if (lookahead == 'Q') ADVANCE(88);
      END_STATE();
    case 71:
      if (lookahead == 'R') ADVANCE(41);
      END_STATE();
    case 72:
      if (lookahead == 'S') ADVANCE(157);
      END_STATE();
    case 73:
      if (lookahead == 'S') ADVANCE(83);
      END_STATE();
    case 74:
      if (lookahead == 'S') ADVANCE(77);
      END_STATE();
    case 75:
      if (lookahead == 'T') ADVANCE(65);
      END_STATE();
    case 76:
      if (lookahead == 'T') ADVANCE(48);
      END_STATE();
    case 77:
      if (lookahead == 'T') ADVANCE(151);
      END_STATE();
    case 78:
      if (lookahead == 'T') ADVANCE(138);
      END_STATE();
    case 79:
      if (lookahead == 'T') ADVANCE(19);
      END_STATE();
    case 80:
      if (lookahead == 'T') ADVANCE(20);
      END_STATE();
    case 81:
      if (lookahead == 'T') ADVANCE(92);
      END_STATE();
    case 82:
      if (lookahead == 'T') ADVANCE(49);
      END_STATE();
    case 83:
      if (lookahead == 'T') ADVANCE(39);
      END_STATE();
    case 84:
      if (lookahead == 'T') ADVANCE(47);
      END_STATE();
    case 85:
      if (lookahead == 'T') ADVANCE(55);
      END_STATE();
    case 86:
      if (lookahead == 'T') ADVANCE(22);
      END_STATE();
    case 87:
      if (lookahead == 'U') ADVANCE(23);
      END_STATE();
    case 88:
      if (lookahead == 'U') ADVANCE(45);
      END_STATE();
    case 89:
      if (lookahead == 'X') ADVANCE(36);
      END_STATE();
    case 90:
      if (lookahead == 'Y') ADVANCE(73);
      END_STATE();
    case 91:
      if (lookahead == 'Y') ADVANCE(140);
      END_STATE();
    case 92:
      if (lookahead == 'Y') ADVANCE(139);
      END_STATE();
    case 93:
      if (lookahead == '\'' ||
          lookahead == '.' ||
          lookahead == '>' ||
          lookahead == '?') ADVANCE(132);
      END_STATE();
    case 94:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(168);
      END_STATE();
    case 95:
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(2);
      END_STATE();
    case 96:
      if (lookahead != 0 &&
          lookahead != '\'') ADVANCE(126);
      END_STATE();
    case 97:
      if (eof) ADVANCE(98);
      if (lookahead == '"') ADVANCE(121);
      if (lookahead == '#') ADVANCE(42);
      if (lookahead == '%') ADVANCE(170);
      if (lookahead == '\'') ADVANCE(122);
      if (lookahead == '(') ADVANCE(144);
      if (lookahead == ')') ADVANCE(146);
      if (lookahead == '*') ADVANCE(142);
      if (lookahead == '+') ADVANCE(143);
      if (lookahead == ',') ADVANCE(148);
      if (lookahead == '-') ADVANCE(102);
      if (lookahead == '.') ADVANCE(101);
      if (lookahead == ':') ADVANCE(104);
      if (lookahead == ';') ADVANCE(166);
      if (lookahead == '<') ADVANCE(4);
      if (lookahead == '>') ADVANCE(136);
      if (lookahead == '?') ADVANCE(141);
      if (lookahead == '|') ADVANCE(145);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(99);
      if (aux_sym__name_char_token3_character_set_1(lookahead)) ADVANCE(106);
      if (aux_sym__name_char_token8_character_set_1(lookahead)) ADVANCE(111);
      if ((3014 <= lookahead && lookahead <= 3016) ||
          (3018 <= lookahead && lookahead <= 3021) ||
          lookahead == 3031 ||
          (3398 <= lookahead && lookahead <= 3400) ||
          (3402 <= lookahead && lookahead <= 3405) ||
          lookahead == 3415 ||
          lookahead == 3633) ADVANCE(113);
      if ((2496 <= lookahead && lookahead <= 2500) ||
          lookahead == 2503 ||
          lookahead == 2504 ||
          (2507 <= lookahead && lookahead <= 2509) ||
          lookahead == 2530 ||
          lookahead == 2531 ||
          (2624 <= lookahead && lookahead <= 2626) ||
          lookahead == 2631 ||
          lookahead == 2632) ADVANCE(109);
      if ((2878 <= lookahead && lookahead <= 2883) ||
          lookahead == 2887 ||
          lookahead == 2888 ||
          (2891 <= lookahead && lookahead <= 2893) ||
          lookahead == 2902 ||
          lookahead == 2903 ||
          lookahead == 2946 ||
          lookahead == 2947 ||
          (3006 <= lookahead && lookahead <= 3010)) ADVANCE(112);
      if ((2635 <= lookahead && lookahead <= 2637) ||
          lookahead == 2672 ||
          lookahead == 2673 ||
          (2689 <= lookahead && lookahead <= 2691) ||
          lookahead == 2748 ||
          (2750 <= lookahead && lookahead <= 2757) ||
          (2759 <= lookahead && lookahead <= 2761) ||
          lookahead == 12293) ADVANCE(110);
      if ((3073 <= lookahead && lookahead <= 3075) ||
          (3134 <= lookahead && lookahead <= 3140) ||
          (3142 <= lookahead && lookahead <= 3144) ||
          (3146 <= lookahead && lookahead <= 3149) ||
          lookahead == 3157 ||
          lookahead == 3158 ||
          lookahead == 3202 ||
          lookahead == 3203) ADVANCE(114);
      if ((3262 <= lookahead && lookahead <= 3268) ||
          (3270 <= lookahead && lookahead <= 3272) ||
          (3274 <= lookahead && lookahead <= 3277) ||
          lookahead == 3285 ||
          lookahead == 3286 ||
          lookahead == 3330 ||
          lookahead == 3331 ||
          (3390 <= lookahead && lookahead <= 3395)) ADVANCE(115);
      if (lookahead == 1473 ||
          lookahead == 1474 ||
          (1611 <= lookahead && lookahead <= 1618) ||
          (1750 <= lookahead && lookahead <= 1764) ||
          lookahead == 1767 ||
          lookahead == 1768) ADVANCE(107);
      if ((1770 <= lookahead && lookahead <= 1773) ||
          (2305 <= lookahead && lookahead <= 2307) ||
          (2366 <= lookahead && lookahead <= 2380) ||
          (2385 <= lookahead && lookahead <= 2388) ||
          lookahead == 2402 ||
          lookahead == 2403 ||
          (2433 <= lookahead && lookahead <= 2435)) ADVANCE(108);
      if ((3636 <= lookahead && lookahead <= 3642) ||
          (3655 <= lookahead && lookahead <= 3662) ||
          lookahead == 3761 ||
          (3764 <= lookahead && lookahead <= 3769) ||
          lookahead == 3771 ||
          lookahead == 3772 ||
          (3784 <= lookahead && lookahead <= 3789) ||
          lookahead == 3864 ||
          lookahead == 3865) ADVANCE(116);
      if (lookahead == 3893 ||
          lookahead == 3895 ||
          lookahead == 3897 ||
          lookahead == 3902 ||
          lookahead == 3903 ||
          (3953 <= lookahead && lookahead <= 3972) ||
          (3974 <= lookahead && lookahead <= 3979) ||
          (3984 <= lookahead && lookahead <= 3989) ||
          lookahead == 3991) ADVANCE(117);
      if ((3993 <= lookahead && lookahead <= 4013) ||
          (4017 <= lookahead && lookahead <= 4023) ||
          lookahead == 4025 ||
          (8400 <= lookahead && lookahead <= 8412) ||
          lookahead == 8417 ||
          (12330 <= lookahead && lookahead <= 12335) ||
          lookahead == 12441) ADVANCE(118);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(100);
      if ((768 <= lookahead && lookahead <= 837) ||
          lookahead == 864 ||
          lookahead == 865 ||
          (1155 <= lookahead && lookahead <= 1158) ||
          (1425 <= lookahead && lookahead <= 1441) ||
          (1443 <= lookahead && lookahead <= 1465) ||
          (1467 <= lookahead && lookahead <= 1469)) ADVANCE(105);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(aux_sym_document_token1);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(99);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(aux_sym__name_char_token1);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(anon_sym_DOT);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(anon_sym_DASH);
      if (lookahead == '-') ADVANCE(17);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(aux_sym__name_char_token2);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(aux_sym__name_char_token3);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(aux_sym__name_char_token4);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(aux_sym__name_char_token5);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(aux_sym__name_char_token6);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(aux_sym__name_char_token7);
      END_STATE();
    case 111:
      ACCEPT_TOKEN(aux_sym__name_char_token8);
      END_STATE();
    case 112:
      ACCEPT_TOKEN(aux_sym__name_char_token9);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(aux_sym__name_char_token10);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(aux_sym__name_char_token11);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(aux_sym__name_char_token12);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(aux_sym__name_char_token13);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(aux_sym__name_char_token14);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(aux_sym__name_char_token15);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(anon_sym__);
      END_STATE();
    case 120:
      ACCEPT_TOKEN(aux_sym_names_token1);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 123:
      ACCEPT_TOKEN(aux_sym_attribute_value_token1);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(aux_sym_attribute_value_token2);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(aux_sym_system_literal_token1);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(125);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(aux_sym_system_literal_token2);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(sym_pubid_char);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(anon_sym_LT_BANG_DASH_DASH);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(aux_sym_comment_token1);
      END_STATE();
    case 130:
      ACCEPT_TOKEN(anon_sym_DASH_DASH_GT);
      END_STATE();
    case 131:
      ACCEPT_TOKEN(anon_sym_LT_QMARK);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(aux_sym_processing_instructions_token1);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(anon_sym_QMARK_GT);
      END_STATE();
    case 134:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(anon_sym_LT_SLASH);
      END_STATE();
    case 136:
      ACCEPT_TOKEN(anon_sym_GT);
      END_STATE();
    case 137:
      ACCEPT_TOKEN(anon_sym_LT_BANG);
      if (lookahead == '-') ADVANCE(12);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(anon_sym_ELEMENT);
      END_STATE();
    case 139:
      ACCEPT_TOKEN(anon_sym_EMPTY);
      END_STATE();
    case 140:
      ACCEPT_TOKEN(anon_sym_ANY);
      END_STATE();
    case 141:
      ACCEPT_TOKEN(anon_sym_QMARK);
      END_STATE();
    case 142:
      ACCEPT_TOKEN(anon_sym_STAR);
      END_STATE();
    case 143:
      ACCEPT_TOKEN(anon_sym_PLUS);
      END_STATE();
    case 144:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 145:
      ACCEPT_TOKEN(anon_sym_PIPE);
      END_STATE();
    case 146:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 147:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      if (lookahead == '*') ADVANCE(150);
      END_STATE();
    case 148:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 149:
      ACCEPT_TOKEN(anon_sym_POUNDPCDATA);
      END_STATE();
    case 150:
      ACCEPT_TOKEN(anon_sym_RPAREN_STAR);
      END_STATE();
    case 151:
      ACCEPT_TOKEN(anon_sym_ATTLIST);
      END_STATE();
    case 152:
      ACCEPT_TOKEN(sym__string_type);
      END_STATE();
    case 153:
      ACCEPT_TOKEN(anon_sym_ID);
      if (lookahead == 'R') ADVANCE(33);
      END_STATE();
    case 154:
      ACCEPT_TOKEN(anon_sym_IDREF);
      if (lookahead == 'S') ADVANCE(155);
      END_STATE();
    case 155:
      ACCEPT_TOKEN(anon_sym_IDREFS);
      END_STATE();
    case 156:
      ACCEPT_TOKEN(anon_sym_ENTITY);
      END_STATE();
    case 157:
      ACCEPT_TOKEN(anon_sym_ENTITIES);
      END_STATE();
    case 158:
      ACCEPT_TOKEN(anon_sym_NMTOKEN);
      if (lookahead == 'S') ADVANCE(159);
      END_STATE();
    case 159:
      ACCEPT_TOKEN(anon_sym_NMTOKENS);
      END_STATE();
    case 160:
      ACCEPT_TOKEN(anon_sym_NOTATION);
      END_STATE();
    case 161:
      ACCEPT_TOKEN(anon_sym_POUNDREQUIRED);
      END_STATE();
    case 162:
      ACCEPT_TOKEN(anon_sym_POUNDIMPLIED);
      END_STATE();
    case 163:
      ACCEPT_TOKEN(anon_sym_POUNDFIXED);
      END_STATE();
    case 164:
      ACCEPT_TOKEN(anon_sym_AMP_POUND);
      if (lookahead == 'x') ADVANCE(167);
      END_STATE();
    case 165:
      ACCEPT_TOKEN(aux_sym_char_ref_token1);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(165);
      END_STATE();
    case 166:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 167:
      ACCEPT_TOKEN(anon_sym_AMP_POUNDx);
      END_STATE();
    case 168:
      ACCEPT_TOKEN(aux_sym_char_ref_token2);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(168);
      END_STATE();
    case 169:
      ACCEPT_TOKEN(anon_sym_AMP);
      if (lookahead == '#') ADVANCE(164);
      END_STATE();
    case 170:
      ACCEPT_TOKEN(anon_sym_PERCENT);
      END_STATE();
    case 171:
      ACCEPT_TOKEN(anon_sym_SYSTEM);
      END_STATE();
    case 172:
      ACCEPT_TOKEN(anon_sym_PUBLIC);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 97},
  [2] = {.lex_state = 97},
  [3] = {.lex_state = 97},
  [4] = {.lex_state = 97},
  [5] = {.lex_state = 7},
  [6] = {.lex_state = 7},
  [7] = {.lex_state = 7},
  [8] = {.lex_state = 11},
  [9] = {.lex_state = 7},
  [10] = {.lex_state = 11},
  [11] = {.lex_state = 11},
  [12] = {.lex_state = 7},
  [13] = {.lex_state = 7},
  [14] = {.lex_state = 7},
  [15] = {.lex_state = 7},
  [16] = {.lex_state = 97},
  [17] = {.lex_state = 97},
  [18] = {.lex_state = 97},
  [19] = {.lex_state = 97},
  [20] = {.lex_state = 97},
  [21] = {.lex_state = 6},
  [22] = {.lex_state = 9},
  [23] = {.lex_state = 5},
  [24] = {.lex_state = 9},
  [25] = {.lex_state = 10},
  [26] = {.lex_state = 5},
  [27] = {.lex_state = 9},
  [28] = {.lex_state = 9},
  [29] = {.lex_state = 10},
  [30] = {.lex_state = 10},
  [31] = {.lex_state = 5},
  [32] = {.lex_state = 9},
  [33] = {.lex_state = 9},
  [34] = {.lex_state = 97},
  [35] = {.lex_state = 97},
  [36] = {.lex_state = 9},
  [37] = {.lex_state = 9},
  [38] = {.lex_state = 9},
  [39] = {.lex_state = 6},
  [40] = {.lex_state = 9},
  [41] = {.lex_state = 97},
  [42] = {.lex_state = 97},
  [43] = {.lex_state = 9},
  [44] = {.lex_state = 97},
  [45] = {.lex_state = 97},
  [46] = {.lex_state = 97},
  [47] = {.lex_state = 97},
  [48] = {.lex_state = 6},
  [49] = {.lex_state = 97},
  [50] = {.lex_state = 6},
  [51] = {.lex_state = 97},
  [52] = {.lex_state = 97},
  [53] = {.lex_state = 97},
  [54] = {.lex_state = 97},
  [55] = {.lex_state = 97},
  [56] = {.lex_state = 97},
  [57] = {.lex_state = 97},
  [58] = {.lex_state = 97},
  [59] = {.lex_state = 97},
  [60] = {.lex_state = 97},
  [61] = {.lex_state = 97},
  [62] = {.lex_state = 97},
  [63] = {.lex_state = 97},
  [64] = {.lex_state = 97},
  [65] = {.lex_state = 97},
  [66] = {.lex_state = 97},
  [67] = {.lex_state = 97},
  [68] = {.lex_state = 97},
  [69] = {.lex_state = 97},
  [70] = {.lex_state = 5},
  [71] = {.lex_state = 15},
  [72] = {.lex_state = 9},
  [73] = {.lex_state = 10},
  [74] = {.lex_state = 15},
  [75] = {.lex_state = 10},
  [76] = {.lex_state = 10},
  [77] = {.lex_state = 9},
  [78] = {.lex_state = 5},
  [79] = {.lex_state = 5},
  [80] = {.lex_state = 15},
  [81] = {.lex_state = 15},
  [82] = {.lex_state = 9},
  [83] = {.lex_state = 15},
  [84] = {.lex_state = 9},
  [85] = {.lex_state = 97},
  [86] = {.lex_state = 11},
  [87] = {.lex_state = 11},
  [88] = {.lex_state = 9},
  [89] = {.lex_state = 7},
  [90] = {.lex_state = 7},
  [91] = {.lex_state = 8},
  [92] = {.lex_state = 7},
  [93] = {.lex_state = 11},
  [94] = {.lex_state = 97},
  [95] = {.lex_state = 7},
  [96] = {.lex_state = 6},
  [97] = {.lex_state = 9},
  [98] = {.lex_state = 97},
  [99] = {.lex_state = 97},
  [100] = {.lex_state = 7},
  [101] = {.lex_state = 7},
  [102] = {.lex_state = 7},
  [103] = {.lex_state = 7},
  [104] = {.lex_state = 7},
  [105] = {.lex_state = 7},
  [106] = {.lex_state = 7},
  [107] = {.lex_state = 9},
  [108] = {.lex_state = 8},
  [109] = {.lex_state = 9},
  [110] = {.lex_state = 9},
  [111] = {.lex_state = 7},
  [112] = {.lex_state = 9},
  [113] = {.lex_state = 9},
  [114] = {.lex_state = 9},
  [115] = {.lex_state = 8},
  [116] = {.lex_state = 13},
  [117] = {.lex_state = 97},
  [118] = {.lex_state = 97},
  [119] = {.lex_state = 9},
  [120] = {.lex_state = 7},
  [121] = {.lex_state = 11},
  [122] = {.lex_state = 9},
  [123] = {.lex_state = 9},
  [124] = {.lex_state = 13},
  [125] = {.lex_state = 7},
  [126] = {.lex_state = 11},
  [127] = {.lex_state = 13},
  [128] = {.lex_state = 9},
  [129] = {.lex_state = 9},
  [130] = {.lex_state = 6},
  [131] = {.lex_state = 9},
  [132] = {.lex_state = 97},
  [133] = {.lex_state = 97},
  [134] = {.lex_state = 97},
  [135] = {.lex_state = 11},
  [136] = {.lex_state = 13},
  [137] = {.lex_state = 7},
  [138] = {.lex_state = 97},
  [139] = {.lex_state = 7},
  [140] = {.lex_state = 7},
  [141] = {.lex_state = 7},
  [142] = {.lex_state = 11},
  [143] = {.lex_state = 97},
  [144] = {.lex_state = 7},
  [145] = {.lex_state = 97},
  [146] = {.lex_state = 7},
  [147] = {.lex_state = 97},
  [148] = {.lex_state = 11},
  [149] = {.lex_state = 8},
  [150] = {.lex_state = 97},
  [151] = {.lex_state = 97},
  [152] = {.lex_state = 7},
  [153] = {.lex_state = 97},
  [154] = {.lex_state = 97},
  [155] = {.lex_state = 97},
  [156] = {.lex_state = 97},
  [157] = {.lex_state = 11},
  [158] = {.lex_state = 97},
  [159] = {.lex_state = 11},
  [160] = {.lex_state = 8},
  [161] = {.lex_state = 8},
  [162] = {.lex_state = 97},
  [163] = {.lex_state = 7},
  [164] = {.lex_state = 97},
  [165] = {.lex_state = 11},
  [166] = {.lex_state = 7},
  [167] = {.lex_state = 7},
  [168] = {.lex_state = 7},
  [169] = {.lex_state = 97},
  [170] = {.lex_state = 11},
  [171] = {.lex_state = 97},
  [172] = {.lex_state = 97},
  [173] = {.lex_state = 97},
  [174] = {.lex_state = 97},
  [175] = {.lex_state = 7},
  [176] = {.lex_state = 7},
  [177] = {.lex_state = 7},
  [178] = {.lex_state = 7},
  [179] = {.lex_state = 7},
  [180] = {.lex_state = 7},
  [181] = {.lex_state = 7},
  [182] = {.lex_state = 7},
  [183] = {.lex_state = 7},
  [184] = {.lex_state = 97},
  [185] = {.lex_state = 7},
  [186] = {.lex_state = 7},
  [187] = {.lex_state = 7},
  [188] = {.lex_state = 97},
  [189] = {.lex_state = 97},
  [190] = {.lex_state = 97},
  [191] = {.lex_state = 97},
  [192] = {.lex_state = 97},
  [193] = {.lex_state = 7},
  [194] = {.lex_state = 7},
  [195] = {.lex_state = 7},
  [196] = {.lex_state = 97},
  [197] = {.lex_state = 7},
  [198] = {.lex_state = 97},
  [199] = {.lex_state = 7},
  [200] = {.lex_state = 7},
  [201] = {.lex_state = 7},
  [202] = {.lex_state = 0},
  [203] = {.lex_state = 97},
  [204] = {.lex_state = 97},
  [205] = {.lex_state = 7},
  [206] = {.lex_state = 7},
  [207] = {.lex_state = 97},
  [208] = {.lex_state = 97},
  [209] = {.lex_state = 7},
  [210] = {.lex_state = 7},
  [211] = {.lex_state = 97},
  [212] = {.lex_state = 0},
  [213] = {.lex_state = 97},
  [214] = {.lex_state = 7},
  [215] = {.lex_state = 97},
  [216] = {.lex_state = 7},
  [217] = {.lex_state = 7},
  [218] = {.lex_state = 7},
  [219] = {.lex_state = 97},
  [220] = {.lex_state = 97},
  [221] = {.lex_state = 7},
  [222] = {.lex_state = 7},
  [223] = {.lex_state = 7},
  [224] = {.lex_state = 7},
  [225] = {.lex_state = 7},
  [226] = {.lex_state = 97},
  [227] = {.lex_state = 97},
  [228] = {.lex_state = 94},
  [229] = {.lex_state = 7},
  [230] = {.lex_state = 96},
  [231] = {.lex_state = 97},
  [232] = {.lex_state = 7},
  [233] = {.lex_state = 7},
  [234] = {.lex_state = 7},
  [235] = {.lex_state = 7},
  [236] = {.lex_state = 7},
  [237] = {.lex_state = 97},
  [238] = {.lex_state = 97},
  [239] = {.lex_state = 7},
  [240] = {.lex_state = 7},
  [241] = {.lex_state = 95},
  [242] = {.lex_state = 97},
  [243] = {.lex_state = 97},
  [244] = {.lex_state = 125},
  [245] = {.lex_state = 7},
  [246] = {.lex_state = 7},
  [247] = {.lex_state = 97},
  [248] = {.lex_state = 97},
  [249] = {.lex_state = 7},
  [250] = {.lex_state = 6},
  [251] = {.lex_state = 97},
  [252] = {.lex_state = 6},
  [253] = {.lex_state = 94},
  [254] = {.lex_state = 13},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [aux_sym_document_token1] = ACTIONS(1),
    [aux_sym__name_char_token1] = ACTIONS(1),
    [anon_sym_DOT] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [aux_sym__name_char_token2] = ACTIONS(1),
    [aux_sym__name_char_token3] = ACTIONS(1),
    [aux_sym__name_char_token4] = ACTIONS(1),
    [aux_sym__name_char_token5] = ACTIONS(1),
    [aux_sym__name_char_token6] = ACTIONS(1),
    [aux_sym__name_char_token7] = ACTIONS(1),
    [aux_sym__name_char_token8] = ACTIONS(1),
    [aux_sym__name_char_token9] = ACTIONS(1),
    [aux_sym__name_char_token10] = ACTIONS(1),
    [aux_sym__name_char_token11] = ACTIONS(1),
    [aux_sym__name_char_token12] = ACTIONS(1),
    [aux_sym__name_char_token13] = ACTIONS(1),
    [aux_sym__name_char_token14] = ACTIONS(1),
    [aux_sym__name_char_token15] = ACTIONS(1),
    [anon_sym__] = ACTIONS(1),
    [aux_sym_names_token1] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [anon_sym_SQUOTE] = ACTIONS(1),
    [aux_sym_attribute_value_token1] = ACTIONS(1),
    [sym_pubid_char] = ACTIONS(1),
    [anon_sym_LT_BANG_DASH_DASH] = ACTIONS(1),
    [anon_sym_LT_QMARK] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_LT_SLASH] = ACTIONS(1),
    [anon_sym_GT] = ACTIONS(1),
    [anon_sym_LT_BANG] = ACTIONS(1),
    [anon_sym_QMARK] = ACTIONS(1),
    [anon_sym_STAR] = ACTIONS(1),
    [anon_sym_PLUS] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_PIPE] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_AMP_POUND] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_AMP_POUNDx] = ACTIONS(1),
    [anon_sym_AMP] = ACTIONS(1),
    [anon_sym_PERCENT] = ACTIONS(1),
    [aux_sym__enc_name_token1] = ACTIONS(1),
    [aux_sym__enc_name_token2] = ACTIONS(1),
  },
  [1] = {
    [sym_document] = STATE(202),
    [sym_comment] = STATE(19),
    [sym_processing_instructions] = STATE(19),
    [sym__markup_decl] = STATE(19),
    [sym_element_decl] = STATE(19),
    [sym_attlist_decl] = STATE(19),
    [sym_pe_reference] = STATE(19),
    [sym_entity_decl] = STATE(19),
    [sym_ge_decl] = STATE(56),
    [sym_pe_decl] = STATE(56),
    [sym_notation_decl] = STATE(19),
    [aux_sym_document_repeat1] = STATE(19),
    [ts_builtin_sym_end] = ACTIONS(3),
    [aux_sym_document_token1] = ACTIONS(5),
    [anon_sym_LT_BANG_DASH_DASH] = ACTIONS(7),
    [anon_sym_LT_QMARK] = ACTIONS(9),
    [anon_sym_LT_BANG] = ACTIONS(11),
    [anon_sym_PERCENT] = ACTIONS(13),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 3,
    STATE(3), 2,
      sym__name_char,
      aux_sym__name_repeat1,
    ACTIONS(15), 7,
      aux_sym_document_token1,
      anon_sym_QMARK,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
    ACTIONS(17), 18,
      aux_sym__name_char_token1,
      anon_sym_DOT,
      anon_sym_DASH,
      anon_sym_COLON,
      aux_sym__name_char_token2,
      aux_sym__name_char_token3,
      aux_sym__name_char_token4,
      aux_sym__name_char_token5,
      aux_sym__name_char_token6,
      aux_sym__name_char_token7,
      aux_sym__name_char_token8,
      aux_sym__name_char_token9,
      aux_sym__name_char_token10,
      aux_sym__name_char_token11,
      aux_sym__name_char_token12,
      aux_sym__name_char_token13,
      aux_sym__name_char_token14,
      aux_sym__name_char_token15,
  [34] = 3,
    STATE(4), 2,
      sym__name_char,
      aux_sym__name_repeat1,
    ACTIONS(19), 7,
      aux_sym_document_token1,
      anon_sym_QMARK,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
    ACTIONS(21), 18,
      aux_sym__name_char_token1,
      anon_sym_DOT,
      anon_sym_DASH,
      anon_sym_COLON,
      aux_sym__name_char_token2,
      aux_sym__name_char_token3,
      aux_sym__name_char_token4,
      aux_sym__name_char_token5,
      aux_sym__name_char_token6,
      aux_sym__name_char_token7,
      aux_sym__name_char_token8,
      aux_sym__name_char_token9,
      aux_sym__name_char_token10,
      aux_sym__name_char_token11,
      aux_sym__name_char_token12,
      aux_sym__name_char_token13,
      aux_sym__name_char_token14,
      aux_sym__name_char_token15,
  [68] = 3,
    STATE(4), 2,
      sym__name_char,
      aux_sym__name_repeat1,
    ACTIONS(23), 7,
      aux_sym_document_token1,
      anon_sym_QMARK,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
    ACTIONS(25), 18,
      aux_sym__name_char_token1,
      anon_sym_DOT,
      anon_sym_DASH,
      anon_sym_COLON,
      aux_sym__name_char_token2,
      aux_sym__name_char_token3,
      aux_sym__name_char_token4,
      aux_sym__name_char_token5,
      aux_sym__name_char_token6,
      aux_sym__name_char_token7,
      aux_sym__name_char_token8,
      aux_sym__name_char_token9,
      aux_sym__name_char_token10,
      aux_sym__name_char_token11,
      aux_sym__name_char_token12,
      aux_sym__name_char_token13,
      aux_sym__name_char_token14,
      aux_sym__name_char_token15,
  [102] = 3,
    STATE(5), 2,
      sym__name_char,
      aux_sym__name_repeat1,
    ACTIONS(23), 6,
      aux_sym_names_token1,
      anon_sym_QMARK_GT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_RPAREN,
      anon_sym_SEMI,
    ACTIONS(28), 18,
      aux_sym__name_char_token1,
      anon_sym_DOT,
      anon_sym_DASH,
      anon_sym_COLON,
      aux_sym__name_char_token2,
      aux_sym__name_char_token3,
      aux_sym__name_char_token4,
      aux_sym__name_char_token5,
      aux_sym__name_char_token6,
      aux_sym__name_char_token7,
      aux_sym__name_char_token8,
      aux_sym__name_char_token9,
      aux_sym__name_char_token10,
      aux_sym__name_char_token11,
      aux_sym__name_char_token12,
      aux_sym__name_char_token13,
      aux_sym__name_char_token14,
      aux_sym__name_char_token15,
  [135] = 3,
    STATE(5), 2,
      sym__name_char,
      aux_sym__name_repeat1,
    ACTIONS(19), 6,
      aux_sym_names_token1,
      anon_sym_QMARK_GT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_RPAREN,
      anon_sym_SEMI,
    ACTIONS(31), 18,
      aux_sym__name_char_token1,
      anon_sym_DOT,
      anon_sym_DASH,
      anon_sym_COLON,
      aux_sym__name_char_token2,
      aux_sym__name_char_token3,
      aux_sym__name_char_token4,
      aux_sym__name_char_token5,
      aux_sym__name_char_token6,
      aux_sym__name_char_token7,
      aux_sym__name_char_token8,
      aux_sym__name_char_token9,
      aux_sym__name_char_token10,
      aux_sym__name_char_token11,
      aux_sym__name_char_token12,
      aux_sym__name_char_token13,
      aux_sym__name_char_token14,
      aux_sym__name_char_token15,
  [168] = 3,
    STATE(6), 2,
      sym__name_char,
      aux_sym__name_repeat1,
    ACTIONS(15), 4,
      aux_sym_names_token1,
      anon_sym_QMARK_GT,
      anon_sym_GT,
      anon_sym_SEMI,
    ACTIONS(33), 18,
      aux_sym__name_char_token1,
      anon_sym_DOT,
      anon_sym_DASH,
      anon_sym_COLON,
      aux_sym__name_char_token2,
      aux_sym__name_char_token3,
      aux_sym__name_char_token4,
      aux_sym__name_char_token5,
      aux_sym__name_char_token6,
      aux_sym__name_char_token7,
      aux_sym__name_char_token8,
      aux_sym__name_char_token9,
      aux_sym__name_char_token10,
      aux_sym__name_char_token11,
      aux_sym__name_char_token12,
      aux_sym__name_char_token13,
      aux_sym__name_char_token14,
      aux_sym__name_char_token15,
  [199] = 3,
    STATE(8), 2,
      sym__name_char,
      aux_sym__name_repeat1,
    ACTIONS(23), 3,
      aux_sym_names_token1,
      anon_sym_PIPE,
      anon_sym_RPAREN_STAR,
    ACTIONS(35), 18,
      aux_sym__name_char_token1,
      anon_sym_DOT,
      anon_sym_DASH,
      anon_sym_COLON,
      aux_sym__name_char_token2,
      aux_sym__name_char_token3,
      aux_sym__name_char_token4,
      aux_sym__name_char_token5,
      aux_sym__name_char_token6,
      aux_sym__name_char_token7,
      aux_sym__name_char_token8,
      aux_sym__name_char_token9,
      aux_sym__name_char_token10,
      aux_sym__name_char_token11,
      aux_sym__name_char_token12,
      aux_sym__name_char_token13,
      aux_sym__name_char_token14,
      aux_sym__name_char_token15,
  [229] = 3,
    STATE(6), 2,
      sym__name_char,
      aux_sym__name_repeat1,
    ACTIONS(15), 3,
      aux_sym_names_token1,
      anon_sym_PIPE,
      anon_sym_RPAREN,
    ACTIONS(33), 18,
      aux_sym__name_char_token1,
      anon_sym_DOT,
      anon_sym_DASH,
      anon_sym_COLON,
      aux_sym__name_char_token2,
      aux_sym__name_char_token3,
      aux_sym__name_char_token4,
      aux_sym__name_char_token5,
      aux_sym__name_char_token6,
      aux_sym__name_char_token7,
      aux_sym__name_char_token8,
      aux_sym__name_char_token9,
      aux_sym__name_char_token10,
      aux_sym__name_char_token11,
      aux_sym__name_char_token12,
      aux_sym__name_char_token13,
      aux_sym__name_char_token14,
      aux_sym__name_char_token15,
  [259] = 3,
    STATE(8), 2,
      sym__name_char,
      aux_sym__name_repeat1,
    ACTIONS(19), 3,
      aux_sym_names_token1,
      anon_sym_PIPE,
      anon_sym_RPAREN_STAR,
    ACTIONS(38), 18,
      aux_sym__name_char_token1,
      anon_sym_DOT,
      anon_sym_DASH,
      anon_sym_COLON,
      aux_sym__name_char_token2,
      aux_sym__name_char_token3,
      aux_sym__name_char_token4,
      aux_sym__name_char_token5,
      aux_sym__name_char_token6,
      aux_sym__name_char_token7,
      aux_sym__name_char_token8,
      aux_sym__name_char_token9,
      aux_sym__name_char_token10,
      aux_sym__name_char_token11,
      aux_sym__name_char_token12,
      aux_sym__name_char_token13,
      aux_sym__name_char_token14,
      aux_sym__name_char_token15,
  [289] = 3,
    STATE(10), 2,
      sym__name_char,
      aux_sym__name_repeat1,
    ACTIONS(15), 3,
      aux_sym_names_token1,
      anon_sym_PIPE,
      anon_sym_RPAREN_STAR,
    ACTIONS(40), 18,
      aux_sym__name_char_token1,
      anon_sym_DOT,
      anon_sym_DASH,
      anon_sym_COLON,
      aux_sym__name_char_token2,
      aux_sym__name_char_token3,
      aux_sym__name_char_token4,
      aux_sym__name_char_token5,
      aux_sym__name_char_token6,
      aux_sym__name_char_token7,
      aux_sym__name_char_token8,
      aux_sym__name_char_token9,
      aux_sym__name_char_token10,
      aux_sym__name_char_token11,
      aux_sym__name_char_token12,
      aux_sym__name_char_token13,
      aux_sym__name_char_token14,
      aux_sym__name_char_token15,
  [319] = 3,
    STATE(5), 2,
      sym__name_char,
      aux_sym__name_repeat1,
    ACTIONS(42), 3,
      aux_sym_names_token1,
      anon_sym_PIPE,
      anon_sym_RPAREN,
    ACTIONS(31), 18,
      aux_sym__name_char_token1,
      anon_sym_DOT,
      anon_sym_DASH,
      anon_sym_COLON,
      aux_sym__name_char_token2,
      aux_sym__name_char_token3,
      aux_sym__name_char_token4,
      aux_sym__name_char_token5,
      aux_sym__name_char_token6,
      aux_sym__name_char_token7,
      aux_sym__name_char_token8,
      aux_sym__name_char_token9,
      aux_sym__name_char_token10,
      aux_sym__name_char_token11,
      aux_sym__name_char_token12,
      aux_sym__name_char_token13,
      aux_sym__name_char_token14,
      aux_sym__name_char_token15,
  [349] = 4,
    ACTIONS(46), 1,
      aux_sym_names_token1,
    STATE(144), 1,
      sym_nm_token,
    STATE(12), 2,
      sym__name_char,
      aux_sym__name_repeat1,
    ACTIONS(44), 18,
      aux_sym__name_char_token1,
      anon_sym_DOT,
      anon_sym_DASH,
      anon_sym_COLON,
      aux_sym__name_char_token2,
      aux_sym__name_char_token3,
      aux_sym__name_char_token4,
      aux_sym__name_char_token5,
      aux_sym__name_char_token6,
      aux_sym__name_char_token7,
      aux_sym__name_char_token8,
      aux_sym__name_char_token9,
      aux_sym__name_char_token10,
      aux_sym__name_char_token11,
      aux_sym__name_char_token12,
      aux_sym__name_char_token13,
      aux_sym__name_char_token14,
      aux_sym__name_char_token15,
  [380] = 4,
    ACTIONS(48), 1,
      aux_sym_names_token1,
    STATE(152), 1,
      sym_nm_token,
    STATE(12), 2,
      sym__name_char,
      aux_sym__name_repeat1,
    ACTIONS(44), 18,
      aux_sym__name_char_token1,
      anon_sym_DOT,
      anon_sym_DASH,
      anon_sym_COLON,
      aux_sym__name_char_token2,
      aux_sym__name_char_token3,
      aux_sym__name_char_token4,
      aux_sym__name_char_token5,
      aux_sym__name_char_token6,
      aux_sym__name_char_token7,
      aux_sym__name_char_token8,
      aux_sym__name_char_token9,
      aux_sym__name_char_token10,
      aux_sym__name_char_token11,
      aux_sym__name_char_token12,
      aux_sym__name_char_token13,
      aux_sym__name_char_token14,
      aux_sym__name_char_token15,
  [411] = 4,
    ACTIONS(50), 1,
      aux_sym_names_token1,
    STATE(125), 1,
      sym_nm_token,
    STATE(12), 2,
      sym__name_char,
      aux_sym__name_repeat1,
    ACTIONS(44), 18,
      aux_sym__name_char_token1,
      anon_sym_DOT,
      anon_sym_DASH,
      anon_sym_COLON,
      aux_sym__name_char_token2,
      aux_sym__name_char_token3,
      aux_sym__name_char_token4,
      aux_sym__name_char_token5,
      aux_sym__name_char_token6,
      aux_sym__name_char_token7,
      aux_sym__name_char_token8,
      aux_sym__name_char_token9,
      aux_sym__name_char_token10,
      aux_sym__name_char_token11,
      aux_sym__name_char_token12,
      aux_sym__name_char_token13,
      aux_sym__name_char_token14,
      aux_sym__name_char_token15,
  [442] = 3,
    STATE(144), 1,
      sym_nm_token,
    STATE(12), 2,
      sym__name_char,
      aux_sym__name_repeat1,
    ACTIONS(44), 18,
      aux_sym__name_char_token1,
      anon_sym_DOT,
      anon_sym_DASH,
      anon_sym_COLON,
      aux_sym__name_char_token2,
      aux_sym__name_char_token3,
      aux_sym__name_char_token4,
      aux_sym__name_char_token5,
      aux_sym__name_char_token6,
      aux_sym__name_char_token7,
      aux_sym__name_char_token8,
      aux_sym__name_char_token9,
      aux_sym__name_char_token10,
      aux_sym__name_char_token11,
      aux_sym__name_char_token12,
      aux_sym__name_char_token13,
      aux_sym__name_char_token14,
      aux_sym__name_char_token15,
  [470] = 3,
    STATE(141), 1,
      sym_nm_token,
    STATE(12), 2,
      sym__name_char,
      aux_sym__name_repeat1,
    ACTIONS(44), 18,
      aux_sym__name_char_token1,
      anon_sym_DOT,
      anon_sym_DASH,
      anon_sym_COLON,
      aux_sym__name_char_token2,
      aux_sym__name_char_token3,
      aux_sym__name_char_token4,
      aux_sym__name_char_token5,
      aux_sym__name_char_token6,
      aux_sym__name_char_token7,
      aux_sym__name_char_token8,
      aux_sym__name_char_token9,
      aux_sym__name_char_token10,
      aux_sym__name_char_token11,
      aux_sym__name_char_token12,
      aux_sym__name_char_token13,
      aux_sym__name_char_token14,
      aux_sym__name_char_token15,
  [498] = 3,
    STATE(105), 1,
      sym_nm_token,
    STATE(12), 2,
      sym__name_char,
      aux_sym__name_repeat1,
    ACTIONS(44), 18,
      aux_sym__name_char_token1,
      anon_sym_DOT,
      anon_sym_DASH,
      anon_sym_COLON,
      aux_sym__name_char_token2,
      aux_sym__name_char_token3,
      aux_sym__name_char_token4,
      aux_sym__name_char_token5,
      aux_sym__name_char_token6,
      aux_sym__name_char_token7,
      aux_sym__name_char_token8,
      aux_sym__name_char_token9,
      aux_sym__name_char_token10,
      aux_sym__name_char_token11,
      aux_sym__name_char_token12,
      aux_sym__name_char_token13,
      aux_sym__name_char_token14,
      aux_sym__name_char_token15,
  [526] = 8,
    ACTIONS(7), 1,
      anon_sym_LT_BANG_DASH_DASH,
    ACTIONS(9), 1,
      anon_sym_LT_QMARK,
    ACTIONS(11), 1,
      anon_sym_LT_BANG,
    ACTIONS(13), 1,
      anon_sym_PERCENT,
    ACTIONS(52), 1,
      ts_builtin_sym_end,
    ACTIONS(54), 1,
      aux_sym_document_token1,
    STATE(56), 2,
      sym_ge_decl,
      sym_pe_decl,
    STATE(20), 9,
      sym_comment,
      sym_processing_instructions,
      sym__markup_decl,
      sym_element_decl,
      sym_attlist_decl,
      sym_pe_reference,
      sym_entity_decl,
      sym_notation_decl,
      aux_sym_document_repeat1,
  [560] = 8,
    ACTIONS(56), 1,
      ts_builtin_sym_end,
    ACTIONS(58), 1,
      aux_sym_document_token1,
    ACTIONS(61), 1,
      anon_sym_LT_BANG_DASH_DASH,
    ACTIONS(64), 1,
      anon_sym_LT_QMARK,
    ACTIONS(67), 1,
      anon_sym_LT_BANG,
    ACTIONS(70), 1,
      anon_sym_PERCENT,
    STATE(56), 2,
      sym_ge_decl,
      sym_pe_decl,
    STATE(20), 9,
      sym_comment,
      sym_processing_instructions,
      sym__markup_decl,
      sym_element_decl,
      sym_attlist_decl,
      sym_pe_reference,
      sym_entity_decl,
      sym_notation_decl,
      aux_sym_document_repeat1,
  [594] = 6,
    ACTIONS(73), 1,
      anon_sym_LPAREN,
    ACTIONS(79), 1,
      anon_sym_NOTATION,
    STATE(222), 1,
      sym_attribute_type,
    ACTIONS(77), 3,
      anon_sym_ID,
      anon_sym_IDREF,
      anon_sym_NMTOKEN,
    STATE(214), 4,
      sym__tokenized_type,
      sym__enumerated_type,
      sym_notation_type,
      sym_enumeration,
    ACTIONS(75), 5,
      sym__string_type,
      anon_sym_IDREFS,
      anon_sym_ENTITY,
      anon_sym_ENTITIES,
      anon_sym_NMTOKENS,
  [622] = 8,
    ACTIONS(81), 1,
      aux_sym_document_token1,
    ACTIONS(83), 1,
      aux_sym__name_char_token1,
    ACTIONS(87), 1,
      aux_sym_names_token1,
    ACTIONS(89), 1,
      anon_sym_LPAREN,
    ACTIONS(91), 1,
      anon_sym_POUNDPCDATA,
    STATE(68), 1,
      sym_cp,
    ACTIONS(85), 2,
      anon_sym_COLON,
      anon_sym__,
    STATE(49), 3,
      sym__name,
      sym_element_choice,
      sym_element_seq,
  [650] = 7,
    ACTIONS(93), 1,
      anon_sym_DQUOTE,
    ACTIONS(95), 1,
      aux_sym_attribute_value_token1,
    ACTIONS(97), 1,
      anon_sym_AMP_POUND,
    ACTIONS(99), 1,
      anon_sym_AMP_POUNDx,
    ACTIONS(101), 1,
      anon_sym_AMP,
    STATE(26), 2,
      sym_reference,
      aux_sym_attribute_value_repeat1,
    STATE(78), 2,
      sym_char_ref,
      sym_entity_ref,
  [674] = 6,
    ACTIONS(83), 1,
      aux_sym__name_char_token1,
    ACTIONS(89), 1,
      anon_sym_LPAREN,
    ACTIONS(103), 1,
      aux_sym_document_token1,
    STATE(162), 1,
      sym_cp,
    ACTIONS(85), 2,
      anon_sym_COLON,
      anon_sym__,
    STATE(49), 3,
      sym__name,
      sym_element_choice,
      sym_element_seq,
  [696] = 7,
    ACTIONS(105), 1,
      anon_sym_SQUOTE,
    ACTIONS(107), 1,
      aux_sym_attribute_value_token2,
    ACTIONS(110), 1,
      anon_sym_AMP_POUND,
    ACTIONS(113), 1,
      anon_sym_AMP_POUNDx,
    ACTIONS(116), 1,
      anon_sym_AMP,
    STATE(25), 2,
      sym_reference,
      aux_sym_attribute_value_repeat2,
    STATE(76), 2,
      sym_char_ref,
      sym_entity_ref,
  [720] = 7,
    ACTIONS(119), 1,
      anon_sym_DQUOTE,
    ACTIONS(121), 1,
      aux_sym_attribute_value_token1,
    ACTIONS(124), 1,
      anon_sym_AMP_POUND,
    ACTIONS(127), 1,
      anon_sym_AMP_POUNDx,
    ACTIONS(130), 1,
      anon_sym_AMP,
    STATE(26), 2,
      sym_reference,
      aux_sym_attribute_value_repeat1,
    STATE(78), 2,
      sym_char_ref,
      sym_entity_ref,
  [744] = 6,
    ACTIONS(83), 1,
      aux_sym__name_char_token1,
    ACTIONS(89), 1,
      anon_sym_LPAREN,
    ACTIONS(133), 1,
      aux_sym_document_token1,
    STATE(138), 1,
      sym_cp,
    ACTIONS(85), 2,
      anon_sym_COLON,
      anon_sym__,
    STATE(49), 3,
      sym__name,
      sym_element_choice,
      sym_element_seq,
  [766] = 6,
    ACTIONS(83), 1,
      aux_sym__name_char_token1,
    ACTIONS(89), 1,
      anon_sym_LPAREN,
    ACTIONS(135), 1,
      aux_sym_document_token1,
    STATE(143), 1,
      sym_cp,
    ACTIONS(85), 2,
      anon_sym_COLON,
      anon_sym__,
    STATE(49), 3,
      sym__name,
      sym_element_choice,
      sym_element_seq,
  [788] = 7,
    ACTIONS(93), 1,
      anon_sym_SQUOTE,
    ACTIONS(137), 1,
      aux_sym_attribute_value_token2,
    ACTIONS(139), 1,
      anon_sym_AMP_POUND,
    ACTIONS(141), 1,
      anon_sym_AMP_POUNDx,
    ACTIONS(143), 1,
      anon_sym_AMP,
    STATE(25), 2,
      sym_reference,
      aux_sym_attribute_value_repeat2,
    STATE(76), 2,
      sym_char_ref,
      sym_entity_ref,
  [812] = 7,
    ACTIONS(139), 1,
      anon_sym_AMP_POUND,
    ACTIONS(141), 1,
      anon_sym_AMP_POUNDx,
    ACTIONS(143), 1,
      anon_sym_AMP,
    ACTIONS(145), 1,
      anon_sym_SQUOTE,
    ACTIONS(147), 1,
      aux_sym_attribute_value_token2,
    STATE(29), 2,
      sym_reference,
      aux_sym_attribute_value_repeat2,
    STATE(76), 2,
      sym_char_ref,
      sym_entity_ref,
  [836] = 7,
    ACTIONS(97), 1,
      anon_sym_AMP_POUND,
    ACTIONS(99), 1,
      anon_sym_AMP_POUNDx,
    ACTIONS(101), 1,
      anon_sym_AMP,
    ACTIONS(145), 1,
      anon_sym_DQUOTE,
    ACTIONS(149), 1,
      aux_sym_attribute_value_token1,
    STATE(23), 2,
      sym_reference,
      aux_sym_attribute_value_repeat1,
    STATE(78), 2,
      sym_char_ref,
      sym_entity_ref,
  [860] = 6,
    ACTIONS(81), 1,
      aux_sym_document_token1,
    ACTIONS(83), 1,
      aux_sym__name_char_token1,
    ACTIONS(89), 1,
      anon_sym_LPAREN,
    STATE(68), 1,
      sym_cp,
    ACTIONS(85), 2,
      anon_sym_COLON,
      anon_sym__,
    STATE(49), 3,
      sym__name,
      sym_element_choice,
      sym_element_seq,
  [882] = 6,
    ACTIONS(83), 1,
      aux_sym__name_char_token1,
    ACTIONS(89), 1,
      anon_sym_LPAREN,
    ACTIONS(151), 1,
      aux_sym_document_token1,
    STATE(156), 1,
      sym_cp,
    ACTIONS(85), 2,
      anon_sym_COLON,
      anon_sym__,
    STATE(49), 3,
      sym__name,
      sym_element_choice,
      sym_element_seq,
  [904] = 1,
    ACTIONS(153), 8,
      aux_sym_document_token1,
      anon_sym_GT,
      anon_sym_QMARK,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [915] = 1,
    ACTIONS(155), 8,
      aux_sym_document_token1,
      anon_sym_GT,
      anon_sym_QMARK,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [926] = 5,
    ACTIONS(83), 1,
      aux_sym__name_char_token1,
    ACTIONS(89), 1,
      anon_sym_LPAREN,
    STATE(154), 1,
      sym_cp,
    ACTIONS(85), 2,
      anon_sym_COLON,
      anon_sym__,
    STATE(49), 3,
      sym__name,
      sym_element_choice,
      sym_element_seq,
  [945] = 5,
    ACTIONS(83), 1,
      aux_sym__name_char_token1,
    ACTIONS(89), 1,
      anon_sym_LPAREN,
    STATE(67), 1,
      sym_cp,
    ACTIONS(85), 2,
      anon_sym_COLON,
      anon_sym__,
    STATE(49), 3,
      sym__name,
      sym_element_choice,
      sym_element_seq,
  [964] = 5,
    ACTIONS(83), 1,
      aux_sym__name_char_token1,
    ACTIONS(89), 1,
      anon_sym_LPAREN,
    STATE(162), 1,
      sym_cp,
    ACTIONS(85), 2,
      anon_sym_COLON,
      anon_sym__,
    STATE(49), 3,
      sym__name,
      sym_element_choice,
      sym_element_seq,
  [983] = 5,
    ACTIONS(159), 1,
      anon_sym_LPAREN,
    STATE(173), 1,
      sym_content_spec,
    ACTIONS(157), 2,
      anon_sym_EMPTY,
      anon_sym_ANY,
    STATE(85), 2,
      sym_element_choice,
      sym_element_seq,
    STATE(164), 2,
      sym_children,
      sym_mixed,
  [1002] = 5,
    ACTIONS(83), 1,
      aux_sym__name_char_token1,
    ACTIONS(89), 1,
      anon_sym_LPAREN,
    STATE(134), 1,
      sym_cp,
    ACTIONS(85), 2,
      anon_sym_COLON,
      anon_sym__,
    STATE(49), 3,
      sym__name,
      sym_element_choice,
      sym_element_seq,
  [1021] = 1,
    ACTIONS(161), 8,
      aux_sym_document_token1,
      anon_sym_GT,
      anon_sym_QMARK,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1032] = 1,
    ACTIONS(163), 8,
      aux_sym_document_token1,
      anon_sym_GT,
      anon_sym_QMARK,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1043] = 5,
    ACTIONS(83), 1,
      aux_sym__name_char_token1,
    ACTIONS(89), 1,
      anon_sym_LPAREN,
    STATE(156), 1,
      sym_cp,
    ACTIONS(85), 2,
      anon_sym_COLON,
      anon_sym__,
    STATE(49), 3,
      sym__name,
      sym_element_choice,
      sym_element_seq,
  [1062] = 1,
    ACTIONS(165), 8,
      aux_sym_document_token1,
      anon_sym_GT,
      anon_sym_QMARK,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1073] = 1,
    ACTIONS(167), 8,
      aux_sym_document_token1,
      anon_sym_GT,
      anon_sym_QMARK,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1084] = 1,
    ACTIONS(169), 8,
      aux_sym_document_token1,
      anon_sym_GT,
      anon_sym_QMARK,
      anon_sym_STAR,
      anon_sym_PLUS,
      anon_sym_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1095] = 6,
    ACTIONS(171), 1,
      anon_sym_DQUOTE,
    ACTIONS(173), 1,
      anon_sym_SQUOTE,
    ACTIONS(177), 1,
      anon_sym_POUNDFIXED,
    STATE(179), 1,
      sym_attribute_value,
    STATE(181), 1,
      sym_default_decl,
    ACTIONS(175), 2,
      anon_sym_POUNDREQUIRED,
      anon_sym_POUNDIMPLIED,
  [1115] = 5,
    ACTIONS(181), 1,
      anon_sym_SYSTEM,
    ACTIONS(183), 1,
      anon_sym_PUBLIC,
    STATE(175), 1,
      sym_pe_def,
    ACTIONS(179), 2,
      anon_sym_DQUOTE,
      anon_sym_SQUOTE,
    STATE(176), 2,
      sym_entity_value,
      sym_external_id,
  [1133] = 2,
    ACTIONS(187), 3,
      anon_sym_QMARK,
      anon_sym_STAR,
      anon_sym_PLUS,
    ACTIONS(185), 4,
      aux_sym_document_token1,
      anon_sym_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1145] = 6,
    ACTIONS(181), 1,
      anon_sym_SYSTEM,
    ACTIONS(183), 1,
      anon_sym_PUBLIC,
    STATE(146), 1,
      sym_external_id,
    STATE(180), 1,
      sym_entity_value,
    STATE(187), 1,
      sym_entity_def,
    ACTIONS(179), 2,
      anon_sym_DQUOTE,
      anon_sym_SQUOTE,
  [1165] = 2,
    ACTIONS(191), 1,
      anon_sym_LT_BANG,
    ACTIONS(189), 5,
      ts_builtin_sym_end,
      aux_sym_document_token1,
      anon_sym_LT_BANG_DASH_DASH,
      anon_sym_LT_QMARK,
      anon_sym_PERCENT,
  [1176] = 2,
    ACTIONS(195), 1,
      anon_sym_LT_BANG,
    ACTIONS(193), 5,
      ts_builtin_sym_end,
      aux_sym_document_token1,
      anon_sym_LT_BANG_DASH_DASH,
      anon_sym_LT_QMARK,
      anon_sym_PERCENT,
  [1187] = 2,
    ACTIONS(199), 1,
      anon_sym_LT_BANG,
    ACTIONS(197), 5,
      ts_builtin_sym_end,
      aux_sym_document_token1,
      anon_sym_LT_BANG_DASH_DASH,
      anon_sym_LT_QMARK,
      anon_sym_PERCENT,
  [1198] = 2,
    ACTIONS(203), 1,
      anon_sym_LT_BANG,
    ACTIONS(201), 5,
      ts_builtin_sym_end,
      aux_sym_document_token1,
      anon_sym_LT_BANG_DASH_DASH,
      anon_sym_LT_QMARK,
      anon_sym_PERCENT,
  [1209] = 2,
    ACTIONS(207), 1,
      anon_sym_LT_BANG,
    ACTIONS(205), 5,
      ts_builtin_sym_end,
      aux_sym_document_token1,
      anon_sym_LT_BANG_DASH_DASH,
      anon_sym_LT_QMARK,
      anon_sym_PERCENT,
  [1220] = 2,
    ACTIONS(211), 1,
      anon_sym_LT_BANG,
    ACTIONS(209), 5,
      ts_builtin_sym_end,
      aux_sym_document_token1,
      anon_sym_LT_BANG_DASH_DASH,
      anon_sym_LT_QMARK,
      anon_sym_PERCENT,
  [1231] = 2,
    ACTIONS(215), 1,
      anon_sym_LT_BANG,
    ACTIONS(213), 5,
      ts_builtin_sym_end,
      aux_sym_document_token1,
      anon_sym_LT_BANG_DASH_DASH,
      anon_sym_LT_QMARK,
      anon_sym_PERCENT,
  [1242] = 2,
    ACTIONS(219), 1,
      anon_sym_LT_BANG,
    ACTIONS(217), 5,
      ts_builtin_sym_end,
      aux_sym_document_token1,
      anon_sym_LT_BANG_DASH_DASH,
      anon_sym_LT_QMARK,
      anon_sym_PERCENT,
  [1253] = 2,
    ACTIONS(223), 1,
      anon_sym_LT_BANG,
    ACTIONS(221), 5,
      ts_builtin_sym_end,
      aux_sym_document_token1,
      anon_sym_LT_BANG_DASH_DASH,
      anon_sym_LT_QMARK,
      anon_sym_PERCENT,
  [1264] = 2,
    ACTIONS(227), 1,
      anon_sym_LT_BANG,
    ACTIONS(225), 5,
      ts_builtin_sym_end,
      aux_sym_document_token1,
      anon_sym_LT_BANG_DASH_DASH,
      anon_sym_LT_QMARK,
      anon_sym_PERCENT,
  [1275] = 2,
    ACTIONS(231), 1,
      anon_sym_LT_BANG,
    ACTIONS(229), 5,
      ts_builtin_sym_end,
      aux_sym_document_token1,
      anon_sym_LT_BANG_DASH_DASH,
      anon_sym_LT_QMARK,
      anon_sym_PERCENT,
  [1286] = 2,
    ACTIONS(235), 1,
      anon_sym_LT_BANG,
    ACTIONS(233), 5,
      ts_builtin_sym_end,
      aux_sym_document_token1,
      anon_sym_LT_BANG_DASH_DASH,
      anon_sym_LT_QMARK,
      anon_sym_PERCENT,
  [1297] = 2,
    ACTIONS(239), 1,
      anon_sym_LT_BANG,
    ACTIONS(237), 5,
      ts_builtin_sym_end,
      aux_sym_document_token1,
      anon_sym_LT_BANG_DASH_DASH,
      anon_sym_LT_QMARK,
      anon_sym_PERCENT,
  [1308] = 2,
    ACTIONS(243), 1,
      anon_sym_LT_BANG,
    ACTIONS(241), 5,
      ts_builtin_sym_end,
      aux_sym_document_token1,
      anon_sym_LT_BANG_DASH_DASH,
      anon_sym_LT_QMARK,
      anon_sym_PERCENT,
  [1319] = 2,
    ACTIONS(247), 1,
      anon_sym_LT_BANG,
    ACTIONS(245), 5,
      ts_builtin_sym_end,
      aux_sym_document_token1,
      anon_sym_LT_BANG_DASH_DASH,
      anon_sym_LT_QMARK,
      anon_sym_PERCENT,
  [1330] = 2,
    ACTIONS(251), 1,
      anon_sym_LT_BANG,
    ACTIONS(249), 5,
      ts_builtin_sym_end,
      aux_sym_document_token1,
      anon_sym_LT_BANG_DASH_DASH,
      anon_sym_LT_QMARK,
      anon_sym_PERCENT,
  [1341] = 6,
    ACTIONS(253), 1,
      aux_sym_document_token1,
    ACTIONS(255), 1,
      anon_sym_PIPE,
    ACTIONS(257), 1,
      anon_sym_RPAREN,
    ACTIONS(259), 1,
      anon_sym_COMMA,
    STATE(117), 1,
      aux_sym_element_choice_repeat1,
    STATE(118), 1,
      aux_sym_element_seq_repeat1,
  [1360] = 6,
    ACTIONS(255), 1,
      anon_sym_PIPE,
    ACTIONS(259), 1,
      anon_sym_COMMA,
    ACTIONS(261), 1,
      aux_sym_document_token1,
    ACTIONS(263), 1,
      anon_sym_RPAREN,
    STATE(98), 1,
      aux_sym_element_choice_repeat1,
    STATE(99), 1,
      aux_sym_element_seq_repeat1,
  [1379] = 2,
    ACTIONS(267), 1,
      anon_sym_LT_BANG,
    ACTIONS(265), 5,
      ts_builtin_sym_end,
      aux_sym_document_token1,
      anon_sym_LT_BANG_DASH_DASH,
      anon_sym_LT_QMARK,
      anon_sym_PERCENT,
  [1390] = 2,
    ACTIONS(271), 2,
      anon_sym_AMP_POUND,
      anon_sym_AMP,
    ACTIONS(269), 3,
      anon_sym_DQUOTE,
      aux_sym_attribute_value_token1,
      anon_sym_AMP_POUNDx,
  [1400] = 4,
    ACTIONS(273), 1,
      aux_sym__name_char_token1,
    ACTIONS(277), 1,
      aux_sym_names_token1,
    STATE(142), 1,
      sym__name,
    ACTIONS(275), 2,
      anon_sym_COLON,
      anon_sym__,
  [1414] = 4,
    ACTIONS(279), 1,
      aux_sym__name_char_token1,
    STATE(166), 1,
      sym__name,
    STATE(167), 1,
      sym_pi_target,
    ACTIONS(281), 2,
      anon_sym_COLON,
      anon_sym__,
  [1428] = 2,
    ACTIONS(271), 2,
      anon_sym_AMP_POUND,
      anon_sym_AMP,
    ACTIONS(269), 3,
      anon_sym_SQUOTE,
      aux_sym_attribute_value_token2,
      anon_sym_AMP_POUNDx,
  [1438] = 4,
    ACTIONS(273), 1,
      aux_sym__name_char_token1,
    ACTIONS(283), 1,
      aux_sym_names_token1,
    STATE(159), 1,
      sym__name,
    ACTIONS(275), 2,
      anon_sym_COLON,
      anon_sym__,
  [1452] = 2,
    ACTIONS(287), 2,
      anon_sym_AMP_POUND,
      anon_sym_AMP,
    ACTIONS(285), 3,
      anon_sym_SQUOTE,
      aux_sym_attribute_value_token2,
      anon_sym_AMP_POUNDx,
  [1462] = 2,
    ACTIONS(291), 2,
      anon_sym_AMP_POUND,
      anon_sym_AMP,
    ACTIONS(289), 3,
      anon_sym_SQUOTE,
      aux_sym_attribute_value_token2,
      anon_sym_AMP_POUNDx,
  [1472] = 4,
    ACTIONS(279), 1,
      aux_sym__name_char_token1,
    ACTIONS(293), 1,
      anon_sym_PERCENT,
    STATE(234), 1,
      sym__name,
    ACTIONS(281), 2,
      anon_sym_COLON,
      anon_sym__,
  [1486] = 2,
    ACTIONS(291), 2,
      anon_sym_AMP_POUND,
      anon_sym_AMP,
    ACTIONS(289), 3,
      anon_sym_DQUOTE,
      aux_sym_attribute_value_token1,
      anon_sym_AMP_POUNDx,
  [1496] = 2,
    ACTIONS(287), 2,
      anon_sym_AMP_POUND,
      anon_sym_AMP,
    ACTIONS(285), 3,
      anon_sym_DQUOTE,
      aux_sym_attribute_value_token1,
      anon_sym_AMP_POUNDx,
  [1506] = 4,
    ACTIONS(295), 1,
      aux_sym__name_char_token1,
    ACTIONS(299), 1,
      aux_sym_names_token1,
    STATE(120), 1,
      sym__name,
    ACTIONS(297), 2,
      anon_sym_COLON,
      anon_sym__,
  [1520] = 4,
    ACTIONS(295), 1,
      aux_sym__name_char_token1,
    ACTIONS(301), 1,
      aux_sym_names_token1,
    STATE(140), 1,
      sym__name,
    ACTIONS(297), 2,
      anon_sym_COLON,
      anon_sym__,
  [1534] = 4,
    ACTIONS(279), 1,
      aux_sym__name_char_token1,
    ACTIONS(303), 1,
      anon_sym_GT,
    STATE(239), 1,
      sym__name,
    ACTIONS(281), 2,
      anon_sym_COLON,
      anon_sym__,
  [1548] = 4,
    ACTIONS(295), 1,
      aux_sym__name_char_token1,
    ACTIONS(305), 1,
      aux_sym_names_token1,
    STATE(139), 1,
      sym__name,
    ACTIONS(297), 2,
      anon_sym_COLON,
      anon_sym__,
  [1562] = 4,
    ACTIONS(279), 1,
      aux_sym__name_char_token1,
    ACTIONS(307), 1,
      anon_sym_GT,
    STATE(239), 1,
      sym__name,
    ACTIONS(281), 2,
      anon_sym_COLON,
      anon_sym__,
  [1576] = 2,
    ACTIONS(309), 2,
      aux_sym_document_token1,
      anon_sym_GT,
    ACTIONS(311), 3,
      anon_sym_QMARK,
      anon_sym_STAR,
      anon_sym_PLUS,
  [1586] = 5,
    ACTIONS(313), 1,
      aux_sym_names_token1,
    ACTIONS(315), 1,
      anon_sym_PIPE,
    ACTIONS(317), 1,
      anon_sym_RPAREN,
    ACTIONS(319), 1,
      anon_sym_RPAREN_STAR,
    STATE(121), 1,
      aux_sym_mixed_repeat1,
  [1602] = 5,
    ACTIONS(315), 1,
      anon_sym_PIPE,
    ACTIONS(321), 1,
      aux_sym_names_token1,
    ACTIONS(323), 1,
      anon_sym_RPAREN,
    ACTIONS(325), 1,
      anon_sym_RPAREN_STAR,
    STATE(93), 1,
      aux_sym_mixed_repeat1,
  [1618] = 3,
    ACTIONS(295), 1,
      aux_sym__name_char_token1,
    STATE(139), 1,
      sym__name,
    ACTIONS(297), 2,
      anon_sym_COLON,
      anon_sym__,
  [1629] = 4,
    ACTIONS(327), 1,
      aux_sym_names_token1,
    ACTIONS(329), 1,
      anon_sym_PIPE,
    ACTIONS(331), 1,
      anon_sym_RPAREN,
    STATE(102), 1,
      aux_sym_enumeration_repeat1,
  [1642] = 3,
    ACTIONS(333), 1,
      aux_sym_names_token1,
    ACTIONS(336), 1,
      anon_sym_GT,
    STATE(90), 2,
      sym_attribute_def,
      aux_sym_attlist_decl_repeat1,
  [1653] = 3,
    ACTIONS(338), 1,
      anon_sym_DQUOTE,
    STATE(91), 1,
      aux_sym_pubid_literal_repeat1,
    ACTIONS(340), 2,
      anon_sym_SQUOTE,
      sym_pubid_char,
  [1664] = 4,
    ACTIONS(343), 1,
      aux_sym_names_token1,
    ACTIONS(345), 1,
      anon_sym_PIPE,
    ACTIONS(347), 1,
      anon_sym_RPAREN,
    STATE(101), 1,
      aux_sym_notation_type_repeat1,
  [1677] = 4,
    ACTIONS(315), 1,
      anon_sym_PIPE,
    ACTIONS(319), 1,
      anon_sym_RPAREN_STAR,
    ACTIONS(349), 1,
      aux_sym_names_token1,
    STATE(126), 1,
      aux_sym_mixed_repeat1,
  [1690] = 1,
    ACTIONS(351), 4,
      aux_sym_document_token1,
      anon_sym_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1697] = 4,
    ACTIONS(171), 1,
      anon_sym_DQUOTE,
    ACTIONS(173), 1,
      anon_sym_SQUOTE,
    ACTIONS(353), 1,
      aux_sym_names_token1,
    STATE(194), 1,
      sym_attribute_value,
  [1710] = 3,
    ACTIONS(181), 1,
      anon_sym_SYSTEM,
    ACTIONS(355), 1,
      anon_sym_PUBLIC,
    STATE(199), 2,
      sym_external_id,
      sym_public_id,
  [1721] = 3,
    ACTIONS(279), 1,
      aux_sym__name_char_token1,
    STATE(223), 1,
      sym__name,
    ACTIONS(281), 2,
      anon_sym_COLON,
      anon_sym__,
  [1732] = 4,
    ACTIONS(255), 1,
      anon_sym_PIPE,
    ACTIONS(357), 1,
      aux_sym_document_token1,
    ACTIONS(359), 1,
      anon_sym_RPAREN,
    STATE(132), 1,
      aux_sym_element_choice_repeat1,
  [1745] = 4,
    ACTIONS(257), 1,
      anon_sym_RPAREN,
    ACTIONS(259), 1,
      anon_sym_COMMA,
    ACTIONS(361), 1,
      aux_sym_document_token1,
    STATE(133), 1,
      aux_sym_element_seq_repeat1,
  [1758] = 3,
    ACTIONS(303), 1,
      anon_sym_GT,
    ACTIONS(363), 1,
      aux_sym_names_token1,
    STATE(90), 2,
      sym_attribute_def,
      aux_sym_attlist_decl_repeat1,
  [1769] = 4,
    ACTIONS(365), 1,
      aux_sym_names_token1,
    ACTIONS(368), 1,
      anon_sym_PIPE,
    ACTIONS(371), 1,
      anon_sym_RPAREN,
    STATE(101), 1,
      aux_sym_notation_type_repeat1,
  [1782] = 4,
    ACTIONS(373), 1,
      aux_sym_names_token1,
    ACTIONS(376), 1,
      anon_sym_PIPE,
    ACTIONS(379), 1,
      anon_sym_RPAREN,
    STATE(102), 1,
      aux_sym_enumeration_repeat1,
  [1795] = 4,
    ACTIONS(329), 1,
      anon_sym_PIPE,
    ACTIONS(381), 1,
      aux_sym_names_token1,
    ACTIONS(383), 1,
      anon_sym_RPAREN,
    STATE(102), 1,
      aux_sym_enumeration_repeat1,
  [1808] = 4,
    ACTIONS(343), 1,
      aux_sym_names_token1,
    ACTIONS(345), 1,
      anon_sym_PIPE,
    ACTIONS(385), 1,
      anon_sym_RPAREN,
    STATE(92), 1,
      aux_sym_notation_type_repeat1,
  [1821] = 4,
    ACTIONS(329), 1,
      anon_sym_PIPE,
    ACTIONS(381), 1,
      aux_sym_names_token1,
    ACTIONS(383), 1,
      anon_sym_RPAREN,
    STATE(89), 1,
      aux_sym_enumeration_repeat1,
  [1834] = 3,
    ACTIONS(387), 1,
      aux_sym_names_token1,
    ACTIONS(389), 1,
      anon_sym_GT,
    STATE(100), 2,
      sym_attribute_def,
      aux_sym_attlist_decl_repeat1,
  [1845] = 3,
    ACTIONS(295), 1,
      aux_sym__name_char_token1,
    STATE(137), 1,
      sym__name,
    ACTIONS(297), 2,
      anon_sym_COLON,
      anon_sym__,
  [1856] = 3,
    ACTIONS(391), 1,
      anon_sym_DQUOTE,
    STATE(115), 1,
      aux_sym_pubid_literal_repeat1,
    ACTIONS(393), 2,
      anon_sym_SQUOTE,
      sym_pubid_char,
  [1867] = 3,
    ACTIONS(273), 1,
      aux_sym__name_char_token1,
    STATE(157), 1,
      sym__name,
    ACTIONS(275), 2,
      anon_sym_COLON,
      anon_sym__,
  [1878] = 3,
    ACTIONS(279), 1,
      aux_sym__name_char_token1,
    STATE(233), 1,
      sym__name,
    ACTIONS(281), 2,
      anon_sym_COLON,
      anon_sym__,
  [1889] = 4,
    ACTIONS(343), 1,
      aux_sym_names_token1,
    ACTIONS(345), 1,
      anon_sym_PIPE,
    ACTIONS(395), 1,
      anon_sym_RPAREN,
    STATE(101), 1,
      aux_sym_notation_type_repeat1,
  [1902] = 3,
    ACTIONS(279), 1,
      aux_sym__name_char_token1,
    STATE(106), 1,
      sym__name,
    ACTIONS(281), 2,
      anon_sym_COLON,
      anon_sym__,
  [1913] = 3,
    ACTIONS(279), 1,
      aux_sym__name_char_token1,
    STATE(186), 1,
      sym__name,
    ACTIONS(281), 2,
      anon_sym_COLON,
      anon_sym__,
  [1924] = 3,
    ACTIONS(83), 1,
      aux_sym__name_char_token1,
    STATE(237), 1,
      sym__name,
    ACTIONS(85), 2,
      anon_sym_COLON,
      anon_sym__,
  [1935] = 3,
    ACTIONS(397), 1,
      anon_sym_DQUOTE,
    STATE(91), 1,
      aux_sym_pubid_literal_repeat1,
    ACTIONS(399), 2,
      anon_sym_SQUOTE,
      sym_pubid_char,
  [1946] = 4,
    ACTIONS(401), 1,
      anon_sym_DASH,
    ACTIONS(404), 1,
      aux_sym_comment_token1,
    ACTIONS(407), 1,
      anon_sym_DASH_DASH_GT,
    STATE(116), 1,
      aux_sym_comment_repeat1,
  [1959] = 4,
    ACTIONS(255), 1,
      anon_sym_PIPE,
    ACTIONS(409), 1,
      aux_sym_document_token1,
    ACTIONS(411), 1,
      anon_sym_RPAREN,
    STATE(132), 1,
      aux_sym_element_choice_repeat1,
  [1972] = 4,
    ACTIONS(259), 1,
      anon_sym_COMMA,
    ACTIONS(413), 1,
      aux_sym_document_token1,
    ACTIONS(415), 1,
      anon_sym_RPAREN,
    STATE(133), 1,
      aux_sym_element_seq_repeat1,
  [1985] = 3,
    ACTIONS(279), 1,
      aux_sym__name_char_token1,
    STATE(220), 1,
      sym__name,
    ACTIONS(281), 2,
      anon_sym_COLON,
      anon_sym__,
  [1996] = 4,
    ACTIONS(343), 1,
      aux_sym_names_token1,
    ACTIONS(345), 1,
      anon_sym_PIPE,
    ACTIONS(417), 1,
      anon_sym_RPAREN,
    STATE(111), 1,
      aux_sym_notation_type_repeat1,
  [2009] = 4,
    ACTIONS(315), 1,
      anon_sym_PIPE,
    ACTIONS(419), 1,
      aux_sym_names_token1,
    ACTIONS(421), 1,
      anon_sym_RPAREN_STAR,
    STATE(126), 1,
      aux_sym_mixed_repeat1,
  [2022] = 3,
    ACTIONS(279), 1,
      aux_sym__name_char_token1,
    STATE(239), 1,
      sym__name,
    ACTIONS(281), 2,
      anon_sym_COLON,
      anon_sym__,
  [2033] = 3,
    ACTIONS(273), 1,
      aux_sym__name_char_token1,
    STATE(159), 1,
      sym__name,
    ACTIONS(275), 2,
      anon_sym_COLON,
      anon_sym__,
  [2044] = 4,
    ACTIONS(423), 1,
      anon_sym_DASH,
    ACTIONS(425), 1,
      aux_sym_comment_token1,
    ACTIONS(427), 1,
      anon_sym_DASH_DASH_GT,
    STATE(127), 1,
      aux_sym_comment_repeat1,
  [2057] = 4,
    ACTIONS(329), 1,
      anon_sym_PIPE,
    ACTIONS(429), 1,
      aux_sym_names_token1,
    ACTIONS(431), 1,
      anon_sym_RPAREN,
    STATE(103), 1,
      aux_sym_enumeration_repeat1,
  [2070] = 4,
    ACTIONS(433), 1,
      aux_sym_names_token1,
    ACTIONS(436), 1,
      anon_sym_PIPE,
    ACTIONS(439), 1,
      anon_sym_RPAREN_STAR,
    STATE(126), 1,
      aux_sym_mixed_repeat1,
  [2083] = 4,
    ACTIONS(423), 1,
      anon_sym_DASH,
    ACTIONS(441), 1,
      aux_sym_comment_token1,
    ACTIONS(443), 1,
      anon_sym_DASH_DASH_GT,
    STATE(116), 1,
      aux_sym_comment_repeat1,
  [2096] = 3,
    ACTIONS(279), 1,
      aux_sym__name_char_token1,
    STATE(251), 1,
      sym__name,
    ACTIONS(281), 2,
      anon_sym_COLON,
      anon_sym__,
  [2107] = 3,
    ACTIONS(279), 1,
      aux_sym__name_char_token1,
    STATE(243), 1,
      sym__name,
    ACTIONS(281), 2,
      anon_sym_COLON,
      anon_sym__,
  [2118] = 4,
    ACTIONS(445), 1,
      anon_sym_ELEMENT,
    ACTIONS(447), 1,
      anon_sym_ATTLIST,
    ACTIONS(449), 1,
      anon_sym_ENTITY,
    ACTIONS(451), 1,
      anon_sym_NOTATION,
  [2131] = 3,
    ACTIONS(295), 1,
      aux_sym__name_char_token1,
    STATE(104), 1,
      sym__name,
    ACTIONS(297), 2,
      anon_sym_COLON,
      anon_sym__,
  [2142] = 4,
    ACTIONS(453), 1,
      aux_sym_document_token1,
    ACTIONS(456), 1,
      anon_sym_PIPE,
    ACTIONS(459), 1,
      anon_sym_RPAREN,
    STATE(132), 1,
      aux_sym_element_choice_repeat1,
  [2155] = 4,
    ACTIONS(461), 1,
      aux_sym_document_token1,
    ACTIONS(464), 1,
      anon_sym_RPAREN,
    ACTIONS(466), 1,
      anon_sym_COMMA,
    STATE(133), 1,
      aux_sym_element_seq_repeat1,
  [2168] = 1,
    ACTIONS(469), 3,
      aux_sym_document_token1,
      anon_sym_PIPE,
      anon_sym_RPAREN,
  [2174] = 3,
    ACTIONS(317), 1,
      anon_sym_RPAREN,
    ACTIONS(319), 1,
      anon_sym_RPAREN_STAR,
    ACTIONS(471), 1,
      anon_sym_PIPE,
  [2184] = 2,
    ACTIONS(473), 1,
      anon_sym_DASH,
    ACTIONS(407), 2,
      aux_sym_comment_token1,
      anon_sym_DASH_DASH_GT,
  [2192] = 1,
    ACTIONS(475), 3,
      aux_sym_names_token1,
      anon_sym_PIPE,
      anon_sym_RPAREN,
  [2198] = 1,
    ACTIONS(459), 3,
      aux_sym_document_token1,
      anon_sym_PIPE,
      anon_sym_RPAREN,
  [2204] = 1,
    ACTIONS(477), 3,
      aux_sym_names_token1,
      anon_sym_PIPE,
      anon_sym_RPAREN,
  [2210] = 1,
    ACTIONS(479), 3,
      aux_sym_names_token1,
      anon_sym_PIPE,
      anon_sym_RPAREN,
  [2216] = 1,
    ACTIONS(481), 3,
      aux_sym_names_token1,
      anon_sym_PIPE,
      anon_sym_RPAREN,
  [2222] = 1,
    ACTIONS(439), 3,
      aux_sym_names_token1,
      anon_sym_PIPE,
      anon_sym_RPAREN_STAR,
  [2228] = 1,
    ACTIONS(464), 3,
      aux_sym_document_token1,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [2234] = 1,
    ACTIONS(483), 3,
      aux_sym_names_token1,
      anon_sym_PIPE,
      anon_sym_RPAREN,
  [2240] = 3,
    ACTIONS(171), 1,
      anon_sym_DQUOTE,
    ACTIONS(173), 1,
      anon_sym_SQUOTE,
    STATE(163), 1,
      sym_attribute_value,
  [2250] = 2,
    STATE(193), 1,
      sym_ndata_decl,
    ACTIONS(485), 2,
      aux_sym_names_token1,
      anon_sym_GT,
  [2258] = 3,
    ACTIONS(487), 1,
      anon_sym_DQUOTE,
    ACTIONS(489), 1,
      anon_sym_SQUOTE,
    STATE(168), 1,
      sym_system_literal,
  [2268] = 3,
    ACTIONS(421), 1,
      anon_sym_RPAREN_STAR,
    ACTIONS(471), 1,
      anon_sym_PIPE,
    ACTIONS(491), 1,
      anon_sym_RPAREN,
  [2278] = 3,
    ACTIONS(397), 1,
      anon_sym_SQUOTE,
    ACTIONS(493), 1,
      sym_pubid_char,
    STATE(160), 1,
      aux_sym_pubid_literal_repeat2,
  [2288] = 3,
    ACTIONS(487), 1,
      anon_sym_DQUOTE,
    ACTIONS(489), 1,
      anon_sym_SQUOTE,
    STATE(185), 1,
      sym_system_literal,
  [2298] = 3,
    ACTIONS(415), 1,
      anon_sym_RPAREN,
    ACTIONS(495), 1,
      anon_sym_PIPE,
    ACTIONS(497), 1,
      anon_sym_COMMA,
  [2308] = 1,
    ACTIONS(379), 3,
      aux_sym_names_token1,
      anon_sym_PIPE,
      anon_sym_RPAREN,
  [2314] = 3,
    ACTIONS(499), 1,
      anon_sym_DQUOTE,
    ACTIONS(501), 1,
      anon_sym_SQUOTE,
    STATE(249), 1,
      sym_pubid_literal,
  [2324] = 1,
    ACTIONS(503), 3,
      aux_sym_document_token1,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [2330] = 3,
    ACTIONS(499), 1,
      anon_sym_DQUOTE,
    ACTIONS(501), 1,
      anon_sym_SQUOTE,
    STATE(197), 1,
      sym_pubid_literal,
  [2340] = 1,
    ACTIONS(505), 3,
      aux_sym_document_token1,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [2346] = 1,
    ACTIONS(507), 3,
      aux_sym_names_token1,
      anon_sym_PIPE,
      anon_sym_RPAREN_STAR,
  [2352] = 3,
    ACTIONS(257), 1,
      anon_sym_RPAREN,
    ACTIONS(495), 1,
      anon_sym_PIPE,
    ACTIONS(497), 1,
      anon_sym_COMMA,
  [2362] = 1,
    ACTIONS(509), 3,
      aux_sym_names_token1,
      anon_sym_PIPE,
      anon_sym_RPAREN_STAR,
  [2368] = 3,
    ACTIONS(511), 1,
      anon_sym_SQUOTE,
    ACTIONS(513), 1,
      sym_pubid_char,
    STATE(160), 1,
      aux_sym_pubid_literal_repeat2,
  [2378] = 3,
    ACTIONS(391), 1,
      anon_sym_SQUOTE,
    ACTIONS(516), 1,
      sym_pubid_char,
    STATE(149), 1,
      aux_sym_pubid_literal_repeat2,
  [2388] = 1,
    ACTIONS(518), 3,
      aux_sym_document_token1,
      anon_sym_PIPE,
      anon_sym_RPAREN,
  [2394] = 1,
    ACTIONS(520), 2,
      aux_sym_names_token1,
      anon_sym_GT,
  [2399] = 1,
    ACTIONS(522), 2,
      aux_sym_document_token1,
      anon_sym_GT,
  [2404] = 2,
    ACTIONS(471), 1,
      anon_sym_PIPE,
    ACTIONS(524), 1,
      anon_sym_RPAREN_STAR,
  [2411] = 1,
    ACTIONS(526), 2,
      aux_sym_names_token1,
      anon_sym_QMARK_GT,
  [2416] = 2,
    ACTIONS(528), 1,
      aux_sym_names_token1,
    ACTIONS(530), 1,
      anon_sym_QMARK_GT,
  [2423] = 1,
    ACTIONS(532), 2,
      aux_sym_names_token1,
      anon_sym_GT,
  [2428] = 2,
    ACTIONS(411), 1,
      anon_sym_RPAREN,
    ACTIONS(495), 1,
      anon_sym_PIPE,
  [2435] = 2,
    ACTIONS(421), 1,
      anon_sym_RPAREN_STAR,
    ACTIONS(471), 1,
      anon_sym_PIPE,
  [2442] = 1,
    ACTIONS(534), 2,
      aux_sym_document_token1,
      anon_sym_GT,
  [2447] = 2,
    ACTIONS(383), 1,
      anon_sym_RPAREN,
    ACTIONS(536), 1,
      anon_sym_PIPE,
  [2454] = 2,
    ACTIONS(538), 1,
      aux_sym_document_token1,
    ACTIONS(540), 1,
      anon_sym_GT,
  [2461] = 1,
    ACTIONS(542), 2,
      aux_sym_document_token1,
      anon_sym_GT,
  [2466] = 2,
    ACTIONS(544), 1,
      aux_sym_names_token1,
    ACTIONS(546), 1,
      anon_sym_GT,
  [2473] = 1,
    ACTIONS(548), 2,
      aux_sym_names_token1,
      anon_sym_GT,
  [2478] = 1,
    ACTIONS(550), 2,
      aux_sym_names_token1,
      anon_sym_GT,
  [2483] = 1,
    ACTIONS(552), 2,
      aux_sym_names_token1,
      anon_sym_GT,
  [2488] = 1,
    ACTIONS(554), 2,
      aux_sym_names_token1,
      anon_sym_GT,
  [2493] = 1,
    ACTIONS(485), 2,
      aux_sym_names_token1,
      anon_sym_GT,
  [2498] = 1,
    ACTIONS(556), 2,
      aux_sym_names_token1,
      anon_sym_GT,
  [2503] = 1,
    ACTIONS(558), 2,
      aux_sym_names_token1,
      anon_sym_GT,
  [2508] = 1,
    ACTIONS(560), 2,
      aux_sym_names_token1,
      anon_sym_GT,
  [2513] = 1,
    ACTIONS(562), 2,
      aux_sym_document_token1,
      anon_sym_GT,
  [2518] = 1,
    ACTIONS(564), 2,
      aux_sym_names_token1,
      anon_sym_GT,
  [2523] = 1,
    ACTIONS(566), 2,
      aux_sym_names_token1,
      anon_sym_GT,
  [2528] = 2,
    ACTIONS(568), 1,
      aux_sym_names_token1,
    ACTIONS(570), 1,
      anon_sym_GT,
  [2535] = 1,
    ACTIONS(572), 2,
      aux_sym_document_token1,
      anon_sym_GT,
  [2540] = 2,
    ACTIONS(415), 1,
      anon_sym_RPAREN,
    ACTIONS(497), 1,
      anon_sym_COMMA,
  [2547] = 2,
    ACTIONS(497), 1,
      anon_sym_COMMA,
    ACTIONS(574), 1,
      anon_sym_RPAREN,
  [2554] = 2,
    ACTIONS(331), 1,
      anon_sym_RPAREN,
    ACTIONS(536), 1,
      anon_sym_PIPE,
  [2561] = 2,
    ACTIONS(536), 1,
      anon_sym_PIPE,
    ACTIONS(576), 1,
      anon_sym_RPAREN,
  [2568] = 1,
    ACTIONS(578), 2,
      aux_sym_names_token1,
      anon_sym_GT,
  [2573] = 1,
    ACTIONS(580), 2,
      aux_sym_names_token1,
      anon_sym_GT,
  [2578] = 1,
    ACTIONS(582), 2,
      aux_sym_names_token1,
      anon_sym_GT,
  [2583] = 2,
    ACTIONS(495), 1,
      anon_sym_PIPE,
    ACTIONS(584), 1,
      anon_sym_RPAREN,
  [2590] = 1,
    ACTIONS(586), 2,
      aux_sym_names_token1,
      anon_sym_GT,
  [2595] = 1,
    ACTIONS(588), 2,
      aux_sym_document_token1,
      anon_sym_GT,
  [2600] = 2,
    ACTIONS(590), 1,
      aux_sym_names_token1,
    ACTIONS(592), 1,
      anon_sym_GT,
  [2607] = 1,
    ACTIONS(594), 2,
      aux_sym_names_token1,
      anon_sym_GT,
  [2612] = 1,
    ACTIONS(596), 1,
      aux_sym_names_token1,
  [2616] = 1,
    ACTIONS(598), 1,
      ts_builtin_sym_end,
  [2620] = 1,
    ACTIONS(600), 1,
      anon_sym_POUNDPCDATA,
  [2624] = 1,
    ACTIONS(602), 1,
      anon_sym_GT,
  [2628] = 1,
    ACTIONS(604), 1,
      aux_sym_names_token1,
  [2632] = 1,
    ACTIONS(606), 1,
      aux_sym_names_token1,
  [2636] = 1,
    ACTIONS(608), 1,
      anon_sym_SQUOTE,
  [2640] = 1,
    ACTIONS(610), 1,
      anon_sym_GT,
  [2644] = 1,
    ACTIONS(612), 1,
      aux_sym_names_token1,
  [2648] = 1,
    ACTIONS(614), 1,
      aux_sym_names_token1,
  [2652] = 1,
    ACTIONS(616), 1,
      anon_sym_GT,
  [2656] = 1,
    ACTIONS(608), 1,
      anon_sym_DQUOTE,
  [2660] = 1,
    ACTIONS(536), 1,
      anon_sym_PIPE,
  [2664] = 1,
    ACTIONS(618), 1,
      aux_sym_names_token1,
  [2668] = 1,
    ACTIONS(620), 1,
      anon_sym_PIPE,
  [2672] = 1,
    ACTIONS(622), 1,
      aux_sym_names_token1,
  [2676] = 1,
    ACTIONS(624), 1,
      aux_sym_names_token1,
  [2680] = 1,
    ACTIONS(626), 1,
      aux_sym_names_token1,
  [2684] = 1,
    ACTIONS(628), 1,
      anon_sym_SEMI,
  [2688] = 1,
    ACTIONS(630), 1,
      anon_sym_SEMI,
  [2692] = 1,
    ACTIONS(632), 1,
      aux_sym_names_token1,
  [2696] = 1,
    ACTIONS(634), 1,
      aux_sym_names_token1,
  [2700] = 1,
    ACTIONS(636), 1,
      aux_sym_names_token1,
  [2704] = 1,
    ACTIONS(638), 1,
      aux_sym_names_token1,
  [2708] = 1,
    ACTIONS(640), 1,
      aux_sym_names_token1,
  [2712] = 1,
    ACTIONS(642), 1,
      anon_sym_GT,
  [2716] = 1,
    ACTIONS(644), 1,
      anon_sym_SEMI,
  [2720] = 1,
    ACTIONS(646), 1,
      aux_sym_char_ref_token2,
  [2724] = 1,
    ACTIONS(648), 1,
      aux_sym_names_token1,
  [2728] = 1,
    ACTIONS(650), 1,
      aux_sym_system_literal_token2,
  [2732] = 1,
    ACTIONS(652), 1,
      anon_sym_LPAREN,
  [2736] = 1,
    ACTIONS(654), 1,
      aux_sym_names_token1,
  [2740] = 1,
    ACTIONS(656), 1,
      aux_sym_names_token1,
  [2744] = 1,
    ACTIONS(658), 1,
      aux_sym_names_token1,
  [2748] = 1,
    ACTIONS(660), 1,
      aux_sym_names_token1,
  [2752] = 1,
    ACTIONS(662), 1,
      aux_sym_names_token1,
  [2756] = 1,
    ACTIONS(664), 1,
      aux_sym_document_token1,
  [2760] = 1,
    ACTIONS(497), 1,
      anon_sym_COMMA,
  [2764] = 1,
    ACTIONS(666), 1,
      aux_sym_names_token1,
  [2768] = 1,
    ACTIONS(668), 1,
      anon_sym_QMARK_GT,
  [2772] = 1,
    ACTIONS(670), 1,
      aux_sym_processing_instructions_token1,
  [2776] = 1,
    ACTIONS(495), 1,
      anon_sym_PIPE,
  [2780] = 1,
    ACTIONS(672), 1,
      anon_sym_SEMI,
  [2784] = 1,
    ACTIONS(674), 1,
      aux_sym_system_literal_token1,
  [2788] = 1,
    ACTIONS(676), 1,
      aux_sym_names_token1,
  [2792] = 1,
    ACTIONS(678), 1,
      aux_sym_names_token1,
  [2796] = 1,
    ACTIONS(680), 1,
      aux_sym_document_token1,
  [2800] = 1,
    ACTIONS(471), 1,
      anon_sym_PIPE,
  [2804] = 1,
    ACTIONS(682), 1,
      aux_sym_names_token1,
  [2808] = 1,
    ACTIONS(646), 1,
      aux_sym_char_ref_token1,
  [2812] = 1,
    ACTIONS(684), 1,
      anon_sym_SEMI,
  [2816] = 1,
    ACTIONS(686), 1,
      aux_sym_char_ref_token1,
  [2820] = 1,
    ACTIONS(686), 1,
      aux_sym_char_ref_token2,
  [2824] = 1,
    ACTIONS(688), 1,
      aux_sym_comment_token1,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 34,
  [SMALL_STATE(4)] = 68,
  [SMALL_STATE(5)] = 102,
  [SMALL_STATE(6)] = 135,
  [SMALL_STATE(7)] = 168,
  [SMALL_STATE(8)] = 199,
  [SMALL_STATE(9)] = 229,
  [SMALL_STATE(10)] = 259,
  [SMALL_STATE(11)] = 289,
  [SMALL_STATE(12)] = 319,
  [SMALL_STATE(13)] = 349,
  [SMALL_STATE(14)] = 380,
  [SMALL_STATE(15)] = 411,
  [SMALL_STATE(16)] = 442,
  [SMALL_STATE(17)] = 470,
  [SMALL_STATE(18)] = 498,
  [SMALL_STATE(19)] = 526,
  [SMALL_STATE(20)] = 560,
  [SMALL_STATE(21)] = 594,
  [SMALL_STATE(22)] = 622,
  [SMALL_STATE(23)] = 650,
  [SMALL_STATE(24)] = 674,
  [SMALL_STATE(25)] = 696,
  [SMALL_STATE(26)] = 720,
  [SMALL_STATE(27)] = 744,
  [SMALL_STATE(28)] = 766,
  [SMALL_STATE(29)] = 788,
  [SMALL_STATE(30)] = 812,
  [SMALL_STATE(31)] = 836,
  [SMALL_STATE(32)] = 860,
  [SMALL_STATE(33)] = 882,
  [SMALL_STATE(34)] = 904,
  [SMALL_STATE(35)] = 915,
  [SMALL_STATE(36)] = 926,
  [SMALL_STATE(37)] = 945,
  [SMALL_STATE(38)] = 964,
  [SMALL_STATE(39)] = 983,
  [SMALL_STATE(40)] = 1002,
  [SMALL_STATE(41)] = 1021,
  [SMALL_STATE(42)] = 1032,
  [SMALL_STATE(43)] = 1043,
  [SMALL_STATE(44)] = 1062,
  [SMALL_STATE(45)] = 1073,
  [SMALL_STATE(46)] = 1084,
  [SMALL_STATE(47)] = 1095,
  [SMALL_STATE(48)] = 1115,
  [SMALL_STATE(49)] = 1133,
  [SMALL_STATE(50)] = 1145,
  [SMALL_STATE(51)] = 1165,
  [SMALL_STATE(52)] = 1176,
  [SMALL_STATE(53)] = 1187,
  [SMALL_STATE(54)] = 1198,
  [SMALL_STATE(55)] = 1209,
  [SMALL_STATE(56)] = 1220,
  [SMALL_STATE(57)] = 1231,
  [SMALL_STATE(58)] = 1242,
  [SMALL_STATE(59)] = 1253,
  [SMALL_STATE(60)] = 1264,
  [SMALL_STATE(61)] = 1275,
  [SMALL_STATE(62)] = 1286,
  [SMALL_STATE(63)] = 1297,
  [SMALL_STATE(64)] = 1308,
  [SMALL_STATE(65)] = 1319,
  [SMALL_STATE(66)] = 1330,
  [SMALL_STATE(67)] = 1341,
  [SMALL_STATE(68)] = 1360,
  [SMALL_STATE(69)] = 1379,
  [SMALL_STATE(70)] = 1390,
  [SMALL_STATE(71)] = 1400,
  [SMALL_STATE(72)] = 1414,
  [SMALL_STATE(73)] = 1428,
  [SMALL_STATE(74)] = 1438,
  [SMALL_STATE(75)] = 1452,
  [SMALL_STATE(76)] = 1462,
  [SMALL_STATE(77)] = 1472,
  [SMALL_STATE(78)] = 1486,
  [SMALL_STATE(79)] = 1496,
  [SMALL_STATE(80)] = 1506,
  [SMALL_STATE(81)] = 1520,
  [SMALL_STATE(82)] = 1534,
  [SMALL_STATE(83)] = 1548,
  [SMALL_STATE(84)] = 1562,
  [SMALL_STATE(85)] = 1576,
  [SMALL_STATE(86)] = 1586,
  [SMALL_STATE(87)] = 1602,
  [SMALL_STATE(88)] = 1618,
  [SMALL_STATE(89)] = 1629,
  [SMALL_STATE(90)] = 1642,
  [SMALL_STATE(91)] = 1653,
  [SMALL_STATE(92)] = 1664,
  [SMALL_STATE(93)] = 1677,
  [SMALL_STATE(94)] = 1690,
  [SMALL_STATE(95)] = 1697,
  [SMALL_STATE(96)] = 1710,
  [SMALL_STATE(97)] = 1721,
  [SMALL_STATE(98)] = 1732,
  [SMALL_STATE(99)] = 1745,
  [SMALL_STATE(100)] = 1758,
  [SMALL_STATE(101)] = 1769,
  [SMALL_STATE(102)] = 1782,
  [SMALL_STATE(103)] = 1795,
  [SMALL_STATE(104)] = 1808,
  [SMALL_STATE(105)] = 1821,
  [SMALL_STATE(106)] = 1834,
  [SMALL_STATE(107)] = 1845,
  [SMALL_STATE(108)] = 1856,
  [SMALL_STATE(109)] = 1867,
  [SMALL_STATE(110)] = 1878,
  [SMALL_STATE(111)] = 1889,
  [SMALL_STATE(112)] = 1902,
  [SMALL_STATE(113)] = 1913,
  [SMALL_STATE(114)] = 1924,
  [SMALL_STATE(115)] = 1935,
  [SMALL_STATE(116)] = 1946,
  [SMALL_STATE(117)] = 1959,
  [SMALL_STATE(118)] = 1972,
  [SMALL_STATE(119)] = 1985,
  [SMALL_STATE(120)] = 1996,
  [SMALL_STATE(121)] = 2009,
  [SMALL_STATE(122)] = 2022,
  [SMALL_STATE(123)] = 2033,
  [SMALL_STATE(124)] = 2044,
  [SMALL_STATE(125)] = 2057,
  [SMALL_STATE(126)] = 2070,
  [SMALL_STATE(127)] = 2083,
  [SMALL_STATE(128)] = 2096,
  [SMALL_STATE(129)] = 2107,
  [SMALL_STATE(130)] = 2118,
  [SMALL_STATE(131)] = 2131,
  [SMALL_STATE(132)] = 2142,
  [SMALL_STATE(133)] = 2155,
  [SMALL_STATE(134)] = 2168,
  [SMALL_STATE(135)] = 2174,
  [SMALL_STATE(136)] = 2184,
  [SMALL_STATE(137)] = 2192,
  [SMALL_STATE(138)] = 2198,
  [SMALL_STATE(139)] = 2204,
  [SMALL_STATE(140)] = 2210,
  [SMALL_STATE(141)] = 2216,
  [SMALL_STATE(142)] = 2222,
  [SMALL_STATE(143)] = 2228,
  [SMALL_STATE(144)] = 2234,
  [SMALL_STATE(145)] = 2240,
  [SMALL_STATE(146)] = 2250,
  [SMALL_STATE(147)] = 2258,
  [SMALL_STATE(148)] = 2268,
  [SMALL_STATE(149)] = 2278,
  [SMALL_STATE(150)] = 2288,
  [SMALL_STATE(151)] = 2298,
  [SMALL_STATE(152)] = 2308,
  [SMALL_STATE(153)] = 2314,
  [SMALL_STATE(154)] = 2324,
  [SMALL_STATE(155)] = 2330,
  [SMALL_STATE(156)] = 2340,
  [SMALL_STATE(157)] = 2346,
  [SMALL_STATE(158)] = 2352,
  [SMALL_STATE(159)] = 2362,
  [SMALL_STATE(160)] = 2368,
  [SMALL_STATE(161)] = 2378,
  [SMALL_STATE(162)] = 2388,
  [SMALL_STATE(163)] = 2394,
  [SMALL_STATE(164)] = 2399,
  [SMALL_STATE(165)] = 2404,
  [SMALL_STATE(166)] = 2411,
  [SMALL_STATE(167)] = 2416,
  [SMALL_STATE(168)] = 2423,
  [SMALL_STATE(169)] = 2428,
  [SMALL_STATE(170)] = 2435,
  [SMALL_STATE(171)] = 2442,
  [SMALL_STATE(172)] = 2447,
  [SMALL_STATE(173)] = 2454,
  [SMALL_STATE(174)] = 2461,
  [SMALL_STATE(175)] = 2466,
  [SMALL_STATE(176)] = 2473,
  [SMALL_STATE(177)] = 2478,
  [SMALL_STATE(178)] = 2483,
  [SMALL_STATE(179)] = 2488,
  [SMALL_STATE(180)] = 2493,
  [SMALL_STATE(181)] = 2498,
  [SMALL_STATE(182)] = 2503,
  [SMALL_STATE(183)] = 2508,
  [SMALL_STATE(184)] = 2513,
  [SMALL_STATE(185)] = 2518,
  [SMALL_STATE(186)] = 2523,
  [SMALL_STATE(187)] = 2528,
  [SMALL_STATE(188)] = 2535,
  [SMALL_STATE(189)] = 2540,
  [SMALL_STATE(190)] = 2547,
  [SMALL_STATE(191)] = 2554,
  [SMALL_STATE(192)] = 2561,
  [SMALL_STATE(193)] = 2568,
  [SMALL_STATE(194)] = 2573,
  [SMALL_STATE(195)] = 2578,
  [SMALL_STATE(196)] = 2583,
  [SMALL_STATE(197)] = 2590,
  [SMALL_STATE(198)] = 2595,
  [SMALL_STATE(199)] = 2600,
  [SMALL_STATE(200)] = 2607,
  [SMALL_STATE(201)] = 2612,
  [SMALL_STATE(202)] = 2616,
  [SMALL_STATE(203)] = 2620,
  [SMALL_STATE(204)] = 2624,
  [SMALL_STATE(205)] = 2628,
  [SMALL_STATE(206)] = 2632,
  [SMALL_STATE(207)] = 2636,
  [SMALL_STATE(208)] = 2640,
  [SMALL_STATE(209)] = 2644,
  [SMALL_STATE(210)] = 2648,
  [SMALL_STATE(211)] = 2652,
  [SMALL_STATE(212)] = 2656,
  [SMALL_STATE(213)] = 2660,
  [SMALL_STATE(214)] = 2664,
  [SMALL_STATE(215)] = 2668,
  [SMALL_STATE(216)] = 2672,
  [SMALL_STATE(217)] = 2676,
  [SMALL_STATE(218)] = 2680,
  [SMALL_STATE(219)] = 2684,
  [SMALL_STATE(220)] = 2688,
  [SMALL_STATE(221)] = 2692,
  [SMALL_STATE(222)] = 2696,
  [SMALL_STATE(223)] = 2700,
  [SMALL_STATE(224)] = 2704,
  [SMALL_STATE(225)] = 2708,
  [SMALL_STATE(226)] = 2712,
  [SMALL_STATE(227)] = 2716,
  [SMALL_STATE(228)] = 2720,
  [SMALL_STATE(229)] = 2724,
  [SMALL_STATE(230)] = 2728,
  [SMALL_STATE(231)] = 2732,
  [SMALL_STATE(232)] = 2736,
  [SMALL_STATE(233)] = 2740,
  [SMALL_STATE(234)] = 2744,
  [SMALL_STATE(235)] = 2748,
  [SMALL_STATE(236)] = 2752,
  [SMALL_STATE(237)] = 2756,
  [SMALL_STATE(238)] = 2760,
  [SMALL_STATE(239)] = 2764,
  [SMALL_STATE(240)] = 2768,
  [SMALL_STATE(241)] = 2772,
  [SMALL_STATE(242)] = 2776,
  [SMALL_STATE(243)] = 2780,
  [SMALL_STATE(244)] = 2784,
  [SMALL_STATE(245)] = 2788,
  [SMALL_STATE(246)] = 2792,
  [SMALL_STATE(247)] = 2796,
  [SMALL_STATE(248)] = 2800,
  [SMALL_STATE(249)] = 2804,
  [SMALL_STATE(250)] = 2808,
  [SMALL_STATE(251)] = 2812,
  [SMALL_STATE(252)] = 2816,
  [SMALL_STATE(253)] = 2820,
  [SMALL_STATE(254)] = 2824,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_document, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(124),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [11] = {.entry = {.count = 1, .reusable = false}}, SHIFT(130),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(129),
  [15] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__name, 1),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [19] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__name, 2),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [23] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__name_repeat1, 2),
  [25] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__name_repeat1, 2), SHIFT_REPEAT(4),
  [28] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__name_repeat1, 2), SHIFT_REPEAT(5),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [35] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__name_repeat1, 2), SHIFT_REPEAT(8),
  [38] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [40] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [42] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_nm_token, 1),
  [44] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [46] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [48] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [50] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [52] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_document, 1),
  [54] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [56] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2),
  [58] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2), SHIFT_REPEAT(20),
  [61] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2), SHIFT_REPEAT(124),
  [64] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2), SHIFT_REPEAT(72),
  [67] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_document_repeat1, 2), SHIFT_REPEAT(130),
  [70] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2), SHIFT_REPEAT(129),
  [73] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [75] = {.entry = {.count = 1, .reusable = true}}, SHIFT(214),
  [77] = {.entry = {.count = 1, .reusable = false}}, SHIFT(214),
  [79] = {.entry = {.count = 1, .reusable = true}}, SHIFT(221),
  [81] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [83] = {.entry = {.count = 1, .reusable = false}}, SHIFT(2),
  [85] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [87] = {.entry = {.count = 1, .reusable = false}}, SHIFT(203),
  [89] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [91] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [93] = {.entry = {.count = 1, .reusable = true}}, SHIFT(178),
  [95] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [97] = {.entry = {.count = 1, .reusable = false}}, SHIFT(250),
  [99] = {.entry = {.count = 1, .reusable = true}}, SHIFT(228),
  [101] = {.entry = {.count = 1, .reusable = false}}, SHIFT(119),
  [103] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_attribute_value_repeat2, 2),
  [107] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_attribute_value_repeat2, 2), SHIFT_REPEAT(25),
  [110] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_attribute_value_repeat2, 2), SHIFT_REPEAT(252),
  [113] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_attribute_value_repeat2, 2), SHIFT_REPEAT(253),
  [116] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_attribute_value_repeat2, 2), SHIFT_REPEAT(128),
  [119] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_attribute_value_repeat1, 2),
  [121] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_attribute_value_repeat1, 2), SHIFT_REPEAT(26),
  [124] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_attribute_value_repeat1, 2), SHIFT_REPEAT(250),
  [127] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_attribute_value_repeat1, 2), SHIFT_REPEAT(228),
  [130] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_attribute_value_repeat1, 2), SHIFT_REPEAT(119),
  [133] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [135] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [137] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [139] = {.entry = {.count = 1, .reusable = false}}, SHIFT(252),
  [141] = {.entry = {.count = 1, .reusable = true}}, SHIFT(253),
  [143] = {.entry = {.count = 1, .reusable = false}}, SHIFT(128),
  [145] = {.entry = {.count = 1, .reusable = true}}, SHIFT(200),
  [147] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [149] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [151] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [153] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_element_choice, 5),
  [155] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_element_choice, 4),
  [157] = {.entry = {.count = 1, .reusable = true}}, SHIFT(164),
  [159] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [161] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_element_seq, 3),
  [163] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_element_seq, 4),
  [165] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_element_seq, 5),
  [167] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_element_choice, 6),
  [169] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_element_seq, 6),
  [171] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [173] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [175] = {.entry = {.count = 1, .reusable = true}}, SHIFT(179),
  [177] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [179] = {.entry = {.count = 1, .reusable = true}}, SHIFT(177),
  [181] = {.entry = {.count = 1, .reusable = true}}, SHIFT(218),
  [183] = {.entry = {.count = 1, .reusable = true}}, SHIFT(216),
  [185] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cp, 1),
  [187] = {.entry = {.count = 1, .reusable = true}}, SHIFT(94),
  [189] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attlist_decl, 6, .production_id = 1),
  [191] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_attlist_decl, 6, .production_id = 1),
  [193] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_element_decl, 8, .production_id = 2),
  [195] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_element_decl, 8, .production_id = 2),
  [197] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_notation_decl, 7, .production_id = 3),
  [199] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_notation_decl, 7, .production_id = 3),
  [201] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attlist_decl, 5, .production_id = 1),
  [203] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_attlist_decl, 5, .production_id = 1),
  [205] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pe_decl, 10),
  [207] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pe_decl, 10),
  [209] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_decl, 1),
  [211] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_decl, 1),
  [213] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ge_decl, 7),
  [215] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_ge_decl, 7),
  [217] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pe_reference, 3),
  [219] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pe_reference, 3),
  [221] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ge_decl, 8),
  [223] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_ge_decl, 8),
  [225] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_processing_instructions, 3),
  [227] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_processing_instructions, 3),
  [229] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_notation_decl, 8, .production_id = 3),
  [231] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_notation_decl, 8, .production_id = 3),
  [233] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comment, 3),
  [235] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comment, 3),
  [237] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_processing_instructions, 5),
  [239] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_processing_instructions, 5),
  [241] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pe_decl, 9),
  [243] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pe_decl, 9),
  [245] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attlist_decl, 7, .production_id = 1),
  [247] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_attlist_decl, 7, .production_id = 1),
  [249] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comment, 2),
  [251] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comment, 2),
  [253] = {.entry = {.count = 1, .reusable = true}}, SHIFT(151),
  [255] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [257] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [259] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [261] = {.entry = {.count = 1, .reusable = true}}, SHIFT(158),
  [263] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [265] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_element_decl, 7, .production_id = 2),
  [267] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_element_decl, 7, .production_id = 2),
  [269] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_ref, 3),
  [271] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_ref, 3),
  [273] = {.entry = {.count = 1, .reusable = false}}, SHIFT(11),
  [275] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [277] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [279] = {.entry = {.count = 1, .reusable = false}}, SHIFT(7),
  [281] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [283] = {.entry = {.count = 1, .reusable = true}}, SHIFT(109),
  [285] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_char_ref, 3),
  [287] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_char_ref, 3),
  [289] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_reference, 1),
  [291] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_reference, 1),
  [293] = {.entry = {.count = 1, .reusable = true}}, SHIFT(235),
  [295] = {.entry = {.count = 1, .reusable = false}}, SHIFT(9),
  [297] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [299] = {.entry = {.count = 1, .reusable = true}}, SHIFT(131),
  [301] = {.entry = {.count = 1, .reusable = true}}, SHIFT(88),
  [303] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [305] = {.entry = {.count = 1, .reusable = true}}, SHIFT(107),
  [307] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [309] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_children, 1),
  [311] = {.entry = {.count = 1, .reusable = true}}, SHIFT(198),
  [313] = {.entry = {.count = 1, .reusable = true}}, SHIFT(148),
  [315] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [317] = {.entry = {.count = 1, .reusable = false}}, SHIFT(174),
  [319] = {.entry = {.count = 1, .reusable = true}}, SHIFT(174),
  [321] = {.entry = {.count = 1, .reusable = true}}, SHIFT(135),
  [323] = {.entry = {.count = 1, .reusable = false}}, SHIFT(184),
  [325] = {.entry = {.count = 1, .reusable = true}}, SHIFT(184),
  [327] = {.entry = {.count = 1, .reusable = true}}, SHIFT(192),
  [329] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [331] = {.entry = {.count = 1, .reusable = true}}, SHIFT(209),
  [333] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_attlist_decl_repeat1, 2), SHIFT_REPEAT(122),
  [336] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_attlist_decl_repeat1, 2),
  [338] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_pubid_literal_repeat1, 2),
  [340] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pubid_literal_repeat1, 2), SHIFT_REPEAT(91),
  [343] = {.entry = {.count = 1, .reusable = true}}, SHIFT(215),
  [345] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [347] = {.entry = {.count = 1, .reusable = true}}, SHIFT(236),
  [349] = {.entry = {.count = 1, .reusable = true}}, SHIFT(170),
  [351] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cp, 2),
  [353] = {.entry = {.count = 1, .reusable = true}}, SHIFT(145),
  [355] = {.entry = {.count = 1, .reusable = true}}, SHIFT(205),
  [357] = {.entry = {.count = 1, .reusable = true}}, SHIFT(169),
  [359] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [361] = {.entry = {.count = 1, .reusable = true}}, SHIFT(189),
  [363] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [365] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_notation_type_repeat1, 2), SHIFT_REPEAT(215),
  [368] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_notation_type_repeat1, 2), SHIFT_REPEAT(81),
  [371] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_notation_type_repeat1, 2),
  [373] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_enumeration_repeat1, 2), SHIFT_REPEAT(213),
  [376] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_enumeration_repeat1, 2), SHIFT_REPEAT(14),
  [379] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_enumeration_repeat1, 2),
  [381] = {.entry = {.count = 1, .reusable = true}}, SHIFT(191),
  [383] = {.entry = {.count = 1, .reusable = true}}, SHIFT(210),
  [385] = {.entry = {.count = 1, .reusable = true}}, SHIFT(201),
  [387] = {.entry = {.count = 1, .reusable = true}}, SHIFT(82),
  [389] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [391] = {.entry = {.count = 1, .reusable = true}}, SHIFT(195),
  [393] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [395] = {.entry = {.count = 1, .reusable = true}}, SHIFT(232),
  [397] = {.entry = {.count = 1, .reusable = true}}, SHIFT(183),
  [399] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [401] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_comment_repeat1, 2), SHIFT_REPEAT(254),
  [404] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_comment_repeat1, 2), SHIFT_REPEAT(116),
  [407] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_comment_repeat1, 2),
  [409] = {.entry = {.count = 1, .reusable = true}}, SHIFT(196),
  [411] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [413] = {.entry = {.count = 1, .reusable = true}}, SHIFT(190),
  [415] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [417] = {.entry = {.count = 1, .reusable = true}}, SHIFT(217),
  [419] = {.entry = {.count = 1, .reusable = true}}, SHIFT(165),
  [421] = {.entry = {.count = 1, .reusable = true}}, SHIFT(171),
  [423] = {.entry = {.count = 1, .reusable = false}}, SHIFT(254),
  [425] = {.entry = {.count = 1, .reusable = true}}, SHIFT(127),
  [427] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [429] = {.entry = {.count = 1, .reusable = true}}, SHIFT(172),
  [431] = {.entry = {.count = 1, .reusable = true}}, SHIFT(224),
  [433] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_mixed_repeat1, 2), SHIFT_REPEAT(248),
  [436] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_mixed_repeat1, 2), SHIFT_REPEAT(71),
  [439] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_mixed_repeat1, 2),
  [441] = {.entry = {.count = 1, .reusable = true}}, SHIFT(116),
  [443] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [445] = {.entry = {.count = 1, .reusable = true}}, SHIFT(247),
  [447] = {.entry = {.count = 1, .reusable = true}}, SHIFT(246),
  [449] = {.entry = {.count = 1, .reusable = true}}, SHIFT(245),
  [451] = {.entry = {.count = 1, .reusable = true}}, SHIFT(229),
  [453] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_element_choice_repeat1, 2), SHIFT_REPEAT(242),
  [456] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_element_choice_repeat1, 2), SHIFT_REPEAT(27),
  [459] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_element_choice_repeat1, 2),
  [461] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_element_seq_repeat1, 2), SHIFT_REPEAT(238),
  [464] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_element_seq_repeat1, 2),
  [466] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_element_seq_repeat1, 2), SHIFT_REPEAT(28),
  [469] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_element_choice_repeat1, 4),
  [471] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [473] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_comment_repeat1, 2),
  [475] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_notation_type_repeat1, 4, .production_id = 6),
  [477] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_notation_type_repeat1, 3, .production_id = 9),
  [479] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_notation_type_repeat1, 2, .production_id = 8),
  [481] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_enumeration_repeat1, 4),
  [483] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_enumeration_repeat1, 3),
  [485] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_def, 1),
  [487] = {.entry = {.count = 1, .reusable = true}}, SHIFT(244),
  [489] = {.entry = {.count = 1, .reusable = true}}, SHIFT(230),
  [491] = {.entry = {.count = 1, .reusable = false}}, SHIFT(171),
  [493] = {.entry = {.count = 1, .reusable = true}}, SHIFT(160),
  [495] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [497] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [499] = {.entry = {.count = 1, .reusable = true}}, SHIFT(108),
  [501] = {.entry = {.count = 1, .reusable = true}}, SHIFT(161),
  [503] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_element_seq_repeat1, 4),
  [505] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_element_seq_repeat1, 3),
  [507] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_mixed_repeat1, 4),
  [509] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_mixed_repeat1, 3),
  [511] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_pubid_literal_repeat2, 2),
  [513] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pubid_literal_repeat2, 2), SHIFT_REPEAT(160),
  [516] = {.entry = {.count = 1, .reusable = true}}, SHIFT(149),
  [518] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_element_choice_repeat1, 3),
  [520] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_default_decl, 3),
  [522] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_spec, 1),
  [524] = {.entry = {.count = 1, .reusable = true}}, SHIFT(188),
  [526] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pi_target, 1),
  [528] = {.entry = {.count = 1, .reusable = true}}, SHIFT(241),
  [530] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [532] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_external_id, 3),
  [534] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_mixed, 5),
  [536] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [538] = {.entry = {.count = 1, .reusable = true}}, SHIFT(204),
  [540] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [542] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_mixed, 4),
  [544] = {.entry = {.count = 1, .reusable = true}}, SHIFT(226),
  [546] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [548] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pe_def, 1),
  [550] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_value, 1),
  [552] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attribute_value, 3),
  [554] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_default_decl, 1),
  [556] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attribute_def, 6, .production_id = 4),
  [558] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_system_literal, 3),
  [560] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pubid_literal, 3),
  [562] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_mixed, 3),
  [564] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_external_id, 5),
  [566] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ndata_decl, 4, .production_id = 5),
  [568] = {.entry = {.count = 1, .reusable = true}}, SHIFT(208),
  [570] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [572] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_mixed, 6),
  [574] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [576] = {.entry = {.count = 1, .reusable = true}}, SHIFT(225),
  [578] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_def, 2),
  [580] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_default_decl, 2),
  [582] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pubid_literal, 2),
  [584] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [586] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_public_id, 3),
  [588] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_children, 2),
  [590] = {.entry = {.count = 1, .reusable = true}}, SHIFT(211),
  [592] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [594] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attribute_value, 2),
  [596] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_notation_type, 6, .production_id = 7),
  [598] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [600] = {.entry = {.count = 1, .reusable = true}}, SHIFT(86),
  [602] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [604] = {.entry = {.count = 1, .reusable = true}}, SHIFT(155),
  [606] = {.entry = {.count = 1, .reusable = true}}, SHIFT(113),
  [608] = {.entry = {.count = 1, .reusable = true}}, SHIFT(182),
  [610] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [612] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enumeration, 5),
  [614] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enumeration, 4),
  [616] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [618] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attribute_type, 1),
  [620] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [622] = {.entry = {.count = 1, .reusable = true}}, SHIFT(153),
  [624] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_notation_type, 5, .production_id = 6),
  [626] = {.entry = {.count = 1, .reusable = true}}, SHIFT(147),
  [628] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [630] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [632] = {.entry = {.count = 1, .reusable = true}}, SHIFT(231),
  [634] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [636] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [638] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enumeration, 3),
  [640] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enumeration, 6),
  [642] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [644] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [646] = {.entry = {.count = 1, .reusable = true}}, SHIFT(219),
  [648] = {.entry = {.count = 1, .reusable = true}}, SHIFT(110),
  [650] = {.entry = {.count = 1, .reusable = true}}, SHIFT(207),
  [652] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [654] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_notation_type, 6, .production_id = 6),
  [656] = {.entry = {.count = 1, .reusable = true}}, SHIFT(96),
  [658] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [660] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [662] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_notation_type, 7, .production_id = 7),
  [664] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [666] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [668] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [670] = {.entry = {.count = 1, .reusable = true}}, SHIFT(240),
  [672] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [674] = {.entry = {.count = 1, .reusable = true}}, SHIFT(212),
  [676] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [678] = {.entry = {.count = 1, .reusable = true}}, SHIFT(112),
  [680] = {.entry = {.count = 1, .reusable = true}}, SHIFT(114),
  [682] = {.entry = {.count = 1, .reusable = true}}, SHIFT(150),
  [684] = {.entry = {.count = 1, .reusable = true}}, SHIFT(73),
  [686] = {.entry = {.count = 1, .reusable = true}}, SHIFT(227),
  [688] = {.entry = {.count = 1, .reusable = true}}, SHIFT(136),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_dtd(void) {
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
