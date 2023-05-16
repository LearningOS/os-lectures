#include<stdio>
#include<coroutine>

coro_ret<int> number_generator(int begin, int count) {
 std::cout << "number_generator invoked." << std::endl;
 for (int i=begin; i<count; ++i) {
   co_yield i;
 }
 co_return;
}
int main(int argc, char* argv[])
{
 auto g = number_generator(1, 10);
 std::cout << "begin to run!" << std::endl;
 while(!g.resume()) {
  std::cout << "got number:" << g.get() << std::endl;
  }
std::cout << "coroutine done, return value:" << g.get() << std::endl;
return 0;
}