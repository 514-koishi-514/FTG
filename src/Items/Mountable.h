//
// 头文件 Mountable.h
// 可装备的对象基类
//

#ifndef MOUNTABLE_H
#define MOUNTABLE_H


class Mountable {
public:
    virtual void mountToParent();

    virtual void unmount();

    [[nodiscard]] bool isMounted() const;

private:
    bool mounted{};
};


#endif //MOUNTABLE_H
