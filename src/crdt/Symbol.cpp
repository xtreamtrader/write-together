/*
 * Author: Franco Ruggeri
 */

#include "Symbol.h"

namespace collaborative_text_editor {
    Symbol::Symbol(char value, int site_id, int site_counter, const std::vector<int>& position) :
        value_(value), site_id_(site_id), site_counter_(site_counter), position_(position) {}

    bool Symbol::operator<(const Symbol& other) {
        return this->position_ < other.position_ ||
            (this->position_ == other.position_ && this->site_id_ < other.site_id_);
    }

    bool Symbol::operator==(const Symbol &other) {
        return this->site_id_ == other.site_id_ && this->site_counter_ == other.site_counter_ &&
               this->position_ == other.position_;
    }

    char Symbol::value() const {
        return value_;
    }

    int Symbol::site_id() const {
        return site_id_;
    }

    int Symbol::site_counter() const {
        return site_counter_;
    }

    std::vector<int> Symbol::position() const {
        return position_;
    }
}
