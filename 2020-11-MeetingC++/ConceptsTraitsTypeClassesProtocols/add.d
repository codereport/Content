
// https://run.dlang.io/is/g6hXE1

import std.stdio;

T add(T)(T a, T b) { return a + b; }

void main() {
    writeln(add(1, 2));
}
