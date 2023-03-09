#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/tema1/transform2D.h"

using namespace std;
using namespace m1;


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    auto camera = GetSceneCamera();
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    logicSpace.x = -3.5;      
    logicSpace.y = -3.5;       
    logicSpace.width = 7;   
    logicSpace.height = 7;

    logicSpaceMiniMap.x = -10;
    logicSpaceMiniMap.y = -12;
    logicSpaceMiniMap.width = 20;
    logicSpaceMiniMap.height = 24;

    character = glm::vec3(0, 0, 0);

    angularStep = 0;

    projectile_begin = 0;
    enemy_begin = 0;

    hp_x = 4.5f;
    hp_y = 2.5f;
    hp = 4;

    score_x = 4.5f;
    score_y = 1.7f;
    score = 0;

    animatie_y = 0;
    animation = false;
    active_pickup = false;
    waiting_pickup = false;
    recharge_pickup = true;
    pickup_begin = 0;
    cooldown = 1;
    shotGun = false;
    godMode = false;

    //orange square
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5f, -0.5f,  0), glm::vec3(1, 0.5, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, -0.5f,  0), glm::vec3(1, 0.5, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-0.5f, 0.5f,  0), glm::vec3(1, 0.5, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, 0.5f,  0), glm::vec3(1, 0.5, 0), glm::vec3(0.2, 0.8, 0.6))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            2, 1, 3
        };

        meshes["orange_square"] = new Mesh("orange_square");
        meshes["orange_square"]->SetDrawMode(GL_TRIANGLES);
        meshes["orange_square"]->InitFromData(vertices, indices);
    }

    //weird square
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5f, -0.5f,  0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, -0.5f,  0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-0.5f, 0.5f,  0), glm::vec3(1, 0.08, 0.57), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, 0.5f,  0), glm::vec3(1, 0.08, 0.57), glm::vec3(0.2, 0.8, 0.6))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            2, 1, 3
        };

        meshes["weird_square"] = new Mesh("weird_square");
        meshes["weird_square"]->SetDrawMode(GL_TRIANGLES);
        meshes["weird_square"]->InitFromData(vertices, indices);
    }

    //black square
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5f, -0.5f,  0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, -0.5f,  0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-0.5f, 0.5f,  0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, 0.5f,  0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            2, 1, 3
        };

        meshes["black_square"] = new Mesh("black_square");
        meshes["black_square"]->SetDrawMode(GL_TRIANGLES);
        meshes["black_square"]->InitFromData(vertices, indices);
    }

    //yellow square
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5f, -0.5f,  0), glm::vec3(1, 0.9, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, -0.5f,  0), glm::vec3(1, 0.9, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-0.5f, 0.5f,  0), glm::vec3(1, 0.9, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, 0.5f,  0), glm::vec3(1, 0.9, 0), glm::vec3(0.2, 0.8, 0.6))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            2, 1, 3
        };

        meshes["yellow_square"] = new Mesh("yellow_square");
        meshes["yellow_square"]->SetDrawMode(GL_TRIANGLES);
        meshes["yellow_square"]->InitFromData(vertices, indices);
    }

    //brown square
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5f, -0.5f,  0), glm::vec3(0.54, 0.27, 0.07), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, -0.5f,  0), glm::vec3(0.54, 0.27, 0.07), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-0.5f, 0.5f,  0), glm::vec3(0.54, 0.27, 0.07), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, 0.5f,  0), glm::vec3(0.54, 0.27, 0.07), glm::vec3(0.2, 0.8, 0.6))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            2, 1, 3
        };

        meshes["brown_square"] = new Mesh("brown_square");
        meshes["brown_square"]->SetDrawMode(GL_TRIANGLES);
        meshes["brown_square"]->InitFromData(vertices, indices);
    }

    //white square
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5f, -0.5f,  0), glm::vec3(1, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, -0.5f,  0), glm::vec3(1, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-0.5f, 0.5f,  0), glm::vec3(1, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, 0.5f,  0), glm::vec3(1, 1, 1), glm::vec3(0.2, 0.8, 0.6))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            2, 1, 3
        };

        meshes["white_square"] = new Mesh("white_square");
        meshes["white_square"]->SetDrawMode(GL_TRIANGLES);
        meshes["white_square"]->InitFromData(vertices, indices);
    }

    //green square
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5f, -0.5f,  0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, -0.5f,  0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-0.5f, 0.5f,  0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, 0.5f,  0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            2, 1, 3
        };

        meshes["green_square"] = new Mesh("green_square");
        meshes["green_square"]->SetDrawMode(GL_TRIANGLES);
        meshes["green_square"]->InitFromData(vertices, indices);
    }

    //red square
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5f, -0.5f,  0), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, -0.5f,  0), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-0.5f, 0.5f,  0), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, 0.5f,  0), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            2, 1, 3
        };

        meshes["red_square"] = new Mesh("red_square");
        meshes["red_square"]->SetDrawMode(GL_TRIANGLES);
        meshes["red_square"]->InitFromData(vertices, indices);
    }

    //blue square
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5f, -0.5f,  0), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, -0.5f,  0), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-0.5f, 0.5f,  0), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, 0.5f,  0), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            2, 1, 3
        };

        meshes["blue_square"] = new Mesh("blue_square");
        meshes["blue_square"]->SetDrawMode(GL_TRIANGLES);
        meshes["blue_square"]->InitFromData(vertices, indices);
    }

    //yellow circle
    {
        vector<VertexFormat> vertices;
        vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)));
        vertices.push_back(VertexFormat(glm::vec3(1, 0, 0), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)));
        for (int i = 2; i < CIRCLE_NUMBER; i++) {
            vertices.push_back(VertexFormat(glm::vec3(cos(grades * i), sin(grades * i), 0), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)));
        }


        vector<unsigned int> indices;
        for (int i = 0; i < CIRCLE_NUMBER; i++) {
            indices.push_back(i);
        }

        indices.push_back(1);

        meshes["yellow_circle"] = new Mesh("yellow_circle");
        meshes["yellow_circle"]->SetDrawMode(GL_TRIANGLE_FAN);
        meshes["yellow_circle"]->InitFromData(vertices, indices);
    }

    //black circle
    {
        vector<VertexFormat> vertices;
        vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)));
        vertices.push_back(VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)));
        for (int i = 2; i < CIRCLE_NUMBER; i++) {
            vertices.push_back(VertexFormat(glm::vec3(cos(grades * i), sin(grades * i), 0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)));
        }


        vector<unsigned int> indices;
        for (int i = 0; i < CIRCLE_NUMBER; i++) {
            indices.push_back(i);
        }

        indices.push_back(1);

        meshes["black_circle"] = new Mesh("black_circle");
        meshes["black_circle"]->SetDrawMode(GL_TRIANGLE_FAN);
        meshes["black_circle"]->InitFromData(vertices, indices);
    }

    //green circle
    {
        vector<VertexFormat> vertices;
        vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0.65), glm::vec3(0.2, 0.8, 0.6)));
        vertices.push_back(VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0.65), glm::vec3(0.2, 0.8, 0.6)));
        for (int i = 2; i < CIRCLE_NUMBER; i++) {
            vertices.push_back(VertexFormat(glm::vec3(cos(grades * i), sin(grades * i), 0), glm::vec3(0, 1, 0.65), glm::vec3(0.2, 0.8, 0.6)));
        }


        vector<unsigned int> indices;
        for (int i = 0; i < CIRCLE_NUMBER; i++) {
            indices.push_back(i);
        }

        indices.push_back(1);

        meshes["green_circle"] = new Mesh("green_circle");
        meshes["green_circle"]->SetDrawMode(GL_TRIANGLE_FAN);
        meshes["green_circle"]->InitFromData(vertices, indices);
    }

    //greener circle
    {
        vector<VertexFormat> vertices;
        vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6)));
        vertices.push_back(VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6)));
        for (int i = 2; i < CIRCLE_NUMBER; i++) {
            vertices.push_back(VertexFormat(glm::vec3(cos(grades * i), sin(grades * i), 0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6)));
        }


        vector<unsigned int> indices;
        for (int i = 0; i < CIRCLE_NUMBER; i++) {
            indices.push_back(i);
        }

        indices.push_back(1);

        meshes["greener_circle"] = new Mesh("greener_circle");
        meshes["greener_circle"]->SetDrawMode(GL_TRIANGLE_FAN);
        meshes["greener_circle"]->InitFromData(vertices, indices);
    }

    //red circle
    {
        vector<VertexFormat> vertices;
        vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)));
        vertices.push_back(VertexFormat(glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)));
        for (int i = 2; i < CIRCLE_NUMBER; i++) {
            vertices.push_back(VertexFormat(glm::vec3(cos(grades * i), sin(grades * i), 0), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)));
        }


        vector<unsigned int> indices;
        for (int i = 0; i < CIRCLE_NUMBER; i++) {
            indices.push_back(i);
        }

        indices.push_back(1);

        meshes["red_circle"] = new Mesh("red_circle");
        meshes["red_circle"]->SetDrawMode(GL_TRIANGLE_FAN);
        meshes["red_circle"]->InitFromData(vertices, indices);
    }

    //blue circle
    {
        vector<VertexFormat> vertices;
        vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)));
        vertices.push_back(VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)));
        for (int i = 2; i < CIRCLE_NUMBER; i++) {
            vertices.push_back(VertexFormat(glm::vec3(cos(grades * i), sin(grades * i), 0), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)));
        }


        vector<unsigned int> indices;
        for (int i = 0; i < CIRCLE_NUMBER; i++) {
            indices.push_back(i);
        }

        indices.push_back(1);

        meshes["blue_circle"] = new Mesh("blue_circle");
        meshes["blue_circle"]->SetDrawMode(GL_TRIANGLE_FAN);
        meshes["blue_circle"]->InitFromData(vertices, indices);
    }

    //weird triangle
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5f, 0, 0), glm::vec3(1,1,1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 1, 0), glm::vec3(1, 0.08, 0.57), glm::vec3(0.2, 0.8, 0.6)),
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
        };

        meshes["weird_triangle"] = new Mesh("weird_triangle");
        meshes["weird_triangle"]->SetDrawMode(GL_TRIANGLES);
        meshes["weird_triangle"]->InitFromData(vertices, indices);
    }

    //weird triangle 2
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5f, 0, 0), glm::vec3(1,0,0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 1, 0), glm::vec3(1, 0.08, 0.57), glm::vec3(0.2, 0.8, 0.6)),
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
        };

        meshes["weird_triangle2"] = new Mesh("weird_triangle2");
        meshes["weird_triangle2"]->SetDrawMode(GL_TRIANGLES);
        meshes["weird_triangle2"]->InitFromData(vertices, indices);
    }

    //outline triangle
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5f, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
        };

        meshes["outline_triangle"] = new Mesh("outline_triangle");
        meshes["outline_triangle"]->SetDrawMode(GL_TRIANGLES);
        meshes["outline_triangle"]->InitFromData(vertices, indices);
    }

    //orange triangle
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5f, 0, 0), glm::vec3(1, 0.7, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, 0, 0), glm::vec3(1, 0.7, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 1, 0), glm::vec3(1, 0.7, 0), glm::vec3(0.2, 0.8, 0.6)),
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
        };

        meshes["orange_triangle"] = new Mesh("orange_triangle");
        meshes["orange_triangle"]->SetDrawMode(GL_TRIANGLES);
        meshes["orange_triangle"]->InitFromData(vertices, indices);
    }

    //black triangle
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5f, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
        };

        meshes["black_triangle"] = new Mesh("black_triangle");
        meshes["black_triangle"]->SetDrawMode(GL_TRIANGLES);
        meshes["black_triangle"]->InitFromData(vertices, indices);
    }

    //wireframe
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5f, -0.5f,  0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, -0.5f,  0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-0.5f, 0.5f,  0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, 0.5f,  0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6))
        };

        vector<unsigned int> indices =
        {
            0, 1, 3, 2
        };

        meshes["wireframe"] = new Mesh("wireframe");
        meshes["wireframe"]->SetDrawMode(GL_LINE_LOOP);
        meshes["wireframe"]->InitFromData(vertices, indices);
    }

}


glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}


void Tema1::SetViewportArea(const ViewportSpace & viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();

    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0.5f, 0.5f, 0.5f), true);

    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);

    if (hp > 0) {
        MoveBullets(deltaTimeSeconds);
        MoveEnemies(deltaTimeSeconds);
        GenerateEnemies();

        if (animation) {
            animatie_y += deltaTimeSeconds * 0.35f;
        }
    }

    DrawScene(visMatrix);

    viewSpaceMiniMap = ViewportSpace(0, 0, 220, 240);
    SetViewportArea(viewSpaceMiniMap, glm::vec3(0.5f, 0.5f, 0.5f), true);

    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpaceMiniMap, viewSpaceMiniMap);

    DrawMiniMap(visMatrix);


}


void Tema1::FrameEnd()
{
}


bool Tema1::RestrictedArea(float x, float y, float radius) {
    if (y <= -11 + radius || y >= 11 - radius) return true;
    if (x <= -10 + radius || x >= 10 - radius) return true;
    if (x <= -7 + radius && x >= -8 - radius &&
        y >= -9 - radius && y <= -2 + radius) return true;
    if (x >= -5.25 - radius && x <= -0.75 + radius &&
        y >= 4.25 - radius && y <= 8.75 + radius) return true;
    if (x >= 2 - radius && x <= 7 + radius &&
        y >= 3 - radius && y <= 4 + radius) return true;
    if (x >= 7 - radius && x <= 8 + radius &&
        y >= 3 - radius && y <= 7 + radius) return true;
    if (x >= 6 - radius && x <= 8 + radius &&
        y >= -9 - radius && y <= -7 + radius) return true;

    return false;
}


void Tema1::DrawCharacter(glm::mat3 visMatrix) {
    string culoare_body = "yellow_circle";
    string culoare_maini = "green_circle";
    string culoare_corn = "weird_triangle";

    if (godMode) {
        culoare_body = "green_circle";
        culoare_maini = "yellow_circle";
        culoare_corn = "weird_triangle2";
    }

    //horn
    modelMatrix = visMatrix;

    modelMatrix *= transform2D::Translate(character.x, character.y);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-character.x, -character.y);

    modelMatrix *= transform2D::Translate(character.x, character.y + 0.05f);
    modelMatrix *= transform2D::Scale(0.15f, 0.5f);
    RenderMesh2D(meshes[culoare_corn], shaders["VertexColor"], modelMatrix);
    
    //body
    modelMatrix = visMatrix;

    modelMatrix *= transform2D::Translate(character.x, character.y);
    modelMatrix *= transform2D::Scale(0.5f, 0.5f);
    RenderMesh2D(meshes[culoare_body], shaders["VertexColor"], modelMatrix);

    //arms
    modelMatrix = visMatrix;

    modelMatrix *= transform2D::Translate(character.x, character.y);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-character.x, -character.y);

    modelMatrix *= transform2D::Translate(character.x - 0.5f, character.y + 0.3f);
    modelMatrix *= transform2D::Scale(0.1f, 0.1f);
    RenderMesh2D(meshes[culoare_maini], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;

    modelMatrix *= transform2D::Translate(character.x, character.y);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-character.x, -character.y);

    modelMatrix *= transform2D::Translate(character.x + 0.5f, character.y + 0.3f);
    modelMatrix *= transform2D::Scale(0.1f, 0.1f);
    RenderMesh2D(meshes[culoare_maini], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;

    modelMatrix *= transform2D::Translate(character.x, character.y);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-character.x, -character.y);

    modelMatrix *= transform2D::Translate(character.x + 0.5f, character.y - 0.3f);
    modelMatrix *= transform2D::Scale(0.1f, 0.1f);
    RenderMesh2D(meshes[culoare_maini], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;

    modelMatrix *= transform2D::Translate(character.x, character.y);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-character.x, -character.y);

    modelMatrix *= transform2D::Translate(character.x - 0.5f, character.y - 0.3f);
    modelMatrix *= transform2D::Scale(0.1f, 0.1f);
    RenderMesh2D(meshes[culoare_maini], shaders["VertexColor"], modelMatrix);
    
    //outline
    modelMatrix = visMatrix;

    modelMatrix *= transform2D::Translate(character.x, character.y);
    modelMatrix *= transform2D::Scale(0.53f, 0.53f);
    RenderMesh2D(meshes["black_circle"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;

    modelMatrix *= transform2D::Translate(character.x, character.y);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-character.x, -character.y);

    modelMatrix *= transform2D::Translate(character.x, character.y + 0.05f);
    modelMatrix *= transform2D::Scale(0.3f, 0.6f);
    RenderMesh2D(meshes["outline_triangle"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;

    modelMatrix *= transform2D::Translate(character.x, character.y);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-character.x, -character.y);

    modelMatrix *= transform2D::Translate(character.x - 0.5f, character.y + 0.3f);
    modelMatrix *= transform2D::Scale(0.13f, 0.13f);
    RenderMesh2D(meshes["black_circle"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;

    modelMatrix *= transform2D::Translate(character.x, character.y);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-character.x, -character.y);

    modelMatrix *= transform2D::Translate(character.x + 0.5f, character.y + 0.3f);
    modelMatrix *= transform2D::Scale(0.13f, 0.13f);
    RenderMesh2D(meshes["black_circle"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;

    modelMatrix *= transform2D::Translate(character.x, character.y);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-character.x, -character.y);

    modelMatrix *= transform2D::Translate(character.x + 0.5f, character.y - 0.3f);
    modelMatrix *= transform2D::Scale(0.13f, 0.13f);
    RenderMesh2D(meshes["black_circle"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;

    modelMatrix *= transform2D::Translate(character.x, character.y);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-character.x, -character.y);

    modelMatrix *= transform2D::Translate(character.x - 0.5f, character.y - 0.3f);
    modelMatrix *= transform2D::Scale(0.13f, 0.13f);
    RenderMesh2D(meshes["black_circle"], shaders["VertexColor"], modelMatrix);
}


void Tema1::DrawBuilding(glm::mat3 visMatrix) {
    modelMatrix = visMatrix * transform2D::Translate(-10.5, 0) * transform2D::Scale(1, 24);
    RenderMesh2D(meshes["orange_square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(10.5, 0) * transform2D::Scale(1, 24);
    RenderMesh2D(meshes["orange_square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(0, 11.5) * transform2D::Scale(20, 1);
    RenderMesh2D(meshes["orange_square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(0, -11.5) * transform2D::Scale(20, 1);
    RenderMesh2D(meshes["orange_square"], shaders["VertexColor"], modelMatrix);
}


void Tema1::MoveBullets(float deltaTimeSeconds) {
    for (auto it = proiectile.begin(); it < proiectile.end();) {
        it->x += deltaTimeSeconds * cos(it->angle + M_PI_2) * 7;
        it->y += deltaTimeSeconds * sin(it->angle + M_PI_2) * 7;

        int distance = 5;
        if (shotGun) {
            distance = 3;
        }
        else if (godMode) {
            distance = 7.5f;
        }

        if (sqrt(pow(it->x_start - it->x, 2) + pow(it->y_start - it->y, 2)) >= distance) {
            it = proiectile.erase(it);
        }
        else if (RestrictedArea(it->x, it->y, 0.1)) {
            it = proiectile.erase(it);
        }
        else {
            it++;
        }
    }
}


void Tema1::DrawBullets(glm::mat3 visMatrix) {
    for (auto it = proiectile.begin(); it < proiectile.end(); it++) {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(it->x, it->y);
        modelMatrix *= transform2D::Scale(0.25f, 0.25f);
        modelMatrix *= transform2D::Rotate(it->angle);
        RenderMesh2D(meshes["weird_square"], shaders["VertexColor"], modelMatrix);
    }
}


void Tema1::DrawObstacles(glm::mat3 visMatrix) {
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(-7.5, -5.5);
    modelMatrix *= transform2D::Scale(1, 7);
    RenderMesh2D(meshes["brown_square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(-3, 6.5);
    modelMatrix *= transform2D::Scale(4.5, 4.5);
    RenderMesh2D(meshes["brown_square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(4.5, 3.5);
    modelMatrix *= transform2D::Scale(5, 1);
    RenderMesh2D(meshes["brown_square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(7.5, 5);
    modelMatrix *= transform2D::Scale(1, 4);
    RenderMesh2D(meshes["brown_square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(7, -8);
    modelMatrix *= transform2D::Scale(2, 2);
    RenderMesh2D(meshes["brown_square"], shaders["VertexColor"], modelMatrix);
}


void Tema1::GenerateEnemies() {
    time(&enemy_end);
    if (difftime(enemy_end, enemy_begin) <= 1) return;
    enemy_begin = enemy_end;
    
    if (character.x < 0 && character.y < 0) {
        float x = rand() % 7 + 2;
        float y = rand() % 7 + 2;
        float speed = rand() % 4 + 0.85f;
        float angle = 0;
        Enemy inamic(x, y, angle, speed);
        enemies.push_back(inamic);
    }

    if (character.x < 0 && character.y > 0) {
        float x = rand() % 7 + 2;
        float y = (-1) * (rand() % 7 + 2);
        float speed = rand() % 4 + 0.85f;
        float angle = 0;
        Enemy inamic(x, y, angle, speed);
        enemies.push_back(inamic);
    }

    if (character.x > 0 && character.y < 0) {
        float x = (-1) * (rand() % 7 + 2);
        float y = rand() % 7 + 2;
        float speed = rand() % 4 + 0.85f;
        float angle = 0;
        Enemy inamic(x, y, angle, speed);
        enemies.push_back(inamic);
    }

    if (character.x >= 0 && character.y >= 0) {
        float x = (-1) * (rand() % 7 + 2);
        float y = (-1) * (rand() % 7 + 2);
        float speed = rand() % 4 + 0.85f;
        float angle = 0;
        Enemy inamic(x, y, angle, speed);
        enemies.push_back(inamic);
    }
}


void Tema1::MoveEnemies(float deltaTimeSeconds) {
    for (auto it = enemies.begin(); it < enemies.end();) {
        glm::ivec2 resolution = window->GetResolution();

        double dx = it->x - character.x;
        double dy = it->y - character.y;

        if (dy < 0) {
            it->angle = -atan(dx / dy);
        }
        else {
            it->angle = M_PI - atan(dx / dy);
        }

        it->x += deltaTimeSeconds * cos(it->angle + M_PI_2) * it->speed;
        it->y += deltaTimeSeconds * sin(it->angle + M_PI_2) * it->speed;

        if (it->y <= -11 + 0.5f || it->y >= 11 - 0.5f ||  it->x <= -10 + 0.5f || it->x >= 10 - 0.5f) {
            it->y -= deltaTimeSeconds * sin(it->angle + M_PI_2) * it->speed;
            it->x -= deltaTimeSeconds * cos(it->angle + M_PI_2) * it->speed;
        }


        if (sqrt(pow(it->x - character.x, 2) + pow(it->y - character.y, 2)) <= 1.4) {
            it = enemies.erase(it);
            if (!godMode) {
                hp--;

                if (hp == 0) {
                    cout << "Score: " << score;
                }
            }
            else {
                score++;
            }
        }
        else {
            it++;
        }
    }
}


void Tema1::DrawEnemy(glm::mat3 visMatrix, Enemy inamic) {
    float inamic_x = inamic.x;
    float inamic_y = inamic.y;
    float inamic_angle = inamic.angle;

    //ochi
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(inamic_x, inamic_y);
    modelMatrix *= transform2D::Rotate(inamic_angle);
    modelMatrix *= transform2D::Translate(-inamic_x, -inamic_y);

    modelMatrix *= transform2D::Translate(inamic_x + 0.215f,inamic_y + 0.285f);
    modelMatrix *= transform2D::Scale(0.03f, 0.03f);
    RenderMesh2D(meshes["white_square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(inamic_x, inamic_y);
    modelMatrix *= transform2D::Rotate(inamic_angle);
    modelMatrix *= transform2D::Translate(-inamic_x, -inamic_y);

    modelMatrix *= transform2D::Translate(inamic_x - 0.285f, inamic_y + 0.285f);
    modelMatrix *= transform2D::Scale(0.03f, 0.03f);
    RenderMesh2D(meshes["white_square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(inamic_x, inamic_y);
    modelMatrix *= transform2D::Rotate(inamic_angle);
    modelMatrix *= transform2D::Translate(-inamic_x, -inamic_y);

    modelMatrix *= transform2D::Translate(inamic_x + 0.23f, inamic_y + 0.27f);
    modelMatrix *= transform2D::Scale(0.08f, 0.08f);
    RenderMesh2D(meshes["black_square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(inamic_x, inamic_y);
    modelMatrix *= transform2D::Rotate(inamic_angle);
    modelMatrix *= transform2D::Translate(-inamic_x, -inamic_y);

    modelMatrix *= transform2D::Translate(inamic_x  - 0.27f, inamic_y + 0.27f);
    modelMatrix *= transform2D::Scale(0.08f, 0.08f);
    RenderMesh2D(meshes["black_square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(inamic_x, inamic_y);
    modelMatrix *= transform2D::Rotate(inamic_angle);
    modelMatrix *= transform2D::Translate(-inamic_x, -inamic_y);

    modelMatrix *= transform2D::Translate(inamic_x + 0.25f, inamic_y + 0.25f);
    modelMatrix *= transform2D::Scale(0.15f, 0.15f);
    RenderMesh2D(meshes["white_square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(inamic_x, inamic_y);
    modelMatrix *= transform2D::Rotate(inamic_angle);
    modelMatrix *= transform2D::Translate(-inamic_x, -inamic_y);

    modelMatrix *= transform2D::Translate(inamic_x  - 0.25f, inamic_y + 0.25f);
    modelMatrix *= transform2D::Scale(0.15f, 0.15f);
    RenderMesh2D(meshes["white_square"], shaders["VertexColor"], modelMatrix);

    //cioc
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(inamic_x, inamic_y);
    modelMatrix *= transform2D::Rotate(inamic_angle);
    modelMatrix *= transform2D::Translate(-inamic_x, -inamic_y);

    modelMatrix *= transform2D::Translate(inamic_x, inamic_y + 0.35f);
    modelMatrix *= transform2D::Scale(0.15f, 0.3f);
    RenderMesh2D(meshes["orange_triangle"], shaders["VertexColor"], modelMatrix);

    //burta
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(inamic_x, inamic_y);
    modelMatrix *= transform2D::Rotate(inamic_angle);
    modelMatrix *= transform2D::Translate(-inamic_x, -inamic_y);

    modelMatrix *= transform2D::Translate(inamic_x, inamic_y + 0.45f);
    modelMatrix *= transform2D::Scale(0.8f, 0.1f);
    RenderMesh2D(meshes["white_square"], shaders["VertexColor"], modelMatrix);

    //body
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(inamic_x, inamic_y);
    modelMatrix *= transform2D::Rotate(inamic_angle);
    modelMatrix *= transform2D::Scale(1, 1);
    RenderMesh2D(meshes["black_square"], shaders["VertexColor"], modelMatrix);

    //picioare
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(inamic_x, inamic_y);
    modelMatrix *= transform2D::Rotate(inamic_angle);
    modelMatrix *= transform2D::Translate(-inamic_x, -inamic_y);

    modelMatrix *= transform2D::Translate(inamic_x - 0.35f, inamic_y + 0.45f);
    modelMatrix *= transform2D::Scale(0.25f, 0.25f);
    RenderMesh2D(meshes["yellow_square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(inamic_x, inamic_y);
    modelMatrix *= transform2D::Rotate(inamic_angle);
    modelMatrix *= transform2D::Translate(-inamic_x, -inamic_y);

    modelMatrix *= transform2D::Translate(inamic_x + 0.35f, inamic_y + 0.45f);
    modelMatrix *= transform2D::Scale(0.25f, 0.25f);
    RenderMesh2D(meshes["yellow_square"], shaders["VertexColor"], modelMatrix);

    //coada
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(inamic_x, inamic_y);
    modelMatrix *= transform2D::Rotate(inamic_angle + 3.14);
    modelMatrix *= transform2D::Translate(-inamic_x, -inamic_y);

    modelMatrix *= transform2D::Translate(inamic_x, inamic_y - 0.43f);
    modelMatrix *= transform2D::Scale(0.15f, 0.15f);
    RenderMesh2D(meshes["black_triangle"], shaders["VertexColor"], modelMatrix);
}


void Tema1::DrawEnemies(glm::mat3 visMatrix) {
    for (auto it = enemies.begin(); it < enemies.end(); it++) {
        DrawEnemy(visMatrix, *it);
    }
}


void Tema1::EnemyProjectileContact() {
    for (auto inamic = enemies.begin(); inamic < enemies.end();) {
        bool eliminat = false;
        for (auto proiectil = proiectile.begin(); proiectil < proiectile.end();) {
            if (sqrt(pow(inamic->x - proiectil->x, 2) + pow(inamic->y - proiectil->y, 2)) <= 0.75f) {
                score++;
                inamic = enemies.erase(inamic);
                eliminat = true;
                proiectile.erase(proiectil);
                break;
            }
            else {
                proiectil++;
            }
        }

        if (!eliminat) {
            inamic++;
        }
    }
}


void Tema1::DrawHPBar(glm::mat3 visMatrix) {
    string culoare = "green_square";

    if (hp == 3 || hp == 2) {
        culoare = "yellow_square";
    }
    else if (hp == 1) {
        culoare = "red_square";
    }
    
    if (hp == 4) {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(hp_x - 0.675f, hp_y);
        modelMatrix *= transform2D::Scale(0.4f, 0.8f);
        RenderMesh2D(meshes[culoare], shaders["VertexColor"], modelMatrix);
    }

    if (hp >= 3) {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(hp_x - 0.225f, hp_y);
        modelMatrix *= transform2D::Scale(0.4f, 0.8f);
        RenderMesh2D(meshes[culoare], shaders["VertexColor"], modelMatrix);
    }

    if (hp >= 2) {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(hp_x + 0.225, hp_y);
        modelMatrix *= transform2D::Scale(0.4f, 0.8f);
        RenderMesh2D(meshes[culoare], shaders["VertexColor"], modelMatrix);
    }

    if (hp >= 1) {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(hp_x + 0.675, hp_y);
        modelMatrix *= transform2D::Scale(0.4f, 0.8f);
        RenderMesh2D(meshes[culoare], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(hp_x - 0.9625f, hp_y);
    modelMatrix *= transform2D::Scale(0.075f, 0.99f);
    RenderMesh2D(meshes["white_square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(hp_x + 0.9625f, hp_y);
    modelMatrix *= transform2D::Scale(0.075f, 0.99f);
    RenderMesh2D(meshes["white_square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(hp_x, hp_y - 0.47f);
    modelMatrix *= transform2D::Scale(1.85f, 0.05f);
    RenderMesh2D(meshes["white_square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(hp_x, hp_y + 0.47f);
    modelMatrix *= transform2D::Scale(1.85f, 0.05f);
    RenderMesh2D(meshes["white_square"], shaders["VertexColor"], modelMatrix);
}


void Tema1::DrawScore(glm::mat3 visMatrix) {
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(score_x, score_y);
    modelMatrix *= transform2D::Scale(2, 0.25f);
    RenderMesh2D(meshes["wireframe"], shaders["VertexColor"], modelMatrix);
    
    string culoare;

    if (score <= 100) {
        culoare = "yellow_square";
    }
    else if (score <= 200) {
        culoare = "orange_square";
    }
    else {
        culoare = "red_square";
    }
    
    int dim = score;

    while (dim > 100) {
        dim %= 100;
    }

    float x = score_x - 1 + (dim / 10.0f) * 0.1;
    float len = (dim / 10.0f) * 0.2f;

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(x, score_y);
    modelMatrix *= transform2D::Scale(len, 0.25f);
    RenderMesh2D(meshes[culoare], shaders["VertexColor"], modelMatrix);
}


void Tema1::DrawAnimation(glm::mat3 visMatrix) {
    if (animation) {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(character.x + 0.5f, character.y + animatie_y);
        modelMatrix *= transform2D::Scale(0.15f, 0.15f);
        RenderMesh2D(meshes[culoare_pickup], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(character.x - 0.6f, character.y + animatie_y - 0.5f);
        modelMatrix *= transform2D::Scale(0.15f, 0.15f);
        RenderMesh2D(meshes[culoare_pickup], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(character.x + 0.4f, character.y + animatie_y - 0.65f);
        modelMatrix *= transform2D::Scale(0.15f, 0.15f);
        RenderMesh2D(meshes[culoare_pickup], shaders["VertexColor"], modelMatrix);

        if (animatie_y >= 0.5f) {
            animation = false;
            animatie_y = 0;
        }
    }
}


void Tema1::DrawRecovery_PickUp(glm::mat3 visMatrix) {
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(pickup_x, pickup_y);
    modelMatrix *= transform2D::Scale(0.25f, 0.25f);
    RenderMesh2D(meshes["greener_circle"], shaders["VertexColor"], modelMatrix);
}


void Tema1::DrawShotGun_PickUp(glm::mat3 visMatrix) {
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(pickup_x, pickup_y);
    modelMatrix *= transform2D::Scale(0.25f, 0.25f);
    RenderMesh2D(meshes["blue_circle"], shaders["VertexColor"], modelMatrix);
}


void Tema1::DrawGodMode_PickUp(glm::mat3 visMatrix) {
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(pickup_x, pickup_y);
    modelMatrix *= transform2D::Scale(0.25f, 0.25f);
    RenderMesh2D(meshes["red_circle"], shaders["VertexColor"], modelMatrix);
}


void Tema1::DrawPickUp(glm::mat3 visMatrix) {
    if (recharge_pickup) {
        time(&pickup_end);

        if (difftime(pickup_end, pickup_begin) >= cooldown) {
            waiting_pickup = true;
            recharge_pickup = false;

            pickup_type = (int)rand() % 10 + 1;

            if (pickup_type <= 5) {
                pickup_type = 1;
            }
            else if (pickup_type <= 8) {
                pickup_type = 2;
            }
            else {
                pickup_type = 3;
            }

            int location = (int)(rand() % 3);

            switch (location) {
            case 0:
                pickup_x = 3;
                pickup_y = 2;
                break;
            case 1:
                pickup_x = -2;
                pickup_y = -9;
                break;
            case 2:
                pickup_x = 6;
                pickup_y = -5;
                break;
            }
        }
    }

    if (waiting_pickup) {
        switch (pickup_type) {
        case 1:
            DrawRecovery_PickUp(visMatrix);
            break;
        case 2:
            DrawShotGun_PickUp(visMatrix);
            break;
        case 3:
            DrawGodMode_PickUp(visMatrix);
            break;
        }

        if (sqrt(pow(character.x - pickup_x, 2) + pow(character.y - pickup_y, 2)) <= 1) {
            waiting_pickup = false;
            active_pickup = true;
            animation = true;
            time(&pickup_begin);

            switch (pickup_type) {
            case 1:
                culoare_pickup = "white_square";
                hp = 4;
                efect_time = 0;
                cooldown = 3.5f;
                break;
            case 2:
                culoare_pickup = "blue_square";
                shotGun = true;
                efect_time = 7.5f;
                cooldown = 7.5f;
                break;
            case 3:
                culoare_pickup = "red_square";
                godMode = true;
                efect_time = 7.5f;
                cooldown = 15;
                break;
            }
        }
    }

    if (active_pickup) {
        time(&pickup_end);
        if (difftime(pickup_end, pickup_begin) >= efect_time) {
            shotGun = false;
            godMode = false;
            active_pickup = false;
            recharge_pickup = true;
            pickup_begin = pickup_end;
        }
    }
}


void Tema1::DrawScene(glm::mat3 visMatrix)
{
    DrawAnimation(visMatrix);

    DrawCharacter(visMatrix);

    DrawHPBar(visMatrix);

    DrawScore(visMatrix);
    
    DrawBuilding(visMatrix);

    EnemyProjectileContact();

    DrawBullets(visMatrix);

    DrawEnemies(visMatrix);

    DrawObstacles(visMatrix);

    DrawPickUp(visMatrix);
}


void Tema1::DrawMiniMap(glm::mat3 visMatrix) {
    DrawCharacter(visMatrix);

    DrawBuilding(visMatrix);

    EnemyProjectileContact();

    DrawBullets(visMatrix);

    DrawEnemies(visMatrix);

    DrawObstacles(visMatrix);

    DrawPickUp(visMatrix);
}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    if (hp > 0) {
        if (window->MouseHold(GLFW_MOUSE_BUTTON_1) && godMode) {
            Projectile proiectil(character.x, character.y, angularStep);
            proiectile.push_back(proiectil);
        }
        
        if (window->KeyHold(GLFW_KEY_W)) {
            logicSpace.y += deltaTime * 5;
            character.y += deltaTime * 5;
            hp_y += deltaTime * 5;
            score_y += deltaTime * 5;
            if (RestrictedArea(character.x, character.y, 0.75)) {
                logicSpace.y -= deltaTime * 5;
                character.y -= deltaTime * 5;
                hp_y -= deltaTime * 5;
                score_y -= deltaTime * 5;
            }
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            logicSpace.y -= deltaTime * 5;
            character.y -= deltaTime * 5;
            hp_y -= deltaTime * 5;
            score_y -= deltaTime * 5;
            if (RestrictedArea(character.x, character.y, 0.75)) {
                logicSpace.y += deltaTime * 5;
                character.y += deltaTime * 5;
                hp_y += deltaTime * 5;
                score_y += deltaTime * 5;
            }
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            logicSpace.x += deltaTime * 5;
            character.x += deltaTime * 5;
            hp_x += deltaTime * 5;
            score_x += deltaTime * 5;
            if (RestrictedArea(character.x, character.y, 0.75)) {
                logicSpace.x -= deltaTime * 5;
                character.x -= deltaTime * 5;
                hp_x -= deltaTime * 5;
                score_x -= deltaTime * 5;
            }
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            logicSpace.x -= deltaTime * 5;
            character.x -= deltaTime * 5;
            hp_x -= deltaTime * 5;
            score_x -= deltaTime * 5;
            if (RestrictedArea(character.x, character.y, 0.75)) {
                logicSpace.x += deltaTime * 5;
                character.x += deltaTime * 5;
                hp_x += deltaTime * 5;
                score_x += deltaTime * 5;
            }
        }
    }
}


void Tema1::OnKeyPress(int key, int mods)
{
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    if (hp > 0) {
        glm::ivec2 resolution = window->GetResolution();
        double dx = mouseX - character.x - resolution.x / 2;
        double dy = mouseY - character.y - resolution.y / 2;

        if (dy < 0) {
            angularStep = atan(dx / dy);
        }
        else {
            angularStep = M_PI + atan(dx / dy);
        }
    }
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (button == 1 && !godMode) {
        time(&projectile_end);
        if (difftime(projectile_end, projectile_begin) <= 0.5f) return;
        projectile_begin = projectile_end;
        Projectile proiectil(character.x, character.y, angularStep);
        proiectile.push_back(proiectil);

        if (active_pickup && pickup_type == 2) {
            Projectile proiectil1(character.x, character.y, angularStep + RADIANS(15));
            Projectile proiectil2(character.x, character.y, angularStep - RADIANS(15));
            proiectile.push_back(proiectil1);
            proiectile.push_back(proiectil2);
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}
