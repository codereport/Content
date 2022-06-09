
// https://run.dlang.io/is/XCZ1Uw

import std.stdio;

//int add(int a, int b) { return a + b; }
T add(T)(T a, T b) { return a + b; }

void main() {
    writeln(add(1, 2));
}
