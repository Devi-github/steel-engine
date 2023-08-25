#pragma once

#include <glm/glm.hpp>

class IArrow {
public:
    virtual void draw(glm::vec3 position) = 0;
};

class MoveArrow : public IArrow {
public:
    MoveArrow();
    ~MoveArrow();
    void draw(glm::vec3 position) override;

    bool XBB(glm::vec3 origin, glm::vec3 position, glm::vec3 direction);
    bool YBB(glm::vec3 origin, glm::vec3 position, glm::vec3 direction);
    bool ZBB(glm::vec3 origin, glm::vec3 position, glm::vec3 direction);

    bool x_highlight = false;
    bool y_highlight = false;
    bool z_highlight = false;

    static MoveArrow* instance;

private:
    GLuint vbo, vao;
};

void setup_arrows();

void draw_move_arrows(glm::vec3 position);
void draw_scale_arrows(glm::vec3 position);
void draw_rotate_sphere(glm::vec3 position);
