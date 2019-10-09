#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class Camera {
    public:
        Camera(glm::vec3 pos)
        : clock_(sf::Clock())
        , lastFrame_(clock_.getElapsedTime().asSeconds())
        , deltaTime_(0.0f)
        , speed_(0.05f)
        , pitch_(0.0f)
        , yaw_(90.0f)
        , pos_(pos)
        , up_(glm::vec3(0.0f, 1.0f, 0.0f))
        , front_(glm::vec3(cos(glm::radians(yaw_)), sin(glm::radians(pitch_)), sin(glm::radians(yaw_))))
        , view_(glm::lookAt(pos_, pos_ + front_, up_)) {}
        Camera() = default;

        void moveForward() {
            pos_ += speed_ * front_;
            view_ = glm::lookAt(pos_, pos_ + front_, up_);
        }
        void moveBack() {
            pos_ -= speed_ * front_;
            view_ = glm::lookAt(pos_, pos_ + front_, up_);
        }
        void moveRight() {
            pos_ += speed_ * glm::normalize(glm::cross(front_, up_));
            view_ = glm::lookAt(pos_, pos_ + front_, up_);
        }
        void moveLeft() {
            pos_ -= speed_ * glm::normalize(glm::cross(front_, up_));
            view_ = glm::lookAt(pos_, pos_ + front_, up_);
        }
        void moveUp() {
            pos_ += speed_ * up_;
            view_ = glm::lookAt(pos_, pos_ + front_, up_);
        }
        void moveDown() {
            pos_ -= speed_ * up_;
            view_ = glm::lookAt(pos_, pos_ + front_, up_);
        }
        void mouseMove(sf::Vector2i mouseOffset) {
            yaw_ += -mouseOffset.x * mouseSensitivity_;
            pitch_ += mouseOffset.y * mouseSensitivity_;

            if (pitch_ > 89.0f) {
                pitch_ = 89.0f;
            } else if (pitch_ < -89.0f) {
                pitch_ = -89.0f;
            }

            front_.x = cos(glm::radians(pitch_)) * cos(glm::radians(yaw_));
            front_.y = sin(glm::radians(pitch_));
            front_.z = cos(glm::radians(pitch_)) * sin(glm::radians(yaw_));
            view_ = glm::lookAt(pos_, pos_ + front_, up_);
        }

        glm::mat4 view() {
            currentFrame_ = clock_.getElapsedTime().asSeconds();
            deltaTime_ = currentFrame_ - lastFrame_;
            lastFrame_ = currentFrame_;
            speed_  = 15.0f * deltaTime_;
            return view_;
        }
    private:
        static float mouseSensitivity_;
        sf::Clock clock_;
        float deltaTime_;
        float lastFrame_;
        float currentFrame_;
        float speed_;
        float pitch_;
        float yaw_;
        glm::vec3 pos_;
        glm::vec3 up_;
        glm::vec3 front_;
        glm::mat4 view_;
};

float Camera::mouseSensitivity_ = 0.05f;

#endif
