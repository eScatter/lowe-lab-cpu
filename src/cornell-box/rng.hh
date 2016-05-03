#pragma once
#include <random>

namespace cornell
{
    class Rng
    {
        std::mt19937 generator_;

        public:
            static Rng &instance()
            {
                static Rng instance_;
                return instance_;
            }

            static std::mt19937 &generator()
            {
                return instance().generator_;
            }

            static void seed(unsigned s)
            {
                generator().seed(s);
            }

            Rng(Rng const &) = delete;
            void operator=(Rng const &) = delete;

        private:
            Rng() {}
    };
}

