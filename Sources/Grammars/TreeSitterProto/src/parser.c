#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#ifdef _MSC_VER
#pragma optimize("", off)
#elif defined(__clang__)
#pragma clang optimize off
#elif defined(__GNUC__)
#pragma GCC optimize ("O0")
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 314
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 133
#define ALIAS_COUNT 0
#define TOKEN_COUNT 69
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 5
#define MAX_ALIAS_SEQUENCE_LENGTH 13
#define PRODUCTION_ID_COUNT 22

enum ts_symbol_identifiers {
  anon_sym_SEMI = 1,
  anon_sym_syntax = 2,
  anon_sym_EQ = 3,
  anon_sym_DQUOTEproto3_DQUOTE = 4,
  anon_sym_DQUOTEproto2_DQUOTE = 5,
  anon_sym_edition = 6,
  anon_sym_import = 7,
  anon_sym_weak = 8,
  anon_sym_public = 9,
  anon_sym_package = 10,
  anon_sym_option = 11,
  anon_sym_DOT = 12,
  anon_sym_LPAREN = 13,
  anon_sym_RPAREN = 14,
  anon_sym_enum = 15,
  anon_sym_LBRACE = 16,
  anon_sym_RBRACE = 17,
  anon_sym_LBRACK = 18,
  anon_sym_RBRACK = 19,
  anon_sym_message = 20,
  anon_sym_extend = 21,
  anon_sym_optional = 22,
  anon_sym_required = 23,
  anon_sym_repeated = 24,
  anon_sym_COMMA = 25,
  anon_sym_oneof = 26,
  anon_sym_map = 27,
  anon_sym_LT = 28,
  anon_sym_GT = 29,
  anon_sym_int32 = 30,
  anon_sym_int64 = 31,
  anon_sym_uint32 = 32,
  anon_sym_uint64 = 33,
  anon_sym_sint32 = 34,
  anon_sym_sint64 = 35,
  anon_sym_fixed32 = 36,
  anon_sym_fixed64 = 37,
  anon_sym_sfixed32 = 38,
  anon_sym_sfixed64 = 39,
  anon_sym_bool = 40,
  anon_sym_string = 41,
  anon_sym_double = 42,
  anon_sym_float = 43,
  anon_sym_bytes = 44,
  anon_sym_reserved = 45,
  anon_sym_extensions = 46,
  anon_sym_to = 47,
  anon_sym_max = 48,
  anon_sym_service = 49,
  anon_sym_rpc = 50,
  anon_sym_stream = 51,
  anon_sym_returns = 52,
  anon_sym_DASH = 53,
  anon_sym_PLUS = 54,
  anon_sym_COLON = 55,
  sym_identifier = 56,
  sym_true = 57,
  sym_false = 58,
  sym_decimal_lit = 59,
  sym_octal_lit = 60,
  sym_hex_lit = 61,
  sym_float_lit = 62,
  anon_sym_SQUOTE = 63,
  aux_sym_string_token1 = 64,
  anon_sym_DQUOTE = 65,
  aux_sym_string_token2 = 66,
  sym_escape_sequence = 67,
  sym_comment = 68,
  sym_source_file = 69,
  sym_empty_statement = 70,
  sym_syntax = 71,
  sym_edition = 72,
  sym_import = 73,
  sym_package = 74,
  sym_option = 75,
  sym_option_name = 76,
  sym_enum = 77,
  sym_enum_name = 78,
  sym_enum_body = 79,
  sym_enum_field = 80,
  sym_message = 81,
  sym_message_body = 82,
  sym_message_name = 83,
  sym_field_name = 84,
  sym_extend = 85,
  sym_field = 86,
  sym_field_options = 87,
  sym_field_option = 88,
  sym_oneof = 89,
  sym_oneof_body = 90,
  sym_oneof_field = 91,
  sym_map_field = 92,
  sym_key_type = 93,
  sym_type = 94,
  sym_reserved = 95,
  sym_extensions = 96,
  sym_ranges = 97,
  sym_range = 98,
  sym_field_names = 99,
  sym_message_or_enum_type = 100,
  sym_field_number = 101,
  sym_service = 102,
  sym_service_body = 103,
  sym_service_name = 104,
  sym_rpc = 105,
  sym_rpc_body = 106,
  sym_rpc_name = 107,
  sym_enum_variant_name = 108,
  sym__constant = 109,
  sym_block_lit = 110,
  sym_block_field = 111,
  sym__identifier_or_string = 112,
  sym_full_ident = 113,
  sym_bool = 114,
  sym_int_lit = 115,
  sym_string = 116,
  aux_sym_source_file_repeat1 = 117,
  aux_sym_option_name_repeat1 = 118,
  aux_sym_enum_body_repeat1 = 119,
  aux_sym_message_body_repeat1 = 120,
  aux_sym_field_options_repeat1 = 121,
  aux_sym_oneof_body_repeat1 = 122,
  aux_sym_ranges_repeat1 = 123,
  aux_sym_field_names_repeat1 = 124,
  aux_sym_message_or_enum_type_repeat1 = 125,
  aux_sym_service_body_repeat1 = 126,
  aux_sym_rpc_body_repeat1 = 127,
  aux_sym_block_lit_repeat1 = 128,
  aux_sym_block_field_repeat1 = 129,
  aux_sym_string_repeat1 = 130,
  aux_sym_string_repeat2 = 131,
  aux_sym_string_repeat3 = 132,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_SEMI] = ";",
  [anon_sym_syntax] = "syntax",
  [anon_sym_EQ] = "=",
  [anon_sym_DQUOTEproto3_DQUOTE] = "\"proto3\"",
  [anon_sym_DQUOTEproto2_DQUOTE] = "\"proto2\"",
  [anon_sym_edition] = "edition",
  [anon_sym_import] = "import",
  [anon_sym_weak] = "weak",
  [anon_sym_public] = "public",
  [anon_sym_package] = "package",
  [anon_sym_option] = "option",
  [anon_sym_DOT] = ".",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_enum] = "enum",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [anon_sym_message] = "message",
  [anon_sym_extend] = "extend",
  [anon_sym_optional] = "optional",
  [anon_sym_required] = "required",
  [anon_sym_repeated] = "repeated",
  [anon_sym_COMMA] = ",",
  [anon_sym_oneof] = "oneof",
  [anon_sym_map] = "map",
  [anon_sym_LT] = "<",
  [anon_sym_GT] = ">",
  [anon_sym_int32] = "int32",
  [anon_sym_int64] = "int64",
  [anon_sym_uint32] = "uint32",
  [anon_sym_uint64] = "uint64",
  [anon_sym_sint32] = "sint32",
  [anon_sym_sint64] = "sint64",
  [anon_sym_fixed32] = "fixed32",
  [anon_sym_fixed64] = "fixed64",
  [anon_sym_sfixed32] = "sfixed32",
  [anon_sym_sfixed64] = "sfixed64",
  [anon_sym_bool] = "bool",
  [anon_sym_string] = "string",
  [anon_sym_double] = "double",
  [anon_sym_float] = "float",
  [anon_sym_bytes] = "bytes",
  [anon_sym_reserved] = "reserved",
  [anon_sym_extensions] = "extensions",
  [anon_sym_to] = "to",
  [anon_sym_max] = "max",
  [anon_sym_service] = "service",
  [anon_sym_rpc] = "rpc",
  [anon_sym_stream] = "stream",
  [anon_sym_returns] = "returns",
  [anon_sym_DASH] = "-",
  [anon_sym_PLUS] = "+",
  [anon_sym_COLON] = ":",
  [sym_identifier] = "identifier",
  [sym_true] = "true",
  [sym_false] = "false",
  [sym_decimal_lit] = "decimal_lit",
  [sym_octal_lit] = "octal_lit",
  [sym_hex_lit] = "hex_lit",
  [sym_float_lit] = "float_lit",
  [anon_sym_SQUOTE] = "'",
  [aux_sym_string_token1] = "string_token1",
  [anon_sym_DQUOTE] = "\"",
  [aux_sym_string_token2] = "string_token2",
  [sym_escape_sequence] = "escape_sequence",
  [sym_comment] = "comment",
  [sym_source_file] = "source_file",
  [sym_empty_statement] = "empty_statement",
  [sym_syntax] = "syntax",
  [sym_edition] = "edition",
  [sym_import] = "import",
  [sym_package] = "package",
  [sym_option] = "option",
  [sym_option_name] = "option_name",
  [sym_enum] = "enum",
  [sym_enum_name] = "enum_name",
  [sym_enum_body] = "enum_body",
  [sym_enum_field] = "enum_field",
  [sym_message] = "message",
  [sym_message_body] = "message_body",
  [sym_message_name] = "message_name",
  [sym_field_name] = "field_name",
  [sym_extend] = "extend",
  [sym_field] = "field",
  [sym_field_options] = "field_options",
  [sym_field_option] = "field_option",
  [sym_oneof] = "oneof",
  [sym_oneof_body] = "oneof_body",
  [sym_oneof_field] = "oneof_field",
  [sym_map_field] = "map_field",
  [sym_key_type] = "key_type",
  [sym_type] = "type",
  [sym_reserved] = "reserved",
  [sym_extensions] = "extensions",
  [sym_ranges] = "ranges",
  [sym_range] = "range",
  [sym_field_names] = "field_names",
  [sym_message_or_enum_type] = "message_or_enum_type",
  [sym_field_number] = "field_number",
  [sym_service] = "service",
  [sym_service_body] = "service_body",
  [sym_service_name] = "service_name",
  [sym_rpc] = "rpc",
  [sym_rpc_body] = "rpc_body",
  [sym_rpc_name] = "rpc_name",
  [sym_enum_variant_name] = "enum_variant_name",
  [sym__constant] = "_constant",
  [sym_block_lit] = "block_lit",
  [sym_block_field] = "block_field",
  [sym__identifier_or_string] = "_identifier_or_string",
  [sym_full_ident] = "full_ident",
  [sym_bool] = "bool",
  [sym_int_lit] = "int_lit",
  [sym_string] = "string",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_option_name_repeat1] = "option_name_repeat1",
  [aux_sym_enum_body_repeat1] = "enum_body_repeat1",
  [aux_sym_message_body_repeat1] = "message_body_repeat1",
  [aux_sym_field_options_repeat1] = "field_options_repeat1",
  [aux_sym_oneof_body_repeat1] = "oneof_body_repeat1",
  [aux_sym_ranges_repeat1] = "ranges_repeat1",
  [aux_sym_field_names_repeat1] = "field_names_repeat1",
  [aux_sym_message_or_enum_type_repeat1] = "message_or_enum_type_repeat1",
  [aux_sym_service_body_repeat1] = "service_body_repeat1",
  [aux_sym_rpc_body_repeat1] = "rpc_body_repeat1",
  [aux_sym_block_lit_repeat1] = "block_lit_repeat1",
  [aux_sym_block_field_repeat1] = "block_field_repeat1",
  [aux_sym_string_repeat1] = "string_repeat1",
  [aux_sym_string_repeat2] = "string_repeat2",
  [aux_sym_string_repeat3] = "string_repeat3",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_syntax] = anon_sym_syntax,
  [anon_sym_EQ] = anon_sym_EQ,
  [anon_sym_DQUOTEproto3_DQUOTE] = anon_sym_DQUOTEproto3_DQUOTE,
  [anon_sym_DQUOTEproto2_DQUOTE] = anon_sym_DQUOTEproto2_DQUOTE,
  [anon_sym_edition] = anon_sym_edition,
  [anon_sym_import] = anon_sym_import,
  [anon_sym_weak] = anon_sym_weak,
  [anon_sym_public] = anon_sym_public,
  [anon_sym_package] = anon_sym_package,
  [anon_sym_option] = anon_sym_option,
  [anon_sym_DOT] = anon_sym_DOT,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_enum] = anon_sym_enum,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [anon_sym_message] = anon_sym_message,
  [anon_sym_extend] = anon_sym_extend,
  [anon_sym_optional] = anon_sym_optional,
  [anon_sym_required] = anon_sym_required,
  [anon_sym_repeated] = anon_sym_repeated,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_oneof] = anon_sym_oneof,
  [anon_sym_map] = anon_sym_map,
  [anon_sym_LT] = anon_sym_LT,
  [anon_sym_GT] = anon_sym_GT,
  [anon_sym_int32] = anon_sym_int32,
  [anon_sym_int64] = anon_sym_int64,
  [anon_sym_uint32] = anon_sym_uint32,
  [anon_sym_uint64] = anon_sym_uint64,
  [anon_sym_sint32] = anon_sym_sint32,
  [anon_sym_sint64] = anon_sym_sint64,
  [anon_sym_fixed32] = anon_sym_fixed32,
  [anon_sym_fixed64] = anon_sym_fixed64,
  [anon_sym_sfixed32] = anon_sym_sfixed32,
  [anon_sym_sfixed64] = anon_sym_sfixed64,
  [anon_sym_bool] = anon_sym_bool,
  [anon_sym_string] = anon_sym_string,
  [anon_sym_double] = anon_sym_double,
  [anon_sym_float] = anon_sym_float,
  [anon_sym_bytes] = anon_sym_bytes,
  [anon_sym_reserved] = anon_sym_reserved,
  [anon_sym_extensions] = anon_sym_extensions,
  [anon_sym_to] = anon_sym_to,
  [anon_sym_max] = anon_sym_max,
  [anon_sym_service] = anon_sym_service,
  [anon_sym_rpc] = anon_sym_rpc,
  [anon_sym_stream] = anon_sym_stream,
  [anon_sym_returns] = anon_sym_returns,
  [anon_sym_DASH] = anon_sym_DASH,
  [anon_sym_PLUS] = anon_sym_PLUS,
  [anon_sym_COLON] = anon_sym_COLON,
  [sym_identifier] = sym_identifier,
  [sym_true] = sym_true,
  [sym_false] = sym_false,
  [sym_decimal_lit] = sym_decimal_lit,
  [sym_octal_lit] = sym_octal_lit,
  [sym_hex_lit] = sym_hex_lit,
  [sym_float_lit] = sym_float_lit,
  [anon_sym_SQUOTE] = anon_sym_SQUOTE,
  [aux_sym_string_token1] = aux_sym_string_token1,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [aux_sym_string_token2] = aux_sym_string_token2,
  [sym_escape_sequence] = sym_escape_sequence,
  [sym_comment] = sym_comment,
  [sym_source_file] = sym_source_file,
  [sym_empty_statement] = sym_empty_statement,
  [sym_syntax] = sym_syntax,
  [sym_edition] = sym_edition,
  [sym_import] = sym_import,
  [sym_package] = sym_package,
  [sym_option] = sym_option,
  [sym_option_name] = sym_option_name,
  [sym_enum] = sym_enum,
  [sym_enum_name] = sym_enum_name,
  [sym_enum_body] = sym_enum_body,
  [sym_enum_field] = sym_enum_field,
  [sym_message] = sym_message,
  [sym_message_body] = sym_message_body,
  [sym_message_name] = sym_message_name,
  [sym_field_name] = sym_field_name,
  [sym_extend] = sym_extend,
  [sym_field] = sym_field,
  [sym_field_options] = sym_field_options,
  [sym_field_option] = sym_field_option,
  [sym_oneof] = sym_oneof,
  [sym_oneof_body] = sym_oneof_body,
  [sym_oneof_field] = sym_oneof_field,
  [sym_map_field] = sym_map_field,
  [sym_key_type] = sym_key_type,
  [sym_type] = sym_type,
  [sym_reserved] = sym_reserved,
  [sym_extensions] = sym_extensions,
  [sym_ranges] = sym_ranges,
  [sym_range] = sym_range,
  [sym_field_names] = sym_field_names,
  [sym_message_or_enum_type] = sym_message_or_enum_type,
  [sym_field_number] = sym_field_number,
  [sym_service] = sym_service,
  [sym_service_body] = sym_service_body,
  [sym_service_name] = sym_service_name,
  [sym_rpc] = sym_rpc,
  [sym_rpc_body] = sym_rpc_body,
  [sym_rpc_name] = sym_rpc_name,
  [sym_enum_variant_name] = sym_enum_variant_name,
  [sym__constant] = sym__constant,
  [sym_block_lit] = sym_block_lit,
  [sym_block_field] = sym_block_field,
  [sym__identifier_or_string] = sym__identifier_or_string,
  [sym_full_ident] = sym_full_ident,
  [sym_bool] = sym_bool,
  [sym_int_lit] = sym_int_lit,
  [sym_string] = sym_string,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_option_name_repeat1] = aux_sym_option_name_repeat1,
  [aux_sym_enum_body_repeat1] = aux_sym_enum_body_repeat1,
  [aux_sym_message_body_repeat1] = aux_sym_message_body_repeat1,
  [aux_sym_field_options_repeat1] = aux_sym_field_options_repeat1,
  [aux_sym_oneof_body_repeat1] = aux_sym_oneof_body_repeat1,
  [aux_sym_ranges_repeat1] = aux_sym_ranges_repeat1,
  [aux_sym_field_names_repeat1] = aux_sym_field_names_repeat1,
  [aux_sym_message_or_enum_type_repeat1] = aux_sym_message_or_enum_type_repeat1,
  [aux_sym_service_body_repeat1] = aux_sym_service_body_repeat1,
  [aux_sym_rpc_body_repeat1] = aux_sym_rpc_body_repeat1,
  [aux_sym_block_lit_repeat1] = aux_sym_block_lit_repeat1,
  [aux_sym_block_field_repeat1] = aux_sym_block_field_repeat1,
  [aux_sym_string_repeat1] = aux_sym_string_repeat1,
  [aux_sym_string_repeat2] = aux_sym_string_repeat2,
  [aux_sym_string_repeat3] = aux_sym_string_repeat3,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_SEMI] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_syntax] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DQUOTEproto3_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DQUOTEproto2_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_edition] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_import] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_weak] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_public] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_package] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_option] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOT] = {
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
  [anon_sym_enum] = {
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
  [anon_sym_message] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_extend] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_optional] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_required] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_repeated] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_oneof] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_map] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_int32] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_int64] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_uint32] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_uint64] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_sint32] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_sint64] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_fixed32] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_fixed64] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_sfixed32] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_sfixed64] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_bool] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_string] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_double] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_float] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_bytes] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_reserved] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_extensions] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_to] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_max] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_service] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_rpc] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_stream] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_returns] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PLUS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [sym_true] = {
    .visible = true,
    .named = true,
  },
  [sym_false] = {
    .visible = true,
    .named = true,
  },
  [sym_decimal_lit] = {
    .visible = true,
    .named = true,
  },
  [sym_octal_lit] = {
    .visible = true,
    .named = true,
  },
  [sym_hex_lit] = {
    .visible = true,
    .named = true,
  },
  [sym_float_lit] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_SQUOTE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_string_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_string_token2] = {
    .visible = false,
    .named = false,
  },
  [sym_escape_sequence] = {
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
  [sym_empty_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_syntax] = {
    .visible = true,
    .named = true,
  },
  [sym_edition] = {
    .visible = true,
    .named = true,
  },
  [sym_import] = {
    .visible = true,
    .named = true,
  },
  [sym_package] = {
    .visible = true,
    .named = true,
  },
  [sym_option] = {
    .visible = true,
    .named = true,
  },
  [sym_option_name] = {
    .visible = true,
    .named = true,
  },
  [sym_enum] = {
    .visible = true,
    .named = true,
  },
  [sym_enum_name] = {
    .visible = true,
    .named = true,
  },
  [sym_enum_body] = {
    .visible = true,
    .named = true,
  },
  [sym_enum_field] = {
    .visible = true,
    .named = true,
  },
  [sym_message] = {
    .visible = true,
    .named = true,
  },
  [sym_message_body] = {
    .visible = true,
    .named = true,
  },
  [sym_message_name] = {
    .visible = true,
    .named = true,
  },
  [sym_field_name] = {
    .visible = true,
    .named = true,
  },
  [sym_extend] = {
    .visible = true,
    .named = true,
  },
  [sym_field] = {
    .visible = true,
    .named = true,
  },
  [sym_field_options] = {
    .visible = true,
    .named = true,
  },
  [sym_field_option] = {
    .visible = true,
    .named = true,
  },
  [sym_oneof] = {
    .visible = true,
    .named = true,
  },
  [sym_oneof_body] = {
    .visible = true,
    .named = true,
  },
  [sym_oneof_field] = {
    .visible = true,
    .named = true,
  },
  [sym_map_field] = {
    .visible = true,
    .named = true,
  },
  [sym_key_type] = {
    .visible = true,
    .named = true,
  },
  [sym_type] = {
    .visible = true,
    .named = true,
  },
  [sym_reserved] = {
    .visible = true,
    .named = true,
  },
  [sym_extensions] = {
    .visible = true,
    .named = true,
  },
  [sym_ranges] = {
    .visible = true,
    .named = true,
  },
  [sym_range] = {
    .visible = true,
    .named = true,
  },
  [sym_field_names] = {
    .visible = true,
    .named = true,
  },
  [sym_message_or_enum_type] = {
    .visible = true,
    .named = true,
  },
  [sym_field_number] = {
    .visible = true,
    .named = true,
  },
  [sym_service] = {
    .visible = true,
    .named = true,
  },
  [sym_service_body] = {
    .visible = true,
    .named = true,
  },
  [sym_service_name] = {
    .visible = true,
    .named = true,
  },
  [sym_rpc] = {
    .visible = true,
    .named = true,
  },
  [sym_rpc_body] = {
    .visible = true,
    .named = true,
  },
  [sym_rpc_name] = {
    .visible = true,
    .named = true,
  },
  [sym_enum_variant_name] = {
    .visible = true,
    .named = true,
  },
  [sym__constant] = {
    .visible = false,
    .named = true,
  },
  [sym_block_lit] = {
    .visible = true,
    .named = true,
  },
  [sym_block_field] = {
    .visible = true,
    .named = true,
  },
  [sym__identifier_or_string] = {
    .visible = false,
    .named = true,
  },
  [sym_full_ident] = {
    .visible = true,
    .named = true,
  },
  [sym_bool] = {
    .visible = true,
    .named = true,
  },
  [sym_int_lit] = {
    .visible = true,
    .named = true,
  },
  [sym_string] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_option_name_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_enum_body_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_message_body_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_field_options_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_oneof_body_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_ranges_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_field_names_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_message_or_enum_type_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_service_body_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_rpc_body_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_block_lit_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_block_field_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_string_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_string_repeat2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_string_repeat3] = {
    .visible = false,
    .named = false,
  },
};

enum ts_field_identifiers {
  field_key = 1,
  field_name = 2,
  field_path = 3,
  field_value = 4,
  field_year = 5,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_key] = "key",
  [field_name] = "name",
  [field_path] = "path",
  [field_value] = "value",
  [field_year] = "year",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 1},
  [3] = {.index = 2, .length = 1},
  [4] = {.index = 3, .length = 2},
  [5] = {.index = 5, .length = 2},
  [6] = {.index = 7, .length = 3},
  [7] = {.index = 10, .length = 2},
  [8] = {.index = 12, .length = 4},
  [9] = {.index = 16, .length = 4},
  [10] = {.index = 20, .length = 3},
  [11] = {.index = 23, .length = 5},
  [12] = {.index = 28, .length = 4},
  [13] = {.index = 32, .length = 5},
  [14] = {.index = 37, .length = 4},
  [15] = {.index = 41, .length = 6},
  [16] = {.index = 47, .length = 5},
  [17] = {.index = 52, .length = 5},
  [18] = {.index = 57, .length = 2},
  [19] = {.index = 59, .length = 7},
  [20] = {.index = 66, .length = 6},
  [21] = {.index = 72, .length = 7},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_path, 1},
  [1] =
    {field_year, 2},
  [2] =
    {field_path, 2},
  [3] =
    {field_name, 1},
    {field_value, 3},
  [5] =
    {field_key, 0},
    {field_value, 1},
  [7] =
    {field_key, 0},
    {field_value, 1},
    {field_value, 2},
  [10] =
    {field_key, 0},
    {field_value, 2},
  [12] =
    {field_key, 0},
    {field_key, 1},
    {field_key, 2},
    {field_value, 3},
  [16] =
    {field_key, 0},
    {field_value, 1},
    {field_value, 2},
    {field_value, 3},
  [20] =
    {field_key, 0},
    {field_value, 2},
    {field_value, 3},
  [23] =
    {field_key, 0},
    {field_key, 1},
    {field_key, 2},
    {field_value, 3},
    {field_value, 4},
  [28] =
    {field_key, 0},
    {field_key, 1},
    {field_key, 2},
    {field_value, 4},
  [32] =
    {field_key, 0},
    {field_value, 1},
    {field_value, 2},
    {field_value, 3},
    {field_value, 4},
  [37] =
    {field_key, 0},
    {field_value, 2},
    {field_value, 3},
    {field_value, 4},
  [41] =
    {field_key, 0},
    {field_key, 1},
    {field_key, 2},
    {field_value, 3},
    {field_value, 4},
    {field_value, 5},
  [47] =
    {field_key, 0},
    {field_key, 1},
    {field_key, 2},
    {field_value, 4},
    {field_value, 5},
  [52] =
    {field_key, 0},
    {field_value, 2},
    {field_value, 3},
    {field_value, 4},
    {field_value, 5},
  [57] =
    {field_name, 0},
    {field_value, 2},
  [59] =
    {field_key, 0},
    {field_key, 1},
    {field_key, 2},
    {field_value, 3},
    {field_value, 4},
    {field_value, 5},
    {field_value, 6},
  [66] =
    {field_key, 0},
    {field_key, 1},
    {field_key, 2},
    {field_value, 4},
    {field_value, 5},
    {field_value, 6},
  [72] =
    {field_key, 0},
    {field_key, 1},
    {field_key, 2},
    {field_value, 4},
    {field_value, 5},
    {field_value, 6},
    {field_value, 7},
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
  [5] = 2,
  [6] = 3,
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
  [46] = 23,
  [47] = 47,
  [48] = 48,
  [49] = 29,
  [50] = 50,
  [51] = 51,
  [52] = 52,
  [53] = 53,
  [54] = 52,
  [55] = 52,
  [56] = 52,
  [57] = 57,
  [58] = 58,
  [59] = 59,
  [60] = 60,
  [61] = 61,
  [62] = 62,
  [63] = 62,
  [64] = 64,
  [65] = 65,
  [66] = 66,
  [67] = 23,
  [68] = 68,
  [69] = 69,
  [70] = 29,
  [71] = 68,
  [72] = 69,
  [73] = 73,
  [74] = 74,
  [75] = 75,
  [76] = 76,
  [77] = 7,
  [78] = 78,
  [79] = 79,
  [80] = 24,
  [81] = 81,
  [82] = 82,
  [83] = 20,
  [84] = 25,
  [85] = 26,
  [86] = 86,
  [87] = 21,
  [88] = 88,
  [89] = 22,
  [90] = 27,
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
  [120] = 28,
  [121] = 121,
  [122] = 122,
  [123] = 123,
  [124] = 124,
  [125] = 125,
  [126] = 126,
  [127] = 127,
  [128] = 23,
  [129] = 129,
  [130] = 130,
  [131] = 131,
  [132] = 132,
  [133] = 133,
  [134] = 134,
  [135] = 135,
  [136] = 29,
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
  [147] = 140,
  [148] = 148,
  [149] = 149,
  [150] = 36,
  [151] = 151,
  [152] = 152,
  [153] = 153,
  [154] = 36,
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
  [198] = 183,
  [199] = 199,
  [200] = 200,
  [201] = 201,
  [202] = 202,
  [203] = 203,
  [204] = 204,
  [205] = 204,
  [206] = 206,
  [207] = 183,
  [208] = 183,
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
  [227] = 227,
  [228] = 228,
  [229] = 229,
  [230] = 230,
  [231] = 231,
  [232] = 232,
  [233] = 233,
  [234] = 234,
  [235] = 235,
  [236] = 236,
  [237] = 229,
  [238] = 232,
  [239] = 235,
  [240] = 240,
  [241] = 214,
  [242] = 242,
  [243] = 218,
  [244] = 242,
  [245] = 245,
  [246] = 233,
  [247] = 247,
  [248] = 248,
  [249] = 249,
  [250] = 250,
  [251] = 251,
  [252] = 252,
  [253] = 253,
  [254] = 254,
  [255] = 255,
  [256] = 256,
  [257] = 257,
  [258] = 258,
  [259] = 259,
  [260] = 260,
  [261] = 261,
  [262] = 262,
  [263] = 263,
  [264] = 264,
  [265] = 265,
  [266] = 266,
  [267] = 267,
  [268] = 268,
  [269] = 269,
  [270] = 270,
  [271] = 271,
  [272] = 272,
  [273] = 273,
  [274] = 274,
  [275] = 275,
  [276] = 276,
  [277] = 277,
  [278] = 278,
  [279] = 279,
  [280] = 280,
  [281] = 281,
  [282] = 282,
  [283] = 283,
  [284] = 284,
  [285] = 285,
  [286] = 286,
  [287] = 287,
  [288] = 288,
  [289] = 289,
  [290] = 290,
  [291] = 291,
  [292] = 292,
  [293] = 284,
  [294] = 294,
  [295] = 295,
  [296] = 296,
  [297] = 284,
  [298] = 284,
  [299] = 299,
  [300] = 300,
  [301] = 301,
  [302] = 302,
  [303] = 303,
  [304] = 304,
  [305] = 305,
  [306] = 306,
  [307] = 263,
  [308] = 263,
  [309] = 263,
  [310] = 296,
  [311] = 311,
  [312] = 312,
  [313] = 313,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(196);
      ADVANCE_MAP(
        '"', 422,
        '\'', 415,
        '(', 213,
        ')', 214,
        '+', 280,
        ',', 231,
        '-', 279,
        '.', 212,
        '/', 7,
        '0', 407,
        ':', 281,
        ';', 197,
        '<', 236,
        '=', 199,
        '>', 237,
        '[', 219,
        '\\', 34,
        ']', 220,
        'b', 130,
        'd', 126,
        'e', 59,
        'f', 35,
        'i', 109,
        'm', 36,
        'n', 37,
        'o', 117,
        'p', 39,
        'r', 63,
        's', 64,
        't', 127,
        'u', 100,
        'w', 73,
        '{', 217,
        '}', 218,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(194);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(405);
      END_STATE();
    case 1:
      ADVANCE_MAP(
        '"', 422,
        '\'', 415,
        '(', 213,
        ')', 214,
        ',', 231,
        '.', 211,
        '/', 7,
        '0', 409,
        ';', 197,
        '=', 199,
        '>', 237,
        '[', 219,
        ']', 220,
        '{', 217,
        '}', 218,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(1);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(406);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 2:
      ADVANCE_MAP(
        '"', 422,
        '\'', 415,
        '+', 280,
        '-', 279,
        '.', 183,
        '/', 7,
        '0', 407,
        ':', 281,
        '=', 199,
        '[', 219,
        ']', 220,
        'f', 301,
        'i', 355,
        'n', 302,
        't', 374,
        '{', 217,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(2);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(405);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 3:
      if (lookahead == '"') ADVANCE(422);
      if (lookahead == '/') ADVANCE(424);
      if (lookahead == '\\') ADVANCE(34);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(427);
      if (lookahead != 0) ADVANCE(428);
      END_STATE();
    case 4:
      if (lookahead == '"') ADVANCE(201);
      END_STATE();
    case 5:
      if (lookahead == '"') ADVANCE(200);
      END_STATE();
    case 6:
      if (lookahead == '\'') ADVANCE(415);
      if (lookahead == '/') ADVANCE(417);
      if (lookahead == '\\') ADVANCE(34);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(420);
      if (lookahead != 0) ADVANCE(421);
      END_STATE();
    case 7:
      if (lookahead == '*') ADVANCE(9);
      if (lookahead == '/') ADVANCE(433);
      END_STATE();
    case 8:
      if (lookahead == '*') ADVANCE(8);
      if (lookahead == '/') ADVANCE(432);
      if (lookahead != 0) ADVANCE(9);
      END_STATE();
    case 9:
      if (lookahead == '*') ADVANCE(8);
      if (lookahead != 0) ADVANCE(9);
      END_STATE();
    case 10:
      if (lookahead == '.') ADVANCE(413);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(182);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(10);
      END_STATE();
    case 11:
      ADVANCE_MAP(
        '.', 211,
        '/', 7,
        ';', 197,
        '[', 219,
        'b', 364,
        'd', 360,
        'f', 334,
        'i', 353,
        'o', 371,
        's', 331,
        'u', 340,
        '}', 218,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(11);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 12:
      ADVANCE_MAP(
        '.', 211,
        '/', 7,
        ';', 197,
        'b', 364,
        'd', 360,
        'e', 354,
        'f', 334,
        'i', 353,
        'm', 297,
        'o', 352,
        'r', 311,
        's', 331,
        'u', 340,
        '}', 218,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(12);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 13:
      ADVANCE_MAP(
        '.', 211,
        '/', 7,
        'b', 364,
        'd', 360,
        'f', 334,
        'i', 353,
        'r', 320,
        's', 331,
        'u', 340,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(13);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 14:
      ADVANCE_MAP(
        '.', 211,
        '/', 7,
        'b', 364,
        'd', 360,
        'f', 334,
        'i', 353,
        's', 331,
        'u', 340,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(14);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 15:
      if (lookahead == '.') ADVANCE(211);
      if (lookahead == '/') ADVANCE(7);
      if (lookahead == 's') ADVANCE(390);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(15);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 16:
      if (lookahead == '.') ADVANCE(183);
      if (lookahead == '/') ADVANCE(7);
      if (lookahead == '0') ADVANCE(407);
      if (lookahead == 'i') ADVANCE(118);
      if (lookahead == 'n') ADVANCE(37);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(16);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(405);
      END_STATE();
    case 17:
      if (lookahead == '/') ADVANCE(7);
      if (lookahead == ';') ADVANCE(197);
      if (lookahead == 'o') ADVANCE(371);
      if (lookahead == 'r') ADVANCE(327);
      if (lookahead == '}') ADVANCE(218);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(17);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 18:
      if (lookahead == '2') ADVANCE(238);
      END_STATE();
    case 19:
      if (lookahead == '2') ADVANCE(246);
      END_STATE();
    case 20:
      if (lookahead == '2') ADVANCE(242);
      END_STATE();
    case 21:
      if (lookahead == '2') ADVANCE(250);
      END_STATE();
    case 22:
      if (lookahead == '2') ADVANCE(254);
      END_STATE();
    case 23:
      if (lookahead == '2') ADVANCE(4);
      if (lookahead == '3') ADVANCE(5);
      END_STATE();
    case 24:
      if (lookahead == '3') ADVANCE(18);
      if (lookahead == '6') ADVANCE(29);
      END_STATE();
    case 25:
      if (lookahead == '3') ADVANCE(19);
      if (lookahead == '6') ADVANCE(30);
      END_STATE();
    case 26:
      if (lookahead == '3') ADVANCE(20);
      if (lookahead == '6') ADVANCE(31);
      END_STATE();
    case 27:
      if (lookahead == '3') ADVANCE(21);
      if (lookahead == '6') ADVANCE(32);
      END_STATE();
    case 28:
      if (lookahead == '3') ADVANCE(22);
      if (lookahead == '6') ADVANCE(33);
      END_STATE();
    case 29:
      if (lookahead == '4') ADVANCE(240);
      END_STATE();
    case 30:
      if (lookahead == '4') ADVANCE(248);
      END_STATE();
    case 31:
      if (lookahead == '4') ADVANCE(244);
      END_STATE();
    case 32:
      if (lookahead == '4') ADVANCE(252);
      END_STATE();
    case 33:
      if (lookahead == '4') ADVANCE(256);
      END_STATE();
    case 34:
      if (lookahead == 'U') ADVANCE(193);
      if (lookahead == 'u') ADVANCE(189);
      if (lookahead == 'x') ADVANCE(187);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(431);
      if (lookahead != 0) ADVANCE(429);
      END_STATE();
    case 35:
      if (lookahead == 'a') ADVANCE(105);
      if (lookahead == 'i') ADVANCE(180);
      if (lookahead == 'l') ADVANCE(132);
      END_STATE();
    case 36:
      if (lookahead == 'a') ADVANCE(139);
      if (lookahead == 'e') ADVANCE(155);
      END_STATE();
    case 37:
      if (lookahead == 'a') ADVANCE(112);
      END_STATE();
    case 38:
      if (lookahead == 'a') ADVANCE(50);
      END_STATE();
    case 39:
      if (lookahead == 'a') ADVANCE(50);
      if (lookahead == 'u') ADVANCE(48);
      END_STATE();
    case 40:
      if (lookahead == 'a') ADVANCE(89);
      END_STATE();
    case 41:
      if (lookahead == 'a') ADVANCE(179);
      END_STATE();
    case 42:
      if (lookahead == 'a') ADVANCE(111);
      END_STATE();
    case 43:
      if (lookahead == 'a') ADVANCE(101);
      END_STATE();
    case 44:
      if (lookahead == 'a') ADVANCE(178);
      if (lookahead == 'e') ADVANCE(155);
      END_STATE();
    case 45:
      if (lookahead == 'a') ADVANCE(158);
      END_STATE();
    case 46:
      if (lookahead == 'a') ADVANCE(90);
      END_STATE();
    case 47:
      if (lookahead == 'a') ADVANCE(165);
      END_STATE();
    case 48:
      if (lookahead == 'b') ADVANCE(106);
      END_STATE();
    case 49:
      if (lookahead == 'b') ADVANCE(107);
      END_STATE();
    case 50:
      if (lookahead == 'c') ADVANCE(102);
      END_STATE();
    case 51:
      if (lookahead == 'c') ADVANCE(275);
      END_STATE();
    case 52:
      if (lookahead == 'c') ADVANCE(205);
      END_STATE();
    case 53:
      if (lookahead == 'c') ADVANCE(72);
      END_STATE();
    case 54:
      if (lookahead == 'd') ADVANCE(223);
      END_STATE();
    case 55:
      if (lookahead == 'd') ADVANCE(223);
      if (lookahead == 's') ADVANCE(96);
      END_STATE();
    case 56:
      if (lookahead == 'd') ADVANCE(229);
      END_STATE();
    case 57:
      if (lookahead == 'd') ADVANCE(227);
      END_STATE();
    case 58:
      if (lookahead == 'd') ADVANCE(268);
      END_STATE();
    case 59:
      if (lookahead == 'd') ADVANCE(98);
      if (lookahead == 'n') ADVANCE(171);
      if (lookahead == 'x') ADVANCE(162);
      END_STATE();
    case 60:
      if (lookahead == 'd') ADVANCE(98);
      if (lookahead == 'n') ADVANCE(171);
      if (lookahead == 'x') ADVANCE(166);
      END_STATE();
    case 61:
      if (lookahead == 'd') ADVANCE(27);
      END_STATE();
    case 62:
      if (lookahead == 'd') ADVANCE(28);
      END_STATE();
    case 63:
      if (lookahead == 'e') ADVANCE(143);
      if (lookahead == 'p') ADVANCE(51);
      END_STATE();
    case 64:
      if (lookahead == 'e') ADVANCE(145);
      if (lookahead == 'f') ADVANCE(99);
      if (lookahead == 'i') ADVANCE(120);
      if (lookahead == 't') ADVANCE(146);
      if (lookahead == 'y') ADVANCE(121);
      END_STATE();
    case 65:
      if (lookahead == 'e') ADVANCE(145);
      if (lookahead == 'y') ADVANCE(121);
      END_STATE();
    case 66:
      if (lookahead == 'e') ADVANCE(61);
      END_STATE();
    case 67:
      if (lookahead == 'e') ADVANCE(401);
      END_STATE();
    case 68:
      if (lookahead == 'e') ADVANCE(403);
      END_STATE();
    case 69:
      if (lookahead == 'e') ADVANCE(262);
      END_STATE();
    case 70:
      if (lookahead == 'e') ADVANCE(221);
      END_STATE();
    case 71:
      if (lookahead == 'e') ADVANCE(206);
      END_STATE();
    case 72:
      if (lookahead == 'e') ADVANCE(274);
      END_STATE();
    case 73:
      if (lookahead == 'e') ADVANCE(43);
      END_STATE();
    case 74:
      if (lookahead == 'e') ADVANCE(56);
      END_STATE();
    case 75:
      if (lookahead == 'e') ADVANCE(113);
      END_STATE();
    case 76:
      if (lookahead == 'e') ADVANCE(57);
      END_STATE();
    case 77:
      if (lookahead == 'e') ADVANCE(152);
      END_STATE();
    case 78:
      if (lookahead == 'e') ADVANCE(58);
      END_STATE();
    case 79:
      if (lookahead == 'e') ADVANCE(128);
      END_STATE();
    case 80:
      if (lookahead == 'e') ADVANCE(47);
      END_STATE();
    case 81:
      if (lookahead == 'e') ADVANCE(42);
      if (lookahead == 'i') ADVANCE(119);
      END_STATE();
    case 82:
      if (lookahead == 'e') ADVANCE(123);
      END_STATE();
    case 83:
      if (lookahead == 'e') ADVANCE(147);
      END_STATE();
    case 84:
      if (lookahead == 'e') ADVANCE(62);
      END_STATE();
    case 85:
      if (lookahead == 'f') ADVANCE(412);
      END_STATE();
    case 86:
      if (lookahead == 'f') ADVANCE(412);
      if (lookahead == 't') ADVANCE(24);
      END_STATE();
    case 87:
      if (lookahead == 'f') ADVANCE(232);
      END_STATE();
    case 88:
      if (lookahead == 'g') ADVANCE(260);
      END_STATE();
    case 89:
      if (lookahead == 'g') ADVANCE(70);
      END_STATE();
    case 90:
      if (lookahead == 'g') ADVANCE(71);
      END_STATE();
    case 91:
      if (lookahead == 'i') ADVANCE(52);
      END_STATE();
    case 92:
      if (lookahead == 'i') ADVANCE(53);
      END_STATE();
    case 93:
      if (lookahead == 'i') ADVANCE(151);
      END_STATE();
    case 94:
      if (lookahead == 'i') ADVANCE(134);
      END_STATE();
    case 95:
      if (lookahead == 'i') ADVANCE(136);
      END_STATE();
    case 96:
      if (lookahead == 'i') ADVANCE(137);
      END_STATE();
    case 97:
      if (lookahead == 'i') ADVANCE(138);
      END_STATE();
    case 98:
      if (lookahead == 'i') ADVANCE(168);
      END_STATE();
    case 99:
      if (lookahead == 'i') ADVANCE(181);
      END_STATE();
    case 100:
      if (lookahead == 'i') ADVANCE(125);
      END_STATE();
    case 101:
      if (lookahead == 'k') ADVANCE(204);
      END_STATE();
    case 102:
      if (lookahead == 'k') ADVANCE(46);
      END_STATE();
    case 103:
      if (lookahead == 'l') ADVANCE(258);
      END_STATE();
    case 104:
      if (lookahead == 'l') ADVANCE(225);
      END_STATE();
    case 105:
      if (lookahead == 'l') ADVANCE(157);
      END_STATE();
    case 106:
      if (lookahead == 'l') ADVANCE(91);
      END_STATE();
    case 107:
      if (lookahead == 'l') ADVANCE(69);
      END_STATE();
    case 108:
      if (lookahead == 'm') ADVANCE(141);
      END_STATE();
    case 109:
      if (lookahead == 'm') ADVANCE(141);
      if (lookahead == 'n') ADVANCE(86);
      END_STATE();
    case 110:
      if (lookahead == 'm') ADVANCE(215);
      END_STATE();
    case 111:
      if (lookahead == 'm') ADVANCE(276);
      END_STATE();
    case 112:
      if (lookahead == 'n') ADVANCE(412);
      END_STATE();
    case 113:
      if (lookahead == 'n') ADVANCE(55);
      END_STATE();
    case 114:
      if (lookahead == 'n') ADVANCE(209);
      END_STATE();
    case 115:
      if (lookahead == 'n') ADVANCE(202);
      END_STATE();
    case 116:
      if (lookahead == 'n') ADVANCE(207);
      END_STATE();
    case 117:
      if (lookahead == 'n') ADVANCE(79);
      if (lookahead == 'p') ADVANCE(161);
      END_STATE();
    case 118:
      if (lookahead == 'n') ADVANCE(85);
      END_STATE();
    case 119:
      if (lookahead == 'n') ADVANCE(88);
      END_STATE();
    case 120:
      if (lookahead == 'n') ADVANCE(167);
      END_STATE();
    case 121:
      if (lookahead == 'n') ADVANCE(163);
      END_STATE();
    case 122:
      if (lookahead == 'n') ADVANCE(153);
      END_STATE();
    case 123:
      if (lookahead == 'n') ADVANCE(54);
      END_STATE();
    case 124:
      if (lookahead == 'n') ADVANCE(154);
      END_STATE();
    case 125:
      if (lookahead == 'n') ADVANCE(169);
      END_STATE();
    case 126:
      if (lookahead == 'o') ADVANCE(175);
      END_STATE();
    case 127:
      if (lookahead == 'o') ADVANCE(272);
      if (lookahead == 'r') ADVANCE(174);
      END_STATE();
    case 128:
      if (lookahead == 'o') ADVANCE(87);
      END_STATE();
    case 129:
      if (lookahead == 'o') ADVANCE(23);
      END_STATE();
    case 130:
      if (lookahead == 'o') ADVANCE(131);
      if (lookahead == 'y') ADVANCE(160);
      END_STATE();
    case 131:
      if (lookahead == 'o') ADVANCE(103);
      END_STATE();
    case 132:
      if (lookahead == 'o') ADVANCE(45);
      END_STATE();
    case 133:
      if (lookahead == 'o') ADVANCE(148);
      END_STATE();
    case 134:
      if (lookahead == 'o') ADVANCE(114);
      END_STATE();
    case 135:
      if (lookahead == 'o') ADVANCE(164);
      END_STATE();
    case 136:
      if (lookahead == 'o') ADVANCE(115);
      END_STATE();
    case 137:
      if (lookahead == 'o') ADVANCE(124);
      END_STATE();
    case 138:
      if (lookahead == 'o') ADVANCE(116);
      END_STATE();
    case 139:
      if (lookahead == 'p') ADVANCE(234);
      if (lookahead == 'x') ADVANCE(273);
      END_STATE();
    case 140:
      if (lookahead == 'p') ADVANCE(51);
      END_STATE();
    case 141:
      if (lookahead == 'p') ADVANCE(133);
      END_STATE();
    case 142:
      if (lookahead == 'p') ADVANCE(150);
      END_STATE();
    case 143:
      if (lookahead == 'p') ADVANCE(80);
      if (lookahead == 'q') ADVANCE(173);
      if (lookahead == 's') ADVANCE(83);
      if (lookahead == 't') ADVANCE(172);
      END_STATE();
    case 144:
      if (lookahead == 'p') ADVANCE(170);
      END_STATE();
    case 145:
      if (lookahead == 'r') ADVANCE(176);
      END_STATE();
    case 146:
      if (lookahead == 'r') ADVANCE(81);
      END_STATE();
    case 147:
      if (lookahead == 'r') ADVANCE(177);
      END_STATE();
    case 148:
      if (lookahead == 'r') ADVANCE(159);
      END_STATE();
    case 149:
      if (lookahead == 'r') ADVANCE(122);
      END_STATE();
    case 150:
      if (lookahead == 'r') ADVANCE(135);
      END_STATE();
    case 151:
      if (lookahead == 'r') ADVANCE(76);
      END_STATE();
    case 152:
      if (lookahead == 's') ADVANCE(266);
      END_STATE();
    case 153:
      if (lookahead == 's') ADVANCE(278);
      END_STATE();
    case 154:
      if (lookahead == 's') ADVANCE(270);
      END_STATE();
    case 155:
      if (lookahead == 's') ADVANCE(156);
      END_STATE();
    case 156:
      if (lookahead == 's') ADVANCE(40);
      END_STATE();
    case 157:
      if (lookahead == 's') ADVANCE(68);
      END_STATE();
    case 158:
      if (lookahead == 't') ADVANCE(264);
      END_STATE();
    case 159:
      if (lookahead == 't') ADVANCE(203);
      END_STATE();
    case 160:
      if (lookahead == 't') ADVANCE(77);
      END_STATE();
    case 161:
      if (lookahead == 't') ADVANCE(94);
      END_STATE();
    case 162:
      if (lookahead == 't') ADVANCE(75);
      END_STATE();
    case 163:
      if (lookahead == 't') ADVANCE(41);
      END_STATE();
    case 164:
      if (lookahead == 't') ADVANCE(129);
      END_STATE();
    case 165:
      if (lookahead == 't') ADVANCE(74);
      END_STATE();
    case 166:
      if (lookahead == 't') ADVANCE(82);
      END_STATE();
    case 167:
      if (lookahead == 't') ADVANCE(25);
      END_STATE();
    case 168:
      if (lookahead == 't') ADVANCE(95);
      END_STATE();
    case 169:
      if (lookahead == 't') ADVANCE(26);
      END_STATE();
    case 170:
      if (lookahead == 't') ADVANCE(97);
      END_STATE();
    case 171:
      if (lookahead == 'u') ADVANCE(110);
      END_STATE();
    case 172:
      if (lookahead == 'u') ADVANCE(149);
      END_STATE();
    case 173:
      if (lookahead == 'u') ADVANCE(93);
      END_STATE();
    case 174:
      if (lookahead == 'u') ADVANCE(67);
      END_STATE();
    case 175:
      if (lookahead == 'u') ADVANCE(49);
      END_STATE();
    case 176:
      if (lookahead == 'v') ADVANCE(92);
      END_STATE();
    case 177:
      if (lookahead == 'v') ADVANCE(78);
      END_STATE();
    case 178:
      if (lookahead == 'x') ADVANCE(273);
      END_STATE();
    case 179:
      if (lookahead == 'x') ADVANCE(198);
      END_STATE();
    case 180:
      if (lookahead == 'x') ADVANCE(66);
      END_STATE();
    case 181:
      if (lookahead == 'x') ADVANCE(84);
      END_STATE();
    case 182:
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(184);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(414);
      END_STATE();
    case 183:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(413);
      END_STATE();
    case 184:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(414);
      END_STATE();
    case 185:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(429);
      END_STATE();
    case 186:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(411);
      END_STATE();
    case 187:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(185);
      END_STATE();
    case 188:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(187);
      END_STATE();
    case 189:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(188);
      END_STATE();
    case 190:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(189);
      END_STATE();
    case 191:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(190);
      END_STATE();
    case 192:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(191);
      END_STATE();
    case 193:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(192);
      END_STATE();
    case 194:
      if (eof) ADVANCE(196);
      ADVANCE_MAP(
        '"', 422,
        '\'', 415,
        '(', 213,
        ')', 214,
        '+', 280,
        ',', 231,
        '-', 279,
        '.', 212,
        '/', 7,
        '0', 407,
        ':', 281,
        ';', 197,
        '<', 236,
        '=', 199,
        '>', 237,
        '[', 219,
        ']', 220,
        'b', 130,
        'd', 126,
        'e', 59,
        'f', 35,
        'i', 109,
        'm', 36,
        'n', 37,
        'o', 117,
        'p', 39,
        'r', 63,
        's', 64,
        't', 127,
        'u', 100,
        'w', 73,
        '{', 217,
        '}', 218,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(194);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(405);
      END_STATE();
    case 195:
      if (eof) ADVANCE(196);
      ADVANCE_MAP(
        '"', 142,
        '.', 211,
        '/', 7,
        '0', 409,
        ';', 197,
        '=', 199,
        'e', 60,
        'i', 108,
        'm', 44,
        'o', 144,
        'p', 38,
        'r', 140,
        's', 65,
        '}', 218,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(195);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(406);
      END_STATE();
    case 196:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 197:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 198:
      ACCEPT_TOKEN(anon_sym_syntax);
      END_STATE();
    case 199:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 200:
      ACCEPT_TOKEN(anon_sym_DQUOTEproto3_DQUOTE);
      END_STATE();
    case 201:
      ACCEPT_TOKEN(anon_sym_DQUOTEproto2_DQUOTE);
      END_STATE();
    case 202:
      ACCEPT_TOKEN(anon_sym_edition);
      END_STATE();
    case 203:
      ACCEPT_TOKEN(anon_sym_import);
      END_STATE();
    case 204:
      ACCEPT_TOKEN(anon_sym_weak);
      END_STATE();
    case 205:
      ACCEPT_TOKEN(anon_sym_public);
      END_STATE();
    case 206:
      ACCEPT_TOKEN(anon_sym_package);
      END_STATE();
    case 207:
      ACCEPT_TOKEN(anon_sym_option);
      END_STATE();
    case 208:
      ACCEPT_TOKEN(anon_sym_option);
      if (lookahead == 'a') ADVANCE(343);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 209:
      ACCEPT_TOKEN(anon_sym_option);
      if (lookahead == 'a') ADVANCE(104);
      END_STATE();
    case 210:
      ACCEPT_TOKEN(anon_sym_option);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 211:
      ACCEPT_TOKEN(anon_sym_DOT);
      END_STATE();
    case 212:
      ACCEPT_TOKEN(anon_sym_DOT);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(413);
      END_STATE();
    case 213:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 214:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 215:
      ACCEPT_TOKEN(anon_sym_enum);
      END_STATE();
    case 216:
      ACCEPT_TOKEN(anon_sym_enum);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 217:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 218:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 219:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 220:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 221:
      ACCEPT_TOKEN(anon_sym_message);
      END_STATE();
    case 222:
      ACCEPT_TOKEN(anon_sym_message);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 223:
      ACCEPT_TOKEN(anon_sym_extend);
      END_STATE();
    case 224:
      ACCEPT_TOKEN(anon_sym_extend);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 225:
      ACCEPT_TOKEN(anon_sym_optional);
      END_STATE();
    case 226:
      ACCEPT_TOKEN(anon_sym_optional);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 227:
      ACCEPT_TOKEN(anon_sym_required);
      END_STATE();
    case 228:
      ACCEPT_TOKEN(anon_sym_required);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 229:
      ACCEPT_TOKEN(anon_sym_repeated);
      END_STATE();
    case 230:
      ACCEPT_TOKEN(anon_sym_repeated);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 231:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 232:
      ACCEPT_TOKEN(anon_sym_oneof);
      END_STATE();
    case 233:
      ACCEPT_TOKEN(anon_sym_oneof);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 234:
      ACCEPT_TOKEN(anon_sym_map);
      END_STATE();
    case 235:
      ACCEPT_TOKEN(anon_sym_map);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 236:
      ACCEPT_TOKEN(anon_sym_LT);
      END_STATE();
    case 237:
      ACCEPT_TOKEN(anon_sym_GT);
      END_STATE();
    case 238:
      ACCEPT_TOKEN(anon_sym_int32);
      END_STATE();
    case 239:
      ACCEPT_TOKEN(anon_sym_int32);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 240:
      ACCEPT_TOKEN(anon_sym_int64);
      END_STATE();
    case 241:
      ACCEPT_TOKEN(anon_sym_int64);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 242:
      ACCEPT_TOKEN(anon_sym_uint32);
      END_STATE();
    case 243:
      ACCEPT_TOKEN(anon_sym_uint32);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 244:
      ACCEPT_TOKEN(anon_sym_uint64);
      END_STATE();
    case 245:
      ACCEPT_TOKEN(anon_sym_uint64);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 246:
      ACCEPT_TOKEN(anon_sym_sint32);
      END_STATE();
    case 247:
      ACCEPT_TOKEN(anon_sym_sint32);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 248:
      ACCEPT_TOKEN(anon_sym_sint64);
      END_STATE();
    case 249:
      ACCEPT_TOKEN(anon_sym_sint64);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 250:
      ACCEPT_TOKEN(anon_sym_fixed32);
      END_STATE();
    case 251:
      ACCEPT_TOKEN(anon_sym_fixed32);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 252:
      ACCEPT_TOKEN(anon_sym_fixed64);
      END_STATE();
    case 253:
      ACCEPT_TOKEN(anon_sym_fixed64);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 254:
      ACCEPT_TOKEN(anon_sym_sfixed32);
      END_STATE();
    case 255:
      ACCEPT_TOKEN(anon_sym_sfixed32);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 256:
      ACCEPT_TOKEN(anon_sym_sfixed64);
      END_STATE();
    case 257:
      ACCEPT_TOKEN(anon_sym_sfixed64);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 258:
      ACCEPT_TOKEN(anon_sym_bool);
      END_STATE();
    case 259:
      ACCEPT_TOKEN(anon_sym_bool);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 260:
      ACCEPT_TOKEN(anon_sym_string);
      END_STATE();
    case 261:
      ACCEPT_TOKEN(anon_sym_string);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 262:
      ACCEPT_TOKEN(anon_sym_double);
      END_STATE();
    case 263:
      ACCEPT_TOKEN(anon_sym_double);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 264:
      ACCEPT_TOKEN(anon_sym_float);
      END_STATE();
    case 265:
      ACCEPT_TOKEN(anon_sym_float);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 266:
      ACCEPT_TOKEN(anon_sym_bytes);
      END_STATE();
    case 267:
      ACCEPT_TOKEN(anon_sym_bytes);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 268:
      ACCEPT_TOKEN(anon_sym_reserved);
      END_STATE();
    case 269:
      ACCEPT_TOKEN(anon_sym_reserved);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 270:
      ACCEPT_TOKEN(anon_sym_extensions);
      END_STATE();
    case 271:
      ACCEPT_TOKEN(anon_sym_extensions);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 272:
      ACCEPT_TOKEN(anon_sym_to);
      END_STATE();
    case 273:
      ACCEPT_TOKEN(anon_sym_max);
      END_STATE();
    case 274:
      ACCEPT_TOKEN(anon_sym_service);
      END_STATE();
    case 275:
      ACCEPT_TOKEN(anon_sym_rpc);
      END_STATE();
    case 276:
      ACCEPT_TOKEN(anon_sym_stream);
      END_STATE();
    case 277:
      ACCEPT_TOKEN(anon_sym_stream);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 278:
      ACCEPT_TOKEN(anon_sym_returns);
      END_STATE();
    case 279:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 280:
      ACCEPT_TOKEN(anon_sym_PLUS);
      END_STATE();
    case 281:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 282:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '2') ADVANCE(239);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 283:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '2') ADVANCE(247);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 284:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '2') ADVANCE(243);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 285:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '2') ADVANCE(251);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 286:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '2') ADVANCE(255);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 287:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '3') ADVANCE(282);
      if (lookahead == '6') ADVANCE(292);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 288:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '3') ADVANCE(283);
      if (lookahead == '6') ADVANCE(293);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 289:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '3') ADVANCE(284);
      if (lookahead == '6') ADVANCE(294);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 290:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '3') ADVANCE(285);
      if (lookahead == '6') ADVANCE(295);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 291:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '3') ADVANCE(286);
      if (lookahead == '6') ADVANCE(296);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 292:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '4') ADVANCE(241);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 293:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '4') ADVANCE(249);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 294:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '4') ADVANCE(245);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 295:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '4') ADVANCE(253);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 296:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '4') ADVANCE(257);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 297:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(368);
      if (lookahead == 'e') ADVANCE(379);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 298:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(333);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 299:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(347);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 300:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(384);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 301:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(344);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 302:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(348);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 303:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(388);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 304:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'b') ADVANCE(345);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 305:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(224);
      if (lookahead == 's') ADVANCE(338);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 306:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(230);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 307:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(228);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 308:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(269);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 309:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(290);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 310:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(291);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 311:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(369);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 312:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(309);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 313:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(263);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 314:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(222);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 315:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(402);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 316:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(404);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 317:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(349);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 318:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(372);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 319:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(306);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 320:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(370);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 321:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(377);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 322:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(303);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 323:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(307);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 324:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(363);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 325:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(308);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 326:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(299);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 327:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(381);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 328:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(310);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 329:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(400);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 330:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(233);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 331:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(341);
      if (lookahead == 'i') ADVANCE(358);
      if (lookahead == 't') ADVANCE(373);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 332:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(261);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 333:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(314);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 334:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(398);
      if (lookahead == 'l') ADVANCE(362);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 335:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(356);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 336:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(375);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 337:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(365);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 338:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(366);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 339:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(367);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 340:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(359);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 341:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(399);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 342:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(259);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 343:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(226);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 344:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(382);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 345:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(313);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 346:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'm') ADVANCE(216);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 347:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'm') ADVANCE(277);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 348:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(400);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 349:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(305);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 350:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(208);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 351:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(210);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 352:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(324);
      if (lookahead == 'p') ADVANCE(386);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 353:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(383);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 354:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(394);
      if (lookahead == 'x') ADVANCE(387);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 355:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(329);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 356:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(332);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 357:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(378);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 358:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(389);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 359:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(391);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 360:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(393);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 361:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(342);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 362:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(300);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 363:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(330);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 364:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(361);
      if (lookahead == 'y') ADVANCE(385);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 365:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(350);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 366:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(357);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 367:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(351);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 368:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'p') ADVANCE(235);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 369:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'p') ADVANCE(322);
      if (lookahead == 'q') ADVANCE(395);
      if (lookahead == 's') ADVANCE(318);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 370:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'p') ADVANCE(322);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 371:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'p') ADVANCE(392);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 372:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(397);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 373:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(335);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 374:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(396);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 375:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(323);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 376:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(326);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 377:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(267);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 378:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(271);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 379:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(380);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 380:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(298);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 381:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(318);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 382:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(316);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 383:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(287);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 384:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(265);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 385:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(321);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 386:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(337);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 387:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(317);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 388:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(319);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 389:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(288);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 390:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(376);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 391:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(289);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 392:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(339);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 393:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(304);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 394:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(346);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 395:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(336);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 396:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(315);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 397:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'v') ADVANCE(325);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 398:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'x') ADVANCE(312);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 399:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'x') ADVANCE(328);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 400:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 401:
      ACCEPT_TOKEN(sym_true);
      END_STATE();
    case 402:
      ACCEPT_TOKEN(sym_true);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 403:
      ACCEPT_TOKEN(sym_false);
      END_STATE();
    case 404:
      ACCEPT_TOKEN(sym_false);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(400);
      END_STATE();
    case 405:
      ACCEPT_TOKEN(sym_decimal_lit);
      if (lookahead == '.') ADVANCE(413);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(182);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(405);
      END_STATE();
    case 406:
      ACCEPT_TOKEN(sym_decimal_lit);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(406);
      END_STATE();
    case 407:
      ACCEPT_TOKEN(sym_octal_lit);
      if (lookahead == '.') ADVANCE(413);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(182);
      if (lookahead == 'X' ||
          lookahead == 'x') ADVANCE(186);
      if (lookahead == '8' ||
          lookahead == '9') ADVANCE(10);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(408);
      END_STATE();
    case 408:
      ACCEPT_TOKEN(sym_octal_lit);
      if (lookahead == '.') ADVANCE(413);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(182);
      if (lookahead == '8' ||
          lookahead == '9') ADVANCE(10);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(408);
      END_STATE();
    case 409:
      ACCEPT_TOKEN(sym_octal_lit);
      if (lookahead == 'X' ||
          lookahead == 'x') ADVANCE(186);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(410);
      END_STATE();
    case 410:
      ACCEPT_TOKEN(sym_octal_lit);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(410);
      END_STATE();
    case 411:
      ACCEPT_TOKEN(sym_hex_lit);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(411);
      END_STATE();
    case 412:
      ACCEPT_TOKEN(sym_float_lit);
      END_STATE();
    case 413:
      ACCEPT_TOKEN(sym_float_lit);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(182);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(413);
      END_STATE();
    case 414:
      ACCEPT_TOKEN(sym_float_lit);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(414);
      END_STATE();
    case 415:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 416:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead == '\n') ADVANCE(421);
      if (lookahead != 0 &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(416);
      END_STATE();
    case 417:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead == '*') ADVANCE(419);
      if (lookahead == '/') ADVANCE(416);
      if (lookahead != 0 &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(421);
      END_STATE();
    case 418:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead == '*') ADVANCE(418);
      if (lookahead == '/') ADVANCE(421);
      if (lookahead != 0 &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(419);
      END_STATE();
    case 419:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead == '*') ADVANCE(418);
      if (lookahead != 0 &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(419);
      END_STATE();
    case 420:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead == '/') ADVANCE(417);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(420);
      if (lookahead != 0 &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(421);
      END_STATE();
    case 421:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead != 0 &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(421);
      END_STATE();
    case 422:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 423:
      ACCEPT_TOKEN(aux_sym_string_token2);
      if (lookahead == '\n') ADVANCE(428);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(423);
      END_STATE();
    case 424:
      ACCEPT_TOKEN(aux_sym_string_token2);
      if (lookahead == '*') ADVANCE(426);
      if (lookahead == '/') ADVANCE(423);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(428);
      END_STATE();
    case 425:
      ACCEPT_TOKEN(aux_sym_string_token2);
      if (lookahead == '*') ADVANCE(425);
      if (lookahead == '/') ADVANCE(428);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(426);
      END_STATE();
    case 426:
      ACCEPT_TOKEN(aux_sym_string_token2);
      if (lookahead == '*') ADVANCE(425);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(426);
      END_STATE();
    case 427:
      ACCEPT_TOKEN(aux_sym_string_token2);
      if (lookahead == '/') ADVANCE(424);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(427);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(428);
      END_STATE();
    case 428:
      ACCEPT_TOKEN(aux_sym_string_token2);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(428);
      END_STATE();
    case 429:
      ACCEPT_TOKEN(sym_escape_sequence);
      END_STATE();
    case 430:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(429);
      END_STATE();
    case 431:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(430);
      END_STATE();
    case 432:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 433:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(433);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 195},
  [2] = {.lex_state = 12},
  [3] = {.lex_state = 12},
  [4] = {.lex_state = 12},
  [5] = {.lex_state = 12},
  [6] = {.lex_state = 12},
  [7] = {.lex_state = 12},
  [8] = {.lex_state = 12},
  [9] = {.lex_state = 12},
  [10] = {.lex_state = 12},
  [11] = {.lex_state = 12},
  [12] = {.lex_state = 12},
  [13] = {.lex_state = 12},
  [14] = {.lex_state = 12},
  [15] = {.lex_state = 12},
  [16] = {.lex_state = 12},
  [17] = {.lex_state = 12},
  [18] = {.lex_state = 12},
  [19] = {.lex_state = 12},
  [20] = {.lex_state = 12},
  [21] = {.lex_state = 12},
  [22] = {.lex_state = 12},
  [23] = {.lex_state = 12},
  [24] = {.lex_state = 12},
  [25] = {.lex_state = 12},
  [26] = {.lex_state = 12},
  [27] = {.lex_state = 12},
  [28] = {.lex_state = 12},
  [29] = {.lex_state = 12},
  [30] = {.lex_state = 11},
  [31] = {.lex_state = 11},
  [32] = {.lex_state = 11},
  [33] = {.lex_state = 2},
  [34] = {.lex_state = 11},
  [35] = {.lex_state = 2},
  [36] = {.lex_state = 11},
  [37] = {.lex_state = 13},
  [38] = {.lex_state = 11},
  [39] = {.lex_state = 2},
  [40] = {.lex_state = 2},
  [41] = {.lex_state = 14},
  [42] = {.lex_state = 11},
  [43] = {.lex_state = 2},
  [44] = {.lex_state = 14},
  [45] = {.lex_state = 14},
  [46] = {.lex_state = 11},
  [47] = {.lex_state = 2},
  [48] = {.lex_state = 2},
  [49] = {.lex_state = 11},
  [50] = {.lex_state = 2},
  [51] = {.lex_state = 2},
  [52] = {.lex_state = 2},
  [53] = {.lex_state = 2},
  [54] = {.lex_state = 2},
  [55] = {.lex_state = 2},
  [56] = {.lex_state = 2},
  [57] = {.lex_state = 195},
  [58] = {.lex_state = 195},
  [59] = {.lex_state = 195},
  [60] = {.lex_state = 195},
  [61] = {.lex_state = 2},
  [62] = {.lex_state = 1},
  [63] = {.lex_state = 1},
  [64] = {.lex_state = 0},
  [65] = {.lex_state = 17},
  [66] = {.lex_state = 1},
  [67] = {.lex_state = 195},
  [68] = {.lex_state = 17},
  [69] = {.lex_state = 17},
  [70] = {.lex_state = 195},
  [71] = {.lex_state = 17},
  [72] = {.lex_state = 17},
  [73] = {.lex_state = 1},
  [74] = {.lex_state = 1},
  [75] = {.lex_state = 1},
  [76] = {.lex_state = 195},
  [77] = {.lex_state = 195},
  [78] = {.lex_state = 195},
  [79] = {.lex_state = 195},
  [80] = {.lex_state = 195},
  [81] = {.lex_state = 195},
  [82] = {.lex_state = 1},
  [83] = {.lex_state = 195},
  [84] = {.lex_state = 195},
  [85] = {.lex_state = 195},
  [86] = {.lex_state = 195},
  [87] = {.lex_state = 195},
  [88] = {.lex_state = 1},
  [89] = {.lex_state = 195},
  [90] = {.lex_state = 195},
  [91] = {.lex_state = 195},
  [92] = {.lex_state = 195},
  [93] = {.lex_state = 195},
  [94] = {.lex_state = 195},
  [95] = {.lex_state = 195},
  [96] = {.lex_state = 1},
  [97] = {.lex_state = 1},
  [98] = {.lex_state = 195},
  [99] = {.lex_state = 1},
  [100] = {.lex_state = 1},
  [101] = {.lex_state = 1},
  [102] = {.lex_state = 1},
  [103] = {.lex_state = 1},
  [104] = {.lex_state = 195},
  [105] = {.lex_state = 1},
  [106] = {.lex_state = 195},
  [107] = {.lex_state = 195},
  [108] = {.lex_state = 195},
  [109] = {.lex_state = 1},
  [110] = {.lex_state = 0},
  [111] = {.lex_state = 1},
  [112] = {.lex_state = 1},
  [113] = {.lex_state = 1},
  [114] = {.lex_state = 1},
  [115] = {.lex_state = 195},
  [116] = {.lex_state = 195},
  [117] = {.lex_state = 15},
  [118] = {.lex_state = 1},
  [119] = {.lex_state = 15},
  [120] = {.lex_state = 17},
  [121] = {.lex_state = 1},
  [122] = {.lex_state = 1},
  [123] = {.lex_state = 1},
  [124] = {.lex_state = 1},
  [125] = {.lex_state = 1},
  [126] = {.lex_state = 195},
  [127] = {.lex_state = 195},
  [128] = {.lex_state = 17},
  [129] = {.lex_state = 1},
  [130] = {.lex_state = 17},
  [131] = {.lex_state = 1},
  [132] = {.lex_state = 1},
  [133] = {.lex_state = 1},
  [134] = {.lex_state = 1},
  [135] = {.lex_state = 1},
  [136] = {.lex_state = 17},
  [137] = {.lex_state = 1},
  [138] = {.lex_state = 1},
  [139] = {.lex_state = 1},
  [140] = {.lex_state = 16},
  [141] = {.lex_state = 195},
  [142] = {.lex_state = 195},
  [143] = {.lex_state = 1},
  [144] = {.lex_state = 195},
  [145] = {.lex_state = 1},
  [146] = {.lex_state = 1},
  [147] = {.lex_state = 16},
  [148] = {.lex_state = 1},
  [149] = {.lex_state = 17},
  [150] = {.lex_state = 0},
  [151] = {.lex_state = 1},
  [152] = {.lex_state = 195},
  [153] = {.lex_state = 15},
  [154] = {.lex_state = 1},
  [155] = {.lex_state = 0},
  [156] = {.lex_state = 1},
  [157] = {.lex_state = 1},
  [158] = {.lex_state = 1},
  [159] = {.lex_state = 6},
  [160] = {.lex_state = 3},
  [161] = {.lex_state = 0},
  [162] = {.lex_state = 1},
  [163] = {.lex_state = 6},
  [164] = {.lex_state = 3},
  [165] = {.lex_state = 1},
  [166] = {.lex_state = 1},
  [167] = {.lex_state = 1},
  [168] = {.lex_state = 195},
  [169] = {.lex_state = 195},
  [170] = {.lex_state = 195},
  [171] = {.lex_state = 195},
  [172] = {.lex_state = 195},
  [173] = {.lex_state = 195},
  [174] = {.lex_state = 6},
  [175] = {.lex_state = 3},
  [176] = {.lex_state = 1},
  [177] = {.lex_state = 0},
  [178] = {.lex_state = 0},
  [179] = {.lex_state = 0},
  [180] = {.lex_state = 0},
  [181] = {.lex_state = 0},
  [182] = {.lex_state = 195},
  [183] = {.lex_state = 1},
  [184] = {.lex_state = 0},
  [185] = {.lex_state = 0},
  [186] = {.lex_state = 195},
  [187] = {.lex_state = 0},
  [188] = {.lex_state = 195},
  [189] = {.lex_state = 0},
  [190] = {.lex_state = 0},
  [191] = {.lex_state = 0},
  [192] = {.lex_state = 0},
  [193] = {.lex_state = 0},
  [194] = {.lex_state = 0},
  [195] = {.lex_state = 0},
  [196] = {.lex_state = 0},
  [197] = {.lex_state = 0},
  [198] = {.lex_state = 1},
  [199] = {.lex_state = 0},
  [200] = {.lex_state = 195},
  [201] = {.lex_state = 0},
  [202] = {.lex_state = 0},
  [203] = {.lex_state = 0},
  [204] = {.lex_state = 1},
  [205] = {.lex_state = 1},
  [206] = {.lex_state = 0},
  [207] = {.lex_state = 1},
  [208] = {.lex_state = 1},
  [209] = {.lex_state = 0},
  [210] = {.lex_state = 1},
  [211] = {.lex_state = 0},
  [212] = {.lex_state = 0},
  [213] = {.lex_state = 1},
  [214] = {.lex_state = 0},
  [215] = {.lex_state = 1},
  [216] = {.lex_state = 1},
  [217] = {.lex_state = 0},
  [218] = {.lex_state = 1},
  [219] = {.lex_state = 1},
  [220] = {.lex_state = 0},
  [221] = {.lex_state = 1},
  [222] = {.lex_state = 1},
  [223] = {.lex_state = 1},
  [224] = {.lex_state = 1},
  [225] = {.lex_state = 0},
  [226] = {.lex_state = 0},
  [227] = {.lex_state = 1},
  [228] = {.lex_state = 0},
  [229] = {.lex_state = 0},
  [230] = {.lex_state = 1},
  [231] = {.lex_state = 0},
  [232] = {.lex_state = 0},
  [233] = {.lex_state = 1},
  [234] = {.lex_state = 0},
  [235] = {.lex_state = 0},
  [236] = {.lex_state = 1},
  [237] = {.lex_state = 0},
  [238] = {.lex_state = 0},
  [239] = {.lex_state = 0},
  [240] = {.lex_state = 0},
  [241] = {.lex_state = 0},
  [242] = {.lex_state = 1},
  [243] = {.lex_state = 1},
  [244] = {.lex_state = 1},
  [245] = {.lex_state = 0},
  [246] = {.lex_state = 1},
  [247] = {.lex_state = 1},
  [248] = {.lex_state = 0},
  [249] = {.lex_state = 1},
  [250] = {.lex_state = 1},
  [251] = {.lex_state = 195},
  [252] = {.lex_state = 0},
  [253] = {.lex_state = 0},
  [254] = {.lex_state = 0},
  [255] = {.lex_state = 1},
  [256] = {.lex_state = 0},
  [257] = {.lex_state = 0},
  [258] = {.lex_state = 0},
  [259] = {.lex_state = 0},
  [260] = {.lex_state = 0},
  [261] = {.lex_state = 0},
  [262] = {.lex_state = 0},
  [263] = {.lex_state = 0},
  [264] = {.lex_state = 0},
  [265] = {.lex_state = 0},
  [266] = {.lex_state = 0},
  [267] = {.lex_state = 0},
  [268] = {.lex_state = 0},
  [269] = {.lex_state = 0},
  [270] = {.lex_state = 0},
  [271] = {.lex_state = 0},
  [272] = {.lex_state = 0},
  [273] = {.lex_state = 0},
  [274] = {.lex_state = 0},
  [275] = {.lex_state = 0},
  [276] = {.lex_state = 0},
  [277] = {.lex_state = 1},
  [278] = {.lex_state = 0},
  [279] = {.lex_state = 0},
  [280] = {.lex_state = 0},
  [281] = {.lex_state = 0},
  [282] = {.lex_state = 0},
  [283] = {.lex_state = 0},
  [284] = {.lex_state = 0},
  [285] = {.lex_state = 0},
  [286] = {.lex_state = 1},
  [287] = {.lex_state = 0},
  [288] = {.lex_state = 0},
  [289] = {.lex_state = 0},
  [290] = {.lex_state = 0},
  [291] = {.lex_state = 0},
  [292] = {.lex_state = 0},
  [293] = {.lex_state = 0},
  [294] = {.lex_state = 195},
  [295] = {.lex_state = 0},
  [296] = {.lex_state = 0},
  [297] = {.lex_state = 0},
  [298] = {.lex_state = 0},
  [299] = {.lex_state = 0},
  [300] = {.lex_state = 0},
  [301] = {.lex_state = 0},
  [302] = {.lex_state = 0},
  [303] = {.lex_state = 0},
  [304] = {.lex_state = 0},
  [305] = {.lex_state = 0},
  [306] = {.lex_state = 0},
  [307] = {.lex_state = 0},
  [308] = {.lex_state = 0},
  [309] = {.lex_state = 0},
  [310] = {.lex_state = 0},
  [311] = {.lex_state = 0},
  [312] = {.lex_state = 0},
  [313] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_syntax] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_edition] = ACTIONS(1),
    [anon_sym_import] = ACTIONS(1),
    [anon_sym_weak] = ACTIONS(1),
    [anon_sym_public] = ACTIONS(1),
    [anon_sym_package] = ACTIONS(1),
    [anon_sym_option] = ACTIONS(1),
    [anon_sym_DOT] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_enum] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [anon_sym_message] = ACTIONS(1),
    [anon_sym_extend] = ACTIONS(1),
    [anon_sym_optional] = ACTIONS(1),
    [anon_sym_required] = ACTIONS(1),
    [anon_sym_repeated] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_oneof] = ACTIONS(1),
    [anon_sym_map] = ACTIONS(1),
    [anon_sym_LT] = ACTIONS(1),
    [anon_sym_GT] = ACTIONS(1),
    [anon_sym_int32] = ACTIONS(1),
    [anon_sym_int64] = ACTIONS(1),
    [anon_sym_uint32] = ACTIONS(1),
    [anon_sym_uint64] = ACTIONS(1),
    [anon_sym_sint32] = ACTIONS(1),
    [anon_sym_sint64] = ACTIONS(1),
    [anon_sym_fixed32] = ACTIONS(1),
    [anon_sym_fixed64] = ACTIONS(1),
    [anon_sym_sfixed32] = ACTIONS(1),
    [anon_sym_sfixed64] = ACTIONS(1),
    [anon_sym_bool] = ACTIONS(1),
    [anon_sym_string] = ACTIONS(1),
    [anon_sym_double] = ACTIONS(1),
    [anon_sym_float] = ACTIONS(1),
    [anon_sym_bytes] = ACTIONS(1),
    [anon_sym_reserved] = ACTIONS(1),
    [anon_sym_extensions] = ACTIONS(1),
    [anon_sym_to] = ACTIONS(1),
    [anon_sym_max] = ACTIONS(1),
    [anon_sym_service] = ACTIONS(1),
    [anon_sym_rpc] = ACTIONS(1),
    [anon_sym_stream] = ACTIONS(1),
    [anon_sym_returns] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [anon_sym_PLUS] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [sym_true] = ACTIONS(1),
    [sym_false] = ACTIONS(1),
    [sym_decimal_lit] = ACTIONS(1),
    [sym_octal_lit] = ACTIONS(1),
    [sym_hex_lit] = ACTIONS(1),
    [sym_float_lit] = ACTIONS(1),
    [anon_sym_SQUOTE] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [sym_escape_sequence] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
  },
  [1] = {
    [sym_source_file] = STATE(275),
    [sym_empty_statement] = STATE(58),
    [sym_syntax] = STATE(59),
    [sym_edition] = STATE(59),
    [sym_import] = STATE(58),
    [sym_package] = STATE(58),
    [sym_option] = STATE(58),
    [sym_enum] = STATE(58),
    [sym_message] = STATE(58),
    [sym_extend] = STATE(58),
    [sym_service] = STATE(58),
    [aux_sym_source_file_repeat1] = STATE(58),
    [ts_builtin_sym_end] = ACTIONS(5),
    [anon_sym_SEMI] = ACTIONS(7),
    [anon_sym_syntax] = ACTIONS(9),
    [anon_sym_edition] = ACTIONS(11),
    [anon_sym_import] = ACTIONS(13),
    [anon_sym_package] = ACTIONS(15),
    [anon_sym_option] = ACTIONS(17),
    [anon_sym_enum] = ACTIONS(19),
    [anon_sym_message] = ACTIONS(21),
    [anon_sym_extend] = ACTIONS(23),
    [anon_sym_service] = ACTIONS(25),
    [sym_comment] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 20,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(27), 1,
      anon_sym_SEMI,
    ACTIONS(29), 1,
      anon_sym_option,
    ACTIONS(31), 1,
      anon_sym_DOT,
    ACTIONS(33), 1,
      anon_sym_enum,
    ACTIONS(35), 1,
      anon_sym_RBRACE,
    ACTIONS(37), 1,
      anon_sym_message,
    ACTIONS(39), 1,
      anon_sym_extend,
    ACTIONS(43), 1,
      anon_sym_repeated,
    ACTIONS(45), 1,
      anon_sym_oneof,
    ACTIONS(47), 1,
      anon_sym_map,
    ACTIONS(51), 1,
      anon_sym_reserved,
    ACTIONS(53), 1,
      anon_sym_extensions,
    ACTIONS(55), 1,
      sym_identifier,
    STATE(224), 1,
      sym_message_or_enum_type,
    STATE(247), 1,
      sym_type,
    STATE(250), 1,
      aux_sym_message_or_enum_type_repeat1,
    ACTIONS(41), 2,
      anon_sym_optional,
      anon_sym_required,
    STATE(3), 11,
      sym_empty_statement,
      sym_option,
      sym_enum,
      sym_message,
      sym_extend,
      sym_field,
      sym_oneof,
      sym_map_field,
      sym_reserved,
      sym_extensions,
      aux_sym_message_body_repeat1,
    ACTIONS(49), 15,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
  [86] = 20,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(27), 1,
      anon_sym_SEMI,
    ACTIONS(29), 1,
      anon_sym_option,
    ACTIONS(31), 1,
      anon_sym_DOT,
    ACTIONS(33), 1,
      anon_sym_enum,
    ACTIONS(37), 1,
      anon_sym_message,
    ACTIONS(39), 1,
      anon_sym_extend,
    ACTIONS(43), 1,
      anon_sym_repeated,
    ACTIONS(45), 1,
      anon_sym_oneof,
    ACTIONS(47), 1,
      anon_sym_map,
    ACTIONS(51), 1,
      anon_sym_reserved,
    ACTIONS(53), 1,
      anon_sym_extensions,
    ACTIONS(55), 1,
      sym_identifier,
    ACTIONS(57), 1,
      anon_sym_RBRACE,
    STATE(224), 1,
      sym_message_or_enum_type,
    STATE(247), 1,
      sym_type,
    STATE(250), 1,
      aux_sym_message_or_enum_type_repeat1,
    ACTIONS(41), 2,
      anon_sym_optional,
      anon_sym_required,
    STATE(4), 11,
      sym_empty_statement,
      sym_option,
      sym_enum,
      sym_message,
      sym_extend,
      sym_field,
      sym_oneof,
      sym_map_field,
      sym_reserved,
      sym_extensions,
      aux_sym_message_body_repeat1,
    ACTIONS(49), 15,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
  [172] = 20,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(59), 1,
      anon_sym_SEMI,
    ACTIONS(62), 1,
      anon_sym_option,
    ACTIONS(65), 1,
      anon_sym_DOT,
    ACTIONS(68), 1,
      anon_sym_enum,
    ACTIONS(71), 1,
      anon_sym_RBRACE,
    ACTIONS(73), 1,
      anon_sym_message,
    ACTIONS(76), 1,
      anon_sym_extend,
    ACTIONS(82), 1,
      anon_sym_repeated,
    ACTIONS(85), 1,
      anon_sym_oneof,
    ACTIONS(88), 1,
      anon_sym_map,
    ACTIONS(94), 1,
      anon_sym_reserved,
    ACTIONS(97), 1,
      anon_sym_extensions,
    ACTIONS(100), 1,
      sym_identifier,
    STATE(224), 1,
      sym_message_or_enum_type,
    STATE(247), 1,
      sym_type,
    STATE(250), 1,
      aux_sym_message_or_enum_type_repeat1,
    ACTIONS(79), 2,
      anon_sym_optional,
      anon_sym_required,
    STATE(4), 11,
      sym_empty_statement,
      sym_option,
      sym_enum,
      sym_message,
      sym_extend,
      sym_field,
      sym_oneof,
      sym_map_field,
      sym_reserved,
      sym_extensions,
      aux_sym_message_body_repeat1,
    ACTIONS(91), 15,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
  [258] = 20,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(27), 1,
      anon_sym_SEMI,
    ACTIONS(29), 1,
      anon_sym_option,
    ACTIONS(31), 1,
      anon_sym_DOT,
    ACTIONS(33), 1,
      anon_sym_enum,
    ACTIONS(37), 1,
      anon_sym_message,
    ACTIONS(39), 1,
      anon_sym_extend,
    ACTIONS(43), 1,
      anon_sym_repeated,
    ACTIONS(45), 1,
      anon_sym_oneof,
    ACTIONS(47), 1,
      anon_sym_map,
    ACTIONS(51), 1,
      anon_sym_reserved,
    ACTIONS(53), 1,
      anon_sym_extensions,
    ACTIONS(55), 1,
      sym_identifier,
    ACTIONS(103), 1,
      anon_sym_RBRACE,
    STATE(224), 1,
      sym_message_or_enum_type,
    STATE(247), 1,
      sym_type,
    STATE(250), 1,
      aux_sym_message_or_enum_type_repeat1,
    ACTIONS(41), 2,
      anon_sym_optional,
      anon_sym_required,
    STATE(6), 11,
      sym_empty_statement,
      sym_option,
      sym_enum,
      sym_message,
      sym_extend,
      sym_field,
      sym_oneof,
      sym_map_field,
      sym_reserved,
      sym_extensions,
      aux_sym_message_body_repeat1,
    ACTIONS(49), 15,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
  [344] = 20,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(27), 1,
      anon_sym_SEMI,
    ACTIONS(29), 1,
      anon_sym_option,
    ACTIONS(31), 1,
      anon_sym_DOT,
    ACTIONS(33), 1,
      anon_sym_enum,
    ACTIONS(37), 1,
      anon_sym_message,
    ACTIONS(39), 1,
      anon_sym_extend,
    ACTIONS(43), 1,
      anon_sym_repeated,
    ACTIONS(45), 1,
      anon_sym_oneof,
    ACTIONS(47), 1,
      anon_sym_map,
    ACTIONS(51), 1,
      anon_sym_reserved,
    ACTIONS(53), 1,
      anon_sym_extensions,
    ACTIONS(55), 1,
      sym_identifier,
    ACTIONS(105), 1,
      anon_sym_RBRACE,
    STATE(224), 1,
      sym_message_or_enum_type,
    STATE(247), 1,
      sym_type,
    STATE(250), 1,
      aux_sym_message_or_enum_type_repeat1,
    ACTIONS(41), 2,
      anon_sym_optional,
      anon_sym_required,
    STATE(4), 11,
      sym_empty_statement,
      sym_option,
      sym_enum,
      sym_message,
      sym_extend,
      sym_field,
      sym_oneof,
      sym_map_field,
      sym_reserved,
      sym_extensions,
      aux_sym_message_body_repeat1,
    ACTIONS(49), 15,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
  [430] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(109), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [468] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(111), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(113), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [506] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(115), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(117), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [544] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(119), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(121), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [582] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(123), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(125), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [620] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(127), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(129), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [658] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(131), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(133), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [696] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(135), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(137), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [734] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(139), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(141), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [772] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(143), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(145), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [810] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(147), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(149), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [848] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(151), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(153), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [886] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(155), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(157), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [924] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(159), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(161), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [962] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(163), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(165), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [1000] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(167), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(169), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [1038] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(171), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(173), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [1076] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(175), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(177), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [1114] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(179), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(181), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [1152] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(183), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(185), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [1190] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(187), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(189), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [1228] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(191), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(193), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [1266] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(195), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(197), 27,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_optional,
      anon_sym_required,
      anon_sym_repeated,
      anon_sym_oneof,
      anon_sym_map,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      anon_sym_reserved,
      anon_sym_extensions,
      sym_identifier,
  [1304] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(199), 1,
      anon_sym_SEMI,
    ACTIONS(202), 1,
      anon_sym_option,
    ACTIONS(205), 1,
      anon_sym_DOT,
    ACTIONS(208), 1,
      anon_sym_RBRACE,
    ACTIONS(213), 1,
      sym_identifier,
    STATE(221), 1,
      sym_type,
    STATE(224), 1,
      sym_message_or_enum_type,
    STATE(250), 1,
      aux_sym_message_or_enum_type_repeat1,
    STATE(30), 4,
      sym_empty_statement,
      sym_option,
      sym_oneof_field,
      aux_sym_oneof_body_repeat1,
    ACTIONS(210), 15,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
  [1355] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(31), 1,
      anon_sym_DOT,
    ACTIONS(55), 1,
      sym_identifier,
    ACTIONS(216), 1,
      anon_sym_SEMI,
    ACTIONS(218), 1,
      anon_sym_option,
    ACTIONS(220), 1,
      anon_sym_RBRACE,
    STATE(221), 1,
      sym_type,
    STATE(224), 1,
      sym_message_or_enum_type,
    STATE(250), 1,
      aux_sym_message_or_enum_type_repeat1,
    STATE(30), 4,
      sym_empty_statement,
      sym_option,
      sym_oneof_field,
      aux_sym_oneof_body_repeat1,
    ACTIONS(49), 15,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
  [1406] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(31), 1,
      anon_sym_DOT,
    ACTIONS(55), 1,
      sym_identifier,
    ACTIONS(216), 1,
      anon_sym_SEMI,
    ACTIONS(218), 1,
      anon_sym_option,
    ACTIONS(222), 1,
      anon_sym_RBRACE,
    STATE(221), 1,
      sym_type,
    STATE(224), 1,
      sym_message_or_enum_type,
    STATE(250), 1,
      aux_sym_message_or_enum_type_repeat1,
    STATE(31), 4,
      sym_empty_statement,
      sym_option,
      sym_oneof_field,
      aux_sym_oneof_body_repeat1,
    ACTIONS(49), 15,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
  [1457] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(224), 1,
      anon_sym_LBRACE,
    ACTIONS(226), 1,
      anon_sym_LBRACK,
    ACTIONS(230), 1,
      anon_sym_COLON,
    ACTIONS(232), 1,
      sym_identifier,
    ACTIONS(238), 1,
      sym_hex_lit,
    ACTIONS(240), 1,
      sym_float_lit,
    ACTIONS(242), 1,
      anon_sym_SQUOTE,
    ACTIONS(244), 1,
      anon_sym_DQUOTE,
    STATE(82), 1,
      aux_sym_string_repeat3,
    ACTIONS(228), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(234), 2,
      sym_true,
      sym_false,
    ACTIONS(236), 2,
      sym_decimal_lit,
      sym_octal_lit,
    STATE(121), 6,
      sym__constant,
      sym_block_lit,
      sym_full_ident,
      sym_bool,
      sym_int_lit,
      sym_string,
  [1508] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(250), 1,
      anon_sym_LBRACK,
    ACTIONS(246), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(248), 17,
      anon_sym_option,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      sym_identifier,
  [1539] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(224), 1,
      anon_sym_LBRACE,
    ACTIONS(232), 1,
      sym_identifier,
    ACTIONS(238), 1,
      sym_hex_lit,
    ACTIONS(242), 1,
      anon_sym_SQUOTE,
    ACTIONS(244), 1,
      anon_sym_DQUOTE,
    ACTIONS(252), 1,
      anon_sym_LBRACK,
    ACTIONS(254), 1,
      anon_sym_COLON,
    ACTIONS(256), 1,
      sym_float_lit,
    STATE(82), 1,
      aux_sym_string_repeat3,
    ACTIONS(228), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(234), 2,
      sym_true,
      sym_false,
    ACTIONS(236), 2,
      sym_decimal_lit,
      sym_octal_lit,
    STATE(151), 6,
      sym__constant,
      sym_block_lit,
      sym_full_ident,
      sym_bool,
      sym_int_lit,
      sym_string,
  [1590] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(258), 4,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
    ACTIONS(260), 17,
      anon_sym_option,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      sym_identifier,
  [1619] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(31), 1,
      anon_sym_DOT,
    ACTIONS(55), 1,
      sym_identifier,
    ACTIONS(262), 1,
      anon_sym_repeated,
    STATE(215), 1,
      sym_type,
    STATE(224), 1,
      sym_message_or_enum_type,
    STATE(250), 1,
      aux_sym_message_or_enum_type_repeat1,
    ACTIONS(49), 15,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
  [1658] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(264), 4,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
    ACTIONS(266), 17,
      anon_sym_option,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      sym_identifier,
  [1687] = 13,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(224), 1,
      anon_sym_LBRACE,
    ACTIONS(232), 1,
      sym_identifier,
    ACTIONS(242), 1,
      anon_sym_SQUOTE,
    ACTIONS(244), 1,
      anon_sym_DQUOTE,
    ACTIONS(268), 1,
      anon_sym_RBRACK,
    ACTIONS(274), 1,
      sym_hex_lit,
    ACTIONS(276), 1,
      sym_float_lit,
    STATE(82), 1,
      aux_sym_string_repeat3,
    ACTIONS(234), 2,
      sym_true,
      sym_false,
    ACTIONS(270), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(272), 2,
      sym_decimal_lit,
      sym_octal_lit,
    STATE(179), 6,
      sym__constant,
      sym_block_lit,
      sym_full_ident,
      sym_bool,
      sym_int_lit,
      sym_string,
  [1735] = 13,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(224), 1,
      anon_sym_LBRACE,
    ACTIONS(232), 1,
      sym_identifier,
    ACTIONS(238), 1,
      sym_hex_lit,
    ACTIONS(242), 1,
      anon_sym_SQUOTE,
    ACTIONS(244), 1,
      anon_sym_DQUOTE,
    ACTIONS(278), 1,
      anon_sym_LBRACK,
    ACTIONS(280), 1,
      sym_float_lit,
    STATE(82), 1,
      aux_sym_string_repeat3,
    ACTIONS(228), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(234), 2,
      sym_true,
      sym_false,
    ACTIONS(236), 2,
      sym_decimal_lit,
      sym_octal_lit,
    STATE(129), 6,
      sym__constant,
      sym_block_lit,
      sym_full_ident,
      sym_bool,
      sym_int_lit,
      sym_string,
  [1783] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(31), 1,
      anon_sym_DOT,
    ACTIONS(55), 1,
      sym_identifier,
    STATE(224), 1,
      sym_message_or_enum_type,
    STATE(250), 1,
      aux_sym_message_or_enum_type_repeat1,
    STATE(253), 1,
      sym_type,
    ACTIONS(49), 15,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
  [1819] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(282), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(284), 17,
      anon_sym_option,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      sym_identifier,
  [1847] = 13,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(224), 1,
      anon_sym_LBRACE,
    ACTIONS(232), 1,
      sym_identifier,
    ACTIONS(242), 1,
      anon_sym_SQUOTE,
    ACTIONS(244), 1,
      anon_sym_DQUOTE,
    ACTIONS(274), 1,
      sym_hex_lit,
    ACTIONS(286), 1,
      anon_sym_RBRACK,
    ACTIONS(288), 1,
      sym_float_lit,
    STATE(82), 1,
      aux_sym_string_repeat3,
    ACTIONS(234), 2,
      sym_true,
      sym_false,
    ACTIONS(270), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(272), 2,
      sym_decimal_lit,
      sym_octal_lit,
    STATE(178), 6,
      sym__constant,
      sym_block_lit,
      sym_full_ident,
      sym_bool,
      sym_int_lit,
      sym_string,
  [1895] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(31), 1,
      anon_sym_DOT,
    ACTIONS(55), 1,
      sym_identifier,
    STATE(215), 1,
      sym_type,
    STATE(224), 1,
      sym_message_or_enum_type,
    STATE(250), 1,
      aux_sym_message_or_enum_type_repeat1,
    ACTIONS(49), 15,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
  [1931] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(31), 1,
      anon_sym_DOT,
    ACTIONS(55), 1,
      sym_identifier,
    STATE(224), 1,
      sym_message_or_enum_type,
    STATE(236), 1,
      sym_type,
    STATE(250), 1,
      aux_sym_message_or_enum_type_repeat1,
    ACTIONS(49), 15,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
  [1967] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(171), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(173), 17,
      anon_sym_option,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      sym_identifier,
  [1995] = 13,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(224), 1,
      anon_sym_LBRACE,
    ACTIONS(232), 1,
      sym_identifier,
    ACTIONS(242), 1,
      anon_sym_SQUOTE,
    ACTIONS(244), 1,
      anon_sym_DQUOTE,
    ACTIONS(274), 1,
      sym_hex_lit,
    ACTIONS(290), 1,
      anon_sym_RBRACK,
    ACTIONS(292), 1,
      sym_float_lit,
    STATE(82), 1,
      aux_sym_string_repeat3,
    ACTIONS(234), 2,
      sym_true,
      sym_false,
    ACTIONS(270), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(272), 2,
      sym_decimal_lit,
      sym_octal_lit,
    STATE(185), 6,
      sym__constant,
      sym_block_lit,
      sym_full_ident,
      sym_bool,
      sym_int_lit,
      sym_string,
  [2043] = 13,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(224), 1,
      anon_sym_LBRACE,
    ACTIONS(232), 1,
      sym_identifier,
    ACTIONS(238), 1,
      sym_hex_lit,
    ACTIONS(242), 1,
      anon_sym_SQUOTE,
    ACTIONS(244), 1,
      anon_sym_DQUOTE,
    ACTIONS(294), 1,
      anon_sym_LBRACK,
    ACTIONS(296), 1,
      sym_float_lit,
    STATE(82), 1,
      aux_sym_string_repeat3,
    ACTIONS(228), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(234), 2,
      sym_true,
      sym_false,
    ACTIONS(236), 2,
      sym_decimal_lit,
      sym_octal_lit,
    STATE(135), 6,
      sym__constant,
      sym_block_lit,
      sym_full_ident,
      sym_bool,
      sym_int_lit,
      sym_string,
  [2091] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(195), 3,
      anon_sym_SEMI,
      anon_sym_DOT,
      anon_sym_RBRACE,
    ACTIONS(197), 17,
      anon_sym_option,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
      anon_sym_double,
      anon_sym_float,
      anon_sym_bytes,
      sym_identifier,
  [2119] = 13,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(224), 1,
      anon_sym_LBRACE,
    ACTIONS(232), 1,
      sym_identifier,
    ACTIONS(242), 1,
      anon_sym_SQUOTE,
    ACTIONS(244), 1,
      anon_sym_DQUOTE,
    ACTIONS(274), 1,
      sym_hex_lit,
    ACTIONS(298), 1,
      anon_sym_RBRACK,
    ACTIONS(300), 1,
      sym_float_lit,
    STATE(82), 1,
      aux_sym_string_repeat3,
    ACTIONS(234), 2,
      sym_true,
      sym_false,
    ACTIONS(270), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(272), 2,
      sym_decimal_lit,
      sym_octal_lit,
    STATE(206), 6,
      sym__constant,
      sym_block_lit,
      sym_full_ident,
      sym_bool,
      sym_int_lit,
      sym_string,
  [2167] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(224), 1,
      anon_sym_LBRACE,
    ACTIONS(232), 1,
      sym_identifier,
    ACTIONS(242), 1,
      anon_sym_SQUOTE,
    ACTIONS(244), 1,
      anon_sym_DQUOTE,
    ACTIONS(274), 1,
      sym_hex_lit,
    ACTIONS(302), 1,
      sym_float_lit,
    STATE(82), 1,
      aux_sym_string_repeat3,
    ACTIONS(234), 2,
      sym_true,
      sym_false,
    ACTIONS(270), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(272), 2,
      sym_decimal_lit,
      sym_octal_lit,
    STATE(211), 6,
      sym__constant,
      sym_block_lit,
      sym_full_ident,
      sym_bool,
      sym_int_lit,
      sym_string,
  [2212] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(224), 1,
      anon_sym_LBRACE,
    ACTIONS(232), 1,
      sym_identifier,
    ACTIONS(242), 1,
      anon_sym_SQUOTE,
    ACTIONS(244), 1,
      anon_sym_DQUOTE,
    ACTIONS(274), 1,
      sym_hex_lit,
    ACTIONS(304), 1,
      sym_float_lit,
    STATE(82), 1,
      aux_sym_string_repeat3,
    ACTIONS(234), 2,
      sym_true,
      sym_false,
    ACTIONS(270), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(272), 2,
      sym_decimal_lit,
      sym_octal_lit,
    STATE(298), 6,
      sym__constant,
      sym_block_lit,
      sym_full_ident,
      sym_bool,
      sym_int_lit,
      sym_string,
  [2257] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(224), 1,
      anon_sym_LBRACE,
    ACTIONS(232), 1,
      sym_identifier,
    ACTIONS(242), 1,
      anon_sym_SQUOTE,
    ACTIONS(244), 1,
      anon_sym_DQUOTE,
    ACTIONS(274), 1,
      sym_hex_lit,
    ACTIONS(306), 1,
      sym_float_lit,
    STATE(82), 1,
      aux_sym_string_repeat3,
    ACTIONS(234), 2,
      sym_true,
      sym_false,
    ACTIONS(270), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(272), 2,
      sym_decimal_lit,
      sym_octal_lit,
    STATE(226), 6,
      sym__constant,
      sym_block_lit,
      sym_full_ident,
      sym_bool,
      sym_int_lit,
      sym_string,
  [2302] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(224), 1,
      anon_sym_LBRACE,
    ACTIONS(232), 1,
      sym_identifier,
    ACTIONS(242), 1,
      anon_sym_SQUOTE,
    ACTIONS(244), 1,
      anon_sym_DQUOTE,
    ACTIONS(274), 1,
      sym_hex_lit,
    ACTIONS(308), 1,
      sym_float_lit,
    STATE(82), 1,
      aux_sym_string_repeat3,
    ACTIONS(234), 2,
      sym_true,
      sym_false,
    ACTIONS(270), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(272), 2,
      sym_decimal_lit,
      sym_octal_lit,
    STATE(284), 6,
      sym__constant,
      sym_block_lit,
      sym_full_ident,
      sym_bool,
      sym_int_lit,
      sym_string,
  [2347] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(224), 1,
      anon_sym_LBRACE,
    ACTIONS(232), 1,
      sym_identifier,
    ACTIONS(242), 1,
      anon_sym_SQUOTE,
    ACTIONS(244), 1,
      anon_sym_DQUOTE,
    ACTIONS(274), 1,
      sym_hex_lit,
    ACTIONS(310), 1,
      sym_float_lit,
    STATE(82), 1,
      aux_sym_string_repeat3,
    ACTIONS(234), 2,
      sym_true,
      sym_false,
    ACTIONS(270), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(272), 2,
      sym_decimal_lit,
      sym_octal_lit,
    STATE(293), 6,
      sym__constant,
      sym_block_lit,
      sym_full_ident,
      sym_bool,
      sym_int_lit,
      sym_string,
  [2392] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(224), 1,
      anon_sym_LBRACE,
    ACTIONS(232), 1,
      sym_identifier,
    ACTIONS(242), 1,
      anon_sym_SQUOTE,
    ACTIONS(244), 1,
      anon_sym_DQUOTE,
    ACTIONS(274), 1,
      sym_hex_lit,
    ACTIONS(312), 1,
      sym_float_lit,
    STATE(82), 1,
      aux_sym_string_repeat3,
    ACTIONS(234), 2,
      sym_true,
      sym_false,
    ACTIONS(270), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(272), 2,
      sym_decimal_lit,
      sym_octal_lit,
    STATE(297), 6,
      sym__constant,
      sym_block_lit,
      sym_full_ident,
      sym_bool,
      sym_int_lit,
      sym_string,
  [2437] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      anon_sym_SEMI,
    ACTIONS(13), 1,
      anon_sym_import,
    ACTIONS(15), 1,
      anon_sym_package,
    ACTIONS(17), 1,
      anon_sym_option,
    ACTIONS(19), 1,
      anon_sym_enum,
    ACTIONS(21), 1,
      anon_sym_message,
    ACTIONS(23), 1,
      anon_sym_extend,
    ACTIONS(25), 1,
      anon_sym_service,
    ACTIONS(314), 1,
      ts_builtin_sym_end,
    STATE(60), 9,
      sym_empty_statement,
      sym_import,
      sym_package,
      sym_option,
      sym_enum,
      sym_message,
      sym_extend,
      sym_service,
      aux_sym_source_file_repeat1,
  [2479] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      anon_sym_SEMI,
    ACTIONS(13), 1,
      anon_sym_import,
    ACTIONS(15), 1,
      anon_sym_package,
    ACTIONS(17), 1,
      anon_sym_option,
    ACTIONS(19), 1,
      anon_sym_enum,
    ACTIONS(21), 1,
      anon_sym_message,
    ACTIONS(23), 1,
      anon_sym_extend,
    ACTIONS(25), 1,
      anon_sym_service,
    ACTIONS(316), 1,
      ts_builtin_sym_end,
    STATE(60), 9,
      sym_empty_statement,
      sym_import,
      sym_package,
      sym_option,
      sym_enum,
      sym_message,
      sym_extend,
      sym_service,
      aux_sym_source_file_repeat1,
  [2521] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      anon_sym_SEMI,
    ACTIONS(13), 1,
      anon_sym_import,
    ACTIONS(15), 1,
      anon_sym_package,
    ACTIONS(17), 1,
      anon_sym_option,
    ACTIONS(19), 1,
      anon_sym_enum,
    ACTIONS(21), 1,
      anon_sym_message,
    ACTIONS(23), 1,
      anon_sym_extend,
    ACTIONS(25), 1,
      anon_sym_service,
    ACTIONS(316), 1,
      ts_builtin_sym_end,
    STATE(57), 9,
      sym_empty_statement,
      sym_import,
      sym_package,
      sym_option,
      sym_enum,
      sym_message,
      sym_extend,
      sym_service,
      aux_sym_source_file_repeat1,
  [2563] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(318), 1,
      ts_builtin_sym_end,
    ACTIONS(320), 1,
      anon_sym_SEMI,
    ACTIONS(323), 1,
      anon_sym_import,
    ACTIONS(326), 1,
      anon_sym_package,
    ACTIONS(329), 1,
      anon_sym_option,
    ACTIONS(332), 1,
      anon_sym_enum,
    ACTIONS(335), 1,
      anon_sym_message,
    ACTIONS(338), 1,
      anon_sym_extend,
    ACTIONS(341), 1,
      anon_sym_service,
    STATE(60), 9,
      sym_empty_statement,
      sym_import,
      sym_package,
      sym_option,
      sym_enum,
      sym_message,
      sym_extend,
      sym_service,
      aux_sym_source_file_repeat1,
  [2605] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(346), 6,
      sym_identifier,
      sym_true,
      sym_false,
      sym_decimal_lit,
      sym_octal_lit,
      sym_float_lit,
    ACTIONS(344), 9,
      anon_sym_EQ,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_COLON,
      sym_hex_lit,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
  [2628] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(242), 1,
      anon_sym_SQUOTE,
    ACTIONS(244), 1,
      anon_sym_DQUOTE,
    ACTIONS(272), 1,
      sym_octal_lit,
    ACTIONS(348), 1,
      sym_identifier,
    STATE(82), 1,
      aux_sym_string_repeat3,
    STATE(196), 1,
      sym_range,
    STATE(199), 1,
      sym_int_lit,
    ACTIONS(274), 2,
      sym_decimal_lit,
      sym_hex_lit,
    STATE(197), 2,
      sym__identifier_or_string,
      sym_string,
    STATE(296), 2,
      sym_ranges,
      sym_field_names,
  [2665] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(242), 1,
      anon_sym_SQUOTE,
    ACTIONS(244), 1,
      anon_sym_DQUOTE,
    ACTIONS(272), 1,
      sym_octal_lit,
    ACTIONS(348), 1,
      sym_identifier,
    STATE(82), 1,
      aux_sym_string_repeat3,
    STATE(196), 1,
      sym_range,
    STATE(199), 1,
      sym_int_lit,
    ACTIONS(274), 2,
      sym_decimal_lit,
      sym_hex_lit,
    STATE(197), 2,
      sym__identifier_or_string,
      sym_string,
    STATE(310), 2,
      sym_ranges,
      sym_field_names,
  [2702] = 3,
    ACTIONS(3), 1,
      sym_comment,
    STATE(289), 1,
      sym_key_type,
    ACTIONS(350), 12,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_sint32,
      anon_sym_sint64,
      anon_sym_fixed32,
      anon_sym_fixed64,
      anon_sym_sfixed32,
      anon_sym_sfixed64,
      anon_sym_bool,
      anon_sym_string,
  [2723] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(352), 1,
      anon_sym_SEMI,
    ACTIONS(355), 1,
      anon_sym_option,
    ACTIONS(358), 1,
      anon_sym_RBRACE,
    ACTIONS(360), 1,
      anon_sym_reserved,
    ACTIONS(363), 1,
      sym_identifier,
    STATE(303), 1,
      sym_enum_variant_name,
    STATE(65), 5,
      sym_empty_statement,
      sym_option,
      sym_enum_field,
      sym_reserved,
      aux_sym_enum_body_repeat1,
  [2752] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(368), 1,
      anon_sym_DOT,
    STATE(66), 1,
      aux_sym_option_name_repeat1,
    ACTIONS(366), 9,
      anon_sym_SEMI,
      anon_sym_EQ,
      anon_sym_RPAREN,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [2773] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(171), 11,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_import,
      anon_sym_package,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_RBRACE,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_service,
      anon_sym_rpc,
  [2790] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(371), 1,
      anon_sym_SEMI,
    ACTIONS(373), 1,
      anon_sym_option,
    ACTIONS(375), 1,
      anon_sym_RBRACE,
    ACTIONS(377), 1,
      anon_sym_reserved,
    ACTIONS(379), 1,
      sym_identifier,
    STATE(303), 1,
      sym_enum_variant_name,
    STATE(65), 5,
      sym_empty_statement,
      sym_option,
      sym_enum_field,
      sym_reserved,
      aux_sym_enum_body_repeat1,
  [2819] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(371), 1,
      anon_sym_SEMI,
    ACTIONS(373), 1,
      anon_sym_option,
    ACTIONS(377), 1,
      anon_sym_reserved,
    ACTIONS(379), 1,
      sym_identifier,
    ACTIONS(381), 1,
      anon_sym_RBRACE,
    STATE(303), 1,
      sym_enum_variant_name,
    STATE(68), 5,
      sym_empty_statement,
      sym_option,
      sym_enum_field,
      sym_reserved,
      aux_sym_enum_body_repeat1,
  [2848] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(195), 11,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_import,
      anon_sym_package,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_RBRACE,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_service,
      anon_sym_rpc,
  [2865] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(371), 1,
      anon_sym_SEMI,
    ACTIONS(373), 1,
      anon_sym_option,
    ACTIONS(377), 1,
      anon_sym_reserved,
    ACTIONS(379), 1,
      sym_identifier,
    ACTIONS(383), 1,
      anon_sym_RBRACE,
    STATE(303), 1,
      sym_enum_variant_name,
    STATE(65), 5,
      sym_empty_statement,
      sym_option,
      sym_enum_field,
      sym_reserved,
      aux_sym_enum_body_repeat1,
  [2894] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(371), 1,
      anon_sym_SEMI,
    ACTIONS(373), 1,
      anon_sym_option,
    ACTIONS(377), 1,
      anon_sym_reserved,
    ACTIONS(379), 1,
      sym_identifier,
    ACTIONS(385), 1,
      anon_sym_RBRACE,
    STATE(303), 1,
      sym_enum_variant_name,
    STATE(71), 5,
      sym_empty_statement,
      sym_option,
      sym_enum_field,
      sym_reserved,
      aux_sym_enum_body_repeat1,
  [2923] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(389), 1,
      anon_sym_DOT,
    STATE(75), 1,
      aux_sym_option_name_repeat1,
    ACTIONS(387), 8,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [2943] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(366), 10,
      anon_sym_SEMI,
      anon_sym_EQ,
      anon_sym_DOT,
      anon_sym_RPAREN,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [2959] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(389), 1,
      anon_sym_DOT,
    STATE(66), 1,
      aux_sym_option_name_repeat1,
    ACTIONS(391), 8,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [2979] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(393), 9,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_import,
      anon_sym_package,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_service,
  [2994] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 9,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_import,
      anon_sym_package,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_service,
  [3009] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(395), 9,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_import,
      anon_sym_package,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_service,
  [3024] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(397), 9,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_import,
      anon_sym_package,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_service,
  [3039] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(175), 9,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_import,
      anon_sym_package,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_service,
  [3054] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(399), 9,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_import,
      anon_sym_package,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_service,
  [3069] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(242), 1,
      anon_sym_SQUOTE,
    ACTIONS(244), 1,
      anon_sym_DQUOTE,
    STATE(88), 1,
      aux_sym_string_repeat3,
    ACTIONS(401), 6,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [3090] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(159), 9,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_import,
      anon_sym_package,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_service,
  [3105] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(179), 9,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_import,
      anon_sym_package,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_service,
  [3120] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(183), 9,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_import,
      anon_sym_package,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_service,
  [3135] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(403), 9,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_import,
      anon_sym_package,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_service,
  [3150] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(163), 9,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_import,
      anon_sym_package,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_service,
  [3165] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(407), 1,
      anon_sym_SQUOTE,
    ACTIONS(410), 1,
      anon_sym_DQUOTE,
    STATE(88), 1,
      aux_sym_string_repeat3,
    ACTIONS(405), 6,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [3186] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(167), 9,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_import,
      anon_sym_package,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_service,
  [3201] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(187), 9,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_import,
      anon_sym_package,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_service,
  [3216] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(413), 9,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_import,
      anon_sym_package,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_service,
  [3231] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(415), 9,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_import,
      anon_sym_package,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_service,
  [3246] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(417), 9,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_import,
      anon_sym_package,
      anon_sym_option,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_extend,
      anon_sym_service,
  [3261] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(419), 1,
      anon_sym_SEMI,
    ACTIONS(422), 1,
      anon_sym_option,
    ACTIONS(425), 1,
      anon_sym_RBRACE,
    ACTIONS(427), 1,
      anon_sym_rpc,
    STATE(94), 4,
      sym_empty_statement,
      sym_option,
      sym_rpc,
      aux_sym_service_body_repeat1,
  [3283] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      anon_sym_SEMI,
    ACTIONS(17), 1,
      anon_sym_option,
    ACTIONS(430), 1,
      anon_sym_RBRACE,
    ACTIONS(432), 1,
      anon_sym_rpc,
    STATE(94), 4,
      sym_empty_statement,
      sym_option,
      sym_rpc,
      aux_sym_service_body_repeat1,
  [3305] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(405), 8,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_COMMA,
      sym_identifier,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
  [3319] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(434), 8,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_COMMA,
      sym_identifier,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
  [3333] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      anon_sym_SEMI,
    ACTIONS(17), 1,
      anon_sym_option,
    ACTIONS(432), 1,
      anon_sym_rpc,
    ACTIONS(436), 1,
      anon_sym_RBRACE,
    STATE(95), 4,
      sym_empty_statement,
      sym_option,
      sym_rpc,
      aux_sym_service_body_repeat1,
  [3355] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(438), 1,
      anon_sym_RBRACE,
    ACTIONS(440), 1,
      anon_sym_LBRACK,
    ACTIONS(442), 1,
      sym_identifier,
    STATE(35), 1,
      sym_field_name,
    STATE(111), 1,
      aux_sym_block_lit_repeat1,
    STATE(138), 1,
      sym_block_field,
  [3377] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(444), 6,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [3389] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(242), 1,
      anon_sym_SQUOTE,
    ACTIONS(244), 1,
      anon_sym_DQUOTE,
    ACTIONS(446), 1,
      sym_identifier,
    STATE(82), 1,
      aux_sym_string_repeat3,
    STATE(231), 2,
      sym__identifier_or_string,
      sym_string,
  [3409] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(448), 6,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [3421] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(440), 1,
      anon_sym_LBRACK,
    ACTIONS(442), 1,
      sym_identifier,
    ACTIONS(450), 1,
      anon_sym_RBRACE,
    STATE(35), 1,
      sym_field_name,
    STATE(99), 1,
      aux_sym_block_lit_repeat1,
    STATE(138), 1,
      sym_block_field,
  [3443] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      anon_sym_SEMI,
    ACTIONS(17), 1,
      anon_sym_option,
    ACTIONS(452), 1,
      anon_sym_RBRACE,
    STATE(106), 3,
      sym_empty_statement,
      sym_option,
      aux_sym_rpc_body_repeat1,
  [3461] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(454), 6,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [3473] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      anon_sym_SEMI,
    ACTIONS(17), 1,
      anon_sym_option,
    ACTIONS(456), 1,
      anon_sym_RBRACE,
    STATE(107), 3,
      sym_empty_statement,
      sym_option,
      aux_sym_rpc_body_repeat1,
  [3491] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(458), 1,
      anon_sym_SEMI,
    ACTIONS(461), 1,
      anon_sym_option,
    ACTIONS(464), 1,
      anon_sym_RBRACE,
    STATE(107), 3,
      sym_empty_statement,
      sym_option,
      aux_sym_rpc_body_repeat1,
  [3509] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(272), 1,
      sym_octal_lit,
    STATE(196), 1,
      sym_range,
    STATE(199), 1,
      sym_int_lit,
    STATE(281), 1,
      sym_ranges,
    ACTIONS(274), 2,
      sym_decimal_lit,
      sym_hex_lit,
  [3529] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(466), 6,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [3541] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(242), 1,
      anon_sym_SQUOTE,
    ACTIONS(244), 1,
      anon_sym_DQUOTE,
    STATE(82), 1,
      aux_sym_string_repeat3,
    STATE(302), 1,
      sym_string,
    ACTIONS(468), 2,
      anon_sym_weak,
      anon_sym_public,
  [3561] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(470), 1,
      anon_sym_RBRACE,
    ACTIONS(472), 1,
      anon_sym_LBRACK,
    ACTIONS(475), 1,
      sym_identifier,
    STATE(35), 1,
      sym_field_name,
    STATE(111), 1,
      aux_sym_block_lit_repeat1,
    STATE(138), 1,
      sym_block_field,
  [3583] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(478), 1,
      anon_sym_LPAREN,
    ACTIONS(480), 1,
      sym_identifier,
    STATE(180), 1,
      sym_field_option,
    STATE(278), 1,
      sym_field_options,
    STATE(288), 1,
      sym_option_name,
  [3602] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(482), 5,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [3613] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(478), 1,
      anon_sym_LPAREN,
    ACTIONS(480), 1,
      sym_identifier,
    STATE(180), 1,
      sym_field_option,
    STATE(288), 1,
      sym_option_name,
    STATE(301), 1,
      sym_field_options,
  [3632] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(272), 1,
      sym_octal_lit,
    STATE(38), 1,
      sym_int_lit,
    STATE(220), 1,
      sym_field_number,
    ACTIONS(274), 2,
      sym_decimal_lit,
      sym_hex_lit,
  [3649] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(272), 1,
      sym_octal_lit,
    STATE(38), 1,
      sym_int_lit,
    STATE(228), 1,
      sym_field_number,
    ACTIONS(274), 2,
      sym_decimal_lit,
      sym_hex_lit,
  [3666] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(31), 1,
      anon_sym_DOT,
    ACTIONS(55), 1,
      sym_identifier,
    ACTIONS(484), 1,
      anon_sym_stream,
    STATE(250), 1,
      aux_sym_message_or_enum_type_repeat1,
    STATE(305), 1,
      sym_message_or_enum_type,
  [3685] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(486), 5,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [3696] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(31), 1,
      anon_sym_DOT,
    ACTIONS(55), 1,
      sym_identifier,
    ACTIONS(488), 1,
      anon_sym_stream,
    STATE(250), 1,
      aux_sym_message_or_enum_type_repeat1,
    STATE(276), 1,
      sym_message_or_enum_type,
  [3715] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(191), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
    ACTIONS(193), 3,
      anon_sym_option,
      anon_sym_reserved,
      sym_identifier,
  [3728] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(490), 5,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [3739] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(492), 5,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [3750] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(478), 1,
      anon_sym_LPAREN,
    ACTIONS(480), 1,
      sym_identifier,
    STATE(180), 1,
      sym_field_option,
    STATE(259), 1,
      sym_field_options,
    STATE(288), 1,
      sym_option_name,
  [3769] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(494), 5,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [3780] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(496), 5,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [3791] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(272), 1,
      sym_octal_lit,
    STATE(38), 1,
      sym_int_lit,
    STATE(248), 1,
      sym_field_number,
    ACTIONS(274), 2,
      sym_decimal_lit,
      sym_hex_lit,
  [3808] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(272), 1,
      sym_octal_lit,
    STATE(199), 1,
      sym_int_lit,
    STATE(225), 1,
      sym_range,
    ACTIONS(274), 2,
      sym_decimal_lit,
      sym_hex_lit,
  [3825] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(171), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
    ACTIONS(173), 3,
      anon_sym_option,
      anon_sym_reserved,
      sym_identifier,
  [3838] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(498), 5,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [3849] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(500), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
    ACTIONS(502), 3,
      anon_sym_option,
      anon_sym_reserved,
      sym_identifier,
  [3862] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(478), 1,
      anon_sym_LPAREN,
    ACTIONS(480), 1,
      sym_identifier,
    STATE(180), 1,
      sym_field_option,
    STATE(288), 1,
      sym_option_name,
    STATE(300), 1,
      sym_field_options,
  [3881] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(504), 5,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [3892] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(506), 5,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [3903] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(478), 1,
      anon_sym_LPAREN,
    ACTIONS(480), 1,
      sym_identifier,
    STATE(180), 1,
      sym_field_option,
    STATE(280), 1,
      sym_field_options,
    STATE(288), 1,
      sym_option_name,
  [3922] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(508), 5,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [3933] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(195), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
    ACTIONS(197), 3,
      anon_sym_option,
      anon_sym_reserved,
      sym_identifier,
  [3946] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(510), 5,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [3957] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(512), 2,
      anon_sym_SEMI,
      anon_sym_COMMA,
    ACTIONS(514), 3,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      sym_identifier,
  [3970] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(516), 5,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [3981] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(274), 1,
      sym_hex_lit,
    ACTIONS(518), 1,
      sym_float_lit,
    STATE(100), 1,
      sym_int_lit,
    ACTIONS(272), 2,
      sym_decimal_lit,
      sym_octal_lit,
  [3998] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(272), 1,
      sym_octal_lit,
    STATE(38), 1,
      sym_int_lit,
    STATE(217), 1,
      sym_field_number,
    ACTIONS(274), 2,
      sym_decimal_lit,
      sym_hex_lit,
  [4015] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(272), 1,
      sym_octal_lit,
    STATE(38), 1,
      sym_int_lit,
    STATE(234), 1,
      sym_field_number,
    ACTIONS(274), 2,
      sym_decimal_lit,
      sym_hex_lit,
  [4032] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(478), 1,
      anon_sym_LPAREN,
    ACTIONS(480), 1,
      sym_identifier,
    STATE(180), 1,
      sym_field_option,
    STATE(265), 1,
      sym_field_options,
    STATE(288), 1,
      sym_option_name,
  [4051] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(522), 1,
      sym_octal_lit,
    STATE(34), 1,
      sym_field_number,
    STATE(38), 1,
      sym_int_lit,
    ACTIONS(520), 2,
      sym_decimal_lit,
      sym_hex_lit,
  [4068] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(524), 5,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [4079] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(526), 5,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [4090] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(238), 1,
      sym_hex_lit,
    ACTIONS(518), 1,
      sym_float_lit,
    STATE(100), 1,
      sym_int_lit,
    ACTIONS(236), 2,
      sym_decimal_lit,
      sym_octal_lit,
  [4107] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(528), 5,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [4118] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(530), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
    ACTIONS(532), 3,
      anon_sym_option,
      anon_sym_reserved,
      sym_identifier,
  [4131] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(258), 5,
      anon_sym_SEMI,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_COMMA,
      anon_sym_to,
  [4142] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(534), 5,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [4153] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(272), 1,
      sym_octal_lit,
    ACTIONS(536), 1,
      anon_sym_max,
    STATE(245), 1,
      sym_int_lit,
    ACTIONS(274), 2,
      sym_decimal_lit,
      sym_hex_lit,
  [4170] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(31), 1,
      anon_sym_DOT,
    ACTIONS(55), 1,
      sym_identifier,
    ACTIONS(538), 1,
      anon_sym_stream,
    STATE(250), 1,
      aux_sym_message_or_enum_type_repeat1,
    STATE(291), 1,
      sym_message_or_enum_type,
  [4189] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(258), 5,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_COMMA,
      sym_identifier,
  [4200] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(242), 1,
      anon_sym_SQUOTE,
    ACTIONS(244), 1,
      anon_sym_DQUOTE,
    STATE(82), 1,
      aux_sym_string_repeat3,
    STATE(311), 1,
      sym_string,
  [4216] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(540), 1,
      anon_sym_DOT,
    ACTIONS(542), 3,
      anon_sym_RPAREN,
      anon_sym_GT,
      sym_identifier,
  [4228] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(31), 1,
      anon_sym_DOT,
    ACTIONS(544), 1,
      sym_identifier,
    STATE(250), 1,
      aux_sym_message_or_enum_type_repeat1,
    STATE(258), 1,
      sym_message_or_enum_type,
  [4244] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(540), 1,
      anon_sym_DOT,
    ACTIONS(546), 3,
      anon_sym_RPAREN,
      anon_sym_GT,
      sym_identifier,
  [4256] = 4,
    ACTIONS(548), 1,
      anon_sym_SQUOTE,
    ACTIONS(552), 1,
      sym_comment,
    STATE(174), 1,
      aux_sym_string_repeat1,
    ACTIONS(550), 2,
      aux_sym_string_token1,
      sym_escape_sequence,
  [4270] = 4,
    ACTIONS(548), 1,
      anon_sym_DQUOTE,
    ACTIONS(552), 1,
      sym_comment,
    STATE(175), 1,
      aux_sym_string_repeat2,
    ACTIONS(554), 2,
      aux_sym_string_token2,
      sym_escape_sequence,
  [4284] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(242), 1,
      anon_sym_SQUOTE,
    ACTIONS(244), 1,
      anon_sym_DQUOTE,
    STATE(82), 1,
      aux_sym_string_repeat3,
    STATE(268), 1,
      sym_string,
  [4300] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(478), 1,
      anon_sym_LPAREN,
    ACTIONS(480), 1,
      sym_identifier,
    STATE(212), 1,
      sym_field_option,
    STATE(288), 1,
      sym_option_name,
  [4316] = 4,
    ACTIONS(552), 1,
      sym_comment,
    ACTIONS(556), 1,
      anon_sym_SQUOTE,
    STATE(159), 1,
      aux_sym_string_repeat1,
    ACTIONS(558), 2,
      aux_sym_string_token1,
      sym_escape_sequence,
  [4330] = 4,
    ACTIONS(552), 1,
      sym_comment,
    ACTIONS(556), 1,
      anon_sym_DQUOTE,
    STATE(160), 1,
      aux_sym_string_repeat2,
    ACTIONS(560), 2,
      aux_sym_string_token2,
      sym_escape_sequence,
  [4344] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(540), 1,
      anon_sym_DOT,
    ACTIONS(562), 3,
      anon_sym_RPAREN,
      anon_sym_GT,
      sym_identifier,
  [4356] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(31), 1,
      anon_sym_DOT,
    ACTIONS(544), 1,
      sym_identifier,
    STATE(250), 1,
      aux_sym_message_or_enum_type_repeat1,
    STATE(305), 1,
      sym_message_or_enum_type,
  [4372] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(31), 1,
      anon_sym_DOT,
    ACTIONS(544), 1,
      sym_identifier,
    STATE(250), 1,
      aux_sym_message_or_enum_type_repeat1,
    STATE(254), 1,
      sym_message_or_enum_type,
  [4388] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(564), 4,
      anon_sym_SEMI,
      anon_sym_option,
      anon_sym_RBRACE,
      anon_sym_rpc,
  [4398] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(566), 4,
      anon_sym_SEMI,
      anon_sym_option,
      anon_sym_RBRACE,
      anon_sym_rpc,
  [4408] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(568), 4,
      anon_sym_SEMI,
      anon_sym_option,
      anon_sym_RBRACE,
      anon_sym_rpc,
  [4418] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(570), 4,
      anon_sym_SEMI,
      anon_sym_option,
      anon_sym_RBRACE,
      anon_sym_rpc,
  [4428] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(572), 4,
      anon_sym_SEMI,
      anon_sym_option,
      anon_sym_RBRACE,
      anon_sym_rpc,
  [4438] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(574), 4,
      anon_sym_SEMI,
      anon_sym_option,
      anon_sym_RBRACE,
      anon_sym_rpc,
  [4448] = 4,
    ACTIONS(552), 1,
      sym_comment,
    ACTIONS(576), 1,
      anon_sym_SQUOTE,
    STATE(174), 1,
      aux_sym_string_repeat1,
    ACTIONS(578), 2,
      aux_sym_string_token1,
      sym_escape_sequence,
  [4462] = 4,
    ACTIONS(552), 1,
      sym_comment,
    ACTIONS(581), 1,
      anon_sym_DQUOTE,
    STATE(175), 1,
      aux_sym_string_repeat2,
    ACTIONS(583), 2,
      aux_sym_string_token2,
      sym_escape_sequence,
  [4476] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(470), 3,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      sym_identifier,
  [4485] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(586), 1,
      anon_sym_SEMI,
    ACTIONS(588), 1,
      anon_sym_COMMA,
    STATE(177), 1,
      aux_sym_ranges_repeat1,
  [4498] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(591), 1,
      anon_sym_RBRACK,
    ACTIONS(593), 1,
      anon_sym_COMMA,
    STATE(191), 1,
      aux_sym_block_field_repeat1,
  [4511] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(593), 1,
      anon_sym_COMMA,
    ACTIONS(595), 1,
      anon_sym_RBRACK,
    STATE(184), 1,
      aux_sym_block_field_repeat1,
  [4524] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(597), 1,
      anon_sym_RBRACK,
    ACTIONS(599), 1,
      anon_sym_COMMA,
    STATE(195), 1,
      aux_sym_field_options_repeat1,
  [4537] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(601), 1,
      anon_sym_RBRACK,
    ACTIONS(603), 1,
      anon_sym_COMMA,
    STATE(181), 1,
      aux_sym_field_options_repeat1,
  [4550] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(389), 1,
      anon_sym_DOT,
    ACTIONS(606), 1,
      anon_sym_EQ,
    STATE(66), 1,
      aux_sym_option_name_repeat1,
  [4563] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(478), 1,
      anon_sym_LPAREN,
    ACTIONS(480), 1,
      sym_identifier,
    STATE(263), 1,
      sym_option_name,
  [4576] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(593), 1,
      anon_sym_COMMA,
    ACTIONS(608), 1,
      anon_sym_RBRACK,
    STATE(190), 1,
      aux_sym_block_field_repeat1,
  [4589] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(593), 1,
      anon_sym_COMMA,
    ACTIONS(610), 1,
      anon_sym_RBRACK,
    STATE(203), 1,
      aux_sym_block_field_repeat1,
  [4602] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(389), 1,
      anon_sym_DOT,
    ACTIONS(612), 1,
      anon_sym_EQ,
    STATE(66), 1,
      aux_sym_option_name_repeat1,
  [4615] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(614), 1,
      anon_sym_SEMI,
    ACTIONS(616), 1,
      anon_sym_LBRACE,
    STATE(169), 1,
      sym_rpc_body,
  [4628] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(389), 1,
      anon_sym_DOT,
    ACTIONS(618), 1,
      anon_sym_EQ,
    STATE(186), 1,
      aux_sym_option_name_repeat1,
  [4641] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(614), 1,
      anon_sym_SEMI,
    ACTIONS(616), 1,
      anon_sym_LBRACE,
    STATE(170), 1,
      sym_rpc_body,
  [4654] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(620), 1,
      anon_sym_RBRACK,
    ACTIONS(622), 1,
      anon_sym_COMMA,
    STATE(190), 1,
      aux_sym_block_field_repeat1,
  [4667] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(593), 1,
      anon_sym_COMMA,
    ACTIONS(625), 1,
      anon_sym_RBRACK,
    STATE(190), 1,
      aux_sym_block_field_repeat1,
  [4680] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(614), 1,
      anon_sym_SEMI,
    ACTIONS(616), 1,
      anon_sym_LBRACE,
    STATE(172), 1,
      sym_rpc_body,
  [4693] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(627), 1,
      anon_sym_SEMI,
    ACTIONS(629), 1,
      anon_sym_COMMA,
    STATE(193), 1,
      aux_sym_field_names_repeat1,
  [4706] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(593), 1,
      anon_sym_COMMA,
    ACTIONS(632), 1,
      anon_sym_RBRACK,
    STATE(190), 1,
      aux_sym_block_field_repeat1,
  [4719] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(599), 1,
      anon_sym_COMMA,
    ACTIONS(634), 1,
      anon_sym_RBRACK,
    STATE(181), 1,
      aux_sym_field_options_repeat1,
  [4732] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(636), 1,
      anon_sym_SEMI,
    ACTIONS(638), 1,
      anon_sym_COMMA,
    STATE(201), 1,
      aux_sym_ranges_repeat1,
  [4745] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(640), 1,
      anon_sym_SEMI,
    ACTIONS(642), 1,
      anon_sym_COMMA,
    STATE(202), 1,
      aux_sym_field_names_repeat1,
  [4758] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(478), 1,
      anon_sym_LPAREN,
    ACTIONS(480), 1,
      sym_identifier,
    STATE(309), 1,
      sym_option_name,
  [4771] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(646), 1,
      anon_sym_to,
    ACTIONS(644), 2,
      anon_sym_SEMI,
      anon_sym_COMMA,
  [4782] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(389), 1,
      anon_sym_DOT,
    ACTIONS(648), 1,
      anon_sym_EQ,
    STATE(182), 1,
      aux_sym_option_name_repeat1,
  [4795] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(638), 1,
      anon_sym_COMMA,
    ACTIONS(650), 1,
      anon_sym_SEMI,
    STATE(177), 1,
      aux_sym_ranges_repeat1,
  [4808] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(642), 1,
      anon_sym_COMMA,
    ACTIONS(652), 1,
      anon_sym_SEMI,
    STATE(193), 1,
      aux_sym_field_names_repeat1,
  [4821] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(593), 1,
      anon_sym_COMMA,
    ACTIONS(654), 1,
      anon_sym_RBRACK,
    STATE(190), 1,
      aux_sym_block_field_repeat1,
  [4834] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(656), 1,
      anon_sym_DOT,
    ACTIONS(658), 1,
      sym_identifier,
    STATE(239), 1,
      sym_full_ident,
  [4847] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(658), 1,
      sym_identifier,
    ACTIONS(660), 1,
      anon_sym_DOT,
    STATE(235), 1,
      sym_full_ident,
  [4860] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(593), 1,
      anon_sym_COMMA,
    ACTIONS(662), 1,
      anon_sym_RBRACK,
    STATE(194), 1,
      aux_sym_block_field_repeat1,
  [4873] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(478), 1,
      anon_sym_LPAREN,
    ACTIONS(480), 1,
      sym_identifier,
    STATE(307), 1,
      sym_option_name,
  [4886] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(478), 1,
      anon_sym_LPAREN,
    ACTIONS(480), 1,
      sym_identifier,
    STATE(308), 1,
      sym_option_name,
  [4899] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(664), 1,
      anon_sym_LBRACE,
    STATE(9), 1,
      sym_oneof_body,
  [4909] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(442), 1,
      sym_identifier,
    STATE(269), 1,
      sym_field_name,
  [4919] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(666), 2,
      anon_sym_RBRACK,
      anon_sym_COMMA,
  [4927] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(601), 2,
      anon_sym_RBRACK,
      anon_sym_COMMA,
  [4935] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(668), 1,
      sym_identifier,
    STATE(219), 1,
      aux_sym_message_or_enum_type_repeat1,
  [4945] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(670), 1,
      anon_sym_LBRACE,
    STATE(84), 1,
      sym_message_body,
  [4955] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(442), 1,
      sym_identifier,
    STATE(282), 1,
      sym_field_name,
  [4965] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(672), 1,
      sym_identifier,
    STATE(279), 1,
      sym_rpc_name,
  [4975] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(674), 1,
      anon_sym_SEMI,
    ACTIONS(676), 1,
      anon_sym_LBRACK,
  [4985] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(678), 1,
      sym_identifier,
    STATE(229), 1,
      sym_enum_name,
  [4995] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(680), 1,
      sym_identifier,
    STATE(219), 1,
      aux_sym_message_or_enum_type_repeat1,
  [5005] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(683), 1,
      anon_sym_SEMI,
    ACTIONS(685), 1,
      anon_sym_LBRACK,
  [5015] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(442), 1,
      sym_identifier,
    STATE(290), 1,
      sym_field_name,
  [5025] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(658), 1,
      sym_identifier,
    STATE(266), 1,
      sym_full_ident,
  [5035] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(658), 1,
      sym_identifier,
    STATE(257), 1,
      sym_full_ident,
  [5045] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(687), 2,
      anon_sym_GT,
      sym_identifier,
  [5053] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(586), 2,
      anon_sym_SEMI,
      anon_sym_COMMA,
  [5061] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(620), 2,
      anon_sym_RBRACK,
      anon_sym_COMMA,
  [5069] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(689), 1,
      sym_identifier,
    STATE(240), 1,
      sym_service_name,
  [5079] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(691), 1,
      anon_sym_SEMI,
    ACTIONS(693), 1,
      anon_sym_LBRACK,
  [5089] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(695), 1,
      anon_sym_LBRACE,
    STATE(83), 1,
      sym_enum_body,
  [5099] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(658), 1,
      sym_identifier,
    STATE(292), 1,
      sym_full_ident,
  [5109] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(627), 2,
      anon_sym_SEMI,
      anon_sym_COMMA,
  [5117] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(670), 1,
      anon_sym_LBRACE,
    STATE(87), 1,
      sym_message_body,
  [5127] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(658), 1,
      sym_identifier,
    STATE(214), 1,
      sym_full_ident,
  [5137] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(697), 1,
      anon_sym_SEMI,
    ACTIONS(699), 1,
      anon_sym_LBRACK,
  [5147] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(670), 1,
      anon_sym_LBRACE,
    STATE(89), 1,
      sym_message_body,
  [5157] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(442), 1,
      sym_identifier,
    STATE(273), 1,
      sym_field_name,
  [5167] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(701), 1,
      anon_sym_LBRACE,
    STATE(20), 1,
      sym_enum_body,
  [5177] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(703), 1,
      anon_sym_LBRACE,
    STATE(21), 1,
      sym_message_body,
  [5187] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(703), 1,
      anon_sym_LBRACE,
    STATE(22), 1,
      sym_message_body,
  [5197] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(705), 1,
      anon_sym_LBRACE,
    STATE(91), 1,
      sym_service_body,
  [5207] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(703), 1,
      anon_sym_LBRACE,
    STATE(25), 1,
      sym_message_body,
  [5217] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(707), 1,
      sym_identifier,
    STATE(232), 1,
      sym_message_name,
  [5227] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(678), 1,
      sym_identifier,
    STATE(237), 1,
      sym_enum_name,
  [5237] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(707), 1,
      sym_identifier,
    STATE(238), 1,
      sym_message_name,
  [5247] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(709), 2,
      anon_sym_SEMI,
      anon_sym_COMMA,
  [5255] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(658), 1,
      sym_identifier,
    STATE(241), 1,
      sym_full_ident,
  [5265] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(442), 1,
      sym_identifier,
    STATE(287), 1,
      sym_field_name,
  [5275] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(711), 1,
      anon_sym_SEMI,
    ACTIONS(713), 1,
      anon_sym_LBRACK,
  [5285] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(715), 1,
      sym_identifier,
    STATE(213), 1,
      aux_sym_message_or_enum_type_repeat1,
  [5295] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(715), 1,
      sym_identifier,
    STATE(219), 1,
      aux_sym_message_or_enum_type_repeat1,
  [5305] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(717), 2,
      anon_sym_DQUOTEproto3_DQUOTE,
      anon_sym_DQUOTEproto2_DQUOTE,
  [5313] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(719), 1,
      anon_sym_SEMI,
  [5320] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(721), 1,
      anon_sym_GT,
  [5327] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(723), 1,
      anon_sym_RPAREN,
  [5334] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(725), 1,
      sym_identifier,
  [5341] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(727), 1,
      anon_sym_LT,
  [5348] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(729), 1,
      anon_sym_RBRACK,
  [5355] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(731), 1,
      anon_sym_RPAREN,
  [5362] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(733), 1,
      anon_sym_RBRACK,
  [5369] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(735), 1,
      anon_sym_returns,
  [5376] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(737), 1,
      anon_sym_EQ,
  [5383] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(739), 1,
      anon_sym_LPAREN,
  [5390] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(741), 1,
      anon_sym_EQ,
  [5397] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(743), 1,
      anon_sym_SEMI,
  [5404] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(745), 1,
      anon_sym_RBRACK,
  [5411] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(747), 1,
      anon_sym_RPAREN,
  [5418] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(749), 1,
      anon_sym_LBRACE,
  [5425] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(751), 1,
      anon_sym_SEMI,
  [5432] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(753), 1,
      anon_sym_EQ,
  [5439] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(755), 1,
      anon_sym_SEMI,
  [5446] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(757), 1,
      anon_sym_LPAREN,
  [5453] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(759), 1,
      anon_sym_LBRACE,
  [5460] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(761), 1,
      anon_sym_EQ,
  [5467] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(763), 1,
      anon_sym_SEMI,
  [5474] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(765), 1,
      ts_builtin_sym_end,
  [5481] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(767), 1,
      anon_sym_RPAREN,
  [5488] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(769), 1,
      sym_identifier,
  [5495] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(771), 1,
      anon_sym_RBRACK,
  [5502] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(773), 1,
      anon_sym_LPAREN,
  [5509] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(775), 1,
      anon_sym_RBRACK,
  [5516] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(777), 1,
      anon_sym_SEMI,
  [5523] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(779), 1,
      anon_sym_EQ,
  [5530] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(781), 1,
      anon_sym_LBRACE,
  [5537] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(783), 1,
      anon_sym_SEMI,
  [5544] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(785), 1,
      anon_sym_COMMA,
  [5551] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(787), 1,
      sym_identifier,
  [5558] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(789), 1,
      anon_sym_EQ,
  [5565] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(791), 1,
      anon_sym_EQ,
  [5572] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(793), 1,
      anon_sym_COMMA,
  [5579] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(795), 1,
      anon_sym_EQ,
  [5586] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(797), 1,
      anon_sym_RPAREN,
  [5593] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(799), 1,
      anon_sym_SEMI,
  [5600] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(801), 1,
      anon_sym_SEMI,
  [5607] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(540), 1,
      anon_sym_DOT,
  [5614] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(803), 1,
      anon_sym_EQ,
  [5621] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(805), 1,
      anon_sym_SEMI,
  [5628] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(807), 1,
      anon_sym_SEMI,
  [5635] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(809), 1,
      anon_sym_SEMI,
  [5642] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(811), 1,
      anon_sym_SEMI,
  [5649] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(813), 1,
      anon_sym_RBRACK,
  [5656] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(815), 1,
      anon_sym_RBRACK,
  [5663] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(817), 1,
      anon_sym_SEMI,
  [5670] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(819), 1,
      anon_sym_EQ,
  [5677] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(821), 1,
      anon_sym_EQ,
  [5684] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(823), 1,
      anon_sym_RPAREN,
  [5691] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(825), 1,
      anon_sym_returns,
  [5698] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(827), 1,
      anon_sym_EQ,
  [5705] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(829), 1,
      anon_sym_EQ,
  [5712] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(831), 1,
      anon_sym_EQ,
  [5719] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(833), 1,
      anon_sym_SEMI,
  [5726] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(835), 1,
      anon_sym_SEMI,
  [5733] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(837), 1,
      anon_sym_LPAREN,
  [5740] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(839), 1,
      anon_sym_SEMI,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 86,
  [SMALL_STATE(4)] = 172,
  [SMALL_STATE(5)] = 258,
  [SMALL_STATE(6)] = 344,
  [SMALL_STATE(7)] = 430,
  [SMALL_STATE(8)] = 468,
  [SMALL_STATE(9)] = 506,
  [SMALL_STATE(10)] = 544,
  [SMALL_STATE(11)] = 582,
  [SMALL_STATE(12)] = 620,
  [SMALL_STATE(13)] = 658,
  [SMALL_STATE(14)] = 696,
  [SMALL_STATE(15)] = 734,
  [SMALL_STATE(16)] = 772,
  [SMALL_STATE(17)] = 810,
  [SMALL_STATE(18)] = 848,
  [SMALL_STATE(19)] = 886,
  [SMALL_STATE(20)] = 924,
  [SMALL_STATE(21)] = 962,
  [SMALL_STATE(22)] = 1000,
  [SMALL_STATE(23)] = 1038,
  [SMALL_STATE(24)] = 1076,
  [SMALL_STATE(25)] = 1114,
  [SMALL_STATE(26)] = 1152,
  [SMALL_STATE(27)] = 1190,
  [SMALL_STATE(28)] = 1228,
  [SMALL_STATE(29)] = 1266,
  [SMALL_STATE(30)] = 1304,
  [SMALL_STATE(31)] = 1355,
  [SMALL_STATE(32)] = 1406,
  [SMALL_STATE(33)] = 1457,
  [SMALL_STATE(34)] = 1508,
  [SMALL_STATE(35)] = 1539,
  [SMALL_STATE(36)] = 1590,
  [SMALL_STATE(37)] = 1619,
  [SMALL_STATE(38)] = 1658,
  [SMALL_STATE(39)] = 1687,
  [SMALL_STATE(40)] = 1735,
  [SMALL_STATE(41)] = 1783,
  [SMALL_STATE(42)] = 1819,
  [SMALL_STATE(43)] = 1847,
  [SMALL_STATE(44)] = 1895,
  [SMALL_STATE(45)] = 1931,
  [SMALL_STATE(46)] = 1967,
  [SMALL_STATE(47)] = 1995,
  [SMALL_STATE(48)] = 2043,
  [SMALL_STATE(49)] = 2091,
  [SMALL_STATE(50)] = 2119,
  [SMALL_STATE(51)] = 2167,
  [SMALL_STATE(52)] = 2212,
  [SMALL_STATE(53)] = 2257,
  [SMALL_STATE(54)] = 2302,
  [SMALL_STATE(55)] = 2347,
  [SMALL_STATE(56)] = 2392,
  [SMALL_STATE(57)] = 2437,
  [SMALL_STATE(58)] = 2479,
  [SMALL_STATE(59)] = 2521,
  [SMALL_STATE(60)] = 2563,
  [SMALL_STATE(61)] = 2605,
  [SMALL_STATE(62)] = 2628,
  [SMALL_STATE(63)] = 2665,
  [SMALL_STATE(64)] = 2702,
  [SMALL_STATE(65)] = 2723,
  [SMALL_STATE(66)] = 2752,
  [SMALL_STATE(67)] = 2773,
  [SMALL_STATE(68)] = 2790,
  [SMALL_STATE(69)] = 2819,
  [SMALL_STATE(70)] = 2848,
  [SMALL_STATE(71)] = 2865,
  [SMALL_STATE(72)] = 2894,
  [SMALL_STATE(73)] = 2923,
  [SMALL_STATE(74)] = 2943,
  [SMALL_STATE(75)] = 2959,
  [SMALL_STATE(76)] = 2979,
  [SMALL_STATE(77)] = 2994,
  [SMALL_STATE(78)] = 3009,
  [SMALL_STATE(79)] = 3024,
  [SMALL_STATE(80)] = 3039,
  [SMALL_STATE(81)] = 3054,
  [SMALL_STATE(82)] = 3069,
  [SMALL_STATE(83)] = 3090,
  [SMALL_STATE(84)] = 3105,
  [SMALL_STATE(85)] = 3120,
  [SMALL_STATE(86)] = 3135,
  [SMALL_STATE(87)] = 3150,
  [SMALL_STATE(88)] = 3165,
  [SMALL_STATE(89)] = 3186,
  [SMALL_STATE(90)] = 3201,
  [SMALL_STATE(91)] = 3216,
  [SMALL_STATE(92)] = 3231,
  [SMALL_STATE(93)] = 3246,
  [SMALL_STATE(94)] = 3261,
  [SMALL_STATE(95)] = 3283,
  [SMALL_STATE(96)] = 3305,
  [SMALL_STATE(97)] = 3319,
  [SMALL_STATE(98)] = 3333,
  [SMALL_STATE(99)] = 3355,
  [SMALL_STATE(100)] = 3377,
  [SMALL_STATE(101)] = 3389,
  [SMALL_STATE(102)] = 3409,
  [SMALL_STATE(103)] = 3421,
  [SMALL_STATE(104)] = 3443,
  [SMALL_STATE(105)] = 3461,
  [SMALL_STATE(106)] = 3473,
  [SMALL_STATE(107)] = 3491,
  [SMALL_STATE(108)] = 3509,
  [SMALL_STATE(109)] = 3529,
  [SMALL_STATE(110)] = 3541,
  [SMALL_STATE(111)] = 3561,
  [SMALL_STATE(112)] = 3583,
  [SMALL_STATE(113)] = 3602,
  [SMALL_STATE(114)] = 3613,
  [SMALL_STATE(115)] = 3632,
  [SMALL_STATE(116)] = 3649,
  [SMALL_STATE(117)] = 3666,
  [SMALL_STATE(118)] = 3685,
  [SMALL_STATE(119)] = 3696,
  [SMALL_STATE(120)] = 3715,
  [SMALL_STATE(121)] = 3728,
  [SMALL_STATE(122)] = 3739,
  [SMALL_STATE(123)] = 3750,
  [SMALL_STATE(124)] = 3769,
  [SMALL_STATE(125)] = 3780,
  [SMALL_STATE(126)] = 3791,
  [SMALL_STATE(127)] = 3808,
  [SMALL_STATE(128)] = 3825,
  [SMALL_STATE(129)] = 3838,
  [SMALL_STATE(130)] = 3849,
  [SMALL_STATE(131)] = 3862,
  [SMALL_STATE(132)] = 3881,
  [SMALL_STATE(133)] = 3892,
  [SMALL_STATE(134)] = 3903,
  [SMALL_STATE(135)] = 3922,
  [SMALL_STATE(136)] = 3933,
  [SMALL_STATE(137)] = 3946,
  [SMALL_STATE(138)] = 3957,
  [SMALL_STATE(139)] = 3970,
  [SMALL_STATE(140)] = 3981,
  [SMALL_STATE(141)] = 3998,
  [SMALL_STATE(142)] = 4015,
  [SMALL_STATE(143)] = 4032,
  [SMALL_STATE(144)] = 4051,
  [SMALL_STATE(145)] = 4068,
  [SMALL_STATE(146)] = 4079,
  [SMALL_STATE(147)] = 4090,
  [SMALL_STATE(148)] = 4107,
  [SMALL_STATE(149)] = 4118,
  [SMALL_STATE(150)] = 4131,
  [SMALL_STATE(151)] = 4142,
  [SMALL_STATE(152)] = 4153,
  [SMALL_STATE(153)] = 4170,
  [SMALL_STATE(154)] = 4189,
  [SMALL_STATE(155)] = 4200,
  [SMALL_STATE(156)] = 4216,
  [SMALL_STATE(157)] = 4228,
  [SMALL_STATE(158)] = 4244,
  [SMALL_STATE(159)] = 4256,
  [SMALL_STATE(160)] = 4270,
  [SMALL_STATE(161)] = 4284,
  [SMALL_STATE(162)] = 4300,
  [SMALL_STATE(163)] = 4316,
  [SMALL_STATE(164)] = 4330,
  [SMALL_STATE(165)] = 4344,
  [SMALL_STATE(166)] = 4356,
  [SMALL_STATE(167)] = 4372,
  [SMALL_STATE(168)] = 4388,
  [SMALL_STATE(169)] = 4398,
  [SMALL_STATE(170)] = 4408,
  [SMALL_STATE(171)] = 4418,
  [SMALL_STATE(172)] = 4428,
  [SMALL_STATE(173)] = 4438,
  [SMALL_STATE(174)] = 4448,
  [SMALL_STATE(175)] = 4462,
  [SMALL_STATE(176)] = 4476,
  [SMALL_STATE(177)] = 4485,
  [SMALL_STATE(178)] = 4498,
  [SMALL_STATE(179)] = 4511,
  [SMALL_STATE(180)] = 4524,
  [SMALL_STATE(181)] = 4537,
  [SMALL_STATE(182)] = 4550,
  [SMALL_STATE(183)] = 4563,
  [SMALL_STATE(184)] = 4576,
  [SMALL_STATE(185)] = 4589,
  [SMALL_STATE(186)] = 4602,
  [SMALL_STATE(187)] = 4615,
  [SMALL_STATE(188)] = 4628,
  [SMALL_STATE(189)] = 4641,
  [SMALL_STATE(190)] = 4654,
  [SMALL_STATE(191)] = 4667,
  [SMALL_STATE(192)] = 4680,
  [SMALL_STATE(193)] = 4693,
  [SMALL_STATE(194)] = 4706,
  [SMALL_STATE(195)] = 4719,
  [SMALL_STATE(196)] = 4732,
  [SMALL_STATE(197)] = 4745,
  [SMALL_STATE(198)] = 4758,
  [SMALL_STATE(199)] = 4771,
  [SMALL_STATE(200)] = 4782,
  [SMALL_STATE(201)] = 4795,
  [SMALL_STATE(202)] = 4808,
  [SMALL_STATE(203)] = 4821,
  [SMALL_STATE(204)] = 4834,
  [SMALL_STATE(205)] = 4847,
  [SMALL_STATE(206)] = 4860,
  [SMALL_STATE(207)] = 4873,
  [SMALL_STATE(208)] = 4886,
  [SMALL_STATE(209)] = 4899,
  [SMALL_STATE(210)] = 4909,
  [SMALL_STATE(211)] = 4919,
  [SMALL_STATE(212)] = 4927,
  [SMALL_STATE(213)] = 4935,
  [SMALL_STATE(214)] = 4945,
  [SMALL_STATE(215)] = 4955,
  [SMALL_STATE(216)] = 4965,
  [SMALL_STATE(217)] = 4975,
  [SMALL_STATE(218)] = 4985,
  [SMALL_STATE(219)] = 4995,
  [SMALL_STATE(220)] = 5005,
  [SMALL_STATE(221)] = 5015,
  [SMALL_STATE(222)] = 5025,
  [SMALL_STATE(223)] = 5035,
  [SMALL_STATE(224)] = 5045,
  [SMALL_STATE(225)] = 5053,
  [SMALL_STATE(226)] = 5061,
  [SMALL_STATE(227)] = 5069,
  [SMALL_STATE(228)] = 5079,
  [SMALL_STATE(229)] = 5089,
  [SMALL_STATE(230)] = 5099,
  [SMALL_STATE(231)] = 5109,
  [SMALL_STATE(232)] = 5117,
  [SMALL_STATE(233)] = 5127,
  [SMALL_STATE(234)] = 5137,
  [SMALL_STATE(235)] = 5147,
  [SMALL_STATE(236)] = 5157,
  [SMALL_STATE(237)] = 5167,
  [SMALL_STATE(238)] = 5177,
  [SMALL_STATE(239)] = 5187,
  [SMALL_STATE(240)] = 5197,
  [SMALL_STATE(241)] = 5207,
  [SMALL_STATE(242)] = 5217,
  [SMALL_STATE(243)] = 5227,
  [SMALL_STATE(244)] = 5237,
  [SMALL_STATE(245)] = 5247,
  [SMALL_STATE(246)] = 5255,
  [SMALL_STATE(247)] = 5265,
  [SMALL_STATE(248)] = 5275,
  [SMALL_STATE(249)] = 5285,
  [SMALL_STATE(250)] = 5295,
  [SMALL_STATE(251)] = 5305,
  [SMALL_STATE(252)] = 5313,
  [SMALL_STATE(253)] = 5320,
  [SMALL_STATE(254)] = 5327,
  [SMALL_STATE(255)] = 5334,
  [SMALL_STATE(256)] = 5341,
  [SMALL_STATE(257)] = 5348,
  [SMALL_STATE(258)] = 5355,
  [SMALL_STATE(259)] = 5362,
  [SMALL_STATE(260)] = 5369,
  [SMALL_STATE(261)] = 5376,
  [SMALL_STATE(262)] = 5383,
  [SMALL_STATE(263)] = 5390,
  [SMALL_STATE(264)] = 5397,
  [SMALL_STATE(265)] = 5404,
  [SMALL_STATE(266)] = 5411,
  [SMALL_STATE(267)] = 5418,
  [SMALL_STATE(268)] = 5425,
  [SMALL_STATE(269)] = 5432,
  [SMALL_STATE(270)] = 5439,
  [SMALL_STATE(271)] = 5446,
  [SMALL_STATE(272)] = 5453,
  [SMALL_STATE(273)] = 5460,
  [SMALL_STATE(274)] = 5467,
  [SMALL_STATE(275)] = 5474,
  [SMALL_STATE(276)] = 5481,
  [SMALL_STATE(277)] = 5488,
  [SMALL_STATE(278)] = 5495,
  [SMALL_STATE(279)] = 5502,
  [SMALL_STATE(280)] = 5509,
  [SMALL_STATE(281)] = 5516,
  [SMALL_STATE(282)] = 5523,
  [SMALL_STATE(283)] = 5530,
  [SMALL_STATE(284)] = 5537,
  [SMALL_STATE(285)] = 5544,
  [SMALL_STATE(286)] = 5551,
  [SMALL_STATE(287)] = 5558,
  [SMALL_STATE(288)] = 5565,
  [SMALL_STATE(289)] = 5572,
  [SMALL_STATE(290)] = 5579,
  [SMALL_STATE(291)] = 5586,
  [SMALL_STATE(292)] = 5593,
  [SMALL_STATE(293)] = 5600,
  [SMALL_STATE(294)] = 5607,
  [SMALL_STATE(295)] = 5614,
  [SMALL_STATE(296)] = 5621,
  [SMALL_STATE(297)] = 5628,
  [SMALL_STATE(298)] = 5635,
  [SMALL_STATE(299)] = 5642,
  [SMALL_STATE(300)] = 5649,
  [SMALL_STATE(301)] = 5656,
  [SMALL_STATE(302)] = 5663,
  [SMALL_STATE(303)] = 5670,
  [SMALL_STATE(304)] = 5677,
  [SMALL_STATE(305)] = 5684,
  [SMALL_STATE(306)] = 5691,
  [SMALL_STATE(307)] = 5698,
  [SMALL_STATE(308)] = 5705,
  [SMALL_STATE(309)] = 5712,
  [SMALL_STATE(310)] = 5719,
  [SMALL_STATE(311)] = 5726,
  [SMALL_STATE(312)] = 5733,
  [SMALL_STATE(313)] = 5740,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0, 0, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(261),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(304),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(110),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(230),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(183),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(218),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(242),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(205),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(227),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [29] = {.entry = {.count = 1, .reusable = false}}, SHIFT(208),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(249),
  [33] = {.entry = {.count = 1, .reusable = false}}, SHIFT(243),
  [35] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [37] = {.entry = {.count = 1, .reusable = false}}, SHIFT(244),
  [39] = {.entry = {.count = 1, .reusable = false}}, SHIFT(204),
  [41] = {.entry = {.count = 1, .reusable = false}}, SHIFT(37),
  [43] = {.entry = {.count = 1, .reusable = false}}, SHIFT(44),
  [45] = {.entry = {.count = 1, .reusable = false}}, SHIFT(277),
  [47] = {.entry = {.count = 1, .reusable = false}}, SHIFT(256),
  [49] = {.entry = {.count = 1, .reusable = false}}, SHIFT(224),
  [51] = {.entry = {.count = 1, .reusable = false}}, SHIFT(62),
  [53] = {.entry = {.count = 1, .reusable = false}}, SHIFT(108),
  [55] = {.entry = {.count = 1, .reusable = false}}, SHIFT(158),
  [57] = {.entry = {.count = 1, .reusable = true}}, SHIFT(90),
  [59] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0), SHIFT_REPEAT(23),
  [62] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0), SHIFT_REPEAT(208),
  [65] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0), SHIFT_REPEAT(249),
  [68] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0), SHIFT_REPEAT(243),
  [71] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0),
  [73] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0), SHIFT_REPEAT(244),
  [76] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0), SHIFT_REPEAT(204),
  [79] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0), SHIFT_REPEAT(37),
  [82] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0), SHIFT_REPEAT(44),
  [85] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0), SHIFT_REPEAT(277),
  [88] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0), SHIFT_REPEAT(256),
  [91] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0), SHIFT_REPEAT(224),
  [94] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0), SHIFT_REPEAT(62),
  [97] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0), SHIFT_REPEAT(108),
  [100] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0), SHIFT_REPEAT(158),
  [103] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [105] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [107] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_body, 2, 0, 0),
  [109] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_enum_body, 2, 0, 0),
  [111] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field, 8, 0, 0),
  [113] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_field, 8, 0, 0),
  [115] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_oneof, 3, 0, 0),
  [117] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_oneof, 3, 0, 0),
  [119] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_extensions, 3, 0, 0),
  [121] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_extensions, 3, 0, 0),
  [123] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_oneof_body, 3, 0, 0),
  [125] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_oneof_body, 3, 0, 0),
  [127] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_oneof_body, 2, 0, 0),
  [129] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_oneof_body, 2, 0, 0),
  [131] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field, 7, 0, 0),
  [133] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_field, 7, 0, 0),
  [135] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field, 5, 0, 0),
  [137] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_field, 5, 0, 0),
  [139] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field, 6, 0, 0),
  [141] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_field, 6, 0, 0),
  [143] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field, 9, 0, 0),
  [145] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_field, 9, 0, 0),
  [147] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field, 10, 0, 0),
  [149] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_field, 10, 0, 0),
  [151] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_field, 10, 0, 0),
  [153] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_map_field, 10, 0, 0),
  [155] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_field, 13, 0, 0),
  [157] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_map_field, 13, 0, 0),
  [159] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum, 3, 0, 0),
  [161] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_enum, 3, 0, 0),
  [163] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message, 3, 0, 0),
  [165] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_message, 3, 0, 0),
  [167] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_extend, 3, 0, 0),
  [169] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_extend, 3, 0, 0),
  [171] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_empty_statement, 1, 0, 0),
  [173] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_empty_statement, 1, 0, 0),
  [175] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_body, 2, 0, 0),
  [177] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_message_body, 2, 0, 0),
  [179] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_extend, 4, 0, 0),
  [181] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_extend, 4, 0, 0),
  [183] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_body, 3, 0, 0),
  [185] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_enum_body, 3, 0, 0),
  [187] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_body, 3, 0, 0),
  [189] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_message_body, 3, 0, 0),
  [191] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_reserved, 3, 0, 0),
  [193] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_reserved, 3, 0, 0),
  [195] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_option, 5, 0, 4),
  [197] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_option, 5, 0, 4),
  [199] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_oneof_body_repeat1, 2, 0, 0), SHIFT_REPEAT(46),
  [202] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_oneof_body_repeat1, 2, 0, 0), SHIFT_REPEAT(198),
  [205] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_oneof_body_repeat1, 2, 0, 0), SHIFT_REPEAT(249),
  [208] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_oneof_body_repeat1, 2, 0, 0),
  [210] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_oneof_body_repeat1, 2, 0, 0), SHIFT_REPEAT(224),
  [213] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_oneof_body_repeat1, 2, 0, 0), SHIFT_REPEAT(158),
  [216] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [218] = {.entry = {.count = 1, .reusable = false}}, SHIFT(198),
  [220] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [222] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [224] = {.entry = {.count = 1, .reusable = true}}, SHIFT(103),
  [226] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [228] = {.entry = {.count = 1, .reusable = true}}, SHIFT(147),
  [230] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [232] = {.entry = {.count = 1, .reusable = false}}, SHIFT(73),
  [234] = {.entry = {.count = 1, .reusable = false}}, SHIFT(109),
  [236] = {.entry = {.count = 1, .reusable = false}}, SHIFT(154),
  [238] = {.entry = {.count = 1, .reusable = true}}, SHIFT(154),
  [240] = {.entry = {.count = 1, .reusable = false}}, SHIFT(121),
  [242] = {.entry = {.count = 1, .reusable = true}}, SHIFT(163),
  [244] = {.entry = {.count = 1, .reusable = true}}, SHIFT(164),
  [246] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_oneof_field, 4, 0, 0),
  [248] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_oneof_field, 4, 0, 0),
  [250] = {.entry = {.count = 1, .reusable = true}}, SHIFT(114),
  [252] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [254] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [256] = {.entry = {.count = 1, .reusable = false}}, SHIFT(151),
  [258] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_int_lit, 1, 0, 0),
  [260] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_int_lit, 1, 0, 0),
  [262] = {.entry = {.count = 1, .reusable = false}}, SHIFT(45),
  [264] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_number, 1, 0, 0),
  [266] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_field_number, 1, 0, 0),
  [268] = {.entry = {.count = 1, .reusable = true}}, SHIFT(146),
  [270] = {.entry = {.count = 1, .reusable = true}}, SHIFT(140),
  [272] = {.entry = {.count = 1, .reusable = false}}, SHIFT(150),
  [274] = {.entry = {.count = 1, .reusable = true}}, SHIFT(150),
  [276] = {.entry = {.count = 1, .reusable = false}}, SHIFT(179),
  [278] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [280] = {.entry = {.count = 1, .reusable = false}}, SHIFT(129),
  [282] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_oneof_field, 7, 0, 0),
  [284] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_oneof_field, 7, 0, 0),
  [286] = {.entry = {.count = 1, .reusable = true}}, SHIFT(125),
  [288] = {.entry = {.count = 1, .reusable = false}}, SHIFT(178),
  [290] = {.entry = {.count = 1, .reusable = true}}, SHIFT(133),
  [292] = {.entry = {.count = 1, .reusable = false}}, SHIFT(185),
  [294] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [296] = {.entry = {.count = 1, .reusable = false}}, SHIFT(135),
  [298] = {.entry = {.count = 1, .reusable = true}}, SHIFT(124),
  [300] = {.entry = {.count = 1, .reusable = false}}, SHIFT(206),
  [302] = {.entry = {.count = 1, .reusable = false}}, SHIFT(211),
  [304] = {.entry = {.count = 1, .reusable = false}}, SHIFT(298),
  [306] = {.entry = {.count = 1, .reusable = false}}, SHIFT(226),
  [308] = {.entry = {.count = 1, .reusable = false}}, SHIFT(284),
  [310] = {.entry = {.count = 1, .reusable = false}}, SHIFT(293),
  [312] = {.entry = {.count = 1, .reusable = false}}, SHIFT(297),
  [314] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 2, 0, 0),
  [316] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [318] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [320] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(67),
  [323] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(110),
  [326] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(230),
  [329] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(183),
  [332] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(218),
  [335] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(242),
  [338] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(205),
  [341] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(227),
  [344] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_name, 1, 0, 0),
  [346] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_field_name, 1, 0, 0),
  [348] = {.entry = {.count = 1, .reusable = true}}, SHIFT(197),
  [350] = {.entry = {.count = 1, .reusable = true}}, SHIFT(285),
  [352] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_enum_body_repeat1, 2, 0, 0), SHIFT_REPEAT(128),
  [355] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_enum_body_repeat1, 2, 0, 0), SHIFT_REPEAT(207),
  [358] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_enum_body_repeat1, 2, 0, 0),
  [360] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_enum_body_repeat1, 2, 0, 0), SHIFT_REPEAT(63),
  [363] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_enum_body_repeat1, 2, 0, 0), SHIFT_REPEAT(295),
  [366] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_option_name_repeat1, 2, 0, 0),
  [368] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_option_name_repeat1, 2, 0, 0), SHIFT_REPEAT(255),
  [371] = {.entry = {.count = 1, .reusable = true}}, SHIFT(128),
  [373] = {.entry = {.count = 1, .reusable = false}}, SHIFT(207),
  [375] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [377] = {.entry = {.count = 1, .reusable = false}}, SHIFT(63),
  [379] = {.entry = {.count = 1, .reusable = false}}, SHIFT(295),
  [381] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [383] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [385] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [387] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_full_ident, 1, 0, 0),
  [389] = {.entry = {.count = 1, .reusable = true}}, SHIFT(255),
  [391] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_full_ident, 2, 0, 0),
  [393] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_syntax, 4, 0, 0),
  [395] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import, 4, 0, 3),
  [397] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_edition, 4, 0, 2),
  [399] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_package, 3, 0, 0),
  [401] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 1, 0, 0),
  [403] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_service_body, 2, 0, 0),
  [405] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_string_repeat3, 2, 0, 0),
  [407] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_string_repeat3, 2, 0, 0), SHIFT_REPEAT(163),
  [410] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_string_repeat3, 2, 0, 0), SHIFT_REPEAT(164),
  [413] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_service, 3, 0, 0),
  [415] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import, 3, 0, 1),
  [417] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_service_body, 3, 0, 0),
  [419] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_service_body_repeat1, 2, 0, 0), SHIFT_REPEAT(67),
  [422] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_service_body_repeat1, 2, 0, 0), SHIFT_REPEAT(183),
  [425] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_service_body_repeat1, 2, 0, 0),
  [427] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_service_body_repeat1, 2, 0, 0), SHIFT_REPEAT(216),
  [430] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [432] = {.entry = {.count = 1, .reusable = true}}, SHIFT(216),
  [434] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_string_repeat3, 3, 0, 0),
  [436] = {.entry = {.count = 1, .reusable = true}}, SHIFT(86),
  [438] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [440] = {.entry = {.count = 1, .reusable = true}}, SHIFT(223),
  [442] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [444] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__constant, 2, 0, 0),
  [446] = {.entry = {.count = 1, .reusable = true}}, SHIFT(231),
  [448] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_lit, 3, 0, 0),
  [450] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [452] = {.entry = {.count = 1, .reusable = true}}, SHIFT(171),
  [454] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_lit, 2, 0, 0),
  [456] = {.entry = {.count = 1, .reusable = true}}, SHIFT(173),
  [458] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_rpc_body_repeat1, 2, 0, 0), SHIFT_REPEAT(67),
  [461] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_rpc_body_repeat1, 2, 0, 0), SHIFT_REPEAT(183),
  [464] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_rpc_body_repeat1, 2, 0, 0),
  [466] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bool, 1, 0, 0),
  [468] = {.entry = {.count = 1, .reusable = true}}, SHIFT(161),
  [470] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_block_lit_repeat1, 2, 0, 0),
  [472] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_block_lit_repeat1, 2, 0, 0), SHIFT_REPEAT(223),
  [475] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_block_lit_repeat1, 2, 0, 0), SHIFT_REPEAT(61),
  [478] = {.entry = {.count = 1, .reusable = true}}, SHIFT(222),
  [480] = {.entry = {.count = 1, .reusable = true}}, SHIFT(188),
  [482] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_field, 7, 0, 20),
  [484] = {.entry = {.count = 1, .reusable = false}}, SHIFT(167),
  [486] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_field, 8, 0, 21),
  [488] = {.entry = {.count = 1, .reusable = false}}, SHIFT(157),
  [490] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_field, 4, 0, 8),
  [492] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_field, 4, 0, 9),
  [494] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_field, 3, 0, 6),
  [496] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_field, 4, 0, 10),
  [498] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_field, 3, 0, 7),
  [500] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_field, 4, 0, 0),
  [502] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_enum_field, 4, 0, 0),
  [504] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_field, 7, 0, 19),
  [506] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_field, 5, 0, 11),
  [508] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_field, 5, 0, 12),
  [510] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_field, 5, 0, 13),
  [512] = {.entry = {.count = 1, .reusable = true}}, SHIFT(176),
  [514] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_block_lit_repeat1, 1, 0, 0),
  [516] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_field, 5, 0, 14),
  [518] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [520] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [522] = {.entry = {.count = 1, .reusable = false}}, SHIFT(36),
  [524] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_field, 6, 0, 15),
  [526] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_field, 6, 0, 16),
  [528] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_field, 6, 0, 17),
  [530] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_field, 7, 0, 0),
  [532] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_enum_field, 7, 0, 0),
  [534] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_field, 2, 0, 5),
  [536] = {.entry = {.count = 1, .reusable = true}}, SHIFT(245),
  [538] = {.entry = {.count = 1, .reusable = false}}, SHIFT(166),
  [540] = {.entry = {.count = 1, .reusable = true}}, SHIFT(286),
  [542] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_or_enum_type, 3, 0, 0),
  [544] = {.entry = {.count = 1, .reusable = true}}, SHIFT(158),
  [546] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_or_enum_type, 1, 0, 0),
  [548] = {.entry = {.count = 1, .reusable = false}}, SHIFT(97),
  [550] = {.entry = {.count = 1, .reusable = true}}, SHIFT(174),
  [552] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [554] = {.entry = {.count = 1, .reusable = true}}, SHIFT(175),
  [556] = {.entry = {.count = 1, .reusable = false}}, SHIFT(96),
  [558] = {.entry = {.count = 1, .reusable = true}}, SHIFT(159),
  [560] = {.entry = {.count = 1, .reusable = true}}, SHIFT(160),
  [562] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_or_enum_type, 2, 0, 0),
  [564] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rpc_body, 1, 0, 0),
  [566] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rpc, 10, 0, 0),
  [568] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rpc, 11, 0, 0),
  [570] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rpc_body, 2, 0, 0),
  [572] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rpc, 12, 0, 0),
  [574] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rpc_body, 3, 0, 0),
  [576] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_repeat1, 2, 0, 0),
  [578] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_string_repeat1, 2, 0, 0), SHIFT_REPEAT(174),
  [581] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_repeat2, 2, 0, 0),
  [583] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_string_repeat2, 2, 0, 0), SHIFT_REPEAT(175),
  [586] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_ranges_repeat1, 2, 0, 0),
  [588] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_ranges_repeat1, 2, 0, 0), SHIFT_REPEAT(127),
  [591] = {.entry = {.count = 1, .reusable = true}}, SHIFT(139),
  [593] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [595] = {.entry = {.count = 1, .reusable = true}}, SHIFT(113),
  [597] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_options, 1, 0, 0),
  [599] = {.entry = {.count = 1, .reusable = true}}, SHIFT(162),
  [601] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_field_options_repeat1, 2, 0, 0),
  [603] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_field_options_repeat1, 2, 0, 0), SHIFT_REPEAT(162),
  [606] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_option_name, 4, 0, 0),
  [608] = {.entry = {.count = 1, .reusable = true}}, SHIFT(118),
  [610] = {.entry = {.count = 1, .reusable = true}}, SHIFT(145),
  [612] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_option_name, 2, 0, 0),
  [614] = {.entry = {.count = 1, .reusable = true}}, SHIFT(168),
  [616] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [618] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_option_name, 1, 0, 0),
  [620] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_block_field_repeat1, 2, 0, 0),
  [622] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_block_field_repeat1, 2, 0, 0), SHIFT_REPEAT(53),
  [625] = {.entry = {.count = 1, .reusable = true}}, SHIFT(148),
  [627] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_field_names_repeat1, 2, 0, 0),
  [629] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_field_names_repeat1, 2, 0, 0), SHIFT_REPEAT(101),
  [632] = {.entry = {.count = 1, .reusable = true}}, SHIFT(137),
  [634] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_options, 2, 0, 0),
  [636] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ranges, 1, 0, 0),
  [638] = {.entry = {.count = 1, .reusable = true}}, SHIFT(127),
  [640] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_names, 1, 0, 0),
  [642] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [644] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_range, 1, 0, 0),
  [646] = {.entry = {.count = 1, .reusable = true}}, SHIFT(152),
  [648] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_option_name, 3, 0, 0),
  [650] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ranges, 2, 0, 0),
  [652] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_names, 2, 0, 0),
  [654] = {.entry = {.count = 1, .reusable = true}}, SHIFT(132),
  [656] = {.entry = {.count = 1, .reusable = true}}, SHIFT(246),
  [658] = {.entry = {.count = 1, .reusable = true}}, SHIFT(73),
  [660] = {.entry = {.count = 1, .reusable = true}}, SHIFT(233),
  [662] = {.entry = {.count = 1, .reusable = true}}, SHIFT(122),
  [664] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [666] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_option, 3, 0, 18),
  [668] = {.entry = {.count = 1, .reusable = true}}, SHIFT(156),
  [670] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [672] = {.entry = {.count = 1, .reusable = true}}, SHIFT(312),
  [674] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [676] = {.entry = {.count = 1, .reusable = true}}, SHIFT(143),
  [678] = {.entry = {.count = 1, .reusable = true}}, SHIFT(267),
  [680] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_message_or_enum_type_repeat1, 2, 0, 0), SHIFT_REPEAT(294),
  [683] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [685] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [687] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type, 1, 0, 0),
  [689] = {.entry = {.count = 1, .reusable = true}}, SHIFT(283),
  [691] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [693] = {.entry = {.count = 1, .reusable = true}}, SHIFT(131),
  [695] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [697] = {.entry = {.count = 1, .reusable = true}}, SHIFT(130),
  [699] = {.entry = {.count = 1, .reusable = true}}, SHIFT(134),
  [701] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [703] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [705] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [707] = {.entry = {.count = 1, .reusable = true}}, SHIFT(272),
  [709] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_range, 3, 0, 0),
  [711] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [713] = {.entry = {.count = 1, .reusable = true}}, SHIFT(112),
  [715] = {.entry = {.count = 1, .reusable = true}}, SHIFT(165),
  [717] = {.entry = {.count = 1, .reusable = true}}, SHIFT(274),
  [719] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [721] = {.entry = {.count = 1, .reusable = true}}, SHIFT(210),
  [723] = {.entry = {.count = 1, .reusable = true}}, SHIFT(192),
  [725] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [727] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [729] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [731] = {.entry = {.count = 1, .reusable = true}}, SHIFT(306),
  [733] = {.entry = {.count = 1, .reusable = true}}, SHIFT(264),
  [735] = {.entry = {.count = 1, .reusable = true}}, SHIFT(262),
  [737] = {.entry = {.count = 1, .reusable = true}}, SHIFT(251),
  [739] = {.entry = {.count = 1, .reusable = true}}, SHIFT(153),
  [741] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [743] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [745] = {.entry = {.count = 1, .reusable = true}}, SHIFT(252),
  [747] = {.entry = {.count = 1, .reusable = true}}, SHIFT(200),
  [749] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_name, 1, 0, 0),
  [751] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [753] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [755] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [757] = {.entry = {.count = 1, .reusable = true}}, SHIFT(117),
  [759] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_name, 1, 0, 0),
  [761] = {.entry = {.count = 1, .reusable = true}}, SHIFT(126),
  [763] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [765] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [767] = {.entry = {.count = 1, .reusable = true}}, SHIFT(260),
  [769] = {.entry = {.count = 1, .reusable = true}}, SHIFT(209),
  [771] = {.entry = {.count = 1, .reusable = true}}, SHIFT(299),
  [773] = {.entry = {.count = 1, .reusable = true}}, SHIFT(119),
  [775] = {.entry = {.count = 1, .reusable = true}}, SHIFT(313),
  [777] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [779] = {.entry = {.count = 1, .reusable = true}}, SHIFT(141),
  [781] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_service_name, 1, 0, 0),
  [783] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [785] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_key_type, 1, 0, 0),
  [787] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_message_or_enum_type_repeat1, 2, 0, 0),
  [789] = {.entry = {.count = 1, .reusable = true}}, SHIFT(116),
  [791] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [793] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [795] = {.entry = {.count = 1, .reusable = true}}, SHIFT(144),
  [797] = {.entry = {.count = 1, .reusable = true}}, SHIFT(187),
  [799] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [801] = {.entry = {.count = 1, .reusable = true}}, SHIFT(136),
  [803] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_variant_name, 1, 0, 0),
  [805] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [807] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [809] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [811] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [813] = {.entry = {.count = 1, .reusable = true}}, SHIFT(270),
  [815] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [817] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [819] = {.entry = {.count = 1, .reusable = true}}, SHIFT(142),
  [821] = {.entry = {.count = 1, .reusable = true}}, SHIFT(155),
  [823] = {.entry = {.count = 1, .reusable = true}}, SHIFT(189),
  [825] = {.entry = {.count = 1, .reusable = true}}, SHIFT(271),
  [827] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [829] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [831] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [833] = {.entry = {.count = 1, .reusable = true}}, SHIFT(120),
  [835] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [837] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rpc_name, 1, 0, 0),
  [839] = {.entry = {.count = 1, .reusable = true}}, SHIFT(149),
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

TS_PUBLIC const TSLanguage *tree_sitter_proto(void) {
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
