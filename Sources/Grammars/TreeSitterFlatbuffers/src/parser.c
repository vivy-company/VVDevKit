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
#define STATE_COUNT 345
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 107
#define ALIAS_COUNT 0
#define TOKEN_COUNT 62
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 39
#define MAX_ALIAS_SEQUENCE_LENGTH 11
#define PRODUCTION_ID_COUNT 96

enum ts_symbol_identifiers {
  sym_documentation = 1,
  anon_sym_include = 2,
  anon_sym_SEMI = 3,
  anon_sym_namespace = 4,
  anon_sym_attribute = 5,
  anon_sym_DQUOTE = 6,
  anon_sym_table = 7,
  anon_sym_struct = 8,
  anon_sym_LBRACE = 9,
  anon_sym_RBRACE = 10,
  anon_sym_enum = 11,
  anon_sym_COLON = 12,
  anon_sym_COMMA = 13,
  anon_sym_union = 14,
  anon_sym_root_type = 15,
  anon_sym_file_extension = 16,
  anon_sym_file_identifier = 17,
  anon_sym_LBRACK = 18,
  anon_sym_RBRACK = 19,
  anon_sym_EQ = 20,
  anon_sym_bool = 21,
  anon_sym_byte = 22,
  anon_sym_ubyte = 23,
  anon_sym_short = 24,
  anon_sym_ushort = 25,
  anon_sym_int = 26,
  anon_sym_uint = 27,
  anon_sym_float = 28,
  anon_sym_long = 29,
  anon_sym_ulong = 30,
  anon_sym_double = 31,
  anon_sym_int8 = 32,
  anon_sym_uint8 = 33,
  anon_sym_int16 = 34,
  anon_sym_uint16 = 35,
  anon_sym_int32 = 36,
  anon_sym_uint32 = 37,
  anon_sym_int64 = 38,
  anon_sym_uint64 = 39,
  anon_sym_float32 = 40,
  anon_sym_float64 = 41,
  anon_sym_string = 42,
  anon_sym_rpc_service = 43,
  anon_sym_LPAREN = 44,
  anon_sym_RPAREN = 45,
  sym_identifier = 46,
  anon_sym_DOT = 47,
  sym_plus_token = 48,
  sym_minus_token = 49,
  sym_true = 50,
  sym_false = 51,
  aux_sym_decimal_lit_token1 = 52,
  anon_sym_0 = 53,
  sym_hex_lit = 54,
  aux_sym_float_lit_token1 = 55,
  anon_sym_infinity = 56,
  anon_sym_inf = 57,
  sym_nan_token = 58,
  aux_sym_string_constant_token1 = 59,
  sym_escape_sequence = 60,
  sym_comment = 61,
  sym_source_file = 62,
  sym_include = 63,
  sym_namespace_decl = 64,
  sym_attribute_decl = 65,
  sym_type_decl = 66,
  sym_enum_decl = 67,
  sym_union_decl = 68,
  sym_object = 69,
  sym_root_decl = 70,
  sym_file_extension_decl = 71,
  sym_file_identifier_decl = 72,
  sym_value = 73,
  sym_enum_val_decl = 74,
  sym_field_decl = 75,
  sym_union_field_decl = 76,
  sym_type = 77,
  sym_rpc_decl = 78,
  sym_rpc_method = 79,
  sym_metadata = 80,
  sym_field_and_value = 81,
  sym_single_value = 82,
  sym_full_ident = 83,
  sym_scalar = 84,
  sym_bool_constant = 85,
  sym_int_constant = 86,
  sym_float_constant = 87,
  sym_plus_minus_constant = 88,
  sym_int_lit = 89,
  sym_decimal_lit = 90,
  sym_float_lit = 91,
  sym_inf_token = 92,
  sym_string_constant = 93,
  aux_sym_source_file_repeat1 = 94,
  aux_sym_source_file_repeat2 = 95,
  aux_sym_type_decl_repeat1 = 96,
  aux_sym_type_decl_repeat2 = 97,
  aux_sym_enum_decl_repeat1 = 98,
  aux_sym_union_decl_repeat1 = 99,
  aux_sym_union_decl_repeat2 = 100,
  aux_sym_object_repeat1 = 101,
  aux_sym_value_repeat1 = 102,
  aux_sym_rpc_decl_repeat1 = 103,
  aux_sym_metadata_repeat1 = 104,
  aux_sym_full_ident_repeat1 = 105,
  aux_sym_string_constant_repeat1 = 106,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_documentation] = "documentation",
  [anon_sym_include] = "include",
  [anon_sym_SEMI] = ";",
  [anon_sym_namespace] = "namespace",
  [anon_sym_attribute] = "attribute",
  [anon_sym_DQUOTE] = "\"",
  [anon_sym_table] = "table",
  [anon_sym_struct] = "struct",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_enum] = "enum",
  [anon_sym_COLON] = ":",
  [anon_sym_COMMA] = ",",
  [anon_sym_union] = "union",
  [anon_sym_root_type] = "root_type",
  [anon_sym_file_extension] = "file_extension",
  [anon_sym_file_identifier] = "file_identifier",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [anon_sym_EQ] = "=",
  [anon_sym_bool] = "bool",
  [anon_sym_byte] = "byte",
  [anon_sym_ubyte] = "ubyte",
  [anon_sym_short] = "short",
  [anon_sym_ushort] = "ushort",
  [anon_sym_int] = "int",
  [anon_sym_uint] = "uint",
  [anon_sym_float] = "float",
  [anon_sym_long] = "long",
  [anon_sym_ulong] = "ulong",
  [anon_sym_double] = "double",
  [anon_sym_int8] = "int8",
  [anon_sym_uint8] = "uint8",
  [anon_sym_int16] = "int16",
  [anon_sym_uint16] = "uint16",
  [anon_sym_int32] = "int32",
  [anon_sym_uint32] = "uint32",
  [anon_sym_int64] = "int64",
  [anon_sym_uint64] = "uint64",
  [anon_sym_float32] = "float32",
  [anon_sym_float64] = "float64",
  [anon_sym_string] = "string",
  [anon_sym_rpc_service] = "rpc_service",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [sym_identifier] = "identifier",
  [anon_sym_DOT] = ".",
  [sym_plus_token] = "plus_token",
  [sym_minus_token] = "minus_token",
  [sym_true] = "true",
  [sym_false] = "false",
  [aux_sym_decimal_lit_token1] = "decimal_lit_token1",
  [anon_sym_0] = "0",
  [sym_hex_lit] = "hex_lit",
  [aux_sym_float_lit_token1] = "float_lit_token1",
  [anon_sym_infinity] = "infinity",
  [anon_sym_inf] = "inf",
  [sym_nan_token] = "nan_token",
  [aux_sym_string_constant_token1] = "string_constant_token1",
  [sym_escape_sequence] = "escape_sequence",
  [sym_comment] = "comment",
  [sym_source_file] = "source_file",
  [sym_include] = "include",
  [sym_namespace_decl] = "namespace_decl",
  [sym_attribute_decl] = "attribute_decl",
  [sym_type_decl] = "type_decl",
  [sym_enum_decl] = "enum_decl",
  [sym_union_decl] = "union_decl",
  [sym_object] = "object",
  [sym_root_decl] = "root_decl",
  [sym_file_extension_decl] = "file_extension_decl",
  [sym_file_identifier_decl] = "file_identifier_decl",
  [sym_value] = "value",
  [sym_enum_val_decl] = "enum_val_decl",
  [sym_field_decl] = "field_decl",
  [sym_union_field_decl] = "union_field_decl",
  [sym_type] = "type",
  [sym_rpc_decl] = "rpc_decl",
  [sym_rpc_method] = "rpc_method",
  [sym_metadata] = "metadata",
  [sym_field_and_value] = "field_and_value",
  [sym_single_value] = "single_value",
  [sym_full_ident] = "full_ident",
  [sym_scalar] = "scalar",
  [sym_bool_constant] = "bool_constant",
  [sym_int_constant] = "int_constant",
  [sym_float_constant] = "float_constant",
  [sym_plus_minus_constant] = "plus_minus_constant",
  [sym_int_lit] = "int_lit",
  [sym_decimal_lit] = "decimal_lit",
  [sym_float_lit] = "float_lit",
  [sym_inf_token] = "inf_token",
  [sym_string_constant] = "string_constant",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_source_file_repeat2] = "source_file_repeat2",
  [aux_sym_type_decl_repeat1] = "type_decl_repeat1",
  [aux_sym_type_decl_repeat2] = "type_decl_repeat2",
  [aux_sym_enum_decl_repeat1] = "enum_decl_repeat1",
  [aux_sym_union_decl_repeat1] = "union_decl_repeat1",
  [aux_sym_union_decl_repeat2] = "union_decl_repeat2",
  [aux_sym_object_repeat1] = "object_repeat1",
  [aux_sym_value_repeat1] = "value_repeat1",
  [aux_sym_rpc_decl_repeat1] = "rpc_decl_repeat1",
  [aux_sym_metadata_repeat1] = "metadata_repeat1",
  [aux_sym_full_ident_repeat1] = "full_ident_repeat1",
  [aux_sym_string_constant_repeat1] = "string_constant_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_documentation] = sym_documentation,
  [anon_sym_include] = anon_sym_include,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_namespace] = anon_sym_namespace,
  [anon_sym_attribute] = anon_sym_attribute,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [anon_sym_table] = anon_sym_table,
  [anon_sym_struct] = anon_sym_struct,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_enum] = anon_sym_enum,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_union] = anon_sym_union,
  [anon_sym_root_type] = anon_sym_root_type,
  [anon_sym_file_extension] = anon_sym_file_extension,
  [anon_sym_file_identifier] = anon_sym_file_identifier,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [anon_sym_EQ] = anon_sym_EQ,
  [anon_sym_bool] = anon_sym_bool,
  [anon_sym_byte] = anon_sym_byte,
  [anon_sym_ubyte] = anon_sym_ubyte,
  [anon_sym_short] = anon_sym_short,
  [anon_sym_ushort] = anon_sym_ushort,
  [anon_sym_int] = anon_sym_int,
  [anon_sym_uint] = anon_sym_uint,
  [anon_sym_float] = anon_sym_float,
  [anon_sym_long] = anon_sym_long,
  [anon_sym_ulong] = anon_sym_ulong,
  [anon_sym_double] = anon_sym_double,
  [anon_sym_int8] = anon_sym_int8,
  [anon_sym_uint8] = anon_sym_uint8,
  [anon_sym_int16] = anon_sym_int16,
  [anon_sym_uint16] = anon_sym_uint16,
  [anon_sym_int32] = anon_sym_int32,
  [anon_sym_uint32] = anon_sym_uint32,
  [anon_sym_int64] = anon_sym_int64,
  [anon_sym_uint64] = anon_sym_uint64,
  [anon_sym_float32] = anon_sym_float32,
  [anon_sym_float64] = anon_sym_float64,
  [anon_sym_string] = anon_sym_string,
  [anon_sym_rpc_service] = anon_sym_rpc_service,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [sym_identifier] = sym_identifier,
  [anon_sym_DOT] = anon_sym_DOT,
  [sym_plus_token] = sym_plus_token,
  [sym_minus_token] = sym_minus_token,
  [sym_true] = sym_true,
  [sym_false] = sym_false,
  [aux_sym_decimal_lit_token1] = aux_sym_decimal_lit_token1,
  [anon_sym_0] = anon_sym_0,
  [sym_hex_lit] = sym_hex_lit,
  [aux_sym_float_lit_token1] = aux_sym_float_lit_token1,
  [anon_sym_infinity] = anon_sym_infinity,
  [anon_sym_inf] = anon_sym_inf,
  [sym_nan_token] = sym_nan_token,
  [aux_sym_string_constant_token1] = aux_sym_string_constant_token1,
  [sym_escape_sequence] = sym_escape_sequence,
  [sym_comment] = sym_comment,
  [sym_source_file] = sym_source_file,
  [sym_include] = sym_include,
  [sym_namespace_decl] = sym_namespace_decl,
  [sym_attribute_decl] = sym_attribute_decl,
  [sym_type_decl] = sym_type_decl,
  [sym_enum_decl] = sym_enum_decl,
  [sym_union_decl] = sym_union_decl,
  [sym_object] = sym_object,
  [sym_root_decl] = sym_root_decl,
  [sym_file_extension_decl] = sym_file_extension_decl,
  [sym_file_identifier_decl] = sym_file_identifier_decl,
  [sym_value] = sym_value,
  [sym_enum_val_decl] = sym_enum_val_decl,
  [sym_field_decl] = sym_field_decl,
  [sym_union_field_decl] = sym_union_field_decl,
  [sym_type] = sym_type,
  [sym_rpc_decl] = sym_rpc_decl,
  [sym_rpc_method] = sym_rpc_method,
  [sym_metadata] = sym_metadata,
  [sym_field_and_value] = sym_field_and_value,
  [sym_single_value] = sym_single_value,
  [sym_full_ident] = sym_full_ident,
  [sym_scalar] = sym_scalar,
  [sym_bool_constant] = sym_bool_constant,
  [sym_int_constant] = sym_int_constant,
  [sym_float_constant] = sym_float_constant,
  [sym_plus_minus_constant] = sym_plus_minus_constant,
  [sym_int_lit] = sym_int_lit,
  [sym_decimal_lit] = sym_decimal_lit,
  [sym_float_lit] = sym_float_lit,
  [sym_inf_token] = sym_inf_token,
  [sym_string_constant] = sym_string_constant,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_source_file_repeat2] = aux_sym_source_file_repeat2,
  [aux_sym_type_decl_repeat1] = aux_sym_type_decl_repeat1,
  [aux_sym_type_decl_repeat2] = aux_sym_type_decl_repeat2,
  [aux_sym_enum_decl_repeat1] = aux_sym_enum_decl_repeat1,
  [aux_sym_union_decl_repeat1] = aux_sym_union_decl_repeat1,
  [aux_sym_union_decl_repeat2] = aux_sym_union_decl_repeat2,
  [aux_sym_object_repeat1] = aux_sym_object_repeat1,
  [aux_sym_value_repeat1] = aux_sym_value_repeat1,
  [aux_sym_rpc_decl_repeat1] = aux_sym_rpc_decl_repeat1,
  [aux_sym_metadata_repeat1] = aux_sym_metadata_repeat1,
  [aux_sym_full_ident_repeat1] = aux_sym_full_ident_repeat1,
  [aux_sym_string_constant_repeat1] = aux_sym_string_constant_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_documentation] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_include] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SEMI] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_namespace] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_attribute] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_table] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_struct] = {
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
  [anon_sym_enum] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_union] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_root_type] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_file_extension] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_file_identifier] = {
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
  [anon_sym_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_bool] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_byte] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ubyte] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_short] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ushort] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_int] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_uint] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_float] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_long] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ulong] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_double] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_int8] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_uint8] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_int16] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_uint16] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_int32] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_uint32] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_int64] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_uint64] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_float32] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_float64] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_string] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_rpc_service] = {
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
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_DOT] = {
    .visible = true,
    .named = false,
  },
  [sym_plus_token] = {
    .visible = true,
    .named = true,
  },
  [sym_minus_token] = {
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
  [aux_sym_decimal_lit_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_0] = {
    .visible = true,
    .named = false,
  },
  [sym_hex_lit] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_float_lit_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_infinity] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_inf] = {
    .visible = true,
    .named = false,
  },
  [sym_nan_token] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_string_constant_token1] = {
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
  [sym_include] = {
    .visible = true,
    .named = true,
  },
  [sym_namespace_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_attribute_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_type_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_enum_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_union_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_object] = {
    .visible = true,
    .named = true,
  },
  [sym_root_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_file_extension_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_file_identifier_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_value] = {
    .visible = true,
    .named = true,
  },
  [sym_enum_val_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_field_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_union_field_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_type] = {
    .visible = true,
    .named = true,
  },
  [sym_rpc_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_rpc_method] = {
    .visible = true,
    .named = true,
  },
  [sym_metadata] = {
    .visible = true,
    .named = true,
  },
  [sym_field_and_value] = {
    .visible = true,
    .named = true,
  },
  [sym_single_value] = {
    .visible = true,
    .named = true,
  },
  [sym_full_ident] = {
    .visible = true,
    .named = true,
  },
  [sym_scalar] = {
    .visible = true,
    .named = true,
  },
  [sym_bool_constant] = {
    .visible = true,
    .named = true,
  },
  [sym_int_constant] = {
    .visible = true,
    .named = true,
  },
  [sym_float_constant] = {
    .visible = true,
    .named = true,
  },
  [sym_plus_minus_constant] = {
    .visible = true,
    .named = true,
  },
  [sym_int_lit] = {
    .visible = true,
    .named = true,
  },
  [sym_decimal_lit] = {
    .visible = true,
    .named = true,
  },
  [sym_float_lit] = {
    .visible = true,
    .named = true,
  },
  [sym_inf_token] = {
    .visible = true,
    .named = true,
  },
  [sym_string_constant] = {
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
  [aux_sym_type_decl_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_type_decl_repeat2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_enum_decl_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_union_decl_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_union_decl_repeat2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_object_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_value_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_rpc_decl_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_metadata_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_full_ident_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_string_constant_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum ts_field_identifiers {
  field_array_type = 1,
  field_array_type_fixed_length = 2,
  field_array_value = 3,
  field_array_value_item = 4,
  field_attribute_name = 5,
  field_documentation = 6,
  field_enum_int_constant = 7,
  field_enum_key = 8,
  field_enum_name = 9,
  field_enum_type = 10,
  field_enum_val_decl = 11,
  field_field_and_value = 12,
  field_field_declaration = 13,
  field_field_key = 14,
  field_field_type = 15,
  field_field_value = 16,
  field_field_without_type = 17,
  field_file_extension_constant = 18,
  field_file_identifier_constant = 19,
  field_full_ident = 20,
  field_include_name = 21,
  field_metadata = 22,
  field_namespace_ident = 23,
  field_object_value = 24,
  field_root_type_ident = 25,
  field_rpc_method = 26,
  field_rpc_method_name = 27,
  field_rpc_name = 28,
  field_rpc_parameter = 29,
  field_rpc_return_type = 30,
  field_scalar_value = 31,
  field_single_value = 32,
  field_string_constant = 33,
  field_table_or_struct_declaration = 34,
  field_table_or_struct_name = 35,
  field_union_field_decl = 36,
  field_union_field_key = 37,
  field_union_field_value = 38,
  field_union_name = 39,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_array_type] = "array_type",
  [field_array_type_fixed_length] = "array_type_fixed_length",
  [field_array_value] = "array_value",
  [field_array_value_item] = "array_value_item",
  [field_attribute_name] = "attribute_name",
  [field_documentation] = "documentation",
  [field_enum_int_constant] = "enum_int_constant",
  [field_enum_key] = "enum_key",
  [field_enum_name] = "enum_name",
  [field_enum_type] = "enum_type",
  [field_enum_val_decl] = "enum_val_decl",
  [field_field_and_value] = "field_and_value",
  [field_field_declaration] = "field_declaration",
  [field_field_key] = "field_key",
  [field_field_type] = "field_type",
  [field_field_value] = "field_value",
  [field_field_without_type] = "field_without_type",
  [field_file_extension_constant] = "file_extension_constant",
  [field_file_identifier_constant] = "file_identifier_constant",
  [field_full_ident] = "full_ident",
  [field_include_name] = "include_name",
  [field_metadata] = "metadata",
  [field_namespace_ident] = "namespace_ident",
  [field_object_value] = "object_value",
  [field_root_type_ident] = "root_type_ident",
  [field_rpc_method] = "rpc_method",
  [field_rpc_method_name] = "rpc_method_name",
  [field_rpc_name] = "rpc_name",
  [field_rpc_parameter] = "rpc_parameter",
  [field_rpc_return_type] = "rpc_return_type",
  [field_scalar_value] = "scalar_value",
  [field_single_value] = "single_value",
  [field_string_constant] = "string_constant",
  [field_table_or_struct_declaration] = "table_or_struct_declaration",
  [field_table_or_struct_name] = "table_or_struct_name",
  [field_union_field_decl] = "union_field_decl",
  [field_union_field_key] = "union_field_key",
  [field_union_field_value] = "union_field_value",
  [field_union_name] = "union_name",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 2},
  [3] = {.index = 3, .length = 1},
  [4] = {.index = 4, .length = 1},
  [5] = {.index = 5, .length = 1},
  [6] = {.index = 6, .length = 1},
  [7] = {.index = 7, .length = 1},
  [8] = {.index = 8, .length = 1},
  [9] = {.index = 9, .length = 1},
  [10] = {.index = 10, .length = 2},
  [11] = {.index = 12, .length = 1},
  [12] = {.index = 13, .length = 1},
  [13] = {.index = 14, .length = 2},
  [14] = {.index = 16, .length = 1},
  [15] = {.index = 17, .length = 1},
  [16] = {.index = 18, .length = 1},
  [17] = {.index = 19, .length = 3},
  [18] = {.index = 22, .length = 2},
  [19] = {.index = 24, .length = 1},
  [20] = {.index = 25, .length = 3},
  [21] = {.index = 28, .length = 2},
  [22] = {.index = 30, .length = 2},
  [23] = {.index = 32, .length = 2},
  [24] = {.index = 34, .length = 3},
  [25] = {.index = 37, .length = 2},
  [26] = {.index = 39, .length = 2},
  [27] = {.index = 41, .length = 1},
  [28] = {.index = 42, .length = 1},
  [29] = {.index = 43, .length = 2},
  [30] = {.index = 45, .length = 2},
  [31] = {.index = 47, .length = 4},
  [32] = {.index = 51, .length = 1},
  [33] = {.index = 52, .length = 1},
  [34] = {.index = 53, .length = 2},
  [35] = {.index = 55, .length = 1},
  [36] = {.index = 56, .length = 3},
  [37] = {.index = 59, .length = 2},
  [38] = {.index = 61, .length = 3},
  [39] = {.index = 64, .length = 3},
  [40] = {.index = 67, .length = 3},
  [41] = {.index = 70, .length = 4},
  [42] = {.index = 74, .length = 4},
  [43] = {.index = 78, .length = 3},
  [44] = {.index = 81, .length = 3},
  [45] = {.index = 84, .length = 3},
  [46] = {.index = 87, .length = 2},
  [47] = {.index = 89, .length = 2},
  [48] = {.index = 91, .length = 3},
  [49] = {.index = 94, .length = 2},
  [50] = {.index = 96, .length = 4},
  [51] = {.index = 100, .length = 3},
  [52] = {.index = 103, .length = 4},
  [53] = {.index = 107, .length = 4},
  [54] = {.index = 111, .length = 5},
  [55] = {.index = 116, .length = 4},
  [56] = {.index = 120, .length = 4},
  [57] = {.index = 124, .length = 4},
  [58] = {.index = 128, .length = 4},
  [59] = {.index = 132, .length = 1},
  [60] = {.index = 133, .length = 1},
  [61] = {.index = 134, .length = 3},
  [62] = {.index = 137, .length = 3},
  [63] = {.index = 140, .length = 2},
  [64] = {.index = 142, .length = 2},
  [65] = {.index = 144, .length = 1},
  [66] = {.index = 145, .length = 4},
  [67] = {.index = 149, .length = 2},
  [68] = {.index = 151, .length = 3},
  [69] = {.index = 154, .length = 4},
  [70] = {.index = 158, .length = 5},
  [71] = {.index = 163, .length = 4},
  [72] = {.index = 167, .length = 5},
  [73] = {.index = 172, .length = 5},
  [74] = {.index = 177, .length = 5},
  [75] = {.index = 182, .length = 3},
  [76] = {.index = 185, .length = 4},
  [77] = {.index = 189, .length = 3},
  [78] = {.index = 192, .length = 3},
  [79] = {.index = 195, .length = 5},
  [80] = {.index = 200, .length = 5},
  [81] = {.index = 205, .length = 5},
  [82] = {.index = 210, .length = 6},
  [83] = {.index = 216, .length = 3},
  [84] = {.index = 219, .length = 4},
  [85] = {.index = 223, .length = 4},
  [86] = {.index = 227, .length = 4},
  [87] = {.index = 231, .length = 3},
  [88] = {.index = 234, .length = 6},
  [89] = {.index = 240, .length = 1},
  [90] = {.index = 241, .length = 5},
  [91] = {.index = 246, .length = 2},
  [92] = {.index = 248, .length = 5},
  [93] = {.index = 253, .length = 4},
  [94] = {.index = 257, .length = 4},
  [95] = {.index = 261, .length = 5},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_documentation, 0},
  [1] =
    {field_documentation, 0, .inherited = true},
    {field_documentation, 1, .inherited = true},
  [3] =
    {field_include_name, 1},
  [4] =
    {field_namespace_ident, 1},
  [5] =
    {field_attribute_name, 1},
  [6] =
    {field_documentation, 1, .inherited = true},
  [7] =
    {field_root_type_ident, 1},
  [8] =
    {field_file_extension_constant, 1},
  [9] =
    {field_file_identifier_constant, 1},
  [10] =
    {field_table_or_struct_declaration, 0},
    {field_table_or_struct_name, 1},
  [12] =
    {field_field_declaration, 0},
  [13] =
    {field_field_key, 0},
  [14] =
    {field_documentation, 1, .inherited = true},
    {field_documentation, 2, .inherited = true},
  [16] =
    {field_full_ident, 0},
  [17] =
    {field_rpc_name, 1},
  [18] =
    {field_attribute_name, 2},
  [19] =
    {field_field_declaration, 3, .inherited = true},
    {field_table_or_struct_declaration, 0},
    {field_table_or_struct_name, 1},
  [22] =
    {field_field_declaration, 0, .inherited = true},
    {field_field_declaration, 1, .inherited = true},
  [24] =
    {field_field_and_value, 1},
  [25] =
    {field_metadata, 2},
    {field_table_or_struct_declaration, 0},
    {field_table_or_struct_name, 1},
  [28] =
    {field_union_field_decl, 3},
    {field_union_name, 1},
  [30] =
    {field_field_without_type, 3},
    {field_union_name, 1},
  [32] =
    {field_rpc_method, 3},
    {field_rpc_name, 1},
  [34] =
    {field_documentation, 0, .inherited = true},
    {field_table_or_struct_declaration, 1},
    {field_table_or_struct_name, 2},
  [37] =
    {field_documentation, 0, .inherited = true},
    {field_rpc_name, 2},
  [39] =
    {field_field_key, 0},
    {field_field_value, 2},
  [41] =
    {field_scalar_value, 0},
  [42] =
    {field_string_constant, 0},
  [43] =
    {field_field_and_value, 1},
    {field_field_and_value, 2, .inherited = true},
  [45] =
    {field_field_and_value, 0, .inherited = true},
    {field_field_and_value, 1, .inherited = true},
  [47] =
    {field_field_declaration, 4, .inherited = true},
    {field_metadata, 2},
    {field_table_or_struct_declaration, 0},
    {field_table_or_struct_name, 1},
  [51] =
    {field_array_type, 1},
  [52] =
    {field_enum_key, 0},
  [53] =
    {field_union_field_key, 0},
    {field_union_field_value, 2},
  [55] =
    {field_union_field_decl, 1},
  [56] =
    {field_union_field_decl, 3},
    {field_union_field_decl, 4, .inherited = true},
    {field_union_name, 1},
  [59] =
    {field_union_field_decl, 0, .inherited = true},
    {field_union_field_decl, 1, .inherited = true},
  [61] =
    {field_field_without_type, 3},
    {field_field_without_type, 4},
    {field_union_name, 1},
  [64] =
    {field_metadata, 2},
    {field_union_field_decl, 4},
    {field_union_name, 1},
  [67] =
    {field_field_without_type, 4},
    {field_metadata, 2},
    {field_union_name, 1},
  [70] =
    {field_documentation, 0, .inherited = true},
    {field_field_declaration, 4, .inherited = true},
    {field_table_or_struct_declaration, 1},
    {field_table_or_struct_name, 2},
  [74] =
    {field_documentation, 0, .inherited = true},
    {field_metadata, 3},
    {field_table_or_struct_declaration, 1},
    {field_table_or_struct_name, 2},
  [78] =
    {field_documentation, 0, .inherited = true},
    {field_union_field_decl, 4},
    {field_union_name, 2},
  [81] =
    {field_documentation, 0, .inherited = true},
    {field_field_without_type, 4},
    {field_union_name, 2},
  [84] =
    {field_documentation, 0, .inherited = true},
    {field_rpc_method, 4},
    {field_rpc_name, 2},
  [87] =
    {field_field_key, 0},
    {field_field_type, 2},
  [89] =
    {field_enum_key, 0},
    {field_metadata, 1},
  [91] =
    {field_enum_name, 1},
    {field_enum_type, 3},
    {field_enum_val_decl, 5},
  [94] =
    {field_documentation, 0, .inherited = true},
    {field_enum_key, 1},
  [96] =
    {field_field_without_type, 3},
    {field_field_without_type, 4},
    {field_field_without_type, 5},
    {field_union_name, 1},
  [100] =
    {field_documentation, 0, .inherited = true},
    {field_union_field_key, 1},
    {field_union_field_value, 3},
  [103] =
    {field_metadata, 2},
    {field_union_field_decl, 4},
    {field_union_field_decl, 5, .inherited = true},
    {field_union_name, 1},
  [107] =
    {field_field_without_type, 4},
    {field_field_without_type, 5},
    {field_metadata, 2},
    {field_union_name, 1},
  [111] =
    {field_documentation, 0, .inherited = true},
    {field_field_declaration, 5, .inherited = true},
    {field_metadata, 3},
    {field_table_or_struct_declaration, 1},
    {field_table_or_struct_name, 2},
  [116] =
    {field_documentation, 0, .inherited = true},
    {field_union_field_decl, 4},
    {field_union_field_decl, 5, .inherited = true},
    {field_union_name, 2},
  [120] =
    {field_documentation, 0, .inherited = true},
    {field_field_without_type, 4},
    {field_field_without_type, 5},
    {field_union_name, 2},
  [124] =
    {field_documentation, 0, .inherited = true},
    {field_metadata, 3},
    {field_union_field_decl, 5},
    {field_union_name, 2},
  [128] =
    {field_documentation, 0, .inherited = true},
    {field_field_without_type, 5},
    {field_metadata, 3},
    {field_union_name, 2},
  [132] =
    {field_object_value, 0},
  [133] =
    {field_single_value, 0},
  [134] =
    {field_field_key, 0},
    {field_field_type, 2},
    {field_metadata, 3},
  [137] =
    {field_documentation, 0, .inherited = true},
    {field_field_key, 1},
    {field_field_type, 3},
  [140] =
    {field_array_type, 1},
    {field_array_type_fixed_length, 3},
  [142] =
    {field_enum_int_constant, 2},
    {field_enum_key, 0},
  [144] =
    {field_enum_val_decl, 1},
  [145] =
    {field_enum_name, 1},
    {field_enum_type, 3},
    {field_enum_val_decl, 5},
    {field_enum_val_decl, 6, .inherited = true},
  [149] =
    {field_enum_val_decl, 0, .inherited = true},
    {field_enum_val_decl, 1, .inherited = true},
  [151] =
    {field_documentation, 0, .inherited = true},
    {field_enum_key, 1},
    {field_metadata, 2},
  [154] =
    {field_enum_name, 1},
    {field_enum_type, 3},
    {field_enum_val_decl, 6},
    {field_metadata, 4},
  [158] =
    {field_field_without_type, 4},
    {field_field_without_type, 5},
    {field_field_without_type, 6},
    {field_metadata, 2},
    {field_union_name, 1},
  [163] =
    {field_documentation, 0, .inherited = true},
    {field_enum_name, 2},
    {field_enum_type, 4},
    {field_enum_val_decl, 6},
  [167] =
    {field_documentation, 0, .inherited = true},
    {field_field_without_type, 4},
    {field_field_without_type, 5},
    {field_field_without_type, 6},
    {field_union_name, 2},
  [172] =
    {field_documentation, 0, .inherited = true},
    {field_metadata, 3},
    {field_union_field_decl, 5},
    {field_union_field_decl, 6, .inherited = true},
    {field_union_name, 2},
  [177] =
    {field_documentation, 0, .inherited = true},
    {field_field_without_type, 5},
    {field_field_without_type, 6},
    {field_metadata, 3},
    {field_union_name, 2},
  [182] =
    {field_field_key, 0},
    {field_field_type, 2},
    {field_field_value, 4},
  [185] =
    {field_documentation, 0, .inherited = true},
    {field_field_key, 1},
    {field_field_type, 3},
    {field_metadata, 4},
  [189] =
    {field_enum_int_constant, 2},
    {field_enum_key, 0},
    {field_metadata, 3},
  [192] =
    {field_documentation, 0, .inherited = true},
    {field_enum_int_constant, 3},
    {field_enum_key, 1},
  [195] =
    {field_enum_name, 1},
    {field_enum_type, 3},
    {field_enum_val_decl, 6},
    {field_enum_val_decl, 7, .inherited = true},
    {field_metadata, 4},
  [200] =
    {field_documentation, 0, .inherited = true},
    {field_enum_name, 2},
    {field_enum_type, 4},
    {field_enum_val_decl, 6},
    {field_enum_val_decl, 7, .inherited = true},
  [205] =
    {field_documentation, 0, .inherited = true},
    {field_enum_name, 2},
    {field_enum_type, 4},
    {field_enum_val_decl, 7},
    {field_metadata, 5},
  [210] =
    {field_documentation, 0, .inherited = true},
    {field_field_without_type, 5},
    {field_field_without_type, 6},
    {field_field_without_type, 7},
    {field_metadata, 3},
    {field_union_name, 2},
  [216] =
    {field_array_value, 0},
    {field_array_value, 2},
    {field_array_value_item, 1},
  [219] =
    {field_field_key, 0},
    {field_field_type, 2},
    {field_field_value, 4},
    {field_metadata, 5},
  [223] =
    {field_documentation, 0, .inherited = true},
    {field_field_key, 1},
    {field_field_type, 3},
    {field_field_value, 5},
  [227] =
    {field_documentation, 0, .inherited = true},
    {field_enum_int_constant, 3},
    {field_enum_key, 1},
    {field_metadata, 4},
  [231] =
    {field_rpc_method_name, 0},
    {field_rpc_parameter, 2},
    {field_rpc_return_type, 5},
  [234] =
    {field_documentation, 0, .inherited = true},
    {field_enum_name, 2},
    {field_enum_type, 4},
    {field_enum_val_decl, 7},
    {field_enum_val_decl, 8, .inherited = true},
    {field_metadata, 5},
  [240] =
    {field_array_value_item, 1},
  [241] =
    {field_array_value, 0},
    {field_array_value, 2},
    {field_array_value, 3},
    {field_array_value_item, 1},
    {field_array_value_item, 2, .inherited = true},
  [246] =
    {field_array_value_item, 0, .inherited = true},
    {field_array_value_item, 1, .inherited = true},
  [248] =
    {field_documentation, 0, .inherited = true},
    {field_field_key, 1},
    {field_field_type, 3},
    {field_field_value, 5},
    {field_metadata, 6},
  [253] =
    {field_metadata, 6},
    {field_rpc_method_name, 0},
    {field_rpc_parameter, 2},
    {field_rpc_return_type, 5},
  [257] =
    {field_documentation, 0, .inherited = true},
    {field_rpc_method_name, 1},
    {field_rpc_parameter, 3},
    {field_rpc_return_type, 6},
  [261] =
    {field_documentation, 0, .inherited = true},
    {field_metadata, 7},
    {field_rpc_method_name, 1},
    {field_rpc_parameter, 3},
    {field_rpc_return_type, 6},
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
  [164] = 130,
  [165] = 165,
  [166] = 166,
  [167] = 138,
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
  [188] = 24,
  [189] = 22,
  [190] = 23,
  [191] = 29,
  [192] = 192,
  [193] = 193,
  [194] = 194,
  [195] = 195,
  [196] = 196,
  [197] = 195,
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
  [266] = 98,
  [267] = 267,
  [268] = 206,
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
  [290] = 102,
  [291] = 291,
  [292] = 292,
  [293] = 293,
  [294] = 294,
  [295] = 295,
  [296] = 296,
  [297] = 297,
  [298] = 298,
  [299] = 299,
  [300] = 300,
  [301] = 301,
  [302] = 302,
  [303] = 303,
  [304] = 304,
  [305] = 305,
  [306] = 306,
  [307] = 307,
  [308] = 308,
  [309] = 309,
  [310] = 310,
  [311] = 311,
  [312] = 312,
  [313] = 313,
  [314] = 314,
  [315] = 315,
  [316] = 316,
  [317] = 317,
  [318] = 318,
  [319] = 319,
  [320] = 320,
  [321] = 321,
  [322] = 322,
  [323] = 323,
  [324] = 324,
  [325] = 325,
  [326] = 326,
  [327] = 327,
  [328] = 328,
  [329] = 329,
  [330] = 330,
  [331] = 331,
  [332] = 332,
  [333] = 333,
  [334] = 334,
  [335] = 335,
  [336] = 336,
  [337] = 337,
  [338] = 338,
  [339] = 339,
  [340] = 340,
  [341] = 341,
  [342] = 342,
  [343] = 343,
  [344] = 344,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(152);
      ADVANCE_MAP(
        '"', 158,
        '(', 218,
        ')', 219,
        '+', 286,
        ',', 165,
        '-', 287,
        '.', 285,
        '/', 4,
        '0', 293,
        ':', 164,
        ';', 155,
        '=', 172,
        '[', 170,
        '\\', 18,
        ']', 171,
        'a', 119,
        'b', 91,
        'd', 89,
        'e', 82,
        'f', 22,
        'i', 78,
        'l', 92,
        'n', 23,
        'r', 96,
        's', 60,
        't', 24,
        'u', 27,
        '{', 161,
        '}', 162,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(150);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(292);
      END_STATE();
    case 1:
      if (lookahead == '"') ADVANCE(158);
      if (lookahead == '/') ADVANCE(304);
      if (lookahead == '\\') ADVANCE(18);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(307);
      if (lookahead != 0) ADVANCE(308);
      END_STATE();
    case 2:
      if (lookahead == '"') ADVANCE(158);
      if (lookahead == '/') ADVANCE(5);
      if (lookahead == '}') ADVANCE(162);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(2);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 3:
      ADVANCE_MAP(
        '(', 218,
        ')', 219,
        ',', 165,
        '.', 284,
        '/', 5,
        ':', 164,
        ';', 155,
        '=', 172,
        '[', 170,
        ']', 171,
        'b', 262,
        'd', 258,
        'f', 248,
        'i', 255,
        'l', 263,
        's', 242,
        'u', 231,
        '{', 161,
        '}', 162,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(3);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 4:
      if (lookahead == '*') ADVANCE(7);
      if (lookahead == '/') ADVANCE(313);
      END_STATE();
    case 5:
      if (lookahead == '*') ADVANCE(7);
      if (lookahead == '/') ADVANCE(314);
      END_STATE();
    case 6:
      if (lookahead == '*') ADVANCE(6);
      if (lookahead == '/') ADVANCE(312);
      if (lookahead != 0) ADVANCE(7);
      END_STATE();
    case 7:
      if (lookahead == '*') ADVANCE(6);
      if (lookahead != 0) ADVANCE(7);
      END_STATE();
    case 8:
      if (lookahead == '.') ADVANCE(295);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(138);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(8);
      END_STATE();
    case 9:
      if (lookahead == '/') ADVANCE(4);
      if (lookahead == '}') ADVANCE(162);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(9);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 10:
      if (lookahead == '2') ADVANCE(203);
      END_STATE();
    case 11:
      if (lookahead == '2') ADVANCE(205);
      END_STATE();
    case 12:
      if (lookahead == '2') ADVANCE(211);
      END_STATE();
    case 13:
      if (lookahead == '4') ADVANCE(207);
      END_STATE();
    case 14:
      if (lookahead == '4') ADVANCE(209);
      END_STATE();
    case 15:
      if (lookahead == '4') ADVANCE(213);
      END_STATE();
    case 16:
      if (lookahead == '6') ADVANCE(199);
      END_STATE();
    case 17:
      if (lookahead == '6') ADVANCE(201);
      END_STATE();
    case 18:
      if (lookahead == 'U') ADVANCE(149);
      if (lookahead == 'u') ADVANCE(145);
      if (lookahead == 'x') ADVANCE(143);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(311);
      if (lookahead != 0) ADVANCE(309);
      END_STATE();
    case 19:
      if (lookahead == '_') ADVANCE(44);
      END_STATE();
    case 20:
      if (lookahead == '_') ADVANCE(121);
      END_STATE();
    case 21:
      if (lookahead == '_') ADVANCE(111);
      END_STATE();
    case 22:
      if (lookahead == 'a') ADVANCE(70);
      if (lookahead == 'i') ADVANCE(72);
      if (lookahead == 'l') ADVANCE(90);
      END_STATE();
    case 23:
      if (lookahead == 'a') ADVANCE(77);
      END_STATE();
    case 24:
      if (lookahead == 'a') ADVANCE(29);
      if (lookahead == 'r') ADVANCE(130);
      END_STATE();
    case 25:
      if (lookahead == 'a') ADVANCE(34);
      END_STATE();
    case 26:
      if (lookahead == 'a') ADVANCE(115);
      END_STATE();
    case 27:
      if (lookahead == 'b') ADVANCE(137);
      if (lookahead == 'i') ADVANCE(87);
      if (lookahead == 'l') ADVANCE(97);
      if (lookahead == 'n') ADVANCE(68);
      if (lookahead == 's') ADVANCE(61);
      END_STATE();
    case 28:
      if (lookahead == 'b') ADVANCE(131);
      END_STATE();
    case 29:
      if (lookahead == 'b') ADVANCE(74);
      END_STATE();
    case 30:
      if (lookahead == 'b') ADVANCE(75);
      END_STATE();
    case 31:
      if (lookahead == 'c') ADVANCE(21);
      END_STATE();
    case 32:
      if (lookahead == 'c') ADVANCE(73);
      if (lookahead == 'f') ADVANCE(300);
      if (lookahead == 't') ADVANCE(183);
      END_STATE();
    case 33:
      if (lookahead == 'c') ADVANCE(117);
      END_STATE();
    case 34:
      if (lookahead == 'c') ADVANCE(47);
      END_STATE();
    case 35:
      if (lookahead == 'c') ADVANCE(49);
      END_STATE();
    case 36:
      if (lookahead == 'd') ADVANCE(45);
      END_STATE();
    case 37:
      if (lookahead == 'd') ADVANCE(55);
      END_STATE();
    case 38:
      if (lookahead == 'e') ADVANCE(175);
      END_STATE();
    case 39:
      if (lookahead == 'e') ADVANCE(288);
      END_STATE();
    case 40:
      if (lookahead == 'e') ADVANCE(290);
      END_STATE();
    case 41:
      if (lookahead == 'e') ADVANCE(159);
      END_STATE();
    case 42:
      if (lookahead == 'e') ADVANCE(177);
      END_STATE();
    case 43:
      if (lookahead == 'e') ADVANCE(193);
      END_STATE();
    case 44:
      if (lookahead == 'e') ADVANCE(134);
      if (lookahead == 'i') ADVANCE(37);
      END_STATE();
    case 45:
      if (lookahead == 'e') ADVANCE(154);
      END_STATE();
    case 46:
      if (lookahead == 'e') ADVANCE(157);
      END_STATE();
    case 47:
      if (lookahead == 'e') ADVANCE(156);
      END_STATE();
    case 48:
      if (lookahead == 'e') ADVANCE(167);
      END_STATE();
    case 49:
      if (lookahead == 'e') ADVANCE(217);
      END_STATE();
    case 50:
      if (lookahead == 'e') ADVANCE(109);
      END_STATE();
    case 51:
      if (lookahead == 'e') ADVANCE(19);
      END_STATE();
    case 52:
      if (lookahead == 'e') ADVANCE(104);
      END_STATE();
    case 53:
      if (lookahead == 'e') ADVANCE(105);
      END_STATE();
    case 54:
      if (lookahead == 'e') ADVANCE(85);
      END_STATE();
    case 55:
      if (lookahead == 'e') ADVANCE(88);
      END_STATE();
    case 56:
      if (lookahead == 'f') ADVANCE(66);
      END_STATE();
    case 57:
      if (lookahead == 'g') ADVANCE(189);
      END_STATE();
    case 58:
      if (lookahead == 'g') ADVANCE(191);
      END_STATE();
    case 59:
      if (lookahead == 'g') ADVANCE(215);
      END_STATE();
    case 60:
      if (lookahead == 'h') ADVANCE(94);
      if (lookahead == 't') ADVANCE(103);
      END_STATE();
    case 61:
      if (lookahead == 'h') ADVANCE(100);
      END_STATE();
    case 62:
      if (lookahead == 'i') ADVANCE(56);
      END_STATE();
    case 63:
      if (lookahead == 'i') ADVANCE(28);
      END_STATE();
    case 64:
      if (lookahead == 'i') ADVANCE(86);
      if (lookahead == 'u') ADVANCE(33);
      END_STATE();
    case 65:
      if (lookahead == 'i') ADVANCE(122);
      END_STATE();
    case 66:
      if (lookahead == 'i') ADVANCE(53);
      END_STATE();
    case 67:
      if (lookahead == 'i') ADVANCE(35);
      END_STATE();
    case 68:
      if (lookahead == 'i') ADVANCE(98);
      END_STATE();
    case 69:
      if (lookahead == 'i') ADVANCE(99);
      END_STATE();
    case 70:
      if (lookahead == 'l') ADVANCE(110);
      END_STATE();
    case 71:
      if (lookahead == 'l') ADVANCE(173);
      END_STATE();
    case 72:
      if (lookahead == 'l') ADVANCE(51);
      END_STATE();
    case 73:
      if (lookahead == 'l') ADVANCE(129);
      END_STATE();
    case 74:
      if (lookahead == 'l') ADVANCE(41);
      END_STATE();
    case 75:
      if (lookahead == 'l') ADVANCE(43);
      END_STATE();
    case 76:
      if (lookahead == 'm') ADVANCE(163);
      END_STATE();
    case 77:
      if (lookahead == 'm') ADVANCE(50);
      if (lookahead == 'n') ADVANCE(301);
      END_STATE();
    case 78:
      if (lookahead == 'n') ADVANCE(32);
      END_STATE();
    case 79:
      if (lookahead == 'n') ADVANCE(57);
      END_STATE();
    case 80:
      if (lookahead == 'n') ADVANCE(166);
      END_STATE();
    case 81:
      if (lookahead == 'n') ADVANCE(168);
      END_STATE();
    case 82:
      if (lookahead == 'n') ADVANCE(128);
      END_STATE();
    case 83:
      if (lookahead == 'n') ADVANCE(58);
      END_STATE();
    case 84:
      if (lookahead == 'n') ADVANCE(65);
      END_STATE();
    case 85:
      if (lookahead == 'n') ADVANCE(112);
      END_STATE();
    case 86:
      if (lookahead == 'n') ADVANCE(59);
      END_STATE();
    case 87:
      if (lookahead == 'n') ADVANCE(114);
      END_STATE();
    case 88:
      if (lookahead == 'n') ADVANCE(124);
      END_STATE();
    case 89:
      if (lookahead == 'o') ADVANCE(132);
      END_STATE();
    case 90:
      if (lookahead == 'o') ADVANCE(26);
      END_STATE();
    case 91:
      if (lookahead == 'o') ADVANCE(93);
      if (lookahead == 'y') ADVANCE(113);
      END_STATE();
    case 92:
      if (lookahead == 'o') ADVANCE(79);
      END_STATE();
    case 93:
      if (lookahead == 'o') ADVANCE(71);
      END_STATE();
    case 94:
      if (lookahead == 'o') ADVANCE(107);
      END_STATE();
    case 95:
      if (lookahead == 'o') ADVANCE(123);
      END_STATE();
    case 96:
      if (lookahead == 'o') ADVANCE(95);
      if (lookahead == 'p') ADVANCE(31);
      END_STATE();
    case 97:
      if (lookahead == 'o') ADVANCE(83);
      END_STATE();
    case 98:
      if (lookahead == 'o') ADVANCE(80);
      END_STATE();
    case 99:
      if (lookahead == 'o') ADVANCE(81);
      END_STATE();
    case 100:
      if (lookahead == 'o') ADVANCE(108);
      END_STATE();
    case 101:
      if (lookahead == 'p') ADVANCE(25);
      END_STATE();
    case 102:
      if (lookahead == 'p') ADVANCE(48);
      END_STATE();
    case 103:
      if (lookahead == 'r') ADVANCE(64);
      END_STATE();
    case 104:
      if (lookahead == 'r') ADVANCE(133);
      END_STATE();
    case 105:
      if (lookahead == 'r') ADVANCE(169);
      END_STATE();
    case 106:
      if (lookahead == 'r') ADVANCE(63);
      END_STATE();
    case 107:
      if (lookahead == 'r') ADVANCE(116);
      END_STATE();
    case 108:
      if (lookahead == 'r') ADVANCE(118);
      END_STATE();
    case 109:
      if (lookahead == 's') ADVANCE(101);
      END_STATE();
    case 110:
      if (lookahead == 's') ADVANCE(40);
      END_STATE();
    case 111:
      if (lookahead == 's') ADVANCE(52);
      END_STATE();
    case 112:
      if (lookahead == 's') ADVANCE(69);
      END_STATE();
    case 113:
      if (lookahead == 't') ADVANCE(38);
      END_STATE();
    case 114:
      if (lookahead == 't') ADVANCE(185);
      END_STATE();
    case 115:
      if (lookahead == 't') ADVANCE(187);
      END_STATE();
    case 116:
      if (lookahead == 't') ADVANCE(179);
      END_STATE();
    case 117:
      if (lookahead == 't') ADVANCE(160);
      END_STATE();
    case 118:
      if (lookahead == 't') ADVANCE(181);
      END_STATE();
    case 119:
      if (lookahead == 't') ADVANCE(120);
      END_STATE();
    case 120:
      if (lookahead == 't') ADVANCE(106);
      END_STATE();
    case 121:
      if (lookahead == 't') ADVANCE(136);
      END_STATE();
    case 122:
      if (lookahead == 't') ADVANCE(135);
      END_STATE();
    case 123:
      if (lookahead == 't') ADVANCE(20);
      END_STATE();
    case 124:
      if (lookahead == 't') ADVANCE(62);
      END_STATE();
    case 125:
      if (lookahead == 't') ADVANCE(42);
      END_STATE();
    case 126:
      if (lookahead == 't') ADVANCE(46);
      END_STATE();
    case 127:
      if (lookahead == 't') ADVANCE(54);
      END_STATE();
    case 128:
      if (lookahead == 'u') ADVANCE(76);
      END_STATE();
    case 129:
      if (lookahead == 'u') ADVANCE(36);
      END_STATE();
    case 130:
      if (lookahead == 'u') ADVANCE(39);
      END_STATE();
    case 131:
      if (lookahead == 'u') ADVANCE(126);
      END_STATE();
    case 132:
      if (lookahead == 'u') ADVANCE(30);
      END_STATE();
    case 133:
      if (lookahead == 'v') ADVANCE(67);
      END_STATE();
    case 134:
      if (lookahead == 'x') ADVANCE(127);
      END_STATE();
    case 135:
      if (lookahead == 'y') ADVANCE(297);
      END_STATE();
    case 136:
      if (lookahead == 'y') ADVANCE(102);
      END_STATE();
    case 137:
      if (lookahead == 'y') ADVANCE(125);
      END_STATE();
    case 138:
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(140);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(296);
      END_STATE();
    case 139:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(295);
      END_STATE();
    case 140:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(296);
      END_STATE();
    case 141:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(309);
      END_STATE();
    case 142:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(294);
      END_STATE();
    case 143:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(141);
      END_STATE();
    case 144:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(143);
      END_STATE();
    case 145:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(144);
      END_STATE();
    case 146:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(145);
      END_STATE();
    case 147:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(146);
      END_STATE();
    case 148:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(147);
      END_STATE();
    case 149:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(148);
      END_STATE();
    case 150:
      if (eof) ADVANCE(152);
      ADVANCE_MAP(
        '"', 158,
        '(', 218,
        ')', 219,
        '+', 286,
        ',', 165,
        '-', 287,
        '.', 285,
        '/', 4,
        '0', 293,
        ':', 164,
        ';', 155,
        '=', 172,
        '[', 170,
        ']', 171,
        'a', 119,
        'b', 91,
        'd', 89,
        'e', 82,
        'f', 22,
        'i', 78,
        'l', 92,
        'n', 23,
        'r', 96,
        's', 60,
        't', 24,
        'u', 27,
        '{', 161,
        '}', 162,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(150);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(292);
      END_STATE();
    case 151:
      if (eof) ADVANCE(152);
      ADVANCE_MAP(
        '"', 158,
        '(', 218,
        ')', 219,
        '+', 286,
        ',', 165,
        '-', 287,
        '.', 139,
        '/', 5,
        '0', 293,
        ':', 164,
        ';', 155,
        '=', 172,
        '[', 170,
        ']', 171,
        'f', 228,
        'i', 250,
        'n', 229,
        't', 266,
        '{', 161,
        '}', 162,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(151);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(292);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 152:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 153:
      ACCEPT_TOKEN(sym_documentation);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(153);
      END_STATE();
    case 154:
      ACCEPT_TOKEN(anon_sym_include);
      END_STATE();
    case 155:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 156:
      ACCEPT_TOKEN(anon_sym_namespace);
      END_STATE();
    case 157:
      ACCEPT_TOKEN(anon_sym_attribute);
      END_STATE();
    case 158:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 159:
      ACCEPT_TOKEN(anon_sym_table);
      END_STATE();
    case 160:
      ACCEPT_TOKEN(anon_sym_struct);
      END_STATE();
    case 161:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 162:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 163:
      ACCEPT_TOKEN(anon_sym_enum);
      END_STATE();
    case 164:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 165:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 166:
      ACCEPT_TOKEN(anon_sym_union);
      END_STATE();
    case 167:
      ACCEPT_TOKEN(anon_sym_root_type);
      END_STATE();
    case 168:
      ACCEPT_TOKEN(anon_sym_file_extension);
      END_STATE();
    case 169:
      ACCEPT_TOKEN(anon_sym_file_identifier);
      END_STATE();
    case 170:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 171:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 172:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 173:
      ACCEPT_TOKEN(anon_sym_bool);
      END_STATE();
    case 174:
      ACCEPT_TOKEN(anon_sym_bool);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 175:
      ACCEPT_TOKEN(anon_sym_byte);
      END_STATE();
    case 176:
      ACCEPT_TOKEN(anon_sym_byte);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 177:
      ACCEPT_TOKEN(anon_sym_ubyte);
      END_STATE();
    case 178:
      ACCEPT_TOKEN(anon_sym_ubyte);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 179:
      ACCEPT_TOKEN(anon_sym_short);
      END_STATE();
    case 180:
      ACCEPT_TOKEN(anon_sym_short);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 181:
      ACCEPT_TOKEN(anon_sym_ushort);
      END_STATE();
    case 182:
      ACCEPT_TOKEN(anon_sym_ushort);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 183:
      ACCEPT_TOKEN(anon_sym_int);
      if (lookahead == '1') ADVANCE(16);
      if (lookahead == '3') ADVANCE(10);
      if (lookahead == '6') ADVANCE(13);
      if (lookahead == '8') ADVANCE(195);
      END_STATE();
    case 184:
      ACCEPT_TOKEN(anon_sym_int);
      if (lookahead == '1') ADVANCE(226);
      if (lookahead == '3') ADVANCE(220);
      if (lookahead == '6') ADVANCE(223);
      if (lookahead == '8') ADVANCE(196);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 185:
      ACCEPT_TOKEN(anon_sym_uint);
      if (lookahead == '1') ADVANCE(17);
      if (lookahead == '3') ADVANCE(11);
      if (lookahead == '6') ADVANCE(14);
      if (lookahead == '8') ADVANCE(197);
      END_STATE();
    case 186:
      ACCEPT_TOKEN(anon_sym_uint);
      if (lookahead == '1') ADVANCE(227);
      if (lookahead == '3') ADVANCE(221);
      if (lookahead == '6') ADVANCE(224);
      if (lookahead == '8') ADVANCE(198);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 187:
      ACCEPT_TOKEN(anon_sym_float);
      if (lookahead == '3') ADVANCE(12);
      if (lookahead == '6') ADVANCE(15);
      END_STATE();
    case 188:
      ACCEPT_TOKEN(anon_sym_float);
      if (lookahead == '3') ADVANCE(222);
      if (lookahead == '6') ADVANCE(225);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 189:
      ACCEPT_TOKEN(anon_sym_long);
      END_STATE();
    case 190:
      ACCEPT_TOKEN(anon_sym_long);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 191:
      ACCEPT_TOKEN(anon_sym_ulong);
      END_STATE();
    case 192:
      ACCEPT_TOKEN(anon_sym_ulong);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 193:
      ACCEPT_TOKEN(anon_sym_double);
      END_STATE();
    case 194:
      ACCEPT_TOKEN(anon_sym_double);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 195:
      ACCEPT_TOKEN(anon_sym_int8);
      END_STATE();
    case 196:
      ACCEPT_TOKEN(anon_sym_int8);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 197:
      ACCEPT_TOKEN(anon_sym_uint8);
      END_STATE();
    case 198:
      ACCEPT_TOKEN(anon_sym_uint8);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 199:
      ACCEPT_TOKEN(anon_sym_int16);
      END_STATE();
    case 200:
      ACCEPT_TOKEN(anon_sym_int16);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 201:
      ACCEPT_TOKEN(anon_sym_uint16);
      END_STATE();
    case 202:
      ACCEPT_TOKEN(anon_sym_uint16);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 203:
      ACCEPT_TOKEN(anon_sym_int32);
      END_STATE();
    case 204:
      ACCEPT_TOKEN(anon_sym_int32);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 205:
      ACCEPT_TOKEN(anon_sym_uint32);
      END_STATE();
    case 206:
      ACCEPT_TOKEN(anon_sym_uint32);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 207:
      ACCEPT_TOKEN(anon_sym_int64);
      END_STATE();
    case 208:
      ACCEPT_TOKEN(anon_sym_int64);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 209:
      ACCEPT_TOKEN(anon_sym_uint64);
      END_STATE();
    case 210:
      ACCEPT_TOKEN(anon_sym_uint64);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 211:
      ACCEPT_TOKEN(anon_sym_float32);
      END_STATE();
    case 212:
      ACCEPT_TOKEN(anon_sym_float32);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 213:
      ACCEPT_TOKEN(anon_sym_float64);
      END_STATE();
    case 214:
      ACCEPT_TOKEN(anon_sym_float64);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 215:
      ACCEPT_TOKEN(anon_sym_string);
      END_STATE();
    case 216:
      ACCEPT_TOKEN(anon_sym_string);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 217:
      ACCEPT_TOKEN(anon_sym_rpc_service);
      END_STATE();
    case 218:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 219:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 220:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '2') ADVANCE(204);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 221:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '2') ADVANCE(206);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 222:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '2') ADVANCE(212);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 223:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '4') ADVANCE(208);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 224:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '4') ADVANCE(210);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 225:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '4') ADVANCE(214);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 226:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '6') ADVANCE(200);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 227:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '6') ADVANCE(202);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 228:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(246);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 229:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(251);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 230:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(274);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 231:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'b') ADVANCE(282);
      if (lookahead == 'i') ADVANCE(257);
      if (lookahead == 'l') ADVANCE(264);
      if (lookahead == 's') ADVANCE(243);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 232:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'b') ADVANCE(249);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 233:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(289);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 234:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(291);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 235:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(176);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 236:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(178);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 237:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(194);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 238:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(299);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 239:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(190);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 240:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(192);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 241:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(216);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 242:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'h') ADVANCE(260);
      if (lookahead == 't') ADVANCE(267);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 243:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'h') ADVANCE(265);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 244:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(271);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 245:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(256);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 246:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(270);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 247:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(174);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 248:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(259);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 249:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(237);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 250:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(238);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 251:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(302);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 252:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(244);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 253:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(239);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 254:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(240);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 255:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(272);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 256:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(241);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 257:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(273);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 258:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(280);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 259:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(230);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 260:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(268);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 261:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(247);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 262:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(261);
      if (lookahead == 'y') ADVANCE(277);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 263:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(253);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 264:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(254);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 265:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(269);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 266:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(279);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 267:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(245);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 268:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(275);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 269:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(276);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 270:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(234);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 271:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(281);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 272:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(184);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 273:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(186);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 274:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(188);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 275:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(180);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 276:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(182);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 277:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(235);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 278:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(236);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 279:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(233);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 280:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(232);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 281:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'y') ADVANCE(298);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 282:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'y') ADVANCE(278);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 283:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 284:
      ACCEPT_TOKEN(anon_sym_DOT);
      END_STATE();
    case 285:
      ACCEPT_TOKEN(anon_sym_DOT);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(295);
      END_STATE();
    case 286:
      ACCEPT_TOKEN(sym_plus_token);
      END_STATE();
    case 287:
      ACCEPT_TOKEN(sym_minus_token);
      END_STATE();
    case 288:
      ACCEPT_TOKEN(sym_true);
      END_STATE();
    case 289:
      ACCEPT_TOKEN(sym_true);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 290:
      ACCEPT_TOKEN(sym_false);
      END_STATE();
    case 291:
      ACCEPT_TOKEN(sym_false);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 292:
      ACCEPT_TOKEN(aux_sym_decimal_lit_token1);
      if (lookahead == '.') ADVANCE(295);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(138);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(292);
      END_STATE();
    case 293:
      ACCEPT_TOKEN(anon_sym_0);
      if (lookahead == '.') ADVANCE(295);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(138);
      if (lookahead == 'X' ||
          lookahead == 'x') ADVANCE(142);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(8);
      END_STATE();
    case 294:
      ACCEPT_TOKEN(sym_hex_lit);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(294);
      END_STATE();
    case 295:
      ACCEPT_TOKEN(aux_sym_float_lit_token1);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(138);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(295);
      END_STATE();
    case 296:
      ACCEPT_TOKEN(aux_sym_float_lit_token1);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(296);
      END_STATE();
    case 297:
      ACCEPT_TOKEN(anon_sym_infinity);
      END_STATE();
    case 298:
      ACCEPT_TOKEN(anon_sym_infinity);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 299:
      ACCEPT_TOKEN(anon_sym_inf);
      if (lookahead == 'i') ADVANCE(252);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 300:
      ACCEPT_TOKEN(anon_sym_inf);
      if (lookahead == 'i') ADVANCE(84);
      END_STATE();
    case 301:
      ACCEPT_TOKEN(sym_nan_token);
      END_STATE();
    case 302:
      ACCEPT_TOKEN(sym_nan_token);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(283);
      END_STATE();
    case 303:
      ACCEPT_TOKEN(aux_sym_string_constant_token1);
      if (lookahead == '\n') ADVANCE(308);
      if (lookahead == '"' ||
          lookahead == '\\') ADVANCE(314);
      if (lookahead != 0) ADVANCE(303);
      END_STATE();
    case 304:
      ACCEPT_TOKEN(aux_sym_string_constant_token1);
      if (lookahead == '*') ADVANCE(306);
      if (lookahead == '/') ADVANCE(303);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(308);
      END_STATE();
    case 305:
      ACCEPT_TOKEN(aux_sym_string_constant_token1);
      if (lookahead == '*') ADVANCE(305);
      if (lookahead == '/') ADVANCE(308);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(306);
      END_STATE();
    case 306:
      ACCEPT_TOKEN(aux_sym_string_constant_token1);
      if (lookahead == '*') ADVANCE(305);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(306);
      END_STATE();
    case 307:
      ACCEPT_TOKEN(aux_sym_string_constant_token1);
      if (lookahead == '/') ADVANCE(304);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(307);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(308);
      END_STATE();
    case 308:
      ACCEPT_TOKEN(aux_sym_string_constant_token1);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(308);
      END_STATE();
    case 309:
      ACCEPT_TOKEN(sym_escape_sequence);
      END_STATE();
    case 310:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(309);
      END_STATE();
    case 311:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(310);
      END_STATE();
    case 312:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 313:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '/') ADVANCE(153);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(314);
      END_STATE();
    case 314:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(314);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 151},
  [3] = {.lex_state = 151},
  [4] = {.lex_state = 151},
  [5] = {.lex_state = 151},
  [6] = {.lex_state = 0},
  [7] = {.lex_state = 3},
  [8] = {.lex_state = 3},
  [9] = {.lex_state = 3},
  [10] = {.lex_state = 3},
  [11] = {.lex_state = 3},
  [12] = {.lex_state = 3},
  [13] = {.lex_state = 3},
  [14] = {.lex_state = 0},
  [15] = {.lex_state = 0},
  [16] = {.lex_state = 0},
  [17] = {.lex_state = 151},
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
  [44] = {.lex_state = 0},
  [45] = {.lex_state = 0},
  [46] = {.lex_state = 0},
  [47] = {.lex_state = 0},
  [48] = {.lex_state = 0},
  [49] = {.lex_state = 0},
  [50] = {.lex_state = 0},
  [51] = {.lex_state = 0},
  [52] = {.lex_state = 0},
  [53] = {.lex_state = 0},
  [54] = {.lex_state = 0},
  [55] = {.lex_state = 0},
  [56] = {.lex_state = 0},
  [57] = {.lex_state = 0},
  [58] = {.lex_state = 0},
  [59] = {.lex_state = 0},
  [60] = {.lex_state = 0},
  [61] = {.lex_state = 0},
  [62] = {.lex_state = 0},
  [63] = {.lex_state = 0},
  [64] = {.lex_state = 0},
  [65] = {.lex_state = 0},
  [66] = {.lex_state = 0},
  [67] = {.lex_state = 0},
  [68] = {.lex_state = 0},
  [69] = {.lex_state = 0},
  [70] = {.lex_state = 0},
  [71] = {.lex_state = 0},
  [72] = {.lex_state = 0},
  [73] = {.lex_state = 0},
  [74] = {.lex_state = 0},
  [75] = {.lex_state = 0},
  [76] = {.lex_state = 0},
  [77] = {.lex_state = 0},
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
  [92] = {.lex_state = 3},
  [93] = {.lex_state = 3},
  [94] = {.lex_state = 3},
  [95] = {.lex_state = 151},
  [96] = {.lex_state = 3},
  [97] = {.lex_state = 151},
  [98] = {.lex_state = 0},
  [99] = {.lex_state = 151},
  [100] = {.lex_state = 151},
  [101] = {.lex_state = 151},
  [102] = {.lex_state = 0},
  [103] = {.lex_state = 151},
  [104] = {.lex_state = 151},
  [105] = {.lex_state = 0},
  [106] = {.lex_state = 151},
  [107] = {.lex_state = 9},
  [108] = {.lex_state = 9},
  [109] = {.lex_state = 9},
  [110] = {.lex_state = 9},
  [111] = {.lex_state = 9},
  [112] = {.lex_state = 151},
  [113] = {.lex_state = 9},
  [114] = {.lex_state = 9},
  [115] = {.lex_state = 9},
  [116] = {.lex_state = 9},
  [117] = {.lex_state = 9},
  [118] = {.lex_state = 9},
  [119] = {.lex_state = 9},
  [120] = {.lex_state = 9},
  [121] = {.lex_state = 9},
  [122] = {.lex_state = 9},
  [123] = {.lex_state = 151},
  [124] = {.lex_state = 151},
  [125] = {.lex_state = 9},
  [126] = {.lex_state = 151},
  [127] = {.lex_state = 9},
  [128] = {.lex_state = 9},
  [129] = {.lex_state = 151},
  [130] = {.lex_state = 0},
  [131] = {.lex_state = 9},
  [132] = {.lex_state = 9},
  [133] = {.lex_state = 9},
  [134] = {.lex_state = 151},
  [135] = {.lex_state = 9},
  [136] = {.lex_state = 151},
  [137] = {.lex_state = 9},
  [138] = {.lex_state = 0},
  [139] = {.lex_state = 151},
  [140] = {.lex_state = 9},
  [141] = {.lex_state = 151},
  [142] = {.lex_state = 9},
  [143] = {.lex_state = 151},
  [144] = {.lex_state = 9},
  [145] = {.lex_state = 9},
  [146] = {.lex_state = 9},
  [147] = {.lex_state = 9},
  [148] = {.lex_state = 151},
  [149] = {.lex_state = 9},
  [150] = {.lex_state = 3},
  [151] = {.lex_state = 151},
  [152] = {.lex_state = 9},
  [153] = {.lex_state = 151},
  [154] = {.lex_state = 9},
  [155] = {.lex_state = 151},
  [156] = {.lex_state = 151},
  [157] = {.lex_state = 9},
  [158] = {.lex_state = 151},
  [159] = {.lex_state = 9},
  [160] = {.lex_state = 9},
  [161] = {.lex_state = 151},
  [162] = {.lex_state = 9},
  [163] = {.lex_state = 151},
  [164] = {.lex_state = 0},
  [165] = {.lex_state = 9},
  [166] = {.lex_state = 151},
  [167] = {.lex_state = 0},
  [168] = {.lex_state = 9},
  [169] = {.lex_state = 1},
  [170] = {.lex_state = 9},
  [171] = {.lex_state = 151},
  [172] = {.lex_state = 9},
  [173] = {.lex_state = 9},
  [174] = {.lex_state = 1},
  [175] = {.lex_state = 151},
  [176] = {.lex_state = 0},
  [177] = {.lex_state = 151},
  [178] = {.lex_state = 151},
  [179] = {.lex_state = 151},
  [180] = {.lex_state = 9},
  [181] = {.lex_state = 151},
  [182] = {.lex_state = 0},
  [183] = {.lex_state = 151},
  [184] = {.lex_state = 9},
  [185] = {.lex_state = 9},
  [186] = {.lex_state = 151},
  [187] = {.lex_state = 151},
  [188] = {.lex_state = 151},
  [189] = {.lex_state = 151},
  [190] = {.lex_state = 151},
  [191] = {.lex_state = 151},
  [192] = {.lex_state = 151},
  [193] = {.lex_state = 1},
  [194] = {.lex_state = 151},
  [195] = {.lex_state = 151},
  [196] = {.lex_state = 151},
  [197] = {.lex_state = 151},
  [198] = {.lex_state = 2},
  [199] = {.lex_state = 151},
  [200] = {.lex_state = 151},
  [201] = {.lex_state = 151},
  [202] = {.lex_state = 151},
  [203] = {.lex_state = 9},
  [204] = {.lex_state = 151},
  [205] = {.lex_state = 151},
  [206] = {.lex_state = 151},
  [207] = {.lex_state = 151},
  [208] = {.lex_state = 151},
  [209] = {.lex_state = 2},
  [210] = {.lex_state = 151},
  [211] = {.lex_state = 151},
  [212] = {.lex_state = 151},
  [213] = {.lex_state = 2},
  [214] = {.lex_state = 151},
  [215] = {.lex_state = 151},
  [216] = {.lex_state = 151},
  [217] = {.lex_state = 151},
  [218] = {.lex_state = 151},
  [219] = {.lex_state = 2},
  [220] = {.lex_state = 151},
  [221] = {.lex_state = 151},
  [222] = {.lex_state = 2},
  [223] = {.lex_state = 151},
  [224] = {.lex_state = 151},
  [225] = {.lex_state = 151},
  [226] = {.lex_state = 151},
  [227] = {.lex_state = 9},
  [228] = {.lex_state = 9},
  [229] = {.lex_state = 9},
  [230] = {.lex_state = 9},
  [231] = {.lex_state = 151},
  [232] = {.lex_state = 151},
  [233] = {.lex_state = 151},
  [234] = {.lex_state = 151},
  [235] = {.lex_state = 151},
  [236] = {.lex_state = 151},
  [237] = {.lex_state = 151},
  [238] = {.lex_state = 151},
  [239] = {.lex_state = 151},
  [240] = {.lex_state = 2},
  [241] = {.lex_state = 151},
  [242] = {.lex_state = 9},
  [243] = {.lex_state = 151},
  [244] = {.lex_state = 9},
  [245] = {.lex_state = 151},
  [246] = {.lex_state = 9},
  [247] = {.lex_state = 151},
  [248] = {.lex_state = 9},
  [249] = {.lex_state = 151},
  [250] = {.lex_state = 9},
  [251] = {.lex_state = 151},
  [252] = {.lex_state = 151},
  [253] = {.lex_state = 151},
  [254] = {.lex_state = 9},
  [255] = {.lex_state = 9},
  [256] = {.lex_state = 9},
  [257] = {.lex_state = 2},
  [258] = {.lex_state = 151},
  [259] = {.lex_state = 151},
  [260] = {.lex_state = 151},
  [261] = {.lex_state = 9},
  [262] = {.lex_state = 9},
  [263] = {.lex_state = 9},
  [264] = {.lex_state = 9},
  [265] = {.lex_state = 2},
  [266] = {.lex_state = 9},
  [267] = {.lex_state = 151},
  [268] = {.lex_state = 151},
  [269] = {.lex_state = 151},
  [270] = {.lex_state = 151},
  [271] = {.lex_state = 151},
  [272] = {.lex_state = 2},
  [273] = {.lex_state = 151},
  [274] = {.lex_state = 151},
  [275] = {.lex_state = 151},
  [276] = {.lex_state = 151},
  [277] = {.lex_state = 2},
  [278] = {.lex_state = 2},
  [279] = {.lex_state = 151},
  [280] = {.lex_state = 151},
  [281] = {.lex_state = 151},
  [282] = {.lex_state = 2},
  [283] = {.lex_state = 2},
  [284] = {.lex_state = 151},
  [285] = {.lex_state = 151},
  [286] = {.lex_state = 151},
  [287] = {.lex_state = 151},
  [288] = {.lex_state = 151},
  [289] = {.lex_state = 151},
  [290] = {.lex_state = 9},
  [291] = {.lex_state = 151},
  [292] = {.lex_state = 2},
  [293] = {.lex_state = 2},
  [294] = {.lex_state = 151},
  [295] = {.lex_state = 151},
  [296] = {.lex_state = 2},
  [297] = {.lex_state = 2},
  [298] = {.lex_state = 151},
  [299] = {.lex_state = 151},
  [300] = {.lex_state = 2},
  [301] = {.lex_state = 2},
  [302] = {.lex_state = 151},
  [303] = {.lex_state = 151},
  [304] = {.lex_state = 2},
  [305] = {.lex_state = 151},
  [306] = {.lex_state = 2},
  [307] = {.lex_state = 151},
  [308] = {.lex_state = 2},
  [309] = {.lex_state = 2},
  [310] = {.lex_state = 151},
  [311] = {.lex_state = 151},
  [312] = {.lex_state = 151},
  [313] = {.lex_state = 151},
  [314] = {.lex_state = 2},
  [315] = {.lex_state = 151},
  [316] = {.lex_state = 151},
  [317] = {.lex_state = 151},
  [318] = {.lex_state = 2},
  [319] = {.lex_state = 151},
  [320] = {.lex_state = 151},
  [321] = {.lex_state = 151},
  [322] = {.lex_state = 151},
  [323] = {.lex_state = 151},
  [324] = {.lex_state = 2},
  [325] = {.lex_state = 151},
  [326] = {.lex_state = 2},
  [327] = {.lex_state = 151},
  [328] = {.lex_state = 2},
  [329] = {.lex_state = 151},
  [330] = {.lex_state = 151},
  [331] = {.lex_state = 151},
  [332] = {.lex_state = 151},
  [333] = {.lex_state = 151},
  [334] = {.lex_state = 151},
  [335] = {.lex_state = 151},
  [336] = {.lex_state = 151},
  [337] = {.lex_state = 151},
  [338] = {.lex_state = 151},
  [339] = {.lex_state = 2},
  [340] = {.lex_state = 151},
  [341] = {.lex_state = 151},
  [342] = {.lex_state = 151},
  [343] = {.lex_state = 151},
  [344] = {.lex_state = 151},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_documentation] = ACTIONS(1),
    [anon_sym_include] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_namespace] = ACTIONS(1),
    [anon_sym_attribute] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [anon_sym_table] = ACTIONS(1),
    [anon_sym_struct] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_enum] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_union] = ACTIONS(1),
    [anon_sym_root_type] = ACTIONS(1),
    [anon_sym_file_extension] = ACTIONS(1),
    [anon_sym_file_identifier] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_bool] = ACTIONS(1),
    [anon_sym_byte] = ACTIONS(1),
    [anon_sym_ubyte] = ACTIONS(1),
    [anon_sym_short] = ACTIONS(1),
    [anon_sym_ushort] = ACTIONS(1),
    [anon_sym_int] = ACTIONS(1),
    [anon_sym_uint] = ACTIONS(1),
    [anon_sym_float] = ACTIONS(1),
    [anon_sym_long] = ACTIONS(1),
    [anon_sym_ulong] = ACTIONS(1),
    [anon_sym_double] = ACTIONS(1),
    [anon_sym_int8] = ACTIONS(1),
    [anon_sym_uint8] = ACTIONS(1),
    [anon_sym_int16] = ACTIONS(1),
    [anon_sym_uint16] = ACTIONS(1),
    [anon_sym_int32] = ACTIONS(1),
    [anon_sym_uint32] = ACTIONS(1),
    [anon_sym_int64] = ACTIONS(1),
    [anon_sym_uint64] = ACTIONS(1),
    [anon_sym_float32] = ACTIONS(1),
    [anon_sym_float64] = ACTIONS(1),
    [anon_sym_string] = ACTIONS(1),
    [anon_sym_rpc_service] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_DOT] = ACTIONS(1),
    [sym_plus_token] = ACTIONS(1),
    [sym_minus_token] = ACTIONS(1),
    [sym_true] = ACTIONS(1),
    [sym_false] = ACTIONS(1),
    [aux_sym_decimal_lit_token1] = ACTIONS(1),
    [anon_sym_0] = ACTIONS(1),
    [sym_hex_lit] = ACTIONS(1),
    [aux_sym_float_lit_token1] = ACTIONS(1),
    [anon_sym_infinity] = ACTIONS(1),
    [anon_sym_inf] = ACTIONS(1),
    [sym_nan_token] = ACTIONS(1),
    [sym_escape_sequence] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
  },
  [1] = {
    [sym_source_file] = STATE(337),
    [sym_include] = STATE(6),
    [sym_namespace_decl] = STATE(14),
    [sym_attribute_decl] = STATE(14),
    [sym_type_decl] = STATE(14),
    [sym_enum_decl] = STATE(14),
    [sym_union_decl] = STATE(14),
    [sym_object] = STATE(14),
    [sym_root_decl] = STATE(14),
    [sym_file_extension_decl] = STATE(14),
    [sym_file_identifier_decl] = STATE(14),
    [sym_rpc_decl] = STATE(14),
    [aux_sym_source_file_repeat1] = STATE(6),
    [aux_sym_source_file_repeat2] = STATE(14),
    [aux_sym_type_decl_repeat1] = STATE(105),
    [ts_builtin_sym_end] = ACTIONS(5),
    [sym_documentation] = ACTIONS(7),
    [anon_sym_include] = ACTIONS(9),
    [anon_sym_namespace] = ACTIONS(11),
    [anon_sym_attribute] = ACTIONS(13),
    [anon_sym_table] = ACTIONS(15),
    [anon_sym_struct] = ACTIONS(15),
    [anon_sym_LBRACE] = ACTIONS(17),
    [anon_sym_enum] = ACTIONS(19),
    [anon_sym_union] = ACTIONS(21),
    [anon_sym_root_type] = ACTIONS(23),
    [anon_sym_file_extension] = ACTIONS(25),
    [anon_sym_file_identifier] = ACTIONS(27),
    [anon_sym_rpc_service] = ACTIONS(29),
    [sym_comment] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 24,
    ACTIONS(31), 1,
      anon_sym_DQUOTE,
    ACTIONS(33), 1,
      anon_sym_LBRACE,
    ACTIONS(35), 1,
      anon_sym_LBRACK,
    ACTIONS(37), 1,
      sym_identifier,
    ACTIONS(45), 1,
      sym_hex_lit,
    ACTIONS(47), 1,
      aux_sym_float_lit_token1,
    ACTIONS(51), 1,
      sym_nan_token,
    ACTIONS(53), 1,
      sym_comment,
    STATE(95), 1,
      sym_plus_minus_constant,
    STATE(124), 1,
      sym_decimal_lit,
    STATE(126), 1,
      sym_int_lit,
    STATE(153), 1,
      sym_inf_token,
    STATE(156), 1,
      sym_full_ident,
    STATE(158), 1,
      sym_scalar,
    STATE(161), 1,
      sym_float_lit,
    STATE(163), 1,
      sym_string_constant,
    STATE(181), 1,
      sym_object,
    STATE(192), 1,
      sym_single_value,
    STATE(243), 1,
      sym_value,
    ACTIONS(39), 2,
      sym_plus_token,
      sym_minus_token,
    ACTIONS(41), 2,
      sym_true,
      sym_false,
    ACTIONS(43), 2,
      aux_sym_decimal_lit_token1,
      anon_sym_0,
    ACTIONS(49), 2,
      anon_sym_infinity,
      anon_sym_inf,
    STATE(129), 3,
      sym_bool_constant,
      sym_int_constant,
      sym_float_constant,
  [79] = 24,
    ACTIONS(31), 1,
      anon_sym_DQUOTE,
    ACTIONS(33), 1,
      anon_sym_LBRACE,
    ACTIONS(35), 1,
      anon_sym_LBRACK,
    ACTIONS(37), 1,
      sym_identifier,
    ACTIONS(45), 1,
      sym_hex_lit,
    ACTIONS(47), 1,
      aux_sym_float_lit_token1,
    ACTIONS(51), 1,
      sym_nan_token,
    ACTIONS(53), 1,
      sym_comment,
    STATE(95), 1,
      sym_plus_minus_constant,
    STATE(124), 1,
      sym_decimal_lit,
    STATE(126), 1,
      sym_int_lit,
    STATE(153), 1,
      sym_inf_token,
    STATE(156), 1,
      sym_full_ident,
    STATE(158), 1,
      sym_scalar,
    STATE(161), 1,
      sym_float_lit,
    STATE(163), 1,
      sym_string_constant,
    STATE(181), 1,
      sym_object,
    STATE(192), 1,
      sym_single_value,
    STATE(226), 1,
      sym_value,
    ACTIONS(39), 2,
      sym_plus_token,
      sym_minus_token,
    ACTIONS(41), 2,
      sym_true,
      sym_false,
    ACTIONS(43), 2,
      aux_sym_decimal_lit_token1,
      anon_sym_0,
    ACTIONS(49), 2,
      anon_sym_infinity,
      anon_sym_inf,
    STATE(129), 3,
      sym_bool_constant,
      sym_int_constant,
      sym_float_constant,
  [158] = 24,
    ACTIONS(31), 1,
      anon_sym_DQUOTE,
    ACTIONS(33), 1,
      anon_sym_LBRACE,
    ACTIONS(35), 1,
      anon_sym_LBRACK,
    ACTIONS(37), 1,
      sym_identifier,
    ACTIONS(45), 1,
      sym_hex_lit,
    ACTIONS(47), 1,
      aux_sym_float_lit_token1,
    ACTIONS(51), 1,
      sym_nan_token,
    ACTIONS(53), 1,
      sym_comment,
    STATE(95), 1,
      sym_plus_minus_constant,
    STATE(124), 1,
      sym_decimal_lit,
    STATE(126), 1,
      sym_int_lit,
    STATE(153), 1,
      sym_inf_token,
    STATE(156), 1,
      sym_full_ident,
    STATE(158), 1,
      sym_scalar,
    STATE(161), 1,
      sym_float_lit,
    STATE(163), 1,
      sym_string_constant,
    STATE(181), 1,
      sym_object,
    STATE(192), 1,
      sym_single_value,
    STATE(241), 1,
      sym_value,
    ACTIONS(39), 2,
      sym_plus_token,
      sym_minus_token,
    ACTIONS(41), 2,
      sym_true,
      sym_false,
    ACTIONS(43), 2,
      aux_sym_decimal_lit_token1,
      anon_sym_0,
    ACTIONS(49), 2,
      anon_sym_infinity,
      anon_sym_inf,
    STATE(129), 3,
      sym_bool_constant,
      sym_int_constant,
      sym_float_constant,
  [237] = 24,
    ACTIONS(31), 1,
      anon_sym_DQUOTE,
    ACTIONS(33), 1,
      anon_sym_LBRACE,
    ACTIONS(35), 1,
      anon_sym_LBRACK,
    ACTIONS(37), 1,
      sym_identifier,
    ACTIONS(45), 1,
      sym_hex_lit,
    ACTIONS(47), 1,
      aux_sym_float_lit_token1,
    ACTIONS(51), 1,
      sym_nan_token,
    ACTIONS(53), 1,
      sym_comment,
    STATE(95), 1,
      sym_plus_minus_constant,
    STATE(124), 1,
      sym_decimal_lit,
    STATE(126), 1,
      sym_int_lit,
    STATE(153), 1,
      sym_inf_token,
    STATE(156), 1,
      sym_full_ident,
    STATE(158), 1,
      sym_scalar,
    STATE(161), 1,
      sym_float_lit,
    STATE(163), 1,
      sym_string_constant,
    STATE(181), 1,
      sym_object,
    STATE(192), 1,
      sym_single_value,
    STATE(287), 1,
      sym_value,
    ACTIONS(39), 2,
      sym_plus_token,
      sym_minus_token,
    ACTIONS(41), 2,
      sym_true,
      sym_false,
    ACTIONS(43), 2,
      aux_sym_decimal_lit_token1,
      anon_sym_0,
    ACTIONS(49), 2,
      anon_sym_infinity,
      anon_sym_inf,
    STATE(129), 3,
      sym_bool_constant,
      sym_int_constant,
      sym_float_constant,
  [316] = 17,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      sym_documentation,
    ACTIONS(9), 1,
      anon_sym_include,
    ACTIONS(11), 1,
      anon_sym_namespace,
    ACTIONS(13), 1,
      anon_sym_attribute,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(19), 1,
      anon_sym_enum,
    ACTIONS(21), 1,
      anon_sym_union,
    ACTIONS(23), 1,
      anon_sym_root_type,
    ACTIONS(25), 1,
      anon_sym_file_extension,
    ACTIONS(27), 1,
      anon_sym_file_identifier,
    ACTIONS(29), 1,
      anon_sym_rpc_service,
    ACTIONS(55), 1,
      ts_builtin_sym_end,
    STATE(105), 1,
      aux_sym_type_decl_repeat1,
    ACTIONS(15), 2,
      anon_sym_table,
      anon_sym_struct,
    STATE(18), 2,
      sym_include,
      aux_sym_source_file_repeat1,
    STATE(15), 11,
      sym_namespace_decl,
      sym_attribute_decl,
      sym_type_decl,
      sym_enum_decl,
      sym_union_decl,
      sym_object,
      sym_root_decl,
      sym_file_extension_decl,
      sym_file_identifier_decl,
      sym_rpc_decl,
      aux_sym_source_file_repeat2,
  [380] = 6,
    ACTIONS(37), 1,
      sym_identifier,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(57), 1,
      anon_sym_LBRACK,
    STATE(104), 1,
      sym_full_ident,
    STATE(270), 1,
      sym_type,
    ACTIONS(59), 22,
      anon_sym_bool,
      anon_sym_byte,
      anon_sym_ubyte,
      anon_sym_short,
      anon_sym_ushort,
      anon_sym_int,
      anon_sym_uint,
      anon_sym_float,
      anon_sym_long,
      anon_sym_ulong,
      anon_sym_double,
      anon_sym_int8,
      anon_sym_uint8,
      anon_sym_int16,
      anon_sym_uint16,
      anon_sym_int32,
      anon_sym_uint32,
      anon_sym_int64,
      anon_sym_uint64,
      anon_sym_float32,
      anon_sym_float64,
      anon_sym_string,
  [420] = 6,
    ACTIONS(37), 1,
      sym_identifier,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(57), 1,
      anon_sym_LBRACK,
    STATE(104), 1,
      sym_full_ident,
    STATE(237), 1,
      sym_type,
    ACTIONS(59), 22,
      anon_sym_bool,
      anon_sym_byte,
      anon_sym_ubyte,
      anon_sym_short,
      anon_sym_ushort,
      anon_sym_int,
      anon_sym_uint,
      anon_sym_float,
      anon_sym_long,
      anon_sym_ulong,
      anon_sym_double,
      anon_sym_int8,
      anon_sym_uint8,
      anon_sym_int16,
      anon_sym_uint16,
      anon_sym_int32,
      anon_sym_uint32,
      anon_sym_int64,
      anon_sym_uint64,
      anon_sym_float32,
      anon_sym_float64,
      anon_sym_string,
  [460] = 6,
    ACTIONS(37), 1,
      sym_identifier,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(57), 1,
      anon_sym_LBRACK,
    STATE(104), 1,
      sym_full_ident,
    STATE(221), 1,
      sym_type,
    ACTIONS(59), 22,
      anon_sym_bool,
      anon_sym_byte,
      anon_sym_ubyte,
      anon_sym_short,
      anon_sym_ushort,
      anon_sym_int,
      anon_sym_uint,
      anon_sym_float,
      anon_sym_long,
      anon_sym_ulong,
      anon_sym_double,
      anon_sym_int8,
      anon_sym_uint8,
      anon_sym_int16,
      anon_sym_uint16,
      anon_sym_int32,
      anon_sym_uint32,
      anon_sym_int64,
      anon_sym_uint64,
      anon_sym_float32,
      anon_sym_float64,
      anon_sym_string,
  [500] = 6,
    ACTIONS(37), 1,
      sym_identifier,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(57), 1,
      anon_sym_LBRACK,
    STATE(104), 1,
      sym_full_ident,
    STATE(175), 1,
      sym_type,
    ACTIONS(59), 22,
      anon_sym_bool,
      anon_sym_byte,
      anon_sym_ubyte,
      anon_sym_short,
      anon_sym_ushort,
      anon_sym_int,
      anon_sym_uint,
      anon_sym_float,
      anon_sym_long,
      anon_sym_ulong,
      anon_sym_double,
      anon_sym_int8,
      anon_sym_uint8,
      anon_sym_int16,
      anon_sym_uint16,
      anon_sym_int32,
      anon_sym_uint32,
      anon_sym_int64,
      anon_sym_uint64,
      anon_sym_float32,
      anon_sym_float64,
      anon_sym_string,
  [540] = 6,
    ACTIONS(37), 1,
      sym_identifier,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(57), 1,
      anon_sym_LBRACK,
    STATE(104), 1,
      sym_full_ident,
    STATE(178), 1,
      sym_type,
    ACTIONS(59), 22,
      anon_sym_bool,
      anon_sym_byte,
      anon_sym_ubyte,
      anon_sym_short,
      anon_sym_ushort,
      anon_sym_int,
      anon_sym_uint,
      anon_sym_float,
      anon_sym_long,
      anon_sym_ulong,
      anon_sym_double,
      anon_sym_int8,
      anon_sym_uint8,
      anon_sym_int16,
      anon_sym_uint16,
      anon_sym_int32,
      anon_sym_uint32,
      anon_sym_int64,
      anon_sym_uint64,
      anon_sym_float32,
      anon_sym_float64,
      anon_sym_string,
  [580] = 6,
    ACTIONS(37), 1,
      sym_identifier,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(57), 1,
      anon_sym_LBRACK,
    STATE(104), 1,
      sym_full_ident,
    STATE(279), 1,
      sym_type,
    ACTIONS(59), 22,
      anon_sym_bool,
      anon_sym_byte,
      anon_sym_ubyte,
      anon_sym_short,
      anon_sym_ushort,
      anon_sym_int,
      anon_sym_uint,
      anon_sym_float,
      anon_sym_long,
      anon_sym_ulong,
      anon_sym_double,
      anon_sym_int8,
      anon_sym_uint8,
      anon_sym_int16,
      anon_sym_uint16,
      anon_sym_int32,
      anon_sym_uint32,
      anon_sym_int64,
      anon_sym_uint64,
      anon_sym_float32,
      anon_sym_float64,
      anon_sym_string,
  [620] = 6,
    ACTIONS(37), 1,
      sym_identifier,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(57), 1,
      anon_sym_LBRACK,
    STATE(104), 1,
      sym_full_ident,
    STATE(284), 1,
      sym_type,
    ACTIONS(59), 22,
      anon_sym_bool,
      anon_sym_byte,
      anon_sym_ubyte,
      anon_sym_short,
      anon_sym_ushort,
      anon_sym_int,
      anon_sym_uint,
      anon_sym_float,
      anon_sym_long,
      anon_sym_ulong,
      anon_sym_double,
      anon_sym_int8,
      anon_sym_uint8,
      anon_sym_int16,
      anon_sym_uint16,
      anon_sym_int32,
      anon_sym_uint32,
      anon_sym_int64,
      anon_sym_uint64,
      anon_sym_float32,
      anon_sym_float64,
      anon_sym_string,
  [660] = 15,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      sym_documentation,
    ACTIONS(11), 1,
      anon_sym_namespace,
    ACTIONS(13), 1,
      anon_sym_attribute,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(19), 1,
      anon_sym_enum,
    ACTIONS(21), 1,
      anon_sym_union,
    ACTIONS(23), 1,
      anon_sym_root_type,
    ACTIONS(25), 1,
      anon_sym_file_extension,
    ACTIONS(27), 1,
      anon_sym_file_identifier,
    ACTIONS(29), 1,
      anon_sym_rpc_service,
    ACTIONS(55), 1,
      ts_builtin_sym_end,
    STATE(105), 1,
      aux_sym_type_decl_repeat1,
    ACTIONS(15), 2,
      anon_sym_table,
      anon_sym_struct,
    STATE(16), 11,
      sym_namespace_decl,
      sym_attribute_decl,
      sym_type_decl,
      sym_enum_decl,
      sym_union_decl,
      sym_object,
      sym_root_decl,
      sym_file_extension_decl,
      sym_file_identifier_decl,
      sym_rpc_decl,
      aux_sym_source_file_repeat2,
  [717] = 15,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      sym_documentation,
    ACTIONS(11), 1,
      anon_sym_namespace,
    ACTIONS(13), 1,
      anon_sym_attribute,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(19), 1,
      anon_sym_enum,
    ACTIONS(21), 1,
      anon_sym_union,
    ACTIONS(23), 1,
      anon_sym_root_type,
    ACTIONS(25), 1,
      anon_sym_file_extension,
    ACTIONS(27), 1,
      anon_sym_file_identifier,
    ACTIONS(29), 1,
      anon_sym_rpc_service,
    ACTIONS(61), 1,
      ts_builtin_sym_end,
    STATE(105), 1,
      aux_sym_type_decl_repeat1,
    ACTIONS(15), 2,
      anon_sym_table,
      anon_sym_struct,
    STATE(16), 11,
      sym_namespace_decl,
      sym_attribute_decl,
      sym_type_decl,
      sym_enum_decl,
      sym_union_decl,
      sym_object,
      sym_root_decl,
      sym_file_extension_decl,
      sym_file_identifier_decl,
      sym_rpc_decl,
      aux_sym_source_file_repeat2,
  [774] = 15,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(63), 1,
      ts_builtin_sym_end,
    ACTIONS(65), 1,
      sym_documentation,
    ACTIONS(68), 1,
      anon_sym_namespace,
    ACTIONS(71), 1,
      anon_sym_attribute,
    ACTIONS(77), 1,
      anon_sym_LBRACE,
    ACTIONS(80), 1,
      anon_sym_enum,
    ACTIONS(83), 1,
      anon_sym_union,
    ACTIONS(86), 1,
      anon_sym_root_type,
    ACTIONS(89), 1,
      anon_sym_file_extension,
    ACTIONS(92), 1,
      anon_sym_file_identifier,
    ACTIONS(95), 1,
      anon_sym_rpc_service,
    STATE(105), 1,
      aux_sym_type_decl_repeat1,
    ACTIONS(74), 2,
      anon_sym_table,
      anon_sym_struct,
    STATE(16), 11,
      sym_namespace_decl,
      sym_attribute_decl,
      sym_type_decl,
      sym_enum_decl,
      sym_union_decl,
      sym_object,
      sym_root_decl,
      sym_file_extension_decl,
      sym_file_identifier_decl,
      sym_rpc_decl,
      aux_sym_source_file_repeat2,
  [831] = 20,
    ACTIONS(31), 1,
      anon_sym_DQUOTE,
    ACTIONS(37), 1,
      sym_identifier,
    ACTIONS(45), 1,
      sym_hex_lit,
    ACTIONS(47), 1,
      aux_sym_float_lit_token1,
    ACTIONS(51), 1,
      sym_nan_token,
    ACTIONS(53), 1,
      sym_comment,
    STATE(95), 1,
      sym_plus_minus_constant,
    STATE(124), 1,
      sym_decimal_lit,
    STATE(126), 1,
      sym_int_lit,
    STATE(153), 1,
      sym_inf_token,
    STATE(156), 1,
      sym_full_ident,
    STATE(158), 1,
      sym_scalar,
    STATE(161), 1,
      sym_float_lit,
    STATE(163), 1,
      sym_string_constant,
    STATE(271), 1,
      sym_single_value,
    ACTIONS(39), 2,
      sym_plus_token,
      sym_minus_token,
    ACTIONS(41), 2,
      sym_true,
      sym_false,
    ACTIONS(43), 2,
      aux_sym_decimal_lit_token1,
      anon_sym_0,
    ACTIONS(49), 2,
      anon_sym_infinity,
      anon_sym_inf,
    STATE(129), 3,
      sym_bool_constant,
      sym_int_constant,
      sym_float_constant,
  [898] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(100), 1,
      anon_sym_include,
    STATE(18), 2,
      sym_include,
      aux_sym_source_file_repeat1,
    ACTIONS(98), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [924] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 14,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_include,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [944] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(105), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [963] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [982] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(109), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1001] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(109), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1020] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(111), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1039] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(113), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1058] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(115), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1077] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(117), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1096] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(119), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1115] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(121), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1134] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(123), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1153] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(125), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1172] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(127), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1191] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(129), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1210] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(131), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1229] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(133), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1248] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(135), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1267] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(137), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1286] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(137), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1305] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(139), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1324] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(141), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1343] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(143), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1362] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(145), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1381] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(147), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1400] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(149), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1419] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(151), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1438] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(153), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1457] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(153), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1476] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(155), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1495] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(157), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1514] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(159), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1533] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(161), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1552] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(163), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1571] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(165), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1590] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(167), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1609] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(169), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1628] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(171), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1647] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(173), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1666] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(175), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1685] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(175), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1704] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(177), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1723] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(179), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1742] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(181), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1761] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(181), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1780] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(183), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1799] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(185), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1818] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(187), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1837] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(189), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1856] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(191), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1875] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(193), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1894] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(195), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1913] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(197), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1932] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(199), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1951] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(201), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1970] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(203), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [1989] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(205), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [2008] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(207), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [2027] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(207), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [2046] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(209), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [2065] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(211), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [2084] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(213), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [2103] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(215), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [2122] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(217), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [2141] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(219), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [2160] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(221), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [2179] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(223), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [2198] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(225), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [2217] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(227), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [2236] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(229), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [2255] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(231), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [2274] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(233), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [2293] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(155), 13,
      ts_builtin_sym_end,
      sym_documentation,
      anon_sym_namespace,
      anon_sym_attribute,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_LBRACE,
      anon_sym_enum,
      anon_sym_union,
      anon_sym_root_type,
      anon_sym_file_extension,
      anon_sym_file_identifier,
      anon_sym_rpc_service,
  [2312] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(237), 1,
      anon_sym_DOT,
    STATE(92), 1,
      aux_sym_full_ident_repeat1,
    ACTIONS(235), 9,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COLON,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_EQ,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [2333] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(242), 1,
      anon_sym_DOT,
    STATE(94), 1,
      aux_sym_full_ident_repeat1,
    ACTIONS(240), 9,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COLON,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_EQ,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [2354] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(242), 1,
      anon_sym_DOT,
    STATE(92), 1,
      aux_sym_full_ident_repeat1,
    ACTIONS(244), 9,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COLON,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_EQ,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [2375] = 10,
    ACTIONS(45), 1,
      sym_hex_lit,
    ACTIONS(49), 1,
      anon_sym_inf,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(246), 1,
      anon_sym_infinity,
    STATE(112), 1,
      sym_int_lit,
    STATE(124), 1,
      sym_decimal_lit,
    STATE(143), 1,
      sym_float_lit,
    STATE(153), 1,
      sym_inf_token,
    ACTIONS(43), 2,
      aux_sym_decimal_lit_token1,
      anon_sym_0,
    ACTIONS(47), 2,
      aux_sym_float_lit_token1,
      sym_nan_token,
  [2408] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(235), 10,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COLON,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_EQ,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_DOT,
  [2424] = 9,
    ACTIONS(43), 1,
      anon_sym_0,
    ACTIONS(45), 1,
      sym_hex_lit,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(248), 1,
      aux_sym_decimal_lit_token1,
    STATE(124), 1,
      sym_decimal_lit,
    STATE(126), 1,
      sym_int_lit,
    STATE(139), 1,
      sym_plus_minus_constant,
    STATE(171), 1,
      sym_int_constant,
    ACTIONS(39), 2,
      sym_plus_token,
      sym_minus_token,
  [2453] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(250), 1,
      sym_documentation,
    STATE(98), 1,
      aux_sym_type_decl_repeat1,
    ACTIONS(253), 7,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_RBRACE,
      anon_sym_enum,
      anon_sym_COMMA,
      anon_sym_union,
      anon_sym_rpc_service,
  [2472] = 9,
    ACTIONS(43), 1,
      anon_sym_0,
    ACTIONS(45), 1,
      sym_hex_lit,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(248), 1,
      aux_sym_decimal_lit_token1,
    STATE(124), 1,
      sym_decimal_lit,
    STATE(126), 1,
      sym_int_lit,
    STATE(139), 1,
      sym_plus_minus_constant,
    STATE(187), 1,
      sym_int_constant,
    ACTIONS(39), 2,
      sym_plus_token,
      sym_minus_token,
  [2501] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(255), 8,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COLON,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_EQ,
      anon_sym_LPAREN,
  [2515] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(257), 8,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COLON,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_EQ,
      anon_sym_LPAREN,
  [2529] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(259), 8,
      sym_documentation,
      anon_sym_table,
      anon_sym_struct,
      anon_sym_RBRACE,
      anon_sym_enum,
      anon_sym_COMMA,
      anon_sym_union,
      anon_sym_rpc_service,
  [2543] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(261), 8,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COLON,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_EQ,
      anon_sym_LPAREN,
  [2557] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(263), 8,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COLON,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_EQ,
      anon_sym_LPAREN,
  [2571] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      sym_documentation,
    ACTIONS(265), 1,
      anon_sym_table,
    ACTIONS(267), 1,
      anon_sym_struct,
    ACTIONS(269), 1,
      anon_sym_enum,
    ACTIONS(271), 1,
      anon_sym_union,
    ACTIONS(273), 1,
      anon_sym_rpc_service,
    STATE(98), 1,
      aux_sym_type_decl_repeat1,
  [2596] = 3,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(275), 3,
      aux_sym_decimal_lit_token1,
      anon_sym_0,
      anon_sym_inf,
    ACTIONS(277), 4,
      sym_hex_lit,
      aux_sym_float_lit_token1,
      anon_sym_infinity,
      sym_nan_token,
  [2611] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(281), 1,
      anon_sym_RBRACE,
    ACTIONS(283), 1,
      sym_identifier,
    STATE(250), 1,
      aux_sym_type_decl_repeat1,
    STATE(109), 2,
      sym_rpc_method,
      aux_sym_rpc_decl_repeat1,
  [2631] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(283), 1,
      sym_identifier,
    ACTIONS(285), 1,
      anon_sym_RBRACE,
    STATE(250), 1,
      aux_sym_type_decl_repeat1,
    STATE(109), 2,
      sym_rpc_method,
      aux_sym_rpc_decl_repeat1,
  [2651] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(287), 1,
      sym_documentation,
    ACTIONS(290), 1,
      anon_sym_RBRACE,
    ACTIONS(292), 1,
      sym_identifier,
    STATE(250), 1,
      aux_sym_type_decl_repeat1,
    STATE(109), 2,
      sym_rpc_method,
      aux_sym_rpc_decl_repeat1,
  [2671] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(283), 1,
      sym_identifier,
    ACTIONS(295), 1,
      anon_sym_RBRACE,
    STATE(250), 1,
      aux_sym_type_decl_repeat1,
    STATE(108), 2,
      sym_rpc_method,
      aux_sym_rpc_decl_repeat1,
  [2691] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(283), 1,
      sym_identifier,
    ACTIONS(297), 1,
      anon_sym_RBRACE,
    STATE(250), 1,
      aux_sym_type_decl_repeat1,
    STATE(107), 2,
      sym_rpc_method,
      aux_sym_rpc_decl_repeat1,
  [2711] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(299), 6,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [2723] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(301), 1,
      anon_sym_RBRACE,
    ACTIONS(303), 1,
      sym_identifier,
    STATE(117), 1,
      aux_sym_type_decl_repeat2,
    STATE(229), 1,
      sym_field_decl,
    STATE(230), 1,
      aux_sym_type_decl_repeat1,
  [2745] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(303), 1,
      sym_identifier,
    ACTIONS(305), 1,
      anon_sym_RBRACE,
    STATE(119), 1,
      aux_sym_type_decl_repeat2,
    STATE(229), 1,
      sym_field_decl,
    STATE(230), 1,
      aux_sym_type_decl_repeat1,
  [2767] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(303), 1,
      sym_identifier,
    ACTIONS(307), 1,
      anon_sym_RBRACE,
    STATE(120), 1,
      aux_sym_type_decl_repeat2,
    STATE(229), 1,
      sym_field_decl,
    STATE(230), 1,
      aux_sym_type_decl_repeat1,
  [2789] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(303), 1,
      sym_identifier,
    ACTIONS(309), 1,
      anon_sym_RBRACE,
    STATE(114), 1,
      aux_sym_type_decl_repeat2,
    STATE(229), 1,
      sym_field_decl,
    STATE(230), 1,
      aux_sym_type_decl_repeat1,
  [2811] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(303), 1,
      sym_identifier,
    ACTIONS(311), 1,
      anon_sym_RBRACE,
    STATE(119), 1,
      aux_sym_type_decl_repeat2,
    STATE(229), 1,
      sym_field_decl,
    STATE(230), 1,
      aux_sym_type_decl_repeat1,
  [2833] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(303), 1,
      sym_identifier,
    ACTIONS(313), 1,
      anon_sym_RBRACE,
    STATE(121), 1,
      aux_sym_type_decl_repeat2,
    STATE(229), 1,
      sym_field_decl,
    STATE(230), 1,
      aux_sym_type_decl_repeat1,
  [2855] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(315), 1,
      sym_documentation,
    ACTIONS(318), 1,
      anon_sym_RBRACE,
    ACTIONS(320), 1,
      sym_identifier,
    STATE(119), 1,
      aux_sym_type_decl_repeat2,
    STATE(229), 1,
      sym_field_decl,
    STATE(230), 1,
      aux_sym_type_decl_repeat1,
  [2877] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(303), 1,
      sym_identifier,
    ACTIONS(323), 1,
      anon_sym_RBRACE,
    STATE(119), 1,
      aux_sym_type_decl_repeat2,
    STATE(229), 1,
      sym_field_decl,
    STATE(230), 1,
      aux_sym_type_decl_repeat1,
  [2899] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(303), 1,
      sym_identifier,
    ACTIONS(325), 1,
      anon_sym_RBRACE,
    STATE(119), 1,
      aux_sym_type_decl_repeat2,
    STATE(229), 1,
      sym_field_decl,
    STATE(230), 1,
      aux_sym_type_decl_repeat1,
  [2921] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(303), 1,
      sym_identifier,
    ACTIONS(327), 1,
      anon_sym_RBRACE,
    STATE(119), 1,
      aux_sym_type_decl_repeat2,
    STATE(229), 1,
      sym_field_decl,
    STATE(230), 1,
      aux_sym_type_decl_repeat1,
  [2943] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(329), 6,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [2955] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(331), 6,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [2967] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(303), 1,
      sym_identifier,
    ACTIONS(333), 1,
      anon_sym_RBRACE,
    STATE(119), 1,
      aux_sym_type_decl_repeat2,
    STATE(229), 1,
      sym_field_decl,
    STATE(230), 1,
      aux_sym_type_decl_repeat1,
  [2989] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(335), 6,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [3001] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(303), 1,
      sym_identifier,
    ACTIONS(337), 1,
      anon_sym_RBRACE,
    STATE(125), 1,
      aux_sym_type_decl_repeat2,
    STATE(229), 1,
      sym_field_decl,
    STATE(230), 1,
      aux_sym_type_decl_repeat1,
  [3023] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(303), 1,
      sym_identifier,
    ACTIONS(339), 1,
      anon_sym_RBRACE,
    STATE(122), 1,
      aux_sym_type_decl_repeat2,
    STATE(229), 1,
      sym_field_decl,
    STATE(230), 1,
      aux_sym_type_decl_repeat1,
  [3045] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(341), 5,
      anon_sym_SEMI,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [3056] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      sym_documentation,
    ACTIONS(343), 1,
      anon_sym_RBRACE,
    ACTIONS(345), 1,
      anon_sym_COMMA,
    STATE(98), 1,
      aux_sym_type_decl_repeat1,
    STATE(195), 1,
      aux_sym_object_repeat1,
  [3075] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(347), 1,
      sym_identifier,
    STATE(238), 1,
      sym_union_field_decl,
    STATE(245), 1,
      sym_full_ident,
    STATE(246), 1,
      aux_sym_type_decl_repeat1,
  [3094] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(349), 1,
      anon_sym_RBRACE,
    ACTIONS(351), 1,
      sym_identifier,
    STATE(246), 1,
      aux_sym_type_decl_repeat1,
    STATE(280), 1,
      sym_union_field_decl,
  [3113] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(347), 1,
      sym_identifier,
    STATE(224), 1,
      sym_union_field_decl,
    STATE(225), 1,
      sym_full_ident,
    STATE(246), 1,
      aux_sym_type_decl_repeat1,
  [3132] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(353), 5,
      anon_sym_SEMI,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [3143] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(351), 1,
      sym_identifier,
    ACTIONS(355), 1,
      anon_sym_RBRACE,
    STATE(246), 1,
      aux_sym_type_decl_repeat1,
    STATE(280), 1,
      sym_union_field_decl,
  [3162] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(357), 5,
      anon_sym_SEMI,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [3173] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(351), 1,
      sym_identifier,
    ACTIONS(359), 1,
      anon_sym_RBRACE,
    STATE(246), 1,
      aux_sym_type_decl_repeat1,
    STATE(280), 1,
      sym_union_field_decl,
  [3192] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      sym_documentation,
    ACTIONS(345), 1,
      anon_sym_COMMA,
    ACTIONS(361), 1,
      anon_sym_RBRACE,
    STATE(164), 1,
      aux_sym_type_decl_repeat1,
    STATE(206), 1,
      aux_sym_object_repeat1,
  [3211] = 6,
    ACTIONS(43), 1,
      anon_sym_0,
    ACTIONS(45), 1,
      sym_hex_lit,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(248), 1,
      aux_sym_decimal_lit_token1,
    STATE(112), 1,
      sym_int_lit,
    STATE(124), 1,
      sym_decimal_lit,
  [3230] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(363), 1,
      anon_sym_RBRACE,
    ACTIONS(365), 1,
      sym_identifier,
    STATE(248), 1,
      aux_sym_type_decl_repeat1,
    STATE(289), 1,
      sym_enum_val_decl,
  [3249] = 5,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(369), 1,
      anon_sym_EQ,
    ACTIONS(371), 1,
      anon_sym_LPAREN,
    STATE(274), 1,
      sym_metadata,
    ACTIONS(367), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [3266] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(365), 1,
      sym_identifier,
    ACTIONS(373), 1,
      anon_sym_RBRACE,
    STATE(248), 1,
      aux_sym_type_decl_repeat1,
    STATE(289), 1,
      sym_enum_val_decl,
  [3285] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(375), 5,
      anon_sym_SEMI,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [3296] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(351), 1,
      sym_identifier,
    ACTIONS(377), 1,
      anon_sym_RBRACE,
    STATE(246), 1,
      aux_sym_type_decl_repeat1,
    STATE(280), 1,
      sym_union_field_decl,
  [3315] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(347), 1,
      sym_identifier,
    STATE(200), 1,
      sym_union_field_decl,
    STATE(201), 1,
      sym_full_ident,
    STATE(246), 1,
      aux_sym_type_decl_repeat1,
  [3334] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(365), 1,
      sym_identifier,
    ACTIONS(379), 1,
      anon_sym_RBRACE,
    STATE(248), 1,
      aux_sym_type_decl_repeat1,
    STATE(289), 1,
      sym_enum_val_decl,
  [3353] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(365), 1,
      sym_identifier,
    ACTIONS(381), 1,
      anon_sym_RBRACE,
    STATE(248), 1,
      aux_sym_type_decl_repeat1,
    STATE(289), 1,
      sym_enum_val_decl,
  [3372] = 5,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(371), 1,
      anon_sym_LPAREN,
    ACTIONS(385), 1,
      anon_sym_EQ,
    STATE(291), 1,
      sym_metadata,
    ACTIONS(383), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [3389] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(351), 1,
      sym_identifier,
    ACTIONS(387), 1,
      anon_sym_RBRACE,
    STATE(246), 1,
      aux_sym_type_decl_repeat1,
    STATE(280), 1,
      sym_union_field_decl,
  [3408] = 5,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(242), 1,
      anon_sym_DOT,
    ACTIONS(389), 1,
      anon_sym_COLON,
    STATE(94), 1,
      aux_sym_full_ident_repeat1,
    ACTIONS(240), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [3425] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(391), 5,
      anon_sym_SEMI,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [3436] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(347), 1,
      sym_identifier,
    STATE(211), 1,
      sym_union_field_decl,
    STATE(212), 1,
      sym_full_ident,
    STATE(246), 1,
      aux_sym_type_decl_repeat1,
  [3455] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(393), 5,
      anon_sym_SEMI,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [3466] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(365), 1,
      sym_identifier,
    ACTIONS(395), 1,
      anon_sym_RBRACE,
    STATE(248), 1,
      aux_sym_type_decl_repeat1,
    STATE(289), 1,
      sym_enum_val_decl,
  [3485] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(397), 5,
      anon_sym_SEMI,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [3496] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(399), 5,
      anon_sym_SEMI,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [3507] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(365), 1,
      sym_identifier,
    ACTIONS(401), 1,
      anon_sym_RBRACE,
    STATE(248), 1,
      aux_sym_type_decl_repeat1,
    STATE(289), 1,
      sym_enum_val_decl,
  [3526] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(403), 5,
      anon_sym_SEMI,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [3537] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(365), 1,
      sym_identifier,
    ACTIONS(405), 1,
      anon_sym_RBRACE,
    STATE(248), 1,
      aux_sym_type_decl_repeat1,
    STATE(289), 1,
      sym_enum_val_decl,
  [3556] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(351), 1,
      sym_identifier,
    ACTIONS(407), 1,
      anon_sym_RBRACE,
    STATE(246), 1,
      aux_sym_type_decl_repeat1,
    STATE(280), 1,
      sym_union_field_decl,
  [3575] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(409), 5,
      anon_sym_SEMI,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [3586] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(351), 1,
      sym_identifier,
    ACTIONS(411), 1,
      anon_sym_RBRACE,
    STATE(246), 1,
      aux_sym_type_decl_repeat1,
    STATE(280), 1,
      sym_union_field_decl,
  [3605] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(413), 5,
      anon_sym_SEMI,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [3616] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      sym_documentation,
    ACTIONS(345), 1,
      anon_sym_COMMA,
    ACTIONS(415), 1,
      anon_sym_RBRACE,
    STATE(98), 1,
      aux_sym_type_decl_repeat1,
    STATE(197), 1,
      aux_sym_object_repeat1,
  [3635] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(365), 1,
      sym_identifier,
    ACTIONS(417), 1,
      anon_sym_RBRACE,
    STATE(248), 1,
      aux_sym_type_decl_repeat1,
    STATE(289), 1,
      sym_enum_val_decl,
  [3654] = 6,
    ACTIONS(43), 1,
      anon_sym_0,
    ACTIONS(45), 1,
      sym_hex_lit,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(248), 1,
      aux_sym_decimal_lit_token1,
    STATE(124), 1,
      sym_decimal_lit,
    STATE(344), 1,
      sym_int_lit,
  [3673] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      sym_documentation,
    ACTIONS(345), 1,
      anon_sym_COMMA,
    ACTIONS(419), 1,
      anon_sym_RBRACE,
    STATE(130), 1,
      aux_sym_type_decl_repeat1,
    STATE(268), 1,
      aux_sym_object_repeat1,
  [3692] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(351), 1,
      sym_identifier,
    ACTIONS(421), 1,
      anon_sym_RBRACE,
    STATE(246), 1,
      aux_sym_type_decl_repeat1,
    STATE(280), 1,
      sym_union_field_decl,
  [3711] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(423), 1,
      anon_sym_DQUOTE,
    ACTIONS(425), 1,
      aux_sym_string_constant_token1,
    ACTIONS(427), 1,
      sym_escape_sequence,
    STATE(174), 1,
      aux_sym_string_constant_repeat1,
  [3727] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(365), 1,
      sym_identifier,
    STATE(247), 1,
      sym_enum_val_decl,
    STATE(248), 1,
      aux_sym_type_decl_repeat1,
  [3743] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(371), 1,
      anon_sym_LPAREN,
    STATE(276), 1,
      sym_metadata,
    ACTIONS(429), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [3757] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(365), 1,
      sym_identifier,
    STATE(236), 1,
      sym_enum_val_decl,
    STATE(248), 1,
      aux_sym_type_decl_repeat1,
  [3773] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(365), 1,
      sym_identifier,
    STATE(207), 1,
      sym_enum_val_decl,
    STATE(248), 1,
      aux_sym_type_decl_repeat1,
  [3789] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(431), 1,
      anon_sym_DQUOTE,
    ACTIONS(433), 1,
      aux_sym_string_constant_token1,
    ACTIONS(435), 1,
      sym_escape_sequence,
    STATE(193), 1,
      aux_sym_string_constant_repeat1,
  [3805] = 5,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(371), 1,
      anon_sym_LPAREN,
    ACTIONS(437), 1,
      anon_sym_SEMI,
    ACTIONS(439), 1,
      anon_sym_EQ,
    STATE(335), 1,
      sym_metadata,
  [3821] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      sym_documentation,
    STATE(98), 1,
      aux_sym_type_decl_repeat1,
    ACTIONS(441), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [3835] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(443), 4,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [3845] = 5,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(371), 1,
      anon_sym_LPAREN,
    ACTIONS(445), 1,
      anon_sym_SEMI,
    ACTIONS(447), 1,
      anon_sym_EQ,
    STATE(321), 1,
      sym_metadata,
  [3861] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(449), 4,
      anon_sym_SEMI,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
  [3871] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(365), 1,
      sym_identifier,
    STATE(214), 1,
      sym_enum_val_decl,
    STATE(248), 1,
      aux_sym_type_decl_repeat1,
  [3887] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(451), 4,
      anon_sym_SEMI,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
  [3897] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      sym_documentation,
    STATE(176), 1,
      aux_sym_type_decl_repeat1,
    ACTIONS(453), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [3911] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(455), 4,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [3921] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(351), 1,
      sym_identifier,
    STATE(246), 1,
      aux_sym_type_decl_repeat1,
    STATE(280), 1,
      sym_union_field_decl,
  [3937] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(365), 1,
      sym_identifier,
    STATE(248), 1,
      aux_sym_type_decl_repeat1,
    STATE(289), 1,
      sym_enum_val_decl,
  [3953] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(457), 4,
      anon_sym_SEMI,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
  [3963] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(371), 1,
      anon_sym_LPAREN,
    STATE(285), 1,
      sym_metadata,
    ACTIONS(459), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [3977] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(111), 4,
      anon_sym_SEMI,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
  [3987] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(109), 4,
      anon_sym_SEMI,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
  [3997] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(109), 4,
      anon_sym_SEMI,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
  [4007] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(121), 4,
      anon_sym_SEMI,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
  [4017] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(461), 4,
      anon_sym_SEMI,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      anon_sym_LPAREN,
  [4027] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(463), 1,
      anon_sym_DQUOTE,
    ACTIONS(465), 1,
      aux_sym_string_constant_token1,
    ACTIONS(468), 1,
      sym_escape_sequence,
    STATE(193), 1,
      aux_sym_string_constant_repeat1,
  [4043] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(371), 1,
      anon_sym_LPAREN,
    ACTIONS(471), 1,
      anon_sym_SEMI,
    STATE(331), 1,
      sym_metadata,
  [4056] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(345), 1,
      anon_sym_COMMA,
    ACTIONS(473), 1,
      anon_sym_RBRACE,
    STATE(204), 1,
      aux_sym_object_repeat1,
  [4069] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(371), 1,
      anon_sym_LPAREN,
    ACTIONS(475), 1,
      anon_sym_LBRACE,
    STATE(310), 1,
      sym_metadata,
  [4082] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(345), 1,
      anon_sym_COMMA,
    ACTIONS(477), 1,
      anon_sym_RBRACE,
    STATE(204), 1,
      aux_sym_object_repeat1,
  [4095] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(479), 1,
      anon_sym_RBRACE,
    ACTIONS(481), 1,
      sym_identifier,
    STATE(286), 1,
      sym_full_ident,
  [4108] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(483), 1,
      anon_sym_RBRACE,
    ACTIONS(485), 1,
      anon_sym_COMMA,
    STATE(258), 1,
      aux_sym_union_decl_repeat2,
  [4121] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(487), 1,
      anon_sym_RBRACE,
    ACTIONS(489), 1,
      anon_sym_COMMA,
    STATE(220), 1,
      aux_sym_union_decl_repeat1,
  [4134] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(491), 1,
      anon_sym_RBRACE,
    ACTIONS(493), 1,
      anon_sym_COMMA,
    STATE(223), 1,
      aux_sym_union_decl_repeat2,
  [4147] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(495), 1,
      anon_sym_COMMA,
    ACTIONS(497), 1,
      anon_sym_RPAREN,
    STATE(239), 1,
      aux_sym_metadata_repeat1,
  [4160] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(499), 3,
      sym_documentation,
      anon_sym_RBRACE,
      sym_identifier,
  [4169] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(501), 1,
      anon_sym_RBRACE,
    ACTIONS(503), 1,
      anon_sym_COMMA,
    STATE(204), 1,
      aux_sym_object_repeat1,
  [4182] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(506), 1,
      anon_sym_RBRACE,
    ACTIONS(508), 1,
      anon_sym_COMMA,
    STATE(231), 1,
      aux_sym_enum_decl_repeat1,
  [4195] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(345), 1,
      anon_sym_COMMA,
    ACTIONS(510), 1,
      anon_sym_RBRACE,
    STATE(204), 1,
      aux_sym_object_repeat1,
  [4208] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(512), 1,
      anon_sym_RBRACE,
    ACTIONS(514), 1,
      anon_sym_COMMA,
    STATE(234), 1,
      aux_sym_enum_decl_repeat1,
  [4221] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(516), 1,
      anon_sym_RBRACE,
    ACTIONS(518), 1,
      anon_sym_COMMA,
    STATE(252), 1,
      aux_sym_union_decl_repeat1,
  [4234] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(481), 1,
      sym_identifier,
    ACTIONS(520), 1,
      anon_sym_RBRACE,
    STATE(286), 1,
      sym_full_ident,
  [4247] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(520), 1,
      anon_sym_RBRACE,
    ACTIONS(522), 1,
      anon_sym_COMMA,
    STATE(258), 1,
      aux_sym_union_decl_repeat2,
  [4260] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(524), 1,
      anon_sym_RBRACE,
    ACTIONS(526), 1,
      anon_sym_COMMA,
    STATE(259), 1,
      aux_sym_union_decl_repeat1,
  [4273] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(528), 1,
      anon_sym_RBRACE,
    ACTIONS(530), 1,
      anon_sym_COMMA,
    STATE(267), 1,
      aux_sym_union_decl_repeat2,
  [4286] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(481), 1,
      sym_identifier,
    ACTIONS(532), 1,
      anon_sym_RBRACE,
    STATE(286), 1,
      sym_full_ident,
  [4299] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(534), 1,
      anon_sym_RBRACE,
    ACTIONS(536), 1,
      anon_sym_COMMA,
    STATE(235), 1,
      aux_sym_enum_decl_repeat1,
  [4312] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(371), 1,
      anon_sym_LPAREN,
    ACTIONS(538), 1,
      anon_sym_LBRACE,
    STATE(343), 1,
      sym_metadata,
  [4325] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(371), 1,
      anon_sym_LPAREN,
    ACTIONS(540), 1,
      anon_sym_LBRACE,
    STATE(311), 1,
      sym_metadata,
  [4338] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(371), 1,
      anon_sym_LPAREN,
    ACTIONS(542), 1,
      anon_sym_LBRACE,
    STATE(323), 1,
      sym_metadata,
  [4351] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(371), 1,
      anon_sym_LPAREN,
    ACTIONS(544), 1,
      anon_sym_LBRACE,
    STATE(340), 1,
      sym_metadata,
  [4364] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(481), 1,
      sym_identifier,
    ACTIONS(546), 1,
      anon_sym_RBRACE,
    STATE(286), 1,
      sym_full_ident,
  [4377] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(548), 1,
      anon_sym_RBRACE,
    ACTIONS(550), 1,
      anon_sym_COMMA,
    STATE(252), 1,
      aux_sym_union_decl_repeat1,
  [4390] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(371), 1,
      anon_sym_LPAREN,
    ACTIONS(552), 1,
      anon_sym_LBRACE,
    STATE(298), 1,
      sym_metadata,
  [4403] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(481), 1,
      sym_identifier,
    ACTIONS(554), 1,
      anon_sym_RBRACE,
    STATE(286), 1,
      sym_full_ident,
  [4416] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(556), 1,
      anon_sym_RBRACE,
    ACTIONS(558), 1,
      anon_sym_COMMA,
    STATE(258), 1,
      aux_sym_union_decl_repeat2,
  [4429] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(560), 1,
      anon_sym_RBRACE,
    ACTIONS(562), 1,
      anon_sym_COMMA,
    STATE(269), 1,
      aux_sym_union_decl_repeat1,
  [4442] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(564), 1,
      anon_sym_RBRACE,
    ACTIONS(566), 1,
      anon_sym_COMMA,
    STATE(199), 1,
      aux_sym_union_decl_repeat2,
  [4455] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(371), 1,
      anon_sym_LPAREN,
    ACTIONS(568), 1,
      anon_sym_SEMI,
    STATE(334), 1,
      sym_metadata,
  [4468] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(570), 3,
      sym_documentation,
      anon_sym_RBRACE,
      sym_identifier,
  [4477] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(572), 3,
      sym_documentation,
      anon_sym_RBRACE,
      sym_identifier,
  [4486] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(574), 3,
      sym_documentation,
      anon_sym_RBRACE,
      sym_identifier,
  [4495] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(576), 1,
      sym_identifier,
    STATE(266), 1,
      aux_sym_type_decl_repeat1,
  [4508] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(578), 1,
      anon_sym_RBRACE,
    ACTIONS(580), 1,
      anon_sym_COMMA,
    STATE(231), 1,
      aux_sym_enum_decl_repeat1,
  [4521] = 3,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(583), 1,
      anon_sym_COLON,
    ACTIONS(585), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [4532] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(495), 1,
      anon_sym_COMMA,
    ACTIONS(587), 1,
      anon_sym_RPAREN,
    STATE(202), 1,
      aux_sym_metadata_repeat1,
  [4545] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(589), 1,
      anon_sym_RBRACE,
    ACTIONS(591), 1,
      anon_sym_COMMA,
    STATE(231), 1,
      aux_sym_enum_decl_repeat1,
  [4558] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(593), 1,
      anon_sym_RBRACE,
    ACTIONS(595), 1,
      anon_sym_COMMA,
    STATE(231), 1,
      aux_sym_enum_decl_repeat1,
  [4571] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(597), 1,
      anon_sym_RBRACE,
    ACTIONS(599), 1,
      anon_sym_COMMA,
    STATE(251), 1,
      aux_sym_enum_decl_repeat1,
  [4584] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(371), 1,
      anon_sym_LPAREN,
    ACTIONS(601), 1,
      anon_sym_LBRACE,
    STATE(325), 1,
      sym_metadata,
  [4597] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(603), 1,
      anon_sym_RBRACE,
    ACTIONS(605), 1,
      anon_sym_COMMA,
    STATE(208), 1,
      aux_sym_union_decl_repeat1,
  [4610] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(607), 1,
      anon_sym_COMMA,
    ACTIONS(610), 1,
      anon_sym_RPAREN,
    STATE(239), 1,
      aux_sym_metadata_repeat1,
  [4623] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(481), 1,
      sym_identifier,
    ACTIONS(612), 1,
      anon_sym_RBRACE,
    STATE(286), 1,
      sym_full_ident,
  [4636] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(614), 1,
      anon_sym_COMMA,
    ACTIONS(616), 1,
      anon_sym_RBRACK,
    STATE(253), 1,
      aux_sym_value_repeat1,
  [4649] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(618), 3,
      sym_documentation,
      anon_sym_RBRACE,
      sym_identifier,
  [4658] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(371), 1,
      anon_sym_LPAREN,
    ACTIONS(620), 1,
      anon_sym_SEMI,
    STATE(315), 1,
      sym_metadata,
  [4671] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(622), 3,
      sym_documentation,
      anon_sym_RBRACE,
      sym_identifier,
  [4680] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(624), 1,
      anon_sym_RBRACE,
    ACTIONS(626), 1,
      anon_sym_COMMA,
    STATE(210), 1,
      aux_sym_union_decl_repeat2,
  [4693] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(628), 1,
      sym_identifier,
    STATE(266), 1,
      aux_sym_type_decl_repeat1,
  [4706] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(630), 1,
      anon_sym_RBRACE,
    ACTIONS(632), 1,
      anon_sym_COMMA,
    STATE(205), 1,
      aux_sym_enum_decl_repeat1,
  [4719] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(634), 1,
      sym_identifier,
    STATE(266), 1,
      aux_sym_type_decl_repeat1,
  [4732] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(371), 1,
      anon_sym_LPAREN,
    ACTIONS(636), 1,
      anon_sym_SEMI,
    STATE(319), 1,
      sym_metadata,
  [4745] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_documentation,
    ACTIONS(638), 1,
      sym_identifier,
    STATE(266), 1,
      aux_sym_type_decl_repeat1,
  [4758] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(640), 1,
      anon_sym_RBRACE,
    ACTIONS(642), 1,
      anon_sym_COMMA,
    STATE(231), 1,
      aux_sym_enum_decl_repeat1,
  [4771] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(644), 1,
      anon_sym_RBRACE,
    ACTIONS(646), 1,
      anon_sym_COMMA,
    STATE(252), 1,
      aux_sym_union_decl_repeat1,
  [4784] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(614), 1,
      anon_sym_COMMA,
    ACTIONS(649), 1,
      anon_sym_RBRACK,
    STATE(260), 1,
      aux_sym_value_repeat1,
  [4797] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(651), 3,
      sym_documentation,
      anon_sym_RBRACE,
      sym_identifier,
  [4806] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(653), 3,
      sym_documentation,
      anon_sym_RBRACE,
      sym_identifier,
  [4815] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(655), 3,
      sym_documentation,
      anon_sym_RBRACE,
      sym_identifier,
  [4824] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(481), 1,
      sym_identifier,
    ACTIONS(657), 1,
      anon_sym_RBRACE,
    STATE(286), 1,
      sym_full_ident,
  [4837] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(659), 1,
      anon_sym_RBRACE,
    ACTIONS(661), 1,
      anon_sym_COMMA,
    STATE(258), 1,
      aux_sym_union_decl_repeat2,
  [4850] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(664), 1,
      anon_sym_RBRACE,
    ACTIONS(666), 1,
      anon_sym_COMMA,
    STATE(252), 1,
      aux_sym_union_decl_repeat1,
  [4863] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(668), 1,
      anon_sym_COMMA,
    ACTIONS(671), 1,
      anon_sym_RBRACK,
    STATE(260), 1,
      aux_sym_value_repeat1,
  [4876] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(673), 3,
      sym_documentation,
      anon_sym_RBRACE,
      sym_identifier,
  [4885] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(675), 3,
      sym_documentation,
      anon_sym_RBRACE,
      sym_identifier,
  [4894] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(677), 3,
      sym_documentation,
      anon_sym_RBRACE,
      sym_identifier,
  [4903] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(679), 3,
      sym_documentation,
      anon_sym_RBRACE,
      sym_identifier,
  [4912] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(481), 1,
      sym_identifier,
    ACTIONS(681), 1,
      anon_sym_RBRACE,
    STATE(286), 1,
      sym_full_ident,
  [4925] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(253), 1,
      sym_identifier,
    ACTIONS(683), 1,
      sym_documentation,
    STATE(266), 1,
      aux_sym_type_decl_repeat1,
  [4938] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(681), 1,
      anon_sym_RBRACE,
    ACTIONS(686), 1,
      anon_sym_COMMA,
    STATE(258), 1,
      aux_sym_union_decl_repeat2,
  [4951] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(345), 1,
      anon_sym_COMMA,
    ACTIONS(688), 1,
      anon_sym_RBRACE,
    STATE(204), 1,
      aux_sym_object_repeat1,
  [4964] = 4,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(690), 1,
      anon_sym_RBRACE,
    ACTIONS(692), 1,
      anon_sym_COMMA,
    STATE(252), 1,
      aux_sym_union_decl_repeat1,
  [4977] = 3,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(694), 1,
      anon_sym_COLON,
    ACTIONS(696), 1,
      anon_sym_RBRACK,
  [4987] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(698), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [4995] = 3,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(481), 1,
      sym_identifier,
    STATE(341), 1,
      sym_full_ident,
  [5005] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(700), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [5013] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(702), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [5021] = 3,
    ACTIONS(31), 1,
      anon_sym_DQUOTE,
    ACTIONS(53), 1,
      sym_comment,
    STATE(295), 1,
      sym_string_constant,
  [5031] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(704), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [5039] = 3,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(706), 1,
      anon_sym_DQUOTE,
    ACTIONS(708), 1,
      sym_identifier,
  [5049] = 3,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(710), 1,
      sym_identifier,
    STATE(273), 1,
      sym_field_and_value,
  [5059] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(712), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [5067] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(714), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [5075] = 3,
    ACTIONS(31), 1,
      anon_sym_DQUOTE,
    ACTIONS(53), 1,
      sym_comment,
    STATE(322), 1,
      sym_string_constant,
  [5085] = 3,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(710), 1,
      sym_identifier,
    STATE(233), 1,
      sym_field_and_value,
  [5095] = 3,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(481), 1,
      sym_identifier,
    STATE(286), 1,
      sym_full_ident,
  [5105] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(716), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [5113] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(718), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [5121] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(659), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [5129] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(720), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [5137] = 3,
    ACTIONS(31), 1,
      anon_sym_DQUOTE,
    ACTIONS(53), 1,
      sym_comment,
    STATE(313), 1,
      sym_string_constant,
  [5147] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(722), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [5155] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(259), 2,
      sym_documentation,
      sym_identifier,
  [5163] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(724), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [5171] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(726), 1,
      sym_identifier,
  [5178] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(728), 1,
      sym_identifier,
  [5185] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(730), 1,
      anon_sym_LBRACE,
  [5192] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(732), 1,
      anon_sym_SEMI,
  [5199] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(734), 1,
      sym_identifier,
  [5206] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(736), 1,
      sym_identifier,
  [5213] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(738), 1,
      anon_sym_LBRACE,
  [5220] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(740), 1,
      anon_sym_COLON,
  [5227] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(742), 1,
      sym_identifier,
  [5234] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(744), 1,
      sym_identifier,
  [5241] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(746), 1,
      anon_sym_LPAREN,
  [5248] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(748), 1,
      anon_sym_LPAREN,
  [5255] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(750), 1,
      sym_identifier,
  [5262] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(389), 1,
      anon_sym_COLON,
  [5269] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(752), 1,
      sym_identifier,
  [5276] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(754), 1,
      anon_sym_COLON,
  [5283] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(756), 1,
      sym_identifier,
  [5290] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(758), 1,
      sym_identifier,
  [5297] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(760), 1,
      anon_sym_LBRACE,
  [5304] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(762), 1,
      anon_sym_LBRACE,
  [5311] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(764), 1,
      anon_sym_RPAREN,
  [5318] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(766), 1,
      anon_sym_SEMI,
  [5325] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(768), 1,
      sym_identifier,
  [5332] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(770), 1,
      anon_sym_SEMI,
  [5339] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(772), 1,
      anon_sym_COLON,
  [5346] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(774), 1,
      anon_sym_SEMI,
  [5353] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(776), 1,
      sym_identifier,
  [5360] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(778), 1,
      anon_sym_SEMI,
  [5367] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(780), 1,
      anon_sym_LBRACE,
  [5374] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(782), 1,
      anon_sym_SEMI,
  [5381] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(784), 1,
      anon_sym_SEMI,
  [5388] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(786), 1,
      anon_sym_LBRACE,
  [5395] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(788), 1,
      sym_identifier,
  [5402] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(790), 1,
      anon_sym_LBRACE,
  [5409] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(792), 1,
      sym_identifier,
  [5416] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(794), 1,
      anon_sym_SEMI,
  [5423] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(796), 1,
      sym_identifier,
  [5430] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(798), 1,
      anon_sym_COLON,
  [5437] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(800), 1,
      anon_sym_COLON,
  [5444] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(802), 1,
      anon_sym_SEMI,
  [5451] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(804), 1,
      anon_sym_DQUOTE,
  [5458] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(806), 1,
      anon_sym_COLON,
  [5465] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(808), 1,
      anon_sym_SEMI,
  [5472] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(810), 1,
      anon_sym_SEMI,
  [5479] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(812), 1,
      anon_sym_SEMI,
  [5486] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(814), 1,
      ts_builtin_sym_end,
  [5493] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(816), 1,
      anon_sym_RPAREN,
  [5500] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(818), 1,
      sym_identifier,
  [5507] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(820), 1,
      anon_sym_LBRACE,
  [5514] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(822), 1,
      anon_sym_SEMI,
  [5521] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(824), 1,
      anon_sym_COLON,
  [5528] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(826), 1,
      anon_sym_LBRACE,
  [5535] = 2,
    ACTIONS(53), 1,
      sym_comment,
    ACTIONS(828), 1,
      anon_sym_RBRACK,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 79,
  [SMALL_STATE(4)] = 158,
  [SMALL_STATE(5)] = 237,
  [SMALL_STATE(6)] = 316,
  [SMALL_STATE(7)] = 380,
  [SMALL_STATE(8)] = 420,
  [SMALL_STATE(9)] = 460,
  [SMALL_STATE(10)] = 500,
  [SMALL_STATE(11)] = 540,
  [SMALL_STATE(12)] = 580,
  [SMALL_STATE(13)] = 620,
  [SMALL_STATE(14)] = 660,
  [SMALL_STATE(15)] = 717,
  [SMALL_STATE(16)] = 774,
  [SMALL_STATE(17)] = 831,
  [SMALL_STATE(18)] = 898,
  [SMALL_STATE(19)] = 924,
  [SMALL_STATE(20)] = 944,
  [SMALL_STATE(21)] = 963,
  [SMALL_STATE(22)] = 982,
  [SMALL_STATE(23)] = 1001,
  [SMALL_STATE(24)] = 1020,
  [SMALL_STATE(25)] = 1039,
  [SMALL_STATE(26)] = 1058,
  [SMALL_STATE(27)] = 1077,
  [SMALL_STATE(28)] = 1096,
  [SMALL_STATE(29)] = 1115,
  [SMALL_STATE(30)] = 1134,
  [SMALL_STATE(31)] = 1153,
  [SMALL_STATE(32)] = 1172,
  [SMALL_STATE(33)] = 1191,
  [SMALL_STATE(34)] = 1210,
  [SMALL_STATE(35)] = 1229,
  [SMALL_STATE(36)] = 1248,
  [SMALL_STATE(37)] = 1267,
  [SMALL_STATE(38)] = 1286,
  [SMALL_STATE(39)] = 1305,
  [SMALL_STATE(40)] = 1324,
  [SMALL_STATE(41)] = 1343,
  [SMALL_STATE(42)] = 1362,
  [SMALL_STATE(43)] = 1381,
  [SMALL_STATE(44)] = 1400,
  [SMALL_STATE(45)] = 1419,
  [SMALL_STATE(46)] = 1438,
  [SMALL_STATE(47)] = 1457,
  [SMALL_STATE(48)] = 1476,
  [SMALL_STATE(49)] = 1495,
  [SMALL_STATE(50)] = 1514,
  [SMALL_STATE(51)] = 1533,
  [SMALL_STATE(52)] = 1552,
  [SMALL_STATE(53)] = 1571,
  [SMALL_STATE(54)] = 1590,
  [SMALL_STATE(55)] = 1609,
  [SMALL_STATE(56)] = 1628,
  [SMALL_STATE(57)] = 1647,
  [SMALL_STATE(58)] = 1666,
  [SMALL_STATE(59)] = 1685,
  [SMALL_STATE(60)] = 1704,
  [SMALL_STATE(61)] = 1723,
  [SMALL_STATE(62)] = 1742,
  [SMALL_STATE(63)] = 1761,
  [SMALL_STATE(64)] = 1780,
  [SMALL_STATE(65)] = 1799,
  [SMALL_STATE(66)] = 1818,
  [SMALL_STATE(67)] = 1837,
  [SMALL_STATE(68)] = 1856,
  [SMALL_STATE(69)] = 1875,
  [SMALL_STATE(70)] = 1894,
  [SMALL_STATE(71)] = 1913,
  [SMALL_STATE(72)] = 1932,
  [SMALL_STATE(73)] = 1951,
  [SMALL_STATE(74)] = 1970,
  [SMALL_STATE(75)] = 1989,
  [SMALL_STATE(76)] = 2008,
  [SMALL_STATE(77)] = 2027,
  [SMALL_STATE(78)] = 2046,
  [SMALL_STATE(79)] = 2065,
  [SMALL_STATE(80)] = 2084,
  [SMALL_STATE(81)] = 2103,
  [SMALL_STATE(82)] = 2122,
  [SMALL_STATE(83)] = 2141,
  [SMALL_STATE(84)] = 2160,
  [SMALL_STATE(85)] = 2179,
  [SMALL_STATE(86)] = 2198,
  [SMALL_STATE(87)] = 2217,
  [SMALL_STATE(88)] = 2236,
  [SMALL_STATE(89)] = 2255,
  [SMALL_STATE(90)] = 2274,
  [SMALL_STATE(91)] = 2293,
  [SMALL_STATE(92)] = 2312,
  [SMALL_STATE(93)] = 2333,
  [SMALL_STATE(94)] = 2354,
  [SMALL_STATE(95)] = 2375,
  [SMALL_STATE(96)] = 2408,
  [SMALL_STATE(97)] = 2424,
  [SMALL_STATE(98)] = 2453,
  [SMALL_STATE(99)] = 2472,
  [SMALL_STATE(100)] = 2501,
  [SMALL_STATE(101)] = 2515,
  [SMALL_STATE(102)] = 2529,
  [SMALL_STATE(103)] = 2543,
  [SMALL_STATE(104)] = 2557,
  [SMALL_STATE(105)] = 2571,
  [SMALL_STATE(106)] = 2596,
  [SMALL_STATE(107)] = 2611,
  [SMALL_STATE(108)] = 2631,
  [SMALL_STATE(109)] = 2651,
  [SMALL_STATE(110)] = 2671,
  [SMALL_STATE(111)] = 2691,
  [SMALL_STATE(112)] = 2711,
  [SMALL_STATE(113)] = 2723,
  [SMALL_STATE(114)] = 2745,
  [SMALL_STATE(115)] = 2767,
  [SMALL_STATE(116)] = 2789,
  [SMALL_STATE(117)] = 2811,
  [SMALL_STATE(118)] = 2833,
  [SMALL_STATE(119)] = 2855,
  [SMALL_STATE(120)] = 2877,
  [SMALL_STATE(121)] = 2899,
  [SMALL_STATE(122)] = 2921,
  [SMALL_STATE(123)] = 2943,
  [SMALL_STATE(124)] = 2955,
  [SMALL_STATE(125)] = 2967,
  [SMALL_STATE(126)] = 2989,
  [SMALL_STATE(127)] = 3001,
  [SMALL_STATE(128)] = 3023,
  [SMALL_STATE(129)] = 3045,
  [SMALL_STATE(130)] = 3056,
  [SMALL_STATE(131)] = 3075,
  [SMALL_STATE(132)] = 3094,
  [SMALL_STATE(133)] = 3113,
  [SMALL_STATE(134)] = 3132,
  [SMALL_STATE(135)] = 3143,
  [SMALL_STATE(136)] = 3162,
  [SMALL_STATE(137)] = 3173,
  [SMALL_STATE(138)] = 3192,
  [SMALL_STATE(139)] = 3211,
  [SMALL_STATE(140)] = 3230,
  [SMALL_STATE(141)] = 3249,
  [SMALL_STATE(142)] = 3266,
  [SMALL_STATE(143)] = 3285,
  [SMALL_STATE(144)] = 3296,
  [SMALL_STATE(145)] = 3315,
  [SMALL_STATE(146)] = 3334,
  [SMALL_STATE(147)] = 3353,
  [SMALL_STATE(148)] = 3372,
  [SMALL_STATE(149)] = 3389,
  [SMALL_STATE(150)] = 3408,
  [SMALL_STATE(151)] = 3425,
  [SMALL_STATE(152)] = 3436,
  [SMALL_STATE(153)] = 3455,
  [SMALL_STATE(154)] = 3466,
  [SMALL_STATE(155)] = 3485,
  [SMALL_STATE(156)] = 3496,
  [SMALL_STATE(157)] = 3507,
  [SMALL_STATE(158)] = 3526,
  [SMALL_STATE(159)] = 3537,
  [SMALL_STATE(160)] = 3556,
  [SMALL_STATE(161)] = 3575,
  [SMALL_STATE(162)] = 3586,
  [SMALL_STATE(163)] = 3605,
  [SMALL_STATE(164)] = 3616,
  [SMALL_STATE(165)] = 3635,
  [SMALL_STATE(166)] = 3654,
  [SMALL_STATE(167)] = 3673,
  [SMALL_STATE(168)] = 3692,
  [SMALL_STATE(169)] = 3711,
  [SMALL_STATE(170)] = 3727,
  [SMALL_STATE(171)] = 3743,
  [SMALL_STATE(172)] = 3757,
  [SMALL_STATE(173)] = 3773,
  [SMALL_STATE(174)] = 3789,
  [SMALL_STATE(175)] = 3805,
  [SMALL_STATE(176)] = 3821,
  [SMALL_STATE(177)] = 3835,
  [SMALL_STATE(178)] = 3845,
  [SMALL_STATE(179)] = 3861,
  [SMALL_STATE(180)] = 3871,
  [SMALL_STATE(181)] = 3887,
  [SMALL_STATE(182)] = 3897,
  [SMALL_STATE(183)] = 3911,
  [SMALL_STATE(184)] = 3921,
  [SMALL_STATE(185)] = 3937,
  [SMALL_STATE(186)] = 3953,
  [SMALL_STATE(187)] = 3963,
  [SMALL_STATE(188)] = 3977,
  [SMALL_STATE(189)] = 3987,
  [SMALL_STATE(190)] = 3997,
  [SMALL_STATE(191)] = 4007,
  [SMALL_STATE(192)] = 4017,
  [SMALL_STATE(193)] = 4027,
  [SMALL_STATE(194)] = 4043,
  [SMALL_STATE(195)] = 4056,
  [SMALL_STATE(196)] = 4069,
  [SMALL_STATE(197)] = 4082,
  [SMALL_STATE(198)] = 4095,
  [SMALL_STATE(199)] = 4108,
  [SMALL_STATE(200)] = 4121,
  [SMALL_STATE(201)] = 4134,
  [SMALL_STATE(202)] = 4147,
  [SMALL_STATE(203)] = 4160,
  [SMALL_STATE(204)] = 4169,
  [SMALL_STATE(205)] = 4182,
  [SMALL_STATE(206)] = 4195,
  [SMALL_STATE(207)] = 4208,
  [SMALL_STATE(208)] = 4221,
  [SMALL_STATE(209)] = 4234,
  [SMALL_STATE(210)] = 4247,
  [SMALL_STATE(211)] = 4260,
  [SMALL_STATE(212)] = 4273,
  [SMALL_STATE(213)] = 4286,
  [SMALL_STATE(214)] = 4299,
  [SMALL_STATE(215)] = 4312,
  [SMALL_STATE(216)] = 4325,
  [SMALL_STATE(217)] = 4338,
  [SMALL_STATE(218)] = 4351,
  [SMALL_STATE(219)] = 4364,
  [SMALL_STATE(220)] = 4377,
  [SMALL_STATE(221)] = 4390,
  [SMALL_STATE(222)] = 4403,
  [SMALL_STATE(223)] = 4416,
  [SMALL_STATE(224)] = 4429,
  [SMALL_STATE(225)] = 4442,
  [SMALL_STATE(226)] = 4455,
  [SMALL_STATE(227)] = 4468,
  [SMALL_STATE(228)] = 4477,
  [SMALL_STATE(229)] = 4486,
  [SMALL_STATE(230)] = 4495,
  [SMALL_STATE(231)] = 4508,
  [SMALL_STATE(232)] = 4521,
  [SMALL_STATE(233)] = 4532,
  [SMALL_STATE(234)] = 4545,
  [SMALL_STATE(235)] = 4558,
  [SMALL_STATE(236)] = 4571,
  [SMALL_STATE(237)] = 4584,
  [SMALL_STATE(238)] = 4597,
  [SMALL_STATE(239)] = 4610,
  [SMALL_STATE(240)] = 4623,
  [SMALL_STATE(241)] = 4636,
  [SMALL_STATE(242)] = 4649,
  [SMALL_STATE(243)] = 4658,
  [SMALL_STATE(244)] = 4671,
  [SMALL_STATE(245)] = 4680,
  [SMALL_STATE(246)] = 4693,
  [SMALL_STATE(247)] = 4706,
  [SMALL_STATE(248)] = 4719,
  [SMALL_STATE(249)] = 4732,
  [SMALL_STATE(250)] = 4745,
  [SMALL_STATE(251)] = 4758,
  [SMALL_STATE(252)] = 4771,
  [SMALL_STATE(253)] = 4784,
  [SMALL_STATE(254)] = 4797,
  [SMALL_STATE(255)] = 4806,
  [SMALL_STATE(256)] = 4815,
  [SMALL_STATE(257)] = 4824,
  [SMALL_STATE(258)] = 4837,
  [SMALL_STATE(259)] = 4850,
  [SMALL_STATE(260)] = 4863,
  [SMALL_STATE(261)] = 4876,
  [SMALL_STATE(262)] = 4885,
  [SMALL_STATE(263)] = 4894,
  [SMALL_STATE(264)] = 4903,
  [SMALL_STATE(265)] = 4912,
  [SMALL_STATE(266)] = 4925,
  [SMALL_STATE(267)] = 4938,
  [SMALL_STATE(268)] = 4951,
  [SMALL_STATE(269)] = 4964,
  [SMALL_STATE(270)] = 4977,
  [SMALL_STATE(271)] = 4987,
  [SMALL_STATE(272)] = 4995,
  [SMALL_STATE(273)] = 5005,
  [SMALL_STATE(274)] = 5013,
  [SMALL_STATE(275)] = 5021,
  [SMALL_STATE(276)] = 5031,
  [SMALL_STATE(277)] = 5039,
  [SMALL_STATE(278)] = 5049,
  [SMALL_STATE(279)] = 5059,
  [SMALL_STATE(280)] = 5067,
  [SMALL_STATE(281)] = 5075,
  [SMALL_STATE(282)] = 5085,
  [SMALL_STATE(283)] = 5095,
  [SMALL_STATE(284)] = 5105,
  [SMALL_STATE(285)] = 5113,
  [SMALL_STATE(286)] = 5121,
  [SMALL_STATE(287)] = 5129,
  [SMALL_STATE(288)] = 5137,
  [SMALL_STATE(289)] = 5147,
  [SMALL_STATE(290)] = 5155,
  [SMALL_STATE(291)] = 5163,
  [SMALL_STATE(292)] = 5171,
  [SMALL_STATE(293)] = 5178,
  [SMALL_STATE(294)] = 5185,
  [SMALL_STATE(295)] = 5192,
  [SMALL_STATE(296)] = 5199,
  [SMALL_STATE(297)] = 5206,
  [SMALL_STATE(298)] = 5213,
  [SMALL_STATE(299)] = 5220,
  [SMALL_STATE(300)] = 5227,
  [SMALL_STATE(301)] = 5234,
  [SMALL_STATE(302)] = 5241,
  [SMALL_STATE(303)] = 5248,
  [SMALL_STATE(304)] = 5255,
  [SMALL_STATE(305)] = 5262,
  [SMALL_STATE(306)] = 5269,
  [SMALL_STATE(307)] = 5276,
  [SMALL_STATE(308)] = 5283,
  [SMALL_STATE(309)] = 5290,
  [SMALL_STATE(310)] = 5297,
  [SMALL_STATE(311)] = 5304,
  [SMALL_STATE(312)] = 5311,
  [SMALL_STATE(313)] = 5318,
  [SMALL_STATE(314)] = 5325,
  [SMALL_STATE(315)] = 5332,
  [SMALL_STATE(316)] = 5339,
  [SMALL_STATE(317)] = 5346,
  [SMALL_STATE(318)] = 5353,
  [SMALL_STATE(319)] = 5360,
  [SMALL_STATE(320)] = 5367,
  [SMALL_STATE(321)] = 5374,
  [SMALL_STATE(322)] = 5381,
  [SMALL_STATE(323)] = 5388,
  [SMALL_STATE(324)] = 5395,
  [SMALL_STATE(325)] = 5402,
  [SMALL_STATE(326)] = 5409,
  [SMALL_STATE(327)] = 5416,
  [SMALL_STATE(328)] = 5423,
  [SMALL_STATE(329)] = 5430,
  [SMALL_STATE(330)] = 5437,
  [SMALL_STATE(331)] = 5444,
  [SMALL_STATE(332)] = 5451,
  [SMALL_STATE(333)] = 5458,
  [SMALL_STATE(334)] = 5465,
  [SMALL_STATE(335)] = 5472,
  [SMALL_STATE(336)] = 5479,
  [SMALL_STATE(337)] = 5486,
  [SMALL_STATE(338)] = 5493,
  [SMALL_STATE(339)] = 5500,
  [SMALL_STATE(340)] = 5507,
  [SMALL_STATE(341)] = 5514,
  [SMALL_STATE(342)] = 5521,
  [SMALL_STATE(343)] = 5528,
  [SMALL_STATE(344)] = 5535,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0, 0, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(281),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(272),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(277),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(297),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(138),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(324),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(318),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(308),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(275),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(288),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(328),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(169),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(167),
  [35] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [37] = {.entry = {.count = 1, .reusable = false}}, SHIFT(93),
  [39] = {.entry = {.count = 1, .reusable = true}}, SHIFT(106),
  [41] = {.entry = {.count = 1, .reusable = false}}, SHIFT(151),
  [43] = {.entry = {.count = 1, .reusable = false}}, SHIFT(123),
  [45] = {.entry = {.count = 1, .reusable = true}}, SHIFT(124),
  [47] = {.entry = {.count = 1, .reusable = true}}, SHIFT(153),
  [49] = {.entry = {.count = 1, .reusable = false}}, SHIFT(155),
  [51] = {.entry = {.count = 1, .reusable = false}}, SHIFT(153),
  [53] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [55] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [57] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [59] = {.entry = {.count = 1, .reusable = false}}, SHIFT(103),
  [61] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 2, 0, 0),
  [63] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0),
  [65] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(102),
  [68] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(272),
  [71] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(277),
  [74] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(297),
  [77] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(138),
  [80] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(324),
  [83] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(318),
  [86] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(308),
  [89] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(275),
  [92] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(288),
  [95] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(328),
  [98] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [100] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(281),
  [103] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_include, 3, 0, 3),
  [105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_decl, 9, 0, 69),
  [107] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_decl, 11, 0, 88),
  [109] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_object, 3, 0, 6),
  [111] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_object, 2, 0, 0),
  [113] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_root_decl, 3, 0, 7),
  [115] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_file_extension_decl, 3, 0, 8),
  [117] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_file_identifier_decl, 3, 0, 9),
  [119] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_decl, 4, 0, 10),
  [121] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_object, 4, 0, 13),
  [123] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rpc_decl, 4, 0, 15),
  [125] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attribute_decl, 5, 0, 16),
  [127] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_decl, 5, 0, 17),
  [129] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_decl, 5, 0, 20),
  [131] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 5, 0, 21),
  [133] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 5, 0, 22),
  [135] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rpc_decl, 5, 0, 23),
  [137] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_decl, 5, 0, 24),
  [139] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rpc_decl, 5, 0, 25),
  [141] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_decl, 6, 0, 31),
  [143] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 6, 0, 21),
  [145] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 6, 0, 36),
  [147] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 6, 0, 38),
  [149] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 6, 0, 39),
  [151] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 6, 0, 40),
  [153] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_decl, 6, 0, 41),
  [155] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_decl, 6, 0, 42),
  [157] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 6, 0, 43),
  [159] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 6, 0, 44),
  [161] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rpc_decl, 6, 0, 45),
  [163] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_decl, 7, 0, 48),
  [165] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 7, 0, 36),
  [167] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 7, 0, 50),
  [169] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 7, 0, 39),
  [171] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 7, 0, 52),
  [173] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 7, 0, 53),
  [175] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_decl, 7, 0, 54),
  [177] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 7, 0, 43),
  [179] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 7, 0, 55),
  [181] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 7, 0, 56),
  [183] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 7, 0, 57),
  [185] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 7, 0, 58),
  [187] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_decl, 8, 0, 48),
  [189] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_decl, 8, 0, 66),
  [191] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_decl, 8, 0, 69),
  [193] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 8, 0, 52),
  [195] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 8, 0, 70),
  [197] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_decl, 8, 0, 71),
  [199] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 8, 0, 55),
  [201] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 8, 0, 72),
  [203] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 8, 0, 57),
  [205] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 8, 0, 73),
  [207] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 8, 0, 74),
  [209] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_decl, 9, 0, 66),
  [211] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_namespace_decl, 3, 0, 4),
  [213] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_decl, 9, 0, 79),
  [215] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_decl, 9, 0, 71),
  [217] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_decl, 9, 0, 80),
  [219] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_decl, 9, 0, 81),
  [221] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 9, 0, 73),
  [223] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_decl, 9, 0, 82),
  [225] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attribute_decl, 3, 0, 5),
  [227] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_decl, 10, 0, 79),
  [229] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_decl, 10, 0, 80),
  [231] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_decl, 10, 0, 81),
  [233] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_decl, 10, 0, 88),
  [235] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_full_ident_repeat1, 2, 0, 0),
  [237] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_full_ident_repeat1, 2, 0, 0), SHIFT_REPEAT(292),
  [240] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_full_ident, 1, 0, 0),
  [242] = {.entry = {.count = 1, .reusable = true}}, SHIFT(292),
  [244] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_full_ident, 2, 0, 0),
  [246] = {.entry = {.count = 1, .reusable = true}}, SHIFT(155),
  [248] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [250] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_type_decl_repeat1, 2, 0, 2), SHIFT_REPEAT(102),
  [253] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_type_decl_repeat1, 2, 0, 2),
  [255] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type, 3, 0, 32),
  [257] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type, 5, 0, 63),
  [259] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_type_decl_repeat1, 1, 0, 1),
  [261] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type, 1, 0, 0),
  [263] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type, 1, 0, 14),
  [265] = {.entry = {.count = 1, .reusable = true}}, SHIFT(314),
  [267] = {.entry = {.count = 1, .reusable = true}}, SHIFT(293),
  [269] = {.entry = {.count = 1, .reusable = true}}, SHIFT(296),
  [271] = {.entry = {.count = 1, .reusable = true}}, SHIFT(306),
  [273] = {.entry = {.count = 1, .reusable = true}}, SHIFT(309),
  [275] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_plus_minus_constant, 1, 0, 0),
  [277] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_plus_minus_constant, 1, 0, 0),
  [279] = {.entry = {.count = 1, .reusable = true}}, SHIFT(290),
  [281] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [283] = {.entry = {.count = 1, .reusable = true}}, SHIFT(302),
  [285] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [287] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_rpc_decl_repeat1, 2, 0, 0), SHIFT_REPEAT(290),
  [290] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_rpc_decl_repeat1, 2, 0, 0),
  [292] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_rpc_decl_repeat1, 2, 0, 0), SHIFT_REPEAT(302),
  [295] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [297] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [299] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_int_constant, 2, 0, 0),
  [301] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [303] = {.entry = {.count = 1, .reusable = true}}, SHIFT(329),
  [305] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [307] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [309] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [311] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [313] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [315] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_type_decl_repeat2, 2, 0, 18), SHIFT_REPEAT(290),
  [318] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_type_decl_repeat2, 2, 0, 18),
  [320] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_type_decl_repeat2, 2, 0, 18), SHIFT_REPEAT(329),
  [323] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [325] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [327] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [329] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_decimal_lit, 1, 0, 0),
  [331] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_int_lit, 1, 0, 0),
  [333] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [335] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_int_constant, 1, 0, 0),
  [337] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [339] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [341] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_scalar, 1, 0, 0),
  [343] = {.entry = {.count = 1, .reusable = true}}, SHIFT(189),
  [345] = {.entry = {.count = 1, .reusable = true}}, SHIFT(182),
  [347] = {.entry = {.count = 1, .reusable = true}}, SHIFT(150),
  [349] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [351] = {.entry = {.count = 1, .reusable = true}}, SHIFT(305),
  [353] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_constant, 3, 0, 0),
  [355] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [357] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_constant, 2, 0, 0),
  [359] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [361] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [363] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [365] = {.entry = {.count = 1, .reusable = true}}, SHIFT(141),
  [367] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_val_decl, 1, 0, 33),
  [369] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [371] = {.entry = {.count = 1, .reusable = true}}, SHIFT(282),
  [373] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [375] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_float_constant, 2, 0, 0),
  [377] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [379] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [381] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [383] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_val_decl, 2, 0, 49),
  [385] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [387] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [389] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [391] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bool_constant, 1, 0, 0),
  [393] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_float_lit, 1, 0, 0),
  [395] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [397] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_inf_token, 1, 0, 0),
  [399] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_single_value, 1, 0, 14),
  [401] = {.entry = {.count = 1, .reusable = true}}, SHIFT(88),
  [403] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_single_value, 1, 0, 27),
  [405] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [407] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [409] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_float_constant, 1, 0, 0),
  [411] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [413] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_single_value, 1, 0, 28),
  [415] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [417] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [419] = {.entry = {.count = 1, .reusable = true}}, SHIFT(188),
  [421] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [423] = {.entry = {.count = 1, .reusable = false}}, SHIFT(136),
  [425] = {.entry = {.count = 1, .reusable = false}}, SHIFT(174),
  [427] = {.entry = {.count = 1, .reusable = true}}, SHIFT(174),
  [429] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_val_decl, 3, 0, 64),
  [431] = {.entry = {.count = 1, .reusable = false}}, SHIFT(134),
  [433] = {.entry = {.count = 1, .reusable = false}}, SHIFT(193),
  [435] = {.entry = {.count = 1, .reusable = true}}, SHIFT(193),
  [437] = {.entry = {.count = 1, .reusable = true}}, SHIFT(203),
  [439] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [441] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_object_repeat1, 2, 0, 6),
  [443] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_metadata, 3, 0, 19),
  [445] = {.entry = {.count = 1, .reusable = true}}, SHIFT(228),
  [447] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [449] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_value, 3, 0, 83),
  [451] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_value, 1, 0, 59),
  [453] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_object_repeat1, 1, 0, 0),
  [455] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_metadata, 4, 0, 29),
  [457] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_value, 4, 0, 90),
  [459] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_val_decl, 4, 0, 78),
  [461] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_value, 1, 0, 60),
  [463] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_constant_repeat1, 2, 0, 0),
  [465] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_constant_repeat1, 2, 0, 0), SHIFT_REPEAT(193),
  [468] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_string_constant_repeat1, 2, 0, 0), SHIFT_REPEAT(193),
  [471] = {.entry = {.count = 1, .reusable = true}}, SHIFT(263),
  [473] = {.entry = {.count = 1, .reusable = true}}, SHIFT(191),
  [475] = {.entry = {.count = 1, .reusable = true}}, SHIFT(127),
  [477] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [479] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [481] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [483] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [485] = {.entry = {.count = 1, .reusable = true}}, SHIFT(219),
  [487] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [489] = {.entry = {.count = 1, .reusable = true}}, SHIFT(135),
  [491] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [493] = {.entry = {.count = 1, .reusable = true}}, SHIFT(222),
  [495] = {.entry = {.count = 1, .reusable = true}}, SHIFT(278),
  [497] = {.entry = {.count = 1, .reusable = true}}, SHIFT(183),
  [499] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_decl, 4, 0, 46),
  [501] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_object_repeat1, 2, 0, 2),
  [503] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_object_repeat1, 2, 0, 2), SHIFT_REPEAT(182),
  [506] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [508] = {.entry = {.count = 1, .reusable = true}}, SHIFT(140),
  [510] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [512] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [514] = {.entry = {.count = 1, .reusable = true}}, SHIFT(142),
  [516] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [518] = {.entry = {.count = 1, .reusable = true}}, SHIFT(160),
  [520] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [522] = {.entry = {.count = 1, .reusable = true}}, SHIFT(257),
  [524] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [526] = {.entry = {.count = 1, .reusable = true}}, SHIFT(144),
  [528] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [530] = {.entry = {.count = 1, .reusable = true}}, SHIFT(265),
  [532] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [534] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [536] = {.entry = {.count = 1, .reusable = true}}, SHIFT(146),
  [538] = {.entry = {.count = 1, .reusable = true}}, SHIFT(131),
  [540] = {.entry = {.count = 1, .reusable = true}}, SHIFT(116),
  [542] = {.entry = {.count = 1, .reusable = true}}, SHIFT(113),
  [544] = {.entry = {.count = 1, .reusable = true}}, SHIFT(133),
  [546] = {.entry = {.count = 1, .reusable = true}}, SHIFT(73),
  [548] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [550] = {.entry = {.count = 1, .reusable = true}}, SHIFT(149),
  [552] = {.entry = {.count = 1, .reusable = true}}, SHIFT(180),
  [554] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [556] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [558] = {.entry = {.count = 1, .reusable = true}}, SHIFT(240),
  [560] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [562] = {.entry = {.count = 1, .reusable = true}}, SHIFT(137),
  [564] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [566] = {.entry = {.count = 1, .reusable = true}}, SHIFT(198),
  [568] = {.entry = {.count = 1, .reusable = true}}, SHIFT(242),
  [570] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_decl, 5, 0, 61),
  [572] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_decl, 5, 0, 62),
  [574] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_type_decl_repeat2, 1, 0, 11),
  [576] = {.entry = {.count = 1, .reusable = true}}, SHIFT(299),
  [578] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_enum_decl_repeat1, 2, 0, 67),
  [580] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_enum_decl_repeat1, 2, 0, 67), SHIFT_REPEAT(185),
  [583] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [585] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_and_value, 1, 0, 12),
  [587] = {.entry = {.count = 1, .reusable = true}}, SHIFT(177),
  [589] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [591] = {.entry = {.count = 1, .reusable = true}}, SHIFT(154),
  [593] = {.entry = {.count = 1, .reusable = true}}, SHIFT(82),
  [595] = {.entry = {.count = 1, .reusable = true}}, SHIFT(157),
  [597] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [599] = {.entry = {.count = 1, .reusable = true}}, SHIFT(159),
  [601] = {.entry = {.count = 1, .reusable = true}}, SHIFT(170),
  [603] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [605] = {.entry = {.count = 1, .reusable = true}}, SHIFT(168),
  [607] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_metadata_repeat1, 2, 0, 30), SHIFT_REPEAT(278),
  [610] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_metadata_repeat1, 2, 0, 30),
  [612] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [614] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [616] = {.entry = {.count = 1, .reusable = true}}, SHIFT(179),
  [618] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_decl, 6, 0, 75),
  [620] = {.entry = {.count = 1, .reusable = true}}, SHIFT(255),
  [622] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_decl, 6, 0, 76),
  [624] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [626] = {.entry = {.count = 1, .reusable = true}}, SHIFT(209),
  [628] = {.entry = {.count = 1, .reusable = true}}, SHIFT(333),
  [630] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [632] = {.entry = {.count = 1, .reusable = true}}, SHIFT(147),
  [634] = {.entry = {.count = 1, .reusable = true}}, SHIFT(148),
  [636] = {.entry = {.count = 1, .reusable = true}}, SHIFT(256),
  [638] = {.entry = {.count = 1, .reusable = true}}, SHIFT(303),
  [640] = {.entry = {.count = 1, .reusable = true}}, SHIFT(90),
  [642] = {.entry = {.count = 1, .reusable = true}}, SHIFT(165),
  [644] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_union_decl_repeat1, 2, 0, 37),
  [646] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_union_decl_repeat1, 2, 0, 37), SHIFT_REPEAT(184),
  [649] = {.entry = {.count = 1, .reusable = true}}, SHIFT(186),
  [651] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_decl, 7, 0, 84),
  [653] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_decl, 7, 0, 85),
  [655] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rpc_method, 7, 0, 87),
  [657] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [659] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_union_decl_repeat2, 2, 0, 0),
  [661] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_union_decl_repeat2, 2, 0, 0), SHIFT_REPEAT(283),
  [664] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [666] = {.entry = {.count = 1, .reusable = true}}, SHIFT(162),
  [668] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_value_repeat1, 2, 0, 91), SHIFT_REPEAT(5),
  [671] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_value_repeat1, 2, 0, 91),
  [673] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_decl, 8, 0, 92),
  [675] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rpc_method, 8, 0, 93),
  [677] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rpc_method, 8, 0, 94),
  [679] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rpc_method, 9, 0, 95),
  [681] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [683] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_type_decl_repeat1, 2, 0, 2), SHIFT_REPEAT(290),
  [686] = {.entry = {.count = 1, .reusable = true}}, SHIFT(213),
  [688] = {.entry = {.count = 1, .reusable = true}}, SHIFT(190),
  [690] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [692] = {.entry = {.count = 1, .reusable = true}}, SHIFT(132),
  [694] = {.entry = {.count = 1, .reusable = true}}, SHIFT(166),
  [696] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [698] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_and_value, 3, 0, 26),
  [700] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_metadata_repeat1, 2, 0, 19),
  [702] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_val_decl, 2, 0, 47),
  [704] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_val_decl, 4, 0, 77),
  [706] = {.entry = {.count = 1, .reusable = true}}, SHIFT(304),
  [708] = {.entry = {.count = 1, .reusable = true}}, SHIFT(336),
  [710] = {.entry = {.count = 1, .reusable = true}}, SHIFT(232),
  [712] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_field_decl, 3, 0, 34),
  [714] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_union_decl_repeat1, 2, 0, 35),
  [716] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_union_field_decl, 4, 0, 51),
  [718] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_val_decl, 5, 0, 86),
  [720] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_value_repeat1, 2, 0, 89),
  [722] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_enum_decl_repeat1, 2, 0, 65),
  [724] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_val_decl, 3, 0, 68),
  [726] = {.entry = {.count = 1, .reusable = true}}, SHIFT(96),
  [728] = {.entry = {.count = 1, .reusable = true}}, SHIFT(217),
  [730] = {.entry = {.count = 1, .reusable = true}}, SHIFT(111),
  [732] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [734] = {.entry = {.count = 1, .reusable = true}}, SHIFT(330),
  [736] = {.entry = {.count = 1, .reusable = true}}, SHIFT(196),
  [738] = {.entry = {.count = 1, .reusable = true}}, SHIFT(172),
  [740] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [742] = {.entry = {.count = 1, .reusable = true}}, SHIFT(338),
  [744] = {.entry = {.count = 1, .reusable = true}}, SHIFT(194),
  [746] = {.entry = {.count = 1, .reusable = true}}, SHIFT(300),
  [748] = {.entry = {.count = 1, .reusable = true}}, SHIFT(339),
  [750] = {.entry = {.count = 1, .reusable = true}}, SHIFT(332),
  [752] = {.entry = {.count = 1, .reusable = true}}, SHIFT(218),
  [754] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [756] = {.entry = {.count = 1, .reusable = true}}, SHIFT(317),
  [758] = {.entry = {.count = 1, .reusable = true}}, SHIFT(294),
  [760] = {.entry = {.count = 1, .reusable = true}}, SHIFT(128),
  [762] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [764] = {.entry = {.count = 1, .reusable = true}}, SHIFT(342),
  [766] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [768] = {.entry = {.count = 1, .reusable = true}}, SHIFT(216),
  [770] = {.entry = {.count = 1, .reusable = true}}, SHIFT(261),
  [772] = {.entry = {.count = 1, .reusable = true}}, SHIFT(326),
  [774] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [776] = {.entry = {.count = 1, .reusable = true}}, SHIFT(215),
  [778] = {.entry = {.count = 1, .reusable = true}}, SHIFT(262),
  [780] = {.entry = {.count = 1, .reusable = true}}, SHIFT(110),
  [782] = {.entry = {.count = 1, .reusable = true}}, SHIFT(244),
  [784] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [786] = {.entry = {.count = 1, .reusable = true}}, SHIFT(118),
  [788] = {.entry = {.count = 1, .reusable = true}}, SHIFT(307),
  [790] = {.entry = {.count = 1, .reusable = true}}, SHIFT(173),
  [792] = {.entry = {.count = 1, .reusable = true}}, SHIFT(249),
  [794] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [796] = {.entry = {.count = 1, .reusable = true}}, SHIFT(320),
  [798] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [800] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [802] = {.entry = {.count = 1, .reusable = true}}, SHIFT(264),
  [804] = {.entry = {.count = 1, .reusable = true}}, SHIFT(327),
  [806] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [808] = {.entry = {.count = 1, .reusable = true}}, SHIFT(254),
  [810] = {.entry = {.count = 1, .reusable = true}}, SHIFT(227),
  [812] = {.entry = {.count = 1, .reusable = true}}, SHIFT(86),
  [814] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [816] = {.entry = {.count = 1, .reusable = true}}, SHIFT(316),
  [818] = {.entry = {.count = 1, .reusable = true}}, SHIFT(312),
  [820] = {.entry = {.count = 1, .reusable = true}}, SHIFT(145),
  [822] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [824] = {.entry = {.count = 1, .reusable = true}}, SHIFT(301),
  [826] = {.entry = {.count = 1, .reusable = true}}, SHIFT(152),
  [828] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
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

TS_PUBLIC const TSLanguage *tree_sitter_flatbuffers(void) {
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
