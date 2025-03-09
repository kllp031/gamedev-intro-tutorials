#pragma once
#include <vector>
#include "Bullet.h"

class BulletManager {
public:
    std::vector<CBullet*> bullets;

    void AddBullet(CBullet* bullet) {
        bullets.push_back(bullet);
    }

    void Update(DWORD dt) {
        for (size_t i = 0; i < bullets.size(); i++) {
            bullets[i]->Update(dt);
            if (!bullets[i]->exist) {
                delete bullets[i];
                bullets.erase(bullets.begin() + i);
                i--;
            }
        }
    }

    void Render() {
        for (CBullet* bullet : bullets) {
            bullet->Render();
        }
    }

    void Clear() {
        for (CBullet* bullet : bullets) {
            delete bullet;
        }
        bullets.clear();
    }
};

// Declare bulletManager as extern
extern BulletManager bulletManager;

