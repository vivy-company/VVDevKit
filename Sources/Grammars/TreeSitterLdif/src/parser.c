#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 106
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 67
#define ALIAS_COUNT 0
#define TOKEN_COUNT 35
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 7
#define PRODUCTION_ID_COUNT 1

enum {
  anon_sym_dn_COLON = 1,
  aux_sym_dn_spec_token1 = 2,
  aux_sym_dn_spec_token2 = 3,
  anon_sym_COMMA = 4,
  anon_sym_PLUS = 5,
  anon_sym_EQ = 6,
  anon_sym_POUND = 7,
  anon_sym_DQUOTE = 8,
  anon_sym_BSLASH = 9,
  sym__hexpair = 10,
  sym__stringchar = 11,
  sym__special = 12,
  anon_sym_changetype_COLON = 13,
  anon_sym_add = 14,
  anon_sym_delete = 15,
  anon_sym_modrdn = 16,
  anon_sym_moddn = 17,
  anon_sym_newrdn_COLON = 18,
  anon_sym_modify = 19,
  anon_sym_add_COLON = 20,
  anon_sym_delete_COLON = 21,
  anon_sym_replace_COLON = 22,
  anon_sym_DASH = 23,
  anon_sym_COLON = 24,
  aux_sym_value_spec_token1 = 25,
  anon_sym_LT = 26,
  aux_sym_attributeType_token1 = 27,
  aux_sym_ldap_oid_token1 = 28,
  anon_sym_DOT = 29,
  anon_sym_SEMI = 30,
  aux_sym_option_token1 = 31,
  sym_url = 32,
  sym_identifier = 33,
  sym_comment = 34,
  sym_source_file = 35,
  sym__definition = 36,
  sym_ldif_change_record = 37,
  sym_dn_spec = 38,
  sym_distinguishedName = 39,
  sym_name = 40,
  sym_name_componet = 41,
  sym_attributeTypeAndValue = 42,
  sym_string = 43,
  sym_pair = 44,
  sym_changerecord = 45,
  sym_change_add = 46,
  sym_change_delete = 47,
  sym_change_moddn = 48,
  sym_change_modify = 49,
  sym_mod_spec = 50,
  sym_attrval_spec = 51,
  sym_value_spec = 52,
  sym_attributeType = 53,
  sym_ldap_oid = 54,
  sym_options = 55,
  sym_option = 56,
  sym__keychar = 57,
  sym_AttributeDescription = 58,
  sym_base64_string = 59,
  aux_sym_source_file_repeat1 = 60,
  aux_sym_name_repeat1 = 61,
  aux_sym_name_componet_repeat1 = 62,
  aux_sym_string_repeat1 = 63,
  aux_sym_change_modify_repeat1 = 64,
  aux_sym_attributeType_repeat1 = 65,
  aux_sym_option_repeat1 = 66,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_dn_COLON] = "dn:",
  [aux_sym_dn_spec_token1] = "dn_spec_token1",
  [aux_sym_dn_spec_token2] = "dn_spec_token2",
  [anon_sym_COMMA] = ",",
  [anon_sym_PLUS] = "+",
  [anon_sym_EQ] = "=",
  [anon_sym_POUND] = "#",
  [anon_sym_DQUOTE] = "\"",
  [anon_sym_BSLASH] = "\\",
  [sym__hexpair] = "_hexpair",
  [sym__stringchar] = "_stringchar",
  [sym__special] = "_special",
  [anon_sym_changetype_COLON] = "changetype:",
  [anon_sym_add] = "add",
  [anon_sym_delete] = "delete",
  [anon_sym_modrdn] = "modrdn",
  [anon_sym_moddn] = "moddn",
  [anon_sym_newrdn_COLON] = "newrdn:",
  [anon_sym_modify] = "modify",
  [anon_sym_add_COLON] = "add:",
  [anon_sym_delete_COLON] = "delete:",
  [anon_sym_replace_COLON] = "replace:",
  [anon_sym_DASH] = "-",
  [anon_sym_COLON] = ":",
  [aux_sym_value_spec_token1] = "value_spec_token1",
  [anon_sym_LT] = "<",
  [aux_sym_attributeType_token1] = "attributeType_token1",
  [aux_sym_ldap_oid_token1] = "ldap_oid_token1",
  [anon_sym_DOT] = ".",
  [anon_sym_SEMI] = ";",
  [aux_sym_option_token1] = "option_token1",
  [sym_url] = "url",
  [sym_identifier] = "identifier",
  [sym_comment] = "comment",
  [sym_source_file] = "source_file",
  [sym__definition] = "_definition",
  [sym_ldif_change_record] = "ldif_change_record",
  [sym_dn_spec] = "dn_spec",
  [sym_distinguishedName] = "distinguishedName",
  [sym_name] = "name",
  [sym_name_componet] = "name_componet",
  [sym_attributeTypeAndValue] = "attributeTypeAndValue",
  [sym_string] = "string",
  [sym_pair] = "pair",
  [sym_changerecord] = "changerecord",
  [sym_change_add] = "change_add",
  [sym_change_delete] = "change_delete",
  [sym_change_moddn] = "change_moddn",
  [sym_change_modify] = "change_modify",
  [sym_mod_spec] = "mod_spec",
  [sym_attrval_spec] = "attrval_spec",
  [sym_value_spec] = "value_spec",
  [sym_attributeType] = "attributeType",
  [sym_ldap_oid] = "ldap_oid",
  [sym_options] = "options",
  [sym_option] = "option",
  [sym__keychar] = "_keychar",
  [sym_AttributeDescription] = "AttributeDescription",
  [sym_base64_string] = "base64_string",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_name_repeat1] = "name_repeat1",
  [aux_sym_name_componet_repeat1] = "name_componet_repeat1",
  [aux_sym_string_repeat1] = "string_repeat1",
  [aux_sym_change_modify_repeat1] = "change_modify_repeat1",
  [aux_sym_attributeType_repeat1] = "attributeType_repeat1",
  [aux_sym_option_repeat1] = "option_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_dn_COLON] = anon_sym_dn_COLON,
  [aux_sym_dn_spec_token1] = aux_sym_dn_spec_token1,
  [aux_sym_dn_spec_token2] = aux_sym_dn_spec_token2,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_PLUS] = anon_sym_PLUS,
  [anon_sym_EQ] = anon_sym_EQ,
  [anon_sym_POUND] = anon_sym_POUND,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [anon_sym_BSLASH] = anon_sym_BSLASH,
  [sym__hexpair] = sym__hexpair,
  [sym__stringchar] = sym__stringchar,
  [sym__special] = sym__special,
  [anon_sym_changetype_COLON] = anon_sym_changetype_COLON,
  [anon_sym_add] = anon_sym_add,
  [anon_sym_delete] = anon_sym_delete,
  [anon_sym_modrdn] = anon_sym_modrdn,
  [anon_sym_moddn] = anon_sym_moddn,
  [anon_sym_newrdn_COLON] = anon_sym_newrdn_COLON,
  [anon_sym_modify] = anon_sym_modify,
  [anon_sym_add_COLON] = anon_sym_add_COLON,
  [anon_sym_delete_COLON] = anon_sym_delete_COLON,
  [anon_sym_replace_COLON] = anon_sym_replace_COLON,
  [anon_sym_DASH] = anon_sym_DASH,
  [anon_sym_COLON] = anon_sym_COLON,
  [aux_sym_value_spec_token1] = aux_sym_value_spec_token1,
  [anon_sym_LT] = anon_sym_LT,
  [aux_sym_attributeType_token1] = aux_sym_attributeType_token1,
  [aux_sym_ldap_oid_token1] = aux_sym_ldap_oid_token1,
  [anon_sym_DOT] = anon_sym_DOT,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [aux_sym_option_token1] = aux_sym_option_token1,
  [sym_url] = sym_url,
  [sym_identifier] = sym_identifier,
  [sym_comment] = sym_comment,
  [sym_source_file] = sym_source_file,
  [sym__definition] = sym__definition,
  [sym_ldif_change_record] = sym_ldif_change_record,
  [sym_dn_spec] = sym_dn_spec,
  [sym_distinguishedName] = sym_distinguishedName,
  [sym_name] = sym_name,
  [sym_name_componet] = sym_name_componet,
  [sym_attributeTypeAndValue] = sym_attributeTypeAndValue,
  [sym_string] = sym_string,
  [sym_pair] = sym_pair,
  [sym_changerecord] = sym_changerecord,
  [sym_change_add] = sym_change_add,
  [sym_change_delete] = sym_change_delete,
  [sym_change_moddn] = sym_change_moddn,
  [sym_change_modify] = sym_change_modify,
  [sym_mod_spec] = sym_mod_spec,
  [sym_attrval_spec] = sym_attrval_spec,
  [sym_value_spec] = sym_value_spec,
  [sym_attributeType] = sym_attributeType,
  [sym_ldap_oid] = sym_ldap_oid,
  [sym_options] = sym_options,
  [sym_option] = sym_option,
  [sym__keychar] = sym__keychar,
  [sym_AttributeDescription] = sym_AttributeDescription,
  [sym_base64_string] = sym_base64_string,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_name_repeat1] = aux_sym_name_repeat1,
  [aux_sym_name_componet_repeat1] = aux_sym_name_componet_repeat1,
  [aux_sym_string_repeat1] = aux_sym_string_repeat1,
  [aux_sym_change_modify_repeat1] = aux_sym_change_modify_repeat1,
  [aux_sym_attributeType_repeat1] = aux_sym_attributeType_repeat1,
  [aux_sym_option_repeat1] = aux_sym_option_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_dn_COLON] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_dn_spec_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_dn_spec_token2] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PLUS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_POUND] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BSLASH] = {
    .visible = true,
    .named = false,
  },
  [sym__hexpair] = {
    .visible = false,
    .named = true,
  },
  [sym__stringchar] = {
    .visible = false,
    .named = true,
  },
  [sym__special] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_changetype_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_add] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_delete] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_modrdn] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_moddn] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_newrdn_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_modify] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_add_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_delete_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_replace_COLON] = {
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
  [aux_sym_value_spec_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_LT] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_attributeType_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_ldap_oid_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_DOT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SEMI] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_option_token1] = {
    .visible = false,
    .named = false,
  },
  [sym_url] = {
    .visible = true,
    .named = true,
  },
  [sym_identifier] = {
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
  [sym__definition] = {
    .visible = false,
    .named = true,
  },
  [sym_ldif_change_record] = {
    .visible = true,
    .named = true,
  },
  [sym_dn_spec] = {
    .visible = true,
    .named = true,
  },
  [sym_distinguishedName] = {
    .visible = true,
    .named = true,
  },
  [sym_name] = {
    .visible = true,
    .named = true,
  },
  [sym_name_componet] = {
    .visible = true,
    .named = true,
  },
  [sym_attributeTypeAndValue] = {
    .visible = true,
    .named = true,
  },
  [sym_string] = {
    .visible = true,
    .named = true,
  },
  [sym_pair] = {
    .visible = true,
    .named = true,
  },
  [sym_changerecord] = {
    .visible = true,
    .named = true,
  },
  [sym_change_add] = {
    .visible = true,
    .named = true,
  },
  [sym_change_delete] = {
    .visible = true,
    .named = true,
  },
  [sym_change_moddn] = {
    .visible = true,
    .named = true,
  },
  [sym_change_modify] = {
    .visible = true,
    .named = true,
  },
  [sym_mod_spec] = {
    .visible = true,
    .named = true,
  },
  [sym_attrval_spec] = {
    .visible = true,
    .named = true,
  },
  [sym_value_spec] = {
    .visible = true,
    .named = true,
  },
  [sym_attributeType] = {
    .visible = true,
    .named = true,
  },
  [sym_ldap_oid] = {
    .visible = true,
    .named = true,
  },
  [sym_options] = {
    .visible = true,
    .named = true,
  },
  [sym_option] = {
    .visible = true,
    .named = true,
  },
  [sym__keychar] = {
    .visible = false,
    .named = true,
  },
  [sym_AttributeDescription] = {
    .visible = true,
    .named = true,
  },
  [sym_base64_string] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_name_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_name_componet_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_string_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_change_modify_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_attributeType_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_option_repeat1] = {
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
  [18] = 17,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 10,
  [23] = 4,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 13,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 31,
  [36] = 34,
  [37] = 32,
  [38] = 38,
  [39] = 39,
  [40] = 40,
  [41] = 20,
  [42] = 42,
  [43] = 43,
  [44] = 33,
  [45] = 45,
  [46] = 46,
  [47] = 47,
  [48] = 48,
  [49] = 38,
  [50] = 50,
  [51] = 51,
  [52] = 47,
  [53] = 45,
  [54] = 54,
  [55] = 55,
  [56] = 50,
  [57] = 57,
  [58] = 58,
  [59] = 59,
  [60] = 60,
  [61] = 57,
  [62] = 62,
  [63] = 63,
  [64] = 51,
  [65] = 65,
  [66] = 66,
  [67] = 67,
  [68] = 68,
  [69] = 58,
  [70] = 70,
  [71] = 71,
  [72] = 71,
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
  [96] = 95,
  [97] = 97,
  [98] = 98,
  [99] = 99,
  [100] = 87,
  [101] = 101,
  [102] = 75,
  [103] = 103,
  [104] = 104,
  [105] = 90,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(61);
      if (lookahead == '"') ADVANCE(70);
      if (lookahead == '#') ADVANCE(69);
      if (lookahead == '+') ADVANCE(67);
      if (lookahead == ',') ADVANCE(66);
      if (lookahead == '-') ADVANCE(88);
      if (lookahead == '.') ADVANCE(95);
      if (lookahead == ':') ADVANCE(89);
      if (lookahead == ';') ADVANCE(96);
      if (lookahead == '<') ADVANCE(91);
      if (lookahead == '=') ADVANCE(68);
      if (lookahead == '>') ADVANCE(76);
      if (lookahead == '\\') ADVANCE(71);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(0)
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 1:
      if (lookahead == '\t') SKIP(1)
      if (lookahead == '\n') ADVANCE(64);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == ' ') ADVANCE(74);
      if (lookahead == '#') ADVANCE(109);
      if (lookahead == '+') ADVANCE(67);
      if (lookahead == ',') ADVANCE(66);
      if (lookahead == '\\') ADVANCE(71);
      if (lookahead != 0 &&
          lookahead != '"' &&
          (lookahead < ';' || '>' < lookahead)) ADVANCE(73);
      END_STATE();
    case 2:
      if (lookahead == '\n') ADVANCE(65);
      if (lookahead == '\r') ADVANCE(2);
      if (lookahead == '#') ADVANCE(109);
      if (lookahead == '+') ADVANCE(67);
      if (lookahead == ',') ADVANCE(66);
      if (lookahead == '.') ADVANCE(95);
      if (lookahead == ';') ADVANCE(96);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(2)
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(97);
      END_STATE();
    case 3:
      if (lookahead == ' ') ADVANCE(75);
      if (lookahead == '"') ADVANCE(70);
      if (lookahead == '#') ADVANCE(69);
      if (lookahead == '\\') ADVANCE(71);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r') SKIP(3)
      if (lookahead != 0 &&
          lookahead != '+' &&
          lookahead != ',' &&
          (lookahead < ';' || '>' < lookahead)) ADVANCE(73);
      END_STATE();
    case 4:
      if (lookahead == ' ') ADVANCE(75);
      if (lookahead == '"') ADVANCE(70);
      if (lookahead == '#') ADVANCE(109);
      if (lookahead == '\\') ADVANCE(71);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r') SKIP(4)
      if (lookahead != 0 &&
          lookahead != '+' &&
          lookahead != ',' &&
          (lookahead < ';' || '>' < lookahead)) ADVANCE(73);
      END_STATE();
    case 5:
      if (lookahead == '"') ADVANCE(70);
      if (lookahead == '#') ADVANCE(77);
      if (lookahead == '\\') ADVANCE(71);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(5)
      if (lookahead == '+' ||
          lookahead == ',' ||
          (';' <= lookahead && lookahead <= '>')) ADVANCE(76);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(58);
      END_STATE();
    case 6:
      if (lookahead == '#') ADVANCE(109);
      if (lookahead == ':') ADVANCE(89);
      if (lookahead == ';') ADVANCE(96);
      if (lookahead == '=') ADVANCE(68);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(6)
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(97);
      END_STATE();
    case 7:
      if (lookahead == '#') ADVANCE(109);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(7)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(93);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 8:
      if (lookahead == '#') ADVANCE(109);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(8)
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(97);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(98);
      END_STATE();
    case 9:
      if (lookahead == '#') ADVANCE(109);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(9)
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(58);
      END_STATE();
    case 10:
      if (lookahead == ':') ADVANCE(62);
      END_STATE();
    case 11:
      if (lookahead == ':') ADVANCE(83);
      END_STATE();
    case 12:
      if (lookahead == ':') ADVANCE(78);
      END_STATE();
    case 13:
      if (lookahead == ':') ADVANCE(85);
      END_STATE();
    case 14:
      if (lookahead == ':') ADVANCE(86);
      END_STATE();
    case 15:
      if (lookahead == ':') ADVANCE(87);
      END_STATE();
    case 16:
      if (lookahead == 'a') ADVANCE(44);
      END_STATE();
    case 17:
      if (lookahead == 'a') ADVANCE(18);
      END_STATE();
    case 18:
      if (lookahead == 'c') ADVANCE(35);
      END_STATE();
    case 19:
      if (lookahead == 'd') ADVANCE(79);
      END_STATE();
    case 20:
      if (lookahead == 'd') ADVANCE(22);
      END_STATE();
    case 21:
      if (lookahead == 'd') ADVANCE(19);
      END_STATE();
    case 22:
      if (lookahead == 'd') ADVANCE(45);
      if (lookahead == 'i') ADVANCE(38);
      if (lookahead == 'r') ADVANCE(23);
      END_STATE();
    case 23:
      if (lookahead == 'd') ADVANCE(46);
      END_STATE();
    case 24:
      if (lookahead == 'd') ADVANCE(13);
      END_STATE();
    case 25:
      if (lookahead == 'd') ADVANCE(47);
      END_STATE();
    case 26:
      if (lookahead == 'd') ADVANCE(24);
      END_STATE();
    case 27:
      if (lookahead == 'e') ADVANCE(41);
      if (lookahead == 'n') ADVANCE(10);
      END_STATE();
    case 28:
      if (lookahead == 'e') ADVANCE(55);
      END_STATE();
    case 29:
      if (lookahead == 'e') ADVANCE(53);
      END_STATE();
    case 30:
      if (lookahead == 'e') ADVANCE(80);
      END_STATE();
    case 31:
      if (lookahead == 'e') ADVANCE(52);
      END_STATE();
    case 32:
      if (lookahead == 'e') ADVANCE(49);
      END_STATE();
    case 33:
      if (lookahead == 'e') ADVANCE(12);
      END_STATE();
    case 34:
      if (lookahead == 'e') ADVANCE(14);
      END_STATE();
    case 35:
      if (lookahead == 'e') ADVANCE(15);
      END_STATE();
    case 36:
      if (lookahead == 'e') ADVANCE(54);
      END_STATE();
    case 37:
      if (lookahead == 'e') ADVANCE(43);
      if (lookahead == 'n') ADVANCE(10);
      END_STATE();
    case 38:
      if (lookahead == 'f') ADVANCE(56);
      END_STATE();
    case 39:
      if (lookahead == 'g') ADVANCE(31);
      END_STATE();
    case 40:
      if (lookahead == 'h') ADVANCE(16);
      END_STATE();
    case 41:
      if (lookahead == 'l') ADVANCE(29);
      END_STATE();
    case 42:
      if (lookahead == 'l') ADVANCE(17);
      END_STATE();
    case 43:
      if (lookahead == 'l') ADVANCE(36);
      END_STATE();
    case 44:
      if (lookahead == 'n') ADVANCE(39);
      END_STATE();
    case 45:
      if (lookahead == 'n') ADVANCE(82);
      END_STATE();
    case 46:
      if (lookahead == 'n') ADVANCE(81);
      END_STATE();
    case 47:
      if (lookahead == 'n') ADVANCE(11);
      END_STATE();
    case 48:
      if (lookahead == 'o') ADVANCE(20);
      END_STATE();
    case 49:
      if (lookahead == 'p') ADVANCE(42);
      END_STATE();
    case 50:
      if (lookahead == 'p') ADVANCE(33);
      END_STATE();
    case 51:
      if (lookahead == 'r') ADVANCE(25);
      END_STATE();
    case 52:
      if (lookahead == 't') ADVANCE(57);
      END_STATE();
    case 53:
      if (lookahead == 't') ADVANCE(30);
      END_STATE();
    case 54:
      if (lookahead == 't') ADVANCE(34);
      END_STATE();
    case 55:
      if (lookahead == 'w') ADVANCE(51);
      END_STATE();
    case 56:
      if (lookahead == 'y') ADVANCE(84);
      END_STATE();
    case 57:
      if (lookahead == 'y') ADVANCE(50);
      END_STATE();
    case 58:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(72);
      END_STATE();
    case 59:
      if (eof) ADVANCE(61);
      if (lookahead == '#') ADVANCE(109);
      if (lookahead == '-') ADVANCE(88);
      if (lookahead == '.') ADVANCE(95);
      if (lookahead == ':') ADVANCE(89);
      if (lookahead == ';') ADVANCE(96);
      if (lookahead == '=') ADVANCE(68);
      if (lookahead == 'a') ADVANCE(21);
      if (lookahead == 'c') ADVANCE(40);
      if (lookahead == 'd') ADVANCE(27);
      if (lookahead == 'm') ADVANCE(48);
      if (lookahead == 'n') ADVANCE(28);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(59)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(94);
      END_STATE();
    case 60:
      if (eof) ADVANCE(61);
      if (lookahead == '#') ADVANCE(109);
      if (lookahead == 'a') ADVANCE(26);
      if (lookahead == 'd') ADVANCE(37);
      if (lookahead == 'r') ADVANCE(32);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(60)
      END_STATE();
    case 61:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(anon_sym_dn_COLON);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(aux_sym_dn_spec_token1);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(63);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(aux_sym_dn_spec_token2);
      if (lookahead == '\n') ADVANCE(64);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == ' ') ADVANCE(74);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(aux_sym_dn_spec_token2);
      if (lookahead == '\n') ADVANCE(65);
      if (lookahead == '\r') ADVANCE(2);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(anon_sym_PLUS);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(anon_sym_POUND);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(109);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(anon_sym_BSLASH);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(sym__hexpair);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(sym__stringchar);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(sym__stringchar);
      if (lookahead == '\n') ADVANCE(64);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead == ' ') ADVANCE(74);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '"' &&
          lookahead != '#' &&
          lookahead != '+' &&
          lookahead != ',' &&
          (lookahead < ';' || '>' < lookahead) &&
          lookahead != '\\') ADVANCE(73);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(sym__stringchar);
      if (lookahead == ' ') ADVANCE(75);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '"' &&
          lookahead != '#' &&
          lookahead != '+' &&
          lookahead != ',' &&
          (lookahead < ';' || '>' < lookahead) &&
          lookahead != '\\') ADVANCE(73);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(sym__special);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(sym__special);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(109);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(anon_sym_changetype_COLON);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(anon_sym_add);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(anon_sym_delete);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(anon_sym_modrdn);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(anon_sym_moddn);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(anon_sym_newrdn_COLON);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(anon_sym_modify);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(anon_sym_add_COLON);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(anon_sym_delete_COLON);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(anon_sym_replace_COLON);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(aux_sym_value_spec_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(90);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(anon_sym_LT);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(aux_sym_attributeType_token1);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(aux_sym_attributeType_token1);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(94);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(aux_sym_ldap_oid_token1);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(94);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(anon_sym_DOT);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(aux_sym_option_token1);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(aux_sym_option_token1);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(108);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(sym_url);
      if (lookahead == '#') ADVANCE(107);
      if (lookahead == '/') ADVANCE(104);
      if (lookahead == ':') ADVANCE(105);
      if (lookahead == '?') ADVANCE(106);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(100);
      if (lookahead != 0) ADVANCE(102);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(sym_url);
      if (lookahead == '#') ADVANCE(107);
      if (lookahead == '/') ADVANCE(104);
      if (lookahead == ':') ADVANCE(101);
      if (lookahead == '?') ADVANCE(106);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(100);
      if (lookahead != 0) ADVANCE(102);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(sym_url);
      if (lookahead == '#') ADVANCE(107);
      if (lookahead == '/') ADVANCE(104);
      if (lookahead == '?') ADVANCE(106);
      if (lookahead != 0) ADVANCE(105);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(sym_url);
      if (lookahead == '#') ADVANCE(107);
      if (lookahead == '/') ADVANCE(105);
      if (lookahead == ':') ADVANCE(101);
      if (lookahead == '?') ADVANCE(106);
      if (lookahead != 0) ADVANCE(102);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(sym_url);
      if (lookahead == '#') ADVANCE(107);
      if (lookahead == '/') ADVANCE(105);
      if (lookahead == '?') ADVANCE(106);
      if (lookahead != 0) ADVANCE(103);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(sym_url);
      if (lookahead == '#') ADVANCE(107);
      if (lookahead == '/') ADVANCE(103);
      if (lookahead == '?') ADVANCE(106);
      if (lookahead != 0) ADVANCE(105);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(sym_url);
      if (lookahead == '#') ADVANCE(107);
      if (lookahead == '?') ADVANCE(106);
      if (lookahead != 0) ADVANCE(105);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(sym_url);
      if (lookahead == '#') ADVANCE(107);
      if (lookahead != 0) ADVANCE(106);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(sym_url);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(107);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(108);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(109);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 59},
  [2] = {.lex_state = 59},
  [3] = {.lex_state = 7},
  [4] = {.lex_state = 1},
  [5] = {.lex_state = 1},
  [6] = {.lex_state = 60},
  [7] = {.lex_state = 60},
  [8] = {.lex_state = 60},
  [9] = {.lex_state = 1},
  [10] = {.lex_state = 6},
  [11] = {.lex_state = 3},
  [12] = {.lex_state = 59},
  [13] = {.lex_state = 6},
  [14] = {.lex_state = 59},
  [15] = {.lex_state = 7},
  [16] = {.lex_state = 7},
  [17] = {.lex_state = 6},
  [18] = {.lex_state = 2},
  [19] = {.lex_state = 4},
  [20] = {.lex_state = 1},
  [21] = {.lex_state = 4},
  [22] = {.lex_state = 2},
  [23] = {.lex_state = 4},
  [24] = {.lex_state = 7},
  [25] = {.lex_state = 7},
  [26] = {.lex_state = 60},
  [27] = {.lex_state = 2},
  [28] = {.lex_state = 2},
  [29] = {.lex_state = 2},
  [30] = {.lex_state = 2},
  [31] = {.lex_state = 8},
  [32] = {.lex_state = 5},
  [33] = {.lex_state = 59},
  [34] = {.lex_state = 8},
  [35] = {.lex_state = 8},
  [36] = {.lex_state = 8},
  [37] = {.lex_state = 5},
  [38] = {.lex_state = 6},
  [39] = {.lex_state = 2},
  [40] = {.lex_state = 2},
  [41] = {.lex_state = 4},
  [42] = {.lex_state = 2},
  [43] = {.lex_state = 2},
  [44] = {.lex_state = 2},
  [45] = {.lex_state = 2},
  [46] = {.lex_state = 63},
  [47] = {.lex_state = 6},
  [48] = {.lex_state = 2},
  [49] = {.lex_state = 2},
  [50] = {.lex_state = 59},
  [51] = {.lex_state = 59},
  [52] = {.lex_state = 2},
  [53] = {.lex_state = 6},
  [54] = {.lex_state = 2},
  [55] = {.lex_state = 2},
  [56] = {.lex_state = 2},
  [57] = {.lex_state = 59},
  [58] = {.lex_state = 6},
  [59] = {.lex_state = 59},
  [60] = {.lex_state = 2},
  [61] = {.lex_state = 2},
  [62] = {.lex_state = 59},
  [63] = {.lex_state = 59},
  [64] = {.lex_state = 2},
  [65] = {.lex_state = 59},
  [66] = {.lex_state = 59},
  [67] = {.lex_state = 59},
  [68] = {.lex_state = 8},
  [69] = {.lex_state = 6},
  [70] = {.lex_state = 59},
  [71] = {.lex_state = 2},
  [72] = {.lex_state = 59},
  [73] = {.lex_state = 2},
  [74] = {.lex_state = 63},
  [75] = {.lex_state = 59},
  [76] = {.lex_state = 90},
  [77] = {.lex_state = 63},
  [78] = {.lex_state = 63},
  [79] = {.lex_state = 59},
  [80] = {.lex_state = 2},
  [81] = {.lex_state = 2},
  [82] = {.lex_state = 99},
  [83] = {.lex_state = 2},
  [84] = {.lex_state = 2},
  [85] = {.lex_state = 59},
  [86] = {.lex_state = 59},
  [87] = {.lex_state = 2},
  [88] = {.lex_state = 2},
  [89] = {.lex_state = 63},
  [90] = {.lex_state = 59},
  [91] = {.lex_state = 2},
  [92] = {.lex_state = 59},
  [93] = {.lex_state = 59},
  [94] = {.lex_state = 9},
  [95] = {.lex_state = 59},
  [96] = {.lex_state = 2},
  [97] = {.lex_state = 2},
  [98] = {.lex_state = 2},
  [99] = {.lex_state = 2},
  [100] = {.lex_state = 59},
  [101] = {.lex_state = 63},
  [102] = {.lex_state = 59},
  [103] = {.lex_state = 59},
  [104] = {.lex_state = 2},
  [105] = {.lex_state = 59},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_PLUS] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_POUND] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [anon_sym_BSLASH] = ACTIONS(1),
    [sym__special] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_LT] = ACTIONS(1),
    [aux_sym_attributeType_token1] = ACTIONS(1),
    [anon_sym_DOT] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [aux_sym_option_token1] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
  },
  [1] = {
    [sym_source_file] = STATE(92),
    [sym__definition] = STATE(12),
    [sym_ldif_change_record] = STATE(12),
    [sym_dn_spec] = STATE(63),
    [aux_sym_source_file_repeat1] = STATE(12),
    [ts_builtin_sym_end] = ACTIONS(5),
    [anon_sym_dn_COLON] = ACTIONS(7),
    [sym_comment] = ACTIONS(9),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 6,
    ACTIONS(11), 1,
      anon_sym_add,
    ACTIONS(13), 1,
      anon_sym_delete,
    ACTIONS(17), 1,
      anon_sym_modify,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(15), 2,
      anon_sym_modrdn,
      anon_sym_moddn,
    STATE(59), 4,
      sym_change_add,
      sym_change_delete,
      sym_change_moddn,
      sym_change_modify,
  [23] = 9,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(21), 1,
      aux_sym_attributeType_token1,
    ACTIONS(23), 1,
      aux_sym_ldap_oid_token1,
    STATE(30), 1,
      sym_attributeTypeAndValue,
    STATE(50), 1,
      sym_ldap_oid,
    STATE(55), 1,
      sym_name_componet,
    STATE(93), 1,
      sym_attributeType,
    STATE(97), 1,
      sym_distinguishedName,
    STATE(98), 1,
      sym_name,
  [51] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(27), 1,
      anon_sym_BSLASH,
    ACTIONS(30), 1,
      sym__stringchar,
    STATE(4), 2,
      sym_pair,
      aux_sym_string_repeat1,
    ACTIONS(25), 3,
      aux_sym_dn_spec_token2,
      anon_sym_COMMA,
      anon_sym_PLUS,
  [70] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(35), 1,
      anon_sym_BSLASH,
    ACTIONS(37), 1,
      sym__stringchar,
    STATE(9), 2,
      sym_pair,
      aux_sym_string_repeat1,
    ACTIONS(33), 3,
      aux_sym_dn_spec_token2,
      anon_sym_COMMA,
      anon_sym_PLUS,
  [89] = 3,
    STATE(6), 2,
      sym_mod_spec,
      aux_sym_change_modify_repeat1,
    ACTIONS(39), 3,
      ts_builtin_sym_end,
      anon_sym_dn_COLON,
      sym_comment,
    ACTIONS(41), 3,
      anon_sym_add_COLON,
      anon_sym_delete_COLON,
      anon_sym_replace_COLON,
  [104] = 3,
    STATE(8), 2,
      sym_mod_spec,
      aux_sym_change_modify_repeat1,
    ACTIONS(44), 3,
      ts_builtin_sym_end,
      anon_sym_dn_COLON,
      sym_comment,
    ACTIONS(46), 3,
      anon_sym_add_COLON,
      anon_sym_delete_COLON,
      anon_sym_replace_COLON,
  [119] = 3,
    STATE(6), 2,
      sym_mod_spec,
      aux_sym_change_modify_repeat1,
    ACTIONS(46), 3,
      anon_sym_add_COLON,
      anon_sym_delete_COLON,
      anon_sym_replace_COLON,
    ACTIONS(48), 3,
      ts_builtin_sym_end,
      anon_sym_dn_COLON,
      sym_comment,
  [134] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(35), 1,
      anon_sym_BSLASH,
    ACTIONS(52), 1,
      sym__stringchar,
    STATE(4), 2,
      sym_pair,
      aux_sym_string_repeat1,
    ACTIONS(50), 3,
      aux_sym_dn_spec_token2,
      anon_sym_COMMA,
      anon_sym_PLUS,
  [153] = 4,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(56), 1,
      aux_sym_option_token1,
    STATE(10), 2,
      sym__keychar,
      aux_sym_attributeType_repeat1,
    ACTIONS(54), 3,
      anon_sym_EQ,
      anon_sym_COLON,
      anon_sym_SEMI,
  [169] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(35), 1,
      anon_sym_BSLASH,
    ACTIONS(59), 1,
      anon_sym_POUND,
    ACTIONS(61), 1,
      anon_sym_DQUOTE,
    ACTIONS(63), 1,
      sym__stringchar,
    STATE(5), 1,
      sym_pair,
    STATE(43), 1,
      sym_string,
  [191] = 5,
    ACTIONS(7), 1,
      anon_sym_dn_COLON,
    ACTIONS(65), 1,
      ts_builtin_sym_end,
    ACTIONS(67), 1,
      sym_comment,
    STATE(63), 1,
      sym_dn_spec,
    STATE(14), 3,
      sym__definition,
      sym_ldif_change_record,
      aux_sym_source_file_repeat1,
  [209] = 4,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(71), 1,
      aux_sym_option_token1,
    STATE(10), 2,
      sym__keychar,
      aux_sym_attributeType_repeat1,
    ACTIONS(69), 3,
      anon_sym_EQ,
      anon_sym_COLON,
      anon_sym_SEMI,
  [225] = 5,
    ACTIONS(73), 1,
      ts_builtin_sym_end,
    ACTIONS(75), 1,
      anon_sym_dn_COLON,
    ACTIONS(78), 1,
      sym_comment,
    STATE(63), 1,
      sym_dn_spec,
    STATE(14), 3,
      sym__definition,
      sym_ldif_change_record,
      aux_sym_source_file_repeat1,
  [243] = 7,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(21), 1,
      aux_sym_attributeType_token1,
    ACTIONS(23), 1,
      aux_sym_ldap_oid_token1,
    STATE(50), 1,
      sym_ldap_oid,
    STATE(57), 1,
      sym_attributeType,
    STATE(67), 1,
      sym_AttributeDescription,
    STATE(85), 1,
      sym_attrval_spec,
  [265] = 7,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(21), 1,
      aux_sym_attributeType_token1,
    ACTIONS(23), 1,
      aux_sym_ldap_oid_token1,
    STATE(30), 1,
      sym_attributeTypeAndValue,
    STATE(50), 1,
      sym_ldap_oid,
    STATE(60), 1,
      sym_name_componet,
    STATE(93), 1,
      sym_attributeType,
  [287] = 4,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(83), 1,
      aux_sym_option_token1,
    STATE(13), 2,
      sym__keychar,
      aux_sym_attributeType_repeat1,
    ACTIONS(81), 3,
      anon_sym_EQ,
      anon_sym_COLON,
      anon_sym_SEMI,
  [303] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(81), 1,
      aux_sym_dn_spec_token2,
    ACTIONS(85), 1,
      anon_sym_SEMI,
    ACTIONS(87), 1,
      aux_sym_option_token1,
    STATE(27), 2,
      sym__keychar,
      aux_sym_attributeType_repeat1,
  [320] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(91), 1,
      anon_sym_BSLASH,
    ACTIONS(93), 1,
      sym__stringchar,
    STATE(23), 2,
      sym_pair,
      aux_sym_string_repeat1,
  [337] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(95), 5,
      aux_sym_dn_spec_token2,
      anon_sym_COMMA,
      anon_sym_PLUS,
      anon_sym_BSLASH,
      sym__stringchar,
  [348] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(91), 1,
      anon_sym_BSLASH,
    ACTIONS(97), 1,
      anon_sym_DQUOTE,
    ACTIONS(99), 1,
      sym__stringchar,
    STATE(19), 2,
      sym_pair,
      aux_sym_string_repeat1,
  [365] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(54), 1,
      aux_sym_dn_spec_token2,
    ACTIONS(101), 1,
      anon_sym_SEMI,
    ACTIONS(103), 1,
      aux_sym_option_token1,
    STATE(22), 2,
      sym__keychar,
      aux_sym_attributeType_repeat1,
  [382] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(25), 1,
      anon_sym_DQUOTE,
    ACTIONS(106), 1,
      anon_sym_BSLASH,
    ACTIONS(109), 1,
      sym__stringchar,
    STATE(23), 2,
      sym_pair,
      aux_sym_string_repeat1,
  [399] = 6,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(21), 1,
      aux_sym_attributeType_token1,
    ACTIONS(23), 1,
      aux_sym_ldap_oid_token1,
    STATE(40), 1,
      sym_attributeTypeAndValue,
    STATE(50), 1,
      sym_ldap_oid,
    STATE(93), 1,
      sym_attributeType,
  [418] = 6,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(112), 1,
      aux_sym_attributeType_token1,
    ACTIONS(114), 1,
      aux_sym_ldap_oid_token1,
    STATE(56), 1,
      sym_ldap_oid,
    STATE(61), 1,
      sym_attributeType,
    STATE(91), 1,
      sym_AttributeDescription,
  [437] = 1,
    ACTIONS(116), 6,
      ts_builtin_sym_end,
      anon_sym_dn_COLON,
      anon_sym_add_COLON,
      anon_sym_delete_COLON,
      anon_sym_replace_COLON,
      sym_comment,
  [446] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(69), 1,
      aux_sym_dn_spec_token2,
    ACTIONS(118), 1,
      anon_sym_SEMI,
    ACTIONS(120), 1,
      aux_sym_option_token1,
    STATE(22), 2,
      sym__keychar,
      aux_sym_attributeType_repeat1,
  [463] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(122), 1,
      aux_sym_dn_spec_token2,
    ACTIONS(124), 1,
      anon_sym_COMMA,
    ACTIONS(126), 1,
      anon_sym_PLUS,
    STATE(29), 1,
      aux_sym_name_componet_repeat1,
  [479] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(128), 1,
      aux_sym_dn_spec_token2,
    ACTIONS(130), 1,
      anon_sym_COMMA,
    ACTIONS(132), 1,
      anon_sym_PLUS,
    STATE(29), 1,
      aux_sym_name_componet_repeat1,
  [495] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(126), 1,
      anon_sym_PLUS,
    ACTIONS(135), 1,
      aux_sym_dn_spec_token2,
    ACTIONS(137), 1,
      anon_sym_COMMA,
    STATE(28), 1,
      aux_sym_name_componet_repeat1,
  [511] = 5,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(139), 1,
      aux_sym_option_token1,
    ACTIONS(141), 1,
      sym_identifier,
    STATE(72), 1,
      sym_option,
    STATE(95), 1,
      sym_options,
  [527] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(145), 1,
      sym__special,
    ACTIONS(143), 3,
      anon_sym_DQUOTE,
      anon_sym_BSLASH,
      sym__hexpair,
  [539] = 3,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(149), 1,
      anon_sym_DOT,
    ACTIONS(147), 3,
      anon_sym_EQ,
      anon_sym_COLON,
      anon_sym_SEMI,
  [551] = 5,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(139), 1,
      aux_sym_option_token1,
    ACTIONS(141), 1,
      sym_identifier,
    STATE(72), 1,
      sym_option,
    STATE(100), 1,
      sym_options,
  [567] = 5,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(151), 1,
      aux_sym_option_token1,
    ACTIONS(153), 1,
      sym_identifier,
    STATE(71), 1,
      sym_option,
    STATE(96), 1,
      sym_options,
  [583] = 5,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(151), 1,
      aux_sym_option_token1,
    ACTIONS(153), 1,
      sym_identifier,
    STATE(71), 1,
      sym_option,
    STATE(87), 1,
      sym_options,
  [599] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(157), 1,
      sym__special,
    ACTIONS(155), 3,
      anon_sym_DQUOTE,
      anon_sym_BSLASH,
      sym__hexpair,
  [611] = 4,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(159), 1,
      anon_sym_COLON,
    ACTIONS(161), 1,
      aux_sym_option_token1,
    STATE(53), 1,
      aux_sym_option_repeat1,
  [624] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(163), 1,
      aux_sym_dn_spec_token2,
    ACTIONS(165), 1,
      anon_sym_COMMA,
    STATE(39), 1,
      aux_sym_name_repeat1,
  [637] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(128), 1,
      aux_sym_dn_spec_token2,
    ACTIONS(130), 2,
      anon_sym_COMMA,
      anon_sym_PLUS,
  [648] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(168), 1,
      sym__stringchar,
    ACTIONS(95), 2,
      anon_sym_DQUOTE,
      anon_sym_BSLASH,
  [659] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(170), 1,
      aux_sym_dn_spec_token2,
    ACTIONS(172), 1,
      anon_sym_COMMA,
    STATE(39), 1,
      aux_sym_name_repeat1,
  [672] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(174), 1,
      aux_sym_dn_spec_token2,
    ACTIONS(176), 2,
      anon_sym_COMMA,
      anon_sym_PLUS,
  [683] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(147), 1,
      aux_sym_dn_spec_token2,
    ACTIONS(178), 1,
      anon_sym_DOT,
    ACTIONS(180), 1,
      anon_sym_SEMI,
  [696] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(182), 1,
      aux_sym_dn_spec_token2,
    ACTIONS(184), 1,
      aux_sym_option_token1,
    STATE(45), 1,
      aux_sym_option_repeat1,
  [709] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(187), 1,
      aux_sym_dn_spec_token1,
    ACTIONS(189), 1,
      anon_sym_COLON,
    ACTIONS(191), 1,
      anon_sym_LT,
  [722] = 4,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(193), 1,
      anon_sym_COLON,
    ACTIONS(195), 1,
      aux_sym_option_token1,
    STATE(38), 1,
      aux_sym_option_repeat1,
  [735] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(197), 1,
      aux_sym_dn_spec_token2,
    ACTIONS(50), 2,
      anon_sym_COMMA,
      anon_sym_PLUS,
  [746] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(159), 1,
      aux_sym_dn_spec_token2,
    ACTIONS(199), 1,
      aux_sym_option_token1,
    STATE(45), 1,
      aux_sym_option_repeat1,
  [759] = 2,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(201), 3,
      anon_sym_EQ,
      anon_sym_COLON,
      anon_sym_SEMI,
  [768] = 2,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(203), 3,
      anon_sym_EQ,
      anon_sym_COLON,
      anon_sym_SEMI,
  [777] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(193), 1,
      aux_sym_dn_spec_token2,
    ACTIONS(205), 1,
      aux_sym_option_token1,
    STATE(49), 1,
      aux_sym_option_repeat1,
  [790] = 4,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(182), 1,
      anon_sym_COLON,
    ACTIONS(207), 1,
      aux_sym_option_token1,
    STATE(53), 1,
      aux_sym_option_repeat1,
  [803] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(210), 1,
      aux_sym_dn_spec_token2,
    ACTIONS(212), 2,
      anon_sym_COMMA,
      anon_sym_PLUS,
  [814] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(172), 1,
      anon_sym_COMMA,
    ACTIONS(214), 1,
      aux_sym_dn_spec_token2,
    STATE(42), 1,
      aux_sym_name_repeat1,
  [827] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(201), 1,
      aux_sym_dn_spec_token2,
    ACTIONS(216), 1,
      anon_sym_SEMI,
  [837] = 3,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(218), 1,
      anon_sym_COLON,
    ACTIONS(220), 1,
      anon_sym_SEMI,
  [847] = 3,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(222), 1,
      aux_sym_option_token1,
    STATE(18), 1,
      sym__keychar,
  [857] = 1,
    ACTIONS(224), 3,
      ts_builtin_sym_end,
      anon_sym_dn_COLON,
      sym_comment,
  [863] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(163), 1,
      aux_sym_dn_spec_token2,
    ACTIONS(226), 1,
      anon_sym_COMMA,
  [873] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(218), 1,
      aux_sym_dn_spec_token2,
    ACTIONS(228), 1,
      anon_sym_SEMI,
  [883] = 1,
    ACTIONS(230), 3,
      ts_builtin_sym_end,
      anon_sym_dn_COLON,
      sym_comment,
  [889] = 3,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(232), 1,
      anon_sym_changetype_COLON,
    STATE(65), 1,
      sym_changerecord,
  [899] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(203), 1,
      aux_sym_dn_spec_token2,
    ACTIONS(234), 1,
      anon_sym_SEMI,
  [909] = 1,
    ACTIONS(236), 3,
      ts_builtin_sym_end,
      anon_sym_dn_COLON,
      sym_comment,
  [915] = 1,
    ACTIONS(238), 3,
      ts_builtin_sym_end,
      anon_sym_dn_COLON,
      sym_comment,
  [921] = 3,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(240), 1,
      anon_sym_COLON,
    STATE(88), 1,
      sym_value_spec,
  [931] = 3,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(242), 1,
      sym_identifier,
    STATE(84), 1,
      sym_base64_string,
  [941] = 3,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(244), 1,
      aux_sym_option_token1,
    STATE(17), 1,
      sym__keychar,
  [951] = 1,
    ACTIONS(246), 3,
      ts_builtin_sym_end,
      anon_sym_dn_COLON,
      sym_comment,
  [957] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(248), 1,
      aux_sym_dn_spec_token2,
  [964] = 2,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(248), 1,
      anon_sym_COLON,
  [971] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(250), 1,
      aux_sym_dn_spec_token2,
  [978] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(252), 1,
      aux_sym_dn_spec_token1,
  [985] = 2,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(254), 1,
      aux_sym_ldap_oid_token1,
  [992] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(256), 1,
      aux_sym_value_spec_token1,
  [999] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(258), 1,
      aux_sym_dn_spec_token1,
  [1006] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(260), 1,
      aux_sym_dn_spec_token1,
  [1013] = 2,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(262), 1,
      anon_sym_DASH,
  [1020] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(264), 1,
      aux_sym_dn_spec_token2,
  [1027] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(266), 1,
      aux_sym_dn_spec_token2,
  [1034] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(268), 1,
      sym_url,
  [1041] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(270), 1,
      aux_sym_dn_spec_token2,
  [1048] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(272), 1,
      aux_sym_dn_spec_token2,
  [1055] = 2,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(274), 1,
      anon_sym_DASH,
  [1062] = 2,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(276), 1,
      anon_sym_changetype_COLON,
  [1069] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(278), 1,
      aux_sym_dn_spec_token2,
  [1076] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(280), 1,
      aux_sym_dn_spec_token2,
  [1083] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(282), 1,
      aux_sym_dn_spec_token1,
  [1090] = 2,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(284), 1,
      anon_sym_SEMI,
  [1097] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(286), 1,
      aux_sym_dn_spec_token2,
  [1104] = 2,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(288), 1,
      ts_builtin_sym_end,
  [1111] = 2,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(290), 1,
      anon_sym_EQ,
  [1118] = 2,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(292), 1,
      sym__hexpair,
  [1125] = 2,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(294), 1,
      anon_sym_COLON,
  [1132] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(294), 1,
      aux_sym_dn_spec_token2,
  [1139] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(296), 1,
      aux_sym_dn_spec_token2,
  [1146] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(298), 1,
      aux_sym_dn_spec_token2,
  [1153] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(300), 1,
      aux_sym_dn_spec_token2,
  [1160] = 2,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(278), 1,
      anon_sym_COLON,
  [1167] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(302), 1,
      aux_sym_dn_spec_token1,
  [1174] = 2,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(304), 1,
      aux_sym_ldap_oid_token1,
  [1181] = 2,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(306), 1,
      anon_sym_newrdn_COLON,
  [1188] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(308), 1,
      aux_sym_dn_spec_token2,
  [1195] = 2,
    ACTIONS(19), 1,
      sym_comment,
    ACTIONS(310), 1,
      anon_sym_SEMI,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 23,
  [SMALL_STATE(4)] = 51,
  [SMALL_STATE(5)] = 70,
  [SMALL_STATE(6)] = 89,
  [SMALL_STATE(7)] = 104,
  [SMALL_STATE(8)] = 119,
  [SMALL_STATE(9)] = 134,
  [SMALL_STATE(10)] = 153,
  [SMALL_STATE(11)] = 169,
  [SMALL_STATE(12)] = 191,
  [SMALL_STATE(13)] = 209,
  [SMALL_STATE(14)] = 225,
  [SMALL_STATE(15)] = 243,
  [SMALL_STATE(16)] = 265,
  [SMALL_STATE(17)] = 287,
  [SMALL_STATE(18)] = 303,
  [SMALL_STATE(19)] = 320,
  [SMALL_STATE(20)] = 337,
  [SMALL_STATE(21)] = 348,
  [SMALL_STATE(22)] = 365,
  [SMALL_STATE(23)] = 382,
  [SMALL_STATE(24)] = 399,
  [SMALL_STATE(25)] = 418,
  [SMALL_STATE(26)] = 437,
  [SMALL_STATE(27)] = 446,
  [SMALL_STATE(28)] = 463,
  [SMALL_STATE(29)] = 479,
  [SMALL_STATE(30)] = 495,
  [SMALL_STATE(31)] = 511,
  [SMALL_STATE(32)] = 527,
  [SMALL_STATE(33)] = 539,
  [SMALL_STATE(34)] = 551,
  [SMALL_STATE(35)] = 567,
  [SMALL_STATE(36)] = 583,
  [SMALL_STATE(37)] = 599,
  [SMALL_STATE(38)] = 611,
  [SMALL_STATE(39)] = 624,
  [SMALL_STATE(40)] = 637,
  [SMALL_STATE(41)] = 648,
  [SMALL_STATE(42)] = 659,
  [SMALL_STATE(43)] = 672,
  [SMALL_STATE(44)] = 683,
  [SMALL_STATE(45)] = 696,
  [SMALL_STATE(46)] = 709,
  [SMALL_STATE(47)] = 722,
  [SMALL_STATE(48)] = 735,
  [SMALL_STATE(49)] = 746,
  [SMALL_STATE(50)] = 759,
  [SMALL_STATE(51)] = 768,
  [SMALL_STATE(52)] = 777,
  [SMALL_STATE(53)] = 790,
  [SMALL_STATE(54)] = 803,
  [SMALL_STATE(55)] = 814,
  [SMALL_STATE(56)] = 827,
  [SMALL_STATE(57)] = 837,
  [SMALL_STATE(58)] = 847,
  [SMALL_STATE(59)] = 857,
  [SMALL_STATE(60)] = 863,
  [SMALL_STATE(61)] = 873,
  [SMALL_STATE(62)] = 883,
  [SMALL_STATE(63)] = 889,
  [SMALL_STATE(64)] = 899,
  [SMALL_STATE(65)] = 909,
  [SMALL_STATE(66)] = 915,
  [SMALL_STATE(67)] = 921,
  [SMALL_STATE(68)] = 931,
  [SMALL_STATE(69)] = 941,
  [SMALL_STATE(70)] = 951,
  [SMALL_STATE(71)] = 957,
  [SMALL_STATE(72)] = 964,
  [SMALL_STATE(73)] = 971,
  [SMALL_STATE(74)] = 978,
  [SMALL_STATE(75)] = 985,
  [SMALL_STATE(76)] = 992,
  [SMALL_STATE(77)] = 999,
  [SMALL_STATE(78)] = 1006,
  [SMALL_STATE(79)] = 1013,
  [SMALL_STATE(80)] = 1020,
  [SMALL_STATE(81)] = 1027,
  [SMALL_STATE(82)] = 1034,
  [SMALL_STATE(83)] = 1041,
  [SMALL_STATE(84)] = 1048,
  [SMALL_STATE(85)] = 1055,
  [SMALL_STATE(86)] = 1062,
  [SMALL_STATE(87)] = 1069,
  [SMALL_STATE(88)] = 1076,
  [SMALL_STATE(89)] = 1083,
  [SMALL_STATE(90)] = 1090,
  [SMALL_STATE(91)] = 1097,
  [SMALL_STATE(92)] = 1104,
  [SMALL_STATE(93)] = 1111,
  [SMALL_STATE(94)] = 1118,
  [SMALL_STATE(95)] = 1125,
  [SMALL_STATE(96)] = 1132,
  [SMALL_STATE(97)] = 1139,
  [SMALL_STATE(98)] = 1146,
  [SMALL_STATE(99)] = 1153,
  [SMALL_STATE(100)] = 1160,
  [SMALL_STATE(101)] = 1167,
  [SMALL_STATE(102)] = 1174,
  [SMALL_STATE(103)] = 1181,
  [SMALL_STATE(104)] = 1188,
  [SMALL_STATE(105)] = 1195,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(103),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [21] = {.entry = {.count = 1, .reusable = false}}, SHIFT(69),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(33),
  [25] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_repeat1, 2),
  [27] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_repeat1, 2), SHIFT_REPEAT(37),
  [30] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_repeat1, 2), SHIFT_REPEAT(4),
  [33] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string, 1),
  [35] = {.entry = {.count = 1, .reusable = false}}, SHIFT(37),
  [37] = {.entry = {.count = 1, .reusable = false}}, SHIFT(9),
  [39] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_change_modify_repeat1, 2),
  [41] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_change_modify_repeat1, 2), SHIFT_REPEAT(101),
  [44] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_change_modify, 2),
  [46] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [48] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_change_modify, 3),
  [50] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string, 2),
  [52] = {.entry = {.count = 1, .reusable = false}}, SHIFT(4),
  [54] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_attributeType_repeat1, 2),
  [56] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_attributeType_repeat1, 2), SHIFT_REPEAT(10),
  [59] = {.entry = {.count = 1, .reusable = false}}, SHIFT(94),
  [61] = {.entry = {.count = 1, .reusable = false}}, SHIFT(21),
  [63] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [65] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [67] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [69] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attributeType, 3),
  [71] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [73] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [75] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(74),
  [78] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(14),
  [81] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attributeType, 2),
  [83] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [85] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_attributeType, 2),
  [87] = {.entry = {.count = 1, .reusable = false}}, SHIFT(27),
  [89] = {.entry = {.count = 1, .reusable = false}}, SHIFT(54),
  [91] = {.entry = {.count = 1, .reusable = false}}, SHIFT(32),
  [93] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [95] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pair, 2),
  [97] = {.entry = {.count = 1, .reusable = false}}, SHIFT(48),
  [99] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [101] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_attributeType_repeat1, 2),
  [103] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_attributeType_repeat1, 2), SHIFT_REPEAT(22),
  [106] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_repeat1, 2), SHIFT_REPEAT(32),
  [109] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_string_repeat1, 2), SHIFT_REPEAT(23),
  [112] = {.entry = {.count = 1, .reusable = false}}, SHIFT(58),
  [114] = {.entry = {.count = 1, .reusable = false}}, SHIFT(44),
  [116] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_mod_spec, 7),
  [118] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_attributeType, 3),
  [120] = {.entry = {.count = 1, .reusable = false}}, SHIFT(22),
  [122] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_name_componet, 2),
  [124] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_name_componet, 2),
  [126] = {.entry = {.count = 1, .reusable = false}}, SHIFT(24),
  [128] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_name_componet_repeat1, 2),
  [130] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_name_componet_repeat1, 2),
  [132] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_name_componet_repeat1, 2), SHIFT_REPEAT(24),
  [135] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_name_componet, 1),
  [137] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_name_componet, 1),
  [139] = {.entry = {.count = 1, .reusable = false}}, SHIFT(47),
  [141] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [143] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [145] = {.entry = {.count = 1, .reusable = false}}, SHIFT(41),
  [147] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ldap_oid, 1),
  [149] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [151] = {.entry = {.count = 1, .reusable = false}}, SHIFT(52),
  [153] = {.entry = {.count = 1, .reusable = true}}, SHIFT(90),
  [155] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [157] = {.entry = {.count = 1, .reusable = false}}, SHIFT(20),
  [159] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_option, 2),
  [161] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [163] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_name_repeat1, 2),
  [165] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_name_repeat1, 2), SHIFT_REPEAT(16),
  [168] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pair, 2),
  [170] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_name, 2),
  [172] = {.entry = {.count = 1, .reusable = false}}, SHIFT(16),
  [174] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attributeTypeAndValue, 3),
  [176] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_attributeTypeAndValue, 3),
  [178] = {.entry = {.count = 1, .reusable = false}}, SHIFT(102),
  [180] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_ldap_oid, 1),
  [182] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_option_repeat1, 2),
  [184] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_option_repeat1, 2), SHIFT_REPEAT(45),
  [187] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [189] = {.entry = {.count = 1, .reusable = false}}, SHIFT(77),
  [191] = {.entry = {.count = 1, .reusable = false}}, SHIFT(78),
  [193] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_option, 1),
  [195] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [197] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 2),
  [199] = {.entry = {.count = 1, .reusable = false}}, SHIFT(45),
  [201] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attributeType, 1),
  [203] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ldap_oid, 3),
  [205] = {.entry = {.count = 1, .reusable = false}}, SHIFT(49),
  [207] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_option_repeat1, 2), SHIFT_REPEAT(53),
  [210] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 3),
  [212] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string, 3),
  [214] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_name, 1),
  [216] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_attributeType, 1),
  [218] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_AttributeDescription, 1),
  [220] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [222] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [224] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_changerecord, 3),
  [226] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_name_repeat1, 2),
  [228] = {.entry = {.count = 1, .reusable = false}}, SHIFT(35),
  [230] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_change_add, 2),
  [232] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [234] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_ldap_oid, 3),
  [236] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ldif_change_record, 2),
  [238] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_change_delete, 2),
  [240] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [242] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [244] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [246] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_change_moddn, 2),
  [248] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_options, 1),
  [250] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [252] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [254] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [256] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [258] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [260] = {.entry = {.count = 1, .reusable = true}}, SHIFT(82),
  [262] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attrval_spec, 3),
  [264] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_value_spec, 3),
  [266] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [268] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [270] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_base64_string, 1),
  [272] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_value_spec, 4),
  [274] = {.entry = {.count = 1, .reusable = true}}, SHIFT(73),
  [276] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dn_spec, 4),
  [278] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_options, 3),
  [280] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [282] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [284] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [286] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [288] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [290] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [292] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [294] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_AttributeDescription, 3),
  [296] = {.entry = {.count = 1, .reusable = true}}, SHIFT(86),
  [298] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_distinguishedName, 1),
  [300] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [302] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [304] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [306] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [308] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [310] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_ldif(void) {
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
