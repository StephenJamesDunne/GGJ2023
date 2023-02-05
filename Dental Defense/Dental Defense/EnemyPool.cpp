#include "EnemyPool.h"

EnemyPool::EnemyPool()
{
    for (auto& e : m_enemies)
        m_available.push(&e);
}


////////////////////////////////////////////////////////////////////////////////

Enemy* EnemyPool::spawn()
{
    Enemy* nextAvailable = nullptr;

    if (!m_available.empty())
    {
        nextAvailable = m_available.front();
        m_available.pop();
    }

    return nextAvailable;
}

////////////////////////////////////////////////////////////////////////////////

void EnemyPool::restore(Enemy* t_enemy)
{
    m_available.push(t_enemy);
}
