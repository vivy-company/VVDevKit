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
#define STATE_COUNT 159
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 107
#define ALIAS_COUNT 0
#define TOKEN_COUNT 66
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 8
#define PRODUCTION_ID_COUNT 1

enum ts_symbol_identifiers {
  sym_using = 1,
  sym_template = 2,
  sym__number = 3,
  anon_sym_DOT = 4,
  anon_sym_SEMI = 5,
  anon_sym_DQUOTE = 6,
  anon_sym_SQUOTE = 7,
  sym_unescaped_double_string_fragment = 8,
  sym_unescaped_single_string_fragment = 9,
  sym_escape_sequence = 10,
  anon_sym__ = 11,
  anon_sym_LPAREN = 12,
  anon_sym_RPAREN = 13,
  sym_object_id = 14,
  sym__object_fragment = 15,
  aux_sym_object_token1 = 16,
  anon_sym_LBRACE = 17,
  anon_sym_RBRACE = 18,
  anon_sym_LBRACK = 19,
  anon_sym_RBRACK = 20,
  anon_sym_layout = 21,
  anon_sym_menu = 22,
  anon_sym_section = 23,
  anon_sym_item = 24,
  anon_sym_COMMA = 25,
  anon_sym_COLON = 26,
  anon_sym_true = 27,
  anon_sym_false = 28,
  sym_property_name = 29,
  aux_sym_signal_name_token1 = 30,
  anon_sym_start = 31,
  anon_sym_end = 32,
  anon_sym_top = 33,
  anon_sym_bottom = 34,
  anon_sym_center = 35,
  anon_sym_right = 36,
  anon_sym_left = 37,
  anon_sym_fill = 38,
  anon_sym_vertical = 39,
  anon_sym_horizontal = 40,
  anon_sym_always = 41,
  anon_sym_never = 42,
  anon_sym_natural = 43,
  anon_sym_none = 44,
  anon_sym_word = 45,
  anon_sym_char = 46,
  anon_sym_word_char = 47,
  anon_sym_yes = 48,
  anon_sym_no = 49,
  anon_sym_both = 50,
  anon_sym_hidden = 51,
  anon_sym_visible = 52,
  anon_sym_wide = 53,
  anon_sym_narrow = 54,
  anon_sym_bind = 55,
  anon_sym_no_DASHsync_DASHcreate = 56,
  anon_sym_bidirectional = 57,
  anon_sym_inverted = 58,
  anon_sym_DOLLAR = 59,
  anon_sym_EQ_GT = 60,
  anon_sym_swapped = 61,
  anon_sym_condition = 62,
  anon_sym_styles = 63,
  sym_comment = 64,
  sym_float = 65,
  sym_source_file = 66,
  sym__toplevel = 67,
  sym_gobject_library = 68,
  sym_version_number = 69,
  sym_import_statement = 70,
  sym_string = 71,
  sym_gettext_string = 72,
  sym_identifier = 73,
  sym_object = 74,
  sym_block = 75,
  sym_decorator = 76,
  sym_object_definition = 77,
  sym_layout_definition = 78,
  sym_menu_definition = 79,
  sym_menu_section = 80,
  sym_menu_item = 81,
  sym_template_name_qualifier = 82,
  sym_template_definition = 83,
  sym_boolean = 84,
  sym_signal_name = 85,
  sym_constant = 86,
  sym__property_value = 87,
  sym_property_binding = 88,
  sym_property_definition = 89,
  sym_function = 90,
  sym_signal_binding = 91,
  sym_condition = 92,
  sym_styles_list = 93,
  sym_number = 94,
  sym_array = 95,
  aux_sym_source_file_repeat1 = 96,
  aux_sym_version_number_repeat1 = 97,
  aux_sym_string_repeat1 = 98,
  aux_sym_string_repeat2 = 99,
  aux_sym_object_repeat1 = 100,
  aux_sym_block_repeat1 = 101,
  aux_sym_layout_definition_repeat1 = 102,
  aux_sym_menu_definition_repeat1 = 103,
  aux_sym_menu_section_repeat1 = 104,
  aux_sym_property_binding_repeat1 = 105,
  aux_sym_array_repeat1 = 106,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_using] = "using",
  [sym_template] = "template",
  [sym__number] = "_number",
  [anon_sym_DOT] = ".",
  [anon_sym_SEMI] = ";",
  [anon_sym_DQUOTE] = "\"",
  [anon_sym_SQUOTE] = "'",
  [sym_unescaped_double_string_fragment] = "string_fragment",
  [sym_unescaped_single_string_fragment] = "string_fragment",
  [sym_escape_sequence] = "escape_sequence",
  [anon_sym__] = "_",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [sym_object_id] = "object_id",
  [sym__object_fragment] = "_object_fragment",
  [aux_sym_object_token1] = "object_token1",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [anon_sym_layout] = "layout",
  [anon_sym_menu] = "menu",
  [anon_sym_section] = "section",
  [anon_sym_item] = "item",
  [anon_sym_COMMA] = ",",
  [anon_sym_COLON] = ":",
  [anon_sym_true] = "true",
  [anon_sym_false] = "false",
  [sym_property_name] = "property_name",
  [aux_sym_signal_name_token1] = "signal_name_token1",
  [anon_sym_start] = "start",
  [anon_sym_end] = "end",
  [anon_sym_top] = "top",
  [anon_sym_bottom] = "bottom",
  [anon_sym_center] = "center",
  [anon_sym_right] = "right",
  [anon_sym_left] = "left",
  [anon_sym_fill] = "fill",
  [anon_sym_vertical] = "vertical",
  [anon_sym_horizontal] = "horizontal",
  [anon_sym_always] = "always",
  [anon_sym_never] = "never",
  [anon_sym_natural] = "natural",
  [anon_sym_none] = "none",
  [anon_sym_word] = "word",
  [anon_sym_char] = "char",
  [anon_sym_word_char] = "word_char",
  [anon_sym_yes] = "yes",
  [anon_sym_no] = "no",
  [anon_sym_both] = "both",
  [anon_sym_hidden] = "hidden",
  [anon_sym_visible] = "visible",
  [anon_sym_wide] = "wide",
  [anon_sym_narrow] = "narrow",
  [anon_sym_bind] = "bind",
  [anon_sym_no_DASHsync_DASHcreate] = "no-sync-create",
  [anon_sym_bidirectional] = "bidirectional",
  [anon_sym_inverted] = "inverted",
  [anon_sym_DOLLAR] = "$",
  [anon_sym_EQ_GT] = "=>",
  [anon_sym_swapped] = "swapped",
  [anon_sym_condition] = "condition",
  [anon_sym_styles] = "styles",
  [sym_comment] = "comment",
  [sym_float] = "float",
  [sym_source_file] = "source_file",
  [sym__toplevel] = "_toplevel",
  [sym_gobject_library] = "gobject_library",
  [sym_version_number] = "version_number",
  [sym_import_statement] = "import_statement",
  [sym_string] = "string",
  [sym_gettext_string] = "gettext_string",
  [sym_identifier] = "identifier",
  [sym_object] = "object",
  [sym_block] = "block",
  [sym_decorator] = "decorator",
  [sym_object_definition] = "object_definition",
  [sym_layout_definition] = "layout_definition",
  [sym_menu_definition] = "menu_definition",
  [sym_menu_section] = "menu_section",
  [sym_menu_item] = "menu_item",
  [sym_template_name_qualifier] = "template_name_qualifier",
  [sym_template_definition] = "template_definition",
  [sym_boolean] = "boolean",
  [sym_signal_name] = "signal_name",
  [sym_constant] = "constant",
  [sym__property_value] = "_property_value",
  [sym_property_binding] = "property_binding",
  [sym_property_definition] = "property_definition",
  [sym_function] = "function",
  [sym_signal_binding] = "signal_binding",
  [sym_condition] = "condition",
  [sym_styles_list] = "styles_list",
  [sym_number] = "number",
  [sym_array] = "array",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_version_number_repeat1] = "version_number_repeat1",
  [aux_sym_string_repeat1] = "string_repeat1",
  [aux_sym_string_repeat2] = "string_repeat2",
  [aux_sym_object_repeat1] = "object_repeat1",
  [aux_sym_block_repeat1] = "block_repeat1",
  [aux_sym_layout_definition_repeat1] = "layout_definition_repeat1",
  [aux_sym_menu_definition_repeat1] = "menu_definition_repeat1",
  [aux_sym_menu_section_repeat1] = "menu_section_repeat1",
  [aux_sym_property_binding_repeat1] = "property_binding_repeat1",
  [aux_sym_array_repeat1] = "array_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_using] = sym_using,
  [sym_template] = sym_template,
  [sym__number] = sym__number,
  [anon_sym_DOT] = anon_sym_DOT,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [anon_sym_SQUOTE] = anon_sym_SQUOTE,
  [sym_unescaped_double_string_fragment] = sym_unescaped_double_string_fragment,
  [sym_unescaped_single_string_fragment] = sym_unescaped_double_string_fragment,
  [sym_escape_sequence] = sym_escape_sequence,
  [anon_sym__] = anon_sym__,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [sym_object_id] = sym_object_id,
  [sym__object_fragment] = sym__object_fragment,
  [aux_sym_object_token1] = aux_sym_object_token1,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [anon_sym_layout] = anon_sym_layout,
  [anon_sym_menu] = anon_sym_menu,
  [anon_sym_section] = anon_sym_section,
  [anon_sym_item] = anon_sym_item,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_true] = anon_sym_true,
  [anon_sym_false] = anon_sym_false,
  [sym_property_name] = sym_property_name,
  [aux_sym_signal_name_token1] = aux_sym_signal_name_token1,
  [anon_sym_start] = anon_sym_start,
  [anon_sym_end] = anon_sym_end,
  [anon_sym_top] = anon_sym_top,
  [anon_sym_bottom] = anon_sym_bottom,
  [anon_sym_center] = anon_sym_center,
  [anon_sym_right] = anon_sym_right,
  [anon_sym_left] = anon_sym_left,
  [anon_sym_fill] = anon_sym_fill,
  [anon_sym_vertical] = anon_sym_vertical,
  [anon_sym_horizontal] = anon_sym_horizontal,
  [anon_sym_always] = anon_sym_always,
  [anon_sym_never] = anon_sym_never,
  [anon_sym_natural] = anon_sym_natural,
  [anon_sym_none] = anon_sym_none,
  [anon_sym_word] = anon_sym_word,
  [anon_sym_char] = anon_sym_char,
  [anon_sym_word_char] = anon_sym_word_char,
  [anon_sym_yes] = anon_sym_yes,
  [anon_sym_no] = anon_sym_no,
  [anon_sym_both] = anon_sym_both,
  [anon_sym_hidden] = anon_sym_hidden,
  [anon_sym_visible] = anon_sym_visible,
  [anon_sym_wide] = anon_sym_wide,
  [anon_sym_narrow] = anon_sym_narrow,
  [anon_sym_bind] = anon_sym_bind,
  [anon_sym_no_DASHsync_DASHcreate] = anon_sym_no_DASHsync_DASHcreate,
  [anon_sym_bidirectional] = anon_sym_bidirectional,
  [anon_sym_inverted] = anon_sym_inverted,
  [anon_sym_DOLLAR] = anon_sym_DOLLAR,
  [anon_sym_EQ_GT] = anon_sym_EQ_GT,
  [anon_sym_swapped] = anon_sym_swapped,
  [anon_sym_condition] = anon_sym_condition,
  [anon_sym_styles] = anon_sym_styles,
  [sym_comment] = sym_comment,
  [sym_float] = sym_float,
  [sym_source_file] = sym_source_file,
  [sym__toplevel] = sym__toplevel,
  [sym_gobject_library] = sym_gobject_library,
  [sym_version_number] = sym_version_number,
  [sym_import_statement] = sym_import_statement,
  [sym_string] = sym_string,
  [sym_gettext_string] = sym_gettext_string,
  [sym_identifier] = sym_identifier,
  [sym_object] = sym_object,
  [sym_block] = sym_block,
  [sym_decorator] = sym_decorator,
  [sym_object_definition] = sym_object_definition,
  [sym_layout_definition] = sym_layout_definition,
  [sym_menu_definition] = sym_menu_definition,
  [sym_menu_section] = sym_menu_section,
  [sym_menu_item] = sym_menu_item,
  [sym_template_name_qualifier] = sym_template_name_qualifier,
  [sym_template_definition] = sym_template_definition,
  [sym_boolean] = sym_boolean,
  [sym_signal_name] = sym_signal_name,
  [sym_constant] = sym_constant,
  [sym__property_value] = sym__property_value,
  [sym_property_binding] = sym_property_binding,
  [sym_property_definition] = sym_property_definition,
  [sym_function] = sym_function,
  [sym_signal_binding] = sym_signal_binding,
  [sym_condition] = sym_condition,
  [sym_styles_list] = sym_styles_list,
  [sym_number] = sym_number,
  [sym_array] = sym_array,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_version_number_repeat1] = aux_sym_version_number_repeat1,
  [aux_sym_string_repeat1] = aux_sym_string_repeat1,
  [aux_sym_string_repeat2] = aux_sym_string_repeat2,
  [aux_sym_object_repeat1] = aux_sym_object_repeat1,
  [aux_sym_block_repeat1] = aux_sym_block_repeat1,
  [aux_sym_layout_definition_repeat1] = aux_sym_layout_definition_repeat1,
  [aux_sym_menu_definition_repeat1] = aux_sym_menu_definition_repeat1,
  [aux_sym_menu_section_repeat1] = aux_sym_menu_section_repeat1,
  [aux_sym_property_binding_repeat1] = aux_sym_property_binding_repeat1,
  [aux_sym_array_repeat1] = aux_sym_array_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_using] = {
    .visible = true,
    .named = true,
  },
  [sym_template] = {
    .visible = true,
    .named = true,
  },
  [sym__number] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_DOT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SEMI] = {
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
  [sym_unescaped_double_string_fragment] = {
    .visible = true,
    .named = true,
  },
  [sym_unescaped_single_string_fragment] = {
    .visible = true,
    .named = true,
  },
  [sym_escape_sequence] = {
    .visible = true,
    .named = true,
  },
  [anon_sym__] = {
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
  [sym_object_id] = {
    .visible = true,
    .named = true,
  },
  [sym__object_fragment] = {
    .visible = false,
    .named = true,
  },
  [aux_sym_object_token1] = {
    .visible = false,
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
  [anon_sym_layout] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_menu] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_section] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_item] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
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
  [sym_property_name] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_signal_name_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_start] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_end] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_top] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_bottom] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_center] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_right] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_left] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_fill] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_vertical] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_horizontal] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_always] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_never] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_natural] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_none] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_word] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_char] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_word_char] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_yes] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_no] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_both] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_hidden] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_visible] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_wide] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_narrow] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_bind] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_no_DASHsync_DASHcreate] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_bidirectional] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_inverted] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOLLAR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_swapped] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_condition] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_styles] = {
    .visible = true,
    .named = false,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_float] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym__toplevel] = {
    .visible = false,
    .named = true,
  },
  [sym_gobject_library] = {
    .visible = true,
    .named = true,
  },
  [sym_version_number] = {
    .visible = true,
    .named = true,
  },
  [sym_import_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_string] = {
    .visible = true,
    .named = true,
  },
  [sym_gettext_string] = {
    .visible = true,
    .named = true,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [sym_object] = {
    .visible = true,
    .named = true,
  },
  [sym_block] = {
    .visible = true,
    .named = true,
  },
  [sym_decorator] = {
    .visible = true,
    .named = true,
  },
  [sym_object_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_layout_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_menu_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_menu_section] = {
    .visible = true,
    .named = true,
  },
  [sym_menu_item] = {
    .visible = true,
    .named = true,
  },
  [sym_template_name_qualifier] = {
    .visible = true,
    .named = true,
  },
  [sym_template_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_boolean] = {
    .visible = true,
    .named = true,
  },
  [sym_signal_name] = {
    .visible = true,
    .named = true,
  },
  [sym_constant] = {
    .visible = true,
    .named = true,
  },
  [sym__property_value] = {
    .visible = false,
    .named = true,
  },
  [sym_property_binding] = {
    .visible = true,
    .named = true,
  },
  [sym_property_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_function] = {
    .visible = true,
    .named = true,
  },
  [sym_signal_binding] = {
    .visible = true,
    .named = true,
  },
  [sym_condition] = {
    .visible = true,
    .named = true,
  },
  [sym_styles_list] = {
    .visible = true,
    .named = true,
  },
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [sym_array] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_version_number_repeat1] = {
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
  [aux_sym_object_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_block_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_layout_definition_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_menu_definition_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_menu_section_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_property_binding_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_array_repeat1] = {
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
  [3] = 2,
  [4] = 2,
  [5] = 5,
  [6] = 6,
  [7] = 6,
  [8] = 8,
  [9] = 8,
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
  [29] = 23,
  [30] = 26,
  [31] = 25,
  [32] = 24,
  [33] = 22,
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
  [75] = 52,
  [76] = 76,
  [77] = 77,
  [78] = 78,
  [79] = 79,
  [80] = 78,
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
  [100] = 17,
  [101] = 101,
  [102] = 86,
  [103] = 81,
  [104] = 17,
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
  [121] = 115,
  [122] = 122,
  [123] = 119,
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
  [153] = 152,
  [154] = 154,
  [155] = 155,
  [156] = 156,
  [157] = 144,
  [158] = 152,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(215);
      ADVANCE_MAP(
        '"', 222,
        '$', 415,
        '\'', 223,
        '(', 240,
        ')', 241,
        ',', 332,
        '.', 220,
        '/', 5,
        ':', 333,
        ';', 221,
        '=', 15,
        '[', 324,
        '\\', 187,
        ']', 325,
        '_', 239,
        'a', 105,
        'b', 86,
        'c', 62,
        'e', 120,
        'f', 21,
        'h', 92,
        'i', 122,
        'l', 16,
        'm', 69,
        'n', 17,
        'r', 87,
        's', 51,
        't', 53,
        'u', 166,
        'v', 64,
        'w', 96,
        'y', 63,
        '{', 322,
        '}', 323,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(213);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(218);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(209);
      END_STATE();
    case 1:
      ADVANCE_MAP(
        '"', 222,
        '$', 415,
        '\'', 223,
        '.', 220,
        '/', 5,
        ':', 333,
        ';', 221,
        ']', 325,
        '_', 239,
        '{', 322,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(1);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(219);
      if (('a' <= lookahead && lookahead <= 'z')) ADVANCE(211);
      END_STATE();
    case 2:
      ADVANCE_MAP(
        '"', 222,
        '\'', 223,
        '/', 5,
        '[', 324,
        '_', 239,
        'a', 111,
        'b', 90,
        'c', 66,
        'e', 126,
        'f', 18,
        'h', 95,
        'l', 61,
        'n', 19,
        'r', 91,
        's', 182,
        't', 134,
        'v', 67,
        'w', 97,
        'y', 68,
        '$', 321,
        '.', 321,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(2);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(218);
      if (('d' <= lookahead && lookahead <= 'z')) ADVANCE(211);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(209);
      END_STATE();
    case 3:
      if (lookahead == '"') ADVANCE(222);
      if (lookahead == '/') ADVANCE(225);
      if (lookahead == '\\') ADVANCE(187);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(228);
      if (lookahead != 0) ADVANCE(229);
      END_STATE();
    case 4:
      if (lookahead == '\'') ADVANCE(223);
      if (lookahead == '/') ADVANCE(231);
      if (lookahead == '\\') ADVANCE(187);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(234);
      if (lookahead != 0) ADVANCE(235);
      END_STATE();
    case 5:
      if (lookahead == '*') ADVANCE(7);
      if (lookahead == '/') ADVANCE(423);
      END_STATE();
    case 6:
      if (lookahead == '*') ADVANCE(6);
      if (lookahead == '/') ADVANCE(422);
      if (lookahead != 0) ADVANCE(7);
      END_STATE();
    case 7:
      if (lookahead == '*') ADVANCE(6);
      if (lookahead != 0) ADVANCE(7);
      END_STATE();
    case 8:
      if (lookahead == '-') ADVANCE(167);
      END_STATE();
    case 9:
      if (lookahead == '-') ADVANCE(38);
      END_STATE();
    case 10:
      ADVANCE_MAP(
        '/', 5,
        '[', 324,
        'c', 135,
        'l', 20,
        'n', 136,
        's', 175,
        '}', 323,
        '$', 321,
        '.', 321,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(10);
      if (('a' <= lookahead && lookahead <= 'z')) ADVANCE(212);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(209);
      END_STATE();
    case 11:
      if (lookahead == '/') ADVANCE(5);
      if (lookahead == 'i') ADVANCE(176);
      if (lookahead == '}') ADVANCE(323);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(11);
      if (('a' <= lookahead && lookahead <= 'z')) ADVANCE(212);
      END_STATE();
    case 12:
      if (lookahead == '/') ADVANCE(5);
      if (lookahead == '}') ADVANCE(323);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(12);
      if (('a' <= lookahead && lookahead <= 'z')) ADVANCE(212);
      END_STATE();
    case 13:
      if (lookahead == ':') ADVANCE(208);
      END_STATE();
    case 14:
      if (lookahead == ':') ADVANCE(13);
      END_STATE();
    case 15:
      if (lookahead == '>') ADVANCE(416);
      END_STATE();
    case 16:
      if (lookahead == 'a') ADVANCE(196);
      if (lookahead == 'e') ADVANCE(79);
      END_STATE();
    case 17:
      if (lookahead == 'a') ADVANCE(156);
      if (lookahead == 'e') ADVANCE(193);
      if (lookahead == 'o') ADVANCE(398);
      END_STATE();
    case 18:
      if (lookahead == 'a') ADVANCE(279);
      if (lookahead == 'i') ADVANCE(278);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 19:
      if (lookahead == 'a') ADVANCE(299);
      if (lookahead == 'e') ADVANCE(314);
      if (lookahead == 'o') ADVANCE(399);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 20:
      if (lookahead == 'a') ADVANCE(357);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 21:
      if (lookahead == 'a') ADVANCE(112);
      if (lookahead == 'i') ADVANCE(113);
      END_STATE();
    case 22:
      if (lookahead == 'a') ADVANCE(198);
      END_STATE();
    case 23:
      if (lookahead == 'a') ADVANCE(146);
      END_STATE();
    case 24:
      if (lookahead == 'a') ADVANCE(149);
      END_STATE();
    case 25:
      if (lookahead == 'a') ADVANCE(107);
      END_STATE();
    case 26:
      if (lookahead == 'a') ADVANCE(108);
      END_STATE();
    case 27:
      if (lookahead == 'a') ADVANCE(109);
      END_STATE();
    case 28:
      if (lookahead == 'a') ADVANCE(110);
      END_STATE();
    case 29:
      if (lookahead == 'a') ADVANCE(152);
      END_STATE();
    case 30:
      if (lookahead == 'a') ADVANCE(157);
      if (lookahead == 'y') ADVANCE(116);
      END_STATE();
    case 31:
      if (lookahead == 'a') ADVANCE(180);
      END_STATE();
    case 32:
      if (lookahead == 'a') ADVANCE(181);
      END_STATE();
    case 33:
      if (lookahead == 'b') ADVANCE(115);
      END_STATE();
    case 34:
      if (lookahead == 'c') ADVANCE(9);
      END_STATE();
    case 35:
      if (lookahead == 'c') ADVANCE(85);
      END_STATE();
    case 36:
      if (lookahead == 'c') ADVANCE(177);
      END_STATE();
    case 37:
      if (lookahead == 'c') ADVANCE(26);
      END_STATE();
    case 38:
      if (lookahead == 'c') ADVANCE(160);
      END_STATE();
    case 39:
      if (lookahead == 'c') ADVANCE(186);
      END_STATE();
    case 40:
      if (lookahead == 'd') ADVANCE(364);
      END_STATE();
    case 41:
      if (lookahead == 'd') ADVANCE(410);
      END_STATE();
    case 42:
      if (lookahead == 'd') ADVANCE(391);
      END_STATE();
    case 43:
      if (lookahead == 'd') ADVANCE(417);
      END_STATE();
    case 44:
      if (lookahead == 'd') ADVANCE(414);
      END_STATE();
    case 45:
      if (lookahead == 'd') ADVANCE(100);
      END_STATE();
    case 46:
      if (lookahead == 'd') ADVANCE(100);
      if (lookahead == 'n') ADVANCE(41);
      END_STATE();
    case 47:
      if (lookahead == 'd') ADVANCE(50);
      END_STATE();
    case 48:
      if (lookahead == 'd') ADVANCE(56);
      END_STATE();
    case 49:
      if (lookahead == 'd') ADVANCE(104);
      END_STATE();
    case 50:
      if (lookahead == 'd') ADVANCE(70);
      END_STATE();
    case 51:
      if (lookahead == 'e') ADVANCE(36);
      if (lookahead == 't') ADVANCE(30);
      if (lookahead == 'w') ADVANCE(23);
      END_STATE();
    case 52:
      if (lookahead == 'e') ADVANCE(119);
      END_STATE();
    case 53:
      if (lookahead == 'e') ADVANCE(119);
      if (lookahead == 'o') ADVANCE(145);
      if (lookahead == 'r') ADVANCE(189);
      END_STATE();
    case 54:
      if (lookahead == 'e') ADVANCE(388);
      END_STATE();
    case 55:
      if (lookahead == 'e') ADVANCE(334);
      END_STATE();
    case 56:
      if (lookahead == 'e') ADVANCE(406);
      END_STATE();
    case 57:
      if (lookahead == 'e') ADVANCE(336);
      END_STATE();
    case 58:
      if (lookahead == 'e') ADVANCE(404);
      END_STATE();
    case 59:
      if (lookahead == 'e') ADVANCE(217);
      END_STATE();
    case 60:
      if (lookahead == 'e') ADVANCE(412);
      END_STATE();
    case 61:
      if (lookahead == 'e') ADVANCE(266);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 62:
      if (lookahead == 'e') ADVANCE(127);
      if (lookahead == 'h') ADVANCE(24);
      if (lookahead == 'o') ADVANCE(131);
      END_STATE();
    case 63:
      if (lookahead == 'e') ADVANCE(163);
      END_STATE();
    case 64:
      if (lookahead == 'e') ADVANCE(162);
      if (lookahead == 'i') ADVANCE(168);
      END_STATE();
    case 65:
      if (lookahead == 'e') ADVANCE(117);
      END_STATE();
    case 66:
      if (lookahead == 'e') ADVANCE(283);
      if (lookahead == 'h') ADVANCE(243);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 67:
      if (lookahead == 'e') ADVANCE(297);
      if (lookahead == 'i') ADVANCE(303);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 68:
      if (lookahead == 'e') ADVANCE(301);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 69:
      if (lookahead == 'e') ADVANCE(129);
      END_STATE();
    case 70:
      if (lookahead == 'e') ADVANCE(123);
      END_STATE();
    case 71:
      if (lookahead == 'e') ADVANCE(165);
      END_STATE();
    case 72:
      if (lookahead == 'e') ADVANCE(161);
      END_STATE();
    case 73:
      if (lookahead == 'e') ADVANCE(43);
      END_STATE();
    case 74:
      if (lookahead == 'e') ADVANCE(44);
      END_STATE();
    case 75:
      if (lookahead == 'e') ADVANCE(150);
      END_STATE();
    case 76:
      if (lookahead == 'e') ADVANCE(151);
      END_STATE();
    case 77:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 78:
      if (lookahead == 'e') ADVANCE(39);
      END_STATE();
    case 79:
      if (lookahead == 'f') ADVANCE(171);
      END_STATE();
    case 80:
      if (lookahead == 'f') ADVANCE(197);
      END_STATE();
    case 81:
      if (lookahead == 'g') ADVANCE(84);
      END_STATE();
    case 82:
      if (lookahead == 'g') ADVANCE(216);
      END_STATE();
    case 83:
      if (lookahead == 'h') ADVANCE(400);
      if (lookahead == 't') ADVANCE(139);
      END_STATE();
    case 84:
      if (lookahead == 'h') ADVANCE(172);
      END_STATE();
    case 85:
      if (lookahead == 'h') ADVANCE(29);
      END_STATE();
    case 86:
      if (lookahead == 'i') ADVANCE(46);
      if (lookahead == 'o') ADVANCE(170);
      END_STATE();
    case 87:
      if (lookahead == 'i') ADVANCE(81);
      END_STATE();
    case 88:
      if (lookahead == 'i') ADVANCE(200);
      END_STATE();
    case 89:
      if (lookahead == 'i') ADVANCE(33);
      END_STATE();
    case 90:
      if (lookahead == 'i') ADVANCE(284);
      if (lookahead == 'o') ADVANCE(305);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 91:
      if (lookahead == 'i') ADVANCE(267);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 92:
      if (lookahead == 'i') ADVANCE(47);
      if (lookahead == 'o') ADVANCE(154);
      END_STATE();
    case 93:
      if (lookahead == 'i') ADVANCE(80);
      END_STATE();
    case 94:
      if (lookahead == 'i') ADVANCE(37);
      END_STATE();
    case 95:
      if (lookahead == 'i') ADVANCE(257);
      if (lookahead == 'o') ADVANCE(290);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 96:
      if (lookahead == 'i') ADVANCE(48);
      if (lookahead == 'o') ADVANCE(158);
      END_STATE();
    case 97:
      if (lookahead == 'i') ADVANCE(255);
      if (lookahead == 'o') ADVANCE(298);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 98:
      if (lookahead == 'i') ADVANCE(128);
      END_STATE();
    case 99:
      if (lookahead == 'i') ADVANCE(141);
      END_STATE();
    case 100:
      if (lookahead == 'i') ADVANCE(159);
      END_STATE();
    case 101:
      if (lookahead == 'i') ADVANCE(45);
      END_STATE();
    case 102:
      if (lookahead == 'i') ADVANCE(142);
      END_STATE();
    case 103:
      if (lookahead == 'i') ADVANCE(143);
      END_STATE();
    case 104:
      if (lookahead == 'i') ADVANCE(183);
      END_STATE();
    case 105:
      if (lookahead == 'l') ADVANCE(195);
      END_STATE();
    case 106:
      if (lookahead == 'l') ADVANCE(376);
      END_STATE();
    case 107:
      if (lookahead == 'l') ADVANCE(386);
      END_STATE();
    case 108:
      if (lookahead == 'l') ADVANCE(378);
      END_STATE();
    case 109:
      if (lookahead == 'l') ADVANCE(380);
      END_STATE();
    case 110:
      if (lookahead == 'l') ADVANCE(413);
      END_STATE();
    case 111:
      if (lookahead == 'l') ADVANCE(316);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 112:
      if (lookahead == 'l') ADVANCE(169);
      END_STATE();
    case 113:
      if (lookahead == 'l') ADVANCE(106);
      END_STATE();
    case 114:
      if (lookahead == 'l') ADVANCE(31);
      END_STATE();
    case 115:
      if (lookahead == 'l') ADVANCE(58);
      END_STATE();
    case 116:
      if (lookahead == 'l') ADVANCE(71);
      END_STATE();
    case 117:
      if (lookahead == 'm') ADVANCE(330);
      END_STATE();
    case 118:
      if (lookahead == 'm') ADVANCE(368);
      END_STATE();
    case 119:
      if (lookahead == 'm') ADVANCE(147);
      END_STATE();
    case 120:
      if (lookahead == 'n') ADVANCE(40);
      END_STATE();
    case 121:
      if (lookahead == 'n') ADVANCE(192);
      END_STATE();
    case 122:
      if (lookahead == 'n') ADVANCE(192);
      if (lookahead == 't') ADVANCE(65);
      END_STATE();
    case 123:
      if (lookahead == 'n') ADVANCE(402);
      END_STATE();
    case 124:
      if (lookahead == 'n') ADVANCE(329);
      END_STATE();
    case 125:
      if (lookahead == 'n') ADVANCE(418);
      END_STATE();
    case 126:
      if (lookahead == 'n') ADVANCE(252);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 127:
      if (lookahead == 'n') ADVANCE(184);
      END_STATE();
    case 128:
      if (lookahead == 'n') ADVANCE(82);
      END_STATE();
    case 129:
      if (lookahead == 'n') ADVANCE(188);
      END_STATE();
    case 130:
      if (lookahead == 'n') ADVANCE(34);
      END_STATE();
    case 131:
      if (lookahead == 'n') ADVANCE(49);
      END_STATE();
    case 132:
      if (lookahead == 'n') ADVANCE(185);
      END_STATE();
    case 133:
      if (lookahead == 'n') ADVANCE(28);
      END_STATE();
    case 134:
      if (lookahead == 'o') ADVANCE(289);
      if (lookahead == 'r') ADVANCE(312);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 135:
      if (lookahead == 'o') ADVANCE(348);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 136:
      if (lookahead == 'o') ADVANCE(353);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 137:
      if (lookahead == 'o') ADVANCE(194);
      END_STATE();
    case 138:
      if (lookahead == 'o') ADVANCE(8);
      END_STATE();
    case 139:
      if (lookahead == 'o') ADVANCE(118);
      END_STATE();
    case 140:
      if (lookahead == 'o') ADVANCE(190);
      END_STATE();
    case 141:
      if (lookahead == 'o') ADVANCE(124);
      END_STATE();
    case 142:
      if (lookahead == 'o') ADVANCE(125);
      END_STATE();
    case 143:
      if (lookahead == 'o') ADVANCE(133);
      END_STATE();
    case 144:
      if (lookahead == 'o') ADVANCE(132);
      END_STATE();
    case 145:
      if (lookahead == 'p') ADVANCE(366);
      END_STATE();
    case 146:
      if (lookahead == 'p') ADVANCE(148);
      END_STATE();
    case 147:
      if (lookahead == 'p') ADVANCE(114);
      END_STATE();
    case 148:
      if (lookahead == 'p') ADVANCE(73);
      END_STATE();
    case 149:
      if (lookahead == 'r') ADVANCE(392);
      END_STATE();
    case 150:
      if (lookahead == 'r') ADVANCE(384);
      END_STATE();
    case 151:
      if (lookahead == 'r') ADVANCE(370);
      END_STATE();
    case 152:
      if (lookahead == 'r') ADVANCE(394);
      END_STATE();
    case 153:
      if (lookahead == 'r') ADVANCE(137);
      END_STATE();
    case 154:
      if (lookahead == 'r') ADVANCE(88);
      END_STATE();
    case 155:
      if (lookahead == 'r') ADVANCE(25);
      END_STATE();
    case 156:
      if (lookahead == 'r') ADVANCE(153);
      if (lookahead == 't') ADVANCE(191);
      END_STATE();
    case 157:
      if (lookahead == 'r') ADVANCE(173);
      END_STATE();
    case 158:
      if (lookahead == 'r') ADVANCE(42);
      END_STATE();
    case 159:
      if (lookahead == 'r') ADVANCE(78);
      END_STATE();
    case 160:
      if (lookahead == 'r') ADVANCE(77);
      END_STATE();
    case 161:
      if (lookahead == 'r') ADVANCE(179);
      END_STATE();
    case 162:
      if (lookahead == 'r') ADVANCE(178);
      END_STATE();
    case 163:
      if (lookahead == 's') ADVANCE(396);
      END_STATE();
    case 164:
      if (lookahead == 's') ADVANCE(382);
      END_STATE();
    case 165:
      if (lookahead == 's') ADVANCE(420);
      END_STATE();
    case 166:
      if (lookahead == 's') ADVANCE(98);
      END_STATE();
    case 167:
      if (lookahead == 's') ADVANCE(199);
      END_STATE();
    case 168:
      if (lookahead == 's') ADVANCE(89);
      END_STATE();
    case 169:
      if (lookahead == 's') ADVANCE(57);
      END_STATE();
    case 170:
      if (lookahead == 't') ADVANCE(83);
      END_STATE();
    case 171:
      if (lookahead == 't') ADVANCE(374);
      END_STATE();
    case 172:
      if (lookahead == 't') ADVANCE(372);
      END_STATE();
    case 173:
      if (lookahead == 't') ADVANCE(362);
      END_STATE();
    case 174:
      if (lookahead == 't') ADVANCE(326);
      END_STATE();
    case 175:
      if (lookahead == 't') ADVANCE(358);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 176:
      if (lookahead == 't') ADVANCE(341);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 177:
      if (lookahead == 't') ADVANCE(99);
      END_STATE();
    case 178:
      if (lookahead == 't') ADVANCE(94);
      END_STATE();
    case 179:
      if (lookahead == 't') ADVANCE(74);
      END_STATE();
    case 180:
      if (lookahead == 't') ADVANCE(59);
      END_STATE();
    case 181:
      if (lookahead == 't') ADVANCE(60);
      END_STATE();
    case 182:
      if (lookahead == 't') ADVANCE(248);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 183:
      if (lookahead == 't') ADVANCE(102);
      END_STATE();
    case 184:
      if (lookahead == 't') ADVANCE(76);
      END_STATE();
    case 185:
      if (lookahead == 't') ADVANCE(27);
      END_STATE();
    case 186:
      if (lookahead == 't') ADVANCE(103);
      END_STATE();
    case 187:
      if (lookahead == 'u') ADVANCE(201);
      if (lookahead == 'x') ADVANCE(207);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(238);
      if (lookahead != 0) ADVANCE(236);
      END_STATE();
    case 188:
      if (lookahead == 'u') ADVANCE(328);
      END_STATE();
    case 189:
      if (lookahead == 'u') ADVANCE(55);
      END_STATE();
    case 190:
      if (lookahead == 'u') ADVANCE(174);
      END_STATE();
    case 191:
      if (lookahead == 'u') ADVANCE(155);
      END_STATE();
    case 192:
      if (lookahead == 'v') ADVANCE(72);
      END_STATE();
    case 193:
      if (lookahead == 'v') ADVANCE(75);
      END_STATE();
    case 194:
      if (lookahead == 'w') ADVANCE(408);
      END_STATE();
    case 195:
      if (lookahead == 'w') ADVANCE(22);
      END_STATE();
    case 196:
      if (lookahead == 'y') ADVANCE(140);
      END_STATE();
    case 197:
      if (lookahead == 'y') ADVANCE(14);
      END_STATE();
    case 198:
      if (lookahead == 'y') ADVANCE(164);
      END_STATE();
    case 199:
      if (lookahead == 'y') ADVANCE(130);
      END_STATE();
    case 200:
      if (lookahead == 'z') ADVANCE(144);
      END_STATE();
    case 201:
      if (lookahead == '{') ADVANCE(206);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(204);
      END_STATE();
    case 202:
      if (lookahead == '}') ADVANCE(236);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(202);
      END_STATE();
    case 203:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(424);
      END_STATE();
    case 204:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(207);
      END_STATE();
    case 205:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(236);
      END_STATE();
    case 206:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(202);
      END_STATE();
    case 207:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(205);
      END_STATE();
    case 208:
      if (('a' <= lookahead && lookahead <= 'z')) ADVANCE(210);
      END_STATE();
    case 209:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(320);
      END_STATE();
    case 210:
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(361);
      END_STATE();
    case 211:
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 212:
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 213:
      if (eof) ADVANCE(215);
      ADVANCE_MAP(
        '"', 222,
        '$', 415,
        '\'', 223,
        '(', 240,
        ')', 241,
        ',', 332,
        '.', 220,
        '/', 5,
        ':', 333,
        ';', 221,
        '=', 15,
        '[', 324,
        ']', 325,
        '_', 239,
        'a', 105,
        'b', 86,
        'c', 62,
        'e', 120,
        'f', 21,
        'h', 92,
        'i', 122,
        'l', 16,
        'm', 69,
        'n', 17,
        'r', 87,
        's', 51,
        't', 53,
        'u', 166,
        'v', 64,
        'w', 96,
        'y', 63,
        '{', 322,
        '}', 323,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(213);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(218);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(209);
      END_STATE();
    case 214:
      if (eof) ADVANCE(215);
      ADVANCE_MAP(
        '/', 5,
        ';', 221,
        '[', 324,
        'b', 101,
        'i', 121,
        'm', 69,
        'n', 138,
        't', 52,
        'u', 166,
        '$', 321,
        '.', 321,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(214);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(219);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(209);
      END_STATE();
    case 215:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 216:
      ACCEPT_TOKEN(sym_using);
      END_STATE();
    case 217:
      ACCEPT_TOKEN(sym_template);
      END_STATE();
    case 218:
      ACCEPT_TOKEN(sym__number);
      if (lookahead == '.') ADVANCE(203);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(218);
      END_STATE();
    case 219:
      ACCEPT_TOKEN(sym__number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(219);
      END_STATE();
    case 220:
      ACCEPT_TOKEN(anon_sym_DOT);
      END_STATE();
    case 221:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 222:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 223:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 224:
      ACCEPT_TOKEN(sym_unescaped_double_string_fragment);
      if (lookahead == '\n') ADVANCE(229);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(224);
      END_STATE();
    case 225:
      ACCEPT_TOKEN(sym_unescaped_double_string_fragment);
      if (lookahead == '*') ADVANCE(227);
      if (lookahead == '/') ADVANCE(224);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(229);
      END_STATE();
    case 226:
      ACCEPT_TOKEN(sym_unescaped_double_string_fragment);
      if (lookahead == '*') ADVANCE(226);
      if (lookahead == '/') ADVANCE(229);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(227);
      END_STATE();
    case 227:
      ACCEPT_TOKEN(sym_unescaped_double_string_fragment);
      if (lookahead == '*') ADVANCE(226);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(227);
      END_STATE();
    case 228:
      ACCEPT_TOKEN(sym_unescaped_double_string_fragment);
      if (lookahead == '/') ADVANCE(225);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(228);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(229);
      END_STATE();
    case 229:
      ACCEPT_TOKEN(sym_unescaped_double_string_fragment);
      if (lookahead != 0 &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(229);
      END_STATE();
    case 230:
      ACCEPT_TOKEN(sym_unescaped_single_string_fragment);
      if (lookahead == '\n') ADVANCE(235);
      if (lookahead != 0 &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(230);
      END_STATE();
    case 231:
      ACCEPT_TOKEN(sym_unescaped_single_string_fragment);
      if (lookahead == '*') ADVANCE(233);
      if (lookahead == '/') ADVANCE(230);
      if (lookahead != 0 &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(235);
      END_STATE();
    case 232:
      ACCEPT_TOKEN(sym_unescaped_single_string_fragment);
      if (lookahead == '*') ADVANCE(232);
      if (lookahead == '/') ADVANCE(235);
      if (lookahead != 0 &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(233);
      END_STATE();
    case 233:
      ACCEPT_TOKEN(sym_unescaped_single_string_fragment);
      if (lookahead == '*') ADVANCE(232);
      if (lookahead != 0 &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(233);
      END_STATE();
    case 234:
      ACCEPT_TOKEN(sym_unescaped_single_string_fragment);
      if (lookahead == '/') ADVANCE(231);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(234);
      if (lookahead != 0 &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(235);
      END_STATE();
    case 235:
      ACCEPT_TOKEN(sym_unescaped_single_string_fragment);
      if (lookahead != 0 &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(235);
      END_STATE();
    case 236:
      ACCEPT_TOKEN(sym_escape_sequence);
      END_STATE();
    case 237:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(236);
      END_STATE();
    case 238:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(237);
      END_STATE();
    case 239:
      ACCEPT_TOKEN(anon_sym__);
      END_STATE();
    case 240:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 241:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 242:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'a') ADVANCE(317);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 243:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'a') ADVANCE(291);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 244:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'a') ADVANCE(275);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 245:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'a') ADVANCE(276);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 246:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'a') ADVANCE(277);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 247:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'a') ADVANCE(294);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 248:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'a') ADVANCE(300);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 249:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'b') ADVANCE(280);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 250:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'c') ADVANCE(270);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 251:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'c') ADVANCE(245);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 252:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'd') ADVANCE(365);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 253:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'd') ADVANCE(411);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 254:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'd') ADVANCE(390);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 255:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'd') ADVANCE(260);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 256:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'd') ADVANCE(263);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 257:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'd') ADVANCE(256);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 258:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'e') ADVANCE(389);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 259:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'e') ADVANCE(335);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 260:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'e') ADVANCE(407);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 261:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'e') ADVANCE(337);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 262:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'e') ADVANCE(405);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 263:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'e') ADVANCE(282);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 264:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'e') ADVANCE(292);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 265:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'e') ADVANCE(293);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 266:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'f') ADVANCE(306);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 267:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'g') ADVANCE(269);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 268:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'h') ADVANCE(401);
      if (lookahead == 't') ADVANCE(286);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 269:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'h') ADVANCE(307);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 270:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'h') ADVANCE(247);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 271:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'i') ADVANCE(318);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 272:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'i') ADVANCE(249);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 273:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'i') ADVANCE(251);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 274:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'l') ADVANCE(377);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 275:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'l') ADVANCE(387);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 276:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'l') ADVANCE(379);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 277:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'l') ADVANCE(381);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 278:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'l') ADVANCE(274);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 279:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'l') ADVANCE(304);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 280:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'l') ADVANCE(262);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 281:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'm') ADVANCE(369);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 282:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'n') ADVANCE(403);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 283:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'n') ADVANCE(310);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 284:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'n') ADVANCE(253);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 285:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'n') ADVANCE(311);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 286:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'o') ADVANCE(281);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 287:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'o') ADVANCE(315);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 288:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'o') ADVANCE(285);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 289:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'p') ADVANCE(367);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 290:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'r') ADVANCE(271);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 291:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'r') ADVANCE(393);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 292:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'r') ADVANCE(385);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 293:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'r') ADVANCE(371);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 294:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'r') ADVANCE(395);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 295:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'r') ADVANCE(287);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 296:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'r') ADVANCE(244);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 297:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'r') ADVANCE(309);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 298:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'r') ADVANCE(254);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 299:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'r') ADVANCE(295);
      if (lookahead == 't') ADVANCE(313);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 300:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'r') ADVANCE(308);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 301:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 's') ADVANCE(397);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 302:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 's') ADVANCE(383);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 303:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 's') ADVANCE(272);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 304:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 's') ADVANCE(261);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 305:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 't') ADVANCE(268);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 306:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 't') ADVANCE(375);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 307:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 't') ADVANCE(373);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 308:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 't') ADVANCE(363);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 309:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 't') ADVANCE(273);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 310:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 't') ADVANCE(265);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 311:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 't') ADVANCE(246);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 312:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'u') ADVANCE(259);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 313:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'u') ADVANCE(296);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 314:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'v') ADVANCE(264);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 315:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'w') ADVANCE(409);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 316:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'w') ADVANCE(242);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 317:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'y') ADVANCE(302);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 318:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == 'z') ADVANCE(288);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'y')) ADVANCE(319);
      END_STATE();
    case 319:
      ACCEPT_TOKEN(sym_object_id);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 320:
      ACCEPT_TOKEN(sym__object_fragment);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(320);
      END_STATE();
    case 321:
      ACCEPT_TOKEN(aux_sym_object_token1);
      END_STATE();
    case 322:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 323:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 324:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 325:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 326:
      ACCEPT_TOKEN(anon_sym_layout);
      END_STATE();
    case 327:
      ACCEPT_TOKEN(anon_sym_layout);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 328:
      ACCEPT_TOKEN(anon_sym_menu);
      END_STATE();
    case 329:
      ACCEPT_TOKEN(anon_sym_section);
      END_STATE();
    case 330:
      ACCEPT_TOKEN(anon_sym_item);
      END_STATE();
    case 331:
      ACCEPT_TOKEN(anon_sym_item);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 332:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 333:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 334:
      ACCEPT_TOKEN(anon_sym_true);
      END_STATE();
    case 335:
      ACCEPT_TOKEN(anon_sym_true);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 336:
      ACCEPT_TOKEN(anon_sym_false);
      END_STATE();
    case 337:
      ACCEPT_TOKEN(anon_sym_false);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 338:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == ':') ADVANCE(13);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 339:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == 'd') ADVANCE(345);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 340:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == 'e') ADVANCE(352);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 341:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == 'e') ADVANCE(347);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 342:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == 'f') ADVANCE(359);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 343:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == 'i') ADVANCE(342);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 344:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == 'i') ADVANCE(351);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 345:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == 'i') ADVANCE(355);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 346:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == 'l') ADVANCE(340);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 347:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == 'm') ADVANCE(331);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 348:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == 'n') ADVANCE(339);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 349:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == 'n') ADVANCE(419);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 350:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == 'o') ADVANCE(356);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 351:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == 'o') ADVANCE(349);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 352:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == 's') ADVANCE(421);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 353:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == 't') ADVANCE(343);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 354:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == 't') ADVANCE(327);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 355:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == 't') ADVANCE(344);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 356:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == 'u') ADVANCE(354);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 357:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == 'y') ADVANCE(350);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 358:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == 'y') ADVANCE(346);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 359:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == 'y') ADVANCE(338);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 360:
      ACCEPT_TOKEN(sym_property_name);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 361:
      ACCEPT_TOKEN(aux_sym_signal_name_token1);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(361);
      END_STATE();
    case 362:
      ACCEPT_TOKEN(anon_sym_start);
      END_STATE();
    case 363:
      ACCEPT_TOKEN(anon_sym_start);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 364:
      ACCEPT_TOKEN(anon_sym_end);
      END_STATE();
    case 365:
      ACCEPT_TOKEN(anon_sym_end);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 366:
      ACCEPT_TOKEN(anon_sym_top);
      END_STATE();
    case 367:
      ACCEPT_TOKEN(anon_sym_top);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 368:
      ACCEPT_TOKEN(anon_sym_bottom);
      END_STATE();
    case 369:
      ACCEPT_TOKEN(anon_sym_bottom);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 370:
      ACCEPT_TOKEN(anon_sym_center);
      END_STATE();
    case 371:
      ACCEPT_TOKEN(anon_sym_center);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 372:
      ACCEPT_TOKEN(anon_sym_right);
      END_STATE();
    case 373:
      ACCEPT_TOKEN(anon_sym_right);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 374:
      ACCEPT_TOKEN(anon_sym_left);
      END_STATE();
    case 375:
      ACCEPT_TOKEN(anon_sym_left);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 376:
      ACCEPT_TOKEN(anon_sym_fill);
      END_STATE();
    case 377:
      ACCEPT_TOKEN(anon_sym_fill);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 378:
      ACCEPT_TOKEN(anon_sym_vertical);
      END_STATE();
    case 379:
      ACCEPT_TOKEN(anon_sym_vertical);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 380:
      ACCEPT_TOKEN(anon_sym_horizontal);
      END_STATE();
    case 381:
      ACCEPT_TOKEN(anon_sym_horizontal);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 382:
      ACCEPT_TOKEN(anon_sym_always);
      END_STATE();
    case 383:
      ACCEPT_TOKEN(anon_sym_always);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 384:
      ACCEPT_TOKEN(anon_sym_never);
      END_STATE();
    case 385:
      ACCEPT_TOKEN(anon_sym_never);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 386:
      ACCEPT_TOKEN(anon_sym_natural);
      END_STATE();
    case 387:
      ACCEPT_TOKEN(anon_sym_natural);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 388:
      ACCEPT_TOKEN(anon_sym_none);
      END_STATE();
    case 389:
      ACCEPT_TOKEN(anon_sym_none);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 390:
      ACCEPT_TOKEN(anon_sym_word);
      if (lookahead == '_') ADVANCE(250);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 391:
      ACCEPT_TOKEN(anon_sym_word);
      if (lookahead == '_') ADVANCE(35);
      END_STATE();
    case 392:
      ACCEPT_TOKEN(anon_sym_char);
      END_STATE();
    case 393:
      ACCEPT_TOKEN(anon_sym_char);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 394:
      ACCEPT_TOKEN(anon_sym_word_char);
      END_STATE();
    case 395:
      ACCEPT_TOKEN(anon_sym_word_char);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 396:
      ACCEPT_TOKEN(anon_sym_yes);
      END_STATE();
    case 397:
      ACCEPT_TOKEN(anon_sym_yes);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 398:
      ACCEPT_TOKEN(anon_sym_no);
      if (lookahead == '-') ADVANCE(167);
      if (lookahead == 'n') ADVANCE(54);
      if (lookahead == 't') ADVANCE(93);
      END_STATE();
    case 399:
      ACCEPT_TOKEN(anon_sym_no);
      if (lookahead == 'n') ADVANCE(258);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 400:
      ACCEPT_TOKEN(anon_sym_both);
      END_STATE();
    case 401:
      ACCEPT_TOKEN(anon_sym_both);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 402:
      ACCEPT_TOKEN(anon_sym_hidden);
      END_STATE();
    case 403:
      ACCEPT_TOKEN(anon_sym_hidden);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 404:
      ACCEPT_TOKEN(anon_sym_visible);
      END_STATE();
    case 405:
      ACCEPT_TOKEN(anon_sym_visible);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 406:
      ACCEPT_TOKEN(anon_sym_wide);
      END_STATE();
    case 407:
      ACCEPT_TOKEN(anon_sym_wide);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 408:
      ACCEPT_TOKEN(anon_sym_narrow);
      END_STATE();
    case 409:
      ACCEPT_TOKEN(anon_sym_narrow);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 410:
      ACCEPT_TOKEN(anon_sym_bind);
      END_STATE();
    case 411:
      ACCEPT_TOKEN(anon_sym_bind);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(319);
      END_STATE();
    case 412:
      ACCEPT_TOKEN(anon_sym_no_DASHsync_DASHcreate);
      END_STATE();
    case 413:
      ACCEPT_TOKEN(anon_sym_bidirectional);
      END_STATE();
    case 414:
      ACCEPT_TOKEN(anon_sym_inverted);
      END_STATE();
    case 415:
      ACCEPT_TOKEN(anon_sym_DOLLAR);
      END_STATE();
    case 416:
      ACCEPT_TOKEN(anon_sym_EQ_GT);
      END_STATE();
    case 417:
      ACCEPT_TOKEN(anon_sym_swapped);
      END_STATE();
    case 418:
      ACCEPT_TOKEN(anon_sym_condition);
      END_STATE();
    case 419:
      ACCEPT_TOKEN(anon_sym_condition);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 420:
      ACCEPT_TOKEN(anon_sym_styles);
      END_STATE();
    case 421:
      ACCEPT_TOKEN(anon_sym_styles);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(360);
      END_STATE();
    case 422:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 423:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(423);
      END_STATE();
    case 424:
      ACCEPT_TOKEN(sym_float);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(424);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 214},
  [2] = {.lex_state = 2},
  [3] = {.lex_state = 2},
  [4] = {.lex_state = 2},
  [5] = {.lex_state = 10},
  [6] = {.lex_state = 10},
  [7] = {.lex_state = 10},
  [8] = {.lex_state = 10},
  [9] = {.lex_state = 10},
  [10] = {.lex_state = 214},
  [11] = {.lex_state = 214},
  [12] = {.lex_state = 1},
  [13] = {.lex_state = 10},
  [14] = {.lex_state = 10},
  [15] = {.lex_state = 10},
  [16] = {.lex_state = 10},
  [17] = {.lex_state = 10},
  [18] = {.lex_state = 10},
  [19] = {.lex_state = 10},
  [20] = {.lex_state = 10},
  [21] = {.lex_state = 1},
  [22] = {.lex_state = 10},
  [23] = {.lex_state = 10},
  [24] = {.lex_state = 10},
  [25] = {.lex_state = 10},
  [26] = {.lex_state = 10},
  [27] = {.lex_state = 10},
  [28] = {.lex_state = 10},
  [29] = {.lex_state = 214},
  [30] = {.lex_state = 214},
  [31] = {.lex_state = 214},
  [32] = {.lex_state = 214},
  [33] = {.lex_state = 214},
  [34] = {.lex_state = 214},
  [35] = {.lex_state = 214},
  [36] = {.lex_state = 214},
  [37] = {.lex_state = 214},
  [38] = {.lex_state = 11},
  [39] = {.lex_state = 11},
  [40] = {.lex_state = 214},
  [41] = {.lex_state = 0},
  [42] = {.lex_state = 0},
  [43] = {.lex_state = 0},
  [44] = {.lex_state = 0},
  [45] = {.lex_state = 1},
  [46] = {.lex_state = 1},
  [47] = {.lex_state = 1},
  [48] = {.lex_state = 1},
  [49] = {.lex_state = 0},
  [50] = {.lex_state = 1},
  [51] = {.lex_state = 0},
  [52] = {.lex_state = 11},
  [53] = {.lex_state = 214},
  [54] = {.lex_state = 1},
  [55] = {.lex_state = 214},
  [56] = {.lex_state = 214},
  [57] = {.lex_state = 0},
  [58] = {.lex_state = 12},
  [59] = {.lex_state = 1},
  [60] = {.lex_state = 214},
  [61] = {.lex_state = 3},
  [62] = {.lex_state = 4},
  [63] = {.lex_state = 12},
  [64] = {.lex_state = 12},
  [65] = {.lex_state = 0},
  [66] = {.lex_state = 0},
  [67] = {.lex_state = 3},
  [68] = {.lex_state = 4},
  [69] = {.lex_state = 214},
  [70] = {.lex_state = 0},
  [71] = {.lex_state = 3},
  [72] = {.lex_state = 4},
  [73] = {.lex_state = 0},
  [74] = {.lex_state = 0},
  [75] = {.lex_state = 12},
  [76] = {.lex_state = 12},
  [77] = {.lex_state = 0},
  [78] = {.lex_state = 214},
  [79] = {.lex_state = 1},
  [80] = {.lex_state = 214},
  [81] = {.lex_state = 1},
  [82] = {.lex_state = 0},
  [83] = {.lex_state = 0},
  [84] = {.lex_state = 0},
  [85] = {.lex_state = 0},
  [86] = {.lex_state = 1},
  [87] = {.lex_state = 0},
  [88] = {.lex_state = 0},
  [89] = {.lex_state = 0},
  [90] = {.lex_state = 0},
  [91] = {.lex_state = 1},
  [92] = {.lex_state = 0},
  [93] = {.lex_state = 214},
  [94] = {.lex_state = 0},
  [95] = {.lex_state = 0},
  [96] = {.lex_state = 0},
  [97] = {.lex_state = 1},
  [98] = {.lex_state = 0},
  [99] = {.lex_state = 0},
  [100] = {.lex_state = 11},
  [101] = {.lex_state = 0},
  [102] = {.lex_state = 1},
  [103] = {.lex_state = 1},
  [104] = {.lex_state = 12},
  [105] = {.lex_state = 0},
  [106] = {.lex_state = 0},
  [107] = {.lex_state = 0},
  [108] = {.lex_state = 0},
  [109] = {.lex_state = 1},
  [110] = {.lex_state = 0},
  [111] = {.lex_state = 0},
  [112] = {.lex_state = 1},
  [113] = {.lex_state = 0},
  [114] = {.lex_state = 0},
  [115] = {.lex_state = 0},
  [116] = {.lex_state = 0},
  [117] = {.lex_state = 0},
  [118] = {.lex_state = 214},
  [119] = {.lex_state = 0},
  [120] = {.lex_state = 214},
  [121] = {.lex_state = 0},
  [122] = {.lex_state = 1},
  [123] = {.lex_state = 0},
  [124] = {.lex_state = 1},
  [125] = {.lex_state = 0},
  [126] = {.lex_state = 0},
  [127] = {.lex_state = 0},
  [128] = {.lex_state = 0},
  [129] = {.lex_state = 0},
  [130] = {.lex_state = 1},
  [131] = {.lex_state = 0},
  [132] = {.lex_state = 0},
  [133] = {.lex_state = 1},
  [134] = {.lex_state = 0},
  [135] = {.lex_state = 0},
  [136] = {.lex_state = 0},
  [137] = {.lex_state = 0},
  [138] = {.lex_state = 0},
  [139] = {.lex_state = 214},
  [140] = {.lex_state = 0},
  [141] = {.lex_state = 0},
  [142] = {.lex_state = 0},
  [143] = {.lex_state = 0},
  [144] = {.lex_state = 0},
  [145] = {.lex_state = 214},
  [146] = {.lex_state = 0},
  [147] = {.lex_state = 0},
  [148] = {.lex_state = 0},
  [149] = {.lex_state = 0},
  [150] = {.lex_state = 0},
  [151] = {.lex_state = 0},
  [152] = {.lex_state = 0},
  [153] = {.lex_state = 0},
  [154] = {.lex_state = 0},
  [155] = {.lex_state = 12},
  [156] = {.lex_state = 0},
  [157] = {.lex_state = 0},
  [158] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_using] = ACTIONS(1),
    [sym_template] = ACTIONS(1),
    [sym__number] = ACTIONS(1),
    [anon_sym_DOT] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [anon_sym_SQUOTE] = ACTIONS(1),
    [sym_escape_sequence] = ACTIONS(1),
    [anon_sym__] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [sym__object_fragment] = ACTIONS(1),
    [aux_sym_object_token1] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [anon_sym_layout] = ACTIONS(1),
    [anon_sym_menu] = ACTIONS(1),
    [anon_sym_section] = ACTIONS(1),
    [anon_sym_item] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_true] = ACTIONS(1),
    [anon_sym_false] = ACTIONS(1),
    [aux_sym_signal_name_token1] = ACTIONS(1),
    [anon_sym_start] = ACTIONS(1),
    [anon_sym_end] = ACTIONS(1),
    [anon_sym_top] = ACTIONS(1),
    [anon_sym_bottom] = ACTIONS(1),
    [anon_sym_center] = ACTIONS(1),
    [anon_sym_right] = ACTIONS(1),
    [anon_sym_left] = ACTIONS(1),
    [anon_sym_fill] = ACTIONS(1),
    [anon_sym_vertical] = ACTIONS(1),
    [anon_sym_horizontal] = ACTIONS(1),
    [anon_sym_always] = ACTIONS(1),
    [anon_sym_never] = ACTIONS(1),
    [anon_sym_natural] = ACTIONS(1),
    [anon_sym_none] = ACTIONS(1),
    [anon_sym_word] = ACTIONS(1),
    [anon_sym_char] = ACTIONS(1),
    [anon_sym_word_char] = ACTIONS(1),
    [anon_sym_yes] = ACTIONS(1),
    [anon_sym_no] = ACTIONS(1),
    [anon_sym_both] = ACTIONS(1),
    [anon_sym_hidden] = ACTIONS(1),
    [anon_sym_visible] = ACTIONS(1),
    [anon_sym_wide] = ACTIONS(1),
    [anon_sym_narrow] = ACTIONS(1),
    [anon_sym_bind] = ACTIONS(1),
    [anon_sym_no_DASHsync_DASHcreate] = ACTIONS(1),
    [anon_sym_bidirectional] = ACTIONS(1),
    [anon_sym_inverted] = ACTIONS(1),
    [anon_sym_DOLLAR] = ACTIONS(1),
    [anon_sym_EQ_GT] = ACTIONS(1),
    [anon_sym_swapped] = ACTIONS(1),
    [anon_sym_condition] = ACTIONS(1),
    [anon_sym_styles] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
    [sym_float] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(147),
    [sym__toplevel] = STATE(11),
    [sym_import_statement] = STATE(11),
    [sym_object] = STATE(86),
    [sym_decorator] = STATE(80),
    [sym_object_definition] = STATE(11),
    [sym_menu_definition] = STATE(11),
    [sym_template_definition] = STATE(11),
    [aux_sym_source_file_repeat1] = STATE(11),
    [ts_builtin_sym_end] = ACTIONS(5),
    [sym_using] = ACTIONS(7),
    [sym_template] = ACTIONS(9),
    [sym__object_fragment] = ACTIONS(11),
    [aux_sym_object_token1] = ACTIONS(13),
    [anon_sym_LBRACK] = ACTIONS(15),
    [anon_sym_menu] = ACTIONS(17),
    [sym_comment] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      sym__object_fragment,
    ACTIONS(13), 1,
      aux_sym_object_token1,
    ACTIONS(15), 1,
      anon_sym_LBRACK,
    ACTIONS(19), 1,
      sym__number,
    ACTIONS(21), 1,
      anon_sym_DQUOTE,
    ACTIONS(23), 1,
      anon_sym_SQUOTE,
    ACTIONS(25), 1,
      anon_sym__,
    ACTIONS(27), 1,
      sym_object_id,
    ACTIONS(33), 1,
      anon_sym_bind,
    ACTIONS(35), 1,
      sym_float,
    STATE(80), 1,
      sym_decorator,
    STATE(86), 1,
      sym_object,
    ACTIONS(29), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(153), 9,
      sym_string,
      sym_gettext_string,
      sym_identifier,
      sym_object_definition,
      sym_boolean,
      sym_constant,
      sym__property_value,
      sym_property_binding,
      sym_number,
    ACTIONS(31), 24,
      anon_sym_start,
      anon_sym_end,
      anon_sym_top,
      anon_sym_bottom,
      anon_sym_center,
      anon_sym_right,
      anon_sym_left,
      anon_sym_fill,
      anon_sym_vertical,
      anon_sym_horizontal,
      anon_sym_always,
      anon_sym_never,
      anon_sym_natural,
      anon_sym_none,
      anon_sym_word,
      anon_sym_char,
      anon_sym_word_char,
      anon_sym_yes,
      anon_sym_no,
      anon_sym_both,
      anon_sym_hidden,
      anon_sym_visible,
      anon_sym_wide,
      anon_sym_narrow,
  [81] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      sym__object_fragment,
    ACTIONS(13), 1,
      aux_sym_object_token1,
    ACTIONS(15), 1,
      anon_sym_LBRACK,
    ACTIONS(19), 1,
      sym__number,
    ACTIONS(21), 1,
      anon_sym_DQUOTE,
    ACTIONS(23), 1,
      anon_sym_SQUOTE,
    ACTIONS(25), 1,
      anon_sym__,
    ACTIONS(27), 1,
      sym_object_id,
    ACTIONS(33), 1,
      anon_sym_bind,
    ACTIONS(37), 1,
      sym_float,
    STATE(80), 1,
      sym_decorator,
    STATE(86), 1,
      sym_object,
    ACTIONS(29), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(158), 9,
      sym_string,
      sym_gettext_string,
      sym_identifier,
      sym_object_definition,
      sym_boolean,
      sym_constant,
      sym__property_value,
      sym_property_binding,
      sym_number,
    ACTIONS(31), 24,
      anon_sym_start,
      anon_sym_end,
      anon_sym_top,
      anon_sym_bottom,
      anon_sym_center,
      anon_sym_right,
      anon_sym_left,
      anon_sym_fill,
      anon_sym_vertical,
      anon_sym_horizontal,
      anon_sym_always,
      anon_sym_never,
      anon_sym_natural,
      anon_sym_none,
      anon_sym_word,
      anon_sym_char,
      anon_sym_word_char,
      anon_sym_yes,
      anon_sym_no,
      anon_sym_both,
      anon_sym_hidden,
      anon_sym_visible,
      anon_sym_wide,
      anon_sym_narrow,
  [162] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      sym__object_fragment,
    ACTIONS(13), 1,
      aux_sym_object_token1,
    ACTIONS(15), 1,
      anon_sym_LBRACK,
    ACTIONS(19), 1,
      sym__number,
    ACTIONS(21), 1,
      anon_sym_DQUOTE,
    ACTIONS(23), 1,
      anon_sym_SQUOTE,
    ACTIONS(25), 1,
      anon_sym__,
    ACTIONS(27), 1,
      sym_object_id,
    ACTIONS(33), 1,
      anon_sym_bind,
    ACTIONS(39), 1,
      sym_float,
    STATE(80), 1,
      sym_decorator,
    STATE(86), 1,
      sym_object,
    ACTIONS(29), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(152), 9,
      sym_string,
      sym_gettext_string,
      sym_identifier,
      sym_object_definition,
      sym_boolean,
      sym_constant,
      sym__property_value,
      sym_property_binding,
      sym_number,
    ACTIONS(31), 24,
      anon_sym_start,
      anon_sym_end,
      anon_sym_top,
      anon_sym_bottom,
      anon_sym_center,
      anon_sym_right,
      anon_sym_left,
      anon_sym_fill,
      anon_sym_vertical,
      anon_sym_horizontal,
      anon_sym_always,
      anon_sym_never,
      anon_sym_natural,
      anon_sym_none,
      anon_sym_word,
      anon_sym_char,
      anon_sym_word_char,
      anon_sym_yes,
      anon_sym_no,
      anon_sym_both,
      anon_sym_hidden,
      anon_sym_visible,
      anon_sym_wide,
      anon_sym_narrow,
  [243] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(41), 1,
      sym__object_fragment,
    ACTIONS(44), 1,
      aux_sym_object_token1,
    ACTIONS(47), 1,
      anon_sym_RBRACE,
    ACTIONS(49), 1,
      anon_sym_LBRACK,
    ACTIONS(52), 1,
      anon_sym_layout,
    ACTIONS(55), 1,
      sym_property_name,
    ACTIONS(58), 1,
      aux_sym_signal_name_token1,
    ACTIONS(61), 1,
      anon_sym_condition,
    ACTIONS(64), 1,
      anon_sym_styles,
    STATE(78), 1,
      sym_decorator,
    STATE(102), 1,
      sym_object,
    STATE(135), 1,
      sym_signal_name,
    STATE(5), 7,
      sym_object_definition,
      sym_layout_definition,
      sym_property_definition,
      sym_signal_binding,
      sym_condition,
      sym_styles_list,
      aux_sym_block_repeat1,
  [292] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      sym__object_fragment,
    ACTIONS(13), 1,
      aux_sym_object_token1,
    ACTIONS(15), 1,
      anon_sym_LBRACK,
    ACTIONS(67), 1,
      anon_sym_RBRACE,
    ACTIONS(69), 1,
      anon_sym_layout,
    ACTIONS(71), 1,
      sym_property_name,
    ACTIONS(73), 1,
      aux_sym_signal_name_token1,
    ACTIONS(75), 1,
      anon_sym_condition,
    ACTIONS(77), 1,
      anon_sym_styles,
    STATE(78), 1,
      sym_decorator,
    STATE(102), 1,
      sym_object,
    STATE(135), 1,
      sym_signal_name,
    STATE(5), 7,
      sym_object_definition,
      sym_layout_definition,
      sym_property_definition,
      sym_signal_binding,
      sym_condition,
      sym_styles_list,
      aux_sym_block_repeat1,
  [341] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      sym__object_fragment,
    ACTIONS(13), 1,
      aux_sym_object_token1,
    ACTIONS(15), 1,
      anon_sym_LBRACK,
    ACTIONS(69), 1,
      anon_sym_layout,
    ACTIONS(71), 1,
      sym_property_name,
    ACTIONS(73), 1,
      aux_sym_signal_name_token1,
    ACTIONS(75), 1,
      anon_sym_condition,
    ACTIONS(77), 1,
      anon_sym_styles,
    ACTIONS(79), 1,
      anon_sym_RBRACE,
    STATE(78), 1,
      sym_decorator,
    STATE(102), 1,
      sym_object,
    STATE(135), 1,
      sym_signal_name,
    STATE(5), 7,
      sym_object_definition,
      sym_layout_definition,
      sym_property_definition,
      sym_signal_binding,
      sym_condition,
      sym_styles_list,
      aux_sym_block_repeat1,
  [390] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      sym__object_fragment,
    ACTIONS(13), 1,
      aux_sym_object_token1,
    ACTIONS(15), 1,
      anon_sym_LBRACK,
    ACTIONS(69), 1,
      anon_sym_layout,
    ACTIONS(71), 1,
      sym_property_name,
    ACTIONS(73), 1,
      aux_sym_signal_name_token1,
    ACTIONS(75), 1,
      anon_sym_condition,
    ACTIONS(77), 1,
      anon_sym_styles,
    ACTIONS(81), 1,
      anon_sym_RBRACE,
    STATE(78), 1,
      sym_decorator,
    STATE(102), 1,
      sym_object,
    STATE(135), 1,
      sym_signal_name,
    STATE(7), 7,
      sym_object_definition,
      sym_layout_definition,
      sym_property_definition,
      sym_signal_binding,
      sym_condition,
      sym_styles_list,
      aux_sym_block_repeat1,
  [439] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      sym__object_fragment,
    ACTIONS(13), 1,
      aux_sym_object_token1,
    ACTIONS(15), 1,
      anon_sym_LBRACK,
    ACTIONS(69), 1,
      anon_sym_layout,
    ACTIONS(71), 1,
      sym_property_name,
    ACTIONS(73), 1,
      aux_sym_signal_name_token1,
    ACTIONS(75), 1,
      anon_sym_condition,
    ACTIONS(77), 1,
      anon_sym_styles,
    ACTIONS(83), 1,
      anon_sym_RBRACE,
    STATE(78), 1,
      sym_decorator,
    STATE(102), 1,
      sym_object,
    STATE(135), 1,
      sym_signal_name,
    STATE(6), 7,
      sym_object_definition,
      sym_layout_definition,
      sym_property_definition,
      sym_signal_binding,
      sym_condition,
      sym_styles_list,
      aux_sym_block_repeat1,
  [488] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(85), 1,
      ts_builtin_sym_end,
    ACTIONS(87), 1,
      sym_using,
    ACTIONS(90), 1,
      sym_template,
    ACTIONS(93), 1,
      sym__object_fragment,
    ACTIONS(96), 1,
      aux_sym_object_token1,
    ACTIONS(99), 1,
      anon_sym_LBRACK,
    ACTIONS(102), 1,
      anon_sym_menu,
    STATE(80), 1,
      sym_decorator,
    STATE(86), 1,
      sym_object,
    STATE(10), 6,
      sym__toplevel,
      sym_import_statement,
      sym_object_definition,
      sym_menu_definition,
      sym_template_definition,
      aux_sym_source_file_repeat1,
  [527] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      sym_using,
    ACTIONS(9), 1,
      sym_template,
    ACTIONS(11), 1,
      sym__object_fragment,
    ACTIONS(13), 1,
      aux_sym_object_token1,
    ACTIONS(15), 1,
      anon_sym_LBRACK,
    ACTIONS(17), 1,
      anon_sym_menu,
    ACTIONS(105), 1,
      ts_builtin_sym_end,
    STATE(80), 1,
      sym_decorator,
    STATE(86), 1,
      sym_object,
    STATE(10), 6,
      sym__toplevel,
      sym_import_statement,
      sym_object_definition,
      sym_menu_definition,
      sym_template_definition,
      aux_sym_source_file_repeat1,
  [566] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(21), 1,
      anon_sym_DQUOTE,
    ACTIONS(23), 1,
      anon_sym_SQUOTE,
    ACTIONS(25), 1,
      anon_sym__,
    ACTIONS(107), 1,
      sym__number,
    ACTIONS(109), 1,
      sym_object_id,
    ACTIONS(111), 1,
      anon_sym_RBRACK,
    STATE(99), 4,
      sym_string,
      sym_gettext_string,
      sym_identifier,
      sym_number,
  [594] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(115), 4,
      anon_sym_layout,
      sym_property_name,
      anon_sym_condition,
      anon_sym_styles,
    ACTIONS(113), 5,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      aux_sym_signal_name_token1,
  [611] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(119), 4,
      anon_sym_layout,
      sym_property_name,
      anon_sym_condition,
      anon_sym_styles,
    ACTIONS(117), 5,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      aux_sym_signal_name_token1,
  [628] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(123), 4,
      anon_sym_layout,
      sym_property_name,
      anon_sym_condition,
      anon_sym_styles,
    ACTIONS(121), 5,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      aux_sym_signal_name_token1,
  [645] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(127), 4,
      anon_sym_layout,
      sym_property_name,
      anon_sym_condition,
      anon_sym_styles,
    ACTIONS(125), 5,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      aux_sym_signal_name_token1,
  [662] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(131), 4,
      anon_sym_layout,
      sym_property_name,
      anon_sym_condition,
      anon_sym_styles,
    ACTIONS(129), 5,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      aux_sym_signal_name_token1,
  [679] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(135), 4,
      anon_sym_layout,
      sym_property_name,
      anon_sym_condition,
      anon_sym_styles,
    ACTIONS(133), 5,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      aux_sym_signal_name_token1,
  [696] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(139), 4,
      anon_sym_layout,
      sym_property_name,
      anon_sym_condition,
      anon_sym_styles,
    ACTIONS(137), 5,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      aux_sym_signal_name_token1,
  [713] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(143), 4,
      anon_sym_layout,
      sym_property_name,
      anon_sym_condition,
      anon_sym_styles,
    ACTIONS(141), 5,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      aux_sym_signal_name_token1,
  [730] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(21), 1,
      anon_sym_DQUOTE,
    ACTIONS(23), 1,
      anon_sym_SQUOTE,
    ACTIONS(25), 1,
      anon_sym__,
    ACTIONS(107), 1,
      sym__number,
    ACTIONS(109), 1,
      sym_object_id,
    STATE(108), 4,
      sym_string,
      sym_gettext_string,
      sym_identifier,
      sym_number,
  [755] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(147), 4,
      anon_sym_layout,
      sym_property_name,
      anon_sym_condition,
      anon_sym_styles,
    ACTIONS(145), 5,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      aux_sym_signal_name_token1,
  [772] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(151), 4,
      anon_sym_layout,
      sym_property_name,
      anon_sym_condition,
      anon_sym_styles,
    ACTIONS(149), 5,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      aux_sym_signal_name_token1,
  [789] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(155), 4,
      anon_sym_layout,
      sym_property_name,
      anon_sym_condition,
      anon_sym_styles,
    ACTIONS(153), 5,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      aux_sym_signal_name_token1,
  [806] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(159), 4,
      anon_sym_layout,
      sym_property_name,
      anon_sym_condition,
      anon_sym_styles,
    ACTIONS(157), 5,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      aux_sym_signal_name_token1,
  [823] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(163), 4,
      anon_sym_layout,
      sym_property_name,
      anon_sym_condition,
      anon_sym_styles,
    ACTIONS(161), 5,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      aux_sym_signal_name_token1,
  [840] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(167), 4,
      anon_sym_layout,
      sym_property_name,
      anon_sym_condition,
      anon_sym_styles,
    ACTIONS(165), 5,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      aux_sym_signal_name_token1,
  [857] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(171), 4,
      anon_sym_layout,
      sym_property_name,
      anon_sym_condition,
      anon_sym_styles,
    ACTIONS(169), 5,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      aux_sym_signal_name_token1,
  [874] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(149), 8,
      ts_builtin_sym_end,
      sym_using,
      sym_template,
      anon_sym_SEMI,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_LBRACK,
      anon_sym_menu,
  [888] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(161), 8,
      ts_builtin_sym_end,
      sym_using,
      sym_template,
      anon_sym_SEMI,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_LBRACK,
      anon_sym_menu,
  [902] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(157), 8,
      ts_builtin_sym_end,
      sym_using,
      sym_template,
      anon_sym_SEMI,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_LBRACK,
      anon_sym_menu,
  [916] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(153), 8,
      ts_builtin_sym_end,
      sym_using,
      sym_template,
      anon_sym_SEMI,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_LBRACK,
      anon_sym_menu,
  [930] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(145), 8,
      ts_builtin_sym_end,
      sym_using,
      sym_template,
      anon_sym_SEMI,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_LBRACK,
      anon_sym_menu,
  [944] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(173), 7,
      ts_builtin_sym_end,
      sym_using,
      sym_template,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_LBRACK,
      anon_sym_menu,
  [957] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(175), 7,
      ts_builtin_sym_end,
      sym_using,
      sym_template,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_LBRACK,
      anon_sym_menu,
  [970] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(177), 7,
      ts_builtin_sym_end,
      sym_using,
      sym_template,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_LBRACK,
      anon_sym_menu,
  [983] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(179), 7,
      ts_builtin_sym_end,
      sym_using,
      sym_template,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_LBRACK,
      anon_sym_menu,
  [996] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(181), 1,
      anon_sym_RBRACE,
    ACTIONS(183), 1,
      anon_sym_item,
    ACTIONS(185), 1,
      sym_property_name,
    STATE(39), 2,
      sym_property_definition,
      aux_sym_layout_definition_repeat1,
    STATE(57), 2,
      sym_menu_item,
      aux_sym_menu_section_repeat1,
  [1017] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(183), 1,
      anon_sym_item,
    ACTIONS(185), 1,
      sym_property_name,
    ACTIONS(187), 1,
      anon_sym_RBRACE,
    STATE(52), 2,
      sym_property_definition,
      aux_sym_layout_definition_repeat1,
    STATE(77), 2,
      sym_menu_item,
      aux_sym_menu_section_repeat1,
  [1038] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(189), 7,
      ts_builtin_sym_end,
      sym_using,
      sym_template,
      sym__object_fragment,
      aux_sym_object_token1,
      anon_sym_LBRACK,
      anon_sym_menu,
  [1051] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(191), 1,
      anon_sym_RBRACE,
    ACTIONS(193), 1,
      anon_sym_section,
    ACTIONS(195), 1,
      anon_sym_item,
    STATE(43), 3,
      sym_menu_section,
      sym_menu_item,
      aux_sym_menu_definition_repeat1,
  [1069] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(197), 1,
      anon_sym_RBRACE,
    ACTIONS(199), 1,
      anon_sym_section,
    ACTIONS(202), 1,
      anon_sym_item,
    STATE(42), 3,
      sym_menu_section,
      sym_menu_item,
      aux_sym_menu_definition_repeat1,
  [1087] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(193), 1,
      anon_sym_section,
    ACTIONS(195), 1,
      anon_sym_item,
    ACTIONS(205), 1,
      anon_sym_RBRACE,
    STATE(42), 3,
      sym_menu_section,
      sym_menu_item,
      aux_sym_menu_definition_repeat1,
  [1105] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(191), 1,
      anon_sym_RBRACE,
    ACTIONS(193), 1,
      anon_sym_section,
    ACTIONS(195), 1,
      anon_sym_item,
    STATE(42), 3,
      sym_menu_section,
      sym_menu_item,
      aux_sym_menu_definition_repeat1,
  [1123] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(209), 1,
      anon_sym_DOT,
    STATE(48), 1,
      aux_sym_object_repeat1,
    ACTIONS(207), 4,
      sym__number,
      sym_object_id,
      anon_sym_LBRACE,
      anon_sym_COLON,
  [1139] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(209), 1,
      anon_sym_DOT,
    STATE(50), 1,
      aux_sym_object_repeat1,
    ACTIONS(207), 4,
      sym__number,
      sym_object_id,
      anon_sym_LBRACE,
      anon_sym_COLON,
  [1155] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(209), 1,
      anon_sym_DOT,
    STATE(45), 1,
      aux_sym_object_repeat1,
    ACTIONS(211), 4,
      sym__number,
      sym_object_id,
      anon_sym_LBRACE,
      anon_sym_COLON,
  [1171] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(215), 1,
      anon_sym_DOT,
    STATE(48), 1,
      aux_sym_object_repeat1,
    ACTIONS(213), 4,
      sym__number,
      sym_object_id,
      anon_sym_LBRACE,
      anon_sym_COLON,
  [1187] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(193), 1,
      anon_sym_section,
    ACTIONS(195), 1,
      anon_sym_item,
    ACTIONS(218), 1,
      anon_sym_RBRACE,
    STATE(44), 3,
      sym_menu_section,
      sym_menu_item,
      aux_sym_menu_definition_repeat1,
  [1205] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(209), 1,
      anon_sym_DOT,
    STATE(48), 1,
      aux_sym_object_repeat1,
    ACTIONS(220), 4,
      sym__number,
      sym_object_id,
      anon_sym_LBRACE,
      anon_sym_COLON,
  [1221] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(21), 1,
      anon_sym_DQUOTE,
    ACTIONS(23), 1,
      anon_sym_SQUOTE,
    ACTIONS(25), 1,
      anon_sym__,
    STATE(116), 2,
      sym_string,
      sym_gettext_string,
  [1238] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(222), 1,
      anon_sym_RBRACE,
    ACTIONS(224), 1,
      anon_sym_item,
    ACTIONS(226), 1,
      sym_property_name,
    STATE(52), 2,
      sym_property_definition,
      aux_sym_layout_definition_repeat1,
  [1255] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(229), 1,
      anon_sym_SEMI,
    STATE(56), 1,
      aux_sym_property_binding_repeat1,
    ACTIONS(231), 3,
      anon_sym_no_DASHsync_DASHcreate,
      anon_sym_bidirectional,
      anon_sym_inverted,
  [1270] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(213), 5,
      sym__number,
      anon_sym_DOT,
      sym_object_id,
      anon_sym_LBRACE,
      anon_sym_COLON,
  [1281] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(233), 1,
      anon_sym_SEMI,
    STATE(55), 1,
      aux_sym_property_binding_repeat1,
    ACTIONS(235), 3,
      anon_sym_no_DASHsync_DASHcreate,
      anon_sym_bidirectional,
      anon_sym_inverted,
  [1296] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(238), 1,
      anon_sym_SEMI,
    STATE(55), 1,
      aux_sym_property_binding_repeat1,
    ACTIONS(240), 3,
      anon_sym_no_DASHsync_DASHcreate,
      anon_sym_bidirectional,
      anon_sym_inverted,
  [1311] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(187), 1,
      anon_sym_RBRACE,
    ACTIONS(195), 1,
      anon_sym_item,
    STATE(65), 2,
      sym_menu_item,
      aux_sym_menu_section_repeat1,
  [1325] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(242), 1,
      anon_sym_RBRACE,
    ACTIONS(244), 1,
      sym_property_name,
    STATE(64), 2,
      sym_property_definition,
      aux_sym_layout_definition_repeat1,
  [1339] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(109), 1,
      sym_object_id,
    ACTIONS(246), 1,
      anon_sym_DOLLAR,
    STATE(111), 1,
      sym_function,
    STATE(129), 1,
      sym_identifier,
  [1355] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      sym__object_fragment,
    ACTIONS(13), 1,
      aux_sym_object_token1,
    STATE(146), 1,
      sym_object,
    STATE(151), 1,
      sym_template_name_qualifier,
  [1371] = 4,
    ACTIONS(248), 1,
      anon_sym_DQUOTE,
    ACTIONS(252), 1,
      sym_comment,
    STATE(67), 1,
      aux_sym_string_repeat1,
    ACTIONS(250), 2,
      sym_unescaped_double_string_fragment,
      sym_escape_sequence,
  [1385] = 4,
    ACTIONS(248), 1,
      anon_sym_SQUOTE,
    ACTIONS(252), 1,
      sym_comment,
    STATE(68), 1,
      aux_sym_string_repeat2,
    ACTIONS(254), 2,
      sym_unescaped_single_string_fragment,
      sym_escape_sequence,
  [1399] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(244), 1,
      sym_property_name,
    ACTIONS(256), 1,
      anon_sym_RBRACE,
    STATE(75), 2,
      sym_property_definition,
      aux_sym_layout_definition_repeat1,
  [1413] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(244), 1,
      sym_property_name,
    ACTIONS(258), 1,
      anon_sym_RBRACE,
    STATE(75), 2,
      sym_property_definition,
      aux_sym_layout_definition_repeat1,
  [1427] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(260), 1,
      anon_sym_RBRACE,
    ACTIONS(262), 1,
      anon_sym_item,
    STATE(65), 2,
      sym_menu_item,
      aux_sym_menu_section_repeat1,
  [1441] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(265), 4,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_RBRACK,
      anon_sym_COMMA,
  [1451] = 4,
    ACTIONS(252), 1,
      sym_comment,
    ACTIONS(267), 1,
      anon_sym_DQUOTE,
    STATE(71), 1,
      aux_sym_string_repeat1,
    ACTIONS(269), 2,
      sym_unescaped_double_string_fragment,
      sym_escape_sequence,
  [1465] = 4,
    ACTIONS(252), 1,
      sym_comment,
    ACTIONS(267), 1,
      anon_sym_SQUOTE,
    STATE(72), 1,
      aux_sym_string_repeat2,
    ACTIONS(271), 2,
      sym_unescaped_single_string_fragment,
      sym_escape_sequence,
  [1479] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      sym__object_fragment,
    ACTIONS(13), 1,
      aux_sym_object_token1,
    STATE(118), 1,
      sym_gobject_library,
    STATE(145), 1,
      sym_object,
  [1495] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(273), 4,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_RBRACK,
      anon_sym_COMMA,
  [1505] = 4,
    ACTIONS(252), 1,
      sym_comment,
    ACTIONS(275), 1,
      anon_sym_DQUOTE,
    STATE(71), 1,
      aux_sym_string_repeat1,
    ACTIONS(277), 2,
      sym_unescaped_double_string_fragment,
      sym_escape_sequence,
  [1519] = 4,
    ACTIONS(252), 1,
      sym_comment,
    ACTIONS(280), 1,
      anon_sym_SQUOTE,
    STATE(72), 1,
      aux_sym_string_repeat2,
    ACTIONS(282), 2,
      sym_unescaped_single_string_fragment,
      sym_escape_sequence,
  [1533] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(285), 4,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_RBRACK,
      anon_sym_COMMA,
  [1543] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(287), 4,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      anon_sym_RBRACK,
      anon_sym_COMMA,
  [1553] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(222), 1,
      anon_sym_RBRACE,
    ACTIONS(289), 1,
      sym_property_name,
    STATE(75), 2,
      sym_property_definition,
      aux_sym_layout_definition_repeat1,
  [1567] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(244), 1,
      sym_property_name,
    ACTIONS(292), 1,
      anon_sym_RBRACE,
    STATE(63), 2,
      sym_property_definition,
      aux_sym_layout_definition_repeat1,
  [1581] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(195), 1,
      anon_sym_item,
    ACTIONS(294), 1,
      anon_sym_RBRACE,
    STATE(65), 2,
      sym_menu_item,
      aux_sym_menu_section_repeat1,
  [1595] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      sym__object_fragment,
    ACTIONS(13), 1,
      aux_sym_object_token1,
    STATE(103), 1,
      sym_object,
  [1608] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(296), 1,
      anon_sym_DOT,
    ACTIONS(299), 1,
      anon_sym_SEMI,
    STATE(79), 1,
      aux_sym_version_number_repeat1,
  [1621] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      sym__object_fragment,
    ACTIONS(13), 1,
      aux_sym_object_token1,
    STATE(81), 1,
      sym_object,
  [1634] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(301), 1,
      sym_object_id,
    ACTIONS(303), 1,
      anon_sym_LBRACE,
    STATE(29), 1,
      sym_block,
  [1647] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(305), 3,
      anon_sym_RBRACE,
      anon_sym_section,
      anon_sym_item,
  [1656] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(21), 1,
      anon_sym_DQUOTE,
    ACTIONS(23), 1,
      anon_sym_SQUOTE,
    STATE(149), 1,
      sym_string,
  [1669] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(307), 3,
      anon_sym_RBRACE,
      anon_sym_section,
      anon_sym_item,
  [1678] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(21), 1,
      anon_sym_DQUOTE,
    ACTIONS(23), 1,
      anon_sym_SQUOTE,
    STATE(107), 1,
      sym_string,
  [1691] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(303), 1,
      anon_sym_LBRACE,
    ACTIONS(309), 1,
      sym_object_id,
    STATE(33), 1,
      sym_block,
  [1704] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(311), 1,
      anon_sym_RBRACK,
    ACTIONS(313), 1,
      anon_sym_COMMA,
    STATE(92), 1,
      aux_sym_array_repeat1,
  [1717] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(315), 3,
      anon_sym_RBRACE,
      anon_sym_section,
      anon_sym_item,
  [1726] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(21), 1,
      anon_sym_DQUOTE,
    ACTIONS(23), 1,
      anon_sym_SQUOTE,
    STATE(142), 1,
      sym_string,
  [1739] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(317), 3,
      anon_sym_RBRACE,
      anon_sym_section,
      anon_sym_item,
  [1748] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(319), 1,
      anon_sym_DOT,
    ACTIONS(321), 1,
      anon_sym_SEMI,
    STATE(97), 1,
      aux_sym_version_number_repeat1,
  [1761] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(323), 1,
      anon_sym_RBRACK,
    ACTIONS(325), 1,
      anon_sym_COMMA,
    STATE(92), 1,
      aux_sym_array_repeat1,
  [1774] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      sym__object_fragment,
    ACTIONS(13), 1,
      aux_sym_object_token1,
    STATE(117), 1,
      sym_object,
  [1787] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(328), 3,
      anon_sym_RBRACE,
      anon_sym_section,
      anon_sym_item,
  [1796] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(21), 1,
      anon_sym_DQUOTE,
    ACTIONS(23), 1,
      anon_sym_SQUOTE,
    STATE(134), 1,
      sym_string,
  [1809] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(330), 3,
      anon_sym_RBRACE,
      anon_sym_section,
      anon_sym_item,
  [1818] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(319), 1,
      anon_sym_DOT,
    ACTIONS(332), 1,
      anon_sym_SEMI,
    STATE(79), 1,
      aux_sym_version_number_repeat1,
  [1831] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(334), 3,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      anon_sym_COMMA,
  [1840] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(313), 1,
      anon_sym_COMMA,
    ACTIONS(336), 1,
      anon_sym_RBRACK,
    STATE(87), 1,
      aux_sym_array_repeat1,
  [1853] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(129), 1,
      anon_sym_RBRACE,
    ACTIONS(131), 2,
      anon_sym_item,
      sym_property_name,
  [1864] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(338), 3,
      anon_sym_RBRACE,
      anon_sym_section,
      anon_sym_item,
  [1873] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(340), 1,
      sym_object_id,
    ACTIONS(342), 1,
      anon_sym_LBRACE,
    STATE(22), 1,
      sym_block,
  [1886] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(342), 1,
      anon_sym_LBRACE,
    ACTIONS(344), 1,
      sym_object_id,
    STATE(23), 1,
      sym_block,
  [1899] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(129), 2,
      anon_sym_RBRACE,
      sym_property_name,
  [1907] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(346), 1,
      anon_sym_LPAREN,
    ACTIONS(348), 1,
      anon_sym_LBRACE,
  [1917] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(350), 1,
      anon_sym_COLON,
    ACTIONS(352), 1,
      anon_sym_EQ_GT,
  [1927] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(354), 1,
      anon_sym_RPAREN,
    ACTIONS(356), 1,
      anon_sym_COMMA,
  [1937] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(323), 2,
      anon_sym_RBRACK,
      anon_sym_COMMA,
  [1945] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(109), 1,
      sym_object_id,
    STATE(131), 1,
      sym_identifier,
  [1955] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(358), 2,
      anon_sym_SEMI,
      anon_sym_swapped,
  [1963] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(360), 1,
      anon_sym_SEMI,
    ACTIONS(362), 1,
      anon_sym_swapped,
  [1973] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(299), 2,
      anon_sym_DOT,
      anon_sym_SEMI,
  [1981] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(364), 1,
      anon_sym_LBRACK,
    STATE(14), 1,
      sym_array,
  [1991] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(366), 2,
      anon_sym_SEMI,
      anon_sym_swapped,
  [1999] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(303), 1,
      anon_sym_LBRACE,
    STATE(30), 1,
      sym_block,
  [2009] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(256), 1,
      anon_sym_RPAREN,
    ACTIONS(368), 1,
      anon_sym_COMMA,
  [2019] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(303), 1,
      anon_sym_LBRACE,
    STATE(34), 1,
      sym_block,
  [2029] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(370), 1,
      sym__number,
    STATE(143), 1,
      sym_version_number,
  [2039] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(342), 1,
      anon_sym_LBRACE,
    STATE(23), 1,
      sym_block,
  [2049] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(372), 2,
      sym__object_fragment,
      aux_sym_object_token1,
  [2057] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(342), 1,
      anon_sym_LBRACE,
    STATE(26), 1,
      sym_block,
  [2067] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(109), 1,
      sym_object_id,
    STATE(148), 1,
      sym_identifier,
  [2077] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(303), 1,
      anon_sym_LBRACE,
    STATE(29), 1,
      sym_block,
  [2087] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(374), 1,
      sym_object_id,
    ACTIONS(376), 1,
      anon_sym_LBRACE,
  [2097] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(378), 1,
      anon_sym_LPAREN,
  [2104] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(380), 1,
      anon_sym_RPAREN,
  [2111] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(382), 1,
      anon_sym_LBRACE,
  [2118] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(384), 1,
      anon_sym_LPAREN,
  [2125] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(386), 1,
      anon_sym_LPAREN,
  [2132] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(388), 1,
      sym_object_id,
  [2139] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(390), 1,
      anon_sym_LPAREN,
  [2146] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(392), 1,
      anon_sym_RPAREN,
  [2153] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(394), 1,
      anon_sym_DOT,
  [2160] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(396), 1,
      anon_sym_RPAREN,
  [2167] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(398), 1,
      anon_sym_EQ_GT,
  [2174] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(400), 1,
      anon_sym_LBRACE,
  [2181] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(402), 1,
      sym__object_fragment,
  [2188] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(404), 1,
      anon_sym_SEMI,
  [2195] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(406), 1,
      sym__number,
  [2202] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(352), 1,
      anon_sym_EQ_GT,
  [2209] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(408), 1,
      anon_sym_SEMI,
  [2216] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(410), 1,
      anon_sym_RPAREN,
  [2223] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(412), 1,
      anon_sym_SEMI,
  [2230] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(414), 1,
      anon_sym_COLON,
  [2237] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(416), 1,
      sym__number,
  [2244] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(418), 1,
      anon_sym_COLON,
  [2251] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(420), 1,
      ts_builtin_sym_end,
  [2258] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(422), 1,
      anon_sym_RBRACK,
  [2265] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(424), 1,
      anon_sym_RPAREN,
  [2272] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(426), 1,
      anon_sym_LBRACE,
  [2279] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(428), 1,
      anon_sym_COLON,
  [2286] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(430), 1,
      anon_sym_SEMI,
  [2293] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(432), 1,
      anon_sym_SEMI,
  [2300] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(434), 1,
      anon_sym_SEMI,
  [2307] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(436), 1,
      sym_property_name,
  [2314] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(438), 1,
      sym__object_fragment,
  [2321] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(440), 1,
      anon_sym_COLON,
  [2328] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(442), 1,
      anon_sym_SEMI,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 81,
  [SMALL_STATE(4)] = 162,
  [SMALL_STATE(5)] = 243,
  [SMALL_STATE(6)] = 292,
  [SMALL_STATE(7)] = 341,
  [SMALL_STATE(8)] = 390,
  [SMALL_STATE(9)] = 439,
  [SMALL_STATE(10)] = 488,
  [SMALL_STATE(11)] = 527,
  [SMALL_STATE(12)] = 566,
  [SMALL_STATE(13)] = 594,
  [SMALL_STATE(14)] = 611,
  [SMALL_STATE(15)] = 628,
  [SMALL_STATE(16)] = 645,
  [SMALL_STATE(17)] = 662,
  [SMALL_STATE(18)] = 679,
  [SMALL_STATE(19)] = 696,
  [SMALL_STATE(20)] = 713,
  [SMALL_STATE(21)] = 730,
  [SMALL_STATE(22)] = 755,
  [SMALL_STATE(23)] = 772,
  [SMALL_STATE(24)] = 789,
  [SMALL_STATE(25)] = 806,
  [SMALL_STATE(26)] = 823,
  [SMALL_STATE(27)] = 840,
  [SMALL_STATE(28)] = 857,
  [SMALL_STATE(29)] = 874,
  [SMALL_STATE(30)] = 888,
  [SMALL_STATE(31)] = 902,
  [SMALL_STATE(32)] = 916,
  [SMALL_STATE(33)] = 930,
  [SMALL_STATE(34)] = 944,
  [SMALL_STATE(35)] = 957,
  [SMALL_STATE(36)] = 970,
  [SMALL_STATE(37)] = 983,
  [SMALL_STATE(38)] = 996,
  [SMALL_STATE(39)] = 1017,
  [SMALL_STATE(40)] = 1038,
  [SMALL_STATE(41)] = 1051,
  [SMALL_STATE(42)] = 1069,
  [SMALL_STATE(43)] = 1087,
  [SMALL_STATE(44)] = 1105,
  [SMALL_STATE(45)] = 1123,
  [SMALL_STATE(46)] = 1139,
  [SMALL_STATE(47)] = 1155,
  [SMALL_STATE(48)] = 1171,
  [SMALL_STATE(49)] = 1187,
  [SMALL_STATE(50)] = 1205,
  [SMALL_STATE(51)] = 1221,
  [SMALL_STATE(52)] = 1238,
  [SMALL_STATE(53)] = 1255,
  [SMALL_STATE(54)] = 1270,
  [SMALL_STATE(55)] = 1281,
  [SMALL_STATE(56)] = 1296,
  [SMALL_STATE(57)] = 1311,
  [SMALL_STATE(58)] = 1325,
  [SMALL_STATE(59)] = 1339,
  [SMALL_STATE(60)] = 1355,
  [SMALL_STATE(61)] = 1371,
  [SMALL_STATE(62)] = 1385,
  [SMALL_STATE(63)] = 1399,
  [SMALL_STATE(64)] = 1413,
  [SMALL_STATE(65)] = 1427,
  [SMALL_STATE(66)] = 1441,
  [SMALL_STATE(67)] = 1451,
  [SMALL_STATE(68)] = 1465,
  [SMALL_STATE(69)] = 1479,
  [SMALL_STATE(70)] = 1495,
  [SMALL_STATE(71)] = 1505,
  [SMALL_STATE(72)] = 1519,
  [SMALL_STATE(73)] = 1533,
  [SMALL_STATE(74)] = 1543,
  [SMALL_STATE(75)] = 1553,
  [SMALL_STATE(76)] = 1567,
  [SMALL_STATE(77)] = 1581,
  [SMALL_STATE(78)] = 1595,
  [SMALL_STATE(79)] = 1608,
  [SMALL_STATE(80)] = 1621,
  [SMALL_STATE(81)] = 1634,
  [SMALL_STATE(82)] = 1647,
  [SMALL_STATE(83)] = 1656,
  [SMALL_STATE(84)] = 1669,
  [SMALL_STATE(85)] = 1678,
  [SMALL_STATE(86)] = 1691,
  [SMALL_STATE(87)] = 1704,
  [SMALL_STATE(88)] = 1717,
  [SMALL_STATE(89)] = 1726,
  [SMALL_STATE(90)] = 1739,
  [SMALL_STATE(91)] = 1748,
  [SMALL_STATE(92)] = 1761,
  [SMALL_STATE(93)] = 1774,
  [SMALL_STATE(94)] = 1787,
  [SMALL_STATE(95)] = 1796,
  [SMALL_STATE(96)] = 1809,
  [SMALL_STATE(97)] = 1818,
  [SMALL_STATE(98)] = 1831,
  [SMALL_STATE(99)] = 1840,
  [SMALL_STATE(100)] = 1853,
  [SMALL_STATE(101)] = 1864,
  [SMALL_STATE(102)] = 1873,
  [SMALL_STATE(103)] = 1886,
  [SMALL_STATE(104)] = 1899,
  [SMALL_STATE(105)] = 1907,
  [SMALL_STATE(106)] = 1917,
  [SMALL_STATE(107)] = 1927,
  [SMALL_STATE(108)] = 1937,
  [SMALL_STATE(109)] = 1945,
  [SMALL_STATE(110)] = 1955,
  [SMALL_STATE(111)] = 1963,
  [SMALL_STATE(112)] = 1973,
  [SMALL_STATE(113)] = 1981,
  [SMALL_STATE(114)] = 1991,
  [SMALL_STATE(115)] = 1999,
  [SMALL_STATE(116)] = 2009,
  [SMALL_STATE(117)] = 2019,
  [SMALL_STATE(118)] = 2029,
  [SMALL_STATE(119)] = 2039,
  [SMALL_STATE(120)] = 2049,
  [SMALL_STATE(121)] = 2057,
  [SMALL_STATE(122)] = 2067,
  [SMALL_STATE(123)] = 2077,
  [SMALL_STATE(124)] = 2087,
  [SMALL_STATE(125)] = 2097,
  [SMALL_STATE(126)] = 2104,
  [SMALL_STATE(127)] = 2111,
  [SMALL_STATE(128)] = 2118,
  [SMALL_STATE(129)] = 2125,
  [SMALL_STATE(130)] = 2132,
  [SMALL_STATE(131)] = 2139,
  [SMALL_STATE(132)] = 2146,
  [SMALL_STATE(133)] = 2153,
  [SMALL_STATE(134)] = 2160,
  [SMALL_STATE(135)] = 2167,
  [SMALL_STATE(136)] = 2174,
  [SMALL_STATE(137)] = 2181,
  [SMALL_STATE(138)] = 2188,
  [SMALL_STATE(139)] = 2195,
  [SMALL_STATE(140)] = 2202,
  [SMALL_STATE(141)] = 2209,
  [SMALL_STATE(142)] = 2216,
  [SMALL_STATE(143)] = 2223,
  [SMALL_STATE(144)] = 2230,
  [SMALL_STATE(145)] = 2237,
  [SMALL_STATE(146)] = 2244,
  [SMALL_STATE(147)] = 2251,
  [SMALL_STATE(148)] = 2258,
  [SMALL_STATE(149)] = 2265,
  [SMALL_STATE(150)] = 2272,
  [SMALL_STATE(151)] = 2279,
  [SMALL_STATE(152)] = 2286,
  [SMALL_STATE(153)] = 2293,
  [SMALL_STATE(154)] = 2300,
  [SMALL_STATE(155)] = 2307,
  [SMALL_STATE(156)] = 2314,
  [SMALL_STATE(157)] = 2321,
  [SMALL_STATE(158)] = 2328,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0, 0, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(137),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(122),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(124),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(98),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(125),
  [27] = {.entry = {.count = 1, .reusable = false}}, SHIFT(74),
  [29] = {.entry = {.count = 1, .reusable = false}}, SHIFT(154),
  [31] = {.entry = {.count = 1, .reusable = false}}, SHIFT(141),
  [33] = {.entry = {.count = 1, .reusable = false}}, SHIFT(130),
  [35] = {.entry = {.count = 1, .reusable = true}}, SHIFT(153),
  [37] = {.entry = {.count = 1, .reusable = true}}, SHIFT(158),
  [39] = {.entry = {.count = 1, .reusable = true}}, SHIFT(152),
  [41] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_block_repeat1, 2, 0, 0), SHIFT_REPEAT(47),
  [44] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_block_repeat1, 2, 0, 0), SHIFT_REPEAT(137),
  [47] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_block_repeat1, 2, 0, 0),
  [49] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_block_repeat1, 2, 0, 0), SHIFT_REPEAT(122),
  [52] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_block_repeat1, 2, 0, 0), SHIFT_REPEAT(127),
  [55] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_block_repeat1, 2, 0, 0), SHIFT_REPEAT(106),
  [58] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_block_repeat1, 2, 0, 0), SHIFT_REPEAT(140),
  [61] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_block_repeat1, 2, 0, 0), SHIFT_REPEAT(128),
  [64] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_block_repeat1, 2, 0, 0), SHIFT_REPEAT(113),
  [67] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [69] = {.entry = {.count = 1, .reusable = false}}, SHIFT(127),
  [71] = {.entry = {.count = 1, .reusable = false}}, SHIFT(106),
  [73] = {.entry = {.count = 1, .reusable = true}}, SHIFT(140),
  [75] = {.entry = {.count = 1, .reusable = false}}, SHIFT(128),
  [77] = {.entry = {.count = 1, .reusable = false}}, SHIFT(113),
  [79] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [81] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [83] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [85] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [87] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(69),
  [90] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(60),
  [93] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(47),
  [96] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(137),
  [99] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(122),
  [102] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(124),
  [105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [107] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [109] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [111] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [113] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_layout_definition, 4, 0, 0),
  [115] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_layout_definition, 4, 0, 0),
  [117] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_styles_list, 2, 0, 0),
  [119] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_styles_list, 2, 0, 0),
  [121] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_array, 2, 0, 0),
  [123] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_array, 2, 0, 0),
  [125] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_layout_definition, 3, 0, 0),
  [127] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_layout_definition, 3, 0, 0),
  [129] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_property_definition, 4, 0, 0),
  [131] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_property_definition, 4, 0, 0),
  [133] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_array, 3, 0, 0),
  [135] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_array, 3, 0, 0),
  [137] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_signal_binding, 4, 0, 0),
  [139] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_signal_binding, 4, 0, 0),
  [141] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_array, 4, 0, 0),
  [143] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_array, 4, 0, 0),
  [145] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_object_definition, 2, 0, 0),
  [147] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_object_definition, 2, 0, 0),
  [149] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_object_definition, 3, 0, 0),
  [151] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_object_definition, 3, 0, 0),
  [153] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block, 2, 0, 0),
  [155] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block, 2, 0, 0),
  [157] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block, 3, 0, 0),
  [159] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block, 3, 0, 0),
  [161] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_object_definition, 4, 0, 0),
  [163] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_object_definition, 4, 0, 0),
  [165] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_signal_binding, 5, 0, 0),
  [167] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_signal_binding, 5, 0, 0),
  [169] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_condition, 4, 0, 0),
  [171] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_condition, 4, 0, 0),
  [173] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_template_definition, 5, 0, 0),
  [175] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 4, 0, 0),
  [177] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_menu_definition, 3, 0, 0),
  [179] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_menu_definition, 4, 0, 0),
  [181] = {.entry = {.count = 1, .reusable = true}}, SHIFT(82),
  [183] = {.entry = {.count = 1, .reusable = false}}, SHIFT(105),
  [185] = {.entry = {.count = 1, .reusable = false}}, SHIFT(144),
  [187] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [189] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_menu_definition, 5, 0, 0),
  [191] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [193] = {.entry = {.count = 1, .reusable = true}}, SHIFT(136),
  [195] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [197] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_menu_definition_repeat1, 2, 0, 0),
  [199] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_menu_definition_repeat1, 2, 0, 0), SHIFT_REPEAT(136),
  [202] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_menu_definition_repeat1, 2, 0, 0), SHIFT_REPEAT(105),
  [205] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [207] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_object, 2, 0, 0),
  [209] = {.entry = {.count = 1, .reusable = true}}, SHIFT(156),
  [211] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_object, 1, 0, 0),
  [213] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_object_repeat1, 2, 0, 0),
  [215] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_object_repeat1, 2, 0, 0), SHIFT_REPEAT(156),
  [218] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [220] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_object, 3, 0, 0),
  [222] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_layout_definition_repeat1, 2, 0, 0),
  [224] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_layout_definition_repeat1, 2, 0, 0),
  [226] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_layout_definition_repeat1, 2, 0, 0), SHIFT_REPEAT(144),
  [229] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_property_binding, 4, 0, 0),
  [231] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [233] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_property_binding_repeat1, 2, 0, 0),
  [235] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_property_binding_repeat1, 2, 0, 0), SHIFT_REPEAT(55),
  [238] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_property_binding, 5, 0, 0),
  [240] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [242] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [244] = {.entry = {.count = 1, .reusable = true}}, SHIFT(157),
  [246] = {.entry = {.count = 1, .reusable = true}}, SHIFT(109),
  [248] = {.entry = {.count = 1, .reusable = false}}, SHIFT(66),
  [250] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [252] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [254] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [256] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [258] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [260] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_menu_section_repeat1, 2, 0, 0),
  [262] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_menu_section_repeat1, 2, 0, 0), SHIFT_REPEAT(105),
  [265] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 2, 0, 0),
  [267] = {.entry = {.count = 1, .reusable = false}}, SHIFT(70),
  [269] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [271] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [273] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 3, 0, 0),
  [275] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_repeat1, 2, 0, 0),
  [277] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_string_repeat1, 2, 0, 0), SHIFT_REPEAT(71),
  [280] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_repeat2, 2, 0, 0),
  [282] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_string_repeat2, 2, 0, 0), SHIFT_REPEAT(72),
  [285] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_gettext_string, 4, 0, 0),
  [287] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_identifier, 1, 0, 0),
  [289] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_layout_definition_repeat1, 2, 0, 0), SHIFT_REPEAT(157),
  [292] = {.entry = {.count = 1, .reusable = true}}, SHIFT(90),
  [294] = {.entry = {.count = 1, .reusable = true}}, SHIFT(88),
  [296] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_version_number_repeat1, 2, 0, 0), SHIFT_REPEAT(139),
  [299] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_version_number_repeat1, 2, 0, 0),
  [301] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [303] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [305] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_menu_section, 3, 0, 0),
  [307] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_menu_item, 4, 0, 0),
  [309] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [311] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [313] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [315] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_menu_section, 5, 0, 0),
  [317] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_menu_item, 3, 0, 0),
  [319] = {.entry = {.count = 1, .reusable = true}}, SHIFT(139),
  [321] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_version_number, 1, 0, 0),
  [323] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_array_repeat1, 2, 0, 0),
  [325] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_array_repeat1, 2, 0, 0), SHIFT_REPEAT(21),
  [328] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_menu_item, 6, 0, 0),
  [330] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_menu_item, 8, 0, 0),
  [332] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_version_number, 2, 0, 0),
  [334] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_number, 1, 0, 0),
  [336] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [338] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_menu_section, 4, 0, 0),
  [340] = {.entry = {.count = 1, .reusable = true}}, SHIFT(119),
  [342] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [344] = {.entry = {.count = 1, .reusable = true}}, SHIFT(121),
  [346] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [348] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [350] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [352] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_signal_name, 1, 0, 0),
  [354] = {.entry = {.count = 1, .reusable = true}}, SHIFT(94),
  [356] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [358] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function, 3, 0, 0),
  [360] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [362] = {.entry = {.count = 1, .reusable = true}}, SHIFT(138),
  [364] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [366] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function, 4, 0, 0),
  [368] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [370] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [372] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_decorator, 3, 0, 0),
  [374] = {.entry = {.count = 1, .reusable = true}}, SHIFT(150),
  [376] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [378] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [380] = {.entry = {.count = 1, .reusable = true}}, SHIFT(114),
  [382] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [384] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [386] = {.entry = {.count = 1, .reusable = true}}, SHIFT(132),
  [388] = {.entry = {.count = 1, .reusable = true}}, SHIFT(133),
  [390] = {.entry = {.count = 1, .reusable = true}}, SHIFT(126),
  [392] = {.entry = {.count = 1, .reusable = true}}, SHIFT(110),
  [394] = {.entry = {.count = 1, .reusable = true}}, SHIFT(155),
  [396] = {.entry = {.count = 1, .reusable = true}}, SHIFT(96),
  [398] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [400] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [402] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [404] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [406] = {.entry = {.count = 1, .reusable = true}}, SHIFT(112),
  [408] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_constant, 1, 0, 0),
  [410] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [412] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [414] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [416] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_gobject_library, 1, 0, 0),
  [418] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_template_name_qualifier, 1, 0, 0),
  [420] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [422] = {.entry = {.count = 1, .reusable = true}}, SHIFT(120),
  [424] = {.entry = {.count = 1, .reusable = true}}, SHIFT(73),
  [426] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [428] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [430] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [432] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [434] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_boolean, 1, 0, 0),
  [436] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [438] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [440] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [442] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
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

TS_PUBLIC const TSLanguage *tree_sitter_blueprint(void) {
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
