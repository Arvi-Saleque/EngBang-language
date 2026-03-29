# EngBang Keyword & Syntax Reference

## Data Types

| EngBang    | C equivalent | Meaning              |
|------------|--------------|----------------------|
| `shonkha`  | `int`        | Integer number       |
| `doshomik` | `float`      | Decimal number       |
| `lekha`    | `char*`      | String / text        |
| `shotto`   | `bool`       | Boolean (true/false) |

---

## Variable Declaration

| EngBang                                   | C equivalent       |
|-------------------------------------------|--------------------|
| `5 rakho x -> shonkha \|`                 | `int x = 5;`       |
| `khaali rakho x -> shonkha \|`            | `int x = 0;`       |
| `5 pakka rakho x -> shonkha \|`           | `const int x = 5;` |
| `5 banaw shonkha rakho x -> shonkha \|`   | `int x = (int)5;`  |

| Keyword  | C equivalent  | Meaning                   |
|----------|---------------|---------------------------|
| `rakho`  | `=` (declare) | Declare a variable        |
| `pakka`  | `const`       | Make variable constant    |
| `khaali` | (default)     | Declare with default value |
| `banaw`  | `(type)`      | Type cast                 |

---

## Variable Update

| EngBang                             | C equivalent     |
|-------------------------------------|------------------|
| `10 bodlao x \|`                    | `x = 10;`        |
| `10 banaw shonkha bodlao x \|`      | `x = (int)10;`   |

| Keyword  | C equivalent  | Meaning           |
|----------|---------------|-------------------|
| `bodlao` | `=` (assign)  | Update a variable |

---

## Print

| EngBang     | C equivalent          |
|-------------|-----------------------|
| `bolo x \|` | `printf("%d\n", x);`  |

| Keyword | Meaning              |
|---------|----------------------|
| `bolo`  | Print / display a value |

---

## Arithmetic Operators

| EngBang | C equivalent |
|---------|--------------|
| `+`     | `+`          |
| `-`     | `-`          |
| `*`     | `*`          |
| `/`     | `/`          |

---

## Loops

```
[varName -> startVal, varName -> endVal] {
  ...body...
  varName barbe
}
```

### Step Keywords

| EngBang                   | C equivalent | Meaning                |
|---------------------------|--------------|------------------------|
| `i barbe`                 | `i++`        | Increment by 1         |
| `i komabe`                | `i--`        | Decrement by 1         |
| `i poriborton_by +10`     | `i += 10`    | Add custom amount      |
| `i poriborton_by -3`      | `i -= 3`     | Subtract custom amount |
| `i poriborton_by *2`      | `i *= 2`     | Multiply by amount     |
| `i poriborton_by /4`      | `i /= 4`     | Divide by amount       |

### Loop Control Statements

| EngBang    | C equivalent | Meaning                              |
|------------|--------------|--------------------------------------|
| `thamo \|` | `break;`     | Exit the loop immediately            |
| `agao \|`  | `continue;`  | Skip rest of iteration, go to next   |

---

## Conditionals

```
varName -> value {
  [{op}] {
    ...body...
  }
}
```

### Condition Operators (inside `[...]`)

| EngBang | C equivalent | Meaning               |
|---------|--------------|-----------------------|
| `{>=}`  | `>=`         | Greater than or equal |
| `{<=}`  | `<=`         | Less than or equal    |
| `{==}`  | `==`         | Equal                 |
| `{!=}`  | `!=`         | Not equal             |
| `{>}`   | `>`          | Greater than          |
| `{<}`   | `<`          | Less than             |
| `{}`    | (always)     | Always match          |

| Keyword | Meaning                      |
|---------|------------------------------|
| `ar`    | Separate multiple bindings   |

---

## Functions

```
funcName(param -> type) -> returnType {
  ...body...
  ferao value |
}
```

| Keyword | C equivalent | Meaning        |
|---------|--------------|----------------|
| `ferao` | `return`     | Return a value |

---

## Comments

| EngBang      | C equivalent |
|--------------|--------------|
| `// text`    | `// text`    |
| `/* text */` | `/* text */` |

---

## Statement Terminator & Symbols

| Symbol         | C equivalent | Meaning                                      |
|----------------|--------------|----------------------------------------------|
| `\|`           | `;`          | End of statement                             |
| `->`           | (various)    | Type annotation, loop range, function return |
| `{ }`          | `{ }`        | Block body (loop / conditional / function)   |

