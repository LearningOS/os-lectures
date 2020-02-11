# latex 常见错误提示及原因简析

from https://blog.csdn.net/dlaicxf/article/details/52527367

## Latex Error Classes



###  较为模糊的错误

This is a list of error classes with ambiguos error messages. Here either the errors are have different causes and the message output is same or else the errors have the same root cause but the messages are different.

| S.No | Class         | 错误提示信息                                           | 错误原因简析                                                 |
| :--- | :------------ | :----------------------------------------------------- | :----------------------------------------------------------- |
| 1    | e_des         | ! LaTeX Error: There's no line here to end             | Usage of \\ at the end of a long label in 'description' environment |
| 2    | e_center      | ! LaTeX Error: There's no line here to end             | Usage of \\ after the heading line in 'center' environment   |
| 3    | e_foot        | ! Argument of \@sect has an extra }                    | Usage of a fragile command 'footnote' within \section        |
| 4    | e_ragged      | ! Argument of \@caption has an extra }                 | Usage of \\ within \raggedright or \raggedleft environment   |
| 5    | e_and         | ! Extra alignment tab has been changed to \cr          | Too many &s in a row of a table or array or eqnarray.        |
| 6    | e_cline       | ! Extra alignment tab has been changed to \cr          | Reference no non existing column in \cline                   |
| 7    | e_col         | ! Extra alignment tab has been changed to \cr.         | Usage @ in tabular* environment                              |
| 8    | e_num         | ! Missing number treated as zero                       | Usage of non numeric parameter after \\                      |
| 9    | e_asterisk    | Missing * at the end of the line                       | * is not printed when used without brace after \\            |
| 10   | e_pbox_miss   | ! Missing number, treated as zero.                     | \parbox[t]{} ..Missing argument to parbox                    |
| 11   | e_mis_circle  | ! Missing number, treated as zero.                     | Missing numeric parameter to \circle                         |
| 12   | e_list        | ! Argument of \lst@next has an extra }                 | Usage of 1stlisting inside fragile command \parbox           |
| 13   | e_capacity    | ! TeX capacity exceeded, sorry [input stack size=1500] | Usage of 1stlisting inside fragile command \parbox           |
| 14   | e_runaway     | Runaway argument?                                      | Generally because of missing braces, e.g \cline{1-2 instead of \cline{1-2} |
| 15   | e_verbatim    | Runaway argument?                                      | Usage of verbatim within scope of another command e.g: \ifthenelse |
| 16   | e_undefined   | ! Undefined control sequence                           | Usage of an unknown command                                  |
| 17   | e_footnote    | ! Undefined control sequence                           | Usage of \footnote within \footnote                          |
| 18   | e_integral    | ! Missing { inserted.                                  | Integral bounds are malformed                                |
| 19   | e_zeta        | ! Missing { inserted.                                  | Extra subscript before integral upper limit term             |
| 20   | e_bezier      | ! Illegal unit of measure (pt inserted).               | Missing numeric argument to \qbezier                         |
| 21   | e_too_bezier  | ! Illegal unit of measure (pt inserted).               | Too many arguments to \qbezier                               |
| 22   | e_unit        | ! Illegal unit of measure (pt inserted)                | \parbox[t]{2} ..Illegal unit of second parameter             |
| 23   | e_symfoot     | ! LaTeX Error: Counter too large.                      | More than 9 footnotes when using symbolic footnotes          |
| 24   | e_large_count | ! LaTeX Error: Counter too large.                      | Trying to display a corresponding letter for a counter vallue >26 |
| 25   | e_begin       | ! LaTeX Error: Missing \begin{document}                | Either text has been placed before \begin{document} or \begin{document} is missing |
| 26   | e_margin      | ! LaTeX Error: Missing \begin{document}.               | Misuse of \marginsize                                        |

------



### 常见错误

| S.No | Class         | 错误提示信息                                                 | 错误原因简析                                                 |
| :--- | :------------ | :----------------------------------------------------------- | :----------------------------------------------------------- |
| 1    | e_fileEnd     | ! File ended while scanning use of \end.                     | Generally caused because of missing a brace                  |
| 2    | e_end         | No message only an asterisk, i.e *                           | Missing \end{document}                                       |
| 3    | e_illegal     | LaTeX Error: Illegal character in array arg                  | Usage of a letter other than r,l and c in tabular environment |
| 4    | e_tab         | ! Misplaced alignment tab character &                        | Missing \begin{tabular} while using tabular environment      |
| 5    | e_backslash   | ! Missing \endcsname inserted                                | Usage of a backslash in front of the name of an environment, e.g \begin{\itemize} |
| 6    | e_delimiter   | ! LaTeX Error: Bad math environment delimiter                | Missing \right immediately after the array environment       |
| 7    | e_right       | ! Extra \right                                               | \right has no matching \left OR \end{array} is missing       |
| 8    | e_package     | ! LaTeX Error: Can only be used in preamble                  | Usage of \usepackage outside the preamble                    |
| 9    | e_math        | ! Missing $ inserted                                         | Missing a starting or ending $ in Math mode, e.g m_e instead of $m_e$ |
| 10   | e_parameter   | ! Illegal parameter number in definition of...               | Usage of parameter number greater than the number of parameters defined in \newcommand, e.g \newcommand{\test}[1]{#3} |
| 11   | e_cmd         | ! LaTeX Error: Command ... already defined                   | Trying to define already existing command, e.g \newcommand{\time} |
| 12   | e_caption     | ! LaTeX Error: \caption outside float                        | \caption{...} used outside table environment                 |
| 13   | e_braces      | ! Too many }'s                                               | Missing \begin{table}statement                               |
| 14   | e_parbox      | ! Argument of \@caption has an extra }                       | Usage of \parbox in a \caption                               |
| 15   | e_item        | ! LaTeX Error: Something's wrong--perhaps a missing \item    | Missing \item within enumerate environment                   |
| 16   | e_fraction    | ! Argument of \end has an extra }                            | Misuse of fraction cmd e.g \frac{1,2}                        |
| 17   | e_verb        | ! LaTeX Error: \verb ended by end of line                    | Newline after \verb, e.g. \verb*dir*                         |
| 18   | e_invalid     | ! LaTeX Error: Command \end{itemize} invalid in math mode    | Missing $ while using math mode in \itemize                  |
| 19   | e_equation    | ! Display math should end with $$                            | Usage of $$ inside equation mode                             |
| 20   | e_column      | ! Misplaced \omit                                            | Usage of \newcommand and \multicolumn within tabular environment |
| 21   | e_subscript   | ! Double subscript.                                          | Usage of double subscript                                    |
| 22   | e_cls         | ! LaTeX Error: File `artcle.cls' not found.                  | Missing .sty or .cls file                                    |
| 23   | e_nofile      | ! LaTeX Error: File `file1.tex' not found.                   | Missing file1.tex, e.g. \input{file1.tex}                    |
| 24   | e_sty         | ! LaTeX Error: File `anysize1.sty' not found                 | Use of unavailable package                                   |
| 25   | e_doc_class   | ! LaTeX Error: Can be used only in preamble.                 | Usage of \documentclass outside preamble                     |
| 26   | e_circle      | ! LaTeX Error: Command \circle invalid in math mode.         | Usage of \circle in math mode                                |
| 27   | e_picture     | ! Use of \pictur@ doesn't match its definition.              | Bad parameter to \picture                                    |
| 28   | e_line        | ! Use of \put dosen't match its definition                   | Badly formatted \line directive                              |
| 29   | e_line_arg    | ! LaTeX Error: Bad \line or \vector argument.                | Bad \line parameter                                          |
| 30   | e_counter     | ! LaTeX Error: No counter '10' defined.                      | Counter undefined                                            |
| 31   | e_outer       | ! LaTeX Error: Not in outer par mode.                        | Using figure inside parbox                                   |
| 32   | e_minipage    | ! LaTeX Error: Not in outer par mode.                        | Using figure minipage                                        |
| 33   | e_lost        | ! LaTeX Error: Float(s) lost.                                | Counter undefined                                            |
| 34   | e_lonely      | ! LaTeX Error: Lonely \item--perhaps a missing list environment. | Usage of \item outside list environment                      |
| 35   | e_parg        | ! LaTeX Error: Missing p-arg in array arg.                   | Missing p argument in tabular environment                    |
| 36   | e_hash        | ! You can't use `macro parameter character #' in vertical mode. | Usage of # in normal mode                                    |
| 37   | e_enlarge     | ! LaTeX Error: Suggested extra height (14454.0pt) dangerously large. | Too big a number given in \enlargethispage                   |
| 38   | e_deftab      | ! LaTeX Error: Undefined tab position.                       | Undefined tabbing                                            |
| 39   | e_pushtab     | ! LaTeX Error: \pushtabs and \poptabs don't match.           | Unequal numbers of push and pop tabs                         |
| 40   | e_overtab     | ! LaTeX Error: Tab overflow.                                 | Too many \= in tabbing environment                           |
| 41   | e_nest        | ! LaTeX Error: Too deeply nested.                            | Too many list environments                                   |
| 42   | e_eqnarray    | ! LaTeX Error: Too many columns in eqnarray environment.     | More than three columns in eqnarray                          |
| 43   | e_classpkg    | ! LaTeX Error: \usepackage before \documentclass.            | Usage of usepackage before loading documentclass             |
| 44   | e_load        | ! LaTeX Error: Two \LoadClass commands.                      | More than one load class command                             |
| 45   | e_require     | ! LaTeX Error: \RequirePackage or \LoadClass in Options Section. | RequirePackage may not be used with \DeclareOption           |
| 46   | e_twoclass    | ! LaTeX Error: Two \documentclass or \documentstyle commands. | More than one documentclass declaration                      |
| 47   | e_font        | ! LaTeX Error: This NFSS system isn't set up properly.       | Invalid font used in \DeclareErrorFont                       |
| 48   | e_superscript | ! Double superscript.                                        | Usage of two superscripts for the same variable, e.g. 2^3^4  |
| 49   | e_clash_opt   | ! LaTeX Error: Option clash for package csvtools.            | Clashing options for the same package                        |
| 50   | e_unknown_opt | ! LaTeX Error: Unknown option ... for package ...            | Unkown option for a package                                  |
| 51   | e_hyphenation | ! Improper \hyphenation will be flushed.                     | Improper parameter to \hyphenation                           |
| 52   | e_stack_size  | ! TeX capacity exceeded, sorry [main memory size=1000000]    | Overflow of buffer due to mistake in command definition      |
| 53   | e_environment | ! LaTeX Error: Environment ... undefined.                    | Undefined environment                                        |
| 54   | e_midline     | ! LaTeX Error: \< in mid line                                | Command \< may appear only at the beginning of a line        |
| 55   | e_infinite    | Goes into infinite loop                                      | Usage of \\strut\hrule                                       |