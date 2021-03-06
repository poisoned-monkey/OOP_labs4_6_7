#pragma once
#include"tools.h"
#include"figure.h"
#include<memory>
struct  line : figure {
    line(const std::array<vertex, 2>& vertices) : vertices_(vertices) {}

    void render(const sdl::renderer& renderer) const override {
        renderer.set_color(color_.r, color_.g, color_.b);
        renderer.draw_line(vertices_[0].x, vertices_[0].y,
                           vertices_[1].x, vertices_[1].y);
    }

    void save(std::ostream& os) const override {
        os << "line" << std::endl;
        for (int32_t i = 0; i < 2; ++i) {
            os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
        }

        os << this->color_.r << ' ' << this->color_.g << ' ' << this->color_.b << std::endl;
    }
private:
    std::array<vertex, 2> vertices_;
};


struct  line_builder : builder {
    std::unique_ptr<figure> add_vertex(const vertex& v) {
        vertices_[n_] = v;
        n_ += 1;
        if (n_ != 2) {
            return nullptr;
        }
        jl.push(1, nullptr);
        return std::make_unique<line>(vertices_);
    }
private:
    int32_t n_ = 0;
    std::array<vertex, 2> vertices_;
};