#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
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
#define STATE_COUNT 735
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 233
#define ALIAS_COUNT 0
#define TOKEN_COUNT 146
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 16
#define PRODUCTION_ID_COUNT 1

enum {
  sym_NAME = 1,
  anon_sym_COMMA = 2,
  anon_sym_SEMI = 3,
  anon_sym_TARGET = 4,
  anon_sym_LPAREN = 5,
  anon_sym_RPAREN = 6,
  anon_sym_SEARCH_DIR = 7,
  anon_sym_OUTPUT = 8,
  anon_sym_OUTPUT_FORMAT = 9,
  anon_sym_OUTPUT_ARCH = 10,
  anon_sym_FORCE_COMMON_ALLOCATION = 11,
  anon_sym_FORCE_GROUP_ALLOCATION = 12,
  anon_sym_INHIBIT_COMMON_ALLOCATION = 13,
  anon_sym_INPUT = 14,
  anon_sym_GROUP = 15,
  anon_sym_MAP = 16,
  anon_sym_INCLUDE = 17,
  anon_sym_NOCROSSREFS = 18,
  anon_sym_NOCROSSREFS_TO = 19,
  anon_sym_EXTERN = 20,
  anon_sym_INSERT = 21,
  anon_sym_AFTER = 22,
  anon_sym_BEFORE = 23,
  anon_sym_REGION_ALIAS = 24,
  anon_sym_LD_FEATURE = 25,
  anon_sym_AS_NEEDED = 26,
  anon_sym_SECTIONS = 27,
  anon_sym_LBRACE = 28,
  anon_sym_RBRACE = 29,
  anon_sym_ENTRY = 30,
  anon_sym_ASSERT = 31,
  anon_sym_SORT_BY_NAME = 32,
  anon_sym_SORT = 33,
  anon_sym_SORT_BY_ALIGNMENT = 34,
  anon_sym_SORT_NONE = 35,
  anon_sym_SORT_BY_INIT_PRIORITY = 36,
  anon_sym_REVERSE = 37,
  anon_sym_EXCLUDE_FILE = 38,
  anon_sym_AMP = 39,
  anon_sym_INPUT_SECTION_FLAGS = 40,
  anon_sym_LBRACK = 41,
  anon_sym_RBRACK = 42,
  anon_sym_KEEP = 43,
  anon_sym_CREATE_OBJECT_SYMBOLS = 44,
  anon_sym_CONSTRUCTORS = 45,
  anon_sym_ASCIZ = 46,
  anon_sym_FILL = 47,
  anon_sym_LINKER_VERSION = 48,
  anon_sym_QUAD = 49,
  anon_sym_SQUAD = 50,
  anon_sym_LONG = 51,
  anon_sym_SHORT = 52,
  anon_sym_BYTE = 53,
  anon_sym_PLUS_EQ = 54,
  anon_sym_DASH_EQ = 55,
  anon_sym_STAR_EQ = 56,
  anon_sym_SLASH_EQ = 57,
  anon_sym_LT_LT_EQ = 58,
  anon_sym_GT_GT_EQ = 59,
  anon_sym_AMP_EQ = 60,
  anon_sym_PIPE_EQ = 61,
  anon_sym_CARET_EQ = 62,
  anon_sym_EQ = 63,
  anon_sym_HIDDEN = 64,
  anon_sym_PROVIDE = 65,
  anon_sym_PROVIDE_HIDDEN = 66,
  anon_sym_MEMORY = 67,
  anon_sym_COLON = 68,
  anon_sym_ORIGIN = 69,
  anon_sym_o = 70,
  anon_sym_org = 71,
  anon_sym_LENGTH = 72,
  anon_sym_l = 73,
  anon_sym_len = 74,
  anon_sym_BANG = 75,
  anon_sym_STARTUP = 76,
  anon_sym_HLL = 77,
  anon_sym_SYSLIB = 78,
  anon_sym_FLOAT = 79,
  anon_sym_NOFLOAT = 80,
  anon_sym_DASH = 81,
  anon_sym_PLUS = 82,
  anon_sym_TILDE = 83,
  anon_sym_NEXT = 84,
  anon_sym_ABSOLUTE = 85,
  anon_sym_DATA_SEGMENT_END = 86,
  anon_sym_BLOCK = 87,
  anon_sym_LOG2CEIL = 88,
  anon_sym_STAR = 89,
  anon_sym_SLASH = 90,
  anon_sym_PERCENT = 91,
  anon_sym_LT_LT = 92,
  anon_sym_GT_GT = 93,
  anon_sym_EQ_EQ = 94,
  anon_sym_BANG_EQ = 95,
  anon_sym_LT_EQ = 96,
  anon_sym_GT_EQ = 97,
  anon_sym_LT = 98,
  anon_sym_GT = 99,
  anon_sym_CARET = 100,
  anon_sym_PIPE = 101,
  anon_sym_AMP_AMP = 102,
  anon_sym_PIPE_PIPE = 103,
  anon_sym_QMARK = 104,
  anon_sym_DEFINED = 105,
  anon_sym_CONSTANT = 106,
  anon_sym_SIZEOF_HEADERS = 107,
  anon_sym_ALIGNOF = 108,
  anon_sym_SIZEOF = 109,
  anon_sym_ADDR = 110,
  anon_sym_LOADADDR = 111,
  anon_sym_ALIGN = 112,
  anon_sym_DATA_SEGMENT_ALIGN = 113,
  anon_sym_DATA_SEGMENT_RELRO_END = 114,
  anon_sym_MAX = 115,
  anon_sym_MIN = 116,
  anon_sym_SEGMENT_START = 117,
  anon_sym_AT = 118,
  anon_sym_SUBALIGN = 119,
  anon_sym_ONLY_IF_RO = 120,
  anon_sym_ONLY_IF_RW = 121,
  anon_sym_SPECIAL = 122,
  anon_sym_ALIGN_WITH_INPUT = 123,
  anon_sym_OVERLAY = 124,
  anon_sym_NOLOAD = 125,
  anon_sym_DSECT = 126,
  anon_sym_COPY = 127,
  anon_sym_INFO = 128,
  anon_sym_READONLY = 129,
  anon_sym_TYPE = 130,
  anon_sym_BIND = 131,
  anon_sym_PHDRS = 132,
  anon_sym_VERSION = 133,
  anon_sym_global = 134,
  anon_sym_local = 135,
  anon_sym_extern = 136,
  sym_SYMBOLNAME = 137,
  sym_LNAME = 138,
  sym_wildcard_name = 139,
  aux_sym_INT_token1 = 140,
  aux_sym_INT_token2 = 141,
  aux_sym_INT_token3 = 142,
  sym_VERS_TAG = 143,
  sym_VERS_IDENTIFIER = 144,
  sym_comment = 145,
  sym_script_file = 146,
  sym_extern_name_list = 147,
  sym_filename = 148,
  sym_ifile_p1 = 149,
  sym_input_list = 150,
  sym_sections = 151,
  sym_sec_or_group_p1 = 152,
  sym_statement_anywhere = 153,
  sym_section_name_spec = 154,
  sym_wildcard_maybe_exclude = 155,
  sym_wildcard_maybe_reverse = 156,
  sym_filename_spec = 157,
  sym_sect_flag_list = 158,
  sym_sect_flags = 159,
  sym_exclude_name_list = 160,
  sym_section_name_list = 161,
  sym_input_section_spec_no_keep = 162,
  sym_input_section_spec = 163,
  sym_statement = 164,
  sym_statement_list = 165,
  sym_length = 166,
  sym_fill_exp = 167,
  sym_assign_op = 168,
  sym_separator = 169,
  sym_assignment = 170,
  sym_memory = 171,
  sym_memory_spec_list = 172,
  sym_memory_spec = 173,
  sym_origin_spec = 174,
  sym_length_spec = 175,
  sym_attributes = 176,
  sym_attributes_list = 177,
  sym_attributes_string = 178,
  sym_startup = 179,
  sym_high_level_library = 180,
  sym_high_level_library_NAME_list = 181,
  sym_low_level_library = 182,
  sym_low_level_library_NAME_list = 183,
  sym_floating_point_support = 184,
  sym_nocrossref_list = 185,
  sym_paren_script_name = 186,
  sym_mustbe_exp = 187,
  sym_exp = 188,
  sym_memspec_at = 189,
  sym_at = 190,
  sym_align = 191,
  sym_subalign = 192,
  sym_sect_constraint = 193,
  sym_section = 194,
  sym_type = 195,
  sym_atype = 196,
  sym_opt_exp_with_type = 197,
  sym_opt_exp_without_type = 198,
  sym_memspec = 199,
  sym_phdr_opt = 200,
  sym_phdrs = 201,
  sym_phdr_list = 202,
  sym_phdr = 203,
  sym_phdr_type = 204,
  sym_phdr_qualifiers = 205,
  sym_phdr_val = 206,
  sym_overlay_section = 207,
  sym_version = 208,
  sym_vers_nodes = 209,
  sym_vers_node = 210,
  sym_verdep = 211,
  sym_vers_tag = 212,
  sym_vers_defns = 213,
  sym_INT = 214,
  aux_sym_script_file_repeat1 = 215,
  aux_sym_extern_name_list_repeat1 = 216,
  aux_sym_input_list_repeat1 = 217,
  aux_sym_sec_or_group_p1_repeat1 = 218,
  aux_sym_sect_flag_list_repeat1 = 219,
  aux_sym_exclude_name_list_repeat1 = 220,
  aux_sym_section_name_list_repeat1 = 221,
  aux_sym_statement_list_repeat1 = 222,
  aux_sym_memory_spec_list_repeat1 = 223,
  aux_sym_attributes_list_repeat1 = 224,
  aux_sym_high_level_library_NAME_list_repeat1 = 225,
  aux_sym_low_level_library_NAME_list_repeat1 = 226,
  aux_sym_low_level_library_NAME_list_repeat2 = 227,
  aux_sym_phdr_list_repeat1 = 228,
  aux_sym_phdr_qualifiers_repeat1 = 229,
  aux_sym_overlay_section_repeat1 = 230,
  aux_sym_vers_nodes_repeat1 = 231,
  aux_sym_verdep_repeat1 = 232,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_NAME] = "NAME",
  [anon_sym_COMMA] = ",",
  [anon_sym_SEMI] = ";",
  [anon_sym_TARGET] = "TARGET",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_SEARCH_DIR] = "SEARCH_DIR",
  [anon_sym_OUTPUT] = "OUTPUT",
  [anon_sym_OUTPUT_FORMAT] = "OUTPUT_FORMAT",
  [anon_sym_OUTPUT_ARCH] = "OUTPUT_ARCH",
  [anon_sym_FORCE_COMMON_ALLOCATION] = "FORCE_COMMON_ALLOCATION",
  [anon_sym_FORCE_GROUP_ALLOCATION] = "FORCE_GROUP_ALLOCATION",
  [anon_sym_INHIBIT_COMMON_ALLOCATION] = "INHIBIT_COMMON_ALLOCATION",
  [anon_sym_INPUT] = "INPUT",
  [anon_sym_GROUP] = "GROUP",
  [anon_sym_MAP] = "MAP",
  [anon_sym_INCLUDE] = "INCLUDE",
  [anon_sym_NOCROSSREFS] = "NOCROSSREFS",
  [anon_sym_NOCROSSREFS_TO] = "NOCROSSREFS_TO",
  [anon_sym_EXTERN] = "EXTERN",
  [anon_sym_INSERT] = "INSERT",
  [anon_sym_AFTER] = "AFTER",
  [anon_sym_BEFORE] = "BEFORE",
  [anon_sym_REGION_ALIAS] = "REGION_ALIAS",
  [anon_sym_LD_FEATURE] = "LD_FEATURE",
  [anon_sym_AS_NEEDED] = "AS_NEEDED",
  [anon_sym_SECTIONS] = "SECTIONS",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_ENTRY] = "ENTRY",
  [anon_sym_ASSERT] = "ASSERT",
  [anon_sym_SORT_BY_NAME] = "SORT_BY_NAME",
  [anon_sym_SORT] = "SORT",
  [anon_sym_SORT_BY_ALIGNMENT] = "SORT_BY_ALIGNMENT",
  [anon_sym_SORT_NONE] = "SORT_NONE",
  [anon_sym_SORT_BY_INIT_PRIORITY] = "SORT_BY_INIT_PRIORITY",
  [anon_sym_REVERSE] = "REVERSE",
  [anon_sym_EXCLUDE_FILE] = "EXCLUDE_FILE",
  [anon_sym_AMP] = "&",
  [anon_sym_INPUT_SECTION_FLAGS] = "INPUT_SECTION_FLAGS",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [anon_sym_KEEP] = "KEEP",
  [anon_sym_CREATE_OBJECT_SYMBOLS] = "CREATE_OBJECT_SYMBOLS",
  [anon_sym_CONSTRUCTORS] = "CONSTRUCTORS",
  [anon_sym_ASCIZ] = "ASCIZ",
  [anon_sym_FILL] = "FILL",
  [anon_sym_LINKER_VERSION] = "LINKER_VERSION",
  [anon_sym_QUAD] = "QUAD",
  [anon_sym_SQUAD] = "SQUAD",
  [anon_sym_LONG] = "LONG",
  [anon_sym_SHORT] = "SHORT",
  [anon_sym_BYTE] = "BYTE",
  [anon_sym_PLUS_EQ] = "+=",
  [anon_sym_DASH_EQ] = "-=",
  [anon_sym_STAR_EQ] = "*=",
  [anon_sym_SLASH_EQ] = "/=",
  [anon_sym_LT_LT_EQ] = "<<=",
  [anon_sym_GT_GT_EQ] = ">>=",
  [anon_sym_AMP_EQ] = "&=",
  [anon_sym_PIPE_EQ] = "|=",
  [anon_sym_CARET_EQ] = "^=",
  [anon_sym_EQ] = "=",
  [anon_sym_HIDDEN] = "HIDDEN",
  [anon_sym_PROVIDE] = "PROVIDE",
  [anon_sym_PROVIDE_HIDDEN] = "PROVIDE_HIDDEN",
  [anon_sym_MEMORY] = "MEMORY",
  [anon_sym_COLON] = ":",
  [anon_sym_ORIGIN] = "ORIGIN",
  [anon_sym_o] = "o",
  [anon_sym_org] = "org",
  [anon_sym_LENGTH] = "LENGTH",
  [anon_sym_l] = "l",
  [anon_sym_len] = "len",
  [anon_sym_BANG] = "!",
  [anon_sym_STARTUP] = "STARTUP",
  [anon_sym_HLL] = "HLL",
  [anon_sym_SYSLIB] = "SYSLIB",
  [anon_sym_FLOAT] = "FLOAT",
  [anon_sym_NOFLOAT] = "NOFLOAT",
  [anon_sym_DASH] = "-",
  [anon_sym_PLUS] = "+",
  [anon_sym_TILDE] = "~",
  [anon_sym_NEXT] = "NEXT",
  [anon_sym_ABSOLUTE] = "ABSOLUTE",
  [anon_sym_DATA_SEGMENT_END] = "DATA_SEGMENT_END",
  [anon_sym_BLOCK] = "BLOCK",
  [anon_sym_LOG2CEIL] = "LOG2CEIL",
  [anon_sym_STAR] = "*",
  [anon_sym_SLASH] = "/",
  [anon_sym_PERCENT] = "%",
  [anon_sym_LT_LT] = "<<",
  [anon_sym_GT_GT] = ">>",
  [anon_sym_EQ_EQ] = "==",
  [anon_sym_BANG_EQ] = "!=",
  [anon_sym_LT_EQ] = "<=",
  [anon_sym_GT_EQ] = ">=",
  [anon_sym_LT] = "<",
  [anon_sym_GT] = ">",
  [anon_sym_CARET] = "^",
  [anon_sym_PIPE] = "|",
  [anon_sym_AMP_AMP] = "&&",
  [anon_sym_PIPE_PIPE] = "||",
  [anon_sym_QMARK] = "\?",
  [anon_sym_DEFINED] = "DEFINED",
  [anon_sym_CONSTANT] = "CONSTANT",
  [anon_sym_SIZEOF_HEADERS] = "SIZEOF_HEADERS",
  [anon_sym_ALIGNOF] = "ALIGNOF",
  [anon_sym_SIZEOF] = "SIZEOF",
  [anon_sym_ADDR] = "ADDR",
  [anon_sym_LOADADDR] = "LOADADDR",
  [anon_sym_ALIGN] = "ALIGN",
  [anon_sym_DATA_SEGMENT_ALIGN] = "DATA_SEGMENT_ALIGN",
  [anon_sym_DATA_SEGMENT_RELRO_END] = "DATA_SEGMENT_RELRO_END",
  [anon_sym_MAX] = "MAX",
  [anon_sym_MIN] = "MIN",
  [anon_sym_SEGMENT_START] = "SEGMENT_START",
  [anon_sym_AT] = "AT",
  [anon_sym_SUBALIGN] = "SUBALIGN",
  [anon_sym_ONLY_IF_RO] = "ONLY_IF_RO",
  [anon_sym_ONLY_IF_RW] = "ONLY_IF_RW",
  [anon_sym_SPECIAL] = "SPECIAL",
  [anon_sym_ALIGN_WITH_INPUT] = "ALIGN_WITH_INPUT",
  [anon_sym_OVERLAY] = "OVERLAY",
  [anon_sym_NOLOAD] = "NOLOAD",
  [anon_sym_DSECT] = "DSECT",
  [anon_sym_COPY] = "COPY",
  [anon_sym_INFO] = "INFO",
  [anon_sym_READONLY] = "READONLY",
  [anon_sym_TYPE] = "TYPE",
  [anon_sym_BIND] = "BIND",
  [anon_sym_PHDRS] = "PHDRS",
  [anon_sym_VERSION] = "VERSION",
  [anon_sym_global] = "global",
  [anon_sym_local] = "local",
  [anon_sym_extern] = "extern",
  [sym_SYMBOLNAME] = "SYMBOLNAME",
  [sym_LNAME] = "LNAME",
  [sym_wildcard_name] = "wildcard_name",
  [aux_sym_INT_token1] = "INT_token1",
  [aux_sym_INT_token2] = "INT_token2",
  [aux_sym_INT_token3] = "INT_token3",
  [sym_VERS_TAG] = "VERS_TAG",
  [sym_VERS_IDENTIFIER] = "VERS_IDENTIFIER",
  [sym_comment] = "comment",
  [sym_script_file] = "script_file",
  [sym_extern_name_list] = "extern_name_list",
  [sym_filename] = "filename",
  [sym_ifile_p1] = "ifile_p1",
  [sym_input_list] = "input_list",
  [sym_sections] = "sections",
  [sym_sec_or_group_p1] = "sec_or_group_p1",
  [sym_statement_anywhere] = "statement_anywhere",
  [sym_section_name_spec] = "section_name_spec",
  [sym_wildcard_maybe_exclude] = "wildcard_maybe_exclude",
  [sym_wildcard_maybe_reverse] = "wildcard_maybe_reverse",
  [sym_filename_spec] = "filename_spec",
  [sym_sect_flag_list] = "sect_flag_list",
  [sym_sect_flags] = "sect_flags",
  [sym_exclude_name_list] = "exclude_name_list",
  [sym_section_name_list] = "section_name_list",
  [sym_input_section_spec_no_keep] = "input_section_spec_no_keep",
  [sym_input_section_spec] = "input_section_spec",
  [sym_statement] = "statement",
  [sym_statement_list] = "statement_list",
  [sym_length] = "length",
  [sym_fill_exp] = "fill_exp",
  [sym_assign_op] = "assign_op",
  [sym_separator] = "separator",
  [sym_assignment] = "assignment",
  [sym_memory] = "memory",
  [sym_memory_spec_list] = "memory_spec_list",
  [sym_memory_spec] = "memory_spec",
  [sym_origin_spec] = "origin_spec",
  [sym_length_spec] = "length_spec",
  [sym_attributes] = "attributes",
  [sym_attributes_list] = "attributes_list",
  [sym_attributes_string] = "attributes_string",
  [sym_startup] = "startup",
  [sym_high_level_library] = "high_level_library",
  [sym_high_level_library_NAME_list] = "high_level_library_NAME_list",
  [sym_low_level_library] = "low_level_library",
  [sym_low_level_library_NAME_list] = "low_level_library_NAME_list",
  [sym_floating_point_support] = "floating_point_support",
  [sym_nocrossref_list] = "nocrossref_list",
  [sym_paren_script_name] = "paren_script_name",
  [sym_mustbe_exp] = "mustbe_exp",
  [sym_exp] = "exp",
  [sym_memspec_at] = "memspec_at",
  [sym_at] = "at",
  [sym_align] = "align",
  [sym_subalign] = "subalign",
  [sym_sect_constraint] = "sect_constraint",
  [sym_section] = "section",
  [sym_type] = "type",
  [sym_atype] = "atype",
  [sym_opt_exp_with_type] = "opt_exp_with_type",
  [sym_opt_exp_without_type] = "opt_exp_without_type",
  [sym_memspec] = "memspec",
  [sym_phdr_opt] = "phdr_opt",
  [sym_phdrs] = "phdrs",
  [sym_phdr_list] = "phdr_list",
  [sym_phdr] = "phdr",
  [sym_phdr_type] = "phdr_type",
  [sym_phdr_qualifiers] = "phdr_qualifiers",
  [sym_phdr_val] = "phdr_val",
  [sym_overlay_section] = "overlay_section",
  [sym_version] = "version",
  [sym_vers_nodes] = "vers_nodes",
  [sym_vers_node] = "vers_node",
  [sym_verdep] = "verdep",
  [sym_vers_tag] = "vers_tag",
  [sym_vers_defns] = "vers_defns",
  [sym_INT] = "INT",
  [aux_sym_script_file_repeat1] = "script_file_repeat1",
  [aux_sym_extern_name_list_repeat1] = "extern_name_list_repeat1",
  [aux_sym_input_list_repeat1] = "input_list_repeat1",
  [aux_sym_sec_or_group_p1_repeat1] = "sec_or_group_p1_repeat1",
  [aux_sym_sect_flag_list_repeat1] = "sect_flag_list_repeat1",
  [aux_sym_exclude_name_list_repeat1] = "exclude_name_list_repeat1",
  [aux_sym_section_name_list_repeat1] = "section_name_list_repeat1",
  [aux_sym_statement_list_repeat1] = "statement_list_repeat1",
  [aux_sym_memory_spec_list_repeat1] = "memory_spec_list_repeat1",
  [aux_sym_attributes_list_repeat1] = "attributes_list_repeat1",
  [aux_sym_high_level_library_NAME_list_repeat1] = "high_level_library_NAME_list_repeat1",
  [aux_sym_low_level_library_NAME_list_repeat1] = "low_level_library_NAME_list_repeat1",
  [aux_sym_low_level_library_NAME_list_repeat2] = "low_level_library_NAME_list_repeat2",
  [aux_sym_phdr_list_repeat1] = "phdr_list_repeat1",
  [aux_sym_phdr_qualifiers_repeat1] = "phdr_qualifiers_repeat1",
  [aux_sym_overlay_section_repeat1] = "overlay_section_repeat1",
  [aux_sym_vers_nodes_repeat1] = "vers_nodes_repeat1",
  [aux_sym_verdep_repeat1] = "verdep_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_NAME] = sym_NAME,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_TARGET] = anon_sym_TARGET,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_SEARCH_DIR] = anon_sym_SEARCH_DIR,
  [anon_sym_OUTPUT] = anon_sym_OUTPUT,
  [anon_sym_OUTPUT_FORMAT] = anon_sym_OUTPUT_FORMAT,
  [anon_sym_OUTPUT_ARCH] = anon_sym_OUTPUT_ARCH,
  [anon_sym_FORCE_COMMON_ALLOCATION] = anon_sym_FORCE_COMMON_ALLOCATION,
  [anon_sym_FORCE_GROUP_ALLOCATION] = anon_sym_FORCE_GROUP_ALLOCATION,
  [anon_sym_INHIBIT_COMMON_ALLOCATION] = anon_sym_INHIBIT_COMMON_ALLOCATION,
  [anon_sym_INPUT] = anon_sym_INPUT,
  [anon_sym_GROUP] = anon_sym_GROUP,
  [anon_sym_MAP] = anon_sym_MAP,
  [anon_sym_INCLUDE] = anon_sym_INCLUDE,
  [anon_sym_NOCROSSREFS] = anon_sym_NOCROSSREFS,
  [anon_sym_NOCROSSREFS_TO] = anon_sym_NOCROSSREFS_TO,
  [anon_sym_EXTERN] = anon_sym_EXTERN,
  [anon_sym_INSERT] = anon_sym_INSERT,
  [anon_sym_AFTER] = anon_sym_AFTER,
  [anon_sym_BEFORE] = anon_sym_BEFORE,
  [anon_sym_REGION_ALIAS] = anon_sym_REGION_ALIAS,
  [anon_sym_LD_FEATURE] = anon_sym_LD_FEATURE,
  [anon_sym_AS_NEEDED] = anon_sym_AS_NEEDED,
  [anon_sym_SECTIONS] = anon_sym_SECTIONS,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_ENTRY] = anon_sym_ENTRY,
  [anon_sym_ASSERT] = anon_sym_ASSERT,
  [anon_sym_SORT_BY_NAME] = anon_sym_SORT_BY_NAME,
  [anon_sym_SORT] = anon_sym_SORT,
  [anon_sym_SORT_BY_ALIGNMENT] = anon_sym_SORT_BY_ALIGNMENT,
  [anon_sym_SORT_NONE] = anon_sym_SORT_NONE,
  [anon_sym_SORT_BY_INIT_PRIORITY] = anon_sym_SORT_BY_INIT_PRIORITY,
  [anon_sym_REVERSE] = anon_sym_REVERSE,
  [anon_sym_EXCLUDE_FILE] = anon_sym_EXCLUDE_FILE,
  [anon_sym_AMP] = anon_sym_AMP,
  [anon_sym_INPUT_SECTION_FLAGS] = anon_sym_INPUT_SECTION_FLAGS,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [anon_sym_KEEP] = anon_sym_KEEP,
  [anon_sym_CREATE_OBJECT_SYMBOLS] = anon_sym_CREATE_OBJECT_SYMBOLS,
  [anon_sym_CONSTRUCTORS] = anon_sym_CONSTRUCTORS,
  [anon_sym_ASCIZ] = anon_sym_ASCIZ,
  [anon_sym_FILL] = anon_sym_FILL,
  [anon_sym_LINKER_VERSION] = anon_sym_LINKER_VERSION,
  [anon_sym_QUAD] = anon_sym_QUAD,
  [anon_sym_SQUAD] = anon_sym_SQUAD,
  [anon_sym_LONG] = anon_sym_LONG,
  [anon_sym_SHORT] = anon_sym_SHORT,
  [anon_sym_BYTE] = anon_sym_BYTE,
  [anon_sym_PLUS_EQ] = anon_sym_PLUS_EQ,
  [anon_sym_DASH_EQ] = anon_sym_DASH_EQ,
  [anon_sym_STAR_EQ] = anon_sym_STAR_EQ,
  [anon_sym_SLASH_EQ] = anon_sym_SLASH_EQ,
  [anon_sym_LT_LT_EQ] = anon_sym_LT_LT_EQ,
  [anon_sym_GT_GT_EQ] = anon_sym_GT_GT_EQ,
  [anon_sym_AMP_EQ] = anon_sym_AMP_EQ,
  [anon_sym_PIPE_EQ] = anon_sym_PIPE_EQ,
  [anon_sym_CARET_EQ] = anon_sym_CARET_EQ,
  [anon_sym_EQ] = anon_sym_EQ,
  [anon_sym_HIDDEN] = anon_sym_HIDDEN,
  [anon_sym_PROVIDE] = anon_sym_PROVIDE,
  [anon_sym_PROVIDE_HIDDEN] = anon_sym_PROVIDE_HIDDEN,
  [anon_sym_MEMORY] = anon_sym_MEMORY,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_ORIGIN] = anon_sym_ORIGIN,
  [anon_sym_o] = anon_sym_o,
  [anon_sym_org] = anon_sym_org,
  [anon_sym_LENGTH] = anon_sym_LENGTH,
  [anon_sym_l] = anon_sym_l,
  [anon_sym_len] = anon_sym_len,
  [anon_sym_BANG] = anon_sym_BANG,
  [anon_sym_STARTUP] = anon_sym_STARTUP,
  [anon_sym_HLL] = anon_sym_HLL,
  [anon_sym_SYSLIB] = anon_sym_SYSLIB,
  [anon_sym_FLOAT] = anon_sym_FLOAT,
  [anon_sym_NOFLOAT] = anon_sym_NOFLOAT,
  [anon_sym_DASH] = anon_sym_DASH,
  [anon_sym_PLUS] = anon_sym_PLUS,
  [anon_sym_TILDE] = anon_sym_TILDE,
  [anon_sym_NEXT] = anon_sym_NEXT,
  [anon_sym_ABSOLUTE] = anon_sym_ABSOLUTE,
  [anon_sym_DATA_SEGMENT_END] = anon_sym_DATA_SEGMENT_END,
  [anon_sym_BLOCK] = anon_sym_BLOCK,
  [anon_sym_LOG2CEIL] = anon_sym_LOG2CEIL,
  [anon_sym_STAR] = anon_sym_STAR,
  [anon_sym_SLASH] = anon_sym_SLASH,
  [anon_sym_PERCENT] = anon_sym_PERCENT,
  [anon_sym_LT_LT] = anon_sym_LT_LT,
  [anon_sym_GT_GT] = anon_sym_GT_GT,
  [anon_sym_EQ_EQ] = anon_sym_EQ_EQ,
  [anon_sym_BANG_EQ] = anon_sym_BANG_EQ,
  [anon_sym_LT_EQ] = anon_sym_LT_EQ,
  [anon_sym_GT_EQ] = anon_sym_GT_EQ,
  [anon_sym_LT] = anon_sym_LT,
  [anon_sym_GT] = anon_sym_GT,
  [anon_sym_CARET] = anon_sym_CARET,
  [anon_sym_PIPE] = anon_sym_PIPE,
  [anon_sym_AMP_AMP] = anon_sym_AMP_AMP,
  [anon_sym_PIPE_PIPE] = anon_sym_PIPE_PIPE,
  [anon_sym_QMARK] = anon_sym_QMARK,
  [anon_sym_DEFINED] = anon_sym_DEFINED,
  [anon_sym_CONSTANT] = anon_sym_CONSTANT,
  [anon_sym_SIZEOF_HEADERS] = anon_sym_SIZEOF_HEADERS,
  [anon_sym_ALIGNOF] = anon_sym_ALIGNOF,
  [anon_sym_SIZEOF] = anon_sym_SIZEOF,
  [anon_sym_ADDR] = anon_sym_ADDR,
  [anon_sym_LOADADDR] = anon_sym_LOADADDR,
  [anon_sym_ALIGN] = anon_sym_ALIGN,
  [anon_sym_DATA_SEGMENT_ALIGN] = anon_sym_DATA_SEGMENT_ALIGN,
  [anon_sym_DATA_SEGMENT_RELRO_END] = anon_sym_DATA_SEGMENT_RELRO_END,
  [anon_sym_MAX] = anon_sym_MAX,
  [anon_sym_MIN] = anon_sym_MIN,
  [anon_sym_SEGMENT_START] = anon_sym_SEGMENT_START,
  [anon_sym_AT] = anon_sym_AT,
  [anon_sym_SUBALIGN] = anon_sym_SUBALIGN,
  [anon_sym_ONLY_IF_RO] = anon_sym_ONLY_IF_RO,
  [anon_sym_ONLY_IF_RW] = anon_sym_ONLY_IF_RW,
  [anon_sym_SPECIAL] = anon_sym_SPECIAL,
  [anon_sym_ALIGN_WITH_INPUT] = anon_sym_ALIGN_WITH_INPUT,
  [anon_sym_OVERLAY] = anon_sym_OVERLAY,
  [anon_sym_NOLOAD] = anon_sym_NOLOAD,
  [anon_sym_DSECT] = anon_sym_DSECT,
  [anon_sym_COPY] = anon_sym_COPY,
  [anon_sym_INFO] = anon_sym_INFO,
  [anon_sym_READONLY] = anon_sym_READONLY,
  [anon_sym_TYPE] = anon_sym_TYPE,
  [anon_sym_BIND] = anon_sym_BIND,
  [anon_sym_PHDRS] = anon_sym_PHDRS,
  [anon_sym_VERSION] = anon_sym_VERSION,
  [anon_sym_global] = anon_sym_global,
  [anon_sym_local] = anon_sym_local,
  [anon_sym_extern] = anon_sym_extern,
  [sym_SYMBOLNAME] = sym_SYMBOLNAME,
  [sym_LNAME] = sym_LNAME,
  [sym_wildcard_name] = sym_wildcard_name,
  [aux_sym_INT_token1] = aux_sym_INT_token1,
  [aux_sym_INT_token2] = aux_sym_INT_token2,
  [aux_sym_INT_token3] = aux_sym_INT_token3,
  [sym_VERS_TAG] = sym_VERS_TAG,
  [sym_VERS_IDENTIFIER] = sym_VERS_IDENTIFIER,
  [sym_comment] = sym_comment,
  [sym_script_file] = sym_script_file,
  [sym_extern_name_list] = sym_extern_name_list,
  [sym_filename] = sym_filename,
  [sym_ifile_p1] = sym_ifile_p1,
  [sym_input_list] = sym_input_list,
  [sym_sections] = sym_sections,
  [sym_sec_or_group_p1] = sym_sec_or_group_p1,
  [sym_statement_anywhere] = sym_statement_anywhere,
  [sym_section_name_spec] = sym_section_name_spec,
  [sym_wildcard_maybe_exclude] = sym_wildcard_maybe_exclude,
  [sym_wildcard_maybe_reverse] = sym_wildcard_maybe_reverse,
  [sym_filename_spec] = sym_filename_spec,
  [sym_sect_flag_list] = sym_sect_flag_list,
  [sym_sect_flags] = sym_sect_flags,
  [sym_exclude_name_list] = sym_exclude_name_list,
  [sym_section_name_list] = sym_section_name_list,
  [sym_input_section_spec_no_keep] = sym_input_section_spec_no_keep,
  [sym_input_section_spec] = sym_input_section_spec,
  [sym_statement] = sym_statement,
  [sym_statement_list] = sym_statement_list,
  [sym_length] = sym_length,
  [sym_fill_exp] = sym_fill_exp,
  [sym_assign_op] = sym_assign_op,
  [sym_separator] = sym_separator,
  [sym_assignment] = sym_assignment,
  [sym_memory] = sym_memory,
  [sym_memory_spec_list] = sym_memory_spec_list,
  [sym_memory_spec] = sym_memory_spec,
  [sym_origin_spec] = sym_origin_spec,
  [sym_length_spec] = sym_length_spec,
  [sym_attributes] = sym_attributes,
  [sym_attributes_list] = sym_attributes_list,
  [sym_attributes_string] = sym_attributes_string,
  [sym_startup] = sym_startup,
  [sym_high_level_library] = sym_high_level_library,
  [sym_high_level_library_NAME_list] = sym_high_level_library_NAME_list,
  [sym_low_level_library] = sym_low_level_library,
  [sym_low_level_library_NAME_list] = sym_low_level_library_NAME_list,
  [sym_floating_point_support] = sym_floating_point_support,
  [sym_nocrossref_list] = sym_nocrossref_list,
  [sym_paren_script_name] = sym_paren_script_name,
  [sym_mustbe_exp] = sym_mustbe_exp,
  [sym_exp] = sym_exp,
  [sym_memspec_at] = sym_memspec_at,
  [sym_at] = sym_at,
  [sym_align] = sym_align,
  [sym_subalign] = sym_subalign,
  [sym_sect_constraint] = sym_sect_constraint,
  [sym_section] = sym_section,
  [sym_type] = sym_type,
  [sym_atype] = sym_atype,
  [sym_opt_exp_with_type] = sym_opt_exp_with_type,
  [sym_opt_exp_without_type] = sym_opt_exp_without_type,
  [sym_memspec] = sym_memspec,
  [sym_phdr_opt] = sym_phdr_opt,
  [sym_phdrs] = sym_phdrs,
  [sym_phdr_list] = sym_phdr_list,
  [sym_phdr] = sym_phdr,
  [sym_phdr_type] = sym_phdr_type,
  [sym_phdr_qualifiers] = sym_phdr_qualifiers,
  [sym_phdr_val] = sym_phdr_val,
  [sym_overlay_section] = sym_overlay_section,
  [sym_version] = sym_version,
  [sym_vers_nodes] = sym_vers_nodes,
  [sym_vers_node] = sym_vers_node,
  [sym_verdep] = sym_verdep,
  [sym_vers_tag] = sym_vers_tag,
  [sym_vers_defns] = sym_vers_defns,
  [sym_INT] = sym_INT,
  [aux_sym_script_file_repeat1] = aux_sym_script_file_repeat1,
  [aux_sym_extern_name_list_repeat1] = aux_sym_extern_name_list_repeat1,
  [aux_sym_input_list_repeat1] = aux_sym_input_list_repeat1,
  [aux_sym_sec_or_group_p1_repeat1] = aux_sym_sec_or_group_p1_repeat1,
  [aux_sym_sect_flag_list_repeat1] = aux_sym_sect_flag_list_repeat1,
  [aux_sym_exclude_name_list_repeat1] = aux_sym_exclude_name_list_repeat1,
  [aux_sym_section_name_list_repeat1] = aux_sym_section_name_list_repeat1,
  [aux_sym_statement_list_repeat1] = aux_sym_statement_list_repeat1,
  [aux_sym_memory_spec_list_repeat1] = aux_sym_memory_spec_list_repeat1,
  [aux_sym_attributes_list_repeat1] = aux_sym_attributes_list_repeat1,
  [aux_sym_high_level_library_NAME_list_repeat1] = aux_sym_high_level_library_NAME_list_repeat1,
  [aux_sym_low_level_library_NAME_list_repeat1] = aux_sym_low_level_library_NAME_list_repeat1,
  [aux_sym_low_level_library_NAME_list_repeat2] = aux_sym_low_level_library_NAME_list_repeat2,
  [aux_sym_phdr_list_repeat1] = aux_sym_phdr_list_repeat1,
  [aux_sym_phdr_qualifiers_repeat1] = aux_sym_phdr_qualifiers_repeat1,
  [aux_sym_overlay_section_repeat1] = aux_sym_overlay_section_repeat1,
  [aux_sym_vers_nodes_repeat1] = aux_sym_vers_nodes_repeat1,
  [aux_sym_verdep_repeat1] = aux_sym_verdep_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_NAME] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SEMI] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_TARGET] = {
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
  [anon_sym_SEARCH_DIR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_OUTPUT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_OUTPUT_FORMAT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_OUTPUT_ARCH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_FORCE_COMMON_ALLOCATION] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_FORCE_GROUP_ALLOCATION] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_INHIBIT_COMMON_ALLOCATION] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_INPUT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GROUP] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_MAP] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_INCLUDE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_NOCROSSREFS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_NOCROSSREFS_TO] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EXTERN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_INSERT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_AFTER] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BEFORE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_REGION_ALIAS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LD_FEATURE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_AS_NEEDED] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SECTIONS] = {
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
  [anon_sym_ENTRY] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ASSERT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SORT_BY_NAME] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SORT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SORT_BY_ALIGNMENT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SORT_NONE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SORT_BY_INIT_PRIORITY] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_REVERSE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EXCLUDE_FILE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_AMP] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_INPUT_SECTION_FLAGS] = {
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
  [anon_sym_KEEP] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_CREATE_OBJECT_SYMBOLS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_CONSTRUCTORS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ASCIZ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_FILL] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LINKER_VERSION] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_QUAD] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SQUAD] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LONG] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SHORT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BYTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PLUS_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_STAR_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SLASH_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT_LT_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT_GT_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_AMP_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PIPE_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_CARET_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_HIDDEN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PROVIDE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PROVIDE_HIDDEN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_MEMORY] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ORIGIN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_o] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_org] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LENGTH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_l] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_len] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BANG] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_STARTUP] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_HLL] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SYSLIB] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_FLOAT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_NOFLOAT] = {
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
  [anon_sym_TILDE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_NEXT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ABSOLUTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DATA_SEGMENT_END] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BLOCK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LOG2CEIL] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_STAR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SLASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PERCENT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT_LT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT_GT] = {
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
  [anon_sym_LT_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT_EQ] = {
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
  [anon_sym_CARET] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PIPE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_AMP_AMP] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PIPE_PIPE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_QMARK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DEFINED] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_CONSTANT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SIZEOF_HEADERS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ALIGNOF] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SIZEOF] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ADDR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LOADADDR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ALIGN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DATA_SEGMENT_ALIGN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DATA_SEGMENT_RELRO_END] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_MAX] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_MIN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SEGMENT_START] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_AT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SUBALIGN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ONLY_IF_RO] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ONLY_IF_RW] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SPECIAL] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ALIGN_WITH_INPUT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_OVERLAY] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_NOLOAD] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DSECT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COPY] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_INFO] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_READONLY] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_TYPE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BIND] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PHDRS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_VERSION] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_global] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_local] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_extern] = {
    .visible = true,
    .named = false,
  },
  [sym_SYMBOLNAME] = {
    .visible = true,
    .named = true,
  },
  [sym_LNAME] = {
    .visible = true,
    .named = true,
  },
  [sym_wildcard_name] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_INT_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_INT_token2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_INT_token3] = {
    .visible = false,
    .named = false,
  },
  [sym_VERS_TAG] = {
    .visible = true,
    .named = true,
  },
  [sym_VERS_IDENTIFIER] = {
    .visible = true,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_script_file] = {
    .visible = true,
    .named = true,
  },
  [sym_extern_name_list] = {
    .visible = true,
    .named = true,
  },
  [sym_filename] = {
    .visible = true,
    .named = true,
  },
  [sym_ifile_p1] = {
    .visible = true,
    .named = true,
  },
  [sym_input_list] = {
    .visible = true,
    .named = true,
  },
  [sym_sections] = {
    .visible = true,
    .named = true,
  },
  [sym_sec_or_group_p1] = {
    .visible = true,
    .named = true,
  },
  [sym_statement_anywhere] = {
    .visible = true,
    .named = true,
  },
  [sym_section_name_spec] = {
    .visible = true,
    .named = true,
  },
  [sym_wildcard_maybe_exclude] = {
    .visible = true,
    .named = true,
  },
  [sym_wildcard_maybe_reverse] = {
    .visible = true,
    .named = true,
  },
  [sym_filename_spec] = {
    .visible = true,
    .named = true,
  },
  [sym_sect_flag_list] = {
    .visible = true,
    .named = true,
  },
  [sym_sect_flags] = {
    .visible = true,
    .named = true,
  },
  [sym_exclude_name_list] = {
    .visible = true,
    .named = true,
  },
  [sym_section_name_list] = {
    .visible = true,
    .named = true,
  },
  [sym_input_section_spec_no_keep] = {
    .visible = true,
    .named = true,
  },
  [sym_input_section_spec] = {
    .visible = true,
    .named = true,
  },
  [sym_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_statement_list] = {
    .visible = true,
    .named = true,
  },
  [sym_length] = {
    .visible = true,
    .named = true,
  },
  [sym_fill_exp] = {
    .visible = true,
    .named = true,
  },
  [sym_assign_op] = {
    .visible = true,
    .named = true,
  },
  [sym_separator] = {
    .visible = true,
    .named = true,
  },
  [sym_assignment] = {
    .visible = true,
    .named = true,
  },
  [sym_memory] = {
    .visible = true,
    .named = true,
  },
  [sym_memory_spec_list] = {
    .visible = true,
    .named = true,
  },
  [sym_memory_spec] = {
    .visible = true,
    .named = true,
  },
  [sym_origin_spec] = {
    .visible = true,
    .named = true,
  },
  [sym_length_spec] = {
    .visible = true,
    .named = true,
  },
  [sym_attributes] = {
    .visible = true,
    .named = true,
  },
  [sym_attributes_list] = {
    .visible = true,
    .named = true,
  },
  [sym_attributes_string] = {
    .visible = true,
    .named = true,
  },
  [sym_startup] = {
    .visible = true,
    .named = true,
  },
  [sym_high_level_library] = {
    .visible = true,
    .named = true,
  },
  [sym_high_level_library_NAME_list] = {
    .visible = true,
    .named = true,
  },
  [sym_low_level_library] = {
    .visible = true,
    .named = true,
  },
  [sym_low_level_library_NAME_list] = {
    .visible = true,
    .named = true,
  },
  [sym_floating_point_support] = {
    .visible = true,
    .named = true,
  },
  [sym_nocrossref_list] = {
    .visible = true,
    .named = true,
  },
  [sym_paren_script_name] = {
    .visible = true,
    .named = true,
  },
  [sym_mustbe_exp] = {
    .visible = true,
    .named = true,
  },
  [sym_exp] = {
    .visible = true,
    .named = true,
  },
  [sym_memspec_at] = {
    .visible = true,
    .named = true,
  },
  [sym_at] = {
    .visible = true,
    .named = true,
  },
  [sym_align] = {
    .visible = true,
    .named = true,
  },
  [sym_subalign] = {
    .visible = true,
    .named = true,
  },
  [sym_sect_constraint] = {
    .visible = true,
    .named = true,
  },
  [sym_section] = {
    .visible = true,
    .named = true,
  },
  [sym_type] = {
    .visible = true,
    .named = true,
  },
  [sym_atype] = {
    .visible = true,
    .named = true,
  },
  [sym_opt_exp_with_type] = {
    .visible = true,
    .named = true,
  },
  [sym_opt_exp_without_type] = {
    .visible = true,
    .named = true,
  },
  [sym_memspec] = {
    .visible = true,
    .named = true,
  },
  [sym_phdr_opt] = {
    .visible = true,
    .named = true,
  },
  [sym_phdrs] = {
    .visible = true,
    .named = true,
  },
  [sym_phdr_list] = {
    .visible = true,
    .named = true,
  },
  [sym_phdr] = {
    .visible = true,
    .named = true,
  },
  [sym_phdr_type] = {
    .visible = true,
    .named = true,
  },
  [sym_phdr_qualifiers] = {
    .visible = true,
    .named = true,
  },
  [sym_phdr_val] = {
    .visible = true,
    .named = true,
  },
  [sym_overlay_section] = {
    .visible = true,
    .named = true,
  },
  [sym_version] = {
    .visible = true,
    .named = true,
  },
  [sym_vers_nodes] = {
    .visible = true,
    .named = true,
  },
  [sym_vers_node] = {
    .visible = true,
    .named = true,
  },
  [sym_verdep] = {
    .visible = true,
    .named = true,
  },
  [sym_vers_tag] = {
    .visible = true,
    .named = true,
  },
  [sym_vers_defns] = {
    .visible = true,
    .named = true,
  },
  [sym_INT] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_script_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_extern_name_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_input_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_sec_or_group_p1_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_sect_flag_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_exclude_name_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_section_name_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_statement_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_memory_spec_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_attributes_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_high_level_library_NAME_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_low_level_library_NAME_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_low_level_library_NAME_list_repeat2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_phdr_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_phdr_qualifiers_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_overlay_section_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_vers_nodes_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_verdep_repeat1] = {
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
  [69] = 64,
  [70] = 70,
  [71] = 71,
  [72] = 62,
  [73] = 73,
  [74] = 74,
  [75] = 75,
  [76] = 76,
  [77] = 73,
  [78] = 76,
  [79] = 79,
  [80] = 80,
  [81] = 81,
  [82] = 75,
  [83] = 66,
  [84] = 71,
  [85] = 71,
  [86] = 86,
  [87] = 87,
  [88] = 87,
  [89] = 63,
  [90] = 86,
  [91] = 91,
  [92] = 68,
  [93] = 68,
  [94] = 75,
  [95] = 62,
  [96] = 87,
  [97] = 97,
  [98] = 64,
  [99] = 63,
  [100] = 86,
  [101] = 73,
  [102] = 66,
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
  [116] = 107,
  [117] = 117,
  [118] = 118,
  [119] = 108,
  [120] = 120,
  [121] = 115,
  [122] = 122,
  [123] = 106,
  [124] = 109,
  [125] = 125,
  [126] = 113,
  [127] = 19,
  [128] = 110,
  [129] = 129,
  [130] = 130,
  [131] = 131,
  [132] = 111,
  [133] = 112,
  [134] = 134,
  [135] = 114,
  [136] = 136,
  [137] = 16,
  [138] = 111,
  [139] = 112,
  [140] = 113,
  [141] = 114,
  [142] = 115,
  [143] = 108,
  [144] = 107,
  [145] = 110,
  [146] = 109,
  [147] = 106,
  [148] = 105,
  [149] = 105,
  [150] = 150,
  [151] = 151,
  [152] = 152,
  [153] = 152,
  [154] = 152,
  [155] = 155,
  [156] = 156,
  [157] = 157,
  [158] = 158,
  [159] = 159,
  [160] = 160,
  [161] = 161,
  [162] = 158,
  [163] = 163,
  [164] = 164,
  [165] = 165,
  [166] = 165,
  [167] = 167,
  [168] = 168,
  [169] = 161,
  [170] = 155,
  [171] = 158,
  [172] = 168,
  [173] = 165,
  [174] = 174,
  [175] = 161,
  [176] = 167,
  [177] = 177,
  [178] = 167,
  [179] = 168,
  [180] = 163,
  [181] = 181,
  [182] = 182,
  [183] = 183,
  [184] = 155,
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
  [217] = 216,
  [218] = 206,
  [219] = 214,
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
  [234] = 232,
  [235] = 235,
  [236] = 236,
  [237] = 237,
  [238] = 236,
  [239] = 239,
  [240] = 239,
  [241] = 237,
  [242] = 242,
  [243] = 243,
  [244] = 244,
  [245] = 245,
  [246] = 246,
  [247] = 247,
  [248] = 248,
  [249] = 248,
  [250] = 250,
  [251] = 251,
  [252] = 252,
  [253] = 253,
  [254] = 242,
  [255] = 255,
  [256] = 256,
  [257] = 257,
  [258] = 258,
  [259] = 259,
  [260] = 19,
  [261] = 18,
  [262] = 25,
  [263] = 263,
  [264] = 264,
  [265] = 265,
  [266] = 266,
  [267] = 267,
  [268] = 36,
  [269] = 269,
  [270] = 269,
  [271] = 271,
  [272] = 272,
  [273] = 273,
  [274] = 274,
  [275] = 275,
  [276] = 276,
  [277] = 276,
  [278] = 278,
  [279] = 279,
  [280] = 280,
  [281] = 263,
  [282] = 282,
  [283] = 283,
  [284] = 16,
  [285] = 264,
  [286] = 286,
  [287] = 287,
  [288] = 265,
  [289] = 282,
  [290] = 279,
  [291] = 275,
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
  [305] = 300,
  [306] = 306,
  [307] = 307,
  [308] = 308,
  [309] = 309,
  [310] = 310,
  [311] = 311,
  [312] = 312,
  [313] = 313,
  [314] = 313,
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
  [341] = 220,
  [342] = 342,
  [343] = 343,
  [344] = 16,
  [345] = 345,
  [346] = 346,
  [347] = 347,
  [348] = 348,
  [349] = 349,
  [350] = 350,
  [351] = 351,
  [352] = 352,
  [353] = 353,
  [354] = 346,
  [355] = 355,
  [356] = 228,
  [357] = 357,
  [358] = 358,
  [359] = 359,
  [360] = 360,
  [361] = 361,
  [362] = 362,
  [363] = 363,
  [364] = 364,
  [365] = 365,
  [366] = 366,
  [367] = 367,
  [368] = 368,
  [369] = 369,
  [370] = 370,
  [371] = 360,
  [372] = 372,
  [373] = 373,
  [374] = 374,
  [375] = 375,
  [376] = 376,
  [377] = 377,
  [378] = 378,
  [379] = 379,
  [380] = 380,
  [381] = 381,
  [382] = 382,
  [383] = 383,
  [384] = 384,
  [385] = 385,
  [386] = 386,
  [387] = 387,
  [388] = 388,
  [389] = 389,
  [390] = 390,
  [391] = 391,
  [392] = 392,
  [393] = 393,
  [394] = 394,
  [395] = 395,
  [396] = 396,
  [397] = 397,
  [398] = 398,
  [399] = 399,
  [400] = 400,
  [401] = 401,
  [402] = 402,
  [403] = 403,
  [404] = 404,
  [405] = 405,
  [406] = 406,
  [407] = 407,
  [408] = 408,
  [409] = 409,
  [410] = 410,
  [411] = 411,
  [412] = 412,
  [413] = 413,
  [414] = 414,
  [415] = 415,
  [416] = 416,
  [417] = 417,
  [418] = 418,
  [419] = 419,
  [420] = 420,
  [421] = 421,
  [422] = 422,
  [423] = 423,
  [424] = 424,
  [425] = 425,
  [426] = 426,
  [427] = 427,
  [428] = 428,
  [429] = 429,
  [430] = 430,
  [431] = 423,
  [432] = 432,
  [433] = 433,
  [434] = 434,
  [435] = 435,
  [436] = 436,
  [437] = 437,
  [438] = 438,
  [439] = 422,
  [440] = 440,
  [441] = 441,
  [442] = 440,
  [443] = 443,
  [444] = 444,
  [445] = 445,
  [446] = 235,
  [447] = 447,
  [448] = 448,
  [449] = 449,
  [450] = 450,
  [451] = 451,
  [452] = 452,
  [453] = 453,
  [454] = 454,
  [455] = 455,
  [456] = 422,
  [457] = 457,
  [458] = 458,
  [459] = 459,
  [460] = 460,
  [461] = 461,
  [462] = 462,
  [463] = 463,
  [464] = 265,
  [465] = 264,
  [466] = 466,
  [467] = 467,
  [468] = 468,
  [469] = 469,
  [470] = 275,
  [471] = 471,
  [472] = 472,
  [473] = 473,
  [474] = 466,
  [475] = 475,
  [476] = 476,
  [477] = 477,
  [478] = 478,
  [479] = 479,
  [480] = 480,
  [481] = 481,
  [482] = 482,
  [483] = 483,
  [484] = 484,
  [485] = 485,
  [486] = 486,
  [487] = 487,
  [488] = 488,
  [489] = 489,
  [490] = 490,
  [491] = 279,
  [492] = 492,
  [493] = 493,
  [494] = 494,
  [495] = 495,
  [496] = 496,
  [497] = 497,
  [498] = 466,
  [499] = 499,
  [500] = 500,
  [501] = 501,
  [502] = 502,
  [503] = 503,
  [504] = 504,
  [505] = 505,
  [506] = 506,
  [507] = 507,
  [508] = 508,
  [509] = 509,
  [510] = 510,
  [511] = 511,
  [512] = 512,
  [513] = 513,
  [514] = 514,
  [515] = 515,
  [516] = 516,
  [517] = 517,
  [518] = 518,
  [519] = 519,
  [520] = 520,
  [521] = 521,
  [522] = 522,
  [523] = 523,
  [524] = 524,
  [525] = 525,
  [526] = 526,
  [527] = 527,
  [528] = 528,
  [529] = 529,
  [530] = 530,
  [531] = 531,
  [532] = 532,
  [533] = 533,
  [534] = 534,
  [535] = 535,
  [536] = 536,
  [537] = 537,
  [538] = 538,
  [539] = 539,
  [540] = 540,
  [541] = 541,
  [542] = 542,
  [543] = 543,
  [544] = 544,
  [545] = 545,
  [546] = 546,
  [547] = 547,
  [548] = 548,
  [549] = 549,
  [550] = 550,
  [551] = 551,
  [552] = 552,
  [553] = 553,
  [554] = 554,
  [555] = 555,
  [556] = 556,
  [557] = 557,
  [558] = 558,
  [559] = 559,
  [560] = 560,
  [561] = 561,
  [562] = 562,
  [563] = 563,
  [564] = 564,
  [565] = 565,
  [566] = 566,
  [567] = 567,
  [568] = 568,
  [569] = 569,
  [570] = 570,
  [571] = 571,
  [572] = 572,
  [573] = 573,
  [574] = 574,
  [575] = 575,
  [576] = 576,
  [577] = 577,
  [578] = 578,
  [579] = 579,
  [580] = 580,
  [581] = 581,
  [582] = 582,
  [583] = 583,
  [584] = 584,
  [585] = 585,
  [586] = 586,
  [587] = 587,
  [588] = 588,
  [589] = 589,
  [590] = 590,
  [591] = 591,
  [592] = 592,
  [593] = 130,
  [594] = 594,
  [595] = 595,
  [596] = 596,
  [597] = 597,
  [598] = 120,
  [599] = 599,
  [600] = 600,
  [601] = 601,
  [602] = 602,
  [603] = 603,
  [604] = 118,
  [605] = 605,
  [606] = 606,
  [607] = 136,
  [608] = 608,
  [609] = 609,
  [610] = 610,
  [611] = 611,
  [612] = 612,
  [613] = 613,
  [614] = 614,
  [615] = 615,
  [616] = 616,
  [617] = 617,
  [618] = 618,
  [619] = 619,
  [620] = 620,
  [621] = 621,
  [622] = 622,
  [623] = 623,
  [624] = 624,
  [625] = 625,
  [626] = 626,
  [627] = 627,
  [628] = 628,
  [629] = 629,
  [630] = 617,
  [631] = 631,
  [632] = 632,
  [633] = 633,
  [634] = 503,
  [635] = 635,
  [636] = 580,
  [637] = 637,
  [638] = 584,
  [639] = 639,
  [640] = 640,
  [641] = 605,
  [642] = 592,
  [643] = 578,
  [644] = 644,
  [645] = 558,
  [646] = 548,
  [647] = 647,
  [648] = 535,
  [649] = 534,
  [650] = 518,
  [651] = 520,
  [652] = 514,
  [653] = 546,
  [654] = 654,
  [655] = 655,
  [656] = 656,
  [657] = 503,
  [658] = 658,
  [659] = 580,
  [660] = 660,
  [661] = 661,
  [662] = 578,
  [663] = 663,
  [664] = 548,
  [665] = 518,
  [666] = 656,
  [667] = 667,
  [668] = 509,
  [669] = 669,
  [670] = 540,
  [671] = 671,
  [672] = 538,
  [673] = 673,
  [674] = 674,
  [675] = 632,
  [676] = 676,
  [677] = 677,
  [678] = 678,
  [679] = 547,
  [680] = 680,
  [681] = 681,
  [682] = 682,
  [683] = 683,
  [684] = 530,
  [685] = 685,
  [686] = 509,
  [687] = 687,
  [688] = 540,
  [689] = 689,
  [690] = 690,
  [691] = 632,
  [692] = 692,
  [693] = 547,
  [694] = 694,
  [695] = 614,
  [696] = 613,
  [697] = 612,
  [698] = 694,
  [699] = 699,
  [700] = 700,
  [701] = 582,
  [702] = 644,
  [703] = 703,
  [704] = 597,
  [705] = 596,
  [706] = 595,
  [707] = 586,
  [708] = 708,
  [709] = 709,
  [710] = 614,
  [711] = 613,
  [712] = 612,
  [713] = 713,
  [714] = 714,
  [715] = 582,
  [716] = 716,
  [717] = 717,
  [718] = 718,
  [719] = 719,
  [720] = 539,
  [721] = 681,
  [722] = 519,
  [723] = 507,
  [724] = 724,
  [725] = 725,
  [726] = 539,
  [727] = 681,
  [728] = 692,
  [729] = 616,
  [730] = 611,
  [731] = 610,
  [732] = 616,
  [733] = 611,
  [734] = 610,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(99);
      if (lookahead == '!') ADVANCE(167);
      if (lookahead == '"') ADVANCE(14);
      if (lookahead == '$') ADVANCE(524);
      if (lookahead == '%') ADVANCE(190);
      if (lookahead == '&') ADVANCE(131);
      if (lookahead == '(') ADVANCE(103);
      if (lookahead == ')') ADVANCE(104);
      if (lookahead == '*') ADVANCE(186);
      if (lookahead == '+') ADVANCE(171);
      if (lookahead == ',') ADVANCE(100);
      if (lookahead == '-') ADVANCE(169);
      if (lookahead == '/') ADVANCE(188);
      if (lookahead == '0') ADVANCE(772);
      if (lookahead == ':') ADVANCE(157);
      if (lookahead == ';') ADVANCE(102);
      if (lookahead == '<') ADVANCE(199);
      if (lookahead == '=') ADVANCE(154);
      if (lookahead == '>') ADVANCE(202);
      if (lookahead == '?') ADVANCE(210);
      if (lookahead == 'A') ADVANCE(290);
      if (lookahead == 'B') ADVANCE(363);
      if (lookahead == 'C') ADVANCE(416);
      if (lookahead == 'D') ADVANCE(273);
      if (lookahead == 'I') ADVANCE(393);
      if (lookahead == 'L') ADVANCE(331);
      if (lookahead == 'M') ADVANCE(274);
      if (lookahead == 'N') ADVANCE(327);
      if (lookahead == 'O') ADVANCE(447);
      if (lookahead == 'R') ADVANCE(314);
      if (lookahead == 'S') ADVANCE(315);
      if (lookahead == 'T') ADVANCE(495);
      if (lookahead == '[') ADVANCE(132);
      if (lookahead == ']') ADVANCE(134);
      if (lookahead == '^') ADVANCE(205);
      if (lookahead == 'g') ADVANCE(515);
      if (lookahead == 'l') ADVANCE(163);
      if (lookahead == '{') ADVANCE(105);
      if (lookahead == '|') ADVANCE(206);
      if (lookahead == '}') ADVANCE(106);
      if (lookahead == '~') ADVANCE(173);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(0)
      if (lookahead == 'E' ||
          lookahead == 'F' ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(522);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(773);
      if (lookahead == '.' ||
          ('G' <= lookahead && lookahead <= '_') ||
          ('h' <= lookahead && lookahead <= 'z')) ADVANCE(525);
      END_STATE();
    case 1:
      if (lookahead == '!') ADVANCE(167);
      if (lookahead == '"') ADVANCE(14);
      if (lookahead == '(') ADVANCE(103);
      if (lookahead == ')') ADVANCE(104);
      if (lookahead == ',') ADVANCE(100);
      if (lookahead == '-') ADVANCE(93);
      if (lookahead == '/') ADVANCE(267);
      if (lookahead == ':') ADVANCE(157);
      if (lookahead == ';') ADVANCE(102);
      if (lookahead == '=') ADVANCE(156);
      if (lookahead == '{') ADVANCE(105);
      if (lookahead == '}') ADVANCE(106);
      if (lookahead == '~') ADVANCE(526);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(1)
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(525);
      END_STATE();
    case 2:
      if (lookahead == '!') ADVANCE(167);
      if (lookahead == '"') ADVANCE(15);
      if (lookahead == '$') ADVANCE(674);
      if (lookahead == '&') ADVANCE(44);
      if (lookahead == '(') ADVANCE(103);
      if (lookahead == '*') ADVANCE(37);
      if (lookahead == '+') ADVANCE(171);
      if (lookahead == '-') ADVANCE(169);
      if (lookahead == '/') ADVANCE(20);
      if (lookahead == '0') ADVANCE(772);
      if (lookahead == ':') ADVANCE(157);
      if (lookahead == '<') ADVANCE(36);
      if (lookahead == '=') ADVANCE(153);
      if (lookahead == '>') ADVANCE(46);
      if (lookahead == 'A') ADVANCE(542);
      if (lookahead == 'B') ADVANCE(589);
      if (lookahead == 'C') ADVANCE(628);
      if (lookahead == 'D') ADVANCE(530);
      if (lookahead == 'L') ADVANCE(564);
      if (lookahead == 'M') ADVANCE(531);
      if (lookahead == 'N') ADVANCE(562);
      if (lookahead == 'O') ADVANCE(641);
      if (lookahead == 'S') ADVANCE(557);
      if (lookahead == '^') ADVANCE(40);
      if (lookahead == '|') ADVANCE(41);
      if (lookahead == '~') ADVANCE(172);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(2)
      if (lookahead == 'E' ||
          lookahead == 'F' ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(672);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(773);
      if (lookahead == '.' ||
          ('G' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(675);
      END_STATE();
    case 3:
      if (lookahead == '!') ADVANCE(167);
      if (lookahead == '"') ADVANCE(15);
      if (lookahead == '$') ADVANCE(674);
      if (lookahead == '(') ADVANCE(103);
      if (lookahead == ')') ADVANCE(104);
      if (lookahead == '+') ADVANCE(170);
      if (lookahead == '-') ADVANCE(168);
      if (lookahead == '/') ADVANCE(21);
      if (lookahead == '0') ADVANCE(772);
      if (lookahead == 'A') ADVANCE(542);
      if (lookahead == 'B') ADVANCE(597);
      if (lookahead == 'C') ADVANCE(626);
      if (lookahead == 'D') ADVANCE(529);
      if (lookahead == 'I') ADVANCE(615);
      if (lookahead == 'L') ADVANCE(564);
      if (lookahead == 'M') ADVANCE(531);
      if (lookahead == 'N') ADVANCE(561);
      if (lookahead == 'O') ADVANCE(640);
      if (lookahead == 'R') ADVANCE(575);
      if (lookahead == 'S') ADVANCE(557);
      if (lookahead == 'T') ADVANCE(663);
      if (lookahead == '~') ADVANCE(172);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(3)
      if (lookahead == 'E' ||
          lookahead == 'F' ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(672);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(773);
      if (lookahead == '.' ||
          ('G' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(675);
      END_STATE();
    case 4:
      if (lookahead == '!') ADVANCE(167);
      if (lookahead == '"') ADVANCE(15);
      if (lookahead == '$') ADVANCE(674);
      if (lookahead == '(') ADVANCE(103);
      if (lookahead == '+') ADVANCE(170);
      if (lookahead == '-') ADVANCE(168);
      if (lookahead == '/') ADVANCE(21);
      if (lookahead == '0') ADVANCE(772);
      if (lookahead == ':') ADVANCE(157);
      if (lookahead == 'A') ADVANCE(542);
      if (lookahead == 'B') ADVANCE(597);
      if (lookahead == 'C') ADVANCE(628);
      if (lookahead == 'D') ADVANCE(530);
      if (lookahead == 'L') ADVANCE(564);
      if (lookahead == 'M') ADVANCE(531);
      if (lookahead == 'N') ADVANCE(562);
      if (lookahead == 'O') ADVANCE(641);
      if (lookahead == 'S') ADVANCE(557);
      if (lookahead == '~') ADVANCE(172);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(4)
      if (lookahead == 'E' ||
          lookahead == 'F' ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(672);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(773);
      if (lookahead == '.' ||
          ('G' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(675);
      END_STATE();
    case 5:
      if (lookahead == '!') ADVANCE(45);
      if (lookahead == '"') ADVANCE(14);
      if (lookahead == '%') ADVANCE(190);
      if (lookahead == '&') ADVANCE(131);
      if (lookahead == '*') ADVANCE(185);
      if (lookahead == '+') ADVANCE(170);
      if (lookahead == ',') ADVANCE(100);
      if (lookahead == '-') ADVANCE(168);
      if (lookahead == '/') ADVANCE(189);
      if (lookahead == ';') ADVANCE(102);
      if (lookahead == '<') ADVANCE(200);
      if (lookahead == '=') ADVANCE(39);
      if (lookahead == '>') ADVANCE(203);
      if (lookahead == '?') ADVANCE(210);
      if (lookahead == '^') ADVANCE(204);
      if (lookahead == '|') ADVANCE(207);
      if (lookahead == '}') ADVANCE(106);
      if (lookahead == '~') ADVANCE(526);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(5)
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(525);
      END_STATE();
    case 6:
      if (lookahead == '!') ADVANCE(45);
      if (lookahead == '"') ADVANCE(14);
      if (lookahead == '%') ADVANCE(190);
      if (lookahead == '&') ADVANCE(131);
      if (lookahead == '*') ADVANCE(185);
      if (lookahead == '+') ADVANCE(170);
      if (lookahead == ',') ADVANCE(100);
      if (lookahead == '-') ADVANCE(168);
      if (lookahead == '/') ADVANCE(189);
      if (lookahead == '<') ADVANCE(200);
      if (lookahead == '=') ADVANCE(39);
      if (lookahead == '>') ADVANCE(203);
      if (lookahead == '?') ADVANCE(210);
      if (lookahead == 'A') ADVANCE(452);
      if (lookahead == 'O') ADVANCE(490);
      if (lookahead == '^') ADVANCE(204);
      if (lookahead == '|') ADVANCE(207);
      if (lookahead == '}') ADVANCE(106);
      if (lookahead == '~') ADVANCE(526);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(6)
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(525);
      END_STATE();
    case 7:
      if (lookahead == '!') ADVANCE(45);
      if (lookahead == '%') ADVANCE(190);
      if (lookahead == '&') ADVANCE(131);
      if (lookahead == '(') ADVANCE(103);
      if (lookahead == ')') ADVANCE(104);
      if (lookahead == '*') ADVANCE(185);
      if (lookahead == '+') ADVANCE(170);
      if (lookahead == ',') ADVANCE(100);
      if (lookahead == '-') ADVANCE(168);
      if (lookahead == '/') ADVANCE(187);
      if (lookahead == ':') ADVANCE(157);
      if (lookahead == ';') ADVANCE(102);
      if (lookahead == '<') ADVANCE(200);
      if (lookahead == '=') ADVANCE(38);
      if (lookahead == '>') ADVANCE(203);
      if (lookahead == '?') ADVANCE(210);
      if (lookahead == 'B') ADVANCE(68);
      if (lookahead == 'C') ADVANCE(74);
      if (lookahead == 'D') ADVANCE(85);
      if (lookahead == 'I') ADVANCE(71);
      if (lookahead == 'L') ADVANCE(60);
      if (lookahead == 'N') ADVANCE(78);
      if (lookahead == 'O') ADVANCE(88);
      if (lookahead == 'R') ADVANCE(58);
      if (lookahead == 'T') ADVANCE(92);
      if (lookahead == '^') ADVANCE(204);
      if (lookahead == 'l') ADVANCE(164);
      if (lookahead == '|') ADVANCE(207);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(7)
      END_STATE();
    case 8:
      if (lookahead == '"') ADVANCE(14);
      if (lookahead == '&') ADVANCE(44);
      if (lookahead == '*') ADVANCE(680);
      if (lookahead == '+') ADVANCE(681);
      if (lookahead == '-') ADVANCE(682);
      if (lookahead == '/') ADVANCE(268);
      if (lookahead == ';') ADVANCE(102);
      if (lookahead == '<') ADVANCE(36);
      if (lookahead == '=') ADVANCE(155);
      if (lookahead == '>') ADVANCE(46);
      if (lookahead == 'A') ADVANCE(458);
      if (lookahead == 'C') ADVANCE(419);
      if (lookahead == 'E') ADVANCE(494);
      if (lookahead == 'R') ADVANCE(321);
      if (lookahead == 'S') ADVANCE(420);
      if (lookahead == '[') ADVANCE(133);
      if (lookahead == '^') ADVANCE(683);
      if (lookahead == '|') ADVANCE(41);
      if (lookahead == '}') ADVANCE(106);
      if (lookahead == '~') ADVANCE(521);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(8)
      if (lookahead == '!' ||
          lookahead == ',' ||
          ('0' <= lookahead && lookahead <= '?') ||
          lookahead == ']') ADVANCE(767);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('B' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(520);
      END_STATE();
    case 9:
      if (lookahead == '"') ADVANCE(14);
      if (lookahead == ')') ADVANCE(104);
      if (lookahead == ',') ADVANCE(100);
      if (lookahead == '/') ADVANCE(267);
      if (lookahead == ':') ADVANCE(157);
      if (lookahead == '=') ADVANCE(156);
      if (lookahead == '>') ADVANCE(201);
      if (lookahead == 'A') ADVANCE(452);
      if (lookahead == 'O') ADVANCE(490);
      if (lookahead == '}') ADVANCE(106);
      if (lookahead == '~') ADVANCE(526);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(9)
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(525);
      END_STATE();
    case 10:
      if (lookahead == '"') ADVANCE(14);
      if (lookahead == '/') ADVANCE(267);
      if (lookahead == '=') ADVANCE(96);
      if (lookahead == 'A') ADVANCE(387);
      if (lookahead == '{') ADVANCE(105);
      if (lookahead == '~') ADVANCE(526);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(10)
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(525);
      END_STATE();
    case 11:
      if (lookahead == '"') ADVANCE(14);
      if (lookahead == '/') ADVANCE(267);
      if (lookahead == '=') ADVANCE(96);
      if (lookahead == 'O') ADVANCE(448);
      if (lookahead == '~') ADVANCE(526);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(11)
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(525);
      END_STATE();
    case 12:
      if (lookahead == '"') ADVANCE(14);
      if (lookahead == '/') ADVANCE(269);
      if (lookahead == ';') ADVANCE(102);
      if (lookahead == '=') ADVANCE(766);
      if (lookahead == 'A') ADVANCE(458);
      if (lookahead == 'C') ADVANCE(419);
      if (lookahead == 'E') ADVANCE(494);
      if (lookahead == 'R') ADVANCE(321);
      if (lookahead == 'S') ADVANCE(420);
      if (lookahead == '[') ADVANCE(133);
      if (lookahead == '}') ADVANCE(106);
      if (lookahead == '~') ADVANCE(521);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(12)
      if (lookahead == '!' ||
          ('*' <= lookahead && lookahead <= '-') ||
          ('0' <= lookahead && lookahead <= ':') ||
          lookahead == '?' ||
          lookahead == ']' ||
          lookahead == '^') ADVANCE(767);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('B' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(520);
      END_STATE();
    case 13:
      if (lookahead == '"') ADVANCE(14);
      if (lookahead == '/') ADVANCE(269);
      if (lookahead == '=') ADVANCE(766);
      if (lookahead == 'E') ADVANCE(494);
      if (lookahead == 'R') ADVANCE(321);
      if (lookahead == 'S') ADVANCE(420);
      if (lookahead == '[') ADVANCE(133);
      if (lookahead == '~') ADVANCE(521);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(13)
      if (lookahead == '!' ||
          ('*' <= lookahead && lookahead <= '-') ||
          ('0' <= lookahead && lookahead <= ':') ||
          lookahead == '?' ||
          lookahead == ']' ||
          lookahead == '^') ADVANCE(767);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(520);
      END_STATE();
    case 14:
      if (lookahead == '"') ADVANCE(266);
      if (lookahead != 0) ADVANCE(14);
      END_STATE();
    case 15:
      if (lookahead == '"') ADVANCE(527);
      if (lookahead != 0) ADVANCE(15);
      END_STATE();
    case 16:
      if (lookahead == '"') ADVANCE(15);
      if (lookahead == '/') ADVANCE(21);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(16)
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(675);
      END_STATE();
    case 17:
      if (lookahead == ')') ADVANCE(104);
      if (lookahead == ',') ADVANCE(101);
      if (lookahead == '/') ADVANCE(677);
      if (lookahead == 'E') ADVANCE(754);
      if (lookahead == 'R') ADVANCE(694);
      if (lookahead == 'S') ADVANCE(721);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(17)
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 18:
      if (lookahead == ')') ADVANCE(104);
      if (lookahead == '/') ADVANCE(677);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(18)
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 19:
      if (lookahead == '*') ADVANCE(22);
      END_STATE();
    case 20:
      if (lookahead == '*') ADVANCE(22);
      if (lookahead == '=') ADVANCE(144);
      if (lookahead == 'D') ADVANCE(65);
      END_STATE();
    case 21:
      if (lookahead == '*') ADVANCE(22);
      if (lookahead == 'D') ADVANCE(65);
      END_STATE();
    case 22:
      if (lookahead == '*') ADVANCE(24);
      if (lookahead != 0) ADVANCE(22);
      END_STATE();
    case 23:
      if (lookahead == ',') ADVANCE(101);
      if (lookahead == '/') ADVANCE(677);
      if (lookahead == 'E') ADVANCE(754);
      if (lookahead == 'R') ADVANCE(694);
      if (lookahead == 'S') ADVANCE(721);
      if (lookahead == ']') ADVANCE(135);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(23)
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 24:
      if (lookahead == '/') ADVANCE(791);
      if (lookahead != 0) ADVANCE(22);
      END_STATE();
    case 25:
      if (lookahead == '/') ADVANCE(527);
      END_STATE();
    case 26:
      if (lookahead == '/') ADVANCE(677);
      if (lookahead == 'C') ADVANCE(724);
      if (lookahead == 'E') ADVANCE(754);
      if (lookahead == 'R') ADVANCE(694);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(26)
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 27:
      if (lookahead == '/') ADVANCE(677);
      if (lookahead == 'E') ADVANCE(754);
      if (lookahead == 'R') ADVANCE(694);
      if (lookahead == 'S') ADVANCE(721);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(27)
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 28:
      if (lookahead == '/') ADVANCE(677);
      if (lookahead == 'E') ADVANCE(754);
      if (lookahead == 'R') ADVANCE(694);
      if (lookahead == 'S') ADVANCE(726);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(28)
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 29:
      if (lookahead == '/') ADVANCE(677);
      if (lookahead == 'E') ADVANCE(754);
      if (lookahead == 'R') ADVANCE(694);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(29)
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 30:
      if (lookahead == '/') ADVANCE(677);
      if (lookahead == 'E') ADVANCE(754);
      if (lookahead == 'S') ADVANCE(727);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(30)
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 31:
      if (lookahead == '/') ADVANCE(677);
      if (lookahead == 'E') ADVANCE(754);
      if (lookahead == 'S') ADVANCE(728);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(31)
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 32:
      if (lookahead == '/') ADVANCE(677);
      if (lookahead == 'E') ADVANCE(754);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(32)
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 33:
      if (lookahead == '/') ADVANCE(19);
      if (lookahead == ';') ADVANCE(102);
      if (lookahead == '{') ADVANCE(105);
      if (lookahead == '}') ADVANCE(106);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(33)
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(775);
      END_STATE();
    case 34:
      if (lookahead == '/') ADVANCE(19);
      if (lookahead == 'e') ADVANCE(789);
      if (lookahead == 'g') ADVANCE(783);
      if (lookahead == 'l') ADVANCE(785);
      if (lookahead == '}') ADVANCE(106);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(34)
      if (lookahead == '!' ||
          lookahead == '$' ||
          lookahead == '*' ||
          lookahead == '-' ||
          lookahead == '.' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(790);
      END_STATE();
    case 35:
      if (lookahead == ':') ADVANCE(790);
      END_STATE();
    case 36:
      if (lookahead == '<') ADVANCE(42);
      END_STATE();
    case 37:
      if (lookahead == '=') ADVANCE(142);
      END_STATE();
    case 38:
      if (lookahead == '=') ADVANCE(195);
      END_STATE();
    case 39:
      if (lookahead == '=') ADVANCE(195);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(526);
      END_STATE();
    case 40:
      if (lookahead == '=') ADVANCE(151);
      END_STATE();
    case 41:
      if (lookahead == '=') ADVANCE(150);
      END_STATE();
    case 42:
      if (lookahead == '=') ADVANCE(147);
      END_STATE();
    case 43:
      if (lookahead == '=') ADVANCE(148);
      END_STATE();
    case 44:
      if (lookahead == '=') ADVANCE(149);
      END_STATE();
    case 45:
      if (lookahead == '=') ADVANCE(196);
      END_STATE();
    case 46:
      if (lookahead == '>') ADVANCE(43);
      END_STATE();
    case 47:
      if (lookahead == 'A') ADVANCE(82);
      END_STATE();
    case 48:
      if (lookahead == 'A') ADVANCE(56);
      END_STATE();
    case 49:
      if (lookahead == 'A') ADVANCE(55);
      END_STATE();
    case 50:
      if (lookahead == 'A') ADVANCE(90);
      END_STATE();
    case 51:
      if (lookahead == 'C') ADVANCE(47);
      END_STATE();
    case 52:
      if (lookahead == 'C') ADVANCE(66);
      END_STATE();
    case 53:
      if (lookahead == 'C') ADVANCE(86);
      END_STATE();
    case 54:
      if (lookahead == 'D') ADVANCE(25);
      END_STATE();
    case 55:
      if (lookahead == 'D') ADVANCE(241);
      END_STATE();
    case 56:
      if (lookahead == 'D') ADVANCE(77);
      END_STATE();
    case 57:
      if (lookahead == 'E') ADVANCE(256);
      END_STATE();
    case 58:
      if (lookahead == 'E') ADVANCE(48);
      END_STATE();
    case 59:
      if (lookahead == 'E') ADVANCE(83);
      END_STATE();
    case 60:
      if (lookahead == 'E') ADVANCE(72);
      END_STATE();
    case 61:
      if (lookahead == 'E') ADVANCE(53);
      END_STATE();
    case 62:
      if (lookahead == 'F') ADVANCE(75);
      END_STATE();
    case 63:
      if (lookahead == 'G') ADVANCE(87);
      END_STATE();
    case 64:
      if (lookahead == 'H') ADVANCE(160);
      END_STATE();
    case 65:
      if (lookahead == 'I') ADVANCE(84);
      END_STATE();
    case 66:
      if (lookahead == 'K') ADVANCE(180);
      END_STATE();
    case 67:
      if (lookahead == 'L') ADVANCE(50);
      END_STATE();
    case 68:
      if (lookahead == 'L') ADVANCE(76);
      END_STATE();
    case 69:
      if (lookahead == 'L') ADVANCE(91);
      END_STATE();
    case 70:
      if (lookahead == 'L') ADVANCE(79);
      END_STATE();
    case 71:
      if (lookahead == 'N') ADVANCE(62);
      END_STATE();
    case 72:
      if (lookahead == 'N') ADVANCE(63);
      END_STATE();
    case 73:
      if (lookahead == 'N') ADVANCE(69);
      END_STATE();
    case 74:
      if (lookahead == 'O') ADVANCE(80);
      END_STATE();
    case 75:
      if (lookahead == 'O') ADVANCE(250);
      END_STATE();
    case 76:
      if (lookahead == 'O') ADVANCE(52);
      END_STATE();
    case 77:
      if (lookahead == 'O') ADVANCE(73);
      END_STATE();
    case 78:
      if (lookahead == 'O') ADVANCE(70);
      END_STATE();
    case 79:
      if (lookahead == 'O') ADVANCE(49);
      END_STATE();
    case 80:
      if (lookahead == 'P') ADVANCE(89);
      END_STATE();
    case 81:
      if (lookahead == 'P') ADVANCE(57);
      END_STATE();
    case 82:
      if (lookahead == 'R') ADVANCE(54);
      END_STATE();
    case 83:
      if (lookahead == 'R') ADVANCE(67);
      END_STATE();
    case 84:
      if (lookahead == 'S') ADVANCE(51);
      END_STATE();
    case 85:
      if (lookahead == 'S') ADVANCE(61);
      END_STATE();
    case 86:
      if (lookahead == 'T') ADVANCE(244);
      END_STATE();
    case 87:
      if (lookahead == 'T') ADVANCE(64);
      END_STATE();
    case 88:
      if (lookahead == 'V') ADVANCE(59);
      END_STATE();
    case 89:
      if (lookahead == 'Y') ADVANCE(247);
      END_STATE();
    case 90:
      if (lookahead == 'Y') ADVANCE(238);
      END_STATE();
    case 91:
      if (lookahead == 'Y') ADVANCE(253);
      END_STATE();
    case 92:
      if (lookahead == 'Y') ADVANCE(81);
      END_STATE();
    case 93:
      if (lookahead == 'l') ADVANCE(97);
      END_STATE();
    case 94:
      if (lookahead == 'n') ADVANCE(165);
      END_STATE();
    case 95:
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(769);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(768);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(95);
      END_STATE();
    case 96:
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(526);
      END_STATE();
    case 97:
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('A' <= lookahead && lookahead <= ']') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(676);
      END_STATE();
    case 98:
      if (eof) ADVANCE(99);
      if (lookahead == '"') ADVANCE(14);
      if (lookahead == ')') ADVANCE(104);
      if (lookahead == '/') ADVANCE(267);
      if (lookahead == ';') ADVANCE(102);
      if (lookahead == '=') ADVANCE(96);
      if (lookahead == '>') ADVANCE(201);
      if (lookahead == 'A') ADVANCE(452);
      if (lookahead == '~') ADVANCE(526);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(98)
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(525);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(anon_sym_COMMA);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(anon_sym_ASSERT);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(anon_sym_ASSERT);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(anon_sym_ASSERT);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(anon_sym_SORT_BY_NAME);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 111:
      ACCEPT_TOKEN(anon_sym_SORT_BY_NAME);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 112:
      ACCEPT_TOKEN(anon_sym_SORT_BY_NAME);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(anon_sym_SORT);
      if (lookahead == '_') ADVANCE(292);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(anon_sym_SORT);
      if (lookahead == '_') ADVANCE(291);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(anon_sym_SORT);
      if (lookahead == '_') ADVANCE(687);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '^') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(anon_sym_SORT);
      if (lookahead == '_') ADVANCE(688);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '^') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(anon_sym_SORT);
      if (lookahead == '_') ADVANCE(689);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '^') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(anon_sym_SORT);
      if (lookahead == '_') ADVANCE(690);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '^') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(anon_sym_SORT_BY_ALIGNMENT);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 120:
      ACCEPT_TOKEN(anon_sym_SORT_BY_ALIGNMENT);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(anon_sym_SORT_NONE);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(anon_sym_SORT_NONE);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 123:
      ACCEPT_TOKEN(anon_sym_SORT_NONE);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(anon_sym_SORT_BY_INIT_PRIORITY);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(anon_sym_SORT_BY_INIT_PRIORITY);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(anon_sym_REVERSE);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(anon_sym_REVERSE);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(anon_sym_REVERSE);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(anon_sym_EXCLUDE_FILE);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 130:
      ACCEPT_TOKEN(anon_sym_EXCLUDE_FILE);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 131:
      ACCEPT_TOKEN(anon_sym_AMP);
      if (lookahead == '&') ADVANCE(208);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 134:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 136:
      ACCEPT_TOKEN(anon_sym_CONSTRUCTORS);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 137:
      ACCEPT_TOKEN(anon_sym_CONSTRUCTORS);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(anon_sym_PLUS_EQ);
      END_STATE();
    case 139:
      ACCEPT_TOKEN(anon_sym_PLUS_EQ);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 140:
      ACCEPT_TOKEN(anon_sym_DASH_EQ);
      END_STATE();
    case 141:
      ACCEPT_TOKEN(anon_sym_DASH_EQ);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 142:
      ACCEPT_TOKEN(anon_sym_STAR_EQ);
      END_STATE();
    case 143:
      ACCEPT_TOKEN(anon_sym_STAR_EQ);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 144:
      ACCEPT_TOKEN(anon_sym_SLASH_EQ);
      END_STATE();
    case 145:
      ACCEPT_TOKEN(anon_sym_SLASH_EQ);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(521);
      END_STATE();
    case 146:
      ACCEPT_TOKEN(anon_sym_SLASH_EQ);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('A' <= lookahead && lookahead <= ']') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(526);
      END_STATE();
    case 147:
      ACCEPT_TOKEN(anon_sym_LT_LT_EQ);
      END_STATE();
    case 148:
      ACCEPT_TOKEN(anon_sym_GT_GT_EQ);
      END_STATE();
    case 149:
      ACCEPT_TOKEN(anon_sym_AMP_EQ);
      END_STATE();
    case 150:
      ACCEPT_TOKEN(anon_sym_PIPE_EQ);
      END_STATE();
    case 151:
      ACCEPT_TOKEN(anon_sym_CARET_EQ);
      END_STATE();
    case 152:
      ACCEPT_TOKEN(anon_sym_CARET_EQ);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 153:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 154:
      ACCEPT_TOKEN(anon_sym_EQ);
      if (lookahead == '=') ADVANCE(195);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(526);
      END_STATE();
    case 155:
      ACCEPT_TOKEN(anon_sym_EQ);
      if (lookahead == '!' ||
          ('*' <= lookahead && lookahead <= '-') ||
          ('0' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          lookahead == '[' ||
          lookahead == ']' ||
          lookahead == '^') ADVANCE(767);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(521);
      END_STATE();
    case 156:
      ACCEPT_TOKEN(anon_sym_EQ);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(526);
      END_STATE();
    case 157:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 158:
      ACCEPT_TOKEN(anon_sym_ORIGIN);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 159:
      ACCEPT_TOKEN(anon_sym_ORIGIN);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 160:
      ACCEPT_TOKEN(anon_sym_LENGTH);
      END_STATE();
    case 161:
      ACCEPT_TOKEN(anon_sym_LENGTH);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 162:
      ACCEPT_TOKEN(anon_sym_LENGTH);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 163:
      ACCEPT_TOKEN(anon_sym_l);
      if (lookahead == 'e') ADVANCE(518);
      if (lookahead == 'o') ADVANCE(514);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 164:
      ACCEPT_TOKEN(anon_sym_l);
      if (lookahead == 'e') ADVANCE(94);
      END_STATE();
    case 165:
      ACCEPT_TOKEN(anon_sym_len);
      END_STATE();
    case 166:
      ACCEPT_TOKEN(anon_sym_len);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 167:
      ACCEPT_TOKEN(anon_sym_BANG);
      END_STATE();
    case 168:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 169:
      ACCEPT_TOKEN(anon_sym_DASH);
      if (lookahead == '=') ADVANCE(140);
      END_STATE();
    case 170:
      ACCEPT_TOKEN(anon_sym_PLUS);
      END_STATE();
    case 171:
      ACCEPT_TOKEN(anon_sym_PLUS);
      if (lookahead == '=') ADVANCE(138);
      END_STATE();
    case 172:
      ACCEPT_TOKEN(anon_sym_TILDE);
      END_STATE();
    case 173:
      ACCEPT_TOKEN(anon_sym_TILDE);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('A' <= lookahead && lookahead <= ']') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(526);
      END_STATE();
    case 174:
      ACCEPT_TOKEN(anon_sym_NEXT);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 175:
      ACCEPT_TOKEN(anon_sym_NEXT);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 176:
      ACCEPT_TOKEN(anon_sym_ABSOLUTE);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 177:
      ACCEPT_TOKEN(anon_sym_ABSOLUTE);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 178:
      ACCEPT_TOKEN(anon_sym_DATA_SEGMENT_END);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 179:
      ACCEPT_TOKEN(anon_sym_DATA_SEGMENT_END);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 180:
      ACCEPT_TOKEN(anon_sym_BLOCK);
      END_STATE();
    case 181:
      ACCEPT_TOKEN(anon_sym_BLOCK);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 182:
      ACCEPT_TOKEN(anon_sym_BLOCK);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 183:
      ACCEPT_TOKEN(anon_sym_LOG2CEIL);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 184:
      ACCEPT_TOKEN(anon_sym_LOG2CEIL);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 185:
      ACCEPT_TOKEN(anon_sym_STAR);
      END_STATE();
    case 186:
      ACCEPT_TOKEN(anon_sym_STAR);
      if (lookahead == '=') ADVANCE(142);
      END_STATE();
    case 187:
      ACCEPT_TOKEN(anon_sym_SLASH);
      if (lookahead == '*') ADVANCE(22);
      END_STATE();
    case 188:
      ACCEPT_TOKEN(anon_sym_SLASH);
      if (lookahead == '*') ADVANCE(22);
      if (lookahead == '=') ADVANCE(146);
      if (lookahead == 'D') ADVANCE(361);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          ('A' <= lookahead && lookahead <= ']') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(526);
      END_STATE();
    case 189:
      ACCEPT_TOKEN(anon_sym_SLASH);
      if (lookahead == '*') ADVANCE(22);
      if (lookahead == 'D') ADVANCE(361);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('A' <= lookahead && lookahead <= ']') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(526);
      END_STATE();
    case 190:
      ACCEPT_TOKEN(anon_sym_PERCENT);
      END_STATE();
    case 191:
      ACCEPT_TOKEN(anon_sym_LT_LT);
      END_STATE();
    case 192:
      ACCEPT_TOKEN(anon_sym_LT_LT);
      if (lookahead == '=') ADVANCE(147);
      END_STATE();
    case 193:
      ACCEPT_TOKEN(anon_sym_GT_GT);
      END_STATE();
    case 194:
      ACCEPT_TOKEN(anon_sym_GT_GT);
      if (lookahead == '=') ADVANCE(148);
      END_STATE();
    case 195:
      ACCEPT_TOKEN(anon_sym_EQ_EQ);
      END_STATE();
    case 196:
      ACCEPT_TOKEN(anon_sym_BANG_EQ);
      END_STATE();
    case 197:
      ACCEPT_TOKEN(anon_sym_LT_EQ);
      END_STATE();
    case 198:
      ACCEPT_TOKEN(anon_sym_GT_EQ);
      END_STATE();
    case 199:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '<') ADVANCE(192);
      if (lookahead == '=') ADVANCE(197);
      END_STATE();
    case 200:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '<') ADVANCE(191);
      if (lookahead == '=') ADVANCE(197);
      END_STATE();
    case 201:
      ACCEPT_TOKEN(anon_sym_GT);
      END_STATE();
    case 202:
      ACCEPT_TOKEN(anon_sym_GT);
      if (lookahead == '=') ADVANCE(198);
      if (lookahead == '>') ADVANCE(194);
      END_STATE();
    case 203:
      ACCEPT_TOKEN(anon_sym_GT);
      if (lookahead == '=') ADVANCE(198);
      if (lookahead == '>') ADVANCE(193);
      END_STATE();
    case 204:
      ACCEPT_TOKEN(anon_sym_CARET);
      END_STATE();
    case 205:
      ACCEPT_TOKEN(anon_sym_CARET);
      if (lookahead == '=') ADVANCE(151);
      END_STATE();
    case 206:
      ACCEPT_TOKEN(anon_sym_PIPE);
      if (lookahead == '=') ADVANCE(150);
      if (lookahead == '|') ADVANCE(209);
      END_STATE();
    case 207:
      ACCEPT_TOKEN(anon_sym_PIPE);
      if (lookahead == '|') ADVANCE(209);
      END_STATE();
    case 208:
      ACCEPT_TOKEN(anon_sym_AMP_AMP);
      END_STATE();
    case 209:
      ACCEPT_TOKEN(anon_sym_PIPE_PIPE);
      END_STATE();
    case 210:
      ACCEPT_TOKEN(anon_sym_QMARK);
      END_STATE();
    case 211:
      ACCEPT_TOKEN(anon_sym_DEFINED);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 212:
      ACCEPT_TOKEN(anon_sym_DEFINED);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 213:
      ACCEPT_TOKEN(anon_sym_CONSTANT);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 214:
      ACCEPT_TOKEN(anon_sym_CONSTANT);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 215:
      ACCEPT_TOKEN(anon_sym_SIZEOF_HEADERS);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 216:
      ACCEPT_TOKEN(anon_sym_SIZEOF_HEADERS);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 217:
      ACCEPT_TOKEN(anon_sym_ALIGNOF);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 218:
      ACCEPT_TOKEN(anon_sym_ALIGNOF);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 219:
      ACCEPT_TOKEN(anon_sym_SIZEOF);
      if (lookahead == '_') ADVANCE(360);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 220:
      ACCEPT_TOKEN(anon_sym_SIZEOF);
      if (lookahead == '_') ADVANCE(588);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 221:
      ACCEPT_TOKEN(anon_sym_ADDR);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 222:
      ACCEPT_TOKEN(anon_sym_ADDR);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 223:
      ACCEPT_TOKEN(anon_sym_LOADADDR);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 224:
      ACCEPT_TOKEN(anon_sym_LOADADDR);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 225:
      ACCEPT_TOKEN(anon_sym_ALIGN);
      if (lookahead == 'O') ADVANCE(579);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 226:
      ACCEPT_TOKEN(anon_sym_ALIGN);
      if (lookahead == 'O') ADVANCE(348);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 227:
      ACCEPT_TOKEN(anon_sym_ALIGN);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 228:
      ACCEPT_TOKEN(anon_sym_DATA_SEGMENT_ALIGN);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 229:
      ACCEPT_TOKEN(anon_sym_DATA_SEGMENT_ALIGN);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 230:
      ACCEPT_TOKEN(anon_sym_DATA_SEGMENT_RELRO_END);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 231:
      ACCEPT_TOKEN(anon_sym_DATA_SEGMENT_RELRO_END);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 232:
      ACCEPT_TOKEN(anon_sym_MAX);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 233:
      ACCEPT_TOKEN(anon_sym_MAX);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 234:
      ACCEPT_TOKEN(anon_sym_MIN);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 235:
      ACCEPT_TOKEN(anon_sym_MIN);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 236:
      ACCEPT_TOKEN(anon_sym_SEGMENT_START);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 237:
      ACCEPT_TOKEN(anon_sym_SEGMENT_START);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 238:
      ACCEPT_TOKEN(anon_sym_OVERLAY);
      END_STATE();
    case 239:
      ACCEPT_TOKEN(anon_sym_OVERLAY);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 240:
      ACCEPT_TOKEN(anon_sym_OVERLAY);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 241:
      ACCEPT_TOKEN(anon_sym_NOLOAD);
      END_STATE();
    case 242:
      ACCEPT_TOKEN(anon_sym_NOLOAD);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 243:
      ACCEPT_TOKEN(anon_sym_NOLOAD);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 244:
      ACCEPT_TOKEN(anon_sym_DSECT);
      END_STATE();
    case 245:
      ACCEPT_TOKEN(anon_sym_DSECT);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 246:
      ACCEPT_TOKEN(anon_sym_DSECT);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 247:
      ACCEPT_TOKEN(anon_sym_COPY);
      END_STATE();
    case 248:
      ACCEPT_TOKEN(anon_sym_COPY);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 249:
      ACCEPT_TOKEN(anon_sym_COPY);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 250:
      ACCEPT_TOKEN(anon_sym_INFO);
      END_STATE();
    case 251:
      ACCEPT_TOKEN(anon_sym_INFO);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 252:
      ACCEPT_TOKEN(anon_sym_INFO);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 253:
      ACCEPT_TOKEN(anon_sym_READONLY);
      END_STATE();
    case 254:
      ACCEPT_TOKEN(anon_sym_READONLY);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 255:
      ACCEPT_TOKEN(anon_sym_READONLY);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 256:
      ACCEPT_TOKEN(anon_sym_TYPE);
      END_STATE();
    case 257:
      ACCEPT_TOKEN(anon_sym_TYPE);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 258:
      ACCEPT_TOKEN(anon_sym_TYPE);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 259:
      ACCEPT_TOKEN(anon_sym_BIND);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 260:
      ACCEPT_TOKEN(anon_sym_BIND);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 261:
      ACCEPT_TOKEN(anon_sym_global);
      if (lookahead == ':') ADVANCE(35);
      if (lookahead == '!' ||
          lookahead == '$' ||
          lookahead == '*' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(790);
      END_STATE();
    case 262:
      ACCEPT_TOKEN(anon_sym_global);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 263:
      ACCEPT_TOKEN(anon_sym_local);
      if (lookahead == ':') ADVANCE(35);
      if (lookahead == '!' ||
          lookahead == '$' ||
          lookahead == '*' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(790);
      END_STATE();
    case 264:
      ACCEPT_TOKEN(anon_sym_local);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 265:
      ACCEPT_TOKEN(anon_sym_extern);
      if (lookahead == ':') ADVANCE(35);
      if (lookahead == '!' ||
          lookahead == '$' ||
          lookahead == '*' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(790);
      END_STATE();
    case 266:
      ACCEPT_TOKEN(sym_NAME);
      END_STATE();
    case 267:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == '*') ADVANCE(22);
      if (lookahead == 'D') ADVANCE(361);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('A' <= lookahead && lookahead <= ']') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(526);
      END_STATE();
    case 268:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == '*') ADVANCE(678);
      if (lookahead == '=') ADVANCE(145);
      if (lookahead == 'D') ADVANCE(362);
      if (lookahead == '!' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(521);
      END_STATE();
    case 269:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == '*') ADVANCE(678);
      if (lookahead == 'D') ADVANCE(362);
      if (lookahead == '!' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(521);
      END_STATE();
    case 270:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == '/') ADVANCE(526);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('A' <= lookahead && lookahead <= ']') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(526);
      END_STATE();
    case 271:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == '/') ADVANCE(521);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(521);
      END_STATE();
    case 272:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == '2') ADVANCE(299);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 273:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'A') ADVANCE(467);
      if (lookahead == 'E') ADVANCE(346);
      if (lookahead == 'S') ADVANCE(329);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(522);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(525);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('C' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(522);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 274:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'A') ADVANCE(492);
      if (lookahead == 'I') ADVANCE(395);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 275:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'A') ADVANCE(508);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 276:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'A') ADVANCE(433);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('B' <= lookahead && lookahead <= ']') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(526);
      END_STATE();
    case 277:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'A') ADVANCE(436);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('B' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(521);
      END_STATE();
    case 278:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'A') ADVANCE(389);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 279:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'A') ADVANCE(308);
      if (lookahead == 'G') ADVANCE(272);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 280:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'A') ADVANCE(497);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 281:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'A') ADVANCE(311);
      if (lookahead == 'V') ADVANCE(333);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 282:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'A') ADVANCE(312);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 283:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'A') ADVANCE(302);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 284:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'A') ADVANCE(385);
      if (lookahead == 'I') ADVANCE(404);
      if (lookahead == 'N') ADVANCE(287);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 285:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'A') ADVANCE(313);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 286:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'A') ADVANCE(410);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 287:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'A') ADVANCE(390);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 288:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'A') ADVANCE(446);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 289:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'A') ADVANCE(386);
      if (lookahead == 'E') ADVANCE(409);
      if (lookahead == 'R') ADVANCE(337);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 290:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'B') ADVANCE(457);
      if (lookahead == 'D') ADVANCE(300);
      if (lookahead == 'L') ADVANCE(364);
      if (lookahead == 'S') ADVANCE(462);
      if (lookahead == 'b' ||
          lookahead == 'd') ADVANCE(522);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(525);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(522);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 291:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'B') ADVANCE(500);
      if (lookahead == 'N') ADVANCE(423);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 292:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'B') ADVANCE(501);
      if (lookahead == 'N') ADVANCE(429);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 293:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'C') ADVANCE(376);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 294:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'C') ADVANCE(276);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('A' <= lookahead && lookahead <= ']') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(526);
      END_STATE();
    case 295:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'C') ADVANCE(379);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 296:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'C') ADVANCE(277);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(521);
      END_STATE();
    case 297:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'C') ADVANCE(470);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 298:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'C') ADVANCE(480);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 299:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'C') ADVANCE(332);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 300:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'D') ADVANCE(432);
      if (lookahead == 'B' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(522);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(525);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(522);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 301:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'D') ADVANCE(259);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 302:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'D') ADVANCE(242);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 303:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'D') ADVANCE(211);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 304:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'D') ADVANCE(270);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('A' <= lookahead && lookahead <= ']') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(526);
      END_STATE();
    case 305:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'D') ADVANCE(178);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 306:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'D') ADVANCE(230);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 307:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'D') ADVANCE(271);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(521);
      END_STATE();
    case 308:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'D') ADVANCE(282);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 309:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'D') ADVANCE(434);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 310:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'D') ADVANCE(322);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 311:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'D') ADVANCE(426);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 312:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'D') ADVANCE(309);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 313:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'D') ADVANCE(334);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 314:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(281);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 315:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(351);
      if (lookahead == 'I') ADVANCE(502);
      if (lookahead == 'O') ADVANCE(437);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 316:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(257);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 317:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(127);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 318:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(176);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 319:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(122);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 320:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(111);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 321:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(491);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 322:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(505);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 323:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(126);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 324:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(121);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 325:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(129);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 326:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(110);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 327:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(493);
      if (lookahead == 'O') ADVANCE(380);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 328:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(440);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 329:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(297);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 330:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(449);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 331:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(402);
      if (lookahead == 'O') ADVANCE(279);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 332:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(367);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 333:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(451);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 334:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(439);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 335:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(421);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 336:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(303);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 337:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(383);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 338:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(407);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 339:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(412);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 340:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(413);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 341:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(411);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 342:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(444);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 343:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(441);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 344:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(285);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 345:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'E') ADVANCE(358);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 346:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'F') ADVANCE(368);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(522);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(525);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'E') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(522);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 347:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'F') ADVANCE(219);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 348:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'F') ADVANCE(217);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 349:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'F') ADVANCE(365);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 350:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'F') ADVANCE(418);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 351:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'G') ADVANCE(388);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 352:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'G') ADVANCE(369);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 353:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'G') ADVANCE(396);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 354:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'G') ADVANCE(471);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 355:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'G') ADVANCE(415);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 356:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'G') ADVANCE(398);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 357:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'G') ADVANCE(400);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 358:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'G') ADVANCE(391);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 359:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'H') ADVANCE(161);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 360:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'H') ADVANCE(344);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 361:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'I') ADVANCE(453);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('A' <= lookahead && lookahead <= ']') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(526);
      END_STATE();
    case 362:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'I') ADVANCE(455);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(521);
      END_STATE();
    case 363:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'I') ADVANCE(394);
      if (lookahead == 'L') ADVANCE(417);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(522);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(525);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(522);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 364:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'I') ADVANCE(353);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 365:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'I') ADVANCE(384);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 366:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'I') ADVANCE(352);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 367:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'I') ADVANCE(378);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 368:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'I') ADVANCE(408);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(522);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(525);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(522);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 369:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'I') ADVANCE(397);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 370:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'I') ADVANCE(427);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 371:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'I') ADVANCE(483);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 372:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'I') ADVANCE(484);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 373:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'I') ADVANCE(355);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 374:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'I') ADVANCE(356);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 375:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'I') ADVANCE(357);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 376:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'K') ADVANCE(181);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 377:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'L') ADVANCE(489);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 378:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'L') ADVANCE(183);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 379:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'L') ADVANCE(487);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 380:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'L') ADVANCE(428);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 381:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'L') ADVANCE(280);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 382:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'L') ADVANCE(498);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 383:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'L') ADVANCE(445);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 384:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'L') ADVANCE(325);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 385:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'L') ADVANCE(373);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 386:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'L') ADVANCE(374);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 387:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'L') ADVANCE(375);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 388:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'M') ADVANCE(338);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 389:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'M') ADVANCE(326);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 390:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'M') ADVANCE(320);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 391:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'M') ADVANCE(339);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 392:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'M') ADVANCE(340);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 393:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(350);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 394:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(301);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 395:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(234);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 396:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(226);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 397:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(158);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 398:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(228);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 399:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(278);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 400:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(227);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 401:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(461);
      if (lookahead == 'P') ADVANCE(496);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 402:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(354);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 403:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(460);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 404:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(371);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 405:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(382);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 406:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(324);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 407:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(478);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 408:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(336);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 409:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(305);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 410:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(473);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 411:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(306);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 412:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(482);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 413:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(475);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 414:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(319);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 415:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'N') ADVANCE(392);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 416:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'O') ADVANCE(401);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(522);
      if (lookahead == 'H' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(525);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(522);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 417:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'O') ADVANCE(293);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 418:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'O') ADVANCE(251);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 419:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'O') ADVANCE(403);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 420:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'O') ADVANCE(435);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 421:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'O') ADVANCE(347);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 422:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'O') ADVANCE(377);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 423:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'O') ADVANCE(406);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 424:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'O') ADVANCE(442);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 425:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'O') ADVANCE(510);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 426:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'O') ADVANCE(405);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 427:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'O') ADVANCE(450);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 428:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'O') ADVANCE(283);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 429:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'O') ADVANCE(414);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 430:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'P') ADVANCE(443);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 431:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'P') ADVANCE(316);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 432:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'R') ADVANCE(221);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(522);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(525);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(522);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 433:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'R') ADVANCE(304);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('A' <= lookahead && lookahead <= ']') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(526);
      END_STATE();
    case 434:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'R') ADVANCE(223);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 435:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'R') ADVANCE(476);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 436:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'R') ADVANCE(307);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(521);
      END_STATE();
    case 437:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'R') ADVANCE(469);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 438:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'R') ADVANCE(488);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 439:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'R') ADVANCE(454);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 440:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'R') ADVANCE(381);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 441:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'R') ADVANCE(477);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 442:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'R') ADVANCE(456);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 443:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'R') ADVANCE(370);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 444:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'R') ADVANCE(472);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 445:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'R') ADVANCE(425);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 446:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'R') ADVANCE(474);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 447:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'R') ADVANCE(366);
      if (lookahead == 'V') ADVANCE(328);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 448:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'R') ADVANCE(366);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 449:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'R') ADVANCE(463);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 450:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'R') ADVANCE(372);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 451:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'R') ADVANCE(466);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 452:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'S') ADVANCE(462);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 453:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'S') ADVANCE(294);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('A' <= lookahead && lookahead <= ']') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(526);
      END_STATE();
    case 454:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'S') ADVANCE(215);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 455:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'S') ADVANCE(296);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(521);
      END_STATE();
    case 456:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'S') ADVANCE(136);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 457:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'S') ADVANCE(422);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(522);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(525);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(522);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 458:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'S') ADVANCE(459);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 459:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'S') ADVANCE(343);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 460:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'S') ADVANCE(481);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 461:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'S') ADVANCE(479);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 462:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'S') ADVANCE(342);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 463:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'S') ADVANCE(323);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 464:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'S') ADVANCE(485);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 465:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'S') ADVANCE(345);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 466:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'S') ADVANCE(317);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 467:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'T') ADVANCE(275);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(522);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(525);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(522);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 468:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'T') ADVANCE(174);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 469:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'T') ADVANCE(113);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 470:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'T') ADVANCE(245);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 471:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'T') ADVANCE(359);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 472:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'T') ADVANCE(108);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 473:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'T') ADVANCE(213);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 474:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'T') ADVANCE(236);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 475:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'T') ADVANCE(119);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 476:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'T') ADVANCE(114);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 477:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'T') ADVANCE(107);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 478:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'T') ADVANCE(509);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 479:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'T') ADVANCE(286);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 480:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'T') ADVANCE(424);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 481:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'T') ADVANCE(438);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 482:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'T') ADVANCE(504);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 483:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'T') ADVANCE(506);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 484:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'T') ADVANCE(499);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 485:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'T') ADVANCE(288);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 486:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'T') ADVANCE(318);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 487:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'U') ADVANCE(310);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 488:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'U') ADVANCE(298);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 489:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'U') ADVANCE(486);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 490:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'V') ADVANCE(328);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 491:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'V') ADVANCE(330);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 492:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'X') ADVANCE(232);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 493:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'X') ADVANCE(468);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 494:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'X') ADVANCE(295);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 495:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'Y') ADVANCE(431);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 496:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'Y') ADVANCE(248);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 497:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'Y') ADVANCE(239);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 498:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'Y') ADVANCE(254);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 499:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'Y') ADVANCE(124);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 500:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'Y') ADVANCE(507);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 501:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'Y') ADVANCE(503);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 502:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'Z') ADVANCE(335);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 503:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == '_') ADVANCE(284);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 504:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == '_') ADVANCE(289);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 505:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == '_') ADVANCE(349);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 506:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == '_') ADVANCE(430);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 507:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == '_') ADVANCE(399);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 508:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == '_') ADVANCE(465);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 509:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == '_') ADVANCE(464);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 510:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == '_') ADVANCE(341);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 511:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'a') ADVANCE(516);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 512:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'a') ADVANCE(517);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 513:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'b') ADVANCE(512);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 514:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'c') ADVANCE(511);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 515:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'l') ADVANCE(519);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 516:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'l') ADVANCE(264);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 517:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'l') ADVANCE(262);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 518:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'n') ADVANCE(166);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 519:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'o') ADVANCE(513);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 520:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(521);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(520);
      END_STATE();
    case 521:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == '!' ||
          lookahead == '*' ||
          lookahead == '?' ||
          lookahead == '^') ADVANCE(767);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(521);
      END_STATE();
    case 522:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(522);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(525);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(522);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 523:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == 'K' ||
          lookahead == 'M' ||
          lookahead == 'k' ||
          lookahead == 'm') ADVANCE(525);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(523);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 524:
      ACCEPT_TOKEN(sym_NAME);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(523);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 525:
      ACCEPT_TOKEN(sym_NAME);
      if (('+' <= lookahead && lookahead <= '-') ||
          lookahead == ':' ||
          lookahead == '=' ||
          lookahead == '[' ||
          lookahead == ']') ADVANCE(526);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(525);
      END_STATE();
    case 526:
      ACCEPT_TOKEN(sym_NAME);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('A' <= lookahead && lookahead <= ']') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(526);
      END_STATE();
    case 527:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      END_STATE();
    case 528:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == '2') ADVANCE(544);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 529:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'A') ADVANCE(648);
      if (lookahead == 'E') ADVANCE(577);
      if (lookahead == 'S') ADVANCE(566);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(672);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(675);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('C' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(672);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 530:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'A') ADVANCE(648);
      if (lookahead == 'E') ADVANCE(577);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(672);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(675);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('C' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(672);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 531:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'A') ADVANCE(661);
      if (lookahead == 'I') ADVANCE(608);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 532:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'A') ADVANCE(670);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 533:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'A') ADVANCE(552);
      if (lookahead == 'G') ADVANCE(528);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 534:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'A') ADVANCE(554);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 535:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'A') ADVANCE(604);
      if (lookahead == 'E') ADVANCE(618);
      if (lookahead == 'R') ADVANCE(569);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 536:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'A') ADVANCE(665);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 537:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'A') ADVANCE(556);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 538:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'A') ADVANCE(619);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 539:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'A') ADVANCE(555);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 540:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'A') ADVANCE(551);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 541:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'A') ADVANCE(639);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 542:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'B') ADVANCE(644);
      if (lookahead == 'D') ADVANCE(546);
      if (lookahead == 'L') ADVANCE(590);
      if (lookahead == 'S') ADVANCE(643);
      if (lookahead == 'b' ||
          lookahead == 'd') ADVANCE(672);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(675);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(672);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 543:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'C') ADVANCE(596);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 544:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'C') ADVANCE(563);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 545:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'C') ADVANCE(654);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 546:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'D') ADVANCE(633);
      if (lookahead == 'B' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(672);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(675);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(672);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 547:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'D') ADVANCE(260);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 548:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'D') ADVANCE(212);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 549:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'D') ADVANCE(179);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 550:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'D') ADVANCE(231);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 551:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'D') ADVANCE(243);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 552:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'D') ADVANCE(534);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 553:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'D') ADVANCE(634);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 554:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'D') ADVANCE(553);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 555:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'D') ADVANCE(630);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 556:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'D') ADVANCE(567);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 557:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'E') ADVANCE(581);
      if (lookahead == 'I') ADVANCE(667);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 558:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'E') ADVANCE(177);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 559:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'E') ADVANCE(258);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 560:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'E') ADVANCE(637);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 561:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'E') ADVANCE(662);
      if (lookahead == 'O') ADVANCE(603);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 562:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'E') ADVANCE(662);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 563:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'E') ADVANCE(591);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 564:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'E') ADVANCE(614);
      if (lookahead == 'O') ADVANCE(533);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 565:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'E') ADVANCE(625);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 566:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'E') ADVANCE(545);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 567:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'E') ADVANCE(635);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 568:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'E') ADVANCE(548);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 569:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'E') ADVANCE(601);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 570:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'E') ADVANCE(638);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 571:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'E') ADVANCE(617);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 572:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'E') ADVANCE(622);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 573:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'E') ADVANCE(537);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 574:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'E') ADVANCE(621);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 575:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'E') ADVANCE(539);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 576:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'E') ADVANCE(586);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 577:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'F') ADVANCE(593);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(672);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(675);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'E') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(672);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 578:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'F') ADVANCE(220);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 579:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'F') ADVANCE(218);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 580:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'F') ADVANCE(627);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 581:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'G') ADVANCE(605);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 582:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'G') ADVANCE(594);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 583:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'G') ADVANCE(650);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 584:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'G') ADVANCE(609);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 585:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'G') ADVANCE(611);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 586:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'G') ADVANCE(606);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 587:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'H') ADVANCE(162);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 588:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'H') ADVANCE(573);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 589:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'I') ADVANCE(607);
      if (lookahead == 'L') ADVANCE(623);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(672);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(675);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(672);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 590:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'I') ADVANCE(584);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 591:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'I') ADVANCE(599);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 592:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'I') ADVANCE(582);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 593:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'I') ADVANCE(616);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(672);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(675);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(672);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 594:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'I') ADVANCE(610);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 595:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'I') ADVANCE(585);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 596:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'K') ADVANCE(182);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 597:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'L') ADVANCE(623);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(672);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(675);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(672);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 598:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'L') ADVANCE(660);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 599:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'L') ADVANCE(184);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 600:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'L') ADVANCE(666);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 601:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'L') ADVANCE(636);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 602:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'L') ADVANCE(536);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 603:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'L') ADVANCE(631);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 604:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'L') ADVANCE(595);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 605:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'M') ADVANCE(571);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 606:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'M') ADVANCE(572);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 607:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'N') ADVANCE(547);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 608:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'N') ADVANCE(235);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 609:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'N') ADVANCE(225);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 610:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'N') ADVANCE(159);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 611:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'N') ADVANCE(229);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 612:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'N') ADVANCE(645);
      if (lookahead == 'P') ADVANCE(664);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 613:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'N') ADVANCE(645);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 614:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'N') ADVANCE(583);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 615:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'N') ADVANCE(580);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 616:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'N') ADVANCE(568);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 617:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'N') ADVANCE(655);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 618:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'N') ADVANCE(549);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 619:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'N') ADVANCE(652);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 620:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'N') ADVANCE(600);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 621:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'N') ADVANCE(550);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 622:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'N') ADVANCE(657);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 623:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'O') ADVANCE(543);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 624:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'O') ADVANCE(598);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 625:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'O') ADVANCE(578);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 626:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'O') ADVANCE(612);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(672);
      if (lookahead == 'H' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(675);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(672);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 627:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'O') ADVANCE(252);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 628:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'O') ADVANCE(613);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(672);
      if (lookahead == 'H' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(675);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(672);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 629:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'O') ADVANCE(669);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 630:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'O') ADVANCE(620);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 631:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'O') ADVANCE(540);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 632:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'P') ADVANCE(559);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 633:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'R') ADVANCE(222);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(672);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(675);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(672);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 634:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'R') ADVANCE(224);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 635:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'R') ADVANCE(642);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 636:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'R') ADVANCE(629);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 637:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'R') ADVANCE(651);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 638:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'R') ADVANCE(602);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 639:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'R') ADVANCE(653);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 640:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'R') ADVANCE(592);
      if (lookahead == 'V') ADVANCE(570);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 641:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'R') ADVANCE(592);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 642:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'S') ADVANCE(216);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 643:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'S') ADVANCE(560);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 644:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'S') ADVANCE(624);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(672);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(675);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(672);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 645:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'S') ADVANCE(656);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 646:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'S') ADVANCE(576);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 647:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'S') ADVANCE(658);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 648:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'T') ADVANCE(532);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(672);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(675);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(672);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 649:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'T') ADVANCE(175);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 650:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'T') ADVANCE(587);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 651:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'T') ADVANCE(109);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 652:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'T') ADVANCE(214);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 653:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'T') ADVANCE(237);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 654:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'T') ADVANCE(246);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 655:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'T') ADVANCE(671);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 656:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'T') ADVANCE(538);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 657:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'T') ADVANCE(668);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 658:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'T') ADVANCE(541);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 659:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'T') ADVANCE(558);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 660:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'U') ADVANCE(659);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 661:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'X') ADVANCE(233);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 662:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'X') ADVANCE(649);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 663:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'Y') ADVANCE(632);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 664:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'Y') ADVANCE(249);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 665:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'Y') ADVANCE(240);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 666:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'Y') ADVANCE(255);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 667:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'Z') ADVANCE(565);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Y') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 668:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == '_') ADVANCE(535);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 669:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == '_') ADVANCE(574);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 670:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == '_') ADVANCE(646);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 671:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == '_') ADVANCE(647);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 672:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(672);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(675);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(672);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 673:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == 'K' ||
          lookahead == 'M' ||
          lookahead == 'k' ||
          lookahead == 'm') ADVANCE(675);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(673);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 674:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(673);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('G' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 675:
      ACCEPT_TOKEN(sym_SYMBOLNAME);
      if (lookahead == '$' ||
          ('.' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(675);
      END_STATE();
    case 676:
      ACCEPT_TOKEN(sym_LNAME);
      if (lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          ('A' <= lookahead && lookahead <= ']') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(676);
      END_STATE();
    case 677:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == '*') ADVANCE(678);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 678:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == '*') ADVANCE(679);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('+' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(678);
      if (lookahead != 0) ADVANCE(22);
      END_STATE();
    case 679:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == '/') ADVANCE(767);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(678);
      if (lookahead != 0) ADVANCE(22);
      END_STATE();
    case 680:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == '=') ADVANCE(143);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 681:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == '=') ADVANCE(139);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 682:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == '=') ADVANCE(141);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 683:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == '=') ADVANCE(152);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 684:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'A') ADVANCE(713);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('B' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 685:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'A') ADVANCE(711);
      if (lookahead == 'I') ADVANCE(718);
      if (lookahead == 'N') ADVANCE(684);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('B' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 686:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'A') ADVANCE(711);
      if (lookahead == 'N') ADVANCE(684);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('B' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 687:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'B') ADVANCE(756);
      if (lookahead == 'N') ADVANCE(722);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 688:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'B') ADVANCE(757);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 689:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'B') ADVANCE(758);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 690:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'B') ADVANCE(759);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 691:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'C') ADVANCE(710);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 692:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'C') ADVANCE(748);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 693:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'D') ADVANCE(695);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 694:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'E') ADVANCE(753);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 695:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'E') ADVANCE(760);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 696:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'E') ADVANCE(128);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 697:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'E') ADVANCE(123);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 698:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'E') ADVANCE(130);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 699:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'E') ADVANCE(112);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 700:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'E') ADVANCE(731);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 701:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'E') ADVANCE(717);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 702:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'F') ADVANCE(707);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 703:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'G') ADVANCE(720);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 704:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'I') ADVANCE(703);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 705:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'I') ADVANCE(746);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 706:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'I') ADVANCE(718);
      if (lookahead == 'N') ADVANCE(684);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 707:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'I') ADVANCE(712);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 708:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'I') ADVANCE(745);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 709:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'I') ADVANCE(725);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 710:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'L') ADVANCE(751);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 711:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'L') ADVANCE(704);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 712:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'L') ADVANCE(698);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 713:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'M') ADVANCE(699);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 714:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'M') ADVANCE(701);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 715:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'N') ADVANCE(684);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 716:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'N') ADVANCE(741);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 717:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'N') ADVANCE(743);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 718:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'N') ADVANCE(705);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 719:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'N') ADVANCE(697);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 720:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'N') ADVANCE(714);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 721:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'O') ADVANCE(730);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 722:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'O') ADVANCE(719);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 723:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'O') ADVANCE(733);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 724:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'O') ADVANCE(716);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 725:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'O') ADVANCE(735);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 726:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'O') ADVANCE(736);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 727:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'O') ADVANCE(737);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 728:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'O') ADVANCE(738);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 729:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'P') ADVANCE(734);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 730:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'R') ADVANCE(742);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 731:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'R') ADVANCE(740);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 732:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'R') ADVANCE(752);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 733:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'R') ADVANCE(739);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 734:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'R') ADVANCE(709);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 735:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'R') ADVANCE(708);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 736:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'R') ADVANCE(744);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 737:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'R') ADVANCE(749);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 738:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'R') ADVANCE(750);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 739:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'S') ADVANCE(137);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 740:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'S') ADVANCE(696);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 741:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'S') ADVANCE(747);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 742:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'T') ADVANCE(115);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 743:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'T') ADVANCE(120);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 744:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'T') ADVANCE(116);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 745:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'T') ADVANCE(755);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 746:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'T') ADVANCE(762);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 747:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'T') ADVANCE(732);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 748:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'T') ADVANCE(723);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 749:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'T') ADVANCE(117);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 750:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'T') ADVANCE(118);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 751:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'U') ADVANCE(693);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 752:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'U') ADVANCE(692);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 753:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'V') ADVANCE(700);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 754:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'X') ADVANCE(691);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 755:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'Y') ADVANCE(125);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 756:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'Y') ADVANCE(761);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 757:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'Y') ADVANCE(763);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 758:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'Y') ADVANCE(764);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 759:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == 'Y') ADVANCE(765);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 760:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == '_') ADVANCE(702);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '^') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 761:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == '_') ADVANCE(685);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '^') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 762:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == '_') ADVANCE(729);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '^') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 763:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == '_') ADVANCE(686);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '^') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 764:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == '_') ADVANCE(706);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '^') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 765:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == '_') ADVANCE(715);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '^') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 766:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == '!' ||
          ('*' <= lookahead && lookahead <= '-') ||
          ('0' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          lookahead == '[' ||
          lookahead == ']' ||
          lookahead == '^') ADVANCE(767);
      if (lookahead == '$' ||
          lookahead == '.' ||
          lookahead == '/' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(521);
      END_STATE();
    case 767:
      ACCEPT_TOKEN(sym_wildcard_name);
      if (lookahead == '!' ||
          lookahead == '$' ||
          ('*' <= lookahead && lookahead <= ':') ||
          lookahead == '=' ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z') ||
          lookahead == '~') ADVANCE(767);
      END_STATE();
    case 768:
      ACCEPT_TOKEN(aux_sym_INT_token2);
      END_STATE();
    case 769:
      ACCEPT_TOKEN(aux_sym_INT_token2);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(769);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(768);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(95);
      END_STATE();
    case 770:
      ACCEPT_TOKEN(aux_sym_INT_token2);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(774);
      END_STATE();
    case 771:
      ACCEPT_TOKEN(aux_sym_INT_token3);
      END_STATE();
    case 772:
      ACCEPT_TOKEN(aux_sym_INT_token3);
      if (lookahead == 'X' ||
          lookahead == 'x') ADVANCE(770);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(769);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'h' ||
          lookahead == 'o') ADVANCE(768);
      if (lookahead == 'K' ||
          lookahead == 'M' ||
          lookahead == 'k' ||
          lookahead == 'm') ADVANCE(771);
      if (('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(773);
      END_STATE();
    case 773:
      ACCEPT_TOKEN(aux_sym_INT_token3);
      if (lookahead == 'B' ||
          lookahead == 'D' ||
          lookahead == 'b' ||
          lookahead == 'd') ADVANCE(769);
      if (lookahead == 'K' ||
          lookahead == 'M' ||
          lookahead == 'k' ||
          lookahead == 'm') ADVANCE(771);
      if (lookahead == 'H' ||
          lookahead == 'O' ||
          lookahead == 'X' ||
          lookahead == 'h' ||
          lookahead == 'o' ||
          lookahead == 'x') ADVANCE(768);
      if (('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(773);
      END_STATE();
    case 774:
      ACCEPT_TOKEN(aux_sym_INT_token3);
      if (lookahead == 'K' ||
          lookahead == 'M' ||
          lookahead == 'k' ||
          lookahead == 'm') ADVANCE(771);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(774);
      END_STATE();
    case 775:
      ACCEPT_TOKEN(sym_VERS_TAG);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(775);
      END_STATE();
    case 776:
      ACCEPT_TOKEN(sym_VERS_IDENTIFIER);
      if (lookahead == ':') ADVANCE(35);
      if (lookahead == 'a') ADVANCE(781);
      if (lookahead == '!' ||
          lookahead == '$' ||
          lookahead == '*' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(790);
      END_STATE();
    case 777:
      ACCEPT_TOKEN(sym_VERS_IDENTIFIER);
      if (lookahead == ':') ADVANCE(35);
      if (lookahead == 'a') ADVANCE(782);
      if (lookahead == '!' ||
          lookahead == '$' ||
          lookahead == '*' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(790);
      END_STATE();
    case 778:
      ACCEPT_TOKEN(sym_VERS_IDENTIFIER);
      if (lookahead == ':') ADVANCE(35);
      if (lookahead == 'b') ADVANCE(777);
      if (lookahead == '!' ||
          lookahead == '$' ||
          lookahead == '*' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(790);
      END_STATE();
    case 779:
      ACCEPT_TOKEN(sym_VERS_IDENTIFIER);
      if (lookahead == ':') ADVANCE(35);
      if (lookahead == 'c') ADVANCE(776);
      if (lookahead == '!' ||
          lookahead == '$' ||
          lookahead == '*' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(790);
      END_STATE();
    case 780:
      ACCEPT_TOKEN(sym_VERS_IDENTIFIER);
      if (lookahead == ':') ADVANCE(35);
      if (lookahead == 'e') ADVANCE(787);
      if (lookahead == '!' ||
          lookahead == '$' ||
          lookahead == '*' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(790);
      END_STATE();
    case 781:
      ACCEPT_TOKEN(sym_VERS_IDENTIFIER);
      if (lookahead == ':') ADVANCE(35);
      if (lookahead == 'l') ADVANCE(263);
      if (lookahead == '!' ||
          lookahead == '$' ||
          lookahead == '*' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(790);
      END_STATE();
    case 782:
      ACCEPT_TOKEN(sym_VERS_IDENTIFIER);
      if (lookahead == ':') ADVANCE(35);
      if (lookahead == 'l') ADVANCE(261);
      if (lookahead == '!' ||
          lookahead == '$' ||
          lookahead == '*' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(790);
      END_STATE();
    case 783:
      ACCEPT_TOKEN(sym_VERS_IDENTIFIER);
      if (lookahead == ':') ADVANCE(35);
      if (lookahead == 'l') ADVANCE(786);
      if (lookahead == '!' ||
          lookahead == '$' ||
          lookahead == '*' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(790);
      END_STATE();
    case 784:
      ACCEPT_TOKEN(sym_VERS_IDENTIFIER);
      if (lookahead == ':') ADVANCE(35);
      if (lookahead == 'n') ADVANCE(265);
      if (lookahead == '!' ||
          lookahead == '$' ||
          lookahead == '*' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(790);
      END_STATE();
    case 785:
      ACCEPT_TOKEN(sym_VERS_IDENTIFIER);
      if (lookahead == ':') ADVANCE(35);
      if (lookahead == 'o') ADVANCE(779);
      if (lookahead == '!' ||
          lookahead == '$' ||
          lookahead == '*' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(790);
      END_STATE();
    case 786:
      ACCEPT_TOKEN(sym_VERS_IDENTIFIER);
      if (lookahead == ':') ADVANCE(35);
      if (lookahead == 'o') ADVANCE(778);
      if (lookahead == '!' ||
          lookahead == '$' ||
          lookahead == '*' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(790);
      END_STATE();
    case 787:
      ACCEPT_TOKEN(sym_VERS_IDENTIFIER);
      if (lookahead == ':') ADVANCE(35);
      if (lookahead == 'r') ADVANCE(784);
      if (lookahead == '!' ||
          lookahead == '$' ||
          lookahead == '*' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(790);
      END_STATE();
    case 788:
      ACCEPT_TOKEN(sym_VERS_IDENTIFIER);
      if (lookahead == ':') ADVANCE(35);
      if (lookahead == 't') ADVANCE(780);
      if (lookahead == '!' ||
          lookahead == '$' ||
          lookahead == '*' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(790);
      END_STATE();
    case 789:
      ACCEPT_TOKEN(sym_VERS_IDENTIFIER);
      if (lookahead == ':') ADVANCE(35);
      if (lookahead == 'x') ADVANCE(788);
      if (lookahead == '!' ||
          lookahead == '$' ||
          lookahead == '*' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(790);
      END_STATE();
    case 790:
      ACCEPT_TOKEN(sym_VERS_IDENTIFIER);
      if (lookahead == ':') ADVANCE(35);
      if (lookahead == '!' ||
          lookahead == '$' ||
          lookahead == '*' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '?' ||
          ('A' <= lookahead && lookahead <= '_') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(790);
      END_STATE();
    case 791:
      ACCEPT_TOKEN(sym_comment);
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
      if (lookahead == 'A') ADVANCE(1);
      if (lookahead == 'B') ADVANCE(2);
      if (lookahead == 'C') ADVANCE(3);
      if (lookahead == 'E') ADVANCE(4);
      if (lookahead == 'F') ADVANCE(5);
      if (lookahead == 'G') ADVANCE(6);
      if (lookahead == 'H') ADVANCE(7);
      if (lookahead == 'I') ADVANCE(8);
      if (lookahead == 'K') ADVANCE(9);
      if (lookahead == 'L') ADVANCE(10);
      if (lookahead == 'M') ADVANCE(11);
      if (lookahead == 'N') ADVANCE(12);
      if (lookahead == 'O') ADVANCE(13);
      if (lookahead == 'P') ADVANCE(14);
      if (lookahead == 'Q') ADVANCE(15);
      if (lookahead == 'R') ADVANCE(16);
      if (lookahead == 'S') ADVANCE(17);
      if (lookahead == 'T') ADVANCE(18);
      if (lookahead == 'V') ADVANCE(19);
      if (lookahead == 'o') ADVANCE(20);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(0)
      END_STATE();
    case 1:
      if (lookahead == 'F') ADVANCE(21);
      if (lookahead == 'L') ADVANCE(22);
      if (lookahead == 'S') ADVANCE(23);
      if (lookahead == 'T') ADVANCE(24);
      END_STATE();
    case 2:
      if (lookahead == 'E') ADVANCE(25);
      if (lookahead == 'Y') ADVANCE(26);
      END_STATE();
    case 3:
      if (lookahead == 'R') ADVANCE(27);
      END_STATE();
    case 4:
      if (lookahead == 'N') ADVANCE(28);
      if (lookahead == 'X') ADVANCE(29);
      END_STATE();
    case 5:
      if (lookahead == 'I') ADVANCE(30);
      if (lookahead == 'L') ADVANCE(31);
      if (lookahead == 'O') ADVANCE(32);
      END_STATE();
    case 6:
      if (lookahead == 'R') ADVANCE(33);
      END_STATE();
    case 7:
      if (lookahead == 'I') ADVANCE(34);
      if (lookahead == 'L') ADVANCE(35);
      END_STATE();
    case 8:
      if (lookahead == 'N') ADVANCE(36);
      END_STATE();
    case 9:
      if (lookahead == 'E') ADVANCE(37);
      END_STATE();
    case 10:
      if (lookahead == 'D') ADVANCE(38);
      if (lookahead == 'I') ADVANCE(39);
      if (lookahead == 'O') ADVANCE(40);
      END_STATE();
    case 11:
      if (lookahead == 'A') ADVANCE(41);
      if (lookahead == 'E') ADVANCE(42);
      END_STATE();
    case 12:
      if (lookahead == 'O') ADVANCE(43);
      END_STATE();
    case 13:
      if (lookahead == 'N') ADVANCE(44);
      if (lookahead == 'U') ADVANCE(45);
      END_STATE();
    case 14:
      if (lookahead == 'H') ADVANCE(46);
      if (lookahead == 'R') ADVANCE(47);
      END_STATE();
    case 15:
      if (lookahead == 'U') ADVANCE(48);
      END_STATE();
    case 16:
      if (lookahead == 'E') ADVANCE(49);
      END_STATE();
    case 17:
      if (lookahead == 'E') ADVANCE(50);
      if (lookahead == 'H') ADVANCE(51);
      if (lookahead == 'P') ADVANCE(52);
      if (lookahead == 'Q') ADVANCE(53);
      if (lookahead == 'T') ADVANCE(54);
      if (lookahead == 'U') ADVANCE(55);
      if (lookahead == 'Y') ADVANCE(56);
      END_STATE();
    case 18:
      if (lookahead == 'A') ADVANCE(57);
      END_STATE();
    case 19:
      if (lookahead == 'E') ADVANCE(58);
      END_STATE();
    case 20:
      ACCEPT_TOKEN(anon_sym_o);
      if (lookahead == 'r') ADVANCE(59);
      END_STATE();
    case 21:
      if (lookahead == 'T') ADVANCE(60);
      END_STATE();
    case 22:
      if (lookahead == 'I') ADVANCE(61);
      END_STATE();
    case 23:
      if (lookahead == 'C') ADVANCE(62);
      if (lookahead == '_') ADVANCE(63);
      END_STATE();
    case 24:
      ACCEPT_TOKEN(anon_sym_AT);
      END_STATE();
    case 25:
      if (lookahead == 'F') ADVANCE(64);
      END_STATE();
    case 26:
      if (lookahead == 'T') ADVANCE(65);
      END_STATE();
    case 27:
      if (lookahead == 'E') ADVANCE(66);
      END_STATE();
    case 28:
      if (lookahead == 'T') ADVANCE(67);
      END_STATE();
    case 29:
      if (lookahead == 'T') ADVANCE(68);
      END_STATE();
    case 30:
      if (lookahead == 'L') ADVANCE(69);
      END_STATE();
    case 31:
      if (lookahead == 'O') ADVANCE(70);
      END_STATE();
    case 32:
      if (lookahead == 'R') ADVANCE(71);
      END_STATE();
    case 33:
      if (lookahead == 'O') ADVANCE(72);
      END_STATE();
    case 34:
      if (lookahead == 'D') ADVANCE(73);
      END_STATE();
    case 35:
      if (lookahead == 'L') ADVANCE(74);
      END_STATE();
    case 36:
      if (lookahead == 'C') ADVANCE(75);
      if (lookahead == 'H') ADVANCE(76);
      if (lookahead == 'P') ADVANCE(77);
      if (lookahead == 'S') ADVANCE(78);
      END_STATE();
    case 37:
      if (lookahead == 'E') ADVANCE(79);
      END_STATE();
    case 38:
      if (lookahead == '_') ADVANCE(80);
      END_STATE();
    case 39:
      if (lookahead == 'N') ADVANCE(81);
      END_STATE();
    case 40:
      if (lookahead == 'N') ADVANCE(82);
      END_STATE();
    case 41:
      if (lookahead == 'P') ADVANCE(83);
      END_STATE();
    case 42:
      if (lookahead == 'M') ADVANCE(84);
      END_STATE();
    case 43:
      if (lookahead == 'C') ADVANCE(85);
      if (lookahead == 'F') ADVANCE(86);
      END_STATE();
    case 44:
      if (lookahead == 'L') ADVANCE(87);
      END_STATE();
    case 45:
      if (lookahead == 'T') ADVANCE(88);
      END_STATE();
    case 46:
      if (lookahead == 'D') ADVANCE(89);
      END_STATE();
    case 47:
      if (lookahead == 'O') ADVANCE(90);
      END_STATE();
    case 48:
      if (lookahead == 'A') ADVANCE(91);
      END_STATE();
    case 49:
      if (lookahead == 'G') ADVANCE(92);
      END_STATE();
    case 50:
      if (lookahead == 'A') ADVANCE(93);
      if (lookahead == 'C') ADVANCE(94);
      END_STATE();
    case 51:
      if (lookahead == 'O') ADVANCE(95);
      END_STATE();
    case 52:
      if (lookahead == 'E') ADVANCE(96);
      END_STATE();
    case 53:
      if (lookahead == 'U') ADVANCE(97);
      END_STATE();
    case 54:
      if (lookahead == 'A') ADVANCE(98);
      END_STATE();
    case 55:
      if (lookahead == 'B') ADVANCE(99);
      END_STATE();
    case 56:
      if (lookahead == 'S') ADVANCE(100);
      END_STATE();
    case 57:
      if (lookahead == 'R') ADVANCE(101);
      END_STATE();
    case 58:
      if (lookahead == 'R') ADVANCE(102);
      END_STATE();
    case 59:
      if (lookahead == 'g') ADVANCE(103);
      END_STATE();
    case 60:
      if (lookahead == 'E') ADVANCE(104);
      END_STATE();
    case 61:
      if (lookahead == 'G') ADVANCE(105);
      END_STATE();
    case 62:
      if (lookahead == 'I') ADVANCE(106);
      END_STATE();
    case 63:
      if (lookahead == 'N') ADVANCE(107);
      END_STATE();
    case 64:
      if (lookahead == 'O') ADVANCE(108);
      END_STATE();
    case 65:
      if (lookahead == 'E') ADVANCE(109);
      END_STATE();
    case 66:
      if (lookahead == 'A') ADVANCE(110);
      END_STATE();
    case 67:
      if (lookahead == 'R') ADVANCE(111);
      END_STATE();
    case 68:
      if (lookahead == 'E') ADVANCE(112);
      END_STATE();
    case 69:
      if (lookahead == 'L') ADVANCE(113);
      END_STATE();
    case 70:
      if (lookahead == 'A') ADVANCE(114);
      END_STATE();
    case 71:
      if (lookahead == 'C') ADVANCE(115);
      END_STATE();
    case 72:
      if (lookahead == 'U') ADVANCE(116);
      END_STATE();
    case 73:
      if (lookahead == 'D') ADVANCE(117);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(anon_sym_HLL);
      END_STATE();
    case 75:
      if (lookahead == 'L') ADVANCE(118);
      END_STATE();
    case 76:
      if (lookahead == 'I') ADVANCE(119);
      END_STATE();
    case 77:
      if (lookahead == 'U') ADVANCE(120);
      END_STATE();
    case 78:
      if (lookahead == 'E') ADVANCE(121);
      END_STATE();
    case 79:
      if (lookahead == 'P') ADVANCE(122);
      END_STATE();
    case 80:
      if (lookahead == 'F') ADVANCE(123);
      END_STATE();
    case 81:
      if (lookahead == 'K') ADVANCE(124);
      END_STATE();
    case 82:
      if (lookahead == 'G') ADVANCE(125);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(anon_sym_MAP);
      END_STATE();
    case 84:
      if (lookahead == 'O') ADVANCE(126);
      END_STATE();
    case 85:
      if (lookahead == 'R') ADVANCE(127);
      END_STATE();
    case 86:
      if (lookahead == 'L') ADVANCE(128);
      END_STATE();
    case 87:
      if (lookahead == 'Y') ADVANCE(129);
      END_STATE();
    case 88:
      if (lookahead == 'P') ADVANCE(130);
      END_STATE();
    case 89:
      if (lookahead == 'R') ADVANCE(131);
      END_STATE();
    case 90:
      if (lookahead == 'V') ADVANCE(132);
      END_STATE();
    case 91:
      if (lookahead == 'D') ADVANCE(133);
      END_STATE();
    case 92:
      if (lookahead == 'I') ADVANCE(134);
      END_STATE();
    case 93:
      if (lookahead == 'R') ADVANCE(135);
      END_STATE();
    case 94:
      if (lookahead == 'T') ADVANCE(136);
      END_STATE();
    case 95:
      if (lookahead == 'R') ADVANCE(137);
      END_STATE();
    case 96:
      if (lookahead == 'C') ADVANCE(138);
      END_STATE();
    case 97:
      if (lookahead == 'A') ADVANCE(139);
      END_STATE();
    case 98:
      if (lookahead == 'R') ADVANCE(140);
      END_STATE();
    case 99:
      if (lookahead == 'A') ADVANCE(141);
      END_STATE();
    case 100:
      if (lookahead == 'L') ADVANCE(142);
      END_STATE();
    case 101:
      if (lookahead == 'G') ADVANCE(143);
      END_STATE();
    case 102:
      if (lookahead == 'S') ADVANCE(144);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(anon_sym_org);
      END_STATE();
    case 104:
      if (lookahead == 'R') ADVANCE(145);
      END_STATE();
    case 105:
      if (lookahead == 'N') ADVANCE(146);
      END_STATE();
    case 106:
      if (lookahead == 'Z') ADVANCE(147);
      END_STATE();
    case 107:
      if (lookahead == 'E') ADVANCE(148);
      END_STATE();
    case 108:
      if (lookahead == 'R') ADVANCE(149);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(anon_sym_BYTE);
      END_STATE();
    case 110:
      if (lookahead == 'T') ADVANCE(150);
      END_STATE();
    case 111:
      if (lookahead == 'Y') ADVANCE(151);
      END_STATE();
    case 112:
      if (lookahead == 'R') ADVANCE(152);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(anon_sym_FILL);
      END_STATE();
    case 114:
      if (lookahead == 'T') ADVANCE(153);
      END_STATE();
    case 115:
      if (lookahead == 'E') ADVANCE(154);
      END_STATE();
    case 116:
      if (lookahead == 'P') ADVANCE(155);
      END_STATE();
    case 117:
      if (lookahead == 'E') ADVANCE(156);
      END_STATE();
    case 118:
      if (lookahead == 'U') ADVANCE(157);
      END_STATE();
    case 119:
      if (lookahead == 'B') ADVANCE(158);
      END_STATE();
    case 120:
      if (lookahead == 'T') ADVANCE(159);
      END_STATE();
    case 121:
      if (lookahead == 'R') ADVANCE(160);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(anon_sym_KEEP);
      END_STATE();
    case 123:
      if (lookahead == 'E') ADVANCE(161);
      END_STATE();
    case 124:
      if (lookahead == 'E') ADVANCE(162);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(anon_sym_LONG);
      END_STATE();
    case 126:
      if (lookahead == 'R') ADVANCE(163);
      END_STATE();
    case 127:
      if (lookahead == 'O') ADVANCE(164);
      END_STATE();
    case 128:
      if (lookahead == 'O') ADVANCE(165);
      END_STATE();
    case 129:
      if (lookahead == '_') ADVANCE(166);
      END_STATE();
    case 130:
      if (lookahead == 'U') ADVANCE(167);
      END_STATE();
    case 131:
      if (lookahead == 'S') ADVANCE(168);
      END_STATE();
    case 132:
      if (lookahead == 'I') ADVANCE(169);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(anon_sym_QUAD);
      END_STATE();
    case 134:
      if (lookahead == 'O') ADVANCE(170);
      END_STATE();
    case 135:
      if (lookahead == 'C') ADVANCE(171);
      END_STATE();
    case 136:
      if (lookahead == 'I') ADVANCE(172);
      END_STATE();
    case 137:
      if (lookahead == 'T') ADVANCE(173);
      END_STATE();
    case 138:
      if (lookahead == 'I') ADVANCE(174);
      END_STATE();
    case 139:
      if (lookahead == 'D') ADVANCE(175);
      END_STATE();
    case 140:
      if (lookahead == 'T') ADVANCE(176);
      END_STATE();
    case 141:
      if (lookahead == 'L') ADVANCE(177);
      END_STATE();
    case 142:
      if (lookahead == 'I') ADVANCE(178);
      END_STATE();
    case 143:
      if (lookahead == 'E') ADVANCE(179);
      END_STATE();
    case 144:
      if (lookahead == 'I') ADVANCE(180);
      END_STATE();
    case 145:
      ACCEPT_TOKEN(anon_sym_AFTER);
      END_STATE();
    case 146:
      if (lookahead == '_') ADVANCE(181);
      END_STATE();
    case 147:
      ACCEPT_TOKEN(anon_sym_ASCIZ);
      END_STATE();
    case 148:
      if (lookahead == 'E') ADVANCE(182);
      END_STATE();
    case 149:
      if (lookahead == 'E') ADVANCE(183);
      END_STATE();
    case 150:
      if (lookahead == 'E') ADVANCE(184);
      END_STATE();
    case 151:
      ACCEPT_TOKEN(anon_sym_ENTRY);
      END_STATE();
    case 152:
      if (lookahead == 'N') ADVANCE(185);
      END_STATE();
    case 153:
      ACCEPT_TOKEN(anon_sym_FLOAT);
      END_STATE();
    case 154:
      if (lookahead == '_') ADVANCE(186);
      END_STATE();
    case 155:
      ACCEPT_TOKEN(anon_sym_GROUP);
      END_STATE();
    case 156:
      if (lookahead == 'N') ADVANCE(187);
      END_STATE();
    case 157:
      if (lookahead == 'D') ADVANCE(188);
      END_STATE();
    case 158:
      if (lookahead == 'I') ADVANCE(189);
      END_STATE();
    case 159:
      ACCEPT_TOKEN(anon_sym_INPUT);
      if (lookahead == '_') ADVANCE(190);
      END_STATE();
    case 160:
      if (lookahead == 'T') ADVANCE(191);
      END_STATE();
    case 161:
      if (lookahead == 'A') ADVANCE(192);
      END_STATE();
    case 162:
      if (lookahead == 'R') ADVANCE(193);
      END_STATE();
    case 163:
      if (lookahead == 'Y') ADVANCE(194);
      END_STATE();
    case 164:
      if (lookahead == 'S') ADVANCE(195);
      END_STATE();
    case 165:
      if (lookahead == 'A') ADVANCE(196);
      END_STATE();
    case 166:
      if (lookahead == 'I') ADVANCE(197);
      END_STATE();
    case 167:
      if (lookahead == 'T') ADVANCE(198);
      END_STATE();
    case 168:
      ACCEPT_TOKEN(anon_sym_PHDRS);
      END_STATE();
    case 169:
      if (lookahead == 'D') ADVANCE(199);
      END_STATE();
    case 170:
      if (lookahead == 'N') ADVANCE(200);
      END_STATE();
    case 171:
      if (lookahead == 'H') ADVANCE(201);
      END_STATE();
    case 172:
      if (lookahead == 'O') ADVANCE(202);
      END_STATE();
    case 173:
      ACCEPT_TOKEN(anon_sym_SHORT);
      END_STATE();
    case 174:
      if (lookahead == 'A') ADVANCE(203);
      END_STATE();
    case 175:
      ACCEPT_TOKEN(anon_sym_SQUAD);
      END_STATE();
    case 176:
      if (lookahead == 'U') ADVANCE(204);
      END_STATE();
    case 177:
      if (lookahead == 'I') ADVANCE(205);
      END_STATE();
    case 178:
      if (lookahead == 'B') ADVANCE(206);
      END_STATE();
    case 179:
      if (lookahead == 'T') ADVANCE(207);
      END_STATE();
    case 180:
      if (lookahead == 'O') ADVANCE(208);
      END_STATE();
    case 181:
      if (lookahead == 'W') ADVANCE(209);
      END_STATE();
    case 182:
      if (lookahead == 'D') ADVANCE(210);
      END_STATE();
    case 183:
      ACCEPT_TOKEN(anon_sym_BEFORE);
      END_STATE();
    case 184:
      if (lookahead == '_') ADVANCE(211);
      END_STATE();
    case 185:
      ACCEPT_TOKEN(anon_sym_EXTERN);
      END_STATE();
    case 186:
      if (lookahead == 'C') ADVANCE(212);
      if (lookahead == 'G') ADVANCE(213);
      END_STATE();
    case 187:
      ACCEPT_TOKEN(anon_sym_HIDDEN);
      END_STATE();
    case 188:
      if (lookahead == 'E') ADVANCE(214);
      END_STATE();
    case 189:
      if (lookahead == 'T') ADVANCE(215);
      END_STATE();
    case 190:
      if (lookahead == 'S') ADVANCE(216);
      END_STATE();
    case 191:
      ACCEPT_TOKEN(anon_sym_INSERT);
      END_STATE();
    case 192:
      if (lookahead == 'T') ADVANCE(217);
      END_STATE();
    case 193:
      if (lookahead == '_') ADVANCE(218);
      END_STATE();
    case 194:
      ACCEPT_TOKEN(anon_sym_MEMORY);
      END_STATE();
    case 195:
      if (lookahead == 'S') ADVANCE(219);
      END_STATE();
    case 196:
      if (lookahead == 'T') ADVANCE(220);
      END_STATE();
    case 197:
      if (lookahead == 'F') ADVANCE(221);
      END_STATE();
    case 198:
      ACCEPT_TOKEN(anon_sym_OUTPUT);
      if (lookahead == '_') ADVANCE(222);
      END_STATE();
    case 199:
      if (lookahead == 'E') ADVANCE(223);
      END_STATE();
    case 200:
      if (lookahead == '_') ADVANCE(224);
      END_STATE();
    case 201:
      if (lookahead == '_') ADVANCE(225);
      END_STATE();
    case 202:
      if (lookahead == 'N') ADVANCE(226);
      END_STATE();
    case 203:
      if (lookahead == 'L') ADVANCE(227);
      END_STATE();
    case 204:
      if (lookahead == 'P') ADVANCE(228);
      END_STATE();
    case 205:
      if (lookahead == 'G') ADVANCE(229);
      END_STATE();
    case 206:
      ACCEPT_TOKEN(anon_sym_SYSLIB);
      END_STATE();
    case 207:
      ACCEPT_TOKEN(anon_sym_TARGET);
      END_STATE();
    case 208:
      if (lookahead == 'N') ADVANCE(230);
      END_STATE();
    case 209:
      if (lookahead == 'I') ADVANCE(231);
      END_STATE();
    case 210:
      if (lookahead == 'E') ADVANCE(232);
      END_STATE();
    case 211:
      if (lookahead == 'O') ADVANCE(233);
      END_STATE();
    case 212:
      if (lookahead == 'O') ADVANCE(234);
      END_STATE();
    case 213:
      if (lookahead == 'R') ADVANCE(235);
      END_STATE();
    case 214:
      ACCEPT_TOKEN(anon_sym_INCLUDE);
      END_STATE();
    case 215:
      if (lookahead == '_') ADVANCE(236);
      END_STATE();
    case 216:
      if (lookahead == 'E') ADVANCE(237);
      END_STATE();
    case 217:
      if (lookahead == 'U') ADVANCE(238);
      END_STATE();
    case 218:
      if (lookahead == 'V') ADVANCE(239);
      END_STATE();
    case 219:
      if (lookahead == 'R') ADVANCE(240);
      END_STATE();
    case 220:
      ACCEPT_TOKEN(anon_sym_NOFLOAT);
      END_STATE();
    case 221:
      if (lookahead == '_') ADVANCE(241);
      END_STATE();
    case 222:
      if (lookahead == 'A') ADVANCE(242);
      if (lookahead == 'F') ADVANCE(243);
      END_STATE();
    case 223:
      ACCEPT_TOKEN(anon_sym_PROVIDE);
      if (lookahead == '_') ADVANCE(244);
      END_STATE();
    case 224:
      if (lookahead == 'A') ADVANCE(245);
      END_STATE();
    case 225:
      if (lookahead == 'D') ADVANCE(246);
      END_STATE();
    case 226:
      if (lookahead == 'S') ADVANCE(247);
      END_STATE();
    case 227:
      ACCEPT_TOKEN(anon_sym_SPECIAL);
      END_STATE();
    case 228:
      ACCEPT_TOKEN(anon_sym_STARTUP);
      END_STATE();
    case 229:
      if (lookahead == 'N') ADVANCE(248);
      END_STATE();
    case 230:
      ACCEPT_TOKEN(anon_sym_VERSION);
      END_STATE();
    case 231:
      if (lookahead == 'T') ADVANCE(249);
      END_STATE();
    case 232:
      if (lookahead == 'D') ADVANCE(250);
      END_STATE();
    case 233:
      if (lookahead == 'B') ADVANCE(251);
      END_STATE();
    case 234:
      if (lookahead == 'M') ADVANCE(252);
      END_STATE();
    case 235:
      if (lookahead == 'O') ADVANCE(253);
      END_STATE();
    case 236:
      if (lookahead == 'C') ADVANCE(254);
      END_STATE();
    case 237:
      if (lookahead == 'C') ADVANCE(255);
      END_STATE();
    case 238:
      if (lookahead == 'R') ADVANCE(256);
      END_STATE();
    case 239:
      if (lookahead == 'E') ADVANCE(257);
      END_STATE();
    case 240:
      if (lookahead == 'E') ADVANCE(258);
      END_STATE();
    case 241:
      if (lookahead == 'R') ADVANCE(259);
      END_STATE();
    case 242:
      if (lookahead == 'R') ADVANCE(260);
      END_STATE();
    case 243:
      if (lookahead == 'O') ADVANCE(261);
      END_STATE();
    case 244:
      if (lookahead == 'H') ADVANCE(262);
      END_STATE();
    case 245:
      if (lookahead == 'L') ADVANCE(263);
      END_STATE();
    case 246:
      if (lookahead == 'I') ADVANCE(264);
      END_STATE();
    case 247:
      ACCEPT_TOKEN(anon_sym_SECTIONS);
      END_STATE();
    case 248:
      ACCEPT_TOKEN(anon_sym_SUBALIGN);
      END_STATE();
    case 249:
      if (lookahead == 'H') ADVANCE(265);
      END_STATE();
    case 250:
      ACCEPT_TOKEN(anon_sym_AS_NEEDED);
      END_STATE();
    case 251:
      if (lookahead == 'J') ADVANCE(266);
      END_STATE();
    case 252:
      if (lookahead == 'M') ADVANCE(267);
      END_STATE();
    case 253:
      if (lookahead == 'U') ADVANCE(268);
      END_STATE();
    case 254:
      if (lookahead == 'O') ADVANCE(269);
      END_STATE();
    case 255:
      if (lookahead == 'T') ADVANCE(270);
      END_STATE();
    case 256:
      if (lookahead == 'E') ADVANCE(271);
      END_STATE();
    case 257:
      if (lookahead == 'R') ADVANCE(272);
      END_STATE();
    case 258:
      if (lookahead == 'F') ADVANCE(273);
      END_STATE();
    case 259:
      if (lookahead == 'O') ADVANCE(274);
      if (lookahead == 'W') ADVANCE(275);
      END_STATE();
    case 260:
      if (lookahead == 'C') ADVANCE(276);
      END_STATE();
    case 261:
      if (lookahead == 'R') ADVANCE(277);
      END_STATE();
    case 262:
      if (lookahead == 'I') ADVANCE(278);
      END_STATE();
    case 263:
      if (lookahead == 'I') ADVANCE(279);
      END_STATE();
    case 264:
      if (lookahead == 'R') ADVANCE(280);
      END_STATE();
    case 265:
      if (lookahead == '_') ADVANCE(281);
      END_STATE();
    case 266:
      if (lookahead == 'E') ADVANCE(282);
      END_STATE();
    case 267:
      if (lookahead == 'O') ADVANCE(283);
      END_STATE();
    case 268:
      if (lookahead == 'P') ADVANCE(284);
      END_STATE();
    case 269:
      if (lookahead == 'M') ADVANCE(285);
      END_STATE();
    case 270:
      if (lookahead == 'I') ADVANCE(286);
      END_STATE();
    case 271:
      ACCEPT_TOKEN(anon_sym_LD_FEATURE);
      END_STATE();
    case 272:
      if (lookahead == 'S') ADVANCE(287);
      END_STATE();
    case 273:
      if (lookahead == 'S') ADVANCE(288);
      END_STATE();
    case 274:
      ACCEPT_TOKEN(anon_sym_ONLY_IF_RO);
      END_STATE();
    case 275:
      ACCEPT_TOKEN(anon_sym_ONLY_IF_RW);
      END_STATE();
    case 276:
      if (lookahead == 'H') ADVANCE(289);
      END_STATE();
    case 277:
      if (lookahead == 'M') ADVANCE(290);
      END_STATE();
    case 278:
      if (lookahead == 'D') ADVANCE(291);
      END_STATE();
    case 279:
      if (lookahead == 'A') ADVANCE(292);
      END_STATE();
    case 280:
      ACCEPT_TOKEN(anon_sym_SEARCH_DIR);
      END_STATE();
    case 281:
      if (lookahead == 'I') ADVANCE(293);
      END_STATE();
    case 282:
      if (lookahead == 'C') ADVANCE(294);
      END_STATE();
    case 283:
      if (lookahead == 'N') ADVANCE(295);
      END_STATE();
    case 284:
      if (lookahead == '_') ADVANCE(296);
      END_STATE();
    case 285:
      if (lookahead == 'M') ADVANCE(297);
      END_STATE();
    case 286:
      if (lookahead == 'O') ADVANCE(298);
      END_STATE();
    case 287:
      if (lookahead == 'I') ADVANCE(299);
      END_STATE();
    case 288:
      ACCEPT_TOKEN(anon_sym_NOCROSSREFS);
      if (lookahead == '_') ADVANCE(300);
      END_STATE();
    case 289:
      ACCEPT_TOKEN(anon_sym_OUTPUT_ARCH);
      END_STATE();
    case 290:
      if (lookahead == 'A') ADVANCE(301);
      END_STATE();
    case 291:
      if (lookahead == 'D') ADVANCE(302);
      END_STATE();
    case 292:
      if (lookahead == 'S') ADVANCE(303);
      END_STATE();
    case 293:
      if (lookahead == 'N') ADVANCE(304);
      END_STATE();
    case 294:
      if (lookahead == 'T') ADVANCE(305);
      END_STATE();
    case 295:
      if (lookahead == '_') ADVANCE(306);
      END_STATE();
    case 296:
      if (lookahead == 'A') ADVANCE(307);
      END_STATE();
    case 297:
      if (lookahead == 'O') ADVANCE(308);
      END_STATE();
    case 298:
      if (lookahead == 'N') ADVANCE(309);
      END_STATE();
    case 299:
      if (lookahead == 'O') ADVANCE(310);
      END_STATE();
    case 300:
      if (lookahead == 'T') ADVANCE(311);
      END_STATE();
    case 301:
      if (lookahead == 'T') ADVANCE(312);
      END_STATE();
    case 302:
      if (lookahead == 'E') ADVANCE(313);
      END_STATE();
    case 303:
      ACCEPT_TOKEN(anon_sym_REGION_ALIAS);
      END_STATE();
    case 304:
      if (lookahead == 'P') ADVANCE(314);
      END_STATE();
    case 305:
      if (lookahead == '_') ADVANCE(315);
      END_STATE();
    case 306:
      if (lookahead == 'A') ADVANCE(316);
      END_STATE();
    case 307:
      if (lookahead == 'L') ADVANCE(317);
      END_STATE();
    case 308:
      if (lookahead == 'N') ADVANCE(318);
      END_STATE();
    case 309:
      if (lookahead == '_') ADVANCE(319);
      END_STATE();
    case 310:
      if (lookahead == 'N') ADVANCE(320);
      END_STATE();
    case 311:
      if (lookahead == 'O') ADVANCE(321);
      END_STATE();
    case 312:
      ACCEPT_TOKEN(anon_sym_OUTPUT_FORMAT);
      END_STATE();
    case 313:
      if (lookahead == 'N') ADVANCE(322);
      END_STATE();
    case 314:
      if (lookahead == 'U') ADVANCE(323);
      END_STATE();
    case 315:
      if (lookahead == 'S') ADVANCE(324);
      END_STATE();
    case 316:
      if (lookahead == 'L') ADVANCE(325);
      END_STATE();
    case 317:
      if (lookahead == 'L') ADVANCE(326);
      END_STATE();
    case 318:
      if (lookahead == '_') ADVANCE(327);
      END_STATE();
    case 319:
      if (lookahead == 'F') ADVANCE(328);
      END_STATE();
    case 320:
      ACCEPT_TOKEN(anon_sym_LINKER_VERSION);
      END_STATE();
    case 321:
      ACCEPT_TOKEN(anon_sym_NOCROSSREFS_TO);
      END_STATE();
    case 322:
      ACCEPT_TOKEN(anon_sym_PROVIDE_HIDDEN);
      END_STATE();
    case 323:
      if (lookahead == 'T') ADVANCE(329);
      END_STATE();
    case 324:
      if (lookahead == 'Y') ADVANCE(330);
      END_STATE();
    case 325:
      if (lookahead == 'L') ADVANCE(331);
      END_STATE();
    case 326:
      if (lookahead == 'O') ADVANCE(332);
      END_STATE();
    case 327:
      if (lookahead == 'A') ADVANCE(333);
      END_STATE();
    case 328:
      if (lookahead == 'L') ADVANCE(334);
      END_STATE();
    case 329:
      ACCEPT_TOKEN(anon_sym_ALIGN_WITH_INPUT);
      END_STATE();
    case 330:
      if (lookahead == 'M') ADVANCE(335);
      END_STATE();
    case 331:
      if (lookahead == 'O') ADVANCE(336);
      END_STATE();
    case 332:
      if (lookahead == 'C') ADVANCE(337);
      END_STATE();
    case 333:
      if (lookahead == 'L') ADVANCE(338);
      END_STATE();
    case 334:
      if (lookahead == 'A') ADVANCE(339);
      END_STATE();
    case 335:
      if (lookahead == 'B') ADVANCE(340);
      END_STATE();
    case 336:
      if (lookahead == 'C') ADVANCE(341);
      END_STATE();
    case 337:
      if (lookahead == 'A') ADVANCE(342);
      END_STATE();
    case 338:
      if (lookahead == 'L') ADVANCE(343);
      END_STATE();
    case 339:
      if (lookahead == 'G') ADVANCE(344);
      END_STATE();
    case 340:
      if (lookahead == 'O') ADVANCE(345);
      END_STATE();
    case 341:
      if (lookahead == 'A') ADVANCE(346);
      END_STATE();
    case 342:
      if (lookahead == 'T') ADVANCE(347);
      END_STATE();
    case 343:
      if (lookahead == 'O') ADVANCE(348);
      END_STATE();
    case 344:
      if (lookahead == 'S') ADVANCE(349);
      END_STATE();
    case 345:
      if (lookahead == 'L') ADVANCE(350);
      END_STATE();
    case 346:
      if (lookahead == 'T') ADVANCE(351);
      END_STATE();
    case 347:
      if (lookahead == 'I') ADVANCE(352);
      END_STATE();
    case 348:
      if (lookahead == 'C') ADVANCE(353);
      END_STATE();
    case 349:
      ACCEPT_TOKEN(anon_sym_INPUT_SECTION_FLAGS);
      END_STATE();
    case 350:
      if (lookahead == 'S') ADVANCE(354);
      END_STATE();
    case 351:
      if (lookahead == 'I') ADVANCE(355);
      END_STATE();
    case 352:
      if (lookahead == 'O') ADVANCE(356);
      END_STATE();
    case 353:
      if (lookahead == 'A') ADVANCE(357);
      END_STATE();
    case 354:
      ACCEPT_TOKEN(anon_sym_CREATE_OBJECT_SYMBOLS);
      END_STATE();
    case 355:
      if (lookahead == 'O') ADVANCE(358);
      END_STATE();
    case 356:
      if (lookahead == 'N') ADVANCE(359);
      END_STATE();
    case 357:
      if (lookahead == 'T') ADVANCE(360);
      END_STATE();
    case 358:
      if (lookahead == 'N') ADVANCE(361);
      END_STATE();
    case 359:
      ACCEPT_TOKEN(anon_sym_FORCE_GROUP_ALLOCATION);
      END_STATE();
    case 360:
      if (lookahead == 'I') ADVANCE(362);
      END_STATE();
    case 361:
      ACCEPT_TOKEN(anon_sym_FORCE_COMMON_ALLOCATION);
      END_STATE();
    case 362:
      if (lookahead == 'O') ADVANCE(363);
      END_STATE();
    case 363:
      if (lookahead == 'N') ADVANCE(364);
      END_STATE();
    case 364:
      ACCEPT_TOKEN(anon_sym_INHIBIT_COMMON_ALLOCATION);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 98},
  [2] = {.lex_state = 2},
  [3] = {.lex_state = 98},
  [4] = {.lex_state = 98},
  [5] = {.lex_state = 3},
  [6] = {.lex_state = 12},
  [7] = {.lex_state = 12},
  [8] = {.lex_state = 12},
  [9] = {.lex_state = 12},
  [10] = {.lex_state = 12},
  [11] = {.lex_state = 12},
  [12] = {.lex_state = 8},
  [13] = {.lex_state = 12},
  [14] = {.lex_state = 12},
  [15] = {.lex_state = 12},
  [16] = {.lex_state = 98},
  [17] = {.lex_state = 2},
  [18] = {.lex_state = 98},
  [19] = {.lex_state = 98},
  [20] = {.lex_state = 98},
  [21] = {.lex_state = 98},
  [22] = {.lex_state = 98},
  [23] = {.lex_state = 98},
  [24] = {.lex_state = 98},
  [25] = {.lex_state = 98},
  [26] = {.lex_state = 98},
  [27] = {.lex_state = 98},
  [28] = {.lex_state = 98},
  [29] = {.lex_state = 98},
  [30] = {.lex_state = 98},
  [31] = {.lex_state = 98},
  [32] = {.lex_state = 98},
  [33] = {.lex_state = 98},
  [34] = {.lex_state = 98},
  [35] = {.lex_state = 98},
  [36] = {.lex_state = 98},
  [37] = {.lex_state = 98},
  [38] = {.lex_state = 98},
  [39] = {.lex_state = 98},
  [40] = {.lex_state = 98},
  [41] = {.lex_state = 4},
  [42] = {.lex_state = 4},
  [43] = {.lex_state = 4},
  [44] = {.lex_state = 4},
  [45] = {.lex_state = 4},
  [46] = {.lex_state = 4},
  [47] = {.lex_state = 4},
  [48] = {.lex_state = 4},
  [49] = {.lex_state = 4},
  [50] = {.lex_state = 4},
  [51] = {.lex_state = 4},
  [52] = {.lex_state = 4},
  [53] = {.lex_state = 4},
  [54] = {.lex_state = 4},
  [55] = {.lex_state = 4},
  [56] = {.lex_state = 4},
  [57] = {.lex_state = 4},
  [58] = {.lex_state = 4},
  [59] = {.lex_state = 4},
  [60] = {.lex_state = 4},
  [61] = {.lex_state = 4},
  [62] = {.lex_state = 4},
  [63] = {.lex_state = 4},
  [64] = {.lex_state = 4},
  [65] = {.lex_state = 4},
  [66] = {.lex_state = 4},
  [67] = {.lex_state = 4},
  [68] = {.lex_state = 4},
  [69] = {.lex_state = 4},
  [70] = {.lex_state = 4},
  [71] = {.lex_state = 4},
  [72] = {.lex_state = 4},
  [73] = {.lex_state = 4},
  [74] = {.lex_state = 4},
  [75] = {.lex_state = 4},
  [76] = {.lex_state = 4},
  [77] = {.lex_state = 4},
  [78] = {.lex_state = 4},
  [79] = {.lex_state = 4},
  [80] = {.lex_state = 4},
  [81] = {.lex_state = 4},
  [82] = {.lex_state = 4},
  [83] = {.lex_state = 4},
  [84] = {.lex_state = 4},
  [85] = {.lex_state = 4},
  [86] = {.lex_state = 4},
  [87] = {.lex_state = 4},
  [88] = {.lex_state = 4},
  [89] = {.lex_state = 4},
  [90] = {.lex_state = 4},
  [91] = {.lex_state = 4},
  [92] = {.lex_state = 4},
  [93] = {.lex_state = 4},
  [94] = {.lex_state = 4},
  [95] = {.lex_state = 4},
  [96] = {.lex_state = 4},
  [97] = {.lex_state = 4},
  [98] = {.lex_state = 4},
  [99] = {.lex_state = 4},
  [100] = {.lex_state = 4},
  [101] = {.lex_state = 4},
  [102] = {.lex_state = 4},
  [103] = {.lex_state = 4},
  [104] = {.lex_state = 4},
  [105] = {.lex_state = 6},
  [106] = {.lex_state = 6},
  [107] = {.lex_state = 6},
  [108] = {.lex_state = 6},
  [109] = {.lex_state = 6},
  [110] = {.lex_state = 6},
  [111] = {.lex_state = 6},
  [112] = {.lex_state = 6},
  [113] = {.lex_state = 6},
  [114] = {.lex_state = 6},
  [115] = {.lex_state = 6},
  [116] = {.lex_state = 7},
  [117] = {.lex_state = 12},
  [118] = {.lex_state = 12},
  [119] = {.lex_state = 7},
  [120] = {.lex_state = 12},
  [121] = {.lex_state = 7},
  [122] = {.lex_state = 12},
  [123] = {.lex_state = 7},
  [124] = {.lex_state = 7},
  [125] = {.lex_state = 12},
  [126] = {.lex_state = 7},
  [127] = {.lex_state = 12},
  [128] = {.lex_state = 7},
  [129] = {.lex_state = 12},
  [130] = {.lex_state = 12},
  [131] = {.lex_state = 12},
  [132] = {.lex_state = 7},
  [133] = {.lex_state = 7},
  [134] = {.lex_state = 12},
  [135] = {.lex_state = 7},
  [136] = {.lex_state = 12},
  [137] = {.lex_state = 12},
  [138] = {.lex_state = 5},
  [139] = {.lex_state = 5},
  [140] = {.lex_state = 5},
  [141] = {.lex_state = 5},
  [142] = {.lex_state = 5},
  [143] = {.lex_state = 5},
  [144] = {.lex_state = 5},
  [145] = {.lex_state = 5},
  [146] = {.lex_state = 5},
  [147] = {.lex_state = 5},
  [148] = {.lex_state = 7},
  [149] = {.lex_state = 5},
  [150] = {.lex_state = 5},
  [151] = {.lex_state = 7},
  [152] = {.lex_state = 7},
  [153] = {.lex_state = 7},
  [154] = {.lex_state = 7},
  [155] = {.lex_state = 7},
  [156] = {.lex_state = 7},
  [157] = {.lex_state = 7},
  [158] = {.lex_state = 7},
  [159] = {.lex_state = 7},
  [160] = {.lex_state = 7},
  [161] = {.lex_state = 7},
  [162] = {.lex_state = 7},
  [163] = {.lex_state = 7},
  [164] = {.lex_state = 7},
  [165] = {.lex_state = 7},
  [166] = {.lex_state = 7},
  [167] = {.lex_state = 7},
  [168] = {.lex_state = 7},
  [169] = {.lex_state = 7},
  [170] = {.lex_state = 7},
  [171] = {.lex_state = 7},
  [172] = {.lex_state = 7},
  [173] = {.lex_state = 7},
  [174] = {.lex_state = 7},
  [175] = {.lex_state = 7},
  [176] = {.lex_state = 7},
  [177] = {.lex_state = 7},
  [178] = {.lex_state = 7},
  [179] = {.lex_state = 7},
  [180] = {.lex_state = 7},
  [181] = {.lex_state = 7},
  [182] = {.lex_state = 7},
  [183] = {.lex_state = 7},
  [184] = {.lex_state = 7},
  [185] = {.lex_state = 7},
  [186] = {.lex_state = 9},
  [187] = {.lex_state = 9},
  [188] = {.lex_state = 9},
  [189] = {.lex_state = 9},
  [190] = {.lex_state = 9},
  [191] = {.lex_state = 9},
  [192] = {.lex_state = 9},
  [193] = {.lex_state = 9},
  [194] = {.lex_state = 9},
  [195] = {.lex_state = 9},
  [196] = {.lex_state = 9},
  [197] = {.lex_state = 9},
  [198] = {.lex_state = 9},
  [199] = {.lex_state = 9},
  [200] = {.lex_state = 9},
  [201] = {.lex_state = 9},
  [202] = {.lex_state = 9},
  [203] = {.lex_state = 9},
  [204] = {.lex_state = 9},
  [205] = {.lex_state = 9},
  [206] = {.lex_state = 23},
  [207] = {.lex_state = 9},
  [208] = {.lex_state = 9},
  [209] = {.lex_state = 9},
  [210] = {.lex_state = 9},
  [211] = {.lex_state = 9},
  [212] = {.lex_state = 9},
  [213] = {.lex_state = 9},
  [214] = {.lex_state = 23},
  [215] = {.lex_state = 13},
  [216] = {.lex_state = 23},
  [217] = {.lex_state = 17},
  [218] = {.lex_state = 17},
  [219] = {.lex_state = 17},
  [220] = {.lex_state = 9},
  [221] = {.lex_state = 9},
  [222] = {.lex_state = 9},
  [223] = {.lex_state = 9},
  [224] = {.lex_state = 9},
  [225] = {.lex_state = 9},
  [226] = {.lex_state = 9},
  [227] = {.lex_state = 9},
  [228] = {.lex_state = 9},
  [229] = {.lex_state = 9},
  [230] = {.lex_state = 9},
  [231] = {.lex_state = 9},
  [232] = {.lex_state = 27},
  [233] = {.lex_state = 10},
  [234] = {.lex_state = 27},
  [235] = {.lex_state = 9},
  [236] = {.lex_state = 27},
  [237] = {.lex_state = 27},
  [238] = {.lex_state = 27},
  [239] = {.lex_state = 27},
  [240] = {.lex_state = 27},
  [241] = {.lex_state = 27},
  [242] = {.lex_state = 27},
  [243] = {.lex_state = 9},
  [244] = {.lex_state = 9},
  [245] = {.lex_state = 9},
  [246] = {.lex_state = 2},
  [247] = {.lex_state = 9},
  [248] = {.lex_state = 13},
  [249] = {.lex_state = 13},
  [250] = {.lex_state = 9},
  [251] = {.lex_state = 9},
  [252] = {.lex_state = 9},
  [253] = {.lex_state = 9},
  [254] = {.lex_state = 27},
  [255] = {.lex_state = 9},
  [256] = {.lex_state = 9},
  [257] = {.lex_state = 9},
  [258] = {.lex_state = 9},
  [259] = {.lex_state = 9},
  [260] = {.lex_state = 9},
  [261] = {.lex_state = 9},
  [262] = {.lex_state = 9},
  [263] = {.lex_state = 23},
  [264] = {.lex_state = 23},
  [265] = {.lex_state = 23},
  [266] = {.lex_state = 9},
  [267] = {.lex_state = 10},
  [268] = {.lex_state = 9},
  [269] = {.lex_state = 23},
  [270] = {.lex_state = 17},
  [271] = {.lex_state = 9},
  [272] = {.lex_state = 9},
  [273] = {.lex_state = 9},
  [274] = {.lex_state = 9},
  [275] = {.lex_state = 23},
  [276] = {.lex_state = 23},
  [277] = {.lex_state = 17},
  [278] = {.lex_state = 9},
  [279] = {.lex_state = 23},
  [280] = {.lex_state = 9},
  [281] = {.lex_state = 17},
  [282] = {.lex_state = 17},
  [283] = {.lex_state = 9},
  [284] = {.lex_state = 9},
  [285] = {.lex_state = 17},
  [286] = {.lex_state = 9},
  [287] = {.lex_state = 9},
  [288] = {.lex_state = 17},
  [289] = {.lex_state = 23},
  [290] = {.lex_state = 17},
  [291] = {.lex_state = 17},
  [292] = {.lex_state = 9},
  [293] = {.lex_state = 7},
  [294] = {.lex_state = 10},
  [295] = {.lex_state = 10},
  [296] = {.lex_state = 10},
  [297] = {.lex_state = 10},
  [298] = {.lex_state = 10},
  [299] = {.lex_state = 10},
  [300] = {.lex_state = 28},
  [301] = {.lex_state = 1},
  [302] = {.lex_state = 1},
  [303] = {.lex_state = 10},
  [304] = {.lex_state = 13},
  [305] = {.lex_state = 28},
  [306] = {.lex_state = 34},
  [307] = {.lex_state = 1},
  [308] = {.lex_state = 1},
  [309] = {.lex_state = 1},
  [310] = {.lex_state = 10},
  [311] = {.lex_state = 34},
  [312] = {.lex_state = 26},
  [313] = {.lex_state = 30},
  [314] = {.lex_state = 30},
  [315] = {.lex_state = 1},
  [316] = {.lex_state = 1},
  [317] = {.lex_state = 1},
  [318] = {.lex_state = 1},
  [319] = {.lex_state = 1},
  [320] = {.lex_state = 1},
  [321] = {.lex_state = 1},
  [322] = {.lex_state = 1},
  [323] = {.lex_state = 1},
  [324] = {.lex_state = 1},
  [325] = {.lex_state = 1},
  [326] = {.lex_state = 1},
  [327] = {.lex_state = 1},
  [328] = {.lex_state = 1},
  [329] = {.lex_state = 1},
  [330] = {.lex_state = 33},
  [331] = {.lex_state = 31},
  [332] = {.lex_state = 1},
  [333] = {.lex_state = 1},
  [334] = {.lex_state = 1},
  [335] = {.lex_state = 1},
  [336] = {.lex_state = 1},
  [337] = {.lex_state = 1},
  [338] = {.lex_state = 33},
  [339] = {.lex_state = 34},
  [340] = {.lex_state = 34},
  [341] = {.lex_state = 1},
  [342] = {.lex_state = 34},
  [343] = {.lex_state = 1},
  [344] = {.lex_state = 1},
  [345] = {.lex_state = 1},
  [346] = {.lex_state = 29},
  [347] = {.lex_state = 1},
  [348] = {.lex_state = 7},
  [349] = {.lex_state = 1},
  [350] = {.lex_state = 33},
  [351] = {.lex_state = 34},
  [352] = {.lex_state = 29},
  [353] = {.lex_state = 1},
  [354] = {.lex_state = 29},
  [355] = {.lex_state = 34},
  [356] = {.lex_state = 1},
  [357] = {.lex_state = 34},
  [358] = {.lex_state = 34},
  [359] = {.lex_state = 7},
  [360] = {.lex_state = 29},
  [361] = {.lex_state = 34},
  [362] = {.lex_state = 1},
  [363] = {.lex_state = 1},
  [364] = {.lex_state = 1},
  [365] = {.lex_state = 1},
  [366] = {.lex_state = 1},
  [367] = {.lex_state = 1},
  [368] = {.lex_state = 34},
  [369] = {.lex_state = 1},
  [370] = {.lex_state = 1},
  [371] = {.lex_state = 29},
  [372] = {.lex_state = 34},
  [373] = {.lex_state = 1},
  [374] = {.lex_state = 1},
  [375] = {.lex_state = 34},
  [376] = {.lex_state = 1},
  [377] = {.lex_state = 1},
  [378] = {.lex_state = 1},
  [379] = {.lex_state = 7},
  [380] = {.lex_state = 1},
  [381] = {.lex_state = 7},
  [382] = {.lex_state = 1},
  [383] = {.lex_state = 1},
  [384] = {.lex_state = 1},
  [385] = {.lex_state = 1},
  [386] = {.lex_state = 11},
  [387] = {.lex_state = 1},
  [388] = {.lex_state = 1},
  [389] = {.lex_state = 1},
  [390] = {.lex_state = 33},
  [391] = {.lex_state = 11},
  [392] = {.lex_state = 1},
  [393] = {.lex_state = 1},
  [394] = {.lex_state = 1},
  [395] = {.lex_state = 1},
  [396] = {.lex_state = 1},
  [397] = {.lex_state = 1},
  [398] = {.lex_state = 1},
  [399] = {.lex_state = 7},
  [400] = {.lex_state = 1},
  [401] = {.lex_state = 1},
  [402] = {.lex_state = 1},
  [403] = {.lex_state = 1},
  [404] = {.lex_state = 1},
  [405] = {.lex_state = 1},
  [406] = {.lex_state = 7},
  [407] = {.lex_state = 1},
  [408] = {.lex_state = 1},
  [409] = {.lex_state = 1},
  [410] = {.lex_state = 1},
  [411] = {.lex_state = 33},
  [412] = {.lex_state = 0},
  [413] = {.lex_state = 33},
  [414] = {.lex_state = 0},
  [415] = {.lex_state = 1},
  [416] = {.lex_state = 1},
  [417] = {.lex_state = 1},
  [418] = {.lex_state = 0},
  [419] = {.lex_state = 0},
  [420] = {.lex_state = 33},
  [421] = {.lex_state = 1},
  [422] = {.lex_state = 18},
  [423] = {.lex_state = 32},
  [424] = {.lex_state = 33},
  [425] = {.lex_state = 1},
  [426] = {.lex_state = 18},
  [427] = {.lex_state = 0},
  [428] = {.lex_state = 1},
  [429] = {.lex_state = 0},
  [430] = {.lex_state = 1},
  [431] = {.lex_state = 32},
  [432] = {.lex_state = 1},
  [433] = {.lex_state = 1},
  [434] = {.lex_state = 33},
  [435] = {.lex_state = 0},
  [436] = {.lex_state = 1},
  [437] = {.lex_state = 1},
  [438] = {.lex_state = 0},
  [439] = {.lex_state = 18},
  [440] = {.lex_state = 0},
  [441] = {.lex_state = 1},
  [442] = {.lex_state = 0},
  [443] = {.lex_state = 1},
  [444] = {.lex_state = 1},
  [445] = {.lex_state = 1},
  [446] = {.lex_state = 1},
  [447] = {.lex_state = 1},
  [448] = {.lex_state = 18},
  [449] = {.lex_state = 33},
  [450] = {.lex_state = 1},
  [451] = {.lex_state = 1},
  [452] = {.lex_state = 1},
  [453] = {.lex_state = 32},
  [454] = {.lex_state = 0},
  [455] = {.lex_state = 1},
  [456] = {.lex_state = 18},
  [457] = {.lex_state = 0},
  [458] = {.lex_state = 33},
  [459] = {.lex_state = 32},
  [460] = {.lex_state = 1},
  [461] = {.lex_state = 0},
  [462] = {.lex_state = 0},
  [463] = {.lex_state = 1},
  [464] = {.lex_state = 0},
  [465] = {.lex_state = 0},
  [466] = {.lex_state = 0},
  [467] = {.lex_state = 1},
  [468] = {.lex_state = 1},
  [469] = {.lex_state = 1},
  [470] = {.lex_state = 0},
  [471] = {.lex_state = 0},
  [472] = {.lex_state = 0},
  [473] = {.lex_state = 0},
  [474] = {.lex_state = 0},
  [475] = {.lex_state = 0},
  [476] = {.lex_state = 0},
  [477] = {.lex_state = 1},
  [478] = {.lex_state = 0},
  [479] = {.lex_state = 0},
  [480] = {.lex_state = 0},
  [481] = {.lex_state = 1},
  [482] = {.lex_state = 18},
  [483] = {.lex_state = 1},
  [484] = {.lex_state = 0},
  [485] = {.lex_state = 0},
  [486] = {.lex_state = 1},
  [487] = {.lex_state = 0},
  [488] = {.lex_state = 1},
  [489] = {.lex_state = 1},
  [490] = {.lex_state = 1},
  [491] = {.lex_state = 0},
  [492] = {.lex_state = 0},
  [493] = {.lex_state = 1},
  [494] = {.lex_state = 1},
  [495] = {.lex_state = 1},
  [496] = {.lex_state = 1},
  [497] = {.lex_state = 0},
  [498] = {.lex_state = 0},
  [499] = {.lex_state = 1},
  [500] = {.lex_state = 0},
  [501] = {.lex_state = 1},
  [502] = {.lex_state = 1},
  [503] = {.lex_state = 0},
  [504] = {.lex_state = 0},
  [505] = {.lex_state = 0},
  [506] = {.lex_state = 0},
  [507] = {.lex_state = 0},
  [508] = {.lex_state = 1},
  [509] = {.lex_state = 1},
  [510] = {.lex_state = 0},
  [511] = {.lex_state = 0},
  [512] = {.lex_state = 18},
  [513] = {.lex_state = 0},
  [514] = {.lex_state = 0},
  [515] = {.lex_state = 0},
  [516] = {.lex_state = 0},
  [517] = {.lex_state = 0},
  [518] = {.lex_state = 18},
  [519] = {.lex_state = 0},
  [520] = {.lex_state = 0},
  [521] = {.lex_state = 0},
  [522] = {.lex_state = 0},
  [523] = {.lex_state = 0},
  [524] = {.lex_state = 0},
  [525] = {.lex_state = 0},
  [526] = {.lex_state = 0},
  [527] = {.lex_state = 0},
  [528] = {.lex_state = 0},
  [529] = {.lex_state = 0},
  [530] = {.lex_state = 0},
  [531] = {.lex_state = 0},
  [532] = {.lex_state = 0},
  [533] = {.lex_state = 0},
  [534] = {.lex_state = 0},
  [535] = {.lex_state = 0},
  [536] = {.lex_state = 0},
  [537] = {.lex_state = 0},
  [538] = {.lex_state = 1},
  [539] = {.lex_state = 16},
  [540] = {.lex_state = 16},
  [541] = {.lex_state = 0},
  [542] = {.lex_state = 2},
  [543] = {.lex_state = 0},
  [544] = {.lex_state = 0},
  [545] = {.lex_state = 0},
  [546] = {.lex_state = 0},
  [547] = {.lex_state = 0},
  [548] = {.lex_state = 0},
  [549] = {.lex_state = 0},
  [550] = {.lex_state = 0},
  [551] = {.lex_state = 0},
  [552] = {.lex_state = 0},
  [553] = {.lex_state = 0},
  [554] = {.lex_state = 0},
  [555] = {.lex_state = 0},
  [556] = {.lex_state = 1},
  [557] = {.lex_state = 0},
  [558] = {.lex_state = 1},
  [559] = {.lex_state = 1},
  [560] = {.lex_state = 1},
  [561] = {.lex_state = 0},
  [562] = {.lex_state = 0},
  [563] = {.lex_state = 0},
  [564] = {.lex_state = 0},
  [565] = {.lex_state = 0},
  [566] = {.lex_state = 0},
  [567] = {.lex_state = 0},
  [568] = {.lex_state = 1},
  [569] = {.lex_state = 0},
  [570] = {.lex_state = 0},
  [571] = {.lex_state = 0},
  [572] = {.lex_state = 2},
  [573] = {.lex_state = 0},
  [574] = {.lex_state = 0},
  [575] = {.lex_state = 0},
  [576] = {.lex_state = 0},
  [577] = {.lex_state = 0},
  [578] = {.lex_state = 0},
  [579] = {.lex_state = 0},
  [580] = {.lex_state = 0},
  [581] = {.lex_state = 0},
  [582] = {.lex_state = 0},
  [583] = {.lex_state = 0},
  [584] = {.lex_state = 0},
  [585] = {.lex_state = 0},
  [586] = {.lex_state = 0},
  [587] = {.lex_state = 0},
  [588] = {.lex_state = 1},
  [589] = {.lex_state = 0},
  [590] = {.lex_state = 0},
  [591] = {.lex_state = 0},
  [592] = {.lex_state = 0},
  [593] = {.lex_state = 0},
  [594] = {.lex_state = 0},
  [595] = {.lex_state = 0},
  [596] = {.lex_state = 0},
  [597] = {.lex_state = 0},
  [598] = {.lex_state = 0},
  [599] = {.lex_state = 0},
  [600] = {.lex_state = 0},
  [601] = {.lex_state = 98},
  [602] = {.lex_state = 1},
  [603] = {.lex_state = 2},
  [604] = {.lex_state = 0},
  [605] = {.lex_state = 1},
  [606] = {.lex_state = 0},
  [607] = {.lex_state = 0},
  [608] = {.lex_state = 0},
  [609] = {.lex_state = 0},
  [610] = {.lex_state = 0},
  [611] = {.lex_state = 0},
  [612] = {.lex_state = 0},
  [613] = {.lex_state = 0},
  [614] = {.lex_state = 0},
  [615] = {.lex_state = 2},
  [616] = {.lex_state = 0},
  [617] = {.lex_state = 0},
  [618] = {.lex_state = 0},
  [619] = {.lex_state = 0},
  [620] = {.lex_state = 0},
  [621] = {.lex_state = 0},
  [622] = {.lex_state = 0},
  [623] = {.lex_state = 0},
  [624] = {.lex_state = 0},
  [625] = {.lex_state = 0},
  [626] = {.lex_state = 2},
  [627] = {.lex_state = 0},
  [628] = {.lex_state = 0},
  [629] = {.lex_state = 0},
  [630] = {.lex_state = 0},
  [631] = {.lex_state = 0},
  [632] = {.lex_state = 16},
  [633] = {.lex_state = 0},
  [634] = {.lex_state = 0},
  [635] = {.lex_state = 0},
  [636] = {.lex_state = 0},
  [637] = {.lex_state = 0},
  [638] = {.lex_state = 0},
  [639] = {.lex_state = 1},
  [640] = {.lex_state = 0},
  [641] = {.lex_state = 1},
  [642] = {.lex_state = 0},
  [643] = {.lex_state = 0},
  [644] = {.lex_state = 0},
  [645] = {.lex_state = 1},
  [646] = {.lex_state = 0},
  [647] = {.lex_state = 0},
  [648] = {.lex_state = 0},
  [649] = {.lex_state = 0},
  [650] = {.lex_state = 18},
  [651] = {.lex_state = 0},
  [652] = {.lex_state = 0},
  [653] = {.lex_state = 0},
  [654] = {.lex_state = 0},
  [655] = {.lex_state = 1},
  [656] = {.lex_state = 1},
  [657] = {.lex_state = 0},
  [658] = {.lex_state = 1},
  [659] = {.lex_state = 0},
  [660] = {.lex_state = 1},
  [661] = {.lex_state = 0},
  [662] = {.lex_state = 0},
  [663] = {.lex_state = 0},
  [664] = {.lex_state = 0},
  [665] = {.lex_state = 18},
  [666] = {.lex_state = 1},
  [667] = {.lex_state = 1},
  [668] = {.lex_state = 1},
  [669] = {.lex_state = 1},
  [670] = {.lex_state = 16},
  [671] = {.lex_state = 0},
  [672] = {.lex_state = 1},
  [673] = {.lex_state = 1},
  [674] = {.lex_state = 7},
  [675] = {.lex_state = 16},
  [676] = {.lex_state = 0},
  [677] = {.lex_state = 0},
  [678] = {.lex_state = 0},
  [679] = {.lex_state = 0},
  [680] = {.lex_state = 0},
  [681] = {.lex_state = 0},
  [682] = {.lex_state = 0},
  [683] = {.lex_state = 0},
  [684] = {.lex_state = 0},
  [685] = {.lex_state = 0},
  [686] = {.lex_state = 1},
  [687] = {.lex_state = 0},
  [688] = {.lex_state = 16},
  [689] = {.lex_state = 0},
  [690] = {.lex_state = 0},
  [691] = {.lex_state = 16},
  [692] = {.lex_state = 0},
  [693] = {.lex_state = 0},
  [694] = {.lex_state = 0},
  [695] = {.lex_state = 0},
  [696] = {.lex_state = 0},
  [697] = {.lex_state = 0},
  [698] = {.lex_state = 0},
  [699] = {.lex_state = 0},
  [700] = {.lex_state = 0},
  [701] = {.lex_state = 0},
  [702] = {.lex_state = 0},
  [703] = {.lex_state = 0},
  [704] = {.lex_state = 0},
  [705] = {.lex_state = 0},
  [706] = {.lex_state = 0},
  [707] = {.lex_state = 0},
  [708] = {.lex_state = 0},
  [709] = {.lex_state = 0},
  [710] = {.lex_state = 0},
  [711] = {.lex_state = 0},
  [712] = {.lex_state = 0},
  [713] = {.lex_state = 0},
  [714] = {.lex_state = 0},
  [715] = {.lex_state = 0},
  [716] = {.lex_state = 0},
  [717] = {.lex_state = 0},
  [718] = {.lex_state = 0},
  [719] = {.lex_state = 0},
  [720] = {.lex_state = 16},
  [721] = {.lex_state = 0},
  [722] = {.lex_state = 0},
  [723] = {.lex_state = 0},
  [724] = {.lex_state = 0},
  [725] = {.lex_state = 0},
  [726] = {.lex_state = 16},
  [727] = {.lex_state = 0},
  [728] = {.lex_state = 0},
  [729] = {.lex_state = 0},
  [730] = {.lex_state = 0},
  [731] = {.lex_state = 0},
  [732] = {.lex_state = 0},
  [733] = {.lex_state = 0},
  [734] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_NAME] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_TARGET] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_SEARCH_DIR] = ACTIONS(1),
    [anon_sym_OUTPUT] = ACTIONS(1),
    [anon_sym_OUTPUT_FORMAT] = ACTIONS(1),
    [anon_sym_OUTPUT_ARCH] = ACTIONS(1),
    [anon_sym_FORCE_COMMON_ALLOCATION] = ACTIONS(1),
    [anon_sym_FORCE_GROUP_ALLOCATION] = ACTIONS(1),
    [anon_sym_INHIBIT_COMMON_ALLOCATION] = ACTIONS(1),
    [anon_sym_INPUT] = ACTIONS(1),
    [anon_sym_GROUP] = ACTIONS(1),
    [anon_sym_MAP] = ACTIONS(1),
    [anon_sym_INCLUDE] = ACTIONS(1),
    [anon_sym_NOCROSSREFS] = ACTIONS(1),
    [anon_sym_NOCROSSREFS_TO] = ACTIONS(1),
    [anon_sym_EXTERN] = ACTIONS(1),
    [anon_sym_INSERT] = ACTIONS(1),
    [anon_sym_AFTER] = ACTIONS(1),
    [anon_sym_BEFORE] = ACTIONS(1),
    [anon_sym_REGION_ALIAS] = ACTIONS(1),
    [anon_sym_LD_FEATURE] = ACTIONS(1),
    [anon_sym_AS_NEEDED] = ACTIONS(1),
    [anon_sym_SECTIONS] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_ENTRY] = ACTIONS(1),
    [anon_sym_ASSERT] = ACTIONS(1),
    [anon_sym_SORT_BY_NAME] = ACTIONS(1),
    [anon_sym_SORT] = ACTIONS(1),
    [anon_sym_SORT_BY_ALIGNMENT] = ACTIONS(1),
    [anon_sym_SORT_NONE] = ACTIONS(1),
    [anon_sym_SORT_BY_INIT_PRIORITY] = ACTIONS(1),
    [anon_sym_REVERSE] = ACTIONS(1),
    [anon_sym_AMP] = ACTIONS(1),
    [anon_sym_INPUT_SECTION_FLAGS] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [anon_sym_KEEP] = ACTIONS(1),
    [anon_sym_CREATE_OBJECT_SYMBOLS] = ACTIONS(1),
    [anon_sym_ASCIZ] = ACTIONS(1),
    [anon_sym_FILL] = ACTIONS(1),
    [anon_sym_LINKER_VERSION] = ACTIONS(1),
    [anon_sym_QUAD] = ACTIONS(1),
    [anon_sym_SQUAD] = ACTIONS(1),
    [anon_sym_LONG] = ACTIONS(1),
    [anon_sym_SHORT] = ACTIONS(1),
    [anon_sym_BYTE] = ACTIONS(1),
    [anon_sym_PLUS_EQ] = ACTIONS(1),
    [anon_sym_DASH_EQ] = ACTIONS(1),
    [anon_sym_STAR_EQ] = ACTIONS(1),
    [anon_sym_SLASH_EQ] = ACTIONS(1),
    [anon_sym_LT_LT_EQ] = ACTIONS(1),
    [anon_sym_GT_GT_EQ] = ACTIONS(1),
    [anon_sym_PIPE_EQ] = ACTIONS(1),
    [anon_sym_CARET_EQ] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_HIDDEN] = ACTIONS(1),
    [anon_sym_PROVIDE] = ACTIONS(1),
    [anon_sym_PROVIDE_HIDDEN] = ACTIONS(1),
    [anon_sym_MEMORY] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_ORIGIN] = ACTIONS(1),
    [anon_sym_o] = ACTIONS(1),
    [anon_sym_org] = ACTIONS(1),
    [anon_sym_LENGTH] = ACTIONS(1),
    [anon_sym_l] = ACTIONS(1),
    [anon_sym_len] = ACTIONS(1),
    [anon_sym_BANG] = ACTIONS(1),
    [anon_sym_STARTUP] = ACTIONS(1),
    [anon_sym_HLL] = ACTIONS(1),
    [anon_sym_SYSLIB] = ACTIONS(1),
    [anon_sym_FLOAT] = ACTIONS(1),
    [anon_sym_NOFLOAT] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [anon_sym_PLUS] = ACTIONS(1),
    [anon_sym_TILDE] = ACTIONS(1),
    [anon_sym_NEXT] = ACTIONS(1),
    [anon_sym_ABSOLUTE] = ACTIONS(1),
    [anon_sym_DATA_SEGMENT_END] = ACTIONS(1),
    [anon_sym_BLOCK] = ACTIONS(1),
    [anon_sym_LOG2CEIL] = ACTIONS(1),
    [anon_sym_STAR] = ACTIONS(1),
    [anon_sym_SLASH] = ACTIONS(1),
    [anon_sym_PERCENT] = ACTIONS(1),
    [anon_sym_LT_LT] = ACTIONS(1),
    [anon_sym_GT_GT] = ACTIONS(1),
    [anon_sym_EQ_EQ] = ACTIONS(1),
    [anon_sym_LT_EQ] = ACTIONS(1),
    [anon_sym_GT_EQ] = ACTIONS(1),
    [anon_sym_LT] = ACTIONS(1),
    [anon_sym_GT] = ACTIONS(1),
    [anon_sym_CARET] = ACTIONS(1),
    [anon_sym_PIPE] = ACTIONS(1),
    [anon_sym_AMP_AMP] = ACTIONS(1),
    [anon_sym_PIPE_PIPE] = ACTIONS(1),
    [anon_sym_QMARK] = ACTIONS(1),
    [anon_sym_DEFINED] = ACTIONS(1),
    [anon_sym_CONSTANT] = ACTIONS(1),
    [anon_sym_SIZEOF_HEADERS] = ACTIONS(1),
    [anon_sym_ALIGNOF] = ACTIONS(1),
    [anon_sym_SIZEOF] = ACTIONS(1),
    [anon_sym_ADDR] = ACTIONS(1),
    [anon_sym_LOADADDR] = ACTIONS(1),
    [anon_sym_ALIGN] = ACTIONS(1),
    [anon_sym_DATA_SEGMENT_ALIGN] = ACTIONS(1),
    [anon_sym_DATA_SEGMENT_RELRO_END] = ACTIONS(1),
    [anon_sym_MAX] = ACTIONS(1),
    [anon_sym_MIN] = ACTIONS(1),
    [anon_sym_SEGMENT_START] = ACTIONS(1),
    [anon_sym_AT] = ACTIONS(1),
    [anon_sym_SUBALIGN] = ACTIONS(1),
    [anon_sym_ONLY_IF_RO] = ACTIONS(1),
    [anon_sym_ONLY_IF_RW] = ACTIONS(1),
    [anon_sym_SPECIAL] = ACTIONS(1),
    [anon_sym_ALIGN_WITH_INPUT] = ACTIONS(1),
    [anon_sym_OVERLAY] = ACTIONS(1),
    [anon_sym_NOLOAD] = ACTIONS(1),
    [anon_sym_DSECT] = ACTIONS(1),
    [anon_sym_COPY] = ACTIONS(1),
    [anon_sym_INFO] = ACTIONS(1),
    [anon_sym_READONLY] = ACTIONS(1),
    [anon_sym_TYPE] = ACTIONS(1),
    [anon_sym_BIND] = ACTIONS(1),
    [anon_sym_PHDRS] = ACTIONS(1),
    [anon_sym_VERSION] = ACTIONS(1),
    [anon_sym_global] = ACTIONS(1),
    [anon_sym_local] = ACTIONS(1),
    [aux_sym_INT_token1] = ACTIONS(1),
    [aux_sym_INT_token2] = ACTIONS(1),
    [aux_sym_INT_token3] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
  },
  [1] = {
    [sym_script_file] = STATE(676),
    [sym_ifile_p1] = STATE(4),
    [sym_sections] = STATE(34),
    [sym_statement_anywhere] = STATE(34),
    [sym_assignment] = STATE(442),
    [sym_memory] = STATE(34),
    [sym_startup] = STATE(34),
    [sym_high_level_library] = STATE(34),
    [sym_low_level_library] = STATE(34),
    [sym_floating_point_support] = STATE(34),
    [sym_phdrs] = STATE(34),
    [sym_version] = STATE(34),
    [aux_sym_script_file_repeat1] = STATE(4),
    [ts_builtin_sym_end] = ACTIONS(5),
    [sym_NAME] = ACTIONS(7),
    [anon_sym_SEMI] = ACTIONS(9),
    [anon_sym_TARGET] = ACTIONS(11),
    [anon_sym_SEARCH_DIR] = ACTIONS(13),
    [anon_sym_OUTPUT] = ACTIONS(13),
    [anon_sym_OUTPUT_FORMAT] = ACTIONS(15),
    [anon_sym_OUTPUT_ARCH] = ACTIONS(11),
    [anon_sym_FORCE_COMMON_ALLOCATION] = ACTIONS(17),
    [anon_sym_FORCE_GROUP_ALLOCATION] = ACTIONS(17),
    [anon_sym_INHIBIT_COMMON_ALLOCATION] = ACTIONS(17),
    [anon_sym_INPUT] = ACTIONS(19),
    [anon_sym_GROUP] = ACTIONS(19),
    [anon_sym_MAP] = ACTIONS(13),
    [anon_sym_INCLUDE] = ACTIONS(21),
    [anon_sym_NOCROSSREFS] = ACTIONS(23),
    [anon_sym_NOCROSSREFS_TO] = ACTIONS(23),
    [anon_sym_EXTERN] = ACTIONS(25),
    [anon_sym_INSERT] = ACTIONS(27),
    [anon_sym_REGION_ALIAS] = ACTIONS(29),
    [anon_sym_LD_FEATURE] = ACTIONS(11),
    [anon_sym_SECTIONS] = ACTIONS(31),
    [anon_sym_ENTRY] = ACTIONS(33),
    [anon_sym_ASSERT] = ACTIONS(35),
    [anon_sym_HIDDEN] = ACTIONS(37),
    [anon_sym_PROVIDE] = ACTIONS(37),
    [anon_sym_PROVIDE_HIDDEN] = ACTIONS(37),
    [anon_sym_MEMORY] = ACTIONS(39),
    [anon_sym_STARTUP] = ACTIONS(41),
    [anon_sym_HLL] = ACTIONS(43),
    [anon_sym_SYSLIB] = ACTIONS(45),
    [anon_sym_FLOAT] = ACTIONS(47),
    [anon_sym_NOFLOAT] = ACTIONS(47),
    [anon_sym_PHDRS] = ACTIONS(49),
    [anon_sym_VERSION] = ACTIONS(51),
    [sym_comment] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 22,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(53), 1,
      anon_sym_LPAREN,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(59), 1,
      anon_sym_EQ,
    ACTIONS(61), 1,
      anon_sym_COLON,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(81), 1,
      anon_sym_BIND,
    STATE(58), 1,
      sym_assign_op,
    STATE(124), 1,
      sym_INT,
    STATE(151), 1,
      sym_exp,
    STATE(233), 1,
      sym_opt_exp_with_type,
    STATE(551), 1,
      sym_atype,
    ACTIONS(65), 2,
      anon_sym_BANG,
      anon_sym_TILDE,
    ACTIONS(67), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
    ACTIONS(57), 9,
      anon_sym_PLUS_EQ,
      anon_sym_DASH_EQ,
      anon_sym_STAR_EQ,
      anon_sym_SLASH_EQ,
      anon_sym_LT_LT_EQ,
      anon_sym_GT_GT_EQ,
      anon_sym_AMP_EQ,
      anon_sym_PIPE_EQ,
      anon_sym_CARET_EQ,
  [93] = 28,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(85), 1,
      ts_builtin_sym_end,
    ACTIONS(87), 1,
      sym_NAME,
    ACTIONS(90), 1,
      anon_sym_SEMI,
    ACTIONS(99), 1,
      anon_sym_OUTPUT_FORMAT,
    ACTIONS(108), 1,
      anon_sym_INCLUDE,
    ACTIONS(114), 1,
      anon_sym_EXTERN,
    ACTIONS(117), 1,
      anon_sym_INSERT,
    ACTIONS(120), 1,
      anon_sym_REGION_ALIAS,
    ACTIONS(123), 1,
      anon_sym_SECTIONS,
    ACTIONS(126), 1,
      anon_sym_ENTRY,
    ACTIONS(129), 1,
      anon_sym_ASSERT,
    ACTIONS(135), 1,
      anon_sym_MEMORY,
    ACTIONS(138), 1,
      anon_sym_STARTUP,
    ACTIONS(141), 1,
      anon_sym_HLL,
    ACTIONS(144), 1,
      anon_sym_SYSLIB,
    ACTIONS(150), 1,
      anon_sym_PHDRS,
    ACTIONS(153), 1,
      anon_sym_VERSION,
    STATE(442), 1,
      sym_assignment,
    ACTIONS(105), 2,
      anon_sym_INPUT,
      anon_sym_GROUP,
    ACTIONS(111), 2,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
    ACTIONS(147), 2,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
    STATE(3), 2,
      sym_ifile_p1,
      aux_sym_script_file_repeat1,
    ACTIONS(93), 3,
      anon_sym_TARGET,
      anon_sym_OUTPUT_ARCH,
      anon_sym_LD_FEATURE,
    ACTIONS(96), 3,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_MAP,
    ACTIONS(102), 3,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
    ACTIONS(132), 3,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
    STATE(34), 9,
      sym_sections,
      sym_statement_anywhere,
      sym_memory,
      sym_startup,
      sym_high_level_library,
      sym_low_level_library,
      sym_floating_point_support,
      sym_phdrs,
      sym_version,
  [198] = 28,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      sym_NAME,
    ACTIONS(9), 1,
      anon_sym_SEMI,
    ACTIONS(15), 1,
      anon_sym_OUTPUT_FORMAT,
    ACTIONS(21), 1,
      anon_sym_INCLUDE,
    ACTIONS(25), 1,
      anon_sym_EXTERN,
    ACTIONS(27), 1,
      anon_sym_INSERT,
    ACTIONS(29), 1,
      anon_sym_REGION_ALIAS,
    ACTIONS(31), 1,
      anon_sym_SECTIONS,
    ACTIONS(33), 1,
      anon_sym_ENTRY,
    ACTIONS(35), 1,
      anon_sym_ASSERT,
    ACTIONS(39), 1,
      anon_sym_MEMORY,
    ACTIONS(41), 1,
      anon_sym_STARTUP,
    ACTIONS(43), 1,
      anon_sym_HLL,
    ACTIONS(45), 1,
      anon_sym_SYSLIB,
    ACTIONS(49), 1,
      anon_sym_PHDRS,
    ACTIONS(51), 1,
      anon_sym_VERSION,
    ACTIONS(156), 1,
      ts_builtin_sym_end,
    STATE(442), 1,
      sym_assignment,
    ACTIONS(19), 2,
      anon_sym_INPUT,
      anon_sym_GROUP,
    ACTIONS(23), 2,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
    ACTIONS(47), 2,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
    STATE(3), 2,
      sym_ifile_p1,
      aux_sym_script_file_repeat1,
    ACTIONS(11), 3,
      anon_sym_TARGET,
      anon_sym_OUTPUT_ARCH,
      anon_sym_LD_FEATURE,
    ACTIONS(13), 3,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_MAP,
    ACTIONS(17), 3,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
    ACTIONS(37), 3,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
    STATE(34), 9,
      sym_sections,
      sym_statement_anywhere,
      sym_memory,
      sym_startup,
      sym_high_level_library,
      sym_low_level_library,
      sym_floating_point_support,
      sym_phdrs,
      sym_version,
  [303] = 19,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    ACTIONS(160), 1,
      anon_sym_RPAREN,
    ACTIONS(164), 1,
      anon_sym_READONLY,
    ACTIONS(166), 1,
      anon_sym_TYPE,
    STATE(124), 1,
      sym_INT,
    STATE(155), 1,
      sym_exp,
    STATE(543), 1,
      sym_type,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(162), 5,
      anon_sym_OVERLAY,
      anon_sym_NOLOAD,
      anon_sym_DSECT,
      anon_sym_COPY,
      anon_sym_INFO,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [384] = 29,
    ACTIONS(168), 1,
      sym_NAME,
    ACTIONS(170), 1,
      anon_sym_SEMI,
    ACTIONS(172), 1,
      anon_sym_INCLUDE,
    ACTIONS(174), 1,
      anon_sym_RBRACE,
    ACTIONS(176), 1,
      anon_sym_ASSERT,
    ACTIONS(180), 1,
      anon_sym_SORT_NONE,
    ACTIONS(182), 1,
      anon_sym_REVERSE,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(186), 1,
      anon_sym_INPUT_SECTION_FLAGS,
    ACTIONS(188), 1,
      anon_sym_LBRACK,
    ACTIONS(190), 1,
      anon_sym_KEEP,
    ACTIONS(194), 1,
      anon_sym_ASCIZ,
    ACTIONS(196), 1,
      anon_sym_FILL,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    STATE(117), 1,
      sym_input_section_spec,
    STATE(129), 1,
      sym_input_section_spec_no_keep,
    STATE(248), 1,
      sym_sect_flags,
    STATE(454), 1,
      sym_assignment,
    STATE(464), 1,
      sym_wildcard_maybe_exclude,
    STATE(513), 1,
      sym_statement_list,
    STATE(640), 1,
      sym_length,
    STATE(644), 1,
      sym_filename_spec,
    STATE(647), 1,
      sym_wildcard_maybe_reverse,
    ACTIONS(178), 2,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
    STATE(15), 2,
      sym_statement,
      aux_sym_statement_list_repeat1,
    ACTIONS(37), 3,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
    ACTIONS(192), 3,
      anon_sym_CREATE_OBJECT_SYMBOLS,
      anon_sym_CONSTRUCTORS,
      anon_sym_LINKER_VERSION,
    ACTIONS(198), 5,
      anon_sym_QUAD,
      anon_sym_SQUAD,
      anon_sym_LONG,
      anon_sym_SHORT,
      anon_sym_BYTE,
  [482] = 29,
    ACTIONS(168), 1,
      sym_NAME,
    ACTIONS(170), 1,
      anon_sym_SEMI,
    ACTIONS(172), 1,
      anon_sym_INCLUDE,
    ACTIONS(176), 1,
      anon_sym_ASSERT,
    ACTIONS(180), 1,
      anon_sym_SORT_NONE,
    ACTIONS(182), 1,
      anon_sym_REVERSE,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(186), 1,
      anon_sym_INPUT_SECTION_FLAGS,
    ACTIONS(188), 1,
      anon_sym_LBRACK,
    ACTIONS(190), 1,
      anon_sym_KEEP,
    ACTIONS(194), 1,
      anon_sym_ASCIZ,
    ACTIONS(196), 1,
      anon_sym_FILL,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(204), 1,
      anon_sym_RBRACE,
    STATE(117), 1,
      sym_input_section_spec,
    STATE(129), 1,
      sym_input_section_spec_no_keep,
    STATE(248), 1,
      sym_sect_flags,
    STATE(454), 1,
      sym_assignment,
    STATE(464), 1,
      sym_wildcard_maybe_exclude,
    STATE(557), 1,
      sym_statement_list,
    STATE(640), 1,
      sym_length,
    STATE(644), 1,
      sym_filename_spec,
    STATE(647), 1,
      sym_wildcard_maybe_reverse,
    ACTIONS(178), 2,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
    STATE(15), 2,
      sym_statement,
      aux_sym_statement_list_repeat1,
    ACTIONS(37), 3,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
    ACTIONS(192), 3,
      anon_sym_CREATE_OBJECT_SYMBOLS,
      anon_sym_CONSTRUCTORS,
      anon_sym_LINKER_VERSION,
    ACTIONS(198), 5,
      anon_sym_QUAD,
      anon_sym_SQUAD,
      anon_sym_LONG,
      anon_sym_SHORT,
      anon_sym_BYTE,
  [580] = 29,
    ACTIONS(168), 1,
      sym_NAME,
    ACTIONS(170), 1,
      anon_sym_SEMI,
    ACTIONS(172), 1,
      anon_sym_INCLUDE,
    ACTIONS(176), 1,
      anon_sym_ASSERT,
    ACTIONS(180), 1,
      anon_sym_SORT_NONE,
    ACTIONS(182), 1,
      anon_sym_REVERSE,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(186), 1,
      anon_sym_INPUT_SECTION_FLAGS,
    ACTIONS(188), 1,
      anon_sym_LBRACK,
    ACTIONS(190), 1,
      anon_sym_KEEP,
    ACTIONS(194), 1,
      anon_sym_ASCIZ,
    ACTIONS(196), 1,
      anon_sym_FILL,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(206), 1,
      anon_sym_RBRACE,
    STATE(117), 1,
      sym_input_section_spec,
    STATE(129), 1,
      sym_input_section_spec_no_keep,
    STATE(248), 1,
      sym_sect_flags,
    STATE(454), 1,
      sym_assignment,
    STATE(464), 1,
      sym_wildcard_maybe_exclude,
    STATE(562), 1,
      sym_statement_list,
    STATE(640), 1,
      sym_length,
    STATE(644), 1,
      sym_filename_spec,
    STATE(647), 1,
      sym_wildcard_maybe_reverse,
    ACTIONS(178), 2,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
    STATE(15), 2,
      sym_statement,
      aux_sym_statement_list_repeat1,
    ACTIONS(37), 3,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
    ACTIONS(192), 3,
      anon_sym_CREATE_OBJECT_SYMBOLS,
      anon_sym_CONSTRUCTORS,
      anon_sym_LINKER_VERSION,
    ACTIONS(198), 5,
      anon_sym_QUAD,
      anon_sym_SQUAD,
      anon_sym_LONG,
      anon_sym_SHORT,
      anon_sym_BYTE,
  [678] = 29,
    ACTIONS(168), 1,
      sym_NAME,
    ACTIONS(170), 1,
      anon_sym_SEMI,
    ACTIONS(172), 1,
      anon_sym_INCLUDE,
    ACTIONS(176), 1,
      anon_sym_ASSERT,
    ACTIONS(180), 1,
      anon_sym_SORT_NONE,
    ACTIONS(182), 1,
      anon_sym_REVERSE,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(186), 1,
      anon_sym_INPUT_SECTION_FLAGS,
    ACTIONS(188), 1,
      anon_sym_LBRACK,
    ACTIONS(190), 1,
      anon_sym_KEEP,
    ACTIONS(194), 1,
      anon_sym_ASCIZ,
    ACTIONS(196), 1,
      anon_sym_FILL,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(208), 1,
      anon_sym_RBRACE,
    STATE(117), 1,
      sym_input_section_spec,
    STATE(129), 1,
      sym_input_section_spec_no_keep,
    STATE(248), 1,
      sym_sect_flags,
    STATE(454), 1,
      sym_assignment,
    STATE(464), 1,
      sym_wildcard_maybe_exclude,
    STATE(640), 1,
      sym_length,
    STATE(644), 1,
      sym_filename_spec,
    STATE(647), 1,
      sym_wildcard_maybe_reverse,
    STATE(716), 1,
      sym_statement_list,
    ACTIONS(178), 2,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
    STATE(15), 2,
      sym_statement,
      aux_sym_statement_list_repeat1,
    ACTIONS(37), 3,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
    ACTIONS(192), 3,
      anon_sym_CREATE_OBJECT_SYMBOLS,
      anon_sym_CONSTRUCTORS,
      anon_sym_LINKER_VERSION,
    ACTIONS(198), 5,
      anon_sym_QUAD,
      anon_sym_SQUAD,
      anon_sym_LONG,
      anon_sym_SHORT,
      anon_sym_BYTE,
  [776] = 29,
    ACTIONS(168), 1,
      sym_NAME,
    ACTIONS(170), 1,
      anon_sym_SEMI,
    ACTIONS(172), 1,
      anon_sym_INCLUDE,
    ACTIONS(176), 1,
      anon_sym_ASSERT,
    ACTIONS(180), 1,
      anon_sym_SORT_NONE,
    ACTIONS(182), 1,
      anon_sym_REVERSE,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(186), 1,
      anon_sym_INPUT_SECTION_FLAGS,
    ACTIONS(188), 1,
      anon_sym_LBRACK,
    ACTIONS(190), 1,
      anon_sym_KEEP,
    ACTIONS(194), 1,
      anon_sym_ASCIZ,
    ACTIONS(196), 1,
      anon_sym_FILL,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(210), 1,
      anon_sym_RBRACE,
    STATE(117), 1,
      sym_input_section_spec,
    STATE(129), 1,
      sym_input_section_spec_no_keep,
    STATE(248), 1,
      sym_sect_flags,
    STATE(454), 1,
      sym_assignment,
    STATE(464), 1,
      sym_wildcard_maybe_exclude,
    STATE(532), 1,
      sym_statement_list,
    STATE(640), 1,
      sym_length,
    STATE(644), 1,
      sym_filename_spec,
    STATE(647), 1,
      sym_wildcard_maybe_reverse,
    ACTIONS(178), 2,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
    STATE(15), 2,
      sym_statement,
      aux_sym_statement_list_repeat1,
    ACTIONS(37), 3,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
    ACTIONS(192), 3,
      anon_sym_CREATE_OBJECT_SYMBOLS,
      anon_sym_CONSTRUCTORS,
      anon_sym_LINKER_VERSION,
    ACTIONS(198), 5,
      anon_sym_QUAD,
      anon_sym_SQUAD,
      anon_sym_LONG,
      anon_sym_SHORT,
      anon_sym_BYTE,
  [874] = 29,
    ACTIONS(168), 1,
      sym_NAME,
    ACTIONS(170), 1,
      anon_sym_SEMI,
    ACTIONS(172), 1,
      anon_sym_INCLUDE,
    ACTIONS(176), 1,
      anon_sym_ASSERT,
    ACTIONS(180), 1,
      anon_sym_SORT_NONE,
    ACTIONS(182), 1,
      anon_sym_REVERSE,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(186), 1,
      anon_sym_INPUT_SECTION_FLAGS,
    ACTIONS(188), 1,
      anon_sym_LBRACK,
    ACTIONS(190), 1,
      anon_sym_KEEP,
    ACTIONS(194), 1,
      anon_sym_ASCIZ,
    ACTIONS(196), 1,
      anon_sym_FILL,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(212), 1,
      anon_sym_RBRACE,
    STATE(117), 1,
      sym_input_section_spec,
    STATE(129), 1,
      sym_input_section_spec_no_keep,
    STATE(248), 1,
      sym_sect_flags,
    STATE(454), 1,
      sym_assignment,
    STATE(464), 1,
      sym_wildcard_maybe_exclude,
    STATE(608), 1,
      sym_statement_list,
    STATE(640), 1,
      sym_length,
    STATE(644), 1,
      sym_filename_spec,
    STATE(647), 1,
      sym_wildcard_maybe_reverse,
    ACTIONS(178), 2,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
    STATE(15), 2,
      sym_statement,
      aux_sym_statement_list_repeat1,
    ACTIONS(37), 3,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
    ACTIONS(192), 3,
      anon_sym_CREATE_OBJECT_SYMBOLS,
      anon_sym_CONSTRUCTORS,
      anon_sym_LINKER_VERSION,
    ACTIONS(198), 5,
      anon_sym_QUAD,
      anon_sym_SQUAD,
      anon_sym_LONG,
      anon_sym_SHORT,
      anon_sym_BYTE,
  [972] = 7,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(220), 1,
      anon_sym_EQ,
    STATE(58), 1,
      sym_assign_op,
    ACTIONS(216), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
    ACTIONS(57), 4,
      anon_sym_LT_LT_EQ,
      anon_sym_GT_GT_EQ,
      anon_sym_AMP_EQ,
      anon_sym_PIPE_EQ,
    ACTIONS(218), 5,
      anon_sym_PLUS_EQ,
      anon_sym_DASH_EQ,
      anon_sym_STAR_EQ,
      anon_sym_SLASH_EQ,
      anon_sym_CARET_EQ,
    ACTIONS(214), 25,
      anon_sym_INCLUDE,
      anon_sym_ASSERT,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_NONE,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      anon_sym_INPUT_SECTION_FLAGS,
      anon_sym_LBRACK,
      anon_sym_KEEP,
      anon_sym_CREATE_OBJECT_SYMBOLS,
      anon_sym_CONSTRUCTORS,
      anon_sym_ASCIZ,
      anon_sym_FILL,
      anon_sym_LINKER_VERSION,
      anon_sym_QUAD,
      anon_sym_SQUAD,
      anon_sym_LONG,
      anon_sym_SHORT,
      anon_sym_BYTE,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      sym_NAME,
      sym_wildcard_name,
  [1026] = 29,
    ACTIONS(168), 1,
      sym_NAME,
    ACTIONS(170), 1,
      anon_sym_SEMI,
    ACTIONS(172), 1,
      anon_sym_INCLUDE,
    ACTIONS(176), 1,
      anon_sym_ASSERT,
    ACTIONS(180), 1,
      anon_sym_SORT_NONE,
    ACTIONS(182), 1,
      anon_sym_REVERSE,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(186), 1,
      anon_sym_INPUT_SECTION_FLAGS,
    ACTIONS(188), 1,
      anon_sym_LBRACK,
    ACTIONS(190), 1,
      anon_sym_KEEP,
    ACTIONS(194), 1,
      anon_sym_ASCIZ,
    ACTIONS(196), 1,
      anon_sym_FILL,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(222), 1,
      anon_sym_RBRACE,
    STATE(117), 1,
      sym_input_section_spec,
    STATE(129), 1,
      sym_input_section_spec_no_keep,
    STATE(248), 1,
      sym_sect_flags,
    STATE(454), 1,
      sym_assignment,
    STATE(464), 1,
      sym_wildcard_maybe_exclude,
    STATE(525), 1,
      sym_statement_list,
    STATE(640), 1,
      sym_length,
    STATE(644), 1,
      sym_filename_spec,
    STATE(647), 1,
      sym_wildcard_maybe_reverse,
    ACTIONS(178), 2,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
    STATE(15), 2,
      sym_statement,
      aux_sym_statement_list_repeat1,
    ACTIONS(37), 3,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
    ACTIONS(192), 3,
      anon_sym_CREATE_OBJECT_SYMBOLS,
      anon_sym_CONSTRUCTORS,
      anon_sym_LINKER_VERSION,
    ACTIONS(198), 5,
      anon_sym_QUAD,
      anon_sym_SQUAD,
      anon_sym_LONG,
      anon_sym_SHORT,
      anon_sym_BYTE,
  [1124] = 28,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(224), 1,
      sym_NAME,
    ACTIONS(227), 1,
      anon_sym_SEMI,
    ACTIONS(230), 1,
      anon_sym_INCLUDE,
    ACTIONS(233), 1,
      anon_sym_RBRACE,
    ACTIONS(235), 1,
      anon_sym_ASSERT,
    ACTIONS(241), 1,
      anon_sym_SORT_NONE,
    ACTIONS(244), 1,
      anon_sym_REVERSE,
    ACTIONS(247), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(250), 1,
      anon_sym_INPUT_SECTION_FLAGS,
    ACTIONS(253), 1,
      anon_sym_LBRACK,
    ACTIONS(256), 1,
      anon_sym_KEEP,
    ACTIONS(262), 1,
      anon_sym_ASCIZ,
    ACTIONS(265), 1,
      anon_sym_FILL,
    ACTIONS(274), 1,
      sym_wildcard_name,
    STATE(117), 1,
      sym_input_section_spec,
    STATE(129), 1,
      sym_input_section_spec_no_keep,
    STATE(248), 1,
      sym_sect_flags,
    STATE(454), 1,
      sym_assignment,
    STATE(464), 1,
      sym_wildcard_maybe_exclude,
    STATE(640), 1,
      sym_length,
    STATE(644), 1,
      sym_filename_spec,
    STATE(647), 1,
      sym_wildcard_maybe_reverse,
    ACTIONS(238), 2,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
    STATE(14), 2,
      sym_statement,
      aux_sym_statement_list_repeat1,
    ACTIONS(259), 3,
      anon_sym_CREATE_OBJECT_SYMBOLS,
      anon_sym_CONSTRUCTORS,
      anon_sym_LINKER_VERSION,
    ACTIONS(271), 3,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
    ACTIONS(268), 5,
      anon_sym_QUAD,
      anon_sym_SQUAD,
      anon_sym_LONG,
      anon_sym_SHORT,
      anon_sym_BYTE,
  [1219] = 28,
    ACTIONS(168), 1,
      sym_NAME,
    ACTIONS(170), 1,
      anon_sym_SEMI,
    ACTIONS(172), 1,
      anon_sym_INCLUDE,
    ACTIONS(176), 1,
      anon_sym_ASSERT,
    ACTIONS(180), 1,
      anon_sym_SORT_NONE,
    ACTIONS(182), 1,
      anon_sym_REVERSE,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(186), 1,
      anon_sym_INPUT_SECTION_FLAGS,
    ACTIONS(188), 1,
      anon_sym_LBRACK,
    ACTIONS(190), 1,
      anon_sym_KEEP,
    ACTIONS(194), 1,
      anon_sym_ASCIZ,
    ACTIONS(196), 1,
      anon_sym_FILL,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(277), 1,
      anon_sym_RBRACE,
    STATE(117), 1,
      sym_input_section_spec,
    STATE(129), 1,
      sym_input_section_spec_no_keep,
    STATE(248), 1,
      sym_sect_flags,
    STATE(454), 1,
      sym_assignment,
    STATE(464), 1,
      sym_wildcard_maybe_exclude,
    STATE(640), 1,
      sym_length,
    STATE(644), 1,
      sym_filename_spec,
    STATE(647), 1,
      sym_wildcard_maybe_reverse,
    ACTIONS(178), 2,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
    STATE(14), 2,
      sym_statement,
      aux_sym_statement_list_repeat1,
    ACTIONS(37), 3,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
    ACTIONS(192), 3,
      anon_sym_CREATE_OBJECT_SYMBOLS,
      anon_sym_CONSTRUCTORS,
      anon_sym_LINKER_VERSION,
    ACTIONS(198), 5,
      anon_sym_QUAD,
      anon_sym_SQUAD,
      anon_sym_LONG,
      anon_sym_SHORT,
      anon_sym_BYTE,
  [1314] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RPAREN,
    ACTIONS(281), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [1358] = 18,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(53), 1,
      anon_sym_LPAREN,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(61), 1,
      anon_sym_COLON,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(81), 1,
      anon_sym_BIND,
    STATE(124), 1,
      sym_INT,
    STATE(151), 1,
      sym_exp,
    STATE(550), 1,
      sym_opt_exp_with_type,
    STATE(551), 1,
      sym_atype,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [1432] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(283), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(285), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [1475] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(287), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(289), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [1518] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(291), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(293), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [1561] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(295), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(297), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [1604] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(299), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(301), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [1647] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(303), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(305), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [1690] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(307), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(309), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [1733] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(311), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(313), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [1776] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(315), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(317), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [1819] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(319), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(321), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [1862] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(323), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(325), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [1905] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(327), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(329), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [1948] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(331), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(333), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [1991] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(335), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(337), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [2034] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(339), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(341), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [2077] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(343), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(345), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [2120] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(347), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(349), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [2163] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(351), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(353), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [2206] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(355), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(357), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [2249] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(359), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(361), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [2292] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(363), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(365), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [2335] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(367), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(369), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [2378] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(371), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
    ACTIONS(373), 33,
      anon_sym_TARGET,
      anon_sym_SEARCH_DIR,
      anon_sym_OUTPUT,
      anon_sym_OUTPUT_FORMAT,
      anon_sym_OUTPUT_ARCH,
      anon_sym_FORCE_COMMON_ALLOCATION,
      anon_sym_FORCE_GROUP_ALLOCATION,
      anon_sym_INHIBIT_COMMON_ALLOCATION,
      anon_sym_INPUT,
      anon_sym_GROUP,
      anon_sym_MAP,
      anon_sym_INCLUDE,
      anon_sym_NOCROSSREFS,
      anon_sym_NOCROSSREFS_TO,
      anon_sym_EXTERN,
      anon_sym_INSERT,
      anon_sym_REGION_ALIAS,
      anon_sym_LD_FEATURE,
      anon_sym_SECTIONS,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_MEMORY,
      anon_sym_STARTUP,
      anon_sym_HLL,
      anon_sym_SYSLIB,
      anon_sym_FLOAT,
      anon_sym_NOFLOAT,
      anon_sym_PHDRS,
      anon_sym_VERSION,
      sym_NAME,
  [2421] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(375), 1,
      anon_sym_LPAREN,
    ACTIONS(377), 1,
      anon_sym_ASSERT,
    ACTIONS(389), 1,
      anon_sym_ALIGN,
    ACTIONS(393), 1,
      anon_sym_SEGMENT_START,
    STATE(105), 1,
      sym_exp,
    STATE(109), 1,
      sym_INT,
    STATE(235), 1,
      sym_mustbe_exp,
    STATE(251), 1,
      sym_fill_exp,
    ACTIONS(385), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(387), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(395), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(381), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(391), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(383), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(379), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [2489] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(375), 1,
      anon_sym_LPAREN,
    ACTIONS(377), 1,
      anon_sym_ASSERT,
    ACTIONS(389), 1,
      anon_sym_ALIGN,
    ACTIONS(393), 1,
      anon_sym_SEGMENT_START,
    STATE(105), 1,
      sym_exp,
    STATE(109), 1,
      sym_INT,
    STATE(235), 1,
      sym_mustbe_exp,
    STATE(245), 1,
      sym_fill_exp,
    ACTIONS(385), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(387), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(395), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(381), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(391), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(383), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(379), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [2557] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(375), 1,
      anon_sym_LPAREN,
    ACTIONS(377), 1,
      anon_sym_ASSERT,
    ACTIONS(389), 1,
      anon_sym_ALIGN,
    ACTIONS(393), 1,
      anon_sym_SEGMENT_START,
    STATE(105), 1,
      sym_exp,
    STATE(109), 1,
      sym_INT,
    STATE(235), 1,
      sym_mustbe_exp,
    STATE(255), 1,
      sym_fill_exp,
    ACTIONS(385), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(387), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(395), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(381), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(391), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(383), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(379), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [2625] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(397), 1,
      anon_sym_LPAREN,
    ACTIONS(399), 1,
      anon_sym_ASSERT,
    ACTIONS(411), 1,
      anon_sym_ALIGN,
    ACTIONS(415), 1,
      anon_sym_SEGMENT_START,
    STATE(146), 1,
      sym_INT,
    STATE(149), 1,
      sym_exp,
    STATE(446), 1,
      sym_mustbe_exp,
    STATE(450), 1,
      sym_fill_exp,
    ACTIONS(407), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(409), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(417), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(403), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(413), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(405), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(401), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [2693] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(375), 1,
      anon_sym_LPAREN,
    ACTIONS(377), 1,
      anon_sym_ASSERT,
    ACTIONS(389), 1,
      anon_sym_ALIGN,
    ACTIONS(393), 1,
      anon_sym_SEGMENT_START,
    STATE(105), 1,
      sym_exp,
    STATE(109), 1,
      sym_INT,
    STATE(235), 1,
      sym_mustbe_exp,
    STATE(247), 1,
      sym_fill_exp,
    ACTIONS(385), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(387), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(395), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(381), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(391), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(383), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(379), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [2761] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(375), 1,
      anon_sym_LPAREN,
    ACTIONS(377), 1,
      anon_sym_ASSERT,
    ACTIONS(389), 1,
      anon_sym_ALIGN,
    ACTIONS(393), 1,
      anon_sym_SEGMENT_START,
    STATE(105), 1,
      sym_exp,
    STATE(109), 1,
      sym_INT,
    STATE(235), 1,
      sym_mustbe_exp,
    STATE(253), 1,
      sym_fill_exp,
    ACTIONS(385), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(387), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(395), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(381), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(391), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(383), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(379), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [2829] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(375), 1,
      anon_sym_LPAREN,
    ACTIONS(377), 1,
      anon_sym_ASSERT,
    ACTIONS(389), 1,
      anon_sym_ALIGN,
    ACTIONS(393), 1,
      anon_sym_SEGMENT_START,
    STATE(105), 1,
      sym_exp,
    STATE(109), 1,
      sym_INT,
    STATE(235), 1,
      sym_mustbe_exp,
    STATE(256), 1,
      sym_fill_exp,
    ACTIONS(385), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(387), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(395), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(381), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(391), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(383), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(379), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [2897] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(375), 1,
      anon_sym_LPAREN,
    ACTIONS(377), 1,
      anon_sym_ASSERT,
    ACTIONS(389), 1,
      anon_sym_ALIGN,
    ACTIONS(393), 1,
      anon_sym_SEGMENT_START,
    STATE(105), 1,
      sym_exp,
    STATE(109), 1,
      sym_INT,
    STATE(235), 1,
      sym_mustbe_exp,
    STATE(250), 1,
      sym_fill_exp,
    ACTIONS(385), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(387), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(395), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(381), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(391), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(383), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(379), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [2965] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(397), 1,
      anon_sym_LPAREN,
    ACTIONS(399), 1,
      anon_sym_ASSERT,
    ACTIONS(411), 1,
      anon_sym_ALIGN,
    ACTIONS(415), 1,
      anon_sym_SEGMENT_START,
    STATE(146), 1,
      sym_INT,
    STATE(149), 1,
      sym_exp,
    STATE(433), 1,
      sym_fill_exp,
    STATE(446), 1,
      sym_mustbe_exp,
    ACTIONS(407), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(409), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(417), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(403), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(413), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(405), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(401), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [3033] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(375), 1,
      anon_sym_LPAREN,
    ACTIONS(377), 1,
      anon_sym_ASSERT,
    ACTIONS(389), 1,
      anon_sym_ALIGN,
    ACTIONS(393), 1,
      anon_sym_SEGMENT_START,
    STATE(105), 1,
      sym_exp,
    STATE(109), 1,
      sym_INT,
    STATE(235), 1,
      sym_mustbe_exp,
    STATE(243), 1,
      sym_fill_exp,
    ACTIONS(385), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(387), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(395), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(381), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(391), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(383), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(379), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [3101] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(397), 1,
      anon_sym_LPAREN,
    ACTIONS(399), 1,
      anon_sym_ASSERT,
    ACTIONS(411), 1,
      anon_sym_ALIGN,
    ACTIONS(415), 1,
      anon_sym_SEGMENT_START,
    STATE(146), 1,
      sym_INT,
    STATE(149), 1,
      sym_exp,
    STATE(428), 1,
      sym_fill_exp,
    STATE(446), 1,
      sym_mustbe_exp,
    ACTIONS(407), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(409), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(417), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(403), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(413), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(405), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(401), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [3169] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    ACTIONS(419), 1,
      anon_sym_COLON,
    STATE(124), 1,
      sym_INT,
    STATE(183), 1,
      sym_exp,
    STATE(316), 1,
      sym_opt_exp_without_type,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [3237] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(375), 1,
      anon_sym_LPAREN,
    ACTIONS(377), 1,
      anon_sym_ASSERT,
    ACTIONS(389), 1,
      anon_sym_ALIGN,
    ACTIONS(393), 1,
      anon_sym_SEGMENT_START,
    STATE(105), 1,
      sym_exp,
    STATE(109), 1,
      sym_INT,
    STATE(235), 1,
      sym_mustbe_exp,
    STATE(244), 1,
      sym_fill_exp,
    ACTIONS(385), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(387), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(395), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(381), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(391), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(383), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(379), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [3305] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(375), 1,
      anon_sym_LPAREN,
    ACTIONS(377), 1,
      anon_sym_ASSERT,
    ACTIONS(389), 1,
      anon_sym_ALIGN,
    ACTIONS(393), 1,
      anon_sym_SEGMENT_START,
    STATE(105), 1,
      sym_exp,
    STATE(109), 1,
      sym_INT,
    STATE(235), 1,
      sym_mustbe_exp,
    STATE(252), 1,
      sym_fill_exp,
    ACTIONS(385), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(387), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(395), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(381), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(391), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(383), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(379), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [3373] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(148), 1,
      sym_exp,
    STATE(235), 1,
      sym_mustbe_exp,
    STATE(554), 1,
      sym_fill_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [3441] = 15,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(148), 1,
      sym_exp,
    STATE(379), 1,
      sym_mustbe_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [3506] = 15,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(397), 1,
      anon_sym_LPAREN,
    ACTIONS(399), 1,
      anon_sym_ASSERT,
    ACTIONS(411), 1,
      anon_sym_ALIGN,
    ACTIONS(415), 1,
      anon_sym_SEGMENT_START,
    STATE(146), 1,
      sym_INT,
    STATE(150), 1,
      sym_exp,
    STATE(362), 1,
      sym_phdr_type,
    ACTIONS(407), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(409), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(417), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(403), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(413), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(405), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(401), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [3571] = 15,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(148), 1,
      sym_exp,
    STATE(461), 1,
      sym_mustbe_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [3636] = 15,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(397), 1,
      anon_sym_LPAREN,
    ACTIONS(399), 1,
      anon_sym_ASSERT,
    ACTIONS(411), 1,
      anon_sym_ALIGN,
    ACTIONS(415), 1,
      anon_sym_SEGMENT_START,
    STATE(146), 1,
      sym_INT,
    STATE(149), 1,
      sym_exp,
    STATE(377), 1,
      sym_mustbe_exp,
    ACTIONS(407), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(409), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(417), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(403), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(413), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(405), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(401), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [3701] = 15,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(148), 1,
      sym_exp,
    STATE(554), 1,
      sym_mustbe_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [3766] = 15,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(148), 1,
      sym_exp,
    STATE(585), 1,
      sym_mustbe_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [3831] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(375), 1,
      anon_sym_LPAREN,
    ACTIONS(377), 1,
      anon_sym_ASSERT,
    ACTIONS(389), 1,
      anon_sym_ALIGN,
    ACTIONS(393), 1,
      anon_sym_SEGMENT_START,
    STATE(109), 1,
      sym_INT,
    STATE(112), 1,
      sym_exp,
    ACTIONS(385), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(387), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(395), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(381), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(391), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(383), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(379), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [3893] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(168), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [3955] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(184), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [4017] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(160), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [4079] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(166), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [4141] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(156), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [4203] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(375), 1,
      anon_sym_LPAREN,
    ACTIONS(377), 1,
      anon_sym_ASSERT,
    ACTIONS(389), 1,
      anon_sym_ALIGN,
    ACTIONS(393), 1,
      anon_sym_SEGMENT_START,
    STATE(109), 1,
      sym_INT,
    STATE(114), 1,
      sym_exp,
    ACTIONS(385), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(387), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(395), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(381), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(391), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(383), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(379), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [4265] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(155), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [4327] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(181), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [4389] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(116), 1,
      sym_exp,
    STATE(124), 1,
      sym_INT,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [4451] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(133), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [4513] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(158), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [4575] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(164), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [4637] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(161), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [4699] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(180), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [4761] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(162), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [4823] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(163), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [4885] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(185), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [4947] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(182), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [5009] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(177), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [5071] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(169), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [5133] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(165), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [5195] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(375), 1,
      anon_sym_LPAREN,
    ACTIONS(377), 1,
      anon_sym_ASSERT,
    ACTIONS(389), 1,
      anon_sym_ALIGN,
    ACTIONS(393), 1,
      anon_sym_SEGMENT_START,
    STATE(107), 1,
      sym_exp,
    STATE(109), 1,
      sym_INT,
    ACTIONS(385), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(387), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(395), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(381), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(391), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(383), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(379), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [5257] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(397), 1,
      anon_sym_LPAREN,
    ACTIONS(399), 1,
      anon_sym_ASSERT,
    ACTIONS(411), 1,
      anon_sym_ALIGN,
    ACTIONS(415), 1,
      anon_sym_SEGMENT_START,
    STATE(144), 1,
      sym_exp,
    STATE(146), 1,
      sym_INT,
    ACTIONS(407), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(409), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(417), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(403), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(413), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(405), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(401), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [5319] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(167), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [5381] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(154), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [5443] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(152), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [5505] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(179), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [5567] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(178), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [5629] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(157), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [5691] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(397), 1,
      anon_sym_LPAREN,
    ACTIONS(399), 1,
      anon_sym_ASSERT,
    ACTIONS(411), 1,
      anon_sym_ALIGN,
    ACTIONS(415), 1,
      anon_sym_SEGMENT_START,
    STATE(141), 1,
      sym_exp,
    STATE(146), 1,
      sym_INT,
    ACTIONS(407), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(409), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(417), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(403), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(413), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(405), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(401), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [5753] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(135), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [5815] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(175), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [5877] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(397), 1,
      anon_sym_LPAREN,
    ACTIONS(399), 1,
      anon_sym_ASSERT,
    ACTIONS(411), 1,
      anon_sym_ALIGN,
    ACTIONS(415), 1,
      anon_sym_SEGMENT_START,
    STATE(139), 1,
      sym_exp,
    STATE(146), 1,
      sym_INT,
    ACTIONS(407), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(409), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(417), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(403), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(413), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(405), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(401), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [5939] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(153), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [6001] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(159), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [6063] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(170), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [6125] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(172), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [6187] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(176), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [6249] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(171), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [6311] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(173), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [6373] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_ASSERT,
    ACTIONS(75), 1,
      anon_sym_ALIGN,
    ACTIONS(79), 1,
      anon_sym_SEGMENT_START,
    ACTIONS(158), 1,
      anon_sym_LPAREN,
    STATE(124), 1,
      sym_INT,
    STATE(174), 1,
      sym_exp,
    ACTIONS(71), 2,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
    ACTIONS(73), 2,
      anon_sym_SIZEOF_HEADERS,
      sym_SYMBOLNAME,
    ACTIONS(83), 3,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
    ACTIONS(65), 4,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(77), 4,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
    ACTIONS(69), 5,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
    ACTIONS(63), 6,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
  [6435] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(421), 5,
      anon_sym_LPAREN,
      anon_sym_BANG,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_TILDE,
    ACTIONS(423), 25,
      anon_sym_ASSERT,
      anon_sym_ORIGIN,
      anon_sym_LENGTH,
      anon_sym_NEXT,
      anon_sym_ABSOLUTE,
      anon_sym_DATA_SEGMENT_END,
      anon_sym_BLOCK,
      anon_sym_LOG2CEIL,
      anon_sym_DEFINED,
      anon_sym_CONSTANT,
      anon_sym_SIZEOF_HEADERS,
      anon_sym_ALIGNOF,
      anon_sym_SIZEOF,
      anon_sym_ADDR,
      anon_sym_LOADADDR,
      anon_sym_ALIGN,
      anon_sym_DATA_SEGMENT_ALIGN,
      anon_sym_DATA_SEGMENT_RELRO_END,
      anon_sym_MAX,
      anon_sym_MIN,
      anon_sym_SEGMENT_START,
      sym_SYMBOLNAME,
      aux_sym_INT_token1,
      aux_sym_INT_token2,
      aux_sym_INT_token3,
  [6473] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(433), 1,
      anon_sym_QMARK,
    ACTIONS(427), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
    ACTIONS(429), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(425), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
    ACTIONS(431), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [6517] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(435), 14,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_AMP,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_OVERLAY,
      sym_NAME,
    ACTIONS(437), 16,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [6555] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(439), 14,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_AMP,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_OVERLAY,
      sym_NAME,
    ACTIONS(441), 16,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [6593] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(443), 14,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_AMP,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_OVERLAY,
      sym_NAME,
    ACTIONS(445), 16,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [6631] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(447), 14,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_AMP,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_OVERLAY,
      sym_NAME,
    ACTIONS(449), 16,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [6669] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(451), 14,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_AMP,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_OVERLAY,
      sym_NAME,
    ACTIONS(453), 16,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [6707] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(455), 14,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_AMP,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_OVERLAY,
      sym_NAME,
    ACTIONS(457), 16,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [6745] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(455), 14,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_AMP,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_OVERLAY,
      sym_NAME,
    ACTIONS(457), 16,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [6783] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(459), 14,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_AMP,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_OVERLAY,
      sym_NAME,
    ACTIONS(461), 16,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [6821] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(459), 14,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_AMP,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_OVERLAY,
      sym_NAME,
    ACTIONS(461), 16,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [6859] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(463), 14,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_AMP,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_OVERLAY,
      sym_NAME,
    ACTIONS(465), 16,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [6897] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(439), 6,
      anon_sym_AMP,
      anon_sym_l,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(441), 21,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_COLON,
      anon_sym_LENGTH,
      anon_sym_len,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [6932] = 3,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(469), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
    ACTIONS(467), 25,
      anon_sym_INCLUDE,
      anon_sym_ASSERT,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_NONE,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      anon_sym_INPUT_SECTION_FLAGS,
      anon_sym_LBRACK,
      anon_sym_KEEP,
      anon_sym_CREATE_OBJECT_SYMBOLS,
      anon_sym_CONSTRUCTORS,
      anon_sym_ASCIZ,
      anon_sym_FILL,
      anon_sym_LINKER_VERSION,
      anon_sym_QUAD,
      anon_sym_SQUAD,
      anon_sym_LONG,
      anon_sym_SHORT,
      anon_sym_BYTE,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      sym_NAME,
      sym_wildcard_name,
  [6967] = 3,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(473), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
    ACTIONS(471), 25,
      anon_sym_INCLUDE,
      anon_sym_ASSERT,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_NONE,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      anon_sym_INPUT_SECTION_FLAGS,
      anon_sym_LBRACK,
      anon_sym_KEEP,
      anon_sym_CREATE_OBJECT_SYMBOLS,
      anon_sym_CONSTRUCTORS,
      anon_sym_ASCIZ,
      anon_sym_FILL,
      anon_sym_LINKER_VERSION,
      anon_sym_QUAD,
      anon_sym_SQUAD,
      anon_sym_LONG,
      anon_sym_SHORT,
      anon_sym_BYTE,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      sym_NAME,
      sym_wildcard_name,
  [7002] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(443), 6,
      anon_sym_AMP,
      anon_sym_l,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(445), 21,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_COLON,
      anon_sym_LENGTH,
      anon_sym_len,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [7037] = 3,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(477), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
    ACTIONS(475), 25,
      anon_sym_INCLUDE,
      anon_sym_ASSERT,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_NONE,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      anon_sym_INPUT_SECTION_FLAGS,
      anon_sym_LBRACK,
      anon_sym_KEEP,
      anon_sym_CREATE_OBJECT_SYMBOLS,
      anon_sym_CONSTRUCTORS,
      anon_sym_ASCIZ,
      anon_sym_FILL,
      anon_sym_LINKER_VERSION,
      anon_sym_QUAD,
      anon_sym_SQUAD,
      anon_sym_LONG,
      anon_sym_SHORT,
      anon_sym_BYTE,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      sym_NAME,
      sym_wildcard_name,
  [7072] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(463), 6,
      anon_sym_AMP,
      anon_sym_l,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(465), 21,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_COLON,
      anon_sym_LENGTH,
      anon_sym_len,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [7107] = 3,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(481), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
    ACTIONS(479), 25,
      anon_sym_INCLUDE,
      anon_sym_ASSERT,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_NONE,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      anon_sym_INPUT_SECTION_FLAGS,
      anon_sym_LBRACK,
      anon_sym_KEEP,
      anon_sym_CREATE_OBJECT_SYMBOLS,
      anon_sym_CONSTRUCTORS,
      anon_sym_ASCIZ,
      anon_sym_FILL,
      anon_sym_LINKER_VERSION,
      anon_sym_QUAD,
      anon_sym_SQUAD,
      anon_sym_LONG,
      anon_sym_SHORT,
      anon_sym_BYTE,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      sym_NAME,
      sym_wildcard_name,
  [7142] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(435), 6,
      anon_sym_AMP,
      anon_sym_l,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(437), 21,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_COLON,
      anon_sym_LENGTH,
      anon_sym_len,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [7177] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(447), 6,
      anon_sym_AMP,
      anon_sym_l,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(449), 21,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_COLON,
      anon_sym_LENGTH,
      anon_sym_len,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [7212] = 3,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(485), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
    ACTIONS(483), 25,
      anon_sym_INCLUDE,
      anon_sym_ASSERT,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_NONE,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      anon_sym_INPUT_SECTION_FLAGS,
      anon_sym_LBRACK,
      anon_sym_KEEP,
      anon_sym_CREATE_OBJECT_SYMBOLS,
      anon_sym_CONSTRUCTORS,
      anon_sym_ASCIZ,
      anon_sym_FILL,
      anon_sym_LINKER_VERSION,
      anon_sym_QUAD,
      anon_sym_SQUAD,
      anon_sym_LONG,
      anon_sym_SHORT,
      anon_sym_BYTE,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      sym_NAME,
      sym_wildcard_name,
  [7247] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(459), 6,
      anon_sym_AMP,
      anon_sym_l,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(461), 21,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_COLON,
      anon_sym_LENGTH,
      anon_sym_len,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [7282] = 3,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(287), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
    ACTIONS(289), 25,
      anon_sym_INCLUDE,
      anon_sym_ASSERT,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_NONE,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      anon_sym_INPUT_SECTION_FLAGS,
      anon_sym_LBRACK,
      anon_sym_KEEP,
      anon_sym_CREATE_OBJECT_SYMBOLS,
      anon_sym_CONSTRUCTORS,
      anon_sym_ASCIZ,
      anon_sym_FILL,
      anon_sym_LINKER_VERSION,
      anon_sym_QUAD,
      anon_sym_SQUAD,
      anon_sym_LONG,
      anon_sym_SHORT,
      anon_sym_BYTE,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      sym_NAME,
      sym_wildcard_name,
  [7317] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(451), 6,
      anon_sym_AMP,
      anon_sym_l,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(453), 21,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_COLON,
      anon_sym_LENGTH,
      anon_sym_len,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [7352] = 3,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(489), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
    ACTIONS(487), 25,
      anon_sym_INCLUDE,
      anon_sym_ASSERT,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_NONE,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      anon_sym_INPUT_SECTION_FLAGS,
      anon_sym_LBRACK,
      anon_sym_KEEP,
      anon_sym_CREATE_OBJECT_SYMBOLS,
      anon_sym_CONSTRUCTORS,
      anon_sym_ASCIZ,
      anon_sym_FILL,
      anon_sym_LINKER_VERSION,
      anon_sym_QUAD,
      anon_sym_SQUAD,
      anon_sym_LONG,
      anon_sym_SHORT,
      anon_sym_BYTE,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      sym_NAME,
      sym_wildcard_name,
  [7387] = 3,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(493), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
    ACTIONS(491), 25,
      anon_sym_INCLUDE,
      anon_sym_ASSERT,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_NONE,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      anon_sym_INPUT_SECTION_FLAGS,
      anon_sym_LBRACK,
      anon_sym_KEEP,
      anon_sym_CREATE_OBJECT_SYMBOLS,
      anon_sym_CONSTRUCTORS,
      anon_sym_ASCIZ,
      anon_sym_FILL,
      anon_sym_LINKER_VERSION,
      anon_sym_QUAD,
      anon_sym_SQUAD,
      anon_sym_LONG,
      anon_sym_SHORT,
      anon_sym_BYTE,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      sym_NAME,
      sym_wildcard_name,
  [7422] = 3,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(497), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
    ACTIONS(495), 25,
      anon_sym_INCLUDE,
      anon_sym_ASSERT,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_NONE,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      anon_sym_INPUT_SECTION_FLAGS,
      anon_sym_LBRACK,
      anon_sym_KEEP,
      anon_sym_CREATE_OBJECT_SYMBOLS,
      anon_sym_CONSTRUCTORS,
      anon_sym_ASCIZ,
      anon_sym_FILL,
      anon_sym_LINKER_VERSION,
      anon_sym_QUAD,
      anon_sym_SQUAD,
      anon_sym_LONG,
      anon_sym_SHORT,
      anon_sym_BYTE,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      sym_NAME,
      sym_wildcard_name,
  [7457] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(455), 6,
      anon_sym_AMP,
      anon_sym_l,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(457), 21,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_COLON,
      anon_sym_LENGTH,
      anon_sym_len,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [7492] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(455), 6,
      anon_sym_AMP,
      anon_sym_l,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(457), 21,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_COLON,
      anon_sym_LENGTH,
      anon_sym_len,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [7527] = 3,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(501), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
    ACTIONS(499), 25,
      anon_sym_INCLUDE,
      anon_sym_ASSERT,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_NONE,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      anon_sym_INPUT_SECTION_FLAGS,
      anon_sym_LBRACK,
      anon_sym_KEEP,
      anon_sym_CREATE_OBJECT_SYMBOLS,
      anon_sym_CONSTRUCTORS,
      anon_sym_ASCIZ,
      anon_sym_FILL,
      anon_sym_LINKER_VERSION,
      anon_sym_QUAD,
      anon_sym_SQUAD,
      anon_sym_LONG,
      anon_sym_SHORT,
      anon_sym_BYTE,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      sym_NAME,
      sym_wildcard_name,
  [7562] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(459), 6,
      anon_sym_AMP,
      anon_sym_l,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(461), 21,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_COLON,
      anon_sym_LENGTH,
      anon_sym_len,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [7597] = 3,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(505), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
    ACTIONS(503), 25,
      anon_sym_INCLUDE,
      anon_sym_ASSERT,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_NONE,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      anon_sym_INPUT_SECTION_FLAGS,
      anon_sym_LBRACK,
      anon_sym_KEEP,
      anon_sym_CREATE_OBJECT_SYMBOLS,
      anon_sym_CONSTRUCTORS,
      anon_sym_ASCIZ,
      anon_sym_FILL,
      anon_sym_LINKER_VERSION,
      anon_sym_QUAD,
      anon_sym_SQUAD,
      anon_sym_LONG,
      anon_sym_SHORT,
      anon_sym_BYTE,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      sym_NAME,
      sym_wildcard_name,
  [7632] = 3,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(279), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
    ACTIONS(281), 25,
      anon_sym_INCLUDE,
      anon_sym_ASSERT,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_NONE,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      anon_sym_INPUT_SECTION_FLAGS,
      anon_sym_LBRACK,
      anon_sym_KEEP,
      anon_sym_CREATE_OBJECT_SYMBOLS,
      anon_sym_CONSTRUCTORS,
      anon_sym_ASCIZ,
      anon_sym_FILL,
      anon_sym_LINKER_VERSION,
      anon_sym_QUAD,
      anon_sym_SQUAD,
      anon_sym_LONG,
      anon_sym_SHORT,
      anon_sym_BYTE,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      sym_NAME,
      sym_wildcard_name,
  [7667] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(455), 8,
      anon_sym_INCLUDE,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_AT,
      sym_NAME,
    ACTIONS(457), 17,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [7700] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(455), 8,
      anon_sym_INCLUDE,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_AT,
      sym_NAME,
    ACTIONS(457), 17,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [7733] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(459), 8,
      anon_sym_INCLUDE,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_AT,
      sym_NAME,
    ACTIONS(461), 17,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [7766] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(459), 8,
      anon_sym_INCLUDE,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_AT,
      sym_NAME,
    ACTIONS(461), 17,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [7799] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(463), 8,
      anon_sym_INCLUDE,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_AT,
      sym_NAME,
    ACTIONS(465), 17,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [7832] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(443), 8,
      anon_sym_INCLUDE,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_AT,
      sym_NAME,
    ACTIONS(445), 17,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [7865] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(439), 8,
      anon_sym_INCLUDE,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_AT,
      sym_NAME,
    ACTIONS(441), 17,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [7898] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(451), 8,
      anon_sym_INCLUDE,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_AT,
      sym_NAME,
    ACTIONS(453), 17,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [7931] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(447), 8,
      anon_sym_INCLUDE,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_AT,
      sym_NAME,
    ACTIONS(449), 17,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [7964] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(435), 8,
      anon_sym_INCLUDE,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_AT,
      sym_NAME,
    ACTIONS(437), 17,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_QMARK,
  [7997] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(425), 1,
      anon_sym_l,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(427), 5,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_LENGTH,
      anon_sym_len,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8036] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(517), 1,
      anon_sym_QMARK,
    ACTIONS(425), 2,
      anon_sym_INCLUDE,
      sym_NAME,
    ACTIONS(427), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
    ACTIONS(513), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(515), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8073] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(517), 1,
      anon_sym_QMARK,
    ACTIONS(521), 1,
      anon_sym_SEMI,
    ACTIONS(519), 2,
      anon_sym_AT,
      sym_NAME,
    ACTIONS(513), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(515), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8109] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(523), 1,
      anon_sym_LPAREN,
    ACTIONS(525), 1,
      anon_sym_COLON,
    STATE(561), 1,
      sym_atype,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8147] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(527), 1,
      anon_sym_COMMA,
    ACTIONS(529), 1,
      anon_sym_RPAREN,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8182] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(531), 1,
      anon_sym_COMMA,
    ACTIONS(533), 1,
      anon_sym_RPAREN,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8217] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(535), 1,
      anon_sym_COMMA,
    ACTIONS(537), 1,
      anon_sym_RPAREN,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8252] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(539), 1,
      anon_sym_RPAREN,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8284] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(541), 1,
      anon_sym_COMMA,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8316] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(543), 1,
      anon_sym_RPAREN,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8348] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(545), 1,
      anon_sym_COMMA,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8380] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(547), 1,
      anon_sym_RPAREN,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8412] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(549), 1,
      anon_sym_RPAREN,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8444] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(535), 1,
      anon_sym_COMMA,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8476] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(551), 1,
      anon_sym_COMMA,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8508] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(553), 1,
      anon_sym_COMMA,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8540] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(555), 1,
      anon_sym_RPAREN,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8572] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(557), 1,
      anon_sym_RPAREN,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8604] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(559), 1,
      anon_sym_RPAREN,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8636] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(561), 1,
      anon_sym_COLON,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8668] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(529), 1,
      anon_sym_RPAREN,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8700] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(527), 1,
      anon_sym_COMMA,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8732] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(563), 1,
      anon_sym_RPAREN,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8764] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(565), 1,
      anon_sym_COMMA,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8796] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(533), 1,
      anon_sym_RPAREN,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8828] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(567), 1,
      anon_sym_RPAREN,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8860] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(569), 1,
      anon_sym_RPAREN,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8892] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(531), 1,
      anon_sym_COMMA,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8924] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(571), 1,
      anon_sym_COLON,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8956] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(573), 1,
      anon_sym_RPAREN,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [8988] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(575), 1,
      anon_sym_COLON,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [9020] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(537), 1,
      anon_sym_RPAREN,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [9052] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(577), 1,
      anon_sym_COMMA,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [9084] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(579), 1,
      anon_sym_RPAREN,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [9116] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(581), 1,
      anon_sym_RPAREN,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [9148] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(583), 1,
      anon_sym_COLON,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [9180] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(585), 1,
      anon_sym_RPAREN,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [9212] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(511), 1,
      anon_sym_QMARK,
    ACTIONS(587), 1,
      anon_sym_RPAREN,
    ACTIONS(507), 5,
      anon_sym_AMP,
      anon_sym_SLASH,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
    ACTIONS(509), 13,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_PERCENT,
      anon_sym_LT_LT,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_CARET,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
  [9244] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(591), 1,
      anon_sym_COMMA,
    ACTIONS(593), 1,
      anon_sym_RBRACE,
    ACTIONS(595), 1,
      anon_sym_EQ,
    ACTIONS(597), 1,
      anon_sym_COLON,
    ACTIONS(599), 1,
      anon_sym_GT,
    ACTIONS(601), 1,
      anon_sym_AT,
    STATE(195), 1,
      sym_memspec,
    STATE(204), 1,
      sym_memspec_at,
    STATE(225), 1,
      sym_phdr_opt,
    ACTIONS(589), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [9286] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(597), 1,
      anon_sym_COLON,
    ACTIONS(599), 1,
      anon_sym_GT,
    ACTIONS(601), 1,
      anon_sym_AT,
    ACTIONS(605), 1,
      anon_sym_COMMA,
    ACTIONS(607), 1,
      anon_sym_RBRACE,
    ACTIONS(609), 1,
      anon_sym_EQ,
    STATE(198), 1,
      sym_memspec,
    STATE(205), 1,
      sym_memspec_at,
    STATE(224), 1,
      sym_phdr_opt,
    ACTIONS(603), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [9328] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(597), 1,
      anon_sym_COLON,
    ACTIONS(599), 1,
      anon_sym_GT,
    ACTIONS(601), 1,
      anon_sym_AT,
    ACTIONS(613), 1,
      anon_sym_COMMA,
    ACTIONS(615), 1,
      anon_sym_RBRACE,
    ACTIONS(617), 1,
      anon_sym_EQ,
    STATE(197), 1,
      sym_memspec,
    STATE(211), 1,
      sym_memspec_at,
    STATE(221), 1,
      sym_phdr_opt,
    ACTIONS(611), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [9370] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(597), 1,
      anon_sym_COLON,
    ACTIONS(599), 1,
      anon_sym_GT,
    ACTIONS(601), 1,
      anon_sym_AT,
    ACTIONS(621), 1,
      anon_sym_COMMA,
    ACTIONS(623), 1,
      anon_sym_RBRACE,
    ACTIONS(625), 1,
      anon_sym_EQ,
    STATE(199), 1,
      sym_memspec,
    STATE(207), 1,
      sym_memspec_at,
    STATE(222), 1,
      sym_phdr_opt,
    ACTIONS(619), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [9412] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(597), 1,
      anon_sym_COLON,
    ACTIONS(599), 1,
      anon_sym_GT,
    ACTIONS(601), 1,
      anon_sym_AT,
    ACTIONS(629), 1,
      anon_sym_COMMA,
    ACTIONS(631), 1,
      anon_sym_RBRACE,
    ACTIONS(633), 1,
      anon_sym_EQ,
    STATE(196), 1,
      sym_memspec,
    STATE(209), 1,
      sym_memspec_at,
    STATE(231), 1,
      sym_phdr_opt,
    ACTIONS(627), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [9454] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(597), 1,
      anon_sym_COLON,
    ACTIONS(599), 1,
      anon_sym_GT,
    ACTIONS(601), 1,
      anon_sym_AT,
    ACTIONS(637), 1,
      anon_sym_COMMA,
    ACTIONS(639), 1,
      anon_sym_RBRACE,
    ACTIONS(641), 1,
      anon_sym_EQ,
    STATE(194), 1,
      sym_memspec,
    STATE(202), 1,
      sym_memspec_at,
    STATE(230), 1,
      sym_phdr_opt,
    ACTIONS(635), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [9496] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(597), 1,
      anon_sym_COLON,
    ACTIONS(599), 1,
      anon_sym_GT,
    ACTIONS(601), 1,
      anon_sym_AT,
    ACTIONS(645), 1,
      anon_sym_COMMA,
    ACTIONS(647), 1,
      anon_sym_RBRACE,
    ACTIONS(649), 1,
      anon_sym_EQ,
    STATE(193), 1,
      sym_memspec,
    STATE(212), 1,
      sym_memspec_at,
    STATE(226), 1,
      sym_phdr_opt,
    ACTIONS(643), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [9538] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(591), 1,
      anon_sym_COMMA,
    ACTIONS(593), 1,
      anon_sym_RBRACE,
    ACTIONS(595), 1,
      anon_sym_EQ,
    ACTIONS(597), 1,
      anon_sym_COLON,
    ACTIONS(601), 1,
      anon_sym_AT,
    STATE(204), 1,
      sym_memspec_at,
    STATE(225), 1,
      sym_phdr_opt,
    ACTIONS(589), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [9574] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(597), 1,
      anon_sym_COLON,
    ACTIONS(601), 1,
      anon_sym_AT,
    ACTIONS(613), 1,
      anon_sym_COMMA,
    ACTIONS(615), 1,
      anon_sym_RBRACE,
    ACTIONS(617), 1,
      anon_sym_EQ,
    STATE(211), 1,
      sym_memspec_at,
    STATE(221), 1,
      sym_phdr_opt,
    ACTIONS(611), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [9610] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(597), 1,
      anon_sym_COLON,
    ACTIONS(601), 1,
      anon_sym_AT,
    ACTIONS(653), 1,
      anon_sym_COMMA,
    ACTIONS(655), 1,
      anon_sym_RBRACE,
    ACTIONS(657), 1,
      anon_sym_EQ,
    STATE(208), 1,
      sym_memspec_at,
    STATE(223), 1,
      sym_phdr_opt,
    ACTIONS(651), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [9646] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(597), 1,
      anon_sym_COLON,
    ACTIONS(601), 1,
      anon_sym_AT,
    ACTIONS(621), 1,
      anon_sym_COMMA,
    ACTIONS(623), 1,
      anon_sym_RBRACE,
    ACTIONS(625), 1,
      anon_sym_EQ,
    STATE(207), 1,
      sym_memspec_at,
    STATE(222), 1,
      sym_phdr_opt,
    ACTIONS(619), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [9682] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(597), 1,
      anon_sym_COLON,
    ACTIONS(601), 1,
      anon_sym_AT,
    ACTIONS(629), 1,
      anon_sym_COMMA,
    ACTIONS(631), 1,
      anon_sym_RBRACE,
    ACTIONS(633), 1,
      anon_sym_EQ,
    STATE(209), 1,
      sym_memspec_at,
    STATE(231), 1,
      sym_phdr_opt,
    ACTIONS(627), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [9718] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(597), 1,
      anon_sym_COLON,
    ACTIONS(601), 1,
      anon_sym_AT,
    ACTIONS(645), 1,
      anon_sym_COMMA,
    ACTIONS(647), 1,
      anon_sym_RBRACE,
    ACTIONS(649), 1,
      anon_sym_EQ,
    STATE(212), 1,
      sym_memspec_at,
    STATE(226), 1,
      sym_phdr_opt,
    ACTIONS(643), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [9754] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(597), 1,
      anon_sym_COLON,
    ACTIONS(601), 1,
      anon_sym_AT,
    ACTIONS(605), 1,
      anon_sym_COMMA,
    ACTIONS(607), 1,
      anon_sym_RBRACE,
    ACTIONS(609), 1,
      anon_sym_EQ,
    STATE(205), 1,
      sym_memspec_at,
    STATE(224), 1,
      sym_phdr_opt,
    ACTIONS(603), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [9790] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(659), 1,
      sym_NAME,
    ACTIONS(661), 1,
      anon_sym_GROUP,
    ACTIONS(663), 1,
      anon_sym_INCLUDE,
    ACTIONS(665), 1,
      anon_sym_RBRACE,
    ACTIONS(667), 1,
      anon_sym_ENTRY,
    ACTIONS(669), 1,
      anon_sym_ASSERT,
    ACTIONS(671), 1,
      anon_sym_OVERLAY,
    STATE(440), 1,
      sym_assignment,
    STATE(575), 1,
      sym_sec_or_group_p1,
    ACTIONS(37), 3,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
    STATE(203), 3,
      sym_statement_anywhere,
      sym_section,
      aux_sym_sec_or_group_p1_repeat1,
  [9831] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(659), 1,
      sym_NAME,
    ACTIONS(661), 1,
      anon_sym_GROUP,
    ACTIONS(663), 1,
      anon_sym_INCLUDE,
    ACTIONS(667), 1,
      anon_sym_ENTRY,
    ACTIONS(669), 1,
      anon_sym_ASSERT,
    ACTIONS(671), 1,
      anon_sym_OVERLAY,
    ACTIONS(673), 1,
      anon_sym_RBRACE,
    STATE(440), 1,
      sym_assignment,
    STATE(618), 1,
      sym_sec_or_group_p1,
    ACTIONS(37), 3,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
    STATE(203), 3,
      sym_statement_anywhere,
      sym_section,
      aux_sym_sec_or_group_p1_repeat1,
  [9872] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(597), 1,
      anon_sym_COLON,
    ACTIONS(613), 1,
      anon_sym_COMMA,
    ACTIONS(615), 1,
      anon_sym_RBRACE,
    ACTIONS(617), 1,
      anon_sym_EQ,
    STATE(221), 1,
      sym_phdr_opt,
    ACTIONS(611), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [9902] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(659), 1,
      sym_NAME,
    ACTIONS(661), 1,
      anon_sym_GROUP,
    ACTIONS(663), 1,
      anon_sym_INCLUDE,
    ACTIONS(667), 1,
      anon_sym_ENTRY,
    ACTIONS(669), 1,
      anon_sym_ASSERT,
    ACTIONS(671), 1,
      anon_sym_OVERLAY,
    ACTIONS(675), 1,
      anon_sym_RBRACE,
    STATE(440), 1,
      sym_assignment,
    ACTIONS(37), 3,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
    STATE(210), 3,
      sym_statement_anywhere,
      sym_section,
      aux_sym_sec_or_group_p1_repeat1,
  [9940] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(597), 1,
      anon_sym_COLON,
    ACTIONS(653), 1,
      anon_sym_COMMA,
    ACTIONS(655), 1,
      anon_sym_RBRACE,
    ACTIONS(657), 1,
      anon_sym_EQ,
    STATE(223), 1,
      sym_phdr_opt,
    ACTIONS(651), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [9970] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(597), 1,
      anon_sym_COLON,
    ACTIONS(645), 1,
      anon_sym_COMMA,
    ACTIONS(647), 1,
      anon_sym_RBRACE,
    ACTIONS(649), 1,
      anon_sym_EQ,
    STATE(226), 1,
      sym_phdr_opt,
    ACTIONS(643), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [10000] = 11,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(677), 1,
      anon_sym_COMMA,
    ACTIONS(686), 1,
      anon_sym_REVERSE,
    ACTIONS(689), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(692), 1,
      anon_sym_RBRACK,
    ACTIONS(694), 1,
      sym_wildcard_name,
    STATE(265), 1,
      sym_wildcard_maybe_exclude,
    STATE(269), 1,
      sym_wildcard_maybe_reverse,
    ACTIONS(683), 2,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
    STATE(206), 2,
      sym_section_name_spec,
      aux_sym_section_name_list_repeat1,
    ACTIONS(680), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
  [10038] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(597), 1,
      anon_sym_COLON,
    ACTIONS(605), 1,
      anon_sym_COMMA,
    ACTIONS(607), 1,
      anon_sym_RBRACE,
    ACTIONS(609), 1,
      anon_sym_EQ,
    STATE(224), 1,
      sym_phdr_opt,
    ACTIONS(603), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [10068] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(597), 1,
      anon_sym_COLON,
    ACTIONS(699), 1,
      anon_sym_COMMA,
    ACTIONS(701), 1,
      anon_sym_RBRACE,
    ACTIONS(703), 1,
      anon_sym_EQ,
    STATE(229), 1,
      sym_phdr_opt,
    ACTIONS(697), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [10098] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(597), 1,
      anon_sym_COLON,
    ACTIONS(621), 1,
      anon_sym_COMMA,
    ACTIONS(623), 1,
      anon_sym_RBRACE,
    ACTIONS(625), 1,
      anon_sym_EQ,
    STATE(222), 1,
      sym_phdr_opt,
    ACTIONS(619), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [10128] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(705), 1,
      sym_NAME,
    ACTIONS(708), 1,
      anon_sym_GROUP,
    ACTIONS(711), 1,
      anon_sym_INCLUDE,
    ACTIONS(714), 1,
      anon_sym_RBRACE,
    ACTIONS(716), 1,
      anon_sym_ENTRY,
    ACTIONS(719), 1,
      anon_sym_ASSERT,
    ACTIONS(725), 1,
      anon_sym_OVERLAY,
    STATE(440), 1,
      sym_assignment,
    ACTIONS(722), 3,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
    STATE(210), 3,
      sym_statement_anywhere,
      sym_section,
      aux_sym_sec_or_group_p1_repeat1,
  [10166] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(597), 1,
      anon_sym_COLON,
    ACTIONS(629), 1,
      anon_sym_COMMA,
    ACTIONS(631), 1,
      anon_sym_RBRACE,
    ACTIONS(633), 1,
      anon_sym_EQ,
    STATE(231), 1,
      sym_phdr_opt,
    ACTIONS(627), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [10196] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(591), 1,
      anon_sym_COMMA,
    ACTIONS(593), 1,
      anon_sym_RBRACE,
    ACTIONS(595), 1,
      anon_sym_EQ,
    ACTIONS(597), 1,
      anon_sym_COLON,
    STATE(225), 1,
      sym_phdr_opt,
    ACTIONS(589), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [10226] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(730), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_COLON,
    ACTIONS(728), 11,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_EQ,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_AT,
      anon_sym_OVERLAY,
      sym_NAME,
  [10248] = 11,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(732), 1,
      anon_sym_COMMA,
    ACTIONS(738), 1,
      anon_sym_REVERSE,
    ACTIONS(740), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(742), 1,
      anon_sym_RBRACK,
    ACTIONS(744), 1,
      sym_wildcard_name,
    STATE(265), 1,
      sym_wildcard_maybe_exclude,
    STATE(269), 1,
      sym_wildcard_maybe_reverse,
    ACTIONS(736), 2,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
    STATE(206), 2,
      sym_section_name_spec,
      aux_sym_section_name_list_repeat1,
    ACTIONS(734), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
  [10286] = 13,
    ACTIONS(182), 1,
      anon_sym_REVERSE,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(186), 1,
      anon_sym_INPUT_SECTION_FLAGS,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(746), 1,
      sym_NAME,
    ACTIONS(748), 1,
      anon_sym_LBRACK,
    STATE(249), 1,
      sym_sect_flags,
    STATE(464), 1,
      sym_wildcard_maybe_exclude,
    STATE(537), 1,
      sym_input_section_spec_no_keep,
    STATE(647), 1,
      sym_wildcard_maybe_reverse,
    STATE(702), 1,
      sym_filename_spec,
    ACTIONS(180), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_NONE,
  [10328] = 11,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(732), 1,
      anon_sym_COMMA,
    ACTIONS(738), 1,
      anon_sym_REVERSE,
    ACTIONS(740), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(744), 1,
      sym_wildcard_name,
    ACTIONS(750), 1,
      anon_sym_RBRACK,
    STATE(265), 1,
      sym_wildcard_maybe_exclude,
    STATE(269), 1,
      sym_wildcard_maybe_reverse,
    ACTIONS(736), 2,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
    STATE(214), 2,
      sym_section_name_spec,
      aux_sym_section_name_list_repeat1,
    ACTIONS(734), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
  [10366] = 11,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(752), 1,
      anon_sym_COMMA,
    ACTIONS(754), 1,
      anon_sym_RPAREN,
    ACTIONS(760), 1,
      anon_sym_REVERSE,
    ACTIONS(762), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(764), 1,
      sym_wildcard_name,
    STATE(270), 1,
      sym_wildcard_maybe_reverse,
    STATE(288), 1,
      sym_wildcard_maybe_exclude,
    ACTIONS(758), 2,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
    STATE(219), 2,
      sym_section_name_spec,
      aux_sym_section_name_list_repeat1,
    ACTIONS(756), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
  [10404] = 11,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(766), 1,
      anon_sym_COMMA,
    ACTIONS(769), 1,
      anon_sym_RPAREN,
    ACTIONS(777), 1,
      anon_sym_REVERSE,
    ACTIONS(780), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(783), 1,
      sym_wildcard_name,
    STATE(270), 1,
      sym_wildcard_maybe_reverse,
    STATE(288), 1,
      sym_wildcard_maybe_exclude,
    ACTIONS(774), 2,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
    STATE(218), 2,
      sym_section_name_spec,
      aux_sym_section_name_list_repeat1,
    ACTIONS(771), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
  [10442] = 11,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(752), 1,
      anon_sym_COMMA,
    ACTIONS(760), 1,
      anon_sym_REVERSE,
    ACTIONS(762), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(764), 1,
      sym_wildcard_name,
    ACTIONS(786), 1,
      anon_sym_RPAREN,
    STATE(270), 1,
      sym_wildcard_maybe_reverse,
    STATE(288), 1,
      sym_wildcard_maybe_exclude,
    ACTIONS(758), 2,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
    STATE(218), 2,
      sym_section_name_spec,
      aux_sym_section_name_list_repeat1,
    ACTIONS(756), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
  [10480] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(790), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_COLON,
    ACTIONS(788), 10,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_EQ,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [10501] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(629), 1,
      anon_sym_COMMA,
    ACTIONS(631), 1,
      anon_sym_RBRACE,
    ACTIONS(633), 1,
      anon_sym_EQ,
    ACTIONS(792), 1,
      anon_sym_COLON,
    ACTIONS(627), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [10528] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(605), 1,
      anon_sym_COMMA,
    ACTIONS(607), 1,
      anon_sym_RBRACE,
    ACTIONS(609), 1,
      anon_sym_EQ,
    ACTIONS(792), 1,
      anon_sym_COLON,
    ACTIONS(603), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [10555] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(699), 1,
      anon_sym_COMMA,
    ACTIONS(701), 1,
      anon_sym_RBRACE,
    ACTIONS(703), 1,
      anon_sym_EQ,
    ACTIONS(792), 1,
      anon_sym_COLON,
    ACTIONS(697), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [10582] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(645), 1,
      anon_sym_COMMA,
    ACTIONS(647), 1,
      anon_sym_RBRACE,
    ACTIONS(649), 1,
      anon_sym_EQ,
    ACTIONS(792), 1,
      anon_sym_COLON,
    ACTIONS(643), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [10609] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(653), 1,
      anon_sym_COMMA,
    ACTIONS(655), 1,
      anon_sym_RBRACE,
    ACTIONS(657), 1,
      anon_sym_EQ,
    ACTIONS(792), 1,
      anon_sym_COLON,
    ACTIONS(651), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [10636] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(591), 1,
      anon_sym_COMMA,
    ACTIONS(593), 1,
      anon_sym_RBRACE,
    ACTIONS(595), 1,
      anon_sym_EQ,
    ACTIONS(792), 1,
      anon_sym_COLON,
    ACTIONS(589), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [10663] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(796), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_COLON,
    ACTIONS(794), 10,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_EQ,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [10684] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(800), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_COLON,
    ACTIONS(798), 10,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_EQ,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [10705] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(792), 1,
      anon_sym_COLON,
    ACTIONS(804), 1,
      anon_sym_COMMA,
    ACTIONS(806), 1,
      anon_sym_RBRACE,
    ACTIONS(808), 1,
      anon_sym_EQ,
    ACTIONS(802), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [10732] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(613), 1,
      anon_sym_COMMA,
    ACTIONS(615), 1,
      anon_sym_RBRACE,
    ACTIONS(617), 1,
      anon_sym_EQ,
    ACTIONS(792), 1,
      anon_sym_COLON,
    ACTIONS(611), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [10759] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(621), 1,
      anon_sym_COMMA,
    ACTIONS(623), 1,
      anon_sym_RBRACE,
    ACTIONS(625), 1,
      anon_sym_EQ,
    ACTIONS(792), 1,
      anon_sym_COLON,
    ACTIONS(619), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [10786] = 10,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(738), 1,
      anon_sym_REVERSE,
    ACTIONS(740), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(744), 1,
      sym_wildcard_name,
    STATE(216), 1,
      sym_section_name_spec,
    STATE(265), 1,
      sym_wildcard_maybe_exclude,
    STATE(269), 1,
      sym_wildcard_maybe_reverse,
    STATE(534), 1,
      sym_section_name_list,
    ACTIONS(736), 2,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
    ACTIONS(734), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
  [10820] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(810), 1,
      anon_sym_LBRACE,
    ACTIONS(812), 1,
      anon_sym_ALIGN,
    ACTIONS(814), 1,
      anon_sym_AT,
    ACTIONS(816), 1,
      anon_sym_SUBALIGN,
    ACTIONS(820), 1,
      anon_sym_ALIGN_WITH_INPUT,
    STATE(267), 1,
      sym_at,
    STATE(302), 1,
      sym_align,
    STATE(370), 1,
      sym_subalign,
    STATE(574), 1,
      sym_sect_constraint,
    ACTIONS(818), 3,
      anon_sym_ONLY_IF_RO,
      anon_sym_ONLY_IF_RW,
      anon_sym_SPECIAL,
  [10856] = 10,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(738), 1,
      anon_sym_REVERSE,
    ACTIONS(740), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(744), 1,
      sym_wildcard_name,
    STATE(216), 1,
      sym_section_name_spec,
    STATE(265), 1,
      sym_wildcard_maybe_exclude,
    STATE(269), 1,
      sym_wildcard_maybe_reverse,
    STATE(649), 1,
      sym_section_name_list,
    ACTIONS(736), 2,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
    ACTIONS(734), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
  [10890] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(824), 3,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_RBRACE,
    ACTIONS(822), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [10910] = 10,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(738), 1,
      anon_sym_REVERSE,
    ACTIONS(740), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(744), 1,
      sym_wildcard_name,
    STATE(216), 1,
      sym_section_name_spec,
    STATE(265), 1,
      sym_wildcard_maybe_exclude,
    STATE(269), 1,
      sym_wildcard_maybe_reverse,
    STATE(592), 1,
      sym_section_name_list,
    ACTIONS(736), 2,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
    ACTIONS(734), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
  [10944] = 10,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(760), 1,
      anon_sym_REVERSE,
    ACTIONS(762), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(764), 1,
      sym_wildcard_name,
    STATE(217), 1,
      sym_section_name_spec,
    STATE(270), 1,
      sym_wildcard_maybe_reverse,
    STATE(288), 1,
      sym_wildcard_maybe_exclude,
    STATE(648), 1,
      sym_section_name_list,
    ACTIONS(758), 2,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
    ACTIONS(756), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
  [10978] = 10,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(738), 1,
      anon_sym_REVERSE,
    ACTIONS(740), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(744), 1,
      sym_wildcard_name,
    STATE(216), 1,
      sym_section_name_spec,
    STATE(265), 1,
      sym_wildcard_maybe_exclude,
    STATE(269), 1,
      sym_wildcard_maybe_reverse,
    STATE(642), 1,
      sym_section_name_list,
    ACTIONS(736), 2,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
    ACTIONS(734), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
  [11012] = 10,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(760), 1,
      anon_sym_REVERSE,
    ACTIONS(762), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(764), 1,
      sym_wildcard_name,
    STATE(217), 1,
      sym_section_name_spec,
    STATE(270), 1,
      sym_wildcard_maybe_reverse,
    STATE(288), 1,
      sym_wildcard_maybe_exclude,
    STATE(514), 1,
      sym_section_name_list,
    ACTIONS(758), 2,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
    ACTIONS(756), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
  [11046] = 10,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(760), 1,
      anon_sym_REVERSE,
    ACTIONS(762), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(764), 1,
      sym_wildcard_name,
    STATE(217), 1,
      sym_section_name_spec,
    STATE(270), 1,
      sym_wildcard_maybe_reverse,
    STATE(288), 1,
      sym_wildcard_maybe_exclude,
    STATE(652), 1,
      sym_section_name_list,
    ACTIONS(758), 2,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
    ACTIONS(756), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
  [11080] = 10,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(760), 1,
      anon_sym_REVERSE,
    ACTIONS(762), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(764), 1,
      sym_wildcard_name,
    STATE(217), 1,
      sym_section_name_spec,
    STATE(270), 1,
      sym_wildcard_maybe_reverse,
    STATE(288), 1,
      sym_wildcard_maybe_exclude,
    STATE(535), 1,
      sym_section_name_list,
    ACTIONS(758), 2,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
    ACTIONS(756), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
  [11114] = 9,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(760), 1,
      anon_sym_REVERSE,
    ACTIONS(762), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(764), 1,
      sym_wildcard_name,
    STATE(270), 1,
      sym_wildcard_maybe_reverse,
    STATE(277), 1,
      sym_section_name_spec,
    STATE(288), 1,
      sym_wildcard_maybe_exclude,
    ACTIONS(758), 2,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
    ACTIONS(756), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
  [11145] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(653), 1,
      anon_sym_COMMA,
    ACTIONS(655), 1,
      anon_sym_RBRACE,
    ACTIONS(651), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11166] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(645), 1,
      anon_sym_COMMA,
    ACTIONS(647), 1,
      anon_sym_RBRACE,
    ACTIONS(643), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11187] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(629), 1,
      anon_sym_COMMA,
    ACTIONS(631), 1,
      anon_sym_RBRACE,
    ACTIONS(627), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11208] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(59), 1,
      anon_sym_EQ,
    STATE(58), 1,
      sym_assign_op,
    ACTIONS(57), 9,
      anon_sym_PLUS_EQ,
      anon_sym_DASH_EQ,
      anon_sym_STAR_EQ,
      anon_sym_SLASH_EQ,
      anon_sym_LT_LT_EQ,
      anon_sym_GT_GT_EQ,
      anon_sym_AMP_EQ,
      anon_sym_PIPE_EQ,
      anon_sym_CARET_EQ,
  [11229] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(804), 1,
      anon_sym_COMMA,
    ACTIONS(806), 1,
      anon_sym_RBRACE,
    ACTIONS(802), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11250] = 10,
    ACTIONS(182), 1,
      anon_sym_REVERSE,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(826), 1,
      sym_NAME,
    ACTIONS(828), 1,
      anon_sym_LBRACK,
    STATE(464), 1,
      sym_wildcard_maybe_exclude,
    STATE(586), 1,
      sym_filename_spec,
    STATE(647), 1,
      sym_wildcard_maybe_reverse,
    ACTIONS(180), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_NONE,
  [11283] = 10,
    ACTIONS(182), 1,
      anon_sym_REVERSE,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(830), 1,
      sym_NAME,
    ACTIONS(832), 1,
      anon_sym_LBRACK,
    STATE(464), 1,
      sym_wildcard_maybe_exclude,
    STATE(647), 1,
      sym_wildcard_maybe_reverse,
    STATE(707), 1,
      sym_filename_spec,
    ACTIONS(180), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_NONE,
  [11316] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(621), 1,
      anon_sym_COMMA,
    ACTIONS(623), 1,
      anon_sym_RBRACE,
    ACTIONS(619), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11337] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(699), 1,
      anon_sym_COMMA,
    ACTIONS(701), 1,
      anon_sym_RBRACE,
    ACTIONS(697), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11358] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(591), 1,
      anon_sym_COMMA,
    ACTIONS(593), 1,
      anon_sym_RBRACE,
    ACTIONS(589), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11379] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(605), 1,
      anon_sym_COMMA,
    ACTIONS(607), 1,
      anon_sym_RBRACE,
    ACTIONS(603), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11400] = 9,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(738), 1,
      anon_sym_REVERSE,
    ACTIONS(740), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(744), 1,
      sym_wildcard_name,
    STATE(265), 1,
      sym_wildcard_maybe_exclude,
    STATE(269), 1,
      sym_wildcard_maybe_reverse,
    STATE(276), 1,
      sym_section_name_spec,
    ACTIONS(736), 2,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
    ACTIONS(734), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
  [11431] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(836), 1,
      anon_sym_COMMA,
    ACTIONS(838), 1,
      anon_sym_RBRACE,
    ACTIONS(834), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11452] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(842), 1,
      anon_sym_COMMA,
    ACTIONS(844), 1,
      anon_sym_RBRACE,
    ACTIONS(840), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11473] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(655), 1,
      anon_sym_RBRACE,
    ACTIONS(651), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11491] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(593), 1,
      anon_sym_RBRACE,
    ACTIONS(589), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11509] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(647), 1,
      anon_sym_RBRACE,
    ACTIONS(643), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11527] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(287), 1,
      anon_sym_RBRACE,
    ACTIONS(289), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11545] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(283), 1,
      anon_sym_RBRACE,
    ACTIONS(285), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11563] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(311), 1,
      anon_sym_RBRACE,
    ACTIONS(313), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11581] = 2,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(846), 10,
      anon_sym_COMMA,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      anon_sym_RBRACK,
      sym_wildcard_name,
  [11597] = 2,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(848), 10,
      anon_sym_COMMA,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      anon_sym_RBRACK,
      sym_wildcard_name,
  [11613] = 2,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(850), 10,
      anon_sym_COMMA,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      anon_sym_RBRACK,
      sym_wildcard_name,
  [11629] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(639), 1,
      anon_sym_RBRACE,
    ACTIONS(635), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11647] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(812), 1,
      anon_sym_ALIGN,
    ACTIONS(816), 1,
      anon_sym_SUBALIGN,
    ACTIONS(852), 1,
      anon_sym_LBRACE,
    ACTIONS(854), 1,
      anon_sym_ALIGN_WITH_INPUT,
    STATE(301), 1,
      sym_align,
    STATE(374), 1,
      sym_subalign,
    STATE(635), 1,
      sym_sect_constraint,
    ACTIONS(818), 3,
      anon_sym_ONLY_IF_RO,
      anon_sym_ONLY_IF_RW,
      anon_sym_SPECIAL,
  [11677] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(355), 1,
      anon_sym_RBRACE,
    ACTIONS(357), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11695] = 2,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(856), 10,
      anon_sym_COMMA,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      anon_sym_RBRACK,
      sym_wildcard_name,
  [11711] = 3,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(858), 1,
      anon_sym_RPAREN,
    ACTIONS(856), 9,
      anon_sym_COMMA,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      sym_wildcard_name,
  [11729] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(607), 1,
      anon_sym_RBRACE,
    ACTIONS(603), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11747] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(862), 1,
      anon_sym_RBRACE,
    ACTIONS(860), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11765] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(838), 1,
      anon_sym_RBRACE,
    ACTIONS(834), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11783] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(844), 1,
      anon_sym_RBRACE,
    ACTIONS(840), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11801] = 2,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(864), 10,
      anon_sym_COMMA,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      anon_sym_RBRACK,
      sym_wildcard_name,
  [11817] = 2,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(692), 10,
      anon_sym_COMMA,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      anon_sym_RBRACK,
      sym_wildcard_name,
  [11833] = 3,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(769), 1,
      anon_sym_RPAREN,
    ACTIONS(692), 9,
      anon_sym_COMMA,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      sym_wildcard_name,
  [11851] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(631), 1,
      anon_sym_RBRACE,
    ACTIONS(627), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11869] = 2,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(866), 10,
      anon_sym_COMMA,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      anon_sym_RBRACK,
      sym_wildcard_name,
  [11885] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(806), 1,
      anon_sym_RBRACE,
    ACTIONS(802), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11903] = 3,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(868), 1,
      anon_sym_RPAREN,
    ACTIONS(846), 9,
      anon_sym_COMMA,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      sym_wildcard_name,
  [11921] = 3,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(872), 1,
      anon_sym_RPAREN,
    ACTIONS(870), 9,
      anon_sym_COMMA,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      sym_wildcard_name,
  [11939] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(615), 1,
      anon_sym_RBRACE,
    ACTIONS(611), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11957] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      anon_sym_RBRACE,
    ACTIONS(281), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [11975] = 3,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(874), 1,
      anon_sym_RPAREN,
    ACTIONS(848), 9,
      anon_sym_COMMA,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      sym_wildcard_name,
  [11993] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(623), 1,
      anon_sym_RBRACE,
    ACTIONS(619), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [12011] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(701), 1,
      anon_sym_RBRACE,
    ACTIONS(697), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [12029] = 3,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(876), 1,
      anon_sym_RPAREN,
    ACTIONS(850), 9,
      anon_sym_COMMA,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      sym_wildcard_name,
  [12047] = 2,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(870), 10,
      anon_sym_COMMA,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      anon_sym_RBRACK,
      sym_wildcard_name,
  [12063] = 3,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(878), 1,
      anon_sym_RPAREN,
    ACTIONS(866), 9,
      anon_sym_COMMA,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      sym_wildcard_name,
  [12081] = 3,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(880), 1,
      anon_sym_RPAREN,
    ACTIONS(864), 9,
      anon_sym_COMMA,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
      anon_sym_SORT_NONE,
      anon_sym_SORT_BY_INIT_PRIORITY,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      sym_wildcard_name,
  [12099] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(884), 1,
      anon_sym_RBRACE,
    ACTIONS(882), 9,
      anon_sym_GROUP,
      anon_sym_INCLUDE,
      anon_sym_ENTRY,
      anon_sym_ASSERT,
      anon_sym_HIDDEN,
      anon_sym_PROVIDE,
      anon_sym_PROVIDE_HIDDEN,
      anon_sym_OVERLAY,
      sym_NAME,
  [12117] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(160), 1,
      anon_sym_RPAREN,
    ACTIONS(888), 1,
      anon_sym_READONLY,
    ACTIONS(890), 1,
      anon_sym_TYPE,
    STATE(543), 1,
      sym_type,
    ACTIONS(886), 5,
      anon_sym_OVERLAY,
      anon_sym_NOLOAD,
      anon_sym_DSECT,
      anon_sym_COPY,
      anon_sym_INFO,
  [12140] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(894), 1,
      anon_sym_ALIGN,
    ACTIONS(892), 7,
      anon_sym_LBRACE,
      anon_sym_AT,
      anon_sym_SUBALIGN,
      anon_sym_ONLY_IF_RO,
      anon_sym_ONLY_IF_RW,
      anon_sym_SPECIAL,
      anon_sym_ALIGN_WITH_INPUT,
  [12156] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(898), 1,
      anon_sym_ALIGN,
    ACTIONS(896), 7,
      anon_sym_LBRACE,
      anon_sym_AT,
      anon_sym_SUBALIGN,
      anon_sym_ONLY_IF_RO,
      anon_sym_ONLY_IF_RW,
      anon_sym_SPECIAL,
      anon_sym_ALIGN_WITH_INPUT,
  [12172] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(902), 1,
      anon_sym_ALIGN,
    ACTIONS(900), 7,
      anon_sym_LBRACE,
      anon_sym_AT,
      anon_sym_SUBALIGN,
      anon_sym_ONLY_IF_RO,
      anon_sym_ONLY_IF_RW,
      anon_sym_SPECIAL,
      anon_sym_ALIGN_WITH_INPUT,
  [12188] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(906), 1,
      anon_sym_ALIGN,
    ACTIONS(904), 7,
      anon_sym_LBRACE,
      anon_sym_AT,
      anon_sym_SUBALIGN,
      anon_sym_ONLY_IF_RO,
      anon_sym_ONLY_IF_RW,
      anon_sym_SPECIAL,
      anon_sym_ALIGN_WITH_INPUT,
  [12204] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(910), 1,
      anon_sym_ALIGN,
    ACTIONS(908), 7,
      anon_sym_LBRACE,
      anon_sym_AT,
      anon_sym_SUBALIGN,
      anon_sym_ONLY_IF_RO,
      anon_sym_ONLY_IF_RW,
      anon_sym_SPECIAL,
      anon_sym_ALIGN_WITH_INPUT,
  [12220] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(914), 1,
      anon_sym_ALIGN,
    ACTIONS(912), 7,
      anon_sym_LBRACE,
      anon_sym_AT,
      anon_sym_SUBALIGN,
      anon_sym_ONLY_IF_RO,
      anon_sym_ONLY_IF_RW,
      anon_sym_SPECIAL,
      anon_sym_ALIGN_WITH_INPUT,
  [12236] = 7,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(918), 1,
      anon_sym_REVERSE,
    STATE(464), 1,
      sym_wildcard_maybe_exclude,
    STATE(520), 1,
      sym_wildcard_maybe_reverse,
    ACTIONS(916), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
  [12260] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(816), 1,
      anon_sym_SUBALIGN,
    ACTIONS(920), 1,
      anon_sym_LBRACE,
    ACTIONS(922), 1,
      anon_sym_ALIGN_WITH_INPUT,
    STATE(373), 1,
      sym_subalign,
    STATE(579), 1,
      sym_sect_constraint,
    ACTIONS(818), 3,
      anon_sym_ONLY_IF_RO,
      anon_sym_ONLY_IF_RW,
      anon_sym_SPECIAL,
  [12284] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(816), 1,
      anon_sym_SUBALIGN,
    ACTIONS(852), 1,
      anon_sym_LBRACE,
    ACTIONS(854), 1,
      anon_sym_ALIGN_WITH_INPUT,
    STATE(374), 1,
      sym_subalign,
    STATE(635), 1,
      sym_sect_constraint,
    ACTIONS(818), 3,
      anon_sym_ONLY_IF_RO,
      anon_sym_ONLY_IF_RW,
      anon_sym_SPECIAL,
  [12308] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(926), 1,
      anon_sym_ALIGN,
    ACTIONS(924), 7,
      anon_sym_LBRACE,
      anon_sym_AT,
      anon_sym_SUBALIGN,
      anon_sym_ONLY_IF_RO,
      anon_sym_ONLY_IF_RW,
      anon_sym_SPECIAL,
      anon_sym_ALIGN_WITH_INPUT,
  [12324] = 2,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(928), 8,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_NONE,
      anon_sym_REVERSE,
      anon_sym_EXCLUDE_FILE,
      anon_sym_LBRACK,
      sym_NAME,
      sym_wildcard_name,
  [12338] = 7,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(918), 1,
      anon_sym_REVERSE,
    STATE(464), 1,
      sym_wildcard_maybe_exclude,
    STATE(651), 1,
      sym_wildcard_maybe_reverse,
    ACTIONS(930), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_ALIGNMENT,
  [12362] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(932), 1,
      anon_sym_RBRACE,
    ACTIONS(934), 1,
      anon_sym_global,
    ACTIONS(936), 1,
      anon_sym_local,
    ACTIONS(938), 1,
      anon_sym_extern,
    ACTIONS(940), 1,
      sym_VERS_IDENTIFIER,
    STATE(600), 1,
      sym_vers_defns,
    STATE(637), 1,
      sym_vers_tag,
  [12387] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(816), 1,
      anon_sym_SUBALIGN,
    ACTIONS(920), 1,
      anon_sym_LBRACE,
    STATE(373), 1,
      sym_subalign,
    STATE(579), 1,
      sym_sect_constraint,
    ACTIONS(818), 3,
      anon_sym_ONLY_IF_RO,
      anon_sym_ONLY_IF_RW,
      anon_sym_SPECIAL,
  [12408] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(816), 1,
      anon_sym_SUBALIGN,
    ACTIONS(852), 1,
      anon_sym_LBRACE,
    STATE(374), 1,
      sym_subalign,
    STATE(635), 1,
      sym_sect_constraint,
    ACTIONS(818), 3,
      anon_sym_ONLY_IF_RO,
      anon_sym_ONLY_IF_RW,
      anon_sym_SPECIAL,
  [12429] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(816), 1,
      anon_sym_SUBALIGN,
    ACTIONS(942), 1,
      anon_sym_LBRACE,
    STATE(366), 1,
      sym_subalign,
    STATE(531), 1,
      sym_sect_constraint,
    ACTIONS(818), 3,
      anon_sym_ONLY_IF_RO,
      anon_sym_ONLY_IF_RW,
      anon_sym_SPECIAL,
  [12450] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(946), 1,
      anon_sym_ALIGN,
    ACTIONS(944), 6,
      anon_sym_LBRACE,
      anon_sym_SUBALIGN,
      anon_sym_ONLY_IF_RO,
      anon_sym_ONLY_IF_RW,
      anon_sym_SPECIAL,
      anon_sym_ALIGN_WITH_INPUT,
  [12465] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(934), 1,
      anon_sym_global,
    ACTIONS(936), 1,
      anon_sym_local,
    ACTIONS(938), 1,
      anon_sym_extern,
    ACTIONS(940), 1,
      sym_VERS_IDENTIFIER,
    ACTIONS(948), 1,
      anon_sym_RBRACE,
    STATE(511), 1,
      sym_vers_tag,
    STATE(600), 1,
      sym_vers_defns,
  [12490] = 7,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(918), 1,
      anon_sym_REVERSE,
    ACTIONS(950), 1,
      anon_sym_CONSTRUCTORS,
    STATE(464), 1,
      sym_wildcard_maybe_exclude,
    STATE(553), 1,
      sym_wildcard_maybe_reverse,
  [12512] = 5,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    STATE(646), 1,
      sym_wildcard_maybe_exclude,
    ACTIONS(952), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_INIT_PRIORITY,
  [12530] = 5,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    STATE(664), 1,
      sym_wildcard_maybe_exclude,
    ACTIONS(954), 3,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
      anon_sym_SORT_BY_INIT_PRIORITY,
  [12548] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(956), 1,
      sym_NAME,
    ACTIONS(958), 1,
      anon_sym_COMMA,
    ACTIONS(960), 1,
      anon_sym_INCLUDE,
    ACTIONS(962), 1,
      anon_sym_RBRACE,
    STATE(328), 2,
      sym_memory_spec,
      aux_sym_memory_spec_list_repeat1,
  [12568] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(814), 1,
      anon_sym_AT,
    ACTIONS(816), 1,
      anon_sym_SUBALIGN,
    ACTIONS(964), 1,
      anon_sym_NOCROSSREFS,
    ACTIONS(966), 1,
      anon_sym_LBRACE,
    STATE(416), 1,
      sym_at,
    STATE(566), 1,
      sym_subalign,
  [12590] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(968), 1,
      sym_NAME,
    ACTIONS(971), 1,
      anon_sym_COMMA,
    ACTIONS(974), 1,
      anon_sym_INCLUDE,
    ACTIONS(977), 1,
      anon_sym_RBRACE,
    STATE(317), 2,
      sym_memory_spec,
      aux_sym_memory_spec_list_repeat1,
  [12610] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(979), 1,
      sym_NAME,
    ACTIONS(981), 1,
      anon_sym_COMMA,
    ACTIONS(983), 1,
      anon_sym_RPAREN,
    STATE(435), 1,
      aux_sym_low_level_library_NAME_list_repeat2,
    STATE(365), 2,
      sym_filename,
      aux_sym_low_level_library_NAME_list_repeat1,
  [12630] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(985), 1,
      sym_NAME,
    ACTIONS(988), 1,
      anon_sym_COMMA,
    ACTIONS(991), 1,
      anon_sym_RPAREN,
    ACTIONS(993), 1,
      anon_sym_AS_NEEDED,
    ACTIONS(996), 1,
      sym_LNAME,
    STATE(319), 1,
      aux_sym_input_list_repeat1,
  [12652] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(999), 6,
      anon_sym_LBRACE,
      anon_sym_SUBALIGN,
      anon_sym_ONLY_IF_RO,
      anon_sym_ONLY_IF_RW,
      anon_sym_SPECIAL,
      anon_sym_ALIGN_WITH_INPUT,
  [12664] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1001), 1,
      sym_NAME,
    ACTIONS(1003), 1,
      anon_sym_COMMA,
    ACTIONS(1005), 1,
      anon_sym_RPAREN,
    ACTIONS(1007), 1,
      anon_sym_AS_NEEDED,
    ACTIONS(1009), 1,
      sym_LNAME,
    STATE(329), 1,
      aux_sym_input_list_repeat1,
  [12686] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1011), 1,
      sym_NAME,
    ACTIONS(1013), 1,
      anon_sym_COMMA,
    ACTIONS(1015), 1,
      anon_sym_RBRACE,
    ACTIONS(1017), 1,
      anon_sym_EQ,
    ACTIONS(1019), 1,
      anon_sym_COLON,
    STATE(367), 1,
      sym_phdr_opt,
  [12708] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(979), 1,
      sym_NAME,
    ACTIONS(981), 1,
      anon_sym_COMMA,
    ACTIONS(1021), 1,
      anon_sym_RPAREN,
    STATE(457), 1,
      aux_sym_low_level_library_NAME_list_repeat2,
    STATE(365), 2,
      sym_filename,
      aux_sym_low_level_library_NAME_list_repeat1,
  [12728] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1019), 1,
      anon_sym_COLON,
    ACTIONS(1023), 1,
      sym_NAME,
    ACTIONS(1025), 1,
      anon_sym_COMMA,
    ACTIONS(1027), 1,
      anon_sym_RBRACE,
    ACTIONS(1029), 1,
      anon_sym_EQ,
    STATE(337), 1,
      sym_phdr_opt,
  [12750] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(979), 1,
      sym_NAME,
    ACTIONS(1031), 1,
      anon_sym_COMMA,
    ACTIONS(1033), 1,
      anon_sym_RPAREN,
    STATE(583), 1,
      sym_low_level_library_NAME_list,
    STATE(318), 2,
      sym_filename,
      aux_sym_low_level_library_NAME_list_repeat1,
  [12770] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1003), 1,
      anon_sym_COMMA,
    ACTIONS(1007), 1,
      anon_sym_AS_NEEDED,
    ACTIONS(1035), 1,
      sym_NAME,
    ACTIONS(1037), 1,
      anon_sym_RPAREN,
    ACTIONS(1039), 1,
      sym_LNAME,
    STATE(327), 1,
      aux_sym_input_list_repeat1,
  [12792] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1003), 1,
      anon_sym_COMMA,
    ACTIONS(1007), 1,
      anon_sym_AS_NEEDED,
    ACTIONS(1041), 1,
      sym_NAME,
    ACTIONS(1043), 1,
      anon_sym_RPAREN,
    ACTIONS(1045), 1,
      sym_LNAME,
    STATE(319), 1,
      aux_sym_input_list_repeat1,
  [12814] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(956), 1,
      sym_NAME,
    ACTIONS(958), 1,
      anon_sym_COMMA,
    ACTIONS(960), 1,
      anon_sym_INCLUDE,
    ACTIONS(1047), 1,
      anon_sym_RBRACE,
    STATE(317), 2,
      sym_memory_spec,
      aux_sym_memory_spec_list_repeat1,
  [12834] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1003), 1,
      anon_sym_COMMA,
    ACTIONS(1007), 1,
      anon_sym_AS_NEEDED,
    ACTIONS(1041), 1,
      sym_NAME,
    ACTIONS(1045), 1,
      sym_LNAME,
    ACTIONS(1049), 1,
      anon_sym_RPAREN,
    STATE(319), 1,
      aux_sym_input_list_repeat1,
  [12856] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1051), 1,
      anon_sym_LBRACE,
    ACTIONS(1054), 1,
      anon_sym_RBRACE,
    ACTIONS(1056), 1,
      sym_VERS_TAG,
    STATE(330), 2,
      sym_vers_node,
      aux_sym_vers_nodes_repeat1,
  [12873] = 5,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    STATE(548), 1,
      sym_wildcard_maybe_exclude,
    ACTIONS(1059), 2,
      anon_sym_SORT_BY_NAME,
      anon_sym_SORT,
  [12890] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1061), 2,
      anon_sym_AS_NEEDED,
      sym_NAME,
    ACTIONS(1063), 3,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      sym_LNAME,
  [12903] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1067), 1,
      anon_sym_SEMI,
    ACTIONS(1069), 1,
      anon_sym_LPAREN,
    STATE(430), 1,
      sym_phdr_val,
    ACTIONS(1065), 2,
      anon_sym_AT,
      sym_NAME,
  [12920] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1071), 2,
      anon_sym_AS_NEEDED,
      sym_NAME,
    ACTIONS(991), 3,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      sym_LNAME,
  [12933] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1073), 1,
      sym_NAME,
    ACTIONS(1075), 1,
      anon_sym_RBRACE,
    STATE(581), 1,
      sym_phdr_list,
    STATE(385), 2,
      sym_phdr,
      aux_sym_phdr_list_repeat1,
  [12950] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(956), 1,
      sym_NAME,
    ACTIONS(960), 1,
      anon_sym_INCLUDE,
    ACTIONS(1077), 1,
      anon_sym_RBRACE,
    STATE(315), 1,
      sym_memory_spec,
    STATE(594), 1,
      sym_memory_spec_list,
  [12969] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1011), 1,
      sym_NAME,
    ACTIONS(1013), 1,
      anon_sym_COMMA,
    ACTIONS(1015), 1,
      anon_sym_RBRACE,
    ACTIONS(1017), 1,
      anon_sym_EQ,
    ACTIONS(1079), 1,
      anon_sym_COLON,
  [12988] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1081), 1,
      anon_sym_LBRACE,
    ACTIONS(1083), 1,
      sym_VERS_TAG,
    STATE(576), 1,
      sym_vers_nodes,
    STATE(350), 2,
      sym_vers_node,
      aux_sym_vers_nodes_repeat1,
  [13005] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1085), 1,
      anon_sym_RBRACE,
    ACTIONS(1089), 1,
      anon_sym_extern,
    ACTIONS(1087), 3,
      anon_sym_global,
      anon_sym_local,
      sym_VERS_IDENTIFIER,
  [13020] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(938), 1,
      anon_sym_extern,
    STATE(472), 1,
      sym_vers_defns,
    ACTIONS(940), 3,
      anon_sym_global,
      anon_sym_local,
      sym_VERS_IDENTIFIER,
  [13035] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(788), 2,
      anon_sym_EQ,
      sym_NAME,
    ACTIONS(790), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_COLON,
  [13048] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(938), 1,
      anon_sym_extern,
    STATE(515), 1,
      sym_vers_defns,
    ACTIONS(940), 3,
      anon_sym_global,
      anon_sym_local,
      sym_VERS_IDENTIFIER,
  [13063] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(979), 1,
      sym_NAME,
    ACTIONS(1091), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
    STATE(365), 2,
      sym_filename,
      aux_sym_low_level_library_NAME_list_repeat1,
  [13078] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(281), 2,
      anon_sym_INCLUDE,
      sym_NAME,
    ACTIONS(279), 3,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_RBRACE,
  [13091] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1093), 1,
      sym_NAME,
    ACTIONS(1096), 1,
      anon_sym_COMMA,
    ACTIONS(1099), 1,
      anon_sym_RPAREN,
    STATE(345), 2,
      sym_filename,
      aux_sym_high_level_library_NAME_list_repeat1,
  [13108] = 6,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(918), 1,
      anon_sym_REVERSE,
    STATE(464), 1,
      sym_wildcard_maybe_exclude,
    STATE(520), 1,
      sym_wildcard_maybe_reverse,
  [13127] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1101), 2,
      anon_sym_AS_NEEDED,
      sym_NAME,
    ACTIONS(1103), 3,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      sym_LNAME,
  [13140] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1105), 1,
      anon_sym_COMMA,
    ACTIONS(1109), 1,
      anon_sym_l,
    STATE(380), 1,
      sym_length_spec,
    ACTIONS(1107), 2,
      anon_sym_LENGTH,
      anon_sym_len,
  [13157] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1111), 1,
      sym_NAME,
    ACTIONS(1114), 1,
      anon_sym_RPAREN,
    ACTIONS(1116), 1,
      anon_sym_BANG,
    STATE(349), 2,
      sym_attributes_string,
      aux_sym_attributes_list_repeat1,
  [13174] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1081), 1,
      anon_sym_LBRACE,
    ACTIONS(1083), 1,
      sym_VERS_TAG,
    ACTIONS(1119), 1,
      anon_sym_RBRACE,
    STATE(330), 2,
      sym_vers_node,
      aux_sym_vers_nodes_repeat1,
  [13191] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1089), 1,
      anon_sym_extern,
    ACTIONS(1121), 1,
      anon_sym_RBRACE,
    ACTIONS(1087), 3,
      anon_sym_global,
      anon_sym_local,
      sym_VERS_IDENTIFIER,
  [13206] = 6,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(918), 1,
      anon_sym_REVERSE,
    STATE(464), 1,
      sym_wildcard_maybe_exclude,
    STATE(553), 1,
      sym_wildcard_maybe_reverse,
  [13225] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(814), 1,
      anon_sym_AT,
    ACTIONS(816), 1,
      anon_sym_SUBALIGN,
    ACTIONS(1123), 1,
      anon_sym_LBRACE,
    STATE(417), 1,
      sym_at,
    STATE(591), 1,
      sym_subalign,
  [13244] = 6,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(918), 1,
      anon_sym_REVERSE,
    STATE(464), 1,
      sym_wildcard_maybe_exclude,
    STATE(651), 1,
      sym_wildcard_maybe_reverse,
  [13263] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1089), 1,
      anon_sym_extern,
    ACTIONS(1125), 1,
      anon_sym_RBRACE,
    ACTIONS(1087), 3,
      anon_sym_global,
      anon_sym_local,
      sym_VERS_IDENTIFIER,
  [13278] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(798), 2,
      anon_sym_EQ,
      sym_NAME,
    ACTIONS(800), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_COLON,
  [13291] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1089), 1,
      anon_sym_extern,
    ACTIONS(1125), 1,
      anon_sym_RBRACE,
    ACTIONS(1127), 1,
      anon_sym_local,
    ACTIONS(1087), 2,
      anon_sym_global,
      sym_VERS_IDENTIFIER,
  [13308] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(938), 1,
      anon_sym_extern,
    STATE(624), 1,
      sym_vers_defns,
    ACTIONS(940), 3,
      anon_sym_global,
      anon_sym_local,
      sym_VERS_IDENTIFIER,
  [13323] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1109), 1,
      anon_sym_l,
    ACTIONS(1129), 1,
      anon_sym_COMMA,
    STATE(403), 1,
      sym_length_spec,
    ACTIONS(1107), 2,
      anon_sym_LENGTH,
      anon_sym_len,
  [13340] = 6,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(918), 1,
      anon_sym_REVERSE,
    STATE(464), 1,
      sym_wildcard_maybe_exclude,
    STATE(684), 1,
      sym_wildcard_maybe_reverse,
  [13359] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(938), 1,
      anon_sym_extern,
    STATE(623), 1,
      sym_vers_defns,
    ACTIONS(940), 3,
      anon_sym_global,
      anon_sym_local,
      sym_VERS_IDENTIFIER,
  [13374] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1131), 1,
      sym_NAME,
    ACTIONS(1133), 1,
      anon_sym_SEMI,
    ACTIONS(1135), 1,
      anon_sym_AT,
    STATE(401), 1,
      aux_sym_phdr_qualifiers_repeat1,
    STATE(625), 1,
      sym_phdr_qualifiers,
  [13393] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1137), 1,
      sym_NAME,
    ACTIONS(1139), 1,
      anon_sym_RPAREN,
    ACTIONS(1141), 1,
      anon_sym_BANG,
    STATE(349), 2,
      sym_attributes_string,
      aux_sym_attributes_list_repeat1,
  [13410] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(979), 1,
      sym_NAME,
    ACTIONS(1143), 1,
      anon_sym_COMMA,
    ACTIONS(1145), 1,
      anon_sym_RPAREN,
    STATE(376), 2,
      sym_filename,
      aux_sym_high_level_library_NAME_list_repeat1,
  [13427] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1147), 1,
      sym_NAME,
    ACTIONS(1150), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
    STATE(365), 2,
      sym_filename,
      aux_sym_low_level_library_NAME_list_repeat1,
  [13442] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1152), 1,
      anon_sym_LBRACE,
    STATE(517), 1,
      sym_sect_constraint,
    ACTIONS(818), 3,
      anon_sym_ONLY_IF_RO,
      anon_sym_ONLY_IF_RW,
      anon_sym_SPECIAL,
  [13457] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1079), 1,
      anon_sym_COLON,
    ACTIONS(1154), 1,
      sym_NAME,
    ACTIONS(1156), 1,
      anon_sym_COMMA,
    ACTIONS(1158), 1,
      anon_sym_RBRACE,
    ACTIONS(1160), 1,
      anon_sym_EQ,
  [13476] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1089), 1,
      anon_sym_extern,
    ACTIONS(1162), 1,
      anon_sym_RBRACE,
    ACTIONS(1087), 3,
      anon_sym_global,
      anon_sym_local,
      sym_VERS_IDENTIFIER,
  [13491] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1137), 1,
      sym_NAME,
    ACTIONS(1141), 1,
      anon_sym_BANG,
    STATE(589), 1,
      sym_attributes_list,
    STATE(363), 2,
      sym_attributes_string,
      aux_sym_attributes_list_repeat1,
  [13508] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(852), 1,
      anon_sym_LBRACE,
    STATE(635), 1,
      sym_sect_constraint,
    ACTIONS(818), 3,
      anon_sym_ONLY_IF_RO,
      anon_sym_ONLY_IF_RW,
      anon_sym_SPECIAL,
  [13523] = 6,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(918), 1,
      anon_sym_REVERSE,
    STATE(464), 1,
      sym_wildcard_maybe_exclude,
    STATE(530), 1,
      sym_wildcard_maybe_reverse,
  [13542] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1089), 1,
      anon_sym_extern,
    ACTIONS(1164), 1,
      anon_sym_RBRACE,
    ACTIONS(1087), 3,
      anon_sym_global,
      anon_sym_local,
      sym_VERS_IDENTIFIER,
  [13557] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(942), 1,
      anon_sym_LBRACE,
    STATE(531), 1,
      sym_sect_constraint,
    ACTIONS(818), 3,
      anon_sym_ONLY_IF_RO,
      anon_sym_ONLY_IF_RW,
      anon_sym_SPECIAL,
  [13572] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(920), 1,
      anon_sym_LBRACE,
    STATE(579), 1,
      sym_sect_constraint,
    ACTIONS(818), 3,
      anon_sym_ONLY_IF_RO,
      anon_sym_ONLY_IF_RW,
      anon_sym_SPECIAL,
  [13587] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(938), 1,
      anon_sym_extern,
    STATE(479), 1,
      sym_vers_defns,
    ACTIONS(940), 3,
      anon_sym_global,
      anon_sym_local,
      sym_VERS_IDENTIFIER,
  [13602] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(979), 1,
      sym_NAME,
    ACTIONS(1143), 1,
      anon_sym_COMMA,
    ACTIONS(1166), 1,
      anon_sym_RPAREN,
    STATE(345), 2,
      sym_filename,
      aux_sym_high_level_library_NAME_list_repeat1,
  [13619] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1168), 2,
      anon_sym_INCLUDE,
      sym_NAME,
    ACTIONS(1170), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [13631] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1172), 4,
      anon_sym_NOCROSSREFS,
      anon_sym_LBRACE,
      anon_sym_AT,
      anon_sym_SUBALIGN,
  [13641] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1176), 1,
      anon_sym_l,
    ACTIONS(1174), 3,
      anon_sym_COMMA,
      anon_sym_LENGTH,
      anon_sym_len,
  [13653] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1178), 2,
      anon_sym_INCLUDE,
      sym_NAME,
    ACTIONS(1180), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [13665] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1109), 1,
      anon_sym_l,
    STATE(394), 1,
      sym_length_spec,
    ACTIONS(1107), 2,
      anon_sym_LENGTH,
      anon_sym_len,
  [13679] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(212), 1,
      anon_sym_RBRACE,
    ACTIONS(1182), 1,
      sym_NAME,
    STATE(425), 1,
      aux_sym_overlay_section_repeat1,
    STATE(608), 1,
      sym_overlay_section,
  [13695] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1184), 1,
      sym_NAME,
    ACTIONS(1187), 1,
      anon_sym_RBRACE,
    STATE(383), 2,
      sym_phdr,
      aux_sym_phdr_list_repeat1,
  [13709] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1189), 1,
      sym_NAME,
    ACTIONS(1191), 1,
      anon_sym_AS_NEEDED,
    ACTIONS(1193), 1,
      sym_LNAME,
    STATE(633), 1,
      sym_input_list,
  [13725] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1073), 1,
      sym_NAME,
    ACTIONS(1195), 1,
      anon_sym_RBRACE,
    STATE(383), 2,
      sym_phdr,
      aux_sym_phdr_list_repeat1,
  [13739] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1199), 1,
      anon_sym_o,
    STATE(359), 1,
      sym_origin_spec,
    ACTIONS(1197), 2,
      anon_sym_ORIGIN,
      anon_sym_org,
  [13753] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(979), 1,
      sym_NAME,
    ACTIONS(1201), 1,
      anon_sym_RPAREN,
    STATE(364), 1,
      sym_filename,
    STATE(587), 1,
      sym_high_level_library_NAME_list,
  [13769] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1189), 1,
      sym_NAME,
    ACTIONS(1191), 1,
      anon_sym_AS_NEEDED,
    ACTIONS(1193), 1,
      sym_LNAME,
    STATE(654), 1,
      sym_input_list,
  [13785] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1189), 1,
      sym_NAME,
    ACTIONS(1191), 1,
      anon_sym_AS_NEEDED,
    ACTIONS(1193), 1,
      sym_LNAME,
    STATE(619), 1,
      sym_input_list,
  [13801] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1203), 1,
      anon_sym_SEMI,
    ACTIONS(1205), 1,
      sym_VERS_TAG,
    STATE(420), 1,
      aux_sym_verdep_repeat1,
    STATE(621), 1,
      sym_verdep,
  [13817] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1199), 1,
      anon_sym_o,
    STATE(348), 1,
      sym_origin_spec,
    ACTIONS(1197), 2,
      anon_sym_ORIGIN,
      anon_sym_org,
  [13831] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(977), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
    ACTIONS(1207), 2,
      anon_sym_INCLUDE,
      sym_NAME,
  [13843] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1209), 1,
      sym_NAME,
    ACTIONS(1212), 1,
      anon_sym_COMMA,
    ACTIONS(1215), 1,
      anon_sym_RPAREN,
    STATE(393), 1,
      aux_sym_extern_name_list_repeat1,
  [13859] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1217), 2,
      anon_sym_INCLUDE,
      sym_NAME,
    ACTIONS(1219), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [13871] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1221), 2,
      anon_sym_INCLUDE,
      sym_NAME,
    ACTIONS(1223), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [13883] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1225), 1,
      sym_NAME,
    ACTIONS(1228), 1,
      anon_sym_SEMI,
    ACTIONS(1230), 1,
      anon_sym_AT,
    STATE(396), 1,
      aux_sym_phdr_qualifiers_repeat1,
  [13899] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1233), 4,
      anon_sym_LBRACE,
      anon_sym_ONLY_IF_RO,
      anon_sym_ONLY_IF_RW,
      anon_sym_SPECIAL,
  [13909] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1189), 1,
      sym_NAME,
    ACTIONS(1191), 1,
      anon_sym_AS_NEEDED,
    ACTIONS(1193), 1,
      sym_LNAME,
    STATE(524), 1,
      sym_input_list,
  [13925] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1109), 1,
      anon_sym_l,
    STATE(380), 1,
      sym_length_spec,
    ACTIONS(1107), 2,
      anon_sym_LENGTH,
      anon_sym_len,
  [13939] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1235), 1,
      sym_NAME,
    ACTIONS(1237), 1,
      anon_sym_COMMA,
    ACTIONS(1239), 1,
      anon_sym_RPAREN,
    STATE(408), 1,
      aux_sym_extern_name_list_repeat1,
  [13955] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1131), 1,
      sym_NAME,
    ACTIONS(1135), 1,
      anon_sym_AT,
    ACTIONS(1241), 1,
      anon_sym_SEMI,
    STATE(396), 1,
      aux_sym_phdr_qualifiers_repeat1,
  [13971] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(206), 1,
      anon_sym_RBRACE,
    ACTIONS(1182), 1,
      sym_NAME,
    STATE(425), 1,
      aux_sym_overlay_section_repeat1,
    STATE(562), 1,
      sym_overlay_section,
  [13987] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1243), 2,
      anon_sym_INCLUDE,
      sym_NAME,
    ACTIONS(1245), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [13999] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(222), 1,
      anon_sym_RBRACE,
    ACTIONS(1182), 1,
      sym_NAME,
    STATE(425), 1,
      aux_sym_overlay_section_repeat1,
    STATE(525), 1,
      sym_overlay_section,
  [14015] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(208), 1,
      anon_sym_RBRACE,
    ACTIONS(1182), 1,
      sym_NAME,
    STATE(425), 1,
      aux_sym_overlay_section_repeat1,
    STATE(716), 1,
      sym_overlay_section,
  [14031] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(523), 1,
      anon_sym_LPAREN,
    ACTIONS(1247), 1,
      anon_sym_COLON,
    ACTIONS(1249), 1,
      anon_sym_BLOCK,
    STATE(569), 1,
      sym_atype,
  [14047] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1251), 4,
      anon_sym_NOCROSSREFS,
      anon_sym_LBRACE,
      anon_sym_AT,
      anon_sym_SUBALIGN,
  [14057] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1253), 1,
      sym_NAME,
    ACTIONS(1255), 1,
      anon_sym_COMMA,
    ACTIONS(1257), 1,
      anon_sym_RPAREN,
    STATE(393), 1,
      aux_sym_extern_name_list_repeat1,
  [14073] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1259), 1,
      sym_NAME,
    ACTIONS(1261), 1,
      anon_sym_COMMA,
    ACTIONS(1263), 1,
      anon_sym_RPAREN,
    STATE(410), 1,
      aux_sym_extern_name_list_repeat1,
  [14089] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1253), 1,
      sym_NAME,
    ACTIONS(1261), 1,
      anon_sym_COMMA,
    ACTIONS(1265), 1,
      anon_sym_RPAREN,
    STATE(393), 1,
      aux_sym_extern_name_list_repeat1,
  [14105] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1205), 1,
      sym_VERS_TAG,
    ACTIONS(1267), 1,
      anon_sym_SEMI,
    STATE(420), 1,
      aux_sym_verdep_repeat1,
    STATE(521), 1,
      sym_verdep,
  [14121] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1269), 1,
      anon_sym_RPAREN,
    ACTIONS(1271), 1,
      anon_sym_AMP,
    STATE(429), 1,
      aux_sym_sect_flag_list_repeat1,
  [14134] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1273), 1,
      anon_sym_SEMI,
    ACTIONS(1275), 1,
      sym_VERS_TAG,
    STATE(413), 1,
      aux_sym_verdep_repeat1,
  [14147] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1278), 1,
      anon_sym_LPAREN,
    ACTIONS(1280), 1,
      anon_sym_COLON,
    STATE(523), 1,
      sym_attributes,
  [14160] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1282), 1,
      sym_NAME,
    ACTIONS(1284), 1,
      anon_sym_AS_NEEDED,
    ACTIONS(1286), 1,
      sym_LNAME,
  [14173] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(816), 1,
      anon_sym_SUBALIGN,
    ACTIONS(1123), 1,
      anon_sym_LBRACE,
    STATE(591), 1,
      sym_subalign,
  [14186] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(816), 1,
      anon_sym_SUBALIGN,
    ACTIONS(1288), 1,
      anon_sym_LBRACE,
    STATE(606), 1,
      sym_subalign,
  [14199] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(523), 1,
      anon_sym_LPAREN,
    ACTIONS(1290), 1,
      anon_sym_COLON,
    STATE(536), 1,
      sym_atype,
  [14212] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1091), 1,
      anon_sym_RPAREN,
    ACTIONS(1292), 1,
      anon_sym_COMMA,
    STATE(419), 1,
      aux_sym_low_level_library_NAME_list_repeat2,
  [14225] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1295), 1,
      anon_sym_SEMI,
    ACTIONS(1297), 1,
      sym_VERS_TAG,
    STATE(413), 1,
      aux_sym_verdep_repeat1,
  [14238] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1299), 1,
      sym_NAME,
    ACTIONS(1301), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [14249] = 4,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(1303), 1,
      sym_wildcard_name,
    STATE(426), 1,
      aux_sym_exclude_name_list_repeat1,
    STATE(693), 1,
      sym_exclude_name_list,
  [14262] = 4,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    STATE(530), 1,
      sym_wildcard_maybe_exclude,
  [14275] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1305), 3,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      sym_VERS_TAG,
  [14284] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1182), 1,
      sym_NAME,
    ACTIONS(1307), 1,
      anon_sym_RBRACE,
    STATE(451), 1,
      aux_sym_overlay_section_repeat1,
  [14297] = 4,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(1309), 1,
      anon_sym_RPAREN,
    ACTIONS(1311), 1,
      sym_wildcard_name,
    STATE(448), 1,
      aux_sym_exclude_name_list_repeat1,
  [14310] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1271), 1,
      anon_sym_AMP,
    ACTIONS(1313), 1,
      anon_sym_RPAREN,
    STATE(412), 1,
      aux_sym_sect_flag_list_repeat1,
  [14323] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1315), 1,
      sym_NAME,
    ACTIONS(1317), 1,
      anon_sym_COMMA,
    ACTIONS(1319), 1,
      anon_sym_RBRACE,
  [14336] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1321), 1,
      anon_sym_RPAREN,
    ACTIONS(1323), 1,
      anon_sym_AMP,
    STATE(429), 1,
      aux_sym_sect_flag_list_repeat1,
  [14349] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1228), 1,
      anon_sym_SEMI,
    ACTIONS(1326), 2,
      anon_sym_AT,
      sym_NAME,
  [14360] = 4,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    STATE(684), 1,
      sym_wildcard_maybe_exclude,
  [14373] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(979), 1,
      sym_NAME,
    STATE(343), 2,
      sym_filename,
      aux_sym_low_level_library_NAME_list_repeat1,
  [14384] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1154), 1,
      sym_NAME,
    ACTIONS(1156), 1,
      anon_sym_COMMA,
    ACTIONS(1158), 1,
      anon_sym_RBRACE,
  [14397] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1328), 3,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      sym_VERS_TAG,
  [14406] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(981), 1,
      anon_sym_COMMA,
    ACTIONS(1021), 1,
      anon_sym_RPAREN,
    STATE(419), 1,
      aux_sym_low_level_library_NAME_list_repeat2,
  [14419] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1330), 1,
      sym_NAME,
    ACTIONS(1332), 2,
      anon_sym_RPAREN,
      anon_sym_BANG,
  [14430] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(979), 1,
      sym_NAME,
    STATE(323), 2,
      sym_filename,
      aux_sym_low_level_library_NAME_list_repeat1,
  [14441] = 3,
    ACTIONS(3), 1,
      sym_comment,
    STATE(122), 1,
      sym_separator,
    ACTIONS(1334), 2,
      anon_sym_COMMA,
      anon_sym_SEMI,
  [14452] = 4,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(1303), 1,
      sym_wildcard_name,
    STATE(426), 1,
      aux_sym_exclude_name_list_repeat1,
    STATE(679), 1,
      sym_exclude_name_list,
  [14465] = 3,
    ACTIONS(3), 1,
      sym_comment,
    STATE(261), 1,
      sym_separator,
    ACTIONS(1336), 2,
      anon_sym_COMMA,
      anon_sym_SEMI,
  [14476] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1338), 1,
      sym_NAME,
    ACTIONS(1340), 2,
      anon_sym_RPAREN,
      anon_sym_BANG,
  [14487] = 3,
    ACTIONS(3), 1,
      sym_comment,
    STATE(18), 1,
      sym_separator,
    ACTIONS(1342), 2,
      anon_sym_COMMA,
      anon_sym_SEMI,
  [14498] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1346), 1,
      anon_sym_SEMI,
    ACTIONS(1344), 2,
      anon_sym_AT,
      sym_NAME,
  [14509] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1350), 1,
      anon_sym_SEMI,
    ACTIONS(1348), 2,
      anon_sym_AT,
      sym_NAME,
  [14520] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1352), 1,
      sym_NAME,
    ACTIONS(1354), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [14531] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(822), 1,
      sym_NAME,
    ACTIONS(824), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [14542] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1356), 1,
      sym_NAME,
    ACTIONS(1358), 1,
      anon_sym_RPAREN,
    STATE(633), 1,
      sym_nocrossref_list,
  [14555] = 4,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(1360), 1,
      anon_sym_RPAREN,
    ACTIONS(1362), 1,
      sym_wildcard_name,
    STATE(448), 1,
      aux_sym_exclude_name_list_repeat1,
  [14568] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1365), 3,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      sym_VERS_TAG,
  [14577] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1367), 1,
      sym_NAME,
    ACTIONS(1369), 1,
      anon_sym_COMMA,
    ACTIONS(1371), 1,
      anon_sym_RBRACE,
  [14590] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1373), 1,
      sym_NAME,
    ACTIONS(1376), 1,
      anon_sym_RBRACE,
    STATE(451), 1,
      aux_sym_overlay_section_repeat1,
  [14603] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1378), 1,
      sym_NAME,
    ACTIONS(1099), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [14614] = 4,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    STATE(505), 1,
      sym_wildcard_maybe_exclude,
  [14627] = 3,
    ACTIONS(3), 1,
      sym_comment,
    STATE(134), 1,
      sym_separator,
    ACTIONS(1334), 2,
      anon_sym_COMMA,
      anon_sym_SEMI,
  [14638] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1380), 1,
      sym_NAME,
    ACTIONS(1215), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [14649] = 4,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(1303), 1,
      sym_wildcard_name,
    STATE(426), 1,
      aux_sym_exclude_name_list_repeat1,
    STATE(547), 1,
      sym_exclude_name_list,
  [14662] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(981), 1,
      anon_sym_COMMA,
    ACTIONS(1382), 1,
      anon_sym_RPAREN,
    STATE(419), 1,
      aux_sym_low_level_library_NAME_list_repeat2,
  [14675] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1384), 3,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      sym_VERS_TAG,
  [14684] = 4,
    ACTIONS(184), 1,
      anon_sym_EXCLUDE_FILE,
    ACTIONS(200), 1,
      sym_wildcard_name,
    ACTIONS(202), 1,
      sym_comment,
    STATE(548), 1,
      sym_wildcard_maybe_exclude,
  [14697] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(956), 1,
      sym_NAME,
    ACTIONS(960), 1,
      anon_sym_INCLUDE,
    STATE(392), 1,
      sym_memory_spec,
  [14710] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1386), 2,
      anon_sym_COMMA,
      anon_sym_SEMI,
  [14718] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1354), 1,
      anon_sym_SEMI,
    ACTIONS(1388), 1,
      anon_sym_COLON,
  [14728] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(979), 1,
      sym_NAME,
    STATE(452), 1,
      sym_filename,
  [14738] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(876), 2,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [14746] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(874), 2,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [14754] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1390), 1,
      anon_sym_LPAREN,
    STATE(111), 1,
      sym_paren_script_name,
  [14764] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1367), 1,
      sym_NAME,
    ACTIONS(1371), 1,
      anon_sym_RBRACE,
  [14774] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1392), 1,
      sym_NAME,
    STATE(633), 1,
      sym_extern_name_list,
  [14784] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1394), 1,
      sym_NAME,
    ACTIONS(1396), 1,
      anon_sym_RPAREN,
  [14794] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(880), 2,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [14802] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1398), 1,
      anon_sym_COMMA,
    ACTIONS(1400), 1,
      anon_sym_RPAREN,
  [14812] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1402), 1,
      anon_sym_SEMI,
    ACTIONS(1404), 1,
      anon_sym_RBRACE,
  [14822] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1406), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [14830] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1408), 1,
      anon_sym_LPAREN,
    STATE(138), 1,
      sym_paren_script_name,
  [14840] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1354), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [14848] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1301), 1,
      anon_sym_SEMI,
    ACTIONS(1410), 1,
      anon_sym_COLON,
  [14858] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1412), 1,
      sym_NAME,
    STATE(633), 1,
      sym_filename,
  [14868] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1414), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [14876] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1416), 1,
      anon_sym_SEMI,
    ACTIONS(1418), 1,
      anon_sym_RBRACE,
  [14886] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1354), 1,
      anon_sym_SEMI,
    ACTIONS(1420), 1,
      anon_sym_COLON,
  [14896] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1412), 1,
      sym_NAME,
    STATE(590), 1,
      sym_filename,
  [14906] = 3,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(1422), 1,
      sym_wildcard_name,
    STATE(544), 1,
      sym_sect_flag_list,
  [14916] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1011), 1,
      sym_NAME,
    ACTIONS(1015), 1,
      anon_sym_RBRACE,
  [14926] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1424), 2,
      anon_sym_COMMA,
      anon_sym_SEMI,
  [14934] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1426), 1,
      anon_sym_LPAREN,
    ACTIONS(1428), 1,
      anon_sym_RPAREN,
  [14944] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1430), 1,
      sym_NAME,
    STATE(134), 1,
      sym_filename,
  [14954] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1432), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [14962] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1154), 1,
      sym_NAME,
    ACTIONS(1158), 1,
      anon_sym_RBRACE,
  [14972] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(979), 1,
      sym_NAME,
    STATE(395), 1,
      sym_filename,
  [14982] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1315), 1,
      sym_NAME,
    ACTIONS(1319), 1,
      anon_sym_RBRACE,
  [14992] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(878), 2,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [15000] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1321), 2,
      anon_sym_RPAREN,
      anon_sym_AMP,
  [15008] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1434), 1,
      sym_NAME,
    ACTIONS(1436), 1,
      anon_sym_RBRACE,
  [15018] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1438), 1,
      sym_NAME,
    STATE(292), 1,
      sym_filename,
  [15028] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1440), 2,
      anon_sym_AFTER,
      anon_sym_BEFORE,
  [15036] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1442), 1,
      sym_NAME,
    ACTIONS(1444), 1,
      anon_sym_RBRACE,
  [15046] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1301), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [15054] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1446), 1,
      anon_sym_LPAREN,
    STATE(132), 1,
      sym_paren_script_name,
  [15064] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1412), 1,
      sym_NAME,
    STATE(32), 1,
      sym_filename,
  [15074] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1448), 2,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [15082] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1257), 1,
      anon_sym_RPAREN,
    ACTIONS(1394), 1,
      sym_NAME,
  [15092] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1450), 1,
      sym_NAME,
    ACTIONS(1452), 1,
      anon_sym_RBRACE,
  [15102] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1454), 1,
      anon_sym_RPAREN,
  [15109] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1456), 1,
      anon_sym_RPAREN,
  [15116] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1458), 1,
      anon_sym_RPAREN,
  [15123] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1460), 1,
      anon_sym_RPAREN,
  [15130] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1462), 1,
      anon_sym_LPAREN,
  [15137] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1464), 1,
      sym_NAME,
  [15144] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1466), 1,
      sym_NAME,
  [15151] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1468), 1,
      anon_sym_SEMI,
  [15158] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1470), 1,
      anon_sym_RBRACE,
  [15165] = 2,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(1472), 1,
      sym_wildcard_name,
  [15172] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(210), 1,
      anon_sym_RBRACE,
  [15179] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1474), 1,
      anon_sym_RPAREN,
  [15186] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1476), 1,
      anon_sym_SEMI,
  [15193] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1478), 1,
      anon_sym_LPAREN,
  [15200] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1480), 1,
      anon_sym_LBRACE,
  [15207] = 2,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(1482), 1,
      sym_wildcard_name,
  [15214] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1484), 1,
      anon_sym_LPAREN,
  [15221] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1486), 1,
      anon_sym_RPAREN,
  [15228] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1488), 1,
      anon_sym_SEMI,
  [15235] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1490), 1,
      anon_sym_COMMA,
  [15242] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1492), 1,
      anon_sym_COLON,
  [15249] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1494), 1,
      anon_sym_RPAREN,
  [15256] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(174), 1,
      anon_sym_RBRACE,
  [15263] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1496), 1,
      anon_sym_LPAREN,
  [15270] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1498), 1,
      anon_sym_RPAREN,
  [15277] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1500), 1,
      anon_sym_COLON,
  [15284] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1502), 1,
      anon_sym_RPAREN,
  [15291] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1504), 1,
      anon_sym_RPAREN,
  [15298] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1152), 1,
      anon_sym_LBRACE,
  [15305] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1506), 1,
      anon_sym_RBRACE,
  [15312] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1428), 1,
      anon_sym_RPAREN,
  [15319] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1508), 1,
      anon_sym_RBRACK,
  [15326] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1508), 1,
      anon_sym_RPAREN,
  [15333] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1510), 1,
      anon_sym_COLON,
  [15340] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1512), 1,
      anon_sym_RPAREN,
  [15347] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1514), 1,
      sym_NAME,
  [15354] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1516), 1,
      sym_SYMBOLNAME,
  [15361] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1518), 1,
      sym_SYMBOLNAME,
  [15368] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(216), 1,
      anon_sym_RPAREN,
  [15375] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1520), 1,
      anon_sym_EQ,
  [15382] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1522), 1,
      anon_sym_RPAREN,
  [15389] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1524), 1,
      anon_sym_RPAREN,
  [15396] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1526), 1,
      anon_sym_LPAREN,
  [15403] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1528), 1,
      anon_sym_RPAREN,
  [15410] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1530), 1,
      anon_sym_RPAREN,
  [15417] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1532), 1,
      anon_sym_RPAREN,
  [15424] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1534), 1,
      anon_sym_LPAREN,
  [15431] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1536), 1,
      anon_sym_LBRACE,
  [15438] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(525), 1,
      anon_sym_COLON,
  [15445] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1538), 1,
      anon_sym_LPAREN,
  [15452] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1540), 1,
      anon_sym_RPAREN,
  [15459] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1542), 1,
      anon_sym_RPAREN,
  [15466] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1544), 1,
      anon_sym_LPAREN,
  [15473] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1546), 1,
      sym_NAME,
  [15480] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1548), 1,
      anon_sym_RBRACE,
  [15487] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1550), 1,
      sym_NAME,
  [15494] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1394), 1,
      sym_NAME,
  [15501] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1552), 1,
      sym_NAME,
  [15508] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1554), 1,
      anon_sym_COLON,
  [15515] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(222), 1,
      anon_sym_RBRACE,
  [15522] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1556), 1,
      anon_sym_LPAREN,
  [15529] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1558), 1,
      anon_sym_LPAREN,
  [15536] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1560), 1,
      anon_sym_LPAREN,
  [15543] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1123), 1,
      anon_sym_LBRACE,
  [15550] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1562), 1,
      anon_sym_LPAREN,
  [15557] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1564), 1,
      sym_NAME,
  [15564] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1566), 1,
      anon_sym_COLON,
  [15571] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1568), 1,
      anon_sym_LPAREN,
  [15578] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1570), 1,
      anon_sym_LBRACE,
  [15585] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1572), 1,
      anon_sym_EQ,
  [15592] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1574), 1,
      anon_sym_LBRACE,
  [15599] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(852), 1,
      anon_sym_LBRACE,
  [15606] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(637), 1,
      anon_sym_RBRACE,
  [15613] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1576), 1,
      anon_sym_RBRACE,
  [15620] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1578), 1,
      anon_sym_LBRACE,
  [15627] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(559), 1,
      anon_sym_RPAREN,
  [15634] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(942), 1,
      anon_sym_LBRACE,
  [15641] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(533), 1,
      anon_sym_RPAREN,
  [15648] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1580), 1,
      anon_sym_RBRACE,
  [15655] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(531), 1,
      anon_sym_COMMA,
  [15662] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1582), 1,
      anon_sym_RPAREN,
  [15669] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1584), 1,
      anon_sym_RPAREN,
  [15676] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1586), 1,
      anon_sym_RPAREN,
  [15683] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1588), 1,
      anon_sym_LPAREN,
  [15690] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1590), 1,
      anon_sym_RPAREN,
  [15697] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1592), 1,
      sym_NAME,
  [15704] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1594), 1,
      anon_sym_RPAREN,
  [15711] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1596), 1,
      anon_sym_RPAREN,
  [15718] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1288), 1,
      anon_sym_LBRACE,
  [15725] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1598), 1,
      anon_sym_RBRACK,
  [15732] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(493), 1,
      anon_sym_RPAREN,
  [15739] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1600), 1,
      anon_sym_RBRACE,
  [15746] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1602), 1,
      anon_sym_LPAREN,
  [15753] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1604), 1,
      anon_sym_LPAREN,
  [15760] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1606), 1,
      anon_sym_LPAREN,
  [15767] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(477), 1,
      anon_sym_RPAREN,
  [15774] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1608), 1,
      anon_sym_LPAREN,
  [15781] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1610), 1,
      anon_sym_SEMI,
  [15788] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1612), 1,
      anon_sym_GT,
  [15795] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1614), 1,
      sym_NAME,
  [15802] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1616), 1,
      anon_sym_EQ,
  [15809] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(473), 1,
      anon_sym_RPAREN,
  [15816] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1618), 1,
      sym_NAME,
  [15823] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1620), 1,
      anon_sym_LBRACE,
  [15830] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(505), 1,
      anon_sym_RPAREN,
  [15837] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(206), 1,
      anon_sym_RBRACE,
  [15844] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1622), 1,
      anon_sym_LPAREN,
  [15851] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1624), 1,
      anon_sym_LPAREN,
  [15858] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1626), 1,
      anon_sym_LPAREN,
  [15865] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1628), 1,
      anon_sym_LPAREN,
  [15872] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1630), 1,
      anon_sym_LPAREN,
  [15879] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1632), 1,
      anon_sym_LPAREN,
  [15886] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1634), 1,
      anon_sym_EQ,
  [15893] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1636), 1,
      anon_sym_LPAREN,
  [15900] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1638), 1,
      anon_sym_RPAREN,
  [15907] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1640), 1,
      anon_sym_RBRACE,
  [15914] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1642), 1,
      anon_sym_RPAREN,
  [15921] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1644), 1,
      anon_sym_RPAREN,
  [15928] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1267), 1,
      anon_sym_SEMI,
  [15935] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1646), 1,
      anon_sym_COMMA,
  [15942] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1648), 1,
      anon_sym_SEMI,
  [15949] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1650), 1,
      anon_sym_SEMI,
  [15956] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1652), 1,
      anon_sym_SEMI,
  [15963] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1654), 1,
      anon_sym_EQ,
  [15970] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1656), 1,
      anon_sym_COLON,
  [15977] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1658), 1,
      anon_sym_LPAREN,
  [15984] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1660), 1,
      anon_sym_LBRACE,
  [15991] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1662), 1,
      anon_sym_RPAREN,
  [15998] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1203), 1,
      anon_sym_SEMI,
  [16005] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1664), 1,
      sym_SYMBOLNAME,
  [16012] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1400), 1,
      anon_sym_RPAREN,
  [16019] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1666), 1,
      anon_sym_RPAREN,
  [16026] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(920), 1,
      anon_sym_LBRACE,
  [16033] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(537), 1,
      anon_sym_RPAREN,
  [16040] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1668), 1,
      anon_sym_RBRACE,
  [16047] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1670), 1,
      anon_sym_RPAREN,
  [16054] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1672), 1,
      sym_NAME,
  [16061] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1674), 1,
      anon_sym_LPAREN,
  [16068] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1676), 1,
      sym_NAME,
  [16075] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1678), 1,
      anon_sym_RBRACK,
  [16082] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(567), 1,
      anon_sym_RPAREN,
  [16089] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1680), 1,
      anon_sym_LPAREN,
  [16096] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1682), 1,
      sym_NAME,
  [16103] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1684), 1,
      anon_sym_RPAREN,
  [16110] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1686), 1,
      anon_sym_LPAREN,
  [16117] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1688), 1,
      anon_sym_RPAREN,
  [16124] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1688), 1,
      anon_sym_RBRACK,
  [16131] = 2,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(1690), 1,
      sym_wildcard_name,
  [16138] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1692), 1,
      anon_sym_RPAREN,
  [16145] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1694), 1,
      anon_sym_RPAREN,
  [16152] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1696), 1,
      anon_sym_RPAREN,
  [16159] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1698), 1,
      anon_sym_RPAREN,
  [16166] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1700), 1,
      sym_NAME,
  [16173] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1702), 1,
      sym_NAME,
  [16180] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1704), 1,
      anon_sym_RPAREN,
  [16187] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1706), 1,
      sym_NAME,
  [16194] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(529), 1,
      anon_sym_RPAREN,
  [16201] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1708), 1,
      sym_NAME,
  [16208] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1710), 1,
      anon_sym_LPAREN,
  [16215] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(557), 1,
      anon_sym_RPAREN,
  [16222] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1712), 1,
      anon_sym_LPAREN,
  [16229] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1714), 1,
      anon_sym_RPAREN,
  [16236] = 2,
    ACTIONS(202), 1,
      sym_comment,
    ACTIONS(1716), 1,
      sym_wildcard_name,
  [16243] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1718), 1,
      sym_NAME,
  [16250] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1720), 1,
      sym_NAME,
  [16257] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1722), 1,
      sym_NAME,
  [16264] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1724), 1,
      sym_NAME,
  [16271] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1726), 1,
      sym_SYMBOLNAME,
  [16278] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1728), 1,
      anon_sym_LPAREN,
  [16285] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1730), 1,
      sym_NAME,
  [16292] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1732), 1,
      sym_NAME,
  [16299] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1734), 1,
      anon_sym_TYPE,
  [16306] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1736), 1,
      sym_SYMBOLNAME,
  [16313] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1738), 1,
      ts_builtin_sym_end,
  [16320] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1740), 1,
      anon_sym_LBRACE,
  [16327] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1742), 1,
      anon_sym_LBRACE,
  [16334] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1744), 1,
      anon_sym_RPAREN,
  [16341] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1746), 1,
      anon_sym_LPAREN,
  [16348] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1748), 1,
      anon_sym_LPAREN,
  [16355] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1750), 1,
      anon_sym_LPAREN,
  [16362] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1752), 1,
      anon_sym_LPAREN,
  [16369] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1754), 1,
      anon_sym_RPAREN,
  [16376] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1756), 1,
      anon_sym_LPAREN,
  [16383] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1758), 1,
      sym_NAME,
  [16390] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1760), 1,
      anon_sym_LPAREN,
  [16397] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1762), 1,
      sym_SYMBOLNAME,
  [16404] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1764), 1,
      anon_sym_LBRACE,
  [16411] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1766), 1,
      anon_sym_LPAREN,
  [16418] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1768), 1,
      sym_SYMBOLNAME,
  [16425] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1770), 1,
      anon_sym_LPAREN,
  [16432] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1772), 1,
      anon_sym_RPAREN,
  [16439] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1774), 1,
      anon_sym_LPAREN,
  [16446] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1776), 1,
      anon_sym_LPAREN,
  [16453] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1778), 1,
      anon_sym_LPAREN,
  [16460] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1780), 1,
      anon_sym_LPAREN,
  [16467] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1782), 1,
      anon_sym_LPAREN,
  [16474] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1784), 1,
      anon_sym_LBRACE,
  [16481] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1786), 1,
      anon_sym_LPAREN,
  [16488] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(535), 1,
      anon_sym_COMMA,
  [16495] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1788), 1,
      anon_sym_LPAREN,
  [16502] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1790), 1,
      anon_sym_LPAREN,
  [16509] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1792), 1,
      anon_sym_LPAREN,
  [16516] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1794), 1,
      anon_sym_LPAREN,
  [16523] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1796), 1,
      anon_sym_LPAREN,
  [16530] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1798), 1,
      anon_sym_LPAREN,
  [16537] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1800), 1,
      anon_sym_LPAREN,
  [16544] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1802), 1,
      anon_sym_LPAREN,
  [16551] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1804), 1,
      anon_sym_LPAREN,
  [16558] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1806), 1,
      anon_sym_LPAREN,
  [16565] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1808), 1,
      anon_sym_LPAREN,
  [16572] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1810), 1,
      anon_sym_COLON,
  [16579] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1812), 1,
      anon_sym_LPAREN,
  [16586] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(527), 1,
      anon_sym_COMMA,
  [16593] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(212), 1,
      anon_sym_RBRACE,
  [16600] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1814), 1,
      anon_sym_LPAREN,
  [16607] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1816), 1,
      anon_sym_LBRACE,
  [16614] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1818), 1,
      anon_sym_LPAREN,
  [16621] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1820), 1,
      sym_SYMBOLNAME,
  [16628] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1822), 1,
      anon_sym_LPAREN,
  [16635] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1824), 1,
      anon_sym_LPAREN,
  [16642] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1826), 1,
      anon_sym_LPAREN,
  [16649] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1828), 1,
      anon_sym_LPAREN,
  [16656] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1830), 1,
      anon_sym_LPAREN,
  [16663] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1832), 1,
      sym_SYMBOLNAME,
  [16670] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1834), 1,
      anon_sym_LPAREN,
  [16677] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1836), 1,
      anon_sym_LPAREN,
  [16684] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1838), 1,
      anon_sym_LPAREN,
  [16691] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1840), 1,
      anon_sym_LPAREN,
  [16698] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1842), 1,
      anon_sym_LPAREN,
  [16705] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1844), 1,
      anon_sym_LPAREN,
  [16712] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1846), 1,
      anon_sym_LPAREN,
  [16719] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(1848), 1,
      anon_sym_LPAREN,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 93,
  [SMALL_STATE(4)] = 198,
  [SMALL_STATE(5)] = 303,
  [SMALL_STATE(6)] = 384,
  [SMALL_STATE(7)] = 482,
  [SMALL_STATE(8)] = 580,
  [SMALL_STATE(9)] = 678,
  [SMALL_STATE(10)] = 776,
  [SMALL_STATE(11)] = 874,
  [SMALL_STATE(12)] = 972,
  [SMALL_STATE(13)] = 1026,
  [SMALL_STATE(14)] = 1124,
  [SMALL_STATE(15)] = 1219,
  [SMALL_STATE(16)] = 1314,
  [SMALL_STATE(17)] = 1358,
  [SMALL_STATE(18)] = 1432,
  [SMALL_STATE(19)] = 1475,
  [SMALL_STATE(20)] = 1518,
  [SMALL_STATE(21)] = 1561,
  [SMALL_STATE(22)] = 1604,
  [SMALL_STATE(23)] = 1647,
  [SMALL_STATE(24)] = 1690,
  [SMALL_STATE(25)] = 1733,
  [SMALL_STATE(26)] = 1776,
  [SMALL_STATE(27)] = 1819,
  [SMALL_STATE(28)] = 1862,
  [SMALL_STATE(29)] = 1905,
  [SMALL_STATE(30)] = 1948,
  [SMALL_STATE(31)] = 1991,
  [SMALL_STATE(32)] = 2034,
  [SMALL_STATE(33)] = 2077,
  [SMALL_STATE(34)] = 2120,
  [SMALL_STATE(35)] = 2163,
  [SMALL_STATE(36)] = 2206,
  [SMALL_STATE(37)] = 2249,
  [SMALL_STATE(38)] = 2292,
  [SMALL_STATE(39)] = 2335,
  [SMALL_STATE(40)] = 2378,
  [SMALL_STATE(41)] = 2421,
  [SMALL_STATE(42)] = 2489,
  [SMALL_STATE(43)] = 2557,
  [SMALL_STATE(44)] = 2625,
  [SMALL_STATE(45)] = 2693,
  [SMALL_STATE(46)] = 2761,
  [SMALL_STATE(47)] = 2829,
  [SMALL_STATE(48)] = 2897,
  [SMALL_STATE(49)] = 2965,
  [SMALL_STATE(50)] = 3033,
  [SMALL_STATE(51)] = 3101,
  [SMALL_STATE(52)] = 3169,
  [SMALL_STATE(53)] = 3237,
  [SMALL_STATE(54)] = 3305,
  [SMALL_STATE(55)] = 3373,
  [SMALL_STATE(56)] = 3441,
  [SMALL_STATE(57)] = 3506,
  [SMALL_STATE(58)] = 3571,
  [SMALL_STATE(59)] = 3636,
  [SMALL_STATE(60)] = 3701,
  [SMALL_STATE(61)] = 3766,
  [SMALL_STATE(62)] = 3831,
  [SMALL_STATE(63)] = 3893,
  [SMALL_STATE(64)] = 3955,
  [SMALL_STATE(65)] = 4017,
  [SMALL_STATE(66)] = 4079,
  [SMALL_STATE(67)] = 4141,
  [SMALL_STATE(68)] = 4203,
  [SMALL_STATE(69)] = 4265,
  [SMALL_STATE(70)] = 4327,
  [SMALL_STATE(71)] = 4389,
  [SMALL_STATE(72)] = 4451,
  [SMALL_STATE(73)] = 4513,
  [SMALL_STATE(74)] = 4575,
  [SMALL_STATE(75)] = 4637,
  [SMALL_STATE(76)] = 4699,
  [SMALL_STATE(77)] = 4761,
  [SMALL_STATE(78)] = 4823,
  [SMALL_STATE(79)] = 4885,
  [SMALL_STATE(80)] = 4947,
  [SMALL_STATE(81)] = 5009,
  [SMALL_STATE(82)] = 5071,
  [SMALL_STATE(83)] = 5133,
  [SMALL_STATE(84)] = 5195,
  [SMALL_STATE(85)] = 5257,
  [SMALL_STATE(86)] = 5319,
  [SMALL_STATE(87)] = 5381,
  [SMALL_STATE(88)] = 5443,
  [SMALL_STATE(89)] = 5505,
  [SMALL_STATE(90)] = 5567,
  [SMALL_STATE(91)] = 5629,
  [SMALL_STATE(92)] = 5691,
  [SMALL_STATE(93)] = 5753,
  [SMALL_STATE(94)] = 5815,
  [SMALL_STATE(95)] = 5877,
  [SMALL_STATE(96)] = 5939,
  [SMALL_STATE(97)] = 6001,
  [SMALL_STATE(98)] = 6063,
  [SMALL_STATE(99)] = 6125,
  [SMALL_STATE(100)] = 6187,
  [SMALL_STATE(101)] = 6249,
  [SMALL_STATE(102)] = 6311,
  [SMALL_STATE(103)] = 6373,
  [SMALL_STATE(104)] = 6435,
  [SMALL_STATE(105)] = 6473,
  [SMALL_STATE(106)] = 6517,
  [SMALL_STATE(107)] = 6555,
  [SMALL_STATE(108)] = 6593,
  [SMALL_STATE(109)] = 6631,
  [SMALL_STATE(110)] = 6669,
  [SMALL_STATE(111)] = 6707,
  [SMALL_STATE(112)] = 6745,
  [SMALL_STATE(113)] = 6783,
  [SMALL_STATE(114)] = 6821,
  [SMALL_STATE(115)] = 6859,
  [SMALL_STATE(116)] = 6897,
  [SMALL_STATE(117)] = 6932,
  [SMALL_STATE(118)] = 6967,
  [SMALL_STATE(119)] = 7002,
  [SMALL_STATE(120)] = 7037,
  [SMALL_STATE(121)] = 7072,
  [SMALL_STATE(122)] = 7107,
  [SMALL_STATE(123)] = 7142,
  [SMALL_STATE(124)] = 7177,
  [SMALL_STATE(125)] = 7212,
  [SMALL_STATE(126)] = 7247,
  [SMALL_STATE(127)] = 7282,
  [SMALL_STATE(128)] = 7317,
  [SMALL_STATE(129)] = 7352,
  [SMALL_STATE(130)] = 7387,
  [SMALL_STATE(131)] = 7422,
  [SMALL_STATE(132)] = 7457,
  [SMALL_STATE(133)] = 7492,
  [SMALL_STATE(134)] = 7527,
  [SMALL_STATE(135)] = 7562,
  [SMALL_STATE(136)] = 7597,
  [SMALL_STATE(137)] = 7632,
  [SMALL_STATE(138)] = 7667,
  [SMALL_STATE(139)] = 7700,
  [SMALL_STATE(140)] = 7733,
  [SMALL_STATE(141)] = 7766,
  [SMALL_STATE(142)] = 7799,
  [SMALL_STATE(143)] = 7832,
  [SMALL_STATE(144)] = 7865,
  [SMALL_STATE(145)] = 7898,
  [SMALL_STATE(146)] = 7931,
  [SMALL_STATE(147)] = 7964,
  [SMALL_STATE(148)] = 7997,
  [SMALL_STATE(149)] = 8036,
  [SMALL_STATE(150)] = 8073,
  [SMALL_STATE(151)] = 8109,
  [SMALL_STATE(152)] = 8147,
  [SMALL_STATE(153)] = 8182,
  [SMALL_STATE(154)] = 8217,
  [SMALL_STATE(155)] = 8252,
  [SMALL_STATE(156)] = 8284,
  [SMALL_STATE(157)] = 8316,
  [SMALL_STATE(158)] = 8348,
  [SMALL_STATE(159)] = 8380,
  [SMALL_STATE(160)] = 8412,
  [SMALL_STATE(161)] = 8444,
  [SMALL_STATE(162)] = 8476,
  [SMALL_STATE(163)] = 8508,
  [SMALL_STATE(164)] = 8540,
  [SMALL_STATE(165)] = 8572,
  [SMALL_STATE(166)] = 8604,
  [SMALL_STATE(167)] = 8636,
  [SMALL_STATE(168)] = 8668,
  [SMALL_STATE(169)] = 8700,
  [SMALL_STATE(170)] = 8732,
  [SMALL_STATE(171)] = 8764,
  [SMALL_STATE(172)] = 8796,
  [SMALL_STATE(173)] = 8828,
  [SMALL_STATE(174)] = 8860,
  [SMALL_STATE(175)] = 8892,
  [SMALL_STATE(176)] = 8924,
  [SMALL_STATE(177)] = 8956,
  [SMALL_STATE(178)] = 8988,
  [SMALL_STATE(179)] = 9020,
  [SMALL_STATE(180)] = 9052,
  [SMALL_STATE(181)] = 9084,
  [SMALL_STATE(182)] = 9116,
  [SMALL_STATE(183)] = 9148,
  [SMALL_STATE(184)] = 9180,
  [SMALL_STATE(185)] = 9212,
  [SMALL_STATE(186)] = 9244,
  [SMALL_STATE(187)] = 9286,
  [SMALL_STATE(188)] = 9328,
  [SMALL_STATE(189)] = 9370,
  [SMALL_STATE(190)] = 9412,
  [SMALL_STATE(191)] = 9454,
  [SMALL_STATE(192)] = 9496,
  [SMALL_STATE(193)] = 9538,
  [SMALL_STATE(194)] = 9574,
  [SMALL_STATE(195)] = 9610,
  [SMALL_STATE(196)] = 9646,
  [SMALL_STATE(197)] = 9682,
  [SMALL_STATE(198)] = 9718,
  [SMALL_STATE(199)] = 9754,
  [SMALL_STATE(200)] = 9790,
  [SMALL_STATE(201)] = 9831,
  [SMALL_STATE(202)] = 9872,
  [SMALL_STATE(203)] = 9902,
  [SMALL_STATE(204)] = 9940,
  [SMALL_STATE(205)] = 9970,
  [SMALL_STATE(206)] = 10000,
  [SMALL_STATE(207)] = 10038,
  [SMALL_STATE(208)] = 10068,
  [SMALL_STATE(209)] = 10098,
  [SMALL_STATE(210)] = 10128,
  [SMALL_STATE(211)] = 10166,
  [SMALL_STATE(212)] = 10196,
  [SMALL_STATE(213)] = 10226,
  [SMALL_STATE(214)] = 10248,
  [SMALL_STATE(215)] = 10286,
  [SMALL_STATE(216)] = 10328,
  [SMALL_STATE(217)] = 10366,
  [SMALL_STATE(218)] = 10404,
  [SMALL_STATE(219)] = 10442,
  [SMALL_STATE(220)] = 10480,
  [SMALL_STATE(221)] = 10501,
  [SMALL_STATE(222)] = 10528,
  [SMALL_STATE(223)] = 10555,
  [SMALL_STATE(224)] = 10582,
  [SMALL_STATE(225)] = 10609,
  [SMALL_STATE(226)] = 10636,
  [SMALL_STATE(227)] = 10663,
  [SMALL_STATE(228)] = 10684,
  [SMALL_STATE(229)] = 10705,
  [SMALL_STATE(230)] = 10732,
  [SMALL_STATE(231)] = 10759,
  [SMALL_STATE(232)] = 10786,
  [SMALL_STATE(233)] = 10820,
  [SMALL_STATE(234)] = 10856,
  [SMALL_STATE(235)] = 10890,
  [SMALL_STATE(236)] = 10910,
  [SMALL_STATE(237)] = 10944,
  [SMALL_STATE(238)] = 10978,
  [SMALL_STATE(239)] = 11012,
  [SMALL_STATE(240)] = 11046,
  [SMALL_STATE(241)] = 11080,
  [SMALL_STATE(242)] = 11114,
  [SMALL_STATE(243)] = 11145,
  [SMALL_STATE(244)] = 11166,
  [SMALL_STATE(245)] = 11187,
  [SMALL_STATE(246)] = 11208,
  [SMALL_STATE(247)] = 11229,
  [SMALL_STATE(248)] = 11250,
  [SMALL_STATE(249)] = 11283,
  [SMALL_STATE(250)] = 11316,
  [SMALL_STATE(251)] = 11337,
  [SMALL_STATE(252)] = 11358,
  [SMALL_STATE(253)] = 11379,
  [SMALL_STATE(254)] = 11400,
  [SMALL_STATE(255)] = 11431,
  [SMALL_STATE(256)] = 11452,
  [SMALL_STATE(257)] = 11473,
  [SMALL_STATE(258)] = 11491,
  [SMALL_STATE(259)] = 11509,
  [SMALL_STATE(260)] = 11527,
  [SMALL_STATE(261)] = 11545,
  [SMALL_STATE(262)] = 11563,
  [SMALL_STATE(263)] = 11581,
  [SMALL_STATE(264)] = 11597,
  [SMALL_STATE(265)] = 11613,
  [SMALL_STATE(266)] = 11629,
  [SMALL_STATE(267)] = 11647,
  [SMALL_STATE(268)] = 11677,
  [SMALL_STATE(269)] = 11695,
  [SMALL_STATE(270)] = 11711,
  [SMALL_STATE(271)] = 11729,
  [SMALL_STATE(272)] = 11747,
  [SMALL_STATE(273)] = 11765,
  [SMALL_STATE(274)] = 11783,
  [SMALL_STATE(275)] = 11801,
  [SMALL_STATE(276)] = 11817,
  [SMALL_STATE(277)] = 11833,
  [SMALL_STATE(278)] = 11851,
  [SMALL_STATE(279)] = 11869,
  [SMALL_STATE(280)] = 11885,
  [SMALL_STATE(281)] = 11903,
  [SMALL_STATE(282)] = 11921,
  [SMALL_STATE(283)] = 11939,
  [SMALL_STATE(284)] = 11957,
  [SMALL_STATE(285)] = 11975,
  [SMALL_STATE(286)] = 11993,
  [SMALL_STATE(287)] = 12011,
  [SMALL_STATE(288)] = 12029,
  [SMALL_STATE(289)] = 12047,
  [SMALL_STATE(290)] = 12063,
  [SMALL_STATE(291)] = 12081,
  [SMALL_STATE(292)] = 12099,
  [SMALL_STATE(293)] = 12117,
  [SMALL_STATE(294)] = 12140,
  [SMALL_STATE(295)] = 12156,
  [SMALL_STATE(296)] = 12172,
  [SMALL_STATE(297)] = 12188,
  [SMALL_STATE(298)] = 12204,
  [SMALL_STATE(299)] = 12220,
  [SMALL_STATE(300)] = 12236,
  [SMALL_STATE(301)] = 12260,
  [SMALL_STATE(302)] = 12284,
  [SMALL_STATE(303)] = 12308,
  [SMALL_STATE(304)] = 12324,
  [SMALL_STATE(305)] = 12338,
  [SMALL_STATE(306)] = 12362,
  [SMALL_STATE(307)] = 12387,
  [SMALL_STATE(308)] = 12408,
  [SMALL_STATE(309)] = 12429,
  [SMALL_STATE(310)] = 12450,
  [SMALL_STATE(311)] = 12465,
  [SMALL_STATE(312)] = 12490,
  [SMALL_STATE(313)] = 12512,
  [SMALL_STATE(314)] = 12530,
  [SMALL_STATE(315)] = 12548,
  [SMALL_STATE(316)] = 12568,
  [SMALL_STATE(317)] = 12590,
  [SMALL_STATE(318)] = 12610,
  [SMALL_STATE(319)] = 12630,
  [SMALL_STATE(320)] = 12652,
  [SMALL_STATE(321)] = 12664,
  [SMALL_STATE(322)] = 12686,
  [SMALL_STATE(323)] = 12708,
  [SMALL_STATE(324)] = 12728,
  [SMALL_STATE(325)] = 12750,
  [SMALL_STATE(326)] = 12770,
  [SMALL_STATE(327)] = 12792,
  [SMALL_STATE(328)] = 12814,
  [SMALL_STATE(329)] = 12834,
  [SMALL_STATE(330)] = 12856,
  [SMALL_STATE(331)] = 12873,
  [SMALL_STATE(332)] = 12890,
  [SMALL_STATE(333)] = 12903,
  [SMALL_STATE(334)] = 12920,
  [SMALL_STATE(335)] = 12933,
  [SMALL_STATE(336)] = 12950,
  [SMALL_STATE(337)] = 12969,
  [SMALL_STATE(338)] = 12988,
  [SMALL_STATE(339)] = 13005,
  [SMALL_STATE(340)] = 13020,
  [SMALL_STATE(341)] = 13035,
  [SMALL_STATE(342)] = 13048,
  [SMALL_STATE(343)] = 13063,
  [SMALL_STATE(344)] = 13078,
  [SMALL_STATE(345)] = 13091,
  [SMALL_STATE(346)] = 13108,
  [SMALL_STATE(347)] = 13127,
  [SMALL_STATE(348)] = 13140,
  [SMALL_STATE(349)] = 13157,
  [SMALL_STATE(350)] = 13174,
  [SMALL_STATE(351)] = 13191,
  [SMALL_STATE(352)] = 13206,
  [SMALL_STATE(353)] = 13225,
  [SMALL_STATE(354)] = 13244,
  [SMALL_STATE(355)] = 13263,
  [SMALL_STATE(356)] = 13278,
  [SMALL_STATE(357)] = 13291,
  [SMALL_STATE(358)] = 13308,
  [SMALL_STATE(359)] = 13323,
  [SMALL_STATE(360)] = 13340,
  [SMALL_STATE(361)] = 13359,
  [SMALL_STATE(362)] = 13374,
  [SMALL_STATE(363)] = 13393,
  [SMALL_STATE(364)] = 13410,
  [SMALL_STATE(365)] = 13427,
  [SMALL_STATE(366)] = 13442,
  [SMALL_STATE(367)] = 13457,
  [SMALL_STATE(368)] = 13476,
  [SMALL_STATE(369)] = 13491,
  [SMALL_STATE(370)] = 13508,
  [SMALL_STATE(371)] = 13523,
  [SMALL_STATE(372)] = 13542,
  [SMALL_STATE(373)] = 13557,
  [SMALL_STATE(374)] = 13572,
  [SMALL_STATE(375)] = 13587,
  [SMALL_STATE(376)] = 13602,
  [SMALL_STATE(377)] = 13619,
  [SMALL_STATE(378)] = 13631,
  [SMALL_STATE(379)] = 13641,
  [SMALL_STATE(380)] = 13653,
  [SMALL_STATE(381)] = 13665,
  [SMALL_STATE(382)] = 13679,
  [SMALL_STATE(383)] = 13695,
  [SMALL_STATE(384)] = 13709,
  [SMALL_STATE(385)] = 13725,
  [SMALL_STATE(386)] = 13739,
  [SMALL_STATE(387)] = 13753,
  [SMALL_STATE(388)] = 13769,
  [SMALL_STATE(389)] = 13785,
  [SMALL_STATE(390)] = 13801,
  [SMALL_STATE(391)] = 13817,
  [SMALL_STATE(392)] = 13831,
  [SMALL_STATE(393)] = 13843,
  [SMALL_STATE(394)] = 13859,
  [SMALL_STATE(395)] = 13871,
  [SMALL_STATE(396)] = 13883,
  [SMALL_STATE(397)] = 13899,
  [SMALL_STATE(398)] = 13909,
  [SMALL_STATE(399)] = 13925,
  [SMALL_STATE(400)] = 13939,
  [SMALL_STATE(401)] = 13955,
  [SMALL_STATE(402)] = 13971,
  [SMALL_STATE(403)] = 13987,
  [SMALL_STATE(404)] = 13999,
  [SMALL_STATE(405)] = 14015,
  [SMALL_STATE(406)] = 14031,
  [SMALL_STATE(407)] = 14047,
  [SMALL_STATE(408)] = 14057,
  [SMALL_STATE(409)] = 14073,
  [SMALL_STATE(410)] = 14089,
  [SMALL_STATE(411)] = 14105,
  [SMALL_STATE(412)] = 14121,
  [SMALL_STATE(413)] = 14134,
  [SMALL_STATE(414)] = 14147,
  [SMALL_STATE(415)] = 14160,
  [SMALL_STATE(416)] = 14173,
  [SMALL_STATE(417)] = 14186,
  [SMALL_STATE(418)] = 14199,
  [SMALL_STATE(419)] = 14212,
  [SMALL_STATE(420)] = 14225,
  [SMALL_STATE(421)] = 14238,
  [SMALL_STATE(422)] = 14249,
  [SMALL_STATE(423)] = 14262,
  [SMALL_STATE(424)] = 14275,
  [SMALL_STATE(425)] = 14284,
  [SMALL_STATE(426)] = 14297,
  [SMALL_STATE(427)] = 14310,
  [SMALL_STATE(428)] = 14323,
  [SMALL_STATE(429)] = 14336,
  [SMALL_STATE(430)] = 14349,
  [SMALL_STATE(431)] = 14360,
  [SMALL_STATE(432)] = 14373,
  [SMALL_STATE(433)] = 14384,
  [SMALL_STATE(434)] = 14397,
  [SMALL_STATE(435)] = 14406,
  [SMALL_STATE(436)] = 14419,
  [SMALL_STATE(437)] = 14430,
  [SMALL_STATE(438)] = 14441,
  [SMALL_STATE(439)] = 14452,
  [SMALL_STATE(440)] = 14465,
  [SMALL_STATE(441)] = 14476,
  [SMALL_STATE(442)] = 14487,
  [SMALL_STATE(443)] = 14498,
  [SMALL_STATE(444)] = 14509,
  [SMALL_STATE(445)] = 14520,
  [SMALL_STATE(446)] = 14531,
  [SMALL_STATE(447)] = 14542,
  [SMALL_STATE(448)] = 14555,
  [SMALL_STATE(449)] = 14568,
  [SMALL_STATE(450)] = 14577,
  [SMALL_STATE(451)] = 14590,
  [SMALL_STATE(452)] = 14603,
  [SMALL_STATE(453)] = 14614,
  [SMALL_STATE(454)] = 14627,
  [SMALL_STATE(455)] = 14638,
  [SMALL_STATE(456)] = 14649,
  [SMALL_STATE(457)] = 14662,
  [SMALL_STATE(458)] = 14675,
  [SMALL_STATE(459)] = 14684,
  [SMALL_STATE(460)] = 14697,
  [SMALL_STATE(461)] = 14710,
  [SMALL_STATE(462)] = 14718,
  [SMALL_STATE(463)] = 14728,
  [SMALL_STATE(464)] = 14738,
  [SMALL_STATE(465)] = 14746,
  [SMALL_STATE(466)] = 14754,
  [SMALL_STATE(467)] = 14764,
  [SMALL_STATE(468)] = 14774,
  [SMALL_STATE(469)] = 14784,
  [SMALL_STATE(470)] = 14794,
  [SMALL_STATE(471)] = 14802,
  [SMALL_STATE(472)] = 14812,
  [SMALL_STATE(473)] = 14822,
  [SMALL_STATE(474)] = 14830,
  [SMALL_STATE(475)] = 14840,
  [SMALL_STATE(476)] = 14848,
  [SMALL_STATE(477)] = 14858,
  [SMALL_STATE(478)] = 14868,
  [SMALL_STATE(479)] = 14876,
  [SMALL_STATE(480)] = 14886,
  [SMALL_STATE(481)] = 14896,
  [SMALL_STATE(482)] = 14906,
  [SMALL_STATE(483)] = 14916,
  [SMALL_STATE(484)] = 14926,
  [SMALL_STATE(485)] = 14934,
  [SMALL_STATE(486)] = 14944,
  [SMALL_STATE(487)] = 14954,
  [SMALL_STATE(488)] = 14962,
  [SMALL_STATE(489)] = 14972,
  [SMALL_STATE(490)] = 14982,
  [SMALL_STATE(491)] = 14992,
  [SMALL_STATE(492)] = 15000,
  [SMALL_STATE(493)] = 15008,
  [SMALL_STATE(494)] = 15018,
  [SMALL_STATE(495)] = 15028,
  [SMALL_STATE(496)] = 15036,
  [SMALL_STATE(497)] = 15046,
  [SMALL_STATE(498)] = 15054,
  [SMALL_STATE(499)] = 15064,
  [SMALL_STATE(500)] = 15074,
  [SMALL_STATE(501)] = 15082,
  [SMALL_STATE(502)] = 15092,
  [SMALL_STATE(503)] = 15102,
  [SMALL_STATE(504)] = 15109,
  [SMALL_STATE(505)] = 15116,
  [SMALL_STATE(506)] = 15123,
  [SMALL_STATE(507)] = 15130,
  [SMALL_STATE(508)] = 15137,
  [SMALL_STATE(509)] = 15144,
  [SMALL_STATE(510)] = 15151,
  [SMALL_STATE(511)] = 15158,
  [SMALL_STATE(512)] = 15165,
  [SMALL_STATE(513)] = 15172,
  [SMALL_STATE(514)] = 15179,
  [SMALL_STATE(515)] = 15186,
  [SMALL_STATE(516)] = 15193,
  [SMALL_STATE(517)] = 15200,
  [SMALL_STATE(518)] = 15207,
  [SMALL_STATE(519)] = 15214,
  [SMALL_STATE(520)] = 15221,
  [SMALL_STATE(521)] = 15228,
  [SMALL_STATE(522)] = 15235,
  [SMALL_STATE(523)] = 15242,
  [SMALL_STATE(524)] = 15249,
  [SMALL_STATE(525)] = 15256,
  [SMALL_STATE(526)] = 15263,
  [SMALL_STATE(527)] = 15270,
  [SMALL_STATE(528)] = 15277,
  [SMALL_STATE(529)] = 15284,
  [SMALL_STATE(530)] = 15291,
  [SMALL_STATE(531)] = 15298,
  [SMALL_STATE(532)] = 15305,
  [SMALL_STATE(533)] = 15312,
  [SMALL_STATE(534)] = 15319,
  [SMALL_STATE(535)] = 15326,
  [SMALL_STATE(536)] = 15333,
  [SMALL_STATE(537)] = 15340,
  [SMALL_STATE(538)] = 15347,
  [SMALL_STATE(539)] = 15354,
  [SMALL_STATE(540)] = 15361,
  [SMALL_STATE(541)] = 15368,
  [SMALL_STATE(542)] = 15375,
  [SMALL_STATE(543)] = 15382,
  [SMALL_STATE(544)] = 15389,
  [SMALL_STATE(545)] = 15396,
  [SMALL_STATE(546)] = 15403,
  [SMALL_STATE(547)] = 15410,
  [SMALL_STATE(548)] = 15417,
  [SMALL_STATE(549)] = 15424,
  [SMALL_STATE(550)] = 15431,
  [SMALL_STATE(551)] = 15438,
  [SMALL_STATE(552)] = 15445,
  [SMALL_STATE(553)] = 15452,
  [SMALL_STATE(554)] = 15459,
  [SMALL_STATE(555)] = 15466,
  [SMALL_STATE(556)] = 15473,
  [SMALL_STATE(557)] = 15480,
  [SMALL_STATE(558)] = 15487,
  [SMALL_STATE(559)] = 15494,
  [SMALL_STATE(560)] = 15501,
  [SMALL_STATE(561)] = 15508,
  [SMALL_STATE(562)] = 15515,
  [SMALL_STATE(563)] = 15522,
  [SMALL_STATE(564)] = 15529,
  [SMALL_STATE(565)] = 15536,
  [SMALL_STATE(566)] = 15543,
  [SMALL_STATE(567)] = 15550,
  [SMALL_STATE(568)] = 15557,
  [SMALL_STATE(569)] = 15564,
  [SMALL_STATE(570)] = 15571,
  [SMALL_STATE(571)] = 15578,
  [SMALL_STATE(572)] = 15585,
  [SMALL_STATE(573)] = 15592,
  [SMALL_STATE(574)] = 15599,
  [SMALL_STATE(575)] = 15606,
  [SMALL_STATE(576)] = 15613,
  [SMALL_STATE(577)] = 15620,
  [SMALL_STATE(578)] = 15627,
  [SMALL_STATE(579)] = 15634,
  [SMALL_STATE(580)] = 15641,
  [SMALL_STATE(581)] = 15648,
  [SMALL_STATE(582)] = 15655,
  [SMALL_STATE(583)] = 15662,
  [SMALL_STATE(584)] = 15669,
  [SMALL_STATE(585)] = 15676,
  [SMALL_STATE(586)] = 15683,
  [SMALL_STATE(587)] = 15690,
  [SMALL_STATE(588)] = 15697,
  [SMALL_STATE(589)] = 15704,
  [SMALL_STATE(590)] = 15711,
  [SMALL_STATE(591)] = 15718,
  [SMALL_STATE(592)] = 15725,
  [SMALL_STATE(593)] = 15732,
  [SMALL_STATE(594)] = 15739,
  [SMALL_STATE(595)] = 15746,
  [SMALL_STATE(596)] = 15753,
  [SMALL_STATE(597)] = 15760,
  [SMALL_STATE(598)] = 15767,
  [SMALL_STATE(599)] = 15774,
  [SMALL_STATE(600)] = 15781,
  [SMALL_STATE(601)] = 15788,
  [SMALL_STATE(602)] = 15795,
  [SMALL_STATE(603)] = 15802,
  [SMALL_STATE(604)] = 15809,
  [SMALL_STATE(605)] = 15816,
  [SMALL_STATE(606)] = 15823,
  [SMALL_STATE(607)] = 15830,
  [SMALL_STATE(608)] = 15837,
  [SMALL_STATE(609)] = 15844,
  [SMALL_STATE(610)] = 15851,
  [SMALL_STATE(611)] = 15858,
  [SMALL_STATE(612)] = 15865,
  [SMALL_STATE(613)] = 15872,
  [SMALL_STATE(614)] = 15879,
  [SMALL_STATE(615)] = 15886,
  [SMALL_STATE(616)] = 15893,
  [SMALL_STATE(617)] = 15900,
  [SMALL_STATE(618)] = 15907,
  [SMALL_STATE(619)] = 15914,
  [SMALL_STATE(620)] = 15921,
  [SMALL_STATE(621)] = 15928,
  [SMALL_STATE(622)] = 15935,
  [SMALL_STATE(623)] = 15942,
  [SMALL_STATE(624)] = 15949,
  [SMALL_STATE(625)] = 15956,
  [SMALL_STATE(626)] = 15963,
  [SMALL_STATE(627)] = 15970,
  [SMALL_STATE(628)] = 15977,
  [SMALL_STATE(629)] = 15984,
  [SMALL_STATE(630)] = 15991,
  [SMALL_STATE(631)] = 15998,
  [SMALL_STATE(632)] = 16005,
  [SMALL_STATE(633)] = 16012,
  [SMALL_STATE(634)] = 16019,
  [SMALL_STATE(635)] = 16026,
  [SMALL_STATE(636)] = 16033,
  [SMALL_STATE(637)] = 16040,
  [SMALL_STATE(638)] = 16047,
  [SMALL_STATE(639)] = 16054,
  [SMALL_STATE(640)] = 16061,
  [SMALL_STATE(641)] = 16068,
  [SMALL_STATE(642)] = 16075,
  [SMALL_STATE(643)] = 16082,
  [SMALL_STATE(644)] = 16089,
  [SMALL_STATE(645)] = 16096,
  [SMALL_STATE(646)] = 16103,
  [SMALL_STATE(647)] = 16110,
  [SMALL_STATE(648)] = 16117,
  [SMALL_STATE(649)] = 16124,
  [SMALL_STATE(650)] = 16131,
  [SMALL_STATE(651)] = 16138,
  [SMALL_STATE(652)] = 16145,
  [SMALL_STATE(653)] = 16152,
  [SMALL_STATE(654)] = 16159,
  [SMALL_STATE(655)] = 16166,
  [SMALL_STATE(656)] = 16173,
  [SMALL_STATE(657)] = 16180,
  [SMALL_STATE(658)] = 16187,
  [SMALL_STATE(659)] = 16194,
  [SMALL_STATE(660)] = 16201,
  [SMALL_STATE(661)] = 16208,
  [SMALL_STATE(662)] = 16215,
  [SMALL_STATE(663)] = 16222,
  [SMALL_STATE(664)] = 16229,
  [SMALL_STATE(665)] = 16236,
  [SMALL_STATE(666)] = 16243,
  [SMALL_STATE(667)] = 16250,
  [SMALL_STATE(668)] = 16257,
  [SMALL_STATE(669)] = 16264,
  [SMALL_STATE(670)] = 16271,
  [SMALL_STATE(671)] = 16278,
  [SMALL_STATE(672)] = 16285,
  [SMALL_STATE(673)] = 16292,
  [SMALL_STATE(674)] = 16299,
  [SMALL_STATE(675)] = 16306,
  [SMALL_STATE(676)] = 16313,
  [SMALL_STATE(677)] = 16320,
  [SMALL_STATE(678)] = 16327,
  [SMALL_STATE(679)] = 16334,
  [SMALL_STATE(680)] = 16341,
  [SMALL_STATE(681)] = 16348,
  [SMALL_STATE(682)] = 16355,
  [SMALL_STATE(683)] = 16362,
  [SMALL_STATE(684)] = 16369,
  [SMALL_STATE(685)] = 16376,
  [SMALL_STATE(686)] = 16383,
  [SMALL_STATE(687)] = 16390,
  [SMALL_STATE(688)] = 16397,
  [SMALL_STATE(689)] = 16404,
  [SMALL_STATE(690)] = 16411,
  [SMALL_STATE(691)] = 16418,
  [SMALL_STATE(692)] = 16425,
  [SMALL_STATE(693)] = 16432,
  [SMALL_STATE(694)] = 16439,
  [SMALL_STATE(695)] = 16446,
  [SMALL_STATE(696)] = 16453,
  [SMALL_STATE(697)] = 16460,
  [SMALL_STATE(698)] = 16467,
  [SMALL_STATE(699)] = 16474,
  [SMALL_STATE(700)] = 16481,
  [SMALL_STATE(701)] = 16488,
  [SMALL_STATE(702)] = 16495,
  [SMALL_STATE(703)] = 16502,
  [SMALL_STATE(704)] = 16509,
  [SMALL_STATE(705)] = 16516,
  [SMALL_STATE(706)] = 16523,
  [SMALL_STATE(707)] = 16530,
  [SMALL_STATE(708)] = 16537,
  [SMALL_STATE(709)] = 16544,
  [SMALL_STATE(710)] = 16551,
  [SMALL_STATE(711)] = 16558,
  [SMALL_STATE(712)] = 16565,
  [SMALL_STATE(713)] = 16572,
  [SMALL_STATE(714)] = 16579,
  [SMALL_STATE(715)] = 16586,
  [SMALL_STATE(716)] = 16593,
  [SMALL_STATE(717)] = 16600,
  [SMALL_STATE(718)] = 16607,
  [SMALL_STATE(719)] = 16614,
  [SMALL_STATE(720)] = 16621,
  [SMALL_STATE(721)] = 16628,
  [SMALL_STATE(722)] = 16635,
  [SMALL_STATE(723)] = 16642,
  [SMALL_STATE(724)] = 16649,
  [SMALL_STATE(725)] = 16656,
  [SMALL_STATE(726)] = 16663,
  [SMALL_STATE(727)] = 16670,
  [SMALL_STATE(728)] = 16677,
  [SMALL_STATE(729)] = 16684,
  [SMALL_STATE(730)] = 16691,
  [SMALL_STATE(731)] = 16698,
  [SMALL_STATE(732)] = 16705,
  [SMALL_STATE(733)] = 16712,
  [SMALL_STATE(734)] = 16719,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_script_file, 0),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(246),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [11] = {.entry = {.count = 1, .reusable = false}}, SHIFT(599),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(725),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(724),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(34),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(719),
  [21] = {.entry = {.count = 1, .reusable = false}}, SHIFT(499),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(717),
  [25] = {.entry = {.count = 1, .reusable = false}}, SHIFT(714),
  [27] = {.entry = {.count = 1, .reusable = false}}, SHIFT(495),
  [29] = {.entry = {.count = 1, .reusable = false}}, SHIFT(700),
  [31] = {.entry = {.count = 1, .reusable = false}}, SHIFT(699),
  [33] = {.entry = {.count = 1, .reusable = false}}, SHIFT(698),
  [35] = {.entry = {.count = 1, .reusable = false}}, SHIFT(692),
  [37] = {.entry = {.count = 1, .reusable = false}}, SHIFT(690),
  [39] = {.entry = {.count = 1, .reusable = false}}, SHIFT(689),
  [41] = {.entry = {.count = 1, .reusable = false}}, SHIFT(687),
  [43] = {.entry = {.count = 1, .reusable = false}}, SHIFT(685),
  [45] = {.entry = {.count = 1, .reusable = false}}, SHIFT(683),
  [47] = {.entry = {.count = 1, .reusable = false}}, SHIFT(26),
  [49] = {.entry = {.count = 1, .reusable = false}}, SHIFT(678),
  [51] = {.entry = {.count = 1, .reusable = false}}, SHIFT(677),
  [53] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [55] = {.entry = {.count = 1, .reusable = false}}, SHIFT(616),
  [57] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [59] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [61] = {.entry = {.count = 1, .reusable = true}}, SHIFT(298),
  [63] = {.entry = {.count = 1, .reusable = false}}, SHIFT(498),
  [65] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [67] = {.entry = {.count = 1, .reusable = false}}, SHIFT(72),
  [69] = {.entry = {.count = 1, .reusable = false}}, SHIFT(614),
  [71] = {.entry = {.count = 1, .reusable = false}}, SHIFT(613),
  [73] = {.entry = {.count = 1, .reusable = false}}, SHIFT(124),
  [75] = {.entry = {.count = 1, .reusable = false}}, SHIFT(612),
  [77] = {.entry = {.count = 1, .reusable = false}}, SHIFT(611),
  [79] = {.entry = {.count = 1, .reusable = false}}, SHIFT(610),
  [81] = {.entry = {.count = 1, .reusable = false}}, SHIFT(552),
  [83] = {.entry = {.count = 1, .reusable = false}}, SHIFT(128),
  [85] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_script_file_repeat1, 2),
  [87] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(246),
  [90] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(34),
  [93] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(599),
  [96] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(725),
  [99] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(724),
  [102] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(34),
  [105] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(719),
  [108] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(499),
  [111] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(717),
  [114] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(714),
  [117] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(495),
  [120] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(700),
  [123] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(699),
  [126] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(698),
  [129] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(692),
  [132] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(690),
  [135] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(689),
  [138] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(687),
  [141] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(685),
  [144] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(683),
  [147] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(26),
  [150] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(678),
  [153] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_script_file_repeat1, 2), SHIFT_REPEAT(677),
  [156] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_script_file, 1),
  [158] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [160] = {.entry = {.count = 1, .reusable = true}}, SHIFT(528),
  [162] = {.entry = {.count = 1, .reusable = false}}, SHIFT(533),
  [164] = {.entry = {.count = 1, .reusable = false}}, SHIFT(485),
  [166] = {.entry = {.count = 1, .reusable = false}}, SHIFT(542),
  [168] = {.entry = {.count = 1, .reusable = false}}, SHIFT(12),
  [170] = {.entry = {.count = 1, .reusable = true}}, SHIFT(117),
  [172] = {.entry = {.count = 1, .reusable = false}}, SHIFT(486),
  [174] = {.entry = {.count = 1, .reusable = true}}, SHIFT(187),
  [176] = {.entry = {.count = 1, .reusable = false}}, SHIFT(709),
  [178] = {.entry = {.count = 1, .reusable = false}}, SHIFT(708),
  [180] = {.entry = {.count = 1, .reusable = false}}, SHIFT(703),
  [182] = {.entry = {.count = 1, .reusable = false}}, SHIFT(682),
  [184] = {.entry = {.count = 1, .reusable = false}}, SHIFT(681),
  [186] = {.entry = {.count = 1, .reusable = false}}, SHIFT(680),
  [188] = {.entry = {.count = 1, .reusable = false}}, SHIFT(236),
  [190] = {.entry = {.count = 1, .reusable = false}}, SHIFT(671),
  [192] = {.entry = {.count = 1, .reusable = false}}, SHIFT(117),
  [194] = {.entry = {.count = 1, .reusable = false}}, SHIFT(667),
  [196] = {.entry = {.count = 1, .reusable = false}}, SHIFT(663),
  [198] = {.entry = {.count = 1, .reusable = false}}, SHIFT(661),
  [200] = {.entry = {.count = 1, .reusable = false}}, SHIFT(465),
  [202] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [204] = {.entry = {.count = 1, .reusable = true}}, SHIFT(324),
  [206] = {.entry = {.count = 1, .reusable = true}}, SHIFT(190),
  [208] = {.entry = {.count = 1, .reusable = true}}, SHIFT(191),
  [210] = {.entry = {.count = 1, .reusable = true}}, SHIFT(192),
  [212] = {.entry = {.count = 1, .reusable = true}}, SHIFT(188),
  [214] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_input_section_spec_no_keep, 1),
  [216] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_input_section_spec_no_keep, 1),
  [218] = {.entry = {.count = 1, .reusable = false}}, SHIFT(104),
  [220] = {.entry = {.count = 1, .reusable = false}}, SHIFT(58),
  [222] = {.entry = {.count = 1, .reusable = true}}, SHIFT(189),
  [224] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_statement_list_repeat1, 2), SHIFT_REPEAT(12),
  [227] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_statement_list_repeat1, 2), SHIFT_REPEAT(117),
  [230] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_statement_list_repeat1, 2), SHIFT_REPEAT(486),
  [233] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_statement_list_repeat1, 2),
  [235] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_statement_list_repeat1, 2), SHIFT_REPEAT(709),
  [238] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_statement_list_repeat1, 2), SHIFT_REPEAT(708),
  [241] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_statement_list_repeat1, 2), SHIFT_REPEAT(703),
  [244] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_statement_list_repeat1, 2), SHIFT_REPEAT(682),
  [247] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_statement_list_repeat1, 2), SHIFT_REPEAT(681),
  [250] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_statement_list_repeat1, 2), SHIFT_REPEAT(680),
  [253] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_statement_list_repeat1, 2), SHIFT_REPEAT(236),
  [256] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_statement_list_repeat1, 2), SHIFT_REPEAT(671),
  [259] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_statement_list_repeat1, 2), SHIFT_REPEAT(117),
  [262] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_statement_list_repeat1, 2), SHIFT_REPEAT(667),
  [265] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_statement_list_repeat1, 2), SHIFT_REPEAT(663),
  [268] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_statement_list_repeat1, 2), SHIFT_REPEAT(661),
  [271] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_statement_list_repeat1, 2), SHIFT_REPEAT(690),
  [274] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_statement_list_repeat1, 2), SHIFT_REPEAT(465),
  [277] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_statement_list, 1),
  [279] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filename, 1),
  [281] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_filename, 1),
  [283] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_statement_anywhere, 2),
  [285] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_statement_anywhere, 2),
  [287] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_separator, 1),
  [289] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_separator, 1),
  [291] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory, 4),
  [293] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_memory, 4),
  [295] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory, 3),
  [297] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_memory, 3),
  [299] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ifile_p1, 3),
  [301] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_ifile_p1, 3),
  [303] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_high_level_library, 3),
  [305] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_high_level_library, 3),
  [307] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_low_level_library, 3),
  [309] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_low_level_library, 3),
  [311] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_statement_anywhere, 4),
  [313] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_statement_anywhere, 4),
  [315] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_floating_point_support, 1),
  [317] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_floating_point_support, 1),
  [319] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_version, 4),
  [321] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_version, 4),
  [323] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sections, 4),
  [325] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_sections, 4),
  [327] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_phdrs, 3),
  [329] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_phdrs, 3),
  [331] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_phdrs, 4),
  [333] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_phdrs, 4),
  [335] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sections, 3),
  [337] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_sections, 3),
  [339] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ifile_p1, 2),
  [341] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_ifile_p1, 2),
  [343] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_startup, 4),
  [345] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_startup, 4),
  [347] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ifile_p1, 1),
  [349] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_ifile_p1, 1),
  [351] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ifile_p1, 8),
  [353] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_ifile_p1, 8),
  [355] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_statement_anywhere, 6),
  [357] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_statement_anywhere, 6),
  [359] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_low_level_library, 4),
  [361] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_low_level_library, 4),
  [363] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ifile_p1, 4),
  [365] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_ifile_p1, 4),
  [367] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ifile_p1, 6),
  [369] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_ifile_p1, 6),
  [371] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_high_level_library, 4),
  [373] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_high_level_library, 4),
  [375] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [377] = {.entry = {.count = 1, .reusable = false}}, SHIFT(732),
  [379] = {.entry = {.count = 1, .reusable = false}}, SHIFT(466),
  [381] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [383] = {.entry = {.count = 1, .reusable = false}}, SHIFT(710),
  [385] = {.entry = {.count = 1, .reusable = false}}, SHIFT(711),
  [387] = {.entry = {.count = 1, .reusable = false}}, SHIFT(109),
  [389] = {.entry = {.count = 1, .reusable = false}}, SHIFT(712),
  [391] = {.entry = {.count = 1, .reusable = false}}, SHIFT(733),
  [393] = {.entry = {.count = 1, .reusable = false}}, SHIFT(734),
  [395] = {.entry = {.count = 1, .reusable = false}}, SHIFT(110),
  [397] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [399] = {.entry = {.count = 1, .reusable = false}}, SHIFT(729),
  [401] = {.entry = {.count = 1, .reusable = false}}, SHIFT(474),
  [403] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [405] = {.entry = {.count = 1, .reusable = false}}, SHIFT(695),
  [407] = {.entry = {.count = 1, .reusable = false}}, SHIFT(696),
  [409] = {.entry = {.count = 1, .reusable = false}}, SHIFT(146),
  [411] = {.entry = {.count = 1, .reusable = false}}, SHIFT(697),
  [413] = {.entry = {.count = 1, .reusable = false}}, SHIFT(730),
  [415] = {.entry = {.count = 1, .reusable = false}}, SHIFT(731),
  [417] = {.entry = {.count = 1, .reusable = false}}, SHIFT(145),
  [419] = {.entry = {.count = 1, .reusable = true}}, SHIFT(378),
  [421] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_assign_op, 1),
  [423] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_assign_op, 1),
  [425] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_mustbe_exp, 1),
  [427] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_mustbe_exp, 1),
  [429] = {.entry = {.count = 1, .reusable = false}}, SHIFT(68),
  [431] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [433] = {.entry = {.count = 1, .reusable = true}}, SHIFT(86),
  [435] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_exp, 6),
  [437] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_exp, 6),
  [439] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_exp, 5),
  [441] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_exp, 5),
  [443] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_exp, 4),
  [445] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_exp, 4),
  [447] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_exp, 1),
  [449] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_exp, 1),
  [451] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_INT, 1),
  [453] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_INT, 1),
  [455] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_exp, 2),
  [457] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_exp, 2),
  [459] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_exp, 3),
  [461] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_exp, 3),
  [463] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_paren_script_name, 3),
  [465] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_paren_script_name, 3),
  [467] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_statement, 1),
  [469] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_statement, 1),
  [471] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_input_section_spec_no_keep, 4),
  [473] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_input_section_spec_no_keep, 4),
  [475] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_input_section_spec_no_keep, 3),
  [477] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_input_section_spec_no_keep, 3),
  [479] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_statement, 7),
  [481] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_statement, 7),
  [483] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_input_section_spec, 4),
  [485] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_input_section_spec, 4),
  [487] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_input_section_spec, 1),
  [489] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_input_section_spec, 1),
  [491] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_input_section_spec_no_keep, 2),
  [493] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_input_section_spec_no_keep, 2),
  [495] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_statement, 4),
  [497] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_statement, 4),
  [499] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_statement, 2),
  [501] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_statement, 2),
  [503] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_input_section_spec_no_keep, 5),
  [505] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_input_section_spec_no_keep, 5),
  [507] = {.entry = {.count = 1, .reusable = false}}, SHIFT(93),
  [509] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [511] = {.entry = {.count = 1, .reusable = true}}, SHIFT(90),
  [513] = {.entry = {.count = 1, .reusable = false}}, SHIFT(92),
  [515] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [517] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [519] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_phdr_type, 1),
  [521] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_phdr_type, 1),
  [523] = {.entry = {.count = 1, .reusable = true}}, SHIFT(293),
  [525] = {.entry = {.count = 1, .reusable = true}}, SHIFT(297),
  [527] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [529] = {.entry = {.count = 1, .reusable = true}}, SHIFT(108),
  [531] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [533] = {.entry = {.count = 1, .reusable = true}}, SHIFT(119),
  [535] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [537] = {.entry = {.count = 1, .reusable = true}}, SHIFT(143),
  [539] = {.entry = {.count = 1, .reusable = true}}, SHIFT(126),
  [541] = {.entry = {.count = 1, .reusable = true}}, SHIFT(508),
  [543] = {.entry = {.count = 1, .reusable = true}}, SHIFT(443),
  [545] = {.entry = {.count = 1, .reusable = true}}, SHIFT(691),
  [547] = {.entry = {.count = 1, .reusable = true}}, SHIFT(444),
  [549] = {.entry = {.count = 1, .reusable = true}}, SHIFT(406),
  [551] = {.entry = {.count = 1, .reusable = true}}, SHIFT(675),
  [553] = {.entry = {.count = 1, .reusable = true}}, SHIFT(672),
  [555] = {.entry = {.count = 1, .reusable = true}}, SHIFT(418),
  [557] = {.entry = {.count = 1, .reusable = true}}, SHIFT(106),
  [559] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [561] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [563] = {.entry = {.count = 1, .reusable = true}}, SHIFT(113),
  [565] = {.entry = {.count = 1, .reusable = true}}, SHIFT(632),
  [567] = {.entry = {.count = 1, .reusable = true}}, SHIFT(147),
  [569] = {.entry = {.count = 1, .reusable = true}}, SHIFT(320),
  [571] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [573] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type, 3),
  [575] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [577] = {.entry = {.count = 1, .reusable = true}}, SHIFT(538),
  [579] = {.entry = {.count = 1, .reusable = true}}, SHIFT(506),
  [581] = {.entry = {.count = 1, .reusable = true}}, SHIFT(397),
  [583] = {.entry = {.count = 1, .reusable = true}}, SHIFT(407),
  [585] = {.entry = {.count = 1, .reusable = true}}, SHIFT(140),
  [587] = {.entry = {.count = 1, .reusable = true}}, SHIFT(310),
  [589] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_section, 10),
  [591] = {.entry = {.count = 1, .reusable = true}}, SHIFT(257),
  [593] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section, 10),
  [595] = {.entry = {.count = 1, .reusable = false}}, SHIFT(41),
  [597] = {.entry = {.count = 1, .reusable = true}}, SHIFT(605),
  [599] = {.entry = {.count = 1, .reusable = true}}, SHIFT(602),
  [601] = {.entry = {.count = 1, .reusable = false}}, SHIFT(601),
  [603] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_section, 8),
  [605] = {.entry = {.count = 1, .reusable = true}}, SHIFT(259),
  [607] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section, 8),
  [609] = {.entry = {.count = 1, .reusable = false}}, SHIFT(54),
  [611] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_section, 5),
  [613] = {.entry = {.count = 1, .reusable = true}}, SHIFT(278),
  [615] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section, 5),
  [617] = {.entry = {.count = 1, .reusable = false}}, SHIFT(48),
  [619] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_section, 7),
  [621] = {.entry = {.count = 1, .reusable = true}}, SHIFT(271),
  [623] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section, 7),
  [625] = {.entry = {.count = 1, .reusable = false}}, SHIFT(53),
  [627] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_section, 6),
  [629] = {.entry = {.count = 1, .reusable = true}}, SHIFT(286),
  [631] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section, 6),
  [633] = {.entry = {.count = 1, .reusable = false}}, SHIFT(46),
  [635] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_section, 4),
  [637] = {.entry = {.count = 1, .reusable = true}}, SHIFT(283),
  [639] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section, 4),
  [641] = {.entry = {.count = 1, .reusable = false}}, SHIFT(42),
  [643] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_section, 9),
  [645] = {.entry = {.count = 1, .reusable = true}}, SHIFT(258),
  [647] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section, 9),
  [649] = {.entry = {.count = 1, .reusable = false}}, SHIFT(50),
  [651] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_section, 11),
  [653] = {.entry = {.count = 1, .reusable = true}}, SHIFT(287),
  [655] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section, 11),
  [657] = {.entry = {.count = 1, .reusable = false}}, SHIFT(45),
  [659] = {.entry = {.count = 1, .reusable = false}}, SHIFT(2),
  [661] = {.entry = {.count = 1, .reusable = false}}, SHIFT(17),
  [663] = {.entry = {.count = 1, .reusable = false}}, SHIFT(494),
  [665] = {.entry = {.count = 1, .reusable = true}}, SHIFT(266),
  [667] = {.entry = {.count = 1, .reusable = false}}, SHIFT(694),
  [669] = {.entry = {.count = 1, .reusable = false}}, SHIFT(728),
  [671] = {.entry = {.count = 1, .reusable = false}}, SHIFT(52),
  [673] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [675] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sec_or_group_p1, 1),
  [677] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_section_name_list_repeat1, 2), SHIFT_REPEAT(254),
  [680] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_section_name_list_repeat1, 2), SHIFT_REPEAT(597),
  [683] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_section_name_list_repeat1, 2), SHIFT_REPEAT(596),
  [686] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_section_name_list_repeat1, 2), SHIFT_REPEAT(595),
  [689] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_section_name_list_repeat1, 2), SHIFT_REPEAT(721),
  [692] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_section_name_list_repeat1, 2),
  [694] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_section_name_list_repeat1, 2), SHIFT_REPEAT(264),
  [697] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_section, 12),
  [699] = {.entry = {.count = 1, .reusable = true}}, SHIFT(280),
  [701] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section, 12),
  [703] = {.entry = {.count = 1, .reusable = false}}, SHIFT(47),
  [705] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_sec_or_group_p1_repeat1, 2), SHIFT_REPEAT(2),
  [708] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_sec_or_group_p1_repeat1, 2), SHIFT_REPEAT(17),
  [711] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_sec_or_group_p1_repeat1, 2), SHIFT_REPEAT(494),
  [714] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_sec_or_group_p1_repeat1, 2),
  [716] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_sec_or_group_p1_repeat1, 2), SHIFT_REPEAT(694),
  [719] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_sec_or_group_p1_repeat1, 2), SHIFT_REPEAT(728),
  [722] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_sec_or_group_p1_repeat1, 2), SHIFT_REPEAT(690),
  [725] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_sec_or_group_p1_repeat1, 2), SHIFT_REPEAT(52),
  [728] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_memspec, 2),
  [730] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memspec, 2),
  [732] = {.entry = {.count = 1, .reusable = false}}, SHIFT(254),
  [734] = {.entry = {.count = 1, .reusable = false}}, SHIFT(597),
  [736] = {.entry = {.count = 1, .reusable = false}}, SHIFT(596),
  [738] = {.entry = {.count = 1, .reusable = false}}, SHIFT(595),
  [740] = {.entry = {.count = 1, .reusable = false}}, SHIFT(721),
  [742] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_section_name_list, 2),
  [744] = {.entry = {.count = 1, .reusable = false}}, SHIFT(264),
  [746] = {.entry = {.count = 1, .reusable = false}}, SHIFT(541),
  [748] = {.entry = {.count = 1, .reusable = false}}, SHIFT(238),
  [750] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_section_name_list, 1),
  [752] = {.entry = {.count = 1, .reusable = false}}, SHIFT(242),
  [754] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section_name_list, 1),
  [756] = {.entry = {.count = 1, .reusable = false}}, SHIFT(704),
  [758] = {.entry = {.count = 1, .reusable = false}}, SHIFT(705),
  [760] = {.entry = {.count = 1, .reusable = false}}, SHIFT(706),
  [762] = {.entry = {.count = 1, .reusable = false}}, SHIFT(727),
  [764] = {.entry = {.count = 1, .reusable = false}}, SHIFT(285),
  [766] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_section_name_list_repeat1, 2), SHIFT_REPEAT(242),
  [769] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_section_name_list_repeat1, 2),
  [771] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_section_name_list_repeat1, 2), SHIFT_REPEAT(704),
  [774] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_section_name_list_repeat1, 2), SHIFT_REPEAT(705),
  [777] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_section_name_list_repeat1, 2), SHIFT_REPEAT(706),
  [780] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_section_name_list_repeat1, 2), SHIFT_REPEAT(727),
  [783] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_section_name_list_repeat1, 2), SHIFT_REPEAT(285),
  [786] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section_name_list, 2),
  [788] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_phdr_opt, 3),
  [790] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_phdr_opt, 3),
  [792] = {.entry = {.count = 1, .reusable = true}}, SHIFT(558),
  [794] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_memspec_at, 3),
  [796] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memspec_at, 3),
  [798] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_phdr_opt, 2),
  [800] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_phdr_opt, 2),
  [802] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_section, 13),
  [804] = {.entry = {.count = 1, .reusable = true}}, SHIFT(274),
  [806] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section, 13),
  [808] = {.entry = {.count = 1, .reusable = false}}, SHIFT(43),
  [810] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [812] = {.entry = {.count = 1, .reusable = false}}, SHIFT(567),
  [814] = {.entry = {.count = 1, .reusable = true}}, SHIFT(563),
  [816] = {.entry = {.count = 1, .reusable = true}}, SHIFT(565),
  [818] = {.entry = {.count = 1, .reusable = true}}, SHIFT(571),
  [820] = {.entry = {.count = 1, .reusable = true}}, SHIFT(308),
  [822] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_fill_exp, 1),
  [824] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_fill_exp, 1),
  [826] = {.entry = {.count = 1, .reusable = false}}, SHIFT(130),
  [828] = {.entry = {.count = 1, .reusable = false}}, SHIFT(232),
  [830] = {.entry = {.count = 1, .reusable = false}}, SHIFT(593),
  [832] = {.entry = {.count = 1, .reusable = false}}, SHIFT(234),
  [834] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_section, 15),
  [836] = {.entry = {.count = 1, .reusable = true}}, SHIFT(272),
  [838] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section, 15),
  [840] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_section, 14),
  [842] = {.entry = {.count = 1, .reusable = true}}, SHIFT(273),
  [844] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section, 14),
  [846] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_section_name_spec, 4),
  [848] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_wildcard_maybe_exclude, 1),
  [850] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_wildcard_maybe_reverse, 1),
  [852] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [854] = {.entry = {.count = 1, .reusable = true}}, SHIFT(307),
  [856] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_section_name_spec, 1),
  [858] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section_name_spec, 1),
  [860] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_section, 16),
  [862] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section, 16),
  [864] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_wildcard_maybe_reverse, 4),
  [866] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_wildcard_maybe_exclude, 5),
  [868] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section_name_spec, 4),
  [870] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_section_name_spec, 7),
  [872] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section_name_spec, 7),
  [874] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_wildcard_maybe_exclude, 1),
  [876] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_wildcard_maybe_reverse, 1),
  [878] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_wildcard_maybe_exclude, 5),
  [880] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_wildcard_maybe_reverse, 4),
  [882] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_section, 2),
  [884] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section, 2),
  [886] = {.entry = {.count = 1, .reusable = true}}, SHIFT(533),
  [888] = {.entry = {.count = 1, .reusable = true}}, SHIFT(485),
  [890] = {.entry = {.count = 1, .reusable = true}}, SHIFT(542),
  [892] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_opt_exp_with_type, 5),
  [894] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_opt_exp_with_type, 5),
  [896] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_opt_exp_with_type, 9),
  [898] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_opt_exp_with_type, 9),
  [900] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_opt_exp_with_type, 6),
  [902] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_opt_exp_with_type, 6),
  [904] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_opt_exp_with_type, 2),
  [906] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_opt_exp_with_type, 2),
  [908] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_opt_exp_with_type, 1),
  [910] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_opt_exp_with_type, 1),
  [912] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_opt_exp_with_type, 10),
  [914] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_opt_exp_with_type, 10),
  [916] = {.entry = {.count = 1, .reusable = false}}, SHIFT(519),
  [918] = {.entry = {.count = 1, .reusable = false}}, SHIFT(555),
  [920] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [922] = {.entry = {.count = 1, .reusable = true}}, SHIFT(309),
  [924] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_opt_exp_with_type, 3),
  [926] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_opt_exp_with_type, 3),
  [928] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_sect_flags, 4),
  [930] = {.entry = {.count = 1, .reusable = false}}, SHIFT(722),
  [932] = {.entry = {.count = 1, .reusable = true}}, SHIFT(390),
  [934] = {.entry = {.count = 1, .reusable = false}}, SHIFT(462),
  [936] = {.entry = {.count = 1, .reusable = false}}, SHIFT(480),
  [938] = {.entry = {.count = 1, .reusable = false}}, SHIFT(445),
  [940] = {.entry = {.count = 1, .reusable = false}}, SHIFT(475),
  [942] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [944] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_at, 4),
  [946] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_at, 4),
  [948] = {.entry = {.count = 1, .reusable = true}}, SHIFT(510),
  [950] = {.entry = {.count = 1, .reusable = false}}, SHIFT(554),
  [952] = {.entry = {.count = 1, .reusable = false}}, SHIFT(507),
  [954] = {.entry = {.count = 1, .reusable = false}}, SHIFT(723),
  [956] = {.entry = {.count = 1, .reusable = false}}, SHIFT(414),
  [958] = {.entry = {.count = 1, .reusable = true}}, SHIFT(460),
  [960] = {.entry = {.count = 1, .reusable = false}}, SHIFT(489),
  [962] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory_spec_list, 1),
  [964] = {.entry = {.count = 1, .reusable = true}}, SHIFT(353),
  [966] = {.entry = {.count = 1, .reusable = true}}, SHIFT(405),
  [968] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_memory_spec_list_repeat1, 2), SHIFT_REPEAT(414),
  [971] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_memory_spec_list_repeat1, 2), SHIFT_REPEAT(460),
  [974] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_memory_spec_list_repeat1, 2), SHIFT_REPEAT(489),
  [977] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_memory_spec_list_repeat1, 2),
  [979] = {.entry = {.count = 1, .reusable = false}}, SHIFT(344),
  [981] = {.entry = {.count = 1, .reusable = true}}, SHIFT(432),
  [983] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_low_level_library_NAME_list, 1),
  [985] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_input_list_repeat1, 2), SHIFT_REPEAT(319),
  [988] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_input_list_repeat1, 2), SHIFT_REPEAT(415),
  [991] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_input_list_repeat1, 2),
  [993] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_input_list_repeat1, 2), SHIFT_REPEAT(564),
  [996] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_input_list_repeat1, 2), SHIFT_REPEAT(319),
  [999] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_align, 4),
  [1001] = {.entry = {.count = 1, .reusable = false}}, SHIFT(329),
  [1003] = {.entry = {.count = 1, .reusable = true}}, SHIFT(415),
  [1005] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_input_list, 1),
  [1007] = {.entry = {.count = 1, .reusable = false}}, SHIFT(564),
  [1009] = {.entry = {.count = 1, .reusable = true}}, SHIFT(329),
  [1011] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_overlay_section_repeat1, 4),
  [1013] = {.entry = {.count = 1, .reusable = true}}, SHIFT(488),
  [1015] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_overlay_section_repeat1, 4),
  [1017] = {.entry = {.count = 1, .reusable = false}}, SHIFT(44),
  [1019] = {.entry = {.count = 1, .reusable = true}}, SHIFT(641),
  [1021] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_low_level_library_NAME_list, 2),
  [1023] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_overlay_section_repeat1, 3),
  [1025] = {.entry = {.count = 1, .reusable = true}}, SHIFT(483),
  [1027] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_overlay_section_repeat1, 3),
  [1029] = {.entry = {.count = 1, .reusable = false}}, SHIFT(49),
  [1031] = {.entry = {.count = 1, .reusable = true}}, SHIFT(437),
  [1033] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [1035] = {.entry = {.count = 1, .reusable = false}}, SHIFT(327),
  [1037] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_input_list, 4),
  [1039] = {.entry = {.count = 1, .reusable = true}}, SHIFT(327),
  [1041] = {.entry = {.count = 1, .reusable = false}}, SHIFT(319),
  [1043] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_input_list, 5),
  [1045] = {.entry = {.count = 1, .reusable = true}}, SHIFT(319),
  [1047] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory_spec_list, 2),
  [1049] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_input_list, 2),
  [1051] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_vers_nodes_repeat1, 2), SHIFT_REPEAT(311),
  [1054] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_vers_nodes_repeat1, 2),
  [1056] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_vers_nodes_repeat1, 2), SHIFT_REPEAT(577),
  [1059] = {.entry = {.count = 1, .reusable = false}}, SHIFT(549),
  [1061] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_input_list_repeat1, 4),
  [1063] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_input_list_repeat1, 4),
  [1065] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_phdr_qualifiers_repeat1, 1),
  [1067] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_phdr_qualifiers_repeat1, 1),
  [1069] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [1071] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_input_list_repeat1, 2),
  [1073] = {.entry = {.count = 1, .reusable = false}}, SHIFT(57),
  [1075] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [1077] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [1079] = {.entry = {.count = 1, .reusable = true}}, SHIFT(645),
  [1081] = {.entry = {.count = 1, .reusable = true}}, SHIFT(311),
  [1083] = {.entry = {.count = 1, .reusable = true}}, SHIFT(577),
  [1085] = {.entry = {.count = 1, .reusable = true}}, SHIFT(487),
  [1087] = {.entry = {.count = 1, .reusable = false}}, SHIFT(497),
  [1089] = {.entry = {.count = 1, .reusable = false}}, SHIFT(421),
  [1091] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_low_level_library_NAME_list_repeat2, 2),
  [1093] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_high_level_library_NAME_list_repeat1, 2), SHIFT_REPEAT(344),
  [1096] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_high_level_library_NAME_list_repeat1, 2), SHIFT_REPEAT(463),
  [1099] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_high_level_library_NAME_list_repeat1, 2),
  [1101] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_input_list_repeat1, 5),
  [1103] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_input_list_repeat1, 5),
  [1105] = {.entry = {.count = 1, .reusable = true}}, SHIFT(381),
  [1107] = {.entry = {.count = 1, .reusable = true}}, SHIFT(626),
  [1109] = {.entry = {.count = 1, .reusable = false}}, SHIFT(626),
  [1111] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_attributes_list_repeat1, 2), SHIFT_REPEAT(441),
  [1114] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_attributes_list_repeat1, 2),
  [1116] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_attributes_list_repeat1, 2), SHIFT_REPEAT(588),
  [1119] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_vers_nodes, 1),
  [1121] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_vers_tag, 8),
  [1123] = {.entry = {.count = 1, .reusable = true}}, SHIFT(382),
  [1125] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_vers_tag, 4),
  [1127] = {.entry = {.count = 1, .reusable = false}}, SHIFT(476),
  [1129] = {.entry = {.count = 1, .reusable = true}}, SHIFT(399),
  [1131] = {.entry = {.count = 1, .reusable = false}}, SHIFT(333),
  [1133] = {.entry = {.count = 1, .reusable = true}}, SHIFT(502),
  [1135] = {.entry = {.count = 1, .reusable = false}}, SHIFT(609),
  [1137] = {.entry = {.count = 1, .reusable = false}}, SHIFT(441),
  [1139] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attributes_list, 1),
  [1141] = {.entry = {.count = 1, .reusable = true}}, SHIFT(588),
  [1143] = {.entry = {.count = 1, .reusable = true}}, SHIFT(463),
  [1145] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_high_level_library_NAME_list, 1),
  [1147] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_low_level_library_NAME_list_repeat1, 2), SHIFT_REPEAT(344),
  [1150] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_low_level_library_NAME_list_repeat1, 2),
  [1152] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [1154] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_overlay_section_repeat1, 5),
  [1156] = {.entry = {.count = 1, .reusable = true}}, SHIFT(467),
  [1158] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_overlay_section_repeat1, 5),
  [1160] = {.entry = {.count = 1, .reusable = false}}, SHIFT(51),
  [1162] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_vers_tag, 2),
  [1164] = {.entry = {.count = 1, .reusable = true}}, SHIFT(478),
  [1166] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_high_level_library_NAME_list, 2),
  [1168] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_length_spec, 3),
  [1170] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_length_spec, 3),
  [1172] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_opt_exp_without_type, 1),
  [1174] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_origin_spec, 3),
  [1176] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_origin_spec, 3),
  [1178] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_memory_spec, 5),
  [1180] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory_spec, 5),
  [1182] = {.entry = {.count = 1, .reusable = false}}, SHIFT(718),
  [1184] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_phdr_list_repeat1, 2), SHIFT_REPEAT(57),
  [1187] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_phdr_list_repeat1, 2),
  [1189] = {.entry = {.count = 1, .reusable = false}}, SHIFT(321),
  [1191] = {.entry = {.count = 1, .reusable = false}}, SHIFT(628),
  [1193] = {.entry = {.count = 1, .reusable = true}}, SHIFT(321),
  [1195] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_phdr_list, 1),
  [1197] = {.entry = {.count = 1, .reusable = true}}, SHIFT(572),
  [1199] = {.entry = {.count = 1, .reusable = false}}, SHIFT(572),
  [1201] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [1203] = {.entry = {.count = 1, .reusable = true}}, SHIFT(424),
  [1205] = {.entry = {.count = 1, .reusable = true}}, SHIFT(420),
  [1207] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_memory_spec_list_repeat1, 2),
  [1209] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_extern_name_list_repeat1, 2), SHIFT_REPEAT(393),
  [1212] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_extern_name_list_repeat1, 2), SHIFT_REPEAT(559),
  [1215] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_extern_name_list_repeat1, 2),
  [1217] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_memory_spec, 6),
  [1219] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory_spec, 6),
  [1221] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_memory_spec, 2),
  [1223] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory_spec, 2),
  [1225] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_phdr_qualifiers_repeat1, 2), SHIFT_REPEAT(333),
  [1228] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_phdr_qualifiers_repeat1, 2),
  [1230] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_phdr_qualifiers_repeat1, 2), SHIFT_REPEAT(609),
  [1233] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_subalign, 4),
  [1235] = {.entry = {.count = 1, .reusable = false}}, SHIFT(408),
  [1237] = {.entry = {.count = 1, .reusable = true}}, SHIFT(501),
  [1239] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_nocrossref_list, 1),
  [1241] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_phdr_qualifiers, 1),
  [1243] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_memory_spec, 4),
  [1245] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory_spec, 4),
  [1247] = {.entry = {.count = 1, .reusable = true}}, SHIFT(294),
  [1249] = {.entry = {.count = 1, .reusable = true}}, SHIFT(570),
  [1251] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_opt_exp_without_type, 2),
  [1253] = {.entry = {.count = 1, .reusable = false}}, SHIFT(393),
  [1255] = {.entry = {.count = 1, .reusable = true}}, SHIFT(469),
  [1257] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_nocrossref_list, 2),
  [1259] = {.entry = {.count = 1, .reusable = false}}, SHIFT(410),
  [1261] = {.entry = {.count = 1, .reusable = true}}, SHIFT(559),
  [1263] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_extern_name_list, 1),
  [1265] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_extern_name_list, 2),
  [1267] = {.entry = {.count = 1, .reusable = true}}, SHIFT(458),
  [1269] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sect_flag_list, 2),
  [1271] = {.entry = {.count = 1, .reusable = true}}, SHIFT(512),
  [1273] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_verdep_repeat1, 2),
  [1275] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_verdep_repeat1, 2), SHIFT_REPEAT(413),
  [1278] = {.entry = {.count = 1, .reusable = true}}, SHIFT(369),
  [1280] = {.entry = {.count = 1, .reusable = true}}, SHIFT(386),
  [1282] = {.entry = {.count = 1, .reusable = false}}, SHIFT(334),
  [1284] = {.entry = {.count = 1, .reusable = false}}, SHIFT(526),
  [1286] = {.entry = {.count = 1, .reusable = true}}, SHIFT(334),
  [1288] = {.entry = {.count = 1, .reusable = true}}, SHIFT(402),
  [1290] = {.entry = {.count = 1, .reusable = true}}, SHIFT(295),
  [1292] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_low_level_library_NAME_list_repeat2, 2), SHIFT_REPEAT(432),
  [1295] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_verdep, 1),
  [1297] = {.entry = {.count = 1, .reusable = true}}, SHIFT(413),
  [1299] = {.entry = {.count = 1, .reusable = false}}, SHIFT(573),
  [1301] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_vers_defns, 3),
  [1303] = {.entry = {.count = 1, .reusable = false}}, SHIFT(426),
  [1305] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_vers_node, 4),
  [1307] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_overlay_section, 1),
  [1309] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_exclude_name_list, 1),
  [1311] = {.entry = {.count = 1, .reusable = false}}, SHIFT(448),
  [1313] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sect_flag_list, 1),
  [1315] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_overlay_section_repeat1, 7),
  [1317] = {.entry = {.count = 1, .reusable = true}}, SHIFT(496),
  [1319] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_overlay_section_repeat1, 7),
  [1321] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_sect_flag_list_repeat1, 2),
  [1323] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_sect_flag_list_repeat1, 2), SHIFT_REPEAT(512),
  [1326] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_phdr_qualifiers_repeat1, 2),
  [1328] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_vers_node, 3),
  [1330] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_attributes_string, 2),
  [1332] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attributes_string, 2),
  [1334] = {.entry = {.count = 1, .reusable = true}}, SHIFT(127),
  [1336] = {.entry = {.count = 1, .reusable = true}}, SHIFT(260),
  [1338] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_attributes_string, 1),
  [1340] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attributes_string, 1),
  [1342] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [1344] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_phdr_qualifiers_repeat1, 4),
  [1346] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_phdr_qualifiers_repeat1, 4),
  [1348] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_phdr_val, 3),
  [1350] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_phdr_val, 3),
  [1352] = {.entry = {.count = 1, .reusable = false}}, SHIFT(629),
  [1354] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_vers_defns, 1),
  [1356] = {.entry = {.count = 1, .reusable = false}}, SHIFT(400),
  [1358] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [1360] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_exclude_name_list_repeat1, 2),
  [1362] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_exclude_name_list_repeat1, 2), SHIFT_REPEAT(448),
  [1365] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_vers_node, 6),
  [1367] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_overlay_section_repeat1, 6),
  [1369] = {.entry = {.count = 1, .reusable = true}}, SHIFT(490),
  [1371] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_overlay_section_repeat1, 6),
  [1373] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_overlay_section_repeat1, 2), SHIFT_REPEAT(718),
  [1376] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_overlay_section_repeat1, 2),
  [1378] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_high_level_library_NAME_list_repeat1, 2),
  [1380] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_extern_name_list_repeat1, 2),
  [1382] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_low_level_library_NAME_list, 3),
  [1384] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_vers_node, 5),
  [1386] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_assignment, 3),
  [1388] = {.entry = {.count = 1, .reusable = true}}, SHIFT(358),
  [1390] = {.entry = {.count = 1, .reusable = true}}, SHIFT(686),
  [1392] = {.entry = {.count = 1, .reusable = false}}, SHIFT(409),
  [1394] = {.entry = {.count = 1, .reusable = false}}, SHIFT(455),
  [1396] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_nocrossref_list, 3),
  [1398] = {.entry = {.count = 1, .reusable = true}}, SHIFT(568),
  [1400] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [1402] = {.entry = {.count = 1, .reusable = true}}, SHIFT(372),
  [1404] = {.entry = {.count = 1, .reusable = true}}, SHIFT(473),
  [1406] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_vers_defns, 5),
  [1408] = {.entry = {.count = 1, .reusable = true}}, SHIFT(668),
  [1410] = {.entry = {.count = 1, .reusable = true}}, SHIFT(342),
  [1412] = {.entry = {.count = 1, .reusable = false}}, SHIFT(16),
  [1414] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_vers_defns, 6),
  [1416] = {.entry = {.count = 1, .reusable = true}}, SHIFT(339),
  [1418] = {.entry = {.count = 1, .reusable = true}}, SHIFT(500),
  [1420] = {.entry = {.count = 1, .reusable = true}}, SHIFT(361),
  [1422] = {.entry = {.count = 1, .reusable = false}}, SHIFT(427),
  [1424] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_assignment, 6),
  [1426] = {.entry = {.count = 1, .reusable = true}}, SHIFT(674),
  [1428] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type, 1),
  [1430] = {.entry = {.count = 1, .reusable = false}}, SHIFT(137),
  [1432] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_vers_defns, 8),
  [1434] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_phdr, 4),
  [1436] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_phdr, 4),
  [1438] = {.entry = {.count = 1, .reusable = false}}, SHIFT(284),
  [1440] = {.entry = {.count = 1, .reusable = true}}, SHIFT(660),
  [1442] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_overlay_section_repeat1, 8),
  [1444] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_overlay_section_repeat1, 8),
  [1446] = {.entry = {.count = 1, .reusable = true}}, SHIFT(509),
  [1448] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_vers_defns, 7),
  [1450] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_phdr, 3),
  [1452] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_phdr, 3),
  [1454] = {.entry = {.count = 1, .reusable = true}}, SHIFT(121),
  [1456] = {.entry = {.count = 1, .reusable = true}}, SHIFT(438),
  [1458] = {.entry = {.count = 1, .reusable = true}}, SHIFT(529),
  [1460] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type, 6),
  [1462] = {.entry = {.count = 1, .reusable = true}}, SHIFT(423),
  [1464] = {.entry = {.count = 1, .reusable = false}}, SHIFT(504),
  [1466] = {.entry = {.count = 1, .reusable = false}}, SHIFT(503),
  [1468] = {.entry = {.count = 1, .reusable = true}}, SHIFT(434),
  [1470] = {.entry = {.count = 1, .reusable = true}}, SHIFT(631),
  [1472] = {.entry = {.count = 1, .reusable = false}}, SHIFT(492),
  [1474] = {.entry = {.count = 1, .reusable = true}}, SHIFT(136),
  [1476] = {.entry = {.count = 1, .reusable = true}}, SHIFT(351),
  [1478] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filename_spec, 4),
  [1480] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [1482] = {.entry = {.count = 1, .reusable = false}}, SHIFT(491),
  [1484] = {.entry = {.count = 1, .reusable = true}}, SHIFT(371),
  [1486] = {.entry = {.count = 1, .reusable = true}}, SHIFT(263),
  [1488] = {.entry = {.count = 1, .reusable = true}}, SHIFT(449),
  [1490] = {.entry = {.count = 1, .reusable = true}}, SHIFT(639),
  [1492] = {.entry = {.count = 1, .reusable = true}}, SHIFT(391),
  [1494] = {.entry = {.count = 1, .reusable = true}}, SHIFT(326),
  [1496] = {.entry = {.count = 1, .reusable = true}}, SHIFT(389),
  [1498] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [1500] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_atype, 2),
  [1502] = {.entry = {.count = 1, .reusable = true}}, SHIFT(545),
  [1504] = {.entry = {.count = 1, .reusable = true}}, SHIFT(546),
  [1506] = {.entry = {.count = 1, .reusable = true}}, SHIFT(186),
  [1508] = {.entry = {.count = 1, .reusable = true}}, SHIFT(118),
  [1510] = {.entry = {.count = 1, .reusable = true}}, SHIFT(299),
  [1512] = {.entry = {.count = 1, .reusable = true}}, SHIFT(125),
  [1514] = {.entry = {.count = 1, .reusable = false}}, SHIFT(584),
  [1516] = {.entry = {.count = 1, .reusable = true}}, SHIFT(582),
  [1518] = {.entry = {.count = 1, .reusable = true}}, SHIFT(580),
  [1520] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [1522] = {.entry = {.count = 1, .reusable = true}}, SHIFT(713),
  [1524] = {.entry = {.count = 1, .reusable = true}}, SHIFT(304),
  [1526] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filename_spec, 7),
  [1528] = {.entry = {.count = 1, .reusable = true}}, SHIFT(289),
  [1530] = {.entry = {.count = 1, .reusable = true}}, SHIFT(518),
  [1532] = {.entry = {.count = 1, .reusable = true}}, SHIFT(470),
  [1534] = {.entry = {.count = 1, .reusable = true}}, SHIFT(453),
  [1536] = {.entry = {.count = 1, .reusable = true}}, SHIFT(200),
  [1538] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [1540] = {.entry = {.count = 1, .reusable = true}}, SHIFT(516),
  [1542] = {.entry = {.count = 1, .reusable = true}}, SHIFT(131),
  [1544] = {.entry = {.count = 1, .reusable = true}}, SHIFT(459),
  [1546] = {.entry = {.count = 1, .reusable = false}}, SHIFT(527),
  [1548] = {.entry = {.count = 1, .reusable = true}}, SHIFT(322),
  [1550] = {.entry = {.count = 1, .reusable = false}}, SHIFT(220),
  [1552] = {.entry = {.count = 1, .reusable = false}}, SHIFT(227),
  [1554] = {.entry = {.count = 1, .reusable = true}}, SHIFT(303),
  [1556] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [1558] = {.entry = {.count = 1, .reusable = true}}, SHIFT(388),
  [1560] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [1562] = {.entry = {.count = 1, .reusable = true}}, SHIFT(103),
  [1564] = {.entry = {.count = 1, .reusable = false}}, SHIFT(522),
  [1566] = {.entry = {.count = 1, .reusable = true}}, SHIFT(296),
  [1568] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [1570] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sect_constraint, 1),
  [1572] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [1574] = {.entry = {.count = 1, .reusable = true}}, SHIFT(375),
  [1576] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [1578] = {.entry = {.count = 1, .reusable = true}}, SHIFT(306),
  [1580] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [1582] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [1584] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [1586] = {.entry = {.count = 1, .reusable = true}}, SHIFT(484),
  [1588] = {.entry = {.count = 1, .reusable = true}}, SHIFT(239),
  [1590] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [1592] = {.entry = {.count = 1, .reusable = false}}, SHIFT(436),
  [1594] = {.entry = {.count = 1, .reusable = true}}, SHIFT(627),
  [1596] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [1598] = {.entry = {.count = 1, .reusable = true}}, SHIFT(120),
  [1600] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [1602] = {.entry = {.count = 1, .reusable = true}}, SHIFT(313),
  [1604] = {.entry = {.count = 1, .reusable = true}}, SHIFT(346),
  [1606] = {.entry = {.count = 1, .reusable = true}}, SHIFT(300),
  [1608] = {.entry = {.count = 1, .reusable = true}}, SHIFT(673),
  [1610] = {.entry = {.count = 1, .reusable = true}}, SHIFT(368),
  [1612] = {.entry = {.count = 1, .reusable = true}}, SHIFT(560),
  [1614] = {.entry = {.count = 1, .reusable = false}}, SHIFT(213),
  [1616] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [1618] = {.entry = {.count = 1, .reusable = false}}, SHIFT(228),
  [1620] = {.entry = {.count = 1, .reusable = true}}, SHIFT(404),
  [1622] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [1624] = {.entry = {.count = 1, .reusable = true}}, SHIFT(539),
  [1626] = {.entry = {.count = 1, .reusable = true}}, SHIFT(94),
  [1628] = {.entry = {.count = 1, .reusable = true}}, SHIFT(96),
  [1630] = {.entry = {.count = 1, .reusable = true}}, SHIFT(540),
  [1632] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [1634] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [1636] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [1638] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [1640] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [1642] = {.entry = {.count = 1, .reusable = true}}, SHIFT(347),
  [1644] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [1646] = {.entry = {.count = 1, .reusable = true}}, SHIFT(556),
  [1648] = {.entry = {.count = 1, .reusable = true}}, SHIFT(355),
  [1650] = {.entry = {.count = 1, .reusable = true}}, SHIFT(357),
  [1652] = {.entry = {.count = 1, .reusable = true}}, SHIFT(493),
  [1654] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [1656] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attributes, 3),
  [1658] = {.entry = {.count = 1, .reusable = true}}, SHIFT(398),
  [1660] = {.entry = {.count = 1, .reusable = true}}, SHIFT(340),
  [1662] = {.entry = {.count = 1, .reusable = true}}, SHIFT(262),
  [1664] = {.entry = {.count = 1, .reusable = true}}, SHIFT(578),
  [1666] = {.entry = {.count = 1, .reusable = true}}, SHIFT(142),
  [1668] = {.entry = {.count = 1, .reusable = true}}, SHIFT(411),
  [1670] = {.entry = {.count = 1, .reusable = true}}, SHIFT(268),
  [1672] = {.entry = {.count = 1, .reusable = false}}, SHIFT(620),
  [1674] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [1676] = {.entry = {.count = 1, .reusable = false}}, SHIFT(356),
  [1678] = {.entry = {.count = 1, .reusable = true}}, SHIFT(598),
  [1680] = {.entry = {.count = 1, .reusable = true}}, SHIFT(241),
  [1682] = {.entry = {.count = 1, .reusable = false}}, SHIFT(341),
  [1684] = {.entry = {.count = 1, .reusable = true}}, SHIFT(275),
  [1686] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filename_spec, 1),
  [1688] = {.entry = {.count = 1, .reusable = true}}, SHIFT(604),
  [1690] = {.entry = {.count = 1, .reusable = false}}, SHIFT(279),
  [1692] = {.entry = {.count = 1, .reusable = true}}, SHIFT(281),
  [1694] = {.entry = {.count = 1, .reusable = true}}, SHIFT(607),
  [1696] = {.entry = {.count = 1, .reusable = true}}, SHIFT(282),
  [1698] = {.entry = {.count = 1, .reusable = true}}, SHIFT(332),
  [1700] = {.entry = {.count = 1, .reusable = false}}, SHIFT(603),
  [1702] = {.entry = {.count = 1, .reusable = false}}, SHIFT(617),
  [1704] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [1706] = {.entry = {.count = 1, .reusable = false}}, SHIFT(622),
  [1708] = {.entry = {.count = 1, .reusable = false}}, SHIFT(22),
  [1710] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_length, 1),
  [1712] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [1714] = {.entry = {.count = 1, .reusable = true}}, SHIFT(291),
  [1716] = {.entry = {.count = 1, .reusable = false}}, SHIFT(290),
  [1718] = {.entry = {.count = 1, .reusable = false}}, SHIFT(630),
  [1720] = {.entry = {.count = 1, .reusable = false}}, SHIFT(134),
  [1722] = {.entry = {.count = 1, .reusable = false}}, SHIFT(634),
  [1724] = {.entry = {.count = 1, .reusable = false}}, SHIFT(471),
  [1726] = {.entry = {.count = 1, .reusable = true}}, SHIFT(636),
  [1728] = {.entry = {.count = 1, .reusable = true}}, SHIFT(215),
  [1730] = {.entry = {.count = 1, .reusable = false}}, SHIFT(638),
  [1732] = {.entry = {.count = 1, .reusable = false}}, SHIFT(633),
  [1734] = {.entry = {.count = 1, .reusable = true}}, SHIFT(615),
  [1736] = {.entry = {.count = 1, .reusable = true}}, SHIFT(643),
  [1738] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [1740] = {.entry = {.count = 1, .reusable = true}}, SHIFT(338),
  [1742] = {.entry = {.count = 1, .reusable = true}}, SHIFT(335),
  [1744] = {.entry = {.count = 1, .reusable = true}}, SHIFT(650),
  [1746] = {.entry = {.count = 1, .reusable = true}}, SHIFT(482),
  [1748] = {.entry = {.count = 1, .reusable = true}}, SHIFT(456),
  [1750] = {.entry = {.count = 1, .reusable = true}}, SHIFT(331),
  [1752] = {.entry = {.count = 1, .reusable = true}}, SHIFT(325),
  [1754] = {.entry = {.count = 1, .reusable = true}}, SHIFT(653),
  [1756] = {.entry = {.count = 1, .reusable = true}}, SHIFT(387),
  [1758] = {.entry = {.count = 1, .reusable = false}}, SHIFT(657),
  [1760] = {.entry = {.count = 1, .reusable = true}}, SHIFT(481),
  [1762] = {.entry = {.count = 1, .reusable = true}}, SHIFT(659),
  [1764] = {.entry = {.count = 1, .reusable = true}}, SHIFT(336),
  [1766] = {.entry = {.count = 1, .reusable = true}}, SHIFT(655),
  [1768] = {.entry = {.count = 1, .reusable = true}}, SHIFT(662),
  [1770] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [1772] = {.entry = {.count = 1, .reusable = true}}, SHIFT(665),
  [1774] = {.entry = {.count = 1, .reusable = true}}, SHIFT(666),
  [1776] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [1778] = {.entry = {.count = 1, .reusable = true}}, SHIFT(670),
  [1780] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [1782] = {.entry = {.count = 1, .reusable = true}}, SHIFT(656),
  [1784] = {.entry = {.count = 1, .reusable = true}}, SHIFT(201),
  [1786] = {.entry = {.count = 1, .reusable = true}}, SHIFT(658),
  [1788] = {.entry = {.count = 1, .reusable = true}}, SHIFT(237),
  [1790] = {.entry = {.count = 1, .reusable = true}}, SHIFT(352),
  [1792] = {.entry = {.count = 1, .reusable = true}}, SHIFT(305),
  [1794] = {.entry = {.count = 1, .reusable = true}}, SHIFT(354),
  [1796] = {.entry = {.count = 1, .reusable = true}}, SHIFT(314),
  [1798] = {.entry = {.count = 1, .reusable = true}}, SHIFT(240),
  [1800] = {.entry = {.count = 1, .reusable = true}}, SHIFT(312),
  [1802] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [1804] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [1806] = {.entry = {.count = 1, .reusable = true}}, SHIFT(688),
  [1808] = {.entry = {.count = 1, .reusable = true}}, SHIFT(88),
  [1810] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_atype, 3),
  [1812] = {.entry = {.count = 1, .reusable = true}}, SHIFT(468),
  [1814] = {.entry = {.count = 1, .reusable = true}}, SHIFT(447),
  [1816] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [1818] = {.entry = {.count = 1, .reusable = true}}, SHIFT(384),
  [1820] = {.entry = {.count = 1, .reusable = true}}, SHIFT(701),
  [1822] = {.entry = {.count = 1, .reusable = true}}, SHIFT(439),
  [1824] = {.entry = {.count = 1, .reusable = true}}, SHIFT(360),
  [1826] = {.entry = {.count = 1, .reusable = true}}, SHIFT(431),
  [1828] = {.entry = {.count = 1, .reusable = true}}, SHIFT(669),
  [1830] = {.entry = {.count = 1, .reusable = true}}, SHIFT(477),
  [1832] = {.entry = {.count = 1, .reusable = true}}, SHIFT(715),
  [1834] = {.entry = {.count = 1, .reusable = true}}, SHIFT(422),
  [1836] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [1838] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [1840] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [1842] = {.entry = {.count = 1, .reusable = true}}, SHIFT(720),
  [1844] = {.entry = {.count = 1, .reusable = true}}, SHIFT(73),
  [1846] = {.entry = {.count = 1, .reusable = true}}, SHIFT(82),
  [1848] = {.entry = {.count = 1, .reusable = true}}, SHIFT(726),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_ld(void) {
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
    .keyword_lex_fn = ts_lex_keywords,
    .keyword_capture_token = sym_NAME,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
