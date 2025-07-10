//
// Mountable.cpp
// 用于实现可装备对象的基类 Mountable
//

#include "Mountable.h"

void Mountable::unmount() {
    mounted = false;
}

bool Mountable::isMounted() const {
    return mounted;
}

void Mountable::mountToParent() {
    mounted = true;
}
