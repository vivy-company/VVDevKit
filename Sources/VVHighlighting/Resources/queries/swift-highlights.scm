; Based on Helix editor's Swift highlights
; https://github.com/helix-editor/helix/blob/master/runtime/queries/swift/highlights.scm

(line_string_literal
  ["\\(" ")"] @punctuation.special)

["." ";" ":" "," ] @punctuation.delimiter
["(" ")" "[" "]" "{" "}"] @punctuation.bracket

; Operators
[
  "!"
  "?"
  "+"
  "-"
  "*"
  "/"
  "%"
  "="
  "+="
  "-="
  "*="
  "/="
  "<"
  ">"
  "<="
  ">="
  "++"
  "--"
  "&"
  "~"
  "%="
  "!="
  "!=="
  "=="
  "==="
  "??"
  "->"
  "..<"
  "..."
  (custom_operator)
] @operator

; Identifiers
(simple_identifier) @variable
(attribute) @attribute
(type_identifier) @type
(self_expression) @variable.builtin

; Declarations
"func" @keyword
[
  (visibility_modifier)
  (member_modifier)
  (function_modifier)
  (property_modifier)
  (parameter_modifier)
  (inheritance_modifier)
] @keyword.modifier

(function_declaration (simple_identifier) @function)
(protocol_function_declaration (simple_identifier) @function)
(deinit_declaration ["deinit" @constructor])
"init" @constructor

(throws) @keyword
"async" @keyword
"await" @keyword
(where_keyword) @keyword
(parameter external_name: (simple_identifier) @parameter)
(parameter name: (simple_identifier) @parameter)
(type_parameter (type_identifier) @type.parameter)
(inheritance_constraint (identifier (simple_identifier) @parameter))
(equality_constraint (identifier (simple_identifier) @parameter))
(pattern bound_identifier: (simple_identifier)) @variable

[
  "typealias"
  "struct"
  "class"
  "actor"
  "enum"
  "protocol"
  "extension"
  "indirect"
  "nonisolated"
  "override"
  "convenience"
  "required"
  "mutating"
  "associatedtype"
  "any"
] @keyword

(opaque_type ["some" @keyword])
(existential_type ["any" @keyword])

[
  (getter_specifier)
  (setter_specifier)
  (modify_specifier)
] @keyword

(class_body (property_declaration (pattern (simple_identifier) @property)))
(protocol_property_declaration (pattern (simple_identifier) @property))

(import_declaration "import" @keyword)

(enum_entry "case" @keyword)

; Function calls
(call_expression (simple_identifier) @function.call)
(call_expression
  (navigation_expression
    (navigation_suffix (simple_identifier) @function.call)))

(navigation_suffix
  (simple_identifier) @property)

"try" @keyword

(directive) @function.macro
(diagnostic) @function.macro

; Statements
(for_statement "for" @keyword)
(for_statement "in" @keyword)
(for_statement item: (simple_identifier) @variable)
(else) @keyword
(as_operator) @keyword

["while" "repeat" "continue" "break"] @keyword

["let" "var"] @keyword

(guard_statement "guard" @keyword)
(if_statement "if" @keyword)
(switch_statement "switch" @keyword)
(switch_entry "case" @keyword)
(switch_entry "fallthrough" @keyword)
(switch_entry (default_keyword) @keyword)
"return" @keyword
(ternary_expression
  ["?" ":"] @operator)

["do" (throw_keyword) (catch_keyword)] @keyword

(statement_label) @label

; Comments
(comment) @comment
(multiline_comment) @comment

; String literals
(line_str_text) @string
(str_escaped_char) @string.escape
(multi_line_str_text) @string
(raw_str_part) @string
(raw_str_end_part) @string
(raw_str_interpolation_start) @punctuation.special
["\"" "\"\"\""] @string

; Lambda literals
(lambda_literal "in" @keyword)

; Basic literals
[
  (hex_literal)
  (oct_literal)
  (bin_literal)
] @number
(integer_literal) @number
(real_literal) @number.float
(boolean_literal) @boolean
"nil" @constant.builtin

; Parameter packs (Swift 5.9+) - not available in our grammar version
