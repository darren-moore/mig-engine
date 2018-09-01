#include "Component.h"

int Component::topIndex_ = 0;
std::unordered_map<std::type_index, int> Component::typeToIndex_;