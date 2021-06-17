# Fuior

Fuior is a domain-specific language for narrative design. Fuior compiles to Lua
and the compiler is written in pure C and can easily be embedded as a library.

This repo contains a standalone CLI compiler (see `/cli`) and a Defold native 
extension (the repo can be added as a project dependency directly).

## The CLI

```bash
cd cli
make
build/$(uname)/fuior --help
```

The CLI looks for a `config.fui` file that it uses for static analysis and
type checking.

## The Defold native extension

```lua
-- Compiles Fuior source code into Lua source code (that you can then loadstring()).
-- filename is optional. used for intl hashes and error messages.
local lua_string = fuior_compiler.compile(fuior_string, filename)
```

Static analysis and type checking steps are skipped.

## Syntax

A Fuior source file is a series of **statements**, separated by line breaks,
executed in order, top to bottom.

Comments can be added anywhere (except in the middle of a text statement or 
choice text).  Anything after the `#` character until the end of the line will 
be ignored by the compiler.

```fuior
# This is a comment
```

Apart from line breaks between statements, white spaces are not significant in 
any way. Empty lines and extra spaces between language tokens are ignored, 
but I do encourage you to practice good indentation.

### Assignment

```fuior
<variable_name> = <expression>
```

The assignment **statement** assigns the value of an **expression** to a **variable**
identified by its name.

### Expressions

Expressions are computed values. Expressions can be:

* Literal values. A literal can be:
    * a number: `my_var = 42.1`
    * boolean: `my_var = true`, `my_var = false`
    * a string (a sequence of characters): `my_var = "Hello world!"`
    * internationalized strings: `my_var = i"Hello world!"`
* The value of a variable: `my_var = another_var`
* Mathematical expressions (`+`, `-`, `*`, `/`):
    ```fuior
    my_var = 12 + 13
    my_var = my_var * 2
    my_var = -negated_var  # Unary negation
    ```
* Comparison operations (`<`, `>`, `<=`, `>=`, `=`, `!=` (not equal)). These resolve to a boolean (`true`/`false`) value
    ```fuior
    my_var = 12 < 13  # my_var becomes true
    my_var = 12 != 12  # my_var becomes false
    ```
* Boolean logic expressions (`and`, `or`, `not`)
    ```fuior
    my_var = favorite_pet = "cat" or favorite_pet = "dog"
    my_var = x >= 10 and x <= 100
    my_var = not x < 42  # Same thing as my_var = x >= 42
    ```
* Paranthesized expressions (to override the order of operations)
    ```fuior
    my_var = ((x + 1) * (x + 3)) * 2
    ```
* Command calls. Some commands return values that can be used in expressions
    ```fuior
    my_var = max(0, min(100, x))
    ```

### Increment/decrement a variable

```fuior
<variable_name> + <expression>
<variable_name> - <expression>
```

The increment/decrement **statements** add/subtract the value of an **expression** from the 
value of a **variable**.

```fuior
# The following 2 statements are semantically equivalent:
my_var +2
my_var = my_var + 2
```

### Commands

```fuior
<command_name> <arg1> <arg2> ... <argn>
```

Commands are **statements** that execute a particular task. A command always 
starts with its name, followed by a list of arguments.

Arguments can be literals, **bare words**, which are interpreted as string
literals or **expressions** between `{` and `}`.

```fuior
# These statements are equivalent:
some_command 12 false {x < 12} "a_string"
some_command 12 false {x < 12} a_string

# These are NOT the same:
some_command my_var    # This is a bare word and passes the "my_var" string as the first argument
some_command {my_var}  # This passes the value of the my_var variable as the first argument
```

### Text statements

```fuior
<character_id>: <dialogue_text>
<character_id>: [<animation>] <dialogue_text>
```

Text **statements** show a text line spoken by a character. Any text until the
end of line will be used verbatim, so you can't use `#` for comments in the middle
of a text line. The text line will be internationalized.

```fuior
alice: Should I eat the big mushroom or the small one?
chesire_cat: [intrigued] Too much thinking! Just go for it!
```

## Conditional statements

```fuior
if <boolean_expression>
  <statements>
end

if <boolean_expression>
  <statements>
elseif <boolean_expression>
  <statements>
elseif <boolean_expression>
  <statements>
...
else
  <statements>
end
```

The conditional **statement** executes a list of **statements** only if
a boolean **expression** resolves to `true` (Lua truthy to be more exact, so any 
value except for `false` and `nil` counts as `true`). An arbitrary number of
`elseif` clauses can be added to check for additional conditions when the previous
conditions failed. Optionally, an `else` clause will execute statements only if 
all of the if-clause and elseif-clause expressions resolve to `false`. 

```fuior
if favorite_pet = "cat"
  alice: I love cats!
elseif favorite_pet = "dog"
  alice: I love dogs!
elseif favorite_pet = "chicken"
  alice: I love chickens!
else
  alice: I don't know. I love all animals, I guess!
end
```

## Choose statements

```fuior
choose
* <option_text>
  <statements>
* [<option_condition>] <option_text>
  <statements>
...
* <option_text>
  <statements>
end
```

Choose **statements** present the user with a list of options and asks them to
make a choice. Once the choice has been made, the corresponding list of statements
for that choice is executed.

Optionally, each option can have an attached condition. This means the option will
only be shown if the option's condition (a boolean expression) evaluates to `true`.

Like the text in text statements, all text until end of line counts as choice text,
so comments don't work here either.

```fuior
choose
* Cats
  favorite_pet = "cat"
* Dogs
  favorite_pet = "dog"
* [owns_chickens] Chickens
  favorite_pet = "chicken"
end
```

## Declaring variables

```fuior
var foo
var bar: string
var baz: number = 12
var moo: number @min(0) @max(100) = 50
```

Before usage, variables must be declared. Fuior is an optionally typed language.
Declaring types for variables is not required, but encouraged.

Variables can be optionally annotated with decorators (see `@min` and `@max` in 
the example above). Their functions are runtime-defined.

## Defining your own commands

```fuior
command my_command()
  some_statements
end

command my_command_that_returns_a_number(): number 
  some_statements
  return 12 # Optional return statement
end
```

You can group statements into reusable blocks by defining your own commands.

Commands can return a value that can be used as part of an **expression**.

Command arguments for custom commands are not yet implemented (the syntax works,
but there is no mechanism to address the arguments as variables).

## Declaring commands

```fuior
declare command1()
declare command2(arg1: number, arg2: ?string)
declare command3(arg1: number, arg2: ?string): number
```

If your runtime defines external commands, you must define them so that
type checking works.
