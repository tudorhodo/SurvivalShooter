#pragma once

#include "components/simple_scene.h"
#include <time.h>

#define CIRCLE_NUMBER 50

using namespace std;

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };

        struct Projectile {
            Projectile(float x, float y, float angle)
                : x(x + cos(angle + M_PI_2) * 0.75), y(y + sin(angle + M_PI_2) * 0.75), x_start(x), y_start(y), angle(angle) {}
            float x;
            float y;
            float x_start;
            float y_start;
            float angle;
        };

        struct Enemy {
            Enemy(float x, float y, float angle, float speed)
                : x(x), y(y), angle(angle), speed(speed) {}
            float x;
            float y;
            float angle;
            float speed;
        };

     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void DrawScene(glm::mat3 visMatrix);
        void DrawMiniMap(glm::mat3 visMatrix);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;

        glm::mat3 VisualizationTransf2DUnif(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);
        void SetViewportArea(const ViewportSpace &viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

        void DrawCharacter(glm::mat3 visMatrix);
        void DrawBullets(glm::mat3 visMatrix);
        void MoveBullets(float deltaTimeSeconds);

        void DrawObstacles(glm::mat3 visMatrix);
        void DrawBuilding(glm::mat3 visMatrix);
        bool RestrictedArea(float x, float y, float radius);

        void GenerateEnemies();
        void MoveEnemies(float deltaTimeSeconds);
        void DrawEnemy(glm::mat3 visMatrix, Enemy inamic);
        void DrawEnemies(glm::mat3 visMatrix);
        void EnemyProjectileContact();

        void DrawHPBar(glm::mat3 visMatrix);
        void DrawScore(glm::mat3 visMatrix);

        void DrawPickUp(glm::mat3 visMatrix);
        void DrawRecovery_PickUp(glm::mat3 visMatrix);
        void DrawShotGun_PickUp(glm::mat3 visMatrix);
        void DrawGodMode_PickUp(glm::mat3 visMatrix);
        void DrawAnimation(glm::mat3 visMatrix);

     protected:
        float length;
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        ViewportSpace viewSpaceMiniMap;
        LogicSpace logicSpaceMiniMap;
        glm::mat3 modelMatrix, visMatrix;
        float grades = 360.0 / (CIRCLE_NUMBER - 1) * 0.0174532925;
        glm::vec3 character;
        float angularStep;

        std::vector<Projectile> proiectile;
        time_t projectile_begin;
        time_t projectile_end;

        std::vector<Enemy> enemies;
        time_t enemy_begin;
        time_t enemy_end;

        int hp;
        int score;
        float hp_x;
        float hp_y;
        float score_x;
        float score_y;

        bool animation;
        float animatie_y;

        bool active_pickup;
        bool waiting_pickup;
        bool recharge_pickup;

        string culoare_pickup;
        int pickup_type;
        float pickup_x;
        float pickup_y;
        bool shotGun;
        bool godMode;

        time_t pickup_begin;
        time_t pickup_end;
        int cooldown;
        float efect_time;
    };
}   // namespace m1
