#define EXPORT __attribute__((visibility("default")))

void js_func_with_int(int x);
void js_func_with_string(char* str);

EXPORT int add(int x, int y) 
{
    return x + y;
}

EXPORT void func_that_will_call_js_with_int()
{
    js_func_with_int(42);
}

EXPORT void func_that_will_call_js_with_string()
{
    js_func_with_string("Hello from WASM!!");
}
