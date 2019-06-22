# Calculator

## Build
The simplest way is to use QtCreator.

## Functional tables
<table>
<tr><th colspan=2> V1 op V2 = r	<th> V1 op V2 % r <th>           X =       <th>           X %
<tr><th> op <th colspan=2> Vs                     <th colspan=2> expa 
<tr><td> +  <td> V2             <td> V1           <td rowspan=4> X op Vs = <td rowspan=3> Vs op X %
<tr><td> -  <td> V2             <td> V1
<tr><td> ×  <td> V1             <td> V1
<tr><td> ÷  <td> V2             <td> V2                                    <td>           X op Vs %
</table>

| expr     | expa             |
| -------- | ---------------- |
| X × =(%) | X × X ($X^{2}$)  |
| X ÷ =(%) | 1 ÷ X ($X^{-1}$) |
| X √      | $\sqrt{X}$       |
| X + =(%) | Vs + X           |
| X - =(%) | Vs - X           |

Note:

- X - value on the display
- Vs - specific value
- op - operation
- r - result
- expr - expression
- expa - expantion
- Vs = 0 by default and changes with each operation

## View
![photo](https://github.com/vpunch/Calculator/blob/master/imgs/photo.png)
![screenshot](https://github.com/vpunch/Calculator/blob/master/imgs/screenshot.png)
