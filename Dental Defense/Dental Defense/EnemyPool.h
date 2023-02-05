#ifndef ENEMY_POOL_H
#define ENEMY_POOL_H

#include <array>
#include <queue>
#include <Enemy.h>

class EnemyPool
{
public:
	static EnemyPool* const getInstance() {
		static EnemyPool* const instance = new EnemyPool();
		return instance;
	}

	EnemyPool(EnemyPool&) = delete;
	EnemyPool& operator=(EnemyPool&) = delete;

	Enemy* spawn();

	void restore(Enemy* t_enemy);

private:
	EnemyPool();

	std::array<Enemy, 50> m_enemies;
	std::queue<Enemy*> m_available;
};

#endif