#include <iostream>
#include <entt/entt.hpp>

struct PositionComponent {
    float x;
    float y;
};

struct VelocityComponent {
    float dx;
    float dy;
};

void PrintSystem(entt::registry& registry)
{
    //========================
    /* 获取拥有组件的所有实体 */
    
    // 普通
    auto view = registry.view<PositionComponent, VelocityComponent>();
    // 迭代器访问
    // for (auto entity : view)
    // {
    //     PositionComponent& position = view.get<PositionComponent>(entity);
    //     position.x = 1;
    //     position.y = 1;
    //     std::cout << position.x << " " << position.y << std::endl;
    // }
    // lambda表达式访问
    view.each([](PositionComponent& position, VelocityComponent& velocity){
        position.x = 1;
        position.y = 1;
        velocity.dx = 2;
        velocity.dy = 2;
        std::cout << position.x << " " << position.y << std::endl;
        std::cout << velocity.dx << " " << velocity.dy << std::endl;
    });

    // 性能优化 group
    auto group = registry.group<PositionComponent, VelocityComponent>();
    group.each([](PositionComponent& position, VelocityComponent& velocity){
        position.x += velocity.dx;
        position.y += velocity.dy;
        std::cout << position.x << " " << position.y << std::endl;
    });
}

int main() {
    // 注册表
    entt::registry m_Registry;
    // 创建实体
    entt::entity m_Entity = m_Registry.create();

    // 添加组件
    m_Registry.emplace<PositionComponent>(m_Entity);
    m_Registry.emplace<VelocityComponent>(m_Entity);
    // 移除组件
    // m_Registry.remove<VelocityComponent>(m_Entity);
    // 移除所有组件
    // m_Registry.clear();

    //====================
    /* 获取某个实体的组件 */

    // 判断是否有某个组件
    if (m_Registry.all_of<PositionComponent>(m_Entity))
        // 获取组件
        PositionComponent& pos = m_Registry.get<PositionComponent>(m_Entity);

    // 判断是否同时拥有多个组件
    // if (m_Registry.all_of<PositionComponent, VelocityComponent>(m_Entity))
    // if (m_Registry.any_of<PositionComponent, VelocityComponent>(m_Entity))

    PrintSystem(m_Registry);

    return 0;
}