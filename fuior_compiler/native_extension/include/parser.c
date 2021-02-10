#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 10
#define STATE_COUNT 196
#define SYMBOL_COUNT 62
#define ALIAS_COUNT 4
#define TOKEN_COUNT 35
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 7

enum {
  sym_comment = 1,
  sym__endl = 2,
  anon_sym_if = 3,
  anon_sym_end = 4,
  anon_sym_elseif = 5,
  anon_sym_else = 6,
  anon_sym_choose = 7,
  anon_sym_STAR = 8,
  anon_sym_LBRACK = 9,
  anon_sym_RBRACK = 10,
  anon_sym_PLUS = 11,
  anon_sym_DASH = 12,
  anon_sym_EQ = 13,
  anon_sym_LBRACE = 14,
  anon_sym_RBRACE = 15,
  sym_bare_word = 16,
  anon_sym_COLON = 17,
  sym_text_copy = 18,
  anon_sym_not = 19,
  anon_sym_SLASH = 20,
  anon_sym_LT = 21,
  anon_sym_GT = 22,
  anon_sym_GT_EQ = 23,
  anon_sym_LT_EQ = 24,
  anon_sym_BANG_EQ = 25,
  anon_sym_and = 26,
  anon_sym_or = 27,
  anon_sym_LPAREN = 28,
  anon_sym_RPAREN = 29,
  sym_identifier = 30,
  sym_number = 31,
  sym_string = 32,
  anon_sym_true = 33,
  anon_sym_false = 34,
  sym_source_file = 35,
  sym__statement = 36,
  sym_if_statement = 37,
  sym_condition = 38,
  sym_if_clause = 39,
  sym_elseif_clause = 40,
  sym_else_clause = 41,
  sym_choose_statement = 42,
  sym_choice = 43,
  sym_choice_condition = 44,
  sym_stat_operation = 45,
  sym_stat_operator = 46,
  sym_stat_rvalue = 47,
  sym_block = 48,
  sym_command = 49,
  sym_command_arg = 50,
  sym_show_text = 51,
  sym__expression = 52,
  sym__constant = 53,
  sym_unary_expression = 54,
  sym_binary_expression = 55,
  sym_paran_expression = 56,
  sym_boolean = 57,
  aux_sym_source_file_repeat1 = 58,
  aux_sym_if_statement_repeat1 = 59,
  aux_sym_choose_statement_repeat1 = 60,
  aux_sym_command_repeat1 = 61,
  alias_sym_text_animation = 62,
  alias_sym_stat_lvalue = 63,
  alias_sym_command_verb = 64,
  alias_sym_text_actor = 65,
};

static const char *ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_comment] = "comment",
  [sym__endl] = "_endl",
  [anon_sym_if] = "if",
  [anon_sym_end] = "end",
  [anon_sym_elseif] = "elseif",
  [anon_sym_else] = "else",
  [anon_sym_choose] = "choose",
  [anon_sym_STAR] = "*",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [anon_sym_PLUS] = "+",
  [anon_sym_DASH] = "-",
  [anon_sym_EQ] = "=",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [sym_bare_word] = "bare_word",
  [anon_sym_COLON] = ":",
  [sym_text_copy] = "text_copy",
  [anon_sym_not] = "not",
  [anon_sym_SLASH] = "/",
  [anon_sym_LT] = "<",
  [anon_sym_GT] = ">",
  [anon_sym_GT_EQ] = ">=",
  [anon_sym_LT_EQ] = "<=",
  [anon_sym_BANG_EQ] = "!=",
  [anon_sym_and] = "and",
  [anon_sym_or] = "or",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [sym_identifier] = "identifier",
  [sym_number] = "number",
  [sym_string] = "string",
  [anon_sym_true] = "true",
  [anon_sym_false] = "false",
  [sym_source_file] = "source_file",
  [sym__statement] = "_statement",
  [sym_if_statement] = "if_statement",
  [sym_condition] = "condition",
  [sym_if_clause] = "if_clause",
  [sym_elseif_clause] = "elseif_clause",
  [sym_else_clause] = "else_clause",
  [sym_choose_statement] = "choose_statement",
  [sym_choice] = "choice",
  [sym_choice_condition] = "choice_condition",
  [sym_stat_operation] = "stat_operation",
  [sym_stat_operator] = "stat_operator",
  [sym_stat_rvalue] = "stat_rvalue",
  [sym_block] = "block",
  [sym_command] = "command",
  [sym_command_arg] = "command_arg",
  [sym_show_text] = "show_text",
  [sym__expression] = "_expression",
  [sym__constant] = "_constant",
  [sym_unary_expression] = "unary_expression",
  [sym_binary_expression] = "binary_expression",
  [sym_paran_expression] = "paran_expression",
  [sym_boolean] = "boolean",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_if_statement_repeat1] = "if_statement_repeat1",
  [aux_sym_choose_statement_repeat1] = "choose_statement_repeat1",
  [aux_sym_command_repeat1] = "command_repeat1",
  [alias_sym_text_animation] = "text_animation",
  [alias_sym_stat_lvalue] = "stat_lvalue",
  [alias_sym_command_verb] = "command_verb",
  [alias_sym_text_actor] = "text_actor",
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym__endl] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_if] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_end] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_elseif] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_else] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_choose] = {
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
  [anon_sym_PLUS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ] = {
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
  [sym_bare_word] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [sym_text_copy] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_not] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SLASH] = {
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
  [anon_sym_GT_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BANG_EQ] = {
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
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [sym_string] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_true] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_false] = {
    .visible = true,
    .named = false,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym__statement] = {
    .visible = false,
    .named = true,
  },
  [sym_if_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_condition] = {
    .visible = true,
    .named = true,
  },
  [sym_if_clause] = {
    .visible = true,
    .named = true,
  },
  [sym_elseif_clause] = {
    .visible = true,
    .named = true,
  },
  [sym_else_clause] = {
    .visible = true,
    .named = true,
  },
  [sym_choose_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_choice] = {
    .visible = true,
    .named = true,
  },
  [sym_choice_condition] = {
    .visible = true,
    .named = true,
  },
  [sym_stat_operation] = {
    .visible = true,
    .named = true,
  },
  [sym_stat_operator] = {
    .visible = true,
    .named = true,
  },
  [sym_stat_rvalue] = {
    .visible = true,
    .named = true,
  },
  [sym_block] = {
    .visible = true,
    .named = true,
  },
  [sym_command] = {
    .visible = true,
    .named = true,
  },
  [sym_command_arg] = {
    .visible = true,
    .named = true,
  },
  [sym_show_text] = {
    .visible = true,
    .named = true,
  },
  [sym__expression] = {
    .visible = false,
    .named = true,
  },
  [sym__constant] = {
    .visible = false,
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
  [sym_paran_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_boolean] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_if_statement_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_choose_statement_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_command_repeat1] = {
    .visible = false,
    .named = false,
  },
  [alias_sym_text_animation] = {
    .visible = true,
    .named = true,
  },
  [alias_sym_stat_lvalue] = {
    .visible = true,
    .named = true,
  },
  [alias_sym_command_verb] = {
    .visible = true,
    .named = true,
  },
  [alias_sym_text_actor] = {
    .visible = true,
    .named = true,
  },
};

static TSSymbol ts_alias_sequences[5][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [1] = {
    [0] = alias_sym_command_verb,
  },
  [2] = {
    [0] = alias_sym_stat_lvalue,
  },
  [3] = {
    [0] = alias_sym_text_actor,
  },
  [4] = {
    [0] = alias_sym_text_actor,
    [3] = alias_sym_text_animation,
  },
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  switch (state) {
    case 0:
      if (lookahead == 0) ADVANCE(28);
      if (lookahead == '\n') ADVANCE(32);
      if (lookahead == '!') ADVANCE(17);
      if (lookahead == '"') ADVANCE(13);
      if (lookahead == '#') ADVANCE(31);
      if (lookahead == '(') ADVANCE(76);
      if (lookahead == ')') ADVANCE(77);
      if (lookahead == '*') ADVANCE(41);
      if (lookahead == '+') ADVANCE(44);
      if (lookahead == '-') ADVANCE(45);
      if (lookahead == '/') ADVANCE(66);
      if (lookahead == ':') ADVANCE(61);
      if (lookahead == '<') ADVANCE(67);
      if (lookahead == '=') ADVANCE(46);
      if (lookahead == '>') ADVANCE(68);
      if (lookahead == '[') ADVANCE(42);
      if (lookahead == ']') ADVANCE(43);
      if (lookahead == 'a') ADVANCE(90);
      if (lookahead == 'c') ADVANCE(87);
      if (lookahead == 'e') ADVANCE(88);
      if (lookahead == 'f') ADVANCE(78);
      if (lookahead == 'i') ADVANCE(85);
      if (lookahead == 'n') ADVANCE(92);
      if (lookahead == 'o') ADVANCE(95);
      if (lookahead == 't') ADVANCE(96);
      if (lookahead == '{') ADVANCE(47);
      if (lookahead == '}') ADVANCE(48);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(103);
      if (lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 1:
      if (lookahead == 0) ADVANCE(28);
      if (lookahead == '\n') ADVANCE(32);
      if (lookahead == '!') ADVANCE(17);
      if (lookahead == '#') ADVANCE(31);
      if (lookahead == '*') ADVANCE(41);
      if (lookahead == '+') ADVANCE(44);
      if (lookahead == '-') ADVANCE(45);
      if (lookahead == '/') ADVANCE(66);
      if (lookahead == '<') ADVANCE(67);
      if (lookahead == '=') ADVANCE(46);
      if (lookahead == '>') ADVANCE(68);
      if (lookahead == 'a') ADVANCE(90);
      if (lookahead == 'c') ADVANCE(87);
      if (lookahead == 'i') ADVANCE(85);
      if (lookahead == 'o') ADVANCE(95);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(1)
      if (lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 2:
      if (lookahead == 0) ADVANCE(28);
      if (lookahead == '\n') ADVANCE(32);
      if (lookahead == '#') ADVANCE(31);
      if (lookahead == 'c') ADVANCE(87);
      if (lookahead == 'i') ADVANCE(85);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(2)
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 3:
      if (lookahead == '\n') ADVANCE(32);
      if (lookahead == '!') ADVANCE(17);
      if (lookahead == '#') ADVANCE(31);
      if (lookahead == ')') ADVANCE(77);
      if (lookahead == '*') ADVANCE(41);
      if (lookahead == '+') ADVANCE(44);
      if (lookahead == '-') ADVANCE(45);
      if (lookahead == '/') ADVANCE(66);
      if (lookahead == '<') ADVANCE(67);
      if (lookahead == '=') ADVANCE(46);
      if (lookahead == '>') ADVANCE(68);
      if (lookahead == ']') ADVANCE(43);
      if (lookahead == 'a') ADVANCE(23);
      if (lookahead == 'e') ADVANCE(22);
      if (lookahead == 'o') ADVANCE(24);
      if (lookahead == '}') ADVANCE(48);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(3)
      END_STATE();
    case 4:
      if (lookahead == '\n') ADVANCE(32);
      if (lookahead == '!') ADVANCE(17);
      if (lookahead == '#') ADVANCE(31);
      if (lookahead == '*') ADVANCE(41);
      if (lookahead == '+') ADVANCE(44);
      if (lookahead == '-') ADVANCE(45);
      if (lookahead == '/') ADVANCE(66);
      if (lookahead == '<') ADVANCE(67);
      if (lookahead == '=') ADVANCE(46);
      if (lookahead == '>') ADVANCE(68);
      if (lookahead == 'a') ADVANCE(90);
      if (lookahead == 'c') ADVANCE(87);
      if (lookahead == 'e') ADVANCE(88);
      if (lookahead == 'i') ADVANCE(85);
      if (lookahead == 'o') ADVANCE(95);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(4)
      if (lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 5:
      if (lookahead == '\n') ADVANCE(32);
      if (lookahead == '!') ADVANCE(17);
      if (lookahead == '#') ADVANCE(31);
      if (lookahead == '*') ADVANCE(41);
      if (lookahead == '+') ADVANCE(44);
      if (lookahead == '-') ADVANCE(45);
      if (lookahead == '/') ADVANCE(66);
      if (lookahead == '<') ADVANCE(67);
      if (lookahead == '=') ADVANCE(46);
      if (lookahead == '>') ADVANCE(68);
      if (lookahead == 'a') ADVANCE(90);
      if (lookahead == 'c') ADVANCE(87);
      if (lookahead == 'e') ADVANCE(91);
      if (lookahead == 'i') ADVANCE(85);
      if (lookahead == 'o') ADVANCE(95);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(5)
      if (lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 6:
      if (lookahead == '\n') ADVANCE(32);
      if (lookahead == '"') ADVANCE(51);
      if (lookahead == '#') ADVANCE(30);
      if (lookahead == '+') ADVANCE(44);
      if (lookahead == '-') ADVANCE(45);
      if (lookahead == ':') ADVANCE(61);
      if (lookahead == '=') ADVANCE(46);
      if (lookahead == 'f') ADVANCE(52);
      if (lookahead == 't') ADVANCE(56);
      if (lookahead == '{') ADVANCE(47);
      if (lookahead == '' ||
          lookahead == '') ADVANCE(49);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(6)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(104);
      if (lookahead != 0) ADVANCE(60);
      END_STATE();
    case 7:
      if (lookahead == '\n') ADVANCE(32);
      if (lookahead == '"') ADVANCE(51);
      if (lookahead == '#') ADVANCE(30);
      if (lookahead == 'f') ADVANCE(52);
      if (lookahead == 't') ADVANCE(56);
      if (lookahead == '{') ADVANCE(47);
      if (lookahead == '' ||
          lookahead == '') ADVANCE(50);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(7)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(104);
      if (lookahead != 0) ADVANCE(60);
      END_STATE();
    case 8:
      if (lookahead == '\n') ADVANCE(32);
      if (lookahead == '#') ADVANCE(31);
      if (lookahead == '*') ADVANCE(41);
      if (lookahead == 'c') ADVANCE(87);
      if (lookahead == 'e') ADVANCE(91);
      if (lookahead == 'i') ADVANCE(85);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(8)
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 9:
      if (lookahead == '\n') ADVANCE(32);
      if (lookahead == '#') ADVANCE(31);
      if (lookahead == 'c') ADVANCE(87);
      if (lookahead == 'e') ADVANCE(88);
      if (lookahead == 'i') ADVANCE(85);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(9)
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 10:
      if (lookahead == '\r') SKIP(15)
      if (lookahead == '#') ADVANCE(29);
      if (lookahead == '[') ADVANCE(42);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(10);
      if (lookahead == '' ||
          lookahead == '') ADVANCE(62);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(64);
      END_STATE();
    case 11:
      if (lookahead == '\r') SKIP(16)
      if (lookahead == '#') ADVANCE(29);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(11);
      if (lookahead == '' ||
          lookahead == '') ADVANCE(63);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(64);
      END_STATE();
    case 12:
      if (lookahead == '"') ADVANCE(13);
      if (lookahead == '#') ADVANCE(31);
      if (lookahead == '(') ADVANCE(76);
      if (lookahead == '-') ADVANCE(45);
      if (lookahead == 'f') ADVANCE(78);
      if (lookahead == 'n') ADVANCE(92);
      if (lookahead == 't') ADVANCE(96);
      if (lookahead == '\t' ||
          ('' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(12)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(103);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 13:
      if (lookahead == '"') ADVANCE(106);
      if (lookahead != 0) ADVANCE(13);
      END_STATE();
    case 14:
      if (lookahead == '#') ADVANCE(31);
      if (lookahead == '\t' ||
          ('' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(14)
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 15:
      if (lookahead == '#') ADVANCE(29);
      if (lookahead == '[') ADVANCE(42);
      if (lookahead == '' ||
          lookahead == '') ADVANCE(62);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(15)
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(64);
      END_STATE();
    case 16:
      if (lookahead == '#') ADVANCE(29);
      if (lookahead == '' ||
          lookahead == '') ADVANCE(63);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(16)
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(64);
      END_STATE();
    case 17:
      if (lookahead == '=') ADVANCE(71);
      END_STATE();
    case 18:
      if (lookahead == 'd') ADVANCE(72);
      END_STATE();
    case 19:
      if (lookahead == 'd') ADVANCE(34);
      END_STATE();
    case 20:
      if (lookahead == 'e') ADVANCE(38);
      END_STATE();
    case 21:
      if (lookahead == 'f') ADVANCE(36);
      END_STATE();
    case 22:
      if (lookahead == 'l') ADVANCE(25);
      if (lookahead == 'n') ADVANCE(19);
      END_STATE();
    case 23:
      if (lookahead == 'n') ADVANCE(18);
      END_STATE();
    case 24:
      if (lookahead == 'r') ADVANCE(74);
      END_STATE();
    case 25:
      if (lookahead == 's') ADVANCE(20);
      END_STATE();
    case 26:
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(26);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(64);
      END_STATE();
    case 27:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(105);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\r') ADVANCE(31);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(29);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(29);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(31);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(30);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(31);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(sym__endl);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(anon_sym_if);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(anon_sym_end);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(anon_sym_end);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(anon_sym_elseif);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(anon_sym_elseif);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(anon_sym_else);
      if (lookahead == 'i') ADVANCE(21);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(anon_sym_else);
      if (lookahead == 'i') ADVANCE(86);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(anon_sym_choose);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(anon_sym_STAR);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(anon_sym_PLUS);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(sym_bare_word);
      if (lookahead == '\n') ADVANCE(32);
      if (lookahead == '"') ADVANCE(51);
      if (lookahead == '#') ADVANCE(30);
      if (lookahead == '+') ADVANCE(44);
      if (lookahead == '-') ADVANCE(45);
      if (lookahead == ':') ADVANCE(61);
      if (lookahead == '=') ADVANCE(46);
      if (lookahead == 'f') ADVANCE(52);
      if (lookahead == 't') ADVANCE(56);
      if (lookahead == '{') ADVANCE(47);
      if (lookahead == '' ||
          lookahead == '') ADVANCE(49);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(6)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(104);
      if (lookahead != 0) ADVANCE(60);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(sym_bare_word);
      if (lookahead == '\n') ADVANCE(32);
      if (lookahead == '"') ADVANCE(51);
      if (lookahead == '#') ADVANCE(30);
      if (lookahead == 'f') ADVANCE(52);
      if (lookahead == 't') ADVANCE(56);
      if (lookahead == '{') ADVANCE(47);
      if (lookahead == '' ||
          lookahead == '') ADVANCE(50);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(7)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(104);
      if (lookahead != 0) ADVANCE(60);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(sym_bare_word);
      if (lookahead == '"') ADVANCE(106);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(13);
      if (lookahead != 0) ADVANCE(51);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(sym_bare_word);
      if (lookahead == 'a') ADVANCE(55);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(60);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(sym_bare_word);
      if (lookahead == 'e') ADVANCE(107);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(60);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(sym_bare_word);
      if (lookahead == 'e') ADVANCE(109);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(60);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(sym_bare_word);
      if (lookahead == 'l') ADVANCE(57);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(60);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(sym_bare_word);
      if (lookahead == 'r') ADVANCE(58);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(60);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(sym_bare_word);
      if (lookahead == 's') ADVANCE(54);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(60);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(sym_bare_word);
      if (lookahead == 'u') ADVANCE(53);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(60);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(sym_bare_word);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(105);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(60);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(sym_bare_word);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(60);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(sym_text_copy);
      if (lookahead == '#') ADVANCE(29);
      if (lookahead == '[') ADVANCE(42);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(10);
      if (lookahead == '' ||
          lookahead == '') ADVANCE(62);
      if (lookahead != 0 &&
          (lookahead < '\n' || '\r' < lookahead)) ADVANCE(64);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(sym_text_copy);
      if (lookahead == '#') ADVANCE(29);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(11);
      if (lookahead == '' ||
          lookahead == '') ADVANCE(63);
      if (lookahead != 0 &&
          (lookahead < '\n' || '\r' < lookahead)) ADVANCE(64);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(sym_text_copy);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(26);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(64);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(anon_sym_not);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(anon_sym_SLASH);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '=') ADVANCE(70);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(anon_sym_GT);
      if (lookahead == '=') ADVANCE(69);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(anon_sym_GT_EQ);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(anon_sym_LT_EQ);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(anon_sym_BANG_EQ);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(anon_sym_and);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(anon_sym_and);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(anon_sym_or);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(anon_sym_or);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(89);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(73);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(35);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(39);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(108);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(110);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(40);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(33);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(37);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'h') ADVANCE(93);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(97);
      if (lookahead == 'n') ADVANCE(80);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(98);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(79);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(80);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(100);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(94);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(99);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(75);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(101);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(81);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(83);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(84);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(65);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(82);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(27);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(103);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(59);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(104);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(105);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(sym_string);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(anon_sym_true);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(anon_sym_true);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(anon_sym_false);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(anon_sym_false);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(102);
      END_STATE();
    default:
      return false;
  }
}

static TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 2},
  [2] = {.lex_state = 0},
  [3] = {.lex_state = 6},
  [4] = {.lex_state = 12},
  [5] = {.lex_state = 0},
  [6] = {.lex_state = 2},
  [7] = {.lex_state = 0},
  [8] = {.lex_state = 7},
  [9] = {.lex_state = 15},
  [10] = {.lex_state = 12},
  [11] = {.lex_state = 7},
  [12] = {.lex_state = 2},
  [13] = {.lex_state = 12},
  [14] = {.lex_state = 12},
  [15] = {.lex_state = 7},
  [16] = {.lex_state = 12},
  [17] = {.lex_state = 12},
  [18] = {.lex_state = 3},
  [19] = {.lex_state = 0},
  [20] = {.lex_state = 2},
  [21] = {.lex_state = 15},
  [22] = {.lex_state = 0},
  [23] = {.lex_state = 14},
  [24] = {.lex_state = 0},
  [25] = {.lex_state = 3},
  [26] = {.lex_state = 1},
  [27] = {.lex_state = 2},
  [28] = {.lex_state = 2},
  [29] = {.lex_state = 7},
  [30] = {.lex_state = 3},
  [31] = {.lex_state = 3},
  [32] = {.lex_state = 12},
  [33] = {.lex_state = 12},
  [34] = {.lex_state = 12},
  [35] = {.lex_state = 12},
  [36] = {.lex_state = 12},
  [37] = {.lex_state = 9},
  [38] = {.lex_state = 3},
  [39] = {.lex_state = 3},
  [40] = {.lex_state = 12},
  [41] = {.lex_state = 0},
  [42] = {.lex_state = 0},
  [43] = {.lex_state = 0},
  [44] = {.lex_state = 0},
  [45] = {.lex_state = 2},
  [46] = {.lex_state = 7},
  [47] = {.lex_state = 3},
  [48] = {.lex_state = 3},
  [49] = {.lex_state = 3},
  [50] = {.lex_state = 3},
  [51] = {.lex_state = 3},
  [52] = {.lex_state = 3},
  [53] = {.lex_state = 9},
  [54] = {.lex_state = 12},
  [55] = {.lex_state = 0},
  [56] = {.lex_state = 0},
  [57] = {.lex_state = 0},
  [58] = {.lex_state = 3},
  [59] = {.lex_state = 3},
  [60] = {.lex_state = 0},
  [61] = {.lex_state = 0},
  [62] = {.lex_state = 2},
  [63] = {.lex_state = 16},
  [64] = {.lex_state = 0},
  [65] = {.lex_state = 0},
  [66] = {.lex_state = 2},
  [67] = {.lex_state = 0},
  [68] = {.lex_state = 0},
  [69] = {.lex_state = 3},
  [70] = {.lex_state = 16},
  [71] = {.lex_state = 0},
  [72] = {.lex_state = 3},
  [73] = {.lex_state = 2},
  [74] = {.lex_state = 0},
  [75] = {.lex_state = 0},
  [76] = {.lex_state = 2},
  [77] = {.lex_state = 2},
  [78] = {.lex_state = 0},
  [79] = {.lex_state = 3},
  [80] = {.lex_state = 9},
  [81] = {.lex_state = 9},
  [82] = {.lex_state = 4},
  [83] = {.lex_state = 9},
  [84] = {.lex_state = 9},
  [85] = {.lex_state = 1},
  [86] = {.lex_state = 12},
  [87] = {.lex_state = 12},
  [88] = {.lex_state = 12},
  [89] = {.lex_state = 12},
  [90] = {.lex_state = 12},
  [91] = {.lex_state = 8},
  [92] = {.lex_state = 9},
  [93] = {.lex_state = 1},
  [94] = {.lex_state = 1},
  [95] = {.lex_state = 1},
  [96] = {.lex_state = 1},
  [97] = {.lex_state = 1},
  [98] = {.lex_state = 1},
  [99] = {.lex_state = 8},
  [100] = {.lex_state = 9},
  [101] = {.lex_state = 9},
  [102] = {.lex_state = 9},
  [103] = {.lex_state = 9},
  [104] = {.lex_state = 9},
  [105] = {.lex_state = 1},
  [106] = {.lex_state = 8},
  [107] = {.lex_state = 8},
  [108] = {.lex_state = 5},
  [109] = {.lex_state = 8},
  [110] = {.lex_state = 8},
  [111] = {.lex_state = 4},
  [112] = {.lex_state = 12},
  [113] = {.lex_state = 12},
  [114] = {.lex_state = 12},
  [115] = {.lex_state = 12},
  [116] = {.lex_state = 12},
  [117] = {.lex_state = 8},
  [118] = {.lex_state = 4},
  [119] = {.lex_state = 4},
  [120] = {.lex_state = 4},
  [121] = {.lex_state = 4},
  [122] = {.lex_state = 4},
  [123] = {.lex_state = 4},
  [124] = {.lex_state = 8},
  [125] = {.lex_state = 8},
  [126] = {.lex_state = 8},
  [127] = {.lex_state = 8},
  [128] = {.lex_state = 8},
  [129] = {.lex_state = 4},
  [130] = {.lex_state = 5},
  [131] = {.lex_state = 12},
  [132] = {.lex_state = 12},
  [133] = {.lex_state = 12},
  [134] = {.lex_state = 12},
  [135] = {.lex_state = 12},
  [136] = {.lex_state = 5},
  [137] = {.lex_state = 5},
  [138] = {.lex_state = 5},
  [139] = {.lex_state = 5},
  [140] = {.lex_state = 5},
  [141] = {.lex_state = 5},
  [142] = {.lex_state = 5},
  [143] = {.lex_state = 6},
  [144] = {.lex_state = 12},
  [145] = {.lex_state = 7},
  [146] = {.lex_state = 12},
  [147] = {.lex_state = 0},
  [148] = {.lex_state = 3},
  [149] = {.lex_state = 0},
  [150] = {.lex_state = 0},
  [151] = {.lex_state = 0},
  [152] = {.lex_state = 0},
  [153] = {.lex_state = 0},
  [154] = {.lex_state = 6},
  [155] = {.lex_state = 12},
  [156] = {.lex_state = 7},
  [157] = {.lex_state = 12},
  [158] = {.lex_state = 0},
  [159] = {.lex_state = 3},
  [160] = {.lex_state = 0},
  [161] = {.lex_state = 0},
  [162] = {.lex_state = 0},
  [163] = {.lex_state = 0},
  [164] = {.lex_state = 0},
  [165] = {.lex_state = 12},
  [166] = {.lex_state = 3},
  [167] = {.lex_state = 15},
  [168] = {.lex_state = 12},
  [169] = {.lex_state = 0},
  [170] = {.lex_state = 3},
  [171] = {.lex_state = 0},
  [172] = {.lex_state = 3},
  [173] = {.lex_state = 16},
  [174] = {.lex_state = 0},
  [175] = {.lex_state = 15},
  [176] = {.lex_state = 12},
  [177] = {.lex_state = 0},
  [178] = {.lex_state = 3},
  [179] = {.lex_state = 0},
  [180] = {.lex_state = 3},
  [181] = {.lex_state = 16},
  [182] = {.lex_state = 0},
  [183] = {.lex_state = 12},
  [184] = {.lex_state = 0},
  [185] = {.lex_state = 0},
  [186] = {.lex_state = 0},
  [187] = {.lex_state = 0},
  [188] = {.lex_state = 0},
  [189] = {.lex_state = 0},
  [190] = {.lex_state = 0},
  [191] = {.lex_state = 12},
  [192] = {.lex_state = 14},
  [193] = {.lex_state = 0},
  [194] = {.lex_state = 12},
  [195] = {.lex_state = 14},
};

static uint16_t ts_parse_table[STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [anon_sym_LT] = ACTIONS(1),
    [anon_sym_true] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_if] = ACTIONS(1),
    [anon_sym_STAR] = ACTIONS(1),
    [anon_sym_elseif] = ACTIONS(1),
    [anon_sym_and] = ACTIONS(1),
    [sym_number] = ACTIONS(1),
    [anon_sym_SLASH] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_GT] = ACTIONS(1),
    [anon_sym_false] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_end] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(1),
    [anon_sym_or] = ACTIONS(1),
    [sym_string] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_GT_EQ] = ACTIONS(1),
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_PLUS] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [sym__endl] = ACTIONS(1),
    [anon_sym_choose] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_BANG_EQ] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [anon_sym_not] = ACTIONS(1),
    [anon_sym_LT_EQ] = ACTIONS(1),
  },
  [1] = {
    [sym_command] = STATE(6),
    [sym_stat_operation] = STATE(6),
    [sym_show_text] = STATE(6),
    [sym_source_file] = STATE(5),
    [sym__statement] = STATE(6),
    [sym_if_statement] = STATE(6),
    [aux_sym_source_file_repeat1] = STATE(6),
    [sym_choose_statement] = STATE(6),
    [sym__endl] = ACTIONS(5),
    [ts_builtin_sym_end] = ACTIONS(7),
    [anon_sym_choose] = ACTIONS(9),
    [sym_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(11),
    [anon_sym_if] = ACTIONS(13),
  },
  [2] = {
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(15),
  },
  [3] = {
    [sym_boolean] = STATE(11),
    [sym_stat_operator] = STATE(14),
    [sym__constant] = STATE(11),
    [sym_command_arg] = STATE(15),
    [aux_sym_command_repeat1] = STATE(15),
    [sym_number] = ACTIONS(17),
    [anon_sym_true] = ACTIONS(19),
    [anon_sym_COLON] = ACTIONS(21),
    [anon_sym_PLUS] = ACTIONS(23),
    [sym_bare_word] = ACTIONS(17),
    [anon_sym_EQ] = ACTIONS(23),
    [sym_string] = ACTIONS(17),
    [anon_sym_false] = ACTIONS(19),
    [anon_sym_DASH] = ACTIONS(23),
    [sym__endl] = ACTIONS(25),
    [anon_sym_LBRACE] = ACTIONS(27),
    [sym_comment] = ACTIONS(29),
  },
  [4] = {
    [sym_boolean] = STATE(18),
    [sym_unary_expression] = STATE(18),
    [sym_binary_expression] = STATE(18),
    [sym__expression] = STATE(18),
    [sym__constant] = STATE(18),
    [sym_condition] = STATE(19),
    [sym_paran_expression] = STATE(18),
    [sym_number] = ACTIONS(31),
    [anon_sym_true] = ACTIONS(33),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(31),
    [anon_sym_false] = ACTIONS(33),
    [anon_sym_DASH] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(37),
    [sym_identifier] = ACTIONS(39),
    [anon_sym_not] = ACTIONS(41),
  },
  [5] = {
    [sym_comment] = ACTIONS(3),
    [ts_builtin_sym_end] = ACTIONS(43),
  },
  [6] = {
    [sym_command] = STATE(20),
    [sym_show_text] = STATE(20),
    [sym__statement] = STATE(20),
    [sym_if_statement] = STATE(20),
    [aux_sym_source_file_repeat1] = STATE(20),
    [sym_choose_statement] = STATE(20),
    [sym_stat_operation] = STATE(20),
    [sym__endl] = ACTIONS(45),
    [ts_builtin_sym_end] = ACTIONS(47),
    [anon_sym_choose] = ACTIONS(9),
    [sym_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(11),
    [anon_sym_if] = ACTIONS(13),
  },
  [7] = {
    [sym_choice] = STATE(22),
    [aux_sym_choose_statement_repeat1] = STATE(22),
    [sym_comment] = ACTIONS(3),
    [anon_sym_STAR] = ACTIONS(49),
  },
  [8] = {
    [sym_number] = ACTIONS(51),
    [anon_sym_true] = ACTIONS(51),
    [sym_comment] = ACTIONS(29),
    [sym_string] = ACTIONS(51),
    [sym_bare_word] = ACTIONS(51),
    [sym__endl] = ACTIONS(51),
    [anon_sym_false] = ACTIONS(51),
    [anon_sym_LBRACE] = ACTIONS(51),
  },
  [9] = {
    [anon_sym_LBRACK] = ACTIONS(53),
    [sym_text_copy] = ACTIONS(55),
    [sym_comment] = ACTIONS(29),
  },
  [10] = {
    [sym_number] = ACTIONS(57),
    [anon_sym_true] = ACTIONS(59),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(57),
    [anon_sym_false] = ACTIONS(59),
    [anon_sym_LPAREN] = ACTIONS(57),
    [anon_sym_DASH] = ACTIONS(57),
    [sym_identifier] = ACTIONS(59),
    [anon_sym_not] = ACTIONS(59),
  },
  [11] = {
    [sym_number] = ACTIONS(61),
    [anon_sym_true] = ACTIONS(61),
    [sym_comment] = ACTIONS(29),
    [sym_string] = ACTIONS(61),
    [sym_bare_word] = ACTIONS(61),
    [sym__endl] = ACTIONS(61),
    [anon_sym_false] = ACTIONS(61),
    [anon_sym_LBRACE] = ACTIONS(61),
  },
  [12] = {
    [sym__endl] = ACTIONS(63),
    [anon_sym_choose] = ACTIONS(65),
    [ts_builtin_sym_end] = ACTIONS(63),
    [sym_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(65),
    [anon_sym_if] = ACTIONS(65),
  },
  [13] = {
    [sym_boolean] = STATE(25),
    [sym_unary_expression] = STATE(25),
    [sym_binary_expression] = STATE(25),
    [sym__expression] = STATE(25),
    [sym__constant] = STATE(25),
    [sym_paran_expression] = STATE(25),
    [sym_number] = ACTIONS(67),
    [anon_sym_true] = ACTIONS(33),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(67),
    [anon_sym_false] = ACTIONS(33),
    [anon_sym_DASH] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(37),
    [sym_identifier] = ACTIONS(69),
    [anon_sym_not] = ACTIONS(41),
  },
  [14] = {
    [sym_boolean] = STATE(26),
    [sym_unary_expression] = STATE(26),
    [sym_binary_expression] = STATE(26),
    [sym__expression] = STATE(26),
    [sym__constant] = STATE(26),
    [sym_stat_rvalue] = STATE(27),
    [sym_paran_expression] = STATE(26),
    [sym_number] = ACTIONS(71),
    [anon_sym_true] = ACTIONS(73),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(71),
    [anon_sym_false] = ACTIONS(73),
    [anon_sym_DASH] = ACTIONS(75),
    [anon_sym_LPAREN] = ACTIONS(77),
    [sym_identifier] = ACTIONS(79),
    [anon_sym_not] = ACTIONS(81),
  },
  [15] = {
    [sym_boolean] = STATE(11),
    [sym__constant] = STATE(11),
    [sym_command_arg] = STATE(29),
    [aux_sym_command_repeat1] = STATE(29),
    [sym_number] = ACTIONS(17),
    [anon_sym_true] = ACTIONS(19),
    [sym_comment] = ACTIONS(29),
    [sym_bare_word] = ACTIONS(17),
    [sym_string] = ACTIONS(17),
    [anon_sym_false] = ACTIONS(19),
    [sym__endl] = ACTIONS(83),
    [anon_sym_LBRACE] = ACTIONS(27),
  },
  [16] = {
    [sym_unary_expression] = STATE(30),
    [sym_binary_expression] = STATE(30),
    [sym_paran_expression] = STATE(30),
    [sym_boolean] = STATE(30),
    [sym__expression] = STATE(30),
    [sym__constant] = STATE(30),
    [sym_number] = ACTIONS(85),
    [anon_sym_true] = ACTIONS(33),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(85),
    [anon_sym_false] = ACTIONS(33),
    [anon_sym_DASH] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(37),
    [sym_identifier] = ACTIONS(87),
    [anon_sym_not] = ACTIONS(41),
  },
  [17] = {
    [sym_unary_expression] = STATE(31),
    [sym_binary_expression] = STATE(31),
    [sym_paran_expression] = STATE(31),
    [sym_boolean] = STATE(31),
    [sym__expression] = STATE(31),
    [sym__constant] = STATE(31),
    [sym_number] = ACTIONS(89),
    [anon_sym_true] = ACTIONS(33),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(89),
    [anon_sym_false] = ACTIONS(33),
    [anon_sym_DASH] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(37),
    [sym_identifier] = ACTIONS(91),
    [anon_sym_not] = ACTIONS(41),
  },
  [18] = {
    [anon_sym_LT] = ACTIONS(93),
    [anon_sym_and] = ACTIONS(95),
    [anon_sym_LT_EQ] = ACTIONS(97),
    [anon_sym_SLASH] = ACTIONS(99),
    [sym_comment] = ACTIONS(3),
    [anon_sym_GT] = ACTIONS(93),
    [anon_sym_or] = ACTIONS(101),
    [anon_sym_PLUS] = ACTIONS(103),
    [anon_sym_EQ] = ACTIONS(97),
    [sym__endl] = ACTIONS(105),
    [anon_sym_GT_EQ] = ACTIONS(97),
    [anon_sym_DASH] = ACTIONS(103),
    [anon_sym_BANG_EQ] = ACTIONS(97),
    [anon_sym_STAR] = ACTIONS(99),
  },
  [19] = {
    [sym_if_clause] = STATE(38),
    [sym_block] = STATE(39),
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(107),
  },
  [20] = {
    [sym_command] = STATE(20),
    [sym_show_text] = STATE(20),
    [sym__statement] = STATE(20),
    [sym_if_statement] = STATE(20),
    [aux_sym_source_file_repeat1] = STATE(20),
    [sym_choose_statement] = STATE(20),
    [sym_stat_operation] = STATE(20),
    [sym__endl] = ACTIONS(109),
    [anon_sym_choose] = ACTIONS(112),
    [ts_builtin_sym_end] = ACTIONS(115),
    [sym_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(117),
    [anon_sym_if] = ACTIONS(120),
  },
  [21] = {
    [anon_sym_LBRACK] = ACTIONS(123),
    [sym_text_copy] = ACTIONS(125),
    [sym_comment] = ACTIONS(29),
  },
  [22] = {
    [sym_choice] = STATE(43),
    [aux_sym_choose_statement_repeat1] = STATE(43),
    [anon_sym_STAR] = ACTIONS(49),
    [sym_comment] = ACTIONS(3),
    [anon_sym_end] = ACTIONS(127),
  },
  [23] = {
    [sym_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(129),
  },
  [24] = {
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(131),
  },
  [25] = {
    [anon_sym_LT] = ACTIONS(93),
    [anon_sym_and] = ACTIONS(95),
    [anon_sym_RBRACE] = ACTIONS(133),
    [anon_sym_SLASH] = ACTIONS(99),
    [anon_sym_LT_EQ] = ACTIONS(97),
    [anon_sym_GT] = ACTIONS(93),
    [anon_sym_or] = ACTIONS(101),
    [anon_sym_PLUS] = ACTIONS(103),
    [anon_sym_EQ] = ACTIONS(97),
    [sym_comment] = ACTIONS(3),
    [anon_sym_GT_EQ] = ACTIONS(97),
    [anon_sym_DASH] = ACTIONS(103),
    [anon_sym_BANG_EQ] = ACTIONS(97),
    [anon_sym_STAR] = ACTIONS(99),
  },
  [26] = {
    [anon_sym_LT] = ACTIONS(135),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(137),
    [anon_sym_GT_EQ] = ACTIONS(139),
    [anon_sym_DASH] = ACTIONS(141),
    [anon_sym_if] = ACTIONS(143),
    [anon_sym_STAR] = ACTIONS(145),
    [anon_sym_and] = ACTIONS(147),
    [ts_builtin_sym_end] = ACTIONS(149),
    [anon_sym_SLASH] = ACTIONS(145),
    [anon_sym_GT] = ACTIONS(135),
    [anon_sym_PLUS] = ACTIONS(141),
    [anon_sym_EQ] = ACTIONS(139),
    [sym__endl] = ACTIONS(149),
    [anon_sym_choose] = ACTIONS(143),
    [anon_sym_BANG_EQ] = ACTIONS(139),
    [sym_identifier] = ACTIONS(143),
    [anon_sym_LT_EQ] = ACTIONS(139),
  },
  [27] = {
    [sym__endl] = ACTIONS(151),
    [anon_sym_choose] = ACTIONS(153),
    [ts_builtin_sym_end] = ACTIONS(151),
    [sym_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(153),
    [anon_sym_if] = ACTIONS(153),
  },
  [28] = {
    [sym__endl] = ACTIONS(155),
    [anon_sym_choose] = ACTIONS(157),
    [ts_builtin_sym_end] = ACTIONS(155),
    [sym_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(157),
    [anon_sym_if] = ACTIONS(157),
  },
  [29] = {
    [sym_boolean] = STATE(11),
    [sym__constant] = STATE(11),
    [sym_command_arg] = STATE(29),
    [aux_sym_command_repeat1] = STATE(29),
    [sym_number] = ACTIONS(159),
    [anon_sym_true] = ACTIONS(162),
    [sym_comment] = ACTIONS(29),
    [sym_string] = ACTIONS(159),
    [sym_bare_word] = ACTIONS(159),
    [sym__endl] = ACTIONS(165),
    [anon_sym_false] = ACTIONS(162),
    [anon_sym_LBRACE] = ACTIONS(167),
  },
  [30] = {
    [anon_sym_LT] = ACTIONS(170),
    [anon_sym_RBRACK] = ACTIONS(172),
    [anon_sym_RBRACE] = ACTIONS(172),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(172),
    [anon_sym_RPAREN] = ACTIONS(172),
    [anon_sym_GT_EQ] = ACTIONS(172),
    [anon_sym_DASH] = ACTIONS(172),
    [anon_sym_STAR] = ACTIONS(172),
    [anon_sym_and] = ACTIONS(172),
    [anon_sym_SLASH] = ACTIONS(172),
    [anon_sym_GT] = ACTIONS(170),
    [anon_sym_PLUS] = ACTIONS(172),
    [anon_sym_EQ] = ACTIONS(172),
    [sym__endl] = ACTIONS(172),
    [anon_sym_BANG_EQ] = ACTIONS(172),
    [anon_sym_LT_EQ] = ACTIONS(172),
  },
  [31] = {
    [anon_sym_LT] = ACTIONS(93),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(101),
    [anon_sym_RPAREN] = ACTIONS(174),
    [anon_sym_GT_EQ] = ACTIONS(97),
    [anon_sym_DASH] = ACTIONS(103),
    [anon_sym_STAR] = ACTIONS(99),
    [anon_sym_and] = ACTIONS(95),
    [anon_sym_SLASH] = ACTIONS(99),
    [anon_sym_GT] = ACTIONS(93),
    [anon_sym_PLUS] = ACTIONS(103),
    [anon_sym_EQ] = ACTIONS(97),
    [anon_sym_BANG_EQ] = ACTIONS(97),
    [anon_sym_LT_EQ] = ACTIONS(97),
  },
  [32] = {
    [sym_unary_expression] = STATE(48),
    [sym_binary_expression] = STATE(48),
    [sym_paran_expression] = STATE(48),
    [sym_boolean] = STATE(48),
    [sym__expression] = STATE(48),
    [sym__constant] = STATE(48),
    [sym_number] = ACTIONS(176),
    [anon_sym_true] = ACTIONS(33),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(176),
    [anon_sym_false] = ACTIONS(33),
    [anon_sym_DASH] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(37),
    [sym_identifier] = ACTIONS(178),
    [anon_sym_not] = ACTIONS(41),
  },
  [33] = {
    [sym_unary_expression] = STATE(49),
    [sym_binary_expression] = STATE(49),
    [sym_paran_expression] = STATE(49),
    [sym_boolean] = STATE(49),
    [sym__expression] = STATE(49),
    [sym__constant] = STATE(49),
    [sym_number] = ACTIONS(180),
    [anon_sym_true] = ACTIONS(33),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(180),
    [anon_sym_false] = ACTIONS(33),
    [anon_sym_DASH] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(37),
    [sym_identifier] = ACTIONS(182),
    [anon_sym_not] = ACTIONS(41),
  },
  [34] = {
    [sym_unary_expression] = STATE(50),
    [sym_binary_expression] = STATE(50),
    [sym_paran_expression] = STATE(50),
    [sym_boolean] = STATE(50),
    [sym__expression] = STATE(50),
    [sym__constant] = STATE(50),
    [sym_number] = ACTIONS(184),
    [anon_sym_true] = ACTIONS(33),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(184),
    [anon_sym_false] = ACTIONS(33),
    [anon_sym_DASH] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(37),
    [sym_identifier] = ACTIONS(186),
    [anon_sym_not] = ACTIONS(41),
  },
  [35] = {
    [sym_unary_expression] = STATE(51),
    [sym_binary_expression] = STATE(51),
    [sym_paran_expression] = STATE(51),
    [sym_boolean] = STATE(51),
    [sym__expression] = STATE(51),
    [sym__constant] = STATE(51),
    [sym_number] = ACTIONS(188),
    [anon_sym_true] = ACTIONS(33),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(188),
    [anon_sym_false] = ACTIONS(33),
    [anon_sym_DASH] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(37),
    [sym_identifier] = ACTIONS(190),
    [anon_sym_not] = ACTIONS(41),
  },
  [36] = {
    [sym_unary_expression] = STATE(52),
    [sym_binary_expression] = STATE(52),
    [sym_paran_expression] = STATE(52),
    [sym_boolean] = STATE(52),
    [sym__expression] = STATE(52),
    [sym__constant] = STATE(52),
    [sym_number] = ACTIONS(192),
    [anon_sym_true] = ACTIONS(33),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(192),
    [anon_sym_false] = ACTIONS(33),
    [anon_sym_DASH] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(37),
    [sym_identifier] = ACTIONS(194),
    [anon_sym_not] = ACTIONS(41),
  },
  [37] = {
    [sym_command] = STATE(53),
    [sym_show_text] = STATE(53),
    [sym__statement] = STATE(53),
    [sym_if_statement] = STATE(53),
    [aux_sym_source_file_repeat1] = STATE(53),
    [sym_choose_statement] = STATE(53),
    [sym_stat_operation] = STATE(53),
    [anon_sym_elseif] = ACTIONS(196),
    [anon_sym_end] = ACTIONS(196),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(196),
    [sym__endl] = ACTIONS(198),
    [anon_sym_choose] = ACTIONS(200),
    [sym_identifier] = ACTIONS(202),
    [anon_sym_if] = ACTIONS(204),
  },
  [38] = {
    [sym_else_clause] = STATE(57),
    [aux_sym_if_statement_repeat1] = STATE(58),
    [sym_elseif_clause] = STATE(58),
    [anon_sym_elseif] = ACTIONS(206),
    [anon_sym_end] = ACTIONS(208),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(210),
  },
  [39] = {
    [anon_sym_elseif] = ACTIONS(212),
    [anon_sym_end] = ACTIONS(212),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(214),
  },
  [40] = {
    [sym_boolean] = STATE(59),
    [sym_unary_expression] = STATE(59),
    [sym_binary_expression] = STATE(59),
    [sym__expression] = STATE(59),
    [sym__constant] = STATE(59),
    [sym_choice_condition] = STATE(60),
    [sym_paran_expression] = STATE(59),
    [sym_number] = ACTIONS(216),
    [anon_sym_true] = ACTIONS(33),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(216),
    [anon_sym_false] = ACTIONS(33),
    [anon_sym_DASH] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(37),
    [sym_identifier] = ACTIONS(218),
    [anon_sym_not] = ACTIONS(41),
  },
  [41] = {
    [sym_block] = STATE(61),
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(220),
  },
  [42] = {
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(222),
  },
  [43] = {
    [sym_choice] = STATE(43),
    [aux_sym_choose_statement_repeat1] = STATE(43),
    [anon_sym_STAR] = ACTIONS(224),
    [sym_comment] = ACTIONS(3),
    [anon_sym_end] = ACTIONS(227),
  },
  [44] = {
    [sym_comment] = ACTIONS(3),
    [anon_sym_RBRACK] = ACTIONS(229),
  },
  [45] = {
    [sym__endl] = ACTIONS(231),
    [anon_sym_choose] = ACTIONS(233),
    [ts_builtin_sym_end] = ACTIONS(231),
    [sym_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(233),
    [anon_sym_if] = ACTIONS(233),
  },
  [46] = {
    [sym_number] = ACTIONS(235),
    [anon_sym_true] = ACTIONS(235),
    [sym_comment] = ACTIONS(29),
    [sym_string] = ACTIONS(235),
    [sym_bare_word] = ACTIONS(235),
    [sym__endl] = ACTIONS(235),
    [anon_sym_false] = ACTIONS(235),
    [anon_sym_LBRACE] = ACTIONS(235),
  },
  [47] = {
    [anon_sym_LT] = ACTIONS(237),
    [anon_sym_RBRACK] = ACTIONS(239),
    [anon_sym_RBRACE] = ACTIONS(239),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(239),
    [anon_sym_RPAREN] = ACTIONS(239),
    [anon_sym_GT_EQ] = ACTIONS(239),
    [anon_sym_DASH] = ACTIONS(239),
    [anon_sym_STAR] = ACTIONS(239),
    [anon_sym_and] = ACTIONS(239),
    [anon_sym_SLASH] = ACTIONS(239),
    [anon_sym_GT] = ACTIONS(237),
    [anon_sym_PLUS] = ACTIONS(239),
    [anon_sym_EQ] = ACTIONS(239),
    [sym__endl] = ACTIONS(239),
    [anon_sym_BANG_EQ] = ACTIONS(239),
    [anon_sym_LT_EQ] = ACTIONS(239),
  },
  [48] = {
    [anon_sym_LT] = ACTIONS(241),
    [anon_sym_RBRACK] = ACTIONS(243),
    [anon_sym_RBRACE] = ACTIONS(243),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(243),
    [anon_sym_RPAREN] = ACTIONS(243),
    [anon_sym_GT_EQ] = ACTIONS(243),
    [anon_sym_DASH] = ACTIONS(103),
    [anon_sym_STAR] = ACTIONS(99),
    [anon_sym_and] = ACTIONS(243),
    [anon_sym_SLASH] = ACTIONS(99),
    [anon_sym_GT] = ACTIONS(241),
    [anon_sym_PLUS] = ACTIONS(103),
    [anon_sym_EQ] = ACTIONS(243),
    [sym__endl] = ACTIONS(243),
    [anon_sym_BANG_EQ] = ACTIONS(243),
    [anon_sym_LT_EQ] = ACTIONS(243),
  },
  [49] = {
    [anon_sym_LT] = ACTIONS(93),
    [anon_sym_RBRACK] = ACTIONS(243),
    [anon_sym_RBRACE] = ACTIONS(243),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(243),
    [anon_sym_RPAREN] = ACTIONS(243),
    [anon_sym_GT_EQ] = ACTIONS(97),
    [anon_sym_DASH] = ACTIONS(103),
    [anon_sym_STAR] = ACTIONS(99),
    [anon_sym_and] = ACTIONS(243),
    [anon_sym_SLASH] = ACTIONS(99),
    [anon_sym_GT] = ACTIONS(93),
    [anon_sym_PLUS] = ACTIONS(103),
    [anon_sym_EQ] = ACTIONS(97),
    [sym__endl] = ACTIONS(243),
    [anon_sym_BANG_EQ] = ACTIONS(97),
    [anon_sym_LT_EQ] = ACTIONS(97),
  },
  [50] = {
    [anon_sym_LT] = ACTIONS(241),
    [anon_sym_RBRACK] = ACTIONS(243),
    [anon_sym_RBRACE] = ACTIONS(243),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(243),
    [anon_sym_RPAREN] = ACTIONS(243),
    [anon_sym_GT_EQ] = ACTIONS(243),
    [anon_sym_DASH] = ACTIONS(243),
    [anon_sym_STAR] = ACTIONS(243),
    [anon_sym_and] = ACTIONS(243),
    [anon_sym_SLASH] = ACTIONS(243),
    [anon_sym_GT] = ACTIONS(241),
    [anon_sym_PLUS] = ACTIONS(243),
    [anon_sym_EQ] = ACTIONS(243),
    [sym__endl] = ACTIONS(243),
    [anon_sym_BANG_EQ] = ACTIONS(243),
    [anon_sym_LT_EQ] = ACTIONS(243),
  },
  [51] = {
    [anon_sym_LT] = ACTIONS(93),
    [anon_sym_RBRACK] = ACTIONS(243),
    [anon_sym_RBRACE] = ACTIONS(243),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(243),
    [anon_sym_RPAREN] = ACTIONS(243),
    [anon_sym_GT_EQ] = ACTIONS(97),
    [anon_sym_DASH] = ACTIONS(103),
    [anon_sym_STAR] = ACTIONS(99),
    [anon_sym_and] = ACTIONS(95),
    [anon_sym_SLASH] = ACTIONS(99),
    [anon_sym_GT] = ACTIONS(93),
    [anon_sym_PLUS] = ACTIONS(103),
    [anon_sym_EQ] = ACTIONS(97),
    [sym__endl] = ACTIONS(243),
    [anon_sym_BANG_EQ] = ACTIONS(97),
    [anon_sym_LT_EQ] = ACTIONS(97),
  },
  [52] = {
    [anon_sym_LT] = ACTIONS(241),
    [anon_sym_RBRACK] = ACTIONS(243),
    [anon_sym_RBRACE] = ACTIONS(243),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(243),
    [anon_sym_RPAREN] = ACTIONS(243),
    [anon_sym_GT_EQ] = ACTIONS(243),
    [anon_sym_DASH] = ACTIONS(243),
    [anon_sym_STAR] = ACTIONS(99),
    [anon_sym_and] = ACTIONS(243),
    [anon_sym_SLASH] = ACTIONS(99),
    [anon_sym_GT] = ACTIONS(241),
    [anon_sym_PLUS] = ACTIONS(243),
    [anon_sym_EQ] = ACTIONS(243),
    [sym__endl] = ACTIONS(243),
    [anon_sym_BANG_EQ] = ACTIONS(243),
    [anon_sym_LT_EQ] = ACTIONS(243),
  },
  [53] = {
    [sym_command] = STATE(81),
    [sym_show_text] = STATE(81),
    [sym__statement] = STATE(81),
    [sym_if_statement] = STATE(81),
    [aux_sym_source_file_repeat1] = STATE(81),
    [sym_choose_statement] = STATE(81),
    [sym_stat_operation] = STATE(81),
    [anon_sym_elseif] = ACTIONS(245),
    [anon_sym_end] = ACTIONS(245),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(245),
    [sym__endl] = ACTIONS(247),
    [anon_sym_choose] = ACTIONS(200),
    [sym_identifier] = ACTIONS(202),
    [anon_sym_if] = ACTIONS(204),
  },
  [54] = {
    [sym_boolean] = STATE(18),
    [sym_unary_expression] = STATE(18),
    [sym_binary_expression] = STATE(18),
    [sym__expression] = STATE(18),
    [sym__constant] = STATE(18),
    [sym_condition] = STATE(64),
    [sym_paran_expression] = STATE(18),
    [sym_number] = ACTIONS(31),
    [anon_sym_true] = ACTIONS(33),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(31),
    [anon_sym_false] = ACTIONS(33),
    [anon_sym_DASH] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(37),
    [sym_identifier] = ACTIONS(39),
    [anon_sym_not] = ACTIONS(41),
  },
  [55] = {
    [sym_block] = STATE(65),
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(220),
  },
  [56] = {
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(249),
  },
  [57] = {
    [sym_comment] = ACTIONS(3),
    [anon_sym_end] = ACTIONS(251),
  },
  [58] = {
    [sym_else_clause] = STATE(68),
    [aux_sym_if_statement_repeat1] = STATE(69),
    [sym_elseif_clause] = STATE(69),
    [anon_sym_elseif] = ACTIONS(206),
    [anon_sym_end] = ACTIONS(251),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(210),
  },
  [59] = {
    [anon_sym_LT] = ACTIONS(93),
    [anon_sym_RBRACK] = ACTIONS(253),
    [anon_sym_and] = ACTIONS(95),
    [anon_sym_SLASH] = ACTIONS(99),
    [anon_sym_LT_EQ] = ACTIONS(97),
    [anon_sym_GT] = ACTIONS(93),
    [anon_sym_or] = ACTIONS(101),
    [anon_sym_PLUS] = ACTIONS(103),
    [anon_sym_EQ] = ACTIONS(97),
    [sym_comment] = ACTIONS(3),
    [anon_sym_GT_EQ] = ACTIONS(97),
    [anon_sym_DASH] = ACTIONS(103),
    [anon_sym_BANG_EQ] = ACTIONS(97),
    [anon_sym_STAR] = ACTIONS(99),
  },
  [60] = {
    [sym_comment] = ACTIONS(3),
    [anon_sym_RBRACK] = ACTIONS(255),
  },
  [61] = {
    [anon_sym_STAR] = ACTIONS(257),
    [sym_comment] = ACTIONS(3),
    [anon_sym_end] = ACTIONS(257),
  },
  [62] = {
    [sym__endl] = ACTIONS(259),
    [anon_sym_choose] = ACTIONS(261),
    [ts_builtin_sym_end] = ACTIONS(259),
    [sym_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(261),
    [anon_sym_if] = ACTIONS(261),
  },
  [63] = {
    [sym_comment] = ACTIONS(29),
    [sym_text_copy] = ACTIONS(263),
  },
  [64] = {
    [sym_block] = STATE(72),
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(107),
  },
  [65] = {
    [sym_comment] = ACTIONS(3),
    [anon_sym_end] = ACTIONS(265),
  },
  [66] = {
    [sym__endl] = ACTIONS(267),
    [anon_sym_choose] = ACTIONS(269),
    [ts_builtin_sym_end] = ACTIONS(267),
    [sym_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(269),
    [anon_sym_if] = ACTIONS(269),
  },
  [67] = {
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(271),
  },
  [68] = {
    [sym_comment] = ACTIONS(3),
    [anon_sym_end] = ACTIONS(273),
  },
  [69] = {
    [aux_sym_if_statement_repeat1] = STATE(69),
    [sym_elseif_clause] = STATE(69),
    [anon_sym_elseif] = ACTIONS(275),
    [anon_sym_end] = ACTIONS(278),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(280),
  },
  [70] = {
    [sym_comment] = ACTIONS(29),
    [sym_text_copy] = ACTIONS(282),
  },
  [71] = {
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(284),
  },
  [72] = {
    [anon_sym_elseif] = ACTIONS(286),
    [anon_sym_end] = ACTIONS(286),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(288),
  },
  [73] = {
    [sym__endl] = ACTIONS(290),
    [anon_sym_choose] = ACTIONS(292),
    [ts_builtin_sym_end] = ACTIONS(290),
    [sym_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(292),
    [anon_sym_if] = ACTIONS(292),
  },
  [74] = {
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(294),
  },
  [75] = {
    [sym_block] = STATE(78),
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(220),
  },
  [76] = {
    [sym__endl] = ACTIONS(296),
    [anon_sym_choose] = ACTIONS(298),
    [ts_builtin_sym_end] = ACTIONS(296),
    [sym_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(298),
    [anon_sym_if] = ACTIONS(298),
  },
  [77] = {
    [sym__endl] = ACTIONS(300),
    [anon_sym_choose] = ACTIONS(302),
    [ts_builtin_sym_end] = ACTIONS(300),
    [sym_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(302),
    [anon_sym_if] = ACTIONS(302),
  },
  [78] = {
    [anon_sym_STAR] = ACTIONS(304),
    [sym_comment] = ACTIONS(3),
    [anon_sym_end] = ACTIONS(304),
  },
  [79] = {
    [anon_sym_LT] = ACTIONS(51),
    [anon_sym_RBRACK] = ACTIONS(306),
    [anon_sym_RBRACE] = ACTIONS(306),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(306),
    [anon_sym_RPAREN] = ACTIONS(306),
    [anon_sym_GT_EQ] = ACTIONS(306),
    [anon_sym_DASH] = ACTIONS(306),
    [anon_sym_STAR] = ACTIONS(306),
    [anon_sym_and] = ACTIONS(306),
    [anon_sym_SLASH] = ACTIONS(306),
    [anon_sym_GT] = ACTIONS(51),
    [anon_sym_PLUS] = ACTIONS(306),
    [anon_sym_EQ] = ACTIONS(306),
    [sym__endl] = ACTIONS(306),
    [anon_sym_BANG_EQ] = ACTIONS(306),
    [anon_sym_LT_EQ] = ACTIONS(306),
  },
  [80] = {
    [anon_sym_elseif] = ACTIONS(65),
    [anon_sym_end] = ACTIONS(65),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(65),
    [sym__endl] = ACTIONS(63),
    [anon_sym_choose] = ACTIONS(65),
    [sym_identifier] = ACTIONS(65),
    [anon_sym_if] = ACTIONS(65),
  },
  [81] = {
    [sym_command] = STATE(81),
    [sym_show_text] = STATE(81),
    [sym__statement] = STATE(81),
    [sym_if_statement] = STATE(81),
    [aux_sym_source_file_repeat1] = STATE(81),
    [sym_choose_statement] = STATE(81),
    [sym_stat_operation] = STATE(81),
    [anon_sym_elseif] = ACTIONS(308),
    [anon_sym_end] = ACTIONS(308),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(308),
    [sym__endl] = ACTIONS(310),
    [anon_sym_choose] = ACTIONS(313),
    [sym_identifier] = ACTIONS(316),
    [anon_sym_if] = ACTIONS(319),
  },
  [82] = {
    [anon_sym_LT] = ACTIONS(322),
    [anon_sym_end] = ACTIONS(143),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(143),
    [anon_sym_or] = ACTIONS(324),
    [anon_sym_GT_EQ] = ACTIONS(326),
    [anon_sym_DASH] = ACTIONS(328),
    [anon_sym_if] = ACTIONS(143),
    [anon_sym_STAR] = ACTIONS(330),
    [anon_sym_elseif] = ACTIONS(143),
    [anon_sym_and] = ACTIONS(332),
    [anon_sym_SLASH] = ACTIONS(330),
    [anon_sym_GT] = ACTIONS(322),
    [anon_sym_PLUS] = ACTIONS(328),
    [anon_sym_EQ] = ACTIONS(326),
    [sym__endl] = ACTIONS(149),
    [anon_sym_choose] = ACTIONS(143),
    [anon_sym_BANG_EQ] = ACTIONS(326),
    [sym_identifier] = ACTIONS(143),
    [anon_sym_LT_EQ] = ACTIONS(326),
  },
  [83] = {
    [anon_sym_elseif] = ACTIONS(153),
    [anon_sym_end] = ACTIONS(153),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(153),
    [sym__endl] = ACTIONS(151),
    [anon_sym_choose] = ACTIONS(153),
    [sym_identifier] = ACTIONS(153),
    [anon_sym_if] = ACTIONS(153),
  },
  [84] = {
    [anon_sym_elseif] = ACTIONS(157),
    [anon_sym_end] = ACTIONS(157),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(157),
    [sym__endl] = ACTIONS(155),
    [anon_sym_choose] = ACTIONS(157),
    [sym_identifier] = ACTIONS(157),
    [anon_sym_if] = ACTIONS(157),
  },
  [85] = {
    [anon_sym_LT] = ACTIONS(170),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(170),
    [anon_sym_GT_EQ] = ACTIONS(172),
    [anon_sym_DASH] = ACTIONS(172),
    [anon_sym_if] = ACTIONS(170),
    [anon_sym_STAR] = ACTIONS(172),
    [anon_sym_and] = ACTIONS(170),
    [ts_builtin_sym_end] = ACTIONS(172),
    [anon_sym_SLASH] = ACTIONS(172),
    [anon_sym_GT] = ACTIONS(170),
    [anon_sym_PLUS] = ACTIONS(172),
    [anon_sym_EQ] = ACTIONS(172),
    [sym__endl] = ACTIONS(172),
    [anon_sym_choose] = ACTIONS(170),
    [anon_sym_BANG_EQ] = ACTIONS(172),
    [sym_identifier] = ACTIONS(170),
    [anon_sym_LT_EQ] = ACTIONS(172),
  },
  [86] = {
    [sym_boolean] = STATE(94),
    [sym_unary_expression] = STATE(94),
    [sym_binary_expression] = STATE(94),
    [sym__expression] = STATE(94),
    [sym__constant] = STATE(94),
    [sym_paran_expression] = STATE(94),
    [sym_number] = ACTIONS(334),
    [anon_sym_true] = ACTIONS(73),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(334),
    [anon_sym_false] = ACTIONS(73),
    [anon_sym_DASH] = ACTIONS(75),
    [anon_sym_LPAREN] = ACTIONS(77),
    [sym_identifier] = ACTIONS(336),
    [anon_sym_not] = ACTIONS(81),
  },
  [87] = {
    [sym_boolean] = STATE(95),
    [sym_unary_expression] = STATE(95),
    [sym_binary_expression] = STATE(95),
    [sym__expression] = STATE(95),
    [sym__constant] = STATE(95),
    [sym_paran_expression] = STATE(95),
    [sym_number] = ACTIONS(338),
    [anon_sym_true] = ACTIONS(73),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(338),
    [anon_sym_false] = ACTIONS(73),
    [anon_sym_DASH] = ACTIONS(75),
    [anon_sym_LPAREN] = ACTIONS(77),
    [sym_identifier] = ACTIONS(340),
    [anon_sym_not] = ACTIONS(81),
  },
  [88] = {
    [sym_boolean] = STATE(96),
    [sym_unary_expression] = STATE(96),
    [sym_binary_expression] = STATE(96),
    [sym__expression] = STATE(96),
    [sym__constant] = STATE(96),
    [sym_paran_expression] = STATE(96),
    [sym_number] = ACTIONS(342),
    [anon_sym_true] = ACTIONS(73),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(342),
    [anon_sym_false] = ACTIONS(73),
    [anon_sym_DASH] = ACTIONS(75),
    [anon_sym_LPAREN] = ACTIONS(77),
    [sym_identifier] = ACTIONS(344),
    [anon_sym_not] = ACTIONS(81),
  },
  [89] = {
    [sym_boolean] = STATE(97),
    [sym_unary_expression] = STATE(97),
    [sym_binary_expression] = STATE(97),
    [sym__expression] = STATE(97),
    [sym__constant] = STATE(97),
    [sym_paran_expression] = STATE(97),
    [sym_number] = ACTIONS(346),
    [anon_sym_true] = ACTIONS(73),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(346),
    [anon_sym_false] = ACTIONS(73),
    [anon_sym_DASH] = ACTIONS(75),
    [anon_sym_LPAREN] = ACTIONS(77),
    [sym_identifier] = ACTIONS(348),
    [anon_sym_not] = ACTIONS(81),
  },
  [90] = {
    [sym_boolean] = STATE(98),
    [sym_unary_expression] = STATE(98),
    [sym_binary_expression] = STATE(98),
    [sym__expression] = STATE(98),
    [sym__constant] = STATE(98),
    [sym_paran_expression] = STATE(98),
    [sym_number] = ACTIONS(350),
    [anon_sym_true] = ACTIONS(73),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(350),
    [anon_sym_false] = ACTIONS(73),
    [anon_sym_DASH] = ACTIONS(75),
    [anon_sym_LPAREN] = ACTIONS(77),
    [sym_identifier] = ACTIONS(352),
    [anon_sym_not] = ACTIONS(81),
  },
  [91] = {
    [sym_command] = STATE(99),
    [sym_stat_operation] = STATE(99),
    [sym_show_text] = STATE(99),
    [sym__statement] = STATE(99),
    [sym_if_statement] = STATE(99),
    [aux_sym_source_file_repeat1] = STATE(99),
    [sym_choose_statement] = STATE(99),
    [anon_sym_end] = ACTIONS(196),
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(354),
    [anon_sym_choose] = ACTIONS(356),
    [sym_identifier] = ACTIONS(358),
    [anon_sym_if] = ACTIONS(360),
    [anon_sym_STAR] = ACTIONS(362),
  },
  [92] = {
    [anon_sym_elseif] = ACTIONS(233),
    [anon_sym_end] = ACTIONS(233),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(233),
    [sym__endl] = ACTIONS(231),
    [anon_sym_choose] = ACTIONS(233),
    [sym_identifier] = ACTIONS(233),
    [anon_sym_if] = ACTIONS(233),
  },
  [93] = {
    [anon_sym_LT] = ACTIONS(237),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(237),
    [anon_sym_GT_EQ] = ACTIONS(239),
    [anon_sym_DASH] = ACTIONS(239),
    [anon_sym_if] = ACTIONS(237),
    [anon_sym_STAR] = ACTIONS(239),
    [anon_sym_and] = ACTIONS(237),
    [ts_builtin_sym_end] = ACTIONS(239),
    [anon_sym_SLASH] = ACTIONS(239),
    [anon_sym_GT] = ACTIONS(237),
    [anon_sym_PLUS] = ACTIONS(239),
    [anon_sym_EQ] = ACTIONS(239),
    [sym__endl] = ACTIONS(239),
    [anon_sym_choose] = ACTIONS(237),
    [anon_sym_BANG_EQ] = ACTIONS(239),
    [sym_identifier] = ACTIONS(237),
    [anon_sym_LT_EQ] = ACTIONS(239),
  },
  [94] = {
    [anon_sym_LT] = ACTIONS(241),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(241),
    [anon_sym_GT_EQ] = ACTIONS(243),
    [anon_sym_DASH] = ACTIONS(141),
    [anon_sym_if] = ACTIONS(241),
    [anon_sym_STAR] = ACTIONS(145),
    [anon_sym_and] = ACTIONS(241),
    [ts_builtin_sym_end] = ACTIONS(243),
    [anon_sym_SLASH] = ACTIONS(145),
    [anon_sym_GT] = ACTIONS(241),
    [anon_sym_PLUS] = ACTIONS(141),
    [anon_sym_EQ] = ACTIONS(243),
    [sym__endl] = ACTIONS(243),
    [anon_sym_choose] = ACTIONS(241),
    [anon_sym_BANG_EQ] = ACTIONS(243),
    [sym_identifier] = ACTIONS(241),
    [anon_sym_LT_EQ] = ACTIONS(243),
  },
  [95] = {
    [anon_sym_LT] = ACTIONS(135),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(241),
    [anon_sym_GT_EQ] = ACTIONS(139),
    [anon_sym_DASH] = ACTIONS(141),
    [anon_sym_if] = ACTIONS(241),
    [anon_sym_STAR] = ACTIONS(145),
    [anon_sym_and] = ACTIONS(241),
    [ts_builtin_sym_end] = ACTIONS(243),
    [anon_sym_SLASH] = ACTIONS(145),
    [anon_sym_GT] = ACTIONS(135),
    [anon_sym_PLUS] = ACTIONS(141),
    [anon_sym_EQ] = ACTIONS(139),
    [sym__endl] = ACTIONS(243),
    [anon_sym_choose] = ACTIONS(241),
    [anon_sym_BANG_EQ] = ACTIONS(139),
    [sym_identifier] = ACTIONS(241),
    [anon_sym_LT_EQ] = ACTIONS(139),
  },
  [96] = {
    [anon_sym_LT] = ACTIONS(241),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(241),
    [anon_sym_GT_EQ] = ACTIONS(243),
    [anon_sym_DASH] = ACTIONS(243),
    [anon_sym_if] = ACTIONS(241),
    [anon_sym_STAR] = ACTIONS(243),
    [anon_sym_and] = ACTIONS(241),
    [ts_builtin_sym_end] = ACTIONS(243),
    [anon_sym_SLASH] = ACTIONS(243),
    [anon_sym_GT] = ACTIONS(241),
    [anon_sym_PLUS] = ACTIONS(243),
    [anon_sym_EQ] = ACTIONS(243),
    [sym__endl] = ACTIONS(243),
    [anon_sym_choose] = ACTIONS(241),
    [anon_sym_BANG_EQ] = ACTIONS(243),
    [sym_identifier] = ACTIONS(241),
    [anon_sym_LT_EQ] = ACTIONS(243),
  },
  [97] = {
    [anon_sym_LT] = ACTIONS(135),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(241),
    [anon_sym_GT_EQ] = ACTIONS(139),
    [anon_sym_DASH] = ACTIONS(141),
    [anon_sym_if] = ACTIONS(241),
    [anon_sym_STAR] = ACTIONS(145),
    [anon_sym_and] = ACTIONS(147),
    [ts_builtin_sym_end] = ACTIONS(243),
    [anon_sym_SLASH] = ACTIONS(145),
    [anon_sym_GT] = ACTIONS(135),
    [anon_sym_PLUS] = ACTIONS(141),
    [anon_sym_EQ] = ACTIONS(139),
    [sym__endl] = ACTIONS(243),
    [anon_sym_choose] = ACTIONS(241),
    [anon_sym_BANG_EQ] = ACTIONS(139),
    [sym_identifier] = ACTIONS(241),
    [anon_sym_LT_EQ] = ACTIONS(139),
  },
  [98] = {
    [anon_sym_LT] = ACTIONS(241),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(241),
    [anon_sym_GT_EQ] = ACTIONS(243),
    [anon_sym_DASH] = ACTIONS(243),
    [anon_sym_if] = ACTIONS(241),
    [anon_sym_STAR] = ACTIONS(145),
    [anon_sym_and] = ACTIONS(241),
    [ts_builtin_sym_end] = ACTIONS(243),
    [anon_sym_SLASH] = ACTIONS(145),
    [anon_sym_GT] = ACTIONS(241),
    [anon_sym_PLUS] = ACTIONS(243),
    [anon_sym_EQ] = ACTIONS(243),
    [sym__endl] = ACTIONS(243),
    [anon_sym_choose] = ACTIONS(241),
    [anon_sym_BANG_EQ] = ACTIONS(243),
    [sym_identifier] = ACTIONS(241),
    [anon_sym_LT_EQ] = ACTIONS(243),
  },
  [99] = {
    [sym_command] = STATE(107),
    [sym_stat_operation] = STATE(107),
    [sym_show_text] = STATE(107),
    [sym__statement] = STATE(107),
    [sym_if_statement] = STATE(107),
    [aux_sym_source_file_repeat1] = STATE(107),
    [sym_choose_statement] = STATE(107),
    [anon_sym_end] = ACTIONS(245),
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(364),
    [anon_sym_choose] = ACTIONS(356),
    [sym_identifier] = ACTIONS(358),
    [anon_sym_if] = ACTIONS(360),
    [anon_sym_STAR] = ACTIONS(366),
  },
  [100] = {
    [anon_sym_elseif] = ACTIONS(261),
    [anon_sym_end] = ACTIONS(261),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(261),
    [sym__endl] = ACTIONS(259),
    [anon_sym_choose] = ACTIONS(261),
    [sym_identifier] = ACTIONS(261),
    [anon_sym_if] = ACTIONS(261),
  },
  [101] = {
    [anon_sym_elseif] = ACTIONS(269),
    [anon_sym_end] = ACTIONS(269),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(269),
    [sym__endl] = ACTIONS(267),
    [anon_sym_choose] = ACTIONS(269),
    [sym_identifier] = ACTIONS(269),
    [anon_sym_if] = ACTIONS(269),
  },
  [102] = {
    [anon_sym_elseif] = ACTIONS(292),
    [anon_sym_end] = ACTIONS(292),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(292),
    [sym__endl] = ACTIONS(290),
    [anon_sym_choose] = ACTIONS(292),
    [sym_identifier] = ACTIONS(292),
    [anon_sym_if] = ACTIONS(292),
  },
  [103] = {
    [anon_sym_elseif] = ACTIONS(298),
    [anon_sym_end] = ACTIONS(298),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(298),
    [sym__endl] = ACTIONS(296),
    [anon_sym_choose] = ACTIONS(298),
    [sym_identifier] = ACTIONS(298),
    [anon_sym_if] = ACTIONS(298),
  },
  [104] = {
    [anon_sym_elseif] = ACTIONS(302),
    [anon_sym_end] = ACTIONS(302),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(302),
    [sym__endl] = ACTIONS(300),
    [anon_sym_choose] = ACTIONS(302),
    [sym_identifier] = ACTIONS(302),
    [anon_sym_if] = ACTIONS(302),
  },
  [105] = {
    [anon_sym_LT] = ACTIONS(51),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(51),
    [anon_sym_GT_EQ] = ACTIONS(306),
    [anon_sym_DASH] = ACTIONS(306),
    [anon_sym_if] = ACTIONS(51),
    [anon_sym_STAR] = ACTIONS(306),
    [anon_sym_and] = ACTIONS(51),
    [ts_builtin_sym_end] = ACTIONS(306),
    [anon_sym_SLASH] = ACTIONS(306),
    [anon_sym_GT] = ACTIONS(51),
    [anon_sym_PLUS] = ACTIONS(306),
    [anon_sym_EQ] = ACTIONS(306),
    [sym__endl] = ACTIONS(306),
    [anon_sym_choose] = ACTIONS(51),
    [anon_sym_BANG_EQ] = ACTIONS(306),
    [sym_identifier] = ACTIONS(51),
    [anon_sym_LT_EQ] = ACTIONS(306),
  },
  [106] = {
    [anon_sym_end] = ACTIONS(65),
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(63),
    [anon_sym_choose] = ACTIONS(65),
    [sym_identifier] = ACTIONS(65),
    [anon_sym_if] = ACTIONS(65),
    [anon_sym_STAR] = ACTIONS(63),
  },
  [107] = {
    [sym_command] = STATE(107),
    [sym_stat_operation] = STATE(107),
    [sym_show_text] = STATE(107),
    [sym__statement] = STATE(107),
    [sym_if_statement] = STATE(107),
    [aux_sym_source_file_repeat1] = STATE(107),
    [sym_choose_statement] = STATE(107),
    [anon_sym_end] = ACTIONS(308),
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(368),
    [anon_sym_choose] = ACTIONS(371),
    [sym_identifier] = ACTIONS(374),
    [anon_sym_if] = ACTIONS(377),
    [anon_sym_STAR] = ACTIONS(115),
  },
  [108] = {
    [anon_sym_LT] = ACTIONS(380),
    [anon_sym_end] = ACTIONS(143),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(382),
    [anon_sym_GT_EQ] = ACTIONS(384),
    [anon_sym_DASH] = ACTIONS(386),
    [anon_sym_if] = ACTIONS(143),
    [anon_sym_STAR] = ACTIONS(388),
    [anon_sym_and] = ACTIONS(390),
    [anon_sym_SLASH] = ACTIONS(388),
    [anon_sym_GT] = ACTIONS(380),
    [anon_sym_PLUS] = ACTIONS(386),
    [anon_sym_EQ] = ACTIONS(384),
    [sym__endl] = ACTIONS(149),
    [anon_sym_choose] = ACTIONS(143),
    [anon_sym_BANG_EQ] = ACTIONS(384),
    [sym_identifier] = ACTIONS(143),
    [anon_sym_LT_EQ] = ACTIONS(384),
  },
  [109] = {
    [anon_sym_end] = ACTIONS(153),
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(151),
    [anon_sym_choose] = ACTIONS(153),
    [sym_identifier] = ACTIONS(153),
    [anon_sym_if] = ACTIONS(153),
    [anon_sym_STAR] = ACTIONS(151),
  },
  [110] = {
    [anon_sym_end] = ACTIONS(157),
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(155),
    [anon_sym_choose] = ACTIONS(157),
    [sym_identifier] = ACTIONS(157),
    [anon_sym_if] = ACTIONS(157),
    [anon_sym_STAR] = ACTIONS(155),
  },
  [111] = {
    [anon_sym_LT] = ACTIONS(170),
    [anon_sym_end] = ACTIONS(170),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(170),
    [anon_sym_or] = ACTIONS(170),
    [anon_sym_GT_EQ] = ACTIONS(172),
    [anon_sym_DASH] = ACTIONS(172),
    [anon_sym_if] = ACTIONS(170),
    [anon_sym_STAR] = ACTIONS(172),
    [anon_sym_elseif] = ACTIONS(170),
    [anon_sym_and] = ACTIONS(170),
    [anon_sym_SLASH] = ACTIONS(172),
    [anon_sym_GT] = ACTIONS(170),
    [anon_sym_PLUS] = ACTIONS(172),
    [anon_sym_EQ] = ACTIONS(172),
    [sym__endl] = ACTIONS(172),
    [anon_sym_choose] = ACTIONS(170),
    [anon_sym_BANG_EQ] = ACTIONS(172),
    [sym_identifier] = ACTIONS(170),
    [anon_sym_LT_EQ] = ACTIONS(172),
  },
  [112] = {
    [sym_boolean] = STATE(119),
    [sym_unary_expression] = STATE(119),
    [sym_binary_expression] = STATE(119),
    [sym__expression] = STATE(119),
    [sym__constant] = STATE(119),
    [sym_paran_expression] = STATE(119),
    [sym_number] = ACTIONS(392),
    [anon_sym_true] = ACTIONS(394),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(392),
    [anon_sym_false] = ACTIONS(394),
    [anon_sym_DASH] = ACTIONS(396),
    [anon_sym_LPAREN] = ACTIONS(398),
    [sym_identifier] = ACTIONS(400),
    [anon_sym_not] = ACTIONS(402),
  },
  [113] = {
    [sym_boolean] = STATE(120),
    [sym_unary_expression] = STATE(120),
    [sym_binary_expression] = STATE(120),
    [sym__expression] = STATE(120),
    [sym__constant] = STATE(120),
    [sym_paran_expression] = STATE(120),
    [sym_number] = ACTIONS(404),
    [anon_sym_true] = ACTIONS(394),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(404),
    [anon_sym_false] = ACTIONS(394),
    [anon_sym_DASH] = ACTIONS(396),
    [anon_sym_LPAREN] = ACTIONS(398),
    [sym_identifier] = ACTIONS(406),
    [anon_sym_not] = ACTIONS(402),
  },
  [114] = {
    [sym_boolean] = STATE(121),
    [sym_unary_expression] = STATE(121),
    [sym_binary_expression] = STATE(121),
    [sym__expression] = STATE(121),
    [sym__constant] = STATE(121),
    [sym_paran_expression] = STATE(121),
    [sym_number] = ACTIONS(408),
    [anon_sym_true] = ACTIONS(394),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(408),
    [anon_sym_false] = ACTIONS(394),
    [anon_sym_DASH] = ACTIONS(396),
    [anon_sym_LPAREN] = ACTIONS(398),
    [sym_identifier] = ACTIONS(410),
    [anon_sym_not] = ACTIONS(402),
  },
  [115] = {
    [sym_boolean] = STATE(122),
    [sym_unary_expression] = STATE(122),
    [sym_binary_expression] = STATE(122),
    [sym__expression] = STATE(122),
    [sym__constant] = STATE(122),
    [sym_paran_expression] = STATE(122),
    [sym_number] = ACTIONS(412),
    [anon_sym_true] = ACTIONS(394),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(412),
    [anon_sym_false] = ACTIONS(394),
    [anon_sym_DASH] = ACTIONS(396),
    [anon_sym_LPAREN] = ACTIONS(398),
    [sym_identifier] = ACTIONS(414),
    [anon_sym_not] = ACTIONS(402),
  },
  [116] = {
    [sym_boolean] = STATE(123),
    [sym_unary_expression] = STATE(123),
    [sym_binary_expression] = STATE(123),
    [sym__expression] = STATE(123),
    [sym__constant] = STATE(123),
    [sym_paran_expression] = STATE(123),
    [sym_number] = ACTIONS(416),
    [anon_sym_true] = ACTIONS(394),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(416),
    [anon_sym_false] = ACTIONS(394),
    [anon_sym_DASH] = ACTIONS(396),
    [anon_sym_LPAREN] = ACTIONS(398),
    [sym_identifier] = ACTIONS(418),
    [anon_sym_not] = ACTIONS(402),
  },
  [117] = {
    [anon_sym_end] = ACTIONS(233),
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(231),
    [anon_sym_choose] = ACTIONS(233),
    [sym_identifier] = ACTIONS(233),
    [anon_sym_if] = ACTIONS(233),
    [anon_sym_STAR] = ACTIONS(231),
  },
  [118] = {
    [anon_sym_LT] = ACTIONS(237),
    [anon_sym_end] = ACTIONS(237),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(237),
    [anon_sym_or] = ACTIONS(237),
    [anon_sym_GT_EQ] = ACTIONS(239),
    [anon_sym_DASH] = ACTIONS(239),
    [anon_sym_if] = ACTIONS(237),
    [anon_sym_STAR] = ACTIONS(239),
    [anon_sym_elseif] = ACTIONS(237),
    [anon_sym_and] = ACTIONS(237),
    [anon_sym_SLASH] = ACTIONS(239),
    [anon_sym_GT] = ACTIONS(237),
    [anon_sym_PLUS] = ACTIONS(239),
    [anon_sym_EQ] = ACTIONS(239),
    [sym__endl] = ACTIONS(239),
    [anon_sym_choose] = ACTIONS(237),
    [anon_sym_BANG_EQ] = ACTIONS(239),
    [sym_identifier] = ACTIONS(237),
    [anon_sym_LT_EQ] = ACTIONS(239),
  },
  [119] = {
    [anon_sym_LT] = ACTIONS(241),
    [anon_sym_end] = ACTIONS(241),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(241),
    [anon_sym_or] = ACTIONS(241),
    [anon_sym_GT_EQ] = ACTIONS(243),
    [anon_sym_DASH] = ACTIONS(328),
    [anon_sym_if] = ACTIONS(241),
    [anon_sym_STAR] = ACTIONS(330),
    [anon_sym_elseif] = ACTIONS(241),
    [anon_sym_and] = ACTIONS(241),
    [anon_sym_SLASH] = ACTIONS(330),
    [anon_sym_GT] = ACTIONS(241),
    [anon_sym_PLUS] = ACTIONS(328),
    [anon_sym_EQ] = ACTIONS(243),
    [sym__endl] = ACTIONS(243),
    [anon_sym_choose] = ACTIONS(241),
    [anon_sym_BANG_EQ] = ACTIONS(243),
    [sym_identifier] = ACTIONS(241),
    [anon_sym_LT_EQ] = ACTIONS(243),
  },
  [120] = {
    [anon_sym_LT] = ACTIONS(322),
    [anon_sym_end] = ACTIONS(241),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(241),
    [anon_sym_or] = ACTIONS(241),
    [anon_sym_GT_EQ] = ACTIONS(326),
    [anon_sym_DASH] = ACTIONS(328),
    [anon_sym_if] = ACTIONS(241),
    [anon_sym_STAR] = ACTIONS(330),
    [anon_sym_elseif] = ACTIONS(241),
    [anon_sym_and] = ACTIONS(241),
    [anon_sym_SLASH] = ACTIONS(330),
    [anon_sym_GT] = ACTIONS(322),
    [anon_sym_PLUS] = ACTIONS(328),
    [anon_sym_EQ] = ACTIONS(326),
    [sym__endl] = ACTIONS(243),
    [anon_sym_choose] = ACTIONS(241),
    [anon_sym_BANG_EQ] = ACTIONS(326),
    [sym_identifier] = ACTIONS(241),
    [anon_sym_LT_EQ] = ACTIONS(326),
  },
  [121] = {
    [anon_sym_LT] = ACTIONS(241),
    [anon_sym_end] = ACTIONS(241),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(241),
    [anon_sym_or] = ACTIONS(241),
    [anon_sym_GT_EQ] = ACTIONS(243),
    [anon_sym_DASH] = ACTIONS(243),
    [anon_sym_if] = ACTIONS(241),
    [anon_sym_STAR] = ACTIONS(243),
    [anon_sym_elseif] = ACTIONS(241),
    [anon_sym_and] = ACTIONS(241),
    [anon_sym_SLASH] = ACTIONS(243),
    [anon_sym_GT] = ACTIONS(241),
    [anon_sym_PLUS] = ACTIONS(243),
    [anon_sym_EQ] = ACTIONS(243),
    [sym__endl] = ACTIONS(243),
    [anon_sym_choose] = ACTIONS(241),
    [anon_sym_BANG_EQ] = ACTIONS(243),
    [sym_identifier] = ACTIONS(241),
    [anon_sym_LT_EQ] = ACTIONS(243),
  },
  [122] = {
    [anon_sym_LT] = ACTIONS(322),
    [anon_sym_end] = ACTIONS(241),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(241),
    [anon_sym_or] = ACTIONS(241),
    [anon_sym_GT_EQ] = ACTIONS(326),
    [anon_sym_DASH] = ACTIONS(328),
    [anon_sym_if] = ACTIONS(241),
    [anon_sym_STAR] = ACTIONS(330),
    [anon_sym_elseif] = ACTIONS(241),
    [anon_sym_and] = ACTIONS(332),
    [anon_sym_SLASH] = ACTIONS(330),
    [anon_sym_GT] = ACTIONS(322),
    [anon_sym_PLUS] = ACTIONS(328),
    [anon_sym_EQ] = ACTIONS(326),
    [sym__endl] = ACTIONS(243),
    [anon_sym_choose] = ACTIONS(241),
    [anon_sym_BANG_EQ] = ACTIONS(326),
    [sym_identifier] = ACTIONS(241),
    [anon_sym_LT_EQ] = ACTIONS(326),
  },
  [123] = {
    [anon_sym_LT] = ACTIONS(241),
    [anon_sym_end] = ACTIONS(241),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(241),
    [anon_sym_or] = ACTIONS(241),
    [anon_sym_GT_EQ] = ACTIONS(243),
    [anon_sym_DASH] = ACTIONS(243),
    [anon_sym_if] = ACTIONS(241),
    [anon_sym_STAR] = ACTIONS(330),
    [anon_sym_elseif] = ACTIONS(241),
    [anon_sym_and] = ACTIONS(241),
    [anon_sym_SLASH] = ACTIONS(330),
    [anon_sym_GT] = ACTIONS(241),
    [anon_sym_PLUS] = ACTIONS(243),
    [anon_sym_EQ] = ACTIONS(243),
    [sym__endl] = ACTIONS(243),
    [anon_sym_choose] = ACTIONS(241),
    [anon_sym_BANG_EQ] = ACTIONS(243),
    [sym_identifier] = ACTIONS(241),
    [anon_sym_LT_EQ] = ACTIONS(243),
  },
  [124] = {
    [anon_sym_end] = ACTIONS(261),
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(259),
    [anon_sym_choose] = ACTIONS(261),
    [sym_identifier] = ACTIONS(261),
    [anon_sym_if] = ACTIONS(261),
    [anon_sym_STAR] = ACTIONS(259),
  },
  [125] = {
    [anon_sym_end] = ACTIONS(269),
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(267),
    [anon_sym_choose] = ACTIONS(269),
    [sym_identifier] = ACTIONS(269),
    [anon_sym_if] = ACTIONS(269),
    [anon_sym_STAR] = ACTIONS(267),
  },
  [126] = {
    [anon_sym_end] = ACTIONS(292),
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(290),
    [anon_sym_choose] = ACTIONS(292),
    [sym_identifier] = ACTIONS(292),
    [anon_sym_if] = ACTIONS(292),
    [anon_sym_STAR] = ACTIONS(290),
  },
  [127] = {
    [anon_sym_end] = ACTIONS(298),
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(296),
    [anon_sym_choose] = ACTIONS(298),
    [sym_identifier] = ACTIONS(298),
    [anon_sym_if] = ACTIONS(298),
    [anon_sym_STAR] = ACTIONS(296),
  },
  [128] = {
    [anon_sym_end] = ACTIONS(302),
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(300),
    [anon_sym_choose] = ACTIONS(302),
    [sym_identifier] = ACTIONS(302),
    [anon_sym_if] = ACTIONS(302),
    [anon_sym_STAR] = ACTIONS(300),
  },
  [129] = {
    [anon_sym_LT] = ACTIONS(51),
    [anon_sym_end] = ACTIONS(51),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(51),
    [anon_sym_or] = ACTIONS(51),
    [anon_sym_GT_EQ] = ACTIONS(306),
    [anon_sym_DASH] = ACTIONS(306),
    [anon_sym_if] = ACTIONS(51),
    [anon_sym_STAR] = ACTIONS(306),
    [anon_sym_elseif] = ACTIONS(51),
    [anon_sym_and] = ACTIONS(51),
    [anon_sym_SLASH] = ACTIONS(306),
    [anon_sym_GT] = ACTIONS(51),
    [anon_sym_PLUS] = ACTIONS(306),
    [anon_sym_EQ] = ACTIONS(306),
    [sym__endl] = ACTIONS(306),
    [anon_sym_choose] = ACTIONS(51),
    [anon_sym_BANG_EQ] = ACTIONS(306),
    [sym_identifier] = ACTIONS(51),
    [anon_sym_LT_EQ] = ACTIONS(306),
  },
  [130] = {
    [anon_sym_LT] = ACTIONS(170),
    [anon_sym_end] = ACTIONS(170),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(170),
    [anon_sym_GT_EQ] = ACTIONS(172),
    [anon_sym_DASH] = ACTIONS(172),
    [anon_sym_if] = ACTIONS(170),
    [anon_sym_STAR] = ACTIONS(172),
    [anon_sym_and] = ACTIONS(170),
    [anon_sym_SLASH] = ACTIONS(172),
    [anon_sym_GT] = ACTIONS(170),
    [anon_sym_PLUS] = ACTIONS(172),
    [anon_sym_EQ] = ACTIONS(172),
    [sym__endl] = ACTIONS(172),
    [anon_sym_choose] = ACTIONS(170),
    [anon_sym_BANG_EQ] = ACTIONS(172),
    [sym_identifier] = ACTIONS(170),
    [anon_sym_LT_EQ] = ACTIONS(172),
  },
  [131] = {
    [sym_boolean] = STATE(137),
    [sym_unary_expression] = STATE(137),
    [sym_binary_expression] = STATE(137),
    [sym__expression] = STATE(137),
    [sym__constant] = STATE(137),
    [sym_paran_expression] = STATE(137),
    [sym_number] = ACTIONS(420),
    [anon_sym_true] = ACTIONS(422),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(420),
    [anon_sym_false] = ACTIONS(422),
    [anon_sym_DASH] = ACTIONS(424),
    [anon_sym_LPAREN] = ACTIONS(426),
    [sym_identifier] = ACTIONS(428),
    [anon_sym_not] = ACTIONS(430),
  },
  [132] = {
    [sym_boolean] = STATE(138),
    [sym_unary_expression] = STATE(138),
    [sym_binary_expression] = STATE(138),
    [sym__expression] = STATE(138),
    [sym__constant] = STATE(138),
    [sym_paran_expression] = STATE(138),
    [sym_number] = ACTIONS(432),
    [anon_sym_true] = ACTIONS(422),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(432),
    [anon_sym_false] = ACTIONS(422),
    [anon_sym_DASH] = ACTIONS(424),
    [anon_sym_LPAREN] = ACTIONS(426),
    [sym_identifier] = ACTIONS(434),
    [anon_sym_not] = ACTIONS(430),
  },
  [133] = {
    [sym_boolean] = STATE(139),
    [sym_unary_expression] = STATE(139),
    [sym_binary_expression] = STATE(139),
    [sym__expression] = STATE(139),
    [sym__constant] = STATE(139),
    [sym_paran_expression] = STATE(139),
    [sym_number] = ACTIONS(436),
    [anon_sym_true] = ACTIONS(422),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(436),
    [anon_sym_false] = ACTIONS(422),
    [anon_sym_DASH] = ACTIONS(424),
    [anon_sym_LPAREN] = ACTIONS(426),
    [sym_identifier] = ACTIONS(438),
    [anon_sym_not] = ACTIONS(430),
  },
  [134] = {
    [sym_boolean] = STATE(140),
    [sym_unary_expression] = STATE(140),
    [sym_binary_expression] = STATE(140),
    [sym__expression] = STATE(140),
    [sym__constant] = STATE(140),
    [sym_paran_expression] = STATE(140),
    [sym_number] = ACTIONS(440),
    [anon_sym_true] = ACTIONS(422),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(440),
    [anon_sym_false] = ACTIONS(422),
    [anon_sym_DASH] = ACTIONS(424),
    [anon_sym_LPAREN] = ACTIONS(426),
    [sym_identifier] = ACTIONS(442),
    [anon_sym_not] = ACTIONS(430),
  },
  [135] = {
    [sym_boolean] = STATE(141),
    [sym_unary_expression] = STATE(141),
    [sym_binary_expression] = STATE(141),
    [sym__expression] = STATE(141),
    [sym__constant] = STATE(141),
    [sym_paran_expression] = STATE(141),
    [sym_number] = ACTIONS(444),
    [anon_sym_true] = ACTIONS(422),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(444),
    [anon_sym_false] = ACTIONS(422),
    [anon_sym_DASH] = ACTIONS(424),
    [anon_sym_LPAREN] = ACTIONS(426),
    [sym_identifier] = ACTIONS(446),
    [anon_sym_not] = ACTIONS(430),
  },
  [136] = {
    [anon_sym_LT] = ACTIONS(237),
    [anon_sym_end] = ACTIONS(237),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(237),
    [anon_sym_GT_EQ] = ACTIONS(239),
    [anon_sym_DASH] = ACTIONS(239),
    [anon_sym_if] = ACTIONS(237),
    [anon_sym_STAR] = ACTIONS(239),
    [anon_sym_and] = ACTIONS(237),
    [anon_sym_SLASH] = ACTIONS(239),
    [anon_sym_GT] = ACTIONS(237),
    [anon_sym_PLUS] = ACTIONS(239),
    [anon_sym_EQ] = ACTIONS(239),
    [sym__endl] = ACTIONS(239),
    [anon_sym_choose] = ACTIONS(237),
    [anon_sym_BANG_EQ] = ACTIONS(239),
    [sym_identifier] = ACTIONS(237),
    [anon_sym_LT_EQ] = ACTIONS(239),
  },
  [137] = {
    [anon_sym_LT] = ACTIONS(241),
    [anon_sym_end] = ACTIONS(241),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(241),
    [anon_sym_GT_EQ] = ACTIONS(243),
    [anon_sym_DASH] = ACTIONS(386),
    [anon_sym_if] = ACTIONS(241),
    [anon_sym_STAR] = ACTIONS(388),
    [anon_sym_and] = ACTIONS(241),
    [anon_sym_SLASH] = ACTIONS(388),
    [anon_sym_GT] = ACTIONS(241),
    [anon_sym_PLUS] = ACTIONS(386),
    [anon_sym_EQ] = ACTIONS(243),
    [sym__endl] = ACTIONS(243),
    [anon_sym_choose] = ACTIONS(241),
    [anon_sym_BANG_EQ] = ACTIONS(243),
    [sym_identifier] = ACTIONS(241),
    [anon_sym_LT_EQ] = ACTIONS(243),
  },
  [138] = {
    [anon_sym_LT] = ACTIONS(380),
    [anon_sym_end] = ACTIONS(241),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(241),
    [anon_sym_GT_EQ] = ACTIONS(384),
    [anon_sym_DASH] = ACTIONS(386),
    [anon_sym_if] = ACTIONS(241),
    [anon_sym_STAR] = ACTIONS(388),
    [anon_sym_and] = ACTIONS(241),
    [anon_sym_SLASH] = ACTIONS(388),
    [anon_sym_GT] = ACTIONS(380),
    [anon_sym_PLUS] = ACTIONS(386),
    [anon_sym_EQ] = ACTIONS(384),
    [sym__endl] = ACTIONS(243),
    [anon_sym_choose] = ACTIONS(241),
    [anon_sym_BANG_EQ] = ACTIONS(384),
    [sym_identifier] = ACTIONS(241),
    [anon_sym_LT_EQ] = ACTIONS(384),
  },
  [139] = {
    [anon_sym_LT] = ACTIONS(241),
    [anon_sym_end] = ACTIONS(241),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(241),
    [anon_sym_GT_EQ] = ACTIONS(243),
    [anon_sym_DASH] = ACTIONS(243),
    [anon_sym_if] = ACTIONS(241),
    [anon_sym_STAR] = ACTIONS(243),
    [anon_sym_and] = ACTIONS(241),
    [anon_sym_SLASH] = ACTIONS(243),
    [anon_sym_GT] = ACTIONS(241),
    [anon_sym_PLUS] = ACTIONS(243),
    [anon_sym_EQ] = ACTIONS(243),
    [sym__endl] = ACTIONS(243),
    [anon_sym_choose] = ACTIONS(241),
    [anon_sym_BANG_EQ] = ACTIONS(243),
    [sym_identifier] = ACTIONS(241),
    [anon_sym_LT_EQ] = ACTIONS(243),
  },
  [140] = {
    [anon_sym_LT] = ACTIONS(380),
    [anon_sym_end] = ACTIONS(241),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(241),
    [anon_sym_GT_EQ] = ACTIONS(384),
    [anon_sym_DASH] = ACTIONS(386),
    [anon_sym_if] = ACTIONS(241),
    [anon_sym_STAR] = ACTIONS(388),
    [anon_sym_and] = ACTIONS(390),
    [anon_sym_SLASH] = ACTIONS(388),
    [anon_sym_GT] = ACTIONS(380),
    [anon_sym_PLUS] = ACTIONS(386),
    [anon_sym_EQ] = ACTIONS(384),
    [sym__endl] = ACTIONS(243),
    [anon_sym_choose] = ACTIONS(241),
    [anon_sym_BANG_EQ] = ACTIONS(384),
    [sym_identifier] = ACTIONS(241),
    [anon_sym_LT_EQ] = ACTIONS(384),
  },
  [141] = {
    [anon_sym_LT] = ACTIONS(241),
    [anon_sym_end] = ACTIONS(241),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(241),
    [anon_sym_GT_EQ] = ACTIONS(243),
    [anon_sym_DASH] = ACTIONS(243),
    [anon_sym_if] = ACTIONS(241),
    [anon_sym_STAR] = ACTIONS(388),
    [anon_sym_and] = ACTIONS(241),
    [anon_sym_SLASH] = ACTIONS(388),
    [anon_sym_GT] = ACTIONS(241),
    [anon_sym_PLUS] = ACTIONS(243),
    [anon_sym_EQ] = ACTIONS(243),
    [sym__endl] = ACTIONS(243),
    [anon_sym_choose] = ACTIONS(241),
    [anon_sym_BANG_EQ] = ACTIONS(243),
    [sym_identifier] = ACTIONS(241),
    [anon_sym_LT_EQ] = ACTIONS(243),
  },
  [142] = {
    [anon_sym_LT] = ACTIONS(51),
    [anon_sym_end] = ACTIONS(51),
    [sym_comment] = ACTIONS(3),
    [anon_sym_or] = ACTIONS(51),
    [anon_sym_GT_EQ] = ACTIONS(306),
    [anon_sym_DASH] = ACTIONS(306),
    [anon_sym_if] = ACTIONS(51),
    [anon_sym_STAR] = ACTIONS(306),
    [anon_sym_and] = ACTIONS(51),
    [anon_sym_SLASH] = ACTIONS(306),
    [anon_sym_GT] = ACTIONS(51),
    [anon_sym_PLUS] = ACTIONS(306),
    [anon_sym_EQ] = ACTIONS(306),
    [sym__endl] = ACTIONS(306),
    [anon_sym_choose] = ACTIONS(51),
    [anon_sym_BANG_EQ] = ACTIONS(306),
    [sym_identifier] = ACTIONS(51),
    [anon_sym_LT_EQ] = ACTIONS(306),
  },
  [143] = {
    [sym_boolean] = STATE(11),
    [sym_stat_operator] = STATE(144),
    [sym__constant] = STATE(11),
    [sym_command_arg] = STATE(145),
    [aux_sym_command_repeat1] = STATE(145),
    [sym_number] = ACTIONS(17),
    [anon_sym_true] = ACTIONS(19),
    [anon_sym_COLON] = ACTIONS(448),
    [anon_sym_PLUS] = ACTIONS(23),
    [sym_bare_word] = ACTIONS(17),
    [anon_sym_EQ] = ACTIONS(23),
    [sym_string] = ACTIONS(17),
    [anon_sym_false] = ACTIONS(19),
    [anon_sym_DASH] = ACTIONS(23),
    [sym__endl] = ACTIONS(450),
    [anon_sym_LBRACE] = ACTIONS(27),
    [sym_comment] = ACTIONS(29),
  },
  [144] = {
    [sym_boolean] = STATE(82),
    [sym_unary_expression] = STATE(82),
    [sym_binary_expression] = STATE(82),
    [sym__expression] = STATE(82),
    [sym__constant] = STATE(82),
    [sym_stat_rvalue] = STATE(83),
    [sym_paran_expression] = STATE(82),
    [sym_number] = ACTIONS(452),
    [anon_sym_true] = ACTIONS(394),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(452),
    [anon_sym_false] = ACTIONS(394),
    [anon_sym_DASH] = ACTIONS(396),
    [anon_sym_LPAREN] = ACTIONS(398),
    [sym_identifier] = ACTIONS(454),
    [anon_sym_not] = ACTIONS(402),
  },
  [145] = {
    [sym_boolean] = STATE(11),
    [sym__constant] = STATE(11),
    [sym_command_arg] = STATE(29),
    [aux_sym_command_repeat1] = STATE(29),
    [sym_number] = ACTIONS(17),
    [anon_sym_true] = ACTIONS(19),
    [sym_comment] = ACTIONS(29),
    [sym_bare_word] = ACTIONS(17),
    [sym_string] = ACTIONS(17),
    [anon_sym_false] = ACTIONS(19),
    [sym__endl] = ACTIONS(456),
    [anon_sym_LBRACE] = ACTIONS(27),
  },
  [146] = {
    [sym_boolean] = STATE(85),
    [sym_unary_expression] = STATE(85),
    [sym_binary_expression] = STATE(85),
    [sym__expression] = STATE(85),
    [sym__constant] = STATE(85),
    [sym_paran_expression] = STATE(85),
    [sym_number] = ACTIONS(458),
    [anon_sym_true] = ACTIONS(73),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(458),
    [anon_sym_false] = ACTIONS(73),
    [anon_sym_DASH] = ACTIONS(75),
    [anon_sym_LPAREN] = ACTIONS(77),
    [sym_identifier] = ACTIONS(460),
    [anon_sym_not] = ACTIONS(81),
  },
  [147] = {
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(462),
  },
  [148] = {
    [anon_sym_LT] = ACTIONS(93),
    [anon_sym_and] = ACTIONS(95),
    [anon_sym_LT_EQ] = ACTIONS(97),
    [anon_sym_SLASH] = ACTIONS(99),
    [sym_comment] = ACTIONS(3),
    [anon_sym_GT] = ACTIONS(93),
    [anon_sym_PLUS] = ACTIONS(103),
    [anon_sym_or] = ACTIONS(101),
    [anon_sym_EQ] = ACTIONS(97),
    [anon_sym_RPAREN] = ACTIONS(464),
    [anon_sym_GT_EQ] = ACTIONS(97),
    [anon_sym_DASH] = ACTIONS(103),
    [anon_sym_BANG_EQ] = ACTIONS(97),
    [anon_sym_STAR] = ACTIONS(99),
  },
  [149] = {
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(466),
  },
  [150] = {
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(468),
  },
  [151] = {
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(470),
  },
  [152] = {
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(472),
  },
  [153] = {
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(474),
  },
  [154] = {
    [aux_sym_command_repeat1] = STATE(156),
    [sym_command_arg] = STATE(156),
    [sym_boolean] = STATE(11),
    [sym_stat_operator] = STATE(155),
    [sym__constant] = STATE(11),
    [anon_sym_true] = ACTIONS(19),
    [sym_comment] = ACTIONS(29),
    [sym_string] = ACTIONS(17),
    [anon_sym_DASH] = ACTIONS(23),
    [anon_sym_LBRACE] = ACTIONS(27),
    [sym_number] = ACTIONS(17),
    [anon_sym_COLON] = ACTIONS(476),
    [anon_sym_PLUS] = ACTIONS(23),
    [sym_bare_word] = ACTIONS(17),
    [anon_sym_EQ] = ACTIONS(23),
    [anon_sym_false] = ACTIONS(19),
    [sym__endl] = ACTIONS(478),
  },
  [155] = {
    [sym_unary_expression] = STATE(108),
    [sym_binary_expression] = STATE(108),
    [sym_paran_expression] = STATE(108),
    [sym_boolean] = STATE(108),
    [sym_stat_rvalue] = STATE(109),
    [sym__expression] = STATE(108),
    [sym__constant] = STATE(108),
    [sym_number] = ACTIONS(480),
    [anon_sym_true] = ACTIONS(422),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(480),
    [anon_sym_false] = ACTIONS(422),
    [anon_sym_DASH] = ACTIONS(424),
    [anon_sym_LPAREN] = ACTIONS(426),
    [sym_identifier] = ACTIONS(482),
    [anon_sym_not] = ACTIONS(430),
  },
  [156] = {
    [sym_boolean] = STATE(11),
    [sym__constant] = STATE(11),
    [sym_command_arg] = STATE(29),
    [aux_sym_command_repeat1] = STATE(29),
    [sym_number] = ACTIONS(17),
    [anon_sym_true] = ACTIONS(19),
    [sym_comment] = ACTIONS(29),
    [sym_bare_word] = ACTIONS(17),
    [sym_string] = ACTIONS(17),
    [anon_sym_false] = ACTIONS(19),
    [sym__endl] = ACTIONS(484),
    [anon_sym_LBRACE] = ACTIONS(27),
  },
  [157] = {
    [sym_boolean] = STATE(111),
    [sym_unary_expression] = STATE(111),
    [sym_binary_expression] = STATE(111),
    [sym__expression] = STATE(111),
    [sym__constant] = STATE(111),
    [sym_paran_expression] = STATE(111),
    [sym_number] = ACTIONS(486),
    [anon_sym_true] = ACTIONS(394),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(486),
    [anon_sym_false] = ACTIONS(394),
    [anon_sym_DASH] = ACTIONS(396),
    [anon_sym_LPAREN] = ACTIONS(398),
    [sym_identifier] = ACTIONS(488),
    [anon_sym_not] = ACTIONS(402),
  },
  [158] = {
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(490),
  },
  [159] = {
    [anon_sym_LT] = ACTIONS(93),
    [anon_sym_and] = ACTIONS(95),
    [anon_sym_LT_EQ] = ACTIONS(97),
    [anon_sym_SLASH] = ACTIONS(99),
    [sym_comment] = ACTIONS(3),
    [anon_sym_GT] = ACTIONS(93),
    [anon_sym_PLUS] = ACTIONS(103),
    [anon_sym_or] = ACTIONS(101),
    [anon_sym_EQ] = ACTIONS(97),
    [anon_sym_RPAREN] = ACTIONS(492),
    [anon_sym_GT_EQ] = ACTIONS(97),
    [anon_sym_DASH] = ACTIONS(103),
    [anon_sym_BANG_EQ] = ACTIONS(97),
    [anon_sym_STAR] = ACTIONS(99),
  },
  [160] = {
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(494),
  },
  [161] = {
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(496),
  },
  [162] = {
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(498),
  },
  [163] = {
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(500),
  },
  [164] = {
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(502),
  },
  [165] = {
    [sym_boolean] = STATE(130),
    [sym_unary_expression] = STATE(130),
    [sym_binary_expression] = STATE(130),
    [sym__expression] = STATE(130),
    [sym__constant] = STATE(130),
    [sym_paran_expression] = STATE(130),
    [sym_number] = ACTIONS(504),
    [anon_sym_true] = ACTIONS(422),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(504),
    [anon_sym_false] = ACTIONS(422),
    [anon_sym_DASH] = ACTIONS(424),
    [anon_sym_LPAREN] = ACTIONS(426),
    [sym_identifier] = ACTIONS(506),
    [anon_sym_not] = ACTIONS(430),
  },
  [166] = {
    [anon_sym_LT] = ACTIONS(93),
    [anon_sym_and] = ACTIONS(95),
    [anon_sym_LT_EQ] = ACTIONS(97),
    [anon_sym_SLASH] = ACTIONS(99),
    [sym_comment] = ACTIONS(3),
    [anon_sym_GT] = ACTIONS(93),
    [anon_sym_PLUS] = ACTIONS(103),
    [anon_sym_or] = ACTIONS(101),
    [anon_sym_EQ] = ACTIONS(97),
    [anon_sym_RPAREN] = ACTIONS(508),
    [anon_sym_GT_EQ] = ACTIONS(97),
    [anon_sym_DASH] = ACTIONS(103),
    [anon_sym_BANG_EQ] = ACTIONS(97),
    [anon_sym_STAR] = ACTIONS(99),
  },
  [167] = {
    [anon_sym_LBRACK] = ACTIONS(510),
    [sym_text_copy] = ACTIONS(512),
    [sym_comment] = ACTIONS(29),
  },
  [168] = {
    [sym_boolean] = STATE(148),
    [sym_unary_expression] = STATE(148),
    [sym_binary_expression] = STATE(148),
    [sym__expression] = STATE(148),
    [sym__constant] = STATE(148),
    [sym_paran_expression] = STATE(148),
    [sym_number] = ACTIONS(514),
    [anon_sym_true] = ACTIONS(33),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(514),
    [anon_sym_false] = ACTIONS(33),
    [anon_sym_DASH] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(37),
    [sym_identifier] = ACTIONS(516),
    [anon_sym_not] = ACTIONS(41),
  },
  [169] = {
    [sym_choice] = STATE(43),
    [aux_sym_choose_statement_repeat1] = STATE(43),
    [anon_sym_STAR] = ACTIONS(49),
    [sym_comment] = ACTIONS(3),
    [anon_sym_end] = ACTIONS(518),
  },
  [170] = {
    [sym_else_clause] = STATE(171),
    [aux_sym_if_statement_repeat1] = STATE(172),
    [sym_elseif_clause] = STATE(172),
    [anon_sym_elseif] = ACTIONS(206),
    [anon_sym_end] = ACTIONS(520),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(210),
  },
  [171] = {
    [sym_comment] = ACTIONS(3),
    [anon_sym_end] = ACTIONS(522),
  },
  [172] = {
    [sym_else_clause] = STATE(174),
    [aux_sym_if_statement_repeat1] = STATE(69),
    [sym_elseif_clause] = STATE(69),
    [anon_sym_elseif] = ACTIONS(206),
    [anon_sym_end] = ACTIONS(522),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(210),
  },
  [173] = {
    [sym_comment] = ACTIONS(29),
    [sym_text_copy] = ACTIONS(524),
  },
  [174] = {
    [sym_comment] = ACTIONS(3),
    [anon_sym_end] = ACTIONS(526),
  },
  [175] = {
    [sym_text_copy] = ACTIONS(528),
    [anon_sym_LBRACK] = ACTIONS(530),
    [sym_comment] = ACTIONS(29),
  },
  [176] = {
    [sym_boolean] = STATE(159),
    [sym_unary_expression] = STATE(159),
    [sym_binary_expression] = STATE(159),
    [sym__expression] = STATE(159),
    [sym__constant] = STATE(159),
    [sym_paran_expression] = STATE(159),
    [sym_number] = ACTIONS(532),
    [anon_sym_true] = ACTIONS(33),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(532),
    [anon_sym_false] = ACTIONS(33),
    [anon_sym_DASH] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(37),
    [sym_identifier] = ACTIONS(534),
    [anon_sym_not] = ACTIONS(41),
  },
  [177] = {
    [sym_choice] = STATE(43),
    [aux_sym_choose_statement_repeat1] = STATE(43),
    [anon_sym_end] = ACTIONS(536),
    [sym_comment] = ACTIONS(3),
    [anon_sym_STAR] = ACTIONS(49),
  },
  [178] = {
    [sym_else_clause] = STATE(179),
    [aux_sym_if_statement_repeat1] = STATE(180),
    [sym_elseif_clause] = STATE(180),
    [anon_sym_elseif] = ACTIONS(206),
    [anon_sym_end] = ACTIONS(538),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(210),
  },
  [179] = {
    [sym_comment] = ACTIONS(3),
    [anon_sym_end] = ACTIONS(540),
  },
  [180] = {
    [sym_else_clause] = STATE(182),
    [aux_sym_if_statement_repeat1] = STATE(69),
    [sym_elseif_clause] = STATE(69),
    [anon_sym_elseif] = ACTIONS(206),
    [anon_sym_end] = ACTIONS(540),
    [sym_comment] = ACTIONS(3),
    [anon_sym_else] = ACTIONS(210),
  },
  [181] = {
    [sym_comment] = ACTIONS(29),
    [sym_text_copy] = ACTIONS(542),
  },
  [182] = {
    [sym_comment] = ACTIONS(3),
    [anon_sym_end] = ACTIONS(544),
  },
  [183] = {
    [sym_boolean] = STATE(166),
    [sym_unary_expression] = STATE(166),
    [sym_binary_expression] = STATE(166),
    [sym__expression] = STATE(166),
    [sym__constant] = STATE(166),
    [sym_paran_expression] = STATE(166),
    [sym_number] = ACTIONS(546),
    [anon_sym_true] = ACTIONS(33),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(546),
    [anon_sym_false] = ACTIONS(33),
    [anon_sym_DASH] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(37),
    [sym_identifier] = ACTIONS(548),
    [anon_sym_not] = ACTIONS(41),
  },
  [184] = {
    [sym_choice] = STATE(169),
    [aux_sym_choose_statement_repeat1] = STATE(169),
    [sym_comment] = ACTIONS(3),
    [anon_sym_STAR] = ACTIONS(49),
  },
  [185] = {
    [sym_if_clause] = STATE(170),
    [sym_block] = STATE(39),
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(107),
  },
  [186] = {
    [sym_comment] = ACTIONS(3),
    [anon_sym_RBRACK] = ACTIONS(550),
  },
  [187] = {
    [sym_choice] = STATE(177),
    [aux_sym_choose_statement_repeat1] = STATE(177),
    [sym_comment] = ACTIONS(3),
    [anon_sym_STAR] = ACTIONS(49),
  },
  [188] = {
    [sym_if_clause] = STATE(178),
    [sym_block] = STATE(39),
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(107),
  },
  [189] = {
    [sym_comment] = ACTIONS(3),
    [anon_sym_RBRACK] = ACTIONS(552),
  },
  [190] = {
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(554),
  },
  [191] = {
    [sym_boolean] = STATE(18),
    [sym_unary_expression] = STATE(18),
    [sym_binary_expression] = STATE(18),
    [sym__expression] = STATE(18),
    [sym__constant] = STATE(18),
    [sym_condition] = STATE(185),
    [sym_paran_expression] = STATE(18),
    [sym_number] = ACTIONS(31),
    [anon_sym_true] = ACTIONS(33),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(31),
    [anon_sym_false] = ACTIONS(33),
    [anon_sym_DASH] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(37),
    [sym_identifier] = ACTIONS(39),
    [anon_sym_not] = ACTIONS(41),
  },
  [192] = {
    [sym_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(556),
  },
  [193] = {
    [sym_comment] = ACTIONS(3),
    [sym__endl] = ACTIONS(558),
  },
  [194] = {
    [sym_unary_expression] = STATE(18),
    [sym_binary_expression] = STATE(18),
    [sym_condition] = STATE(188),
    [sym_paran_expression] = STATE(18),
    [sym_boolean] = STATE(18),
    [sym__expression] = STATE(18),
    [sym__constant] = STATE(18),
    [sym_number] = ACTIONS(31),
    [anon_sym_true] = ACTIONS(33),
    [sym_comment] = ACTIONS(3),
    [sym_string] = ACTIONS(31),
    [anon_sym_false] = ACTIONS(33),
    [anon_sym_DASH] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(37),
    [sym_identifier] = ACTIONS(39),
    [anon_sym_not] = ACTIONS(41),
  },
  [195] = {
    [sym_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(560),
  },
};

static TSParseActionEntry ts_parse_actions[] = {
  [0] = {.count = 0, .reusable = false},
  [1] = {.count = 1, .reusable = false}, RECOVER(),
  [3] = {.count = 1, .reusable = true}, SHIFT_EXTRA(),
  [5] = {.count = 1, .reusable = true}, SHIFT(6),
  [7] = {.count = 1, .reusable = true}, REDUCE(sym_source_file, 0),
  [9] = {.count = 1, .reusable = false}, SHIFT(2),
  [11] = {.count = 1, .reusable = false}, SHIFT(3),
  [13] = {.count = 1, .reusable = false}, SHIFT(4),
  [15] = {.count = 1, .reusable = true}, SHIFT(7),
  [17] = {.count = 1, .reusable = false}, SHIFT(11),
  [19] = {.count = 1, .reusable = false}, SHIFT(8),
  [21] = {.count = 1, .reusable = false}, SHIFT(9),
  [23] = {.count = 1, .reusable = false}, SHIFT(10),
  [25] = {.count = 1, .reusable = false}, SHIFT(12),
  [27] = {.count = 1, .reusable = false}, SHIFT(13),
  [29] = {.count = 1, .reusable = false}, SHIFT_EXTRA(),
  [31] = {.count = 1, .reusable = true}, SHIFT(18),
  [33] = {.count = 1, .reusable = false}, SHIFT(79),
  [35] = {.count = 1, .reusable = true}, SHIFT(16),
  [37] = {.count = 1, .reusable = true}, SHIFT(17),
  [39] = {.count = 1, .reusable = false}, SHIFT(18),
  [41] = {.count = 1, .reusable = false}, SHIFT(16),
  [43] = {.count = 1, .reusable = true},  ACCEPT_INPUT(),
  [45] = {.count = 1, .reusable = true}, SHIFT(20),
  [47] = {.count = 1, .reusable = true}, REDUCE(sym_source_file, 1),
  [49] = {.count = 1, .reusable = true}, SHIFT(21),
  [51] = {.count = 1, .reusable = false}, REDUCE(sym_boolean, 1),
  [53] = {.count = 1, .reusable = false}, SHIFT(23),
  [55] = {.count = 1, .reusable = false}, SHIFT(24),
  [57] = {.count = 1, .reusable = true}, REDUCE(sym_stat_operator, 1),
  [59] = {.count = 1, .reusable = false}, REDUCE(sym_stat_operator, 1),
  [61] = {.count = 1, .reusable = false}, REDUCE(sym_command_arg, 1),
  [63] = {.count = 1, .reusable = true}, REDUCE(sym_command, 2, .production_id = 1),
  [65] = {.count = 1, .reusable = false}, REDUCE(sym_command, 2, .production_id = 1),
  [67] = {.count = 1, .reusable = true}, SHIFT(25),
  [69] = {.count = 1, .reusable = false}, SHIFT(25),
  [71] = {.count = 1, .reusable = true}, SHIFT(26),
  [73] = {.count = 1, .reusable = false}, SHIFT(105),
  [75] = {.count = 1, .reusable = true}, SHIFT(146),
  [77] = {.count = 1, .reusable = true}, SHIFT(168),
  [79] = {.count = 1, .reusable = false}, SHIFT(26),
  [81] = {.count = 1, .reusable = false}, SHIFT(146),
  [83] = {.count = 1, .reusable = false}, SHIFT(28),
  [85] = {.count = 1, .reusable = true}, SHIFT(30),
  [87] = {.count = 1, .reusable = false}, SHIFT(30),
  [89] = {.count = 1, .reusable = true}, SHIFT(31),
  [91] = {.count = 1, .reusable = false}, SHIFT(31),
  [93] = {.count = 1, .reusable = false}, SHIFT(32),
  [95] = {.count = 1, .reusable = true}, SHIFT(33),
  [97] = {.count = 1, .reusable = true}, SHIFT(32),
  [99] = {.count = 1, .reusable = true}, SHIFT(34),
  [101] = {.count = 1, .reusable = true}, SHIFT(35),
  [103] = {.count = 1, .reusable = true}, SHIFT(36),
  [105] = {.count = 1, .reusable = true}, REDUCE(sym_condition, 1),
  [107] = {.count = 1, .reusable = true}, SHIFT(37),
  [109] = {.count = 2, .reusable = true}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(20),
  [112] = {.count = 2, .reusable = false}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(2),
  [115] = {.count = 1, .reusable = true}, REDUCE(aux_sym_source_file_repeat1, 2),
  [117] = {.count = 2, .reusable = false}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(3),
  [120] = {.count = 2, .reusable = false}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(4),
  [123] = {.count = 1, .reusable = false}, SHIFT(40),
  [125] = {.count = 1, .reusable = false}, SHIFT(41),
  [127] = {.count = 1, .reusable = true}, SHIFT(42),
  [129] = {.count = 1, .reusable = true}, SHIFT(44),
  [131] = {.count = 1, .reusable = true}, SHIFT(45),
  [133] = {.count = 1, .reusable = true}, SHIFT(46),
  [135] = {.count = 1, .reusable = false}, SHIFT(86),
  [137] = {.count = 1, .reusable = false}, SHIFT(89),
  [139] = {.count = 1, .reusable = true}, SHIFT(86),
  [141] = {.count = 1, .reusable = true}, SHIFT(90),
  [143] = {.count = 1, .reusable = false}, REDUCE(sym_stat_rvalue, 1),
  [145] = {.count = 1, .reusable = true}, SHIFT(88),
  [147] = {.count = 1, .reusable = false}, SHIFT(87),
  [149] = {.count = 1, .reusable = true}, REDUCE(sym_stat_rvalue, 1),
  [151] = {.count = 1, .reusable = true}, REDUCE(sym_stat_operation, 3, .production_id = 2),
  [153] = {.count = 1, .reusable = false}, REDUCE(sym_stat_operation, 3, .production_id = 2),
  [155] = {.count = 1, .reusable = true}, REDUCE(sym_command, 3, .production_id = 1),
  [157] = {.count = 1, .reusable = false}, REDUCE(sym_command, 3, .production_id = 1),
  [159] = {.count = 2, .reusable = false}, REDUCE(aux_sym_command_repeat1, 2), SHIFT_REPEAT(11),
  [162] = {.count = 2, .reusable = false}, REDUCE(aux_sym_command_repeat1, 2), SHIFT_REPEAT(8),
  [165] = {.count = 1, .reusable = false}, REDUCE(aux_sym_command_repeat1, 2),
  [167] = {.count = 2, .reusable = false}, REDUCE(aux_sym_command_repeat1, 2), SHIFT_REPEAT(13),
  [170] = {.count = 1, .reusable = false}, REDUCE(sym_unary_expression, 2),
  [172] = {.count = 1, .reusable = true}, REDUCE(sym_unary_expression, 2),
  [174] = {.count = 1, .reusable = true}, SHIFT(47),
  [176] = {.count = 1, .reusable = true}, SHIFT(48),
  [178] = {.count = 1, .reusable = false}, SHIFT(48),
  [180] = {.count = 1, .reusable = true}, SHIFT(49),
  [182] = {.count = 1, .reusable = false}, SHIFT(49),
  [184] = {.count = 1, .reusable = true}, SHIFT(50),
  [186] = {.count = 1, .reusable = false}, SHIFT(50),
  [188] = {.count = 1, .reusable = true}, SHIFT(51),
  [190] = {.count = 1, .reusable = false}, SHIFT(51),
  [192] = {.count = 1, .reusable = true}, SHIFT(52),
  [194] = {.count = 1, .reusable = false}, SHIFT(52),
  [196] = {.count = 1, .reusable = false}, REDUCE(sym_block, 1),
  [198] = {.count = 1, .reusable = true}, SHIFT(53),
  [200] = {.count = 1, .reusable = false}, SHIFT(190),
  [202] = {.count = 1, .reusable = false}, SHIFT(143),
  [204] = {.count = 1, .reusable = false}, SHIFT(191),
  [206] = {.count = 1, .reusable = true}, SHIFT(54),
  [208] = {.count = 1, .reusable = true}, SHIFT(56),
  [210] = {.count = 1, .reusable = false}, SHIFT(55),
  [212] = {.count = 1, .reusable = true}, REDUCE(sym_if_clause, 1),
  [214] = {.count = 1, .reusable = false}, REDUCE(sym_if_clause, 1),
  [216] = {.count = 1, .reusable = true}, SHIFT(59),
  [218] = {.count = 1, .reusable = false}, SHIFT(59),
  [220] = {.count = 1, .reusable = true}, SHIFT(91),
  [222] = {.count = 1, .reusable = true}, SHIFT(62),
  [224] = {.count = 2, .reusable = true}, REDUCE(aux_sym_choose_statement_repeat1, 2), SHIFT_REPEAT(21),
  [227] = {.count = 1, .reusable = true}, REDUCE(aux_sym_choose_statement_repeat1, 2),
  [229] = {.count = 1, .reusable = true}, SHIFT(63),
  [231] = {.count = 1, .reusable = true}, REDUCE(sym_show_text, 4, .production_id = 3),
  [233] = {.count = 1, .reusable = false}, REDUCE(sym_show_text, 4, .production_id = 3),
  [235] = {.count = 1, .reusable = false}, REDUCE(sym_command_arg, 3),
  [237] = {.count = 1, .reusable = false}, REDUCE(sym_paran_expression, 3),
  [239] = {.count = 1, .reusable = true}, REDUCE(sym_paran_expression, 3),
  [241] = {.count = 1, .reusable = false}, REDUCE(sym_binary_expression, 3),
  [243] = {.count = 1, .reusable = true}, REDUCE(sym_binary_expression, 3),
  [245] = {.count = 1, .reusable = false}, REDUCE(sym_block, 2),
  [247] = {.count = 1, .reusable = true}, SHIFT(81),
  [249] = {.count = 1, .reusable = true}, SHIFT(66),
  [251] = {.count = 1, .reusable = true}, SHIFT(67),
  [253] = {.count = 1, .reusable = true}, REDUCE(sym_choice_condition, 1),
  [255] = {.count = 1, .reusable = true}, SHIFT(70),
  [257] = {.count = 1, .reusable = true}, REDUCE(sym_choice, 3),
  [259] = {.count = 1, .reusable = true}, REDUCE(sym_choose_statement, 5),
  [261] = {.count = 1, .reusable = false}, REDUCE(sym_choose_statement, 5),
  [263] = {.count = 1, .reusable = false}, SHIFT(71),
  [265] = {.count = 1, .reusable = true}, REDUCE(sym_else_clause, 2),
  [267] = {.count = 1, .reusable = true}, REDUCE(sym_if_statement, 5),
  [269] = {.count = 1, .reusable = false}, REDUCE(sym_if_statement, 5),
  [271] = {.count = 1, .reusable = true}, SHIFT(73),
  [273] = {.count = 1, .reusable = true}, SHIFT(74),
  [275] = {.count = 2, .reusable = true}, REDUCE(aux_sym_if_statement_repeat1, 2), SHIFT_REPEAT(54),
  [278] = {.count = 1, .reusable = true}, REDUCE(aux_sym_if_statement_repeat1, 2),
  [280] = {.count = 1, .reusable = false}, REDUCE(aux_sym_if_statement_repeat1, 2),
  [282] = {.count = 1, .reusable = false}, SHIFT(75),
  [284] = {.count = 1, .reusable = true}, SHIFT(76),
  [286] = {.count = 1, .reusable = true}, REDUCE(sym_elseif_clause, 3),
  [288] = {.count = 1, .reusable = false}, REDUCE(sym_elseif_clause, 3),
  [290] = {.count = 1, .reusable = true}, REDUCE(sym_if_statement, 6),
  [292] = {.count = 1, .reusable = false}, REDUCE(sym_if_statement, 6),
  [294] = {.count = 1, .reusable = true}, SHIFT(77),
  [296] = {.count = 1, .reusable = true}, REDUCE(sym_show_text, 7, .production_id = 4),
  [298] = {.count = 1, .reusable = false}, REDUCE(sym_show_text, 7, .production_id = 4),
  [300] = {.count = 1, .reusable = true}, REDUCE(sym_if_statement, 7),
  [302] = {.count = 1, .reusable = false}, REDUCE(sym_if_statement, 7),
  [304] = {.count = 1, .reusable = true}, REDUCE(sym_choice, 6),
  [306] = {.count = 1, .reusable = true}, REDUCE(sym_boolean, 1),
  [308] = {.count = 1, .reusable = false}, REDUCE(aux_sym_source_file_repeat1, 2),
  [310] = {.count = 2, .reusable = true}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(81),
  [313] = {.count = 2, .reusable = false}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(190),
  [316] = {.count = 2, .reusable = false}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(143),
  [319] = {.count = 2, .reusable = false}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(191),
  [322] = {.count = 1, .reusable = false}, SHIFT(112),
  [324] = {.count = 1, .reusable = false}, SHIFT(115),
  [326] = {.count = 1, .reusable = true}, SHIFT(112),
  [328] = {.count = 1, .reusable = true}, SHIFT(116),
  [330] = {.count = 1, .reusable = true}, SHIFT(114),
  [332] = {.count = 1, .reusable = false}, SHIFT(113),
  [334] = {.count = 1, .reusable = true}, SHIFT(94),
  [336] = {.count = 1, .reusable = false}, SHIFT(94),
  [338] = {.count = 1, .reusable = true}, SHIFT(95),
  [340] = {.count = 1, .reusable = false}, SHIFT(95),
  [342] = {.count = 1, .reusable = true}, SHIFT(96),
  [344] = {.count = 1, .reusable = false}, SHIFT(96),
  [346] = {.count = 1, .reusable = true}, SHIFT(97),
  [348] = {.count = 1, .reusable = false}, SHIFT(97),
  [350] = {.count = 1, .reusable = true}, SHIFT(98),
  [352] = {.count = 1, .reusable = false}, SHIFT(98),
  [354] = {.count = 1, .reusable = true}, SHIFT(99),
  [356] = {.count = 1, .reusable = false}, SHIFT(193),
  [358] = {.count = 1, .reusable = false}, SHIFT(154),
  [360] = {.count = 1, .reusable = false}, SHIFT(194),
  [362] = {.count = 1, .reusable = true}, REDUCE(sym_block, 1),
  [364] = {.count = 1, .reusable = true}, SHIFT(107),
  [366] = {.count = 1, .reusable = true}, REDUCE(sym_block, 2),
  [368] = {.count = 2, .reusable = true}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(107),
  [371] = {.count = 2, .reusable = false}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(193),
  [374] = {.count = 2, .reusable = false}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(154),
  [377] = {.count = 2, .reusable = false}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(194),
  [380] = {.count = 1, .reusable = false}, SHIFT(131),
  [382] = {.count = 1, .reusable = false}, SHIFT(134),
  [384] = {.count = 1, .reusable = true}, SHIFT(131),
  [386] = {.count = 1, .reusable = true}, SHIFT(135),
  [388] = {.count = 1, .reusable = true}, SHIFT(133),
  [390] = {.count = 1, .reusable = false}, SHIFT(132),
  [392] = {.count = 1, .reusable = true}, SHIFT(119),
  [394] = {.count = 1, .reusable = false}, SHIFT(129),
  [396] = {.count = 1, .reusable = true}, SHIFT(157),
  [398] = {.count = 1, .reusable = true}, SHIFT(176),
  [400] = {.count = 1, .reusable = false}, SHIFT(119),
  [402] = {.count = 1, .reusable = false}, SHIFT(157),
  [404] = {.count = 1, .reusable = true}, SHIFT(120),
  [406] = {.count = 1, .reusable = false}, SHIFT(120),
  [408] = {.count = 1, .reusable = true}, SHIFT(121),
  [410] = {.count = 1, .reusable = false}, SHIFT(121),
  [412] = {.count = 1, .reusable = true}, SHIFT(122),
  [414] = {.count = 1, .reusable = false}, SHIFT(122),
  [416] = {.count = 1, .reusable = true}, SHIFT(123),
  [418] = {.count = 1, .reusable = false}, SHIFT(123),
  [420] = {.count = 1, .reusable = true}, SHIFT(137),
  [422] = {.count = 1, .reusable = false}, SHIFT(142),
  [424] = {.count = 1, .reusable = true}, SHIFT(165),
  [426] = {.count = 1, .reusable = true}, SHIFT(183),
  [428] = {.count = 1, .reusable = false}, SHIFT(137),
  [430] = {.count = 1, .reusable = false}, SHIFT(165),
  [432] = {.count = 1, .reusable = true}, SHIFT(138),
  [434] = {.count = 1, .reusable = false}, SHIFT(138),
  [436] = {.count = 1, .reusable = true}, SHIFT(139),
  [438] = {.count = 1, .reusable = false}, SHIFT(139),
  [440] = {.count = 1, .reusable = true}, SHIFT(140),
  [442] = {.count = 1, .reusable = false}, SHIFT(140),
  [444] = {.count = 1, .reusable = true}, SHIFT(141),
  [446] = {.count = 1, .reusable = false}, SHIFT(141),
  [448] = {.count = 1, .reusable = false}, SHIFT(167),
  [450] = {.count = 1, .reusable = false}, SHIFT(80),
  [452] = {.count = 1, .reusable = true}, SHIFT(82),
  [454] = {.count = 1, .reusable = false}, SHIFT(82),
  [456] = {.count = 1, .reusable = false}, SHIFT(84),
  [458] = {.count = 1, .reusable = true}, SHIFT(85),
  [460] = {.count = 1, .reusable = false}, SHIFT(85),
  [462] = {.count = 1, .reusable = true}, SHIFT(92),
  [464] = {.count = 1, .reusable = true}, SHIFT(93),
  [466] = {.count = 1, .reusable = true}, SHIFT(100),
  [468] = {.count = 1, .reusable = true}, SHIFT(101),
  [470] = {.count = 1, .reusable = true}, SHIFT(102),
  [472] = {.count = 1, .reusable = true}, SHIFT(103),
  [474] = {.count = 1, .reusable = true}, SHIFT(104),
  [476] = {.count = 1, .reusable = false}, SHIFT(175),
  [478] = {.count = 1, .reusable = false}, SHIFT(106),
  [480] = {.count = 1, .reusable = true}, SHIFT(108),
  [482] = {.count = 1, .reusable = false}, SHIFT(108),
  [484] = {.count = 1, .reusable = false}, SHIFT(110),
  [486] = {.count = 1, .reusable = true}, SHIFT(111),
  [488] = {.count = 1, .reusable = false}, SHIFT(111),
  [490] = {.count = 1, .reusable = true}, SHIFT(117),
  [492] = {.count = 1, .reusable = true}, SHIFT(118),
  [494] = {.count = 1, .reusable = true}, SHIFT(124),
  [496] = {.count = 1, .reusable = true}, SHIFT(125),
  [498] = {.count = 1, .reusable = true}, SHIFT(126),
  [500] = {.count = 1, .reusable = true}, SHIFT(127),
  [502] = {.count = 1, .reusable = true}, SHIFT(128),
  [504] = {.count = 1, .reusable = true}, SHIFT(130),
  [506] = {.count = 1, .reusable = false}, SHIFT(130),
  [508] = {.count = 1, .reusable = true}, SHIFT(136),
  [510] = {.count = 1, .reusable = false}, SHIFT(192),
  [512] = {.count = 1, .reusable = false}, SHIFT(147),
  [514] = {.count = 1, .reusable = true}, SHIFT(148),
  [516] = {.count = 1, .reusable = false}, SHIFT(148),
  [518] = {.count = 1, .reusable = true}, SHIFT(149),
  [520] = {.count = 1, .reusable = true}, SHIFT(150),
  [522] = {.count = 1, .reusable = true}, SHIFT(151),
  [524] = {.count = 1, .reusable = false}, SHIFT(152),
  [526] = {.count = 1, .reusable = true}, SHIFT(153),
  [528] = {.count = 1, .reusable = false}, SHIFT(158),
  [530] = {.count = 1, .reusable = false}, SHIFT(195),
  [532] = {.count = 1, .reusable = true}, SHIFT(159),
  [534] = {.count = 1, .reusable = false}, SHIFT(159),
  [536] = {.count = 1, .reusable = true}, SHIFT(160),
  [538] = {.count = 1, .reusable = true}, SHIFT(161),
  [540] = {.count = 1, .reusable = true}, SHIFT(162),
  [542] = {.count = 1, .reusable = false}, SHIFT(163),
  [544] = {.count = 1, .reusable = true}, SHIFT(164),
  [546] = {.count = 1, .reusable = true}, SHIFT(166),
  [548] = {.count = 1, .reusable = false}, SHIFT(166),
  [550] = {.count = 1, .reusable = true}, SHIFT(173),
  [552] = {.count = 1, .reusable = true}, SHIFT(181),
  [554] = {.count = 1, .reusable = true}, SHIFT(184),
  [556] = {.count = 1, .reusable = true}, SHIFT(186),
  [558] = {.count = 1, .reusable = true}, SHIFT(187),
  [560] = {.count = 1, .reusable = true}, SHIFT(189),
};

#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_fuior(void) {
  static TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .symbol_metadata = ts_symbol_metadata,
    .parse_table = (const unsigned short *)ts_parse_table,
    .parse_actions = ts_parse_actions,
    .lex_modes = ts_lex_modes,
    .symbol_names = ts_symbol_names,
    .alias_sequences = (const TSSymbol *)ts_alias_sequences,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .lex_fn = ts_lex,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
  };
  return &language;
}
