
// Engine includes //
#include "random.hpp"
#include "trace.hpp"

static Random* random = nullptr;

bool Random::Initialize() {
    random = new Random;
    if (!random) {
        Trace::Message("Random failed to initialize.");
        return false;
    }

    return true;
}

void Random::Shutdown() {
    if (!random) return;

    delete random;
    random = nullptr;
}

vec3 Random::random_vec3(float low, float high) {
    mt19937 gen(random->rd());
    uniform_real_distribution<> dist(low, high);

    vec3 result_vec3 = { dist(gen), dist(gen), dist(gen) };
    return result_vec3;
}