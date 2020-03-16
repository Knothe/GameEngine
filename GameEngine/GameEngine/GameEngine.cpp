
#include "Singletons/Platform.h"
#include "Singletons/GameManager.h"

using std::wcout;
using std::endl;

int main() {
	Platform::GetPtr();
	GameManager* g = GameManager::getPtr();
	g->Init();
	g->GameLoop();
	
	return 0;
}