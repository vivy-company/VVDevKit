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
#define STATE_COUNT 596
#define LARGE_STATE_COUNT 25
#define SYMBOL_COUNT 248
#define ALIAS_COUNT 0
#define TOKEN_COUNT 182
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 1
#define MAX_ALIAS_SEQUENCE_LENGTH 15
#define PRODUCTION_ID_COUNT 6

enum ts_symbol_identifiers {
  aux_sym_body_token1 = 1,
  anon_sym_LPAREN = 2,
  anon_sym_COMMA = 3,
  anon_sym_RPAREN = 4,
  anon_sym_COLON = 5,
  sym__newline = 6,
  sym_comment = 7,
  sym_multiline_comment = 8,
  sym_identifier = 9,
  sym_mnemonic = 10,
  sym_bb_ref = 11,
  sym_stack_object = 12,
  sym_constant_pool_index = 13,
  sym_jump_table_index = 14,
  sym_string = 15,
  sym_number = 16,
  aux_sym_float_token1 = 17,
  aux_sym_float_token2 = 18,
  sym_var = 19,
  sym_physical_register = 20,
  sym_immediate_type = 21,
  sym_ir_block = 22,
  sym_external_symbol = 23,
  sym_global_var = 24,
  sym_ir_local_var = 25,
  sym_metadata_ref = 26,
  anon_sym_LBRACE = 27,
  anon_sym_RBRACE = 28,
  anon_sym_successors = 29,
  anon_sym_liveins = 30,
  anon_sym_EQ = 31,
  anon_sym_dbg_DASHinstr_DASHref = 32,
  anon_sym_pre_DASHinstr_DASHsymbol = 33,
  anon_sym_post_DASHinstr_DASHsymbol = 34,
  anon_sym_heap_DASHalloc_DASHmarker = 35,
  anon_sym_pcsections = 36,
  anon_sym_mmra = 37,
  anon_sym_cfi_DASHtype = 38,
  anon_sym_debug_DASHinstr_DASHnumber = 39,
  anon_sym_debug_DASHlocation = 40,
  anon_sym_COLON_COLON = 41,
  anon_sym_LT = 42,
  anon_sym_mcsymbol = 43,
  anon_sym_GT = 44,
  anon_sym_LPAREN2 = 45,
  anon_sym_BANG = 46,
  anon_sym_null = 47,
  aux_sym_md_value_token1 = 48,
  anon_sym_PIPE = 49,
  anon_sym_STAR = 50,
  anon_sym_LBRACK = 51,
  anon_sym_RBRACK = 52,
  anon_sym_DOT = 53,
  anon_sym__ = 54,
  anon_sym_tied_DASHdef = 55,
  anon_sym_target_DASHflags = 56,
  sym_primitive_type = 57,
  anon_sym_vscale = 58,
  anon_sym_x = 59,
  anon_sym_CustomRegMask = 60,
  anon_sym_same_value = 61,
  anon_sym_def_cfa_register = 62,
  anon_sym_restore = 63,
  anon_sym_undefined = 64,
  anon_sym_offset = 65,
  anon_sym_rel_offset = 66,
  anon_sym_def_cfa = 67,
  anon_sym_def_cfa_offset = 68,
  anon_sym_adjust_cfa_offset = 69,
  anon_sym_llvm_def_aspace_cfa = 70,
  anon_sym_register = 71,
  anon_sym_escape = 72,
  anon_sym_remember_state = 73,
  anon_sym_restore_state = 74,
  anon_sym_window_save = 75,
  anon_sym_negate_ra_sign_state = 76,
  anon_sym_true = 77,
  anon_sym_false = 78,
  anon_sym_intpred = 79,
  anon_sym_floatpred = 80,
  anon_sym_eq = 81,
  anon_sym_ne = 82,
  anon_sym_sgt = 83,
  anon_sym_sge = 84,
  anon_sym_slt = 85,
  anon_sym_sle = 86,
  anon_sym_ugt = 87,
  anon_sym_uge = 88,
  anon_sym_ult = 89,
  anon_sym_ule = 90,
  anon_sym_oeq = 91,
  anon_sym_ogt = 92,
  anon_sym_oge = 93,
  anon_sym_olt = 94,
  anon_sym_ole = 95,
  anon_sym_one = 96,
  anon_sym_ord = 97,
  anon_sym_uno = 98,
  anon_sym_ueq = 99,
  anon_sym_une = 100,
  anon_sym_shufflemask = 101,
  anon_sym_undef = 102,
  anon_sym_liveout = 103,
  anon_sym_target_DASHindex = 104,
  anon_sym_blockaddress = 105,
  anon_sym_intrinsic = 106,
  anon_sym_load = 107,
  anon_sym_store = 108,
  anon_sym_unknown_DASHsize = 109,
  anon_sym_on = 110,
  anon_sym_from = 111,
  anon_sym_into = 112,
  anon_sym_align = 113,
  anon_sym_basealign = 114,
  anon_sym_addrspace = 115,
  anon_sym_unknown_DASHaddress = 116,
  anon_sym_BQUOTE = 117,
  anon_sym_PLUS = 118,
  anon_sym_DASH = 119,
  anon_sym_call_DASHentry = 120,
  anon_sym_custom = 121,
  anon_sym_constant_DASHpool = 122,
  anon_sym_stack = 123,
  anon_sym_got = 124,
  anon_sym_jump_DASHtable = 125,
  anon_sym_volatile = 126,
  anon_sym_non_DASHtemporal = 127,
  anon_sym_dereferenceable = 128,
  anon_sym_invariant = 129,
  anon_sym_syncscope = 130,
  anon_sym_unordered = 131,
  anon_sym_monotonic = 132,
  anon_sym_acquire = 133,
  anon_sym_release = 134,
  anon_sym_acq_rel = 135,
  anon_sym_seq_cst = 136,
  anon_sym_implicit = 137,
  anon_sym_implicit_DASHdef = 138,
  anon_sym_def = 139,
  anon_sym_dead = 140,
  anon_sym_killed = 141,
  anon_sym_internal = 142,
  anon_sym_early_DASHclobber = 143,
  anon_sym_debug_DASHuse = 144,
  anon_sym_renamable = 145,
  anon_sym_frame_DASHsetup = 146,
  anon_sym_frame_DASHdestroy = 147,
  anon_sym_nnan = 148,
  anon_sym_ninf = 149,
  anon_sym_nsz = 150,
  anon_sym_arcp = 151,
  anon_sym_contract = 152,
  anon_sym_afn = 153,
  anon_sym_reassoc = 154,
  anon_sym_nuw = 155,
  anon_sym_nsw = 156,
  anon_sym_exact = 157,
  anon_sym_nofpexcept = 158,
  anon_sym_nomerge = 159,
  anon_sym_unpredictable = 160,
  anon_sym_noconvergent = 161,
  anon_sym_nneg = 162,
  anon_sym_disjoint = 163,
  anon_sym_nusw = 164,
  anon_sym_machine_DASHblock_DASHaddress_DASHtaken = 165,
  anon_sym_landing_DASHpad = 166,
  anon_sym_inlineasm_DASHbr_DASHindirect_DASHtarget = 167,
  anon_sym_ehfunclet_DASHentry = 168,
  anon_sym_ir_DASHblock_DASHaddress_DASHtaken = 169,
  anon_sym_call_DASHframe_DASHsize = 170,
  anon_sym_bb_id = 171,
  anon_sym_bbsections = 172,
  anon_sym_Exception = 173,
  anon_sym_Cold = 174,
  anon_sym_half = 175,
  anon_sym_bfloat = 176,
  anon_sym_float = 177,
  anon_sym_double = 178,
  anon_sym_x86_fp80 = 179,
  anon_sym_fp128 = 180,
  anon_sym_ppc_fp128 = 181,
  sym_body = 182,
  sym_basic_block = 183,
  sym_label = 184,
  sym_float = 185,
  sym_register = 186,
  sym_bundle = 187,
  sym_successors = 188,
  sym_liveins = 189,
  sym_instruction = 190,
  sym_mc_symbol = 191,
  sym_metadata = 192,
  sym_md_value = 193,
  sym_register_operand = 194,
  sym_argument = 195,
  sym_machine_operand = 196,
  sym_subregister = 197,
  sym_registerclass = 198,
  sym_low_level_type = 199,
  sym_custom_regmask = 200,
  sym_cfi_operand = 201,
  sym_immediate = 202,
  sym_predicate = 203,
  sym_intpred = 204,
  sym_floatpred = 205,
  sym_shuffle_mask = 206,
  sym_liveout = 207,
  sym_target_index = 208,
  sym_block_address = 209,
  sym_intrinsic = 210,
  sym_memory_operand = 211,
  sym_mem_attribute = 212,
  sym_machine_pointer_info = 213,
  sym_ir_value = 214,
  sym_escaped_ir_value = 215,
  sym__escaped_ir_content = 216,
  sym_offset = 217,
  sym_memory_pseudo_source_value = 218,
  sym_memory_pseudo_source_value_keyword = 219,
  sym_memory_operand_flag = 220,
  sym_sync_scope = 221,
  sym_atomic_ordering = 222,
  sym_register_flag = 223,
  sym_instruction_flag = 224,
  sym_attribute = 225,
  sym_float_keyword = 226,
  aux_sym_body_repeat1 = 227,
  aux_sym_basic_block_repeat1 = 228,
  aux_sym_basic_block_repeat2 = 229,
  aux_sym_basic_block_repeat3 = 230,
  aux_sym_bundle_repeat1 = 231,
  aux_sym_successors_repeat1 = 232,
  aux_sym_liveins_repeat1 = 233,
  aux_sym_instruction_repeat1 = 234,
  aux_sym_instruction_repeat2 = 235,
  aux_sym_instruction_repeat3 = 236,
  aux_sym_instruction_repeat4 = 237,
  aux_sym_instruction_repeat5 = 238,
  aux_sym_metadata_repeat1 = 239,
  aux_sym_register_operand_repeat1 = 240,
  aux_sym_argument_repeat1 = 241,
  aux_sym_custom_regmask_repeat1 = 242,
  aux_sym_cfi_operand_repeat1 = 243,
  aux_sym_shuffle_mask_repeat1 = 244,
  aux_sym_memory_operand_repeat1 = 245,
  aux_sym_memory_operand_repeat2 = 246,
  aux_sym_escaped_ir_value_repeat1 = 247,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [aux_sym_body_token1] = "body_token1",
  [anon_sym_LPAREN] = "(",
  [anon_sym_COMMA] = ",",
  [anon_sym_RPAREN] = ")",
  [anon_sym_COLON] = ":",
  [sym__newline] = "_newline",
  [sym_comment] = "comment",
  [sym_multiline_comment] = "multiline_comment",
  [sym_identifier] = "identifier",
  [sym_mnemonic] = "mnemonic",
  [sym_bb_ref] = "bb_ref",
  [sym_stack_object] = "stack_object",
  [sym_constant_pool_index] = "constant_pool_index",
  [sym_jump_table_index] = "jump_table_index",
  [sym_string] = "string",
  [sym_number] = "number",
  [aux_sym_float_token1] = "float_token1",
  [aux_sym_float_token2] = "float_token2",
  [sym_var] = "var",
  [sym_physical_register] = "physical_register",
  [sym_immediate_type] = "immediate_type",
  [sym_ir_block] = "ir_block",
  [sym_external_symbol] = "external_symbol",
  [sym_global_var] = "global_var",
  [sym_ir_local_var] = "ir_local_var",
  [sym_metadata_ref] = "metadata_ref",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_successors] = "successors",
  [anon_sym_liveins] = "liveins",
  [anon_sym_EQ] = "=",
  [anon_sym_dbg_DASHinstr_DASHref] = "dbg-instr-ref",
  [anon_sym_pre_DASHinstr_DASHsymbol] = "pre-instr-symbol",
  [anon_sym_post_DASHinstr_DASHsymbol] = "post-instr-symbol",
  [anon_sym_heap_DASHalloc_DASHmarker] = "heap-alloc-marker",
  [anon_sym_pcsections] = "pcsections",
  [anon_sym_mmra] = "mmra",
  [anon_sym_cfi_DASHtype] = "cfi-type",
  [anon_sym_debug_DASHinstr_DASHnumber] = "debug-instr-number",
  [anon_sym_debug_DASHlocation] = "debug-location",
  [anon_sym_COLON_COLON] = "::",
  [anon_sym_LT] = "<",
  [anon_sym_mcsymbol] = "mcsymbol",
  [anon_sym_GT] = ">",
  [anon_sym_LPAREN2] = "(",
  [anon_sym_BANG] = "!",
  [anon_sym_null] = "null",
  [aux_sym_md_value_token1] = "md_value_token1",
  [anon_sym_PIPE] = "|",
  [anon_sym_STAR] = "*",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [anon_sym_DOT] = ".",
  [anon_sym__] = "_",
  [anon_sym_tied_DASHdef] = "tied-def",
  [anon_sym_target_DASHflags] = "target-flags",
  [sym_primitive_type] = "primitive_type",
  [anon_sym_vscale] = "vscale",
  [anon_sym_x] = "x",
  [anon_sym_CustomRegMask] = "CustomRegMask",
  [anon_sym_same_value] = "same_value",
  [anon_sym_def_cfa_register] = "def_cfa_register",
  [anon_sym_restore] = "restore",
  [anon_sym_undefined] = "undefined",
  [anon_sym_offset] = "offset",
  [anon_sym_rel_offset] = "rel_offset",
  [anon_sym_def_cfa] = "def_cfa",
  [anon_sym_def_cfa_offset] = "def_cfa_offset",
  [anon_sym_adjust_cfa_offset] = "adjust_cfa_offset",
  [anon_sym_llvm_def_aspace_cfa] = "llvm_def_aspace_cfa",
  [anon_sym_register] = "register",
  [anon_sym_escape] = "escape",
  [anon_sym_remember_state] = "remember_state",
  [anon_sym_restore_state] = "restore_state",
  [anon_sym_window_save] = "window_save",
  [anon_sym_negate_ra_sign_state] = "negate_ra_sign_state",
  [anon_sym_true] = "true",
  [anon_sym_false] = "false",
  [anon_sym_intpred] = "intpred",
  [anon_sym_floatpred] = "floatpred",
  [anon_sym_eq] = "eq",
  [anon_sym_ne] = "ne",
  [anon_sym_sgt] = "sgt",
  [anon_sym_sge] = "sge",
  [anon_sym_slt] = "slt",
  [anon_sym_sle] = "sle",
  [anon_sym_ugt] = "ugt",
  [anon_sym_uge] = "uge",
  [anon_sym_ult] = "ult",
  [anon_sym_ule] = "ule",
  [anon_sym_oeq] = "oeq",
  [anon_sym_ogt] = "ogt",
  [anon_sym_oge] = "oge",
  [anon_sym_olt] = "olt",
  [anon_sym_ole] = "ole",
  [anon_sym_one] = "one",
  [anon_sym_ord] = "ord",
  [anon_sym_uno] = "uno",
  [anon_sym_ueq] = "ueq",
  [anon_sym_une] = "une",
  [anon_sym_shufflemask] = "shufflemask",
  [anon_sym_undef] = "undef",
  [anon_sym_liveout] = "liveout",
  [anon_sym_target_DASHindex] = "target-index",
  [anon_sym_blockaddress] = "blockaddress",
  [anon_sym_intrinsic] = "intrinsic",
  [anon_sym_load] = "load",
  [anon_sym_store] = "store",
  [anon_sym_unknown_DASHsize] = "unknown-size",
  [anon_sym_on] = "on",
  [anon_sym_from] = "from",
  [anon_sym_into] = "into",
  [anon_sym_align] = "align",
  [anon_sym_basealign] = "basealign",
  [anon_sym_addrspace] = "addrspace",
  [anon_sym_unknown_DASHaddress] = "unknown-address",
  [anon_sym_BQUOTE] = "`",
  [anon_sym_PLUS] = "+",
  [anon_sym_DASH] = "-",
  [anon_sym_call_DASHentry] = "call-entry",
  [anon_sym_custom] = "custom",
  [anon_sym_constant_DASHpool] = "constant-pool",
  [anon_sym_stack] = "stack",
  [anon_sym_got] = "got",
  [anon_sym_jump_DASHtable] = "jump-table",
  [anon_sym_volatile] = "volatile",
  [anon_sym_non_DASHtemporal] = "non-temporal",
  [anon_sym_dereferenceable] = "dereferenceable",
  [anon_sym_invariant] = "invariant",
  [anon_sym_syncscope] = "syncscope",
  [anon_sym_unordered] = "unordered",
  [anon_sym_monotonic] = "monotonic",
  [anon_sym_acquire] = "acquire",
  [anon_sym_release] = "release",
  [anon_sym_acq_rel] = "acq_rel",
  [anon_sym_seq_cst] = "seq_cst",
  [anon_sym_implicit] = "implicit",
  [anon_sym_implicit_DASHdef] = "implicit-def",
  [anon_sym_def] = "def",
  [anon_sym_dead] = "dead",
  [anon_sym_killed] = "killed",
  [anon_sym_internal] = "internal",
  [anon_sym_early_DASHclobber] = "early-clobber",
  [anon_sym_debug_DASHuse] = "debug-use",
  [anon_sym_renamable] = "renamable",
  [anon_sym_frame_DASHsetup] = "frame-setup",
  [anon_sym_frame_DASHdestroy] = "frame-destroy",
  [anon_sym_nnan] = "nnan",
  [anon_sym_ninf] = "ninf",
  [anon_sym_nsz] = "nsz",
  [anon_sym_arcp] = "arcp",
  [anon_sym_contract] = "contract",
  [anon_sym_afn] = "afn",
  [anon_sym_reassoc] = "reassoc",
  [anon_sym_nuw] = "nuw",
  [anon_sym_nsw] = "nsw",
  [anon_sym_exact] = "exact",
  [anon_sym_nofpexcept] = "nofpexcept",
  [anon_sym_nomerge] = "nomerge",
  [anon_sym_unpredictable] = "unpredictable",
  [anon_sym_noconvergent] = "noconvergent",
  [anon_sym_nneg] = "nneg",
  [anon_sym_disjoint] = "disjoint",
  [anon_sym_nusw] = "nusw",
  [anon_sym_machine_DASHblock_DASHaddress_DASHtaken] = "machine-block-address-taken",
  [anon_sym_landing_DASHpad] = "landing-pad",
  [anon_sym_inlineasm_DASHbr_DASHindirect_DASHtarget] = "inlineasm-br-indirect-target",
  [anon_sym_ehfunclet_DASHentry] = "ehfunclet-entry",
  [anon_sym_ir_DASHblock_DASHaddress_DASHtaken] = "ir-block-address-taken",
  [anon_sym_call_DASHframe_DASHsize] = "call-frame-size",
  [anon_sym_bb_id] = "bb_id",
  [anon_sym_bbsections] = "bbsections",
  [anon_sym_Exception] = "Exception",
  [anon_sym_Cold] = "Cold",
  [anon_sym_half] = "half",
  [anon_sym_bfloat] = "bfloat",
  [anon_sym_float] = "float",
  [anon_sym_double] = "double",
  [anon_sym_x86_fp80] = "x86_fp80",
  [anon_sym_fp128] = "fp128",
  [anon_sym_ppc_fp128] = "ppc_fp128",
  [sym_body] = "body",
  [sym_basic_block] = "basic_block",
  [sym_label] = "label",
  [sym_float] = "float",
  [sym_register] = "register",
  [sym_bundle] = "bundle",
  [sym_successors] = "successors",
  [sym_liveins] = "liveins",
  [sym_instruction] = "instruction",
  [sym_mc_symbol] = "mc_symbol",
  [sym_metadata] = "metadata",
  [sym_md_value] = "md_value",
  [sym_register_operand] = "register_operand",
  [sym_argument] = "argument",
  [sym_machine_operand] = "machine_operand",
  [sym_subregister] = "subregister",
  [sym_registerclass] = "registerclass",
  [sym_low_level_type] = "low_level_type",
  [sym_custom_regmask] = "custom_regmask",
  [sym_cfi_operand] = "cfi_operand",
  [sym_immediate] = "immediate",
  [sym_predicate] = "predicate",
  [sym_intpred] = "intpred",
  [sym_floatpred] = "floatpred",
  [sym_shuffle_mask] = "shuffle_mask",
  [sym_liveout] = "liveout",
  [sym_target_index] = "target_index",
  [sym_block_address] = "block_address",
  [sym_intrinsic] = "intrinsic",
  [sym_memory_operand] = "memory_operand",
  [sym_mem_attribute] = "mem_attribute",
  [sym_machine_pointer_info] = "machine_pointer_info",
  [sym_ir_value] = "ir_value",
  [sym_escaped_ir_value] = "escaped_ir_value",
  [sym__escaped_ir_content] = "_escaped_ir_content",
  [sym_offset] = "offset",
  [sym_memory_pseudo_source_value] = "memory_pseudo_source_value",
  [sym_memory_pseudo_source_value_keyword] = "memory_pseudo_source_value_keyword",
  [sym_memory_operand_flag] = "memory_operand_flag",
  [sym_sync_scope] = "sync_scope",
  [sym_atomic_ordering] = "atomic_ordering",
  [sym_register_flag] = "register_flag",
  [sym_instruction_flag] = "instruction_flag",
  [sym_attribute] = "attribute",
  [sym_float_keyword] = "float_keyword",
  [aux_sym_body_repeat1] = "body_repeat1",
  [aux_sym_basic_block_repeat1] = "basic_block_repeat1",
  [aux_sym_basic_block_repeat2] = "basic_block_repeat2",
  [aux_sym_basic_block_repeat3] = "basic_block_repeat3",
  [aux_sym_bundle_repeat1] = "bundle_repeat1",
  [aux_sym_successors_repeat1] = "successors_repeat1",
  [aux_sym_liveins_repeat1] = "liveins_repeat1",
  [aux_sym_instruction_repeat1] = "instruction_repeat1",
  [aux_sym_instruction_repeat2] = "instruction_repeat2",
  [aux_sym_instruction_repeat3] = "instruction_repeat3",
  [aux_sym_instruction_repeat4] = "instruction_repeat4",
  [aux_sym_instruction_repeat5] = "instruction_repeat5",
  [aux_sym_metadata_repeat1] = "metadata_repeat1",
  [aux_sym_register_operand_repeat1] = "register_operand_repeat1",
  [aux_sym_argument_repeat1] = "argument_repeat1",
  [aux_sym_custom_regmask_repeat1] = "custom_regmask_repeat1",
  [aux_sym_cfi_operand_repeat1] = "cfi_operand_repeat1",
  [aux_sym_shuffle_mask_repeat1] = "shuffle_mask_repeat1",
  [aux_sym_memory_operand_repeat1] = "memory_operand_repeat1",
  [aux_sym_memory_operand_repeat2] = "memory_operand_repeat2",
  [aux_sym_escaped_ir_value_repeat1] = "escaped_ir_value_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [aux_sym_body_token1] = aux_sym_body_token1,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_COLON] = anon_sym_COLON,
  [sym__newline] = sym__newline,
  [sym_comment] = sym_comment,
  [sym_multiline_comment] = sym_multiline_comment,
  [sym_identifier] = sym_identifier,
  [sym_mnemonic] = sym_mnemonic,
  [sym_bb_ref] = sym_bb_ref,
  [sym_stack_object] = sym_stack_object,
  [sym_constant_pool_index] = sym_constant_pool_index,
  [sym_jump_table_index] = sym_jump_table_index,
  [sym_string] = sym_string,
  [sym_number] = sym_number,
  [aux_sym_float_token1] = aux_sym_float_token1,
  [aux_sym_float_token2] = aux_sym_float_token2,
  [sym_var] = sym_var,
  [sym_physical_register] = sym_physical_register,
  [sym_immediate_type] = sym_immediate_type,
  [sym_ir_block] = sym_ir_block,
  [sym_external_symbol] = sym_external_symbol,
  [sym_global_var] = sym_global_var,
  [sym_ir_local_var] = sym_ir_local_var,
  [sym_metadata_ref] = sym_metadata_ref,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_successors] = anon_sym_successors,
  [anon_sym_liveins] = anon_sym_liveins,
  [anon_sym_EQ] = anon_sym_EQ,
  [anon_sym_dbg_DASHinstr_DASHref] = anon_sym_dbg_DASHinstr_DASHref,
  [anon_sym_pre_DASHinstr_DASHsymbol] = anon_sym_pre_DASHinstr_DASHsymbol,
  [anon_sym_post_DASHinstr_DASHsymbol] = anon_sym_post_DASHinstr_DASHsymbol,
  [anon_sym_heap_DASHalloc_DASHmarker] = anon_sym_heap_DASHalloc_DASHmarker,
  [anon_sym_pcsections] = anon_sym_pcsections,
  [anon_sym_mmra] = anon_sym_mmra,
  [anon_sym_cfi_DASHtype] = anon_sym_cfi_DASHtype,
  [anon_sym_debug_DASHinstr_DASHnumber] = anon_sym_debug_DASHinstr_DASHnumber,
  [anon_sym_debug_DASHlocation] = anon_sym_debug_DASHlocation,
  [anon_sym_COLON_COLON] = anon_sym_COLON_COLON,
  [anon_sym_LT] = anon_sym_LT,
  [anon_sym_mcsymbol] = anon_sym_mcsymbol,
  [anon_sym_GT] = anon_sym_GT,
  [anon_sym_LPAREN2] = anon_sym_LPAREN,
  [anon_sym_BANG] = anon_sym_BANG,
  [anon_sym_null] = anon_sym_null,
  [aux_sym_md_value_token1] = aux_sym_md_value_token1,
  [anon_sym_PIPE] = anon_sym_PIPE,
  [anon_sym_STAR] = anon_sym_STAR,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [anon_sym_DOT] = anon_sym_DOT,
  [anon_sym__] = anon_sym__,
  [anon_sym_tied_DASHdef] = anon_sym_tied_DASHdef,
  [anon_sym_target_DASHflags] = anon_sym_target_DASHflags,
  [sym_primitive_type] = sym_primitive_type,
  [anon_sym_vscale] = anon_sym_vscale,
  [anon_sym_x] = anon_sym_x,
  [anon_sym_CustomRegMask] = anon_sym_CustomRegMask,
  [anon_sym_same_value] = anon_sym_same_value,
  [anon_sym_def_cfa_register] = anon_sym_def_cfa_register,
  [anon_sym_restore] = anon_sym_restore,
  [anon_sym_undefined] = anon_sym_undefined,
  [anon_sym_offset] = anon_sym_offset,
  [anon_sym_rel_offset] = anon_sym_rel_offset,
  [anon_sym_def_cfa] = anon_sym_def_cfa,
  [anon_sym_def_cfa_offset] = anon_sym_def_cfa_offset,
  [anon_sym_adjust_cfa_offset] = anon_sym_adjust_cfa_offset,
  [anon_sym_llvm_def_aspace_cfa] = anon_sym_llvm_def_aspace_cfa,
  [anon_sym_register] = anon_sym_register,
  [anon_sym_escape] = anon_sym_escape,
  [anon_sym_remember_state] = anon_sym_remember_state,
  [anon_sym_restore_state] = anon_sym_restore_state,
  [anon_sym_window_save] = anon_sym_window_save,
  [anon_sym_negate_ra_sign_state] = anon_sym_negate_ra_sign_state,
  [anon_sym_true] = anon_sym_true,
  [anon_sym_false] = anon_sym_false,
  [anon_sym_intpred] = anon_sym_intpred,
  [anon_sym_floatpred] = anon_sym_floatpred,
  [anon_sym_eq] = anon_sym_eq,
  [anon_sym_ne] = anon_sym_ne,
  [anon_sym_sgt] = anon_sym_sgt,
  [anon_sym_sge] = anon_sym_sge,
  [anon_sym_slt] = anon_sym_slt,
  [anon_sym_sle] = anon_sym_sle,
  [anon_sym_ugt] = anon_sym_ugt,
  [anon_sym_uge] = anon_sym_uge,
  [anon_sym_ult] = anon_sym_ult,
  [anon_sym_ule] = anon_sym_ule,
  [anon_sym_oeq] = anon_sym_oeq,
  [anon_sym_ogt] = anon_sym_ogt,
  [anon_sym_oge] = anon_sym_oge,
  [anon_sym_olt] = anon_sym_olt,
  [anon_sym_ole] = anon_sym_ole,
  [anon_sym_one] = anon_sym_one,
  [anon_sym_ord] = anon_sym_ord,
  [anon_sym_uno] = anon_sym_uno,
  [anon_sym_ueq] = anon_sym_ueq,
  [anon_sym_une] = anon_sym_une,
  [anon_sym_shufflemask] = anon_sym_shufflemask,
  [anon_sym_undef] = anon_sym_undef,
  [anon_sym_liveout] = anon_sym_liveout,
  [anon_sym_target_DASHindex] = anon_sym_target_DASHindex,
  [anon_sym_blockaddress] = anon_sym_blockaddress,
  [anon_sym_intrinsic] = anon_sym_intrinsic,
  [anon_sym_load] = anon_sym_load,
  [anon_sym_store] = anon_sym_store,
  [anon_sym_unknown_DASHsize] = anon_sym_unknown_DASHsize,
  [anon_sym_on] = anon_sym_on,
  [anon_sym_from] = anon_sym_from,
  [anon_sym_into] = anon_sym_into,
  [anon_sym_align] = anon_sym_align,
  [anon_sym_basealign] = anon_sym_basealign,
  [anon_sym_addrspace] = anon_sym_addrspace,
  [anon_sym_unknown_DASHaddress] = anon_sym_unknown_DASHaddress,
  [anon_sym_BQUOTE] = anon_sym_BQUOTE,
  [anon_sym_PLUS] = anon_sym_PLUS,
  [anon_sym_DASH] = anon_sym_DASH,
  [anon_sym_call_DASHentry] = anon_sym_call_DASHentry,
  [anon_sym_custom] = anon_sym_custom,
  [anon_sym_constant_DASHpool] = anon_sym_constant_DASHpool,
  [anon_sym_stack] = anon_sym_stack,
  [anon_sym_got] = anon_sym_got,
  [anon_sym_jump_DASHtable] = anon_sym_jump_DASHtable,
  [anon_sym_volatile] = anon_sym_volatile,
  [anon_sym_non_DASHtemporal] = anon_sym_non_DASHtemporal,
  [anon_sym_dereferenceable] = anon_sym_dereferenceable,
  [anon_sym_invariant] = anon_sym_invariant,
  [anon_sym_syncscope] = anon_sym_syncscope,
  [anon_sym_unordered] = anon_sym_unordered,
  [anon_sym_monotonic] = anon_sym_monotonic,
  [anon_sym_acquire] = anon_sym_acquire,
  [anon_sym_release] = anon_sym_release,
  [anon_sym_acq_rel] = anon_sym_acq_rel,
  [anon_sym_seq_cst] = anon_sym_seq_cst,
  [anon_sym_implicit] = anon_sym_implicit,
  [anon_sym_implicit_DASHdef] = anon_sym_implicit_DASHdef,
  [anon_sym_def] = anon_sym_def,
  [anon_sym_dead] = anon_sym_dead,
  [anon_sym_killed] = anon_sym_killed,
  [anon_sym_internal] = anon_sym_internal,
  [anon_sym_early_DASHclobber] = anon_sym_early_DASHclobber,
  [anon_sym_debug_DASHuse] = anon_sym_debug_DASHuse,
  [anon_sym_renamable] = anon_sym_renamable,
  [anon_sym_frame_DASHsetup] = anon_sym_frame_DASHsetup,
  [anon_sym_frame_DASHdestroy] = anon_sym_frame_DASHdestroy,
  [anon_sym_nnan] = anon_sym_nnan,
  [anon_sym_ninf] = anon_sym_ninf,
  [anon_sym_nsz] = anon_sym_nsz,
  [anon_sym_arcp] = anon_sym_arcp,
  [anon_sym_contract] = anon_sym_contract,
  [anon_sym_afn] = anon_sym_afn,
  [anon_sym_reassoc] = anon_sym_reassoc,
  [anon_sym_nuw] = anon_sym_nuw,
  [anon_sym_nsw] = anon_sym_nsw,
  [anon_sym_exact] = anon_sym_exact,
  [anon_sym_nofpexcept] = anon_sym_nofpexcept,
  [anon_sym_nomerge] = anon_sym_nomerge,
  [anon_sym_unpredictable] = anon_sym_unpredictable,
  [anon_sym_noconvergent] = anon_sym_noconvergent,
  [anon_sym_nneg] = anon_sym_nneg,
  [anon_sym_disjoint] = anon_sym_disjoint,
  [anon_sym_nusw] = anon_sym_nusw,
  [anon_sym_machine_DASHblock_DASHaddress_DASHtaken] = anon_sym_machine_DASHblock_DASHaddress_DASHtaken,
  [anon_sym_landing_DASHpad] = anon_sym_landing_DASHpad,
  [anon_sym_inlineasm_DASHbr_DASHindirect_DASHtarget] = anon_sym_inlineasm_DASHbr_DASHindirect_DASHtarget,
  [anon_sym_ehfunclet_DASHentry] = anon_sym_ehfunclet_DASHentry,
  [anon_sym_ir_DASHblock_DASHaddress_DASHtaken] = anon_sym_ir_DASHblock_DASHaddress_DASHtaken,
  [anon_sym_call_DASHframe_DASHsize] = anon_sym_call_DASHframe_DASHsize,
  [anon_sym_bb_id] = anon_sym_bb_id,
  [anon_sym_bbsections] = anon_sym_bbsections,
  [anon_sym_Exception] = anon_sym_Exception,
  [anon_sym_Cold] = anon_sym_Cold,
  [anon_sym_half] = anon_sym_half,
  [anon_sym_bfloat] = anon_sym_bfloat,
  [anon_sym_float] = anon_sym_float,
  [anon_sym_double] = anon_sym_double,
  [anon_sym_x86_fp80] = anon_sym_x86_fp80,
  [anon_sym_fp128] = anon_sym_fp128,
  [anon_sym_ppc_fp128] = anon_sym_ppc_fp128,
  [sym_body] = sym_body,
  [sym_basic_block] = sym_basic_block,
  [sym_label] = sym_label,
  [sym_float] = sym_float,
  [sym_register] = sym_register,
  [sym_bundle] = sym_bundle,
  [sym_successors] = sym_successors,
  [sym_liveins] = sym_liveins,
  [sym_instruction] = sym_instruction,
  [sym_mc_symbol] = sym_mc_symbol,
  [sym_metadata] = sym_metadata,
  [sym_md_value] = sym_md_value,
  [sym_register_operand] = sym_register_operand,
  [sym_argument] = sym_argument,
  [sym_machine_operand] = sym_machine_operand,
  [sym_subregister] = sym_subregister,
  [sym_registerclass] = sym_registerclass,
  [sym_low_level_type] = sym_low_level_type,
  [sym_custom_regmask] = sym_custom_regmask,
  [sym_cfi_operand] = sym_cfi_operand,
  [sym_immediate] = sym_immediate,
  [sym_predicate] = sym_predicate,
  [sym_intpred] = sym_intpred,
  [sym_floatpred] = sym_floatpred,
  [sym_shuffle_mask] = sym_shuffle_mask,
  [sym_liveout] = sym_liveout,
  [sym_target_index] = sym_target_index,
  [sym_block_address] = sym_block_address,
  [sym_intrinsic] = sym_intrinsic,
  [sym_memory_operand] = sym_memory_operand,
  [sym_mem_attribute] = sym_mem_attribute,
  [sym_machine_pointer_info] = sym_machine_pointer_info,
  [sym_ir_value] = sym_ir_value,
  [sym_escaped_ir_value] = sym_escaped_ir_value,
  [sym__escaped_ir_content] = sym__escaped_ir_content,
  [sym_offset] = sym_offset,
  [sym_memory_pseudo_source_value] = sym_memory_pseudo_source_value,
  [sym_memory_pseudo_source_value_keyword] = sym_memory_pseudo_source_value_keyword,
  [sym_memory_operand_flag] = sym_memory_operand_flag,
  [sym_sync_scope] = sym_sync_scope,
  [sym_atomic_ordering] = sym_atomic_ordering,
  [sym_register_flag] = sym_register_flag,
  [sym_instruction_flag] = sym_instruction_flag,
  [sym_attribute] = sym_attribute,
  [sym_float_keyword] = sym_float_keyword,
  [aux_sym_body_repeat1] = aux_sym_body_repeat1,
  [aux_sym_basic_block_repeat1] = aux_sym_basic_block_repeat1,
  [aux_sym_basic_block_repeat2] = aux_sym_basic_block_repeat2,
  [aux_sym_basic_block_repeat3] = aux_sym_basic_block_repeat3,
  [aux_sym_bundle_repeat1] = aux_sym_bundle_repeat1,
  [aux_sym_successors_repeat1] = aux_sym_successors_repeat1,
  [aux_sym_liveins_repeat1] = aux_sym_liveins_repeat1,
  [aux_sym_instruction_repeat1] = aux_sym_instruction_repeat1,
  [aux_sym_instruction_repeat2] = aux_sym_instruction_repeat2,
  [aux_sym_instruction_repeat3] = aux_sym_instruction_repeat3,
  [aux_sym_instruction_repeat4] = aux_sym_instruction_repeat4,
  [aux_sym_instruction_repeat5] = aux_sym_instruction_repeat5,
  [aux_sym_metadata_repeat1] = aux_sym_metadata_repeat1,
  [aux_sym_register_operand_repeat1] = aux_sym_register_operand_repeat1,
  [aux_sym_argument_repeat1] = aux_sym_argument_repeat1,
  [aux_sym_custom_regmask_repeat1] = aux_sym_custom_regmask_repeat1,
  [aux_sym_cfi_operand_repeat1] = aux_sym_cfi_operand_repeat1,
  [aux_sym_shuffle_mask_repeat1] = aux_sym_shuffle_mask_repeat1,
  [aux_sym_memory_operand_repeat1] = aux_sym_memory_operand_repeat1,
  [aux_sym_memory_operand_repeat2] = aux_sym_memory_operand_repeat2,
  [aux_sym_escaped_ir_value_repeat1] = aux_sym_escaped_ir_value_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [aux_sym_body_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [sym__newline] = {
    .visible = false,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_multiline_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [sym_mnemonic] = {
    .visible = true,
    .named = true,
  },
  [sym_bb_ref] = {
    .visible = true,
    .named = true,
  },
  [sym_stack_object] = {
    .visible = true,
    .named = true,
  },
  [sym_constant_pool_index] = {
    .visible = true,
    .named = true,
  },
  [sym_jump_table_index] = {
    .visible = true,
    .named = true,
  },
  [sym_string] = {
    .visible = true,
    .named = true,
  },
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_float_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_float_token2] = {
    .visible = false,
    .named = false,
  },
  [sym_var] = {
    .visible = true,
    .named = true,
  },
  [sym_physical_register] = {
    .visible = true,
    .named = true,
  },
  [sym_immediate_type] = {
    .visible = true,
    .named = true,
  },
  [sym_ir_block] = {
    .visible = true,
    .named = true,
  },
  [sym_external_symbol] = {
    .visible = true,
    .named = true,
  },
  [sym_global_var] = {
    .visible = true,
    .named = true,
  },
  [sym_ir_local_var] = {
    .visible = true,
    .named = true,
  },
  [sym_metadata_ref] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_successors] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_liveins] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_dbg_DASHinstr_DASHref] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_pre_DASHinstr_DASHsymbol] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_post_DASHinstr_DASHsymbol] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_heap_DASHalloc_DASHmarker] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_pcsections] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_mmra] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_cfi_DASHtype] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_debug_DASHinstr_DASHnumber] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_debug_DASHlocation] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_mcsymbol] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN2] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BANG] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_null] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_md_value_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_PIPE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_STAR] = {
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
  [anon_sym_DOT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym__] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_tied_DASHdef] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_target_DASHflags] = {
    .visible = true,
    .named = false,
  },
  [sym_primitive_type] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_vscale] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_x] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_CustomRegMask] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_same_value] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_def_cfa_register] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_restore] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_undefined] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_offset] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_rel_offset] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_def_cfa] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_def_cfa_offset] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_adjust_cfa_offset] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_llvm_def_aspace_cfa] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_register] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_escape] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_remember_state] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_restore_state] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_window_save] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_negate_ra_sign_state] = {
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
  [anon_sym_intpred] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_floatpred] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_eq] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ne] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_sgt] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_sge] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_slt] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_sle] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ugt] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_uge] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ult] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ule] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_oeq] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ogt] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_oge] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_olt] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ole] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_one] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ord] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_uno] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ueq] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_une] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_shufflemask] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_undef] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_liveout] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_target_DASHindex] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_blockaddress] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_intrinsic] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_load] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_store] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_unknown_DASHsize] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_on] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_from] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_into] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_align] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_basealign] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_addrspace] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_unknown_DASHaddress] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PLUS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_call_DASHentry] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_custom] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_constant_DASHpool] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_stack] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_got] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_jump_DASHtable] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_volatile] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_non_DASHtemporal] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_dereferenceable] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_invariant] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_syncscope] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_unordered] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_monotonic] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_acquire] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_release] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_acq_rel] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_seq_cst] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_implicit] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_implicit_DASHdef] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_def] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_dead] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_killed] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_internal] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_early_DASHclobber] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_debug_DASHuse] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_renamable] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_frame_DASHsetup] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_frame_DASHdestroy] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_nnan] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ninf] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_nsz] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_arcp] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_contract] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_afn] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_reassoc] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_nuw] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_nsw] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_exact] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_nofpexcept] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_nomerge] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_unpredictable] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_noconvergent] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_nneg] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_disjoint] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_nusw] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_machine_DASHblock_DASHaddress_DASHtaken] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_landing_DASHpad] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_inlineasm_DASHbr_DASHindirect_DASHtarget] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ehfunclet_DASHentry] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ir_DASHblock_DASHaddress_DASHtaken] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_call_DASHframe_DASHsize] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_bb_id] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_bbsections] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_Exception] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_Cold] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_half] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_bfloat] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_float] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_double] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_x86_fp80] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_fp128] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ppc_fp128] = {
    .visible = true,
    .named = false,
  },
  [sym_body] = {
    .visible = true,
    .named = true,
  },
  [sym_basic_block] = {
    .visible = true,
    .named = true,
  },
  [sym_label] = {
    .visible = true,
    .named = true,
  },
  [sym_float] = {
    .visible = true,
    .named = true,
  },
  [sym_register] = {
    .visible = true,
    .named = true,
  },
  [sym_bundle] = {
    .visible = true,
    .named = true,
  },
  [sym_successors] = {
    .visible = true,
    .named = true,
  },
  [sym_liveins] = {
    .visible = true,
    .named = true,
  },
  [sym_instruction] = {
    .visible = true,
    .named = true,
  },
  [sym_mc_symbol] = {
    .visible = true,
    .named = true,
  },
  [sym_metadata] = {
    .visible = true,
    .named = true,
  },
  [sym_md_value] = {
    .visible = true,
    .named = true,
  },
  [sym_register_operand] = {
    .visible = true,
    .named = true,
  },
  [sym_argument] = {
    .visible = true,
    .named = true,
  },
  [sym_machine_operand] = {
    .visible = true,
    .named = true,
  },
  [sym_subregister] = {
    .visible = true,
    .named = true,
  },
  [sym_registerclass] = {
    .visible = true,
    .named = true,
  },
  [sym_low_level_type] = {
    .visible = true,
    .named = true,
  },
  [sym_custom_regmask] = {
    .visible = true,
    .named = true,
  },
  [sym_cfi_operand] = {
    .visible = true,
    .named = true,
  },
  [sym_immediate] = {
    .visible = true,
    .named = true,
  },
  [sym_predicate] = {
    .visible = true,
    .named = true,
  },
  [sym_intpred] = {
    .visible = true,
    .named = true,
  },
  [sym_floatpred] = {
    .visible = true,
    .named = true,
  },
  [sym_shuffle_mask] = {
    .visible = true,
    .named = true,
  },
  [sym_liveout] = {
    .visible = true,
    .named = true,
  },
  [sym_target_index] = {
    .visible = true,
    .named = true,
  },
  [sym_block_address] = {
    .visible = true,
    .named = true,
  },
  [sym_intrinsic] = {
    .visible = true,
    .named = true,
  },
  [sym_memory_operand] = {
    .visible = true,
    .named = true,
  },
  [sym_mem_attribute] = {
    .visible = true,
    .named = true,
  },
  [sym_machine_pointer_info] = {
    .visible = true,
    .named = true,
  },
  [sym_ir_value] = {
    .visible = true,
    .named = true,
  },
  [sym_escaped_ir_value] = {
    .visible = true,
    .named = true,
  },
  [sym__escaped_ir_content] = {
    .visible = false,
    .named = true,
  },
  [sym_offset] = {
    .visible = true,
    .named = true,
  },
  [sym_memory_pseudo_source_value] = {
    .visible = true,
    .named = true,
  },
  [sym_memory_pseudo_source_value_keyword] = {
    .visible = true,
    .named = true,
  },
  [sym_memory_operand_flag] = {
    .visible = true,
    .named = true,
  },
  [sym_sync_scope] = {
    .visible = true,
    .named = true,
  },
  [sym_atomic_ordering] = {
    .visible = true,
    .named = true,
  },
  [sym_register_flag] = {
    .visible = true,
    .named = true,
  },
  [sym_instruction_flag] = {
    .visible = true,
    .named = true,
  },
  [sym_attribute] = {
    .visible = true,
    .named = true,
  },
  [sym_float_keyword] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_body_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_basic_block_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_basic_block_repeat2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_basic_block_repeat3] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_bundle_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_successors_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_liveins_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_instruction_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_instruction_repeat2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_instruction_repeat3] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_instruction_repeat4] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_instruction_repeat5] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_metadata_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_register_operand_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_argument_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_custom_regmask_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_cfi_operand_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_shuffle_mask_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_memory_operand_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_memory_operand_repeat2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_escaped_ir_value_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum ts_field_identifiers {
  field_name = 1,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_name] = "name",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 1},
  [3] = {.index = 2, .length = 1},
  [4] = {.index = 3, .length = 1},
  [5] = {.index = 4, .length = 1},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_name, 0},
  [1] =
    {field_name, 1},
  [2] =
    {field_name, 2},
  [3] =
    {field_name, 3},
  [4] =
    {field_name, 4},
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
  [71] = 64,
  [72] = 72,
  [73] = 65,
  [74] = 74,
  [75] = 68,
  [76] = 76,
  [77] = 77,
  [78] = 78,
  [79] = 79,
  [80] = 80,
  [81] = 61,
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
  [99] = 97,
  [100] = 100,
  [101] = 94,
  [102] = 91,
  [103] = 87,
  [104] = 82,
  [105] = 79,
  [106] = 98,
  [107] = 107,
  [108] = 108,
  [109] = 89,
  [110] = 110,
  [111] = 111,
  [112] = 107,
  [113] = 113,
  [114] = 95,
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
  [214] = 96,
  [215] = 215,
  [216] = 88,
  [217] = 217,
  [218] = 218,
  [219] = 92,
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
  [285] = 85,
  [286] = 286,
  [287] = 287,
  [288] = 288,
  [289] = 289,
  [290] = 290,
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
  [342] = 86,
  [343] = 343,
  [344] = 344,
  [345] = 345,
  [346] = 346,
  [347] = 347,
  [348] = 348,
  [349] = 349,
  [350] = 350,
  [351] = 351,
  [352] = 352,
  [353] = 353,
  [354] = 354,
  [355] = 355,
  [356] = 356,
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
  [371] = 371,
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
  [411] = 120,
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
  [431] = 431,
  [432] = 432,
  [433] = 433,
  [434] = 434,
  [435] = 435,
  [436] = 436,
  [437] = 437,
  [438] = 438,
  [439] = 439,
  [440] = 440,
  [441] = 441,
  [442] = 442,
  [443] = 443,
  [444] = 444,
  [445] = 445,
  [446] = 446,
  [447] = 447,
  [448] = 448,
  [449] = 449,
  [450] = 450,
  [451] = 451,
  [452] = 452,
  [453] = 453,
  [454] = 454,
  [455] = 455,
  [456] = 456,
  [457] = 457,
  [458] = 458,
  [459] = 459,
  [460] = 460,
  [461] = 461,
  [462] = 462,
  [463] = 463,
  [464] = 464,
  [465] = 465,
  [466] = 466,
  [467] = 467,
  [468] = 468,
  [469] = 469,
  [470] = 470,
  [471] = 471,
  [472] = 472,
  [473] = 473,
  [474] = 474,
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
  [491] = 491,
  [492] = 492,
  [493] = 493,
  [494] = 494,
  [495] = 495,
  [496] = 496,
  [497] = 497,
  [498] = 498,
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
  [589] = 548,
  [590] = 590,
  [591] = 591,
  [592] = 592,
  [593] = 593,
  [594] = 594,
  [595] = 595,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(886);
      ADVANCE_MAP(
        '\n', 893,
        '\r', 1,
        '!', 1519,
        '"', 10,
        '$', 878,
        '%', 17,
        '&', 20,
        '(', 1518,
        ')', 890,
        '*', 1527,
        '+', 1629,
        ',', 889,
        '-', 1630,
        '.', 1530,
        '/', 26,
        '0', 855,
        ':', 892,
        ';', 894,
        '<', 1515,
        '=', 1495,
        '>', 1517,
        '@', 21,
        'C', 600,
        'E', 856,
        '[', 1528,
        ']', 1529,
        '_', 1531,
        '`', 1628,
        'a', 192,
        'b', 105,
        'c', 106,
        'd', 173,
        'e', 101,
        'f', 115,
        'g', 601,
        'h', 118,
        'i', 523,
        'j', 831,
        'k', 449,
        'l', 108,
        'm', 116,
        'n', 267,
        'o', 307,
        'p', 1537,
        'r', 268,
        's', 1536,
        't', 109,
        'u', 73,
        'v', 611,
        'w', 450,
        'x', 1540,
        '{', 1489,
        '|', 1526,
        '}', 1490,
      );
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(882);
      END_STATE();
    case 1:
      if (lookahead == '\n') ADVANCE(893);
      END_STATE();
    case 2:
      ADVANCE_MAP(
        '\n', 893,
        '\r', 1,
        '!', 16,
        '$', 878,
        '%', 174,
        '&', 20,
        ',', 889,
        '-', 1399,
        '.', 1400,
        '/', 26,
        '0', 1408,
        ':', 80,
        ';', 894,
        '<', 1515,
        '@', 21,
        'C', 1369,
        '_', 1532,
        'a', 1016,
        'b', 1097,
        'c', 1105,
        'd', 982,
        'e', 938,
        'f', 1171,
        'h', 944,
        'i', 1186,
        'k', 1140,
        'l', 1137,
        'm', 1189,
        'n', 1048,
        'o', 1104,
        'p', 997,
        'r', 1032,
        's', 943,
        't', 950,
        'u', 1204,
        'w', 1151,
        'x', 918,
        '{', 1489,
      );
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(2);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(1409);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 3:
      ADVANCE_MAP(
        '\n', 893,
        '\r', 1,
        '"', 10,
        '%', 18,
        '(', 888,
        ')', 890,
        '+', 1629,
        ',', 889,
        '-', 1630,
        '.', 1530,
        '/', 26,
        ':', 892,
        ';', 894,
        '=', 1495,
        '@', 21,
        '`', 1628,
        'c', 153,
        'd', 304,
        'e', 661,
        'f', 114,
        'g', 601,
        'h', 309,
        'i', 579,
        'j', 831,
        'l', 603,
        'm', 528,
        'n', 305,
        'o', 308,
        'p', 220,
        's', 414,
        't', 671,
        'u', 312,
        'v', 610,
        '{', 1489,
      );
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(3);
      END_STATE();
    case 4:
      ADVANCE_MAP(
        '\n', 893,
        '\r', 1,
        '$', 878,
        '%', 879,
        '(', 1518,
        ')', 890,
        '+', 1629,
        ',', 889,
        '-', 1630,
        '/', 26,
        ':', 80,
        ';', 894,
        '_', 1531,
        'c', 392,
        'd', 306,
        'e', 100,
        'f', 690,
        'h', 309,
        'i', 524,
        'k', 449,
        'm', 528,
        'o', 553,
        'p', 220,
        'r', 362,
        'u', 591,
        '{', 1489,
      );
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(5);
      END_STATE();
    case 5:
      ADVANCE_MAP(
        '\n', 893,
        '\r', 1,
        '$', 878,
        '%', 879,
        ')', 890,
        '+', 1629,
        ',', 889,
        '-', 1630,
        '/', 26,
        ':', 80,
        ';', 894,
        '_', 1531,
        'c', 392,
        'd', 306,
        'e', 100,
        'f', 690,
        'h', 309,
        'i', 524,
        'k', 449,
        'm', 528,
        'o', 553,
        'p', 220,
        'r', 362,
        'u', 591,
        '{', 1489,
      );
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(5);
      END_STATE();
    case 6:
      ADVANCE_MAP(
        '!', 1519,
        '(', 1518,
        ')', 890,
        '*', 1527,
        ',', 889,
        '/', 26,
        ':', 891,
        ';', 894,
        '<', 1515,
        '>', 1517,
        '[', 1528,
        ']', 1529,
        'n', 1524,
        '{', 1489,
        '|', 1526,
        '}', 1490,
      );
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(7);
      if (lookahead == '$' ||
          ('-' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1525);
      END_STATE();
    case 7:
      ADVANCE_MAP(
        '!', 1519,
        '(', 888,
        ')', 890,
        '*', 1527,
        ',', 889,
        '/', 26,
        ':', 891,
        ';', 894,
        '<', 1515,
        '>', 1517,
        '[', 1528,
        ']', 1529,
        'n', 1524,
        '{', 1489,
        '|', 1526,
        '}', 1490,
      );
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(7);
      if (lookahead == '$' ||
          ('-' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= '\\') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1525);
      END_STATE();
    case 8:
      ADVANCE_MAP(
        '!', 16,
        '$', 878,
        '%', 174,
        '&', 20,
        '-', 1399,
        '.', 1400,
        '/', 26,
        '0', 1408,
        ';', 894,
        '<', 1515,
        '@', 21,
        'C', 1369,
        '_', 1532,
        'a', 1016,
        'b', 1097,
        'd', 1094,
        'e', 938,
        'f', 1171,
        'h', 945,
        'i', 1186,
        'k', 1140,
        'l', 1137,
        'n', 1048,
        'o', 1104,
        'p', 1249,
        'r', 1032,
        's', 943,
        't', 979,
        'u', 1204,
        'w', 1151,
        'x', 918,
      );
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(8);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(1409);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('c' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 9:
      ADVANCE_MAP(
        '!', 16,
        '$', 878,
        '%', 174,
        '&', 20,
        '-', 1399,
        '.', 1400,
        '/', 26,
        '0', 1408,
        ';', 894,
        '<', 1515,
        '@', 21,
        'C', 1369,
        '_', 1532,
        'a', 1016,
        'b', 1097,
        'd', 983,
        'e', 938,
        'f', 1171,
        'h', 945,
        'i', 1186,
        'k', 1140,
        'l', 1137,
        'n', 1048,
        'o', 1104,
        'p', 1249,
        'r', 1032,
        's', 943,
        't', 950,
        'u', 1204,
        'w', 1151,
        'x', 918,
      );
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(9);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(1409);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('c' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 10:
      if (lookahead == '"') ADVANCE(1405);
      if (lookahead != 0) ADVANCE(10);
      END_STATE();
    case 11:
      if (lookahead == '"') ADVANCE(1486);
      if (lookahead != 0) ADVANCE(11);
      END_STATE();
    case 12:
      if (lookahead == '"') ADVANCE(1467);
      if (lookahead != 0) ADVANCE(12);
      END_STATE();
    case 13:
      if (lookahead == '"') ADVANCE(1461);
      if (lookahead != 0) ADVANCE(13);
      END_STATE();
    case 14:
      if (lookahead == '"') ADVANCE(1464);
      if (lookahead != 0) ADVANCE(14);
      END_STATE();
    case 15:
      if (lookahead == '"') ADVANCE(1458);
      if (lookahead != 0) ADVANCE(15);
      END_STATE();
    case 16:
      if (lookahead == '"') ADVANCE(11);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1487);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1488);
      END_STATE();
    case 17:
      if (lookahead == '"') ADVANCE(12);
      if (lookahead == 'c') ADVANCE(1439);
      if (lookahead == 'f') ADVANCE(1432);
      if (lookahead == 'i') ADVANCE(1442);
      if (lookahead == 'j') ADVANCE(1448);
      if (lookahead == 's') ADVANCE(1445);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1450);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 18:
      if (lookahead == '"') ADVANCE(12);
      if (lookahead == 'f') ADVANCE(1475);
      if (lookahead == 'i') ADVANCE(1477);
      if (lookahead == 's') ADVANCE(1479);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1481);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1484);
      END_STATE();
    case 19:
      if (lookahead == '"') ADVANCE(12);
      if (lookahead == 'i') ADVANCE(1477);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1481);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1484);
      END_STATE();
    case 20:
      if (lookahead == '"') ADVANCE(13);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1462);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1463);
      END_STATE();
    case 21:
      if (lookahead == '"') ADVANCE(14);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1465);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1466);
      END_STATE();
    case 22:
      if (lookahead == '"') ADVANCE(15);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1459);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1460);
      END_STATE();
    case 23:
      ADVANCE_MAP(
        '%', 19,
        '(', 888,
        ')', 890,
        '*', 1527,
        ',', 889,
        '-', 1399,
        '/', 26,
        '0', 1408,
        ';', 894,
        '<', 1515,
        '>', 1517,
        '@', 21,
        '[', 1528,
        ']', 1529,
        '`', 1628,
        '{', 1489,
        '}', 1490,
      );
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(23);
      if (lookahead == 'i' ||
          lookahead == 'p' ||
          lookahead == 's') ADVANCE(1398);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(1409);
      if (lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('_' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 24:
      ADVANCE_MAP(
        '%', 444,
        '(', 888,
        ')', 890,
        ',', 889,
        '-', 872,
        '/', 26,
        '0', 1408,
        ';', 894,
        'C', 599,
        'E', 856,
        'a', 193,
        'b', 172,
        'c', 157,
        'e', 427,
        'f', 114,
        'i', 571,
        'l', 107,
        'm', 117,
        'r', 352,
        's', 311,
        't', 671,
        'u', 554,
        'v', 731,
      );
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(24);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(1409);
      END_STATE();
    case 25:
      ADVANCE_MAP(
        '%', 444,
        '/', 26,
        ';', 894,
        'a', 1112,
        'c', 1235,
        'd', 1148,
        'e', 1391,
        'f', 1279,
        'n', 1147,
        'r', 1085,
        'u', 1209,
      );
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(25);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 26:
      if (lookahead == '*') ADVANCE(28);
      END_STATE();
    case 27:
      if (lookahead == '*') ADVANCE(27);
      if (lookahead == '/') ADVANCE(895);
      if (lookahead != 0) ADVANCE(28);
      END_STATE();
    case 28:
      if (lookahead == '*') ADVANCE(27);
      if (lookahead != 0) ADVANCE(28);
      END_STATE();
    case 29:
      if (lookahead == '+') ADVANCE(874);
      if (lookahead == '-') ADVANCE(873);
      if (lookahead == '/') ADVANCE(26);
      if (lookahead == '0') ADVANCE(1406);
      if (lookahead == ';') ADVANCE(894);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(29);
      if (lookahead == 's' ||
          lookahead == 'u') ADVANCE(72);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(1407);
      END_STATE();
    case 30:
      if (lookahead == '-') ADVANCE(345);
      END_STATE();
    case 31:
      if (lookahead == '-') ADVANCE(465);
      END_STATE();
    case 32:
      if (lookahead == '-') ADVANCE(252);
      END_STATE();
    case 33:
      if (lookahead == '-') ADVANCE(398);
      END_STATE();
    case 34:
      if (lookahead == '-') ADVANCE(169);
      END_STATE();
    case 35:
      if (lookahead == '-') ADVANCE(464);
      END_STATE();
    case 36:
      if (lookahead == '-') ADVANCE(791);
      END_STATE();
    case 37:
      if (lookahead == '-') ADVANCE(178);
      END_STATE();
    case 38:
      if (lookahead == '-') ADVANCE(658);
      END_STATE();
    case 39:
      if (lookahead == '-') ADVANCE(151);
      END_STATE();
    case 40:
      if (lookahead == '-') ADVANCE(539);
      END_STATE();
    case 41:
      if (lookahead == '-') ADVANCE(402);
      END_STATE();
    case 42:
      if (lookahead == '-') ADVANCE(219);
      END_STATE();
    case 43:
      if (lookahead == '-') ADVANCE(754);
      END_STATE();
    case 44:
      if (lookahead == '-') ADVANCE(576);
      END_STATE();
    case 45:
      if (lookahead == '-') ADVANCE(358);
      END_STATE();
    case 46:
      if (lookahead == '-') ADVANCE(344);
      END_STATE();
    case 47:
      if (lookahead == '-') ADVANCE(177);
      END_STATE();
    case 48:
      if (lookahead == '-') ADVANCE(827);
      END_STATE();
    case 49:
      if (lookahead == '-') ADVANCE(806);
      END_STATE();
    case 50:
      if (lookahead == '-') ADVANCE(652);
      END_STATE();
    case 51:
      if (lookahead == '-') ADVANCE(736);
      END_STATE();
    case 52:
      if (lookahead == '-') ADVANCE(435);
      END_STATE();
    case 53:
      if (lookahead == '-') ADVANCE(805);
      END_STATE();
    case 54:
      if (lookahead == '-') ADVANCE(251);
      END_STATE();
    case 55:
      if (lookahead == '-') ADVANCE(807);
      END_STATE();
    case 56:
      if (lookahead == '-') ADVANCE(696);
      END_STATE();
    case 57:
      if (lookahead == '-') ADVANCE(456);
      END_STATE();
    case 58:
      if (lookahead == '-') ADVANCE(190);
      END_STATE();
    case 59:
      if (lookahead == '-') ADVANCE(463);
      END_STATE();
    case 60:
      if (lookahead == '-') ADVANCE(824);
      END_STATE();
    case 61:
      if (lookahead == '-') ADVANCE(767);
      END_STATE();
    case 62:
      if (lookahead == '-') ADVANCE(770);
      END_STATE();
    case 63:
      if (lookahead == '-') ADVANCE(466);
      END_STATE();
    case 64:
      if (lookahead == '-') ADVANCE(170);
      END_STATE();
    case 65:
      if (lookahead == '-') ADVANCE(168);
      END_STATE();
    case 66:
      if (lookahead == '-') ADVANCE(171);
      END_STATE();
    case 67:
      if (lookahead == '-') ADVANCE(191);
      END_STATE();
    case 68:
      if (lookahead == '.') ADVANCE(1411);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(68);
      END_STATE();
    case 69:
      if (lookahead == '.') ADVANCE(22);
      END_STATE();
    case 70:
      if (lookahead == '/') ADVANCE(26);
      if (lookahead == ';') ADVANCE(894);
      if (lookahead == '<') ADVANCE(1515);
      if (lookahead == 't') ADVANCE(432);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(70);
      if (lookahead == 'p' ||
          lookahead == 's') ADVANCE(1538);
      END_STATE();
    case 71:
      if (lookahead == '/') ADVANCE(26);
      if (lookahead == ';') ADVANCE(894);
      if (lookahead == '_') ADVANCE(1532);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(71);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 72:
      if (lookahead == '0') ADVANCE(855);
      END_STATE();
    case 73:
      if (lookahead == '0') ADVANCE(855);
      if (lookahead == 'e') ADVANCE(664);
      if (lookahead == 'g') ADVANCE(274);
      if (lookahead == 'l') ADVANCE(275);
      if (lookahead == 'n') ADVANCE(247);
      END_STATE();
    case 74:
      if (lookahead == '1') ADVANCE(76);
      END_STATE();
    case 75:
      if (lookahead == '1') ADVANCE(77);
      END_STATE();
    case 76:
      if (lookahead == '2') ADVANCE(78);
      END_STATE();
    case 77:
      if (lookahead == '2') ADVANCE(79);
      END_STATE();
    case 78:
      if (lookahead == '8') ADVANCE(1725);
      END_STATE();
    case 79:
      if (lookahead == '8') ADVANCE(1727);
      END_STATE();
    case 80:
      if (lookahead == ':') ADVANCE(1514);
      END_STATE();
    case 81:
      if (lookahead == '>') ADVANCE(887);
      END_STATE();
    case 82:
      if (lookahead == 'M') ADVANCE(141);
      END_STATE();
    case 83:
      if (lookahead == 'R') ADVANCE(314);
      END_STATE();
    case 84:
      if (lookahead == '_') ADVANCE(847);
      END_STATE();
    case 85:
      if (lookahead == '_') ADVANCE(433);
      if (lookahead == 's') ADVANCE(330);
      END_STATE();
    case 86:
      if (lookahead == '_') ADVANCE(616);
      if (lookahead == 'e') ADVANCE(156);
      END_STATE();
    case 87:
      if (lookahead == '_') ADVANCE(396);
      END_STATE();
    case 88:
      if (lookahead == '_') ADVANCE(743);
      END_STATE();
    case 89:
      if (lookahead == '_') ADVANCE(226);
      END_STATE();
    case 90:
      if (lookahead == '_') ADVANCE(757);
      END_STATE();
    case 91:
      if (lookahead == '_') ADVANCE(167);
      END_STATE();
    case 92:
      if (lookahead == '_') ADVANCE(691);
      if (lookahead == 'u') ADVANCE(454);
      END_STATE();
    case 93:
      if (lookahead == '_') ADVANCE(250);
      END_STATE();
    case 94:
      if (lookahead == '_') ADVANCE(222);
      END_STATE();
    case 95:
      if (lookahead == '_') ADVANCE(688);
      END_STATE();
    case 96:
      if (lookahead == '_') ADVANCE(224);
      END_STATE();
    case 97:
      if (lookahead == '_') ADVANCE(764);
      END_STATE();
    case 98:
      if (lookahead == '_') ADVANCE(766);
      END_STATE();
    case 99:
      if (lookahead == '_') ADVANCE(642);
      END_STATE();
    case 100:
      if (lookahead == 'a') ADVANCE(678);
      END_STATE();
    case 101:
      if (lookahead == 'a') ADVANCE(678);
      if (lookahead == 'h') ADVANCE(393);
      if (lookahead == 'q') ADVANCE(1581);
      if (lookahead == 's') ADVANCE(221);
      if (lookahead == 'x') ADVANCE(126);
      END_STATE();
    case 102:
      if (lookahead == 'a') ADVANCE(1506);
      END_STATE();
    case 103:
      if (lookahead == 'a') ADVANCE(1555);
      END_STATE();
    case 104:
      if (lookahead == 'a') ADVANCE(1561);
      END_STATE();
    case 105:
      if (lookahead == 'a') ADVANCE(726);
      if (lookahead == 'b') ADVANCE(85);
      if (lookahead == 'f') ADVANCE(519);
      if (lookahead == 'l') ADVANCE(612);
      END_STATE();
    case 106:
      if (lookahead == 'a') ADVANCE(490);
      if (lookahead == 'f') ADVANCE(431);
      if (lookahead == 'o') ADVANCE(545);
      if (lookahead == 'u') ADVANCE(763);
      END_STATE();
    case 107:
      if (lookahead == 'a') ADVANCE(556);
      END_STATE();
    case 108:
      if (lookahead == 'a') ADVANCE(556);
      if (lookahead == 'i') ADVANCE(845);
      if (lookahead == 'l') ADVANCE(844);
      if (lookahead == 'o') ADVANCE(120);
      END_STATE();
    case 109:
      if (lookahead == 'a') ADVANCE(672);
      if (lookahead == 'i') ADVANCE(319);
      if (lookahead == 'r') ADVANCE(835);
      END_STATE();
    case 110:
      if (lookahead == 'a') ADVANCE(646);
      END_STATE();
    case 111:
      if (lookahead == 'a') ADVANCE(538);
      if (lookahead == 'o') ADVANCE(525);
      END_STATE();
    case 112:
      if (lookahead == 'a') ADVANCE(235);
      if (lookahead == 'b') ADVANCE(838);
      if (lookahead == 'f') ADVANCE(1654);
      if (lookahead == 'r') ADVANCE(317);
      END_STATE();
    case 113:
      if (lookahead == 'a') ADVANCE(235);
      if (lookahead == 'b') ADVANCE(838);
      if (lookahead == 'f') ADVANCE(1652);
      END_STATE();
    case 114:
      if (lookahead == 'a') ADVANCE(514);
      END_STATE();
    case 115:
      if (lookahead == 'a') ADVANCE(514);
      if (lookahead == 'l') ADVANCE(605);
      if (lookahead == 'p') ADVANCE(74);
      if (lookahead == 'r') ADVANCE(111);
      END_STATE();
    case 116:
      if (lookahead == 'a') ADVANCE(194);
      if (lookahead == 'c') ADVANCE(715);
      if (lookahead == 'm') ADVANCE(675);
      if (lookahead == 'o') ADVANCE(575);
      END_STATE();
    case 117:
      if (lookahead == 'a') ADVANCE(194);
      if (lookahead == 'o') ADVANCE(575);
      END_STATE();
    case 118:
      if (lookahead == 'a') ADVANCE(488);
      if (lookahead == 'e') ADVANCE(110);
      END_STATE();
    case 119:
      if (lookahead == 'a') ADVANCE(730);
      if (lookahead == 'g') ADVANCE(455);
      if (lookahead == 'l') ADVANCE(86);
      if (lookahead == 'm') ADVANCE(320);
      if (lookahead == 'n') ADVANCE(125);
      if (lookahead == 's') ADVANCE(793);
      END_STATE();
    case 120:
      if (lookahead == 'a') ADVANCE(236);
      END_STATE();
    case 121:
      if (lookahead == 'a') ADVANCE(546);
      if (lookahead == 'e') ADVANCE(411);
      END_STATE();
    case 122:
      if (lookahead == 'a') ADVANCE(420);
      END_STATE();
    case 123:
      if (lookahead == 'a') ADVANCE(775);
      END_STATE();
    case 124:
      if (lookahead == 'a') ADVANCE(804);
      END_STATE();
    case 125:
      if (lookahead == 'a') ADVANCE(535);
      END_STATE();
    case 126:
      if (lookahead == 'a') ADVANCE(205);
      END_STATE();
    case 127:
      if (lookahead == 'a') ADVANCE(680);
      END_STATE();
    case 128:
      if (lookahead == 'a') ADVANCE(813);
      END_STATE();
    case 129:
      if (lookahead == 'a') ADVANCE(99);
      END_STATE();
    case 130:
      if (lookahead == 'a') ADVANCE(201);
      if (lookahead == 'o') ADVANCE(686);
      END_STATE();
    case 131:
      if (lookahead == 'a') ADVANCE(735);
      END_STATE();
    case 132:
      if (lookahead == 'a') ADVANCE(776);
      END_STATE();
    case 133:
      if (lookahead == 'a') ADVANCE(248);
      END_STATE();
    case 134:
      if (lookahead == 'a') ADVANCE(510);
      END_STATE();
    case 135:
      if (lookahead == 'a') ADVANCE(480);
      END_STATE();
    case 136:
      if (lookahead == 'a') ADVANCE(725);
      END_STATE();
    case 137:
      if (lookahead == 'a') ADVANCE(512);
      END_STATE();
    case 138:
      if (lookahead == 'a') ADVANCE(212);
      END_STATE();
    case 139:
      if (lookahead == 'a') ADVANCE(677);
      END_STATE();
    case 140:
      if (lookahead == 'a') ADVANCE(243);
      END_STATE();
    case 141:
      if (lookahead == 'a') ADVANCE(729);
      END_STATE();
    case 142:
      if (lookahead == 'a') ADVANCE(583);
      END_STATE();
    case 143:
      if (lookahead == 'a') ADVANCE(482);
      END_STATE();
    case 144:
      if (lookahead == 'a') ADVANCE(570);
      END_STATE();
    case 145:
      if (lookahead == 'a') ADVANCE(653);
      END_STATE();
    case 146:
      if (lookahead == 'a') ADVANCE(90);
      END_STATE();
    case 147:
      if (lookahead == 'a') ADVANCE(474);
      END_STATE();
    case 148:
      if (lookahead == 'a') ADVANCE(499);
      END_STATE();
    case 149:
      if (lookahead == 'a') ADVANCE(216);
      END_STATE();
    case 150:
      if (lookahead == 'a') ADVANCE(846);
      END_STATE();
    case 151:
      if (lookahead == 'a') ADVANCE(520);
      END_STATE();
    case 152:
      if (lookahead == 'a') ADVANCE(475);
      END_STATE();
    case 153:
      if (lookahead == 'a') ADVANCE(498);
      if (lookahead == 'f') ADVANCE(431);
      if (lookahead == 'o') ADVANCE(594);
      if (lookahead == 'u') ADVANCE(763);
      END_STATE();
    case 154:
      if (lookahead == 'a') ADVANCE(809);
      END_STATE();
    case 155:
      if (lookahead == 'a') ADVANCE(217);
      END_STATE();
    case 156:
      if (lookahead == 'a') ADVANCE(749);
      END_STATE();
    case 157:
      if (lookahead == 'a') ADVANCE(500);
      END_STATE();
    case 158:
      if (lookahead == 'a') ADVANCE(810);
      END_STATE();
    case 159:
      if (lookahead == 'a') ADVANCE(812);
      END_STATE();
    case 160:
      if (lookahead == 'a') ADVANCE(185);
      END_STATE();
    case 161:
      if (lookahead == 'a') ADVANCE(540);
      END_STATE();
    case 162:
      if (lookahead == 'a') ADVANCE(186);
      END_STATE();
    case 163:
      if (lookahead == 'a') ADVANCE(187);
      END_STATE();
    case 164:
      if (lookahead == 'a') ADVANCE(704);
      END_STATE();
    case 165:
      if (lookahead == 'a') ADVANCE(826);
      END_STATE();
    case 166:
      if (lookahead == 'a') ADVANCE(188);
      END_STATE();
    case 167:
      if (lookahead == 'a') ADVANCE(768);
      END_STATE();
    case 168:
      if (lookahead == 'a') ADVANCE(264);
      END_STATE();
    case 169:
      if (lookahead == 'a') ADVANCE(264);
      if (lookahead == 's') ADVANCE(429);
      END_STATE();
    case 170:
      if (lookahead == 'a') ADVANCE(265);
      END_STATE();
    case 171:
      if (lookahead == 'a') ADVANCE(266);
      END_STATE();
    case 172:
      if (lookahead == 'b') ADVANCE(85);
      END_STATE();
    case 173:
      if (lookahead == 'b') ADVANCE(413);
      if (lookahead == 'e') ADVANCE(112);
      if (lookahead == 'i') ADVANCE(714);
      if (lookahead == 'o') ADVANCE(832);
      END_STATE();
    case 174:
      if (lookahead == 'b') ADVANCE(1426);
      if (lookahead == 'c') ADVANCE(1439);
      if (lookahead == 'f') ADVANCE(1432);
      if (lookahead == 'j') ADVANCE(1448);
      if (lookahead == 's') ADVANCE(1445);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 175:
      if (lookahead == 'b') ADVANCE(617);
      END_STATE();
    case 176:
      if (lookahead == 'b') ADVANCE(495);
      END_STATE();
    case 177:
      if (lookahead == 'b') ADVANCE(507);
      END_STATE();
    case 178:
      if (lookahead == 'b') ADVANCE(698);
      END_STATE();
    case 179:
      if (lookahead == 'b') ADVANCE(328);
      END_STATE();
    case 180:
      if (lookahead == 'b') ADVANCE(340);
      END_STATE();
    case 181:
      if (lookahead == 'b') ADVANCE(349);
      END_STATE();
    case 182:
      if (lookahead == 'b') ADVANCE(180);
      END_STATE();
    case 183:
      if (lookahead == 'b') ADVANCE(622);
      END_STATE();
    case 184:
      if (lookahead == 'b') ADVANCE(623);
      END_STATE();
    case 185:
      if (lookahead == 'b') ADVANCE(503);
      END_STATE();
    case 186:
      if (lookahead == 'b') ADVANCE(504);
      END_STATE();
    case 187:
      if (lookahead == 'b') ADVANCE(505);
      END_STATE();
    case 188:
      if (lookahead == 'b') ADVANCE(506);
      END_STATE();
    case 189:
      if (lookahead == 'b') ADVANCE(842);
      if (lookahead == 'r') ADVANCE(317);
      END_STATE();
    case 190:
      if (lookahead == 'b') ADVANCE(518);
      END_STATE();
    case 191:
      if (lookahead == 'b') ADVANCE(522);
      END_STATE();
    case 192:
      if (lookahead == 'c') ADVANCE(662);
      if (lookahead == 'd') ADVANCE(244);
      if (lookahead == 'f') ADVANCE(544);
      if (lookahead == 'l') ADVANCE(430);
      if (lookahead == 'r') ADVANCE(200);
      END_STATE();
    case 193:
      if (lookahead == 'c') ADVANCE(662);
      if (lookahead == 'l') ADVANCE(430);
      END_STATE();
    case 194:
      if (lookahead == 'c') ADVANCE(428);
      END_STATE();
    case 195:
      if (lookahead == 'c') ADVANCE(87);
      END_STATE();
    case 196:
      if (lookahead == 'c') ADVANCE(476);
      END_STATE();
    case 197:
      if (lookahead == 'c') ADVANCE(1684);
      END_STATE();
    case 198:
      if (lookahead == 'c') ADVANCE(1615);
      END_STATE();
    case 199:
      if (lookahead == 'c') ADVANCE(1643);
      END_STATE();
    case 200:
      if (lookahead == 'c') ADVANCE(644);
      END_STATE();
    case 201:
      if (lookahead == 'c') ADVANCE(468);
      END_STATE();
    case 202:
      if (lookahead == 'c') ADVANCE(472);
      END_STATE();
    case 203:
      if (lookahead == 'c') ADVANCE(615);
      if (lookahead == 'f') ADVANCE(651);
      if (lookahead == 'm') ADVANCE(375);
      if (lookahead == 'n') ADVANCE(49);
      END_STATE();
    case 204:
      if (lookahead == 'c') ADVANCE(318);
      END_STATE();
    case 205:
      if (lookahead == 'c') ADVANCE(774);
      END_STATE();
    case 206:
      if (lookahead == 'c') ADVANCE(471);
      END_STATE();
    case 207:
      if (lookahead == 'c') ADVANCE(741);
      END_STATE();
    case 208:
      if (lookahead == 'c') ADVANCE(148);
      END_STATE();
    case 209:
      if (lookahead == 'c') ADVANCE(397);
      END_STATE();
    case 210:
      if (lookahead == 'c') ADVANCE(442);
      END_STATE();
    case 211:
      if (lookahead == 'c') ADVANCE(639);
      END_STATE();
    case 212:
      if (lookahead == 'c') ADVANCE(780);
      END_STATE();
    case 213:
      if (lookahead == 'c') ADVANCE(365);
      END_STATE();
    case 214:
      if (lookahead == 'c') ADVANCE(40);
      END_STATE();
    case 215:
      if (lookahead == 'c') ADVANCE(819);
      END_STATE();
    case 216:
      if (lookahead == 'c') ADVANCE(290);
      END_STATE();
    case 217:
      if (lookahead == 'c') ADVANCE(376);
      END_STATE();
    case 218:
      if (lookahead == 'c') ADVANCE(213);
      END_STATE();
    case 219:
      if (lookahead == 'c') ADVANCE(494);
      END_STATE();
    case 220:
      if (lookahead == 'c') ADVANCE(771);
      if (lookahead == 'o') ADVANCE(724);
      if (lookahead == 'r') ADVANCE(380);
      END_STATE();
    case 221:
      if (lookahead == 'c') ADVANCE(145);
      END_STATE();
    case 222:
      if (lookahead == 'c') ADVANCE(399);
      END_STATE();
    case 223:
      if (lookahead == 'c') ADVANCE(383);
      END_STATE();
    case 224:
      if (lookahead == 'c') ADVANCE(401);
      END_STATE();
    case 225:
      if (lookahead == 'c') ADVANCE(521);
      END_STATE();
    case 226:
      if (lookahead == 'c') ADVANCE(739);
      END_STATE();
    case 227:
      if (lookahead == 'c') ADVANCE(165);
      END_STATE();
    case 228:
      if (lookahead == 'c') ADVANCE(366);
      END_STATE();
    case 229:
      if (lookahead == 'c') ADVANCE(823);
      END_STATE();
    case 230:
      if (lookahead == 'c') ADVANCE(825);
      END_STATE();
    case 231:
      if (lookahead == 'c') ADVANCE(828);
      END_STATE();
    case 232:
      if (lookahead == 'c') ADVANCE(477);
      END_STATE();
    case 233:
      if (lookahead == 'd') ADVANCE(1598);
      END_STATE();
    case 234:
      if (lookahead == 'd') ADVANCE(1715);
      END_STATE();
    case 235:
      if (lookahead == 'd') ADVANCE(1656);
      END_STATE();
    case 236:
      if (lookahead == 'd') ADVANCE(1617);
      END_STATE();
    case 237:
      if (lookahead == 'd') ADVANCE(1712);
      END_STATE();
    case 238:
      if (lookahead == 'd') ADVANCE(1658);
      END_STATE();
    case 239:
      if (lookahead == 'd') ADVANCE(1577);
      END_STATE();
    case 240:
      if (lookahead == 'd') ADVANCE(1579);
      END_STATE();
    case 241:
      if (lookahead == 'd') ADVANCE(1549);
      END_STATE();
    case 242:
      if (lookahead == 'd') ADVANCE(1642);
      END_STATE();
    case 243:
      if (lookahead == 'd') ADVANCE(1707);
      END_STATE();
    case 244:
      if (lookahead == 'd') ADVANCE(674);
      if (lookahead == 'j') ADVANCE(841);
      END_STATE();
    case 245:
      if (lookahead == 'd') ADVANCE(54);
      END_STATE();
    case 246:
      if (lookahead == 'd') ADVANCE(604);
      END_STATE();
    case 247:
      if (lookahead == 'd') ADVANCE(323);
      if (lookahead == 'e') ADVANCE(1602);
      if (lookahead == 'k') ADVANCE(559);
      if (lookahead == 'o') ADVANCE(1600);
      if (lookahead == 'p') ADVANCE(701);
      END_STATE();
    case 248:
      if (lookahead == 'd') ADVANCE(259);
      END_STATE();
    case 249:
      if (lookahead == 'd') ADVANCE(378);
      END_STATE();
    case 250:
      if (lookahead == 'd') ADVANCE(331);
      END_STATE();
    case 251:
      if (lookahead == 'd') ADVANCE(332);
      END_STATE();
    case 252:
      if (lookahead == 'd') ADVANCE(374);
      if (lookahead == 's') ADVANCE(350);
      END_STATE();
    case 253:
      if (lookahead == 'd') ADVANCE(335);
      END_STATE();
    case 254:
      if (lookahead == 'd') ADVANCE(310);
      END_STATE();
    case 255:
      if (lookahead == 'd') ADVANCE(342);
      END_STATE();
    case 256:
      if (lookahead == 'd') ADVANCE(342);
      if (lookahead == 'k') ADVANCE(585);
      if (lookahead == 'o') ADVANCE(681);
      END_STATE();
    case 257:
      if (lookahead == 'd') ADVANCE(443);
      END_STATE();
    case 258:
      if (lookahead == 'd') ADVANCE(437);
      END_STATE();
    case 259:
      if (lookahead == 'd') ADVANCE(708);
      END_STATE();
    case 260:
      if (lookahead == 'd') ADVANCE(461);
      END_STATE();
    case 261:
      if (lookahead == 'd') ADVANCE(709);
      END_STATE();
    case 262:
      if (lookahead == 'd') ADVANCE(710);
      END_STATE();
    case 263:
      if (lookahead == 'd') ADVANCE(712);
      END_STATE();
    case 264:
      if (lookahead == 'd') ADVANCE(261);
      END_STATE();
    case 265:
      if (lookahead == 'd') ADVANCE(262);
      END_STATE();
    case 266:
      if (lookahead == 'd') ADVANCE(263);
      END_STATE();
    case 267:
      if (lookahead == 'e') ADVANCE(1583);
      if (lookahead == 'i') ADVANCE(555);
      if (lookahead == 'n') ADVANCE(121);
      if (lookahead == 'o') ADVANCE(203);
      if (lookahead == 's') ADVANCE(849);
      if (lookahead == 'u') ADVANCE(493);
      END_STATE();
    case 268:
      if (lookahead == 'e') ADVANCE(119);
      END_STATE();
    case 269:
      if (lookahead == 'e') ADVANCE(1594);
      if (lookahead == 't') ADVANCE(1593);
      END_STATE();
    case 270:
      if (lookahead == 'e') ADVANCE(1596);
      if (lookahead == 't') ADVANCE(1595);
      END_STATE();
    case 271:
      if (lookahead == 'e') ADVANCE(1597);
      END_STATE();
    case 272:
      if (lookahead == 'e') ADVANCE(1585);
      if (lookahead == 't') ADVANCE(1584);
      END_STATE();
    case 273:
      if (lookahead == 'e') ADVANCE(1587);
      if (lookahead == 't') ADVANCE(1586);
      END_STATE();
    case 274:
      if (lookahead == 'e') ADVANCE(1589);
      if (lookahead == 't') ADVANCE(1588);
      END_STATE();
    case 275:
      if (lookahead == 'e') ADVANCE(1591);
      if (lookahead == 't') ADVANCE(1590);
      END_STATE();
    case 276:
      if (lookahead == 'e') ADVANCE(1602);
      if (lookahead == 'k') ADVANCE(581);
      if (lookahead == 'o') ADVANCE(1599);
      END_STATE();
    case 277:
      if (lookahead == 'e') ADVANCE(439);
      END_STATE();
    case 278:
      if (lookahead == 'e') ADVANCE(1575);
      END_STATE();
    case 279:
      if (lookahead == 'e') ADVANCE(1576);
      END_STATE();
    case 280:
      if (lookahead == 'e') ADVANCE(1618);
      END_STATE();
    case 281:
      if (lookahead == 'e') ADVANCE(1722);
      END_STATE();
    case 282:
      if (lookahead == 'e') ADVANCE(1565);
      END_STATE();
    case 283:
      if (lookahead == 'e') ADVANCE(1539);
      END_STATE();
    case 284:
      if (lookahead == 'e') ADVANCE(1644);
      END_STATE();
    case 285:
      if (lookahead == 'e') ADVANCE(1694);
      END_STATE();
    case 286:
      if (lookahead == 'e') ADVANCE(1645);
      END_STATE();
    case 287:
      if (lookahead == 'e') ADVANCE(1548);
      END_STATE();
    case 288:
      if (lookahead == 'e') ADVANCE(1508);
      END_STATE();
    case 289:
      if (lookahead == 'e') ADVANCE(1637);
      END_STATE();
    case 290:
      if (lookahead == 'e') ADVANCE(1626);
      END_STATE();
    case 291:
      if (lookahead == 'e') ADVANCE(1664);
      END_STATE();
    case 292:
      if (lookahead == 'e') ADVANCE(1666);
      END_STATE();
    case 293:
      if (lookahead == 'e') ADVANCE(1641);
      END_STATE();
    case 294:
      if (lookahead == 'e') ADVANCE(1636);
      END_STATE();
    case 295:
      if (lookahead == 'e') ADVANCE(1543);
      END_STATE();
    case 296:
      if (lookahead == 'e') ADVANCE(1571);
      END_STATE();
    case 297:
      if (lookahead == 'e') ADVANCE(1619);
      END_STATE();
    case 298:
      if (lookahead == 'e') ADVANCE(1569);
      END_STATE();
    case 299:
      if (lookahead == 'e') ADVANCE(1696);
      END_STATE();
    case 300:
      if (lookahead == 'e') ADVANCE(1567);
      END_STATE();
    case 301:
      if (lookahead == 'e') ADVANCE(1711);
      END_STATE();
    case 302:
      if (lookahead == 'e') ADVANCE(1639);
      END_STATE();
    case 303:
      if (lookahead == 'e') ADVANCE(1573);
      END_STATE();
    case 304:
      if (lookahead == 'e') ADVANCE(189);
      END_STATE();
    case 305:
      if (lookahead == 'e') ADVANCE(1582);
      if (lookahead == 'o') ADVANCE(578);
      END_STATE();
    case 306:
      if (lookahead == 'e') ADVANCE(113);
      END_STATE();
    case 307:
      if (lookahead == 'e') ADVANCE(663);
      if (lookahead == 'f') ADVANCE(404);
      if (lookahead == 'g') ADVANCE(269);
      if (lookahead == 'l') ADVANCE(270);
      if (lookahead == 'n') ADVANCE(1621);
      if (lookahead == 'r') ADVANCE(233);
      END_STATE();
    case 308:
      if (lookahead == 'e') ADVANCE(663);
      if (lookahead == 'g') ADVANCE(269);
      if (lookahead == 'l') ADVANCE(270);
      if (lookahead == 'n') ADVANCE(271);
      if (lookahead == 'r') ADVANCE(233);
      END_STATE();
    case 309:
      if (lookahead == 'e') ADVANCE(110);
      END_STATE();
    case 310:
      if (lookahead == 'e') ADVANCE(857);
      END_STATE();
    case 311:
      if (lookahead == 'e') ADVANCE(665);
      if (lookahead == 't') ADVANCE(608);
      if (lookahead == 'y') ADVANCE(562);
      END_STATE();
    case 312:
      if (lookahead == 'e') ADVANCE(664);
      if (lookahead == 'g') ADVANCE(274);
      if (lookahead == 'l') ADVANCE(275);
      if (lookahead == 'n') ADVANCE(276);
      END_STATE();
    case 313:
      if (lookahead == 'e') ADVANCE(84);
      END_STATE();
    case 314:
      if (lookahead == 'e') ADVANCE(412);
      END_STATE();
    case 315:
      if (lookahead == 'e') ADVANCE(95);
      END_STATE();
    case 316:
      if (lookahead == 'e') ADVANCE(426);
      END_STATE();
    case 317:
      if (lookahead == 'e') ADVANCE(400);
      END_STATE();
    case 318:
      if (lookahead == 'e') ADVANCE(648);
      END_STATE();
    case 319:
      if (lookahead == 'e') ADVANCE(245);
      END_STATE();
    case 320:
      if (lookahead == 'e') ADVANCE(530);
      END_STATE();
    case 321:
      if (lookahead == 'e') ADVANCE(682);
      if (lookahead == 'o') ADVANCE(1623);
      END_STATE();
    case 322:
      if (lookahead == 'e') ADVANCE(682);
      if (lookahead == 'o') ADVANCE(1623);
      if (lookahead == 'p') ADVANCE(703);
      if (lookahead == 'r') ADVANCE(436);
      END_STATE();
    case 323:
      if (lookahead == 'e') ADVANCE(387);
      END_STATE();
    case 324:
      if (lookahead == 'e') ADVANCE(156);
      END_STATE();
    case 325:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 326:
      if (lookahead == 'e') ADVANCE(666);
      END_STATE();
    case 327:
      if (lookahead == 'e') ADVANCE(238);
      END_STATE();
    case 328:
      if (lookahead == 'e') ADVANCE(679);
      END_STATE();
    case 329:
      if (lookahead == 'e') ADVANCE(257);
      END_STATE();
    case 330:
      if (lookahead == 'e') ADVANCE(229);
      END_STATE();
    case 331:
      if (lookahead == 'e') ADVANCE(394);
      END_STATE();
    case 332:
      if (lookahead == 'e') ADVANCE(388);
      END_STATE();
    case 333:
      if (lookahead == 'e') ADVANCE(777);
      END_STATE();
    case 334:
      if (lookahead == 'e') ADVANCE(239);
      END_STATE();
    case 335:
      if (lookahead == 'e') ADVANCE(389);
      END_STATE();
    case 336:
      if (lookahead == 'e') ADVANCE(479);
      END_STATE();
    case 337:
      if (lookahead == 'e') ADVANCE(390);
      END_STATE();
    case 338:
      if (lookahead == 'e') ADVANCE(131);
      END_STATE();
    case 339:
      if (lookahead == 'e') ADVANCE(240);
      END_STATE();
    case 340:
      if (lookahead == 'e') ADVANCE(667);
      END_STATE();
    case 341:
      if (lookahead == 'e') ADVANCE(241);
      END_STATE();
    case 342:
      if (lookahead == 'e') ADVANCE(391);
      END_STATE();
    case 343:
      if (lookahead == 'e') ADVANCE(242);
      END_STATE();
    case 344:
      if (lookahead == 'e') ADVANCE(567);
      END_STATE();
    case 345:
      if (lookahead == 'e') ADVANCE(567);
      if (lookahead == 'f') ADVANCE(684);
      END_STATE();
    case 346:
      if (lookahead == 'e') ADVANCE(43);
      END_STATE();
    case 347:
      if (lookahead == 'e') ADVANCE(668);
      END_STATE();
    case 348:
      if (lookahead == 'e') ADVANCE(669);
      END_STATE();
    case 349:
      if (lookahead == 'e') ADVANCE(670);
      END_STATE();
    case 350:
      if (lookahead == 'e') ADVANCE(794);
      END_STATE();
    case 351:
      if (lookahead == 'e') ADVANCE(785);
      END_STATE();
    case 352:
      if (lookahead == 'e') ADVANCE(516);
      END_STATE();
    case 353:
      if (lookahead == 'e') ADVANCE(215);
      END_STATE();
    case 354:
      if (lookahead == 'e') ADVANCE(586);
      END_STATE();
    case 355:
      if (lookahead == 'e') ADVANCE(787);
      END_STATE();
    case 356:
      if (lookahead == 'e') ADVANCE(572);
      END_STATE();
    case 357:
      if (lookahead == 'e') ADVANCE(788);
      END_STATE();
    case 358:
      if (lookahead == 'e') ADVANCE(573);
      END_STATE();
    case 359:
      if (lookahead == 'e') ADVANCE(789);
      END_STATE();
    case 360:
      if (lookahead == 'e') ADVANCE(551);
      END_STATE();
    case 361:
      if (lookahead == 'e') ADVANCE(552);
      END_STATE();
    case 362:
      if (lookahead == 'e') ADVANCE(557);
      END_STATE();
    case 363:
      if (lookahead == 'e') ADVANCE(533);
      END_STATE();
    case 364:
      if (lookahead == 'e') ADVANCE(797);
      END_STATE();
    case 365:
      if (lookahead == 'e') ADVANCE(733);
      END_STATE();
    case 366:
      if (lookahead == 'e') ADVANCE(654);
      END_STATE();
    case 367:
      if (lookahead == 'e') ADVANCE(134);
      END_STATE();
    case 368:
      if (lookahead == 'e') ADVANCE(536);
      END_STATE();
    case 369:
      if (lookahead == 'e') ADVANCE(744);
      END_STATE();
    case 370:
      if (lookahead == 'e') ADVANCE(802);
      END_STATE();
    case 371:
      if (lookahead == 'e') ADVANCE(745);
      END_STATE();
    case 372:
      if (lookahead == 'e') ADVANCE(747);
      END_STATE();
    case 373:
      if (lookahead == 'e') ADVANCE(695);
      END_STATE();
    case 374:
      if (lookahead == 'e') ADVANCE(746);
      END_STATE();
    case 375:
      if (lookahead == 'e') ADVANCE(699);
      END_STATE();
    case 376:
      if (lookahead == 'e') ADVANCE(96);
      END_STATE();
    case 377:
      if (lookahead == 'e') ADVANCE(702);
      END_STATE();
    case 378:
      if (lookahead == 'e') ADVANCE(707);
      END_STATE();
    case 379:
      if (lookahead == 'e') ADVANCE(858);
      END_STATE();
    case 380:
      if (lookahead == 'e') ADVANCE(59);
      END_STATE();
    case 381:
      if (lookahead == 'e') ADVANCE(230);
      END_STATE();
    case 382:
      if (lookahead == 'e') ADVANCE(769);
      END_STATE();
    case 383:
      if (lookahead == 'e') ADVANCE(166);
      END_STATE();
    case 384:
      if (lookahead == 'e') ADVANCE(67);
      END_STATE();
    case 385:
      if (lookahead == 'f') ADVANCE(1716);
      END_STATE();
    case 386:
      if (lookahead == 'f') ADVANCE(1674);
      END_STATE();
    case 387:
      if (lookahead == 'f') ADVANCE(1607);
      END_STATE();
    case 388:
      if (lookahead == 'f') ADVANCE(1533);
      END_STATE();
    case 389:
      if (lookahead == 'f') ADVANCE(1650);
      END_STATE();
    case 390:
      if (lookahead == 'f') ADVANCE(1496);
      END_STATE();
    case 391:
      if (lookahead == 'f') ADVANCE(1605);
      END_STATE();
    case 392:
      if (lookahead == 'f') ADVANCE(431);
      END_STATE();
    case 393:
      if (lookahead == 'f') ADVANCE(839);
      END_STATE();
    case 394:
      if (lookahead == 'f') ADVANCE(91);
      END_STATE();
    case 395:
      if (lookahead == 'f') ADVANCE(403);
      END_STATE();
    case 396:
      if (lookahead == 'f') ADVANCE(659);
      END_STATE();
    case 397:
      if (lookahead == 'f') ADVANCE(103);
      END_STATE();
    case 398:
      if (lookahead == 'f') ADVANCE(496);
      if (lookahead == 'i') ADVANCE(588);
      END_STATE();
    case 399:
      if (lookahead == 'f') ADVANCE(129);
      END_STATE();
    case 400:
      if (lookahead == 'f') ADVANCE(373);
      END_STATE();
    case 401:
      if (lookahead == 'f') ADVANCE(104);
      END_STATE();
    case 402:
      if (lookahead == 'f') ADVANCE(684);
      END_STATE();
    case 403:
      if (lookahead == 'f') ADVANCE(501);
      END_STATE();
    case 404:
      if (lookahead == 'f') ADVANCE(740);
      END_STATE();
    case 405:
      if (lookahead == 'f') ADVANCE(751);
      END_STATE();
    case 406:
      if (lookahead == 'f') ADVANCE(752);
      END_STATE();
    case 407:
      if (lookahead == 'f') ADVANCE(753);
      END_STATE();
    case 408:
      if (lookahead == 'f') ADVANCE(405);
      END_STATE();
    case 409:
      if (lookahead == 'f') ADVANCE(406);
      END_STATE();
    case 410:
      if (lookahead == 'f') ADVANCE(407);
      END_STATE();
    case 411:
      if (lookahead == 'g') ADVANCE(1700);
      END_STATE();
    case 412:
      if (lookahead == 'g') ADVANCE(82);
      END_STATE();
    case 413:
      if (lookahead == 'g') ADVANCE(52);
      END_STATE();
    case 414:
      if (lookahead == 'g') ADVANCE(272);
      if (lookahead == 'l') ADVANCE(273);
      if (lookahead == 't') ADVANCE(130);
      END_STATE();
    case 415:
      if (lookahead == 'g') ADVANCE(31);
      END_STATE();
    case 416:
      if (lookahead == 'g') ADVANCE(547);
      END_STATE();
    case 417:
      if (lookahead == 'g') ADVANCE(38);
      END_STATE();
    case 418:
      if (lookahead == 'g') ADVANCE(364);
      END_STATE();
    case 419:
      if (lookahead == 'g') ADVANCE(35);
      END_STATE();
    case 420:
      if (lookahead == 'g') ADVANCE(721);
      END_STATE();
    case 421:
      if (lookahead == 'g') ADVANCE(549);
      END_STATE();
    case 422:
      if (lookahead == 'g') ADVANCE(285);
      END_STATE();
    case 423:
      if (lookahead == 'g') ADVANCE(596);
      END_STATE();
    case 424:
      if (lookahead == 'g') ADVANCE(356);
      END_STATE();
    case 425:
      if (lookahead == 'g') ADVANCE(359);
      END_STATE();
    case 426:
      if (lookahead == 'g') ADVANCE(462);
      END_STATE();
    case 427:
      if (lookahead == 'h') ADVANCE(393);
      END_STATE();
    case 428:
      if (lookahead == 'h') ADVANCE(440);
      END_STATE();
    case 429:
      if (lookahead == 'i') ADVANCE(867);
      END_STATE();
    case 430:
      if (lookahead == 'i') ADVANCE(416);
      END_STATE();
    case 431:
      if (lookahead == 'i') ADVANCE(36);
      END_STATE();
    case 432:
      if (lookahead == 'i') ADVANCE(319);
      END_STATE();
    case 433:
      if (lookahead == 'i') ADVANCE(237);
      END_STATE();
    case 434:
      if (lookahead == 'i') ADVANCE(580);
      END_STATE();
    case 435:
      if (lookahead == 'i') ADVANCE(589);
      END_STATE();
    case 436:
      if (lookahead == 'i') ADVANCE(560);
      END_STATE();
    case 437:
      if (lookahead == 'i') ADVANCE(582);
      END_STATE();
    case 438:
      if (lookahead == 'i') ADVANCE(210);
      END_STATE();
    case 439:
      if (lookahead == 'i') ADVANCE(561);
      if (lookahead == 'o') ADVANCE(836);
      END_STATE();
    case 440:
      if (lookahead == 'i') ADVANCE(574);
      END_STATE();
    case 441:
      if (lookahead == 'i') ADVANCE(568);
      END_STATE();
    case 442:
      if (lookahead == 'i') ADVANCE(782);
      END_STATE();
    case 443:
      if (lookahead == 'i') ADVANCE(231);
      END_STATE();
    case 444:
      if (lookahead == 'i') ADVANCE(711);
      END_STATE();
    case 445:
      if (lookahead == 'i') ADVANCE(198);
      END_STATE();
    case 446:
      if (lookahead == 'i') ADVANCE(199);
      END_STATE();
    case 447:
      if (lookahead == 'i') ADVANCE(868);
      END_STATE();
    case 448:
      if (lookahead == 'i') ADVANCE(421);
      END_STATE();
    case 449:
      if (lookahead == 'i') ADVANCE(492);
      END_STATE();
    case 450:
      if (lookahead == 'i') ADVANCE(558);
      END_STATE();
    case 451:
      if (lookahead == 'i') ADVANCE(144);
      END_STATE();
    case 452:
      if (lookahead == 'i') ADVANCE(423);
      END_STATE();
    case 453:
      if (lookahead == 'i') ADVANCE(625);
      END_STATE();
    case 454:
      if (lookahead == 'i') ADVANCE(693);
      END_STATE();
    case 455:
      if (lookahead == 'i') ADVANCE(759);
      END_STATE();
    case 456:
      if (lookahead == 'i') ADVANCE(569);
      END_STATE();
    case 457:
      if (lookahead == 'i') ADVANCE(627);
      END_STATE();
    case 458:
      if (lookahead == 'i') ADVANCE(629);
      END_STATE();
    case 459:
      if (lookahead == 'i') ADVANCE(502);
      END_STATE();
    case 460:
      if (lookahead == 'i') ADVANCE(630);
      END_STATE();
    case 461:
      if (lookahead == 'i') ADVANCE(700);
      END_STATE();
    case 462:
      if (lookahead == 'i') ADVANCE(762);
      END_STATE();
    case 463:
      if (lookahead == 'i') ADVANCE(592);
      END_STATE();
    case 464:
      if (lookahead == 'i') ADVANCE(593);
      if (lookahead == 'l') ADVANCE(624);
      END_STATE();
    case 465:
      if (lookahead == 'i') ADVANCE(593);
      if (lookahead == 'l') ADVANCE(624);
      if (lookahead == 'u') ADVANCE(750);
      END_STATE();
    case 466:
      if (lookahead == 'i') ADVANCE(597);
      END_STATE();
    case 467:
      if (lookahead == 'j') ADVANCE(640);
      END_STATE();
    case 468:
      if (lookahead == 'k') ADVANCE(1634);
      END_STATE();
    case 469:
      if (lookahead == 'k') ADVANCE(1603);
      END_STATE();
    case 470:
      if (lookahead == 'k') ADVANCE(1541);
      END_STATE();
    case 471:
      if (lookahead == 'k') ADVANCE(69);
      END_STATE();
    case 472:
      if (lookahead == 'k') ADVANCE(64);
      END_STATE();
    case 473:
      if (lookahead == 'k') ADVANCE(348);
      END_STATE();
    case 474:
      if (lookahead == 'k') ADVANCE(360);
      END_STATE();
    case 475:
      if (lookahead == 'k') ADVANCE(361);
      END_STATE();
    case 476:
      if (lookahead == 'k') ADVANCE(133);
      END_STATE();
    case 477:
      if (lookahead == 'k') ADVANCE(66);
      END_STATE();
    case 478:
      if (lookahead == 'l') ADVANCE(1520);
      END_STATE();
    case 479:
      if (lookahead == 'l') ADVANCE(1646);
      END_STATE();
    case 480:
      if (lookahead == 'l') ADVANCE(1660);
      END_STATE();
    case 481:
      if (lookahead == 'l') ADVANCE(1516);
      END_STATE();
    case 482:
      if (lookahead == 'l') ADVANCE(1638);
      END_STATE();
    case 483:
      if (lookahead == 'l') ADVANCE(1633);
      END_STATE();
    case 484:
      if (lookahead == 'l') ADVANCE(1498);
      END_STATE();
    case 485:
      if (lookahead == 'l') ADVANCE(1500);
      END_STATE();
    case 486:
      if (lookahead == 'l') ADVANCE(234);
      END_STATE();
    case 487:
      if (lookahead == 'l') ADVANCE(863);
      END_STATE();
    case 488:
      if (lookahead == 'l') ADVANCE(385);
      END_STATE();
    case 489:
      if (lookahead == 'l') ADVANCE(30);
      END_STATE();
    case 490:
      if (lookahead == 'l') ADVANCE(489);
      END_STATE();
    case 491:
      if (lookahead == 'l') ADVANCE(438);
      END_STATE();
    case 492:
      if (lookahead == 'l') ADVANCE(511);
      END_STATE();
    case 493:
      if (lookahead == 'l') ADVANCE(478);
      if (lookahead == 's') ADVANCE(850);
      if (lookahead == 'w') ADVANCE(1686);
      END_STATE();
    case 494:
      if (lookahead == 'l') ADVANCE(607);
      END_STATE();
    case 495:
      if (lookahead == 'l') ADVANCE(281);
      END_STATE();
    case 496:
      if (lookahead == 'l') ADVANCE(122);
      END_STATE();
    case 497:
      if (lookahead == 'l') ADVANCE(41);
      END_STATE();
    case 498:
      if (lookahead == 'l') ADVANCE(513);
      END_STATE();
    case 499:
      if (lookahead == 'l') ADVANCE(283);
      END_STATE();
    case 500:
      if (lookahead == 'l') ADVANCE(497);
      END_STATE();
    case 501:
      if (lookahead == 'l') ADVANCE(368);
      END_STATE();
    case 502:
      if (lookahead == 'l') ADVANCE(289);
      END_STATE();
    case 503:
      if (lookahead == 'l') ADVANCE(292);
      END_STATE();
    case 504:
      if (lookahead == 'l') ADVANCE(294);
      END_STATE();
    case 505:
      if (lookahead == 'l') ADVANCE(299);
      END_STATE();
    case 506:
      if (lookahead == 'l') ADVANCE(302);
      END_STATE();
    case 507:
      if (lookahead == 'l') ADVANCE(618);
      END_STATE();
    case 508:
      if (lookahead == 'l') ADVANCE(434);
      END_STATE();
    case 509:
      if (lookahead == 'l') ADVANCE(434);
      if (lookahead == 't') ADVANCE(322);
      if (lookahead == 'v') ADVANCE(127);
      END_STATE();
    case 510:
      if (lookahead == 'l') ADVANCE(448);
      END_STATE();
    case 511:
      if (lookahead == 'l') ADVANCE(327);
      END_STATE();
    case 512:
      if (lookahead == 'l') ADVANCE(837);
      END_STATE();
    case 513:
      if (lookahead == 'l') ADVANCE(46);
      END_STATE();
    case 514:
      if (lookahead == 'l') ADVANCE(738);
      END_STATE();
    case 515:
      if (lookahead == 'l') ADVANCE(128);
      END_STATE();
    case 516:
      if (lookahead == 'l') ADVANCE(324);
      END_STATE();
    case 517:
      if (lookahead == 'l') ADVANCE(626);
      END_STATE();
    case 518:
      if (lookahead == 'l') ADVANCE(628);
      END_STATE();
    case 519:
      if (lookahead == 'l') ADVANCE(637);
      END_STATE();
    case 520:
      if (lookahead == 'l') ADVANCE(517);
      END_STATE();
    case 521:
      if (lookahead == 'l') ADVANCE(370);
      END_STATE();
    case 522:
      if (lookahead == 'l') ADVANCE(643);
      END_STATE();
    case 523:
      if (lookahead == 'm') ADVANCE(647);
      if (lookahead == 'n') ADVANCE(509);
      if (lookahead == 'r') ADVANCE(47);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1457);
      END_STATE();
    case 524:
      if (lookahead == 'm') ADVANCE(647);
      if (lookahead == 'n') ADVANCE(790);
      END_STATE();
    case 525:
      if (lookahead == 'm') ADVANCE(1622);
      END_STATE();
    case 526:
      if (lookahead == 'm') ADVANCE(83);
      END_STATE();
    case 527:
      if (lookahead == 'm') ADVANCE(1632);
      END_STATE();
    case 528:
      if (lookahead == 'm') ADVANCE(675);
      END_STATE();
    case 529:
      if (lookahead == 'm') ADVANCE(175);
      END_STATE();
    case 530:
      if (lookahead == 'm') ADVANCE(179);
      END_STATE();
    case 531:
      if (lookahead == 'm') ADVANCE(93);
      END_STATE();
    case 532:
      if (lookahead == 'm') ADVANCE(657);
      END_STATE();
    case 533:
      if (lookahead == 'm') ADVANCE(650);
      END_STATE();
    case 534:
      if (lookahead == 'm') ADVANCE(313);
      END_STATE();
    case 535:
      if (lookahead == 'm') ADVANCE(160);
      END_STATE();
    case 536:
      if (lookahead == 'm') ADVANCE(136);
      END_STATE();
    case 537:
      if (lookahead == 'm') ADVANCE(37);
      END_STATE();
    case 538:
      if (lookahead == 'm') ADVANCE(325);
      END_STATE();
    case 539:
      if (lookahead == 'm') ADVANCE(139);
      END_STATE();
    case 540:
      if (lookahead == 'm') ADVANCE(346);
      END_STATE();
    case 541:
      if (lookahead == 'm') ADVANCE(181);
      END_STATE();
    case 542:
      if (lookahead == 'm') ADVANCE(183);
      END_STATE();
    case 543:
      if (lookahead == 'm') ADVANCE(184);
      END_STATE();
    case 544:
      if (lookahead == 'n') ADVANCE(1682);
      END_STATE();
    case 545:
      if (lookahead == 'n') ADVANCE(728);
      END_STATE();
    case 546:
      if (lookahead == 'n') ADVANCE(1672);
      END_STATE();
    case 547:
      if (lookahead == 'n') ADVANCE(1624);
      END_STATE();
    case 548:
      if (lookahead == 'n') ADVANCE(1714);
      END_STATE();
    case 549:
      if (lookahead == 'n') ADVANCE(1625);
      END_STATE();
    case 550:
      if (lookahead == 'n') ADVANCE(1512);
      END_STATE();
    case 551:
      if (lookahead == 'n') ADVANCE(1710);
      END_STATE();
    case 552:
      if (lookahead == 'n') ADVANCE(1706);
      END_STATE();
    case 553:
      if (lookahead == 'n') ADVANCE(1620);
      END_STATE();
    case 554:
      if (lookahead == 'n') ADVANCE(256);
      END_STATE();
    case 555:
      if (lookahead == 'n') ADVANCE(386);
      END_STATE();
    case 556:
      if (lookahead == 'n') ADVANCE(258);
      END_STATE();
    case 557:
      if (lookahead == 'n') ADVANCE(125);
      END_STATE();
    case 558:
      if (lookahead == 'n') ADVANCE(246);
      END_STATE();
    case 559:
      if (lookahead == 'n') ADVANCE(602);
      END_STATE();
    case 560:
      if (lookahead == 'n') ADVANCE(758);
      END_STATE();
    case 561:
      if (lookahead == 'n') ADVANCE(716);
      END_STATE();
    case 562:
      if (lookahead == 'n') ADVANCE(207);
      END_STATE();
    case 563:
      if (lookahead == 'n') ADVANCE(34);
      END_STATE();
    case 564:
      if (lookahead == 'n') ADVANCE(717);
      END_STATE();
    case 565:
      if (lookahead == 'n') ADVANCE(718);
      END_STATE();
    case 566:
      if (lookahead == 'n') ADVANCE(225);
      END_STATE();
    case 567:
      if (lookahead == 'n') ADVANCE(798);
      END_STATE();
    case 568:
      if (lookahead == 'n') ADVANCE(781);
      END_STATE();
    case 569:
      if (lookahead == 'n') ADVANCE(260);
      END_STATE();
    case 570:
      if (lookahead == 'n') ADVANCE(783);
      END_STATE();
    case 571:
      if (lookahead == 'n') ADVANCE(508);
      if (lookahead == 'r') ADVANCE(47);
      END_STATE();
    case 572:
      if (lookahead == 'n') ADVANCE(786);
      END_STATE();
    case 573:
      if (lookahead == 'n') ADVANCE(803);
      END_STATE();
    case 574:
      if (lookahead == 'n') ADVANCE(384);
      END_STATE();
    case 575:
      if (lookahead == 'n') ADVANCE(634);
      END_STATE();
    case 576:
      if (lookahead == 'n') ADVANCE(840);
      END_STATE();
    case 577:
      if (lookahead == 'n') ADVANCE(848);
      END_STATE();
    case 578:
      if (lookahead == 'n') ADVANCE(49);
      END_STATE();
    case 579:
      if (lookahead == 'n') ADVANCE(843);
      END_STATE();
    case 580:
      if (lookahead == 'n') ADVANCE(338);
      END_STATE();
    case 581:
      if (lookahead == 'n') ADVANCE(631);
      END_STATE();
    case 582:
      if (lookahead == 'n') ADVANCE(417);
      END_STATE();
    case 583:
      if (lookahead == 'n') ADVANCE(800);
      END_STATE();
    case 584:
      if (lookahead == 'n') ADVANCE(135);
      END_STATE();
    case 585:
      if (lookahead == 'n') ADVANCE(635);
      END_STATE();
    case 586:
      if (lookahead == 'n') ADVANCE(223);
      END_STATE();
    case 587:
      if (lookahead == 'n') ADVANCE(446);
      END_STATE();
    case 588:
      if (lookahead == 'n') ADVANCE(254);
      END_STATE();
    case 589:
      if (lookahead == 'n') ADVANCE(742);
      END_STATE();
    case 590:
      if (lookahead == 'n') ADVANCE(341);
      END_STATE();
    case 591:
      if (lookahead == 'n') ADVANCE(255);
      END_STATE();
    case 592:
      if (lookahead == 'n') ADVANCE(755);
      END_STATE();
    case 593:
      if (lookahead == 'n') ADVANCE(760);
      END_STATE();
    case 594:
      if (lookahead == 'n') ADVANCE(727);
      END_STATE();
    case 595:
      if (lookahead == 'n') ADVANCE(51);
      END_STATE();
    case 596:
      if (lookahead == 'n') ADVANCE(98);
      END_STATE();
    case 597:
      if (lookahead == 'n') ADVANCE(772);
      END_STATE();
    case 598:
      if (lookahead == 'n') ADVANCE(65);
      END_STATE();
    case 599:
      if (lookahead == 'o') ADVANCE(486);
      END_STATE();
    case 600:
      if (lookahead == 'o') ADVANCE(486);
      if (lookahead == 'u') ADVANCE(723);
      END_STATE();
    case 601:
      if (lookahead == 'o') ADVANCE(773);
      END_STATE();
    case 602:
      if (lookahead == 'o') ADVANCE(852);
      END_STATE();
    case 603:
      if (lookahead == 'o') ADVANCE(120);
      END_STATE();
    case 604:
      if (lookahead == 'o') ADVANCE(851);
      END_STATE();
    case 605:
      if (lookahead == 'o') ADVANCE(123);
      END_STATE();
    case 606:
      if (lookahead == 'o') ADVANCE(525);
      END_STATE();
    case 607:
      if (lookahead == 'o') ADVANCE(182);
      END_STATE();
    case 608:
      if (lookahead == 'o') ADVANCE(686);
      END_STATE();
    case 609:
      if (lookahead == 'o') ADVANCE(860);
      END_STATE();
    case 610:
      if (lookahead == 'o') ADVANCE(515);
      END_STATE();
    case 611:
      if (lookahead == 'o') ADVANCE(515);
      if (lookahead == 's') ADVANCE(208);
      END_STATE();
    case 612:
      if (lookahead == 'o') ADVANCE(196);
      END_STATE();
    case 613:
      if (lookahead == 'o') ADVANCE(526);
      END_STATE();
    case 614:
      if (lookahead == 'o') ADVANCE(527);
      END_STATE();
    case 615:
      if (lookahead == 'o') ADVANCE(577);
      END_STATE();
    case 616:
      if (lookahead == 'o') ADVANCE(408);
      END_STATE();
    case 617:
      if (lookahead == 'o') ADVANCE(481);
      END_STATE();
    case 618:
      if (lookahead == 'o') ADVANCE(202);
      END_STATE();
    case 619:
      if (lookahead == 'o') ADVANCE(483);
      END_STATE();
    case 620:
      if (lookahead == 'o') ADVANCE(197);
      END_STATE();
    case 621:
      if (lookahead == 'o') ADVANCE(587);
      END_STATE();
    case 622:
      if (lookahead == 'o') ADVANCE(484);
      END_STATE();
    case 623:
      if (lookahead == 'o') ADVANCE(485);
      END_STATE();
    case 624:
      if (lookahead == 'o') ADVANCE(227);
      END_STATE();
    case 625:
      if (lookahead == 'o') ADVANCE(548);
      END_STATE();
    case 626:
      if (lookahead == 'o') ADVANCE(214);
      END_STATE();
    case 627:
      if (lookahead == 'o') ADVANCE(564);
      END_STATE();
    case 628:
      if (lookahead == 'o') ADVANCE(206);
      END_STATE();
    case 629:
      if (lookahead == 'o') ADVANCE(565);
      END_STATE();
    case 630:
      if (lookahead == 'o') ADVANCE(550);
      END_STATE();
    case 631:
      if (lookahead == 'o') ADVANCE(853);
      END_STATE();
    case 632:
      if (lookahead == 'o') ADVANCE(687);
      END_STATE();
    case 633:
      if (lookahead == 'o') ADVANCE(619);
      END_STATE();
    case 634:
      if (lookahead == 'o') ADVANCE(815);
      END_STATE();
    case 635:
      if (lookahead == 'o') ADVANCE(854);
      END_STATE();
    case 636:
      if (lookahead == 'o') ADVANCE(706);
      END_STATE();
    case 637:
      if (lookahead == 'o') ADVANCE(132);
      END_STATE();
    case 638:
      if (lookahead == 'o') ADVANCE(694);
      END_STATE();
    case 639:
      if (lookahead == 'o') ADVANCE(656);
      END_STATE();
    case 640:
      if (lookahead == 'o') ADVANCE(441);
      END_STATE();
    case 641:
      if (lookahead == 'o') ADVANCE(409);
      if (lookahead == 'r') ADVANCE(316);
      END_STATE();
    case 642:
      if (lookahead == 'o') ADVANCE(410);
      END_STATE();
    case 643:
      if (lookahead == 'o') ADVANCE(232);
      END_STATE();
    case 644:
      if (lookahead == 'p') ADVANCE(1678);
      END_STATE();
    case 645:
      if (lookahead == 'p') ADVANCE(1668);
      END_STATE();
    case 646:
      if (lookahead == 'p') ADVANCE(39);
      END_STATE();
    case 647:
      if (lookahead == 'p') ADVANCE(491);
      END_STATE();
    case 648:
      if (lookahead == 'p') ADVANCE(795);
      END_STATE();
    case 649:
      if (lookahead == 'p') ADVANCE(149);
      END_STATE();
    case 650:
      if (lookahead == 'p') ADVANCE(636);
      END_STATE();
    case 651:
      if (lookahead == 'p') ADVANCE(379);
      END_STATE();
    case 652:
      if (lookahead == 'p') ADVANCE(633);
      END_STATE();
    case 653:
      if (lookahead == 'p') ADVANCE(282);
      END_STATE();
    case 654:
      if (lookahead == 'p') ADVANCE(784);
      END_STATE();
    case 655:
      if (lookahead == 'p') ADVANCE(288);
      END_STATE();
    case 656:
      if (lookahead == 'p') ADVANCE(293);
      END_STATE();
    case 657:
      if (lookahead == 'p') ADVANCE(48);
      END_STATE();
    case 658:
      if (lookahead == 'p') ADVANCE(140);
      END_STATE();
    case 659:
      if (lookahead == 'p') ADVANCE(75);
      END_STATE();
    case 660:
      if (lookahead == 'p') ADVANCE(155);
      END_STATE();
    case 661:
      if (lookahead == 'q') ADVANCE(1581);
      END_STATE();
    case 662:
      if (lookahead == 'q') ADVANCE(92);
      END_STATE();
    case 663:
      if (lookahead == 'q') ADVANCE(1592);
      END_STATE();
    case 664:
      if (lookahead == 'q') ADVANCE(1601);
      END_STATE();
    case 665:
      if (lookahead == 'q') ADVANCE(89);
      END_STATE();
    case 666:
      if (lookahead == 'r') ADVANCE(1563);
      END_STATE();
    case 667:
      if (lookahead == 'r') ADVANCE(1662);
      END_STATE();
    case 668:
      if (lookahead == 'r') ADVANCE(1545);
      END_STATE();
    case 669:
      if (lookahead == 'r') ADVANCE(1502);
      END_STATE();
    case 670:
      if (lookahead == 'r') ADVANCE(1510);
      END_STATE();
    case 671:
      if (lookahead == 'r') ADVANCE(835);
      END_STATE();
    case 672:
      if (lookahead == 'r') ADVANCE(418);
      END_STATE();
    case 673:
      if (lookahead == 'r') ADVANCE(859);
      END_STATE();
    case 674:
      if (lookahead == 'r') ADVANCE(732);
      END_STATE();
    case 675:
      if (lookahead == 'r') ADVANCE(102);
      END_STATE();
    case 676:
      if (lookahead == 'r') ADVANCE(861);
      END_STATE();
    case 677:
      if (lookahead == 'r') ADVANCE(473);
      END_STATE();
    case 678:
      if (lookahead == 'r') ADVANCE(487);
      END_STATE();
    case 679:
      if (lookahead == 'r') ADVANCE(97);
      END_STATE();
    case 680:
      if (lookahead == 'r') ADVANCE(451);
      END_STATE();
    case 681:
      if (lookahead == 'r') ADVANCE(249);
      END_STATE();
    case 682:
      if (lookahead == 'r') ADVANCE(584);
      END_STATE();
    case 683:
      if (lookahead == 'r') ADVANCE(56);
      END_STATE();
    case 684:
      if (lookahead == 'r') ADVANCE(161);
      END_STATE();
    case 685:
      if (lookahead == 'r') ADVANCE(609);
      END_STATE();
    case 686:
      if (lookahead == 'r') ADVANCE(280);
      END_STATE();
    case 687:
      if (lookahead == 'r') ADVANCE(719);
      END_STATE();
    case 688:
      if (lookahead == 'r') ADVANCE(146);
      END_STATE();
    case 689:
      if (lookahead == 'r') ADVANCE(61);
      END_STATE();
    case 690:
      if (lookahead == 'r') ADVANCE(606);
      END_STATE();
    case 691:
      if (lookahead == 'r') ADVANCE(336);
      END_STATE();
    case 692:
      if (lookahead == 'r') ADVANCE(44);
      END_STATE();
    case 693:
      if (lookahead == 'r') ADVANCE(284);
      END_STATE();
    case 694:
      if (lookahead == 'r') ADVANCE(287);
      END_STATE();
    case 695:
      if (lookahead == 'r') ADVANCE(354);
      END_STATE();
    case 696:
      if (lookahead == 'r') ADVANCE(337);
      END_STATE();
    case 697:
      if (lookahead == 'r') ADVANCE(138);
      END_STATE();
    case 698:
      if (lookahead == 'r') ADVANCE(57);
      END_STATE();
    case 699:
      if (lookahead == 'r') ADVANCE(422);
      END_STATE();
    case 700:
      if (lookahead == 'r') ADVANCE(353);
      END_STATE();
    case 701:
      if (lookahead == 'r') ADVANCE(329);
      END_STATE();
    case 702:
      if (lookahead == 'r') ADVANCE(424);
      END_STATE();
    case 703:
      if (lookahead == 'r') ADVANCE(334);
      END_STATE();
    case 704:
      if (lookahead == 'r') ADVANCE(425);
      END_STATE();
    case 705:
      if (lookahead == 'r') ADVANCE(339);
      END_STATE();
    case 706:
      if (lookahead == 'r') ADVANCE(143);
      END_STATE();
    case 707:
      if (lookahead == 'r') ADVANCE(343);
      END_STATE();
    case 708:
      if (lookahead == 'r') ADVANCE(369);
      END_STATE();
    case 709:
      if (lookahead == 'r') ADVANCE(371);
      END_STATE();
    case 710:
      if (lookahead == 'r') ADVANCE(372);
      END_STATE();
    case 711:
      if (lookahead == 'r') ADVANCE(58);
      END_STATE();
    case 712:
      if (lookahead == 'r') ADVANCE(382);
      END_STATE();
    case 713:
      if (lookahead == 'r') ADVANCE(62);
      END_STATE();
    case 714:
      if (lookahead == 's') ADVANCE(467);
      END_STATE();
    case 715:
      if (lookahead == 's') ADVANCE(862);
      END_STATE();
    case 716:
      if (lookahead == 's') ADVANCE(1493);
      END_STATE();
    case 717:
      if (lookahead == 's') ADVANCE(1713);
      END_STATE();
    case 718:
      if (lookahead == 's') ADVANCE(1504);
      END_STATE();
    case 719:
      if (lookahead == 's') ADVANCE(1491);
      END_STATE();
    case 720:
      if (lookahead == 's') ADVANCE(1613);
      END_STATE();
    case 721:
      if (lookahead == 's') ADVANCE(1534);
      END_STATE();
    case 722:
      if (lookahead == 's') ADVANCE(1627);
      END_STATE();
    case 723:
      if (lookahead == 's') ADVANCE(792);
      END_STATE();
    case 724:
      if (lookahead == 's') ADVANCE(830);
      END_STATE();
    case 725:
      if (lookahead == 's') ADVANCE(469);
      END_STATE();
    case 726:
      if (lookahead == 's') ADVANCE(367);
      END_STATE();
    case 727:
      if (lookahead == 's') ADVANCE(796);
      END_STATE();
    case 728:
      if (lookahead == 's') ADVANCE(796);
      if (lookahead == 't') ADVANCE(697);
      END_STATE();
    case 729:
      if (lookahead == 's') ADVANCE(470);
      END_STATE();
    case 730:
      if (lookahead == 's') ADVANCE(756);
      END_STATE();
    case 731:
      if (lookahead == 's') ADVANCE(208);
      END_STATE();
    case 732:
      if (lookahead == 's') ADVANCE(649);
      END_STATE();
    case 733:
      if (lookahead == 's') ADVANCE(737);
      END_STATE();
    case 734:
      if (lookahead == 's') ADVANCE(814);
      END_STATE();
    case 735:
      if (lookahead == 's') ADVANCE(537);
      END_STATE();
    case 736:
      if (lookahead == 's') ADVANCE(429);
      END_STATE();
    case 737:
      if (lookahead == 's') ADVANCE(632);
      END_STATE();
    case 738:
      if (lookahead == 's') ADVANCE(279);
      END_STATE();
    case 739:
      if (lookahead == 's') ADVANCE(779);
      END_STATE();
    case 740:
      if (lookahead == 's') ADVANCE(333);
      END_STATE();
    case 741:
      if (lookahead == 's') ADVANCE(211);
      END_STATE();
    case 742:
      if (lookahead == 's') ADVANCE(799);
      END_STATE();
    case 743:
      if (lookahead == 's') ADVANCE(150);
      END_STATE();
    case 744:
      if (lookahead == 's') ADVANCE(720);
      END_STATE();
    case 745:
      if (lookahead == 's') ADVANCE(722);
      END_STATE();
    case 746:
      if (lookahead == 's') ADVANCE(801);
      END_STATE();
    case 747:
      if (lookahead == 's') ADVANCE(761);
      END_STATE();
    case 748:
      if (lookahead == 's') ADVANCE(820);
      END_STATE();
    case 749:
      if (lookahead == 's') ADVANCE(286);
      END_STATE();
    case 750:
      if (lookahead == 's') ADVANCE(291);
      END_STATE();
    case 751:
      if (lookahead == 's') ADVANCE(351);
      END_STATE();
    case 752:
      if (lookahead == 's') ADVANCE(355);
      END_STATE();
    case 753:
      if (lookahead == 's') ADVANCE(357);
      END_STATE();
    case 754:
      if (lookahead == 's') ADVANCE(447);
      END_STATE();
    case 755:
      if (lookahead == 's') ADVANCE(817);
      END_STATE();
    case 756:
      if (lookahead == 's') ADVANCE(620);
      END_STATE();
    case 757:
      if (lookahead == 's') ADVANCE(452);
      END_STATE();
    case 758:
      if (lookahead == 's') ADVANCE(445);
      END_STATE();
    case 759:
      if (lookahead == 's') ADVANCE(808);
      END_STATE();
    case 760:
      if (lookahead == 's') ADVANCE(818);
      END_STATE();
    case 761:
      if (lookahead == 's') ADVANCE(53);
      END_STATE();
    case 762:
      if (lookahead == 's') ADVANCE(811);
      END_STATE();
    case 763:
      if (lookahead == 's') ADVANCE(816);
      END_STATE();
    case 764:
      if (lookahead == 's') ADVANCE(821);
      END_STATE();
    case 765:
      if (lookahead == 's') ADVANCE(60);
      END_STATE();
    case 766:
      if (lookahead == 's') ADVANCE(822);
      END_STATE();
    case 767:
      if (lookahead == 's') ADVANCE(865);
      END_STATE();
    case 768:
      if (lookahead == 's') ADVANCE(660);
      END_STATE();
    case 769:
      if (lookahead == 's') ADVANCE(765);
      END_STATE();
    case 770:
      if (lookahead == 's') ADVANCE(866);
      END_STATE();
    case 771:
      if (lookahead == 's') ADVANCE(381);
      END_STATE();
    case 772:
      if (lookahead == 's') ADVANCE(829);
      END_STATE();
    case 773:
      if (lookahead == 't') ADVANCE(1635);
      END_STATE();
    case 774:
      if (lookahead == 't') ADVANCE(1690);
      END_STATE();
    case 775:
      if (lookahead == 't') ADVANCE(1721);
      END_STATE();
    case 776:
      if (lookahead == 't') ADVANCE(1718);
      END_STATE();
    case 777:
      if (lookahead == 't') ADVANCE(1551);
      END_STATE();
    case 778:
      if (lookahead == 't') ADVANCE(1609);
      END_STATE();
    case 779:
      if (lookahead == 't') ADVANCE(1647);
      END_STATE();
    case 780:
      if (lookahead == 't') ADVANCE(1680);
      END_STATE();
    case 781:
      if (lookahead == 't') ADVANCE(1702);
      END_STATE();
    case 782:
      if (lookahead == 't') ADVANCE(1649);
      END_STATE();
    case 783:
      if (lookahead == 't') ADVANCE(1640);
      END_STATE();
    case 784:
      if (lookahead == 't') ADVANCE(1692);
      END_STATE();
    case 785:
      if (lookahead == 't') ADVANCE(1553);
      END_STATE();
    case 786:
      if (lookahead == 't') ADVANCE(1698);
      END_STATE();
    case 787:
      if (lookahead == 't') ADVANCE(1557);
      END_STATE();
    case 788:
      if (lookahead == 't') ADVANCE(1559);
      END_STATE();
    case 789:
      if (lookahead == 't') ADVANCE(1708);
      END_STATE();
    case 790:
      if (lookahead == 't') ADVANCE(321);
      END_STATE();
    case 791:
      if (lookahead == 't') ADVANCE(864);
      END_STATE();
    case 792:
      if (lookahead == 't') ADVANCE(613);
      END_STATE();
    case 793:
      if (lookahead == 't') ADVANCE(638);
      END_STATE();
    case 794:
      if (lookahead == 't') ADVANCE(834);
      END_STATE();
    case 795:
      if (lookahead == 't') ADVANCE(453);
      END_STATE();
    case 796:
      if (lookahead == 't') ADVANCE(142);
      END_STATE();
    case 797:
      if (lookahead == 't') ADVANCE(33);
      END_STATE();
    case 798:
      if (lookahead == 't') ADVANCE(673);
      END_STATE();
    case 799:
      if (lookahead == 't') ADVANCE(683);
      END_STATE();
    case 800:
      if (lookahead == 't') ADVANCE(50);
      END_STATE();
    case 801:
      if (lookahead == 't') ADVANCE(685);
      END_STATE();
    case 802:
      if (lookahead == 't') ADVANCE(45);
      END_STATE();
    case 803:
      if (lookahead == 't') ADVANCE(676);
      END_STATE();
    case 804:
      if (lookahead == 't') ADVANCE(315);
      END_STATE();
    case 805:
      if (lookahead == 't') ADVANCE(147);
      END_STATE();
    case 806:
      if (lookahead == 't') ADVANCE(363);
      END_STATE();
    case 807:
      if (lookahead == 't') ADVANCE(164);
      END_STATE();
    case 808:
      if (lookahead == 't') ADVANCE(326);
      END_STATE();
    case 809:
      if (lookahead == 't') ADVANCE(298);
      END_STATE();
    case 810:
      if (lookahead == 't') ADVANCE(300);
      END_STATE();
    case 811:
      if (lookahead == 't') ADVANCE(347);
      END_STATE();
    case 812:
      if (lookahead == 't') ADVANCE(303);
      END_STATE();
    case 813:
      if (lookahead == 't') ADVANCE(459);
      END_STATE();
    case 814:
      if (lookahead == 't') ADVANCE(94);
      END_STATE();
    case 815:
      if (lookahead == 't') ADVANCE(621);
      END_STATE();
    case 816:
      if (lookahead == 't') ADVANCE(614);
      END_STATE();
    case 817:
      if (lookahead == 't') ADVANCE(689);
      END_STATE();
    case 818:
      if (lookahead == 't') ADVANCE(692);
      END_STATE();
    case 819:
      if (lookahead == 't') ADVANCE(55);
      END_STATE();
    case 820:
      if (lookahead == 't') ADVANCE(154);
      END_STATE();
    case 821:
      if (lookahead == 't') ADVANCE(158);
      END_STATE();
    case 822:
      if (lookahead == 't') ADVANCE(159);
      END_STATE();
    case 823:
      if (lookahead == 't') ADVANCE(457);
      END_STATE();
    case 824:
      if (lookahead == 't') ADVANCE(152);
      END_STATE();
    case 825:
      if (lookahead == 't') ADVANCE(458);
      END_STATE();
    case 826:
      if (lookahead == 't') ADVANCE(460);
      END_STATE();
    case 827:
      if (lookahead == 't') ADVANCE(162);
      END_STATE();
    case 828:
      if (lookahead == 't') ADVANCE(163);
      END_STATE();
    case 829:
      if (lookahead == 't') ADVANCE(713);
      END_STATE();
    case 830:
      if (lookahead == 't') ADVANCE(63);
      END_STATE();
    case 831:
      if (lookahead == 'u') ADVANCE(532);
      END_STATE();
    case 832:
      if (lookahead == 'u') ADVANCE(176);
      END_STATE();
    case 833:
      if (lookahead == 'u') ADVANCE(395);
      END_STATE();
    case 834:
      if (lookahead == 'u') ADVANCE(645);
      END_STATE();
    case 835:
      if (lookahead == 'u') ADVANCE(278);
      END_STATE();
    case 836:
      if (lookahead == 'u') ADVANCE(778);
      END_STATE();
    case 837:
      if (lookahead == 'u') ADVANCE(295);
      END_STATE();
    case 838:
      if (lookahead == 'u') ADVANCE(415);
      END_STATE();
    case 839:
      if (lookahead == 'u') ADVANCE(566);
      END_STATE();
    case 840:
      if (lookahead == 'u') ADVANCE(541);
      END_STATE();
    case 841:
      if (lookahead == 'u') ADVANCE(734);
      END_STATE();
    case 842:
      if (lookahead == 'u') ADVANCE(419);
      END_STATE();
    case 843:
      if (lookahead == 'v') ADVANCE(127);
      END_STATE();
    case 844:
      if (lookahead == 'v') ADVANCE(531);
      END_STATE();
    case 845:
      if (lookahead == 'v') ADVANCE(277);
      END_STATE();
    case 846:
      if (lookahead == 'v') ADVANCE(296);
      END_STATE();
    case 847:
      if (lookahead == 'v') ADVANCE(137);
      END_STATE();
    case 848:
      if (lookahead == 'v') ADVANCE(377);
      END_STATE();
    case 849:
      if (lookahead == 'w') ADVANCE(1688);
      if (lookahead == 'z') ADVANCE(1676);
      END_STATE();
    case 850:
      if (lookahead == 'w') ADVANCE(1704);
      END_STATE();
    case 851:
      if (lookahead == 'w') ADVANCE(88);
      END_STATE();
    case 852:
      if (lookahead == 'w') ADVANCE(563);
      END_STATE();
    case 853:
      if (lookahead == 'w') ADVANCE(598);
      END_STATE();
    case 854:
      if (lookahead == 'w') ADVANCE(595);
      END_STATE();
    case 855:
      if (lookahead == 'x') ADVANCE(870);
      END_STATE();
    case 856:
      if (lookahead == 'x') ADVANCE(204);
      END_STATE();
    case 857:
      if (lookahead == 'x') ADVANCE(1611);
      END_STATE();
    case 858:
      if (lookahead == 'x') ADVANCE(228);
      END_STATE();
    case 859:
      if (lookahead == 'y') ADVANCE(1631);
      END_STATE();
    case 860:
      if (lookahead == 'y') ADVANCE(1670);
      END_STATE();
    case 861:
      if (lookahead == 'y') ADVANCE(1709);
      END_STATE();
    case 862:
      if (lookahead == 'y') ADVANCE(529);
      END_STATE();
    case 863:
      if (lookahead == 'y') ADVANCE(42);
      END_STATE();
    case 864:
      if (lookahead == 'y') ADVANCE(655);
      END_STATE();
    case 865:
      if (lookahead == 'y') ADVANCE(542);
      END_STATE();
    case 866:
      if (lookahead == 'y') ADVANCE(543);
      END_STATE();
    case 867:
      if (lookahead == 'z') ADVANCE(297);
      END_STATE();
    case 868:
      if (lookahead == 'z') ADVANCE(301);
      END_STATE();
    case 869:
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(875);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1412);
      END_STATE();
    case 870:
      if (lookahead == 'H' ||
          ('K' <= lookahead && lookahead <= 'M') ||
          lookahead == 'R') ADVANCE(876);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(1413);
      END_STATE();
    case 871:
      if (lookahead == 'H' ||
          ('K' <= lookahead && lookahead <= 'M') ||
          lookahead == 'R') ADVANCE(876);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(1410);
      END_STATE();
    case 872:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1409);
      END_STATE();
    case 873:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1407);
      END_STATE();
    case 874:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(68);
      END_STATE();
    case 875:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1412);
      END_STATE();
    case 876:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(1413);
      END_STATE();
    case 877:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(1410);
      END_STATE();
    case 878:
      if (lookahead == '$' ||
          lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1456);
      END_STATE();
    case 879:
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 880:
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1402);
      END_STATE();
    case 881:
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1401);
      END_STATE();
    case 882:
      if (eof) ADVANCE(886);
      ADVANCE_MAP(
        '\n', 893,
        '\r', 1,
        '!', 1519,
        '"', 10,
        '$', 878,
        '%', 17,
        '&', 20,
        '(', 888,
        ')', 890,
        '*', 1527,
        '+', 1629,
        ',', 889,
        '-', 1630,
        '.', 1530,
        '/', 26,
        '0', 855,
        ':', 892,
        ';', 894,
        '<', 1515,
        '=', 1495,
        '>', 1517,
        '@', 21,
        'C', 600,
        'E', 856,
        '[', 1528,
        ']', 1529,
        '_', 1531,
        '`', 1628,
        'a', 192,
        'b', 105,
        'c', 106,
        'd', 173,
        'e', 101,
        'f', 115,
        'g', 601,
        'h', 118,
        'i', 523,
        'j', 831,
        'k', 449,
        'l', 108,
        'm', 116,
        'n', 267,
        'o', 307,
        'p', 1537,
        'r', 268,
        's', 1536,
        't', 109,
        'u', 73,
        'v', 611,
        'w', 450,
        'x', 1540,
        '{', 1489,
        '|', 1526,
        '}', 1490,
      );
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(882);
      END_STATE();
    case 883:
      if (eof) ADVANCE(886);
      ADVANCE_MAP(
        '\n', 893,
        '\r', 1,
        '"', 10,
        '$', 878,
        '%', 879,
        '(', 888,
        ')', 890,
        ',', 889,
        '/', 26,
        ':', 891,
        ';', 894,
        '=', 1495,
        '{', 1489,
        '|', 81,
      );
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(883);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 884:
      if (eof) ADVANCE(886);
      ADVANCE_MAP(
        '\n', 893,
        '\r', 1,
        '$', 878,
        '%', 879,
        '/', 26,
        ';', 894,
        '_', 1532,
        'a', 1112,
        'c', 1235,
        'd', 1049,
        'e', 939,
        'f', 1279,
        'i', 1187,
        'k', 1140,
        'l', 1153,
        'n', 1147,
        'r', 1045,
        's', 1372,
        'u', 1201,
      );
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(884);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 885:
      if (eof) ADVANCE(886);
      ADVANCE_MAP(
        '\n', 893,
        '\r', 1,
        '$', 878,
        '%', 879,
        '/', 26,
        ';', 894,
        '_', 1532,
        'a', 1112,
        'c', 1235,
        'd', 1049,
        'e', 939,
        'f', 1279,
        'i', 1187,
        'k', 1140,
        'n', 1147,
        'r', 1045,
        'u', 1201,
        '}', 1490,
      );
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(885);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 886:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 887:
      ACCEPT_TOKEN(aux_sym_body_token1);
      END_STATE();
    case 888:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 889:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 890:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 891:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 892:
      ACCEPT_TOKEN(anon_sym_COLON);
      if (lookahead == ':') ADVANCE(1514);
      END_STATE();
    case 893:
      ACCEPT_TOKEN(sym__newline);
      END_STATE();
    case 894:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(894);
      END_STATE();
    case 895:
      ACCEPT_TOKEN(sym_multiline_comment);
      END_STATE();
    case 896:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '-') ADVANCE(1159);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 897:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '-') ADVANCE(1111);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 898:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '-') ADVANCE(1030);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 899:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '-') ADVANCE(1342);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 900:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '-') ADVANCE(1139);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 901:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '-') ADVANCE(1197);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 902:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '-') ADVANCE(958);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 903:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '-') ADVANCE(1208);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 904:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '-') ADVANCE(1009);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 905:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '-') ADVANCE(1300);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 906:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '-') ADVANCE(1380);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 907:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '-') ADVANCE(1157);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 908:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '-') ADVANCE(1282);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 909:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '-') ADVANCE(1158);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 910:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '-') ADVANCE(1324);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 911:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '-') ADVANCE(1160);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 912:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '0') ADVANCE(1724);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('1' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 913:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '1') ADVANCE(915);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 914:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '1') ADVANCE(916);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 915:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '2') ADVANCE(919);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 916:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '2') ADVANCE(921);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 917:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '6') ADVANCE(928);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 918:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '8') ADVANCE(917);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 919:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '8') ADVANCE(1726);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 920:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '8') ADVANCE(912);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 921:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '8') ADVANCE(1728);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 922:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'M') ADVANCE(963);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 923:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'R') ADVANCE(1053);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 924:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '_') ADVANCE(1385);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 925:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '_') ADVANCE(1307);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 926:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '_') ADVANCE(1106);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 927:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '_') ADVANCE(1244);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 928:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '_') ADVANCE(1107);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 929:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '_') ADVANCE(959);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 930:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '_') ADVANCE(1026);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 931:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '_') ADVANCE(1273);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 932:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '_') ADVANCE(1305);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 933:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '_') ADVANCE(1011);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 934:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '_') ADVANCE(1325);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 935:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '_') ADVANCE(1014);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 936:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '_') ADVANCE(1326);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 937:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '_') ADVANCE(1246);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 938:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1268);
      if (lookahead == 's') ADVANCE(1010);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 939:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1268);
      if (lookahead == 'x') ADVANCE(971);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 940:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1507);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 941:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1556);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 942:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1562);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 943:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1193);
      if (lookahead == 'h') ADVANCE(1376);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1457);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 944:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1172);
      if (lookahead == 'e') ADVANCE(946);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 945:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1172);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 946:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1251);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 947:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1017);
      if (lookahead == 'b') ADVANCE(1375);
      if (lookahead == 'f') ADVANCE(1653);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('c' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 948:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1017);
      if (lookahead == 'b') ADVANCE(1379);
      if (lookahead == 'f') ADVANCE(1653);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('c' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 949:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1017);
      if (lookahead == 'b') ADVANCE(1379);
      if (lookahead == 'f') ADVANCE(1655);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('c' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 950:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1266);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 951:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1253);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 952:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1194);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 953:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1329);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 954:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1023);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 955:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1296);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 956:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1131);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 957:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1354);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 958:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1183);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 959:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1302);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 960:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1168);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 961:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1330);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 962:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1173);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 963:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1299);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 964:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1007);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 965:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(932);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 966:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1269);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 967:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1203);
      if (lookahead == 'e') ADVANCE(1124);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 968:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1351);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 969:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1383);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 970:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1196);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 971:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1004);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 972:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1309);
      if (lookahead == 'n') ADVANCE(952);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 973:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1309);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 974:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1005);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 975:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1357);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 976:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1358);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 977:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1360);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 978:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(991);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 979:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(1286);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 980:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(992);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 981:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(937);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 982:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'b') ADVANCE(1125);
      if (lookahead == 'e') ADVANCE(947);
      if (lookahead == 'o') ADVANCE(1370);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 983:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'b') ADVANCE(1125);
      if (lookahead == 'e') ADVANCE(948);
      if (lookahead == 'o') ADVANCE(1370);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 984:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'b') ADVANCE(1234);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 985:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'b') ADVANCE(1236);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 986:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'b') ADVANCE(1065);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 987:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'b') ADVANCE(1073);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 988:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'b') ADVANCE(1081);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 989:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'b') ADVANCE(987);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 990:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'b') ADVANCE(1178);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 991:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'b') ADVANCE(1181);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 992:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'b') ADVANCE(1182);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 993:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(926);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 994:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(1165);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 995:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(1616);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 996:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(1685);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 997:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(1301);
      if (lookahead == 'o') ADVANCE(1298);
      if (lookahead == 'p') ADVANCE(993);
      if (lookahead == 'r') ADVANCE(1095);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1457);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 998:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(1247);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 999:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(1149);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1000:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(1110);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1001:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(901);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1002:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(1349);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1003:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(1239);
      if (lookahead == 'f') ADVANCE(1257);
      if (lookahead == 'm') ADVANCE(1088);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1004:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(1337);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1005:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(1338);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1006:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(1366);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1007:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(1096);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1008:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(1066);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1009:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(1177);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1010:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(951);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1011:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(1113);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1012:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(1013);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1013:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(1091);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1014:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(1114);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1015:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(968);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1016:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(1162);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1017:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(1657);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1018:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(1659);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1019:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(1578);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1020:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(1580);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1021:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(1550);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1022:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(1224);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1023:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(1031);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1024:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(1063);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1025:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(1155);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1026:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(1070);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1027:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(1072);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1028:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(1040);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1029:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(1079);
      if (lookahead == 'p') ADVANCE(1283);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1030:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(1093);
      if (lookahead == 's') ADVANCE(1087);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1031:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(1281);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1032:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1126);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1033:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1723);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1034:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1566);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1035:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1547);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1036:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1509);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1037:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1665);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1038:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1667);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1039:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1544);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1040:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1390);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1041:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1572);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1042:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1570);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1043:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1568);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1044:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1574);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1045:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(972);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1046:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1695);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1047:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1697);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1048:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1134);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1049:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(949);
      if (lookahead == 'i') ADVANCE(1294);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1050:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1392);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1051:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1190);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1052:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1229);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1053:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1123);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1054:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1265);
      if (lookahead == 'p') ADVANCE(1275);
      if (lookahead == 'r') ADVANCE(1141);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1055:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1265);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1056:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(924);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1057:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1018);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1058:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1136);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1059:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1002);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1060:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1260);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1061:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(931);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1062:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1019);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1063:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1099);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1064:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1306);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1065:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1272);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1066:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1256);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1067:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1020);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1068:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1331);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1069:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1021);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1070:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1109);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1071:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1025);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1072:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1100);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1073:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1261);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1074:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1346);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1075:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1101);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1076:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1150);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1077:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1262);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1078:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(898);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1079:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1103);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1080:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1263);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1081:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1264);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1082:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1334);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1083:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1335);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1084:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1336);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1085:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(973);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1086:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1353);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1087:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1348);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1088:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1284);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1089:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1195);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1090:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1285);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1091:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1311);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1092:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1215);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1093:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(1316);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1094:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(948);
      if (lookahead == 'o') ADVANCE(1370);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1095:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(909);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1096:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(935);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1097:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(1185);
      if (lookahead == 'l') ADVANCE(1226);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1098:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(1717);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1099:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(1606);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1100:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(1651);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1101:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(1497);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1102:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(1675);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1103:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(1608);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1104:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(1115);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1105:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(1138);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1106:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(1259);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1107:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(1250);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1108:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(1116);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1109:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(929);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1110:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(941);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1111:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(1179);
      if (lookahead == 'i') ADVANCE(1218);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1112:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(1202);
      if (lookahead == 'r') ADVANCE(998);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1113:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(981);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1114:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(942);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1115:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(1304);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1116:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(1180);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1117:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(1319);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1118:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(1320);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1119:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(1322);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1120:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(1117);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1121:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(1118);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1122:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(1119);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1123:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(922);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1124:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(1701);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1125:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(900);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1126:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(1154);
      if (lookahead == 'l') ADVANCE(927);
      if (lookahead == 'm') ADVANCE(1051);
      if (lookahead == 'n') ADVANCE(952);
      if (lookahead == 's') ADVANCE(1345);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1127:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(896);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1128:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(1222);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1129:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(1074);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1130:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(906);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1131:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(1291);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1132:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(1046);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1133:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(1092);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1134:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(957);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1135:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(1086);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1136:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(1156);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1137:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(1382);
      if (lookahead == 'l') ADVANCE(1381);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1138:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(899);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1139:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(1219);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1140:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(1175);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1141:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(1205);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1142:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(999);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1143:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(1128);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1144:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(1231);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1145:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(995);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1146:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(1232);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1147:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(1210);
      if (lookahead == 'n') ADVANCE(967);
      if (lookahead == 'o') ADVANCE(1003);
      if (lookahead == 's') ADVANCE(1387);
      if (lookahead == 'u') ADVANCE(1297);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1148:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(1294);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1149:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(1333);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1150:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(1211);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1151:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(1206);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1152:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(1214);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1153:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(1384);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1154:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(1318);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1155:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(1006);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1156:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(1323);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1157:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(1218);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1158:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(1220);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1159:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(1221);
      if (lookahead == 'l') ADVANCE(1241);
      if (lookahead == 'u') ADVANCE(1315);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1160:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(1223);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1161:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'j') ADVANCE(1238);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1162:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'j') ADVANCE(1378);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1163:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'k') ADVANCE(1604);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1164:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'k') ADVANCE(1542);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1165:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'k') ADVANCE(954);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1166:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'k') ADVANCE(1080);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1167:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(1394);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1168:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(1661);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1169:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(1499);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1170:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(1501);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1171:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(1225);
      if (lookahead == 'p') ADVANCE(913);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1172:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(1098);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1173:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(1374);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1174:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(1142);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1175:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(1176);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1176:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(1057);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1177:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(1227);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1178:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(1033);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1179:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(956);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1180:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(1089);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1181:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(1038);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1182:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(1047);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1183:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(1184);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1184:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(1233);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1185:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(1243);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1186:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'm') ADVANCE(1252);
      if (lookahead == 'n') ADVANCE(1328);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1457);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1187:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'm') ADVANCE(1252);
      if (lookahead == 'n') ADVANCE(1361);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1188:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'm') ADVANCE(923);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1189:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'm') ADVANCE(1267);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1190:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'm') ADVANCE(986);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1191:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'm') ADVANCE(930);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1192:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'm') ADVANCE(984);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1193:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'm') ADVANCE(1056);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1194:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'm') ADVANCE(978);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1195:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'm') ADVANCE(955);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1196:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'm') ADVANCE(1078);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1197:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'm') ADVANCE(966);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1198:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'm') ADVANCE(985);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1199:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'm') ADVANCE(988);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1200:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(1513);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1201:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(1029);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1202:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(1683);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1203:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(1673);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1204:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(1024);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1205:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(1317);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1206:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(1022);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1207:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(1289);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1208:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(1377);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1209:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(1258);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1210:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(1102);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1211:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(1292);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1212:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(1069);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1213:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(1362);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1214:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(1339);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1215:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(1341);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1216:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(960);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1217:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(1386);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1218:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(1028);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1219:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(1308);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1220:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(1310);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1221:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(1313);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1222:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(936);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1223:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(1327);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1224:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(1389);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1225:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(953);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1226:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(994);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1227:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(989);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1228:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(1393);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1229:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(1373);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1230:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(1188);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1231:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(1207);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1232:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(1200);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1233:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(1001);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1234:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(1169);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1235:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(1213);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1236:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(1170);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1237:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(996);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1238:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(1152);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1239:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(1217);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1240:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(1276);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1241:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(1015);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1242:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(1278);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1243:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(961);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1244:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(1120);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1245:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(1121);
      if (lookahead == 'r') ADVANCE(1058);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1246:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(1122);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1247:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'p') ADVANCE(1679);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1248:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'p') ADVANCE(1669);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1249:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'p') ADVANCE(993);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1457);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1250:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'p') ADVANCE(920);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1251:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'p') ADVANCE(902);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1252:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'p') ADVANCE(1174);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1253:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'p') ADVANCE(1034);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1254:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'p') ADVANCE(964);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1255:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'p') ADVANCE(1036);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1256:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'p') ADVANCE(1340);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1257:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'p') ADVANCE(1050);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1258:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'p') ADVANCE(1283);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1259:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'p') ADVANCE(914);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1260:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(1564);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1261:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(1663);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1262:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(1546);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1263:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(1503);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1264:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(1511);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1265:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(1216);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1266:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(1129);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1267:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(940);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1268:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(1167);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1269:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(1166);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1270:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(908);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1271:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(905);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1272:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(934);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1273:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(965);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1274:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(903);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1275:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(1062);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1276:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(1293);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1277:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(1228);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1278:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(1035);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1279:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(970);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1280:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(1067);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1281:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(1064);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1282:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(1075);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1283:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(1071);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1284:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(1132);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1285:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(1133);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1286:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(1135);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1287:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(974);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1288:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(910);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1289:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1505);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1290:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1614);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1291:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1535);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1292:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1494);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1293:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1492);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1294:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1161);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1295:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1343);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1296:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1163);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1297:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1388);
      if (lookahead == 'w') ADVANCE(1687);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1298:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1368);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1299:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1164);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1300:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1395);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1301:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1059);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1302:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1254);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1303:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1344);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1304:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1068);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1305:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1143);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1306:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1290);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1307:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(969);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1308:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1347);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1309:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1321);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1310:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1350);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1311:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1312);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1312:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1240);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1313:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1352);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1314:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1363);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1315:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1037);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1316:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1356);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1317:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1145);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1318:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1355);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1319:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1082);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1320:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1083);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1321:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1237);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1322:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1084);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1323:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1359);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1324:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1397);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1325:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1364);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1326:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1365);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1327:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(1367);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1328:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1054);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1329:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1720);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1330:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1719);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1331:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1552);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1332:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1610);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1333:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1648);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1334:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1554);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1335:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1558);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1336:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1560);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1337:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1691);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1338:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1681);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1339:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1703);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1340:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1693);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1341:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1699);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1342:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1396);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1343:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1230);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1344:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(933);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1345:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1242);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1346:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(897);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1347:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1270);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1348:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1371);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1349:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1144);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1350:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1271);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1351:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1146);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1352:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1274);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1353:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(907);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1354:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1061);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1355:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1060);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1356:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1277);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1357:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1042);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1358:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1043);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1359:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1077);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1360:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1044);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1361:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1055);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1362:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1287);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1363:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(975);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1364:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(976);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1365:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(977);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1366:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(980);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1367:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(1288);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1368:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(911);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1369:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(1295);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1370:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(990);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1371:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(1248);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1372:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(1012);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1373:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(1332);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1374:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(1039);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1375:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(1127);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1376:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(1108);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1377:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(1199);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1378:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(1303);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1379:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(1130);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1380:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(1315);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1381:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'v') ADVANCE(1191);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1382:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'v') ADVANCE(1052);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1383:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'v') ADVANCE(1041);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1384:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'v') ADVANCE(1076);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1385:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'v') ADVANCE(962);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1386:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'v') ADVANCE(1090);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1387:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'w') ADVANCE(1689);
      if (lookahead == 'z') ADVANCE(1677);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'y')) ADVANCE(1400);
      END_STATE();
    case 1388:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'w') ADVANCE(1705);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1389:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'w') ADVANCE(925);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1390:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'x') ADVANCE(1612);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1391:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'x') ADVANCE(971);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1392:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'x') ADVANCE(1008);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1393:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'y') ADVANCE(1671);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1394:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'y') ADVANCE(904);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1395:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'y') ADVANCE(1192);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1396:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'y') ADVANCE(1255);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1397:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'y') ADVANCE(1198);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1398:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1457);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1399:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1399);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1400:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1401:
      ACCEPT_TOKEN(sym_bb_ref);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1401);
      END_STATE();
    case 1402:
      ACCEPT_TOKEN(sym_stack_object);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1402);
      END_STATE();
    case 1403:
      ACCEPT_TOKEN(sym_constant_pool_index);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1403);
      END_STATE();
    case 1404:
      ACCEPT_TOKEN(sym_jump_table_index);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1404);
      END_STATE();
    case 1405:
      ACCEPT_TOKEN(sym_string);
      END_STATE();
    case 1406:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(1411);
      if (lookahead == 'x') ADVANCE(871);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1407);
      END_STATE();
    case 1407:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(1411);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1407);
      END_STATE();
    case 1408:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == 'x') ADVANCE(877);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1409);
      END_STATE();
    case 1409:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1409);
      END_STATE();
    case 1410:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(1410);
      END_STATE();
    case 1411:
      ACCEPT_TOKEN(aux_sym_float_token1);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(869);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1411);
      END_STATE();
    case 1412:
      ACCEPT_TOKEN(aux_sym_float_token1);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1412);
      END_STATE();
    case 1413:
      ACCEPT_TOKEN(aux_sym_float_token2);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(1413);
      END_STATE();
    case 1414:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == '"') ADVANCE(12);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1450);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1415:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == '"') ADVANCE(15);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1450);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1416:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == '-') ADVANCE(1424);
      if (lookahead == '.') ADVANCE(1414);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1417:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == '-') ADVANCE(1443);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1418:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == '-') ADVANCE(1447);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1419:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == '.') ADVANCE(1403);
      if (lookahead == '$' ||
          lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1420:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == '.') ADVANCE(1404);
      if (lookahead == '$' ||
          lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1421:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == '.') ADVANCE(1415);
      if (lookahead == '$' ||
          lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1422:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'a') ADVANCE(1427);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1423:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'a') ADVANCE(1425);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1424:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'b') ADVANCE(1435);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1425:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'b') ADVANCE(1436);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1426:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'b') ADVANCE(1455);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1427:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'c') ADVANCE(1433);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1428:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'c') ADVANCE(1434);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1429:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'd') ADVANCE(1417);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1430:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'e') ADVANCE(1429);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1431:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'e') ADVANCE(1420);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1432:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'i') ADVANCE(1449);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1433:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'k') ADVANCE(1454);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1434:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'k') ADVANCE(1421);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1435:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'l') ADVANCE(1440);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1436:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'l') ADVANCE(1431);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1437:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'm') ADVANCE(1441);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1438:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'n') ADVANCE(1444);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1439:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'o') ADVANCE(1438);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1440:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'o') ADVANCE(1428);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1441:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'p') ADVANCE(1418);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1442:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'r') ADVANCE(1416);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1443:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 's') ADVANCE(1445);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1444:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 's') ADVANCE(1446);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1445:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 't') ADVANCE(1422);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1446:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 't') ADVANCE(1419);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1447:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 't') ADVANCE(1423);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1448:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'u') ADVANCE(1437);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1449:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == 'x') ADVANCE(1430);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1450:
      ACCEPT_TOKEN(sym_var);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1450);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1451:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1451);
      END_STATE();
    case 1452:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1402);
      END_STATE();
    case 1453:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1401);
      END_STATE();
    case 1454:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1452);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(880);
      END_STATE();
    case 1455:
      ACCEPT_TOKEN(sym_var);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1453);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(881);
      END_STATE();
    case 1456:
      ACCEPT_TOKEN(sym_physical_register);
      if (lookahead == '$' ||
          lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1456);
      END_STATE();
    case 1457:
      ACCEPT_TOKEN(sym_immediate_type);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1457);
      END_STATE();
    case 1458:
      ACCEPT_TOKEN(sym_ir_block);
      END_STATE();
    case 1459:
      ACCEPT_TOKEN(sym_ir_block);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1459);
      END_STATE();
    case 1460:
      ACCEPT_TOKEN(sym_ir_block);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1460);
      END_STATE();
    case 1461:
      ACCEPT_TOKEN(sym_external_symbol);
      END_STATE();
    case 1462:
      ACCEPT_TOKEN(sym_external_symbol);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1462);
      END_STATE();
    case 1463:
      ACCEPT_TOKEN(sym_external_symbol);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1463);
      END_STATE();
    case 1464:
      ACCEPT_TOKEN(sym_global_var);
      END_STATE();
    case 1465:
      ACCEPT_TOKEN(sym_global_var);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1465);
      END_STATE();
    case 1466:
      ACCEPT_TOKEN(sym_global_var);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1466);
      END_STATE();
    case 1467:
      ACCEPT_TOKEN(sym_ir_local_var);
      END_STATE();
    case 1468:
      ACCEPT_TOKEN(sym_ir_local_var);
      if (lookahead == '"') ADVANCE(12);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1482);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1484);
      END_STATE();
    case 1469:
      ACCEPT_TOKEN(sym_ir_local_var);
      if (lookahead == '-') ADVANCE(1478);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1484);
      END_STATE();
    case 1470:
      ACCEPT_TOKEN(sym_ir_local_var);
      if (lookahead == '.') ADVANCE(1468);
      if (lookahead == '$' ||
          lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1484);
      END_STATE();
    case 1471:
      ACCEPT_TOKEN(sym_ir_local_var);
      if (lookahead == 'a') ADVANCE(1472);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(1484);
      END_STATE();
    case 1472:
      ACCEPT_TOKEN(sym_ir_local_var);
      if (lookahead == 'c') ADVANCE(1476);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1484);
      END_STATE();
    case 1473:
      ACCEPT_TOKEN(sym_ir_local_var);
      if (lookahead == 'd') ADVANCE(1469);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1484);
      END_STATE();
    case 1474:
      ACCEPT_TOKEN(sym_ir_local_var);
      if (lookahead == 'e') ADVANCE(1473);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1484);
      END_STATE();
    case 1475:
      ACCEPT_TOKEN(sym_ir_local_var);
      if (lookahead == 'i') ADVANCE(1480);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1484);
      END_STATE();
    case 1476:
      ACCEPT_TOKEN(sym_ir_local_var);
      if (lookahead == 'k') ADVANCE(1485);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1484);
      END_STATE();
    case 1477:
      ACCEPT_TOKEN(sym_ir_local_var);
      if (lookahead == 'r') ADVANCE(1470);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1484);
      END_STATE();
    case 1478:
      ACCEPT_TOKEN(sym_ir_local_var);
      if (lookahead == 's') ADVANCE(1479);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1484);
      END_STATE();
    case 1479:
      ACCEPT_TOKEN(sym_ir_local_var);
      if (lookahead == 't') ADVANCE(1471);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1484);
      END_STATE();
    case 1480:
      ACCEPT_TOKEN(sym_ir_local_var);
      if (lookahead == 'x') ADVANCE(1474);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1484);
      END_STATE();
    case 1481:
      ACCEPT_TOKEN(sym_ir_local_var);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1481);
      END_STATE();
    case 1482:
      ACCEPT_TOKEN(sym_ir_local_var);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1482);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1484);
      END_STATE();
    case 1483:
      ACCEPT_TOKEN(sym_ir_local_var);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1402);
      END_STATE();
    case 1484:
      ACCEPT_TOKEN(sym_ir_local_var);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1484);
      END_STATE();
    case 1485:
      ACCEPT_TOKEN(sym_ir_local_var);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1483);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(880);
      END_STATE();
    case 1486:
      ACCEPT_TOKEN(sym_metadata_ref);
      END_STATE();
    case 1487:
      ACCEPT_TOKEN(sym_metadata_ref);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1487);
      END_STATE();
    case 1488:
      ACCEPT_TOKEN(sym_metadata_ref);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1488);
      END_STATE();
    case 1489:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 1490:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 1491:
      ACCEPT_TOKEN(anon_sym_successors);
      END_STATE();
    case 1492:
      ACCEPT_TOKEN(anon_sym_successors);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1493:
      ACCEPT_TOKEN(anon_sym_liveins);
      END_STATE();
    case 1494:
      ACCEPT_TOKEN(anon_sym_liveins);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1495:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 1496:
      ACCEPT_TOKEN(anon_sym_dbg_DASHinstr_DASHref);
      END_STATE();
    case 1497:
      ACCEPT_TOKEN(anon_sym_dbg_DASHinstr_DASHref);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1498:
      ACCEPT_TOKEN(anon_sym_pre_DASHinstr_DASHsymbol);
      END_STATE();
    case 1499:
      ACCEPT_TOKEN(anon_sym_pre_DASHinstr_DASHsymbol);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1500:
      ACCEPT_TOKEN(anon_sym_post_DASHinstr_DASHsymbol);
      END_STATE();
    case 1501:
      ACCEPT_TOKEN(anon_sym_post_DASHinstr_DASHsymbol);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1502:
      ACCEPT_TOKEN(anon_sym_heap_DASHalloc_DASHmarker);
      END_STATE();
    case 1503:
      ACCEPT_TOKEN(anon_sym_heap_DASHalloc_DASHmarker);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1504:
      ACCEPT_TOKEN(anon_sym_pcsections);
      END_STATE();
    case 1505:
      ACCEPT_TOKEN(anon_sym_pcsections);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1506:
      ACCEPT_TOKEN(anon_sym_mmra);
      END_STATE();
    case 1507:
      ACCEPT_TOKEN(anon_sym_mmra);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1508:
      ACCEPT_TOKEN(anon_sym_cfi_DASHtype);
      END_STATE();
    case 1509:
      ACCEPT_TOKEN(anon_sym_cfi_DASHtype);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1510:
      ACCEPT_TOKEN(anon_sym_debug_DASHinstr_DASHnumber);
      END_STATE();
    case 1511:
      ACCEPT_TOKEN(anon_sym_debug_DASHinstr_DASHnumber);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1512:
      ACCEPT_TOKEN(anon_sym_debug_DASHlocation);
      END_STATE();
    case 1513:
      ACCEPT_TOKEN(anon_sym_debug_DASHlocation);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1514:
      ACCEPT_TOKEN(anon_sym_COLON_COLON);
      END_STATE();
    case 1515:
      ACCEPT_TOKEN(anon_sym_LT);
      END_STATE();
    case 1516:
      ACCEPT_TOKEN(anon_sym_mcsymbol);
      END_STATE();
    case 1517:
      ACCEPT_TOKEN(anon_sym_GT);
      END_STATE();
    case 1518:
      ACCEPT_TOKEN(anon_sym_LPAREN2);
      END_STATE();
    case 1519:
      ACCEPT_TOKEN(anon_sym_BANG);
      if (lookahead == '"') ADVANCE(11);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1487);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1488);
      END_STATE();
    case 1520:
      ACCEPT_TOKEN(anon_sym_null);
      END_STATE();
    case 1521:
      ACCEPT_TOKEN(anon_sym_null);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1525);
      END_STATE();
    case 1522:
      ACCEPT_TOKEN(aux_sym_md_value_token1);
      if (lookahead == 'l') ADVANCE(1521);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1525);
      END_STATE();
    case 1523:
      ACCEPT_TOKEN(aux_sym_md_value_token1);
      if (lookahead == 'l') ADVANCE(1522);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1525);
      END_STATE();
    case 1524:
      ACCEPT_TOKEN(aux_sym_md_value_token1);
      if (lookahead == 'u') ADVANCE(1523);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1525);
      END_STATE();
    case 1525:
      ACCEPT_TOKEN(aux_sym_md_value_token1);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '\\' ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1525);
      END_STATE();
    case 1526:
      ACCEPT_TOKEN(anon_sym_PIPE);
      END_STATE();
    case 1527:
      ACCEPT_TOKEN(anon_sym_STAR);
      END_STATE();
    case 1528:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 1529:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 1530:
      ACCEPT_TOKEN(anon_sym_DOT);
      END_STATE();
    case 1531:
      ACCEPT_TOKEN(anon_sym__);
      END_STATE();
    case 1532:
      ACCEPT_TOKEN(anon_sym__);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1533:
      ACCEPT_TOKEN(anon_sym_tied_DASHdef);
      END_STATE();
    case 1534:
      ACCEPT_TOKEN(anon_sym_target_DASHflags);
      END_STATE();
    case 1535:
      ACCEPT_TOKEN(anon_sym_target_DASHflags);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1536:
      ACCEPT_TOKEN(sym_primitive_type);
      ADVANCE_MAP(
        '0', 1457,
        'a', 534,
        'e', 665,
        'g', 272,
        'h', 833,
        'l', 273,
        't', 130,
        'u', 218,
        'y', 562,
      );
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(1457);
      END_STATE();
    case 1537:
      ACCEPT_TOKEN(sym_primitive_type);
      if (lookahead == 'c') ADVANCE(771);
      if (lookahead == 'o') ADVANCE(724);
      if (lookahead == 'p') ADVANCE(195);
      if (lookahead == 'r') ADVANCE(380);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1457);
      END_STATE();
    case 1538:
      ACCEPT_TOKEN(sym_primitive_type);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1538);
      END_STATE();
    case 1539:
      ACCEPT_TOKEN(anon_sym_vscale);
      END_STATE();
    case 1540:
      ACCEPT_TOKEN(anon_sym_x);
      END_STATE();
    case 1541:
      ACCEPT_TOKEN(anon_sym_CustomRegMask);
      END_STATE();
    case 1542:
      ACCEPT_TOKEN(anon_sym_CustomRegMask);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1543:
      ACCEPT_TOKEN(anon_sym_same_value);
      END_STATE();
    case 1544:
      ACCEPT_TOKEN(anon_sym_same_value);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1545:
      ACCEPT_TOKEN(anon_sym_def_cfa_register);
      END_STATE();
    case 1546:
      ACCEPT_TOKEN(anon_sym_def_cfa_register);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1547:
      ACCEPT_TOKEN(anon_sym_restore);
      if (lookahead == '_') ADVANCE(1314);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1548:
      ACCEPT_TOKEN(anon_sym_restore);
      if (lookahead == '_') ADVANCE(748);
      END_STATE();
    case 1549:
      ACCEPT_TOKEN(anon_sym_undefined);
      END_STATE();
    case 1550:
      ACCEPT_TOKEN(anon_sym_undefined);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1551:
      ACCEPT_TOKEN(anon_sym_offset);
      END_STATE();
    case 1552:
      ACCEPT_TOKEN(anon_sym_offset);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1553:
      ACCEPT_TOKEN(anon_sym_rel_offset);
      END_STATE();
    case 1554:
      ACCEPT_TOKEN(anon_sym_rel_offset);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1555:
      ACCEPT_TOKEN(anon_sym_def_cfa);
      if (lookahead == '_') ADVANCE(641);
      END_STATE();
    case 1556:
      ACCEPT_TOKEN(anon_sym_def_cfa);
      if (lookahead == '_') ADVANCE(1245);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1557:
      ACCEPT_TOKEN(anon_sym_def_cfa_offset);
      END_STATE();
    case 1558:
      ACCEPT_TOKEN(anon_sym_def_cfa_offset);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1559:
      ACCEPT_TOKEN(anon_sym_adjust_cfa_offset);
      END_STATE();
    case 1560:
      ACCEPT_TOKEN(anon_sym_adjust_cfa_offset);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1561:
      ACCEPT_TOKEN(anon_sym_llvm_def_aspace_cfa);
      END_STATE();
    case 1562:
      ACCEPT_TOKEN(anon_sym_llvm_def_aspace_cfa);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1563:
      ACCEPT_TOKEN(anon_sym_register);
      END_STATE();
    case 1564:
      ACCEPT_TOKEN(anon_sym_register);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1565:
      ACCEPT_TOKEN(anon_sym_escape);
      END_STATE();
    case 1566:
      ACCEPT_TOKEN(anon_sym_escape);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1567:
      ACCEPT_TOKEN(anon_sym_remember_state);
      END_STATE();
    case 1568:
      ACCEPT_TOKEN(anon_sym_remember_state);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1569:
      ACCEPT_TOKEN(anon_sym_restore_state);
      END_STATE();
    case 1570:
      ACCEPT_TOKEN(anon_sym_restore_state);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1571:
      ACCEPT_TOKEN(anon_sym_window_save);
      END_STATE();
    case 1572:
      ACCEPT_TOKEN(anon_sym_window_save);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1573:
      ACCEPT_TOKEN(anon_sym_negate_ra_sign_state);
      END_STATE();
    case 1574:
      ACCEPT_TOKEN(anon_sym_negate_ra_sign_state);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1575:
      ACCEPT_TOKEN(anon_sym_true);
      END_STATE();
    case 1576:
      ACCEPT_TOKEN(anon_sym_false);
      END_STATE();
    case 1577:
      ACCEPT_TOKEN(anon_sym_intpred);
      END_STATE();
    case 1578:
      ACCEPT_TOKEN(anon_sym_intpred);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1579:
      ACCEPT_TOKEN(anon_sym_floatpred);
      END_STATE();
    case 1580:
      ACCEPT_TOKEN(anon_sym_floatpred);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1581:
      ACCEPT_TOKEN(anon_sym_eq);
      END_STATE();
    case 1582:
      ACCEPT_TOKEN(anon_sym_ne);
      END_STATE();
    case 1583:
      ACCEPT_TOKEN(anon_sym_ne);
      if (lookahead == 'g') ADVANCE(124);
      END_STATE();
    case 1584:
      ACCEPT_TOKEN(anon_sym_sgt);
      END_STATE();
    case 1585:
      ACCEPT_TOKEN(anon_sym_sge);
      END_STATE();
    case 1586:
      ACCEPT_TOKEN(anon_sym_slt);
      END_STATE();
    case 1587:
      ACCEPT_TOKEN(anon_sym_sle);
      END_STATE();
    case 1588:
      ACCEPT_TOKEN(anon_sym_ugt);
      END_STATE();
    case 1589:
      ACCEPT_TOKEN(anon_sym_uge);
      END_STATE();
    case 1590:
      ACCEPT_TOKEN(anon_sym_ult);
      END_STATE();
    case 1591:
      ACCEPT_TOKEN(anon_sym_ule);
      END_STATE();
    case 1592:
      ACCEPT_TOKEN(anon_sym_oeq);
      END_STATE();
    case 1593:
      ACCEPT_TOKEN(anon_sym_ogt);
      END_STATE();
    case 1594:
      ACCEPT_TOKEN(anon_sym_oge);
      END_STATE();
    case 1595:
      ACCEPT_TOKEN(anon_sym_olt);
      END_STATE();
    case 1596:
      ACCEPT_TOKEN(anon_sym_ole);
      END_STATE();
    case 1597:
      ACCEPT_TOKEN(anon_sym_one);
      END_STATE();
    case 1598:
      ACCEPT_TOKEN(anon_sym_ord);
      END_STATE();
    case 1599:
      ACCEPT_TOKEN(anon_sym_uno);
      END_STATE();
    case 1600:
      ACCEPT_TOKEN(anon_sym_uno);
      if (lookahead == 'r') ADVANCE(249);
      END_STATE();
    case 1601:
      ACCEPT_TOKEN(anon_sym_ueq);
      END_STATE();
    case 1602:
      ACCEPT_TOKEN(anon_sym_une);
      END_STATE();
    case 1603:
      ACCEPT_TOKEN(anon_sym_shufflemask);
      END_STATE();
    case 1604:
      ACCEPT_TOKEN(anon_sym_shufflemask);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1605:
      ACCEPT_TOKEN(anon_sym_undef);
      END_STATE();
    case 1606:
      ACCEPT_TOKEN(anon_sym_undef);
      if (lookahead == 'i') ADVANCE(1212);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1607:
      ACCEPT_TOKEN(anon_sym_undef);
      if (lookahead == 'i') ADVANCE(590);
      END_STATE();
    case 1608:
      ACCEPT_TOKEN(anon_sym_undef);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1609:
      ACCEPT_TOKEN(anon_sym_liveout);
      END_STATE();
    case 1610:
      ACCEPT_TOKEN(anon_sym_liveout);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1611:
      ACCEPT_TOKEN(anon_sym_target_DASHindex);
      END_STATE();
    case 1612:
      ACCEPT_TOKEN(anon_sym_target_DASHindex);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1613:
      ACCEPT_TOKEN(anon_sym_blockaddress);
      END_STATE();
    case 1614:
      ACCEPT_TOKEN(anon_sym_blockaddress);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1615:
      ACCEPT_TOKEN(anon_sym_intrinsic);
      END_STATE();
    case 1616:
      ACCEPT_TOKEN(anon_sym_intrinsic);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1617:
      ACCEPT_TOKEN(anon_sym_load);
      END_STATE();
    case 1618:
      ACCEPT_TOKEN(anon_sym_store);
      END_STATE();
    case 1619:
      ACCEPT_TOKEN(anon_sym_unknown_DASHsize);
      END_STATE();
    case 1620:
      ACCEPT_TOKEN(anon_sym_on);
      END_STATE();
    case 1621:
      ACCEPT_TOKEN(anon_sym_on);
      if (lookahead == 'e') ADVANCE(1597);
      END_STATE();
    case 1622:
      ACCEPT_TOKEN(anon_sym_from);
      END_STATE();
    case 1623:
      ACCEPT_TOKEN(anon_sym_into);
      END_STATE();
    case 1624:
      ACCEPT_TOKEN(anon_sym_align);
      END_STATE();
    case 1625:
      ACCEPT_TOKEN(anon_sym_basealign);
      END_STATE();
    case 1626:
      ACCEPT_TOKEN(anon_sym_addrspace);
      END_STATE();
    case 1627:
      ACCEPT_TOKEN(anon_sym_unknown_DASHaddress);
      END_STATE();
    case 1628:
      ACCEPT_TOKEN(anon_sym_BQUOTE);
      END_STATE();
    case 1629:
      ACCEPT_TOKEN(anon_sym_PLUS);
      END_STATE();
    case 1630:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 1631:
      ACCEPT_TOKEN(anon_sym_call_DASHentry);
      END_STATE();
    case 1632:
      ACCEPT_TOKEN(anon_sym_custom);
      END_STATE();
    case 1633:
      ACCEPT_TOKEN(anon_sym_constant_DASHpool);
      END_STATE();
    case 1634:
      ACCEPT_TOKEN(anon_sym_stack);
      END_STATE();
    case 1635:
      ACCEPT_TOKEN(anon_sym_got);
      END_STATE();
    case 1636:
      ACCEPT_TOKEN(anon_sym_jump_DASHtable);
      END_STATE();
    case 1637:
      ACCEPT_TOKEN(anon_sym_volatile);
      END_STATE();
    case 1638:
      ACCEPT_TOKEN(anon_sym_non_DASHtemporal);
      END_STATE();
    case 1639:
      ACCEPT_TOKEN(anon_sym_dereferenceable);
      END_STATE();
    case 1640:
      ACCEPT_TOKEN(anon_sym_invariant);
      END_STATE();
    case 1641:
      ACCEPT_TOKEN(anon_sym_syncscope);
      END_STATE();
    case 1642:
      ACCEPT_TOKEN(anon_sym_unordered);
      END_STATE();
    case 1643:
      ACCEPT_TOKEN(anon_sym_monotonic);
      END_STATE();
    case 1644:
      ACCEPT_TOKEN(anon_sym_acquire);
      END_STATE();
    case 1645:
      ACCEPT_TOKEN(anon_sym_release);
      END_STATE();
    case 1646:
      ACCEPT_TOKEN(anon_sym_acq_rel);
      END_STATE();
    case 1647:
      ACCEPT_TOKEN(anon_sym_seq_cst);
      END_STATE();
    case 1648:
      ACCEPT_TOKEN(anon_sym_implicit);
      if (lookahead == '-') ADVANCE(1027);
      if (lookahead == '$' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1649:
      ACCEPT_TOKEN(anon_sym_implicit);
      if (lookahead == '-') ADVANCE(253);
      END_STATE();
    case 1650:
      ACCEPT_TOKEN(anon_sym_implicit_DASHdef);
      END_STATE();
    case 1651:
      ACCEPT_TOKEN(anon_sym_implicit_DASHdef);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1652:
      ACCEPT_TOKEN(anon_sym_def);
      END_STATE();
    case 1653:
      ACCEPT_TOKEN(anon_sym_def);
      if (lookahead == '_') ADVANCE(1000);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1654:
      ACCEPT_TOKEN(anon_sym_def);
      if (lookahead == '_') ADVANCE(209);
      END_STATE();
    case 1655:
      ACCEPT_TOKEN(anon_sym_def);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1656:
      ACCEPT_TOKEN(anon_sym_dead);
      END_STATE();
    case 1657:
      ACCEPT_TOKEN(anon_sym_dead);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1658:
      ACCEPT_TOKEN(anon_sym_killed);
      END_STATE();
    case 1659:
      ACCEPT_TOKEN(anon_sym_killed);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1660:
      ACCEPT_TOKEN(anon_sym_internal);
      END_STATE();
    case 1661:
      ACCEPT_TOKEN(anon_sym_internal);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1662:
      ACCEPT_TOKEN(anon_sym_early_DASHclobber);
      END_STATE();
    case 1663:
      ACCEPT_TOKEN(anon_sym_early_DASHclobber);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1664:
      ACCEPT_TOKEN(anon_sym_debug_DASHuse);
      END_STATE();
    case 1665:
      ACCEPT_TOKEN(anon_sym_debug_DASHuse);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1666:
      ACCEPT_TOKEN(anon_sym_renamable);
      END_STATE();
    case 1667:
      ACCEPT_TOKEN(anon_sym_renamable);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1668:
      ACCEPT_TOKEN(anon_sym_frame_DASHsetup);
      END_STATE();
    case 1669:
      ACCEPT_TOKEN(anon_sym_frame_DASHsetup);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1670:
      ACCEPT_TOKEN(anon_sym_frame_DASHdestroy);
      END_STATE();
    case 1671:
      ACCEPT_TOKEN(anon_sym_frame_DASHdestroy);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1672:
      ACCEPT_TOKEN(anon_sym_nnan);
      END_STATE();
    case 1673:
      ACCEPT_TOKEN(anon_sym_nnan);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1674:
      ACCEPT_TOKEN(anon_sym_ninf);
      END_STATE();
    case 1675:
      ACCEPT_TOKEN(anon_sym_ninf);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1676:
      ACCEPT_TOKEN(anon_sym_nsz);
      END_STATE();
    case 1677:
      ACCEPT_TOKEN(anon_sym_nsz);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1678:
      ACCEPT_TOKEN(anon_sym_arcp);
      END_STATE();
    case 1679:
      ACCEPT_TOKEN(anon_sym_arcp);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1680:
      ACCEPT_TOKEN(anon_sym_contract);
      END_STATE();
    case 1681:
      ACCEPT_TOKEN(anon_sym_contract);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1682:
      ACCEPT_TOKEN(anon_sym_afn);
      END_STATE();
    case 1683:
      ACCEPT_TOKEN(anon_sym_afn);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1684:
      ACCEPT_TOKEN(anon_sym_reassoc);
      END_STATE();
    case 1685:
      ACCEPT_TOKEN(anon_sym_reassoc);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1686:
      ACCEPT_TOKEN(anon_sym_nuw);
      END_STATE();
    case 1687:
      ACCEPT_TOKEN(anon_sym_nuw);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1688:
      ACCEPT_TOKEN(anon_sym_nsw);
      END_STATE();
    case 1689:
      ACCEPT_TOKEN(anon_sym_nsw);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1690:
      ACCEPT_TOKEN(anon_sym_exact);
      END_STATE();
    case 1691:
      ACCEPT_TOKEN(anon_sym_exact);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1692:
      ACCEPT_TOKEN(anon_sym_nofpexcept);
      END_STATE();
    case 1693:
      ACCEPT_TOKEN(anon_sym_nofpexcept);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1694:
      ACCEPT_TOKEN(anon_sym_nomerge);
      END_STATE();
    case 1695:
      ACCEPT_TOKEN(anon_sym_nomerge);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1696:
      ACCEPT_TOKEN(anon_sym_unpredictable);
      END_STATE();
    case 1697:
      ACCEPT_TOKEN(anon_sym_unpredictable);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1698:
      ACCEPT_TOKEN(anon_sym_noconvergent);
      END_STATE();
    case 1699:
      ACCEPT_TOKEN(anon_sym_noconvergent);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1700:
      ACCEPT_TOKEN(anon_sym_nneg);
      END_STATE();
    case 1701:
      ACCEPT_TOKEN(anon_sym_nneg);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1702:
      ACCEPT_TOKEN(anon_sym_disjoint);
      END_STATE();
    case 1703:
      ACCEPT_TOKEN(anon_sym_disjoint);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1704:
      ACCEPT_TOKEN(anon_sym_nusw);
      END_STATE();
    case 1705:
      ACCEPT_TOKEN(anon_sym_nusw);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1706:
      ACCEPT_TOKEN(anon_sym_machine_DASHblock_DASHaddress_DASHtaken);
      END_STATE();
    case 1707:
      ACCEPT_TOKEN(anon_sym_landing_DASHpad);
      END_STATE();
    case 1708:
      ACCEPT_TOKEN(anon_sym_inlineasm_DASHbr_DASHindirect_DASHtarget);
      END_STATE();
    case 1709:
      ACCEPT_TOKEN(anon_sym_ehfunclet_DASHentry);
      END_STATE();
    case 1710:
      ACCEPT_TOKEN(anon_sym_ir_DASHblock_DASHaddress_DASHtaken);
      END_STATE();
    case 1711:
      ACCEPT_TOKEN(anon_sym_call_DASHframe_DASHsize);
      END_STATE();
    case 1712:
      ACCEPT_TOKEN(anon_sym_bb_id);
      END_STATE();
    case 1713:
      ACCEPT_TOKEN(anon_sym_bbsections);
      END_STATE();
    case 1714:
      ACCEPT_TOKEN(anon_sym_Exception);
      END_STATE();
    case 1715:
      ACCEPT_TOKEN(anon_sym_Cold);
      END_STATE();
    case 1716:
      ACCEPT_TOKEN(anon_sym_half);
      END_STATE();
    case 1717:
      ACCEPT_TOKEN(anon_sym_half);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1718:
      ACCEPT_TOKEN(anon_sym_bfloat);
      END_STATE();
    case 1719:
      ACCEPT_TOKEN(anon_sym_bfloat);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1720:
      ACCEPT_TOKEN(anon_sym_float);
      if (lookahead == 'p') ADVANCE(1280);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1721:
      ACCEPT_TOKEN(anon_sym_float);
      if (lookahead == 'p') ADVANCE(705);
      END_STATE();
    case 1722:
      ACCEPT_TOKEN(anon_sym_double);
      END_STATE();
    case 1723:
      ACCEPT_TOKEN(anon_sym_double);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1724:
      ACCEPT_TOKEN(anon_sym_x86_fp80);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1725:
      ACCEPT_TOKEN(anon_sym_fp128);
      END_STATE();
    case 1726:
      ACCEPT_TOKEN(anon_sym_fp128);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    case 1727:
      ACCEPT_TOKEN(anon_sym_ppc_fp128);
      END_STATE();
    case 1728:
      ACCEPT_TOKEN(anon_sym_ppc_fp128);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(1400);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 883},
  [2] = {.lex_state = 2},
  [3] = {.lex_state = 2},
  [4] = {.lex_state = 2},
  [5] = {.lex_state = 2},
  [6] = {.lex_state = 2},
  [7] = {.lex_state = 2},
  [8] = {.lex_state = 2},
  [9] = {.lex_state = 2},
  [10] = {.lex_state = 2},
  [11] = {.lex_state = 2},
  [12] = {.lex_state = 2},
  [13] = {.lex_state = 2},
  [14] = {.lex_state = 2},
  [15] = {.lex_state = 2},
  [16] = {.lex_state = 2},
  [17] = {.lex_state = 2},
  [18] = {.lex_state = 2},
  [19] = {.lex_state = 2},
  [20] = {.lex_state = 2},
  [21] = {.lex_state = 2},
  [22] = {.lex_state = 9},
  [23] = {.lex_state = 8},
  [24] = {.lex_state = 8},
  [25] = {.lex_state = 884},
  [26] = {.lex_state = 884},
  [27] = {.lex_state = 884},
  [28] = {.lex_state = 884},
  [29] = {.lex_state = 884},
  [30] = {.lex_state = 884},
  [31] = {.lex_state = 884},
  [32] = {.lex_state = 884},
  [33] = {.lex_state = 885},
  [34] = {.lex_state = 885},
  [35] = {.lex_state = 885},
  [36] = {.lex_state = 885},
  [37] = {.lex_state = 885},
  [38] = {.lex_state = 885},
  [39] = {.lex_state = 885},
  [40] = {.lex_state = 885},
  [41] = {.lex_state = 885},
  [42] = {.lex_state = 885},
  [43] = {.lex_state = 884},
  [44] = {.lex_state = 884},
  [45] = {.lex_state = 884},
  [46] = {.lex_state = 885},
  [47] = {.lex_state = 885},
  [48] = {.lex_state = 885},
  [49] = {.lex_state = 25},
  [50] = {.lex_state = 25},
  [51] = {.lex_state = 25},
  [52] = {.lex_state = 25},
  [53] = {.lex_state = 25},
  [54] = {.lex_state = 25},
  [55] = {.lex_state = 25},
  [56] = {.lex_state = 7},
  [57] = {.lex_state = 23},
  [58] = {.lex_state = 3},
  [59] = {.lex_state = 3},
  [60] = {.lex_state = 3},
  [61] = {.lex_state = 6},
  [62] = {.lex_state = 3},
  [63] = {.lex_state = 3},
  [64] = {.lex_state = 7},
  [65] = {.lex_state = 7},
  [66] = {.lex_state = 3},
  [67] = {.lex_state = 23},
  [68] = {.lex_state = 7},
  [69] = {.lex_state = 3},
  [70] = {.lex_state = 3},
  [71] = {.lex_state = 7},
  [72] = {.lex_state = 23},
  [73] = {.lex_state = 7},
  [74] = {.lex_state = 3},
  [75] = {.lex_state = 7},
  [76] = {.lex_state = 3},
  [77] = {.lex_state = 3},
  [78] = {.lex_state = 3},
  [79] = {.lex_state = 7},
  [80] = {.lex_state = 4},
  [81] = {.lex_state = 4},
  [82] = {.lex_state = 7},
  [83] = {.lex_state = 3},
  [84] = {.lex_state = 3},
  [85] = {.lex_state = 3},
  [86] = {.lex_state = 3},
  [87] = {.lex_state = 7},
  [88] = {.lex_state = 7},
  [89] = {.lex_state = 7},
  [90] = {.lex_state = 3},
  [91] = {.lex_state = 7},
  [92] = {.lex_state = 7},
  [93] = {.lex_state = 3},
  [94] = {.lex_state = 7},
  [95] = {.lex_state = 7},
  [96] = {.lex_state = 7},
  [97] = {.lex_state = 7},
  [98] = {.lex_state = 7},
  [99] = {.lex_state = 7},
  [100] = {.lex_state = 3},
  [101] = {.lex_state = 7},
  [102] = {.lex_state = 7},
  [103] = {.lex_state = 7},
  [104] = {.lex_state = 7},
  [105] = {.lex_state = 7},
  [106] = {.lex_state = 7},
  [107] = {.lex_state = 4},
  [108] = {.lex_state = 3},
  [109] = {.lex_state = 3},
  [110] = {.lex_state = 4},
  [111] = {.lex_state = 3},
  [112] = {.lex_state = 4},
  [113] = {.lex_state = 3},
  [114] = {.lex_state = 3},
  [115] = {.lex_state = 3},
  [116] = {.lex_state = 3},
  [117] = {.lex_state = 3},
  [118] = {.lex_state = 3},
  [119] = {.lex_state = 3},
  [120] = {.lex_state = 3},
  [121] = {.lex_state = 3},
  [122] = {.lex_state = 3},
  [123] = {.lex_state = 3},
  [124] = {.lex_state = 3},
  [125] = {.lex_state = 3},
  [126] = {.lex_state = 3},
  [127] = {.lex_state = 3},
  [128] = {.lex_state = 3},
  [129] = {.lex_state = 3},
  [130] = {.lex_state = 3},
  [131] = {.lex_state = 3},
  [132] = {.lex_state = 3},
  [133] = {.lex_state = 7},
  [134] = {.lex_state = 3},
  [135] = {.lex_state = 3},
  [136] = {.lex_state = 3},
  [137] = {.lex_state = 23},
  [138] = {.lex_state = 23},
  [139] = {.lex_state = 3},
  [140] = {.lex_state = 3},
  [141] = {.lex_state = 23},
  [142] = {.lex_state = 3},
  [143] = {.lex_state = 3},
  [144] = {.lex_state = 23},
  [145] = {.lex_state = 3},
  [146] = {.lex_state = 7},
  [147] = {.lex_state = 3},
  [148] = {.lex_state = 23},
  [149] = {.lex_state = 3},
  [150] = {.lex_state = 3},
  [151] = {.lex_state = 3},
  [152] = {.lex_state = 3},
  [153] = {.lex_state = 3},
  [154] = {.lex_state = 23},
  [155] = {.lex_state = 23},
  [156] = {.lex_state = 3},
  [157] = {.lex_state = 3},
  [158] = {.lex_state = 3},
  [159] = {.lex_state = 7},
  [160] = {.lex_state = 7},
  [161] = {.lex_state = 3},
  [162] = {.lex_state = 3},
  [163] = {.lex_state = 3},
  [164] = {.lex_state = 3},
  [165] = {.lex_state = 23},
  [166] = {.lex_state = 23},
  [167] = {.lex_state = 3},
  [168] = {.lex_state = 3},
  [169] = {.lex_state = 3},
  [170] = {.lex_state = 3},
  [171] = {.lex_state = 7},
  [172] = {.lex_state = 3},
  [173] = {.lex_state = 3},
  [174] = {.lex_state = 3},
  [175] = {.lex_state = 3},
  [176] = {.lex_state = 3},
  [177] = {.lex_state = 7},
  [178] = {.lex_state = 23},
  [179] = {.lex_state = 3},
  [180] = {.lex_state = 24},
  [181] = {.lex_state = 3},
  [182] = {.lex_state = 3},
  [183] = {.lex_state = 3},
  [184] = {.lex_state = 24},
  [185] = {.lex_state = 3},
  [186] = {.lex_state = 3},
  [187] = {.lex_state = 3},
  [188] = {.lex_state = 3},
  [189] = {.lex_state = 3},
  [190] = {.lex_state = 3},
  [191] = {.lex_state = 3},
  [192] = {.lex_state = 3},
  [193] = {.lex_state = 3},
  [194] = {.lex_state = 3},
  [195] = {.lex_state = 3},
  [196] = {.lex_state = 3},
  [197] = {.lex_state = 3},
  [198] = {.lex_state = 3},
  [199] = {.lex_state = 3},
  [200] = {.lex_state = 3},
  [201] = {.lex_state = 4},
  [202] = {.lex_state = 3},
  [203] = {.lex_state = 3},
  [204] = {.lex_state = 3},
  [205] = {.lex_state = 3},
  [206] = {.lex_state = 3},
  [207] = {.lex_state = 3},
  [208] = {.lex_state = 3},
  [209] = {.lex_state = 3},
  [210] = {.lex_state = 24},
  [211] = {.lex_state = 3},
  [212] = {.lex_state = 3},
  [213] = {.lex_state = 24},
  [214] = {.lex_state = 3},
  [215] = {.lex_state = 3},
  [216] = {.lex_state = 3},
  [217] = {.lex_state = 24},
  [218] = {.lex_state = 3},
  [219] = {.lex_state = 3},
  [220] = {.lex_state = 3},
  [221] = {.lex_state = 3},
  [222] = {.lex_state = 3},
  [223] = {.lex_state = 3},
  [224] = {.lex_state = 3},
  [225] = {.lex_state = 3},
  [226] = {.lex_state = 3},
  [227] = {.lex_state = 3},
  [228] = {.lex_state = 3},
  [229] = {.lex_state = 3},
  [230] = {.lex_state = 3},
  [231] = {.lex_state = 3},
  [232] = {.lex_state = 3},
  [233] = {.lex_state = 3},
  [234] = {.lex_state = 3},
  [235] = {.lex_state = 3},
  [236] = {.lex_state = 3},
  [237] = {.lex_state = 3},
  [238] = {.lex_state = 3},
  [239] = {.lex_state = 3},
  [240] = {.lex_state = 3},
  [241] = {.lex_state = 3},
  [242] = {.lex_state = 3},
  [243] = {.lex_state = 3},
  [244] = {.lex_state = 3},
  [245] = {.lex_state = 3},
  [246] = {.lex_state = 24},
  [247] = {.lex_state = 24},
  [248] = {.lex_state = 24},
  [249] = {.lex_state = 24},
  [250] = {.lex_state = 24},
  [251] = {.lex_state = 24},
  [252] = {.lex_state = 24},
  [253] = {.lex_state = 24},
  [254] = {.lex_state = 3},
  [255] = {.lex_state = 24},
  [256] = {.lex_state = 24},
  [257] = {.lex_state = 3},
  [258] = {.lex_state = 3},
  [259] = {.lex_state = 3},
  [260] = {.lex_state = 3},
  [261] = {.lex_state = 0},
  [262] = {.lex_state = 0},
  [263] = {.lex_state = 4},
  [264] = {.lex_state = 0},
  [265] = {.lex_state = 4},
  [266] = {.lex_state = 4},
  [267] = {.lex_state = 0},
  [268] = {.lex_state = 4},
  [269] = {.lex_state = 0},
  [270] = {.lex_state = 4},
  [271] = {.lex_state = 0},
  [272] = {.lex_state = 883},
  [273] = {.lex_state = 883},
  [274] = {.lex_state = 4},
  [275] = {.lex_state = 883},
  [276] = {.lex_state = 0},
  [277] = {.lex_state = 883},
  [278] = {.lex_state = 4},
  [279] = {.lex_state = 0},
  [280] = {.lex_state = 4},
  [281] = {.lex_state = 0},
  [282] = {.lex_state = 883},
  [283] = {.lex_state = 0},
  [284] = {.lex_state = 0},
  [285] = {.lex_state = 883},
  [286] = {.lex_state = 0},
  [287] = {.lex_state = 0},
  [288] = {.lex_state = 0},
  [289] = {.lex_state = 0},
  [290] = {.lex_state = 883},
  [291] = {.lex_state = 883},
  [292] = {.lex_state = 0},
  [293] = {.lex_state = 0},
  [294] = {.lex_state = 0},
  [295] = {.lex_state = 0},
  [296] = {.lex_state = 0},
  [297] = {.lex_state = 0},
  [298] = {.lex_state = 883},
  [299] = {.lex_state = 0},
  [300] = {.lex_state = 0},
  [301] = {.lex_state = 0},
  [302] = {.lex_state = 883},
  [303] = {.lex_state = 0},
  [304] = {.lex_state = 0},
  [305] = {.lex_state = 0},
  [306] = {.lex_state = 883},
  [307] = {.lex_state = 0},
  [308] = {.lex_state = 0},
  [309] = {.lex_state = 0},
  [310] = {.lex_state = 0},
  [311] = {.lex_state = 883},
  [312] = {.lex_state = 883},
  [313] = {.lex_state = 0},
  [314] = {.lex_state = 0},
  [315] = {.lex_state = 0},
  [316] = {.lex_state = 0},
  [317] = {.lex_state = 70},
  [318] = {.lex_state = 883},
  [319] = {.lex_state = 0},
  [320] = {.lex_state = 0},
  [321] = {.lex_state = 883},
  [322] = {.lex_state = 883},
  [323] = {.lex_state = 0},
  [324] = {.lex_state = 883},
  [325] = {.lex_state = 0},
  [326] = {.lex_state = 883},
  [327] = {.lex_state = 0},
  [328] = {.lex_state = 0},
  [329] = {.lex_state = 883},
  [330] = {.lex_state = 0},
  [331] = {.lex_state = 0},
  [332] = {.lex_state = 0},
  [333] = {.lex_state = 29},
  [334] = {.lex_state = 70},
  [335] = {.lex_state = 0},
  [336] = {.lex_state = 883},
  [337] = {.lex_state = 70},
  [338] = {.lex_state = 883},
  [339] = {.lex_state = 0},
  [340] = {.lex_state = 0},
  [341] = {.lex_state = 0},
  [342] = {.lex_state = 883},
  [343] = {.lex_state = 883},
  [344] = {.lex_state = 0},
  [345] = {.lex_state = 0},
  [346] = {.lex_state = 883},
  [347] = {.lex_state = 0},
  [348] = {.lex_state = 883},
  [349] = {.lex_state = 0},
  [350] = {.lex_state = 0},
  [351] = {.lex_state = 883},
  [352] = {.lex_state = 0},
  [353] = {.lex_state = 0},
  [354] = {.lex_state = 0},
  [355] = {.lex_state = 883},
  [356] = {.lex_state = 0},
  [357] = {.lex_state = 0},
  [358] = {.lex_state = 883},
  [359] = {.lex_state = 0},
  [360] = {.lex_state = 883},
  [361] = {.lex_state = 0},
  [362] = {.lex_state = 0},
  [363] = {.lex_state = 883},
  [364] = {.lex_state = 0},
  [365] = {.lex_state = 0},
  [366] = {.lex_state = 883},
  [367] = {.lex_state = 0},
  [368] = {.lex_state = 883},
  [369] = {.lex_state = 0},
  [370] = {.lex_state = 883},
  [371] = {.lex_state = 0},
  [372] = {.lex_state = 883},
  [373] = {.lex_state = 883},
  [374] = {.lex_state = 883},
  [375] = {.lex_state = 0},
  [376] = {.lex_state = 883},
  [377] = {.lex_state = 0},
  [378] = {.lex_state = 0},
  [379] = {.lex_state = 0},
  [380] = {.lex_state = 883},
  [381] = {.lex_state = 0},
  [382] = {.lex_state = 0},
  [383] = {.lex_state = 0},
  [384] = {.lex_state = 883},
  [385] = {.lex_state = 883},
  [386] = {.lex_state = 70},
  [387] = {.lex_state = 0},
  [388] = {.lex_state = 883},
  [389] = {.lex_state = 0},
  [390] = {.lex_state = 0},
  [391] = {.lex_state = 0},
  [392] = {.lex_state = 0},
  [393] = {.lex_state = 0},
  [394] = {.lex_state = 0},
  [395] = {.lex_state = 0},
  [396] = {.lex_state = 0},
  [397] = {.lex_state = 0},
  [398] = {.lex_state = 70},
  [399] = {.lex_state = 0},
  [400] = {.lex_state = 0},
  [401] = {.lex_state = 24},
  [402] = {.lex_state = 71},
  [403] = {.lex_state = 0},
  [404] = {.lex_state = 70},
  [405] = {.lex_state = 24},
  [406] = {.lex_state = 0},
  [407] = {.lex_state = 0},
  [408] = {.lex_state = 883},
  [409] = {.lex_state = 0},
  [410] = {.lex_state = 0},
  [411] = {.lex_state = 883},
  [412] = {.lex_state = 0},
  [413] = {.lex_state = 0},
  [414] = {.lex_state = 24},
  [415] = {.lex_state = 24},
  [416] = {.lex_state = 0},
  [417] = {.lex_state = 0},
  [418] = {.lex_state = 70},
  [419] = {.lex_state = 0},
  [420] = {.lex_state = 0},
  [421] = {.lex_state = 0},
  [422] = {.lex_state = 0},
  [423] = {.lex_state = 0},
  [424] = {.lex_state = 0},
  [425] = {.lex_state = 0},
  [426] = {.lex_state = 0},
  [427] = {.lex_state = 24},
  [428] = {.lex_state = 0},
  [429] = {.lex_state = 883},
  [430] = {.lex_state = 0},
  [431] = {.lex_state = 0},
  [432] = {.lex_state = 0},
  [433] = {.lex_state = 0},
  [434] = {.lex_state = 24},
  [435] = {.lex_state = 29},
  [436] = {.lex_state = 0},
  [437] = {.lex_state = 0},
  [438] = {.lex_state = 0},
  [439] = {.lex_state = 0},
  [440] = {.lex_state = 883},
  [441] = {.lex_state = 0},
  [442] = {.lex_state = 0},
  [443] = {.lex_state = 0},
  [444] = {.lex_state = 0},
  [445] = {.lex_state = 0},
  [446] = {.lex_state = 71},
  [447] = {.lex_state = 0},
  [448] = {.lex_state = 883},
  [449] = {.lex_state = 0},
  [450] = {.lex_state = 0},
  [451] = {.lex_state = 0},
  [452] = {.lex_state = 883},
  [453] = {.lex_state = 0},
  [454] = {.lex_state = 0},
  [455] = {.lex_state = 0},
  [456] = {.lex_state = 0},
  [457] = {.lex_state = 883},
  [458] = {.lex_state = 70},
  [459] = {.lex_state = 24},
  [460] = {.lex_state = 883},
  [461] = {.lex_state = 0},
  [462] = {.lex_state = 0},
  [463] = {.lex_state = 883},
  [464] = {.lex_state = 0},
  [465] = {.lex_state = 0},
  [466] = {.lex_state = 0},
  [467] = {.lex_state = 0},
  [468] = {.lex_state = 0},
  [469] = {.lex_state = 883},
  [470] = {.lex_state = 0},
  [471] = {.lex_state = 70},
  [472] = {.lex_state = 0},
  [473] = {.lex_state = 70},
  [474] = {.lex_state = 0},
  [475] = {.lex_state = 0},
  [476] = {.lex_state = 0},
  [477] = {.lex_state = 0},
  [478] = {.lex_state = 883},
  [479] = {.lex_state = 0},
  [480] = {.lex_state = 883},
  [481] = {.lex_state = 0},
  [482] = {.lex_state = 0},
  [483] = {.lex_state = 0},
  [484] = {.lex_state = 0},
  [485] = {.lex_state = 24},
  [486] = {.lex_state = 2},
  [487] = {.lex_state = 883},
  [488] = {.lex_state = 883},
  [489] = {.lex_state = 0},
  [490] = {.lex_state = 0},
  [491] = {.lex_state = 0},
  [492] = {.lex_state = 0},
  [493] = {.lex_state = 24},
  [494] = {.lex_state = 0},
  [495] = {.lex_state = 24},
  [496] = {.lex_state = 883},
  [497] = {.lex_state = 0},
  [498] = {.lex_state = 0},
  [499] = {.lex_state = 0},
  [500] = {.lex_state = 0},
  [501] = {.lex_state = 0},
  [502] = {.lex_state = 0},
  [503] = {.lex_state = 0},
  [504] = {.lex_state = 883},
  [505] = {.lex_state = 0},
  [506] = {.lex_state = 24},
  [507] = {.lex_state = 883},
  [508] = {.lex_state = 883},
  [509] = {.lex_state = 883},
  [510] = {.lex_state = 0},
  [511] = {.lex_state = 0},
  [512] = {.lex_state = 0},
  [513] = {.lex_state = 883},
  [514] = {.lex_state = 883},
  [515] = {.lex_state = 883},
  [516] = {.lex_state = 0},
  [517] = {.lex_state = 24},
  [518] = {.lex_state = 883},
  [519] = {.lex_state = 0},
  [520] = {.lex_state = 24},
  [521] = {.lex_state = 24},
  [522] = {.lex_state = 2},
  [523] = {.lex_state = 24},
  [524] = {.lex_state = 24},
  [525] = {.lex_state = 0},
  [526] = {.lex_state = 0},
  [527] = {.lex_state = 0},
  [528] = {.lex_state = 883},
  [529] = {.lex_state = 0},
  [530] = {.lex_state = 25},
  [531] = {.lex_state = 883},
  [532] = {.lex_state = 24},
  [533] = {.lex_state = 0},
  [534] = {.lex_state = 883},
  [535] = {.lex_state = 0},
  [536] = {.lex_state = 0},
  [537] = {.lex_state = 0},
  [538] = {.lex_state = 0},
  [539] = {.lex_state = 0},
  [540] = {.lex_state = 0},
  [541] = {.lex_state = 883},
  [542] = {.lex_state = 883},
  [543] = {.lex_state = 0},
  [544] = {.lex_state = 24},
  [545] = {.lex_state = 0},
  [546] = {.lex_state = 24},
  [547] = {.lex_state = 24},
  [548] = {.lex_state = 0},
  [549] = {.lex_state = 24},
  [550] = {.lex_state = 883},
  [551] = {.lex_state = 0},
  [552] = {.lex_state = 0},
  [553] = {.lex_state = 0},
  [554] = {.lex_state = 0},
  [555] = {.lex_state = 24},
  [556] = {.lex_state = 0},
  [557] = {.lex_state = 24},
  [558] = {.lex_state = 0},
  [559] = {.lex_state = 0},
  [560] = {.lex_state = 0},
  [561] = {.lex_state = 0},
  [562] = {.lex_state = 0},
  [563] = {.lex_state = 0},
  [564] = {.lex_state = 24},
  [565] = {.lex_state = 0},
  [566] = {.lex_state = 883},
  [567] = {.lex_state = 24},
  [568] = {.lex_state = 0},
  [569] = {.lex_state = 24},
  [570] = {.lex_state = 24},
  [571] = {.lex_state = 24},
  [572] = {.lex_state = 0},
  [573] = {.lex_state = 0},
  [574] = {.lex_state = 0},
  [575] = {.lex_state = 24},
  [576] = {.lex_state = 883},
  [577] = {.lex_state = 0},
  [578] = {.lex_state = 0},
  [579] = {.lex_state = 0},
  [580] = {.lex_state = 70},
  [581] = {.lex_state = 0},
  [582] = {.lex_state = 0},
  [583] = {.lex_state = 883},
  [584] = {.lex_state = 883},
  [585] = {.lex_state = 70},
  [586] = {.lex_state = 0},
  [587] = {.lex_state = 0},
  [588] = {.lex_state = 24},
  [589] = {.lex_state = 0},
  [590] = {.lex_state = 25},
  [591] = {.lex_state = 24},
  [592] = {.lex_state = 0},
  [593] = {.lex_state = 883},
  [594] = {.lex_state = 0},
  [595] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [sym__newline] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_stack_object] = ACTIONS(1),
    [sym_constant_pool_index] = ACTIONS(1),
    [sym_jump_table_index] = ACTIONS(1),
    [sym_string] = ACTIONS(1),
    [aux_sym_float_token2] = ACTIONS(1),
    [sym_var] = ACTIONS(1),
    [sym_physical_register] = ACTIONS(1),
    [sym_immediate_type] = ACTIONS(1),
    [sym_ir_block] = ACTIONS(1),
    [sym_external_symbol] = ACTIONS(1),
    [sym_global_var] = ACTIONS(1),
    [sym_ir_local_var] = ACTIONS(1),
    [sym_metadata_ref] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_successors] = ACTIONS(1),
    [anon_sym_liveins] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_dbg_DASHinstr_DASHref] = ACTIONS(1),
    [anon_sym_pre_DASHinstr_DASHsymbol] = ACTIONS(1),
    [anon_sym_post_DASHinstr_DASHsymbol] = ACTIONS(1),
    [anon_sym_heap_DASHalloc_DASHmarker] = ACTIONS(1),
    [anon_sym_pcsections] = ACTIONS(1),
    [anon_sym_mmra] = ACTIONS(1),
    [anon_sym_cfi_DASHtype] = ACTIONS(1),
    [anon_sym_debug_DASHinstr_DASHnumber] = ACTIONS(1),
    [anon_sym_debug_DASHlocation] = ACTIONS(1),
    [anon_sym_COLON_COLON] = ACTIONS(1),
    [anon_sym_LT] = ACTIONS(1),
    [anon_sym_mcsymbol] = ACTIONS(1),
    [anon_sym_GT] = ACTIONS(1),
    [anon_sym_LPAREN2] = ACTIONS(1),
    [anon_sym_BANG] = ACTIONS(1),
    [anon_sym_null] = ACTIONS(1),
    [anon_sym_PIPE] = ACTIONS(1),
    [anon_sym_STAR] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [anon_sym_DOT] = ACTIONS(1),
    [anon_sym__] = ACTIONS(1),
    [anon_sym_tied_DASHdef] = ACTIONS(1),
    [anon_sym_target_DASHflags] = ACTIONS(1),
    [sym_primitive_type] = ACTIONS(1),
    [anon_sym_vscale] = ACTIONS(1),
    [anon_sym_x] = ACTIONS(1),
    [anon_sym_CustomRegMask] = ACTIONS(1),
    [anon_sym_same_value] = ACTIONS(1),
    [anon_sym_def_cfa_register] = ACTIONS(1),
    [anon_sym_restore] = ACTIONS(1),
    [anon_sym_undefined] = ACTIONS(1),
    [anon_sym_offset] = ACTIONS(1),
    [anon_sym_rel_offset] = ACTIONS(1),
    [anon_sym_def_cfa] = ACTIONS(1),
    [anon_sym_def_cfa_offset] = ACTIONS(1),
    [anon_sym_adjust_cfa_offset] = ACTIONS(1),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(1),
    [anon_sym_register] = ACTIONS(1),
    [anon_sym_escape] = ACTIONS(1),
    [anon_sym_remember_state] = ACTIONS(1),
    [anon_sym_restore_state] = ACTIONS(1),
    [anon_sym_window_save] = ACTIONS(1),
    [anon_sym_negate_ra_sign_state] = ACTIONS(1),
    [anon_sym_true] = ACTIONS(1),
    [anon_sym_false] = ACTIONS(1),
    [anon_sym_intpred] = ACTIONS(1),
    [anon_sym_floatpred] = ACTIONS(1),
    [anon_sym_eq] = ACTIONS(1),
    [anon_sym_ne] = ACTIONS(1),
    [anon_sym_sgt] = ACTIONS(1),
    [anon_sym_sge] = ACTIONS(1),
    [anon_sym_slt] = ACTIONS(1),
    [anon_sym_sle] = ACTIONS(1),
    [anon_sym_ugt] = ACTIONS(1),
    [anon_sym_uge] = ACTIONS(1),
    [anon_sym_ult] = ACTIONS(1),
    [anon_sym_ule] = ACTIONS(1),
    [anon_sym_oeq] = ACTIONS(1),
    [anon_sym_ogt] = ACTIONS(1),
    [anon_sym_oge] = ACTIONS(1),
    [anon_sym_olt] = ACTIONS(1),
    [anon_sym_ole] = ACTIONS(1),
    [anon_sym_one] = ACTIONS(1),
    [anon_sym_ord] = ACTIONS(1),
    [anon_sym_uno] = ACTIONS(1),
    [anon_sym_ueq] = ACTIONS(1),
    [anon_sym_une] = ACTIONS(1),
    [anon_sym_shufflemask] = ACTIONS(1),
    [anon_sym_undef] = ACTIONS(1),
    [anon_sym_liveout] = ACTIONS(1),
    [anon_sym_target_DASHindex] = ACTIONS(1),
    [anon_sym_blockaddress] = ACTIONS(1),
    [anon_sym_intrinsic] = ACTIONS(1),
    [anon_sym_load] = ACTIONS(1),
    [anon_sym_store] = ACTIONS(1),
    [anon_sym_unknown_DASHsize] = ACTIONS(1),
    [anon_sym_on] = ACTIONS(1),
    [anon_sym_from] = ACTIONS(1),
    [anon_sym_into] = ACTIONS(1),
    [anon_sym_align] = ACTIONS(1),
    [anon_sym_basealign] = ACTIONS(1),
    [anon_sym_addrspace] = ACTIONS(1),
    [anon_sym_unknown_DASHaddress] = ACTIONS(1),
    [anon_sym_BQUOTE] = ACTIONS(1),
    [anon_sym_PLUS] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [anon_sym_call_DASHentry] = ACTIONS(1),
    [anon_sym_custom] = ACTIONS(1),
    [anon_sym_constant_DASHpool] = ACTIONS(1),
    [anon_sym_stack] = ACTIONS(1),
    [anon_sym_got] = ACTIONS(1),
    [anon_sym_jump_DASHtable] = ACTIONS(1),
    [anon_sym_volatile] = ACTIONS(1),
    [anon_sym_non_DASHtemporal] = ACTIONS(1),
    [anon_sym_dereferenceable] = ACTIONS(1),
    [anon_sym_invariant] = ACTIONS(1),
    [anon_sym_syncscope] = ACTIONS(1),
    [anon_sym_unordered] = ACTIONS(1),
    [anon_sym_monotonic] = ACTIONS(1),
    [anon_sym_acquire] = ACTIONS(1),
    [anon_sym_release] = ACTIONS(1),
    [anon_sym_acq_rel] = ACTIONS(1),
    [anon_sym_seq_cst] = ACTIONS(1),
    [anon_sym_implicit] = ACTIONS(1),
    [anon_sym_implicit_DASHdef] = ACTIONS(1),
    [anon_sym_def] = ACTIONS(1),
    [anon_sym_dead] = ACTIONS(1),
    [anon_sym_killed] = ACTIONS(1),
    [anon_sym_internal] = ACTIONS(1),
    [anon_sym_early_DASHclobber] = ACTIONS(1),
    [anon_sym_debug_DASHuse] = ACTIONS(1),
    [anon_sym_renamable] = ACTIONS(1),
    [anon_sym_frame_DASHsetup] = ACTIONS(1),
    [anon_sym_frame_DASHdestroy] = ACTIONS(1),
    [anon_sym_nnan] = ACTIONS(1),
    [anon_sym_ninf] = ACTIONS(1),
    [anon_sym_nsz] = ACTIONS(1),
    [anon_sym_arcp] = ACTIONS(1),
    [anon_sym_contract] = ACTIONS(1),
    [anon_sym_afn] = ACTIONS(1),
    [anon_sym_reassoc] = ACTIONS(1),
    [anon_sym_nuw] = ACTIONS(1),
    [anon_sym_nsw] = ACTIONS(1),
    [anon_sym_exact] = ACTIONS(1),
    [anon_sym_nofpexcept] = ACTIONS(1),
    [anon_sym_nomerge] = ACTIONS(1),
    [anon_sym_unpredictable] = ACTIONS(1),
    [anon_sym_noconvergent] = ACTIONS(1),
    [anon_sym_nneg] = ACTIONS(1),
    [anon_sym_disjoint] = ACTIONS(1),
    [anon_sym_nusw] = ACTIONS(1),
    [anon_sym_machine_DASHblock_DASHaddress_DASHtaken] = ACTIONS(1),
    [anon_sym_landing_DASHpad] = ACTIONS(1),
    [anon_sym_inlineasm_DASHbr_DASHindirect_DASHtarget] = ACTIONS(1),
    [anon_sym_ehfunclet_DASHentry] = ACTIONS(1),
    [anon_sym_ir_DASHblock_DASHaddress_DASHtaken] = ACTIONS(1),
    [anon_sym_call_DASHframe_DASHsize] = ACTIONS(1),
    [anon_sym_bb_id] = ACTIONS(1),
    [anon_sym_bbsections] = ACTIONS(1),
    [anon_sym_Exception] = ACTIONS(1),
    [anon_sym_Cold] = ACTIONS(1),
    [anon_sym_half] = ACTIONS(1),
    [anon_sym_bfloat] = ACTIONS(1),
    [anon_sym_float] = ACTIONS(1),
    [anon_sym_double] = ACTIONS(1),
    [anon_sym_fp128] = ACTIONS(1),
    [anon_sym_ppc_fp128] = ACTIONS(1),
  },
  [1] = {
    [sym_body] = STATE(595),
    [sym_basic_block] = STATE(277),
    [sym_label] = STATE(504),
    [aux_sym_body_repeat1] = STATE(277),
    [ts_builtin_sym_end] = ACTIONS(5),
    [aux_sym_body_token1] = ACTIONS(7),
    [sym__newline] = ACTIONS(9),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(11),
  },
  [2] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_argument] = STATE(132),
    [sym_machine_operand] = STATE(215),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_instruction_repeat4] = STATE(192),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [anon_sym_COMMA] = ACTIONS(13),
    [sym__newline] = ACTIONS(15),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(15),
    [anon_sym_dbg_DASHinstr_DASHref] = ACTIONS(29),
    [anon_sym_pre_DASHinstr_DASHsymbol] = ACTIONS(31),
    [anon_sym_post_DASHinstr_DASHsymbol] = ACTIONS(31),
    [anon_sym_heap_DASHalloc_DASHmarker] = ACTIONS(33),
    [anon_sym_pcsections] = ACTIONS(33),
    [anon_sym_mmra] = ACTIONS(33),
    [anon_sym_cfi_DASHtype] = ACTIONS(35),
    [anon_sym_debug_DASHinstr_DASHnumber] = ACTIONS(35),
    [anon_sym_debug_DASHlocation] = ACTIONS(33),
    [anon_sym_COLON_COLON] = ACTIONS(37),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_target_DASHflags] = ACTIONS(43),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
  [3] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_argument] = STATE(167),
    [sym_machine_operand] = STATE(215),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_instruction_repeat4] = STATE(189),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [anon_sym_COMMA] = ACTIONS(79),
    [sym__newline] = ACTIONS(81),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(81),
    [anon_sym_dbg_DASHinstr_DASHref] = ACTIONS(83),
    [anon_sym_pre_DASHinstr_DASHsymbol] = ACTIONS(31),
    [anon_sym_post_DASHinstr_DASHsymbol] = ACTIONS(31),
    [anon_sym_heap_DASHalloc_DASHmarker] = ACTIONS(33),
    [anon_sym_pcsections] = ACTIONS(33),
    [anon_sym_mmra] = ACTIONS(33),
    [anon_sym_cfi_DASHtype] = ACTIONS(35),
    [anon_sym_debug_DASHinstr_DASHnumber] = ACTIONS(35),
    [anon_sym_debug_DASHlocation] = ACTIONS(33),
    [anon_sym_COLON_COLON] = ACTIONS(85),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_target_DASHflags] = ACTIONS(43),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
  [4] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_argument] = STATE(173),
    [sym_machine_operand] = STATE(215),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_instruction_repeat4] = STATE(188),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [anon_sym_COMMA] = ACTIONS(87),
    [sym__newline] = ACTIONS(89),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(89),
    [anon_sym_dbg_DASHinstr_DASHref] = ACTIONS(91),
    [anon_sym_pre_DASHinstr_DASHsymbol] = ACTIONS(31),
    [anon_sym_post_DASHinstr_DASHsymbol] = ACTIONS(31),
    [anon_sym_heap_DASHalloc_DASHmarker] = ACTIONS(33),
    [anon_sym_pcsections] = ACTIONS(33),
    [anon_sym_mmra] = ACTIONS(33),
    [anon_sym_cfi_DASHtype] = ACTIONS(35),
    [anon_sym_debug_DASHinstr_DASHnumber] = ACTIONS(35),
    [anon_sym_debug_DASHlocation] = ACTIONS(33),
    [anon_sym_COLON_COLON] = ACTIONS(93),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_target_DASHflags] = ACTIONS(43),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
  [5] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_argument] = STATE(156),
    [sym_machine_operand] = STATE(215),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_instruction_repeat4] = STATE(187),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [anon_sym_COMMA] = ACTIONS(95),
    [sym__newline] = ACTIONS(97),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(97),
    [anon_sym_dbg_DASHinstr_DASHref] = ACTIONS(99),
    [anon_sym_pre_DASHinstr_DASHsymbol] = ACTIONS(31),
    [anon_sym_post_DASHinstr_DASHsymbol] = ACTIONS(31),
    [anon_sym_heap_DASHalloc_DASHmarker] = ACTIONS(33),
    [anon_sym_pcsections] = ACTIONS(33),
    [anon_sym_mmra] = ACTIONS(33),
    [anon_sym_cfi_DASHtype] = ACTIONS(35),
    [anon_sym_debug_DASHinstr_DASHnumber] = ACTIONS(35),
    [anon_sym_debug_DASHlocation] = ACTIONS(33),
    [anon_sym_COLON_COLON] = ACTIONS(101),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_target_DASHflags] = ACTIONS(43),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
  [6] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_argument] = STATE(161),
    [sym_machine_operand] = STATE(215),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_instruction_repeat4] = STATE(179),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [anon_sym_COMMA] = ACTIONS(103),
    [sym__newline] = ACTIONS(105),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(105),
    [anon_sym_dbg_DASHinstr_DASHref] = ACTIONS(107),
    [anon_sym_pre_DASHinstr_DASHsymbol] = ACTIONS(31),
    [anon_sym_post_DASHinstr_DASHsymbol] = ACTIONS(31),
    [anon_sym_heap_DASHalloc_DASHmarker] = ACTIONS(33),
    [anon_sym_pcsections] = ACTIONS(33),
    [anon_sym_mmra] = ACTIONS(33),
    [anon_sym_cfi_DASHtype] = ACTIONS(35),
    [anon_sym_debug_DASHinstr_DASHnumber] = ACTIONS(35),
    [anon_sym_debug_DASHlocation] = ACTIONS(33),
    [anon_sym_COLON_COLON] = ACTIONS(109),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_target_DASHflags] = ACTIONS(43),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
  [7] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_argument] = STATE(205),
    [sym_machine_operand] = STATE(215),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [sym__newline] = ACTIONS(111),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(111),
    [anon_sym_dbg_DASHinstr_DASHref] = ACTIONS(113),
    [anon_sym_pre_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_post_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_heap_DASHalloc_DASHmarker] = ACTIONS(117),
    [anon_sym_pcsections] = ACTIONS(117),
    [anon_sym_mmra] = ACTIONS(117),
    [anon_sym_cfi_DASHtype] = ACTIONS(119),
    [anon_sym_debug_DASHinstr_DASHnumber] = ACTIONS(119),
    [anon_sym_debug_DASHlocation] = ACTIONS(117),
    [anon_sym_COLON_COLON] = ACTIONS(121),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_target_DASHflags] = ACTIONS(43),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
  [8] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_argument] = STATE(205),
    [sym_machine_operand] = STATE(215),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [sym__newline] = ACTIONS(123),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(123),
    [anon_sym_dbg_DASHinstr_DASHref] = ACTIONS(113),
    [anon_sym_pre_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_post_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_heap_DASHalloc_DASHmarker] = ACTIONS(117),
    [anon_sym_pcsections] = ACTIONS(117),
    [anon_sym_mmra] = ACTIONS(117),
    [anon_sym_cfi_DASHtype] = ACTIONS(119),
    [anon_sym_debug_DASHinstr_DASHnumber] = ACTIONS(119),
    [anon_sym_debug_DASHlocation] = ACTIONS(117),
    [anon_sym_COLON_COLON] = ACTIONS(125),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_target_DASHflags] = ACTIONS(43),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
  [9] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_argument] = STATE(205),
    [sym_machine_operand] = STATE(215),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [sym__newline] = ACTIONS(127),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(127),
    [anon_sym_dbg_DASHinstr_DASHref] = ACTIONS(113),
    [anon_sym_pre_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_post_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_heap_DASHalloc_DASHmarker] = ACTIONS(117),
    [anon_sym_pcsections] = ACTIONS(117),
    [anon_sym_mmra] = ACTIONS(117),
    [anon_sym_cfi_DASHtype] = ACTIONS(119),
    [anon_sym_debug_DASHinstr_DASHnumber] = ACTIONS(119),
    [anon_sym_debug_DASHlocation] = ACTIONS(117),
    [anon_sym_COLON_COLON] = ACTIONS(129),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_target_DASHflags] = ACTIONS(43),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
  [10] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_argument] = STATE(205),
    [sym_machine_operand] = STATE(215),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [sym__newline] = ACTIONS(131),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(131),
    [anon_sym_dbg_DASHinstr_DASHref] = ACTIONS(113),
    [anon_sym_pre_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_post_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_heap_DASHalloc_DASHmarker] = ACTIONS(117),
    [anon_sym_pcsections] = ACTIONS(117),
    [anon_sym_mmra] = ACTIONS(117),
    [anon_sym_cfi_DASHtype] = ACTIONS(119),
    [anon_sym_debug_DASHinstr_DASHnumber] = ACTIONS(119),
    [anon_sym_debug_DASHlocation] = ACTIONS(117),
    [anon_sym_COLON_COLON] = ACTIONS(133),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_target_DASHflags] = ACTIONS(43),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
  [11] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_argument] = STATE(205),
    [sym_machine_operand] = STATE(215),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [sym__newline] = ACTIONS(135),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(135),
    [anon_sym_dbg_DASHinstr_DASHref] = ACTIONS(113),
    [anon_sym_pre_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_post_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_heap_DASHalloc_DASHmarker] = ACTIONS(117),
    [anon_sym_pcsections] = ACTIONS(117),
    [anon_sym_mmra] = ACTIONS(117),
    [anon_sym_cfi_DASHtype] = ACTIONS(119),
    [anon_sym_debug_DASHinstr_DASHnumber] = ACTIONS(119),
    [anon_sym_debug_DASHlocation] = ACTIONS(117),
    [anon_sym_COLON_COLON] = ACTIONS(137),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_target_DASHflags] = ACTIONS(43),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
  [12] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_argument] = STATE(205),
    [sym_machine_operand] = STATE(215),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [sym__newline] = ACTIONS(139),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(139),
    [anon_sym_dbg_DASHinstr_DASHref] = ACTIONS(113),
    [anon_sym_pre_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_post_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_heap_DASHalloc_DASHmarker] = ACTIONS(117),
    [anon_sym_pcsections] = ACTIONS(117),
    [anon_sym_mmra] = ACTIONS(117),
    [anon_sym_cfi_DASHtype] = ACTIONS(119),
    [anon_sym_debug_DASHinstr_DASHnumber] = ACTIONS(119),
    [anon_sym_debug_DASHlocation] = ACTIONS(117),
    [anon_sym_COLON_COLON] = ACTIONS(141),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_target_DASHflags] = ACTIONS(43),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
  [13] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_argument] = STATE(205),
    [sym_machine_operand] = STATE(215),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [sym__newline] = ACTIONS(143),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(143),
    [anon_sym_dbg_DASHinstr_DASHref] = ACTIONS(113),
    [anon_sym_pre_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_post_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_heap_DASHalloc_DASHmarker] = ACTIONS(117),
    [anon_sym_pcsections] = ACTIONS(117),
    [anon_sym_mmra] = ACTIONS(117),
    [anon_sym_cfi_DASHtype] = ACTIONS(119),
    [anon_sym_debug_DASHinstr_DASHnumber] = ACTIONS(119),
    [anon_sym_debug_DASHlocation] = ACTIONS(117),
    [anon_sym_COLON_COLON] = ACTIONS(145),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_target_DASHflags] = ACTIONS(43),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
  [14] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_argument] = STATE(205),
    [sym_machine_operand] = STATE(215),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [sym__newline] = ACTIONS(147),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(147),
    [anon_sym_dbg_DASHinstr_DASHref] = ACTIONS(113),
    [anon_sym_pre_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_post_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_heap_DASHalloc_DASHmarker] = ACTIONS(117),
    [anon_sym_pcsections] = ACTIONS(117),
    [anon_sym_mmra] = ACTIONS(117),
    [anon_sym_cfi_DASHtype] = ACTIONS(119),
    [anon_sym_debug_DASHinstr_DASHnumber] = ACTIONS(119),
    [anon_sym_debug_DASHlocation] = ACTIONS(117),
    [anon_sym_COLON_COLON] = ACTIONS(149),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_target_DASHflags] = ACTIONS(43),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
  [15] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_argument] = STATE(205),
    [sym_machine_operand] = STATE(215),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [sym__newline] = ACTIONS(151),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(151),
    [anon_sym_dbg_DASHinstr_DASHref] = ACTIONS(113),
    [anon_sym_pre_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_post_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_heap_DASHalloc_DASHmarker] = ACTIONS(117),
    [anon_sym_pcsections] = ACTIONS(117),
    [anon_sym_mmra] = ACTIONS(117),
    [anon_sym_cfi_DASHtype] = ACTIONS(119),
    [anon_sym_debug_DASHinstr_DASHnumber] = ACTIONS(119),
    [anon_sym_debug_DASHlocation] = ACTIONS(117),
    [anon_sym_COLON_COLON] = ACTIONS(153),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_target_DASHflags] = ACTIONS(43),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
  [16] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_argument] = STATE(205),
    [sym_machine_operand] = STATE(215),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [sym__newline] = ACTIONS(155),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(155),
    [anon_sym_dbg_DASHinstr_DASHref] = ACTIONS(113),
    [anon_sym_pre_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_post_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_heap_DASHalloc_DASHmarker] = ACTIONS(117),
    [anon_sym_pcsections] = ACTIONS(117),
    [anon_sym_mmra] = ACTIONS(117),
    [anon_sym_cfi_DASHtype] = ACTIONS(119),
    [anon_sym_debug_DASHinstr_DASHnumber] = ACTIONS(119),
    [anon_sym_debug_DASHlocation] = ACTIONS(117),
    [anon_sym_COLON_COLON] = ACTIONS(157),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_target_DASHflags] = ACTIONS(43),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
  [17] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_argument] = STATE(205),
    [sym_machine_operand] = STATE(215),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [sym__newline] = ACTIONS(159),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(159),
    [anon_sym_dbg_DASHinstr_DASHref] = ACTIONS(113),
    [anon_sym_pre_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_post_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_heap_DASHalloc_DASHmarker] = ACTIONS(117),
    [anon_sym_pcsections] = ACTIONS(117),
    [anon_sym_mmra] = ACTIONS(117),
    [anon_sym_cfi_DASHtype] = ACTIONS(119),
    [anon_sym_debug_DASHinstr_DASHnumber] = ACTIONS(119),
    [anon_sym_debug_DASHlocation] = ACTIONS(117),
    [anon_sym_COLON_COLON] = ACTIONS(161),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_target_DASHflags] = ACTIONS(43),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
  [18] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_argument] = STATE(205),
    [sym_machine_operand] = STATE(215),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [sym__newline] = ACTIONS(163),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(163),
    [anon_sym_dbg_DASHinstr_DASHref] = ACTIONS(113),
    [anon_sym_pre_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_post_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_heap_DASHalloc_DASHmarker] = ACTIONS(117),
    [anon_sym_pcsections] = ACTIONS(117),
    [anon_sym_mmra] = ACTIONS(117),
    [anon_sym_cfi_DASHtype] = ACTIONS(119),
    [anon_sym_debug_DASHinstr_DASHnumber] = ACTIONS(119),
    [anon_sym_debug_DASHlocation] = ACTIONS(117),
    [anon_sym_COLON_COLON] = ACTIONS(165),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_target_DASHflags] = ACTIONS(43),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
  [19] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_argument] = STATE(205),
    [sym_machine_operand] = STATE(215),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [sym__newline] = ACTIONS(167),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(167),
    [anon_sym_dbg_DASHinstr_DASHref] = ACTIONS(113),
    [anon_sym_pre_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_post_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_heap_DASHalloc_DASHmarker] = ACTIONS(117),
    [anon_sym_pcsections] = ACTIONS(117),
    [anon_sym_mmra] = ACTIONS(117),
    [anon_sym_cfi_DASHtype] = ACTIONS(119),
    [anon_sym_debug_DASHinstr_DASHnumber] = ACTIONS(119),
    [anon_sym_debug_DASHlocation] = ACTIONS(117),
    [anon_sym_COLON_COLON] = ACTIONS(169),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_target_DASHflags] = ACTIONS(43),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
  [20] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_argument] = STATE(205),
    [sym_machine_operand] = STATE(215),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [sym__newline] = ACTIONS(171),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(171),
    [anon_sym_dbg_DASHinstr_DASHref] = ACTIONS(113),
    [anon_sym_pre_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_post_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_heap_DASHalloc_DASHmarker] = ACTIONS(117),
    [anon_sym_pcsections] = ACTIONS(117),
    [anon_sym_mmra] = ACTIONS(117),
    [anon_sym_cfi_DASHtype] = ACTIONS(119),
    [anon_sym_debug_DASHinstr_DASHnumber] = ACTIONS(119),
    [anon_sym_debug_DASHlocation] = ACTIONS(117),
    [anon_sym_COLON_COLON] = ACTIONS(173),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_target_DASHflags] = ACTIONS(43),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
  [21] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_argument] = STATE(205),
    [sym_machine_operand] = STATE(215),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [sym__newline] = ACTIONS(175),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(175),
    [anon_sym_dbg_DASHinstr_DASHref] = ACTIONS(113),
    [anon_sym_pre_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_post_DASHinstr_DASHsymbol] = ACTIONS(115),
    [anon_sym_heap_DASHalloc_DASHmarker] = ACTIONS(117),
    [anon_sym_pcsections] = ACTIONS(117),
    [anon_sym_mmra] = ACTIONS(117),
    [anon_sym_cfi_DASHtype] = ACTIONS(119),
    [anon_sym_debug_DASHinstr_DASHnumber] = ACTIONS(119),
    [anon_sym_debug_DASHlocation] = ACTIONS(117),
    [anon_sym_COLON_COLON] = ACTIONS(177),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_target_DASHflags] = ACTIONS(43),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
  [22] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_argument] = STATE(205),
    [sym_machine_operand] = STATE(215),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_dbg_DASHinstr_DASHref] = ACTIONS(113),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_target_DASHflags] = ACTIONS(43),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
  [23] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_machine_operand] = STATE(208),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
  [24] = {
    [sym_mc_symbol] = STATE(113),
    [sym_metadata] = STATE(113),
    [sym_register_operand] = STATE(113),
    [sym_machine_operand] = STATE(212),
    [sym_custom_regmask] = STATE(113),
    [sym_cfi_operand] = STATE(113),
    [sym_immediate] = STATE(113),
    [sym_predicate] = STATE(113),
    [sym_shuffle_mask] = STATE(113),
    [sym_liveout] = STATE(113),
    [sym_target_index] = STATE(113),
    [sym_block_address] = STATE(113),
    [sym_intrinsic] = STATE(113),
    [sym_register_flag] = STATE(107),
    [sym_float_keyword] = STATE(333),
    [aux_sym_register_operand_repeat1] = STATE(107),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(17),
    [sym_mnemonic] = ACTIONS(17),
    [sym_bb_ref] = ACTIONS(19),
    [sym_stack_object] = ACTIONS(19),
    [sym_constant_pool_index] = ACTIONS(19),
    [sym_jump_table_index] = ACTIONS(19),
    [sym_number] = ACTIONS(17),
    [sym_var] = ACTIONS(21),
    [sym_physical_register] = ACTIONS(23),
    [sym_immediate_type] = ACTIONS(25),
    [sym_external_symbol] = ACTIONS(19),
    [sym_global_var] = ACTIONS(19),
    [sym_metadata_ref] = ACTIONS(27),
    [anon_sym_LT] = ACTIONS(39),
    [anon_sym__] = ACTIONS(41),
    [anon_sym_CustomRegMask] = ACTIONS(45),
    [anon_sym_same_value] = ACTIONS(47),
    [anon_sym_def_cfa_register] = ACTIONS(47),
    [anon_sym_restore] = ACTIONS(47),
    [anon_sym_undefined] = ACTIONS(47),
    [anon_sym_offset] = ACTIONS(49),
    [anon_sym_rel_offset] = ACTIONS(49),
    [anon_sym_def_cfa] = ACTIONS(49),
    [anon_sym_def_cfa_offset] = ACTIONS(51),
    [anon_sym_adjust_cfa_offset] = ACTIONS(51),
    [anon_sym_llvm_def_aspace_cfa] = ACTIONS(53),
    [anon_sym_register] = ACTIONS(55),
    [anon_sym_escape] = ACTIONS(57),
    [anon_sym_remember_state] = ACTIONS(59),
    [anon_sym_restore_state] = ACTIONS(59),
    [anon_sym_window_save] = ACTIONS(59),
    [anon_sym_negate_ra_sign_state] = ACTIONS(59),
    [anon_sym_intpred] = ACTIONS(61),
    [anon_sym_floatpred] = ACTIONS(63),
    [anon_sym_shufflemask] = ACTIONS(65),
    [anon_sym_undef] = ACTIONS(67),
    [anon_sym_liveout] = ACTIONS(69),
    [anon_sym_target_DASHindex] = ACTIONS(71),
    [anon_sym_blockaddress] = ACTIONS(73),
    [anon_sym_intrinsic] = ACTIONS(75),
    [anon_sym_implicit] = ACTIONS(67),
    [anon_sym_implicit_DASHdef] = ACTIONS(67),
    [anon_sym_def] = ACTIONS(67),
    [anon_sym_dead] = ACTIONS(67),
    [anon_sym_killed] = ACTIONS(67),
    [anon_sym_internal] = ACTIONS(67),
    [anon_sym_early_DASHclobber] = ACTIONS(67),
    [anon_sym_debug_DASHuse] = ACTIONS(67),
    [anon_sym_renamable] = ACTIONS(67),
    [anon_sym_half] = ACTIONS(77),
    [anon_sym_bfloat] = ACTIONS(77),
    [anon_sym_float] = ACTIONS(77),
    [anon_sym_double] = ACTIONS(77),
    [anon_sym_x86_fp80] = ACTIONS(77),
    [anon_sym_fp128] = ACTIONS(77),
    [anon_sym_ppc_fp128] = ACTIONS(77),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 18,
    ACTIONS(23), 1,
      sym_physical_register,
    ACTIONS(41), 1,
      anon_sym__,
    ACTIONS(179), 1,
      ts_builtin_sym_end,
    ACTIONS(181), 1,
      sym__newline,
    ACTIONS(184), 1,
      sym_identifier,
    ACTIONS(187), 1,
      sym_var,
    ACTIONS(189), 1,
      anon_sym_successors,
    ACTIONS(191), 1,
      anon_sym_liveins,
    STATE(41), 1,
      aux_sym_basic_block_repeat3,
    STATE(43), 1,
      aux_sym_basic_block_repeat2,
    STATE(409), 1,
      sym_instruction,
    STATE(410), 1,
      sym_register_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(53), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    STATE(112), 2,
      sym_register_flag,
      aux_sym_register_operand_repeat1,
    STATE(582), 2,
      sym_successors,
      sym_liveins,
    ACTIONS(67), 10,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
    ACTIONS(193), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [86] = 18,
    ACTIONS(23), 1,
      sym_physical_register,
    ACTIONS(41), 1,
      anon_sym__,
    ACTIONS(187), 1,
      sym_var,
    ACTIONS(189), 1,
      anon_sym_successors,
    ACTIONS(191), 1,
      anon_sym_liveins,
    ACTIONS(195), 1,
      ts_builtin_sym_end,
    ACTIONS(197), 1,
      sym__newline,
    ACTIONS(200), 1,
      sym_identifier,
    STATE(34), 1,
      aux_sym_basic_block_repeat3,
    STATE(43), 1,
      aux_sym_basic_block_repeat2,
    STATE(409), 1,
      sym_instruction,
    STATE(410), 1,
      sym_register_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(53), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    STATE(112), 2,
      sym_register_flag,
      aux_sym_register_operand_repeat1,
    STATE(582), 2,
      sym_successors,
      sym_liveins,
    ACTIONS(67), 10,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
    ACTIONS(193), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [172] = 18,
    ACTIONS(23), 1,
      sym_physical_register,
    ACTIONS(41), 1,
      anon_sym__,
    ACTIONS(187), 1,
      sym_var,
    ACTIONS(189), 1,
      anon_sym_successors,
    ACTIONS(191), 1,
      anon_sym_liveins,
    ACTIONS(203), 1,
      ts_builtin_sym_end,
    ACTIONS(205), 1,
      sym__newline,
    ACTIONS(208), 1,
      sym_identifier,
    STATE(33), 1,
      aux_sym_basic_block_repeat3,
    STATE(43), 1,
      aux_sym_basic_block_repeat2,
    STATE(409), 1,
      sym_instruction,
    STATE(410), 1,
      sym_register_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(53), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    STATE(112), 2,
      sym_register_flag,
      aux_sym_register_operand_repeat1,
    STATE(582), 2,
      sym_successors,
      sym_liveins,
    ACTIONS(67), 10,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
    ACTIONS(193), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [258] = 18,
    ACTIONS(23), 1,
      sym_physical_register,
    ACTIONS(41), 1,
      anon_sym__,
    ACTIONS(179), 1,
      ts_builtin_sym_end,
    ACTIONS(181), 1,
      sym__newline,
    ACTIONS(184), 1,
      sym_identifier,
    ACTIONS(187), 1,
      sym_var,
    ACTIONS(189), 1,
      anon_sym_successors,
    ACTIONS(191), 1,
      anon_sym_liveins,
    STATE(26), 1,
      aux_sym_basic_block_repeat2,
    STATE(41), 1,
      aux_sym_basic_block_repeat3,
    STATE(409), 1,
      sym_instruction,
    STATE(410), 1,
      sym_register_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(53), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    STATE(112), 2,
      sym_register_flag,
      aux_sym_register_operand_repeat1,
    STATE(582), 2,
      sym_successors,
      sym_liveins,
    ACTIONS(67), 10,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
    ACTIONS(193), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [344] = 18,
    ACTIONS(23), 1,
      sym_physical_register,
    ACTIONS(41), 1,
      anon_sym__,
    ACTIONS(187), 1,
      sym_var,
    ACTIONS(189), 1,
      anon_sym_successors,
    ACTIONS(191), 1,
      anon_sym_liveins,
    ACTIONS(211), 1,
      ts_builtin_sym_end,
    ACTIONS(213), 1,
      sym__newline,
    ACTIONS(216), 1,
      sym_identifier,
    STATE(30), 1,
      aux_sym_basic_block_repeat2,
    STATE(39), 1,
      aux_sym_basic_block_repeat3,
    STATE(409), 1,
      sym_instruction,
    STATE(410), 1,
      sym_register_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(53), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    STATE(112), 2,
      sym_register_flag,
      aux_sym_register_operand_repeat1,
    STATE(582), 2,
      sym_successors,
      sym_liveins,
    ACTIONS(67), 10,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
    ACTIONS(193), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [430] = 18,
    ACTIONS(23), 1,
      sym_physical_register,
    ACTIONS(41), 1,
      anon_sym__,
    ACTIONS(187), 1,
      sym_var,
    ACTIONS(189), 1,
      anon_sym_successors,
    ACTIONS(191), 1,
      anon_sym_liveins,
    ACTIONS(219), 1,
      ts_builtin_sym_end,
    ACTIONS(221), 1,
      sym__newline,
    ACTIONS(224), 1,
      sym_identifier,
    STATE(38), 1,
      aux_sym_basic_block_repeat3,
    STATE(43), 1,
      aux_sym_basic_block_repeat2,
    STATE(409), 1,
      sym_instruction,
    STATE(410), 1,
      sym_register_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(53), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    STATE(112), 2,
      sym_register_flag,
      aux_sym_register_operand_repeat1,
    STATE(582), 2,
      sym_successors,
      sym_liveins,
    ACTIONS(67), 10,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
    ACTIONS(193), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [516] = 18,
    ACTIONS(23), 1,
      sym_physical_register,
    ACTIONS(41), 1,
      anon_sym__,
    ACTIONS(187), 1,
      sym_var,
    ACTIONS(189), 1,
      anon_sym_successors,
    ACTIONS(191), 1,
      anon_sym_liveins,
    ACTIONS(203), 1,
      ts_builtin_sym_end,
    ACTIONS(205), 1,
      sym__newline,
    ACTIONS(208), 1,
      sym_identifier,
    STATE(25), 1,
      aux_sym_basic_block_repeat2,
    STATE(33), 1,
      aux_sym_basic_block_repeat3,
    STATE(409), 1,
      sym_instruction,
    STATE(410), 1,
      sym_register_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(53), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    STATE(112), 2,
      sym_register_flag,
      aux_sym_register_operand_repeat1,
    STATE(582), 2,
      sym_successors,
      sym_liveins,
    ACTIONS(67), 10,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
    ACTIONS(193), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [602] = 18,
    ACTIONS(23), 1,
      sym_physical_register,
    ACTIONS(41), 1,
      anon_sym__,
    ACTIONS(187), 1,
      sym_var,
    ACTIONS(189), 1,
      anon_sym_successors,
    ACTIONS(191), 1,
      anon_sym_liveins,
    ACTIONS(227), 1,
      ts_builtin_sym_end,
    ACTIONS(229), 1,
      sym__newline,
    ACTIONS(232), 1,
      sym_identifier,
    STATE(27), 1,
      aux_sym_basic_block_repeat2,
    STATE(40), 1,
      aux_sym_basic_block_repeat3,
    STATE(409), 1,
      sym_instruction,
    STATE(410), 1,
      sym_register_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(53), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    STATE(112), 2,
      sym_register_flag,
      aux_sym_register_operand_repeat1,
    STATE(582), 2,
      sym_successors,
      sym_liveins,
    ACTIONS(67), 10,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
    ACTIONS(193), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [688] = 14,
    ACTIONS(23), 1,
      sym_physical_register,
    ACTIONS(41), 1,
      anon_sym__,
    ACTIONS(179), 1,
      ts_builtin_sym_end,
    ACTIONS(184), 1,
      sym_identifier,
    ACTIONS(187), 1,
      sym_var,
    ACTIONS(235), 1,
      sym__newline,
    STATE(35), 1,
      aux_sym_basic_block_repeat3,
    STATE(409), 1,
      sym_instruction,
    STATE(410), 1,
      sym_register_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(53), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    STATE(112), 2,
      sym_register_flag,
      aux_sym_register_operand_repeat1,
    ACTIONS(67), 10,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
    ACTIONS(193), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [761] = 14,
    ACTIONS(23), 1,
      sym_physical_register,
    ACTIONS(41), 1,
      anon_sym__,
    ACTIONS(187), 1,
      sym_var,
    ACTIONS(238), 1,
      ts_builtin_sym_end,
    ACTIONS(240), 1,
      sym__newline,
    ACTIONS(243), 1,
      sym_identifier,
    STATE(35), 1,
      aux_sym_basic_block_repeat3,
    STATE(409), 1,
      sym_instruction,
    STATE(410), 1,
      sym_register_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(53), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    STATE(112), 2,
      sym_register_flag,
      aux_sym_register_operand_repeat1,
    ACTIONS(67), 10,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
    ACTIONS(193), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [834] = 14,
    ACTIONS(246), 1,
      ts_builtin_sym_end,
    ACTIONS(248), 1,
      sym__newline,
    ACTIONS(251), 1,
      sym_identifier,
    ACTIONS(254), 1,
      sym_var,
    ACTIONS(257), 1,
      sym_physical_register,
    ACTIONS(260), 1,
      anon_sym__,
    STATE(35), 1,
      aux_sym_basic_block_repeat3,
    STATE(409), 1,
      sym_instruction,
    STATE(410), 1,
      sym_register_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(53), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    STATE(112), 2,
      sym_register_flag,
      aux_sym_register_operand_repeat1,
    ACTIONS(263), 10,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
    ACTIONS(266), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [907] = 14,
    ACTIONS(23), 1,
      sym_physical_register,
    ACTIONS(41), 1,
      anon_sym__,
    ACTIONS(187), 1,
      sym_var,
    ACTIONS(269), 1,
      sym__newline,
    ACTIONS(271), 1,
      sym_identifier,
    ACTIONS(273), 1,
      anon_sym_RBRACE,
    STATE(37), 1,
      aux_sym_bundle_repeat1,
    STATE(410), 1,
      sym_register_operand,
    STATE(586), 1,
      sym_instruction,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(53), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    STATE(112), 2,
      sym_register_flag,
      aux_sym_register_operand_repeat1,
    ACTIONS(67), 10,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
    ACTIONS(193), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [980] = 14,
    ACTIONS(275), 1,
      sym__newline,
    ACTIONS(278), 1,
      sym_identifier,
    ACTIONS(281), 1,
      sym_var,
    ACTIONS(284), 1,
      sym_physical_register,
    ACTIONS(287), 1,
      anon_sym_RBRACE,
    ACTIONS(289), 1,
      anon_sym__,
    STATE(37), 1,
      aux_sym_bundle_repeat1,
    STATE(410), 1,
      sym_register_operand,
    STATE(586), 1,
      sym_instruction,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(53), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    STATE(112), 2,
      sym_register_flag,
      aux_sym_register_operand_repeat1,
    ACTIONS(292), 10,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
    ACTIONS(295), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [1053] = 14,
    ACTIONS(23), 1,
      sym_physical_register,
    ACTIONS(41), 1,
      anon_sym__,
    ACTIONS(187), 1,
      sym_var,
    ACTIONS(227), 1,
      ts_builtin_sym_end,
    ACTIONS(232), 1,
      sym_identifier,
    ACTIONS(298), 1,
      sym__newline,
    STATE(35), 1,
      aux_sym_basic_block_repeat3,
    STATE(409), 1,
      sym_instruction,
    STATE(410), 1,
      sym_register_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(53), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    STATE(112), 2,
      sym_register_flag,
      aux_sym_register_operand_repeat1,
    ACTIONS(67), 10,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
    ACTIONS(193), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [1126] = 14,
    ACTIONS(23), 1,
      sym_physical_register,
    ACTIONS(41), 1,
      anon_sym__,
    ACTIONS(187), 1,
      sym_var,
    ACTIONS(219), 1,
      ts_builtin_sym_end,
    ACTIONS(224), 1,
      sym_identifier,
    ACTIONS(301), 1,
      sym__newline,
    STATE(35), 1,
      aux_sym_basic_block_repeat3,
    STATE(409), 1,
      sym_instruction,
    STATE(410), 1,
      sym_register_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(53), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    STATE(112), 2,
      sym_register_flag,
      aux_sym_register_operand_repeat1,
    ACTIONS(67), 10,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
    ACTIONS(193), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [1199] = 14,
    ACTIONS(23), 1,
      sym_physical_register,
    ACTIONS(41), 1,
      anon_sym__,
    ACTIONS(187), 1,
      sym_var,
    ACTIONS(203), 1,
      ts_builtin_sym_end,
    ACTIONS(208), 1,
      sym_identifier,
    ACTIONS(304), 1,
      sym__newline,
    STATE(35), 1,
      aux_sym_basic_block_repeat3,
    STATE(409), 1,
      sym_instruction,
    STATE(410), 1,
      sym_register_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(53), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    STATE(112), 2,
      sym_register_flag,
      aux_sym_register_operand_repeat1,
    ACTIONS(67), 10,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
    ACTIONS(193), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [1272] = 14,
    ACTIONS(23), 1,
      sym_physical_register,
    ACTIONS(41), 1,
      anon_sym__,
    ACTIONS(187), 1,
      sym_var,
    ACTIONS(195), 1,
      ts_builtin_sym_end,
    ACTIONS(200), 1,
      sym_identifier,
    ACTIONS(307), 1,
      sym__newline,
    STATE(35), 1,
      aux_sym_basic_block_repeat3,
    STATE(409), 1,
      sym_instruction,
    STATE(410), 1,
      sym_register_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(53), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    STATE(112), 2,
      sym_register_flag,
      aux_sym_register_operand_repeat1,
    ACTIONS(67), 10,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
    ACTIONS(193), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [1345] = 14,
    ACTIONS(23), 1,
      sym_physical_register,
    ACTIONS(41), 1,
      anon_sym__,
    ACTIONS(187), 1,
      sym_var,
    ACTIONS(271), 1,
      sym_identifier,
    ACTIONS(310), 1,
      sym__newline,
    ACTIONS(312), 1,
      anon_sym_RBRACE,
    STATE(36), 1,
      aux_sym_bundle_repeat1,
    STATE(410), 1,
      sym_register_operand,
    STATE(586), 1,
      sym_instruction,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(53), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    STATE(112), 2,
      sym_register_flag,
      aux_sym_register_operand_repeat1,
    ACTIONS(67), 10,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
    ACTIONS(193), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [1418] = 8,
    ACTIONS(316), 1,
      sym__newline,
    ACTIONS(321), 1,
      anon_sym_successors,
    ACTIONS(324), 1,
      anon_sym_liveins,
    STATE(43), 1,
      aux_sym_basic_block_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(582), 2,
      sym_successors,
      sym_liveins,
    ACTIONS(314), 3,
      ts_builtin_sym_end,
      sym_var,
      sym_physical_register,
    ACTIONS(319), 31,
      sym_identifier,
      anon_sym__,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [1477] = 3,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(314), 4,
      ts_builtin_sym_end,
      sym__newline,
      sym_var,
      sym_physical_register,
    ACTIONS(319), 33,
      sym_identifier,
      anon_sym_successors,
      anon_sym_liveins,
      anon_sym__,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [1523] = 4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(333), 2,
      anon_sym_successors,
      anon_sym_liveins,
    ACTIONS(327), 4,
      ts_builtin_sym_end,
      sym__newline,
      sym_var,
      sym_physical_register,
    ACTIONS(330), 31,
      sym_identifier,
      anon_sym__,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [1571] = 3,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(246), 4,
      ts_builtin_sym_end,
      sym__newline,
      sym_var,
      sym_physical_register,
    ACTIONS(335), 31,
      sym_identifier,
      anon_sym__,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [1615] = 3,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(287), 4,
      sym__newline,
      sym_var,
      sym_physical_register,
      anon_sym_RBRACE,
    ACTIONS(337), 31,
      sym_identifier,
      anon_sym__,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [1659] = 3,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(339), 4,
      ts_builtin_sym_end,
      sym__newline,
      sym_var,
      sym_physical_register,
    ACTIONS(341), 31,
      sym_identifier,
      anon_sym__,
      anon_sym_undef,
      anon_sym_implicit,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [1703] = 4,
    ACTIONS(343), 1,
      sym_identifier,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(54), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    ACTIONS(193), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [1736] = 4,
    ACTIONS(345), 1,
      sym_identifier,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(50), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    ACTIONS(347), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [1769] = 4,
    ACTIONS(350), 1,
      sym_identifier,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(50), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    ACTIONS(193), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [1802] = 4,
    ACTIONS(352), 1,
      sym_identifier,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(51), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    ACTIONS(193), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [1835] = 4,
    ACTIONS(354), 1,
      sym_identifier,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(50), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    ACTIONS(193), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [1868] = 4,
    ACTIONS(352), 1,
      sym_identifier,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(50), 2,
      sym_instruction_flag,
      aux_sym_instruction_repeat2,
    ACTIONS(193), 19,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [1901] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(356), 20,
      sym_identifier,
      anon_sym_frame_DASHsetup,
      anon_sym_frame_DASHdestroy,
      anon_sym_nnan,
      anon_sym_ninf,
      anon_sym_nsz,
      anon_sym_arcp,
      anon_sym_contract,
      anon_sym_afn,
      anon_sym_reassoc,
      anon_sym_nuw,
      anon_sym_nsw,
      anon_sym_exact,
      anon_sym_nofpexcept,
      anon_sym_nomerge,
      anon_sym_unpredictable,
      anon_sym_noconvergent,
      anon_sym_nneg,
      anon_sym_disjoint,
      anon_sym_nusw,
  [1928] = 12,
    ACTIONS(358), 1,
      anon_sym_LPAREN,
    ACTIONS(366), 1,
      sym_metadata_ref,
    ACTIONS(369), 1,
      anon_sym_LBRACE,
    ACTIONS(372), 1,
      anon_sym_LT,
    ACTIONS(375), 1,
      anon_sym_BANG,
    ACTIONS(381), 1,
      anon_sym_LBRACK,
    STATE(88), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(378), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    STATE(56), 2,
      sym_md_value,
      aux_sym_metadata_repeat1,
    ACTIONS(361), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
    ACTIONS(364), 4,
      anon_sym_RPAREN,
      anon_sym_RBRACE,
      anon_sym_GT,
      anon_sym_RBRACK,
  [1974] = 9,
    ACTIONS(384), 1,
      anon_sym_LPAREN,
    ACTIONS(395), 1,
      anon_sym_LBRACE,
    ACTIONS(398), 1,
      anon_sym_LT,
    ACTIONS(401), 1,
      anon_sym_LBRACK,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(392), 2,
      sym_identifier,
      sym_number,
    STATE(57), 2,
      sym__escaped_ir_content,
      aux_sym_escaped_ir_value_repeat1,
    ACTIONS(387), 5,
      anon_sym_COMMA,
      sym_immediate_type,
      sym_global_var,
      sym_ir_local_var,
      anon_sym_STAR,
    ACTIONS(390), 5,
      anon_sym_RPAREN,
      anon_sym_RBRACE,
      anon_sym_GT,
      anon_sym_RBRACK,
      anon_sym_BQUOTE,
  [2013] = 4,
    ACTIONS(404), 1,
      anon_sym_LPAREN,
    ACTIONS(408), 1,
      anon_sym_DOT,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(406), 15,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_EQ,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [2041] = 4,
    ACTIONS(410), 1,
      anon_sym_LPAREN,
    ACTIONS(414), 1,
      anon_sym_DOT,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(412), 15,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_EQ,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [2069] = 3,
    STATE(562), 1,
      sym_floatpred,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(416), 16,
      anon_sym_true,
      anon_sym_false,
      anon_sym_ugt,
      anon_sym_uge,
      anon_sym_ult,
      anon_sym_ule,
      anon_sym_oeq,
      anon_sym_ogt,
      anon_sym_oge,
      anon_sym_olt,
      anon_sym_ole,
      anon_sym_one,
      anon_sym_ord,
      anon_sym_uno,
      anon_sym_ueq,
      anon_sym_une,
  [2095] = 4,
    ACTIONS(422), 1,
      anon_sym_LPAREN2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(418), 4,
      anon_sym_LPAREN,
      anon_sym_BANG,
      anon_sym_null,
      aux_sym_md_value_token1,
    ACTIONS(420), 12,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_COLON,
      sym_metadata_ref,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_STAR,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
  [2123] = 12,
    ACTIONS(424), 1,
      sym_stack_object,
    ACTIONS(428), 1,
      sym_ir_local_var,
    ACTIONS(430), 1,
      anon_sym_BQUOTE,
    ACTIONS(432), 1,
      anon_sym_call_DASHentry,
    ACTIONS(434), 1,
      anon_sym_custom,
    STATE(279), 1,
      sym_machine_pointer_info,
    STATE(389), 1,
      sym_memory_pseudo_source_value_keyword,
    STATE(390), 1,
      sym_escaped_ir_value,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(426), 2,
      sym_global_var,
      anon_sym_unknown_DASHaddress,
    STATE(283), 2,
      sym_ir_value,
      sym_memory_pseudo_source_value,
    ACTIONS(436), 4,
      anon_sym_constant_DASHpool,
      anon_sym_stack,
      anon_sym_got,
      anon_sym_jump_DASHtable,
  [2166] = 3,
    ACTIONS(410), 1,
      anon_sym_LPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(412), 15,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_EQ,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [2191] = 12,
    ACTIONS(438), 1,
      anon_sym_LPAREN,
    ACTIONS(442), 1,
      sym_metadata_ref,
    ACTIONS(444), 1,
      anon_sym_LBRACE,
    ACTIONS(446), 1,
      anon_sym_LT,
    ACTIONS(448), 1,
      anon_sym_BANG,
    ACTIONS(452), 1,
      anon_sym_LBRACK,
    ACTIONS(454), 1,
      anon_sym_RBRACK,
    STATE(88), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(450), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    STATE(56), 2,
      sym_md_value,
      aux_sym_metadata_repeat1,
    ACTIONS(440), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [2234] = 12,
    ACTIONS(438), 1,
      anon_sym_LPAREN,
    ACTIONS(442), 1,
      sym_metadata_ref,
    ACTIONS(444), 1,
      anon_sym_LBRACE,
    ACTIONS(446), 1,
      anon_sym_LT,
    ACTIONS(448), 1,
      anon_sym_BANG,
    ACTIONS(452), 1,
      anon_sym_LBRACK,
    ACTIONS(454), 1,
      anon_sym_GT,
    STATE(88), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(450), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    STATE(56), 2,
      sym_md_value,
      aux_sym_metadata_repeat1,
    ACTIONS(440), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [2277] = 12,
    ACTIONS(424), 1,
      sym_stack_object,
    ACTIONS(428), 1,
      sym_ir_local_var,
    ACTIONS(430), 1,
      anon_sym_BQUOTE,
    ACTIONS(432), 1,
      anon_sym_call_DASHentry,
    ACTIONS(434), 1,
      anon_sym_custom,
    STATE(276), 1,
      sym_machine_pointer_info,
    STATE(389), 1,
      sym_memory_pseudo_source_value_keyword,
    STATE(390), 1,
      sym_escaped_ir_value,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(426), 2,
      sym_global_var,
      anon_sym_unknown_DASHaddress,
    STATE(283), 2,
      sym_ir_value,
      sym_memory_pseudo_source_value,
    ACTIONS(436), 4,
      anon_sym_constant_DASHpool,
      anon_sym_stack,
      anon_sym_got,
      anon_sym_jump_DASHtable,
  [2320] = 3,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(458), 2,
      sym_identifier,
      sym_number,
    ACTIONS(456), 14,
      anon_sym_LPAREN,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      sym_immediate_type,
      sym_global_var,
      sym_ir_local_var,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_STAR,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_BQUOTE,
  [2345] = 12,
    ACTIONS(438), 1,
      anon_sym_LPAREN,
    ACTIONS(442), 1,
      sym_metadata_ref,
    ACTIONS(444), 1,
      anon_sym_LBRACE,
    ACTIONS(446), 1,
      anon_sym_LT,
    ACTIONS(448), 1,
      anon_sym_BANG,
    ACTIONS(452), 1,
      anon_sym_LBRACK,
    ACTIONS(454), 1,
      anon_sym_RBRACE,
    STATE(88), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(450), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    STATE(56), 2,
      sym_md_value,
      aux_sym_metadata_repeat1,
    ACTIONS(440), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [2388] = 12,
    ACTIONS(424), 1,
      sym_stack_object,
    ACTIONS(428), 1,
      sym_ir_local_var,
    ACTIONS(430), 1,
      anon_sym_BQUOTE,
    ACTIONS(432), 1,
      anon_sym_call_DASHentry,
    ACTIONS(434), 1,
      anon_sym_custom,
    STATE(262), 1,
      sym_machine_pointer_info,
    STATE(389), 1,
      sym_memory_pseudo_source_value_keyword,
    STATE(390), 1,
      sym_escaped_ir_value,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(426), 2,
      sym_global_var,
      anon_sym_unknown_DASHaddress,
    STATE(283), 2,
      sym_ir_value,
      sym_memory_pseudo_source_value,
    ACTIONS(436), 4,
      anon_sym_constant_DASHpool,
      anon_sym_stack,
      anon_sym_got,
      anon_sym_jump_DASHtable,
  [2431] = 12,
    ACTIONS(424), 1,
      sym_stack_object,
    ACTIONS(428), 1,
      sym_ir_local_var,
    ACTIONS(430), 1,
      anon_sym_BQUOTE,
    ACTIONS(432), 1,
      anon_sym_call_DASHentry,
    ACTIONS(434), 1,
      anon_sym_custom,
    STATE(264), 1,
      sym_machine_pointer_info,
    STATE(389), 1,
      sym_memory_pseudo_source_value_keyword,
    STATE(390), 1,
      sym_escaped_ir_value,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(426), 2,
      sym_global_var,
      anon_sym_unknown_DASHaddress,
    STATE(283), 2,
      sym_ir_value,
      sym_memory_pseudo_source_value,
    ACTIONS(436), 4,
      anon_sym_constant_DASHpool,
      anon_sym_stack,
      anon_sym_got,
      anon_sym_jump_DASHtable,
  [2474] = 12,
    ACTIONS(438), 1,
      anon_sym_LPAREN,
    ACTIONS(442), 1,
      sym_metadata_ref,
    ACTIONS(444), 1,
      anon_sym_LBRACE,
    ACTIONS(446), 1,
      anon_sym_LT,
    ACTIONS(448), 1,
      anon_sym_BANG,
    ACTIONS(452), 1,
      anon_sym_LBRACK,
    ACTIONS(460), 1,
      anon_sym_RBRACK,
    STATE(88), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(450), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    STATE(56), 2,
      sym_md_value,
      aux_sym_metadata_repeat1,
    ACTIONS(440), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [2517] = 3,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(464), 2,
      sym_identifier,
      sym_number,
    ACTIONS(462), 14,
      anon_sym_LPAREN,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      sym_immediate_type,
      sym_global_var,
      sym_ir_local_var,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_STAR,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_BQUOTE,
  [2542] = 12,
    ACTIONS(438), 1,
      anon_sym_LPAREN,
    ACTIONS(442), 1,
      sym_metadata_ref,
    ACTIONS(444), 1,
      anon_sym_LBRACE,
    ACTIONS(446), 1,
      anon_sym_LT,
    ACTIONS(448), 1,
      anon_sym_BANG,
    ACTIONS(452), 1,
      anon_sym_LBRACK,
    ACTIONS(460), 1,
      anon_sym_GT,
    STATE(88), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(450), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    STATE(56), 2,
      sym_md_value,
      aux_sym_metadata_repeat1,
    ACTIONS(440), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [2585] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(466), 16,
      anon_sym_LPAREN,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_EQ,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [2608] = 12,
    ACTIONS(438), 1,
      anon_sym_LPAREN,
    ACTIONS(442), 1,
      sym_metadata_ref,
    ACTIONS(444), 1,
      anon_sym_LBRACE,
    ACTIONS(446), 1,
      anon_sym_LT,
    ACTIONS(448), 1,
      anon_sym_BANG,
    ACTIONS(452), 1,
      anon_sym_LBRACK,
    ACTIONS(460), 1,
      anon_sym_RBRACE,
    STATE(88), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(450), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    STATE(56), 2,
      sym_md_value,
      aux_sym_metadata_repeat1,
    ACTIONS(440), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [2651] = 3,
    ACTIONS(468), 1,
      anon_sym_LPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(470), 15,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_EQ,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [2676] = 12,
    ACTIONS(424), 1,
      sym_stack_object,
    ACTIONS(428), 1,
      sym_ir_local_var,
    ACTIONS(430), 1,
      anon_sym_BQUOTE,
    ACTIONS(432), 1,
      anon_sym_call_DASHentry,
    ACTIONS(434), 1,
      anon_sym_custom,
    STATE(267), 1,
      sym_machine_pointer_info,
    STATE(389), 1,
      sym_memory_pseudo_source_value_keyword,
    STATE(390), 1,
      sym_escaped_ir_value,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(426), 2,
      sym_global_var,
      anon_sym_unknown_DASHaddress,
    STATE(283), 2,
      sym_ir_value,
      sym_memory_pseudo_source_value,
    ACTIONS(436), 4,
      anon_sym_constant_DASHpool,
      anon_sym_stack,
      anon_sym_got,
      anon_sym_jump_DASHtable,
  [2719] = 3,
    ACTIONS(472), 1,
      anon_sym_LPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(474), 15,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_EQ,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [2744] = 12,
    ACTIONS(438), 1,
      anon_sym_LPAREN,
    ACTIONS(442), 1,
      sym_metadata_ref,
    ACTIONS(444), 1,
      anon_sym_LBRACE,
    ACTIONS(446), 1,
      anon_sym_LT,
    ACTIONS(448), 1,
      anon_sym_BANG,
    ACTIONS(452), 1,
      anon_sym_LBRACK,
    ACTIONS(460), 1,
      anon_sym_RPAREN,
    STATE(88), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(450), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    STATE(56), 2,
      sym_md_value,
      aux_sym_metadata_repeat1,
    ACTIONS(440), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [2787] = 8,
    ACTIONS(23), 1,
      sym_physical_register,
    ACTIONS(67), 1,
      anon_sym_implicit,
    ACTIONS(187), 1,
      sym_var,
    ACTIONS(476), 1,
      anon_sym__,
    STATE(499), 1,
      sym_register_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(112), 2,
      sym_register_flag,
      aux_sym_register_operand_repeat1,
    ACTIONS(478), 9,
      anon_sym_undef,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
  [2822] = 3,
    ACTIONS(480), 1,
      anon_sym_LPAREN2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(420), 15,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [2847] = 12,
    ACTIONS(438), 1,
      anon_sym_LPAREN,
    ACTIONS(442), 1,
      sym_metadata_ref,
    ACTIONS(444), 1,
      anon_sym_LBRACE,
    ACTIONS(446), 1,
      anon_sym_LT,
    ACTIONS(448), 1,
      anon_sym_BANG,
    ACTIONS(452), 1,
      anon_sym_LBRACK,
    ACTIONS(482), 1,
      anon_sym_RPAREN,
    STATE(88), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(450), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    STATE(56), 2,
      sym_md_value,
      aux_sym_metadata_repeat1,
    ACTIONS(440), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [2890] = 12,
    ACTIONS(424), 1,
      sym_stack_object,
    ACTIONS(428), 1,
      sym_ir_local_var,
    ACTIONS(430), 1,
      anon_sym_BQUOTE,
    ACTIONS(432), 1,
      anon_sym_call_DASHentry,
    ACTIONS(434), 1,
      anon_sym_custom,
    STATE(271), 1,
      sym_machine_pointer_info,
    STATE(389), 1,
      sym_memory_pseudo_source_value_keyword,
    STATE(390), 1,
      sym_escaped_ir_value,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(426), 2,
      sym_global_var,
      anon_sym_unknown_DASHaddress,
    STATE(283), 2,
      sym_ir_value,
      sym_memory_pseudo_source_value,
    ACTIONS(436), 4,
      anon_sym_constant_DASHpool,
      anon_sym_stack,
      anon_sym_got,
      anon_sym_jump_DASHtable,
  [2933] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(484), 16,
      anon_sym_LPAREN,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_EQ,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [2956] = 4,
    ACTIONS(410), 1,
      anon_sym_LPAREN,
    ACTIONS(486), 1,
      anon_sym_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(412), 14,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [2983] = 4,
    ACTIONS(404), 1,
      anon_sym_LPAREN,
    ACTIONS(488), 1,
      anon_sym_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(406), 14,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [3010] = 12,
    ACTIONS(438), 1,
      anon_sym_LPAREN,
    ACTIONS(442), 1,
      sym_metadata_ref,
    ACTIONS(444), 1,
      anon_sym_LBRACE,
    ACTIONS(446), 1,
      anon_sym_LT,
    ACTIONS(448), 1,
      anon_sym_BANG,
    ACTIONS(452), 1,
      anon_sym_LBRACK,
    ACTIONS(490), 1,
      anon_sym_RBRACK,
    STATE(88), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(450), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    STATE(71), 2,
      sym_md_value,
      aux_sym_metadata_repeat1,
    ACTIONS(440), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [3053] = 3,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(494), 3,
      anon_sym_BANG,
      anon_sym_null,
      aux_sym_md_value_token1,
    ACTIONS(492), 13,
      anon_sym_LPAREN,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_COLON,
      sym_metadata_ref,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_STAR,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
  [3078] = 3,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(498), 3,
      anon_sym_BANG,
      anon_sym_null,
      aux_sym_md_value_token1,
    ACTIONS(496), 13,
      anon_sym_LPAREN,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_COLON,
      sym_metadata_ref,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_STAR,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
  [3103] = 3,
    ACTIONS(404), 1,
      anon_sym_LPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(406), 15,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_EQ,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [3128] = 12,
    ACTIONS(438), 1,
      anon_sym_LPAREN,
    ACTIONS(442), 1,
      sym_metadata_ref,
    ACTIONS(444), 1,
      anon_sym_LBRACE,
    ACTIONS(446), 1,
      anon_sym_LT,
    ACTIONS(448), 1,
      anon_sym_BANG,
    ACTIONS(452), 1,
      anon_sym_LBRACK,
    ACTIONS(490), 1,
      anon_sym_GT,
    STATE(88), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(450), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    STATE(73), 2,
      sym_md_value,
      aux_sym_metadata_repeat1,
    ACTIONS(440), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [3171] = 3,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(502), 3,
      anon_sym_BANG,
      anon_sym_null,
      aux_sym_md_value_token1,
    ACTIONS(500), 13,
      anon_sym_LPAREN,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_COLON,
      sym_metadata_ref,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_STAR,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
  [3196] = 12,
    ACTIONS(424), 1,
      sym_stack_object,
    ACTIONS(428), 1,
      sym_ir_local_var,
    ACTIONS(430), 1,
      anon_sym_BQUOTE,
    ACTIONS(432), 1,
      anon_sym_call_DASHentry,
    ACTIONS(434), 1,
      anon_sym_custom,
    STATE(269), 1,
      sym_machine_pointer_info,
    STATE(389), 1,
      sym_memory_pseudo_source_value_keyword,
    STATE(390), 1,
      sym_escaped_ir_value,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(426), 2,
      sym_global_var,
      anon_sym_unknown_DASHaddress,
    STATE(283), 2,
      sym_ir_value,
      sym_memory_pseudo_source_value,
    ACTIONS(436), 4,
      anon_sym_constant_DASHpool,
      anon_sym_stack,
      anon_sym_got,
      anon_sym_jump_DASHtable,
  [3239] = 12,
    ACTIONS(438), 1,
      anon_sym_LPAREN,
    ACTIONS(442), 1,
      sym_metadata_ref,
    ACTIONS(444), 1,
      anon_sym_LBRACE,
    ACTIONS(446), 1,
      anon_sym_LT,
    ACTIONS(448), 1,
      anon_sym_BANG,
    ACTIONS(452), 1,
      anon_sym_LBRACK,
    ACTIONS(490), 1,
      anon_sym_RBRACE,
    STATE(88), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(450), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    STATE(75), 2,
      sym_md_value,
      aux_sym_metadata_repeat1,
    ACTIONS(440), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [3282] = 3,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(506), 3,
      anon_sym_BANG,
      anon_sym_null,
      aux_sym_md_value_token1,
    ACTIONS(504), 13,
      anon_sym_LPAREN,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_COLON,
      sym_metadata_ref,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_STAR,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
  [3307] = 3,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(510), 3,
      anon_sym_BANG,
      anon_sym_null,
      aux_sym_md_value_token1,
    ACTIONS(508), 13,
      anon_sym_LPAREN,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_COLON,
      sym_metadata_ref,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_PIPE,
      anon_sym_STAR,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
  [3332] = 12,
    ACTIONS(438), 1,
      anon_sym_LPAREN,
    ACTIONS(442), 1,
      sym_metadata_ref,
    ACTIONS(444), 1,
      anon_sym_LBRACE,
    ACTIONS(446), 1,
      anon_sym_LT,
    ACTIONS(448), 1,
      anon_sym_BANG,
    ACTIONS(452), 1,
      anon_sym_LBRACK,
    ACTIONS(490), 1,
      anon_sym_RPAREN,
    STATE(88), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(450), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    STATE(79), 2,
      sym_md_value,
      aux_sym_metadata_repeat1,
    ACTIONS(440), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [3375] = 12,
    ACTIONS(438), 1,
      anon_sym_LPAREN,
    ACTIONS(442), 1,
      sym_metadata_ref,
    ACTIONS(444), 1,
      anon_sym_LBRACE,
    ACTIONS(446), 1,
      anon_sym_LT,
    ACTIONS(448), 1,
      anon_sym_BANG,
    ACTIONS(452), 1,
      anon_sym_LBRACK,
    ACTIONS(512), 1,
      anon_sym_RPAREN,
    STATE(88), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(450), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    STATE(104), 2,
      sym_md_value,
      aux_sym_metadata_repeat1,
    ACTIONS(440), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [3418] = 12,
    ACTIONS(438), 1,
      anon_sym_LPAREN,
    ACTIONS(442), 1,
      sym_metadata_ref,
    ACTIONS(444), 1,
      anon_sym_LBRACE,
    ACTIONS(446), 1,
      anon_sym_LT,
    ACTIONS(448), 1,
      anon_sym_BANG,
    ACTIONS(452), 1,
      anon_sym_LBRACK,
    ACTIONS(514), 1,
      anon_sym_RPAREN,
    STATE(88), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(450), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    STATE(105), 2,
      sym_md_value,
      aux_sym_metadata_repeat1,
    ACTIONS(440), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [3461] = 12,
    ACTIONS(424), 1,
      sym_stack_object,
    ACTIONS(428), 1,
      sym_ir_local_var,
    ACTIONS(430), 1,
      anon_sym_BQUOTE,
    ACTIONS(432), 1,
      anon_sym_call_DASHentry,
    ACTIONS(434), 1,
      anon_sym_custom,
    STATE(261), 1,
      sym_machine_pointer_info,
    STATE(389), 1,
      sym_memory_pseudo_source_value_keyword,
    STATE(390), 1,
      sym_escaped_ir_value,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(426), 2,
      sym_global_var,
      anon_sym_unknown_DASHaddress,
    STATE(283), 2,
      sym_ir_value,
      sym_memory_pseudo_source_value,
    ACTIONS(436), 4,
      anon_sym_constant_DASHpool,
      anon_sym_stack,
      anon_sym_got,
      anon_sym_jump_DASHtable,
  [3504] = 12,
    ACTIONS(438), 1,
      anon_sym_LPAREN,
    ACTIONS(442), 1,
      sym_metadata_ref,
    ACTIONS(444), 1,
      anon_sym_LBRACE,
    ACTIONS(446), 1,
      anon_sym_LT,
    ACTIONS(448), 1,
      anon_sym_BANG,
    ACTIONS(452), 1,
      anon_sym_LBRACK,
    ACTIONS(514), 1,
      anon_sym_RBRACE,
    STATE(88), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(450), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    STATE(68), 2,
      sym_md_value,
      aux_sym_metadata_repeat1,
    ACTIONS(440), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [3547] = 12,
    ACTIONS(438), 1,
      anon_sym_LPAREN,
    ACTIONS(442), 1,
      sym_metadata_ref,
    ACTIONS(444), 1,
      anon_sym_LBRACE,
    ACTIONS(446), 1,
      anon_sym_LT,
    ACTIONS(448), 1,
      anon_sym_BANG,
    ACTIONS(452), 1,
      anon_sym_LBRACK,
    ACTIONS(514), 1,
      anon_sym_GT,
    STATE(88), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(450), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    STATE(65), 2,
      sym_md_value,
      aux_sym_metadata_repeat1,
    ACTIONS(440), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [3590] = 12,
    ACTIONS(438), 1,
      anon_sym_LPAREN,
    ACTIONS(442), 1,
      sym_metadata_ref,
    ACTIONS(444), 1,
      anon_sym_LBRACE,
    ACTIONS(446), 1,
      anon_sym_LT,
    ACTIONS(448), 1,
      anon_sym_BANG,
    ACTIONS(452), 1,
      anon_sym_LBRACK,
    ACTIONS(514), 1,
      anon_sym_RBRACK,
    STATE(88), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(450), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    STATE(64), 2,
      sym_md_value,
      aux_sym_metadata_repeat1,
    ACTIONS(440), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [3633] = 12,
    ACTIONS(438), 1,
      anon_sym_LPAREN,
    ACTIONS(442), 1,
      sym_metadata_ref,
    ACTIONS(444), 1,
      anon_sym_LBRACE,
    ACTIONS(446), 1,
      anon_sym_LT,
    ACTIONS(448), 1,
      anon_sym_BANG,
    ACTIONS(452), 1,
      anon_sym_LBRACK,
    ACTIONS(516), 1,
      anon_sym_RPAREN,
    STATE(88), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(450), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    STATE(56), 2,
      sym_md_value,
      aux_sym_metadata_repeat1,
    ACTIONS(440), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [3676] = 12,
    ACTIONS(438), 1,
      anon_sym_LPAREN,
    ACTIONS(442), 1,
      sym_metadata_ref,
    ACTIONS(444), 1,
      anon_sym_LBRACE,
    ACTIONS(446), 1,
      anon_sym_LT,
    ACTIONS(448), 1,
      anon_sym_BANG,
    ACTIONS(452), 1,
      anon_sym_LBRACK,
    ACTIONS(454), 1,
      anon_sym_RPAREN,
    STATE(88), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(450), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    STATE(56), 2,
      sym_md_value,
      aux_sym_metadata_repeat1,
    ACTIONS(440), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [3719] = 12,
    ACTIONS(438), 1,
      anon_sym_LPAREN,
    ACTIONS(442), 1,
      sym_metadata_ref,
    ACTIONS(444), 1,
      anon_sym_LBRACE,
    ACTIONS(446), 1,
      anon_sym_LT,
    ACTIONS(448), 1,
      anon_sym_BANG,
    ACTIONS(452), 1,
      anon_sym_LBRACK,
    ACTIONS(518), 1,
      anon_sym_RPAREN,
    STATE(88), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(450), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    STATE(82), 2,
      sym_md_value,
      aux_sym_metadata_repeat1,
    ACTIONS(440), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [3762] = 7,
    ACTIONS(67), 1,
      anon_sym_implicit,
    ACTIONS(520), 1,
      sym_var,
    ACTIONS(522), 1,
      sym_physical_register,
    ACTIONS(524), 1,
      anon_sym__,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(110), 2,
      sym_register_flag,
      aux_sym_register_operand_repeat1,
    ACTIONS(478), 9,
      anon_sym_undef,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
  [3794] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(526), 15,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_EQ,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [3816] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(496), 15,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [3838] = 5,
    ACTIONS(533), 1,
      anon_sym_implicit,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(110), 2,
      sym_register_flag,
      aux_sym_register_operand_repeat1,
    ACTIONS(528), 3,
      sym_var,
      sym_physical_register,
      anon_sym__,
    ACTIONS(530), 9,
      anon_sym_undef,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
  [3866] = 4,
    ACTIONS(536), 1,
      anon_sym_COMMA,
    STATE(111), 1,
      aux_sym_cfi_operand_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(539), 13,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [3892] = 7,
    ACTIONS(67), 1,
      anon_sym_implicit,
    ACTIONS(522), 1,
      sym_physical_register,
    ACTIONS(524), 1,
      anon_sym__,
    ACTIONS(541), 1,
      sym_var,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(110), 2,
      sym_register_flag,
      aux_sym_register_operand_repeat1,
    ACTIONS(478), 9,
      anon_sym_undef,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
  [3924] = 4,
    STATE(209), 1,
      sym_offset,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(545), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(543), 12,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
  [3950] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(504), 15,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [3972] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(547), 15,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_EQ,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [3994] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(549), 15,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_EQ,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [4016] = 4,
    STATE(207), 1,
      sym_offset,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(545), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(551), 12,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
  [4042] = 4,
    ACTIONS(553), 1,
      anon_sym_COMMA,
    STATE(111), 1,
      aux_sym_cfi_operand_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(556), 13,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [4068] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(470), 15,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_EQ,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [4090] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(558), 15,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [4112] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(560), 15,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_EQ,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [4134] = 4,
    ACTIONS(562), 1,
      anon_sym_COMMA,
    STATE(118), 1,
      aux_sym_cfi_operand_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(565), 13,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [4160] = 9,
    ACTIONS(165), 1,
      anon_sym_COLON_COLON,
    ACTIONS(567), 1,
      anon_sym_COMMA,
    STATE(190), 1,
      aux_sym_instruction_repeat4,
    STATE(204), 1,
      aux_sym_instruction_repeat3,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(163), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [4195] = 9,
    ACTIONS(129), 1,
      anon_sym_COLON_COLON,
    ACTIONS(575), 1,
      anon_sym_COMMA,
    STATE(123), 1,
      aux_sym_instruction_repeat3,
    STATE(195), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(127), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [4230] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(577), 14,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [4251] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(579), 14,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [4272] = 9,
    ACTIONS(121), 1,
      anon_sym_COLON_COLON,
    ACTIONS(581), 1,
      anon_sym_COMMA,
    STATE(174), 1,
      aux_sym_instruction_repeat3,
    STATE(197), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(111), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [4307] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(583), 14,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [4328] = 9,
    ACTIONS(141), 1,
      anon_sym_COLON_COLON,
    ACTIONS(585), 1,
      anon_sym_COMMA,
    STATE(181), 1,
      aux_sym_instruction_repeat4,
    STATE(204), 1,
      aux_sym_instruction_repeat3,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(139), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [4363] = 9,
    ACTIONS(141), 1,
      anon_sym_COLON_COLON,
    ACTIONS(585), 1,
      anon_sym_COMMA,
    STATE(175), 1,
      aux_sym_instruction_repeat3,
    STATE(181), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(139), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [4398] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(587), 14,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [4419] = 9,
    ACTIONS(589), 1,
      anon_sym_COMMA,
    ACTIONS(593), 1,
      anon_sym_COLON_COLON,
    STATE(164), 1,
      aux_sym_instruction_repeat3,
    STATE(200), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(591), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [4454] = 11,
    ACTIONS(27), 1,
      sym_metadata_ref,
    ACTIONS(595), 1,
      anon_sym_LPAREN,
    ACTIONS(599), 1,
      anon_sym_LBRACE,
    ACTIONS(601), 1,
      anon_sym_LT,
    ACTIONS(603), 1,
      anon_sym_BANG,
    ACTIONS(607), 1,
      anon_sym_LBRACK,
    STATE(170), 1,
      sym_md_value,
    STATE(216), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(605), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    ACTIONS(597), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [4493] = 9,
    ACTIONS(145), 1,
      anon_sym_COLON_COLON,
    ACTIONS(609), 1,
      anon_sym_COMMA,
    STATE(182), 1,
      aux_sym_instruction_repeat4,
    STATE(204), 1,
      aux_sym_instruction_repeat3,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(143), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [4528] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(611), 14,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [4549] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(613), 14,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [4570] = 9,
    ACTIONS(615), 1,
      anon_sym_LPAREN,
    ACTIONS(619), 1,
      anon_sym_RPAREN,
    ACTIONS(623), 1,
      anon_sym_LBRACE,
    ACTIONS(625), 1,
      anon_sym_LT,
    ACTIONS(627), 1,
      anon_sym_LBRACK,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(621), 2,
      sym_identifier,
      sym_number,
    STATE(178), 2,
      sym__escaped_ir_content,
      aux_sym_escaped_ir_value_repeat1,
    ACTIONS(617), 5,
      anon_sym_COMMA,
      sym_immediate_type,
      sym_global_var,
      sym_ir_local_var,
      anon_sym_STAR,
  [4605] = 9,
    ACTIONS(615), 1,
      anon_sym_LPAREN,
    ACTIONS(623), 1,
      anon_sym_LBRACE,
    ACTIONS(625), 1,
      anon_sym_LT,
    ACTIONS(627), 1,
      anon_sym_LBRACK,
    ACTIONS(633), 1,
      anon_sym_RBRACK,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(631), 2,
      sym_identifier,
      sym_number,
    STATE(57), 2,
      sym__escaped_ir_content,
      aux_sym_escaped_ir_value_repeat1,
    ACTIONS(629), 5,
      anon_sym_COMMA,
      sym_immediate_type,
      sym_global_var,
      sym_ir_local_var,
      anon_sym_STAR,
  [4640] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(635), 14,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [4661] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(539), 14,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [4682] = 9,
    ACTIONS(615), 1,
      anon_sym_LPAREN,
    ACTIONS(619), 1,
      anon_sym_RBRACE,
    ACTIONS(623), 1,
      anon_sym_LBRACE,
    ACTIONS(625), 1,
      anon_sym_LT,
    ACTIONS(627), 1,
      anon_sym_LBRACK,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(639), 2,
      sym_identifier,
      sym_number,
    STATE(166), 2,
      sym__escaped_ir_content,
      aux_sym_escaped_ir_value_repeat1,
    ACTIONS(637), 5,
      anon_sym_COMMA,
      sym_immediate_type,
      sym_global_var,
      sym_ir_local_var,
      anon_sym_STAR,
  [4717] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(641), 14,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [4738] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(643), 14,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [4759] = 9,
    ACTIONS(615), 1,
      anon_sym_LPAREN,
    ACTIONS(619), 1,
      anon_sym_GT,
    ACTIONS(623), 1,
      anon_sym_LBRACE,
    ACTIONS(625), 1,
      anon_sym_LT,
    ACTIONS(627), 1,
      anon_sym_LBRACK,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(647), 2,
      sym_identifier,
      sym_number,
    STATE(154), 2,
      sym__escaped_ir_content,
      aux_sym_escaped_ir_value_repeat1,
    ACTIONS(645), 5,
      anon_sym_COMMA,
      sym_immediate_type,
      sym_global_var,
      sym_ir_local_var,
      anon_sym_STAR,
  [4794] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(649), 14,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [4815] = 11,
    ACTIONS(27), 1,
      sym_metadata_ref,
    ACTIONS(595), 1,
      anon_sym_LPAREN,
    ACTIONS(599), 1,
      anon_sym_LBRACE,
    ACTIONS(601), 1,
      anon_sym_LT,
    ACTIONS(603), 1,
      anon_sym_BANG,
    ACTIONS(607), 1,
      anon_sym_LBRACK,
    STATE(211), 1,
      sym_md_value,
    STATE(216), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(605), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    ACTIONS(597), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [4854] = 9,
    ACTIONS(145), 1,
      anon_sym_COLON_COLON,
    ACTIONS(609), 1,
      anon_sym_COMMA,
    STATE(176), 1,
      aux_sym_instruction_repeat3,
    STATE(182), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(143), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [4889] = 9,
    ACTIONS(615), 1,
      anon_sym_LPAREN,
    ACTIONS(619), 1,
      anon_sym_RBRACK,
    ACTIONS(623), 1,
      anon_sym_LBRACE,
    ACTIONS(625), 1,
      anon_sym_LT,
    ACTIONS(627), 1,
      anon_sym_LBRACK,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(653), 2,
      sym_identifier,
      sym_number,
    STATE(138), 2,
      sym__escaped_ir_content,
      aux_sym_escaped_ir_value_repeat1,
    ACTIONS(651), 5,
      anon_sym_COMMA,
      sym_immediate_type,
      sym_global_var,
      sym_ir_local_var,
      anon_sym_STAR,
  [4924] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(655), 14,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [4945] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(657), 14,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [4966] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(659), 14,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [4987] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(661), 14,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [5008] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(663), 14,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [5029] = 9,
    ACTIONS(615), 1,
      anon_sym_LPAREN,
    ACTIONS(623), 1,
      anon_sym_LBRACE,
    ACTIONS(625), 1,
      anon_sym_LT,
    ACTIONS(627), 1,
      anon_sym_LBRACK,
    ACTIONS(633), 1,
      anon_sym_GT,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(631), 2,
      sym_identifier,
      sym_number,
    STATE(57), 2,
      sym__escaped_ir_content,
      aux_sym_escaped_ir_value_repeat1,
    ACTIONS(629), 5,
      anon_sym_COMMA,
      sym_immediate_type,
      sym_global_var,
      sym_ir_local_var,
      anon_sym_STAR,
  [5064] = 9,
    ACTIONS(615), 1,
      anon_sym_LPAREN,
    ACTIONS(623), 1,
      anon_sym_LBRACE,
    ACTIONS(625), 1,
      anon_sym_LT,
    ACTIONS(627), 1,
      anon_sym_LBRACK,
    ACTIONS(665), 1,
      anon_sym_BQUOTE,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(631), 2,
      sym_identifier,
      sym_number,
    STATE(57), 2,
      sym__escaped_ir_content,
      aux_sym_escaped_ir_value_repeat1,
    ACTIONS(629), 5,
      anon_sym_COMMA,
      sym_immediate_type,
      sym_global_var,
      sym_ir_local_var,
      anon_sym_STAR,
  [5099] = 9,
    ACTIONS(667), 1,
      anon_sym_COMMA,
    ACTIONS(671), 1,
      anon_sym_COLON_COLON,
    STATE(134), 1,
      aux_sym_instruction_repeat3,
    STATE(196), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(669), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [5134] = 9,
    ACTIONS(133), 1,
      anon_sym_COLON_COLON,
    ACTIONS(673), 1,
      anon_sym_COMMA,
    STATE(203), 1,
      aux_sym_instruction_repeat4,
    STATE(204), 1,
      aux_sym_instruction_repeat3,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(131), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [5169] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(675), 14,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [5190] = 11,
    ACTIONS(27), 1,
      sym_metadata_ref,
    ACTIONS(595), 1,
      anon_sym_LPAREN,
    ACTIONS(599), 1,
      anon_sym_LBRACE,
    ACTIONS(601), 1,
      anon_sym_LT,
    ACTIONS(603), 1,
      anon_sym_BANG,
    ACTIONS(607), 1,
      anon_sym_LBRACK,
    STATE(127), 1,
      sym_md_value,
    STATE(216), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(605), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    ACTIONS(597), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [5229] = 11,
    ACTIONS(27), 1,
      sym_metadata_ref,
    ACTIONS(595), 1,
      anon_sym_LPAREN,
    ACTIONS(599), 1,
      anon_sym_LBRACE,
    ACTIONS(601), 1,
      anon_sym_LT,
    ACTIONS(603), 1,
      anon_sym_BANG,
    ACTIONS(607), 1,
      anon_sym_LBRACK,
    STATE(124), 1,
      sym_md_value,
    STATE(216), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(605), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    ACTIONS(597), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [5268] = 9,
    ACTIONS(677), 1,
      anon_sym_COMMA,
    ACTIONS(681), 1,
      anon_sym_COLON_COLON,
    STATE(169), 1,
      aux_sym_instruction_repeat3,
    STATE(185), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(679), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [5303] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(683), 14,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [5324] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(565), 14,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [5345] = 9,
    ACTIONS(161), 1,
      anon_sym_COLON_COLON,
    ACTIONS(685), 1,
      anon_sym_COMMA,
    STATE(198), 1,
      aux_sym_instruction_repeat4,
    STATE(204), 1,
      aux_sym_instruction_repeat3,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(159), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [5380] = 9,
    ACTIONS(615), 1,
      anon_sym_LPAREN,
    ACTIONS(623), 1,
      anon_sym_LBRACE,
    ACTIONS(625), 1,
      anon_sym_LT,
    ACTIONS(627), 1,
      anon_sym_LBRACK,
    ACTIONS(691), 1,
      anon_sym_BQUOTE,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(689), 2,
      sym_identifier,
      sym_number,
    STATE(155), 2,
      sym__escaped_ir_content,
      aux_sym_escaped_ir_value_repeat1,
    ACTIONS(687), 5,
      anon_sym_COMMA,
      sym_immediate_type,
      sym_global_var,
      sym_ir_local_var,
      anon_sym_STAR,
  [5415] = 9,
    ACTIONS(615), 1,
      anon_sym_LPAREN,
    ACTIONS(623), 1,
      anon_sym_LBRACE,
    ACTIONS(625), 1,
      anon_sym_LT,
    ACTIONS(627), 1,
      anon_sym_LBRACK,
    ACTIONS(633), 1,
      anon_sym_RBRACE,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(631), 2,
      sym_identifier,
      sym_number,
    STATE(57), 2,
      sym__escaped_ir_content,
      aux_sym_escaped_ir_value_repeat1,
    ACTIONS(629), 5,
      anon_sym_COMMA,
      sym_immediate_type,
      sym_global_var,
      sym_ir_local_var,
      anon_sym_STAR,
  [5450] = 9,
    ACTIONS(693), 1,
      anon_sym_COMMA,
    ACTIONS(697), 1,
      anon_sym_COLON_COLON,
    STATE(168), 1,
      aux_sym_instruction_repeat3,
    STATE(193), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(695), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [5485] = 9,
    ACTIONS(129), 1,
      anon_sym_COLON_COLON,
    ACTIONS(575), 1,
      anon_sym_COMMA,
    STATE(195), 1,
      aux_sym_instruction_repeat4,
    STATE(204), 1,
      aux_sym_instruction_repeat3,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(127), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [5520] = 9,
    ACTIONS(121), 1,
      anon_sym_COLON_COLON,
    ACTIONS(581), 1,
      anon_sym_COMMA,
    STATE(197), 1,
      aux_sym_instruction_repeat4,
    STATE(204), 1,
      aux_sym_instruction_repeat3,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(111), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [5555] = 9,
    ACTIONS(161), 1,
      anon_sym_COLON_COLON,
    ACTIONS(685), 1,
      anon_sym_COMMA,
    STATE(157), 1,
      aux_sym_instruction_repeat3,
    STATE(198), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(159), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [5590] = 11,
    ACTIONS(27), 1,
      sym_metadata_ref,
    ACTIONS(595), 1,
      anon_sym_LPAREN,
    ACTIONS(599), 1,
      anon_sym_LBRACE,
    ACTIONS(601), 1,
      anon_sym_LT,
    ACTIONS(603), 1,
      anon_sym_BANG,
    ACTIONS(607), 1,
      anon_sym_LBRACK,
    STATE(130), 1,
      sym_md_value,
    STATE(216), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(605), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    ACTIONS(597), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [5629] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(699), 14,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
      anon_sym_PLUS,
      anon_sym_DASH,
  [5650] = 9,
    ACTIONS(701), 1,
      anon_sym_COMMA,
    ACTIONS(705), 1,
      anon_sym_COLON_COLON,
    STATE(129), 1,
      aux_sym_instruction_repeat3,
    STATE(183), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(703), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [5685] = 9,
    ACTIONS(177), 1,
      anon_sym_COLON_COLON,
    ACTIONS(707), 1,
      anon_sym_COMMA,
    STATE(186), 1,
      aux_sym_instruction_repeat4,
    STATE(204), 1,
      aux_sym_instruction_repeat3,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(175), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [5720] = 9,
    ACTIONS(157), 1,
      anon_sym_COLON_COLON,
    ACTIONS(709), 1,
      anon_sym_COMMA,
    STATE(199), 1,
      aux_sym_instruction_repeat4,
    STATE(204), 1,
      aux_sym_instruction_repeat3,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(155), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [5755] = 9,
    ACTIONS(173), 1,
      anon_sym_COLON_COLON,
    ACTIONS(711), 1,
      anon_sym_COMMA,
    STATE(194), 1,
      aux_sym_instruction_repeat4,
    STATE(204), 1,
      aux_sym_instruction_repeat3,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(171), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [5790] = 11,
    ACTIONS(27), 1,
      sym_metadata_ref,
    ACTIONS(595), 1,
      anon_sym_LPAREN,
    ACTIONS(599), 1,
      anon_sym_LBRACE,
    ACTIONS(601), 1,
      anon_sym_LT,
    ACTIONS(603), 1,
      anon_sym_BANG,
    ACTIONS(607), 1,
      anon_sym_LBRACK,
    STATE(147), 1,
      sym_md_value,
    STATE(216), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(605), 2,
      anon_sym_null,
      aux_sym_md_value_token1,
    ACTIONS(597), 4,
      anon_sym_COMMA,
      anon_sym_COLON,
      anon_sym_PIPE,
      anon_sym_STAR,
  [5829] = 9,
    ACTIONS(615), 1,
      anon_sym_LPAREN,
    ACTIONS(623), 1,
      anon_sym_LBRACE,
    ACTIONS(625), 1,
      anon_sym_LT,
    ACTIONS(627), 1,
      anon_sym_LBRACK,
    ACTIONS(633), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(631), 2,
      sym_identifier,
      sym_number,
    STATE(57), 2,
      sym__escaped_ir_content,
      aux_sym_escaped_ir_value_repeat1,
    ACTIONS(629), 5,
      anon_sym_COMMA,
      sym_immediate_type,
      sym_global_var,
      sym_ir_local_var,
      anon_sym_STAR,
  [5864] = 8,
    ACTIONS(681), 1,
      anon_sym_COLON_COLON,
    ACTIONS(713), 1,
      anon_sym_COMMA,
    STATE(202), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(679), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [5896] = 8,
    ACTIONS(715), 1,
      anon_sym_LPAREN,
    ACTIONS(719), 1,
      anon_sym_store,
    ACTIONS(721), 1,
      anon_sym_syncscope,
    STATE(252), 1,
      sym_sync_scope,
    STATE(253), 1,
      sym_atomic_ordering,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(717), 2,
      sym_number,
      anon_sym_unknown_DASHsize,
    ACTIONS(723), 6,
      anon_sym_unordered,
      anon_sym_monotonic,
      anon_sym_acquire,
      anon_sym_release,
      anon_sym_acq_rel,
      anon_sym_seq_cst,
  [5928] = 8,
    ACTIONS(157), 1,
      anon_sym_COLON_COLON,
    ACTIONS(725), 1,
      anon_sym_COMMA,
    STATE(202), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(155), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [5960] = 8,
    ACTIONS(173), 1,
      anon_sym_COLON_COLON,
    ACTIONS(727), 1,
      anon_sym_COMMA,
    STATE(202), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(171), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [5992] = 8,
    ACTIONS(141), 1,
      anon_sym_COLON_COLON,
    ACTIONS(729), 1,
      anon_sym_COMMA,
    STATE(202), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(139), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [6024] = 8,
    ACTIONS(721), 1,
      anon_sym_syncscope,
    ACTIONS(731), 1,
      anon_sym_LPAREN,
    ACTIONS(735), 1,
      anon_sym_store,
    STATE(247), 1,
      sym_sync_scope,
    STATE(248), 1,
      sym_atomic_ordering,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(733), 2,
      sym_number,
      anon_sym_unknown_DASHsize,
    ACTIONS(723), 6,
      anon_sym_unordered,
      anon_sym_monotonic,
      anon_sym_acquire,
      anon_sym_release,
      anon_sym_acq_rel,
      anon_sym_seq_cst,
  [6056] = 8,
    ACTIONS(121), 1,
      anon_sym_COLON_COLON,
    ACTIONS(737), 1,
      anon_sym_COMMA,
    STATE(202), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(111), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [6088] = 8,
    ACTIONS(169), 1,
      anon_sym_COLON_COLON,
    ACTIONS(739), 1,
      anon_sym_COMMA,
    STATE(202), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(167), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [6120] = 8,
    ACTIONS(671), 1,
      anon_sym_COLON_COLON,
    ACTIONS(741), 1,
      anon_sym_COMMA,
    STATE(202), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(669), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [6152] = 8,
    ACTIONS(705), 1,
      anon_sym_COLON_COLON,
    ACTIONS(743), 1,
      anon_sym_COMMA,
    STATE(202), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(703), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [6184] = 8,
    ACTIONS(697), 1,
      anon_sym_COLON_COLON,
    ACTIONS(745), 1,
      anon_sym_COMMA,
    STATE(202), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(695), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [6216] = 8,
    ACTIONS(153), 1,
      anon_sym_COLON_COLON,
    ACTIONS(747), 1,
      anon_sym_COMMA,
    STATE(202), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(151), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [6248] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(749), 13,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
  [6268] = 8,
    ACTIONS(593), 1,
      anon_sym_COLON_COLON,
    ACTIONS(751), 1,
      anon_sym_COMMA,
    STATE(202), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(591), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [6300] = 8,
    ACTIONS(129), 1,
      anon_sym_COLON_COLON,
    ACTIONS(753), 1,
      anon_sym_COMMA,
    STATE(202), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(127), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [6332] = 8,
    ACTIONS(149), 1,
      anon_sym_COLON_COLON,
    ACTIONS(755), 1,
      anon_sym_COMMA,
    STATE(202), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(147), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [6364] = 8,
    ACTIONS(165), 1,
      anon_sym_COLON_COLON,
    ACTIONS(757), 1,
      anon_sym_COMMA,
    STATE(202), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(163), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [6396] = 8,
    ACTIONS(145), 1,
      anon_sym_COLON_COLON,
    ACTIONS(759), 1,
      anon_sym_COMMA,
    STATE(202), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(143), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [6428] = 8,
    ACTIONS(177), 1,
      anon_sym_COLON_COLON,
    ACTIONS(761), 1,
      anon_sym_COMMA,
    STATE(202), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(175), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [6460] = 8,
    ACTIONS(133), 1,
      anon_sym_COLON_COLON,
    ACTIONS(763), 1,
      anon_sym_COMMA,
    STATE(202), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(131), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [6492] = 8,
    ACTIONS(137), 1,
      anon_sym_COLON_COLON,
    ACTIONS(765), 1,
      anon_sym_COMMA,
    STATE(202), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(135), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [6524] = 8,
    ACTIONS(161), 1,
      anon_sym_COLON_COLON,
    ACTIONS(767), 1,
      anon_sym_COMMA,
    STATE(202), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(159), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [6556] = 3,
    ACTIONS(771), 1,
      anon_sym_implicit,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(769), 12,
      sym_var,
      sym_physical_register,
      anon_sym__,
      anon_sym_undef,
      anon_sym_implicit_DASHdef,
      anon_sym_def,
      anon_sym_dead,
      anon_sym_killed,
      anon_sym_internal,
      anon_sym_early_DASHclobber,
      anon_sym_debug_DASHuse,
      anon_sym_renamable,
  [6578] = 7,
    ACTIONS(773), 1,
      anon_sym_COMMA,
    STATE(202), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(778), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(784), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(776), 3,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_COLON_COLON,
    ACTIONS(781), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [6608] = 8,
    ACTIONS(125), 1,
      anon_sym_COLON_COLON,
    ACTIONS(787), 1,
      anon_sym_COMMA,
    STATE(202), 1,
      aux_sym_instruction_repeat4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(123), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(569), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(573), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(571), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [6640] = 4,
    ACTIONS(789), 1,
      anon_sym_COMMA,
    STATE(204), 1,
      aux_sym_instruction_repeat3,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(792), 11,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
  [6664] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(792), 12,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
  [6683] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(776), 12,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
  [6702] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(794), 12,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
  [6721] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(796), 12,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
  [6740] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(551), 12,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
  [6759] = 8,
    ACTIONS(798), 1,
      anon_sym_RPAREN,
    ACTIONS(804), 1,
      anon_sym_ir_DASHblock_DASHaddress_DASHtaken,
    ACTIONS(806), 1,
      anon_sym_bb_id,
    ACTIONS(808), 1,
      anon_sym_bbsections,
    STATE(406), 1,
      sym_attribute,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(802), 2,
      anon_sym_align,
      anon_sym_call_DASHframe_DASHsize,
    ACTIONS(800), 5,
      sym_ir_block,
      anon_sym_machine_DASHblock_DASHaddress_DASHtaken,
      anon_sym_landing_DASHpad,
      anon_sym_inlineasm_DASHbr_DASHindirect_DASHtarget,
      anon_sym_ehfunclet_DASHentry,
  [6790] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(810), 12,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
  [6809] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(812), 12,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
  [6828] = 7,
    ACTIONS(721), 1,
      anon_sym_syncscope,
    ACTIONS(814), 1,
      anon_sym_LPAREN,
    STATE(249), 1,
      sym_atomic_ordering,
    STATE(250), 1,
      sym_sync_scope,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(816), 2,
      sym_number,
      anon_sym_unknown_DASHsize,
    ACTIONS(723), 6,
      anon_sym_unordered,
      anon_sym_monotonic,
      anon_sym_acquire,
      anon_sym_release,
      anon_sym_acq_rel,
      anon_sym_seq_cst,
  [6857] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(508), 12,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
  [6876] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(818), 12,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
  [6895] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(492), 12,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
  [6914] = 7,
    ACTIONS(715), 1,
      anon_sym_LPAREN,
    ACTIONS(721), 1,
      anon_sym_syncscope,
    STATE(252), 1,
      sym_sync_scope,
    STATE(253), 1,
      sym_atomic_ordering,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(717), 2,
      sym_number,
      anon_sym_unknown_DASHsize,
    ACTIONS(723), 6,
      anon_sym_unordered,
      anon_sym_monotonic,
      anon_sym_acquire,
      anon_sym_release,
      anon_sym_acq_rel,
      anon_sym_seq_cst,
  [6943] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(820), 12,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
  [6962] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(500), 12,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
      anon_sym_debug_DASHlocation,
      anon_sym_COLON_COLON,
  [6981] = 6,
    ACTIONS(681), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(679), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7007] = 6,
    ACTIONS(153), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(151), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7033] = 6,
    ACTIONS(830), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(828), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7059] = 6,
    ACTIONS(141), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(139), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7085] = 6,
    ACTIONS(593), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(591), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7111] = 6,
    ACTIONS(129), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(127), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7137] = 6,
    ACTIONS(137), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(135), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7163] = 6,
    ACTIONS(173), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(171), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7189] = 3,
    STATE(562), 1,
      sym_intpred,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(832), 10,
      anon_sym_eq,
      anon_sym_ne,
      anon_sym_sgt,
      anon_sym_sge,
      anon_sym_slt,
      anon_sym_sle,
      anon_sym_ugt,
      anon_sym_uge,
      anon_sym_ult,
      anon_sym_ule,
  [7209] = 6,
    ACTIONS(177), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(175), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7235] = 6,
    ACTIONS(165), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(163), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7261] = 6,
    ACTIONS(836), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(834), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7287] = 6,
    ACTIONS(840), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(838), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7313] = 6,
    ACTIONS(844), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(842), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7339] = 6,
    ACTIONS(705), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(703), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7365] = 6,
    ACTIONS(121), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(111), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7391] = 6,
    ACTIONS(145), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(143), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7417] = 6,
    ACTIONS(697), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(695), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7443] = 6,
    ACTIONS(169), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(167), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7469] = 6,
    ACTIONS(671), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(669), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7495] = 6,
    ACTIONS(157), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(155), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7521] = 6,
    ACTIONS(133), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(131), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7547] = 6,
    ACTIONS(149), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(147), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7573] = 6,
    ACTIONS(848), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(846), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7599] = 6,
    ACTIONS(125), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(123), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7625] = 6,
    ACTIONS(161), 1,
      anon_sym_COLON_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(159), 2,
      sym__newline,
      anon_sym_LBRACE,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7651] = 7,
    ACTIONS(804), 1,
      anon_sym_ir_DASHblock_DASHaddress_DASHtaken,
    ACTIONS(806), 1,
      anon_sym_bb_id,
    ACTIONS(808), 1,
      anon_sym_bbsections,
    STATE(479), 1,
      sym_attribute,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(802), 2,
      anon_sym_align,
      anon_sym_call_DASHframe_DASHsize,
    ACTIONS(800), 5,
      sym_ir_block,
      anon_sym_machine_DASHblock_DASHaddress_DASHtaken,
      anon_sym_landing_DASHpad,
      anon_sym_inlineasm_DASHbr_DASHindirect_DASHtarget,
      anon_sym_ehfunclet_DASHentry,
  [7679] = 5,
    ACTIONS(715), 1,
      anon_sym_LPAREN,
    STATE(253), 1,
      sym_atomic_ordering,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(717), 2,
      sym_number,
      anon_sym_unknown_DASHsize,
    ACTIONS(723), 6,
      anon_sym_unordered,
      anon_sym_monotonic,
      anon_sym_acquire,
      anon_sym_release,
      anon_sym_acq_rel,
      anon_sym_seq_cst,
  [7702] = 5,
    ACTIONS(715), 1,
      anon_sym_LPAREN,
    STATE(434), 1,
      sym_atomic_ordering,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(717), 2,
      sym_number,
      anon_sym_unknown_DASHsize,
    ACTIONS(723), 6,
      anon_sym_unordered,
      anon_sym_monotonic,
      anon_sym_acquire,
      anon_sym_release,
      anon_sym_acq_rel,
      anon_sym_seq_cst,
  [7725] = 5,
    ACTIONS(850), 1,
      anon_sym_LPAREN,
    STATE(459), 1,
      sym_atomic_ordering,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(852), 2,
      sym_number,
      anon_sym_unknown_DASHsize,
    ACTIONS(723), 6,
      anon_sym_unordered,
      anon_sym_monotonic,
      anon_sym_acquire,
      anon_sym_release,
      anon_sym_acq_rel,
      anon_sym_seq_cst,
  [7748] = 5,
    ACTIONS(850), 1,
      anon_sym_LPAREN,
    STATE(251), 1,
      sym_atomic_ordering,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(852), 2,
      sym_number,
      anon_sym_unknown_DASHsize,
    ACTIONS(723), 6,
      anon_sym_unordered,
      anon_sym_monotonic,
      anon_sym_acquire,
      anon_sym_release,
      anon_sym_acq_rel,
      anon_sym_seq_cst,
  [7771] = 5,
    ACTIONS(854), 1,
      anon_sym_LPAREN,
    STATE(415), 1,
      sym_atomic_ordering,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(856), 2,
      sym_number,
      anon_sym_unknown_DASHsize,
    ACTIONS(723), 6,
      anon_sym_unordered,
      anon_sym_monotonic,
      anon_sym_acquire,
      anon_sym_release,
      anon_sym_acq_rel,
      anon_sym_seq_cst,
  [7794] = 5,
    ACTIONS(814), 1,
      anon_sym_LPAREN,
    STATE(249), 1,
      sym_atomic_ordering,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(816), 2,
      sym_number,
      anon_sym_unknown_DASHsize,
    ACTIONS(723), 6,
      anon_sym_unordered,
      anon_sym_monotonic,
      anon_sym_acquire,
      anon_sym_release,
      anon_sym_acq_rel,
      anon_sym_seq_cst,
  [7817] = 5,
    ACTIONS(814), 1,
      anon_sym_LPAREN,
    STATE(405), 1,
      sym_atomic_ordering,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(816), 2,
      sym_number,
      anon_sym_unknown_DASHsize,
    ACTIONS(723), 6,
      anon_sym_unordered,
      anon_sym_monotonic,
      anon_sym_acquire,
      anon_sym_release,
      anon_sym_acq_rel,
      anon_sym_seq_cst,
  [7840] = 4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(861), 2,
      anon_sym_load,
      anon_sym_store,
    STATE(254), 2,
      sym_memory_operand_flag,
      aux_sym_memory_operand_repeat1,
    ACTIONS(858), 5,
      sym_string,
      anon_sym_volatile,
      anon_sym_non_DASHtemporal,
      anon_sym_dereferenceable,
      anon_sym_invariant,
  [7860] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(863), 9,
      anon_sym_LPAREN,
      sym_number,
      anon_sym_unknown_DASHsize,
      anon_sym_unordered,
      anon_sym_monotonic,
      anon_sym_acquire,
      anon_sym_release,
      anon_sym_acq_rel,
      anon_sym_seq_cst,
  [7876] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(865), 9,
      anon_sym_LPAREN,
      sym_number,
      anon_sym_unknown_DASHsize,
      anon_sym_unordered,
      anon_sym_monotonic,
      anon_sym_acquire,
      anon_sym_release,
      anon_sym_acq_rel,
      anon_sym_seq_cst,
  [7892] = 4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(869), 2,
      anon_sym_load,
      anon_sym_store,
    STATE(258), 2,
      sym_memory_operand_flag,
      aux_sym_memory_operand_repeat1,
    ACTIONS(867), 5,
      sym_string,
      anon_sym_volatile,
      anon_sym_non_DASHtemporal,
      anon_sym_dereferenceable,
      anon_sym_invariant,
  [7912] = 4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(871), 2,
      anon_sym_load,
      anon_sym_store,
    STATE(254), 2,
      sym_memory_operand_flag,
      aux_sym_memory_operand_repeat1,
    ACTIONS(867), 5,
      sym_string,
      anon_sym_volatile,
      anon_sym_non_DASHtemporal,
      anon_sym_dereferenceable,
      anon_sym_invariant,
  [7932] = 4,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(822), 2,
      anon_sym_pre_DASHinstr_DASHsymbol,
      anon_sym_post_DASHinstr_DASHsymbol,
    ACTIONS(826), 2,
      anon_sym_cfi_DASHtype,
      anon_sym_debug_DASHinstr_DASHnumber,
    ACTIONS(824), 4,
      anon_sym_heap_DASHalloc_DASHmarker,
      anon_sym_pcsections,
      anon_sym_mmra,
      anon_sym_debug_DASHlocation,
  [7951] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(873), 7,
      sym_string,
      anon_sym_load,
      anon_sym_store,
      anon_sym_volatile,
      anon_sym_non_DASHtemporal,
      anon_sym_dereferenceable,
      anon_sym_invariant,
  [7965] = 6,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(877), 1,
      anon_sym_RPAREN,
    STATE(426), 1,
      sym_offset,
    STATE(433), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(545), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
  [7986] = 6,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(879), 1,
      anon_sym_RPAREN,
    STATE(441), 1,
      sym_offset,
    STATE(444), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(545), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
  [8007] = 5,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(879), 1,
      anon_sym_RPAREN,
    STATE(444), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(881), 3,
      anon_sym_on,
      anon_sym_from,
      anon_sym_into,
  [8026] = 6,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(883), 1,
      anon_sym_RPAREN,
    STATE(436), 1,
      sym_offset,
    STATE(437), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(545), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
  [8047] = 5,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(885), 1,
      anon_sym_RPAREN,
    STATE(397), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(887), 3,
      anon_sym_on,
      anon_sym_from,
      anon_sym_into,
  [8066] = 5,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(883), 1,
      anon_sym_RPAREN,
    STATE(437), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(889), 3,
      anon_sym_on,
      anon_sym_from,
      anon_sym_into,
  [8085] = 6,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(891), 1,
      anon_sym_RPAREN,
    STATE(428), 1,
      sym_offset,
    STATE(431), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(545), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
  [8106] = 5,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(893), 1,
      anon_sym_RPAREN,
    STATE(403), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(895), 3,
      anon_sym_on,
      anon_sym_from,
      anon_sym_into,
  [8125] = 6,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(897), 1,
      anon_sym_RPAREN,
    STATE(462), 1,
      sym_offset,
    STATE(465), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(545), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
  [8146] = 5,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(897), 1,
      anon_sym_RPAREN,
    STATE(465), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(899), 3,
      anon_sym_on,
      anon_sym_from,
      anon_sym_into,
  [8165] = 6,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(901), 1,
      anon_sym_RPAREN,
    STATE(423), 1,
      sym_offset,
    STATE(424), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(545), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
  [8186] = 6,
    ACTIONS(11), 1,
      sym_identifier,
    ACTIONS(903), 1,
      ts_builtin_sym_end,
    ACTIONS(905), 1,
      sym__newline,
    STATE(504), 1,
      sym_label,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(275), 2,
      sym_basic_block,
      aux_sym_body_repeat1,
  [8207] = 6,
    ACTIONS(907), 1,
      ts_builtin_sym_end,
    ACTIONS(909), 1,
      sym__newline,
    ACTIONS(912), 1,
      sym_identifier,
    STATE(504), 1,
      sym_label,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(273), 2,
      sym_basic_block,
      aux_sym_body_repeat1,
  [8228] = 5,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(915), 1,
      anon_sym_RPAREN,
    STATE(442), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(917), 3,
      anon_sym_on,
      anon_sym_from,
      anon_sym_into,
  [8247] = 6,
    ACTIONS(11), 1,
      sym_identifier,
    ACTIONS(919), 1,
      ts_builtin_sym_end,
    ACTIONS(921), 1,
      sym__newline,
    STATE(504), 1,
      sym_label,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(273), 2,
      sym_basic_block,
      aux_sym_body_repeat1,
  [8268] = 6,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(915), 1,
      anon_sym_RPAREN,
    STATE(442), 1,
      aux_sym_memory_operand_repeat2,
    STATE(450), 1,
      sym_offset,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(545), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
  [8289] = 6,
    ACTIONS(11), 1,
      sym_identifier,
    ACTIONS(903), 1,
      ts_builtin_sym_end,
    ACTIONS(921), 1,
      sym__newline,
    STATE(504), 1,
      sym_label,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    STATE(273), 2,
      sym_basic_block,
      aux_sym_body_repeat1,
  [8310] = 5,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(923), 1,
      anon_sym_RPAREN,
    STATE(445), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(925), 3,
      anon_sym_on,
      anon_sym_from,
      anon_sym_into,
  [8329] = 6,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(923), 1,
      anon_sym_RPAREN,
    STATE(445), 1,
      aux_sym_memory_operand_repeat2,
    STATE(454), 1,
      sym_offset,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(545), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
  [8350] = 5,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(877), 1,
      anon_sym_RPAREN,
    STATE(433), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(927), 3,
      anon_sym_on,
      anon_sym_from,
      anon_sym_into,
  [8369] = 4,
    ACTIONS(929), 1,
      sym_metadata_ref,
    STATE(503), 1,
      sym_mem_attribute,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(931), 3,
      anon_sym_align,
      anon_sym_basealign,
      anon_sym_addrspace,
  [8385] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(356), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(159), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8400] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(935), 4,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
  [8411] = 4,
    ACTIONS(937), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(940), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8426] = 4,
    ACTIONS(410), 1,
      anon_sym_LPAREN,
    ACTIONS(942), 1,
      anon_sym_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(412), 2,
      anon_sym_COMMA,
      anon_sym_EQ,
  [8441] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(946), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8456] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(286), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(948), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8471] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(948), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8486] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(950), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8501] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(354), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(669), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8516] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(287), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(952), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8531] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(288), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(952), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8546] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(952), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8561] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(289), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(954), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8576] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(954), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8591] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(956), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8606] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(958), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8621] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(292), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(838), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8636] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(361), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(159), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8651] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(838), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8666] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(293), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(838), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8681] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(294), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(960), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8696] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(295), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(960), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8711] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(960), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8726] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(296), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(962), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8741] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(365), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(695), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8756] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(962), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8771] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(297), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(964), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8786] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(320), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(147), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8801] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(375), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(175), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8816] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(319), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(147), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8831] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(377), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(175), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8846] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(147), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8861] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(964), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8876] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(175), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8891] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(315), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(111), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8906] = 5,
    ACTIONS(966), 1,
      anon_sym_LT,
    ACTIONS(968), 1,
      anon_sym_tied_DASHdef,
    ACTIONS(970), 1,
      sym_primitive_type,
    STATE(539), 1,
      sym_low_level_type,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [8923] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(310), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(111), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8938] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(382), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(828), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8953] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(828), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8968] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(383), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(828), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8983] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(299), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(591), 2,
      sym__newline,
      anon_sym_LBRACE,
  [8998] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(300), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(135), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9013] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(301), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(135), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9028] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(135), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9043] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(303), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(834), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9058] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(834), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9073] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(304), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(834), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9088] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(305), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(972), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9103] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(307), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(972), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9118] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(972), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9133] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(974), 4,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
  [9144] = 4,
    ACTIONS(978), 1,
      aux_sym_float_token1,
    STATE(117), 1,
      sym_float,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(976), 2,
      sym_number,
      aux_sym_float_token2,
  [9159] = 5,
    ACTIONS(966), 1,
      anon_sym_LT,
    ACTIONS(970), 1,
      sym_primitive_type,
    ACTIONS(980), 1,
      anon_sym_tied_DASHdef,
    STATE(573), 1,
      sym_low_level_type,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [9176] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(982), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9191] = 4,
    ACTIONS(984), 1,
      sym__newline,
    STATE(374), 1,
      sym_register,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(986), 2,
      sym_var,
      sym_physical_register,
  [9206] = 5,
    ACTIONS(966), 1,
      anon_sym_LT,
    ACTIONS(970), 1,
      sym_primitive_type,
    ACTIONS(988), 1,
      anon_sym_tied_DASHdef,
    STATE(556), 1,
      sym_low_level_type,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [9223] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(308), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(990), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9238] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(314), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(990), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9253] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(990), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9268] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(155), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9283] = 4,
    ACTIONS(404), 1,
      anon_sym_LPAREN,
    ACTIONS(992), 1,
      anon_sym_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(406), 2,
      anon_sym_COMMA,
      anon_sym_EQ,
  [9298] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(323), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(155), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9313] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(325), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(155), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9328] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(327), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(151), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9343] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(328), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(151), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9358] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(151), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9373] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(330), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(846), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9388] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(846), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9403] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(331), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(846), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9418] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(391), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(143), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9433] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(994), 4,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
  [9444] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(996), 4,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
  [9455] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(379), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(143), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9470] = 4,
    ACTIONS(998), 1,
      anon_sym_RPAREN,
    STATE(422), 1,
      sym_register,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1000), 2,
      sym_var,
      sym_physical_register,
  [9485] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(381), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(131), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9500] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(335), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1002), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9515] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(378), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(131), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9530] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1002), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9545] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(339), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(842), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9560] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(131), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9575] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(842), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9590] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(371), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(127), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9605] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(340), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(842), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9620] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(369), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(127), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9635] = 4,
    ACTIONS(1004), 1,
      anon_sym_RPAREN,
    STATE(392), 1,
      sym_register,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1000), 2,
      sym_var,
      sym_physical_register,
  [9650] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(341), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(139), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9665] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(344), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(139), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9680] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(163), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9695] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(345), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(163), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9710] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(347), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(163), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9725] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(367), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(703), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9740] = 5,
    ACTIONS(1006), 1,
      anon_sym_LPAREN,
    ACTIONS(1008), 1,
      anon_sym_COMMA,
    ACTIONS(1010), 1,
      sym__newline,
    STATE(412), 1,
      aux_sym_successors_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [9757] = 5,
    ACTIONS(1012), 1,
      anon_sym_COMMA,
    ACTIONS(1014), 1,
      anon_sym_COLON,
    ACTIONS(1016), 1,
      sym__newline,
    STATE(396), 1,
      aux_sym_liveins_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [9774] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(167), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9789] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(364), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(167), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9804] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(362), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(167), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9819] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(349), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(123), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9834] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(171), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9849] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(350), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(123), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9864] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(123), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9879] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(284), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1018), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9894] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(359), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1018), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9909] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(357), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1018), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9924] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(309), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(171), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9939] = 5,
    ACTIONS(966), 1,
      anon_sym_LT,
    ACTIONS(970), 1,
      sym_primitive_type,
    ACTIONS(1020), 1,
      anon_sym_tied_DASHdef,
    STATE(529), 1,
      sym_low_level_type,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [9956] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1022), 4,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
  [9967] = 4,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(316), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(679), 2,
      sym__newline,
      anon_sym_LBRACE,
  [9982] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1024), 4,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
  [9993] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1026), 4,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
  [10004] = 4,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(313), 1,
      aux_sym_instruction_repeat5,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(171), 2,
      sym__newline,
      anon_sym_LBRACE,
  [10019] = 4,
    ACTIONS(1028), 1,
      anon_sym_COMMA,
    ACTIONS(1030), 1,
      anon_sym_RPAREN,
    STATE(476), 1,
      aux_sym_custom_regmask_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10033] = 4,
    ACTIONS(1012), 1,
      anon_sym_COMMA,
    ACTIONS(1032), 1,
      sym__newline,
    STATE(455), 1,
      aux_sym_liveins_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10047] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1034), 3,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
  [10057] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1036), 3,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
  [10067] = 4,
    ACTIONS(1012), 1,
      anon_sym_COMMA,
    ACTIONS(1038), 1,
      sym__newline,
    STATE(455), 1,
      aux_sym_liveins_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10081] = 4,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(893), 1,
      anon_sym_RPAREN,
    STATE(400), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10095] = 4,
    ACTIONS(966), 1,
      anon_sym_LT,
    ACTIONS(970), 1,
      sym_primitive_type,
    STATE(592), 1,
      sym_low_level_type,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10109] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1040), 3,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
  [10119] = 4,
    ACTIONS(1042), 1,
      anon_sym_COMMA,
    ACTIONS(1045), 1,
      anon_sym_RPAREN,
    STATE(400), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10133] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1047), 3,
      sym_number,
      anon_sym_Exception,
      anon_sym_Cold,
  [10143] = 3,
    STATE(76), 1,
      sym_registerclass,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1049), 2,
      sym_identifier,
      anon_sym__,
  [10155] = 4,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(923), 1,
      anon_sym_RPAREN,
    STATE(400), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10169] = 4,
    ACTIONS(966), 1,
      anon_sym_LT,
    ACTIONS(970), 1,
      sym_primitive_type,
    STATE(545), 1,
      sym_low_level_type,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10183] = 3,
    ACTIONS(850), 1,
      anon_sym_LPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(852), 2,
      sym_number,
      anon_sym_unknown_DASHsize,
  [10195] = 4,
    ACTIONS(1051), 1,
      anon_sym_COMMA,
    ACTIONS(1053), 1,
      anon_sym_RPAREN,
    STATE(416), 1,
      aux_sym_basic_block_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10209] = 4,
    ACTIONS(1055), 1,
      anon_sym_COMMA,
    ACTIONS(1058), 1,
      anon_sym_EQ,
    STATE(407), 1,
      aux_sym_instruction_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10223] = 3,
    STATE(452), 1,
      sym_register,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(986), 2,
      sym_var,
      sym_physical_register,
  [10235] = 4,
    ACTIONS(1060), 1,
      sym__newline,
    ACTIONS(1062), 1,
      anon_sym_LBRACE,
    STATE(527), 1,
      sym_bundle,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10249] = 4,
    ACTIONS(1064), 1,
      anon_sym_COMMA,
    ACTIONS(1066), 1,
      anon_sym_EQ,
    STATE(475), 1,
      aux_sym_instruction_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10263] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(558), 3,
      anon_sym_COMMA,
      anon_sym_COLON,
      sym__newline,
  [10273] = 4,
    ACTIONS(1008), 1,
      anon_sym_COMMA,
    ACTIONS(1068), 1,
      sym__newline,
    STATE(451), 1,
      aux_sym_successors_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10287] = 4,
    ACTIONS(1008), 1,
      anon_sym_COMMA,
    ACTIONS(1070), 1,
      sym__newline,
    STATE(451), 1,
      aux_sym_successors_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10301] = 3,
    ACTIONS(1074), 1,
      sym_number,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1072), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [10313] = 3,
    ACTIONS(1076), 1,
      anon_sym_LPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1078), 2,
      sym_number,
      anon_sym_unknown_DASHsize,
  [10325] = 4,
    ACTIONS(1051), 1,
      anon_sym_COMMA,
    ACTIONS(1080), 1,
      anon_sym_RPAREN,
    STATE(430), 1,
      aux_sym_basic_block_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10339] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1082), 3,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
  [10349] = 4,
    ACTIONS(966), 1,
      anon_sym_LT,
    ACTIONS(970), 1,
      sym_primitive_type,
    STATE(525), 1,
      sym_low_level_type,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10363] = 4,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(1084), 1,
      anon_sym_RPAREN,
    STATE(400), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10377] = 4,
    ACTIONS(1086), 1,
      anon_sym_COMMA,
    ACTIONS(1088), 1,
      anon_sym_RPAREN,
    STATE(464), 1,
      aux_sym_argument_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10391] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1090), 3,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
  [10401] = 4,
    ACTIONS(1028), 1,
      anon_sym_COMMA,
    ACTIONS(1092), 1,
      anon_sym_RPAREN,
    STATE(472), 1,
      aux_sym_custom_regmask_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10415] = 4,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(1094), 1,
      anon_sym_RPAREN,
    STATE(419), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10429] = 4,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(1094), 1,
      anon_sym_RPAREN,
    STATE(400), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10443] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1096), 3,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
  [10453] = 4,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(915), 1,
      anon_sym_RPAREN,
    STATE(442), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10467] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1098), 3,
      sym_number,
      anon_sym_true,
      anon_sym_false,
  [10477] = 4,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(901), 1,
      anon_sym_RPAREN,
    STATE(424), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10491] = 3,
    STATE(142), 1,
      sym_register,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1000), 2,
      sym_var,
      sym_physical_register,
  [10503] = 4,
    ACTIONS(1100), 1,
      anon_sym_COMMA,
    ACTIONS(1103), 1,
      anon_sym_RPAREN,
    STATE(430), 1,
      aux_sym_basic_block_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10517] = 4,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(901), 1,
      anon_sym_RPAREN,
    STATE(400), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10531] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1105), 3,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
  [10541] = 4,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(915), 1,
      anon_sym_RPAREN,
    STATE(400), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10555] = 3,
    ACTIONS(814), 1,
      anon_sym_LPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(816), 2,
      sym_number,
      anon_sym_unknown_DASHsize,
  [10567] = 3,
    ACTIONS(1109), 1,
      aux_sym_float_token1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1107), 2,
      sym_number,
      aux_sym_float_token2,
  [10579] = 4,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(891), 1,
      anon_sym_RPAREN,
    STATE(431), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10593] = 4,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(891), 1,
      anon_sym_RPAREN,
    STATE(400), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10607] = 4,
    ACTIONS(1111), 1,
      anon_sym_COMMA,
    ACTIONS(1113), 1,
      anon_sym_RPAREN,
    STATE(470), 1,
      aux_sym_shuffle_mask_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10621] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1115), 3,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
  [10631] = 3,
    STATE(483), 1,
      sym_register,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1000), 2,
      sym_var,
      sym_physical_register,
  [10643] = 4,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(883), 1,
      anon_sym_RPAREN,
    STATE(437), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10657] = 4,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(897), 1,
      anon_sym_RPAREN,
    STATE(400), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10671] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1117), 3,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
  [10681] = 4,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(883), 1,
      anon_sym_RPAREN,
    STATE(400), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10695] = 4,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(877), 1,
      anon_sym_RPAREN,
    STATE(400), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10709] = 3,
    STATE(78), 1,
      sym_registerclass,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1049), 2,
      sym_identifier,
      anon_sym__,
  [10721] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1119), 3,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
  [10731] = 3,
    ACTIONS(1121), 1,
      anon_sym_LPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1123), 2,
      anon_sym_COMMA,
      sym__newline,
  [10743] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1125), 3,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
  [10753] = 4,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(897), 1,
      anon_sym_RPAREN,
    STATE(465), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10767] = 4,
    ACTIONS(1123), 1,
      sym__newline,
    ACTIONS(1127), 1,
      anon_sym_COMMA,
    STATE(451), 1,
      aux_sym_successors_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10781] = 3,
    ACTIONS(1132), 1,
      anon_sym_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1130), 2,
      anon_sym_COMMA,
      sym__newline,
  [10793] = 4,
    ACTIONS(1012), 1,
      anon_sym_COMMA,
    ACTIONS(1134), 1,
      sym__newline,
    STATE(393), 1,
      aux_sym_liveins_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10807] = 4,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(877), 1,
      anon_sym_RPAREN,
    STATE(433), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10821] = 4,
    ACTIONS(1130), 1,
      sym__newline,
    ACTIONS(1136), 1,
      anon_sym_COMMA,
    STATE(455), 1,
      aux_sym_liveins_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10835] = 4,
    ACTIONS(1008), 1,
      anon_sym_COMMA,
    ACTIONS(1139), 1,
      sym__newline,
    STATE(413), 1,
      aux_sym_successors_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10849] = 3,
    STATE(563), 1,
      sym_register,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1000), 2,
      sym_var,
      sym_physical_register,
  [10861] = 4,
    ACTIONS(966), 1,
      anon_sym_LT,
    ACTIONS(970), 1,
      sym_primitive_type,
    STATE(519), 1,
      sym_low_level_type,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10875] = 3,
    ACTIONS(854), 1,
      anon_sym_LPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(856), 2,
      sym_number,
      anon_sym_unknown_DASHsize,
  [10887] = 3,
    STATE(163), 1,
      sym_register,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1000), 2,
      sym_var,
      sym_physical_register,
  [10899] = 4,
    ACTIONS(1141), 1,
      anon_sym_COMMA,
    ACTIONS(1144), 1,
      anon_sym_RPAREN,
    STATE(461), 1,
      aux_sym_argument_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10913] = 4,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(879), 1,
      anon_sym_RPAREN,
    STATE(444), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10927] = 3,
    STATE(560), 1,
      sym_register,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1000), 2,
      sym_var,
      sym_physical_register,
  [10939] = 4,
    ACTIONS(1086), 1,
      anon_sym_COMMA,
    ACTIONS(1146), 1,
      anon_sym_RPAREN,
    STATE(461), 1,
      aux_sym_argument_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10953] = 4,
    ACTIONS(875), 1,
      anon_sym_COMMA,
    ACTIONS(879), 1,
      anon_sym_RPAREN,
    STATE(400), 1,
      aux_sym_memory_operand_repeat2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10967] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1148), 3,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
  [10977] = 4,
    ACTIONS(1150), 1,
      anon_sym_COMMA,
    ACTIONS(1153), 1,
      anon_sym_RPAREN,
    STATE(467), 1,
      aux_sym_custom_regmask_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [10991] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(940), 3,
      anon_sym_COMMA,
      sym__newline,
      anon_sym_LBRACE,
  [11001] = 3,
    STATE(552), 1,
      sym_register,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1000), 2,
      sym_var,
      sym_physical_register,
  [11013] = 4,
    ACTIONS(1111), 1,
      anon_sym_COMMA,
    ACTIONS(1155), 1,
      anon_sym_RPAREN,
    STATE(474), 1,
      aux_sym_shuffle_mask_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11027] = 4,
    ACTIONS(966), 1,
      anon_sym_LT,
    ACTIONS(970), 1,
      sym_primitive_type,
    STATE(543), 1,
      sym_low_level_type,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11041] = 4,
    ACTIONS(1028), 1,
      anon_sym_COMMA,
    ACTIONS(1157), 1,
      anon_sym_RPAREN,
    STATE(467), 1,
      aux_sym_custom_regmask_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11055] = 4,
    ACTIONS(966), 1,
      anon_sym_LT,
    ACTIONS(970), 1,
      sym_primitive_type,
    STATE(516), 1,
      sym_low_level_type,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11069] = 4,
    ACTIONS(1159), 1,
      anon_sym_COMMA,
    ACTIONS(1162), 1,
      anon_sym_RPAREN,
    STATE(474), 1,
      aux_sym_shuffle_mask_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11083] = 4,
    ACTIONS(1064), 1,
      anon_sym_COMMA,
    ACTIONS(1164), 1,
      anon_sym_EQ,
    STATE(407), 1,
      aux_sym_instruction_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11097] = 4,
    ACTIONS(1028), 1,
      anon_sym_COMMA,
    ACTIONS(1166), 1,
      anon_sym_RPAREN,
    STATE(467), 1,
      aux_sym_custom_regmask_repeat1,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11111] = 3,
    ACTIONS(27), 1,
      sym_metadata_ref,
    STATE(490), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11122] = 3,
    ACTIONS(1168), 1,
      sym_identifier,
    STATE(76), 1,
      sym_subregister,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11133] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1103), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [11142] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1170), 2,
      anon_sym_LPAREN,
      anon_sym_COLON,
  [11151] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1162), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [11160] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1172), 2,
      anon_sym_COMMA,
      sym__newline,
  [11169] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1153), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [11178] = 3,
    ACTIONS(27), 1,
      sym_metadata_ref,
    STATE(218), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11189] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1174), 2,
      sym_number,
      anon_sym_undef,
  [11198] = 3,
    ACTIONS(1176), 1,
      sym__newline,
    ACTIONS(1178), 1,
      sym_bb_ref,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11209] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1180), 2,
      sym_identifier,
      sym_string,
  [11218] = 3,
    ACTIONS(1168), 1,
      sym_identifier,
    STATE(78), 1,
      sym_subregister,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11229] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1182), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [11238] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1184), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [11247] = 3,
    ACTIONS(39), 1,
      anon_sym_LT,
    STATE(218), 1,
      sym_mc_symbol,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11258] = 3,
    ACTIONS(27), 1,
      sym_metadata_ref,
    STATE(206), 1,
      sym_metadata,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11269] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1186), 2,
      sym_number,
      anon_sym_undef,
  [11278] = 3,
    ACTIONS(39), 1,
      anon_sym_LT,
    STATE(206), 1,
      sym_mc_symbol,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11289] = 3,
    ACTIONS(1188), 1,
      sym_number,
    ACTIONS(1190), 1,
      anon_sym_vscale,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11300] = 3,
    ACTIONS(933), 1,
      anon_sym_LPAREN,
    STATE(468), 1,
      sym_memory_operand,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11311] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1192), 2,
      anon_sym_COMMA,
      sym__newline,
  [11320] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1072), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [11329] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1058), 2,
      anon_sym_COMMA,
      anon_sym_EQ,
  [11338] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1144), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [11347] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1194), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [11356] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1196), 2,
      sym_external_symbol,
      sym_global_var,
  [11365] = 2,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
    ACTIONS(1045), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [11374] = 3,
    ACTIONS(1198), 1,
      anon_sym_LPAREN,
    ACTIONS(1200), 1,
      anon_sym_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11385] = 2,
    ACTIONS(1202), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11393] = 2,
    ACTIONS(1204), 1,
      sym_number,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11401] = 2,
    ACTIONS(1206), 1,
      anon_sym_LPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11409] = 2,
    ACTIONS(1208), 1,
      anon_sym_LPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11417] = 2,
    ACTIONS(1210), 1,
      anon_sym_LPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11425] = 2,
    ACTIONS(1212), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11433] = 2,
    ACTIONS(1214), 1,
      sym_string,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11441] = 2,
    ACTIONS(1216), 1,
      sym__newline,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11449] = 2,
    ACTIONS(1218), 1,
      anon_sym_LPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11457] = 2,
    ACTIONS(1220), 1,
      anon_sym_LPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11465] = 2,
    ACTIONS(1222), 1,
      anon_sym_LPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11473] = 2,
    ACTIONS(816), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11481] = 2,
    ACTIONS(1224), 1,
      sym_number,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11489] = 2,
    ACTIONS(1226), 1,
      anon_sym_LPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11497] = 2,
    ACTIONS(1078), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11505] = 2,
    ACTIONS(1228), 1,
      sym_number,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11513] = 2,
    ACTIONS(1230), 1,
      sym_number,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11521] = 2,
    ACTIONS(1232), 1,
      sym_bb_ref,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11529] = 2,
    ACTIONS(1234), 1,
      sym_number,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11537] = 2,
    ACTIONS(1236), 1,
      sym_number,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11545] = 2,
    ACTIONS(1238), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11553] = 2,
    ACTIONS(1240), 1,
      sym_global_var,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11561] = 2,
    ACTIONS(1242), 1,
      sym__newline,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11569] = 2,
    ACTIONS(1244), 1,
      anon_sym_LPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11577] = 2,
    ACTIONS(1246), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11585] = 2,
    ACTIONS(1248), 1,
      sym_ir_block,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11593] = 2,
    ACTIONS(1250), 1,
      sym_identifier,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11601] = 2,
    ACTIONS(1252), 1,
      sym_number,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11609] = 2,
    ACTIONS(1254), 1,
      anon_sym_x,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11617] = 2,
    ACTIONS(1256), 1,
      anon_sym_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11625] = 2,
    ACTIONS(1258), 1,
      anon_sym_x,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11633] = 2,
    ACTIONS(1260), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11641] = 2,
    ACTIONS(1262), 1,
      anon_sym_GT,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11649] = 2,
    ACTIONS(1264), 1,
      anon_sym_x,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11657] = 2,
    ACTIONS(1266), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11665] = 2,
    ACTIONS(1268), 1,
      anon_sym_GT,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11673] = 2,
    ACTIONS(1270), 1,
      anon_sym_LPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11681] = 2,
    ACTIONS(1272), 1,
      anon_sym_LPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11689] = 2,
    ACTIONS(1274), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11697] = 2,
    ACTIONS(1276), 1,
      sym_number,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11705] = 2,
    ACTIONS(856), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11713] = 2,
    ACTIONS(1278), 1,
      sym_number,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11721] = 2,
    ACTIONS(1280), 1,
      sym_number,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11729] = 2,
    ACTIONS(490), 1,
      sym_string,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11737] = 2,
    ACTIONS(1282), 1,
      sym_number,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11745] = 2,
    ACTIONS(1284), 1,
      sym_identifier,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11753] = 2,
    ACTIONS(1286), 1,
      anon_sym_COMMA,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11761] = 2,
    ACTIONS(1288), 1,
      anon_sym_COMMA,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11769] = 2,
    ACTIONS(1290), 1,
      anon_sym_mcsymbol,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11777] = 2,
    ACTIONS(1292), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11785] = 2,
    ACTIONS(1294), 1,
      sym_number,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11793] = 2,
    ACTIONS(1296), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11801] = 2,
    ACTIONS(1298), 1,
      sym_number,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11809] = 2,
    ACTIONS(1300), 1,
      anon_sym_COMMA,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11817] = 2,
    ACTIONS(1302), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11825] = 2,
    ACTIONS(1304), 1,
      anon_sym_COMMA,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11833] = 2,
    ACTIONS(1306), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11841] = 2,
    ACTIONS(1308), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11849] = 2,
    ACTIONS(1310), 1,
      anon_sym_COMMA,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11857] = 2,
    ACTIONS(1312), 1,
      sym_number,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11865] = 2,
    ACTIONS(1314), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11873] = 2,
    ACTIONS(1316), 1,
      sym_identifier,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11881] = 2,
    ACTIONS(1318), 1,
      sym_number,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11889] = 2,
    ACTIONS(1320), 1,
      sym_global_var,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11897] = 2,
    ACTIONS(1322), 1,
      sym_number,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11905] = 2,
    ACTIONS(1324), 1,
      sym_number,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11913] = 2,
    ACTIONS(1326), 1,
      sym_number,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11921] = 2,
    ACTIONS(1328), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11929] = 2,
    ACTIONS(1330), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11937] = 2,
    ACTIONS(1332), 1,
      anon_sym_GT,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11945] = 2,
    ACTIONS(1334), 1,
      sym_number,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11953] = 2,
    ACTIONS(1336), 1,
      anon_sym_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11961] = 2,
    ACTIONS(1338), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11969] = 2,
    ACTIONS(1340), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11977] = 2,
    ACTIONS(1342), 1,
      sym__newline,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11985] = 2,
    ACTIONS(1344), 1,
      sym_primitive_type,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [11993] = 2,
    ACTIONS(1346), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [12001] = 2,
    ACTIONS(1348), 1,
      sym__newline,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [12009] = 2,
    ACTIONS(1350), 1,
      anon_sym_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [12017] = 2,
    ACTIONS(1352), 1,
      anon_sym_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [12025] = 2,
    ACTIONS(1354), 1,
      sym_primitive_type,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [12033] = 2,
    ACTIONS(1356), 1,
      sym__newline,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [12041] = 2,
    ACTIONS(1358), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [12049] = 2,
    ACTIONS(1360), 1,
      sym_number,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [12057] = 2,
    ACTIONS(514), 1,
      sym_string,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [12065] = 2,
    ACTIONS(1047), 1,
      sym_ir_block,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [12073] = 2,
    ACTIONS(1047), 1,
      sym_number,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [12081] = 2,
    ACTIONS(852), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [12089] = 2,
    ACTIONS(1362), 1,
      anon_sym_COLON,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [12097] = 2,
    ACTIONS(1196), 1,
      sym_string,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
  [12105] = 2,
    ACTIONS(1364), 1,
      ts_builtin_sym_end,
    ACTIONS(3), 2,
      sym_comment,
      sym_multiline_comment,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(25)] = 0,
  [SMALL_STATE(26)] = 86,
  [SMALL_STATE(27)] = 172,
  [SMALL_STATE(28)] = 258,
  [SMALL_STATE(29)] = 344,
  [SMALL_STATE(30)] = 430,
  [SMALL_STATE(31)] = 516,
  [SMALL_STATE(32)] = 602,
  [SMALL_STATE(33)] = 688,
  [SMALL_STATE(34)] = 761,
  [SMALL_STATE(35)] = 834,
  [SMALL_STATE(36)] = 907,
  [SMALL_STATE(37)] = 980,
  [SMALL_STATE(38)] = 1053,
  [SMALL_STATE(39)] = 1126,
  [SMALL_STATE(40)] = 1199,
  [SMALL_STATE(41)] = 1272,
  [SMALL_STATE(42)] = 1345,
  [SMALL_STATE(43)] = 1418,
  [SMALL_STATE(44)] = 1477,
  [SMALL_STATE(45)] = 1523,
  [SMALL_STATE(46)] = 1571,
  [SMALL_STATE(47)] = 1615,
  [SMALL_STATE(48)] = 1659,
  [SMALL_STATE(49)] = 1703,
  [SMALL_STATE(50)] = 1736,
  [SMALL_STATE(51)] = 1769,
  [SMALL_STATE(52)] = 1802,
  [SMALL_STATE(53)] = 1835,
  [SMALL_STATE(54)] = 1868,
  [SMALL_STATE(55)] = 1901,
  [SMALL_STATE(56)] = 1928,
  [SMALL_STATE(57)] = 1974,
  [SMALL_STATE(58)] = 2013,
  [SMALL_STATE(59)] = 2041,
  [SMALL_STATE(60)] = 2069,
  [SMALL_STATE(61)] = 2095,
  [SMALL_STATE(62)] = 2123,
  [SMALL_STATE(63)] = 2166,
  [SMALL_STATE(64)] = 2191,
  [SMALL_STATE(65)] = 2234,
  [SMALL_STATE(66)] = 2277,
  [SMALL_STATE(67)] = 2320,
  [SMALL_STATE(68)] = 2345,
  [SMALL_STATE(69)] = 2388,
  [SMALL_STATE(70)] = 2431,
  [SMALL_STATE(71)] = 2474,
  [SMALL_STATE(72)] = 2517,
  [SMALL_STATE(73)] = 2542,
  [SMALL_STATE(74)] = 2585,
  [SMALL_STATE(75)] = 2608,
  [SMALL_STATE(76)] = 2651,
  [SMALL_STATE(77)] = 2676,
  [SMALL_STATE(78)] = 2719,
  [SMALL_STATE(79)] = 2744,
  [SMALL_STATE(80)] = 2787,
  [SMALL_STATE(81)] = 2822,
  [SMALL_STATE(82)] = 2847,
  [SMALL_STATE(83)] = 2890,
  [SMALL_STATE(84)] = 2933,
  [SMALL_STATE(85)] = 2956,
  [SMALL_STATE(86)] = 2983,
  [SMALL_STATE(87)] = 3010,
  [SMALL_STATE(88)] = 3053,
  [SMALL_STATE(89)] = 3078,
  [SMALL_STATE(90)] = 3103,
  [SMALL_STATE(91)] = 3128,
  [SMALL_STATE(92)] = 3171,
  [SMALL_STATE(93)] = 3196,
  [SMALL_STATE(94)] = 3239,
  [SMALL_STATE(95)] = 3282,
  [SMALL_STATE(96)] = 3307,
  [SMALL_STATE(97)] = 3332,
  [SMALL_STATE(98)] = 3375,
  [SMALL_STATE(99)] = 3418,
  [SMALL_STATE(100)] = 3461,
  [SMALL_STATE(101)] = 3504,
  [SMALL_STATE(102)] = 3547,
  [SMALL_STATE(103)] = 3590,
  [SMALL_STATE(104)] = 3633,
  [SMALL_STATE(105)] = 3676,
  [SMALL_STATE(106)] = 3719,
  [SMALL_STATE(107)] = 3762,
  [SMALL_STATE(108)] = 3794,
  [SMALL_STATE(109)] = 3816,
  [SMALL_STATE(110)] = 3838,
  [SMALL_STATE(111)] = 3866,
  [SMALL_STATE(112)] = 3892,
  [SMALL_STATE(113)] = 3924,
  [SMALL_STATE(114)] = 3950,
  [SMALL_STATE(115)] = 3972,
  [SMALL_STATE(116)] = 3994,
  [SMALL_STATE(117)] = 4016,
  [SMALL_STATE(118)] = 4042,
  [SMALL_STATE(119)] = 4068,
  [SMALL_STATE(120)] = 4090,
  [SMALL_STATE(121)] = 4112,
  [SMALL_STATE(122)] = 4134,
  [SMALL_STATE(123)] = 4160,
  [SMALL_STATE(124)] = 4195,
  [SMALL_STATE(125)] = 4230,
  [SMALL_STATE(126)] = 4251,
  [SMALL_STATE(127)] = 4272,
  [SMALL_STATE(128)] = 4307,
  [SMALL_STATE(129)] = 4328,
  [SMALL_STATE(130)] = 4363,
  [SMALL_STATE(131)] = 4398,
  [SMALL_STATE(132)] = 4419,
  [SMALL_STATE(133)] = 4454,
  [SMALL_STATE(134)] = 4493,
  [SMALL_STATE(135)] = 4528,
  [SMALL_STATE(136)] = 4549,
  [SMALL_STATE(137)] = 4570,
  [SMALL_STATE(138)] = 4605,
  [SMALL_STATE(139)] = 4640,
  [SMALL_STATE(140)] = 4661,
  [SMALL_STATE(141)] = 4682,
  [SMALL_STATE(142)] = 4717,
  [SMALL_STATE(143)] = 4738,
  [SMALL_STATE(144)] = 4759,
  [SMALL_STATE(145)] = 4794,
  [SMALL_STATE(146)] = 4815,
  [SMALL_STATE(147)] = 4854,
  [SMALL_STATE(148)] = 4889,
  [SMALL_STATE(149)] = 4924,
  [SMALL_STATE(150)] = 4945,
  [SMALL_STATE(151)] = 4966,
  [SMALL_STATE(152)] = 4987,
  [SMALL_STATE(153)] = 5008,
  [SMALL_STATE(154)] = 5029,
  [SMALL_STATE(155)] = 5064,
  [SMALL_STATE(156)] = 5099,
  [SMALL_STATE(157)] = 5134,
  [SMALL_STATE(158)] = 5169,
  [SMALL_STATE(159)] = 5190,
  [SMALL_STATE(160)] = 5229,
  [SMALL_STATE(161)] = 5268,
  [SMALL_STATE(162)] = 5303,
  [SMALL_STATE(163)] = 5324,
  [SMALL_STATE(164)] = 5345,
  [SMALL_STATE(165)] = 5380,
  [SMALL_STATE(166)] = 5415,
  [SMALL_STATE(167)] = 5450,
  [SMALL_STATE(168)] = 5485,
  [SMALL_STATE(169)] = 5520,
  [SMALL_STATE(170)] = 5555,
  [SMALL_STATE(171)] = 5590,
  [SMALL_STATE(172)] = 5629,
  [SMALL_STATE(173)] = 5650,
  [SMALL_STATE(174)] = 5685,
  [SMALL_STATE(175)] = 5720,
  [SMALL_STATE(176)] = 5755,
  [SMALL_STATE(177)] = 5790,
  [SMALL_STATE(178)] = 5829,
  [SMALL_STATE(179)] = 5864,
  [SMALL_STATE(180)] = 5896,
  [SMALL_STATE(181)] = 5928,
  [SMALL_STATE(182)] = 5960,
  [SMALL_STATE(183)] = 5992,
  [SMALL_STATE(184)] = 6024,
  [SMALL_STATE(185)] = 6056,
  [SMALL_STATE(186)] = 6088,
  [SMALL_STATE(187)] = 6120,
  [SMALL_STATE(188)] = 6152,
  [SMALL_STATE(189)] = 6184,
  [SMALL_STATE(190)] = 6216,
  [SMALL_STATE(191)] = 6248,
  [SMALL_STATE(192)] = 6268,
  [SMALL_STATE(193)] = 6300,
  [SMALL_STATE(194)] = 6332,
  [SMALL_STATE(195)] = 6364,
  [SMALL_STATE(196)] = 6396,
  [SMALL_STATE(197)] = 6428,
  [SMALL_STATE(198)] = 6460,
  [SMALL_STATE(199)] = 6492,
  [SMALL_STATE(200)] = 6524,
  [SMALL_STATE(201)] = 6556,
  [SMALL_STATE(202)] = 6578,
  [SMALL_STATE(203)] = 6608,
  [SMALL_STATE(204)] = 6640,
  [SMALL_STATE(205)] = 6664,
  [SMALL_STATE(206)] = 6683,
  [SMALL_STATE(207)] = 6702,
  [SMALL_STATE(208)] = 6721,
  [SMALL_STATE(209)] = 6740,
  [SMALL_STATE(210)] = 6759,
  [SMALL_STATE(211)] = 6790,
  [SMALL_STATE(212)] = 6809,
  [SMALL_STATE(213)] = 6828,
  [SMALL_STATE(214)] = 6857,
  [SMALL_STATE(215)] = 6876,
  [SMALL_STATE(216)] = 6895,
  [SMALL_STATE(217)] = 6914,
  [SMALL_STATE(218)] = 6943,
  [SMALL_STATE(219)] = 6962,
  [SMALL_STATE(220)] = 6981,
  [SMALL_STATE(221)] = 7007,
  [SMALL_STATE(222)] = 7033,
  [SMALL_STATE(223)] = 7059,
  [SMALL_STATE(224)] = 7085,
  [SMALL_STATE(225)] = 7111,
  [SMALL_STATE(226)] = 7137,
  [SMALL_STATE(227)] = 7163,
  [SMALL_STATE(228)] = 7189,
  [SMALL_STATE(229)] = 7209,
  [SMALL_STATE(230)] = 7235,
  [SMALL_STATE(231)] = 7261,
  [SMALL_STATE(232)] = 7287,
  [SMALL_STATE(233)] = 7313,
  [SMALL_STATE(234)] = 7339,
  [SMALL_STATE(235)] = 7365,
  [SMALL_STATE(236)] = 7391,
  [SMALL_STATE(237)] = 7417,
  [SMALL_STATE(238)] = 7443,
  [SMALL_STATE(239)] = 7469,
  [SMALL_STATE(240)] = 7495,
  [SMALL_STATE(241)] = 7521,
  [SMALL_STATE(242)] = 7547,
  [SMALL_STATE(243)] = 7573,
  [SMALL_STATE(244)] = 7599,
  [SMALL_STATE(245)] = 7625,
  [SMALL_STATE(246)] = 7651,
  [SMALL_STATE(247)] = 7679,
  [SMALL_STATE(248)] = 7702,
  [SMALL_STATE(249)] = 7725,
  [SMALL_STATE(250)] = 7748,
  [SMALL_STATE(251)] = 7771,
  [SMALL_STATE(252)] = 7794,
  [SMALL_STATE(253)] = 7817,
  [SMALL_STATE(254)] = 7840,
  [SMALL_STATE(255)] = 7860,
  [SMALL_STATE(256)] = 7876,
  [SMALL_STATE(257)] = 7892,
  [SMALL_STATE(258)] = 7912,
  [SMALL_STATE(259)] = 7932,
  [SMALL_STATE(260)] = 7951,
  [SMALL_STATE(261)] = 7965,
  [SMALL_STATE(262)] = 7986,
  [SMALL_STATE(263)] = 8007,
  [SMALL_STATE(264)] = 8026,
  [SMALL_STATE(265)] = 8047,
  [SMALL_STATE(266)] = 8066,
  [SMALL_STATE(267)] = 8085,
  [SMALL_STATE(268)] = 8106,
  [SMALL_STATE(269)] = 8125,
  [SMALL_STATE(270)] = 8146,
  [SMALL_STATE(271)] = 8165,
  [SMALL_STATE(272)] = 8186,
  [SMALL_STATE(273)] = 8207,
  [SMALL_STATE(274)] = 8228,
  [SMALL_STATE(275)] = 8247,
  [SMALL_STATE(276)] = 8268,
  [SMALL_STATE(277)] = 8289,
  [SMALL_STATE(278)] = 8310,
  [SMALL_STATE(279)] = 8329,
  [SMALL_STATE(280)] = 8350,
  [SMALL_STATE(281)] = 8369,
  [SMALL_STATE(282)] = 8385,
  [SMALL_STATE(283)] = 8400,
  [SMALL_STATE(284)] = 8411,
  [SMALL_STATE(285)] = 8426,
  [SMALL_STATE(286)] = 8441,
  [SMALL_STATE(287)] = 8456,
  [SMALL_STATE(288)] = 8471,
  [SMALL_STATE(289)] = 8486,
  [SMALL_STATE(290)] = 8501,
  [SMALL_STATE(291)] = 8516,
  [SMALL_STATE(292)] = 8531,
  [SMALL_STATE(293)] = 8546,
  [SMALL_STATE(294)] = 8561,
  [SMALL_STATE(295)] = 8576,
  [SMALL_STATE(296)] = 8591,
  [SMALL_STATE(297)] = 8606,
  [SMALL_STATE(298)] = 8621,
  [SMALL_STATE(299)] = 8636,
  [SMALL_STATE(300)] = 8651,
  [SMALL_STATE(301)] = 8666,
  [SMALL_STATE(302)] = 8681,
  [SMALL_STATE(303)] = 8696,
  [SMALL_STATE(304)] = 8711,
  [SMALL_STATE(305)] = 8726,
  [SMALL_STATE(306)] = 8741,
  [SMALL_STATE(307)] = 8756,
  [SMALL_STATE(308)] = 8771,
  [SMALL_STATE(309)] = 8786,
  [SMALL_STATE(310)] = 8801,
  [SMALL_STATE(311)] = 8816,
  [SMALL_STATE(312)] = 8831,
  [SMALL_STATE(313)] = 8846,
  [SMALL_STATE(314)] = 8861,
  [SMALL_STATE(315)] = 8876,
  [SMALL_STATE(316)] = 8891,
  [SMALL_STATE(317)] = 8906,
  [SMALL_STATE(318)] = 8923,
  [SMALL_STATE(319)] = 8938,
  [SMALL_STATE(320)] = 8953,
  [SMALL_STATE(321)] = 8968,
  [SMALL_STATE(322)] = 8983,
  [SMALL_STATE(323)] = 8998,
  [SMALL_STATE(324)] = 9013,
  [SMALL_STATE(325)] = 9028,
  [SMALL_STATE(326)] = 9043,
  [SMALL_STATE(327)] = 9058,
  [SMALL_STATE(328)] = 9073,
  [SMALL_STATE(329)] = 9088,
  [SMALL_STATE(330)] = 9103,
  [SMALL_STATE(331)] = 9118,
  [SMALL_STATE(332)] = 9133,
  [SMALL_STATE(333)] = 9144,
  [SMALL_STATE(334)] = 9159,
  [SMALL_STATE(335)] = 9176,
  [SMALL_STATE(336)] = 9191,
  [SMALL_STATE(337)] = 9206,
  [SMALL_STATE(338)] = 9223,
  [SMALL_STATE(339)] = 9238,
  [SMALL_STATE(340)] = 9253,
  [SMALL_STATE(341)] = 9268,
  [SMALL_STATE(342)] = 9283,
  [SMALL_STATE(343)] = 9298,
  [SMALL_STATE(344)] = 9313,
  [SMALL_STATE(345)] = 9328,
  [SMALL_STATE(346)] = 9343,
  [SMALL_STATE(347)] = 9358,
  [SMALL_STATE(348)] = 9373,
  [SMALL_STATE(349)] = 9388,
  [SMALL_STATE(350)] = 9403,
  [SMALL_STATE(351)] = 9418,
  [SMALL_STATE(352)] = 9433,
  [SMALL_STATE(353)] = 9444,
  [SMALL_STATE(354)] = 9455,
  [SMALL_STATE(355)] = 9470,
  [SMALL_STATE(356)] = 9485,
  [SMALL_STATE(357)] = 9500,
  [SMALL_STATE(358)] = 9515,
  [SMALL_STATE(359)] = 9530,
  [SMALL_STATE(360)] = 9545,
  [SMALL_STATE(361)] = 9560,
  [SMALL_STATE(362)] = 9575,
  [SMALL_STATE(363)] = 9590,
  [SMALL_STATE(364)] = 9605,
  [SMALL_STATE(365)] = 9620,
  [SMALL_STATE(366)] = 9635,
  [SMALL_STATE(367)] = 9650,
  [SMALL_STATE(368)] = 9665,
  [SMALL_STATE(369)] = 9680,
  [SMALL_STATE(370)] = 9695,
  [SMALL_STATE(371)] = 9710,
  [SMALL_STATE(372)] = 9725,
  [SMALL_STATE(373)] = 9740,
  [SMALL_STATE(374)] = 9757,
  [SMALL_STATE(375)] = 9774,
  [SMALL_STATE(376)] = 9789,
  [SMALL_STATE(377)] = 9804,
  [SMALL_STATE(378)] = 9819,
  [SMALL_STATE(379)] = 9834,
  [SMALL_STATE(380)] = 9849,
  [SMALL_STATE(381)] = 9864,
  [SMALL_STATE(382)] = 9879,
  [SMALL_STATE(383)] = 9894,
  [SMALL_STATE(384)] = 9909,
  [SMALL_STATE(385)] = 9924,
  [SMALL_STATE(386)] = 9939,
  [SMALL_STATE(387)] = 9956,
  [SMALL_STATE(388)] = 9967,
  [SMALL_STATE(389)] = 9982,
  [SMALL_STATE(390)] = 9993,
  [SMALL_STATE(391)] = 10004,
  [SMALL_STATE(392)] = 10019,
  [SMALL_STATE(393)] = 10033,
  [SMALL_STATE(394)] = 10047,
  [SMALL_STATE(395)] = 10057,
  [SMALL_STATE(396)] = 10067,
  [SMALL_STATE(397)] = 10081,
  [SMALL_STATE(398)] = 10095,
  [SMALL_STATE(399)] = 10109,
  [SMALL_STATE(400)] = 10119,
  [SMALL_STATE(401)] = 10133,
  [SMALL_STATE(402)] = 10143,
  [SMALL_STATE(403)] = 10155,
  [SMALL_STATE(404)] = 10169,
  [SMALL_STATE(405)] = 10183,
  [SMALL_STATE(406)] = 10195,
  [SMALL_STATE(407)] = 10209,
  [SMALL_STATE(408)] = 10223,
  [SMALL_STATE(409)] = 10235,
  [SMALL_STATE(410)] = 10249,
  [SMALL_STATE(411)] = 10263,
  [SMALL_STATE(412)] = 10273,
  [SMALL_STATE(413)] = 10287,
  [SMALL_STATE(414)] = 10301,
  [SMALL_STATE(415)] = 10313,
  [SMALL_STATE(416)] = 10325,
  [SMALL_STATE(417)] = 10339,
  [SMALL_STATE(418)] = 10349,
  [SMALL_STATE(419)] = 10363,
  [SMALL_STATE(420)] = 10377,
  [SMALL_STATE(421)] = 10391,
  [SMALL_STATE(422)] = 10401,
  [SMALL_STATE(423)] = 10415,
  [SMALL_STATE(424)] = 10429,
  [SMALL_STATE(425)] = 10443,
  [SMALL_STATE(426)] = 10453,
  [SMALL_STATE(427)] = 10467,
  [SMALL_STATE(428)] = 10477,
  [SMALL_STATE(429)] = 10491,
  [SMALL_STATE(430)] = 10503,
  [SMALL_STATE(431)] = 10517,
  [SMALL_STATE(432)] = 10531,
  [SMALL_STATE(433)] = 10541,
  [SMALL_STATE(434)] = 10555,
  [SMALL_STATE(435)] = 10567,
  [SMALL_STATE(436)] = 10579,
  [SMALL_STATE(437)] = 10593,
  [SMALL_STATE(438)] = 10607,
  [SMALL_STATE(439)] = 10621,
  [SMALL_STATE(440)] = 10631,
  [SMALL_STATE(441)] = 10643,
  [SMALL_STATE(442)] = 10657,
  [SMALL_STATE(443)] = 10671,
  [SMALL_STATE(444)] = 10681,
  [SMALL_STATE(445)] = 10695,
  [SMALL_STATE(446)] = 10709,
  [SMALL_STATE(447)] = 10721,
  [SMALL_STATE(448)] = 10731,
  [SMALL_STATE(449)] = 10743,
  [SMALL_STATE(450)] = 10753,
  [SMALL_STATE(451)] = 10767,
  [SMALL_STATE(452)] = 10781,
  [SMALL_STATE(453)] = 10793,
  [SMALL_STATE(454)] = 10807,
  [SMALL_STATE(455)] = 10821,
  [SMALL_STATE(456)] = 10835,
  [SMALL_STATE(457)] = 10849,
  [SMALL_STATE(458)] = 10861,
  [SMALL_STATE(459)] = 10875,
  [SMALL_STATE(460)] = 10887,
  [SMALL_STATE(461)] = 10899,
  [SMALL_STATE(462)] = 10913,
  [SMALL_STATE(463)] = 10927,
  [SMALL_STATE(464)] = 10939,
  [SMALL_STATE(465)] = 10953,
  [SMALL_STATE(466)] = 10967,
  [SMALL_STATE(467)] = 10977,
  [SMALL_STATE(468)] = 10991,
  [SMALL_STATE(469)] = 11001,
  [SMALL_STATE(470)] = 11013,
  [SMALL_STATE(471)] = 11027,
  [SMALL_STATE(472)] = 11041,
  [SMALL_STATE(473)] = 11055,
  [SMALL_STATE(474)] = 11069,
  [SMALL_STATE(475)] = 11083,
  [SMALL_STATE(476)] = 11097,
  [SMALL_STATE(477)] = 11111,
  [SMALL_STATE(478)] = 11122,
  [SMALL_STATE(479)] = 11133,
  [SMALL_STATE(480)] = 11142,
  [SMALL_STATE(481)] = 11151,
  [SMALL_STATE(482)] = 11160,
  [SMALL_STATE(483)] = 11169,
  [SMALL_STATE(484)] = 11178,
  [SMALL_STATE(485)] = 11189,
  [SMALL_STATE(486)] = 11198,
  [SMALL_STATE(487)] = 11209,
  [SMALL_STATE(488)] = 11218,
  [SMALL_STATE(489)] = 11229,
  [SMALL_STATE(490)] = 11238,
  [SMALL_STATE(491)] = 11247,
  [SMALL_STATE(492)] = 11258,
  [SMALL_STATE(493)] = 11269,
  [SMALL_STATE(494)] = 11278,
  [SMALL_STATE(495)] = 11289,
  [SMALL_STATE(496)] = 11300,
  [SMALL_STATE(497)] = 11311,
  [SMALL_STATE(498)] = 11320,
  [SMALL_STATE(499)] = 11329,
  [SMALL_STATE(500)] = 11338,
  [SMALL_STATE(501)] = 11347,
  [SMALL_STATE(502)] = 11356,
  [SMALL_STATE(503)] = 11365,
  [SMALL_STATE(504)] = 11374,
  [SMALL_STATE(505)] = 11385,
  [SMALL_STATE(506)] = 11393,
  [SMALL_STATE(507)] = 11401,
  [SMALL_STATE(508)] = 11409,
  [SMALL_STATE(509)] = 11417,
  [SMALL_STATE(510)] = 11425,
  [SMALL_STATE(511)] = 11433,
  [SMALL_STATE(512)] = 11441,
  [SMALL_STATE(513)] = 11449,
  [SMALL_STATE(514)] = 11457,
  [SMALL_STATE(515)] = 11465,
  [SMALL_STATE(516)] = 11473,
  [SMALL_STATE(517)] = 11481,
  [SMALL_STATE(518)] = 11489,
  [SMALL_STATE(519)] = 11497,
  [SMALL_STATE(520)] = 11505,
  [SMALL_STATE(521)] = 11513,
  [SMALL_STATE(522)] = 11521,
  [SMALL_STATE(523)] = 11529,
  [SMALL_STATE(524)] = 11537,
  [SMALL_STATE(525)] = 11545,
  [SMALL_STATE(526)] = 11553,
  [SMALL_STATE(527)] = 11561,
  [SMALL_STATE(528)] = 11569,
  [SMALL_STATE(529)] = 11577,
  [SMALL_STATE(530)] = 11585,
  [SMALL_STATE(531)] = 11593,
  [SMALL_STATE(532)] = 11601,
  [SMALL_STATE(533)] = 11609,
  [SMALL_STATE(534)] = 11617,
  [SMALL_STATE(535)] = 11625,
  [SMALL_STATE(536)] = 11633,
  [SMALL_STATE(537)] = 11641,
  [SMALL_STATE(538)] = 11649,
  [SMALL_STATE(539)] = 11657,
  [SMALL_STATE(540)] = 11665,
  [SMALL_STATE(541)] = 11673,
  [SMALL_STATE(542)] = 11681,
  [SMALL_STATE(543)] = 11689,
  [SMALL_STATE(544)] = 11697,
  [SMALL_STATE(545)] = 11705,
  [SMALL_STATE(546)] = 11713,
  [SMALL_STATE(547)] = 11721,
  [SMALL_STATE(548)] = 11729,
  [SMALL_STATE(549)] = 11737,
  [SMALL_STATE(550)] = 11745,
  [SMALL_STATE(551)] = 11753,
  [SMALL_STATE(552)] = 11761,
  [SMALL_STATE(553)] = 11769,
  [SMALL_STATE(554)] = 11777,
  [SMALL_STATE(555)] = 11785,
  [SMALL_STATE(556)] = 11793,
  [SMALL_STATE(557)] = 11801,
  [SMALL_STATE(558)] = 11809,
  [SMALL_STATE(559)] = 11817,
  [SMALL_STATE(560)] = 11825,
  [SMALL_STATE(561)] = 11833,
  [SMALL_STATE(562)] = 11841,
  [SMALL_STATE(563)] = 11849,
  [SMALL_STATE(564)] = 11857,
  [SMALL_STATE(565)] = 11865,
  [SMALL_STATE(566)] = 11873,
  [SMALL_STATE(567)] = 11881,
  [SMALL_STATE(568)] = 11889,
  [SMALL_STATE(569)] = 11897,
  [SMALL_STATE(570)] = 11905,
  [SMALL_STATE(571)] = 11913,
  [SMALL_STATE(572)] = 11921,
  [SMALL_STATE(573)] = 11929,
  [SMALL_STATE(574)] = 11937,
  [SMALL_STATE(575)] = 11945,
  [SMALL_STATE(576)] = 11953,
  [SMALL_STATE(577)] = 11961,
  [SMALL_STATE(578)] = 11969,
  [SMALL_STATE(579)] = 11977,
  [SMALL_STATE(580)] = 11985,
  [SMALL_STATE(581)] = 11993,
  [SMALL_STATE(582)] = 12001,
  [SMALL_STATE(583)] = 12009,
  [SMALL_STATE(584)] = 12017,
  [SMALL_STATE(585)] = 12025,
  [SMALL_STATE(586)] = 12033,
  [SMALL_STATE(587)] = 12041,
  [SMALL_STATE(588)] = 12049,
  [SMALL_STATE(589)] = 12057,
  [SMALL_STATE(590)] = 12065,
  [SMALL_STATE(591)] = 12073,
  [SMALL_STATE(592)] = 12081,
  [SMALL_STATE(593)] = 12089,
  [SMALL_STATE(594)] = 12097,
  [SMALL_STATE(595)] = 12105,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_body, 0, 0, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(272),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(277),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(480),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(224),
  [15] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 3, 0, 3),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(113),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(113),
  [21] = {.entry = {.count = 1, .reusable = false}}, SHIFT(85),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(427),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [29] = {.entry = {.count = 1, .reusable = false}}, SHIFT(133),
  [31] = {.entry = {.count = 1, .reusable = false}}, SHIFT(494),
  [33] = {.entry = {.count = 1, .reusable = false}}, SHIFT(492),
  [35] = {.entry = {.count = 1, .reusable = false}}, SHIFT(555),
  [37] = {.entry = {.count = 1, .reusable = true}}, SHIFT(322),
  [39] = {.entry = {.count = 1, .reusable = true}}, SHIFT(553),
  [41] = {.entry = {.count = 1, .reusable = false}}, SHIFT(63),
  [43] = {.entry = {.count = 1, .reusable = false}}, SHIFT(542),
  [45] = {.entry = {.count = 1, .reusable = false}}, SHIFT(541),
  [47] = {.entry = {.count = 1, .reusable = false}}, SHIFT(460),
  [49] = {.entry = {.count = 1, .reusable = false}}, SHIFT(469),
  [51] = {.entry = {.count = 1, .reusable = false}}, SHIFT(524),
  [53] = {.entry = {.count = 1, .reusable = false}}, SHIFT(463),
  [55] = {.entry = {.count = 1, .reusable = false}}, SHIFT(457),
  [57] = {.entry = {.count = 1, .reusable = false}}, SHIFT(521),
  [59] = {.entry = {.count = 1, .reusable = false}}, SHIFT(135),
  [61] = {.entry = {.count = 1, .reusable = false}}, SHIFT(515),
  [63] = {.entry = {.count = 1, .reusable = false}}, SHIFT(514),
  [65] = {.entry = {.count = 1, .reusable = false}}, SHIFT(513),
  [67] = {.entry = {.count = 1, .reusable = false}}, SHIFT(201),
  [69] = {.entry = {.count = 1, .reusable = false}}, SHIFT(509),
  [71] = {.entry = {.count = 1, .reusable = false}}, SHIFT(518),
  [73] = {.entry = {.count = 1, .reusable = false}}, SHIFT(507),
  [75] = {.entry = {.count = 1, .reusable = false}}, SHIFT(508),
  [77] = {.entry = {.count = 1, .reusable = false}}, SHIFT(435),
  [79] = {.entry = {.count = 1, .reusable = true}}, SHIFT(237),
  [81] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 4, 0, 4),
  [83] = {.entry = {.count = 1, .reusable = false}}, SHIFT(160),
  [85] = {.entry = {.count = 1, .reusable = true}}, SHIFT(306),
  [87] = {.entry = {.count = 1, .reusable = true}}, SHIFT(234),
  [89] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 5, 0, 5),
  [91] = {.entry = {.count = 1, .reusable = false}}, SHIFT(171),
  [93] = {.entry = {.count = 1, .reusable = true}}, SHIFT(372),
  [95] = {.entry = {.count = 1, .reusable = true}}, SHIFT(239),
  [97] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 1, 0, 1),
  [99] = {.entry = {.count = 1, .reusable = false}}, SHIFT(177),
  [101] = {.entry = {.count = 1, .reusable = true}}, SHIFT(290),
  [103] = {.entry = {.count = 1, .reusable = true}}, SHIFT(220),
  [105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 2, 0, 2),
  [107] = {.entry = {.count = 1, .reusable = false}}, SHIFT(159),
  [109] = {.entry = {.count = 1, .reusable = true}}, SHIFT(388),
  [111] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 4, 0, 2),
  [113] = {.entry = {.count = 1, .reusable = false}}, SHIFT(146),
  [115] = {.entry = {.count = 1, .reusable = false}}, SHIFT(491),
  [117] = {.entry = {.count = 1, .reusable = false}}, SHIFT(484),
  [119] = {.entry = {.count = 1, .reusable = false}}, SHIFT(544),
  [121] = {.entry = {.count = 1, .reusable = true}}, SHIFT(312),
  [123] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 7, 0, 3),
  [125] = {.entry = {.count = 1, .reusable = true}}, SHIFT(348),
  [127] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 6, 0, 4),
  [129] = {.entry = {.count = 1, .reusable = true}}, SHIFT(370),
  [131] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 6, 0, 3),
  [133] = {.entry = {.count = 1, .reusable = true}}, SHIFT(380),
  [135] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 9, 0, 5),
  [137] = {.entry = {.count = 1, .reusable = true}}, SHIFT(298),
  [139] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 7, 0, 5),
  [141] = {.entry = {.count = 1, .reusable = true}}, SHIFT(343),
  [143] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 3, 0, 1),
  [145] = {.entry = {.count = 1, .reusable = true}}, SHIFT(385),
  [147] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 5, 0, 1),
  [149] = {.entry = {.count = 1, .reusable = true}}, SHIFT(321),
  [151] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 8, 0, 4),
  [153] = {.entry = {.count = 1, .reusable = true}}, SHIFT(326),
  [155] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 8, 0, 5),
  [157] = {.entry = {.count = 1, .reusable = true}}, SHIFT(324),
  [159] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 5, 0, 3),
  [161] = {.entry = {.count = 1, .reusable = true}}, SHIFT(358),
  [163] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 7, 0, 4),
  [165] = {.entry = {.count = 1, .reusable = true}}, SHIFT(346),
  [167] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 6, 0, 2),
  [169] = {.entry = {.count = 1, .reusable = true}}, SHIFT(360),
  [171] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 4, 0, 1),
  [173] = {.entry = {.count = 1, .reusable = true}}, SHIFT(311),
  [175] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 5, 0, 2),
  [177] = {.entry = {.count = 1, .reusable = true}}, SHIFT(376),
  [179] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_basic_block, 6, 0, 0),
  [181] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_basic_block, 6, 0, 0), SHIFT(45),
  [184] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_basic_block, 6, 0, 0), SHIFT(5),
  [187] = {.entry = {.count = 1, .reusable = true}}, SHIFT(285),
  [189] = {.entry = {.count = 1, .reusable = false}}, SHIFT(584),
  [191] = {.entry = {.count = 1, .reusable = false}}, SHIFT(583),
  [193] = {.entry = {.count = 1, .reusable = false}}, SHIFT(55),
  [195] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_basic_block, 7, 0, 0),
  [197] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_basic_block, 7, 0, 0), SHIFT(45),
  [200] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_basic_block, 7, 0, 0), SHIFT(5),
  [203] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_basic_block, 5, 0, 0),
  [205] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_basic_block, 5, 0, 0), SHIFT(45),
  [208] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_basic_block, 5, 0, 0), SHIFT(5),
  [211] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_basic_block, 2, 0, 0),
  [213] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_basic_block, 2, 0, 0), SHIFT(45),
  [216] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_basic_block, 2, 0, 0), SHIFT(5),
  [219] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_basic_block, 3, 0, 0),
  [221] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_basic_block, 3, 0, 0), SHIFT(45),
  [224] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_basic_block, 3, 0, 0), SHIFT(5),
  [227] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_basic_block, 4, 0, 0),
  [229] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_basic_block, 4, 0, 0), SHIFT(45),
  [232] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_basic_block, 4, 0, 0), SHIFT(5),
  [235] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_basic_block, 6, 0, 0), SHIFT(35),
  [238] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_basic_block, 8, 0, 0),
  [240] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_basic_block, 8, 0, 0), SHIFT(35),
  [243] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_basic_block, 8, 0, 0), SHIFT(5),
  [246] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_basic_block_repeat3, 2, 0, 0),
  [248] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_basic_block_repeat3, 2, 0, 0), SHIFT_REPEAT(35),
  [251] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_basic_block_repeat3, 2, 0, 0), SHIFT_REPEAT(5),
  [254] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_basic_block_repeat3, 2, 0, 0), SHIFT_REPEAT(285),
  [257] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_basic_block_repeat3, 2, 0, 0), SHIFT_REPEAT(59),
  [260] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_basic_block_repeat3, 2, 0, 0), SHIFT_REPEAT(63),
  [263] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_basic_block_repeat3, 2, 0, 0), SHIFT_REPEAT(201),
  [266] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_basic_block_repeat3, 2, 0, 0), SHIFT_REPEAT(55),
  [269] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [271] = {.entry = {.count = 1, .reusable = false}}, SHIFT(5),
  [273] = {.entry = {.count = 1, .reusable = true}}, SHIFT(512),
  [275] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_bundle_repeat1, 2, 0, 0), SHIFT_REPEAT(37),
  [278] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_bundle_repeat1, 2, 0, 0), SHIFT_REPEAT(5),
  [281] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_bundle_repeat1, 2, 0, 0), SHIFT_REPEAT(285),
  [284] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_bundle_repeat1, 2, 0, 0), SHIFT_REPEAT(59),
  [287] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_bundle_repeat1, 2, 0, 0),
  [289] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_bundle_repeat1, 2, 0, 0), SHIFT_REPEAT(63),
  [292] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_bundle_repeat1, 2, 0, 0), SHIFT_REPEAT(201),
  [295] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_bundle_repeat1, 2, 0, 0), SHIFT_REPEAT(55),
  [298] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_basic_block, 4, 0, 0), SHIFT(35),
  [301] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_basic_block, 3, 0, 0), SHIFT(35),
  [304] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_basic_block, 5, 0, 0), SHIFT(35),
  [307] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_basic_block, 7, 0, 0), SHIFT(35),
  [310] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [312] = {.entry = {.count = 1, .reusable = true}}, SHIFT(579),
  [314] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_basic_block_repeat2, 2, 0, 0),
  [316] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_basic_block_repeat2, 2, 0, 0), SHIFT_REPEAT(43),
  [319] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_basic_block_repeat2, 2, 0, 0),
  [321] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_basic_block_repeat2, 2, 0, 0), SHIFT_REPEAT(584),
  [324] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_basic_block_repeat2, 2, 0, 0), SHIFT_REPEAT(583),
  [327] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_basic_block_repeat2, 1, 0, 0), REDUCE(aux_sym_basic_block_repeat3, 1, 0, 0),
  [330] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_basic_block_repeat2, 1, 0, 0), REDUCE(aux_sym_basic_block_repeat3, 1, 0, 0),
  [333] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_basic_block_repeat2, 1, 0, 0),
  [335] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_basic_block_repeat3, 2, 0, 0),
  [337] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_bundle_repeat1, 2, 0, 0),
  [339] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_basic_block_repeat3, 3, 0, 0),
  [341] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_basic_block_repeat3, 3, 0, 0),
  [343] = {.entry = {.count = 1, .reusable = false}}, SHIFT(2),
  [345] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_instruction_repeat2, 2, 0, 0),
  [347] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_instruction_repeat2, 2, 0, 0), SHIFT_REPEAT(55),
  [350] = {.entry = {.count = 1, .reusable = false}}, SHIFT(4),
  [352] = {.entry = {.count = 1, .reusable = false}}, SHIFT(3),
  [354] = {.entry = {.count = 1, .reusable = false}}, SHIFT(6),
  [356] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_instruction_flag, 1, 0, 0),
  [358] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_metadata_repeat1, 2, 0, 0), SHIFT_REPEAT(99),
  [361] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_metadata_repeat1, 2, 0, 0), SHIFT_REPEAT(88),
  [364] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_metadata_repeat1, 2, 0, 0),
  [366] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_metadata_repeat1, 2, 0, 0), SHIFT_REPEAT(61),
  [369] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_metadata_repeat1, 2, 0, 0), SHIFT_REPEAT(101),
  [372] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_metadata_repeat1, 2, 0, 0), SHIFT_REPEAT(102),
  [375] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_metadata_repeat1, 2, 0, 0), SHIFT_REPEAT(589),
  [378] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_metadata_repeat1, 2, 0, 0), SHIFT_REPEAT(88),
  [381] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_metadata_repeat1, 2, 0, 0), SHIFT_REPEAT(103),
  [384] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_escaped_ir_value_repeat1, 2, 0, 0), SHIFT_REPEAT(137),
  [387] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_escaped_ir_value_repeat1, 2, 0, 0), SHIFT_REPEAT(57),
  [390] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_escaped_ir_value_repeat1, 2, 0, 0),
  [392] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_escaped_ir_value_repeat1, 2, 0, 0), SHIFT_REPEAT(57),
  [395] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_escaped_ir_value_repeat1, 2, 0, 0), SHIFT_REPEAT(141),
  [398] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_escaped_ir_value_repeat1, 2, 0, 0), SHIFT_REPEAT(144),
  [401] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_escaped_ir_value_repeat1, 2, 0, 0), SHIFT_REPEAT(148),
  [404] = {.entry = {.count = 1, .reusable = true}}, SHIFT(386),
  [406] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_register_operand, 2, 0, 0),
  [408] = {.entry = {.count = 1, .reusable = true}}, SHIFT(478),
  [410] = {.entry = {.count = 1, .reusable = true}}, SHIFT(334),
  [412] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_register_operand, 1, 0, 0),
  [414] = {.entry = {.count = 1, .reusable = true}}, SHIFT(488),
  [416] = {.entry = {.count = 1, .reusable = true}}, SHIFT(561),
  [418] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_metadata, 1, 0, 0),
  [420] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_metadata, 1, 0, 0),
  [422] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [424] = {.entry = {.count = 1, .reusable = true}}, SHIFT(389),
  [426] = {.entry = {.count = 1, .reusable = true}}, SHIFT(390),
  [428] = {.entry = {.count = 1, .reusable = false}}, SHIFT(390),
  [430] = {.entry = {.count = 1, .reusable = true}}, SHIFT(165),
  [432] = {.entry = {.count = 1, .reusable = true}}, SHIFT(502),
  [434] = {.entry = {.count = 1, .reusable = true}}, SHIFT(594),
  [436] = {.entry = {.count = 1, .reusable = true}}, SHIFT(387),
  [438] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [440] = {.entry = {.count = 1, .reusable = true}}, SHIFT(88),
  [442] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [444] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [446] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [448] = {.entry = {.count = 1, .reusable = false}}, SHIFT(589),
  [450] = {.entry = {.count = 1, .reusable = false}}, SHIFT(88),
  [452] = {.entry = {.count = 1, .reusable = true}}, SHIFT(103),
  [454] = {.entry = {.count = 1, .reusable = true}}, SHIFT(96),
  [456] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__escaped_ir_content, 3, 0, 0),
  [458] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__escaped_ir_content, 3, 0, 0),
  [460] = {.entry = {.count = 1, .reusable = true}}, SHIFT(214),
  [462] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__escaped_ir_content, 2, 0, 0),
  [464] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__escaped_ir_content, 2, 0, 0),
  [466] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_registerclass, 1, 0, 0),
  [468] = {.entry = {.count = 1, .reusable = true}}, SHIFT(317),
  [470] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_register_operand, 4, 0, 0),
  [472] = {.entry = {.count = 1, .reusable = true}}, SHIFT(337),
  [474] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_register_operand, 3, 0, 0),
  [476] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [478] = {.entry = {.count = 1, .reusable = true}}, SHIFT(201),
  [480] = {.entry = {.count = 1, .reusable = true}}, SHIFT(106),
  [482] = {.entry = {.count = 1, .reusable = true}}, SHIFT(114),
  [484] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_subregister, 1, 0, 0),
  [486] = {.entry = {.count = 1, .reusable = false}}, SHIFT(446),
  [488] = {.entry = {.count = 1, .reusable = false}}, SHIFT(402),
  [490] = {.entry = {.count = 1, .reusable = true}}, SHIFT(219),
  [492] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_md_value, 1, 0, 0),
  [494] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_md_value, 1, 0, 0),
  [496] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_metadata, 3, 0, 0),
  [498] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_metadata, 3, 0, 0),
  [500] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_md_value, 2, 0, 0),
  [502] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_md_value, 2, 0, 0),
  [504] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_metadata, 4, 0, 0),
  [506] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_metadata, 4, 0, 0),
  [508] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_md_value, 3, 0, 0),
  [510] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_md_value, 3, 0, 0),
  [512] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [514] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [516] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [518] = {.entry = {.count = 1, .reusable = true}}, SHIFT(109),
  [520] = {.entry = {.count = 1, .reusable = true}}, SHIFT(86),
  [522] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [524] = {.entry = {.count = 1, .reusable = true}}, SHIFT(90),
  [526] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_register_operand, 7, 0, 0),
  [528] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_register_operand_repeat1, 2, 0, 0),
  [530] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_register_operand_repeat1, 2, 0, 0), SHIFT_REPEAT(201),
  [533] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_register_operand_repeat1, 2, 0, 0), SHIFT_REPEAT(201),
  [536] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_cfi_operand_repeat1, 2, 0, 0), SHIFT_REPEAT(567),
  [539] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_cfi_operand_repeat1, 2, 0, 0),
  [541] = {.entry = {.count = 1, .reusable = true}}, SHIFT(342),
  [543] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_machine_operand, 1, 0, 0),
  [545] = {.entry = {.count = 1, .reusable = true}}, SHIFT(546),
  [547] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_register_operand, 8, 0, 0),
  [549] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_register_operand, 5, 0, 0),
  [551] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_machine_operand, 2, 0, 0),
  [553] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_cfi_operand, 3, 0, 0), SHIFT(567),
  [556] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cfi_operand, 3, 0, 0),
  [558] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_register, 1, 0, 0),
  [560] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_register_operand, 6, 0, 0),
  [562] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_cfi_operand, 2, 0, 0), SHIFT(567),
  [565] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cfi_operand, 2, 0, 0),
  [567] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [569] = {.entry = {.count = 1, .reusable = true}}, SHIFT(494),
  [571] = {.entry = {.count = 1, .reusable = true}}, SHIFT(492),
  [573] = {.entry = {.count = 1, .reusable = true}}, SHIFT(555),
  [575] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [577] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_target_index, 4, 0, 0),
  [579] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_liveout, 4, 0, 0),
  [581] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [583] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_shuffle_mask, 4, 0, 0),
  [585] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [587] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_predicate, 4, 0, 0),
  [589] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [591] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 4, 0, 3),
  [593] = {.entry = {.count = 1, .reusable = true}}, SHIFT(282),
  [595] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [597] = {.entry = {.count = 1, .reusable = true}}, SHIFT(216),
  [599] = {.entry = {.count = 1, .reusable = true}}, SHIFT(94),
  [601] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [603] = {.entry = {.count = 1, .reusable = false}}, SHIFT(548),
  [605] = {.entry = {.count = 1, .reusable = false}}, SHIFT(216),
  [607] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [609] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [611] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cfi_operand, 1, 0, 0),
  [613] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_float, 1, 0, 0),
  [615] = {.entry = {.count = 1, .reusable = true}}, SHIFT(137),
  [617] = {.entry = {.count = 1, .reusable = true}}, SHIFT(178),
  [619] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [621] = {.entry = {.count = 1, .reusable = false}}, SHIFT(178),
  [623] = {.entry = {.count = 1, .reusable = true}}, SHIFT(141),
  [625] = {.entry = {.count = 1, .reusable = true}}, SHIFT(144),
  [627] = {.entry = {.count = 1, .reusable = true}}, SHIFT(148),
  [629] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [631] = {.entry = {.count = 1, .reusable = false}}, SHIFT(57),
  [633] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [635] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_custom_regmask, 5, 0, 0),
  [637] = {.entry = {.count = 1, .reusable = true}}, SHIFT(166),
  [639] = {.entry = {.count = 1, .reusable = false}}, SHIFT(166),
  [641] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cfi_operand, 4, 0, 0),
  [643] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_shuffle_mask, 5, 0, 0),
  [645] = {.entry = {.count = 1, .reusable = true}}, SHIFT(154),
  [647] = {.entry = {.count = 1, .reusable = false}}, SHIFT(154),
  [649] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_custom_regmask, 4, 0, 0),
  [651] = {.entry = {.count = 1, .reusable = true}}, SHIFT(138),
  [653] = {.entry = {.count = 1, .reusable = false}}, SHIFT(138),
  [655] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_address, 6, 0, 0),
  [657] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cfi_operand, 6, 0, 0),
  [659] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_mc_symbol, 4, 0, 0),
  [661] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_immediate, 2, 0, 0),
  [663] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_liveout, 5, 0, 0),
  [665] = {.entry = {.count = 1, .reusable = true}}, SHIFT(332),
  [667] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [669] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 2, 0, 1),
  [671] = {.entry = {.count = 1, .reusable = true}}, SHIFT(351),
  [673] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [675] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_intrinsic, 4, 0, 0),
  [677] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [679] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 3, 0, 2),
  [681] = {.entry = {.count = 1, .reusable = true}}, SHIFT(318),
  [683] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_liveout, 3, 0, 0),
  [685] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [687] = {.entry = {.count = 1, .reusable = true}}, SHIFT(155),
  [689] = {.entry = {.count = 1, .reusable = false}}, SHIFT(155),
  [691] = {.entry = {.count = 1, .reusable = true}}, SHIFT(353),
  [693] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [695] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 5, 0, 4),
  [697] = {.entry = {.count = 1, .reusable = true}}, SHIFT(363),
  [699] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_custom_regmask, 3, 0, 0),
  [701] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [703] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 6, 0, 5),
  [705] = {.entry = {.count = 1, .reusable = true}}, SHIFT(368),
  [707] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [709] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [711] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [713] = {.entry = {.count = 1, .reusable = true}}, SHIFT(235),
  [715] = {.entry = {.count = 1, .reusable = true}}, SHIFT(398),
  [717] = {.entry = {.count = 1, .reusable = true}}, SHIFT(268),
  [719] = {.entry = {.count = 1, .reusable = true}}, SHIFT(213),
  [721] = {.entry = {.count = 1, .reusable = true}}, SHIFT(528),
  [723] = {.entry = {.count = 1, .reusable = true}}, SHIFT(255),
  [725] = {.entry = {.count = 1, .reusable = true}}, SHIFT(226),
  [727] = {.entry = {.count = 1, .reusable = true}}, SHIFT(242),
  [729] = {.entry = {.count = 1, .reusable = true}}, SHIFT(240),
  [731] = {.entry = {.count = 1, .reusable = true}}, SHIFT(473),
  [733] = {.entry = {.count = 1, .reusable = true}}, SHIFT(265),
  [735] = {.entry = {.count = 1, .reusable = true}}, SHIFT(217),
  [737] = {.entry = {.count = 1, .reusable = true}}, SHIFT(229),
  [739] = {.entry = {.count = 1, .reusable = true}}, SHIFT(233),
  [741] = {.entry = {.count = 1, .reusable = true}}, SHIFT(236),
  [743] = {.entry = {.count = 1, .reusable = true}}, SHIFT(223),
  [745] = {.entry = {.count = 1, .reusable = true}}, SHIFT(225),
  [747] = {.entry = {.count = 1, .reusable = true}}, SHIFT(231),
  [749] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_offset, 2, 0, 0),
  [751] = {.entry = {.count = 1, .reusable = true}}, SHIFT(245),
  [753] = {.entry = {.count = 1, .reusable = true}}, SHIFT(230),
  [755] = {.entry = {.count = 1, .reusable = true}}, SHIFT(222),
  [757] = {.entry = {.count = 1, .reusable = true}}, SHIFT(221),
  [759] = {.entry = {.count = 1, .reusable = true}}, SHIFT(227),
  [761] = {.entry = {.count = 1, .reusable = true}}, SHIFT(238),
  [763] = {.entry = {.count = 1, .reusable = true}}, SHIFT(244),
  [765] = {.entry = {.count = 1, .reusable = true}}, SHIFT(232),
  [767] = {.entry = {.count = 1, .reusable = true}}, SHIFT(241),
  [769] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_register_flag, 1, 0, 0),
  [771] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_register_flag, 1, 0, 0),
  [773] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_instruction_repeat4, 2, 0, 0), SHIFT_REPEAT(259),
  [776] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_instruction_repeat4, 2, 0, 0),
  [778] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_instruction_repeat4, 2, 0, 0), SHIFT_REPEAT(494),
  [781] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_instruction_repeat4, 2, 0, 0), SHIFT_REPEAT(492),
  [784] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_instruction_repeat4, 2, 0, 0), SHIFT_REPEAT(555),
  [787] = {.entry = {.count = 1, .reusable = true}}, SHIFT(243),
  [789] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_instruction_repeat3, 2, 0, 0), SHIFT_REPEAT(22),
  [792] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_instruction_repeat3, 2, 0, 0),
  [794] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_machine_operand, 3, 0, 0),
  [796] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_argument, 6, 0, 0),
  [798] = {.entry = {.count = 1, .reusable = true}}, SHIFT(593),
  [800] = {.entry = {.count = 1, .reusable = true}}, SHIFT(501),
  [802] = {.entry = {.count = 1, .reusable = true}}, SHIFT(591),
  [804] = {.entry = {.count = 1, .reusable = true}}, SHIFT(590),
  [806] = {.entry = {.count = 1, .reusable = true}}, SHIFT(588),
  [808] = {.entry = {.count = 1, .reusable = true}}, SHIFT(401),
  [810] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_instruction_repeat3, 3, 0, 0),
  [812] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_argument, 5, 0, 0),
  [814] = {.entry = {.count = 1, .reusable = true}}, SHIFT(404),
  [816] = {.entry = {.count = 1, .reusable = true}}, SHIFT(278),
  [818] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_argument, 1, 0, 0),
  [820] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_instruction_repeat4, 3, 0, 0),
  [822] = {.entry = {.count = 1, .reusable = true}}, SHIFT(491),
  [824] = {.entry = {.count = 1, .reusable = true}}, SHIFT(484),
  [826] = {.entry = {.count = 1, .reusable = true}}, SHIFT(544),
  [828] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 6, 0, 1),
  [830] = {.entry = {.count = 1, .reusable = true}}, SHIFT(384),
  [832] = {.entry = {.count = 1, .reusable = true}}, SHIFT(565),
  [834] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 9, 0, 4),
  [836] = {.entry = {.count = 1, .reusable = true}}, SHIFT(302),
  [838] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 10, 0, 5),
  [840] = {.entry = {.count = 1, .reusable = true}}, SHIFT(291),
  [842] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 7, 0, 2),
  [844] = {.entry = {.count = 1, .reusable = true}}, SHIFT(338),
  [846] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 8, 0, 3),
  [848] = {.entry = {.count = 1, .reusable = true}}, SHIFT(329),
  [850] = {.entry = {.count = 1, .reusable = true}}, SHIFT(458),
  [852] = {.entry = {.count = 1, .reusable = true}}, SHIFT(280),
  [854] = {.entry = {.count = 1, .reusable = true}}, SHIFT(418),
  [856] = {.entry = {.count = 1, .reusable = true}}, SHIFT(274),
  [858] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_memory_operand_repeat1, 2, 0, 0), SHIFT_REPEAT(260),
  [861] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_memory_operand_repeat1, 2, 0, 0),
  [863] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_atomic_ordering, 1, 0, 0),
  [865] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sync_scope, 4, 0, 0),
  [867] = {.entry = {.count = 1, .reusable = true}}, SHIFT(260),
  [869] = {.entry = {.count = 1, .reusable = true}}, SHIFT(184),
  [871] = {.entry = {.count = 1, .reusable = true}}, SHIFT(180),
  [873] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory_operand_flag, 1, 0, 0),
  [875] = {.entry = {.count = 1, .reusable = true}}, SHIFT(281),
  [877] = {.entry = {.count = 1, .reusable = true}}, SHIFT(449),
  [879] = {.entry = {.count = 1, .reusable = true}}, SHIFT(447),
  [881] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [883] = {.entry = {.count = 1, .reusable = true}}, SHIFT(439),
  [885] = {.entry = {.count = 1, .reusable = true}}, SHIFT(395),
  [887] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [889] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [891] = {.entry = {.count = 1, .reusable = true}}, SHIFT(432),
  [893] = {.entry = {.count = 1, .reusable = true}}, SHIFT(399),
  [895] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [897] = {.entry = {.count = 1, .reusable = true}}, SHIFT(466),
  [899] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [901] = {.entry = {.count = 1, .reusable = true}}, SHIFT(425),
  [903] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_body, 1, 0, 0),
  [905] = {.entry = {.count = 1, .reusable = true}}, SHIFT(275),
  [907] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_body_repeat1, 2, 0, 0),
  [909] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_body_repeat1, 2, 0, 0), SHIFT_REPEAT(273),
  [912] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_body_repeat1, 2, 0, 0), SHIFT_REPEAT(480),
  [915] = {.entry = {.count = 1, .reusable = true}}, SHIFT(394),
  [917] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [919] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_body, 2, 0, 0),
  [921] = {.entry = {.count = 1, .reusable = true}}, SHIFT(273),
  [923] = {.entry = {.count = 1, .reusable = true}}, SHIFT(443),
  [925] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [927] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [929] = {.entry = {.count = 1, .reusable = true}}, SHIFT(477),
  [931] = {.entry = {.count = 1, .reusable = true}}, SHIFT(520),
  [933] = {.entry = {.count = 1, .reusable = true}}, SHIFT(257),
  [935] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_machine_pointer_info, 1, 0, 0),
  [937] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_instruction_repeat5, 2, 0, 0), SHIFT_REPEAT(496),
  [940] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_instruction_repeat5, 2, 0, 0),
  [942] = {.entry = {.count = 1, .reusable = true}}, SHIFT(446),
  [944] = {.entry = {.count = 1, .reusable = true}}, SHIFT(496),
  [946] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 13, 0, 5),
  [948] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 12, 0, 5),
  [950] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 12, 0, 4),
  [952] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 11, 0, 5),
  [954] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 11, 0, 4),
  [956] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 11, 0, 3),
  [958] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 10, 0, 2),
  [960] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 10, 0, 4),
  [962] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 10, 0, 3),
  [964] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 9, 0, 2),
  [966] = {.entry = {.count = 1, .reusable = true}}, SHIFT(495),
  [968] = {.entry = {.count = 1, .reusable = true}}, SHIFT(575),
  [970] = {.entry = {.count = 1, .reusable = true}}, SHIFT(572),
  [972] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 9, 0, 3),
  [974] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_escaped_ir_value, 3, 0, 0),
  [976] = {.entry = {.count = 1, .reusable = false}}, SHIFT(136),
  [978] = {.entry = {.count = 1, .reusable = true}}, SHIFT(136),
  [980] = {.entry = {.count = 1, .reusable = true}}, SHIFT(570),
  [982] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 9, 0, 1),
  [984] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_liveins, 2, 0, 0),
  [986] = {.entry = {.count = 1, .reusable = true}}, SHIFT(411),
  [988] = {.entry = {.count = 1, .reusable = true}}, SHIFT(557),
  [990] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 8, 0, 2),
  [992] = {.entry = {.count = 1, .reusable = true}}, SHIFT(402),
  [994] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory_pseudo_source_value, 2, 0, 0),
  [996] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_escaped_ir_value, 2, 0, 0),
  [998] = {.entry = {.count = 1, .reusable = true}}, SHIFT(172),
  [1000] = {.entry = {.count = 1, .reusable = true}}, SHIFT(120),
  [1002] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 8, 0, 1),
  [1004] = {.entry = {.count = 1, .reusable = true}}, SHIFT(162),
  [1006] = {.entry = {.count = 1, .reusable = true}}, SHIFT(523),
  [1008] = {.entry = {.count = 1, .reusable = true}}, SHIFT(522),
  [1010] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_successors, 3, 0, 0),
  [1012] = {.entry = {.count = 1, .reusable = true}}, SHIFT(408),
  [1014] = {.entry = {.count = 1, .reusable = true}}, SHIFT(506),
  [1016] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_liveins, 3, 0, 0),
  [1018] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_instruction, 7, 0, 1),
  [1020] = {.entry = {.count = 1, .reusable = true}}, SHIFT(517),
  [1022] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory_pseudo_source_value_keyword, 1, 0, 0),
  [1024] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory_pseudo_source_value, 1, 0, 0),
  [1026] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ir_value, 1, 0, 0),
  [1028] = {.entry = {.count = 1, .reusable = true}}, SHIFT(440),
  [1030] = {.entry = {.count = 1, .reusable = true}}, SHIFT(126),
  [1032] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_liveins, 6, 0, 0),
  [1034] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory_operand, 8, 0, 0),
  [1036] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory_operand, 4, 0, 0),
  [1038] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_liveins, 4, 0, 0),
  [1040] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory_operand, 5, 0, 0),
  [1042] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_memory_operand_repeat2, 2, 0, 0), SHIFT_REPEAT(281),
  [1045] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_memory_operand_repeat2, 2, 0, 0),
  [1047] = {.entry = {.count = 1, .reusable = true}}, SHIFT(498),
  [1049] = {.entry = {.count = 1, .reusable = false}}, SHIFT(74),
  [1051] = {.entry = {.count = 1, .reusable = true}}, SHIFT(246),
  [1053] = {.entry = {.count = 1, .reusable = true}}, SHIFT(576),
  [1055] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_instruction_repeat1, 2, 0, 0), SHIFT_REPEAT(80),
  [1058] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_instruction_repeat1, 2, 0, 0),
  [1060] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [1062] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [1064] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [1066] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [1068] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_successors, 4, 0, 0),
  [1070] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_successors, 7, 0, 0),
  [1072] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attribute, 2, 0, 0),
  [1074] = {.entry = {.count = 1, .reusable = true}}, SHIFT(489),
  [1076] = {.entry = {.count = 1, .reusable = true}}, SHIFT(471),
  [1078] = {.entry = {.count = 1, .reusable = true}}, SHIFT(270),
  [1080] = {.entry = {.count = 1, .reusable = true}}, SHIFT(534),
  [1082] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory_operand, 15, 0, 0),
  [1084] = {.entry = {.count = 1, .reusable = true}}, SHIFT(417),
  [1086] = {.entry = {.count = 1, .reusable = true}}, SHIFT(531),
  [1088] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [1090] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory_operand, 14, 0, 0),
  [1092] = {.entry = {.count = 1, .reusable = true}}, SHIFT(145),
  [1094] = {.entry = {.count = 1, .reusable = true}}, SHIFT(421),
  [1096] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory_operand, 13, 0, 0),
  [1098] = {.entry = {.count = 1, .reusable = true}}, SHIFT(152),
  [1100] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_basic_block_repeat1, 2, 0, 0), SHIFT_REPEAT(246),
  [1103] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_basic_block_repeat1, 2, 0, 0),
  [1105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory_operand, 12, 0, 0),
  [1107] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_float_keyword, 1, 0, 0),
  [1109] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_float_keyword, 1, 0, 0),
  [1111] = {.entry = {.count = 1, .reusable = true}}, SHIFT(485),
  [1113] = {.entry = {.count = 1, .reusable = true}}, SHIFT(128),
  [1115] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory_operand, 11, 0, 0),
  [1117] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory_operand, 6, 0, 0),
  [1119] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory_operand, 10, 0, 0),
  [1121] = {.entry = {.count = 1, .reusable = true}}, SHIFT(547),
  [1123] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_successors_repeat1, 2, 0, 0),
  [1125] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory_operand, 7, 0, 0),
  [1127] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_successors_repeat1, 2, 0, 0), SHIFT_REPEAT(522),
  [1130] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_liveins_repeat1, 2, 0, 0),
  [1132] = {.entry = {.count = 1, .reusable = true}}, SHIFT(549),
  [1134] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_liveins, 5, 0, 0),
  [1136] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_liveins_repeat1, 2, 0, 0), SHIFT_REPEAT(408),
  [1139] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_successors, 6, 0, 0),
  [1141] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_argument_repeat1, 2, 0, 0), SHIFT_REPEAT(531),
  [1144] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_argument_repeat1, 2, 0, 0),
  [1146] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [1148] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_memory_operand, 9, 0, 0),
  [1150] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_custom_regmask_repeat1, 2, 0, 0), SHIFT_REPEAT(440),
  [1153] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_custom_regmask_repeat1, 2, 0, 0),
  [1155] = {.entry = {.count = 1, .reusable = true}}, SHIFT(143),
  [1157] = {.entry = {.count = 1, .reusable = true}}, SHIFT(139),
  [1159] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_shuffle_mask_repeat1, 2, 0, 0), SHIFT_REPEAT(485),
  [1162] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_shuffle_mask_repeat1, 2, 0, 0),
  [1164] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [1166] = {.entry = {.count = 1, .reusable = true}}, SHIFT(153),
  [1168] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [1170] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_label, 1, 0, 0),
  [1172] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_successors_repeat1, 5, 0, 0),
  [1174] = {.entry = {.count = 1, .reusable = true}}, SHIFT(481),
  [1176] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_successors, 2, 0, 0),
  [1178] = {.entry = {.count = 1, .reusable = true}}, SHIFT(373),
  [1180] = {.entry = {.count = 1, .reusable = true}}, SHIFT(574),
  [1182] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attribute, 3, 0, 0),
  [1184] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_mem_attribute, 2, 0, 0),
  [1186] = {.entry = {.count = 1, .reusable = true}}, SHIFT(438),
  [1188] = {.entry = {.count = 1, .reusable = true}}, SHIFT(535),
  [1190] = {.entry = {.count = 1, .reusable = true}}, SHIFT(533),
  [1192] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_liveins_repeat1, 4, 0, 0),
  [1194] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attribute, 1, 0, 0),
  [1196] = {.entry = {.count = 1, .reusable = true}}, SHIFT(352),
  [1198] = {.entry = {.count = 1, .reusable = true}}, SHIFT(210),
  [1200] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [1202] = {.entry = {.count = 1, .reusable = true}}, SHIFT(125),
  [1204] = {.entry = {.count = 1, .reusable = true}}, SHIFT(453),
  [1206] = {.entry = {.count = 1, .reusable = true}}, SHIFT(526),
  [1208] = {.entry = {.count = 1, .reusable = true}}, SHIFT(568),
  [1210] = {.entry = {.count = 1, .reusable = true}}, SHIFT(366),
  [1212] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_low_level_type, 7, 0, 0),
  [1214] = {.entry = {.count = 1, .reusable = true}}, SHIFT(587),
  [1216] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bundle, 3, 0, 0),
  [1218] = {.entry = {.count = 1, .reusable = true}}, SHIFT(493),
  [1220] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [1222] = {.entry = {.count = 1, .reusable = true}}, SHIFT(228),
  [1224] = {.entry = {.count = 1, .reusable = true}}, SHIFT(556),
  [1226] = {.entry = {.count = 1, .reusable = true}}, SHIFT(566),
  [1228] = {.entry = {.count = 1, .reusable = true}}, SHIFT(490),
  [1230] = {.entry = {.count = 1, .reusable = true}}, SHIFT(122),
  [1232] = {.entry = {.count = 1, .reusable = true}}, SHIFT(448),
  [1234] = {.entry = {.count = 1, .reusable = true}}, SHIFT(554),
  [1236] = {.entry = {.count = 1, .reusable = true}}, SHIFT(163),
  [1238] = {.entry = {.count = 1, .reusable = true}}, SHIFT(263),
  [1240] = {.entry = {.count = 1, .reusable = true}}, SHIFT(551),
  [1242] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [1244] = {.entry = {.count = 1, .reusable = true}}, SHIFT(511),
  [1246] = {.entry = {.count = 1, .reusable = true}}, SHIFT(116),
  [1248] = {.entry = {.count = 1, .reusable = true}}, SHIFT(536),
  [1250] = {.entry = {.count = 1, .reusable = true}}, SHIFT(500),
  [1252] = {.entry = {.count = 1, .reusable = true}}, SHIFT(150),
  [1254] = {.entry = {.count = 1, .reusable = true}}, SHIFT(564),
  [1256] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [1258] = {.entry = {.count = 1, .reusable = true}}, SHIFT(585),
  [1260] = {.entry = {.count = 1, .reusable = true}}, SHIFT(149),
  [1262] = {.entry = {.count = 1, .reusable = true}}, SHIFT(581),
  [1264] = {.entry = {.count = 1, .reusable = true}}, SHIFT(580),
  [1266] = {.entry = {.count = 1, .reusable = true}}, SHIFT(108),
  [1268] = {.entry = {.count = 1, .reusable = true}}, SHIFT(510),
  [1270] = {.entry = {.count = 1, .reusable = true}}, SHIFT(355),
  [1272] = {.entry = {.count = 1, .reusable = true}}, SHIFT(550),
  [1274] = {.entry = {.count = 1, .reusable = true}}, SHIFT(266),
  [1276] = {.entry = {.count = 1, .reusable = true}}, SHIFT(218),
  [1278] = {.entry = {.count = 1, .reusable = true}}, SHIFT(191),
  [1280] = {.entry = {.count = 1, .reusable = true}}, SHIFT(578),
  [1282] = {.entry = {.count = 1, .reusable = true}}, SHIFT(497),
  [1284] = {.entry = {.count = 1, .reusable = true}}, SHIFT(420),
  [1286] = {.entry = {.count = 1, .reusable = true}}, SHIFT(530),
  [1288] = {.entry = {.count = 1, .reusable = true}}, SHIFT(571),
  [1290] = {.entry = {.count = 1, .reusable = true}}, SHIFT(487),
  [1292] = {.entry = {.count = 1, .reusable = true}}, SHIFT(456),
  [1294] = {.entry = {.count = 1, .reusable = true}}, SHIFT(206),
  [1296] = {.entry = {.count = 1, .reusable = true}}, SHIFT(121),
  [1298] = {.entry = {.count = 1, .reusable = true}}, SHIFT(539),
  [1300] = {.entry = {.count = 1, .reusable = true}}, SHIFT(532),
  [1302] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [1304] = {.entry = {.count = 1, .reusable = true}}, SHIFT(569),
  [1306] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_floatpred, 1, 0, 0),
  [1308] = {.entry = {.count = 1, .reusable = true}}, SHIFT(131),
  [1310] = {.entry = {.count = 1, .reusable = true}}, SHIFT(429),
  [1312] = {.entry = {.count = 1, .reusable = true}}, SHIFT(538),
  [1314] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_intpred, 1, 0, 0),
  [1316] = {.entry = {.count = 1, .reusable = true}}, SHIFT(505),
  [1318] = {.entry = {.count = 1, .reusable = true}}, SHIFT(140),
  [1320] = {.entry = {.count = 1, .reusable = true}}, SHIFT(577),
  [1322] = {.entry = {.count = 1, .reusable = true}}, SHIFT(558),
  [1324] = {.entry = {.count = 1, .reusable = true}}, SHIFT(529),
  [1326] = {.entry = {.count = 1, .reusable = true}}, SHIFT(142),
  [1328] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_low_level_type, 1, 0, 0),
  [1330] = {.entry = {.count = 1, .reusable = true}}, SHIFT(119),
  [1332] = {.entry = {.count = 1, .reusable = true}}, SHIFT(151),
  [1334] = {.entry = {.count = 1, .reusable = true}}, SHIFT(559),
  [1336] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [1338] = {.entry = {.count = 1, .reusable = true}}, SHIFT(158),
  [1340] = {.entry = {.count = 1, .reusable = true}}, SHIFT(482),
  [1342] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bundle, 2, 0, 0),
  [1344] = {.entry = {.count = 1, .reusable = true}}, SHIFT(540),
  [1346] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_low_level_type, 5, 0, 0),
  [1348] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [1350] = {.entry = {.count = 1, .reusable = true}}, SHIFT(336),
  [1352] = {.entry = {.count = 1, .reusable = true}}, SHIFT(486),
  [1354] = {.entry = {.count = 1, .reusable = true}}, SHIFT(537),
  [1356] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [1358] = {.entry = {.count = 1, .reusable = true}}, SHIFT(256),
  [1360] = {.entry = {.count = 1, .reusable = true}}, SHIFT(414),
  [1362] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [1364] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
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

TS_PUBLIC const TSLanguage *tree_sitter_llvm_mir(void) {
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
