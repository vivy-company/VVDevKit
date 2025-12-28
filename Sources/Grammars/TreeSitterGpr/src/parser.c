#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 291
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 78
#define ALIAS_COUNT 0
#define TOKEN_COUNT 40
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 6
#define MAX_ALIAS_SEQUENCE_LENGTH 9
#define PRODUCTION_ID_COUNT 20

enum {
  aux_sym_with_declaration_token1 = 1,
  aux_sym_with_declaration_token2 = 2,
  anon_sym_COMMA = 3,
  anon_sym_SEMI = 4,
  aux_sym_project_declaration_token1 = 5,
  aux_sym_project_declaration_token2 = 6,
  aux_sym_project_declaration_token3 = 7,
  aux_sym_project_qualifier_token1 = 8,
  aux_sym_project_qualifier_token2 = 9,
  aux_sym_project_qualifier_token3 = 10,
  aux_sym_project_qualifier_token4 = 11,
  aux_sym_project_qualifier_token5 = 12,
  aux_sym__project_extension_token1 = 13,
  aux_sym__project_extension_token2 = 14,
  aux_sym_empty_declaration_token1 = 15,
  aux_sym_package_declaration_token1 = 16,
  aux_sym__package_renaming_token1 = 17,
  sym_string_literal = 18,
  aux_sym_string_literal_at_token1 = 19,
  anon_sym_LPAREN = 20,
  anon_sym_RPAREN = 21,
  anon_sym_SQUOTE = 22,
  anon_sym_AMP = 23,
  aux_sym_builtin_function_call_token1 = 24,
  aux_sym_builtin_function_call_token2 = 25,
  aux_sym_typed_string_declaration_token1 = 26,
  anon_sym_COLON = 27,
  anon_sym_COLON_EQ = 28,
  aux_sym_case_construction_token1 = 29,
  aux_sym_case_item_token1 = 30,
  anon_sym_EQ_GT = 31,
  anon_sym_PIPE = 32,
  aux_sym__others_designator_token1 = 33,
  aux_sym_attribute_declaration_token1 = 34,
  aux_sym_attribute_declaration_token2 = 35,
  anon_sym_DOT = 36,
  sym_identifier = 37,
  sym_numeric_literal = 38,
  sym_comment = 39,
  sym_project = 40,
  aux_sym__context_clause = 41,
  sym_with_declaration = 42,
  sym_project_declaration = 43,
  sym_project_qualifier = 44,
  sym__project_extension = 45,
  sym__declarative_item = 46,
  sym__simple_declarative_item = 47,
  sym_empty_declaration = 48,
  sym_package_declaration = 49,
  sym__package_spec = 50,
  sym__package_renaming = 51,
  sym__package_extension = 52,
  sym_string_literal_at = 53,
  sym_attribute_reference = 54,
  sym_variable_reference = 55,
  sym_project_reference = 56,
  sym_term = 57,
  sym_expression = 58,
  sym_expression_list = 59,
  sym_builtin_function_call = 60,
  sym_typed_string_declaration = 61,
  sym_variable_declaration = 62,
  sym_case_construction = 63,
  sym_case_item = 64,
  sym_discrete_choice_list = 65,
  sym__others_designator = 66,
  sym_attribute_declaration = 67,
  sym_associative_array_index = 68,
  sym_name = 69,
  aux_sym_project_repeat1 = 70,
  aux_sym_with_declaration_repeat1 = 71,
  aux_sym__package_spec_repeat1 = 72,
  aux_sym_expression_repeat1 = 73,
  aux_sym_expression_list_repeat1 = 74,
  aux_sym_case_construction_repeat1 = 75,
  aux_sym_discrete_choice_list_repeat1 = 76,
  aux_sym_name_repeat1 = 77,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [aux_sym_with_declaration_token1] = "limited",
  [aux_sym_with_declaration_token2] = "with",
  [anon_sym_COMMA] = ",",
  [anon_sym_SEMI] = ";",
  [aux_sym_project_declaration_token1] = "project",
  [aux_sym_project_declaration_token2] = "is",
  [aux_sym_project_declaration_token3] = "end",
  [aux_sym_project_qualifier_token1] = "standard",
  [aux_sym_project_qualifier_token2] = "abstract",
  [aux_sym_project_qualifier_token3] = "aggregate",
  [aux_sym_project_qualifier_token4] = "library",
  [aux_sym_project_qualifier_token5] = "configuration",
  [aux_sym__project_extension_token1] = "extends",
  [aux_sym__project_extension_token2] = "all",
  [aux_sym_empty_declaration_token1] = "null",
  [aux_sym_package_declaration_token1] = "package",
  [aux_sym__package_renaming_token1] = "renames",
  [sym_string_literal] = "string_literal",
  [aux_sym_string_literal_at_token1] = "at",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_SQUOTE] = "'",
  [anon_sym_AMP] = "&",
  [aux_sym_builtin_function_call_token1] = "external",
  [aux_sym_builtin_function_call_token2] = "external_as_list",
  [aux_sym_typed_string_declaration_token1] = "type",
  [anon_sym_COLON] = ":",
  [anon_sym_COLON_EQ] = ":=",
  [aux_sym_case_construction_token1] = "case",
  [aux_sym_case_item_token1] = "when",
  [anon_sym_EQ_GT] = "=>",
  [anon_sym_PIPE] = "|",
  [aux_sym__others_designator_token1] = "others",
  [aux_sym_attribute_declaration_token1] = "for",
  [aux_sym_attribute_declaration_token2] = "use",
  [anon_sym_DOT] = ".",
  [sym_identifier] = "identifier",
  [sym_numeric_literal] = "numeric_literal",
  [sym_comment] = "comment",
  [sym_project] = "project",
  [aux_sym__context_clause] = "_context_clause",
  [sym_with_declaration] = "with_declaration",
  [sym_project_declaration] = "project_declaration",
  [sym_project_qualifier] = "project_qualifier",
  [sym__project_extension] = "_project_extension",
  [sym__declarative_item] = "_declarative_item",
  [sym__simple_declarative_item] = "_simple_declarative_item",
  [sym_empty_declaration] = "empty_declaration",
  [sym_package_declaration] = "package_declaration",
  [sym__package_spec] = "_package_spec",
  [sym__package_renaming] = "_package_renaming",
  [sym__package_extension] = "_package_extension",
  [sym_string_literal_at] = "string_literal_at",
  [sym_attribute_reference] = "attribute_reference",
  [sym_variable_reference] = "variable_reference",
  [sym_project_reference] = "project_reference",
  [sym_term] = "term",
  [sym_expression] = "expression",
  [sym_expression_list] = "expression_list",
  [sym_builtin_function_call] = "builtin_function_call",
  [sym_typed_string_declaration] = "typed_string_declaration",
  [sym_variable_declaration] = "variable_declaration",
  [sym_case_construction] = "case_construction",
  [sym_case_item] = "case_item",
  [sym_discrete_choice_list] = "discrete_choice_list",
  [sym__others_designator] = "_others_designator",
  [sym_attribute_declaration] = "attribute_declaration",
  [sym_associative_array_index] = "associative_array_index",
  [sym_name] = "name",
  [aux_sym_project_repeat1] = "project_repeat1",
  [aux_sym_with_declaration_repeat1] = "with_declaration_repeat1",
  [aux_sym__package_spec_repeat1] = "_package_spec_repeat1",
  [aux_sym_expression_repeat1] = "expression_repeat1",
  [aux_sym_expression_list_repeat1] = "expression_list_repeat1",
  [aux_sym_case_construction_repeat1] = "case_construction_repeat1",
  [aux_sym_discrete_choice_list_repeat1] = "discrete_choice_list_repeat1",
  [aux_sym_name_repeat1] = "name_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [aux_sym_with_declaration_token1] = aux_sym_with_declaration_token1,
  [aux_sym_with_declaration_token2] = aux_sym_with_declaration_token2,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [aux_sym_project_declaration_token1] = aux_sym_project_declaration_token1,
  [aux_sym_project_declaration_token2] = aux_sym_project_declaration_token2,
  [aux_sym_project_declaration_token3] = aux_sym_project_declaration_token3,
  [aux_sym_project_qualifier_token1] = aux_sym_project_qualifier_token1,
  [aux_sym_project_qualifier_token2] = aux_sym_project_qualifier_token2,
  [aux_sym_project_qualifier_token3] = aux_sym_project_qualifier_token3,
  [aux_sym_project_qualifier_token4] = aux_sym_project_qualifier_token4,
  [aux_sym_project_qualifier_token5] = aux_sym_project_qualifier_token5,
  [aux_sym__project_extension_token1] = aux_sym__project_extension_token1,
  [aux_sym__project_extension_token2] = aux_sym__project_extension_token2,
  [aux_sym_empty_declaration_token1] = aux_sym_empty_declaration_token1,
  [aux_sym_package_declaration_token1] = aux_sym_package_declaration_token1,
  [aux_sym__package_renaming_token1] = aux_sym__package_renaming_token1,
  [sym_string_literal] = sym_string_literal,
  [aux_sym_string_literal_at_token1] = aux_sym_string_literal_at_token1,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_SQUOTE] = anon_sym_SQUOTE,
  [anon_sym_AMP] = anon_sym_AMP,
  [aux_sym_builtin_function_call_token1] = aux_sym_builtin_function_call_token1,
  [aux_sym_builtin_function_call_token2] = aux_sym_builtin_function_call_token2,
  [aux_sym_typed_string_declaration_token1] = aux_sym_typed_string_declaration_token1,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_COLON_EQ] = anon_sym_COLON_EQ,
  [aux_sym_case_construction_token1] = aux_sym_case_construction_token1,
  [aux_sym_case_item_token1] = aux_sym_case_item_token1,
  [anon_sym_EQ_GT] = anon_sym_EQ_GT,
  [anon_sym_PIPE] = anon_sym_PIPE,
  [aux_sym__others_designator_token1] = aux_sym__others_designator_token1,
  [aux_sym_attribute_declaration_token1] = aux_sym_attribute_declaration_token1,
  [aux_sym_attribute_declaration_token2] = aux_sym_attribute_declaration_token2,
  [anon_sym_DOT] = anon_sym_DOT,
  [sym_identifier] = sym_identifier,
  [sym_numeric_literal] = sym_numeric_literal,
  [sym_comment] = sym_comment,
  [sym_project] = sym_project,
  [aux_sym__context_clause] = aux_sym__context_clause,
  [sym_with_declaration] = sym_with_declaration,
  [sym_project_declaration] = sym_project_declaration,
  [sym_project_qualifier] = sym_project_qualifier,
  [sym__project_extension] = sym__project_extension,
  [sym__declarative_item] = sym__declarative_item,
  [sym__simple_declarative_item] = sym__simple_declarative_item,
  [sym_empty_declaration] = sym_empty_declaration,
  [sym_package_declaration] = sym_package_declaration,
  [sym__package_spec] = sym__package_spec,
  [sym__package_renaming] = sym__package_renaming,
  [sym__package_extension] = sym__package_extension,
  [sym_string_literal_at] = sym_string_literal_at,
  [sym_attribute_reference] = sym_attribute_reference,
  [sym_variable_reference] = sym_variable_reference,
  [sym_project_reference] = sym_project_reference,
  [sym_term] = sym_term,
  [sym_expression] = sym_expression,
  [sym_expression_list] = sym_expression_list,
  [sym_builtin_function_call] = sym_builtin_function_call,
  [sym_typed_string_declaration] = sym_typed_string_declaration,
  [sym_variable_declaration] = sym_variable_declaration,
  [sym_case_construction] = sym_case_construction,
  [sym_case_item] = sym_case_item,
  [sym_discrete_choice_list] = sym_discrete_choice_list,
  [sym__others_designator] = sym__others_designator,
  [sym_attribute_declaration] = sym_attribute_declaration,
  [sym_associative_array_index] = sym_associative_array_index,
  [sym_name] = sym_name,
  [aux_sym_project_repeat1] = aux_sym_project_repeat1,
  [aux_sym_with_declaration_repeat1] = aux_sym_with_declaration_repeat1,
  [aux_sym__package_spec_repeat1] = aux_sym__package_spec_repeat1,
  [aux_sym_expression_repeat1] = aux_sym_expression_repeat1,
  [aux_sym_expression_list_repeat1] = aux_sym_expression_list_repeat1,
  [aux_sym_case_construction_repeat1] = aux_sym_case_construction_repeat1,
  [aux_sym_discrete_choice_list_repeat1] = aux_sym_discrete_choice_list_repeat1,
  [aux_sym_name_repeat1] = aux_sym_name_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [aux_sym_with_declaration_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_with_declaration_token2] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SEMI] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_project_declaration_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_project_declaration_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_project_declaration_token3] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_project_qualifier_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_project_qualifier_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_project_qualifier_token3] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_project_qualifier_token4] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_project_qualifier_token5] = {
    .visible = true,
    .named = false,
  },
  [aux_sym__project_extension_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym__project_extension_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_empty_declaration_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_package_declaration_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym__package_renaming_token1] = {
    .visible = true,
    .named = false,
  },
  [sym_string_literal] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_string_literal_at_token1] = {
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
  [anon_sym_SQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_AMP] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_builtin_function_call_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_builtin_function_call_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_typed_string_declaration_token1] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON_EQ] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_case_construction_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_case_item_token1] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PIPE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym__others_designator_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_attribute_declaration_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_attribute_declaration_token2] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOT] = {
    .visible = true,
    .named = false,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [sym_numeric_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_project] = {
    .visible = true,
    .named = true,
  },
  [aux_sym__context_clause] = {
    .visible = false,
    .named = false,
  },
  [sym_with_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_project_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_project_qualifier] = {
    .visible = true,
    .named = true,
  },
  [sym__project_extension] = {
    .visible = false,
    .named = true,
  },
  [sym__declarative_item] = {
    .visible = false,
    .named = true,
  },
  [sym__simple_declarative_item] = {
    .visible = false,
    .named = true,
  },
  [sym_empty_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_package_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym__package_spec] = {
    .visible = false,
    .named = true,
  },
  [sym__package_renaming] = {
    .visible = false,
    .named = true,
  },
  [sym__package_extension] = {
    .visible = false,
    .named = true,
  },
  [sym_string_literal_at] = {
    .visible = true,
    .named = true,
  },
  [sym_attribute_reference] = {
    .visible = true,
    .named = true,
  },
  [sym_variable_reference] = {
    .visible = true,
    .named = true,
  },
  [sym_project_reference] = {
    .visible = true,
    .named = true,
  },
  [sym_term] = {
    .visible = true,
    .named = true,
  },
  [sym_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_expression_list] = {
    .visible = true,
    .named = true,
  },
  [sym_builtin_function_call] = {
    .visible = true,
    .named = true,
  },
  [sym_typed_string_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_variable_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_case_construction] = {
    .visible = true,
    .named = true,
  },
  [sym_case_item] = {
    .visible = true,
    .named = true,
  },
  [sym_discrete_choice_list] = {
    .visible = true,
    .named = true,
  },
  [sym__others_designator] = {
    .visible = false,
    .named = true,
  },
  [sym_attribute_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_associative_array_index] = {
    .visible = true,
    .named = true,
  },
  [sym_name] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_project_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_with_declaration_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__package_spec_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_expression_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_expression_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_case_construction_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_discrete_choice_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_name_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum {
  field_basename = 1,
  field_endname = 2,
  field_name = 3,
  field_origname = 4,
  field_type = 5,
  field_value = 6,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_basename] = "basename",
  [field_endname] = "endname",
  [field_name] = "name",
  [field_origname] = "origname",
  [field_type] = "type",
  [field_value] = "value",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 1},
  [3] = {.index = 2, .length = 3},
  [4] = {.index = 5, .length = 2},
  [5] = {.index = 7, .length = 1},
  [6] = {.index = 8, .length = 1},
  [7] = {.index = 9, .length = 2},
  [8] = {.index = 11, .length = 2},
  [9] = {.index = 13, .length = 1},
  [10] = {.index = 14, .length = 2},
  [11] = {.index = 16, .length = 2},
  [12] = {.index = 18, .length = 2},
  [13] = {.index = 20, .length = 2},
  [14] = {.index = 22, .length = 1},
  [15] = {.index = 23, .length = 2},
  [16] = {.index = 25, .length = 2},
  [17] = {.index = 27, .length = 2},
  [18] = {.index = 29, .length = 2},
  [19] = {.index = 31, .length = 2},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_basename, 1},
  [1] =
    {field_origname, 1},
  [2] =
    {field_basename, 2, .inherited = true},
    {field_endname, 2, .inherited = true},
    {field_name, 1},
  [5] =
    {field_name, 1},
    {field_origname, 2, .inherited = true},
  [7] =
    {field_name, 0},
  [8] =
    {field_endname, 2},
  [9] =
    {field_name, 1},
    {field_value, 3},
  [11] =
    {field_endname, 4},
    {field_name, 1},
  [13] =
    {field_endname, 3},
  [14] =
    {field_basename, 0, .inherited = true},
    {field_endname, 3},
  [16] =
    {field_name, 0},
    {field_type, 2},
  [18] =
    {field_endname, 5},
    {field_name, 1},
  [20] =
    {field_basename, 0, .inherited = true},
    {field_endname, 4},
  [22] =
    {field_name, 1},
  [23] =
    {field_endname, 5},
    {field_name, 2},
  [25] =
    {field_endname, 6},
    {field_name, 1},
  [27] =
    {field_name, 1},
    {field_value, 6},
  [29] =
    {field_endname, 6},
    {field_name, 2},
  [31] =
    {field_endname, 7},
    {field_name, 2},
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
  [9] = 2,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 16,
  [18] = 14,
  [19] = 19,
  [20] = 20,
  [21] = 14,
  [22] = 19,
  [23] = 20,
  [24] = 14,
  [25] = 20,
  [26] = 16,
  [27] = 19,
  [28] = 19,
  [29] = 20,
  [30] = 16,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 35,
  [36] = 36,
  [37] = 33,
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
  [51] = 49,
  [52] = 52,
  [53] = 53,
  [54] = 54,
  [55] = 55,
  [56] = 53,
  [57] = 57,
  [58] = 58,
  [59] = 50,
  [60] = 58,
  [61] = 57,
  [62] = 54,
  [63] = 55,
  [64] = 64,
  [65] = 65,
  [66] = 65,
  [67] = 52,
  [68] = 68,
  [69] = 68,
  [70] = 70,
  [71] = 64,
  [72] = 50,
  [73] = 68,
  [74] = 74,
  [75] = 57,
  [76] = 58,
  [77] = 77,
  [78] = 53,
  [79] = 55,
  [80] = 65,
  [81] = 81,
  [82] = 81,
  [83] = 83,
  [84] = 84,
  [85] = 85,
  [86] = 53,
  [87] = 58,
  [88] = 85,
  [89] = 57,
  [90] = 68,
  [91] = 50,
  [92] = 92,
  [93] = 85,
  [94] = 94,
  [95] = 95,
  [96] = 65,
  [97] = 97,
  [98] = 55,
  [99] = 85,
  [100] = 100,
  [101] = 101,
  [102] = 102,
  [103] = 103,
  [104] = 104,
  [105] = 105,
  [106] = 100,
  [107] = 100,
  [108] = 104,
  [109] = 109,
  [110] = 110,
  [111] = 104,
  [112] = 112,
  [113] = 113,
  [114] = 114,
  [115] = 100,
  [116] = 116,
  [117] = 117,
  [118] = 104,
  [119] = 119,
  [120] = 120,
  [121] = 121,
  [122] = 122,
  [123] = 123,
  [124] = 124,
  [125] = 125,
  [126] = 125,
  [127] = 127,
  [128] = 127,
  [129] = 129,
  [130] = 130,
  [131] = 131,
  [132] = 132,
  [133] = 127,
  [134] = 120,
  [135] = 135,
  [136] = 136,
  [137] = 137,
  [138] = 127,
  [139] = 139,
  [140] = 140,
  [141] = 141,
  [142] = 142,
  [143] = 143,
  [144] = 144,
  [145] = 145,
  [146] = 146,
  [147] = 145,
  [148] = 145,
  [149] = 149,
  [150] = 150,
  [151] = 151,
  [152] = 150,
  [153] = 149,
  [154] = 150,
  [155] = 155,
  [156] = 149,
  [157] = 150,
  [158] = 149,
  [159] = 145,
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
  [198] = 171,
  [199] = 199,
  [200] = 200,
  [201] = 201,
  [202] = 202,
  [203] = 203,
  [204] = 204,
  [205] = 205,
  [206] = 203,
  [207] = 171,
  [208] = 188,
  [209] = 177,
  [210] = 210,
  [211] = 211,
  [212] = 212,
  [213] = 213,
  [214] = 173,
  [215] = 204,
  [216] = 216,
  [217] = 188,
  [218] = 177,
  [219] = 210,
  [220] = 212,
  [221] = 173,
  [222] = 204,
  [223] = 171,
  [224] = 188,
  [225] = 177,
  [226] = 210,
  [227] = 212,
  [228] = 173,
  [229] = 205,
  [230] = 230,
  [231] = 231,
  [232] = 191,
  [233] = 233,
  [234] = 234,
  [235] = 231,
  [236] = 236,
  [237] = 237,
  [238] = 213,
  [239] = 239,
  [240] = 191,
  [241] = 210,
  [242] = 231,
  [243] = 243,
  [244] = 244,
  [245] = 245,
  [246] = 191,
  [247] = 247,
  [248] = 231,
  [249] = 249,
  [250] = 250,
  [251] = 251,
  [252] = 252,
  [253] = 253,
  [254] = 200,
  [255] = 192,
  [256] = 256,
  [257] = 257,
  [258] = 257,
  [259] = 259,
  [260] = 260,
  [261] = 200,
  [262] = 211,
  [263] = 257,
  [264] = 264,
  [265] = 265,
  [266] = 266,
  [267] = 200,
  [268] = 268,
  [269] = 257,
  [270] = 266,
  [271] = 244,
  [272] = 272,
  [273] = 201,
  [274] = 189,
  [275] = 266,
  [276] = 244,
  [277] = 277,
  [278] = 189,
  [279] = 266,
  [280] = 244,
  [281] = 212,
  [282] = 189,
  [283] = 250,
  [284] = 245,
  [285] = 204,
  [286] = 286,
  [287] = 287,
  [288] = 288,
  [289] = 289,
  [290] = 268,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(113);
      if (lookahead == '"') ADVANCE(2);
      if (lookahead == '&') ADVANCE(147);
      if (lookahead == '\'') ADVANCE(146);
      if (lookahead == '(') ADVANCE(144);
      if (lookahead == ')') ADVANCE(145);
      if (lookahead == ',') ADVANCE(118);
      if (lookahead == '-') ADVANCE(8);
      if (lookahead == '.') ADVANCE(166);
      if (lookahead == ':') ADVANCE(154);
      if (lookahead == ';') ADVANCE(119);
      if (lookahead == '=') ADVANCE(9);
      if (lookahead == '|') ADVANCE(161);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(23);
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(20);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(67);
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(75);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(87);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(54);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(107);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(96);
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(11);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(40);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(97);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(109);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(92);
      if (lookahead == 'W' ||
          lookahead == 'w') ADVANCE(53);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(0)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(257);
      END_STATE();
    case 1:
      if (lookahead == '"') ADVANCE(2);
      if (lookahead == '(') ADVANCE(144);
      if (lookahead == ')') ADVANCE(145);
      if (lookahead == '-') ADVANCE(8);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(253);
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(229);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(1)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 2:
      if (lookahead == '"') ADVANCE(142);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(2);
      END_STATE();
    case 3:
      if (lookahead == '-') ADVANCE(8);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(181);
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(170);
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(224);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(206);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(251);
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(168);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(241);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(254);
      if (lookahead == 'W' ||
          lookahead == 'w') ADVANCE(207);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(3)
      if (('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 4:
      if (lookahead == '-') ADVANCE(8);
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(171);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(222);
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(224);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(251);
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(169);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(254);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(4)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 5:
      if (lookahead == '-') ADVANCE(8);
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(171);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(222);
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(224);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(251);
      if (lookahead == 'W' ||
          lookahead == 'w') ADVANCE(205);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(5)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 6:
      if (lookahead == '-') ADVANCE(8);
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(171);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(222);
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(224);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(251);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(6)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 7:
      if (lookahead == '-') ADVANCE(8);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(7)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 8:
      if (lookahead == '-') ADVANCE(258);
      END_STATE();
    case 9:
      if (lookahead == '>') ADVANCE(160);
      END_STATE();
    case 10:
      if (lookahead == '_') ADVANCE(65);
      END_STATE();
    case 11:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(25);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(76);
      END_STATE();
    case 12:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(66);
      END_STATE();
    case 13:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(71);
      END_STATE();
    case 14:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(50);
      END_STATE();
    case 15:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(63);
      END_STATE();
    case 16:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(80);
      END_STATE();
    case 17:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(83);
      END_STATE();
    case 18:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(91);
      END_STATE();
    case 19:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(102);
      END_STATE();
    case 20:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(93);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(68);
      END_STATE();
    case 21:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(27);
      END_STATE();
    case 22:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(105);
      END_STATE();
    case 23:
      if (lookahead == 'B' ||
          lookahead == 'b') ADVANCE(94);
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(48);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(61);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(143);
      END_STATE();
    case 24:
      if (lookahead == 'B' ||
          lookahead == 'b') ADVANCE(81);
      if (lookahead == 'M' ||
          lookahead == 'm') ADVANCE(58);
      END_STATE();
    case 25:
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(60);
      END_STATE();
    case 26:
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(98);
      END_STATE();
    case 27:
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(99);
      END_STATE();
    case 28:
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(123);
      END_STATE();
    case 29:
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(114);
      END_STATE();
    case 30:
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(125);
      END_STATE();
    case 31:
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(89);
      END_STATE();
    case 32:
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(17);
      END_STATE();
    case 33:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(165);
      END_STATE();
    case 34:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(156);
      END_STATE();
    case 35:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(73);
      END_STATE();
    case 36:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(152);
      END_STATE();
    case 37:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(139);
      END_STATE();
    case 38:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(129);
      END_STATE();
    case 39:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(49);
      END_STATE();
    case 40:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(72);
      END_STATE();
    case 41:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(26);
      END_STATE();
    case 42:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(69);
      END_STATE();
    case 43:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(29);
      END_STATE();
    case 44:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(82);
      END_STATE();
    case 45:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(90);
      END_STATE();
    case 46:
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(56);
      END_STATE();
    case 47:
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(108);
      END_STATE();
    case 48:
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(85);
      END_STATE();
    case 49:
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(22);
      END_STATE();
    case 50:
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(37);
      END_STATE();
    case 51:
      if (lookahead == 'H' ||
          lookahead == 'h') ADVANCE(116);
      END_STATE();
    case 52:
      if (lookahead == 'H' ||
          lookahead == 'h') ADVANCE(44);
      END_STATE();
    case 53:
      if (lookahead == 'H' ||
          lookahead == 'h') ADVANCE(42);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(101);
      END_STATE();
    case 54:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(24);
      END_STATE();
    case 55:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(77);
      END_STATE();
    case 56:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(47);
      END_STATE();
    case 57:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(95);
      END_STATE();
    case 58:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(104);
      END_STATE();
    case 59:
      if (lookahead == 'J' ||
          lookahead == 'j') ADVANCE(41);
      END_STATE();
    case 60:
      if (lookahead == 'K' ||
          lookahead == 'k') ADVANCE(14);
      END_STATE();
    case 61:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(136);
      END_STATE();
    case 62:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(137);
      END_STATE();
    case 63:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(148);
      END_STATE();
    case 64:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(62);
      END_STATE();
    case 65:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(57);
      END_STATE();
    case 66:
      if (lookahead == 'M' ||
          lookahead == 'm') ADVANCE(45);
      END_STATE();
    case 67:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(28);
      if (lookahead == 'X' ||
          lookahead == 'x') ADVANCE(103);
      END_STATE();
    case 68:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(46);
      END_STATE();
    case 69:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(158);
      END_STATE();
    case 70:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(133);
      END_STATE();
    case 71:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(32);
      END_STATE();
    case 72:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(12);
      END_STATE();
    case 73:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(31);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(74);
      END_STATE();
    case 74:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(15);
      END_STATE();
    case 75:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(79);
      END_STATE();
    case 76:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(59);
      END_STATE();
    case 77:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(70);
      END_STATE();
    case 78:
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(36);
      END_STATE();
    case 79:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(163);
      END_STATE();
    case 80:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(110);
      END_STATE();
    case 81:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(16);
      END_STATE();
    case 82:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(88);
      END_STATE();
    case 83:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(30);
      END_STATE();
    case 84:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(21);
      END_STATE();
    case 85:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(39);
      END_STATE();
    case 86:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(19);
      END_STATE();
    case 87:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(122);
      END_STATE();
    case 88:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(162);
      END_STATE();
    case 89:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(135);
      END_STATE();
    case 90:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(141);
      END_STATE();
    case 91:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(10);
      END_STATE();
    case 92:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(33);
      END_STATE();
    case 93:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(34);
      END_STATE();
    case 94:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(106);
      END_STATE();
    case 95:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(100);
      END_STATE();
    case 96:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(52);
      END_STATE();
    case 97:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(13);
      END_STATE();
    case 98:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(120);
      END_STATE();
    case 99:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(127);
      END_STATE();
    case 100:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(150);
      END_STATE();
    case 101:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(51);
      END_STATE();
    case 102:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(55);
      END_STATE();
    case 103:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(35);
      END_STATE();
    case 104:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(43);
      END_STATE();
    case 105:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(38);
      END_STATE();
    case 106:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(84);
      END_STATE();
    case 107:
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(64);
      END_STATE();
    case 108:
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(86);
      END_STATE();
    case 109:
      if (lookahead == 'Y' ||
          lookahead == 'y') ADVANCE(78);
      END_STATE();
    case 110:
      if (lookahead == 'Y' ||
          lookahead == 'y') ADVANCE(131);
      END_STATE();
    case 111:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(257);
      END_STATE();
    case 112:
      if (eof) ADVANCE(113);
      if (lookahead == '-') ADVANCE(8);
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(171);
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(224);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(251);
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(169);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(254);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(112)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(aux_sym_with_declaration_token1);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(aux_sym_with_declaration_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(aux_sym_with_declaration_token2);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(aux_sym_with_declaration_token2);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 120:
      ACCEPT_TOKEN(aux_sym_project_declaration_token1);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(aux_sym_project_declaration_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(aux_sym_project_declaration_token2);
      END_STATE();
    case 123:
      ACCEPT_TOKEN(aux_sym_project_declaration_token3);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(aux_sym_project_declaration_token3);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(aux_sym_project_qualifier_token1);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(aux_sym_project_qualifier_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(aux_sym_project_qualifier_token2);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(aux_sym_project_qualifier_token2);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(aux_sym_project_qualifier_token3);
      END_STATE();
    case 130:
      ACCEPT_TOKEN(aux_sym_project_qualifier_token3);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 131:
      ACCEPT_TOKEN(aux_sym_project_qualifier_token4);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(aux_sym_project_qualifier_token4);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(aux_sym_project_qualifier_token5);
      END_STATE();
    case 134:
      ACCEPT_TOKEN(aux_sym_project_qualifier_token5);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(aux_sym__project_extension_token1);
      END_STATE();
    case 136:
      ACCEPT_TOKEN(aux_sym__project_extension_token2);
      END_STATE();
    case 137:
      ACCEPT_TOKEN(aux_sym_empty_declaration_token1);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(aux_sym_empty_declaration_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 139:
      ACCEPT_TOKEN(aux_sym_package_declaration_token1);
      END_STATE();
    case 140:
      ACCEPT_TOKEN(aux_sym_package_declaration_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 141:
      ACCEPT_TOKEN(aux_sym__package_renaming_token1);
      END_STATE();
    case 142:
      ACCEPT_TOKEN(sym_string_literal);
      if (lookahead == '"') ADVANCE(2);
      END_STATE();
    case 143:
      ACCEPT_TOKEN(aux_sym_string_literal_at_token1);
      END_STATE();
    case 144:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 145:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 146:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 147:
      ACCEPT_TOKEN(anon_sym_AMP);
      END_STATE();
    case 148:
      ACCEPT_TOKEN(aux_sym_builtin_function_call_token1);
      if (lookahead == '_') ADVANCE(18);
      END_STATE();
    case 149:
      ACCEPT_TOKEN(aux_sym_builtin_function_call_token1);
      if (lookahead == '_') ADVANCE(173);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 150:
      ACCEPT_TOKEN(aux_sym_builtin_function_call_token2);
      END_STATE();
    case 151:
      ACCEPT_TOKEN(aux_sym_builtin_function_call_token2);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 152:
      ACCEPT_TOKEN(aux_sym_typed_string_declaration_token1);
      END_STATE();
    case 153:
      ACCEPT_TOKEN(aux_sym_typed_string_declaration_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 154:
      ACCEPT_TOKEN(anon_sym_COLON);
      if (lookahead == '=') ADVANCE(155);
      END_STATE();
    case 155:
      ACCEPT_TOKEN(anon_sym_COLON_EQ);
      END_STATE();
    case 156:
      ACCEPT_TOKEN(aux_sym_case_construction_token1);
      END_STATE();
    case 157:
      ACCEPT_TOKEN(aux_sym_case_construction_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 158:
      ACCEPT_TOKEN(aux_sym_case_item_token1);
      END_STATE();
    case 159:
      ACCEPT_TOKEN(aux_sym_case_item_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 160:
      ACCEPT_TOKEN(anon_sym_EQ_GT);
      END_STATE();
    case 161:
      ACCEPT_TOKEN(anon_sym_PIPE);
      END_STATE();
    case 162:
      ACCEPT_TOKEN(aux_sym__others_designator_token1);
      END_STATE();
    case 163:
      ACCEPT_TOKEN(aux_sym_attribute_declaration_token1);
      END_STATE();
    case 164:
      ACCEPT_TOKEN(aux_sym_attribute_declaration_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 165:
      ACCEPT_TOKEN(aux_sym_attribute_declaration_token2);
      END_STATE();
    case 166:
      ACCEPT_TOKEN(anon_sym_DOT);
      END_STATE();
    case 167:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '_') ADVANCE(217);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 168:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(183);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(225);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 169:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(183);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 170:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(237);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(218);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 171:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(237);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 172:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(219);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 173:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(238);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 174:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(215);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 175:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(203);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 176:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(230);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 177:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(233);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 178:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(246);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 179:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(185);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 180:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(249);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 181:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'B' ||
          lookahead == 'b') ADVANCE(239);
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(201);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 182:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'B' ||
          lookahead == 'b') ADVANCE(231);
      if (lookahead == 'M' ||
          lookahead == 'm') ADVANCE(210);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 183:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(213);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 184:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(243);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 185:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(244);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 186:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(115);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 187:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(126);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 188:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(124);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 189:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(177);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 190:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(157);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 191:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(153);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 192:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(140);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 193:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(130);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 194:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(202);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 195:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(184);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 196:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(186);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 197:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(221);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 198:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(235);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 199:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(209);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 200:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(252);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 201:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(232);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 202:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(180);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 203:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(192);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 204:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'H' ||
          lookahead == 'h') ADVANCE(117);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 205:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'H' ||
          lookahead == 'h') ADVANCE(197);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 206:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(182);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 207:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(242);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 208:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(226);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 209:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(200);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 210:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(248);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 211:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(240);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 212:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'J' ||
          lookahead == 'j') ADVANCE(195);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 213:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'K' ||
          lookahead == 'k') ADVANCE(175);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 214:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(138);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 215:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(149);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 216:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(214);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 217:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(211);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 218:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(199);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 219:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(189);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 220:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(134);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 221:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(159);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 222:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(188);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 223:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(174);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 224:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(228);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 225:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(212);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 226:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(220);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 227:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(191);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 228:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(164);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 229:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(225);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 230:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(255);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 231:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(176);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 232:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(194);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 233:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(187);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 234:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(179);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 235:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(223);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 236:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(178);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 237:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(190);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 238:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(167);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 239:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(247);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 240:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(245);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 241:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(172);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 242:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(204);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 243:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(121);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 244:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(128);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 245:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(151);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 246:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(208);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 247:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(234);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 248:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(196);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 249:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(193);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 250:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(198);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 251:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(216);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 252:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(236);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 253:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'X' ||
          lookahead == 'x') ADVANCE(250);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 254:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'Y' ||
          lookahead == 'y') ADVANCE(227);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 255:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'Y' ||
          lookahead == 'y') ADVANCE(132);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 256:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(256);
      END_STATE();
    case 257:
      ACCEPT_TOKEN(sym_numeric_literal);
      if (lookahead == '_') ADVANCE(111);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(257);
      END_STATE();
    case 258:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(258);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 3},
  [2] = {.lex_state = 4},
  [3] = {.lex_state = 4},
  [4] = {.lex_state = 4},
  [5] = {.lex_state = 4},
  [6] = {.lex_state = 4},
  [7] = {.lex_state = 4},
  [8] = {.lex_state = 4},
  [9] = {.lex_state = 112},
  [10] = {.lex_state = 4},
  [11] = {.lex_state = 4},
  [12] = {.lex_state = 112},
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
  [26] = {.lex_state = 1},
  [27] = {.lex_state = 1},
  [28] = {.lex_state = 1},
  [29] = {.lex_state = 1},
  [30] = {.lex_state = 1},
  [31] = {.lex_state = 1},
  [32] = {.lex_state = 5},
  [33] = {.lex_state = 5},
  [34] = {.lex_state = 5},
  [35] = {.lex_state = 0},
  [36] = {.lex_state = 6},
  [37] = {.lex_state = 6},
  [38] = {.lex_state = 6},
  [39] = {.lex_state = 6},
  [40] = {.lex_state = 6},
  [41] = {.lex_state = 0},
  [42] = {.lex_state = 0},
  [43] = {.lex_state = 0},
  [44] = {.lex_state = 0},
  [45] = {.lex_state = 0},
  [46] = {.lex_state = 0},
  [47] = {.lex_state = 0},
  [48] = {.lex_state = 0},
  [49] = {.lex_state = 4},
  [50] = {.lex_state = 4},
  [51] = {.lex_state = 112},
  [52] = {.lex_state = 112},
  [53] = {.lex_state = 4},
  [54] = {.lex_state = 4},
  [55] = {.lex_state = 4},
  [56] = {.lex_state = 112},
  [57] = {.lex_state = 4},
  [58] = {.lex_state = 112},
  [59] = {.lex_state = 112},
  [60] = {.lex_state = 4},
  [61] = {.lex_state = 112},
  [62] = {.lex_state = 112},
  [63] = {.lex_state = 112},
  [64] = {.lex_state = 112},
  [65] = {.lex_state = 112},
  [66] = {.lex_state = 4},
  [67] = {.lex_state = 4},
  [68] = {.lex_state = 4},
  [69] = {.lex_state = 112},
  [70] = {.lex_state = 0},
  [71] = {.lex_state = 4},
  [72] = {.lex_state = 5},
  [73] = {.lex_state = 5},
  [74] = {.lex_state = 0},
  [75] = {.lex_state = 5},
  [76] = {.lex_state = 5},
  [77] = {.lex_state = 0},
  [78] = {.lex_state = 5},
  [79] = {.lex_state = 5},
  [80] = {.lex_state = 5},
  [81] = {.lex_state = 0},
  [82] = {.lex_state = 0},
  [83] = {.lex_state = 0},
  [84] = {.lex_state = 0},
  [85] = {.lex_state = 0},
  [86] = {.lex_state = 6},
  [87] = {.lex_state = 6},
  [88] = {.lex_state = 0},
  [89] = {.lex_state = 6},
  [90] = {.lex_state = 6},
  [91] = {.lex_state = 6},
  [92] = {.lex_state = 0},
  [93] = {.lex_state = 0},
  [94] = {.lex_state = 0},
  [95] = {.lex_state = 0},
  [96] = {.lex_state = 6},
  [97] = {.lex_state = 0},
  [98] = {.lex_state = 6},
  [99] = {.lex_state = 0},
  [100] = {.lex_state = 0},
  [101] = {.lex_state = 0},
  [102] = {.lex_state = 0},
  [103] = {.lex_state = 0},
  [104] = {.lex_state = 0},
  [105] = {.lex_state = 0},
  [106] = {.lex_state = 0},
  [107] = {.lex_state = 0},
  [108] = {.lex_state = 0},
  [109] = {.lex_state = 0},
  [110] = {.lex_state = 0},
  [111] = {.lex_state = 0},
  [112] = {.lex_state = 0},
  [113] = {.lex_state = 0},
  [114] = {.lex_state = 0},
  [115] = {.lex_state = 0},
  [116] = {.lex_state = 0},
  [117] = {.lex_state = 0},
  [118] = {.lex_state = 0},
  [119] = {.lex_state = 0},
  [120] = {.lex_state = 0},
  [121] = {.lex_state = 0},
  [122] = {.lex_state = 0},
  [123] = {.lex_state = 0},
  [124] = {.lex_state = 0},
  [125] = {.lex_state = 0},
  [126] = {.lex_state = 0},
  [127] = {.lex_state = 7},
  [128] = {.lex_state = 7},
  [129] = {.lex_state = 0},
  [130] = {.lex_state = 0},
  [131] = {.lex_state = 0},
  [132] = {.lex_state = 0},
  [133] = {.lex_state = 7},
  [134] = {.lex_state = 0},
  [135] = {.lex_state = 0},
  [136] = {.lex_state = 0},
  [137] = {.lex_state = 0},
  [138] = {.lex_state = 7},
  [139] = {.lex_state = 0},
  [140] = {.lex_state = 0},
  [141] = {.lex_state = 7},
  [142] = {.lex_state = 0},
  [143] = {.lex_state = 7},
  [144] = {.lex_state = 0},
  [145] = {.lex_state = 7},
  [146] = {.lex_state = 7},
  [147] = {.lex_state = 7},
  [148] = {.lex_state = 7},
  [149] = {.lex_state = 0},
  [150] = {.lex_state = 0},
  [151] = {.lex_state = 0},
  [152] = {.lex_state = 0},
  [153] = {.lex_state = 0},
  [154] = {.lex_state = 0},
  [155] = {.lex_state = 7},
  [156] = {.lex_state = 0},
  [157] = {.lex_state = 0},
  [158] = {.lex_state = 0},
  [159] = {.lex_state = 7},
  [160] = {.lex_state = 7},
  [161] = {.lex_state = 0},
  [162] = {.lex_state = 0},
  [163] = {.lex_state = 7},
  [164] = {.lex_state = 7},
  [165] = {.lex_state = 7},
  [166] = {.lex_state = 0},
  [167] = {.lex_state = 7},
  [168] = {.lex_state = 7},
  [169] = {.lex_state = 7},
  [170] = {.lex_state = 7},
  [171] = {.lex_state = 0},
  [172] = {.lex_state = 0},
  [173] = {.lex_state = 0},
  [174] = {.lex_state = 0},
  [175] = {.lex_state = 0},
  [176] = {.lex_state = 0},
  [177] = {.lex_state = 0},
  [178] = {.lex_state = 7},
  [179] = {.lex_state = 0},
  [180] = {.lex_state = 0},
  [181] = {.lex_state = 0},
  [182] = {.lex_state = 7},
  [183] = {.lex_state = 0},
  [184] = {.lex_state = 0},
  [185] = {.lex_state = 0},
  [186] = {.lex_state = 0},
  [187] = {.lex_state = 0},
  [188] = {.lex_state = 0},
  [189] = {.lex_state = 0},
  [190] = {.lex_state = 0},
  [191] = {.lex_state = 0},
  [192] = {.lex_state = 0},
  [193] = {.lex_state = 0},
  [194] = {.lex_state = 0},
  [195] = {.lex_state = 7},
  [196] = {.lex_state = 0},
  [197] = {.lex_state = 0},
  [198] = {.lex_state = 0},
  [199] = {.lex_state = 0},
  [200] = {.lex_state = 0},
  [201] = {.lex_state = 0},
  [202] = {.lex_state = 0},
  [203] = {.lex_state = 0},
  [204] = {.lex_state = 0},
  [205] = {.lex_state = 0},
  [206] = {.lex_state = 0},
  [207] = {.lex_state = 0},
  [208] = {.lex_state = 0},
  [209] = {.lex_state = 0},
  [210] = {.lex_state = 0},
  [211] = {.lex_state = 0},
  [212] = {.lex_state = 0},
  [213] = {.lex_state = 0},
  [214] = {.lex_state = 0},
  [215] = {.lex_state = 0},
  [216] = {.lex_state = 0},
  [217] = {.lex_state = 0},
  [218] = {.lex_state = 0},
  [219] = {.lex_state = 0},
  [220] = {.lex_state = 0},
  [221] = {.lex_state = 0},
  [222] = {.lex_state = 0},
  [223] = {.lex_state = 0},
  [224] = {.lex_state = 0},
  [225] = {.lex_state = 0},
  [226] = {.lex_state = 0},
  [227] = {.lex_state = 0},
  [228] = {.lex_state = 0},
  [229] = {.lex_state = 0},
  [230] = {.lex_state = 0},
  [231] = {.lex_state = 0},
  [232] = {.lex_state = 0},
  [233] = {.lex_state = 0},
  [234] = {.lex_state = 0},
  [235] = {.lex_state = 0},
  [236] = {.lex_state = 7},
  [237] = {.lex_state = 0},
  [238] = {.lex_state = 0},
  [239] = {.lex_state = 0},
  [240] = {.lex_state = 0},
  [241] = {.lex_state = 0},
  [242] = {.lex_state = 0},
  [243] = {.lex_state = 0},
  [244] = {.lex_state = 0},
  [245] = {.lex_state = 0},
  [246] = {.lex_state = 0},
  [247] = {.lex_state = 0},
  [248] = {.lex_state = 0},
  [249] = {.lex_state = 0},
  [250] = {.lex_state = 7},
  [251] = {.lex_state = 0},
  [252] = {.lex_state = 0},
  [253] = {.lex_state = 0},
  [254] = {.lex_state = 0},
  [255] = {.lex_state = 0},
  [256] = {.lex_state = 0},
  [257] = {.lex_state = 0},
  [258] = {.lex_state = 0},
  [259] = {.lex_state = 0},
  [260] = {.lex_state = 0},
  [261] = {.lex_state = 0},
  [262] = {.lex_state = 0},
  [263] = {.lex_state = 0},
  [264] = {.lex_state = 7},
  [265] = {.lex_state = 0},
  [266] = {.lex_state = 7},
  [267] = {.lex_state = 0},
  [268] = {.lex_state = 7},
  [269] = {.lex_state = 0},
  [270] = {.lex_state = 7},
  [271] = {.lex_state = 0},
  [272] = {.lex_state = 0},
  [273] = {.lex_state = 0},
  [274] = {.lex_state = 0},
  [275] = {.lex_state = 7},
  [276] = {.lex_state = 0},
  [277] = {.lex_state = 0},
  [278] = {.lex_state = 0},
  [279] = {.lex_state = 7},
  [280] = {.lex_state = 0},
  [281] = {.lex_state = 0},
  [282] = {.lex_state = 0},
  [283] = {.lex_state = 7},
  [284] = {.lex_state = 0},
  [285] = {.lex_state = 0},
  [286] = {.lex_state = 0},
  [287] = {.lex_state = 0},
  [288] = {.lex_state = 0},
  [289] = {.lex_state = 0},
  [290] = {.lex_state = 7},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [aux_sym_with_declaration_token1] = ACTIONS(1),
    [aux_sym_with_declaration_token2] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [aux_sym_project_declaration_token1] = ACTIONS(1),
    [aux_sym_project_declaration_token2] = ACTIONS(1),
    [aux_sym_project_declaration_token3] = ACTIONS(1),
    [aux_sym_project_qualifier_token1] = ACTIONS(1),
    [aux_sym_project_qualifier_token2] = ACTIONS(1),
    [aux_sym_project_qualifier_token3] = ACTIONS(1),
    [aux_sym_project_qualifier_token4] = ACTIONS(1),
    [aux_sym_project_qualifier_token5] = ACTIONS(1),
    [aux_sym__project_extension_token1] = ACTIONS(1),
    [aux_sym__project_extension_token2] = ACTIONS(1),
    [aux_sym_empty_declaration_token1] = ACTIONS(1),
    [aux_sym_package_declaration_token1] = ACTIONS(1),
    [aux_sym__package_renaming_token1] = ACTIONS(1),
    [sym_string_literal] = ACTIONS(1),
    [aux_sym_string_literal_at_token1] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_SQUOTE] = ACTIONS(1),
    [anon_sym_AMP] = ACTIONS(1),
    [aux_sym_builtin_function_call_token1] = ACTIONS(1),
    [aux_sym_builtin_function_call_token2] = ACTIONS(1),
    [aux_sym_typed_string_declaration_token1] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_COLON_EQ] = ACTIONS(1),
    [aux_sym_case_construction_token1] = ACTIONS(1),
    [aux_sym_case_item_token1] = ACTIONS(1),
    [anon_sym_EQ_GT] = ACTIONS(1),
    [anon_sym_PIPE] = ACTIONS(1),
    [aux_sym__others_designator_token1] = ACTIONS(1),
    [aux_sym_attribute_declaration_token1] = ACTIONS(1),
    [aux_sym_attribute_declaration_token2] = ACTIONS(1),
    [anon_sym_DOT] = ACTIONS(1),
    [sym_numeric_literal] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
  },
  [1] = {
    [sym_project] = STATE(260),
    [aux_sym__context_clause] = STATE(35),
    [sym_with_declaration] = STATE(35),
    [sym_project_declaration] = STATE(256),
    [sym_project_qualifier] = STATE(253),
    [sym__declarative_item] = STATE(12),
    [sym__simple_declarative_item] = STATE(12),
    [sym_empty_declaration] = STATE(12),
    [sym_package_declaration] = STATE(12),
    [sym_typed_string_declaration] = STATE(12),
    [sym_variable_declaration] = STATE(12),
    [sym_case_construction] = STATE(12),
    [sym_attribute_declaration] = STATE(12),
    [aux_sym_project_repeat1] = STATE(12),
    [aux_sym_with_declaration_token1] = ACTIONS(5),
    [aux_sym_with_declaration_token2] = ACTIONS(7),
    [aux_sym_project_declaration_token1] = ACTIONS(9),
    [aux_sym_project_qualifier_token1] = ACTIONS(11),
    [aux_sym_project_qualifier_token2] = ACTIONS(11),
    [aux_sym_project_qualifier_token3] = ACTIONS(13),
    [aux_sym_project_qualifier_token4] = ACTIONS(11),
    [aux_sym_project_qualifier_token5] = ACTIONS(11),
    [aux_sym_empty_declaration_token1] = ACTIONS(15),
    [aux_sym_package_declaration_token1] = ACTIONS(17),
    [aux_sym_typed_string_declaration_token1] = ACTIONS(19),
    [aux_sym_case_construction_token1] = ACTIONS(21),
    [aux_sym_attribute_declaration_token1] = ACTIONS(23),
    [sym_identifier] = ACTIONS(25),
    [sym_comment] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(27), 1,
      aux_sym_project_declaration_token3,
    ACTIONS(29), 1,
      aux_sym_empty_declaration_token1,
    ACTIONS(32), 1,
      aux_sym_package_declaration_token1,
    ACTIONS(35), 1,
      aux_sym_typed_string_declaration_token1,
    ACTIONS(38), 1,
      aux_sym_case_construction_token1,
    ACTIONS(41), 1,
      aux_sym_attribute_declaration_token1,
    ACTIONS(44), 1,
      sym_identifier,
    STATE(2), 9,
      sym__declarative_item,
      sym__simple_declarative_item,
      sym_empty_declaration,
      sym_package_declaration,
      sym_typed_string_declaration,
      sym_variable_declaration,
      sym_case_construction,
      sym_attribute_declaration,
      aux_sym_project_repeat1,
  [36] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(47), 1,
      aux_sym_project_declaration_token3,
    ACTIONS(49), 1,
      aux_sym_empty_declaration_token1,
    ACTIONS(51), 1,
      aux_sym_package_declaration_token1,
    ACTIONS(53), 1,
      aux_sym_typed_string_declaration_token1,
    ACTIONS(55), 1,
      aux_sym_case_construction_token1,
    ACTIONS(57), 1,
      aux_sym_attribute_declaration_token1,
    ACTIONS(59), 1,
      sym_identifier,
    STATE(5), 9,
      sym__declarative_item,
      sym__simple_declarative_item,
      sym_empty_declaration,
      sym_package_declaration,
      sym_typed_string_declaration,
      sym_variable_declaration,
      sym_case_construction,
      sym_attribute_declaration,
      aux_sym_project_repeat1,
  [72] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(49), 1,
      aux_sym_empty_declaration_token1,
    ACTIONS(51), 1,
      aux_sym_package_declaration_token1,
    ACTIONS(53), 1,
      aux_sym_typed_string_declaration_token1,
    ACTIONS(55), 1,
      aux_sym_case_construction_token1,
    ACTIONS(57), 1,
      aux_sym_attribute_declaration_token1,
    ACTIONS(59), 1,
      sym_identifier,
    ACTIONS(61), 1,
      aux_sym_project_declaration_token3,
    STATE(6), 9,
      sym__declarative_item,
      sym__simple_declarative_item,
      sym_empty_declaration,
      sym_package_declaration,
      sym_typed_string_declaration,
      sym_variable_declaration,
      sym_case_construction,
      sym_attribute_declaration,
      aux_sym_project_repeat1,
  [108] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(49), 1,
      aux_sym_empty_declaration_token1,
    ACTIONS(51), 1,
      aux_sym_package_declaration_token1,
    ACTIONS(53), 1,
      aux_sym_typed_string_declaration_token1,
    ACTIONS(55), 1,
      aux_sym_case_construction_token1,
    ACTIONS(57), 1,
      aux_sym_attribute_declaration_token1,
    ACTIONS(59), 1,
      sym_identifier,
    ACTIONS(61), 1,
      aux_sym_project_declaration_token3,
    STATE(2), 9,
      sym__declarative_item,
      sym__simple_declarative_item,
      sym_empty_declaration,
      sym_package_declaration,
      sym_typed_string_declaration,
      sym_variable_declaration,
      sym_case_construction,
      sym_attribute_declaration,
      aux_sym_project_repeat1,
  [144] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(49), 1,
      aux_sym_empty_declaration_token1,
    ACTIONS(51), 1,
      aux_sym_package_declaration_token1,
    ACTIONS(53), 1,
      aux_sym_typed_string_declaration_token1,
    ACTIONS(55), 1,
      aux_sym_case_construction_token1,
    ACTIONS(57), 1,
      aux_sym_attribute_declaration_token1,
    ACTIONS(59), 1,
      sym_identifier,
    ACTIONS(63), 1,
      aux_sym_project_declaration_token3,
    STATE(2), 9,
      sym__declarative_item,
      sym__simple_declarative_item,
      sym_empty_declaration,
      sym_package_declaration,
      sym_typed_string_declaration,
      sym_variable_declaration,
      sym_case_construction,
      sym_attribute_declaration,
      aux_sym_project_repeat1,
  [180] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(49), 1,
      aux_sym_empty_declaration_token1,
    ACTIONS(51), 1,
      aux_sym_package_declaration_token1,
    ACTIONS(53), 1,
      aux_sym_typed_string_declaration_token1,
    ACTIONS(55), 1,
      aux_sym_case_construction_token1,
    ACTIONS(57), 1,
      aux_sym_attribute_declaration_token1,
    ACTIONS(59), 1,
      sym_identifier,
    ACTIONS(65), 1,
      aux_sym_project_declaration_token3,
    STATE(8), 9,
      sym__declarative_item,
      sym__simple_declarative_item,
      sym_empty_declaration,
      sym_package_declaration,
      sym_typed_string_declaration,
      sym_variable_declaration,
      sym_case_construction,
      sym_attribute_declaration,
      aux_sym_project_repeat1,
  [216] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(49), 1,
      aux_sym_empty_declaration_token1,
    ACTIONS(51), 1,
      aux_sym_package_declaration_token1,
    ACTIONS(53), 1,
      aux_sym_typed_string_declaration_token1,
    ACTIONS(55), 1,
      aux_sym_case_construction_token1,
    ACTIONS(57), 1,
      aux_sym_attribute_declaration_token1,
    ACTIONS(59), 1,
      sym_identifier,
    ACTIONS(67), 1,
      aux_sym_project_declaration_token3,
    STATE(2), 9,
      sym__declarative_item,
      sym__simple_declarative_item,
      sym_empty_declaration,
      sym_package_declaration,
      sym_typed_string_declaration,
      sym_variable_declaration,
      sym_case_construction,
      sym_attribute_declaration,
      aux_sym_project_repeat1,
  [252] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(69), 1,
      ts_builtin_sym_end,
    ACTIONS(71), 1,
      aux_sym_empty_declaration_token1,
    ACTIONS(74), 1,
      aux_sym_package_declaration_token1,
    ACTIONS(77), 1,
      aux_sym_typed_string_declaration_token1,
    ACTIONS(80), 1,
      aux_sym_case_construction_token1,
    ACTIONS(83), 1,
      aux_sym_attribute_declaration_token1,
    ACTIONS(86), 1,
      sym_identifier,
    STATE(9), 9,
      sym__declarative_item,
      sym__simple_declarative_item,
      sym_empty_declaration,
      sym_package_declaration,
      sym_typed_string_declaration,
      sym_variable_declaration,
      sym_case_construction,
      sym_attribute_declaration,
      aux_sym_project_repeat1,
  [288] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(49), 1,
      aux_sym_empty_declaration_token1,
    ACTIONS(51), 1,
      aux_sym_package_declaration_token1,
    ACTIONS(53), 1,
      aux_sym_typed_string_declaration_token1,
    ACTIONS(55), 1,
      aux_sym_case_construction_token1,
    ACTIONS(57), 1,
      aux_sym_attribute_declaration_token1,
    ACTIONS(59), 1,
      sym_identifier,
    ACTIONS(89), 1,
      aux_sym_project_declaration_token3,
    STATE(2), 9,
      sym__declarative_item,
      sym__simple_declarative_item,
      sym_empty_declaration,
      sym_package_declaration,
      sym_typed_string_declaration,
      sym_variable_declaration,
      sym_case_construction,
      sym_attribute_declaration,
      aux_sym_project_repeat1,
  [324] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(49), 1,
      aux_sym_empty_declaration_token1,
    ACTIONS(51), 1,
      aux_sym_package_declaration_token1,
    ACTIONS(53), 1,
      aux_sym_typed_string_declaration_token1,
    ACTIONS(55), 1,
      aux_sym_case_construction_token1,
    ACTIONS(57), 1,
      aux_sym_attribute_declaration_token1,
    ACTIONS(59), 1,
      sym_identifier,
    ACTIONS(67), 1,
      aux_sym_project_declaration_token3,
    STATE(10), 9,
      sym__declarative_item,
      sym__simple_declarative_item,
      sym_empty_declaration,
      sym_package_declaration,
      sym_typed_string_declaration,
      sym_variable_declaration,
      sym_case_construction,
      sym_attribute_declaration,
      aux_sym_project_repeat1,
  [360] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(15), 1,
      aux_sym_empty_declaration_token1,
    ACTIONS(17), 1,
      aux_sym_package_declaration_token1,
    ACTIONS(19), 1,
      aux_sym_typed_string_declaration_token1,
    ACTIONS(21), 1,
      aux_sym_case_construction_token1,
    ACTIONS(23), 1,
      aux_sym_attribute_declaration_token1,
    ACTIONS(25), 1,
      sym_identifier,
    ACTIONS(91), 1,
      ts_builtin_sym_end,
    STATE(9), 9,
      sym__declarative_item,
      sym__simple_declarative_item,
      sym_empty_declaration,
      sym_package_declaration,
      sym_typed_string_declaration,
      sym_variable_declaration,
      sym_case_construction,
      sym_attribute_declaration,
      aux_sym_project_repeat1,
  [396] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      aux_sym_project_declaration_token1,
    ACTIONS(95), 1,
      sym_string_literal,
    ACTIONS(97), 1,
      anon_sym_LPAREN,
    ACTIONS(99), 1,
      anon_sym_RPAREN,
    ACTIONS(103), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(97), 1,
      sym_term,
    STATE(123), 1,
      sym_expression,
    ACTIONS(101), 2,
      aux_sym_builtin_function_call_token1,
      aux_sym_builtin_function_call_token2,
    STATE(116), 5,
      sym_string_literal_at,
      sym_variable_reference,
      sym_project_reference,
      sym_expression_list,
      sym_builtin_function_call,
  [435] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      aux_sym_project_declaration_token1,
    ACTIONS(95), 1,
      sym_string_literal,
    ACTIONS(97), 1,
      anon_sym_LPAREN,
    ACTIONS(103), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(97), 1,
      sym_term,
    STATE(173), 1,
      sym_expression,
    ACTIONS(101), 2,
      aux_sym_builtin_function_call_token1,
      aux_sym_builtin_function_call_token2,
    STATE(116), 5,
      sym_string_literal_at,
      sym_variable_reference,
      sym_project_reference,
      sym_expression_list,
      sym_builtin_function_call,
  [471] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      aux_sym_project_declaration_token1,
    ACTIONS(95), 1,
      sym_string_literal,
    ACTIONS(97), 1,
      anon_sym_LPAREN,
    ACTIONS(103), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(97), 1,
      sym_term,
    STATE(151), 1,
      sym_expression,
    ACTIONS(101), 2,
      aux_sym_builtin_function_call_token1,
      aux_sym_builtin_function_call_token2,
    STATE(116), 5,
      sym_string_literal_at,
      sym_variable_reference,
      sym_project_reference,
      sym_expression_list,
      sym_builtin_function_call,
  [507] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      aux_sym_project_declaration_token1,
    ACTIONS(95), 1,
      sym_string_literal,
    ACTIONS(97), 1,
      anon_sym_LPAREN,
    ACTIONS(103), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(97), 1,
      sym_term,
    STATE(207), 1,
      sym_expression,
    ACTIONS(101), 2,
      aux_sym_builtin_function_call_token1,
      aux_sym_builtin_function_call_token2,
    STATE(116), 5,
      sym_string_literal_at,
      sym_variable_reference,
      sym_project_reference,
      sym_expression_list,
      sym_builtin_function_call,
  [543] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      aux_sym_project_declaration_token1,
    ACTIONS(95), 1,
      sym_string_literal,
    ACTIONS(97), 1,
      anon_sym_LPAREN,
    ACTIONS(103), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(97), 1,
      sym_term,
    STATE(223), 1,
      sym_expression,
    ACTIONS(101), 2,
      aux_sym_builtin_function_call_token1,
      aux_sym_builtin_function_call_token2,
    STATE(116), 5,
      sym_string_literal_at,
      sym_variable_reference,
      sym_project_reference,
      sym_expression_list,
      sym_builtin_function_call,
  [579] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      aux_sym_project_declaration_token1,
    ACTIONS(95), 1,
      sym_string_literal,
    ACTIONS(97), 1,
      anon_sym_LPAREN,
    ACTIONS(103), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(97), 1,
      sym_term,
    STATE(228), 1,
      sym_expression,
    ACTIONS(101), 2,
      aux_sym_builtin_function_call_token1,
      aux_sym_builtin_function_call_token2,
    STATE(116), 5,
      sym_string_literal_at,
      sym_variable_reference,
      sym_project_reference,
      sym_expression_list,
      sym_builtin_function_call,
  [615] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      aux_sym_project_declaration_token1,
    ACTIONS(95), 1,
      sym_string_literal,
    ACTIONS(97), 1,
      anon_sym_LPAREN,
    ACTIONS(103), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(97), 1,
      sym_term,
    STATE(226), 1,
      sym_expression,
    ACTIONS(101), 2,
      aux_sym_builtin_function_call_token1,
      aux_sym_builtin_function_call_token2,
    STATE(116), 5,
      sym_string_literal_at,
      sym_variable_reference,
      sym_project_reference,
      sym_expression_list,
      sym_builtin_function_call,
  [651] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      aux_sym_project_declaration_token1,
    ACTIONS(95), 1,
      sym_string_literal,
    ACTIONS(97), 1,
      anon_sym_LPAREN,
    ACTIONS(103), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(97), 1,
      sym_term,
    STATE(188), 1,
      sym_expression,
    ACTIONS(101), 2,
      aux_sym_builtin_function_call_token1,
      aux_sym_builtin_function_call_token2,
    STATE(116), 5,
      sym_string_literal_at,
      sym_variable_reference,
      sym_project_reference,
      sym_expression_list,
      sym_builtin_function_call,
  [687] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      aux_sym_project_declaration_token1,
    ACTIONS(95), 1,
      sym_string_literal,
    ACTIONS(97), 1,
      anon_sym_LPAREN,
    ACTIONS(103), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(97), 1,
      sym_term,
    STATE(221), 1,
      sym_expression,
    ACTIONS(101), 2,
      aux_sym_builtin_function_call_token1,
      aux_sym_builtin_function_call_token2,
    STATE(116), 5,
      sym_string_literal_at,
      sym_variable_reference,
      sym_project_reference,
      sym_expression_list,
      sym_builtin_function_call,
  [723] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      aux_sym_project_declaration_token1,
    ACTIONS(95), 1,
      sym_string_literal,
    ACTIONS(97), 1,
      anon_sym_LPAREN,
    ACTIONS(103), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(97), 1,
      sym_term,
    STATE(241), 1,
      sym_expression,
    ACTIONS(101), 2,
      aux_sym_builtin_function_call_token1,
      aux_sym_builtin_function_call_token2,
    STATE(116), 5,
      sym_string_literal_at,
      sym_variable_reference,
      sym_project_reference,
      sym_expression_list,
      sym_builtin_function_call,
  [759] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      aux_sym_project_declaration_token1,
    ACTIONS(95), 1,
      sym_string_literal,
    ACTIONS(97), 1,
      anon_sym_LPAREN,
    ACTIONS(103), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(97), 1,
      sym_term,
    STATE(224), 1,
      sym_expression,
    ACTIONS(101), 2,
      aux_sym_builtin_function_call_token1,
      aux_sym_builtin_function_call_token2,
    STATE(116), 5,
      sym_string_literal_at,
      sym_variable_reference,
      sym_project_reference,
      sym_expression_list,
      sym_builtin_function_call,
  [795] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      aux_sym_project_declaration_token1,
    ACTIONS(95), 1,
      sym_string_literal,
    ACTIONS(97), 1,
      anon_sym_LPAREN,
    ACTIONS(103), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(97), 1,
      sym_term,
    STATE(214), 1,
      sym_expression,
    ACTIONS(101), 2,
      aux_sym_builtin_function_call_token1,
      aux_sym_builtin_function_call_token2,
    STATE(116), 5,
      sym_string_literal_at,
      sym_variable_reference,
      sym_project_reference,
      sym_expression_list,
      sym_builtin_function_call,
  [831] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      aux_sym_project_declaration_token1,
    ACTIONS(95), 1,
      sym_string_literal,
    ACTIONS(97), 1,
      anon_sym_LPAREN,
    ACTIONS(103), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(97), 1,
      sym_term,
    STATE(208), 1,
      sym_expression,
    ACTIONS(101), 2,
      aux_sym_builtin_function_call_token1,
      aux_sym_builtin_function_call_token2,
    STATE(116), 5,
      sym_string_literal_at,
      sym_variable_reference,
      sym_project_reference,
      sym_expression_list,
      sym_builtin_function_call,
  [867] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      aux_sym_project_declaration_token1,
    ACTIONS(95), 1,
      sym_string_literal,
    ACTIONS(97), 1,
      anon_sym_LPAREN,
    ACTIONS(103), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(97), 1,
      sym_term,
    STATE(171), 1,
      sym_expression,
    ACTIONS(101), 2,
      aux_sym_builtin_function_call_token1,
      aux_sym_builtin_function_call_token2,
    STATE(116), 5,
      sym_string_literal_at,
      sym_variable_reference,
      sym_project_reference,
      sym_expression_list,
      sym_builtin_function_call,
  [903] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      aux_sym_project_declaration_token1,
    ACTIONS(95), 1,
      sym_string_literal,
    ACTIONS(97), 1,
      anon_sym_LPAREN,
    ACTIONS(103), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(97), 1,
      sym_term,
    STATE(210), 1,
      sym_expression,
    ACTIONS(101), 2,
      aux_sym_builtin_function_call_token1,
      aux_sym_builtin_function_call_token2,
    STATE(116), 5,
      sym_string_literal_at,
      sym_variable_reference,
      sym_project_reference,
      sym_expression_list,
      sym_builtin_function_call,
  [939] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      aux_sym_project_declaration_token1,
    ACTIONS(95), 1,
      sym_string_literal,
    ACTIONS(97), 1,
      anon_sym_LPAREN,
    ACTIONS(103), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(97), 1,
      sym_term,
    STATE(219), 1,
      sym_expression,
    ACTIONS(101), 2,
      aux_sym_builtin_function_call_token1,
      aux_sym_builtin_function_call_token2,
    STATE(116), 5,
      sym_string_literal_at,
      sym_variable_reference,
      sym_project_reference,
      sym_expression_list,
      sym_builtin_function_call,
  [975] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      aux_sym_project_declaration_token1,
    ACTIONS(95), 1,
      sym_string_literal,
    ACTIONS(97), 1,
      anon_sym_LPAREN,
    ACTIONS(103), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(97), 1,
      sym_term,
    STATE(217), 1,
      sym_expression,
    ACTIONS(101), 2,
      aux_sym_builtin_function_call_token1,
      aux_sym_builtin_function_call_token2,
    STATE(116), 5,
      sym_string_literal_at,
      sym_variable_reference,
      sym_project_reference,
      sym_expression_list,
      sym_builtin_function_call,
  [1011] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      aux_sym_project_declaration_token1,
    ACTIONS(95), 1,
      sym_string_literal,
    ACTIONS(97), 1,
      anon_sym_LPAREN,
    ACTIONS(103), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(97), 1,
      sym_term,
    STATE(198), 1,
      sym_expression,
    ACTIONS(101), 2,
      aux_sym_builtin_function_call_token1,
      aux_sym_builtin_function_call_token2,
    STATE(116), 5,
      sym_string_literal_at,
      sym_variable_reference,
      sym_project_reference,
      sym_expression_list,
      sym_builtin_function_call,
  [1047] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      aux_sym_project_declaration_token1,
    ACTIONS(95), 1,
      sym_string_literal,
    ACTIONS(97), 1,
      anon_sym_LPAREN,
    ACTIONS(103), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(110), 1,
      sym_term,
    ACTIONS(101), 2,
      aux_sym_builtin_function_call_token1,
      aux_sym_builtin_function_call_token2,
    STATE(116), 5,
      sym_string_literal_at,
      sym_variable_reference,
      sym_project_reference,
      sym_expression_list,
      sym_builtin_function_call,
  [1080] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 1,
      aux_sym_empty_declaration_token1,
    ACTIONS(109), 1,
      aux_sym_case_construction_token1,
    ACTIONS(111), 1,
      aux_sym_attribute_declaration_token1,
    ACTIONS(113), 1,
      sym_identifier,
    ACTIONS(105), 2,
      aux_sym_project_declaration_token3,
      aux_sym_case_item_token1,
    STATE(33), 6,
      sym__simple_declarative_item,
      sym_empty_declaration,
      sym_variable_declaration,
      sym_case_construction,
      sym_attribute_declaration,
      aux_sym__package_spec_repeat1,
  [1108] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(117), 1,
      aux_sym_empty_declaration_token1,
    ACTIONS(120), 1,
      aux_sym_case_construction_token1,
    ACTIONS(123), 1,
      aux_sym_attribute_declaration_token1,
    ACTIONS(126), 1,
      sym_identifier,
    ACTIONS(115), 2,
      aux_sym_project_declaration_token3,
      aux_sym_case_item_token1,
    STATE(33), 6,
      sym__simple_declarative_item,
      sym_empty_declaration,
      sym_variable_declaration,
      sym_case_construction,
      sym_attribute_declaration,
      aux_sym__package_spec_repeat1,
  [1136] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 1,
      aux_sym_empty_declaration_token1,
    ACTIONS(109), 1,
      aux_sym_case_construction_token1,
    ACTIONS(111), 1,
      aux_sym_attribute_declaration_token1,
    ACTIONS(113), 1,
      sym_identifier,
    ACTIONS(129), 2,
      aux_sym_project_declaration_token3,
      aux_sym_case_item_token1,
    STATE(32), 6,
      sym__simple_declarative_item,
      sym_empty_declaration,
      sym_variable_declaration,
      sym_case_construction,
      sym_attribute_declaration,
      aux_sym__package_spec_repeat1,
  [1164] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(131), 1,
      aux_sym_with_declaration_token1,
    ACTIONS(133), 1,
      aux_sym_with_declaration_token2,
    ACTIONS(135), 1,
      aux_sym_project_declaration_token1,
    ACTIONS(139), 1,
      aux_sym_project_qualifier_token3,
    STATE(239), 1,
      sym_project_declaration,
    STATE(253), 1,
      sym_project_qualifier,
    STATE(41), 2,
      aux_sym__context_clause,
      sym_with_declaration,
    ACTIONS(137), 4,
      aux_sym_project_qualifier_token1,
      aux_sym_project_qualifier_token2,
      aux_sym_project_qualifier_token4,
      aux_sym_project_qualifier_token5,
  [1196] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(141), 1,
      aux_sym_project_declaration_token3,
    ACTIONS(143), 1,
      aux_sym_empty_declaration_token1,
    ACTIONS(145), 1,
      aux_sym_case_construction_token1,
    ACTIONS(147), 1,
      aux_sym_attribute_declaration_token1,
    ACTIONS(149), 1,
      sym_identifier,
    STATE(40), 6,
      sym__simple_declarative_item,
      sym_empty_declaration,
      sym_variable_declaration,
      sym_case_construction,
      sym_attribute_declaration,
      aux_sym__package_spec_repeat1,
  [1223] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(115), 1,
      aux_sym_project_declaration_token3,
    ACTIONS(151), 1,
      aux_sym_empty_declaration_token1,
    ACTIONS(154), 1,
      aux_sym_case_construction_token1,
    ACTIONS(157), 1,
      aux_sym_attribute_declaration_token1,
    ACTIONS(160), 1,
      sym_identifier,
    STATE(37), 6,
      sym__simple_declarative_item,
      sym_empty_declaration,
      sym_variable_declaration,
      sym_case_construction,
      sym_attribute_declaration,
      aux_sym__package_spec_repeat1,
  [1250] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(143), 1,
      aux_sym_empty_declaration_token1,
    ACTIONS(145), 1,
      aux_sym_case_construction_token1,
    ACTIONS(147), 1,
      aux_sym_attribute_declaration_token1,
    ACTIONS(149), 1,
      sym_identifier,
    ACTIONS(163), 1,
      aux_sym_project_declaration_token3,
    STATE(39), 6,
      sym__simple_declarative_item,
      sym_empty_declaration,
      sym_variable_declaration,
      sym_case_construction,
      sym_attribute_declaration,
      aux_sym__package_spec_repeat1,
  [1277] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(143), 1,
      aux_sym_empty_declaration_token1,
    ACTIONS(145), 1,
      aux_sym_case_construction_token1,
    ACTIONS(147), 1,
      aux_sym_attribute_declaration_token1,
    ACTIONS(149), 1,
      sym_identifier,
    ACTIONS(165), 1,
      aux_sym_project_declaration_token3,
    STATE(37), 6,
      sym__simple_declarative_item,
      sym_empty_declaration,
      sym_variable_declaration,
      sym_case_construction,
      sym_attribute_declaration,
      aux_sym__package_spec_repeat1,
  [1304] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(143), 1,
      aux_sym_empty_declaration_token1,
    ACTIONS(145), 1,
      aux_sym_case_construction_token1,
    ACTIONS(147), 1,
      aux_sym_attribute_declaration_token1,
    ACTIONS(149), 1,
      sym_identifier,
    ACTIONS(167), 1,
      aux_sym_project_declaration_token3,
    STATE(37), 6,
      sym__simple_declarative_item,
      sym_empty_declaration,
      sym_variable_declaration,
      sym_case_construction,
      sym_attribute_declaration,
      aux_sym__package_spec_repeat1,
  [1331] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(169), 1,
      aux_sym_with_declaration_token1,
    ACTIONS(172), 1,
      aux_sym_with_declaration_token2,
    STATE(41), 2,
      aux_sym__context_clause,
      sym_with_declaration,
    ACTIONS(175), 6,
      aux_sym_project_declaration_token1,
      aux_sym_project_qualifier_token1,
      aux_sym_project_qualifier_token2,
      aux_sym_project_qualifier_token3,
      aux_sym_project_qualifier_token4,
      aux_sym_project_qualifier_token5,
  [1353] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(179), 1,
      anon_sym_DOT,
    STATE(43), 1,
      aux_sym_name_repeat1,
    ACTIONS(177), 8,
      anon_sym_COMMA,
      anon_sym_SEMI,
      aux_sym_project_declaration_token2,
      aux_sym__project_extension_token1,
      anon_sym_RPAREN,
      anon_sym_SQUOTE,
      anon_sym_AMP,
      anon_sym_COLON_EQ,
  [1373] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(183), 1,
      anon_sym_DOT,
    STATE(43), 1,
      aux_sym_name_repeat1,
    ACTIONS(181), 8,
      anon_sym_COMMA,
      anon_sym_SEMI,
      aux_sym_project_declaration_token2,
      aux_sym__project_extension_token1,
      anon_sym_RPAREN,
      anon_sym_SQUOTE,
      anon_sym_AMP,
      anon_sym_COLON_EQ,
  [1393] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(181), 9,
      anon_sym_COMMA,
      anon_sym_SEMI,
      aux_sym_project_declaration_token2,
      aux_sym__project_extension_token1,
      anon_sym_RPAREN,
      anon_sym_SQUOTE,
      anon_sym_AMP,
      anon_sym_COLON_EQ,
      anon_sym_DOT,
  [1408] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(97), 1,
      anon_sym_LPAREN,
    ACTIONS(179), 1,
      anon_sym_DOT,
    STATE(42), 1,
      aux_sym_name_repeat1,
    STATE(117), 1,
      sym_expression_list,
    ACTIONS(186), 5,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_SQUOTE,
      anon_sym_AMP,
  [1431] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(188), 8,
      aux_sym_with_declaration_token1,
      aux_sym_with_declaration_token2,
      aux_sym_project_declaration_token1,
      aux_sym_project_qualifier_token1,
      aux_sym_project_qualifier_token2,
      aux_sym_project_qualifier_token3,
      aux_sym_project_qualifier_token4,
      aux_sym_project_qualifier_token5,
  [1445] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(190), 8,
      aux_sym_with_declaration_token1,
      aux_sym_with_declaration_token2,
      aux_sym_project_declaration_token1,
      aux_sym_project_qualifier_token1,
      aux_sym_project_qualifier_token2,
      aux_sym_project_qualifier_token3,
      aux_sym_project_qualifier_token4,
      aux_sym_project_qualifier_token5,
  [1459] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(192), 8,
      aux_sym_with_declaration_token1,
      aux_sym_with_declaration_token2,
      aux_sym_project_declaration_token1,
      aux_sym_project_qualifier_token1,
      aux_sym_project_qualifier_token2,
      aux_sym_project_qualifier_token3,
      aux_sym_project_qualifier_token4,
      aux_sym_project_qualifier_token5,
  [1473] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(194), 7,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_package_declaration_token1,
      aux_sym_typed_string_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1486] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(196), 7,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_package_declaration_token1,
      aux_sym_typed_string_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1499] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(198), 1,
      ts_builtin_sym_end,
    ACTIONS(194), 6,
      aux_sym_empty_declaration_token1,
      aux_sym_package_declaration_token1,
      aux_sym_typed_string_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1514] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(200), 1,
      ts_builtin_sym_end,
    ACTIONS(202), 6,
      aux_sym_empty_declaration_token1,
      aux_sym_package_declaration_token1,
      aux_sym_typed_string_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1529] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(204), 7,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_package_declaration_token1,
      aux_sym_typed_string_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1542] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(206), 7,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_package_declaration_token1,
      aux_sym_typed_string_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1555] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(208), 7,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_package_declaration_token1,
      aux_sym_typed_string_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1568] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(210), 1,
      ts_builtin_sym_end,
    ACTIONS(204), 6,
      aux_sym_empty_declaration_token1,
      aux_sym_package_declaration_token1,
      aux_sym_typed_string_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1583] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(212), 7,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_package_declaration_token1,
      aux_sym_typed_string_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1596] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(214), 1,
      ts_builtin_sym_end,
    ACTIONS(216), 6,
      aux_sym_empty_declaration_token1,
      aux_sym_package_declaration_token1,
      aux_sym_typed_string_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1611] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(218), 1,
      ts_builtin_sym_end,
    ACTIONS(196), 6,
      aux_sym_empty_declaration_token1,
      aux_sym_package_declaration_token1,
      aux_sym_typed_string_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1626] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(216), 7,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_package_declaration_token1,
      aux_sym_typed_string_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1639] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(220), 1,
      ts_builtin_sym_end,
    ACTIONS(212), 6,
      aux_sym_empty_declaration_token1,
      aux_sym_package_declaration_token1,
      aux_sym_typed_string_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1654] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(222), 1,
      ts_builtin_sym_end,
    ACTIONS(206), 6,
      aux_sym_empty_declaration_token1,
      aux_sym_package_declaration_token1,
      aux_sym_typed_string_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1669] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(224), 1,
      ts_builtin_sym_end,
    ACTIONS(208), 6,
      aux_sym_empty_declaration_token1,
      aux_sym_package_declaration_token1,
      aux_sym_typed_string_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1684] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(226), 1,
      ts_builtin_sym_end,
    ACTIONS(228), 6,
      aux_sym_empty_declaration_token1,
      aux_sym_package_declaration_token1,
      aux_sym_typed_string_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1699] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(230), 1,
      ts_builtin_sym_end,
    ACTIONS(232), 6,
      aux_sym_empty_declaration_token1,
      aux_sym_package_declaration_token1,
      aux_sym_typed_string_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1714] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(232), 7,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_package_declaration_token1,
      aux_sym_typed_string_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1727] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(202), 7,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_package_declaration_token1,
      aux_sym_typed_string_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1740] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(234), 7,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_package_declaration_token1,
      aux_sym_typed_string_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1753] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(236), 1,
      ts_builtin_sym_end,
    ACTIONS(234), 6,
      aux_sym_empty_declaration_token1,
      aux_sym_package_declaration_token1,
      aux_sym_typed_string_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1768] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(179), 1,
      anon_sym_DOT,
    STATE(42), 1,
      aux_sym_name_repeat1,
    ACTIONS(186), 5,
      anon_sym_SEMI,
      aux_sym_project_declaration_token2,
      aux_sym__project_extension_token1,
      anon_sym_SQUOTE,
      anon_sym_COLON_EQ,
  [1785] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(228), 7,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_package_declaration_token1,
      aux_sym_typed_string_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1798] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(196), 6,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_case_item_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1810] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(234), 6,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_case_item_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1822] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(240), 1,
      anon_sym_LPAREN,
    ACTIONS(238), 5,
      anon_sym_COMMA,
      anon_sym_SEMI,
      aux_sym_project_declaration_token2,
      anon_sym_RPAREN,
      anon_sym_AMP,
  [1836] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(212), 6,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_case_item_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1848] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(216), 6,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_case_item_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1860] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(244), 1,
      anon_sym_SQUOTE,
    ACTIONS(242), 5,
      anon_sym_COMMA,
      anon_sym_SEMI,
      aux_sym_project_declaration_token2,
      anon_sym_RPAREN,
      anon_sym_AMP,
  [1874] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(204), 6,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_case_item_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1886] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(208), 6,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_case_item_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1898] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(232), 6,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_case_item_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [1910] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(246), 1,
      aux_sym_project_declaration_token2,
    ACTIONS(248), 1,
      aux_sym__project_extension_token1,
    ACTIONS(250), 1,
      aux_sym__package_renaming_token1,
    STATE(202), 1,
      sym__package_extension,
    STATE(205), 1,
      sym__package_spec,
    STATE(206), 1,
      sym__package_renaming,
  [1932] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(246), 1,
      aux_sym_project_declaration_token2,
    ACTIONS(248), 1,
      aux_sym__project_extension_token1,
    ACTIONS(250), 1,
      aux_sym__package_renaming_token1,
    STATE(202), 1,
      sym__package_extension,
    STATE(203), 1,
      sym__package_renaming,
    STATE(229), 1,
      sym__package_spec,
  [1954] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(252), 5,
      anon_sym_COMMA,
      anon_sym_SEMI,
      aux_sym_project_declaration_token2,
      anon_sym_RPAREN,
      anon_sym_AMP,
  [1965] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(256), 1,
      anon_sym_AMP,
    STATE(95), 1,
      aux_sym_expression_repeat1,
    ACTIONS(254), 3,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
  [1980] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(258), 1,
      sym_string_literal,
    ACTIONS(260), 1,
      aux_sym__others_designator_token1,
    STATE(189), 1,
      sym_associative_array_index,
    STATE(190), 2,
      sym_string_literal_at,
      sym__others_designator,
  [1997] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(204), 5,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [2008] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(216), 5,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [2019] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(258), 1,
      sym_string_literal,
    ACTIONS(260), 1,
      aux_sym__others_designator_token1,
    STATE(278), 1,
      sym_associative_array_index,
    STATE(190), 2,
      sym_string_literal_at,
      sym__others_designator,
  [2036] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(212), 5,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [2047] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(234), 5,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [2058] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(196), 5,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [2069] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(264), 1,
      aux_sym_string_literal_at_token1,
    ACTIONS(262), 4,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_AMP,
  [2082] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(258), 1,
      sym_string_literal,
    ACTIONS(260), 1,
      aux_sym__others_designator_token1,
    STATE(274), 1,
      sym_associative_array_index,
    STATE(190), 2,
      sym_string_literal_at,
      sym__others_designator,
  [2099] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(266), 5,
      anon_sym_COMMA,
      anon_sym_SEMI,
      aux_sym_project_declaration_token2,
      anon_sym_RPAREN,
      anon_sym_AMP,
  [2110] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(270), 1,
      anon_sym_AMP,
    STATE(95), 1,
      aux_sym_expression_repeat1,
    ACTIONS(268), 3,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
  [2125] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(232), 5,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [2136] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(256), 1,
      anon_sym_AMP,
    STATE(84), 1,
      aux_sym_expression_repeat1,
    ACTIONS(273), 3,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
  [2151] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(208), 5,
      aux_sym_project_declaration_token3,
      aux_sym_empty_declaration_token1,
      aux_sym_case_construction_token1,
      aux_sym_attribute_declaration_token1,
      sym_identifier,
  [2162] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(258), 1,
      sym_string_literal,
    ACTIONS(260), 1,
      aux_sym__others_designator_token1,
    STATE(282), 1,
      sym_associative_array_index,
    STATE(190), 2,
      sym_string_literal_at,
      sym__others_designator,
  [2179] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(275), 1,
      aux_sym_project_declaration_token3,
    ACTIONS(277), 1,
      aux_sym_case_item_token1,
    STATE(101), 2,
      sym_case_item,
      aux_sym_case_construction_repeat1,
  [2193] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      aux_sym_project_declaration_token3,
    ACTIONS(281), 1,
      aux_sym_case_item_token1,
    STATE(101), 2,
      sym_case_item,
      aux_sym_case_construction_repeat1,
  [2207] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(284), 4,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_AMP,
  [2217] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(286), 1,
      anon_sym_COMMA,
    STATE(103), 1,
      aux_sym_with_declaration_repeat1,
    ACTIONS(289), 2,
      anon_sym_SEMI,
      anon_sym_RPAREN,
  [2231] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(277), 1,
      aux_sym_case_item_token1,
    ACTIONS(291), 1,
      aux_sym_project_declaration_token3,
    STATE(107), 2,
      sym_case_item,
      aux_sym_case_construction_repeat1,
  [2245] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(293), 1,
      sym_string_literal,
    ACTIONS(295), 1,
      aux_sym__others_designator_token1,
    STATE(172), 1,
      sym__others_designator,
    STATE(230), 1,
      sym_discrete_choice_list,
  [2261] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(277), 1,
      aux_sym_case_item_token1,
    ACTIONS(297), 1,
      aux_sym_project_declaration_token3,
    STATE(101), 2,
      sym_case_item,
      aux_sym_case_construction_repeat1,
  [2275] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(277), 1,
      aux_sym_case_item_token1,
    ACTIONS(299), 1,
      aux_sym_project_declaration_token3,
    STATE(101), 2,
      sym_case_item,
      aux_sym_case_construction_repeat1,
  [2289] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(277), 1,
      aux_sym_case_item_token1,
    ACTIONS(301), 1,
      aux_sym_project_declaration_token3,
    STATE(100), 2,
      sym_case_item,
      aux_sym_case_construction_repeat1,
  [2303] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(303), 4,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_AMP,
  [2313] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(268), 4,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_AMP,
  [2323] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(277), 1,
      aux_sym_case_item_token1,
    ACTIONS(305), 1,
      aux_sym_project_declaration_token3,
    STATE(106), 2,
      sym_case_item,
      aux_sym_case_construction_repeat1,
  [2337] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(307), 4,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_AMP,
  [2347] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(309), 4,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_AMP,
  [2357] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(311), 4,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_AMP,
  [2367] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(277), 1,
      aux_sym_case_item_token1,
    ACTIONS(313), 1,
      aux_sym_project_declaration_token3,
    STATE(101), 2,
      sym_case_item,
      aux_sym_case_construction_repeat1,
  [2381] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(262), 4,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_AMP,
  [2391] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(315), 4,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_AMP,
  [2401] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(277), 1,
      aux_sym_case_item_token1,
    ACTIONS(317), 1,
      aux_sym_project_declaration_token3,
    STATE(115), 2,
      sym_case_item,
      aux_sym_case_construction_repeat1,
  [2415] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(319), 1,
      anon_sym_COMMA,
    ACTIONS(321), 1,
      anon_sym_SEMI,
    STATE(103), 1,
      aux_sym_with_declaration_repeat1,
  [2428] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(319), 1,
      anon_sym_COMMA,
    ACTIONS(323), 1,
      anon_sym_RPAREN,
    STATE(103), 1,
      aux_sym_with_declaration_repeat1,
  [2441] = 3,
    ACTIONS(3), 1,
      sym_comment,
    STATE(277), 1,
      sym__others_designator,
    ACTIONS(325), 2,
      sym_string_literal,
      aux_sym__others_designator_token1,
  [2452] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(319), 1,
      anon_sym_COMMA,
    ACTIONS(327), 1,
      anon_sym_SEMI,
    STATE(119), 1,
      aux_sym_with_declaration_repeat1,
  [2465] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(329), 1,
      anon_sym_COMMA,
    ACTIONS(331), 1,
      anon_sym_RPAREN,
    STATE(129), 1,
      aux_sym_expression_list_repeat1,
  [2478] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(333), 1,
      anon_sym_EQ_GT,
    ACTIONS(335), 1,
      anon_sym_PIPE,
    STATE(136), 1,
      aux_sym_discrete_choice_list_repeat1,
  [2491] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(319), 1,
      anon_sym_COMMA,
    ACTIONS(337), 1,
      anon_sym_RPAREN,
    STATE(120), 1,
      aux_sym_with_declaration_repeat1,
  [2504] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(319), 1,
      anon_sym_COMMA,
    ACTIONS(339), 1,
      anon_sym_RPAREN,
    STATE(134), 1,
      aux_sym_with_declaration_repeat1,
  [2517] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(341), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(271), 1,
      sym_variable_reference,
  [2530] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(341), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(244), 1,
      sym_variable_reference,
  [2543] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(329), 1,
      anon_sym_COMMA,
    ACTIONS(343), 1,
      anon_sym_RPAREN,
    STATE(140), 1,
      aux_sym_expression_list_repeat1,
  [2556] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(345), 1,
      anon_sym_EQ_GT,
    ACTIONS(347), 1,
      anon_sym_PIPE,
    STATE(130), 1,
      aux_sym_discrete_choice_list_repeat1,
  [2569] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(350), 1,
      aux_sym_project_declaration_token2,
    ACTIONS(352), 1,
      aux_sym__project_extension_token1,
    STATE(186), 1,
      sym__project_extension,
  [2582] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(352), 1,
      aux_sym__project_extension_token1,
    ACTIONS(354), 1,
      aux_sym_project_declaration_token2,
    STATE(233), 1,
      sym__project_extension,
  [2595] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(341), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(276), 1,
      sym_variable_reference,
  [2608] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(319), 1,
      anon_sym_COMMA,
    ACTIONS(356), 1,
      anon_sym_RPAREN,
    STATE(103), 1,
      aux_sym_with_declaration_repeat1,
  [2621] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(319), 1,
      anon_sym_COMMA,
    ACTIONS(358), 1,
      anon_sym_SEMI,
    STATE(103), 1,
      aux_sym_with_declaration_repeat1,
  [2634] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(335), 1,
      anon_sym_PIPE,
    ACTIONS(360), 1,
      anon_sym_EQ_GT,
    STATE(130), 1,
      aux_sym_discrete_choice_list_repeat1,
  [2647] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(289), 3,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
  [2656] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(341), 1,
      sym_identifier,
    STATE(77), 1,
      sym_name,
    STATE(280), 1,
      sym_variable_reference,
  [2669] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(319), 1,
      anon_sym_COMMA,
    ACTIONS(321), 1,
      anon_sym_SEMI,
    STATE(135), 1,
      aux_sym_with_declaration_repeat1,
  [2682] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(362), 1,
      anon_sym_COMMA,
    ACTIONS(365), 1,
      anon_sym_RPAREN,
    STATE(140), 1,
      aux_sym_expression_list_repeat1,
  [2695] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(341), 1,
      sym_identifier,
    STATE(185), 1,
      sym_name,
  [2705] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(264), 1,
      aux_sym_string_literal_at_token1,
    ACTIONS(367), 1,
      anon_sym_RPAREN,
  [2715] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(341), 1,
      sym_identifier,
    STATE(132), 1,
      sym_name,
  [2725] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(369), 1,
      aux_sym_project_declaration_token1,
    ACTIONS(371), 1,
      aux_sym_project_qualifier_token4,
  [2735] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(341), 1,
      sym_identifier,
    STATE(267), 1,
      sym_name,
  [2745] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(341), 1,
      sym_identifier,
    STATE(251), 1,
      sym_name,
  [2755] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(341), 1,
      sym_identifier,
    STATE(261), 1,
      sym_name,
  [2765] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(341), 1,
      sym_identifier,
    STATE(254), 1,
      sym_name,
  [2775] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(373), 1,
      anon_sym_LPAREN,
    ACTIONS(375), 1,
      aux_sym_attribute_declaration_token2,
  [2785] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(377), 1,
      anon_sym_COLON,
    ACTIONS(379), 1,
      anon_sym_COLON_EQ,
  [2795] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(365), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [2803] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(381), 1,
      anon_sym_COLON,
    ACTIONS(383), 1,
      anon_sym_COLON_EQ,
  [2813] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(385), 1,
      anon_sym_LPAREN,
    ACTIONS(387), 1,
      aux_sym_attribute_declaration_token2,
  [2823] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(389), 1,
      anon_sym_COLON,
    ACTIONS(391), 1,
      anon_sym_COLON_EQ,
  [2833] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(341), 1,
      sym_identifier,
    STATE(175), 1,
      sym_name,
  [2843] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(393), 1,
      anon_sym_LPAREN,
    ACTIONS(395), 1,
      aux_sym_attribute_declaration_token2,
  [2853] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(397), 1,
      anon_sym_COLON,
    ACTIONS(399), 1,
      anon_sym_COLON_EQ,
  [2863] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(401), 1,
      anon_sym_LPAREN,
    ACTIONS(403), 1,
      aux_sym_attribute_declaration_token2,
  [2873] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(341), 1,
      sym_identifier,
    STATE(200), 1,
      sym_name,
  [2883] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(341), 1,
      sym_identifier,
    STATE(131), 1,
      sym_name,
  [2893] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(405), 1,
      aux_sym__project_extension_token2,
    ACTIONS(407), 1,
      sym_string_literal,
  [2903] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(345), 2,
      anon_sym_EQ_GT,
      anon_sym_PIPE,
  [2911] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(341), 1,
      sym_identifier,
    STATE(194), 1,
      sym_name,
  [2921] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(341), 1,
      sym_identifier,
    STATE(193), 1,
      sym_name,
  [2931] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(341), 1,
      sym_identifier,
    STATE(259), 1,
      sym_name,
  [2941] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(97), 1,
      anon_sym_LPAREN,
    STATE(117), 1,
      sym_expression_list,
  [2951] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(409), 1,
      sym_identifier,
    STATE(94), 1,
      sym_attribute_reference,
  [2961] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(409), 1,
      sym_identifier,
    STATE(114), 1,
      sym_attribute_reference,
  [2971] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(341), 1,
      sym_identifier,
    STATE(286), 1,
      sym_name,
  [2981] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(341), 1,
      sym_identifier,
    STATE(180), 1,
      sym_name,
  [2991] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(411), 1,
      anon_sym_SEMI,
  [2998] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(333), 1,
      anon_sym_EQ_GT,
  [3005] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(413), 1,
      anon_sym_SEMI,
  [3012] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(415), 1,
      ts_builtin_sym_end,
  [3019] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(417), 1,
      anon_sym_SEMI,
  [3026] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(419), 1,
      ts_builtin_sym_end,
  [3033] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(421), 1,
      anon_sym_SEMI,
  [3040] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(423), 1,
      sym_identifier,
  [3047] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(425), 1,
      ts_builtin_sym_end,
  [3054] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(427), 1,
      anon_sym_SEMI,
  [3061] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(429), 1,
      ts_builtin_sym_end,
  [3068] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(431), 1,
      sym_identifier,
  [3075] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(433), 1,
      anon_sym_SEMI,
  [3082] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(435), 1,
      aux_sym_project_declaration_token2,
  [3089] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(437), 1,
      anon_sym_SEMI,
  [3096] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(439), 1,
      aux_sym_project_declaration_token2,
  [3103] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(441), 1,
      sym_numeric_literal,
  [3110] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(443), 1,
      anon_sym_SEMI,
  [3117] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(445), 1,
      anon_sym_RPAREN,
  [3124] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(367), 1,
      anon_sym_RPAREN,
  [3131] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(447), 1,
      aux_sym_case_construction_token1,
  [3138] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(449), 1,
      sym_string_literal,
  [3145] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(451), 1,
      anon_sym_SEMI,
  [3152] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(453), 1,
      aux_sym_project_declaration_token2,
  [3159] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(455), 1,
      sym_identifier,
  [3166] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(457), 1,
      aux_sym_project_declaration_token2,
  [3173] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(459), 1,
      sym_string_literal,
  [3180] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(461), 1,
      anon_sym_SEMI,
  [3187] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(463), 1,
      anon_sym_SQUOTE,
  [3194] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(465), 1,
      anon_sym_COLON_EQ,
  [3201] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(467), 1,
      anon_sym_LPAREN,
  [3208] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(469), 1,
      aux_sym_project_declaration_token2,
  [3215] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(471), 1,
      anon_sym_SEMI,
  [3222] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(473), 1,
      anon_sym_SEMI,
  [3229] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(475), 1,
      anon_sym_SEMI,
  [3236] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(477), 1,
      anon_sym_SEMI,
  [3243] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(479), 1,
      anon_sym_SEMI,
  [3250] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(481), 1,
      anon_sym_SEMI,
  [3257] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(483), 1,
      anon_sym_SEMI,
  [3264] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(485), 1,
      anon_sym_SEMI,
  [3271] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(487), 1,
      anon_sym_SEMI,
  [3278] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(489), 1,
      anon_sym_SEMI,
  [3285] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(491), 1,
      anon_sym_SEMI,
  [3292] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(493), 1,
      anon_sym_SEMI,
  [3299] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(495), 1,
      anon_sym_SEMI,
  [3306] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(497), 1,
      ts_builtin_sym_end,
  [3313] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(499), 1,
      anon_sym_SEMI,
  [3320] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(501), 1,
      anon_sym_SEMI,
  [3327] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(503), 1,
      anon_sym_SEMI,
  [3334] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(505), 1,
      anon_sym_SEMI,
  [3341] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(507), 1,
      anon_sym_SEMI,
  [3348] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(509), 1,
      anon_sym_SEMI,
  [3355] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_SEMI,
  [3362] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(513), 1,
      anon_sym_SEMI,
  [3369] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(515), 1,
      anon_sym_SEMI,
  [3376] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(517), 1,
      anon_sym_SEMI,
  [3383] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(519), 1,
      anon_sym_SEMI,
  [3390] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(521), 1,
      anon_sym_SEMI,
  [3397] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(523), 1,
      anon_sym_SEMI,
  [3404] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(525), 1,
      anon_sym_EQ_GT,
  [3411] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(527), 1,
      aux_sym_case_construction_token1,
  [3418] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(529), 1,
      aux_sym_case_construction_token1,
  [3425] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(531), 1,
      aux_sym_project_declaration_token2,
  [3432] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(533), 1,
      aux_sym_with_declaration_token2,
  [3439] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(535), 1,
      aux_sym_case_construction_token1,
  [3446] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(537), 1,
      sym_identifier,
  [3453] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(539), 1,
      sym_string_literal,
  [3460] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(541), 1,
      anon_sym_SEMI,
  [3467] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(543), 1,
      ts_builtin_sym_end,
  [3474] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(545), 1,
      aux_sym_case_construction_token1,
  [3481] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(547), 1,
      anon_sym_SEMI,
  [3488] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(549), 1,
      aux_sym_case_construction_token1,
  [3495] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(551), 1,
      anon_sym_SEMI,
  [3502] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(553), 1,
      aux_sym_project_declaration_token2,
  [3509] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(555), 1,
      aux_sym_project_declaration_token2,
  [3516] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(557), 1,
      aux_sym_case_construction_token1,
  [3523] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(559), 1,
      aux_sym_project_declaration_token1,
  [3530] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(561), 1,
      aux_sym_case_construction_token1,
  [3537] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(563), 1,
      sym_string_literal,
  [3544] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(565), 1,
      sym_identifier,
  [3551] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(567), 1,
      anon_sym_SEMI,
  [3558] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(569), 1,
      ts_builtin_sym_end,
  [3565] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(571), 1,
      aux_sym_project_declaration_token1,
  [3572] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(573), 1,
      anon_sym_COLON_EQ,
  [3579] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(575), 1,
      sym_string_literal,
  [3586] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(91), 1,
      ts_builtin_sym_end,
  [3593] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(577), 1,
      aux_sym_attribute_declaration_token2,
  [3600] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(579), 1,
      aux_sym_attribute_declaration_token2,
  [3607] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(581), 1,
      anon_sym_SEMI,
  [3614] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(583), 1,
      ts_builtin_sym_end,
  [3621] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(585), 1,
      anon_sym_COLON_EQ,
  [3628] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(587), 1,
      anon_sym_SEMI,
  [3635] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(589), 1,
      aux_sym_attribute_declaration_token2,
  [3642] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(591), 1,
      sym_identifier,
  [3649] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(593), 1,
      anon_sym_SEMI,
  [3656] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(595), 1,
      sym_identifier,
  [3663] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(597), 1,
      anon_sym_COLON_EQ,
  [3670] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(599), 1,
      sym_identifier,
  [3677] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(601), 1,
      aux_sym_attribute_declaration_token2,
  [3684] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(603), 1,
      sym_identifier,
  [3691] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(605), 1,
      aux_sym_project_declaration_token2,
  [3698] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(607), 1,
      anon_sym_SEMI,
  [3705] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(609), 1,
      anon_sym_LPAREN,
  [3712] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(611), 1,
      anon_sym_RPAREN,
  [3719] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(613), 1,
      sym_identifier,
  [3726] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(615), 1,
      aux_sym_project_declaration_token2,
  [3733] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(617), 1,
      anon_sym_RPAREN,
  [3740] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(619), 1,
      anon_sym_RPAREN,
  [3747] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(621), 1,
      sym_identifier,
  [3754] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(623), 1,
      aux_sym_project_declaration_token2,
  [3761] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(625), 1,
      anon_sym_SEMI,
  [3768] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(627), 1,
      anon_sym_RPAREN,
  [3775] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(629), 1,
      sym_identifier,
  [3782] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(631), 1,
      aux_sym_project_declaration_token2,
  [3789] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(633), 1,
      anon_sym_SEMI,
  [3796] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(635), 1,
      anon_sym_SEMI,
  [3803] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(369), 1,
      aux_sym_project_declaration_token1,
  [3810] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(637), 1,
      sym_string_literal,
  [3817] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(639), 1,
      sym_string_literal,
  [3824] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(641), 1,
      sym_identifier,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 36,
  [SMALL_STATE(4)] = 72,
  [SMALL_STATE(5)] = 108,
  [SMALL_STATE(6)] = 144,
  [SMALL_STATE(7)] = 180,
  [SMALL_STATE(8)] = 216,
  [SMALL_STATE(9)] = 252,
  [SMALL_STATE(10)] = 288,
  [SMALL_STATE(11)] = 324,
  [SMALL_STATE(12)] = 360,
  [SMALL_STATE(13)] = 396,
  [SMALL_STATE(14)] = 435,
  [SMALL_STATE(15)] = 471,
  [SMALL_STATE(16)] = 507,
  [SMALL_STATE(17)] = 543,
  [SMALL_STATE(18)] = 579,
  [SMALL_STATE(19)] = 615,
  [SMALL_STATE(20)] = 651,
  [SMALL_STATE(21)] = 687,
  [SMALL_STATE(22)] = 723,
  [SMALL_STATE(23)] = 759,
  [SMALL_STATE(24)] = 795,
  [SMALL_STATE(25)] = 831,
  [SMALL_STATE(26)] = 867,
  [SMALL_STATE(27)] = 903,
  [SMALL_STATE(28)] = 939,
  [SMALL_STATE(29)] = 975,
  [SMALL_STATE(30)] = 1011,
  [SMALL_STATE(31)] = 1047,
  [SMALL_STATE(32)] = 1080,
  [SMALL_STATE(33)] = 1108,
  [SMALL_STATE(34)] = 1136,
  [SMALL_STATE(35)] = 1164,
  [SMALL_STATE(36)] = 1196,
  [SMALL_STATE(37)] = 1223,
  [SMALL_STATE(38)] = 1250,
  [SMALL_STATE(39)] = 1277,
  [SMALL_STATE(40)] = 1304,
  [SMALL_STATE(41)] = 1331,
  [SMALL_STATE(42)] = 1353,
  [SMALL_STATE(43)] = 1373,
  [SMALL_STATE(44)] = 1393,
  [SMALL_STATE(45)] = 1408,
  [SMALL_STATE(46)] = 1431,
  [SMALL_STATE(47)] = 1445,
  [SMALL_STATE(48)] = 1459,
  [SMALL_STATE(49)] = 1473,
  [SMALL_STATE(50)] = 1486,
  [SMALL_STATE(51)] = 1499,
  [SMALL_STATE(52)] = 1514,
  [SMALL_STATE(53)] = 1529,
  [SMALL_STATE(54)] = 1542,
  [SMALL_STATE(55)] = 1555,
  [SMALL_STATE(56)] = 1568,
  [SMALL_STATE(57)] = 1583,
  [SMALL_STATE(58)] = 1596,
  [SMALL_STATE(59)] = 1611,
  [SMALL_STATE(60)] = 1626,
  [SMALL_STATE(61)] = 1639,
  [SMALL_STATE(62)] = 1654,
  [SMALL_STATE(63)] = 1669,
  [SMALL_STATE(64)] = 1684,
  [SMALL_STATE(65)] = 1699,
  [SMALL_STATE(66)] = 1714,
  [SMALL_STATE(67)] = 1727,
  [SMALL_STATE(68)] = 1740,
  [SMALL_STATE(69)] = 1753,
  [SMALL_STATE(70)] = 1768,
  [SMALL_STATE(71)] = 1785,
  [SMALL_STATE(72)] = 1798,
  [SMALL_STATE(73)] = 1810,
  [SMALL_STATE(74)] = 1822,
  [SMALL_STATE(75)] = 1836,
  [SMALL_STATE(76)] = 1848,
  [SMALL_STATE(77)] = 1860,
  [SMALL_STATE(78)] = 1874,
  [SMALL_STATE(79)] = 1886,
  [SMALL_STATE(80)] = 1898,
  [SMALL_STATE(81)] = 1910,
  [SMALL_STATE(82)] = 1932,
  [SMALL_STATE(83)] = 1954,
  [SMALL_STATE(84)] = 1965,
  [SMALL_STATE(85)] = 1980,
  [SMALL_STATE(86)] = 1997,
  [SMALL_STATE(87)] = 2008,
  [SMALL_STATE(88)] = 2019,
  [SMALL_STATE(89)] = 2036,
  [SMALL_STATE(90)] = 2047,
  [SMALL_STATE(91)] = 2058,
  [SMALL_STATE(92)] = 2069,
  [SMALL_STATE(93)] = 2082,
  [SMALL_STATE(94)] = 2099,
  [SMALL_STATE(95)] = 2110,
  [SMALL_STATE(96)] = 2125,
  [SMALL_STATE(97)] = 2136,
  [SMALL_STATE(98)] = 2151,
  [SMALL_STATE(99)] = 2162,
  [SMALL_STATE(100)] = 2179,
  [SMALL_STATE(101)] = 2193,
  [SMALL_STATE(102)] = 2207,
  [SMALL_STATE(103)] = 2217,
  [SMALL_STATE(104)] = 2231,
  [SMALL_STATE(105)] = 2245,
  [SMALL_STATE(106)] = 2261,
  [SMALL_STATE(107)] = 2275,
  [SMALL_STATE(108)] = 2289,
  [SMALL_STATE(109)] = 2303,
  [SMALL_STATE(110)] = 2313,
  [SMALL_STATE(111)] = 2323,
  [SMALL_STATE(112)] = 2337,
  [SMALL_STATE(113)] = 2347,
  [SMALL_STATE(114)] = 2357,
  [SMALL_STATE(115)] = 2367,
  [SMALL_STATE(116)] = 2381,
  [SMALL_STATE(117)] = 2391,
  [SMALL_STATE(118)] = 2401,
  [SMALL_STATE(119)] = 2415,
  [SMALL_STATE(120)] = 2428,
  [SMALL_STATE(121)] = 2441,
  [SMALL_STATE(122)] = 2452,
  [SMALL_STATE(123)] = 2465,
  [SMALL_STATE(124)] = 2478,
  [SMALL_STATE(125)] = 2491,
  [SMALL_STATE(126)] = 2504,
  [SMALL_STATE(127)] = 2517,
  [SMALL_STATE(128)] = 2530,
  [SMALL_STATE(129)] = 2543,
  [SMALL_STATE(130)] = 2556,
  [SMALL_STATE(131)] = 2569,
  [SMALL_STATE(132)] = 2582,
  [SMALL_STATE(133)] = 2595,
  [SMALL_STATE(134)] = 2608,
  [SMALL_STATE(135)] = 2621,
  [SMALL_STATE(136)] = 2634,
  [SMALL_STATE(137)] = 2647,
  [SMALL_STATE(138)] = 2656,
  [SMALL_STATE(139)] = 2669,
  [SMALL_STATE(140)] = 2682,
  [SMALL_STATE(141)] = 2695,
  [SMALL_STATE(142)] = 2705,
  [SMALL_STATE(143)] = 2715,
  [SMALL_STATE(144)] = 2725,
  [SMALL_STATE(145)] = 2735,
  [SMALL_STATE(146)] = 2745,
  [SMALL_STATE(147)] = 2755,
  [SMALL_STATE(148)] = 2765,
  [SMALL_STATE(149)] = 2775,
  [SMALL_STATE(150)] = 2785,
  [SMALL_STATE(151)] = 2795,
  [SMALL_STATE(152)] = 2803,
  [SMALL_STATE(153)] = 2813,
  [SMALL_STATE(154)] = 2823,
  [SMALL_STATE(155)] = 2833,
  [SMALL_STATE(156)] = 2843,
  [SMALL_STATE(157)] = 2853,
  [SMALL_STATE(158)] = 2863,
  [SMALL_STATE(159)] = 2873,
  [SMALL_STATE(160)] = 2883,
  [SMALL_STATE(161)] = 2893,
  [SMALL_STATE(162)] = 2903,
  [SMALL_STATE(163)] = 2911,
  [SMALL_STATE(164)] = 2921,
  [SMALL_STATE(165)] = 2931,
  [SMALL_STATE(166)] = 2941,
  [SMALL_STATE(167)] = 2951,
  [SMALL_STATE(168)] = 2961,
  [SMALL_STATE(169)] = 2971,
  [SMALL_STATE(170)] = 2981,
  [SMALL_STATE(171)] = 2991,
  [SMALL_STATE(172)] = 2998,
  [SMALL_STATE(173)] = 3005,
  [SMALL_STATE(174)] = 3012,
  [SMALL_STATE(175)] = 3019,
  [SMALL_STATE(176)] = 3026,
  [SMALL_STATE(177)] = 3033,
  [SMALL_STATE(178)] = 3040,
  [SMALL_STATE(179)] = 3047,
  [SMALL_STATE(180)] = 3054,
  [SMALL_STATE(181)] = 3061,
  [SMALL_STATE(182)] = 3068,
  [SMALL_STATE(183)] = 3075,
  [SMALL_STATE(184)] = 3082,
  [SMALL_STATE(185)] = 3089,
  [SMALL_STATE(186)] = 3096,
  [SMALL_STATE(187)] = 3103,
  [SMALL_STATE(188)] = 3110,
  [SMALL_STATE(189)] = 3117,
  [SMALL_STATE(190)] = 3124,
  [SMALL_STATE(191)] = 3131,
  [SMALL_STATE(192)] = 3138,
  [SMALL_STATE(193)] = 3145,
  [SMALL_STATE(194)] = 3152,
  [SMALL_STATE(195)] = 3159,
  [SMALL_STATE(196)] = 3166,
  [SMALL_STATE(197)] = 3173,
  [SMALL_STATE(198)] = 3180,
  [SMALL_STATE(199)] = 3187,
  [SMALL_STATE(200)] = 3194,
  [SMALL_STATE(201)] = 3201,
  [SMALL_STATE(202)] = 3208,
  [SMALL_STATE(203)] = 3215,
  [SMALL_STATE(204)] = 3222,
  [SMALL_STATE(205)] = 3229,
  [SMALL_STATE(206)] = 3236,
  [SMALL_STATE(207)] = 3243,
  [SMALL_STATE(208)] = 3250,
  [SMALL_STATE(209)] = 3257,
  [SMALL_STATE(210)] = 3264,
  [SMALL_STATE(211)] = 3271,
  [SMALL_STATE(212)] = 3278,
  [SMALL_STATE(213)] = 3285,
  [SMALL_STATE(214)] = 3292,
  [SMALL_STATE(215)] = 3299,
  [SMALL_STATE(216)] = 3306,
  [SMALL_STATE(217)] = 3313,
  [SMALL_STATE(218)] = 3320,
  [SMALL_STATE(219)] = 3327,
  [SMALL_STATE(220)] = 3334,
  [SMALL_STATE(221)] = 3341,
  [SMALL_STATE(222)] = 3348,
  [SMALL_STATE(223)] = 3355,
  [SMALL_STATE(224)] = 3362,
  [SMALL_STATE(225)] = 3369,
  [SMALL_STATE(226)] = 3376,
  [SMALL_STATE(227)] = 3383,
  [SMALL_STATE(228)] = 3390,
  [SMALL_STATE(229)] = 3397,
  [SMALL_STATE(230)] = 3404,
  [SMALL_STATE(231)] = 3411,
  [SMALL_STATE(232)] = 3418,
  [SMALL_STATE(233)] = 3425,
  [SMALL_STATE(234)] = 3432,
  [SMALL_STATE(235)] = 3439,
  [SMALL_STATE(236)] = 3446,
  [SMALL_STATE(237)] = 3453,
  [SMALL_STATE(238)] = 3460,
  [SMALL_STATE(239)] = 3467,
  [SMALL_STATE(240)] = 3474,
  [SMALL_STATE(241)] = 3481,
  [SMALL_STATE(242)] = 3488,
  [SMALL_STATE(243)] = 3495,
  [SMALL_STATE(244)] = 3502,
  [SMALL_STATE(245)] = 3509,
  [SMALL_STATE(246)] = 3516,
  [SMALL_STATE(247)] = 3523,
  [SMALL_STATE(248)] = 3530,
  [SMALL_STATE(249)] = 3537,
  [SMALL_STATE(250)] = 3544,
  [SMALL_STATE(251)] = 3551,
  [SMALL_STATE(252)] = 3558,
  [SMALL_STATE(253)] = 3565,
  [SMALL_STATE(254)] = 3572,
  [SMALL_STATE(255)] = 3579,
  [SMALL_STATE(256)] = 3586,
  [SMALL_STATE(257)] = 3593,
  [SMALL_STATE(258)] = 3600,
  [SMALL_STATE(259)] = 3607,
  [SMALL_STATE(260)] = 3614,
  [SMALL_STATE(261)] = 3621,
  [SMALL_STATE(262)] = 3628,
  [SMALL_STATE(263)] = 3635,
  [SMALL_STATE(264)] = 3642,
  [SMALL_STATE(265)] = 3649,
  [SMALL_STATE(266)] = 3656,
  [SMALL_STATE(267)] = 3663,
  [SMALL_STATE(268)] = 3670,
  [SMALL_STATE(269)] = 3677,
  [SMALL_STATE(270)] = 3684,
  [SMALL_STATE(271)] = 3691,
  [SMALL_STATE(272)] = 3698,
  [SMALL_STATE(273)] = 3705,
  [SMALL_STATE(274)] = 3712,
  [SMALL_STATE(275)] = 3719,
  [SMALL_STATE(276)] = 3726,
  [SMALL_STATE(277)] = 3733,
  [SMALL_STATE(278)] = 3740,
  [SMALL_STATE(279)] = 3747,
  [SMALL_STATE(280)] = 3754,
  [SMALL_STATE(281)] = 3761,
  [SMALL_STATE(282)] = 3768,
  [SMALL_STATE(283)] = 3775,
  [SMALL_STATE(284)] = 3782,
  [SMALL_STATE(285)] = 3789,
  [SMALL_STATE(286)] = 3796,
  [SMALL_STATE(287)] = 3803,
  [SMALL_STATE(288)] = 3810,
  [SMALL_STATE(289)] = 3817,
  [SMALL_STATE(290)] = 3824,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = false}}, SHIFT(234),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(289),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(143),
  [11] = {.entry = {.count = 1, .reusable = false}}, SHIFT(287),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(144),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(285),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(283),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(268),
  [21] = {.entry = {.count = 1, .reusable = false}}, SHIFT(128),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(266),
  [25] = {.entry = {.count = 1, .reusable = false}}, SHIFT(152),
  [27] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_project_repeat1, 2),
  [29] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_project_repeat1, 2), SHIFT_REPEAT(204),
  [32] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_project_repeat1, 2), SHIFT_REPEAT(250),
  [35] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_project_repeat1, 2), SHIFT_REPEAT(290),
  [38] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_project_repeat1, 2), SHIFT_REPEAT(127),
  [41] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_project_repeat1, 2), SHIFT_REPEAT(270),
  [44] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_project_repeat1, 2), SHIFT_REPEAT(157),
  [47] = {.entry = {.count = 1, .reusable = false}}, SHIFT(165),
  [49] = {.entry = {.count = 1, .reusable = false}}, SHIFT(204),
  [51] = {.entry = {.count = 1, .reusable = false}}, SHIFT(250),
  [53] = {.entry = {.count = 1, .reusable = false}}, SHIFT(290),
  [55] = {.entry = {.count = 1, .reusable = false}}, SHIFT(127),
  [57] = {.entry = {.count = 1, .reusable = false}}, SHIFT(270),
  [59] = {.entry = {.count = 1, .reusable = false}}, SHIFT(157),
  [61] = {.entry = {.count = 1, .reusable = false}}, SHIFT(155),
  [63] = {.entry = {.count = 1, .reusable = false}}, SHIFT(170),
  [65] = {.entry = {.count = 1, .reusable = false}}, SHIFT(141),
  [67] = {.entry = {.count = 1, .reusable = false}}, SHIFT(169),
  [69] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_project_repeat1, 2),
  [71] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_project_repeat1, 2), SHIFT_REPEAT(285),
  [74] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_project_repeat1, 2), SHIFT_REPEAT(283),
  [77] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_project_repeat1, 2), SHIFT_REPEAT(268),
  [80] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_project_repeat1, 2), SHIFT_REPEAT(128),
  [83] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_project_repeat1, 2), SHIFT_REPEAT(266),
  [86] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_project_repeat1, 2), SHIFT_REPEAT(152),
  [89] = {.entry = {.count = 1, .reusable = false}}, SHIFT(146),
  [91] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_project, 1),
  [93] = {.entry = {.count = 1, .reusable = false}}, SHIFT(199),
  [95] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [97] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [99] = {.entry = {.count = 1, .reusable = true}}, SHIFT(109),
  [101] = {.entry = {.count = 1, .reusable = false}}, SHIFT(166),
  [103] = {.entry = {.count = 1, .reusable = false}}, SHIFT(45),
  [105] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_case_item, 4),
  [107] = {.entry = {.count = 1, .reusable = false}}, SHIFT(222),
  [109] = {.entry = {.count = 1, .reusable = false}}, SHIFT(138),
  [111] = {.entry = {.count = 1, .reusable = false}}, SHIFT(279),
  [113] = {.entry = {.count = 1, .reusable = false}}, SHIFT(150),
  [115] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym__package_spec_repeat1, 2),
  [117] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__package_spec_repeat1, 2), SHIFT_REPEAT(222),
  [120] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__package_spec_repeat1, 2), SHIFT_REPEAT(138),
  [123] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__package_spec_repeat1, 2), SHIFT_REPEAT(279),
  [126] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__package_spec_repeat1, 2), SHIFT_REPEAT(150),
  [129] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_case_item, 3),
  [131] = {.entry = {.count = 1, .reusable = true}}, SHIFT(234),
  [133] = {.entry = {.count = 1, .reusable = true}}, SHIFT(289),
  [135] = {.entry = {.count = 1, .reusable = true}}, SHIFT(143),
  [137] = {.entry = {.count = 1, .reusable = true}}, SHIFT(287),
  [139] = {.entry = {.count = 1, .reusable = true}}, SHIFT(144),
  [141] = {.entry = {.count = 1, .reusable = false}}, SHIFT(178),
  [143] = {.entry = {.count = 1, .reusable = false}}, SHIFT(215),
  [145] = {.entry = {.count = 1, .reusable = false}}, SHIFT(133),
  [147] = {.entry = {.count = 1, .reusable = false}}, SHIFT(275),
  [149] = {.entry = {.count = 1, .reusable = false}}, SHIFT(154),
  [151] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__package_spec_repeat1, 2), SHIFT_REPEAT(215),
  [154] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__package_spec_repeat1, 2), SHIFT_REPEAT(133),
  [157] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__package_spec_repeat1, 2), SHIFT_REPEAT(275),
  [160] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__package_spec_repeat1, 2), SHIFT_REPEAT(154),
  [163] = {.entry = {.count = 1, .reusable = false}}, SHIFT(195),
  [165] = {.entry = {.count = 1, .reusable = false}}, SHIFT(182),
  [167] = {.entry = {.count = 1, .reusable = false}}, SHIFT(264),
  [169] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__context_clause, 2), SHIFT_REPEAT(234),
  [172] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__context_clause, 2), SHIFT_REPEAT(289),
  [175] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__context_clause, 2),
  [177] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_name, 2),
  [179] = {.entry = {.count = 1, .reusable = true}}, SHIFT(236),
  [181] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_name_repeat1, 2),
  [183] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_name_repeat1, 2), SHIFT_REPEAT(236),
  [186] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_name, 1),
  [188] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_with_declaration, 5),
  [190] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_with_declaration, 4),
  [192] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_with_declaration, 3),
  [194] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_package_declaration, 4, .production_id = 4),
  [196] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_empty_declaration, 2),
  [198] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_package_declaration, 4, .production_id = 4),
  [200] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_package_declaration, 4, .production_id = 3),
  [202] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_package_declaration, 4, .production_id = 3),
  [204] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_variable_declaration, 6, .production_id = 11),
  [206] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_typed_string_declaration, 7, .production_id = 14),
  [208] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_case_construction, 7),
  [210] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_variable_declaration, 6, .production_id = 11),
  [212] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_attribute_declaration, 5, .production_id = 7),
  [214] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_case_construction, 6),
  [216] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_case_construction, 6),
  [218] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_empty_declaration, 2),
  [220] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attribute_declaration, 5, .production_id = 7),
  [222] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_typed_string_declaration, 7, .production_id = 14),
  [224] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_case_construction, 7),
  [226] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_typed_string_declaration, 8, .production_id = 14),
  [228] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_typed_string_declaration, 8, .production_id = 14),
  [230] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attribute_declaration, 8, .production_id = 17),
  [232] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_attribute_declaration, 8, .production_id = 17),
  [234] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_variable_declaration, 4, .production_id = 5),
  [236] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_variable_declaration, 4, .production_id = 5),
  [238] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attribute_reference, 1),
  [240] = {.entry = {.count = 1, .reusable = true}}, SHIFT(121),
  [242] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_variable_reference, 1),
  [244] = {.entry = {.count = 1, .reusable = true}}, SHIFT(167),
  [246] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [248] = {.entry = {.count = 1, .reusable = true}}, SHIFT(163),
  [250] = {.entry = {.count = 1, .reusable = true}}, SHIFT(164),
  [252] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attribute_reference, 4),
  [254] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression, 2),
  [256] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [258] = {.entry = {.count = 1, .reusable = true}}, SHIFT(142),
  [260] = {.entry = {.count = 1, .reusable = true}}, SHIFT(190),
  [262] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_term, 1),
  [264] = {.entry = {.count = 1, .reusable = true}}, SHIFT(187),
  [266] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_variable_reference, 3),
  [268] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_expression_repeat1, 2),
  [270] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_expression_repeat1, 2), SHIFT_REPEAT(31),
  [273] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression, 1),
  [275] = {.entry = {.count = 1, .reusable = true}}, SHIFT(242),
  [277] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [279] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_case_construction_repeat1, 2),
  [281] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_case_construction_repeat1, 2), SHIFT_REPEAT(105),
  [284] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression_list, 4),
  [286] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_with_declaration_repeat1, 2), SHIFT_REPEAT(237),
  [289] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_with_declaration_repeat1, 2),
  [291] = {.entry = {.count = 1, .reusable = true}}, SHIFT(232),
  [293] = {.entry = {.count = 1, .reusable = true}}, SHIFT(124),
  [295] = {.entry = {.count = 1, .reusable = true}}, SHIFT(172),
  [297] = {.entry = {.count = 1, .reusable = true}}, SHIFT(231),
  [299] = {.entry = {.count = 1, .reusable = true}}, SHIFT(235),
  [301] = {.entry = {.count = 1, .reusable = true}}, SHIFT(240),
  [303] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression_list, 2),
  [305] = {.entry = {.count = 1, .reusable = true}}, SHIFT(191),
  [307] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression_list, 3),
  [309] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_literal_at, 3),
  [311] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_project_reference, 3),
  [313] = {.entry = {.count = 1, .reusable = true}}, SHIFT(248),
  [315] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_builtin_function_call, 2, .production_id = 5),
  [317] = {.entry = {.count = 1, .reusable = true}}, SHIFT(246),
  [319] = {.entry = {.count = 1, .reusable = true}}, SHIFT(237),
  [321] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [323] = {.entry = {.count = 1, .reusable = true}}, SHIFT(213),
  [325] = {.entry = {.count = 1, .reusable = true}}, SHIFT(277),
  [327] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [329] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [331] = {.entry = {.count = 1, .reusable = true}}, SHIFT(112),
  [333] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_discrete_choice_list, 1),
  [335] = {.entry = {.count = 1, .reusable = true}}, SHIFT(288),
  [337] = {.entry = {.count = 1, .reusable = true}}, SHIFT(211),
  [339] = {.entry = {.count = 1, .reusable = true}}, SHIFT(262),
  [341] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [343] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [345] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_discrete_choice_list_repeat1, 2),
  [347] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_discrete_choice_list_repeat1, 2), SHIFT_REPEAT(288),
  [350] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [352] = {.entry = {.count = 1, .reusable = true}}, SHIFT(161),
  [354] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [356] = {.entry = {.count = 1, .reusable = true}}, SHIFT(238),
  [358] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [360] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_discrete_choice_list, 2),
  [362] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_expression_list_repeat1, 2), SHIFT_REPEAT(15),
  [365] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_expression_list_repeat1, 2),
  [367] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_associative_array_index, 1),
  [369] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_project_qualifier, 1),
  [371] = {.entry = {.count = 1, .reusable = true}}, SHIFT(247),
  [373] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [375] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [377] = {.entry = {.count = 1, .reusable = false}}, SHIFT(145),
  [379] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [381] = {.entry = {.count = 1, .reusable = false}}, SHIFT(159),
  [383] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [385] = {.entry = {.count = 1, .reusable = true}}, SHIFT(88),
  [387] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [389] = {.entry = {.count = 1, .reusable = false}}, SHIFT(147),
  [391] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [393] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [395] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [397] = {.entry = {.count = 1, .reusable = false}}, SHIFT(148),
  [399] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [401] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [403] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [405] = {.entry = {.count = 1, .reusable = true}}, SHIFT(197),
  [407] = {.entry = {.count = 1, .reusable = true}}, SHIFT(196),
  [409] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [411] = {.entry = {.count = 1, .reusable = true}}, SHIFT(90),
  [413] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [415] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_project_declaration, 7, .production_id = 15),
  [417] = {.entry = {.count = 1, .reusable = true}}, SHIFT(179),
  [419] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_project_declaration, 8, .production_id = 16),
  [421] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [423] = {.entry = {.count = 1, .reusable = true}}, SHIFT(265),
  [425] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_project_declaration, 8, .production_id = 18),
  [427] = {.entry = {.count = 1, .reusable = true}}, SHIFT(181),
  [429] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_project_declaration, 9, .production_id = 19),
  [431] = {.entry = {.count = 1, .reusable = true}}, SHIFT(272),
  [433] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__package_spec, 3, .production_id = 6),
  [435] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__project_extension, 3),
  [437] = {.entry = {.count = 1, .reusable = true}}, SHIFT(216),
  [439] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [441] = {.entry = {.count = 1, .reusable = true}}, SHIFT(113),
  [443] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [445] = {.entry = {.count = 1, .reusable = true}}, SHIFT(258),
  [447] = {.entry = {.count = 1, .reusable = true}}, SHIFT(177),
  [449] = {.entry = {.count = 1, .reusable = true}}, SHIFT(126),
  [451] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__package_renaming, 2, .production_id = 2),
  [453] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__package_extension, 2, .production_id = 1),
  [455] = {.entry = {.count = 1, .reusable = true}}, SHIFT(183),
  [457] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__project_extension, 2),
  [459] = {.entry = {.count = 1, .reusable = true}}, SHIFT(184),
  [461] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [463] = {.entry = {.count = 1, .reusable = true}}, SHIFT(168),
  [465] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [467] = {.entry = {.count = 1, .reusable = true}}, SHIFT(192),
  [469] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [471] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [473] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [475] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [477] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [479] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [481] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [483] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [485] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [487] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [489] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [491] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [493] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [495] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [497] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_project_declaration, 6, .production_id = 8),
  [499] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [501] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [503] = {.entry = {.count = 1, .reusable = true}}, SHIFT(86),
  [505] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [507] = {.entry = {.count = 1, .reusable = true}}, SHIFT(96),
  [509] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [511] = {.entry = {.count = 1, .reusable = true}}, SHIFT(73),
  [513] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [515] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [517] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [519] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [521] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [523] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [525] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [527] = {.entry = {.count = 1, .reusable = true}}, SHIFT(281),
  [529] = {.entry = {.count = 1, .reusable = true}}, SHIFT(209),
  [531] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [533] = {.entry = {.count = 1, .reusable = true}}, SHIFT(249),
  [535] = {.entry = {.count = 1, .reusable = true}}, SHIFT(212),
  [537] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [539] = {.entry = {.count = 1, .reusable = true}}, SHIFT(137),
  [541] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [543] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_project, 2),
  [545] = {.entry = {.count = 1, .reusable = true}}, SHIFT(218),
  [547] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [549] = {.entry = {.count = 1, .reusable = true}}, SHIFT(220),
  [551] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__package_spec, 5, .production_id = 13),
  [553] = {.entry = {.count = 1, .reusable = true}}, SHIFT(111),
  [555] = {.entry = {.count = 1, .reusable = true}}, SHIFT(201),
  [557] = {.entry = {.count = 1, .reusable = true}}, SHIFT(225),
  [559] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_project_qualifier, 2),
  [561] = {.entry = {.count = 1, .reusable = true}}, SHIFT(227),
  [563] = {.entry = {.count = 1, .reusable = true}}, SHIFT(139),
  [565] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [567] = {.entry = {.count = 1, .reusable = true}}, SHIFT(176),
  [569] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_project_declaration, 7, .production_id = 12),
  [571] = {.entry = {.count = 1, .reusable = true}}, SHIFT(160),
  [573] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [575] = {.entry = {.count = 1, .reusable = true}}, SHIFT(125),
  [577] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [579] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [581] = {.entry = {.count = 1, .reusable = true}}, SHIFT(174),
  [583] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [585] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [587] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [589] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [591] = {.entry = {.count = 1, .reusable = true}}, SHIFT(243),
  [593] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__package_spec, 4, .production_id = 10),
  [595] = {.entry = {.count = 1, .reusable = true}}, SHIFT(158),
  [597] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [599] = {.entry = {.count = 1, .reusable = true}}, SHIFT(245),
  [601] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [603] = {.entry = {.count = 1, .reusable = true}}, SHIFT(156),
  [605] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [607] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__package_spec, 4, .production_id = 9),
  [609] = {.entry = {.count = 1, .reusable = true}}, SHIFT(255),
  [611] = {.entry = {.count = 1, .reusable = true}}, SHIFT(257),
  [613] = {.entry = {.count = 1, .reusable = true}}, SHIFT(153),
  [615] = {.entry = {.count = 1, .reusable = true}}, SHIFT(108),
  [617] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [619] = {.entry = {.count = 1, .reusable = true}}, SHIFT(263),
  [621] = {.entry = {.count = 1, .reusable = true}}, SHIFT(149),
  [623] = {.entry = {.count = 1, .reusable = true}}, SHIFT(118),
  [625] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [627] = {.entry = {.count = 1, .reusable = true}}, SHIFT(269),
  [629] = {.entry = {.count = 1, .reusable = true}}, SHIFT(82),
  [631] = {.entry = {.count = 1, .reusable = true}}, SHIFT(273),
  [633] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [635] = {.entry = {.count = 1, .reusable = true}}, SHIFT(252),
  [637] = {.entry = {.count = 1, .reusable = true}}, SHIFT(162),
  [639] = {.entry = {.count = 1, .reusable = true}}, SHIFT(122),
  [641] = {.entry = {.count = 1, .reusable = true}}, SHIFT(284),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_gpr(void) {
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
