/**
 * @file Objects.hpp
 * @author ADAMOUMOU
 * @brief CitroFlex game objects implementation
 * @version 0.1
 * 
 * @copyright Copyright (c) 2024 ADAMOUMOU
 * This project is released under the MIT License.
 * See the LICENSE file for details.
 */

#include <Objects.hpp>

using namespace Objects;


double Object::get_x() { return x; }
void Object::SetX( double new_x ) { 
    x = new_x;
    if (!attachedElements.empty()) {  // Only update if there are attached elements
        UpdateAttached();
    }
}
void Object::AddX( double add_x ) { 
    x += add_x;
    UpdateAttached();
}

double Object::get_y() { return y; }
void Object::SetY( double new_y ) { 
    y = new_y;
    if (!attachedElements.empty()) {  // Only update if there are attached elements
        UpdateAttached();
    }
}
void Object::AddY( double add_y ) { 
    y += add_y;
    UpdateAttached();
}

void Object::UpdateAttached() {
    for (Object* element : attachedElements) {
        element->x = x + element->relativeX;
        element->y = y + element->relativeY;
        
        // Propagate to children
        element->UpdateAttached();
    }
}

void Object::Update( Scene::Scene* scene ) {
    OnUpdate(scene);
}

void Object::Init() {
}

void Object::Attach(Object *obj) {
    // Calculate relative position
    obj->relativeX = obj->get_x() - x;
    obj->relativeY = obj->get_y() - y;
    
    obj->parent = this;
    attachedElements.push_back(obj);
}

void Object::SetRelativePosition(double x, double y) {
    relativeX = x;
    relativeY = y;
}

void Rectangle::Update( Scene::Scene* scene ) {
    Object::Update(scene);
    if (!visible) return;
    C2D_DrawRectSolid(get_x(), get_y(), 0, width, height, color);
}

void Line::Update( Scene::Scene* scene ) {
    Object::Update(scene);
    if (!visible) return;
    C2D_DrawLine(get_x(), get_y(), color, 
                endX, endY, color, 
                thickness, 0.0f);
}

void Line::SetEndPoint(double x, double y) {
    endX = x;
    endY = y;
}

void Circle::Update( Scene::Scene* scene ) {
    Object::Update(scene);
    if (!visible) return;
    C2D_DrawCircleSolid(get_x(), get_y(), 0, radius, color);
}

void Ellipse::Update( Scene::Scene* scene ) {
    Object::Update(scene);
    if (!visible) return;
    C2D_DrawEllipseSolid(get_x(), get_y(), 0, width, height, color);
}

Sprite::~Sprite() {
    if (spriteSheet) {
        C2D_SpriteSheetFree(spriteSheet);
    }
}

bool Sprite::LoadFromFile(const char* path) {
    spriteSheet = C2D_SpriteSheetLoad(path);
    if (!spriteSheet) return false;
    
    C2D_SpriteFromSheet(&sprite, spriteSheet, frameIndex);
    C2D_SpriteSetCenter(&sprite, 0.5f, 0.5f);
    C2D_SpriteSetPos(&sprite, get_x(), get_y());
    return true;
}

void Sprite::SetFrame(int index) {
    if (spriteSheet) {
        frameIndex = index;
        C2D_SpriteFromSheet(&sprite, spriteSheet, frameIndex);
    }
}

void Sprite::Update( Scene::Scene* scene ) {
    Object::Update(scene);
    if (!visible) return;
    if (spriteSheet) {
        C2D_SpriteSetPos(&sprite, get_x(), get_y());
        C2D_SpriteSetRotation(&sprite, angle * M_PI / 180.0);
        C2D_DrawSprite(&sprite);
    }
}

double Sprite::getAngle() { 
    return angle; 
}

void Sprite::SetAngle(double new_angle) { 
    angle = new_angle;
}

void Sprite::AddAngle(double add_angle) { 
    angle += add_angle;
}
