#include <selene.h>
#include <assert.h>

//int main() {
//	//using namespace lua;
//	lua::State state{ true };
//
//	//load file
//	state.Load("src/test.lua");
//
//	//access variables
//	assert(state["foo"] == 4);
//	assert(state["bar"][3] == "hi");
//	assert(state["bar"]["key"] == "there");
//
//	//direct Lua from C++
//	state("print \'Hello Lua From C\'");
//
//	//call Lua funtions from C++
//	state["helloWorld"];
//
//	int sum, difference;
//	lua::tie(sum, difference) = state["sum_and_difference"](5, 2);
//	assert(sum == 7 && difference == 3);
//
//	system("PAUSE");
//	return 0;
//}