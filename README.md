# ray tracer challenge

This is a C++20 implementation of [The Ray Tracer
Challenge](https://pragprog.com/titles/jbtracer/the-ray-tracer-challenge/).

## Contributors

*All* the code in this repository was produced in pair-programming sessions with [@bsubei](https://github.com/bsubei).

## Status

All the features described in the book are implemented, along with a few bonus features. A detailed list will be added
soon. Screenshots will be added soon as well.

## License

TBD

## TODO

Performance-related:

- [x] do rendering in multiple threads
- [ ] add microbenchmarks so we can measure something at least
    - [ ] allow for canvas sizes determined during runtime (so we can benchmark different sizes)
- [ ] profile and look for critical paths
- [ ] avoid unnecessary copies where it matters
- [ ] utilize SIMD for Matrix/transform operations
- [ ] BVH optimization for scenes with many objects

Code style/hygiene:

- [ ] revisit shared_ptr usage and ownership model
- [ ] redo folder structure (src/ has too many files). Probably put primitives in their own folder. Consider using
  namespaces.
- [ ] consider including using absolute paths
- [ ] strictly enforce include-what-you-use
- [ ] look for newer C++ 20/23 alternatives to existing code (e.g. ranges::min_element)

Features:

- [ ] render to window and move camera
    - [ ] low resolution/detail while moving camera (depends on performance)
- [ ] Next steps chapter
    - [ ] soft shadows
    - [ ] focal blur
    - [ ] motion blur
    - [ ] anti-aliasing
    - [ ] texture maps
- [ ] other bonus chapters
